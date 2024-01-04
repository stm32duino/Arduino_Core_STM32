/*
 *******************************************************************************
 * Copyright (c) 2023, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_STM32H573I_DK)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  // CN15 Arduino connector
  PB_11, // D0
  PB_10, // D1
  PG_15, // D2
  PB_5,  // D3
  PG_4,  // D4
  PH_11, // D5
  PH_10, // D6
  PG_5,  // D7
  // CN13 Arduino connector
  PG_8,  // D8
  PA_8,  // D9
  PA_3,  // D10/A6
  PB_15, // D11
  PI_2,  // D12
  PI_1,  // D13
  PB_7,  // D14
  PB_6,  // D15
  // CN16 Arduino connector
  PB_0,  // D16/A0
  PA_4,  // D17/A1
  PA_0,  // D18/A2
  PA_5,  // D19/A3
  PA_6,  // D20/A4
  PF_12, // D21/A5
  // User button,
  PC_13, // D22
  // User LED,
  PI_8,  // D23
  PI_9,  // D24
  PF_1,  // D25
  PF_4,  // D26
  // OSPI,
  PG_6,  // D27
  PF_10, // D28
  PB_2,  // D29
  PB_1,  // D30
  PD_12, // D31
  PC_2,  // D32
  PD_13, // D33
  PH_2,  // D34
  PH_3,  // D35
  PG_9,  // D36
  PC_0,  // D37
  // microSD,
  PC_8,  // D38
  PC_9,  // D39
  PC_10, // D40
  PC_11, // D41
  PC_12, // D42
  PD_2,  // D43
  PH_14, // D44
  // Audio,
  PI_4,  // D45
  PI_5,  // D46
  PI_7,  // D47
  PI_6,  // D48
  PG_10, // D49
  PI_11, // D50
  // I2C4,
  PB_8,  // D51
  PB_9,  // D52
  // Microphone,
  PD_6,  // D53
  PD_11, // D54
  PE_0,  // D55
  PE_1,  // D56
  PC_3,  // D57
  PE_4,  // D58
  // RMII,
  PG_11, // D59
  PG_13, // D60
  PG_12, // D61
  PC_4,  // D62
  PC_5,  // D63
  PI_10, // D64
  PA_7,  // D65
  PC_1,  // D66
  PA_2,  // D67
  PA_1,  // D68
  // TFT LCD,
  PD_14, // D69
  PD_15, // D70
  PD_0,  // D71
  PD_1,  // D72
  PE_7,  // D73
  PE_8,  // D74
  PE_9,  // D75
  PE_10, // D76
  PE_11, // D77
  PE_12, // D78
  PE_13, // D79
  PE_14, // D80
  PE_15, // D81
  PD_8,  // D82
  PD_9,  // D83
  PD_10, // D84
  PD_3,  // D85
  PD_4,  // D86
  PD_5,  // D87
  PC_7,  // D88
  PF_0,  // D89
  PH_13, // D90
  // Backlight driver,
  PI_3,  // D91
  // Touch panel connector,
  PG_3,  // D92
  PG_7,  // D93
  // LCD PWR enable,
  PC_6,  // D94
  // PMOD,
  PF_6,  // D95
  PF_9,  // D96
  PF_7,  // D97
  PF_8,  // D98
  PH_8,  // D99
  PH_7,  // D100
  PH_9,  // D101
  PH_6,  // D102
  PF_11, // D103/A7
  PH_12, // D104
  PF_3,  // D105
  PB_12, // D106
  PH_4,  // D107
  PH_5,  // D108
  // VCP,
  PA_9,  // D109
  PA_10, // D110
  // USB,
  PA_11, // D111
  PA_12, // D112
  PG_0,  // D113
  PF_13, // D114/A8
  PB_13, // D115
  PB_14, // D116
  PG_1,  // D117
  PF_14, // D118/A9
  // JTAG,
  PA_13, // D119
  PA_14, // D120
  PA_15, // D121
  PB_3,  // D122
  PB_4,  // D123
  PE_2,  // D124
  PE_3,  // D125
  PG_14, // D126
  PE_5,  // D127
  PE_6,  // D128
  // Clock,
  PH_0,  // D129
  PC_14, // D130
  PC_15  // D131
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16,  // A0,  PB0
  17,  // A1,  PA4
  18,  // A2,  PA0
  19,  // A3,  PA5
  20,  // A4,  PA6
  21,  // A5,  PF12
  10,  // A6,  PA3
  103, // A7,  PF11
  114, // A8,  PF13
  118  // A9,  PF14
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI
                                     | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_CSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIGITAL;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = RCC_CSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_SAI1
                                             | RCC_PERIPHCLK_SAI2 | RCC_PERIPHCLK_SDMMC1
                                             | RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_CSI;
  PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLL2_SOURCE_CSI;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 32;
  PeriphClkInitStruct.PLL2.PLL2P = 1;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2_VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVP;
  PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL2P;
  PeriphClkInitStruct.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLL2P;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLL1Q;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_STM32H573I_DK */
