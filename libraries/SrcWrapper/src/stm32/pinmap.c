/*
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//Based on mbed-os/hal/mbed_pinmap_common.c
#include "pinmap.h"
#include "pinconfig.h"
#include "stm32yyxx_ll_gpio.h"
#include "stm32yyxx_ll_system.h"

#if defined(STM32MP1xx)
  #include "lock_resource.h"
#endif

/* Map STM_PIN to LL */
const uint32_t pin_map_ll[16] = {
  LL_GPIO_PIN_0,
  LL_GPIO_PIN_1,
  LL_GPIO_PIN_2,
  LL_GPIO_PIN_3,
  LL_GPIO_PIN_4,
  LL_GPIO_PIN_5,
  LL_GPIO_PIN_6,
  LL_GPIO_PIN_7,
  LL_GPIO_PIN_8,
  LL_GPIO_PIN_9,
  LL_GPIO_PIN_10,
  LL_GPIO_PIN_11,
  LL_GPIO_PIN_12,
  LL_GPIO_PIN_13,
  LL_GPIO_PIN_14,
  LL_GPIO_PIN_15
};

bool pin_in_pinmap(PinName pin, const PinMap *map)
{
  if (pin != (PinName)NC) {
    while (map->pin != NC) {
      if (map->pin == pin) {
        return true;
      }
      map++;
    }
  }
  return false;
}

/**
 * Configure pin (mode, speed, output type and pull-up/pull-down)
 */
void pin_function(PinName pin, int function)
{
  /* Get the pin informations */
  uint32_t mode  = STM_PIN_FUNCTION(function);
  uint32_t afnum = STM_PIN_AFNUM(function);
  uint32_t port = STM_PORT(pin);
  uint32_t ll_pin  = STM_LL_GPIO_PIN(pin);
  uint32_t ll_mode = 0;

  if (pin == (PinName)NC) {
    Error_Handler();
  }

  /* Handle pin remap if any */
#if defined(LL_SYSCFG_PIN_RMP_PA11) && defined(LL_SYSCFG_PIN_RMP_PA12)
  if ((pin >= PA_9) && (pin <= PA_12)) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    switch ((int)pin) {
      case PA_9:
        LL_SYSCFG_EnablePinRemap(LL_SYSCFG_PIN_RMP_PA11);
        break;
      case PA_11:
        LL_SYSCFG_DisablePinRemap(LL_SYSCFG_PIN_RMP_PA11);
        break;
      case PA_10:
        LL_SYSCFG_EnablePinRemap(LL_SYSCFG_PIN_RMP_PA12);
        break;
      case PA_12:
        LL_SYSCFG_DisablePinRemap(LL_SYSCFG_PIN_RMP_PA12);
        break;
      default:
        break;
    }
  }
#endif

  /* Enable GPIO clock */
  GPIO_TypeDef *gpio = set_GPIO_Port_Clock(port);

#if defined(STM32MP1xx)
  PERIPH_LOCK(gpio);
#endif
  /*  Set default speed to high.
   *  For most families there are dedicated registers so it is
   *  not so important, register can be set at any time.
   *  But for families like F1, speed only applies to output.
   */
#if defined (STM32F1xx)
  if (mode == STM_PIN_OUTPUT) {
#endif
#ifdef LL_GPIO_SPEED_FREQ_VERY_HIGH
    LL_GPIO_SetPinSpeed(gpio, ll_pin, LL_GPIO_SPEED_FREQ_VERY_HIGH);
#else
    LL_GPIO_SetPinSpeed(gpio, ll_pin, LL_GPIO_SPEED_FREQ_HIGH);
#endif
#if defined (STM32F1xx)
  }
#endif

  switch (mode) {
    case STM_PIN_INPUT:
      ll_mode = LL_GPIO_MODE_INPUT;
#if defined(STM32F1xx)
      // on F1 family, input mode may be associated with an alternate function
      pin_SetAFPin(gpio, pin, afnum);
#endif
      break;
    case STM_PIN_OUTPUT:
      ll_mode = LL_GPIO_MODE_OUTPUT;
      break;
    case STM_PIN_ALTERNATE:
      ll_mode = LL_GPIO_MODE_ALTERNATE;
      /* In case of ALT function, also set the afnum */
      pin_SetAFPin(gpio, pin, afnum);
      break;
    case STM_PIN_ANALOG:
      ll_mode = LL_GPIO_MODE_ANALOG;
      break;
    default:
      Error_Handler();
      break;
  }
  LL_GPIO_SetPinMode(gpio, ll_pin, ll_mode);

#if defined(GPIO_ASCR_ASC0)
  /* For families where Analog Control ASC0 register is present */
  if (STM_PIN_ANALOG_CONTROL(function)) {
    LL_GPIO_EnablePinAnalogControl(gpio, ll_pin);
  } else {
    LL_GPIO_DisablePinAnalogControl(gpio, ll_pin);
  }
#endif

  if ((mode == STM_PIN_OUTPUT) || (mode == STM_PIN_ALTERNATE)) {
    if (STM_PIN_OD(function)) {
      LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_OPENDRAIN);
    } else {
      LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_PUSHPULL);
    }
  }

  pin_PullConfig(gpio, ll_pin, STM_PIN_PUPD(function));

  pin_DisconnectDebug(pin);

#if defined(STM32MP1xx)
  PERIPH_UNLOCK(gpio);
#endif
}

void pinmap_pinout(PinName pin, const PinMap *map)
{
  if (pin == NC) {
    return;
  }

  while (map->pin != NC) {
    if (map->pin == pin) {
      pin_function(pin, map->function);
      return;
    }
    map++;
  }
  Error_Handler();
}

void *pinmap_find_peripheral(PinName pin, const PinMap *map)
{
  while (map->pin != NC) {
    if (map->pin == pin) {
      return map->peripheral;
    }
    map++;
  }
  return NP;
}

void *pinmap_peripheral(PinName pin, const PinMap *map)
{
  void *peripheral = NP;

  if (pin != (PinName)NC) {
    peripheral = pinmap_find_peripheral(pin, map);
  }
  return peripheral;
}

PinName pinmap_find_pin(void *peripheral, const PinMap *map)
{
  while (map->peripheral != NP) {
    if (map->peripheral == peripheral) {
      return map->pin;
    }
    map++;
  }
  return NC;
}

PinName pinmap_pin(void *peripheral, const PinMap *map)
{
  PinName pin = NC;

  if (peripheral != NP) {
    pin = pinmap_find_pin(peripheral, map);
  }
  return pin;
}

uint32_t pinmap_find_function(PinName pin, const PinMap *map)
{
  while (map->pin != NC) {
    if (map->pin == pin) {
      return map->function;
    }
    map++;
  }
  return (uint32_t)NC;
}

uint32_t pinmap_function(PinName pin, const PinMap *map)
{
  uint32_t function = (uint32_t)NC;

  if (pin != (PinName)NC) {
    function = pinmap_find_function(pin, map);
  }
  return function;
}

// Merge peripherals
void *pinmap_merge_peripheral(void *a, void *b)
{
  // both are the same (inc both NP)
  if (a == b) {
    return a;
  }

  // one (or both) is not set
  if (a == NP) {
    return b;
  }
  if (b == NP) {
    return a;
  }

  // mis-match error case
  return NP;
}
