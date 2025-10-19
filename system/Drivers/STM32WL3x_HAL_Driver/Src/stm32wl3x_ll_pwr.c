/**
  ******************************************************************************
  * @file    stm32wl3x_ll_pwr.c
  * @author  MCD Application Team
  * @brief   PWR LL module driver.
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
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_ll_pwr.h"

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_LL_Exported_Functions
  * @{
  */

/** @addtogroup PWR_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the PWR registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PWR registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_PWR_DeInit(void)
{
  /* Disable PWR Wakeup Source */

  LL_PWR_WriteReg(EWUA, 0);
  LL_PWR_WriteReg(WUPA, 0);
  LL_PWR_WriteReg(EWUB, 0);
  LL_PWR_WriteReg(WUPB, 0);
  LL_PWR_WriteReg(IEWU, 0);
  LL_PWR_WriteReg(IWUP, 0);

#if defined(PWR_SDWN_WUEN_WUEN)
  LL_PWR_WriteReg(SDWN_WUEN, 0);
  LL_PWR_WriteReg(SDWN_WUPOL, 0);
#endif /* PWR_SDWN_WUEN_WUEN */

  LL_PWR_WriteReg(IWUF,
                  LL_PWR_WAKEUP_LPAWUR
                  | LL_PWR_WAKEUP_SUBG
                  | LL_PWR_WAKEUP_SUBGHOST
                  | LL_PWR_WAKEUP_LCSC
                  | LL_PWR_WAKEUP_COMP
                  | LL_PWR_WAKEUP_LCD
                  | LL_PWR_WAKEUP_RTC
                  | LL_PWR_WAKEUP_LPUART
                 );

  LL_PWR_WriteReg(WUFA, LL_PWR_WAKEUP_ALL);
  LL_PWR_WriteReg(WUFB, LL_PWR_WAKEUP_ALL);

#if defined(PWR_SDWN_WUEN_WUEN)
  LL_PWR_WriteReg(SDWN_WUF, 0);
#endif /* PWR_SDWN_WUEN_WUEN */

  return SUCCESS;
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
#endif /* defined(PWR) */
/**
  * @}
  */

#endif /* defined(USE_FULL_LL_DRIVER) */
