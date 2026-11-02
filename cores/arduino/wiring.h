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

/**
 * @file wiring.h
 * @brief STM32 wiring extensions: analog resolution and frequency,
 * digitalToggle(), noTone(), attachInterrupt() and timing helper macros.
 */

#ifndef _WIRING_H_
#define _WIRING_H_

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h> // for struct timeval

#include "api/Common.h"
#include "api/deprecated-avr-comp/avr/dtostrf.h"
#include "api/itoa.h"
#include "clock.h"
#include "dwt.h"
#include "interrupt.h"

/* wiring_analog */
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Set the resolution of analogRead return values.
 * Default is 10 bits (range from 0 to 1023).
 *
 * @note The ADC is configured with the closest supported hardware resolution
 * (capped to the maximum of the ADC) and the result is scaled to the requested
 * resolution. Values outside the range 1 to 32 call Error_Handler().
 *
 * @see analogRead(), analogWriteResolution()
 *
 * @param res Number of bits of the resolution, from 1 to 32.
 */
extern void analogReadResolution(int res);
/**
 * @brief Set the resolution of analogWrite parameters.
 * Default is 8 bits (range from 0 to 255).
 *
 * @note The PWM hardware resolution is capped to 16 bits and the value is
 * scaled accordingly. Values outside the range 1 to 32 call Error_Handler().
 *
 * @see analogWrite(), analogReadResolution(), analogWriteFrequency()
 *
 * @param res Number of bits of the resolution, from 1 to 32.
 */
extern void analogWriteResolution(int res);
/**
 * @brief Set the frequency of analogWrite.
 * Default is PWM_FREQUENCY (1000) in Hertz.
 *
 * @see analogWrite(), analogWriteResolution()
 *
 * @param freq PWM frequency in Hertz.
 */
extern void analogWriteFrequency(uint32_t freq);

/* wiring_constants */
/** Default analog reference, kept for AVR compatibility. */
#define DEFAULT 1
/** External analog reference, kept for AVR compatibility. */
#define EXTERNAL 0

/** Enable all interrupts. */
#define interrupts() __enable_irq()
/** Disable all interrupts. */
#define noInterrupts() __disable_irq()

#ifndef _BV
/** Value of a bit mask with only the given bit set. */
#define _BV(bit) (1 << (bit))
#endif
#ifndef cbi
/** Clear the bits of bitmask in the register pointed to by reg. */
#define cbi(reg, bitmask) *reg &= ~bitmask
#endif
#ifndef sbi
/** Set the bits of bitmask in the register pointed to by reg. */
#define sbi(reg, bitmask) *reg |= bitmask
#endif

/* wiring_digital */
/**
 * @brief Toggle the value from a specified digital pin.
 *
 * @param pinNumber The number of the digital pin you want to toggle.
 */
extern void digitalToggle(pin_size_t pinNumber);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
  /**
  * @brief Stop tone generation on pin.
  *
  * @param _pin The pin on which to stop tone generation.
  * @param destruct If true, the tone timer is deinitialized and deleted.
  * If false, it is only paused.
  */
  extern void noTone(uint8_t _pin, bool destruct);
  #if !defined(HAL_EXTI_MODULE_DISABLED)
    /**
    * @brief Attach a callback function to an external interrupt on a pin.
    *
    * @note LOW and HIGH level triggers are only available on series supporting
    * level interrupts, otherwise they fall back to FALLING and RISING respectively.
    *
    * @param pin The pin to attach the interrupt to.
    * @param callback Function called when the interrupt fires. It takes no arguments.
    * @param mode Trigger mode: CHANGE, RISING, FALLING, LOW or HIGH.
    */
    extern void attachInterrupt(pin_size_t pin, callback_function_t callback, PinStatus mode);
  #endif
#endif

#include <board.h>

#ifdef __cplusplus
  #include "HardwareTimer.h"
  #include "WSerial.h"
#endif // __cplusplus


/** Number of CPU clock cycles per microsecond. */
#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
/** Convert a number of CPU clock cycles to microseconds. */
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
/** Convert a number of microseconds to CPU clock cycles. */
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

#endif /* _WIRING_H_ */
