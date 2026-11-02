/*
 *******************************************************************************
 * Copyright (c) 2026, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_WEACT_WB55CGU6)
#include "pins_arduino.h"
#include "lock_resource.h"

// Digital PinName array
const PinName digitalPin[] = {
  PB_2,   // D0
  PA_9,   // D1
  PA_8,   // D2
  PA_7,   // D3
  PA_6,   // D4
  PA_5,   // D5
  PA_4,   // D6
  PA_3,   // D7
  PA_2,   // D8
  PA_1,   // D9
  PA_0,   // D10
  PB_8,   // D11
  PB_9,   // D12
  PH_3,   // D13 - BOOT0 / SW2 button
  PB_0,   // D14
  PB_1,   // D15
  PE_4,   // D16 - onboard blue LED
  PA_10,  // D17
  PA_15,  // D18
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7    // D23
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  10, // A0,  PA0
  9,  // A1,  PA1
  8,  // A2,  PA2
  7,  // A3,  PA3
  6,  // A4,  PA4
  5,  // A5,  PA5
  4,  // A6,  PA6
  3,  // A7,  PA7
  2,  // A8,  PA8
  1   // A9,  PA9
};

// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *
  * Board is fitted with a 32MHz HSE crystal (X2) and a 32.768kHz LSE
  * crystal (X1). SYSCLK is driven directly by HSE (no PLL needed) and
  * USB/RNG are clocked from the dedicated HSI48 oscillator, otherwise
  * the USB peripheral is left unclocked and never enumerates.
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /* This prevents concurrent access to RCC registers by CPU2 (M0+) */
  hsem_lock(CFG_HW_RCC_SEMID, HSEM_LOCK_DEFAULT_RETRY);

  /* Macro to configure the PLL multiplication factor */
  __HAL_RCC_PLL_PLLM_CONFIG(RCC_PLLM_DIV2);

  /* Macro to configure the PLL clock source */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);
  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* This prevents the CPU2 (M0+) to disable the HSI48 oscillator */
  hsem_lock(CFG_HW_CLK48_CONFIG_SEMID, HSEM_LOCK_DEFAULT_RETRY);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
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
  PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
  PeriphClkInitStruct.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE0;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

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
#endif /* ARDUINO_WEACT_WB55CGU6 */
