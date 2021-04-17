/*
 *******************************************************************************
 * Copyright (c) 2017-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_BLUE_F407VE_MINI)

#include "pins_arduino.h"

// Pin number
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  //External (left to right)
  //GND
  //VBAT
  //5V
  PE_0,   //D0
  PE_2,
  PE_4,
  PE_6,
  PC_14,  //OSC32_IN
  PC_0,
  PC_2,
  PA_0,
  PA_1,
  PA_4,
  PA_6,   //D10
  PC_4,
  PB_0,
  PB_2,
  PE_8,
  PE_9,
  PE_11,
  PE_13,
  PE_15,
  PB_11,
  PB_13,  //D20
  PB_15,
  PD_9,
  PD_11,
  PD_13,
  PD_15,
  PC_6,
  PC_8,
  PC_9,
  PA_9,
  PA_11,  //D30 - USB_DM
  PA_13,
  PA_15,
  PC_11,
  PC_12,
  PD_1,
  PD_3,
  PD_5,
  PD_7,
  PB_4,
  PB_6,   //D40
  PB_8,
  //GND
  //3V3
  //GND
  //Internal (left to right)
  //GND
  //3V3
  //5V
  PE_1,
  PE_3,
  PE_5,
  PC_13,
  PC_15,  //OSC32_OUT
  PC_1,
  PC_3,
  PA_2,
  PA_3,   //D50
  PA_5,
  PA_7,
  PC_5,
  PB_1,
  PE_7,
  PE_10,
  PE_12,
  PE_14,
  PB_10,
  PB_12,  //D60
  PB_14,
  PD_8,
  PD_10,
  PD_12,
  PD_14,
  PC_7,
  PA_8,
  PA_10,
  PA_12,  //USB_DP
  PA_14,  //D70
  PC_10,
  PD_0,
  PD_2,
  PD_4,
  PD_6,
  PB_3,
  PB_5,
  PB_7,
  PB_9    //D79 - LED
  //GND
  //3V3
  //GND
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  7,  //A0
  8,  //A1
  49, //A2
  50, //A3
  9,  //A4
  51, //A5
  12, //A6
  54, //A7
  5,  //A8
  47, //A9
  6,  //A10
  48, //A11
  11, //A12
  53, //A13
  10, //A14
  52  //A15
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
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
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

#endif /* ARDUINO_BLUE_F407VE_MINI */
