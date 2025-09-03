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
#if defined(ARDUINO_DISCO_F411VE)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  //P1 connector Right side
  PC_0,  //D0/A10
  PC_2,  //D1/A12
  PA_0,  //D2/A0
  PA_2,  //D3/A2
  PA_4,  //D4/A4
  PA_6,  //D5/A6
  PC_4,  //D6/A14
  PB_0,  //D7/A8
  PB_2,  //D8
  PE_8,  //D9
  PE_10, //D10
  PE_12, //D11
  PE_14, //D12
  PB_10, //D13
  PB_12, //D14
  PB_14, //D15
  PD_8,  //D16
  PD_10, //D17
  PD_12, //D18
  PD_14, //D19
  //P2 connector Left side
  PH_0,  //D20
  PC_14, //D21
  PE_6,  //D22
  PE_4,  //D23
  PE_2,  //D24
  PE_0,  //D25
  PB_8,  //D26
  PB_6,  //D27
  PB_4,  //D28
  PD_7,  //D29
  PD_5,  //D30
  PD_3,  //D31
  PD_1,  //D32
  PC_12, //D33
  PC_10, //D34
  PA_14, //D35
  PA_10, //D36
  PA_8,  //D37
  PC_8,  //D38
  PC_6,  //D39
  //P1 Connector Left Side
  PC_1,  //D40/A11
  PC_3,  //D41/A13
  PA_1,  //D42/A1
  PA_3,  //D43/A3
  PA_5,  //D44/A5
  PA_7,  //D45/A7
  PC_5,  //D46/A15
  PB_1,  //D47/A9
  PE_7,  //D48
  PE_9,  //D49
  PE_11, //D50
  PE_13, //D51
  PE_15, //D52
  PB_13, //D53
  PB_15, //D54
  PD_9,  //D55
  PD_11, //D56
  PD_13, //D57
  PD_15, //D58
  //P2 connector Right side
  PH_1,  //D59
  PC_15, //D60
  PC_13, //D61
  PE_5,  //D62
  PE_3,  //D63
  PE_1,  //D64
  PB_9,  //D65
  PB_7,  //D66
  PB_5,  //D67
  PB_3,  //D68
  PD_6,  //D69
  PD_4,  //D70
  PD_2,  //D71
  PD_0,  //D72
  PC_11, //D73
  PA_15, //D74
  PA_13, //D75
  PA_9,  //D76
  PC_9,  //D77
  PC_7,  //D78
  //CN5 USB USER connector
  PA_11, //D79
  PA_12  //D80
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  2,  //A0
  42,  //A1
  3,  //A2
  43, //A3
  4, //A4
  44, //A5
  5, //A6
  45, //A7
  7,  //A8
  47, //A9
  0,  //A10
  40, //A11
  1,  //A12
  41, //A13
  6,  //A14
  46  //A15
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief System Clock Configuration
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_DISCO_F411VE */
