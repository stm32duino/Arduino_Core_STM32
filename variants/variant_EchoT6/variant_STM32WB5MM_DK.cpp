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
#if defined(ARDUINO_STM32WB5MM_DK)
#include "pins_arduino.h"
#include "lock_resource.h"

// Digital PinName array
const PinName digitalPin[] = {
  PC_0,  // D0/A9
  PB_5,  // D1
  PD_12, // D2
  PD_14, // D3
  PE_4,  // D4
  PB_10, // D5
  PE_0,  // D6
  PB_2,  // D7
  PD_13, // D8
  PD_15, // D9
  PA_4,  // D10/A10
  PA_7,  // D11/A11
  PB_4,  // D12
  PA_1,  // D13/A12
  PA_10, // D14
  PB_8,  // D15
  PC_3,  // D16/A0
  PA_2,  // D17/A1
  PA_5,  // D18/A2
  PC_1,  // D19/A3
  PC_4,  // D20/A4
  PC_5,  // D21/A5
  PD_0,  // D22
  PA_6,  // D23/A6
  PD_4,  // D24
  PC_2,  // D25/A7
  PD_1,  // D26
  PB_12, // D27
  PB_15, // D28
  PB_14, // D29
  PE_3,  // D30
  PD_8,  // D31
  PA_0,  // D32/A8
  PA_15, // D33
  PC_11, // D34
  PC_10, // D35
  PC_12, // D36
  PC_13, // D37
  PB_6,  // D38
  PB_7,  // D39
  PA_11, // D40
  PA_12, // D41
  PD_3,  // D42
  PA_3,  // D43
  PB_9,  // D44
  PD_5,  // D45
  PD_6,  // D46
  PD_7,  // D47
  PA_8,  // D48
  PA_9,  // D49
  PC_6,  // D50
  PC_7,  // D51
  PD_10, // D52
  PD_11, // D53
  PC_8,  // D54
  PC_9,  // D55
  PH_0,  // D56
  PB_11, // D57
  PB_13, // D58
  PD_2,  // D59
  PD_9,  // D60
  PE_1,  // D61
  PA_13, // D62
  PA_14, // D63
  PB_3,  // D64
  PE_2,  // D65
  PH_1,  // D66
  PH_3   // D67
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0,  PC3
  17, // A1,  PA2
  18, // A2,  PA5
  19, // A3,  PC1
  20, // A4,  PC4
  21, // A5,  PC5
  23, // A6,  PA6
  25, // A7,  PC2
  32, // A8,  PA0
  0,  // A9,  PC0
  10, // A10, PA4
  11, // A11, PA7
  13  // A12, PA1
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* This prevents the CPU2 (M0+) to disable the HSI48 oscillator */
  hsem_lock(CFG_HW_CLK48_CONFIG_SEMID, HSEM_LOCK_DEFAULT_RETRY);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
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
  /** Initializes the peripherals clocks
  */
  /* RNG needs to be configured like in M0 core, i.e. with HSI48 */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS | RCC_PERIPHCLK_RFWAKEUP
                                             | RCC_PERIPHCLK_CLK48SEL | RCC_PERIPHCLK_USB
                                             | RCC_PERIPHCLK_RNG;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;
  PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE0;
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
#endif /* ARDUINO_STM32WB5MM_DK */
