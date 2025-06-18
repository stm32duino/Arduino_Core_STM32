/**
  ******************************************************************************
  * @file    stm32wb0x_hal_flash_ex.c
  * @author  MCD Application Team
  * @brief   Extended FLASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the FLASH extended peripheral:
  *           + Extended programming operations functions
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  ******************************************************************************
 @verbatim
 ==============================================================================
                   ##### Flash Extended features #####
  ==============================================================================

  [..] The FLASH interface contains the following additional features

       (+) Single bank memory organization
       (+) Readout protection
       (+) WRERP protection


                        ##### How to use this driver #####
 ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory.
       It includes
      (#) Flash Memory Erase functions:
           (++) Erase function: Erase page, erase all sectors
           (++) There are two modes of erase :
             (+++) Polling Mode using HAL_FLASHEx_Erase()
             (+++) Interrupt Mode using HAL_FLASHEx_Erase_IT()
      (#)  OTP Memory Programming functions:
           (++) There are two modes of OTP program :
             (+++) Polling Mode using HAL_FLASHEx_OTPWRite()
             (+++) Interrupt Mode using HAL_FLASHEx_OTPWrite_IT()


 @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal.h"

/** @addtogroup STM32WB0x_HAL_Driver
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
/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */

static void              FLASH_MassErase(void);
static void              FLASH_MassRead(void);
static void              FLASH_Program_OTPWord(uint32_t Address, uint32_t Data);
static void              FLASH_KeyWrite(void);
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
  * @param[in]  pEraseInit Pointer to an @ref FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * @param[out]  PageError Pointer to variable that contains the configuration
  *         information on faulty page in case of error (0xFFFFFFFF means that all
  *         the pages have been correctly erased)
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status;
  uint32_t index;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPE_ERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Verify that next operation can be proceed */
  if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
  {
    /* Mass erase to be done */
    FLASH_MassErase();

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }
  else
  {
    /*Initialization of PageError variable*/
    *PageError = 0xFFFFFFFFU;

    for (index = pEraseInit->Page; index < (pEraseInit->Page + pEraseInit->NbPages); index++)
    {
      /* Start erase page */
      FLASH_PageErase(index);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

      if (status != HAL_OK)
      {
        /* In case of error, stop erase procedure and return the faulty address */
        *PageError = index;
        break;
      }
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}


/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages with interrupt enabled.
  * @param  pEraseInit Pointer to an @ref FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status;
  /* Check the parameters */
  assert_param(IS_FLASH_TYPE_ERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* save procedure for interrupt treatment */
  pFlash.ProcedureOnGoing = pEraseInit->TypeErase;

  /* Verify that next operation can be proceed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status != HAL_OK)
  {
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  else
  {
    /* Enable End of Operation and Error interrupts */
    __HAL_FLASH_ENABLE_IT(FLASH_IT_CMDDONE | FLASH_IT_CMDERR | FLASH_IT_ILLCMD);

    if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
    {
      /* Set Page to 0 for Interrupt callback management */
      pFlash.Page = 0;

      /* Proceed to Mass Erase */
      FLASH_MassErase();
    }
    else
    {
      /* Erase by page to be done */
      pFlash.NbPagesToErase = pEraseInit->NbPages;
      pFlash.Page = pEraseInit->Page;

      /*Erase 1st page and wait for IT */
      FLASH_PageErase(pEraseInit->Page);
    }
  }

  /* return status */
  return HAL_OK;
}

/**
  * @brief  Program a word at a specified OTP address.
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed.
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OTPWrite(uint32_t Address, uint32_t Data)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_ADDR_ALIGNED_32BITS(Address));
  assert_param(IS_FLASH_PROGRAM_OTP_ADDRESS(Address));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Program a word (32-bit) at a specified OTP address */
  FLASH_Program_OTPWord(Address, Data);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}

/**
  * @brief  Program a word at a specified OTP address with interrupt enabled.
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OTPWrite_IT(uint32_t Address, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_ADDR_ALIGNED_32BITS(Address));
  assert_param(IS_FLASH_PROGRAM_OTP_ADDRESS(Address));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Set internal variables used by the IRQ handler */
  pFlash.ProcedureOnGoing = FLASH_CMD_OTPWRITE;
  pFlash.Address = Address;

  /* Clear All IT pending flag */
  __HAL_FLASH_CLEAR_IT(FLASH_IT_CMDDONE | FLASH_IT_CMDSTART | FLASH_IT_CMDERR | FLASH_IT_ILLCMD);

  /* Enable End of Operation and Error interrupts */
  __HAL_FLASH_ENABLE_IT(FLASH_IT_CMDDONE | FLASH_IT_CMDERR | FLASH_IT_ILLCMD);

  /* Program a word (32-bit) at a specified address */
  FLASH_Program_OTPWord(Address, Data);

  /* return status */
  return HAL_OK;
}

/**
  * @brief  Page Protection function. It allows protecting from write and page erase
  *         by group of 8 pages.
  * @param  pageProtectionStruct Pointer to a @ref FLASH_PageProtectionTypeDef enumeration. Bitfield with
  *         the write/page erase protection for group of 8 pages (group 0: Flash pages 0 to 7, group 1: Flash
  *         pages 8 to 15... i.e. if pageProt=0x0C the function will protect pages from 16 to 31).
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_PageProtection(FLASH_PageProtectionTypeDef *pageProtectionStruct)
{
  /* Check Null pointer */
  if (pageProtectionStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(pageProtectionStruct->state));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

#if defined( STM32WB06) || defined( STM32WB07)
  uint32_t dev_cut_version;
  dev_cut_version = (LL_SYSCFG_GetDeviceVersion() << 4) | LL_SYSCFG_GetDeviceRevision();

  if (dev_cut_version == LL_BLUENRG_LP_CUT_10)
  {
    pageProtectionStruct->pageProt_1 = 0;
  }
#endif /* STM32WB06 || STM32WB07*/

  if (pageProtectionStruct->state == ENABLE)
  {
    FLASH->PAGEPROT0 |= pageProtectionStruct->pageProt_0;
    if (pageProtectionStruct->pageProt_1 != 0)
    {
      FLASH->PAGEPROT1 |= pageProtectionStruct->pageProt_1;
    }

  }
  else
  {
    FLASH->PAGEPROT0 &= ~pageProtectionStruct->pageProt_0;
    if (pageProtectionStruct->pageProt_1 != 0)
    {
      FLASH->PAGEPROT1 &= ~pageProtectionStruct->pageProt_1;
    }

  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return HAL_OK;

}

/**
  * @brief  Set Protection level configuration
  * @param  ProtectionLevel Level of protection
  *         This parameter can be a combination of all the following values:
  *         @arg @ref PROT_LEVEL_NONE
  *         @arg @ref PROT_LEVEL_1
  *         @arg @ref PROT_LEVEL_2
  *         @arg @ref PROT_LEVEL_3
  * @retval None
  */
HAL_StatusTypeDef HAL_FLASHEx_Protection_Config(uint32_t ProtectionLevel)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_PROTECTION_LEVEL(ProtectionLevel));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  FLASH->DATA2 = FLASH_DATAKEY2;
  FLASH->DATA3 = FLASH_DATAKEY3;

  if (ProtectionLevel == PROT_LEVEL_1)
  {
    FLASH->DATA0 = FLASH_KEY1;
    FLASH->DATA1 = FLASH_KEY1;
  }
  else if (ProtectionLevel == PROT_LEVEL_2)
  {
    FLASH->DATA0 = FLASH_KEY2;
    FLASH->DATA1 = FLASH_KEY2;
  }
  /* Configure KEYWRITE command */
  FLASH_KeyWrite();
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}


/**
  * @brief  Return the FLASH Protection level.
  * @retval FLASH Protection Level:
  *         This return value can be one of the following values:
  *            @arg @ref PROT_LEVEL_NONE
  *            @arg @ref PROT_LEVEL_1
  *            @arg @ref PROT_LEVEL_2
  *            @arg @ref PROT_LEVEL_3
  */
uint32_t HAL_FLASHEx_GetProtection_Level(void)
{
  uint32_t Prot_Key1 = READ_REG(FLASH->DATA0);
  uint32_t Prot_Key2 = READ_REG(FLASH->DATA1);

  if ((Prot_Key1 == FLASH_KEY1) && (Prot_Key2 == FLASH_KEY1))
  {
    return (PROT_LEVEL_1);
  }
  else if ((Prot_Key1 == FLASH_KEY2) && (Prot_Key2 == FLASH_KEY2))
  {
    return (PROT_LEVEL_2);
  }
  else if ((Prot_Key1 == FLASH_KEY0) && (Prot_Key2 == FLASH_KEY0))
  {
    return (PROT_LEVEL_NONE);
  }
  else
  {
    return (PROT_LEVEL_3);
  }
}

/**
  * @brief  Perform a mass read.
  * @param  pattern Specifies the expected value.
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_MassRead(uint32_t pattern)
{
  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Program a mass read  */
  FLASH_MassRead();

  /* Check FLASH End of Operation flag  */
  if ((FLASH->IRQSTAT & FLASH_FLAG_CMDDONE) == 0U)
  {
    /* Clear FLASH End of Operation pending bit */
    FLASH->IRQRAW = FLASH_FLAG_CMDDONE;
  }

  /* verify Flash content */
  if (FLASH->DATA0 != pattern)
  {
    return HAL_ERROR;
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return HAL_OK;
}

/**
  * @brief  Perform a LFSR signature  issued by a MASSREAD command
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_LFSRSignature(uint32_t *LFSR_Result)
{
  HAL_StatusTypeDef status;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Process Locked */
    __HAL_LOCK(&pFlash);

    /* Reset error code */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* Program a mass read  */
    FLASH_MassRead();

    /* Check FLASH End of Operation flag  */
    if ((FLASH->IRQSTAT & FLASH_FLAG_CMDDONE) == 0U)
    {
      /* Clear FLASH End of Operation pending bit */
      FLASH->IRQRAW = FLASH_FLAG_CMDDONE;
    }
    /* Return LFSRVAL result */
    (*LFSR_Result) = FLASH->LFSRVAL;

    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }

  return status;
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
  * @retval None
  */
static void FLASH_MassErase(void)
{
  /* Clear All Flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE | FLASH_FLAG_CMDSTART | FLASH_FLAG_CMDERR | FLASH_FLAG_ILLCMD);

  /* MASSERASE command */
  FLASH->COMMAND = FLASH_CMD_MASSERASE;
}

/**
  * @brief  Erase the specified FLASH memory page.
  * @param  Page FLASH page to erase
  *         This parameter must be a value between 0 and (max number of pages in Flash - 1)
  * @retval None
  */
void FLASH_PageErase(uint32_t Page)
{
  /* Check the parameters */
  assert_param(IS_FLASH_PAGE(Page));

  /* Clear All Flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE | FLASH_FLAG_CMDSTART | FLASH_FLAG_CMDERR | FLASH_FLAG_ILLCMD);

  FLASH->ADDRESS = (((Page * FLASH_PAGE_SIZE) >> 2) & FLASH_SIZE_MASK);

  /* Write the ERASE command */
  FLASH->COMMAND = FLASH_CMD_ERASE_PAGES;
}

/**
  * @brief  Mass read of FLASH memory.
  * @retval None
  */
static void FLASH_MassRead(void)
{
  /* Clear All Flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE | FLASH_FLAG_CMDSTART | FLASH_FLAG_CMDERR | FLASH_FLAG_ILLCMD);

  /* MASSERASE command */
  FLASH->COMMAND = FLASH_CMD_MASSREAD;
}

/**
  * @brief  Program a word (32-bit) at a specified OTP address.
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed.
  * @retval None
  */
static void FLASH_Program_OTPWord(uint32_t Address, uint32_t Data)
{
  uint32_t otp_address;
  uint32_t addr_offset;

  /* Clear All Flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE | FLASH_FLAG_CMDSTART | FLASH_FLAG_CMDERR | FLASH_FLAG_ILLCMD);

  addr_offset = Address - OTP_AREA_BASE;
  otp_address = (((addr_offset & 0x300) >> 2) | ((addr_offset & 0xFF) >> 2));
  /* Load the word address */
  FLASH->ADDRESS = otp_address;

  /* Load the data to program */
  FLASH->DATA0 = Data;

  /* Load the OTP WRITE command */
  FLASH->COMMAND = FLASH_CMD_OTPWRITE;
}

/**
  * @brief Write the customer key used to protect the main Flash
  * @retval None
  */
static void FLASH_KeyWrite(void)
{
  /* Clear All Flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE | FLASH_FLAG_CMDSTART | FLASH_FLAG_CMDERR | FLASH_FLAG_ILLCMD);
  /* MASSREAD command */
  FLASH->COMMAND = FLASH_CMD_KEYWRITE;
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
