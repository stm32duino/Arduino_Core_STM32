/*
  Copyright (c) 2011 Arduino.  All right reserved.
  Copyright (c) 2013 by Paul Stoffregen <paul@pjrc.com> (delayMicroseconds)
  Copyright (c) 2018 MCCI Corporation (correct delayMicroseconds)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_TIME_H_
#define _WIRING_TIME_H_

#include "clock.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \brief Returns the number of milliseconds since the Arduino board began running the current program.
 *
 * This number will overflow (go back to zero), after approximately 50 days.
 *
 * \return Number of milliseconds since the program started (uint32_t)
 */
extern uint32_t millis( void ) ;

/**
 * \brief Returns the number of microseconds since the Arduino board began running the current program.
 *
 * This number will overflow (go back to zero), after approximately 70 minutes. On 16 MHz Arduino boards
 * (e.g. Duemilanove and Nano), this function has a resolution of four microseconds (i.e. the value returned is
 * always a multiple of four). On 8 MHz Arduino boards (e.g. the LilyPad), this function has a resolution
 * of eight microseconds.
 *
 * \note There are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.
 */
extern uint32_t micros( void ) ;

/**
 * \brief Pauses the program for the amount of time (in miliseconds) specified as parameter.
 * (There are 1000 milliseconds in a second.)
 *
 * \param dwMs the number of milliseconds to pause (uint32_t)
 */
extern void delay( uint32_t dwMs ) ;

/**
 * \brief Pauses the program for the amount of time (in microseconds) specified as parameter.
 *
 * \param dwUs the number of microseconds to pause (uint32_t)
 *
 * \note This implementation does not call GetMicroseconds(), thereby avoiding
 * time- and power-wasting multiplies at each step of the delay. It also avoids
 * unnecesary register reads. Instead it does one multiply/divide to convert
 * us to ticks, based on the current clock setting, and waits until that many
 * ticks are observed.
 * See https://github.com/mcci-catena/Arduino_Core_STM32/issues/8 for more.
 */
static inline void delayMicroseconds(uint32_t) __attribute__((always_inline, unused));
static inline void delayMicroseconds(uint32_t usec)
{
  // if the delay is huge, just delay by milliseconds. Assume
  // that the compiler will optimize this out for small constant
  // delays, and that it will optimize away the other branch.
  // Chose the limit so that the multiply for `ticks` won't
  // overflow.
  if (usec >= 10*1000)
    {
       delay((usec + 1000 - 1) / 1000);
       return;
    }

  // fetch initial time as a tick count.
  const uint32_t now = SysTick->VAL;

  // fetch max count, which is ticks/millisecond.
  const uint32_t tickmax = SysTick->LOAD + 1;

  // convert usec to an equivalent numer of ticks
  // there are tickmax/1000 ticks per microsecond.
  // so the following is usec * (tickmax/1000), rounded
  // and done in fixed point without loss of precision.
  const uint32_t ticks = (usec * tickmax + 500) / 1000;

  // val and lastval track tick counts.
  uint32_t val, lastVal;

  // dt tracks to the elapsed number of ticks.
  uint32_t dt;

  // loop until we've observed at least `ticks`
  // clicks of SysTick. NB: SysTick is a down-counter.
  for (dt = 0, lastVal = now;
       dt < ticks;
       lastVal = val)
  {
    val = SysTick->VAL;
    if (val >= lastVal)
    {
      // count wrapped from 0 to tickmax,
      // so add the wrap-around count.
      dt += tickmax + lastVal - val;
    }
    else
    {
      dt += lastVal - val;
    }
  }
}

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_TIME_H_ */
