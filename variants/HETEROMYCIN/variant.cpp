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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

const PinName digitalPin[] = {
    // USART1
    PA_10, // D0 - RX
    PA_9,  // D1 - TX

    // USART3
    PC_11, // D2 - RX
    PC_10, // D3 - TX

    // SWD
    PA_13, // D4 - SWDIO
    PA_14, // D5 - SWCLK
    PB_3,  // D6 - SWO

    // MISC
    PA_15, // D7 - Status LED
    PD_11, // D8 - SD_DETECT
    PA_4,  // D9 - MCU_SS

    // SPI4
    PD_10, // D10 - SS_SD
    PE_14, // D11 - MOSI
    PE_13, // D12 - MISO
    PE_12, // D13 - SCK

    // I2C
    PB_9, // D14 - SDA
    PB_6, // D15 - SCL

    // SPI1
    PA_7, // D16 - MOSI
    PA_6, // D17 - MISO
    PA_5, // D18 - SCK

    // Stepper
    PA_3,  // D19 - STEP_X
    PE_7,  // D20 - DIR_X
    PE_8,  // D21 - SS_X
    PA_2,  // D22 - STEP_Y
    PB_1,  // D23 - DIR_Y
    PB_2,  // D24 - SS_Y
    PA_1,  // D25 - STEP_Z
    PC_5,  // D26 - DIR_Z
    PB_0,  // D27 - SS_Z
    PB_15, // D28 - STEP_E0
    PB_13, // D29 - DIR_E0
    PD_9,  // D30 - SS_E0
    PB_14, // D31 - STEP_E1
    PB_10, // D32 - DIR_E1
    PB_12, // D33 - SS_E1

    // PWM
    PE_5,  // D34 - PWM_BED
    PA_0,  // D35 - PWM_HEAT1
    PE_6,  // D36 - PWM_HEAT2
    PD_12, // D37 - PWM_FAN1
    PD_13, // D38 - PWM_FAN2
    PD_14, // D39 - PWM_FAN3
    PD_15, // D40 - PWM_FAN4
    PC_9,  // D41 - PWM_EXT1
    PC_8,  // D42 - PWM_EXT2
    PC_7,  // D43 - PWM_EXT3
    PC_6,  // D44 - PWM_EXT4

    // Endstops
    PE_4, // D45 - X_MIN
    PE_3, // D46 - Y_MIN
    PE_2, // D47 - Z_MIN

    // GPIO
    PD_6, // D48 - D1
    PD_5, // D49 - D2
    PD_4, // D50 - D3
    PD_3, // D51 - D4
    PD_2, // D52 - D5

    // ADC
    PC_3, // D53/A0 - TEMP1
    PC_2, // D54/A1 - TEMP2
    PC_1, // D55/A2 - TEMP3
    PC_0, // D56/A3 - TEMP4
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
WEAK void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType =
      RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 10;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Activate the Over-Drive mode */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection =
      RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART3 |
      RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Enables the Clock Security System */
  HAL_RCC_EnableCSS();

  /* Configure the Systick interrupt time */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  /* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
