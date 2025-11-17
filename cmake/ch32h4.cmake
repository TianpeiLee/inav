include(qingke-v5f)
include(ch32-stdperiph)
include(ch32h4-usb)


set(CH32H4_STDPERIPH_DIR "${MAIN_LIB_DIR}/main/CH32H41x/Peripheral")
set(CH32H4_CMSIS_CORE_DIR "${MAIN_LIB_DIR}/main/CH32H41x/Cmsis/Core")
set(CH32H4_CMSIS_DEBUG_DIR "${MAIN_LIB_DIR}/main/CH32H41x/Cmsis/Debug")
set(CH32H4_CMSIS_USER_DIR "${MAIN_LIB_DIR}/main/CH32H41x/Cmsis/User")
  
set(CH32H4_STDPERIPH_SRC_EXCLUDES
        ch32h417_can.c
        ch32h417_dvp.c
        ch32h417_dfsdm.c
        ch32h417_ecdc.c
        ch32h417_eth.c
        ch32h417_gpha.c
        ch32h417_serdes.c
        ch32h417_swpmi.c
)

set(CH32H4_STDPERIPH_SRC_DIR "${CH32H4_STDPERIPH_DIR}/src")
glob_except(CH32H4_STDPERIPH_SRC "${CH32H4_STDPERIPH_SRC_DIR}/*.c" "${CH32H4_STDPERIPH_SRC_EXCLUDES}")

list(APPEND CH32H4_STDPERIPH_SRC "${CH32H4_CMSIS_CORE_DIR}/core_riscv.c" )
list(APPEND CH32H4_STDPERIPH_SRC "${CH32H4_CMSIS_DEBUG_DIR}/ch32_debug.c" )
list(APPEND CH32H4_STDPERIPH_SRC "${CH32H4_CMSIS_USER_DIR}/ch32h417_it.c" )
list(APPEND CH32H4_STDPERIPH_SRC "${CH32H4_CMSIS_USER_DIR}/system_ch32h417.c" )

main_sources(CH32H4_SRC
    config/config_streamer_ch32h41x.c
    config/config_streamer_ram.c
    config/config_streamer_extflash.c 
    drivers/adc_ch32h41x.c
    drivers/bus_i2c_ch32h41x.c
    drivers/bus_spi_ch32h41x.c
    drivers/dma_ch32h41x.c
    drivers/serial_uart_hal_ch32h41x.c
    drivers/serial_uart_ch32h41x.c
    drivers/system_ch32h41x.c
    drivers/timer.c 
    drivers/timer_ch32h41x.c 
    drivers/timer_impl_stdperiph_ch32h41x.c 
)
set_source_files_properties(${CH32H4_SRC} PROPERTIES COMPILE_FLAGS "-ffunction-sections -fdata-sections -frename-section=.text=.text.tcm_code")

set(CH32H4_INCLUDE_DIRS
    ${CMSIS_INCLUDE_DIR}
    ${CMSIS_DSP_INCLUDE_DIR}
    ${CH32H4_STDPERIPH_DIR}/inc
    ${CH32H4_CMSIS_DEBUG_DIR}
    ${CH32H4_CMSIS_CORE_DIR}
    ${CH32H4_CMSIS_USER_DIR}
)

set(CH32H4_DEFINITIONS
    ${QINGKE_V5F_DEFINITIONS}
    CH32H41x
    RISC_V 
)

function(target_ch32h41x)
    target_ch32(
        SOURCES ${CH32_STDPERIPH_SRC} ${CH32H4_SRC}
        COMPILE_DEFINITIONS ${CH32H4_DEFINITIONS}
        COMPILE_OPTIONS ${QINGKE_V5F_COMMON_OPTIONS} ${QINGKE_V5F_COMPILE_OPTIONS}
        INCLUDE_DIRECTORIES ${CH32H4_INCLUDE_DIRS}
        LINK_OPTIONS ${QINGKE_V5F_COMMON_OPTIONS} ${QINGKE_V5F_LINK_OPTIONS}

        MSC_SOURCES ${CH32H4_USBMSC_SRC} ${CH32H4_MSC_SRC}
        VCP_SOURCES ${CH32H4_USB_SRC} ${CH32H4_VCP_SRC}
        VCP_INCLUDE_DIRECTORIES ${CH32H4_USB_INCLUDE_DIRS}

        OPTIMIZATION -O2

        OPENOCD_TARGET ch32h415x

        ${ARGN}
    )
endfunction()

#target_ch32h41x_xEU6


set(ch32h41x_xEU6_COMPILE_DEFINITIONS
    CH32H415REU6
    MCU_FLASH_SIZE=960    #可以减小编译大小
)

function(target_ch32h41x_xEU6 name)
    target_ch32h41x(
        NAME ${name}
        STARTUP startup_ch32h417_v5f.s
        SOURCES ${CH32H4_STDPERIPH_SRC}
        COMPILE_DEFINITIONS ${ch32h41x_xEU6_COMPILE_DEFINITIONS}
        LINKER_SCRIPT ch32h41x_v5f
        #BOOTLOADER
        SVD ch32h41x_xEU6
        ${ARGN}
    )
endfunction()

#set(at32f43x_xGT7_COMPILE_DEFINITIONS
#    AT32F435RGT7
#    MCU_FLASH_SIZE=1024
#)

function(target_at32f43x_xGT7 name)

endfunction()


function(target_at32f43x_xMT7 name)

endfunction()


function(target_stm32f405xg name)
endfunction()

function(target_stm32f411xe name)
endfunction()

function(target_stm32f427xg name)
endfunction()

function(target_stm32f722xe name)
endfunction()

function(target_stm32f745xg name)
endfunction()

function(target_stm32f746xg name)
endfunction()

function(target_stm32f765xg name)
endfunction()

function(target_stm32f765xi name)
endfunction()

function(target_stm32h743xi name)
endfunction()

function(target_stm32h7Axi name)
endfunction()