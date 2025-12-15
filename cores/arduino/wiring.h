/*
  Copyright (c) 2011 Arduino.  All right reserved.
  Copyright (c) 2013 by Paul Stoffregen <paul@pjrc.com> (delayMicroseconds)

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

#ifndef _WIRING_H_
#define _WIRING_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "Arduino.h"

#include "avr/dtostrf.h"



#include <stdarg.h>
#include "clock.h"
#include "dwt.h"
#include <sys/time.h> // for struct timeval

/* wirinig_analog*/
#ifdef __cplusplus
extern "C" {
#endif
/*
 * \brief Set the resolution of analogRead return values. Default is 10 bits (range from 0 to 1023).
 *
 * \param res
 */
extern void analogReadResolution(int res);
/*
 * \brief Set the resolution of analogWrite parameters. Default is 8 bits (range from 0 to 255).
 *
 * \param res
 */
extern void analogWriteResolution(int res);
/*
 * \brief Set the frequency of analogWrite. Default is PWM_FREQUENCY (1000) in Hertz.
 *
 * \param freq
 */
extern void analogWriteFrequency(uint32_t freq);
extern void analogOutputInit(void) ;

/* wiring_constants */
#define DEFAULT 1
#define EXTERNAL 0

#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
#ifndef cbi
#define cbi(reg, bitmask) *reg &= ~bitmask
#endif
#ifndef sbi
#define sbi(reg, bitmask) *reg |= bitmask
#endif

typedef bool boolean __attribute__((deprecated));

/* wiring_digital */
/**
 * \brief Toggle the value from a specified digital pin.
 *
 * \param ulPin The number of the digital pin you want to toggle (int)
 */
extern void digitalToggle(pin_size_t pinNumber) ;

#ifdef __cplusplus
}
#endif

#include <board.h>

#ifdef __cplusplus
  #include "HardwareTimer.h"
  #include "WSerial.h"
#endif // __cplusplus


#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

#endif /* _WIRING_H_ */
