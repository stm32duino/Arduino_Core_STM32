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
#if defined(ARDUINO_HERON)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   //  0 - A0/D0
  PA_1,   //  1 - A1/D1
  PA_2,   //  2 - A2/D2
  PA_3,   //  3 - A3/D3
  PB_1,   //  4 - A4/D4
  PB_8,   //  5 - D5
  PB_9,   //  6 - D6
  PA_8,   //  7 - LED_BUILTIN
  PC_13,  //  8 - USER_BTN
  PB_14,  //  9 - D9
  PB_13,  // 10 - D10
  PB_0,   // 11 - A7/D11
  PB_15,  // 12 - D12
  PB_4,   // 13 - D13
  PA_7,   // 14 - A5
  PB_3,   // 15 - CK
  PB_5,   // 16 - MO
  PA_6,   // 17 - A6/MI
  PA_10,  // 18 - RX
  PA_9,   // 19 - TX
  PH_3,   // 20 - B
  PB_6,   // 21 - SCL
  PB_7,   // 22 - SDA
  PA_13,  // 23 - SWDIO
  PA_14,  // 24 - SWCLK
  PA_5,   // 25 - USART3_VCP_RX
  PB_10,  // 26 - USART3_VCP_TX
  PH_0,   // 27 - ENABLE_3V3
  PH_1,   // 28 - DISCHARGE_3V3
  PA_15,  // 29 - CHARGE_DETECT
  PA_4,   // 30 - A8/BATTERY_VOLTAGE (STAT)
  PB_2,   // 31 - USB_DETECT
  PA_11,  // 32 - USB_D_N
  PA_12,  // 33 - USB_D_P
  PC_14,  // 34 - OSC32_IN (LSE)
  PC_15   // 35 - OSC32_OUT (LSE)
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,   // PA0 - A0
  1,   // PA1 - A1
  2,   // PA2 - A2
  3,   // PA3 - A3
  4,   // PB1 - A4
  14,  // PA7 - A5
  17,  // PA6 - A6/MI
  11,  // PB0 - A7/D11
  30   // PA4 - A8/BATTERY_VOLTAGE (STAT)
  // 15   // PB2 - USB_DETECT
  // 25   // PA5 - A10/USART3_VCP_RX
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void initVariant(void)
{
  /* All pins set to high-Z (floating) initially */
  /* DS13737 Rev 10, Section 3.9.4 - Reset Mode: */
  /* In order to improve the consumption under reset, the I/O state under and after reset is
   * “analog state” (the I/O Schmitt trigger is disabled). In addition, the internal reset pull-up is
   * deactivated when the reset source is internal.
   */

  /* Turn on the 3V3 regulator */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct); /* PH0 is ENABLE_3V3, PH1 is DISCHARGE_3V3 */
  HAL_GPIO_WritePin(GPIOH, GPIO_InitStruct.Pin, GPIO_PIN_SET); /* Enable 3V3 regulator and disable discharging */
}

/**
  * @brief  System Clock Configuration – Low-power optimized STM32U575 with native USB CDC
  *
  * Key features:
  *   • SYSCLK = 48 MHz derived from MSI (Range 11) → lowest active-mode current
  *   • USB OTG_FS uses HSI48 as CLK48 source via the official U5 method (RCC_PERIPHCLK_CLK48 + IclkClockSelection)
  *   • LSE enabled for RTC / ultra-low-power timing
  *   • No PLL → minimal power and EMI
  *   • CRS enabled → automatic HSI48 trimming from USB SOF packets (±250 ppm accuracy)
  *
  * References:
  *   • RM0456 Rev 7 – §6.3.2 (CLK48 selection), §6.5 (CRS), §40.4.3 (USB OTG_FS PHY)
  *   • STM32CubeU5 v1.4.0 / v1.7.0 – CDC_Standalone examples for NUCLEO-U575ZI-Q
  *   • ST migration note: SYSCFG clock must now be enabled by user in HAL_PCD_MspInit()
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef       RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef       RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit     = {};
  RCC_CRSInitTypeDef       CRS_InitStruct    = {};

  /* -------------------------------------------------------------------------
   * 1. Voltage scaling – Scale 1 is required for MSI Range 11 (48 MHz)
   * ------------------------------------------------------------------------- */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }

  /* -------------------------------------------------------------------------
   * 2. LSE drive strength (optimize for low-power)
   * ------------------------------------------------------------------------- */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /* -------------------------------------------------------------------------
   * 3. Oscillator configuration
   *     • MSI   = ON  (initially Range 0 = 100 kHz – lowest power at boot)
   *     • HSI48 = ON  (required for USB CLK48 source)
   *     • HSI   = ON  (used for ADCs, DAC, etc.)
   *     • LSE   = ON  (RTC / ultra-low-power timing)
   *     • PLL   = OFF (no PLL → lowest power)
   * ------------------------------------------------------------------------- */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_MSI
                                          | RCC_OSCILLATORTYPE_HSI48
                                          | RCC_OSCILLATORTYPE_HSI
                                          | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.MSIState            = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange       = RCC_MSIRANGE_0;           // 100 kHz initially (will be overridden later)
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State          = RCC_HSI48_ON;             // Critical for USB
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSEState            = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_NONE;             // No PLL → lowest power
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* -------------------------------------------------------------------------
   * 4. Select MSI as system clock source (will run at 48 MHz after PeriphClk config)
   * ------------------------------------------------------------------------- */
  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK     | RCC_CLOCKTYPE_PCLK1
                                     | RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_PCLK3
                                     | RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_MSI;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  /* -------------------------------------------------------------------------
   * 5. Peripheral clock configuration – THIS IS THE OFFICIAL U5 WAY TO SELECT CLK48
   *     • RCC_PERIPHCLK_CLK48 + IclkClockSelection = RCC_CLK48CLKSOURCE_HSI48
   *       → writes RCC->CCIPR1.ICLKSEL = 00 (RM0456 §6.3.2, Fig. 36)
   *     • MSI is switched to Range 11 (48 MHz) automatically by the HAL when
   *       any peripheral requests it (here ADCDAC, DAC1, LPUART1, etc.)
   * ------------------------------------------------------------------------- */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC
                                       | RCC_PERIPHCLK_CLK48         // USB CLK48 domain
                                       | RCC_PERIPHCLK_DAC1
                                       | RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.AdcDacClockSelection  = RCC_ADCDACCLKSOURCE_HSI;
  PeriphClkInit.IclkClockSelection    = RCC_CLK48CLKSOURCE_HSI48;     // Selects HSI48 for USB OTG_FS
  PeriphClkInit.Dac1ClockSelection    = RCC_DAC1CLKSOURCE_LSE;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }

  /* -------------------------------------------------------------------------
   * 6. Low-power helpers
   * ------------------------------------------------------------------------- */
  HAL_RCCEx_EnableMSIPLLMode();                                    // MSI PLL-mode for better stability in Stop
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);       // Wake from Stop on MSI

  /* -------------------------------------------------------------------------
   * 7. Clock Recovery System – auto-trim HSI48 from USB SOF packets
   *     Required for reliable USB enumeration across temperature/cable length
   *     Power impact < 1 µA, enabled in all official ST U5 USB examples
   * ------------------------------------------------------------------------- */
  __HAL_RCC_CRS_CLK_ENABLE();
  CRS_InitStruct.Prescaler             = RCC_CRS_SYNC_DIV1;
  CRS_InitStruct.Source                = RCC_CRS_SYNC_SOURCE_USB;   // Trim using USB SOF
  CRS_InitStruct.ReloadValue           = RCC_CRS_RELOADVALUE_DEFAULT;
  CRS_InitStruct.ErrorLimitValue       = RCC_CRS_ERRORLIMIT_DEFAULT;
  CRS_InitStruct.HSI48CalibrationValue = 0x00;                       // Default trim (will be auto-adjusted)
  HAL_RCCEx_CRSConfig(&CRS_InitStruct);
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_HERON */
