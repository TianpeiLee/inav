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

#pragma once

#define TARGET_BOARD_IDENTIFIER "WCH4"
#define USBD_PRODUCT_STRING     "WCH CH32H41x"

#undef USE_LOG

#define LED0                    PC4

#define BEEPER                  PF4
#define BEEPER_INVERTED


#define ENABLE_DSHOT


//Gyro & ACC
#define USE_SPI
#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN       PC10
#define SPI3_MISO_PIN      PC11
#define SPI3_MOSI_PIN      PC12
#define SPI3_NSS_PIN       PF3

#define SPI3_SCK_AF        GPIO_AF6
#define SPI3_MISO_AF       GPIO_AF6
#define SPI3_MOSI_AF       GPIO_AF6


//LSM6DXX
#define USE_IMU_LSM6DXX
#define IMU_LSM6DXX_ALIGN           CW0_DEG
#define LSM6DXX_SPI_BUS             BUS_SPI3
#define LSM6DXX_CS_PIN              SPI3_NSS_PIN


// ICM42605/ICM42688P
#define USE_IMU_ICM42605
#define IMU_ICM42605_ALIGN          CW0_DEG
#define ICM42605_SPI_BUS            BUS_SPI3
#define ICM42605_CS_PIN             SPI3_NSS_PIN



//-------------------I2C-------------------
#define USE_I2C
#define USE_I2C_DEVICE_2
#define I2C2_SCL                PC0        // SCL pad
#define I2C2_SDA                PC1        // SDA pad

#define USE_BARO
#define BARO_I2C_BUS             BUS_I2C2
#define USE_BARO_DPS310

#define USE_MAG
#define MAG_I2C_BUS             BUS_I2C2
#define USE_MAG_ALL
#define DEFAULT_I2C_BUS         BUS_I2C2

#define USE_PITOT_ADC
#define PITOT_I2C_BUS           BUS_I2C2
#define TEMPERATURE_I2C_BUS     BUS_I2C2

//--------------------blackbox---------------
#define USE_SPI_DEVICE_4

#define SPI4_SCK_PIN       PE12
#define SPI4_MISO_PIN      PE13
#define SPI4_MOSI_PIN      PE14
#define SPI4_NSS_PIN       PB10

#define SPI4_SCK_AF      GPIO_AF5
#define SPI4_MISO_AF     GPIO_AF5
#define SPI4_MOSI_AF     GPIO_AF5

#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT
#define M25P16_CS_PIN      SPI4_NSS_PIN
#define M25P16_SPI_BUS     BUS_SPI4
#define USE_FLASHFS
#define USE_FLASH_M25P16



#define USE_SPI_DEVICE_2
#define SPI2_NSS_PIN            PE11
#define SPI2_SCK_PIN            PB13
#define SPI2_MISO_PIN           PB14
#define SPI2_MOSI_PIN           PB15

#define SPI2_SCK_AF          GPIO_AF5
#define SPI2_MISO_AF         GPIO_AF5
#define SPI2_MOSI_AF         GPIO_AF5

//-------------------UART---------------------
#define USE_VCP
// #undef USE_USB_MSC      //调试时候禁用USB
// #undef USE_TEMPERATURE_SENSOR

// #define USE_LOG
// #define VBUS_SENSING_PIN        PC2
// #define VBUS_SENSING_ENABLED

// #define USE_UART_INVERTER //无此功能

#define USE_UART1
#define UART1_RX_PIN            PA10
#define UART1_TX_PIN            PA9
#define UART1_AHB1_PERIPHERALS  RCC_HBPeriph_DMA2
// #define INVERTER_PIN_UART1_RX   PC0 // PC0 used as inverter select GPIO

#define USE_UART2
#define UART2_TX_PIN            PA2
#define UART2_RX_PIN            PA3

#define USE_UART3
#define UART3_RX_PIN            PA13
#define UART3_TX_PIN            PA14

#define USE_UART4
#define UART4_TX_PIN            PC6
#define UART4_RX_PIN            PC7

#define USE_UART5
#define UART5_TX_PIN            PE0
#define UART5_RX_PIN            PF5

#define USE_UART6
#define UART6_RX_PIN            PA1
#define UART6_TX_PIN            PA0

#define USE_UART7
#define UART7_RX_PIN            NONE
#define UART7_TX_PIN            PB12

#define USE_UART8
#define UART8_TX_PIN            PB4
#define UART8_RX_PIN            PB3

#define SERIAL_PORT_COUNT       9 //VCP, USART1-8


#define DEFAULT_RX_TYPE         RX_TYPE_SERIAL
#define SERIALRX_PROVIDER       SERIALRX_CRSF
#define SERIALRX_UART           SERIAL_PORT_USART1


// #define USE_RANGEFINDER
// #define RANGEFINDER_I2C_BUS     BUS_I2C2
#define USE_RANGEFINDER
#define USE_RANGEFINDER_MSP
#define USE_OPFLOW
#define USE_OPFLOW_MSP


//-----------------ADC--------------------
#define USE_ADC
#define ADC_CHANNEL_1_PIN               PC2
#define ADC_CHANNEL_2_PIN               PC3

#define CURRENT_METER_ADC_CHANNEL       ADC_CHN_1
#define VBAT_ADC_CHANNEL                ADC_CHN_2

#define ADC_CHANNEL_1_INSTANCE          ADC1
#define ADC_CHANNEL_2_INSTANCE          ADC1


#define SENSORS_SET (SENSOR_ACC|SENSOR_MAG|SENSOR_BARO)

#define USE_LED_STRIP
#define WS2811_PIN                      PB6



#define DEFAULT_RX_TYPE         RX_TYPE_SERIAL
#define DISABLE_RX_PWM_FEATURE
#define DEFAULT_FEATURES        (FEATURE_TX_PROF_SEL | FEATURE_BLACKBOX | FEATURE_VBAT|FEATURE_CURRENT_METER|FEATURE_OSD)
#define CURRENT_METER_SCALE     250

// #define USE_SPEKTRUM_BIND
// #define BIND_PIN                PA3 // USART3 RX

#define USE_SERIAL_4WAY_BLHELI_INTERFACE

// Number of available PWM outputs
#define MAX_PWM_OUTPUT_PORTS    5
#define TARGET_MOTOR_COUNT      4

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         0xffff
#define TARGET_IO_PORTE         0xffff
#define TARGET_IO_PORTF         0xffff

#define USE_DSHOT
#define USE_ESC_SENSOR


