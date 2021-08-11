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

#if defined(ARDUINO_NUCLEO_G0B1RE)
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PC_5,
  PC_4,
  PA_10,
  PB_3,
  PB_5,
  PB_4,
  PB_14,
  PA_8,
  PA_9,
  PC_7,
  PB_0,
  PA_7,
  PA_6,
  PA_5,
  PB_9,
  PB_8,
  // ST Morpho
  // CN7 Left Side
  PC_10,
  PC_12,
  PA_14,
  PD_0,
  PD_3,
  PA_13,
  PD_4,
  PA_15,
  PB_7,
  PC_13,
  PC_14,
  PC_15,
  PF_0,
  PF_1,
  PC_2,
  PC_3,
  // CN7 Right Side
  PC_11,
  PD_2,
  PD_1,
  PD_5,
  // CN10 Left Side
  PC_9,
  // CN10 Right side
  PC_8,
  PC_6,
  PA_3,
  PD_6,
  PA_12,
  PA_11,
  PC_1,
  PC_0,
  PB_2,
  PB_6,
  PB_15,
  PB_10,
  PB_13,
  PA_2,
  PD_8,
  PD_9,
  PA_0,
  PA_1,
  PA_4,
  PB_1,
  PB_11,
  PB_12,
  PF_2,
  PA_9_R,
  PA_10_R
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  53, //A0
  54, //A1
  55, //A2
  56, //A3
  57, //A4
  58, //A5
  11, //A6
  12, //A7
  45, //A8
  48, //A9
  0,  //A10
  1,  //A11
  10, //A12
  13, //A13 - LED
  39, //A14 - STLINK RX
  50  //A15 - STLINK TX
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_G0B1RE */
