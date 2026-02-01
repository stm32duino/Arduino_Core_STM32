/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_hsem.h
  * @author  MCD Application Team
  * @brief   Header file of HSEM HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WBAxx_HAL_HSEM_H
#define STM32WBAxx_HAL_HSEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
   * @{
   */

/** @addtogroup HSEM
   * @{
   */

/* Exported constants --------------------------------------------------------*/

/** @defgroup HSEM_Exported_Constants HSEM
  * @{
  */
/** @defgroup HSEM_Attributes HSEM Attributes
  * @brief HSEM Privilege/NPrivilege and Secure/NSecure Attributes
  * @{
  */
#define HSEM_NSEC_PRIV    HSEM_R_PRIV                 /*!< NSecure and Privileged attribute  */
#define HSEM_NSEC_NPRIV   0x0U                        /*!< NSecure and NPrivileged attribute */
#define HSEM_SEC_PRIV     (HSEM_R_SEC  | HSEM_R_PRIV) /*!< Secure and Privileged attribute   */
#define HSEM_SEC_NPRIV    HSEM_R_SEC                  /*!< Secure and NPrivileged attribute  */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/** @defgroup HSEM_Exported_Macros HSEM Exported Macros
  * @{
  */

/**
  * @brief  SemID to mask helper Macro.
  * @param  __SEMID__: semaphore ID from 0 to 15
  * @retval Semaphore Mask.
  */
#define __HAL_HSEM_SEMID_TO_MASK(__SEMID__) (1 << (__SEMID__))

/**
  * @brief  Enables the specified HSEM interrupts.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval None.
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define __HAL_HSEM_ENABLE_IT(__SEM_MASK__) (HSEM->SIER |= (__SEM_MASK__))
#else
#define __HAL_HSEM_ENABLE_IT(__SEM_MASK__) (HSEM->IER |= (__SEM_MASK__))
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/**
  * @brief  Disables the specified HSEM interrupts.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval None.
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define __HAL_HSEM_DISABLE_IT(__SEM_MASK__) (HSEM->SIER &= ~(__SEM_MASK__))
#else
#define __HAL_HSEM_DISABLE_IT(__SEM_MASK__) (HSEM->IER &= ~(__SEM_MASK__))
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Checks whether interrupt has occurred or not for semaphores specified by a mask.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval semaphores Mask : Semaphores where an interrupt occurred.
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define __HAL_HSEM_GET_IT(__SEM_MASK__) ((__SEM_MASK__) & HSEM->SMISR)
#else
#define __HAL_HSEM_GET_IT(__SEM_MASK__) ((__SEM_MASK__) & HSEM->MISR)
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get the semaphores release status flags.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval semaphores Mask : Semaphores where Release flags rise.
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define __HAL_HSEM_GET_FLAG(__SEM_MASK__) ((__SEM_MASK__) & HSEM->SISR)
#else
#define __HAL_HSEM_GET_FLAG(__SEM_MASK__) ((__SEM_MASK__) & HSEM->ISR)
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Clears the HSEM Interrupt flags.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval None.
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define __HAL_HSEM_CLEAR_FLAG(__SEM_MASK__) (HSEM->SICR |= (__SEM_MASK__))
#else
#define __HAL_HSEM_CLEAR_FLAG(__SEM_MASK__) (HSEM->ICR |= (__SEM_MASK__))
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSEM_Exported_Functions HSEM Exported Functions
  * @{
  */

/** @addtogroup HSEM_Exported_Functions_Group1 Take and Release functions
  * @brief    HSEM Take and Release functions
  * @{
  */

/* HSEM semaphore take (lock) using 2-Step  method ****************************/
HAL_StatusTypeDef  HAL_HSEM_Take(uint32_t SemID, uint32_t ProcessID, uint32_t Attribute);
/* HSEM semaphore fast take (lock) using 1-Step  method ***********************/
HAL_StatusTypeDef  HAL_HSEM_FastTake(uint32_t SemID, uint32_t Attribute);
/* HSEM Release  **************************************************************/
void  HAL_HSEM_Release(uint32_t SemID, uint32_t ProcessID, uint32_t Attribute);
/* HSEM Release All************************************************************/
void  HAL_HSEM_ReleaseAll(uint32_t Key, uint32_t CoreID, uint32_t Attribute);
/* HSEM Check semaphore state Taken or not   **********************************/
uint32_t HAL_HSEM_IsSemTaken(uint32_t SemID);

/**
  * @}
  */

/** @addtogroup HSEM_Exported_Functions_Group2 HSEM Set and Get Key functions
  * @brief    HSEM Set and Get Key functions.
  * @{
  */
/* HSEM Set Clear Key *********************************************************/
void  HAL_HSEM_SetClearKey(uint32_t Key);
/* HSEM Get Clear Key *********************************************************/
uint32_t HAL_HSEM_GetClearKey(void);
/**
  * @}
  */

/** @addtogroup HSEM_Exported_Functions_Group3
  * @brief   HSEM Notification functions
  * @{
  */
/* HSEM Activate HSEM Notification (When a semaphore is released) ) *****************/
void HAL_HSEM_ActivateNotification(uint32_t SemMask);
/* HSEM Deactivate HSEM Notification (When a semaphore is released)  ****************/
void HAL_HSEM_DeactivateNotification(uint32_t SemMask);
/* HSEM Free Callback (When a semaphore is released)  *******************************/
void HAL_HSEM_FreeCallback(uint32_t SemMask);
/* HSEM IRQ Handler  **********************************************************/
void HAL_HSEM_IRQHandler(void);

/**
  * @}
  */

#if defined(HSEM_SECCFGR_SEC0) || defined(HSEM_PRIVCFGR_PRIV0)
/** @addtogroup HSEM_Exported_Functions_Group4
  *  @brief    HSEM Attributes functions.
  * @{
  */
#if defined(HSEM_SECCFGR_SEC0)
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
void HAL_HSEM_SetSemaphoreSecure(uint32_t SemMask);
void HAL_HSEM_SetSemaphoreNonSecure(uint32_t SemMask);
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
uint32_t HAL_HSEM_GetSemaphoreSecure(void);
#endif /* (HSEM_SECCFGR_SEC0) */

#if defined(HSEM_PRIVCFGR_PRIV0)
void HAL_HSEM_SetSemaphorePrivilege(uint32_t SemMask);
void HAL_HSEM_SetSemaphoreNonPrivilege(uint32_t SemMask);
uint32_t HAL_HSEM_GetSemaphorePrivilege(void);
#endif /* (HSEM_PRIVCFGR_PRIV0) */

/**
  * @}
  */
#endif /* (HSEM_SECCFGR_SEC0) || (HSEM_PRIVCFGR_PRIV0) */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup HSEM_Private_Macros HSEM Private Macros
  * @{
  */

#define IS_HSEM_SEMID(__SEMID__) ((__SEMID__) <= HSEM_SEMID_MAX )

#define IS_HSEM_PROCESSID(__PROCESSID__) ((__PROCESSID__) <= HSEM_PROCESSID_MAX )

#define IS_HSEM_KEY(__KEY__) ((__KEY__) <= HSEM_CLEAR_KEY_MAX )

#define IS_HSEM_LOCKID(__LOCKID__) ((__LOCKID__) == HSEM_CPU1_LOCKID)


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WBAxx_HAL_HSEM_H */
