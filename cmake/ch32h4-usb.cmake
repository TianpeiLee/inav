set(CH32_USBCORE_DIR "${MAIN_LIB_DIR}/main/CH32H41x/middlewares/core")
set(CH32_USBCDC_DIR "${MAIN_LIB_DIR}/main/CH32H41x/middlewares/class/cdc")
set(CH32_USBMSC_DIR "${MAIN_LIB_DIR}/main/CH32H41x/middlewares/class/msc")
set(CH32_USBBOARD_DIR "${MAIN_LIB_DIR}/main/CH32H41x/middlewares/board")
set(CH32_USBREG_DIR "${MAIN_LIB_DIR}/main/CH32H41x/middlewares/ch32h41x_hs")
set(CH32_USBCOMM_DIR "${MAIN_LIB_DIR}/main/CH32H41x/middlewares/common")


set(CH32H4_USB_INCLUDE_DIRS
    "${CH32_USBCORE_DIR}"
    "${CH32_USBCDC_DIR}"
    "${CH32_USBMSC_DIR}"
    "${CH32_USBBOARD_DIR}"
    "${CH32_USBREG_DIR}"
    "${CH32_USBCOMM_DIR}"
)

set(CH32_USBCORE_SRC
    "${CH32_USBCORE_DIR}/usbd_core.c"
)
set(CH32_USBCDC_SRC
    "${CH32_USBCDC_DIR}/usbd_cdc_acm.c"
    "${CH32_USBBOARD_DIR}/cdc_vcp_ch32h41x.c"
)

set(CH32_USBREG_SRC
    "${CH32_USBREG_DIR}/usb_ch32h41x_usbhs_reg.c"
)

main_sources(CH32H4_VCP_SRC 
    drivers/serial_usb_vcp_ch32h41x.c 
    drivers/usb_io.c
)

set(CH32H4_USBMSC_SRC
    usbd_msc.c
)

main_sources(CH32H4_MSC_SRC 
    drivers/usb_msc_ch32h41x.c 
)

list(TRANSFORM CH32H4_USBMSC_SRC PREPEND "${CH32_USBMSC_DIR}/")

list(APPEND CH32H4_USBMSC_SRC ${CH32H4_MSC_SRC})

list(APPEND CH32H4_USB_SRC ${CH32_USBREG_SRC})
list(APPEND CH32H4_USB_SRC ${CH32H4_VCP_SRC})
list(APPEND CH32H4_USB_SRC ${CH32_USBCORE_SRC})
list(APPEND CH32H4_USB_SRC ${CH32_USBCDC_SRC})
