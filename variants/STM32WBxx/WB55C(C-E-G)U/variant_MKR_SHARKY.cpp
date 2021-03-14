/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_MKR_SHARKY)
#include "pins_arduino.h"
#include "lock_resource.h"

// Pin number
const PinName digitalPin[] = {
  PB_0,  //D0
  PB_1,  //D1
  PA_8,  //D2
  PA_9,  //D3
  PA_10, //D4
  PA_15, //D5
  PE_4,  //D6
  PB_2,  //D7
  PB_5,  //D8
  PB_3,  //D9
  PB_4,  //D10
  PB_9,  //D11
  PB_8,  //D12
  PB_7,  //D13
  PB_6,  //D14
  PH_3,  //D15
  PA_0,  //D16
  PA_1,  //D17
  PA_2,  //D18 // SW
  PA_3,  //D19 // SW
  PA_4,  //D20
  PA_5,  //D21
  PA_6,  //D22
  PA_7   //D23
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0
  17, // A1
  18, // A2
  19, // A3
  20, // A4
  21, // A5
  22, // A6
  23, // A7
  2,  // A8
  3   // A9
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

  /* This prevents concurrent access to RCC registers by CPU2 (M0+) */
  hsem_lock(CFG_HW_RCC_SEMID, HSEM_LOCK_DEFAULT_RETRY);

  /* Configure LSE Drive Capability */
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI1
                                     | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE
                                     | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 32;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4 | RCC_CLOCKTYPE_HCLK2
                                | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the peripherals clocks */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS | RCC_PERIPHCLK_RFWAKEUP
                                             | RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_USART1
                                             | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_USB
                                             | RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLLSAI1.PLLN = 24;
  PeriphClkInitStruct.PLLSAI1.PLLP = RCC_PLLP_DIV2;
  PeriphClkInitStruct.PLLSAI1.PLLQ = RCC_PLLQ_DIV2;
  PeriphClkInitStruct.PLLSAI1.PLLR = RCC_PLLR_DIV2;
  PeriphClkInitStruct.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_USBCLK | RCC_PLLSAI1_ADCCLK;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Enables the Clock Security System */
  HAL_RCCEx_EnableLSECSS();
  /* Enable MSI Auto calibration */
  HAL_RCCEx_EnableMSIPLLMode();

  hsem_unlock(CFG_HW_RCC_SEMID);
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_MKR_SHARKY */
