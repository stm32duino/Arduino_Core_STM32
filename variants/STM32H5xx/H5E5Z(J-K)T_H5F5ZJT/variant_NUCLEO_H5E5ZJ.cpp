/*
 *******************************************************************************
 * Copyright (c) 2020-2026, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_H5E5ZJ)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_8,  //D0
  PB_4,  //D1
  PA_10, //D2
  PF_1,  //D3
  PD_3,  //D4
  PG_15, //D5
  PF_3,  //D6
  PE_9,  //D7/A6
  PA_9,  //D8
  PF_4,  //D9
  PE_11, //D10/A7
  PE_14, //D11/A8
  PE_13, //D12/A9
  PE_12, //D13/A10
  PG_6,  //D14
  PF_5,  //D15
  PA_6,  //D16/A0
  PA_7,  //D17/A1
  PA_4,  //D18/A2
  PB_0,  //D19/A3
  PF_12, //D20/A4
  PF_11, //D21/A5
  PA_3,  //D22
  PF_0,  //D23
  PE_5,  //D24
  PC_13, //D25
  PD_8,  //D26
  PD_9,  //D27
  PA_1,  //D28
  PA_2,  //D29
  PC_1,  //D30
  PD_1,  //D31
  PC_4,  //D32
  PC_5,  //D33
  PA_5,  //D34
  PB_12, //D35
  PG_12, //D36
  PD_4,  //D37
  PB_13, //D38
  PB_14, //D39
  PA_11, //D40
  PB_8,  //D41
  PB_9,  //D42
  PD_7,  //D43
  PG_9,  //D44
  PG_10, //D45
  PB_2,  //D46
  PC_0,  //D47
  PE_7,  //D48
  PD_12, //D49
  PD_11, //D50
  PF_10, //D51
  PB_5,  //D52
  PD_6,  //D53
  PD_5,  //D54
  PD_13, //D55
  PF_7,  //D56
  PG_11, //D57
  PG_5,  //D58
  PB_10, //D59
  PD_0,  //D60
  PB_7,  //D61
  PB_6,  //D62
  PG_13, //D63
  PC_10, //D64
  PC_12, //D65
  PG_0,  //D66
  PB_3,  //D67
  PA_13, //D68
  PA_14, //D69
  PA_15, //D70
  PG_2,  //D71
  PA_0,  //D72/A11
  PC_14, //D73
  PC_15, //D74
  PH_0,  //D75
  PH_1,  //D76
  PC_2,  //D77/A12
  PC_3,  //D78/A13
  PC_11, //D79
  PF_15, //D80
  PG_1,  //D81
  PG_4,  //D82
  PC_9,  //D83
  PF_6,  //D84
  PD_14, //D85
  PD_15, //D86
  PE_0,  //D87
  PE_15, //D88/A14
  PB_1,  //D89/A15
  PF_2,  //D90
  PF_14, //D91/A16
  PB_15, //D92
  PE_10, //D93/A17
  PE_8,  //D94/A18
  PF_13, //D95/A19
  PF_8,  //D96
  PF_9,  //D97
  PG_3,  //D98
  PD_10, //D99
  PE_4,  //D100
  PG_7   //D101

};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  16, // A0,  PA6
  17, // A1,  PA7
  18, // A2,  PA4
  19, // A3,  PB0
  20, // A4,  PF12
  21, // A5,  PF11
  7,  // A6,  PE9
  10, // A7,  PE11
  11, // A8,  PE14
  12, // A9,  PE13
  13, // A10, PE12
  72, // A11, PA0
  77, // A12, PC2
  78, // A13, PC3
  88, // A14, PE15
  89, // A15, PB1
  91, // A16, PF14
  93, // A17, PE10
  94, // A18, PE8
  95  // A19, PF13
};

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

  /** Configure LSE Drive Capability
  *  Warning : Only applied when the LSE is disabled.
  */
  HAL_PWR_EnableBkUpAccess();

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 31;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_LPUART1
                                             | RCC_PERIPHCLK_OTGHS;
  PeriphClkInitStruct.OtghsClockSelection = RCC_OTGHSCLKSOURCE_HSE_DIV2;

  PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLL2_SOURCE_HSE;
  PeriphClkInitStruct.PLL2.PLL2M = 3;
  PeriphClkInitStruct.PLL2.PLL2N = 31;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 4;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2_VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0.0;
  PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVR;
  PeriphClkInitStruct.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_PLL2R;
  PeriphClkInitStruct.PLL3.PLL3Source = RCC_PLL3_SOURCE_HSE;
  PeriphClkInitStruct.PLL3.PLL3M = 3;
  PeriphClkInitStruct.PLL3.PLL3N = 31;
  PeriphClkInitStruct.PLL3.PLL3P = 2;
  PeriphClkInitStruct.PLL3.PLL3Q = 16;
  PeriphClkInitStruct.PLL3.PLL3R = 2;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3_VCIRANGE_3;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3_VCORANGE_WIDE;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0.0;
  PeriphClkInitStruct.PLL3.PLL3ClockOut = RCC_PLL3_DIVQ;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PLL3Q;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Configure desired clock settings for OTG_HS PHY */
  __HAL_RCC_OTGPHY_CONFIG(RCC_OTGPHYREFCKCLKSOURCE_24M);
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_NUCLEO_H5E5ZJ */
