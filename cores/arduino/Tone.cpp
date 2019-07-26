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

#if defined(HAL_TIM_MODULE_ENABLED) && defined(TIMER_TONE)

#define MAX_FREQ  65535

typedef struct {
  PinName pin;
  int32_t count;
  uint8_t state;
} timerPinInfo_t;

static void timerTonePinInit(PinName p, uint32_t frequency, uint32_t duration);
static void tonePeriodElapsedCallback(HardwareTimer *HT);
static timerPinInfo_t TimerTone_pinInfo;

static HardwareTimer *TimerTone = NULL;

PinName g_lastPin = NC;

/**
  * @brief  Tone Period elapsed callback in non-blocking mode
  * @param  htim : timer handle
  * @retval None
  */
static void tonePeriodElapsedCallback(HardwareTimer *HT)
{
  UNUSED(HT);
  GPIO_TypeDef *port = get_GPIO_Port(STM_PORT(TimerTone_pinInfo.pin));

  if (port != NULL) {
    if (TimerTone_pinInfo.count != 0) {
      if (TimerTone_pinInfo.count > 0) {
        TimerTone_pinInfo.count--;
      }
      TimerTone_pinInfo.state = (TimerTone_pinInfo.state == 0) ? 1 : 0;
      digital_io_write(port, STM_LL_GPIO_PIN(TimerTone_pinInfo.pin), TimerTone_pinInfo.state);
    } else {
      digital_io_write(port, STM_LL_GPIO_PIN(TimerTone_pinInfo.pin), 0);
    }
  }
}


/**
  * @brief  This function will reset the tone timer
  * @param  port : pointer to port
  * @param  pin : pin number to toggle
  * @retval None
  */
static void timerTonePinDeinit()
{
  TimerTone->timerHandleDeinit();
  pin_function(TimerTone_pinInfo.pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
}

static void timerTonePinInit(PinName p, uint32_t frequency, uint32_t duration)
{
  uint32_t timFreq = 2 * frequency;

  TimerTone_pinInfo.pin = p;

  if (frequency > MAX_FREQ) {
    return;
  }

  TimerTone_pinInfo.state = 0;

  if (frequency == 0) {
    timerTonePinDeinit();
    return;
  }

  //Calculate the toggle count
  if (duration > 0) {
    TimerTone_pinInfo.count = ((timFreq * duration) / 1000);
  } else {
    TimerTone_pinInfo.count = -1;
  }

  pin_function(TimerTone_pinInfo.pin, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL, 0));

  TimerTone->setMode(1, TIMER_OUTPUT_COMPARE, NC);
  TimerTone->setOverflow(timFreq, HERTZ_FORMAT);
  TimerTone->attachInterrupt(tonePeriodElapsedCallback);
  TimerTone->resume();
}

// frequency (in hertz) and duration (in milliseconds).
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
  PinName p = digitalPinToPinName(_pin);

  if (TimerTone == NULL) {
    TimerTone = new HardwareTimer(TIMER_TONE);
  }

  if (p != NC) {
    if ((g_lastPin == NC) || (g_lastPin == p)) {

      timerTonePinInit(p, frequency, duration);
      g_lastPin = p;
    }
  }
}

void noTone(uint8_t _pin, bool destruct)
{
  PinName p = digitalPinToPinName(_pin);
  if (p != NC) {
    timerTonePinDeinit();
    g_lastPin = NC;
  }
  if (destruct) {
    if (TimerTone != NULL) {
      delete (TimerTone);
      TimerTone = NULL;
    }
  }
}
#else

#warning "TIMER_TONE or HAL_TIM_MODULE_ENABLED not defined"
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
  UNUSED(_pin);
  UNUSED(frequency);
  UNUSED(duration);
}

void noTone(uint8_t _pin)
{
  UNUSED(_pin);
}

#endif /* HAL_TIM_MODULE_ENABLED && TIMER_TONE */
