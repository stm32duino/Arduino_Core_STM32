/**
  ******************************************************************************
  * @file    stm32c0xx_ll_system.h
  * @author  MCD Application Team
  * @brief   Header file of SYSTEM LL module.
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
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL SYSTEM driver contains a set of generic APIs that can be
    used by user:
      (+) Some of the FLASH features need to be handled in the SYSTEM file.
      (+) Access to DBGCMU registers
      (+) Access to SYSCFG registers
  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32C0xx_LL_SYSTEM_H
#define STM32C0xx_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx.h"

/** @addtogroup STM32C0xx_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG) || defined (DBG)

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
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
  * @{
  */
#define LL_SYSCFG_REMAP_FLASH               0x00000000U                                           /*!< Main Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SYSTEMFLASH         SYSCFG_CFGR1_MEM_MODE_0                               /*!< System Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SRAM                (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0)   /*!< Embedded SRAM mapped at 0x00000000 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_PIN_RMP SYSCFG PIN RMP
  * @{
  */
#define LL_SYSCFG_PIN_RMP_PA11              SYSCFG_CFGR1_PA11_RMP                           /*!< PA11 pad behaves as PA9 pin */
#define LL_SYSCFG_PIN_RMP_PA12              SYSCFG_CFGR1_PA12_RMP                           /*!< PA12 pad behaves as PA10 pin */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_IR_MOD SYSCFG IR Modulation
  * @{
  */
#define LL_SYSCFG_IR_MOD_TIM16       (SYSCFG_CFGR1_IR_MOD_0 & SYSCFG_CFGR1_IR_MOD_1)    /*!< 00: Timer16 is selected as IRDA Modulation envelope source */
#define LL_SYSCFG_IR_MOD_USART1      (SYSCFG_CFGR1_IR_MOD_0)                            /*!< 01: USART1 is selected as IRDA Modulation envelope source */
#define LL_SYSCFG_IR_MOD_USART2      (SYSCFG_CFGR1_IR_MOD_1)                            /*!< 10: USART2 is selected as IRDA Modulation envelope source */

/**
  * @}
  */
/** @defgroup SYSTEM_LL_EC_IR_POL SYSCFG IR Polarity
  * @{
  */
#define LL_SYSCFG_IR_POL_NOT_INVERTED  0x00000000U                                     /*!< 0: Output of IRDA (IROut) not inverted */
#define LL_SYSCFG_IR_POL_INVERTED     (SYSCFG_CFGR1_IR_POL)                            /*!< 1: Output of IRDA (IROut) inverted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_BOOSTEN SYSCFG I/O analog switch voltage booster enable
  * @{
  */
#define LL_SYSCFG_CFGR1_BOOSTEN       SYSCFG_CFGR1_BOOSTEN                             /*!< I/O analog switch voltage booster enable */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_I2C_FASTMODEPLUS SYSCFG I2C FASTMODEPLUS
  * @{
  */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB6     SYSCFG_CFGR1_I2C_PB6_FMP  /*!< I2C PB6 Fast mode plus */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB7     SYSCFG_CFGR1_I2C_PB7_FMP  /*!< I2C PB7 Fast mode plus */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB8     SYSCFG_CFGR1_I2C_PB8_FMP  /*!< I2C PB8 Fast mode plus */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB9     SYSCFG_CFGR1_I2C_PB9_FMP  /*!< I2C PB9 Fast mode plus */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C1    SYSCFG_CFGR1_I2C1_FMP     /*!< Enable I2C1 Fast mode Plus  */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA9     SYSCFG_CFGR1_I2C_PA9_FMP  /*!< Enable Fast Mode Plus on PA9  */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PA10    SYSCFG_CFGR1_I2C_PA10_FMP /*!< Enable Fast Mode Plus on PA10 */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PC14    SYSCFG_CFGR1_I2C_PC14_FMP /*!< Enable Fast Mode Plus on PC14 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK SYSCFG TIMER BREAK
  * @{
  */
#define LL_SYSCFG_TIMBREAK_LOCKUP          SYSCFG_CFGR2_CLL            /*!< Enables and locks the LOCKUP (Hardfault) output of
                                                                            CortexM0 with Break Input of TIM1/16/17 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP_IP  DBGMCU APB1 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP      DBG_APB_FZ1_DBG_TIM3_STOP        /*!< TIM3 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_RTC_STOP       DBG_APB_FZ1_DBG_RTC_STOP         /*!< RTC Calendar frozen when core is halted */
#define LL_DBGMCU_APB1_GRP1_WWDG_STOP      DBG_APB_FZ1_DBG_WWDG_STOP        /*!< Debug Window Watchdog stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_IWDG_STOP      DBG_APB_FZ1_DBG_IWDG_STOP        /*!< Debug Independent Watchdog stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C1_STOP      DBG_APB_FZ1_DBG_I2C1_SMBUS_TIMEOUT_STOP /*!< I2C1 SMBUS timeout mode stopped when Core is halted */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP_IP DBGMCU APB2 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB2_GRP1_TIM1_STOP      DBG_APB_FZ2_DBG_TIM1_STOP        /*!< TIM1 counter stopped when core is halted */
#if defined(DBG_APB_FZ2_DBG_TIM14_STOP)
#define LL_DBGMCU_APB2_GRP1_TIM14_STOP     DBG_APB_FZ2_DBG_TIM14_STOP       /*!< TIM14 counter stopped when core is halted */
#endif /* DBG_APB_FZ2_DBG_TIM14_STOP */
#define LL_DBGMCU_APB2_GRP1_TIM16_STOP     DBG_APB_FZ2_DBG_TIM16_STOP       /*!< TIM16 counter stopped when core is halted */
#define LL_DBGMCU_APB2_GRP1_TIM17_STOP     DBG_APB_FZ2_DBG_TIM17_STOP       /*!< TIM17 counter stopped when core is halted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000U             /*!< FLASH Zero Latency cycle */
#define LL_FLASH_LATENCY_1                 FLASH_ACR_LATENCY_0     /*!< FLASH One Latency cycle */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_PINMUX_CFG PINMUX Config
  * @{
  */
#if (DEV_ID == 0x443UL)
#define LL_PINMUX_SO8_PIN1_PB7               (((SYSCFG_CFGR3_PINMUX0_0 | SYSCFG_CFGR3_PINMUX0_1) << 16U) | 0x00000000U)              /*!< STM32C011 SO8 package, Pin1 assigned to GPIO PB7 */
#define LL_PINMUX_SO8_PIN1_PC14              (((SYSCFG_CFGR3_PINMUX0_0 | SYSCFG_CFGR3_PINMUX0_1) << 16U) | SYSCFG_CFGR3_PINMUX0_0)   /*!< STM32C011 SO8 package, Pin1 assigned to GPIO PC14 */
#define LL_PINMUX_SO8_PIN4_PF2               (((SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1) << 16U) | 0x00000000U)              /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PF2 */
#define LL_PINMUX_SO8_PIN4_PA0               (((SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1) << 16U) | SYSCFG_CFGR3_PINMUX1_0)   /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PA0 */
#define LL_PINMUX_SO8_PIN4_PA1               (((SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1) << 16U) | SYSCFG_CFGR3_PINMUX1_1)   /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PA1 */
#define LL_PINMUX_SO8_PIN4_PA2               (((SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1) << 16U) | SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1)     /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PA2 */
#define LL_PINMUX_SO8_PIN5_PA8               (((SYSCFG_CFGR3_PINMUX2_0 | SYSCFG_CFGR3_PINMUX2_1) << 16U) | 0x00000000U)              /*!< STM32C011 SO8 package, Pin5 assigned to GPIO PA8 */
#define LL_PINMUX_SO8_PIN5_PA11              (((SYSCFG_CFGR3_PINMUX2_0 | SYSCFG_CFGR3_PINMUX2_1) << 16U) | SYSCFG_CFGR3_PINMUX2_0)   /*!< STM32C011 SO8 package, Pin5 assigned to GPIO PA11 */
#define LL_PINMUX_SO8_PIN8_PA14              (((SYSCFG_CFGR3_PINMUX3_0 | SYSCFG_CFGR3_PINMUX3_1) << 16U) | 0x00000000U)              /*!< STM32C011 SO8 package, Pin8 assigned to GPIO PA14 */
#define LL_PINMUX_SO8_PIN8_PB6               (((SYSCFG_CFGR3_PINMUX3_0 | SYSCFG_CFGR3_PINMUX3_1) << 16U) | SYSCFG_CFGR3_PINMUX3_0)   /*!< STM32C011 SO8 package, Pin8 assigned to GPIO PB6 */
#define LL_PINMUX_SO8_PIN8_PC15              (((SYSCFG_CFGR3_PINMUX3_0 | SYSCFG_CFGR3_PINMUX3_1) << 16U) | SYSCFG_CFGR3_PINMUX3_1)   /*!< STM32C011 SO8 package, Pin8 assigned to GPIO PC15 */
#define LL_PINMUX_WLCSP12_PINE2_PA7          (((SYSCFG_CFGR3_PINMUX4_0 | SYSCFG_CFGR3_PINMUX4_1) << 16U) | 0x00000000U)              /*!< STM32C011 WLCSP12 package, PinE2 assigned to GPIO PA7 */
#define LL_PINMUX_WLCSP12_PINE2_PA12         (((SYSCFG_CFGR3_PINMUX4_0 | SYSCFG_CFGR3_PINMUX4_1) << 16U) | SYSCFG_CFGR3_PINMUX4_0)   /*!< STM32C011 WLCSP12 package, PinE2 assigned to GPIO PA12 */
#define LL_PINMUX_WLCSP12_PINF1_PA3          (((SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1) << 16U) | 0x00000000U)              /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA3*/
#define LL_PINMUX_WLCSP12_PINF1_PA4          (((SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1) << 16U) | SYSCFG_CFGR3_PINMUX5_0)   /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA4 */
#define LL_PINMUX_WLCSP12_PINF1_PA5          (((SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1) << 16U) | SYSCFG_CFGR3_PINMUX5_1)   /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA5 */
#define LL_PINMUX_WLCSP12_PINF1_PA6          (((SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1) << 16U) | SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1)   /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA6 */

#elif (DEV_ID == 0x453UL)
#define LL_PINMUX_WLCSP14_PINF2_PA1           (((SYSCFG_CFGR3_PINMUX0_0 | SYSCFG_CFGR3_PINMUX0_1) << 16U) | 0x00000000U)             /*!< STM32C031 WLCSP14 package, PinF2 assigned to GPIO PA1 */
#define LL_PINMUX_WLCSP14_PINF2_PA2           (((SYSCFG_CFGR3_PINMUX0_0 | SYSCFG_CFGR3_PINMUX0_1) << 16U) | SYSCFG_CFGR3_PINMUX0_0)  /*!< STM32C031 WLCSP14 package, PinF2 assigned to GPIO PA2 */
#define LL_PINMUX_WLCSP14_PING3_PF2           (((SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1) << 16U) | 0x00000000U)             /*!< STM32C031 WLCSP14 package, PinG3 assigned to GPIO PF2 */
#define LL_PINMUX_WLCSP14_PING3_PA0           (((SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1) << 16U) | SYSCFG_CFGR3_PINMUX1_0)  /*!< STM32C031 WLCSP14 package, PinG3 assigned to GPIO PA0 */
#define LL_PINMUX_WLCSP14_PINJ1_PA8           (((SYSCFG_CFGR3_PINMUX2_0 | SYSCFG_CFGR3_PINMUX2_1) << 16U) | 0x00000000U)             /*!< STM32C031 WLCSP14 package, PinJ1 assigned to GPIO PA8 */
#define LL_PINMUX_WLCSP14_PINJ1_PA11          (((SYSCFG_CFGR3_PINMUX2_0 | SYSCFG_CFGR3_PINMUX2_1) << 16U) | SYSCFG_CFGR3_PINMUX2_0)  /*!< STM32C031 WLCSP14 package, PinJ1 assigned to GPIO PA11 */
#define LL_PINMUX_WLCSP14_PINH2_PA5           (((SYSCFG_CFGR3_PINMUX3_0 | SYSCFG_CFGR3_PINMUX3_1) << 16U) | 0x00000000U)             /*!< STM32C031 WLCSP14 package, PinH2 assigned to GPIO PA5 */
#define LL_PINMUX_WLCSP14_PINH2_PA6           (((SYSCFG_CFGR3_PINMUX3_0 | SYSCFG_CFGR3_PINMUX3_1) << 16U) | SYSCFG_CFGR3_PINMUX3_0)  /*!< STM32C031 WLCSP14 package, PinH2 assigned to GPIO PA6 */
#define LL_PINMUX_WLCSP14_PING1_PA7           (((SYSCFG_CFGR3_PINMUX4_0 | SYSCFG_CFGR3_PINMUX4_1) << 16U) | 0x00000000U)             /*!< STM32C031 WLCSP14 package, PinG1 assigned to GPIO PA7 */
#define LL_PINMUX_WLCSP14_PING1_PA12          (((SYSCFG_CFGR3_PINMUX4_0 | SYSCFG_CFGR3_PINMUX4_1) << 16U) | SYSCFG_CFGR3_PINMUX4_0)  /*!< STM32C031 WLCSP14 package, PinG1 assigned to GPIO PA12 */
#define LL_PINMUX_WLCSP14_PINJ3_PA3           (((SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1) << 16U) | 0x00000000U)             /*!< STM32C031 WLCSP14 package, PinJ3 assigned to GPIO PA3 */
#define LL_PINMUX_WLCSP14_PINJ3_PA4           (((SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1) << 16U) | SYSCFG_CFGR3_PINMUX5_0)  /*!< STM32C031 WLCSP14 package, PinJ3 assigned to GPIO PA4 */
#endif /* DEV_ID == 0x443UL */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_PINMUX_SOURCE PINMUX Config Source
  * @{
  */
#if (DEV_ID == 0x443UL)
#define LL_PINMUX_SO8_PIN1               (SYSCFG_CFGR3_PINMUX0_0 | SYSCFG_CFGR3_PINMUX0_1)       /*!< STM32C011 SO8 package, GPIO Pin1 multiplexer  */
#define LL_PINMUX_SO8_PIN4               (SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1)       /*!< STM32C011 SO8 package, GPIO Pin4 multiplexer  */
#define LL_PINMUX_SO8_PIN5               (SYSCFG_CFGR3_PINMUX2_0 | SYSCFG_CFGR3_PINMUX2_1)       /*!< STM32C011 SO8 package, GPIO Pin5 multiplexer  */
#define LL_PINMUX_SO8_PIN8               (SYSCFG_CFGR3_PINMUX3_0 | SYSCFG_CFGR3_PINMUX3_1)       /*!< STM32C011 SO8 package, GPIO Pin8 multiplexer  */
#define LL_PINMUX_WLCSP12_PINE2          (SYSCFG_CFGR3_PINMUX4_0 | SYSCFG_CFGR3_PINMUX4_1)       /*!< STM32C011 WLCSP12 package, GPIO PinE2 multiplexer */
#define LL_PINMUX_WLCSP12_PINF1          (SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1)       /*!< STM32C011 WLCSP12 package, GPIO PinF1 multiplexer */
#elif (DEV_ID == 0x453UL)
#define LL_PINMUX_WLCSP14_PINF2          (SYSCFG_CFGR3_PINMUX0_0 | SYSCFG_CFGR3_PINMUX0_1)       /*!< STM32C031 WLCSP14 package, GPIO PinF2 multiplexer */
#define LL_PINMUX_WLCSP14_PING3          (SYSCFG_CFGR3_PINMUX1_0 | SYSCFG_CFGR3_PINMUX1_1)       /*!< STM32C031 WLCSP14 package, GPIO PinG3 multiplexer */
#define LL_PINMUX_WLCSP14_PINJ1          (SYSCFG_CFGR3_PINMUX2_0 | SYSCFG_CFGR3_PINMUX2_1)       /*!< STM32C031 WLCSP14 package, GPIO PinJ1 multiplexer */
#define LL_PINMUX_WLCSP14_PINH2          (SYSCFG_CFGR3_PINMUX3_0 | SYSCFG_CFGR3_PINMUX3_1)       /*!< STM32C031 WLCSP14 package, GPIO PinH2 multiplexer */
#define LL_PINMUX_WLCSP14_PING1          (SYSCFG_CFGR3_PINMUX4_0 | SYSCFG_CFGR3_PINMUX4_1)       /*!< STM32C031 WLCSP14 package, GPIO PinG1 multiplexer */
#define LL_PINMUX_WLCSP14_PINJ3          (SYSCFG_CFGR3_PINMUX5_0 | SYSCFG_CFGR3_PINMUX5_1)       /*!< STM32C031 WLCSP14 package, GPIO PinJ3 multiplexer */
#endif /* DEV_ID == 0x443UL */
 /**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE));
}

/**
  * @brief  Enable remap of a pin on different pad
  * @rmtoll SYSCFG_CFGR1 PA11_RMP  LL_SYSCFG_EnablePinRemap\n
  *         SYSCFG_CFGR1 PA12_RMP   LL_SYSCFG_EnablePinRemap\n
  * @param  PinRemap This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_PIN_RMP_PA11
  *         @arg @ref LL_SYSCFG_PIN_RMP_PA12
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnablePinRemap(uint32_t PinRemap)
{
  SET_BIT(SYSCFG->CFGR1, PinRemap);
}

/**
  * @brief  Enable remap of a pin on different pad
  * @rmtoll SYSCFG_CFGR1 PA11_RMP  LL_SYSCFG_DisablePinRemap\n
  *         SYSCFG_CFGR1 PA12_RMP   LL_SYSCFG_DisablePinRemap\n
  * @param  PinRemap This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_PIN_RMP_PA11
  *         @arg @ref LL_SYSCFG_PIN_RMP_PA12
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisablePinRemap(uint32_t PinRemap)
{
  CLEAR_BIT(SYSCFG->CFGR1, PinRemap);
}

/**
  * @brief  Set IR Modulation Envelope signal source.
  * @rmtoll SYSCFG_CFGR1 IR_MOD  LL_SYSCFG_SetIRModEnvelopeSignal
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_IR_MOD_TIM16
  *         @arg @ref LL_SYSCFG_IR_MOD_USART1
  *         @arg @ref LL_SYSCFG_IR_MOD_USART2
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetIRModEnvelopeSignal(uint32_t Source)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_MOD, Source);
}

/**
  * @brief  Get IR Modulation Envelope signal source.
  * @rmtoll SYSCFG_CFGR1 IR_MOD  LL_SYSCFG_GetIRModEnvelopeSignal
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_IR_MOD_TIM16
  *         @arg @ref LL_SYSCFG_IR_MOD_USART1
  *         @arg @ref LL_SYSCFG_IR_MOD_USART2
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetIRModEnvelopeSignal(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_MOD));
}

/**
  * @brief  Set IR Output polarity.
  * @rmtoll SYSCFG_CFGR1 IR_POL  LL_SYSCFG_SetIRPolarity
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_IR_POL_INVERTED
  *         @arg @ref LL_SYSCFG_IR_POL_NOT_INVERTED
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetIRPolarity(uint32_t Polarity)
{
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_POL, Polarity);
}

/**
  * @brief  Get IR Output polarity.
  * @rmtoll SYSCFG_CFGR1 IR_POL  LL_SYSCFG_GetIRPolarity
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_IR_POL_INVERTED
  *         @arg @ref LL_SYSCFG_IR_POL_NOT_INVERTED
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetIRPolarity(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_POL));
}


/**
  * @brief  Enable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_FMP_PB6   LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB7   LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB8   LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB9   LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_I2C1  LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA9   LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA10  LL_SYSCFG_EnableFastModePlus
  *         SYSCFG_CFGR1 I2C_FMP_PC14  LL_SYSCFG_EnableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA10
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PC14
  *
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  SET_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Disable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_FMP_PB6   LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB7   LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB8   LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB9   LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_I2C1  LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA9   LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA10  LL_SYSCFG_DisableFastModePlus
  *         SYSCFG_CFGR1 I2C_FMP_PC14  LL_SYSCFG_EnableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PA10
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PC14
  *
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  CLEAR_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Set connections to TIM1/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL   LL_SYSCFG_SetTIMBreakInputs\n
  * @param  Break This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIMBreakInputs(uint32_t Break)
{
  MODIFY_REG(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL, Break);
}

/**
  * @brief  Get connections to TIM1/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL   LL_SYSCFG_GetTIMBreakInputs\n
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIMBreakInputs(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL));
}

/**
  * @brief  Config PinMux
  * @rmtoll SYSCFG_CFGR3 CLL   LL_SYSCFG_ConfigPinMux\n
  * @param  mux_cfg This parameter can be a value of @ref SYSTEM_LL_PINMUX_CFG
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_ConfigPinMux(uint32_t mux_cfg)
{
  MODIFY_REG(SYSCFG->CFGR3, (mux_cfg >> 16U), (mux_cfg & 0x0000FFFFU));
}

/**
  * @brief  Get PinMux configuration
  * @rmtoll SYSCFG_CFGR3 CLL   LL_SYSCFG_GetConfigPinMux\n
  * @param  LL_PINMUX_PACKx_PINy This parameter can be a value of @ref SYSTEM_LL_PINMUX_SOURCE
  * @retval Returned value can be one of SYSTEM_LL_PINMUX_CFG defines
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetConfigPinMux(uint32_t LL_PINMUX_PACKx_PINy)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR3, LL_PINMUX_PACKx_PINy) | (LL_PINMUX_PACKx_PINy << 16U));
}

#if defined(SYSCFG_ITLINE0_SR_EWDG)
/**
  * @brief  Check if Window watchdog interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE0 SR_EWDG       LL_SYSCFG_IsActiveFlag_WWDG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_WWDG(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[0], SYSCFG_ITLINE0_SR_EWDG) == (SYSCFG_ITLINE0_SR_EWDG)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE0_SR_EWDG */

#if defined(SYSCFG_ITLINE2_SR_RTC)
/**
  * @brief  Check if RTC interrupt occurred or not (EXTI line 19).
  * @rmtoll SYSCFG_ITLINE2 SR_RTC  LL_SYSCFG_IsActiveFlag_RTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_RTC(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[2], SYSCFG_ITLINE2_SR_RTC) == (SYSCFG_ITLINE2_SR_RTC)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE2_SR_RTC */

#if defined(SYSCFG_ITLINE3_SR_FLASH_ITF)
/**
  * @brief  Check if Flash interface interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE3 SR_FLASH_ITF  LL_SYSCFG_IsActiveFlag_FLASH_ITF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_FLASH_ITF(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[3], SYSCFG_ITLINE3_SR_FLASH_ITF) == (SYSCFG_ITLINE3_SR_FLASH_ITF)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE3_SR_FLASH_ITF */


#if defined(SYSCFG_ITLINE4_SR_CLK_CTRL)
/**
  * @brief  Check if Reset and clock control interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE4 SR_CLK_CTRL   LL_SYSCFG_IsActiveFlag_CLK_CTRL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_CLK_CTRL(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[4], SYSCFG_ITLINE4_SR_CLK_CTRL) == (SYSCFG_ITLINE4_SR_CLK_CTRL)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE4_SR_CLK_CTRL */

#if defined(SYSCFG_ITLINE5_SR_EXTI0)
/**
  * @brief  Check if EXTI line 0 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE5 SR_EXTI0      LL_SYSCFG_IsActiveFlag_EXTI0
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI0(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[5], SYSCFG_ITLINE5_SR_EXTI0) == (SYSCFG_ITLINE5_SR_EXTI0)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE5_SR_EXTI0 */

#if defined(SYSCFG_ITLINE5_SR_EXTI1)
/**
  * @brief  Check if EXTI line 1 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE5 SR_EXTI1      LL_SYSCFG_IsActiveFlag_EXTI1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI1(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[5], SYSCFG_ITLINE5_SR_EXTI1) == (SYSCFG_ITLINE5_SR_EXTI1)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE5_SR_EXTI1 */

#if defined(SYSCFG_ITLINE6_SR_EXTI2)
/**
  * @brief  Check if EXTI line 2 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE6 SR_EXTI2      LL_SYSCFG_IsActiveFlag_EXTI2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI2(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[6], SYSCFG_ITLINE6_SR_EXTI2) == (SYSCFG_ITLINE6_SR_EXTI2)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE6_SR_EXTI2 */

#if defined(SYSCFG_ITLINE6_SR_EXTI3)
/**
  * @brief  Check if EXTI line 3 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE6 SR_EXTI3      LL_SYSCFG_IsActiveFlag_EXTI3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI3(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[6], SYSCFG_ITLINE6_SR_EXTI3) == (SYSCFG_ITLINE6_SR_EXTI3)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE6_SR_EXTI3 */

#if defined(SYSCFG_ITLINE7_SR_EXTI4)
/**
  * @brief  Check if EXTI line 4 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI4      LL_SYSCFG_IsActiveFlag_EXTI4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI4(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI4) == (SYSCFG_ITLINE7_SR_EXTI4)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI4 */

#if defined(SYSCFG_ITLINE7_SR_EXTI5)
/**
  * @brief  Check if EXTI line 5 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI5      LL_SYSCFG_IsActiveFlag_EXTI5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI5(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI5) == (SYSCFG_ITLINE7_SR_EXTI5)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI5 */

#if defined(SYSCFG_ITLINE7_SR_EXTI6)
/**
  * @brief  Check if EXTI line 6 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI6      LL_SYSCFG_IsActiveFlag_EXTI6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI6(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI6) == (SYSCFG_ITLINE7_SR_EXTI6)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI6 */

#if defined(SYSCFG_ITLINE7_SR_EXTI7)
/**
  * @brief  Check if EXTI line 7 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI7      LL_SYSCFG_IsActiveFlag_EXTI7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI7(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI7) == (SYSCFG_ITLINE7_SR_EXTI7)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI7 */

#if defined(SYSCFG_ITLINE7_SR_EXTI8)
/**
  * @brief  Check if EXTI line 8 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI8      LL_SYSCFG_IsActiveFlag_EXTI8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI8(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI8) == (SYSCFG_ITLINE7_SR_EXTI8)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI8 */

#if defined(SYSCFG_ITLINE7_SR_EXTI9)
/**
  * @brief  Check if EXTI line 9 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI9      LL_SYSCFG_IsActiveFlag_EXTI9
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI9(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI9) == (SYSCFG_ITLINE7_SR_EXTI9)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI9 */

#if defined(SYSCFG_ITLINE7_SR_EXTI10)
/**
  * @brief  Check if EXTI line 10 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI10     LL_SYSCFG_IsActiveFlag_EXTI10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI10(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI10) == (SYSCFG_ITLINE7_SR_EXTI10)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI10 */

#if defined(SYSCFG_ITLINE7_SR_EXTI11)
/**
  * @brief  Check if EXTI line 11 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI11     LL_SYSCFG_IsActiveFlag_EXTI11
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI11(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI11) == (SYSCFG_ITLINE7_SR_EXTI11)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI11 */

#if defined(SYSCFG_ITLINE7_SR_EXTI12)
/**
  * @brief  Check if EXTI line 12 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI12     LL_SYSCFG_IsActiveFlag_EXTI12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI12(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI12) == (SYSCFG_ITLINE7_SR_EXTI12)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI12 */

#if defined(SYSCFG_ITLINE7_SR_EXTI13)
/**
  * @brief  Check if EXTI line 13 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI13     LL_SYSCFG_IsActiveFlag_EXTI13
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI13(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI13) == (SYSCFG_ITLINE7_SR_EXTI13)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI13 */

#if defined(SYSCFG_ITLINE7_SR_EXTI14)
/**
  * @brief  Check if EXTI line 14 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI14     LL_SYSCFG_IsActiveFlag_EXTI14
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI14(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI14) == (SYSCFG_ITLINE7_SR_EXTI14)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI14 */

#if defined(SYSCFG_ITLINE7_SR_EXTI15)
/**
  * @brief  Check if EXTI line 15 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE7 SR_EXTI15     LL_SYSCFG_IsActiveFlag_EXTI15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_EXTI15(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[7], SYSCFG_ITLINE7_SR_EXTI15) == (SYSCFG_ITLINE7_SR_EXTI15)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE7_SR_EXTI15 */


#if defined(SYSCFG_ITLINE9_SR_DMA1_CH1)
/**
  * @brief  Check if DMA1 channel 1 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE9 SR_DMA1_CH1   LL_SYSCFG_IsActiveFlag_DMA1_CH1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_DMA1_CH1(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[9], SYSCFG_ITLINE9_SR_DMA1_CH1) == (SYSCFG_ITLINE9_SR_DMA1_CH1)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE9_SR_DMA1_CH1 */

#if defined(SYSCFG_ITLINE10_SR_DMA1_CH2)
/**
  * @brief  Check if DMA1 channel 2 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE10 SR_DMA1_CH2   LL_SYSCFG_IsActiveFlag_DMA1_CH2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_DMA1_CH2(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[10], SYSCFG_ITLINE10_SR_DMA1_CH2) == (SYSCFG_ITLINE10_SR_DMA1_CH2)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE10_SR_DMA1_CH2 */

#if defined(SYSCFG_ITLINE10_SR_DMA1_CH3)
/**
  * @brief  Check if DMA1 channel 3 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE10 SR_DMA1_CH3   LL_SYSCFG_IsActiveFlag_DMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_DMA1_CH3(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[10], SYSCFG_ITLINE10_SR_DMA1_CH3) == (SYSCFG_ITLINE10_SR_DMA1_CH3)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE10_SR_DMA1_CH3 */


#if defined(SYSCFG_ITLINE11_SR_DMAMUX1)
/**
  * @brief  Check if DMAMUX interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE11 SR_DMAMUX1   LL_SYSCFG_IsActiveFlag_DMAMUX
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_DMAMUX(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[11], SYSCFG_ITLINE11_SR_DMAMUX1) == (SYSCFG_ITLINE11_SR_DMAMUX1)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE11_SR_DMAMUX */

#if defined(SYSCFG_ITLINE12_SR_ADC)
/**
  * @brief  Check if ADC interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE12 SR_ADC        LL_SYSCFG_IsActiveFlag_ADC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_ADC(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[12], SYSCFG_ITLINE12_SR_ADC) == (SYSCFG_ITLINE12_SR_ADC)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE12_SR_ADC */

#if defined(SYSCFG_ITLINE13_SR_TIM1_BRK)
/**
  * @brief  Check if Timer 1 break interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE13 SR_TIM1_BRK   LL_SYSCFG_IsActiveFlag_TIM1_BRK
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM1_BRK(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[13], SYSCFG_ITLINE13_SR_TIM1_BRK) == (SYSCFG_ITLINE13_SR_TIM1_BRK)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE13_SR_TIM1_BRK */

#if defined(SYSCFG_ITLINE13_SR_TIM1_UPD)
/**
  * @brief  Check if Timer 1 update interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE13 SR_TIM1_UPD   LL_SYSCFG_IsActiveFlag_TIM1_UPD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM1_UPD(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[13], SYSCFG_ITLINE13_SR_TIM1_UPD) == (SYSCFG_ITLINE13_SR_TIM1_UPD)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE13_SR_TIM1_UPD */

#if defined(SYSCFG_ITLINE13_SR_TIM1_TRG)
/**
  * @brief  Check if Timer 1 trigger interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE13 SR_TIM1_TRG   LL_SYSCFG_IsActiveFlag_TIM1_TRG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM1_TRG(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[13], SYSCFG_ITLINE13_SR_TIM1_TRG) == (SYSCFG_ITLINE13_SR_TIM1_TRG)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE13_SR_TIM1_TRG */

#if defined(SYSCFG_ITLINE13_SR_TIM1_CCU)
/**
  * @brief  Check if Timer 1 commutation interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE13 SR_TIM1_CCU   LL_SYSCFG_IsActiveFlag_TIM1_CCU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM1_CCU(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[13], SYSCFG_ITLINE13_SR_TIM1_CCU) == (SYSCFG_ITLINE13_SR_TIM1_CCU)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE13_SR_TIM1_CCU */

#if defined(SYSCFG_ITLINE14_SR_TIM1_CC)
/**
  * @brief  Check if Timer 1 capture compare interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE14 SR_TIM1_CC    LL_SYSCFG_IsActiveFlag_TIM1_CC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM1_CC(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[14], SYSCFG_ITLINE14_SR_TIM1_CC) == (SYSCFG_ITLINE14_SR_TIM1_CC)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE14_SR_TIM1_CC */


#if defined(SYSCFG_ITLINE16_SR_TIM3_GLB)
/**
  * @brief  Check if Timer 3 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE16 SR_TIM3_GLB   LL_SYSCFG_IsActiveFlag_TIM3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM3(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[16], SYSCFG_ITLINE16_SR_TIM3_GLB) == (SYSCFG_ITLINE16_SR_TIM3_GLB)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE16_SR_TIM3_GLB */

#if defined(SYSCFG_ITLINE19_SR_TIM14_GLB)
/**
  * @brief  Check if Timer 14 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE19 SR_TIM14_GLB  LL_SYSCFG_IsActiveFlag_TIM14
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM14(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[19], SYSCFG_ITLINE19_SR_TIM14_GLB) == (SYSCFG_ITLINE19_SR_TIM14_GLB)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE19_SR_TIM14_GLB */

#if defined(SYSCFG_ITLINE21_SR_TIM16_GLB)
/**
  * @brief  Check if Timer 16 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE21 SR_TIM16_GLB  LL_SYSCFG_IsActiveFlag_TIM16
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM16(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[21], SYSCFG_ITLINE21_SR_TIM16_GLB) == (SYSCFG_ITLINE21_SR_TIM16_GLB)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE21_SR_TIM16_GLB */

#if defined(SYSCFG_ITLINE22_SR_TIM17_GLB)
/**
  * @brief  Check if Timer 17 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE22 SR_TIM17_GLB  LL_SYSCFG_IsActiveFlag_TIM17
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_TIM17(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[22], SYSCFG_ITLINE22_SR_TIM17_GLB) == (SYSCFG_ITLINE22_SR_TIM17_GLB)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE22_SR_TIM17_GLB */

#if defined(SYSCFG_ITLINE23_SR_I2C1_GLB)
/**
  * @brief  Check if I2C1 interrupt occurred or not, combined with EXTI line 23.
  * @rmtoll SYSCFG_ITLINE23 SR_I2C1_GLB   LL_SYSCFG_IsActiveFlag_I2C1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_I2C1(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[23], SYSCFG_ITLINE23_SR_I2C1_GLB) == (SYSCFG_ITLINE23_SR_I2C1_GLB)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE23_SR_I2C1_GLB */

#if defined(SYSCFG_ITLINE25_SR_SPI1)
/**
  * @brief  Check if SPI1 interrupt occurred or not.
  * @rmtoll SYSCFG_ITLINE25 SR_SPI1       LL_SYSCFG_IsActiveFlag_SPI1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_SPI1(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[25], SYSCFG_ITLINE25_SR_SPI1) == (SYSCFG_ITLINE25_SR_SPI1)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE25_SR_SPI1 */


#if defined(SYSCFG_ITLINE27_SR_USART1_GLB)
/**
  * @brief  Check if USART1 interrupt occurred or not, combined with EXTI line 25.
  * @rmtoll SYSCFG_ITLINE27 SR_USART1_GLB  LL_SYSCFG_IsActiveFlag_USART1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_USART1(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[27], SYSCFG_ITLINE27_SR_USART1_GLB) == (SYSCFG_ITLINE27_SR_USART1_GLB)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE27_SR_USART1_GLB */

#if defined(SYSCFG_ITLINE28_SR_USART2_GLB)
/**
  * @brief  Check if USART2 interrupt occurred or not, combined with EXTI line 26.
  * @rmtoll SYSCFG_ITLINE28 SR_USART2_GLB  LL_SYSCFG_IsActiveFlag_USART2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_USART2(void)
{
  return ((READ_BIT(SYSCFG->IT_LINE_SR[28], SYSCFG_ITLINE28_SR_USART2_GLB) == (SYSCFG_ITLINE28_SR_USART2_GLB)) ? 1UL : 0UL);
}
#endif /* SYSCFG_ITLINE28_SR_USART2_GLB */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the device identifier
  * @rmtoll DBG_IDCODE DEV_ID        LL_DBGMCU_GetDeviceID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDeviceID(void)
{
  return (uint32_t)(READ_BIT(DBG->IDCODE, DBG_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier
  * @note This field indicates the revision of the device.
  * @rmtoll DBG_IDCODE REV_ID        LL_DBGMCU_GetRevisionID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBG->IDCODE, DBG_IDCODE_REV_ID) >> DBG_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @rmtoll DBG_CR    DBG_STOP      LL_DBGMCU_EnableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBG->CR, DBG_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @rmtoll DBG_CR    DBG_STOP      LL_DBGMCU_DisableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBG->CR, DBG_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @rmtoll DBG_CR    DBG_STANDBY   LL_DBGMCU_EnableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBG->CR, DBG_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @rmtoll DBG_CR    DBG_STANDBY   LL_DBGMCU_DisableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBG->CR, DBG_CR_DBG_STANDBY);
}

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBG_APB_FZ1 DBG_TIM3_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBG_APB_FZ1 DBG_RTC_STOP            LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBG_APB_FZ1 DBG_WWDG_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBG_APB_FZ1 DBG_IWDG_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBG_APB_FZ1 DBG_I2C1_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBG->APBFZ1, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBG_APB_FZ1 DBG_TIM3_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBG_APB_FZ1 DBG_RTC_STOP            LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBG_APB_FZ1 DBG_WWDG_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBG_APB_FZ1 DBG_IWDG_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBG_APB_FZ1 DBG_I2C1_SMBUS_TIMEOUT  LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBG->APBFZ1, Periphs);
}

/**
  * @brief  Freeze APB2 peripherals
  * @rmtoll DBG_APB_FZ2 DBG_TIM1_STOP   LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBG_APB_FZ2 DBG_TIM14_STOP  LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBG_APB_FZ2 DBG_TIM16_STOP  LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBG_APB_FZ2 DBG_TIM17_STOP  LL_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  *
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBG->APBFZ2, Periphs);
}

/**
  * @brief  Unfreeze APB2 peripherals
  * @rmtoll DBG_APB_FZ2 DBG_TIM1_STOP   LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBG_APB_FZ2 DBG_TIM14_STOP  LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBG_APB_FZ2 DBG_TIM16_STOP  LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBG_APB_FZ2 DBG_TIM17_STOP  LL_DBGMCU_APB2_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  *
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBG->APBFZ2, Periphs);
}
/**
  * @}
  */


/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    FLASH_ACR_LATENCY       LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    FLASH_ACR_LATENCY       LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @brief  Enable Prefetch
  * @rmtoll FLASH_ACR    FLASH_ACR_PRFTEN        LL_FLASH_EnablePrefetch
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePrefetch(void)
{
  SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
}

/**
  * @brief  Disable Prefetch
  * @rmtoll FLASH_ACR    FLASH_ACR_PRFTEN        LL_FLASH_DisablePrefetch
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePrefetch(void)
{
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
}

/**
  * @brief  Check if Prefetch buffer is enabled
  * @rmtoll FLASH_ACR    FLASH_ACR_PRFTEN        LL_FLASH_IsPrefetchEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsPrefetchEnabled(void)
{
  return ((READ_BIT(FLASH->ACR, FLASH_ACR_PRFTEN) == (FLASH_ACR_PRFTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Instruction cache
  * @rmtoll FLASH_ACR    FLASH_ACR_ICEN          LL_FLASH_EnableInstCache
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableInstCache(void)
{
  SET_BIT(FLASH->ACR, FLASH_ACR_ICEN);
}

/**
  * @brief  Disable Instruction cache
  * @rmtoll FLASH_ACR    FLASH_ACR_ICEN          LL_FLASH_DisableInstCache
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableInstCache(void)
{
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICEN);
}

/**
  * @brief  Enable Instruction cache reset
  * @note  bit can be written only when the instruction cache is disabled
  * @rmtoll FLASH_ACR    FLASH_ACR_ICRST         LL_FLASH_EnableInstCacheReset
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableInstCacheReset(void)
{
  SET_BIT(FLASH->ACR, FLASH_ACR_ICRST);
}

/**
  * @brief  Disable Instruction cache reset
  * @rmtoll FLASH_ACR    FLASH_ACR_ICRST         LL_FLASH_DisableInstCacheReset
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableInstCacheReset(void)
{
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICRST);
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

#endif /* defined (FLASH) || defined (SYSCFG) || defined (DBG) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32C0xx_LL_SYSTEM_H */
