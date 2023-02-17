/*
 *******************************************************************************
 * Copyright (c) 2011-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_DISCO_F100RB)

#include "pins_arduino.h"

// Pin number following UM0919 table 4,5 and 6
const PinName digitalPin[] = {
  // P1 connector
  PC_13, //D0
  PC_0,  //D1
  PC_1,  //D2
  PC_2,  //D3
  PC_3,  //D4
  PA_0,  //D5 - User button
  PA_1,  //D6
  PA_2,  //D7
  PA_3,  //D8
  PA_4,  //D9
  PA_5,  //D10
  PA_6,  //D11
  PA_7,  //D12
  PC_4,  //D13
  PC_5,  //D14
  PB_0,  //D15
  PB_1,  //D16
  PB_2,  //D17
  // P2 connector
  PC_6,  //D18
  PC_7,  //D19
  PC_8,  //D20 - LED blue
  PC_9,  //D21 - LED green
  PA_8,  //D22
  PA_9,  //D23
  PA_10, //D24
  PA_11, //D25
  PA_12, //D26
  PA_13, //D27
  PA_14, //D28
  PA_15, //D29
  PC_10, //D30
  PC_11, //D31
  PC_12, //D32
  PD_2,  //D33
  PB_3,  //D34
  PB_4,  //D35
  PB_5,  //D36 - I2C SCL
  PB_6,  //D37 - I2C SDA
  PB_7,  //D38
  PB_8,  //D39
  PB_9,  //D40
  // P3 connector
  PB_10, //D41
  PB_11, //D42
  PB_12, //D43 - SPI SS
  PB_13, //D44 - SPI SCLK
  PB_14, //D45 - SPI MISO
  PB_15  //D46 - SPI MOSI
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  1,  //A0
  2,  //A1
  3,  //A2
  4,  //A3
  5,  //A4
  6,  //A5
  7,  //A6
  8,  //A7
  9,  //A8
  10, //A9
  11, //A10
  12, //A11
  13, //A12
  14, //A13
  15, //A14
  16  //A15
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 24000000
  *            HCLK(Hz)                       = 24000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            PLL_Source                     = HSE
  *            PLL_Mul                        = 6
  *            Flash Latency(WS)              = 0
  *            ADC Prescaler                  = 2
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_DISCO_F100RB */
