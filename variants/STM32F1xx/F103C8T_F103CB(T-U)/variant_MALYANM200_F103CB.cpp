/*
 *******************************************************************************
 * Copyright (c) 2018-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_MALYANM200_F103CB)
#include "pins_arduino.h"
#include <wiring.h>

// Pin number
const PinName digitalPin[] = {
  /* USB connector on the top, MCU side */
  /* Left Side */
  PB_9,  //D0
  PB_8,  //D1
  PB_7,  //D2
  PB_6,  //D3
  PB_5,  //D4
  PB_4,  //D5
  PB_3,  //D6
  PA_15, //D7
  PA_12, //D8 - USB DP
  PA_11, //D9 - USB DM
  PA_10, //D10
  PA_9,  //D11
  PA_8,  //D12
  PB_15, //D13
  PB_14, //D14
  PB_13, //D15
  PB_12, //D16
  /* Right side */
  PC_13, //D17 - LED
  PC_14, //D18
  PC_15, //D19
  PA_0,  //D20/A0
  PA_1,  //D21/A1
  PA_2,  //D22/A2
  PA_3,  //D23/A3
  PA_4,  //D24/A4
  PA_5,  //D25/A5
  PA_6,  //D26/A6
  PA_7,  //D27/A7
  PB_0,  //D28/A8
  PB_1,  //D29/A9
  PB_10, //D30
  PB_11, //D31
  PB_2,  //D32 - BOOT1
  PA_13, //D33 - SWDI0
  PA_14, //D34 - SWCLK
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  20, // A0
  21, // A1
  22, // A2
  23, // A3
  24, // A4
  25, // A5
  26, // A6
  27, // A7
  28, // A8
  29  // A9
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLL_Source                     = HSE
  *            PLL_Mul                        = 9
  *            Flash Latency(WS)              = 2
  *            ADC Prescaler                  = 6
  *            USB Prescaler                  = 1.5
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_MALYANM200_F103CB */
