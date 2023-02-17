/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_B_U585I_IOT02A)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PD_9,  //D0
  PD_8,  //D1
  PD_15, //D2
  PB_2,  //D3/A6
  PE_7,  //D4
  PE_0,  //D5
  PB_6,  //D6
  PF_13, //D7
  PC_1,  //D8/A7
  PA_8,  //D9
  PE_12, //D10
  PE_15, //D11
  PE_14, //D12
  PE_13, //D13
  PB_9,  //D14
  PB_8,  //D15
  PC_0,  //D16/A0
  PC_2,  //D17/A1
  PC_4,  //D18/A2
  PC_5,  //D19/A3
  PA_7,  //D20/A4
  PB_0,  //D21/A5
  PH_6,  //D22
  PH_7,  //D23
  PC_13, //D24
  PA_9,  //D25
  PA_10, //D26
  PH_4,  //D27
  PH_5,  //D28
  PD_10, //D29
  PE_11, //D30
  PG_2,  //D31
  PG_5,  //D32
  PH_1,  //D33
  PF_11, //D34
  PE_9,  //D35
  PE_10, //D36
  PB_1,  //D37
  PF_10, //D38
  PA_11, //D39
  PA_12, //D40
  PA_15, //D41
  PB_5,  //D42
  PB_15, //D43
  PD_13, //D44
  PE_8,  //D45
  PF_14, //D46/A18
  PF_0,  //D47
  PF_1,  //D48
  PF_2,  //D49
  PF_3,  //D50
  PF_4,  //D51
  PF_12, //D52
  PH_9,  //D53
  PH_10, //D54
  PH_11, //D55
  PH_12, //D56
  PI_5,  //D57
  PB_10, //D58
  PB_11, //D59
  PC_3,  //D60
  PD_7,  //D61
  PE_3,  //D62
  PF_6,  //D63
  PF_7,  //D64
  PF_8,  //D65
  PF_9,  //D66
  PH_2,  //D67
  PI_0,  //D68
  PG_6,  //D69
  PC_10, //D70
  PC_11, //D71
  PB_12, //D72
  PD_1,  //D73
  PD_3,  //D74
  PD_4,  //D75
  PD_14, //D76
  PF_15, //D77
  PG_15, //D78
  PH_15, //D79
  PD_11, //D80/A8
  PD_12, //D81/A9
  PG_12, //D82
  PD_6,  //D83
  PG_10, //D84
  PG_9,  //D85
  PC_12, //D86
  PB_4,  //D87
  PE_6,  //D88
  PB_13, //D89
  PG_0,  //D90/A10
  PC_9,  //D91
  PG_1,  //D92/A11
  PD_2,  //D93
  PD_5,  //D94
  PG_8,  //D95
  PA_0,  //D96/A12
  PA_2,  //D97/A13
  PA_3,  //D98/A14
  PA_1,  //D99/A15
  PA_4,  //D100/A16
  PG_4,  //D101
  PG_3,  //D102
  PE_4,  //D103
  PG_7,  //D104
  PA_5,  //D105/A17
  PE_5,  //D106
  PE_2,  //D107
  PD_0,  //D108
  PF_5,  //D109
  PB_14, //D110
  PH_13, //D111
  PA_6,  //D112
  PB_7,  //D113
  PC_6,  //D114
  PC_7,  //D115
  PC_8,  //D116
  PE_1,  //D117
  PH_8,  //D118
  PH_14, //D119
  PI_1,  //D120
  PI_2,  //D121
  PI_3,  //D122
  PI_4,  //D123
  PI_6,  //D124
  PI_7,  //D125
  PA_13, //D126
  PA_14, //D127
  PB_3,  //D128
  PH_0,  //D129
  PC_14, //D130
  PC_15, //D131
  PH_3   //D132
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16,  // A0,  PC0
  17,  // A1,  PC2
  18,  // A2,  PC4
  19,  // A3,  PC5
  20,  // A4,  PA7
  21,  // A5,  B0P
  3,   // A6,  PB2
  8,   // A7,  PC1
  80,  // A8,  PD11
  81,  // A9,  PD12
  90,  // A10, PG0
  92,  // A11, PG1
  96,  // A12, PA0
  97,  // A13, PA2
  98,  // A14, PA3
  99,  // A15, PA1
  100, // A16, PA4
  105, // A17, PA5
  46   // A18, PF14
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/** System Clock Configuration
*/
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_ADF1
                                       | RCC_PERIPHCLK_DAC1 | RCC_PERIPHCLK_I2C1
                                       | RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_LPUART1
                                       | RCC_PERIPHCLK_OSPI | RCC_PERIPHCLK_SPI1
                                       | RCC_PERIPHCLK_SPI2 | RCC_PERIPHCLK_SPI3
                                       | RCC_PERIPHCLK_CLK48;
  PeriphClkInit.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_SYSCLK;
  PeriphClkInit.Adf1ClockSelection = RCC_ADF1CLKSOURCE_HCLK;
  PeriphClkInit.Dac1ClockSelection = RCC_DAC1CLKSOURCE_LSI;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
  PeriphClkInit.Spi1ClockSelection = RCC_SPI1CLKSOURCE_SYSCLK;
  PeriphClkInit.Spi2ClockSelection = RCC_SPI2CLKSOURCE_SYSCLK;
  PeriphClkInit.Spi3ClockSelection = RCC_SPI3CLKSOURCE_SYSCLK;
  PeriphClkInit.IclkClockSelection = RCC_CLK48CLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* B_U585I_IOT02A */
