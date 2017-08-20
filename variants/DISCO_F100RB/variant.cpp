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

// Pin number following UM0919 table 4,5 and 6
const PinName digitalPin[] = {
// P1 connector
  PC_13, //D0
  PC_0,  //D1
  PC_1,  //D2
  PC_2,  //D3
  PC_3,  //D4
  PA_0,  //D5 - User button
  PA_1,  //D6
  PA_2,  //D7
  PA_3,  //D8
  PA_4,  //D9
  PA_5,  //D10
  PA_6,  //D11
  PA_7,  //D12
  PC_4,  //D13
  PC_5,  //D14
  PB_0,  //D15
  PB_1,  //D16
  PB_2,  //D17
// P2 connector
  PC_6,  //D18
  PC_7,  //D19
  PC_8,  //D20 - LED blue
  PC_9,  //D21 - LED green
  PA_8,  //D22
  PA_9,  //D23
  PA_10, //D24
  PA_11, //D25
  PA_12, //D26
  PA_13, //D27
  PA_14, //D28
  PA_15, //D29
  PC_10, //D30
  PC_11, //D31
  PC_12, //D32
  PD_2,  //D33
  PB_3,  //D34
  PB_4,  //D35
  PB_5,  //D36 - I2C SCL
  PB_6,  //D37 - I2C SDA
  PB_7,  //D38
  PB_8,  //D39
  PB_9,  //D40
// P3 connector
  PB_10, //D41
  PB_11, //D42
  PB_12, //D43 - SPI SS
  PB_13, //D44 - SPI SCLK
  PB_14, //D45 - SPI MISO
  PB_15, //D46 - SPI MOSI
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC_0,  //D47/A0 = D0
  PC_1,  //D48/A1 = D1
  PC_2,  //D49/A2 = D2
  PC_3,  //D50/A3 = D3
  PA_0,  //D51/A4 = D4
  PA_1,  //D52/A5 = D5
  PA_2,  //D53/A6 = D6
  PA_3,  //D54/A7 = D7
  PA_4,  //D55/A8 = D8
  PA_5,  //D56/A9 = D9
  PA_6,  //D57/A10 = D10
  PA_7,  //D58/A11 = D11
  PC_4,  //D59/A12 = D12
  PC_5,  //D60/A13 = D13
  PB_0,  //D61/A14 = D14
  PB_1   //D62/A15 = D15
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */

 HardwareSerial Serial(PA_3, PA_2);
 #ifdef ENABLE_SERIAL1
 HardwareSerial Serial1(PA_10, PA_9);
 #endif
 #ifdef ENABLE_SERIAL2
 HardwareSerial Serial2(PB_11, PB_10);
 #endif

 void serialEvent() __attribute__((weak));
 void serialEvent() { }
 #ifdef ENABLE_SERIAL1
 void serialEvent1() __attribute__((weak));
 void serialEvent1() { }
 #endif
 #ifdef ENABLE_SERIAL2
 void serialEvent2() __attribute__((weak));
 void serialEvent2() { }
 #endif

 void serialEventRun(void)
 {
   if (Serial.available()) serialEvent();
 #ifdef ENABLE_SERIAL1
   if (Serial1.available()) serialEvent1();
 #endif
 #ifdef ENABLE_SERIAL2
   if (Serial2.available()) serialEvent2();
 #endif
 }

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 24000000
  *            HCLK(Hz)                       = 24000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            PLL_Source                     = HSE
  *            PLL_Mul                        = 6
  *            Flash Latency(WS)              = 0
  *            ADC Prescaler                  = 2
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    while(1);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
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
