/* Tone.cpp

  A Tone Generator Library

  Written by Brett Hagman

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "HardwareTimer.h"

#if defined(TIMER_TONE) && !defined(HAL_TIM_MODULE_ONLY) && \
    (defined(HAL_TIM_MODULE_ENABLED) || (defined(USE_HAL_TIM_MODULE) && (USE_HAL_TIM_MODULE == 1)))

#define MAX_FREQ  65535

typedef struct {
  PinName pin;
  int32_t count;
} timerPinInfo_t;

static void timerTonePinInit(PinName p, uint32_t frequency, uint32_t duration);
static void tonePeriodElapsedCallback();
static timerPinInfo_t TimerTone_pinInfo = {NC, 0};
static HardwareTimer *TimerTone = NULL;

/**
 * @brief Tone Period elapsed callback in non-blocking mode.
 */
static void tonePeriodElapsedCallback()
{
  GPIO_TypeDef *port = get_GPIO_Port(STM_PORT(TimerTone_pinInfo.pin));

  if (port != NULL) {
    if (TimerTone_pinInfo.count != 0) {
      if (TimerTone_pinInfo.count > 0) {
        TimerTone_pinInfo.count--;
      }
      digital_io_toggle(port, STM_LL_GPIO_PIN(TimerTone_pinInfo.pin));
    } else {
      digital_io_write(port, STM_LL_GPIO_PIN(TimerTone_pinInfo.pin), 0);
    }
  }
}

/**
 * @brief Reset the tone timer and release the tone pin.
 */
static void timerTonePinDeinit()
{
  if (TimerTone != NULL) {
    TimerTone->timerHandleDeinit();
  }
  if (TimerTone_pinInfo.pin != NC) {
    pin_function(TimerTone_pinInfo.pin, STM_PIN_DATA(STM_MODE_INPUT, LL_GPIO_PULL_NO, 0));
    TimerTone_pinInfo.pin = NC;
  }
}

/**
 * @brief Configure the tone timer and output pin for a given frequency and duration.
 *
 * @param p Pin to output the tone on.
 * @param frequency Tone frequency in Hertz. 0 pauses the timer, values above MAX_FREQ are ignored.
 * @param duration Tone duration in milliseconds. 0 means the tone plays until noTone() is called.
 */
static void timerTonePinInit(PinName p, uint32_t frequency, uint32_t duration)
{
  uint32_t timFreq = 2 * frequency;

  if (frequency <= MAX_FREQ) {
    if (frequency == 0) {
      if (TimerTone != NULL) {
        TimerTone->pause();
      }
    } else {
      TimerTone_pinInfo.pin = p;

      //Calculate the toggle count
      if (duration > 0) {
        TimerTone_pinInfo.count = ((timFreq * duration) / 1000);
      } else {
        TimerTone_pinInfo.count = -1;
      }

      pin_function(TimerTone_pinInfo.pin, STM_PIN_DATA(STM_MODE_OUTPUT_PP, LL_GPIO_PULL_NO, 0));

      TimerTone->setOverflow(timFreq, HERTZ_FORMAT);
      TimerTone->attachInterrupt(tonePeriodElapsedCallback);
      TimerTone->resume();
    }
  }
}

/**
 * @brief Generate a square wave of the given frequency on a pin.
 *
 * @param _pin Pin to output the tone on.
 * @param frequency Frequency of the tone in Hertz.
 * @param duration Duration of the tone in milliseconds. 0 plays the tone until noTone() is called.
 */
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
  PinName p = digitalPinToPinName(_pin);

  if (TimerTone == NULL) {
    TimerTone = new HardwareTimer(TIMER_TONE);
  }

  if (p != NC) {
    if ((TimerTone_pinInfo.pin == NC) || (TimerTone_pinInfo.pin == p)) {
      timerTonePinInit(p, frequency, duration);
    }
  }
}


/**
 * @brief Stop tone generation on a pin, keeping the tone timer allocated.
 *
 * @param _pin Pin on which to stop tone generation.
 */
void noTone(uint8_t _pin)
{
  noTone(_pin, false);
}

void noTone(uint8_t _pin, bool destruct)
{
  PinName p = digitalPinToPinName(_pin);
  if ((p != NC) && (TimerTone_pinInfo.pin == p) && (TimerTone != NULL)) {
    if (destruct) {
      timerTonePinDeinit();
      delete (TimerTone);
      TimerTone = NULL;
    } else {
      TimerTone->pause();
    }
  }
}
#else
#warning "Tone library disabled"
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
  (void)_pin;
  (void)frequency;
  (void)duration;
}

void noTone(uint8_t _pin)
{
  (void)_pin;
}

void noTone(uint8_t _pin, bool destruct)
{
  (void)_pin;
  (void)destruct;
}
#endif /* HAL_TIM_MODULE_ENABLED && TIMER_TONE && !HAL_TIM_MODULE_ONLY*/
