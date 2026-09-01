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
#if defined(ARDUINO_NUCLEO_H533RE)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_15,  //D0
  PB_14,  //D1
  PC_8,   //D2
  PB_3,   //D3
  PB_5,   //D4
  PB_4,   //D5
  PB_10,  //D6
  PA_8,   //D7
  PC_7,   //D8
  PC_6,   //D9
  PC_9,   //D10
  PA_7,   //D11/A10
  PA_6,   //D12A11
  PA_5,   //D13/A12
  PB_7,   //D14
  PB_6,   //D15
  PC_10,  //D16
  PC_12,  //D17
  PA_13,  //D18
  PA_14,  //D19
  PA_15,  //D20
  PC_13,  //D21
  PC_14,  //D22
  PC_15,  //D23
  PH_0,   //D24
  PH_1,   //D25
  PC_2,   //D26/A6
  PC_3,   //D27/A7
  PC_11,  //D28
  PD_2,   //D29
  PA_0,   //D30/A0
  PA_1,   //D31/A1
  PB_1,   //D32/A2
  PB_0,   //D33/A3
  PC_1,   //D34/A4
  PC_0,   //D35/A5
  PA_9,   //D36
  PA_10,  //D37
  PC_5,   //D38/A8
  PA_12,  //D39
  PA_11,  //D40
  PB_12,  //D41
  PB_2,   //D42
  PB_15,  //D43
  PB_14,  //D44
  PB_13,  //D45
  PC_4,   //D46/A9
  PB_8,   //D47
  PA_2,   //D48/A13
  PA_3,   //D49/A14
  PA_4    //D50/A15
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  30, // A0,  PA0
  31, // A1,  PA1
  32, // A2,  PB1
  33, // A3,  PB0
  34, // A4,  PC1
  35, // A5,  PC0
  26, // A6,  PC2
  27, // A7,  PC3
  38, // A8,  PC5
  46, // A9,  PC4
  11, // A10, PA7
  12, // A11, PA6
  13, // A12, PA5
  48, // A13, PA2
  49, // A14, PA3
  50  // A15, PA4
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
  RCC_CRSInitTypeDef RCC_CRSInitStruct = {};

  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Configure LSE Drive Capability
  *  Warning : Only applied when the LSE is disabled.
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 125;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB buses clocks */
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
  /* Initializes the peripherals clock */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_DAC
                                             | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_SDMMC1
                                             | RCC_PERIPHCLK_SPI1 | RCC_PERIPHCLK_SPI2
                                             | RCC_PERIPHCLK_SPI3 | RCC_PERIPHCLK_SPI4
                                             | RCC_PERIPHCLK_USB;;
  PeriphClkInitStruct.DacLowPowerClockSelection = RCC_DACLPCLKSOURCE_LSE;
  PeriphClkInitStruct.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_HCLK;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLL1Q;
  PeriphClkInitStruct.Spi1ClockSelection = RCC_SPI1CLKSOURCE_PLL1Q;
  PeriphClkInitStruct.Spi2ClockSelection = RCC_SPI2CLKSOURCE_PLL1Q;
  PeriphClkInitStruct.Spi3ClockSelection = RCC_SPI3CLKSOURCE_PLL1Q;
  PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLL2_SOURCE_HSE;
  PeriphClkInitStruct.PLL2.PLL2M = 6;
  PeriphClkInitStruct.PLL2.PLL2N = 125;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 4;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2_VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0.0;
  PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVQ;
  PeriphClkInitStruct.Spi4ClockSelection = RCC_SPI4CLKSOURCE_PLL2Q;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }


  /* Enable the CRS APB clock */
  __HAL_RCC_CRS_CLK_ENABLE();

  /* Configures CRS */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_LSE;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 32768);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;

  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);

  /* Configure the programming delay */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_2);
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_H533RE */
