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

// Pin number
const PinName digitalPin[] = {
  PA_3,  //D0
  PA_2,  //D1
  PA_10, //D2
  PB_13, //D3
  PB_5,  //D4
  PB_7,  //D5
  PB_2,  //D6
  PA_8,  //D7
  PA_9,  //D8
  PB_12, //D9
  PB_6,  //D10
  PB_15, //D11
  PB_14, //D12
  PB_13, //D13 - default SB2 is closed
  PB_9,  //D14
  PB_8,  //D15
// Non-arduino headers
// Connector CN2
  NC,    //D16 - BOOT0
  PA_13, //D17 - SWD
  PA_14, //D18 - SWD
  PH_1,  //D19
  PH_0,  //D20
// Connector CN3
  PA_1,  //D21
  PC_2,  //D22
  PC_1,  //D23
  PA_12, //D24
  PA_11, //D25
  PA_0,  //D26/A0
  PA_0,  //D27/A1 - alias for A0 - requires closing solder bridge SB7
  PA_4,  //D28/A2 - RADIO_DIO_5_PORT
  PA_4,  //D29/A3 - alias for A2 - requires closing solder bridge SB8
  PB_9,  //D30/A4 - requires closing solder bridge SB11
  PB_8,  //D31/A5 - requires closing solder bridge SB12
  PA_5,  //D32/A6 - RADIO_DIO_4_PORT
  PC_0,  //D33 - RADIO_RESET_PORT
  PA_7,  //D34 - RADIO_MOSI_PORT
  PA_6,  //D35 - RADIO_MISO_PORT
  PB_3,  //D36 - RADIO_SCLK_PORT
  PA_15, //D37 - RADIO_NSS_PORT
  PB_4,  //D38 - RADIO_DIO_0_PORT
  PB_1,  //D39 - RADIO_DIO_1_PORT
  PB_0,  //D40 - RADIO_DIO_2_PORT
  PC_13, //D41 - RADIO_DIO_3_PORT
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/** System Clock Configuration
*/
WEAK void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
