/*
 *******************************************************************************
 * Copyright (c) 2023, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_F412ZG)
#include "pins_arduino.h"

// Digital PinName array
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  PG_9,  //D0
  PG_14, //D1
  PF_15, //D2
  PE_13, //D3
  PF_14, //D4
  PE_11, //D5
  PE_9,  //D6
  PF_13, //D7
  PF_12, //D8
  PD_15, //D9
  PD_14, //D10
  PA_7,  //D11/A10
  PA_6,  //D12/A11
  PA_5,  //D13/A12
  PB_9,  //D14
  PB_8,  //D15
  PC_6,  //D16
  PB_15, //D17
  PB_13, //D18
  PB_12, //D19
  PA_15, //D20
  PC_7,  //D21
  PB_5,  //D22
  PB_3,  //D23
  PA_4,  //D24/A13
  PB_4,  //D25
  PB_6,  //D26
  PB_2,  //D27
  PD_13, //D28
  PD_12, //D29
  PD_11, //D30
  PE_2,  //D31
  PA_0,  //D32/A14
  PB_0,  //D33/A15 - LED_GREEN
  PE_0,  //D34
  PB_11, //D35
  PB_10, //D36
  PE_15, //D37
  PE_14, //D38
  PE_12, //D39
  PE_10, //D40
  PE_7,  //D41
  PE_8,  //D42
  PC_8,  //D43
  PC_9,  //D44
  PC_10, //D45
  PC_11, //D46
  PC_12, //D47
  PD_2,  //D48
  PG_2,  //D49
  PG_3,  //D50
  PD_7,  //D51
  PD_6,  //D52
  PD_5,  //D53
  PD_4,  //D54
  PD_3,  //D55
  PE_2,  //D56
  PE_4,  //D57
  PE_5,  //D58
  PE_6,  //D59
  PE_3,  //D60
  PF_8,  //D61
  PF_7,  //D62
  PF_9,  //D63
  PG_1,  //D64
  PG_0,  //D65
  PD_1,  //D66
  PD_0,  //D67
  PF_0,  //D68
  PF_1,  //D69
  PF_2,  //D70
  PB_7,  //D71 - LED_BLUE
  PB_14, //D72 - LED_RED
  PC_13, //D73 - USER_BTN
  PD_9,  //D74 - Serial Rx
  PD_8,  //D75 - Serial Tx
  PA_3,  //D76/A0
  PC_0,  //D77/A1
  PC_3,  //D78/A2
  PC_1,  //D79/A3
  PC_4,  //D80/A4
  PC_5,  //D81/A5
  PB_1,  //D82/A6
  PC_2,  //D83/A7
  PA_2,  //D84/A8
  PF_6,  //D85
  PA_1,  //D86/A9
  PF_4,  //D87
  PA_8,  //D88
  PA_9,  //D89
  PA_10, //D90
  PA_11, //D91
  PA_12, //D92
  PA_13, //D93
  PA_14, //D94
  PF_3,  //D95/A20
  PF_5,  //D96/A21
  PF_10, //D97/A22
  PC_14, //D98
  PC_15, //D99
  PD_10, //D100
  PE_1,  //D101
  PF_11, //D102
  PG_4,  //D103
  PG_5,  //D104
  PG_6,  //D105
  PG_7,  //D106
  PG_8,  //D107
  PG_10, //D108
  PG_11, //D109
  PG_12, //D110
  PG_13, //D111
  PG_15, //D112
  PH_0,  //D113
  PH_1   //D114
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  76, //A0
  77, //A1
  78, //A2
  79, //A3
  80, //A4
  81, //A5
  82, //A6
  83, //A7
  84, //A8
  86, //A9
  11, //A10
  12, //A11
  13, //A12
  24, //A13
  32, //A14
  33  //A15
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDIO | RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  PeriphClkInitStruct.SdioClockSelection = RCC_SDIOCLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_NUCLEO_F412ZG */
