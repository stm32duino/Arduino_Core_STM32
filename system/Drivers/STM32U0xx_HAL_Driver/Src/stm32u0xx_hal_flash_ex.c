/**
  ******************************************************************************
  * @file    stm32u0xx_hal_flash_ex.c
  * @author  MCD Application Team
  * @brief   Extended FLASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the FLASH extended peripheral:
  *           + Extended programming operations functions
  *
 @verbatim
 ==============================================================================
                   ##### Flash Extended features #####
  ==============================================================================

  [..] Comparing to other previous devices, the FLASH interface for STM32U0xx
       devices contains the following additional features

       (+) Capacity up to 128 Kbytes with single bank architecture supporting read-while-write
           capability (RWW)
       (+) Write protection
       (+) Single bank memory organization
       (+) Hide Protection areas

                        ##### How to use this driver #####
 ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory
       of all STM32U0xx devices. It includes
      (#) Flash Memory Erase functions:
           (++) Lock and Unlock the FLASH interface using HAL_FLASH_Unlock() and
                HAL_FLASH_Lock() functions
           (++) Erase function: Erase page, erase all sectors
           (++) There are two modes of erase :
             (+++) Polling Mode using HAL_FLASHEx_Erase()
             (+++) Interrupt Mode using HAL_FLASHEx_Erase_IT()

      (#) Option Bytes Programming function: Use HAL_FLASHEx_OBProgram() to :
        (++) Set/Reset the write protection
        (++) Set the Read protection Level
        (++) Program the user Option Bytes
        (++) Set boot lock
        (++) Configure the Hide protection areas

      (#) Get Option Bytes Configuration function: Use HAL_FLASHEx_OBGetConfig() to :
        (++) Get the value of a write protection area
        (++) Know if the read protection is activated
        (++) Get the value of the user Option Bytes
        (++) Get the boot lock information
        (++) Get the configuration of Hide protection areas

      (#) Enable or disable debugger usage using HAL_FLASHEx_EnableDebugger and
          HAL_FLASHEx_DisableDebugger.

      (#) Check is flash content is empty or not using HAL_FLASHEx_FlashEmptyCheck.
          and modify this setting (for flash loader purpose e.g.) using
          HAL_FLASHEx_ForceFlashEmpty.

      (#) Enable HDP area protection using HAL_FLASHEx_EnableHDPProtection

 @endverbatim
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal.h"

/** @addtogroup STM32U0xx_HAL_Driver
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
static void               FLASH_MassErase(void);
static void               FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRDPEndOffset);
static void               FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t *WRPStartOffset, uint32_t *WRDPEndOffset);
static void               FLASH_OB_OptrConfig(uint32_t UserType, uint32_t UserConfig, uint32_t RDPLevel);
static uint32_t           FLASH_OB_GetRDP(void);
static uint32_t           FLASH_OB_GetUser(void);
void                      FLASH_OB_GetOEMKeyCRC(uint32_t *OEM1KeyCRC, uint32_t *OEM2KEYCRC);
static void               FLASH_OB_HDPConfig(uint32_t BootEntry, uint32_t HDPEndPage, uint32_t HDPEn);
static void               FLASH_OB_GetHDPConfig(uint32_t *BootEntry, uint32_t *HDPEndPage, uint32_t *HDPEn);
static void               FLASH_OB_RDPKeyConfig(uint32_t RDPKeyType, uint32_t RDPKey0, uint32_t RDPKey1,
                                                uint32_t RDPKey2, uint32_t RDPKey3);

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
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* For single bank product force Banks to Bank 1 */
    pEraseInit->Banks = FLASH_BANK_1;
    if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASS)
    {
      /* Proceed to Mass Erase */
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

      /* If operation is completed or interrupted, disable the Page Erase Bit */
      CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
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
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* save procedure for interrupt treatment */
  pFlash.ProcedureOnGoing = pEraseInit->TypeErase;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status != HAL_OK)
  {
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  else
  {
    /* For single bank product force Banks to Bank 1 */
    pEraseInit->Banks = FLASH_BANK_1;
    /* Store Bank number */
    pFlash.Banks = pEraseInit->Banks;

    /* Enable End of Operation and Error interrupts */
    FLASH->CR |= FLASH_CR_EOPIE | FLASH_CR_ERRIE;

    if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASS)
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
  return status;
}

/**
  * @brief  Program Option bytes.
  * @param  pOBInit Pointer to an @ref FLASH_OBProgramInitTypeDef structure that
  *         contains the configuration information for the programming.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of @ref HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account only
  *         - after an option bytes launch through the call of @ref HAL_FLASH_OB_Launch()
  *         - a Power On Reset
  *         - an exit from Standby or Shutdown mode.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  uint32_t optr;
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Write protection configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_WRP) != 0x00U)
  {
    /* Configure of Write protection on the selected area */
    FLASH_OB_WRPConfig(pOBInit->WRPArea, pOBInit->WRPStartOffset, pOBInit->WRPEndOffset);
  }

  /* Option register */
  if ((pOBInit->OptionType & (OPTIONBYTE_RDP | OPTIONBYTE_USER)) == (OPTIONBYTE_RDP | OPTIONBYTE_USER))
  {
    /* Fully modify OPTR register with RDP & user data */
    FLASH_OB_OptrConfig(pOBInit->USERType, pOBInit->USERConfig, pOBInit->RDPLevel);
  }
  else if ((pOBInit->OptionType & OPTIONBYTE_RDP) != 0x00U)
  {
    /* Only modify RDP so get current user data */
    optr = FLASH_OB_GetUser();
    FLASH_OB_OptrConfig(optr, optr, pOBInit->RDPLevel);
  }
  else if ((pOBInit->OptionType & OPTIONBYTE_USER) != 0x00U)
  {
    /* Only modify user so get current RDP level */
    optr = FLASH_OB_GetRDP();
    FLASH_OB_OptrConfig(pOBInit->USERType, pOBInit->USERConfig, optr);
  }
  else
  {
    /* nothing to do */
  }

  /* HDP Area Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_HDP) != 0x00U)
  {
    /* Configure the HDP area protection */
    FLASH_OB_HDPConfig(pOBInit->BootLock, pOBInit->HDPEndPage, pOBInit->HDPState);
  }

  /* RDP Keys OEM1/2 Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_RDPKEY) != 0x00U)
  {
    /* Configure the RDP keys */
    FLASH_OB_RDPKeyConfig(pOBInit->RDPKeyType, pOBInit->RDPKey1, pOBInit->RDPKey2, pOBInit->RDPKey3, pOBInit->RDPKey4);
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

    /* If the option byte program operation is completed, disable the OPTSTRT Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTSTRT);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  /* return status */
  return status;
}

/**
  * @brief  Get the Option bytes configuration.
  * @note   warning: this API only read flash register, it does not reflect any
  *         change that would have been programmed between previous Option byte
  *         loading and current call.
  * @param  pOBInit Pointer to an @ref FLASH_OBProgramInitTypeDef structure that contains the
  *                  configuration information. The fields pOBInit->WRPArea should
  *                  indicate which area is requested for the WRP.
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = OPTIONBYTE_ALL;

  /* Get write protection on the selected area */
  FLASH_OB_GetWRP(pOBInit->WRPArea, &(pOBInit->WRPStartOffset), &(pOBInit->WRPEndOffset));

  /* Get Read protection level */
  pOBInit->RDPLevel = FLASH_OB_GetRDP();

  /* Get the user option bytes */
  pOBInit->USERConfig = FLASH_OB_GetUser();
  pOBInit->USERType = OB_USER_ALL;

  /* Get the Securable Memory Area protection */
  FLASH_OB_GetHDPConfig(&(pOBInit->BootLock), &(pOBInit->HDPEndPage), &(pOBInit->HDPState));
}

/**
  * @brief  Enable Debugger.
  * @note   After calling this API, flash interface allow debugger intrusion.
  * @retval None
  */
void HAL_FLASHEx_EnableDebugger(void)
{
  FLASH->ACR |= FLASH_ACR_DBG_SWEN;
}


/**
  * @brief  Disable Debugger.
  * @note   After calling this API, Debugger is disabled: it is no more possible to
  *         break, see CPU register, etc...
  * @retval None
  */
void HAL_FLASHEx_DisableDebugger(void)
{
  FLASH->ACR &= ~FLASH_ACR_DBG_SWEN;
}

/**
  * @brief  Flash Empty check
  * @note   This API checks if first location in Flash is programmed or not.
  *         This check is done once by Option Byte Loader.
  * @retval 0 if 1st location is not programmed else
  */
uint32_t HAL_FLASHEx_FlashEmptyCheck(void)
{
  return ((FLASH->ACR & FLASH_ACR_EMPTY));
}


/**
  * @brief  Force Empty check value.
  * @note   Allows to modify program empty check value in order to force this
  *         information in Flash Interface, for all next reset that do not launch
  *         Option Byte Loader.
  * @param  FlashEmpty this parameter can be a value of @ref FLASHEx_Empty_Check
  * @retval None
  */
void HAL_FLASHEx_ForceFlashEmpty(uint32_t FlashEmpty)
{
  uint32_t acr;
  assert_param(IS_FLASH_EMPTY_CHECK(FlashEmpty));

  acr = (FLASH->ACR & ~FLASH_ACR_EMPTY);
  FLASH->ACR = (acr | FlashEmpty);
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
  /* Set the Mass Erase Bit and start bit */
  SET_BIT(FLASH->CR, (FLASH_CR_STRT | FLASH_CR_MER1));
}

/**
  * @brief  Erase the specified FLASH memory page.
  * @param  Page FLASH page to erase
  *         This parameter must be a value between 0 and (max number of pages in Flash - 1)
  * @retval None
  */
void FLASH_PageErase(uint32_t Page)
{
  uint32_t tmp;

  /* Check the parameters */
  assert_param(IS_FLASH_BANK(FLASH_BANK_1));
  assert_param(IS_FLASH_PAGE(Page));

  /* Get configuration register, then clear page number */
  tmp = (FLASH->CR & ~FLASH_CR_PNB);

  /* Set page number, Page Erase bit & Start bit */
  FLASH->CR = (tmp | (FLASH_CR_STRT | (Page <<  FLASH_CR_PNB_Pos) | FLASH_CR_PER));
}

/**
  * @brief  Flush the instruction cache.
  * @retval None
  */
void FLASH_FlushCaches(void)
{
  /* Flush instruction cache  */
  if (READ_BIT(FLASH->ACR, FLASH_ACR_ICEN) != 0U)
  {
    /* Disable instruction cache */
    __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
    /* Reset instruction cache */
    __HAL_FLASH_INSTRUCTION_CACHE_RESET();
    /* Enable instruction cache */
    __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
  }
}


/**
  * @brief  Configure the write protection of the desired pages.
  * @note   When WRP is active in a zone, it cannot be erased or programmed.
  *         Consequently, a software mass erase cannot be performed if one zone
  *         is write-protected.
  * @note   When the memory read protection level is selected (RDP level = 1),
  *         it is not possible to program or erase Flash memory if the CPU debug
  *         features are connected (JTAG or single wire) or boot code is being
  *         executed from RAM or System flash, even if WRP is not activated.
  * @param  WRPArea  Specifies the area to be configured.
  *         This parameter can be one of the following values:
  *           @arg @ref OB_WRPAREA_ZONE_A Flash Zone A
  *           @arg @ref OB_WRPAREA_ZONE_B Flash Zone B
  * @param  WRPStartOffset  Specifies the start page of the write protected area
  *         This parameter can be page number between 0 and (max number of pages in the Flash Bank - 1)
  * @param  WRDPEndOffset  Specifies the end page of the write protected area
  *         This parameter can be page number between WRPStartOffset and (max number of pages in the Flash Bank - 1)
  * @retval None
  */
static void FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRDPEndOffset)
{
  /* Check the parameters */
  assert_param(IS_OB_WRPAREA(WRPArea));
  assert_param(IS_FLASH_PAGE(WRPStartOffset));
  assert_param(IS_FLASH_PAGE(WRDPEndOffset));

  /* Configure the write protected area */
  if (WRPArea == OB_WRPAREA_ZONE_A)
  {
    FLASH->WRP1AR = ((WRDPEndOffset << FLASH_WRP1AR_WRP1A_END_Pos) | WRPStartOffset);
  }
  else
  {
    FLASH->WRP1BR = ((WRDPEndOffset << FLASH_WRP1BR_WRP1B_END_Pos) | WRPStartOffset);
  }
}

/**
  * @brief  Return the FLASH Write Protection Option Bytes value.
  * @param[in]  WRPArea Specifies the area to be returned.
  *             This parameter can be one of the following values:
  *               @arg @ref OB_WRPAREA_ZONE_A Flash Zone A
  *               @arg @ref OB_WRPAREA_ZONE_B Flash Zone B
  * @param[out]  WRPStartOffset  Specifies the address where to copied the start page
  *                         of the write protected area
  * @param[out]  WRDPEndOffset  Dpecifies the address where to copied the end page of
  *                        the write protected area
  * @retval None
  */
static void FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t *WRPStartOffset, uint32_t *WRDPEndOffset)
{

  /* Get the configuration of the write protected area */
  if (WRPArea == OB_WRPAREA_ZONE_A)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_STRT);
    *WRDPEndOffset = (READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_END) >> FLASH_WRP1AR_WRP1A_END_Pos);
  }
  else if (WRPArea == OB_WRPAREA_ZONE_B)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_STRT);
    *WRDPEndOffset = (READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_END) >> FLASH_WRP1BR_WRP1B_END_Pos);
  }
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Set user & RDP configuration
  * @note   !!! Warning : When enabling OB_RDP level 2 it is no more possible
  *         to go back to level 1 or 0 !!!
  * @param  UserType  The FLASH User Option Bytes to be modified.
  *         This parameter can be a combination of @ref FLASH_OB_USER_Type
  * @param  UserConfig  The FLASH User Option Bytes values.
  *         This parameter can be a combination of:
  *           @arg @ref FLASH_OB_USER_BOR_ENABLE
  *           @arg @ref FLASH_OB_USER_BOR_LEVEL
  *           @arg @ref FLASH_OB_USER_RESET_CONFIG
  *           @arg @ref FLASH_OB_USER_NRST_STOP
  *           @arg @ref FLASH_OB_USER_NRST_STANDBY
  *           @arg @ref FLASH_OB_USER_NRST_SHUTDOWN
  *           @arg @ref FLASH_OB_USER_IWDG_SW
  *           @arg @ref FLASH_OB_USER_IWDG_STOP
  *           @arg @ref FLASH_OB_USER_IWDG_STANDBY
  *           @arg @ref FLASH_OB_USER_WWDG_SW
  *           @arg @ref FLASH_OB_USER_SRAM_PARITY
  *           @arg @ref FLASH_OB_USER_NBOOT_SEL
  *           @arg @ref FLASH_OB_USER_NBOOT1
  *           @arg @ref FLASH_OB_USER_NBOOT0
  *           @arg @ref FLASH_OB_USER_INPUT_RESET_HOLDER
  * @param  RDPLevel  specifies the read protection level.
  *         This parameter can be one of the following values:
  *           @arg @ref OB_RDP_LEVEL_0 No protection
  *           @arg @ref OB_RDP_LEVEL_1 Memory Read protection
  *           @arg @ref OB_RDP_LEVEL_2 Full chip protection
  * @retval None
  */
static void FLASH_OB_OptrConfig(uint32_t UserType, uint32_t UserConfig, uint32_t RDPLevel)
{
  uint32_t optr;

  /* Check the parameters */
  assert_param(IS_OB_USER_TYPE(UserType));
  assert_param(IS_OB_USER_CONFIG(UserType, UserConfig));
  assert_param(IS_OB_RDP_LEVEL(RDPLevel));

  /* Configure the RDP level in the option bytes register */
  optr = FLASH->OPTR;
  optr &= ~(UserType | FLASH_OPTR_RDP);
  FLASH->OPTR = (optr | UserConfig | RDPLevel);
}

/**
  * @brief  Return the FLASH Read Protection level.
  * @retval FLASH ReadOut Protection Status:
  *         This return value can be one of the following values:
  *           @arg @ref OB_RDP_LEVEL_0 No protection
  *           @arg @ref OB_RDP_LEVEL_1 Read protection of the memory
  *           @arg @ref OB_RDP_LEVEL_2 Full chip protection
  */
static uint32_t FLASH_OB_GetRDP(void)
{
  uint32_t rdplvl = READ_BIT(FLASH->OPTR, FLASH_OPTR_RDP);

  if ((rdplvl != OB_RDP_LEVEL_0) && (rdplvl != OB_RDP_LEVEL_2))
  {
    return (OB_RDP_LEVEL_1);
  }
  else
  {
    return rdplvl;
  }
}

/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval The FLASH User Option Bytes values. It will be a combination of all the following values:
  *           @arg @ref FLASH_OB_USER_BOR_ENABLE
  *           @arg @ref FLASH_OB_USER_BOR_LEVEL
  *           @arg @ref FLASH_OB_USER_RESET_CONFIG
  *           @arg @ref FLASH_OB_USER_NRST_STOP
  *           @arg @ref FLASH_OB_USER_NRST_STANDBY
  *           @arg @ref FLASH_OB_USER_NRST_SHUTDOWN
  *           @arg @ref FLASH_OB_USER_IWDG_SW
  *           @arg @ref FLASH_OB_USER_IWDG_STOP
  *           @arg @ref FLASH_OB_USER_IWDG_STANDBY
  *           @arg @ref FLASH_OB_USER_WWDG_SW
  *           @arg @ref FLASH_OB_USER_SRAM_PARITY
  *           @arg @ref FLASH_OB_USER_NBOOT_SEL
  *           @arg @ref FLASH_OB_USER_NBOOT1
  *           @arg @ref FLASH_OB_USER_NBOOT0
  *           @arg @ref FLASH_OB_USER_INPUT_RESET_HOLDER
  */
static uint32_t FLASH_OB_GetUser(void)
{
  uint32_t user = ((FLASH->OPTR & ~FLASH_OPTR_RDP) & OB_USER_ALL);
  return user;
}

/**
  * @brief  Configure the HDP memory register.
  * @param   BootEntry  specifies if boot scheme is forced to Flash (System or user) or not
  *          This parameter can be one of the following values:
  *           @arg @ref OB_BOOT_LOCK_DISABLE No boot entry
  *           @arg @ref OB_BOOT_LOCK_ENABLE Flash selected as unique entry boot
  * @param   HDPEndPage specifies the end page of the hide protection area
  * @param   HDPEn     Enable and disable the HDP area
  * @retval None
  */
static void FLASH_OB_HDPConfig(uint32_t BootEntry, uint32_t HDPEndPage, uint32_t HDPEn)
{
  uint32_t secmem;

  /* Check the parameters */
  assert_param(IS_OB_BOOT_LOCK(BootEntry));
  assert_param(IS_FLASH_PAGE(HDPEndPage));
  /* Set securable memory area configuration */
  secmem = (FLASH->SECR & ~(FLASH_SECR_BOOT_LOCK | FLASH_SECR_HDP1_PEND | FLASH_SECR_HDP1EN));
  FLASH->SECR = (secmem | BootEntry | HDPEndPage | (HDPEn << FLASH_SECR_HDP1EN_Pos));
}

/**
  * @brief   Return the HDP memory register configuration.
  * @param   BootEntry  specifies if boot scheme configuration.
  * @param   HDPEndPage specifies the end page of the hide protection area
  * @param   HDPEn      specifies the status of the hide protection area (Enabled(other) or disabled(0xB4))
  * @retval None
  */
static void FLASH_OB_GetHDPConfig(uint32_t *BootEntry, uint32_t *HDPEndPage, uint32_t *HDPEn)
{
  uint32_t secmem = FLASH->SECR;

  *BootEntry = (secmem & FLASH_SECR_BOOT_LOCK);
  *HDPEndPage = (secmem & FLASH_SECR_HDP1_PEND);
  *HDPEn = (secmem & FLASH_SECR_HDP1EN) >> FLASH_SECR_HDP1EN_Pos;
}

/**
  * @brief  Set the read protection key.
  * @param  RDPKeyType specifies the read protection key type.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_KEY_OEM1: OEM1 key
  *            @arg OB_RDP_KEY_OEM2: OEM2 key
  * @param  RDPKey0 specifies the RDP key 0.
  * @param  RDPKey1 specifies the RDP key 1.
  * @param  RDPKey2 specifies the RDP key 2.
  * @param  RDPKey3 specifies the RDP key 3.
  * @retval None
  */
static void FLASH_OB_RDPKeyConfig(uint32_t RDPKeyType, uint32_t RDPKey0, uint32_t RDPKey1,
                                  uint32_t RDPKey2, uint32_t RDPKey3)
{
  /* Check the parameters */
  assert_param(IS_OB_RDP_KEY_TYPE(RDPKeyType));

  /* Configure the RDP OEM1/2 key */
  if (RDPKeyType == OB_RDP_KEY_OEM1)
  {
    WRITE_REG(FLASH->OEM1KEYW0R, RDPKey0);
    WRITE_REG(FLASH->OEM1KEYW1R, RDPKey1);
    WRITE_REG(FLASH->OEM1KEYW2R, RDPKey2);
    WRITE_REG(FLASH->OEM1KEYW3R, RDPKey3);
  }
  else if (RDPKeyType == OB_RDP_KEY_OEM2)
  {

    WRITE_REG(FLASH->OEM2KEYW0R, RDPKey0);
    WRITE_REG(FLASH->OEM2KEYW1R, RDPKey1);
    WRITE_REG(FLASH->OEM2KEYW2R, RDPKey2);
    WRITE_REG(FLASH->OEM2KEYW3R, RDPKey3);
  }
  else
  {
    /* nothing to do */
  }
}

/**
  * @brief  Get the OEM1/2 keys CRC.
  * @param  RDPKeyType specifies the read protection key type.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_KEY_OEM1: OEM1 key
  *            @arg OB_RDP_KEY_OEM2: OEM2 key
  * @param  OEMKeyCRC specifies the OEM keys CRC.
  * @retval None
  */
void HAL_FLASH_OB_GetOEMKeyCRC(uint32_t RDPKeyType, uint32_t *OEMKeyCRC)
{
  uint32_t regvalue;

  regvalue = FLASH->OEMKEYSR;
  if (RDPKeyType == OB_RDP_KEY_OEM1)
  {
    *OEMKeyCRC = (regvalue & FLASH_OEMKEYSR_OEM1KEYCRC);
  }
  else if (RDPKeyType == OB_RDP_KEY_OEM2)
  {
    *OEMKeyCRC = (regvalue & FLASH_OEMKEYSR_OEM2KEYCRC) >> FLASH_OEMKEYSR_OEM2KEYCRC_Pos;
  }
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Enable the HDP Protection area .
  * @param  Banks specifies the bank number
  *         this parameter can be:
  *         @arg @ref FLASH_BANK_1
  * @retval None
  */
void HAL_FLASHEx_EnableHDPProtection(uint32_t Banks)
{
  assert_param(IS_FLASH_BANK(Banks));

  MODIFY_REG(FLASH->HDPCR, FLASH_HDPCR_HDP1_ACCDIS, FLASH_HDPCR_HDP1_ACCDIS);
}

/**
  * @brief  Check if the HDP area protection enabled.
  * @retval returns 1 if the Protection is enabled
  *                 0 if the protection is disabled
  */
uint32_t HAL_FLASHEx_IsEnabledHDPProtection(void)
{
  return ((READ_BIT(FLASH->HDPCR, FLASH_HDPCR_HDP1_ACCDIS) == FLASH_HDPCR_HDP1_ACCDIS) ? 0UL : 1UL);
}
/**
  * @brief  HDP extension area configuration.
  * @param  pHDPExtension pointer to an FLASH_HDPExtentionTypeDef structure that
  *                       contains the configuration information.
  * @retval None
  */
void HAL_FLASHEx_ConfigHDPExtension(const FLASH_HDPExtensionTypeDef *pHDPExtension)
{
  assert_param(IS_FLASH_PAGE(pHDPExtension->NbPages));
  assert_param(IS_OB_HDPEXT_CONFIG(pHDPExtension->Status));

  MODIFY_REG(FLASH->HDPEXTR, FLASH_HDPEXTR_HDP1_EXT, (pHDPExtension->NbPages));
  MODIFY_REG(FLASH->HDPCR, FLASH_HDPCR_HDP1EXT_ACCDIS, (pHDPExtension->Status));
}
/**
  * @brief  Get HDP extension configuration.
  * @param  pHDPExtension pointer to an FLASH_HDPExtentionTypeDef structure that
  *                       contains the configuration information.
  * @retval None
  */
void HAL_FLASHEx_GetHDPExtensionConfig(FLASH_HDPExtensionTypeDef *pHDPExtension)
{
  uint32_t regvalue;

  regvalue = FLASH->HDPEXTR;
  pHDPExtension->NbPages = regvalue & FLASH_HDPEXTR_HDP1_EXT;
  regvalue = FLASH->HDPCR;
  pHDPExtension->Status = regvalue & FLASH_HDPCR_HDP1EXT_ACCDIS;
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
