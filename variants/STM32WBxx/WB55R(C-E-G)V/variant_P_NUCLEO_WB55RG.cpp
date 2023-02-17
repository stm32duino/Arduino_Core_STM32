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
#if defined(ARDUINO_P_NUCLEO_WB55RG)
#include "pins_arduino.h"
#include "lock_resource.h"

// Pin number
const PinName digitalPin[] = {
  PA_3,
  PA_2,
  PC_6,
  PA_10,
  PC_10,
  PA_15,
  PA_8,
  PC_13,
  PC_12,
  PA_9,
  PA_4,
  PA_7,
  PA_6,
  PA_5,
  PB_9,
  PB_8,
  // ST Morpho
  // CN7 Left Side
  PB_11,
  PC_5,
  PA_13,
  PA_14,
  PC_14,
  PC_15,
  // CN7 Right Side
  PB_2,
  PE_4,
  // CN10 Left Side
  PC_4,
  // CN10 Right side
  PB_4,
  PB_7,
  PA_12,
  PA_11,
  PB_12,
  PB_0,
  PB_1,
  PB_15,
  PB_14,
  PB_13,
  PB_6,
  PD_0,
  PD_1,
  PB_3,
  PC_0,
  PC_1,
  PA_1,
  PA_0,
  PC_3,
  PC_2,
  PB_5,
  PB_10,
  PC_11,
  PH_3
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  39, // A0
  40, // A1
  41, // A2
  42, // A3
  43, // A4
  44, // A5
  0,  // A6
  1,  // A7
  6,  // A8
  9,  // A9
  10, // A10
  11, // A11
  12, // A12
  13, // A13
  17, // A14
  24  // A15
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

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* This prevents the CPU2 (M0+) to disable the HSI48 oscillator */
  hsem_lock(CFG_HW_CLK48_CONFIG_SEMID, HSEM_LOCK_DEFAULT_RETRY);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48
                                     | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4 | RCC_CLOCKTYPE_HCLK2
                                | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the peripherals clocks */
  /* RNG needs to be configured like in M0 core, i.e. with HSI48 */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS | RCC_PERIPHCLK_RFWAKEUP
                                             | RCC_PERIPHCLK_RNG | RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;
  PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }

  LL_PWR_SMPS_SetStartupCurrent(LL_PWR_SMPS_STARTUP_CURRENT_80MA);
  LL_PWR_SMPS_SetOutputVoltageLevel(LL_PWR_SMPS_OUTPUT_VOLTAGE_1V40);
  LL_PWR_SMPS_Enable();

  /* Select HSI as system clock source after Wake Up from Stop mode */
  LL_RCC_SetClkAfterWakeFromStop(LL_RCC_STOP_WAKEUPCLOCK_HSI);

  hsem_unlock(CFG_HW_RCC_SEMID);
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_P_NUCLEO_WB55RG */
