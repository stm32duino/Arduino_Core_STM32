/*
 *******************************************************************************
 * Copyright (c) 2014, STMicroelectronics
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

#ifndef _PERIPHERALPINS_H
#define _PERIPHERALPINS_H

#include "pinmap.h"
#ifdef STM32F1xx
  #include "PinAF_STM32F1.h"
#endif

/*
 * Pin maps: for each peripheral signal, the PinMap array lists the pins that
 * can carry it, with the peripheral instance and pin function (see pinmap.h).
 * Each array is terminated by an entry with pin NC and peripheral NP.
 * They are generated per variant in PeripheralPins.c.
 * Unless stated otherwise, an entry holds: pin, peripheral instance and alternate function.
 */
//*** ADC ***
/** @brief ADC inputs pin map: pin, ADC instance and pin function (alternate
 *         function and ADC channel). */
extern const PinMap PinMap_ADC[];

//*** DAC ***
/** @brief DAC outputs pin map: pin, DAC instance and pin function (alternate
 *         function and DAC channel). */
extern const PinMap PinMap_DAC[];

//*** I2C ***
/** @brief I2C SDA signal pin map. */
extern const PinMap PinMap_I2C_SDA[];
/** @brief I2C SCL signal pin map. */
extern const PinMap PinMap_I2C_SCL[];

//*** I3C ***
/** @brief I3C SDA signal pin map. */
extern const PinMap PinMap_I3C_SDA[];
/** @brief I3C SCL signal pin map. */
extern const PinMap PinMap_I3C_SCL[];

//*** TIM ***
/** @brief Backward compatibility alias of #PinMap_TIM */
#define PinMap_PWM PinMap_TIM
/** @brief Timer channels pin map: pin, timer instance and pin function
 *         (alternate function, timer channel and inverted flag). */
extern const PinMap PinMap_TIM[];

//*** SERIAL ***
/** @brief U(S)ART TX signal pin map. */
extern const PinMap PinMap_UART_TX[];
/** @brief U(S)ART RX signal pin map. */
extern const PinMap PinMap_UART_RX[];
/** @brief U(S)ART RTS signal pin map. */
extern const PinMap PinMap_UART_RTS[];
/** @brief U(S)ART CTS signal pin map. */
extern const PinMap PinMap_UART_CTS[];

//*** SPI ***
/** @brief SPI MOSI signal pin map. */
extern const PinMap PinMap_SPI_MOSI[];
/** @brief SPI MISO signal pin map. */
extern const PinMap PinMap_SPI_MISO[];
/** @brief SPI SCLK signal pin map. */
extern const PinMap PinMap_SPI_SCLK[];
/** @brief SPI SSEL (chip select) signal pin map. */
extern const PinMap PinMap_SPI_SSEL[];

//*** CAN ***
/** @brief CAN RD (receive) signal pin map. */
extern const PinMap PinMap_CAN_RD[];
/** @brief CAN TD (transmit) signal pin map. */
extern const PinMap PinMap_CAN_TD[];

//*** ETHERNET ***
/** @brief Ethernet signals pin map. */
extern const PinMap PinMap_Ethernet[];

//*** QUADSPI ***
/** @brief QUADSPI DATA0 signal pin map. */
extern const PinMap PinMap_QUADSPI_DATA0[];
/** @brief QUADSPI DATA1 signal pin map. */
extern const PinMap PinMap_QUADSPI_DATA1[];
/** @brief QUADSPI DATA2 signal pin map. */
extern const PinMap PinMap_QUADSPI_DATA2[];
/** @brief QUADSPI DATA3 signal pin map. */
extern const PinMap PinMap_QUADSPI_DATA3[];
/** @brief QUADSPI SCLK (clock) signal pin map. */
extern const PinMap PinMap_QUADSPI_SCLK[];
/** @brief QUADSPI NCS1 (chip select, bank 1) signal pin map. */
extern const PinMap PinMap_QUADSPI_NCS1[];
/** @brief QUADSPI NCS2 (chip select, bank 2) signal pin map. */
extern const PinMap PinMap_QUADSPI_NCS2[];

//*** OCTOSPI ***
/** @brief OCTOSPI DATA0 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA0[];
/** @brief OCTOSPI DATA1 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA1[];
/** @brief OCTOSPI DATA2 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA2[];
/** @brief OCTOSPI DATA3 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA3[];
/** @brief OCTOSPI DATA4 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA4[];
/** @brief OCTOSPI DATA5 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA5[];
/** @brief OCTOSPI DATA6 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA6[];
/** @brief OCTOSPI DATA7 signal pin map. */
extern const PinMap PinMap_OCTOSPI_DATA7[];
/** @brief OCTOSPI SCLK (clock) signal pin map. */
extern const PinMap PinMap_OCTOSPI_SCLK[];
/** @brief OCTOSPI NCS1 (chip select, bank 1) signal pin map. */
extern const PinMap PinMap_OCTOSPI_NCS1[];
/** @brief OCTOSPI NCS2 (chip select, bank 2) signal pin map. */
extern const PinMap PinMap_OCTOSPI_NCS2[];
/** @brief OCTOSPI NCLK (inverted clock) signal pin map. */
extern const PinMap PinMap_OCTOSPI_NCLK[];
/** @brief OCTOSPI DQS (data strobe) signal pin map. */
extern const PinMap PinMap_OCTOSPI_DQS[];

//*** XSPI ***
/** @brief XSPI DATA0 signal pin map. */
extern const PinMap PinMap_XSPI_DATA0[];
/** @brief XSPI DATA1 signal pin map. */
extern const PinMap PinMap_XSPI_DATA1[];
/** @brief XSPI DATA2 signal pin map. */
extern const PinMap PinMap_XSPI_DATA2[];
/** @brief XSPI DATA3 signal pin map. */
extern const PinMap PinMap_XSPI_DATA3[];
/** @brief XSPI DATA4 signal pin map. */
extern const PinMap PinMap_XSPI_DATA4[];
/** @brief XSPI DATA5 signal pin map. */
extern const PinMap PinMap_XSPI_DATA5[];
/** @brief XSPI DATA6 signal pin map. */
extern const PinMap PinMap_XSPI_DATA6[];
/** @brief XSPI DATA7 signal pin map. */
extern const PinMap PinMap_XSPI_DATA7[];
/** @brief XSPI SCLK (clock) signal pin map. */
extern const PinMap PinMap_XSPI_SCLK[];
/** @brief XSPI NCS1 (chip select, bank 1) signal pin map. */
extern const PinMap PinMap_XSPI_NCS1[];
/** @brief XSPI NCS2 (chip select, bank 2) signal pin map. */
extern const PinMap PinMap_XSPI_NCS2[];
/** @brief XSPI NCLK (inverted clock) signal pin map. */
extern const PinMap PinMap_XSPI_NCLK[];
/** @brief XSPI DQS (data strobe) signal pin map. */
extern const PinMap PinMap_XSPI_DQS[];

//*** USB ***
/** @brief USB signals (DM/DP) pin map. */
extern const PinMap PinMap_USB[];
/** @brief USB OTG FS signals pin map. */
extern const PinMap PinMap_USB_OTG_FS[];
/** @brief USB OTG HS signals pin map. */
extern const PinMap PinMap_USB_OTG_HS[];

//*** SD ***
/** @brief SD CMD signal pin map. */
extern const PinMap PinMap_SD_CMD[];
/** @brief SD CK (clock) signal pin map. */
extern const PinMap PinMap_SD_CK[];
/** @brief SD DATA0 signal pin map. */
extern const PinMap PinMap_SD_DATA0[];
/** @brief SD DATA1 signal pin map. */
extern const PinMap PinMap_SD_DATA1[];
/** @brief SD DATA2 signal pin map. */
extern const PinMap PinMap_SD_DATA2[];
/** @brief SD DATA3 signal pin map. */
extern const PinMap PinMap_SD_DATA3[];
/** @brief SD DATA4 signal pin map. */
extern const PinMap PinMap_SD_DATA4[];
/** @brief SD DATA5 signal pin map. */
extern const PinMap PinMap_SD_DATA5[];
/** @brief SD DATA6 signal pin map. */
extern const PinMap PinMap_SD_DATA6[];
/** @brief SD DATA7 signal pin map. */
extern const PinMap PinMap_SD_DATA7[];
/** @brief SD CKIN (clock feedback input) signal pin map. */
extern const PinMap PinMap_SD_CKIN[];
/** @brief SD CDIR (command direction) signal pin map. */
extern const PinMap PinMap_SD_CDIR[];
/** @brief SD D0DIR (data 0 direction) signal pin map. */
extern const PinMap PinMap_SD_D0DIR[];
/** @brief SD D123DIR (data 1, 2 and 3 direction) signal pin map. */
extern const PinMap PinMap_SD_D123DIR[];

#endif

