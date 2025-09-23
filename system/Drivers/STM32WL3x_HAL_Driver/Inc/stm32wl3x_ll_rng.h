/**
  ******************************************************************************
  * @file    stm32wl3x_ll_rng.h
  * @author  MCD Application Team
  * @brief   Header file of RNG LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WL3x_LL_RNG_H
#define STM32WL3x_LL_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x.h"

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

#if defined (RNG)
/** @defgroup RNG_LL RNG
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RNG_LL_ES_Init_Struct RNG Exported Init structures
  * @{
  */

/**
  * @brief LL RNG Init Structure Definition
  */
typedef struct
{
  uint32_t         ClockDetection; /*!< RNG Clock detection.
                                      This parameter can be modified using unitary functions @ref
                    LL_RNG_EnableClkDetect(). */
} LL_RNG_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RNG_LL_Exported_Constants RNG Exported Constants
  * @{
  */

/** @defgroup RNG_LL_CLK_DET Logic that detects the presence of the RNG Clock
  * @{
  */
#define LL_RNG_CLK_DET_DISABLE        0x00000000U              /*!< RNG Clock detection disabled  */
#define LL_RNG_CLK_DET_ENABLE         RNG_CR_TST_CLK           /*!< RNG Clock detection enabled   */
/**
  * @}
  */

/** @defgroup RNG_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RNG_ReadReg function
  * @{
  */
#define LL_RNG_SR_RNGRDY RNG_SR_RNGRDY    /*!< Register contains valid random data */
#define LL_RNG_SR_REVCLK RNG_SR_REVCLK    /*!< Clock Reveal bit                    */
#define LL_RNG_SR_FAULT  RNG_SR_FAULT     /*!< Fault Reveal bit                    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RNG_LL_Exported_Macros RNG Exported Macros
  * @{
  */

/** @defgroup RNG_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RNG register
  * @param  __INSTANCE__ RNG Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_RNG_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RNG register
  * @param  __INSTANCE__ RNG Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_RNG_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup RNG_LL_Exported_Functions RNG Exported Functions
  * @{
  */
/** @defgroup RNG_LL_EF_Configuration RNG Configuration functions
  * @{
  */

/**
  * @brief  Enable Random Number Generation
  * @rmtoll CR           RNG_DIS         LL_RNG_Enable
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_Enable(RNG_TypeDef *RNGx)
{
  CLEAR_BIT(RNGx->CR, RNG_CR_RNG_DIS);
}

/**
  * @brief  Disable Random Number Generation
  * @rmtoll CR           RNG_DIS         LL_RNG_Disable
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_Disable(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->CR, RNG_CR_RNG_DIS);
}

/**
  * @brief  Check if Random Number Generator is enabled
  * @rmtoll CR           RNG_DIS         LL_RNG_IsEnabled
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsEnabled(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->CR, RNG_CR_RNG_DIS) != (RNG_CR_RNG_DIS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable RNG Clock detection
  * @rmtoll CR           TST_CLK           LL_RNG_EnableClkDetect
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_EnableClkDetect(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->CR, RNG_CR_TST_CLK);
}

/**
  * @brief  Disable RNG Clock detection
  * @rmtoll CR           TST_CLK         LL_RNG_DisableClkDetect
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_DisableClkDetect(RNG_TypeDef *RNGx)
{
  CLEAR_BIT(RNGx->CR, RNG_CR_TST_CLK);
}

/**
  * @}
  */

/** @defgroup RNG_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Indicate if the RNG value ready Flag is set or not
  * @rmtoll SR           RNGRDY          LL_RNG_IsActiveFlag_RNGRDY
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_RNGRDY(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_RNGRDY) == (RNG_SR_RNGRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if the Clock Reveal Status Flag is set or not
  * @rmtoll SR           REVCLK          LL_RNG_IsActiveFlag_REVCLK
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_REVCLK(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_REVCLK) == (RNG_SR_REVCLK)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if the Fault Reveal Flag is set or not
  * @rmtoll SR           FAULT          LL_RNG_IsActiveFlag_FAULT
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_FAULT(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_FAULT) == (RNG_SR_FAULT)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Fault Reveal Flag Flag
  * @rmtoll SR           FAULT          LL_RNG_ClearFlag_FAULT
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_ClearFlag_FAULT(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->SR, RNG_SR_FAULT);
}

/**
  * @}
  */

/** @defgroup RNG_LL_EF_Data_Management Data Management
  * @{
  */

/**
  * @brief  Return16-bit Random Number value
  * @rmtoll DR           RNDATA        LL_RNG_ReadRandData16
  * @param  RNGx RNG Instance
  * @retval Generated 16-bit random value
  */
__STATIC_INLINE uint16_t LL_RNG_ReadRandData16(RNG_TypeDef *RNGx)
{
  return (uint16_t)(READ_REG(RNGx->VAL));
}

/**
  * @}
  */

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RNG_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_RNG_Init(RNG_TypeDef *RNGx, LL_RNG_InitTypeDef *RNG_InitStruct);
void LL_RNG_StructInit(LL_RNG_InitTypeDef *RNG_InitStruct);
ErrorStatus LL_RNG_DeInit(RNG_TypeDef *RNGx);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */
#endif /* RNG */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32WL3x_LL_RNG_H */
