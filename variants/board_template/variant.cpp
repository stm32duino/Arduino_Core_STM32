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
extern "C" {
#endif

// Digital PinName array
// This array allows to wrap Arduino pin number(Dx or x)
// to STM32 PinName (PX_n)
const PinName digitalPin[] = {
  //PX_n, //Dx
  P, //D0
  P, //D1
  P, //D2
  P, //D3
  P, //D4
  P, //D5
  P, //D6
  P, //D7
  P, //D8
  P, //D9
  P, //D10
  P, //D11
  P, //D12
  P, //D13
  P, //D14
  P, //D15
  P, //D16/A0
  P, //D17/A1
  P, //D18/A2
  P, //D19/A3
  P, //D20/A4
  P, //D21/A5
  // Required only if Ax pins are automaticaly defined using `NUM_ANALOG_FIRST`
  // and have to be contiguous in this array
  // Duplicated pins in order to be aligned with PinMap_ADC
  P, //D22/A6 = D
  P, //D23/A7 = D
  P  //D24/A8 = D
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
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  // Here copy the desired System Clock Configuration
  // It could be generated thanks STM32CubeMX after code generation for Toolchain/IDE: 'SW4STM32',
  // available in src/main.c
  // or
  // copied from a STM32CubeYY project examples
  // where 'YY' could be F0, F1, F2, F3, F4, F7, G0, G4, H7, L0, L1, L4, MP1, WB
}

#ifdef __cplusplus
}
#endif
