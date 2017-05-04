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
#include "wiring_private.h"

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * ATTENTION:
 * This function performs better with short pulses in noInterrupt() context
 */

#ifdef __cplusplus
 extern "C" {
#endif


uint32_t pulseIn( uint32_t pin, uint32_t state, uint32_t timeout )
{
  uint32_t startMicros = micros();
  uint32_t start_level = (uint32_t)digitalRead(pin);
  uint32_t current_level = start_level;

  while(current_level == start_level) {
    if (micros() - startMicros > timeout) {
      return 0;
    }
    current_level = (uint32_t)digitalRead(pin);
  }

  while(current_level != state) {
    if (micros() - startMicros > timeout) {
      return 0;
    }
    current_level = (uint32_t)digitalRead(pin);
  }

  //lets start measuring the pulse time now
  startMicros = micros();

  while(current_level == state) {
    if (micros() - startMicros > timeout) {
      return 0;
    }
    current_level = (uint32_t)digitalRead(pin);
  }

  return (micros() - startMicros);
}

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * ATTENTION:
 * this function relies on micros() so cannot be used in noInterrupt() context
 */
uint32_t pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
  return pulseIn(pin, state, timeout);
}

#ifdef __cplusplus
}
#endif
