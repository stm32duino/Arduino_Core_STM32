/*
 *******************************************************************************
 * Copyright (c) 2022, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_STEVAL_MKBOXPRO)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  // Sensor Bus
  PI_0,                     //D0 - MCU_SEL SPI/I2C mux switch digital
  PB_6,                     //D1 - I2C1_SCL --> SCL
  PB_7,                     //D2 - I2C1_SDA --> SDA
  PI_1,                     //D3 - SPI2_SCK --> SPI
  PI_2,                     //D4 - SPI2_MISO --> SPI
  PI_3,                     //D5 - SPI2_MOSI --> SPI
  PI_7,                     //D6 - SPI_Sen_CS_A
  PI_5,                     //D7 - SPI_Sen_CS_G
  PE_9,                     //D8 - MIC_ADF_CK
  PE_10,                    //D9 - MIC_ADF_SD
  // Sensor interrupt
  PE_6,                     //D10 - MAG_DRDY
  PB_15,                    //D11 - TEMP_INT
  PE_11,                    //D12 - HUM_DRDY
  PF_2,                     //D13 - ACC_INT2
  PF_15,                    //D14 - ACC_INT2
  PA_4,                     //D15 - IMU_INT1
  PD_11,                    //D16 - IMU_INT2
  PE_8,                     //D17 - PRESS_INT
  // MICs
  PE_4,                     //D18 - MDF1_SDI3
  PE_7,                     //D19 - MDF1_SDI2
  PB_12,                    //D20 - MDF1_SDI1
  PD_3,                     //D21 - MDF1_SDI0
  PF_10,                    //D22 - MDF1_CCK
  PA_10,                    //D23 - SAI_SD
  PE_2,                     //D24 - SAI_MCLK
  PA_3,                     //D25 - SAI_MCK
  PA_8,                     //D26 - SAI_SCK
  PA_9,                     //D27 - SAI_FS
  // SD_CARD
  PC_5,                     //D28 - SD_DETECT
  PC_6,                     //D29 - SD_DATA0dir
  PC_7,                     //D30 - SD_DATA123dir
  PC_8,                     //D31 - SD_DATA0
  PC_9,                     //D32 - SD_DATA1
  PC_10,                    //D33 - SD_DATA2
  PC_11,                    //D34 - SD_DATA3
  PC_12,                    //D35 - SD_CLK
  PD_2,                     //D36 - SD_CMD
  PB_8,                     //D37 - SD_CLK_f
  PB_9,                     //D38 - SD_CMDdir
  PH_8,                     //D39 - SEL_SD_V
  PH_10,                    //D40 - EN_SD
  // DIL24_DUT
  PC_0,                     //D41/A0 - LOCK_1v8
  PG_3,                     //D42 - DIL_GP
  PG_4,                     //D43 - DIL_DEN
  PG_10,                    //D44 - SPI_dut_MISO (SPI3)
  PB_5,                     //D45 - SPI_dut_MOSI (SPI3) - interconnected with PG8
  PG_9,                     //D46 - SPI_dut_CK (SPI3) - interconnected with PG7
  PG_1,                     //D47 - SPI_dut_CS
  PG_12,                    //D48 - SPI_dut_CS2
  PG_6,                     //D49 - DIL_INT2
  PG_2,                     //D50 - DIL_INT1
  PG_15,                    //D51 - DIL_INT4
  PG_0,                     //D52 - DIL_INT3
  PG_7,                     //D53 - I2C3_SCL - interconnected with PG9
  PG_8,                     //D54 - I2C3_SDA - interconnected with PB5
  // LED and buttons
  PF_6,                     //D55 - LED1 green
  PH_11,                    //D56 - LED2 red (BLE shared)
  PH_12,                    //D57 - LED3 yellow
  PF_9,                     //D58 - LED USB enum
  PC_13,                    //D59 - SW1 (BLE shared)
  PE_0,                     //D60 - SW2 interconnect with PH3
  PH_3,                     //D61 - SW2 (Boot0)
  PB_10,                    //D62 - CH_BAT_LED
  // JP4 connector
  PE_5,                     //D63 - GPIO_JP4
  // Speaker1
  PE_13,                    //D64
  // BT
  PB_1,                     //D65/A1 - GPIO_0_BT
  PB_11,                    //D66 - GPIO_1_BT
  PE_1,                     //D67 - V_BT_EN
  PD_1,                     //D68 - BT_BOOT
  PD_4,                     //D69 - BT_NRST
  PA_2,                     //D70 - BT_SPI_NSS (SPI1 RDY)
  PA_5,                     //D71 - BT_SPI_CLK (SPI1)
  PA_6,                     //D72 - BT_SPI_MISO (SPI1)
  PA_7,                     //D73 - BT_SPI_MOSI (SPI1)
  PD_5,                     //D74 - BT_USART_TX (USART2)
  PD_6,                     //D75 - BT_USART_RX (USART2)
  // NFC                             -
  PE_12,                    //D76 - NFC_GPIO
  PB_13,                    //D77 - I2C_SCL
  PB_14,                    //D78 - I2C_SDA
  // USB                             -
  PA_11,                    //D79 - USB DM
  PA_12,                    //D80 - USB DP
  PF_4,                     //D81 - PU USB DP (useless as internal PU available)
  // Power
  PB_0,                     //D82/A2 - Vbatt_sens/3
  PC_4,                     //D83/A3 - Vbatt_test
  PC_1,                     //D84/A4 - PW_BT
  PF_8,                     //D85 - SW_ON
  PF_0,                     //D86 - VusbP
  // LDFM LDO
  PI_6,                     //D87 - V4_GOOD
  PC_3,                     //D88 - V4_EN
  // Wireless CH
  PF_7,                     //D89 - WC_RSTB
  PE_3,                     //D90 - WC_INTB
  PD_12,                    //D91 - I2C4_SCL (also on Prog connector)
  PD_13,                    //D92 - I2C4_SDA (also on Prog connector)
  // Prog connector
  PA_0,                     //D93 - UART4_TX
  PA_1,                     //D94 - UART4_RX
  PA_13,                    //D95 - JTMS_SWDIO
  PA_14,                    //D96 - JTCL_SWCLK
  PA_15,                    //D97 - JTDI
  PB_3,                     //D98 - JTDO
  PB_4,                     //D99 - JTNRST
  // Oscillators
  PC_14,                    //D100 - OSC32_IN
  PC_15,                    //D101 - OSC32_OUT
  PH_0,                     //D102 - OSC_IN
  PH_1,                     //D103 - OSC_OUT
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  41,  // A0,  PC0
  65,  // A1,  PB1
  82,  // A2,  PB0
  83,  // A3,  PC4
  84   // A4,  PC1
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/** System Clock Configuration
*/
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the peripherals clock
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInit.IclkClockSelection = RCC_CLK48CLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_STEVAL_MKBOXPRO */
