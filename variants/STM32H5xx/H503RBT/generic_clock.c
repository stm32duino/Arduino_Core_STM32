/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#if defined(ARDUINO_GENERIC_H503RBTX)
#include "pins_arduino.h"

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /** Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /**
    * @note How to generate PLL clock
    * <SOURCE>
    *   HSI     64 MHz ... internal clock
    *   HSI48   48 MHz ... internal clock for recovery
    *   LSI     32 kHz ... internal clock
    *   CSI      4 MHz ... internal clock for low power
    *
    * <MULTIPLEXER>
    *   SOURCE / PLLM * PLLN
    *
    * <TARGRT>
    *   PLL ... MULTIPLEXER / PLLP
    *
    * default CPU clock:
    *   4(CSI) / 1(PLLM) * 125(PLLN) / 2(PLLP) ... 250 MHz
    */

  /** Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInitTypeDef structure */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_CSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = RCC_CSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_CSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 125;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  // TODO: Edit peripherals clock config.
  /** Initializes the peripherals clock */
  // PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_OSPI | RCC_PERIPHCLK_SDMMC1 | RCC_PERIPHCLK_USB;
  // PeriphClkInitStruct.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_HCLK;
  // PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLL2_SOURCE_HSE;
  // PeriphClkInitStruct.PLL2.PLL2M = 2;
  // PeriphClkInitStruct.PLL2.PLL2N = 128;
  // PeriphClkInitStruct.PLL2.PLL2P = 2;
  // PeriphClkInitStruct.PLL2.PLL2Q = 16;
  // PeriphClkInitStruct.PLL2.PLL2R = 2;
  // PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2_VCIRANGE_2;
  // PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
  // PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  // PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVQ;
  // PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PLL2Q;
  // PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_HCLK;
  // PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLL1Q;
  // PeriphClkInitStruct.PLL3.PLL3Source = RCC_PLL3_SOURCE_HSE;
  // PeriphClkInitStruct.PLL3.PLL3M = 2;
  // PeriphClkInitStruct.PLL3.PLL3N = 96;
  // PeriphClkInitStruct.PLL3.PLL3P = 2;
  // PeriphClkInitStruct.PLL3.PLL3Q = 8;
  // PeriphClkInitStruct.PLL3.PLL3R = 2;
  // PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3_VCIRANGE_0;
  // PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3_VCORANGE_MEDIUM;
  // PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  // PeriphClkInitStruct.PLL3.PLL3ClockOut = RCC_PLL3_DIVQ;
  // PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL3Q;

  // if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
  //   Error_Handler();
  // }
}

#endif /* ARDUINO_GENERIC_H503RBTX */
