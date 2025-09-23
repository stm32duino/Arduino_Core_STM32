/**
  ******************************************************************************
  * @file    stm32wl3x_hal_pwr.h
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
#ifndef STM32WL3x_HAL_PWR_H
#define STM32WL3x_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_def.h"
#include "stm32wl3x_ll_pwr.h"

/** @addtogroup STM32WL3x_HAL_Driver
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
  POWER_SAVE_LEVEL_DISABLED          = 0,
  POWER_SAVE_LEVEL_SLEEP             = 1,
  POWER_SAVE_LEVEL_DEEPSTOP_TIMER    = 2,
  POWER_SAVE_LEVEL_DEEPSTOP_NOTIMER  = 3
} PowerSaveLevels;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_PVD_Detection_Level  Power Voltage Detector Level selection
  * @note     Refer datasheet for selection voltage value
  * @{
  */
#define PWR_PVDLEVEL_0                  (0x00000000U)                         /*!< PVD threshold around 2.05 V */
#define PWR_PVDLEVEL_1                  (PWR_CR2_PVDLS_0)                     /*!< PVD threshold around 2.20 V */
#define PWR_PVDLEVEL_2                  (PWR_CR2_PVDLS_1)                     /*!< PVD threshold around 2.36 V */
#define PWR_PVDLEVEL_3                  (PWR_CR2_PVDLS_1 | PWR_CR2_PVDLS_0)   /*!< PVD threshold around 2.52 V */
#define PWR_PVDLEVEL_4                  (PWR_CR2_PVDLS_2)                     /*!< PVD threshold around 2.64 V */
#define PWR_PVDLEVEL_5                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_0)   /*!< PVD threshold around 2.81 V */
#define PWR_PVDLEVEL_6                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_1)   /*!< PVD threshold around 2.91 V */
#define PWR_PVDLEVEL_7                  (PWR_CR2_PVDLS)                       /*!< External input analog voltage (compared internally to VREFINT for BlueNRG-LP and LPS.  Compared internally to VBGP for STM32WL33) */
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

/** @defgroup PWR_Flags PWR Flags
  * @{
  */
/*--------------------------------IWUF-------------------------------*/
#define PWR_FLAG_LPUART       0x00000000U
#define PWR_FLAG_RTC          0x00000001U
#define PWR_FLAG_LCD          0x00000002U
#define PWR_FLAG_COMP         0x00000003U
#define PWR_FLAG_LCSC         0x00000004U
#define PWR_FLAG_MRSUBG       0x00000005U
#define PWR_FLAG_MRSUBGHCPU   0x00000006U
#define PWR_FLAG_LPAWUR       0x00000007U

/*--------------------------------SR2--------------------------------*/
#define PWR_FLAG_SMPSBYPR     0x00000008U
#define PWR_FLAG_SMPSENR      0x00000009U
#define PWR_FLAG_SMPSRDY      0x0000000AU
#define PWR_FLAG_REGLPS       0x0000000BU
#define PWR_FLAG_REGMS        0x0000000CU
#define PWR_FLAG_PVDO         0x0000000DU

/*--------------------------------WUFA--------------------------------*/
#define PWR_FLAG_WUFA0        0x0000000EU
#define PWR_FLAG_WUFA1        0x0000000FU
#define PWR_FLAG_WUFA2        0x00000010U
#define PWR_FLAG_WUFA3        0x00000011U
#define PWR_FLAG_WUFA4        0x00000012U
#define PWR_FLAG_WUFA5        0x00000013U
#define PWR_FLAG_WUFA6        0x00000014U
#define PWR_FLAG_WUFA7        0x00000015U
#define PWR_FLAG_WUFA8        0x00000016U
#define PWR_FLAG_WUFA9        0x00000017U
#define PWR_FLAG_WUFA10       0x00000018U
#define PWR_FLAG_WUFA11       0x00000019U
#define PWR_FLAG_WUFA12       0x0000001AU
#define PWR_FLAG_WUFA13       0x0000001BU
#define PWR_FLAG_WUFA14       0x0000001CU
#define PWR_FLAG_WUFA15       0x0000001DU
#define PWR_FLAG_WUFA_ALL     0x0000FFFFU

/*--------------------------------WUFB--------------------------------*/
#define PWR_FLAG_WUFB0        0x0000001EU
#define PWR_FLAG_WUFB1        0x0000001FU
#define PWR_FLAG_WUFB2        0x00000020U
#define PWR_FLAG_WUFB3        0x00000021U
#define PWR_FLAG_WUFB4        0x00000022U
#define PWR_FLAG_WUFB5        0x00000023U
#define PWR_FLAG_WUFB6        0x00000024U
#define PWR_FLAG_WUFB7        0x00000025U
#define PWR_FLAG_WUFB8        0x00000026U
#define PWR_FLAG_WUFB9        0x00000027U
#define PWR_FLAG_WUFB10       0x00000028U
#define PWR_FLAG_WUFB11       0x00000029U
#define PWR_FLAG_WUFB12       0x0000002AU
#define PWR_FLAG_WUFB13       0x0000002BU
#define PWR_FLAG_WUFB14       0x0000002CU
#define PWR_FLAG_WUFB15       0x0000002DU
#define PWR_FLAG_WUFB_ALL     0xFFFF0000U
#define PWR_FLAG_WUF_ALL      (PWR_FLAG_WUFA_ALL | PWR_FLAG_WUFB_ALL)

/*--------------------------------SDWN_WUF----------------------------*/
#define PWR_FLAG_WUF          0x0000002EU

/*--------------------------------EXTSRR------------------------------*/
#define PWR_FLAG_DEEPSTOPF    0x00000030U
#define PWR_FLAG_RFPHASEF     0x00000031U

/**
  * @}
  */

/** @defgroup PWR_WAKEUP_SOURCE Wakeup Source
  * @{
  */
#define PWR_WAKEUP_ALL           0x0000FFFF               /*!< Enable all the wakeup source                    */
#define PWR_WAKEUP_PIN0          (uint32_t)(1U << 0U)     /*!< Enable the wakeup source IO0                    */
#define PWR_WAKEUP_PIN1          (uint32_t)(1U << 1U)     /*!< Enable the wakeup source IO1                    */
#define PWR_WAKEUP_PIN2          (uint32_t)(1U << 2U)     /*!< Enable the wakeup source IO2                    */
#define PWR_WAKEUP_PIN3          (uint32_t)(1U << 3U)     /*!< Enable the wakeup source IO3                    */
#define PWR_WAKEUP_PIN4          (uint32_t)(1U << 4U)     /*!< Enable the wakeup source IO4                    */
#define PWR_WAKEUP_PIN5          (uint32_t)(1U << 5U)     /*!< Enable the wakeup source IO5                    */
#define PWR_WAKEUP_PIN6          (uint32_t)(1U << 6U)     /*!< Enable the wakeup source IO6                    */
#define PWR_WAKEUP_PIN7          (uint32_t)(1U << 7U)     /*!< Enable the wakeup source IO7                    */
#define PWR_WAKEUP_PIN8          (uint32_t)(1U << 8U)     /*!< Enable the wakeup source IO8                    */
#define PWR_WAKEUP_PIN9          (uint32_t)(1U << 9U)     /*!< Enable the wakeup source IO9                    */
#define PWR_WAKEUP_PIN10         (uint32_t)(1U << 10U)    /*!< Enable the wakeup source IO10                   */
#define PWR_WAKEUP_PIN11         (uint32_t)(1U << 11U)    /*!< Enable the wakeup source IO11                   */
#define PWR_WAKEUP_PIN12         (uint32_t)(1U << 12U)    /*!< Enable the wakeup source IO12                   */
#define PWR_WAKEUP_PIN13         (uint32_t)(1U << 13U)    /*!< Enable the wakeup source IO13                   */
#define PWR_WAKEUP_PIN14         (uint32_t)(1U << 14U)    /*!< Enable the wakeup source IO14                   */
#define PWR_WAKEUP_PIN15         (uint32_t)(1U << 15U)    /*!< Enable the wakeup source IO15                   */

#define PWR_WAKEUP_LPAWUR        PWR_IEWU_EWLPAWUR        /*!< Enable wakeup on LPAWUR RFIP event              */
#define PWR_WAKEUP_SUBG          PWR_IEWU_EWMRSUBG        /*!< Enable wakeup on MRSUBG RFIP event              */
#define PWR_WAKEUP_SUBGHOST      PWR_IEWU_EWMRSUBGHCPU    /*!< Enable wakeup on MRSUBG Host CPU event          */
#define PWR_WAKEUP_LCSC          PWR_IEWU_EIWL4           /*!< Enable wakeup on internal event (LCSC)          */
#define PWR_WAKEUP_COMP          PWR_IEWU_EIWL3           /*!< Enable wakeup on internal event (COMP)          */
#define PWR_WAKEUP_LCD           PWR_IEWU_EIWL2           /*!< Enable wakeup on internal event (LCD)           */
#define PWR_WAKEUP_RTC           PWR_IEWU_EIWL1           /*!< Enable wakeup on internal event (RTC)           */
#define PWR_WAKEUP_LPUART        PWR_IEWU_EIWL0           /*!< Enable wakeup on internal event (LPUART)        */

/**
  * @}
  */

/** @defgroup PWR_WAKEUP_SOURCE_PORT IO Port for wakeup source
  * @{
  */
#define PWR_WAKEUP_PORTA   (0x00000000U)       /*!< IO port A to get out from DEEPSTOP mode */
#define PWR_WAKEUP_PORTB   (0x00000001U)       /*!< IO port B to get out from DEEPSTOP mode */
/**
  * @}
  */

/** @defgroup PWR_WAKEUP_POLARITY IOs Wakeup configuration polarity
  * @{
  */
#define PWR_WUP_RISIEDG    (0x000000000U)
#define PWR_WUP_FALLEDG    (0x000000001U)
/**
  * @}
  */

/** @defgroup PWR_LOW_PWR_MODE Low Power mode selection
  * @{
  */
#define PWR_MODE_DEEPSTOP  (0x000000000U)
#define PWR_MODE_SHUTDOWN  (PWR_CR1_LPMS)
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
/** @brief  Check PWR flags are set or not.
  * @param  __FLAG__ : Specifies the flag to check.
  *                    This parameter can be one of the following values when available :
  *                    @arg @ref PWR_FLAG_LPUART      : LPUART Internal wakeup flag.
  *                                                     Indicates that a wakeup from LPUART occurred since last clear.
  *                    @arg @ref PWR_FLAG_RTC         : RTC Internal wakeup flag.
  *                                                     Indicates that a wakeup from RTC occurred since last clear.
  *                    @arg @ref PWR_FLAG_LCD         : LCD Internal wakeup flag.
  *                                                     Indicates that a wakeup from LCD occurred since last clear.
  *                    @arg @ref PWR_FLAG_COMP        : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_LCSC        : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_MRSUBG      : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_MRSUBGHCPU  : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_LPAWUR      : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_SMPSBYPR    : SMPS PRECHARGE mode status.
  *                                                     Indicates that the SMPS regulator is in PRECHARGE mode.
  *                    @arg @ref PWR_FLAG_SMPSENR     : SMPS RUN mode status.
  *                                                     Indicates that the SMPS regulator is in RUN mode.
  *                    @arg @ref PWR_FLAG_SMPSRDY     : SMPS ready status.
  *                                                     Indicates that the SMPS regulator is ready.
  *                    @arg @ref PWR_FLAG_REGLPS      : Low Power regulator ready status.
  *                                                     Indicates that the Low Power regulator is ready.
  *                    @arg @ref PWR_FLAG_REGMS       : Main regulator ready status.
  *                                                     Indicates that the Low Power regulator is ready.
  *                    @arg @ref PWR_FLAG_PVDO        : Power voltage Detector Output.
  *                                                     Indicates that the Low Power regulator is ready.
  *                    @arg @ref PWR_FLAG_WUFA0       : PA0 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA0 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA1       : PA1 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA1 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA2       : PA2 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA2 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA3       : PA3 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA3 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA4       : PA4 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA4 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA5       : PA5 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA5 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA6       : PA6 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA6 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA7       : PA7 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA7 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA8       : PA8 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA8 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA9       : PA9 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA9 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA10      : PA10 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA10 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA11      : PA11 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA11 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA12      : PA12 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA12 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA13      : PA13 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA13 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA14      : PA14 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA14 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA15      : PA15 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA15 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB0       : PB0 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB0 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB1       : PB1 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB1 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB2       : PB2 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB2 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB3       : PB3 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB3 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB4       : PB4 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB4 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB5       : PB5 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB5 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB6       : PB6 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB6 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB7       : PB7 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB7 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB8       : PB8 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB8 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB9       : PB9 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB9 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB10      : PB10 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB10 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB11      : PB11 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB11 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB12      : PB12 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB12 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB13      : PB13 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB13 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB14      : PB14 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB14 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB15      : PB15 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB15 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUF         : PB0 pin wakeup from shutdown flag
  *                                                     Indicates a shutdown wakeup from PB0 pin occurred.
  *                    @arg @ref PWR_FLAG_RFPHASEF    : RFPHASE Flag.
  *                                                     Indicates that the RF SUBGHz IP is awake and may require
  *                                                     a system attention.
  *                    @arg @ref PWR_FLAG_DEEPSTOPF   : System DEEPTSTOP Flag.
  *                                                     the device entered a DEEPSTOP mode.
  * @retval The state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_PWR_GET_FLAG(__FLAG__)( \
                                      ((__FLAG__) == PWR_FLAG_LPUART)     ? (READ_BIT(PWR->IWUF, PWR_IWUF_IWUF0)         == \
                                          PWR_IWUF_IWUF0)        : \
                                      ((__FLAG__) == PWR_FLAG_RTC)        ? (READ_BIT(PWR->IWUF, PWR_IWUF_IWUF1)         == \
                                          PWR_IWUF_IWUF1)        : \
                                      ((__FLAG__) == PWR_FLAG_LCD)        ? (READ_BIT(PWR->IWUF, PWR_IWUF_IWUF2)         == \
                                          PWR_IWUF_IWUF2)        : \
                                      ((__FLAG__) == PWR_FLAG_COMP)       ? (READ_BIT(PWR->IWUF, PWR_IWUF_IWUF3)         == \
                                          PWR_IWUF_IWUF3)        : \
                                      ((__FLAG__) == PWR_FLAG_LCSC)       ? (READ_BIT(PWR->IWUF, PWR_IWUF_IWUF4)         == \
                                          PWR_IWUF_IWUF4)        : \
                                      ((__FLAG__) == PWR_FLAG_MRSUBG)     ? (READ_BIT(PWR->IWUF, PWR_IWUF_WMRSUBGF)      == \
                                          PWR_IWUF_WMRSUBGF)     : \
                                      ((__FLAG__) == PWR_FLAG_MRSUBGHCPU) ? (READ_BIT(PWR->IWUF, PWR_IWUF_WMRSUBGHCPUF)  == \
                                          PWR_IWUF_WMRSUBGHCPUF) : \
                                      ((__FLAG__) == PWR_FLAG_LPAWUR)     ? (READ_BIT(PWR->IWUF, PWR_IWUF_WLPAWURF)      == \
                                          PWR_IWUF_WLPAWURF)     : \
                                      ((__FLAG__) == PWR_FLAG_SMPSBYPR)   ? (READ_BIT(PWR->SR2,  PWR_SR2_SMPSBYPR)       == \
                                          PWR_SR2_SMPSBYPR)      : \
                                      ((__FLAG__) == PWR_FLAG_SMPSENR)    ? (READ_BIT(PWR->SR2,  PWR_SR2_SMPSENR)        == \
                                          PWR_SR2_SMPSENR)       : \
                                      ((__FLAG__) == PWR_FLAG_SMPSRDY)    ? (READ_BIT(PWR->SR2,  PWR_SR2_SMPSRDY)        == \
                                          PWR_SR2_SMPSRDY)       : \
                                      ((__FLAG__) == PWR_FLAG_REGLPS)     ? (READ_BIT(PWR->SR2,  PWR_SR2_REGLPS)         == \
                                          PWR_SR2_REGLPS)        : \
                                      ((__FLAG__) == PWR_FLAG_REGMS)      ? (READ_BIT(PWR->SR2,  PWR_SR2_REGMS)          == \
                                          PWR_SR2_REGMS)         : \
                                      ((__FLAG__) == PWR_FLAG_PVDO)       ? (READ_BIT(PWR->SR2,  PWR_SR2_PVDO)           == \
                                          PWR_SR2_PVDO)          : \
                                      ((__FLAG__) == PWR_FLAG_WUFA0)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF0)          == \
                                          PWR_WUFA_WUF0)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA1)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF1)          == \
                                          PWR_WUFA_WUF1)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA2)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF2)          == \
                                          PWR_WUFA_WUF2)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA3)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF3)          == \
                                          PWR_WUFA_WUF3)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA4)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF4)          == \
                                          PWR_WUFA_WUF4)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA5)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF5)          == \
                                          PWR_WUFA_WUF5)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA6)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF6)          == \
                                          PWR_WUFA_WUF6)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA7)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF7)          == \
                                          PWR_WUFA_WUF7)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA8)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF8)          == \
                                          PWR_WUFA_WUF8)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA9)      ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF9)          == \
                                          PWR_WUFA_WUF9)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFA10)     ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF10)         == \
                                          PWR_WUFA_WUF10)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFA11)     ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF11)         == \
                                          PWR_WUFA_WUF11)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFA12)     ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF12)         == \
                                          PWR_WUFA_WUF12)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFA13)     ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF13)         == \
                                          PWR_WUFA_WUF13)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFA14)     ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF14)         == \
                                          PWR_WUFA_WUF14)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFA15)     ? (READ_BIT(PWR->WUFA, PWR_WUFA_WUF15)         == \
                                          PWR_WUFA_WUF15)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFB0)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF0)          == \
                                          PWR_WUFB_WUF0)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB1)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF1)          == \
                                          PWR_WUFB_WUF1)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB2)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF2)          == \
                                          PWR_WUFB_WUF2)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB3)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF3)          == \
                                          PWR_WUFB_WUF3)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB4)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF4)          == \
                                          PWR_WUFB_WUF4)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB5)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF5)          == \
                                          PWR_WUFB_WUF5)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB6)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF6)          == \
                                          PWR_WUFB_WUF6)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB7)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF7)          == \
                                          PWR_WUFB_WUF7)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB8)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF8)          == \
                                          PWR_WUFB_WUF8)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB9)      ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF9)          == \
                                          PWR_WUFB_WUF9)         : \
                                      ((__FLAG__) == PWR_FLAG_WUFB10)     ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF10)         == \
                                          PWR_WUFB_WUF10)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFB11)     ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF11)         == \
                                          PWR_WUFB_WUF11)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFB12)     ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF12)         == \
                                          PWR_WUFB_WUF12)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFB13)     ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF13)         == \
                                          PWR_WUFB_WUF13)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFB14)     ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF14)         == \
                                          PWR_WUFB_WUF14)        : \
                                      ((__FLAG__) == PWR_FLAG_WUFB15)     ? (READ_BIT(PWR->WUFB, PWR_WUFB_WUF15)         == \
                                          PWR_WUFB_WUF15)        : \
                                      ((__FLAG__) == PWR_FLAG_WUF)        ? (READ_BIT(PWR->SDWN_WUF, PWR_SDWN_WUF_WUF)   == \
                                          PWR_SDWN_WUF_WUF)      : \
                                      ((__FLAG__) == PWR_FLAG_DEEPSTOPF)  ? (READ_BIT(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF) == \
                                          PWR_EXTSRR_DEEPSTOPF)  : \
                                      (READ_BIT(PWR->EXTSRR, PWR_EXTSRR_RFPHASEF)  == PWR_EXTSRR_RFPHASEF))

/** @brief  Clear PWR flags.
  * @param  __FLAG__ : Specifies the flag to clear.
  *                    This parameter can be one of the following values when available :
  *                    @arg @ref PWR_FLAG_LPUART      : LPUART Internal wakeup flag.
  *                                                     Indicates that a wakeup from LPUART occurred since last clear.
  *                    @arg @ref PWR_FLAG_RTC         : RTC Internal wakeup flag.
  *                                                     Indicates that a wakeup from RTC occurred since last clear.
  *                    @arg @ref PWR_FLAG_LCD         : LCD Internal wakeup flag.
  *                                                     Indicates that a wakeup from LCD occurred since last clear.
  *                    @arg @ref PWR_FLAG_COMP        : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_LCSC        : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_MRSUBG      : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_MRSUBGHCPU  : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_LPAWUR      : COMP Internal wakeup flag.
  *                                                     Indicates that a wakeup from COMP occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA0       : PA0 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA0 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA1       : PA1 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA1 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA2       : PA2 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA2 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA3       : PA3 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA3 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA4       : PA4 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA4 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA5       : PA5 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA5 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA6       : PA6 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA6 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA7       : PA7 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA7 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA8       : PA8 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA8 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA9       : PA9 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA9 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA10      : PA10 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA10 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA11      : PA11 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA11 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA12      : PA12 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA12 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA13      : PA13 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA13 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA14      : PA14 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA14 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFA15      : PA15 pin wakeup flag.
  *                                                     Indicates that a wakeup from PA15 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB0       : PB0 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB0 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB1       : PB1 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB1 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB2       : PB2 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB2 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB3       : PB3 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB3 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB4       : PB4 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB4 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB5       : PB5 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB5 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB6       : PB6 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB6 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB7       : PB7 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB7 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB8       : PB8 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB8 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB9       : PB9 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB9 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB10      : PB10 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB10 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB11      : PB11 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB11 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB12      : PB12 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB12 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB13      : PB13 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB13 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB14      : PB14 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB14 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUFB15      : PB15 pin wakeup flag.
  *                                                     Indicates that a wakeup from PB15 pin occurred since last clear.
  *                    @arg @ref PWR_FLAG_WUF         : PB0 pin wakeup from shutdown flag
  *                                                     Indicates a shutdown wakeup from PB0 pin occurred..
  *                    @arg @ref PWR_FLAG_RFPHASEF    : RFPHASE Flag.
  *                                                     Indicates that the RF SUBGHz IP is awake and may require
  *                                                     a system attention.
  *                    @arg @ref PWR_FLAG_DEEPSTOPF   : System DEEPTSTOP Flag.
  *                                                     Indicates that the device entered a DEEPSTOP mode.
  * @retval None.
  */
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)( \
                                        ((__FLAG__) == PWR_FLAG_LPUART)     ? (SET_BIT(PWR->IWUF, PWR_IWUF_IWUF0))         : \
                                        ((__FLAG__) == PWR_FLAG_RTC)        ? (SET_BIT(PWR->IWUF, PWR_IWUF_IWUF1))         : \
                                        ((__FLAG__) == PWR_FLAG_LCD)        ? (SET_BIT(PWR->IWUF, PWR_IWUF_IWUF2))         : \
                                        ((__FLAG__) == PWR_FLAG_COMP)       ? (SET_BIT(PWR->IWUF, PWR_IWUF_IWUF3))         : \
                                        ((__FLAG__) == PWR_FLAG_LCSC)       ? (SET_BIT(PWR->IWUF, PWR_IWUF_IWUF4))         : \
                                        ((__FLAG__) == PWR_FLAG_MRSUBG)     ? (SET_BIT(PWR->IWUF, PWR_IWUF_WMRSUBGF))      : \
                                        ((__FLAG__) == PWR_FLAG_MRSUBGHCPU) ? (SET_BIT(PWR->IWUF, PWR_IWUF_WMRSUBGHCPUF))  : \
                                        ((__FLAG__) == PWR_FLAG_LPAWUR)     ? (SET_BIT(PWR->IWUF, PWR_IWUF_WLPAWURF))      : \
                                        ((__FLAG__) == PWR_FLAG_WUFA0)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF0))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA1)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF1))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA2)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF2))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA3)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF3))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA4)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF4))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA5)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF5))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA6)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF6))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA7)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF7))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA8)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF8))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA9)      ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF9))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFA10)     ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF10))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFA11)     ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF11))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFA12)     ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF12))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFA13)     ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF13))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFA14)     ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF14))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFA15)     ? (SET_BIT(PWR->WUFA, PWR_WUFA_WUF15))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFB0)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF0))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB1)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF1))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB2)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF2))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB3)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF3))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB4)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF4))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB5)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF5))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB6)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF6))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB7)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF7))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB8)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF8))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB9)      ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF9))          : \
                                        ((__FLAG__) == PWR_FLAG_WUFB10)     ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF10))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFB11)     ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF11))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFB12)     ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF12))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFB13)     ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF13))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFB14)     ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF14))         : \
                                        ((__FLAG__) == PWR_FLAG_WUFB15)     ? (SET_BIT(PWR->WUFB, PWR_WUFB_WUF15))         : \
                                        ((__FLAG__) == PWR_FLAG_WUF)        ? (CLEAR_BIT(PWR->SDWN_WUF, PWR_SDWN_WUF_WUF)) : \
                                        ((__FLAG__) == PWR_FLAG_DEEPSTOPF)  ? (SET_BIT(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF)) : \
                                        (SET_BIT(PWR->EXTSRR, PWR_EXTSRR_RFPHASEF)))

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
#define __HAL_PWR_PVD_CLEAR_FLAG()  WRITE_REG(SYSCFG->PWRC_ISCR, SYSCFG_PWRC_ISCR_PVD_ISC)

/**
  * @brief Check if the wake up from SHUTWDOWN happens from PB0 or not.
  * @retval None
  */
#define __HAL_PWR_IO_WAKEUP_SHUTDOWN_GET_FLAG()  LL_PWR_IsIOWakeupSDN()

/**
  * @brief Check if the wake up from SHUTWDOWN happens from PB0 or not.
  * @retval None
  */
#define __HAL_PWR_CLEAR_IO_WAKEUP_SHUTDOWN_FLAG()  LL_PWR_ClearIOWakeupFlagSDN()

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


#define IS_PWR_PVD_MODE(MODE)  (((MODE) == PWR_PVD_MODE_NORMAL)||\
                                ((MODE) == PWR_PVD_MODE_IT))

#define IS_PWR_WAKEUP_SOURCE(PIN) (((PIN) == PWR_WAKEUP_ALL)       ||\
                                   ((PIN) == PWR_WAKEUP_PIN0 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN1 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN2 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN3 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN4 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN5 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN6 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN7 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN8 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN9 )     ||\
                                   ((PIN) == PWR_WAKEUP_PIN10)     ||\
                                   ((PIN) == PWR_WAKEUP_PIN11)     ||\
                                   ((PIN) == PWR_WAKEUP_PIN12)     ||\
                                   ((PIN) == PWR_WAKEUP_PIN13)     ||\
                                   ((PIN) == PWR_WAKEUP_PIN14)     ||\
                                   ((PIN) == PWR_WAKEUP_PIN15)     ||\
                                   ((PIN) == PWR_WAKEUP_LPAWUR)    ||\
                                   ((PIN) == PWR_WAKEUP_SUBG)      ||\
                                   ((PIN) == PWR_WAKEUP_SUBGHOST)  ||\
                                   ((PIN) == PWR_WAKEUP_LCSC)      ||\
                                   ((PIN) == PWR_WAKEUP_COMP)      ||\
                                   ((PIN) == PWR_WAKEUP_LCD)       ||\
                                   ((PIN) == PWR_WAKEUP_RTC)       ||\
                                   ((PIN) == PWR_WAKEUP_LPUART))

#define IS_PWR_WAKEUP_POLARITY(POL)  (((POL) == PWR_WUP_RISIEDG) ||\
                                      ((POL) == PWR_WUP_FALLEDG))

/**
  * @}
  */

/* Include PWR HAL Extended module */
#include "stm32wl3x_hal_pwr_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions  PWR Exported Functions
  * @{
  */

/* Programmable voltage detector functions  ***********************************/
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void              HAL_PWR_EnablePVD(void);
void              HAL_PWR_DisablePVD(void);
void              HAL_PWR_PVDCallback(void);

/* Wake up pins configuration functions ***************************************/
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPort, uint32_t WakeUpPin, uint32_t WakeUpPolarity);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPort, uint32_t WakeUpPin);
uint32_t HAL_PWR_GetClearWakeupSource(uint32_t WakeUpPort);

/* Low power modes configuration functions ************************************/
HAL_StatusTypeDef HAL_PWR_ConfigDEEPSTOP(PWR_DEEPSTOPTypeDef *sConfigDEEPSTOP);
HAL_StatusTypeDef HAL_PWR_ConfigSHUTDOWN(PWR_SHUTDOWNTypeDef *sConfigSHUTDOWN);
void HAL_PWR_EnterSLEEPMode(void);
void HAL_PWR_EnterDEEPSTOPMode(void);


/* Sleep on exit and sev on pending configuration functions *******************/
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

/* Interrupt handler functions ************************************************/
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_WKUP_IRQHandler(void);
void HAL_PWR_WKUPx_Callback(uint32_t wakeupPort, uint32_t wakeupIOs);

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


#endif /* STM32WL3x_HAL_PWR_H */
