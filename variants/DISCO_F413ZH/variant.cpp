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
  PF_6,  // D0 - UART7 RX
  PF_7,  // D1 - UART7 TX
  PG_13, // D2
  PF_10, // D3
  PB_6,  // D4
  PE_6,  // D5
  PB_0,  // D6/A8
  PC_13, // D7
  PA_4,  // D8/A11
  PB_8,  // D9
  PA_15, // D10 - SPI_SSEL
  PB_5,  // D11 - SPI_MOSI, ISM43362_WIFI_MOSI
  PB_4,  // D12 - SPI_MISO, ISM43362_WIFI_MISO
  PB_12, // D13 - SPI_SCK, LED_GREEN, ISM43362_WIFI_SCLK
  PB_11, // D14 - I2C_SDA
  PB_10, // D15 - I2C_SCL
  PC_0,  // D16/A0
  PA_1,  // D17/A1
  PA_2,  // D18/A2
  PA_5,  // D19/A3
  PB_1,  // D20/A4
  PC_4,  // D21/A5
  // not on connector
  PG_14, // D22 - STLink Tx
  PG_9,  // D23 - STLink Rx
  PE_3,  // D24 - LD4, LED1_RED
  PC_5,  // D25/A15 - LD3, LED2_GREEN
  PA_0,  // D26/A9 - User button
  PG_11, // D27 - ISM43362_WIFI_NSS
  PH_1,  // D28 - ISM43362_WIFI_RESET
  PG_12, // D29 - ISM43362_WIFI_DATAREADY
  PB_15, // D30 - ISM43362_WIFI_WAKEUP
  PE_2,  // D31
  PE_4,  // D32
  PE_5,  // D33
  PC_14, // D34
  PC_15, // D35
  PF_0,  // D36
  PF_1,  // D37
  PF_2,  // D38
  PF_3,  // D39
  PF_4,  // D40
  PF_5,  // D41
  PF_8,  // D42
  PF_9,  // D43
  PC_1,  // D44/A12
  PC_2,  // D45/A13
  PC_3,  // D46/A14
  PA_3,  // D47/A10
  PA_6,  // D48/A6
  PA_7,  // D49/A7
  PB_2,  // D50
  PF_11, // D51
  PF_12, // D52
  PF_13, // D53
  PF_14, // D54
  PF_15, // D55
  PG_0,  // D56
  PG_1,  // D57
  PE_7,  // D58
  PE_8,  // D59
  PE_9,  // D60
  PE_10, // D61
  PE_11, // D62
  PE_12, // D63
  PE_13, // D64
  PE_14, // D65
  PE_15, // D66
  PB_13, // D67
  PB_14, // D68
  PB_15, // D69
  PD_8,  // D70
  PD_9,  // D71
  PD_10, // D72
  PD_11, // D73
  PD_12, // D74
  PD_13, // D75
  PD_14, // D76
  PD_15, // D77
  PG_2,  // D78
  PG_3,  // D79
  PG_4,  // D80
  PG_5,  // D81
  PG_6,  // D82
  PG_7,  // D83
  PG_8,  // D84
  PC_6,  // D85
  PC_7,  // D86
  PC_8,  // D87
  PC_9,  // D88
  PA_8,  // D89
  PA_9,  // D90
  PA_10, // D91
  PA_11, // D92
  PA_12, // D93
  PA_13, // D94
  PA_14, // D95
  PC_10, // D96
  PC_11, // D97
  PC_12, // D98
  PD_0,  // D99
  PD_1,  // D100
  PD_2,  // D101
  PD_3,  // D102
  PD_4,  // D103
  PD_5,  // D104
  PD_6,  // D105
  PD_7,  // D106
  PG_10, // D107
  PG_11, // D108
  PG_12, // D109
  PG_15, // D110
  PB_3,  // D111
  PB_7,  // D112
  PB_9,  // D113
  PE_0,  // D114
  PE_1   // D115
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, //A0
  17, //A1
  18, //A2
  19, //A3
  20, //A4
  21, //A5
  48, //A6
  49, //A7
  6,  //A8
  26, //A9
  47, //A10
  8,  //A11
  44, //A12
  45, //A13
  46, //A14
  25  //A15
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void initVariant(void)
{
  /* In DISCO_F413ZH board, Arduino connector and Wifi embeded module are sharing the same SPI pins */
  /* We need to set the default SPI SS pin for the Wifi module to the inactive state i.e. 1 */
  /* See board User Manual: WIFI_SPI_CS = PG_11*/
  __HAL_RCC_GPIOG_CLK_ENABLE();
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);
}

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
  clocked below the maximum system frequency, to update the voltage scaling value
  regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 2;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);

  if (ret != HAL_OK) {
    while (1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3);
  if (ret != HAL_OK) {
    while (1);
  }

  /* Select PLLI2S output as USB clock source */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CK48CLKSOURCE_PLLI2SQ;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 8;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SQ = 4;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct)  != HAL_OK) {
    while (1);
  }
}

#ifdef __cplusplus
}
#endif
