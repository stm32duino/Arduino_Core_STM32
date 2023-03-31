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
 * SERVICES; LOSS OF USE, DATA, OR  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#if defined(ARDUINO_MICROMOD_F405)

#include "pins_arduino.h"

// Pin number
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  PC_0,   //D0
  PC_1,   //D1
  PC_6,   //PWM0
  PC_7,   //PWM1
  PA_2,   //TX1
  PA_3,   //RX1
  PD_2,   //G0
  PA_8,   //G1
  PA_0,   //G2
  PC_8,   //G3
  PC_9,   //G4
  PC_13,  //G5
  PC_2,   //G6
  PB_13,  //G10 HOST_VBUS
  PB_12,  //G11 HOST_ID
  PB_4,   //AUD_OUT
  PB_5,   //AUD_IN
  PA_4,   //AUD_LRCLK
  PB_3,   //AUD_BCLK
  PB_9,   //CAN_TX
  PB_8,   //CAN_RX
  PB_10,  //SCL
  PB_11,  //SDA
  PB_1,   //INT
  PB_6,   //SCL1
  PB_7,   //SDA1
  PA_5,   //SCK
  PA_7,   //COPI
  PA_6,   //CIPO
  PC_4,   //CS
  PB_14,  //HOST_D-
  PB_15,  //HOST_D+
  PA_15,  //STAT
  PC_5,   //A0
  PB_0,   //A1
  PA_1,   //BATT_VIN/3
  PC_14,  //OSC32
  PC_15,  //OSC32
  PA_11,  //D+
  PA_12,  //D-
  PA_13,  //SWDIO
  PA_14,  //SWCLK
  PC_10,  //FLASH_SCK
  PC_11,  //FLASH_SDO
  PC_12,  //FLASH_SDI
  PC_3    //FLASH_CS
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  33, // A0,  PC5
  34, // A1,  PB0
  35, // A2,  PA1
  8,  // A3,  PA0
  4,  // A4,  PA2
  5,  // A5,  PA3
  17, // A6,  PA4
  26, // A7,  PA5
  28, // A8,  PA6
  27, // A9,  PA7
  23, // A10, PB1
  0,  // A11, PC0
  1,  // A12, PC1
  12, // A13, PC2
  29  // A14, PC4
};

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
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /**Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  /* Ensure CCM RAM clock is enabled */
  __HAL_RCC_CCMDATARAMEN_CLK_ENABLE();

}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_MICROMOD_F405 */
