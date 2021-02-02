/*
 *******************************************************************************
 * Copyright (c) 2016-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#include "dwt.h"
#include "hw_config.h"
#include "clock.h"
#include "usbd_if.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  This function performs the global init of the system (HAL, IOs...)
  * @param  None
  * @retval None
  */
void hw_config_init(void)
{
  /* Init DWT if present */
#ifdef DWT_BASE
  dwt_init();
#endif

  /* Initialize the HAL */
  HAL_Init();

#ifdef HSEM_BASE
  __HAL_RCC_HSEM_CLK_ENABLE();
#endif

  configHSECapacitorTuning();

  /* Configure the system clock */
  SystemClock_Config();

#if defined (USBCON) && defined(USBD_USE_CDC)
  USBD_CDC_init();
#endif
}
#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
