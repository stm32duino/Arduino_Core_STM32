/**
  ******************************************************************************
  * @file    stm32wb0x_hal_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef STM32WB0x_HAL_PWR_H
#define STM32WB0x_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal_def.h"

/* Include low level driver */
#include "stm32wb0x_ll_pwr.h"
#include "stm32wb0x_ll_system.h"
/* Include PWR HAL Extended module */
#include "stm32wb0x_hal_pwr_ex.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
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
  uint32_t PVDLevel;       /*!< PVDLevel: Specifies the PVD detection level.
                                This parameter can be a value of @ref PWR_PVD_Detection_Level. */

  uint32_t Mode;           /*!< Mode: Specifies the operating mode for the selected pins.
                                This parameter can be a value of @ref PWR_PVD_Mode. */
} PWR_PVDTypeDef;

/**
  * @brief  PWR DEEPSTOP configuration structure definition
  */
typedef struct
{
  uint32_t deepStopMode; /*!< Specifies the configuration of the slow clock in DEEPSTOP.
                          This parameter can be one of the following value:
                          - PWR_DEEPSTOP_WITH_SLOW_CLOCK_OFF
                          - PWR_DEEPSTOP_WITH_SLOW_CLOCK_ON */

} PWR_DEEPSTOPTypeDef;

/**
  * @brief  PWR SHUTDOWN configuration structure definition
  */
typedef struct
{
  uint8_t BORStatus;       /*!< Specifies the BOR status ENABLE or DISABLE */
  uint8_t WakeUpPinStatus; /*!< Specifies if the PB0 wake up source
                                is ENABLE or DISABLE*/
  uint8_t WakeUpPol;       /*!< Specifies the wake up source polarity */
} PWR_SHUTDOWNTypeDef;

/**
  * @brief  PWR SAVE enum definition
  */
typedef enum
{
  POWER_SAVE_LEVEL_RUNNING          = 0,
  POWER_SAVE_LEVEL_CPU_HALT         = 1,
  POWER_SAVE_LEVEL_STOP_LS_CLOCK_ON = 2,
  POWER_SAVE_LEVEL_STOP             = 3
} PowerSaveLevels;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWREx_WUP_Polarity Shift to apply to retrieve polarity information from PWR_WAKEUP_PINy_xxx constants
  * @{
  */
#define PWR_WUP_POLARITY_SHIFT               0x13U  /*!< Internal constant used to retrieve wakeup pin polarity*/
/**
  * @}
  */

/** @defgroup PWR_Low_Power_Mode_Selection  PWR Low Power Mode Selection
  * @{
  */
#define PWR_LOWPOWERMODE_STOP              (0x00000000U)                         /*!< DeepStop mode */
#define PWR_LOWPOWERMODE_SHUTDOWN          (PWR_CR1_LPMS)                        /*!< Shutdown mode */

/**
  * @}
  */
/** @defgroup PWR_PVD_Detection_Level  Power Voltage Detector Level selection
  * @note     Refer datasheet for selection voltage value
  * @{
  */
#define PWR_PVDLEVEL_0                  (0x00000000U)                            /*!< PVD threshold around 2.0 V */
#define PWR_PVDLEVEL_1                  (PWR_CR2_PVDLS_0)                        /*!< PVD threshold around 2.2 V */
#define PWR_PVDLEVEL_2                  (PWR_CR2_PVDLS_1)                        /*!< PVD threshold around 2.4 V */
#define PWR_PVDLEVEL_3                  (PWR_CR2_PVDLS_1 | PWR_CR2_PVDLS_0)      /*!< PVD threshold around 2.5 V */
#define PWR_PVDLEVEL_4                  (PWR_CR2_PVDLS_2)                        /*!< PVD threshold around 2.6 V */
#define PWR_PVDLEVEL_5                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_0)      /*!< PVD threshold around 2.8 V */
#define PWR_PVDLEVEL_6                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_1)      /*!< PVD threshold around 2.9 V */
#define PWR_PVDLEVEL_7                  (PWR_CR2_PVDLS)                          /*!< External input analog voltage   (Compare internally to VBGP) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode  PWR PVD interrupt and event mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL                 (0x00000000U)                  /*!< Basic mode is used */
#define PWR_PVD_MODE_IT                     (SYSCFG_PWRC_IER_PVD_IE)       /*!< Interrupt Mode detection */
/**
  * @}
  */

/** @defgroup PWR_Regulator_state_in_SLEEP_STOP_mode  PWR regulator mode
  * @{
  */
#define PWR_MAINREGULATOR_ON                (0x00000000U)               /*!< Regulator in main mode      */
#define PWR_LOWPOWERREGULATOR_ON            (0x00000001U)               /*!< Regulator in low-power mode */
/**
  * @}
  */
/** @defgroup PWREx_Wakeup_Source_Select Wakeup Source Select
  * @{
  */
#define PWR_WUP_CR3               (0x00000000U)
#define PWR_WUP_CR6               (0x00000001U)
/**
  * @}
  */

/** @defgroup PWR_DEEPSTOP_SLOW_CLOCK_CONFIG Slow clock configuration in DEEPSTOP mode
  * @{
  */
#define PWR_DEEPSTOP_WITH_SLOW_CLOCK_OFF  (0x00000000U)
#define PWR_DEEPSTOP_WITH_SLOW_CLOCK_ON   (0x00000001U)
/**
  * @}
  */

/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWR_Exported_Macros  PWR Exported Macros
  * @{
  */
/** @brief  Check whether or not a specific PWR flag is set.
  * @param __FLAG__ specifies the flag to check.
  *           This parameter can be one of the following values:
  *
  *            /--------------------------------SR1-------------------------------/
  *            @arg @ref PWR_FLAG_WUF0       Wake Up Flag 0. Indicates that a wakeup event
  *                                          was received from the pin PB0.
  *            @arg @ref PWR_FLAG_WUF1       Wake Up Flag 1. Indicates that a wakeup event
  *                                          was received from the pin PB1.
  *            @arg @ref PWR_FLAG_WUF2       Wake Up Flag 2. Indicates that a wakeup event
  *                                          was received from the pin PB2.
  *            @arg @ref PWR_FLAG_WUF3       Wake Up Flag 3. Indicates that a wakeup event
  *                                          was received from the pin PB3.
  *            @arg @ref PWR_FLAG_WUF4       Wake Up Flag 4. Indicates that a wakeup event
  *                                          was received from the pin PB4.
  *            @arg @ref PWR_FLAG_WUF5       Wake Up Flag 5. Indicates that a wakeup event
  *                                          was received from the pin PB5.
  *            @arg @ref PWR_FLAG_WUF6       Wake Up Flag 6. Indicates that a wakeup event
  *                                          was received from the pin PB6.
  *            @arg @ref PWR_FLAG_WUF7       Wake Up Flag 7. Indicates that a wakeup event
  *                                          was received from the pin PB7.
  *            @arg @ref PWR_FLAG_WUF8       Wake Up Flag 8. Indicates that a wakeup event
  *                                          was received from the pin PA8.
  *            @arg @ref PWR_FLAG_WUF9       Wake Up Flag 9. Indicates that a wakeup event
  *                                          was received from the pin PA9.
  *            @arg @ref PWR_FLAG_WUF10      Wake Up Flag 10. Indicates that a wakeup event
  *                                          was received from the pin PA10.
  *            @arg @ref PWR_FLAG_WUF11      Wake Up Flag 11. Indicates that a wakeup event
  *                                          was received from the pin PA11.
  *            @arg @ref PWR_FLAG_WBLEF      Wake Up Flag Indicates that a wakeup event
  *                                          was received from the Bluetooth LE.
  *
  *            @arg @ref PWR_FLAG_BHWF       Wake Up Flag Indicates that a wakeup event
  *                                          was received from the Bluetooth LE Host CPU.
  *
  *            @arg @ref PWR_FLAG_IWUF2      Wake Up Flag 11. Indicates that a wakeup event
  *                                          was received from the pin PA11.
  *
  *            /--------------------------------SR2-------------------------------/
  *            @arg @ref PWR_FLAG_SMPSBYPR   This flag indicates if theSMPS regulator is in
  *                                          PRECHARGE mode
  *            @arg @ref PWR_FLAG_SMPSENR    This flag indicates if SMPS regulator is in RUN
  *                                          mode.
  *            @arg @ref PWR_FLAG_SMPSRDYF   This flag indicates if the SMPS regulator is ready
  *            @arg @ref PWR_FLAG_REGLPS     This flag indicates if the low-power regulator
  *                                          is ready
  *            @arg @ref PWR_FLAG_REGMS      This flag indicates if the main regulator is
  *                                          ready.
  *            @arg @ref PWR_FLAG_PVDO       This flag indicates if the VDDIO is lower than
  *                                          the selected threshold.
  *
  *            /--------------------------------SR3-------------------------------/
  *            @arg @ref PWR_FLAG_WUF12      Wake Up Flag 12. Indicates that a wakeup event
  *                                          was received from the pin PA0.
  *            @arg @ref PWR_FLAG_WUF13      Wake Up Flag 13. Indicates that a wakeup event
  *                                          was received from the pin PA1.
  *            @arg @ref PWR_FLAG_WUF14      Wake Up Flag 14. Indicates that a wakeup event
  *                                          was received from the pin PA2.
  *            @arg @ref PWR_FLAG_WUF15      Wake Up Flag 15. Indicates that a wakeup event
  *                                          was received from the pin PA3.
  *            @arg @ref PWR_FLAG_WUF16      Wake Up Flag 16. Indicates that a wakeup event
  *                                          was received from the pin PB12 or PA4 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF17      Wake Up Flag 17. Indicates that a wakeup event
  *                                          was received from the pin PB13 or PA5 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF18      Wake Up Flag 18. Indicates that a wakeup event
  *                                          was received from the pin PB14 or PA6 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF19      Wake Up Flag 19. Indicates that a wakeup event
  *                                          was received from the pin PB15 or PA7 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF20      Wake Up Flag 20. Indicates that a wakeup event
  *                                          was received from the pin PB8.
  *            @arg @ref PWR_FLAG_WUF21      Wake Up Flag 21. Indicates that a wakeup event
  *                                          was received from the pin PB9.
  *            @arg @ref PWR_FLAG_WUF22      Wake Up Flag 22. Indicates that a wakeup event
  *                                          was received from the pin PB10.
  *            @arg @ref PWR_FLAG_WUF23      Wake Up Flag 23. Indicates that a wakeup event
  *                                          was received from the pin PB11.
  *            @arg @ref PWR_FLAG_WUF24      Wake Up Flag 24. Indicates that a wakeup event
  *                                          was received from the pin PB12.
  *            @arg @ref PWR_FLAG_WUF25      Wake Up Flag 25. Indicates that a wakeup event
  *                                          was received from the pin PB13.
  *            @arg @ref PWR_FLAG_WUF26      Wake Up Flag 26. Indicates that a wakeup event
  *                                          was received from the pin PB14.
  *            @arg @ref PWR_FLAG_WUF27      Wake Up Flag 27. Indicates that a wakeup event
  *                                          was received from the pin PB15.
  *             /--------------------------------EXTSRR-------------------------------/
  *            @arg @ref PWR_FLAG_DEEPSTOPF  System DEEPTSTOP Flag
  *            @arg @ref PWR_FLAG_RFPHASEF   RFPHASE Flag
  *
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#if defined (PWR_CR6_EWU20)
#define __HAL_PWR_GET_FLAG(__FLAG__)( \
                                      ((__FLAG__) == PWR_FLAG_WUF0)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF0)      == PWR_SR1_WUF0)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF1)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF1)      == PWR_SR1_WUF1)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF2)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF2)      == PWR_SR1_WUF2)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF3)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF3)      == PWR_SR1_WUF3)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF4)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF4)      == PWR_SR1_WUF4)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF5)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF5)      == PWR_SR1_WUF5)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF6)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF6)      == PWR_SR1_WUF6)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF7)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF7)      == PWR_SR1_WUF7)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF8)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF8)      == PWR_SR1_WUF8)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF9)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF9)      == PWR_SR1_WUF9)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF10)     ? (READ_BIT(PWR->SR1, PWR_SR1_WUF10)     == PWR_SR1_WUF10)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF11)     ? (READ_BIT(PWR->SR1, PWR_SR1_WUF11)     == PWR_SR1_WUF11)        : \
                                      ((__FLAG__) == PWR_FLAG_WBLEF)     ? (READ_BIT(PWR->SR1, PWR_SR1_WBLEF)     == PWR_SR1_WBLEF)        : \
                                      ((__FLAG__) == PWR_FLAG_BHWF)      ? (READ_BIT(PWR->SR1, PWR_SR1_WBLEHCPUF) == PWR_SR1_WBLEHCPUF)    : \
                                      ((__FLAG__) == PWR_FLAG_WUFI)      ? (READ_BIT(PWR->SR1, PWR_SR1_IWUF)      == PWR_SR1_IWUF)         : \
                                      ((__FLAG__) == PWR_FLAG_SMPSBYPR)  ? (READ_BIT(PWR->SR2, PWR_SR2_SMPSBYPR)  == PWR_SR2_SMPSBYPR)     : \
                                      ((__FLAG__) == PWR_FLAG_SMPSENR)   ? (READ_BIT(PWR->SR2, PWR_SR2_SMPSENR)   == PWR_SR2_SMPSENR)      : \
                                      ((__FLAG__) == PWR_FLAG_SMPSRDYF)  ? (READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY)   == PWR_SR2_SMPSRDY)      : \
                                      ((__FLAG__) == PWR_FLAG_REGLPS)    ? (READ_BIT(PWR->SR2, PWR_SR2_REGLPS)    == PWR_SR2_REGLPS)       : \
                                      ((__FLAG__) == PWR_FLAG_REGMS)     ? (READ_BIT(PWR->SR2, PWR_SR2_REGMS)     == PWR_SR2_REGMS)        : \
                                      ((__FLAG__) == PWR_FLAG_PVDO)      ? (READ_BIT(PWR->SR2, PWR_SR2_PVDO)      == PWR_SR2_PVDO)         : \
                                      ((__FLAG__) == PWR_FLAG_WUF12)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF12)     == PWR_SR3_WUF12)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF13)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF13)     == PWR_SR3_WUF13)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF14)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF14)     == PWR_SR3_WUF14)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF15)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF15)     == PWR_SR3_WUF15)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF16)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF16)     == PWR_SR3_WUF16)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF17)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF17)     == PWR_SR3_WUF17)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF18)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF18)     == PWR_SR3_WUF18)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF19)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF19)     == PWR_SR3_WUF19)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF20)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF20)     == PWR_SR3_WUF20)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF21)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF21)     == PWR_SR3_WUF21)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF22)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF22)     == PWR_SR3_WUF22)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF23)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF23)     == PWR_SR3_WUF23)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF24)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF24)     == PWR_SR3_WUF24)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF25)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF25)     == PWR_SR3_WUF25)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF26)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF26)     == PWR_SR3_WUF26)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF27)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF27)     == PWR_SR3_WUF27)        : \
                                      ((__FLAG__) == PWR_FLAG_DEEPSTOPF) ? (READ_BIT(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF) == PWR_EXTSRR_DEEPSTOPF) : \
                                      (READ_BIT(PWR->EXTSRR, PWR_EXTSRR_RFPHASEF)  == PWR_EXTSRR_RFPHASEF))
#else
#define __HAL_PWR_GET_FLAG(__FLAG__)( \
                                      ((__FLAG__) == PWR_FLAG_WUF0)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF0)      == PWR_SR1_WUF0)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF1)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF1)      == PWR_SR1_WUF1)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF2)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF2)      == PWR_SR1_WUF2)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF3)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF3)      == PWR_SR1_WUF3)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF4)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF4)      == PWR_SR1_WUF4)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF5)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF5)      == PWR_SR1_WUF5)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF6)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF6)      == PWR_SR1_WUF6)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF7)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF7)      == PWR_SR1_WUF7)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF8)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF8)      == PWR_SR1_WUF8)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF9)      ? (READ_BIT(PWR->SR1, PWR_SR1_WUF9)      == PWR_SR1_WUF9)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF10)     ? (READ_BIT(PWR->SR1, PWR_SR1_WUF10)     == PWR_SR1_WUF10)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF11)     ? (READ_BIT(PWR->SR1, PWR_SR1_WUF11)     == PWR_SR1_WUF11)             : \
                                      ((__FLAG__) == PWR_FLAG_WBLEF)     ? (READ_BIT(PWR->SR1, PWR_SR1_WBLEF)     == PWR_SR1_WBLEF)             : \
                                      ((__FLAG__) == PWR_FLAG_BHWF)      ? (READ_BIT(PWR->SR1, PWR_SR1_WBLEHCPUF) == PWR_SR1_WBLEHCPUF)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFI)      ? (READ_BIT(PWR->SR1, PWR_SR1_IWUF)      == PWR_SR1_IWUF)              : \
                                      ((__FLAG__) == PWR_FLAG_IWUF2)     ? (READ_BIT(PWR->SR1, PWR_SR1_IWUF2)     == PWR_SR1_IWUF2)             : \
                                      ((__FLAG__) == PWR_FLAG_SMPSBYPR)  ? (READ_BIT(PWR->SR2, PWR_SR2_SMPSBYPR)  == PWR_SR2_SMPSBYPR)          : \
                                      ((__FLAG__) == PWR_FLAG_SMPSENR)   ? (READ_BIT(PWR->SR2, PWR_SR2_SMPSENR)   == PWR_SR2_SMPSENR)           : \
                                      ((__FLAG__) == PWR_FLAG_SMPSRDYF)  ? (READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY)   == PWR_SR2_SMPSRDY)           : \
                                      ((__FLAG__) == PWR_FLAG_REGLPS)    ? (READ_BIT(PWR->SR2, PWR_SR2_REGLPS)    == PWR_SR2_REGLPS)            : \
                                      ((__FLAG__) == PWR_FLAG_PVDO)      ? (READ_BIT(PWR->SR2, PWR_SR2_PVDO)      == PWR_SR2_PVDO)              : \
                                      ((__FLAG__) == PWR_FLAG_WUF12)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF12)     == PWR_SR3_WUF12)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF13)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF13)     == PWR_SR3_WUF13)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF14)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF14)     == PWR_SR3_WUF14)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF15)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF15)     == PWR_SR3_WUF15)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF16)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF16)     == PWR_SR3_WUF16)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF17)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF17)     == PWR_SR3_WUF17)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF18)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF18)     == PWR_SR3_WUF18)             : \
                                      ((__FLAG__) == PWR_FLAG_WUF19)     ? (READ_BIT(PWR->SR3, PWR_SR3_WUF19)     == PWR_SR3_WUF19)             : \
                                      ((__FLAG__) == PWR_FLAG_DEEPSTOPF) ? (READ_BIT(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF) == PWR_EXTSRR_DEEPSTOPF): \
                                      (READ_BIT(PWR->EXTSRR,  PWR_EXTSRR_RFPHASEF)  == PWR_EXTSRR_RFPHASEF))
#endif /* PWR_CR6_EWU20 */

/** @brief  Clear a specific PWR flag.
  * @param __FLAG__ specifies the flag to clear.
  *           This parameter can be one of the following values:
  *            /--------------------------------SR1-------------------------------/
  *            @arg @ref PWR_FLAG_WUF0       Wake Up Flag 0. Indicates that a wakeup event
  *                                          was received from the pin PB0.
  *            @arg @ref PWR_FLAG_WUF1       Wake Up Flag 1. Indicates that a wakeup event
  *                                          was received from the pin PB1.
  *            @arg @ref PWR_FLAG_WUF2       Wake Up Flag 2. Indicates that a wakeup event
  *                                          was received from the pin PB2.
  *            @arg @ref PWR_FLAG_WUF3       Wake Up Flag 3. Indicates that a wakeup event
  *                                          was received from the pin PB3.
  *            @arg @ref PWR_FLAG_WUF4       Wake Up Flag 4. Indicates that a wakeup event
  *                                          was received from the pin PB4.
  *            @arg @ref PWR_FLAG_WUF5       Wake Up Flag 5. Indicates that a wakeup event
  *                                          was received from the pin PB5.
  *            @arg @ref PWR_FLAG_WUF6       Wake Up Flag 6. Indicates that a wakeup event
  *                                          was received from the pin PB6.
  *            @arg @ref PWR_FLAG_WUF7       Wake Up Flag 7. Indicates that a wakeup event
  *                                          was received from the pin PB7.
  *            @arg @ref PWR_FLAG_WUF8       Wake Up Flag 8. Indicates that a wakeup event
  *                                          was received from the pin PA8.
  *            @arg @ref PWR_FLAG_WUF9       Wake Up Flag 9. Indicates that a wakeup event
  *                                          was received from the pin PA9.
  *            @arg @ref PWR_FLAG_WUF10      Wake Up Flag 10. Indicates that a wakeup event
  *                                          was received from the pin PA10.
  *            @arg @ref PWR_FLAG_WUF11      Wake Up Flag 11. Indicates that a wakeup event
  *                                          was received from the pin PA11.
  *            @arg @ref PWR_FLAG_WBLEF      Wake Up Flag Indicates that a wakeup event
  *                                          was received from the Bluetooth LE.
  *
  *            @arg @ref PWR_FLAG_BHWF       Wake Up Flag Indicates that a wakeup event
  *                                          was received from the Bluetooth LE Host CPU.
  *
  *            @arg @ref PWR_FLAG_IWUF2      Wake Up Flag 11. Indicates that a wakeup event
  *                                          was received from the pin PA11.
  *
  *            /--------------------------------SR3-------------------------------/
  *            @arg @ref PWR_FLAG_WUF12      Wake Up Flag 12. Indicates that a wakeup event
  *                                          was received from the pin PA0.
  *            @arg @ref PWR_FLAG_WUF13      Wake Up Flag 13. Indicates that a wakeup event
  *                                          was received from the pin PA1.
  *            @arg @ref PWR_FLAG_WUF14      Wake Up Flag 14. Indicates that a wakeup event
  *                                          was received from the pin PA2.
  *            @arg @ref PWR_FLAG_WUF15      Wake Up Flag 15. Indicates that a wakeup event
  *                                          was received from the pin PA3.
  *            @arg @ref PWR_FLAG_WUF16      Wake Up Flag 16. Indicates that a wakeup event
  *                                          was received from the pin PB12 or PA4 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF17      Wake Up Flag 17. Indicates that a wakeup event
  *                                          was received from the pin PB13 or PA5 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF18      Wake Up Flag 18. Indicates that a wakeup event
  *                                          was received from the pin PB14 or PA6 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF19      Wake Up Flag 19. Indicates that a wakeup event
  *                                          was received from the pin PB15 or PA7 for STM32wb07.
  *            @arg @ref PWR_FLAG_WUF20      Wake Up Flag 20. Indicates that a wakeup event
  *                                          was received from the pin PB8.
  *            @arg @ref PWR_FLAG_WUF21      Wake Up Flag 21. Indicates that a wakeup event
  *                                          was received from the pin PB9.
  *            @arg @ref PWR_FLAG_WUF22      Wake Up Flag 22. Indicates that a wakeup event
  *                                          was received from the pin PB10.
  *            @arg @ref PWR_FLAG_WUF23      Wake Up Flag 23. Indicates that a wakeup event
  *                                          was received from the pin PB11.
  *            @arg @ref PWR_FLAG_WUF24      Wake Up Flag 24. Indicates that a wakeup event
  *                                          was received from the pin PB12.
  *            @arg @ref PWR_FLAG_WUF25      Wake Up Flag 25. Indicates that a wakeup event
  *                                          was received from the pin PB13.
  *            @arg @ref PWR_FLAG_WUF26      Wake Up Flag 26. Indicates that a wakeup event
  *                                          was received from the pin PB14.
  *            @arg @ref PWR_FLAG_WUF27      Wake Up Flag 27. Indicates that a wakeup event
  *                                          was received from the pin PB15.
  *            @arg @ref PWR_WU_FLAG_ALL        all Wakeup flags.
  *
  *            /--------------------------------EXTSRR-------------------------------/
  *            @arg @ref PWR_FLAG_DEEPSTOPF  System DEEPTSTOP Flag
  *            @arg @ref PWR_FLAG_RFPHASEF   RFPHASE Flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#if defined (PWR_CR6_EWU20)
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)( \
                                        ((__FLAG__) == PWR_FLAG_DEEPSTOPF) ? (SET_BIT(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF)) : \
                                        ((__FLAG__) == PWR_FLAG_RFPHASEF)  ? (SET_BIT(PWR->EXTSRR, PWR_EXTSRR_RFPHASEF))  : \
                                        ((__FLAG__) == PWR_FLAG_WUF0)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF0))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF1)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF1))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF2)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF2))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF3)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF3))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF4)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF4))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF5)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF5))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF6)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF6))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF7)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF7))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF8)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF8))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF9)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF9))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF10)     ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF10))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF11)     ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF11))        : \
                                        ((__FLAG__) == PWR_FLAG_WBLEF)     ? (SET_BIT(PWR->SR1,    PWR_SR1_WBLEF))        : \
                                        ((__FLAG__) == PWR_FLAG_BHWF)      ? (SET_BIT(PWR->SR1,    PWR_SR1_WBLEHCPUF))    : \
                                        ((__FLAG__) == PWR_FLAG_WUF12)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF12))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF13)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF13))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF14)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF14))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF15)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF15))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF16)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF16))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF17)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF17))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF18)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF18))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF19)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF19))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF20)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF20))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF21)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF21))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF22)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF22))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF23)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF23))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF24)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF24))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF25)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF25))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF26)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF26))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF27)     ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF27))        : \
                                        ((__FLAG__) == PWR_FLAG_SR1_ALL)   ? (SET_BIT(PWR->SR1,    PWR_FLAG_SR1_ALL))     : \
                                        ((__FLAG__) == PWR_FLAG_SR3_ALL)   ? (SET_BIT(PWR->SR3,    PWR_FLAG_SR3_ALL))     : \
                                        (SET_BIT(PWR->SR1, PWR_FLAG_SR1_ALL), SET_BIT(PWR->SR3, PWR_FLAG_SR3_ALL)))

#else
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)( \
                                        ((__FLAG__) == PWR_FLAG_DEEPSTOPF)    ? (SET_BIT(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF)) : \
                                        ((__FLAG__) == PWR_FLAG_RFPHASEF )    ? (SET_BIT(PWR->EXTSRR, PWR_EXTSRR_RFPHASEF))  : \
                                        ((__FLAG__) == PWR_FLAG_WUF0)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF0))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF1)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF1))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF2)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF2))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF3)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF3))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF4)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF4))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF5)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF5))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF6)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF6))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF7)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF7))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF8)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF8))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF9)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF9))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF10)        ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF10))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF11)        ? (SET_BIT(PWR->SR1,    PWR_SR1_WUF11))        : \
                                        ((__FLAG__) == PWR_FLAG_WBLEF)        ? (SET_BIT(PWR->SR1,    PWR_SR1_WBLEF))        : \
                                        ((__FLAG__) == PWR_FLAG_BHWF)         ? (SET_BIT(PWR->SR1,    PWR_SR1_WBLEHCPUF))    : \
                                        ((__FLAG__) == PWR_FLAG_IWUF2)        ? (SET_BIT(PWR->SR1,    PWR_SR1_IWUF2))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF12)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF12))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF13)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF13))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF14)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF14))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF15)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF15))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF16)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF16))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF17)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF17))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF18)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF18))        : \
                                        ((__FLAG__) == PWR_FLAG_WUF19)        ? (SET_BIT(PWR->SR3,    PWR_SR3_WUF19))        : \
                                        ((__FLAG__) == PWR_FLAG_SR1_ALL)      ? (SET_BIT(PWR->SR1,    PWR_FLAG_SR1_ALL))     : \
                                        ((__FLAG__) == PWR_FLAG_SR3_ALL)      ? (SET_BIT(PWR->SR3,    PWR_FLAG_SR3_ALL))     : \
                                        (SET_BIT(PWR->SR1, PWR_FLAG_SR1_ALL), SET_BIT(PWR->SR3, PWR_FLAG_SR3_ALL)))
#endif /* PWR_CR6_EWU20 */

/**
  * @brief Enable the PVD Line.
  * @retval None
  */
#define __HAL_PWR_PVD_ENABLE_IT()   SET_BIT(SYSCFG->PWRC_IER, SYSCFG_PWRC_IER_PVD_IE)

/**
  * @brief Disable the PVD Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVD_DISABLE_IT()  CLEAR_BIT(SYSCFG->PWRC_IER, SYSCFG_PWRC_IER_PVD_IE)


/**
  * @brief Check whether or not the PVD interrupt flag is set.
  * @retval PVD Line Status.
  */
#define __HAL_PWR_PVD_GET_FLAG()  (READ_BIT(SYSCFG->PWRC_ISCR, SYSCFG_PWRC_ISCR_PVD_ISC)\
                                   == (SYSCFG_PWRC_ISCR_PVD_ISC)) ? 1UL : 0U

/**
  * @brief Clear the PVD interrupt flag.
  * @retval None
  */
#define __HAL_PWR_PVD_CLEAR_FLAG()  SET_BIT(SYSCFG->PWRC_ISCR, SYSCFG_PWRC_ISCR_PVD_ISC)

/**
  * @}
  */


/* Private macros --------------------------------------------------------*/
/** @defgroup PWR_Private_Macros  PWR Private Macros
  * @{
  */

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_0) || ((LEVEL) == PWR_PVDLEVEL_1)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_2) || ((LEVEL) == PWR_PVDLEVEL_3)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_4) || ((LEVEL) == PWR_PVDLEVEL_5)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_6) || ((LEVEL) == PWR_PVDLEVEL_7))


#define IS_PWR_PVD_MODE(MODE)  (((MODE) == PWR_PVD_MODE_NORMAL)              ||\
                                ((MODE) == PWR_PVD_MODE_IT))

#define IS_PWR_REGULATOR(REGULATOR)               (((REGULATOR) == PWR_MAINREGULATOR_ON)    || \
                                                   ((REGULATOR) == PWR_LOWPOWERREGULATOR_ON))

/**
  * @}
  */
/** @addtogroup PWR_Exported_Functions
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions_Group1
  * @{
  */
void              HAL_PWR_DeInit(void);

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD);
void              HAL_PWR_EnablePVD(void);
void              HAL_PWR_DisablePVD(void);
void              HAL_PWR_PVDCallback(void);
/* WakeUp pins configuration functions ****************************************/
void              HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPin, uint32_t WakeUpPolarity);
void              HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);
uint32_t          HAL_PWR_GetClearWakeupSource(void);
/* Low Power modes configuration functions ************************************/
HAL_StatusTypeDef HAL_PWR_ConfigDEEPSTOP(PWR_DEEPSTOPTypeDef *sConfigDEEPSTOP);
HAL_StatusTypeDef HAL_PWR_ConfigSHUTDOWN(PWR_SHUTDOWNTypeDef *sConfigSHUTDOWN);
void              HAL_PWR_EnterDEEPSTOPMode(void);
void              HAL_PWR_EnterSLEEPMode(void);

/* Sleep on exit and sev on pending configuration functions *******************/
void              HAL_PWR_EnableSleepOnExit(void);
void              HAL_PWR_DisableSleepOnExit(void);
void              HAL_PWR_EnableSEVOnPend(void);
void              HAL_PWR_DisableSEVOnPend(void);

/* Interrupt handler functions ************************************************/
void              HAL_PWR_PVD_IRQHandler(void);
void              HAL_PWR_WKUP_IRQHandler(void);
void              HAL_PWR_WKUPx_Callback(uint32_t WakeupIOs);

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


#endif /* STM32WB0x_HAL_PWR_H */
