/**
  ******************************************************************************
  * @file    stm32u3xx_hal_ccb.c
  * @author  MCD Application Team
  * @brief   CCB HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Inter Integrated Circuit (CCB) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
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
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
    The CCB HAL driver can be used as follows:

    (#) Declare a CCB_HandleTypeDef handle structure, for example: CCB_HandleTypeDef  hccb;

    (#) Initialize the CCB low level resources by implementing the HAL_CCB_MspInit() API:
        (##) Enable the CCB interface clock

    (#) Initialize the CCB registers by calling the HAL_CCB_Init() API which trig
        HAL_CCB_MspInit().

    (#) Fill entirely the structures corresponding to your operation:
        For instance: CCB_ECDSACurveParamTypeDef and CCB_ECDSAKeyBlobTypeDef
        for HAL_CCB_ECDSA_WrapPrivateKey().

    (#) Execute the operation and check the returned value.

    (#) Call the function HAL_CCB_DeInit() to restore the default configuration which trig
        HAL_CCB_MspDeInit().

    *** High level operation ***
    =================================
    [..]
      (+) Input structure requires buffers as uint8_t array.

      (+) Output structure requires buffers as uint8_t array.

      (+) Proteted ECDSA Sign
      (++) HAL_CCB_ECDSA_WrapPrivateKey() for protected ECDSA blob creation when using user key.
      (++) HAL_CCB_ECDSA_GenerateWrapPrivateKey() for protected ECDSA blob creation when using internal key.
      (++) HAL_CCB_ECDSA_Sign() for protected ECDSA Signing message usage.
      (++) HAL_CCB_ECDSA_ComputePublicKey() for protected ECDSA computing public key usage.

      (+) Proteted ECC Scalar Multiplication
      (++) HAL_CCB_ECC_WrapPrivateKey() for protected ECC blob creation when using user key.
      (++) HAL_CCB_ECC_GenerateWrapPrivateKey() for protected ECC blob creation when using internal key.
      (++) HAL_CCB_ECC_ComputeScalarMul() for protected ECC scalar multiplication usage.

      (+) Proteted RSA Modular Exponentiation
      (++) HAL_CCB_RSA_WrapPrivateKey() for protected RSA blob creation when using user key.
      (++) HAL_CCB_RSA_ComputeModularExp() for protected RSA computing modular exponetiation usage.

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */
#if defined(CCB) && defined(HAL_CCB_MODULE_ENABLED)

/** @defgroup CCB CCB
  * @brief CCB HAL module driver
  * @{
  */

/* Private define ------------------------------------------------------------*/
/** @addtogroup CCB_Private_Defines
  * @{
  */

/** @defgroup CCB_TIMEOUT_DEFAULT_VALUE CCB timout Default Value
  * @{
  */
#ifndef HAL_CCB_TIMEOUT_DEFAULT_VALUE
#define HAL_CCB_TIMEOUT_DEFAULT_VALUE      0xFFFFU         /* CCB Timeout.*/
#endif /*HAL_CCB_TIMEOUT_DEFAULT_VALUE */

/**
  * @}
  */

/** @defgroup CCB_Operations CCB Operations
  * @{
  */
#define CCB_ECDSA_SIGN_CPU_BLOB_CREATION     (0x000000C0U)  /*!< ECDSA signature blob creation with priv key from the CPU */
#define CCB_ECDSA_SIGN_RNG_BLOB_CREATION     (0x000000C2U)  /*!< ECDSA signature blob creation with priv key from the RNG */
#define CCB_ECDSA_SIGN_BLOB_USE              (0x000000C3U)  /*!< ECDSA signature blob use for ECDSA signature */
#define CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION (0x00000080U)  /*!< ECC scalar multiplication blob creation with priv key from the CPU- */
#define CCB_ECC_SCALAR_MUL_RNG_BLOB_CREATION (0x00000082U)  /*!< ECC scalar multiplication blob creation with priv key from the RNG */
#define CCB_ECC_SCALAR_MUL_BLOB_USE          (0x00000081U)  /*!< ECC Scalar multiplication blob use, or ECDSA signature blob use for public key computation */
#define CCB_MODULAR_EXP_CPU_BLOB_CREATION    (0x00000044U)  /*!< Modular exponentiation blob creation with priv key from the CPU */
#define CCB_MODULAR_EXP_BLOB_USE             (0x00000045U)  /*!< Modular exponentiation blob use */
#define CCB_PKA_ECDSA_VERIF_OK               (0x0000D60DU)  /*!< PKA ECDSA Signature verification success */

/**
  * @}
  */

/** @defgroup CCB_PKA_Mode CCB PKA mode
  * @{
  */
#define CCB_PKA_MODE_MODULAR_EXP_PROTECT     (0x00000003U)  /*!< PKA Modular exponentiation */
#define CCB_PKA_ECC_MUL_MODE                 (0x00000020U)  /*!< PKA ECC scalar multiplication */
#define CCB_PKA_ECDSA_SIGNATURE_MODE         (0x00000024U)  /*!< PKA ECDSA signature */
#define CCB_PKA_MODE_ECDSA_VERIFICATION      (0x00000026U)  /*!< PKA ECDSA verification */
#define CCB_PKA_ERROR_OPERATION_NONE         (0x0000D60DU)  /*!< No PKA Hardware operation error */
#define CCB_PKA_RAM_SIZE                     (0x00000536U)  /*!< CCB PKA Ram Size */

/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup CCB_Private_Constants CCB Private Constants
  * @{
  */
#define CCB_FAKE_VALUE               0X0001UL /*!< Fake value used for SAES_IVRs                             */
#define CCB_MAGIC_VALUE              0X0CCBUL /*!< Magic number used when chaining key from SAES to PKA RAM  */
#define CCB_IV0_VALUE                0X0002UL /*!< SAES_IVR0 that must be equal to 0x2                       */
#define CCB_BLOCK_SIZE               0X0004UL /*!< Block size is 128 Bits (4*32 bits)                        */
#define CCB_SIZE_SKEY_INWORD         0X0008UL /*!< Symmetric key size is always 256 (8*32 bits)              */
#define CCB_COMPUTE_PUBLIC_KEY       0x02U    /*!< CCB compute public key                                    */
#define CCB_VERIF_OPERATION_ENABLED  0x01U    /*!< CCB verification enabled                                  */
#define CCB_VERIF_OPERATION_DISABLED 0U       /*!< CCB verification disabled                                 */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @addtogroup CCB_Private_Macros
  * @{
  */
#define RAM_PARAM_END(TAB,INDEX)                do{                                   \
                                                                    TAB[INDEX] = 0UL;       \
                                                                    TAB[INDEX + 1U] = 0UL;  \
                                                                  } while(0)

#define HAL_CCB_GET_FLAG(__HANDLE__, __FLAG__)                  (((((__HANDLE__)->Instance->SR)\
                                                                   & (__FLAG__)) == (__FLAG__)) ? SET : RESET)

#define HAL_CCB_GET_SAES_FLAG(__FLAG__)           (((__FLAG__)>1U)  ?                    \
                                                   (((SAES->SR & (__FLAG__)) == (__FLAG__)) ? SET : RESET) :\
                                                   (((SAES->ISR & (__FLAG__)) == (__FLAG__)) ? SET : RESET) )

#define HAL_CCB_GET_PKA_FLAG(__FLAG__)              ((((PKA->SR)\
                                                       & (__FLAG__)) == (__FLAG__)) ? SET : RESET)

#define HAL_CCB_CLEAR_PKA_FLAG(__FLAG__)            WRITE_REG(PKA->CLRFR, (__FLAG__))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Polling Private function */
static HAL_StatusTypeDef CCB_WaitOperStep(CCB_HandleTypeDef *hccb, uint32_t step, uint32_t Timeout);
static HAL_StatusTypeDef CCB_WaitFLAG(CCB_HandleTypeDef *hccb, uint32_t flag, uint32_t Timeout);
static HAL_StatusTypeDef Protect_PKA_WaitFLAG(CCB_HandleTypeDef *hccb, uint32_t flag, uint32_t Timeout);
static HAL_StatusTypeDef Unprotect_PKA_WaitFLAG(uint32_t flag, uint32_t Timeout);
static HAL_StatusTypeDef CCB_RNG_Wait_SET_FLAG(uint32_t flag, uint32_t Timeout);
static HAL_StatusTypeDef Protect_SAES_WaitFLAG(CCB_HandleTypeDef *hccb, uint32_t flag, FlagStatus Status,
                                               uint32_t Timeout);

/* Set parameters Private function */
static HAL_StatusTypeDef CCB_ECDSASign_SetPram(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *in);
static HAL_StatusTypeDef CCB_ECCMul_SetPram(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *in);
static HAL_StatusTypeDef CCB_RSAModExp_SetPram(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *in);
static HAL_StatusTypeDef CCB_SetPram(CCB_HandleTypeDef *hccb, uint32_t modulusSizeByte, uint32_t dst_address,
                                     const uint8_t *src);

/* Initialization Private function */
static HAL_StatusTypeDef Protect_PKA_Init(CCB_HandleTypeDef *hccb, uint32_t Operation);
static HAL_StatusTypeDef Unprotected_PKA_Init(void);
static HAL_StatusTypeDef CCB_RNG_Init(void);

/* Wrapping Private function */
static HAL_StatusTypeDef WrappingKeyConfiguration(CCB_HandleTypeDef *hccb, uint32_t Operation,
                                                  CCB_WrappingKeyTypeDef *pWrappingKey);
static HAL_StatusTypeDef Protect_SAES_UnwrapKey(CCB_HandleTypeDef *hccb, const CCB_WrappingKeyTypeDef *pWrappingKey,
                                                uint32_t Timeout);

/* Data managementPrivate function */
static uint32_t GetOptBitSize_u8(uint32_t byteNumber, uint8_t msb);
static void CCB_Memcpy_u8_to_u32(__IO uint32_t dst[], const uint8_t src[], size_t size);
static void CCB_Memcpy_u32_to_u8(uint8_t dst[], __IO const uint32_t src[], size_t n);
static void CCB_Memcpy_u32_to_u32(__IO uint32_t dst[], __IO const uint32_t src[], size_t n);
static void CCB_Memcpy_u8_to_u64(__IO uint32_t dst[], const uint8_t src[]);
static void CCB_Memcpy_Not_Align(__IO uint32_t dst[], const uint8_t src[], size_t size);
static uint32_t CCB_get_cipherkey_size(CCB_ECDSACurveParamTypeDef *pCurveParam);

/* Blob processing Private function */
static HAL_StatusTypeDef CCB_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey, uint32_t operation,
                                              CCB_WrappingKeyTypeDef *pWrappingKey);
static HAL_StatusTypeDef CCB_BlobCreation_InitialPhase(CCB_HandleTypeDef *hccb, uint32_t *IV);
static HAL_StatusTypeDef CCB_BlobUse_InitialPhase(CCB_HandleTypeDef *hccb, const uint32_t *pIV, uint32_t *pTag);
static HAL_StatusTypeDef CCB_BlobCreation_FinalPhase(CCB_HandleTypeDef *hccb, uint32_t Operation, uint32_t *pTag,
                                                     uint32_t sizeparam);
static HAL_StatusTypeDef CCB_BlobUse_FinalPhase(CCB_HandleTypeDef *hccb, uint32_t Operation, uint32_t sizeparam);
static HAL_StatusTypeDef CCB_ECDSA_SignBlobCreation(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                                    const uint8_t *pClearPrivateKey,
                                                    CCB_WrappingKeyTypeDef *pWrappingKey,
                                                    uint32_t *pIV, uint32_t *pTag, uint32_t *pWarappedKey,
                                                    uint8_t CCB_Operation);
static HAL_StatusTypeDef CCB_ECC_ScalarMulBlobCreation(CCB_HandleTypeDef *hccb,
                                                       CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                       const uint8_t *pClearPrivateKey,
                                                       CCB_WrappingKeyTypeDef *pWrappingKey,
                                                       uint32_t *pIV, uint32_t *pTag, uint32_t *pWarappedKey,
                                                       uint8_t CCB_Operation);
static HAL_StatusTypeDef CCB_ECC_ComputeScalarMul(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                  CCB_WrappingKeyTypeDef *pWrappingKey,
                                                  uint32_t *pIV, uint32_t *pTag, uint32_t *pWarappedKey,
                                                  CCB_ECCMulPointTypeDef *pInputPoint,
                                                  CCB_ECCMulPointTypeDef *pOutputPoint,
                                                  const uint32_t *pPublicKey,
                                                  uint8_t VerifOperation);
static HAL_StatusTypeDef CCB_RSA_ExpBlobCreation(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                                 const CCB_RSAClearKeyTypeDef *pRSAClearPrivateKey,
                                                 CCB_WrappingKeyTypeDef *pWrappingKey, uint32_t *pIV,
                                                 uint32_t *pTag, uint32_t *pWrappedExp, uint32_t *pWrappedPhi);
static HAL_StatusTypeDef CCB_RSA_ComputeModularExp(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                                   CCB_WrappingKeyTypeDef *pWrappingKey, uint32_t *pIV,
                                                   uint32_t *pTag, uint32_t *pWrappedExp, uint32_t *pWrappedPhi,
                                                   const uint8_t *pOperand, uint8_t *pModularExp,
                                                   const uint32_t *pReferenceModularExp, uint8_t VerifOperation);
static HAL_StatusTypeDef PKA_ECDSASign(CCB_ECDSACurveParamTypeDef *pCurveParam,
                                       const uint8_t *pClearPrivateKey, uint8_t *pInteger, uint8_t *pHash,
                                       CCB_ECDSASignTypeDef *pSignature);

static HAL_StatusTypeDef PKA_ECC_ComputeScalarMul(CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                  const uint8_t *pClearPrivateKey, uint32_t PublicKey[2][20]);
static HAL_StatusTypeDef PKA_RSA_ComputeModularExp(CCB_RSAParamTypeDef *pParam,
                                                   const CCB_RSAClearKeyTypeDef *pRSAClearPrivateKey,
                                                   uint8_t *pOp1, uint32_t *pReferenceModularExp);
static HAL_StatusTypeDef PKA_ECDSAVerif(CCB_ECDSACurveParamTypeDef *pCurveParam,
                                        CCB_ECCMulPointTypeDef *pPublicKeyOut, const uint8_t *pHash,
                                        CCB_ECDSASignTypeDef *pSignature);
static uint32_t PKA_ECDSAVerif_Result(void);
static HAL_StatusTypeDef PKA_RAM_Erase(void);
static void CCB_PKA_RAMReset(void);
/** @defgroup CCB_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          deinitialize the CCB peripheral:

      (+) User must implement HAL_CCB_MspInit() function in which he configures
          all related peripherals resources.

      (+) Call the function HAL_CCB_Init() to configure the device.

      (+) Call the function HAL_CCB_DeInit() to restore the default configuration
          of the selected CCB peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the CCB associated handle
  *         according to the specified parameters.
  * @param  hccb CCB handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CCB_Init(CCB_HandleTypeDef *hccb)
{
  /* Check the CCB handle allocation */
  if (hccb == NULL)
  {
    /* Return error */
    return HAL_ERROR;
  }

  /* Initialization of the hardware */
  HAL_CCB_MspInit(hccb);

  /* PKA RAM RESET*/
  CCB_PKA_RAMReset();

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Initialize the CCB MSP.
  * @param  hccb CCB handle
  * @retval None
  */
__weak void HAL_CCB_MspInit(CCB_HandleTypeDef *hccb)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hccb);
  /* NOTE : This function should not be modified, when the callback is needed,
  the HAL_CCB_MspInit can be implemented in the user file
  */
}

/**
  * @brief  DeInitialize the CCB peripheral.
  * @param  hccb CCB handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CCB_DeInit(CCB_HandleTypeDef *hccb)
{
  /* Check the CCB handle allocation */
  if (hccb == NULL)
  {
    /* Return error */
    return HAL_ERROR;
  }

  /* Set CCB IPRST */
  SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* CCB is busy while CCB IPRST is in progress --> waiting flag */
  if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  /* clear CCB IPRST */
  CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* De-initialize the hardware */
  HAL_CCB_MspDeInit(hccb);

  /* Reset the driver state */
  hccb->State = HAL_CCB_STATE_RESET;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  DeInitialize the CCB MSP.
  * @param  hccb CCB handle
  * @retval None
  */
__weak void HAL_CCB_MspDeInit(CCB_HandleTypeDef *hccb)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hccb);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CCB_MspDeInit can be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup CCB_Exported_Functions_Group2 Peripheral State and Errorfunctions
  *  @brief set symmetric key functions
  *
@verbatim
 ===============================================================================
            ##### Peripheral State and Error functions #####
 ===============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Return the CCB error code.
  * @param  hccb : pointer to a CCB_HandleTypeDef structure
  * @retval CCB error code
  */
uint32_t HAL_CCB_GetError(const CCB_HandleTypeDef *hccb)
{
  return hccb->ErrorCode;
}

/**
  * @brief  Returns the CCB state.
  * @param  hccb: pointer to a CCB_HandleTypeDef structure
  * @retval State code
  */
uint32_t HAL_CCB_GetState(const CCB_HandleTypeDef *hccb)
{
  return hccb->State;
}

/**
  * @brief  Return the CCB hardware operartion error code.
  * @param  hccb : pointer to a CCB_HandleTypeDef structure
  * @retval CCB hardware operartion error code
  */
uint32_t HAL_CCB_GetOperationError(const CCB_HandleTypeDef *hccb)
{
  return ((hccb->Instance->SR & 0x1F00U) >> 8U);
}

/**
  * @}
  */

/** @defgroup CCB_Exported_Functions_Group3 operation functions
  *  @brief set symmetric key functions
  *
@verbatim
 ===============================================================================
                         ##### operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the CCB operations.

    (#) There are three type of CCB/PKA protected operations:
       (++) ECDSA sign : The operation is performed in the polling mode.
            These functions return when data operation is completed.
       (++) ECC Scalar Multiplication : The operation is performed using Interrupts.
            These functions return immediately.
            The end of the operation is indicated by HAL_PKA_ErrorCallback in case of error.
            The end of the operation is indicated by HAL_PKA_OperationCpltCallback in case of success.
            To stop any operation in interrupt mode, use HAL_PKA_Abort().
       (++) RSA Modular Exponentiation : The operation is performed using Interrupts.
            These functions return immediately.
            The end of the operation is indicated by HAL_PKA_ErrorCallback in case of error.
            The end of the operation is indicated by HAL_PKA_OperationCpltCallback in case of success.
            To stop any operation in interrupt mode, use HAL_PKA_Abort().

    (#) ECDSA sign functions are :
       (++) HAL_CCB_ECDSA_WrapPrivateKey()for blob creation.
       (++) HAL_CCB_ECDSA_GenerateWrapPrivateKey()for blob creation.
       (++) HAL_CCB_ECDSA_Sign() for blob usage.
       (++) HAL_CCB_ECDSA_ComputePublicKey() for blob usage.

    (#) ECC Scalar Multiplication functions are :
       (++) HAL_CCB_ECC_WrapPrivateKey()for blob creation.
       (++) HAL_CCB_ECC_GenerateWrapPrivateKey()for blob creation.
       (++) HAL_CCB_ECC_ComputeScalarMul() for blob usage.

    (#) RSA Modular Exponentiation functions are :
       (++) HAL_CCB_RSA_WrapPrivateKey()for blob creation.
       (++) HAL_CCB_RSA_ComputeModularExp() for blob usage.

@endverbatim
  * @{
  */
/**
  * @brief  ECDSA Wrap Symmetric Key.
  * @param  hccb CCB handle.
  * @param  pClearAESKey pointer to the clear AES Key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECDSA_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey,
                                                 CCB_WrappingKeyTypeDef *pWrappingKey)
{
  return (CCB_WrapSymmetricKey(hccb, pClearAESKey, CCB_ECDSA_SIGN_CPU_BLOB_CREATION, pWrappingKey));
}

/**
  * @brief  ECC Wrap Symmetric Key.
  * @param  hccb CCB handle.
  * @param  pClearAESKey pointer to the clear AES Key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECC_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey,
                                               CCB_WrappingKeyTypeDef *pWrappingKey)
{
  return (CCB_WrapSymmetricKey(hccb, pClearAESKey, CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION, pWrappingKey));
}

/**
  * @brief  RSA Wrap Symmetric Key.
  * @param  hccb CCB handle.
  * @param  pClearAESKey pointer to the clear AES Key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_RSA_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey,
                                               CCB_WrappingKeyTypeDef *pWrappingKey)
{
  return (CCB_WrapSymmetricKey(hccb, pClearAESKey, CCB_MODULAR_EXP_CPU_BLOB_CREATION, pWrappingKey));
}

/**
  * @brief  Blob Creation: ECDSA Wrap the private Key (input from user).
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pClearPrivateKey pointer to the clear private key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECDSA_WrapPrivateKey(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                               const uint8_t *pClearPrivateKey, CCB_WrappingKeyTypeDef *pWrappingKey,
                                               const CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob)
{
  uint32_t count;
  __IO uint16_t f_count;
  uint16_t random0 = 0;
  uint16_t random1 = 0;
  uint16_t random2 = 0;
  uint16_t random3 = 0;
  uint32_t key_size;
  uint32_t tickstart;

  uint8_t hash[80U] = {0};
  uint8_t r_sign[80U] = {0};
  uint8_t s_sign[80U] = {0};
  uint8_t point_x[80U] = {0};
  uint8_t point_y[80U] = {0};
  uint8_t integer[80U] = {0};
  uint32_t iv_temp[4] = {0};
  uint32_t tag_temp[4] = {0};
  uint32_t wrapped_key_temp[80U] = {0};

  CCB_ECDSASignTypeDef signature = {r_sign, s_sign};
  CCB_ECCMulPointTypeDef publicKeyOut = {(uint8_t *)point_x, (uint8_t *)point_y};

  if (CCB_RNG_Init() != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  for (count = 0U; count < (pCurveParam->primeOrderSizeByte); count++)
  {
    if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    tickstart = HAL_GetTick();

    while (hash[count] == 0U)
    {
      hash[count] = (uint8_t)((RNG->DR) & 0x000000FFU);
      if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
      {
        /* Set state and return error */
        return HAL_ERROR;
      }
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random0 == 0U)
  {
    random0 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random1 == 0U)
  {
    random1 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random2 == 0U)
  {
    random2 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random3 == 0U)
  {
    random3 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  for (count = 0U; count < (pCurveParam->primeOrderSizeByte); count++)
  {
    tickstart = HAL_GetTick();

    while (integer[count] == 0U)
    {
      integer[count] = (uint8_t)((RNG->DR) & 0x000000FFU);
      if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
      {
        /* Set state and return error */
        return HAL_ERROR;
      }
    }

    if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  if (hccb->State == HAL_CCB_STATE_READY)
  {

    if (Unprotected_PKA_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    if (PKA_ECDSASign(pCurveParam, pClearPrivateKey, (uint8_t *)integer, (uint8_t *)hash,
                      &signature) != HAL_OK)
    {
      if (PKA_RAM_Erase() != HAL_OK)
      {
        hccb->ErrorCode |= HAL_CCB_ERROR_PKARAM_ERASE;
      }
      return HAL_ERROR;
    }

    f_count = 0;
    while (f_count < random0)
    {
      f_count++;
    }

    /* Signature blob creation */
    if (CCB_ECDSA_SignBlobCreation(hccb, pCurveParam, pClearPrivateKey, pWrappingKey, iv_temp, tag_temp,
                                   wrapped_key_temp, CCB_ECDSA_SIGN_CPU_BLOB_CREATION) != HAL_OK)
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    /* Reset each element in the PKA RAM */
    for (uint32_t index = 0U; index < CCB_PKA_RAM_SIZE; index++)
    {
      /* Clear the content */
      PKA->RAM[index] = 0UL;
    }

    /* Create ECDSA public key */
    if (CCB_ECC_ComputeScalarMul(hccb, pCurveParam, pWrappingKey, iv_temp, tag_temp,
                                 wrapped_key_temp, NULL, &publicKeyOut, NULL,
                                 CCB_COMPUTE_PUBLIC_KEY) != HAL_OK)
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    if (Unprotected_PKA_Init() != HAL_OK)
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    /* PKA ECDSA valid R & S signature */
    if (PKA_ECDSAVerif(pCurveParam, &publicKeyOut, hash, &signature) != HAL_OK)
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    f_count = 0;
    while (f_count < random1)
    {
      f_count++;
    }

    /* Check if it is valid signature and improve robustness against intrusion (intentional) */
    if ((PKA_ECDSAVerif_Result() != CCB_PKA_ECDSA_VERIF_OK) || (f_count != random1) || (f_count == 0U))
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    f_count = 0;
    while (f_count < random2)
    {
      f_count++;
    }

    /* Check if it is valid signature and improve robustness against intrusion (intentional) */
    if ((PKA_ECDSAVerif_Result() != CCB_PKA_ECDSA_VERIF_OK) || (f_count != random2) || (f_count == 0U))
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    f_count = 0;
    while (f_count < random3)
    {
      f_count++;
    }

    /* Check if it is valid signature and improve robustness against intrusion (intentional) */
    if ((PKA_ECDSAVerif_Result() != CCB_PKA_ECDSA_VERIF_OK) || (f_count != random3) || (f_count == 0U))
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }
  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Export created Blob */
  key_size = CCB_get_cipherkey_size(pCurveParam);
  for (count = 0U; count < key_size; count++)
  {
    if (count < CCB_BLOCK_SIZE)
    {
      pWrappedPrivateKeyBlob->pIV[count] = iv_temp[count];
      pWrappedPrivateKeyBlob->pTag[count] = tag_temp[count];
    }
    pWrappedPrivateKeyBlob->pWrappedKey[count] = wrapped_key_temp[count];
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Creation: ECDSA generate (by RNG) and wrap the private Key (no user input).
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECDSA_GenerateWrapPrivateKey(CCB_HandleTypeDef *hccb,
                                                       CCB_ECDSACurveParamTypeDef *pCurveParam,
                                                       CCB_WrappingKeyTypeDef *pWrappingKey,
                                                       CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob)
{
  uint32_t count;
  uint32_t key_size;
  uint32_t iv_temp[4] = {0};
  uint32_t tag_temp[4] = {0};
  uint32_t wrapped_key_temp[80U] = {0};

  if (hccb->State == HAL_CCB_STATE_READY)
  {

    /* Signature blob creation */
    if (CCB_ECDSA_SignBlobCreation(hccb, pCurveParam, NULL, pWrappingKey, iv_temp, tag_temp, wrapped_key_temp,
                                   CCB_ECDSA_SIGN_RNG_BLOB_CREATION) != HAL_OK)
    {
      /* Set state, error code and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Export created Blob */
  key_size = CCB_get_cipherkey_size(pCurveParam);
  for (count = 0U; count < key_size; count++)
  {
    if (count < CCB_BLOCK_SIZE)
    {
      pWrappedPrivateKeyBlob->pIV[count] = iv_temp[count];
      pWrappedPrivateKeyBlob->pTag[count] = tag_temp[count];
    }
    pWrappedPrivateKeyBlob->pWrappedKey[count] = wrapped_key_temp[count];
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Usage: ECDSA Signature.
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @param  pHash pointer to the Hash.
  * @param  pSignature pointer to the signature.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECDSA_Sign(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                     CCB_WrappingKeyTypeDef *pWrappingKey,
                                     CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob, const uint8_t *pHash,
                                     CCB_ECDSASignTypeDef *pSignature)

{
  uint32_t count;
  uint32_t count_block = 0;
  uint32_t offset;
  uint32_t operand_size;
  uint32_t cipherkey_size;

  if (hccb->State == HAL_CCB_STATE_READY)
  {
    /* Set Operation in CCB */
    MODIFY_REG(CCB->CR, CCB_CR_CCOP, CCB_ECDSA_SIGN_BLOB_USE);

    /* Wait until OPSTEP is set to 0x01 */
    if (CCB_WaitOperStep(hccb, 0x01, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Initialize RNG */
    if (CCB_RNG_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /* Initialize PKA */
    if (Protect_PKA_Init(hccb, CCB_ECDSA_SIGN_BLOB_USE) != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /*  Initialize SAES */
    if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* Disable the SAES peripheral */
      SAES->CR &=  ~AES_CR_EN;

      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /* Update the state */
    hccb->State = HAL_CCB_STATE_BUSY;

    /* Wrapping Key configuration */
    if (WrappingKeyConfiguration(hccb, CCB_ECDSA_SIGN_BLOB_USE, pWrappingKey) != HAL_OK)
    {
      /* Set state, error code and return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x012 */
    if (CCB_WaitOperStep(hccb, 0x012, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Update the state */
    hccb->State = HAL_CCB_STATE_BUSY;

    /* set operand size (in word 32bits)*/

    operand_size = 2UL * ((uint32_t)(((pCurveParam->modulusSizeByte) + 7UL) / 8UL) + 1UL);

    if ((operand_size % 4UL) != 0UL)
    {
      cipherkey_size = operand_size - 2UL;
    }
    else
    {
      cipherkey_size = operand_size;
    }

    /* Set Hash message */
    CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_HASH_E ], pHash, pCurveParam->modulusSizeByte);

    /* Initial Phase Processing */
    if (CCB_BlobUse_InitialPhase(hccb, pWrappedPrivateKeyBlob->pIV, pWrappedPrivateKeyBlob->pTag) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x13 */
    if (CCB_WaitOperStep(hccb, 0x13, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Set ECDSA parameters */
    if (CCB_ECDSASign_SetPram(hccb, pCurveParam) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Set SAES GCMPH Payload phase and trig OPSTEP that trig OPSTEP transition 0x13 --> 0x14 */
    MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_1);

    /* Wait until OPSTEP is set to 0x14 */
    if (CCB_WaitOperStep(hccb, 0x14, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Write encrypted Key*/
    for (offset = 0UL; offset < cipherkey_size; offset++)
    {
      WRITE_REG(SAES->DINR, pWrappedPrivateKeyBlob->pWrappedKey[cipherkey_size - (offset + 1UL)]);

      if ((offset % 4UL) == 0x3UL)
      {
        /* Wait until CCF flag is SET in SAES */
        if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
          /* return error */
          return HAL_ERROR;
        }

        /* Write key in PKA RAM */
        for (count = 0UL; count < 4UL; count++)
        {
          PKA->RAM[PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + count_block + count] = CCB_MAGIC_VALUE;
        }
        count_block += 4UL;
      }
    }

    if ((operand_size % 4UL) != 0UL)
    {
      RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + cipherkey_size);
    }
    /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x14 --> 0x16 */
    if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x16 */
    if (CCB_WaitOperStep(hccb, 0x16, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Write random k */
    for (offset = 0UL; offset < (operand_size - 2UL); offset++)
    {
      /* Wait for RNG Data Ready flag */
      if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }
      PKA->RAM[PKA_ECDSA_SIGN_IN_K + offset] = CCB_FAKE_VALUE;
    }

    /*  Padding at zero */
    RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_K + offset);

    /* Wait for PKA RNGOK flag : GCMPH = 0x3 (final phase) as events that trig OPSTEP transition 0x16 --> 0x17 */
    if (Protect_PKA_WaitFLAG(hccb, PKA_SR_RNGOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x17 */
    if (CCB_WaitOperStep(hccb, 0x17, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Final phase processing */
    if (CCB_BlobUse_FinalPhase(hccb, CCB_ECDSA_SIGN_BLOB_USE, pCurveParam->modulusSizeByte) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x18 */
    if (CCB_WaitOperStep(hccb, 0x18, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* SET PKA START operation bit and trig OPSTEP transition 0x18 --> 0x19 */
    SET_BIT(PKA->CR, PKA_CR_START);

    /* Wait until OPSTEP is set to 0x19 */
    if (CCB_WaitOperStep(hccb, 0x19, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until end of operation flag is SET in PKA and trig OPSTEP transition 0x19 --> 0x1A */
    if (Protect_PKA_WaitFLAG(hccb, PKA_SR_PROCENDF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x1A */
    if (CCB_WaitOperStep(hccb, 0x1A, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Check PKA Operation error result */
    if ((PKA->RAM[PKA_ECDSA_SIGN_OUT_ERROR]) !=  CCB_PKA_ERROR_OPERATION_NONE)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
    /* Read r part signature */
    CCB_Memcpy_u32_to_u8(pSignature->pRSign, &PKA->RAM[PKA_ECDSA_SIGN_OUT_SIGNATURE_R], pCurveParam->modulusSizeByte);
    /* Read s part signature */
    CCB_Memcpy_u32_to_u8(pSignature->pSSign, &PKA->RAM[PKA_ECDSA_SIGN_OUT_SIGNATURE_S], pCurveParam->modulusSizeByte);


    /* set CCB IPRST  */
    SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

    /* CCB is busy while CCB IPRST is in progress */
    if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    /* clear CCB IPRST */
    CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

    /* Update the CCB state */
    hccb->State = HAL_CCB_STATE_READY;
  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Usage: ECDSA Compute Public Key.
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @param  pPublicKey pointer to the output public key.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECDSA_ComputePublicKey(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                                 CCB_WrappingKeyTypeDef *pWrappingKey,
                                                 CCB_ECDSAKeyBlobTypeDef *pWrappedPrivateKeyBlob,
                                                 CCB_ECCMulPointTypeDef *pPublicKey)
{
  if (hccb->State == HAL_CCB_STATE_READY)
  {
    if (CCB_ECC_ComputeScalarMul(hccb, pCurveParam, pWrappingKey, pWrappedPrivateKeyBlob->pIV,
                                 pWrappedPrivateKeyBlob->pTag, pWrappedPrivateKeyBlob->pWrappedKey, NULL, pPublicKey,
                                 NULL, CCB_COMPUTE_PUBLIC_KEY) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Creation: ECC Wrap the private Key (input from user).
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pClearPrivateKey pointer to the clear private key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECC_WrapPrivateKey(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                             const uint8_t *pClearPrivateKey, CCB_WrappingKeyTypeDef *pWrappingKey,
                                             CCB_ECCMulKeyBlobTypeDef *pWrappedPrivateKeyBlob)
{
  uint8_t random = 0;
  uint32_t public_key[2][20] = {{0UL}, {0UL}};
  __IO uint8_t f_count;
  uint32_t count;
  uint32_t key_size;
  uint32_t iv_temp[4] = {0};
  uint32_t tag_temp[4] = {0};
  uint32_t wrapped_key_temp[80] = {0};
  uint32_t tickstart;

  if (hccb->State == HAL_CCB_STATE_READY)
  {

    if (Unprotected_PKA_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    if (CCB_RNG_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    if (PKA_ECC_ComputeScalarMul(pCurveParam, pClearPrivateKey, public_key) != HAL_OK)
    {
      if (PKA_RAM_Erase() != HAL_OK)
      {
        hccb->ErrorCode |= HAL_CCB_ERROR_PKARAM_ERASE;
      }
      return HAL_ERROR;
    }

    if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    tickstart = HAL_GetTick();

    while (random == 0U)
    {
      random = (uint8_t)(RNG->DR & 0xFFU);
      if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
      {
        /* Set state and return error */
        return HAL_ERROR;
      }
    }

    f_count = 0;
    while (f_count < random)
    {
      f_count++;
    }

    if (CCB_ECC_ScalarMulBlobCreation(hccb, pCurveParam, pClearPrivateKey, pWrappingKey,
                                      iv_temp, tag_temp, wrapped_key_temp,
                                      CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION) != HAL_OK)
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    /* Compute CCB public key */
    if (CCB_ECC_ComputeScalarMul(hccb, pCurveParam, pWrappingKey, iv_temp, tag_temp, wrapped_key_temp, NULL,
                                 NULL, &public_key[0][0], CCB_VERIF_OPERATION_ENABLED) != HAL_OK)

    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Export created Blob */
  key_size = CCB_get_cipherkey_size(pCurveParam);
  for (count = 0U; count < key_size; count++)
  {
    if (count < CCB_BLOCK_SIZE)
    {
      pWrappedPrivateKeyBlob->pIV[count] = iv_temp[count];
      pWrappedPrivateKeyBlob->pTag[count] = tag_temp[count];
    }
    pWrappedPrivateKeyBlob->pWrappedKey[count] = wrapped_key_temp[count];
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Creation: ECC generate (by RNG) and wrap the private Key (no user input).
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECC_GenerateWrapPrivateKey(CCB_HandleTypeDef *hccb,
                                                     CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                     CCB_WrappingKeyTypeDef *pWrappingKey,
                                                     CCB_ECCMulKeyBlobTypeDef *pWrappedPrivateKeyBlob)
{

  if (hccb->State == HAL_CCB_STATE_READY)
  {
    /* CCB ECC generate private wrap key */
    if (CCB_ECC_ScalarMulBlobCreation(hccb, pCurveParam, NULL, pWrappingKey,
                                      pWrappedPrivateKeyBlob->pIV, pWrappedPrivateKeyBlob->pTag,
                                      pWrappedPrivateKeyBlob->pWrappedKey,
                                      CCB_ECC_SCALAR_MUL_RNG_BLOB_CREATION) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Usage: ECC Compute Scalar Multiplication.
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pInputPoint pointer to the input point structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @param  pOutputPoint pointer to the output point.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_ECC_ComputeScalarMul(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                               CCB_WrappingKeyTypeDef *pWrappingKey,
                                               CCB_ECCMulKeyBlobTypeDef *pWrappedPrivateKeyBlob,
                                               CCB_ECCMulPointTypeDef *pInputPoint,
                                               CCB_ECCMulPointTypeDef *pOutputPoint)
{
  if (hccb->State == HAL_CCB_STATE_READY)
  {
    if (CCB_ECC_ComputeScalarMul(hccb, pCurveParam, pWrappingKey, pWrappedPrivateKeyBlob->pIV,
                                 pWrappedPrivateKeyBlob->pTag, pWrappedPrivateKeyBlob->pWrappedKey,
                                 pInputPoint, pOutputPoint, NULL, CCB_VERIF_OPERATION_DISABLED) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Creation: RSA Wrap the private Key (input from user).
  * @param  hccb CCB handle.
  * @param  pParam pointer to the modular exponatiation parameters.
  * @param  pRSAClearPrivateKey pointer to the clear Private Key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_RSA_WrapPrivateKey(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                             const CCB_RSAClearKeyTypeDef *pRSAClearPrivateKey,
                                             CCB_WrappingKeyTypeDef *pWrappingKey,
                                             CCB_RSAKeyBlobTypeDef *pWrappedPrivateKeyBlob)
{
  uint8_t  exp_base[520U] = {0};
  uint32_t count;
  __IO uint16_t f_count;
  uint16_t random0 = 0;
  uint32_t modular_exp_ref[520U] = {0};
  uint32_t operand_size;
  uint32_t cipherkey_size;
  uint32_t iv_temp[4] = {0};
  uint32_t tag_temp[4] = {0};
  uint32_t wrapped_exp[520U] = {0};
  uint32_t wrapped_phi[520U] = {0};
  uint32_t tickstart;

  if (hccb->State == HAL_CCB_STATE_READY)
  {
    if (CCB_RNG_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    for (uint32_t offset = 0U; offset < pParam->modulusSizeByte; offset++)
    {
      if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        return HAL_ERROR;
      }

      tickstart = HAL_GetTick();

      while (exp_base[offset] == 0U)
      {
        exp_base[offset] = (uint8_t)(RNG->DR & 0xFFU);
        if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
        {
          /* Set state and return error */
          return HAL_ERROR;
        }
      }
    }

    if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    tickstart = HAL_GetTick();

    while (random0 == 0U)
    {
      random0 = (uint16_t)(RNG->DR & 0x3FFU);
      if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
      {
        /* Set state and return error */
        return HAL_ERROR;
      }
    }

    if (Unprotected_PKA_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    if (PKA_RSA_ComputeModularExp(pParam, pRSAClearPrivateKey, (uint8_t *)exp_base, modular_exp_ref) != HAL_OK)
    {
      if (PKA_RAM_Erase() != HAL_OK)
      {
        hccb->ErrorCode |= HAL_CCB_ERROR_PKARAM_ERASE;
      }
      return  HAL_ERROR;
    }

    if (CCB_RNG_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    f_count = 0;
    while (f_count < random0)
    {
      f_count++;
    }

    if (CCB_RSA_ExpBlobCreation(hccb, pParam, pRSAClearPrivateKey, pWrappingKey, iv_temp, tag_temp, wrapped_exp,
                                wrapped_phi) != HAL_OK)
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }

    if (CCB_RSA_ComputeModularExp(hccb, pParam, pWrappingKey, iv_temp, tag_temp, wrapped_exp, wrapped_phi,
                                  (uint8_t *)exp_base, NULL, modular_exp_ref,
                                  CCB_VERIF_OPERATION_ENABLED) != HAL_OK)
    {
      /* Set state, and intrusion error */
      hccb->State = HAL_CCB_STATE_ERROR;
      HAL_CCB_IntrusionCallback(hccb);
    }
  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* set operand size */
  operand_size   = 2UL * ((uint32_t)(((pParam->modulusSizeByte) + 7UL) / 8UL) + 1UL);
  if ((operand_size % 4UL) != 0UL)
  {
    cipherkey_size = operand_size - 2UL;
  }
  else
  {
    cipherkey_size = operand_size;
  }

  /* Export created Blob */
  for (count = 0U; count < cipherkey_size; count++)
  {
    if (count < CCB_BLOCK_SIZE)
    {
      pWrappedPrivateKeyBlob->pIV[count] = iv_temp[count];
      pWrappedPrivateKeyBlob->pTag[count] = tag_temp[count];
    }
    pWrappedPrivateKeyBlob->pWrappedExp[count] = wrapped_exp[count];
    pWrappedPrivateKeyBlob->pWrappedPhi[count] = wrapped_phi[count];
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Usage: RSA Compute Modular exponentiation.
  * @param  hccb CCB handle.
  * @param  pParam pointer to the modular exponatiation parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pOperand pointer to the operand.
  * @param  pWrappedPrivateKeyBlob pointer to the related wrapped Private Key Blob.
  * @param  pModularExp pointer to the output operation.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CCB_RSA_ComputeModularExp(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                                CCB_WrappingKeyTypeDef *pWrappingKey,
                                                CCB_RSAKeyBlobTypeDef *pWrappedPrivateKeyBlob,
                                                const uint8_t *pOperand, uint8_t *pModularExp)
{
  if (hccb->State == HAL_CCB_STATE_READY)
  {
    if (CCB_RSA_ComputeModularExp(hccb, pParam, pWrappingKey, pWrappedPrivateKeyBlob->pIV,
                                  pWrappedPrivateKeyBlob->pTag, pWrappedPrivateKeyBlob->pWrappedExp,
                                  pWrappedPrivateKeyBlob->pWrappedPhi, pOperand,
                                  pModularExp, NULL, CCB_VERIF_OPERATION_DISABLED) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Processing Error callback. Infinite loop against intrusion.
  * @param  hccb : CCB handle
  * @retval None
  */
__weak void HAL_CCB_IntrusionCallback(CCB_HandleTypeDef *hccb)
{
  for (;;)
  {
    NVIC_SystemReset();
  }

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CCB_IntrusionCallback could be implemented in the user file
   */
}
/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Wait CCB Operation step
  * @param  hccb CCB handle
  * @param  step ctep to wait
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_WaitOperStep(CCB_HandleTypeDef *hccb, uint32_t step, uint32_t Timeout)
{
  uint32_t tickstart;

  tickstart = HAL_GetTick();

  /* Wait until OPSTEP is set */
  while ((READ_REG(hccb->Instance->SR) & step) != step)
  {
    /* Check for the Timeout */
    if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Wait CCB Flag
  * @param  hccb CCB handle
  * @param  flag Specifies the flag to check
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_WaitFLAG(CCB_HandleTypeDef *hccb, uint32_t flag, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (HAL_IS_BIT_SET(hccb->Instance->SR, flag))
  {
    if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Wait PKA Flag
  * @param  hccb CCB handle
  * @param  flag Specifies the flag to check
  * @param  Timeout Timeout duration
  * @retval HAL status.
  */
static HAL_StatusTypeDef Protect_PKA_WaitFLAG(CCB_HandleTypeDef *hccb, uint32_t flag, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(PKA->SR, flag))
  {
    if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
    {
      CLEAR_BIT(PKA->CR, PKA_CR_EN);

      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }

  /* Clear flag */
  SET_BIT(PKA->CLRFR, flag);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Wait PKA Flag
  * @param  flag Specifies the flag to check
  * @param  Timeout Timeout duration
  * @retval HAL status.
  */
static HAL_StatusTypeDef Unprotect_PKA_WaitFLAG(uint32_t flag, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(PKA->SR, flag))
  {
    if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
    {
      CLEAR_BIT(PKA->CR, PKA_CR_EN);

      /* return error */
      return HAL_ERROR;
    }
  }

  /* Clear flag */
  SET_BIT(PKA->CLRFR, flag);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Wait RNG Flag
  * @param  flag Specifies the flag to check
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_RNG_Wait_SET_FLAG(uint32_t flag, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(RNG->SR, flag))
  {
    if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
    {
      RNG->CR &= ~RNG_CR_RNGEN;

      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Wait SAES Flag
  * @param  hccb CCB handle
  * @param  flag Specifies the flag to check
  * @param  Status Flag status (SET or RESET)
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef Protect_SAES_WaitFLAG(CCB_HandleTypeDef *hccb, uint32_t flag, FlagStatus Status,
                                               uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (HAL_CCB_GET_SAES_FLAG(flag) != Status)
  {
    if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
    {
      SAES->CR &= ~AES_CR_EN;

      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }

  /* Clear flag */
  SET_BIT(SAES->ICR, flag);


  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Set ECDSA signture parameters in related PKA RAM address
  * @param  hccb CCB handle
  * @param  in pointer to the ECDSA signture parametersstructure
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_ECDSASign_SetPram(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *in)
{
  /* Get the prime order n length */
  PKA->RAM[PKA_ECDSA_SIGN_IN_ORDER_NB_BITS]
    = GetOptBitSize_u8(in->primeOrderSizeByte, *(in->pPrimeOrder));
  PKA->RAM[PKA_ECDSA_SIGN_IN_ORDER_NB_BITS + 1U] = 0x0U;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Get the modulus p length */
  PKA->RAM[PKA_ECDSA_SIGN_IN_MOD_NB_BITS] = GetOptBitSize_u8(in->modulusSizeByte, *(in->pModulus));
  PKA->RAM[PKA_ECDSA_SIGN_IN_MOD_NB_BITS + 1U] = 0x0U;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Get the coefficient a sign */
  PKA->RAM[PKA_ECDSA_SIGN_IN_A_COEFF_SIGN] = in->coefSignA;
  PKA->RAM[PKA_ECDSA_SIGN_IN_A_COEFF_SIGN + 1U] = 0x0;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Move the input parameters coefficient |a| to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECDSA_SIGN_IN_A_COEFF, in->pAbsCoefA) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters coefficient B to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECDSA_SIGN_IN_B_COEFF, in->pCoefB) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters modulus value p to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECDSA_SIGN_IN_MOD_GF, in->pModulus) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters prime order n to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECDSA_SIGN_IN_ORDER_N, in->pPrimeOrder) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters base point G coordinate x to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECDSA_SIGN_IN_INITIAL_POINT_X, in->pPointX) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters base point G coordinate y to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECDSA_SIGN_IN_INITIAL_POINT_Y, in->pPointY) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Set ECC scalar multiplication parameters in related PKA RAM address
  * @param  hccb CCB handle
  * @param  in pointer to the ECC parametersstructure
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_ECCMul_SetPram(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *in)
{
  /* Get the prime order n length */
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_EXP_NB_BITS]
    = GetOptBitSize_u8(in->primeOrderSizeByte, *(in->pPrimeOrder));
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_EXP_NB_BITS + 1U] = 0x0;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Get the modulus p length */
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_OP_NB_BITS] = GetOptBitSize_u8(in->modulusSizeByte, *(in->pModulus));
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_OP_NB_BITS + 1U] = 0x0;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Get the coefficient a sign */
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_A_COEFF_SIGN] = in->coefSignA;
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_A_COEFF_SIGN + 1U] = 0x0;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Move the input parameters coefficient |a| to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECC_SCALAR_MUL_IN_A_COEFF, in->pAbsCoefA) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters coefficient B to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECC_SCALAR_MUL_IN_B_COEFF, in->pCoefB) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters modulus value p to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECC_SCALAR_MUL_IN_MOD_GF, in->pModulus) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Move the input parameters prime order n to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_ECC_SCALAR_MUL_IN_N_PRIME_ORDER, in->pPrimeOrder) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Set RSA sModular Exponentiation parameters in related PKA RAM address
  * @param  hccb CCB handle
  * @param  in pointer to the ECC parametersstructure
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_RSAModExp_SetPram(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *in)
{
  /* Get the exp length */
  PKA->RAM[PKA_MODULAR_EXP_IN_EXP_NB_BITS] = GetOptBitSize_u8(in->expSizeByte, *(in->pMod));
  PKA->RAM[PKA_MODULAR_EXP_IN_EXP_NB_BITS + 1U] = 0x0U;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Get the modulus n length */
  PKA->RAM[PKA_MODULAR_EXP_IN_OP_NB_BITS] = GetOptBitSize_u8(in->modulusSizeByte, *(in->pMod));
  PKA->RAM[PKA_MODULAR_EXP_IN_OP_NB_BITS + 1U] = 0x0U;
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Move the input parameters modulus to PKA RAM */
  if (CCB_SetPram(hccb, in->modulusSizeByte, PKA_MODULAR_EXP_PROTECT_IN_MODULUS, in->pMod) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Set CCB parameters
  * @param  hccb CCB handle
  * @param  modulusSizeByte Modulus size in byte
  * @param  dst_address destination address
  * @param  src Pointer to source
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_SetPram(CCB_HandleTypeDef *hccb, uint32_t modulusSizeByte, uint32_t dst_address,
                                     const uint8_t *src)
{
  uint32_t offset;
  uint32_t operand_size;
  operand_size = 2UL * ((uint32_t)(((modulusSizeByte) + 7UL) / 8UL) + 1UL);

  if ((modulusSizeByte % 8UL) != 0UL)
  {
    for (offset = 0; offset < (operand_size - 4UL); offset += 2UL)
    {
      CCB_Memcpy_u8_to_u64(&PKA->RAM[dst_address + offset],
                           &src[(modulusSizeByte) - ((offset * 4UL) + 1UL)]);
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        hccb->State = HAL_CCB_STATE_ERROR;
        return HAL_ERROR;
      }
    }

    CCB_Memcpy_Not_Align(&PKA->RAM[dst_address + offset],
                         &src[(modulusSizeByte) - ((offset * 4UL) + 1UL)], modulusSizeByte % 8UL);

    if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
    RAM_PARAM_END(PKA->RAM, dst_address + ((modulusSizeByte + 7UL) / 4UL));
    if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }

  else
  {
    for (offset = 0; offset < (operand_size - 2UL); offset += 2UL)
    {
      CCB_Memcpy_u8_to_u64(&PKA->RAM[dst_address + offset],
                           &src[(modulusSizeByte) - ((offset * 4UL) + 1UL)]);
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        hccb->State = HAL_CCB_STATE_ERROR;
        return HAL_ERROR;
      }
    }

    RAM_PARAM_END(PKA->RAM, dst_address
                  + ((modulusSizeByte + 3UL) / 4UL));
    if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initialize the PKA
  * @param  hccb CCB handle
  * @param  Operation PKA Operation
  * @retval HAL status
  */
static HAL_StatusTypeDef Protect_PKA_Init(CCB_HandleTypeDef *hccb, uint32_t Operation)
{
  /* Reset the control register and enable the PKA */
  PKA->CR = PKA_CR_EN;

  /* Wait the INITOK flag Setting */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_INITOK, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reset any pending flag */
  SET_BIT(PKA->CLRFR, PKA_CLRFR_PROCENDFC | PKA_CLRFR_RAMERRFC | PKA_CLRFR_ADDRERRFC | PKA_CLRFR_OPERRFC);

  /* Set the mode and deactivate the interrupts */
  if ((Operation == CCB_ECDSA_SIGN_CPU_BLOB_CREATION)
      || (Operation == CCB_ECDSA_SIGN_RNG_BLOB_CREATION)
      || (Operation == CCB_ECDSA_SIGN_BLOB_USE))
  {
    MODIFY_REG(PKA->CR, PKA_CR_MODE | PKA_CR_PROCENDIE | PKA_CR_RAMERRIE | PKA_CR_ADDRERRIE
               | PKA_CR_OPERRIE, CCB_PKA_ECDSA_SIGNATURE_MODE << PKA_CR_MODE_Pos);
  }

  else if ((Operation == CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION)
           || (Operation == CCB_ECC_SCALAR_MUL_RNG_BLOB_CREATION)
           || (Operation == CCB_ECC_SCALAR_MUL_BLOB_USE))
  {
    MODIFY_REG(PKA->CR, PKA_CR_MODE | PKA_CR_PROCENDIE | PKA_CR_RAMERRIE | PKA_CR_ADDRERRIE
               | PKA_CR_OPERRIE, CCB_PKA_ECC_MUL_MODE << PKA_CR_MODE_Pos);
  }

  else if ((Operation == CCB_MODULAR_EXP_CPU_BLOB_CREATION)
           || (Operation == CCB_MODULAR_EXP_BLOB_USE))
  {
    MODIFY_REG(PKA->CR, PKA_CR_MODE | PKA_CR_PROCENDIE | PKA_CR_RAMERRIE | PKA_CR_ADDRERRIE
               | PKA_CR_OPERRIE, CCB_PKA_MODE_MODULAR_EXP_PROTECT << PKA_CR_MODE_Pos);
  }
  else
  {
    /* do nothing */
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Unprotected PKA Initialization
  * @retval HAL status.
  */
static HAL_StatusTypeDef Unprotected_PKA_Init(void)
{
  uint32_t tickstart = HAL_GetTick();

  /* Reset the control register and enable the PKA (wait the end of PKA RAM erase) */
  while ((PKA->CR & PKA_CR_EN) != PKA_CR_EN)
  {
    PKA->CR = PKA_CR_EN;

    /* Check the Timeout */
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set timeout status */
      break;
    }
  }
  /* Wait the INITOK flag Setting */
  if (Unprotect_PKA_WaitFLAG(PKA_SR_INITOK, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reset any pending flag */
  SET_BIT(PKA->CLRFR, PKA_CLRFR_PROCENDFC | PKA_CLRFR_RAMERRFC | PKA_CLRFR_ADDRERRFC | PKA_CLRFR_OPERRFC);

  return HAL_OK;
}

/**
  * @brief  Initialize the RNG
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_RNG_Init(void)
{
  uint32_t tickstart;

  /* Disable RNG */
  RNG->CR &= ~RNG_CR_RNGEN;

  /* Clock Error Detection Configuration when CONDRT bit is set to 1 */
  MODIFY_REG(RNG->CR, RNG_CR_CONDRST,  RNG_CR_CONDRST);
#if defined(RNG_CR_NIST_VALUE)
  /* Recommended value for NIST compliance, refer to application note AN4230 */
  WRITE_REG(RNG->CR, RNG_CR_NIST_VALUE | RNG_CR_CONDRST);
#endif /* defined(RNG_CR_NIST_VALUE) */
#if defined(RNG_HTCR_NIST_VALUE)
  /* Recommended value for NIST compliance, refer to application note AN4230 */
  WRITE_REG(RNG->HTCR, RNG_HTCR_NIST_VALUE);
#endif /* defined(RNG_HTCR_NIST_VALUE) */
#if defined(RNG_NSCR_NIST_VALUE)
  WRITE_REG(RNG->NSCR, RNG_NSCR_NIST_VALUE);
#endif /* defined(RNG_NSCR_NIST_VALUE) */

  /* Writing bit CONDRST=0 */
  CLEAR_BIT(RNG->CR, RNG_CR_CONDRST);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait for conditioning reset process to be completed */
  while (HAL_IS_BIT_SET(RNG->CR, RNG_CR_CONDRST))
  {
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (HAL_IS_BIT_SET(RNG->CR, RNG_CR_CONDRST))
      {
        /* Set state and return error */
        return HAL_ERROR;
      }
    }
  }

  /* Enable the RNG Peripheral */
  RNG->CR |=  RNG_CR_RNGEN;

  /* verify that no seed error */
  if ((RNG->SR & (RNG_SR_SEIS)) != (uint32_t)RESET)
  {
    /* Set state and return error */
    return HAL_ERROR;
  }

  /* Check if data register contains valid random data */
  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Wait CCB wrapping key configuration
  * @param  hccb CCB handle
  * @param  Operation Operation
  * @param  pWrappingKey pointer to the wrapping key structure
  * @retval HAL status
  */
static HAL_StatusTypeDef WrappingKeyConfiguration(CCB_HandleTypeDef *hccb, uint32_t Operation,
                                                  CCB_WrappingKeyTypeDef *pWrappingKey)
{
  uint32_t tmp;

  switch (pWrappingKey->WrappingKeyType)
  {
    case HAL_CCB_USER_KEY_WRAPPED:

      if (Protect_SAES_UnwrapKey(hccb, pWrappingKey, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        return HAL_ERROR;
      }

      if ((Operation == CCB_ECDSA_SIGN_CPU_BLOB_CREATION) || (Operation == CCB_ECDSA_SIGN_RNG_BLOB_CREATION)
          || (Operation == CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION)
          || (Operation == CCB_ECC_SCALAR_MUL_RNG_BLOB_CREATION)
          || (Operation == CCB_MODULAR_EXP_CPU_BLOB_CREATION))
      {
        /* SAES: GCMPH = 0x0 (initial phase) as event that trig OPSTEP 0x1 --> 0x2 */
        WRITE_REG(SAES->CR, AES_CR_KEYSIZE | AES_CR_CHMOD_0 | AES_CR_CHMOD_1);
      }

      else if ((Operation == CCB_ECDSA_SIGN_BLOB_USE) || (Operation == CCB_ECC_SCALAR_MUL_BLOB_USE)
               || (Operation == CCB_MODULAR_EXP_BLOB_USE))
      {
        /* SAES: GCMPH = 0x0 (initial phase) as event that trig OPSTEP 0x1 --> 0x12 */
        WRITE_REG(SAES->CR, AES_CR_KEYSIZE | AES_CR_CHMOD_0
                  | AES_CR_CHMOD_1 | AES_CR_MODE_1);
      }

      else
      {
        /* do nothing */
      }
      break;

    case HAL_CCB_USER_KEY_HW:

      if ((Operation == CCB_ECDSA_SIGN_CPU_BLOB_CREATION) || (Operation == CCB_ECDSA_SIGN_RNG_BLOB_CREATION)
          || (Operation == CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION)
          || (Operation == CCB_ECC_SCALAR_MUL_RNG_BLOB_CREATION)
          || (Operation == CCB_MODULAR_EXP_CPU_BLOB_CREATION))
      {
        /* SAES: GCMPH = 0x0 (initial phase) as event that trig OPSTEP 0x1 --> 0x2 */
        WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KEYSIZE | AES_CR_CHMOD_0
                  | AES_CR_CHMOD_1);
      }

      else if ((Operation == CCB_ECDSA_SIGN_BLOB_USE) || (Operation == CCB_ECC_SCALAR_MUL_BLOB_USE)
               || (Operation == CCB_MODULAR_EXP_BLOB_USE))
      {
        /* SAES: GCMPH = 0x0 (initial phase) as event that trig OPSTEP 0x1 --> 0x12 */
        WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KEYSIZE | AES_CR_CHMOD_0
                  | AES_CR_CHMOD_1 | AES_CR_MODE_1);
      }

      else
      {
        /* Do nothing */
      }

      /* Wait for Key valid to be set */
      if (Protect_SAES_WaitFLAG(hccb, AES_SR_KEYVALID, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        return HAL_ERROR;
      }

      else
      {
        /* do nothing */
      }
      break;

    case HAL_CCB_USER_KEY_HSW:

      if ((Operation == CCB_ECDSA_SIGN_CPU_BLOB_CREATION) || (Operation == CCB_ECDSA_SIGN_RNG_BLOB_CREATION)
          || (Operation == CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION)
          || (Operation == CCB_ECC_SCALAR_MUL_RNG_BLOB_CREATION)
          || (Operation == CCB_MODULAR_EXP_CPU_BLOB_CREATION))
      {
        /* SAES: GCMPH = 0x0 (initial phase) as event that trig OPSTEP 0x1 --> 0x2 */
        WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KEYSIZE | AES_CR_CHMOD_0
                  | AES_CR_CHMOD_1);
      }

      else if ((Operation == CCB_ECDSA_SIGN_BLOB_USE) || (Operation == CCB_ECC_SCALAR_MUL_BLOB_USE)
               || (Operation == CCB_MODULAR_EXP_BLOB_USE))
      {
        /* SAES: GCMPH = 0x0 (initial phase) as event that trig OPSTEP 0x1 --> 0x12 */
        WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KEYSIZE | AES_CR_CHMOD_0 |
                  AES_CR_CHMOD_1 | AES_CR_MODE_1);
      }

      else
      {
        /* Do nothing */
      }

      /* Wait for Key valid to be set */
      if (Protect_SAES_WaitFLAG(hccb, AES_SR_KEYVALID, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        return HAL_ERROR;
      }

      else
      {
        /* do nothing */
      }

      /*we need to read BKP register from TAMP to transfer SW Key to the SAES where
      it will be XOR with HW key, new key in SAES register*/
      for (uint32_t k = 0UL; k < 8UL; k++)
      {
        /* Determine address of the specified Backup register */
        tmp = (uint32_t)(&(TAMP->BKP0R));
        tmp += (k * 4UL);

        /* Read the data from the specified register */
        if ((*(__IO uint32_t *)tmp) != 0UL)
        {
          /* Set state, error code and return error */
          hccb->State = HAL_CCB_STATE_ERROR;
          hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
          return HAL_ERROR;
        }
      }
      break;

    default :
      return HAL_ERROR;
      break;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Unwrap SAES key
  * @param  hccb CCB handle
  * @param  pWrappingKey pointer to the wrapping key structure
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef Protect_SAES_UnwrapKey(CCB_HandleTypeDef *hccb, const CCB_WrappingKeyTypeDef *pWrappingKey,
                                                uint32_t Timeout)
{
  uint32_t in_count = 0UL;
  uint32_t tickstart = HAL_GetTick()  ;

  if (pWrappingKey->AES_Algorithm != CCB_AES_ECB)
  {
    WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KMOD_0 | AES_CR_KEYSIZE | AES_CR_CHMOD_0);
  }
  else
  {
    WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KMOD_0 | AES_CR_KEYSIZE);
  }

  /* Wait for Key valid to be set */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_KEYVALID, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Disable the SAES peripheral */
  SAES->CR &=  ~AES_CR_EN;

  /* wait for key valid */
  while (HAL_IS_BIT_CLR(SAES->SR, AES_SR_KEYVALID))
  {
    if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
    {
      SAES->CR &= ~AES_CR_EN;

      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }
  }

  /* Set the operating mode*/
  MODIFY_REG(SAES->CR, AES_CR_KMOD, AES_CR_KMOD_0);

  /* key preparation for decryption, operating mode 2*/
  MODIFY_REG(SAES->CR, AES_CR_MODE, AES_CR_MODE_0);

  /* Enable SAES */
  SAES->CR |= AES_CR_EN;

  /* wait  CCF in SAES */
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Return to decryption operating mode(Mode 3)*/
  MODIFY_REG(SAES->CR, AES_CR_MODE, AES_CR_MODE_1);

  if (pWrappingKey->AES_Algorithm != CCB_AES_ECB)
  {
    /* Set the Initialization Vector */
    SAES->IVR3 = *(uint32_t *)(pWrappingKey->pInitVect);
    SAES->IVR2 = *(uint32_t *)(pWrappingKey->pInitVect + 1U);
    SAES->IVR1 = *(uint32_t *)(pWrappingKey->pInitVect + 2U);
    SAES->IVR0 = *(uint32_t *)(pWrappingKey->pInitVect + 3U);
  }
  /* Enable CRYP */
  SAES->CR |= AES_CR_EN;

  /* Set the phase */
  while (in_count < 8UL) /* symmetric key size is always 256 */
  {
    /* Write four times to input the key to encrypt */
    SAES->DINR  = pWrappingKey->pUserWrappedWrappingKey[in_count];
    in_count++;
    SAES->DINR  = pWrappingKey->pUserWrappedWrappingKey[in_count];
    in_count++;
    SAES->DINR  = pWrappingKey->pUserWrappedWrappingKey[in_count];
    in_count++;
    SAES->DINR  = pWrappingKey->pUserWrappedWrappingKey[in_count];
    in_count++;

    /* wait  CCF in SAES */
    if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  /* Disable the SAES */
  SAES->CR &=  ~AES_CR_EN;
  SAES->ICR |=  0x0EUL;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Get optimal number of bits inside an array of u8
  * @param  byteNumber Number of u8 inside the array
  * @param  msb Most significant uint8_t of the array
  */
static uint32_t GetOptBitSize_u8(uint32_t byteNumber, uint8_t msb)
{
  uint32_t position;

  position = 32UL - __CLZ(msb);

  return (((byteNumber - 1UL) * 8UL) + position);
}

/**
  * @brief  Copy uint32_t array to uint8_t array to fit PKA number representation.
  * @param  dst Pointer to destination
  * @param  src Pointer to source
  * @param  n Number of uint8_t to copy
  * @retval None.
  */
static void CCB_Memcpy_u32_to_u8(uint8_t dst[], __IO const uint32_t src[], size_t n)
{
  uint32_t index_uint32_t = 0UL; /* This index is used outside of the loop */

  for (; index_uint32_t < (n / 4UL); index_uint32_t++)
  {
    /* Avoid casting from uint8_t* to uint32_t* by copying 4 uint8_t in a row */
    /* Apply __REV equivalent */
    uint32_t index_uint8_t = n - 4UL - (index_uint32_t * 4UL);
    dst[index_uint8_t + 3UL] = (uint8_t)((src[index_uint32_t] & 0x000000FFU));
    dst[index_uint8_t + 2UL] = (uint8_t)((src[index_uint32_t] & 0x0000FF00U) >> 8UL);
    dst[index_uint8_t + 1UL] = (uint8_t)((src[index_uint32_t] & 0x00FF0000U) >> 16UL);
    dst[index_uint8_t + 0UL] = (uint8_t)((src[index_uint32_t] & 0xFF000000U) >> 24UL);
  }

  /* Manage the buffers not aligned on uint32_t */
  if ((n % 4UL) == 1UL)
  {
    dst[0UL] = (uint8_t)((src[index_uint32_t] & 0x000000FFU));
  }
  else if ((n % 4UL) == 2UL)
  {
    dst[1UL] = (uint8_t)((src[index_uint32_t] & 0x000000FFU));
    dst[0UL] = (uint8_t)((src[index_uint32_t] & 0x0000FF00U) >> 8UL);
  }
  else if ((n % 4UL) == 3UL)
  {
    dst[2UL] = (uint8_t)((src[index_uint32_t] & 0x000000FFU));
    dst[1UL] = (uint8_t)((src[index_uint32_t] & 0x0000FF00U) >> 8UL);
    dst[0UL] = (uint8_t)((src[index_uint32_t] & 0x00FF0000U) >> 16UL);
  }
  else
  {
    /* The last element is already handle in the loop */
  }
}

/**
  * @brief  Copy uint8_t array to uint32_t array to fit number representation
  * @param  dst Pointer to destination
  * @param  src Pointer to source
  * @param  size Number of uint8_t to copy (must be multiple of 4)
  * @retval None.
  */
static void CCB_Memcpy_u8_to_u32(__IO uint32_t dst[], const uint8_t src[], size_t size)
{
  uint32_t index = 0UL;

  if (dst != NULL)
  {
    if (src != NULL)
    {
      for (; index < (size / 4UL); index++)
      {
        /* Apply the equivalent of __REV from uint8_t to uint32_t */
        dst[index] = ((uint32_t)src[(size - (index * 4UL) - 1UL)]) \
                     | ((uint32_t)src[(size - (index * 4UL) - 2UL)] << 8UL) \
                     | ((uint32_t)src[(size - (index * 4UL) - 3UL)] << 16UL) \
                     | ((uint32_t)src[(size - (index * 4UL) - 4UL)] << 24UL);
      }

      /* Manage the buffers not aligned on uint32_t */
      if ((size % 4UL) == 1UL)
      {
        dst[index] = (uint32_t)src[(size - (index * 4UL) - 1UL)];
      }
      else if ((size % 4UL) == 2UL)
      {
        dst[index] = ((uint32_t)src[(size - (index * 4UL) - 1UL)]) \
                     | ((uint32_t)src[(size - (index * 4UL) - 2UL)] << 8UL);
      }
      else if ((size % 4UL) == 3UL)
      {
        dst[index] = ((uint32_t)src[(size - (index * 4UL) - 1UL)]) \
                     | ((uint32_t)src[(size - (index * 4UL) - 2UL)] << 8UL) \
                     | ((uint32_t)src[(size - (index * 4UL) - 3UL)] << 16UL);
      }
      else
      {
        /* The last element is already handle in the loop */
      }
    }
  }
}

/**
  * @brief  Copy uint32_t array to uint32_t array.
  * @param  dst Pointer to destination
  * @param  src Pointer to source
  * @param  n Number of u32 to be handled
  * @retval None.
  */
void CCB_Memcpy_u32_to_u32(__IO uint32_t dst[], __IO const uint32_t src[], size_t n)
{
  /* For each element in the array */
  for (uint32_t index = 0UL; index < n; index++)
  {
    /* Copy the content */
    dst[index] = src[index];
  }
}

/**
  * @brief  Copy uint8_t array to uint64_t array to fit number representation
  * @param  dst Pointer to destination
  * @param  src Pointer to source
  * @retval None.
  */
static void CCB_Memcpy_u8_to_u64(__IO uint32_t dst[], const uint8_t src[])
{
  if ((dst != NULL) && (src != NULL))
  {
    /* Apply the equivalent of __REV from uint8_t to uint32_t */
    dst[0] = ((uint32_t)src[0]) | ((uint32_t)src[-1] << 8UL) | ((uint32_t)src[-2] << 16UL)
             | ((uint32_t)src[-3] << 24UL);
    dst[1] = ((uint32_t)src[-4]) | ((uint32_t)src[-5] << 8UL) | ((uint32_t)src[-6] << 16UL)
             | ((uint32_t)src[-7] << 24UL);
  }
}

/**
  * @brief  Copy uint8_t array to uint64_t array to fit number representation
  * @param  dst Pointer to destination
  * @param  src Pointer to source
  * @param  size Pointer to number of uint8_t to copy
  * @retval None.
  */
static void CCB_Memcpy_Not_Align(__IO uint32_t dst[], const uint8_t src[], size_t size)
{
  /* Manage the buffers not aligned on uint32_t */
  if ((size % 8UL) == 1UL)
  {
    dst[0] = ((uint32_t)src[0]);
    dst[1] = 0;
  }
  else if ((size % 8UL) == 2UL)
  {
    dst[0] = ((uint32_t)src[0]) | ((uint32_t)src[-1] << 8UL);;
    dst[1] = 0UL;
  }
  else if ((size % 8UL) == 3UL)
  {
    dst[0] = ((uint32_t)src[0]) | ((uint32_t)src[-1] << 8UL) | ((uint32_t)src[-2] << 16UL);
    dst[1] = 0UL;
  }

  else if ((size % 8UL) == 4UL)
  {
    dst[0] = ((uint32_t)src[0]) | ((uint32_t)src[-1] << 8UL) | ((uint32_t)src[-2] << 16UL)
             | ((uint32_t)src[-3] << 24UL);
    dst[1] = 0UL;
  }

  else if ((size % 8UL) == 5UL)
  {
    dst[0] = ((uint32_t)src[0]) | ((uint32_t)src[-1] << 8UL) | ((uint32_t)src[-2] << 16UL)
             | ((uint32_t)src[-3] << 24UL);
    dst[1] = ((uint32_t)src[-4]);
  }
  else if ((size % 8UL) == 6UL)
  {
    dst[0] = ((uint32_t)src[0]) | ((uint32_t)src[-1] << 8UL) | ((uint32_t)src[-2] << 16UL)
             | ((uint32_t)src[-3] << 24UL);
    dst[1] = ((uint32_t)src[-4]) | ((uint32_t)src[-5] << 8UL);
  }
  else if ((size % 8UL) == 7UL)
  {
    dst[0] = ((uint32_t)src[0]) | ((uint32_t)src[-1] << 8UL) | ((uint32_t)src[-2] << 16UL)
             | ((uint32_t)src[-3] << 24UL);
    dst[1] = ((uint32_t)src[-4]) | ((uint32_t)src[-5] << 8UL) | ((uint32_t)src[-6] << 16UL);
  }
  else
  {
    /* The last element is already handle in the loop */
  }

}

/**
  * @brief  Get cipher key size
  * @param  pCurveParam to Curve Parameters
  * @retval cipher key size.
  */
static uint32_t  CCB_get_cipherkey_size(CCB_ECDSACurveParamTypeDef *pCurveParam)
{
  uint32_t operand_size = 2U * ((((pCurveParam->modulusSizeByte) + 7U) / 8U) + 1U);

  if ((operand_size % 4U) != 0U)
  {
    return (operand_size - 2U);
  }
  else
  {
    return operand_size;
  }

}

/**
  * @brief  Wrap Symmetric Key.
  * @param  hccb CCB handle.
  * @param  pClearAESKey pointer to the clear AES Key.
  * @param  operation operation.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @retval HAL status.
  */
static HAL_StatusTypeDef CCB_WrapSymmetricKey(CCB_HandleTypeDef *hccb, const uint32_t *pClearAESKey, uint32_t operation,
                                              CCB_WrappingKeyTypeDef *pWrappingKey)
{

  uint32_t i;
  uint32_t cryp_in_count = 0UL;
  uint32_t cryp_out_count = 0UL;
  const uint32_t *pcryp_in_buff = pClearAESKey;
  uint32_t *pcryp_out_buff = pWrappingKey->pUserWrappedWrappingKey;

  if (hccb->State == HAL_CCB_STATE_READY)
  {

    /* Set Operation in CCB */
    MODIFY_REG(CCB->CR, CCB_CR_CCOP, operation);

    /* Wait until OPSTEP is set to 0x01 */
    if (CCB_WaitOperStep(hccb, 0x01, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Initialize RNG */
    if (CCB_RNG_Init() != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /*  Initialize SAES */
    if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* Disable the SAES peripheral clock */
      SAES->CR &=  ~AES_CR_EN;

      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /* Update the state */
    hccb->State = HAL_CCB_STATE_BUSY;

    if (pWrappingKey->AES_Algorithm != CCB_AES_ECB)
    {
      WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KMOD_0 | AES_CR_KEYSIZE | AES_CR_CHMOD_0);
    }

    else
    {
      WRITE_REG(SAES->CR, AES_CR_KEYSEL_0 | AES_CR_KMOD_0 | AES_CR_KEYSIZE);
    }

    /* Wait for Key valid to be set */
    if (Protect_SAES_WaitFLAG(hccb, AES_SR_KEYVALID, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Disable the CRYP peripheral clock */
    SAES->CR &=  ~AES_CR_EN;

    /* Set the operating mode*/
    MODIFY_REG(SAES->CR, AES_CR_KMOD, AES_CR_KMOD_0);

    /* Encryption operating mode(Mode 0)*/
    MODIFY_REG(SAES->CR, AES_CR_MODE, 0x0UL); /*!< Encryption mode   */

    if (pWrappingKey->AES_Algorithm != CCB_AES_ECB)
    {
      /* Set the Initialization Vector */
      SAES->IVR3 = *(uint32_t *)(pWrappingKey->pInitVect);
      SAES->IVR2 = *(uint32_t *)(pWrappingKey->pInitVect + 1U);
      SAES->IVR1 = *(uint32_t *)(pWrappingKey->pInitVect + 2U);
      SAES->IVR0 = *(uint32_t *)(pWrappingKey->pInitVect + 3U);
    }

    /* Enable CRYP */
    SAES->CR |= AES_CR_EN;

    while (cryp_in_count < CCB_SIZE_SKEY_INWORD)
    {
      for (i = 0UL; i < 4UL; i++)
      {
        SAES->DINR  = pcryp_in_buff[cryp_in_count];
        cryp_in_count++;
      }

      /* Wait for CCF flag to be raised */
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        return HAL_ERROR;
      }

      /* Clear CCF Flag */
      SET_BIT(SAES->ICR, AES_ICR_CCF);

      /* Read the output block from the output FIFO and put them in temporary buffer then
      get CrypOutBuff from temporary buffer */
      for (i = 0UL; i < 4UL; i++)
      {
        pcryp_out_buff[cryp_out_count] = SAES->DOUTR;
        cryp_out_count++;
      }
    }
  }
  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* CCB IPRST set */
  SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* CCB is busy while CCB IPRST is in progress */
  if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  /* clear CCB IPRST */
  CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Initial phase processing when blob creation
  * @param  hccb CCB handle
  * @param  pIV pointer to the initil vector
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_BlobCreation_InitialPhase(CCB_HandleTypeDef *hccb, uint32_t *pIV)
{
  /* Load IVs from RNG to SAES */
  SAES->IVR0 = CCB_IV0_VALUE;  /* SAES_IVR0 that must be equal to 0x2 */
  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* For IV1, IV2 and IV3, random generated values are loaded from RNG to SAES by CCB */
  SAES->IVR1 = CCB_FAKE_VALUE;
  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  SAES->IVR2 = CCB_FAKE_VALUE;
  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  SAES->IVR3 = CCB_FAKE_VALUE;
  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* if an error occurs, RNGERRF flag is set in PKA */
  if (HAL_CCB_GET_PKA_FLAG(PKA_SR_RNGERRF) == SET)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  else
  {
    /* Read back IVs from SAES */
    pIV[3] = SAES->IVR3;
    pIV[2] = SAES->IVR2;
    pIV[1] = SAES->IVR1;
    pIV[0] = SAES->IVR0;
  }

  /* Set EN in SAES_CR*/
  SAES->CR |= AES_CR_EN;

  /* Wait until CCF is SET in SAES_ISR (end of GCM init) */
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set SAES GCMPH Header phase and trig OPSTEP transition 0x2 --> 0x3 */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_0 | AES_CR_EN);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initial phase processing when blob use
  * @param  hccb CCB handle
  * @param  pIV pointer to the initil vector
  * @param  pTag pointer to the Tag
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_BlobUse_InitialPhase(CCB_HandleTypeDef *hccb, const uint32_t *pIV, uint32_t *pTag)
{
  uint16_t count;

  /* Set IVs from created Blob */
  SAES->IVR0 = pIV[0];
  SAES->IVR1 = pIV[1];
  SAES->IVR2 = pIV[2];
  SAES->IVR3 = pIV[3];

  /* Set EN in SAES_CR*/
  SAES->CR |= AES_CR_EN;

  /* Wait until CCF is SET in SAES_ISR (end of GCM init) */
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Write reference tag in CCB */
  for (count = 0; count < CCB_BLOCK_SIZE; count++)
  {
    WRITE_REG(hccb->Instance->REFTAGR[count], pTag[count]);
  }

  /* Set SAES GCMPH Header phase and trig OPSTEP transition 0x12 --> 0x13 */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH | AES_CR_EN,
             AES_CR_GCMPH_0 | AES_CR_EN);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Final phase processing when blob creation
  * @param  hccb CCB handle
  * @param  Operation Operation
  * @param  pTag pointer to the Tag
  * @param  sizeparam size of parameters
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_BlobCreation_FinalPhase(CCB_HandleTypeDef *hccb, uint32_t Operation, uint32_t *pTag,
                                                     uint32_t sizeparam)
{
  uint32_t last_block[4] = {0};
  uint16_t count;
  uint32_t operand_size;
  uint32_t cipherkey_size;

  /* set operand size in 32bits */
  operand_size   = 2UL * ((uint32_t)(((sizeparam) + 7UL) / 8UL) + 1UL);
  if ((operand_size % 4UL) != 0UL)
  {
    cipherkey_size = operand_size - 2UL;
  }
  else
  {
    cipherkey_size = operand_size;
  }
  /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
  HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

  /* Preparing last Block */
  if (Operation == CCB_MODULAR_EXP_CPU_BLOB_CREATION)
  {
    /* bitsize of exp length, modulus n length  and modulus (address and data)*/
    last_block[1] = ((64UL * 2UL) + (operand_size * 32UL)) * 2UL;

    /* ciphred data size*/
    last_block[3] = cipherkey_size * 32UL;
  }

  else if ((Operation == CCB_ECDSA_SIGN_CPU_BLOB_CREATION) || (Operation == CCB_ECDSA_SIGN_RNG_BLOB_CREATION))
  {
    /* bitsize of |a|, b, p, n, Gx and Gy --> sizeparam*8*6*2 (address and data); n length,
    plength and a sign --> 64*3*2 (address and data) */
    last_block[1] = (((operand_size * 32UL) * 6UL) + (3UL * 64UL)) * 2UL;

    /* 1 ciphred data with 256 size*/
    last_block[3] = cipherkey_size * 32UL;
  }
  else
  {
    /* bitsize of |a|, b, p, n, --> sizeparam*8*4*2 (address and data); n length,
    plength and a sign --> 64*3*2 (address and data) */

    last_block[1] = (((operand_size * 32UL) * 4UL) + (3UL * 64UL)) * 2UL;

    /* 1 ciphred data with 256 size*/
    last_block[3] = cipherkey_size * 32UL;
  }

  for (count = 0; count < CCB_BLOCK_SIZE; count++)
  {
    SAES->DINR = last_block[count];
  }

  /* Wait until CCF flag is SET in SAES */
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Read Authentif Tag */
  for (count = 0U; count < CCB_BLOCK_SIZE; count++)
  {
    pTag[count] = SAES->DOUTR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Final phase processing when blob use
  * @param  hccb CCB handle
  * @param  Operation Operation
  * @param  sizeparam size of parameters
  * @retval HAL status
  */
static HAL_StatusTypeDef CCB_BlobUse_FinalPhase(CCB_HandleTypeDef *hccb, uint32_t Operation, uint32_t sizeparam)
{
  uint32_t last_block[4] = {0};
  uint16_t count;
  uint32_t operand_size;
  uint32_t cipherkey_size;

  /* set operand size in 32bits */
  operand_size   = 2UL * ((uint32_t)(((sizeparam) + 7UL) / 8UL) + 1UL);
  if ((operand_size % 4UL) != 0UL)
  {
    cipherkey_size = operand_size - 2UL;
  }
  else
  {
    cipherkey_size = operand_size;
  }

  /* Set SAES GCMPH final phase */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_0 | AES_CR_GCMPH_1);

  /* Preparing last Block */
  if (Operation == CCB_MODULAR_EXP_BLOB_USE)
  {
    /* bitsize of exp length, modulus n length  and modulus (address and data)*/
    last_block[1] = ((64UL * 2UL) + (operand_size * 32UL)) * 2UL;

    /* ciphred data size*/
    last_block[3] = cipherkey_size * 32UL;
  }

  else if (Operation == CCB_ECDSA_SIGN_BLOB_USE)
  {
    /* bitsize of |a|, b, p, n, Gx and Gy --> sizeparam*8*6*2 (address and data); n length,
    plength and a sign --> 64*3*2 (address and data) */
    last_block[1] = (((operand_size * 32UL) * 6UL) + (3UL * 64UL)) * 2UL;

    /* 1 ciphred data with 256 size*/
    last_block[3] = cipherkey_size * 32UL;
  }
  else
  {
    /* bitsize of |a|, b, p, n, --> sizeparam*8*4*2 (address and data); n length,
    plength and a sign --> 64*3*2 (address and data) */

    last_block[1] = (((operand_size * 32UL) * 4UL) + (3UL * 64UL)) * 2UL;

    /* 1 ciphred data with 256 size*/
    last_block[3] = cipherkey_size * 32UL;
  }

  for (count = 0U; count < CCB_BLOCK_SIZE; count++)
  {
    SAES->DINR = last_block[count];
  }

  /* Wait until CCF flag is SET in SAES  */
  if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Read Authentif Tag and check integrity of Blob as event that trig OPSTEP transition 0x17 --> 0x18 */
  for (count = 0U; count < CCB_BLOCK_SIZE; count++)
  {
    if ((SAES->DOUTR) != 0UL)
    {
      /* Set state, error code and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      hccb->ErrorCode = HAL_CCB_ERROR_OPERATION;
      return HAL_ERROR;
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Blob Usage: ECDSA Signature Creation.
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pClearPrivateKey pointer to the clear private key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pIV pointer to the IV.
  * @param  pTag pointer to the Tag.
  * @param  pWarappedKey pointer to the Warapped Key.
  * @param  CCB_Operation is the CCB Operations.
  * @retval HAL status.
  */
static HAL_StatusTypeDef CCB_ECDSA_SignBlobCreation(CCB_HandleTypeDef *hccb, CCB_ECDSACurveParamTypeDef *pCurveParam,
                                                    const uint8_t *pClearPrivateKey,
                                                    CCB_WrappingKeyTypeDef *pWrappingKey, uint32_t *pIV,
                                                    uint32_t *pTag, uint32_t *pWarappedKey, uint8_t CCB_Operation)
{
  uint16_t count;
  uint32_t countBlock = 0UL;
  uint32_t offset;
  uint32_t operand_size;
  uint32_t cipherkey_size;

  /* Set Operation in CCB */
  MODIFY_REG(CCB->CR, CCB_CR_CCOP, CCB_Operation);

  /* Wait until OPSTEP is set to 0x01 */
  if (CCB_WaitOperStep(hccb, 0x01, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Initialize RNG */
  if (CCB_RNG_Init() != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Initialize PKA */
  if (Protect_PKA_Init(hccb, CCB_Operation) != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /*  Initialize SAES */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* Disable the SAES peripheral clock */
    SAES->CR &=  ~AES_CR_EN;

    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* Wrapping Key configuration */
  if (WrappingKeyConfiguration(hccb, CCB_Operation, pWrappingKey) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x02 */
  if (CCB_WaitOperStep(hccb, 0x02, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* set operand size (in word 32bits)*/

  operand_size   = 2UL * ((uint32_t)(((pCurveParam->modulusSizeByte) + 7UL) / 8UL) + 1UL);

  if ((operand_size % 4UL) != 0UL)
  {
    cipherkey_size = operand_size - 2UL;
  }
  else
  {
    cipherkey_size = operand_size;
  }
  /* Initial Phase processing */
  if (CCB_BlobCreation_InitialPhase(hccb, pIV) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x03 */
  if (CCB_WaitOperStep(hccb, 0x03, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set ECDSA parameters */
  if (CCB_ECDSASign_SetPram(hccb, pCurveParam) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set SAES GCMPH Payload phase and trig OPSTEP that trig OPSTEP transition 0x3 --> 0x4 */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_1);

  if (CCB_Operation == CCB_ECDSA_SIGN_CPU_BLOB_CREATION)
  {
    /* Wait until OPSTEP is set to 0x04 */
    if (CCB_WaitOperStep(hccb, 0x04, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
    HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

    /* Write private Key d by CPU  (user key) */
    if ((pCurveParam->modulusSizeByte % 8UL) != 0UL)
    {
      for (offset = 0UL; offset < (operand_size - 4UL); offset += 2UL)
      {
        CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + offset],
                             &pClearPrivateKey[(pCurveParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
      }

      CCB_Memcpy_Not_Align(&PKA->RAM[PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + offset],
                           &pClearPrivateKey[(pCurveParam->modulusSizeByte) - ((offset * 4UL) + 1UL)],
                           pCurveParam->modulusSizeByte % 8UL);
      RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + offset + 2UL);
    }
    else
    {
      for (offset = 0UL; offset < (operand_size - 2UL); offset += 2UL)
      {
        CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + offset],
                             &pClearPrivateKey[(pCurveParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
      }

      RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + offset);
    }
    /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x4 --> 0x8 */
    if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }
  }
  else if (CCB_Operation == CCB_ECDSA_SIGN_RNG_BLOB_CREATION)
  {
    /* Wait until OPSTEP is set to 0x6 */
    if (CCB_WaitOperStep(hccb, 0x06, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
    HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

    /* Write private d Key from RNG */

    for (offset = 0UL; offset < (operand_size - 2UL); offset++)
    {
      if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }
      PKA->RAM[PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + offset] = CCB_FAKE_VALUE;
    }

    RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D
                  + offset);

    /* Check RNG Error Flag in PKA */
    if (HAL_CCB_GET_PKA_FLAG(PKA_SR_RNGERRF) != RESET)
    {
      /* Set state and  return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /* Wait until RNGOKF flag is SET in PKA and trig OPSTEP transition 0x6 --> 0x8 */
    if (Protect_PKA_WaitFLAG(hccb, PKA_SR_RNGOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }
  }
  else
  {
    /* Nothing To Do */
  }

  /* Wait until OPSTEP is set to 0x08 */
  if (CCB_WaitOperStep(hccb, 0x08, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
  HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

  /* Read clear-text private key d for encryption */
  for (offset = 0; offset < cipherkey_size; offset++)
  {
    PKA->RAM[PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + offset] = CCB_MAGIC_VALUE;

    if ((offset % 4UL) == 3UL)
    {
      /* Wait until CCF flag is SET in SAES*/
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }

      /* Read ciphered private Key d */
      for (count = 0U; count < CCB_BLOCK_SIZE; count++)
      {
        pWarappedKey[cipherkey_size - (countBlock + count + 1UL)]
          = READ_REG(SAES->DOUTR);
      }
      countBlock += 4UL;
    }
  }

  /* Wait for Galois Filter End of Computation */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }
  if ((operand_size % 4UL) != 0UL)
  {
    RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D
                  + cipherkey_size);
  }
  /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x08 --> 0x09 */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set SAES GCMPH final phase */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_0 | AES_CR_GCMPH_1);

  /* Wait until OPSTEP is set to 0x0A */
  if (CCB_WaitOperStep(hccb, 0x0A, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Final phase processing */
  if (CCB_BlobCreation_FinalPhase(hccb, CCB_Operation, pTag,
                                  pCurveParam->modulusSizeByte) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }


  /* CCB IPRST set */
  SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* CCB is busy while CCB IPRST is in progress */
  if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return timeout*/
    return HAL_TIMEOUT;
  }

  /* clear CCB IPRST */
  CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}


/**
  * @brief  Blob Creation: ECC generate (by RNG) and wrap the private Key (no user input).
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pClearPrivateKey pointer to the related wrapped Private Key Blob.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  WarappedKey pointer to the related wrapped Private Key Blob.
  * @param  CCB_Operation is the CCB Operations.
  * @retval HAL status.
  */
static HAL_StatusTypeDef CCB_ECC_ScalarMulBlobCreation(CCB_HandleTypeDef *hccb,
                                                       CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                       const uint8_t *pClearPrivateKey,
                                                       CCB_WrappingKeyTypeDef *pWrappingKey,
                                                       uint32_t *IV, uint32_t *Tag, uint32_t *WarappedKey,
                                                       uint8_t CCB_Operation)
{
  uint16_t count;
  uint32_t countBlock = 0UL;
  uint32_t offset;
  uint32_t operand_size;
  uint32_t cipherkey_size;

  if (hccb->State == HAL_CCB_STATE_READY)
  {
    /* Set Operation in CCB */
    MODIFY_REG(CCB->CR, CCB_CR_CCOP, CCB_Operation);

    /* Wait until OPSTEP is set to 0x01 */
    if (CCB_WaitOperStep(hccb, 0x01, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Initialize RNG */
    if (CCB_RNG_Init() != HAL_OK)
    {
      /* return state and error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /* Initialize PKA */
    if (Protect_PKA_Init(hccb, CCB_Operation) != HAL_OK)
    {
      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /*  Initialize SAES */
    if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* Disable the SAES peripheral clock */
      SAES->CR &=  ~AES_CR_EN;

      /* Set state and return error */
      hccb->State = HAL_CCB_STATE_ERROR;
      return HAL_ERROR;
    }

    /* Update the state */
    hccb->State = HAL_CCB_STATE_BUSY;

    /* Wrapping Key configuration */
    if (WrappingKeyConfiguration(hccb, CCB_Operation, pWrappingKey) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x02 */
    if (CCB_WaitOperStep(hccb, 0x02, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Update the state */
    hccb->State = HAL_CCB_STATE_BUSY;

    /* set operand size */
    operand_size   = 2UL * ((uint32_t)(((pCurveParam->primeOrderSizeByte) + 7UL) / 8UL) + 1UL);
    if ((operand_size % 4UL) != 0UL)
    {
      cipherkey_size = operand_size - 2UL;
    }
    else
    {
      cipherkey_size = operand_size;
    }

    /* Initial Phase processing */
    if (CCB_BlobCreation_InitialPhase(hccb, IV) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Wait until OPSTEP is set to 0x03 */
    if (CCB_WaitOperStep(hccb, 0x03, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Set ECC Scalar multiplications parameters */
    if (CCB_ECCMul_SetPram(hccb, pCurveParam) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Set SAES GCMPH Payload phase and trig OPSTEP that trig OPSTEP transition 0x3 --> 0x4 */
    MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_1);

    /* Wait until OPSTEP is set to 0x04 */
    if (CCB_WaitOperStep(hccb, 0x04, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
    HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

    if (CCB_Operation == CCB_ECC_SCALAR_MUL_CPU_BLOB_CREATION)
    {

      /* Write clear scalar k by CPU */
      if ((pCurveParam->modulusSizeByte % 8UL) != 0UL)
      {
        for (offset = 0UL; offset < (operand_size - 4UL); offset += 2UL)
        {
          CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_K + offset],
                               &pClearPrivateKey[(pCurveParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
        }

        CCB_Memcpy_Not_Align(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_K + offset],
                             &pClearPrivateKey[(pCurveParam->modulusSizeByte) - ((offset * 4UL) + 1UL)],
                             pCurveParam->modulusSizeByte % 8UL);
        RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_K + offset + 2UL);
      }
      else
      {
        for (offset = 0UL; offset < (operand_size - 2UL); offset += 2UL)
        {
          CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_K + offset],
                               &pClearPrivateKey[(pCurveParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
        }

        RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_K + offset);
      }
      /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x4 --> 0x8 */
      if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }
    }
    else if (CCB_Operation == CCB_ECC_SCALAR_MUL_RNG_BLOB_CREATION)
    {
      /* Write scalar k when RNG */
      for (offset = 0UL; offset < (operand_size - 2UL); offset++)
      {
        if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
          /* return error */
          return HAL_ERROR;
        }
        PKA->RAM[PKA_ECC_SCALAR_MUL_IN_K + offset] = CCB_FAKE_VALUE;
      }
      RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_K + offset);

      /* PKA: Check RNG Error Flag */
      if (HAL_CCB_GET_PKA_FLAG(PKA_SR_RNGERRF) != RESET)
      {
        /* Set state and return error */
        hccb->State = HAL_CCB_STATE_ERROR;
        return HAL_ERROR;
      }

      /* Wait until RNGOKF flag is SET in PKA and trig OPSTEP transition 0x6 --> 0x8 */
      if (Protect_PKA_WaitFLAG(hccb, PKA_SR_RNGOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }
    }
    else
    {
      /* Nothing To Do */
    }

    /* Wait until OPSTEP is set to 0x08 */
    if (CCB_WaitOperStep(hccb, 0x08, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
    HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

    /* Read clear-text scalar K for encryption */
    for (offset = 0; offset < cipherkey_size; offset++)
    {

      PKA->RAM[PKA_ECC_SCALAR_MUL_IN_K + offset] = CCB_MAGIC_VALUE;

      if ((offset % 4UL) == 3UL)
      {
        /* Wait until CCF flag is SET in SAES*/
        if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
          /* return error */
          return HAL_ERROR;
        }

        /* Read ciphered scalar k */
        for (count = 0U; count < CCB_BLOCK_SIZE; count++)
        {
          WarappedKey[cipherkey_size - (countBlock + count + 1U)]
            = READ_REG(SAES->DOUTR);
        }
        countBlock += 4UL;
      }
    }

    /* Wait for Galois Filter End of Computation */
    if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    if ((operand_size % 4UL) != 0UL)
    {
      RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_K
                    + cipherkey_size);
    }

    /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x8 --> 0xA */
    if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Set SAES GCMPH final phase */
    MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_0 | AES_CR_GCMPH_1);

    /* Wait until OPSTEP is set to 0x0A */
    if (CCB_WaitOperStep(hccb, 0x0A, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }

    /* Final phase processing */
    if (CCB_BlobCreation_FinalPhase(hccb, CCB_Operation, Tag,
                                    pCurveParam->modulusSizeByte) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }


    /* CCB IPRST set */
    SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

    /* CCB is busy while CCB IPRST is in progress */
    if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    /* clear CCB IPRST */
    CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

    /* Update the CCB state */
    hccb->State = HAL_CCB_STATE_READY;
  }

  else
  {
    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    hccb->ErrorCode = HAL_CCB_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Usage: ECC Compute Scalar Multiplication.
  * @param  hccb CCB handle.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pIV pointer to the IV.
  * @param  pTag pointer to the Tag.
  * @param  pWarappedKey pointer to the Warapped Key.
  * @param  pInputPoint pointer to the input point structure.
  * @param  pOutputPoint pointer to the output point.
  * @param  pPublicKey pointer to the input public key for check.
  * @param  VerifOperation allows to compare the OutputPoint with the Publickey.
  * @retval HAL status.
  */
static HAL_StatusTypeDef CCB_ECC_ComputeScalarMul(CCB_HandleTypeDef *hccb, CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                  CCB_WrappingKeyTypeDef *pWrappingKey,
                                                  uint32_t *pIV, uint32_t *pTag, uint32_t *pWarappedKey,
                                                  CCB_ECCMulPointTypeDef *pInputPoint,
                                                  CCB_ECCMulPointTypeDef *pOutputPoint,
                                                  const uint32_t *pPublicKey,
                                                  uint8_t VerifOperation)
{
  __IO uint16_t f_count;
  uint16_t random1 = 0;
  uint16_t random2 = 0;
  uint16_t random3 = 0;
  uint16_t count_ram;
  uint32_t count_block = 0UL;
  uint32_t offset;
  uint32_t operand_size;
  uint32_t cipherkey_size;
  uint32_t tickstart;

  /* Set Operation in CCB */
  MODIFY_REG(CCB->CR, CCB_CR_CCOP, CCB_ECC_SCALAR_MUL_BLOB_USE);

  /* Wait until OPSTEP is set to 0x01 */
  if (CCB_WaitOperStep(hccb, 0x01, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Initialize RNG */
  if (CCB_RNG_Init() != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random1 == 0U)
  {
    random1 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random2 == 0U)
  {
    random2 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random3 == 0U)
  {
    random3 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  /* Initialize PKA */
  if (Protect_PKA_Init(hccb, CCB_ECC_SCALAR_MUL_BLOB_USE) != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }


  if (VerifOperation == CCB_VERIF_OPERATION_DISABLED)
  {
    /* Write Customized point coordinate */
    CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X ], pInputPoint->pPointX,
                         pCurveParam->modulusSizeByte);
    RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));
    CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y ], pInputPoint->pPointY,
                         pCurveParam->modulusSizeByte);
    RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));
  }
  else if (VerifOperation == CCB_VERIF_OPERATION_ENABLED)
  {
    /* Write  point G coordinate */
    CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X ], pCurveParam->pPointX,
                         pCurveParam->modulusSizeByte);
    RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));
    CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y ], pCurveParam->pPointY,
                         pCurveParam->modulusSizeByte);
    RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));
  }
  else
  {
    /* nothing to do */
  }

  /*  Initialize SAES */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* Disable the SAES peripheral */
    SAES->CR &=  ~AES_CR_EN;

    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* Wrapping Key configuration */
  if (WrappingKeyConfiguration(hccb, CCB_ECC_SCALAR_MUL_BLOB_USE, pWrappingKey) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x012 */
  if (CCB_WaitOperStep(hccb, 0x012, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* set 32bits word number and operand size*/

  operand_size   = 2UL * ((uint32_t)(((pCurveParam->primeOrderSizeByte) + 7UL) / 8UL) + 1UL);

  if ((operand_size % 4UL) != 0UL)
  {
    cipherkey_size = operand_size - 2UL;
  }
  else
  {
    cipherkey_size = operand_size;
  }

  /* Initial Phase Processing */
  if (CCB_BlobUse_InitialPhase(hccb, pIV, pTag) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x13 */
  if (CCB_WaitOperStep(hccb, 0x13, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }
  if (VerifOperation == CCB_COMPUTE_PUBLIC_KEY)
  {
    /* Set parameters */
    if (CCB_ECDSASign_SetPram(hccb, pCurveParam) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }
  }
  else
  {
    /* Set parameters */
    if (CCB_ECCMul_SetPram(hccb, pCurveParam) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }
  }

  /* Set SAES GCMPH Payload phase and trig OPSTEP that trig OPSTEP transition 0x13 --> 0x14 */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_1);

  /* Wait until OPSTEP is set to 0x14 */
  if (CCB_WaitOperStep(hccb, 0x14, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  for (offset = 0UL; offset < cipherkey_size; offset++)
  {
    /* Write Wrapped scalar k in PKA RAM */
    WRITE_REG(SAES->DINR, pWarappedKey[cipherkey_size - (offset + 1UL)]);

    if ((offset % 4UL) == 0x3UL)
    {
      /* Wait until CCF flag is SET in SAES */
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }

      /* Write Unrapped scalar k in PKA RAM */
      for (count_ram = 0U; count_ram < 4U; count_ram++)
      {
        PKA->RAM[PKA_ECDSA_SIGN_IN_K + (count_block + count_ram)] = CCB_MAGIC_VALUE;
      }
      count_block += 4UL;
    }
  }
  if ((operand_size % 4UL) != 0UL)
  {
    RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_K
                  + cipherkey_size);
  }

  /* Wait until OPSTEP is set to 0x17 */
  if (CCB_WaitOperStep(hccb, 0x17, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }
  if (VerifOperation == CCB_COMPUTE_PUBLIC_KEY)
  {
    /* Final phase processing */
    if (CCB_BlobUse_FinalPhase(hccb, CCB_ECDSA_SIGN_BLOB_USE, pCurveParam->modulusSizeByte) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }
  }
  else
  {
    /* Final phase processing */
    if (CCB_BlobUse_FinalPhase(hccb, CCB_ECC_SCALAR_MUL_BLOB_USE, pCurveParam->modulusSizeByte) != HAL_OK)
    {
      /* return error */
      return HAL_ERROR;
    }
  }

  /* Wait until OPSTEP is set to 0x18 */
  if (CCB_WaitOperStep(hccb, 0x18, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* SET PKA START operation bit and trig OPSTEP transition 0x18 --> 0x19 */
  SET_BIT(PKA->CR, PKA_CR_START);

  /* Wait until OPSTEP is set to 0x19 */
  if (CCB_WaitOperStep(hccb, 0x19, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until end of operation flag is SET in PKA and trig OPSTEP transition 0x19 --> 0x1A */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_PROCENDF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x1A */
  if (CCB_WaitOperStep(hccb, 0x1A, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Check PKA Operation error result */
  if ((PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_ERROR]) !=  CCB_PKA_ERROR_OPERATION_NONE)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  if (VerifOperation == CCB_VERIF_OPERATION_DISABLED)
  {
    /* P coordinate x */
    CCB_Memcpy_u32_to_u8(pOutputPoint->pPointX, &PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_X],
                         pCurveParam->modulusSizeByte);

    /* P coordinate y */
    CCB_Memcpy_u32_to_u8(pOutputPoint->pPointY, &PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_Y],
                         pCurveParam->modulusSizeByte);
  }
  else if (VerifOperation == CCB_COMPUTE_PUBLIC_KEY)
  {
    /* P coordinate x */
    CCB_Memcpy_u32_to_u8(pOutputPoint->pPointX, &PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_X],
                         pCurveParam->modulusSizeByte);

    /* P coordinate y */
    CCB_Memcpy_u32_to_u8(pOutputPoint->pPointY, &PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_Y],
                         pCurveParam->modulusSizeByte);
  }
  else /* (VerifOperation == CCB_VERIF_OPERATION_ENABLED) */
  {
    f_count = 0;
    while (f_count < random1)
    {
      f_count++;
    }

    /* P coordinate x */
    for (offset = 0UL; offset < ((pCurveParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check  public key coordinate x and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_X + offset] != pPublicKey[offset]) ||
           (f_count != random1) || (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }

    /* P coordinate y */

    for (offset = 0UL; offset < ((pCurveParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check  public key coordinate y and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_Y + offset] != pPublicKey[offset + 20U]) ||
           (f_count != random1) || (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }

    f_count = 0;
    while (f_count < random2)
    {
      f_count++;
    }

    /* P coordinate x */
    for (offset = 0UL; offset < ((pCurveParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check  public key coordinate x and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_X + offset] != pPublicKey[offset]) ||
           (f_count != random2) || (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }

    /* P coordinate y */

    for (offset = 0UL; offset < ((pCurveParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check  public key coordinate y and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_Y + offset] != pPublicKey[offset + 20U]) ||
           (f_count != random2) || (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }

    f_count = 0;
    while (f_count < random3)
    {
      f_count++;
    }

    /* P coordinate x */
    for (offset = 0UL; offset < ((pCurveParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check  public key coordinate x and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_X + offset] != pPublicKey[offset]) ||
           (f_count != random3) || (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }

    /* P coordinate y */

    for (offset = 0UL; offset < ((pCurveParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check  public key coordinate y and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_Y + offset] != pPublicKey[offset + 20U]) ||
           (f_count != random3) || (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }
  }

  /* CCB IPRST set */
  SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* CCB is busy while CCB IPRST is in progress */
  if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  /* clear CCB IPRST */
  CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Creation: RSA Wrap the private Key (input from user).
  * @param  hccb CCB handle.
  * @param  pParam pointer to the modular exponatiation parameters.
  * @param  pRSAClearPrivateKey pointer to the clear Private Key.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pWrappedExp pointer to the related wrapped Private Key Blob.
  * @retval HAL status.
  */
static HAL_StatusTypeDef CCB_RSA_ExpBlobCreation(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                                 const CCB_RSAClearKeyTypeDef *pRSAClearPrivateKey,
                                                 CCB_WrappingKeyTypeDef *pWrappingKey, uint32_t *pIV,
                                                 uint32_t *pTag, uint32_t *pWrappedExp, uint32_t *pWrappedPhi)
{
  uint16_t count;
  uint32_t countBlock = 0UL;
  uint32_t offset;
  uint32_t operand_size;
  uint32_t cipherkey_size;

  /* Set Operation in CCB */
  MODIFY_REG(CCB->CR, CCB_CR_CCOP, CCB_MODULAR_EXP_CPU_BLOB_CREATION);

  /* Wait until OPSTEP is set to 0x01 */
  if (CCB_WaitOperStep(hccb, 0x01, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Initialize RNG */
  if (CCB_RNG_Init() != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Initialize PKA */
  if (Protect_PKA_Init(hccb, CCB_MODULAR_EXP_CPU_BLOB_CREATION) != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /*  Initialize SAES */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* Disable the SAES peripheral clock */
    SAES->CR &=  ~AES_CR_EN;

    /* Set state, error code and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* Wrapping Key configuration */
  if (WrappingKeyConfiguration(hccb, CCB_MODULAR_EXP_CPU_BLOB_CREATION, pWrappingKey) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x02 */
  if (CCB_WaitOperStep(hccb, 0x02, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* set operand size */
  operand_size   = 2UL * ((uint32_t)(((pParam->modulusSizeByte) + 7UL) / 8UL) + 1UL);
  if ((operand_size % 4UL) != 0UL)
  {
    cipherkey_size = operand_size - 2UL;
  }
  else
  {
    cipherkey_size = operand_size;
  }

  /* Initial Phase processing */
  if (CCB_BlobCreation_InitialPhase(hccb, pIV) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x03 */
  if (CCB_WaitOperStep(hccb, 0x03, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set RSA Modular Exponentiation parameters */
  if (CCB_RSAModExp_SetPram(hccb, pParam) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set SAES GCMPH Payload phase and trig OPSTEP that trig OPSTEP transition 0x3 --> 0x4 */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_1);

  /* Wait until OPSTEP is set to 0x04 */
  if (CCB_WaitOperStep(hccb, 0x04, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
  HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

  /* Write clear-text exponent e  */
  if ((pParam->modulusSizeByte % 8UL) != 0UL)
  {
    for (offset = 0UL; offset < (operand_size - 4UL); offset += 2UL)
    {
      CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + offset],
                           &pRSAClearPrivateKey->pExp[(pParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
    }

    CCB_Memcpy_Not_Align(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + offset],
                         &pRSAClearPrivateKey->pExp[(pParam->modulusSizeByte) - ((offset * 4UL) + 1UL)],
                         pParam->modulusSizeByte % 8UL);
    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + offset + 2UL);
  }
  else
  {
    for (offset = 0; offset < (operand_size - 2UL); offset += 2UL)
    {
      CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + offset],
                           &pRSAClearPrivateKey->pExp[(pParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
    }

    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT
                  + offset);
  }


  /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x4 --> 0x5 */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x05 */
  if (CCB_WaitOperStep(hccb, 0x05, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
  HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

  /* Write clear-text phi  */
  if ((pParam->modulusSizeByte % 8UL) != 0UL)
  {
    for (offset = 0; offset < (operand_size - 4UL); offset += 2UL)
    {
      CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_PHI + offset],
                           &pRSAClearPrivateKey->pPhi[(pParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
    }

    CCB_Memcpy_Not_Align(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_PHI + offset],
                         &pRSAClearPrivateKey->pPhi[(pParam->modulusSizeByte) - ((offset * 4UL) + 1UL)],
                         pParam->modulusSizeByte % 8UL);
    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_PHI + offset + 2UL);
  }
  else
  {
    for (offset = 0; offset < (operand_size - 2UL); offset += 2UL)
    {
      CCB_Memcpy_u8_to_u64(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_PHI + offset],
                           &pRSAClearPrivateKey->pPhi[(pParam->modulusSizeByte) - ((offset * 4UL) + 1UL)]);
    }

    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_PHI + offset);
  }

  /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x5 --> 0x8:   */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x08 */
  if (CCB_WaitOperStep(hccb, 0x08, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
  HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

  /* Read clear exponent e for encryption  */
  for (offset = 0UL; offset < cipherkey_size; offset++)
  {

    PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + offset] = CCB_MAGIC_VALUE;

    if ((offset % 4UL) == 3UL)
    {
      /* Wait until CCF flag is SET in SAES*/
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }

      /* Read ciphered exponent e */
      for (count = 0U; count < CCB_BLOCK_SIZE; count++)
      {
        pWrappedExp[cipherkey_size - (countBlock + count + 1UL)]
          = READ_REG(SAES->DOUTR);
      }
      countBlock += 4UL;
    }
  }

  /* Wait for Galois Filter End of Computation */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  if ((operand_size % 4UL) != 0UL)
  {
    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT
                  + cipherkey_size);
  }

  /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x8 --> 0x9 */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x09 */
  if (CCB_WaitOperStep(hccb, 0x09, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
  HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

  countBlock = 0U;

  /* Read clear  phi for encryption  */
  for (offset = 0; offset < cipherkey_size; offset++)
  {

    PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_PHI + offset] = CCB_MAGIC_VALUE;

    if ((offset % 4UL) == 3UL)
    {
      /* Wait until CCF flag is SET in SAES*/
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }

      /* Read ciphered phi */
      for (count = 0U; count < CCB_BLOCK_SIZE; count++)
      {
        pWrappedPhi[cipherkey_size - (countBlock + count + 1UL)]
          = READ_REG(SAES->DOUTR);
      }
      countBlock += 4UL;
    }
  }

  /* Wait for Galois Filter End of Computation */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  if ((operand_size % 4UL) != 0UL)
  {
    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_PHI
                  + cipherkey_size);
  }

  /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x9 --> 0xA  */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set SAES GCMPH final phase */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_0 | AES_CR_GCMPH_1);

  /* Wait until OPSTEP is set to 0x0A */
  if (CCB_WaitOperStep(hccb, 0x0A, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Final phase processing */
  if (CCB_BlobCreation_FinalPhase(hccb, CCB_MODULAR_EXP_CPU_BLOB_CREATION, pTag,
                                  pParam->modulusSizeByte) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* CCB IPRST set */
  SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* CCB is busy while CCB IPRST is in progress */
  if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  /* clear CCB IPRST */
  CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Blob Usage: RSA Compute Modular exponentiation.
  * @param  hccb CCB handle.
  * @param  pParam pointer to the modular exponatiation parameters.
  * @param  pWrappingKey pointer to the Wrapping Key structure.
  * @param  pOperand pointer to the operand.
  * @param  pWrappedExp pointer to the related wrapped Private Key Blob.
  * @param  pModularExp pointer to the output operation.
  * @param  pReferenceModularExp pointer to the ReferenceModularExp computed in modular exponentiation Blob creation
  * @param  VerifOperation pointer to the VerifOperation.
  * @retval HAL status.
  */
static HAL_StatusTypeDef CCB_RSA_ComputeModularExp(CCB_HandleTypeDef *hccb, CCB_RSAParamTypeDef *pParam,
                                                   CCB_WrappingKeyTypeDef *pWrappingKey, uint32_t *pIV,
                                                   uint32_t *pTag, uint32_t *pWrappedExp, uint32_t *pWrappedPhi,
                                                   const uint8_t *pOperand, uint8_t *pModularExp,
                                                   const uint32_t *pReferenceModularExp, uint8_t VerifOperation)
{
  __IO uint16_t f_count;
  uint16_t random1 = 0;
  uint16_t random2 = 0;
  uint16_t random3 = 0;
  uint16_t count_ram;
  uint32_t count_block = 0UL;
  uint32_t offset;
  uint32_t operand_size;
  uint32_t cipherkey_size;
  uint32_t tickstart;

  /* Set Operation in CCB */
  MODIFY_REG(CCB->CR, CCB_CR_CCOP, CCB_MODULAR_EXP_BLOB_USE);

  /* Wait until OPSTEP is set to 0x01 */
  if (CCB_WaitOperStep(hccb, 0x01, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Initialize RNG */
  if (CCB_RNG_Init() != HAL_OK)
  {
    /* Set State and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random1 == 0U)
  {
    random1 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random2 == 0U)
  {
    random2 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  while (random3 == 0U)
  {
    random3 = (uint16_t)(RNG->DR & 0x3FFU);
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Set state and return error */
      return HAL_ERROR;
    }
  }

  /* Initialize PKA */
  if (Protect_PKA_Init(hccb, CCB_MODULAR_EXP_BLOB_USE) != HAL_OK)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /*  Initialize SAES */
  if (Protect_SAES_WaitFLAG(hccb, AES_SR_BUSY, RESET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* Disable the SAES peripheral */
    SAES->CR &=  ~AES_CR_EN;

    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* Wrapping Key configuration */
  if (WrappingKeyConfiguration(hccb, CCB_MODULAR_EXP_BLOB_USE, pWrappingKey) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x012 */
  if (CCB_WaitOperStep(hccb, 0x012, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Update the state */
  hccb->State = HAL_CCB_STATE_BUSY;

  /* set 32bits word number of encrypted exponent e and encrypted phi*/
  /* set operand size */

  operand_size   = 2UL * ((uint32_t)(((pParam->modulusSizeByte) + 7UL) / 8UL) + 1UL);
  if ((operand_size % 4UL) != 0UL)
  {
    cipherkey_size = operand_size - 2UL;
  }

  else
  {
    cipherkey_size = operand_size;
  }

  /* Set Operand A - base of exponentiation */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT_BASE ], pOperand, pParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT_BASE + ((pParam->modulusSizeByte + 3UL)));

  /* Initial Phase Processing */
  if (CCB_BlobUse_InitialPhase(hccb, pIV, pTag) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x13 */
  if (CCB_WaitOperStep(hccb, 0x13, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set RSA Modular Exponentiation parameters */
  if (CCB_RSAModExp_SetPram(hccb, pParam) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Set SAES GCMPH Payload phase and trig OPSTEP that trig OPSTEP transition 0x13 --> 0x14 */
  MODIFY_REG(SAES->CR, AES_CR_GCMPH, AES_CR_GCMPH_1);

  /* Wait until OPSTEP is set to 0x14 */
  if (CCB_WaitOperStep(hccb, 0x14, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Write encrypted exponent e in DINR of SAES */
  for (offset = 0UL; offset < cipherkey_size; offset++)
  {
    WRITE_REG(SAES->DINR, pWrappedExp[cipherkey_size - (offset + 1U)]);

    if ((offset % 4UL) == 0x3UL)
    {
      /* Wait until CCF flag is SET in SAES */
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }

      /* Write key in PKA RAM */
      for (count_ram = 0U; count_ram < 4U; count_ram++)
      {
        PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + (count_block + count_ram)] = CCB_MAGIC_VALUE;
      }
      count_block += 4UL;
    }
  }

  if ((operand_size % 4UL) != 0UL)
  {
    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + cipherkey_size);
  }

  /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x14 --> 0x15 */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  if (CCB_WaitOperStep(hccb, 0x15, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Clear the CMF flag and the chaining mode status bits in 8 to 15 in PKA_SR */
  HAL_CCB_CLEAR_PKA_FLAG(PKA_CLRFR_CMFC);

  count_block = 0UL;
  /* Write encrypted phi in DINR of SAES */

  for (offset = 0UL; offset < cipherkey_size; offset++)
  {
    WRITE_REG(SAES->DINR, pWrappedPhi[cipherkey_size - (offset + 1UL)]);

    if ((offset % 4UL) == 0x3UL)
    {
      /* Wait until CCF flag is SET in SAES */
      if (Protect_SAES_WaitFLAG(hccb, AES_ISR_CCF, SET, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        /* return error */
        return HAL_ERROR;
      }

      /* Write key in PKA RAM */
      for (count_ram = 0U; count_ram < 4U; count_ram++)
      {
        PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_PHI + (count_block + count_ram)] = CCB_MAGIC_VALUE;
      }
      count_block += 4UL;
    }
  }

  if ((operand_size % 4UL) != 0UL)
  {
    RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_PHI + cipherkey_size);
  }

  /* Wait until DATAOKF flag is SET in PKA and trig OPSTEP transition 0x15 --> 0x17 */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_DATAOKF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x17 */
  if (CCB_WaitOperStep(hccb, 0x17, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Final phase processing */
  if (CCB_BlobUse_FinalPhase(hccb, CCB_MODULAR_EXP_BLOB_USE, pParam->modulusSizeByte) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x18 */
  if (CCB_WaitOperStep(hccb, 0x18, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* SET PKA START operation bit and trig OPSTEP transition 0x18 --> 0x19 */
  SET_BIT(PKA->CR, PKA_CR_START);

  /* Wait until OPSTEP is set to 0x19 */
  if (CCB_WaitOperStep(hccb, 0x19, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until end of operation flag is SET in PKA and trig OPSTEP transition 0x19 --> 0x1A */
  if (Protect_PKA_WaitFLAG(hccb, PKA_SR_PROCENDF, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Wait until OPSTEP is set to 0x1A */
  if (CCB_WaitOperStep(hccb, 0x1A, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  /* Check PKA Operation error result */
  if ((PKA->RAM[PKA_MODULAR_EXP_OUT_ERROR]) !=  CCB_PKA_ERROR_OPERATION_NONE)
  {
    /* Set state and return error */
    hccb->State = HAL_CCB_STATE_ERROR;
    return HAL_ERROR;
  }

  if (VerifOperation == CCB_VERIF_OPERATION_DISABLED)
  {
    /* Read result output */
    CCB_Memcpy_u32_to_u8(pModularExp, &PKA->RAM[PKA_MODULAR_EXP_OUT_RESULT], pParam->modulusSizeByte);
  }
  else /* CCB_VERIF_OPERATION_ENABLED */
  {
    f_count = 0;
    while (f_count < random1)
    {
      f_count++;
    }

    for (offset = 0UL; offset < ((pParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check Modular Exponentiation and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_MODULAR_EXP_OUT_RESULT + offset] != pReferenceModularExp[offset]) || (f_count != random1) ||
           (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }

    }

    f_count = 0;
    while (f_count < random2)
    {
      f_count++;
    }

    for (offset = 0UL; offset < ((pParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check Modular Exponentiation and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_MODULAR_EXP_OUT_RESULT + offset] != pReferenceModularExp[offset]) || (f_count != random2) ||
           (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }

    f_count = 0;
    while (f_count < random3)
    {
      f_count++;
    }

    for (offset = 0UL; offset < ((pParam->modulusSizeByte + 3UL) / 4UL); offset++)
    {
      /* Check Modular Exponentiation and improve robustness against intrusion (intentional) */
      if (((PKA->RAM[PKA_MODULAR_EXP_OUT_RESULT + offset] != pReferenceModularExp[offset]) || (f_count != random3) ||
           (f_count == 0U)))
      {
        /* Set state, and intrusion error */
        hccb->State = HAL_CCB_STATE_ERROR;
        HAL_CCB_IntrusionCallback(hccb);
      }
    }
  }

  /* CCB IPRST set */
  SET_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* CCB is busy while CCB IPRST is in progress */
  if (CCB_WaitFLAG(hccb, CCB_SR_BUSY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  /* clear CCB IPRST */
  CLEAR_BIT(hccb->Instance->CR, CCB_CR_IPRST);

  /* Update the CCB state */
  hccb->State = HAL_CCB_STATE_READY;

  /* Return HAL OK */
  return HAL_OK;
}

/**
  * @brief  Erase the PKA RAM.
  * @retval HAL status.
  */
static HAL_StatusTypeDef PKA_RAM_Erase(void)
{
  uint32_t index;
  __IO uint8_t random_nbr = 0U;
  uint32_t tickstart;

  PKA->RAM[CCB_PKA_RAM_SIZE - 1U] = CCB_MAGIC_VALUE;

  /* For each element in the PKA RAM */
  for (index = 0; index < CCB_PKA_RAM_SIZE; index++)
  {
    if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }
    /* Clear the content */
    PKA->RAM[index] = RNG->DR;
  }

  if (PKA->RAM[CCB_PKA_RAM_SIZE - 1U] == CCB_MAGIC_VALUE)
  {
    if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    tickstart = HAL_GetTick();

    while (random_nbr == 0U)
    {
      random_nbr = (uint8_t)(RNG->DR & 0xFFU);
      if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
      {
        /* Set state and return error */
        return HAL_ERROR;
      }
    }

    while (random_nbr != 0UL)
    {
      random_nbr--;
    }

    /* For each element in the PKA RAM */
    for (index = 0; index < CCB_PKA_RAM_SIZE; index++)
    {
      if (CCB_RNG_Wait_SET_FLAG(RNG_SR_DRDY, HAL_CCB_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
      {
        return HAL_ERROR;
      }
      /* Clear the content */
      PKA->RAM[index] = RNG->DR;
    }

    if (PKA->RAM[CCB_PKA_RAM_SIZE - 1U] == CCB_MAGIC_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Return HAL OK */
  return HAL_OK;

}

/**
  * @brief  CCB PKA ECDSA Signature.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pClearPrivateKey pointer to the clear private key.
  * @param  pInteger pointer to the integer k.
  * @param  pHash pointer to the input hash.
  * @param  pSignature Pointer to output signature
  * @retval HAL status.
  */
static HAL_StatusTypeDef PKA_ECDSASign(CCB_ECDSACurveParamTypeDef *pCurveParam,
                                       const uint8_t *pClearPrivateKey, uint8_t *pInteger, uint8_t *pHash,
                                       CCB_ECDSASignTypeDef *pSignature)
{
  uint32_t tickstart;
  uint32_t timeout = HAL_CCB_TIMEOUT_DEFAULT_VALUE;

  /* Get the prime order n length */
  PKA->RAM[PKA_ECDSA_SIGN_IN_ORDER_NB_BITS] = GetOptBitSize_u8(pCurveParam->primeOrderSizeByte,
                                                               *(pCurveParam->pPrimeOrder));

  /* Get the modulus p length */
  PKA->RAM[PKA_ECDSA_SIGN_IN_MOD_NB_BITS] = GetOptBitSize_u8(pCurveParam->modulusSizeByte, *(pCurveParam->pModulus));

  /* Get the coefficient a sign */
  PKA->RAM[PKA_ECDSA_SIGN_IN_A_COEFF_SIGN] = pCurveParam->coefSignA;

  /* Move the input parameters coefficient |a| to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_A_COEFF], pCurveParam->pAbsCoefA, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_A_COEFF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters coefficient B to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_B_COEFF], pCurveParam->pCoefB, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_B_COEFF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters modulus value p to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_MOD_GF], pCurveParam->pModulus, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_MOD_GF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters integer k to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_K], pInteger, pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_K + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Move the input parameters base point G coordinate x to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_INITIAL_POINT_X], pCurveParam->pPointX,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_INITIAL_POINT_X + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters base point G coordinate y to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_INITIAL_POINT_Y], pCurveParam->pPointY,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_INITIAL_POINT_Y + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters hash of message z to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_HASH_E], pHash, pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_HASH_E + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Move the input parameters private key d to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D], pClearPrivateKey, pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Move the input parameters prime order n to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_SIGN_IN_ORDER_N], pCurveParam->pPrimeOrder,
                       pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_SIGN_IN_ORDER_N + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  /* Set the mode and deactivate the interrupts */
  MODIFY_REG(PKA->CR, PKA_CR_MODE | PKA_CR_PROCENDIE | PKA_CR_RAMERRIE | PKA_CR_ADDRERRIE | PKA_CR_OPERRIE,
             CCB_PKA_ECDSA_SIGNATURE_MODE << PKA_CR_MODE_Pos);

  /* Start the computation */
  PKA->CR |= PKA_CR_START;

  /* Wait for the end of operation or timeout */
  while ((PKA->SR & PKA_SR_PROCENDF) == 0UL)
  {
    if (((HAL_GetTick() - tickstart) > timeout) || (timeout == 0UL))
    {
      /* Abort any ongoing operation */
      CLEAR_BIT(PKA->CR, PKA_CR_EN);
      /* Make ready for the next operation */
      SET_BIT(PKA->CR, PKA_CR_EN);

      return HAL_TIMEOUT;
    }

  }

  /* Clear all flags */
  PKA->CLRFR |= (PKA_CLRFR_PROCENDFC | PKA_CLRFR_RAMERRFC | PKA_CLRFR_ADDRERRFC | PKA_CLRFR_OPERRFC);

  CCB_Memcpy_u32_to_u8(pSignature->pRSign, &PKA->RAM[PKA_ECDSA_SIGN_OUT_SIGNATURE_R], pCurveParam->primeOrderSizeByte);
  CCB_Memcpy_u32_to_u8(pSignature->pSSign, &PKA->RAM[PKA_ECDSA_SIGN_OUT_SIGNATURE_S], pCurveParam->primeOrderSizeByte);

  if (PKA_RAM_Erase() != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Blob Usage: ECC Compute Scalar Multiplication.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pClearPrivateKey pointer to the related wrapped Private Key Blob.
  * @param  PublicKey is table of two coordinates X and Y of the publicKey.
  * @retval HAL status.
  */
static HAL_StatusTypeDef PKA_ECC_ComputeScalarMul(CCB_ECCMulCurveParamTypeDef *pCurveParam,
                                                  const uint8_t *pClearPrivateKey, uint32_t PublicKey[2][20])
{
  uint32_t tickstart;
  uint32_t timeout = HAL_CCB_TIMEOUT_DEFAULT_VALUE;

  /*********************************************************************************** Set input parameter in PKA RAM */
  /* Get the prime order n length */
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_EXP_NB_BITS] = GetOptBitSize_u8(pCurveParam->primeOrderSizeByte,
                                                                 *(pCurveParam->pPrimeOrder));

  /* Get the modulus length */
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_OP_NB_BITS] = GetOptBitSize_u8(pCurveParam->modulusSizeByte,
                                                                *(pCurveParam->pModulus));

  /* Get the coefficient a sign */
  PKA->RAM[PKA_ECC_SCALAR_MUL_IN_A_COEFF_SIGN] = pCurveParam->coefSignA;

  /* Move the input parameters coefficient |a| to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_A_COEFF], pCurveParam->pAbsCoefA, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_A_COEFF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters coefficient b to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_B_COEFF], pCurveParam->pCoefB, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_B_COEFF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters modulus value p to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_MOD_GF], pCurveParam->pModulus, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_MOD_GF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters scalar multiplier k to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_K], pClearPrivateKey, pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_K + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Move the input parameters Point P coordinate x to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X], pCurveParam->pPointX,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters Point P coordinate y to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y], pCurveParam->pPointY,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters curve prime order N to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECC_SCALAR_MUL_IN_N_PRIME_ORDER], pCurveParam->pPrimeOrder,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECC_SCALAR_MUL_IN_N_PRIME_ORDER + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /********************************************************************************************** Start the operation */
  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  /* Set the mode and deactivate the interrupts */
  MODIFY_REG(PKA->CR, PKA_CR_MODE | PKA_CR_PROCENDIE | PKA_CR_RAMERRIE | PKA_CR_ADDRERRIE | PKA_CR_OPERRIE,
             CCB_PKA_ECC_MUL_MODE << PKA_CR_MODE_Pos);

  /* Start the computation */
  PKA->CR |= PKA_CR_START;

  /* Wait for the end of operation or timeout */
  while ((PKA->SR & PKA_SR_PROCENDF) == 0UL)
  {
    if (((HAL_GetTick() - tickstart) > timeout) || (timeout == 0UL))
    {
      /* Abort any ongoing operation */
      CLEAR_BIT(PKA->CR, PKA_CR_EN);
      /* Make ready for the next operation */
      SET_BIT(PKA->CR, PKA_CR_EN);

      return HAL_TIMEOUT;
    }
  }

  /* Clear all flags */
  PKA->CLRFR |= (PKA_CLRFR_PROCENDFC | PKA_CLRFR_RAMERRFC | PKA_CLRFR_ADDRERRFC | PKA_CLRFR_OPERRFC);
  /* get PublicKey result */
  /* Move the result from appropriate location (with opprand size in 32bit word ) */
  CCB_Memcpy_u32_to_u32(PublicKey[0], &PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_X],
                        ((pCurveParam->modulusSizeByte + 3UL) / 4UL));
  CCB_Memcpy_u32_to_u32(PublicKey[1], &PKA->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_Y],
                        ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  if (PKA_RAM_Erase() != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Compute CCB Modular exponentiation.
  * @param  pParam pointer to the modular exponatiation parameters.
  * @param  pRSAClearPrivateKey pointer to the clear Private Key.
  * @param  pOp1 Pointer to Operand 1 (Array of size elements).
  * @param  pReferenceModularExp pointer to the ReferenceModularExp computed in modular exponentiation Blob creation.
  * @retval HAL status.
  */
static HAL_StatusTypeDef PKA_RSA_ComputeModularExp(CCB_RSAParamTypeDef *pParam,
                                                   const CCB_RSAClearKeyTypeDef *pRSAClearPrivateKey,
                                                   uint8_t *pOp1, uint32_t *pReferenceModularExp)
{
  uint32_t tickstart = HAL_GetTick();

  /* Get the number of bit per operand */
  PKA->RAM[PKA_MODULAR_EXP_IN_OP_NB_BITS] = pParam->modulusSizeByte * 8U;

  /* Get the number of bit of the exponent */
  PKA->RAM[PKA_MODULAR_EXP_IN_EXP_NB_BITS] = pParam->expSizeByte * 8U;

  /* Move the input parameters pOp1 to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT_BASE], pOp1, pParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT_BASE + ((pParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the exponent to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_EXPONENT], pRSAClearPrivateKey->pExp, pParam->expSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT + ((pParam->expSizeByte + 3UL) / 4UL));

  /* Move the modulus to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_MODULUS], pParam->pMod, pParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_MODULUS + ((pParam->modulusSizeByte + 3UL) / 4UL));

  /* Move Phi value to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_MODULAR_EXP_PROTECT_IN_PHI], pRSAClearPrivateKey->pPhi, pParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_MODULAR_EXP_PROTECT_IN_PHI + ((pParam->modulusSizeByte + 3UL) / 4UL));

  /* Set the mode and deactivate the interrupts */
  MODIFY_REG(PKA->CR, PKA_CR_MODE | PKA_CR_PROCENDIE | PKA_CR_RAMERRIE | PKA_CR_ADDRERRIE | PKA_CR_OPERRIE,
             CCB_PKA_MODE_MODULAR_EXP_PROTECT << PKA_CR_MODE_Pos);

  /* Start the computation */
  PKA->CR |= PKA_CR_START;

  /* Wait for the end of operation or timeout */
  while ((PKA->SR & PKA_SR_PROCENDF) == 0UL)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if ((HAL_GetTick() - tickstart) > HAL_CCB_TIMEOUT_DEFAULT_VALUE)
    {
      /* Abort any ongoing operation */
      CLEAR_BIT(PKA->CR, PKA_CR_EN);
      /* Make ready for the next operation */
      SET_BIT(PKA->CR, PKA_CR_EN);
      return HAL_TIMEOUT;
    }
  }

  /* Clear all flags */
  PKA->CLRFR |= (PKA_CLRFR_PROCENDFC | PKA_CLRFR_RAMERRFC | PKA_CLRFR_ADDRERRFC | PKA_CLRFR_OPERRFC);

  /* Move the result from appropriate location (with opprand size in 32bit word ) */
  CCB_Memcpy_u32_to_u32(pReferenceModularExp, &PKA->RAM[PKA_MODULAR_EXP_OUT_RESULT],
                        ((pParam->modulusSizeByte + 3UL) / 4UL));

  if (PKA_RAM_Erase() != HAL_OK)
  {
    /* return error */
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
 @brief  Verify the validity of a signature using elliptic curves over prime fields in blocking mode.
  * @param  pCurveParam pointer to the Curve parameters.
  * @param  pPublicKeyOut pointer to the public key.
  * @param  pHash pointer to the hash.
  * @param  pSignature Pointer to input signature
  * @retval HAL status.
  */
static HAL_StatusTypeDef PKA_ECDSAVerif(CCB_ECDSACurveParamTypeDef *pCurveParam,
                                        CCB_ECCMulPointTypeDef *pPublicKeyOut, const uint8_t *pHash,
                                        CCB_ECDSASignTypeDef *pSignature)
{
  uint32_t tickstart;
  uint32_t timeout = HAL_CCB_TIMEOUT_DEFAULT_VALUE;

  /* Set CCB input parameter in PKA RAM */
  /* Get the prime order n length */
  PKA->RAM[PKA_ECDSA_VERIF_IN_ORDER_NB_BITS] = GetOptBitSize_u8(pCurveParam->primeOrderSizeByte,
                                                                *(pCurveParam->pPrimeOrder));

  /* Get the modulus p length */
  PKA->RAM[PKA_ECDSA_VERIF_IN_MOD_NB_BITS] = GetOptBitSize_u8(pCurveParam->modulusSizeByte, *(pCurveParam->pModulus));

  /* Get the coefficient a sign */
  PKA->RAM[PKA_ECDSA_VERIF_IN_A_COEFF_SIGN] = pCurveParam->coefSignA;

  /* Move the input parameters coefficient |a| to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_A_COEFF], pCurveParam->pAbsCoefA, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_A_COEFF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters modulus value p to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_MOD_GF], pCurveParam->pModulus, pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_MOD_GF + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters base point G coordinate x to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_INITIAL_POINT_X], pCurveParam->pPointX,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_INITIAL_POINT_X + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters base point G coordinate y to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_INITIAL_POINT_Y], pCurveParam->pPointY,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_INITIAL_POINT_Y + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters public-key curve point Q coordinate xQ to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_PUBLIC_KEY_POINT_X], pPublicKeyOut->pPointX,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_PUBLIC_KEY_POINT_X + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters public-key curve point Q coordinate xQ to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_PUBLIC_KEY_POINT_Y], pPublicKeyOut->pPointY,
                       pCurveParam->modulusSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_PUBLIC_KEY_POINT_Y + ((pCurveParam->modulusSizeByte + 3UL) / 4UL));

  /* Move the input parameters signature part r to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_SIGNATURE_R], pSignature->pRSign, pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_SIGNATURE_R + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Move the input parameters signature part s to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_SIGNATURE_S], pSignature->pSSign, pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_SIGNATURE_S + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Move the input parameters hash of message z to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_HASH_E], pHash, pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_HASH_E + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));

  /* Move the input parameters curve prime order n to PKA RAM */
  CCB_Memcpy_u8_to_u32(&PKA->RAM[PKA_ECDSA_VERIF_IN_ORDER_N], pCurveParam->pPrimeOrder,
                       pCurveParam->primeOrderSizeByte);
  RAM_PARAM_END(PKA->RAM, PKA_ECDSA_VERIF_IN_ORDER_N + ((pCurveParam->primeOrderSizeByte + 3UL) / 4UL));


  /* Set the mode and deactivate the interrupts */
  MODIFY_REG(PKA->CR, PKA_CR_MODE | PKA_CR_PROCENDIE | PKA_CR_RAMERRIE | PKA_CR_ADDRERRIE | PKA_CR_OPERRIE,
             CCB_PKA_MODE_ECDSA_VERIFICATION << PKA_CR_MODE_Pos);

  /* Start the computation */
  PKA->CR |= PKA_CR_START;

  tickstart = HAL_GetTick();
  /* Wait for the end of operation or timeout */
  while ((PKA->SR & PKA_SR_PROCENDF) == 0UL)
  {
    if (((HAL_GetTick() - tickstart) > timeout) || (timeout == 0UL))
    {
      /* Abort any ongoing operation */
      CLEAR_BIT(PKA->CR, PKA_CR_EN);
      /* Make ready for the next operation */
      SET_BIT(PKA->CR, PKA_CR_EN);
      return HAL_TIMEOUT;
    }
  }

  /* Clear all flags */
  PKA->CLRFR |= (PKA_CLRFR_PROCENDFC | PKA_CLRFR_RAMERRFC | PKA_CLRFR_ADDRERRFC | PKA_CLRFR_OPERRFC);

  return HAL_OK;
}

/**
  * @brief  Return the result of the ECDSA verification operation.
  * @retval 1 if signature is verified, 0 in other case
  */
static uint32_t PKA_ECDSAVerif_Result(void)
{
  return (PKA->RAM[PKA_ECDSA_VERIF_OUT_RESULT]);
}

/**
  * @brief  Reset the PKA RAM.
  * @retval None
  */
static void CCB_PKA_RAMReset(void)
{
  uint32_t index;

  /* For each element in the PKA RAM */
  for (index = 0; index < CCB_PKA_RAM_SIZE; index++)
  {
    /* Clear the content */
    PKA->RAM[index] = 0UL;
  }
}

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
