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
#if defined(ARDUINO_DISCO_F072RB)
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  //P2 connector Right side (top view)
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
  PA_13,
#ifdef USB_REMOVED
  PA_12,
  PA_11,
#else
  NC,
  NC,
#endif
  PA_10,
  PA_9,
  PA_8,
  PC_9,
  PC_8,
  PC_7,
  PC_6,
  PB_15,
  PB_14,
  PB_13,
  //P1 connector Left side (top view)
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
#ifdef TSC_REMOVED
  PA_2,
  PA_3,
#else
  NC,
  NC,
#endif
  PA_4,
  PA_5,
#ifdef TSC_REMOVED
  PA_6,
  PA_7,
#else
  NC,
  NC,
#endif
  PC_4,
  PC_5,
#ifdef TSC_REMOVED
  PB_0,
  PB_1,
#else
  NC,
  NC,
#endif
  PB_2,
  PB_10,
  PB_11,
  PB_12
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  31, // A0
  32, // A1
  33, // A2
  34, // A3
  35, // A4
  36, // A5
  37, // A6
  38, // A7
  39, // A8
  40, // A9
  41, // A10
  42, // A11
  43, // A12
  44, // A13
  45, // A14
  46  // A15
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

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_DISCO_F072RB */
