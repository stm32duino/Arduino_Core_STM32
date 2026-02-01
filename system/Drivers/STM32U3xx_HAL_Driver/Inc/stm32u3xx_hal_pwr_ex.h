/**
  ******************************************************************************
  * @file    stm32u3xx_hal_pwr_ex.h
  * @author  GPM Application Team
  * @brief   Header file of PWR HAL Extended module.
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
#ifndef STM32U3xx_HAL_PWR_EX_H
#define STM32U3xx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup PWREx_Exported_Types PWR Extended Exported Types
  * @{
  */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_RAM_PowerDown PWR Extended SRAM Power Down
  * @{
  */
#define PWR_SRAM1_POWERDOWN            PWR_CR1_SRAM1PD                         /*!< SRAM1 power down */
#define PWR_SRAM2_POWERDOWN            PWR_CR1_SRAM2PD                         /*!< SRAM2 power down */
#if defined(RAMCFG_SRAM3)
#define PWR_SRAM3_POWERDOWN            PWR_CR1_SRAM3PD                         /*!< SRAM3 power down */
#define PWR_SRAM4_POWERDOWN            PWR_CR1_SRAM4PD                         /*!< SRAM4 power down */
#endif /* RAMCFG_SRAM3 */
/**
  * @}
  */

/** @defgroup PWREx_RAM_Contents_Stop_Retention PWR Extended SRAM Contents Stop Retention
  * @{
  */
/* SRAM1 pages retention defines */
#define PWR_SRAM1_PAGE1_STOP_RETENTION PWR_CR2_SRAM1PDS1  /*!< SRAM1 page 1 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM1_PAGE2_STOP_RETENTION PWR_CR2_SRAM1PDS2  /*!< SRAM1 page 2 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM1_PAGE3_STOP_RETENTION PWR_CR2_SRAM1PDS3  /*!< SRAM1 page 3 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM1_PAGE4_STOP_RETENTION PWR_CR2_SRAM1PDS4  /*!< SRAM1 page 4 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM1_PAGE5_STOP_RETENTION PWR_CR2_SRAM1PDS5  /*!< SRAM1 page 5 retention in Stop modes (Stop 0, 1, 2, 3) */
#if defined(PWR_CR2_SRAM1PDS6)
#define PWR_SRAM1_PAGE6_STOP_RETENTION PWR_CR2_SRAM1PDS6  /*!< SRAM1 page 6 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM1_PAGE7_STOP_RETENTION PWR_CR2_SRAM1PDS7  /*!< SRAM1 page 7 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM1_FULL_STOP_RETENTION  (PWR_CR2_SRAM1PDS1 | PWR_CR2_SRAM1PDS2 | PWR_CR2_SRAM1PDS3 | PWR_CR2_SRAM1PDS4 |\
                                        PWR_CR2_SRAM1PDS5 | PWR_CR2_SRAM1PDS6 | PWR_CR2_SRAM1PDS7)
/*!< SRAM1 full retention in Stop modes (Stop 0, 1, 2, 3)  */
#else
#define PWR_SRAM1_FULL_STOP_RETENTION  (PWR_CR2_SRAM1PDS1 | PWR_CR2_SRAM1PDS2 | PWR_CR2_SRAM1PDS3 | PWR_CR2_SRAM1PDS4 |\
                                        PWR_CR2_SRAM1PDS5)
/*!< SRAM1 full retention in Stop modes (Stop 0, 1, 2, 3)  */
#endif /* PWR_CR2_SRAM1PDS6 */

/* SRAM2 pages retention defines */
#define PWR_SRAM2_PAGE1_STOP_RETENTION PWR_CR2_SRAM2PDS1  /*!< SRAM2 page 1 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM2_PAGE2_STOP_RETENTION PWR_CR2_SRAM2PDS2  /*!< SRAM2 page 2 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM2_PAGE3_STOP_RETENTION PWR_CR2_SRAM2PDS3  /*!< SRAM2 page 3 retention in Stop modes (Stop 0, 1, 2, 3) */
#define PWR_SRAM2_FULL_STOP_RETENTION  (PWR_CR2_SRAM2PDS1 | PWR_CR2_SRAM2PDS2 | PWR_CR2_SRAM2PDS3)
/*!< SRAM2 full retention in Stop modes (Stop 0, 1, 2, 3)   */

#if defined(RAMCFG_SRAM3)
/* SRAM3 pages retention defines */
#define PWR_SRAM3_PAGE1_STOP_RETENTION PWR_CR2_SRAM3PDS1 /*!< SRAM3 page 1 retention in Stop modes (Stop 0, 1, 2, 3)  */
#define PWR_SRAM3_PAGE2_STOP_RETENTION PWR_CR2_SRAM3PDS2 /*!< SRAM3 page 2 retention in Stop modes (Stop 0, 1, 2, 3)  */
#define PWR_SRAM3_PAGE3_STOP_RETENTION PWR_CR2_SRAM3PDS3 /*!< SRAM3 page 3 retention in Stop modes (Stop 0, 1, 2, 3)  */
#define PWR_SRAM3_PAGE4_STOP_RETENTION PWR_CR2_SRAM3PDS4 /*!< SRAM3 page 4 retention in Stop modes (Stop 0, 1, 2, 3)  */
#define PWR_SRAM3_PAGE5_STOP_RETENTION PWR_CR2_SRAM3PDS5 /*!< SRAM3 page 5 retention in Stop modes (Stop 0, 1, 2, 3)  */
#define PWR_SRAM3_FULL_STOP_RETENTION  (PWR_CR2_SRAM1PDS1 | PWR_CR2_SRAM1PDS2 | PWR_CR2_SRAM1PDS3 | PWR_CR2_SRAM1PDS4 |\
                                        PWR_CR2_SRAM1PDS5)
/*!< SRAM3 full retention in Stop modes (Stop 0, 1, 2, 3)  */

/* SRAM4 pages retention defines */
#define PWR_SRAM4_FULL_STOP_RETENTION  PWR_CR2_SRAM4PDS    /*!< SRAM4 full retention in Stop modes (Stop 0, 1, 2, 3)  */
#endif /* defined(RAMCFG_SRAM3) */

/* I-Cache SRAM retention defines */
#define PWR_ICACHE_STOP_RETENTION      PWR_CR2_ICRAMPDS    /*!< ICACHE SRAM retention in Stop modes (Stop 0, 1, 2, 3) */

/* FDCAN & USB SRAM retention defines */
#define PWR_FDCAN_USB_STOP_RETENTION   PWR_CR2_PRAMPDS     /*!< FDCAN & USB SRAM retention in Stop modes
                                                                (Stop 0, 1, 2, 3) */

/* PKA SRAM retention defines */
#define PWR_PKA_STOP_RETENTION         PWR_CR2_PKARAMPDS   /*!< PKA SRAM retention in Stop modes (Stop 0, 1, 2, 3) */
/**
  * @}
  */

/** @defgroup PWREx_RAM_Contents_Standby_Retention PWR Extended SRAM Contents Standby Retention
  * @{
  */
#define PWR_SRAM2_PAGE1_STANDBY_RETENTION PWR_CR1_RRSB1  /*!< SRAM2 page 1 retention in Standby mode */
#define PWR_SRAM2_PAGE2_STANDBY_RETENTION PWR_CR1_RRSB2  /*!< SRAM2 page 2 retention in Standby mode */
#define PWR_SRAM2_PAGE3_STANDBY_RETENTION PWR_CR1_RRSB3  /*!< SRAM2 page 3 retention in Standby mode */
#define PWR_SRAM2_FULL_STANDBY_RETENTION  (PWR_CR1_RRSB1 |PWR_CR1_RRSB2  |PWR_CR1_RRSB3 )
/*!< SRAM2 full retention in Standby mode   */
/**
  * @}
  */

/** @defgroup PWREx_Supply_Configuration PWR Extended Supply Configuration
  * @{
  */
#define PWR_LDO_SUPPLY                 (0U)             /*!< LDO supply  */
#define PWR_SMPS_SUPPLY                PWR_CR3_REGSEL   /*!< SMPS supply */
/**
  * @}
  */

/** @defgroup PWREx_Regulator_Voltage_Scale PWR Extended Regulator Voltage Scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE1   PWR_VOSR_R1EN    /*!< Voltage scaling range 1 */
#define PWR_REGULATOR_VOLTAGE_SCALE2   PWR_VOSR_R2EN    /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging_Selection PWR Extended Battery Charging Resistor Selection
  * @{
  */
#define PWR_BATTERY_CHARGING_RESISTOR_5   (0U)          /*!< VBAT charging through a 5 kOhms resistor   */
#define PWR_BATTERY_CHARGING_RESISTOR_1_5 PWR_BDCR_VBRS /*!< VBAT charging through a 1.5 kOhms resistor */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Port PWR Extended GPIO Port
  * @{
  */
#define PWR_GPIO_A                     (0U)                                    /*!< GPIO port A */
#define PWR_GPIO_B                     (1U)                                    /*!< GPIO port B */
#define PWR_GPIO_C                     (2U)                                    /*!< GPIO port C */
#define PWR_GPIO_D                     (3U)                                    /*!< GPIO port D */
#define PWR_GPIO_E                     (4U)                                    /*!< GPIO port E */
#if defined(RAMCFG_SRAM3)
#define PWR_GPIO_F                     (5U)                                    /*!< GPIO port F */
#endif /* RAMCFG_SRAM3 */
#if defined(PWR_PDCRG_PD15)
#define PWR_GPIO_G                     (6U)                                    /*!< GPIO port G */
#endif /* PWR_PDCRG_PD15 */
#define PWR_GPIO_H                     (7U)                                    /*!< GPIO port H */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Pin_Mask PWR Extended GPIO Pin Mask
  * @{
  */
#define PWR_GPIO_BIT_0                 (0x00001U)                              /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1                 (0x00002U)                              /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2                 (0x00004U)                              /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3                 (0x00008U)                              /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4                 (0x00010U)                              /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5                 (0x00020U)                              /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6                 (0x00040U)                              /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7                 (0x00080U)                              /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8                 (0x00100U)                              /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9                 (0x00200U)                              /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10                (0x00400U)                              /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11                (0x00800U)                              /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12                (0x01000U)                              /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13                (0x02000U)                              /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14                (0x04000U)                              /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15                (0x08000U)                              /*!< GPIO port I/O pin 15 */
#define PWR_GPIO_PIN_MASK              (0x0FFFFU)
/**
  * @}
  */

/** @defgroup PWREx_I3C_PULLUP_GPIO PWR Extended I3C Pull-up Configuration
  * @{
  */
#define PWR_I3CPU_PA1                  PWR_I3CPUCR1_PA1_I3CPU                            /*!< I3C pull-up on PA1  */
#define PWR_I3CPU_PA6                  PWR_I3CPUCR1_PA6_I3CPU                            /*!< I3C pull-up on PA6  */
#define PWR_I3CPU_PA7                  PWR_I3CPUCR1_PA7_I3CPU                            /*!< I3C pull-up on PA7  */
#define PWR_I3CPU_PB2                  PWR_I3CPUCR1_PB2_I3CPU                            /*!< I3C pull-up on PB2  */
#define PWR_I3CPU_PB6                  PWR_I3CPUCR1_PB6_I3CPU                            /*!< I3C pull-up on PB6  */
#if defined(RAMCFG_SRAM3)
#define PWR_I3CPU_PB7                  PWR_I3CPUCR1_PB7_I3CPU                            /*!< I3C pull-up on PB7  */
#endif /* RAMCFG_SRAM3 */
#if defined(PWR_I3CPUCR1_PB8_I3CPU)
#define PWR_I3CPU_PB8                  PWR_I3CPUCR1_PB8_I3CPU                            /*!< I3C pull-up on PB8  */
#define PWR_I3CPU_PB9                  PWR_I3CPUCR1_PB9_I3CPU                            /*!< I3C pull-up on PB9  */
#endif /* PWR_I3CPUCR1_PB8_I3CPU */
#define PWR_I3CPU_PB10                 PWR_I3CPUCR1_PB10_I3CPU                           /*!< I3C pull-up on PB10 */
#define PWR_I3CPU_PB12                 PWR_I3CPUCR1_PB12_I3CPU                           /*!< I3C pull-up on PB12 */
#define PWR_I3CPU_PB13                 PWR_I3CPUCR1_PB13_I3CPU                           /*!< I3C pull-up on PB13 */
#if defined(PWR_I3CPUCR1_PB8_I3CPU)
#define PWR_I3CPU_PB14                 PWR_I3CPUCR1_PB14_I3CPU                           /*!< I3C pull-up on PB14 */
#define PWR_I3CPU_PC0                  (PWR_I3CPUCR2_PC0_I3CPU  << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PC0  */
#endif /* PWR_I3CPUCR1_PB8_I3CPU */
#define PWR_I3CPU_PC1                  (PWR_I3CPUCR2_PC1_I3CPU  << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PC1  */
#define PWR_I3CPU_PD12                 (PWR_I3CPUCR2_PD12_I3CPU << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PD12 */
#define PWR_I3CPU_PD13                 (PWR_I3CPUCR2_PD13_I3CPU << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PD13 */
#if defined(PWR_I3CPUCR1_PB8_I3CPU)
#define PWR_I3CPU_PG7                  (PWR_I3CPUCR2_PG7_I3CPU  << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PG7  */
#define PWR_I3CPU_PG8                  (PWR_I3CPUCR2_PG8_I3CPU  << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PG8  */
#define PWR_I3CPU_PG13                 (PWR_I3CPUCR2_PG13_I3CPU << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PG13 */
#define PWR_I3CPU_PG14                 (PWR_I3CPUCR2_PG14_I3CPU << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PG14 */
#endif /* PWR_I3CPUCR1_PB8_I3CPU */
#define PWR_I3CPU_PH3                  (PWR_I3CPUCR2_PH3_I3CPU  << PWR_I3CUPCR2_OFFSET)  /*!< I3C pull-up on PH3  */

#if defined(RAMCFG_SRAM3)
#define PWR_I3CPUCR_ALL                (PWR_I3CPU_PA1  | PWR_I3CPU_PA6  | PWR_I3CPU_PA7  | PWR_I3CPU_PB2  |\
                                        PWR_I3CPU_PB6  | PWR_I3CPU_PB7  | PWR_I3CPU_PB8  | PWR_I3CPU_PB9  |\
                                        PWR_I3CPU_PB10 | PWR_I3CPU_PB12 | PWR_I3CPU_PB13 | PWR_I3CPU_PB14 |\
                                        PWR_I3CPU_PC0  | PWR_I3CPU_PC1  | PWR_I3CPU_PD12 | PWR_I3CPU_PD13 |\
                                        PWR_I3CPU_PG7  | PWR_I3CPU_PG8  | PWR_I3CPU_PG13 | PWR_I3CPU_PG14 |\
                                        PWR_I3CPU_PH3)
#elif defined(PWR_I3CPUCR1_PB8_I3CPU)
#define PWR_I3CPUCR_ALL                (PWR_I3CPU_PA1  | PWR_I3CPU_PA6  | PWR_I3CPU_PA7  | PWR_I3CPU_PB2  |\
                                        PWR_I3CPU_PB6  | PWR_I3CPU_PB8  | PWR_I3CPU_PB9  | PWR_I3CPU_PB10 |\
                                        PWR_I3CPU_PB12 | PWR_I3CPU_PB13 | PWR_I3CPU_PB14 | PWR_I3CPU_PC0  |\
                                        PWR_I3CPU_PC1  | PWR_I3CPU_PD12 | PWR_I3CPU_PD13 | PWR_I3CPU_PG7  |\
                                        PWR_I3CPU_PG8  | PWR_I3CPU_PG13 | PWR_I3CPU_PG14 | PWR_I3CPU_PH3)
#else
#define PWR_I3CPUCR_ALL                (PWR_I3CPU_PA1  | PWR_I3CPU_PA6  | PWR_I3CPU_PA7  | PWR_I3CPU_PB2  |\
                                        PWR_I3CPU_PB6  | PWR_I3CPU_PB10 | PWR_I3CPU_PB12 | PWR_I3CPU_PB13 |\
                                        PWR_I3CPU_PC1  | PWR_I3CPU_PD12 | PWR_I3CPU_PD13 | PWR_I3CPU_PH3)
#endif /* defined(RAMCFG_SRAM3)*/
/*!<  I3C pull-up all */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWREx_Exported_Macros PWR Extended Exported Macros
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @addtogroup PWREx_Private_Constants PWR Extended Private Constants
  * @{
  */

/* All available RAM retention in Standby mode define */
#define PWR_ALL_RAM_STANDBY_RETENTION_MASK (PWR_SRAM2_FULL_STANDBY_RETENTION)

/* Offset for I3C Pull-Up Configuration */
#define PWR_I3CUPCR2_OFFSET            (16U)
/**
  * @}
  */

/* Private macros --------------------------------------------------------*/

/** @addtogroup PWREx_Private_Macros PWR Extended Private Macros
  * @{
  */
/* Supply selection check macro */
#define IS_PWR_SUPPLY(__PWR_SOURCE__)            (((__PWR_SOURCE__) == PWR_LDO_SUPPLY) ||\
                                                  ((__PWR_SOURCE__) == PWR_SMPS_SUPPLY))

/* Voltage scaling range check macro */
#define IS_PWR_VOLTAGE_SCALING_RANGE(__RANGE__)  (((__RANGE__) == PWR_REGULATOR_VOLTAGE_SCALE1) ||\
                                                  ((__RANGE__) == PWR_REGULATOR_VOLTAGE_SCALE2))

/* Battery charging resistor selection check macro */
#define IS_PWR_BATTERY_RESISTOR_SELECT(__RESISTOR__) (((__RESISTOR__) == PWR_BATTERY_CHARGING_RESISTOR_5) ||\
                                                      ((__RESISTOR__) == PWR_BATTERY_CHARGING_RESISTOR_1_5))

/* GPIO port check macro */
#if defined(RAMCFG_SRAM3)
#define IS_PWR_GPIO_PORT(__GPIO_PORT__)          (((__GPIO_PORT__) == PWR_GPIO_A) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_B) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_C) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_D) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_E) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_F) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_G) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_H))
#else
#if defined(PWR_GPIO_G)
#define IS_PWR_GPIO_PORT(__GPIO_PORT__)          (((__GPIO_PORT__) == PWR_GPIO_A) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_B) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_C) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_D) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_E) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_G) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_H))
#else
#define IS_PWR_GPIO_PORT(__GPIO_PORT__)          (((__GPIO_PORT__) == PWR_GPIO_A) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_B) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_C) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_D) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_E) ||\
                                                  ((__GPIO_PORT__) == PWR_GPIO_H))
#endif /* PWR_GPIO_G */
#endif /* defined(RAMCFG_SRAM3) */

/* GPIO pin mask check macro */
#define IS_PWR_GPIO_PIN_MASK(__BIT_MASK__)       ((((__BIT_MASK__) & PWR_GPIO_PIN_MASK) != 0U) &&\
                                                  ((__BIT_MASK__) <= PWR_GPIO_PIN_MASK))

/* RAMs power down check macro */
#if defined(RAMCFG_SRAM3)
#define IS_PWR_RAM_POWERDOWN(__RAM__)            (((__RAM__) == PWR_SRAM1_POWERDOWN) ||\
                                                  ((__RAM__) == PWR_SRAM2_POWERDOWN) ||\
                                                  ((__RAM__) == PWR_SRAM3_POWERDOWN) ||\
                                                  ((__RAM__) == PWR_SRAM4_POWERDOWN))
#else
#define IS_PWR_RAM_POWERDOWN(__RAM__)            (((__RAM__) == PWR_SRAM1_POWERDOWN) ||\
                                                  ((__RAM__) == PWR_SRAM2_POWERDOWN))
#endif /* RAMCFG_SRAM3 */

/* RAMs retention in Stop mode check macro */
#if defined(RAMCFG_SRAM3)
#define IS_PWR_RAM_STOP_RETENTION(__RAM__)       (((__RAM__) == PWR_SRAM1_PAGE1_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE2_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE3_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE4_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE5_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE6_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE7_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE1_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE2_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE3_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_SRAM3_PAGE1_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM3_PAGE2_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM3_PAGE3_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM3_PAGE4_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM3_PAGE5_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM3_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_SRAM4_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_ICACHE_STOP_RETENTION)      ||\
                                                  ((__RAM__) == PWR_FDCAN_USB_STOP_RETENTION)   ||\
                                                  ((__RAM__) == PWR_PKA_STOP_RETENTION))
#elif defined(PWR_SRAM1_PAGE6_STOP_RETENTION)
#define IS_PWR_RAM_STOP_RETENTION(__RAM__)       (((__RAM__) == PWR_SRAM1_PAGE1_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE2_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE3_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE4_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE5_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE6_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE7_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE1_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE2_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE3_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_ICACHE_STOP_RETENTION)      ||\
                                                  ((__RAM__) == PWR_FDCAN_USB_STOP_RETENTION)   ||\
                                                  ((__RAM__) == PWR_PKA_STOP_RETENTION))
#else
#define IS_PWR_RAM_STOP_RETENTION(__RAM__)       (((__RAM__) == PWR_SRAM1_PAGE1_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE2_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE3_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE4_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_PAGE5_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM1_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE1_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE2_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_PAGE3_STOP_RETENTION) ||\
                                                  ((__RAM__) == PWR_SRAM2_FULL_STOP_RETENTION)  ||\
                                                  ((__RAM__) == PWR_ICACHE_STOP_RETENTION)      ||\
                                                  ((__RAM__) == PWR_FDCAN_USB_STOP_RETENTION)   ||\
                                                  ((__RAM__) == PWR_PKA_STOP_RETENTION))
#endif /* RAMCFG_SRAM3 */

/* SRAM2 retention in Standby mode check macro */
#define IS_PWR_SRAM2_STANDBY_RETENTION(__PAGE__) (((__PAGE__) == PWR_SRAM2_PAGE1_STANDBY_RETENTION) ||\
                                                  ((__PAGE__) == PWR_SRAM2_PAGE2_STANDBY_RETENTION) ||\
                                                  ((__PAGE__) == PWR_SRAM2_PAGE3_STANDBY_RETENTION) ||\
                                                  ((__PAGE__) == PWR_SRAM2_FULL_STANDBY_RETENTION))

/* I3C Pull-up configuration check macro */
#if defined(PWR_I3CPU_PB7)
#define  IS_PWR_I3C_PULLUP_GPIO(__GPIO__)        (((__GPIO__) == PWR_I3CPU_PA1)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PA6)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PA7)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB2)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB6)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB7)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB8)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB9)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB10) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB12) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB14) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PC0)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PC1)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PD12) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PD13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG7)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG8)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG14) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PH3)  ||\
                                                  ((__GPIO__) == PWR_I3CPUCR_ALL))
#elif defined(PWR_I3CPU_PB8)
#define  IS_PWR_I3C_PULLUP_GPIO(__GPIO__)        (((__GPIO__) == PWR_I3CPU_PA1)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PA6)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PA7)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB2)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB6)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB8)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB9)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB10) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB12) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB14) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PC0)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PC1)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PD12) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PD13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG7)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG8)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PG14) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PH3)  ||\
                                                  ((__GPIO__) == PWR_I3CPUCR_ALL))
#else
#define  IS_PWR_I3C_PULLUP_GPIO(__GPIO__)        (((__GPIO__) == PWR_I3CPU_PA1)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PA6)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PA7)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB2)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB6)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB10) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB12) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PB13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PC1)  ||\
                                                  ((__GPIO__) == PWR_I3CPU_PD12) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PD13) ||\
                                                  ((__GPIO__) == PWR_I3CPU_PH3)  ||\
                                                  ((__GPIO__) == PWR_I3CPUCR_ALL))
#endif  /* defined(PWR_I3CPU_PB7) */
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

void              HAL_PWREx_EnableVddUSB(void);
void              HAL_PWREx_DisableVddUSB(void);
#if defined(PWR_SVMCR_IO2SV)
void              HAL_PWREx_EnableVddIO2(void);
void              HAL_PWREx_DisableVddIO2(void);
#endif /* PWR_SVMCR_IO2SV */
void              HAL_PWREx_EnableVddA(void);
void              HAL_PWREx_DisableVddA(void);

HAL_StatusTypeDef HAL_PWREx_EnableEpodBooster(void);
HAL_StatusTypeDef HAL_PWREx_DisableEpodBooster(void);

HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource);
uint32_t          HAL_PWREx_GetSupplyConfig(void);
void              HAL_PWREx_EnableFastSoftStart(void);
void              HAL_PWREx_DisableFastSoftStart(void);
void              HAL_PWREx_EnableBatteryCharging(uint32_t ResistorValue);
void              HAL_PWREx_DisableBatteryCharging(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @{
  */
void HAL_PWREx_EnterSHUTDOWNMode(void);
void HAL_PWREx_EnableUltraLowPowerMode(void);
void HAL_PWREx_DisableUltraLowPowerMode(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group3 Memories Retention Functions
  * @{
  */
void              HAL_PWREx_EnableRAMsPowerDown(uint32_t RAMSelection);
void              HAL_PWREx_DisableRAMsPowerDown(uint32_t RAMSelection);
void              HAL_PWREx_EnableRAMsContentStopRetention(uint32_t RAMSelection);
void              HAL_PWREx_DisableRAMsContentStopRetention(uint32_t RAMSelection);
void              HAL_PWREx_EnableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages);
void              HAL_PWREx_DisableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages);
void              HAL_PWREx_EnableFlashFastWakeUp(void);
void              HAL_PWREx_DisableFlashFastWakeUp(void);
void              HAL_PWREx_EnableSRAMFastWakeUp(void);
void              HAL_PWREx_DisableSRAMFastWakeUp(void);

/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group4 I/O Pull-Up Pull-Down Configuration Functions
  * @{
  */
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group5 I3C Pull-Up Configuration Functions
  * @{
  */
HAL_StatusTypeDef HAL_PWREx_EnableI3CPullUp(uint32_t Gpio);
HAL_StatusTypeDef HAL_PWREx_DisableI3CPullUp(uint32_t Gpio);
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

#endif /* STM32U3xx_HAL_PWR_EX_H */
