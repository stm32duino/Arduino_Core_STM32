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

#if defined(ARDUINO_NUCLEO_H503RB)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_15  // D0
  PA_14  // D1
  PA_10  // D2
  PB_3   // D3
  PB_5   // D4
  PB_4   // D5
  PB_10  // D6
  PA_8   // D7
  PC_7   // D8
  PC_6   // D9
  PC_9   // D10
  PA_7   // D11
  PA_6   // D12
  PA_5   // D13
  PB_7   // D14
  PB_6   // D15/A0
  PA_0   // D16/A1
  PA_1   // D17/A2
  PA_2   // D18/A3
  PB_0   // D19/A4
  PC_1   // D20/A5
  PC_0   // D21
  PA_3   // D22
  PA_4   // D23
  PA_9   // D24
  PA_13  // D25
  PC_2   // D26
  PC_3   // D27
  PC_5   // D28
  PC_8   // D29
  PC_10  // D30
  PC_11  // D31
  PC_12  // D32
  PC_13  // D33
  PC_14  // D34
  PC_15  // D35
  PD_2   // D36
  PH_0   // D37
  PH_1   // D38
  PA_12  // D39/A6
  PA_11  // D40/A7
  PB_12  // D41/A8
  PB_2   // D42/A9
  PB_1   // D43/A10
  PB_15  // D44/A11
  PB_14  // D45/A12
  PB_13  // D46/A13
  PC_4   // D47/A14
  PB_8   // D48/A15
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  15,  // A0,  PA0
  16,  // A1,  PA1
  17,  // A2,  PA2
  18,  // A3,  PB0
  19,  // A4,  PC1
  20,  // A5,  PC0
  39,  // A6,  PA12
  40,  // A7,  PA11
  41,  // A8,  PB12
  42,  // A9,  PB2
  43,  // A10, PB1
  44,  // A11, PB15
  45,  // A12, PB14
  46,  // A13, PB13
  47,  // A14, PC4
  48   // A15, PB8
};

#ifdef __cplusplus
extern "C" {
#endif

/**
* @note [How to generate PLL clock]
* <SOURCE>
*   HSE      8 MHz ... STLINK MCO output
*   HSE     24 MHz ... on-board X3 (default)
*   HSE   4~50 MHz ... prepare your own external clock
*   LSE 32.768 kHz ... on-board X2
*   HSI     64 MHz ... internal clock
*   HSI48   48 MHz ... internal clock for USB/RNG with recovery
*   LSI 32.768 kHz ... internal clock
*   CSI      4 MHz ... internal clock for low power
*
* <MULTIPLEXER>
*   SOURCE / PLLM * PLLN
*
* <TARGRT>
*   PLL ... MULTIPLEXER / PLLP
*
* - Default CPU clock: 24(HSE) / 12(PLLM) * 250(PLLN) / 2(PLLP) ... 250 MHz
* - PLL3 supports only H562/H563/H573.
*/

WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /* Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInitTypeDef structure */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIGITAL;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 250;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the peripherals clock */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_OSPI | RCC_PERIPHCLK_SDMMC1 | RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLL1Q;
  PeriphClkInitStruct.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_HCLK;
  PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_HCLK;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_NUCLEO_H503RB */