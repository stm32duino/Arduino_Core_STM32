/**
  ******************************************************************************
  * @file    dwt.c
  * @author  Frederic Pillon
  * @brief   Provide Data Watchpoint and Trace services
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019, STMicroelectronics
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#include "dwt.h"

#ifdef DWT_BASE
#ifdef __cplusplus
extern "C" {
#endif


uint32_t dwt_init(void)
{

  /* Enable use of DWT */
  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  }

  /* Unlock */
  dwt_access(true);

  /* Reset the clock cycle counter value */
  DWT->CYCCNT = 0;

  /* Enable  clock cycle counter */
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk;

  /* 3 NO OPERATION instructions */
  __asm volatile(" nop      \n\t"
                 " nop      \n\t"
                 " nop      \n\t");

  /* Check if clock cycle counter has started */
  return (DWT->CYCCNT) ? 0 : 1;
}

void dwt_access(bool ena)
{
#if (__CORTEX_M == 0x07U)
  /*
   * Define DWT LSR mask which is (currentuly) not defined by the CMSIS.
   * Same as ITM LSR one.
   */
#if !defined DWT_LSR_Present_Msk
#define DWT_LSR_Present_Msk ITM_LSR_Present_Msk
#endif
#if !defined DWT_LSR_Access_Msk
#define DWT_LSR_Access_Msk ITM_LSR_Access_Msk
#endif
  uint32_t lsr = DWT->LSR;

  if ((lsr & DWT_LSR_Present_Msk) != 0) {
    if (ena) {
      if ((lsr & DWT_LSR_Access_Msk) != 0) { //locked
        DWT->LAR = 0xC5ACCE55;
      }
    } else {
      if ((lsr & DWT_LSR_Access_Msk) == 0) { //unlocked
        DWT->LAR = 0;
      }
    }
  }
#else /* __CORTEX_M */
  UNUSED(ena);
#endif /* __CORTEX_M */
}

#ifdef __cplusplus
}
#endif

#endif
