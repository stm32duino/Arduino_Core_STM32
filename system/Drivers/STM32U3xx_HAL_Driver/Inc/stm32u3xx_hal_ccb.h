/**
  ******************************************************************************
  * @file    stm32u3xx_hal_ccb.h
  * @author  MCD Application Team
  * @brief   Header file of CCB HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U3xx_HAL_CCB_H
#define STM32U3xx_HAL_CCB_H

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */
#if defined(CCB) && defined(HAL_CCB_MODULE_ENABLED)
/** @addtogroup CCB
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CCB_Exported_Types CCB Exported Types
  * @{
  */

/**
  * @brief  HAL CCB Handle Structure definition
  */
typedef struct
{
  CCB_TypeDef *Instance;                    /*!< CCB registers base address                           */
  __IO uint32_t State;                      /*!< Global state of the CCB HAL driver                   */
#if !defined(GENERATOR_C7AMBA_CCB_V1_0)
  __IO uint32_t RNGState;                   /*!< Internal state of the RNG instance                   */
  __IO uint32_t PKAState;                   /*!< Internal state of the PKA instance                   */
  __IO uint32_t SAESState;                  /*!< Internal state of the SAES instance                  */
#endif /* (GENERATOR_C7AMBA_CCB_V1_0) */
  __IO uint32_t ErrorCode;                  /*!< Error code in case of HAL driver  error              */
} CCB_HandleTypeDef;

/** @brief  CCB Wrapping Key definition
  */
typedef struct
{
  uint32_t WrappingKeyType;                 /*!< This parameter can be value of @ref CCB_WrappingKeyTypeDef */
  uint32_t AES_Algorithm;                   /*!< Used only when wrappingkey type is HAL_CCB_USER_KEY_WRAPPED,
                                                 AES Algorithm. This parameter can be a value of
                                                 @ref CCB_AES_Algorithm_Mode */
  uint32_t *pInitVect;                      /*!< Used only when wrappingkey type is HAL_CCB_USER_KEY_WRAPPED,
                                                 Pointer to the initialization vector, counter with CBC Algorithm */
  uint32_t *pUserWrappedWrappingKey;        /*!< Used only when wrappingkey type is HAL_CCB_USER_KEY_WRAPPED,
                                                 Pointer to the wrapped wrapping Key */
} CCB_WrappingKeyTypeDef;

/**
  * @brief  CCB ECDSA and ECC scalar Multiplication curve parameters
  */
typedef struct
{
  uint32_t primeOrderSizeByte;              /*!< Number of element in primeOrder array in byte*/
  uint32_t modulusSizeByte;                 /*!< Number of element in modulus array in byte */
  uint32_t coefSignA;                       /*!< Curve coefficient a sign */
  const uint8_t *pAbsCoefA;                 /*!< Pointer to curve coefficient |a|     (Array of modulusSize elements) */
  const uint8_t *pCoefB;                    /*!< Pointer to B coefficient             (Array of modulusSize elements) */
  const uint8_t *pModulus;                  /*!< Pointer to curve modulus value p     (Array of modulusSize elements) */
  const uint8_t *pPrimeOrder;               /*!< Pointer to order of the curve n      (Array of primeOrderSize elements) */
  const uint8_t *pPointX;                   /*!< Pointer to curve base point xG       (Array of modulusSize elements) */
  const uint8_t *pPointY;                   /*!< Pointer to curve base point yG       (Array of modulusSize elements) */
} CCB_ECDSACurveParamTypeDef, CCB_ECCMulCurveParamTypeDef;

/** @brief  CCB ECDSA Key Blob definition
  */
typedef struct
{
  uint32_t *pIV;                            /*!< Pointer to the Initial Vector */
  uint32_t *pTag;                           /*!< Pointer to the Tag */
  uint32_t *pWrappedKey;                    /*!< Pointer to the Wrapped Key */
} CCB_ECDSAKeyBlobTypeDef, CCB_ECCMulKeyBlobTypeDef;

/**
  * @brief  CCB ECDSA Signature definition
  */
typedef struct
{
  uint8_t *pRSign;                          /*!< Pointer to signature part r          (Array of modulusSize elements) */
  uint8_t *pSSign;                          /*!< Pointer to signature part s          (Array of modulusSize elements) */
} CCB_ECDSASignTypeDef;

/**
  * @brief  CCB ECC scalar multiplication point definition
  */
typedef struct
{
  uint8_t *pPointX;                         /*!< Pointer to point P coordinate xP */
  uint8_t *pPointY;                         /*!< Pointer to point P coordinate yP */
} CCB_ECCMulPointTypeDef;

/**
  * @brief  CCB RSA clear key definition
  */
typedef struct
{
  uint8_t *pExp;                            /*!< Pointer to Exponent */
  uint8_t *pPhi;                            /*!< Pointer to Phi value */
} CCB_RSAClearKeyTypeDef;

/**
  * @brief  CCB RSA Modular exponatiation parameters
  */
typedef struct
{
  uint32_t expSizeByte;                     /*!< Number of element in pExp and pMontgomeryParam arrays */
  uint32_t modulusSizeByte;                 /*!< Number of element in modulus array */
  const uint8_t *pMod;                      /*!< Pointer to modulus              (Array of OpSize elements) */
} CCB_RSAParamTypeDef;

/**
  * @brief  CCB RSA Modular exponatiation Key Blob definition
  */
typedef struct
{
  uint32_t *pIV;                            /*!< Pointer to the Initial Vector */
  uint32_t *pTag;                           /*!< Pointer to the Tag */
  uint32_t *pWrappedExp;                    /*!< Pointer to the Wrapped Exponent */
  uint32_t *pWrappedPhi;                    /*!< Pointer to the Wrapped Phi */
} CCB_RSAKeyBlobTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup CCB_Exported_Constants CCB Exported Constants
  * @{
  */

/** @defgroup CCB_State CCB State
  * @{
  */
#define HAL_CCB_STATE_RESET                 (0x00000000U)  /*!< CCB not yet initialized or disabled                */
#define HAL_CCB_STATE_READY                 (0xDA5DA605U) /*!< CCB is ready for operation                         */
#define HAL_CCB_STATE_BUSY                  (0x00000002U)  /*!< CCB BUSY, internal processing is ongoing           */
#define HAL_CCB_STATE_ERROR                 (0x00000003U)  /*!< Blocking error, driver should be re-initialized    */

/**
  * @}
  */

/** @defgroup CCB_AES_Algorithm_Mode AES Algorithm Mode
  * @{
  */
#define CCB_AES_ECB            0x00000000U                 /*!< Electronic codebook chaining algorithm   */
#define CCB_AES_CBC            AES_CR_CHMOD_0              /*!< Cipher block chaining algorithm          */

/**
  * @}
  */

/** @defgroup CCB_ErrorCode CCB Error Code
  * @{
  */
#define HAL_CCB_ERROR_NONE                  (0x00000000U)  /*!< No error                         */
#define HAL_CCB_ERROR_INVALID_PARAM         (0x00000001U)  /*!< Invalid parameters error         */
#define HAL_CCB_ERROR_OPERATION             (0x00000002U)  /*!< Operation error                  */
#define HAL_CCB_ERROR_SAES_TAMP             (0x00000010U)  /*!< SAES TAMP ERROR                  */
#define HAL_CCB_ERROR_RNG_TAMP              (0x00000020U)  /*!< RNG TAMP ERROR                   */
#define HAL_CCB_ERROR_PKAREG_TAMP           (0x00000040U)  /*!< PKA Register TAMP ERROR          */
#define HAL_CCB_ERROR_PKAOPR_TAMP           (0x00000080U)  /*!< PKA Operation TAMP ERROR         */
#define HAL_CCB_ERROR_PKARAM_ERASE          (0x00000100U)  /*!< PKA RAM erase ERROR              */

/**
  * @}
  */

/** @defgroup CCB_WrappingKeyTypeDef CCB Wrapping Key definition
  * @{
  */
#define HAL_CCB_USER_KEY_WRAPPED       (0x00000000U)    /*!< the wrapped key is a SW user key */
#define HAL_CCB_USER_KEY_HW            AES_CR_KEYSEL_0  /*!< Hardware key : derived hardware
                                                                      unique key (DHUK 256-bit) */
#define HAL_CCB_USER_KEY_HSW           AES_CR_KEYSEL_2  /*!< DHUK XOR BHK Hardware unique
                                                                      key XOR software key */

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CCB_Exported_Functions
  * @{
  */

/* Initialization/de-initialization functions  ********************************/
/** @addtogroup CCB_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef     HAL_CCB_Init(CCB_HandleTypeDef *hccb);
void                  HAL_CCB_MspInit(CCB_HandleTypeDef *hccb);
HAL_StatusTypeDef     HAL_CCB_DeInit(CCB_HandleTypeDef *hccb);
void                  HAL_CCB_MspDeInit(CCB_HandleTypeDef *hccb);

/**
  * @}
  */

/* Handler functions ********************************/
/** @addtogroup CCB_Exported_Functions_Group2
  * @{
  */
uint32_t HAL_CCB_GetError(const CCB_HandleTypeDef *hccb);
uint32_t HAL_CCB_GetState(const CCB_HandleTypeDef *hccb);
uint32_t HAL_CCB_GetOperationError(const CCB_HandleTypeDef *hccb);

/**
  * @}
  */

/* Operation functions *****************************************************/
/** @addtogroup CCB_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_CCB_ECDSA_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey,
                                                 CCB_WrappingKeyTypeDef *pWrappingKey);
HAL_StatusTypeDef HAL_CCB_ECC_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey,
                                               CCB_WrappingKeyTypeDef *pWrappingKey);
HAL_StatusTypeDef HAL_CCB_RSA_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey,
                                               CCB_WrappingKeyTypeDef *pWrappingKey);

HAL_StatusTypeDef HAL_CCB_ECDSA_WrapPrivateKey(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                               const uint8_t *pClearPrivateKey,
                                               CCB_WrappingKeyTypeDef *pWrappingKey,
                                               const CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob);

HAL_StatusTypeDef HAL_CCB_ECDSA_GenerateWrapPrivateKey(CCB_HandleTypeDef *hccb,
                                                       CCB_ECDSACurveParamTypeDef *pCurveParam,
                                                       CCB_WrappingKeyTypeDef *pWrappingKey,
                                                       CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob);

HAL_StatusTypeDef HAL_CCB_ECDSA_Sign(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                     CCB_WrappingKeyTypeDef *pWrappingKey,
                                     CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob, const uint8_t *pHash,
                                     CCB_ECDSASignTypeDef *pSignature);
HAL_StatusTypeDef HAL_CCB_ECDSA_ComputePublicKey(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                                 CCB_WrappingKeyTypeDef *pWrappingKey,
                                                 CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob,
                                                 CCB_ECCMulPointTypeDef *pPublicKey);

HAL_StatusTypeDef HAL_CCB_ECC_WrapPrivateKey(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                             const uint8_t *pClearPrivateKey,
                                             CCB_WrappingKeyTypeDef *pWrappingKey,
                                             CCB_ECCMulKeyBlobTypeDef *pWrappedPrivateKeyBlob);

HAL_StatusTypeDef HAL_CCB_ECC_GenerateWrapPrivateKey(CCB_HandleTypeDef *hccb,
                                                     CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                     CCB_WrappingKeyTypeDef *pWrappingKey,
                                                     CCB_ECCMulKeyBlobTypeDef *pWrappedPrivateKeyBlob);

HAL_StatusTypeDef HAL_CCB_ECC_ComputeScalarMul(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                               CCB_WrappingKeyTypeDef *pWrappingKey,
                                               CCB_ECCMulKeyBlobTypeDef *pWrappedPrivateKeyBlob,
                                               CCB_ECCMulPointTypeDef *pInputPoint,
                                               CCB_ECCMulPointTypeDef *pOutputPoint);

HAL_StatusTypeDef HAL_CCB_RSA_WrapPrivateKey(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                             const CCB_RSAClearKeyTypeDef *pRSAClearPrivateKey,
                                             CCB_WrappingKeyTypeDef *pWrappingKey,
                                             CCB_RSAKeyBlobTypeDef *pWrappedPrivateKeyBlob);
HAL_StatusTypeDef HAL_CCB_RSA_ComputeModularExp(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                                CCB_WrappingKeyTypeDef *pWrappingKey,
                                                CCB_RSAKeyBlobTypeDef *pWrappedPrivateKeyBlob,
                                                const uint8_t *pOperand, uint8_t *pModularExp);

/* Callback functions in non-blocking modes ***********************************/
void HAL_CCB_IntrusionCallback(CCB_HandleTypeDef *hccb);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(CCB) && defined(HAL_CCB_MODULE_ENABLED) */
/**
  * @}
  */
#endif /* STM32U3xx_HAL_CCB_H */
