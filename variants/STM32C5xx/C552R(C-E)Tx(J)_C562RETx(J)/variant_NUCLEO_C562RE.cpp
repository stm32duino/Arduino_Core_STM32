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
#if defined(ARDUINO_NUCLEO_C562RE)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_15, // D0
  PB_14, // D1
  PA_10, // D2
  PB_3,  // D3
  PC_1,  // D4/A6
  PB_4,  // D5
  PB_10, // D6
  PA_8,  // D7
  PA_9,  // D8
  PC_6,  // D9
  PC_9,  // D10/A7
  PA_7,  // D11/A8
  PA_6,  // D12/A9
  PA_5,  // D13
  PB_7,  // D14
  PB_6,  // D15
  PC_10, // D16
  PC_12, // D17
  PH_2,  // D18
  PA_2,  // D19/A15
  PA_3,  // D20/A16
  PA_13, // D21
  PA_14, // D22
  PA_15, // D23
  PE_2,  // D24
  PC_13, // D25
  PC_14, // D26
  PC_15, // D27
  PH_0,  // D28
  PH_1,  // D29
  PC_2,  // D30/A10
  PC_3,  // D31/A11
  PC_11, // D32
  PD_2,  // D33
  PA_0,  // D34/A0
  PA_1,  // D35/A1
  PA_4,  // D36/A2
  PB_0,  // D37/A3
  PC_5,  // D38/A4
  PC_0,  // D39/A5
  PC_8,  // D40
  PC_7,  // D41
  PB_5,  // D42
  PA_12, // D43
  PA_11, // D44
  PB_12, // D45
  PB_1,  // D46/A12
  PB_2,  // D47/A13
  PB_13, // D48
  PC_4,  // D49/A14
  PB_8,  // D50
  PB_9   // D51
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  34, // A0,  PA0
  35, // A1,  PA1
  36, // A2,  PA4
  37, // A3,  PB0
  38, // A4,  PC5
  39, // A5,  PC0
  4,  // A6,  PC1
  11, // A7,  PA7
  12, // A8,  PA6
  13, // A9,  PA5
  30, // A10, PC2
  31, // A11, PC3
  46, // A12, PB1
  47, // A13, PB2
  49, // A14, PC4
  19, // A15, PA2
  20  // A16, PA3
};

// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  if (HAL_RCC_HSE_Enable(HAL_RCC_HSE_ON) != HAL_OK) {
    Error_Handler();
  }

  hal_rcc_psi_config_t config_psi;
  config_psi.psi_source = HAL_RCC_PSI_SRC_HSE;
  config_psi.psi_ref = HAL_RCC_PSI_REF_24MHZ;
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
  config_bus.pclk3_prescaler = HAL_RCC_PCLK_PRESCALER4;
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

  /* Peripherals using PCLK3 (36 MHz):
  LPUART1
  */

  /* Peripherals using HSIDIV3 (48 MHz):
    USB
  */
  if (HAL_RCC_HSIDIV3_Enable() != HAL_OK) {
    Error_Handler();
  }

}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_NUCLEO_C562RE */
