/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_VAKE_V1)

#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_3,
  PA_2,
  PA_10,
  PB_3,
  PB_5,
  PB_4,
  PB_10,
  PA_8,
  PA_9,
  PC_7,
  PB_6,
  PA_7,
  PA_6,
  PA_5,
  PB_9,
  PB_8,
  PC_10,
  PC_12,
  NC,     // BOOT0
  PA_13,
  PA_14,
  PA_15,
  PB_7,
  PC_13,
  PC_14,
  PC_15,
  PH_0,
  PH_1,
  PC_2,
  PC_3,
  PC_11,
  PD_2,
  PC_9,
  PC_8,
  PC_6,
  PC_5,
  PA_12,
  PA_11,
  PB_12,
  NC,
  PB_2,
  PB_1,
  PB_15,
  PB_14,
  PB_13,
  PC_4,
  PB_11,
  PD_0,
  PD_1,
  PD_3,
  PD_4,
  PD_5,
  PD_6,
  PD_7,
  PD_8,
  PD_9,
  PD_10,
  PD_11,
  PD_12,
  PD_13,
  PD_14,
  PD_15,
  PE_0,
  PE_1,
  PE_2,
  PE_3,
  PE_4,
  PE_5,
  PE_6,
  PE_7,
  PE_8,
  PE_9,
  PE_10,
  PE_11,
  PE_12,
  PE_13,
  PE_14,
  PE_15,
  PA_0,
  PA_1,
  PA_4,
  PB_0,
  PC_1,
  PC_0
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  //A0
  1,  //A1
  82, //A2
  83, //A3
  28, //A4
  29  //A5
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 8
  *            PLL_N                          = 180
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLRCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }
}
#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_VAKE_V1 */
