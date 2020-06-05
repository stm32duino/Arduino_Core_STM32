#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
#ifdef ARDUINO_NUCLEO_H743ZI2
  PB_7,  //D0 - USART_A_RX
  PB_6,  //D1 - USART_A_TX
  PG_14, //D2
#else
  PG_9,  //D0 - USART_A_RX
  PG_14, //D1 - USART_A_TX
  PF_15, //D2
#endif
  PE_13, //D3 - TIMER_A_PWM3
#ifdef ARDUINO_NUCLEO_H743ZI2
  PE_14, //D4
#else
  PF_14, //D4
#endif
  PE_11, //D5 - TIMER_A_PWM2
  PE_9,  //D6 - TIMER_A_PWM1
#ifdef ARDUINO_NUCLEO_H743ZI2
  PG_12, //D7
  PF_3,  //D8
#else
  PF_13, //D7
  PF_12, //D8
#endif
  PD_15, //D9 - TIMER_B_PWM2
  PD_14, //D10 - SPI_A_CS/ TIM_B_PWM3
#ifdef ARDUINO_NUCLEO_H743ZI2
  PB_5,  //D11 - SPI_A_MOSI/PA7 if SB33 ON and SB35 OFF
#else
  PA_7,  //D11 - SPI_A_MOSI/Used by ETH when JP6 ON
#endif
  PA_6,  //D12 - SPI_A_MISO
  PA_5,  //D13 - SPI_A_SCK
  PB_9,  //D14 - I2C_A_SDA
  PB_8,  //D15 - I2C_A_SCL
  PC_6,  //D16 - I2S_A_MCK
  PB_15, //D17 - I2S_A_SD
  PB_13, //D18 - I2S_A_CK/Used by ETH when JP7(ZI)/JP6(ZI2) ON
  PB_12, //D19 - I2S_A_WS
  PA_15, //D20 - I2S_B_WS
  PC_7,  //D21 - I2S_B_MCK
#ifdef ARDUINO_NUCLEO_H743ZI2
  PB_5,  //D22
#else
  PB_5,  //D22 - I2S_B_SD/SPI_B_MOSI
#endif
  PB_3,  //D23 - I2S_B_CK/SPI_B_SCK - SWO
  PA_4,  //D24 - SPI_B_NSS
  PB_4,  //D25 - SPI_B_MISO
#ifdef ARDUINO_NUCLEO_H743ZI2
  PG_6,  //D26 - QSPI_CS
#else
  PB_6,  //D26 - QSPI_CS
#endif
  PB_2,  //D27 - QSPI_CLK
  PD_13, //D28 - QSPI_BK1_IO3
  PD_12, //D29 - QSPI_BK1_IO1
  PD_11, //D30 - QSPI_BK1_IO0
  PE_2,  //D31 - SAI_A_MCLK/QSPI_BK1_IO2
  PA_0,  //D32 - TIMER_C_PWM1
  PB_0,  //D33 - TIMER_D_PWM1 - LD1 LED_GREEN
  PE_0,  //D34 - TIMER_B_ETR
  PB_11, //D35 - TIMER_C_PWM3
  PB_10, //D36 - TIMER_C_PWM2
  PE_15, //D37 - TIMER_A_BKIN1
#ifdef ARDUINO_NUCLEO_H743ZI2
  PE_6,  //D38
#else
  PE_14, //D38
#endif
  PE_12, //D39 - TIMER_A_PWM3N
  PE_10, //D40 - TIMER_A_PWM2N
  PE_7,  //D41 - TIMER_A_ETR
  PE_8,  //D42 - TIMER_A_PWM1N
  PC_8,  //D43 - SDMMC1_D0
  PC_9,  //D44 - SDMMC1_D1/I2S_A_CKIN
  PC_10, //D45 - SDMMC1_D2
  PC_11, //D46 - SDMMC1_D3
  PC_12, //D47 - SDMMC1_CK
  PD_2,  //D48 - SDMMC1_CMD
  PG_2,  //D49
  PG_3,  //D50
  PD_7,  //D51 - USART_B_SCLK
  PD_6,  //D52 - USART_B_RX
  PD_5,  //D53 - USART_B_TX
  PD_4,  //D54 - USART_B_RTS
  PD_3,  //D55 - USART_B_CTS
  PE_2,  //D56
  PE_4,  //D57 - SAI_A_FS
  PE_5,  //D58 - SAI_A_SCK
#ifdef ARDUINO_NUCLEO_H743ZI2
  PE_6,  //D59
#else
  PE_6,  //D59 - SAI_A_SD
#endif
  PE_3,  //D60 - SAI_B_SD
  PF_8,  //D61 - SAI_B_SCK
  PF_7,  //D62 - SAI_B_MCLK
  PF_9,  //D63 - SAI_B_FS
  PG_1,  //D64
  PG_0,  //D65
  PD_1,  //D66 - CAN_TX
  PD_0,  //D67 - CAN_RX
  PF_0,  //D68 - I2C_B_SDA
  PF_1,  //D69 - I2C_B_SCL
  PF_2,  //D70 - I2C_B_SMBA
#ifdef ARDUINO_NUCLEO_H743ZI2
  PE_9,  //D71
  PB_2,  //D72
  PE_1,  //D73 - LD2 LED_BLUE
#else
  PA_7,  //D71
  NC,    //D72
  PB_7,  //D73 - LD2 LED_BLUE
#endif
  PB_14, //D74 - LD3 LED_RED
  PC_13, //D75 - USER_BTN
  PD_9,  //D76 - Serial Rx
  PD_8,  //D77 - Serial Tx
  PA_3,  //D78 - A0
  PC_0,  //D79 - A1
  PC_3,  //D80 - A2
#ifdef ARDUINO_NUCLEO_H743ZI2
  PB_1,  //D81 - A3
  PC_2,  //D82 - A4
#else
  PF_3,  //D81 - A3
  PF_5,  //D82 - A4
#endif
  PF_10, //D83 - A5
#ifdef ARDUINO_NUCLEO_H743ZI2
  PF_4,  //D84 - A6
  PF_5,  //D85 - A7
  PF_6,  //D86 - A8
#else
  PB_1,  //D84 - A6
  PC_2,  //D85 - A7
  PF_4,  //D86 - A8
#endif
  PF_11, //D87 - A9
  PD_10, //D88
  PG_4,  //D89
  PG_5,  //D90
  PG_8,  //D91
  PG_10, //D92
  PG_15, //D93
#ifdef ARDUINO_NUCLEO_H743ZI2
  PA_7,  //D94 - SPI_A_MOSI/Used by ETH when SB31 ON
  PF_12, //D95
  PF_13, //D96
  PF_14, //D97
  PF_15, //D98
  PG_9,  //D99
#else
  PE_1,  //D94
  PF_6,  //D95
  PG_6,  //D96
  PG_12  //D97
#endif
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  /* Supply configuration update enable */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 20;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 120;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Enable USB Voltage detector */
  HAL_PWREx_EnableUSBVoltageDetector();
}

#ifdef __cplusplus
}
#endif
