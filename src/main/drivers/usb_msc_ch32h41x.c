/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Author: Chris Hockuba (https://github.com/conkerkh)
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "platform.h"

#if defined(USE_USB_MSC)

#include "build/build_config.h"

#include "common/utils.h"

#include "blackbox/blackbox.h"
#include "blackbox/blackbox_io.h"

#include "drivers/io.h"
#include "drivers/light_led.h"
#include "drivers/nvic.h"
#include "drivers/persistent.h"
#include "drivers/sdcard/sdmmc_sdio.h"
#include "drivers/time.h"
#include "drivers/usb_msc.h"



#include "usb_io.h"
#include "msc/usbd_storage.h"

#include "usbd_core.h"
#include "usbd_msc.h"
#include "usb_ch32h41x_usbhs_reg.h"

// #if defined(STM32F4)
// #include "usb_core.h"
// #include "usbd_cdc_vcp.h"
// #include "usb_io.h"
// #elif defined(STM32F7)
// #include "vcp_hal/usbd_cdc_interface.h"
// #include "usb_io.h"
// USBD_HandleTypeDef USBD_Device;
// #else
// #include "usb_core.h"
// #include "usb_init.h"
// #include "hw_config.h"
// #endif
// #include "msc/usbd_storage.h"

#define DEBOUNCE_TIME_MS 20

#if defined(MSC_USE_BUTTON)
static IO_t mscButton;
#endif

void mscInit(void)
{
#if defined(MSC_USE_BUTTON)
    if (usbDevConfig()->mscButtonPin) {
        mscButton = IOGetByTag(usbDevConfig()->mscButtonPin);
        IOInit(mscButton, OWNER_USB_MSC_PIN, 0);
        if (usbDevConfig()->mscButtonUsePullup) {
            IOConfigGPIO(mscButton, IOCFG_IPU);
        } else {
            IOConfigGPIO(mscButton, IOCFG_IPD);
        }
    }
#endif
}


//0xE205 -- DFU
#define MSC_IN_EP  0x81
#define MSC_OUT_EP 0x01

#define USBD_VID           0x1A86
#define USBD_PID           0xFE10 
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define USB_CONFIG_SIZE (9 + MSC_DESCRIPTOR_LEN)

#define MSC_MAX_MPS 64

static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0200, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_SELF_POWERED, USBD_MAX_POWER),
    MSC_DESCRIPTOR_INIT(0x00, MSC_OUT_EP, MSC_IN_EP, MSC_MAX_MPS, 0x05)
};

static const uint8_t device_quality_descriptor[] = {
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x00,
    0x00,
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 },                   /* Langid */
    "INAV",                                   /* Manufacturer */
    "INAV FC Mass Storage (FS Mode)",         /* Product */
    "2025123456",                                   /* Serial Number */
    "INAV CH32H415", 
    "INAV CH32H415"
};

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    return device_descriptor;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    return config_descriptor;
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    return device_quality_descriptor;
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    if (index > 5) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor msc_ram_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback
};


static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}


static struct usbd_interface intf0;

void msc_ram_init(uint8_t busid, uintptr_t reg_base)
{
    USBD_STORAGE_fops->Init(0);

    usbd_desc_register(busid, &msc_ram_descriptor);
    usbd_add_interface(busid, usbd_msc_init_intf(busid, &intf0, MSC_OUT_EP, MSC_IN_EP));
    usbd_initialize(busid, reg_base, usbd_event_handler);
}


static void msc_usb_gpio_config(void)
{
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_AFIO | RCC_HB2Periph_GPIOB, ENABLE);
    //remap
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
}

static void msc_usb_clk_config(void)
{
        //disable first
        RCC_HBPeriphClockCmd(RCC_HBPeriph_USBHS, DISABLE);
        RCC_UTMIcmd(DISABLE);
        if((RCC->PLLCFGR & RCC_SYSPLL_SEL) != RCC_SYSPLL_USBHS)
        {
            RCC_USBHS_PLLCmd(DISABLE);
        }


    if((RCC->PLLCFGR & RCC_SYSPLL_SEL) != RCC_SYSPLL_USBHS)
    {
        /* Initialize USBHS 480M PLL */
        RCC_USBHS_PLLCmd(DISABLE);
        RCC_USBHSPLLCLKConfig(RCC_USBHSPLLSource_HSE);
        RCC_USBHSPLLReferConfig(RCC_USBHSPLLRefer_25M);
        RCC_USBHSPLLClockSourceDivConfig(RCC_USBHSPLL_IN_Div1);
        RCC_USBHS_PLLCmd(ENABLE);
    }
    /* Enable UTMI Clock */
    RCC_UTMIcmd(ENABLE);
    /* Enable USBHS Clock */
    RCC_HBPeriphClockCmd(RCC_HBPeriph_USBHS, ENABLE);
}



uint8_t mscStart(void)
{
    ledInit(false);

    //gpio remap
    msc_usb_gpio_config( );
    //Start USB
    usbGenerateDisconnectPulse();

    IOInit(IOGetByTag(IO_TAG(PB8)), OWNER_USB,0, 0);
    IOInit(IOGetByTag(IO_TAG(PB9)), OWNER_USB,0, 0);


    switch (blackboxConfig()->device) {
#ifdef USE_SDCARD
    case BLACKBOX_DEVICE_SDCARD:
        USBD_STORAGE_fops = &USBD_MSC_MICRO_SDIO_fops;
        break;
#endif

#ifdef USE_FLASHFS
    case BLACKBOX_DEVICE_FLASH:
        USBD_STORAGE_fops = &USBD_MSC_EMFAT_fops;
        break;
#endif
    default:
        return 1;
    }

    //usb clk init
    msc_usb_clk_config( ); 
    usb_rxsof_handler = NULL;
    msc_ram_init(0, 0);

    persistentObjectWrite(PERSISTENT_OBJECT_RESET_REASON, RESET_NONE);

    NVIC_SetPriority(USBHS_IRQn,NVIC_PRIO_USB) ;
    NVIC_EnableIRQ(USBHS_IRQn);
    
    // NVIC configuration for SYSTick
    NVIC_DisableIRQ(SysTick1_IRQn);
    asm("fence.i");
    NVIC_SetPriority(SysTick1_IRQn, 0);
    NVIC_EnableIRQ(SysTick1_IRQn);

    return 0;
}

bool mscCheckButton(void)
{
    bool result = false;
#if defined(MSC_USE_BUTTON)
    if (mscButton) {
        uint8_t state = IORead(mscButton);
        if (usbDevConfig()->mscButtonUsePullup) {
            result = state == 0;
        } else {
            result = state == 1;
        }
    }
#endif
    return result;
}

void mscWaitForButton(void)
{
    // In order to exit MSC mode simply disconnect the board, or push the button again.
    while (mscCheckButton());
    delay(DEBOUNCE_TIME_MS);
    while (true) {
        asm("NOP");
        if (mscCheckButton()) {
            delay(1);
            NVIC_SystemReset();
        }
    }
}


static uint32_t g_block_size = 0;
void usbd_msc_get_cap(uint8_t busid, uint8_t lun, uint32_t *block_num, uint32_t *block_size)
{
    (void)busid;
    USBD_STORAGE_fops->GetCapacity(lun, block_num, block_size);
    g_block_size = *block_size;
}


int usbd_msc_sector_read(uint8_t busid, uint8_t lun, uint32_t sector, uint8_t *buffer, uint32_t length)
{
    (void)busid;
    return USBD_STORAGE_fops->Read(lun, buffer, sector, length / g_block_size);
}


int usbd_msc_sector_write(uint8_t busid, uint8_t lun, uint32_t sector, uint8_t *buffer, uint32_t length)
{
   (void)busid;
   return  USBD_STORAGE_fops->Write(lun, buffer, sector, length / g_block_size);
}

#endif
