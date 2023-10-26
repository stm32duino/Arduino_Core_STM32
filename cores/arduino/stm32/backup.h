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
#if !defined(RTC_BKP_INDEX) && defined(LL_RTC_BKP_DR1)
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

#if defined(HAL_PWR_MODULE_ENABLED) && \
    (defined(PWR_CR_DBP) || defined(PWR_CR1_DBP) || defined(PWR_DBPR_DBP))
#define PWR_ENABLE_BACKUP_ACCESS_EXIST
#endif

/* Exported functions ------------------------------------------------------- */
static inline void resetBackupDomain(void)
{
#if defined(PWR_ENABLE_BACKUP_ACCESS_EXIST)
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
#if defined(PWR_ENABLE_BACKUP_ACCESS_EXIST)
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
#if defined(TAMP_BKP0R) && defined(__HAL_RCC_RTCAPB_CLK_ENABLE)
  /* Enable RTC CLK for TAMP backup registers */
  __HAL_RCC_RTCAPB_CLK_ENABLE();
#endif
}

static inline void disableBackupDomain(void)
{
#if defined(PWR_ENABLE_BACKUP_ACCESS_EXIST)
  /* Forbid access to Backup domain */
  HAL_PWR_DisableBkUpAccess();
#endif
#ifdef __HAL_RCC_BKPSRAM_CLK_DISABLE
  /* Disable BKPSRAM CLK for backup SRAM */
  __HAL_RCC_BKPSRAM_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_BKP_CLK_DISABLE
  /* Disable BKP CLK for backup registers */
  __HAL_RCC_BKP_CLK_DISABLE();
#endif
#if defined(TAMP_BKP0R) && defined(__HAL_RCC_RTCAPB_CLK_DISABLE)
  /* Disable RTC CLK for TAMP backup registers */
  __HAL_RCC_RTCAPB_CLK_DISABLE();
#endif
}

static inline void setBackupRegister(uint32_t index, uint32_t value)
{
#if defined(BKP_BASE)
  LL_RTC_BKP_SetRegister(BKP, index, value);
#elif defined(RTC_BKP0R)
  LL_RTC_BAK_SetRegister(RTC, index, value);
#elif defined(TAMP_BKP0R)
#if defined(STM32G4xx) || defined(STM32H5xx) || defined(STM32L5xx) ||\
    defined(STM32U5xx) || defined(STM32MP1xx) || defined(STM32WLxx)
  /* For those series this API requires RTC even if it is not used
     and TAMP is used instead */
  LL_RTC_BKP_SetRegister(RTC, index, value);
#else
  LL_RTC_BKP_SetRegister(TAMP, index, value);
#endif
#elif defined(BKPREG1)
  LL_PWR_BKP_SetRegister(index, value);
#else
  UNUSED(index);
  UNUSED(value);
#endif
}

static inline uint32_t getBackupRegister(uint32_t index)
{
#if defined(BKP_BASE)
  return LL_RTC_BKP_GetRegister(BKP, index);
#elif defined(RTC_BKP0R)
  return LL_RTC_BAK_GetRegister(RTC, index);
#elif defined(TAMP_BKP0R)
#if defined(STM32G4xx) || defined(STM32H5xx) || defined(STM32L5xx) ||\
    defined(STM32U5xx) || defined(STM32MP1xx) || defined(STM32WLxx)
  /* For those series this API requires RTC even if it is not used
     and TAMP is used instead */
  return LL_RTC_BKP_GetRegister(RTC, index);
#else
  return LL_RTC_BKP_GetRegister(TAMP, index);
#endif
#elif defined(BKPREG1)
  return LL_PWR_BKP_GetRegister(index);
#else
  UNUSED(index);
  return 0;
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
