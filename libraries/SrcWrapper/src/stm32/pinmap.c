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

typedef struct {
  PinName pin;
  uint32_t LL_AnalogSwitch;
} PinAnalogSwitch;

#if defined(STM32H7xx)
#define DUALPAD_ANALOG_SWITCH
const PinAnalogSwitch PinMapAnalogSwitch[] = {
  {PA_0,     LL_SYSCFG_ANALOG_SWITCH_PA0},
  {PA_1,     LL_SYSCFG_ANALOG_SWITCH_PA1},
  {PC_2,     LL_SYSCFG_ANALOG_SWITCH_PC2},
  {PC_3,     LL_SYSCFG_ANALOG_SWITCH_PC3},
  {NC,   0}
};
#else
/**
 * Even if MP1 support some dual pad (analog switch), we don't consider it
 * because its behavior is different from H7 and almost useless.
 * Switches remains open all the time. No need to configure it */
#undef DUALPAD_ANALOG_SWITCH
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

#if defined(DUALPAD_ANALOG_SWITCH)
/**
 * Configure Analog dualpad switch if necessary
 * LL_AnalogSwitch: LL define to be used to configure Analog switch
 */
static void configure_dualpad_switch(PinName pin, int function, uint32_t LL_AnalogSwitch)
{
  if (LL_AnalogSwitch == 0) {
    return ;
  }

  if (((function & STM_MODE_ANALOG) != STM_MODE_ANALOG)
      && ((pin & PDUAL) == PDUAL)) {
    /**
      * We don't configure an analog function but the pin is an analog pad
      * Pxy_C. In this cases Analog switch should be closed
      */
    LL_SYSCFG_CloseAnalogSwitch(LL_AnalogSwitch);
    return ;
  } else {
    /**
      * Either we configure an analog function,
      * or it is not an analog function but it is not an analog pad Pxy_C.
      * In both cases Analog switch should be opened
      * Note: direct ADC is restricted to Pxy_C,  pin only
      */
    LL_SYSCFG_OpenAnalogSwitch(LL_AnalogSwitch);
    return ;
  }
}

/**
 * In case of dual pad, determine whether gpio needs to be configured
 * pLL_AnalogSwitch: pointer used to return LL define to be used to configure
 * Analog switch
 * return: true when gpio must be configured
 */
static bool is_dualpad_switch_gpio_configurable(PinName pin, int function, uint32_t *pLL_AnalogSwitch)
{
  PinAnalogSwitch *AnalogSwitch = (PinAnalogSwitch *) PinMapAnalogSwitch;

  /* Read through PinMapAnalogSwitch array */
  while (AnalogSwitch->pin != NC) {
    /* Check whether pin is or is associated to dualpad Analog Input */
    if ((AnalogSwitch->pin | PDUAL)  == (pin | PDUAL)) {
      *pLL_AnalogSwitch = AnalogSwitch->LL_AnalogSwitch;
      if (((function & STM_MODE_ANALOG) == STM_MODE_ANALOG)
          && ((pin & PDUAL) == PDUAL)) {
        /**
         * We configure an analog function and the pin is an analog pad Pxy_C
         * In this case gpio configuration must be skipped
         */
        return false;
      } else {
        return true;
      }
    }
    AnalogSwitch ++;
  }
  *pLL_AnalogSwitch = 0;
  return true;
}
#endif /* DUALPAD_ANALOG_SWITCH */

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
  /* Get the pin information */
  uint32_t mode  = STM_PIN_FUNCTION(function);
  uint32_t afnum = STM_PIN_AFNUM(function);
  uint32_t port = STM_PORT(pin);
  uint32_t ll_pin  = STM_LL_GPIO_PIN(pin);
  uint32_t ll_mode = 0;

  if (pin == (PinName)NC) {
    Error_Handler();
  }

  /* Handle pin remap if any */
#if defined(LL_SYSCFG_PIN_RMP_PA11) && defined(LL_SYSCFG_PIN_RMP_PA12) || defined(SYSCFG_CFGR1_PA11_PA12_RMP)
  switch (pin & PNAME_MASK) {
#if defined(SYSCFG_CFGR1_PA11_PA12_RMP)
    /* Disable PIN pair PA11/12 mapped instead of PA9/10 */
    case PA_9:
    case PA_10:
      LL_SYSCFG_DisablePinRemap();
      break;
    /* Enable PIN pair PA11/12 mapped instead of PA9/10 */
    case PA_11:
    case PA_12:
      if ((pin & PREMAP) == PREMAP) {
        LL_SYSCFG_EnablePinRemap();
      }
      break;
#else
    case PA_9:
      if ((pin & PREMAP) == PREMAP) {
        LL_SYSCFG_EnablePinRemap(LL_SYSCFG_PIN_RMP_PA11);
      }
      break;
    case PA_10:
      if ((pin & PREMAP) == PREMAP) {
        LL_SYSCFG_EnablePinRemap(LL_SYSCFG_PIN_RMP_PA12);
      }
      break;
    case PA_11:
      LL_SYSCFG_DisablePinRemap(LL_SYSCFG_PIN_RMP_PA11);
      break;
    case PA_12:
      LL_SYSCFG_DisablePinRemap(LL_SYSCFG_PIN_RMP_PA12);
      break;
#endif
    default:
      break;
  }
#endif

#if defined(DUALPAD_ANALOG_SWITCH)
  uint32_t LL_AnalogSwitch = 0;
  if (!is_dualpad_switch_gpio_configurable(pin, function, &LL_AnalogSwitch)) {
    /* Skip gpio configuration */
    configure_dualpad_switch(pin, function, LL_AnalogSwitch);
    return;
  }
#endif /* DUALPAD_ANALOG_SWITCH */

  /* Enable GPIO clock */
  GPIO_TypeDef *gpio = set_GPIO_Port_Clock(port);

  hsem_lock(CFG_HW_GPIO_SEMID, HSEM_LOCK_DEFAULT_RETRY);

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
      if (afnum != STM_PIN_AFNUM_MASK) {
        pin_SetAFPin(gpio, pin, afnum);
      }
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

#if defined(DUALPAD_ANALOG_SWITCH)
  configure_dualpad_switch(pin, function, LL_AnalogSwitch);
#endif /* DUALPAD_ANALOG_SWITCH */

  pin_DisconnectDebug(pin);

  hsem_unlock(CFG_HW_GPIO_SEMID);
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

  // mismatch error case
  return NP;
}
