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
//P1 connector Right side
  PC0,  //D0
  PC2,  //D1
  PA0,  //D2
  PA2,  //D3
  PA4,  //D4
  PA6,  //D5
  PC4,  //D6
  PB0,  //D7
  PB2,  //D8
  PE8,  //D9
  PE10, //D10
  PE12, //D11
  PE14, //D12
  PB10, //D13
  PB12, //D14
  PB14, //D15
  PD8,  //D16
  PD10, //D17
  PD12, //D18
  PD14, //D19
//P2 connector Left side  
  PH0,  //D20
  PC14, //D21
  PE6,  //D22
  PE4,  //D23
  PE2,  //D24
  PE0,  //D25
  PB8,  //D26
  PB6,  //D27
  PB4,  //D28
  PD7,  //D29
  PD5,  //D30
  PD3,  //D31
  PD1,  //D32
  PC12, //D33
  PC10, //D34
  PA10, //D35
  PA8,  //D36
  PC8,  //D37
  PC6,  //D38
//P1 Connector Left Side
  PC1,  //D39
  PC3,  //D40
  PA1,  //D41
  PA3,  //D42
  PA5,  //D43
  PA7,  //D44
  PC5,  //D45
  PB1,  //D46
  PE7,  //D47
  PE9,  //D48
  PE11, //D49
  PE13, //D50
  PE15, //D51
  PB11, //D52
  PB13, //D53
  PB15, //D54
  PD9,  //D55
  PD11, //D56
  PD13, //D57
  PD15, //D58
//P2 connector Right side
  PH1,  //D59
  PC15, //D60
  PC13, //D61
  PE5,  //D62
  PE3,  //D63
  PE1,  //D64
  PB9,  //D65
  PB7,  //D66
  PB5,  //D67
  PB3,  //D68
  PD6,  //D69
  PD4,  //D70
  PD2,  //D71
  PD0,  //D72
  PC11, //D73
  PA15, //D74
  PA13, //D75
  PA9,  //D76
  PC9,  //D77
  PC7,  //D78
//Duplicated to have A0-A5 as F407 do not have Uno like connector
  PA0,  //D79/A0
  PA1,  //D80/A1
  PA2,  //D81/A2
  PA3,  //D82/A3
  PB0,  //D83/A4
  PB1   //D84/A5
// Here we could continue to define Analog pin if we want A6,...
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */

UARTClass Serial(USART3_E);    //available on PD8/PD9

void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
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
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
