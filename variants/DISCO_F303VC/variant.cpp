/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
  PC_0,
  PC_2,
  PF_2,
  PA_0,
  PA_2,
  PA_4,
  PA_6,
  PC_4,
  PB_0,
  PB_2,
  PE_8,
  PE_10,
  PE_12,
  PE_14,
  PB_10,
  PB_12,
  PB_14,
  PD_8,
  PD_10,
  PD_12,
  PD_14,
  PC_7,
  PF_9,
  PF_0,
  PC_14,
  PE_6,
  PE_4,
  PE_2,
  PE_0,
  PB_8,
  PB_6,
  PB_4,
  PD_7,
  PD_5,
  PD_3,
  PD_1,
  PC_12,
  PC_10,
  PA_14,
  PF_6,
  PA_12,
  PA_10,
  PA_8,
  PC_8,
  PC_1,
  PC_3,
  PA_1,
  PA_3,
  PF_4,
  PA_5,
  PA_7,
  PC_5,
  PB_1,
  PE_7,
  PE_9,
  PE_11,
  PE_13,
  PE_15,
  PB_11,
  PB_13,
  PB_15,
  PD_9,
  PD_11,
  PD_13,
  PD_15,
  PC_6,
  PF_10,
  PF_1,
  PC_15,
  PC_13,
  PE_5,
  PE_3,
  PE_1,
  PB_9,
  PB_7,
  PB_5,
  PB_3,
  PD_6,
  PD_4,
  PD_2,
  PD_0,
  PC_11,
  PA_15,
  PA_13,
  PA_11,
  PA_9,
  PC_9
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,
  1,
  2,
  7,
  8,
  9,
  15,
  16,
  17,
  18,
  19,
  20,
  44,
  45,
  48,
  51,
  52,
  53,
  59,
  60,
  61,
  62,
  63
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
