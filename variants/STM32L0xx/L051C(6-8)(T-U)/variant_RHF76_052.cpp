/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_RHF76_052)

#include "pins_arduino.h"

const PinName digitalPin[] = {
  PA_1,  //D0 - RFSW0
  PA_2,  //D1 - RFSW1
  PA_4,  //D2 - NSS
  PA_5,  //D3 - CLK
  PA_6,  //D4 - MISO
  PA_7,  //D5 - MOSI
  PB_0,  //D6 - DIO2
  PB_1,  //D7 - DIO3
  PB_2,  //D8 - DIO1
  PB_4,  //D9 - Status LED trigger, connect to an external LED to show status of LoRaWAN processing
  PB_5,  //D10 - Status LED trigger, connect to an external LED, Reserved
  PB_10, //D11 - DIO0
  PB_11, //D12 - NRST
  PC_0,  //D13
  PB_6,  //D14 - UART_TX
  PB_7,  //D15 - UART_RX
  PA_9,  //D16 - UART_TX
  PA_10  //D17 - UART_RX
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_RHF76_052 */
