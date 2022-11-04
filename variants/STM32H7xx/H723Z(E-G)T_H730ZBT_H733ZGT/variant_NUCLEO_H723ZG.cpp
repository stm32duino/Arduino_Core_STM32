/*
 *******************************************************************************
 * Copyright (c) 2022, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_NUCLEO_H723ZG)
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PB_7,
  PB_6,
  PG_14,
  PE_13,
  PE_14,
  PE_11,
  PE_9,
  PG_12,
  PF_3,
  PD_15,
  PD_14,
  PB_5,
  PA_6,
  PA_5,
  PB_9,
  PB_8,
  PC_6,
  PB_15,
  PB_13,
  PB_12,
  PA_15,
  PC_7,
  PB_5,
  PB_3,
  PA_4,
  PB_4,
  PG_6,
  PB_2,
  PD_13,
  PD_12,
  PD_11,
  PE_2,
  PA_0,
  PB_0,
  PE_0,
  PB_11,
  PB_10,
  PE_15,
  PE_6,
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
  PG_2,
  PG_3,
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
  PE_9,
  PB_2,
  PA_3,
  PC_0,
  PC_3_C,
  PB_1,
  PC_2_C,
  PF_10,
  PF_4,
  PF_5,
  PF_6,
  PF_11,
  PA_1,
  PA_2,
  PA_7,
  PA_8,
  PA_9,
  PA_10,
  PA_11,
  PA_12,
  PA_13,
  PA_14,
  PB_14,
  PC_1,
  PC_4,
  PC_5,
  PC_13,
  PC_14,
  PC_15,
  PD_8,
  PD_9,
  PD_10,
  PE_1,
  PF_12,
  PF_13,
  PF_14,
  PF_15,
  PG_4,
  PG_5,
  PG_7,
  PG_8,
  PG_9,
  PG_10,
  PG_11,
  PG_13,
  PG_15,
  PH_0,
  PH_1
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  73,  // A0
  74,  // A1
  75,  // A2
  76,  // A3
  77,  // A4
  78,  // A5
  79,  // A6
  80,  // A7
  81,  // A8
  82,  // A9
  83,  // A10
  84,  // A11
  85,  // A12
  94,  // A13
  95,  // A14
  96,  // A15
  104, // A16
  105, // A17
  106, // A18
  8,   // A19
  12,  // A20
  13,  // A21
  24,  // A22
  32,  // A23
  33,  // A24
  61,  // A25
  62,  // A26
  63   // A27
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 275;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_ */
