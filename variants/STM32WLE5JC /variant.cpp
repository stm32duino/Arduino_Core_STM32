/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // Digital PinName array
  // This array allows to wrap Arduino pin number(Dx or x)
  // to STM32 PinName (PX_n)
  const PinName digitalPin[] = {
      //PX_n, //Dx
      PB_6,  //D0
      PB_7,  //D1
      PB_15, //D2
      PA_15, //D3
      PB_4,  //D4
      PB_3,  //D5
      PB_7,  //D6
      PB_6,  //D7
      PB_5,  //D8
      PC_1,  //D9
      PC_0,  //D10
      PA_3,  //D11
      PA_2,  //D12
      PB_10, //D13
      PA_9,  //D14
      PA_0,  //D15
      PB_13, //D16/A0
      PB_9,  //D17/A1
      PB_14, //D18/A2
      PA_10, //D19/A3

      // Required only if Ax pins are automaticaly defined using `NUM_ANALOG_FIRST`
      // and have to be contiguous in this array
      // Duplicated pins in order to be aligned with PinMap_ADC
      //P, //D22/A6 = D
      //P, //D23/A7 = D
      //P  //D24/A8 = D
  };

  // If analog pins are not contiguous in the digitalPin array:
  // Add the analogInputPin array without defining NUM_ANALOG_FIRST
  // Analog (Ax) pin number array
  // where x is the index to retrieve the digital pin number
  const uint32_t analogInputPin[] = {
      //PXn, //Ax = Dx
      2, //A0 = Dx
      8, //A1 = Dy
      3  //A2 = Dz
  }

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
  * @param  None
  * @retval None
  */
  WEAK void SystemClock_Config(void)
  {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    /** Initializes the CPU, AHB and APB busses clocks
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      while (1);
    }
    /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3 | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
      while (1);
    }
  }

#ifdef __cplusplus
}
#endif
