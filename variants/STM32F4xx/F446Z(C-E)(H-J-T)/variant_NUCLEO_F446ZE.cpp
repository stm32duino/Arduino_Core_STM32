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
#if defined(ARDUINO_NUCLEO_F446ZE)

#include "pins_arduino.h"

// Pin number
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
  PA_7,  //D11
  PA_6,  //D12
  PA_5,  //D13
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
  PA_4,  //D24
  PB_4,  //D25
  PB_6,  //D26
  PB_2,  //D27
  PD_13, //D28
  PD_12, //D29
  PD_11, //D30
  PE_2,  //D31
  PA_0,  //D32
  PB_0,  //D33/A23 - LED_GREEN
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
  NC,    //D71
  NC,    //D72
  PB_7,  //D73 - LED_BLUE
  PB_14, //D74 - LED_RED
  PC_13, //D75 - USER_BTN
  PD_9,  //D76 - Serial Rx
  PD_8,  //D77 - Serial Tx
  PA_3,  //D78/A0
  PC_0,  //D79/A1
  PC_3,  //D80/A2
  PF_3,  //D81/A3
  PF_5,  //D82/A4
  PF_10, //D83/A5
  PB_1,  //D84/A6
  PC_2,  //D85/A7
  PF_4,  //D86/A8
  PF_6,  //D87/A9
  PA_1,  //D88/A18
  PA_2,  //D89/A19
  PA_8,  //D90
  PA_9,  //D91
  PA_10, //D92
  PA_11, //D93
  PA_12, //D94
  PA_13, //D95
  PA_14, //D96
  PC_1,  //D97/A20
  PC_4,  //D98/A21
  PC_5,  //D99/A22
  PC_14, //D100
  PC_15, //D101
  PD_10, //D102
  PE_1,  //D103
  PF_11, //D104
  PG_4,  //D105
  PG_5,  //D106
  PG_6,  //D107
  PG_7,  //D108
  PG_8,  //D109
  PG_10, //D110
  PG_11, //D111
  PG_12, //D112
  PG_13, //D113
  PG_15, //D114
  PH_0,  //D115
  PH_1   //D116
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  78, //A0
  79, //A1
  80, //A2
  81, //A3
  82, //A4
  83, //A5
  84, //A6
  85, //A7
  86, //A8
  87, //A9
  11, //A10
  12, //A11
  13, //A12
  24, //A13
  32, //A14
  61, //A15
  62, //A16
  63, //A17
  88, //A18
  89, //A19
  97, //A20
  98, //A21
  99, //A22
  33  //A23
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

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
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDIO | RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIM = 4;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 96;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLSAIP;
  PeriphClkInitStruct.SdioClockSelection = RCC_SDIOCLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_L476RG */
