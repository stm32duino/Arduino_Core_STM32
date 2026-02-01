/*
 *******************************************************************************
 * Copyright (c) 2024, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_C071RB)
#include "pins_arduino.h"
#include "stm32yyxx_ll_utils.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_7,   // D0
  PB_6,   // D1
  PA_10,  // D2
  PC_7,   // D3
  PB_5,   // D4
  PB_4,   // D5
  PC_8,   // D6
  PA_8,   // D7/A6
  PA_9,   // D8
  PB_3,   // D9
  PA_15,  // D10
  PA_7,   // D11/A7
  PA_6,   // D12/A8
  PA_5,   // D13/A9
  PB_9,   // D14
  PB_8,   // D15
  PA_0,   // D16/A0
  PA_1,   // D17/A1
  PA_4,   // D18/A2
  PB_0,   // D19/A3
  PC_4,   // D20/A4
  PC_5,   // D21/A5
  PC_10,  // D22
  PC_12,  // D23
  PD_4,   // D24
  PD_0,   // D25
  PD_3,   // D26
  PA_13,  // D27
  PA_14,  // D28
  PC_6,   // D29
  PC_2,   // D30
  PC_13,  // D31
  PC_14,  // D32
  PC_15,  // D33
  PF_0,   // D34
  PF_1,   // D35
  PF_3,   // D36
  PB_2,   // D37/A10
  PB_11,  // D38/A11
  PC_11,  // D39
  PD_2,   // D40
  PD_1,   // D41
  PF_2,   // D42
  PD_5,   // D43
  PC_3,   // D44
  PC_9,   // D45
  PC_1,   // D46
  PA_3,   // D47
  PD_6,   // D48
  PA_12,  // D49
  PA_11,  // D50
  PB_12,  // D51/A12
  PA_2,   // D52
  PC_0,   // D53
  PB_1,   // D54/A13
  PB_15,  // D55
  PB_14,  // D56
  PB_13,  // D57
  PB_10,  // D58/A14
  PD_8,   // D59
  PD_9    // D60
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0,  PA0
  17, // A1,  PA1
  18, // A2,  PA4
  19, // A3,  PB0
  20, // A4,  PC4
  21, // A5,  PC5
  7,  // A6,  PA8
  11, // A7,  PA7
  12, // A8,  PA6
  13, // A9,  PA5
  37, // A10, PB2
  38, // A11, PB11
  51, // A12, PB12
  54, // A13, PB1
  58  // A14, PB10
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
  LL_RCC_HSI48_Enable();
  while (LL_RCC_HSI48_IsReady() != 1) {
  }

  LL_RCC_HSI_SetCalibTrimming(64);
  LL_RCC_SetHSIDiv(LL_RCC_HSI_DIV_1);
  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_HCLK_DIV_1);

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
#endif /* ARDUINO_NUCLEO_C71RB */
