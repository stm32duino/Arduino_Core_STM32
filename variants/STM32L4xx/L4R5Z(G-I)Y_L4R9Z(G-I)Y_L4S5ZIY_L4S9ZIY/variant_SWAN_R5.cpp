/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_SWAN_R5)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PD_9,
  PD_8,
  PF_15,
  PE_13,
  PE_3,
  PE_11,
  PE_9,
  PF_13,
  PF_12,
  PD_15,
  PA_4,
  PA_7,
  PA_6,
  PA_5,
  PB_9,
  PE_1,
  PA_3,
  PA_1,
  PC_3,
  PC_1,
  PC_4,
  PC_5,
  PB_1,
  PC_2,
  PA_0,
  PA_10,
  PA_9,
  PG_12,
  PB_4,
  PD_6,
  PA_2,
  PD_4,
  PD_3,
  PB_10,
  PB_11,
  PD_2,
  PB_13,
  PG_8,
  PG_7,
  PB_7,
  PB_6,
  PF_0,
  PF_1,
  PC_9,
  PC_0,
  PD_0,
  PB_15,
  PB_14,
  PD_1,
  PD_5,
  PE_10,
  PC_11,
  PE_12,
  PB_0,
  PE_14,
  PE_15,
  PE_2,
  PC_13,
  PE_4,
  PA_11,
  PA_12,
  PC_6,
  PE_6,
  PG_0,
  PG_1,
  PG_2,
  PG_3,
  PB_2,
  PH_3,
  PB_3,
  PA_15,
  PA_14,
  PA_13,
  PC_14,
  PC_15
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  16, // A0,  PA3
  17, // A1,  PA1
  18, // A2,  PC3
  19, // A3,  PC1
  20, // A4,  PC4
  21, // A5,  PC5
  22, // A6,  PB1
  23, // A7,  PC2
  24, // A8,  PA0
  10, // A9,  PA4
  11, // A10, PA7
  12, // A11, PA6
  13, // A12, PA5
  30, // A13, PA2
  44, // A14, PC0
  53  // A15, PB0
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void initVariant(void)
{

  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Set the DISCHARGE pin and the USB_DETECT pin to FLOAT */
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); /* PE6 DISCHRG */
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); /* PC6 is USB_DETECT */

  /* Turn on the 3V3 regulator */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);

}

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK) {
    Error_Handler();
  }
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMLOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV5;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_SDMMC1
                                       | RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_OSPI;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
  PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_MSI;
  PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_MSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_SWAN_R5* */
