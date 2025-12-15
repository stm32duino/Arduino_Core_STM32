/*
 *******************************************************************************
 * Copyright (c) 2025, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_F410RB)
#include "pins_arduino.h"

// Digital PinName array
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
  NC,   //D18 - BOOT0
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
  PB_11,
  // CN10 Left Side
  PC_9,
  // CN10 Right side
  PC_8,
  PC_6,
  PC_5,
  PA_12,
  PA_11,
  PB_12,
  NC,    //D39
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
const pin_size_t analogInputPin[] = {
  46, //A0
  47, //A1
  48, //A2
  49, //A3
  50, //A4
  51, //A5
  11, //A6
  12, //A7
  13, //A8
  28, //A9
  29, //A10
  35, //A11
  41, //A12
  45, //A13
  0,  //A14
  1   //A15
};

#ifdef __cplusplus
extern "C" {
#endif
/**
  * @brief  System Clock Configuration
  *         SYSCLK = 100MHz for ARDUINO_NUCLEO_F410RB
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }
}


#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_GENERIC_* */
