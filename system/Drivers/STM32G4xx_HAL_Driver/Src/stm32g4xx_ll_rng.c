/**
  ******************************************************************************
  * @file    stm32g4xx_ll_rng.c
  * @author  MCD Application Team
  * @brief   RNG LL module driver.
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
#include "stm32g4xx_ll_rng.h"
#include "stm32g4xx_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32G4xx_LL_Driver
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
/** @defgroup RNG_LL_Private_Macros RNG Private Macros
  * @{
  */
#define IS_LL_RNG_CED(__MODE__) (((__MODE__) == LL_RNG_CED_ENABLE) || \
                                 ((__MODE__) == LL_RNG_CED_DISABLE))

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
ErrorStatus LL_RNG_DeInit(const RNG_TypeDef *RNGx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_RNG_ALL_INSTANCE(RNGx));
  if (RNGx == RNG)
  {
    /* Enable RNG reset state */
    LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_RNG);

    /* Release RNG from reset state */
    LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_RNG);
  }
  else
  {
    status = ERROR;
  }

  return status;
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
ErrorStatus LL_RNG_Init(RNG_TypeDef *RNGx, const LL_RNG_InitTypeDef *RNG_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_RNG_ALL_INSTANCE(RNGx));
  assert_param(IS_LL_RNG_CED(RNG_InitStruct->ClockErrorDetection));

  /* Clock Error Detection configuration */
  MODIFY_REG(RNGx->CR, RNG_CR_CED, RNG_InitStruct->ClockErrorDetection);

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
  RNG_InitStruct->ClockErrorDetection = LL_RNG_CED_ENABLE;

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

#endif /* RNG */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

