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

#if defined(UNIT_TEST) || defined(SITL_BUILD)
static inline void __set_BASEPRI(uint32_t basePri) {(void)basePri;}
static inline void __set_BASEPRI_MAX(uint32_t basePri) {(void)basePri;}
#endif // UNIT_TEST


#if defined(CH32H41x)

#define PFIC_ITHRESDR_ADDR    (0xE000E040)
#define PFIC_ITHRESDR         *((volatile uint32_t *)PFIC_ITHRESDR_ADDR)

__attribute__( ( always_inline ) ) static inline void __set_BASEPRI_nb(uint32_t basePri)
{
    PFIC_ITHRESDR = basePri & 0xF0;
    asm("fence");
}

__attribute__( ( always_inline ) ) static inline void __set_BASEPRI_MAX_nb(uint32_t basePri)
{
    uint32_t cur_tmp = PFIC_ITHRESDR & 0xF0;
    if(cur_tmp < (basePri & 0xF0)) PFIC_ITHRESDR = basePri & 0xF0;
    asm("fence");
}


// restore BASEPRI (called as cleanup function), with global memory barrier
static inline void __basepriRestoreMem(uint8_t *val)
{
    PFIC_ITHRESDR = (*val) & 0xF0;
    asm("fence");
}

// set BASEPRI_MAX, with global memory barrier, returns true
static inline uint8_t __basepriSetMemRetVal(uint8_t prio)
{
    // __set_BASEPRI_MAX(prio);
        
    uint32_t cur_tmp = PFIC_ITHRESDR & 0xF0;
    if(cur_tmp < (prio & 0xF0)) PFIC_ITHRESDR = prio & 0xF0;
    asm("fence");
    return 1;
}

// restore BASEPRI (called as cleanup function), no memory barrier
static inline void __basepriRestore(uint8_t *val)
{
    __set_BASEPRI_nb(*val);
}

// set BASEPRI_MAX, no memory barrier, returns true
static inline uint8_t __basepriSetRetVal(uint8_t prio)
{
    __set_BASEPRI_MAX_nb(prio);
    return 1;
}

static inline uint32_t  __get_BASEPRI(void)
{
    uint32_t val = PFIC_ITHRESDR & 0xF0;
    asm("fence");
    return val;
}


#else
// cleanup BASEPRI restore function, with global memory barrier
static inline void __basepriRestoreMem(uint8_t *val)
{
    __set_BASEPRI(*val);
}

// set BASEPRI_MAX function, with global memory barrier, returns true
static inline uint8_t __basepriSetMemRetVal(uint8_t prio)
{
    __set_BASEPRI_MAX(prio);
    return 1;
}
#endif
// The CMSIS provides the function __set_BASEPRI(priority) for changing the value of the BASEPRI register.
// The function uses the hardware convention for the ‘priority’ argument, which means that the priority must
// be shifted left by the number of unimplemented bits (8 – __NVIC_PRIO_BITS).
//
// NOTE: The priority numbering convention used in __set_BASEPRI(priority) is thus different than in the
// NVIC_SetPriority(priority) function, which expects the “priority” argument not shifted.

// Run block with elevated BASEPRI (using BASEPRI_MAX), restoring BASEPRI on exit. All exit paths are handled
// Full memory barrier is placed at start and exit of block
#ifdef UNIT_TEST
#define ATOMIC_BLOCK(prio) {}
#else
#define ATOMIC_BLOCK(prio) for ( uint8_t __basepri_save __attribute__((__cleanup__(__basepriRestoreMem))) = __get_BASEPRI(), \
                                     __ToDo = __basepriSetMemRetVal((prio) << (8U - __NVIC_PRIO_BITS)); __ToDo ; __ToDo = 0 )

#endif // UNIT_TEST
