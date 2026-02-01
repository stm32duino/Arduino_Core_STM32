/**
  ******************************************************************************
  * @file    stm32u3xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extended module.
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
#ifndef STM32U3xx_HAL_GPIO_EX_H
#define STM32U3xx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO Extended HAL module driver
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */

/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection
  * @{
  */
#if defined(STM32U385xx) || defined(STM32U375xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_CRS              ((uint8_t)0x00)   /*!< CRS Alternate Function mapping           */
#define GPIO_AF0_LPTIM1           ((uint8_t)0x00)   /*!< LPTIM1 Alternate Function mapping        */
#define GPIO_AF0_MCO              ((uint8_t)0x00)   /*!< MCO Alternate Function mapping           */
#define GPIO_AF0_PWR              ((uint8_t)0x00)   /*!< PWR Alternate Function mapping           */
#define GPIO_AF0_RTC              ((uint8_t)0x00)   /*!< RTC Alternate Function mapping           */
#define GPIO_AF0_SWJ              ((uint8_t)0x00)   /*!< SWD and JTAG Alternate Function mapping  */
#define GPIO_AF0_TRACE            ((uint8_t)0x00)   /*!< TRACE Alternate Function mapping         */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_IR               ((uint8_t)0x01)   /*!< IR Alternate Function mapping      */
#define GPIO_AF1_LPTIM1           ((uint8_t)0x01)   /*!< LPTIM1 Alternate Function mapping  */
#define GPIO_AF1_TIM1             ((uint8_t)0x01)   /*!< TIM1 Alternate Function mapping    */
#define GPIO_AF1_TIM2             ((uint8_t)0x01)   /*!< TIM2 Alternate Function mapping    */

/**
  * @brief   AF 2 selection
  */

#define GPIO_AF2_LPTIM1           ((uint8_t)0x02)   /*!< LPTIM1 Alternate Function mapping  */
#define GPIO_AF2_LPTIM2           ((uint8_t)0x02)   /*!< LPTIM2 Alternate Function mapping  */
#define GPIO_AF2_LPTIM3           ((uint8_t)0x02)   /*!< LPTIM3 Alternate Function mapping  */
#define GPIO_AF2_TIM1             ((uint8_t)0x02)   /*!< TIM1 Alternate Function mapping    */
#define GPIO_AF2_TIM2             ((uint8_t)0x02)   /*!< TIM2 Alternate Function mapping    */
#define GPIO_AF2_TIM3             ((uint8_t)0x02)   /*!< TIM3 Alternate Function mapping    */
#define GPIO_AF2_TIM4             ((uint8_t)0x02)   /*!< TIM4 Alternate Function mapping    */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_ADF1             ((uint8_t)0x03)   /*!< ADF1 Alternate Function mapping      */
#define GPIO_AF3_I2C1             ((uint8_t)0x03)   /*!< I2C1 Alternate Function mapping      */
#define GPIO_AF3_I2C2             ((uint8_t)0x03)   /*!< I2C2 Alternate Function mapping      */
#define GPIO_AF3_I3C1             ((uint8_t)0x03)   /*!< I3C1 Alternate Function mapping      */
#define GPIO_AF3_I3C2             ((uint8_t)0x03)   /*!< I3C2 Alternate Function mapping      */
#define GPIO_AF3_OCTOSPI1         ((uint8_t)0x03)   /*!< OCTOSPI1 Alternate Function mapping  */
#define GPIO_AF3_SAI1             ((uint8_t)0x03)   /*!< SAI1 Alternate Function mapping      */
#define GPIO_AF3_SPI2             ((uint8_t)0x03)   /*!< SPI2 Alternate Function mapping      */
#define GPIO_AF3_TIM1             ((uint8_t)0x03)   /*!< TIM1 Alternate Function mapping      */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1             ((uint8_t)0x04)   /*!< I2C1 Alternate Function mapping    */
#define GPIO_AF4_I2C2             ((uint8_t)0x04)   /*!< I2C2 Alternate Function mapping    */
#define GPIO_AF4_I2C3             ((uint8_t)0x04)   /*!< I2C3 Alternate Function mapping    */
#define GPIO_AF4_LPTIM3           ((uint8_t)0x04)   /*!< LPTIM3 Alternate Function mapping  */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_I2C3             ((uint8_t)0x05)   /*!< I2C3 Alternate Function mapping      */
#define GPIO_AF5_I3C1             ((uint8_t)0x05)   /*!< I3C1 Alternate Function mapping      */
#define GPIO_AF5_I3C2             ((uint8_t)0x05)   /*!< I3C2 Alternate Function mapping      */
#define GPIO_AF5_OCTOSPI1         ((uint8_t)0x05)   /*!< OCTOSPI1 Alternate Function mapping  */
#define GPIO_AF5_SPI1             ((uint8_t)0x05)   /*!< SPI1 Alternate Function mapping      */
#define GPIO_AF5_SPI2             ((uint8_t)0x05)   /*!< SPI2 Alternate Function mapping      */
#define GPIO_AF5_SPI3             ((uint8_t)0x05)   /*!< SPI3 Alternate Function mapping      */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_I3C1             ((uint8_t)0x06)   /*!< I3C1 Alternate Function mapping  */
#define GPIO_AF6_I3C2             ((uint8_t)0x06)   /*!< I3C2 Alternate Function mapping  */
#define GPIO_AF6_SPI3             ((uint8_t)0x06)   /*!< SPI3 Alternate Function mapping  */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1           ((uint8_t)0x07)   /*!< USART1 Alternate Function mapping  */
#define GPIO_AF7_USART3           ((uint8_t)0x07)   /*!< USART3 Alternate Function mapping  */


/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_LPUART1          ((uint8_t)0x08)   /*!< LPUART1 Alternate Function mapping */
#define GPIO_AF8_UART4            ((uint8_t)0x08)   /*!< UART4 Alternate Function mapping   */
#define GPIO_AF8_UART5            ((uint8_t)0x08)   /*!< UART5 Alternate Function mapping   */
#define GPIO_AF8_SDMMC1           ((uint8_t)0x08)   /*!< SDMMC1 Alternate Function mapping  */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_FDCAN1           ((uint8_t)0x09)   /*!< FDCAN1 Alternate Function mapping  */
#define GPIO_AF9_TSC              ((uint8_t)0x09)   /*!< TSC Alternate Function mapping     */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_CRS             ((uint8_t)0x0A)   /*!< CRS Alternate Function mapping       */
#define GPIO_AF10_OCTOSPI1        ((uint8_t)0x0A)   /*!< OCTOSPI1 Alternate Function mapping  */
#define GPIO_AF10_USB             ((uint8_t)0x0A)   /*!< USB Alternate Function mapping       */

/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_MCO2            ((uint8_t)0x0B)   /*!< MCO2 Alternate Function mapping    */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_COMP1           ((uint8_t)0x0C)   /*!< COMP1 Alternate Function mapping   */
#define GPIO_AF12_COMP2           ((uint8_t)0x0C)   /*!< COMP2 Alternate Function mapping   */
#define GPIO_AF12_SDMMC1          ((uint8_t)0x0C)   /*!< SDMMC1 Alternate Function mapping  */
#define GPIO_AF12_TRACE           ((uint8_t)0x0C)   /*!< TRACE Alternate Function mapping   */


/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_AUDIOCLK        ((uint8_t)0x0D)   /*!< AUDIOCLOCK Alternate Function mapping  */
#define GPIO_AF13_LPTIM2          ((uint8_t)0x0D)   /*!< LPTIM2 Alternate Function mapping      */
#define GPIO_AF13_LPTIM4          ((uint8_t)0x0D)   /*!< LPTIM4 Alternate Function mapping      */
#define GPIO_AF13_SAI1            ((uint8_t)0x0D)   /*!< SAI1 Alternate Function mapping        */


/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_LPTIM2          ((uint8_t)0x0E)   /*!< LPTIM2 Alternate Function mapping  */
#define GPIO_AF14_LPTIM3          ((uint8_t)0x0E)   /*!< LPTIM3 Alternate Function mapping  */
#define GPIO_AF14_TIM2            ((uint8_t)0x0E)   /*!< TIM2 Alternate Function mapping    */
#define GPIO_AF14_TIM15           ((uint8_t)0x0E)   /*!< TIM15 Alternate Function mapping   */
#define GPIO_AF14_TIM16           ((uint8_t)0x0E)   /*!< TIM16 Alternate Function mapping   */
#define GPIO_AF14_TIM17           ((uint8_t)0x0E)   /*!< TIM17 Alternate Function mapping   */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT        ((uint8_t)0x0F)   /*!< EVENTOUT Alternate Function mapping  */

#define IS_GPIO_AF(AF)            ((AF) <= (uint8_t)0x0F)

#endif /* defined(STM32U385xx) || defined(STM32U375xx) */


/**
  * @}
  */

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
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0UL :\
                                      ((__GPIOx__) == (GPIOB))? 1UL :\
                                      ((__GPIOx__) == (GPIOC))? 2UL :\
                                      ((__GPIOx__) == (GPIOD))? 3UL :\
                                      ((__GPIOx__) == (GPIOE))? 4UL :\
                                      ((__GPIOx__) == (GPIOG))? 6UL :\
                                      ((__GPIOx__) == (GPIOH))? 7UL : 16UL)

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
#endif /* __cplusplus */

#endif /* STM32U3xx_HAL_GPIO_EX_H */
