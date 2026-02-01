/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL Extended module.
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
#ifndef STM32WBAxx_HAL_FLASH_EX_H
#define STM32WBAxx_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Constants FLASH Extended Private Constants
  * @{
  */
#if defined(FLASH_SECBBR1_SECBB0) || defined(FLASH_PRIVBBR1_PRIVBB0) || defined(FLASH_SECBB1R1_SECBB0) || defined(FLASH_PRIVBB1R1_PRIVBB0)
#define FLASH_BLOCKBASED_NB_REG (4U) /*!< Number of block-based registers available */
#endif /* FLASH_SECBBR1_SECBB0 || FLASH_PRIVBBR1_PRIVBB0 */
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Types FLASH Exported Types
  * @{
  */

#if defined(FLASH_SECBBR1_SECBB0) || defined(FLASH_PRIVBBR1_PRIVBB0) || defined(FLASH_SECBB1R1_SECBB0) || defined(FLASH_PRIVBB1R1_PRIVBB0)
/**
  * @brief  FLASHEx Block-based attributes structure definition
  */
typedef struct
{
#if defined(FLASH_DBANK_SUPPORT)
  uint32_t Bank;                                        /*!< Selection of the associated bank of Block-based Area.
                                                             This parameter must be a value of @ref FLASH_Banks */
#endif /* FLASH_DBANK_SUPPORT */
  uint32_t BBAttributesType;                            /*!< Block-Based Attributes type.
                                                             This parameter must be a value of @ref FLASHEx_BB_Attributes */
  uint32_t BBAttributes_array[FLASH_BLOCKBASED_NB_REG]; /*!< Each bit specifies the block-based attribute configuration of a page:
                                                             0 means page non-protected, 1 means page protected.
                                                             Protection (secure or privilege) depends on BBAttributesType value */
} FLASH_BBAttributesTypeDef;
#endif /* FLASH_SECBBR1_SECBB0 || FLASH_PRIVBBR1_PRIVBB0 */

#if defined(FLASH_SECHDPEXTR_HDP_PEXT)
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  FLASHEx Extended secure hide area structure definition
  */
typedef struct
{
  uint32_t Bank;            /*!< Selection of the associated bank of extended secure hide area.
                                 This parameter must be a value of @ref FLASH_Banks */
  uint32_t NbPages;         /*!< Number of pages of the extended secure hide area.
                                 This parameter must be a value between 0 and (WM end page - WM start page) if no HDP,
                                 or between 0 and (WM end page - HDP end page) if HDP enabled */
} FLASH_HDPExtensionTypeDef;
#endif /* __ARM_FEATURE_CMSE */
#endif /* FLASH_SECHDPEXTR_HDP_PEXT */

/**
  * @brief  FLASHEx Operation structure definition
  */
typedef struct
{
  uint32_t OperationType;    /*!< Flash operation Type.
                                  This parameter must be a value of @ref FLASHEx_Operation_Type */
  uint32_t FlashArea;        /*!< Flash operation memory area.
                                  This parameter must be a value of FLASH_Operation_Area */
  uint32_t Address;          /*!< Flash operation Address offset.
                                  This parameter is given by bank, and must be a value between 0x0 and 0xFFFF0 */
} FLASH_OperationTypeDef;

/**
  * @brief  FLASH ECC information structure definition
  */
typedef struct
{
  uint32_t Area;        /*!< Area from which an ECC was detected.
                             This parameter can be a value of @ref FLASHEx_ECC_Area  */
  uint32_t Address;     /*!< Flash address from which en ECC error was detected.
                             This parameter must be a value between begin address and end address of the Flash */
  uint32_t MasterID;    /*!< Master that initiated transfer on which error was detected
                             This parameter can be a value of @ref FLASHEx_ECC_Master */
} FLASH_EccInfoTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Constants FLASH Extended Exported Constants
  * @{
  */

#if defined(FLASH_PRIVCFGR_SPRIV)
/** @defgroup FLASHEx_PRIV_MODE_CFG FLASH privilege mode configuration
  * @{
  */
#define FLASH_NSPRIV_GRANTED  0x00000000U           /*!< access to non-secure Flash registers is granted to privileged or unprivileged access */
#define FLASH_NSPRIV_DENIED   FLASH_PRIVCFGR_NSPRIV /*!< access to non-secure Flash registers is denied to non-privilege access */

#define FLASH_SPRIV_GRANTED   0x00000000U           /*!< access to secure Flash registers is granted to privileged or unprivileged access */
#define FLASH_SPRIV_DENIED    FLASH_PRIVCFGR_SPRIV  /*!< access to secure Flash registers is denied to non-privilege access */
/**
  * @}
  */
#endif /* FLASH_PRIVCFGR_SPRIV */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup FLASHEx_SEC_INVERSION_CFG FLASH security inversion configuration
  * @{
  */
#define FLASH_INV_DISABLE    0x00000000U       /*!< Security state of Flash is not inverted */
#define FLASH_INV_ENABLE     FLASH_SECCR1_INV  /*!< Security state of Flash is inverted */
/**
  * @}
  */
#endif /* __ARM_FEATURE_CMSE */

/** @defgroup FLASHEx_LPM_CFG FLASH LPM configuration
  * @{
  */
#define FLASH_LPM_DISABLE      0x00000000U    /*!< Flash is in normal read mode */
#define FLASH_LPM_ENABLE       FLASH_ACR_LPM  /*!< Flash is in low-power read mode */
/**
  * @}
  */

#if defined(FLASH_SECBBR1_SECBB0) || defined(FLASH_PRIVBBR1_PRIVBB0) || defined(FLASH_SECBB1R1_SECBB0) || defined(FLASH_PRIVBB1R1_PRIVBB0)
/** @defgroup FLASHEx_BB_Attributes FLASH Block-Based Attributes
  * @{
  */
#define FLASH_BB_SEC         0x00000001U       /*!< Flash Block-Based Security Attributes */
#define FLASH_BB_PRIV        0x00000002U       /*!< Flash Block-Based Privilege Attributes */
/**
  * @}
  */
#endif /* FLASH_SECBBR1_SECBB0 || FLASH_PRIVBBR1_PRIVBB0 */

/** @defgroup FLASHEx_Operation_Type FLASH Operation Type
  * @{
  */
#define FLASH_OPERATION_TYPE_NONE         00000000U                                     /*!< No Flash operation      */
#if defined(FLASH_DOUBLEWORD_SUPPORT)
#define FLASH_OPERATION_TYPE_DOUBLEWORD   FLASH_OPSR_CODE_OP_0                          /*!< Single write operation  */
#else /* FLASH_DOUBLEWORD_SUPPORT */
#define FLASH_OPERATION_TYPE_QUADWORD     FLASH_OPSR_CODE_OP_0                          /*!< Single write operation  */
#endif /* FLASH_DOUBLEWORD_SUPPORT */
#define FLASH_OPERATION_TYPE_BURST        FLASH_OPSR_CODE_OP_1                          /*!< Burst write operation   */
#define FLASH_OPERATION_TYPE_PAGEERASE    (FLASH_OPSR_CODE_OP_1 | FLASH_OPSR_CODE_OP_0) /*!< Page erase operation    */
#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_OPERATION_TYPE_BANKERASE    FLASH_OPSR_CODE_OP_2                          /*!< Bank erase operation    */
#endif /* FLASH_DBANK_SUPPORT */
#define FLASH_OPERATION_TYPE_MASSERASE    (FLASH_OPSR_CODE_OP_2 | FLASH_OPSR_CODE_OP_0) /*!< Mass erase operation    */
#define FLASH_OPERATION_TYPE_OPTIONCHANGE (FLASH_OPSR_CODE_OP_2 | FLASH_OPSR_CODE_OP_1) /*!< Option change operation */
/**
  * @}
  */

#if defined(FLASH_SECHDPEXTR_HDP_PEXT)
/** @defgroup FLASH_ExtHDP_Protection FLASH Extended HDP Area protection type
  * @{
  */
#define FLASH_EXTHDP_NO_PROTECTION           0xA3U       /*!< Access to bits configuration and area allowed        */
#define FLASH_EXTHDP_ONLY_ACCESS_PROTECTED   0x5CU       /*!< Access to area denied and bits configuration allowed */
#define FLASH_EXTHDP_ALL_PROTECTED           0x00U       /*!< Access to bits configuration and area denied         */
/**
  * @}
  */
#endif /* FLASH_SECHDPEXTR_HDP_PEXT */

/** @defgroup FLASHEx_ECC_Area FLASH ECC Area
  * @{
  */
#define FLASH_ECC_AREA_USER_BANK1  0x00000000U          /*!< FLASH bank 1 area */
#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_ECC_AREA_USER_BANK2  FLASH_ECCR_BK_ECC    /*!< FLASH bank 2 area */
#endif /* FLASH_DBANK_SUPPORT */
#define FLASH_ECC_AREA_SYSTEM      FLASH_ECCR_SYSF_ECC  /*!< System FLASH area */
/**
  * @}
  */

/** @defgroup FLASHEx_ECC_Master FLASH ECC Master
  * @{
  */
#define FLASH_ECC_MASTER_CPU1     0x00000000U  /*!< ECC error occurs on a CPU1 transaction */
/**
  * @}
  */

/** @defgroup FLASHEx_Suspend_Request FLASH Suspend Request
  * @{
  */
#if defined(FLASH_DBANK_SUPPORT)
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_SUSPEND_PROGRAM             (FLASH_SECCR2_PS1 | FLASH_SECCR2_PS2) /*!< Suspend all program requests */
#define FLASH_SUSPEND_BANK1_PROGRAM       FLASH_SECCR2_PS1                      /*!< Suspend all program requests in bank 1 */
#define FLASH_SUSPEND_BANK2_PROGRAM       FLASH_SECCR2_PS2                      /*!< Suspend all program requests in bank 2 */
#define FLASH_SUSPEND_ERASE               (FLASH_SECCR2_ES1 | FLASH_SECCR2_ES2) /*!< Suspend all erase requests */
#define FLASH_SUSPEND_BANK1_ERASE         FLASH_SECCR2_ES1                      /*!< Suspend all erase requests in bank 1 */
#define FLASH_SUSPEND_BANK2_ERASE         FLASH_SECCR2_ES2                      /*!< Suspend all erase requests in bank 2 */
#define FLASH_SUSPEND_PROGRAM_ERASE       (FLASH_SECCR2_PS1 | FLASH_SECCR2_ES1 | \
                                           FLASH_SECCR2_PS2 | FLASH_SECCR2_ES2) /*!< Suspend all requests (program and erase) */
#define FLASH_SUSPEND_BANK1_PROGRAM_ERASE (FLASH_SECCR2_PS1 | FLASH_SECCR2_ES1) /*!< Suspend all requests in bank 1 (program and erase) */
#define FLASH_SUSPEND_BANK2_PROGRAM_ERASE (FLASH_SECCR2_PS2 | FLASH_SECCR2_ES2) /*!< Suspend all requests in bank 2 (program and erase) */
#else
#define FLASH_SUSPEND_PROGRAM             (FLASH_NSCR2_PS1 | FLASH_NSCR2_PS2) /*!< Suspend all program requests */
#define FLASH_SUSPEND_BANK1_PROGRAM       FLASH_NSCR2_PS1                     /*!< Suspend all program requests in bank 1 */
#define FLASH_SUSPEND_BANK2_PROGRAM       FLASH_NSCR2_PS2                     /*!< Suspend all program requests in bank 2 */
#define FLASH_SUSPEND_ERASE               (FLASH_NSCR2_ES1 | FLASH_NSCR2_ES2) /*!< Suspend all erase requests */
#define FLASH_SUSPEND_BANK1_ERASE         FLASH_NSCR2_ES1                     /*!< Suspend all erase requests in bank 1 */
#define FLASH_SUSPEND_BANK2_ERASE         FLASH_NSCR2_ES2                     /*!< Suspend all erase requests in bank 2 */
#define FLASH_SUSPEND_PROGRAM_ERASE       (FLASH_NSCR2_PS1 | FLASH_NSCR2_ES1 | \
                                           FLASH_NSCR2_PS2 | FLASH_NSCR2_ES2) /*!< Suspend all requests (program and erase) */
#define FLASH_SUSPEND_BANK1_PROGRAM_ERASE (FLASH_NSCR2_PS1 | FLASH_NSCR2_ES1) /*!< Suspend all requests in bank 1 (program and erase) */
#define FLASH_SUSPEND_BANK2_PROGRAM_ERASE (FLASH_NSCR2_PS2 | FLASH_NSCR2_ES2) /*!< Suspend all requests in bank 2 (program and erase) */
#endif /* __ARM_FEATURE_CMSE */
#else /* FLASH_DBANK_SUPPORT */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_SUSPEND_PROGRAM             FLASH_SECCR2_PS                     /*!< Suspend all program requests */
#define FLASH_SUSPEND_ERASE               FLASH_SECCR2_ES                     /*!< Suspend all erase requests */
#define FLASH_SUSPEND_PROGRAM_ERASE       (FLASH_SECCR2_PS | FLASH_SECCR2_ES) /*!< Suspend all requests (program and erase) */
#else
#define FLASH_SUSPEND_PROGRAM             FLASH_NSCR2_PS                      /*!< Suspend all program requests */
#define FLASH_SUSPEND_ERASE               FLASH_NSCR2_ES                      /*!< Suspend all erase requests */
#define FLASH_SUSPEND_PROGRAM_ERASE       (FLASH_NSCR2_PS | FLASH_NSCR2_ES)   /*!< Suspend all requests (program and erase) */
#endif /* __ARM_FEATURE_CMSE */
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */

/** @defgroup FLASHEx_Allow_Request FLASH Allow Request
  * @{
  */
#if defined(FLASH_DBANK_SUPPORT)
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_ALLOW_PROGRAM             (FLASH_SECCR2_PS1 | FLASH_SECCR2_PS2) /*!< Suspend all program requests */
#define FLASH_ALLOW_BANK1_PROGRAM       FLASH_SECCR2_PS1                      /*!< Suspend all program requests in bank 1 */
#define FLASH_ALLOW_BANK2_PROGRAM       FLASH_SECCR2_PS2                      /*!< Suspend all program requests in bank 2 */
#define FLASH_ALLOW_ERASE               (FLASH_SECCR2_ES1 | FLASH_SECCR2_ES2) /*!< Suspend all erase requests */
#define FLASH_ALLOW_BANK1_ERASE         FLASH_SECCR2_ES1                      /*!< Suspend all erase requests in bank 1 */
#define FLASH_ALLOW_BANK2_ERASE         FLASH_SECCR2_ES2                      /*!< Suspend all erase requests in bank 2 */
#define FLASH_ALLOW_PROGRAM_ERASE       (FLASH_SECCR2_PS1 | FLASH_SECCR2_ES1 | \
                                         FLASH_SECCR2_PS2 | FLASH_SECCR2_ES2) /*!< Suspend all requests (program and erase) */
#define FLASH_ALLOW_BANK1_PROGRAM_ERASE (FLASH_SECCR2_PS1 | FLASH_SECCR2_ES1) /*!< Suspend all requests in bank 1 (program and erase) */
#define FLASH_ALLOW_BANK2_PROGRAM_ERASE (FLASH_SECCR2_PS2 | FLASH_SECCR2_ES2) /*!< Suspend all requests in bank 2 (program and erase) */
#else
#define FLASH_ALLOW_PROGRAM             (FLASH_NSCR2_PS1 | FLASH_NSCR2_PS2) /*!< Suspend all program requests */
#define FLASH_ALLOW_BANK1_PROGRAM       FLASH_NSCR2_PS1                     /*!< Suspend all program requests in bank 1 */
#define FLASH_ALLOW_BANK2_PROGRAM       FLASH_NSCR2_PS2                     /*!< Suspend all program requests in bank 2 */
#define FLASH_ALLOW_ERASE               (FLASH_NSCR2_ES1 | FLASH_NSCR2_ES2) /*!< Suspend all erase requests */
#define FLASH_ALLOW_BANK1_ERASE         FLASH_NSCR2_ES1                     /*!< Suspend all erase requests in bank 1 */
#define FLASH_ALLOW_BANK2_ERASE         FLASH_NSCR2_ES2                     /*!< Suspend all erase requests in bank 2 */
#define FLASH_ALLOW_PROGRAM_ERASE       (FLASH_NSCR2_PS1 | FLASH_NSCR2_ES1 | \
                                         FLASH_NSCR2_PS2 | FLASH_NSCR2_ES2) /*!< Suspend all requests (program and erase) */
#define FLASH_ALLOW_BANK1_PROGRAM_ERASE (FLASH_NSCR2_PS1 | FLASH_NSCR2_ES1) /*!< Suspend all requests in bank 1 (program and erase) */
#define FLASH_ALLOW_BANK2_PROGRAM_ERASE (FLASH_NSCR2_PS2 | FLASH_NSCR2_ES2) /*!< Suspend all requests in bank 2 (program and erase) */
#endif /* __ARM_FEATURE_CMSE */
#else /* FLASH_DBANK_SUPPORT */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_ALLOW_PROGRAM               FLASH_SECCR2_PS                     /*!< Allow all program requests */
#define FLASH_ALLOW_ERASE                 FLASH_SECCR2_ES                     /*!< Allow all erase requests */
#define FLASH_ALLOW_PROGRAM_ERASE         (FLASH_SECCR2_PS | FLASH_SECCR2_ES) /*!< Allow all requests (program and erase) */
#else
#define FLASH_ALLOW_PROGRAM               FLASH_NSCR2_PS                      /*!< Allow all program requests */
#define FLASH_ALLOW_ERASE                 FLASH_NSCR2_ES                      /*!< Allow all erase requests */
#define FLASH_ALLOW_PROGRAM_ERASE         (FLASH_NSCR2_PS | FLASH_NSCR2_ES)   /*!< Allow all requests (program and erase) */
#endif /* __ARM_FEATURE_CMSE */
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/* Extended Program operation functions  *************************************/
/** @addtogroup FLASHEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(const FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
#if defined(FLASH_SECBBR1_SECBB0) || defined(FLASH_PRIVBBR1_PRIVBB0) || defined(FLASH_SECBB1R1_SECBB0) || defined(FLASH_PRIVBB1R1_PRIVBB0)
HAL_StatusTypeDef HAL_FLASHEx_ConfigBBAttributes(const FLASH_BBAttributesTypeDef *pBBAttributes);
void              HAL_FLASHEx_GetConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes);
#endif /* FLASH_SECBBR1_SECBB0 || FLASH_PRIVBBR1_PRIVBB0 */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
void              HAL_FLASHEx_EnableSecHideProtection(uint32_t Banks);
#if defined(FLASH_SECHDPEXTR_HDP_PEXT)
HAL_StatusTypeDef HAL_FLASHEx_ConfigHDPExtension(FLASH_HDPExtensionTypeDef *pHDPExtension);
void              HAL_FLASHEx_GetConfigHDPExtension(FLASH_HDPExtensionTypeDef *pHDPExtension);
void              HAL_FLASHEx_EnableHDPExtensionProtection(uint32_t Banks, uint32_t ProtectionType);
#endif /* FLASH_SECHDPEXTR_HDP_PEXT */
#endif /* __ARM_FEATURE_CMSE */
#if defined(FLASH_OEMKEYSR_OEM1KEYCRC)
void              HAL_FLASHEx_GetRDPKeyCRC(uint32_t RDPKeyType, uint32_t *CRCKeyValue);
#endif /* FLASH_OEMKEYSR_OEM1KEYCRC */
/**
  * @}
  */

/** @addtogroup FLASHEx_Exported_Functions_Group2
  * @{
  */
void              HAL_FLASHEx_SuspendOperation(uint32_t Request);
void              HAL_FLASHEx_AllowOperation(uint32_t Request);
uint32_t          HAL_FLASHEx_IsOperationSuspended(void);
#if defined(FLASH_PRIVCFGR_SPRIV)
void              HAL_FLASHEx_ConfigPrivMode(uint32_t PrivMode);
uint32_t          HAL_FLASHEx_GetPrivMode(void);
#endif /* FLASH_PRIVCFGR_SPRIV */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_FLASHEx_ConfigSecInversion(uint32_t SecInvState);
uint32_t          HAL_FLASHEx_GetSecInversion(void);
#endif /* __ARM_FEATURE_CMSE */
#if defined(FLASH_DBANK_SUPPORT)
HAL_StatusTypeDef HAL_FLASHEx_EnablePowerDown(uint32_t Banks);
#else /* FLASH_DBANK_SUPPORT */
HAL_StatusTypeDef HAL_FLASHEx_EnablePowerDown(void);
#endif /* FLASH_DBANK_SUPPORT */
HAL_StatusTypeDef HAL_FLASHEx_ConfigLowPowerRead(uint32_t ConfigLPM);
uint32_t          HAL_FLASHEx_GetLowPowerRead(void);
void              HAL_FLASHEx_GetOperation(FLASH_OperationTypeDef *pFlashOperation);
/**
  * @}
  */

/** @addtogroup FLASHEx_Exported_Functions_Group3
  * @{
  */
void              HAL_FLASHEx_EnableEccCorrectionInterrupt(void);
void              HAL_FLASHEx_DisableEccCorrectionInterrupt(void);
void              HAL_FLASHEx_GetEccInfo(FLASH_EccInfoTypeDef *pData);
void              HAL_FLASHEx_ECCD_IRQHandler(void);
__weak void       HAL_FLASHEx_EccDetectionCallback(void);
__weak void       HAL_FLASHEx_EccCorrectionCallback(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private function ----------------------------------------------------------*/
/** @addtogroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
#if defined(FLASH_DBANK_SUPPORT)
void FLASH_PageErase(uint32_t Page, uint32_t Banks);
#else /* FLASH_DBANK_SUPPORT */
void FLASH_PageErase(uint32_t Page);
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Macros FLASH Private Macros
  *  @{
  */
#define IS_FLASH_BB_EXCLUSIVE(CFG)         (((CFG) == FLASH_BB_SEC)  || \
                                            ((CFG) == FLASH_BB_PRIV))

#define IS_FLASH_CFGPRIVMODE(CFG)          (((CFG) & 0xFFFFFFFCU) == 0U)

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_CFGSECINV(CFG)            (((CFG) == FLASH_INV_DISABLE) || \
                                            ((CFG) == FLASH_INV_ENABLE))
#endif /* __ARM_FEATURE_CMSE */

#define IS_FLASH_CFGLPM(CFG)               (((CFG) == FLASH_LPM_DISABLE) || \
                                            ((CFG) == FLASH_LPM_ENABLE))

#if defined(FLASH_SECHDPEXTR_HDP_PEXT)
#define IS_FLASH_EXTHDP_PROTECTION(CFG)    (((CFG) == FLASH_EXTHDP_ONLY_ACCESS_PROTECTED) || \
                                            ((CFG) == FLASH_EXTHDP_ALL_PROTECTED))
#endif /* FLASH_SECHDPEXTR_HDP_PEXT */

#if defined(FLASH_DBANK_SUPPORT)
#define IS_FLASH_SUSPEND_REQ(VALUE)        (((VALUE) == FLASH_SUSPEND_PROGRAM)             || \
                                            ((VALUE) == FLASH_SUSPEND_BANK1_PROGRAM)       || \
                                            ((VALUE) == FLASH_SUSPEND_BANK2_PROGRAM)       || \
                                            ((VALUE) == FLASH_SUSPEND_ERASE)               || \
                                            ((VALUE) == FLASH_SUSPEND_BANK1_ERASE)         || \
                                            ((VALUE) == FLASH_SUSPEND_BANK2_ERASE)         || \
                                            ((VALUE) == FLASH_SUSPEND_PROGRAM_ERASE)       || \
                                            ((VALUE) == FLASH_SUSPEND_BANK1_PROGRAM_ERASE) || \
                                            ((VALUE) == FLASH_SUSPEND_BANK2_PROGRAM_ERASE))

#define IS_FLASH_ALLOW_REQ(VALUE)          (((VALUE) == FLASH_ALLOW_PROGRAM)             || \
                                            ((VALUE) == FLASH_ALLOW_BANK1_PROGRAM)       || \
                                            ((VALUE) == FLASH_ALLOW_BANK2_PROGRAM)       || \
                                            ((VALUE) == FLASH_ALLOW_ERASE)               || \
                                            ((VALUE) == FLASH_ALLOW_BANK1_ERASE)         || \
                                            ((VALUE) == FLASH_ALLOW_BANK2_ERASE)         || \
                                            ((VALUE) == FLASH_ALLOW_PROGRAM_ERASE)       || \
                                            ((VALUE) == FLASH_ALLOW_BANK1_PROGRAM_ERASE) || \
                                            ((VALUE) == FLASH_ALLOW_BANK2_PROGRAM_ERASE))
#else /* FLASH_DBANK_SUPPORT */
#define IS_FLASH_SUSPEND_REQ(VALUE)        (((VALUE) == FLASH_SUSPEND_PROGRAM) || \
                                            ((VALUE) == FLASH_SUSPEND_ERASE)   || \
                                            ((VALUE) == FLASH_SUSPEND_PROGRAM_ERASE))

#define IS_FLASH_ALLOW_REQ(VALUE)          (((VALUE) == FLASH_ALLOW_PROGRAM) || \
                                            ((VALUE) == FLASH_ALLOW_ERASE)   || \
                                            ((VALUE) == FLASH_ALLOW_PROGRAM_ERASE))
#endif /* FLASH_DBANK_SUPPORT */
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

#endif /* STM32WBAxx_HAL_FLASH_EX_H */
