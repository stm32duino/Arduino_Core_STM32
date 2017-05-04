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
#include "PortNames.h"
#include "stm32_def.h"

// Return GPIO base address
GPIO_TypeDef *get_GPIO_Port(uint32_t port_idx) {
    GPIO_TypeDef* gpioPort = 0;
    switch (port_idx) {
        case PortA:
            gpioPort = GPIOA_BASE;
            break;
        case PortB:
            gpioPort = GPIOB_BASE;
            break;
#if defined GPIOC_BASE
        case PortC:
            gpioPort = GPIOC_BASE;
            break;
#endif
#if defined GPIOD_BASE
        case PortD:
            gpioPort = GPIOD_BASE;
            break;
#endif
#if defined GPIOE_BASE
        case PortE:
            gpioPort = GPIOE_BASE;
            break;
#endif
#if defined GPIOF_BASE
        case PortF:
            gpioPort = GPIOF_BASE;
            break;
#endif
#if defined GPIOG_BASE
        case PortG:
            gpioPort = GPIOG_BASE;
            break;
#endif
#if defined GPIOH_BASE
        case PortH:
            gpioPort = GPIOH_BASE;
            break;
#endif
#if defined GPIOI_BASE
        case PortI:
            gpioPort = GPIOI_BASE;
            break;
#endif
#if defined GPIOJ_BASE
        case PortJ:
            gpioPort = GPIOJ_BASE;
            break;
#endif
#if defined GPIOK_BASE
        case PortK:
            gpioPort = GPIOK_BASE;
            break;
#endif
        default:
			// wrong port number
			//TBD: error management
            gpioPort = 0;
            break;
    }
    return gpioPort;
}

// Enable GPIO clock and return GPIO base address
GPIO_TypeDef *set_GPIO_Port_Clock(uint32_t port_idx) {
    GPIO_TypeDef* gpioPort = 0;
    switch (port_idx) {
        case PortA:
            gpioPort = GPIOA_BASE;
            __GPIOA_CLK_ENABLE();
            break;
        case PortB:
            gpioPort = GPIOB_BASE;
            __GPIOB_CLK_ENABLE();
            break;
#if defined GPIOC_BASE
        case PortC:
            gpioPort = GPIOC_BASE;
            __GPIOC_CLK_ENABLE();
            break;
#endif
#if defined GPIOD_BASE
        case PortD:
            gpioPort = GPIOD_BASE;
            __GPIOD_CLK_ENABLE();
            break;
#endif
#if defined GPIOE_BASE
        case PortE:
            gpioPort = GPIOE_BASE;
            __GPIOE_CLK_ENABLE();
            break;
#endif
#if defined GPIOF_BASE
        case PortF:
            gpioPort = GPIOF_BASE;
            __GPIOF_CLK_ENABLE();
            break;
#endif
#if defined GPIOG_BASE
        case PortG:
            gpioPort = GPIOG_BASE;
            __GPIOG_CLK_ENABLE();
            break;
#endif
#if defined GPIOH_BASE
        case PortH:
            gpioPort = GPIOH_BASE;
            __GPIOH_CLK_ENABLE();
            break;
#endif
#if defined GPIOI_BASE
        case PortI:
            gpioPort = GPIOI_BASE;
            __GPIOI_CLK_ENABLE();
            break;
#endif
#if defined GPIOJ_BASE
        case PortJ:
            gpioPort = GPIOJ_BASE;
            __GPIOJ_CLK_ENABLE();
            break;
#endif
#if defined GPIOK_BASE
        case PortK:
            gpioPort = GPIOK_BASE;
            __GPIOK_CLK_ENABLE();
            break;
#endif
        default:
			// wrong port number
			//TBD: error management
            gpioPort = 0;
            break;
    }
    return gpioPort;
}

