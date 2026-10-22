
/** \addtogroup hal */
/** @{*/
/* mbed Microcontroller Library
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
#ifndef _PINMAP_H
#define _PINMAP_H

#include "PinNames.h"
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint32_t pin_map_ll[16];

#ifndef GPIO_AF_NONE
#define GPIO_AF_NONE 0
#endif
#define STM_LL_GPIO_PIN(X) (pin_map_ll[STM_PIN(X)])

// No peripheral
#define NP       0U

typedef struct {
  PinName pin;
  void *peripheral;
  int function;
} PinMap;

/**
  * @brief Check whether a pin is present in a pinmap.
  * @param pin Pin name to look for.
  * @param map PinMap array, terminated by an entry with pin NC.
  * @return true if the pin is found in the map, false otherwise.
  */
bool pin_in_pinmap(PinName pin, const PinMap *map);

/**
  * @brief Configure a pin: mode, speed, output type, pull-up/pull-down and AF.
  * @param pin Pin name.
  * @param function Pin function, encoded with the STM_PIN_* macros.
  * Calls Error_Handler if the pin is NC or the mode is unknown.
  */
void pin_function(PinName pin, int function);

/**
  * @brief Get the pin name of a PinMap entry.
  * @param map PinMap entry.
  * @return Pin name stored in the entry.
  */
static inline PinName pin_pinName(const PinMap *map)
{
  return map->pin;
}

/**
  * @brief Configure a pin from a pinmap entry matching the pin.
  * @param pin Pin name.
  * @param map PinMap array, terminated by an entry with pin NC.
  * Calls Error_Handler if the pin is not found in the map.
  */
void  pinmap_pinout(PinName pin, const PinMap *map);

/**
  * @brief Find the peripheral associated with a pin.
  * @param pin Pin name.
  * @param map PinMap array, terminated by an entry with pin NC.
  * @return Peripheral pointer, or NP if not found.
  */
void *pinmap_find_peripheral(PinName pin, const PinMap *map);

/**
  * @brief Find the peripheral associated with a pin, ignoring NC pins.
  * @param pin Pin name.
  * @param map PinMap array, terminated by an entry with pin NC.
  * @return Peripheral pointer, or NP if the pin is NC or not found.
  */
void *pinmap_peripheral(PinName pin, const PinMap *map);

/**
  * @brief Find the pin associated with a peripheral.
  * @param peripheral Peripheral pointer.
  * @param map PinMap array, terminated by an entry with peripheral NP.
  * @return Pin name, or NC if not found.
  */
PinName pinmap_find_pin(void *peripheral, const PinMap *map);

/**
  * @brief Find the pin associated with a peripheral, ignoring NP peripherals.
  * @param peripheral Peripheral pointer.
  * @param map PinMap array, terminated by an entry with peripheral NP.
  * @return Pin name, or NC if the peripheral is NP or not found.
  */
PinName pinmap_pin(void *peripheral, const PinMap *map);

/**
  * @brief Find the function associated with a pin.
  * @param pin Pin name.
  * @param map PinMap array, terminated by an entry with pin NC.
  * @return Function value, or NC cast to uint32_t if not found.
  */
uint32_t pinmap_find_function(PinName pin, const PinMap *map);

/**
  * @brief Find the function associated with a pin, ignoring NC pins.
  * @param pin Pin name.
  * @param map PinMap array, terminated by an entry with pin NC.
  * @return Function value, or NC cast to uint32_t if the pin is NC or not found.
  */
uint32_t pinmap_function(PinName pin, const PinMap *map);

/**
  * @brief Merge two peripheral pointers that may be NP.
  * @param a First peripheral pointer.
  * @param b Second peripheral pointer.
  * @return The peripheral that is set, or a if both are the same. NP if they conflict.
  */
void *pinmap_merge_peripheral(void *a, void *b);

#ifdef __cplusplus
}
#endif

#endif

/** @}*/
