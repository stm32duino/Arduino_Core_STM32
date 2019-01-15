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

/*
 * This version created by Andrew W Symons (AWS), 19-Nov-18
 * for DIYMROE_STM32F407VGT board
 */

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
// Numbered anticlockwise from USB socket
// Header right (as viewed with USB socket at the bottom), numbered from bottom
  PE_3,  //  0 Header right, pin 1
  PE_2,  //  1 Header right, pin 2
  PE_5,  //  2 Header right, pin 3
  PE_4,  //  3 Header right, pin 4
  PC_13, //  4 Header right, pin 5
  PE_6,  //  5 Header right, pin 6
         // -- Header right, pin 7 = GND
         // -- Header right, pin 8 = 3.3V
  PC_1,  //  6 Header right, pin 9
  PC_0,  //  7 Header right, pin 10
  PA_0,  //  8 Header right, pin 11
  PC_2,  //  9 Header right, pin 12
  PA_2,  // 10 Header right, pin 13
  PA_1,  // 11 Header right, pin 14
  PA_3,  // 12 Header right, pin 15
  PC_3,  // 13 Header right, pin 16
  PA_5,  // 14 Header right, pin 17
  PA_4,  // 15 Header right, pin 18
  PA_7,  // 16 Header right, pin 19
  PA_6,  // 17 Header right, pin 20
  PC_5,  // 18 Header right, pin 21
  PC_4,  // 19 Header right, pin 22
  PB_1,  // 20 Header right, pin 23
  PB_0,  // 21 Header right, pin 24
  PB_9,  // 22 Header right, pin 25
  PB_8,  // 23 Header right, pin 26
  PE_7,  // 24 Header right, pin 27
  PE_1,  // 25 Header right, pin 28
  PE_9,  // 26 Header right, pin 29
  PE_8,  // 27 Header right, pin 30
  PB_2,  // 28 Header right, pin 31
  PE_10, // 29 Header right, pin 32

// The final four headers in the right hand side are for BOOT0 and BOOT1 jumpers;
// ... They are not numbered as headers on the schematic

// Header top (as viewed with USB socket at the bottom), numbered from right
  PE_11, // 30 Header top, pin 1
  PE_12, // 31 Header top, pin 2
  PE_13, // 32 Header top, pin 3
  PE_14, // 33 Header top, pin 4
  PE_15, // 34 Header top, pin 5
  PB_10, // 35 Header top, pin 6
  PB_11, // 36 Header top, pin 7
         // -- Header top, pin 8 = GND
  PB_12, // 37 Header top, pin 9
         // -- Header top, pin 10 = 3.3V
  PB_14, // 38 Header top, pin 11
  PB_13, // 39 Header top, pin 12
  PD_8,  // 40 Header top, pin 13
  PB_15, // 41 Header top, pin 14
  PD_10, // 42 Header top, pin 15
  PD_9,  // 43 Header top, pin 16
  PD_12, // 44 Header top, pin 17
  PD_11, // 45 Header top, pin 18
  PD_14, // 46 Header top, pin 19
  PD_13, // 47 Header top, pin 20
  PC_6,  // 48 Header top, pin 21
  PD_15, // 49 Header top, pin 22
  PC_8,  // 50 Header top, pin 23
  PC_7,  // 51 Header top, pin 24

// Header left (as viewed with UBS coket at the bottom), numbered from top
         // -- Header left, pin 1 = GND
         // -- Header left, pin 2 = Vcc (5V)
  PA_8,  // 52 Header left, pin 3
  PC_9,  // 53 Header left, pin 4
  PA_10, // 54 Header left, pin 5
  PA_9,  // 55 Header left, pin 6
  PA_12, // 56 Header left, pin 7 and USB_DP
  PA_11, // 57 Header left, pin 8 and USB_DM
  PA_14, // 58 Header left, pin 9
  PA_13, // 59 Header left, pin 10
  PC_10, // 60 Header left, pin 11
  PA_15, // 61 Header left, pin 12
  PC_12, // 62 Header left, pin 13
  PC_11, // 63 Header left, pin 14
  PD_1,  // 64 Header left, pin 15
  PD_0,  // 65 Header left, pin 16
  PD_3,  // 66 Header left, pin 17
  PD_2,  // 67 Header left, pin 18
  PD_5,  // 68 Header left, pin 19
  PD_4,  // 69 Header left, pin 20
  PD_7,  // 70 Header left, pin 21
  PD_6,  // 71 Header left, pin 22
  PB_4,  // 72 Header left, pin 23
  PB_3,  // 73 Header left, pin 24
  PB_6,  // 74 Header left, pin 25
  PB_5,  // 75 Header left, pin 26
  PE_0,  // 76 Header left, pin 27 and LED_BUILTIN
  PB_7,  // 77 Header left, pin 28
// Duplicated pins in order to be aligned with PinMap_ADC
  PA_0,  // 78/A0
  PA_1,  // 79/A1
  PA_2,  // 80/A2
  PA_3,  // 81/A3
  PA_4,  // 82/A4
  PA_5,  // 83/A5
  PA_6,  // 84/A6
  PA_7,  // 85/A7
  PB_0,  // 86/A8
  PB_1,  // 87/A9
  PC_0,  // 88/A10
  PC_1,  // 89/A11
  PC_2,  // 90/A12
  PC_3,  // 91/A13
  PC_4,  // 92/A14
  PC_5   // 93/A15
};

#ifdef __cplusplus
}
#endif

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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Configure the Systick interrupt time */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  /* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
