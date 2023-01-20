/**
  ******************************************************************************
  * @file    stm32c0xx_hal_pwr_ex.h
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
#ifndef STM32C0xx_HAL_PWR_EX_H
#define STM32C0xx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal_def.h"

/** @addtogroup STM32C0xx_HAL_Driver
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

/** @defgroup PWREx_GPIO_Pin_Mask PWR Extended GPIO Pin Mask
  * @{
  */
#define PWR_GPIO_BIT_0      (0x0001U)     /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1      (0x0002U)     /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2      (0x0004U)     /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3      (0x0008U)     /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4      (0x0010U)     /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5      (0x0020U)     /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6      (0x0040U)     /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7      (0x0080U)     /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8      (0x0100U)     /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9      (0x0200U)     /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10     (0x0400U)     /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11     (0x0800U)     /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12     (0x1000U)     /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13     (0x2000U)     /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14     (0x4000U)     /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15     (0x8000U)     /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_Backup_Registers  PWREx Backup Registers Definition
  * @{
  */
#define PWR_BKP_NUMBER                    4U
#define PWR_BKP_DR0                       0x00U
#define PWR_BKP_DR1                       0x01U
#define PWR_BKP_DR2                       0x02U
#define PWR_BKP_DR3                       0x03U
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Port  GPIO Port
  * @{
  */
#define PWR_GPIO_A                          (0x00000000u)  /*!< GPIO port A */
#define PWR_GPIO_B                          (0x00000001u)  /*!< GPIO port B */
#define PWR_GPIO_C                          (0x00000002u)  /*!< GPIO port C */
#if defined(STM32C031xx)
#define PWR_GPIO_D                          (0x00000003u)  /*!< GPIO port D */
#endif /* STM32C031xx */
#define PWR_GPIO_F                          (0x00000005u)  /*!< GPIO port F */
/**
  * @}
  */

/** @defgroup PWREx_Flash_PowerDown  Flash Power Down modes
  * @{
  */
#define PWR_FLASHPD_SLEEP                   PWR_CR1_FPD_SLP    /*!< Enable Flash power down in sleep mode */
#define PWR_FLASHPD_STOP                    PWR_CR1_FPD_STOP   /*!< Enable Flash power down in stop mode */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_GPIO_BIT_NUMBER(__BIT_NUMBER__)  ((((__BIT_NUMBER__) & 0x0000FFFFu) != 0x00u) && \
                                                 (((__BIT_NUMBER__) & 0xFFFF0000u) == 0x00u))
#if defined(STM32C031xx)
#define IS_PWR_GPIO(__GPIO__)               (((__GPIO__) == PWR_GPIO_A) || \
                                             ((__GPIO__) == PWR_GPIO_B) || \
                                             ((__GPIO__) == PWR_GPIO_C) || \
                                             ((__GPIO__) == PWR_GPIO_D) || \
                                             ((__GPIO__) == PWR_GPIO_F))
#elif defined (STM32C011xx)
#define IS_PWR_GPIO(__GPIO__)               (((__GPIO__) == PWR_GPIO_A) || \
                                             ((__GPIO__) == PWR_GPIO_B) || \
                                             ((__GPIO__) == PWR_GPIO_C) || \
                                             ((__GPIO__) == PWR_GPIO_F))

#endif /* STM32C031xx */
#define IS_PWR_FLASH_POWERDOWN(__MODE__)    ((((__MODE__) & (PWR_FLASHPD_SLEEP | PWR_FLASHPD_STOP)) != 0x00u) && \
                                             (((__MODE__) & ~(PWR_FLASHPD_SLEEP | PWR_FLASHPD_STOP)) == 0x00u))

#define IS_PWR_BKP(__BKP__)   ((__BKP__) < PWR_BKP_NUMBER)



/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Functions  PWR Extended Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1  Extended Peripheral Control functions
  * @{
  */

/* Peripheral Control functions  **********************************************/
void              HAL_PWREx_EnableInternalWakeUpLine(void);
void              HAL_PWREx_DisableInternalWakeUpLine(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);
void              HAL_PWREx_EnableFlashPowerDown(uint32_t PowerMode);
void              HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode);
void              HAL_PWREx_BKUPWrite(uint32_t BackupRegister, uint16_t Data);
uint32_t          HAL_PWREx_BKUPRead(uint32_t BackupRegister);

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


#endif /* STM32C0xx_HAL_PWR_EX_H */
