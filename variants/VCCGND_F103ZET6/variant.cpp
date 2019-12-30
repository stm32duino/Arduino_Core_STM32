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
  //PX_n, //Dx
  PE_0,   //D0
  PE_1,   //D1
  PE_2,   //D2
  PE_3,   //D3
  PE_4,   //D4
  PE_5,   //D5
  PE_6,   //D6
  PC_13,  //D7
  PC_14,  //D8 - LSE
  PC_15,  //D9 - LSE
  PF_0,   //D10
  PF_1,   //D11
  PF_2,   //D12
  PF_3,   //D13
  PF_4,   //D14
  PF_5,   //D15
  PF_6,   //D16
  PF_7,   //D17
  PF_8,   //D18
  PF_9,   //D19
  PF_10,  //D20
  PC_0,   //D21
  PC_1,   //D22
  PC_2,   //D23
  PC_3,   //D24
  PA_0,   //D25
  PA_1,   //D26
  PA_2,   //D27
  PA_3,   //D28
  PA_4,   //D29
  PA_5,   //D30 - SPI SCLK
  PA_6,   //D31 - SPI MISO
  PA_7,   //D32 - SPI MOSI
  PC_4,   //D33
  PC_5,   //D34
  PB_0,   //D35
  PB_1,   //D36
  PB_2,   //D37 - BOOT1
  PF_11,  //D38
  PF_12,  //D39
  PF_13,  //D40
  PF_14,  //D41
  PF_15,  //D42
  PG_0,   //D43
  PG_1,   //D44
  PE_7,   //D45
  PE_8,   //D46
  PE_9,   //D47
  PE_10,  //D48
  PE_11,  //D49
  PE_12,  //D50
  PE_13,  //D51
  PE_14,  //D52
  PE_15,  //D53
  PB_10,  //D54
  PB_11,  //D55
  PB_12,  //D56
  PB_13,  //D57
  PB_14,  //D58
  PB_15,  //D59
  PD_8,   //D60
  PD_9,   //D61
  PD_10,  //D62
  PD_11,  //D63
  PD_12,  //D64
  PD_13,  //D65
  PD_14,  //D66
  PD_15,  //D67
  PG_2,   //D68
  PG_3,   //D69
  PG_4,   //D70
  PG_5,   //D71
  PG_6,   //D72
  PG_7,   //D73
  PG_8,   //D74
  PC_6,   //D75
  PC_7,   //D76
  PC_8,   //D77
  PC_9,   //D78
  PA_8,   //D79
  PA_9,   //D80
  PA_10,  //D81
  PA_11,  //D82 - USB DM
  PA_12,  //D83 - USB DP
  PA_13,  //D84 - SWDI0
  PA_14,  //D85 - SWCLK
  PA_15,  //D86
  PC_10,  //D87
  PC_11,  //D88
  PC_12,  //D89
  PD_0,   //D90
  PD_1,   //D91
  PD_2,   //D92
  PD_3,   //D93
  PD_4,   //D94
  PD_5,   //D95
  PD_6,   //D96
  PD_7,	  //D97
  PG_9,   //D98
  PG_10,  //D99
  PG_11,  //D100
  PG_12,  //D101
  PG_13,  //D102
  PG_14,  //D103
  PG_15,  //D104 - LED_BUILTIN
  PB_3,   //D105
  PB_4,   //D106
  PB_5,   //D107
  PB_6,   //D108 - I2C SCL
  PB_7,   //D109 - I2C SDA
  PB_8,   //D110
  PB_9,   //D111
  // Required only if Ax pins are automaticaly defined using `NUM_ANALOG_FIRST`
  // and have to be contiguous in this array
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC_0,   //D112/A0 = D0
  PC_1,   //D123/A1 = D1
  PF_6,   //D114/A2 = D2
  PF_7,   //D115/A3 = D3
  PF_8,   //D116/A4 = D4
  PF_9,   //D117/A5 = D5
  PF_10   //D118/A6 = D6
  
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
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
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
  // Here copy the desired System Clock Configuration
  // It could be generated thanks STM32CubeMX after code generation for Toolchain/IDE: 'SW4STM32',
  // available in src/main.c
  // or
  // copied from a STM32CubeYY project examples
  // where 'YY' could be F0, F1, F2, F3, F4, F7, G0, G4, H7, L0, L1, L4, MP1, WB
  
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
