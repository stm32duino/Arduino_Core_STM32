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

// Pin number
// Match Table 11. NUCLEO-L4R5ZI, NUCLEO-L4R5ZI-P pin assignments
// from UM2179 STM32 Nucleo-144 board
const PinName digitalPin[] = {
  PE_13, // SPI1_CLK
  PE_14, // SPI1_MISO
  PE_15, // SPI1_MOSI

  /* LSM6DSOX (3D ACC+GYR) */
  PA_2,  // INT1_INEMO
  PE_3,  // INT2_INEMO
  PE_12, // CS_INEMO

  /* LIS3DHH (ACCELEROMETER) */
  PE_10, // CS_ACC2
  PC_13, // ACC2_INT1
  PE_6,  // ACC2_INT2

  /* LIS2DW12 (ACCELEROMETER) */
  PE_11, // CS_ACC
  PC_5,  // ACC_INT1
  PD_14, // ACC_INT2

  /* SPI2: BLE */
  PC_3,  // SPI2_MOSI
  PD_1,  // SPI2_SCK
  PD_3,  // SPI2_MISO
  PD_0,  // SPI2_CS

  /* USART2: BLE */
  PD_5,  // USART2_BLE-RX_uC-TX
  PD_6,  // USART2_BLE-TX_uC-RX

  /* SPBTLE-1S (BLE) */
  PA_8,  // NRST_BLE
  PD_4,  // BLE_INT

  /* SPI3: MAGNETOMETER */
  PB_3,  // SPI3_CLK
  PB_4,  // SPI3_MISO
  PB_5,  // SPI3_MOSI

  /* LIS2MDLTR (MAGNETOMETER) */
  PA_15, // CS_MAG
  PD_12, // INT_MAG

  /* I2C1: LPS22HH + NU */
  PB_6,  // I2C1_SCL
  PB_7,  // I2C1_SDA

  /* LPS22HH (PRESSURE) */
  PD_15, // INT_PRESS

  /* HTS221 (HUM + TEMP) */
  PD_13, // INT_HTS

  /* I2C3: STTS751-0DP3F */
  PG_7,  // I2C3_SCL
  PG_8,  // I2C3_SDA

  /* STTS751-0DP3F (TEMPERATURE) */
  PG_5,  // INT_STT
  PG_6,  // EVENT_STT
  PE_1,  // INT_STT

  /* STBB3JR (BUCK-BOOST) */
  PE_4,  // SD_EN
  PF_0,  // BB_MODE

  /* STBC02AJR (CHG+PP+LDO) */
  PG_4,  // SW_SEL
  PG_2,  // BTN_PWR
  PG_3,  // CHG_LED
  PG_10, // CHG_LED2
  PC_4,  // AN_VBAT (A0)

  /* MP23ABS1TR (MIC) */
  /* TS922EIJT (OPAMP) */
  PA_3,  // M1P (A1)
  PB_0,  // MREF (A2)
  PA_4,  // DAC_OUT1

  /* LDK130PU-R */
  PF_7,  // 2V7_EN

  /* ST6G3244MEBJR (SD) */
  PB_12, // SD_DETECT
  PE_5,  // SD_SEL
  PB_8,  // SDMMC1_CLK_F
  PB_9,  // SDMMC1_CMDDIR
  PC_6,  // SDMMC1_DAT0DIR
  PC_7,  // SDMMC1_DAT123DIR
  PC_8,  // SDMMC1_D0
  PC_9,  // SDMMC1_D1
  PC_10, // SDMMC1_D2
  PC_11, // SDMMC1_D3
  PC_12, // SDMMC1_CK
  PD_2,  // SDMMC1_CMD

  /* Other*/
  PG_1,  // USER_PB1
  PH_3,  // BOOT0
  PB_15, // CPU_LED
  PF_2   // CPU_LED2
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /* Configure the main internal regulator output voltage */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV5;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_DFSDM1 | RCC_PERIPHCLK_USB
                                       | RCC_PERIPHCLK_SDMMC1;
  PeriphClkInit.Dfsdm1ClockSelection = RCC_DFSDM1CLKSOURCE_PCLK;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLP;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
