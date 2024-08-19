/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_hsem.h
  * @author  MCD Application Team
  * @brief   Header file of HSEM LL module.
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
#ifndef STM32WBAxx_LL_HSEM_H
#define STM32WBAxx_LL_HSEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx.h"

/** @addtogroup STM32WBAxx_LL_Driver
  * @{
  */

#if defined(HSEM)

/** @defgroup HSEM_LL HSEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup HSEM_LL_Exported_Constants HSEM Exported Constants
  * @{
  */

/** @defgroup HSEM_LL_EC_LOCKID LOCKID Defines
  * @{
  */
#define LL_HSEM_LOCKID_NONE             0U
#define LL_HSEM_LOCKID_CPU1             HSEM_CR_LOCKID_CPU1
#define LL_HSEM_LOCKID                  HSEM_CR_LOCKID_CURRENT
/**
  * @}
  */

/** @defgroup HSEM_LL_EC_ATTRIBUTES Attributes Defines
  * @brief HSEM Privilege/NPrivilege and Secure/NSecure Attributes
  * @{
  */
#define LL_HSEM_NSEC_PRIV    HSEM_R_PRIV                 /*!< NSecure and Privileged attribute  */
#define LL_HSEM_NSEC_NPRIV   0x0U                        /*!< NSecure and NPrivileged attribute */
#define LL_HSEM_SEC_PRIV     (HSEM_R_SEC  | HSEM_R_PRIV) /*!< Secure and Privileged attribute   */
#define LL_HSEM_SEC_NPRIV    HSEM_R_SEC                  /*!< Secure and NPrivileged attribute  */
/**
  * @}
  */

/** @defgroup HSEM_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_HSEM_ReadReg function
  * @{
  */

#define LL_HSEM_SEMAPHORE_0                HSEM_IER_ISE0
#define LL_HSEM_SEMAPHORE_1                HSEM_IER_ISE1
#define LL_HSEM_SEMAPHORE_2                HSEM_IER_ISE2
#define LL_HSEM_SEMAPHORE_3                HSEM_IER_ISE3
#define LL_HSEM_SEMAPHORE_4                HSEM_IER_ISE4
#define LL_HSEM_SEMAPHORE_5                HSEM_IER_ISE5
#define LL_HSEM_SEMAPHORE_6                HSEM_IER_ISE6
#define LL_HSEM_SEMAPHORE_7                HSEM_IER_ISE7
#define LL_HSEM_SEMAPHORE_8                HSEM_IER_ISE8
#define LL_HSEM_SEMAPHORE_9                HSEM_IER_ISE9
#define LL_HSEM_SEMAPHORE_10               HSEM_IER_ISE10
#define LL_HSEM_SEMAPHORE_11               HSEM_IER_ISE11
#define LL_HSEM_SEMAPHORE_12               HSEM_IER_ISE12
#define LL_HSEM_SEMAPHORE_13               HSEM_IER_ISE13
#define LL_HSEM_SEMAPHORE_14               HSEM_IER_ISE14
#define LL_HSEM_SEMAPHORE_15               HSEM_IER_ISE15
#define LL_HSEM_SEMAPHORE_ALL              0x0000FFFFU
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup HSEM_LL_Exported_Macros HSEM Exported Macros
  * @{
  */

/** @defgroup HSEM_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in HSEM register
  * @param  __INSTANCE__ HSEM Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_HSEM_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in HSEM register
  * @param  __INSTANCE__ HSEM Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_HSEM_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSEM_LL_Exported_Functions HSEM Exported Functions
  * @{
  */

/** @defgroup HSEM_LL_EF_Data_Management Data_Management
  * @{
  */


/**
  * @brief  Return 1 if the semaphore is locked, else return 0.
  * @rmtoll R            LOCK          LL_HSEM_IsSemaphoreLocked
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsSemaphoreLocked(const HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return ((READ_BIT(HSEMx->R[Semaphore], HSEM_R_LOCK) == (HSEM_R_LOCK_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Get core id.
  * @rmtoll R            LOCKID        LL_HSEM_GetCoreId
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_HSEM_LOCKID_NONE
  *         @arg @ref LL_HSEM_LOCKID_CPU1
  */
__STATIC_INLINE uint32_t LL_HSEM_GetCoreId(const HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return (uint32_t)(READ_BIT(HSEMx->R[Semaphore], HSEM_R_LOCKID_Msk));
}

/**
  * @brief  Get process id.
  * @rmtoll R            PROCID        LL_HSEM_GetProcessId
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @retval Process number. Value between Min_Data=0 and Max_Data=255
  */
__STATIC_INLINE uint32_t LL_HSEM_GetProcessId(const HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return (uint32_t)(READ_BIT(HSEMx->R[Semaphore], HSEM_R_PROCID_Msk));
}

/**
  * @brief  Get the lock by writing in R register.
  * @note The R register has to be read to determined if the lock is taken.
  * @rmtoll R            LOCK          LL_HSEM_SetLock
  * @rmtoll R            LOCKID        LL_HSEM_SetLock
  * @rmtoll R            PROCID        LL_HSEM_SetLock
  * @rmtoll R            SEC           LL_HSEM_SetLock
  * @rmtoll R            PRIV          LL_HSEM_SetLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @param  process Process id. Value between Min_Data=0 and Max_Data=255
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetLock(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t process, uint32_t attribute)
{
  WRITE_REG(HSEMx->R[Semaphore], (HSEM_R_LOCK | LL_HSEM_LOCKID | process | attribute));
}

/**
  * @brief  Get the lock with 2-step lock.
  * @rmtoll R            LOCK          LL_HSEM_2StepLock
  * @rmtoll R            LOCKID        LL_HSEM_2StepLock
  * @rmtoll R            PROCID        LL_HSEM_2StepLock
  * @rmtoll R            SEC           LL_HSEM_2StepLock
  * @rmtoll R            PRIV          LL_HSEM_2StepLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @param  process Process id. Value between Min_Data=0 and Max_Data=255
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval 1 lock fail, 0 lock successful or already locked by same process and core
  */
__STATIC_INLINE uint32_t LL_HSEM_2StepLock(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t process, uint32_t attribute)
{
  WRITE_REG(HSEMx->R[Semaphore], (HSEM_R_LOCK | LL_HSEM_LOCKID | process | attribute));
  return ((HSEMx->R[Semaphore] != (HSEM_R_LOCK | LL_HSEM_LOCKID | process | attribute)) ? 1UL : 0UL);
}

/**
  * @brief  Get the lock with 1-step lock.
  * @rmtoll RLR          LOCK          LL_HSEM_1StepLock
  * @rmtoll RLR          LOCKID        LL_HSEM_1StepLock
  * @rmtoll RLR          PROCID        LL_HSEM_1StepLock
  * @rmtoll RLR          SEC           LL_HSEM_1StepLock
  * @rmtoll RLR          PRIV          LL_HSEM_1StepLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval 1 lock fail, 0 lock successful or already locked by same core
  */
__STATIC_INLINE uint32_t LL_HSEM_1StepLock(const HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t attribute)
{
  return ((HSEMx->RLR[Semaphore] != (HSEM_RLR_LOCK | LL_HSEM_LOCKID | attribute)) ? 1UL : 0UL);
}

/**
  * @brief  Release the lock of the semaphore.
  * @note In case of LL_HSEM_1StepLock usage to lock a semaphore, the process is 0.
  * @rmtoll R            LOCK          LL_HSEM_ReleaseLock
  * @rmtoll R            SEC           LL_HSEM_ReleaseLock
  * @rmtoll R            PRIV          LL_HSEM_ReleaseLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @param  process Process number. Value between Min_Data=0 and Max_Data=255
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ReleaseLock(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t process, uint32_t attribute)
{
  WRITE_REG(HSEMx->R[Semaphore], (LL_HSEM_LOCKID | process | attribute));
}

/**
  * @brief  Get the lock status of the semaphore.
  * @rmtoll R            LOCK          LL_HSEM_GetStatus
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=31
  * @retval 0 semaphore is free, 1 semaphore is locked  */
__STATIC_INLINE uint32_t LL_HSEM_GetStatus(const HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return ((HSEMx->R[Semaphore] != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Set the key.
  * @rmtoll KEYR         KEY           LL_HSEM_SetKey
  * @param  HSEMx HSEM Instance.
  * @param  key Key value.
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetKey(HSEM_TypeDef *HSEMx, uint32_t key)
{
  WRITE_REG(HSEMx->KEYR, key << HSEM_KEYR_KEY_Pos);
}

/**
  * @brief  Get the key.
  * @rmtoll KEYR         KEY           LL_HSEM_GetKey
  * @param  HSEMx HSEM Instance.
  * @retval key to unlock all semaphore from the same core
  */
__STATIC_INLINE uint32_t LL_HSEM_GetKey(const HSEM_TypeDef *HSEMx)
{
  return (uint32_t)(READ_BIT(HSEMx->KEYR, HSEM_KEYR_KEY) >> HSEM_KEYR_KEY_Pos);
}

/**
  * @brief  Release all semaphore with the same core id.
  * @rmtoll CR           KEY           LL_HSEM_ResetAllLock
  * @param  HSEMx HSEM Instance.
  * @param  key Key value.
  * @param  core This parameter can be one of the following values:
  *         @arg @ref LL_HSEM_LOCKID_CPU1
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ResetAllLock(HSEM_TypeDef *HSEMx, uint32_t key, uint32_t core, uint32_t attribute)
{
  WRITE_REG(HSEMx->CR, (key << HSEM_CR_KEY_Pos) | core | attribute);
}

#if  defined(HSEM_SECCFGR_SEC0)
/**
  * @brief  Set semaphore accessible by secure only.
  * @rmtoll SECCFGR           SEC           LL_HSEM_SetSemaphoreSecure
  * @param  HSEMx HSEM Instance.
  * @param  SemMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetSemaphoreSecure(HSEM_TypeDef *HSEMx, uint32_t SemMask)
{
  SET_BIT(HSEMx->SECCFGR, SemMask);
}

/**
  * @brief  Set semaphore accessible by secure and non-secure.
  * @rmtoll SECCFGR           SEC           LL_HSEM_SetSemaphoreNonSecure
  * @param  HSEMx HSEM Instance.
  * @param  SemMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetSemaphoreNonSecure(HSEM_TypeDef *HSEMx, uint32_t SemMask)
{
  CLEAR_BIT(HSEMx->SECCFGR, SemMask);
}

/**
  * @brief  Get security attribute of semaphore.
  * @rmtoll SECCFGR           SEC           LL_HSEM_GetSemaphoreSecure
  * @param  HSEMx HSEM Instance.
  * @retval Security attribute of semaphores
  */
__STATIC_INLINE uint32_t LL_HSEM_GetSemaphoreSecure(const HSEM_TypeDef *HSEMx)
{
  return HSEMx->SECCFGR;
}

/**
  * @brief  Set semaphore accessible by privilege only.
  * @rmtoll PRIVCFGR           PRIV           LL_HSEM_SetSemaphorePrivilege
  * @param  HSEMx HSEM Instance.
  * @param  SemMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetSemaphorePrivilege(HSEM_TypeDef *HSEMx, uint32_t SemMask)
{
  SET_BIT(HSEMx->PRIVCFGR, SemMask);
}

/**
  * @brief  Set semaphore accessible by privilege and non-privilege.
  * @rmtoll PRIVCFGR           PRIV           LL_HSEM_SetSemaphoreNonPrivilege
  * @param  HSEMx HSEM Instance.
  * @param  SemMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetSemaphoreNonPrivilege(HSEM_TypeDef *HSEMx, uint32_t SemMask)
{
  CLEAR_BIT(HSEMx->PRIVCFGR, SemMask);
}

/**
  * @brief  Get privilege attribute of semaphore.
  * @rmtoll PRIVCFGR           PRIV           LL_HSEM_GetSemaphorePrivilege
  * @param  HSEMx HSEM Instance.
  * @retval Privilege attribute of semaphores
  */
__STATIC_INLINE uint32_t LL_HSEM_GetSemaphorePrivilege(const HSEM_TypeDef *HSEMx)
{
  return HSEMx->PRIVCFGR;
}

#endif
/**
  * @}
  */

/** @defgroup HSEM_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable interrupt.
  * @rmtoll IER         ISEM          LL_HSEM_EnableIT_IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_EnableIT_IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(HSEMx->SIER, SemaphoreMask);
#else
  SET_BIT(HSEMx->IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Disable interrupt.
  * @rmtoll IER          ISEM          LL_HSEM_DisableIT_IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_DisableIT_IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(HSEMx->SIER, SemaphoreMask);
#else
  CLEAR_BIT(HSEMx->IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Check if interrupt is enabled.
  * @rmtoll IER          ISEM          LL_HSEM_IsEnabledIT_IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsEnabledIT_IER(const HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SIER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->IER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}


/**
  * @}
  */

/** @defgroup HSEM_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear interrupt status.
  * @rmtoll ICR         ISEM          LL_HSEM_ClearFlag_ICR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ClearFlag_ICR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  WRITE_REG(HSEMx->SICR, SemaphoreMask);
#else
  WRITE_REG(HSEMx->ICR, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from ISR register.
  * @rmtoll ISR         ISEM          LL_HSEM_IsActiveFlag_ISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_ISR(const HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->ISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from MISR register.
  * @rmtoll MISR        ISEM          LL_HSEM_IsActiveFlag_MISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_MISR(const HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SMISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->MISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(HSEM) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32WBAxx_LL_HSEM_H */
