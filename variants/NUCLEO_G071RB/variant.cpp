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
  PC_5,  //D0
  PC_4,  //D1
  PA_10, //D2
  PB_3,  //D3
  PB_5,  //D4
  PB_4,  //D5
  PB_14, //D6
  PA_8,  //D7
  PA_9,  //D8
  PC_7,  //D9
  PB_0,  //D10
  PA_7,  //D11/A6
  PA_6,  //D12/A7
  PA_5,  //D13/LED
  PB_9,  //D14
  PB_8,  //D15
  // ST Morpho
  // CN7 Left Side
  PC_10, //D16
  PC_12, //D17
  PA_14, //D18/SWD
  PD_0,  //D19
  PD_3,  //D20
  PA_13, //D21/SWD
  PD_4,  //D22
  PA_15, //D23
  PB_7,  //D24
  PC_13, //D25
  PC_14, //D26
  PC_15, //D27
  PF_0,  //D28
  PF_1,  //D29
  PC_2,  //D30
  PC_3,  //D31
  // CN7 Right Side
  PC_11, //D32
  PD_2,  //D33
  PD_1,  //D34
  PD_5,  //D35
  // CN10 Left Side
  PC_9,  //D36
  // CN10 Right side
  PC_8,  //D37
  PC_6,  //D38
  PA_3,  //D39
  PD_6,  //D40
  PA_11, //D41
  PA_12, //D42
  PC_1,  //D43
  PC_0,  //D44
  PB_2,  //D45/A8
  PB_6,  //D46
  PB_15, //D47
  PB_10, //D48/A9
  PB_13, //D49
  PA_2,  //D50
  PD_8,  //D51
  PD_9,  //D52
  PA_0,  //D53/A0
  PA_1,  //D54/A1
  PA_4,  //D55/A2
  PB_1,  //D56/A3
  PB_11, //D57/A4
  PB_12  //D58/A5
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  53, //A0
  54, //A1
  55, //A2
  56, //A3
  57, //A4
  58, //A5
  11, //A6
  12, //A7
  45, //A8
  48  //A9
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
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 1
  *            PLL_N                          = 8
  *            PLL_R                          = 2
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
