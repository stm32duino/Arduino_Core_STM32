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
const PinName digital_arduino[] = {
  PA3,  //D0
  PA2,  //D1
  PA10, //D2
  PB3,  //D3
  PB5,  //D4
  PB4,  //D5
  PB10, //D6
  PA8,  //D7
  PA9,  //D8
  PC7,  //D9
  PB6,  //D10
  PA7,  //D11
  PA6,  //D12
  PA5,  //D13
  PB9,  //D14
  PB8,  //D15
// ST Morpho
// CN7 Left Side
  PC10, //D16
  PC12, //D17
  PF11, //D18 - BOOT0
  PA13, //D19 - SWD
  PA14, //D20 - SWD
  PA15, //D21
  PB7,  //D22
  PC13, //D23
  PC14, //D24
  PC15, //D25
  PF0,  //D26
  PF1,  //D27
  PC2,  //D28
  PC3,  //D29
// CN7 Right Side
  PC11, //D30
  PD2,  //D31
// CN10 Left Side
  PC9,  //D32
// CN10 Right side
  PC8,  //D33
  PC6,  //D34
  PC5,  //D35
  PA12, //D36
  PA11, //D37
  PB12, //D38
  PB11, //D39
  PB2,  //D40
  PB1,  //D41
  PB15, //D42
  PB14, //D43
  PB13, //D44
  PC4,  //D45
  PA0,  //D46/A0
  PA1,  //D47/A1
  PA4,  //D48/A2
  PB0,  //D49/A3
  PC1,  //D50/A4
  PC0,  //D51/A5
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
HardwareSerial  Serial(PA3, PA2); //Connected to ST-Link
HardwareSerial  Serial1(PA10, PA9);
HardwareSerial  Serial2(PA1, PA0);

// Need rework to be generic

void serialEvent() __attribute__((weak));
void serialEvent() { }
void serialEvent1() __attribute__((weak));
void serialEvent1() { }
void serialEvent2() __attribute__((weak));
void serialEvent2() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
  if (Serial1.available()) serialEvent1();
  if (Serial2.available()) serialEvent2();
}

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void __libc_init_array(void);

uint32_t pinNametoPinNumber(PinName p)
{
  uint32_t i = 0;
  for(i = 0; i < NUM_DIGITAL_PINS; i++) {
	  if (digital_arduino[i] == p)
		  break;
  }
  return i;
}

void init( void )
{
  hw_config_init();
}

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
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* No HSE Oscillator on Nucleo, Activate PLL with HSI/2 as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
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
