/**
  ******************************************************************************
  * @file    stm32wl3x_ll_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR LL module.
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
#ifndef STM32WL3x_LL_PWR_H
#define STM32WL3x_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x.h"

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_LOW_PWR_MODE Low Power mode selection
  * @{
  */
#define LL_PWR_MODE_DEEPSTOP               (0x000000000U)   /*!< Low Power Mode Selection DEEPSTOP mode */
#define LL_PWR_MODE_SHUTDOWN               (PWR_CR1_LPMS)   /*!< Low Power Mode Selection SHUTDOWN mode */
#define LL_PWR_MODE_ULTRA_DEEPSTOP         (PWR_CR1_LPMS)   /*!< Low Power Mode Selection SHUTDOWN mode */
/**
  * @}
  */

/** @defgroup PWR_LL_RAMRET RAM Retention enable in Power Save mode
  * @{
  */
#define LL_PWR_RAMRET_1    PWR_CR2_RAMRET1           /*!< RAM1 bank retention in Power Save mode */

/**
  * @}
  */

/** @defgroup PWR_LL_PVDLEVEL PVDLEVEL
  * @{
  */
#define LL_PWR_PVDLEVEL_0                  (0x00000000U)                                     /*!< VPVD0 around 2.0 V */
#define LL_PWR_PVDLEVEL_1                  (PWR_CR2_PVDLS_0)                                 /*!< VPVD1 around 2.2 V */
#define LL_PWR_PVDLEVEL_2                  (PWR_CR2_PVDLS_1)                                 /*!< VPVD2 around 2.4 V */
#define LL_PWR_PVDLEVEL_3                  (PWR_CR2_PVDLS_1 | PWR_CR2_PVDLS_0)               /*!< VPVD3 around 2.5 V */
#define LL_PWR_PVDLEVEL_4                  (PWR_CR2_PVDLS_2)                                 /*!< VPVD4 around 2.6 V */
#define LL_PWR_PVDLEVEL_5                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_0)               /*!< VPVD5 around 2.8 V */
#define LL_PWR_PVDLEVEL_6                  (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_1)               /*!< VPVD6 around 2.9 V */
#define LL_PWR_PVDLEVEL_7                  (PWR_CR2_PVDLS)                                   /*!< External input analog voltage   (Compare internally to VBGP) */
/**
  * @}
  */

/** @defgroup PWR_LL_WAKEUP_SOURCE_PORT IO Port for wakeup source
  * @{
  */
#define LL_PWR_WAKEUP_PORTA   (0x00000000U)                  /*!< IO port A to get out from DEEPSTOP mode */
#define LL_PWR_WAKEUP_PORTB   (0x00000001U)                  /*!< IO port B to get out from DEEPSTOP mode */
/**
  * @}
  */


/** @defgroup PWR_LL_WAKEUP_SOURCE Wakeup Source
  * @{
  */

#define LL_PWR_WAKEUP_ALL           0x0000FFFF               /*!< Enable all the wakeup source                    */
#define LL_PWR_WAKEUP_PIN0          (uint32_t)(1U << 0U)     /*!< Enable the wakeup source PIN0                   */
#define LL_PWR_WAKEUP_PIN1          (uint32_t)(1U << 1U)     /*!< Enable the wakeup source PIN1                   */
#define LL_PWR_WAKEUP_PIN2          (uint32_t)(1U << 2U)     /*!< Enable the wakeup source PIN2                   */
#define LL_PWR_WAKEUP_PIN3          (uint32_t)(1U << 3U)     /*!< Enable the wakeup source PIN3                   */
#define LL_PWR_WAKEUP_PIN4          (uint32_t)(1U << 4U)     /*!< Enable the wakeup source PIN4                   */
#define LL_PWR_WAKEUP_PIN5          (uint32_t)(1U << 5U)     /*!< Enable the wakeup source PIN5                   */
#define LL_PWR_WAKEUP_PIN6          (uint32_t)(1U << 6U)     /*!< Enable the wakeup source PIN6                   */
#define LL_PWR_WAKEUP_PIN7          (uint32_t)(1U << 7U)     /*!< Enable the wakeup source PIN7                   */
#define LL_PWR_WAKEUP_PIN8          (uint32_t)(1U << 8U)     /*!< Enable the wakeup source PIN8                   */
#define LL_PWR_WAKEUP_PIN9          (uint32_t)(1U << 9U)     /*!< Enable the wakeup source PIN9                   */
#define LL_PWR_WAKEUP_PIN10         (uint32_t)(1U << 10U)    /*!< Enable the wakeup source PIN10                  */
#define LL_PWR_WAKEUP_PIN11         (uint32_t)(1U << 11U)    /*!< Enable the wakeup source PIN11                  */
#define LL_PWR_WAKEUP_PIN12         (uint32_t)(1U << 12U)    /*!< Enable the wakeup source PIN12                  */
#define LL_PWR_WAKEUP_PIN13         (uint32_t)(1U << 13U)    /*!< Enable the wakeup source PIN13                  */
#define LL_PWR_WAKEUP_PIN14         (uint32_t)(1U << 14U)    /*!< Enable the wakeup source PIN14                  */
#define LL_PWR_WAKEUP_PIN15         (uint32_t)(1U << 15U)    /*!< Enable the wakeup source PIN15                  */

#define LL_PWR_WAKEUP_LPAWUR        PWR_IEWU_EWLPAWUR        /*!< Enable wakeup on LPAWUR RFIP event              */
#define LL_PWR_WAKEUP_SUBG          PWR_IEWU_EWMRSUBG        /*!< Enable wakeup on MRSUBG RFIP event              */
#define LL_PWR_WAKEUP_SUBGHOST      PWR_IEWU_EWMRSUBGHCPU    /*!< Enable wakeup on MRSUBG Host CPU event          */
#define LL_PWR_WAKEUP_LCSC          PWR_IEWU_EIWL4           /*!< Enable wakeup on internal event (LCSC)          */
#define LL_PWR_WAKEUP_COMP          PWR_IEWU_EIWL3           /*!< Enable wakeup on internal event (COMP)          */
#define LL_PWR_WAKEUP_LCD           PWR_IEWU_EIWL2           /*!< Enable wakeup on internal event (LCD)           */
#define LL_PWR_WAKEUP_RTC           PWR_IEWU_EIWL1           /*!< Enable wakeup on internal event (RTC)           */
#define LL_PWR_WAKEUP_LPUART        PWR_IEWU_EIWL0           /*!< Enable wakeup on internal event (LPUART)        */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief
  * @{
  */
#define LL_PWR_FLAG_LPAWUR             PWR_IWUF_WLPAWURF                       /*!< LPAWUR wakeup flag                 */
#define LL_PWR_FLAG_MRSUBGHCPU         PWR_IWUF_WMRSUBGHCPUF                   /*!< MRSUBG Host CPU wakeup flag        */
#define LL_PWR_FLAG_MRSUBG             PWR_IWUF_WMRSUBGF                       /*!< MRSUBG wakeup flag                 */
#define LL_PWR_FLAG_LCSC               PWR_IWUF_IWUF4                          /*!< Internal wakeup LCSC flag          */
#define LL_PWR_FLAG_COMP               PWR_IWUF_IWUF3                          /*!< Internal wakeup COMP flag          */
#define LL_PWR_FLAG_LCD                PWR_IWUF_IWUF2                          /*!< Internal wakeup LCD flag           */
#define LL_PWR_FLAG_RTC                PWR_IWUF_IWUF1                          /*!< Internal wakeup RTC flag           */
#define LL_PWR_FLAG_LPUART             PWR_IWUF_IWUF0                          /*!< Internal wakeup LPUART flag        */
#define LL_PWR_WUFA_WUF0               PWR_WUFA_WUF0                           /*!< Wakeup flag on PA0                 */
#define LL_PWR_WUFA_WUF1               PWR_WUFA_WUF1                           /*!< Wakeup flag on PA1                 */
#define LL_PWR_WUFA_WUF2               PWR_WUFA_WUF2                           /*!< Wakeup flag on PA2                 */
#define LL_PWR_WUFA_WUF3               PWR_WUFA_WUF3                           /*!< Wakeup flag on PA3                 */
#define LL_PWR_WUFA_WUF4               PWR_WUFA_WUF4                           /*!< Wakeup flag on PA4                 */
#define LL_PWR_WUFA_WUF5               PWR_WUFA_WUF5                           /*!< Wakeup flag on PA5                 */
#define LL_PWR_WUFA_WUF6               PWR_WUFA_WUF6                           /*!< Wakeup flag on PA6                 */
#define LL_PWR_WUFA_WUF7               PWR_WUFA_WUF7                           /*!< Wakeup flag on PA7                 */
#define LL_PWR_WUFA_WUF8               PWR_WUFA_WUF8                           /*!< Wakeup flag on PA8                 */
#define LL_PWR_WUFA_WUF9               PWR_WUFA_WUF9                           /*!< Wakeup flag on PA9                 */
#define LL_PWR_WUFA_WUF11              PWR_WUFA_WUF11                          /*!< Wakeup flag on PA11                */
#define LL_PWR_WUFA_WUF12              PWR_WUFA_WUF12                          /*!< Wakeup flag on PA12                */
#define LL_PWR_WUFA_WUF13              PWR_WUFA_WUF13                          /*!< Wakeup flag on PA13                */
#define LL_PWR_WUFA_WUF14              PWR_WUFA_WUF14                          /*!< Wakeup flag on PA14                */
#define LL_PWR_WUFA_WUF15              PWR_WUFA_WUF15                          /*!< Wakeup flag on PA15                */
#define LL_PWR_WUFB_WUF0               PWR_WUFB_WUF0                           /*!< Wakeup flag on PB0                 */
#define LL_PWR_WUFB_WUF1               PWR_WUFB_WUF1                           /*!< Wakeup flag on PB1                 */
#define LL_PWR_WUFB_WUF2               PWR_WUFB_WUF2                           /*!< Wakeup flag on PB2                 */
#define LL_PWR_WUFB_WUF3               PWR_WUFB_WUF3                           /*!< Wakeup flag on PB3                 */
#define LL_PWR_WUFB_WUF4               PWR_WUFB_WUF4                           /*!< Wakeup flag on PB4                 */
#define LL_PWR_WUFB_WUF5               PWR_WUFB_WUF5                           /*!< Wakeup flag on PB5                 */
#define LL_PWR_WUFB_WUF6               PWR_WUFB_WUF6                           /*!< Wakeup flag on PB6                 */
#define LL_PWR_WUFB_WUF7               PWR_WUFB_WUF7                           /*!< Wakeup flag on PB7                 */
#define LL_PWR_WUFB_WUF8               PWR_WUFB_WUF8                           /*!< Wakeup flag on PB8                 */
#define LL_PWR_WUFB_WUF9               PWR_WUFB_WUF9                           /*!< Wakeup flag on PB9                 */
#define LL_PWR_WUFB_WUF10              PWR_WUFB_WUF10                          /*!< Wakeup flag on PB10                */
#define LL_PWR_WUFB_WUF11              PWR_WUFB_WUF11                          /*!< Wakeup flag on PB11                */
#define LL_PWR_WUFB_WUF12              PWR_WUFB_WUF12                          /*!< Wakeup flag on PB12                */
#define LL_PWR_WUFB_WUF13              PWR_WUFB_WUF13                          /*!< Wakeup flag on PB13                */
#define LL_PWR_WUFB_WUF14              PWR_WUFB_WUF14                          /*!< Wakeup flag on PB14                */
#define LL_PWR_WUFB_WUF15              PWR_WUFB_WUF15                          /*!< Wakeup flag on PB15                */
#define LL_PWR_SR2_PVDO                PWR_SR2_PVDO                            /*!< Power voltage Detector Output      */
#define LL_PWR_SR2_REGMS               PWR_SR2_REGMS                           /*!< Main regulator ready status        */
#define LL_PWR_SR2_REGLPS              PWR_SR2_REGLPS                          /*!< Low Power regulator ready status   */
#define LL_PWR_SR2_SMPSRDY             PWR_SR2_SMPSRDY                         /*!< SMPS ready status                  */
#define LL_PWR_SR2_SMPSENR             PWR_SR2_SMPSENR                         /*!< SMPS RUN mode status               */
#define LL_PWR_SR2_SMPSBYPR            PWR_SR2_SMPSBYPR                        /*!< SMPS PRECHARGE mode status         */

/**
  * @}
  */

/** @defgroup PWR_LL_IO_PUD_CFG IOs PU/PD configuration
  * @{
  */
#define LL_PWR_GPIO_BIT_0          (uint32_t)(1U << 0U)     /*!< GPIO port I/O pin 0  */
#define LL_PWR_GPIO_BIT_1          (uint32_t)(1U << 1U)     /*!< GPIO port I/O pin 1  */
#define LL_PWR_GPIO_BIT_2          (uint32_t)(1U << 2U)     /*!< GPIO port I/O pin 2  */
#define LL_PWR_GPIO_BIT_3          (uint32_t)(1U << 3U)     /*!< GPIO port I/O pin 3  */
#define LL_PWR_GPIO_BIT_4          (uint32_t)(1U << 4U)     /*!< GPIO port I/O pin 4  */
#define LL_PWR_GPIO_BIT_5          (uint32_t)(1U << 5U)     /*!< GPIO port I/O pin 5  */
#define LL_PWR_GPIO_BIT_6          (uint32_t)(1U << 6U)     /*!< GPIO port I/O pin 6  */
#define LL_PWR_GPIO_BIT_7          (uint32_t)(1U << 7U)     /*!< GPIO port I/O pin 7  */
#define LL_PWR_GPIO_BIT_8          (uint32_t)(1U << 8U)     /*!< GPIO port I/O pin 8  */
#define LL_PWR_GPIO_BIT_9          (uint32_t)(1U << 9U)     /*!< GPIO port I/O pin 9  */
#define LL_PWR_GPIO_BIT_10         (uint32_t)(1U << 10U)    /*!< GPIO port I/O pin 10 */
#define LL_PWR_GPIO_BIT_11         (uint32_t)(1U << 11U)    /*!< GPIO port I/O pin 11 */
#define LL_PWR_GPIO_BIT_12         (uint32_t)(1U << 12U)    /*!< GPIO port I/O pin 12 */
#define LL_PWR_GPIO_BIT_13         (uint32_t)(1U << 13U)    /*!< GPIO port I/O pin 13 */
#define LL_PWR_GPIO_BIT_14         (uint32_t)(1U << 14U)    /*!< GPIO port I/O pin 14 */
#define LL_PWR_GPIO_BIT_15         (uint32_t)(1U << 15U)    /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO GPIO Port
  * @{
  */
#define LL_PWR_GPIO_A                ((uint32_t)(&(PWR->PUCRA)))
#define LL_PWR_GPIO_B                ((uint32_t)(&(PWR->PUCRB)))

/**
  * @}
  */

/** @defgroup PWR_LL_WAKEUP_CFG IOs Wakeup configuration polarity
  * @{
  */
#define LL_PWR_WUP_RISIEDG (0x000000000U)   /*!< Detection of wakeup event on rising edge.  */
#define LL_PWR_WUP_FALLEDG (0x000000001U)   /*!< Detection of wakeup event on falling edge. */
/**
  * @}
  */

/** @defgroup PWR_LL_IO_LATCH_BOOT I/Os value latched at POR.
  * @{
  */
#define LL_PWR_PA8_LATCH_POR    PWR_SR2_IOBOOTVAL_0  /*!< PA8  input value latched at POR. */
#define LL_PWR_PA9_LATCH_POR    PWR_SR2_IOBOOTVAL_1  /*!< PA9  input value latched at POR. */
#define LL_PWR_PA10_LATCH_POR   PWR_SR2_IOBOOTVAL_2  /*!< PA10 input value latched at POR. */
#define LL_PWR_PA11_LATCH_POR   PWR_SR2_IOBOOTVAL_3  /*!< PA11 input value latched at POR. */
#if defined(PWR_SR2_IOBOOTVAL2_0)
#define LL_PWR_PB12_LATCH_POR   PWR_SR2_IOBOOTVAL2_0 /*!< PB12  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_0 */
#if defined(PWR_SR2_IOBOOTVAL2_1)
#define LL_PWR_PB13_LATCH_POR   PWR_SR2_IOBOOTVAL2_1 /*!< PB13  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_1 */
#if defined(PWR_SR2_IOBOOTVAL2_2)
#define LL_PWR_PB14_LATCH_POR   PWR_SR2_IOBOOTVAL2_2 /*!< PB14  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_2 */
#if defined(PWR_SR2_IOBOOTVAL2_3)
#define LL_PWR_PB15_LATCH_POR   PWR_SR2_IOBOOTVAL2_3 /*!< PB15  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_3 */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_MODE SMPS Mode
  * @{
  */
#define LL_PWR_SMPS       (0x000000000U)   /*!< SMPS is enabled     */
#define LL_PWR_NO_SMPS    PWR_CR5_NOSMPS   /*!< SMPS is disabled    */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_PRECHARGE_MODE SMPS PRECHARGE Mode
  * @{
  */
#define LL_PWR_NO_SMPS_PRECHARGE    (0x000000000U)     /*!< SMPS not in pecharge mode     */
#define LL_PWR_SMPS_PRECHARGE       PWR_CR5_SMPSFBYP   /*!< SMPS is disabled and bypassed in precharge mode    */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_BOF_MODE SMPS BOF Mode
  * @{
  */
#define LL_PWR_NO_SMPS_BOF    (0x000000000U)     /*!< SMPS BOF mode not enabled */
#define LL_PWR_SMPS_BOF       PWR_CR5_NOSMPSBOF  /*!< SMPS BOF mode enable      */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_BOF_STATIC_MODE SMPS BOF STATIC Mode
  * @{
  */
#define LL_PWR_NO_SMPS_BOF_STATIC    (0x000000000U)           /*!< SMPS BOF static mode not enabled */
#define LL_PWR_SMPS_BOF_STATIC       PWR_CR5_SMPS_BOF_STATIC  /*!< SMPS BOF static mode enable      */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_BOF_DYNAMIC_MODE SMPS BOF DYNAMIC Mode
  * @{
  */
#define LL_PWR_NO_SMPS_BOF_DYNAMIC    (0x000000000U)         /*!< SMPS BOF dynamic mode not enabled */
#define LL_PWR_SMPS_BOF_DYNAMIC       PWR_CR5_SMPS_BOF_DYN   /*!< SMPS BOF dynamic mode enable      */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_OPEN_MODE SMPS OPEN Mode during DEEPSTOP
  * @{
  */
#define LL_PWR_NO_SMPS_LPOPEN    (0x000000000U)      /*!< In DEEPSTOP, the SMPS is in PRECHARGE mode with output connected to VDDIO */
#define LL_PWR_SMPS_LPOPEN       PWR_CR5_SMPSLPOPEN  /*!< In DEEPSTOP, the SMPS is disabled with floating output                    */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_BOM SMPS BOM
  * @{
  */
#define LL_PWR_SMPS_BOM1       (0x000000000U)
#define LL_PWR_SMPS_BOM2       PWR_CR5_SMPSBOMSEL_0
#define LL_PWR_SMPS_BOM3       PWR_CR5_SMPSBOMSEL_1
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_OUTLVL SMPS Output Level
  * @{
  */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V20              (0x00000000U )                                                             /*!< 0000: 1.20V (min VBAT = 1.95V)           */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V30              (PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0 )                                     /*!< 0011: 1.30V (min VBAT = 1.95V)           */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V40              (PWR_CR5_SMPSLVL_2)                                                        /*!< 0100: 1.40V (min VBAT = 1.95V) (default) */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V50              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)                                      /*!< 0101: 1.50V (min VBAT = 1.95V)           */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V60              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)                                      /*!< 0110: 1.60V (min VBAT = 1.95V)           */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V70              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)                    /*!< 0111: 1.70V (min VBAT = 2V)              */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V80              (PWR_CR5_SMPSLVL_3)                                                        /*!< 1000: 1.80V (min VBAT = 2.1V)            */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V90              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_0)                                      /*!< 1001: 1.90V (min VBAT = 2.2V)            */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_2V00              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1)                                      /*!< 1010: 2V (min VBAT = 2.3V)               */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_2V10              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)                    /*!< 1011: 2.1V (min VBAT = 2.4V)             */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_2V20              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2)                                      /*!< 1100: 2.2V (min VBAT = 2.5V)             */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_2V30              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)                    /*!< 1101: 2.3V (min VBAT = 2.6V)             */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_2V40              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)  /*!< 1111: 2.4V (min VBAT = 2.7V)             */

/**
  * @}
  */

#if defined(PWR_CR5_SMPS_PRECH_CUR_SEL)
/** @defgroup PWR_LL_SMPS_PRECHARGE_LIMIT_CURRENT Select SMPS PRECHARGE limit current
  * @{
  */
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_2_5     (0x000000000U)
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_5       (PWR_CR5_SMPS_PRECH_CUR_SEL_0)
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_10      (PWR_CR5_SMPS_PRECH_CUR_SEL_1)
#define LL_PWR_SMPS_PRECH_LIMIT_CUR_20      (PWR_CR5_SMPS_PRECH_CUR_SEL_0|PWR_CR5_SMPS_PRECH_CUR_SEL_1)
/**
  * @}
  */
#endif /* PWR_CR5_SMPS_PRECH_CUR_SEL */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_Configuration Configuration Function
  * @{
  */

/**
  * @brief  Enable automatic IBIAS control during RUN or DEEPSTOP mode.
  * @rmtoll CR1          IBIAS_RUN_AUTO           LL_PWR_EnableIBIASAuto
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableIBIASAuto(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_IBIAS_RUN_AUTO);
}

/**
  * @brief  Disable automatic IBIAS control during RUN or DEEPSTOP mode.
  * @rmtoll CR1          IBIAS_RUN_AUTO           LL_PWR_DisableIBIASAuto
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableIBIASAuto(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_IBIAS_RUN_AUTO);
}

/**
  * @brief  Checks if automatic IBIAS control during RUN or DEEPSTOP mode is enabled or disabled.
  * @rmtoll CR1         IBIAS_RUN_AUTO      LL_PWR_IsEnabledIBIASAuto
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledIBIASAuto(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_IBIAS_RUN_AUTO) == (PWR_CR1_IBIAS_RUN_AUTO)) ? 1UL : 0UL);
}

/**
  * @brief  Enable IBIAS during RUN mode when automatic mode is disabled.
  * @rmtoll CR1          IBIAS_RUN_STATE           LL_PWR_EnableIBIASRun
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableIBIASRun(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_IBIAS_RUN_STATE);
}

/**
  * @brief  Disable IBIAS during RUN mode when automatic mode is disabled.
  * @rmtoll CR1          IBIAS_RUN_STATE           LL_PWR_DisableIBIASRun
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableIBIASRun(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_IBIAS_RUN_STATE);
}

/**
  * @brief  Checks if IBIAS is enabled or disabled, during RUN mode when automatic mode is disabled.
  * @rmtoll CR1         IBIAS_RUN_STATE      LL_PWR_IsEnabledIBIASRun
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledIBIASRun(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_IBIAS_RUN_STATE) == (PWR_CR1_IBIAS_RUN_STATE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the BOR reset supervising during SHUTDOWN mode.
  * @rmtoll CR1          ENSDNBOR           LL_PWR_EnableBORinSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBORinSDN(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_ENSDNBOR);
}

/**
  * @brief  Disable the BOR reset supervising during SHUTDOWN mode.
  * @rmtoll CR1          ENSDNBOR           LL_PWR_DisableBORinSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBORinSDN(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_ENSDNBOR);
}

/**
  * @brief  Checks if BOR is enabled or disabled during SHUTDOWN mode.
  * @rmtoll CR1         ENSDNBOR      LL_PWR_IsEnabledBORinSDN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBORinSDN(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_ENSDNBOR) == (PWR_CR1_ENSDNBOR)) ? 1UL : 0UL);
}

#if defined(PWR_SDWN_WUEN_WUEN)
/**
  * @brief  Shutdown/Ultra_deepstop I/O Wakeup enable.
  * @rmtoll SDWN_WUEN          WUEN           LL_PWR_EnableIOWakeupSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableIOWakeupSDN(void)
{
  SET_BIT(PWR->SDWN_WUEN, PWR_SDWN_WUEN_WUEN);
}

/**
  * @brief  Shutdown/Ultra_deepstop I/O Wakeup disable.
  * @rmtoll SDWN_WUEN          WUEN           LL_PWR_DisableIOWakeupSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableIOWakeupSDN(void)
{
  CLEAR_BIT(PWR->SDWN_WUEN, PWR_SDWN_WUEN_WUEN);
}

/**
  * @brief  Checks if Shutdown/Ultra_deepstop I/O Wakeup is enabled or disabled.
  * @rmtoll SDWN_WUEN         WUEN     LL_PWR_IsEnabledIOWakeupSDN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledIOWakeupSDN(void)
{
  return ((READ_BIT(PWR->SDWN_WUEN, PWR_SDWN_WUEN_WUEN) == (PWR_SDWN_WUEN_WUEN)) ? 1UL : 0UL);
}

/**
  * @brief  Shutdown/Ultra_deepstop I/O Wakeup Polarity configuration.
  * @rmtoll SDWN_WUPOL          WUPOL           LL_PWR_IOWakeupPolaritySDN
  * @param  pol IO wakeup polarity. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WUP_RISIEDG
  *         @arg @ref LL_PWR_WUP_FALLEDG
  * @retval None
  * @note The wakeup from shutdown or ultra_deepstop can happen on pulse or level detection
  */
__STATIC_INLINE void LL_PWR_IOWakeupPolaritySDN(uint8_t pol)
{
  MODIFY_REG_FIELD(PWR->SDWN_WUPOL, PWR_SDWN_WUPOL_WUPOL, pol);
}

/**
  * @brief  Checks if Shutdown/Ultra_deepstop I/O Wakeup occurred.
  * @rmtoll SDWN_WUF         WUF     LL_PWR_IsIOWakeupSDN
  * @retval State of bit (1 or 0)
  * @note For STM32WL3RX device the I/O wakeup from shutdown and ultra-deepstop modes can be occurred
          by the following pins: PB0, PA0, PA7, PA8, PA9, and PA11.
  * @note For STM32WL3XX device The I/O wakeup from shutdown mode can be occurred
          by PB0 pin.

  */
__STATIC_INLINE uint32_t LL_PWR_IsIOWakeupSDN(void)
{
  return ((READ_BIT(PWR->SDWN_WUF, PWR_SDWN_WUF_WUF) == (PWR_SDWN_WUF_WUF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear I/O Wakeup occurred flag
  * @rmtoll SDWN_WUF          WUF           LL_PWR_ClearIOWakeupFlagSDN
  * @retval None
  * @note For STM32WL3RX device the I/O wakeup from shutdown and ultra-deepstop modes can be occurred
          by the following pins: PB0, PA0, PA7, PA8, PA9, and PA11
  * @note For STM32WL3XX device The I/O wakeup from shutdown mode can be occurred
          by PB0 pin
  */
__STATIC_INLINE void LL_PWR_ClearIOWakeupFlagSDN(void)
{
  CLEAR_BIT(PWR->SDWN_WUF, PWR_SDWN_WUF_WUF);
}
#endif /* PWR_SDWN_WUEN_WUEN */

/**
  * @brief  Select the low-power mode.
  * @rmtoll CR1          LPMS           LL_PWR_LowPowerMode
  * @param  LowPowerMode Low Power Mode Selection. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_DEEPSTOP
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  *         @arg @ref LL_PWR_MODE_ULTRA_DEEPSTOP
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t LowPowerMode)
{
  MODIFY_REG_FIELD(PWR->CR1, PWR_CR1_LPMS, LowPowerMode);
}

/**
  * @brief  Get Low-Power mode
  * @rmtoll CR1          LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_DEEPSTOP
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  *         @arg @ref LL_PWR_MODE_ULTRA_DEEPSTOP
  */

__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPMS));
}

/**
  * @brief  Enabled the temperature sensor.
  * @rmtoll CR2          ENTS           LL_PWR_EnableTempSens
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableTempSens(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_ENTS);
}

/**
  * @brief  Disable the temperature sensor.
  * @rmtoll CR2          ENTS           LL_PWR_DisableTempSens
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableTempSens(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_ENTS);
}

/**
  * @brief  Checks if temperature sensor is enabled or disabled.
  * @rmtoll CR2         ENTS     LL_PWR_IsEnabledTempSens
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledTempSens(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_ENTS) == (PWR_CR2_ENTS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the RAM bank retention.
  * @rmtoll CR2         RAMRET1      LL_PWR_EnableRAMBankRet
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableRAMBankRet(void)
{
  SET_BIT(PWR->CR2, LL_PWR_RAMRET_1);
}

/**
  * @brief  Disable the RAM bank retention.
  * @rmtoll CR2         RAMRET1      LL_PWR_DisableRAMBankRet
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableRAMBankRet(void)
{
  CLEAR_BIT(PWR->CR2, LL_PWR_RAMRET_1);
}

/**
  * @brief  Get the RAM banks retention selected.
  * @rmtoll CR2         RAMRET1       LL_PWR_GetRAMBankRet
  * @retval RAM bank selection. This parameter can be the following value:
  *         @arg @ref LL_PWR_RAMRET_1
  */
__STATIC_INLINE uint32_t LL_PWR_GetRAMBankRet(void)
{
  return (READ_BIT(PWR->CR2, PWR_CR2_RAMRET1) ? 1UL : 0UL);
}

/**
  * @brief  Enable the PVD (Programmable Voltage Detector).
  * @rmtoll CR2          PVDE           LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Disable the PVD (Programmable Voltage Detector).
  * @rmtoll CR2          PVDE           LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Checks if PVD is enabled or disabled.
  * @rmtoll CR2         PVDE      LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_PVDE) == (PWR_CR2_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Set PVD voltage level.
  * @rmtoll CR2         PVDLS      LL_PWR_SetPVDLevel
  * @param  PVDLevel PVD voltage level selection. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_PVDLS, PVDLevel);
}

/**
  * @brief  Get PVD voltage level.
  * @rmtoll CR2         PVDLS      LL_PWR_GetPVDLevel
  * @retval PVD voltage level selection. The parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR2, PWR_CR2_PVDLS));
}

/**
  * @brief  Enable IO Wakeup Source to get out of DEEPSTOP mode.
  * @rmtoll EWUA             LL_PWR_EnableWakeUpPin
  *         EWUB             LL_PWR_EnableWakeUpPin
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @param  WakeUpPin Enable the wakeup sources. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN0
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN9
  *         @arg @ref LL_PWR_WAKEUP_PIN10
  *         @arg @ref LL_PWR_WAKEUP_PIN11
  *         @arg @ref LL_PWR_WAKEUP_PIN12
  *         @arg @ref LL_PWR_WAKEUP_PIN13
  *         @arg @ref LL_PWR_WAKEUP_PIN14
  *         @arg @ref LL_PWR_WAKEUP_PIN15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t Port, uint32_t WakeUpPin)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    SET_BIT(PWR->EWUA, (WakeUpPin & 0x0000FFFF));
  }
  else
  {
    SET_BIT(PWR->EWUB, (WakeUpPin & 0x0000FFFF));
  }
}

/**
  * @brief  Disable IO Wakeup Source to get out of DEEPSTOP mode.
  * @rmtoll EWUA             LL_PWR_DisableWakeUpPin
  *         EWUB             LL_PWR_DisableWakeUpPin
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @param  WakeUpPin Disable the wakeup sources. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN0
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN9
  *         @arg @ref LL_PWR_WAKEUP_PIN10
  *         @arg @ref LL_PWR_WAKEUP_PIN11
  *         @arg @ref LL_PWR_WAKEUP_PIN12
  *         @arg @ref LL_PWR_WAKEUP_PIN13
  *         @arg @ref LL_PWR_WAKEUP_PIN14
  *         @arg @ref LL_PWR_WAKEUP_PIN15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t Port, uint32_t WakeUpPin)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    CLEAR_BIT(PWR->EWUA, (WakeUpPin & 0x0000FFFF));
  }
  else
  {
    CLEAR_BIT(PWR->EWUB, (WakeUpPin & 0x0000FFFF));
  }
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll EWUA/EWUB        LL_PWR_IsEnabledWakeUpPin
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @param  WakeUpPin Wakeup sources enabled. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN0
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN9
  *         @arg @ref LL_PWR_WAKEUP_PIN10
  *         @arg @ref LL_PWR_WAKEUP_PIN11
  *         @arg @ref LL_PWR_WAKEUP_PIN12
  *         @arg @ref LL_PWR_WAKEUP_PIN13
  *         @arg @ref LL_PWR_WAKEUP_PIN14
  *         @arg @ref LL_PWR_WAKEUP_PIN15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t Port, uint32_t WakeUpPin)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    return ((READ_BIT(PWR->EWUA, (WakeUpPin & 0x0000FFFF)) == (WakeUpPin & 0x0000FFFF)) ? 1UL : 0UL);
  }
  else
  {
    return ((READ_BIT(PWR->EWUB, (WakeUpPin & 0x0000FFFF)) == (WakeUpPin & 0x0000FFFF)) ? 1UL : 0UL);
  }
}

/**
  * @brief  Set the Wake-Up pin polarity low for the event detection.
  * @rmtoll WUPA/WUPB              LL_PWR_SetWakeUpPinPolarityLow
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @param  WakeUpPin wakeup sources to configure. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN0
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN9
  *         @arg @ref LL_PWR_WAKEUP_PIN10
  *         @arg @ref LL_PWR_WAKEUP_PIN11
  *         @arg @ref LL_PWR_WAKEUP_PIN12
  *         @arg @ref LL_PWR_WAKEUP_PIN13
  *         @arg @ref LL_PWR_WAKEUP_PIN14
  *         @arg @ref LL_PWR_WAKEUP_PIN15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t Port, uint32_t WakeUpPin)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    SET_BIT(PWR->WUPA, (WakeUpPin & 0x0000FFFF));
  }
  else
  {
    SET_BIT(PWR->WUPB, (WakeUpPin & 0x0000FFFF));
  }
}

/**
  * @brief  Set the polarity for the I/Os wakeup sources.
  * @rmtoll WUPA/WUPB               LL_PWR_SetWakeUpPinPolarityHigh
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @param  WakeUpPin IO to configure. This parameter can be a
  *         combination of the following values @arg @ref PWR_LL_WAKEUP_SOURCE
  * @retval None
  * @note   Please refer the user manual to know which wakeup source are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t Port, uint32_t WakeUpPin)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    CLEAR_BIT(PWR->WUPA, (WakeUpPin & 0x0000FFFF));
  }
  else
  {
    CLEAR_BIT(PWR->WUPB, (WakeUpPin & 0x0000FFFF));
  }
}

/**
  * @brief  Get the polarity for the I/Os wakeup sources.
  * @rmtoll WUPA/WUPB              LL_PWR_IsWakeUpPinPolarity
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @param  WakeUpPin IO wakeup sources configured. This parameter can be a one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN0
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN9
  *         @arg @ref LL_PWR_WAKEUP_PIN10
  *         @arg @ref LL_PWR_WAKEUP_PIN11
  *         @arg @ref LL_PWR_WAKEUP_PIN12
  *         @arg @ref LL_PWR_WAKEUP_PIN13
  *         @arg @ref LL_PWR_WAKEUP_PIN14
  *         @arg @ref LL_PWR_WAKEUP_PIN15
  * @retval The IO polarity to configure. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WUP_RISIEDG
  *         @arg @ref LL_PWR_WUP_FALLEDG
  */
__STATIC_INLINE uint32_t LL_PWR_IsWakeUpPinPolarity(uint32_t Port, uint32_t WakeUpPin)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    return (uint32_t)((READ_BIT(PWR->WUPA, (WakeUpPin & 0x0000FFFF))) ? 1UL : 0UL);
  }
  else
  {
    return (uint32_t)((READ_BIT(PWR->WUPB, (WakeUpPin & 0x0000FFFF))) ? 1UL : 0UL);
  }
}

/**
  * @brief  Get which IO source woken up the device after a DEEPSTOP.
  * @rmtoll WUFA/WUFB               LL_PWR_GetIOWakeupSource
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @retval Wakeup IO Source from DEEPSTOP. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN0
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN9
  *         @arg @ref LL_PWR_WAKEUP_PIN10
  *         @arg @ref LL_PWR_WAKEUP_PIN11
  *         @arg @ref LL_PWR_WAKEUP_PIN12
  *         @arg @ref LL_PWR_WAKEUP_PIN13
  *         @arg @ref LL_PWR_WAKEUP_PIN14
  *         @arg @ref LL_PWR_WAKEUP_PIN15
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeupSource(uint32_t Port)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    return (uint32_t)(READ_REG(PWR->WUFA) & 0x0000FFFF);
  }
  else
  {
    return (uint32_t)(READ_REG(PWR->WUFB) & 0x0000FFFF);
  }
}

/**
  * @brief  Clear the source that woken up the device after a DEEPSTOP.
  * @rmtoll WUFA/WUFB              LL_PWR_ClearWakeupSource
  * @param  Port IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PORTA
  *         @arg @ref LL_PWR_WAKEUP_PORTB
  * @param  WakeUpPin Wakeup IO Source from DEEPSTOP. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WUFA_WUF0
  *         @arg @ref LL_PWR_WUFA_WUF1
  *         @arg @ref LL_PWR_WUFA_WUF2
  *         @arg @ref LL_PWR_WUFA_WUF3
  *         @arg @ref LL_PWR_WUFA_WUF4
  *         @arg @ref LL_PWR_WUFA_WUF5
  *         @arg @ref LL_PWR_WUFA_WUF6
  *         @arg @ref LL_PWR_WUFA_WUF7
  *         @arg @ref LL_PWR_WUFA_WUF8
  *         @arg @ref LL_PWR_WUFA_WUF9
  *         @arg @ref LL_PWR_WUFA_WUF11
  *         @arg @ref LL_PWR_WUFA_WUF12
  *         @arg @ref LL_PWR_WUFA_WUF13
  *         @arg @ref LL_PWR_WUFA_WUF14
  *         @arg @ref LL_PWR_WUFA_WUF15
  *         @arg @ref LL_PWR_WUFB_WUF0
  *         @arg @ref LL_PWR_WUFB_WUF1
  *         @arg @ref LL_PWR_WUFB_WUF2
  *         @arg @ref LL_PWR_WUFB_WUF3
  *         @arg @ref LL_PWR_WUFB_WUF4
  *         @arg @ref LL_PWR_WUFB_WUF5
  *         @arg @ref LL_PWR_WUFB_WUF6
  *         @arg @ref LL_PWR_WUFB_WUF7
  *         @arg @ref LL_PWR_WUFB_WUF8
  *         @arg @ref LL_PWR_WUFB_WUF9
  *         @arg @ref LL_PWR_WUFB_WUF10
  *         @arg @ref LL_PWR_WUFB_WUF11
  *         @arg @ref LL_PWR_WUFB_WUF12
  *         @arg @ref LL_PWR_WUFB_WUF14
  *         @arg @ref LL_PWR_WUFB_WUF15
  */
__STATIC_INLINE void LL_PWR_ClearWakeupSource(uint32_t Port, uint32_t WakeUpPin)
{
  if (Port == LL_PWR_WAKEUP_PORTA)
  {
    WRITE_REG(PWR->WUFA, (WakeUpPin & 0x0000FFFF));
  }
  else
  {
    WRITE_REG(PWR->WUFB, (WakeUpPin & 0x0000FFFF));
  }
}

/**
  * @brief  Enable Internal Wakeup Source to get out of DEEPSTOP mode.
  * @rmtoll IEWU             LL_PWR_EnableInternWU
  * @param  WakeUpSource Enable the internal wakeup sources.
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LPAWUR
  *         @arg @ref LL_PWR_WAKEUP_SUBG
  *         @arg @ref LL_PWR_WAKEUP_SUBGHOST
  *         @arg @ref LL_PWR_WAKEUP_LCSC
  *         @arg @ref LL_PWR_WAKEUP_COMP
  *         @arg @ref LL_PWR_WAKEUP_LCD
  *         @arg @ref LL_PWR_WAKEUP_RTC
  *         @arg @ref LL_PWR_WAKEUP_LPUART
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableInternWU(uint32_t WakeUpSource)
{
  SET_BIT(PWR->IEWU, (WakeUpSource & 0x0000FFFF));
}

/**
  * @brief  Disable Internal Wakeup Source to get out of DEEPSTOP mode.
  * @rmtoll IEWU            LL_PWR_DisableInternWU
  * @param  WakeUpSource Disable the internal wakeup sources.
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LPAWUR
  *         @arg @ref LL_PWR_WAKEUP_SUBG
  *         @arg @ref LL_PWR_WAKEUP_SUBGHOST
  *         @arg @ref LL_PWR_WAKEUP_LCSC
  *         @arg @ref LL_PWR_WAKEUP_COMP
  *         @arg @ref LL_PWR_WAKEUP_LCD
  *         @arg @ref LL_PWR_WAKEUP_RTC
  *         @arg @ref LL_PWR_WAKEUP_LPUART
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableInternWU(uint32_t WakeUpSource)
{
  CLEAR_BIT(PWR->IEWU, (WakeUpSource & 0x0000FFFF));
}

/**
  * @brief  Is Internal Wakeup Source enabled.
  * @rmtoll IEWU         LL_PWR_IsEnabledInternWU
  * @param  WakeUpSource Wakeup sources enabled. This parameter can be a one the following values:
  *         @arg @ref LL_PWR_WAKEUP_LPAWUR
  *         @arg @ref LL_PWR_WAKEUP_SUBG
  *         @arg @ref LL_PWR_WAKEUP_SUBGHOST
  *         @arg @ref LL_PWR_WAKEUP_LCSC
  *         @arg @ref LL_PWR_WAKEUP_COMP
  *         @arg @ref LL_PWR_WAKEUP_LCD
  *         @arg @ref LL_PWR_WAKEUP_RTC
  *         @arg @ref LL_PWR_WAKEUP_LPUART
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledInternWU(uint32_t WakeUpSource)
{
  return ((READ_BIT(PWR->IEWU, (WakeUpSource & 0x0000FFFF)) == (WakeUpSource & 0x0000FFFF)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Polarity for the Internal wakeup sources.
  * @rmtoll IWUP               LL_PWR_SetWakeupInternalPolarity
  * @param  WakeUpSource Internal wakeup sources to configure.
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LPAWUR
  *         @arg @ref LL_PWR_WAKEUP_SUBG
  *         @arg @ref LL_PWR_WAKEUP_SUBGHOST
  *         @arg @ref LL_PWR_WAKEUP_LCSC
  *         @arg @ref LL_PWR_WAKEUP_COMP
  *         @arg @ref LL_PWR_WAKEUP_LCD
  *         @arg @ref LL_PWR_WAKEUP_RTC
  *         @arg @ref LL_PWR_WAKEUP_LPUART
  * @param  Polarity Internal polarity to configure. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WUP_RISIEDG
  *         @arg @ref LL_PWR_WUP_FALLEDG
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeupInternalPolarity(uint32_t WakeUpSource, uint32_t Polarity)
{
  if (Polarity == LL_PWR_WUP_FALLEDG)
  {
    SET_BIT(PWR->IWUP, (WakeUpSource & 0x0000FFFF));
  }
  else
  {
    CLEAR_BIT(PWR->IWUP, (WakeUpSource & 0x0000FFFF));
  }
}

/**
  * @brief  Get the polarity for the Internal wakeup sources.
  * @rmtoll IWUP                 LL_PWR_GetWakeupInternalPolarity
  * @param  WakeUpSource Internal wakeup sources configured. This parameter can be a one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LPAWUR
  *         @arg @ref LL_PWR_WAKEUP_SUBG
  *         @arg @ref LL_PWR_WAKEUP_SUBGHOST
  *         @arg @ref LL_PWR_WAKEUP_LCSC
  *         @arg @ref LL_PWR_WAKEUP_COMP
  *         @arg @ref LL_PWR_WAKEUP_LCD
  *         @arg @ref LL_PWR_WAKEUP_RTC
  *         @arg @ref LL_PWR_WAKEUP_LPUART
  * @retval The Internal polarity configured. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WUP_RISIEDG
  *         @arg @ref LL_PWR_WUP_FALLEDG
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeupInternalPolarity(uint32_t WakeUpSource)
{
  return (uint32_t)((READ_BIT(PWR->IWUP, (WakeUpSource & 0x0000FFFF))) ? 1UL : 0UL);
}

/**
  * @brief  Get which Internal source woken up the device after a DEEPSTOP.
  * @rmtoll IWUF                LL_PWR_GetInternalWakeupSource
  * @retval Internal Wakeup Source from DEEPSTOP. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_FLAG_LPAWUR
  *         @arg @ref LL_PWR_FLAG_MRSUBGHCPU
  *         @arg @ref LL_PWR_FLAG_MRSUBG
  *         @arg @ref LL_PWR_FLAG_LCSC
  *         @arg @ref LL_PWR_FLAG_COMP
  *         @arg @ref LL_PWR_FLAG_LCD
  *         @arg @ref LL_PWR_FLAG_RTC
  *         @arg @ref LL_PWR_FLAG_LPUART
  */
__STATIC_INLINE uint32_t LL_PWR_GetInternalWakeupSource(void)
{
  return (uint32_t)(READ_REG(PWR->IWUF) & 0x0000FFFF);
}

/**
  * @brief  Clear the Internal source that woken up the device after a DEEPSTOP.
  * @rmtoll IWUF                 LL_PWR_ClearInternalWakeupSource
  * @param  WakeUpSource Internal Wakeup Source from DEEPSTOP.
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_FLAG_LPAWUR
  *         @arg @ref LL_PWR_FLAG_MRSUBGHCPU
  *         @arg @ref LL_PWR_FLAG_MRSUBG
  *         @arg @ref LL_PWR_FLAG_LCSC
  *         @arg @ref LL_PWR_FLAG_COMP
  *         @arg @ref LL_PWR_FLAG_LCD
  *         @arg @ref LL_PWR_FLAG_RTC
  *         @arg @ref LL_PWR_FLAG_LPUART
  */
__STATIC_INLINE void LL_PWR_ClearInternalWakeupSource(uint32_t WakeUpSource)
{
  WRITE_REG(PWR->IWUF, (WakeUpSource & 0x0000FFFF));
}

/**
  * @brief  Get LPUART Flag
  * @rmtoll IWUF          IWUF0           LL_PWR_IsActiveFlag_LPUART
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_LPUART(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_IWUF0) == (PWR_IWUF_IWUF0)) ? 1UL : 0UL);
}

/**
  * @brief  Get RTC Flag
  * @rmtoll IWUF          IWUF1           LL_PWR_IsActiveFlag_RTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_RTC(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_IWUF1) == (PWR_IWUF_IWUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Get LCD Flag
  * @rmtoll IWUF          IWUF2           LL_PWR_IsActiveFlag_LCD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_LCD(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_IWUF2) == (PWR_IWUF_IWUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Get COMP Flag
  * @rmtoll IWUF          IWUF3           LL_PWR_IsActiveFlag_COMP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_COMP(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_IWUF3) == (PWR_IWUF_IWUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get LCSC Flag
  * @rmtoll IWUF          IWUF4           LL_PWR_IsActiveFlag_LCSC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_LCSC(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_IWUF4) == (PWR_IWUF_IWUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Get MRSUBG Flag
  * @rmtoll IWUF          WMRSUBGF           LL_PWR_IsActiveFlag_MRSUBG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_MRSUBG(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_WMRSUBGF) == (PWR_IWUF_WMRSUBGF)) ? 1UL : 0UL);
}

/**
  * @brief  Get MRSUBG Host CPU Flag
  * @rmtoll IWUF          WMRSUBGHCPUF           LL_PWR_IsActiveFlag_WMRSUBGHCPU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_MRSUBGHCPU(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_WMRSUBGHCPUF) == (PWR_IWUF_WMRSUBGHCPUF)) ? 1UL : 0UL);
}

#if defined(LPAWUR)
/**
  * @brief  Get LPAWUR Flag
  * @rmtoll IWUF          WLPAWURF           LL_PWR_IsActiveFlag_LPAWUR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_LPAWUR(void)
{
  return ((READ_BIT(PWR->IWUF, PWR_IWUF_WLPAWURF) == (PWR_IWUF_WLPAWURF)) ? 1UL : 0UL);
}
#endif /* LPAWUR */

/**
  * @brief  Get IO BOOT value.
  * @rmtoll SR2               LL_PWR_GetIOBootVal
  * @param  IO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PA8_LATCH_POR
  *         @arg @ref LL_PWR_PA9_LATCH_POR
  *         @arg @ref LL_PWR_PA10_LATCH_POR
  *         @arg @ref LL_PWR_PA11_LATCH_POR
  *         @arg @ref LL_PWR_PB12_LATCH_POR
  *         @arg @ref LL_PWR_PB13_LATCH_POR
  *         @arg @ref LL_PWR_PB14_LATCH_POR
  *         @arg @ref LL_PWR_PB15_LATCH_POR
  * @retval State of pin (1 or 0).
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE uint32_t LL_PWR_GetIOBootVal(uint32_t IO)
{
  return ((READ_BIT(PWR->SR2, IO) == (IO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDD voltage is below or above the selected PVD threshold
  * @rmtoll SR2       PVDO         LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_PVDO) == (PWR_SR2_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Get the Main Regulator ready status.
  * @rmtoll SR2       REGMS         LL_PWR_IsActiveFlag_REGMS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGMS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGMS) == (PWR_SR2_REGMS)) ? 1UL : 0UL);
}

/**
  * @brief  Get the Low Power Regulator ready status.
  * @rmtoll SR2      REGLPS         LL_PWR_IsActiveFlag_REGLPS
  * @retval State of Low Power Regulator (1=ready or 0=not ready).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGLPS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGLPS) == (PWR_SR2_REGLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS ready status.
  * @rmtoll SR2    PWR_SR2_SMPSRDY      LL_PWR_IsSMPSReady
  * @retval State of SMPS (1=ready or 0=not ready).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSReady(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) == (PWR_SR2_SMPSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS RUN mode status.
  * @rmtoll SR2       PWR_SR2_SMPSENR         LL_PWR_IsSMPSinRUNMode
  * @retval SMPS RUN mode status (1=SMPS in RUN mode or 0=in PRECHARGE or NOSMPS mode).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSinRUNMode(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSENR) == (PWR_SR2_SMPSENR)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS PRECHARGE mode status.
  * @rmtoll SR2    PWR_SR2_SMPSBYPR     LL_PWR_IsSMPSinPRECHARGEMode
  * @retval SMPS PRECHARGE mode status (1=SMPS regulator is in PRECHARGE mode or 0=NOT in PRECHARGE).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSinPRECHARGEMode(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSBYPR) == (PWR_SR2_SMPSBYPR)) ? 1UL : 0UL);
}

#if defined (STM32WL3RX)
/**
  * @brief  Enable ULTRA_DEEPSTOP bit
  * @rmtoll PDCRA          UDP           LL_PWR_EnableUDP
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUDP(void)
{
  SET_BIT(PWR->PDCRA, PWR_PDCRA_UDP);
}

/**
  * @brief  Disable ULTRA_DEEPSTOP bit
  * @rmtoll PDCRA          UDP           LL_PWR_DisableUDP
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUDP(void)
{
  CLEAR_BIT(PWR->PDCRA, PWR_PDCRA_UDP);
}

/**
  * @brief  Check if ULTRA_DEEPSTOP bit is enabled
  * @rmtoll PDCRA          UDP           LL_PWR_IsEnabledUDP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUDP(void)
{
  return ((READ_BIT(PWR->PDCRA, PWR_PDCRA_UDP) == (PWR_PDCRA_UDP)) ? 1UL : 0UL);
}
#endif /* STM32WL3RX */

/**
  * @brief  Set SMPS Mode.
  * @rmtoll CR5          PWR_CR5_NOSMPS           LL_PWR_SetSMPSMode
  * @param Mode SMPS Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS
  *         @arg @ref LL_PWR_NO_SMPS
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSMode(uint32_t Mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, Mode);
}

/**
  * @brief  Get SMPS Mode.
  * @rmtoll CR5          PWR_CR5_NOSMPS           LL_PWR_GetSMPSMode
  * @retval SMPS Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS
  *         @arg @ref LL_PWR_NO_SMPS
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_NOSMPS));
}

/**
  * @brief  Set SMPS in PRECHARGE Mode.
  * @rmtoll CR5          PWR_CR5_SMPSFBYP           LL_PWR_SetSMPSPrechargeMode
  * @param Mode SMPS in Precharge Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_NO_SMPS_PRECHARGE
  *         @arg @ref LL_PWR_SMPS_PRECHARGE
  * @retval None
  */
__STATIC_INLINE void  LL_PWR_SetSMPSPrechargeMode(uint32_t Mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSFBYP, Mode);
}

/**
  * @brief   Check if SMPS is configured in PRECHARGE Mode.
  * @rmtoll CR5          PWR_CR5_SMPSFBYP      LL_PWR_IsEnabledSMPSPrechargeMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSPrechargeMode(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_SMPSFBYP) == (PWR_CR5_SMPSFBYP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable SMPS BOF (Bypass On the Fly).
  * @rmtoll CR5   PWR_CR5_NOSMPSBOF    LL_PWR_EnableSMPSBOF
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSMPSBOF(void)
{
  SET_BIT(PWR->CR5, PWR_CR5_NOSMPS_BOF);
}

/**
  * @brief  Disable SMPS BOF (Bypass On the Fly).
  * @rmtoll CR5   PWR_CR5_NOSMPSBOF    LL_PWR_DisableSMPSBOF
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSMPSBOF(void)
{
  CLEAR_BIT(PWR->CR5, PWR_CR5_NOSMPS_BOF);
}

/**
  * @brief  Check if SMPS BOF (Bypass On the Fly) is enabled or not.
  * @rmtoll CR5   PWR_CR5_NOSMPSBOF    LL_PWR_IsEnabledSMPSBOF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSBOF(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_NOSMPS_BOF) == (PWR_CR5_NOSMPS_BOF)) ? 1UL : 0UL);
}

/**
  * @brief  Enable SMPS BOF Static.
  * @rmtoll CR5   PWR_CR5_SMPS_BOF_STATIC    LL_PWR_EnableSMPSBOFStatic
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSMPSBOFStatic(void)
{
  SET_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_STATIC);
}

/**
  * @brief  Disable SMPS BOF Static.
  * @rmtoll CR5   PWR_CR5_SMPS_BOF_STATIC   LL_PWR_DisableSMPSBOFStatic
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSMPSBOFStatic(void)
{
  CLEAR_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_STATIC);
}

/**
  * @brief  Check if SMPS BOF Static is enabled or not.
  * @rmtoll CR5   PWR_CR5_SMPS_BOF_STATIC    LL_PWR_IsEnabledSMPSBOFStatic
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSBOFStatic(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_STATIC) == (PWR_CR5_SMPS_BOF_STATIC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable SMPS BOF Dynamic.
  * @rmtoll CR5   PWR_CR5_SMPS_BOF_DYN    LL_PWR_EnableSMPSBOFDynamic
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSMPSBOFDynamic(void)
{
  SET_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_DYN);
}

/**
  * @brief  Disable SMPS BOF Dynamic.
  * @rmtoll CR5   PWR_CR5_SMPS_BOF_DYN   LL_PWR_DisableSMPSBOFDynamic
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSMPSBOFDynamic(void)
{
  CLEAR_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_DYN);
}

/**
  * @brief  Check if SMPS BOF Dynamic is enabled or not.
  * @rmtoll CR5   PWR_CR5_SMPS_BOF_DYN    LL_PWR_IsEnabledSMPSBOFDynamic
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSBOFDynamic(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_DYN) == (PWR_CR5_SMPS_BOF_DYN)) ? 1UL : 0UL);
}

/**
  * @brief  Set SMPS OPEN Mode during DEEPSTOP.
  * @rmtoll CR5          PWR_CR5_NOSMPS           LL_PWR_SetSMPSOpenMode
  * @param  Mode SMPS Mode. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_NO_SMPS_LPOPEN
  *         @arg @ref LL_PWR_SMPS_LPOPEN
  */
__STATIC_INLINE void LL_PWR_SetSMPSOpenMode(uint32_t Mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLPOPEN, Mode);
}

/**
  * @brief  Set SMPS BOM
  * @rmtoll CR5   PWR_CR5_SMPSBOMSEL_0/PWR_CR5_SMPSBOMSEL_1    LL_PWR_SetSMPSBOM
  * @param  BOM BOM. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BOM1
  *         @arg @ref LL_PWR_SMPS_BOM2
  *         @arg @ref LL_PWR_SMPS_BOM3
  */
__STATIC_INLINE void LL_PWR_SetSMPSBOM(uint32_t BOM)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSBOMSEL, BOM);
}

/**
  * @brief  Get SMPS BOM
  * @rmtoll CR5   PWR_CR5_SMPSBOMSEL_0/PWR_CR5_SMPSBOMSEL_1    LL_PWR_GetSMPSBOM
  * @retval BOM. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BOM1
  *         @arg @ref LL_PWR_SMPS_BOM2
  *         @arg @ref LL_PWR_SMPS_BOM3
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSBOM(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_SMPSBOMSEL));
}

/**
  * @brief  Set SMPS Output Level
  * @rmtoll CR5       SMPSLVL    LL_PWR_SMPS_SetOutputVoltageLevel
  * @param  OutputVoltageLevel Output Level. This parameter can be one of the values
  *         of the @arg @ref PWR_LL_SMPS_OUTLVL.
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V20
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V30
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V40
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V50
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V60
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V70
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V80
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V90
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_2V00
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_2V10
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_2V20
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_2V30
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_2V40
  * @retval None
  * @note   Please refer the user manual to know which levels are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_SMPS_SetOutputVoltageLevel(uint32_t OutputVoltageLevel)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLVL, OutputVoltageLevel);
}

/**
  * @brief  Get SMPS Output Level
  * @rmtoll CR5   PWR_CR5_SMPSLVL    LL_PWR_SMPS_GetOutputVoltageLevel
  * @retval Output Level. This parameter can be one of the values
  *         of the @arg @ref PWR_LL_SMPS_OUTLVL.
  * @note   Please refer the user manual to know which levels are able for this
  *         feature.
  */
__STATIC_INLINE uint32_t LL_PWR_SMPS_GetOutputVoltageLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_SMPSLVL));
}

/**
  * @brief  Enable pull-up and pull-down configuration
  * @rmtoll CR1          APC           LL_PWR_EnablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePUPDCfg(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration
  * @rmtoll CR1          APC           LL_PWR_DisablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePUPDCfg(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief  Check if pull-up and pull-down configuration is enabled
  * @rmtoll CR1          APC           LL_PWR_IsEnabledPUPDCfg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDCfg(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_APC) == (PWR_CR1_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-up state in Shutdown mode
  * @rmtoll PUCRA        PUA0-15        LL_PWR_EnableGPIOPullUp\n
  *         PUCRB        PUB0-15        LL_PWR_EnableGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber Pins Pull-up enable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)(GPIO + 4UL)), GPIONumber);
  SET_BIT(*((__IO uint32_t *)GPIO), GPIONumber);
}

/**
  * @brief  Disable GPIO pull-up state in Shutdown mode
  * @rmtoll PUCRA        PUA0-15        LL_PWR_DisableGPIOPullUp\n
  *         PUCRB        PUB0-15        LL_PWR_DisableGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber Pins Pull-up disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)GPIO), GPIONumber);
}

/**
  * @brief  Check if GPIO pull-up state is enabled
  * @rmtoll PUCRA         PUA0-15       LL_PWR_IsEnabledGPIOPullUp\n
  *         PUCRB         PUB0-15       LL_PWR_IsEnabledGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber Pins Pull-up disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval State of bit (1 or 0).
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  return ((READ_BIT(*((__IO uint32_t *)GPIO), GPIONumber) == (GPIONumber)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-down state in Shutdown mode
  * @rmtoll PDCRA         PDA0-15       LL_PWR_EnableGPIOPullDown\n
  *         PDCRB         PUB0-15       LL_PWR_EnableGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber Pins Pull-down enable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)GPIO), GPIONumber);
  SET_BIT(*((__IO uint32_t *)(GPIO + 4UL)), GPIONumber);
}

/**
  * @brief  Disable GPIO pull-down state in Shutdown mode.
  * @rmtoll PDCRA        PDA0-15        LL_PWR_DisableGPIOPullDown\n
  *         PDCRB        PDB0-15        LL_PWR_DisableGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)(GPIO + 4UL)), GPIONumber);
}

/**
  * @brief  Checks if GPIO pull-down state is enabled
  * @rmtoll PDCRA        PDA0-15        LL_PWR_IsEnabledGPIOPullDown\n
  *         PDCRB        PDB0-15        LL_PWR_IsEnabledGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval State of bit (1 or 0).
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  return ((READ_BIT(*((__IO uint32_t *)(GPIO + 4UL)), GPIONumber) == (GPIONumber)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the IO in NO PULL configuration for port A.
  * @rmtoll PDCRA/PUCRA               LL_PWR_SetNoPullA
  * @param  IO Pins No Pull configuration. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_SetNoPullA(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRA, IO);
  CLEAR_BIT(PWR->PDCRA, IO);
}

/**
  * @brief  Configure the IO in NO PULL configuration for port B.
  * @rmtoll PDCRB/PUCRB               LL_PWR_SetNoPullB
  * @param  IO Pins Pull-down disable. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  * @note   Please refer the user manual to know which IOs are able for this
  *         feature.
  */
__STATIC_INLINE void LL_PWR_SetNoPullB(uint32_t IO)
{
  CLEAR_BIT(PWR->PUCRB, IO);
  CLEAR_BIT(PWR->PDCRB, IO);
}

/**
  * @brief  Set SMPS trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetSMPSTrim
  * @param  Trim SMPS output voltage trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSTrim(uint32_t Trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_SMPS_TRIM, ((Trim << PWR_ENGTRIM_SMPS_TRIM_Pos) & PWR_ENGTRIM_SMPS_TRIM));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_SMPSTRIMEN);
}

/**
  * @brief  Get SMPS trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetSMPSTrim
  * @retval SMPS output voltage trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_SMPSTRIMEN))
  {
    return (uint32_t)(READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_SMPS_TRIM) >> PWR_ENGTRIM_SMPS_TRIM_Pos);
  }
  else
  {
    return (uint32_t)(READ_BIT(PWR->TRIMR, PWR_TRIMR_SMPS_TRIM) >> PWR_TRIMR_SMPS_TRIM_Pos);
  }
}

/**
  * @brief  Set Main regulator voltage trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetMRTrim
  * @param  Trim Main Regulator voltage trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetMRTrim(uint32_t Trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_MR, ((Trim << PWR_ENGTRIM_TRIM_MR_Pos) & PWR_ENGTRIM_TRIM_MR));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMMREN);
}

/**
  * @brief  Get Main regulator voltage trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetMRTrim
  * @retval Main regulator voltage trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetMRTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMMREN))
  {
    return (uint32_t)(READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_MR) >> PWR_ENGTRIM_TRIM_MR_Pos);
  }
  else
  {
    return (uint32_t)(READ_BIT(PWR->TRIMR, PWR_TRIMR_TRIM_MR) >> PWR_TRIMR_TRIM_MR_Pos);
  }
}

#if defined(PWR_ENGTRIM_TRIM_LSI_LPMU)
/**
  * @brief  Set Low Speed Internal oscillator LPMU trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetLPMULSITrim
  * @param  Trim Low Speed Internal oscillator trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetLSILPMUTrim(uint32_t Trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_LSI_LPMU, ((Trim << PWR_ENGTRIM_TRIM_LSI_LPMU_Pos) & PWR_ENGTRIM_TRIM_LSI_LPMU));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMLSILPMUEN);
}

/**
  * @brief  Get Low Speed Internal oscillator LPMU trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetLSITrim
  * @retval Low Speed Internal oscillator trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetLSILPMUTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMLSILPMUEN))
  {
    return (uint32_t)(READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_LSI_LPMU) >> PWR_ENGTRIM_TRIM_LSI_LPMU_Pos);
  }
  else
  {
    return (uint32_t)(READ_BIT(PWR->TRIMR, PWR_TRIMR_TRIM_LSI_LPMU) >> PWR_TRIMR_TRIM_LSI_LPMU_Pos);
  }
}
#endif /* PWR_ENGTRIM_TRIM_LSI_LPMU */

#if defined(PWR_ENGTRIM_TRIM_RFDREG)
/**
  * @brief  Set RF LDO trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetRFDREGTrim
  * @param  Trim RF LDO trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRFDREGTrim(uint32_t Trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_RFDREG, ((Trim << PWR_ENGTRIM_TRIM_RFDREG_Pos) & PWR_ENGTRIM_TRIM_RFDREG));
  SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMRFDREGEN);
}

/**
  * @brief  Get RF LDO trimming value.
  * @rmtoll TRIMR/ENGTRIM               LL_PWR_GetRFDREGTrim
  * @retval RF LDO trimming value
  */
__STATIC_INLINE uint32_t LL_PWR_GetRFDREGTrim(void)
{
  if (READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMRFDREGEN))
  {
    return (uint32_t)(READ_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_RFDREG) >> PWR_ENGTRIM_TRIM_RFDREG_Pos);
  }
  else
  {
    return (uint32_t)(READ_BIT(PWR->TRIMR, PWR_TRIMR_RFD_REG_TRIM) >> PWR_TRIMR_RFD_REG_TRIM_Pos);
  }
}
#endif /* PWR_ENGTRIM_TRIM_RFDREG */

#if defined(PWR_CR5_SMPS_PRECH_CUR_SEL)
/**
  * @brief  Select SMPS PRECHARGE limit current.
  * @rmtoll CR5               LL_PWR_SetSMPSPrechargeLimitCurrent
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_2_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_10
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_20
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSPrechargeLimitCurrent(uint32_t Mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPS_PRECH_CUR_SEL, Mode);
}

/**
  * @brief  Get SMPS PRECHARGE limit current selected.
  * @rmtoll CR5               LL_PWR_GetSMPSPrechargeLimitCurrent
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_2_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_10
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_20
  */
__STATIC_INLINE uint32_t LL_PWR_GetSMPSPrechargeLimitCurrent(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_SMPS_PRECH_CUR_SEL));
}
#endif /* PWR_CR5_SMPS_PRECH_CUR_SEL */

#if defined(PWR_CR5_CLKDETR_DISABLE)
/**
  * @brief  Enable automatic SMPS bypass switching in case of unexpected loss of the SMPS clock.
  * @rmtoll CR5          PWR_CR5_CLKDETR_DISABLE           LL_PWR_EnableSMPSCLkDet
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSMPSCLkDet(void)
{
  CLEAR_BIT(PWR->CR5, PWR_CR5_CLKDETR_DISABLE);
}

/**
  * @brief  Disable automatic SMPS bypass switching in case of unexpected loss of the SMPS clock.
  * @rmtoll CR5          PWR_CR5_CLKDETR_DISABLE           LL_PWR_DisableSMPSCLkDet
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSMPSCLkDet(void)
{
  SET_BIT(PWR->CR5, PWR_CR5_CLKDETR_DISABLE);
}

/**
  * @brief  Checks if automatic IBIAS control during RUN or DEEPSTOP mode is enabled or disabled.
  * @rmtoll CR5         PWR_CR5_CLKDETR_DISABLE      LL_PWR_IsEnabledSMPSCLkDet
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSCLkDet(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_CLKDETR_DISABLE) == (PWR_CR5_CLKDETR_DISABLE)) ? 0UL : 1UL);
}
#endif /* PWR_CR5_CLKDETR_DISABLE */

#if defined(PWR_CR5_SMPS_ENA_DCM)
/**
  * @brief  Enable Discontinuous conduction mode.
  * @rmtoll CR5          PWR_CR5_SMPS_ENA_DCM           LL_PWR_EnableSMPSDCM
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSMPSDCM(void)
{
  SET_BIT(PWR->CR5, PWR_CR5_SMPS_ENA_DCM);
}

/**
  * @brief  Disable Discontinuous conduction mode.
  * @rmtoll CR5          PWR_CR5_SMPS_ENA_DCM           LL_PWR_DisableSMPSDCM
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSMPSDCM(void)
{
  CLEAR_BIT(PWR->CR5, PWR_CR5_SMPS_ENA_DCM);
}

/**
  * @brief  Checks if Discontinuous conduction mode is enabled or disabled.
  * @rmtoll CR5         PWR_CR5_SMPS_ENA_DCM      LL_PWR_IsEnabledSMPSDCM
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSDCM(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_SMPS_ENA_DCM) == (PWR_CR5_SMPS_ENA_DCM)) ? 1UL : 0UL);
}
#endif /* PWR_CR5_SMPS_ENA_DCM */

/**
  * @}
  */

/** @defgroup PWR_LL_DBG_DEEPSTOP Function to setup the DEEPSTOP2 will be applied instead
  *                               of DEEPSTOP and the debugger features not lost
  * @{
  */

/**
  * @brief  Enable the DEEPSTOP2 feature, debugger feature not lost during DEEPSTOP.
  * @rmtoll DBGR               LL_PWR_EnableDEEPSTOP2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableDEEPSTOP2(void)
{
  SET_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2);
}

/**
  * @brief  Disable the DEEPSTOP2 feature, debugger feature lost during DEEPSTOP.
  * @rmtoll DBGR               LL_PWR_DisableDEEPSTOP2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDEEPSTOP2(void)
{
  CLEAR_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2);
}

/**
  * @brief  Checks if the DEEPSTOP2 feature is enabled or disabled
  * @rmtoll DBGR               LL_PWR_IsEnabledDEEPSTOP2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDEEPSTOP2(void)
{
  return ((READ_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2) == (PWR_DBGR_DEEPSTOP2)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup PWR_LL_DEEPSTOP_GPIORET Functions to setup the GPIORET bit.
  *                                   GPIO retention
  * @{
  */

/**
  * @brief  Enable the GPIORET feature, GPIO retain their status during DEEPSTOP
  *         and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      LL_PWR_EnableGPIORET
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableGPIORET(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_GPIORET);
}

/**
  * @brief  Disable the GPIORET feature, don't retain their status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      LL_PWR_DisableGPIORET
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableGPIORET(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_GPIORET);
}

/**
  * @brief  Checks if the GPIO retention in DEEPSTOP feature is enabled or disabled
  * @rmtoll CR2         GPIORET      LL_PWR_IsEnabledGPIORET
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIORET(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_GPIORET) == (PWR_CR2_GPIORET)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup PWR_LL_DEEPSTOP_DBGRET Functions to setup the DBGRET bit.
  *           GPIOA_Pin_2 and GPIOA_Pin_3 retention exiting from DEEPSTOP
  * @{
  */

/**
  * @brief  Enable the DBGRET feature, GPIOA_Pin_2 and GPIOA_Pin_3 retain their
  *         status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      LL_PWR_EnableDBGRET
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableDBGRET(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_DBGRET);
}

/**
  * @brief  Disable the DBGRET feature, GPIOA_Pin_2 and GPIOA_Pin_3 don't retain
  *         status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      LL_PWR_DisableDBGRET
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDBGRET(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_DBGRET);
}

/**
  * @brief  Checks if the GPIOA_Pin_2 and GPIOA_Pin_3 retention in DEEPSTOP
  *         feature is enabled or disabled
  * @rmtoll CR2         DBGRET      LL_PWR_IsEnabledDBGRET
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDBGRET(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_DBGRET) == (PWR_CR2_DBGRET)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR FLAG Management
  * @{
  */

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 0.
  * @rmtoll WUFA          WUF0            LL_PWR_IsActiveFlag_WUA0
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA0(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF0) == (PWR_WUFA_WUF0)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 1.
  * @rmtoll WUFA          WUF1            LL_PWR_IsActiveFlag_WUA1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA1(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF1) == (PWR_WUFA_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 2.
  * @rmtoll WUFA          WUF2            LL_PWR_IsActiveFlag_WUA2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA2(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF2) == (PWR_WUFA_WUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 3.
  * @rmtoll WUFA          WUF3            LL_PWR_IsActiveFlag_WUA3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA3(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF3) == (PWR_WUFA_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 4.
  * @rmtoll WUFA          WUF4            LL_PWR_IsActiveFlag_WUA4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA4(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF4) == (PWR_WUFA_WUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 5.
  * @rmtoll WUFA          WUF5            LL_PWR_IsActiveFlag_WUA5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA5(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF5) == (PWR_WUFA_WUF5)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 6.
  * @rmtoll WUFA          WUF6            LL_PWR_IsActiveFlag_WUA6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA6(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF6) == (PWR_WUFA_WUF6)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 7.
  * @rmtoll WUFA          WUF7            LL_PWR_IsActiveFlag_WUA7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA7(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF7) == (PWR_WUFA_WUF7)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 8.
  * @rmtoll WUFA          WUF8            LL_PWR_IsActiveFlag_WUA8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA8(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF8) == (PWR_WUFA_WUF8)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 9.
  * @rmtoll WUFA          WUF9            LL_PWR_IsActiveFlag_WUA9
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA9(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF9) == (PWR_WUFA_WUF9)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 10.
  * @rmtoll WUFA          WUF10            LL_PWR_IsActiveFlag_WUA10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA10(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF10) == (PWR_WUFA_WUF10)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 11.
  * @rmtoll WUFA          WUF11            LL_PWR_IsActiveFlag_WUA11
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA11(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF11) == (PWR_WUFA_WUF11)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 12.
  * @rmtoll WUFA          WUF12            LL_PWR_IsActiveFlag_WUA12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA12(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF12) == (PWR_WUFA_WUF12)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 13.
  * @rmtoll WUFA          WUF13            LL_PWR_IsActiveFlag_WUA13
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA13(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF13) == (PWR_WUFA_WUF13)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 14.
  * @rmtoll WUFA          WUF14            LL_PWR_IsActiveFlag_WUA14
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA14(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF14) == (PWR_WUFA_WUF14)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 15.
  * @rmtoll WUFA          WUF15            LL_PWR_IsActiveFlag_WUA15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUA15(void)
{
  return ((READ_BIT(PWR->WUFA, PWR_WUFA_WUF15) == (PWR_WUFA_WUF15)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Wake-up Flag WUFA0
  * @rmtoll WUFA     WUF0          LL_PWR_ClearFlag_WUA0
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA0(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF0);
}

/**
  * @brief  Clear Wake-up Flag WUFA1
  * @rmtoll WUFA     WUF1          LL_PWR_ClearFlag_WUA1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA1(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF1);
}
/**
  * @brief  Clear Wake-up Flag WUFA2
  * @rmtoll WUFA     WUF2          LL_PWR_ClearFlag_WUA2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA2(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF2);
}
/**
  * @brief  Clear Wake-up Flag WUFA3
  * @rmtoll WUFA     WUF3          LL_PWR_ClearFlag_WUA3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA3(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF3);
}
/**
  * @brief  Clear Wake-up Flag WUFA4
  * @rmtoll WUFA     WUF4          LL_PWR_ClearFlag_WUA4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA4(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF4);
}

/**
  * @brief  Clear Wake-up Flag WUFA5
  * @rmtoll WUFA     WUF5          LL_PWR_ClearFlag_WUA5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA5(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF5);
}

/**
  * @brief  Clear Wake-up Flag WUFA6
  * @rmtoll WUFA     WUF6          LL_PWR_ClearFlag_WUA6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA6(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF6);
}

/**
  * @brief  Clear Wake-up Flag WUFA7
  * @rmtoll WUFA     WUF7          LL_PWR_ClearFlag_WUA7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA7(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF7);
}

/**
  * @brief  Clear Wake-up Flag WUFA8
  * @rmtoll WUFA     WUF8          LL_PWR_ClearFlag_WUA8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA8(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF8);
}

/**
  * @brief  Clear Wake-up Flag WUFA9
  * @rmtoll WUFA     WUF9          LL_PWR_ClearFlag_WUA9
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA9(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF9);
}

/**
  * @brief  Clear Wake-up Flag WUFA10
  * @rmtoll WUFA     WUF10          LL_PWR_ClearFlag_WUA10
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA10(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF10);
}

/**
  * @brief  Clear Wake-up Flag WUFA11
  * @rmtoll WUFA     WUF11          LL_PWR_ClearFlag_WUA11
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA11(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF11);
}

/**
  * @brief  Clear Wake-up Flag WUFA12
  * @rmtoll WUFA     WUF12          LL_PWR_ClearFlag_WUA12
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA12(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF12);
}

/**
  * @brief  Clear Wake-up Flag WUFA13
  * @rmtoll WUFA     WUF13          LL_PWR_ClearFlag_WUA13
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA13(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF13);
}

/**
  * @brief  Clear Wake-up Flag WUFA14
  * @rmtoll WUFA     WUF14          LL_PWR_ClearFlag_WUA14
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA14(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF14);
}

/**
  * @brief  Clear Wake-up Flag WUFA15
  * @rmtoll WUFA     WUF15          LL_PWR_ClearFlag_WUA15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUA15(void)
{
  WRITE_REG(PWR->WUFA, PWR_WUFA_WUF15);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 0.
  * @rmtoll WUFB          WUF0            LL_PWR_IsActiveFlag_WUB0
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB0(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF0) == (PWR_WUFB_WUF0)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 1.
  * @rmtoll WUFB          WUF1            LL_PWR_IsActiveFlag_WUB1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB1(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF1) == (PWR_WUFB_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 2.
  * @rmtoll WUFB          WUF2            LL_PWR_IsActiveFlag_WUB2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB2(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF2) == (PWR_WUFB_WUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 3.
  * @rmtoll WUFB          WUF3            LL_PWR_IsActiveFlag_WUB3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB3(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF3) == (PWR_WUFB_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 4.
  * @rmtoll WUFB          WUF4            LL_PWR_IsActiveFlag_WUB4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB4(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF4) == (PWR_WUFB_WUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 5.
  * @rmtoll WUFB          WUF5            LL_PWR_IsActiveFlag_WUB5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB5(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF5) == (PWR_WUFB_WUF5)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 6.
  * @rmtoll WUFB          WUF6            LL_PWR_IsActiveFlag_WUB6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB6(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF6) == (PWR_WUFB_WUF6)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 7.
  * @rmtoll WUFB          WUF7            LL_PWR_IsActiveFlag_WUB7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB7(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF7) == (PWR_WUFB_WUF7)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 8.
  * @rmtoll WUFB          WUF8            LL_PWR_IsActiveFlag_WUB8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB8(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF8) == (PWR_WUFB_WUF8)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 9.
  * @rmtoll WUFB          WUF9            LL_PWR_IsActiveFlag_WUB9
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB9(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF9) == (PWR_WUFB_WUF9)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 10.
  * @rmtoll WUFB          WUF10            LL_PWR_IsActiveFlag_WUB10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB10(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF10) == (PWR_WUFB_WUF10)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 11.
  * @rmtoll WUFB          WUF11            LL_PWR_IsActiveFlag_WUB11
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB11(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF11) == (PWR_WUFB_WUF11)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 12.
  * @rmtoll WUFB          WUF12            LL_PWR_IsActiveFlag_WUB12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB12(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF12) == (PWR_WUFB_WUF12)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 13.
  * @rmtoll WUFB          WUF13            LL_PWR_IsActiveFlag_WUB13
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB13(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF13) == (PWR_WUFB_WUF13)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 14.
  * @rmtoll WUFB          WUF14            LL_PWR_IsActiveFlag_WUB14
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB14(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF14) == (PWR_WUFB_WUF14)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 15.
  * @rmtoll WUFB          WUF15            LL_PWR_IsActiveFlag_WUB15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WUB15(void)
{
  return ((READ_BIT(PWR->WUFB, PWR_WUFB_WUF15) == (PWR_WUFB_WUF15)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Wake-up Flag WUFB0
  * @rmtoll WUFB     WUF0          LL_PWR_ClearFlag_WUB0
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB0(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF0);
}

/**
  * @brief  Clear Wake-up Flag WUFB1
  * @rmtoll WUFB     WUF1          LL_PWR_ClearFlag_WUB1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB1(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF1);
}
/**
  * @brief  Clear Wake-up Flag WUFB2
  * @rmtoll WUFB     WUF2          LL_PWR_ClearFlag_WUB2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB2(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF2);
}
/**
  * @brief  Clear Wake-up Flag WUFB3
  * @rmtoll WUFB     WUF3          LL_PWR_ClearFlag_WUB3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB3(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF3);
}
/**
  * @brief  Clear Wake-up Flag WUFB4
  * @rmtoll WUFB     WUF4          LL_PWR_ClearFlag_WUB4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB4(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF4);
}

/**
  * @brief  Clear Wake-up Flag WUFB5
  * @rmtoll WUFB     WUF5          LL_PWR_ClearFlag_WUB5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB5(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF5);
}

/**
  * @brief  Clear Wake-up Flag WUFB6
  * @rmtoll WUFB     WUF6          LL_PWR_ClearFlag_WUB6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB6(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF6);
}

/**
  * @brief  Clear Wake-up Flag WUFB7
  * @rmtoll WUFB     WUF7          LL_PWR_ClearFlag_WUB7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB7(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF7);
}

/**
  * @brief  Clear Wake-up Flag WUFB8
  * @rmtoll WUFB     WUF8          LL_PWR_ClearFlag_WUB8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB8(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF8);
}

/**
  * @brief  Clear Wake-up Flag WUFB9
  * @rmtoll WUFB     WUF9          LL_PWR_ClearFlag_WUB9
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB9(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF9);
}

/**
  * @brief  Clear Wake-up Flag WUFB10
  * @rmtoll WUFB     WUF10          LL_PWR_ClearFlag_WUB10
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB10(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF10);
}

/**
  * @brief  Clear Wake-up Flag WUFB11
  * @rmtoll WUFB     WUF11          LL_PWR_ClearFlag_WUB11
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB11(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF11);
}

/**
  * @brief  Clear Wake-up Flag WUFB12
  * @rmtoll WUFB     WUF12          LL_PWR_ClearFlag_WUB12
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB12(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF12);
}

/**
  * @brief  Clear Wake-up Flag WUFB13
  * @rmtoll WUFB     WUF13          LL_PWR_ClearFlag_WUB13
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB13(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF13);
}

/**
  * @brief  Clear Wake-up Flag WUFB14
  * @rmtoll WUFB     WUF14          LL_PWR_ClearFlag_WUB14
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB14(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF14);
}

/**
  * @brief  Clear Wake-up Flag WUFB15
  * @rmtoll WUFB     WUF15          LL_PWR_ClearFlag_WUB15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WUB15(void)
{
  WRITE_REG(PWR->WUFB, PWR_WUFB_WUF15);
}

/**
  * @brief  Clear internal Wake-up Flag LPUART
  * @rmtoll IWUF     IWUF0          LL_PWR_ClearFlag_LPUART
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_LPUART(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_IWUF0);
}

/**
  * @brief  Clear internal Wake-up Flag RTC
  * @rmtoll IWUF     IWUF1          LL_PWR_ClearFlag_RTC
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_RTC(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_IWUF1);
}

/**
  * @brief  Clear internal Wake-up Flag LCD
  * @rmtoll IWUF     IWUF2          LL_PWR_ClearFlag_LCD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_LCD(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_IWUF2);
}

/**
  * @brief  Clear internal Wake-up Flag COMP
  * @rmtoll IWUF     IWUF3          LL_PWR_ClearFlag_LCD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_COMP(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_IWUF3);
}

/**
  * @brief  Clear internal Wake-up Flag LCSC
  * @rmtoll IWUF     IWUF4          LL_PWR_ClearFlag_LCSC
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_LCSC(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_IWUF4);
}

/**
  * @brief  Clear internal Wake-up Flag MRSUBG
  * @rmtoll IWUF     WMRSUBGF          LL_PWR_ClearFlag_MRSUBG
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_MRSUBG(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_WMRSUBGF);
}

/**
  * @brief  Clear MRSUBG Host CPU wakeup flag
  * @rmtoll IWUF     WMRSUBGHCPUF          LL_PWR_ClearFlag_MRSUBGHCPU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_MRSUBGHCPU(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_WMRSUBGHCPUF);
}

#if defined (LPAWUR)
/**
  * @brief  Clear LPAWUR wakeup flag
  * @rmtoll IWUF     WLPAWURF          LL_PWR_ClearFlag_LPAWUR
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_LPAWUR(void)
{
  WRITE_REG(PWR->IWUF, PWR_IWUF_WLPAWURF);
}

#endif /* LPAWUR */
/**
  * @}
  */

/** @defgroup PWR_LL_RF_DEEPSTOP_FLAG flags about RF radio activity start and DEEPSTOP sequence occurred.
  * @{
  */

/**
  * @brief  Check if a radio wakeup event occurs.
  * @rmtoll EXTSRR         RFPHASEF      LL_PWR_GetRFWakeupFlag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_GetRFWakeupFlag(void)
{
  return ((READ_BIT(PWR->EXTSRR, PWR_EXTSRR_RFPHASEF) == (PWR_EXTSRR_RFPHASEF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear radio wakeup event occurs flag.
  * @rmtoll EXTSRR         RFPHASEF      LL_PWR_ClearRFWakeupFlag
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearRFWakeupFlag(void)
{
  WRITE_REG(PWR->EXTSRR, PWR_EXTSRR_RFPHASEF);
}

/**
  * @brief  Check if a DEEPSTOP sequence occurred.
  * @rmtoll EXTSRR         DEEPSTOPF      LL_PWR_GetDeepstopSeqFlag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_GetDeepstopSeqFlag(void)
{
  return ((READ_BIT(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF) == (PWR_EXTSRR_DEEPSTOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear DEEPSTOP sequence occurred flag.
  * @rmtoll EXTSRR         DEEPSTOPF      LL_PWR_ClearDeepstopSeqFlag
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearDeepstopSeqFlag(void)
{
  WRITE_REG(PWR->EXTSRR, PWR_EXTSRR_DEEPSTOPF);
}
/**
  * @}
  */

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WL3x_LL_PWR_H */
