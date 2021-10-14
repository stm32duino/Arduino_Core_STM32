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
#if defined(ARDUINO_MALYANM200_F070CB) || defined(ARDUINO_MALYANM300_F070CB)

#include "pins_arduino.h"
#include <wiring.h>

/**Firmware starts at address different than 0*/
/* figure out how to derive this from the LD script */
#define FW_START_ADDR 0x08002000

/**Force VectorTable to specific memory position defined in linker*/
volatile uint32_t ram_vector_table[48] __attribute__((section(".RAMVectorTable")));

// Pin number
const PinName digitalPin[] = {
  /* USB connector on the top, MCU side */
  /* Left Side */
  PB_9,
  PB_8,
  PB_7,
  PB_6,
  PB_5,
  PB_4,
  PB_3,
  PA_15,
  PA_12,
  PA_11,
  PA_10,
  PA_9,
  PA_8,
  PB_15,
  PB_14,
  PB_13,
  PB_12,
  /* Right side */
  PC_13,
  PC_14,
  PC_15,
  PA_0,
  PA_1,
  PA_2,
  PA_3,
  PA_4,
  PA_5,
  PA_6,
  PA_7,
  PB_0,
  PB_1,
  PB_10,
  PB_11,
  PB_2,
  PA_13,
  PA_14,
  PF_0,
  PF_1
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
  * Initialize the variant. Note that this runs After
  * the lib initializers - if they use an interrupt, they'll fail.
  * Consider moving this to a call before the premains.
  */
void initVariant()
{
  for (int i = 0; i < 48; i++) {
    ram_vector_table[i] = *(volatile uint32_t *)(FW_START_ADDR + (i << 2));
  }

  __HAL_SYSCFG_REMAPMEMORY_SRAM();
}

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
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI14
                                     | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_USART1
                                       | RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_MALYANMx00_F070CB */
