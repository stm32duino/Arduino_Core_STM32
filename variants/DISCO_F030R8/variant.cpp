/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
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
const PinName digitalPin[] = {
 //P1 connector Right side (bottom view)
  PC_13, //D0
  PC_14, //D1
  PC_15, //D2
  PF_0,  //D3
  PF_1,  //D4
  PC_0,  //D5
  PC_1,  //D6
  PC_2,  //D7
  PC_3,  //D8
  PA_0,  //D9 - USER_BTN
  PA_1,  //D10
  PA_2,  //D11
  PA_3,  //D12
  PF_4,  //D13
  PF_5,  //D14
  PA_4,  //D15
  PA_5,  //D16
  PA_6,  //D17
  PA_7,  //D18
  PC_4,  //D19
  PC_5,  //D20
  PB_0,  //D21
  PB_1,  //D22
  PB_2,  //D23
  PB_10, //D24
  PB_11, //D25
  PB_12, //D26
  //P2 connector Left side (bottom view)
  PB_9,  //D27
  PB_8,  //D28
  PB_7,  //D29
  PB_6,  //D30
  PB_5,  //D31
  PB_4,  //D32
  PB_3,  //D33
  PD_2,  //D34
  PC_12, //D35
  PC_11, //D36
  PC_10, //D37
  PA_15, //D38
  PA_14, //D39
  PF_7,  //D40
  PF_6,  //D41
  PA_13, //D42
  PA_12, //D43
  PA_11, //D44
  PA_10, //D45
  PA_9,  //D46
  PA_8,  //D47
  PC_9,  //D48 - LED_GREEN (LD3)
  PC_8,  //D49 - LED_BLUE (LD4)
  PC_7,  //D50
  PC_6,  //D51
  PB_15, //D52
  PB_14, //D53
  PB_13, //D54
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC_0,  //D55/A0 = D5
  PC_1,  //D56/A1 = D6
  PC_2,  //D57/A2 = D7
  PC_3,  //D58/A3 = D8
  PA_0,  //D59/A4 = D9
  PA_1,  //D60/A5 = D10
  PA_2,  //D61/A6 = D11
  PA_3,  //D62/A7 = D12
  PA_4,  //D63/A8 = D15
  PA_5,  //D64/A9 = D16
  PA_6,  //D65/A10= D17
  PA_7,  //D66/A11= D18
  PC_4,  //D67/A12 = D19
  PC_5,  //D68/A13 = D20
  PB_0,  //D69/A14 = D21
  PB_1   //D70/A15 = D22
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
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI/2)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = 1
  *            PLLMUL                         = 12
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
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
