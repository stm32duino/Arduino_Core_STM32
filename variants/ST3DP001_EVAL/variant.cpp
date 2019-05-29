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

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

const PinName digitalPin[] = {
  PA_9,  // TX
  PA_10, // RX

  // WIFI
  PD_3,  // CTS
  PD_4,  // RTS
  PD_5,  // TX
  PD_6,  // RX
  PB_5,  // WIFI_WAKEUP
  PE_11, // WIFI_RESET
  PE_12, // WIFI_BOOT

  // STATUS_LED
  PE_1,  //STATUS_LED

  // SPI USER
  PB_12, // SPI_CS
  PB_15, // SPI_MOSI
  PB_14, // SPI_MISO
  PB_13, // SPI_SCK

  // I2C USER
  PB_7,  // SDA
  PB_6,  // SCL

  // SPI
  PA_4,  // SPI_CS
  PA_5,  // SPI_SCK
  PA_6,  // SPI_MISO
  PA_7,  // SPI_MOSI

  // JTAG
  PA_13, // JTAG_TMS/SWDIO
  PA_14, // JTAG_TCK/SWCLK
  PB_3,  // JTAG_TDO/SWO

  // SDCARD
  PC_8,  // SDIO_D0
  PC_9,  // SDIO_D1
  PA_15, // SD_CARD_DETECT
  PC_10, // SDIO_D2
  PC_11, // SDIO_D3
  PC_12, // SDIO_CK
  PD_2,  // SDIO_CMD

  // OTG
  PA_11, // OTG_DM
  PA_12, // OTG_DP

  // IR/PROBE
  PD_1,  // IR_OUT
  PC_1,  // IR_ON

  // USER_PINS
  PD_7,  // USER3
  PB_9,  // USER1
  PE_0,  // USER2
  PB_4,  // USER4

  // USERKET
  PE_7,  // USER_BUTTON

  // ENDSTOPS
  PD_8,  // X_STOP
  PD_9,  // Y_STOP
  PD_10, // Z_STOP
  PD_11, // U_STOP
  PA_8,  // V_STOP
  PD_0,  // W_STOP

  // HEATERS
  PD_13, // BED_HEAT_2
  PD_14, // BED_HEAT_1
  PD_15, // BED_HEAT_3
  PC_7,  // E1_HEAT_PWM
  PB_0,  // E2_HEAT_PWM
  PB_1,  // E3_HEAT_PWM

  // THERMISTOR
  PC_2,  // BED_THERMISTOR_1
  PC_3,  // BED_THERMISTOR_2
  PA_3,  // BED_THERMISTOR_3
  PA_0,  // E1_THERMISTOR
  PA_1,  // E2_THERMISTOR
  PA_2,  // E3_THERMISTOR

  // FANS
  PC_4,  // E1_FAN
  PC_5,  // E2_FAN
  PE_8,  // E3_FAN

  // X_MOTOR
  PE_13, // X_RESET
  PE_14, // X_PWM
  PE_15, // X_DIR

  // Y_MOTOR
  PE_10, // Y_RESET
  PB_10, // Y_PWM
  PE_9,  // Y_DIR

  // Z_MOTOR
  PC_15, // Z_RESET
  PC_6,  // Z_PWM
  PC_0,  // Z_DIR

  // E1_MOTOR
  PC_14, // E1_RESET
  PC_13, // E1_DIR
  PD_12, // E1_PWM

  // E2_MOTOR
  PE_4,  // E2_RESET
  PE_5,  // E2_PWM
  PE_6,  // E2_DIR

  // E3_MOTOR
  PE_3,  // E3_RESET
  PE_2,  // E3_DIR
  PB_8   // E3_PWM
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
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 84000000
  *            HCLK(Hz)                       = 84000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 336
  *            PLL_P                          = 4
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale2 mode
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
