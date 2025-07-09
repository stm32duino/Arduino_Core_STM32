/**
  ******************************************************************************
  * @file    stm32wb0x_ll_system.h
  * @author  MCD Application Team
  * @brief   Header file of SYSTEM LL module.
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
    The LL SYSTEM driver contains a set of generic APIs that can be
    used by user:
      (+) Some of the FLASH features need to be handled in the SYSTEM file.
      (+) Access to SYSCFG registers

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WB0x_LL_SYSTEM_H
#define STM32WB0x_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup SYSCFG_IO_LL_ES_INIT SYSCFG IO Exported Init structure
  * @{
  */
typedef struct
{

  uint32_t Line;                 /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range PA0 to PB15
                                      This parameter can be any combination of @ref EXTI_LL_EC_LINE */

  FunctionalState LineCommand;  /*!< Specifies the new state of the selected EXTI lines.
                                     This parameter can be set either to ENABLE or DISABLE */

  uint8_t Type;                 /*!< Specifies the type for the EXTI lines EDGE or LEVEL.
                                     This parameter can be a value of @ref EXTI_LL_EC_TYPE. */

  uint8_t Trigger;              /*!< Specifies the trigger signal active edge/level for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_LL_EC_TRIGGER. */
} LL_SYSCFG_IO_InitTypeDef;

/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
  * @{
  */
#define LL_SYSCFG_REMAP_FLASH                   0x00000000U                 /*!< Main Flash memory mapped at 0x00000000   */
#define LL_SYSCFG_REMAP_SRAM                    FLASH_CONFIG_REMAP          /*!< SRAM mapped at 0x00000000               */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_I2C_FASTMODEPLUS SYSCFG I2C FASTMODEPLUS
  * @{
  */
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PA0_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA0          SYSCFG_I2C_FMP_CTRL_I2C1_PA0_FMP /*!< Enable Fast Mode Plus on PA0       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PA1_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA1          SYSCFG_I2C_FMP_CTRL_I2C1_PA1_FMP /*!< Enable Fast Mode Plus on PA1       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB6_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB6          SYSCFG_I2C_FMP_CTRL_I2C1_PB6_FMP  /*!< Enable Fast Mode Plus on PB6       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB7_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB7          SYSCFG_I2C_FMP_CTRL_I2C1_PB7_FMP  /*!< Enable Fast Mode Plus on PB7       */
#endif

#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB6          SYSCFG_I2C_FMP_CTRL_I2C2_PB6_FMP /*!< Enable Fast Mode Plus on PB6       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PB7_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB7          SYSCFG_I2C_FMP_CTRL_I2C2_PB7_FMP /*!< Enable Fast Mode Plus on PB7       */
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_PWRC_IM SYSCFG Power Controller Interrupt MASK
  * @{
  */
#define LL_SYSCFG_PWRC_PVD                     SYSCFG_PWRC_IER_PVD_IE  /*!< PVD interrupt mask  */
#define LL_SYSCFG_PWRC_WKUP                    SYSCFG_PWRC_IER_WKUP_IE /*!< WKUP interrupt mask */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_RXTX_DET_TYPE SYSCFG BLE Tx/Rx sequence information detection type
  * @{
  */
#define LL_SYSCFG_BLERXTX_DET_TYPE_EDGE           ((uint8_t)0x00U) /*!<  Tx/Rx detection type EDGE  */
#define LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL          ((uint8_t)0x01U) /*!<  Tx/Rx detection type LEVEL */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_RXTX_EDGE_TRIGGER SYSCFG BLE Tx/Rx detection trigger
  * @{
  */
#define LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE     ((uint8_t)0x00U) /*!< Trigger on Rising Edge  */
#define LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE    ((uint8_t)0x01U) /*!< Trigger on Falling Edge */
#define LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE       ((uint8_t)0x02U) /*!< Trigger on Both Edge    */
#define LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL       ((uint8_t)0x03U) /*!< Trigger on Low Level    */
#define LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL      ((uint8_t)0x04U) /*!< Trigger on High Level   */

/**
  * @}
  */

/** @defgroup SYSCFG_LL_TX_RX_EVENT_ENABLE SYSCFG BLE Tx/Rx event
  * @{
  */
#define LL_SYSCFG_BLE_TX_EVENT    SYSCFG_BLERXTX_IER_TX_IE /*!< Tx Event Enable */
#define LL_SYSCFG_BLE_RX_EVENT    SYSCFG_BLERXTX_IER_RX_IE /*!< Rx Event Enable */
#if defined(SYSCFG_BLERXTX_ISCR_RX_ISEDGE)
#define LL_SYSCFG_BLE_RX_FALLING_EDGE_EVENT    (0x00000000U)                     /*!< Falling edge on RX sequence detected */
#define LL_SYSCFG_BLE_RX_RISING_EDGE_EVENT     (SYSCFG_BLERXTX_ISCR_RX_ISEDGE)   /*!< Rising edge on RX sequence detected  */
#endif
#if defined(SYSCFG_BLERXTX_ISCR_TX_ISEDGE)
#define LL_SYSCFG_BLE_TX_FALLING_EDGE_EVENT    (0x00000000U)                     /*!< Falling edge on TX sequence detected */
#define LL_SYSCFG_BLE_TX_RISING_EDGE_EVENT     (SYSCFG_BLERXTX_ISCR_TX_ISEDGE)   /*!< Rising edge on TX sequence detected  */
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_FLASH_WAIT_STATE FLASH Wait States
  * @{
  */
#define LL_FLASH_WAIT_STATES_0                 0x00000000U                          /*!< FLASH Zero wait state   */
#define LL_FLASH_WAIT_STATES_1                 FLASH_CONFIG_WAIT_STATES_0           /*!< FLASH One wait state    */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_FLASH_FLAGS FLASH Flags Definition
  * @{
  */
#define LL_FLASH_FLAG_CMDDONE             FLASH_IRQRAW_CMDDONE_RIS     /*!< FLASH command done flag      */
#define LL_FLASH_FLAG_CMDSTART            FLASH_IRQRAW_CMDSTART_RIS    /*!< FLASH command started flag   */
#define LL_FLASH_FLAG_CMDERR              FLASH_IRQRAW_CMDERR_RIS      /*!< FLASH command error flag     */
#define LL_FLASH_FLAG_ILLCMD              FLASH_IRQRAW_ILLCMD_RIS      /*!< FLASH illegal command flag   */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_FLASH_INTERRUPT FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define LL_FLASH_IT_CMDDONE                    FLASH_IRQMASK_CMDDONEM     /*!< FLASH command done Interrupt source */
#define LL_FLASH_IT_CMDSTART                   FLASH_IRQMASK_CMDSTARTM    /*!< FLASH command started Interrupt source */
#define LL_FLASH_IT_CMDERR                     FLASH_IRQMASK_CMDERRM      /*!< FLASH command error Interrupt source */
#define LL_FLASH_IT_ILLCMD                     FLASH_IRQMASK_ILLCMDM      /*!< FLASH illegal command Interrupt source */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000U                  /*!< FLASH Zero wait state  */
#define LL_FLASH_LATENCY_1                 FLASH_CONFIG_WAIT_STATES_0   /*!< FLASH One wait state when system clock frequency is 64 MHz */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_IO_DTR EXTI Lines
  * @{
  */
#define LL_EXTI_LINE_PA0                        SYSCFG_IO_DTR_PA0_DT     /*!< PA0  */
#define LL_EXTI_LINE_PA1                        SYSCFG_IO_DTR_PA1_DT     /*!< PA1  */
#define LL_EXTI_LINE_PA2                        SYSCFG_IO_DTR_PA2_DT     /*!< PA2  */
#define LL_EXTI_LINE_PA3                        SYSCFG_IO_DTR_PA3_DT     /*!< PA3  */
#if defined (STM32WB06) || defined (STM32WB07)
#define LL_EXTI_LINE_PA4                        SYSCFG_IO_DTR_PA4_DT     /*!< PA4  */
#define LL_EXTI_LINE_PA5                        SYSCFG_IO_DTR_PA5_DT     /*!< PA5  */
#define LL_EXTI_LINE_PA6                        SYSCFG_IO_DTR_PA6_DT     /*!< PA6  */
#define LL_EXTI_LINE_PA7                        SYSCFG_IO_DTR_PA7_DT     /*!< PA7  */
#endif
#define LL_EXTI_LINE_PA8                        SYSCFG_IO_DTR_PA8_DT     /*!< PA8  */
#define LL_EXTI_LINE_PA9                        SYSCFG_IO_DTR_PA9_DT     /*!< PA9  */
#define LL_EXTI_LINE_PA10                       SYSCFG_IO_DTR_PA10_DT    /*!< PA10 */
#define LL_EXTI_LINE_PA11                       SYSCFG_IO_DTR_PA11_DT    /*!< PA11 */
#if defined (STM32WB06) || defined (STM32WB07)
#define LL_EXTI_LINE_PA12                       SYSCFG_IO_DTR_PA12_DT    /*!< PA12 */
#define LL_EXTI_LINE_PA13                       SYSCFG_IO_DTR_PA13_DT    /*!< PA13 */
#define LL_EXTI_LINE_PA14                       SYSCFG_IO_DTR_PA14_DT    /*!< PA14 */
#define LL_EXTI_LINE_PA15                       SYSCFG_IO_DTR_PA15_DT    /*!< PA15 */
#endif
#define LL_EXTI_LINE_PB0                        SYSCFG_IO_DTR_PB0_DT     /*!< PB0  */
#define LL_EXTI_LINE_PB1                        SYSCFG_IO_DTR_PB1_DT     /*!< PB1  */
#define LL_EXTI_LINE_PB2                        SYSCFG_IO_DTR_PB2_DT     /*!< PB2  */
#define LL_EXTI_LINE_PB3                        SYSCFG_IO_DTR_PB3_DT     /*!< PB3  */
#define LL_EXTI_LINE_PB4                        SYSCFG_IO_DTR_PB4_DT     /*!< PB4  */
#define LL_EXTI_LINE_PB5                        SYSCFG_IO_DTR_PB5_DT     /*!< PB5  */
#define LL_EXTI_LINE_PB6                        SYSCFG_IO_DTR_PB6_DT     /*!< PB6  */
#define LL_EXTI_LINE_PB7                        SYSCFG_IO_DTR_PB7_DT     /*!< PB7  */
#if defined (STM32WB06) || defined (STM32WB07)
#define LL_EXTI_LINE_PB8                        SYSCFG_IO_DTR_PB8_DT     /*!< PB8  */
#define LL_EXTI_LINE_PB9                        SYSCFG_IO_DTR_PB9_DT     /*!< PB9  */
#define LL_EXTI_LINE_PB10                       SYSCFG_IO_DTR_PB10_DT    /*!< PB10 */
#define LL_EXTI_LINE_PB11                       SYSCFG_IO_DTR_PB11_DT    /*!< PB11 */
#endif
#define LL_EXTI_LINE_PB12                       SYSCFG_IO_DTR_PB12_DT    /*!< PB12 */
#define LL_EXTI_LINE_PB13                       SYSCFG_IO_DTR_PB13_DT    /*!< PB13 */
#define LL_EXTI_LINE_PB14                       SYSCFG_IO_DTR_PB14_DT    /*!< PB14 */
#define LL_EXTI_LINE_PB15                       SYSCFG_IO_DTR_PB15_DT    /*!< PB15 */
#define LL_EXTI_LINE_ALL                       (0xFFFFFFFFU)             /*!< All the PA0...PB15 */

#if defined(USE_FULL_LL_DRIVER)
#define LL_EXTI_LINE_NONE                      (0x00000000U)    /*!<   */
#endif /*USE_FULL_LL_DRIVER*/

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TYPE EXTI Type
  * @{
  */
#define LL_EXTI_TYPE_EDGE               ((uint8_t)0x00U) /*!<  Interrupt Type EDGE detection */
#define LL_EXTI_TYPE_LEVEL              ((uint8_t)0x01U) /*!<  Interrupt Type LEVEL detection */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TRIGGER  EXTI Edge Trigger
  * @{
  */
#define LL_EXTI_TRIGGER_NONE                 ((uint8_t)0x00U) /*!< Trigger None */
#define LL_EXTI_TRIGGER_RISING_EDGE          ((uint8_t)0x01U) /*!< Trigger Rising Edge */
#define LL_EXTI_TRIGGER_FALLING_EDGE         ((uint8_t)0x02U) /*!< Trigger Falling Edge */
#define LL_EXTI_TRIGGER_BOTH_EDGE            ((uint8_t)0x03U) /*!< Trigger Both Edge */
#define LL_EXTI_TRIGGER_LOW_LEVEL            ((uint8_t)0x04U) /*!< Trigger Low Level */
#define LL_EXTI_TRIGGER_HIGH_LEVEL           ((uint8_t)0x05U) /*!< Trigger High Level */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_DEVICE_INFORMATION Device Version Information
  * @{
  */
#define LL_BLUENRG_LP_CUT_10               0x10
#define LL_BLUENRG_LP_CUT_20               0x20

/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SYSCFG_IO_LL_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @defgroup EXTI_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SYSCFG register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_SYSCFG_WriteReg(__REG__, __VALUE__) WRITE_REG(SYSCFG->__REG__, (__VALUE__))

/**
  * @brief  Read a value in SYSCFG register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_SYSCFG_ReadReg(__REG__) READ_REG(SYSCFG->__REG__)
/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */
/** @defgroup SYSCFG_LL_EC SYSCFG exported Functions
  * @{
  */

/**
  * @brief  Get the device version and cut information.
  * @rmtoll DIE_ID PRODUCT/VERSION/REVISION   LL_SYSCFG_GetDeviceID
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceID(void)
{
  return (uint32_t)READ_REG(SYSCFG->DIE_ID);
}


/**
  * @brief  Get the device cut revision (metal fix) information.
  * @rmtoll DIE_ID REVISION   LL_SYSCFG_GetDeviceRevision
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceRevision(void)
{
  return (uint32_t)((READ_REG(SYSCFG->DIE_ID) & SYSCFG_DIE_ID_REVISION) >> SYSCFG_DIE_ID_REVISION_Pos);
}

/**
  * @brief  Get the device cut version information.
  * @rmtoll DIE_ID VERSION   LL_SYSCFG_GetDeviceVersion
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceVersion(void)
{
  return (uint32_t)((READ_REG(SYSCFG->DIE_ID) & SYSCFG_DIE_ID_VERSION) >> SYSCFG_DIE_ID_VERSION_Pos);
}

/**
  * @brief  Get the JTAG_ID device information.
  * @rmtoll JTAG_ID    LL_SYSCFG_GetDeviceJTAG_ID
  * @retval Device ID
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetDeviceJTAG_ID(void)
{
  return (uint32_t)READ_REG(SYSCFG->JTAG_ID);
}

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll CONFIG REMAP      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  * @arg LL_SYSCFG_REMAP_FLASH
  * @arg LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(FLASH->CONFIG, (FLASH_CONFIG_REMAP), Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll CONFIG REMAP      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  * @arg LL_SYSCFG_REMAP_FLASH
  * @arg LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  uint32_t remap;
  uint32_t memory_map = LL_SYSCFG_REMAP_FLASH;

  remap = READ_BIT(FLASH->CONFIG, FLASH_CONFIG_REMAP) >> FLASH_CONFIG_REMAP_Pos;

  if (remap == 1)
  {
    memory_map = LL_SYSCFG_REMAP_SRAM;
  }
  else
  {
    memory_map = LL_SYSCFG_REMAP_FLASH;
  }
  return memory_map;
}

/**
  * @brief  Enable the I2C fast mode plus driving capability.
  * @rmtoll I2C_FMP_CTRL  I2C1_PAx_FMP/I2C2_PBx_FMP   LL_SYSCFG_EnableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA0
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA1
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB10
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB11
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA6
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA7
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA13
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  * @retval None
  * @note   LL_SYSCFG_I2C_FASTMODEPLUS_PB10, LL_SYSCFG_I2C_FASTMODEPLUS_PB11, LL_SYSCFG_I2C_FASTMODEPLUS_PA6,
  *         LL_SYSCFG_I2C_FASTMODEPLUS_PA7, LL_SYSCFG_I2C_FASTMODEPLUS_PA13 and LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  */
__STATIC_INLINE void LL_SYSCFG_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  SET_BIT(SYSCFG->I2C_FMP_CTRL, ConfigFastModePlus);
}

/**
  * @brief  Disable the I2C fast mode plus driving capability.
  * @rmtoll I2C_FMP_CTRL  I2C1_PAx_FMP/I2C2_PBx_FMP   LL_SYSCFG_DisableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA0
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA1
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB10
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB11
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA6
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA7
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA13
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  * @arg LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  * @retval None
  * @note   LL_SYSCFG_I2C_FASTMODEPLUS_PB10, LL_SYSCFG_I2C_FASTMODEPLUS_PB11, LL_SYSCFG_I2C_FASTMODEPLUS_PA6,
  *         LL_SYSCFG_I2C_FASTMODEPLUS_PA7, LL_SYSCFG_I2C_FASTMODEPLUS_PA13 and LL_SYSCFG_I2C_FASTMODEPLUS_PA14
  */
__STATIC_INLINE void LL_SYSCFG_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  CLEAR_BIT(SYSCFG->I2C_FMP_CTRL, ConfigFastModePlus);
}
/**
  * @}
  */

/** @defgroup SYSTEM_LL_PWRC SYSCFG Power Functions
  * @{
  */

/**
  * @brief  Enable PWRC Interrupt Mask
  * @rmtoll PWRC_IER        LL_SYSCFG_PWRC_EnableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_PWRC_PVD
  * @arg LL_SYSCFG_PWRC_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_PWRC_EnableIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->PWRC_IER, Interrupt);
}

/**
  * @brief  Disable PWRC Interrupt Mask
  * @rmtoll PWRC_IER        LL_SYSCFG_PWRC_DisableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_PWRC_PVD
  * @arg LL_SYSCFG_PWRC_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_PWRC_DisableIT(uint32_t Interrupt)
{
  CLEAR_BIT(SYSCFG->PWRC_IER, Interrupt);
}

/**
  * @brief  Indicate if PWRC Interrupt Mask is enabled
  * @rmtoll PWRC_IER        LL_SYSCFG_PWRC_IsEnabledIT
  * @param  Interrupt This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_PWRC_PVD
  * @arg LL_SYSCFG_PWRC_WKUP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_PWRC_IsEnabledIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->PWRC_IER, Interrupt) == (Interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Get PWRC Interrupt Status
  * @rmtoll PWRC_ISCR        LL_SYSCFG_PWRC_GetStatusIT
  * @param  Interrupt This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_PWRC_PVD
  * @arg LL_SYSCFG_PWRC_WKUP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_PWRC_GetStatusIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->PWRC_ISCR, Interrupt) == (Interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Clear PWRC Interrupt Status
  * @rmtoll PWRC_ISCR        LL_SYSCFG_PWRC_ClearIT
  * @param  Interrupt This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_PWRC_PVD
  * @arg LL_SYSCFG_PWRC_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_PWRC_ClearIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->PWRC_ISCR, Interrupt);
}

/**
  * @}
  */

/** @defgroup SYSCFG_IO_LL_Exported_Functions EXTI Exported Functions
  * @{
  */
/** @defgroup EXTI_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable IO Interrupt for Lines in range PA0... PB15
  * @rmtoll IO_IER        LL_EXTI_EnableIT
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  */
__STATIC_INLINE void LL_EXTI_EnableIT(uint32_t ExtiLine)
{
  SET_BIT(SYSCFG->IO_IER, ExtiLine);
}

/**
  * @brief  Disable IO Interrupt for Lines in range PA0... PB15
  * @rmtoll IO_IER        LL_EXTI_DisableIT
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  */
__STATIC_INLINE void LL_EXTI_DisableIT(uint32_t ExtiLine)
{
  CLEAR_BIT(SYSCFG->IO_IER, ExtiLine);
}

/**
  * @brief  Indicate if IO Interrupt Mask is enabled for Lines in range PA0... PB15
  * @rmtoll IO_IER        LL_EXTI_IsEnabledIT
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval State of bit (1 or 0).
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledIT(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_IER, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_TYPE_Management Level/Edge Management
  * @{
  */

/**
  * @brief  Set IO Interrupt Type for Lines in range PA0... PB15
  * @rmtoll IO_DTR        LL_EXTI_EnableEdgeDetection
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  */
__STATIC_INLINE void LL_EXTI_EnableEdgeDetection(uint32_t ExtiLine)
{
  CLEAR_BIT(SYSCFG->IO_DTR, ExtiLine);
}

/**
  * @brief  Set IO Interrupt Type for Lines in range PA0... PB15
  * @rmtoll IO_DTR        LL_EXTI_DisableEdgeDetection
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  */
__STATIC_INLINE void LL_EXTI_DisableEdgeDetection(uint32_t ExtiLine)
{
  SET_BIT(SYSCFG->IO_DTR, ExtiLine);
}

/**
  * @brief  Get IO Interrupt Type for Lines in range PA0... PB15
  * @rmtoll IO_DTR        LL_EXTI_IsEnabledEdgeDetection
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
al One of the following values:
  *         @arg @ref LL_EXTI_TYPE_EDGE
  *         @arg @ref LL_EXTI_TYPE_LEVEL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledEdgeDetection(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_DTR, ExtiLine) == (ExtiLine)) ? 0UL : 1UL);
}
/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Trigger_EDGE_Management Trigger_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Rising Edge Trigger for Lines in range  PA0... PB15
  * @rmtoll IO_IBER                    LL_EXTI_EnableBothEdgeTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableBothEdgeTrig(uint32_t ExtiLine)
{
  SET_BIT(SYSCFG->IO_IBER, ExtiLine);
}
/**
  * @brief  Disable ExtiLine Rising Edge Trigger for Lines in range PA0... PB15
  * @rmtoll IBER                    LL_EXTI_DisableBothEdgeTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @retval None
  */

__STATIC_INLINE void LL_EXTI_DisableBothEdgeTrig(uint32_t ExtiLine)
{
  CLEAR_BIT(SYSCFG->IO_IBER, ExtiLine);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range PA0... PB15
  * @rmtoll IBER                     LL_EXTI_IsEnabledBothEdgeTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t LL_EXTI_IsEnabledBothEdgeTrig(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_IBER, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_RISING/Falling_Trigger_Management FRISING/Falling_Trigger_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Rising Edge Trigger for Lines in range PA0... PB15
  * @rmtoll IO_IEVR                    LL_EXTI_EnableRisingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableRisingTrig(uint32_t ExtiLine)
{
  SET_BIT(SYSCFG->IO_IEVR, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Rising Edge Trigger for Lines in range  PA0... PB15
  * @rmtoll IO_IEVR                    LL_EXTI_DisableRisingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableRisingTrig(uint32_t ExtiLine)
{
  CLEAR_BIT(SYSCFG->IO_IEVR, ExtiLine);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range PA0... PB15
  * @rmtoll IO_IEVR                   LL_EXTI_IsEnabledRisingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledRisingTrig(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_IEVR, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Flag_Management Flag_Management
  * @{
  */

/**
  * @brief  Check if the ExtLine Flag is set or not for Lines in range  PA0...PB15
  * @rmtoll IO_ISCR                      LL_EXTI_IsActiveFlag
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveFlag(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_ISCR, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Read ExtLine Combination Flag for Lines in range PA0...PB15
  * @rmtoll IO_ISCR                      LL_EXTI_ReadFlag
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  * @retval Flag state
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadFlag(uint32_t ExtiLine)
{
  return (uint32_t)(READ_BIT(SYSCFG->IO_ISCR, ExtiLine));
}

/**
  * @brief  Clear ExtLine Flags for Lines in range PA0...PB15
  * @rmtoll IO_ISCR                     LL_EXTI_ClearFlag
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_PA0
  *         @arg @ref LL_EXTI_LINE_PA1
  *         @arg @ref LL_EXTI_LINE_PA2
  *         @arg @ref LL_EXTI_LINE_PA3
  *         @arg @ref LL_EXTI_LINE_PA4
  *         @arg @ref LL_EXTI_LINE_PA5
  *         @arg @ref LL_EXTI_LINE_PA6
  *         @arg @ref LL_EXTI_LINE_PA7
  *         @arg @ref LL_EXTI_LINE_PA8
  *         @arg @ref LL_EXTI_LINE_PA9
  *         @arg @ref LL_EXTI_LINE_PA10
  *         @arg @ref LL_EXTI_LINE_PA11
  *         @arg @ref LL_EXTI_LINE_PA12
  *         @arg @ref LL_EXTI_LINE_PA13
  *         @arg @ref LL_EXTI_LINE_PA14
  *         @arg @ref LL_EXTI_LINE_PA15
  *         @arg @ref LL_EXTI_LINE_PB0
  *         @arg @ref LL_EXTI_LINE_PB1
  *         @arg @ref LL_EXTI_LINE_PB2
  *         @arg @ref LL_EXTI_LINE_PB3
  *         @arg @ref LL_EXTI_LINE_PB4
  *         @arg @ref LL_EXTI_LINE_PB5
  *         @arg @ref LL_EXTI_LINE_PB6
  *         @arg @ref LL_EXTI_LINE_PB7
  *         @arg @ref LL_EXTI_LINE_PB8
  *         @arg @ref LL_EXTI_LINE_PB9
  *         @arg @ref LL_EXTI_LINE_PB10
  *         @arg @ref LL_EXTI_LINE_PB11
  *         @arg @ref LL_EXTI_LINE_PB12
  *         @arg @ref LL_EXTI_LINE_PB13
  *         @arg @ref LL_EXTI_LINE_PB14
  *         @arg @ref LL_EXTI_LINE_PB15
  *         @arg @ref LL_EXTI_LINE_ALL
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WB06 and  STM32WB07
  * @note   PA0-PA3, PA8-PA11, PB0-PB7 and PB12-PB15 are valid for STM32WB05 and STM32WB09
  */
__STATIC_INLINE void LL_EXTI_ClearFlag(uint32_t ExtiLine)
{
  WRITE_REG(SYSCFG->IO_ISCR, ExtiLine);
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASH_LL_Exported_Functions FLASH Exported Functions
  * @{
  */
/** @defgroup SYSTEM_LL_EF_Configuration FLASH Configuration functions
  * @{
  */
/**
  * @brief  Enable the FLASH burst write operations.
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableBurstWrite(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CONFIG, FLASH_CONFIG_DIS_GROUP_WRITE);
}

/**
  * @brief  Disable the FLASH burst write operations.
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableBurstWrite(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CONFIG, FLASH_CONFIG_DIS_GROUP_WRITE);
}

/**
  * @brief  Set the FLASH Interrupt Vector Table location.
  * @param  FLASHx FLASH Instance
  * @param vect_table Vector Table Configuration
  *         This parameter can be one of the following values :
  *     @arg @ref LL_SYSCFG_REMAP_FLASH Vector Table located in FLASH
  *     @arg @ref LL_SYSCFG_REMAP_SRAM  Vector Table located in RAM
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetVectTable(FLASH_TypeDef *FLASHx, uint32_t vect_table)
{
  MODIFY_REG(FLASHx->CONFIG, FLASH_CONFIG_REMAP, vect_table);
}

/**
  * @brief  Get the FLASH Interrupt Vector Table location.
  * @param  FLASHx FLASH Instance
  * @retval Vector Table Configuration
  *         Returned value can be one of the following values :
  *     @arg @ref LL_SYSCFG_REMAP_FLASH Vector Table located in FLASH
  *     @arg @ref LL_SYSCFG_REMAP_SRAM  Vector Table located in RAM
  */
__STATIC_INLINE uint32_t LL_FLASH_GetVectTable(FLASH_TypeDef *FLASHx)
{
  return (uint32_t)(READ_BIT(FLASHx->CONFIG, FLASH_CONFIG_REMAP));
}
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_FLASH_Interrupt FLASH Interrupts Functions
  * @brief Functions to handle FLASH interrupts
  * @{
 */

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref LL_FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref LL_FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref LL_FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval none
  */
__STATIC_INLINE void LL_FLASH_EnableIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
  CLEAR_BIT(FLASHx->IRQMASK, interrupt);
}

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref LL_FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref LL_FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref LL-FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval none
  */
__STATIC_INLINE void LL_FLASH_DisableIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
  SET_BIT(FLASHx->IRQMASK, interrupt);
}

/**
  * @brief  Check whether the specified FLASH interrupt has occurred or not.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref LL_FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref LL_FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref LL_FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval The new state of interrupt flag (SET or RESET).
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
  return (uint32_t)((READ_BIT(FLASHx->IRQSTAT, interrupt) != RESET) ? SET : RESET);
}

/**
  * @brief  Clear the specified FLASH interrupt flag.
  * @param  FLASHx FLASH Instance
  * @param  interrupt FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_IT_CMDDONE  Command Done Interrupt
  *     @arg @ref LL_FLASH_IT_CMDSTART Command Started Interrupt
  *     @arg @ref LL_FLASH_IT_CMDERR   Command Error Interrupt
  *     @arg @ref LL_FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearIT(FLASH_TypeDef *FLASHx, uint32_t interrupt)
{
  WRITE_REG(FLASHx->IRQSTAT, interrupt);
}

/**
  * @brief  Check whether the specified FLASH flag is set or not.
  * @param  FLASHx FLASH Instance
  * @param  flag specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg @ref LL_FLASH_FLAG_CMDDONE     FLASH command done flag
  *     @arg @ref LL_FLASH_FLAG_CMDSTART    FLASH command started flag
  *     @arg @ref LL_FLASH_FLAG_CMDERR      FLASH command error flag
  *     @arg @ref LL_FLASH_FLAG_ILLCMD      FLASH illegal command flag
  * @retval The new state of FLASH flag (SET or RESET).
  */
__STATIC_INLINE uint32_t LL_FLASH_GetFlag(FLASH_TypeDef *FLASHx, uint32_t flag)
{
  return (uint32_t)((READ_BIT(FLASHx->IRQRAW, flag) == flag) ? 1UL : 0UL);
}

/**
  * @brief  Clear the FLASH's pending flags.
  * @param  FLASHx FLASH Instance
  * @param  flag specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg @ref LL_FLASH_FLAG_CMDDONE     FLASH command done flag
  *     @arg @ref LL_FLASH_FLAG_CMDSTART    FLASH command started flag
  *     @arg @ref LL_FLASH_FLAG_CMDERR      FLASH command error flag
  *     @arg @ref LL_FLASH_FLAG_ILLCMD      FLASH illegal command flag
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag(FLASH_TypeDef *FLASHx, uint32_t flag)
{
  WRITE_REG(FLASHx->IRQRAW, flag);
}

/**
  * @}
  */

/** @defgroup FLASH_Security FLASH Security Functions
  *  @brief Functions to read FLASH security applied
  * @{
  */

/**
  * @brief  Check if FLASH & RAM SWD access is disabled
  * @rmtoll SIZE           SWD_DISABLE  LL_FLASH_SWD_Access_IsDisabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_SWD_Access_IsDisabled(void)
{
  return ((READ_BIT(FLASH->SIZE, FLASH_FLASH_SIZE_SWD_DISABLE) == (FLASH_FLASH_SIZE_SWD_DISABLE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if FLASH Readout Protection is enabled
  * @rmtoll SIZE           FLASH_SECURE  LL_FLASH_ReadoutProtection_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadoutProtection_IsEnabled(void)
{
  return ((READ_BIT(FLASH->SIZE, FLASH_FLASH_SIZE_FLASH_SECURE) == (FLASH_FLASH_SIZE_FLASH_SECURE)) ? 1UL : 0UL);
}

/**
  * @}
  */


/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_CONFIG    WAIT_STATE      LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  * @arg LL_FLASH_LATENCY_0
  * @arg LL_FLASH_LATENCY_1
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->CONFIG, FLASH_CONFIG_WAIT_STATES, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_CONFIG    WAIT_STATE     LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  * @arg LL_FLASH_LATENCY_0
  * @arg LL_FLASH_LATENCY_1
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->CONFIG, FLASH_CONFIG_WAIT_STATES));
}

/**
  * @}
  */
/**
  * @}
  */

/** @defgroup SYSCFG_BLE_LL_Exported_Functions SYSCFG BLE Exported Functions
  * @{
  */
/** @defgroup SYSCFG_LL_RADIO_RXTX_IT_Management RX TX IT_Management
  * @{
  */
/**
  * @brief  Enable Tx Rx Interrupt
  * @rmtoll BLERXTX_IER        LL_SYSCFG_BLERXTX_EnableIT
  * @param  Signal This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_EnableIT(uint32_t Signal)
{
  SET_BIT(SYSCFG->BLERXTX_IER, Signal);
}

/**
  * @brief  Disable Tx Rx Interrupt
  * @rmtoll BLERXTX_IER        LL_SYSCFG_BLERXTX_DisableIT
  * @param  Signal This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_DisableIT(uint32_t Signal)
{
  CLEAR_BIT(SYSCFG->BLERXTX_IER, Signal);
}

/**
  * @brief  Indicate if Tx Rx Interrupt is enabled
  * @rmtoll BLERXTX_IER        LL_SYSCFG_BLERXTX_IsEnabledIT
  * @param  Signal This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERXTX_IsEnabledIT(uint32_t Signal)
{
  return ((READ_BIT(SYSCFG->BLERXTX_IER, Signal) == (Signal)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SYSCFG_LL_RADIO_EVENT_TYPE_Management Level-Edge Management
  * @{
  */
/**
  * @brief  Set Tx-Rx Interrupt Detection Type
  * @rmtoll BLERXTX_DTR        LL_SYSCFG_BLERXTX_SetType
  * @param  Type This parameter can be one of the following values:
  * @arg LL_SYSCFG_BLERXTX_DET_TYPE_EDGE
  * @arg LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL
  * @param  Signal This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_SetType(uint8_t Type, uint32_t Signal)
{
  if (Type == LL_SYSCFG_BLERXTX_DET_TYPE_EDGE)
  {
    CLEAR_BIT(SYSCFG->BLERXTX_DTR, Signal);
  }
  else
  {
    SET_BIT(SYSCFG->BLERXTX_DTR, Signal);
  }
}

/**
  * @brief  Get Tx-Rx Interrupt Detection Type
  * @rmtoll BLERXTX_DTR        LL_SYSCFG_BLERXTX_GetType
  * @param  Signal This parameter one of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval One of the following values:
  * @arg LL_SYSCFG_BLERXTX_DET_TYPE_EDGE
  * @arg LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERXTX_GetType(uint32_t Signal)
{
  if (READ_BIT(SYSCFG->BLERXTX_DTR, Signal))
  {
    return LL_SYSCFG_BLERXTX_DET_TYPE_LEVEL;
  }

  return LL_SYSCFG_BLERXTX_DET_TYPE_EDGE;
}

/**
  * @}
  */

/** @defgroup LL_SYSCFG_BLERXTX_Trigger Trigger Management
  * @{
  */
/**
  * @brief  Set Tx Rx Interrupt Trigger
  * @rmtoll BLERXTX_IBER/BLERXTX__IEVR/BLERXTX__DTR        LL_SYSCFG_BLERXTX_SetTrigger
  * @param  Trigger This parameter can be one of the following values:
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL
  * @param  Signal This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_SetTrigger(uint8_t Trigger, uint32_t Signal)
{
  switch (Trigger)
  {
    case LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE:
    {
      SET_BIT(SYSCFG->BLERXTX_IBER, Signal);
      CLEAR_BIT(SYSCFG->BLERXTX_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE:
    {
      CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
      SET_BIT(SYSCFG->BLERXTX_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE:
    {
      CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
      CLEAR_BIT(SYSCFG->BLERXTX_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL:
    {
      CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
      CLEAR_BIT(SYSCFG->BLERXTX_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL:
    {
      CLEAR_BIT(SYSCFG->BLERXTX_IBER, Signal);
      SET_BIT(SYSCFG->BLERXTX_IEVR, Signal);
    }
  }
}

/**
  * @brief  Get Tx Rx Interrupt Trigger
  * @rmtoll BLERXTX_IBER/BLERXTX_IEVR/BLERXTX_DTR        LL_SYSCFG_BLERXTX_GetTrigger
  * @param  Signal This parameter can be one of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval The return value can be one of the following values:
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL
  * @arg LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL
  */
__STATIC_INLINE uint8_t LL_SYSCFG_BLERXTX_GetTrigger(uint32_t Signal)
{
  uint32_t level_setup, level_edge, both_edge;

  level_setup = READ_BIT(SYSCFG->BLERXTX_DTR, Signal);
  level_edge = READ_BIT(SYSCFG->BLERXTX_IEVR, Signal);
  both_edge = READ_BIT(SYSCFG->BLERXTX_IBER, Signal);

  if (level_setup)
  {
    if (level_edge)
    {
      return LL_SYSCFG_BLERXTX_TRIGGER_HIGH_LEVEL;
    }
    else
    {
      return LL_SYSCFG_BLERXTX_TRIGGER_LOW_LEVEL;
    }
  }
  else
  {
    if (both_edge)
    {
      return LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE;
    }
    if (level_edge)
    {
      return LL_SYSCFG_BLERXTX_TRIGGER_RISING_EDGE;
    }
  }
  return LL_SYSCFG_BLERXTX_TRIGGER_FALLING_EDGE;
}

/**
  * @}
  */

/** @defgroup SYSCFG_LL_EVENT_Flag_Management Flag Management
  * @{
  */
/**
  * @brief Check if the Tx Rx Interrupt is set or not
  * @note  This bit is cleared by writing a 1 to the bit.
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLERXTX_IsInterruptPending
  * @param  Signal This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERXTX_IsInterruptPending(uint32_t Signal)
{
  return ((READ_BIT(SYSCFG->BLERXTX_ISCR, Signal) == (Signal)) ? 1UL : 0UL);
}


/**
  * @brief Clear the Tx Rx Interrupt
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLERXTX_ClearInterrupt
  * @param  Signal This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_BLE_TX_EVENT
  * @arg LL_SYSCFG_BLE_RX_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_BLERXTX_ClearInterrupt(uint32_t Signal)
{
  WRITE_REG(SYSCFG->BLERXTX_ISCR, Signal);
}


#if defined(SYSCFG_BLERXTX_ISCR_TX_ISEDGE)
/**
  * @brief Returns the TX interrupt edge status on a TX sequence event
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLETX_EdgeSequence
  * @retval  The return value can be one of the following values:
  * @arg LL_SYSCFG_BLE_TX_FALLING_EDGE_EVENT
  * @arg LL_SYSCFG_BLE_TX_RISING_EDGE_EVENT
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLETX_EdgeSequence(void)
{
  return READ_BIT(SYSCFG->BLERXTX_ISCR, SYSCFG_BLERXTX_ISCR_TX_ISEDGE);
}
#endif


#if defined(SYSCFG_BLERXTX_ISCR_RX_ISEDGE)
/**
  * @brief Returns the RX interrupt edge status on a RX sequence event
  * @rmtoll BLERXTX_ISCR                   LL_SYSCFG_BLERX_EdgeSequence
  * @retval  The return value can be one of the following values:
  * @arg LL_SYSCFG_BLE_RX_FALLING_EDGE_EVENT
  * @arg LL_SYSCFG_BLE_RX_RISING_EDGE_EVENT
  */
__STATIC_INLINE uint32_t LL_SYSCFG_BLERX_EdgeSequence(void)
{
  return READ_BIT(SYSCFG->BLERXTX_ISCR, SYSCFG_BLERXTX_ISCR_RX_ISEDGE);
}
#endif


/**
  * @}
  */
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup SYSCFG_IO_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_SYSCFG_IO_Init(LL_SYSCFG_IO_InitTypeDef *SYSCFG_IO_InitStruct);
ErrorStatus LL_SYSCFG_IO_DeInit(void);
void LL_SYSCFG_IO_StructInit(LL_SYSCFG_IO_InitTypeDef *SYSCFG_IO_InitStruct);

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

#endif /* defined (FLASH) || defined (SYSCFG) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WB0x_LL_SYSTEM_H */
