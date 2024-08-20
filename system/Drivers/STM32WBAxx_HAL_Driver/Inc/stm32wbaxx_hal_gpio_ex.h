/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extended module.
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
#ifndef STM32WBAxx_HAL_GPIO_EX_H
#define STM32WBAxx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/

/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */



#if defined(STM32WBA54xx) || defined(STM32WBA55xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /*!< RTC_50Hz Alternate Function mapping           */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /*!< SWJ (SWD and JTAG) Alternate Function mapping */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /*!< TRACE Alternate Function mapping              */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /*!< LPTIM1 Alternate Function mapping             */
#define GPIO_AF0_PWR           ((uint8_t)0x00)  /*!< PWR Alternate Function mapping                */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /*!< IR Alternate Function mapping   */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping   */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping   */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /*!< TIM3 Alternate Function mapping   */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /*!< LPTIM1 Alternate Function mapping */
#define GPIO_AF2_LPTIM2        ((uint8_t)0x02)  /*!< LPTIM2 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_SAI1          ((uint8_t)0x03)  /*!< SAI1 Alternate Function mapping   */
#define GPIO_AF3_USART2        ((uint8_t)0x03)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF3_IR            ((uint8_t)0x03)  /*!< IR Alternate Function mapping     */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_I2C3          ((uint8_t)0x06)  /*!< I2C3 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /*!< SPI3 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_LPUART1       ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TSC           ((uint8_t)0x09)  /*!< TSC Alternate Function mapping */

/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_RF          ((uint8_t)0x0B)  /*!< RF_ANTSW0 Alternate Function mapping */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_COMP1        ((uint8_t)0x0C)  /*!< COMP1 Alternate Function mapping */
#define GPIO_AF12_COMP2        ((uint8_t)0x0C)  /*!< COMP2 Alternate Function mapping */

/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_SAI1         ((uint8_t)0x0D)  /*!< SAI1 Alternate Function mapping   */
#define GPIO_AF13_LPTIM2       ((uint8_t)0x0D)  /*!< LPTIM2 Alternate Function mapping */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_LPTIM2       ((uint8_t)0x0E)  /*!< LPTIM2 Alternate Function mapping */
#define GPIO_AF14_TIM3         ((uint8_t)0x0E)  /*!< TIM3 Alternate Function mapping   */
#define GPIO_AF14_TIM16        ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping  */
#define GPIO_AF14_TIM17        ((uint8_t)0x0E)  /*!< TIM17 Alternate Function mapping  */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT     ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x0F)

#endif /* (defined(STM32WBA54xx) || defined(STM32WBA55xx)) */

#if defined(STM32WBA52xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /*!< RTC_50Hz Alternate Function mapping           */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /*!< SWJ (SWD and JTAG) Alternate Function mapping */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /*!< TRACE Alternate Function mapping              */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /*!< LPTIM1 Alternate Function mapping             */
#define GPIO_AF0_PWR           ((uint8_t)0x00)  /*!< PWR Alternate Function mapping                */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /*!< IR Alternate Function mapping   */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping   */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping   */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /*!< TIM3 Alternate Function mapping   */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /*!< LPTIM1 Alternate Function mapping */
#define GPIO_AF2_LPTIM2        ((uint8_t)0x02)  /*!< LPTIM2 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_SAI1          ((uint8_t)0x03)  /*!< SAI1 Alternate Function mapping   */
#define GPIO_AF3_USART2        ((uint8_t)0x03)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF3_IR            ((uint8_t)0x03)  /*!< IR Alternate Function mapping     */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_I2C3          ((uint8_t)0x06)  /*!< I2C3 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /*!< SPI3 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_LPUART1       ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TSC           ((uint8_t)0x09)  /*!< TSC Alternate Function mapping */

/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_RF          ((uint8_t)0x0B)  /*!< RF_ANTSW0 Alternate Function mapping */

/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_LPTIM2       ((uint8_t)0x0D)  /*!< LPTIM2 Alternate Function mapping */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_LPTIM2       ((uint8_t)0x0E)  /*!< LPTIM2 Alternate Function mapping */
#define GPIO_AF14_TIM3         ((uint8_t)0x0E)  /*!< TIM3 Alternate Function mapping   */
#define GPIO_AF14_TIM16        ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping  */
#define GPIO_AF14_TIM17        ((uint8_t)0x0E)  /*!< TIM17 Alternate Function mapping  */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT     ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x0F)

#endif /* (defined(STM32WBA54xx) || defined(STM32WBA55xx)) */

#if defined(STM32WBA50xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /*!< RTC_50Hz Alternate Function mapping           */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /*!< SWJ (SWD and JTAG) Alternate Function mapping */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /*!< TRACE Alternate Function mapping              */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /*!< LPTIM1 Alternate Function mapping             */
#define GPIO_AF0_PWR           ((uint8_t)0x00)  /*!< PWR Alternate Function mapping                */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping   */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping   */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /*!< LPTIM1 Alternate Function mapping */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_I2C3          ((uint8_t)0x06)  /*!< I2C3 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /*!< SPI3 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_LPUART1       ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TSC           ((uint8_t)0x09)  /*!< TSC Alternate Function mapping */

/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_RF          ((uint8_t)0x0B)  /*!< RF_ANTSW0 Alternate Function mapping */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_TIM16        ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT     ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping */
#define GPIO_AF15_RF_DTB0      ((uint8_t)0x0F)  /*!< RF_DTB0 Alternate Function mapping  */
#define GPIO_AF15_RF_DTB1      ((uint8_t)0x0F)  /*!< RF_DTB1 Alternate Function mapping  */
#define GPIO_AF15_RF_DTB2      ((uint8_t)0x0F)  /*!< RF_DTB2 Alternate Function mapping  */
#define GPIO_AF15_RF_DTB3      ((uint8_t)0x0F)  /*!< RF_DTB3 Alternate Function mapping  */
#define GPIO_AF15_RF_DTB4      ((uint8_t)0x0F)  /*!< RF_DTB4 Alternate Function mapping  */
#define GPIO_AF15_RF_DTB5      ((uint8_t)0x0F)  /*!< RF_DTB5 Alternate Function mapping  */
#define GPIO_AF15_RF_DTB6      ((uint8_t)0x0F)  /*!< RF_DTB6 Alternate Function mapping  */
#define GPIO_AF15_RF_DTB7      ((uint8_t)0x0F)  /*!< RF_DTB7 Alternate Function mapping  */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x0F)

#endif /* defined(STM32WBA50xx) */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Macros GPIOEx Exported Macros
  * @{
  */

/** @defgroup GPIOEx_Get_Port_Index GPIOEx Get Port Index
  * @{
  */
#define GPIO_GET_INDEX(__GPIOx__)           (((uint32_t )(__GPIOx__) & (~GPIOA_BASE)) >> 10)

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WBAxx_HAL_GPIO_EX_H */
