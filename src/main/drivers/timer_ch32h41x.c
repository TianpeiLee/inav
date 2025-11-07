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

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "build/atomic.h"

#include "common/utils.h"

#include "drivers/io.h"
#include "drivers/rcc.h"
#include "drivers/time.h"
#include "drivers/nvic.h"
#include "drivers/timer.h"
#include "drivers/timer_impl.h"

#include "ch32h417.h"

const timerDef_t timerDefinitions[HARDWARE_TIMER_DEFINITION_COUNT] = {
#if defined(TIM1)
    [0] = { .tim = TIM1,  .rcc = RCC_HB2(TIM1),  .irq = TIM1_CC_IRQn, .secondIrq = TIM1_UP_IRQn },
#endif

#if defined(TIM2)
    [1] = { .tim = TIM2,  .rcc = RCC_HB1(TIM2),  .irq = TIM2_IRQn},
#endif

#if defined(TIM3)
    [2] = { .tim = TIM3,  .rcc = RCC_HB1(TIM3),  .irq = TIM3_IRQn},
#endif

#if defined(TIM4)
    [3] = { .tim = TIM4,  .rcc = RCC_HB1(TIM4),  .irq = TIM4_IRQn},
#endif

#if defined(TIM5)
    [4] = { .tim = TIM5,  .rcc = RCC_HB1(TIM5),  .irq = TIM5_IRQn},
#endif

#if defined(TIM6)
    [5] = { .tim = TIM6,  .rcc = RCC_HB1(TIM6),  .irq = TIM6_IRQn},
#endif

#if defined(TIM7)
    [6] = { .tim = TIM7,  .rcc = RCC_HB1(TIM7),  .irq = TIM7_IRQn},
#endif

#if defined(TIM8) 
    [7] = { .tim = TIM8,  .rcc = RCC_HB2(TIM8),  .irq = TIM8_CC_IRQn, .secondIrq = TIM8_UP_IRQn },
#endif

#if defined(TIM9)
    [8] = { .tim = TIM9,  .rcc = RCC_HB2(TIM9),  .irq = TIM9_IRQn},
#endif

#if defined(TIM10)
    [9] = { .tim = TIM10, .rcc = RCC_HB2(TIM10), .irq = TIM10_IRQn},
#endif

#if defined(TIM11)
    [10] = { .tim = TIM11, .rcc = RCC_HB2(TIM11), .irq = TIM11_IRQn},
#endif

#if defined(TIM12) 
    [11] = { .tim = TIM12, .rcc = RCC_HB2(TIM12), .irq = TIM12_IRQn},
#endif

};

uint32_t timerClock(TIM_TypeDef *tim)
{
    UNUSED(tim);
    return HCLKClock;
}

// Timer IRQ handlers
#if defined(TIM1)
_TIM_IRQ_HANDLER(TIM1_CC_IRQHandler,1)
_TIM_IRQ_HANDLER(TIM1_UP_IRQHandler,1)
#endif

#if defined(TIM2)
_TIM_IRQ_HANDLER(TIM2_IRQHandler,2)
#endif

#if defined(TIM3)
_TIM_IRQ_HANDLER(TIM3_IRQHandler,3)
#endif

#if defined(TIM4)
_TIM_IRQ_HANDLER(TIM4_IRQHandler,4)
#endif

#if defined(TIM5)
_TIM_IRQ_HANDLER(TIM5_IRQHandler,5)
#endif

#if defined(TIM6)
_TIM_IRQ_HANDLER(TIM6_IRQHandler,6)
#endif

#if defined(TIM7)
_TIM_IRQ_HANDLER(TIM7_IRQHandler,7)
#endif

#if defined(TIM8)
_TIM_IRQ_HANDLER(TIM8_CC_IRQHandler,8)
_TIM_IRQ_HANDLER(TIM8_UP_IRQHandler,8)
#endif

#if defined(TIM9)
_TIM_IRQ_HANDLER(TIM9_IRQHandler,9)
#endif

#if defined(TIM10)
_TIM_IRQ_HANDLER(TIM10_IRQHandler,10)
#endif

#if defined(TIM11)
_TIM_IRQ_HANDLER(TIM11_IRQHandler,11)
#endif

#if defined(TIM12)
_TIM_IRQ_HANDLER(TIM12_IRQHandler,12)
#endif


