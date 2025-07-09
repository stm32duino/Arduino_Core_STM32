/**
  ******************************************************************************
  * @file    stm32wb0x_ll_pwr.h
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
#ifndef STM32WB0x_LL_PWR_H
#define STM32WB0x_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
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

/** @defgroup PWR_LL_EC_MODE_PWR PWR Mode
  * @{
  */
#define LL_PWR_MODE_DEEPSTOP         (0x000000000U)
#define LL_PWR_MODE_SHUTDOWN         (PWR_CR1_LPMS)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RAMRET RAM Retention enable
  * @{
  */
#define LL_PWR_RAMRET_1              PWR_CR2_RAMRET1
#if defined(PWR_CR2_RAMRET2)
#define LL_PWR_RAMRET_2              PWR_CR2_RAMRET2
#endif /* PWR_CR2_RAMRET2 */
#if defined(PWR_CR2_RAMRET3)
#define LL_PWR_RAMRET_3              PWR_CR2_RAMRET3
#endif /* PWR_CR2_RAMRET3 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL PVD Level
  * @{
  */
#define LL_PWR_PVDLEVEL_0            (0x00000000U)                             /*!< VPVD0 around 2.0 V */
#define LL_PWR_PVDLEVEL_1            (PWR_CR2_PVDLS_0)                         /*!< VPVD1 around 2.2 V */
#define LL_PWR_PVDLEVEL_2            (PWR_CR2_PVDLS_1)                         /*!< VPVD2 around 2.4 V */
#define LL_PWR_PVDLEVEL_3            (PWR_CR2_PVDLS_1 | PWR_CR2_PVDLS_0)       /*!< VPVD3 around 2.5 V */
#define LL_PWR_PVDLEVEL_4            (PWR_CR2_PVDLS_2)                         /*!< VPVD4 around 2.6 V */
#define LL_PWR_PVDLEVEL_5            (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_0)       /*!< VPVD5 around 2.8 V */
#define LL_PWR_PVDLEVEL_6            (PWR_CR2_PVDLS_2 | PWR_CR2_PVDLS_1)       /*!< VPVD6 around 2.9 V */
#define LL_PWR_PVDLEVEL_7            (PWR_CR2_PVDLS)                           /*!< External input analog voltage   (Compare internally to VBGP) */


/**
  * @}
  */

/** @defgroup PWR_LL_EW_SOURCE_PORT IO Port for wakeup source
  * @{
  */
#define LL_PWR_EWS_PORTA             (0x00000000U)             /*!< IO port A to get out from DEEPSTOP mode */
#define LL_PWR_EWS_PORTB             (0x00000001U)             /*!< IO port B to get out from DEEPSTOP mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EW_WAKEUP_SOURCE Wakeup Source
  * @{
  */
#if !defined(PWR_CR6_EWU20)
#define LL_PWR_WAKEUP_CR6_ALL        (0x000000FFU << 16)         /*!< Enable all the wakeup source in CR6            */
#define LL_PWR_WAKEUP_CR3_ALL        (0x0000FFFFU)              /*!< Enable all the wakeup source in CR3            */
#define LL_PWR_WAKEUP_ALL            LL_PWR_WAKEUP_CR6_ALL | LL_PWR_WAKEUP_CR3_ALL
#define LL_PWR_WAKEUP_RTC            PWR_CR3_EIWL              /*!< Enable wakeup on Internal event (RTC)          */
#define LL_PWR_WAKEUP_LPUART         PWR_CR3_EIWL2             /*!< Enable wakeup on Internal event 2 (LPUART)     */
#define LL_PWR_WAKEUP_BLEHOST        PWR_CR3_EWBLEHCPU         /*!< Enable wakeup on BLE Host CPU event            */
#define LL_PWR_WAKEUP_BLE            PWR_CR3_EWBLE             /*!< Enable wakeup on BLE event                     */
#define LL_PWR_WAKEUP_PA11           PWR_CR3_EWU11             /*!< Enable wakeup on PA11 I/O event                */
#define LL_PWR_WAKEUP_PA10           PWR_CR3_EWU10             /*!< Enable wakeup on PA10 I/O event                */
#define LL_PWR_WAKEUP_PA9            PWR_CR3_EWU9              /*!< Enable wakeup on PA9 I/O event                 */
#define LL_PWR_WAKEUP_PA8            PWR_CR3_EWU8              /*!< Enable wakeup on PA8 I/O event                 */
#define LL_PWR_WAKEUP_PA3            (PWR_CR6_EWU15 << 16)     /*!< Enable wakeup on PA3 I/O event                 */
#define LL_PWR_WAKEUP_PA2            (PWR_CR6_EWU14 << 16)     /*!< Enable wakeup on PA2 I/O event                 */
#define LL_PWR_WAKEUP_PA1            (PWR_CR6_EWU13 << 16)     /*!< Enable wakeup on PA1 I/O event                 */
#define LL_PWR_WAKEUP_PA0            (PWR_CR6_EWU12 << 16)     /*!< Enable wakeup on PA0 I/O event                 */
#define LL_PWR_WAKEUP_PB7            PWR_CR3_EWU7              /*!< Enable wakeup on PB7 I/O event                 */
#define LL_PWR_WAKEUP_PB6            PWR_CR3_EWU6              /*!< Enable wakeup on PB6 I/O event                 */
#define LL_PWR_WAKEUP_PB5            PWR_CR3_EWU5              /*!< Enable wakeup on PB5 I/O event                 */
#define LL_PWR_WAKEUP_PB4            PWR_CR3_EWU4              /*!< Enable wakeup on PB4 I/O event                 */
#define LL_PWR_WAKEUP_PB3            PWR_CR3_EWU3              /*!< Enable wakeup on PB3 I/O event                 */
#define LL_PWR_WAKEUP_PB2            PWR_CR3_EWU2              /*!< Enable wakeup on PB2 I/O event                 */
#define LL_PWR_WAKEUP_PB1            PWR_CR3_EWU1              /*!< Enable wakeup on PB1 I/O event                 */
#define LL_PWR_WAKEUP_PB0            PWR_CR3_EWU0              /*!< Enable wakeup on PB0 I/O event                 */
#define LL_PWR_WAKEUP_PB15           (PWR_CR6_EWU19 << 16)     /*!< Enable wakeup on PB15 I/O event                */
#define LL_PWR_WAKEUP_PB14           (PWR_CR6_EWU18 << 16)     /*!< Enable wakeup on PB14 I/O event                */
#define LL_PWR_WAKEUP_PB13           (PWR_CR6_EWU17 << 16)     /*!< Enable wakeup on PB13 I/O event                */
#define LL_PWR_WAKEUP_PB12           (PWR_CR6_EWU16 << 16)     /*!< Enable wakeup on PB12 I/O event                */
#else
#define LL_PWR_WAKEUP_CR6_ALL        (0x0000FFFFU << 16)        /*!< Enable all the wakeup source in CR6            */
#define LL_PWR_WAKEUP_CR3_ALL        (0x0000BFFFU)              /*!< Enable all the wakeup source in CR3            */
#define LL_PWR_WAKEUP_ALL            LL_PWR_WAKEUP_CR6_ALL | LL_PWR_WAKEUP_CR3_ALL
#define LL_PWR_WAKEUP_RTC            PWR_CR3_EIWL              /*!< Enable wakeup on Internal event (RTC)          */
#define LL_PWR_WAKEUP_BLEHOST        PWR_CR3_EWBLEHCPU         /*!< Enable wakeup on BLE Host CPU event            */
#define LL_PWR_WAKEUP_BLE            PWR_CR3_EWBLE             /*!< Enable wakeup on BLE event                     */
#define LL_PWR_WAKEUP_PA15           (PWR_CR6_EWU27 << 16)     /*!< Enable wakeup on PA15 I/O event                */
#define LL_PWR_WAKEUP_PA14           (PWR_CR6_EWU26 << 16)     /*!< Enable wakeup on PA14 I/O event                */
#define LL_PWR_WAKEUP_PA13           (PWR_CR6_EWU25 << 16)     /*!< Enable wakeup on PA13 I/O event                */
#define LL_PWR_WAKEUP_PA12           (PWR_CR6_EWU24 << 16)     /*!< Enable wakeup on PA12 I/O event                */
#define LL_PWR_WAKEUP_PA11           PWR_CR3_EWU11             /*!< Enable wakeup on PA11 I/O event                */
#define LL_PWR_WAKEUP_PA10           PWR_CR3_EWU10             /*!< Enable wakeup on PA10 I/O event                */
#define LL_PWR_WAKEUP_PA9            PWR_CR3_EWU9              /*!< Enable wakeup on PA9 I/O event                 */
#define LL_PWR_WAKEUP_PA8            PWR_CR3_EWU8              /*!< Enable wakeup on PA8 I/O event                 */
#define LL_PWR_WAKEUP_PA7            (PWR_CR6_EWU19 << 16)     /*!< Enable wakeup on LP-PA7 I/O event              */
#define LL_PWR_WAKEUP_PA6            (PWR_CR6_EWU18 << 16)     /*!< Enable wakeup on LP-PA6 I/O event              */
#define LL_PWR_WAKEUP_PA5            (PWR_CR6_EWU17 << 16)     /*!< Enable wakeup on LP-PA5 I/O event              */
#define LL_PWR_WAKEUP_PA4            (PWR_CR6_EWU16 << 16)     /*!< Enable wakeup on LP-PA4 I/O event              */
#define LL_PWR_WAKEUP_PA3            (PWR_CR6_EWU15 << 16)     /*!< Enable wakeup on PA3 I/O event                 */
#define LL_PWR_WAKEUP_PA2            (PWR_CR6_EWU14 << 16)     /*!< Enable wakeup on PA2 I/O event                 */
#define LL_PWR_WAKEUP_PA1            (PWR_CR6_EWU13 << 16)     /*!< Enable wakeup on PA1 I/O event                 */
#define LL_PWR_WAKEUP_PA0            (PWR_CR6_EWU12 << 16)     /*!< Enable wakeup on PA0 I/O event                 */
#define LL_PWR_WAKEUP_PB11           (PWR_CR6_EWU23 << 16)     /*!< Enable wakeup on PB11 I/O event                */
#define LL_PWR_WAKEUP_PB10           (PWR_CR6_EWU22 << 16)     /*!< Enable wakeup on PB10 I/O event                */
#define LL_PWR_WAKEUP_PB9            (PWR_CR6_EWU21 << 16)     /*!< Enable wakeup on PB9 I/O event                 */
#define LL_PWR_WAKEUP_PB8            (PWR_CR6_EWU20 << 16)     /*!< Enable wakeup on PB8 I/O event                 */
#define LL_PWR_WAKEUP_PB7            PWR_CR3_EWU7              /*!< Enable wakeup on PB7 I/O event                 */
#define LL_PWR_WAKEUP_PB6            PWR_CR3_EWU6              /*!< Enable wakeup on PB6 I/O event                 */
#define LL_PWR_WAKEUP_PB5            PWR_CR3_EWU5              /*!< Enable wakeup on PB5 I/O event                 */
#define LL_PWR_WAKEUP_PB4            PWR_CR3_EWU4              /*!< Enable wakeup on PB4 I/O event                 */
#define LL_PWR_WAKEUP_PB3            PWR_CR3_EWU3              /*!< Enable wakeup on PB3 I/O event                 */
#define LL_PWR_WAKEUP_PB2            PWR_CR3_EWU2              /*!< Enable wakeup on PB2 I/O event                 */
#define LL_PWR_WAKEUP_PB1            PWR_CR3_EWU1              /*!< Enable wakeup on PB1 I/O event                 */
#define LL_PWR_WAKEUP_PB0            PWR_CR3_EWU0              /*!< Enable wakeup on PB0 I/O event                 */
#endif /* !defined(PWR_CR6_EWU20) */
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

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_SR1_WUFI                    PWR_SR1_IWUF
#if defined(PWR_CR3_EIWL2)
#define LL_PWR_SR1_WUFI2                   PWR_SR1_IWUF2
#endif /* PWR_CR3_EIWL2 */
#define LL_PWR_SR1_BHWF                    PWR_SR1_WBLEHCPUF
#define LL_PWR_SR1_WBLEF                   PWR_SR1_WBLEF
#define LL_PWR_SR1_WUF0                    PWR_SR1_WUF0
#define LL_PWR_SR1_WUF1                    PWR_SR1_WUF1
#define LL_PWR_SR1_WUF2                    PWR_SR1_WUF2
#define LL_PWR_SR1_WUF3                    PWR_SR1_WUF3
#define LL_PWR_SR1_WUF4                    PWR_SR1_WUF4
#define LL_PWR_SR1_WUF5                    PWR_SR1_WUF5
#define LL_PWR_SR1_WUF6                    PWR_SR1_WUF6
#define LL_PWR_SR1_WUF7                    PWR_SR1_WUF7
#define LL_PWR_SR1_WUF8                    PWR_SR1_WUF8
#define LL_PWR_SR1_WUF9                    PWR_SR1_WUF9
#define LL_PWR_SR1_WUF10                   PWR_SR1_WUF10
#define LL_PWR_SR1_WUF11                   PWR_SR1_WUF11
#define LL_PWR_SR3_WUF12                   (PWR_SR3_WUF12 << 16)
#define LL_PWR_SR3_WUF13                   (PWR_SR3_WUF13 << 16)
#define LL_PWR_SR3_WUF14                   (PWR_SR3_WUF14 << 16)
#define LL_PWR_SR3_WUF15                   (PWR_SR3_WUF15 << 16)
#define LL_PWR_SR3_WUF16                   (PWR_SR3_WUF16 << 16)
#define LL_PWR_SR3_WUF17                   (PWR_SR3_WUF17 << 16)
#define LL_PWR_SR3_WUF18                   (PWR_SR3_WUF18 << 16)
#define LL_PWR_SR3_WUF19                   (PWR_SR3_WUF19 << 16)
#if defined(PWR_CR6_EWU20)
#define LL_PWR_SR3_WUF20                   (PWR_SR3_WUF20 << 16)
#endif /* PWR_CR6_EWU20 */
#if defined(PWR_CR6_EWU21)
#define LL_PWR_SR3_WUF21                   (PWR_SR3_WUF21 << 16)
#endif /* PWR_CR6_EWU21 */
#if defined(PWR_CR6_EWU22)
#define LL_PWR_SR3_WUF22                   (PWR_SR3_WUF22 << 16)
#endif /* PWR_CR6_EWU22 */
#if defined(PWR_CR6_EWU23)
#define LL_PWR_SR3_WUF23                   (PWR_SR3_WUF23 << 16)
#endif /* PWR_CR6_EWU23 */
#if defined(PWR_CR6_EWU24)
#define LL_PWR_SR3_WUF24                   (PWR_SR3_WUF24 << 16)
#endif /* PWR_CR6_EWU24 */
#if defined(PWR_CR6_EWU25)
#define LL_PWR_SR3_WUF25                   (PWR_SR3_WUF25 << 16)
#endif /* PWR_CR6_EWU25 */
#if defined(PWR_CR6_EWU26)
#define LL_PWR_SR3_WUF26                   (PWR_SR3_WUF26 << 16)
#endif /* PWR_CR6_EWU26 */
#if defined(PWR_CR6_EWU27)
#define LL_PWR_SR3_WUF27                   (PWR_SR3_WUF27 << 16)
#endif /* PWR_CR6_EWU27 */
#if defined (PWR_CR3_EIWL2)
#define LL_PWR_SR1_WUFALL                  0x0000FFFF
#else
#define LL_PWR_SR1_WUFALL                  0x0000BFFF
#endif /* PWR_CR3_EIWL2 */
#if defined (PWR_SR3_WUF20)
#define LL_PWR_SR3_WUFALL                  0xFFFF0000
#else
#define LL_PWR_SR3_WUFALL                  0x00FF0000
#endif /* PWR_SR3_WUF20 */
#define LL_PWR_WUFALL                      (LL_PWR_SR1_WUFALL | LL_PWR_SR3_WUFALL)
#define LL_PWR_EXTSRR_RFPHASEF             PWR_EXTSRR_RFPHASEF
#define LL_PWR_EXTSRR_DEEPSTOPF            PWR_EXTSRR_DEEPSTOPF
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_PIN_MASK PWR GPIO Pin Mask
  * @{
  */
#define LL_PWR_GPIO_BIT_0              (0x0001U)               /*!< GPIO port I/O pin 0  */
#define LL_PWR_GPIO_BIT_1              (0x0002U)               /*!< GPIO port I/O pin 1  */
#define LL_PWR_GPIO_BIT_2              (0x0004U)               /*!< GPIO port I/O pin 2  */
#define LL_PWR_GPIO_BIT_3              (0x0008U)               /*!< GPIO port I/O pin 3  */
#define LL_PWR_GPIO_BIT_4              (0x0010U)               /*!< GPIO port I/O pin 4  */
#define LL_PWR_GPIO_BIT_5              (0x0020U)               /*!< GPIO port I/O pin 5  */
#define LL_PWR_GPIO_BIT_6              (0x0040U)               /*!< GPIO port I/O pin 6  */
#define LL_PWR_GPIO_BIT_7              (0x0080U)               /*!< GPIO port I/O pin 7  */
#define LL_PWR_GPIO_BIT_8              (0x0100U)               /*!< GPIO port I/O pin 8  */
#define LL_PWR_GPIO_BIT_9              (0x0200U)               /*!< GPIO port I/O pin 9  */
#define LL_PWR_GPIO_BIT_10             (0x0400U)               /*!< GPIO port I/O pin 10 */
#define LL_PWR_GPIO_BIT_11             (0x0800U)               /*!< GPIO port I/O pin 11 */
#define LL_PWR_GPIO_BIT_12             (0x1000U)               /*!< GPIO port I/O pin 12 */
#define LL_PWR_GPIO_BIT_13             (0x2000U)               /*!< GPIO port I/O pin 13 */
#define LL_PWR_GPIO_BIT_14             (0x4000U)               /*!< GPIO port I/O pin 14 */
#define LL_PWR_GPIO_BIT_15             (0x8000U)               /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_IO_CFG IOs PU/PD configuration
  * @{
  */
#define LL_PWR_WUP_RISIEDG      (0x000000000U)                 /*!< Detection of wakeup event on rising edge. */
#define LL_PWR_WUP_FALLEDG      (0x000000001U)                 /*!< Detection of wakeup event on falling edge. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_IO_OUT_CFG PA4-PA11 output configuration during DEEPSTOP
  * @{
  */
#define LL_PWR_IOCFG_BYP        (0x000000000U)                 /*!< BYPASS mode. The I/O mode is controlled by the GPIO block
                                                                  registers in active mode and switch to input mode during DEESPTOP state. */
#define LL_PWR_IOCFG_RTC        (0x000000001U)                 /*!< RTC_OUT signal for PA11 and PA8                                        */
#define LL_PWR_IOCFG_LCO        (0x000000001U)                 /*!< LCO output signal for PA10 and PA9                                     */
#define LL_PWR_IOCFG_LOW        (0x000000002U)                 /*!< I/O drives a low level in both active and DEEPSTOP modes               */
#define LL_PWR_IOCFG_HIGH       (0x000000003U)                 /*!< I/O drives a high level in both active and DEEPSTOP modes              */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_IO_LATCH_BOOT PA8-PA11 I/Os value latched at POR.
  * @{
  */
#define LL_PWR_PA8_LATCH_POR    PWR_SR2_IOBOOTVAL_0            /*!< PA8  input value latched at POR. */
#define LL_PWR_PA9_LATCH_POR    PWR_SR2_IOBOOTVAL_1            /*!< PA9  input value latched at POR. */
#define LL_PWR_PA10_LATCH_POR   PWR_SR2_IOBOOTVAL_2            /*!< PA10 input value latched at POR. */
#define LL_PWR_PA11_LATCH_POR   PWR_SR2_IOBOOTVAL_3            /*!< PA11 input value latched at POR. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_IO_LATCH_BOOT_2 PB12-PB15 I/Os value latched at POR.
  * @{
  */
#if defined(PWR_SR2_IOBOOTVAL2_0)
#define LL_PWR_PB12_LATCH_POR   PWR_SR2_IOBOOTVAL2_0           /*!< PB12  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_0 */
#if defined(PWR_SR2_IOBOOTVAL2_1)
#define LL_PWR_PB13_LATCH_POR   PWR_SR2_IOBOOTVAL2_1           /*!< PB13  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_1 */
#if defined(PWR_SR2_IOBOOTVAL2_2)
#define LL_PWR_PB14_LATCH_POR   PWR_SR2_IOBOOTVAL2_2           /*!< PB14  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_2 */
#if defined(PWR_SR2_IOBOOTVAL2_3)
#define LL_PWR_PB15_LATCH_POR   PWR_SR2_IOBOOTVAL2_3           /*!< PB15  input value latched at POR. */
#endif /* PWR_SR2_IOBOOTVAL2_3 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_MODE SMPS Mode
  * @{
  */
#define LL_PWR_SMPS             (0x000000000U)                 /*!< SMPS is enabled     */
#define LL_PWR_NO_SMPS          PWR_CR5_NOSMPS                 /*!< SMPS is disabled    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_PRECHARGE_MODE SMPS PRECHARGE Mode
  * @{
  */
#define LL_PWR_NO_SMPS_PRECHARGE    (0x000000000U)             /*!< SMPS not in pecharge mode     */
#define LL_PWR_SMPS_PRECHARGE       PWR_CR5_SMPSFBYP           /*!< SMPS is disabled and bypassed in precharge mode    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_OPEN_MODE SMPS OPEN Mode during DEEPSTOP
  * @{
  */
#define LL_PWR_NO_SMPS_LPOPEN    (0x000000000U)                /*!< In DEEPSTOP, the SMPS is in PRECHARGE mode with output connected to VDDIO */
#define LL_PWR_SMPS_LPOPEN       PWR_CR5_SMPSLPOPEN            /*!< In DEEPSTOP, the SMPS is disabled with floating output                    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_BOM SMPS BOM
  * @{
  */
#define LL_PWR_SMPS_BOM1        (0x000000000U)
#define LL_PWR_SMPS_BOM2        PWR_CR5_SMPSBOMSEL_0
#define LL_PWR_SMPS_BOM3        PWR_CR5_SMPSBOMSEL_1
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_OUTPUT_VOLTAGE_LEVEL SMPS step down converter output voltage scaling voltage level
  * @{
  */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V20              (0x000000000U)                                                   /*!< SMPS step down converter supply output voltage 1.20V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V25              (PWR_CR5_SMPSLVL_0)                                              /*!< SMPS step down converter supply output voltage 1.25V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V30              (PWR_CR5_SMPSLVL_1)                                              /*!< SMPS step down converter supply output voltage 1.30V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V35              (PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)                            /*!< SMPS step down converter supply output voltage 1.35V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V40              (PWR_CR5_SMPSLVL_2)                                              /*!< SMPS step down converter supply output voltage 1.40V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V45              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)                            /*!< SMPS step down converter supply output voltage 1.45V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V50              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)                            /*!< SMPS step down converter supply output voltage 1.50V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V55              (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)          /*!< SMPS step down converter supply output voltage 1.55V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V60              (PWR_CR5_SMPSLVL_3)                                              /*!< SMPS step down converter supply output voltage 1.60V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V65              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_0)                            /*!< SMPS step down converter supply output voltage 1.65V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V70              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1)                            /*!< SMPS step down converter supply output voltage 1.70V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V75              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)          /*!< SMPS step down converter supply output voltage 1.75V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V80              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2)                            /*!< SMPS step down converter supply output voltage 1.80V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V85              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)          /*!< SMPS step down converter supply output voltage 1.85V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V90              (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)          /*!< SMPS step down converter supply output voltage 1.90V */
#define LL_PWR_SMPS_OUTPUT_VOLTAGE_1V95              (PWR_CR5_SMPSLVL)                                                /*!< SMPS step down converter supply output voltage 1.95V */
/**
  * @}
  */

#if defined(PWR_CR5_SMPS_PRECH_CUR_SEL)
/** @defgroup PWR_LL_EC_SMPS_PRECHARGE_LIMIT_CURRENT Select SMPS PRECHARGE limit current
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

/** @defgroup PWR_LL_EM_WRITE_READ Common Write and read registers Macros
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

/** @defgroup PWR_LL_EF_Configuration PWR Configuration
  * @{
  */

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

/**
  * @brief  Set low-power mode.
  * @rmtoll CR1          LPMS           LL_PWR_SetPowerMode
  * @param  LowPowerMode Low Power Mode Selection. This parameter can be one of the following values:
  *         @arg LL_PWR_MODE_DEEPSTOP
  *         @arg LL_PWR_MODE_SHUTDOWN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t LowPowerMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, LowPowerMode);
}

/**
  * @brief  Get Low-Power mode
  * @rmtoll CR1          LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_DEEPSTOP
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  */

__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPMS));
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

#if defined(PWR_CR2_LSILPMUFEN)
/**
  * @brief  LSI always enabled. Instead to be enabled/disabled by hardware depending
  *         on the analog LPMU block needs.
  * @rmtoll CR2          LSILPMUFEN           LL_PWR_EnableLSILPMU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableLSILPMU(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_LSILPMUFEN);
}

/**
  * @brief  Disable the LSI always enabled. With this setting the LSI LPMU is automatically enabled/disabled
  *         by hardware depending on the analog LPMU block needs.
  * @rmtoll CR2          LSILPMUFEN           LL_PWR_DisableLSILPMU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableLSILPMU(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_LSILPMUFEN);
}

/**
  * @brief  Checks if LSI LPMU is enabled or disabled.
  * @rmtoll CR2         LSILPMUFEN     LL_PWR_IsEnabledLSILPMU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledLSILPMU(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_LSILPMUFEN) == (PWR_CR2_LSILPMUFEN)) ? 1UL : 0UL);
}
#endif /* PWR_CR2_LSILPMUFEN */

#if defined(PWR_CR2_ENTS)
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
#endif /* PWR_CR2_ENTS */

/**
  * @brief  Enable the RAM bank retention.
  * @rmtoll CR2         RAMRET1    LL_PWR_DisableRAMBankRet
  *         CR2         RAMRET2    LL_PWR_DisableRAMBankRet
  *         CR2         RAMRET3    LL_PWR_DisableRAMBankRet
  * @param  banks RAM bank selection. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_RAMRET_1
  *         @arg @ref LL_PWR_RAMRET_2 (*)
  *         @arg @ref LL_PWR_RAMRET_3 (*)
  *         (*) Not available on devices STM32WB05
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableRAMBankRet(uint32_t banks)
{
  SET_BIT(PWR->CR2, banks);
}

/**
  * @brief  Get the RAM banks retention selected.
  * @rmtoll CR2         RAMRET1    LL_PWR_DisableRAMBankRet
  *         CR2         RAMRET2    LL_PWR_DisableRAMBankRet
  *         CR2         RAMRET3    LL_PWR_DisableRAMBankRet
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RAMRET_1
  *         @arg @ref LL_PWR_RAMRET_2 (*)
  *         @arg @ref LL_PWR_RAMRET_3 (*)
  *         (*) Not available on devices STM32WB05
  */
__STATIC_INLINE uint32_t LL_PWR_GetRAMBankRet(void)
{
  uint32_t ram_ret;

  ram_ret = READ_BIT(PWR->CR2, (PWR_CR2_RAMRET1));
#if defined(PWR_CR2_RAMRET2)
  ram_ret |= READ_BIT(PWR->CR2, (PWR_CR2_RAMRET2));
#endif /* PWR_CR2_RAMRET2 */
#if defined(PWR_CR2_RAMRET3)
  ram_ret |= READ_BIT(PWR->CR2, (PWR_CR2_RAMRET3));
#endif /* PWR_CR2_RAMRET3 */
  return ram_ret;
}

/**
  * @brief  Disable the RAM bank retention.
  * @rmtoll CR2         RAMRET1    LL_PWR_DisableRAMBankRet
  *         CR2         RAMRET2    LL_PWR_DisableRAMBankRet
  *         CR2         RAMRET3    LL_PWR_DisableRAMBankRet
  * @param  banks RAM bank selection. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_RAMRET_1
  *         @arg @ref LL_PWR_RAMRET_2 (*)
  *         @arg @ref LL_PWR_RAMRET_3 (*)
  *         (*) Not available on devices STM32WB05
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableRAMBankRet(uint32_t banks)
{
  CLEAR_BIT(PWR->CR2, banks);
}

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector.
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
  * @brief  Get the voltage threshold detection.
  * @rmtoll CR2         PVDLS      LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
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
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR2          PVDE           LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Disable the Power Voltage Detector.
  * @rmtoll CR2          PVDE           LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled or disabled.
  * @rmtoll CR2         PVDE      LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_PVDE) == (PWR_CR2_PVDE)) ? 1UL : 0UL);
}

#if defined (PWR_CR2_GPIORET)
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
#endif /* PWR_CR2_GPIORET */

#if defined (PWR_CR2_DBGRET)
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
#endif /* PWR_CR2_DBGRET */

/**
  * @brief  Enable Internal Wake-up line (RTC)
  * @rmtoll CR3          EIWL          LL_PWR_EnableInternWU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableInternWU(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EIWL);
}

/**
  * @brief  Disable Internal Wake-up line (RTC)
  * @rmtoll CR3          EIWL          LL_PWR_DisableInternWU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableInternWU(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EIWL);
}

/**
  * @brief  Check if Internal Wake-up line is enabled (RTC)
  * @rmtoll CR3          EIWL          LL_PWR_IsEnabledInternWU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledInternWU(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_EIWL) == (PWR_CR3_EIWL)) ? 1UL : 0UL);
}

#if defined (PWR_CR3_EIWL2)
/**
  * @brief  Enable Internal Wake-up line (LPUART)
  * @rmtoll CR3          EIWL2          LL_PWR_EnableInternWU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableInternWU2(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EIWL2);
}

/**
  * @brief  Disable Internal Wake-up line (LPUART)
  * @rmtoll CR3          EIWL2          LL_PWR_EnableInternWU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableInternWU2(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EIWL2);
}

/**
  * @brief  Check if Internal Wake-up line is enabled (LPUART)
  * @rmtoll CR3          EIWL2          LL_PWR_EnableInternWU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledInternWU2(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_EIWL2) == (PWR_CR3_EIWL2)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Internal Wake-up2 flag
  * @rmtoll SR3          IWUF2        LL_PWR_ClearFlag_BORH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_InternWU2(void)
{
  WRITE_REG(PWR->SR1, PWR_SR1_IWUF2);
}

#endif /* PWR_CR3_EIWL2 */

/**
  * @brief  Enable Wakeup PINx to get out of DEEPSTOP mode.
  * @rmtoll CR3          EWU0         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU1         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU2         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU3         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU4         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU5         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU6         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU7         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU8         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU9         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU10        LL_PWR_EnableWakeUpPin\n
  *         CR3          EWU11        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU12        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU13        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU14        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU15        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU16        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU17        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU18        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU19        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU20        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU21        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU22        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU23        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU24        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU25        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU26        LL_PWR_EnableWakeUpPin\n
  *         CR6          EWU27        LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin Enable the wakeup sources.
  * This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PA0
  *         @arg @ref LL_PWR_WAKEUP_PA1
  *         @arg @ref LL_PWR_WAKEUP_PA2
  *         @arg @ref LL_PWR_WAKEUP_PA3
  *         @arg @ref LL_PWR_WAKEUP_PA4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA8
  *         @arg @ref LL_PWR_WAKEUP_PA9
  *         @arg @ref LL_PWR_WAKEUP_PA10
  *         @arg @ref LL_PWR_WAKEUP_PA11
  *         @arg @ref LL_PWR_WAKEUP_PA12 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA13 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA14 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA15 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB0
  *         @arg @ref LL_PWR_WAKEUP_PB1
  *         @arg @ref LL_PWR_WAKEUP_PB2
  *         @arg @ref LL_PWR_WAKEUP_PB3
  *         @arg @ref LL_PWR_WAKEUP_PB4
  *         @arg @ref LL_PWR_WAKEUP_PB5
  *         @arg @ref LL_PWR_WAKEUP_PB6
  *         @arg @ref LL_PWR_WAKEUP_PB7
  *         @arg @ref LL_PWR_WAKEUP_PB8 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB9 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB10 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB11 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB12 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB13 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB14 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CR3, (WakeUpPin & 0x0000FFFF));
  SET_BIT(PWR->CR6, (WakeUpPin >> 16));
}

/**
  * @brief  Disable Wakeup PINx to get out of DEEPSTOP mode.
  * @rmtoll CR3          EWU0         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU1         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU2         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU3         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU4         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU5         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU6         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU7         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU8         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU9         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU10        LL_PWR_DisableWakeUpPin\n
  *         CR3          EWU11        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU12        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU13        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU14        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU15        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU16        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU17        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU18        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU19        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU20        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU21        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU22        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU23        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU24        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU25        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU26        LL_PWR_DisableWakeUpPin\n
  *         CR6          EWU27        LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin Enable the wakeup sources.
  * This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PA0
  *         @arg @ref LL_PWR_WAKEUP_PA1
  *         @arg @ref LL_PWR_WAKEUP_PA2
  *         @arg @ref LL_PWR_WAKEUP_PA3
  *         @arg @ref LL_PWR_WAKEUP_PA4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA8
  *         @arg @ref LL_PWR_WAKEUP_PA9
  *         @arg @ref LL_PWR_WAKEUP_PA10
  *         @arg @ref LL_PWR_WAKEUP_PA11
  *         @arg @ref LL_PWR_WAKEUP_PA12 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA13 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA14 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA15 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB0
  *         @arg @ref LL_PWR_WAKEUP_PB1
  *         @arg @ref LL_PWR_WAKEUP_PB2
  *         @arg @ref LL_PWR_WAKEUP_PB3
  *         @arg @ref LL_PWR_WAKEUP_PB4
  *         @arg @ref LL_PWR_WAKEUP_PB5
  *         @arg @ref LL_PWR_WAKEUP_PB6
  *         @arg @ref LL_PWR_WAKEUP_PB7
  *         @arg @ref LL_PWR_WAKEUP_PB8 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB9 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB10 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB11 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB12 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB13 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB14 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CR3, (WakeUpPin & 0x0000FFFF));
  CLEAR_BIT(PWR->CR6, (WakeUpPin >> 16));
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll CR3          EWU0         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU1         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU2         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU3         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU4         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU5         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU6         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU7         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU8         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU9         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU10        LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWU11        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU12        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU13        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU14        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU15        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU16        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU17        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU18        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU19        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU20        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU21        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU22        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU23        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU24        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU25        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU26        LL_PWR_IsEnabledWakeUpPin\n
  *         CR6          EWU27        LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PA0
  *         @arg @ref LL_PWR_WAKEUP_PA1
  *         @arg @ref LL_PWR_WAKEUP_PA2
  *         @arg @ref LL_PWR_WAKEUP_PA3
  *         @arg @ref LL_PWR_WAKEUP_PA4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA8
  *         @arg @ref LL_PWR_WAKEUP_PA9
  *         @arg @ref LL_PWR_WAKEUP_PA10
  *         @arg @ref LL_PWR_WAKEUP_PA11
  *         @arg @ref LL_PWR_WAKEUP_PA12 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA13 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA14 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA15 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB0
  *         @arg @ref LL_PWR_WAKEUP_PB1
  *         @arg @ref LL_PWR_WAKEUP_PB2
  *         @arg @ref LL_PWR_WAKEUP_PB3
  *         @arg @ref LL_PWR_WAKEUP_PB4
  *         @arg @ref LL_PWR_WAKEUP_PB5
  *         @arg @ref LL_PWR_WAKEUP_PB6
  *         @arg @ref LL_PWR_WAKEUP_PB7
  *         @arg @ref LL_PWR_WAKEUP_PB8 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB9 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB10 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB11 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB12 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB13 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB14 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->CR3, (WakeUpPin & 0x0000FFFF)) == (WakeUpPin & 0x0000FFFF)) &&
          (READ_BIT(PWR->CR6, (WakeUpPin >> 16)) == (WakeUpPin >> 16)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin polarity low for the event detection
  * @rmtoll CR4          WUP0         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP1         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP2         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP3         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP4         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP5         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP6         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP7         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP8         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP9         LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP10        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WUP11        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP12        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP13        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP14        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP15        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP16        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP17        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP18        LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR7          WUP19        LL_PWR_SetWakeUpPinPolarityLow
  * @param  WakeUpPin Pin to configure. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PA0
  *         @arg @ref LL_PWR_WAKEUP_PA1
  *         @arg @ref LL_PWR_WAKEUP_PA2
  *         @arg @ref LL_PWR_WAKEUP_PA3
  *         @arg @ref LL_PWR_WAKEUP_PA4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA8
  *         @arg @ref LL_PWR_WAKEUP_PA9
  *         @arg @ref LL_PWR_WAKEUP_PA10
  *         @arg @ref LL_PWR_WAKEUP_PA11
  *         @arg @ref LL_PWR_WAKEUP_PA12 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA13 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA14 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA15 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB0
  *         @arg @ref LL_PWR_WAKEUP_PB1
  *         @arg @ref LL_PWR_WAKEUP_PB2
  *         @arg @ref LL_PWR_WAKEUP_PB3
  *         @arg @ref LL_PWR_WAKEUP_PB4
  *         @arg @ref LL_PWR_WAKEUP_PB5
  *         @arg @ref LL_PWR_WAKEUP_PB6
  *         @arg @ref LL_PWR_WAKEUP_PB7
  *         @arg @ref LL_PWR_WAKEUP_PB8 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB9 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB10 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB11 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB12 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB13 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB14 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CR4, (WakeUpPin & 0x0000FFFF));
  SET_BIT(PWR->CR7, (WakeUpPin >> 16));

}

/**
  * @brief  Set the Wake-Up pin polarity high for the event detection
  * @rmtoll CR4          WUP0         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP1         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP2         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP3         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP4         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP5         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP6         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP7         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP8         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP9         LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP10        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WUP11        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP12        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP13        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP14        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP15        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP16        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP17        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP18        LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR7          WUP19        LL_PWR_SetWakeUpPinPolarityHigh
  * @param  WakeUpPin Pin to configure. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PA0
  *         @arg @ref LL_PWR_WAKEUP_PA1
  *         @arg @ref LL_PWR_WAKEUP_PA2
  *         @arg @ref LL_PWR_WAKEUP_PA3
  *         @arg @ref LL_PWR_WAKEUP_PA4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA8
  *         @arg @ref LL_PWR_WAKEUP_PA9
  *         @arg @ref LL_PWR_WAKEUP_PA10
  *         @arg @ref LL_PWR_WAKEUP_PA11
  *         @arg @ref LL_PWR_WAKEUP_PA12 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA13 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA14 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA15 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB0
  *         @arg @ref LL_PWR_WAKEUP_PB1
  *         @arg @ref LL_PWR_WAKEUP_PB2
  *         @arg @ref LL_PWR_WAKEUP_PB3
  *         @arg @ref LL_PWR_WAKEUP_PB4
  *         @arg @ref LL_PWR_WAKEUP_PB5
  *         @arg @ref LL_PWR_WAKEUP_PB6
  *         @arg @ref LL_PWR_WAKEUP_PB7
  *         @arg @ref LL_PWR_WAKEUP_PB8 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB9 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB10 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB11 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB12 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB13 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB14 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CR4, (WakeUpPin & 0x0000FFFF));
  CLEAR_BIT(PWR->CR7, (WakeUpPin >> 16));

}

/**
  * @brief  Get the polarity for the I/Os wakeup sources.
  * @rmtoll CR4          WUP0         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP1         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP2         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP3         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP4         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP5         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP6         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP7         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP8         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP9         LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP10        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WUP11        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP12        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP13        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP14        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP15        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP16        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP17        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP18        LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR7          WUP19        LL_PWR_IsWakeUpPinPolarityLow
  * @param  WakeUpPin Pin to configure. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PA0
  *         @arg @ref LL_PWR_WAKEUP_PA1
  *         @arg @ref LL_PWR_WAKEUP_PA2
  *         @arg @ref LL_PWR_WAKEUP_PA3
  *         @arg @ref LL_PWR_WAKEUP_PA4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA8
  *         @arg @ref LL_PWR_WAKEUP_PA9
  *         @arg @ref LL_PWR_WAKEUP_PA10
  *         @arg @ref LL_PWR_WAKEUP_PA11
  *         @arg @ref LL_PWR_WAKEUP_PA12 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA13 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA14 (*)
  *         @arg @ref LL_PWR_WAKEUP_PA15 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB0
  *         @arg @ref LL_PWR_WAKEUP_PB1
  *         @arg @ref LL_PWR_WAKEUP_PB2
  *         @arg @ref LL_PWR_WAKEUP_PB3
  *         @arg @ref LL_PWR_WAKEUP_PB4
  *         @arg @ref LL_PWR_WAKEUP_PB5
  *         @arg @ref LL_PWR_WAKEUP_PB6
  *         @arg @ref LL_PWR_WAKEUP_PB7
  *         @arg @ref LL_PWR_WAKEUP_PB8 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB9 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB10 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB11 (*)
  *         @arg @ref LL_PWR_WAKEUP_PB12 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB13 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB14 (**)
  *         @arg @ref LL_PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  * @retval None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  if (WakeUpPin & 0x0000FFFF)
  {
    return (uint32_t)((READ_BIT(PWR->CR4, (WakeUpPin & 0x0000FFFF))) ? 1UL : 0UL);
  }
  else
  {
    return (uint32_t)((READ_BIT(PWR->CR7, (WakeUpPin >> 16))) ? 1UL : 0UL);
  }

}

/**
  * @brief  Enable wakeup on BLE event.
  * @rmtoll CR3          EWBLE         LL_PWR_EnableWU_EWBLE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWU_EWBLE(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EWBLE);
}

/**
  * @brief  Enable wakeup on BLE Host CPU event.
  * @rmtoll CR3          EWBLEHCPU         LL_PWR_EnableWU_EWBLEHCPU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWU_EWBLEHCPU(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EWBLEHCPU);
}

/**
  * @brief  Disable wakeup on BLE Host CPU event.
  * @rmtoll CR3          EWBLE         LL_PWR_DisableWU_EWBLE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWU_EWBLE(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EWBLE);
}

/**
  * @brief  Disable wakeup on BLE Host CPU event.
  * @rmtoll CR3          EWBLEHCPU         LL_PWR_DisableWU_EWBLEHCPU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWU_EWBLEHCPU(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EWBLEHCPU);
}

/**
  * @brief  Check if the wakeup BLE is enabled
  * @rmtoll CR3          EWBLE         LL_PWR_IsEnabledWU_EWBLE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWU_EWBLE(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_EWBLE) == (PWR_CR3_EWBLE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the wakeup BLE Host CPU is enabled
  * @rmtoll CR3          EWBLEHCPU         LL_PWR_IsEnabledWU_EWBLEHCPU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWU_EWBLEHCPU(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_EWBLEHCPU) == (PWR_CR3_EWBLEHCPU)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Internal Wake-up line Flag (RTC)
  * @rmtoll SR1          IWUF          LL_PWR_IsActiveFlag_InternWU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_InternWU(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_IWUF) == (PWR_SR1_IWUF)) ? 1UL : 0UL);
}

#if defined(PWR_CR3_EIWL2)
/**
  * @brief  Get Internal Wake-up line Flag (LPUART)
  * @rmtoll SR1          IWUF2          LL_PWR_IsActiveFlag_InternWU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_InternWU2(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_IWUF2) == (PWR_SR1_IWUF2)) ? 1UL : 0UL);
}
#endif /* PWR_CR3_EIWL2 */

/**
  * @brief  Get Wake-up Flag 0
  * @rmtoll SR1          WUF0          LL_PWR_IsActiveFlag_WU0
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU0(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF0) == (PWR_SR1_WUF0)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 1
  * @rmtoll SR1          WUF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF1) == (PWR_SR1_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 2
  * @rmtoll SR1          WUF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF2) == (PWR_SR1_WUF2)) ? 1UL : 0UL);
}
/**
  * @brief  Get Wake-up Flag 3
  * @rmtoll SR1          WUF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF3) == (PWR_SR1_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 4
  * @rmtoll SR1          WUF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF4) == (PWR_SR1_WUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 5
  * @rmtoll SR1          WUF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF5) == (PWR_SR1_WUF5)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 6
  * @rmtoll SR1          WUF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF6) == (PWR_SR1_WUF6)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 7
  * @rmtoll SR1          WUF7          LL_PWR_IsActiveFlag_WU7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF7) == (PWR_SR1_WUF7)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 8
  * @rmtoll SR1          WUF8         LL_PWR_IsActiveFlag_WU8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU8(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF8) == (PWR_SR1_WUF8)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 9
  * @rmtoll SR1          WUF9          LL_PWR_IsActiveFlag_WU9
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU9(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF9) == (PWR_SR1_WUF9)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 10
  * @rmtoll SR1          WUF10          LL_PWR_IsActiveFlag_WU10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU10(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF10) == (PWR_SR1_WUF10)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 11
  * @rmtoll SR1          WUF11          LL_PWR_IsActiveFlag_WU11
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU11(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF11) == (PWR_SR1_WUF11)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 12
  * @rmtoll SR3          WUF12          LL_PWR_IsActiveFlag_WU12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU12(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF12) == (PWR_SR3_WUF12)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 13
  * @rmtoll SR3          WUF13          LL_PWR_IsActiveFlag_WU13
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU13(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF13) == (PWR_SR3_WUF13)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 14
  * @rmtoll SR3          WUF14          LL_PWR_IsActiveFlag_WU14
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU14(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF14) == (PWR_SR3_WUF14)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 15
  * @rmtoll SR3          WUF15          LL_PWR_IsActiveFlag_WU15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU15(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF15) == (PWR_SR3_WUF15)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 16
  * @rmtoll SR3          WUF16          LL_PWR_IsActiveFlag_WU16
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU16(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF16) == (PWR_SR3_WUF16)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 17
  * @rmtoll SR3          WUF17          LL_PWR_IsActiveFlag_WU17
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU17(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF17) == (PWR_SR3_WUF17)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 18
  * @rmtoll SR3          WUF18          LL_PWR_IsActiveFlag_WU18
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU18(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF18) == (PWR_SR3_WUF18)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 19
  * @rmtoll SR3          WUF19          LL_PWR_IsActiveFlag_WU19
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU19(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF19) == (PWR_SR3_WUF19)) ? 1UL : 0UL);
}

#if defined (PWR_CR6_EWU20)
/**
  * @brief  Get Wake-up Flag 20
  * @rmtoll SR3          WUF20          LL_PWR_IsActiveFlag_WU20
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU20(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF20) == (PWR_SR3_WUF20)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU20 */

#if defined (PWR_CR6_EWU21)
/**
  * @brief  Get Wake-up Flag 21
  * @rmtoll SR3          WUF21          LL_PWR_IsActiveFlag_WU21
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU21(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF21) == (PWR_SR3_WUF21)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU21 */

#if defined (PWR_CR6_EWU22)
/**
  * @brief  Get Wake-up Flag 22
  * @rmtoll SR3          WUF22          LL_PWR_IsActiveFlag_WU22
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU22(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF22) == (PWR_SR3_WUF22)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU22 */

#if defined (PWR_CR6_EWU23)
/**
  * @brief  Get Wake-up Flag 23
  * @rmtoll SR3          WUF23          LL_PWR_IsActiveFlag_WU23
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU23(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF23) == (PWR_SR3_WUF23)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU23 */

#if defined (PWR_CR6_EWU24)
/**
  * @brief  Get Wake-up Flag 24
  * @rmtoll SR3          WUF24          LL_PWR_IsActiveFlag_WU23
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU24(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF24) == (PWR_SR3_WUF24)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU24 */

#if defined (PWR_CR6_EWU25)
/**
  * @brief  Get Wake-up Flag 23
  * @rmtoll SR3          WUF25          LL_PWR_IsActiveFlag_WU25
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU25(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF25) == (PWR_SR3_WUF25)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU25 */

#if defined (PWR_CR6_EWU26)
/**
  * @brief  Get Wake-up Flag 26
  * @rmtoll SR3          WUF26          LL_PWR_IsActiveFlag_WU26
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU26(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF26) == (PWR_SR3_WUF26)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU26 */

#if defined (PWR_CR6_EWU27)
/**
  * @brief  Get Wake-up Flag 27
  * @rmtoll SR3          WUF27          LL_PWR_IsActiveFlag_WU27
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU27(void)
{
  return ((READ_BIT(PWR->SR3, PWR_SR3_WUF27) == (PWR_SR3_WUF27)) ? 1UL : 0UL);
}
#endif /* PWR_CR6_EWU27 */

/**
  * @brief  Get which source woken up the device after a DEEPSTOP.
  * @rmtoll SR1          WUFI           LL_PWR_GetWakeupSource\n
  *         SR1          WUFI2          LL_PWR_GetWakeupSource\n
  *         SR1          BHWF           LL_PWR_GetWakeupSource\n
  *         SR1          WBLEF          LL_PWR_GetWakeupSource\n
  *         SR1          WUF0           LL_PWR_GetWakeupSource\n
  *         SR1          WUF1           LL_PWR_GetWakeupSource\n
  *         SR1          WUF2           LL_PWR_GetWakeupSource\n
  *         SR1          WUF3           LL_PWR_GetWakeupSource\n
  *         SR1          WUF4           LL_PWR_GetWakeupSource\n
  *         SR1          WUF5           LL_PWR_GetWakeupSource\n
  *         SR1          WUF6           LL_PWR_GetWakeupSource\n
  *         SR1          WUF7           LL_PWR_GetWakeupSource\n
  *         SR1          WUF8           LL_PWR_GetWakeupSource\n
  *         SR1          WUF9           LL_PWR_GetWakeupSource\n
  *         SR1          WUF10          LL_PWR_GetWakeupSource\n
  *         SR1          WUF11          LL_PWR_GetWakeupSource\n
  *         SR3          WUF12          LL_PWR_GetWakeupSource\n
  *         SR3          WUF13          LL_PWR_GetWakeupSource\n
  *         SR3          WUF14          LL_PWR_GetWakeupSource\n
  *         SR3          WUF15          LL_PWR_GetWakeupSource\n
  *         SR3          WUF16          LL_PWR_GetWakeupSource\n
  *         SR3          WUF17          LL_PWR_GetWakeupSource\n
  *         SR3          WUF18          LL_PWR_GetWakeupSource\n
  *         SR3          WUF19          LL_PWR_GetWakeupSource\n
  *         SR3          WUF20          LL_PWR_GetWakeupSource\n
  *         SR3          WUF21          LL_PWR_GetWakeupSource\n
  *         SR3          WUF22          LL_PWR_GetWakeupSource\n
  *         SR3          WUF23          LL_PWR_GetWakeupSource\n
  *         SR3          WUF24          LL_PWR_GetWakeupSource\n
  *         SR3          WUF25          LL_PWR_GetWakeupSource\n
  *         SR3          WUF26          LL_PWR_GetWakeupSource\n
  *         SR3          WUF27          LL_PWR_GetWakeupSource
  * @retval Wakeup Source from DEEPSTOP. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_SR1_WUFI
  *         @arg @ref LL_PWR_SR1_WUFI2 (**)
  *         @arg @ref LL_PWR_SR1_BHWF
  *         @arg @ref LL_PWR_SR1_WBLEF
  *         @arg @ref LL_PWR_SR1_WUF0
  *         @arg @ref LL_PWR_SR1_WUF1
  *         @arg @ref LL_PWR_SR1_WUF2
  *         @arg @ref LL_PWR_SR1_WUF3
  *         @arg @ref LL_PWR_SR1_WUF4
  *         @arg @ref LL_PWR_SR1_WUF5
  *         @arg @ref LL_PWR_SR1_WUF6
  *         @arg @ref LL_PWR_SR1_WUF7
  *         @arg @ref LL_PWR_SR1_WUF8
  *         @arg @ref LL_PWR_SR1_WUF9
  *         @arg @ref LL_PWR_SR1_WUF10
  *         @arg @ref LL_PWR_SR1_WUF11
  *         @arg @ref LL_PWR_SR3_WUF12
  *         @arg @ref LL_PWR_SR3_WUF13
  *         @arg @ref LL_PWR_SR3_WUF14
  *         @arg @ref LL_PWR_SR3_WUF15
  *         @arg @ref LL_PWR_SR3_WUF16
  *         @arg @ref LL_PWR_SR3_WUF17
  *         @arg @ref LL_PWR_SR3_WUF18
  *         @arg @ref LL_PWR_SR3_WUF19
  *         @arg @ref LL_PWR_SR3_WUF20 (*)
  *         @arg @ref LL_PWR_SR3_WUF21 (*)
  *         @arg @ref LL_PWR_SR3_WUF22 (*)
  *         @arg @ref LL_PWR_SR3_WUF23 (*)
  *         @arg @ref LL_PWR_SR3_WUF24 (*)
  *         @arg @ref LL_PWR_SR3_WUF25 (*)
  *         @arg @ref LL_PWR_SR3_WUF26 (*)
  *         @arg @ref LL_PWR_SR3_WUF27 (*)
  *         (*) Not available on devices STM32WB05 and STM32WB09
  *         (**) Not available on devices STM32WB07
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeupSource(void)
{
  uint32_t wakeup_source;

  wakeup_source = READ_REG(PWR->SR1) & 0x0000FFFF;
  return (uint32_t)(wakeup_source | (READ_REG(PWR->SR3) << 16));
}

/**
  * @brief   Clear Wake-up Flags.
  * @rmtoll  SR1          WUFI2          LL_PWR_ClearFlag_WU\n
  *          SR1          BHWF           LL_PWR_ClearFlag_WU\n
  *          SR1          WBLEF          LL_PWR_ClearFlag_WU\n
  *          SR1          WUF0           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF1           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF2           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF3           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF4           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF5           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF6           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF7           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF8           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF9           LL_PWR_ClearFlag_WU\n
  *          SR1          WUF10          LL_PWR_ClearFlag_WU\n
  *          SR1          WUF11          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF12          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF13          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF14          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF15          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF16          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF17          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF18          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF19          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF20          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF21          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF22          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF23          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF24          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF25          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF26          LL_PWR_ClearFlag_WU\n
  *          SR3          WUF27          LL_PWR_ClearFlag_WU
  * @param  source Wakeup Source from DEEPSTOP. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_SR1_WUFI2 (**)
  *         @arg @ref LL_PWR_SR1_BHWF
  *         @arg @ref LL_PWR_SR1_WBLEF
  *         @arg @ref LL_PWR_SR1_WUF0
  *         @arg @ref LL_PWR_SR1_WUF1
  *         @arg @ref LL_PWR_SR1_WUF2
  *         @arg @ref LL_PWR_SR1_WUF3
  *         @arg @ref LL_PWR_SR1_WUF4
  *         @arg @ref LL_PWR_SR1_WUF5
  *         @arg @ref LL_PWR_SR1_WUF6
  *         @arg @ref LL_PWR_SR1_WUF7
  *         @arg @ref LL_PWR_SR1_WUF8
  *         @arg @ref LL_PWR_SR1_WUF9
  *         @arg @ref LL_PWR_SR1_WUF10
  *         @arg @ref LL_PWR_SR1_WUF11
  *         @arg @ref LL_PWR_SR3_WUF12
  *         @arg @ref LL_PWR_SR3_WUF13
  *         @arg @ref LL_PWR_SR3_WUF14
  *         @arg @ref LL_PWR_SR3_WUF15
  *         @arg @ref LL_PWR_SR3_WUF16
  *         @arg @ref LL_PWR_SR3_WUF17
  *         @arg @ref LL_PWR_SR3_WUF18
  *         @arg @ref LL_PWR_SR3_WUF19
  *         @arg @ref LL_PWR_SR3_WUF20 (*)
  *         @arg @ref LL_PWR_SR3_WUF21 (*)
  *         @arg @ref LL_PWR_SR3_WUF22 (*)
  *         @arg @ref LL_PWR_SR3_WUF23 (*)
  *         @arg @ref LL_PWR_SR3_WUF24 (*)
  *         @arg @ref LL_PWR_SR3_WUF25 (*)
  *         @arg @ref LL_PWR_SR3_WUF26 (*)
  *         @arg @ref LL_PWR_SR3_WUF27 (*)
  *         (*) Not available on devices STM32WB05 and STM32WB09
  *         (**) Not available on devices STM32WB07
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearWakeupSource(uint32_t source)
{
  WRITE_REG(PWR->SR1, (source & 0x0000FFFF));
  WRITE_REG(PWR->SR3, (source >> 16));
}

/**
  * @brief   Clear Wake-up Flag 0.
  * @rmtoll SR1          WUF0         LL_PWR_ClearFlag_WU0
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU0()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF0);
}

/**
  * @brief   Clear Wake-up Flag 1.
  * @rmtoll SR1          WUF1         LL_PWR_ClearFlag_WU1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF1);
}


/**
  * @brief   Clear Wake-up Flag 2.
  * @rmtoll SR1          WUF2         LL_PWR_ClearFlag_WU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF2);
}

/**
  * @brief   Clear Wake-up Flag 3.
  * @rmtoll SR1          WUF3         LL_PWR_ClearFlag_WU3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF3);
}

/**
  * @brief   Clear Wake-up Flag 4.
  * @rmtoll SR1          WUF4         LL_PWR_ClearFlag_WU4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF4);
}

/**
  * @brief   Clear Wake-up Flag 5.
  * @rmtoll SR1          WUF5         LL_PWR_ClearFlag_WU5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF5);
}

/**
  * @brief   Clear Wake-up Flag 6.
  * @rmtoll SR1          WUF6         LL_PWR_ClearFlag_WU6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF6);
}

/**
  * @brief   Clear Wake-up Flag 7.
  * @rmtoll SR1          WUF5         LL_PWR_ClearFlag_WU7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU7()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF7);
}

/**
  * @brief   Clear Wake-up Flag 8.
  * @rmtoll SR1          WUF5         LL_PWR_ClearFlag_WU8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU8()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF8);
}

/**
  * @brief   Clear Wake-up Flag 9.
  * @rmtoll SR1          WUF9         LL_PWR_ClearFlag_WU9
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU9()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF9);
}

/**
  * @brief   Clear Wake-up Flag 10.
  * @rmtoll SR1          WUF10         LL_PWR_ClearFlag_WU10
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU10()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF10);
}

/**
  * @brief   Clear Wake-up Flag 11.
  * @rmtoll SR1          WUF11         LL_PWR_ClearFlag_WU11
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU11()
{
  WRITE_REG(PWR->SR1, PWR_SR1_WUF11);
}

/**
  * @brief   Clear Wake-up Flag 12.
  * @rmtoll SR3          WUF12         LL_PWR_ClearFlag_WU12
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU12()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF12);
}

/**
  * @brief   Clear Wake-up Flag 13.
  * @rmtoll SR3          WUF13         LL_PWR_ClearFlag_WU13
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU13()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF13);
}

/**
  * @brief   Clear Wake-up Flag 14.
  * @rmtoll SR3          WUF14         LL_PWR_ClearFlag_WU14
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU14()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF14);
}

/**
  * @brief   Clear Wake-up Flag 15.
  * @rmtoll SR3          WUF15         LL_PWR_ClearFlag_WU15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU15()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF15);
}

/**
  * @brief   Clear Wake-up Flag 16.
  * @rmtoll SR3          WUF16         LL_PWR_ClearFlag_WU16
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU16()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF16);
}

/**
  * @brief   Clear Wake-up Flag 17.
  * @rmtoll SR3          WUF17         LL_PWR_ClearFlag_WU17
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU17()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF17);
}

/**
  * @brief   Clear Wake-up Flag 18.
  * @rmtoll SR3          WUF18         LL_PWR_ClearFlag_WU18
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU18()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF18);
}

/**
  * @brief   Clear Wake-up Flag 19.
  * @rmtoll SR3          WUF19         LL_PWR_ClearFlag_WU19
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU19()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF19);
}

#if defined(PWR_CR6_EWUP20)
/**
  * @brief   Clear Wake-up Flag 20.
  * @rmtoll SR3          WUF20         LL_PWR_ClearFlag_WU20
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU20()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF20);
}
#endif /* PWR_CR6_EWUP20 */

#if defined(PWR_CR6_EWUP21)
/**
  * @brief   Clear Wake-up Flag 21.
  * @rmtoll SR3          WUF21         LL_PWR_ClearFlag_WU21
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU21()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF21);
}
#endif /* PWR_CR6_EWUP21  */

#if defined(PWR_CR6_EWUP21)
/**
  * @brief   Clear Wake-up Flag 22.
  * @rmtoll SR3          WUF22         LL_PWR_ClearFlag_WU22
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU22()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF22);
}
#endif /* PWR_CR6_EWUP22  */

#if defined(PWR_CR6_EWUP23)
/**
  * @brief   Clear Wake-up Flag 23.
  * @rmtoll SR3          WUF23         LL_PWR_ClearFlag_WU23
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU23()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF23);
}
#endif /* PWR_CR6_EWUP23  */

#if defined(PWR_CR6_EWUP24)
/**
  * @brief   Clear Wake-up Flag 24.
  * @rmtoll SR3          WUF24         LL_PWR_ClearFlag_WU24
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU24()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF24);
}
#endif /* PWR_CR6_EWUP24  */

#if defined(PWR_CR6_EWUP25)
/**
  * @brief   Clear Wake-up Flag 25.
  * @rmtoll SR3          WUF25         LL_PWR_ClearFlag_WU25
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU25()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF25);
}
#endif /* PWR_CR6_EWUP25  */

#if defined(PWR_CR6_EWUP26)
/**
  * @brief   Clear Wake-up Flag 26.
  * @rmtoll SR3          WUF26         LL_PWR_ClearFlag_WU26
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU26()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF26);
}
#endif /* PWR_CR6_EWUP26  */

#if defined(PWR_CR6_EWUP27)
/**
  * @brief   Clear Wake-up Flag 26.
  * @rmtoll SR3          WUF27         LL_PWR_ClearFlag_WU27
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU27()
{
  WRITE_REG(PWR->SR3, PWR_SR3_WUF27);
}
#endif /* PWR_CR6_EWUP26  */

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management_Radio FLAG management for radio
  * @{
  */

/**
  * @brief  Get BLE wakeup interrupt flag
  * @rmtoll SR1          WBLEHCPUF        LL_PWR_IsActiveFlag_WBLEHCPUF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WBLEHCPUF(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WBLEHCPUF) == (PWR_SR1_WBLEHCPUF)) ? 1UL : 0UL);
}

/**
  * @brief  Get BLE wakeup interrupt flag
  * @rmtoll SR1          WBLEF        LL_PWR_IsActiveFlag_WBLEF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WBLEF(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WBLEF) == (PWR_SR1_WBLEF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear BLE HOST CPU wakeup interrupt flag
  * @rmtoll SR1          WBLEHCPUF         LL_PWR_ClearFlag_WBLEHCPU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WBLEHCPUF(void)
{
  WRITE_REG(PWR->SR1, PWR_SR1_WBLEHCPUF);
}

/**
  * @brief  Clear BLE wakeup interrupt flag
  * @rmtoll SR1          WBLEF         LL_PWR_ClearFlag_WBLEF
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WBLEF(void)
{
  WRITE_REG(PWR->SR1, PWR_SR1_WBLEF);
}

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
  * @rmtoll EXTSRR         DEEPSTOPF      LL_PWR_ClearRFWakeupFlag
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
  * @brief  Get IO BOOT value.
  * @rmtoll SR2               LL_PWR_GetIOBootVal
  * @param  IO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PA8_LATCH_POR
  *         @arg @ref LL_PWR_PA9_LATCH_POR
  *         @arg @ref LL_PWR_PA10_LATCH_POR
  *         @arg @ref LL_PWR_PA11_LATCH_POR
  *         @arg @ref LL_PWR_PB12_LATCH_POR (*)
  *         @arg @ref LL_PWR_PB13_LATCH_POR (*)
  *         @arg @ref LL_PWR_PB14_LATCH_POR (*)
  *         @arg @ref LL_PWR_PB15_LATCH_POR (*)
  *         (*) Not available on device STM32WB05
  * @retval State of pin (1 or 0).
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

#if defined(PWR_SR2_REGMS)
/**
  * @brief  Get the Main Regulator ready status.
  * @rmtoll SR2       REGMS         LL_PWR_IsActiveFlag_REGMS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGMS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGMS) == (PWR_SR2_REGMS)) ? 1UL : 0UL);
}
#endif /* PWR_SR2_REGMS */

/**
  * @brief  Indicate whether or not the low-power regulator is ready
  * @rmtoll SR2      REGLPS         LL_PWR_IsActiveFlag_REGLPS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGLPS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGLPS) == (PWR_SR2_REGLPS)) ? 1UL : 0UL);
}
/** @defgroup PWR_LL_EF_Configuration_SMPS Configuration of SMPS
  * @{
  */

/**
  * @brief  Get the SMPS ready status.
  * @rmtoll SR2      SMPSRDY      LL_PWR_IsSMPSReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSReady(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) == (PWR_SR2_SMPSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS RUN mode status.
  * @rmtoll SR2      SMPSENR         LL_PWR_IsSMPSinRUNMode
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSinRUNMode(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSENR) == (PWR_SR2_SMPSENR)) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS PRECHARGE mode status.
  * @rmtoll SR2    SMPSBYPR          LL_PWR_IsSMPSinPRECHARGEMode
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PWR_IsSMPSinPRECHARGEMode(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSBYPR) == (PWR_SR2_SMPSBYPR)) ? 1UL : 0UL);
}

/**
  * @brief  Set SMPS Mode.
  * @rmtoll CR5          NOSMPS           LL_PWR_SetSMPSMode
  * @param mode SMPS Mode. This parameter can be one of the following values:
  *        @arg @ref LL_PWR_SMPS
  *        @arg @ref LL_PWR_NO_SMPS
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, mode);
}

/**
  * @brief  Get SMPS Mode.
  * @rmtoll CR5          NOSMPS           LL_PWR_GetSMPSMode
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
  * @rmtoll CR5          SMPSFBYP           LL_PWR_SetSMPSPrechargeMode
  * @param mode SMPS in Precharge Mode. This parameter can be one of the following values:
  *        @arg @ref LL_PWR_NO_SMPS_PRECHARGE
  *        @arg @ref LL_PWR_SMPS_PRECHARGE
  * @retval None
  */
__STATIC_INLINE void  LL_PWR_SetSMPSPrechargeMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSFBYP, mode);
}

/**
  * @brief   Check if SMPS is configured in PRECHARGE Mode.
  * @rmtoll CR5          SMPSFBYP      LL_PWR_IsEnabledSMPSPrechargeMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSPrechargeMode(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_SMPSFBYP) == (PWR_CR5_SMPSFBYP)) ? 1UL : 0UL);
}

/**
  * @brief  Select OPEN Mode for SMPS during DEEPSTOP.
  * @rmtoll CR5          SMPSLPOPEN           LL_PWR_SetSMPSOpenMode
  * @param  mode SMPS Mode. This parameter can be one of the following values:
  *         @arg @ref  LL_PWR_NO_SMPS_LPOPEN
  *         @arg @ref LL_PWR_SMPS_LPOPEN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSOpenMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLPOPEN, mode);
}

/**
  * @brief  Set SMPS BOM
  * @rmtoll CR5     SMPSBOMSEL     LL_PWR_SetSMPSBOM
  *         CR5     SMPSBOMSEL     LL_PWR_SetSMPSBOM
  * @param  BOM BOM. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BOM1
  *         @arg @ref LL_PWR_SMPS_BOM2
  *         @arg @ref LL_PWR_SMPS_BOM3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSBOM(uint32_t BOM)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSBOMSEL, BOM);
}

/**
  * @brief  Get SMPS BOM
  * @rmtoll CR5     SMPSBOMSEL     LL_PWR_GetSMPSBOM
  *         CR5     SMPSBOMSEL     LL_PWR_GetSMPSBOM
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
  * @rmtoll CR5     SMPSLVL    LL_PWR_SMPS_SetOutputVoltageLevel
  * @param  OutputVoltageLevel Output Level. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V20
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V25
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V30
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V35
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V40
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V45
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V50
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V55
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V60
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V65
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V70
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V75
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V80
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V85
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V90
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V95
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SMPS_SetOutputVoltageLevel(uint32_t OutputVoltageLevel)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLVL, OutputVoltageLevel);
}

/**
  * @brief  Get SMPS Output Level
  * @rmtoll CR5      SMPSLVL    LL_PWR_SMPS_GetOutputVoltageLevel
  * @retval Output Level. This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V20
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V25
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V30
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V35
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V40
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V45
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V50
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V55
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V60
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V65
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V70
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V75
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V80
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V85
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V90
  *         @arg @ref LL_PWR_SMPS_OUTPUT_VOLTAGE_1V95
  *
  */
__STATIC_INLINE uint32_t LL_PWR_SMPS_GetOutputVoltageLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_SMPSLVL));
}

/**
  * @}
  */

/**
  * @brief  Enable GPIO pull-up state in Shutdown mode
  * @note   Some pins are not configurable for pulling in Shutdown modes.
  *         Refer to reference manual for available pins.
  * @rmtoll PUCRA        PUA0-15        LL_PWR_EnableGPIOPullUp\n
  *         PUCRB        PUB0-15        LL_PWR_EnableGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber This parameter can be one of the following values:
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
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)(GPIO + 4UL)), GPIONumber);
  SET_BIT(*((__IO uint32_t *)GPIO), GPIONumber);
}

/**
  * @brief  Disable GPIO pull-up state in Shutdown mode
  * @note   Some pins are not configurable for pulling in Shutdown modes.
  *         Refer to reference manual for available pins.
  * @rmtoll PUCRA        PUA0-15        LL_PWR_DisableGPIOPullUp\n
  *         PUCRB        PUB0-15        LL_PWR_DisableGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber This parameter can be one of the following values:
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
  * @param  GPIONumber This parameter can be a combination of the following values:
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
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  return ((READ_BIT(*((__IO uint32_t *)GPIO), GPIONumber) == (GPIONumber)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-down state in Shutdown mode
  * @note   Some pins are not configurable for pulling in Shutdown
  *         modes. Refer to reference manual for available pins
  * @rmtoll PDCRA         PDA0-15       LL_PWR_EnableGPIOPullDown\n
  *         PDCRB         PUB0-15       LL_PWR_EnableGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber This parameter can be a combination of the following values:
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
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)GPIO), GPIONumber);
  SET_BIT(*((__IO uint32_t *)(GPIO + 4UL)), GPIONumber);
}

/**
  * @brief  Disable GPIO pull-down state in Shutdown mode.
  * @note   Some pins are not configurable for pulling in Shutdown
  *         modes. Refer to reference manual for available pins.
  * @rmtoll PDCRA        PDA0-15        LL_PWR_DisableGPIOPullDown\n
  *         PDCRB        PDB0-15        LL_PWR_DisableGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  * @param  GPIONumber This parameter can be a combination of the following values:
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
  * @param  GPIONumber This parameter can be a combination of the following values:
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
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  return ((READ_BIT(*((__IO uint32_t *)(GPIO + 4UL)), GPIONumber) == (GPIONumber)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the GPIO in NO PULL configuration for port A.
  * @rmtoll PDCRA/PUCRA               LL_PWR_SetNoPullA
  * @param  GPIONumber Pins No Pull configuration. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4(*)
  *         @arg @ref LL_PWR_GPIO_BIT_5(*)
  *         @arg @ref LL_PWR_GPIO_BIT_6(*)
  *         @arg @ref LL_PWR_GPIO_BIT_7(*)
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12(*)
  *         @arg @ref LL_PWR_GPIO_BIT_13(*)
  *         @arg @ref LL_PWR_GPIO_BIT_14(*)
  *         @arg @ref LL_PWR_GPIO_BIT_15(*)
  *         (*) available only on STM32WB06 and STM32WB07 devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetNoPullA(uint32_t GPIONumber)
{
  CLEAR_BIT(PWR->PUCRA, GPIONumber);
  CLEAR_BIT(PWR->PDCRA, GPIONumber);
}

/**
  * @brief  Configure the GPIO in NO PULL configuration for port B.
  * @rmtoll PDCRB/PUCRB               LL_PWR_SetNoPullB
  * @param  GPIONumber Pins No Pull configuration. This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8(*)
  *         @arg @ref LL_PWR_GPIO_BIT_9(*)
  *         @arg @ref LL_PWR_GPIO_BIT_10(*)
  *         @arg @ref LL_PWR_GPIO_BIT_11(*)
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  *         (*) available only oon STM32WB06 and STM32WB07 devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetNoPullB(uint32_t GPIONumber)
{
  CLEAR_BIT(PWR->PUCRB, GPIONumber);
  CLEAR_BIT(PWR->PDCRB, GPIONumber);
}

#if defined(PWR_IOxCFG_IOCFG4)
/**
  * @brief  Set PA4 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG4        LL_PWR_SetPA4OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA4OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG4, mode);
}

/**
  * @brief  Get PA4 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG4          LL_PWR_GetPA4OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_RTC
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA4OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG4) >> PWR_IOxCFG_IOCFG4_Pos);
}
#endif /* PWR_IOxCFG_IOCFG4 */

#if defined(PWR_IOxCFG_IOCFG5)
/**
  * @brief  Set PA5 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG5           LL_PWR_SetPA5OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA5OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG5, mode);
}

/**
  * @brief  Get PA5 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG5           LL_PWR_GetPA5OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA5OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG5) >> PWR_IOxCFG_IOCFG5_Pos);
}
#endif /* PWR_IOxCFG_IOCFG5 */

#if defined(PWR_IOxCFG_IOCFG6)
/**
  * @brief  Set PA6 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG6           LL_PWR_SetPA6OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA6OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG6, mode);
}

/**
  * @brief  Get PA6 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG6           LL_PWR_GetPA6OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA6OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG6) >> PWR_IOxCFG_IOCFG6_Pos);
}
#endif /* PWR_IOxCFG_IOCFG6 */

#if defined(PWR_IOxCFG_IOCFG7)
/**
  * @brief  Set PA7 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG7           LL_PWR_SetPA7OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA7OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG7, mode);
}

/**
  * @brief  Get PA7 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG7           LL_PWR_GetPA7OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA7OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG7) >> PWR_IOxCFG_IOCFG7_Pos);
}
#endif /* PWR_IOxCFG_IOCFG7 */

#if defined(PWR_IOxCFG_IOCFG0)
/**
  * @brief  Set PA8 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG0           LL_PWR_SetPA8OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA8OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG0, mode);
}

/**
  * @brief  Get PA8 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG0           LL_PWR_GetPA8OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA8OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG0) >> PWR_IOxCFG_IOCFG0_Pos);
}
#endif /* PWR_IOxCFG_IOCFG0 */

#if defined(PWR_IOxCFG_IOCFG1)
/**
  * @brief  Set PA9 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG1           LL_PWR_SetPA9OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA9OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG1, mode);
}

/**
  * @brief  Get PA9 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG1           LL_PWR_GetPA9OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA9OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG1) >> PWR_IOxCFG_IOCFG1_Pos);
}
#endif /* PWR_IOxCFG_IOCFG1 */

#if defined(PWR_IOxCFG_IOCFG2)
/**
  * @brief  Set PA10 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG2           LL_PWR_SetPA10OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA10OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG2, mode);
}

/**
  * @brief  Get PA10 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG2           LL_PWR_GetPA10OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA10OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG2) >> PWR_IOxCFG_IOCFG2_Pos);
}
#endif /* PWR_IOxCFG_IOCFG2 */

#if defined(PWR_IOxCFG_IOCFG3)
/**
  * @brief  Set PA11 during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG3           LL_PWR_SetPA11OutputinDEEPSTOP
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPA11OutputinDEEPSTOP(uint32_t mode)
{
  MODIFY_REG_FIELD(PWR->IOxCFG, PWR_IOxCFG_IOCFG3, mode);
}

/**
  * @brief  Get PA11 output during DEEPSTOP mode.
  * @rmtoll IOxCFG         IOCFG3           LL_PWR_GetPA11OutputinDEEPSTOP
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_PWR_IOCFG_BYP
  *         @arg @ref LL_PWR_IOCFG_LCO
  *         @arg @ref LL_PWR_IOCFG_LOW
  *         @arg @ref LL_PWR_IOCFG_HIGH
  */
__STATIC_INLINE uint32_t LL_PWR_GetPA11OutputinDEEPSTOP(void)
{
  return (uint32_t)(READ_BIT(PWR->IOxCFG, PWR_IOxCFG_IOCFG3) >> PWR_IOxCFG_IOCFG3_Pos);
}
#endif /* PWR_IOxCFG_IOCFG3 */

/**
  * @brief  Set SMPS trimming value.
  * @rmtoll ENGTRIM               LL_PWR_SetSMPSTrim
  * @param  trim SMPS output voltage trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_SMPS_TRIM, ((trim << PWR_ENGTRIM_SMPS_TRIM_Pos) & PWR_ENGTRIM_SMPS_TRIM));
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
  * @param  trim Main Regulator voltage trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetMRTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_MR, ((trim << PWR_ENGTRIM_TRIM_MR_Pos) & PWR_ENGTRIM_TRIM_MR));
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
  * @param  trim Low Speed Internal oscillator trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetLSILPMUTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_LSI_LPMU, ((trim << PWR_ENGTRIM_TRIM_LSI_LPMU_Pos) & PWR_ENGTRIM_TRIM_LSI_LPMU));
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
  * @param  trim RF LDO trimming value
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRFDREGTrim(uint32_t trim)
{
  MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_RFDREG, ((trim << PWR_ENGTRIM_TRIM_RFDREG_Pos) & PWR_ENGTRIM_TRIM_RFDREG));
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

/** @defgroup PWR_LL_DBG_DEEPSTOP Function to setup the DEEPSTOP2 will be applied instead
  *                               of DEEPSTOP and the debugger features not lost
  * @{
  */

/**
  * @brief  Enable the DEEPSTOP2 feature, debugger feature not lost during DEEPSTOP.
  * @rmtoll DBGR      DEEPSTOP2         LL_PWR_EnableDEEPSTOP2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableDEEPSTOP2(void)
{
  SET_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2);
}

/**
  * @brief  Disable the DEEPSTOP2 feature, debugger feature lost during DEEPSTOP.
  * @rmtoll DBGR      DEEPSTOP2         LL_PWR_DisableDEEPSTOP2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDEEPSTOP2(void)
{
  CLEAR_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2);
}

/**
  * @brief  Checks if the DEEPSTOP2 feature is enabled or disabled
  * @rmtoll DBGR    DEEPSTOP2           LL_PWR_IsEnabledDEEPSTOP2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDEEPSTOP2(void)
{
  return ((READ_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2) == (PWR_DBGR_DEEPSTOP2)) ? 1UL : 0UL);
}
/**
  * @}
  */

#if defined(PWR_CR5_SMPS_PRECH_CUR_SEL)
/**
  * @brief  Select SMPS PRECHARGE limit current.
  * @rmtoll CR5       SMPS_PRECH_CUR_SEL        LL_PWR_SetSMPSPrechargeLimitCurrent
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_2_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_5
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_10
  *         @arg @ref LL_PWR_SMPS_PRECH_LIMIT_CUR_20
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSMPSPrechargeLimitCurrent(uint32_t mode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPS_PRECH_CUR_SEL, mode);
}

/**
  * @brief  Get SMPS PRECHARGE limit current selected.
  * @rmtoll CR5       SMPS_PRECH_CUR_SEL        LL_PWR_GetSMPSPrechargeLimitCurrent
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

#if defined(PWR_SDWN_WUEN_WUEN)
/**
  * @brief  Shutdown I/O Wakeup enable.
  * @rmtoll SDWN_WUEN          WUEN           LL_PWR_EnableIOWakeupSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableIOWakeupSDN(void)
{
  SET_BIT(PWR->SDWN_WUEN, PWR_SDWN_WUEN_WUEN);
}

/**
  * @brief  Shutdown I/O Wakeup disable.
  * @rmtoll SDWN_WUEN          WUEN           LL_PWR_DisableIOWakeupSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableIOWakeupSDN(void)
{
  CLEAR_BIT(PWR->SDWN_WUEN, PWR_SDWN_WUEN_WUEN);
}

/**
  * @brief  Checks if Shutdown I/O Wakeup is enabled or disabled.
  * @rmtoll SDWN_WUEN         WUEN     LL_PWR_IsEnabledIOWakeupSDN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledIOWakeupSDN(void)
{
  return ((READ_BIT(PWR->SDWN_WUEN, PWR_SDWN_WUEN_WUEN) == (PWR_SDWN_WUEN_WUEN)) ? 1UL : 0UL);
}

/**
  * @brief  Shutdown I/O Wakeup Polarity configuration.
  * @rmtoll SDWN_WUPOL          WUPOL           LL_PWR_IOWakeupPolaritySDN
  * @param  pol:
  *             - 0 : PB0 pin wakeup from shutdown on high pulse or high level detection
  *             - 1 : PB0 pin wakeup from shutdown on low pulse or low level detection
  * @retval None
  */
__STATIC_INLINE void LL_PWR_IOWakeupPolaritySDN(uint8_t pol)
{
  if (pol == 0)
  {
    CLEAR_BIT(PWR->SDWN_WUPOL, PWR_SDWN_WUPOL_WUPOL);
  }
  else
  {
    SET_BIT(PWR->SDWN_WUPOL, PWR_SDWN_WUPOL_WUPOL);
  }
}

/**
  * @brief  Checks if Shutdown I/O Wakeup from PB0 pin occurred.
  * @rmtoll SDWN_WUF         WUF     LL_PWR_IsIOWakeupSDN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsIOWakeupSDN(void)
{
  return ((READ_BIT(PWR->SDWN_WUF, PWR_SDWN_WUF_WUF) == (PWR_SDWN_WUF_WUF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear I/O Wakeup from PB0 pin occurred flag
  * @rmtoll SDWN_WUF          WUF           LL_PWR_ClearIOWakeupFlagSDN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearIOWakeupFlagSDN(void)
{
  CLEAR_BIT(PWR->SDWN_WUF, PWR_SDWN_WUF_WUF);
}
#endif /* PWR_SDWN_WUEN_WUEN */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
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

/**
  * @}
  */

#endif /* PWR */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WB0x_LL_PWR_H */
