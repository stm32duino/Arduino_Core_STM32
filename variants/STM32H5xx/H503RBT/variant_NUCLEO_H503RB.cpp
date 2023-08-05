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
  PA_0,   // D0/A0
  PA_1,   // D1/A1
  PA_2,   // D2/A2
  PA_3,   // D3/A3
  PA_4,   // D4/A4
  PA_5,   // D5/A5
  PA_6,   // D6/A6
  PA_7,   // D7/A7
  PA_8,   // D8
  PA_9,   // D9
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13
  PA_14,  // D14
  PA_15,  // D15
  PB_0,   // D16/A8
  PB_1,   // D17/A9
  PB_2,   // D18
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_10,  // D25
  PB_12,  // D26
  PB_13,  // D27
  PB_14,  // D28
  PB_15,  // D29
  PC_0,   // D30/A10
  PC_1,   // D31/A11
  PC_2,   // D32/A12
  PC_3,   // D33/A13
  PC_4,   // D34/A14
  PC_5,   // D35/A15
  PC_6,   // D36
  PC_7,   // D37
  PC_8,   // D38
  PC_9,   // D39
  PC_10,  // D40
  PC_11,  // D41
  PC_12,  // D42
  PC_13,  // D43
  PC_14,  // D44
  PC_15,  // D45
  PD_2,   // D46
  PH_0,   // D47
  PH_1    // D48
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA3
  4,  // A4,  PA4
  5,  // A5,  PA5
  6,  // A6,  PA6
  7,  // A7,  PA7
  16, // A8,  PB0
  17, // A9,  PB1
  30, // A10, PC0
  31, // A11, PC1
  32, // A12, PC2
  33, // A13, PC3
  34, // A14, PC4
  35  // A15, PC5
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

WEAK void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  // Configure the main internal regulator output voltage
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  // Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInitTypeDef structure
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

  // Initializes the CPU, AHB and APB buses clocks
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  // Initializes the peripherals clock
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

// extern "C"
#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_NUCLEO_H503RB */