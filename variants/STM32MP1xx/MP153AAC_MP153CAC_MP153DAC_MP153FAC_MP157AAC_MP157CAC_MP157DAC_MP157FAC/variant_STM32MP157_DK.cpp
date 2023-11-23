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
#if defined(ARDUINO_STM32MP157A_DK1) || defined(ARDUINO_STM32MP157C_DK2)
#include "pins_arduino.h"

// Pin number
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  //PX_n, //Dx
  // CN14 Right Top Arduino Pins
  PE_7,  //D0  - USART7_RX
  PE_8,  //D1  - USART7_TX and TIM1_CH1N
  PE_1,  //D2
  PD_14, //D3  - TIM4_CH3
  PE_10, //D4  - TIM1_CH2N
  PD_15, //D5  - TIM4_CH4
  PE_9,  //D6  - TIM1_CH1
  PD_1,  //D7
  // CN13 Right Bottom Arduino Pins
  PG_3,  //D8
  PH_6,  //D9  - TIM12_CH1
  PE_11, //D10 - SPI4_NSS and TIM1_CH2
  PE_14, //D11 - SPI4_MOSI and TIM1_CH4
  PE_13, //D12 - SPI4_MISO and TIM1_CH3
  PE_12, //D13 - SPI4_SCK and TIM1_CH3N
  PA_12, //D14 - I2C5_SDA
  PA_11, //D15 - I2C5_SCL
  // // CN2 Raspberry Pi GPIO connectors
  // // NC,      // RPI_1 - 3V3
  // // NC,      // RPI_2 - 5V
  // PA_12, //D16 - RPI_3 - GPIO2 / I2C5_SDA
  // // NC,      // PRI_4 - 5V
  // PA_11, //D17 - RPI_5 - GPIO3 / I2C5_SCL
  // // NC,      // RPI_6 - GND
  // PA_8,  //D18 - RPI_7 - GPIO4 / MCO1
  // PB_10, //D19 - RPI_8 - GPIO14 / USART3_TX
  // // NC,      // RPI_9 - GND
  // PB_12, //D20 - RPI_10 - GPIO15 / USART3_RX
  // PG_8,  //D21 - RPI_11 - GPIO17 / USART3_RTS
  // PI_5,  //D22 - RPI_12 - GPIO18 / SAI2_SCKA
  // PD_7,  //D23 - RPI_13 - GPIO27 / SDMMC3_D3
  // // NC,      // RPI_14 - GND
  // PG_15, //D24 - RPI_15 - GPIO22 / SDMMC3_CK
  // PF_1,  //D25 - RPI_16 - GPIO23 / SDMMC3_CMD
  // // NC,      // RPI_17 - 3V3
  // PF_0,  //D26 - RPI_18 - GPIO24 / SDMMC3_D0
  // PF_9,  //D27 - RPI_19 - GPIO10 / SPI5_MOSI
  // // NC,      // RPI_20 - GND
  // PF_8,  //D28 - RPI_21 - GPIO9 / SPI5_MISO
  // PF_4,  //D29 - RPI_22 - GPIO25 / SDMMC3_D1
  // PF_7,  //D30 - RPI_23 - GPIO11 / SPI5_SCK
  // PF_6,  //D31 - RPI_24 - GPIO8 / SPI5_NSS
  // // NC,      // RPI_25 - GND
  // PF_3,  //D32 - RPI_26 - GPIO7
  // PF_15, //D33 - RPI_27 - I2C1_SDA
  // PD_12, //D34 - RPI_28 - I2C1_SCL
  // PG_2,  //D35 - RPI_29 - GPIO5 / MCO2
  // // NC,      // RPI_30 - GND
  // PH_11, //D36 - RPI_31 - GPIO6 / TIM5_CH2
  // PD_13, //D37 - RPI_32 - GPIO12 / TIM4_CH2
  // PC_7,  //D38 - RPI_33 - GPIO13 /TIM3_CH2
  // // NC,      // RPI_34 - GND
  // PI_7,  //D39 - RPI_35 - GPIO19 / SAI2_FSA
  // PB_13, //D40 - RPI_36 - GPIO16 / USART3_CTS
  // PF_5,  //D41 - RPI_37 - GPIO26 / SDMMC3_D2
  // PI_6,  //D42 - RPI_38 - GPIO20 / SAI2_SDA
  // // NC,      // RPI_39 - GND
  // PF_11, //D43 - RPI_40 - GPIO21 / SAI2_SDB
  // Built-In LEDs
  PA_14, //D16, D44 - LED LD5, Green, Active Low, Connected to B3 (USER1 Button)
  PA_13, //D17, D45 - LED LD6, Red, Active Low, Connected to B4 (USER2 Button)
  PH_7,  //D18, D46 - LED LD7, Orange, Active High
  // NC,    // PD_11, LED LD8, Blue, but Used in Linux heartbeat signal. Active High
  // CN17 Left Arduino Analog Pins
  PF_14, //A0 - D19, D47 - ADC2_INP6
  PF_13, //A1 - D20, D48 - ADC2_INP2
  ANA_0, //A2 - D21, D49 - ADC1_INP0
  ANA_1, //A3 - D22, D50 - ADC1_INP1
  PC_3,  //A4 - D23, D51 - ADC1_INP13, or PA_12 (D14) with SB23 ON / SB24 OFF
  PF_12  //A5 - D24, D52 - ADC1_INP6, or PA_11 (D15) with SB25 ON / SB26 OFF
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  19, // A0
  20, // A1
  21, // A2
  22, // A3
  23, // A4
  24  // A5
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
void SystemClock_Config(void)
{
  /**
   * NOTE: Because of the limitation of STM32MP1xx, unlike other MCUs this is
   * NOT a WEAK function, preventing being overridden.
   * In STM32MP1 series, SystemClock_Config()) is "done" by running the FSBL
   * (First Stage Boot Loader) on Cortex-A. This function call shall NOT be
   * executed in production mode. SystemClock_Config() shall be under
   * if(IS_ENGINEERING_BOOT_MODE()).
   *
   * NOTE:
   *  * Production mode: Both CA7 and CM4 core running, BOOT0 and BOOT2 are ON.
   *  * Engineering mode: Only CM4 running, BOOT0 = OFF, BOOT2 = ON.
   * See:
   *  https://wiki.st.com/stm32mpu/wiki/How_to_use_engineering_and_production_modes
   */
  if (!IS_ENGINEERING_BOOT_MODE()) {
    return;
  }

  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /**Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE
                                     | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSIDivValue = RCC_HSI_DIV1;

  /**PLL1 Config
  */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 81;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 1;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLFRACV = 0x800;
  RCC_OscInitStruct.PLL.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

  /**PLL2 Config
  */
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL2.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStruct.PLL2.PLLM = 3;
  RCC_OscInitStruct.PLL2.PLLN = 66;
  RCC_OscInitStruct.PLL2.PLLP = 2;
  RCC_OscInitStruct.PLL2.PLLQ = 1;
  RCC_OscInitStruct.PLL2.PLLR = 1;
  RCC_OscInitStruct.PLL2.PLLFRACV = 0x1400;
  RCC_OscInitStruct.PLL2.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL2.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL2.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

  /**PLL3 Config
  */
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLL3SOURCE_HSE;
  RCC_OscInitStruct.PLL3.PLLM = 2;
  RCC_OscInitStruct.PLL3.PLLN = 34;
  RCC_OscInitStruct.PLL3.PLLP = 2;
  RCC_OscInitStruct.PLL3.PLLQ = 17;
  RCC_OscInitStruct.PLL3.PLLR = 37;
  RCC_OscInitStruct.PLL3.PLLRGE = RCC_PLL3IFRANGE_1;
  RCC_OscInitStruct.PLL3.PLLFRACV = 0x1A04;
  RCC_OscInitStruct.PLL3.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL3.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL3.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

  /**PLL4 Config
  */
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL4.PLLSource = RCC_PLL4SOURCE_HSE;
  RCC_OscInitStruct.PLL4.PLLM = 4;
  RCC_OscInitStruct.PLL4.PLLN = 99;
  RCC_OscInitStruct.PLL4.PLLP = 6;
  RCC_OscInitStruct.PLL4.PLLQ = 8;
  RCC_OscInitStruct.PLL4.PLLR = 8;
  RCC_OscInitStruct.PLL4.PLLRGE = RCC_PLL4IFRANGE_0;
  RCC_OscInitStruct.PLL4.PLLFRACV = 0;
  RCC_OscInitStruct.PLL4.PLLMODE = RCC_PLL_INTEGER;
  RCC_OscInitStruct.PLL4.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL4.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    /* Initialization Error */
    while (1);
  }
  /**RCC Clock Config
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_ACLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_PCLK3 | RCC_CLOCKTYPE_PCLK4
                                | RCC_CLOCKTYPE_PCLK5 | RCC_CLOCKTYPE_MPU;
  RCC_ClkInitStruct.MPUInit.MPU_Clock = RCC_MPUSOURCE_PLL1;
  RCC_ClkInitStruct.MPUInit.MPU_Div = RCC_MPU_DIV2;
  RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_PLL2;
  RCC_ClkInitStruct.AXISSInit.AXI_Div = RCC_AXI_DIV1;
  RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_PLL3;
  RCC_ClkInitStruct.MCUInit.MCU_Div = RCC_MCU_DIV1;
  RCC_ClkInitStruct.APB4_Div = RCC_APB4_DIV2;
  RCC_ClkInitStruct.APB5_Div = RCC_APB5_DIV4;
  RCC_ClkInitStruct.APB1_Div = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2_Div = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB3_Div = RCC_APB3_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK) {
    /* Initialization Error */
    while (1);
  }

  /**Set the HSE division factor for RTC clock
  */
  __HAL_RCC_RTC_HSEDIV(24);

  /* Configure ADCx clock prescaler */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PER;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }

  /* Configure VREFBUF */
  __HAL_RCC_VREF_CLK_ENABLE();
  HAL_SYSCFG_VREFBUF_HighImpedanceConfig(SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE);
  HAL_SYSCFG_EnableVREFBUF();

}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_STM32MP157* */
