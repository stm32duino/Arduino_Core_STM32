#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
// Match Table 20. NUCLEO-H743ZI pin assignments
// from UM1974 STM32 Nucleo-144 board
const PinName digitalPin[] = {
  PG_9,  //D0 - USART_A_RX
  PG_14, //D1 - USART_A_TX
  PF_15, //D2
  PE_13, //D3 - TIMER_A_PWM3
  PF_14, //D4
  PE_11, //D5 - TIMER_A_PWM2
  PE_9,  //D6 - TIMER_A_PWM1
  PF_13, //D7
  PF_12, //D8
  PD_15, //D9  - TIMER_B_PWM2
  PD_14, //D10 - SPI_A_CS/ TIM_B_PWM3
  PA_7,  //D11 - SPI_A_MOSI/If JP6 ON used also for Ethernet PHY as RMII_DV
  PA_6,  //D12 - SPI_A_MISO
  PA_5,  //D13 - SPI_A_SCK
  PB_9,  //D14 - I2C_A_SDA
  PB_8,  //D15 - I2C_A_SCL
  PC_6,  //D16 - I2S_A_MCK
  PB_15, //D17 - I2S_A_SD
  PB_13, //D18 - I2S_A_CK/If JP7 ON used also for Ethernet PHY as RMII_TXD1
  PB_12, //D19 - I2S_A_WS
  PA_15, //D20 - I2S_B_WS
  PC_7,  //D21 - I2S_B_MCK
  PB_5,  //D22 - I2S_B_SD/SPI_B_MOSI
  PB_3,  //D23 - I2S_B_CK/SPI_B_SCK - SWO
  PA_4,  //D24 - SPI_B_NSS
  PB_4,  //D25 - SPI_B_MISO
  PB_6,  //D26 - QSPI_CS
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
  PE_14, //D38
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
  PE_2,  //D56 - SAI_A_MCLK/QSPI_BK1_IO2 - D31
  PE_4,  //D57 - SAI_A_FS
  PE_5,  //D58 - SAI_A_SCK
  PE_6,  //D59 - SAI_A_SD
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
  PA_7,  //D71 - D11
  NC,    //D72
  PB_7,  //D73 - LD2 LED_BLUE
  PB_14, //D74 - LD3 LED_RED
  PC_13, //D75 - USER_BTN
  PD_9,  //D76 - Serial Rx
  PD_8,  //D77 - Serial Tx
  PD_10, //D78
  PE_1,  //D79
  PG_4,  //D80
  PG_5,  //D81
  PG_8,  //D82
  PG_10, //D83
  PG_12, //D84
  PG_15, //D85
  PA_3,  //D86/A0
  PC_0,  //D87/A1
  PC_3,  //D88/A2
  PF_3,  //D89/A3
  PF_5,  //D90/A4
  PF_10, //D91/A5
  PB_1,  //D92/A6
  PC_2,  //D93/A7
  PF_4,  //D94/A8
  PF_6,  //D95/A9
  PF_11, //D96/A10
  // Duplicated pins in order to be aligned with PinMap_ADC
  PF_14, //D97/A11 = D4
  PF_13, //D98/A12 = D7
  PF_12, //D99/A13 = D8
  PA_7,  //D100/A14 = D11
  PA_6,  //D101/A15 = D12
  PA_5,  //D102/A16 = D13
  PA_4,  //D103/A17 = D24
  PA_0,  //D104/A18 = D32
  PF_8,  //D105/A19 = D61
  PF_7,  //D106/A20 = D62
  PF_9,  //D107/A21 = D63
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
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Supply configuration update enable */
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) {
  }

  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_CSI;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_CSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 129;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Configure the Systick interrupt time */
  HAL_SYSTICK_Config(SystemCoreClock/1000);

  /* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
