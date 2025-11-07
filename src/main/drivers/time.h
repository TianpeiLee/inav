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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "common/time.h"

extern uint32_t usTicks;

void delayMicroseconds(timeUs_t us);
void delayNanos(timeDelta_t ns);
void delay(timeMs_t ms);

timeUs_t micros(void);
timeUs_t microsISR(void);
timeMs_t millis(void);

uint32_t ticks(void);

#if defined(CH32H41x)
uint32_t __get_MCYCLE(void);
void __set_MCYCLE(uint32_t value);
void __set_MCOUNT_INHIBIT(uint32_t value);
uint32_t __get_MCOUNT_INHIBIT(void);
#endif

#ifdef __cplusplus
}
#endif