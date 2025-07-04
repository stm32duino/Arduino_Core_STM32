/**
  ******************************************************************************
  * @file    stm32wb0x_hal_flash.c
  * @author  MCD Application Team
  * @brief   FLASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the internal FLASH memory:
  *           + Program operations functions
  *           + Memory Control functions
  *           + Peripheral Errors functions
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
                        ##### FLASH peripheral features #####
  ==============================================================================
    [..]
      The Flash memory interface implements the erase and program Flash memory operations
      and write/erase protection mechanisms.

    [..]
      The FLASH main features are:
      (+) Flash memory read operations
      (+) Flash memory program/erase operations
      (+) Read / write protections

                        ##### How to use this driver #####
  ==============================================================================
    [..]
      This driver provides functions and macros to configure and program the FLASH
      memory.

      (#) Flash Memory IO Programming functions:
           (++) Program functions: word and burst program
           (++) There are two modes of programming:
            (+++) Polling mode using HAL_FLASH_Program() function
            (+++) Interrupt mode using HAL_FLASH_Program_IT() function
            (+++) Polling mode using HAL_FLASH_BurstProgram() function
            (+++) Interrupt mode using HAL_FLASH_BurstProgram_IT() function

      (#) Interrupts and flags management functions:
           (++) Handle FLASH interrupts by calling HAL_FLASH_IRQHandler()
           (++) Callback functions are called when the flash operations are finished :
                HAL_FLASH_EndOfOperationCallback() when everything is ok, otherwise
                HAL_FLASH_OperationErrorCallback()
           (++) Get error flag status by calling HAL_GetError()

    [..]
      In addition to these functions, this driver includes a set of macros allowing
      to handle the following operations:
       (+) Set the wait state latency
       (+) Enable/Disable the Flash interrupts
       (+) Monitor the Flash flags status

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Variables FLASH Private Variables
  * @{
  */
/**
  * @brief  Variable used for Program/Erase sectors under interruption
  */

FLASH_ProcessTypeDef pFlash = {.Lock = HAL_UNLOCKED, \
                               .ErrorCode = HAL_FLASH_ERROR_NONE, \
                               .ProcedureOnGoing = 0U, \
                               .Address = 0U, \
                               .Page = 0U, \
                               .NbPagesToErase = 0U
                              };
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
static void          FLASH_Program_Word(uint32_t Address, uint32_t Data);
static void          FLASH_Program_Burst(uint32_t Address, uint32_t DataAddress);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Functions FLASH Exported Functions
  * @{
  */

/** @defgroup FLASH_Exported_Functions_Group1 Programming operation functions
  *  @brief   Programming operation functions
  *
@verbatim
 ===============================================================================
                  ##### Programming operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the FLASH
    program operations.

@endverbatim
  * @{
  */

/**
  * @brief  Program a data at a specified address.
  * @param  TypeProgram Indicate the way to program at a specified address
  *                This parameter can be a value of @ref FLASH_TYPE_PROGRAM
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed
  *                This parameter is the data for the word program and the address where
  *                are stored the data for the burst program.
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_ADDR_ALIGNED_32BITS(Address));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Verify that next operation can be proceed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if (TypeProgram == FLASH_TYPEPROGRAM_WORD)
    {
      /* Check the parameters */
      assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

      /* Program a word (32-bit) at a specified address */
      FLASH_Program_Word(Address, Data);
    }
    else
    {
      /* Check the parameters */
      assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

      /* Program 4 word starting from a specified address */
      FLASH_Program_Burst(Address, Data);
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}

/**
  * @brief  Program a word or burst program of a row at a specified address with interrupt enabled.
  * @param  TypeProgram Indicate the way to program at a specified address.
  *                           This parameter can be a value of @ref FLASH_TYPE_PROGRAM
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed
  *                This parameter is the data for the double word program and the address where
  *                are stored the data for the row fast program.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t Data)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_ADDR_ALIGNED_32BITS(Address));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

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
    pFlash.ProcedureOnGoing = TypeProgram;
    pFlash.Address = Address;

    /* Clear All IT pending flag */
    __HAL_FLASH_CLEAR_IT(FLASH_IT_CMDDONE | FLASH_IT_CMDSTART | FLASH_IT_CMDERR | FLASH_IT_ILLCMD);

    /* Enable End of Operation and Error interrupts */
    __HAL_FLASH_ENABLE_IT(FLASH_IT_CMDDONE | FLASH_IT_CMDERR | FLASH_IT_ILLCMD);

    if (TypeProgram == FLASH_TYPEPROGRAM_WORD)
    {
      /* Check the parameters */
      assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

      /* Program a word (32-bit) at a specified address */
      FLASH_Program_Word(Address, Data);
    }
    else
    {
      /* Check the parameters */
      assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));
      /* Program 4 word starting from a specified address */
      FLASH_Program_Burst(Address, Data);
    }
  }

  /* return status */
  return status;
}

/**
  * @brief Handle FLASH interrupt request.
  * @retval None
  */
void HAL_FLASH_IRQHandler(void)
{
  uint32_t param=0;
  uint32_t error;

  /* Save flash errors. */
  error = FLASH->IRQSTAT & FLASH_FLAG_ALL_ERRORS;

  /* A] Set parameter for user or error callbacks */

  /* Check if the operation was a program or erase */
  if ((pFlash.ProcedureOnGoing & (FLASH_CMD_WRITE | FLASH_CMD_BURSTWRITE | FLASH_CMD_OTPWRITE)) != 0x00U)
  {
    /* Return address being programmed */
    param = pFlash.Address;
  }
  else if ((pFlash.ProcedureOnGoing & (FLASH_CMD_MASSERASE | FLASH_CMD_ERASE_PAGES)) != 0x00U)
  {
    /* return page number being erased (0 for mass erase) */
    param = pFlash.Page;
  }
  else
  {
    /* Nothing to do */
  }

  /* B] Check errors */
  if (error != 0x00U)
  {
    /* Save the error code */
    pFlash.ErrorCode |= error;

    /* Clear error flags */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    /* Stop the procedure ongoing */
    pFlash.ProcedureOnGoing = FLASH_TYPENONE;

    /* Error callback */
    HAL_FLASH_OperationErrorCallback(param);
  }

  /* C] Check FLASH End of Operation flag */
  if (__HAL_FLASH_GET_IT(FLASH_IT_CMDDONE))
  {

    /* Clear FLASH End of Operation IT flag pending bit */
    __HAL_FLASH_CLEAR_IT(FLASH_IT_CMDDONE);

    /* Clear FLASH End of Operation pending bit */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE);


    if (pFlash.ProcedureOnGoing == FLASH_CMD_ERASE_PAGES)
    {
      /* Nb of pages to erased can be decreased */
      pFlash.NbPagesToErase--;

      /* Check if there are still pages to erase */
      if (pFlash.NbPagesToErase != 0x00u)
      {
        /* Increment page number */
        pFlash.Page++;
        FLASH_PageErase(pFlash.Page);
      }
      else
      {
        pFlash.Page = 0xFFFFFFFFU;
        pFlash.ProcedureOnGoing = FLASH_TYPENONE;
      }
    }
    else
    {
      /*Stop the ongoing procedure */
      pFlash.Page = 0xFFFFFFFFU;
      pFlash.ProcedureOnGoing = FLASH_TYPENONE;
    }

    /* User callback */
    HAL_FLASH_EndOfOperationCallback(param);
  }

  if (pFlash.ProcedureOnGoing == FLASH_TYPENONE)
  {
    /* Disable End of Operation and Error interrupts */
    __HAL_FLASH_DISABLE_IT(FLASH_IT_CMDDONE | FLASH_IT_CMDERR | FLASH_IT_ILLCMD);

    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
}

/**
  * @brief  FLASH end of operation interrupt callback.
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure
  *                  Mass Erase: 0
  *                  Page Erase: Page which has been erased
  *                  Program: Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ReturnValue);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASH_EndOfOperationCallback could be implemented in the user file
   */
}

/**
  * @brief  FLASH operation error interrupt callback.
  * @param  ReturnValue The value saved in this parameter depends on the ongoing procedure
  *                 Mass Erase: 0
  *                 Page Erase: Page number which returned an error
  *                 Program: Address which was selected for data program
  * @retval None
  */
__weak void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ReturnValue);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FLASH_OperationErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions_Group2 Peripheral Errors functions
  *  @brief   Peripheral Errors functions
  *
@verbatim
 ===============================================================================
                ##### Peripheral Errors functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time Errors of the FLASH peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Get the specific FLASH error flag.
  * @retval FLASH_ErrorCode The returned value can be
  *            @arg @ref HAL_FLASH_ERROR_NONE    No error set
  *            @arg @ref HAL_FLASH_ERROR_OP      FLASH Operation error
  *            @arg @ref HAL_FLASH_ERROR_ILLCMD  FLASH Illegal command
  */
uint32_t HAL_FLASH_GetError(void)
{
  return pFlash.ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @addtogroup FLASH_Private_Functions
  * @{
  */

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout Maximum flash operation timeout
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  /* Wait for the FLASH operation to complete by polling on CMDDONE flag to be set.
     If the FLASH operation fails, an error flag will be set */
  while (__HAL_FLASH_GET_FLAG(FLASH_FLAG_CMDDONE) != SET)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((HAL_GetTick() - tickstart) >= Timeout)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Check flash errors */
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_ALL_ERRORS))
  {
    /* Save the error code */
    pFlash.ErrorCode |= FLASH->IRQSTAT;

    /* Clear error flags */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Program a word (32-bit) at a specified address.
  * @param  Address Specifies the address to be programmed.
  * @param  Data Specifies the data to be programmed.
  * @retval None
  */
static void FLASH_Program_Word(uint32_t Address, uint32_t Data)
{
  /* Clear All Flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE | FLASH_FLAG_CMDSTART | FLASH_FLAG_CMDERR | FLASH_FLAG_ILLCMD);

  /* Load the word address */

  FLASH->ADDRESS = (((Address - FLASH_START_ADDR) >> 2) & FLASH_SIZE_MASK);

  /* Load the data to program */
  FLASH->DATA0 = Data;

  /* Load the WRITE command */
  FLASH->COMMAND = FLASH_CMD_WRITE;
}

/**
  * @brief  Program 4 words starting from the specified address.
  * @param  Address Specifies the address to be programmed.
  * @param  DataAddress Specifies the address where the data are stored.
  * @retval None
  */
static void FLASH_Program_Burst(uint32_t Address, uint32_t DataAddress)
{
  uint32_t *src_addr  = (uint32_t *)DataAddress;

  /* Clear All Flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_CMDDONE | FLASH_FLAG_CMDSTART | FLASH_FLAG_CMDERR | FLASH_FLAG_ILLCMD);

  /* Load the word address */
  FLASH->ADDRESS = (((Address - FLASH_START_ADDR) >> 2) & FLASH_SIZE_MASK);
  FLASH->DATA0 = *src_addr;
  src_addr = src_addr + 1;
  FLASH->DATA1 = *src_addr;
  src_addr = src_addr + 1;
  FLASH->DATA2 = *src_addr;
  src_addr = src_addr + 1;
  FLASH->DATA3 = *src_addr;

  /* Load the BURST WRITE command */
  FLASH->COMMAND = FLASH_CMD_BURSTWRITE;
}

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
