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

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
  PE_0,
  PE_1,
  PE_2,
  PE_3,
  PE_4,
  PE_5,
  PE_6,
  PE_7,
  PE_8,
  PE_9,
  PE_10,
  PE_11,
  PE_12,
  PE_13,
  PE_14,
  PE_15,

  PB_0,
  PB_1,
  PB_2,
  PB_3,
  PB_4,
  PB_5,
  PB_6,
  PB_7,
  PB_8,
  PB_9,
  PB_10,
  PB_11,
  PB_12,
  PB_13,
  PB_14,
  PB_15,

  PC_0,
  PC_1,
  PC_2,
  PC_3,
  PC_4,
  PC_5,
  PC_6,
  PC_7,
  PC_8,
  PC_9,
  PC_10,
  PC_11,
  PC_12,
  PC_13,
  PC_14,
  PC_15,

  PD_0,
  PD_1,
  PD_2,
  PD_3,
  PD_4,
  PD_5,
  PD_6,
  PD_7,
  PD_8,
  PD_9,
  PD_10,
  PD_11,
  PD_12,
  PD_13,
  PD_14,
  PD_15,

  PA_0, // A0
  PA_1, // A1
  PA_2, // A2
  PA_3, // A3
  PA_4, // A4
  PA_5, // A5
  PA_6, // A6
  PA_7, // A7
  PA_8,
  PA_9,
  PA_10,
  PA_11,
  PA_12,
  PA_13,
  PA_14,
  PA_15,
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
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /**Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
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

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Ensure CCM RAM clock is enabled */
  __HAL_RCC_CCMDATARAMEN_CLK_ENABLE();
}

#ifdef USE_TIM6_TIMEBASE
TIM_HandleTypeDef h_tim6;
extern uint32_t uwTickPrio;

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    clkconfig;
  uint32_t              uwTimclock = 0;
  uint32_t              uwPrescalerValue = 0;
  uint32_t              pFLatency;

  if (TickPriority > 15) {
    TickPriority = 15;
  }
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, TickPriority, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  uwTickPrio = TickPriority;

  __HAL_RCC_TIM6_CLK_ENABLE();

  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  uwTimclock = 2 * HAL_RCC_GetPCLK1Freq();
  /* Compute the prescaler value to have TIM6 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t)((uwTimclock / 1000000) - 1);

  h_tim6.Instance = TIM6;

  h_tim6.Init.Period = (1000000 / 1000) - 1;
  h_tim6.Init.Prescaler = uwPrescalerValue;
  h_tim6.Init.ClockDivision = 0;
  h_tim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  if (HAL_TIM_Base_Init(&h_tim6) == HAL_OK) {
    /* Start the TIM time Base generation in interrupt mode */
    return HAL_TIM_Base_Start_IT(&h_tim6);
  }

  /* Return function status */
  return HAL_ERROR;
}

void HAL_SuspendTick(void)
{
  __HAL_TIM_DISABLE_IT(&h_tim6, TIM_IT_UPDATE);
}

void HAL_ResumeTick(void)
{
  __HAL_TIM_ENABLE_IT(&h_tim6, TIM_IT_UPDATE);
}

#endif // USE_TIM6_TIMEBASE

#ifdef __cplusplus
}
#endif
