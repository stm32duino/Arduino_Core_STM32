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

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
//PX_n, //Dx
  P, //D0
  P, //D1
  P, //D2
  P, //D3
  P, //D4
  P, //D5
  P, //D6
  P, //D7
  P, //D8
  P, //D9
  P, //D10
  P, //D11
  P, //D12
  P, //D13
  P, //D14
  P, //D15
  P, //D16
  P, //D17
  P, //D18
  P, //D19
  P, //D20
  P, //D21
  P, //D22
  P, //D23
  P, //D24
  P, //D25
  P, //D26
  P, //D27
  P, //D28
  P, //D29
  P, //D30
  P, //D31
  P, //D32
  P, //D33
  P, //D34
  P, //D35
  P, //D36
  P, //D37
  P, //D38
  P, //D39
  P, //D40
  P, //D41
  P, //D42
  P, //D43
  P, //D44
  P, //D45
  P, //D46
  P, //D47
  P, //D48
  P, //D49
  P, //D50
  P, //D51
  P, //D52
  P, //D53
  P, //D54
  P, //D55
  P, //D56
  P, //D57
  P, //D58
  P, //D59
  P, //D60
  P, //D61
  P, //D62
  P, //D63
  P, //D64
  P, //D65
  P, //D66
  P, //D67
  P, //D68
  P, //D69
  P, //D70
  P, //D71
  P, //D72
  P, //D73
  P, //D74
  P, //D75
  P, //D76
  P, //D77
  P, //D78/A0
  P, //D79/A1
  P, //D80/A2
  P, //D81/A3
  P, //D82/A4
  P, //D83/A5
  P, //D84/A6
  P, //D85/A7
  P, //D86/A8
  P, //D87/A9
  // Duplicated pins in order to be aligned with PinMap_ADC
  P, //D88/A10 = D
  P, //D89/A11 = D
  P, //D90/A12 = D
  P, //D91/A13 = D
  P, //D92/A14 = D
  P, //D93/A15 = D
  P, //D94/A16 = D
  P  //D95/A17 = D
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
// Replace PX_n_Rx and PX_n_Tx by UART_RX and UART_TX pin names
HardwareSerial  Serial(PX_n_Rx, PX_n_Tx); // Connected to ST-Link

void serialEvent() __attribute__((weak));
void serialEvent() { }

// Define as many Serial instance as desired
// Replace 'SerialX' by the desired name
//#ifdef ENABLE_SERIALX
//HardwareSerial  SerialX(PX_n_Rx, PX_n_Tx);
//
//void serialEventx() __attribute__((weak));
//void serialEventx() { }
//#endif

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
//#ifdef ENABLE_SERIALX
//  if (SerialX.available()) serialEventX();
//#endif
}

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
// Here copy the desired System Clock Configuration
// It could be generated thanks STM32CubeMX after code generation for Toolchain/IDE: 'SW4STM32',
// available in src/main.c
// or
// copied from a STM32CubeYY project examples
// where 'YY' could be F0, F1, F2, F3, F4, F7, L0, L1, L4
}

#ifdef __cplusplus
}
#endif
