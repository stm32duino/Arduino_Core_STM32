/**
  ******************************************************************************
  * @file    stm32wb0x_ll_pwr.c
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
#include "stm32wb0x_ll_pwr.h"
#include "stm32wb0x_ll_bus.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @brief PWR LL module driver
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */
/* Definitions of PWR registers reset value */
#if defined(STM32WB06) || defined(STM32WB07)
#define PWR_CR1_RESET_VALUE     (0x00000010)
#define PWR_CR2_RESET_VALUE     (0x00000100)
#define PWR_CR5_RESET_VALUE     (0x00000014)
#define PWR_PUCRA_RESET_VALUE   (0x0000FFF7)
#define PWR_PUCRB_RESET_VALUE   (0x0000FFFF)
#define PWR_IOxCFG_RESET_VALUE  (0x00000000)
#else
#define PWR_CR1_RESET_VALUE     (0x00000114)
#define PWR_CR2_RESET_VALUE     (0x00000000)
#define PWR_CR5_RESET_VALUE     (0x00006014)
#define PWR_PUCRA_RESET_VALUE   (0x00000F07)
#define PWR_PUCRB_RESET_VALUE   (0x0000F0FF)
#endif /* STM32WB06 || STM32WB07*/
#define PWR_CR3_RESET_VALUE     (0x00000000)
#define PWR_CR4_RESET_VALUE     (0x00000000)
#define PWR_CR6_RESET_VALUE     (0x00000000)
#define PWR_CR7_RESET_VALUE     (0x00000000)
#define PWR_PDCRA_RESET_VALUE   (0x00000008)
#define PWR_PDCRB_RESET_VALUE   (0x00000000)
#define PWR_ENGTRIM_RESET_VALUE (0x00000000)
#define PWR_EWUA_RESET_VALUE    (0x00000000)
#define PWR_EWUB_RESET_VALUE    (0x00000000)
#define PWR_IEWU_RESET_VALUE    (0x00000000)
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
  /* Apply reset values to all PWR registers */
  LL_PWR_WriteReg(CR1, PWR_CR1_RESET_VALUE);
  LL_PWR_WriteReg(CR2, PWR_CR2_RESET_VALUE);
  LL_PWR_WriteReg(CR3, PWR_CR3_RESET_VALUE);
  LL_PWR_WriteReg(CR4, PWR_CR4_RESET_VALUE);
  LL_PWR_WriteReg(CR5, PWR_CR5_RESET_VALUE);
  LL_PWR_WriteReg(PUCRA, PWR_PUCRA_RESET_VALUE);
  LL_PWR_WriteReg(PDCRA, PWR_PDCRA_RESET_VALUE);
  LL_PWR_WriteReg(PUCRB, PWR_PUCRB_RESET_VALUE);
  LL_PWR_WriteReg(PDCRB, PWR_PDCRB_RESET_VALUE);
  LL_PWR_WriteReg(CR6, PWR_CR6_RESET_VALUE);
  LL_PWR_WriteReg(CR7, PWR_CR7_RESET_VALUE);
#if defined(STM32WB06) || defined(STM32WB07)
  LL_PWR_WriteReg(IOxCFG, PWR_IOxCFG_RESET_VALUE);
#endif /*  STM32WB06 || STM32WB07 */
  LL_PWR_WriteReg(ENGTRIM, PWR_ENGTRIM_RESET_VALUE);

  /* Clear all flags */
  LL_PWR_WriteReg(SR1,
                  LL_PWR_SR1_WUF0
                  | LL_PWR_SR1_WUF1
                  | LL_PWR_SR1_WUF2
                  | LL_PWR_SR1_WUF3
                  | LL_PWR_SR1_WUF4
                  | LL_PWR_SR1_WUF5
                  | LL_PWR_SR1_WUF6
                  | LL_PWR_SR1_WUF7
                  | LL_PWR_SR1_WUF8
                  | LL_PWR_SR1_WUF9
                  | LL_PWR_SR1_WUF10
                  | LL_PWR_SR1_WUF11
#if defined(PWR_CR3_EIWL2)
                  | LL_PWR_SR1_WUFI2
#endif /*  PWR_CR3_EIWL2 */
                 );
  LL_PWR_WriteReg(SR3,
                  (LL_PWR_SR3_WUF12 >> 16)
                  | (LL_PWR_SR3_WUF13 >> 16)
                  | (LL_PWR_SR3_WUF14 >> 16)
                  | (LL_PWR_SR3_WUF15 >> 16)
                  | (LL_PWR_SR3_WUF16 >> 16)
                  | (LL_PWR_SR3_WUF17 >> 16)
                  | (LL_PWR_SR3_WUF18 >> 16)
                  | (LL_PWR_SR3_WUF19 >> 16)
#if defined(PWR_CR6_EWU20)
                  | (LL_PWR_SR3_WUF20 >> 16)
#endif /* PWR_CR6_EWU20 */
#if defined(PWR_CR6_EWU21)
                  | (LL_PWR_SR3_WUF21 >> 16)
#endif /* PWR_CR6_EWU21 */
#if defined(PWR_CR6_EWU22)
                  | (LL_PWR_SR3_WUF22 >> 16)
#endif /* PWR_CR6_EWU22 */
#if defined(PWR_CR6_EWU23)
                  | (LL_PWR_SR3_WUF23 >> 16)
#endif /* PWR_CR6_EWU23 */
#if defined(PWR_CR6_EWU24)
                  | (LL_PWR_SR3_WUF24 >> 16)
#endif /* PWR_CR6_EWU24 */
#if defined(PWR_CR6_EWU25)
                  | (LL_PWR_SR3_WUF25 >> 16)
#endif /* PWR_CR6_EWU25 */
#if defined(PWR_CR6_EWU26)
                  | (LL_PWR_SR3_WUF26 >> 16)
#endif /* PWR_CR6_EWU26 */
#if defined(PWR_CR6_EWU27)
                  | (LL_PWR_SR3_WUF27 >> 16)
#endif /* PWR_CR6_EWU27 */
                 );

  LL_PWR_WriteReg(EXTSRR,
                  LL_PWR_EXTSRR_RFPHASEF
                  | LL_PWR_EXTSRR_DEEPSTOPF
                 );
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
#endif /* PWR */
/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
