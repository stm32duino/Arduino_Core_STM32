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
#if defined(ARDUINO_NUCLEO_C031C6)
#include "pins_arduino.h"
#include "stm32yyxx_ll_utils.h"

// Digital PinName array
const PinName digitalPin[] = {
  // CN9
  PB_7,  // D0
  PB_6,  // D1
  PA_10, // D2
  PB_3,  // D3
  PB_10, // D4
  PB_4,  // D5
  PB_5,  // D6
  PA_15, // D7

  // CN5
  PA_9,  // D8
  PC_7,  // D9
  PB_0,  // D10
  PA_7,  // D11
  PA_6,  // D12
  PA_5,  // D13 // LED
  PB_9,  // D14
  PB_8,  // D15

  // CN7 Left Side
  PD_0,  // D16
  PD_2,  // D17
  PA_14, // D18
  PA_13, // D19
  PC_6,  // D20
  PC_13, // D21 // Button
  PC_14, // D22 // OSCX_IN
  PF_0,  // D23 // OSC_IN
  PF_1,  // D24 // OSC_OUT
  PB_11, // D25
  PA_2,  // D26 // VCP_TX

  // CN7 Right Side
  PD_1,  // D27

  // CN10 Left Side
  PD_3,  // D28

  // CN8 Left Side
  PA_0,  // D29
  PA_1,  // D30
  PA_4,  // D31
  PB_1,  // D32
  PA_11, // D33
  PA_12, // D34

  // CN10 Right Side
  PA_3,  // D35 // VCP_RX
  PC_15, // D36 // OSCX_OUT
  PB_12, // D37
  PB_2,  // D38
  PF_3,  // D39
  PA_8,  // D40
  PB_15, // D41
  PB_14, // D42
  PB_13, // D43

  // Others
  PF_2,   // D44 // NRST
  PA_9_R, // D45
  PA_10_R // D46
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  29, // A0
  30, // A1
  31, // A2
  32, // A3
  33, // A4
  34, // A5
  26, // A6
  35, // A7
  13, // A8
  12, // A9
  11, // A10
  40, // A11
  19, // A12
  18, // A13
  10, // A14
  38, // A15
  4,  // A16
  25, // A17
  37  // A18
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

  /* HSE configuration and activation */
  LL_RCC_HSE_Enable();
  while (LL_RCC_HSE_IsReady() != 1) {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the HSE */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSE);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSE) {
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
#endif /* ARDUINO_NUCLEO_C031C6 */
