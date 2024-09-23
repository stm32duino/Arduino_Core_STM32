/*
 *******************************************************************************
 * Copyright (c) 2024, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_WEACT_H562RG)
#include "pins_arduino.h"
#include "Arduino.h"
// Digital PinName array
const PinName digitalPin[] = {
  PC_14,  // D0
  PC_0,   // D1/A0
  PC_2,   // D2/A1
  PA_0,   // D3/A2
  PA_2,   // D4/A3
  PA_4,   // D5/A4
  PA_6,   // D6/A5
  PC_4,   // D7/A6
  PB_0,   // D8/A7
  PB_2,   // D9
  PC_13,  // D10
  PC_15,  // D11
  PC_1,   // D12/A8
  PC_3,   // D13/A9
  PA_1,   // D14/A10
  PA_3,   // D15/A11
  PA_5,   // D16/A12
  PA_7,   // D17/A13
  PC_5,   // D18/A14
  PB_1,   // D19/A15
  PB_10,  // D20
  PB_7,   // D21
  PB_5,   // D22
  PB_3,   // D23
  PC_12,  // D24
  PC_10,  // D25
  PA_12,  // D26
  PA_10,  // D27
  PA_8,   // D28
  PC_8,   // D29
  PC_6,   // D30
  PB_14,  // D31
  PB_12,  // D32
  PB_8,   // D33
  PB_6,   // D34
  PB_4,   // D35
  PD_2,   // D36
  PC_11,  // D37
  PA_15,  // D38
  PA_11,  // D39
  PA_9,   // D40
  PC_9,   // D41
  PC_7,   // D42
  PB_15,  // D43
  PB_13,  // D44
  PA_13,  // D45
  PA_14,  // D46
  PH_0,   // D47
  PH_1    // D48
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  1,  // A0,  PC0
  2,  // A1,  PC2
  3,  // A2,  PA0
  4,  // A3,  PA2
  5,  // A4,  PA4
  6,  // A5,  PA6
  7,  // A6,  PC4
  8,  // A7,  PB0
  12, // A8,  PC1
  13, // A9,  PC3
  14, // A10, PA1
  15, // A11, PA3
  16, // A12, PA5
  17, // A13, PA7
  18, // A14, PC5
  19  // A15, PB1
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE ;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 62;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 4096;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_2);
  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC1 | RCC_PERIPHCLK_ADCDAC
                                             | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLL2_SOURCE_HSE;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 32;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 8;
  PeriphClkInitStruct.PLL2.PLL2R = 4;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2_VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVQ | RCC_PLL2_DIVR;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PLL2Q;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLL2R;
  PeriphClkInitStruct.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_PLL2R;
  PeriphClkInitStruct.PLL3.PLL3Source = RCC_PLL3_SOURCE_HSE;
  PeriphClkInitStruct.PLL3.PLL3M = 1;
  PeriphClkInitStruct.PLL3.PLL3N = 48;
  PeriphClkInitStruct.PLL3.PLL3P = 2;
  PeriphClkInitStruct.PLL3.PLL3Q = 8;
  PeriphClkInitStruct.PLL3.PLL3R = 2;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3_VCIRANGE_0;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3_VCORANGE_MEDIUM;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.PLL3.PLL3ClockOut = RCC_PLL3_DIVQ;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL3Q;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_WEACT_H562RG */
