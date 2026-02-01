/**
  ******************************************************************************
  * @file    stm32wb0x_ll_system.c
  * @author  MCD Application Team
  * @brief   HAL module driver.
  *          This is the common part of the HAL initialization
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
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The common HAL driver contains a set of generic and common APIs that can be
    used by the PPP peripheral drivers and the user to start using the HAL.
    [..]
    The HAL contains two APIs' categories:
         (+) Common HAL APIs
         (+) Services HAL APIs

  @endverbatim
  ******************************************************************************
  */

#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_ll_system.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined (SYSCFG)
/** @addtogroup SYSTEM_LL
  * @{
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup EXTI_Private_Macros
  * @{
  */

#define IS_LL_EXTI_LINE(__VALUE__)              (((__VALUE__) & ~LL_EXTI_LINE_ALL) == 0x00000000U)

#define IS_LL_EXTI_TYPE(__VALUE__)                   (((__VALUE__) == LL_EXTI_TYPE_EDGE)            \
                                                      || ((__VALUE__) == LL_EXTI_TYPE_LEVEL))


#define IS_LL_EXTI_TRIGGER(__VALUE__)                (((__VALUE__) == LL_EXTI_TRIGGER_RISING_EDGE)  \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_FALLING_EDGE) \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_BOTH_EDGE)    \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_LOW_LEVEL)    \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_HIGH_LEVEL))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @addtogroup SYSCFG_IO_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the SYSCFG_IO registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: SYSCFG_IO registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_SYSCFG_IO_DeInit(void)
{
  /* I/O Interrupt detection type register set to default reset values */
  LL_SYSCFG_WriteReg(IO_DTR,  0x00000000U);

  /* I/O Interrupt Edge register set to default reset values */
  LL_SYSCFG_WriteReg(IO_IBER,  0x00000000U);

  /* I/O Interrupt polarity event register set to default reset values */
  LL_SYSCFG_WriteReg(IO_IEVR, 0x00000000U);

  /* I/O Interrupt Enable register set to default reset values */
  LL_SYSCFG_WriteReg(IO_IER, 0x00000000U);

  /* Clear all the I/O Interrupt */
  LL_SYSCFG_WriteReg(IO_ISCR, LL_EXTI_LINE_ALL);

  return SUCCESS;
}

/**
  * @brief  Initialize the SYSCFG_IO registers according to the specified parameters in SYSCFG_IO_InitStruct.
  * @param  SYSCFG_IO_InitStruct pointer to a @ref LL_SYSCFG_IO_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: SYSCFG_IO registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_SYSCFG_IO_Init(LL_SYSCFG_IO_InitTypeDef *SYSCFG_IO_InitStruct)
{
  ErrorStatus status = SUCCESS;
  /* Check the parameters */
  assert_param(IS_LL_EXTI_LINE(SYSCFG_IO_InitStruct->Line));
  assert_param(IS_FUNCTIONAL_STATE(SYSCFG_IO_InitStruct->LineCommand));
  assert_param(IS_LL_EXTI_TYPE(SYSCFG_IO_InitStruct->Type));

  /* ENABLE LineCommand */
  if (SYSCFG_IO_InitStruct->LineCommand != DISABLE)
  {
    assert_param(IS_LL_EXTI_TRIGGER(SYSCFG_IO_InitStruct->Trigger));

    /* Configure SYSCFG IO Lines in range from PA0 to PB15 */
    if (SYSCFG_IO_InitStruct->Line != LL_EXTI_LINE_NONE)
    {
      /* Set the IT Type on provided Lines */
      LL_EXTI_EnableEdgeDetection(SYSCFG_IO_InitStruct->Line);

      if (SYSCFG_IO_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (SYSCFG_IO_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING_EDGE:
            LL_EXTI_EnableEdgeDetection(SYSCFG_IO_InitStruct->Line);
            LL_EXTI_EnableRisingTrig(SYSCFG_IO_InitStruct->Line);
            break;
          case LL_EXTI_TRIGGER_FALLING_EDGE:
            LL_EXTI_EnableEdgeDetection(SYSCFG_IO_InitStruct->Line);
            LL_EXTI_DisableRisingTrig(SYSCFG_IO_InitStruct->Line);
            break;
          case LL_EXTI_TRIGGER_BOTH_EDGE:
            LL_EXTI_EnableEdgeDetection(SYSCFG_IO_InitStruct->Line);
            LL_EXTI_EnableBothEdgeTrig(SYSCFG_IO_InitStruct->Line);
            break;
          case LL_EXTI_TRIGGER_LOW_LEVEL:
            LL_EXTI_DisableEdgeDetection(SYSCFG_IO_InitStruct->Line);
            LL_EXTI_DisableRisingTrig(SYSCFG_IO_InitStruct->Line);
            break;
          case LL_EXTI_TRIGGER_HIGH_LEVEL:
            LL_EXTI_DisableEdgeDetection(SYSCFG_IO_InitStruct->Line);
            LL_EXTI_EnableRisingTrig(SYSCFG_IO_InitStruct->Line);
            break;
          default:
            status = ERROR;
            break;
        }
        LL_EXTI_EnableIT(SYSCFG_IO_InitStruct->Line);
        LL_EXTI_ClearFlag(SYSCFG_IO_InitStruct->Line);
      }
    }
    /* DISABLE LineCommand */
    else
    {
      LL_EXTI_DisableIT(SYSCFG_IO_InitStruct->Line);
    }
  }
  return status;
}

/**
  * @brief  Set each @ref LL_SYSCFG_IO_InitTypeDef field to default value.
  * @param  SYSCFG_IO_InitStruct Pointer to a @ref LL_SYSCFG_IO_InitTypeDef structure.
  * @retval None
  */
void LL_SYSCFG_IO_StructInit(LL_SYSCFG_IO_InitTypeDef *SYSCFG_IO_InitStruct)
{
  SYSCFG_IO_InitStruct->Line           = LL_EXTI_LINE_NONE;
  SYSCFG_IO_InitStruct->LineCommand    = DISABLE;
  SYSCFG_IO_InitStruct->Type           = LL_EXTI_TYPE_EDGE;
  SYSCFG_IO_InitStruct->Trigger        = LL_EXTI_TRIGGER_NONE;
}

/**
  * @}
  */

/**
  * @}
  */


#endif /* defined (SYSCFG) */


/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */