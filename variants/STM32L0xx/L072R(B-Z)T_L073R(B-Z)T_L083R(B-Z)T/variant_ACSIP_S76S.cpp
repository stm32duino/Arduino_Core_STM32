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
#if defined(ARDUINO_ACSIP_S76S)

#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PC_0,  // D0/A0
  PC_1,  // D1/A1
  PC_2,  // D2/A2
  PC_3,  // D3/A3
  PA_0,  // D4/A4
  PA_2,  // D5/A5
  PA_3,  // D6/A6
  PA_4,  // D7/A7
  PA_5,  // D8/A8
  PA_6,  // D9/A9
  PA_7,  // D10/A10
  PC_4,  // D11/A11
  PC_5,  // D12/A12
  PB_0,  // D13/A13
  PB_1,  // D14/A14
  PC_6,  // D15
  PC_7,  // D16
  PC_8,  // D17
  PC_9,  // D18
  PA_1,  // D19/A15
  PA_8,  // D20
  PA_10, // D21
  PA_9,  // D22
  PA_11, // D23
  PA_12, // D24
  PA_13, // D25
  PA_14, // D26
  PC_10, // D27
  PC_11, // D28
  PC_12, // D29
  PD_2,  // D30
  PB_5,  // D31
  PB_6,  // D32
  PB_7,  // D33
  PB_8,  // D34
  PA_15, // D35
  PB_3,  // D36
  PB_4,  // D37
  PB_9,  // D38
  PB_10, // D39
  PB_11, // D40
  PB_12, // D41
  PB_13, // D42
  PB_14, // D43
  PB_15, // D44
  PC_13, // D45
  PC_14, // D46
  PC_15, // D47
  PH_0,  // D48
  PH_1   // D49
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PC0
  1,  // A1,  PC1
  2,  // A2,  PC2
  3,  // A3,  PC3
  4,  // A4,  PA0
  5,  // A5,  PA2
  6,  // A6,  PA3
  7,  // A7,  PA4
  8,  // A8,  PA5
  9,  // A9,  PA6
  10, // A10, PA7
  11, // A11, PC4
  12, // A12, PC5
  13, // A13, PB0
  14, // A14, PB1
  19  // A15, PA1
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_ACSIP_S76S */
