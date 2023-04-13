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
#if defined(ARDUINO_RAK3172_MODULE)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0
  PA_1,   // D1
  PA_2,   // D2     - USART2/LPUART1 TX
  PA_3,   // D3     - USART2/LPUART1 RX
  PA_4,   // D4     - SPI_NSS
  PA_5,   // D5     - SPI_SCK
  PA_6,   // D6     - SPI_MISO
  PA_7,   // D7     - SPI_MOSI
  PA_8,   // D8
  PA_9,   // D9
  PA_10,  // D10/A3
  PA_11,  // D11/A7 - I2C_SDA
  PA_12,  // D12/A8 - I2C_SCL
  PA_13,  // D13/A5 - SWDIO
  PA_14,  // D14/A6 - SWCLK
  PA_15,  // D15/A4
  PB_2,   // D16/A2
  PB_3,   // D17/A0
  PB_4,   // D18/A1
  PB_5,   // D19
  PB_6,   // D20    - USART1_TX
  PB_7,   // D21    - USAR1_RX
  PB_8,   // D22
  PB_12,  // D23
  PC_13,  // D24
  PH_3    // D25    - BOOT0
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  17, // A0,  PB3
  18, // A1,  PB4
  16, // A2,  PB2
  10, // A3,  PA10
  15, // A4,  PA15
  13, // A5,  PA13
  14, // A6,  PA14
  11, // A7,  PA11
  12  // A8,  PA12
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
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

#endif /* ARDUINO_RAK3172_MODULE */
