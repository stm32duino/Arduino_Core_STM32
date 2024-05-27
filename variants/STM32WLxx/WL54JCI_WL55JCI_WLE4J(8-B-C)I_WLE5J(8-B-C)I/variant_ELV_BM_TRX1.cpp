/*
 *******************************************************************************
 * Copyright (c) 2024, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_ELV_BM_TRX1)
#include "pins_arduino.h"
// Digital PinName array
const PinName digitalPin[] = {
  NC,      // D0
  PB_12,   // D1
  PA_0,    // D2
  PB_14,   // D3/A0
  PC_13,   // D4
  PA_9,    // D5
  PA_10,   // D6
  PA_11,   // D7
  PA_12,   // D8
  NC,      // D9
  NC,      // D10
  NC,      // D11
  NC,      // D12
  NC,      // D13
  NC,      // D14
  NC,      // D15
  NC,      // D16
  PA_14,   // D17/A2
  PA_13,   // D18/A3
  PA_2,    // D19
  PA_3,    // D20
  PA_4,    // D21
  PA_5,    // D22
  PA_6,    // D23
  PA_7,    // D24
  PA_15,   // D25
  PB_3,    // D26
  PC_4,    // D27
  PC_5     // D28
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  3,  // A0,  PB14
  11, // A1,  PA14
  12  // A2,  PA13
};

// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/*
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
 */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  /* Configure the main internal regulator output voltage*/

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the CPU, AHB and APB busses clocks*/
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEDiv = RCC_HSE_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 6;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers*/

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3 | RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
                                | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}
#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_ELV_BM_TRX1 */
