/**
  ******************************************************************************
  * @file    stm32wb0x_ll_rng.c
  * @author  MCD Application Team
  * @brief   RNG LL module driver.
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
#include "stm32wb0x_ll_rng.h"
#include "stm32wb0x_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined (RNG)

/** @addtogroup RNG_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
#if defined (STM32WB09)
/** @addtogroup RNG_LL_Exported_Functions
  * @{
  */

/** @addtogroup RNG_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize RNG registers (Registers restored to their default values).
  * @param  RNGx RNG Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RNG registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RNG_DeInit(RNG_TypeDef *RNGx)
{
  /* Check the parameters */
  assert_param(IS_RNG_ALL_INSTANCE(RNGx));

  /* Enable RNG reset state */
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_RNG);

  /* Release RNG from reset state */
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_RNG);
  return (SUCCESS);
}

/**
  * @brief  Initialize RNG registers according to the specified parameters in RNG_InitStruct.
  * @param  RNGx RNG Instance
  * @param  RNG_InitStruct pointer to a LL_RNG_InitTypeDef structure
  *         that contains the configuration information for the specified RNG peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RNG registers are initialized according to RNG_InitStruct content
  *          - ERROR: not applicable
  */
ErrorStatus LL_RNG_Init(RNG_TypeDef *RNGx, LL_RNG_InitTypeDef *RNG_InitStruct)
{

  /* Check that the divider value is equal to the one to configure. If not, it must redo the write and checking. */
  while (LL_RNG_GetSamplingClockEnableDivider(RNGx) != RNG_InitStruct->SamplingClockDivider)
  {
    /* While the new divider value is being resynchronized with the TRNG core clock domain, it is not possible to
       write another new value. */
    LL_RNG_SetSamplingClockEnableDivider(RNGx, RNG_InitStruct->SamplingClockDivider);
  }


  return (SUCCESS);
}

/**
  * @brief Set each @ref LL_RNG_InitTypeDef field to default value.
  * @param RNG_InitStruct pointer to a @ref LL_RNG_InitTypeDef structure
  *                       whose fields will be set to default values.
  * @retval None
  */
void LL_RNG_StructInit(LL_RNG_InitTypeDef *RNG_InitStruct)
{
  RNG_InitStruct->SamplingClockDivider = 0;

}
/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32WB09 */
#if defined (STM32WB07) || defined (STM32WB06) || defined(STM32WB05)
/** @addtogroup RNG_LL_Private_Macros
  * @{
  */
#define IS_LL_RNG_CLK_DET(__MODE__) (((__MODE__) == LL_RNG_CLK_DET_ENABLE) || \
                                     ((__MODE__) == LL_RNG_CLK_DET_DISABLE))

/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RNG_LL_Exported_Functions
  * @{
  */

/** @addtogroup RNG_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize RNG registers (Registers restored to their default values).
  * @param  RNGx RNG Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RNG registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RNG_DeInit(RNG_TypeDef *RNGx)
{
  /* Check the parameters */
  assert_param(IS_RNG_ALL_INSTANCE(RNGx));
  /* Enable RNG reset state */
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_RNG);

  /* Release RNG from reset state */
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_RNG);
  return (SUCCESS);
}

/**
  * @brief  Initialize RNG registers according to the specified parameters in RNG_InitStruct.
  * @param  RNGx RNG Instance
  * @param  RNG_InitStruct pointer to a LL_RNG_InitTypeDef structure
  *         that contains the configuration information for the specified RNG peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RNG registers are initialized according to RNG_InitStruct content
  *          - ERROR: not applicable
  */
ErrorStatus LL_RNG_Init(RNG_TypeDef *RNGx, LL_RNG_InitTypeDef *RNG_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_RNG_ALL_INSTANCE(RNGx));
  assert_param(IS_LL_RNG_CLK_DET(RNG_InitStruct->ClockDetection));

  /* Clock Detection configuration */
  MODIFY_REG(RNGx->CR, RNG_CR_TST_CLK, RNG_InitStruct->ClockDetection);

  return (SUCCESS);
}

/**
  * @brief Set each @ref LL_RNG_InitTypeDef field to default value.
  * @param RNG_InitStruct pointer to a @ref LL_RNG_InitTypeDef structure
  *                       whose fields will be set to default values.
  * @retval None
  */
void LL_RNG_StructInit(LL_RNG_InitTypeDef *RNG_InitStruct)
{
  /* Set RNG_InitStruct fields to default values */
  RNG_InitStruct->ClockDetection = LL_RNG_CLK_DET_DISABLE;

}
/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32WB07 || STM32WB06 || STM32WB05*/
/**
  * @}
  */

#endif /* RNG */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
