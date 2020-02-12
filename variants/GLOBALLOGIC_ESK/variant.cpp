/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 *
 * Author: Sergey Shcherbakov 2020
 * As a base used board_template/variant.cpp
 */

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
  /* Test pins */
  PC_2,  // D0 - TP2
  PE_6,  // D1 - TP3
  PC_13, // D2 - TP4
  PA_3,  // D3 - TP5
  PE_5,  // D4 - TP6
  PD_6,  // D5 - TP7
  PD_3,  // D6 - TP8
  PD_2,  // D7 - TP9
  PB_14, // D8 - TP10
  PB_15, // D9 - TP11
  PA_8,  // D10 - TP12

  /* Button switches */
  PC_11, // D11 - SW1
  PA_15, // D12 - SW2
  PC_9,  // D13 - SW3
  PC_6,  // D14 - SW4
  PC_8,  // D15 - SW5

  /* WH1602 Char Display */
  PE_7,  // D16 - DISP_RS
  PE_10, // D17 - DISP_RW
  PE_11, // D18 - DISP_ENA
  PE_12, // D19 - DISP_DB4
  PE_13, // D20 - DISP_DB5
  PE_14, // D21 - DISP_DB6
  PE_15, // D22 - DISP_DB7
  PE_9,  // D23 - Display backlight open-drain output

  /* Ethernet */
  PB_0,  // D24 - ETH_UP_LED#, it's should be used by Ethernet driver
  PE_8,  // D25 - RMII_PHY_INT#, it's should be used by Ethernet driver _ONLY_
  PD_10, // D26 - RMII_PHY_RST#, it's should be used by Ethernet driver _ONLY_

  /* MEMS */
  PE_4,  // D27 - MEMS_INT1#_A/G
  PE_2,  // D28 - MEMS_INT2#_A/G
  PB_8,  // D29 - MEMS_INT#_M

  /* USART3 */
  PD_9,  // D30 - USART3_RX
  PD_8,  // D31 - USART3_TX

  /* I2C */
  PB_6,  // D32 - I2C1_SCL
  PB_9,  // D33 - I2C1_SDA

  /* SPI */
  PA_5,  // D34 - SPI1_SCK
  PB_5,  // D35 - SPI1_MOSI
  PB_4,  // D36 - SPI1_MISO
  PD_7,  // D37 - SPI1_CS0#

  /* CAN */
  PD_0,  // D38 - CAN1_RX
  PD_1,  // D39 - CAN1_TX

  /* Other */
  PB_7,  // D40 - PWM_EN
  PB_1,  // D41 - ADC only, i.e. it's connected to Temperature Sensor

  /* LEDS */
  PD_12, // D42 - Green LED
  PD_13, // D43 - Orange LED
  PD_14, // D44 - Red LED
  PD_15, // D45 - Blue LED

  /* DHT11 */
  PD_11, // D46 - DHT11 senor input
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  41,  //A0 - Temp Sensor
  3,   //A1 - PA3
  0    //A2 - PC2
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
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 144000000
  *            HCLK(Hz)                       = 144000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 288
  *            PLL_P                          = 2
  *            PLL_Q                          = 6
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  * @note: 144MHz frequency is used to provide standard CAN bitrates
  */
WEAK void SystemClock_Config(void)
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
  RCC_OscInitStruct.PLL.PLLN = 288;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 6;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // 144MHz/1 = 144MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  // 144MHz/4 = 36MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  // 144MHz/2 = 72MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001) {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

#ifdef __cplusplus
}
#endif
