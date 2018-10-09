/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */

#include "variant.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // Pin number
  // This array allows to wrap Arduino pin number(Dx or x)
  // to STM32 PinName (PX_n)
  const PinName digitalPin[] = {
      // USART
      PA_10, // D0 - RX
      PA_9,  // D1 - TX

      // SWD
      PA_14, // D2 - SWCLK
      PA_13, // D3 - SWDIO

      // EXT3
      PE_5, // D4 - EXT_D1
      PE_4, // D5 - EXT_D2
      PE_3, // D6 - EXT_D3
      PE_2, // D7 - EXT_D4
      PE_1, // D8 - EXT_D5

      // SPI
      PB_2, // D9 - SS_SDLCD
      PC_4, // D10 - SS_E
      PA_7, // D11 - MOSI
      PA_6, // D12 - MISO
      PA_5, // D13 - SCK
      PB_1, // D14 - SS_X
      PB_0, // D15 - SS_Y
      PC_5, // D16 - SS_Z

      // I2C
      PB_6, // D17 - SCL
      PB_7, // D18 - SDA

      // USB
      PA_12, // D19 - DD+
      PA_11, // D20 - DD-

      // LED
      PD_0, // D21 - STATUS_LED

      // PWM
      // TIM2
      PA_15, // D22 - X_STEP
      PB_3,  // D23 - Y_STEP
      PB_10, // D24 - Z_STEP
      PB_11, // D25 - E_STEP
      // TIM3
      PB_5, // D26 - PWM_EXT1
      PB_4, // D27 - PWM_EXT2
      PC_8, // D28 - PWM_EXT3
      PC_9, // D29 - PWM_EXT4
      // TIM5
      PA_0, // D30 - PWM_FAN1
      PA_1, // D31 - PWM_BED
      PA_2, // D32 - PWM_FAN2
      PA_3, // D33 - PWM_HEAT

      // Stepper
      PC_12, // D34 - X_EN
      PC_10, // D35 - X_DIR
      PC_11, // D36 - X_DIAG
      PD_4,  // D37 - Y_EN
      PD_6,  // D38 - Y_DIR
      PD_5,  // D39 - Y_DIAG
      PE_15, // D40 - Z_EN
      PE_13, // D41 - Z_DIR
      PE_14, // D42 - Z_DIAG
      PE_11, // D43 - E_EN
      PE_10, // D44 - E_DIR
      PE_12, // D45 - E_DIAG

      // EXT3
      PC_6,  // D46 - LCD_BEEPER
      PC_7,  // D47 - BTN_ENC
      PD_14, // D48 - LCD_EN
      PD_15, // D49 - LCD_RS
      PD_13, // D50 - LCD_D4
      PD_12, // D51 - LCD_D5
      PD_11, // D52 - LCD_D6
      PD_10, // D53 - LCD_D7

      // EXT2
      PC_14, // D54 - BTN_EN1
      PC_15, // D55 - BTN_EN2
      PC_13, // D56 - SD_CARD_DET

      // SD Card Reader
      PE_7,  // D57 - SS_SD

      // Endstops
      PB_12, // D58 - X_MIN
      PB_13, // D59 - X_MAX
      PB_14, // D60 - Y_MIN
      PB_15, // D61 - Y_MAX
      PD_8,  // D62 - Z_MIN
      PD_9,  // D63 - Z_MAX

      // ADC
      PC_0, // D64 - THERM_1
      PC_1, // D65 - THERM_2
      PC_2, // D66 - THERM_3
      PA_4, // D67 - FAN_SPEED1
      PC_3  // D68 - FAN_SPEED2
  };

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
  /**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 24000000
  *            PLL_M                          = 12
  *            PLL_N                          = 216
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
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage */
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 12;
    RCC_OscInitStruct.PLL.PLLN = 216;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    /**Activate the Over-Drive mode */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    /**Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_CLK48;
    PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    /**Enables the Clock Security System */
    HAL_RCC_EnableCSS();

    /**Configure the Systick interrupt time */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    /**Configure the Systick */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
  }

#ifdef __cplusplus
}
#endif
