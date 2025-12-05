/**
  ******************************************************************************
  * @file    stm32wl3x_hal_flash.c
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
 @verbatim
 ==============================================================================
                   ##### Flash Extended features #####
  ==============================================================================

  [..] The FLASH interface contains the following additional features

       (+) Single bank memory organization
       (+) Readout protection
       (+) Write protection


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
#include "stm32wl3x_ll_system.h"
#include "stm32wl3x_hal.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx FLASHEx
  * @brief FLASH Extended HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
static void              FLASH_MassErase(void);
static void              FLASH_Program_OTPWord(uint32_t Address, uint32_t Data);
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
  /* Check the parameters */
  assert_param(IS_FLASH_TYPE_ERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_OK;

  /* save procedure for interrupt treatment */
  if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
  {
    pFlash.ProcedureOnGoing = FLASH_CMD_MASSERASE;
  }
  else
  {
    pFlash.ProcedureOnGoing = FLASH_CMD_ERASE_PAGES;
  }

  /* Clear All IT pending flag */
  __HAL_FLASH_CLEAR_IT(FLASH_IT_CMDDONE | FLASH_IT_CMDSTART | FLASH_IT_CMDERR | FLASH_IT_ILLCMD);

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
  pFlash.ErrorCode = HAL_OK;

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
  pFlash.ErrorCode = HAL_OK;

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
  * @brief  Page Protection function. It allows protecting from write
  *         by group of 8 pages.
  * @param  pageProtectionStruct Bitfield with the write/page erase protection for group of 8 pages.
  *         (group 0: Flash pages 0 to 7, group 1: Flash pages 8 to 15 ...)
  *         @ref FLASH_PageProtectionTypeDef.
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
