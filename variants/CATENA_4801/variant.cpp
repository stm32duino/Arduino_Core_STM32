/*
  Copyright (c) 2011 Arduino.  All right reserved.
  Copyright (c) 2018 MCCI Corporation.  All rights reserved.

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
#include "stm32l0xx_ll_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
// This array allows to map Arduino pin number(Dx or x)
// to STM32 PinName (PX_n) -- don't forget to also change variant.h
const PinName digitalPin[] = {
//PX_n,  //Dx
  PA_10, //D0      D0_UART_RX		JP4-2
  PA_9,  //D1      D1_UART_TX		JP4-3
  PA_7,  //D2      RADIO_MOSI
  PA_6,  //D3      RADIO_MISO
  PB_3,  //D4      RADIO_SCK
  PB_6,  //D5      EN
  PA_13, //D6      D6_SWDIO		JP1-4
  PA_15, //D7      RADIO_NSS
  PC_0,  //D8      RADIO_RESET
  PA_14, //D9      D9_SWCLK		JP1-3
  PH_1,  //D10     D10
  PB_5,  //D11     D11
  PB_7,  //D12     D12
  PB_2,  //D13     D13
  PA_0,  //D14/A0  A0_VBAT_DET
  PA_5,  //D15/A1  A1
  PA_4,  //D16/A2  A2
  PA_3,  //D17/A3  A3_RS485_RX
  PA_2,  //D18/A4  A4_RS485_TX
  PB_12, //D19/A5  NSS
  PB_9,  //D20/A6  SDA
  PB_8,  //D21/A7  SCL
  PB_14, //D22/A8  MISO
  PB_15, //D23/A9  MOSI
  PB_13, //D24/A10 SCK
  PB_4,  //D25/A11 RADIO_DIO_0
  PB_1,  //D26/A12 RADIO_DIO_1
  PB_0,  //D27/A13 RADIO_DIO_2
  PC_13, //D28/A14 RADIO_DIO_3
  PA_1,  //D29/A15 RADIO_ANT_SWITCH_RX       CRF1
  PC_1,  //D30/A16 RADIO_ANT_SWITCH_TX_BOOST CRF3
  PC_2,  //D31/A17 RADIO_ANT_SWITCH_TX_RFO   CRF2
  NC,    //D32     Flash Write-Protect (not supported these platforms)
  PA_8,  //D33     TCXO VDD, possibly VDD boost enable.
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
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;
#ifdef USBCON
  RCC_CRSInitTypeDef RCC_CRSInitStruct;
#endif

    /**Configure the main internal regulator output voltage
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|
#ifdef USBCON
                                     RCC_OSCILLATORTYPE_HSI48|
#endif
                                     RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
#ifdef USBCON
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
#endif
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
//  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;	/* SYSCLK == 24Mhz */
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;	/* SYSCLK == 32Mhz */
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
#ifdef USBCON
                              |RCC_PERIPHCLK_USB
#endif
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
#ifdef USBCON
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
#endif
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  LL_RCC_SetClkAfterWakeFromStop(LL_RCC_STOP_WAKEUPCLOCK_HSI);

#ifdef USBCON
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

/*

Name:	yield

Function:
        Yield CPU

Definition:
        void yield(void);

Description:
        This function override default week yield() function in the cores/
        arduino/hooks.c file. It requests wait for interrupt.

Returns:
        No explicit result.

Notes:
        We need to keep this function in this file because linker should link
        this yield function in this file. So do not make this yield function
        in separate file.

*/

void yield(void)
        {
        /* Read PRIMASK register, check interrupt status before disable them */
        /* Returns 0 if they are enabled, or non-zero if disabled */
        if (__get_PRIMASK())
                {
                if (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)
                        {
                        SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;
                        HAL_IncTick();
                        }
                }
        else
                {
                /* Request Wait For Interrupt */
                __WFI();
                }
        }

uint32_t HAL_GetTick(void)
        {
        extern __IO uint32_t uwTick;

        /* Read PRIMASK register, check interrupt status before disable them */
        /* Returns 0 if they are enabled, or non-zero if disabled */
        if (__get_PRIMASK())
                {
                if (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)
                        {
                        SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;
                        HAL_IncTick();
                        }
                }

        return uwTick;
        }

#ifdef __cplusplus
}
#endif
