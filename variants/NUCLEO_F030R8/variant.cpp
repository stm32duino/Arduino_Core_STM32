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

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
  PA_3,  //D0
  PA_2,  //D1
  PA_10, //D2
  PB_3,  //D3 - no PWM
  PB_5,  //D4
  PB_4,  //D5
  PB_10, //D6 - no PWM
  PA_8,  //D7
  PA_9,  //D8
  PC_7,  //D9
  PB_6,  //D10
  PA_7,  //D11
  PA_6,  //D12
  PA_5,  //D13
  PB_9,  //D14
  PB_8,  //D15
// ST Morpho
// CN7 Left Side
  PC_10, //D16
  PC_12, //D17
  PF_6,  //D18
  PF_7,  //D19
  PA_13, //D20 - SWD
  PA_14, //D21 - SWD
  PA_15, //D22
  PB_7,  //D23
  PC_13, //D24
  PC_14, //D25
  PC_15, //D26
  PF_0,  //D27
  PF_1,  //D28
  PC_2,  //D29
  PC_3,  //D30
// CN7 Right Side
  PC_11, //D31
  PD_2,  //D32
// CN10 Left Side
  PC_9,  //D33
// CN10 Right side
  PC_8,  //D34
  PC_6,  //D35
  PC_5,  //D36
  PA_12, //D37
  PA_11, //D38
  PB_12, //D39
  PB_11, //D40
  PB_2,  //D41
  PB_1,  //D42
  PB_15, //D43
  PB_14, //D44
  PB_13, //D45
  PC_4,  //D46
  PF_5,  //D47
  PF_4,  //D48
  PA_0,  //D49/A0
  PA_1,  //D50/A1
  PA_4,  //D51/A2
  PB_0,  //D52/A3
  PC_1,  //D53/A4
  PC_0,  //D54/A5
  // Duplicated pins in order to be aligned with PinMap_ADC
  PA_7,  //D55/A6  = D11
  PA_6,  //D56/A7  = D12
  PC_2,  //D57/A8  = D29
  PC_3,  //D58/A9  = D30
  PC_5,  //D59/A10 = D36
  PC_4   //D60/A11 = D46
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
HardwareSerial  Serial(PA_3, PA_2); //Connected to ST-Link
#ifdef ENABLE_SERIAL1
HardwareSerial  Serial1(PA_10, PA_9);
#endif

void serialEvent() __attribute__((weak));
void serialEvent() { }
#ifdef ENABLE_SERIAL1
void serialEvent1() __attribute__((weak));
void serialEvent1() { }
#endif

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
#ifdef ENABLE_SERIAL1
  if (Serial1.available()) serialEvent1();
#endif
}

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI/2)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = 1
  *            PLLMUL                         = 12
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* No HSE Oscillator on Nucleo, Activate PLL with HSI/2 as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 15;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
