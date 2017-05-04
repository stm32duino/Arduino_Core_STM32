/*
 *******************************************************************************
 * Copyright (c) 2016, STMicroelectronics
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
#ifndef _PORTNAMES_H
#define _PORTNAMES_H

#include "stm32_def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	FirstPort = 0x00,
    PortA = FirstPort,
    PortB,
#if defined GPIOC_BASE
    PortC,
#endif
#if defined GPIOD_BASE
    PortD,
#endif
#if defined GPIOE_BASE
    PortE,
#endif
#if defined GPIOF_BASE
    PortF,
#endif
#if defined GPIOG_BASE
    PortG,
#endif
#if defined GPIOH_BASE
    PortH,
#endif
#if defined GPIOI_BASE
    PortI,
#endif
#if defined GPIOJ_BASE
    PortJ,
#endif
#if defined GPIOK_BASE
    PortK,
#endif
	PortZ,
	LastPort = PortZ-1
} PortName;

_Static_assert  (LastPort <= 0x0F, "PortName must be less than 16");

#define MAX_NB_PORT (LastPort-FirstPort+1)

GPIO_TypeDef *get_GPIO_Port(uint32_t port_idx);
GPIO_TypeDef *set_GPIO_Port_Clock(uint32_t port_idx);

#ifdef __cplusplus
}
#endif
#endif
