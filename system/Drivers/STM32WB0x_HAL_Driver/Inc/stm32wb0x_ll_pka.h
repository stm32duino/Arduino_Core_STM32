/**
  ******************************************************************************
  * @file    stm32wb0x_ll_pka.h
  * @author  MCD Application Team
  * @brief   Header file of PKA LL module.
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
#ifndef STM32WB0x_LL_PKA_H
#define STM32WB0x_LL_PKA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined(PKA)

/** @defgroup PKA_LL PKA
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/** @defgroup PKA_LL_ES_INIT PKA Exported Init structure
  * @{
  */

#if defined (STM32WB05)|| defined(STM32WB09)
/**
  * @brief  PKA Init structures definition
  */
typedef struct
{
  uint32_t Mode;          /*!< Specifies the PKA operation mode.
                               This parameter can be a value of @ref PKA_LL_EC_MODE.
                               This feature can be modified afterwards using unitary function @ref LL_PKA_SetMode(). */
} LL_PKA_InitTypeDef;
#endif /* STM32WB05 || STM32WB09 */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Constants PKA Exported Constants
  * @{
  */

/** @defgroup PKA_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PKA_ReadReg function
  * @{
  */
#if defined (STM32WB06) || defined(STM32WB07)
#define LL_PKA_PROCEND                 PKA_ISR_PROC_END
#define LL_PKA_RAMERR                  PKA_ISR_RAM_ERR
#define LL_PKA_ADDRERR                 PKA_ISR_ADD_ERR
#endif /* STM32WB06 || STM32WB07 */
#if defined (STM32WB05)|| defined(STM32WB09)
#define LL_PKA_SR_ADDRERRF                 PKA_SR_ADDRERRF
#define LL_PKA_SR_RAMERRF                  PKA_SR_RAMERRF
#define LL_PKA_SR_PROCENDF                 PKA_SR_PROCENDF
#define LL_PKA_SR_BUSY                     PKA_SR_BUSY
#endif /* STM32WB05 || STM32WB09 */
/**
  * @}
  */

/** @defgroup PKA_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_PKA_ReadReg and  LL_PKA_WriteReg functions
  * @{
  */
#define LL_PKA_CR_ADDRERRIE                PKA_CR_ADDRERRIE
#define LL_PKA_CR_RAMERRIE                 PKA_CR_RAMERRIE
#define LL_PKA_CR_PROCENDIE                PKA_CR_PROCENDIE
#define LL_PKA_CLRFR_PROCENDFC             PKA_CLRFR_PROCENDFC
#define LL_PKA_CLRFR_RAMERRFC              PKA_CLRFR_RAMERRFC
#define LL_PKA_CLRFR_ADDRERRFC             PKA_CLRFR_ADDRERRFC
/**
  * @}
  */
#if defined (STM32WB05)|| defined(STM32WB09)
/** @defgroup PKA_LL_SECLVL Value Defines
  * @brief    IT defines which can be used with LL_PKA_SetSecurityLevel and  LL_PKA_GetSecurityLevel functions
  * @{
  */
#define LL_PKA_SECURITY_LEVEL_NONE              0x00000000U
#define LL_PKA_SECURITY_LEVEL_ENABLE            0x00000001U
#endif /* STM32WB05 || STM32WB09 */
/**
  * @}
  */

/** @defgroup PKA_LL_EC_MODE Operation Mode
  * @brief    List of operation mode.
  * @{
  */

#if defined (STM32WB05)|| defined(STM32WB09)
#define LL_PKA_MODE_MONTGOMERY_PARAM_MOD_EXP ((uint32_t)0x00000000U) /*!< Compute Montgomery parameter and modular exponentiation */
#define LL_PKA_MODE_MONTGOMERY_PARAM         ((uint32_t)0x00000001U) /*!< Compute Montgomery parameter only */
#define LL_PKA_MODE_MODULAR_EXP              ((uint32_t)0x00000002U) /*!< Compute modular exponentiation only (Montgomery parameter should be loaded) */
#define LL_PKA_MODE_MONTGOMERY_PARAM_ECC     ((uint32_t)0x00000020U) /*!< Compute Montgomery parameter and compute ECC kP operation */
#define LL_PKA_MODE_ECC_KP_PRIMITIVE         ((uint32_t)0x00000022U) /*!< Compute the ECC kP primitive only (Montgomery parameter should be loaded) */
#define LL_PKA_MODE_ECDSA_SIGNATURE          ((uint32_t)0x00000024U) /*!< ECDSA signature */
#define LL_PKA_MODE_POINT_CHECK              ((uint32_t)0x00000028U) /*!< Point check */
#define LL_PKA_MODE_RSA_CRT_EXP              ((uint32_t)0x00000007U) /*!< RSA CRT exponentiation */
#define LL_PKA_MODE_MODULAR_INV              ((uint32_t)0x00000008U) /*!< Modular inversion */
#define LL_PKA_MODE_ARITHMETIC_ADD           ((uint32_t)0x00000009U) /*!< Arithmetic addition */
#define LL_PKA_MODE_ARITHMETIC_SUB           ((uint32_t)0x0000000AU) /*!< Arithmetic subtraction */
#define LL_PKA_MODE_ARITHMETIC_MUL           ((uint32_t)0x0000000BU) /*!< Arithmetic multiplication */
#define LL_PKA_MODE_COMPARISON               ((uint32_t)0x0000000CU) /*!< Comparison */
#define LL_PKA_MODE_MODULAR_REDUC            ((uint32_t)0x0000000DU) /*!< Modular reduction */
#define LL_PKA_MODE_MODULAR_ADD              ((uint32_t)0x0000000EU) /*!< Modular addition */
#define LL_PKA_MODE_MODULAR_SUB              ((uint32_t)0x0000000FU) /*!< Modular subtraction */
#define LL_PKA_MODE_MONTGOMERY_MUL           ((uint32_t)0x00000010U) /*!< Montgomery multiplication */
#endif /* STM32WB05 || STM32WB09 */

#if defined (STM32WB09)
#define LL_PKA_MODE_ECDSA_VERIFICATION       ((uint32_t)0x00000025U) /*!< ECDSA verification */
#define LL_PKA_MODE_DOUBLE_BASE_LADDER       ((uint32_t)0x00000027U)   /*!< Double base ladder */
#define LL_PKA_MODE_ECC_COMPLETE_ADD         ((uint32_t)0x00000023U)   /*!< ECC complete addition */
#endif /* STM32WB09 */
#if defined (STM32WB05)
#define LL_PKA_MODE_ECDSA_VERIFICATION       ((uint32_t)0x00000026U) /*!< ECDSA verification */
#endif /* STM32WB05 */


/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Macros PKA Exported Macros
  * @{
  */

/** @defgroup PKA_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PKA register
  * @param  __INSTANCE__ PKA Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PKA_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PKA register
  * @param  __INSTANCE__ PKA Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PKA_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Functions PKA Exported Functions
  * @{
  */

/** @defgroup PKA_LL_EF_Configuration Configuration
  * @{
  */
#if defined (STM32WB05)|| defined(STM32WB09)
/**
  * @brief  Configure PKA peripheral.
  * @brief  Set PKA operating mode.
  * @rmtoll CR           MODE          LL_PKA_Config
  * @param  PKAx PKA Instance.
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM_MOD_EXP
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM_ECC
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP
  *         @arg @ref LL_PKA_MODE_ECC_KP_PRIMITIVE
  *         @arg @ref LL_PKA_MODE_ECDSA_SIGNATURE
  *         @arg @ref LL_PKA_MODE_ECDSA_VERIFICATION
  *         @arg @ref LL_PKA_MODE_POINT_CHECK
  *         @arg @ref LL_PKA_MODE_RSA_CRT_EXP
  *         @arg @ref LL_PKA_MODE_MODULAR_INV
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_ADD
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_SUB
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_MUL
  *         @arg @ref LL_PKA_MODE_COMPARISON
  *         @arg @ref LL_PKA_MODE_MODULAR_REDUC
  *         @arg @ref LL_PKA_MODE_MODULAR_ADD
  *         @arg @ref LL_PKA_MODE_MODULAR_SUB
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_MUL
  * the next arguments are for stm32wb09 only
  *         @arg @ref LL_PKA_MODE_DOUBLE_BASE_LADDER
  *         @arg @ref LL_PKA_MODE_ECC_COMPLETE_ADD
  */

__STATIC_INLINE void LL_PKA_Config(PKA_TypeDef *PKAx, uint32_t Mode)
{
  MODIFY_REG(PKAx->CR, (PKA_CR_MODE), (Mode << PKA_CR_MODE_Pos));
}
#endif /* STM32WB05 || STM32WB09 */

#if defined (STM32WB05)|| defined(STM32WB09)
/**
  * @brief  Enable PKA peripheral.
  * @rmtoll CR           EN            LL_PKA_Enable
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_Enable(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CR, PKA_CR_EN);
}

/**
  * @brief  Disable PKA peripheral.
  * @rmtoll CR           EN            LL_PKA_Disable
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_Disable(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->CR, PKA_CR_EN);
}

/**
  * @brief  Check if the PKA peripheral is enabled or disabled.
  * @rmtoll CR           EN            LL_PKA_IsEnabled
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabled(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->CR, PKA_CR_EN) == (PKA_CR_EN)) ? 1UL : 0UL);
}
#endif /* STM32WB05 || STM32WB09 */

#if defined (STM32WB05)|| defined(STM32WB09)
/**
  * @brief  Set PKA operating mode.
  * @rmtoll CR           MODE          LL_PKA_SetMode
  * @param  PKAx PKA Instance.
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM_MOD_EXP
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM_ECC
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP
  *         @arg @ref LL_PKA_MODE_ECC_KP_PRIMITIVE
  *         @arg @ref LL_PKA_MODE_ECDSA_SIGNATURE
  *         @arg @ref LL_PKA_MODE_ECDSA_VERIFICATION
  *         @arg @ref LL_PKA_MODE_POINT_CHECK
  *         @arg @ref LL_PKA_MODE_RSA_CRT_EXP
  *         @arg @ref LL_PKA_MODE_MODULAR_INV
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_ADD
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_SUB
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_MUL
  *         @arg @ref LL_PKA_MODE_COMPARISON
  *         @arg @ref LL_PKA_MODE_MODULAR_REDUC
  *         @arg @ref LL_PKA_MODE_MODULAR_ADD
  *         @arg @ref LL_PKA_MODE_MODULAR_SUB
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_MUL
  *         @arg @ref LL_PKA_MODE_DOUBLE_BASE_LADDER
  *         @arg @ref LL_PKA_MODE_ECC_COMPLETE_ADD
  * @retval None
  */

__STATIC_INLINE void LL_PKA_SetMode(PKA_TypeDef *PKAx, uint32_t Mode)
{
  MODIFY_REG(PKAx->CR, PKA_CR_MODE, Mode << PKA_CR_MODE_Pos);
}


/**
  * @brief  Get PKA operating mode.
  * @rmtoll CR           MODE          LL_PKA_GetMode
  * @param  PKAx PKA Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM_MOD_EXP
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM_ECC
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP
  *         @arg @ref LL_PKA_MODE_ECC_KP_PRIMITIVE
  *         @arg @ref LL_PKA_MODE_ECDSA_SIGNATURE
  *         @arg @ref LL_PKA_MODE_ECDSA_VERIFICATION
  *         @arg @ref LL_PKA_MODE_POINT_CHECK
  *         @arg @ref LL_PKA_MODE_RSA_CRT_EXP
  *         @arg @ref LL_PKA_MODE_MODULAR_INV
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_ADD
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_SUB
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_MUL
  *         @arg @ref LL_PKA_MODE_COMPARISON
  *         @arg @ref LL_PKA_MODE_MODULAR_REDUC
  *         @arg @ref LL_PKA_MODE_MODULAR_ADD
  *         @arg @ref LL_PKA_MODE_MODULAR_SUB
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_MUL

  *         @arg @ref LL_PKA_MODE_DOUBLE_BASE_LADDER
  *         @arg @ref LL_PKA_MODE_ECC_COMPLETE_ADD
  */

__STATIC_INLINE uint32_t LL_PKA_GetMode(const PKA_TypeDef *PKAx)
{
  return (uint32_t)(READ_BIT(PKAx->CR, PKA_CR_MODE) >> PKA_CR_MODE_Pos);
}

/**
  * @brief  Set the Security level.
  * @rmtoll CR           SECLVL         LL_PKA_SetSecurityLevel
  * @param  arg This parameter can be one of the following values:
  *         @arg @ref LL_PKA_SECURITY_LEVEL_NONE
  *         @arg @ref LL_PKA_SECURITY_LEVEL_ENABLE
  * @param  PKAx PKA Instance.
  * @retval NONE
  */
__STATIC_INLINE void LL_PKA_SetSecurityLevel(PKA_TypeDef *PKAx, uint32_t arg)
{
  MODIFY_REG(PKAx->CR, PKA_CR_SECLVL, (arg << PKA_CR_SECLVL_Pos));
}

/**
  * @brief  Get the Security level.
  * @rmtoll CR           SECLVL         LL_PKA_GetSecurityLevel
  * @param  PKAx PKA Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PKA_SECURITY_LEVEL_NONE
  *         @arg @ref LL_PKA_SECURITY_LEVEL_ENABLE
  */
__STATIC_INLINE void LL_PKA_GetSecurityLevel(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CR, PKA_CR_SECLVL);
}
#endif /* STM32WB05 || STM32WB09 */

#if defined (STM32WB06) || defined(STM32WB07)
/**
  * @brief  Starts the operation for the PKA peripheral.
  * @rmtoll CSR           GO            LL_PKA_Start
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_Start(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CSR, PKA_CSR_GO);
  /* The Bit GO must be reset before the end of calculation */
  CLEAR_BIT(PKAx->CSR, PKA_CSR_GO);
}
#endif /* STM32WB06 || STM32WB07 */
#if defined (STM32WB05)|| defined(STM32WB09)
/**
  * @brief  Start the operation selected using LL_PKA_SetMode.
  * @rmtoll CR           START         LL_PKA_Start
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_Start(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CR, PKA_CR_START);
}
#endif /* STM32WB05 || STM32WB09 */
/**
  * @}
  */

/** @defgroup PKA_LL_EF_IT_Management IT_Management
  * @{
  */
#if defined (STM32WB06) || defined(STM32WB07)

/**
  * @brief  Enable address error interrupt.
  * @rmtoll IEN           ADDERR_EN     LL_PKA_EnableIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_ADDRERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->IEN, PKA_IEN_ADDERR_EN);
}

/**
  * @brief  Enable RAM error interrupt.
  * @rmtoll IEN           RAMERR_EN      LL_PKA_EnableIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_RAMERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->IEN, PKA_IEN_RAMERR_EN);
}

/**
  * @brief  Enable end of operation interrupt.
  * @rmtoll IEN           READY_EN     LL_PKA_EnableIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_PROCEND(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->IEN, PKA_IEN_READY_EN);
}

/**
  * @brief  Disable address error interrupt.
  * @rmtoll IEN           ADDERR_EN     LL_PKA_DisableIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_ADDRERR(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->IEN, PKA_IEN_ADDERR_EN);
}

/**
  * @brief  Disable RAM error interrupt.
  * @rmtoll IEN           RAMERR_EN      LL_PKA_DisableIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_RAMERR(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->IEN, PKA_IEN_RAMERR_EN);
}

/**
  * @brief  Disable End of operation interrupt.
  * @rmtoll IEN           READY_EN     LL_PKA_DisableIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_PROCEND(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->IEN, PKA_IEN_READY_EN);
}

/**
  * @brief  Check if address error interrupt is enabled.
  * @rmtoll IEN           ADDERR_EN     LL_PKA_IsEnabledIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_ADDRERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->IEN, PKA_IEN_ADDERR_EN) == (PKA_IEN_ADDERR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RAM error interrupt is enabled.
  * @rmtoll IEN           RAMERR_EN      LL_PKA_IsEnabledIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_RAMERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->IEN, PKA_IEN_RAMERR_EN) == (PKA_IEN_RAMERR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Check if end of operation interrupt is enabled.
  * @rmtoll IEN           READY_EN     LL_PKA_IsEnabledIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_PROCEND(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->IEN, PKA_IEN_READY_EN) == (PKA_IEN_READY_EN)) ? 1UL : 0UL);
}

#endif /* STM32WB06 || STM32WB07 */
#if defined (STM32WB05)|| defined(STM32WB09)
/**
  * @brief  Enable address error interrupt.
  * @rmtoll CR           ADDRERRIE     LL_PKA_EnableIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_ADDRERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CR, PKA_CR_ADDRERRIE);
}

/**
  * @brief  Enable RAM error interrupt.
  * @rmtoll CR           RAMERRIE      LL_PKA_EnableIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_RAMERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CR, PKA_CR_RAMERRIE);
}

/**
  * @brief  Enable end of operation interrupt.
  * @rmtoll CR           PROCENDIE     LL_PKA_EnableIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_EnableIT_PROCEND(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CR, PKA_CR_PROCENDIE);
}

/**
  * @brief  Disable address error interrupt.
  * @rmtoll CR           ADDRERRIE     LL_PKA_DisableIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_ADDRERR(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->CR, PKA_CR_ADDRERRIE);
}

/**
  * @brief  Disable RAM error interrupt.
  * @rmtoll CR           RAMERRIE      LL_PKA_DisableIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_RAMERR(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->CR, PKA_CR_RAMERRIE);
}

/**
  * @brief  Disable End of operation interrupt.
  * @rmtoll CR           PROCENDIE     LL_PKA_DisableIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_DisableIT_PROCEND(PKA_TypeDef *PKAx)
{
  CLEAR_BIT(PKAx->CR, PKA_CR_PROCENDIE);
}


/**
  * @brief  Check if address error interrupt is enabled.
  * @rmtoll CR           ADDRERRIE     LL_PKA_IsEnabledIT_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_ADDRERR(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->CR, PKA_CR_ADDRERRIE) == (PKA_CR_ADDRERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RAM error interrupt is enabled.
  * @rmtoll CR           RAMERRIE      LL_PKA_IsEnabledIT_RAMERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_RAMERR(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->CR, PKA_CR_RAMERRIE) == (PKA_CR_RAMERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if end of operation interrupt is enabled.
  * @rmtoll CR           PROCENDIE     LL_PKA_IsEnabledIT_PROCEND
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_PROCEND(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->CR, PKA_CR_PROCENDIE) == (PKA_CR_PROCENDIE)) ? 1UL : 0UL);
}
#endif /* STM32WB05 || STM32WB09 */
/**
  * @}
  */

/** @defgroup PKA_LL_EF_FLAG_Management PKA flag management
  * @{
  */
#if defined (STM32WB06) || defined(STM32WB07)
/**
  * @brief  Get PKA address error flag.
  * @rmtoll ISR           ADD_ERR      LL_PKA_IsActiveFlag_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_ADDRERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->ISR, PKA_ISR_ADD_ERR) == (PKA_ISR_ADD_ERR)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA RAM error flag.
  * @rmtoll ISR           RAM_ERR       LL_PKA_IsActiveFlag_RAMERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_RAMERR(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->ISR, PKA_ISR_RAM_ERR) == (PKA_ISR_RAM_ERR)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA end of operation flag.
  * @rmtoll ISR           PROC_END      LL_PKA_IsActiveFlag_PROCEND
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_PROCEND(PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->ISR, PKA_ISR_PROC_END) == (PKA_ISR_PROC_END)) ? 1UL : 0UL);
}

/**
  * @brief  Clear PKA address error flag.
  * @rmtoll ISR        ADD_ERR     LL_PKA_ClearFlag_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_ADDRERR(PKA_TypeDef *PKAx)
{
  /* To clear the pending interrupt,
   * the user must write this bit to 1
   * and clear it just after by writing 0.
   */
  SET_BIT(PKAx->ISR, PKA_ISR_ADD_ERR);
  CLEAR_BIT(PKAx->ISR, PKA_ISR_ADD_ERR);
}

/**
  * @brief  Clear PKA RAM error flag.
  * @rmtoll ISR        RAM_ERR      LL_PKA_ClearFlag_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_RAMERR(PKA_TypeDef *PKAx)
{
  /* To clear the pending interrupt,
   * the user must write this bit to 1
   * and clear it just after by writing 0.
   */
  SET_BIT(PKAx->ISR, PKA_ISR_RAM_ERR);
  CLEAR_BIT(PKAx->ISR, PKA_ISR_RAM_ERR);
}

/**
  * @brief  Clear PKA end of operation flag.
  * @rmtoll ISR        PROC_END     LL_PKA_ClearFlag_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_PROCEND(PKA_TypeDef *PKAx)
{
  /* To clear the pending interrupt,
   * the user must write this bit to 1
   * and clear it just after by writing 0.
   */
  SET_BIT(PKAx->ISR, PKA_ISR_PROC_END);
  CLEAR_BIT(PKAx->ISR, PKA_ISR_PROC_END);
}
#endif /* STM32WB06 || STM32WB07 */

#if defined (STM32WB05)|| defined(STM32WB09)
/**
  * @brief  Get PKA address error flag.
  * @rmtoll SR           ADDRERRF      LL_PKA_IsActiveFlag_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_ADDRERR(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->SR, PKA_SR_ADDRERRF) == (PKA_SR_ADDRERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA RAM error flag.
  * @rmtoll SR           RAMERRF       LL_PKA_IsActiveFlag_RAMERR
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_RAMERR(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->SR, PKA_SR_RAMERRF) == (PKA_SR_RAMERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA end of operation flag.
  * @rmtoll SR           PROCENDF      LL_PKA_IsActiveFlag_PROCEND
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_PROCEND(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->SR, PKA_SR_PROCENDF) == (PKA_SR_PROCENDF)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA busy flag.
  * @rmtoll SR           BUSY          LL_PKA_IsActiveFlag_BUSY
  * @param  PKAx PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_BUSY(const PKA_TypeDef *PKAx)
{
  return ((READ_BIT(PKAx->SR, PKA_SR_BUSY) == (PKA_SR_BUSY)) ? 1UL : 0UL);
}

/**
  * @brief  Clear PKA address error flag.
  * @rmtoll CLRFR        ADDRERRFC     LL_PKA_ClearFlag_ADDRERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_ADDRERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CLRFR, PKA_CLRFR_ADDRERRFC);
}

/**
  * @brief  Clear PKA RAM error flag.
  * @rmtoll CLRFR        RAMERRFC      LL_PKA_ClearFlag_RAMERR
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_RAMERR(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CLRFR, PKA_CLRFR_RAMERRFC);
}

/**
  * @brief  Clear PKA end of operation flag.
  * @rmtoll CLRFR        PROCENDFC     LL_PKA_ClearFlag_PROCEND
  * @param  PKAx PKA Instance.
  * @retval None
  */
__STATIC_INLINE void LL_PKA_ClearFlag_PROCEND(PKA_TypeDef *PKAx)
{
  SET_BIT(PKAx->CLRFR, PKA_CLRFR_PROCENDFC);
}
#endif /* STM32WB05 || STM32WB09 */

/**
  * @}
  */
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PKA_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_PKA_DeInit(const PKA_TypeDef *PKAx);
#if defined (STM32WB05)|| defined(STM32WB09)
ErrorStatus LL_PKA_Init(PKA_TypeDef *PKAx, LL_PKA_InitTypeDef *PKA_InitStruct);
void LL_PKA_StructInit(LL_PKA_InitTypeDef *PKA_InitStruct);
#endif /* STM32WB05 || STM32WB09 */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */
/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(PKA) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WB0x_LL_PKA_H */
