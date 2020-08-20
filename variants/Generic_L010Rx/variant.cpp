/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Digital PinName array
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  //PX_n, //Dx
  PA_0, //  D0  / A0
  PA_1, //  D1  / A1
  PA_2, //  D2  / A2
  PA_3, //  D3  / A3
  PA_4, //  D4  / A4
  PA_5, //  D5  / A5
  PA_6, //  D6  / A6
  PA_7, //  D7  / A7
  PA_8, //  D8
  PA_9, //  D9
  PA_10, // D10
  PA_11, // D11
  PA_12, // D12
  PA_13, // D13
  PA_14, // D14
  PA_15, // D15

  PB_0, //  D16  / A8
  PB_1, //  D17  / A9
  PB_2, //  D18
  PB_3, //  D19
  PB_4, //  D20
  PB_5, //  D21
  PB_6, //  D22
  PB_7, //  D23
  PB_8, //  D24
  PB_9, //  D25
  PB_10, // D26
  PB_11, // D27
  PB_12, // D28
  PB_13, // D29
  PB_14, // D30
  PB_15, // D31

  PC_0, //  D32  / A10
  PC_1, //  D33  / A11
  PC_2, //  D34  / A12
  PC_3, //  D35  / A13
  PC_4, //  D36  / A14
  PC_5, //  D37  / A15
  PC_6, //  D38
  PC_7, //  D39
  PC_8, //  D40
  PC_9, //  D41
  PC_10, // D42
  PC_11, // D43
  PC_12, // D44
  PC_13, // D45

  PD_2, //  D46
};

// If analog pins are not contiguous in the digitalPin array:
// Add the analogInputPin array without defining NUM_ANALOG_FIRST
// Analog (Ax) pin number array
// where x is the index to retrieve the digital pin number
const uint32_t analogInputPin[] = {
  //PXn, //Ax = Dx
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  16,
  17,
  32,
  33,
  34,
  35,
  36,
  37,
};

#ifdef __cplusplus
}
#endif

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
  // Here copy the desired System Clock Configuration
  // It could be generated thanks STM32CubeMX after code generation for Toolchain/IDE: 'SW4STM32',
  // available in src/main.c
  // or
  // copied from a STM32CubeYY project examples
  // where 'YY' could be F0, F1, F2, F3, F4, F7, G0, G4, H7, L0, L1, L4, MP1, WB

  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_8;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_RTC
                                       | RCC_PERIPHCLK_LPTIM1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.LptimClockSelection = RCC_LPTIM1CLKSOURCE_PCLK;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

#ifdef __cplusplus
}
#endif
