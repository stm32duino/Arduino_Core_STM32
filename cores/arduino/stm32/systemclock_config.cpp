/*

Module: systemclock_config.cpp

Function:
        Provide SystemClock_Config() function for STM32 platform.

Copyright notice and license information:
        Copyright 2018-2019 MCCI Corporation. All rights reserved.

        This library is free software; you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public
        License as published by the Free Software Foundation; either
        version 2.1 of the License, or (at your option) any later version.

        This library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
        See the GNU Lesser General Public License for more details.

        You should have received a copy of the GNU Lesser General Public
        License along with this library; if not, write to the Free
        Software Foundation, Inc., 51 Franklin St, Fifth Floor,
        Boston, MA  02110-1301  USA

Author:
        ChaeHee Won, MCCI Corporation

*/

#include <Arduino.h>

#ifndef	CATENA_CFG_SYSCLK
# ifdef USBCON
#  define CATENA_CFG_SYSCLK	16
# else
#  define CATENA_CFG_SYSCLK	4
# endif
#endif

#if CATENA_CFG_SYSCLK < 16
# ifdef USBCON
#  error USB cannot be supported at clock rates < 16 MHz (CATENA_CFG_SYSCLK < 16)
# endif
#endif

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
  RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };
#if 0	/* Move clock setting code to usbd_conf.c */
  RCC_CRSInitTypeDef RCC_CRSInitStruct = { 0 };
#endif

    /**Configure the main internal regulator output voltage
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|
#ifdef USBCON
                                     RCC_OSCILLATORTYPE_HSI48|
#endif
#if CATENA_CFG_SYSCLK < 16
                                     RCC_OSCILLATORTYPE_MSI;
#else
                                     RCC_OSCILLATORTYPE_HSI;
#endif

  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
#if CATENA_CFG_SYSCLK < 16
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 2;
# if CATENA_CFG_SYSCLK == 2
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
# else	/* CATENA_CFG_SYSCLK == 4 */
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
# endif	/* CATENA_CFG_SYSCLK == 2 */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

#else	/* CATENA_CFG_SYSCLK >= 16 */

  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 18;
# ifdef USBCON
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
# endif
# if CATENA_CFG_SYSCLK == 16
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
# else	/* CATENA_CFG_SYSCLK != 16 */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
#  if CATENA_CFG_SYSCLK == 24
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;	/* SYSCLK == 24Mhz */
#  else	/* CATENA_CFG_SYSCLK == 32 */
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;	/* SYSCLK == 32Mhz */
#  endif
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
# endif
#endif
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
#if CATENA_CFG_SYSCLK < 16
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
#elif CATENA_CFG_SYSCLK == 16
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
#else
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
/*  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;	HCLK = SYSCLK / 2 */
#endif
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

#if CATENA_CFG_SYSCLK < 24
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
#else
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
#endif

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
#ifdef USBCON
                              |RCC_PERIPHCLK_USB
#endif
                              |RCC_PERIPHCLK_RTC;
#if CATENA_CFG_SYSCLK < 24
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
#else
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_HSI;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
#endif
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
#ifdef USBCON
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
#endif
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

#if CATENA_CFG_SYSCLK < 16
  LL_RCC_SetClkAfterWakeFromStop(LL_RCC_STOP_WAKEUPCLOCK_MSI);
#else
  LL_RCC_SetClkAfterWakeFromStop(LL_RCC_STOP_WAKEUPCLOCK_HSI);
#endif

#if 0	/* Move clock setting code to usbd_conf.c */
    /**Enable the SYSCFG APB clock
    */
  __HAL_RCC_CRS_CLK_ENABLE();

    /**Configures CRS
    */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000,1000);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;

  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
#endif

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
