/**
  ******************************************************************************
  * @file    stm32mp1xx_ll_exti.c
  * @author  MCD Application Team
  * @brief   EXTI LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
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
#include "stm32mp1xx_ll_exti.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup STM32MP1xx_LL_Driver
  * @{
  */

#if defined (EXTI)

/** @defgroup EXTI_LL EXTI
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define EXTI_PR1_Msk  0x0001FFFFU
#define EXTI_PR3_Msk  0x00000616U

/* Private macros ------------------------------------------------------------*/
/** @addtogroup EXTI_LL_Private_Macros
  * @{
  */

#define IS_LL_EXTI_LINE_0_31(__VALUE__)              (((__VALUE__) & ~LL_EXTI_LINE_ALL_0_31) == 0x00000000U)
#define IS_LL_EXTI_LINE_32_63(__VALUE__)             (((__VALUE__) & ~LL_EXTI_LINE_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI_LINE_64_95(__VALUE__)             (((__VALUE__) & ~LL_EXTI_LINE_ALL_64_95) == 0x00000000U)

#define IS_LL_EXTI_MODE(__VALUE__)                   (((__VALUE__) == LL_EXTI_MODE_IT)            \
                                                   || ((__VALUE__) == LL_EXTI_MODE_EVENT)         \
                                                   || ((__VALUE__) == LL_EXTI_MODE_IT_EVENT))


#define IS_LL_EXTI_TRIGGER(__VALUE__)                (((__VALUE__) == LL_EXTI_TRIGGER_NONE)       \
                                                   || ((__VALUE__) == LL_EXTI_TRIGGER_RISING)     \
                                                   || ((__VALUE__) == LL_EXTI_TRIGGER_FALLING)    \
                                                   || ((__VALUE__) == LL_EXTI_TRIGGER_RISING_FALLING))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup EXTI_LL_Exported_Functions
  * @{
  */

/** @addtogroup EXTI_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the EXTI registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_EXTI_DeInit(void)
{
  /* Rising Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(RTSR1,  0x00000000U);

  /* Falling Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(FTSR1,  0x00000000U);

  /* Raising Pending Register 1set to default reset values */
  LL_EXTI_WriteReg(RPR1, EXTI_PR1_Msk);

  /* Raising Pending Register 1set to default reset values */
  LL_EXTI_WriteReg(FPR1, EXTI_PR1_Msk);

  /* Rising Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(RTSR3,  0x00000000U);

  /* Falling Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(FTSR3,  0x00000000U);

  /* Raising Pending Register 3set to default reset values */
  LL_EXTI_WriteReg(RPR3, EXTI_PR3_Msk);

  /* Raising Pending Register 3set to default reset values */
  LL_EXTI_WriteReg(FPR3, EXTI_PR3_Msk);

  /* Interrupt mask register set to default reset values */
  LL_EXTI_WriteReg(C2IMR1, 0xFFFE0000U);

  /* Event mask register set to default reset values */
  LL_EXTI_WriteReg(C2EMR1, 0x00000000U);

  /* Interrupt mask register 2 set to default reset values */
  LL_EXTI_WriteReg(C2IMR2, 0xFFFFFFFFU);

  /* Interrupt mask register 3 set to default reset values */
  LL_EXTI_WriteReg(C2IMR3, 0x00000DE9U);

  /* Event mask register 3 set to default reset values */
  LL_EXTI_WriteReg(C2EMR3, 0x00000000U);

  return SUCCESS;
}

/**
  * @brief  Initialize the EXTI registers according to the specified parameters in EXTI_InitStruct.
  * @note   When trying to apply a Trigger configuration to a Direct line or an
  *         EVENT Mode to a line which does not support this/these
  *         functionality(ies) will not return any error but change will not be
  *         applied by HW. In any case avoid doing this.
  *         Please note that for lines 32 to 63 only LL_EXTI_MODE_IT and
  *         LL_EXTI_TRIGGER_NONE are allowed values, ERROR will be returned if
  *         using other values.
  * @param  EXTI_InitStruct pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are initialized
  *          - ERROR: EXTI registers are not well initialized
  */
ErrorStatus LL_EXTI_Init(LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  ErrorStatus status = SUCCESS;
  /* Check the parameters */
  assert_param(IS_LL_EXTI_LINE_0_31(EXTI_InitStruct->Line_0_31));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTI_InitStruct->Line_32_63));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTI_InitStruct->Line_64_95));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->LineCommand));
  assert_param(IS_LL_EXTI_MODE(EXTI_InitStruct->Mode));

  /* ENABLE LineCommand */
  if (EXTI_InitStruct->LineCommand != DISABLE)
  {
    assert_param(IS_LL_EXTI_TRIGGER(EXTI_InitStruct->Trigger));

    /* Configure EXTI Lines in range from 0 to 31 */
    if (EXTI_InitStruct->Line_0_31 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_EXTI_DisableEvent_0_31(EXTI_InitStruct->Line_0_31);
          /* Then Enable IT on provided Lines */
          LL_EXTI_EnableIT_0_31(EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_EXTI_DisableIT_0_31(EXTI_InitStruct->Line_0_31);
          /* Then Enable Event on provided Lines */
          LL_EXTI_EnableEvent_0_31(EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_EXTI_EnableIT_0_31(EXTI_InitStruct->Line_0_31);
          LL_EXTI_EnableEvent_0_31(EXTI_InitStruct->Line_0_31);
          break;
        default:
          status = ERROR;
          break;
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_0_31(EXTI_InitStruct->Line_0_31);
            /* Then Enable Rising Trigger on provided Lines */
            LL_EXTI_EnableRisingTrig_0_31(EXTI_InitStruct->Line_0_31);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_0_31(EXTI_InitStruct->Line_0_31);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_0_31(EXTI_InitStruct->Line_0_31);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_0_31(EXTI_InitStruct->Line_0_31);
            LL_EXTI_EnableFallingTrig_0_31(EXTI_InitStruct->Line_0_31);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }
    /* Configure EXTI Lines in range from 32 to 63 */
    if (EXTI_InitStruct->Line_32_63 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
        case LL_EXTI_MODE_IT:
          /* Then Enable IT on provided Lines */
          LL_EXTI_EnableIT_32_63(EXTI_InitStruct->Line_32_63);
          break;
        default:
          status = ERROR;
          break;
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        status = ERROR;
      }
    }

    /* Configure EXTI Lines in range from 64 to 95 */
    if (EXTI_InitStruct->Line_64_95 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_EXTI_DisableEvent_64_95(EXTI_InitStruct->Line_64_95);
          /* Then Enable IT on provided Lines */
          LL_EXTI_EnableIT_64_95(EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_EXTI_DisableIT_64_95(EXTI_InitStruct->Line_64_95);
          /* Then Enable Event on provided Lines */
          LL_EXTI_EnableEvent_64_95(EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_EXTI_EnableIT_64_95(EXTI_InitStruct->Line_64_95);
          LL_EXTI_EnableEvent_64_95(EXTI_InitStruct->Line_64_95);
          break;
        default:
          status = ERROR;
          break;
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_64_95(EXTI_InitStruct->Line_64_95);
            /* Then Enable Rising Trigger on provided Lines */
            LL_EXTI_EnableRisingTrig_64_95(EXTI_InitStruct->Line_64_95);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_64_95(EXTI_InitStruct->Line_64_95);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_64_95(EXTI_InitStruct->Line_64_95);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_64_95(EXTI_InitStruct->Line_64_95);
            LL_EXTI_EnableFallingTrig_64_95(EXTI_InitStruct->Line_64_95);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }
  }
  /* DISABLE LineCommand */
  else
  {
    /* De-configure EXTI Lines in range from 0 to 31 */
    LL_EXTI_DisableIT_0_31(EXTI_InitStruct->Line_0_31);
    LL_EXTI_DisableEvent_0_31(EXTI_InitStruct->Line_0_31);

    /* De-configure EXTI Lines in range from 32 to 63 */
    LL_EXTI_DisableIT_32_63(EXTI_InitStruct->Line_32_63);

    /* De-configure EXTI Lines in range from 64 to 95 */
    LL_EXTI_DisableIT_64_95(EXTI_InitStruct->Line_64_95);
    LL_EXTI_DisableEvent_64_95(EXTI_InitStruct->Line_64_95);
  }
  return status;
}

/**
  * @brief  Set each @ref LL_EXTI_InitTypeDef field to default value.
  * @param  EXTI_InitStruct Pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval None
  */
void LL_EXTI_StructInit(LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  EXTI_InitStruct->Line_0_31      = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->Line_32_63     = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->Line_64_95     = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->LineCommand    = DISABLE;
  EXTI_InitStruct->Mode           = LL_EXTI_MODE_IT;
  EXTI_InitStruct->Trigger        = LL_EXTI_TRIGGER_FALLING;
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

#endif /* defined (EXTI) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
