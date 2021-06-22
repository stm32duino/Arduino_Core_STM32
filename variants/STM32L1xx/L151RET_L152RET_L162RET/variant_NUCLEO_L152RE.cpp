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
#if defined(ARDUINO_NUCLEO_L152RE)
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PA_3,
  PA_2,
  PA_10,
  PB_3,
  PB_5,
  PB_4,
  PB_10,
  PA_8,
  PA_9,
  PC_7,
  PB_6,
  PA_7,
  PA_6,
  PA_5,
  PB_9,
  PB_8,
  // ST Morpho
  // CN7 Left Side
  PC_10,
  PC_12,
  PA_13,
  PA_14,
  PA_15,
  PB_7,
  PC_13,
  PC_14,
  PC_15,
  PH_0,
  PH_1,
  PC_2,
  PC_3,
  // CN7 Right Side
  PC_11,
  PD_2,
  // CN10 Left Side
  PC_9,
  // CN10 Right side
  PC_8,
  PC_6,
  PC_5,
  PA_12,
  PA_11,
  PB_12,
  PB_11,
  PB_2,
  PB_1,
  PB_15,
  PB_14,
  PB_13,
  PC_4,
  PA_0,
  PA_1,
  PA_4,
  PB_0,
  PC_1,
  PC_0
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  45, //A0
  46, //A1
  47, //A2
  48, //A3
  49, //A4
  50, //A5
  11, //A6
  12, //A7
  27, //A8
  28, //A9
  34, //A10
  37, //A11
  40, //A12
  41, //A13
  42, //A14
  43, //A15
  44, //A16
  39, //A17
  13, //A18
  1,  //A19
  0   //A20
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
/**
  * @brief  System Clock Configuration
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /*
   * Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
}
#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_L152RE */
