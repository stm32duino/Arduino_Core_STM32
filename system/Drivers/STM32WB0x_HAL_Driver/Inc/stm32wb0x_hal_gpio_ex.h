/**
  ******************************************************************************
  * @file    stm32wb0x_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extended module.
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
#ifndef STM32WB0x_HAL_GPIO_EX_H
#define STM32WB0x_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal_def.h"

/** @addtogroup STM32WB0x_HAL_Driver
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


/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */

#if defined (STM32WB05) || defined (STM32WB09)
/**
  * @brief   AF 0 selection
  */

#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /*!< SWCLK Alternate Function mapping               */
#define GPIO_AF0_I2C1          ((uint8_t)0x00)  /*!< I2C1 Alternate Function mapping                */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /*!< LPUART1 Alternate Function mapping             */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART1 Alternate Function mapping              */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_IR_OUT        ((uint8_t)0x01)  /*!< IR_OUT Alternate Function mapping              */
#define GPIO_AF1_LCO           ((uint8_t)0x01)  /*!< LCO Alternate Function mapping                 */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART1 Alternate Function mapping              */
#define GPIO_AF1_LPUART1       ((uint8_t)0x01)  /*!< LPUART1 Alternate Function mapping             */
#define GPIO_AF1_TX_SEQUENCE   ((uint8_t)0x01)  /*!< TX Sequence Alternate Function mapping         */
#define GPIO_AF1_RTC           ((uint8_t)0x01)  /*!< RTC Alternate Function mapping                 */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_IR_OUT        ((uint8_t)0x02)  /*!< IR Alternate Function mapping                  */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping                */
#define GPIO_AF2_TIM16         ((uint8_t)0x02)  /*!< TIM16 Alternate Function mapping               */
#define GPIO_AF2_TIM17         ((uint8_t)0x02)  /*!< TIM17 Alternate Function mapping               */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02)  /*!< LPUART1 Alternate Function mapping             */
#define GPIO_AF2_USART1        ((uint8_t)0x02)  /*!< USART1 Alternate Function mapping              */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /*!< RTC Alternate Function mapping                 */
#define GPIO_AF2_TX_SEQUENCE   ((uint8_t)0x02)  /*!< TX_SEQUENCE Alternate Function mapping         */
#define GPIO_AF2_RX_SEQUENCE   ((uint8_t)0x02)  /*!< RX_SEQUENCE Alternate Function mapping         */

/**
  * @brief   AF 3 selection
  */

#define GPIO_AF3_SPI3           ((uint8_t)0x03)  /*!< SPI3 Alternate Function mapping               */
#define GPIO_AF3_TIM2           ((uint8_t)0x03)  /*!< TIM2 Alternate Function mapping               */
#define GPIO_AF3_LPUART1        ((uint8_t)0x03)  /*!< LPUART1 Alternate Function mapping            */
#define GPIO_AF3_MCO            ((uint8_t)0x03)  /*!< MCO Alternate Function mapping                */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_TIM2           ((uint8_t)0x04)  /*!< TIM2 Alternate Function mapping               */
#define GPIO_AF4_SPI3           ((uint8_t)0x04)  /*!< SPI3 Alternate Function mapping               */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SWDIO         ((uint8_t)0x05)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF5_SWCLK         ((uint8_t)0x05)  /*!< SWCLK Alternate Function mapping               */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_ANT           ((uint8_t)0x06)  /*!< ANT Alternate Function mapping                 */
#define GPIO_AF6_RXACTIVITY    ((uint8_t)0x06)  /*!< RXACTIVITY Alternate Function mapping          */
#define GPIO_AF6_TIM16         ((uint8_t)0x06)  /*!< TIM16 Alternate Function mapping               */
#define GPIO_AF6_TIM17         ((uint8_t)0x06)  /*!< TIM17 Alternate Function mapping               */
#define GPIO_AF6_USART1        ((uint8_t)0x06)  /*!< USART1 Alternate Function mapping              */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_SWDIO         ((uint8_t)0x07)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF7_SWCLK         ((uint8_t)0x07)  /*!< SWCLK Alternate Function mapping               */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

#endif /* STM32WB05 || STM32WB09 */


#if defined (STM32WB06) || defined (STM32WB07)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_I2C1          ((uint8_t)0x00)  /*!< I2C1 Alternate Function mapping               */
#define GPIO_AF0_I2C2          ((uint8_t)0x00)  /*!< I2C2 Alternate Function mapping               */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                */
#define GPIO_AF0_LCO           ((uint8_t)0x00)  /*!< LCO Alternate Function mapping                */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /*!< SWDIO Alternate Function mapping              */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /*!< SWCLK Alternate Function mapping              */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /*!< LPUART1 Alternate Function mapping            */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART1 Alternate Function mapping             */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /*!< SPI1 Alternate Function mapping               */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /*!< SPI1 Alternate Function mapping               */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /*!< SPI2 Alternate Function mapping               */
#define GPIO_AF1_SWDIO         ((uint8_t)0x01)  /*!< SWDIO Alternate Function mapping              */
#define GPIO_AF1_SWCLK         ((uint8_t)0x01)  /*!< SWCLK Alternate Function mapping              */
#define GPIO_AF1_I2C2          ((uint8_t)0x01)  /*!< I2C2 Alternate Function mapping               */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART1 Alternate Function mapping             */
#define GPIO_AF1_LPUART1       ((uint8_t)0x01)  /*!< LPUART1 Alternate Function mapping            */
#define GPIO_AF1_PDM           ((uint8_t)0x01)  /*!< PDM Alternate Function mapping                */
#define GPIO_AF1_LCO           ((uint8_t)0x01)  /*!< LCO Alternate Function mapping                */
#define GPIO_AF1_TX_SEQUENCE   ((uint8_t)0x01)  /*!< TX Sequence Alternate Function mapping        */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_SPI1          ((uint8_t)0x02)  /*!< SPI1 Alternate Function mapping                */
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /*!< SPI2 Alternate Function mapping                */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /*!< RTC Alternate Function mapping                 */
#define GPIO_AF2_USART1        ((uint8_t)0x02)  /*!< USART1 Alternate Function mapping              */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping                */
#define GPIO_AF2_I2C1          ((uint8_t)0x02)  /*!< I2C1 Alternate Function mapping                */
#define GPIO_AF2_PDM           ((uint8_t)0x02)  /*!< PDM Alternate Function mapping                 */
#define GPIO_AF2_MCO           ((uint8_t)0x02)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF2_TX_SEQUENCE   ((uint8_t)0x02)  /*!< TX_SEQUENCE Alternate Function mapping         */
#define GPIO_AF2_RX_SEQUENCE   ((uint8_t)0x02)  /*!< RX_SEQUENCE Alternate Function mapping         */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_SPI2           ((uint8_t)0x03)  /*!< SPI2 Alternate Function mapping               */
#define GPIO_AF3_SPI3           ((uint8_t)0x03)  /*!< SPI3 Alternate Function mapping               */
#define GPIO_AF3_LPUART1        ((uint8_t)0x03)  /*!< LPUART1 Alternate Function mapping            */
#define GPIO_AF3_TIM1           ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping               */
#define GPIO_AF3_PDM            ((uint8_t)0x03)  /*!< PDM Alternate Function mapping                */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_TIM1           ((uint8_t)0x04)  /*!< TIM1 Alternate Function mapping               */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SWDIO          ((uint8_t)0x05)  /*!< SWDIO Alternate Function mapping              */
#define GPIO_AF5_SWCLK          ((uint8_t)0x05)  /*!< SWCLK Alternate Function mapping              */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_SWDIO         ((uint8_t)0x07)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF7_SWCLK         ((uint8_t)0x07)  /*!< SWCLK Alternate Function mapping               */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping              */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

#endif /* STM32WB06 || STM32WB07 */

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
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL : 1uL)
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

#endif /* STM32WB0x_HAL_GPIO_EX_H */
