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
#if defined(ARDUINO_DISCO_F030R8)

#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  //P1 connector Right side (bottom view)
  PC_13,
  PC_14,
  PC_15,
  PF_0,
  PF_1,
  PC_0,
  PC_1,
  PC_2,
  PC_3,
  PA_0,
  PA_1,
  PA_2,
  PA_3,
  PF_4,
  PF_5,
  PA_4,
  PA_5,
  PA_6,
  PA_7,
  PC_4,
  PC_5,
  PB_0,
  PB_1,
  PB_2,
  PB_10,
  PB_11,
  PB_12,
  //P2 connector Left side (bottom view)
  PB_9,
  PB_8,
  PB_7,
  PB_6,
  PB_5,
  PB_4,
  PB_3,
  PD_2,
  PC_12,
  PC_11,
  PC_10,
  PA_15,
  PA_14,
  PF_7,
  PF_6,
  PA_13,
  PA_12,
  PA_11,
  PA_10,
  PA_9,
  PA_8,
  PC_9,
  PC_8,
  PC_7,
  PC_6,
  PB_15,
  PB_14,
  PB_13
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  5,  //A0  = D5
  6,  //A1  = D6
  7,  //A2  = D7
  8,  //A3  = D8
  9,  //A4  = D9
  10, //A5  = D10
  11, //A6  = D11
  12, //A7  = D12
  15, //A8  = D15
  16, //A9  = D16
  17, //A10 = D17
  18, //A11 = D18
  19, //A12 = D19
  20, //A13 = D20
  21, //A14 = D21
  22  //A15 = D22
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
  /*
   * Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_DISCO_F030R8 */
