/**
  ******************************************************************************
  * @file    backup.h
  * @author  fpistm
  * @brief   Header for backup domain driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
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
#ifndef __BACKUP_H
#define __BACKUP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "stm32yyxx_ll_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported macro ------------------------------------------------------------*/
#if (!defined(STM32F0xx) && !defined(STM32F3xx) && !defined(STM32L0xx) &&\
  !defined(STM32L1xx) && !defined(STM32L4xx)) || defined(RTC_BACKUP_SUPPORT)
#if !defined(STM32L412xx) && !defined(STM32L422xx)
#define ENABLE_BACKUP_SUPPORT
#endif
#endif

#if !defined(RTC_BKP_INDEX) && defined(ENABLE_BACKUP_SUPPORT)
#define RTC_BKP_INDEX LL_RTC_BKP_DR1
#else
#define RTC_BKP_INDEX 0
#endif
#ifndef RTC_BKP_VALUE
#define RTC_BKP_VALUE 0x32F2
#endif


/* Exported functions ------------------------------------------------------- */
static inline void resetBackupRegister(void)
{
#ifdef HAL_PWR_MODULE_ENABLED
  /*  Enable access to the RTC registers */
  HAL_PWR_EnableBkUpAccess();
  /**
    *  Write twice the value to flush the APB-AHB bridge
    *  This bit shall be written in the register before writing the next one
    */
  HAL_PWR_EnableBkUpAccess();
#endif
  __HAL_RCC_BACKUPRESET_FORCE();
  __HAL_RCC_BACKUPRESET_RELEASE();
}

static inline void enableBackupRegister(void)
{
  /* Enable Power Clock */
#ifdef __HAL_RCC_PWR_IS_CLK_DISABLED
  if (__HAL_RCC_PWR_IS_CLK_DISABLED()) {
    __HAL_RCC_PWR_CLK_ENABLE();
  }
#endif
#ifdef HAL_PWR_MODULE_ENABLED
  /* Allow access to Backup domain */
  HAL_PWR_EnableBkUpAccess();
#endif
#ifdef __HAL_RCC_BKP_CLK_ENABLE
  /* Enable BKP CLK enable for backup registers */
  __HAL_RCC_BKP_CLK_ENABLE();
#endif
}

static inline void disableBackupRegister(void)
{
#ifdef HAL_PWR_MODULE_ENABLED
  /* Forbid access to Backup domain */
  HAL_PWR_DisableBkUpAccess();
#endif
#ifdef __HAL_RCC_BKP_CLK_DISABLE
  /* Disable BKP CLK enable for backup registers */
  __HAL_RCC_BKP_CLK_DISABLE();
#endif
  /* Disable Power Clock */
#ifdef __HAL_RCC_PWR_IS_CLK_DISABLED
  if (!__HAL_RCC_PWR_IS_CLK_DISABLED()) {
    __HAL_RCC_PWR_CLK_DISABLE();
  }
#endif
}

static inline void setBackupRegister(uint32_t index, uint32_t value)
{
#if defined(STM32F1xx)
  LL_RTC_BKP_SetRegister(BKP, index, value);
#else
#ifdef ENABLE_BACKUP_SUPPORT
  LL_RTC_BAK_SetRegister(RTC, index, value);
#else
  UNUSED(index);
  UNUSED(value);
#endif
#endif
}

static inline uint32_t getBackupRegister(uint32_t index)
{
#if defined(STM32F1xx)
  return LL_RTC_BKP_GetRegister(BKP, index);
#else
#ifdef ENABLE_BACKUP_SUPPORT
  return LL_RTC_BAK_GetRegister(RTC, index);
#else
  UNUSED(index);
  return 0;
#endif
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* __BACKUP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
