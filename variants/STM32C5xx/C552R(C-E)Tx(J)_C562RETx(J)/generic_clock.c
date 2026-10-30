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
#if defined(ARDUINO_GENERIC_C552RCTX) || defined(ARDUINO_GENERIC_C552RCTXJ) ||\
    defined(ARDUINO_GENERIC_C552RETX) || defined(ARDUINO_GENERIC_C552RETXJ) ||\
    defined(ARDUINO_GENERIC_C562RETX) || defined(ARDUINO_GENERIC_C562RETXJ)
#include "pins_arduino.h"

/**
  * @brief  System Clock Configuration
  */
WEAK void SystemClock_Config(void)
{
  if (HAL_RCC_HSIS_Enable() != HAL_OK) {
    Error_Handler();
  }

  hal_rcc_psi_config_t config_psi;
  config_psi.psi_source = HAL_RCC_PSI_SRC_HSI_8MHz;
  config_psi.psi_ref = HAL_RCC_PSI_REF_8MHZ;
  config_psi.psi_out = HAL_RCC_PSI_OUT_144MHZ;
  if (HAL_RCC_PSI_SetConfig(&config_psi) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_RCC_PSIS_Enable() != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB busses clocks */
  hal_rcc_bus_clk_config_t config_bus;
  config_bus.hclk_prescaler  = HAL_RCC_HCLK_PRESCALER1;
  config_bus.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER1;
  config_bus.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER1;
  config_bus.pclk3_prescaler = HAL_RCC_PCLK_PRESCALER1;
  if (HAL_RCC_SetBusClockConfig(&config_bus) != HAL_OK) {
    Error_Handler();
  }

  /** Frequency will be increased */
  HAL_FLASH_ITF_SetLatency(HAL_FLASH, HAL_FLASH_ITF_LATENCY_4);

  if (HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_PSIS) != HAL_OK) {
    Error_Handler();
  }

  HAL_FLASH_ITF_SetProgrammingDelay(HAL_FLASH, HAL_FLASH_ITF_PROGRAM_DELAY_2);

  if (HAL_UpdateCoreClock() != HAL_OK) {
    Error_Handler();
  }
}

#endif /* ARDUINO_GENERIC_* */
