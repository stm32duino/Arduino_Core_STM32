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

#if defined(HAL_CRC_MODULE_ENABLED)
CRC_HandleTypeDef hcrc = {.Instance =
#if defined(CRC2_BASE)
                            CRC2
#elif defined(CRC_BASE)
                            CRC
#else
#error "No CRC instance available!"
#endif
                         };
#endif

/**
  * @brief  This function performs the global init of the system (HAL, IOs...)
  * @param  None
  * @retval None
  */
void hw_config_init(void)
{
  configIPClock();

#if defined(PWR_CR3_UCPD_DBDIS) || defined(PWR_UCPDR_UCPD_DBDIS)
  /* Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral */
  HAL_PWREx_DisableUCPDDeadBattery();
#endif
#if defined(SYSCFG_CFGR1_UCPD1_STROBE) || defined(SYSCFG_CFGR1_UCPD2_STROBE)
  /* Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral */
  HAL_SYSCFG_StrobeDBattpinsConfig(SYSCFG_CFGR1_UCPD1_STROBE | SYSCFG_CFGR1_UCPD2_STROBE);
#endif /* SYSCFG_CFGR1_UCPD1_STROBE || SYSCFG_CFGR1_UCPD2_STROBE */

#if defined(PWR_SVMCR_ASV)
  HAL_PWREx_EnableVddA();
#endif
  /* Init DWT if present */
#ifdef DWT_BASE
  dwt_init();
#endif

  /* Initialize the HAL */
  HAL_Init();

  configHSECapacitorTuning();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize the CRC */
#if defined(HAL_CRC_MODULE_ENABLED)
  HAL_CRC_Init(&hcrc);
#endif

#if defined (USBCON) && defined(USBD_USE_CDC)
  USBD_CDC_init();
#endif

#if (__CORTEX_M == 33U) &&\
  defined(HAL_ICACHE_MODULE_ENABLED) && !defined(HAL_ICACHE_MODULE_DISABLED)
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK) {
    Error_Handler();
  }
#endif
}
#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
