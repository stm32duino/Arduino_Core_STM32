/**
  ******************************************************************************
  * @file    stm32u0xx_hal_gpio_ex.h
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
#ifndef STM32U0xx_HAL_GPIO_EX_H
#define STM32U0xx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal_def.h"

/** @addtogroup STM32U0xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */

/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection
  * @{
  */

/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO (MCO1) Alternate Function mapping */
#define GPIO_AF0_OSC_EN        ((uint8_t)0x00)  /*!< OSC (By pass and Enable) Alternate Function mapping */
#define GPIO_AF0_OSC32_EN      ((uint8_t)0x00)  /*!< OSC32 (By pass and Enable) Alternate Function mapping */
#define GPIO_AF0_SWD           ((uint8_t)0x00)  /*!< SWD (SWDIO/SWDCLK)  Alternate Function mapping */
#define GPIO_AF0_MCO2          ((uint8_t)0x00)  /*!< MCO (MCO2) Alternate Function mapping */
#define GPIO_AF0_RTC           ((uint8_t)0x00)  /*!< RTC (OUT2/REFIN) Alternate Function mapping */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /*!< IR Alternate Function mapping */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)  /*!< LPTIM1 Alternate Function mapping */
#define GPIO_AF1_OSC_EN        ((uint8_t)0x01)  /*!< OSC (By pass and Enable) Alternate Function mapping */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /*!< LPTIM1 Alternate Function mapping */
#if defined(LPTIM3)
#define GPIO_AF2_LPTIM3        ((uint8_t)0x02)  /*!< LPTIM3 Alternate Function mapping */
#endif /* LPTIM3 */
#if defined(I2C4)
#define GPIO_AF2_I2C4          ((uint8_t)0x02)  /*!< I2C4 Alternate Function mapping */
#endif /* I2C4 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM3 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_I2C2          ((uint8_t)0x03)  /*!< I2C2 Alternate Function mapping */
#define GPIO_AF3_MCO2          ((uint8_t)0x03)  /*!< MCO (MCO2) Alternate Function mapping */
#define GPIO_AF3_USART2        ((uint8_t)0x03)  /*!< USART2 Alternate Function mapping */
#if defined(I2C4)
#define GPIO_AF3_I2C4          ((uint8_t)0x03)  /*!< I2C4 Alternate Function mapping */
#endif /* I2C4 */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping */
#if defined(LPTIM3)
#define GPIO_AF4_LPTIM3        ((uint8_t)0x04)  /*!< LPTIM3 Alternate Function mapping */
#endif /* LPTIM3 */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /*!< I2C2 Alternate Function mapping */
#if defined(I2C4)
#define GPIO_AF4_I2C4          ((uint8_t)0x04)  /*!< I2C4 Alternate Function mapping */
#endif /* I2C4 */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /*!< I2C2 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /*!< SPI2 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /*!< SPI2 Alternate Function mapping */
#if defined (SPI3)
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /*!< SPI3 Alternate Function mapping */
#endif /* SPI3 */
#define GPIO_AF6_COMP1         ((uint8_t)0x06)  /*!< COMP1 Alternate Function mapping */
#if defined(LPUART3)
#define GPIO_AF6_LPUART3       ((uint8_t)0x06)  /*!< LPUART3 Alternate Function mapping */
#endif /* LPUART3 */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /*!< USART3 Alternate Function mapping */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_USART4        ((uint8_t)0x08)  /*!< USART4 Alternate Function mapping  */
#define GPIO_AF8_LPUART1       ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping */
#define GPIO_AF8_LPUART2       ((uint8_t)0x08)  /*!< LPUART2 Alternate Function mapping */
#if defined(LPUART3)
#define GPIO_AF8_LPUART3       ((uint8_t)0x08)  /*!< LPUART3 Alternate Function mapping */
#endif /* LPUART3 */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TSC           ((uint8_t)0x09)  /*!< TSC Alternate Function mapping */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_LPUART2      ((uint8_t)0x0A)  /*!< LPUART2 Alternate Function mapping */
#if defined(USB_DRD_FS)
#define GPIO_AF10_USB          ((uint8_t)0x0A)  /*!< USB Alternate Function mapping */
#endif /* USB_DRD_FS */
#if defined(CRS)
#define GPIO_AF10_CRS          ((uint8_t)0x0A)  /*!< CRS Alternate Function mapping */
#endif /* CRS */

/**
  * @brief   AF 11 selection
  */
#if defined(LCD)
#define GPIO_AF11_LCD         ((uint8_t)0x0B)  /*!< LCD Alternate Function mapping */
#endif /* LCD */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_COMP1       ((uint8_t)0x0C)  /*!< COMP1 Alternate Function mapping */
#if defined(COMP2)
#define GPIO_AF12_COMP2       ((uint8_t)0x0C)  /*!< COMP2 Alternate Function mapping */
#endif /* COMP2 */
#if defined(LCD)
#define GPIO_AF12_LCD         ((uint8_t)0x0C)  /*!< LCD Alternate Function mapping */
#endif /* LCD */

/**
  * @brief   AF 13 selection
  */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_LPTIM1      ((uint8_t)0x0E)  /*!< LPTIM1 Alternate Function mapping */
#define GPIO_AF14_LPTIM2      ((uint8_t)0x0E)  /*!< LPTIM2 Alternate Function mapping */
#if defined(LPTIM3)
#define GPIO_AF14_LPTIM3      ((uint8_t)0x0E)  /*!< LPTIM3 Alternate Function mapping */
#endif /* LPTIM3 */
#define GPIO_AF14_TIM2        ((uint8_t)0x0E)  /*!< TIM2 Alternate Function mapping   */
#define GPIO_AF14_TIM15       ((uint8_t)0x0E)  /*!< TIM15 Alternate Function mapping  */
#define GPIO_AF14_TIM16       ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping  */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT    ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping */

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
#if defined (GPIOE)
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL :\
                                      ((__GPIOx__) == (GPIOB))? 1uL :\
                                      ((__GPIOx__) == (GPIOC))? 2uL :\
                                      ((__GPIOx__) == (GPIOD))? 3uL :\
                                      ((__GPIOx__) == (GPIOE))? 4uL :\
                                      ((__GPIOx__) == (GPIOF))? 5uL : 6uL)
#else
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL :\
                                      ((__GPIOx__) == (GPIOB))? 1uL :\
                                      ((__GPIOx__) == (GPIOC))? 2uL :\
                                      ((__GPIOx__) == (GPIOD))? 3uL :\
                                      ((__GPIOx__) == (GPIOF))? 5uL : 6uL)
#endif /* GPIOE */
/**
  * @}
  */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x0F)

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

#endif /* STM32U0xx_HAL_GPIO_EX_H */
