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
  PG_9,  //D0
  PG_14, //D1
  PF_15, //D2
  PE_13, //D3
  PF_14, //D4
  PE_11, //D5
  PE_9,  //D6
  PF_13, //D7
  PF_12, //D8
  PD_15, //D9
  PD_14, //D10
  PA_7,  //D11 - If SB121, SB122 (ON,OFF) connected to PA7 (default, see D71)
         //      else SB121, SB122 (OFF,ON) connected to PB5 (D22)
  PA_6,  //D12
  PA_5,  //D13
  PB_9,  //D14
  PB_8,  //D15
  PC_6,  //D16
  PB_15, //D17
  PB_13, //D18 - used as I2S_A_CK and connected to CN7 pin 5 by default, if JP7 is ON,
         //      it is also connected to Ethernet PHY as RMII_TXD1. In this case only
         //      one function of Ethernet or I2S_A must be used.
  PB_12, //D19
  PA_15, //D20
  PC_7,  //D21
  PB_5,  //D22 - D11 if SB121 off, SB122 on
  PB_3,  //D23
  PA_4,  //D24
  PB_4,  //D25
  PB_6,  //D26
  PB_2,  //D27
  PD_13, //D28
  PD_12, //D29
  PD_11, //D30
  PE_2,  //D31 - PE2 is connected to both CN9 pin 14 (I/O) and CN10 pin 25 (I/O).
         //      Only one connector pin must be used at one time.
  PA_0,  //D32
  PB_0,  //D33 - LED1
  PE_0,  //D34
  PB_11, //D35
  PB_10, //D36
  PE_15, //D37
  PE_14, //D38
  PE_12, //D39
  PE_10, //D40
  PE_7,  //D41
  PE_8,  //D42
  PC_8,  //D43
  PC_9,  //D44
  PC_10, //D45
  PC_11, //D46
  PC_12, //D47
  PD_2,  //D48
  PG_2,  //D49
  PG_3,  //D50
  PD_7,  //D51
  PD_6,  //D52
  PD_5,  //D53
  PD_4,  //D54
  PD_3,  //D55
  PE_2,  //D56 - connected to both CN9 pin 14 (I/O) and CN10 pin 25 (I/O).
         //      Only one connector pin must be used at one time
  PE_4,  //D57
  PE_5,  //D58
  PE_6,  //D59
  PE_3,  //D60
  PF_8,  //D61
  PF_7,  //D62
  PF_9,  //D63
  PG_1,  //D64
  PG_0,  //D65
  PD_1,  //D66
  PD_0,  //D67
  PF_0,  //D68
  PF_1,  //D69
  PF_2,  //D70
  PA_7,  //D71 - used as D11 and connected to CN7 pin 14 by default, if JP6 is ON,
         //     it is also connected to both Ethernet PHY as RMII_DV and CN9 pin 15.
         //     In this case only one function of the Ethernet or D11 must be used.
  NC,    //D72
  PB_7,  //D73 - LED_BLUE
  PB_14, //D74 - LED_RED
  PC_13, //D75 - USER_BTN
  PD_9,  //D76 - Serial Rx
  PD_8,  //D77 - Serial Tx
  PA_3,  //D78/A0
  PC_0,  //D79/A1
  PC_3,  //D80/A2
  PF_3,  //D81/A3
  PF_5,  //D82/A4
  PF_10, //D83/A5
  PB_1,  //D84/A6
  PC_2,  //D85/A7
  PF_4,  //D86/A8
  PF_6,  //D87/A9
  // Duplicated pins in order to be aligned with PinMap_ADC
  PA_7,  //D88/A10 = D11/D71
  PA_6,  //D89/A11 = D12
  PA_5,  //D90/A12 = D13
  PA_4,  //D91/A13 = D24
  PA_0,  //D92/A14 = D32
  PF_8,  //D93/A15 = D61
  PF_7,  //D94/A16 = D62
  PF_9   //D95/A17 = D63
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
HardwareSerial  Serial(PD_9, PD_8); // Connected to ST-Link

void serialEvent() __attribute__((weak));
void serialEvent() { }

#ifdef ENABLE_SERIAL1
HardwareSerial  Serial1(PG_9, PG_14);

void serialEvent1() __attribute__((weak));
void serialEvent1() { }
#endif
#ifdef ENABLE_SERIAL2
HardwareSerial  Serial2(PD_6, PD_5);

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
