/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#ifndef _PINCONFIGURED_H
#define _PINCONFIGURED_H

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PINCONF_INDEX(X) (STM_PORT(X)-FirstPort)

#define PINCONF_MASK     0x01
#define PINCONF_SHIFT(X) (STM_PIN(X))
#define PINCONF_BIT(X)   (PINCONF_MASK << PINCONF_SHIFT(X))

#define PINCONF_VAL(X, Y)   ((Y >> PINCONF_SHIFT(X)) & PINCONF_MASK)

#define is_pin_configured(pin, map) \
  (PINCONF_VAL(pin, map[PINCONF_INDEX(pin)]))
#define set_pin_configured(pin, map) \
  (map[PINCONF_INDEX(pin)] = map[PINCONF_INDEX(pin)] | PINCONF_BIT(pin))
#define reset_pin_configured(pin, map) \
  (map[PINCONF_INDEX(pin)] = map[PINCONF_INDEX(pin)] & (~PINCONF_BIT(pin)))

#ifdef __cplusplus
}
#endif

#endif
