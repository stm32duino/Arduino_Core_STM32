/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_flash_ex.c
  * @author  MCD Application Team
  * @brief   Extended FLASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the FLASH extended peripheral:
  *           + Extended programming operations functions
  *
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
 @verbatim
 ==============================================================================
                   ##### Flash Extended features #####
 ==============================================================================

  [..] Comparing to other previous devices, the FLASH interface for STM32WBAxx
       devices contains the following additional features

       (+) Capacity up to 2 Mbyte
       (+) Watermark-based secure area including the secure hide areas
       (+) Block-based secure pages

                        ##### How to use this driver #####
 ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory
       of all STM32WBAxx devices. It includes:
      (#) Flash Memory Erase functions:
           (++) Lock and Unlock the FLASH interface using HAL_FLASH_Unlock() and
                HAL_FLASH_Lock() functions
           (++) Erase function: page Erase and Mass Erase
           (++) There are two modes of erase :
             (+++) Polling Mode using HAL_FLASHEx_Erase()
             (+++) Interrupt Mode using HAL_FLASHEx_Erase_IT()

      (#) Option Bytes Programming function: Use HAL_FLASHEx_OBProgram() to:
        (++) Configure the write protection for each area
        (++) Set the Read protection Level
        (++) Program the user Option Bytes
        (++) Configure the watermark security for each area including the secure hide areas
        (++) Configure the boot lock (BOOT_LOCK)
        (++) Configure the Boot addresses

      (#) Get Option Bytes Configuration function: Use HAL_FLASHEx_OBGetConfig() to:
        (++) Get the value of a write protection area
        (++) Know if the read protection is activated
        (++) Get the value of the user Option Bytes
        (++) Get the configuration of a watermark security area including the secure hide areas
        (++) Get the boot lock (BOOT_LOCK) configuration
        (++) Get the value of a boot address

      (#) Block-based secure / privilege area configuration function: Use HAL_FLASHEx_ConfigBBAttributes()
        (++) Bit-field allowing to secure or un-secure each page
        (++) Bit-field allowing to privilege or un-privilege each page

      (#) Get the block-based secure / privilege area configuration function: Use HAL_FLASHEx_GetBBSec()
        (++) Return the configuration of the block-based security and privilege for all the pages

      (#) Activation of the secure hide area function: Use HAL_FLASHEx_EnableSecHideProtection()
        (++) Deny the access to the secure hide area

      (#) Privilege mode configuration function: Use HAL_FLASHEx_ConfigPrivMode()
        (++) FLASH register can be protected against non-privilege accesses

      (#) Get the privilege mode configuration function: Use HAL_FLASHEx_GetPrivMode()
        (++) Return if the FLASH registers are protected against non-privilege accesses

      (#) Security inversion configuration function: Use HAL_FLASHEx_ConfigSecInversion()
        (++) FLASH secure state can be override

      (#) Get the security inversion configuration function: Use HAL_FLASHEx_GetSecInversion()
        (++) Return if FLASH secure state is override

      (#) Enable low-power mode function: Use HAL_FLASHEx_EnablePowerDown()
        (++) Enable low-power mode for Flash

      (#) Enable low-power read mode function: Use HAL_FLASHEx_ConfigLowPowerRead()
        (++) Enable low-power read mode for Flash memory

      (#) Get the low-power read mode configuration function: Use HAL_FLASHEx_GetLowPowerRead()
        (++) Return if FLASH is in low-power read mode or normal read mode

      (#) Get Flash operation function: Use HAL_FLASHEx_GetOperation()
        (++) Return information about the on-going Flash operation. After a
             system reset, return information about the interrupted Flash operation, if any.

 @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx FLASHEx
  * @brief FLASH Extended HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
#if defined(FLASH_DBANK_SUPPORT)
static void     FLASH_MassErase(uint32_t Banks);
#else /* FLASH_DBANK_SUPPORT */
static void     FLASH_MassErase(void);
#endif /* FLASH_DBANK_SUPPORT */
static void     FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRPEndOffset,
                                   FunctionalState WRPLock);
static void     FLASH_OB_RDPConfig(uint32_t RDPLevel);
static void     FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
static void     FLASH_OB_WMSECConfig(uint32_t WMSecConfig, uint32_t WMSecStartPage, uint32_t WMSecEndPage,
                                     uint32_t WMHDPEndPage);
static void     FLASH_OB_BootLockConfig(uint32_t BootLockConfig);
#endif /* __ARM_FEATURE_CMSE */
static void     FLASH_OB_BootAddrConfig(uint32_t BootAddrConfig, uint32_t BootAddr);
static void     FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t *WRPStartOffset, uint32_t *WRPEndOffset,
                                FunctionalState *WRPLock);
static uint32_t FLASH_OB_GetRDP(void);
static uint32_t FLASH_OB_GetUser(void);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
static void     FLASH_OB_GetWMSEC(uint32_t *WMSecConfig, uint32_t *WMSecStartPage, uint32_t *WMSecEndPage,
                                  uint32_t *WMHDPEndPage);
static uint32_t FLASH_OB_GetBootLock(void);
#endif /* __ARM_FEATURE_CMSE */
static void     FLASH_OB_GetBootAddr(uint32_t BootAddrConfig, uint32_t *BootAddr);
#if defined(FLASH_OEM1KEYR3_OEM1KEY)
static void     FLASH_OB_RDPKeyConfig(uint32_t RDPKeyType, uint32_t RDPKey1, uint32_t RDPKey2,
                                      uint32_t RDPKey3, uint32_t RDPKey4);
#else /* FLASH_OEM1KEYR3_OEM1KEY */
static void     FLASH_OB_RDPKeyConfig(uint32_t RDPKeyType, uint32_t RDPKey1, uint32_t RDPKey2);
#endif /* FLASH_OEM1KEYR3_OEM1KEY */
/**
  * @}
  */

/* Exported functions -------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Functions FLASH Extended Exported Functions
  * @{
  */

/** @defgroup FLASHEx_Exported_Functions_Group1 Extended IO operation functions
  *  @brief   Extended IO operation functions
  *
@verbatim
 ===============================================================================
                ##### Extended programming operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the Extended FLASH
    programming operations Operations.

@endverbatim
  * @{
  */

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages.
  * @note   Before any operation, it is possible to check there is no operation suspended
  *         by call HAL_FLASHEx_IsOperationSuspended()
  * @param[in]  pEraseInit Pointer to an @ref FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  *
  * @param[out]  PageError Pointer to variable that contains the configuration
  *         information on faulty page in case of error (0xFFFFFFFF means that all
  *         the pages have been correctly erased)
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(const FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status;
  uint32_t page_index;
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Verify that next operation can be proceed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Current operation type */
    pFlash.ProcedureOnGoing = pEraseInit->TypeErase;

    /* Access to SECCR1 or NSCR1 depends on operation type */
#if defined(FLASH_SECCR1_LOCK)
    reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR1) : &(FLASH_NS->NSCR1);
#else
    reg_cr = &(FLASH_NS->NSCR1);
#endif /* FLASH_SECCR1_LOCK */

    if ((pEraseInit->TypeErase & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEERASE_MASSERASE)
    {
      /* Mass erase to be done */
#if defined(FLASH_DBANK_SUPPORT)
      FLASH_MassErase(pEraseInit->Banks);
#else /* FLASH_DBANK_SUPPORT */
      FLASH_MassErase();
#endif /* FLASH_DBANK_SUPPORT */

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    }
    else
    {
      /*Initialization of PageError variable*/
      *PageError = 0xFFFFFFFFU;

      for (page_index = pEraseInit->Page; page_index < (pEraseInit->Page + pEraseInit->NbPages); page_index++)
      {
        /* Start erase page */
#if defined(FLASH_DBANK_SUPPORT)
        FLASH_PageErase(page_index, pEraseInit->Banks);
#else /* FLASH_DBANK_SUPPORT */
        FLASH_PageErase(page_index);
#endif /* FLASH_DBANK_SUPPORT */

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

        if (status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty page */
          *PageError = page_index;
          break;
        }
      }
    }

    /* If the erase operation is completed, disable the associated bits */
#if defined(FLASH_DBANK_SUPPORT)
    CLEAR_BIT((*reg_cr), (((pEraseInit->TypeErase) & (~(FLASH_NON_SECURE_MASK))) | FLASH_NSCR1_BKER | FLASH_NSCR1_PNB));
#else /* FLASH_DBANK_SUPPORT */
    CLEAR_BIT((*reg_cr), (((pEraseInit->TypeErase) & (~(FLASH_NON_SECURE_MASK))) | FLASH_NSCR1_PNB));
#endif /* FLASH_DBANK_SUPPORT */
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages with interrupt enabled.
  * @note   Before any operation, it is possible to check there is no operation suspended
  *         by call HAL_FLASHEx_IsOperationSuspended()
  * @param  pEraseInit Pointer to an @ref FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status;
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Verify that next operation can be proceed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status != HAL_OK)
  {
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  else
  {
    /* Set internal variables used by the IRQ handler */
    pFlash.ProcedureOnGoing = pEraseInit->TypeErase;

    /* Access to SECCR1 or NSCR1 depends on operation type */
#if defined(FLASH_SECCR1_LOCK)
    reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR1) : &(FLASH_NS->NSCR1);
#else
    reg_cr = &(FLASH_NS->NSCR1);
#endif /* FLASH_SECCR1_LOCK */

    /* Enable End of Operation and Error interrupts */
    (*reg_cr) |= (FLASH_IT_EOP | FLASH_IT_OPERR);

    if ((pEraseInit->TypeErase & (~FLASH_NON_SECURE_MASK)) == FLASH_TYPEERASE_MASSERASE)
    {
      /* Mass erase to be done */
#if defined(FLASH_DBANK_SUPPORT)
      FLASH_MassErase(pEraseInit->Banks);
#else /* FLASH_DBANK_SUPPORT */
      FLASH_MassErase();
#endif /* FLASH_DBANK_SUPPORT */
    }
    else
    {
      /* Erase by page to be done */
      pFlash.NbPagesToErase = pEraseInit->NbPages;
      pFlash.Page = pEraseInit->Page;
#if defined(FLASH_DBANK_SUPPORT)
      pFlash.Bank = pEraseInit->Banks;
#endif /* FLASH_DBANK_SUPPORT */

      /* Erase first page and wait for IT */
#if defined(FLASH_DBANK_SUPPORT)
        FLASH_PageErase(pEraseInit->Page, pEraseInit->Banks);
#else /* FLASH_DBANK_SUPPORT */
        FLASH_PageErase(pEraseInit->Page);
#endif /* FLASH_DBANK_SUPPORT */
    }
  }

  /* return status */
  return status;
}

/**
  * @brief  Program Option bytes.
  * @param  pOBInit Pointer to an @ref FLASH_OBProgramInitTypeDef structure that
  *         contains the configuration information for the programming.
  *
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of @ref HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of @ref HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Verify that next operation can be proceed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Write protection configuration */
    if ((pOBInit->OptionType & OPTIONBYTE_WRP) != 0U)
    {
      /* Configure of Write protection on the selected area */
      FLASH_OB_WRPConfig(pOBInit->WRPArea, pOBInit->WRPStartOffset, pOBInit->WRPEndOffset, pOBInit->WRPLock);
    }

    /* Read protection configuration */
    if ((pOBInit->OptionType & OPTIONBYTE_RDP) != 0U)
    {
      /* Configure the Read protection level */
      FLASH_OB_RDPConfig(pOBInit->RDPLevel);
    }

    /* Read protection key configuration */
    if ((pOBInit->OptionType & OPTIONBYTE_RDPKEY) != 0U)
    {
      /* Configure the Read protection key */
#if defined(FLASH_OEM1KEYR3_OEM1KEY)
      FLASH_OB_RDPKeyConfig(pOBInit->RDPKeyType, pOBInit->RDPKey1, pOBInit->RDPKey2, pOBInit->RDPKey3, pOBInit->RDPKey4);
#else /* FLASH_OEM1KEYR3_OEM1KEY */
      FLASH_OB_RDPKeyConfig(pOBInit->RDPKeyType, pOBInit->RDPKey1, pOBInit->RDPKey2);
#endif /* FLASH_OEM1KEYR3_OEM1KEY */
    }

    /* User Configuration */
    if ((pOBInit->OptionType & OPTIONBYTE_USER) != 0U)
    {
      /* Configure the user option bytes */
      FLASH_OB_UserConfig(pOBInit->USERType, pOBInit->USERConfig);
    }

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    /* Watermark secure configuration */
    if ((pOBInit->OptionType & OPTIONBYTE_WMSEC) != 0U)
    {
      /* Configure the watermark-based secure area */
      FLASH_OB_WMSECConfig(pOBInit->WMSecConfig, pOBInit->WMSecStartPage, pOBInit->WMSecEndPage,
                           pOBInit->WMHDPEndPage);
    }

    /* Unique boot entry point configuration */
    if ((pOBInit->OptionType & OPTIONBYTE_BOOT_LOCK) != 0U)
    {
      /* Configure the unique boot entry point */
      FLASH_OB_BootLockConfig(pOBInit->BootLock);
    }
#endif /* __ARM_FEATURE_CMSE */

    /* Boot address configuration */
    if ((pOBInit->OptionType & OPTIONBYTE_BOOTADDR) != 0U)
    {
      /* Configure the boot address */
      FLASH_OB_BootAddrConfig(pOBInit->BootAddrConfig, pOBInit->BootAddr);
    }

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->NSCR1, FLASH_NSCR1_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}

/**
  * @brief  Get the Option bytes configuration.
  * @param  pOBInit Pointer to an @ref FLASH_OBProgramInitTypeDef structure that contains the
  *                  configuration information.
  * @note   The fields pOBInit->WRPArea, pOBInit->WMSecConfig and pOBInit->BootAddrConfig
  *         should indicate which area/address is requested for the WRP, WM Security or
  *         Boot Address, else no information will be returned
  *
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = (OPTIONBYTE_RDP | OPTIONBYTE_USER);

#if defined(FLASH_DBANK_SUPPORT)
  if ((pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAB) ||
      (pOBInit->WRPArea == OB_WRPAREA_BANK2_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK2_AREAB))
#else /* FLASH_DBANK_SUPPORT */
  if ((pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAB))
#endif /* FLASH_DBANK_SUPPORT */
  {
    pOBInit->OptionType |= OPTIONBYTE_WRP;
    /* Get write protection on the selected area */
    FLASH_OB_GetWRP(pOBInit->WRPArea, &(pOBInit->WRPStartOffset), &(pOBInit->WRPEndOffset), &(pOBInit->WRPLock));
  }

  /* Get Read protection level */
  pOBInit->RDPLevel = FLASH_OB_GetRDP();

  /* Get the user option bytes */
  pOBInit->USERConfig = FLASH_OB_GetUser();

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Get the configuration of the watermark secure area for the selected area */
#if defined(FLASH_DBANK_SUPPORT)
  if ((pOBInit->WMSecConfig == OB_WMSEC_AREA1) || (pOBInit->WMSecConfig == OB_WMSEC_AREA2))
#else /* FLASH_DBANK_SUPPORT */
  if (pOBInit->WMSecConfig == OB_WMSEC_AREA1)
#endif /* FLASH_DBANK_SUPPORT */
  {
    pOBInit->OptionType |= OPTIONBYTE_WMSEC;
    FLASH_OB_GetWMSEC(&(pOBInit->WMSecConfig), &(pOBInit->WMSecStartPage), &(pOBInit->WMSecEndPage),
                      &(pOBInit->WMHDPEndPage));
  }

  pOBInit->OptionType |= OPTIONBYTE_BOOT_LOCK;

  /* Get the configuration of the unique boot entry point */
  pOBInit->BootLock = FLASH_OB_GetBootLock();
#endif /* __ARM_FEATURE_CMSE */

  /* Get the value of the selected boot address */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if ((pOBInit->BootAddrConfig == OB_BOOTADDR_NS0) || (pOBInit->BootAddrConfig == OB_BOOTADDR_NS1) ||
      (pOBInit->BootAddrConfig == OB_BOOTADDR_SEC0))
#else
  if ((pOBInit->BootAddrConfig == OB_BOOTADDR_NS0) || (pOBInit->BootAddrConfig == OB_BOOTADDR_NS1))
#endif /* __ARM_FEATURE_CMSE */
  {
    pOBInit->OptionType |= OPTIONBYTE_BOOTADDR;
    FLASH_OB_GetBootAddr(pOBInit->BootAddrConfig, &(pOBInit->BootAddr));
  }
}

#if defined(FLASH_SECBBR1_SECBB0) || defined(FLASH_PRIVBBR1_PRIVBB0) || defined(FLASH_SECBB1R1_SECBB0) || defined(FLASH_PRIVBB1R1_PRIVBB0)
/**
  * @brief  Configure the block-based secure area.
  *
  * @param  pBBAttributes pointer to an @ref FLASH_BBAttributesTypeDef structure that
  *         contains the configuration information for the programming.
  *
  * @note   The field pBBAttributes->Bank should indicate which area is requested
  *         for the block-based attributes.
  * @note   The field pBBAttributes->BBAttributesType should indicate which
  *         block-base attribute type is requested: Secure or Privilege.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_ConfigBBAttributes(const FLASH_BBAttributesTypeDef *pBBAttributes)
{
  HAL_StatusTypeDef status;
  uint8_t index;
  __IO uint32_t *reg;

  /* Check the parameters */
#if defined(FLASH_DBANK_SUPPORT)
  assert_param(IS_FLASH_BANK_EXCLUSIVE(pBBAttributes->Bank));
#endif /* FLASH_DBANK_SUPPORT */
  assert_param(IS_FLASH_BB_EXCLUSIVE(pBBAttributes->BBAttributesType));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Set the first Block-Based register to write */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    if (pBBAttributes->BBAttributesType == FLASH_BB_SEC)
    {
#if defined(FLASH_DBANK_SUPPORT)
      if (pBBAttributes->Bank == FLASH_BANK_1)
      {
        reg = &(FLASH->SECBB1R1);
      }
      else
      {
        reg = &(FLASH->SECBB2R1);
      }
#else /* FLASH_DBANK_SUPPORT */
      reg = &(FLASH->SECBBR1);
#endif /* FLASH_DBANK_SUPPORT */
    }
    else
#endif /* __ARM_FEATURE_CMSE */
    {
#if defined(FLASH_DBANK_SUPPORT)
      if (pBBAttributes->Bank == FLASH_BANK_1)
      {
        reg = &(FLASH->PRIVBB1R1);
      }
      else
      {
        reg = &(FLASH->PRIVBB2R1);
      }
#else /* FLASH_DBANK_SUPPORT */
      reg = &(FLASH->PRIVBBR1);
#endif /* FLASH_DBANK_SUPPORT */
    }

    /* Modify the register values and check that new attributes are taken in account */
    for (index = 0; index < FLASH_BLOCKBASED_NB_REG; index++)
    {
      *reg = pBBAttributes->BBAttributes_array[index];
      if ((*reg) != pBBAttributes->BBAttributes_array[index])
      {
        status = HAL_ERROR;
      }
      reg++;
    }

    /* ISB instruction is called to be sure next instructions are performed with correct attributes */
    __ISB();
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Return the block-based attributes.
  *
  * @param  pBBAttributes [in/out] pointer to an FLASH_BBAttributesTypeDef structure
  *                  that contains the configuration information.
  * @note   The field pBBAttributes->BBAttributesType should indicate which
  *         block-base attribute type is requested: Secure or Privilege.
  *
  * @retval None
  */
void HAL_FLASHEx_GetConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes)
{
  uint8_t index;
  __IO uint32_t *reg;

  /* Check the parameters */
#if defined(FLASH_DBANK_SUPPORT)
  assert_param(IS_FLASH_BANK_EXCLUSIVE(pBBAttributes->Bank));
#endif /* FLASH_DBANK_SUPPORT */
  assert_param(IS_FLASH_BB_EXCLUSIVE(pBBAttributes->BBAttributesType));

  /* Set the first Block-Based register to read */
  if (pBBAttributes->BBAttributesType == FLASH_BB_SEC)
  {
#if defined(FLASH_DBANK_SUPPORT)
    if (pBBAttributes->Bank == FLASH_BANK_1)
    {
      reg = &(FLASH->SECBB1R1);
    }
    else
    {
      reg = &(FLASH->SECBB2R1);
    }
#else /* FLASH_DBANK_SUPPORT */
    reg = &(FLASH->SECBBR1);
#endif /* FLASH_DBANK_SUPPORT */
  }
  else
  {
#if defined(FLASH_DBANK_SUPPORT)
    if (pBBAttributes->Bank == FLASH_BANK_1)
    {
      reg = &(FLASH->PRIVBB1R1);
    }
    else
    {
      reg = &(FLASH->PRIVBB2R1);
    }
#else /* FLASH_DBANK_SUPPORT */
    reg = &(FLASH->PRIVBBR1);
#endif /* FLASH_DBANK_SUPPORT */
  }

  /* Read the register values */
  for (index = 0; index < FLASH_BLOCKBASED_NB_REG; index++)
  {
    pBBAttributes->BBAttributes_array[index] = (*reg);
    reg++;
  }
}
#endif /* FLASH_SECBBR1_SECBB0 || FLASH_PRIVBBR1_PRIVBB0 */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Activation of the protection of the secure hide area.
  *
  * @param  Banks indicate the bank concerned by the activation
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1 to be protected
#if defined(FLASH_DBANK_SUPPORT)
  *            @arg FLASH_BANK_2: Bank2 to be protected
  *            @arg FLASH_BANK_BOTH: Bank1 and Bank2 to be protected
#endif
  *
  * @retval None
  */
void HAL_FLASHEx_EnableSecHideProtection(uint32_t Banks)
{
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));

#if defined(FLASH_DBANK_SUPPORT)
  if ((Banks & FLASH_BANK_1) != 0U)
  {
    SET_BIT(FLASH->SECHDPCR, FLASH_SECHDPCR_HDP1_ACCDIS);
  }

  if ((Banks & FLASH_BANK_2) != 0U)
  {
    SET_BIT(FLASH->SECHDPCR, FLASH_SECHDPCR_HDP2_ACCDIS);
  }
#else /* FLASH_DBANK_SUPPORT */
  SET_BIT(FLASH->SECHDPCR, FLASH_SECHDPCR_HDP_ACCDIS);
#endif /* FLASH_DBANK_SUPPORT */

}

#if defined(FLASH_SECHDPEXTR_HDP_PEXT)
/**
  * @brief  Configure the extended secure hide area.
  *
  * @param  pHDPExtension pointer to an @ref FLASH_HDPExtensionTypeDef structure that
  *         contains the configuration information for the programming.
  *
  * @note   The field pHDPExtension->Bank should indicate which area is requested
  *         for the extended secure hide area.
  * @note   The field pHDPExtension->NbPages should indicate the number of
  *         pages of the extended secure hide area.
  *
  * @retval  HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_ConfigHDPExtension(FLASH_HDPExtensionTypeDef *pHDPExtension)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(pHDPExtension->Bank));
  assert_param(IS_FLASH_PAGE(pHDPExtension->NbPages));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if ((pHDPExtension->Bank) == FLASH_BANK_1)
    {
      MODIFY_REG(FLASH->SECHDPEXTR, FLASH_SECHDPEXTR_HDP_PEXT, pHDPExtension->NbPages);
    }

    /* ISB instruction is called to be sure next instructions are performed with
      correct extended secure hide area configuration  */
    __ISB();
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Return the extended secure hide area.
  *
  * @param  pHDPExtension [in/out] pointer to an @ref FLASH_HDPExtensionTypeDef structure
  *         that contains the configuration information.
  *
  * @note   The field pHDPExtension->Bank should indicate which area is requested
  *         for the extended secure hide area.
  *
  * @retval  None
  */
void HAL_FLASHEx_GetConfigHDPExtension(FLASH_HDPExtensionTypeDef *pHDPExtension)
{
  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(pHDPExtension->Bank));

  if ((pHDPExtension->Bank) == FLASH_BANK_1)
  {
    pHDPExtension->NbPages = (FLASH->SECHDPEXTR & FLASH_SECHDPEXTR_HDP_PEXT);
  }
}

/**
  * @brief  Activation of the protection of the extended secure hide area.
  *
  * @param  Banks indicate the bank concerned by the activation
  *          This parameter can be one of the following values:
  *            @arg @ref FLASH_BANK_1 Bank1 to be protected
  *            @arg @ref FLASH_BANK_BOTH Bank1 to be protected
  * @param  ProtectionType indicate the type of protection to be performed
  *          This parameter can be one of the following values:
  *            @arg @ref FLASH_EXTHDP_ONLY_ACCESS_PROTECTED Access to area denied and bits configuration allowed
  *            @arg @ref FLASH_EXTHDP_ALL_PROTECTED Access to bits configuration and area denied
  *
  * @retval  None
  */
void HAL_FLASHEx_EnableHDPExtensionProtection(uint32_t Banks, uint32_t ProtectionType)
{
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));
  assert_param(IS_FLASH_EXTHDP_PROTECTION(ProtectionType));

  if ((Banks & FLASH_BANK_1) != 0U)
  {
    MODIFY_REG(FLASH->SECHDPCR,
               FLASH_SECHDPCR_HDPEXT_ACCDIS,
               ((ProtectionType & 0xFFU) << FLASH_SECHDPCR_HDPEXT_ACCDIS_Pos));
  }
}
#endif /* FLASH_SECHDPEXTR_HDP_PEXT */
#endif /* __ARM_FEATURE_CMSE */

#if defined(FLASH_OEMKEYSR_OEM1KEYCRC)
/**
  * @brief  Get the CRC value of a read protection key.
  *
  * @param  RDPKeyType Specifies the read protection key type.
  *          This parameter can be one of the following values:
  *            @arg @ref OB_RDP_KEY_OEM1 OEM1 key
  *            @arg @ref OB_RDP_KEY_OEM2 OEM2 key
  * @param  CRCKeyValue Specifies the address to return the CRC value of the key.
  *
  * @retval  None
  */
void HAL_FLASHEx_GetRDPKeyCRC(uint32_t RDPKeyType, uint32_t *CRCKeyValue)
{
  /* Check the parameters */
  assert_param(IS_OB_RDP_KEY_TYPE(RDPKeyType));

  /* Get the CRC value of OEM key */
  if (RDPKeyType == OB_RDP_KEY_OEM1)
  {
    *CRCKeyValue = (FLASH->OEMKEYSR & FLASH_OEMKEYSR_OEM1KEYCRC);
  }
  else
  {
    *CRCKeyValue = ((FLASH->OEMKEYSR & FLASH_OEMKEYSR_OEM2KEYCRC) >> FLASH_OEMKEYSR_OEM2KEYCRC_Pos);
  }
}
#endif /* FLASH_OEMKEYSR_OEM1KEYCRC */

/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions_Group2 Extended Peripheral Control functions
  *  @brief   Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
                      ##### Extended Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the FLASH
    memory operations.

@endverbatim
  * @{
  */

/**
  * @brief  Suspend new program or erase operation request.
  * @param  Request  Indicate the suspend operation request
  *                  This parameter can be a value of @ref FLASHEx_Suspend_Request
  * @retval None
  */
void HAL_FLASHEx_SuspendOperation(uint32_t Request)
{
  /* Check the parameter */
  assert_param(IS_FLASH_SUSPEND_REQ(Request));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(FLASH->SECCR2, Request);
#else
  SET_BIT(FLASH->NSCR2, Request);
#endif /* __ARM_FEATURE_CMSE */
}

/**
  * @brief  Allow new program or erase operation request.
  * @param  Request  Indicate the allow operation request
  *                  This parameter can be a value of @ref FLASHEx_Allow_Request
  * @retval None
  */
void HAL_FLASHEx_AllowOperation(uint32_t Request)
{
  /* Check the parameter */
  assert_param(IS_FLASH_ALLOW_REQ(Request));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(FLASH->SECCR2, Request);
#else
  CLEAR_BIT(FLASH->NSCR2, Request);
#endif /* __ARM_FEATURE_CMSE */
}

/**
  * @brief  Check if new program or erase operation request is suspended
  * @retval Status
  *          - 0 : No suspended flash operation
  *          - FLASH_SUSPEND_PROGRAM : Program operations are suspended
  *          - FLASH_SUSPEND_ERASE : Erase operations are suspended
  *          - FLASH_SUSPEND_PROGRAM_ERASE : Program and erase operations are suspended
  */
uint32_t HAL_FLASHEx_IsOperationSuspended(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return (FLASH->SECCR2 & FLASH_SUSPEND_PROGRAM_ERASE);
#else
  return (FLASH->NSCR2 & FLASH_SUSPEND_PROGRAM_ERASE);
#endif /* __ARM_FEATURE_CMSE */
}

#if defined(FLASH_PRIVCFGR_SPRIV)
/**
  * @brief  Configuration of the privilege attribute.
  *
  * @param  PrivMode indicate privilege mode configuration
  *          This parameter can be one of the following values:
  *            @arg FLASH_SPRIV_GRANTED: access to secure Flash registers is granted to privileged or unprivileged access
  *            @arg FLASH_SPRIV_DENIED: access to secure Flash registers is denied to unprivileged access
  *            @arg FLASH_NSPRIV_GRANTED: access to non-secure Flash registers is granted to privileged or unprivileged access
  *            @arg FLASH_NSPRIV_DENIED: access to non-secure Flash registers is denied to unprivilege access
  *
  * @retval None
  */
void HAL_FLASHEx_ConfigPrivMode(uint32_t PrivMode)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CFGPRIVMODE(PrivMode));

  MODIFY_REG(FLASH->PRIVCFGR, (FLASH_PRIVCFGR_SPRIV | FLASH_PRIVCFGR_NSPRIV), PrivMode);
}

/**
  * @brief  Return the value of the privilege attribute.
  *
  * @retval  It indicates the privilege mode configuration.
  *          This return value can be one of the following values:
  *            @arg FLASH_SPRIV_GRANTED: access to secure Flash registers is granted to privileged or unprivileged access
  *            @arg FLASH_SPRIV_DENIED: access to secure Flash registers is denied to unprivileged access
  *            @arg FLASH_NSPRIV_GRANTED: access to non-secure Flash registers is granted to privileged or unprivileged access
  *            @arg FLASH_NSPRIV_DENIED: access to Flash registers is denied to unprivilege accessP
  */
uint32_t HAL_FLASHEx_GetPrivMode(void)
{
  return (FLASH->PRIVCFGR & (FLASH_PRIVCFGR_SPRIV | FLASH_PRIVCFGR_NSPRIV));
}
#endif /* FLASH_PRIVCFGR_SPRIV */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configuration of the security inversion.
  *
  * @param  SecInvState indicate the flash security state configuration
  *          This parameter can be one of the following values:
  *            @arg FLASH_SEC_INV_DISABLE: Security state of Flash is not inverted
  *            @arg FLASH_SEC_INV_ENABLE: Security state of Flash is inverted
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_ConfigSecInversion(uint32_t SecInvState)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_CFGSECINV(SecInvState));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    MODIFY_REG(FLASH->SECCR1, FLASH_SECCR1_INV, SecInvState);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Return the value of the security inversion.
  *
  * @retval  It indicates the flash security state configuration
  *          This return value can be one of the following values:
  *            @arg FLASH_SEC_INV_DISABLE: Security state of Flash is not inverted
  *            @arg FLASH_SEC_INV_ENABLE: Security state of Flash is inverted
  */
uint32_t HAL_FLASHEx_GetSecInversion(void)
{
  return (FLASH->SECCR1 & FLASH_SECCR1_INV);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Enable the Power-down Mode for Flash Banks
#if defined(FLASH_DBANK_SUPPORT)
  * @param  Banks indicate which bank to put in power-down mode
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Flash Bank 1
  *            @arg FLASH_BANK_2: Flash Bank 2
  *            @arg FLASH_BANK_BOTH: Flash Bank 1 and Bank 2
#endif
  * @retval HAL Status
  */
#if defined(FLASH_DBANK_SUPPORT)
HAL_StatusTypeDef HAL_FLASHEx_EnablePowerDown(uint32_t Banks)
#else /* FLASH_DBANK_SUPPORT */
HAL_StatusTypeDef HAL_FLASHEx_EnablePowerDown()
#endif /* FLASH_DBANK_SUPPORT */
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tickstart;

#if defined(FLASH_DBANK_SUPPORT)
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));

  /* Request power-down mode for Bank 1 */
  if ((Banks & FLASH_BANK_1) != 0U)
  {
    /* Check PD1 and PDREQ1 bits (Flash is not in power-down mode and not being
       already under power-down request) */
    if ((FLASH->NSSR & FLASH_NSSR_PD1) != 0U)
    {
      status = HAL_ERROR;
    }
    else if ((FLASH->ACR & FLASH_ACR_PDREQ1) != 0U)
    {
      status = HAL_ERROR;
    }
    else
    {
      /* Unlock PDREQ bit */
      WRITE_REG(FLASH->PDKEY1R, FLASH_PDKEY1_1);
      WRITE_REG(FLASH->PDKEY1R, FLASH_PDKEY1_2);

      /* Set PDREQ in FLASH_ACR register */
      SET_BIT(FLASH->ACR, FLASH_ACR_PDREQ1);

      /* Check PD1 bit */
      tickstart = HAL_GetTick();
      while (((FLASH->NSSR & FLASH_NSSR_PD1) == 0U))
      {
        if((HAL_GetTick() - tickstart) > FLASH_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /* Request power-down mode for Bank 2 */
  if ((Banks & FLASH_BANK_2) != 0U)
  {
    /* Check PD2 and PDREQ2 bits (Bank 2 is not in power-down mode and not being
       already under power-down request) */
    if ((FLASH->NSSR & FLASH_NSSR_PD2) != 0U)
    {
      status = HAL_ERROR;
    }
    else if ((FLASH->ACR & FLASH_ACR_PDREQ2) != 0U)
    {
      status = HAL_ERROR;
    }
    else
    {
      /* Unlock PDREQ2 bit */
      WRITE_REG(FLASH->PDKEY2R, FLASH_PDKEY2_1);
      WRITE_REG(FLASH->PDKEY2R, FLASH_PDKEY2_2);

      /* Set PDREQ2 in FLASH_ACR register */
      SET_BIT(FLASH->ACR, FLASH_ACR_PDREQ2);

      /* Check PD2 bit */
      tickstart = HAL_GetTick();
      while (((FLASH->NSSR & FLASH_NSSR_PD2) == 0U))
      {
        if ((HAL_GetTick() - tickstart) > FLASH_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }
#else /* FLASH_DBANK_SUPPORT */
  /* Check PD and PDREQ bits (Flash is not in power-down mode and not being
     already under power-down request) */
  if ((FLASH->NSSR & FLASH_NSSR_PD) != 0U)
  {
    status = HAL_ERROR;
  }
  else if ((FLASH->ACR & FLASH_ACR_PDREQ) != 0U)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Unlock PDREQ bit */
    WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY1);
    WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY2);

    /* Set PDREQ in FLASH_ACR register */
    SET_BIT(FLASH->ACR, FLASH_ACR_PDREQ);

    /* Check PD1 bit */
    tickstart = HAL_GetTick();
    while (((FLASH->NSSR & FLASH_NSSR_PD) != FLASH_NSSR_PD))
    {
      if ((HAL_GetTick() - tickstart) > FLASH_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }
#endif /* FLASH_DBANK_SUPPORT */

  return status;
}

/**
  * @brief  Configuration of the Low-Power read Mode.
  *
  * @param  ConfigLPM indicate the Low-Power read Mode configuration.
  *         This parameter can be one of the following values:
  *           @arg FLASH_LPM_ENABLE: Flash is in low-power read mode
  *           @arg FLASH_LPM_DISABLE: Flash is in normal read mode
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_ConfigLowPowerRead(uint32_t ConfigLPM)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_FLASH_CFGLPM(ConfigLPM));

  /* Set LPM Bit in FLASH_ACR register */
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LPM, ConfigLPM);

  /* Check that low power read mode has been activated */
  if (READ_BIT(FLASH->ACR, FLASH_ACR_LPM) != ConfigLPM)
  {
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Return the value of the Low-Power read Mode.
  *
  * @retval  It indicates the flash low-power read mode configuration
  *          This return value can be one of the following values:
  *            @arg FLASH_LPM_ENABLE: Flash is in low-power read mode
  *            @arg FLASH_LPM_DISABLE: Flash is in normal read mode
  */
uint32_t HAL_FLASHEx_GetLowPowerRead(void)
{
  return (FLASH->ACR & FLASH_ACR_LPM);
}

/**
  * @brief  Return the on-going Flash Operation. After a system reset, return
  *         the interrupted Flash operation, if any.
  * @param  pFlashOperation [out] pointer to a FLASH_OperationTypeDef structure
  *                 that contains the Flash operation information.
  *
  * @retval None
  */
void HAL_FLASHEx_GetOperation(FLASH_OperationTypeDef *pFlashOperation)
{
  uint32_t opsr_reg = FLASH->OPSR;

  /* Get Flash operation Type */
  pFlashOperation->OperationType = opsr_reg & FLASH_OPSR_CODE_OP;

  /* Get Flash operation memory */
#if defined(FLASH_DBANK_SUPPORT)
  pFlashOperation->FlashArea = (opsr_reg & (FLASH_OPSR_SYSF_OP | FLASH_OPSR_BK_OP));
#else /* FLASH_DBANK_SUPPORT */
  pFlashOperation->FlashArea = opsr_reg & FLASH_OPSR_SYSF_OP;
#endif /* FLASH_DBANK_SUPPORT */

  /* Get Flash operation address */
  pFlashOperation->Address = opsr_reg & FLASH_OPSR_ADDR_OP;
}

/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions_Group3 Extended ECC operation functions
  *  @brief   Extended ECC operation functions
  *
@verbatim
 ===============================================================================
                  ##### Extended ECC operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the Extended FLASH
    ECC Operations.

@endverbatim
  * @{
  */
/**
  * @brief  Enable ECC correction interrupt
  * @note   ECC detection does not need to be enabled as directly linked to
  *         Non-Maskable Interrupt (NMI)
  * @retval None
  */
void HAL_FLASHEx_EnableEccCorrectionInterrupt(void)
{
  __HAL_FLASH_ENABLE_IT(FLASH_IT_ECCC);
}

/**
  * @brief  Disable ECC correction interrupt
  * @retval None
  */
void HAL_FLASHEx_DisableEccCorrectionInterrupt(void)
{
  __HAL_FLASH_DISABLE_IT(FLASH_IT_ECCC);
}

/**
  * @brief  Get the ECC error information.
  * @param  pData Pointer to an FLASH_EccInfoTypeDef structure that contains the
  *         ECC error information.
  * @note   This function should be called before ECC bit is cleared
  *         (in callback function)
  * @retval None
  */
void HAL_FLASHEx_GetEccInfo(FLASH_EccInfoTypeDef *pData)
{
  uint32_t eccr;
  /* Check Null pointer */
  assert_param(pData != NULL);

  /* Get back information from ECC register */
  eccr = FLASH->ECCR;

  /* Retrieve and sort information */
#if defined(FLASH_DBANK_SUPPORT)
  pData->Area = (eccr & (FLASH_ECCR_SYSF_ECC | FLASH_ECCR_BK_ECC));
#else /* FLASH_DBANK_SUPPORT */
  pData->Area = (eccr & FLASH_ECCR_SYSF_ECC);
#endif /* FLASH_DBANK_SUPPORT */
  pData->Address = ((eccr & FLASH_ECCR_ADDR_ECC) << 3U);

  /* Add Base address depending on targeted area */
  if (pData->Area == FLASH_ECC_AREA_USER_BANK1)
  {
    pData->Address |= FLASH_BASE;
  }
#if defined(FLASH_DBANK_SUPPORT)
  else if (pData->Area == FLASH_ECC_AREA_USER_BANK2)
  {
    pData->Address |= (FLASH_BASE + FLASH_BANK_SIZE);
  }
#endif /* FLASH_DBANK_SUPPORT */
  else
  {
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    pData->Address |= SYSTEM_FLASH_BASE_S;
#else
    pData->Address |= SYSTEM_FLASH_BASE_NS;
#endif /* __ARM_FEATURE_CMSE */
  }

  /* Set Master which initiates transaction. On WBA, it's necessary CPU1 */
  pData->MasterID = FLASH_ECC_MASTER_CPU1;
}

/**
  * @brief  Handle Flash ECC Detection interrupt request.
  * @note   On STM32WBA, this Irq Handler should be called in Non-Maskable Interrupt (NMI)
  *         interrupt subroutine.
  * @retval None
  */
void HAL_FLASHEx_ECCD_IRQHandler(void)
{
  /* Check ECC Detection Error */
  if ((FLASH->ECCR & FLASH_ECCR_ECCD) != 0U)
  {
    /* Call User callback */
    HAL_FLASHEx_EccDetectionCallback();

    /* Clear ECC detection flag in order to allow new ECC error record */
    SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCD);
  }
}

/**
  * @brief  FLASH ECC Correction interrupt callback.
  * @retval None
  */
__weak void HAL_FLASHEx_EccCorrectionCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASHEx_EccCorrectionCallback could be implemented in the user file
   */
}

/**
  * @brief  FLASH ECC Detection interrupt callback.
  * @retval None
  */
__weak void HAL_FLASHEx_EccDetectionCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASHEx_EccDetectionCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @addtogroup FLASHEx_Private_Functions
  * @{
  */
/**
  * @brief  Mass erase of FLASH memory.
#if defined(FLASH_DBANK_SUPPORT)
  * @param  Banks Banks to be erased
  *          This parameter can be one of the following values:
  *            @arg @ref FLASH_BANK_1 Bank1 to be erased
  *            @arg @ref FLASH_BANK_2 Bank2 to be erased
  *            @arg @ref FLASH_BANK_BOTH Bank1 and Bank2 to be erased
#endif
  * @retval None
  */
#if defined(FLASH_DBANK_SUPPORT)
static void FLASH_MassErase(uint32_t Banks)
#else /* FLASH_DBANK_SUPPORT */
static void FLASH_MassErase()
#endif /* FLASH_DBANK_SUPPORT */
{
  __IO uint32_t *reg_cr;

#if defined(FLASH_DBANK_SUPPORT)
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));
#endif /* FLASH_DBANK_SUPPORT */

  /* Access to SECCR1 or NSCR1 registers depends on operation type */
#if defined(FLASH_SECCR1_LOCK)
  reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR1) : &(FLASH_NS->NSCR1);
#else
  reg_cr = &(FLASH_NS->NSCR1);
#endif /* FLASH_SECCR1_LOCK */

#if defined(FLASH_DBANK_SUPPORT)
  /* Set the Mass Erase Bit for the bank 1 and 2 if requested */
  SET_BIT((*reg_cr), Banks);

  /* Proceed to erase */
  SET_BIT((*reg_cr), FLASH_NSCR1_STRT);
#else /* FLASH_DBANK_SUPPORT */
  /* Set the Mass Erase Bit for the bank 1 and proceed to erase */
  SET_BIT((*reg_cr), FLASH_NSCR1_MER | FLASH_NSCR1_STRT);
#endif /* FLASH_DBANK_SUPPORT */
}

/**
  * @brief  Erase the specified FLASH memory page.
  * @param  Page FLASH page to erase
  *         This parameter must be a value between 0 and (max number of pages in the bank - 1)
#if defined(FLASH_DBANK_SUPPORT)
  * @param  Banks Bank(s) where the page will be erased
  *          This parameter can be one of the following values:
  *            @arg @ref FLASH_BANK_1 Page in bank 1 to be erased
  *            @arg @ref FLASH_BANK_2 Page in bank 2 to be erased
#endif
  * @retval None
  */
#if defined(FLASH_DBANK_SUPPORT)
void FLASH_PageErase(uint32_t Page, uint32_t Banks)
#else /* FLASH_DBANK_SUPPORT */
void FLASH_PageErase(uint32_t Page)
#endif /* FLASH_DBANK_SUPPORT */
{
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_PAGE(Page));
#if defined(FLASH_DBANK_SUPPORT)
  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(Banks));
#endif /* FLASH_DBANK_SUPPORT */

  /* Access to SECCR1 or NSCR1 registers depends on operation type */
#if defined(FLASH_SECCR1_LOCK)
  reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR1) : &(FLASH_NS->NSCR1);
#else
  reg_cr = &(FLASH_NS->NSCR1);
#endif /* FLASH_SECCR1_LOCK */

#if defined(FLASH_DBANK_SUPPORT)
  if ((Banks & FLASH_BANK_1) != 0U)
  {
    CLEAR_BIT((*reg_cr), FLASH_NSCR1_BKER);
  }
  else
  {
    SET_BIT((*reg_cr), FLASH_NSCR1_BKER);
  }
#endif /* FLASH_DBANK_SUPPORT */

  /* Proceed to erase the page */
  MODIFY_REG((*reg_cr), (FLASH_NSCR1_PNB | FLASH_NSCR1_PER | FLASH_NSCR1_STRT), ((Page << FLASH_NSCR1_PNB_Pos) | FLASH_NSCR1_PER | FLASH_NSCR1_STRT));
}

/**
  * @brief  Configure the write protection of the desired pages.
  *
  * @note   When WRP is active in a zone, it cannot be erased or programmed.
  *         Consequently, a software mass erase cannot be performed if one zone
  *         is write-protected.
  * @note   When the memory read protection level is selected (RDP level = 1),
  *         it is not possible to program or erase Flash memory if the CPU debug
  *         features are connected (JTAG or single wire) or boot code is being
  *         executed from RAM or System flash, even if WRP is not activated.
  * @note   To configure the WRP options, the option lock bit OPTLOCK must be
  *         cleared with the call of the @ref HAL_FLASH_OB_Unlock() function.
  * @note   To validate the WRP options, the option bytes must be reloaded
  *         through the call of the @ref HAL_FLASH_OB_Launch() function.
  *
  * @param  WRPArea Specifies the area to be configured.
  *          This parameter can be one of the following values:
  *            @arg @ref OB_WRPAREA_BANK1_AREAA Flash Bank 1 Area A
  *            @arg @ref OB_WRPAREA_BANK1_AREAB Flash Bank 1 Area B
#if defined(FLASH_DBANK_SUPPORT)
  *            @arg @ref OB_WRPAREA_BANK2_AREAA Flash Bank 2 Area A
  *            @arg @ref OB_WRPAREA_BANK2_AREAB Flash Bank 2 Area B
#endif
  *
  * @param  WRPStartOffset Specifies the start page of the write protected area
  *          This parameter can be page number between 0 and (max number of pages in the Flash - 1)
  *
  * @param  WRPEndOffset Specifies the end page of the write protected area
  *          This parameter can be page number between WRPStartOffset and (max number of pages in the Flash - 1)
  *
  * @param  WRPLock Enables the lock of the write protected area
  *          This parameter can be set to ENABLE or DISABLE
  *
  * @retval None
  */
static void FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRPEndOffset, FunctionalState WRPLock)
{
  /* Check the parameters */
  assert_param(IS_OB_WRPAREA(WRPArea));
  assert_param(IS_FLASH_PAGE(WRPStartOffset));
  assert_param(IS_FLASH_PAGE(WRPEndOffset));
  assert_param(IS_FUNCTIONAL_STATE(WRPLock));

  /* Configure the write protected area */
  if (WRPArea == OB_WRPAREA_BANK1_AREAA)
  {
#if defined(FLASH_DBANK_SUPPORT)
    FLASH->WRP1AR = (((uint32_t)(~WRPLock) << FLASH_WRP1AR_UNLOCK_Pos)       | \
                     (WRPEndOffset << FLASH_WRP1AR_WRP1A_PEND_Pos) | \
                     WRPStartOffset);
#else /* FLASH_DBANK_SUPPORT */
    FLASH->WRPAR = (((uint32_t)(~WRPLock) << FLASH_WRPAR_UNLOCK_Pos)       | \
                    (WRPEndOffset << FLASH_WRPAR_WRPA_PEND_Pos) | \
                    WRPStartOffset);
#endif /* FLASH_DBANK_SUPPORT */
  }
  else if (WRPArea == OB_WRPAREA_BANK1_AREAB)
  {
#if defined(FLASH_DBANK_SUPPORT)
    FLASH->WRP1BR = (((uint32_t)(~WRPLock) << FLASH_WRP1BR_UNLOCK_Pos)       | \
                     (WRPEndOffset << FLASH_WRP1BR_WRP1B_PEND_Pos) | \
                     WRPStartOffset);
#else /* FLASH_DBANK_SUPPORT */
    FLASH->WRPBR = (((uint32_t)(~WRPLock) << FLASH_WRPBR_UNLOCK_Pos)       | \
                    (WRPEndOffset << FLASH_WRPBR_WRPB_PEND_Pos) | \
                    WRPStartOffset);
#endif /* FLASH_DBANK_SUPPORT */
  }
#if defined(FLASH_DBANK_SUPPORT)
  else if (WRPArea == OB_WRPAREA_BANK2_AREAA)
  {
    FLASH->WRP2AR = (((uint32_t)(~WRPLock) << FLASH_WRP2AR_UNLOCK_Pos)       | \
                     (WRPEndOffset << FLASH_WRP2AR_WRP2A_PEND_Pos) | \
                     WRPStartOffset);
  }
  else if (WRPArea == OB_WRPAREA_BANK2_AREAB)
  {
    FLASH->WRP2BR = (((uint32_t)(~WRPLock) << FLASH_WRP2BR_UNLOCK_Pos)       | \
                     (WRPEndOffset << FLASH_WRP2BR_WRP2B_PEND_Pos) | \
                     WRPStartOffset);
  }
#endif /* FLASH_DBANK_SUPPORT */
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Set the read protection level.
  *
  * @note   To configure the RDP level, the option lock bit OPTLOCK must be
  *         cleared with the call of the @ref HAL_FLASH_OB_Unlock() function.
  * @note   To validate the RDP level, the option bytes must be reloaded
  *         through the call of the @ref HAL_FLASH_OB_Launch() function.
  * @note   !!! Warning : When enabling OB_RDP level 2 it's no more possible
  *         to go back to other levels !!!
  *
  * @param  RDPLevel specifies the read protection level.
  *         This parameter can be one of the following values:
  *            @arg @ref OB_RDP_LEVEL_0 No protection
  *            @arg @ref OB_RDP_LEVEL_0_5 No debug access to secure area
  *            @arg @ref OB_RDP_LEVEL_1 Read protection of the memory
  *            @arg @ref OB_RDP_LEVEL_2 Full chip protection
  *
  * @retval None
  */
static void FLASH_OB_RDPConfig(uint32_t RDPLevel)
{
  /* Check the parameters */
  assert_param(IS_OB_RDP_LEVEL(RDPLevel));

  /* Configure the RDP level in the option bytes register */
  MODIFY_REG(FLASH->OPTR, FLASH_OPTR_RDP, RDPLevel);
}

/**
  * @brief  Set the read protection key.
  * @param  RDPKeyType Specifies the read protection key type.
  *         This parameter can be one of the following values:
  *            @arg @ref OB_RDP_KEY_OEM1 OEM1 key
  *            @arg @ref OB_RDP_KEY_OEM2 OEM2 key
  * @param  RDPKey1 Specifies the RDP key bits[0:31].
  * @param  RDPKey2 Specifies the RDP key bits[32:63].
#if defined(FLASH_OEM1KEYR3_OEM1KEY)
  * @param  RDPKey3 Specifies the RDP key bits[64:95].
  * @param  RDPKey4 Specifies the RDP key bits[96:127].
#endif
  * @retval None
  */
#if defined(FLASH_OEM1KEYR3_OEM1KEY)
static void FLASH_OB_RDPKeyConfig(uint32_t RDPKeyType, uint32_t RDPKey1, uint32_t RDPKey2,
                                  uint32_t RDPKey3, uint32_t RDPKey4)
#else /* FLASH_OEM1KEYR3_OEM1KEY */
static void FLASH_OB_RDPKeyConfig(uint32_t RDPKeyType, uint32_t RDPKey1, uint32_t RDPKey2)
#endif /* FLASH_OEM1KEYR3_OEM1KEY */
{
  /* Check the parameters */
  assert_param(IS_OB_RDP_KEY_TYPE(RDPKeyType));

  /* Configure the RDP OEM key */
  if (RDPKeyType == OB_RDP_KEY_OEM1)
  {
    WRITE_REG(FLASH->OEM1KEYR1, RDPKey1);
    WRITE_REG(FLASH->OEM1KEYR2, RDPKey2);
#if defined(FLASH_OEM1KEYR3_OEM1KEY)
    WRITE_REG(FLASH->OEM1KEYR3, RDPKey3);
    WRITE_REG(FLASH->OEM1KEYR4, RDPKey4);
#endif /* FLASH_OEM1KEYR3_OEM1KEY */
  }
  else
  {
    WRITE_REG(FLASH->OEM2KEYR1, RDPKey1);
    WRITE_REG(FLASH->OEM2KEYR2, RDPKey2);
#if defined(FLASH_OEM1KEYR3_OEM1KEY)
    WRITE_REG(FLASH->OEM2KEYR3, RDPKey3);
    WRITE_REG(FLASH->OEM2KEYR4, RDPKey4);
#endif /* FLASH_OEM1KEYR3_OEM1KEY */
  }
}

/**
  * @brief  Program the FLASH User Option Byte.
  *
  * @note   To configure the user option bytes, the option lock bit OPTLOCK must
  *         be cleared with the call of the @ref HAL_FLASH_OB_Unlock() function.
  * @note   To validate the user option bytes, the option bytes must be reloaded
  *         through the call of the @ref HAL_FLASH_OB_Launch() function.
  *
  * @param  UserType The FLASH User Option Bytes to be modified.
  *         This parameter can be a combination of @ref FLASH_OB_USER_Type
  * @param  UserConfig The selected User Option Bytes values.
  *         This parameter can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
  *         @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY,
  *         @ref FLASH_OB_USER_SRAM1_RST, @ref FLASH_OB_USER_IWDG_SW,
  *         @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
  *         @ref FLASH_OB_USER_WWDG_SW, @ref FLASH_OB_USER_SRAM2_PAR,
  *         @ref FLASH_OB_USER_SRAM2_RST, @ref FLASH_OB_USER_nSWBOOT0,
  *         @ref FLASH_OB_USER_nBOOT0 and @ref OB_USER_TZEN(*)
  * (*) Feature not available on all devices of the family
  * @retval None
  */
static void FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig)
{
  uint32_t optr_reg_val = 0;
  uint32_t optr_reg_mask = 0;

  /* Check the parameters */
  assert_param(IS_OB_USER_TYPE(UserType));

  if ((UserType & OB_USER_BOR_LEV) != 0U)
  {
    /* BOR level option byte should be modified */
    assert_param(IS_OB_USER_BOR_LEVEL(UserConfig & FLASH_OPTR_BOR_LEV));

    /* Set value and mask for BOR level option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_BOR_LEV);
    optr_reg_mask |= FLASH_OPTR_BOR_LEV;
  }

  if ((UserType & OB_USER_nRST_STOP) != 0U)
  {
    /* nRST_STOP option byte should be modified */
    assert_param(IS_OB_USER_STOP(UserConfig & FLASH_OPTR_nRST_STOP));

    /* Set value and mask for nRST_STOP option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_STOP);
    optr_reg_mask |= FLASH_OPTR_nRST_STOP;
  }

  if ((UserType & OB_USER_nRST_STDBY) != 0U)
  {
    /* nRST_STDBY option byte should be modified */
    assert_param(IS_OB_USER_STANDBY(UserConfig & FLASH_OPTR_nRST_STDBY));

    /* Set value and mask for nRST_STDBY option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_STDBY);
    optr_reg_mask |= FLASH_OPTR_nRST_STDBY;
  }

  if ((UserType & OB_USER_SRAM1_RST) != 0U)
  {
    /* SRAM1_RST option byte should be modified */
    assert_param(IS_OB_USER_SRAM1_RST(UserConfig & FLASH_OPTR_SRAM1_RST));

    /* Set value and mask for SRAM1_RST option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_SRAM1_RST);
    optr_reg_mask |= FLASH_OPTR_SRAM1_RST;
  }

  if ((UserType & OB_USER_IWDG_SW) != 0U)
  {
    /* IWDG_SW option byte should be modified */
    assert_param(IS_OB_USER_IWDG(UserConfig & FLASH_OPTR_IWDG_SW));

    /* Set value and mask for IWDG_SW option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_SW);
    optr_reg_mask |= FLASH_OPTR_IWDG_SW;
  }

  if ((UserType & OB_USER_IWDG_STOP) != 0U)
  {
    /* IWDG_STOP option byte should be modified */
    assert_param(IS_OB_USER_IWDG_STOP(UserConfig & FLASH_OPTR_IWDG_STOP));

    /* Set value and mask for IWDG_STOP option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_STOP);
    optr_reg_mask |= FLASH_OPTR_IWDG_STOP;
  }

  if ((UserType & OB_USER_IWDG_STDBY) != 0U)
  {
    /* IWDG_STDBY option byte should be modified */
    assert_param(IS_OB_USER_IWDG_STDBY(UserConfig & FLASH_OPTR_IWDG_STDBY));

    /* Set value and mask for IWDG_STDBY option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_STDBY);
    optr_reg_mask |= FLASH_OPTR_IWDG_STDBY;
  }

#if defined(FLASH_OPTR_WWDG_SW)
  if ((UserType & OB_USER_WWDG_SW) != 0U)
  {
    /* WWDG_SW option byte should be modified */
    assert_param(IS_OB_USER_WWDG(UserConfig & FLASH_OPTR_WWDG_SW));

    /* Set value and mask for WWDG_SW option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_WWDG_SW);
    optr_reg_mask |= FLASH_OPTR_WWDG_SW;
  }
#endif /* FLASH_OPTR_WWDG_SW */

#if defined(FLASH_DBANK_SUPPORT)
  if ((UserType & OB_USER_SWAP_BANK) != 0U)
  {
    /* SWAP_BANK option byte should be modified */
    assert_param(IS_OB_USER_SWAP_BANK(UserConfig & FLASH_OPTR_SWAP_BANK));

    /* Set value and mask for SWAP_BANK option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_SWAP_BANK);
    optr_reg_mask |= FLASH_OPTR_SWAP_BANK;
  }

  if ((UserType & OB_USER_DUALBANK) != 0U)
  {
    /* DUALBANK option byte should be modified */
    assert_param(IS_OB_USER_DUALBANK(UserConfig & FLASH_OPTR_DUAL_BANK));

    /* Set value and mask for DUALBANK option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_DUAL_BANK);
    optr_reg_mask |= FLASH_OPTR_DUAL_BANK;
  }
#endif /* FLASH_DBANK_SUPPORT */

  if ((UserType & OB_USER_SRAM2_PE) != 0U)
  {
    /* SRAM2_PAR option byte should be modified */
    assert_param(IS_OB_USER_SRAM2_PARITY(UserConfig & FLASH_OPTR_SRAM2_PE));

    /* Set value and mask for SRAM2_PAR option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_SRAM2_PE);
    optr_reg_mask |= FLASH_OPTR_SRAM2_PE;
  }

  if ((UserType & OB_USER_SRAM2_RST) != 0U)
  {
    /* SRAM2_RST option byte should be modified */
    assert_param(IS_OB_USER_SRAM2_RST(UserConfig & FLASH_OPTR_SRAM2_RST));

    /* Set value and mask for SRAM2_RST option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_SRAM2_RST);
    optr_reg_mask |= FLASH_OPTR_SRAM2_RST;
  }

  if ((UserType & OB_USER_nSWBOOT0) != 0U)
  {
    /* nSWBOOT0 option byte should be modified */
    assert_param(IS_OB_USER_SWBOOT0(UserConfig & FLASH_OPTR_nSWBOOT0));

    /* Set value and mask for nSWBOOT0 option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nSWBOOT0);
    optr_reg_mask |= FLASH_OPTR_nSWBOOT0;
  }

  if ((UserType & OB_USER_nBOOT0) != 0U)
  {
    /* nBOOT0 option byte should be modified */
    assert_param(IS_OB_USER_BOOT0(UserConfig & FLASH_OPTR_nBOOT0));

    /* Set value and mask for nBOOT0 option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nBOOT0);
    optr_reg_mask |= FLASH_OPTR_nBOOT0;
  }

#if defined(FLASH_OPTR_IO_VDD_HSLV)
  if ((UserType & OB_USER_IO_VDD_HSLV) != 0U)
  {
    /* IO_VDD_HSLV option byte should be modified */
    assert_param(IS_OB_USER_IO_VDD_HSLV(UserConfig & FLASH_OPTR_IO_VDD_HSLV));

    /* Set value and mask for IO_VDD_HSLV option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IO_VDD_HSLV);
    optr_reg_mask |= FLASH_OPTR_IO_VDD_HSLV;
  }
#endif /* FLASH_OPTR_IO_VDD_HSLV */

#if defined(FLASH_OPTR_IO_VDDIO2_HSLV)
  if ((UserType & OB_USER_IO_VDDIO2_HSLV) != 0U)
  {
    /* IO_VDDIO2_HSLV option byte should be modified */
    assert_param(IS_OB_USER_IO_VDDIO2_HSLV(UserConfig & FLASH_OPTR_IO_VDDIO2_HSLV));

    /* Set value and mask for IO_VDDIO2_HSLV option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IO_VDDIO2_HSLV);
    optr_reg_mask |= FLASH_OPTR_IO_VDDIO2_HSLV;
  }
#endif /* FLASH_OPTR_IO_VDDIO2_HSLV */

#if defined(FLASH_OPTR_TZEN)
  if ((UserType & OB_USER_TZEN) != 0U)
  {
    /* TZEN option byte should be modified */
    assert_param(IS_OB_USER_TZEN(UserConfig & FLASH_OPTR_TZEN));

    /* Set value and mask for TZEN option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_TZEN);
    optr_reg_mask |= FLASH_OPTR_TZEN;
  }
#endif /* FLASH_OPTR_TZEN */

  /* Configure the option bytes register */
  MODIFY_REG(FLASH->OPTR, optr_reg_mask, optr_reg_val);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure the watermarked-based secure area.
  *
  * @param  WMSecConfig specifies the area to be configured.
  *          This parameter can be a combination of the following values:
  *            @arg @ref OB_WMSEC_AREA1 Select Flash Secure Area 1
  *            @arg @ref OB_WMSEC_SECURE_AREA_CONFIG Configure Flash Secure Area
  *            @arg @ref OB_WMSEC_HDP_AREA_CONFIG Configure Flash secure hide Area
  *            @arg @ref OB_WMSEC_HDP_AREA_ENABLE Enable secure hide Area in Secure Area
  *            @arg @ref OB_WMSEC_HDP_AREA_DISABLE Disable secure hide Area in Secure Area
  *
  * @param  WMSecStartPage Specifies the start page of the secure area
  *          This parameter can be page number between 0 and (max number of pages in the bank - 1)
  *
  * @param  WMSecEndPage Specifies the end page of the secure area
  *          This parameter can be page number between WMSecStartPage and (max number of pages in the bank - 1)
  *
  * @param  WMHDPEndPage Specifies the end page of the secure hide area
  *          This parameter can be a page number between WMSecStartPage and WMSecEndPage
  *
  * @retval None
  */
static void FLASH_OB_WMSECConfig(uint32_t WMSecConfig, uint32_t WMSecStartPage, uint32_t WMSecEndPage,
                                 uint32_t WMHDPEndPage)
{
  uint32_t tmp_secwm1 = 0U;
  uint32_t tmp_secwm2 = 0U;

  /* Check the parameters */
  assert_param(IS_OB_WMSEC_CONFIG(WMSecConfig));
#if defined(FLASH_DBANK_SUPPORT)
  assert_param(IS_OB_WMSEC_AREA_EXCLUSIVE(WMSecConfig & (FLASH_BANK_1 | FLASH_BANK_2)));
#else /* FLASH_DBANK_SUPPORT */
  assert_param(IS_OB_WMSEC_AREA_EXCLUSIVE(WMSecConfig & FLASH_BANK_1));
#endif /* FLASH_DBANK_SUPPORT */
  assert_param(IS_FLASH_PAGE(WMSecStartPage));
  assert_param(IS_FLASH_PAGE(WMSecEndPage));
  assert_param(IS_FLASH_PAGE(WMHDPEndPage));

  /* Read SECWM registers */
  if ((WMSecConfig & OB_WMSEC_AREA1) != 0U)
  {
#if defined(FLASH_DBANK_SUPPORT)
    tmp_secwm1 = FLASH->SECWM1R1;
    tmp_secwm2 = FLASH->SECWM1R2;
#else /* FLASH_DBANK_SUPPORT */
    tmp_secwm1 = FLASH->SECWMR1;
    tmp_secwm2 = FLASH->SECWMR2;
#endif /* FLASH_DBANK_SUPPORT */
  }
#if defined(FLASH_DBANK_SUPPORT)
  else if ((WMSecConfig & OB_WMSEC_AREA2) != 0U)
  {
    tmp_secwm1 = FLASH->SECWM2R1;
    tmp_secwm2 = FLASH->SECWM2R2;
  }
#endif /* FLASH_DBANK_SUPPORT */
  else
  {
    /* Nothing to do */
  }

  /* Configure Secure Area */
  if ((WMSecConfig & OB_WMSEC_SECURE_AREA_CONFIG) != 0U)
  {
#if defined(FLASH_DBANK_SUPPORT)
    MODIFY_REG(tmp_secwm1, (FLASH_SECWM1R1_SECWM1_PSTRT | FLASH_SECWM1R1_SECWM1_PEND),
               ((WMSecEndPage << FLASH_SECWM1R1_SECWM1_PEND_Pos) | WMSecStartPage));
#else /* FLASH_DBANK_SUPPORT */
    MODIFY_REG(tmp_secwm1, (FLASH_SECWMR1_SECWM_PSTRT | FLASH_SECWMR1_SECWM_PEND),
               ((WMSecEndPage << FLASH_SECWMR1_SECWM_PEND_Pos) | WMSecStartPage));
#endif /* FLASH_DBANK_SUPPORT */
  }

  /* Configure Secure Hide Area */
  if ((WMSecConfig & OB_WMSEC_HDP_AREA_CONFIG) != 0U)
  {
#if defined(FLASH_DBANK_SUPPORT)
    tmp_secwm2 &= (~FLASH_SECWM1R2_HDP1_PEND);
    tmp_secwm2 |= (WMHDPEndPage << FLASH_SECWM1R2_HDP1_PEND_Pos);
#else /* FLASH_DBANK_SUPPORT */
    tmp_secwm2 &= (~FLASH_SECWMR2_HDP_PEND);
    tmp_secwm2 |= (WMHDPEndPage << FLASH_SECWMR2_HDP_PEND_Pos);
#endif /* FLASH_DBANK_SUPPORT */
  }

  /* Enable Secure Hide Area */
  if ((WMSecConfig & OB_WMSEC_HDP_AREA_ENABLE) != 0U)
  {
#if defined(FLASH_DBANK_SUPPORT)
    tmp_secwm2 |= FLASH_SECWM1R2_HDP1EN;
#else /* FLASH_DBANK_SUPPORT */
    tmp_secwm2 |= FLASH_SECWMR2_HDPEN;
#endif /* FLASH_DBANK_SUPPORT */
  }

  /* Disable Secure Hide Area */
  if ((WMSecConfig & OB_WMSEC_HDP_AREA_DISABLE) != 0U)
  {
#if defined(FLASH_DBANK_SUPPORT)
    tmp_secwm2 &= (~FLASH_SECWM1R2_HDP1EN);
#else /* FLASH_DBANK_SUPPORT */
#if defined(FLASH_HDP_BYTE_VALUE_SUPPORT)
    MODIFY_REG(tmp_secwm2, FLASH_SECWMR2_HDPEN, (0xB4U << FLASH_SECWMR2_HDPEN_Pos));
#else /* FLASH_HDP_BYTE_VALUE_SUPPORT */
    tmp_secwm2 &= (~FLASH_SECWMR2_HDPEN);
#endif /* FLASH_HDP_BYTE_VALUE_SUPPORT */
#endif /* FLASH_DBANK_SUPPORT */
  }

  /* Write SECWM registers */
  if ((WMSecConfig & OB_WMSEC_AREA1) != 0U)
  {
#if defined(FLASH_DBANK_SUPPORT)
    FLASH->SECWM1R1 = tmp_secwm1;
    FLASH->SECWM1R2 = tmp_secwm2;
#else /* FLASH_DBANK_SUPPORT */
    FLASH->SECWMR1 = tmp_secwm1;
    FLASH->SECWMR2 = tmp_secwm2;
#endif /* FLASH_DBANK_SUPPORT */
  }
#if defined(FLASH_DBANK_SUPPORT)
  else if ((WMSecConfig & OB_WMSEC_AREA2) != 0U)
  {
    FLASH->SECWM2R1 = tmp_secwm1;
    FLASH->SECWM2R2 = tmp_secwm2;
  }
#endif /* FLASH_DBANK_SUPPORT */
  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief  Configure the boot lock.
  * @param  BootLockConfig Specifies the activation of the BOOT_LOCK.
  *          This parameter can be one of the following values:
  *            @arg @ref OB_BOOT_LOCK_DISABLE Boot Lock mode deactivated
  *            @arg @ref OB_BOOT_LOCK_ENABLE Boot Lock mode activated
  * @retval None
  */
static void FLASH_OB_BootLockConfig(uint32_t BootLockConfig)
{
  /* Check the parameters */
  assert_param(IS_OB_BOOT_LOCK(BootLockConfig));

  /* Configure the option bytes register */
  MODIFY_REG(FLASH->SECBOOTADD0R, FLASH_SECBOOTADD0R_BOOT_LOCK, BootLockConfig);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Configure the boot address.
  *
  * @param  BootAddrConfig specifies the area to be configured.
  *          This parameter can be one of the following values:
  *            @arg @ref OB_BOOTADDR_NS0 Non-secure boot address 0
  *            @arg @ref OB_BOOTADDR_NS1 Non-secure boot address 1
  *            @arg @ref OB_BOOTADDR_SEC0 Secure boot address 0
  *
  * @param  BootAddr Specifies the address used for the boot
  *          This parameter can be page number between 0 and 0xFFFFFF00
  *
  * @retval None
  */
static void FLASH_OB_BootAddrConfig(uint32_t BootAddrConfig, uint32_t BootAddr)
{
  /* Check the parameters */
  assert_param(IS_OB_BOOTADDR_CONFIG(BootAddrConfig));

  if (BootAddrConfig == OB_BOOTADDR_NS0)
  {
    MODIFY_REG(FLASH->NSBOOTADD0R, FLASH_NSBOOTADD0R_NSBOOTADD0, BootAddr);
  }
  else if (BootAddrConfig == OB_BOOTADDR_NS1)
  {
    MODIFY_REG(FLASH->NSBOOTADD1R, FLASH_NSBOOTADD1R_NSBOOTADD1, BootAddr);
  }
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  else if (BootAddrConfig == OB_BOOTADDR_SEC0)
  {
    MODIFY_REG(FLASH->SECBOOTADD0R, FLASH_SECBOOTADD0R_SECBOOTADD0, BootAddr);
  }
#endif /* __ARM_FEATURE_CMSE */
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Return the FLASH Write Protection Option Bytes value.
  *
  * @param[in]  WRPArea Specifies the area to be returned.
  *              This parameter can be one of the following values:
  *              @arg @ref OB_WRPAREA_BANK1_AREAA Flash Bank 1 Area A
  *              @arg @ref OB_WRPAREA_BANK1_AREAB Flash Bank 1 Area B
#if defined(FLASH_DBANK_SUPPORT)
  *              @arg @ref OB_WRPAREA_BANK2_AREAA Flash Bank 2 Area A
  *              @arg @ref OB_WRPAREA_BANK2_AREAB Flash Bank 2 Area B
#endif
  *
  * @param[out]  WRPStartOffset Specifies the address where to copied the start page
  *                             of the write protected area
  *
  * @param[out]  WRPEndOffset Specifies the address where to copied the end page of
  *                           the write protected area
  *
  * @param[out]  WRPLock Specifies the lock status of the write protected area.
  *              The returned value can be ENABLE or DISABLE
  *
  * @retval None
  */
static void FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t *WRPStartOffset, uint32_t *WRPEndOffset, FunctionalState *WRPLock)
{
  /* Get the configuration of the write protected area */
  if (WRPArea == OB_WRPAREA_BANK1_AREAA)
  {
#if defined(FLASH_DBANK_SUPPORT)
    *WRPStartOffset = READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_PEND) >> FLASH_WRP1AR_WRP1A_PEND_Pos);
    *WRPLock = (READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_UNLOCK) != 0U) ? DISABLE : ENABLE;
#else /* FLASH_DBANK_SUPPORT */
    *WRPStartOffset = READ_BIT(FLASH->WRPAR, FLASH_WRPAR_WRPA_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRPAR, FLASH_WRPAR_WRPA_PEND) >> FLASH_WRPAR_WRPA_PEND_Pos);
    *WRPLock = (READ_BIT(FLASH->WRPAR, FLASH_WRPAR_UNLOCK) != 0U) ? DISABLE : ENABLE;
#endif /* FLASH_DBANK_SUPPORT */
  }
  else if (WRPArea == OB_WRPAREA_BANK1_AREAB)
  {
#if defined(FLASH_DBANK_SUPPORT)
    *WRPStartOffset = READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_PEND) >> FLASH_WRP1BR_WRP1B_PEND_Pos);
    *WRPLock = (READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_UNLOCK) != 0U) ? DISABLE : ENABLE;
#else /* FLASH_DBANK_SUPPORT */
    *WRPStartOffset = READ_BIT(FLASH->WRPBR, FLASH_WRPBR_WRPB_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRPBR, FLASH_WRPBR_WRPB_PEND) >> FLASH_WRPBR_WRPB_PEND_Pos);
    *WRPLock = (READ_BIT(FLASH->WRPBR, FLASH_WRPBR_UNLOCK) != 0U) ? DISABLE : ENABLE;
#endif /* FLASH_DBANK_SUPPORT */
  }
#if defined(FLASH_DBANK_SUPPORT)
  else if (WRPArea == OB_WRPAREA_BANK2_AREAA)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP2AR, FLASH_WRP2AR_WRP2A_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP2AR, FLASH_WRP2AR_WRP2A_PEND) >> FLASH_WRP2AR_WRP2A_PEND_Pos);
    *WRPLock = (READ_BIT(FLASH->WRP2AR, FLASH_WRP2AR_UNLOCK) != 0U) ? DISABLE : ENABLE;
  }
  else if (WRPArea == OB_WRPAREA_BANK2_AREAB)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP2BR, FLASH_WRP2BR_WRP2B_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP2BR, FLASH_WRP2BR_WRP2B_PEND) >> FLASH_WRP2BR_WRP2B_PEND_Pos);
    *WRPLock = (READ_BIT(FLASH->WRP2BR, FLASH_WRP2BR_UNLOCK) != 0U) ? DISABLE : ENABLE;
  }
#endif /* FLASH_DBANK_SUPPORT */
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Return the FLASH Read Protection level.
  * @retval FLASH ReadOut Protection Level
  *         This return value can be one of the following values:
  *            @arg @ref OB_RDP_LEVEL_0 No protection
  *            @arg @ref OB_RDP_LEVEL_0_5 No debug access to secure area
  *            @arg @ref OB_RDP_LEVEL_1 Read protection of the memory
  *            @arg @ref OB_RDP_LEVEL_2 Full chip protection
  */
static uint32_t FLASH_OB_GetRDP(void)
{
  uint32_t rdp_level = READ_BIT(FLASH->OPTR, FLASH_OPTR_RDP);

  if ((rdp_level != OB_RDP_LEVEL_0) && (rdp_level != OB_RDP_LEVEL_0_5) && (rdp_level != OB_RDP_LEVEL_2))
  {
    return (OB_RDP_LEVEL_1);
  }
  else
  {
    return (rdp_level);
  }
}

/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval The FLASH User Option Bytes values.
  *         The return value can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
  *         @arg @ref FLASH_OB_USER_nRST_STOP, @arg @ref FLASH_OB_USER_nRST_STANDBY,
  *         @arg @ref FLASH_OB_USER_SRAM1_RST, @arg @ref FLASH_OB_USER_IWDG_SW,
  *         @arg @ref FLASH_OB_USER_IWDG_STOP, @arg @ref FLASH_OB_USER_IWDG_STANDBY,
  *         @arg @ref FLASH_OB_USER_WWDG_SW, @arg @ref FLASH_OB_USER_SRAM2_PAR,
  *         @arg @ref FLASH_OB_USER_SRAM2_RST, @arg @ref FLASH_OB_USER_nSWBOOT0,
  *         @arg @ref FLASH_OB_USER_nBOOT0 and @arg @ref OB_USER_TZEN(*)
  * (*) Feature not available on all devices of the family
  */
static uint32_t FLASH_OB_GetUser(void)
{
  uint32_t user_config = READ_REG(FLASH->OPTR);
  CLEAR_BIT(user_config, FLASH_OPTR_RDP);

  return user_config;
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Return the watermarked-based secure area configuration.
  *
  * @param  WMSecConfig [in/out] Specifies the area to be returned.
  *                  This parameter can be one of the following values:
  *                   @arg @ref OB_WMSEC_AREA1 select Flash Secure Area 1
  *                  When return from the function, this parameter will be a combinaison of the following values:
  *                   @arg @ref OB_WMSEC_AREA1 selected Flash Secure Area 1
  *                   @arg @ref OB_WMSEC_HDP_AREA_ENABLE Secure Hide Area in Secure Area enabled
  *                   @arg @ref OB_WMSEC_HDP_AREA_DISABLE Secure Hide Area in Secure Area disabled
  *
  * @param  WMSecStartPage [out] Specifies the start page of the secure area
  *
  * @param  WMSecEndPage [out]   Specifies the end page of the secure area
  *
  * @param  WMHDPEndPage [out]   Specifies the end page of the secure hide area
  *
  * @retval None
  */
static void FLASH_OB_GetWMSEC(uint32_t *WMSecConfig, uint32_t *WMSecStartPage, uint32_t *WMSecEndPage,
                              uint32_t *WMHDPEndPage)
{
  uint32_t tmp_secwm1 = 0U;
  uint32_t tmp_secwm2 = 0U;

  /* Check the parameters */
  assert_param(IS_OB_WMSEC_CONFIG(*WMSecConfig));
#if defined(FLASH_DBANK_SUPPORT)
  assert_param(IS_FLASH_BANK_EXCLUSIVE((*WMSecConfig) & (FLASH_BANK_1 | FLASH_BANK_2)));
#else /* FLASH_DBANK_SUPPORT */
  assert_param(IS_FLASH_BANK_EXCLUSIVE((*WMSecConfig) & FLASH_BANK_1));
#endif /* FLASH_DBANK_SUPPORT */

  /* Read SECWM registers */
  if (((*WMSecConfig) & OB_WMSEC_AREA1) != 0U)
  {
#if defined(FLASH_DBANK_SUPPORT)
    tmp_secwm1 = FLASH->SECWM1R1;
    tmp_secwm2 = FLASH->SECWM1R2;
#else /* FLASH_DBANK_SUPPORT */
    tmp_secwm1 = FLASH->SECWMR1;
    tmp_secwm2 = FLASH->SECWMR2;
#endif /* FLASH_DBANK_SUPPORT */
  }
#if defined(FLASH_DBANK_SUPPORT)
  else if (((*WMSecConfig) & OB_WMSEC_AREA2) != 0U)
  {
    tmp_secwm1 = FLASH->SECWM2R1;
    tmp_secwm2 = FLASH->SECWM2R2;
  }
#endif /* FLASH_DBANK_SUPPORT */
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }

  /* Configuration of secure area */
#if defined(FLASH_DBANK_SUPPORT)
  *WMSecStartPage = (tmp_secwm1 & FLASH_SECWM1R1_SECWM1_PSTRT);
  *WMSecEndPage = ((tmp_secwm1 & FLASH_SECWM1R1_SECWM1_PEND) >> FLASH_SECWM1R1_SECWM1_PEND_Pos);
#else /* FLASH_DBANK_SUPPORT */
  *WMSecStartPage = (tmp_secwm1 & FLASH_SECWMR1_SECWM_PSTRT);
  *WMSecEndPage = ((tmp_secwm1 & FLASH_SECWMR1_SECWM_PEND) >> FLASH_SECWMR1_SECWM_PEND_Pos);
#endif /* FLASH_DBANK_SUPPORT */

  /* Configuration of secure hide area */
#if defined(FLASH_DBANK_SUPPORT)
  *WMHDPEndPage = ((tmp_secwm2 & FLASH_SECWM1R2_HDP1_PEND) >> FLASH_SECWM1R2_HDP1_PEND_Pos);
#else /* FLASH_DBANK_SUPPORT */
  *WMHDPEndPage = ((tmp_secwm2 & FLASH_SECWMR2_HDP_PEND) >> FLASH_SECWMR2_HDP_PEND_Pos);
#endif /* FLASH_DBANK_SUPPORT */

#if defined(FLASH_DBANK_SUPPORT)
  if ((tmp_secwm2 & FLASH_SECWM1R2_HDP1EN) == 0U)
#else /* FLASH_DBANK_SUPPORT */
#if defined(FLASH_HDP_BYTE_VALUE_SUPPORT)
  if ((tmp_secwm2 & FLASH_SECWMR2_HDPEN) == (0xB4U << FLASH_SECWMR2_HDPEN_Pos))
#else /* FLASH_HDP_BYTE_VALUE_SUPPORT */
  if ((tmp_secwm2 & FLASH_SECWMR2_HDPEN) == 0U)
#endif /* FLASH_HDP_BYTE_VALUE_SUPPORT */
#endif /* FLASH_DBANK_SUPPORT */
  {
    *WMSecConfig = ((*WMSecConfig) | OB_WMSEC_HDP_AREA_DISABLE);
  }
  else
  {
    *WMSecConfig = ((*WMSecConfig) | OB_WMSEC_HDP_AREA_ENABLE);
  }
}

/**
  * @brief  Return the boot lock configuration.
  *
  * @retval  Value of Boot Lock configuration
  *          It can be one of the following values:
  *            @arg @ref OB_BOOT_LOCK_DISABLE Boot Lock mode deactivated
  *            @arg @ref OB_BOOT_LOCK_ENABLE Boot Lock mode activated
  */
static uint32_t FLASH_OB_GetBootLock(void)
{
  return (FLASH->SECBOOTADD0R & FLASH_SECBOOTADD0R_BOOT_LOCK);
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Return the boot address.
  *
  * @param[in]  BootAddrConfig Specifies the area to be returned
  *              This parameter can be one of the following values:
  *                @arg @ref OB_BOOTADDR_NS0 Non-secure boot address 0
  *                @arg @ref OB_BOOTADDR_NS1 Non-secure boot address 1
  *                @arg @ref OB_BOOTADDR_SEC0 Secure boot address 0
  *
  * @param[out]  BootAddr specifies the boot address value
  *
  * @retval None
  */
static void FLASH_OB_GetBootAddr(uint32_t BootAddrConfig, uint32_t *BootAddr)
{
  if (BootAddrConfig == OB_BOOTADDR_NS0)
  {
    *BootAddr = (FLASH->NSBOOTADD0R & FLASH_NSBOOTADD0R_NSBOOTADD0);
  }
  else if (BootAddrConfig == OB_BOOTADDR_NS1)
  {
    *BootAddr = (FLASH->NSBOOTADD1R & FLASH_NSBOOTADD1R_NSBOOTADD1);
  }
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  else if (BootAddrConfig == OB_BOOTADDR_SEC0)
  {
    *BootAddr = (FLASH->SECBOOTADD0R & FLASH_SECBOOTADD0R_SECBOOTADD0);
  }
#endif /* __ARM_FEATURE_CMSE */
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_FLASH_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
