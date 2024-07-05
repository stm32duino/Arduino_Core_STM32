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
/** @defgroup PWREx_Exported_Types PWR Extended Exported Types
  * @{
  */

#if defined(PWR_PVM_SUPPORT)
/**
  * @brief  PWR PVM configuration structure definition
  */
typedef struct
{
  uint32_t PVMType;   /*!< PVMType: Specifies which voltage is monitored and against which threshold.
                           This parameter can be a value of @ref PWREx_PVM_Type.
                           @arg @ref PWR_PVM_USB Peripheral Voltage Monitoring USB enable */

  uint32_t Mode;      /*!< Mode: Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref PWREx_PVM_Mode. */
} PWR_PVMTypeDef;
#endif /* PWR_PVM_SUPPORT */
/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
#if defined(PWR_PVM_SUPPORT)
/** @defgroup PWREx_PVM_Type Peripheral Voltage Monitoring type
  * @{
  */
#define PWR_PVM_USB  PWR_CR2_PVM_VDDIO2_0  /*!< Peripheral Voltage Monitoring enable for USB peripheral: Enable to keep
                                            the USB peripheral voltage monitoring under control (power domain Vddio2) */
/**
  * @}
  */
/** @defgroup PWREx_PVM_Mode  PWR PVM interrupt and event mode
  * @{
  */
#define PWR_PVM_MODE_NORMAL               ((uint32_t)0x00000000) /*!< basic mode is used */
#define PWR_PVM_MODE_IT_RISING            ((uint32_t)0x00010001) /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_IT_FALLING           ((uint32_t)0x00010002) /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_IT_RISING_FALLING    ((uint32_t)0x00010003) /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVM_MODE_EVENT_RISING         ((uint32_t)0x00020001) /*!< Event Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_EVENT_FALLING        ((uint32_t)0x00020002) /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_EVENT_RISING_FALLING ((uint32_t)0x00020003) /*!< Event Mode with Rising/Falling edge trigger detection */
/**
  * @}
  */
/** @defgroup PWR_PVM_EXTI_LINE  PWR PVM external interrupt line
  * @{
  */
#define PWR_EXTI_LINE_PVM                   (EXTI_IMR2_IM34)  /*!< External interrupt line 34 connected to PVM */
/**
  * @}
  */

/** @defgroup PWR_PVM_EVENT_LINE  PWR PVM event line
  * @{
  */
#define PWR_EVENT_LINE_PVM                  (EXTI_EMR2_EM34)  /*!< Event line 34 connected to PVM */
/**
  * @}
  */
#endif /* PWR_PVM_SUPPORT */

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
#if defined(GPIOD)
#define PWR_GPIO_D                          (0x00000003u)  /*!< GPIO port D */
#endif /* GPIOD */
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

/** @addtogroup PWR_Flag  PWR Status Flags
  * @brief  Elements values convention: 0000 00XX 000Y YYYYb
  *           - Y YYYY  : Flag position in the XX register (5 bits)
  *           - XX  : Status register (2 bits)
  *                 - 01: SR1 register
  *                 - 10: SR2 register
  *         The only exception is PWR_FLAG_WU, encompassing all
  *         wake-up flags and set to PWR_SR1_WUF.
  * @{
  */
#if defined(PWR_PVM_SUPPORT)
#define PWR_FLAG_PVMOUSB  (0x00020000u | PWR_SR2_PVMO_USB)   /*!< USB Peripheral Voltage Monitoring output */
#endif /* PWR_PVM_SUPPORT */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @addtogroup PWREx_Exported_Macros  PWR Extended Exported Macros
  * @{
  */
#if defined(PWR_PVM_SUPPORT)
/**
  * @brief Enable the PVM Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_IT()            SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Disable the PVM Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_IT()           CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Enable the PVM Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_EVENT()         SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM)

/**
  * @brief Disable the PVM Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_EVENT()        CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM)

/**
  * @brief Enable the PVM Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Disable the PVM Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Enable the PVM Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Disable the PVM Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief  Enable the PVM Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                   \
    __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief Disable the PVM Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_GENERATE_SWIT()        SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM)

/**
  * @brief Check whether or not the PVM EXTI interrupt Rising flag is set.
  * @retval EXTI PVM Line Status.
  */
#define __HAL_PWR_PVM_EXTI_GET_RISING_FLAG()      (EXTI->RPR2 & PWR_EXTI_LINE_PVM)

/**
  * @brief Check whether or not the PVM EXTI interrupt Falling flag is set.
  * @retval EXTI PVM Line Status.
  */
#define __HAL_PWR_PVM_EXTI_GET_FALLING_FLAG()     (EXTI->FPR2 & PWR_EXTI_LINE_PVM)

/**
  * @brief Clear the PVM EXTI interrupt Rising flag.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_CLEAR_RISING_FLAG()    WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Clear the PVM EXTI interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_CLEAR_FALLING_FLAG()   WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM)
#endif /* PWR_PVM_SUPPORT */
/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */

/** @defgroup PWREx_PVM_Mode_Mask PWR PVM Mode Mask
  * @{
  */
#define PVM_MODE_IT        ((uint32_t)0x00010000)  /*!< Mask for interruption yielded by PVM threshold crossing */
#define PVM_MODE_EVT       ((uint32_t)0x00020000)  /*!< Mask for event yielded by PVM threshold crossing        */
#define PVM_RISING_EDGE    ((uint32_t)0x00000001)  /*!< Mask for rising edge set as PVM trigger                 */
#define PVM_FALLING_EDGE   ((uint32_t)0x00000002)  /*!< Mask for falling edge set as PVM trigger                */
/**
  * @}
  */

/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_GPIO_BIT_NUMBER(__BIT_NUMBER__)  ((((__BIT_NUMBER__) & 0x0000FFFFu) != 0x00u) && \
                                                 (((__BIT_NUMBER__) & 0xFFFF0000u) == 0x00u))
#if defined(GPIOD)
#define IS_PWR_GPIO(__GPIO__)               (((__GPIO__) == PWR_GPIO_A) || \
                                             ((__GPIO__) == PWR_GPIO_B) || \
                                             ((__GPIO__) == PWR_GPIO_C) || \
                                             ((__GPIO__) == PWR_GPIO_D) || \
                                             ((__GPIO__) == PWR_GPIO_F))
#else
#define IS_PWR_GPIO(__GPIO__)               (((__GPIO__) == PWR_GPIO_A) || \
                                             ((__GPIO__) == PWR_GPIO_B) || \
                                             ((__GPIO__) == PWR_GPIO_C) || \
                                             ((__GPIO__) == PWR_GPIO_F))

#endif /* GPIOD */
#define IS_PWR_FLASH_POWERDOWN(__MODE__)    ((((__MODE__) & (PWR_FLASHPD_SLEEP | PWR_FLASHPD_STOP)) != 0x00u) && \
                                             (((__MODE__) & ~(PWR_FLASHPD_SLEEP | PWR_FLASHPD_STOP)) == 0x00u))

#define IS_PWR_BKP(__BKP__)   ((__BKP__) < PWR_BKP_NUMBER)

#if defined(PWR_PVM_SUPPORT)
#define IS_PWR_PVM_TYPE(TYPE) ((TYPE) == PWR_PVM_USB)

#define IS_PWR_PVM_MODE(MODE)  (((MODE) == PWR_PVM_MODE_NORMAL)              ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING)           ||\
                                ((MODE) == PWR_PVM_MODE_IT_FALLING)          ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING_FALLING)   ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING)        ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_FALLING)       ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING_FALLING))
#endif /* PWR_PVM_SUPPORT */

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

#if defined(PWR_PVM_SUPPORT)
/* Power voltage monitoring configuration functions ***************************/
void HAL_PWREx_EnablePVMUSB(void);
void HAL_PWREx_DisablePVMUSB(void);
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM);
#endif /* PWR_PVM_SUPPORT */


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
