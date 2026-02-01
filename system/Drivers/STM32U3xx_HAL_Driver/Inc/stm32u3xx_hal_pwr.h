/**
  ******************************************************************************
  * @file    stm32u3xx_hal_pwr.h
  * @author  GPM Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef STM32U3xx_HAL_PWR_H
#define STM32U3xx_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t PVDLevel; /*!< Specifies the PVD detection level.
                          This parameter can be a value of
                          @ref PWR_PVD_Detection_Level.                       */

  uint32_t Mode;     /*!< Specifies the operating mode for the selected lines.
                          This parameter can be a value of @ref PWR_PVD_Mode. */
} PWR_PVDTypeDef;

/**
  * @brief  PWR PVM configuration structure definition
  */
typedef struct
{
  uint32_t PVMType;   /*!< Specifies which voltage is monitored.
                           This parameter can be a value of
                           @ref PWR_PVM_Type.                               */

  uint32_t Mode;      /*!< Specifies the operating mode for the selected lines.
                           This parameter can be a value of
                           @ref PWR_PVM_Mode.                               */
} PWR_PVMTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_PVD_Detection_Level Programmable Voltage Detection Level
  * @{
  */
#define PWR_PVDLEVEL_0                 (0U)                                    /*!< PVD threshold around 2.0 V       */
#define PWR_PVDLEVEL_1                 PWR_SVMCR_PVDLS_0                       /*!< PVD threshold around 2.2 V       */
#define PWR_PVDLEVEL_2                 PWR_SVMCR_PVDLS_1                       /*!< PVD threshold around 2.4 V       */
#define PWR_PVDLEVEL_3                 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_1) /*!< PVD threshold around 2.5 V       */
#define PWR_PVDLEVEL_4                 PWR_SVMCR_PVDLS_2                       /*!< PVD threshold around 2.6 V       */
#define PWR_PVDLEVEL_5                 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_2) /*!< PVD threshold around 2.8 V       */
#define PWR_PVDLEVEL_6                 (PWR_SVMCR_PVDLS_1 | PWR_SVMCR_PVDLS_2) /*!< PVD threshold around 2.9 V       */
#define PWR_PVDLEVEL_7                 PWR_SVMCR_PVDLS                         /*!< External input analog voltage
                                                                                    (compared internally to VREFINT) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode PWR PVD Mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL               (0x00U)                              /*!< Basic Mode is used                */
#define PWR_PVD_MODE_IT_RISING            (0x05U)                              /*!< External Interrupt Mode with Rising
                                                                                    edge trigger detection            */
#define PWR_PVD_MODE_IT_FALLING           (0x06U)                              /*!< External Interrupt Mode with Falling
                                                                                    edge trigger detection            */
#define PWR_PVD_MODE_IT_RISING_FALLING    (0x07U)                              /*!< External Interrupt Mode with Rising/
                                                                                    Falling edge trigger detection    */
#define PWR_PVD_MODE_EVENT_RISING         (0x09U)                              /*!< Event Mode with Rising edge trigger
                                                                                    detection                         */
#define PWR_PVD_MODE_EVENT_FALLING        (0x0AU)                              /*!< Event Mode with Falling edge trigger
                                                                                    detection                         */
#define PWR_PVD_MODE_EVENT_RISING_FALLING (0x0BU)                              /*!< Event Mode with Rising/Falling edge
                                                                                    trigger detection                 */
/**
  * @}
  */

/** @defgroup PWR_PVM_Mode PWR PVM Interrupt and Event Mode
  * @{
  */
#define PWR_PVM_MODE_NORMAL               (0x00U) /*!< Basic Mode is used                                             */
#define PWR_PVM_MODE_IT_RISING            (0x05U) /*!< External Interrupt Mode with Rising edge trigger detection     */
#define PWR_PVM_MODE_IT_FALLING           (0x06U) /*!< External Interrupt Mode with Falling edge trigger detection    */
#define PWR_PVM_MODE_IT_RISING_FALLING    (0x07U) /*!< External Interrupt Mode with Rising/Falling edge trigger
                                                        detection                                                     */
#define PWR_PVM_MODE_EVENT_RISING         (0x09U) /*!< Event Mode with Rising edge trigger detection                  */
#define PWR_PVM_MODE_EVENT_FALLING        (0x0AU) /*!< Event Mode with Falling edge trigger detection                 */
#define PWR_PVM_MODE_EVENT_RISING_FALLING (0x0BU) /*!< Event Mode with Rising/Falling edge trigger detection          */
/**
  * @}
  */

/** @defgroup PWR_Regulator_In_LowPower_Mode PWR Regulator State in Sleep/Stop Mode
  * @{
  */
#define PWR_MAINREGULATOR_ON           (0U)                                  /*!< Main Regulator ON in Run Mode       */
#define PWR_LOWPOWERREGULATOR_ON       PWR_CR1_LPMS_0                        /*!< Main Regulator ON in Low Power Mode */
/**
  * @}
  */

/** @defgroup PWR_Low_Power_Mode_Selection  PWR Low Power Mode Selection
  * @{
  */
#define PWR_LOWPOWERMODE_STOP0    (0U)                                /*!< Stop 0: stop mode with main regulator      */
#define PWR_LOWPOWERMODE_STOP1    PWR_CR1_LPMS_0                      /*!< Stop 1: stop mode with low power regulator */
#define PWR_LOWPOWERMODE_STOP2    PWR_CR1_LPMS_1                      /*!< Stop 2: stop mode with low power regulator */
#define PWR_LOWPOWERMODE_STOP3    (PWR_CR1_LPMS_0 | PWR_CR1_LPMS_1)   /*!< Stop 3: stop mode with low power regulator */
/**
  * @}
  */

/** @defgroup PWR_Sleep_Mode_Entry PWR Sleep Mode Entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI              (1U)  /*!< Wait For Interruption instruction to enter Sleep mode              */
#define PWR_SLEEPENTRY_WFE              (2U)  /*!< Wait For Event instruction to enter Sleep mode                     */
#define PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR (3U)  /*!< Wait For Event instruction to enter Sleep mode with no event clear */
/**
  * @}
  */

/** @defgroup PWR_Stop_Mode_Entry PWR Stop Mode Entry
  * @{
  */
#define PWR_STOPENTRY_WFI              (1U)    /*!< Wait For Interruption instruction to enter Stop mode              */
#define PWR_STOPENTRY_WFE              (2U)    /*!< Wait For Event instruction to enter Stop mode                     */
#define PWR_STOPENTRY_WFE_NO_EVT_CLEAR (3U)    /*!< Wait For Event instruction to enter Stop mode with no event clear */
/**
  * @}
  */

/** @defgroup PWR_Flags PWR Flags
  * @{
  */
#define PWR_FLAG_STOPF                 (0x1U)                        /*!< Stop flag                                   */
#define PWR_FLAG_SBF                   (0x2U)                        /*!< Standby flag                                */
#define PWR_FLAG_R1RDY                 (0x3U)                        /*!< Voltage range 1 selection ready flag        */
#define PWR_FLAG_R2RDY                 (0x4U)                        /*!< Voltage range 2 selection ready flag        */
#define PWR_FLAG_BOOSTRDY              (0x5U)                        /*!< EPOD booster ready flag                     */
#define PWR_FLAG_PVDO                  (0x6U)                        /*!< VDD voltage detector output flag            */
#define PWR_FLAG_REGS                  (0x7U)                        /*!< Regulator selection flag                    */
#define PWR_FLAG_VDDA1RDY              (0x8U)                        /*!< VDDA ready versus 1.6V voltage monitor flag */
#define PWR_FLAG_VDDA2RDY              (0x9U)                        /*!< VDDA ready versus 1.8V voltage monitor flag */
#if defined(PWR_SVMSR_VDDIO2RDY)
#define PWR_FLAG_VDDIO2RDY             (0xAU)                        /*!< VDDIO2 ready voltage monitor flag           */
#endif /* PWR_SVMSR_VDDIO2RDY */
#define PWR_FLAG_VDDUSBRDY             (0xBU)                        /*!< VDDUSB ready voltage monitor flag           */
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Lines_Flags PWR Wakeup Lines Flags
  * @{
  */
#define PWR_WAKEUP_FLAG1               (0x10U)                                 /*!< Wakeup flag 1   */
#define PWR_WAKEUP_FLAG2               (0x20U)                                 /*!< Wakeup flag 2   */
#define PWR_WAKEUP_FLAG3               (0x30U)                                 /*!< Wakeup flag 3   */
#define PWR_WAKEUP_FLAG4               (0x40U)                                 /*!< Wakeup flag 4   */
#define PWR_WAKEUP_FLAG5               (0x50U)                                 /*!< Wakeup flag 5   */
#define PWR_WAKEUP_FLAG6               (0x60U)                                 /*!< Wakeup flag 6   */
#define PWR_WAKEUP_FLAG7               (0x70U)                                 /*!< Wakeup flag 7   */
#define PWR_WAKEUP_FLAG8               (0x80U)                                 /*!< Wakeup flag 8   */
#define PWR_WAKEUP_FLAG9               (0x90U)                                 /*!< Wakeup flag 9   */
#define PWR_WAKEUP_FLAG10              (0xA0U)                                 /*!< Wakeup flag 10  */
#define PWR_WAKEUP_ALL_FLAG            (0xB0U)                                 /*!< Wakeup flag all */
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Line_ PWR Wake Up Lines
  * @{
  */

/* (Default polarity and default line selection) */
#define PWR_WAKEUP_LINE1               PWR_WUCR1_WUPEN1                     /*!< PA0  : Wakeup line 1 (high polarity) */
#define PWR_WAKEUP_LINE2               PWR_WUCR1_WUPEN2                     /*!< PA4  : Wakeup line 2 (high polarity) */
#define PWR_WAKEUP_LINE3               PWR_WUCR1_WUPEN3                     /*!< PE6  : Wakeup line 3 (high polarity) */
#define PWR_WAKEUP_LINE4               PWR_WUCR1_WUPEN4                     /*!< PA2  : Wakeup line 4 (high polarity) */
#define PWR_WAKEUP_LINE5               PWR_WUCR1_WUPEN5                     /*!< PC5  : Wakeup line 4 (high polarity) */
#define PWR_WAKEUP_LINE6               PWR_WUCR1_WUPEN6                     /*!< PB5  : Wakeup line 6 (high polarity) */
#define PWR_WAKEUP_LINE7               PWR_WUCR1_WUPEN7                     /*!< PB15 : Wakeup line 7 (high polarity) */
#define PWR_WAKEUP_LINE8               PWR_WUCR1_WUPEN8                     /*!< reserved                             */
#define PWR_WAKEUP_LINE9               PWR_WUCR1_WUPEN9                     /*!< I3C1 reset pattern                   */
#define PWR_WAKEUP_LINE10              PWR_WUCR1_WUPEN10                    /*!< I3C2 reset pattern                   */

/* PWR Wakeup line polarity */
#define PWR_WAKEUP_POLARITY_HIGH       (0U)                                 /*!< High polarity */
#define PWR_WAKEUP_POLARITY_LOW        (1U)                                 /*!< Low polarity  */

/* PWR Wakeup line selection */
#define PWR_WAKEUP_SELECT_0            (0U)                                 /*!< Wake up 0 selected */
#define PWR_WAKEUP_SELECT_1            (1U)                                 /*!< Wake up 1 selected */
#define PWR_WAKEUP_SELECT_2            (2U)                                 /*!< Wake up 2 selected */
#define PWR_WAKEUP_SELECT_3            (3U)                                 /*!< Wake up 3 selected */
/**
  * @}
  */

/** @defgroup PWR_Secure_Items PWR Secure Items
  * @{
  */
#define PWR_WKUP1                      PWR_SECCFGR_WUP1SEC    /*!< WUP1 secure protection                             */
#define PWR_WKUP2                      PWR_SECCFGR_WUP2SEC    /*!< WUP2 secure protection                             */
#define PWR_WKUP3                      PWR_SECCFGR_WUP3SEC    /*!< WUP3 secure protection                             */
#define PWR_WKUP4                      PWR_SECCFGR_WUP4SEC    /*!< WUP4 secure protection                             */
#define PWR_WKUP5                      PWR_SECCFGR_WUP5SEC    /*!< WUP5 secure protection                             */
#define PWR_WKUP6                      PWR_SECCFGR_WUP6SEC    /*!< WUP6 secure protection                             */
#define PWR_WKUP7                      PWR_SECCFGR_WUP7SEC    /*!< WUP7 secure protection                             */
#define PWR_WKUP8                      PWR_SECCFGR_WUP8SEC    /*!< WUP8 secure protection                             */
#define PWR_WKUP9                      PWR_SECCFGR_WUP9SEC    /*!< WUP9 secure protection                             */
#define PWR_WKUP10                     PWR_SECCFGR_WUP10SEC   /*!< WUP10 secure protection                            */
#define PWR_LPM                        PWR_SECCFGR_LPMSEC     /*!< Low power modes secure protection                  */
#define PWR_VDM                        PWR_SECCFGR_VDMSEC     /*!< Voltage detection and monitoring secure protection */
#define PWR_VB                         PWR_SECCFGR_VBSEC      /*!< Backup domain secure protection                    */
#define PWR_APC                        PWR_SECCFGR_APCSEC     /*!< Pull-up/pull-down secure protection                */
#define PWR_ALL                        (PWR_WKUP1 | PWR_WKUP2 | PWR_WKUP3 | PWR_WKUP4 | PWR_WKUP5  |\
                                        PWR_WKUP6 | PWR_WKUP7 | PWR_WKUP8 | PWR_WKUP9 | PWR_WKUP10 |\
                                        PWR_LPM   | PWR_VDM   | PWR_VB    | PWR_APC)
/**
  * @}
  */

/** @defgroup PWR_Attributes PWR Attributes
  * @brief PWR Privilege/NPrivilege and Secure/NSecure Attributes
  * @{
  */
#define PWR_NSEC_PRIV                  (PWR_ITEM_ATTR_NSEC_PRIV_MASK | 0x01U)  /*!< NSecure and Privileged attribute  */
#define PWR_NSEC_NPRIV                 PWR_ITEM_ATTR_NSEC_PRIV_MASK            /*!< NSecure and NPrivileged attribute */
#define PWR_SEC_PRIV                   (PWR_ITEM_ATTR_SEC_PRIV_MASK  | 0x02U)  /*!< Secure and Privileged attribute   */
#define PWR_SEC_NPRIV                  PWR_ITEM_ATTR_SEC_PRIV_MASK             /*!< Secure and NPrivileged attribute  */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup PWR_Exported_Macros PWR Exported Macros
  * @{
  */

#if defined(PWR_SVMSR_VDDIO2RDY)
/** @brief  Check PWR flags are set or not.
  * @param  __FLAG__ : Specifies the flag to check.
  *                    This parameter can be one of the following values when available :
  *                    @arg @ref PWR_FLAG_STOPF     : Stop flag.
  *                                                   Indicates that the device was resumed from Stop mode.
  *                    @arg @ref PWR_FLAG_SBF       : Standby flag.
  *                                                   Indicates that the device was resumed from Standby mode.
  *                    @arg @ref PWR_FLAG_R1RDY     : Ready bit for VCORE voltage range 1.
  *                                                   Indicates that Vcore is equal or above VOS range 1 level.
  *                    @arg @ref PWR_FLAG_R2RDY     : Ready bit for VCORE voltage range 2.
  *                                                   Indicates that Vcore is equal or above VOS range 2 level.
  *                    @arg @ref PWR_FLAG_BOOSTRDY  : EPOD booster ready flag.
  *                                                   Indicates that the Power booster is ready.
  *                    @arg @ref PWR_FLAG_PVDO      : Voltage detector output flag.
  *                                                   Indicates that Vdd is equal or above
  *                                                   the PVD threshold selected by PVDLS.
  *                    @arg @ref PWR_FLAG_REGS      : Regulator selection flag.
  *                                                   Indicates the regulator selected.
  *                    @arg @ref PWR_FLAG_VDDA1RDY  : VDDA ready versus 1.6V voltage monitor flag.
  *                                                   Indicates VDDA is equal or above the threshold of the
  *                                                   VDDA voltage monitor 1 (around 1.6V).
  *                    @arg @ref PWR_FLAG_VDDA2RDY  : VDDA ready versus 1.8V voltage monitor flag.
  *                                                   Indicates VDDA is equal or above the threshold of the
  *                                                   VDDA voltage monitor 1 (around 1.8V).
  *                    @arg @ref PWR_FLAG_VDDIO2RDY  : VDDIO2 ready flag.
  *                                                   Indicates VDDIO2 is equal or above the threshold of the
  *                                                   VDDIO2 voltage monitor.
  *                    @arg @ref PWR_FLAG_VDDUSBRDY  : VDDUSB ready flag.
  *                                                   Indicates VDDUSB is equal or above the threshold of the
  *                                                   VDDUSB voltage monitor.
  *                    @arg @ref PWR_WAKEUP_FLAG1   : Wakeup flag 1.
  *                                                   Indicates that a wakeup event was received from the WKUP line 1.
  *                    @arg @ref PWR_WAKEUP_FLAG2   : Wakeup flag 2.
  *                                                   Indicates that a wakeup event was received from the WKUP line 2.
  *                    @arg @ref PWR_WAKEUP_FLAG3   : Wakeup flag 3.
  *                                                   Indicates that a wakeup event was received from the WKUP line 3.
  *                    @arg @ref PWR_WAKEUP_FLAG4   : Wakeup flag 4.
  *                                                   Indicates that a wakeup event was received from the WKUP line 4.
  *                    @arg @ref PWR_WAKEUP_FLAG5   : Wakeup flag 5.
  *                                                   Indicates that a wakeup event was received from the WKUP line 5.
  *                    @arg @ref PWR_WAKEUP_FLAG6   : Wakeup flag 6.
  *                                                   Indicates that a wakeup event was received from the WKUP line 6.
  *                    @arg @ref PWR_WAKEUP_FLAG7   : Wakeup flag 7.
  *                                                   Indicates that a wakeup event was received from the WKUP line 7.
  *                    @arg @ref PWR_WAKEUP_FLAG8   : Wakeup flag 8.
  *                                                   Indicates that a wakeup event was received from the WKUP line 8.
  *                    @arg @ref PWR_WAKEUP_FLAG9   : Wakeup flag 9.
  *                                                   Indicates that a wakeup event was received from the WKUP line 9.
  *                    @arg @ref PWR_WAKEUP_FLAG10  : Wakeup flag 10.
  *                                                   Indicates that a wakeup event was received from the WKUP line 10.
  * @retval The state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_PWR_GET_FLAG(__FLAG__)                                                                         \
  (                                                                                                          \
    ((__FLAG__) == PWR_FLAG_STOPF)     ? (READ_BIT(PWR->SR, PWR_SR_STOPF)           == PWR_SR_STOPF)       : \
    ((__FLAG__) == PWR_FLAG_SBF)       ? (READ_BIT(PWR->SR, PWR_SR_SBF)             == PWR_SR_SBF)         : \
    ((__FLAG__) == PWR_FLAG_R1RDY)     ? (READ_BIT(PWR->VOSR, PWR_VOSR_R1RDY)       == PWR_VOSR_R1RDY)     : \
    ((__FLAG__) == PWR_FLAG_R2RDY)     ? (READ_BIT(PWR->VOSR, PWR_VOSR_R2RDY)       == PWR_VOSR_R2RDY)     : \
    ((__FLAG__) == PWR_FLAG_BOOSTRDY)  ? (READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY)    == PWR_VOSR_BOOSTRDY)  : \
    ((__FLAG__) == PWR_FLAG_PVDO)      ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO)      == PWR_SVMSR_PVDO)     : \
    ((__FLAG__) == PWR_FLAG_REGS)      ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_REGS)      == PWR_SVMSR_REGS)     : \
    ((__FLAG__) == PWR_FLAG_VDDA1RDY)  ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA1RDY)  == PWR_SVMSR_VDDA1RDY) : \
    ((__FLAG__) == PWR_FLAG_VDDA2RDY)  ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA2RDY)  == PWR_SVMSR_VDDA2RDY) : \
    ((__FLAG__) == PWR_FLAG_VDDIO2RDY) ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDIO2RDY) == PWR_SVMSR_VDDIO2RDY): \
    ((__FLAG__) == PWR_FLAG_VDDUSBRDY) ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDUSBRDY) == PWR_SVMSR_VDDUSBRDY): \
    ((__FLAG__) == PWR_WAKEUP_FLAG1)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF1)        == PWR_WUSR_WUF1)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG2)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF2)        == PWR_WUSR_WUF2)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG3)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF3)        == PWR_WUSR_WUF3)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG4)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF4)        == PWR_WUSR_WUF4)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG5)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF5)        == PWR_WUSR_WUF5)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG6)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF6)        == PWR_WUSR_WUF6)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG7)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF7)        == PWR_WUSR_WUF7)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG8)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF8)        == PWR_WUSR_WUF8)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG9)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF9)        == PWR_WUSR_WUF9)      : \
    (READ_BIT(PWR->WUSR, PWR_WUSR_WUF10) == PWR_WUSR_WUF10))
#else
/** @brief  Check PWR flags are set or not.
  * @param  __FLAG__ : Specifies the flag to check.
  *                    This parameter can be one of the following values when available :
  *                    @arg @ref PWR_FLAG_STOPF     : Stop flag.
  *                                                   Indicates that the device was resumed from Stop mode.
  *                    @arg @ref PWR_FLAG_SBF       : Standby flag.
  *                                                   Indicates that the device was resumed from Standby mode.
  *                    @arg @ref PWR_FLAG_R1RDY     : Ready bit for VCORE voltage range 1.
  *                                                   Indicates that Vcore is equal or above VOS range 1 level.
  *                    @arg @ref PWR_FLAG_R2RDY     : Ready bit for VCORE voltage range 2.
  *                                                   Indicates that Vcore is equal or above VOS range 2 level.
  *                    @arg @ref PWR_FLAG_BOOSTRDY  : EPOD booster ready flag.
  *                                                   Indicates that the Power booster is ready.
  *                    @arg @ref PWR_FLAG_PVDO      : Voltage detector output flag.
  *                                                   Indicates that Vdd is equal or above
  *                                                   the PVD threshold selected by PVDLS.
  *                    @arg @ref PWR_FLAG_REGS      : Regulator selection flag.
  *                                                   Indicates the regulator selected.
  *                    @arg @ref PWR_FLAG_VDDA1RDY  : VDDA ready versus 1.6V voltage monitor flag.
  *                                                   Indicates VDDA is equal or above the threshold of the
  *                                                   VDDA voltage monitor 1 (around 1.6V).
  *                    @arg @ref PWR_FLAG_VDDA2RDY  : VDDA ready versus 1.8V voltage monitor flag.
  *                                                   Indicates VDDA is equal or above the threshold of the
  *                                                   VDDA voltage monitor 1 (around 1.8V).
  *                    @arg @ref PWR_FLAG_VDDUSBRDY  : VDDUSB ready flag.
  *                                                   Indicates VDDUSB is equal or above the threshold of the
  *                                                   VDDUSB voltage monitor.
  *                    @arg @ref PWR_WAKEUP_FLAG1   : Wakeup flag 1.
  *                                                   Indicates that a wakeup event was received from the WKUP line 1.
  *                    @arg @ref PWR_WAKEUP_FLAG2   : Wakeup flag 2.
  *                                                   Indicates that a wakeup event was received from the WKUP line 2.
  *                    @arg @ref PWR_WAKEUP_FLAG3   : Wakeup flag 3.
  *                                                   Indicates that a wakeup event was received from the WKUP line 3.
  *                    @arg @ref PWR_WAKEUP_FLAG4   : Wakeup flag 4.
  *                                                   Indicates that a wakeup event was received from the WKUP line 4.
  *                    @arg @ref PWR_WAKEUP_FLAG5   : Wakeup flag 5.
  *                                                   Indicates that a wakeup event was received from the WKUP line 5.
  *                    @arg @ref PWR_WAKEUP_FLAG6   : Wakeup flag 6.
  *                                                   Indicates that a wakeup event was received from the WKUP line 6.
  *                    @arg @ref PWR_WAKEUP_FLAG7   : Wakeup flag 7.
  *                                                   Indicates that a wakeup event was received from the WKUP line 7.
  *                    @arg @ref PWR_WAKEUP_FLAG8   : Wakeup flag 8.
  *                                                   Indicates that a wakeup event was received from the WKUP line 8.
  *                    @arg @ref PWR_WAKEUP_FLAG9   : Wakeup flag 9.
  *                                                   Indicates that a wakeup event was received from the WKUP line 9.
  *                    @arg @ref PWR_WAKEUP_FLAG10  : Wakeup flag 10.
  *                                                   Indicates that a wakeup event was received from the WKUP line 10.
  * @retval The state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_PWR_GET_FLAG(__FLAG__)                                                                         \
  (                                                                                                          \
    ((__FLAG__) == PWR_FLAG_STOPF)     ? (READ_BIT(PWR->SR, PWR_SR_STOPF)           == PWR_SR_STOPF)       : \
    ((__FLAG__) == PWR_FLAG_SBF)       ? (READ_BIT(PWR->SR, PWR_SR_SBF)             == PWR_SR_SBF)         : \
    ((__FLAG__) == PWR_FLAG_R1RDY)     ? (READ_BIT(PWR->VOSR, PWR_VOSR_R1RDY)       == PWR_VOSR_R1RDY)     : \
    ((__FLAG__) == PWR_FLAG_R2RDY)     ? (READ_BIT(PWR->VOSR, PWR_VOSR_R2RDY)       == PWR_VOSR_R2RDY)     : \
    ((__FLAG__) == PWR_FLAG_BOOSTRDY)  ? (READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY)    == PWR_VOSR_BOOSTRDY)  : \
    ((__FLAG__) == PWR_FLAG_PVDO)      ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO)      == PWR_SVMSR_PVDO)     : \
    ((__FLAG__) == PWR_FLAG_REGS)      ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_REGS)      == PWR_SVMSR_REGS)     : \
    ((__FLAG__) == PWR_FLAG_VDDA1RDY)  ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA1RDY)  == PWR_SVMSR_VDDA1RDY) : \
    ((__FLAG__) == PWR_FLAG_VDDA2RDY)  ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA2RDY)  == PWR_SVMSR_VDDA2RDY) : \
    ((__FLAG__) == PWR_FLAG_VDDUSBRDY) ? (READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDUSBRDY) == PWR_SVMSR_VDDUSBRDY): \
    ((__FLAG__) == PWR_WAKEUP_FLAG1)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF1)        == PWR_WUSR_WUF1)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG2)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF2)        == PWR_WUSR_WUF2)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG3)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF3)        == PWR_WUSR_WUF3)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG4)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF4)        == PWR_WUSR_WUF4)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG5)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF5)        == PWR_WUSR_WUF5)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG6)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF6)        == PWR_WUSR_WUF6)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG7)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF7)        == PWR_WUSR_WUF7)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG8)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF8)        == PWR_WUSR_WUF8)      : \
    ((__FLAG__) == PWR_WAKEUP_FLAG9)   ? (READ_BIT(PWR->WUSR, PWR_WUSR_WUF9)        == PWR_WUSR_WUF9)      : \
    (READ_BIT(PWR->WUSR, PWR_WUSR_WUF10) == PWR_WUSR_WUF10))
#endif /* PWR_SVMSR_VDDIO2RDY */

/** @brief  Clear PWR flags.
  * @param  __FLAG__ : Specifies the flag to clear.
  *                    This parameter can be one of the following values when available:
  *                    @arg @ref PWR_FLAG_STOPF      : Stop flag.
  *                                                    Indicates that the device was resumed from Stop mode.
  *                    @arg @ref PWR_FLAG_SBF        : Standby flag.
  *                                                    Indicates that the device was resumed from Standby mode.
  *                    @arg @ref PWR_WAKEUP_FLAG1    : Wakeup flag 1.
  *                                                    Indicates that a wakeup event was received from the WKUP line 1.
  *                    @arg @ref PWR_WAKEUP_FLAG2    : Wakeup flag 2.
  *                                                    Indicates that a wakeup event was received from the WKUP line 2.
  *                    @arg @ref PWR_WAKEUP_FLAG3    : Wakeup flag 3.
  *                                                    Indicates that a wakeup event was received from the WKUP line 3.
  *                    @arg @ref PWR_WAKEUP_FLAG4    : Wakeup flag 4.
  *                                                    Indicates that a wakeup event was received from the WKUP line 4.
  *                    @arg @ref PWR_WAKEUP_FLAG5    : Wakeup flag 5.
  *                                                    Indicates that a wakeup event was received from the WKUP line 5.
  *                    @arg @ref PWR_WAKEUP_FLAG6    : Wakeup flag 6.
  *                                                    Indicates that a wakeup event was received from the WKUP line 6.
  *                    @arg @ref PWR_WAKEUP_FLAG7    : Wakeup flag 7.
  *                                                    Indicates that a wakeup event was received from the WKUP line 7.
  *                    @arg @ref PWR_WAKEUP_FLAG8    : Wakeup flag 8.
  *                                                    Indicates that a wakeup event was received from the WKUP line 8.
  *                    @arg @ref PWR_WAKEUP_FLAG9    : Wakeup flag 9.
  *                                                    Indicates that a wakeup event was received from the WKUP line 9.
  *                    @arg @ref PWR_WAKEUP_FLAG10   : Wakeup flag 10.
  *                                                    Indicates that a wakeup event was received from the WKUP line 10.
  *                    @arg @ref PWR_WAKEUP_ALL_FLAG : all Wakeup flags.
  * @retval None.
  */
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)                                             \
(                                                                                  \
    ((__FLAG__) == PWR_FLAG_STOPF)    ? (SET_BIT(PWR->SR, PWR_SR_CSSF))          : \
    ((__FLAG__) == PWR_FLAG_SBF)      ? (SET_BIT(PWR->SR, PWR_SR_CSSF))          : \
    ((__FLAG__) == PWR_WAKEUP_FLAG1)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF1)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG2)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF2)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG3)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF3)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG4)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF4)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG5)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF5)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG6)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF6)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG7)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF7)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG8)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF8)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG9)  ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF9)) : \
    ((__FLAG__) == PWR_WAKEUP_FLAG10) ? (WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF10)): \
    (WRITE_REG(PWR->WUSCR, (PWR_WUSCR_CWUF1 | PWR_WUSCR_CWUF2 | PWR_WUSCR_CWUF3 | PWR_WUSCR_CWUF4 | PWR_WUSCR_CWUF5 | \
                            PWR_WUSCR_CWUF6 | PWR_WUSCR_CWUF7 | PWR_WUSCR_CWUF8 | PWR_WUSCR_CWUF9 | PWR_WUSCR_CWUF10))))

/**
  * @brief  Enable the PVD Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT() SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_IT() CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT() SET_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT() CLEAR_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE() SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE() CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE() SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do                                                    \
  {                                                     \
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();            \
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Disable the PVD Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do                                                     \
  {                                                      \
    __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();            \
    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Generate a Software Interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Check whether or not the PVD EXTI interrupt Rising flag is set.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_RISING_FLAG() (EXTI->RPR1 & PWR_EXTI_LINE_PVD)

/**
  * @brief  Check whether or not the PVD EXTI interrupt Falling flag is set.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FALLING_FLAG() (EXTI->FPR1 & PWR_EXTI_LINE_PVD)

/**
  * @brief  Clear the PVD EXTI interrupt Rising flag.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_RISING_FLAG() WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Clear the PVD EXTI interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FALLING_FLAG()   WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the USBVM Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_ENABLE_IT() SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Disable the USBVM Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_DISABLE_IT() CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Enable the USBVM Event Line.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_ENABLE_EVENT() SET_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Disable the USBVM Event Line.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_DISABLE_EVENT() CLEAR_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Enable the USBVM Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_ENABLE_RISING_EDGE() SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Disable the USBVM Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_DISABLE_RISING_EDGE() CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Enable the USBVM Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_ENABLE_FALLING_EDGE() SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Disable the USBVM Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Enable the USBVM Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do                                                      \
  {                                                       \
    __HAL_PWR_USBVM_EXTI_ENABLE_RISING_EDGE();            \
    __HAL_PWR_USBVM_EXTI_ENABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Disable the USBVM Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do                                                       \
  {                                                        \
    __HAL_PWR_USBVM_EXTI_DISABLE_RISING_EDGE();            \
    __HAL_PWR_USBVM_EXTI_DISABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Generate a Software Interrupt on USBVM EXTI Line.
  * @retval None
  */
#define __HAL_PWR_USBVM_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Check whether the specified USBVM EXTI flag is set or not.
  * @retval EXTI USBVM Line Status.
  */
#define __HAL_PWR_USBVM_EXTI_GET_FLAG() ((EXTI->RPR1 | EXTI->FPR1) & PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Clear the USBVM interrupt Rising flag.
  * @retval None.
  */
#define __HAL_PWR_USBVM_EXTI_CLEAR_RISING_FLAG() WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVM_VDDUSB)

/**
  * @brief  Clear the USBVM interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_USBVM_EXTI_CLEAR_FALLING_FLAG() WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVM_VDDUSB)

#if defined(PWR_SVMCR_IO2VMEN)
/**
  * @brief  Enable the IO2VM Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_ENABLE_IT() SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Disable the IO2VM Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_DISABLE_IT() CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Enable the IO2VM Event Line.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_ENABLE_EVENT() SET_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Disable the IO2VM Event Line.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_DISABLE_EVENT() CLEAR_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Enable the IO2VM Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_ENABLE_RISING_EDGE() SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Disable the IO2VM Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_DISABLE_RISING_EDGE() CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Enable the IO2VM Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_ENABLE_FALLING_EDGE() SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Disable the IO2VM Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Enable the IO2VM Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do                                                      \
  {                                                       \
    __HAL_PWR_IO2VM_EXTI_ENABLE_RISING_EDGE();            \
    __HAL_PWR_IO2VM_EXTI_ENABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Disable the IO2VM Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do                                                       \
  {                                                        \
    __HAL_PWR_IO2VM_EXTI_DISABLE_RISING_EDGE();            \
    __HAL_PWR_IO2VM_EXTI_DISABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Generate a Software Interrupt on IO2VM EXTI Line.
  * @retval None
  */
#define __HAL_PWR_IO2VM_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Check whether the specified IO2VM EXTI flag is set or not.
  * @retval EXTI IO2VM Line Status.
  */
#define __HAL_PWR_IO2VM_EXTI_GET_FLAG() ((EXTI->RPR1 | EXTI->FPR1) & PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Clear the IO2VM interrupt Rising flag.
  * @retval None.
  */
#define __HAL_PWR_IO2VM_EXTI_CLEAR_RISING_FLAG() WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVM_VDDIO2)

/**
  * @brief  Clear the IO2VM interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_IO2VM_EXTI_CLEAR_FALLING_FLAG() WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVM_VDDIO2)
#endif /* PWR_SVMCR_IO2VMEN */

/**
  * @brief  Enable the ADCVM1 Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_ENABLE_IT() SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Disable the ADCVM1 Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_DISABLE_IT() CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Enable the ADCVM1 Event Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_ENABLE_EVENT() SET_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Disable the ADCVM1 Event Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_DISABLE_EVENT() CLEAR_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Enable the ADCVM1 Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_ENABLE_RISING_EDGE() SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Disable the ADCVM1 Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_DISABLE_RISING_EDGE() CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Enable the ADCVM1 Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_ENABLE_FALLING_EDGE() SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Disable the ADCVM1 Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Enable the ADCVM1 Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do                                                       \
  {                                                        \
    __HAL_PWR_ADCVM1_EXTI_ENABLE_RISING_EDGE();            \
    __HAL_PWR_ADCVM1_EXTI_ENABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Disable the ADCVM1 Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do                                                        \
  {                                                         \
    __HAL_PWR_ADCVM1_EXTI_DISABLE_RISING_EDGE();            \
    __HAL_PWR_ADCVM1_EXTI_DISABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Generate a Software Interrupt on ADCVM1 EXTI Line.
  * @retval None
  */
#define __HAL_PWR_ADCVM1_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Check whether the specified ADCVM1 EXTI flag is set or not.
  * @retval EXTI ADCVM1 Line Status.
  */
#define __HAL_PWR_ADCVM1_EXTI_GET_FLAG() ((EXTI->RPR1 | EXTI->FPR1) & PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Clear the ADCVM1 interrupt Rising flag.
  * @retval None.
  */
#define __HAL_PWR_ADCVM1_EXTI_CLEAR_RISING_FLAG() WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Clear the ADCVM1 interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_ADCVM1_EXTI_CLEAR_FALLING_FLAG() WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVM_VDDA1)

/**
  * @brief  Enable the ADCVM2 Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_ENABLE_IT() SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Disable the ADCVM2 Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_DISABLE_IT() CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Enable the ADCVM2 Event Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_ENABLE_EVENT() SET_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Disable the ADCVM2 Event Line.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_DISABLE_EVENT() CLEAR_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Enable the ADCVM2 Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_ENABLE_RISING_EDGE() SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Disable the ADCVM2 Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_DISABLE_RISING_EDGE() CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Enable the ADCVM2 Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_ENABLE_FALLING_EDGE() SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Disable the ADCVM2 Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Enable the ADCVM2 Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do                                                       \
  {                                                        \
    __HAL_PWR_ADCVM2_EXTI_ENABLE_RISING_EDGE();            \
    __HAL_PWR_ADCVM2_EXTI_ENABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Disable the ADCVM2 Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do                                                        \
  {                                                         \
    __HAL_PWR_ADCVM2_EXTI_DISABLE_RISING_EDGE();            \
    __HAL_PWR_ADCVM2_EXTI_DISABLE_FALLING_EDGE();           \
  } while(0)

/**
  * @brief  Generate a Software Interrupt on ADCVM2 EXTI Line.
  * @retval None
  */
#define __HAL_PWR_ADCVM2_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Check whether the specified ADCVM2 EXTI flag is set or not.
  * @retval EXTI ADCVM2 Line Status.
  */
#define __HAL_PWR_ADCVM2_EXTI_GET_FLAG() ((EXTI->RPR1 | EXTI->FPR1) & PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Clear the ADCVM2 interrupt Rising flag.
  * @retval None.
  */
#define __HAL_PWR_ADCVM2_EXTI_CLEAR_RISING_FLAG() WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVM_VDDA2)

/**
  * @brief  Clear the ADCVM2 interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_ADCVM2_EXTI_CLEAR_FALLING_FLAG() WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVM_VDDA2)
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/

/** @addtogroup PWR_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_PVD_EXTI_Line PWR PVD EXTI Line
  * @{
  */
#define PWR_EXTI_LINE_PVD              EXTI_IMR1_IM16                          /*!< PVD EXTI Line */
/**
  * @}
  */

/** @defgroup PWR_PVM_EXTI PWR PVM interrupts and event lines defines
  * @{
  */
#define PWR_EXTI_LINE_PVM_VDDUSB       EXTI_IMR1_IM19       /*!< PVM VDDUSB voltage monitor EXTI Line */
#if defined(PWR_SVMCR_IO2VMEN)
#define PWR_EXTI_LINE_PVM_VDDIO2       EXTI_IMR1_IM20       /*!< PVM VDDIO2 voltage monitor EXTI Line */
#endif /* PWR_SVMCR_IO2VMEN */
#define PWR_EXTI_LINE_PVM_VDDA1        EXTI_IMR1_IM21       /*!< PVM VDDA voltage monitor 1 EXTI Line */
#define PWR_EXTI_LINE_PVM_VDDA2        EXTI_IMR1_IM22       /*!< PVM VDDA voltage monitor 2 EXTI Line */
/**
  * @}
  */

/** @defgroup PWR_PVM_Type PWR Voltage Monitoring Type
  * @{
  */
#define PWR_VDDUSB_VM                  (0U)                 /*!< Independent USB voltage monitor    */
#if defined(PWR_SVMCR_IO2VMEN)
#define PWR_VDDIO2_VM                  (1U)                 /*!< Independent VDDIO2 voltage monitor */
#endif /* PWR_SVMCR_IO2VMEN */
#define PWR_VDDA_VM1                   (2U)                 /*!< Independent VDDA voltage monitor 1 */
#define PWR_VDDA_VM2                   (3U)                 /*!< Independent VDDA voltage monitor 2 */
/**
  * @}
  */

/* Defines attribute */
#define PWR_ITEM_ATTR_NSEC_PRIV_MASK   (0x10U)              /*!< NSecure Privilege / NPrivilege attribute item mask */
#define PWR_ITEM_ATTR_SEC_PRIV_MASK    (0x20U)              /*!< Secure Privilege / NPrivilege attribute item mask  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @addtogroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/* Stop mode entry check macro */
#define IS_PWR_STOPMODE(__MODE__)  (((__MODE__) == PWR_LOWPOWERMODE_STOP0) ||\
                                    ((__MODE__) == PWR_LOWPOWERMODE_STOP1) ||\
                                    ((__MODE__) == PWR_LOWPOWERMODE_STOP2) ||\
                                    ((__MODE__) == PWR_LOWPOWERMODE_STOP3))

/* Wake up lines check macro */
#define IS_PWR_WAKEUP_LINE(__LINE__) (((__LINE__) == PWR_WAKEUP_LINE1) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE2) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE3) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE4) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE5) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE6) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE7) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE8) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE9) ||\
                                      ((__LINE__) == PWR_WAKEUP_LINE10))

/* Wake up lines polarity check macro */
#define IS_PWR_WAKEUP_POLARITY(__POLARITY__) (((__POLARITY__) == PWR_WAKEUP_POLARITY_HIGH) ||\
                                              ((__POLARITY__) == PWR_WAKEUP_POLARITY_LOW))

/* Wake up lines selection check macro */
#define IS_PWR_WAKEUP_SELECTION(__SELECTION__) (((__SELECTION__) == PWR_WAKEUP_SELECT_0) ||\
                                                ((__SELECTION__) == PWR_WAKEUP_SELECT_1) ||\
                                                ((__SELECTION__) == PWR_WAKEUP_SELECT_2) ||\
                                                ((__SELECTION__) == PWR_WAKEUP_SELECT_3))


/* PVD level check macro */
#define IS_PWR_PVD_LEVEL(__LEVEL__) (((__LEVEL__) == PWR_PVDLEVEL_0) || ((__LEVEL__) == PWR_PVDLEVEL_1) || \
                                     ((__LEVEL__) == PWR_PVDLEVEL_2) || ((__LEVEL__) == PWR_PVDLEVEL_3) || \
                                     ((__LEVEL__) == PWR_PVDLEVEL_4) || ((__LEVEL__) == PWR_PVDLEVEL_5) || \
                                     ((__LEVEL__) == PWR_PVDLEVEL_6) || ((__LEVEL__) == PWR_PVDLEVEL_7))

/* PVD mode check macro */
#define IS_PWR_PVD_MODE(__MODE__) (((__MODE__) == PWR_PVD_MODE_NORMAL)               ||\
                                   ((__MODE__) == PWR_PVD_MODE_IT_RISING)            ||\
                                   ((__MODE__) == PWR_PVD_MODE_IT_FALLING)           ||\
                                   ((__MODE__) == PWR_PVD_MODE_IT_RISING_FALLING)    ||\
                                   ((__MODE__) == PWR_PVD_MODE_EVENT_RISING)         ||\
                                   ((__MODE__) == PWR_PVD_MODE_EVENT_FALLING)        ||\
                                   ((__MODE__) == PWR_PVD_MODE_EVENT_RISING_FALLING))

/* Sleep mode entry check macro */
#define IS_PWR_SLEEP_ENTRY(__ENTRY__) (((__ENTRY__) == PWR_SLEEPENTRY_WFI) ||\
                                       ((__ENTRY__) == PWR_SLEEPENTRY_WFE) ||\
                                       ((__ENTRY__) == PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR))

/* Stop mode entry check macro */
#define IS_PWR_STOP_ENTRY(__ENTRY__) (((__ENTRY__) == PWR_STOPENTRY_WFI) ||\
                                      ((__ENTRY__) == PWR_STOPENTRY_WFE) ||\
                                      ((__ENTRY__) == PWR_STOPENTRY_WFE_NO_EVT_CLEAR))

/* PWR items check macro */
#define IS_PWR_ITEMS_ATTRIBUTES(__ITEM__) ((((__ITEM__) & (~PWR_ALL)) == 0U) && ((__ITEM__) != 0U))

#if defined (CPU_IN_SECURE_STATE)
/* PWR attribute check macro (Secure) */
#define IS_PWR_ATTRIBUTES(__ATTRIBUTES__) ((((~(((__ATTRIBUTES__)& \
                                                 0xF0U) >> 4U)) & ((__ATTRIBUTES__) & 0x0FU)) == 0U) && \
                                           (((__ATTRIBUTES__) & 0xFFFFFFCCU) == 0U))
#else
/* PWR attribute check macro (NSecure) */
#define IS_PWR_ATTRIBUTES(__ATTRIBUTES__) (((__ATTRIBUTES__) == PWR_NSEC_NPRIV) || ((__ATTRIBUTES__) == PWR_NSEC_PRIV))
#endif /* defined (CPU_IN_SECURE_STATE) */

/* Check PVM type parameter */
#if defined(PWR_SVMCR_IO2VMEN)
#define IS_PWR_PVM_TYPE(__TYPE__)  \
  (((__TYPE__) == PWR_VDDUSB_VM) ||\
   ((__TYPE__) == PWR_VDDIO2_VM) ||\
   ((__TYPE__) == PWR_VDDA_VM1) ||\
   ((__TYPE__) == PWR_VDDA_VM2))
#else
#define IS_PWR_PVM_TYPE(__TYPE__)  \
  (((__TYPE__) == PWR_VDDUSB_VM) ||\
   ((__TYPE__) == PWR_VDDA_VM1) ||\
   ((__TYPE__) == PWR_VDDA_VM2))
#endif /* PWR_SVMCR_IO2VMEN */

/* Check PVM mode check parameter */
#define IS_PWR_PVM_MODE(__MODE__)                   \
  (((__MODE__) == PWR_PVM_MODE_NORMAL)            ||\
   ((__MODE__) == PWR_PVM_MODE_IT_RISING)         ||\
   ((__MODE__) == PWR_PVM_MODE_IT_FALLING)        ||\
   ((__MODE__) == PWR_PVM_MODE_IT_RISING_FALLING) ||\
   ((__MODE__) == PWR_PVM_MODE_EVENT_RISING)      ||\
   ((__MODE__) == PWR_PVM_MODE_EVENT_FALLING)     ||\
   ((__MODE__) == PWR_PVM_MODE_EVENT_RISING_FALLING))
/**
  * @}
  */

/* Include PWR HAL Extended module */
#include "stm32u3xx_hal_pwr_ex.h"

/* Exported functions --------------------------------------------------------*/

/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2
  * @{
  */
/* Programmable voltage detector functions ************************************/
HAL_StatusTypeDef HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD);
void              HAL_PWR_EnablePVD(void);
void              HAL_PWR_DisablePVD(void);

/* Wake up lines configuration functions ***************************************/
void     HAL_PWR_EnableWakeUpLine(uint32_t WakeUpLine, uint32_t Selection, uint32_t Polarity);
void     HAL_PWR_DisableWakeUpLine(uint32_t WakeUpLine);
uint32_t HAL_PWR_GetClearWakeupSource(void);

/* Low power modes configuration functions ************************************/
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTOPMode(uint32_t StopMode, uint8_t STOPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

/* Sleep on exit and sev on pending configuration functions *******************/
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

/* Programmable voltage monitor functions ************************************/
void              HAL_PWR_EnableVddUSBVoltageMonitor(void);
void              HAL_PWR_DisableVddUSBVoltageMonitor(void);
#if defined(PWR_SVMCR_IO2VMEN)
void              HAL_PWR_EnableVddIO2VoltageMonitor(void);
void              HAL_PWR_DisableVddIO2VoltageMonitor(void);
#endif /* PWR_SVMCR_IO2VMEN */
void              HAL_PWR_EnableVddA1VoltageMonitor(void);
void              HAL_PWR_DisableVddA1VoltageMonitor(void);
void              HAL_PWR_EnableVddA2VoltageMonitor(void);
void              HAL_PWR_DisableVddA2VoltageMonitor(void);
HAL_StatusTypeDef HAL_PWR_ConfigPVM(const PWR_PVMTypeDef *pConfigPVM);

/* Interrupt handler functions ************************************************/
void HAL_PWR_PVD_PVM_IRQHandler(void);
void HAL_PWR_PVD_Rising_Callback(void);
void HAL_PWR_PVD_Falling_Callback(void);
void HAL_PWR_USBVM_Rising_Callback(void);
void HAL_PWR_USBVM_Falling_Callback(void);
#if defined(PWR_SVMCR_IO2VMEN)
void HAL_PWR_IO2VM_Rising_Callback(void);
void HAL_PWR_IO2VM_Falling_Callback(void);
#endif /* PWR_SVMCR_IO2VMEN */
void HAL_PWR_ADCVM1_Rising_Callback(void);
void HAL_PWR_ADCVM1_Falling_Callback(void);
void HAL_PWR_ADCVM2_Rising_Callback(void);
void HAL_PWR_ADCVM2_Falling_Callback(void);
void HAL_PWR_WKUP_IRQHandler(void);
void HAL_PWR_WKUP1_Callback(void);
void HAL_PWR_WKUP2_Callback(void);
void HAL_PWR_WKUP3_Callback(void);
void HAL_PWR_WKUP4_Callback(void);
void HAL_PWR_WKUP5_Callback(void);
void HAL_PWR_WKUP6_Callback(void);
void HAL_PWR_WKUP7_Callback(void);
void HAL_PWR_WKUP8_Callback(void);
void HAL_PWR_WKUP9_Callback(void);
void HAL_PWR_WKUP10_Callback(void);
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group3
  * @{
  */
/* Privileges and security configuration functions ****************************/
void              HAL_PWR_ConfigAttributes(uint32_t Item, uint32_t Attributes);
HAL_StatusTypeDef HAL_PWR_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);
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
#endif /* __cplusplus */

#endif /* STM32U3xx_HAL_PWR_H */
