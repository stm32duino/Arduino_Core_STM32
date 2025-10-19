/**
  ******************************************************************************
  * @file    stm32wl3x_hal_pwr_ex.h
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
#ifndef STM32WL3x_HAL_PWR_EX_H
#define STM32WL3x_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_def.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants  PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_GPIO_Bit_Number GPIO bit number for pull I/O setting
  * @{
  */
#define PWR_GPIO_BIT_0   (uint32_t)(1U << 0U)    /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1   (uint32_t)(1U << 1U)    /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2   (uint32_t)(1U << 2U)    /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3   (uint32_t)(1U << 3U)    /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4   (uint32_t)(1U << 4U)    /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5   (uint32_t)(1U << 5U)    /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6   (uint32_t)(1U << 6U)    /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7   (uint32_t)(1U << 7U)    /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8   (uint32_t)(1U << 8U)    /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9   (uint32_t)(1U << 9U)    /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10  (uint32_t)(1U << 10U)   /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11  (uint32_t)(1U << 11U)   /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12  (uint32_t)(1U << 12U)   /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13  (uint32_t)(1U << 13U)   /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14  (uint32_t)(1U << 14U)   /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15  (uint32_t)(1U << 15U)   /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_GPIO GPIO port
  * @{
  */
#define PWR_GPIO_A   (0x00000000U)      /*!< GPIO port A */
#define PWR_GPIO_B   (0x00000001U)      /*!< GPIO port B */
/**
  * @}
  */

/** @defgroup PWREx_SMPS_OPERATING_MODES SMPS step down converter operating modes
  * @{
  */
#define PWR_SMPS_ON                (0x000000000U)           /*!< SMPS step down ON */
#define PWR_SMPS_OFF               PWR_CR5_NOSMPS           /*!< SMPS step down OFF */
#define PWR_SMPS_BYPASS            PWR_SMPS_PRECHARGE       /*!< SMPS is disabled and bypassed in precharge mode */

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

/** @defgroup PWREx_SMPS_BOM SMPS BOM Configuration
  * @{
  */
#define PWR_SMPS_BOM1       (0x000000000U)               /*!< SMPS BOM1 1.5 uH */
#define PWR_SMPS_BOM2       PWR_CR5_SMPSBOMSEL_0         /*!< SMPS BOM2 2.2 uH */
#define PWR_SMPS_BOM3       PWR_CR5_SMPSBOMSEL_1         /*!< SMPS BOM3 10 uH  */
/**
  * @}
  */

/** @defgroup PWREx_SMPS_OUTPUT_VOLTAGE_LEVEL SMPS step down converter output voltage scaling voltage level
  * @{
  */
/* Note: SMPS voltage is trimmed during device production to control
         the actual voltage level variation from device to device. */

#define PWR_SMPS_OUTPUT_VOLTAGE_1V20  (0x00000000U )                                                               /*!< 1.20V (min VBAT = 1.20V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V30  (PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0 )                                       /*!< 1.30V (min VBAT = 1.30V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V40  (PWR_CR5_SMPSLVL_2)                                                          /*!< 1.40V (min VBAT = 1.40V) (default)  */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V50  (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)                                        /*!< 1.50V (min VBAT = 1.50V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V60  (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1)                                        /*!< 1.60V (min VBAT = 1.60V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V70  (PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)                      /*!< 1.70V (min VBAT = 1.70V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V80  (PWR_CR5_SMPSLVL_3)                                                          /*!< 1.80V (min VBAT = 1.80V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_1V90  (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_0)                                        /*!< 1.90V (min VBAT = 1.90V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_2V00  (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1)                                        /*!< 2.00V (min VBAT = 2.00V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_2V10  (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)                      /*!< 2.10V (min VBAT = 2.10V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_2V20  (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2)                                        /*!< 2.20V (min VBAT = 2.20V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_2V30  (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_0)                      /*!< 2.30V (min VBAT = 2.30V)            */
#define PWR_SMPS_OUTPUT_VOLTAGE_2V40  (PWR_CR5_SMPSLVL_3|PWR_CR5_SMPSLVL_2|PWR_CR5_SMPSLVL_1|PWR_CR5_SMPSLVL_0)    /*!< 2.40V (min VBAT = 2.40V)            */

/**
  * @}
  */

/** @defgroup PWREx_RAM_Contents_DEEPSTOP_Retention PWR Extended SRAM Contents DEEPSTOP Retention
  * @{
  */
#define PWR_RAMRET_1    (0x00000001U)    /*!< RAM1 bank retention in DEEPSOTP mode */

/**
  * @}
  */

/**
  * @}
  */
/* Private define ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros --------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_GPIO_BIT_NUMBER(BIT_NUMBER) (((BIT_NUMBER) & GPIO_PIN_MASK) != (uint32_t)0x00)

#define IS_PWR_GPIO(GPIO) (((GPIO) == PWR_GPIO_A) ||\
                           ((GPIO) == PWR_GPIO_B))

#define IS_PWR_SMPS_MODE(SMPS_MODE) (((SMPS_MODE) == PWR_SMPS_ON)         ||\
                                     ((SMPS_MODE) == PWR_SMPS_OFF)        ||\
                                     ((SMPS_MODE) == PWR_SMPS_PRECHARGE))

#define IS_PWR_SMPS_BOM(BOM) (((BOM) == PWR_SMPS_BOM1)      ||\
                              ((BOM) == PWR_SMPS_BOM2)      ||\
                              ((BOM) == PWR_SMPS_BOM3))

#define IS_PWR_SMPS_OUTPUT_VOLTAGE(SMPS_OUTPUT_VOLTAGE) (((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V20) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V30) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V40) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V50) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V60) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V70) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V80) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_1V90) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_2V00) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_2V10) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_2V20) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_2V30) ||\
                                                         ((SMPS_OUTPUT_VOLTAGE) == PWR_SMPS_OUTPUT_VOLTAGE_2V40))

/**
  * @}
  */


/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup PWREx_Exported_Functions_Group1 I/O Pull-Up Pull-Down Configuration Functions
  * @{
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);

/**
  * @}
  */
/* Peripheral Control functions  **********************************************/
void HAL_PWREx_DisableInternalWakeUpLine(uint32_t WakeUpPeripehral);
void HAL_PWREx_EnableInternalWakeUpLine(uint32_t WakeUpPeripheral, uint32_t WakeUpPolarity);
uint32_t HAL_PWREx_GetClearInternalWakeUpLine(void);

/** @addtogroup PWREx_Exported_Functions_Group2 SMPS Configuration Functions
  * @{
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSMPS(uint32_t outputVoltage, uint32_t BOM);
void              HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode);
uint32_t          HAL_PWREx_SMPS_GetMode(void);
/**
  * @}
  */
/* Low Power modes configuration functions ************************************/
void              HAL_PWREx_EnterSHUTDOWNMode(void);
void              HAL_PWREx_EnableDEEPSTOP2(void);
void              HAL_PWREx_DisableDEEPSTOP2(void);
/** @addtogroup PWREx_Exported_Functions_Group3 Memories Retention Functions
  * @{
  */
void              HAL_PWREx_EnableSRAMRetention(void);
void              HAL_PWREx_DisableSRAMRetention(void);
void              HAL_PWREx_EnableGPIORetention(void);
void              HAL_PWREx_DisableGPIORetention(void);
void              HAL_PWREx_EnableDBGRetention(void);
void              HAL_PWREx_DisableDBGRetention(void);
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

#endif /* STM32WL3x_HAL_PWR_EX_H */
