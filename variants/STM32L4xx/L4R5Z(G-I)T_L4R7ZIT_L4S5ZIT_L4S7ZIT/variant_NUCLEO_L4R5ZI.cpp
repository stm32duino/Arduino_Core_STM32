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
#if defined(ARDUINO_NUCLEO_L4R5ZI)
#include "pins_arduino.h"

// Pin number
// Match Table 11. NUCLEO-L4R5ZI pin assignments
// from UM2179 STM32 Nucleo-144 board
const PinName digitalPin[] = {
  PD_9,
  PD_8,
  PF_15,
  PE_13,
  PF_14,
  PE_11,
  PE_9,
  PF_13,
  PF_12,
  PD_15,
  PD_14,
  PA_7,
  PA_6,
  PA_5,
  PB_9,
  PB_8,
  PC_6,
  PB_15,
  PB_13,
  PB_12,
  PA_4,
  PB_4,
  PB_5,
  PB_3,
  PA_4,
  PB_4,
  PA_2,
  PB_10,
  PE_15,
  PB_0,
  PE_12,
  PE_14,
  PA_0,
  PB_0,
  PE_0,
  PB_11,
  PB_10,
  PE_15,
  PE_14,
  PE_12,
  PE_10,
  PE_7,
  PE_8,
  PC_8,
  PC_9,
  PC_10,
  PC_11,
  PC_12,
  PD_2,
  PF_3,
  PF_5,
  PD_7,
  PD_6,
  PD_5,
  PD_4,
  PD_3,
  PE_2,
  PE_4,
  PE_5,
  PE_6,
  PE_3,
  PF_8,
  PF_7,
  PF_9,
  PG_1,
  PG_0,
  PD_1,
  PD_0,
  PF_0,
  PF_1,
  PF_2,
  PB_6,
  PB_2,
  // ST Morpho
  PA_8,
  PA_9,
  PA_10,
  PA_11,
  PA_12,
  PA_15,
  PB_7,
  PB_14,
  PC_7,
  PC_13,
  PC_14,
  PC_15,
  PD_10,
  PD_11,
  PD_12,
  PD_13,
  PE_1,
  PF_10,
  PF_11,
  PG_2,
  PG_3,
  PG_4,
  PG_5,
  PG_6,
  PG_7,
  PG_8,
  PG_9,
  PG_10,
  PG_11,
  PG_12,
  PG_13,
  PG_14,
  PH_0,
  PH_1,
  PA_3,
  PC_0,
  PC_3,
  PC_1,
  PC_4,
  PC_5,
  PB_1,
  PC_2,
  PA_1,
  PG_15,
  PF_4,
  PF_6,
  PA_13,
  PA_14,
  PH_3
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  107, //A0
  108, //A1
  109, //A2
  110, //A3
  111, //A4
  112, //A5
  113, //A6
  114, //A7
  115, //A8
  11,  //A9
  12,  //A10
  13,  //A11
  20,  //A12
  26,  //A13
  29,  //A14
  32   //A15
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK) {
    Error_Handler();
  }
  /* Configure LSE Drive Capability */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /*
   * Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
  /* Enable MSI Auto calibration */
  HAL_RCCEx_EnableMSIPLLMode();
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_L4R5ZI */
