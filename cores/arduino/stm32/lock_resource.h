/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LOCK_RESOURCE_H
#define _LOCK_RESOURCE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "stm32yyxx_ll_hsem.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum {
  LOCK_RESOURCE_STATUS_OK       = 0x00U,
  LOCK_RESOURCE_STATUS_ERROR    = 0x01U,
  LOCK_RESOURCE_STATUS_TIMEOUT  = 0x02U
} LockResource_Status_t;

/* Exported constants --------------------------------------------------------*/
#if defined(STM32WBxx)
/*
 * HW semaphore Complement ID list defined in hw_conf.h from STM32WB.
 * They could be used also for H7 dualcore targets.
 */

/**
 *  The CPU2 may be configured to store the Thread persistent data either in internal NVM storage on CPU2 or in
 *  SRAM2 buffer provided by the user application. This can be configured with the system command SHCI_C2_Config()
 *  When the CPU2 is requested to store persistent data in SRAM2, it can write data in this buffer at any time when needed.
 *  In order to read consistent data with the CPU1 from the SRAM2 buffer, the flow should be:
 *  + CPU1 takes CFG_HW_THREAD_NVM_SRAM_SEMID semaphore
 *  + CPU1 reads all persistent data from SRAM2 (most of the time, the goal is to write these data into an NVM managed by CPU1)
 *  + CPU1 releases CFG_HW_THREAD_NVM_SRAM_SEMID semaphore
 *  CFG_HW_THREAD_NVM_SRAM_SEMID semaphore makes sure CPU2 does not update the persistent data in SRAM2 at the same time CPU1 is reading them.
 *  There is no timing constraint on how long this semaphore can be kept.
 */
#define CFG_HW_THREAD_NVM_SRAM_SEMID                    9

/**
 *  The CPU2 may be configured to store the BLE persistent data either in internal NVM storage on CPU2 or in
 *  SRAM2 buffer provided by the user application. This can be configured with the system command SHCI_C2_Config()
 *  When the CPU2 is requested to store persistent data in SRAM2, it can write data in this buffer at any time when needed.
 *  In order to read consistent data with the CPU1 from the SRAM2 buffer, the flow should be:
 *  + CPU1 takes CFG_HW_BLE_NVM_SRAM_SEMID semaphore
 *  + CPU1 reads all persistent data from SRAM2 (most of the time, the goal is to write these data into an NVM managed by CPU1)
 *  + CPU1 releases CFG_HW_BLE_NVM_SRAM_SEMID semaphore
 *  CFG_HW_BLE_NVM_SRAM_SEMID semaphore makes sure CPU2 does not update the persistent data in SRAM2 at the same time CPU1 is reading them.
 *  There is no timing constraint on how long this semaphore can be kept.
 */
#define CFG_HW_BLE_NVM_SRAM_SEMID                    8

/*
 * Index of the semaphore used by CPU2 to prevent the CPU1 to either write or
 * erase data in flash. The CPU1 shall not either write or erase in flash when
 * this semaphore is taken by the CPU2. When the CPU1 needs to either write or
 * erase in flash, it shall first get the semaphore and release it just
 * after writing a raw (64bits data) or erasing one sector.
 *  Once the Semaphore has been released, there shall be at least 1us before it can be taken again. This is required
 *  to give the opportunity to CPU2 to take it.
 * On v1.4.0 and older CPU2 wireless firmware, this semaphore is unused and
 * CPU2 is using PES bit. By default, CPU2 is using the PES bit to protect its
 * timing. The CPU1 may request the CPU2 to use the semaphore instead of the
 * PES bit by sending the system command SHCI_C2_SetFlashActivityControl()
 */
#define CFG_HW_BLOCK_FLASH_REQ_BY_CPU2_SEMID                    7U

/*
 * Index of the semaphore used by CPU1 to prevent the CPU2 to either write or
 * erase data in flash. In order to protect its timing, the CPU1 may get this
 * semaphore to prevent the  CPU2 to either write or erase in flash
 * (as this will stall both CPUs)
 * The PES bit shall not be used as this may stall the CPU2 in some cases.
 */
#define CFG_HW_BLOCK_FLASH_REQ_BY_CPU1_SEMID                    6U

/*
 * Index of the semaphore used to manage the CLK48 clock configuration
 * When the USB is required, this semaphore shall be taken before configuring
 * the CLK48 for USB and should be released after the application switch OFF
 * the clock when the USB is not used anymore. When using the RNG, it is good
 * enough to use CFG_HW_RNG_SEMID to control CLK48.
 * More details in AN5289
 */
#define CFG_HW_CLK48_CONFIG_SEMID                               5U
#define CFG_HW_RCC_CRRCR_CCIPR_SEMID     CFG_HW_CLK48_CONFIG_SEMID

/* Index of the semaphore used to manage the entry Stop Mode procedure */
#define CFG_HW_ENTRY_STOP_MODE_SEMID                            4U
#define CFG_HW_ENTRY_STOP_MODE_MASK_SEMID   (1U << CFG_HW_ENTRY_STOP_MODE_SEMID)

/* Index of the semaphore used to access the RCC */
#define CFG_HW_RCC_SEMID                                        3U

/* Index of the semaphore used to access the FLASH */
#define CFG_HW_FLASH_SEMID                                      2U

/* Index of the semaphore used to access the PKA */
#define CFG_HW_PKA_SEMID                                        1U

/* Index of the semaphore used to access the RNG */
#define CFG_HW_RNG_SEMID                                        0U

/* Index of the semaphore used to access GPIO */
#define CFG_HW_GPIO_SEMID                                       8U

/* Index of the semaphore used to access the EXTI */
#define CFG_HW_EXTI_SEMID                                       9U

#elif defined(STM32MP1xx)
/*
 * HW semaphore from STM32MP1
 * EXTI and GPIO are inherited from STM32MP1 Linux.
 * Other SEMID are not used by linux and must not be used here,
 * but reserved for MPU.
 */
/* Index of the semaphore used to access GPIO */
#define CFG_HW_GPIO_SEMID                                       0U

/* Index of the semaphore used to access the EXTI */
#define CFG_HW_EXTI_SEMID                                       1U
#endif /* STM32WBxx */

/* Fake semaphore ID definition for compilation purpose only */
#ifndef HSEM_SEMID_MAX
#define HSEM_SEMID_MAX                                          0U
#endif
#ifndef CFG_HW_BLOCK_FLASH_REQ_BY_CPU2_SEMID
#define CFG_HW_BLOCK_FLASH_REQ_BY_CPU2_SEMID   (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_BLOCK_FLASH_REQ_BY_CPU1_SEMID
#define CFG_HW_BLOCK_FLASH_REQ_BY_CPU1_SEMID   (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_CLK48_CONFIG_SEMID
#define CFG_HW_CLK48_CONFIG_SEMID              (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_RCC_CRRCR_CCIPR_SEMID
#define CFG_HW_RCC_CRRCR_CCIPR_SEMID           (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_ENTRY_STOP_MODE_SEMID
#define CFG_HW_ENTRY_STOP_MODE_SEMID           (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_RCC_SEMID
#define CFG_HW_RCC_SEMID                       (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_FLASH_SEMID
#define CFG_HW_FLASH_SEMID                     (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_PKA_SEMID
#define CFG_HW_PKA_SEMID                       (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_RNG_SEMID
#define CFG_HW_RNG_SEMID                       (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_GPIO_SEMID
#define CFG_HW_GPIO_SEMID                      (HSEM_SEMID_MAX +1)
#endif
#ifndef CFG_HW_EXTI_SEMID
#define CFG_HW_EXTI_SEMID                      (HSEM_SEMID_MAX +1)
#endif

/* Hardware Semaphore wait forever value */
#define HSEM_LOCK_WAIT_FOREVER                         0xFFFFFFFFU
/* Hardware Semaphore default retry value */
#ifndef HSEM_LOCK_DEFAULT_RETRY
#define HSEM_LOCK_DEFAULT_RETRY                            0xFFFFU
#endif

/*
 * @brief  hsem_lock function is used for register protection of shared Peripheral
 *         and shall be called before accessing registers of this shared Peripheral
 *         If Semaphore id is already taken, the function will busy loop waiting for it to
 *         be released, but give up after @retry downcounter have elapsed
 * @param  semID: Semaphore id used to identify which peripheral to protect
 * @param  retry: number of retry
 * @retval None
 */
static inline void hsem_lock(uint32_t semID, uint32_t retry)
{
#if defined(STM32MP1xx) || defined(STM32WBxx)
  if ((semID) <= HSEM_SEMID_MAX) {
    while (LL_HSEM_1StepLock(HSEM, semID)) {
      if (retry != HSEM_LOCK_WAIT_FOREVER) {
        retry--;
        if (retry == 0) {
          Error_Handler();
        }
      }
    }
  }
#else
  UNUSED(semID);
  UNUSED(retry);
#endif /* STM32MP1xx || STM32WBxx */
}

/*
 * @brief  hsem_unlock released a previously-acquired semaphore
 * @param  semID Semaphore id used to identify which peripheral to release
 * @retval None
 */
static inline void hsem_unlock(uint32_t semID)
{
#if defined(STM32MP1xx) || defined(STM32WBxx)
  if ((semID) <= HSEM_SEMID_MAX) {
    LL_HSEM_ReleaseLock(HSEM, semID, 0);
  }
#else
  UNUSED(semID);
#endif /* STM32MP1xx || STM32WBxx */
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _LOCK_RESOURCE_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
