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
#if defined(ARDUINO_GENERIC_NODE_SE_TTI)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_3,   // D0/USR_BTN/SWO/RTS
  PA_15,  // D1/BUZZER
  PA_2,   // D2/TX
  PA_3,   // D3/RX
  PA_11,  // D4/SDA2/A1
  PA_12,  // D5/SCL2/A2
  PA_13,  // D6/A3/SWDIO
  PA_14,  // D7/A4/SWCLK
  PA_0,   // D8/FE_CTRL1
  PA_1,   // D9/FE_CTRL2
  PA_4,   // D10/CS1 FLASH
  PA_5,   // D11/SCK1
  PA_6,   // D12/MISO
  PA_7,   // D13/MOSI
  PA_8,   // D14/ACCEL_INT2
  PA_9,   // D15/SCL1
  PA_10,  // D16/SDA1
  PB_0,   // D17/VDD_TCX0
  PB_2,   // D18/VABAT_ADC/A0
  PB_4,   // D19/VBAT_READ_EN
  PB_5,   // D20/LED_RED
  PB_6,   // D21/LED_GREEN
  PB_7,   // D22/LED_BLUE
  PB_8,   // D23/FE_CTRL3
  PB_12,  // D24/LS1_SENSORS_EN
  PC_13,  // D25/LS2_FLASH_EN
  PH_3,   // D26/BOOT0
  PC_14,  // D27/OSC32-IN
  PC_15   // D28/OSC32-OUT
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  18, // A0,  PB2
  4,  // A1,  PA11
  5,  // A2,  PA12
  6,  // A3,  PA13
  7   // A4,  PA14
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3 | RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
                                | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_GENERIC_NODE_SE_TTI */
