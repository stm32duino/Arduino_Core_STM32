/*
 *******************************************************************************
 * Copyright (c) 2026, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_DISCO_F723IE)

#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
  PA_3,   // D0  - USART2_RX
  PA_2,   // D1  - USART2_TX
  PC_5,   // D2
  PE_5,   // D3  - TIM9_CH1
  PH_3,   // D4
  PB_0,   // D5  - TIM3_CH3
  PE_6,   // D6  - TIM9_CH2
  PE_3,   // D7
  PE_4,   // D8
  PH_6,   // D9  - TIM12_CH1
  PA_1,   // D10 - TIM2_CH2 / SPI1_NSS
  PB_5,   // D11 - TIM3_CH2 / SPI1_MOSI
  PB_4,   // D12 - SPI1_MISO
  PA_5,   // D13 - SPI1_SCK
  PH_5,   // D14 - I2C2_SDA
  PH_4,   // D15 - I2C2_SCL
  PA_6,   // A0
  PA_4,   // A1
  PC_4,   // A2
  PF_10,  // A3 - ADC3_IN8
  PC_0,   // A4
  PC_1,   // A5
  PA_0,   // User button
  PA_7,   // LED_RED
  PB_1,   // LED_GREEN
  PC_6,   // ST-LINK VCP TX
  PC_7,   // ST-LINK VCP RX
  PA_8,
  PA_9,
  PA_10,
  PA_11,
  PA_12,
  PA_13,
  PA_14,
  PA_15,
  PB_2,
  PB_3,
  PB_6,
  PB_7,
  PB_8,
  PB_9,
  PB_10,
  PB_11,
  PB_12,
  PB_13,
  PB_14,
  PB_15,
  PC_2,
  PC_3,
  PC_8,
  PC_9,
  PC_10,
  PC_11,
  PC_12,
  PC_13,
  PC_14,
  PC_15,
  PD_0,
  PD_1,
  PD_2,
  PD_3,
  PD_4,
  PD_5,
  PD_6,
  PD_7,
  PD_8,
  PD_9,
  PD_10,
  PD_11,
  PD_12,
  PD_13,
  PD_14,
  PD_15,
  PE_0,
  PE_1,
  PE_2,
  PE_7,
  PE_8,
  PE_9,
  PE_10,
  PE_11,
  PE_12,
  PE_13,
  PE_14,
  PE_15,
  PF_0,
  PF_1,
  PF_2,
  PF_3,
  PF_4,
  PF_5,
  PF_6,
  PF_7,
  PF_8,
  PF_9,
  PF_11,
  PF_12,
  PF_13,
  PF_14,
  PF_15,
  PG_0,
  PG_1,
  PG_2,
  PG_3,
  PG_4,
  PG_5,
  PG_8,
  PG_9,
  PG_10,
  PG_11,
  PG_12,
  PG_13,
  PG_14,
  PG_15,
  PH_0,
  PH_1,
  PH_2,
  PH_7,
  PH_8,
  PH_9,
  PH_10,
  PH_11,
  PH_12,
  PH_13,
  PH_14,
  PH_15,
  PI_0,
  PI_1,
  PI_2,
  PI_3,
  PI_4,
  PI_5,
  PI_6,
  PI_7,
  PI_8,
  PI_9,
  PI_10,
  PI_11
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  16, // A0
  17, // A1
  18, // A2
  19, // A3
  20, // A4
  21  // A5
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  Board-specific early init, called from main() before setup(),
  *         but after the core has already enabled the Cortex-M7 I/D-Cache
  *         (see premain() in cores/arduino/main.cpp).
  *
  *         The ARMv7-M *default* memory map treats 0x60000000-0x7FFFFFFF
  *         (all FMC NOR/SRAM bank windows - PSRAM on NE1 at 0x60000000, the
  *         on-board LCD on NE2 at 0x64000000) as cacheable "Normal/External
  *         RAM" unless an MPU region says otherwise. With the D-Cache
  *         enabled and no MPU region configured, writes to a memory-mapped
  *         peripheral register interface there (e.g. the LCD's
  *         command/index and data registers) can get absorbed into the
  *         cache instead of reaching the external bus: no crash, no hang,
  *         the external device just never receives a coherent byte stream.
  *         ST's own reference firmware for this board does the same thing
  *         for the same reason (see MPU_ConfigPSRAM() in the STM32CubeF7
  *         BSP example Applications/Display/LCD_PicturesFromUSB/Src/main.c).
  * @param  None
  * @retval None
  */
WEAK void initVariant(void)
{
  HAL_MPU_Disable();

  MPU_Region_InitTypeDef mpu = {0};
  mpu.Enable = MPU_REGION_ENABLE;
  mpu.BaseAddress = 0x64000000;      // FMC Bank2 (NE2, on-board LCD)
  mpu.Size = MPU_REGION_SIZE_64MB;   // whole NE2 decode window
  mpu.AccessPermission = MPU_REGION_FULL_ACCESS;
  mpu.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  mpu.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  mpu.IsShareable = MPU_ACCESS_SHAREABLE;
  mpu.Number = MPU_REGION_NUMBER0;
  mpu.TypeExtField = MPU_TEX_LEVEL0;
  mpu.SubRegionDisable = 0x00;
  mpu.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  HAL_MPU_ConfigRegion(&mpu);

  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows:
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the RCC Oscillators according to the specified parameters */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Activate the Over-Drive mode */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the peripherals clock (48 MHz for USB OTG FS/HS) */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_DISCO_F723IE */
