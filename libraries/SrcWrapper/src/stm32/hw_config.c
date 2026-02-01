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
#if defined (USBCON) && defined(USBD_USE_CDC)
  #include "usbd_if.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(STM32H7xx)
#if !defined(USE_PWR_LDO_SUPPLY) &&  !defined(USE_PWR_DIRECT_SMPS_SUPPLY) &&\
!defined(USE_PWR_EXTERNAL_SOURCE_SUPPLY) && !defined(USE_PWR_SMPS_1V8_SUPPLIES_LDO) &&\
!defined(USE_PWR_SMPS_2V5_SUPPLIES_LDO) && !defined(USE_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO) &&\
!defined(USE_PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO) && !defined(USE_PWR_SMPS_1V8_SUPPLIES_EXT) &&\
!defined(USE_PWR_SMPS_2V5_SUPPLIES_EXT)
#pragma message "\n\
Configure the system power supply according to the\n\
definition to be used at compilation preprocessing level.\n\
The application shall set one of the following configuration option:\n\
                            - USE_PWR_LDO_SUPPLY\n\
                            - USE_PWR_DIRECT_SMPS_SUPPLY\n\
                            - USE_PWR_EXTERNAL_SOURCE_SUPPLY\n\
                            - USE_PWR_SMPS_1V8_SUPPLIES_LDO\n\
                            - USE_PWR_SMPS_2V5_SUPPLIES_LDO\n\
                            - USE_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO\n\
                            - USE_PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO\n\
                            - USE_PWR_SMPS_1V8_SUPPLIES_EXT\n\
                            - USE_PWR_SMPS_2V5_SUPPLIES_EXT\n"
#endif
#endif

#if defined(HAL_CRC_MODULE_ENABLED)
CRC_HandleTypeDef hcrc = {.Instance =
#if defined(CRC2_BASE)
                            CRC2,
#elif defined(CRC_BASE)
                            CRC,
#else
#error "No CRC instance available!"
#endif
#if defined(CRC_INPUTDATA_FORMAT_BYTES)
                          .InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES
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

#if !defined (SKIP_DISABLING_UCPD_DEAD_BATTERY)
#if defined(PWR_CR3_UCPD_DBDIS) || defined(PWR_UCPDR_UCPD_DBDIS)
  /* Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral */
  HAL_PWREx_DisableUCPDDeadBattery();
#endif
#if defined(SYSCFG_CFGR1_UCPD1_STROBE) || defined(SYSCFG_CFGR1_UCPD2_STROBE)
  /* Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral */
  HAL_SYSCFG_StrobeDBattpinsConfig(SYSCFG_CFGR1_UCPD1_STROBE | SYSCFG_CFGR1_UCPD2_STROBE);
#endif /* SYSCFG_CFGR1_UCPD1_STROBE || SYSCFG_CFGR1_UCPD2_STROBE */
#endif /* !SKIP_DISABLING_UCPD_DEAD_BATTERY */

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
