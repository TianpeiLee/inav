/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#ifdef USE_SPI

#include "drivers/bus_spi.h"
#include "drivers/exti.h"
#include "drivers/io.h"
#include "drivers/io_impl.h"
#include "drivers/rcc.h"

#ifndef SPI2_SCK_PIN
#define SPI2_NSS_PIN    PB11
#define SPI2_SCK_PIN    PB13
#define SPI2_MISO_PIN   PB14
#define SPI2_MOSI_PIN   PB15
#endif

#ifndef SPI3_SCK_PIN
#define SPI3_NSS_PIN    PF3
#define SPI3_SCK_PIN    PC10
#define SPI3_MISO_PIN   PC11
#define SPI3_MOSI_PIN   PC12
#endif

#ifndef SPI4_SCK_PIN
#define SPI4_NSS_PIN    PB10
#define SPI4_SCK_PIN    PE12
#define SPI4_MISO_PIN   PE13
#define SPI4_MOSI_PIN   PE14
#endif

#ifndef SPI2_NSS_PIN
#define SPI2_NSS_PIN NONE
#endif
#ifndef SPI3_NSS_PIN
#define SPI3_NSS_PIN NONE
#endif
#ifndef SPI4_NSS_PIN
#define SPI4_NSS_PIN NONE
#endif

#if defined(CH32H41x)  
    #if defined(USE_SPI_DEVICE_1) || defined(USE_SPI_DEVICE_2) || defined(USE_SPI_DEVICE_3) || defined(USE_SPI_DEVICE_4)
    static const uint32_t spiDivisorMapFast[] = {
        SPI_BaudRatePrescaler_Mode7,     // SPI_CLOCK_INITIALIZATON      390.625 KBits/s
        SPI_BaudRatePrescaler_Mode6,     // SPI_CLOCK_SLOW               781.25 KBits/s
        SPI_BaudRatePrescaler_Mode3,     // SPI_CLOCK_STANDARD           12.5 MBits/s
        SPI_BaudRatePrescaler_Mode3,     // SPI_CLOCK_FAST               25.0 MBits/s
        SPI_BaudRatePrescaler_Mode3      // SPI_CLOCK_ULTRAFAST          50.0 MBits/s
    };
    #endif
    //CH32H41x all spi clk from HCLK
//MAP spi pin config and af 
static spiDevice_t spiHardwareMap[] = {
#ifdef USE_SPI_DEVICE_1
#if defined(SPI1_SCK_AF) || defined(SPI1_MISO_AF) || defined(SPI1_MOSI_AF)
#if !defined(SPI1_SCK_AF) || !defined(SPI1_MISO_AF) || !defined(SPI1_MOSI_AF)
#error SPI1: SCK, MISO and MOSI AFs should be defined together in target.h!
#endif
    { .dev = SPI1, .nss = IO_TAG(SPI1_NSS_PIN), .sck = IO_TAG(SPI1_SCK_PIN), .miso = IO_TAG(SPI1_MISO_PIN), .mosi = IO_TAG(SPI1_MOSI_PIN), .rcc = RCC_HB2(SPI1), .sckAF = SPI1_SCK_AF, .misoAF = SPI1_MISO_AF, .mosiAF = SPI1_MOSI_AF, .divisorMap = spiDivisorMapFast }
#else
    { .dev = SPI1, .nss = IO_TAG(SPI1_NSS_PIN), .sck = IO_TAG(SPI1_SCK_PIN), .miso = IO_TAG(SPI1_MISO_PIN), .mosi = IO_TAG(SPI1_MOSI_PIN), .rcc = RCC_HB2(SPI1), .sckAF = GPIO_AF5, .misoAF = GPIO_AF5, .mosiAF = GPIO_AF5, .divisorMap = spiDivisorMapFast }
#endif
#else
    { .dev = NULL },     // No SPI1
#endif

#ifdef USE_SPI_DEVICE_2
#if defined(SPI2_SCK_AF) || defined(SPI2_MISO_AF) || defined(SPI2_MOSI_AF)
#if !defined(SPI2_SCK_AF) || !defined(SPI2_MISO_AF) || !defined(SPI2_MOSI_AF)
#error SPI2: SCK, MISO and MOSI AFs should be defined together in target.h!
#endif
    { .dev = SPI2, .nss = IO_TAG(SPI2_NSS_PIN), .sck = IO_TAG(SPI2_SCK_PIN), .miso = IO_TAG(SPI2_MISO_PIN), .mosi = IO_TAG(SPI2_MOSI_PIN), .rcc = RCC_HB1(SPI2), .sckAF = SPI2_SCK_AF, .misoAF = SPI2_MISO_AF, .mosiAF = SPI2_MOSI_AF, .divisorMap = spiDivisorMapFast },
#else
    { .dev = SPI2, .nss = IO_TAG(SPI2_NSS_PIN), .sck = IO_TAG(SPI2_SCK_PIN), .miso = IO_TAG(SPI2_MISO_PIN), .mosi = IO_TAG(SPI2_MOSI_PIN), .rcc = RCC_HB1(SPI2), .sckAF = GPIO_AF5, .misoAF = GPIO_AF5, .mosiAF = GPIO_AF5, .divisorMap = spiDivisorMapFast },
#endif
#else
    { .dev = NULL },    // No SPI2
#endif

#ifdef USE_SPI_DEVICE_3
#if defined(SPI3_SCK_AF) || defined(SPI3_MISO_AF) || defined(SPI3_MOSI_AF)
#if !defined(SPI3_SCK_AF) || !defined(SPI3_MISO_AF) || !defined(SPI3_MOSI_AF)
#error SPI3: SCK, MISO and MOSI AFs should be defined together in target.h!
#endif
    { .dev = SPI3, .nss = IO_TAG(SPI3_NSS_PIN), .sck = IO_TAG(SPI3_SCK_PIN), .miso = IO_TAG(SPI3_MISO_PIN), .mosi = IO_TAG(SPI3_MOSI_PIN), .rcc = RCC_HB1(SPI3), .sckAF = SPI3_SCK_AF, .misoAF = SPI3_MISO_AF, .mosiAF = SPI3_MOSI_AF, .divisorMap = spiDivisorMapFast },
#else
    { .dev = SPI3, .nss = IO_TAG(SPI3_NSS_PIN), .sck = IO_TAG(SPI3_SCK_PIN), .miso = IO_TAG(SPI3_MISO_PIN), .mosi = IO_TAG(SPI3_MOSI_PIN), .rcc = RCC_HB1(SPI3), .sckAF = GPIO_AF6, .misoAF = GPIO_AF6, .mosiAF = GPIO_AF6, .divisorMap = spiDivisorMapFast },
#endif
#else
    { .dev = NULL },    // No SPI3
#endif

#ifdef USE_SPI_DEVICE_4
#if defined(SPI4_SCK_AF) || defined(SPI4_MISO_AF) || defined(SPI4_MOSI_AF)
#if !defined(SPI4_SCK_AF) || !defined(SPI4_MISO_AF) || !defined(SPI4_MOSI_AF)
#error SPI3: SCK, MISO and MOSI AFs should be defined together in target.h!
#endif
    { .dev = SPI4, .nss = IO_TAG(SPI4_NSS_PIN), .sck = IO_TAG(SPI4_SCK_PIN), .miso = IO_TAG(SPI4_MISO_PIN), .mosi = IO_TAG(SPI4_MOSI_PIN), .rcc = RCC_HB1(SPI4), .sckAF = SPI4_SCK_AF, .misoAF = SPI4_MISO_AF, .mosiAF = SPI4_MOSI_AF, .divisorMap = spiDivisorMapFast },
#else
    { .dev = SPI4, .nss = IO_TAG(SPI4_NSS_PIN), .sck = IO_TAG(SPI4_SCK_PIN), .miso = IO_TAG(SPI4_MISO_PIN), .mosi = IO_TAG(SPI4_MOSI_PIN), .rcc = RCC_HB1(SPI4), .sckAF = GPIO_AF5, .misoAF = GPIO_AF5, .mosiAF = GPIO_AF5, .divisorMap = spiDivisorMapFast },
#endif
#else
    { .dev = NULL }    // No SPI4
#endif
};
 #else
#error "Invalid CPU"
#endif

SPIDevice spiDeviceByInstance(SPI_TypeDef *instance)
{
    if (instance == SPI1)
        return SPIDEV_1;

    if (instance == SPI2)
        return SPIDEV_2;

    if (instance == SPI3)
        return SPIDEV_3;
    
    if (instance == SPI4)
        return SPIDEV_4;

    return SPIINVALID;
}

bool spiInitDevice(SPIDevice device, bool leadingEdge)
{
    spiDevice_t *spi = &(spiHardwareMap[device]);

    if (!spi->dev) {
        return false;
    }

    if (spi->initDone) {
        return true;
    }
    // Enable SPI clock
    RCC_ClockCmd(spi->rcc, ENABLE);
    RCC_ResetCmd(spi->rcc, ENABLE);

    IOInit(IOGetByTag(spi->sck),  OWNER_SPI, RESOURCE_SPI_SCK,  device + 1);
    IOInit(IOGetByTag(spi->miso), OWNER_SPI, RESOURCE_SPI_MISO, device + 1);
    IOInit(IOGetByTag(spi->mosi), OWNER_SPI, RESOURCE_SPI_MOSI, device + 1);

    IOConfigGPIOAF(IOGetByTag(spi->sck),  SPI_IO_AF_SCK_CFG, spi->sckAF);
    IOConfigGPIOAF(IOGetByTag(spi->miso), SPI_IO_AF_MISO_CFG, spi->misoAF);
    IOConfigGPIOAF(IOGetByTag(spi->mosi), SPI_IO_AF_CFG, spi->mosiAF);

    if (spi->nss) {
        IOInit(IOGetByTag(spi->nss),  OWNER_SPI, RESOURCE_SPI_CS,  device + 1);
        IOConfigGPIO(IOGetByTag(spi->nss), SPI_IO_CS_CFG);
    }

    //DeInit SPI Hardware
    SPI_I2S_DeInit(spi->dev);
    SPI_InitTypeDef spiInit;
    spiInit.SPI_Mode = SPI_Mode_Master;
    spiInit.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spiInit.SPI_DataSize = SPI_DataSize_8b;
    spiInit.SPI_NSS = SPI_NSS_Soft;
    spiInit.SPI_FirstBit = SPI_FirstBit_MSB;
    spiInit.SPI_CRCPolynomial = 7;
    spiInit.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_Mode2;

    if(leadingEdge){
        //SPI_MODE0
        spiInit.SPI_CPOL = SPI_CPOL_Low;
        spiInit.SPI_CPHA = SPI_CPHA_1Edge;
    } else {
        spiInit.SPI_CPOL = SPI_CPOL_High;
        spiInit.SPI_CPHA = SPI_CPHA_2Edge;
    }

    SPI_Init(spi->dev, &spiInit);
    SPI_Cmd(spi->dev, ENABLE);

    if (spi->nss) {
        // Drive NSS high to disable connected SPI device.
        IOHi(IOGetByTag(spi->nss));
    }

    spi->initDone = true;
    return true;
}

uint32_t spiTimeoutUserCallback(SPI_TypeDef *instance)
{
    SPIDevice device = spiDeviceByInstance(instance);
    if (device == SPIINVALID) {
        return -1;
    }
    spiHardwareMap[device].errorCount++;
    return spiHardwareMap[device].errorCount;
}

// return uint8_t value or -1 when failure
uint8_t spiTransferByte(SPI_TypeDef *instance, uint8_t data)
{
    uint16_t spiTimeout = 1000;

    while (SPI_I2S_GetFlagStatus(instance, SPI_I2S_FLAG_TXE) == RESET)
        if ((spiTimeout--) == 0)
            return spiTimeoutUserCallback(instance);
  
    SPI_I2S_SendData(instance, data);

    spiTimeout = 1000;
    while (SPI_I2S_GetFlagStatus(instance, SPI_I2S_FLAG_RXNE) == RESET)
        if ((spiTimeout--) == 0)
            return spiTimeoutUserCallback(instance);

    return ((uint8_t) SPI_I2S_ReceiveData(instance));
}

/**
 * Return true if the bus is currently in the middle of a transmission.
 */
bool spiIsBusBusy(SPI_TypeDef *instance)
{
    return SPI_I2S_GetFlagStatus(instance, SPI_I2S_FLAG_TXE) == RESET || SPI_I2S_GetFlagStatus(instance, SPI_I2S_FLAG_BSY) == SET;
}

bool spiTransfer(SPI_TypeDef *instance, uint8_t *out, const uint8_t *in, int len)
{
    uint16_t spiTimeout = 1000;

    instance->DATAR;
    while (len--) {
        uint8_t b = in ? *(in++) : 0xFF;
        while (SPI_I2S_GetFlagStatus(instance, SPI_I2S_FLAG_TXE) == RESET) {
            if ((spiTimeout--) == 0)
                return spiTimeoutUserCallback(instance);
        }
        SPI_I2S_SendData(instance, b);
        spiTimeout = 1000;
        while (SPI_I2S_GetFlagStatus(instance, SPI_I2S_FLAG_RXNE) == RESET) {
            if ((spiTimeout--) == 0)
                return spiTimeoutUserCallback(instance);
        }
        b = SPI_I2S_ReceiveData(instance);
        if (out)
            *(out++) = b;
    }

    return true;
}

void spiSetSpeed(SPI_TypeDef *instance, SPIClockSpeed_e speed)
{
    #define BR_CLEAR_MASK 0xFFC7
    SPIDevice device = spiDeviceByInstance(instance);
    if (device == SPIINVALID) {
        return;
    }

    SPI_Cmd(instance, DISABLE);

    uint16_t tempRegister = instance->CTLR1;
    tempRegister &= BR_CLEAR_MASK;
    tempRegister |= spiHardwareMap[device].divisorMap[speed];
    instance->CTLR1 = tempRegister;
    
    SPI_Cmd(instance, ENABLE);
}

uint16_t spiGetErrorCounter(SPI_TypeDef *instance)
{
    SPIDevice device = spiDeviceByInstance(instance);
    if (device == SPIINVALID) {
        return 0;
    }
    return spiHardwareMap[device].errorCount;
}

void spiResetErrorCounter(SPI_TypeDef *instance)
{
    SPIDevice device = spiDeviceByInstance(instance);
    if (device != SPIINVALID) {
        spiHardwareMap[device].errorCount = 0;
    }
}

SPI_TypeDef * spiInstanceByDevice( SPIDevice device )
{
    return spiHardwareMap[device].dev;
}
#endif // USE_SPI
