/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_ETHERCAT_DUINO)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PC_11,    // D0 / RX0
  PC_10,    // D1 / TX0
  PB_14,    // D2
  PD_12,    // D3
  PD_13,    // D4
  PD_14,    // D5
  PD_15,    // D6
  PC_6,     // D7
  PC_7,     // D8
  PC_8,     // D9
  PC_9,     // D10
  PA_8,     // D11
  PA_9,     // D12
  PA_15,    // D13
  PD_5,     // D14
  PD_6,     // D15
  PB_10,    // D16
  PB_11,    // D17 / SPI_SS
  PE_8,     // D18
  PE_7,     // D19
  PF_15,    // D20
  PF_14,    // D21
  PG_6,     // D22
  PG_7,     // D23
  PG_4,     // D24
  PG_5,     // D25
  PG_2,     // D26
  PG_3,     // D27
  PE_11,    // D28
  PE_15,    // D29
  PE_9,     // D30
  PE_10,    // D31
  PG_0,     // D32
  PG_1,     // D33
  PF_13,    // D34
  PF_12,    // D35
  PF_11,    // D36
  PG_9,     // D37
  PG_10,    // D38
  PG_11,    // D39
  PG_12,    // D40
  PG_13,    // D41
  PG_14,    // D42
  PF_10,    // D43
  PF_4,     // D44 / A14
  PF_3,     // D45 / A15
  PC_14,    // D46
  PC_15,    // D47
  PC_13,    // D48
  PE_6,     // D49
  PE_5,     // D50
  PE_4,     // D51
  PE_3,     // D52
  PE_2,     // D53
  PC_0,     // A0
  PC_1,     // A1
  PC_2,     // A2
  PC_3,     // A3
  PA_0,     // A4
  PA_1,     // A5
  PA_2,     // A6
  PA_3,     // A7
  PA_6,     // A8
  PA_7,     // A9
  PC_4,     // A10
  PC_5,     // A11
  PA_5,     // DAC0 / A12
  PA_4,     // DAC1 / A13
  PD_0,     // CANRX
  PD_1,     // CANTX
  PB_3,     // LED_1 / LED_BUILTIN
  PB_8,     // SCL1
  PB_9,     // SDA1
  PE_12,    // MOSI
  PE_13,    // MISO
  PE_14,    // SCK
  PG_15,    // LED_2
  PA_11,    // USB_DM
  PA_12,    // USB_DP
  PF_0,     // ECAT_SYNC0
  PF_1,     // ECAT_SYNC1
  PF_2,     // ECAT_IRQ
  PF_5,     // ECAT_RST
  PF_6,     // ECAT_D3
  PF_7,     // ECAT_D2
  PF_8,     // ECAT_D0
  PF_9,     // ECAT_D1
  PB_2,     // ECAT_SCK
  PB_4,     // ECAT_LED_RUN
  PB_5,     // ECAT_LED_ERR
  PB_6      // ECAT_CS
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  54, // A0,   PC0
  55, // A1,   PC1
  56, // A2,   PC2
  57, // A3,   PC3
  58, // A4,   PA0
  59, // A5,   PA1
  60, // A6,   PA2
  61, // A7,   PA3
  62, // A8,   PA6
  63, // A9,   PA7
  64, // A10,  PC4
  65, // A11,  PC5
  66, // A12,  PA5
  67, // A13,  PA4
  44, // A14,  PF4
  45  // A15,  PF3
};

#ifdef __cplusplus
extern "C"
{
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Activate the Over-Drive mode */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_ETHERCAT_DUINO */
