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
  !defined(STM32L1xx) && !defined(STM32L4xx) && !defined(STM32MP1xx)) || \
  defined(RTC_BACKUP_SUPPORT)
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

#if defined (BL_HID)
#if !defined(HID_MAGIC_NUMBER_BKP_INDEX)
#define HID_MAGIC_NUMBER_BKP_INDEX LL_RTC_BKP_DR4
#endif /* HID_MAGIC_NUMBER_BKP_INDEX */
#if !defined(HID_OLD_MAGIC_NUMBER_BKP_INDEX) && defined(LL_RTC_BKP_DR10)
#define HID_OLD_MAGIC_NUMBER_BKP_INDEX LL_RTC_BKP_DR10
#endif /* HID_OLD_MAGIC_NUMBER_BKP_INDEX */
#ifndef HID_MAGIC_NUMBER_BKP_VALUE
#define HID_MAGIC_NUMBER_BKP_VALUE 0x424C
#endif /* HID_MAGIC_NUMBER_BKP_VALUE */
#endif /* BL_HID */

/* Exported functions ------------------------------------------------------- */
static inline void resetBackupDomain(void)
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

static inline void enableBackupDomain(void)
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
  /* Enable BKP CLK for backup registers */
  __HAL_RCC_BKP_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_BKPSRAM_CLK_ENABLE
  /* Enable BKPSRAM CLK for backup SRAM */
  __HAL_RCC_BKPSRAM_CLK_ENABLE();
#endif
}

static inline void disableBackupDomain(void)
{
#ifdef HAL_PWR_MODULE_ENABLED
  /* Forbid access to Backup domain */
  HAL_PWR_DisableBkUpAccess();
#endif
#ifdef __HAL_RCC_BKPSRAM_CLK_DISABLE
  /* Disnable BKPSRAM CLK for backup SRAM */
  __HAL_RCC_BKPSRAM_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_BKP_CLK_DISABLE
  /* Disable BKP CLK for backup registers */
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
#elif defined(STM32G0xx)
  LL_RTC_BKP_SetRegister(TAMP, index, value);
#elif defined(STM32G4xx)
  LL_RTC_BKP_SetRegister(RTC, index, value);
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
#elif defined(STM32G0xx)
  return LL_RTC_BKP_GetRegister(TAMP, index);
#elif defined(STM32G4xx)
  return LL_RTC_BKP_GetRegister(RTC, index);
#else
#ifdef ENABLE_BACKUP_SUPPORT
  return LL_RTC_BAK_GetRegister(RTC, index);
#else
  UNUSED(index);
  return 0;
#endif
#endif
}

static inline void writeBackupSRAM(uint32_t offset, uint32_t *data, uint32_t length)
{
#if defined(BKPSRAM_BASE)
  uint32_t i = 0;
  /* Write 32-Bit data to Backup SRAM */
  for (i = 0; i < length; i++) {
    *(__IO uint32_t *)(BKPSRAM_BASE + (offset + i) * 4) = data[i];
  }
#else
  UNUSED(offset);
  UNUSED(data);
  UNUSED(length);
#endif
}

static inline void readBackupSRAM(uint32_t offset, uint32_t *data, uint32_t length)
{
#if defined(BKPSRAM_BASE)
  uint32_t i = 0;
  /* Read 32-Bit data from Backup SRAM */
  for (i = 0; i < length; i++) {
    data[i] = *(__IO uint32_t *)(BKPSRAM_BASE + (offset + i) * 4);
  }
#else
  UNUSED(offset);
  UNUSED(data);
  UNUSED(length);
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* __BACKUP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
