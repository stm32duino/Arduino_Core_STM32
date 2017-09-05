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

// Pin number following https://github.com/stm32duino/Arduino_Core_STM32F1/blob/master/variants/STM32F103C_BluePill/variant.h
const PinName digitalPin[] = {
  PA_0,  //D0
  PA_1,  //D1
  PA_2,  //D2
  PA_3,  //D3
  PA_4,  //D4
  PA_5,  //D5
  PA_6,  //D6
  PA_7,  //D7
  PA_8,  //D8
  PA_9,  //D9
  PA_10, //D10
  PA_11, //D11
  PA_12, //D12
  PA_13, //D13
  PA_14, //D14
  PA_15, //D15
  PB_0,  //D16
  PB_1,  //D17
  PB_2,  //D18
  PB_3,  //D19
  PB_4,  //D20
  PB_5,  //D21
  PB_6,  //D22
  PB_7,  //D23
  PB_8,  //D24
  PB_9,  //D25
  PB_10, //D26
  PB_11, //D27
  PB_12, //D28
  PB_13, //D29
  PB_14, //D30
  PB_15, //D31
  PC_13, //D32 - LED
  PC_14, //D33
  PC_15, //D34
  // Duplicated pins in order to be aligned with PinMap_ADC
  PA_0,  //D35/A0 = D0
  PA_1,  //D36/A1 = D1
  PA_2,  //D37/A2 = D2
  PA_3,  //D38/A3 = D3
  PA_4,  //D39/A4 = D4
  PA_5,  //D40/A5 = D5
  PA_6,  //D41/A6 = D6
  PA_7,  //D42/A7 = D7
  PB_0,  //D43/A8 = D8
  PB_1   //D44/A9 = D9
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */

HardwareSerial Serial1(PA_10, PA_9);
#ifdef ENABLE_SERIAL2
HardwareSerial Serial2(PA_3, PA_2);
#endif
#ifdef ENABLE_SERIAL3
HardwareSerial Serial3(PB_11, PB_10);
#endif

#if defined(SERIAL_USB) && defined(USBCON)
USBSerial Serial;    //available on PA11/PA12
#endif

void serialEvent1() __attribute__((weak));
void serialEvent1() { }
#ifdef ENABLE_SERIAL2
void serialEvent2() __attribute__((weak));
void serialEvent2() { }
#endif
#ifdef ENABLE_SERIAL3
void serialEvent3() __attribute__((weak));
void serialEvent3() { }
#endif

#if defined(SERIAL_USB) && defined(USBCON)
void serialEvent() __attribute__((weak));
void serialEvent() { }
#endif

void serialEventRun(void)
{
  if (Serial1.available()) serialEvent1();
#ifdef ENABLE_SERIAL2
  if (Serial2.available()) serialEvent2();
#endif
#ifdef ENABLE_SERIAL3
  if (Serial3.available()) serialEvent3();
#endif

#if defined(SERIAL_USB) && defined(USBCON)
  if (Serial.available()) serialEvent();
#endif
}

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SERIAL_USB) && defined(USBCON)
void USBSerial_Rx_Handler(uint8_t *data, uint16_t len){
  Serial.CDC_RxHandler(data, len);
}
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLL_Source                     = HSE
  *            PLL_Mul                        = 9
  *            Flash Latency(WS)              = 2
  *            ADC Prescaler                  = 6
  *            USB Prescaler                  = 1.5
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    while(1);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
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
