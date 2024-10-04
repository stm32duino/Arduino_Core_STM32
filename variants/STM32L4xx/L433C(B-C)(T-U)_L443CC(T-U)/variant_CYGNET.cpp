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

#if defined(ARDUINO_CYGNET)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // 0 - D0/A0
  PA_1,   // 1 - D1/A1
  PA_2,   // 2 - D2/A2
  PA_3,   // 3 - D3/A3
  PB_1,   // 4 - D4/A4
  PB_8,   // 5 - D5
  PB_9,   // 6 - D6
  PA_4,   // 7 - BAT_VOLTAGE
  PA_8,   // 8 - LED_BUILTIN
  PB_14,  // 9 - D9
  PB_13,  // 10 - D10
  PB_0,   // 11 - D11
  PB_15,  // 12 - D12
  PB_4,   // 13 - D13
  PA_5,   // 14 - CK
  PA_6,   // 15 - MI
  PA_7,   // 16 - A5
  PA_9,   // 17 - TX
  PA_10,  // 18 - RX
  PA_11,  // 19 - USB_DM
  PA_12,  // 20 - USB_DP
  PA_13,  // 21 - SWDIO
  PA_14,  // 22 - SWCLK
  PA_15,  // 23 - CHARGE_DETECT
  PB_3,   // 24 - USB_DETECT
  PB_5,   // 25 - MO
  PB_6,   // 26 - SCL
  PB_7,   // 27 - SDA
  PB_10,  // 28 - LPUART1_VCP_RX
  PB_11,  // 29 - LPUART1_VCP_TX
  PC_13,  // 30 - USER_BTN
  PC_14,  // 31 - OSC32_IN
  PC_15,  // 32 - OSC32_OUT
  PH_0,   // 33 - ENABLE_3V3
  PH_1,   // 34 - DISCHARGE_3V3
  PH_3    // 35 - B
};

// Analog (Ax) to digital pin number array
const uint32_t analogInputPin[] = {
  0,  // PA0, A0
  1,  // PA1, A1
  2,  // PA2, A2
  3,  // PA3, A3
  4,  // PB1, A4
  16, // PA7, A5
  7   // PA4, BAT_VOLTAGE
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void initVariant(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  // Init lines that we'll be using below
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* Set DISCHARGE_3V3 as well as the pins we're not initially using to FLOAT */
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct); /* PH1 DISCHARGE_3V3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); /* PB3 is USB_DETECT */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); /* PA15 is CHARGE_DETECT */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); /* PA4 is BAT_VOLTAGE */

  /* Turn on the 3V3 regulator */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOH, GPIO_InitStruct.Pin, GPIO_PIN_SET);
}

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE
                                     | RCC_OSCILLATORTYPE_MSI
                                     | RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  // RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the Peripheral clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_SDMMC1
                                       | RCC_PERIPHCLK_ADC /* | RCC_PERIPHCLK_OSPI */;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
  // PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_MSI;
  PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_MSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();

  /** Ensure that MSI is wake-up system clock
  */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_CYGNET */
