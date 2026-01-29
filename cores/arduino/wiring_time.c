/*
  Copyright (c) 2011 Arduino.  All right reserved.

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

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned long millis(void)
{
  // ToDo: ensure no interrupts
  return getCurrentMillis();
}

// Interrupt-compatible version of micros
unsigned long micros(void)
{
  return getCurrentMicros();
}

void delay(unsigned long ms)
{
  if (ms != 0) {
    unsigned long start = getCurrentMillis();
    do {
      yield();
    } while (getCurrentMillis() - start < ms);
  }
}

/**
 * \brief Pauses the program for the amount of time (in microseconds) specified as parameter.
 *
 * \param us the number of microseconds to pause (unsigned int)
 */

void delayMicroseconds(unsigned int us)
{
#if defined(DWT_BASE) && !defined(DWT_DELAY_DISABLED)
  int32_t start  = dwt_getCycles();
  int32_t cycles = us * (SystemCoreClock / 1000000);

  while ((int32_t)dwt_getCycles() - start < cycles);
#else
  __IO uint32_t currentTicks = SysTick->VAL;
  /* Number of ticks per millisecond */
  const uint32_t tickPerMs = SysTick->LOAD + 1;
  /* Number of ticks to count */
  const uint32_t nbTicks = ((us - ((us > 0) ? 1 : 0)) * tickPerMs) / 1000;
  /* Number of elapsed ticks */
  uint32_t elapsedTicks = 0;
  __IO uint32_t oldTicks = currentTicks;
  do {
    currentTicks = SysTick->VAL;
    elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks :
                    oldTicks - currentTicks;
    oldTicks = currentTicks;
  } while (nbTicks > elapsedTicks);
#endif
}

/**
 * \brief gives the number of seconds and microseconds since the Epoch
 *
 *        based on millisecond since last power on.
 *
 * \note  The function is declared as weak  to be overwritten  in case of other
 *        implementations in user file (using RTC values for example).
 *
 * \param tv argument is a struct timeval
 * \param tz argument is a struct timezone (unused)
 *
 * \return 0
 */
int __attribute__((weak)) _gettimeofday(struct timeval *tv, void *tz)
{
  (void)tz;
  tv->tv_sec = getCurrentMillis() / 1000;
  tv->tv_usec = getCurrentMicros() - (tv->tv_sec * 1000000);  // get remaining microseconds
  return 0;
}

#ifdef __cplusplus
}
#endif
