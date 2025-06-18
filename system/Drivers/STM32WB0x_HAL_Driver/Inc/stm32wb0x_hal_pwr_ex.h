/**
  ******************************************************************************
  * @file    stm32wb0x_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extended module.
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
#ifndef STM32WB0x_HAL_PWR_EX_H
#define STM32WB0x_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal_def.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants  PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_WakeUp_Pins  PWR Wake-up pins
  * @{
  */
#if !defined(PWR_CR6_EWU20)
#define PWR_WAKEUP_CR3_ALL        (0x00000FFFU)
#define PWR_WAKEUP_CR6_ALL        (0x000000FFU << 16)
#define PWR_WAKEUP_ALL            0x00FF0FFFU               /*!< Enable all the wakeup source                   */
#define PWR_WAKEUP_PIN_RTC        PWR_CR3_EIWL              /*!< Enable wakeup on Internal event (RTC)          */
#define PWR_WAKEUP_PIN_LPUART     PWR_CR3_EIWL2             /*!< Enable wakeup on Internal event 2 (LPUART)     */
#define PWR_WAKEUP_BLEHOST        PWR_CR3_EWBLEHCPU         /*!< Enable wakeup on BLE Host CPU event            */
#define PWR_WAKEUP_BLE            PWR_CR3_EWBLE             /*!< Enable wakeup on BLE event                     */
#define PWR_WAKEUP_PA11           PWR_CR3_EWU11             /*!< Enable wakeup on PA11 I/O event                */
#define PWR_WAKEUP_PA10           PWR_CR3_EWU10             /*!< Enable wakeup on PA10 I/O event                */
#define PWR_WAKEUP_PA9            PWR_CR3_EWU9              /*!< Enable wakeup on PA9 I/O event                 */
#define PWR_WAKEUP_PA8            PWR_CR3_EWU8              /*!< Enable wakeup on PA8 I/O event                 */
#define PWR_WAKEUP_PA3            (PWR_CR6_EWU15 << 16)     /*!< Enable wakeup on PA3 I/O event                 */
#define PWR_WAKEUP_PA2            (PWR_CR6_EWU14 << 16)     /*!< Enable wakeup on PA2 I/O event                 */
#define PWR_WAKEUP_PA1            (PWR_CR6_EWU13 << 16)     /*!< Enable wakeup on PA1 I/O event                 */
#define PWR_WAKEUP_PA0            (PWR_CR6_EWU12 << 16)     /*!< Enable wakeup on PA0 I/O event                 */
#define PWR_WAKEUP_PB7            PWR_CR3_EWU7              /*!< Enable wakeup on PB7 I/O event                 */
#define PWR_WAKEUP_PB6            PWR_CR3_EWU6              /*!< Enable wakeup on PB6 I/O event                 */
#define PWR_WAKEUP_PB5            PWR_CR3_EWU5              /*!< Enable wakeup on PB5 I/O event                 */
#define PWR_WAKEUP_PB4            PWR_CR3_EWU4              /*!< Enable wakeup on PB4 I/O event                 */
#define PWR_WAKEUP_PB3            PWR_CR3_EWU3              /*!< Enable wakeup on PB3 I/O event                 */
#define PWR_WAKEUP_PB2            PWR_CR3_EWU2              /*!< Enable wakeup on PB2 I/O event                 */
#define PWR_WAKEUP_PB1            PWR_CR3_EWU1              /*!< Enable wakeup on PB1 I/O event                 */
#define PWR_WAKEUP_PB0            PWR_CR3_EWU0              /*!< Enable wakeup on PB0 I/O event                 */
#define PWR_WAKEUP_PB15           (PWR_CR6_EWU19 << 16)     /*!< Enable wakeup on PB15 I/O event                */
#define PWR_WAKEUP_PB14           (PWR_CR6_EWU18 << 16)     /*!< Enable wakeup on PB14 I/O event                */
#define PWR_WAKEUP_PB13           (PWR_CR6_EWU17 << 16)     /*!< Enable wakeup on PB13 I/O event                */
#define PWR_WAKEUP_PB12           (PWR_CR6_EWU16 << 16)     /*!< Enable wakeup on PB12 I/O event                */
#else
#define PWR_WAKEUP_CR3_ALL        0x00000FFFU
#define PWR_WAKEUP_CR6_ALL        (0x0000FFFFU << 16)
#define PWR_WAKEUP_ALL            0xFFFF0FFFU               /*!< Enable all the wakeup source                   */
#define PWR_WAKEUP_PIN_RTC        PWR_CR3_EIWL              /*!< Enable wakeup on Internal event (RTC)          */
#define PWR_WAKEUP_BLEHOST        PWR_CR3_EWBLEHCPU         /*!< Enable wakeup on BLE Host CPU event            */
#define PWR_WAKEUP_BLE            PWR_CR3_EWBLE             /*!< Enable wakeup on BLE event                     */
#define PWR_WAKEUP_PA15           (PWR_CR6_EWU27 << 16)     /*!< Enable wakeup on PA15 I/O event                */
#define PWR_WAKEUP_PA14           (PWR_CR6_EWU26 << 16)     /*!< Enable wakeup on PA14 I/O event                */
#define PWR_WAKEUP_PA13           (PWR_CR6_EWU25 << 16)     /*!< Enable wakeup on PA13 I/O event                */
#define PWR_WAKEUP_PA12           (PWR_CR6_EWU24 << 16)     /*!< Enable wakeup on PA12 I/O event                */
#define PWR_WAKEUP_PA11           PWR_CR3_EWU11             /*!< Enable wakeup on PA11 I/O event                */
#define PWR_WAKEUP_PA10           PWR_CR3_EWU10             /*!< Enable wakeup on PA10 I/O event                */
#define PWR_WAKEUP_PA9            PWR_CR3_EWU9              /*!< Enable wakeup on PA9 I/O event                 */
#define PWR_WAKEUP_PA8            PWR_CR3_EWU8              /*!< Enable wakeup on PA8 I/O event                 */
#define PWR_WAKEUP_PA7            (PWR_CR6_EWU19 << 16)     /*!< Enable wakeup on LP-PA7 I/O event              */
#define PWR_WAKEUP_PA6            (PWR_CR6_EWU18 << 16)     /*!< Enable wakeup on LP-PA6 I/O event              */
#define PWR_WAKEUP_PA5            (PWR_CR6_EWU17 << 16)     /*!< Enable wakeup on LP-PA5 I/O event              */
#define PWR_WAKEUP_PA4            (PWR_CR6_EWU16 << 16)     /*!< Enable wakeup on LP-PA4 I/O event              */
#define PWR_WAKEUP_PA3            (PWR_CR6_EWU15 << 16)     /*!< Enable wakeup on PA3 I/O event                 */
#define PWR_WAKEUP_PA2            (PWR_CR6_EWU14 << 16)     /*!< Enable wakeup on PA2 I/O event                 */
#define PWR_WAKEUP_PA1            (PWR_CR6_EWU13 << 16)     /*!< Enable wakeup on PA1 I/O event                 */
#define PWR_WAKEUP_PA0            (PWR_CR6_EWU12 << 16)     /*!< Enable wakeup on PA0 I/O event                 */
#define PWR_WAKEUP_PB11           (PWR_CR6_EWU23 << 16)     /*!< Enable wakeup on PB11 I/O event                */
#define PWR_WAKEUP_PB10           (PWR_CR6_EWU22 << 16)     /*!< Enable wakeup on PB10 I/O event                */
#define PWR_WAKEUP_PB9            (PWR_CR6_EWU21 << 16)     /*!< Enable wakeup on PB9 I/O event                 */
#define PWR_WAKEUP_PB8            (PWR_CR6_EWU20 << 16)     /*!< Enable wakeup on PB8 I/O event                 */
#define PWR_WAKEUP_PB7            PWR_CR3_EWU7              /*!< Enable wakeup on PB7 I/O event                 */
#define PWR_WAKEUP_PB6            PWR_CR3_EWU6              /*!< Enable wakeup on PB6 I/O event                 */
#define PWR_WAKEUP_PB5            PWR_CR3_EWU5              /*!< Enable wakeup on PB5 I/O event                 */
#define PWR_WAKEUP_PB4            PWR_CR3_EWU4              /*!< Enable wakeup on PB4 I/O event                 */
#define PWR_WAKEUP_PB3            PWR_CR3_EWU3              /*!< Enable wakeup on PB3 I/O event                 */
#define PWR_WAKEUP_PB2            PWR_CR3_EWU2              /*!< Enable wakeup on PB2 I/O event                 */
#define PWR_WAKEUP_PB1            PWR_CR3_EWU1              /*!< Enable wakeup on PB1 I/O event                 */
#define PWR_WAKEUP_PB0            PWR_CR3_EWU0              /*!< Enable wakeup on PB0 I/O event                 */
#endif /* !defined PWR_CR6_EWU20 */

/**
  * @}
  */

/** @defgroup PWREx_GPIO_Bit_Number GPIO bit number I/O setting in shutdown mode
  * @{
  */
#define PWR_GPIO_BIT_0   PWR_PUCRA_PA0    /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1   PWR_PUCRA_PA1    /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2   PWR_PUCRB_PB2    /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3   PWR_PUCRB_PB3    /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4   PWR_PUCRB_PB4    /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5   PWR_PUCRB_PB5    /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6   PWR_PUCRB_PB6    /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7   PWR_PUCRB_PB7    /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8   PWR_PUCRA_PA8    /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9   PWR_PUCRA_PA9    /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10  PWR_PUCRA_PA10   /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11  PWR_PUCRA_PA11   /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12  PWR_PUCRB_PB12   /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13  PWR_PUCRB_PB13   /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14  PWR_PUCRB_PB14   /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15  PWR_PUCRB_PB15   /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_Flag  PWR Status Flags
  *        Elements values convention: 0000 0000 XXXY YYYYb
  *           - Y YYYY  : Flag position in the XXX register (5 bits)
  *           - XXX  : Status register (3 bits)
  *                 - 001: SR1 register
  *                 - 010: SR2 register
  *                 - 011: SR3 register
  *                 - 100: EXTSRR register
  * @{
  */
/*--------------------------------SR1-------------------------------*/
#define PWR_FLAG_WUF0                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF0_Pos)       /*!< Wakeup event on wakeup pin PB0 */
#define PWR_FLAG_WUF1                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF1_Pos)       /*!< Wakeup event on wakeup pin PB1 */
#define PWR_FLAG_WUF2                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF2_Pos)       /*!< Wakeup event on wakeup pin PB2 */
#define PWR_FLAG_WUF3                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF3_Pos)       /*!< Wakeup event on wakeup pin PB3 */
#define PWR_FLAG_WUF4                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF4_Pos)       /*!< Wakeup event on wakeup pin PB4 */
#define PWR_FLAG_WUF5                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF5_Pos)       /*!< Wakeup event on wakeup pin PB5 */
#define PWR_FLAG_WUF6                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF6_Pos)       /*!< Wakeup event on wakeup pin PB6 */
#define PWR_FLAG_WUF7                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF7_Pos)       /*!< Wakeup event on wakeup pin PB7 */
#define PWR_FLAG_WUF8                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF8_Pos)       /*!< Wakeup event on wakeup pin PA8 */
#define PWR_FLAG_WUF9                       (PWR_FLAG_REG_SR1 | PWR_SR1_WUF9_Pos)       /*!< Wakeup event on wakeup pin PA9 */
#define PWR_FLAG_WUF10                      (PWR_FLAG_REG_SR1 | PWR_SR1_WUF10_Pos)      /*!< Wakeup event on wakeup pin PA10 */
#define PWR_FLAG_WUF11                      (PWR_FLAG_REG_SR1 | PWR_SR1_WUF11_Pos)      /*!< Wakeup event on wakeup pin PA11 */
#define PWR_FLAG_WBLEF                      (PWR_FLAG_REG_SR1 | PWR_SR1_WBLEF_Pos)      /*!< Bluetooth LE WakeUp Flag */
#define PWR_FLAG_BHWF                       (PWR_FLAG_REG_SR1 | PWR_SR1_WBLEHCPUF_Pos)  /*!< Bluetooth LE Host CPU WakeUp Flag */
#define PWR_FLAG_WUFI                       (PWR_FLAG_REG_SR1 | PWR_SR1_IWUF_Pos)       /*!< Wakeup on internal wakeup line */
#if defined(PWR_CR3_EIWL2)
#define PWR_FLAG_IWUF2                      (PWR_FLAG_REG_SR1 | PWR_SR1_IWUF2_Pos)      /*!< Wakeup on internal wakeup 2 line */
#define PWR_FLAG_SR1_ALL                    0x0000FFFFU
#else
#define PWR_FLAG_SR1_ALL                    0x0000BFFFU
#endif /* PWR_CR3_EIWL2 */

/*--------------------------------SR2-------------------------------*/
#define PWR_FLAG_SMPSBYPR                   (PWR_FLAG_REG_SR2 | PWR_SR2_SMPSBYPR_Pos)   /*!< SMPS in SMPS PRECHARGE mode */
#define PWR_FLAG_SMPSENR                    (PWR_FLAG_REG_SR2 | PWR_SR2_SMPSENR_Pos)    /*!< SMPS in RUN mode Flag */

#define PWR_FLAG_SMPSRDYF                   (PWR_FLAG_REG_SR2 | PWR_SR2_SMPSRDY_Pos)    /*!< SMPS Ready Flag */

#define PWR_FLAG_REGLPS                     (PWR_FLAG_REG_SR2 | PWR_SR2_REGLPS_Pos)     /*!< Low-power regulator start flag */
#if defined(PWR_SR2_REGMS)
#define PWR_FLAG_REGMS                      (PWR_FLAG_REG_SR2 | PWR_SR2_REGMS_Pos)      /*!< Wakeup on internal wakeup 2 line */
#endif /* PWR_SR2_REGMS */

#define PWR_FLAG_PVDO                       (PWR_FLAG_REG_SR2 | PWR_SR2_PVDO_Pos)       /*!< Power Voltage Detector output flag */

/*------------------------------SR3---------------------------*/
#define PWR_FLAG_WUF12                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF12_Pos)       /*!< Wakeup event on wakeup pin PA0 */
#define PWR_FLAG_WUF13                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF13_Pos)       /*!< Wakeup event on wakeup pin PA1 */
#define PWR_FLAG_WUF14                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF14_Pos)       /*!< Wakeup event on wakeup pin PA2 */
#define PWR_FLAG_WUF15                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF15_Pos)       /*!< Wakeup event on wakeup pin PA3 */
#define PWR_FLAG_WUF16                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF16_Pos)       /*!< Wakeup event on wakeup pin PB12 */
#define PWR_FLAG_WUF17                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF17_Pos)       /*!< Wakeup event on wakeup pin PB13 */
#define PWR_FLAG_WUF18                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF18_Pos)       /*!< Wakeup event on wakeup pin PB14 */
#define PWR_FLAG_WUF19                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF19_Pos)       /*!< Wakeup event on wakeup pin PB15 */
#if defined(PWR_CR6_EWU20)
#define PWR_FLAG_WUF20                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF20_Pos)       /*!< Wakeup event on wakeup pin 20 */
#endif /* PWR_CR6_EWU20 */
#if defined(PWR_CR6_EWU21)
#define PWR_FLAG_WUF21                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF21_Pos)       /*!< Wakeup event on wakeup pin 21 */
#endif /* PWR_CR6_EWU21 */
#if defined (PWR_CR6_EWU22)
#define PWR_FLAG_WUF22                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF22_Pos)       /*!< Wakeup event on wakeup pin 22 */
#endif /* PWR_CR6_EWU22 */
#if defined(PWR_CR6_EWU23)
#define PWR_FLAG_WUF23                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF23_Pos)       /*!< Wakeup event on wakeup pin 23 */
#endif /* PWR_CR6_EWU23 */
#if defined(PWR_CR6_EWU24)
#define PWR_FLAG_WUF24                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF24_Pos)       /*!< Wakeup event on wakeup pin 24 */
#endif /* PWR_CR6_EWU24 */
#if defined (PWR_CR6_EWU25)
#define PWR_FLAG_WUF25                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF25_Pos)       /*!< Wakeup event on wakeup pin 25 */
#endif /* PWR_CR6_EWU25 */
#if defined(PWR_CR6_EWU26)
#define PWR_FLAG_WUF26                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF26_Pos)       /*!< Wakeup event on wakeup pin 26 */
#endif /* PWR_CR6_EWU26 */
#if defined (PWR_CR6_EWU27)
#define PWR_FLAG_WUF27                      (PWR_FLAG_REG_SR3 | PWR_SR3_WUF27_Pos)       /*!< Wakeup event on wakeup pin 27 */
#endif /* PWR_CR6_EWU27 */
#if defined(PWR_CR6_EWU20)
#define PWR_FLAG_SR3_ALL                    0x0000FFFFU
#else
#define PWR_FLAG_SR3_ALL                    0x000000FFU
#endif /* PWR_CR6_EWU20 */
#define PWR_WU_FLAG_ALL                     (PWR_FLAG_SR1_ALL | PWR_FLAG_SR3_ALL)
/*------------------------------EXTSRR---------------------------*/
#define PWR_FLAG_DEEPSTOPF                  (PWR_FLAG_REG_EXTSRR | PWR_EXTSRR_DEEPSTOPF_Pos)    /*!< System DEEPTSTOP Flag */
#define PWR_FLAG_RFPHASEF                   (PWR_FLAG_REG_EXTSRR | PWR_EXTSRR_RFPHASEF_Pos)     /*!< RFPHASE Flag */
/**
  * @}
  */

/** @defgroup PWREx_PIN_Polarity PWREx Pin Polarity configuration
  * @{
  */
#define PWR_WUP_RISIEDG          0x00000000U
#define PWR_WUP_FALLEDG          0x00000001U
/**
  * @}
  */

/** @defgroup PWR_RAMRET RAM Retention enable
  * @{
  */
#define PWR_RAMRET_1    PWR_CR2_RAMRET1
#if defined(PWR_CR2_RAMRET2)
#define PWR_RAMRET_2    PWR_CR2_RAMRET2
#endif /* PWR_CR2_RAMRET2 */
#if defined(PWR_CR2_RAMRET3)
#define PWR_RAMRET_3    PWR_CR2_RAMRET3
#endif /* PWR_CR2_RAMRET2 */

/**
  * @}
  */

/** @defgroup PWREx_GPIO GPIO port
  * @{
  */
#define PWR_GPIO_A         0x00000000U      /*!< GPIO port A */
#define PWR_GPIO_B         0x00000001U      /*!< GPIO port B */
/**
  * @}
  */

/** @defgroup PWREx_PIN_Pull PWREx Pin Pull configuration
  * @{
  */
#define PWR_PIN_NO_PULL                (0x0U)
#define PWR_PIN_PULL_UP                (0x1U)
#define PWR_PIN_PULL_DOWN              (0x2U)
/**
  * @}
  */

/** @defgroup PWREx_GPIO_PullUp_Port PWR Extended GPIO Pull-Up Port
  * @{
  */
#define PWR_GPIO_PULLUP_PORT_A         (0x00U)                                 /*!< GPIO port A */
#define PWR_GPIO_PULLUP_PORT_B         (0x01U)                                 /*!< GPIO port B */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_PullDown_Port PWR Extended GPIO Pull-Down Port
  * @{
  */
#define PWR_GPIO_PULLDOWN_PORT_A       (0x00U)                                 /*!< GPIO port A */
#define PWR_GPIO_PULLDOWN_PORT_B       (0x01U)                                 /*!< GPIO port B */

/**
  * @}
  */

/** @defgroup PWREx_SMPS_OPERATING_MODES SMPS step down converter operating modes
  * @{
  */
#define PWR_SMPS_ON         0x000000000U                  /*!< SMPS step down ON */
#define PWR_SMPS_OFF        PWR_CR5_NOSMPS                /*!< SMPS step down OFF */
#define PWR_SMPS_BYPASS     PWR_SMPS_PRECHARGE         /*!< SMPS is disabled and bypassed in precharge mode */

/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_PRECHARGE_MODE SMPS PRECHARGE Mode
  * @{
  */
#define PWR_NO_SMPS_PRECHARGE    (0x000000000U)           /*!< SMPS not in pecharge mode */
#define PWR_SMPS_PRECHARGE       PWR_CR5_SMPSFBYP         /*!< SMPS is disabled and bypassed in precharge mode */
/**
  * @}
  */

/** @defgroup PWR_LL_SMPS_BOM SMPS BOM
  * @{
  */
#define PWR_SMPS_BOM1       (0x000000000U)                /*!< SMPS BOM1 1.5 uH */
#define PWR_SMPS_BOM2       PWR_CR5_SMPSBOMSEL_0          /*!< SMPS BOM2 2.2 uH */
#define PWR_SMPS_BOM3       PWR_CR5_SMPSBOMSEL_1          /*!< SMPS BOM3 10 uH  */
/**
  * @}
  */

/** @defgroup PWREx_SMPS_OUTPUT_VOLTAGE_LEVEL SMPS step down converter output voltage scaling voltage level
  * @{
  */
/* Note: SMPS voltage is trimmed during device production to control
         the actual voltage level variation from device to device. */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V20    (0x000000000U)                                             /*!< SMPS step down converter supply output voltage 1.20V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V25    (PWR_CR5_SMPSLVL_0)                                        /*!< SMPS step down converter supply output voltage 1.25V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V30    (PWR_CR5_SMPSLVL_1)                                        /*!< SMPS step down converter supply output voltage 1.30V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V35    (PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)                      /*!< SMPS step down converter supply output voltage 1.35V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V40    (PWR_CR5_SMPSLVL_2)                                        /*!< SMPS step down converter supply output voltage 1.40V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V45    (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)                      /*!< SMPS step down converter supply output voltage 1.45V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V50    (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)                      /*!< SMPS step down converter supply output voltage 1.50V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V55    (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)    /*!< SMPS step down converter supply output voltage 1.55V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V60    (PWR_CR5_SMPSLVL_3)                                        /*!< SMPS step down converter supply output voltage 1.60V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V65    (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_0)                      /*!< SMPS step down converter supply output voltage 1.65V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V70    (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1)                      /*!< SMPS step down converter supply output voltage 1.70V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V75    (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)    /*!< SMPS step down converter supply output voltage 1.75V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V80    (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2)                      /*!< SMPS step down converter supply output voltage 1.80V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V85    (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)    /*!< SMPS step down converter supply output voltage 1.85V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V90    (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)    /*!< SMPS step down converter supply output voltage 1.90V */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V95    (PWR_CR5_SMPSLVL)                                          /*!< SMPS step down converter supply output voltage 1.95V */
/**
  * @}
  */

/** @defgroup PWREx_FLAG_REG PWR status register
  * @{
  */
#define PWR_FLAG_REG_SR1         (0x20UL)                                                                         /*!< Bitfield to indicate PWR flag located in register PWR_SR1 */
#define PWR_FLAG_REG_SR2         (0x40UL)                                                                         /*!< Bitfield to indicate PWR flag located in register PWR_SR2 */
#define PWR_FLAG_REG_SR3         (0x60UL)                                                                         /*!< Bitfield to indicate PWR flag located in register PWR_SR3 */
#define PWR_FLAG_REG_EXTSRR      (0x80UL)                                                                         /*!< Bitfield to indicate PWR flag located in register PWR_EXTSRR */
#define PWR_FLAG_REG_MASK        (PWR_FLAG_REG_SR1 | PWR_FLAG_REG_SR2 | PWR_FLAG_REG_SR3 | PWR_FLAG_REG_EXTSRR)   /*!< Bitfield mask to indicate PWR flag location in PWR register */

/**
  * @}
  */
/**
  * @}
  */
/* Private define ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros --------------------------------------------------------*/
/** @defgroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#if defined(PWR_CR6_EWU20)
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PA15)    ||\
                                ((PIN) == PWR_WAKEUP_PA14)    ||\
                                ((PIN) == PWR_WAKEUP_PA13)    ||\
                                ((PIN) == PWR_WAKEUP_PA12)    ||\
                                ((PIN) == PWR_WAKEUP_PA11)    ||\
                                ((PIN) == PWR_WAKEUP_PA10)    ||\
                                ((PIN) == PWR_WAKEUP_PA9)     ||\
                                ((PIN) == PWR_WAKEUP_PA8)     ||\
                                ((PIN) == PWR_WAKEUP_PA7)     ||\
                                ((PIN) == PWR_WAKEUP_PA6)     ||\
                                ((PIN) == PWR_WAKEUP_PA5)     ||\
                                ((PIN) == PWR_WAKEUP_PA4)     ||\
                                ((PIN) == PWR_WAKEUP_PA3)     ||\
                                ((PIN) == PWR_WAKEUP_PA2)     ||\
                                ((PIN) == PWR_WAKEUP_PA1)     ||\
                                ((PIN) == PWR_WAKEUP_PA0)     ||\
                                ((PIN) == PWR_WAKEUP_PB11)    ||\
                                ((PIN) == PWR_WAKEUP_PB10)    ||\
                                ((PIN) == PWR_WAKEUP_PB9)     ||\
                                ((PIN) == PWR_WAKEUP_PB8)     ||\
                                ((PIN) == PWR_WAKEUP_PB7)     ||\
                                ((PIN) == PWR_WAKEUP_PB6)     ||\
                                ((PIN) == PWR_WAKEUP_PB5)     ||\
                                ((PIN) == PWR_WAKEUP_PB4)     ||\
                                ((PIN) == PWR_WAKEUP_PB3)     ||\
                                ((PIN) == PWR_WAKEUP_PB2)     ||\
                                ((PIN) == PWR_WAKEUP_PB1)     ||\
                                ((PIN) == PWR_WAKEUP_PB0)     ||\
                                ((PIN) == PWR_WAKEUP_CR3_ALL) ||\
                                ((PIN) == PWR_WAKEUP_CR6_ALL) ||\
                                ((PIN) == PWR_WAKEUP_ALL))
#else
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PA11)    ||\
                                ((PIN) == PWR_WAKEUP_PA10)    ||\
                                ((PIN) == PWR_WAKEUP_PA9)     ||\
                                ((PIN) == PWR_WAKEUP_PA8)     ||\
                                ((PIN) == PWR_WAKEUP_PA3)     ||\
                                ((PIN) == PWR_WAKEUP_PA2)     ||\
                                ((PIN) == PWR_WAKEUP_PA1)     ||\
                                ((PIN) == PWR_WAKEUP_PA0)     ||\
                                ((PIN) == PWR_WAKEUP_PB15)    ||\
                                ((PIN) == PWR_WAKEUP_PB14)    ||\
                                ((PIN) == PWR_WAKEUP_PB13)    ||\
                                ((PIN) == PWR_WAKEUP_PB12)    ||\
                                ((PIN) == PWR_WAKEUP_PB7)     ||\
                                ((PIN) == PWR_WAKEUP_PB6)     ||\
                                ((PIN) == PWR_WAKEUP_PB5)     ||\
                                ((PIN) == PWR_WAKEUP_PB4)     ||\
                                ((PIN) == PWR_WAKEUP_PB3)     ||\
                                ((PIN) == PWR_WAKEUP_PB2)     ||\
                                ((PIN) == PWR_WAKEUP_PB1)     ||\
                                ((PIN) == PWR_WAKEUP_PB0)     ||\
                                ((PIN) == PWR_WAKEUP_CR3_ALL) ||\
                                ((PIN) == PWR_WAKEUP_CR6_ALL) ||\
                                ((PIN) == PWR_WAKEUP_ALL))

#endif /* PWR_CR6_EWU20 */

#define IS_PWR_WAKEUP_PIN_POLARITY(POLARITY)  (((POLARITY) == PWR_WUP_RISIEDG) ||\
                                               ((POLARITY) == PWR_WUP_FALLEDG))

/* Check wake up pin pull configuration parameter */
#define IS_PWR_WAKEUP_PIN_PULL(PULL) (((PULL) == PWR_PIN_NO_PULL)    ||\
                                      ((PULL) == PWR_PIN_PULL_UP)    ||\
                                      ((PULL) == PWR_PIN_PULL_DOWN))

#define IS_PWR_GPIO_BIT_NUMBER(BIT_NUMBER) (((BIT_NUMBER) & GPIO_PIN_MASK) != (uint32_t)0x00)

#define IS_PWR_GPIO(GPIO) (((GPIO) == PWR_GPIO_A) ||\
                           ((GPIO) == PWR_GPIO_B))

#define IS_PWR_SMPS_MODE(SMPS_MODE) (((SMPS_MODE) == PWR_SMPS_ON       )    ||\
                                     ((SMPS_MODE) == PWR_SMPS_OFF      )    ||\
                                     ((SMPS_MODE) == PWR_SMPS_PRECHARGE))

#define IS_PWR_SMPS_OUTPUT_VOLTAGE(SMPS_OUTPUT_VOLTAGE) (((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V20) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V25) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V30) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V35) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V40) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V45) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V50) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V55) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V60) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V65) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V70) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V75) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V80) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V85) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V90) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V95))

#define IS_PWR_SMPS_BOM(BOM) (((BOM) == PWR_SMPS_BOM1)      ||\
                              ((BOM) == PWR_SMPS_BOM2)      ||\
                              ((BOM) == PWR_SMPS_BOM3))

/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions
  * @{
  */
/* Peripheral Control functions  **********************************************/
void              HAL_PWREx_EnableInternalWakeUpLine(void);
void              HAL_PWREx_DisableInternalWakeUpLine(void);
void              HAL_PWREx_EnableInternalWakeUpLineLpuart(void);
void              HAL_PWREx_DisableInternalWakeUpLineLpuart(void);


void              HAL_PWREx_EnableBleHostCpuWakeUp(void);
void              HAL_PWREx_DisableBleHostCpuWakeUp(void);
void              HAL_PWREx_EnableBleWakeUp(void);
void              HAL_PWREx_DisableBleWakeUp(void);

HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);

void              HAL_PWREx_EnableSRAMRetention(uint32_t banks);
void              HAL_PWREx_DisableSRAMRetention(uint32_t banks);

void              HAL_PWREx_EnableGPIORetention(void);
void              HAL_PWREx_DisableGPIORetention(void);

void              HAL_PWREx_EnableDBGRetention(void);
void              HAL_PWREx_DisableDBGRetention(void);

HAL_StatusTypeDef HAL_PWREx_ConfigSMPS(uint32_t OutputVoltage, uint32_t BOM);
void              HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode);
uint32_t          HAL_PWREx_SMPS_GetMode(void);

/* Low Power modes configuration functions ************************************/
void              HAL_PWREx_EnterSHUTDOWNMode(void);

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


#endif /* STM32WB0x_HAL_PWR_EX_H */
