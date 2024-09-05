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
#if defined(ARDUINO_NUCLEO_U083RC)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_3,  // D0
  PA_2,  // D1
  PA_10, // D2
  PB_3,  // D3
  PB_5,  // D4
  PB_4,  // D5
  PB_10, // D6
  PA_8,  // D7
  PA_9,  // D8
  PC_7,  // D9
  PB_6,  // D10/A6
  PA_7,  // D11/A7
  PA_6,  // D12/A8
  PA_5,  // D13
  PB_9,  // D14
  PB_8,  // D15
  PA_0,  // D16/A0
  PA_1,  // D17/A1
  PA_4,  // D18/A2
  PB_0,  // D19/A3
  PC_1,  // D20/A4
  PC_0,  // D21/A5
  PC_10, // D22
  PC_12, // D23
  PA_13, // D24
  PA_14, // D25
  PA_15, // D26
  PB_7,  // D27
  PC_13, // D28
  PC_14, // D29
  PC_15, // D30
  PF_0,  // D31
  PF_1,  // D32
  PC_2,  // D33/A9
  PC_3,  // D34/A10
  PC_11, // D35
  PD_2,  // D36
  PC_9,  // D37
  PC_8,  // D38
  PC_6,  // D39/A11
  PC_5,  // D40
  PA_12, // D41
  PA_11, // D42
  PB_12, // D43
  PB_11, // D44
  PB_2,  // D45
  PB_1,  // D46/A12
  PB_15, // D47
  PB_14, // D48
  PB_13, // D49
  PC_4,  // D50/A13
  PF_2,  // D51
  PF_3   // D52
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0,  PA0
  17, // A1,  PA1
  18, // A2,  PA4
  19, // A3,  PB0
  20, // A4,  PC1
  21, // A5,  PC0
  11, // A6,  PA7
  12, // A7,  PA6
  13, // A8,  PA5
  33, // A9,  PC2
  34, // A10, PC3
  40, // A11, PC5
  46, // A12, PB1
  50  // A13, PC4
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 7;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_LPUART2
                                       | RCC_PERIPHCLK_LPUART3 | RCC_PERIPHCLK_USB;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInit.Lpuart2ClockSelection = RCC_LPUART2CLKSOURCE_HSI;
  PeriphClkInit.Lpuart3ClockSelection = RCC_LPUART3CLKSOURCE_HSI;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;


  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }


}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_U083RC */
