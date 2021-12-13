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

#if defined(ARDUINO_WeActMiniH743VITX) || defined(ARDUINO_WeActMiniH750VBTX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PE_1,   // D0
  PE_0,   // D1
  PB_9,   // D2
  PB_8,   // D3
  PB_7,   // D4
  PB_6,   // D5
  PB_5,   // D6
  PB_4,   // D7
  PB_3,   // D8
  PD_7,   // D9
  PD_6,   // D10
  PD_5,   // D11
  PD_4,   // D12
  PD_3,   // D13
  PD_2,   // D14
  PD_1,   // D15
  PD_0,   // D16
  PC_12,  // D17
  PC_11,  // D18
  PC_10,  // D19
  PA_15,  // D20
  PA_12,  // D21
  PA_11,  // D22
  PA_10,  // D23
  PA_9,   // D24
  PA_8,   // D25
  PC_9,   // D26
  PC_8,   // D27
  PC_7,   // D28
  PC_6,   // D29
  PD_15,  // D30
  PD_14,  // D31
  PD_13,  // D32
  PD_12,  // D33
  PD_11,  // D34
  PD_10,  // D35
  PD_9,   // D36
  PD_8,   // D37
  PB_15,  // D38
  PB_14,  // D39
  PB_13,  // D40
  PB_12,  // D41
  PE_2,   // D42
  PE_3,   // D43
  PE_4,   // D44
  PE_5,   // D45
  PE_6,   // D46
  PC_13,  // D47
  PC_0,   // D48/A0
  PC_1,   // D49/A1
  PC_2_C, // D50/A2
  PC_3_C, // D51/A3
  PA_0,   // D52/A4
  PA_1,   // D53/A5
  PA_2,   // D54/A6
  PA_3,   // D55/A7
  PA_4,   // D56/A8
  PA_5,   // D57/A9
  PA_6,   // D58/A10
  PA_7,   // D59/A11
  PC_4,   // D60/A12
  PC_5,   // D61/A13
  PB_0,   // D62/A14
  PB_1,   // D63/A15
  PB_2,   // D64
  PE_7,   // D65
  PE_8,   // D66
  PE_9,   // D67
  PE_10,  // D68
  PE_11,  // D69
  PE_12,  // D70
  PE_13,  // D71
  PE_14,  // D72
  PE_15,  // D73
  PB_10,  // D74
  PB_11,  // D75
  PA_13,  // D76
  PA_14,  // D77
  PC_14,  // D78
  PC_15,  // D79
  PH_0,   // D80
  PH_1    // D81
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  48, // A0,  PC0
  49, // A1,  PC1
  50, // A2,  PC2_C
  51, // A3,  PC3_C
  52, // A4,  PA0
  53, // A5,  PA1
  54, // A6,  PA2
  55, // A7,  PA3
  56, // A8,  PA4
  57, // A9,  PA5
  58, // A10, PA6
  59, // A11, PA7
  60, // A12, PC4
  61, // A13, PC5
  62, // A14, PB0
  63  // A15, PB1
};

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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
   *  Run mode (VOS0 to VOS3)
   *  Scale 0: boosted performance (available only with LDO regulator)
   *  Scale 1: high performance
   *  Scale 2: medium performance and consumption
   *  Scale 3: optimized performance and low-power consumption
   *
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  /* PLL1 pclk is sysclk 480 Mhz */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  // 480 Mhz
  RCC_OscInitStruct.PLL.PLLM = 5; // M div 5
  RCC_OscInitStruct.PLL.PLLN = 96; // N mul 96
  RCC_OscInitStruct.PLL.PLLP = 1; // P div 1
  RCC_OscInitStruct.PLL.PLLQ = 10; // Q div 10 - USB 48 Mhz
  RCC_OscInitStruct.PLL.PLLR = 10; // R unused
  // 360 Mhz
  /*
  RCC_OscInitStruct.PLL.PLLM = 5; // M div 10
  RCC_OscInitStruct.PLL.PLLN = 144; // N mul 144 (add 1 to N)
  RCC_OscInitStruct.PLL.PLLP = 2; // P div 2 (add 1 to PLLP) must be even
  RCC_OscInitStruct.PLL.PLLQ = 15; // Q div 10 (add 1 to PLLQ) - USB 48 Mhz
  RCC_OscInitStruct.PLL.PLLR = 15; // R unused
  */

  /*
   * RCC_PLL1VCIRANGE_0  Clock range frequency between 1 and 2 MHz
   * RCC_PLL1VCIRANGE_1  Clock range frequency between 2 and 4 MHz
   * RCC_PLL1VCIRANGE_2  Clock range frequency between 4 and 8 MHz
   * RCC_PLL1VCIRANGE_3  Clock range frequency between 8 and 16 MHz */
  /* PLLRGE: RCC_PLL1VCIRANGE_2 Clock range frequency between 4 and 8 MHz  */
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  /* VCOSEL PLL1VCOWIDE 2-16 Mhz */
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_QSPI
                                             | RCC_PERIPHCLK_SDMMC | RCC_PERIPHCLK_ADC
                                             | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_USART16
                                             | RCC_PERIPHCLK_USART234578 | RCC_PERIPHCLK_I2C123
                                             | RCC_PERIPHCLK_I2C4 | RCC_PERIPHCLK_SPI123
                                             | RCC_PERIPHCLK_SPI45 | RCC_PERIPHCLK_SPI6;

  /* PLL1 qclk used for USB 48 Mhz */
  /* PLL1 qclk also used for FMC, QUADSPI, SDMMC, RNG, SAI */
  /* PLL2 pclk is needed for adc max 80 Mhz (p,q,r same) */
  /* PLL2 pclk also used for LP timers 2,3,4,5, SPI 1,2,3 */
  /* PLL2 qclk is needed for uart, can, spi4,5,6 80 Mhz */
  /* PLL3 r clk is needed for i2c 80 Mhz (p,q,r same) */
  PeriphClkInitStruct.PLL2.PLL2M = 15; // M DIV 15 vco 25 / 15 ~ 1.667 Mhz
  PeriphClkInitStruct.PLL2.PLL2N = 96; // N MUL 96
  PeriphClkInitStruct.PLL2.PLL2P = 2;  // P div 2
  PeriphClkInitStruct.PLL2.PLL2Q = 2;  // Q div 2
  PeriphClkInitStruct.PLL2.PLL2R = 2;  // R div 2
  // RCC_PLL1VCIRANGE_0  Clock range frequency between 1 and 2 MHz
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_0;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.PLL3.PLL3M = 15; // M DIV 15 vco 25 / 15 ~ 1.667 Mhz
  PeriphClkInitStruct.PLL3.PLL3N = 96; // N MUL 96
  PeriphClkInitStruct.PLL3.PLL3P = 2;  // P div 2
  PeriphClkInitStruct.PLL3.PLL3Q = 2;  // Q div 2
  PeriphClkInitStruct.PLL3.PLL3R = 2;  // R div 2
  // RCC_PLL1VCIRANGE_0  Clock range frequency between 1 and 2 MHz
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_0;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOMEDIUM;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  // ADC from PLL2 pclk
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  // USB from PLL1 qclk
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  // QSPI from PLL1 qclk
  PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_PLL;
  // SDMMC from PLL1 qclk
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
  // LPUART from PLL2 qclk
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PLL2;
  // USART from PLL2 qclk
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_PLL2;
  // USART from PLL2 qclk
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_PLL2;
  // I2C123 from PLL3 rclk
  PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_PLL3;
  // I2C4 from PLL3 rclk
  PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PLL3;
  // SPI123 from PLL2 pclk
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL2;
  // SPI45 from PLL2 qclk
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_PLL2;
  // SPI6 from PLL2 qclk
  PeriphClkInitStruct.Spi6ClockSelection = RCC_SPI6CLKSOURCE_PLL2;


  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}

/*
 * Power saving mode, mcu runs significantly cooler
 * Sysclock 240 Mhz, bus clocks 120 Mhz
 */
void SysClkHalfSpeed()
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { };
  /** Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1
                                | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  } else {
    SystemCoreClockUpdate();
  }
}

/*
 * Full speed - sysclk from PLL1 P - 480 Mhz
 * Sysclock 480 Mhz, bus clocks 240 Mhz
 */
void SysClkFullSpeed()
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { };
  /** Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1
                                | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  } else {
    SystemCoreClockUpdate();
  }
}

#endif /* ARDUINO_WeActMiniH743VITX || ARDUINO_WeActMiniH750VBTX */
