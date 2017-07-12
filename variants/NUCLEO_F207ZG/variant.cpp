/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
// Match Table Table 16. NUCLEO-F207ZG pin assignments
// from UM1974 STM32 Nucleo-144 board
const PinName digitalPin[] = {
  PG9,  //D0
  PG14, //D1
  PF15, //D2
  PE13, //D3
  PF14, //D4
  PE11, //D5
  PE9,  //D6
  PF13, //D7
  PF12, //D8
  PD15, //D9
  PD14, //D10
  PA7,  //D11 - If SB121, SB122 (ON,OFF) connected to PA7 (default, see D71)
        //      else SB121, SB122 (OFF,ON) connected to PB5 (D22)
  PA6,  //D12
  PA5,  //D13
  PB9,  //D14
  PB8,  //D15
  PC6,  //D16
  PB15, //D17
  PB13, //D18 - used as I2S_A_CK and connected to CN7 pin 5 by default, if JP7 is ON, 
        //      it is also connected to Ethernet PHY as RMII_TXD1. In this case only 
		//      one function of Ethernet or I2S_A must be used.
  PB12, //D19
  PA15, //D20
  PC7,  //D21
  PB5,  //D22 - D11 if SB121 off, SB122 on
  PB3,  //D23
  PA4,  //D24
  PB4,  //D25
  PB6,  //D26
  PB2,  //D27
  PD13, //D28
  PD12, //D29
  PD11, //D30
  PE2,  //D31 - PE2 is connected to both CN9 pin 14 (I/O) and CN10 pin 25 (I/O).
        //      Only one connector pin must be used at one time. 
  PA0,  //D32
  PB0,  //D33 - LED1
  PE0,  //D34
  PB11, //D35
  PB10, //D36
  PE15, //D37
  PE14, //D38
  PE12, //D39
  PE10, //D40
  PE7,  //D41
  PE8,  //D42
  PC8,  //D43
  PC9,  //D44
  PC10, //D45
  PC11, //D46
  PC12, //D47
  PD2,  //D48
  PG2,  //D49
  PG3,  //D50
  PD7,  //D51
  PD6,  //D52
  PD5,  //D53
  PD4,  //D54
  PD3,  //D55
  PE2,  //D56 - connected to both CN9 pin 14 (I/O) and CN10 pin 25 (I/O). 
        //      Only one connector pin must be used at one time
  PE4,  //D57
  PE5,  //D58
  PE6,  //D59
  PE3,  //D60
  PF8,  //D61
  PF7,  //D62
  PF9,  //D63
  PG1,  //D64
  PG0,  //D65
  PD1,  //D66
  PD0,  //D67
  PF0,  //D68
  PF1,  //D69
  PF2,  //D70
  PA7,  //D71 - used as D11 and connected to CN7 pin 14 by default, if JP6 is ON,
        //     it is also connected to both Ethernet PHY as RMII_DV and CN9 pin 15.
        //     In this case only one function of the Ethernet or D11 must be used. 
  NC,   //D72
  PB7,  //D73 - LED_BLUE
  PB14, //D74 - LED_RED
  PC13, //D75 - USER_BTN
  PD9,  //D76 - Serial Rx
  PD8,  //D77 - Serial Tx
  PA3,  //D78/A0
  PC0,  //D79/A1
  PC3,  //D80/A2
  PF3,  //D81/A3
  PF5,  //D82/A4
  PF10, //D83/A5
  PB1,  //D84/A6
  PC2,  //D85/A7
  PF4,  //D86/A8
  PF6,  //D87/A9
  // Duplicated pins in order to be aligned with PinMap_ADC
  PA7,  //D88/A10 = D11/D71
  PA6,  //D89/A11 = D12
  PA5,  //D90/A12 = D13
  PA4,  //D91/A13 = D24
  PA0,  //D92/A14 = D32
  PF8,  //D93/A15 = D61
  PF7,  //D94/A16 = D62
  PF9   //D95/A17 = D63
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
HardwareSerial  Serial(PD9, PD8); // Connected to ST-Link

void serialEvent() __attribute__((weak));
void serialEvent() { }

#ifdef ENABLE_SERIAL1
HardwareSerial  Serial1(PG9, PG14);

void serialEvent1() __attribute__((weak));
void serialEvent1() { }
#endif
#ifdef ENABLE_SERIAL2
HardwareSerial  Serial2(PD6, PD5);

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
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    while(1);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
