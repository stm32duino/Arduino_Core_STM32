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
#if defined(ARDUINO_PX_HER0)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PA_6,   // GPIO0
  PA_5,   // GPIO1
  PA_1,   // GPIO2
  PA_0,   // GPIO3
  PC_3,   // GPIO4
  PC_2,   // GPIO5
  PC_1,   // GPIO6
  PB_7,   // GPIO7
  PH_0,   // USR_LED
  PC_0,   // LCD_BTN_1_LT
  PH_1,   // LCD_BTN_2_RT
  PC_13,  // LCD_BTN_3_UP
  PC_12,  // LCD_BTN_4_DN
  PA_15,  // LCD_BTN_5_YES
  PC_9,   // LCD_BTN_6_NO
  PA_8,   // USB_DET
  PB_11,  // LCD_RS
  PB_12,  // LCD_BACKLIGHT
  PC_6,   // PWM_BUZZER
  PC_7,   // VBAT_MEAS_EN
  PC_8,   // PWR_HOLD

  PA_9,   // UART1_TX
  PA_10,  // UART1_RX
  PA_2,   // UART2_TX
  PA_3,   // UART2_RX
  PC_10,  // UART4_TX
  PC_11,  // UART4_RX

  PB_8,   // I2C1_SCL
  PB_9,   // I2C1_SDA

  PB_6,   // SPI1_CS
  PB_3,   // SPI1_SCK
  PB_5,   // SPI1_MOSI
  PB_4,   // SPI1_MISO

  PB_2,   // SPI2_CS_SF
  PB_10,  // SPI2_CS_LCD
  PD_2,   // SPI2_CS_SD
  PB_13,  // SPI2_SCK
  PB_15,  // SPI2_MOSI
  PB_14,  // SPI2_MISO

  PA_4,   // DAC1

  PB_0,   // ADC0
  PC_5,   // ADC1
  PC_4,   // ADC2
  PA_7,   // ADC3
  PB_1,   // ADC_VBAT
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  40, // A0
  41, // A1
  42, // A2
  43, // A3
  44  // A4
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE
                                     | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2
                                       | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_RTC
                                       | RCC_PERIPHCLK_USB;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_PX_HER0 */
