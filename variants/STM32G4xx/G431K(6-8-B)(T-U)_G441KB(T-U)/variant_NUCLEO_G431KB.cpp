/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_G431KB)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PA_10, // D0
  PA_9,  // D1
  PA_12, // D2
  PB_0,  // D3
  PB_7,  // D4
  PA_15, // D5
  PB_6,  // D6
  PF_0,  // D7
  PF_1,  // D8
  PA_8,  // D9
  PA_11, // D10
  PB_5,  // D11
  PB_4,  // D12
  PB_8,  // D13 - LED - SB7 ON SB6 OFF
  PA_0,  // D14/A0
  PA_1,  // D15/A1
  PA_3,  // D16/A2 - SB12 ON VCP RX
  PA_4,  // D17/A3
  PA_5,  // D18/A4 - SB3 ON also connected to PB7
  PA_6,  // D19/A5 - SB2 ON also connected to PA15
  PA_7,  // D20/A6
  PA_2   // D21/A7 - SB1 ON VCP TX
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  14, // A0
  15, // A1
  16, // A2
  17, // A3
  18, // A4
  19, // A5
  20, // A6
  21  // A7
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
  * @brief  System Clock Configuration
  */
WEAK void SystemClock_Config(void)
{
  /* HSE is available but SB9 and SB10 OFF so not usable per default */
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /* Configure the main internal regulator output voltage */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the peripherals clocks */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_USB;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ARDUINO_NUCLEO_G431KB */
