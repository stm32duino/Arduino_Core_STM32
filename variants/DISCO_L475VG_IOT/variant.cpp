/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number based on UM2153
const PinName digitalPin[] = {
// CN3 connector
  PA_1,  //D0 - UART4_RX
  PA_0,  //D1 - UART4_TX
  PD_14, //D2
  PB_0,  //D3 - PWM
  PA_3,  //D4
  PB_4,  //D5 - PWM
  PB_1,  //D6 - PWM
  PA_4,  //D7
// CN1 connector
  PB_2,  //D8
  PA_15, //D9 - PWM
  PA_2,  //D10 - SPI_SSN/PWM
  PA_7,  //D11 - SPI1_MOSI/PWM
  PA_6,  //D12 - SPI1_MISO
  PA_5,  //D13 - SPI1_SCK/LED1
  PB_9,  //D14 - I2C1_SDA
  PB_8,  //D15 - I2C1_SCL
// Not on connector
  PB_14, //D16 - LED2
  PC_13, //D17 - USER_BTN
// ST-LINK
  PB_6,  //D18 - ST-LINK-UART1_TX
  PB_7,  //D19 - ST-LINK-UART1_RX
// CN9 USB OTG FS connector
  PA_9,  //D20 - USB_OTG_FS_VBUS
  PA_10, //D21 - USB_OTG_FS_ID
  PA_11, //D22 - USB_OTG_FS_DM
  PA_12, //D23 - USB_OTG_FS_DP
  PD_12, //D24 - USB_OTG_FS_PWR_EN
  PE_3,  //D25 - USB_OTG_OVRCR_EXTI3
// CN10 PMOD connector
  PD_0,  //D26 - PMOD-RESET
  PD_1,  //D27 - PMOD-SPI2_SCK
  PD_2,  //D28 - PMOD-IRQ_EXTI2
  PD_3,  //D29 - PMOD-UART2_CTS/SPI2_MISO
  PD_4,  //D30 - PMOD-UART2_RTS/SPI2_MOSI
  PD_5,  //D31 - PMOD-UART2_TX/SPI2_CSN
  PD_6,  //D32 - PMOD-UART2_RX
// Sensors / modules pins
  PA_8,  //D33 - SPBTLE-RF-RST
  PB_5,  //D34 - SPSGRF-915-SPI3_CSN
  PB_10, //D35 - INTERNAL-I2C2_SCL
  PB_11, //D36 - INTERNAL-I2C2_SDA
  PB_12, //D37 - ISM43362-BOOT0
  PB_13, //D38 - ISM43362-WAKEUP
  PB_15, //D39 - SPSGRF-915-SDN
  PC_6,  //D40 - VL53L0X_XSHUT
  PC_7,  //D41 - VL53L0X_GPIO1_EXTI7
  PC_8,  //D42 - LIS3MDL_DRDY_EXTI8
  PC_9,  //D43 - LED3 (WIFI) & LED4 (BLE)
  PC_10, //D44 - INTERNAL-SPI3_SCK
  PC_11, //D45 - INTERNAL-SPI3_MISO
  PC_12, //D46 - INTERNAL-SPI3_MOSI
  PD_7,  //D47 - STSAFE-A100-RESET
  PD_8,  //D48 - INTERNAL-UART3_TX
  PD_9,  //D49 - INTERNAL-UART3_RX
  PD_10, //D50 - LPS22HB_INT_DRDY_EXTI10
  PD_11, //D51 - LSM6DSL_INT1_EXTI11
  PD_13, //D52 - SPBTLE-RF-SPI3_CSN
  PD_15, //D53 - HTS221_DRDY_EXTI15
  PE_0,  //D54 - ISM43362-SPI3_CSN
  PE_1,  //D55 - ISM43362-DRDY_EXTI1
  PE_2,  //D56 - M24SR64-Y-RF_DISABLE
  PE_4,  //D57 - M24SR64-Y-GPO
  PE_5,  //D58 - SPSGRF-915-GPIO3_EXTI5
  PE_6,  //D59 - SPBTLE-RF-IRQ_EXTI6
  PE_7,  //D60 - DFSDM1_DATIN2
  PE_8,  //D61 - ISM43362-RST
  PE_9,  //D62 - DFSDM1_CKOUT
  PE_10, //D63 - QUADSPI_CLK
  PE_11, //D64 - QUADSPI_NCS
  PE_12, //D65 - QUADSPI_BK1_IO0
  PE_13, //D66 - QUADSPI_BK1_IO1
  PE_14, //D67 - QUADSPI_BK1_IO2
  PE_15, //D68 - QUADSPI_BK1_IO3
// CN4 connector
  PC_5,  //D69/A0
  PC_4,  //D70/A1
  PC_3,  //D71/A2
  PC_2,  //D72/A3
  PC_1,  //D73/A4
  PC_0,  //D74/A5
// Duplicated pins in order to be aligned with PinMap_ADC
  PA_1,  //D75/A6
  PA_0,  //D76/A7
  PB_0,  //D77/A8
  PA_3,  //D78/A9
  PB_1,  //D79/A10
  PA_4,  //D80/A11
  PA_2,  //D81/A12
  PA_7,  //D82/A13
  PA_6,  //D83/A14
  PA_5   //D84/A15
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
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_P                          = 7
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  /**Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();

    /**Configure LSE Drive Capability
    */
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /* MSI is enabled after System reset, activate PLL with MSI as source */
  /* NOTE: A limitation is present on the MB1297C-01 board. The reset connexion
  between STM32L4 and the ST-LINK MCU (STM32F103) is not present even if
  schematics are correct. The software reset is available so that the hardware
  missing reset may not be necessary. If the hardware reset is needed, a simple
  workaround is available by soldering an external wire between the SB2 and SB8.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM            = 1;
  RCC_OscInitStruct.PLL.PLLN            = 40;
  RCC_OscInitStruct.PLL.PLLP            = 7;
  RCC_OscInitStruct.PLL.PLLQ            = 2;
  RCC_OscInitStruct.PLL.PLLR            = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_UART4
                              |RCC_PERIPHCLK_UART5|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_DFSDM1
                              |RCC_PERIPHCLK_USB|RCC_PERIPHCLK_ADC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
  PeriphClkInit.Dfsdm1ClockSelection = RCC_DFSDM1CLKSOURCE_PCLK;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the main internal regulator output voltage
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /**Configure the Systick interrupt time
  */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /**Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
