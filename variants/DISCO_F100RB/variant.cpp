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
  PC13, //D0
  PC0,  //D1
  PC1,  //D2
  PC2,  //D3
  PC3,  //D4
  PA0,  //D5 - User button
  PA1,  //D6
  PA2,  //D7
  PA3,  //D8
  PA4,  //D9
  PA5,  //D10
  PA6,  //D11
  PA7,  //D12
  PC4,  //D13
  PC5,  //D14
  PB0,  //D15
  PB1,  //D16
  PB2,  //D17
// P2 connector
  PC6,  //D18
  PC7,  //D19
  PC8,  //D20 - LED blue
  PC9,  //D21 - LED green
  PA8,  //D22
  PA9,  //D23
  PA10, //D24
  PA11, //D25
  PA12, //D26
  PA13, //D27
  PA14, //D28
  PA15, //D29
  PC10, //D30
  PC11, //D31
  PC12, //D32
  PD2,  //D33
  PB3,  //D34
  PB4,  //D35
  PB5,  //D36 - I2C SCL
  PB6,  //D37 - I2C SDA
  PB7,  //D38
  PB8,  //D39
  PB9,  //D40
// P3 connector
  PB10, //D41
  PB11, //D42
  PB12, //D43 - SPI SS
  PB13, //D44 - SPI SCLK
  PB14, //D45 - SPI MISO
  PB15, //D46 - SPI MOSI
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC0,  //D47/A0 = D0
  PC1,  //D48/A1 = D1
  PC2,  //D49/A2 = D2
  PC3,  //D50/A3 = D3
  PA0,  //D51/A4 = D4
  PA1,  //D52/A5 = D5
  PA2,  //D53/A6 = D6
  PA3,  //D54/A7 = D7
  PA4,  //D55/A8 = D8
  PA5,  //D56/A9 = D9
  PA6,  //D57/A10 = D10
  PA7,  //D58/A11 = D11
  PC4,  //D59/A12 = D12
  PC5,  //D60/A13 = D13
  PB0,  //D61/A14 = D14
  PB1   //D62/A15 = D15
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */

 HardwareSerial Serial(PA3, PA2);
 #ifdef ENABLE_SERIAL1
 HardwareSerial Serial1(PA10, PA9);
 #endif
 #ifdef ENABLE_SERIAL2
 HardwareSerial Serial2(PB11, PB10);
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

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
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
