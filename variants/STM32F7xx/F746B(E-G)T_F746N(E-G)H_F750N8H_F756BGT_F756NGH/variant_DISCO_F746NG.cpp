/*
 *******************************************************************************
 * Copyright (c) 2017-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_DISCO_F746NG)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PC_7,
  PC_6,
  PG_6,
  PB_4,
  PG_7,
  PI_0,
  PH_6,
  PI_3,
  PI_2,
  PA_15,
  PA_8,
  PB_15,
  PB_14,
  PI_1,
  PB_9,
  PB_8,
  PA_0,
  PF_10,
  PF_9,
  PF_8,
  PF_7,
  PF_6,
  PI_11,
  PB_7,
  PA_9,
  PC_13,
  PA_1,
  PA_2,
  PA_3,
  PA_4,
  PA_5,
  PA_6,
  PA_7,
  PA_10,
  PA_11,
  PA_12,
  PA_13,
  PA_14,
  PB_0,
  PB_1,
  PB_2,
  PB_3,
  PB_5,
  PB_6,
  PB_10,
  PB_11,
  PB_12,
  PB_13,
  PC_0,
  PC_1,
  PC_2,
  PC_3,
  PC_4,
  PC_5,
  PC_8,
  PC_9,
  PC_10,
  PC_11,
  PC_12,
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
  PF_0,
  PF_1,
  PF_2,
  PF_3,
  PF_4,
  PF_5,
  PF_11,
  PF_12,
  PF_13,
  PF_14,
  PF_15,
  PG_0,
  PG_1,
  PG_2,
  PG_3,
  PG_4,
  PG_5,
  PG_8,
  PG_9,
  PG_10,
  PG_11,
  PG_12,
  PG_13,
  PG_14,
  PG_15,
  PH_0,
  PH_1,
  PH_2,
  PH_3,
  PH_4,
  PH_5,
  PH_7,
  PH_8,
  PH_9,
  PH_10,
  PH_11,
  PH_12,
  PH_13,
  PH_14,
  PH_15,
  PI_4,
  PI_5,
  PI_6,
  PI_7,
  PI_8,
  PI_9,
  PI_10,
  PI_12,
  PI_13,
  PI_14,
  PI_15,
  PJ_0,
  PJ_1,
  PJ_2,
  PJ_3,
  PJ_4,
  PJ_5,
  PJ_6,
  PJ_7,
  PJ_8,
  PJ_9,
  PJ_10,
  PJ_11,
  PJ_12,
  PJ_13,
  PJ_14,
  PJ_15,
  PK_0,
  PK_1,
  PK_2,
  PK_3,
  PK_4,
  PK_5,
  PK_6,
  PK_7
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0
  17, // A1
  18, // A2
  19, // A3
  20, // A4
  21  // A5
};


// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            PLLSAI_N                       = 192
  *            PLLSAI_P                       = 4
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Activate the Over-Drive mode */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC | RCC_PERIPHCLK_USART1
                                             | RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_DISCO_F746NG */
