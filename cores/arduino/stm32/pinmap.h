
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

typedef struct {
    PinName pin;
    int peripheral;
    int function;
} PinMap;

typedef struct {
  TIM_TypeDef *timer;
  IRQn_Type irq;
  uint8_t clk_src;
} TimerMap;

bool pin_in_pinmap(PinName pin, const PinMap* map);
void pin_function(PinName pin, int function);

uint32_t pinmap_peripheral(PinName pin, const PinMap* map);
uint32_t pinmap_function(PinName pin, const PinMap* map);
uint32_t pinmap_find_peripheral(PinName pin, const PinMap* map);
uint32_t pinmap_find_function(PinName pin, const PinMap* map);
uint32_t pinmap_merge(uint32_t a, uint32_t b);

uint32_t timermap_irq(TIM_TypeDef *tim, const TimerMap* map);
uint32_t timermap_clkSrc(TIM_TypeDef *tim, const TimerMap* map);

#ifdef __cplusplus
}
#endif

#endif

/** @}*/
