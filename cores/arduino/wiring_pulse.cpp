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

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * ATTENTION:
 * This function relies on micros() so cannot be used in noInterrupt() context
 */
uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout)
{
  // Cache the port and bit of the pin in order to speed up the
  // pulse width measuring loop and achieve finer resolution.
  // Calling digitalRead() instead yields much coarser resolution.
  uint32_t bit = digitalPinToBitMask(pin);
  __IO uint32_t *portIn = portInputRegister(digitalPinToPort(pin));
  uint32_t stateMask = (state ? bit : 0);
  uint32_t startMicros = micros();

  // wait for any previous pulse to end
  while ((*portIn & bit) == stateMask) {
    if (micros() - startMicros > timeout) {
      return 0;
    }
  }

  // wait for the pulse to start
  while ((*portIn & bit) != stateMask) {
    if (micros() - startMicros > timeout) {
      return 0;
    }
  }

  uint32_t start = micros();
  // wait for the pulse to stop
  while ((*portIn & bit) == stateMask) {
    if (micros() - startMicros > timeout) {
      return 0;
    }
  }
  return (micros() - start);
}

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * ATTENTION:
 * This function relies on micros() so cannot be used in noInterrupt() context
 */
uint32_t pulseInLong(uint32_t pin, uint32_t state, uint32_t timeout)
{
  return pulseIn(pin, state, timeout);
}
