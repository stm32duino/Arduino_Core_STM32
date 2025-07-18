/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extended module.
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
#ifndef STM32WBAxx_HAL_PWR_EX_H
#define STM32WBAxx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup PWREx_Exported_Types PWR Extended Exported Types
  * @{
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_RAM_Contents_Stop_Retention PWR Extended SRAM Contents Stop Retention
  * @{
  */
/* SRAM1 pages retention defines */
#if defined(PWR_STOP2_SUPPORT) && !defined(PWR_STOP3_SUPPORT)
#define PWR_SRAM1_PAGE1_STOP_RETENTION       PWR_CR2_SRAM1PDS1                       /*!< SRAM1 page 1 retention in Stop mode */
#define PWR_SRAM1_PAGE2_STOP_RETENTION       PWR_CR2_SRAM1PDS2                       /*!< SRAM1 page 2 retention in Stop mode */
#define PWR_SRAM1_PAGE3_STOP_RETENTION       PWR_CR2_SRAM1PDS3                       /*!< SRAM1 page 3 retention in Stop mode */
#define PWR_SRAM1_PAGE4_STOP_RETENTION       PWR_CR2_SRAM1PDS4                       /*!< SRAM1 page 4 retention in Stop mode */
#define PWR_SRAM1_PAGE567_STOP_RETENTION     PWR_CR2_SRAM1PDS567                     /*!< SRAM1 page 5-6-7 retention in Stop mode */
#define PWR_SRAM1_FULL_STOP_RETENTION        (PWR_CR2_SRAM1PDS1 |PWR_CR2_SRAM1PDS2 |PWR_CR2_SRAM1PDS3 |\
                                              PWR_CR2_SRAM1PDS4 | PWR_CR2_SRAM1PDS567)
#else
#define PWR_SRAM1_FULL_STOP_RETENTION        PWR_CR2_SRAM1PDS1     /*!< SRAM1 full retention in Stop modes */
#endif /* defined(PWR_STOP2_SUPPORT) && !defined(PWR_STOP3_SUPPORT) */

/* SRAM2 pages retention defines */
#if defined(PWR_STOP3_SUPPORT)
#define PWR_SRAM2_PAGE1_STOP_RETENTION       PWR_CR2_SRAM2PDS1                        /*!< SRAM2 page1 retention in Stop modes */
#define PWR_SRAM2_PAGE2_STOP_RETENTION       PWR_CR2_SRAM2PDS2                        /*!< SRAM2 page2 retention in Stop modes */
#define PWR_SRAM2_FULL_STOP_RETENTION        (PWR_CR2_SRAM2PDS1 | PWR_CR2_SRAM2PDS2)  /*!< SRAM2 full retention in Stop modes  */
#else
#define PWR_SRAM2_FULL_STOP_RETENTION        PWR_CR2_SRAM2PDS1     /*!< SRAM2 full retention in Stop modes */
#endif /* !defined(PWR_STOP3_SUPPORT) */

/* Cache RAMs retention defines */
#define PWR_ICACHE_FULL_STOP_RETENTION       PWR_CR2_ICRAMPDS      /*!< ICACHE SRAM retention in Stop modes */
#if defined(PWR_STOP2_SUPPORT)
#if defined(USB_OTG_HS)
/* USB_OTG_HS SRAM power-down in Stop modes */
#define PWR_USB_OTG_HS_SRAM_STOP_RETENTION   PWR_CR2_PRAMPDS      /*!< USB_OTG_HS SRAM content retained in Stop modes */
#endif /* defined(USB_OTG_HS) */

/* PKA SRAM power-down in Stop modes */
#define PWR_PKA_SRAM_STOP_RETENTION          PWR_CR2_PKARAMPDS    /*!< PKA SRAM content retained in Stop modes */
#endif /* defined(PWR_STOP2_SUPPORT) */
/**
  * @}
  */


/** @defgroup PWREx_RAM_Contents_Standby_Retention PWR Extended SRAM Contents Standby Retention
  * @{
  */
#if defined(PWR_STOP2_SUPPORT) && !defined(PWR_STOP3_SUPPORT)
#define PWR_SRAM1_PAGE1_STANDBY_RETENTION       PWR_CR1_R1RSB1                       /*!< SRAM1 page 1 retention in Standby mode */
#define PWR_SRAM1_PAGE2_STANDBY_RETENTION       PWR_CR1_R1RSB2                       /*!< SRAM1 page 2 retention in Standby mode */
#define PWR_SRAM1_PAGE3_STANDBY_RETENTION       PWR_CR1_R1RSB3                       /*!< SRAM1 page 3 retention in Standby mode */
#define PWR_SRAM1_PAGE4_STANDBY_RETENTION       PWR_CR1_R1RSB4                       /*!< SRAM1 page 4 retention in Standby mode */
#define PWR_SRAM1_PAGE567_STANDBY_RETENTION     PWR_CR1_R1RSB567                     /*!< SRAM1 page 5-6-7 retention in Standby mode */
#define PWR_SRAM1_FULL_STANDBY_RETENTION        (PWR_CR1_R1RSB1 |PWR_CR1_R1RSB2 | PWR_CR1_R1RSB3 |\
                                                 PWR_CR1_R1RSB4 | PWR_CR1_R1RSB567)  /*!< SRAM1 full retention in Standby mode        */
#else
#define PWR_SRAM1_FULL_STANDBY_RETENTION        PWR_CR1_R1RSB1      /*!< SRAM1 full retention in Standby mode      */
#endif /* defined(PWR_STOP2_SUPPORT) */

#if defined(PWR_STOP3_SUPPORT)
#define PWR_SRAM2_PAGE1_STANDBY_RETENTION       PWR_CR1_R2RSB1                      /*!< SRAM2 page 1 retention in Standby mode      */
#define PWR_SRAM2_PAGE2_STANDBY_RETENTION       PWR_CR1_R2RSB2                      /*!< SRAM2 page 2 retention in Standby mode      */
#define PWR_SRAM2_FULL_STANDBY_RETENTION        (PWR_CR1_R2RSB1 |  PWR_CR1_R2RSB2)  /*!< SRAM2 full retention in Standby mode      */
#else
#define PWR_SRAM2_FULL_STANDBY_RETENTION        PWR_CR1_R2RSB1      /*!< SRAM2 full retention in Standby mode      */
#endif /* defined(PWR_STOP3_SUPPORT) */
#define PWR_RADIOSRAM_FULL_STANDBY_RETENTION    PWR_CR1_RADIORSB    /*!< 2.4GHz RADIO SRAMs (TXRX and Sequence)
                                                                         and Sleep clock retention in Standby mode */
/**
  * @}
  */

#if defined(PWR_CR3_REGSEL)
/** @defgroup PWREx_Supply_Configuration PWR Extended Supply Configuration
  * @{
  */
#define PWR_LDO_SUPPLY                      (0U)            /* LDO supply  */
#define PWR_SMPS_SUPPLY                     PWR_CR3_REGSEL  /* SMPS supply */
/**
  * @}
  */
#endif /* defined(PWR_CR3_REGSEL) */

/** @defgroup PWREx_Regulator_Voltage_Scale PWR Extended Regulator Voltage Scale
  * @{
  */
#if defined(PWR_STOP3_SUPPORT)
#define PWR_REGULATOR_VOLTAGE_SCALE1     PWR_VOSR_VOS_0     /*!< Voltage scaling range 1    */
#define PWR_REGULATOR_VOLTAGE_SCALE1_5   PWR_VOSR_VOS_1     /*!< Voltage scaling range 1.5  */
#define PWR_REGULATOR_VOLTAGE_SCALE2     (0U)               /*!< Voltage scaling range 2    */
#else
#define PWR_REGULATOR_VOLTAGE_SCALE1     PWR_VOSR_VOS       /*!< Voltage scaling range 1 */
#define PWR_REGULATOR_VOLTAGE_SCALE2     (0U)               /*!< Voltage scaling range 2 */
#endif /* defined(PWR_STOP3_SUPPORT) */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Port PWR Extended GPIO Port
  * @{
  */
#define PWR_GPIO_A (0x00U) /*!< GPIO port A */
#define PWR_GPIO_B (0x01U) /*!< GPIO port B */
#define PWR_GPIO_C (0x02U) /*!< GPIO port C */
#if defined(PWR_STOP2_SUPPORT)
#if defined(GPIOD)
#define PWR_GPIO_D (0x03U) /*!< GPIO port D */
#endif /* defined(GPIOD) */
#if defined(GPIOE)
#define PWR_GPIO_E (0x04U) /*!< GPIO port E */
#endif /* defined(GPIOE) */
#if defined(GPIOG)
#define PWR_GPIO_G (0x06U) /*!< GPIO port G */
#endif /* defined(GPIOG) */
#endif /* defined(PWR_STOP2_SUPPORT) */
#define PWR_GPIO_H (0x07U) /*!< GPIO port H */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Pin_Mask PWR Extended GPIO Pin Mask
  * @{
  */
#define PWR_GPIO_BIT_0      (0x00001U) /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1      (0x00002U) /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2      (0x00004U) /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3      (0x00008U) /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4      (0x00010U) /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5      (0x00020U) /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6      (0x00040U) /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7      (0x00080U) /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8      (0x00100U) /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9      (0x00200U) /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10     (0x00400U) /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11     (0x00800U) /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12     (0x01000U) /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13     (0x02000U) /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14     (0x04000U) /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15     (0x08000U) /*!< GPIO port I/O pin 15 */
#define PWR_GPIO_PIN_MASK   (0x0FFFFU)
/**
  * @}
  */

/** @defgroup PWREx_RADIO_Mode PWR Extended 2.4 GHz RADIO operating mode
  * @{
  */
#define PWR_RADIO_DEEPSLEEP_MODE        (0x0U)               /*!< 2.4 GHz RADIO deep sleep mode */
#define PWR_RADIO_SLEEP_MODE            PWR_RADIOSCR_MODE_0  /*!< 2.4 GHz RADIO sleep mode      */
#define PWR_RADIO_ACTIVE_MODE           PWR_RADIOSCR_MODE_1  /*!< 2.4 GHz RADIO active mode     */
/**
  * @}
  */

/** @defgroup PWREx_RADIO_PHY_Mode PWR Extended 2.4 GHz RADIO PHY operating mode
  * @{
  */
#define PWR_RADIO_PHY_SLEEP_MODE        (0x0U)                /*!< 2.4 GHz RADIO PHY sleep mode   */
#define PWR_RADIO_PHY_STANDBY_MODE      PWR_RADIOSCR_PHYMODE  /*!< 2.4 GHz RADIO PHY standby mode */
/**
  * @}
  */

/** @defgroup PWREx_RADIO_ENCODE_Mode PWR Extended 2.4 GHz RADIO encryption operating mode
  * @{
  */
#define PWR_RADIO_ENCMODE_DISABLED     (0x0U)                /*!< 2.4 GHz RADIO encryption function disabled */
#define PWR_RADIO_ENCMODE_ENABLED      PWR_RADIOSCR_ENCMODE  /*!< 2.4 GHz RADIO encryption function enabled */
/**
  * @}
  */

#if defined(PWR_RADIOSCR_REGPASEL)
/** @defgroup PWREx_Regulator_Input_Supply_Selection PWR Extended RADIO regulator input supply selection
  * @{
  */
#define PWR_RADIO_REG_VDDRFPA           (0x0U)                /*!< VDDRFPA pin selected as regulator REG_VDDHPA input supply   */
#define PWR_RADIO_REG_VDDHPA_VD11       PWR_RADIOSCR_REGPASEL
/*!< Regulator REG_VDDHPA input supply selection between VDDRFPA
     and VDD11 dependent on requested regulated output voltage   */
/**
  * @}
  */
#endif /* defined(PWR_RADIOSCR_REGPASEL) */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup PWREx_Exported_Macros PWR Extended Exported Macros
  * @{
  */

/**
  * @brief Configure the main internal regulator output voltage.
  * @note  This macro is similar to HAL_PWREx_ControlVoltageScaling() API but
  *        doesn't check whether or not VOSRDY flag is set. User may resort
  *        to __HAL_PWR_GET_FLAG() macro to check VOSRDY bit state.
  * @param  __REGULATOR__ : Specifies the regulator output voltage to achieve a
  *                         tradeoff between performance and power consumption.
  *                         This parameter can be one of the following values :
  *                         @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 : Regulator voltage output scale 1.
  *                                                                  Provides a typical output voltage at 1.2 V.
  *                                                                  It allows a system clock frequency up to 100 MHz,
  *                                                                  and is required for any 2.4 GHz RADIO transmit and
  *                                                                  receive operation.
  *                         @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 : Regulator voltage output scale 2.
  *                                                                  The system clock frequency can be up to 16 MHz.
  *                                                                  The 2.4 GHz RADIO shall not transmit nor receive.
  * @retval None.
  */
#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__)  \
  do                                                      \
  {                                                       \
    __IO uint32_t tmpreg;                                 \
    MODIFY_REG(PWR->VOSR, PWR_VOSR_VOS, (__REGULATOR__)); \
    /* Delay after an RCC peripheral clock enabling */    \
    tmpreg = READ_BIT(PWR->VOSR, PWR_VOSR_VOS);           \
    UNUSED(tmpreg);                                       \
  } while(0)
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/

/** @addtogroup PWREx_Private_Constants PWR Extended Private Constants
  * @{
  */

/* All available RAM retention in Stop mode define */
#if defined(PWR_STOP2_SUPPORT) && !defined(PWR_STOP3_SUPPORT)
#if defined(USB_OTG_HS)
#define PWR_ALL_RAM_STOP_RETENTION_MASK (PWR_SRAM1_FULL_STOP_RETENTION  | PWR_SRAM2_FULL_STOP_RETENTION  | \
                                         PWR_ICACHE_FULL_STOP_RETENTION | PWR_USB_OTG_HS_SRAM_STOP_RETENTION | \
                                         PWR_PKA_SRAM_STOP_RETENTION)
#else
#define PWR_ALL_RAM_STOP_RETENTION_MASK (PWR_SRAM1_FULL_STOP_RETENTION  | PWR_SRAM2_FULL_STOP_RETENTION  | \
                                         PWR_ICACHE_FULL_STOP_RETENTION | PWR_PKA_SRAM_STOP_RETENTION)

#endif /* defined(USB_OTG_HS) */
#else
#if defined(PWR_STOP3_SUPPORT)
#if defined (PWR_USB_SRAM_STOP_RETENTION)
#define PWR_ALL_RAM_STOP_RETENTION_MASK (PWR_SRAM1_FULL_STOP_RETENTION  | PWR_SRAM2_FULL_STOP_RETENTION | \
                                         PWR_USB_SRAM_STOP_RETENTION    | PWR_PKA_SRAM_STOP_RETENTION)
#else /* defined (PWR_USB_SRAM_STOP_RETENTION) */
#define PWR_ALL_RAM_STOP_RETENTION_MASK (PWR_SRAM1_FULL_STOP_RETENTION  | PWR_SRAM2_FULL_STOP_RETENTION | \
                                         PWR_PKA_SRAM_STOP_RETENTION)
#endif /* defined (PWR_USB_SRAM_STOP_RETENTION) */
#else
#define PWR_ALL_RAM_STOP_RETENTION_MASK (PWR_SRAM1_FULL_STOP_RETENTION | PWR_SRAM2_FULL_STOP_RETENTION  | \
                                         PWR_ICACHE_FULL_STOP_RETENTION )
#endif /* defined(PWR_STOP3_SUPPORT) */
#endif /* defined(PWR_STOP2_SUPPORT) && !defined(PWR_STOP3_SUPPORT) */
/* All available RAM retention in Standby mode define */
#define PWR_ALL_RAM_STANDBY_RETENTION_MASK (PWR_SRAM1_FULL_STANDBY_RETENTION | PWR_SRAM2_FULL_STANDBY_RETENTION)
/**
  * @}
  */

/* Private macros --------------------------------------------------------*/

/** @addtogroup PWREx_Private_Macros PWR Extended Private Macros
  * @{
  */

#if defined(PWR_CR3_REGSEL)
/* Supply selection check macro */
#define IS_PWR_SUPPLY(PWR_SOURCE)                (((PWR_SOURCE) == PWR_LDO_SUPPLY) ||\
                                                  ((PWR_SOURCE) == PWR_SMPS_SUPPLY))
#endif /* defined(PWR_CR3_REGSEL) */

/* Voltage scaling range check macro */
#if defined(PWR_STOP3_SUPPORT)
#define IS_PWR_VOLTAGE_SCALING_RANGE(RANGE)      (((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1)   ||\
                                                  ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1_5) ||\
                                                  ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE2))
#else
#define IS_PWR_VOLTAGE_SCALING_RANGE(RANGE)      (((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1)   ||\
                                                  ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE2))
#endif /* defined(PWR_STOP3_SUPPORT) */

/* GPIO port check macro */
#if defined(PWR_STOP2_SUPPORT)
#if defined(PWR_GPIO_D)
#if defined(PWR_GPIO_E) && defined(PWR_GPIO_G)
#define IS_PWR_GPIO_PORT(GPIO_PORT)              (((GPIO_PORT) == PWR_GPIO_A) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_B) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_C) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_D) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_E) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_G) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_H))
#elif defined(PWR_GPIO_E)
#define IS_PWR_GPIO_PORT(GPIO_PORT)              (((GPIO_PORT) == PWR_GPIO_A) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_B) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_C) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_D) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_E) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_H))
#elif defined(PWR_GPIO_G)
#define IS_PWR_GPIO_PORT(GPIO_PORT)              (((GPIO_PORT) == PWR_GPIO_A) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_B) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_C) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_D) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_G) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_H))
#else /* No PWR_GPIO_E and PWR_GPIO_G */
#define IS_PWR_GPIO_PORT(GPIO_PORT)              (((GPIO_PORT) == PWR_GPIO_A) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_B) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_C) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_D) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_H))
#endif /* PWR_GPIO_E */
#else /* No PWR_GPIO_D */
#define IS_PWR_GPIO_PORT(GPIO_PORT)              (((GPIO_PORT) == PWR_GPIO_A) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_B) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_C) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_H))
#endif /* PWR_GPIO_D */
#else
#define IS_PWR_GPIO_PORT(GPIO_PORT)              (((GPIO_PORT) == PWR_GPIO_A) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_B) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_C) ||\
                                                  ((GPIO_PORT) == PWR_GPIO_H))
#endif /* defined(PWR_STOP2_SUPPORT) */

/* GPIO pin mask check macro */
#define IS_PWR_GPIO_PIN_MASK(BIT_MASK)           ((((BIT_MASK) & PWR_GPIO_PIN_MASK) != 0U) &&\
                                                  ((BIT_MASK) <= PWR_GPIO_PIN_MASK))

/* SRAM1 retention in Standby mode check macro */
#if defined(PWR_STOP2_SUPPORT) && !defined(PWR_STOP3_SUPPORT)
#define IS_PWR_SRAM1_STANDBY_RETENTION(CONTENT)  (((CONTENT) == PWR_SRAM1_PAGE1_STANDBY_RETENTION)   ||\
                                                  ((CONTENT) == PWR_SRAM1_PAGE2_STANDBY_RETENTION)   ||\
                                                  ((CONTENT) == PWR_SRAM1_PAGE3_STANDBY_RETENTION)   ||\
                                                  ((CONTENT) == PWR_SRAM1_PAGE4_STANDBY_RETENTION)   ||\
                                                  ((CONTENT) == PWR_SRAM1_PAGE567_STANDBY_RETENTION) ||\
                                                  ((CONTENT) == PWR_SRAM1_FULL_STANDBY_RETENTION))
#else
#define IS_PWR_SRAM1_STANDBY_RETENTION(CONTENT)  ((CONTENT) == PWR_SRAM1_FULL_STANDBY_RETENTION)
#endif /* defined(PWR_STOP2_SUPPORT) && !defined(PWR_STOP3_SUPPORT) */

/* SRAM2 retention in Standby mode check macro */
#if defined(PWR_STOP3_SUPPORT)
#define IS_PWR_SRAM2_STANDBY_RETENTION(CONTENT)  (((CONTENT) == PWR_SRAM2_PAGE1_STANDBY_RETENTION)   ||\
                                                  ((CONTENT) == PWR_SRAM2_PAGE2_STANDBY_RETENTION)   ||\
                                                  ((CONTENT) == PWR_SRAM2_FULL_STANDBY_RETENTION))
#else
#define IS_PWR_SRAM2_STANDBY_RETENTION(CONTENT)  ((CONTENT) == PWR_SRAM2_FULL_STANDBY_RETENTION)
#endif /* defined(PWR_STOP3_SUPPORT) */

/* RADIO SRAM retention in Standby mode check macro */
#define IS_PWR_RADIOSRAM_STANDBY_RETENTION(CONTENT)  ((CONTENT) == PWR_RADIOSRAM_FULL_STANDBY_RETENTION)

/* RAMs retention in Stop mode check macro */
#if defined(PWR_STOP2_SUPPORT)
#if defined(USB_OTG_HS)
#define IS_PWR_RAM_STOP_RETENTION(RAMCONTENT)    (((RAMCONTENT) == PWR_SRAM1_PAGE1_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE2_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE3_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE4_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE567_STOP_RETENTION) ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_FULL_STOP_RETENTION)    ||\
                                                  ((RAMCONTENT) == PWR_SRAM2_FULL_STOP_RETENTION)    ||\
                                                  ((RAMCONTENT) == PWR_ICACHE_FULL_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_USB_OTG_HS_SRAM_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_PKA_SRAM_STOP_RETENTION))
#else
#if   defined(PWR_STOP3_SUPPORT)
#define IS_PWR_RAM_STOP_RETENTION(RAMCONTENT)    (((RAMCONTENT) == PWR_SRAM1_FULL_STOP_RETENTION)    ||\
                                                  ((RAMCONTENT) == PWR_SRAM2_PAGE1_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM2_PAGE2_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM2_FULL_STOP_RETENTION)    ||\
                                                  ((RAMCONTENT) == PWR_PKA_SRAM_STOP_RETENTION))
#else
#define IS_PWR_RAM_STOP_RETENTION(RAMCONTENT)    (((RAMCONTENT) == PWR_SRAM1_PAGE1_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE2_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE3_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE4_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_PAGE567_STOP_RETENTION) ||\
                                                  ((RAMCONTENT) == PWR_SRAM1_FULL_STOP_RETENTION)    ||\
                                                  ((RAMCONTENT) == PWR_SRAM2_FULL_STOP_RETENTION)    ||\
                                                  ((RAMCONTENT) == PWR_ICACHE_FULL_STOP_RETENTION)   ||\
                                                  ((RAMCONTENT) == PWR_PKA_SRAM_STOP_RETENTION))
#endif /* defined(PWR_STOP3_SUPPORT) */
#endif /* defined(USB_OTG_HS) */
#else
#define IS_PWR_RAM_STOP_RETENTION(RAMCONTENT)    (((RAMCONTENT) == PWR_SRAM1_FULL_STOP_RETENTION) ||\
                                                  ((RAMCONTENT) == PWR_SRAM2_FULL_STOP_RETENTION) ||\
                                                  ((RAMCONTENT) == PWR_ICACHE_FULL_STOP_RETENTION))
#endif /* defined(PWR_STOP2_SUPPORT) */
#if defined(PWR_STOP2_SUPPORT)
/* Vdd11 USB switch delay check macro */
#define IS_PWR_VDD11USB_SWITCH_DELAY(DELAY)      ((DELAY) <= 1023U)
#endif /* defined(PWR_STOP2_SUPPORT) */
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1 Power Supply Control Functions
  * @{
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
uint32_t          HAL_PWREx_GetVoltageRange(void);

#if defined(PWR_CR3_REGSEL)
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource);
uint32_t          HAL_PWREx_GetSupplyConfig(void);
#endif /* defined(PWR_CR3_REGSEL) */
#if defined(PWR_CR2_FPWM)
void HAL_PWREx_EnableSMPSPWM(void);
void HAL_PWREx_DisableSMPSPWM(void);
#endif /* defined(PWR_CR2_FPWM) */
void              HAL_PWREx_EnableFastSoftStart(void);
void              HAL_PWREx_DisableFastSoftStart(void);
#if defined(PWR_STOP2_SUPPORT)
#if defined(PWR_VOSR_USBPWREN)
void              HAL_PWREx_ConfigVdd11UsbSwitchDelay(uint32_t Delay);
void              HAL_PWREx_EnableVdd11USB(void);
void              HAL_PWREx_DisableVdd11USB(void);
HAL_StatusTypeDef HAL_PWREx_EnableUSBBooster(void);
HAL_StatusTypeDef HAL_PWREx_DisableUSBBooster(void);
void              HAL_PWREx_EnableUSBPWR(void);
void              HAL_PWREx_DisableUSBPWR(void);
#endif /* defined(PWR_VOSR_USBPWREN) */
#if defined(PWR_SVMCR_USV)
void              HAL_PWREx_EnableVddUSB(void);
void              HAL_PWREx_DisableVddUSB(void);
#endif /* defined(PWR_SVMCR_USV) */
#if defined(PWR_SVMCR_IO2SV)
void              HAL_PWREx_EnableVddIO2(void);
void              HAL_PWREx_DisableVddIO2(void);
#endif /* defined(PWR_SVMCR_IO2SV) */
#endif /* defined(PWR_STOP2_SUPPORT) */
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @{
  */
void HAL_PWREx_EnableUltraLowPowerMode(void);
void HAL_PWREx_DisableUltraLowPowerMode(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group4 Memories Retention Functions
  * @{
  */
void              HAL_PWREx_EnableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages);
void              HAL_PWREx_DisableSRAM2ContentStandbyRetention(void);
void              HAL_PWREx_EnableRadioSRAMClockStandbyRetention(uint32_t RadioSRAM);
void              HAL_PWREx_DisableRadioSRAMClockStandbyRetention(void);
void              HAL_PWREx_EnableSRAM1ContentStandbyRetention(uint32_t SRAM1Pages);
void              HAL_PWREx_DisableSRAM1ContentStandbyRetention(void);
void              HAL_PWREx_EnableRAMsContentStopRetention(uint32_t RAMSelection);
void              HAL_PWREx_DisableRAMsContentStopRetention(uint32_t RAMSelection);
void              HAL_PWREx_EnableFlashFastWakeUp(void);
void              HAL_PWREx_DisableFlashFastWakeUp(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group5 I/O Retention Functions
  * @{
  */
HAL_StatusTypeDef HAL_PWREx_EnableStandbyIORetention(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_DisableStandbyIORetention(uint32_t GPIO_Port, uint32_t GPIO_Pin);
uint32_t          HAL_PWREx_GetStandbyIORetentionStatus(uint32_t GPIO_Port);
HAL_StatusTypeDef HAL_PWREx_DisableStandbyRetainedIOState(uint32_t GPIO_Port, uint32_t GPIO_Pin);
#if defined(PWR_STOP2_SUPPORT)
void              HAL_PWREx_EnablePTAOutputStop2Retention(void);
void              HAL_PWREx_DisablePTAOutputStop2Retention(void);
uint32_t          HAL_PWREx_GetPTAOutputStop2RetentionState(void);
void              HAL_PWREx_ClearPTAOutputStop2RetentionState(void);
#endif /* defined(PWR_STOP2_SUPPORT) */
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group6 I/O RADIO Configuration and Status Reading Functions
  * @{
  */
uint32_t HAL_PWREx_GetRADIOOperatingMode(void);
uint32_t HAL_PWREx_GetRADIOPHYOperatingMode(void);
uint32_t HAL_PWREx_GetRADIOEncryptionOperatingMode(void);
uint32_t HAL_PWREx_GetRFVDDHPA(void);

#if defined(PWR_RADIOSCR_REGPASEL)
HAL_StatusTypeDef  HAL_PWREx_SetREGVDDHPAInputSupply(uint32_t SupplySelection);
uint32_t HAL_PWREx_GetREGVDDHPAInputSupply(void);
#endif /* defined(PWR_RADIOSCR_REGPASEL) */
#if defined(PWR_RADIOSCR_REGPABYPEN)
void HAL_PWREx_EnableREGVDDHPABypass(void);
void HAL_PWREx_DisableREGVDDHPABypass(void);
#endif /* defined(PWR_RADIOSCR_REGPABYPEN) */
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


#endif /* STM32WBAxx_HAL_PWR_EX_H */
