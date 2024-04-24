/**
  ******************************************************************************
  * @file    dwt.h
  * @author  Frederic Pillon
  * @brief   Header for dwt.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DWT_H_
#define _DWT_H_

#include "stm32_def.h"
#include <stdbool.h>

#ifdef DWT_BASE

#ifdef __cplusplus
extern "C" {
#endif

uint32_t dwt_init(void);
void dwt_access(bool ena);

static inline uint32_t dwt_max_sec(void)
{
  return (UINT32_MAX / SystemCoreClock);
};

static inline uint32_t dwt_max_msec(void)
{
  return (UINT32_MAX / (SystemCoreClock / 1000));
};

static inline uint32_t dwt_max_usec(void)
{
  return (UINT32_MAX / (SystemCoreClock / 1000000));
};

static inline uint32_t dwt_getCycles(void)
{
  return (DWT->CYCCNT);
};

#ifdef __cplusplus
}
#endif

#endif /* DWT_BASE */
#endif /* _DWT_H_ */
