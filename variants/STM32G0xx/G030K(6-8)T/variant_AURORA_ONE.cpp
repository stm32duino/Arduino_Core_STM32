/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_AURORA_ONE)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_10,   //D0
  PA_9,    //D1
  PA_6,    //D2/A6
  PA_7,    //D3/A7
  PA_8,    //D4
  PC_6,    //D5
  PA_11,   //D6/A10
  PA_12,   //D7/A11
  PB_2,    //D8/A12
  PB_1,    //D9/A9
  PB_0,    //D10/A8
  PB_5,    //D11
  PB_4,    //D12
  PB_3,    //D13/LED
  PB_7,    //D14/A13
  PB_6,    //D15
  PB_9,    //D16/MAINSL
  PB_8,    //D17/MAINSL
  PA_15,   //D18/MAINSL
  PA_14,   //D19/A14/SWCLK
  PA_13,   //D20/A15/SWDIO
  PA_0,    //D21/A0
  PA_1,    //D22/A1
  PA_2,    //D23/A2
  PA_3,    //D24/A3
  PA_4,    //D25/A4
  PA_5,    //D26/A5
  PA_9_R,  //D27
  PA_10_R  //D28
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  21, //A0
  22, //A1
  23, //A2
  24, //A3
  25, //A4
  26, //A5
  2,  //A6
  3,  //A7
  10, //A8
  9,  //A9
  6,  //A10
  7,  //A11
  8,  //A12
  14, //A13
  19, //A14
  20  //A15
};

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
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /*
   * Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_AURORA_ONE */
