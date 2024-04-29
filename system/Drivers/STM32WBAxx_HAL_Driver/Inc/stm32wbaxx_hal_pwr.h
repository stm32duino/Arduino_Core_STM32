/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef STM32WBAxx_HAL_PWR_H
#define STM32WBAxx_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
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

  uint32_t Mode;     /*!< Specifies the operating mode for the selected pins.
                          This parameter can be a value of @ref PWR_PVD_Mode. */
} PWR_PVDTypeDef;
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
#define PWR_PVDLEVEL_0 0x00000000UL                            /*!< PVD threshold around 2.0 V       */
#define PWR_PVDLEVEL_1 (PWR_SVMCR_PVDLS_0)                     /*!< PVD threshold around 2.2 V       */
#define PWR_PVDLEVEL_2 (PWR_SVMCR_PVDLS_1)                     /*!< PVD threshold around 2.4 V       */
#define PWR_PVDLEVEL_3 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_1) /*!< PVD threshold around 2.5 V       */
#define PWR_PVDLEVEL_4 (PWR_SVMCR_PVDLS_2)                     /*!< PVD threshold around 2.6 V       */
#define PWR_PVDLEVEL_5 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_2) /*!< PVD threshold around 2.8 V       */
#define PWR_PVDLEVEL_6 (PWR_SVMCR_PVDLS_1 | PWR_SVMCR_PVDLS_2) /*!< PVD threshold around 2.9 V       */
#define PWR_PVDLEVEL_7 (PWR_SVMCR_PVDLS)                       /*!< External input analog voltage
                                                                    (compared internally to VREFINT) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode PWR PVD Mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL               (0x00U) /*!< Basic Mode is used                                                 */
#define PWR_PVD_MODE_IT_RISING            (0x05U) /*!< External Interrupt Mode with Rising edge trigger detection         */
#define PWR_PVD_MODE_IT_FALLING           (0x06U) /*!< External Interrupt Mode with Falling edge trigger detection        */
#define PWR_PVD_MODE_IT_RISING_FALLING    (0x07U) /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING         (0x09U) /*!< Event Mode with Rising edge trigger detection                      */
#define PWR_PVD_MODE_EVENT_FALLING        (0x0AU) /*!< Event Mode with Falling edge trigger detection                     */
#define PWR_PVD_MODE_EVENT_RISING_FALLING (0x0BU) /*!< Event Mode with Rising/Falling edge trigger detection              */
/**
  * @}
  */

/** @defgroup PWR_Regulator_In_LowPower_Mode PWR Regulator State in Sleep/Stop Mode
  * @{
  */
#define PWR_MAINREGULATOR_ON     (0x00U)          /*!< Main Regulator ON in Run Mode       */
#define PWR_LOWPOWERREGULATOR_ON (PWR_CR1_LPMS_0) /*!< Main Regulator ON in Low Power Mode */
/**
  * @}
  */

/** @defgroup PWR_Low_Power_Mode_Selection  PWR Low Power Mode Selection
  * @{
  */
#define PWR_LOWPOWERMODE_STOP0        (0x00000000u)    /*!< Stop 0: stop mode with main regulator      */
#define PWR_LOWPOWERMODE_STOP1        (PWR_CR1_LPMS_0) /*!< Stop 1: stop mode with low power regulator */
#define PWR_LOWPOWERMODE_STANDBY      (PWR_CR1_LPMS_2) /*!< Standby mode                               */
/**
  * @}
  */

/** @defgroup PWR_Sleep_Mode_Entry PWR Sleep Mode Entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI (0x01U) /*!< Wait For Interruption instruction to enter Sleep mode */
#define PWR_SLEEPENTRY_WFE (0x02U) /*!< Wait For Event instruction to enter Sleep mode        */
/**
  * @}
  */

/** @defgroup PWR_Stop_Mode_Entry PWR Stop Mode Entry
  * @{
  */
#define PWR_STOPENTRY_WFI (0x01U) /*!< Wait For Interruption instruction to enter Stop mode */
#define PWR_STOPENTRY_WFE (0x02U) /*!< Wait For Event instruction to enter Stop mode        */
/**
  * @}
  */

/** @defgroup PWR_Flags PWR Flags
  * @{
  */
#define PWR_FLAG_VOSRDY               (1U)  /*!< Voltage scaling ready flag                                      */
#define PWR_FLAG_STOPF                (2U)  /*!< Stop flag                                                       */
#define PWR_FLAG_SBF                  (3U)  /*!< Standby flag                                                    */
#define PWR_FLAG_ACTVOSRDY            (4U)  /*!< Currently applied VOS ready flag                                */
#define PWR_FLAG_PVDO                 (5U)  /*!< VDD voltage detector output flag                                */
#if defined(PWR_SVMSR_REGS)
#define PWR_FLAG_REGS                 (6U)  /*!< Regulator selection flag                                        */
#endif /* defined(PWR_SVMSR_REGS) */
#define PWR_FLAG_REGPARDYVDDRFPA      (7U)  /*!< Ready bit for VDDHPA voltage level when selecting VDDRFPA input */
#if defined(PWR_RADIOSCR_REGPARDYV11)
#define PWR_FLAG_REGPARDYV11          (8U)  /*!< Ready bit for VDDHPA voltage level when selecting VDD11 input   */
#endif /* defined(PWR_RADIOSCR_REGPARDYV11) */
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Lines_Flags PWR Wakeup Lines Flags
  * @{
  */
#define PWR_WAKEUP_FLAG1    (0x10U) /*!< Wakeup flag 1   */
#if defined(PWR_WUCR1_WUPEN2)
#define PWR_WAKEUP_FLAG2    (0x20U) /*!< Wakeup flag 2   */
#endif /* defined(PWR_WUCR1_WUPEN2) */
#define PWR_WAKEUP_FLAG3    (0x30U) /*!< Wakeup flag 3   */
#define PWR_WAKEUP_FLAG4    (0x40U) /*!< Wakeup flag 4   */
#if defined(PWR_WUCR1_WUPEN5)
#define PWR_WAKEUP_FLAG5    (0x50U) /*!< Wakeup flag 5   */
#endif /* defined(PWR_WUCR1_WUPEN5) */
#define PWR_WAKEUP_FLAG6    (0x60U) /*!< Wakeup flag 6   */
#define PWR_WAKEUP_FLAG7    (0x70U) /*!< Wakeup flag 7   */
#define PWR_WAKEUP_FLAG8    (0x80U) /*!< Wakeup flag 8   */
#define PWR_WAKEUP_ALL_FLAG (0x90U) /*!< Wakeup flag all */
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pin_High_Polarity PWR Wake Up Pins High Polarity
  * @{
  */
#define PWR_WAKEUP_PIN1_HIGH_0 (PWR_WUCR1_WUPEN1 | PWR_WAKEUP1_SOURCE_SELECTION_0) /*!< PA0  : Wakeup pin 1 (high polarity) */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN1_HIGH_1 (PWR_WUCR1_WUPEN1 | PWR_WAKEUP1_SOURCE_SELECTION_1) /*!< PB2  : Wakeup pin 1 (high polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#if defined(PWR_WUCR1_WUPEN2)
#define PWR_WAKEUP_PIN2_HIGH_0 (PWR_WUCR1_WUPEN2 | PWR_WAKEUP2_SOURCE_SELECTION_0) /*!< PA4  : Wakeup pin 2 (high polarity) */
#define PWR_WAKEUP_PIN2_HIGH_1 (PWR_WUCR1_WUPEN2 | PWR_WAKEUP2_SOURCE_SELECTION_1) /*!< PC13 : Wakeup pin 2 (high polarity) */
#endif /* defined(PWR_WUCR1_WUPEN2) */

#define PWR_WAKEUP_PIN3_HIGH_1 (PWR_WUCR1_WUPEN3 | PWR_WAKEUP3_SOURCE_SELECTION_1) /*!< PA1  : Wakeup pin 3 (high polarity) */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN3_HIGH_2 (PWR_WUCR1_WUPEN3 | PWR_WAKEUP3_SOURCE_SELECTION_2) /*!< PB6  : Wakeup pin 3 (high polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#define PWR_WAKEUP_PIN4_HIGH_0 (PWR_WUCR1_WUPEN4 | PWR_WAKEUP4_SOURCE_SELECTION_0) /*!< PA2  : Wakeup pin 4 (high polarity) */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN4_HIGH_1 (PWR_WUCR1_WUPEN4 | PWR_WAKEUP4_SOURCE_SELECTION_1) /*!< PB1  : Wakeup pin 4 (high polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#if defined(PWR_WUCR1_WUPEN5)
#define PWR_WAKEUP_PIN5_HIGH_1 (PWR_WUCR1_WUPEN5 | PWR_WAKEUP5_SOURCE_SELECTION_1) /*!< PA3  : Wakeup pin 5 (high polarity) */
#define PWR_WAKEUP_PIN5_HIGH_2 (PWR_WUCR1_WUPEN5 | PWR_WAKEUP5_SOURCE_SELECTION_2) /*!< PB7  : Wakeup pin 5 (high polarity) */
#endif /* defined(PWR_WUCR1_WUPEN5) */

#define PWR_WAKEUP_PIN6_HIGH_0 (PWR_WUCR1_WUPEN6 | PWR_WAKEUP6_SOURCE_SELECTION_0) /*!< PA12 : Wakeup pin 6 (high polarity) */
#define PWR_WAKEUP_PIN6_HIGH_1 (PWR_WUCR1_WUPEN6 | PWR_WAKEUP6_SOURCE_SELECTION_1) /*!< PA5  : Wakeup pin 6 (high polarity) */
#define PWR_WAKEUP_PIN6_HIGH_3 (PWR_WUCR1_WUPEN6 | PWR_WAKEUP6_SOURCE_SELECTION_3) /*!< RTC  : Wakeup pin 6 (high polarity) */

#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN7_HIGH_0 (PWR_WUCR1_WUPEN7 | PWR_WAKEUP7_SOURCE_SELECTION_0) /*!< PB14 : Wakeup pin 7 (high polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */
#define PWR_WAKEUP_PIN7_HIGH_1 (PWR_WUCR1_WUPEN7 | PWR_WAKEUP7_SOURCE_SELECTION_1) /*!< PA6  : Wakeup pin 7 (high polarity) */
#define PWR_WAKEUP_PIN7_HIGH_3 (PWR_WUCR1_WUPEN7 | PWR_WAKEUP7_SOURCE_SELECTION_3) /*!< RTC  : Wakeup pin 7 (high polarity) */

#define PWR_WAKEUP_PIN8_HIGH_1 (PWR_WUCR1_WUPEN8 | PWR_WAKEUP8_SOURCE_SELECTION_1) /*!< PA7  : Wakeup pin 8 (high polarity) */
#define PWR_WAKEUP_PIN8_HIGH_2 (PWR_WUCR1_WUPEN8 | PWR_WAKEUP8_SOURCE_SELECTION_2) /*!< PB9  : Wakeup pin 8 (high polarity) */
#define PWR_WAKEUP_PIN8_HIGH_3 (PWR_WUCR1_WUPEN8 | PWR_WAKEUP8_SOURCE_SELECTION_3) /*!< TAMP : Wakeup pin 8 (high polarity) */
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pin_Low_Polarity PWR Wake Up Pins Low Polarity
  * @{
  */
#define PWR_WAKEUP_PIN1_LOW_0 (PWR_WUCR1_WUPEN1 | PWR_WAKEUP1_POLARITY_LOW | PWR_WAKEUP1_SOURCE_SELECTION_0) /*!< PA0  : Wakeup pin 1 (low polarity) */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN1_LOW_1 (PWR_WUCR1_WUPEN1 | PWR_WAKEUP1_POLARITY_LOW | PWR_WAKEUP1_SOURCE_SELECTION_1) /*!< PB2  : Wakeup pin 1 (low polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#if defined(PWR_WUCR1_WUPEN2)
#define PWR_WAKEUP_PIN2_LOW_0 (PWR_WUCR1_WUPEN2 | PWR_WAKEUP2_POLARITY_LOW | PWR_WAKEUP2_SOURCE_SELECTION_0) /*!< PA4  : Wakeup pin 2 (low polarity) */
#define PWR_WAKEUP_PIN2_LOW_1 (PWR_WUCR1_WUPEN2 | PWR_WAKEUP2_POLARITY_LOW | PWR_WAKEUP2_SOURCE_SELECTION_1) /*!< PC13 : Wakeup pin 2 (low polarity) */
#endif /* defined(PWR_WUCR1_WUPEN2) */

#define PWR_WAKEUP_PIN3_LOW_1 (PWR_WUCR1_WUPEN3 | PWR_WAKEUP3_POLARITY_LOW | PWR_WAKEUP3_SOURCE_SELECTION_1) /*!< PA1  : Wakeup pin 3 (low polarity) */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN3_LOW_2 (PWR_WUCR1_WUPEN3 | PWR_WAKEUP3_POLARITY_LOW | PWR_WAKEUP3_SOURCE_SELECTION_2) /*!< PB6  : Wakeup pin 3 (low polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#define PWR_WAKEUP_PIN4_LOW_0 (PWR_WUCR1_WUPEN4 | PWR_WAKEUP4_POLARITY_LOW | PWR_WAKEUP4_SOURCE_SELECTION_0) /*!< PA2  : Wakeup pin 4 (low polarity) */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN4_LOW_1 (PWR_WUCR1_WUPEN4 | PWR_WAKEUP4_POLARITY_LOW | PWR_WAKEUP4_SOURCE_SELECTION_1) /*!< PB1  : Wakeup pin 4 (low polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#if defined(PWR_WUCR1_WUPEN5)
#define PWR_WAKEUP_PIN5_LOW_1 (PWR_WUCR1_WUPEN5 | PWR_WAKEUP5_POLARITY_LOW | PWR_WAKEUP5_SOURCE_SELECTION_1) /*!< PA3  : Wakeup pin 5 (low polarity) */
#define PWR_WAKEUP_PIN5_LOW_2 (PWR_WUCR1_WUPEN5 | PWR_WAKEUP5_POLARITY_LOW | PWR_WAKEUP5_SOURCE_SELECTION_2) /*!< PB7  : Wakeup pin 5 (low polarity) */
#endif /* defined(PWR_WUCR1_WUPEN5) */

#define PWR_WAKEUP_PIN6_LOW_0 (PWR_WUCR1_WUPEN6 | PWR_WAKEUP6_POLARITY_LOW | PWR_WAKEUP6_SOURCE_SELECTION_0) /*!< PA12  : Wakeup pin 6 (low polarity) */
#define PWR_WAKEUP_PIN6_LOW_1 (PWR_WUCR1_WUPEN6 | PWR_WAKEUP6_POLARITY_LOW | PWR_WAKEUP6_SOURCE_SELECTION_1) /*!< PA5  : Wakeup pin 6 (low polarity) */
#define PWR_WAKEUP_PIN6_LOW_3 (PWR_WUCR1_WUPEN6 | PWR_WAKEUP6_POLARITY_LOW | PWR_WAKEUP6_SOURCE_SELECTION_3) /*!< RTC  : Wakeup pin 6 (low polarity) */

#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP_PIN7_LOW_0 (PWR_WUCR1_WUPEN7 | PWR_WAKEUP7_POLARITY_LOW | PWR_WAKEUP7_SOURCE_SELECTION_0) /*!< PB14 : Wakeup pin 7 (low polarity) */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */
#define PWR_WAKEUP_PIN7_LOW_1 (PWR_WUCR1_WUPEN7 | PWR_WAKEUP7_POLARITY_LOW | PWR_WAKEUP7_SOURCE_SELECTION_1) /*!< PA6  : Wakeup pin 7 (low polarity) */
#define PWR_WAKEUP_PIN7_LOW_3 (PWR_WUCR1_WUPEN7 | PWR_WAKEUP7_POLARITY_LOW | PWR_WAKEUP7_SOURCE_SELECTION_3) /*!< RTC  : Wakeup pin 7 (low polarity) */

#define PWR_WAKEUP_PIN8_LOW_1 (PWR_WUCR1_WUPEN8 | PWR_WAKEUP8_POLARITY_LOW | PWR_WAKEUP8_SOURCE_SELECTION_1) /*!< PA7  : Wakeup pin 8 (low polarity) */
#define PWR_WAKEUP_PIN8_LOW_2 (PWR_WUCR1_WUPEN8 | PWR_WAKEUP8_POLARITY_LOW | PWR_WAKEUP8_SOURCE_SELECTION_2) /*!< PB9  : Wakeup pin 8 (low polarity) */
#define PWR_WAKEUP_PIN8_LOW_3 (PWR_WUCR1_WUPEN8 | PWR_WAKEUP8_POLARITY_LOW | PWR_WAKEUP8_SOURCE_SELECTION_3) /*!< TAMP : Wakeup pin 8 (low polarity) */
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pins PWR Wake Up Pins (Default polarity and default pin selection)
  * @{
  */
#define PWR_WAKEUP_PIN1 (PWR_WUCR1_WUPEN1) /*!< PA0  : Wakeup pin 1 (high polarity) */
#if defined(PWR_WUCR1_WUPEN2)
#define PWR_WAKEUP_PIN2 (PWR_WUCR1_WUPEN2) /*!< PA4  : Wakeup pin 2 (high polarity) */
#endif /* defined(PWR_WUCR1_WUPEN2) */
#define PWR_WAKEUP_PIN3 (PWR_WUCR1_WUPEN3) /*!< reserved                            */
#define PWR_WAKEUP_PIN4 (PWR_WUCR1_WUPEN4) /*!< PA2  : Wakeup pin 4 (high polarity) */
#if defined(PWR_WUCR1_WUPEN5)
#define PWR_WAKEUP_PIN5 (PWR_WUCR1_WUPEN5) /*!< reserved                            */
#endif /* defined(PWR_WUCR1_WUPEN5) */
#define PWR_WAKEUP_PIN6 (PWR_WUCR1_WUPEN6) /*!< PA12 : Wakeup pin 6 (high polarity) */
#define PWR_WAKEUP_PIN7 (PWR_WUCR1_WUPEN7) /*!< PB14 : Wakeup pin 7 (high polarity) */
#define PWR_WAKEUP_PIN8 (PWR_WUCR1_WUPEN8) /*!< reserved                            */
/**
  * @}
  */

/** @defgroup PWR_Items PWR Items
  * @{
  */
#define PWR_WKUP1 (PWR_SECCFGR_WUP1SEC) /*!< WUP1 secure protection                             */
#if defined(PWR_WUCR1_WUPEN2)
#define PWR_WKUP2 (PWR_SECCFGR_WUP2SEC) /*!< WUP2 secure protection                             */
#endif /* defined(PWR_WUCR1_WUPEN2) */
#define PWR_WKUP3 (PWR_SECCFGR_WUP3SEC) /*!< WUP3 secure protection                             */
#define PWR_WKUP4 (PWR_SECCFGR_WUP4SEC) /*!< WUP4 secure protection                             */
#if defined(PWR_WUCR1_WUPEN5)
#define PWR_WKUP5 (PWR_SECCFGR_WUP5SEC) /*!< WUP5 secure protection                             */
#endif /* defined(PWR_WUCR1_WUPEN5) */
#define PWR_WKUP6 (PWR_SECCFGR_WUP6SEC) /*!< WUP6 secure protection                             */
#define PWR_WKUP7 (PWR_SECCFGR_WUP7SEC) /*!< WUP7 secure protection                             */
#define PWR_WKUP8 (PWR_SECCFGR_WUP8SEC) /*!< WUP8 secure protection                             */
#define PWR_LPM   (PWR_SECCFGR_LPMSEC)  /*!< Low power modes secure protection                  */
#define PWR_VDM   (PWR_SECCFGR_VDMSEC)  /*!< Voltage detection and monitoring secure protection */
#define PWR_VB    (PWR_SECCFGR_VBSEC)   /*!< Backup domain secure protection                    */
#if defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5)
#define PWR_ALL   (PWR_WKUP1 | PWR_WKUP2 | PWR_WKUP3 | PWR_WKUP4 | \
                   PWR_WKUP5 | PWR_WKUP7 | PWR_WKUP6 | PWR_WKUP8 | \
                   PWR_LPM   | PWR_VDM   | PWR_VB)
#else
#define PWR_ALL   (PWR_WKUP1             | PWR_WKUP3 | PWR_WKUP4 | \
                               PWR_WKUP7 | PWR_WKUP6 | PWR_WKUP8 | \
                   PWR_LPM   | PWR_VDM   | PWR_VB)
#endif /* defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5) */
/**
  * @}
  */

#if defined(PWR_PRIVCFGR_SPRIV)
/** @defgroup PWR_Attributes PWR Attributes
  * @brief PWR Privilege/NPrivilege and Secure/NSecure Attributes
  * @{
  */
#define PWR_NSEC_PRIV  (PWR_ITEM_ATTR_NSEC_PRIV_MASK | 0x01U) /*!< NSecure and Privileged attribute  */
#define PWR_NSEC_NPRIV (PWR_ITEM_ATTR_NSEC_PRIV_MASK)         /*!< NSecure and NPrivileged attribute */
#define PWR_SEC_PRIV   (PWR_ITEM_ATTR_SEC_PRIV_MASK  | 0x02U) /*!< Secure and Privileged attribute   */
#define PWR_SEC_NPRIV  (PWR_ITEM_ATTR_SEC_PRIV_MASK)          /*!< Secure and NPrivileged attribute  */
/**
  * @}
  */
#endif /* defined(PWR_PRIVCFGR_SPRIV) */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup PWR_Exported_Macros PWR Exported Macros
  * @{
  */

/** @brief  Check PWR flags are set or not.
  * @param  __FLAG__ : Specifies the flag to check.
  *                    This parameter can be one of the following values when available :
  *                    @arg @ref PWR_FLAG_VOSRDY    : Voltage scaling ready flag.
  *                                                   Indicates that the Vcore level at or above VOS selected level.
  *                    @arg @ref PWR_FLAG_STOPF     : Stop flag.
  *                                                   Indicates that the device was resumed from Stop mode.
  *                    @arg @ref PWR_FLAG_SBF       : Standby flag.
  *                                                   Indicates that the device was resumed from Standby mode.
  *                    @arg @ref PWR_FLAG_ACTVOSRDY : Currently applied VOS ready flag.
  *                                                   Indicates that Vcore is equal to the current
  *                                                   voltage scaling provided by ACTVOS.
  *                    @arg @ref PWR_FLAG_PVDO VDD  : Voltage detector output flag.
  *                                                   Indicates that Vdd is equal or above
  *                                                   the PVD threshold selected by PVDLS.
  *                    @arg @ref PWR_FLAG_REGS      : Regulator selection flag.
  *                                                   Indicates the regulator selected.(*)
  *                    @arg @ref PWR_FLAG_REGPARDYVDDRFPA : Ready bit for VDDHPA voltage level when selecting VDDRFPA
  *                                                         input.
  *                                                         Indicates VDDHPA voltage level is ready.
  *                    @arg @ref PWR_FLAG_REGPARDYV11     : Ready bit for VDDHPA voltage level when selecting VDD11
  *                                                         input.
  *                                                         Indicates VDDHPA voltage level is ready.(*)
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
  * (*) Feature not available on all devices of the family
  * @retval The state of __FLAG__ (TRUE or FALSE).
  */
#if defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5)
#if defined(PWR_FLAG_REGS)
#define __HAL_PWR_GET_FLAG(__FLAG__)( \
                                      ((__FLAG__) == PWR_FLAG_VOSRDY)           ? (READ_BIT(PWR->VOSR, PWR_VOSR_VOSRDY)== \
                                          PWR_VOSR_VOSRDY)    : \
                                      ((__FLAG__) == PWR_FLAG_STOPF)            ? (READ_BIT(PWR->SR, PWR_SR_STOPF)== \
                                          PWR_SR_STOPF)       : \
                                      ((__FLAG__) == PWR_FLAG_SBF)              ? (READ_BIT(PWR->SR, PWR_SR_SBF)== \
                                          PWR_SR_SBF)         : \
                                      ((__FLAG__) == PWR_FLAG_ACTVOSRDY)        ?(READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOSRDY)== \
                                          PWR_SVMSR_ACTVOSRDY): \
                                      ((__FLAG__) == PWR_FLAG_PVDO)             ?(READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO)== \
                                          PWR_SVMSR_PVDO)     : \
                                      ((__FLAG__) == PWR_FLAG_REGS)             ?(READ_BIT(PWR->SVMSR, PWR_SVMSR_REGS)== \
                                          PWR_SVMSR_REGS)     : \
                                      ((__FLAG__) == PWR_FLAG_REGPARDYVDDRFPA)  ?(READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPARDYVDDRFPA)== \
                                          PWR_RADIOSCR_REGPARDYVDDRFPA)     : \
                                      ((__FLAG__) == PWR_FLAG_REGPARDYV11)      ?(READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPARDYV11)== \
                                          PWR_RADIOSCR_REGPARDYV11)     : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG1)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF1)  == \
                                          PWR_WUSR_WUF1)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG2)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF2)  == \
                                          PWR_WUSR_WUF2)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG3)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF3)  == \
                                          PWR_WUSR_WUF3)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG4)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF4)  == \
                                          PWR_WUSR_WUF4)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG5)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF5)  == \
                                          PWR_WUSR_WUF5)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG6)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF6)  == \
                                          PWR_WUSR_WUF6)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG7)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF7)  == \
                                          PWR_WUSR_WUF7)      : \
                                      (READ_BIT(PWR->WUSR, PWR_WUSR_WUF8)       == PWR_WUSR_WUF8))
#else
#define __HAL_PWR_GET_FLAG(__FLAG__)( \
                                      ((__FLAG__) == PWR_FLAG_VOSRDY)           ? (READ_BIT(PWR->VOSR, PWR_VOSR_VOSRDY)== \
                                          PWR_VOSR_VOSRDY)    : \
                                      ((__FLAG__) == PWR_FLAG_STOPF)            ? (READ_BIT(PWR->SR, PWR_SR_STOPF)== \
                                          PWR_SR_STOPF)       : \
                                      ((__FLAG__) == PWR_FLAG_SBF)              ? (READ_BIT(PWR->SR, PWR_SR_SBF)== \
                                          PWR_SR_SBF)         : \
                                      ((__FLAG__) == PWR_FLAG_ACTVOSRDY)        ?(READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOSRDY)== \
                                          PWR_SVMSR_ACTVOSRDY): \
                                      ((__FLAG__) == PWR_FLAG_PVDO)             ?(READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO)== \
                                          PWR_SVMSR_PVDO)     : \
                                      ((__FLAG__) == PWR_FLAG_REGPARDYVDDRFPA)  ?(READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPARDYVDDRFPA)== \
                                          PWR_RADIOSCR_REGPARDYVDDRFPA)     : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG1)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF1)  == \
                                          PWR_WUSR_WUF1)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG2)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF2)  == \
                                          PWR_WUSR_WUF2)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG3)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF3)  == \
                                          PWR_WUSR_WUF3)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG4)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF4)  == \
                                          PWR_WUSR_WUF4)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG5)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF5)  == \
                                          PWR_WUSR_WUF5)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG6)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF6)  == \
                                          PWR_WUSR_WUF6)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG7)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF7)  == \
                                          PWR_WUSR_WUF7)      : \
                                      (READ_BIT(PWR->WUSR, PWR_WUSR_WUF8)       == PWR_WUSR_WUF8))
#endif /* defined(PWR_FLAG_REGS) */
#else
#define __HAL_PWR_GET_FLAG(__FLAG__)( \
                                      ((__FLAG__) == PWR_FLAG_VOSRDY)           ? (READ_BIT(PWR->VOSR, PWR_VOSR_VOSRDY)== \
                                          PWR_VOSR_VOSRDY)    : \
                                      ((__FLAG__) == PWR_FLAG_STOPF)            ? (READ_BIT(PWR->SR, PWR_SR_STOPF)== \
                                          PWR_SR_STOPF)       : \
                                      ((__FLAG__) == PWR_FLAG_SBF)              ? (READ_BIT(PWR->SR, PWR_SR_SBF)== \
                                          PWR_SR_SBF)         : \
                                      ((__FLAG__) == PWR_FLAG_ACTVOSRDY)        ?(READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOSRDY)== \
                                          PWR_SVMSR_ACTVOSRDY): \
                                      ((__FLAG__) == PWR_FLAG_PVDO)             ?(READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO)== \
                                          PWR_SVMSR_PVDO)     : \
                                      ((__FLAG__) == PWR_FLAG_REGPARDYVDDRFPA)  ?(READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPARDYVDDRFPA)== \
                                          PWR_RADIOSCR_REGPARDYVDDRFPA)     : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG1)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF1)  == \
                                          PWR_WUSR_WUF1)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG3)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF3)  == \
                                          PWR_WUSR_WUF3)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG4)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF4)  == \
                                          PWR_WUSR_WUF4)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG6)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF6)  == \
                                          PWR_WUSR_WUF6)      : \
                                      ((__FLAG__) == PWR_WAKEUP_FLAG7)          ?(READ_BIT(PWR->WUSR, PWR_WUSR_WUF7)  == \
                                          PWR_WUSR_WUF7)      : \
                                      (READ_BIT(PWR->WUSR, PWR_WUSR_WUF8)       == PWR_WUSR_WUF8))
#endif /*defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5) */

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
  *                    @arg @ref PWR_WAKEUP_ALL_FLAG : all Wakeup flags.
  * @retval None.
  */
#if defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5)
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)  ( \
                                          ((__FLAG__) == PWR_FLAG_STOPF)   ? (SET_BIT(PWR->SR, PWR_SR_CSSF))        : \
                                          ((__FLAG__) == PWR_FLAG_SBF)     ? (SET_BIT(PWR->SR, PWR_SR_CSSF))        : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG1) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF1)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG2) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF2)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG3) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF3)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG4) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF4)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG5) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF5)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG6) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF6)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG7) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF7)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG8) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF8)) : \
                                          (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF)))
#else
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)  ( \
                                          ((__FLAG__) == PWR_FLAG_STOPF)   ? (SET_BIT(PWR->SR, PWR_SR_CSSF))        : \
                                          ((__FLAG__) == PWR_FLAG_SBF)     ? (SET_BIT(PWR->SR, PWR_SR_CSSF))        : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG1) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF1)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG3) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF3)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG4) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF4)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG6) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF6)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG7) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF7)) : \
                                          ((__FLAG__) == PWR_WAKEUP_FLAG8) ? (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF8)) : \
                                          (SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF)))
#endif /* defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5) */

/**
  * @brief  Enable the PVD Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT() SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Extended Interrupt Line.
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
  * @brief  Enable the PVD Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE() SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE() CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE() SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do                                                      \
  {                                                       \
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();              \
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();             \
  } while(0)

/**
  * @brief  Disable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do                                                       \
  {                                                        \
    __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();              \
    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();             \
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
  * @}
  */

/* Private constants ---------------------------------------------------------*/

/** @addtogroup PWR_Private_Constants PWR Private Constants
  * @{
  */
/* Define PVD extended interrupts and event line */
#define PWR_EXTI_LINE_PVD (0x00010000UL) /*!< PVD EXTI Line */

/* Defines wake up lines shift */
#define PWR_WUP_POLARITY_SHIFT      (0x08U) /*!< Internal constant used to retrieve wakeup signal polariry  */
#define PWR_WUP_SELECT_SIGNAL_SHIFT (0x10U) /*!< Internal constant used to retrieve wakeup signal selection */

/* Defines wake up lines mask */
#define PWR_EWUP_MASK         (0x000000FFUL) /*!< Internal constant used to retrieve wakeup signal enable    */
#define PWR_WUP_POLARITY_MASK (0x0000FF00UL) /*!< Internal constant used to retrieve wakeup signal polariry  */
#define PWR_WUP_SELECT_MASK   (0xFFFF0000UL) /*!< Internal constant used to retrieve wakeup signal selection */

/* Defines wake up lines selection */
#define PWR_WAKEUP1_SOURCE_SELECTION_0 (0U)
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP1_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL1_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#if defined(PWR_WUCR1_WUPEN2)
#define PWR_WAKEUP2_SOURCE_SELECTION_0 (0U)                                                                       /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP2_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL2_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(PWR_WUCR1_WUPEN2) */

#define PWR_WAKEUP3_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL3_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP3_SOURCE_SELECTION_2 (PWR_WUCR3_WUSEL3_1 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#define PWR_WAKEUP4_SOURCE_SELECTION_0 (0U)                                                                       /*!< Internal constant used to retrieve wakeup signal selection */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP4_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL4_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */

#if defined(PWR_WUCR1_WUPEN5)
#define PWR_WAKEUP5_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL5_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP5_SOURCE_SELECTION_2 (PWR_WUCR3_WUSEL5_1 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(PWR_WUCR1_WUPEN5) */

#define PWR_WAKEUP6_SOURCE_SELECTION_0 (0U)                                                                       /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP6_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL6_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP6_SOURCE_SELECTION_3 ((PWR_WUCR3_WUSEL6_0 | PWR_WUCR3_WUSEL6_1) << PWR_WUP_SELECT_SIGNAL_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */

#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_WAKEUP7_SOURCE_SELECTION_0 (0U)                                                                       /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */
#define PWR_WAKEUP7_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL7_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP7_SOURCE_SELECTION_3 ((PWR_WUCR3_WUSEL7_0 | PWR_WUCR3_WUSEL7_1) << PWR_WUP_SELECT_SIGNAL_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */

#define PWR_WAKEUP8_SOURCE_SELECTION_1 (PWR_WUCR3_WUSEL8_0 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP8_SOURCE_SELECTION_2 (PWR_WUCR3_WUSEL8_1 << PWR_WUP_SELECT_SIGNAL_SHIFT)                        /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP8_SOURCE_SELECTION_3 ((PWR_WUCR3_WUSEL8_0 | PWR_WUCR3_WUSEL8_1) << PWR_WUP_SELECT_SIGNAL_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */

/* Defines wake up lines low polarity */
#define PWR_WAKEUP1_POLARITY_LOW (PWR_WUCR2_WUPP1 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */
#if defined(PWR_WUCR1_WUPEN2)
#define PWR_WAKEUP2_POLARITY_LOW (PWR_WUCR2_WUPP2 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(PWR_WUCR1_WUPEN2) */
#define PWR_WAKEUP3_POLARITY_LOW (PWR_WUCR2_WUPP3 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP4_POLARITY_LOW (PWR_WUCR2_WUPP4 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */
#if defined(PWR_WUCR1_WUPEN5)
#define PWR_WAKEUP5_POLARITY_LOW (PWR_WUCR2_WUPP5 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */
#endif /* defined(PWR_WUCR1_WUPEN5) */
#define PWR_WAKEUP6_POLARITY_LOW (PWR_WUCR2_WUPP6 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP7_POLARITY_LOW (PWR_WUCR2_WUPP7 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */
#define PWR_WAKEUP8_POLARITY_LOW (PWR_WUCR2_WUPP8 << PWR_WUP_POLARITY_SHIFT) /*!< Internal constant used to retrieve wakeup signal selection */

/* Defines attribute */
#define PWR_ITEM_ATTR_NSEC_PRIV_MASK (0x10U) /*!< NSecure Privilege / NPrivilege attribute item mask */
#define PWR_ITEM_ATTR_SEC_PRIV_MASK  (0x20U) /*!< Secure Privilege / NPrivilege attribute item mask  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @addtogroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/* Stop mode entry check macro */
#define IS_PWR_REGULATOR(REGULATOR)  (((REGULATOR) == PWR_LOWPOWERMODE_STOP0) || \
                                      ((REGULATOR) == PWR_LOWPOWERMODE_STOP1))

/* Wake up pins check macro */
#if defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5)
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN1_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN2_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN2_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH_2)  ||\
                                ((PIN) == PWR_WAKEUP_PIN4_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN4_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN5_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN5_HIGH_2)  ||\
                                ((PIN) == PWR_WAKEUP_PIN6_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN6_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN6_HIGH_3)  ||\
                                ((PIN) == PWR_WAKEUP_PIN7_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN7_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN7_HIGH_3)  ||\
                                ((PIN) == PWR_WAKEUP_PIN8_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN8_HIGH_2)  ||\
                                ((PIN) == PWR_WAKEUP_PIN8_HIGH_3)  ||\
                                ((PIN) == PWR_WAKEUP_PIN1_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN1_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN2_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN2_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN3_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN3_LOW_2)   ||\
                                ((PIN) == PWR_WAKEUP_PIN4_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN4_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN5_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN5_LOW_2)   ||\
                                ((PIN) == PWR_WAKEUP_PIN6_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN6_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN6_LOW_3)   ||\
                                ((PIN) == PWR_WAKEUP_PIN7_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN7_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN7_LOW_3)   ||\
                                ((PIN) == PWR_WAKEUP_PIN8_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN8_LOW_2)   ||\
                                ((PIN) == PWR_WAKEUP_PIN8_LOW_3)   ||\
                                ((PIN) == PWR_WAKEUP_PIN1)         ||\
                                ((PIN) == PWR_WAKEUP_PIN2)         ||\
                                ((PIN) == PWR_WAKEUP_PIN3)         ||\
                                ((PIN) == PWR_WAKEUP_PIN4)         ||\
                                ((PIN) == PWR_WAKEUP_PIN5)         ||\
                                ((PIN) == PWR_WAKEUP_PIN6)         ||\
                                ((PIN) == PWR_WAKEUP_PIN7)         ||\
                                ((PIN) == PWR_WAKEUP_PIN8))
#else
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN4_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN6_HIGH_0)  ||\
                                ((PIN) == PWR_WAKEUP_PIN6_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN6_HIGH_3)  ||\
                                ((PIN) == PWR_WAKEUP_PIN7_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN7_HIGH_3)  ||\
                                ((PIN) == PWR_WAKEUP_PIN8_HIGH_1)  ||\
                                ((PIN) == PWR_WAKEUP_PIN8_HIGH_2)  ||\
                                ((PIN) == PWR_WAKEUP_PIN8_HIGH_3)  ||\
                                ((PIN) == PWR_WAKEUP_PIN1_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN3_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN4_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN6_LOW_0)   ||\
                                ((PIN) == PWR_WAKEUP_PIN6_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN6_LOW_3)   ||\
                                ((PIN) == PWR_WAKEUP_PIN7_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN7_LOW_3)   ||\
                                ((PIN) == PWR_WAKEUP_PIN8_LOW_1)   ||\
                                ((PIN) == PWR_WAKEUP_PIN8_LOW_2)   ||\
                                ((PIN) == PWR_WAKEUP_PIN8_LOW_3)   ||\
                                ((PIN) == PWR_WAKEUP_PIN1)         ||\
                                ((PIN) == PWR_WAKEUP_PIN3)         ||\
                                ((PIN) == PWR_WAKEUP_PIN4)         ||\
                                ((PIN) == PWR_WAKEUP_PIN6)         ||\
                                ((PIN) == PWR_WAKEUP_PIN7)         ||\
                                ((PIN) == PWR_WAKEUP_PIN8))
#endif /* defined(PWR_WUCR1_WUPEN2) && defined(PWR_WUCR1_WUPEN5) */

/* PVD level check macro */
#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_0) || ((LEVEL) == PWR_PVDLEVEL_1) || \
                                 ((LEVEL) == PWR_PVDLEVEL_2) || ((LEVEL) == PWR_PVDLEVEL_3) || \
                                 ((LEVEL) == PWR_PVDLEVEL_4) || ((LEVEL) == PWR_PVDLEVEL_5) || \
                                 ((LEVEL) == PWR_PVDLEVEL_6) || ((LEVEL) == PWR_PVDLEVEL_7))

/* PVD mode check macro */
#define IS_PWR_PVD_MODE(MODE) (((MODE) == PWR_PVD_MODE_NORMAL)               ||\
                               ((MODE) == PWR_PVD_MODE_IT_RISING)            ||\
                               ((MODE) == PWR_PVD_MODE_IT_FALLING)           ||\
                               ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING)    ||\
                               ((MODE) == PWR_PVD_MODE_EVENT_RISING)         ||\
                               ((MODE) == PWR_PVD_MODE_EVENT_FALLING)        ||\
                               ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALLING))

/* Sleep mode entry check macro */
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) || ((ENTRY) == PWR_SLEEPENTRY_WFE))

/* Stop mode entry check macro */
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPENTRY_WFI) || ((ENTRY) == PWR_STOPENTRY_WFE))

/* PWR items check macro */
#define IS_PWR_ITEMS_ATTRIBUTES(ITEM) ((((ITEM) & (~PWR_ALL)) == 0U) && ((ITEM) != 0U))

#if defined(PWR_PRIVCFGR_SPRIV)
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* PWR attribute check macro (Secure) */
#define IS_PWR_ATTRIBUTES(ATTRIBUTES) ((((~(((ATTRIBUTES)& \
                                             0xF0U) >> 4U)) & ((ATTRIBUTES) & 0x0FU)) == 0U) && \
                                       (((ATTRIBUTES) & 0xFFFFFFCCU) == 0U))
#else
/* PWR attribute check macro (NSecure) */
#define IS_PWR_ATTRIBUTES(ATTRIBUTES) (((ATTRIBUTES) == PWR_NSEC_NPRIV) || ((ATTRIBUTES) == PWR_NSEC_PRIV))
#endif /* __ARM_FEATURE_CMSE */
#endif /* defined(PWR_PRIVCFGR_SPRIV) */

/* PWR regulation VDDHPA input supply selection */
#define IS_PWR_REGPASEL_SUPPLYSELECTION(SUPPLYSELECTION) (((SUPPLYSELECTION) == PWR_RADIO_REG_VDDRFPA)     ||\
                                                          ((SUPPLYSELECTION) == PWR_RADIO_REG_VDDHPA_VD11))
/**
  * @}
  */

/* Include PWR HAL Extended module */
#include "stm32wbaxx_hal_pwr_ex.h"

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

/* Wake up pins configuration functions ***************************************/
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPin);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPin);
uint32_t HAL_PWR_GetClearWakeupSource(void);

/* Low power modes configuration functions ************************************/
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

/* Sleep on exit and sev on pending configuration functions *******************/
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

/* Interrupt handler functions ************************************************/
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVD_Rising_Callback(void);
void HAL_PWR_PVD_Falling_Callback(void);
void HAL_PWR_WKUP_IRQHandler(void);
void HAL_PWR_WKUP1_Callback(void);
#if defined(PWR_WUCR1_WUPEN2)
void HAL_PWR_WKUP2_Callback(void);
#endif /* defined(PWR_WUCR1_WUPEN2) */
void HAL_PWR_WKUP3_Callback(void);
void HAL_PWR_WKUP4_Callback(void);
#if defined(PWR_WUCR1_WUPEN5)
void HAL_PWR_WKUP5_Callback(void);
#endif /* defined(PWR_WUCR1_WUPEN5) */
void HAL_PWR_WKUP6_Callback(void);
void HAL_PWR_WKUP7_Callback(void);
void HAL_PWR_WKUP8_Callback(void);
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

#endif /* STM32WBAxx_HAL_PWR_H */
