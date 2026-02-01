/**
  ******************************************************************************
  * @file    stm32u3xx_hal_gtzc.h
  * @author  MCD Application Team
  * @brief   Header file of GTZC HAL module.
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
#ifndef STM32U3xx_HAL_GTZC_H
#define STM32U3xx_HAL_GTZC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

#if defined(GTZC_TZSC1) && defined(HAL_GTZC_MODULE_ENABLED)

/** @addtogroup GTZC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup GTZC_Exported_Types GTZC Exported Types
  * @{
  */

/*!< Values needed for MPCBB_Attribute_ConfigTypeDef structure sizing */
#define GTZC_MCPBB_NB_VCTR_REG_MAX      (12U)
              /*!< Maximum number of super-blocks (32 consecutive blocks, block size is 512 bytes) */
#define GTZC_MCPBB_NB_LCK_VCTR_REG_MAX  (1U)
              /*!< Maximum number of lock configuration registers to manage super-blocks */

  typedef struct
{
  uint32_t MPCBB_SecConfig_array[GTZC_MCPBB_NB_VCTR_REG_MAX];
                        /*!< Each element specifies secure access mode for a super-block.
                             Each bit corresponds to a block inside the super-block.
                             0 means non-secure, 1 means secure */
  uint32_t MPCBB_PrivConfig_array[GTZC_MCPBB_NB_VCTR_REG_MAX];
                        /*!< Each element specifies privilege access mode for a super-block.
                             Each bit corresponds to a block inside the super-block.
                             0 means non-privilege, 1 means privilege */
  uint32_t MPCBB_LockConfig_array[GTZC_MCPBB_NB_LCK_VCTR_REG_MAX];
                        /*!< Each bit specifies the lock configuration of a super-block (32 blocks).
                             0 means unlocked, 1 means locked */
} MPCBB_Attribute_ConfigTypeDef;

typedef struct
{
  uint32_t SecureRWIllegalMode; /*!< Secure read/write illegal access
                                     field. It can be a value of @ref GTZC_MPCBB_SecureRWIllegalMode */
  uint32_t InvertSecureState;   /*!< Default security state field (can be inverted or not).
                                     It can be a value of @ref GTZC_MPCBB_InvertSecureState */
  MPCBB_Attribute_ConfigTypeDef AttributeConfig; /*!< MPCBB attribute configuration sub-structure */
} MPCBB_ConfigTypeDef;

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/

/** @defgroup GTZC_Private_Constants GTZC Private Constants
  * @{
  */

/** @defgroup GTZC_Private_PeriphId_composition GTZC Peripheral identifier composition
  * @{
  */

/* composition definition for Peripheral identifier parameter (PeriphId) used in
 * HAL_GTZC_TZSC_ConfigPeriphAttributes() and HAL_GTZC_TZSC_GetConfigPeriphAttributes()
 * functions and also in all HAL_GTZC_TZIC relative functions.
 * Bitmap Definition
 *   bits[31:28] Field "register". Define the register index a peripheral belongs to.
 *               Each bit is dedicated to a single register.
 *   bit[5]      Field "all peripherals". If this bit is set then the PeriphId targets
 *               all peripherals within all registers.
 *   bits[4:0]   Field "bit position". Define the bit position within the
 *               register dedicated to the peripheral, value from 0 to 31.
 */
#define GTZC_PERIPH_REG_SHIFT     (28U)
#define GTZC_PERIPH_REG           (0xF0000000U)
#define GTZC_PERIPH_REG1          (0x00000000U)
#define GTZC_PERIPH_REG2          (0x10000000U)
#define GTZC_PERIPH_REG3          (0x20000000U)
#define GTZC_PERIPH_REG4          (0x30000000U)
#define GTZC_PERIPH_BIT_POSITION  (0x0000001FU)

/**
  * @}
  */

/** @defgroup GTZC_Private_Attributes_Msk GTZC Attributes Masks
  * @{
  */
#define GTZC_ATTR_SEC_MASK         0x100U
#define GTZC_ATTR_PRIV_MASK        0x200U

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup GTZC_Exported_Constants GTZC Exported Constants
  * @{
  */

/** @defgroup GTZC_MPCBB_SecureRWIllegalMode GTZC MPCBB SRWILADIS values
  * @{
  */

#define GTZC_MPCBB_SRWILADIS_ENABLE  (0U)
#define GTZC_MPCBB_SRWILADIS_DISABLE (GTZC_MPCBB_CR_SRWILADIS_Msk)

/**
  * @}
  */

/** @defgroup GTZC_MPCBB_InvertSecureState GTZC MPCBB INVSECSTATE values
  * @{
  */

#define GTZC_MPCBB_INVSECSTATE_NOT_INVERTED  (0U)
#define GTZC_MPCBB_INVSECSTATE_INVERTED      (GTZC_MPCBB_CR_INVSECSTATE_Msk)

/**
  * @}
  */

/** @defgroup GTZC_TZSC_TZIC_PeriphId GTZC TZSC and TZIC Peripheral identifier values
  * @{
  */
/* GTZC */
#define GTZC_PERIPH_TIM2          (GTZC_PERIPH_REG1 | GTZC_CFGR1_TIM2_Pos)
#define GTZC_PERIPH_TIM3          (GTZC_PERIPH_REG1 | GTZC_CFGR1_TIM3_Pos)
#define GTZC_PERIPH_TIM4          (GTZC_PERIPH_REG1 | GTZC_CFGR1_TIM4_Pos)
#define GTZC_PERIPH_TIM6          (GTZC_PERIPH_REG1 | GTZC_CFGR1_TIM6_Pos)
#define GTZC_PERIPH_TIM7          (GTZC_PERIPH_REG1 | GTZC_CFGR1_TIM7_Pos)
#define GTZC_PERIPH_WWDG          (GTZC_PERIPH_REG1 | GTZC_CFGR1_WWDG_Pos)
#define GTZC_PERIPH_IWDG          (GTZC_PERIPH_REG1 | GTZC_CFGR1_IWDG_Pos)
#define GTZC_PERIPH_SPI2          (GTZC_PERIPH_REG1 | GTZC_CFGR1_SPI2_Pos)
#if defined(USART2)
#define GTZC_PERIPH_USART2        (GTZC_PERIPH_REG1 | GTZC_CFGR1_USART2_Pos)
#endif /* USART2 */
#define GTZC_PERIPH_USART3        (GTZC_PERIPH_REG1 | GTZC_CFGR1_USART3_Pos)
#define GTZC_PERIPH_UART4         (GTZC_PERIPH_REG1 | GTZC_CFGR1_UART4_Pos)
#define GTZC_PERIPH_UART5         (GTZC_PERIPH_REG1 | GTZC_CFGR1_UART5_Pos)
#define GTZC_PERIPH_I2C1          (GTZC_PERIPH_REG1 | GTZC_CFGR1_I2C1_Pos)
#define GTZC_PERIPH_I2C2          (GTZC_PERIPH_REG1 | GTZC_CFGR1_I2C2_Pos)
#define GTZC_PERIPH_CRS           (GTZC_PERIPH_REG1 | GTZC_CFGR1_CRS_Pos)
#if defined(I2C4)
#define GTZC_PERIPH_I2C4          (GTZC_PERIPH_REG1 | GTZC_CFGR1_I2C4_Pos)
#endif /* I2C4 */
#define GTZC_PERIPH_LPTIM2        (GTZC_PERIPH_REG1 | GTZC_CFGR1_LPTIM2_Pos)
#define GTZC_PERIPH_FDCAN1        (GTZC_PERIPH_REG1 | GTZC_CFGR1_FDCAN1_Pos)
#if defined(FDCAN2)
#define GTZC_PERIPH_FDCAN2        (GTZC_PERIPH_REG1 | GTZC_CFGR1_FDCAN2_Pos)
#endif /* FDCAN2 */
#define GTZC_PERIPH_SPI3          (GTZC_PERIPH_REG1 | GTZC_CFGR1_SPI3_Pos)
#define GTZC_PERIPH_I3C1          (GTZC_PERIPH_REG1 | GTZC_CFGR1_I3C1_Pos)
#define GTZC_PERIPH_OPAMP         (GTZC_PERIPH_REG1 | GTZC_CFGR1_OPAMP_Pos)
#define GTZC_PERIPH_VREFBUF       (GTZC_PERIPH_REG1 | GTZC_CFGR1_VREFBUF_Pos)
#if defined(SPI4)
#define GTZC_PERIPH_SPI4          (GTZC_PERIPH_REG1 | GTZC_CFGR1_SPI4_Pos)
#endif /* SPI4 */

#define GTZC_PERIPH_TIM1          (GTZC_PERIPH_REG2 | GTZC_CFGR2_TIM1_Pos)
#define GTZC_PERIPH_SPI1          (GTZC_PERIPH_REG2 | GTZC_CFGR2_SPI1_Pos)
#if defined(TIM8)
#define GTZC_PERIPH_TIM8          (GTZC_PERIPH_REG2 | GTZC_CFGR2_TIM8_Pos)
#endif /* TIM8 */
#define GTZC_PERIPH_USART1        (GTZC_PERIPH_REG2 | GTZC_CFGR2_USART1_Pos)
#define GTZC_PERIPH_TIM15         (GTZC_PERIPH_REG2 | GTZC_CFGR2_TIM15_Pos)
#define GTZC_PERIPH_TIM16         (GTZC_PERIPH_REG2 | GTZC_CFGR2_TIM16_Pos)
#define GTZC_PERIPH_TIM17         (GTZC_PERIPH_REG2 | GTZC_CFGR2_TIM17_Pos)
#define GTZC_PERIPH_SAI1          (GTZC_PERIPH_REG2 | GTZC_CFGR2_SAI1_Pos)
#if defined(TIM12)
#define GTZC_PERIPH_TIM12         (GTZC_PERIPH_REG2 | GTZC_CFGR2_TIM12_Pos)
#endif /* TIM12 */
#define GTZC_PERIPH_USB           (GTZC_PERIPH_REG2 | GTZC_CFGR2_USB_Pos)
#define GTZC_PERIPH_I3C2          (GTZC_PERIPH_REG2 | GTZC_CFGR2_I3C2_Pos)
#define GTZC_PERIPH_LPUART1       (GTZC_PERIPH_REG2 | GTZC_CFGR2_LPUART1_Pos)
#define GTZC_PERIPH_I2C3          (GTZC_PERIPH_REG2 | GTZC_CFGR2_I2C3_Pos)
#define GTZC_PERIPH_LPTIM1        (GTZC_PERIPH_REG2 | GTZC_CFGR2_LPTIM1_Pos)
#define GTZC_PERIPH_LPTIM3        (GTZC_PERIPH_REG2 | GTZC_CFGR2_LPTIM3_Pos)
#define GTZC_PERIPH_LPTIM4        (GTZC_PERIPH_REG2 | GTZC_CFGR2_LPTIM4_Pos)
#define GTZC_PERIPH_COMP          (GTZC_PERIPH_REG2 | GTZC_CFGR2_COMP_Pos)

#define GTZC_PERIPH_CRC           (GTZC_PERIPH_REG3 | GTZC_CFGR3_CRC_Pos)
#define GTZC_PERIPH_TSC           (GTZC_PERIPH_REG3 | GTZC_CFGR3_TSC_Pos)
#define GTZC_PERIPH_ICACHE_REG    (GTZC_PERIPH_REG3 | GTZC_CFGR3_ICACHE_REG_Pos)
#define GTZC_PERIPH_ADC12         (GTZC_PERIPH_REG3 | GTZC_CFGR3_ADC12_Pos)
#if defined(AES)
#define GTZC_PERIPH_AES           (GTZC_PERIPH_REG3 | GTZC_CFGR3_AES_Pos)
#endif /* AES */
#define GTZC_PERIPH_HASH          (GTZC_PERIPH_REG3 | GTZC_CFGR3_HASH_Pos)
#define GTZC_PERIPH_RNG           (GTZC_PERIPH_REG3 | GTZC_CFGR3_RNG_Pos)
#if defined(PKA)
#define GTZC_PERIPH_PKA           (GTZC_PERIPH_REG3 | GTZC_CFGR3_PKA_Pos)
#endif /* PKA */
#if defined(SAES)
#define GTZC_PERIPH_SAES          (GTZC_PERIPH_REG3 | GTZC_CFGR3_SAES_Pos)
#endif /* SAES */
#if defined(CCB)
#define GTZC_PERIPH_CCB           (GTZC_PERIPH_REG3 | GTZC_CFGR3_CCB_Pos)
#endif /* CCB */
#define GTZC_PERIPH_SDMMC1        (GTZC_PERIPH_REG3 | GTZC_CFGR3_SDMMC1_Pos)
#define GTZC_PERIPH_OCTOSPI1_REG  (GTZC_PERIPH_REG3 | GTZC_CFGR3_OCTOSPI1_REG_Pos)
#define GTZC_PERIPH_RAMCFG        (GTZC_PERIPH_REG3 | GTZC_CFGR3_RAMCFG_Pos)
#define GTZC_PERIPH_DAC1          (GTZC_PERIPH_REG3 | GTZC_CFGR3_DAC1_Pos)
#define GTZC_PERIPH_ADF1          (GTZC_PERIPH_REG3 | GTZC_CFGR3_ADF1_Pos)
#if defined(HSP1)
#define GTZC_PERIPH_HSP1          (GTZC_PERIPH_REG3 | GTZC_CFGR3_HSP1_Pos)
#endif /* HSP1 */

#define GTZC_PERIPH_GPDMA1        (GTZC_PERIPH_REG4 | GTZC_CFGR4_GPDMA1_Pos)
#define GTZC_PERIPH_FLASH_REG     (GTZC_PERIPH_REG4 | GTZC_CFGR4_FLASH_REG_Pos)
#define GTZC_PERIPH_FLASH         (GTZC_PERIPH_REG4 | GTZC_CFGR4_FLASH_Pos)
#define GTZC_PERIPH_PWR           (GTZC_PERIPH_REG4 | GTZC_CFGR4_PWR_Pos)
#define GTZC_PERIPH_RCC           (GTZC_PERIPH_REG4 | GTZC_CFGR4_RCC_Pos)
#define GTZC_PERIPH_SYSCFG        (GTZC_PERIPH_REG4 | GTZC_CFGR4_SYSCFG_Pos)
#define GTZC_PERIPH_EXTI          (GTZC_PERIPH_REG4 | GTZC_CFGR4_EXTI_Pos)
#define GTZC_PERIPH_RTC           (GTZC_PERIPH_REG4 | GTZC_CFGR4_RTC_Pos)
#define GTZC_PERIPH_TAMP          (GTZC_PERIPH_REG4 | GTZC_CFGR4_TAMP_Pos)
#define GTZC_PERIPH_TZSC          (GTZC_PERIPH_REG4 | GTZC_CFGR4_TZSC_Pos)
#define GTZC_PERIPH_TZIC          (GTZC_PERIPH_REG4 | GTZC_CFGR4_TZIC_Pos)
#define GTZC_PERIPH_SRAM1         (GTZC_PERIPH_REG4 | GTZC_CFGR4_SRAM1_Pos)
#define GTZC_PERIPH_MPCBB1_REG    (GTZC_PERIPH_REG4 | GTZC_CFGR4_MPCBB1_REG_Pos)
#define GTZC_PERIPH_SRAM2         (GTZC_PERIPH_REG4 | GTZC_CFGR4_SRAM2_Pos)
#define GTZC_PERIPH_MPCBB2_REG    (GTZC_PERIPH_REG4 | GTZC_CFGR4_MPCBB2_REG_Pos)
#if defined(SRAM3_BASE)
#define GTZC_PERIPH_SRAM3         (GTZC_PERIPH_REG4 | GTZC_CFGR4_SRAM2_Pos)
#define GTZC_PERIPH_MPCBB3_REG    (GTZC_PERIPH_REG4 | GTZC_CFGR4_MPCBB2_REG_Pos)
#endif /* SRAM3_BASE */
#if defined(SRAM4_BASE)
#define GTZC_PERIPH_SRAM4         (GTZC_PERIPH_REG4 | GTZC_CFGR4_SRAM2_Pos)
#define GTZC_PERIPH_MPCBB4_REG    (GTZC_PERIPH_REG4 | GTZC_CFGR4_MPCBB2_REG_Pos)
#endif /* SRAM4_BASE */


#define GTZC_PERIPH_ALL           (0x00000020U)

/* Note that two maximum values are also defined here:
 * - max number of securable AHB/APB peripherals or masters
 *   (used in TZSC sub-block)
 * - max number of securable and TrustZone-aware AHB/APB peripherals or masters
 *   (used in TZIC sub-block)
 */
#if defined(HSP1)
#define GTZC_TZSC_PERIPH_NUMBER   (HAL_GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_HSP1) + 1U)
#else
#define GTZC_TZSC_PERIPH_NUMBER   (HAL_GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_ADF1) + 1U)
#endif /* HSP1 */

#if defined(SRAM4_BASE)
#define GTZC_TZIC_PERIPH_NUMBER   (HAL_GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_MPCBB4_REG) + 1U)
#else
#define GTZC_TZIC_PERIPH_NUMBER   (HAL_GTZC_GET_ARRAY_INDEX(GTZC_PERIPH_MPCBB2_REG) + 1U)
#endif /* SRAM4_BASE */


/**
  * @}
  */

/** @defgroup GTZC_TZSC_PeriphAttributes GTZC TZSC peripheral attribute values
  * @{
  */

/* user-oriented definitions for attribute parameter (PeriphAttributes) used in
 * HAL_GTZC_TZSC_ConfigPeriphAttributes() and HAL_GTZC_TZSC_GetConfigPeriphAttributes()
 * functions
 */
#define GTZC_TZSC_PERIPH_SEC    (GTZC_ATTR_SEC_MASK | 0x00000001U)  /*!< Secure attribute        */
#define GTZC_TZSC_PERIPH_NSEC   (GTZC_ATTR_SEC_MASK | 0x00000000U)  /*!< Non-secure attribute    */
#define GTZC_TZSC_PERIPH_PRIV   (GTZC_ATTR_PRIV_MASK | 0x00000002U) /*!< Privilege attribute     */
#define GTZC_TZSC_PERIPH_NPRIV  (GTZC_ATTR_PRIV_MASK | 0x00000000U) /*!< Non-privilege attribute */

/**
  * @}
  */

/** @defgroup GTZC_TZSC_Lock GTZC TZSC lock values
  * @{
  */

/* user-oriented definitions for HAL_GTZC_TZSC_GetLock() returned value */
#define GTZC_TZSC_LOCK_OFF  (0U)
#define GTZC_TZSC_LOCK_ON   GTZC_TZSC_CR_LCK_Msk

/**
  * @}
  */

/** @defgroup GTZC_MPCBB_Group GTZC MPCBB values
  * @{
  */

/* user-oriented definitions for MPCBB */
#define GTZC_MPCBB_BLOCK_SIZE           0x200U                        /* 512 Bytes */
#define GTZC_MPCBB_SUPERBLOCK_SIZE      (GTZC_MPCBB_BLOCK_SIZE * 32U) /* 16 KBytes */
#define GTZC_MCPBB_SUPERBLOCK_UNLOCKED  (0U)
#define GTZC_MCPBB_SUPERBLOCK_LOCKED    (1U)

#define GTZC_MCPBB_BLOCK_NSEC           (GTZC_ATTR_SEC_MASK  | 0U)
#define GTZC_MCPBB_BLOCK_SEC            (GTZC_ATTR_SEC_MASK  | 1U)
#define GTZC_MCPBB_BLOCK_NPRIV          (GTZC_ATTR_PRIV_MASK | 0U)
#define GTZC_MCPBB_BLOCK_PRIV           (GTZC_ATTR_PRIV_MASK | 2U)

/* user-oriented definitions for HAL_GTZC_MPCBB_GetLock() returned value */
#define GTZC_MCPBB_LOCK_OFF  (0U)
#define GTZC_MCPBB_LOCK_ON   (1U)

/**
  * @}
  */

/** @defgroup GTZC_TZIC_Flag GTZC TZIC flag values
  * @{
  */

/* user-oriented definitions for HAL_GTZC_TZIC_GetFlag() flag parameter */
#define GTZC_TZIC_NO_ILA_EVENT       (0U)
#define GTZC_TZIC_ILA_EVENT_PENDING  (1U)

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup GTZC_Private_Macros GTZC Private Macros
  * @{
  */

/* retrieve information to access register for a specific PeriphId */
#define GTZC_GET_REG_INDEX(periph_id)\
  (((periph_id) & GTZC_PERIPH_REG) >> GTZC_PERIPH_REG_SHIFT)
#define GTZC_GET_REG_INDEX_IN_INSTANCE(periph_id)\
  ((((periph_id) & GTZC_PERIPH_REG) <= GTZC_PERIPH_REG4) ? \
   (((periph_id) & GTZC_PERIPH_REG) >> GTZC_PERIPH_REG_SHIFT) : \
   ((((periph_id) & GTZC_PERIPH_REG) >> GTZC_PERIPH_REG_SHIFT) - 4U))
#define GTZC_GET_PERIPH_POS(periph_id)     ((periph_id) & GTZC_PERIPH_BIT_POSITION)

#if defined(CPU_IN_SECURE_STATE)
#define IS_GTZC_BASE_ADDRESS(mem, address)\
  ( ( (uint32_t)(address) == (uint32_t)GTZC_BASE_ADDRESS_NS(mem) ) || \
    ( (uint32_t)(address) == (uint32_t)GTZC_BASE_ADDRESS_S(mem) ) )
#else
#define IS_GTZC_BASE_ADDRESS(mem, address)\
  ( (uint32_t)(address) == (uint32_t)GTZC_BASE_ADDRESS_NS(mem) )
#endif /* CPU_IN_SECURE_STATE */

/* MISRA C:2012 Rule-20.10 deviation granted to use the definition of */
/* GTZC_MEM_SIZE(), GTZC_BASE_ADDRESS_S() and GTZC_BASE_ADDRESS_NS() */
#define GTZC_MEM_SIZE(mem)\
  ( mem ## _SIZE )

#define GTZC_BASE_ADDRESS_S(mem)\
  ( mem ## _BASE_S )

#define GTZC_BASE_ADDRESS_NS(mem)\
  ( mem ## _BASE_NS )

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup GTZC_Exported_Macros GTZC Exported Macros
  * @{
  */

/* user-oriented macro to get array index of a specific PeriphId
  * in case of GTZC_PERIPH_ALL usage in the two following functions:
  * HAL_GTZC_TZSC_ConfigPeriphAttributes() and HAL_GTZC_TZSC_GetConfigPeriphAttributes()
  */
#define HAL_GTZC_GET_ARRAY_INDEX(periph_id) \
  ((GTZC_GET_REG_INDEX((periph_id)) * 32U) + GTZC_GET_PERIPH_POS((periph_id)))

#define HAL_GTZC_TZSC_GET_ARRAY_INDEX(periph_id) \
  (((GTZC_GET_REG_INDEX(periph_id) * 32U) + GTZC_GET_PERIPH_POS(periph_id)))

#define HAL_GTZC_TZIC_GET_ARRAY_INDEX(periph_id) \
  ((GTZC_GET_REG_INDEX((periph_id)) * 32U) + GTZC_GET_PERIPH_POS((periph_id)))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup GTZC_Exported_Functions
  * @{
  */

/** @addtogroup GTZC_Exported_Functions_Group1
  * @brief    TZSC Initialization and Configuration functions
  * @{
  */

HAL_StatusTypeDef HAL_GTZC_TZSC_ConfigPeriphAttributes(uint32_t PeriphId,
                                                       uint32_t PeriphAttributes);
HAL_StatusTypeDef HAL_GTZC_TZSC_GetConfigPeriphAttributes(uint32_t PeriphId,
                                                          uint32_t *PeriphAttributes);

/**
  * @}
  */

#if defined(CPU_IN_SECURE_STATE)
/** @addtogroup GTZC_Exported_Functions_Group3
  * @brief    TZSC and TZSC-MPCWM Lock functions
  * @{
  */

void     HAL_GTZC_TZSC_Lock(GTZC_TZSC_TypeDef *TZSC_Instance);
uint32_t HAL_GTZC_TZSC_GetLock(const GTZC_TZSC_TypeDef *TZSC_Instance);

/**
  * @}
  */
#endif /* CPU_IN_SECURE_STATE */

/** @addtogroup GTZC_Exported_Functions_Group4
  * @brief    MPCBB Initialization and Configuration functions
  * @{
  */

HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMem(uint32_t MemBaseAddress,
                                           const MPCBB_ConfigTypeDef *pMPCBB_desc);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMem(uint32_t MemBaseAddress,
                                              MPCBB_ConfigTypeDef *pMPCBB_desc);
HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMemAttributes(uint32_t MemAddress,
                                                     uint32_t NbBlocks,
                                                     const uint32_t *pMemAttributes);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMemAttributes(uint32_t MemAddress,
                                                        uint32_t NbBlocks,
                                                        uint32_t *pMemAttributes);

#if defined(CPU_IN_SECURE_STATE)
HAL_StatusTypeDef HAL_GTZC_MPCBB_LockConfig(uint32_t MemAddress,
                                            uint32_t NbSuperBlocks,
                                            const uint32_t *pLockAttributes);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetLockConfig(uint32_t MemAddress,
                                               uint32_t NbSuperBlocks,
                                               uint32_t *pLockAttributes);
HAL_StatusTypeDef HAL_GTZC_MPCBB_Lock(uint32_t MemBaseAddress);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetLock(uint32_t MemBaseAddress,
                                         uint32_t *pLockState);
#endif /* CPU_IN_SECURE_STATE */

/**
  * @}
  */

#if defined(CPU_IN_SECURE_STATE)
/** @addtogroup GTZC_Exported_Functions_Group5
  * @brief    TZIC functions
  * @{
  */

HAL_StatusTypeDef HAL_GTZC_TZIC_DisableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_GTZC_TZIC_EnableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_GTZC_TZIC_GetFlag(uint32_t PeriphId, uint32_t *pFlag);
HAL_StatusTypeDef HAL_GTZC_TZIC_ClearFlag(uint32_t PeriphId);

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group6
  * @brief    IRQ related Functions
  * @{
  */

void HAL_GTZC_IRQHandler(void);
void HAL_GTZC_TZIC_Callback(uint32_t PeriphId);

/**
  * @}
  */
#endif /* CPU_IN_SECURE_STATE */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(GTZC_TZSC1) && defined(HAL_GTZC_MODULE_ENABLED) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U3xx_HAL_GTZC_H */
