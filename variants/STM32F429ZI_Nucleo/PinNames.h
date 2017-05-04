/*
 * <Description>
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 *
 * License type: GPLv2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _PINNAMES_H
#define _PINNAMES_H

#include "PinNamesTypes.h"
#include "PortNames.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {

    PA0  = (PortA << 4) + 0x00,
    PA1  = (PortA << 4) + 0x01,
    PA2  = (PortA << 4) + 0x02,
    PA3  = (PortA << 4) + 0x03,
    PA4  = (PortA << 4) + 0x04,
    PA5  = (PortA << 4) + 0x05,
    PA6  = (PortA << 4) + 0x06,
    PA7  = (PortA << 4) + 0x07,
    PA8  = (PortA << 4) + 0x08,
    PA9  = (PortA << 4) + 0x09,
    PA10 = (PortA << 4) + 0x0A,
    PA11 = (PortA << 4) + 0x0B,
    PA12 = (PortA << 4) + 0x0C,
    PA13 = (PortA << 4) + 0x0D,
    PA14 = (PortA << 4) + 0x0E,
    PA15 = (PortA << 4) + 0x0F,

    PB0  = (PortB << 4) + 0x00,
    PB1  = (PortB << 4) + 0x01,
    PB2  = (PortB << 4) + 0x02,
    PB3  = (PortB << 4) + 0x03,
    PB4  = (PortB << 4) + 0x04,
    PB5  = (PortB << 4) + 0x05,
    PB6  = (PortB << 4) + 0x06,
    PB7  = (PortB << 4) + 0x07,
    PB8  = (PortB << 4) + 0x08,
    PB9  = (PortB << 4) + 0x09,
    PB10 = (PortB << 4) + 0x0A,
    PB11 = (PortB << 4) + 0x0B,
    PB12 = (PortB << 4) + 0x0C,
    PB13 = (PortB << 4) + 0x0D,
    PB14 = (PortB << 4) + 0x0E,
    PB15 = (PortB << 4) + 0x0F,
#if defined GPIOC_BASE
    PC0  = (PortC << 4) + 0x00,
    PC1  = (PortC << 4) + 0x01,
    PC2  = (PortC << 4) + 0x02,
    PC3  = (PortC << 4) + 0x03,
    PC4  = (PortC << 4) + 0x04,
    PC5  = (PortC << 4) + 0x05,
    PC6  = (PortC << 4) + 0x06,
    PC7  = (PortC << 4) + 0x07,
    PC8  = (PortC << 4) + 0x08,
    PC9  = (PortC << 4) + 0x09,
    PC10 = (PortC << 4) + 0x0A,
    PC11 = (PortC << 4) + 0x0B,
    PC12 = (PortC << 4) + 0x0C,
    PC13 = (PortC << 4) + 0x0D,
    PC14 = (PortC << 4) + 0x0E,
    PC15 = (PortC << 4) + 0x0F,
#endif
#if defined GPIOD_BASE
    PD0  = (PortD << 4) + 0x00,
    PD1  = (PortD << 4) + 0x01,
    PD2  = (PortD << 4) + 0x02,
    PD3  = (PortD << 4) + 0x03,
    PD4  = (PortD << 4) + 0x04,
    PD5  = (PortD << 4) + 0x05,
    PD6  = (PortD << 4) + 0x06,
    PD7  = (PortD << 4) + 0x07,
    PD8  = (PortD << 4) + 0x08,
    PD9  = (PortD << 4) + 0x09,
    PD10 = (PortD << 4) + 0x0A,
    PD11 = (PortD << 4) + 0x0B,
    PD12 = (PortD << 4) + 0x0C,
    PD13 = (PortD << 4) + 0x0D,
    PD14 = (PortD << 4) + 0x0E,
    PD15 = (PortD << 4) + 0x0F,
#endif
#if defined GPIOE_BASE
    PE0  = (PortE << 4) + 0x00,
    PE1  = (PortE << 4) + 0x01,
    PE2  = (PortE << 4) + 0x02,
    PE3  = (PortE << 4) + 0x03,
    PE4  = (PortE << 4) + 0x04,
    PE5  = (PortE << 4) + 0x05,
    PE6  = (PortE << 4) + 0x06,
    PE7  = (PortE << 4) + 0x07,
    PE8  = (PortE << 4) + 0x08,
    PE9  = (PortE << 4) + 0x09,
    PE10 = (PortE << 4) + 0x0A,
    PE11 = (PortE << 4) + 0x0B,
    PE12 = (PortE << 4) + 0x0C,
    PE13 = (PortE << 4) + 0x0D,
    PE14 = (PortE << 4) + 0x0E,
    PE15 = (PortE << 4) + 0x0F,
#endif
#if defined GPIOF_BASE
    PF0  = (PortF << 4) + 0x00,
    PF1  = (PortF << 4) + 0x01,
    PF2  = (PortF << 4) + 0x02,
    PF3  = (PortF << 4) + 0x03,
    PF4  = (PortF << 4) + 0x04,
    PF5  = (PortF << 4) + 0x05,
    PF6  = (PortF << 4) + 0x06,
    PF7  = (PortF << 4) + 0x07,
    PF8  = (PortF << 4) + 0x08,
    PF9  = (PortF << 4) + 0x09,
    PF10 = (PortF << 4) + 0x0A,
    PF11 = (PortF << 4) + 0x0B,
    PF12 = (PortF << 4) + 0x0C,
    PF13 = (PortF << 4) + 0x0D,
    PF14 = (PortF << 4) + 0x0E,
    PF15 = (PortF << 4) + 0x0F,
#endif
#if defined GPIOG_BASE
    PG0  = (PortG << 4) + 0x00,
    PG1  = (PortG << 4) + 0x01,
    PG2  = (PortG << 4) + 0x02,
    PG3  = (PortG << 4) + 0x03,
    PG4  = (PortG << 4) + 0x04,
    PG5  = (PortG << 4) + 0x05,
    PG6  = (PortG << 4) + 0x06,
    PG7  = (PortG << 4) + 0x07,
    PG8  = (PortG << 4) + 0x08,
    PG9  = (PortG << 4) + 0x09,
    PG10 = (PortG << 4) + 0x0A,
    PG11 = (PortG << 4) + 0x0B,
    PG12 = (PortG << 4) + 0x0C,
    PG13 = (PortG << 4) + 0x0D,
    PG14 = (PortG << 4) + 0x0E,
    PG15 = (PortG << 4) + 0x0F,
#endif
#if defined GPIOH_BASE
    PH0  = (PortH << 4) + 0x00,
    PH1  = (PortH << 4) + 0x01,
#endif

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

#ifdef __cplusplus
}
#endif

#endif
