/**
  ******************************************************************************
  * @file    stm32wl3x_hal_gpio_ex.h
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
#ifndef STM32WL3x_HAL_GPIO_EX_H
#define STM32WL3x_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_def.h"

/** @addtogroup STM32WL3x_HAL_Driver
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

#if defined(STM32WL3XX) || defined(STM32WL3RX)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_LCO           ((uint8_t)0x00)  /*!< LCO Alternate Function mapping                 */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /*!< SWCLK Alternate Function mapping               */
#define GPIO_AF0_I2C1          ((uint8_t)0x00)  /*!< I2C1 Alternate Function mapping                */
#define GPIO_AF0_I2C2          ((uint8_t)0x00)  /*!< I2C2 Alternate Function mapping                */
#define GPIO_AF0_RTC           ((uint8_t)0x00)  /*!< RTC Alternate Function mapping                 */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART Alternate Function mapping               */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /*!< SPI1 Alternate Function mapping                */

/**
  * @brief   AF 1 selection
  */

#define GPIO_AF1_SWDIO         ((uint8_t)0x01)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF1_SWCLK         ((uint8_t)0x01)  /*!< SWCLK Alternate Function mapping               */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART Alternate Function mapping               */
#define GPIO_AF1_LPUART1       ((uint8_t)0x01)  /*!< LPUART Alternate Function mapping              */

/**
  * @brief   AF 2 selection
  */

#define GPIO_AF2_COMP1          ((uint8_t)0x02)  /*!< COMP1 Alternate Function mapping               */
#define GPIO_AF2_LC_ACTIVITY    ((uint8_t)0x02)  /*!< LC_ACTIVITY Alternate Function mapping         */
#define GPIO_AF2_LCO            ((uint8_t)0x02)  /*!< LCO Alternate Function mapping                 */
#define GPIO_AF2_RF_ACTIVITY    ((uint8_t)0x02)  /*!< RF_ACTIVITY Alternate Function mapping         */
#define GPIO_AF2_RTC            ((uint8_t)0x02)  /*!< RTC Alternate Function mapping                 */
#define GPIO_AF2_RX_SEQUENCE    ((uint8_t)0x02)  /*!< RX_SEQUENCE Alternate Function mapping         */
#define GPIO_AF2_TIM16          ((uint8_t)0x02)  /*!< TIM16 Alternate Function mapping               */
#define GPIO_AF2_TX_SEQUENCE    ((uint8_t)0x02)  /*!< TX_SEQUENCE Alternate Function mapping         */

/**
  * @brief   AF 3 selection
  */

#define GPIO_AF3_SPI1           ((uint8_t)0x03)  /*!< SPI1 Alternate Function mapping                */
#define GPIO_AF3_SPI3           ((uint8_t)0x03)  /*!< SPI3 Alternate Function mapping                */
#define GPIO_AF3_MCO            ((uint8_t)0x03)  /*!< MCO Alternate Function mapping                 */

/**
  * @brief   AF 4 selection
  */

#define GPIO_AF4_TIM2           ((uint8_t)0x04)  /*!< TIM2 Alternate Function mapping                */
#define GPIO_AF4_ANTENNA        ((uint8_t)0x04)  /*!< ANTENNA Alternate Function mapping             */
#define GPIO_AF4_SUBG           ((uint8_t)0x04)  /*!< SUBG Alternate Function mapping                */

/**
  * @brief   AF 5 selection
  */

#define GPIO_AF5_SWDIO         ((uint8_t)0x05)  /*!< SWDIO Alternate Function mapping               */
#define GPIO_AF5_SWCLK         ((uint8_t)0x05)  /*!< SWCLK Alternate Function mapping               */

/**
  * @brief   AF 6 selection
  */

#define GPIO_AF6_LCD            ((uint8_t)0x06)  /*!< LCD Alternate Function mapping                  */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x06)

#endif /* STM32WL3XX */


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

#endif /* STM32WL3x_HAL_GPIO_EX_H */
