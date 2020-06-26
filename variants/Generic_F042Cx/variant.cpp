/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Digital PinName array
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  PA_0,   //USART2_CTS          TIM2_CH1/TIM2_ETR      TSC_G1_IO1
  PA_1,   //EVENTOUT            USART2_DE/USART2_RTS   TIM2_CH2    TSC_G1_IO2
  PA_2,   //USART2_TX           TIM2_CH3               TSC_G1_IO3
  PA_3,   //USART2_RX           TIM2_CH4               TSC_G1_IO4
  PA_4,   //I2S1_WS/SPI1_NSS    USART2_CK   USB_NOE    TSC_G2_IO1    TIM14_CH1
  PA_5,   //I2S1_CK/SPI1_SCK    CEC         TIM2_CH1/TIM2_ETR    TSC_G2_IO2
  PA_6,   //I2S1_MCK/SPI1_MISO  TIM3_CH1    TIM1_BKIN    TSC_G2_IO3        TIM16_CH1
  PA_7,   //I2S1_SD/SPI1_MOSI   TIM3_CH2    TIM1_CH1N    TSC_G2_IO4    TIM14_CH1    TIM17_CH1
  PA_8,   //RCC_MCO             USART1_CK   TIM1_CH1    EVENTOUT    CRS_SYNC
  PA_9,   //USART1_TX           TIM1_CH2    TSC_G4_IO1    I2C1_SCL
  PA_10,  //TIM17_BKIN          USART1_RX   TIM1_CH3    TSC_G4_IO2    I2C1_SDA
  PA_11,  //USB_DM              EVENTOUT    USART1_CTS    TIM1_CH4    TSC_G4_IO3    CAN_RX    I2C1_SCL
  PA_12,  //USB_DP              EVENTOUT    USART1_DE/USART1_RTS    TIM1_ETR    TSC_G4_IO4    CAN_TX    I2C1_SDA
  PA_13,  //SYS_SWDIO           IR_OUT      USB_NOE
  PA_14,  //SYS_SWCLK           USART2_TX
  PA_15,  //I2S1_WS/SPI1_NSS    USART2_RX   TIM2_CH1/TIM2_ETR    EVENTOUT        USB_NOE
  PB_0,   //EVENTOUT            TIM3_CH3    TIM1_CH2N    TSC_G3_IO2
  PB_1,   //TIM14_CH1           TIM3_CH4    TIM1_CH3N    TSC_G3_IO3
  PB_2,   //TSC_G3_IO4
  PB_3,   //I2S1_CK/SPI1_SCK    EVENTOUT    TIM2_CH2    TSC_G5_IO1
  PB_4,   //I2S1_MCK/SPI1_MISO  TIM3_CH1    EVENTOUT    TSC_G5_IO2        TIM17_BKIN
  PB_5,   //I2S1_SD/SPI1_MOSI   TIM3_CH2    TIM16_BKIN    I2C1_SMBA
  PB_6,   //USART1_TX           I2C1_SCL    TIM16_CH1N    TSC_G5_IO3
  PB_7,   //USART1_RX           I2C1_SDA    TIM17_CH1N    TSC_G5_IO4
  PB_8,   //CEC                 I2C1_SCL    TIM16_CH1    TSC_SYNC    CAN_RX
  PB_9,    //IR_OUT              I2C1_SDA    TIM17_CH1    EVENTOUT    CAN_TX    SPI2_NSS
  PB_10,  //CEC    I2C1_SCL     TIM2_CH3    TSC_SYNC     SPI2_SCK
  PB_11,  //EVENTOUT            I2C1_SDA    TIM2_CH4
  PB_12,  //SPI2_NSS            EVENTOUT    TIM1_BKIN
  PB_13,  //SPI2_SCK            TIM1_CH1N
  PB_14,  //SPI2_MISO           TIM1_CH2N
  PB_15,  //SPI2_MOSI           TIM1_CH3N
  PC_13,  //
  PF_0,   //I2C1_SDA            CRS_SYNC               I2C1_SDA
  PF_1,   //I2C1_SCL            I2C1_SCL
  PF_11,  //
};

// If analog pins are not contiguous in the digitalPin array:
// Add the analogInputPin array without defining NUM_ANALOG_FIRST
// Analog (Ax) pin number array
// where x is the index to retrieve the digital pin number
const uint32_t analogInputPin[] = {
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7
};

#ifdef __cplusplus
}
#endif

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit;
  RCC_CRSInitTypeDef RCC_CRSInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  __HAL_RCC_CRS_CLK_ENABLE();

  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;
  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
