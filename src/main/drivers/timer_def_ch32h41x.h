/*
 * This file is part of INAV.
 *
 * INAV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * INAV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with INAV.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define timerDMASafeType_t  uint32_t

#define DEF_TIM_DMAMAP__D(dma, stream, channel)         DMA_TAG(dma, stream, channel)
#define DEF_TIM_DMAMAP__NONE                            DMA_NONE

// Define TIM device/DMA/MUX 
#define DEF_TIM(tim, ch, pin, usage, flags, dmavar)     {               \
     tim,                                                               \
     IO_TAG(pin),                                                       \
     DEF_TIM_CHNL_ ## ch,                                               \
     DEF_TIM_OUTPUT(ch) | flags,                                        \
     IOCFG_AF_PP,                                                       \
     DEF_TIM_AF(TCH_## tim ## _ ## ch, pin),                            \
     usage,                                                             \
     DEF_TIM_DMAMAP(dmavar, tim ## _ ## ch),                            \
     DEF_TIM_DMA_REQUEST(tim ## _ ## ch)                                \
  }

// AF mappings
#define DEF_TIM_AF(timch, pin)        CONCAT(DEF_TIM_AF__, DEF_TIM_AF__ ## pin ## __ ## timch)
// MUX mappings
#define DEF_TIM_AF__D(af_n, tim_n)     GPIO_AF ## af_n

#define DEF_TIM_DMA_REQUEST(timch) \
    CONCAT(DEF_TIM_DMA_REQ__, DEF_TIM_TCH2BTCH(timch))


/* add the DMA mappings here */
// D(DMAx, Stream, Channel)
// at32f43x has DMAMUX that allow arbitrary assignment of peripherals to streams.
#define DEF_TIM_DMA_FULL \
    D(1, 1, 0), D(1, 2, 0), D(1, 3, 0), D(1, 4, 0), D(1, 5, 0), D(1, 6, 0), D(1, 7, 0), D(1, 8, 0), \
    D(2, 1, 0), D(2, 2, 0), D(2, 3, 0), D(2, 4, 0), D(2, 5, 0), D(2, 6, 0), D(2, 7, 0), D(2, 8, 0),

#define DEF_TIM_DMA__BTCH_TIM1_CH1    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM1_CH2    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM1_CH3    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM1_CH4    DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM2_CH1    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM2_CH2    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM2_CH3    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM2_CH4    DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM3_CH1    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM3_CH2    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM3_CH3    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM3_CH4    DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM4_CH1    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM4_CH2    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM4_CH3    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM4_CH4    DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM5_CH1    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM5_CH2    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM5_CH3    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM5_CH4    DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM8_CH1    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM8_CH2    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM8_CH3    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM8_CH4    DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM9_CH1    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM9_CH2    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM9_CH3    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM9_CH4    DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM10_CH1   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM10_CH2   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM10_CH3   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM10_CH4   DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM11_CH1   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM11_CH2   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM11_CH3   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM11_CH4   DEF_TIM_DMA_FULL

#define DEF_TIM_DMA__BTCH_TIM12_CH1   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM12_CH2   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM12_CH3   DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM12_CH4   DEF_TIM_DMA_FULL


// TIM_UP table
#define DEF_TIM_DMA__BTCH_TIM1_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM2_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM3_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM4_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM5_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM6_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM7_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM8_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM9_UP     DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM10_UP    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM11_UP    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM12_UP    DEF_TIM_DMA_FULL
#define DEF_TIM_DMA__BTCH_TIM13_UP    NONE
#define DEF_TIM_DMA__BTCH_TIM14_UP    NONE

#define DMA_REQUEST_NONE 255

#define DEF_TIM_DMA_REQ__BTCH_TIM1_CH1    DMAMUX_DMAREQ_ID_TIM1_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM1_CH2    DMAMUX_DMAREQ_ID_TIM1_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM1_CH3    DMAMUX_DMAREQ_ID_TIM1_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM1_CH4    DMAMUX_DMAREQ_ID_TIM1_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM2_CH1    DMAMUX_DMAREQ_ID_TIM2_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM2_CH2    DMAMUX_DMAREQ_ID_TIM2_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM2_CH3    DMAMUX_DMAREQ_ID_TIM2_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM2_CH4    DMAMUX_DMAREQ_ID_TIM2_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM3_CH1    DMAMUX_DMAREQ_ID_TIM3_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM3_CH2    DMAMUX_DMAREQ_ID_TIM3_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM3_CH3    DMAMUX_DMAREQ_ID_TIM3_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM3_CH4    DMAMUX_DMAREQ_ID_TIM3_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM4_CH1    DMAMUX_DMAREQ_ID_TIM4_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM4_CH2    DMAMUX_DMAREQ_ID_TIM4_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM4_CH3    DMAMUX_DMAREQ_ID_TIM4_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM4_CH4    DMAMUX_DMAREQ_ID_TIM4_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM5_CH1    DMAMUX_DMAREQ_ID_TIM5_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM5_CH2    DMAMUX_DMAREQ_ID_TIM5_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM5_CH3    DMAMUX_DMAREQ_ID_TIM5_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM5_CH4    DMAMUX_DMAREQ_ID_TIM5_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM8_CH1    DMAMUX_DMAREQ_ID_TIM8_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM8_CH2    DMAMUX_DMAREQ_ID_TIM8_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM8_CH3    DMAMUX_DMAREQ_ID_TIM8_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM8_CH4    DMAMUX_DMAREQ_ID_TIM8_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM9_CH1    DMAMUX_DMAREQ_ID_TIM9_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM9_CH2    DMAMUX_DMAREQ_ID_TIM9_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM9_CH3    DMAMUX_DMAREQ_ID_TIM9_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM9_CH4    DMAMUX_DMAREQ_ID_TIM9_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM10_CH1   DMAMUX_DMAREQ_ID_TIM10_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM10_CH2   DMAMUX_DMAREQ_ID_TIM10_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM10_CH3   DMAMUX_DMAREQ_ID_TIM10_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM10_CH4   DMAMUX_DMAREQ_ID_TIM10_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM11_CH1   DMAMUX_DMAREQ_ID_TIM11_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM11_CH2   DMAMUX_DMAREQ_ID_TIM11_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM11_CH3   DMAMUX_DMAREQ_ID_TIM11_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM11_CH4   DMAMUX_DMAREQ_ID_TIM11_CH4

#define DEF_TIM_DMA_REQ__BTCH_TIM12_CH1   DMAMUX_DMAREQ_ID_TIM12_CH1
#define DEF_TIM_DMA_REQ__BTCH_TIM12_CH2   DMAMUX_DMAREQ_ID_TIM12_CH2
#define DEF_TIM_DMA_REQ__BTCH_TIM12_CH3   DMAMUX_DMAREQ_ID_TIM12_CH3
#define DEF_TIM_DMA_REQ__BTCH_TIM12_CH4   DMAMUX_DMAREQ_ID_TIM12_CH4


// TIM_UP request table
#define DEF_TIM_DMA_REQ__BTCH_TIM1_UP     DMAMUX_DMAREQ_ID_TIM1_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM2_UP     DMAMUX_DMAREQ_ID_TIM2_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM3_UP     DMAMUX_DMAREQ_ID_TIM3_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM4_UP     DMAMUX_DMAREQ_ID_TIM4_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM5_UP     DMAMUX_DMAREQ_ID_TIM5_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM8_UP     DMAMUX_DMAREQ_ID_TIM8_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM9_UP     DMAMUX_DMAREQ_ID_TIM9_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM10_UP    DMAMUX_DMAREQ_ID_TIM10_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM11_UP    DMAMUX_DMAREQ_ID_TIM11_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM12_UP    DMAMUX_DMAREQ_ID_TIM12_UP
#define DEF_TIM_DMA_REQ__BTCH_TIM13_UP    DMA_REQUEST_NONE
#define DEF_TIM_DMA_REQ__BTCH_TIM14_UP    DMA_REQUEST_NONE

// AF table 
//NONE d(mux_id, timerid)
#define DEF_TIM_AF__NONE__TCH_TIM1_CH1     D(1, 1)
#define DEF_TIM_AF__NONE__TCH_TIM1_CH2     D(1, 1)
#define DEF_TIM_AF__NONE__TCH_TIM1_CH3     D(1, 1)
#define DEF_TIM_AF__NONE__TCH_TIM1_CH4     D(1, 1)
//8x USE TIM3
#define DEF_TIM_AF__NONE__TCH_TIM3_CH1     D(1, 3)
#define DEF_TIM_AF__NONE__TCH_TIM3_CH2     D(1, 3)
#define DEF_TIM_AF__NONE__TCH_TIM3_CH3     D(1, 3)
#define DEF_TIM_AF__NONE__TCH_TIM3_CH4     D(1, 3)
//4x USE TIM8
#define DEF_TIM_AF__NONE__TCH_TIM8_CH1     D(1, 8)
#define DEF_TIM_AF__NONE__TCH_TIM8_CH2     D(1, 8)
#define DEF_TIM_AF__NONE__TCH_TIM8_CH3     D(1, 8)
#define DEF_TIM_AF__NONE__TCH_TIM8_CH4     D(1, 8)



//TIM1 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PE9__TCH_TIM1_CH1      D(1, 1)
#define DEF_TIM_AF__PA8__TCH_TIM1_CH1      D(1, 1)

#define DEF_TIM_AF__PE11__TCH_TIM1_CH2     D(1, 1)
#define DEF_TIM_AF__PA9__TCH_TIM1_CH2      D(1, 1)

#define DEF_TIM_AF__PE13__TCH_TIM1_CH3     D(1, 1)
#define DEF_TIM_AF__PA10__TCH_TIM1_CH3     D(1, 1)

#define DEF_TIM_AF__PE14__TCH_TIM1_CH4     D(1, 1)
#define DEF_TIM_AF__PA11__TCH_TIM1_CH4     D(1, 1)

#define DEF_TIM_AF__PE8__TCH_TIM1_CH1N     D(1, 1)
#define DEF_TIM_AF__PA7__TCH_TIM1_CH1N     D(1, 1)
#define DEF_TIM_AF__PB13__TCH_TIM1_CH1N    D(1, 1)

#define DEF_TIM_AF__PE10__TCH_TIM1_CH2N    D(1, 1)
#define DEF_TIM_AF__PB0__TCH_TIM1_CH2N     D(1, 1)
#define DEF_TIM_AF__PB14__TCH_TIM1_CH2N    D(1, 1)

#define DEF_TIM_AF__PE12__TCH_TIM1_CH3N    D(1, 1)
#define DEF_TIM_AF__PB1__TCH_TIM1_CH3N     D(1, 1)
#define DEF_TIM_AF__PB15__TCH_TIM1_CH3N    D(1, 1)

//TIM8 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PE3__TCH_TIM8_CH1      D(0, 8)
#define DEF_TIM_AF__PE4__TCH_TIM8_CH2      D(0, 8)
#define DEF_TIM_AF__PE5__TCH_TIM8_CH3      D(0, 8)
#define DEF_TIM_AF__PE6__TCH_TIM8_CH4      D(0, 8)

#define DEF_TIM_AF__PC6__TCH_TIM8_CH1      D(3, 8)
#define DEF_TIM_AF__PC7__TCH_TIM8_CH2      D(3, 8)
#define DEF_TIM_AF__PC8__TCH_TIM8_CH3      D(3, 8)
#define DEF_TIM_AF__PC9__TCH_TIM8_CH4      D(3, 8)

#define DEF_TIM_AF__PC1__TCH_TIM8_CH1N     D(0, 8)
#define DEF_TIM_AF__PC2__TCH_TIM8_CH2N     D(0, 8)
#define DEF_TIM_AF__PC3__TCH_TIM8_CH3N     D(0, 8)

#define DEF_TIM_AF__PA5__TCH_TIM8_CH1N     D(3, 8)
#define DEF_TIM_AF__PB14__TCH_TIM8_CH2N    D(3, 8)
#define DEF_TIM_AF__PB15__TCH_TIM8_CH3N    D(3, 8)

#define DEF_TIM_AF__PA7__TCH_TIM8_CH1N     D(3, 8)
#define DEF_TIM_AF__PB0__TCH_TIM8_CH2N     D(3, 8)
#define DEF_TIM_AF__PB1__TCH_TIM8_CH3N     D(3, 8)


//TIM2 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PA0__TCH_TIM2_CH1      D(1, 2)
#define DEF_TIM_AF__PA5__TCH_TIM2_CH1      D(1, 2)
#define DEF_TIM_AF__PA15__TCH_TIM2_CH1     D(1, 2)

#define DEF_TIM_AF__PA1__TCH_TIM2_CH2      D(1, 2)
#define DEF_TIM_AF__PB3__TCH_TIM2_CH2      D(1, 2)

#define DEF_TIM_AF__PA2__TCH_TIM2_CH3      D(1, 2)
#define DEF_TIM_AF__PB10__TCH_TIM2_CH3     D(1, 2)

#define DEF_TIM_AF__PA3__TCH_TIM2_CH4      D(1, 2)
#define DEF_TIM_AF__PB11__TCH_TIM2_CH4     D(1, 2)

//TIM3 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PA6__TCH_TIM3_CH1      D(2, 3)
#define DEF_TIM_AF__PB4__TCH_TIM3_CH1      D(2, 3)
#define DEF_TIM_AF__PC6__TCH_TIM3_CH1      D(2, 3)
#define DEF_TIM_AF__PD3__TCH_TIM3_CH1      D(9, 3)

#define DEF_TIM_AF__PA7__TCH_TIM3_CH2      D(2, 3)
#define DEF_TIM_AF__PB5__TCH_TIM3_CH2      D(2, 3)
#define DEF_TIM_AF__PC7__TCH_TIM3_CH2      D(2, 3)
#define DEF_TIM_AF__PD4__TCH_TIM3_CH2      D(9, 3)

#define DEF_TIM_AF__PB0__TCH_TIM3_CH3      D(2, 3)
#define DEF_TIM_AF__PC8__TCH_TIM3_CH3      D(2, 3)
#define DEF_TIM_AF__PD5__TCH_TIM3_CH3      D(9, 3)

#define DEF_TIM_AF__PB1__TCH_TIM3_CH4      D(2, 3)
#define DEF_TIM_AF__PC9__TCH_TIM3_CH4      D(2, 3)
#define DEF_TIM_AF__PD6__TCH_TIM3_CH4      D(9, 3)

//TIM4 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PB6__TCH_TIM4_CH1      D(2, 4)
#define DEF_TIM_AF__PD12__TCH_TIM4_CH1     D(2, 4)
#define DEF_TIM_AF__PE3__TCH_TIM4_CH1      D(2, 4)

#define DEF_TIM_AF__PB7__TCH_TIM4_CH2      D(2, 4)
#define DEF_TIM_AF__PD13__TCH_TIM4_CH2     D(2, 4)
#define DEF_TIM_AF__PE4__TCH_TIM4_CH2      D(2, 4)

#define DEF_TIM_AF__PB8__TCH_TIM4_CH3      D(2, 4)
#define DEF_TIM_AF__PD14__TCH_TIM4_CH3     D(2, 4)
#define DEF_TIM_AF__PE5__TCH_TIM4_CH3      D(2, 4)

#define DEF_TIM_AF__PB9__TCH_TIM4_CH4      D(2, 4)
#define DEF_TIM_AF__PD15__TCH_TIM4_CH4     D(2, 4)
#define DEF_TIM_AF__PE6__TCH_TIM4_CH4      D(2, 4)

//TIM5 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PA0__TCH_TIM5_CH1      D(2, 5)
#define DEF_TIM_AF__PD12__TCH_TIM5_CH1     D(6, 5)
#define DEF_TIM_AF__PC1__TCH_TIM5_CH1      D(2, 5)

#define DEF_TIM_AF__PA1__TCH_TIM5_CH2      D(2, 5)
#define DEF_TIM_AF__PD13__TCH_TIM5_CH2     D(6, 5)
#define DEF_TIM_AF__PC2__TCH_TIM5_CH2      D(2, 5)

#define DEF_TIM_AF__PA2__TCH_TIM5_CH3      D(2, 5)
#define DEF_TIM_AF__PD14__TCH_TIM5_CH3     D(6, 5)
#define DEF_TIM_AF__PC3__TCH_TIM5_CH3      D(2, 5)

#define DEF_TIM_AF__PA3__TCH_TIM5_CH4      D(2, 5)
#define DEF_TIM_AF__PD15__TCH_TIM5_CH4     D(6, 5)
#define DEF_TIM_AF__PB0__TCH_TIM5_CH4      D(4, 5)

//TIM9 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PB14__TCH_TIM9_CH1     D(2, 9)
#define DEF_TIM_AF__PA0__TCH_TIM9_CH1      D(6, 9)
#define DEF_TIM_AF__PC9__TCH_TIM9_CH1      D(6, 9)

#define DEF_TIM_AF__PB15__TCH_TIM9_CH2     D(2, 9)
#define DEF_TIM_AF__PA1__TCH_TIM9_CH2      D(6, 9)
#define DEF_TIM_AF__PC10__TCH_TIM9_CH2     D(2, 9)
#define DEF_TIM_AF__PB10__TCH_TIM9_CH2     D(2, 9)

#define DEF_TIM_AF__PE5__TCH_TIM9_CH3      D(4, 9)
#define DEF_TIM_AF__PA2__TCH_TIM9_CH3      D(4, 9)
#define DEF_TIM_AF__PC12__TCH_TIM9_CH3     D(2, 9)
#define DEF_TIM_AF__PB12__TCH_TIM9_CH3     D(8, 9)

#define DEF_TIM_AF__PE6__TCH_TIM9_CH4      D(4, 9)
#define DEF_TIM_AF__PA3__TCH_TIM9_CH4      D(4, 9)
#define DEF_TIM_AF__PC11__TCH_TIM9_CH4     D(2, 9)
#define DEF_TIM_AF__PB11__TCH_TIM9_CH4     D(9, 9)

//TIM10 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PF8__TCH_TIM10_CH1     D(9, 10)
#define DEF_TIM_AF__PA6__TCH_TIM10_CH1     D(9, 10)
#define DEF_TIM_AF__PB6__TCH_TIM10_CH1     D(0, 10)

#define DEF_TIM_AF__PF9__TCH_TIM10_CH2     D(9, 10)
#define DEF_TIM_AF__PA7__TCH_TIM10_CH2     D(9, 10)
#define DEF_TIM_AF__PB7__TCH_TIM10_CH2     D(0, 10)

#define DEF_TIM_AF__PF6__TCH_TIM10_CH3     D(9, 10)
#define DEF_TIM_AF__PA3__TCH_TIM10_CH3     D(8, 10)
#define DEF_TIM_AF__PB8__TCH_TIM10_CH3     D(1, 10)

#define DEF_TIM_AF__PF7__TCH_TIM10_CH4     D(9, 10)
#define DEF_TIM_AF__PA4__TCH_TIM10_CH4     D(9, 10)
#define DEF_TIM_AF__PB9__TCH_TIM10_CH4     D(1, 10)

//TIM11 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PD3__TCH_TIM11_CH1     D( 2, 11)
#define DEF_TIM_AF__PF6__TCH_TIM11_CH1     D(13, 11)
#define DEF_TIM_AF__PE0__TCH_TIM11_CH1     D(13, 11)

#define DEF_TIM_AF__PD4__TCH_TIM11_CH2     D( 2, 11)
#define DEF_TIM_AF__PF7__TCH_TIM11_CH2     D(13, 11)
#define DEF_TIM_AF__PE1__TCH_TIM11_CH2     D(13, 11)

#define DEF_TIM_AF__PD5__TCH_TIM11_CH3     D( 2, 11)
#define DEF_TIM_AF__PF8__TCH_TIM11_CH3     D(13, 11)
#define DEF_TIM_AF__PD7__TCH_TIM11_CH3     D(13, 11)

#define DEF_TIM_AF__PD6__TCH_TIM11_CH4     D( 2, 11)
#define DEF_TIM_AF__PF9__TCH_TIM11_CH4     D(13, 11)


//TIM12 MUX  d(mux_id, timerid)
#define DEF_TIM_AF__PB1__TCH_TIM12_CH1     D(5, 12)
#define DEF_TIM_AF__PE3__TCH_TIM12_CH1     D(3, 12)

#define DEF_TIM_AF__PB2__TCH_TIM12_CH2     D(5, 12)
#define DEF_TIM_AF__PE4__TCH_TIM12_CH2     D(3, 12)
#define DEF_TIM_AF__PE13__TCH_TIM12_CH2    D(2, 12)

#define DEF_TIM_AF__PF12__TCH_TIM12_CH3    D(13, 12)
#define DEF_TIM_AF__PE5__TCH_TIM12_CH3     D(3, 12)
#define DEF_TIM_AF__PE14__TCH_TIM12_CH3    D(2, 12)

#define DEF_TIM_AF__PF13__TCH_TIM12_CH4    D(13, 12)
#define DEF_TIM_AF__PE6__TCH_TIM12_CH4     D(3, 12)
#define DEF_TIM_AF__PE15__TCH_TIM12_CH4    D(2, 12)
