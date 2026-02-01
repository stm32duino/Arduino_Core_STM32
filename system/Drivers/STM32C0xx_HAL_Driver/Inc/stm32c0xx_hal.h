/**
  ******************************************************************************
  * @file    stm32c0xx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef STM32C0xx_HAL_H
#define STM32C0xx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_ll_system.h"
#include "stm32c0xx_hal_conf.h"

/** @addtogroup STM32C0xx_HAL_Driver
  * @{
  */

/** @defgroup HAL HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */

typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;

/**
  * @}
  */

/** @defgroup HAL_BIND_CFG  Bind Pin config
  * @{
  */

#if (DEV_ID == 0x443UL)
#define HAL_BIND_SO8_PIN1_PB7          LL_PINMUX_SO8_PIN1_PB7         /*!< STM32C011 SO8 package, Pin1 assigned to GPIO PB7 */
#define HAL_BIND_SO8_PIN1_PC14         LL_PINMUX_SO8_PIN1_PC14        /*!< STM32C011 SO8 package, Pin1 assigned to GPIO PC14 */
#define HAL_BIND_SO8_PIN4_PF2          LL_PINMUX_SO8_PIN4_PF2         /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PF2 */
#define HAL_BIND_SO8_PIN4_PA0          LL_PINMUX_SO8_PIN4_PA0         /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PA0 */
#define HAL_BIND_SO8_PIN4_PA1          LL_PINMUX_SO8_PIN4_PA1         /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PA1 */
#define HAL_BIND_SO8_PIN4_PA2          LL_PINMUX_SO8_PIN4_PA2         /*!< STM32C011 SO8 package, Pin4 assigned to GPIO PA2 */
#define HAL_BIND_SO8_PIN5_PA8          LL_PINMUX_SO8_PIN5_PA8         /*!< STM32C011 SO8 package, Pin5 assigned to GPIO PA8*/
#define HAL_BIND_SO8_PIN5_PA11         LL_PINMUX_SO8_PIN5_PA11        /*!< STM32C011 SO8 package, Pin5 assigned to GPIO PA11 */
#define HAL_BIND_SO8_PIN8_PA14         LL_PINMUX_SO8_PIN8_PA14        /*!< STM32C011 SO8 package, Pin8 assigned to GPIO PA14 */
#define HAL_BIND_SO8_PIN8_PB6          LL_PINMUX_SO8_PIN8_PB6         /*!< STM32C011 SO8 package, Pin8 assigned to GPIO PB6 */
#define HAL_BIND_SO8_PIN8_PC15         LL_PINMUX_SO8_PIN8_PC15        /*!< STM32C011 SO8 package, Pin8 assigned to GPIO PC15 */
#define HAL_BIND_WLCSP12_PINE2_PA7     LL_PINMUX_WLCSP12_PINE2_PA7    /*!< STM32C011 WLCSP12 package, PinE2 assigned to GPIO PA7 */
#define HAL_BIND_WLCSP12_PINE2_PA12    LL_PINMUX_WLCSP12_PINE2_PA12   /*!< STM32C011 WLCSP12 package, PinE2 assigned to GPIO PA12*/
#define HAL_BIND_WLCSP12_PINF1_PA3     LL_PINMUX_WLCSP12_PINF1_PA3    /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA3 */
#define HAL_BIND_WLCSP12_PINF1_PA4     LL_PINMUX_WLCSP12_PINF1_PA4    /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA4 */
#define HAL_BIND_WLCSP12_PINF1_PA5     LL_PINMUX_WLCSP12_PINF1_PA5    /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA5 */
#define HAL_BIND_WLCSP12_PINF1_PA6     LL_PINMUX_WLCSP12_PINF1_PA6    /*!< STM32C011 WLCSP12 package, PinF1 assigned to GPIO PA6 */
#elif (DEV_ID == 0x453UL)
#define HAL_BIND_WLCSP14_PINF2_PA1     LL_PINMUX_WLCSP14_PINF2_PA1    /*!< STM32C031 WLCSP14 package, PinF2 assigned to GPIO PA1 */
#define HAL_BIND_WLCSP14_PINF2_PA2     LL_PINMUX_WLCSP14_PINF2_PA2    /*!< STM32C031 WLCSP14 package, PinF2 assigned to GPIO PA2 */
#define HAL_BIND_WLCSP14_PING3_PF2     LL_PINMUX_WLCSP14_PING3_PF2    /*!< STM32C031 WLCSP14 package, PinG3 assigned to GPIO PF2 */
#define HAL_BIND_WLCSP14_PING3_PA0     LL_PINMUX_WLCSP14_PING3_PA0    /*!< STM32C031 WLCSP14 package, PinG3 assigned to GPIO PA0 */
#define HAL_BIND_WLCSP14_PINJ1_PA8     LL_PINMUX_WLCSP14_PINJ1_PA8    /*!< STM32C031 WLCSP14 package, PinJ1 assigned to GPIO PA8 */
#define HAL_BIND_WLCSP14_PINJ1_PA11    LL_PINMUX_WLCSP14_PINJ1_PA11   /*!< STM32C031 WLCSP14 package, PinJ1 assigned to GPIO PA11 */
#define HAL_BIND_WLCSP14_PINH2_PA5     LL_PINMUX_WLCSP14_PINH2_PA5    /*!< STM32C031 WLCSP14 package, PinH2 assigned to GPIO PA5 */
#define HAL_BIND_WLCSP14_PINH2_PA6     LL_PINMUX_WLCSP14_PINH2_PA6    /*!< STM32C031 WLCSP14 package, PinH2 assigned to GPIO PA6 */
#define HAL_BIND_WLCSP14_PING1_PA7     LL_PINMUX_WLCSP14_PING1_PA7    /*!< STM32C031 WLCSP14 package, PinG1 assigned to GPIO PA7 */
#define HAL_BIND_WLCSP14_PING1_PA12    LL_PINMUX_WLCSP14_PING1_PA12   /*!< STM32C031 WLCSP14 package, PinG1 assigned to GPIO PA12 */
#define HAL_BIND_WLCSP14_PINJ3_PA3     LL_PINMUX_WLCSP14_PINJ3_PA3    /*!< STM32C031 WLCSP14 package, PinJ3 assigned to GPIO PA3 */
#define HAL_BIND_WLCSP14_PINJ3_PA4     LL_PINMUX_WLCSP14_PINJ3_PA4    /*!< STM32C031 WLCSP14 package, PinJ3 assigned to GPIO PA4 */
#elif (DEV_ID == 0x493UL)
#define HAL_BIND_WLCSP19_PINH3_PF2     LL_PINMUX_WLCSP19_PINH3_PF2    /*!< STM32C071 WLCSP19 package, PinH3 assigned to GPIO PF2 */
#define HAL_BIND_WLCSP19_PINH3_PA0     LL_PINMUX_WLCSP19_PINH3_PA0    /*!< STM32C071 WLCSP19 package, PinH3 assigned to GPIO PA0 */
#define HAL_BIND_WLCSP19_PINB1_PA14    LL_PINMUX_WLCSP19_PINB1_PA14   /*!< STM32C071 WLCSP19 package, PinB1 assigned to GPIO PA14 */
#define HAL_BIND_WLCSP19_PINB1_PA15    LL_PINMUX_WLCSP19_PINB1_PA15   /*!< STM32C071 WLCSP19 package, PinB1 assigned to GPIO PA15 */
#define HAL_BIND_TSSOP20_PIN19_PA14    LL_PINMUX_TSSOP20_PIN19_PA14
#define HAL_BIND_TSSOP20_PIN19_PA15    LL_PINMUX_TSSOP20_PIN19_PA15
#define HAL_BIND_TSSOP20_PIN20_PB6     LL_PINMUX_TSSOP20_PIN20_PB6    /*!< STM32C071 TSSOP20 package, Pin20 assigned to GPIO PB6 */
#define HAL_BIND_TSSOP20_PIN20_PB3     LL_PINMUX_TSSOP20_PIN20_PB3    /*!< STM32C071 TSSOP20 package, Pin20 assigned to GPIO PB3 */
#define HAL_BIND_TSSOP20_PIN20_PB4     LL_PINMUX_TSSOP20_PIN20_PB4    /*!< STM32C071 TSSOP20 package, Pin20 assigned to GPIO PB4 */
#define HAL_BIND_TSSOP20_PIN20_PB5     LL_PINMUX_TSSOP20_PIN20_PB5    /*!< STM32C071 TSSOP20 package, Pin20 assigned to GPIO PB5 */
#define HAL_BIND_WLCSP19_PINB3_PB      LL_PINMUX_WLCSP19_PINB3_PB7    /*!< STM32C071 WLCSP19 package, PinH2 assigned to GPIO PB7 */
#define HAL_BIND_WLCSP19_PINB3_PB8     LL_PINMUX_WLCSP19_PINB3_PB8    /*!< STM32C071 WLCSP19 package, PinH2 assigned to GPIO PB8 */
#define HAL_BIND_TSSOP20_PIN1_PB7      LL_PINMUX_TSSOP20_PIN1_PB7     /*!< STM32C071 TSSOP20 package, Pin1 assigned to GPIO PB7 */
#define HAL_BIND_TSSOP20_PIN1_PB8      LL_PINMUX_TSSOP20_PIN1_PB8     /*!< STM32C071 TSSOP20 package, Pin1 assigned to GPIO PB8 */
#elif (DEV_ID == 0x44CUL)
#define HAL_BIND_WLCSP15_PINH3_PF2     LL_PINMUX_WLCSP15_PINH3_PF2    /*!< STM32C051 WLCSP15 package, PinH3 assigned to GPIO PF2 */
#define HAL_BIND_WLCSP15_PINH3_PA0     LL_PINMUX_WLCSP15_PINH3_PA0    /*!< STM32C051 WLCSP15 package, PinH3 assigned to GPIO PA0 */
#define HAL_BIND_WLCSP15_PING2_PA1     LL_PINMUX_WLCSP15_PING2_PA1    /*!< STM32C051 WLCSP15 package, PinG2 assigned to GPIO PA1 */
#define HAL_BIND_WLCSP15_PING2_PA2     LL_PINMUX_WLCSP15_PING2_PA2    /*!< STM32C051 WLCSP15 package, PinG2 assigned to GPIO PA2 */
#define HAL_BIND_WLCSP15_PINK3_PA3     LL_PINMUX_WLCSP15_PINK3_PA3    /*!< STM32C051 WLCSP15 package, PinK3 assigned to GPIO PA3 */
#define HAL_BIND_WLCSP15_PINK3_PA4     LL_PINMUX_WLCSP15_PINK3_PA4    /*!< STM32C051 WLCSP15 package, PinK3 assigned to GPIO PA4 */
#define HAL_BIND_WLCSP15_PINJ2_PA5     LL_PINMUX_WLCSP15_PINJ2_PA5    /*!< STM32C051 WLCSP15 package, PinJ2 assigned to GPIO PA5 */
#define HAL_BIND_WLCSP15_PINJ2_PA6     LL_PINMUX_WLCSP15_PINJ2_PA6    /*!< STM32C051 WLCSP15 package, PinJ2 assigned to GPIO PA6 */
#define HAL_BIND_WLCSP15_PINH1_PA7     LL_PINMUX_WLCSP15_PINH1_PA7    /*!< STM32C051 WLCSP15 package, PinH1 assigned to GPIO PA7 */
#define HAL_BIND_WLCSP15_PINH1_PA12    LL_PINMUX_WLCSP15_PINH1_PA12   /*!< STM32C051 WLCSP15 package, PinH1 assigned to GPIO PA12 */
#define HAL_BIND_WLCSP15_PINE2_PA14    LL_PINMUX_WLCSP15_PINE2_PA14   /*!< STM32C051 WLCSP15 package, PinE2 assigned to GPIO PA14 */
#define HAL_BIND_WLCSP15_PINE2_PA15    LL_PINMUX_WLCSP15_PINE2_PA15   /*!< STM32C051 WLCSP15 package, PinE2 assigned to GPIO PA15 */
#define HAL_BIND_WLCSP15_PINB1_PA3     LL_PINMUX_WLCSP15_PINB1_PA3    /*!< STM32C051 WLCSP15 package, PinB1 assigned to GPIO PA3 */
#define HAL_BIND_WLCSP15_PINB1_PA4     LL_PINMUX_WLCSP15_PINB1_PA4    /*!< STM32C051 WLCSP15 package, PinB1 assigned to GPIO PA4 */
#define HAL_BIND_WLCSP15_PINB1_PA5     LL_PINMUX_WLCSP15_PINB1_PA5    /*!< STM32C051 WLCSP15 package, PinB1 assigned to GPIO PA5 */
#define HAL_BIND_WLCSP15_PINB1_PA6     LL_PINMUX_WLCSP15_PINB1_PA6    /*!< STM32C051 WLCSP15 package, PinB1 assigned to GPIO PA6 */
#define HAL_BIND_WLCSP15_PINA2_PB7     LL_PINMUX_WLCSP15_PINA2_PB7    /*!< STM32C051 WLCSP15 package, PinA2 assigned to GPIO PB7 */
#define HAL_BIND_WLCSP15_PINA2_PB8     LL_PINMUX_WLCSP15_PINA2_PB8    /*!< STM32C051 WLCSP15 package, PinA2 assigned to GPIO PB8 */
#elif (DEV_ID == 0x44DUL)
#define HAL_BIND_TSSOP20_PIN19_PA14    LL_PINMUX_TSSOP20_PIN19_PA14   /*!< STM32C091/92 TSSOP20 package, Pin19 assigned to GPIO PA14 */
#define HAL_BIND_TSSOP20_PIN19_PA15    LL_PINMUX_TSSOP20_PIN19_PA15   /*!< STM32C091/92 TSSOP20 package, Pin19 assigned to GPIO PA15 */
#define HAL_BIND_TSSOP20_PIN15_PA8     LL_PINMUX_TSSOP20_PIN15_PA8    /*!< STM32C091/92 TSSOP20 package, Pin15 assigned to GPIO PA8 */
#define HAL_BIND_TSSOP20_PIN15_PB0     LL_PINMUX_TSSOP20_PIN15_PB0    /*!< STM32C091/92 TSSOP20 package, Pin15 assigned to GPIO PB0 */
#define HAL_BIND_TSSOP20_PIN15_PB1     LL_PINMUX_TSSOP20_PIN15_PB1    /*!< STM32C091/92 TSSOP20 package, Pin15 assigned to GPIO PB1 */
#define HAL_BIND_TSSOP20_PIN15_PB2     LL_PINMUX_TSSOP20_PIN15_PB2    /*!< STM32C091/92 TSSOP20 package, Pin15 assigned to GPIO PB2 */
#define HAL_BIND_TSSOP20_PIN20_PB6     LL_PINMUX_TSSOP20_PIN20_PB6    /*!< STM32C091/92 TSSOP20 package, Pin20 assigned to GPIO PB6 */
#define HAL_BIND_TSSOP20_PIN20_PB3     LL_PINMUX_TSSOP20_PIN20_PB3    /*!< STM32C091/92 TSSOP20 package, Pin20 assigned to GPIO PB3 */
#define HAL_BIND_TSSOP20_PIN20_PB4     LL_PINMUX_TSSOP20_PIN20_PB4    /*!< STM32C091/92 TSSOP20 package, Pin20 assigned to GPIO PB4 */
#define HAL_BIND_TSSOP20_PIN20_PB5     LL_PINMUX_TSSOP20_PIN20_PB5    /*!< STM32C091/92 TSSOP20 package, Pin20 assigned to GPIO PB5 */
#define HAL_BIND_WLCSP24_PINA3_PB5     LL_PINMUX_WLCSP24_PINA3_PB5    /*!< STM32C091/92 WLCSP24 package, PinA3 assigned to GPIO PB5 */
#define HAL_BIND_WLCSP24_PINA3_PB3     LL_PINMUX_WLCSP24_PINA3_PB3    /*!< STM32C091/92 WLCSP24 package, PinA3 assigned to GPIO PB3 */
#define HAL_BIND_WLCSP24_PINB4_PB7     LL_PINMUX_WLCSP24_PINB4_PB7    /*!< STM32C091/92 WLCSP24 package, PinB4 assigned to GPIO PB7 */
#define HAL_BIND_WLCSP24_PINB4_PB8     LL_PINMUX_WLCSP24_PINB4_PB8    /*!< STM32C091/92 WLCSP24 package, PinB4 assigned to GPIO PB8 */
#endif /* DEV_ID == 0x443UL */

/**
  * @}
  */

/** @defgroup HAL_BIND_SCOURCE  Bind Pin Source
  * @{
  */
#if (DEV_ID == 0x443UL)
#define HAL_BIND_SO8_PIN1                LL_PINMUX_SO8_PIN1          /*!< STM32C011 SO8 package, GPIO Pin1 multiplexer */
#define HAL_BIND_SO8_PIN4                LL_PINMUX_SO8_PIN4          /*!< STM32C011 SO8 package, GPIO Pin4 multiplexer */
#define HAL_BIND_SO8_PIN5                LL_PINMUX_SO8_PIN5          /*!< STM32C011 SO8 package, GPIO Pin5 multiplexer */
#define HAL_BIND_SO8_PIN8                LL_PINMUX_SO8_PIN8          /*!< STM32C011 SO8 package, GPIO Pin8 multiplexer */
#define HAL_BIND_WLCSP12_PINE2           LL_PINMUX_WLCSP12_PINE2     /*!< STM32C011 WLCSP12 package, GPIO PinE2 multiplexer */
#define HAL_BIND_WLCSP12_PINF1           LL_PINMUX_WLCSP12_PINF1     /*!< STM32C011 WLCSP12 package, GPIO PinF1 multiplexer */
#elif (DEV_ID == 0x453UL)
#define HAL_BIND_WLCSP14_PINF2           LL_PINMUX_WLCSP14_PINF2     /*!< STM32C031 WLCSP14 package, GPIO PinF2 multiplexer */
#define HAL_BIND_WLCSP14_PING3           LL_PINMUX_WLCSP14_PING3     /*!< STM32C031 WLCSP14 package, GPIO PinG3 multiplexer */
#define HAL_BIND_WLCSP14_PINJ1           LL_PINMUX_WLCSP14_PINJ1     /*!< STM32C031 WLCSP14 package, GPIO PinJ1 multiplexer */
#define HAL_BIND_WLCSP14_PINH2           LL_PINMUX_WLCSP14_PINH2     /*!< STM32C031 WLCSP14 package, GPIO PinH2 multiplexer */
#define HAL_BIND_WLCSP14_PING1           LL_PINMUX_WLCSP14_PING1     /*!< STM32C031 WLCSP14 package, GPIO PinG1 multiplexer */
#define HAL_BIND_WLCSP14_PINJ3           LL_PINMUX_WLCSP14_PINJ3     /*!< STM32C031 WLCSP14 package, GPIO PinJ3 multiplexer */
#elif (DEV_ID == 0x493UL)
#define  HAL_BIND_WLCSP19_PINH3          LL_PINMUX_WLCSP19_PINH3     /*!< STM32C071 WLCSP19 package, GPIO PinH3 multiplexer  */
#define  HAL_BIND_WLCSP19_PINB1          LL_PINMUX_WLCSP19_PINB1     /*!< STM32C071 WLCSP19 package, GPIO PinB1 multiplexer  */
#define  HAL_BIND_TSSOP20_PIN19          LL_PINMUX_TSSOP20_PIN19     /*!< STM32C071 TSSOP20 package, GPIO Pin19 multiplexer  */
#define  HAL_BIND_TSSOP20_PIN20          LL_PINMUX_TSSOP20_PIN20     /*!< STM32C071 TSSOP20 package, GPIO Pin20 multiplexer  */
#define  HAL_BIND_WLCSP19_PINB3          LL_PINMUX_WLCSP19_PINB3     /*!< STM32C071 WLCSP19 package, GPIO PinB3 multiplexer  */
#define  HAL_BIND_TSSOP20_PIN1           LL_PINMUX_TSSOP20_PIN1      /*!< STM32C071 TSSOP20 package, GPIO Pin1 multiplexer   */
#elif (DEV_ID == 0x44CUL)
#define  HAL_BIND_WLCSP15_PINH3          LL_PINMUX_WLCSP15_PINH3     /*!< STM32C051 WLCSP15 package, GPIO PinH3 multiplexer  */
#define  HAL_BIND_WLCSP15_PING2          LL_PINMUX_WLCSP15_PING2     /*!< STM32C051 WLCSP15 package, GPIO PinG2 multiplexer  */
#define  HAL_BIND_WLCSP15_PINK3          LL_PINMUX_WLCSP15_PINK3     /*!< STM32C051 WLCSP15 package, GPIO PinK3 multiplexer  */
#define  HAL_BIND_WLCSP15_PINJ2          LL_PINMUX_WLCSP15_PINJ2     /*!< STM32C051 WLCSP15 package, GPIO PinJ2 multiplexer  */
#define  HAL_BIND_WLCSP15_PINH1          LL_PINMUX_WLCSP15_PINH1     /*!< STM32C051 WLCSP15 package, GPIO PinH1 multiplexer  */
#define  HAL_BIND_WLCSP15_PINE2          LL_PINMUX_WLCSP15_PINE2     /*!< STM32C051 WLCSP15 package, GPIO PinE2 multiplexer  */
#define  HAL_BIND_WLCSP15_PINB1          LL_PINMUX_WLCSP15_PINB1     /*!< STM32C051 WLCSP15 package, GPIO PinB1 multiplexer  */
#define  HAL_BIND_WLCSP15_PINA2          LL_PINMUX_WLCSP15_PINA2     /*!< STM32C051 WLCSP15 package, GPIO PinA2 multiplexer  */
#elif (DEV_ID == 0x44DUL)
#define  HAL_BIND_TSSOP20_PIN19          LL_PINMUX_TSSOP20_PIN19     /*!< STM32C051 WLCSP15 package, GPIO PinH3 multiplexer  */
#define  HAL_BIND_TSSOP20_PIN15          LL_PINMUX_TSSOP20_PIN15     /*!< STM32C051 WLCSP15 package, GPIO PinG2 multiplexer  */
#define  HAL_BIND_TSSOP20_PIN20          LL_PINMUX_TSSOP20_PIN20     /*!< STM32C051 WLCSP15 package, GPIO PinK3 multiplexer  */
#define  HAL_BIND_WLCSP24_PINA3          LL_PINMUX_WLCSP24_PINA3     /*!< STM32C051 WLCSP15 package, GPIO PinJ2 multiplexer  */
#define  HAL_BIND_WLCSP24_PINB4          LL_PINMUX_WLCSP24_PINB4     /*!< STM32C051 WLCSP15 package, GPIO PinH1 multiplexer  */
#endif /* DEV_ID == 0x443UL */
/**
  * @}
 */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_BootMode Boot Mode
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH          0x00000000U                      /*!< Main Flash memory mapped at 0x0000 0000   */
#define SYSCFG_BOOT_SYSTEMFLASH        SYSCFG_CFGR1_MEM_MODE_0          /*!< System Flash memory mapped at 0x0000 0000 */
#define SYSCFG_BOOT_SRAM               (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0)  /*!< Embedded SRAM mapped at 0x0000 0000 */

/**
  * @}
  */

/** @defgroup SYSCFG_Break Break
  * @{
  */
#define SYSCFG_BREAK_LOCKUP            SYSCFG_CFGR2_CLL    /*!< Enables and locks the LOCKUP output of CortexM0+ with Break Input of TIM1/16/17 */
/**
  * @}
  */

/** @defgroup HAL_Pin_remapping Pin remapping
  * @{
  */
#define SYSCFG_REMAP_PA11                   SYSCFG_CFGR1_PA11_RMP       /*!< PA11 pad behaves digitally as PA9 GPIO pin */
#define SYSCFG_REMAP_PA12                   SYSCFG_CFGR1_PA12_RMP       /*!< PA12 pad behaves digitally as PA10 GPIO pin */
/**
  * @}
  */

/** @defgroup HAL_IR_ENV_SEL IR Modulation Envelope signal selection
  * @{
  */
#define HAL_SYSCFG_IRDA_ENV_SEL_TIM16     (SYSCFG_CFGR1_IR_MOD_0 & SYSCFG_CFGR1_IR_MOD_1)    /*!< 00: Timer16 is selected as IR Modulation envelope source */
#define HAL_SYSCFG_IRDA_ENV_SEL_USART1    (SYSCFG_CFGR1_IR_MOD_0)                            /*!< 01: USART1 is selected as IR Modulation envelope source */
#define HAL_SYSCFG_IRDA_ENV_SEL_USART2    (SYSCFG_CFGR1_IR_MOD_1)                            /*!< 10: USART2 is selected as IR Modulation envelope source */

/**
  * @}
  */

/** @defgroup HAL_IR_POL_SEL IR output polarity selection
  * @{
  */
#define HAL_SYSCFG_IRDA_POLARITY_NOT_INVERTED     0x00000000U                                /*!< 00: IR output polarity not inverted */
#define HAL_SYSCFG_IRDA_POLARITY_INVERTED         SYSCFG_CFGR1_IR_POL                        /*!< 01: IR output polarity inverted */

/**
  * @}
  */
/** @defgroup SYSCFG_FastModePlus_GPIO Fast mode Plus on GPIO
  * @{
  */

/** @brief  Fast mode Plus driving capability on a specific GPIO
  */
#define SYSCFG_FASTMODEPLUS_PB6        SYSCFG_CFGR1_I2C_PB6_FMP  /*!< Enable Fast mode Plus on PB6 */
#define SYSCFG_FASTMODEPLUS_PB7        SYSCFG_CFGR1_I2C_PB7_FMP  /*!< Enable Fast mode Plus on PB7 */
#define SYSCFG_FASTMODEPLUS_PB8        SYSCFG_CFGR1_I2C_PB8_FMP  /*!< Enable Fast mode Plus on PB8 */
#define SYSCFG_FASTMODEPLUS_PB9        SYSCFG_CFGR1_I2C_PB9_FMP  /*!< Enable Fast mode Plus on PB9 */
#define SYSCFG_FASTMODEPLUS_PA9        SYSCFG_CFGR1_I2C_PA9_FMP  /*!< Enable Fast mode Plus on PA9 */
#define SYSCFG_FASTMODEPLUS_PA10       SYSCFG_CFGR1_I2C_PA10_FMP /*!< Enable Fast mode Plus on PA10 */
#define SYSCFG_FASTMODEPLUS_PC14       SYSCFG_CFGR1_I2C_PC14_FMP /*!< Enable Fast mode Plus on PC14 */
/**
  * @}
  */

/** @defgroup SYSCFG_FastModePlus_I2Cx Fast mode Plus driving capability activation for I2Cx
  * @{
  */

/** @brief  Fast mode Plus driving capability on a specific GPIO
  */
#define SYSCFG_FASTMODEPLUS_I2C1       SYSCFG_CFGR1_I2C1_FMP /*!< Enable Fast mode Plus on I2C1 */
#if defined(I2C2)
#define SYSCFG_FASTMODEPLUS_I2C2       SYSCFG_CFGR1_I2C2_FMP /*!< Enable Fast mode Plus on I2C2 */
#endif /* I2C2 */
/**
  * @}
  */

/** @defgroup HAL_ISR_Wrapper HAL ISR Wrapper
  * @brief ISR Wrapper
  * @{
  */
#define HAL_SYSCFG_ITLINE0                           0x00000000U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE2                           0x00000002U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE3                           0x00000003U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE4                           0x00000004U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE5                           0x00000005U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE6                           0x00000006U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE7                           0x00000007U /*!< Internal define for macro handling */
#if defined(USB_DRD_FS)
#define HAL_SYSCFG_ITLINE8                           0x00000008U /*!< Internal define for macro handling */
#endif /* USB */
#define HAL_SYSCFG_ITLINE9                           0x00000009U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE10                          0x0000000AU /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE11                          0x0000000BU /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE12                          0x0000000CU /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE13                          0x0000000DU /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE14                          0x0000000EU /*!< Internal define for macro handling */
#if defined(TIM2)
#define HAL_SYSCFG_ITLINE15                          0x0000000FU /*!< Internal define for macro handling */
#endif /* TIM2 */
#define HAL_SYSCFG_ITLINE16                          0x00000010U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE19                          0x00000013U /*!< Internal define for macro handling */
#if defined(TIM15)
#define HAL_SYSCFG_ITLINE20                          0x00000014U /*!< Internal define for macro handling */
#endif /* TIM15 */
#define HAL_SYSCFG_ITLINE21                          0x00000015U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE22                          0x00000016U /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE23                          0x00000017U /*!< Internal define for macro handling */
#if defined(I2C2)
#define HAL_SYSCFG_ITLINE24                          0x00000018U /*!< Internal define for macro handling */
#endif /* I2C2 */
#define HAL_SYSCFG_ITLINE25                          0x00000019U /*!< Internal define for macro handling */
#if defined(SPI2)
#define HAL_SYSCFG_ITLINE26                          0x0000001AU /*!< Internal define for macro handling */
#endif /* SPI2 */
#define HAL_SYSCFG_ITLINE27                          0x0000001BU /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE28                          0x0000001CU /*!< Internal define for macro handling */
#if defined(USART3)
#define HAL_SYSCFG_ITLINE29                          0x0000001DU /*!< Internal define for macro handling */
#endif /* USART3 */
#if defined(FDCAN1)
#define HAL_SYSCFG_ITLINE30                          0x0000001EU /*!< Internal define for macro handling */
#define HAL_SYSCFG_ITLINE31                          0x0000001FU /*!< Internal define for macro handling */
#endif /* FDCAN1 */

#define HAL_ITLINE_WWDG           ((HAL_SYSCFG_ITLINE0 << 0x18U) | SYSCFG_ITLINE0_SR_WWDG)          /*!< WWDG Interrupt */
#define HAL_ITLINE_RTC            ((HAL_SYSCFG_ITLINE2 << 0x18U) | SYSCFG_ITLINE2_SR_RTC)           /*!< RTC  Interrupt */
#define HAL_ITLINE_FLASH_ITF      ((HAL_SYSCFG_ITLINE3 << 0x18U) | SYSCFG_ITLINE3_SR_FLASH_ITF)     /*!< Flash ITF Interrupt */
#define HAL_ITLINE_CLK_CTRL       ((HAL_SYSCFG_ITLINE4 << 0x18U) | SYSCFG_ITLINE4_SR_CLK_CTRL)      /*!< CLK Control Interrupt */
#if defined(CRS)
#define HAL_ITLINE_CRS            ((HAL_SYSCFG_ITLINE4 << 0x18U) | SYSCFG_ITLINE4_SR_CRS)           /*!< CRS Interrupt */
#endif /* CRS */
#define HAL_ITLINE_EXTI0          ((HAL_SYSCFG_ITLINE5 << 0x18U) | SYSCFG_ITLINE5_SR_EXTI0)         /*!< External Interrupt 0 */
#define HAL_ITLINE_EXTI1          ((HAL_SYSCFG_ITLINE5 << 0x18U) | SYSCFG_ITLINE5_SR_EXTI1)         /*!< External Interrupt 1 */
#define HAL_ITLINE_EXTI2          ((HAL_SYSCFG_ITLINE6 << 0x18U) | SYSCFG_ITLINE6_SR_EXTI2)         /*!< External Interrupt 2 */
#define HAL_ITLINE_EXTI3          ((HAL_SYSCFG_ITLINE6 << 0x18U) | SYSCFG_ITLINE6_SR_EXTI3)         /*!< External Interrupt 3 */
#define HAL_ITLINE_EXTI4          ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI4)         /*!< EXTI4 Interrupt */
#define HAL_ITLINE_EXTI5          ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI5)         /*!< EXTI5 Interrupt */
#define HAL_ITLINE_EXTI6          ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI6)         /*!< EXTI6 Interrupt */
#define HAL_ITLINE_EXTI7          ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI7)         /*!< EXTI7 Interrupt */
#define HAL_ITLINE_EXTI8          ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI8)         /*!< EXTI8 Interrupt */
#define HAL_ITLINE_EXTI9          ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI9)         /*!< EXTI9 Interrupt */
#define HAL_ITLINE_EXTI10         ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI10)        /*!< EXTI10 Interrupt */
#define HAL_ITLINE_EXTI11         ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI11)        /*!< EXTI11 Interrupt */
#define HAL_ITLINE_EXTI12         ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI12)        /*!< EXTI12 Interrupt */
#define HAL_ITLINE_EXTI13         ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI13)        /*!< EXTI13 Interrupt */
#define HAL_ITLINE_EXTI14         ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI14)        /*!< EXTI14 Interrupt */
#define HAL_ITLINE_EXTI15         ((HAL_SYSCFG_ITLINE7 << 0x18U) | SYSCFG_ITLINE7_SR_EXTI15)        /*!< EXTI15 Interrupt */
#if defined(USB_DRD_FS)
#define HAL_ITLINE_USB            ((HAL_SYSCFG_ITLINE8 << 0x18U) | SYSCFG_ITLINE8_SR_USB)           /*!< USB Interrupt */
#endif /* USB */
#define HAL_ITLINE_DMA1_CH1       ((HAL_SYSCFG_ITLINE9 << 0x18U) | SYSCFG_ITLINE9_SR_DMA1_CH1)      /*!< DMA1 Channel 1 Interrupt */
#define HAL_ITLINE_DMA1_CH2       ((HAL_SYSCFG_ITLINE10 << 0x18U) | SYSCFG_ITLINE10_SR_DMA1_CH2)    /*!< DMA1 Channel 2 Interrupt */
#define HAL_ITLINE_DMA1_CH3       ((HAL_SYSCFG_ITLINE10 << 0x18U) | SYSCFG_ITLINE10_SR_DMA1_CH3)    /*!< DMA1 Channel 3 Interrupt */
#define HAL_ITLINE_DMAMUX         ((HAL_SYSCFG_ITLINE11 << 0x18U) | SYSCFG_ITLINE11_SR_DMAMUX)      /*!< DMAMUX Interrupt */
#if defined(SYSCFG_ITLINE11_SR_DMA1_CH4)
#define HAL_ITLINE_DMA1_CH4       ((HAL_SYSCFG_ITLINE11 << 0x18U) | SYSCFG_ITLINE11_SR_DMA1_CH4)    /*!< DMA1 Channel 4 Interrupt */
#endif /* SYSCFG_ITLINE11_SR_DMA1_CH4 */
#if defined(SYSCFG_ITLINE11_SR_DMA1_CH5)
#define HAL_ITLINE_DMA1_CH5       ((HAL_SYSCFG_ITLINE11 << 0x18U) | SYSCFG_ITLINE11_SR_DMA1_CH5)    /*!< DMA1 Channel 5 Interrupt */
#endif /* SYSCFG_ITLINE11_SR_DMA1_CH5 */
#if defined(SYSCFG_ITLINE11_SR_DMA1_CH6)
#define HAL_ITLINE_DMA1_CH6       ((HAL_SYSCFG_ITLINE11 << 0x18U) | SYSCFG_ITLINE11_SR_DMA1_CH6)    /*!< DMA1 Channel 6 Interrupt */
#endif /* SYSCFG_ITLINE11_SR_DMA1_CH6 */
#if defined(SYSCFG_ITLINE11_SR_DMA1_CH7)
#define HAL_ITLINE_DMA1_CH7       ((HAL_SYSCFG_ITLINE11 << 0x18U) | SYSCFG_ITLINE11_SR_DMA1_CH7)    /*!< DMA1 Channel 7 Interrupt */
#endif /* SYSCFG_ITLINE11_SR_DMA1_CH7 */
#define HAL_ITLINE_ADC            ((HAL_SYSCFG_ITLINE12 << 0x18U) | SYSCFG_ITLINE12_SR_ADC)         /*!< ADC Interrupt */
#define HAL_ITLINE_TIM1_BRK       ((HAL_SYSCFG_ITLINE13 << 0x18U) | SYSCFG_ITLINE13_SR_TIM1_BRK)    /*!< TIM1 BRK Interrupt */
#define HAL_ITLINE_TIM1_UPD       ((HAL_SYSCFG_ITLINE13 << 0x18U) | SYSCFG_ITLINE13_SR_TIM1_UPD)    /*!< TIM1 UPD Interrupt */
#define HAL_ITLINE_TIM1_TRG       ((HAL_SYSCFG_ITLINE13 << 0x18U) | SYSCFG_ITLINE13_SR_TIM1_TRG)    /*!< TIM1 TRG Interrupt */
#define HAL_ITLINE_TIM1_CCU       ((HAL_SYSCFG_ITLINE13 << 0x18U) | SYSCFG_ITLINE13_SR_TIM1_CCU)    /*!< TIM1 CCU Interrupt */
#define HAL_ITLINE_TIM1_CC        ((HAL_SYSCFG_ITLINE14 << 0x18U) | SYSCFG_ITLINE14_SR_TIM1_CC)     /*!< TIM1 CC Interrupt */
#if defined(TIM2)
#define HAL_ITLINE_TIM2           ((HAL_SYSCFG_ITLINE15 << 0x18U) | SYSCFG_ITLINE15_SR_TIM2)        /*!< TIM2 Interrupt */
#endif /* TIM2 */
#define HAL_ITLINE_TIM3           ((HAL_SYSCFG_ITLINE16 << 0x18U) | SYSCFG_ITLINE16_SR_TIM3_GLB)    /*!< TIM3 Interrupt */
#define HAL_ITLINE_TIM14          ((HAL_SYSCFG_ITLINE19 << 0x18U) | SYSCFG_ITLINE19_SR_TIM14_GLB)   /*!< TIM14 Interrupt */
#if defined(TIM15)
#define HAL_ITLINE_TIM15          ((HAL_SYSCFG_ITLINE20 << 0x18U) | SYSCFG_ITLINE20_SR_TIM15_GLB)   /*!< TIM15 Interrupt */
#endif /* TIM15 */
#define HAL_ITLINE_TIM16          ((HAL_SYSCFG_ITLINE21 << 0x18U) | SYSCFG_ITLINE21_SR_TIM16_GLB)   /*!< TIM16 Interrupt */
#define HAL_ITLINE_TIM17          ((HAL_SYSCFG_ITLINE22 << 0x18U) | SYSCFG_ITLINE22_SR_TIM17_GLB)   /*!< TIM17 Interrupt */
#define HAL_ITLINE_I2C1           ((HAL_SYSCFG_ITLINE23 << 0x18U) | SYSCFG_ITLINE23_SR_I2C1_GLB)    /*!< I2C1 Interrupt */
#if defined(I2C2)
#define HAL_ITLINE_I2C2           ((HAL_SYSCFG_ITLINE24 << 0x18U) | SYSCFG_ITLINE24_SR_I2C2_GLB)    /*!< I2C1 Interrupt */
#endif /* I2C2 */
#define HAL_ITLINE_SPI1           ((HAL_SYSCFG_ITLINE25 << 0x18U) | SYSCFG_ITLINE25_SR_SPI1)        /*!< SPI1 Interrupt */
#if defined(SPI2)
#define HAL_ITLINE_SPI2           ((HAL_SYSCFG_ITLINE26 << 0x18U) | SYSCFG_ITLINE25_SR_SPI2)        /*!< SPI1 Interrupt */
#endif /* SPI2 */
#define HAL_ITLINE_USART1         ((HAL_SYSCFG_ITLINE27 << 0x18U) | SYSCFG_ITLINE27_SR_USART1_GLB)  /*!< USART1 GLB Interrupt */
#define HAL_ITLINE_USART2         ((HAL_SYSCFG_ITLINE28 << 0x18U) | SYSCFG_ITLINE28_SR_USART2_GLB)  /*!< USART2 GLB Interrupt */
#if defined(USART3)
#define HAL_ITLINE_USART3         ((HAL_SYSCFG_ITLINE29 << 0x18U) | SYSCFG_ITLINE29_SR_USART3_GLB)  /*!< USART3 GLB Interrupt */
#endif /* USART3 */
#if defined(USART4)
#define HAL_ITLINE_USART4         ((HAL_SYSCFG_ITLINE29 << 0x18U) | SYSCFG_ITLINE29_SR_USART4_GLB)  /*!< USART4 GLB Interrupt */
#endif /* USART4 */
#if defined(FDCAN1)
#define HAL_ITLINE_FDCAN1_IT0     ((HAL_SYSCFG_ITLINE30 << 0x18U) | SYSCFG_ITLINE30_SR_FDCAN1_IT0_GLB)  /*!< FDCAN1_IT0 GLB Interrupt */
#define HAL_ITLINE_FDCAN1_IT1     ((HAL_SYSCFG_ITLINE31 << 0x18U) | SYSCFG_ITLINE31_SR_FDCAN1_IT1_GLB)  /*!< FDCAN1_IT1 GLB Interrupt */
#endif /* FDCAN1 */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @defgroup DBG_Exported_Macros DBG Exported Macros
  * @{
  */

/** @brief  Freeze and Unfreeze Peripherals in Debug mode
  */

#if defined(DBG_APB_FZ1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_FREEZE_TIM2()           SET_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()         CLEAR_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_TIM2_STOP)
#endif /* DBG_APB_FZ1_DBG_TIM2_STOP */

#if defined(DBG_APB_FZ1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_FREEZE_TIM3()           SET_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM3()         CLEAR_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_TIM3_STOP)
#endif /* DBG_APB_FZ1_DBG_TIM3_STOP */

#if defined(DBG_APB_FZ1_DBG_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC()            SET_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()          CLEAR_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_RTC_STOP)
#endif /* DBG_APB_FZ1_DBG_RTC_STOP */

#if defined(DBG_APB_FZ1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_FREEZE_WWDG()           SET_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_WWDG()         CLEAR_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_WWDG_STOP)
#endif /* DBG_APB_FZ1_DBG_RTC_STOP */

#if defined(DBG_APB_FZ1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG()           SET_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()         CLEAR_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_IWDG_STOP)
#endif /* DBG_APB_FZ1_DBG_IWDG_STOP */

#if defined(DBG_APB_FZ1_DBG_I2C1_SMBUS_TIMEOUT_STOP)
#define __HAL_DBGMCU_FREEZE_I2C1_TIMEOUT()   SET_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_I2C1_SMBUS_TIMEOUT_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1_TIMEOUT() CLEAR_BIT(DBG->APBFZ1, DBG_APB_FZ1_DBG_I2C1_SMBUS_TIMEOUT_STOP)
#endif /* DBG_APB_FZ1_DBG_I2C1_SMBUS_TIMEOUT_STOP */

#if defined(DBG_APB_FZ2_DBG_TIM1_STOP)
#define __HAL_DBGMCU_FREEZE_TIM1()           SET_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM1()         CLEAR_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM1_STOP)
#endif /* DBG_APB_FZ2_DBG_TIM1_STOP */

#if defined(DBG_APB_FZ2_DBG_TIM14_STOP)
#define __HAL_DBGMCU_FREEZE_TIM14()          SET_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM14_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM14()        CLEAR_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM14_STOP)
#endif /* DBG_APB_FZ2_DBG_TIM14_STOP */

#if defined(DBG_APB_FZ2_DBG_TIM15_STOP)
#define __HAL_DBGMCU_FREEZE_TIM15()          SET_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM15_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM15()        CLEAR_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM15_STOP)
#endif /* DBG_APB_FZ2_DBG_TIM15_STOP */

#if defined(DBG_APB_FZ2_DBG_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16()          SET_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM16_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM16()        CLEAR_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM16_STOP)
#endif /* DBG_APB_FZ2_DBG_TIM16_STOP */

#if defined(DBG_APB_FZ2_DBG_TIM17_STOP)
#define __HAL_DBGMCU_FREEZE_TIM17()          SET_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM17_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM17()        CLEAR_BIT(DBG->APBFZ2, DBG_APB_FZ2_DBG_TIM17_STOP)
#endif /* DBG_APB_FZ2_DBG_TIM17_STOP */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/**
  * @brief ISR wrapper check
  * @note Allow to determine interrupt source per line.
  */
#define __HAL_GET_PENDING_IT(__SOURCE__)     (SYSCFG->IT_LINE_SR[((__SOURCE__) >> 0x18U)] & ((__SOURCE__) & 0x00FFFFFF))

/** @brief  Main Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()       CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE)

/** @brief  System Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH() MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, SYSCFG_CFGR1_MEM_MODE_0)

/** @brief  Embedded SRAM mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SRAM() \
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0))

/**
  * @brief  Return the boot mode as configured by user.
  * @retval The boot mode as configured by user. The returned value can be one
  *         of the following values @ref SYSCFG_BootMode
  */
#define __HAL_SYSCFG_GET_BOOT_MODE()           READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE)

/** @brief  SYSCFG Break Cortex-M0+ Lockup lock.
  *         Enables and locks the connection of Cortex-M0+ LOCKUP (Hardfault) output to TIM1/16/17 Break input
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL)

/** @brief  Fast-mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__ This parameter can be a value of @ref SYSCFG_FastModePlus_GPIO
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__)  \
  do { \
    assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    SET_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0U)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) \
  do { \
    assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    CLEAR_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0U)


/** @brief  selection of the modulation envelope signal macro, using bits [7:6] of SYSCFG_CFGR1 register
  * @param __SOURCE__ This parameter can be a value of @ref HAL_IR_ENV_SEL
  */
#define __HAL_SYSCFG_IRDA_ENV_SELECTION(__SOURCE__)  do {assert_param(IS_HAL_SYSCFG_IRDA_ENV_SEL((__SOURCE__)));\
                                                          CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_MOD);\
                                                          SET_BIT(SYSCFG->CFGR1, (__SOURCE__));\
                                                        }while(0U)

#define __HAL_SYSCFG_GET_IRDA_ENV_SELECTION()  ((SYSCFG->CFGR1) & 0x000000C0U)

/** @brief  IROut Polarity Selection, using bit[5] of SYSCFG_CFGR1 register
  * @param __SEL__ This parameter can be a value of @ref HAL_IR_POL_SEL
  */
#define __HAL_SYSCFG_IRDA_OUT_POLARITY_SELECTION(__SEL__)  do { assert_param(IS_HAL_SYSCFG_IRDA_POL_SEL((__SEL__)));\
                                                                 CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_POL);\
                                                                 SET_BIT(SYSCFG->CFGR1,(__SEL__));\
                                                              }while(0U)

/**
  * @brief  Return the IROut Polarity mode as configured by user.
  * @retval The IROut polarity as configured by user. The returned value can be one
  *         of @ref HAL_IR_POL_SEL
  */
#define __HAL_SYSCFG_GET_POLARITY()           READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_POL)

/** @brief  Break input to TIM1/16/17 capability enable/disable macros
  * @param __BREAK__ This parameter can be a value of @ref SYSCFG_Break
  */
#define __HAL_SYSCFG_BREAK_ENABLE(__BREAK__)     do {assert_param(IS_SYSCFG_BREAK_CONFIG((__BREAK__)));\
                                                      SET_BIT(SYSCFG->CFGR2, (__BREAK__));\
                                                    }while(0U)

#define __HAL_SYSCFG_BREAK_DISABLE(__BREAK__)    do {assert_param(IS_SYSCFG_BREAK_CONFIG((__BREAK__)));\
                                                      CLEAR_BIT(SYSCFG->CFGR2, (__BREAK__));\
                                                    }while(0U)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

#define IS_SYSCFG_BREAK_CONFIG(__CONFIG__) ((__CONFIG__) == SYSCFG_BREAK_LOCKUP)

#define IS_HAL_SYSCFG_IRDA_ENV_SEL(SEL)   (((SEL) == HAL_SYSCFG_IRDA_ENV_SEL_TIM16)   || \
                                           ((SEL) == HAL_SYSCFG_IRDA_ENV_SEL_USART1)  || \
                                           ((SEL) == HAL_SYSCFG_IRDA_ENV_SEL_USART2))

#define IS_HAL_SYSCFG_IRDA_POL_SEL(SEL)   (((SEL) == HAL_SYSCFG_IRDA_POLARITY_NOT_INVERTED)   || \
                                           ((SEL) == HAL_SYSCFG_IRDA_POLARITY_INVERTED))


#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_PC14) == SYSCFG_FASTMODEPLUS_PC14)  || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA9)  == SYSCFG_FASTMODEPLUS_PA9)  || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PA10) == SYSCFG_FASTMODEPLUS_PA10) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB6)  == SYSCFG_FASTMODEPLUS_PB6)  || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7)  == SYSCFG_FASTMODEPLUS_PB7)  || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB8)  == SYSCFG_FASTMODEPLUS_PB8)  || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB9)  == SYSCFG_FASTMODEPLUS_PB9))

#define IS_HAL_REMAP_PIN(RMP)               (((RMP) == SYSCFG_REMAP_PA11) || \
                                             ((RMP) == SYSCFG_REMAP_PA12) || \
                                             ((RMP) == (SYSCFG_REMAP_PA11 | SYSCFG_REMAP_PA12)))
#if (DEV_ID == 0x443UL)
#define IS_HAL_SYSCFG_PINBINDING(PIN) (((PIN) == HAL_BIND_SO8_PIN1_PB7)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN1_PC14) || \
                                       ((PIN) == HAL_BIND_SO8_PIN4_PF2)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN4_PA0)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN4_PA1)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN4_PA2)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN5_PA8) || \
                                       ((PIN) == HAL_BIND_SO8_PIN5_PA11)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN8_PA14)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN8_PB6)  || \
                                       ((PIN) == HAL_BIND_SO8_PIN8_PC15) || \
                                       ((PIN) == HAL_BIND_WLCSP12_PINE2_PA7)  || \
                                       ((PIN) == HAL_BIND_WLCSP12_PINE2_PA12) || \
                                       ((PIN) == HAL_BIND_WLCSP12_PINF1_PA3)  || \
                                       ((PIN) == HAL_BIND_WLCSP12_PINF1_PA4)  || \
                                       ((PIN) == HAL_BIND_WLCSP12_PINF1_PA5)  || \
                                       ((PIN) == HAL_BIND_WLCSP12_PINF1_PA6))
#elif (DEV_ID == 0x453UL)
#define IS_HAL_SYSCFG_PINBINDING(PIN) (((PIN) == HAL_BIND_WLCSP14_PINF2_PA1) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PINF2_PA2) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PING3_PF2) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PING3_PA0) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PINJ1_PA8) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PINJ1_PA11) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PINH2_PA5) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PINH2_PA6) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PING1_PA7) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PING1_PA12)|| \
                                       ((PIN) == HAL_BIND_WLCSP14_PINJ3_PA3) || \
                                       ((PIN) == HAL_BIND_WLCSP14_PINJ3_PA4))
#elif (DEV_ID == 0x493UL)
#define IS_HAL_SYSCFG_PINBINDING(PIN) (((PIN) == LL_PINMUX_WLCSP19_PINH3_PF2) || \
                                       ((PIN) == LL_PINMUX_WLCSP19_PINH3_PA0) || \
                                       ((PIN) == LL_PINMUX_WLCSP19_PINB1_PA14) || \
                                       ((PIN) == LL_PINMUX_WLCSP19_PINB1_PA15) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB6) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB3) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB4) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB5) || \
                                       ((PIN) == LL_PINMUX_WLCSP19_PINB3_PB7) || \
                                       ((PIN) == LL_PINMUX_WLCSP19_PINB3_PB8))
#elif (DEV_ID == 0x44CUL)
#define IS_HAL_SYSCFG_PINBINDING(PIN) (((PIN) == LL_PINMUX_WLCSP15_PINH3_PF2) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINH3_PA0) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PING2_PA1) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PING2_PA2) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINK3_PA3) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINK3_PA4) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINJ2_PA5) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINJ2_PA6) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINH1_PA7) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINH1_PA12) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINE2_PA14) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINE2_PA15) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINB1_PA3) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINB1_PA4) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINB1_PA5) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINB1_PA6) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINA2_PB7) || \
                                       ((PIN) == LL_PINMUX_WLCSP15_PINA2_PB8))
#elif (DEV_ID == 0x44DUL)
#define IS_HAL_SYSCFG_PINBINDING(PIN) (((PIN) == LL_PINMUX_TSSOP20_PIN19_PA14) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN19_PA15) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN15_PA8) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN15_PB0) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN15_PB1) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN15_PB2) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB6) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB3) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB4) || \
                                       ((PIN) == LL_PINMUX_TSSOP20_PIN20_PB5) || \
                                       ((PIN) == LL_PINMUX_WLCSP24_PINA3_PB5) || \
                                       ((PIN) == LL_PINMUX_WLCSP24_PINA3_PB3) || \
                                       ((PIN) == LL_PINMUX_WLCSP24_PINB4_PB7) || \
                                       ((PIN) == LL_PINMUX_WLCSP24_PINB4_PB8))
#endif /* DEV_ID == 0x443UL | DEV_ID == 0x453UL | DEV_ID == 0x493UL | DEV_ID == 0x44CUL | DEV_ID == 0x44DUL */
/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 HAL Initialization and Configuration functions
  * @{
  */

/* Initialization and Configuration functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group2 HAL Control functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group3 DBGMCU Control functions
  * @{
  */

/* DBGMCU Peripheral Control functions  *****************************************/
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);

/**
  * @}
  */

/* Exported variables ---------------------------------------------------------*/
/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern __IO uint32_t        uwTick;
extern uint32_t             uwTickPrio;
extern HAL_TickFreqTypeDef  uwTickFreq;
/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group4 SYSCFG configuration functions
  * @{
  */

/* SYSCFG Control functions  ****************************************************/
void HAL_SYSCFG_EnableRemap(uint32_t PinRemap);
void HAL_SYSCFG_DisableRemap(uint32_t PinRemap);
void HAL_SYSCFG_SetPinBinding(uint32_t pin_binding);
uint32_t HAL_SYSCFG_GetPinBinding(uint32_t pin_binding_source);
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

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32C0xx_HAL_H */
