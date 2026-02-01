/**
  ******************************************************************************
  * @file    stm32wl3x_ll_system.h
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
#ifndef STM32WL3x_LL_SYSTEM_H
#define STM32WL3x_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x.h"

/** @addtogroup STM32WL3x_LL_Driver
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
/** @defgroup SYSCFG_IO_LL_ES_INIT SYSTEM Exported Init structure
  * @{
  */
typedef struct
{

  uint32_t Line;                 /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range PA0 to PB15
                                      This parameter can be any combination of @ref EXTI_LL_EC_LINE */

  FunctionalState LineCommand;  /*!< Specifies the new state of the selected EXTI lines.
                                     This parameter can be set either to ENABLE or DISABLE */

  uint8_t Type;                 /*!< Specifies the type for the EXTI lines EDGE or LEVEL.
                                     This parameter can be a value of @ref SYSTEM_LL_EC_TYPE. */

  uint8_t Trigger;              /*!< Specifies the trigger signal active edge/level for the EXTI lines.
                                     This parameter can be a value of @ref SYSTEM_LL_EC_TRIGGER. */
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
#define LL_SYSCFG_REMAP_SRAM                    FLASH_CONFIG_REMAP                  /*!< SRAM mapped at 0x00000000               */
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
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB10_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB10         SYSCFG_I2C_FMP_CTRL_I2C1_PB10_FMP /*!< Enable Fast Mode Plus on PB10      */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C1_PB11_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB11         SYSCFG_I2C_FMP_CTRL_I2C1_PB11_FMP /*!< Enable Fast Mode Plus on PB11      */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA6_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA6          SYSCFG_I2C_FMP_CTRL_I2C2_PA6_FMP  /*!< Enable Fast Mode Plus on PA6       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA7_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA7          SYSCFG_I2C_FMP_CTRL_I2C2_PA7_FMP  /*!< Enable Fast Mode Plus on PA7       */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA13_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA13         SYSCFG_I2C_FMP_CTRL_I2C2_PA13_FMP /*!< Enable Fast Mode Plus on PA13      */
#endif
#if defined(SYSCFG_I2C_FMP_CTRL_I2C2_PA14_FMP)
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA14         SYSCFG_I2C_FMP_CTRL_I2C2_PA14_FMP /*!< Enable Fast Mode Plus on PA14      */
#endif
/**
  * @}
  */
/** @defgroup SYSTEM_LL_PWRC_IM SYSCFG Power Controller Interrupt MASK
  * @{
  */
#define LL_SYSCFG_PWRC_PVD                     SYSCFG_PWRC_IER_PVD_IE  /*!< PVD interrupt mask  */
#define LL_SYSCFG_PWRC_WKUP                    SYSCFG_PWRC_IER_WKUP_IE /*!< WKUP interrupt mask */
#define LL_SYSCFG_PWRC_BORH                    SYSCFG_PWRC_IER_BORH_IE /*!< BORH interrupt mask */
/**
  * @}
  */

/** @defgroup SYSCFG_IO_LL_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_LL_EC_LINE LINE
  * @{
  */
#define LL_EXTI_LINE_PA0        (uint32_t)(1U << 0U)    /*!< PA0  */
#define LL_EXTI_LINE_PA1        (uint32_t)(1U << 1U)    /*!< PA1  */
#define LL_EXTI_LINE_PA2        (uint32_t)(1U << 2U)    /*!< PA2  */
#define LL_EXTI_LINE_PA3        (uint32_t)(1U << 3U)    /*!< PA3  */
#define LL_EXTI_LINE_PA4        (uint32_t)(1U << 4U)    /*!< PA4  */
#define LL_EXTI_LINE_PA5        (uint32_t)(1U << 5U)    /*!< PA5  */
#define LL_EXTI_LINE_PA6        (uint32_t)(1U << 6U)    /*!< PA6  */
#define LL_EXTI_LINE_PA7        (uint32_t)(1U << 7U)    /*!< PA7  */
#define LL_EXTI_LINE_PA8        (uint32_t)(1U << 8U)    /*!< PA8  */
#define LL_EXTI_LINE_PA9        (uint32_t)(1U << 9U)    /*!< PA9  */
#define LL_EXTI_LINE_PA10       (uint32_t)(1U << 10U)   /*!< PA10 */
#define LL_EXTI_LINE_PA11       (uint32_t)(1U << 11U)   /*!< PA11 */
#define LL_EXTI_LINE_PA12       (uint32_t)(1U << 12U)   /*!< PA12 */
#define LL_EXTI_LINE_PA13       (uint32_t)(1U << 13U)   /*!< PA13 */
#define LL_EXTI_LINE_PA14       (uint32_t)(1U << 14U)   /*!< PA14 */
#define LL_EXTI_LINE_PA15       (uint32_t)(1U << 15U)   /*!< PA15 */
#define LL_EXTI_LINE_PB0        (uint32_t)(1U << 16U)   /*!< PB0  */
#define LL_EXTI_LINE_PB1        (uint32_t)(1U << 17U)   /*!< PB1  */
#define LL_EXTI_LINE_PB2        (uint32_t)(1U << 18U)   /*!< PB2  */
#define LL_EXTI_LINE_PB3        (uint32_t)(1U << 19U)   /*!< PB3  */
#define LL_EXTI_LINE_PB4        (uint32_t)(1U << 20U)   /*!< PB4  */
#define LL_EXTI_LINE_PB5        (uint32_t)(1U << 21U)   /*!< PB5  */
#define LL_EXTI_LINE_PB6        (uint32_t)(1U << 22U)   /*!< PB6  */
#define LL_EXTI_LINE_PB7        (uint32_t)(1U << 23U)   /*!< PB7  */
#define LL_EXTI_LINE_PB8        (uint32_t)(1U << 24U)   /*!< PB8  */
#define LL_EXTI_LINE_PB9        (uint32_t)(1U << 25U)   /*!< PB9  */
#define LL_EXTI_LINE_PB10       (uint32_t)(1U << 26U)   /*!< PB10 */
#define LL_EXTI_LINE_PB11       (uint32_t)(1U << 27U)   /*!< PB11 */
#define LL_EXTI_LINE_PB12       (uint32_t)(1U << 28U)   /*!< PB12 */
#define LL_EXTI_LINE_PB13       (uint32_t)(1U << 29U)   /*!< PB13 */
#define LL_EXTI_LINE_PB14       (uint32_t)(1U << 30U)   /*!< PB14 */
#define LL_EXTI_LINE_PB15       (uint32_t)(1U << 31U)   /*!< PB15 */
#define LL_EXTI_LINE_ALL        (uint32_t)(0xFFFFFFFFU) /*!< All the EXTI lines PA0...PB15 */

#if defined(USE_FULL_LL_DRIVER)
#define LL_EXTI_LINE_NONE              (0x00000000U)    /*!< None Extended line */
#endif /*USE_FULL_LL_DRIVER*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TYPE Type
  * @{
  */
#define LL_EXTI_TYPE_EDGE               ((uint8_t)0x00U) /*!<  Interrupt Type EDGE detection */
#define LL_EXTI_TYPE_LEVEL              ((uint8_t)0x01U) /*!<  Interrupt Type LEVEL detection */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TRIGGER Edge Trigger
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


/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_WAIT_STATES_0                 0x00000000U                  /*!< FLASH Zero wait state  */
#define LL_FLASH_WAIT_STATES_1                 FLASH_CONFIG_WAIT_STATES_0   /*!< FLASH One wait state when system clock frequency is 64 MHz */
#define LL_FLASH_LATENCY_0                     0x00000000U                  /*!< FLASH Zero wait state  */
#define LL_FLASH_LATENCY_1                     FLASH_CONFIG_WAIT_STATES_0   /*!< FLASH One wait state when system clock frequency is 64 MHz */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_DEVICE_INFORMATION Device Version Information
  * @{
  */
#if defined (MR_SUBG)
#define LL_SPIRIT3_CUT_10                  0x10
#endif
/**
  * @}
  */


/** @defgroup SYSTEM_LL_IO_ANALOG_SWITCH IO GPIOB14 analog configuration
  * @{
  */
#define LL_SYSCFG_PB14_PVD      0x00000000U                      /*!< PVD external voltage feature is selected */
#define LL_SYSCFG_PB14_ATB1     SYSCFG_GPIO_SWA_CTRL_ATB1_nPVD   /*!< ATB1 feature is selected                 */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB0_STOP_IP DBGMCU APB0 _GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB0_GRP1_TIM2_STOP      DBGMCU_DBG_APB0_FZ_DBG_TIM2_STOP   /*!< The counter clock of TIM2 is stopped when the core is halted              */
#define LL_DBGMCU_APB0_GRP1_TIM16_STOP     DBGMCU_DBG_APB0_FZ_DBG_TIM16_STOP   /*!< The counter clock of TIM16 is stopped when the core is halted              */
#define LL_DBGMCU_APB0_GRP1_RTC_STOP       DBGMCU_DBG_APB0_FZ_DBG_RTC_STOP    /*!< The clock of the RTC counter is stopped when the core is halted           */
#define LL_DBGMCU_APB0_GRP1_IWDG_STOP      DBGMCU_DBG_APB0_FZ_DBG_IWDG_STOP   /*!< The independent watchdog counter clock is stopped when the core is halted */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_STOP_IP DBGMCU APB1 _GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_I2C1_STOP      DBGMCU_DBG_APB1_FZ_DBG_I2C1_STOP   /*!< The counter clock of I2C1 is stopped when the core is halted              */
#define LL_DBGMCU_APB1_GRP1_I2C2_STOP      DBGMCU_DBG_APB1_FZ_DBG_I2C2_STOP  /*!< The counter clock of I2C2 is stopped when the core is halted             */

/**
  * @}
  */

/** @defgroup SYSCFG_LL_RXTX_DET_TYPE Tx/Rx sequence information detection type
  * @{
  */
#define LL_SYSCFG_MR_SUBG_DET_TYPE_EDGE           ((uint8_t)0x00U) /*!<  Tx/Rx, COMP_OUT and RF_IP_BUSY_STATUS detection type EDGE  */
#define LL_SYSCFG_MR_SUBG_DET_TYPE_LEVEL          ((uint8_t)0x01U) /*!<  Tx/Rx, COMP_OUT and RF_IP_BUSY_STATUS detection type LEVEL */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_RXTX_EDGE_TRIGGER Tx/Rx detection trigger
  * @{
  */
#define LL_SYSCFG_MR_SUBG_TRIGGER_RISING_EDGE     ((uint8_t)0x00U) /*!< Trigger on Rising Edge  */
#define LL_SYSCFG_MR_SUBG_TRIGGER_FALLING_EDGE    ((uint8_t)0x01U) /*!< Trigger on Falling Edge */
#define LL_SYSCFG_MR_SUBG_TRIGGER_BOTH_EDGE       ((uint8_t)0x02U) /*!< Trigger on Both Edge    */
#define LL_SYSCFG_MR_SUBG_TRIGGER_LOW_LEVEL       ((uint8_t)0x03U) /*!< Trigger on Low Level    */
#define LL_SYSCFG_MR_SUBG_TRIGGER_HIGH_LEVEL      ((uint8_t)0x04U) /*!< Trigger on High Level   */
/**
  * @}
  */

/** @defgroup SYSCFG_LL_TX_RX_EVENT_ENABLE Tx/Rx event
  * @{
  */
#define LL_SYSCFG_MR_SUBG_TX_EVENT               SYSCFG_INTAI_IER_TX_IE                /*!< Tx Event Enable               */
#define LL_SYSCFG_MR_SUBG_RX_EVENT               SYSCFG_INTAI_IER_RX_IE                /*!< Rx Event Enable               */
#define LL_SYSCFG_MR_SUBG_COMPOUT_EVENT          SYSCFG_INTAI_IER_COMP_IE              /*!< COMP_OUT Event Enable         */
#define LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT        SYSCFG_INTAI_IER_RFIP_BUSY_STATUS_IE  /*!< RFIP_BUSY_STATUS Event Enable */
#define LL_SYSCFG_LCSC_LC_ACTIVITY_ISC           SYSCFG_INTAI_ISCR_LC_ACTIVITY_ISC     /*!< Edge status on LC_ACTIVITY signal Event Enable */
#define LL_SYSCFG_LCSC_LC_ACTIVITY_ISEDGE        SYSCFG_INTAI_ISCR_LC_ACTIVITY_ISEDGE  /*!< Status on LC_ACTIVITY Event Enable */
#define LL_SYSCFG_LCSC_LC_ACTIVITY_FALLING_EDGE  (0U)                                  /*!< Falling Edge LC_ACTIVITY Event */
#define LL_SYSCFG_LCSC_LC_ACTIVITY_RISING_EDGE   (1U)                                  /*!< Rising Edge LC_ACTIVITY Event */
#define LL_SYSCFG_LCSC_IBER_SINGLE               (0U)                                  /*!< Detection on single edge */
#define LL_SYSCFG_LCSC_IBER_BOTH                 (SYSCFG_INTAI_IBER_LC_ACTIVITY_IBE)   /*!< Detection on both edges */
#define LL_SYSCFG_LCSC_IEVR_FALLING              (0U)                                  /*!< Detection on falling edge / low level */
#define LL_SYSCFG_LCSC_IEVR_RISING               (SYSCFG_INTAI_IEVR_LC_ACTIVITY_IEV)   /*!< Detection on rising edge / high level */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SYSCFG_IO_LL_Exported_Macros SYSTEM Exported Macros
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
/** @defgroup SYSCFG_LL_Exported_Functions SYSCFG Exported Functions
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
  */
__STATIC_INLINE void LL_EXTI_DisableIT(uint32_t ExtiLine)
{
  CLEAR_BIT(SYSCFG->IO_IER, ExtiLine);
}

/**
  * @brief  Indicate if IO Interrupt Mask is enabled
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
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledIT(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_IER, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */
/** @defgroup EXTI_LL_EF_TYPE_Management Level Edge Management
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledEdgeDetection(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_DTR, ExtiLine) == (ExtiLine)) ? 0UL : 1UL);
}
/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Trigger_EDGE_Management Trigger Management
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
  * @retval State of bit (1 or 0).
  */

__STATIC_INLINE uint32_t LL_EXTI_IsEnabledBothEdgeTrig(uint32_t ExtiLine)
{
  return ((READ_BIT(SYSCFG->IO_IBER, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */


/** @defgroup EXTI_LL_EF_RISING/Falling_Trigger_Management RISING Falling Trigger Management
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @retval None
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
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
  * @note   PA0-PA15 and PB0-PB15 are valid for STM32WL33
  */
__STATIC_INLINE void LL_EXTI_ClearFlag(uint32_t ExtiLine)
{
  WRITE_REG(SYSCFG->IO_ISCR, ExtiLine);
}

/**
  * @}
  */
/** @defgroup SYSTEM_LL_PWRC SYSCFG
  * @{
  */

/**
  * @brief  Enable PWRC Interrupt Mask
  * @rmtoll PWRC_IER        LL_SYSCFG_PWRC_EnableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  * @arg LL_SYSCFG_PWRC_PVD
  * @arg LL_SYSCFG_PWRC_WKUP
  * @arg LL_SYSCFG_PWRC_BORH
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
  * @arg LL_SYSCFG_PWRC_BORH
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
  * @arg LL_SYSCFG_PWRC_BORH
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
  * @arg LL_SYSCFG_PWRC_BORH
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
  * @arg LL_SYSCFG_PWRC_BORH
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_PWRC_ClearIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->PWRC_ISCR, Interrupt);
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH wait_states
  * @rmtoll FLASH_CONFIG    Latency      LL_FLASH_SetLatency
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

/** @defgroup SYSCFG_LL_RADIO_EVENT_TYPE_Management Level/Edge Management
  * @{
  */

/**
  * @brief  Enable Internal asynchronous Interrupt
  * @rmtoll INTAI_IER        LL_SYSCFG_MR_SUBG_INTAI_EnableIT
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_MR_SUBG_INTAI_EnableIT(uint32_t Signal)
{
  SET_BIT(SYSCFG->INTAI_IER, Signal);
}

/**
  * @brief  Disable Internal asynchronous Interrupt
  * @rmtoll INTAI_IER        LL_SYSCFG_MR_SUBG_INTAI_DisableIT
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_MR_SUBG_INTAI_DisableIT(uint32_t Signal)
{
  CLEAR_BIT(SYSCFG->INTAI_IER, Signal);
}

/**
  * @brief  Indicate if Internal asynchronous Interrupt is enabled
  * @rmtoll INTAI_IER        LL_SYSCFG_MR_SUBG_INTAI_IsEnabledIT
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_MR_SUBG_INTAI_IsEnabledIT(uint32_t Signal)
{
  return ((READ_BIT(SYSCFG->INTAI_IER, Signal) == (Signal)) ? 1UL : 0UL);
}


/**
  * @brief  Set Internal asynchronous Interrupt Detection Type
  * @rmtoll INTAI_DTR        LL_SYSCFG_MR_SUBG_INTAI_SetType
  * @param  Type This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_DET_TYPE_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_DET_TYPE_LEVEL
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_MR_SUBG_INTAI_SetType(uint8_t Type, uint32_t Signal)
{
  if (Type == LL_SYSCFG_MR_SUBG_DET_TYPE_EDGE)
  {
    CLEAR_BIT(SYSCFG->INTAI_DTR, Signal);
  }
  else
  {
    SET_BIT(SYSCFG->INTAI_DTR, Signal);
  }
}

/**
  * @brief  Get Internal asynchronous Interrupt Detection Type
  * @rmtoll INTAI_DTR        LL_SYSCFG_MR_SUBG_INTAI_GetType
  * @param  Signal This parameter one of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval One of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_DET_TYPE_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_DET_TYPE_LEVEL
  */
__STATIC_INLINE uint32_t LL_SYSCFG_MR_SUBG_INTAI_GetType(uint32_t Signal)
{
  if (READ_BIT(SYSCFG->INTAI_DTR, Signal))
  {
    return LL_SYSCFG_MR_SUBG_DET_TYPE_LEVEL;
  }

  return LL_SYSCFG_MR_SUBG_DET_TYPE_EDGE;
}

/**
  * @}
  */

/** @defgroup SYSCFG_LL_EF_Trigger_Management Trigger_Management
  * @{
  */

/**
  * @brief  Set Internal asynchronous Interrupt Trigger
  * @rmtoll INTAI_IBER/INTAI_IEVR/INTAI_DTR        LL_SYSCFG_MR_SUBG_INTAI_SetTrigger
  * @param  Trigger This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_RISING_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_FALLING_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_BOTH_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_LOW_LEVEL
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_HIGH_LEVEL
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_MR_SUBG_INTAI_SetTrigger(uint8_t Trigger, uint32_t Signal)
{
  switch (Trigger)
  {
    case LL_SYSCFG_MR_SUBG_TRIGGER_BOTH_EDGE:
    {
      SET_BIT(SYSCFG->INTAI_IBER, Signal);
      CLEAR_BIT(SYSCFG->INTAI_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_MR_SUBG_TRIGGER_RISING_EDGE:
    {
      CLEAR_BIT(SYSCFG->INTAI_IBER, Signal);
      SET_BIT(SYSCFG->INTAI_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_MR_SUBG_TRIGGER_FALLING_EDGE:
    {
      CLEAR_BIT(SYSCFG->INTAI_IBER, Signal);
      CLEAR_BIT(SYSCFG->INTAI_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_MR_SUBG_TRIGGER_LOW_LEVEL:
    {
      CLEAR_BIT(SYSCFG->INTAI_IBER, Signal);
      CLEAR_BIT(SYSCFG->INTAI_IEVR, Signal);
      break;
    }
    case LL_SYSCFG_MR_SUBG_TRIGGER_HIGH_LEVEL:
    {
      CLEAR_BIT(SYSCFG->INTAI_IBER, Signal);
      SET_BIT(SYSCFG->INTAI_IEVR, Signal);
      break;
    }
  }
}

/**
  * @brief  Get Internal asynchronous Interrupt Trigger
  * @rmtoll INTAI_IBER/INTAI_IEVR/INTAI_DTR        LL_SYSCFG_MR_SUBG_INTAI_GetTrigger
  * @param  Signal This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval The return value can be one of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_RISING_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_FALLING_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_BOTH_EDGE
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_LOW_LEVEL
  *         @arg @ref LL_SYSCFG_MR_SUBG_TRIGGER_HIGH_LEVEL
  */
__STATIC_INLINE uint8_t LL_SYSCFG_MR_SUBG_INTAI_GetTrigger(uint32_t Signal)
{
  uint32_t level_setup, level_edge, both_edge;

  level_setup = READ_BIT(SYSCFG->INTAI_DTR, Signal);
  level_edge = READ_BIT(SYSCFG->INTAI_IEVR, Signal);
  both_edge = READ_BIT(SYSCFG->INTAI_IBER, Signal);

  if (level_setup)
  {
    if (level_edge)
    {
      return LL_SYSCFG_MR_SUBG_TRIGGER_HIGH_LEVEL;
    }
    else
    {
      return LL_SYSCFG_MR_SUBG_TRIGGER_LOW_LEVEL;
    }
  }
  else
  {
    if (both_edge)
    {
      return LL_SYSCFG_MR_SUBG_TRIGGER_BOTH_EDGE;
    }
    if (level_edge)
    {
      return LL_SYSCFG_MR_SUBG_TRIGGER_RISING_EDGE;
    }
  }
  return LL_SYSCFG_MR_SUBG_TRIGGER_FALLING_EDGE;
}


/**
  * @brief Check if the Internal asynchronous Interrupt is set or not
  * @note  This bit is cleared by writing a 1 to the bit.
  * @rmtoll INTAI_ISCR                   LL_SYSCFG_MR_SUBG_INTAI_IsInterruptPending
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_MR_SUBG_INTAI_IsInterruptPending(uint32_t Signal)
{
  return ((READ_BIT(SYSCFG->INTAI_ISCR, Signal) == (Signal)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the Internal asynchronous Interrupt
  * @rmtoll INTAI_ISCR                   LL_SYSCFG_MR_SUBG_INTAI_ClearInterrupt
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MR_SUBG_TX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RX_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_COMPOUT_EVENT
  *         @arg @ref LL_SYSCFG_MR_SUBG_RFIP_BUSY_EVENT
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_MR_SUBG_INTAI_ClearInterrupt(uint32_t Signal)
{
  WRITE_REG(SYSCFG->INTAI_ISCR, Signal);
}

/**
  * @brief   Set interrupt edge register on LC_ACTIVITY signal detection on single or both edges.
  * @rmtoll INTAI_IBER                   LL_SYSCFG_LCSC_INTAI_IBER_Edge_Detection
  * @param  Value This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_LCSC_IBER_SINGLE
  *         @arg @ref LL_SYSCFG_LCSC_IBER_BOTH
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_LCSC_INTAI_IBER_Edge_Detection(uint32_t Value)
{
  MODIFY_REG(SYSCFG->INTAI_IBER, SYSCFG_INTAI_IBER_LC_ACTIVITY_IBE, Value);
}



/**
  * @brief  Check if the Internal asynchronous Interrupt is set or not
  * @note   This bit is cleared by writing a 1 to the bit.
  * @rmtoll INTAI_ISCR                   LL_SYSCFG_LCSC_INTAI_IsInterruptPending
  * @param  Value This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_LCSC_LC_ACTIVITY_ISC
  *         @arg @ref LL_SYSCFG_LCSC_LC_ACTIVITY_ISEDGE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_LCSC_INTAI_IsInterruptPending(uint32_t Value)
{
  return ((READ_BIT(SYSCFG->INTAI_ISCR, Value) == (Value)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the Internal asynchronous Interrupt
  * @rmtoll INTAI_ISCR                   LL_SYSCFG_LCSC_INTAI_ClearInterrupt
  * @param  Signal This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_LCSC_LC_ACTIVITY_ISC
  *         @arg @ref LL_SYSCFG_LCSC_LC_ACTIVITY_ISEDGE
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_LCSC_INTAI_ClearInterrupt(uint32_t Signal)
{
  WRITE_REG(SYSCFG->INTAI_ISCR, Signal);
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_ANALOG_SWITCH Analog source selection to connect on analog pads
  * @{
  */
/**
  * @brief  Setup analog feature on PB14 between ATB1 and PVD when the PB14 I/O
  *         is programmed in analog mode
  * @rmtoll GPIO_SWA_CTRL    ATB1_nPVD   LL_IO_AnalogSwitchControl_PB14
  * @param  feature this parameter can be one of the following values:
  * @arg LL_SYSCFG_PB14_PVD
  * @arg LL_SYSCFG_PB14_ATB1
  * @retval None
  */
__STATIC_INLINE void LL_IO_SetAnalogSwitchControl_PB14(uint32_t feature)
{
  MODIFY_REG(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_ATB1_nPVD, feature);
}

/**
  * @brief  Setup analog feature on PB14 between ATB1 and PVD when the PB14 I/O
  *         is programmed in analog mode
  * @rmtoll GPIO_SWA_CTRL    ATB1_nPVD   LL_IO_AnalogSwitchControl_PB14
  * @retval The return value can be one of the following values:
  * @arg LL_SYSCFG_PB14_PVD
  * @arg LL_SYSCFG_PB14_ATB1
  */
__STATIC_INLINE uint32_t LL_IO_GetAnalogSwitchControl_PB14(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->GPIO_SWA_CTRL, SYSCFG_GPIO_SWA_CTRL_ATB1_nPVD));
}

/**
  * @brief  Set the interrupt polarity event on LC_ACTIVITY signal detection on falling edge / low level or on rising edge / high level
  * @rmtoll INTAI_IEVR                   LL_SYSCFG_LCSC_INTAI_IEVR_Polarity
  * @param  Value This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_LCSC_IEVR_FALLING
  *         @arg @ref LL_SYSCFG_LCSC_IEVR_RISING
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_LCSC_INTAI_IEVR_Polarity(uint32_t Value)
{
  MODIFY_REG(SYSCFG->INTAI_IEVR, SYSCFG_INTAI_IEVR_LC_ACTIVITY_IEV, Value);
}

/**
  * @brief  Check if MR_SUBG is busy
  * @rmtoll SYSCFG_SR1  RFIP_BUSY_STATUS      LL_SYSCFG_IsMR_SUBGBusy
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsMR_SUBGBusy(void)
{
  return ((READ_BIT(SYSCFG->SR1, SYSCFG_SR1_RFIP_BUSY_STATUS) == (SYSCFG_SR1_RFIP_BUSY_STATUS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @rmtoll DBG_CR    DBG_STOP      LL_DBGMCU_EnableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @rmtoll DBG_CR    DBG_STOP      LL_DBGMCU_DisableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @rmtoll DBG_CR    DBG_SLEEP   LL_DBGMCU_EnableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @rmtoll DBG_CR    DBG_SLEEP   LL_DBGMCU_DisableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Freeze APB0 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB0FZR DBG_xxxx_STOP  LL_DBGMCU_APB0_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB0_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB0_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB0_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB0_GRP1_IWDG_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB0_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->DBG_APB0_FZ, Periphs);
}

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->DBG_APB1_FZ, Periphs);
}

/**
  * @brief  Unfreeze APB0 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR DBG_xxxx_STOP  LL_DBGMCU_APB0_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB0_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB0_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB0_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB0_GRP1_IWDG_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB0_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->DBG_APB0_FZ, Periphs);
}

/**
  * @brief  Unfreeze CPU1 APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->DBG_APB1_FZ, Periphs);
}
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

#endif /* STM32WL3x_LL_SYSTEM_H */