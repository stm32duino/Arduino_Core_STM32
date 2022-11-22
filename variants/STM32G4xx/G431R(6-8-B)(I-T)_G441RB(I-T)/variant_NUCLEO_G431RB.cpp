/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_G431RB)


#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  // CN9
  PC_5,  //D0/A12
  PC_4,  //D1/A13
  PA_10, //D2
  PB_3,  //D3
  PB_5,  //D4
  PB_4,  //D5
  PB_10, //D6
  PA_8,  //D7
  // CN5
  PA_9,  //D8
  PC_7,  //D9
  PB_6,  //D10
  PA_7,  //D11/A18
  PA_6,  //D12/A19
  PA_5,  //D13/A20/LED
  PB_9,  //D14
  PB_8,  //D15
  // CN7 Left Side
  PC_10, //D16
  PC_12, //D17
  PA_13, //D18/SWDIO
  PA_14, //D19/SWCLK
  PA_15, //D20
  PB_7,  //D21
  PC_13, //D22
  PC_14, //D23
  PC_15, //D24
  PF_0,  //D25/A14
  PF_1,  //D26/A15
  PC_2,  //D27/A16
  PC_3,  //D28/A17
  // CN7 Right Side
  PD_2,  //D29
  PC_11, //D30
  // CN10 Left Side
  PC_9,  //D31
  // CN8
  PA_0,  //D32/A0
  PA_1,  //D33/A1
  PA_4,  //D34/A2
  PB_0,  //D35/A3
  PC_1,  //D36/A4
  PC_0,  //D37/A5
  // CN10 Right side
  PB_14, //D38/A6
  PB_15, //D39/A7
  PB_1,  //D40/A8
  PB_2,  //D41/A9
  PB_11, //D42/A10
  PB_12, //D43/A11
  PB_13, //D44
  PA_11, //D45
  PA_12, //D46
  PC_6,  //D47
  PC_8,  //D48
  PA_2,  //D49/A21
  PA_3   //D50/A22
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  32, // A0
  33, // A1
  34, // A2
  35, // A3
  36, // A4
  37, // A5
  38, // A6
  39, // A7
  40, // A8
  41, // A9
  42, // A10
  43, // A11
  0,  // A12
  1,  // A13
  25, // A14
  26, // A15
  27, // A16
  28, // A17
  11, // A18
  12, // A19
  13, // A20
  49, // A21
  50  // A22
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
  * @brief  System Clock Configuration
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
#ifdef USBCON
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};
#endif

  /* Configure the main internal regulator output voltage */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK) {
    Error_Handler();
  }

#ifdef USBCON
  /* Initializes the peripherals clocks */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
#endif
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ARDUINO_NUCLEO_G431RB */
