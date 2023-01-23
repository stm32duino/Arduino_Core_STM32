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
#if defined(ARDUINO_STM32C0316_DK)
#include "pins_arduino.h"
#include "stm32yyxx_ll_utils.h"

// Digital PinName array
const PinName digitalPin[] = {

  PA_3,  // D0
  PA_2,  // D1
  PC_6,  // D2
  PC_7,  // D3
  PA_0,  // D4
  PD_0,  // D5
  PD_1,  // D6
  PD_2,  // D7
  PD_3,  // D8
  PA_8,  // D9
  PB_0,  // D10
  PA_7,  // D11
  PA_6,  // D12
  PA_1,  // D13
  PA_4,  // D14
  PA_5,  // D15
  PA_10, // D16
  PA_9,  // D17
  PB_11, // D18
  PB_10, // D19
  PB_6,  // D20
  PB_7   // D21
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  14, // A4,
  15, // A5,
  16, // A0,
  17, // A1,
  18, // A2,
  19  // A3,
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
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while (LL_RCC_HSI_IsReady() != 1) {
  }

  LL_RCC_HSI_SetCalibTrimming(64);
  LL_RCC_SetHSIDiv(LL_RCC_HSI_DIV_1);
  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI) {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(48000000);

  /* Update the time base */
  if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_STM32C0316_DK */
