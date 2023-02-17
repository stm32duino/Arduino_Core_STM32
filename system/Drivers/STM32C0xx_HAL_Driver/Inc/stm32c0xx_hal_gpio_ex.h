/**
  ******************************************************************************
  * @file    stm32c0xx_hal_gpio_ex.h
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
#ifndef STM32C0xx_HAL_GPIO_EX_H
#define STM32C0xx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal_def.h"

/** @addtogroup STM32C0xx_HAL_Driver
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

#if defined(STM32C011xx)
/*------------------------- STM32C011xx --------------------------------------*/
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO (MCO1 and MCO2) Alternate Function mapping */
#define GPIO_AF0_OSC32         ((uint8_t)0x00)  /*!< OSC32 (By pass and Enable) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /*!< SWJ (SWD) Alternate Function mapping */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF0_I2S1          ((uint8_t)0x00)  /*!< I2S1 Alternate Function mapping */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART1 Alternate Function mapping */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /*!< IR Alternate Function mapping */
#define GPIO_AF1_OSC           ((uint8_t)0x01)  /*!< OSC (By pass and Enable) Alternate Function mapping */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM3          ((uint8_t)0x01)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF1_USART2        ((uint8_t)0x01)  /*!< USART2 Alternate Function mapping */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM16         ((uint8_t)0x02)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF2_TIM17         ((uint8_t)0x02)  /*!< TIM17 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_MCO2          ((uint8_t)0x03)  /*!< MCO2 Alternate Function mapping */
#define GPIO_AF3_TIM3          ((uint8_t)0x03)  /*!< TIM3 Alternate Function mapping */
/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_TIM14         ((uint8_t)0x04)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF4_USART2        ((uint8_t)0x04)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF4_USART1        ((uint8_t)0x04)  /*!< USART1 Alternate Function mapping */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /*!< I2S Alternate Function mapping */
#define GPIO_AF5_USART1        ((uint8_t)0x05)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF5_TIM1          ((uint8_t)0x05)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF5_TIM16         ((uint8_t)0x05)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF5_TIM17         ((uint8_t)0x05)  /*!< TIM17 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06)  /*!< I2C1 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_EVENTOUT      ((uint8_t)0x07)  /*!< EVENTOUT Alternate Function mapping */
#define GPIO_AF7_I2C1          ((uint8_t)0x07)  /*!< I2C1 Alternate Function mapping */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_I2S1          ((uint8_t)0x08)  /*!< I2S1 Alternate Function mapping */
#define GPIO_AF8_SPI1          ((uint8_t)0x08)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF8_IR            ((uint8_t)0x08)  /*!< IR Alternate Function mapping */
/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF9_USART2        ((uint8_t)0x09)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF9_SPI1          ((uint8_t)0x09)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF9_I2S1          ((uint8_t)0x09)  /*!< I2S1 Alternate Function mapping */
/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_TIM1         ((uint8_t)0x0A)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF10_I2C1         ((uint8_t)0x0A)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF10_SPI1         ((uint8_t)0x0A)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF10_TIM16        ((uint8_t)0x0A)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF10_TIM17        ((uint8_t)0x0A)  /*!< TIM17 Alternate Function mapping */
/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_TIM1         ((uint8_t)0x0B)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF11_TIM3         ((uint8_t)0x0B)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF11_MCO2         ((uint8_t)0x0B)  /*!< MCO2 Alternate Function mapping */
/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_TIM3         ((uint8_t)0x0C)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF12_USART1       ((uint8_t)0x0C)  /*!< USART1 Alternate Function mapping */
/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_TIM14        ((uint8_t)0x0D)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF13_TIM3         ((uint8_t)0x0D)  /*!< TIM3 Alternate Function mapping */
/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_USART1      ((uint8_t)0x0E)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF14_I2C1        ((uint8_t)0x0E)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF14_TIM16       ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping */
/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping */
#define GPIO_AF15_MCO2          ((uint8_t)0x0F)  /*!< MCO2 Alternate Function mapping */
#define GPIO_AF15_TIM17         ((uint8_t)0x0F)  /*!< TIM17 Alternate Function mapping */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x0F)
#endif /* STM32C011xx */

#if defined(STM32C031xx)
/*------------------------- STM32C031xx --------------------------------------*/
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /*!< EVENTOUT Alternate Function mapping */
#define GPIO_AF0_IR            ((uint8_t)0x00)  /*!< IR Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO (MCO1 and MCO2) Alternate Function mapping */
#define GPIO_AF0_OSC           ((uint8_t)0x00)  /*!< OSC (By pass and Enable) Alternate Function mapping */
#define GPIO_AF0_OSC32         ((uint8_t)0x00)  /*!< OSC32 (By pass and Enable) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /*!< SWJ (SWD) Alternate Function mapping */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF0_I2S1          ((uint8_t)0x00)  /*!< I2S1 Alternate Function mapping */
#define GPIO_AF0_TIM14         ((uint8_t)0x00)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /*!< USART2 Alternate Function mapping */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /*!< IR Alternate Function mapping */
#define GPIO_AF1_OSC           ((uint8_t)0x01)  /*!< OSC (By pass and Enable) Alternate Function mapping */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM3          ((uint8_t)0x01)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF1_USART2        ((uint8_t)0x01)  /*!< USART2 Alternate Function mapping */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM14         ((uint8_t)0x02)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF2_TIM16         ((uint8_t)0x02)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF2_TIM17         ((uint8_t)0x02)  /*!< TIM17 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_MCO2          ((uint8_t)0x03)  /*!< MCO2 Alternate Function mapping */
#define GPIO_AF3_TIM3          ((uint8_t)0x03)  /*!< TIM3 Alternate Function mapping */
/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_TIM14         ((uint8_t)0x04)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF4_USART2        ((uint8_t)0x04)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF4_USART1        ((uint8_t)0x04)  /*!< USART1 Alternate Function mapping */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /*!< I2S Alternate Function mapping */
#define GPIO_AF5_USART1        ((uint8_t)0x05)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF5_TIM1          ((uint8_t)0x05)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF5_TIM16         ((uint8_t)0x05)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF5_TIM17         ((uint8_t)0x05)  /*!< TIM17 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06)  /*!< I2C1 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_EVENTOUT      ((uint8_t)0x07)  /*!< EVENTOUT Alternate Function mapping */
#define GPIO_AF7_I2C1          ((uint8_t)0x07)  /*!< I2C1 Alternate Function mapping */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_I2S1          ((uint8_t)0x08)  /*!< I2S1 Alternate Function mapping */
#define GPIO_AF8_SPI1          ((uint8_t)0x08)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF8_IR            ((uint8_t)0x08)  /*!< IR Alternate Function mapping */
/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF9_USART2        ((uint8_t)0x09)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF9_SPI1          ((uint8_t)0x09)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF9_I2S1          ((uint8_t)0x09)  /*!< I2S1 Alternate Function mapping */
/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_TIM1         ((uint8_t)0x0A)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF10_I2C1         ((uint8_t)0x0A)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF10_SPI1         ((uint8_t)0x0A)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF10_TIM16        ((uint8_t)0x0A)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF10_TIM17        ((uint8_t)0x0A)  /*!< TIM17 Alternate Function mapping */
/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_TIM1         ((uint8_t)0x0B)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF11_TIM3         ((uint8_t)0x0B)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF11_MCO2         ((uint8_t)0x0B)  /*!< MCO2 Alternate Function mapping */
/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_TIM3         ((uint8_t)0x0C)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF12_USART1       ((uint8_t)0x0C)  /*!< USART1 Alternate Function mapping */
/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_TIM14        ((uint8_t)0x0D)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF13_TIM3         ((uint8_t)0x0D)  /*!< TIM3 Alternate Function mapping */
/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_USART1      ((uint8_t)0x0E)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF14_I2C1        ((uint8_t)0x0E)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF14_TIM16       ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping */
/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping */
#define GPIO_AF15_MCO2          ((uint8_t)0x0F)  /*!< MCO2 Alternate Function mapping */
#define GPIO_AF15_TIM17         ((uint8_t)0x0F)  /*!< TIM17 Alternate Function mapping */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x0F)
#endif /* STM32C031xx */
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
#if defined(STM32C011xx)
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL :\
                                      ((__GPIOx__) == (GPIOB))? 1uL :\
                                      ((__GPIOx__) == (GPIOC))? 2uL :\
                                      ((__GPIOx__) == (GPIOF))? 3uL : 5uL)
#elif defined(STM32C031xx)
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL :\
                                      ((__GPIOx__) == (GPIOB))? 1uL :\
                                      ((__GPIOx__) == (GPIOC))? 2uL :\
                                      ((__GPIOx__) == (GPIOD))? 3uL :\
                                      ((__GPIOx__) == (GPIOF))? 4uL : 5uL)
#endif /* STM32C011xx */
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

#endif /* STM32C0xx_HAL_GPIO_EX_H */
