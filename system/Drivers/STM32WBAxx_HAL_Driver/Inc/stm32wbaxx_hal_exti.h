/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_exti.h
  * @author  MCD Application Team
  * @brief   Header file of EXTI HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WBAxx_HAL_EXTI_H
#define STM32WBAxx_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Types EXTI Exported Types
  * @{
  */
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U,
  HAL_EXTI_RISING_CB_ID          = 0x01U,
  HAL_EXTI_FALLING_CB_ID         = 0x02U,
} EXTI_CallbackIDTypeDef;


/**
  * @brief  EXTI Handle structure definition
  */
typedef struct
{
  uint32_t Line;                    /*!<  Exti line number */
  void (* RisingCallback)(void);    /*!<  Exti rising callback */
  void (* FallingCallback)(void);   /*!<  Exti falling callback */
} EXTI_HandleTypeDef;

/**
  * @brief  EXTI Configuration structure definition
  */
typedef struct
{
  uint32_t Line;      /*!< The Exti line to be configured. This parameter
                           can be a value of @ref EXTI_Line */
  uint32_t Mode;      /*!< The Exit Mode to be configured for a core.
                           This parameter can be a combination of @ref EXTI_Mode */
  uint32_t Trigger;   /*!< The Exti Trigger to be configured. This parameter
                           can be a value of @ref EXTI_Trigger */
  uint32_t GPIOSel;   /*!< The Exti GPIO multiplexer selection to be configured.
                           This parameter is only possible for line 0 to 15. It
                           can be a value of @ref EXTI_GPIOSel */
} EXTI_ConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_Line  EXTI Line
  * @{
  */
#define EXTI_LINE_0                         (EXTI_GPIO     | EXTI_REG1 | 0x00U)
#define EXTI_LINE_1                         (EXTI_GPIO     | EXTI_REG1 | 0x01U)
#define EXTI_LINE_2                         (EXTI_GPIO     | EXTI_REG1 | 0x02U)
#define EXTI_LINE_3                         (EXTI_GPIO     | EXTI_REG1 | 0x03U)
#define EXTI_LINE_4                         (EXTI_GPIO     | EXTI_REG1 | 0x04U)
#define EXTI_LINE_5                         (EXTI_GPIO     | EXTI_REG1 | 0x05U)
#define EXTI_LINE_6                         (EXTI_GPIO     | EXTI_REG1 | 0x06U)
#define EXTI_LINE_7                         (EXTI_GPIO     | EXTI_REG1 | 0x07U)
#define EXTI_LINE_8                         (EXTI_GPIO     | EXTI_REG1 | 0x08U)
#define EXTI_LINE_9                         (EXTI_GPIO     | EXTI_REG1 | 0x09U)
#define EXTI_LINE_10                        (EXTI_GPIO     | EXTI_REG1 | 0x0AU)
#define EXTI_LINE_11                        (EXTI_GPIO     | EXTI_REG1 | 0x0BU)
#define EXTI_LINE_12                        (EXTI_GPIO     | EXTI_REG1 | 0x0CU)
#define EXTI_LINE_13                        (EXTI_GPIO     | EXTI_REG1 | 0x0DU)
#define EXTI_LINE_14                        (EXTI_GPIO     | EXTI_REG1 | 0x0EU)
#define EXTI_LINE_15                        (EXTI_GPIO     | EXTI_REG1 | 0x0FU)
#define EXTI_LINE_16                        (EXTI_CONFIG   | EXTI_REG1 | 0x10U)
#if defined(COMP1)
#define EXTI_LINE_17                        (EXTI_CONFIG   | EXTI_REG1 | 0x11U)
#endif /* COMP1 */
#if defined(COMP2)
#define EXTI_LINE_18                        (EXTI_CONFIG   | EXTI_REG1 | 0x12U)
#endif /* COMP2 */
#if defined (EXTI_IMR1_IM19)
#define EXTI_LINE_19                        (EXTI_CONFIG   | EXTI_REG1 | 0x13U)
#endif /* EXTI_IMR1_IM19 */
#if defined (EXTI_IMR1_IM20)
#define EXTI_LINE_20                        (EXTI_CONFIG   | EXTI_REG1 | 0x14U)
#endif /* EXTI_IMR1_IM20 */
/**
  * @}
  */

/** @defgroup EXTI_Mode  EXTI Mode
  * @{
  */
#define EXTI_MODE_NONE                      0x00000000U
#define EXTI_MODE_INTERRUPT                 0x00000001U
#define EXTI_MODE_EVENT                     0x00000002U
/**
  * @}
  */

/** @defgroup EXTI_Trigger  EXTI Trigger
  * @{
  */
#define EXTI_TRIGGER_NONE                   0x00000000U
#define EXTI_TRIGGER_RISING                 0x00000001U
#define EXTI_TRIGGER_FALLING                0x00000002U
#define EXTI_TRIGGER_RISING_FALLING         (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)
/**
  * @}
  */

/** @defgroup EXTI_GPIOSel  EXTI GPIOSel
  * @brief
  * @{
  */
#define EXTI_GPIOA                          0x00000000U
#define EXTI_GPIOB                          0x00000001U
#define EXTI_GPIOC                          0x00000002U
#if defined(GPIOD)
#define EXTI_GPIOD                          0x00000002U
#endif /* GPIOD */
#if defined(GPIOE)
#define EXTI_GPIOE                          0x00000004U
#endif /* GPIOE */
#if defined(GPIOG)
#define EXTI_GPIOG                          0x00000006U
#endif /* GPIOG */
#define EXTI_GPIOH                          0x00000007U
/**
  * @}
  */

#if defined(EXTI_SECCFGR1_SEC0)
/** @defgroup EXTI_Line_attributes EXTI line attributes
  * @brief EXTI line secure or non-secure and privileged or non-privileged attributes
  * @note secure and non-secure attributes are only available from secure state when the system
  *       implement the security (TZEN=1)
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define  EXTI_LINE_SEC                      (EXTI_LINE_ATTR_SEC_MASK | 0x00000001U)   /*!< Secure line attribute          */
#define  EXTI_LINE_NSEC                     (EXTI_LINE_ATTR_SEC_MASK | 0x00000000U)   /*!< Non-secure line attribute      */
#endif /* __ARM_FEATURE_CMSE */
#define  EXTI_LINE_PRIV                     (EXTI_LINE_ATTR_PRIV_MASK | 0x00000002U)   /*!< Privileged line attribute      */
#define  EXTI_LINE_NPRIV                    (EXTI_LINE_ATTR_PRIV_MASK | 0x00000000U)   /*!< Non-privileged line attribute  */
/**
  * @}
  */
#endif /* #if defined(EXTI_SECCFGR1_SEC0) */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Private constants --------------------------------------------------------*/
/** @defgroup EXTI_Private_Constants EXTI Private Constants
  * @{
  */
/**
  * @brief  EXTI Line property definition
  */
#define EXTI_PROPERTY_SHIFT                 24U
#define EXTI_DIRECT                         (0x01UL << EXTI_PROPERTY_SHIFT)
#define EXTI_CONFIG                         (0x02UL << EXTI_PROPERTY_SHIFT)
#define EXTI_GPIO                           ((0x04UL << EXTI_PROPERTY_SHIFT) | EXTI_CONFIG)
#define EXTI_RESERVED                       (0x08UL << EXTI_PROPERTY_SHIFT)
#define EXTI_PROPERTY_MASK                  (EXTI_DIRECT | EXTI_CONFIG | EXTI_GPIO)

/**
  * @brief  EXTI Register and bit usage
  */
#define EXTI_REG_SHIFT                      16U
#define EXTI_REG1                           (0x00UL << EXTI_REG_SHIFT)
#define EXTI_REG2                           (0x01UL << EXTI_REG_SHIFT)
#define EXTI_REG_MASK                       (EXTI_REG1 | EXTI_REG2)
#define EXTI_PIN_MASK                       0x0000001FU

/**
  * @brief  EXTI Mask for interrupt & event mode
  */
#define EXTI_MODE_MASK                      (EXTI_MODE_EVENT | EXTI_MODE_INTERRUPT)

/**
  * @brief  EXTI Mask for trigger possibilities
  */
#define EXTI_TRIGGER_MASK                   (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)

/**
  * @brief  EXTI Line number
  */
#if defined (EXTI_IMR1_IM20)
#define EXTI_LINE_NB                        20U
#elif defined (EXTI_IMR1_IM19)
#define EXTI_LINE_NB                        19U
#else /* EXTI_IMR1_IM20 */
#define EXTI_LINE_NB                        18U
#endif /* EXTI_IMR1_IM20 */

#if defined(EXTI_SECCFGR1_SEC0)
/**
  * @brief  EXTI Mask for secure & privilege attributes
  */
#define EXTI_LINE_ATTR_SEC_MASK             0x100U
#define EXTI_LINE_ATTR_PRIV_MASK            0x200U
/**
  * @}
  */
#endif /* #if defined(EXTI_SECCFGR1_SEC0) */

/* Private macros ------------------------------------------------------------*/
/** @defgroup EXTI_Private_Macros EXTI Private Macros
  * @{
  */
#define IS_EXTI_LINE(__LINE__)          ((((__LINE__) & ~(EXTI_PROPERTY_MASK | EXTI_REG_MASK | EXTI_PIN_MASK)) == 0x00U) && \
                                         ((((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_DIRECT)   || \
                                          (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_CONFIG)   || \
                                          (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_GPIO))    && \
                                         (((__LINE__) & (EXTI_REG_MASK | EXTI_PIN_MASK))      < \
                                          (((EXTI_LINE_NB / 32U) << EXTI_REG_SHIFT) | (EXTI_LINE_NB % 32U))))

#define IS_EXTI_MODE(__LINE__)          ((((__LINE__) & EXTI_MODE_MASK) != 0x00U) && \
                                         (((__LINE__) & ~EXTI_MODE_MASK) == 0x00U))

#define IS_EXTI_TRIGGER(__LINE__)       (((__LINE__) & ~EXTI_TRIGGER_MASK) == 0x00U)

#define IS_EXTI_PENDING_EDGE(__LINE__)  (((__LINE__) == EXTI_TRIGGER_RISING) || \
                                         ((__LINE__) == EXTI_TRIGGER_FALLING))

#define IS_EXTI_CONFIG_LINE(__LINE__)   (((__LINE__) & EXTI_CONFIG) != 0x00U)

#if defined(GPIOD)
#if defined(GPIOE) && defined(GPIOG)
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOD) || \
                                         ((__PORT__) == EXTI_GPIOE) || \
                                         ((__PORT__) == EXTI_GPIOG) || \
                                         ((__PORT__) == EXTI_GPIOH))
#elif defined(GPIOE)
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOD) || \
                                         ((__PORT__) == EXTI_GPIOE) || \
                                         ((__PORT__) == EXTI_GPIOH))
#elif defined(GPIOG)
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOD) || \
                                         ((__PORT__) == EXTI_GPIOG) || \
                                         ((__PORT__) == EXTI_GPIOH))
#else /* No GPIOE and GPIOG */
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOD) || \
                                         ((__PORT__) == EXTI_GPIOH))
#endif /* defined(GPIOE) && defined(GPIOG) */
#else /* No GPIOD */
#if defined(GPIOE) && defined(GPIOG)
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOE) || \
                                         ((__PORT__) == EXTI_GPIOG) || \
                                         ((__PORT__) == EXTI_GPIOH))
#elif defined(GPIOE)
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOE) || \
                                         ((__PORT__) == EXTI_GPIOH))
#elif defined(GPIOG)
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOG) || \
                                         ((__PORT__) == EXTI_GPIOH))
#else /* No GPIOE and GPIOG */
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOH))
#endif /* defined(GPIOE) && defined(GPIOG) */
#endif /* defined(GPIOD) */

#define IS_EXTI_GPIO_PIN(__PIN__)        ((__PIN__) < 16U)

#if defined(EXTI_SECCFGR1_SEC0)
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

#define IS_EXTI_LINE_ATTRIBUTES(__ATTRIBUTES__) (((((__ATTRIBUTES__) & EXTI_LINE_SEC) == EXTI_LINE_SEC) || \
                                                  (((__ATTRIBUTES__) & EXTI_LINE_NSEC) == EXTI_LINE_NSEC) || \
                                                  (((__ATTRIBUTES__) & EXTI_LINE_PRIV) == EXTI_LINE_PRIV) || \
                                                  (((__ATTRIBUTES__) & EXTI_LINE_NPRIV) == EXTI_LINE_NPRIV)) && \
                                                 (((__ATTRIBUTES__) & ~(EXTI_LINE_SEC|EXTI_LINE_NSEC|EXTI_LINE_PRIV|EXTI_LINE_NPRIV)) == 0U))

#else

#define IS_EXTI_LINE_ATTRIBUTES(__ATTRIBUTES__) (((((__ATTRIBUTES__) & EXTI_LINE_PRIV) == EXTI_LINE_PRIV) || \
                                                  (((__ATTRIBUTES__) & EXTI_LINE_NPRIV) == EXTI_LINE_NPRIV)) && \
                                                 (((__ATTRIBUTES__) & ~(EXTI_LINE_PRIV|EXTI_LINE_NPRIV)) == 0U))

#endif /* __ARM_FEATURE_CMSE */
#endif /* #if defined(EXTI_SECCFGR1_SEC0) */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
  * @brief    EXTI Exported Functions
  * @{
  */

/** @defgroup EXTI_Exported_Functions_Group1 Configuration functions
  * @brief    Configuration functions
  * @{
  */
/* Configuration functions ****************************************************/
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, const EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(const EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(const EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group2 IO operation functions
  * @brief    IO operation functions
  * @{
  */
/* IO operation functions *****************************************************/
void              HAL_EXTI_IRQHandler(const EXTI_HandleTypeDef *hexti);
uint32_t          HAL_EXTI_GetPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_ClearPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_GenerateSWI(const EXTI_HandleTypeDef *hexti);

/**
  * @}
  */

/** @addtogroup EXTI_Exported_Functions_Group3 EXTI line attributes management functions
  * @{
  */

#if defined(EXTI_SECCFGR1_SEC0)
/* EXTI line attributes management functions **********************************/
void              HAL_EXTI_ConfigLineAttributes(uint32_t ExtiLine, uint32_t LineAttributes);
HAL_StatusTypeDef HAL_EXTI_GetConfigLineAttributes(uint32_t ExtiLine, uint32_t *pLineAttributes);
#endif /* #if defined(EXTI_SECCFGR1_SEC0) */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
void              HAL_EXTI_LockAttributes(void);
uint32_t          HAL_EXTI_GetLockAttributes(void);
#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WBAxx_HAL_EXTI_H */
