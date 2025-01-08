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
#ifdef ARDUINO_DAISY_PATCH_SM

#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A9
  PA_1,   // D1/A8
  PA_2,   // D2/A2
  PA_3,   // D3/A0
  PA_4,   // D4/A12
  PA_5,   // D5/A13
  PA_6,   // D6/A1
  PA_7,   // D7/A3
  PA_9,   // D8
  PA_10,  // D9
  PA_11,  // D10
  PA_12,  // D11
  PA_13,  // D12
  PA_14,  // D13
  PA_15,  // D14
  PB_1,   // D15/A6
  PB_3,   // D16
  PB_4,   // D17
  PB_8,   // D18
  PB_9,   // D19
  PB_10,  // D20
  PB_11,  // D21
  PB_14,  // D22
  PB_15,  // D23
  PC_0,   // D24/A5
  PC_1,   // D25/A4
  PC_4,   // D26/A7
  PC_7,   // D27
  PC_8,   // D28
  PC_9,   // D29
  PC_10,  // D30
  PC_11,  // D31
  PC_12,  // D32
  PC_13,  // D33
  PC_14,  // D34
  PD_0,   // D35
  PD_1,   // D36
  PD_2,   // D37
  PD_3,   // D38
  PD_8,   // D39
  PD_9,   // D40
  PD_10,  // D41
  PD_14,  // D42
  PD_15,  // D43
  PE_0,   // D44
  PE_1,   // D45
  PE_2,   // D46
  PE_3,   // D47
  PE_4,   // D48
  PE_5,   // D49
  PE_6,   // D50
  PE_7,   // D51
  PE_8,   // D52
  PE_9,   // D53
  PE_10,  // D54
  PE_11,  // D55
  PE_12,  // D56
  PE_13,  // D57
  PE_14,  // D58
  PE_15,  // D59
  PF_0,   // D60
  PF_1,   // D61
  PF_2,   // D62
  PF_3,   // D63
  PF_4,   // D64
  PF_5,   // D65
  PF_6,   // D66
  PF_7,   // D67
  PF_8,   // D68
  PF_9,   // D69
  PF_10,  // D70
  PF_11,  // D71
  PF_12,  // D72
  PF_13,  // D73
  PF_14,  // D74
  PF_15,  // D75
  PG_0,   // D76
  PG_1,   // D77
  PG_2,   // D78
  PG_3,   // D79
  PG_4,   // D80
  PG_5,   // D81
  PG_6,   // D82
  PG_8,   // D83
  PG_13,  // D84
  PG_14,  // D85
  PG_15,  // D86
  PH_0,   // D87
  PH_1,   // D88
  PH_2,   // D89
  PH_3,   // D90
  PH_5,   // D91
  PH_8,   // D92
  PH_9,   // D93
  PH_10,  // D94
  PH_11,  // D95
  PH_12,  // D96
  PH_13,  // D97
  PH_14,  // D98
  PH_15,  // D99
  PI_0,   // D100
  PI_1,   // D101
  PI_2,   // D102
  PI_3,   // D103
  PI_4,   // D104
  PI_5,   // D105
  PI_6,   // D106
  PI_7,   // D107
  PI_9,   // D108
  PI_10,  // D109
  PC_2_C, // D110/A11
  PC_3_C  // D111/A10
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  3,   // A0, PA3
  6,   // A1, PA6
  2,   // A2, PA2
  7,   // A3, PA7
  25,  // A4, PC1
  24,  // A5, PC0
  15,  // A6, PB1
  26,  // A7, PC4
  1,   // A8, PA1
  0,   // A9, PA0
  110, // A10, PC2_C
  111, // A11, PC3_C
  4,   // A12, PA4
  5,   // A13, PA5
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
  RCC_OscInitTypeDef       RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef       RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /* Supply configuration update enable */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0); // 480MHz

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /* Macro to configure the PLL clock source */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType
    = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 200; // 400MHz Mode
  //RCC_OscInitStruct.PLL.PLLN = 240; // 480MHz Mode
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType
    = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
      | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection
    = RCC_PERIPHCLK_USART16 | RCC_PERIPHCLK_RNG | RCC_PERIPHCLK_SPI123
      | RCC_PERIPHCLK_SAI2 | RCC_PERIPHCLK_SAI1 | RCC_PERIPHCLK_SDMMC
      | RCC_PERIPHCLK_USART234578 | RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_I2C123
      | RCC_PERIPHCLK_USB | RCC_PERIPHCLK_QSPI | RCC_PERIPHCLK_FMC
      | RCC_PERIPHCLK_SPI45 | RCC_PERIPHCLK_SPI6;
  // PLL 2
  PeriphClkInitStruct.PLL2.PLL2M = 4;
  //  PeriphClkInitStruct.PLL2.PLL2N = 115; // Max Freq @ 3v3 (overclocked SDRAM)
  PeriphClkInitStruct.PLL2.PLL2N = 100;  // 100Mhz -> FMC
  PeriphClkInitStruct.PLL2.PLL2P = 8;  // 57.5
  PeriphClkInitStruct.PLL2.PLL2Q = 10; // 46
  PeriphClkInitStruct.PLL2.PLL2R = 2;  // 115Mhz
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  // PLL 3
  PeriphClkInitStruct.PLL3.PLL3M = 6;
  PeriphClkInitStruct.PLL3.PLL3N = 295;
  PeriphClkInitStruct.PLL3.PLL3P = 64; // 12.29Mhz
  PeriphClkInitStruct.PLL3.PLL3Q = 4;
  PeriphClkInitStruct.PLL3.PLL3R = 32; // 24.xMhz
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_1;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_PLL2;
  PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
  PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL3;
  PeriphClkInitStruct.Sai23ClockSelection = RCC_SAI23CLKSOURCE_PLL3;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL2;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Spi6ClockSelection = RCC_SPI6CLKSOURCE_D3PCLK1;
  PeriphClkInitStruct.Usart234578ClockSelection
    = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PLL3;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL3;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Enable USB Voltage detector */
  HAL_PWREx_EnableUSBVoltageDetector();
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_DAISY_PATCH_SM */
