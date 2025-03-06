/**
  ******************************************************************************
  * @file    stm32u3xx_ll_bus.h
  * @author  MCD Application Team
  * @brief   Header file of BUS LL module.
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
  @verbatim
  ==============================================================================
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB , APB peripherals,  1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB , APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U3xx_LL_BUS_H
#define STM32U3xx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx.h"

/** @addtogroup STM32U3xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Constants BUS Exported Constants
  * @{
  */

/** @defgroup BUS_LL_EC_AHB1_GRP1_PERIPH  AHB1 GRP1 PERIPH
  * @{
  */
#define LL_AHB1_GRP1_PERIPH_GPDMA1        RCC_AHB1ENR1_GPDMA1EN
#define LL_AHB1_GRP1_PERIPH_ADF1          RCC_AHB1ENR1_ADF1EN
#if defined(HSP1)
#define LL_AHB1_GRP1_PERIPH_HSP1          RCC_AHB1ENR1_HSP1EN
#else
#define LL_AHB1_GRP1_PERIPH_HSP1          0
#endif /* #if defined(HSP1) */
#define LL_AHB1_GRP1_PERIPH_FLASH         RCC_AHB1ENR1_FLASHEN
#define LL_AHB1_GRP1_PERIPH_CRC           RCC_AHB1ENR1_CRCEN
#define LL_AHB1_GRP1_PERIPH_TSC           RCC_AHB1ENR1_TSCEN
#define LL_AHB1_GRP1_PERIPH_RAMCFG        RCC_AHB1ENR1_RAMCFGEN
#define LL_AHB1_GRP1_PERIPH_GTZC1         RCC_AHB1ENR1_GTZC1EN
#define LL_AHB1_GRP1_PERIPH_ICACHE        RCC_AHB1SLPENR1_ICACHESLPEN
#if defined(SRAM4)
#define LL_AHB1_GRP1_PERIPH_SRAM4         RCC_AHB1ENR1_SRAM4EN
#else
#define LL_AHB1_GRP1_PERIPH_SRAM4       0
#endif /* #if defined(SRAM4) */
#define LL_AHB1_GRP1_PERIPH_SRAM1         RCC_AHB1ENR1_SRAM1EN
#define LL_AHB1_GRP1_PERIPH_ALL           (LL_AHB1_GRP1_PERIPH_GPDMA1 | \
                                           LL_AHB1_GRP1_PERIPH_ADF1   | \
                                           LL_AHB1_GRP1_PERIPH_FLASH  | \
                                           LL_AHB1_GRP1_PERIPH_CRC    | \
                                           LL_AHB1_GRP1_PERIPH_TSC    | \
                                           LL_AHB1_GRP1_PERIPH_RAMCFG | \
                                           LL_AHB1_GRP1_PERIPH_GTZC1  | \
                                           LL_AHB1_GRP1_PERIPH_SRAM4  | \
                                           LL_AHB1_GRP1_PERIPH_SRAM1  )
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB1_GRP2_PERIPH  AHB1 GRP2 PERIPH
  * @{
  */
#define LL_AHB1_GRP2_PERIPH_PWR           RCC_AHB1ENR2_PWREN
#define LL_AHB1_GRP2_PERIPH_ALL           RCC_AHB1ENR2_PWREN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_GPIOA          RCC_AHB2ENR1_GPIOAEN
#define LL_AHB2_GRP1_PERIPH_GPIOB          RCC_AHB2ENR1_GPIOBEN
#define LL_AHB2_GRP1_PERIPH_GPIOC          RCC_AHB2ENR1_GPIOCEN
#define LL_AHB2_GRP1_PERIPH_GPIOD          RCC_AHB2ENR1_GPIODEN
#define LL_AHB2_GRP1_PERIPH_GPIOE          RCC_AHB2ENR1_GPIOEEN
#if defined(GPIOF)
#define LL_AHB2_GRP1_PERIPH_GPIOF          RCC_AHB2ENR1_GPIOFEN
#else
#define LL_AHB2_GRP1_PERIPH_GPIOF          0
#endif /* #if defined(GPIOF) */
#define LL_AHB2_GRP1_PERIPH_GPIOG          RCC_AHB2ENR1_GPIOGEN
#define LL_AHB2_GRP1_PERIPH_GPIOH          RCC_AHB2ENR1_GPIOHEN
#define LL_AHB2_GRP1_PERIPH_ADC12          RCC_AHB2ENR1_ADC12EN
#define LL_AHB2_GRP1_PERIPH_DAC1           RCC_AHB2ENR1_DAC1EN
#if defined(AES)
#define LL_AHB2_GRP1_PERIPH_AES            RCC_AHB2ENR1_AESEN
#else
#define LL_AHB2_GRP1_PERIPH_AES            0
#endif /* #if defined(AES) */
#if defined(HASH)
#define LL_AHB2_GRP1_PERIPH_HASH           RCC_AHB2ENR1_HASHEN
#else
#define LL_AHB2_GRP1_PERIPH_HASH           0
#endif /* #if defined(HASH) */
#if defined(RNG)
#define LL_AHB2_GRP1_PERIPH_RNG            RCC_AHB2ENR1_RNGEN
#else
#define LL_AHB2_GRP1_PERIPH_RNG            0
#endif /* #if defined(RNG) */
#if defined(PKA)
#define LL_AHB2_GRP1_PERIPH_PKA            RCC_AHB2ENR1_PKAEN
#else
#define LL_AHB2_GRP1_PERIPH_PKA            0
#endif /* #if defined(PKA) */
#if defined(SAES)
#define LL_AHB2_GRP1_PERIPH_SAES           RCC_AHB2ENR1_SAESEN
#else
#define LL_AHB2_GRP1_PERIPH_SAES           0
#endif /* #if defined(SAES) */
#if defined(CCB)
#define LL_AHB2_GRP1_PERIPH_CCB            RCC_AHB2ENR1_CCBEN
#else
#define LL_AHB2_GRP1_PERIPH_CCB            0
#endif /* #if defined(CCB) */
#define LL_AHB2_GRP1_PERIPH_SDMMC1         RCC_AHB2ENR1_SDMMC1EN
#define LL_AHB2_GRP1_PERIPH_SRAM2          RCC_AHB2ENR1_SRAM2EN
#if defined(SRAM3)
#define LL_AHB2_GRP1_PERIPH_SRAM3  RCC_AHB2ENR1_SRAM3EN
#else
#define LL_AHB2_GRP1_PERIPH_SRAM3       0
#endif /* #if defined(SRAM3) */
#define LL_AHB2_GRP1_PERIPH_ALL            (LL_AHB2_GRP1_PERIPH_GPIOA  |\
                                            LL_AHB2_GRP1_PERIPH_GPIOB  |\
                                            LL_AHB2_GRP1_PERIPH_GPIOC  |\
                                            LL_AHB2_GRP1_PERIPH_GPIOD  |\
                                            LL_AHB2_GRP1_PERIPH_GPIOE  |\
                                            LL_AHB2_GRP1_PERIPH_GPIOF  |\
                                            LL_AHB2_GRP1_PERIPH_GPIOG  |\
                                            LL_AHB2_GRP1_PERIPH_GPIOH  |\
                                            LL_AHB2_GRP1_PERIPH_ADC12  |\
                                            LL_AHB2_GRP1_PERIPH_DAC1   |\
                                            LL_AHB2_GRP1_PERIPH_AES    |\
                                            LL_AHB2_GRP1_PERIPH_HASH   |\
                                            LL_AHB2_GRP1_PERIPH_RNG    |\
                                            LL_AHB2_GRP1_PERIPH_PKA    |\
                                            LL_AHB2_GRP1_PERIPH_SAES   |\
                                            LL_AHB2_GRP1_PERIPH_CCB    |\
                                            LL_AHB2_GRP1_PERIPH_SDMMC1 |\
                                            LL_AHB2_GRP1_PERIPH_SRAM2  |\
                                            LL_AHB2_GRP1_PERIPH_SRAM3)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP2_PERIPH  AHB2 GRP2 PERIPH
  * @{
  */
#define LL_AHB2_GRP2_PERIPH_OCTOSPI1       RCC_AHB2ENR2_OCTOSPI1EN
#define LL_AHB2_GRP2_PERIPH_ALL            RCC_AHB2ENR2_OCTOSPI1EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_TIM2          RCC_APB1ENR1_TIM2EN
#define LL_APB1_GRP1_PERIPH_TIM3          RCC_APB1ENR1_TIM3EN
#define LL_APB1_GRP1_PERIPH_TIM4          RCC_APB1ENR1_TIM4EN
#define LL_APB1_GRP1_PERIPH_TIM6          RCC_APB1ENR1_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7          RCC_APB1ENR1_TIM7EN
#define LL_APB1_GRP1_PERIPH_SPI3          RCC_APB1ENR1_SPI3EN
#if defined(SPI4)
#define LL_APB1_GRP1_PERIPH_SPI4          RCC_APB1ENR1_SPI4EN
#else
#define LL_APB1_GRP1_PERIPH_SPI4          0
#endif /* #if defined(SPI4) */
#define LL_APB1_GRP1_PERIPH_WWDG          RCC_APB1ENR1_WWDGEN
#define LL_APB1_GRP1_PERIPH_SPI2          RCC_APB1ENR1_SPI2EN
#if defined(USART2)
#define LL_APB1_GRP1_PERIPH_USART2          RCC_APB1ENR1_USART2EN
#else
#define LL_APB1_GRP1_PERIPH_USART2          0
#endif /* #if defined(USART2) */
#define LL_APB1_GRP1_PERIPH_USART3        RCC_APB1ENR1_USART3EN
#define LL_APB1_GRP1_PERIPH_UART4         RCC_APB1ENR1_UART4EN
#define LL_APB1_GRP1_PERIPH_UART5         RCC_APB1ENR1_UART5EN
#define LL_APB1_GRP1_PERIPH_I2C1          RCC_APB1ENR1_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2          RCC_APB1ENR1_I2C2EN
#define LL_APB1_GRP1_PERIPH_I3C1          RCC_APB1ENR1_I3C1EN
#define LL_APB1_GRP1_PERIPH_CRS           RCC_APB1ENR1_CRSEN
#define LL_APB1_GRP1_PERIPH_OPAMP         RCC_APB1ENR1_OPAMPEN
#define LL_APB1_GRP1_PERIPH_VREF          RCC_APB1ENR1_VREFEN
#define LL_APB1_GRP1_PERIPH_RTCAPB        RCC_APB1ENR1_RTCAPBEN
#define LL_APB1_GRP1_PERIPH_ALL           ( LL_APB1_GRP1_PERIPH_TIM2             |\
                                            LL_APB1_GRP1_PERIPH_TIM3             |\
                                            LL_APB1_GRP1_PERIPH_TIM4             |\
                                            LL_APB1_GRP1_PERIPH_TIM6             |\
                                            LL_APB1_GRP1_PERIPH_TIM7             |\
                                            LL_APB1_GRP1_PERIPH_SPI3             |\
                                            LL_APB1_GRP1_PERIPH_SPI4             |\
                                            LL_APB1_GRP1_PERIPH_WWDG             |\
                                            LL_APB1_GRP1_PERIPH_SPI2             |\
                                            LL_APB1_GRP1_PERIPH_USART2           |\
                                            LL_APB1_GRP1_PERIPH_USART3           |\
                                            LL_APB1_GRP1_PERIPH_UART4            |\
                                            LL_APB1_GRP1_PERIPH_UART5            |\
                                            LL_APB1_GRP1_PERIPH_I2C1             |\
                                            LL_APB1_GRP1_PERIPH_I2C2             |\
                                            LL_APB1_GRP1_PERIPH_I3C1             |\
                                            LL_APB1_GRP1_PERIPH_CRS              |\
                                            LL_APB1_GRP1_PERIPH_OPAMP            |\
                                            LL_APB1_GRP1_PERIPH_VREF             |\
                                            LL_APB1_GRP1_PERIPH_RTCAPB           )
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#if defined(I2C4)
#define LL_APB1_GRP2_PERIPH_I2C4          RCC_APB1ENR2_I2C4EN
#else
#define LL_APB1_GRP2_PERIPH_I2C4          0
#endif /* #if defined(I2C4) */
#define LL_APB1_GRP2_PERIPH_LPTIM2         RCC_APB1ENR2_LPTIM2EN
#define LL_APB1_GRP2_PERIPH_FDCAN          RCC_APB1ENR2_FDCANEN
#define LL_APB1_GRP2_PERIPH_ALL            (LL_APB1_GRP2_PERIPH_I2C4 |\
                                            LL_APB1_GRP2_PERIPH_LPTIM2 |\
                                            LL_APB1_GRP2_PERIPH_FDCAN )
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_TIM1           RCC_APB2ENR_TIM1EN
#define LL_APB2_GRP1_PERIPH_SPI1           RCC_APB2ENR_SPI1EN
#if defined(TIM8)
#define LL_APB2_GRP1_PERIPH_TIM8           RCC_APB2ENR_TIM8EN
#else
#define LL_APB2_GRP1_PERIPH_TIM8           0
#endif /* #if defined(TIM8) */
#define LL_APB2_GRP1_PERIPH_USART1         RCC_APB2ENR_USART1EN
#if defined(TIM12)
#define LL_APB2_GRP1_PERIPH_TIM12           RCC_APB2ENR_TIM12EN
#else
#define LL_APB2_GRP1_PERIPH_TIM12           0
#endif /* #if defined(TIM12) */
#define LL_APB2_GRP1_PERIPH_TIM15          RCC_APB2ENR_TIM15EN
#define LL_APB2_GRP1_PERIPH_TIM16          RCC_APB2ENR_TIM16EN
#define LL_APB2_GRP1_PERIPH_TIM17          RCC_APB2ENR_TIM17EN
#define LL_APB2_GRP1_PERIPH_SAI1           RCC_APB2ENR_SAI1EN
#define LL_APB2_GRP1_PERIPH_USB1           RCC_APB2ENR_USB1EN
#define LL_APB2_GRP1_PERIPH_I3C2           RCC_APB2ENR_I3C2EN
#define LL_APB2_GRP1_PERIPH_ALL            (LL_APB2_GRP1_PERIPH_TIM1   |\
                                            LL_APB2_GRP1_PERIPH_SPI1   |\
                                            LL_APB2_GRP1_PERIPH_TIM8  |\
                                            LL_APB2_GRP1_PERIPH_USART1 |\
                                            LL_APB2_GRP1_PERIPH_TIM12  |\
                                            LL_APB2_GRP1_PERIPH_TIM15  |\
                                            LL_APB2_GRP1_PERIPH_TIM16  |\
                                            LL_APB2_GRP1_PERIPH_TIM17  |\
                                            LL_APB2_GRP1_PERIPH_SAI1   |\
                                            LL_APB2_GRP1_PERIPH_USB1   |\
                                            LL_APB2_GRP1_PERIPH_I3C2   )
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB3_GRP1_PERIPH  APB3 GRP1 PERIPH
  * @{
  */
#define LL_APB3_GRP1_PERIPH_SYSCFG        RCC_APB3ENR_SYSCFGEN
#define LL_APB3_GRP1_PERIPH_LPUART1       RCC_APB3ENR_LPUART1EN
#define LL_APB3_GRP1_PERIPH_I2C3          RCC_APB3ENR_I2C3EN
#define LL_APB3_GRP1_PERIPH_LPTIM1        RCC_APB3ENR_LPTIM1EN
#define LL_APB3_GRP1_PERIPH_LPTIM3        RCC_APB3ENR_LPTIM3EN
#define LL_APB3_GRP1_PERIPH_LPTIM4        RCC_APB3ENR_LPTIM4EN
#define LL_APB3_GRP1_PERIPH_COMP          RCC_APB3ENR_COMPEN
#define LL_APB3_GRP1_PERIPH_ALL           (LL_APB3_GRP1_PERIPH_SYSCFG  |\
                                           LL_APB3_GRP1_PERIPH_LPUART1 |\
                                           LL_APB3_GRP1_PERIPH_I2C3    |\
                                           LL_APB3_GRP1_PERIPH_LPTIM1  |\
                                           LL_APB3_GRP1_PERIPH_LPTIM3  |\
                                           LL_APB3_GRP1_PERIPH_LPTIM4  |\
                                           LL_APB3_GRP1_PERIPH_COMP    )

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Functions BUS Exported Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB1 AHB1
  * @{
  */
/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll AHB1ENR1    GPDMA1EN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    ADF1EN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    HSP1EN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    FLASHEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    CRCEN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    TSCEN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    RAMCFGEN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    GTZC1EN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    SRAM4EN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR1    SRAM1EN      LL_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1ENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1ENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled or not
  * @rmtoll AHB1ENR1         GPDMA1EN         LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         ADF1EN           LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         HSP1EN           LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         FLASHEN          LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         CRCEN            LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         TSCEN            LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         RAMCFGEN         LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         GTZC1EN          LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         SRAM4EN          LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR1         SRAM1EN          LL_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1ENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHB1ENR1    GPDMA1EN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    ADF1EN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    HSP1EN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    FLASHEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    CRCEN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    TSCEN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    RAMCFGEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    GTZC1EN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    SRAM4EN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR1    SRAM1EN      LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR1, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll AHB1RSTR1    GPDMA1RSTR     LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR1    ADF1RSTR       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR1    HSP1RST        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR1    CRCRSTR        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR1    TSCRSTR        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR1    RAMCFGRSTR     LL_AHB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR1, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll AHB1RSTR1    GPDMA1RSTR      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR1    ADF1RSTR        LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR1    HSP1RST         LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR1    CRCRSTR         LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR1    TSCRSTR         LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR1    RAMCFGRSTR      LL_AHB1_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR1, Periphs);
}

/**
  * @brief  Enable AHB1 peripheral clocks in Sleep mode
  * @rmtoll AHB1SLPENR1    GPDMA1EN     LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    ADFEN        LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    HSP1SLPEN    LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    FLASHEN      LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    CRCEN        LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    TSCEN        LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    RAMCFGEN     LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    GTZC1EN      LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    ICACHESLPEN  LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1STPENR1    SRAM4EN      LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SLPENR1    SRAM1EN      LL_AHB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ICACHE
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1SLPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1SLPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll AHB1SLPENR1    GPDMA1SLPEN     LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    ADF1SLPEN       LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    HSP1SLPEN       LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    FLASHSLPEN      LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    CRCSLPEN        LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    TSCSLPEN        LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    RAMCFGSLPEN     LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    GTZC1SLPEN      LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    ICACHESLPEN     LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    SRAM4SLPEN      LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SLPENR1    SRAM1SLPEN      LL_AHB1_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ICACHE
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1SLPENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripheral clocks in Sleep mode
  * @rmtoll AHB1SLPENR1    GPDMA1SLPEN     LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    ADF1SLPEN       LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    HSP1SLPEN       LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    FLASHSLPEN      LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    CRCSLPEN        LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    TSCSLPEN        LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    RAMCFGSLPEN     LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    GTZC1SLPEN      LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    ICACHESLPEN     LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    SRAM4SLPEN      LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SLPENR1    SRAM1SLPEN      LL_AHB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ICACHE
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  CLEAR_BIT(RCC->AHB1SLPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1SLPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable AHB1 peripheral clocks in Stop mode
  * @rmtoll AHB1SLPENR1    GPDMA1STPEN     LL_AHB1_GRP1_EnableClockStop\n
  *         AHB1SLPENR1    ADF1STPEN       LL_AHB1_GRP1_EnableClockStop\n
  *         AHB1SLPENR1    FLASHSTPEN      LL_AHB1_GRP1_EnableClockStop\n
  *         AHB1SLPENR1    RAMCFGSTPEN     LL_AHB1_GRP1_EnableClockStop\n
  *         AHB1SLPENR1    GTZC1STPEN      LL_AHB1_GRP1_EnableClockStop\n
  *         AHB1STPENR1    SRAM4STPEN      LL_AHB1_GRP1_EnableClockStop\n
  *         AHB1SLPENR1    SRAM1STPEN      LL_AHB1_GRP1_EnableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1STPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1STPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clocks in Stop mode is enabled or not
  * @rmtoll AHB1SLPENR1   GPDMA1STPEN     LL_AHB1_GRP1_IsEnabledClockStop\n
  *         AHB1SLPENR1   ADF1STPEN       LL_AHB1_GRP1_IsEnabledClockStop\n
  *         AHB1SLPENR1   FLASHSTPEN      LL_AHB1_GRP1_IsEnabledClockStop\n
  *         AHB1SLPENR1   RAMCFGSTPEN     LL_AHB1_GRP1_IsEnabledClockStop\n
  *         AHB1SLPENR1   GTZC1STPEN      LL_AHB1_GRP1_IsEnabledClockStop\n
  *         AHB1STPENR1   SRAM4STPEN      LL_AHB1_GRP1_IsEnabledClockStop\n
  *         AHB1SLPENR1   SRAM1STPEN      LL_AHB1_GRP1_IsEnabledClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockStop(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1STPENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripheral clocks in Stop mode
  * @rmtoll AHB1SLPENR1    GPDMA1STPEN     LL_AHB1_GRP1_DisableClockStop\n
  *         AHB1SLPENR1    ADF1STPEN       LL_AHB1_GRP1_DisableClockStop\n
  *         AHB1SLPENR1    FLASHSTPEN      LL_AHB1_GRP1_DisableClockStop\n
  *         AHB1SLPENR1    RAMCFGSTPEN     LL_AHB1_GRP1_DisableClockStop\n
  *         AHB1SLPENR1    GTZC1STPEN      LL_AHB1_GRP1_DisableClockStop\n
  *         AHB1STPENR1    SRAM4STPEN      LL_AHB1_GRP1_DisableClockStop\n
  *         AHB1SLPENR1    SRAM1STPEN      LL_AHB1_GRP1_DisableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM4 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  CLEAR_BIT(RCC->AHB1STPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1STPENR1, Periphs);
  (void)tmpreg;
}


/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll AHB1ENR2    PWREN        LL_AHB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP2_PERIPH_PWR
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1ENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1ENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled or not
  * @rmtoll AHB1ENR2    PWREN        LL_AHB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP2_PERIPH_PWR
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1ENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHB1ENR2    PWREN        LL_AHB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP2_PERIPH_PWR
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR2, Periphs);
}

/**
  * @brief  Enable AHB1 peripheral clocks in Sleep mode
  * @rmtoll AHB1SLPENR2    PWRSLPEN        LL_AHB1_GRP2_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP2_PERIPH_PWR
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP2_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1SLPENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1SLPENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll AHB1SLPENR2    PWRSLPEN        LL_AHB1_GRP2_IsEnabledClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP2_PERIPH_PWR
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP2_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1SLPENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripheral clocks in Sleep mode
  * @rmtoll AHB1SLPENR2    PWRSLPEN        LL_AHB1_GRP2_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP2_PERIPH_PWR
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP2_DisableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  CLEAR_BIT(RCC->AHB1SLPENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1SLPENR2, Periphs);
  (void)tmpreg;
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2_GRP1_PERIPH AHB2 GRP1 PERIPH
  * @{
  */
/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR1      GPIOAEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOBEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOCEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIODEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOEEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOFEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOGEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOHEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      ADC12EN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      DAC1EN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      AESEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      HASHEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      RNGEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      PKAEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SAESEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      CCBEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SDMMC1EN      LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SRAM2EN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SRAM3EN       LL_AHB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2ENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2ENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled or not
  * @rmtoll AHB2ENR1      GPIOAEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOBEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOCEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIODEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOEEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOFEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOGEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOHEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      ADC12EN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      DAC1EN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      AESEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      HASHEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      RNGEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      PKAEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      SAESEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      CCBEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      SDMMC1EN      LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      SRAM2EN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      SRAM3EN       LL_AHB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll AHB2ENR1      GPIOAEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOBEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOCEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIODEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOEEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOFEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOGEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOHEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      ADC12EN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      DAC1EN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      AESEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      HASHEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      RNGEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      PKAEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      SAESEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      CCBEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      SDMMC1EN      LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      SRAM2EN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      SRAM3EN       LL_AHB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR1, Periphs);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll AHB2RSTR1      GPIOARST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      GPIOBRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      GPIOCRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      GPIODRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      GPIOERST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      GPIOFRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      GPIOGRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      GPIOHRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      ADC12RST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      DAC1RST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      AESRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      HASHRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      RNGRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      PKARST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      SAESRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      CCBRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1      SDMMC1RST     LL_AHB2_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR1, Periphs);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll AHB2RSTR1      GPIOARST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      GPIOBRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      GPIOCRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      GPIODRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      GPIOERST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      GPIOFRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      GPIOGRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      GPIOHRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      ADC12RST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      DAC1RST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      AESRST         LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      HASHRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      RNGRST         LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      PKARST         LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      SAESRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      CCBRST         LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1      SDMMC1RST      LL_AHB2_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR1, Periphs);
}

/**
  * @brief  Enable AHB2 peripheral clocks in Sleep mode
  * @rmtoll AHB2SLPENR1      GPIOASLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      GPIOBSLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      GPIOCSLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      GPIODSLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      GPIOESLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      GPIOFSLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      GPIOGSLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      GPIOHSLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      ADC12SLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      DAC1SLPEN     LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      AESSLPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      HASHSLPEN     LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      RNGSLPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      PKASLPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      SAESSLPEN     LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      CCBSLPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      SDMMC1SLPEN   LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      SRAM2SLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SLPENR1      SRAM3SLPEN    LL_AHB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2SLPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2SLPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll AHB2SLPENR1      GPIOASLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      GPIOBSLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      GPIOCSLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      GPIODSLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      GPIOESLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      GPIOFSLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      GPIOGSLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      GPIOHSLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      ADC12SLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      DAC1SLPEN        LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      AESSLPEN         LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      HASHSLPEN        LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      RNGSLPEN         LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      PKASLPEN         LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      SAESSLPEN        LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      CCBSLPEN         LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      SDMMC1SLPEN      LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      SRAM2SLPEN       LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SLPENR1      SRAM3SLPEN       LL_AHB2_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2SLPENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripheral clocks in Sleep mode
  * @rmtoll AHB2SLPENR1      GPIOASLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      GPIOBSLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      GPIOCSLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      GPIODSLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      GPIOESLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      GPIOFSLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      GPIOGSLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      GPIOHSLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      ADC12SLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      DAC1SLPEN        LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      AESSLPEN         LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      HASHSLPEN        LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      RNGSLPEN         LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      PKASLPEN         LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      SAESSLPEN        LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      CCBSLPEN         LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      SDMMC1SLPEN      LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      SRAM2SLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SLPENR1      SRAM3SLPEN       LL_AHB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2SLPENR1, Periphs);
}

/**
  * @brief  Enable AHB2 peripheral clocks in Stop mode
  * @rmtoll AHB2STPENR1      GPIOASTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      GPIOBSTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      GPIOCSTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      GPIODSTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      GPIOESTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      GPIOFSTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      GPIOGSTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      GPIOHSTPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      DAC1STPEN        LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      SRAM2STPEN       LL_AHB2_GRP1_EnableClockStop\n
  *         AHB2STPENR1      SRAM3STPEN       LL_AHB2_GRP1_EnableClockStop\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2STPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2STPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clocks in Stop mode is enabled or not
  * @rmtoll AHB2STPENR1      GPIOASTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      GPIOBSTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      GPIOCSTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      GPIODSTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      GPIOESTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      GPIOFSTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      GPIOGSTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      GPIOHSTPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      DAC1STPEN        LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      SRAM2STPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  *         AHB2STPENR1      SRAM3STPEN       LL_AHB2_GRP1_IsEnabledClockStop\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClockStop(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2STPENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripheral clocks in Stop mode
  * @rmtoll AHB2STPENR1      GPIOASTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      GPIOBSTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      GPIOCSTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      GPIODSTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      GPIOESTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      GPIOFSTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      GPIOGSTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      GPIOHSTPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      DAC1STPEN        LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      SRAM2STPEN       LL_AHB2_GRP1_DisableClockStop\n
  *         AHB2STPENR1      SRAM3STPEN       LL_AHB2_GRP1_DisableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockStop(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2STPENR1, Periphs);
}


/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR2    OCTOSPI1EN        LL_AHB2_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2ENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2ENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled or not
  * @rmtoll AHB2ENR2    OCTOSPI1EN        LL_AHB2_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll AHB2ENR2    OCTOSPI1EN        LL_AHB2_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR2, Periphs);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll AHB2RSTR2    OCTOSPI1RST        LL_AHB2_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR2, Periphs);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll AHB2RSTR2    OCTOSPI1RST        LL_AHB2_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR2, Periphs);
}

/**
  * @brief  Enable AHB2 peripheral clocks in Sleep mode
  * @rmtoll AHB2SLPENR2    OCTOSPI1EN        LL_AHB2_GRP2_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2SLPENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2SLPENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll AHB2SLPENR2    OCTOSPI1SLPEN        LL_AHB2_GRP2_IsEnabledClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP2_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2SLPENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripheral clocks in Sleep mode
  * @rmtoll AHB2SLPENR2    OCTOSPI1SLPEN        LL_AHB2_GRP2_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_DisableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  CLEAR_BIT(RCC->AHB2SLPENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2SLPENR2, Periphs);
  (void)tmpreg;
}

/**
  * @}
  */


/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPI3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPI4EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I3C1EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     CRSEN         LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     OPAMPEN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     VREFEN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     RTCAPBEN      LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1ENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1ENR2     LPTIM2EN      LL_APB1_GRP2_EnableClock
  *         APB1ENR2     FDCANEN       LL_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1ENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPI3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPI4EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I3C1EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     CRSEN         LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     OPAMPEN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     VREFEN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     RTCAPBEN      LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR2     LPTIM2EN      LL_APB1_GRP2_IsEnabledClock
  *         APB1ENR2     FDCANEN       LL_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPI3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPI4EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I3C1EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     CRSEN         LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     OPAMPEN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     VREFEN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     RTCAPBEN      LL_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR1, Periphs);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR2     I2C4EN        LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     FDCANEN       LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR2, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR1     TIM2RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM3RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM4RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM6RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM7RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     SPI3RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     SPI4RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     SPI2RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     USART2RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     USART3RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     UART4RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     UART5RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     I2C1RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     I2C2RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     I3C1RST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     CRSRST         LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     OPAMPRST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     VREFRST        LL_APB1_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR2     I2C4RST        LL_APB1_GRP2_ForceReset\n
  *         APB1RSTR2     LPTIM2RST      LL_APB1_GRP2_ForceReset\n
  *         APB1RSTR2     FDCANRST       LL_APB1_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR1     TIM2RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM3RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM4RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM6RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM7RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     SPI3RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     SPI4RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     SPI2RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     USART2RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     USART3RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     UART4RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     UART5RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     I2C1RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     I2C2RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     I3C1RST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     CRSRST         LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     OPAMPRST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     VREFRST        LL_APB1_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR2     I2C4RST        LL_APB1_GRP2_ReleaseReset\n
  *         APB1RSTR2     LPTIM2RST      LL_APB1_GRP2_ReleaseReset\n
  *         APB1RSTR2     FDCANRST       LL_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Enable APB1 peripheral clocks in Sleep mode
  * @rmtoll APB1SLPENR1     TIM2SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     TIM3SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     TIM4SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     TIM6SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     TIM7SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     SPI3SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     SPI4SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     WWDGSLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     SPI2SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     USART2SLPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     USART3SLPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     UART4SLPEN       LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     UART5SLPEN       LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     I2C1SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     I2C2SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     I3C1SLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     CRSSLPEN         LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     OPAMPSLPEN       LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     VREFSLPEN        LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SLPENR1     RTCAPBSLPEN      LL_APB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SLPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SLPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable APB1 peripheral clocks in Sleep mode
  * @rmtoll APB1SLPENR2     I2C4SLPEN        LL_APB1_GRP2_EnableClockSleep\n
  *         APB1SLPENR2     LPTIM2SLPEN      LL_APB1_GRP2_EnableClockSleep\n
  *         APB1SLPENR2     FDCANSLPEN       LL_APB1_GRP2_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SLPENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SLPENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll APB1SLPENR1     TIM2SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     TIM3SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     TIM4SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     TIM6SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     TIM7SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     SPI3SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     SPI4SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     WWDGSLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     SPI2SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     USART2SLPEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     USART3SLPEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     UART4SLPEN       LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     UART5SLPEN       LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     I2C1SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     I2C2SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     I3C1SLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     CRSSLPEN         LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     OPAMPSLPEN       LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     VREFSLPEN        LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SLPENR1     RTCAPBSLPEN      LL_APB1_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *        (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SLPENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Check if APB1 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll APB1SLPENR2     I2C4SLPEN        LL_APB1_GRP2_IsEnabledClockSleep\n
  *         APB1SLPENR2     LPTIM2SLPEN      LL_APB1_GRP2_IsEnabledClockSleep\n
  *         APB1SLPENR2     FDCANSLPEN       LL_APB1_GRP2_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SLPENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripheral clocks in Sleep mode
  * @rmtoll APB1SLPENR1     TIM2SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     TIM3SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     TIM4SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     TIM6SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     TIM7SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     SPI3SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     SPI4SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     WWDGSLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     SPI2SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     USART2SLPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     USART3SLPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     UART4SLPEN       LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     UART5SLPEN       LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     I2C1SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     I2C2SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     I3C1SLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     CRSSLPEN         LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     OPAMPSLPEN       LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     VREFSLPEN        LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SLPENR1     RTCAPBSLPEN      LL_APB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SLPENR1, Periphs);
}

/**
  * @brief  Disable APB1 peripheral clocks in Sleep mode
  * @rmtoll APB1SLPENR2     I2C4SLPEN        LL_APB1_GRP2_DisableClockSleep\n
  *         APB1SLPENR2     LPTIM2SLPEN      LL_APB1_GRP2_DisableClockSleep\n
  *         APB1SLPENR2     FDCANSLPEN       LL_APB1_GRP2_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SLPENR2, Periphs);
}

/**
  * @brief  Enable APB1 peripheral clocks in Stop mode
  * @rmtoll APB1STPENR1     SPI3STPEN        LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     SPI4STPEN        LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     SPI2STPEN        LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     USART2STPEN      LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     USART3STPEN      LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     UART4STPEN       LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     UART5STPEN       LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     I2C1STPEN        LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     I2C2STPEN        LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     I3C1STPEN        LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     OPAMPSTPEN       LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     VREFSTPEN        LL_APB1_GRP1_EnableClockStop\n
  *         APB1STPENR1     RTCAPBSTPEN      LL_APB1_GRP1_EnableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1STPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1STPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable APB1 peripheral clocks in Stop mode
  * @rmtoll APB1STPENR2     I2C4STPEN        LL_APB1_GRP2_EnableClockStop\n
  *         APB1STPENR2     LPTIM2STPEN      LL_APB1_GRP2_EnableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1STPENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1STPENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clocks in Stop mode is enabled or not
  * @rmtoll APB1STPENR1     SPI3STPEN        LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     SPI4STPEN        LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     SPI2STPEN        LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     USART2STPEN      LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     USART3STPEN      LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     UART4STPEN       LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     UART5STPEN       LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     I2C1STPEN        LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     I2C2STPEN        LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     I3C1STPEN        LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     OPAMPSTPEN       LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     VREFSTPEN        LL_APB1_GRP1_IsEnabledClockStop\n
  *         APB1STPENR1     RTCAPBSTPEN      LL_APB1_GRP1_IsEnabledClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockStop(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1STPENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Check if APB1 peripheral clocks in Stop mode is enabled or not
  * @rmtoll APB1STPENR2     I2C4STPEN        LL_APB1_GRP2_IsEnabledClockStop\n
  *         APB1STPENR2     LPTIM2STPEN      LL_APB1_GRP2_IsEnabledClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClockStop(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1STPENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripheral clocks in Stop mode
  * @rmtoll APB1STPENR1     SPI3STPEN        LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     SPI4STPEN        LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     SPI2STPEN        LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     USART2STPEN      LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     USART3STPEN      LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     UART4STPEN       LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     UART5STPEN       LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     I2C1STPEN        LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     I2C2STPEN        LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     I3C1STPEN        LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     OPAMPSTPEN       LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     VREFSTPEN        LL_APB1_GRP1_DisableClockStop\n
  *         APB1STPENR1     RTCAPBSTPEN      LL_APB1_GRP1_DisableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI4 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockStop(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1STPENR1, Periphs);
}

/**
  * @brief  Disable APB1 peripheral clocks in Stop mode
  * @rmtoll APB1STPENR2     I2C4STPEN        LL_APB1_GRP2_DisableClockStop\n
  *         APB1STPENR2     LPTIM2STPEN      LL_APB1_GRP2_DisableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockStop(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1STPENR2, Periphs);
}


/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */

/**
  * @brief  Enable APB2 peripherals clock.
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM12EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      USB1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      I3C2EN        LL_APB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clock is enabled or not
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM12EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      USB1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      I3C2EN        LL_APB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *         (*) value not defined in all devices.
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM12EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      USB1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      I3C2EN        LL_APB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll APB2RSTR      TIM1RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      SPI1RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM8RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      USART1RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM12RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM15RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM16RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM17RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      SAI1RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      USB1RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      I3C2RST        LL_APB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll APB2RSTR      TIM1RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      SPI1RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM8RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      USART1RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM12RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM15RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM16RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM17RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      SAI1RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      USB1RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      I3C2RST        LL_APB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Enable APB2 peripheral clocks in Sleep mode
  * @rmtoll APB2SLPENR      TIM1SLPEN        LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      SPI1SLPEN        LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      TIM8SLPEN        LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      USART1SLPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      TIM15SLPEN       LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      TIM12SLPEN       LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      TIM16SLPEN       LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      TIM17SLPEN       LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      SAI1SLPEN        LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      USB1SLPEN        LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SLPENR      I3C2SLPEN        LL_APB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2SLPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2SLPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll APB2SLPENR      TIM1SLPEN        LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      SPI1SLPEN        LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      TIM8SLPEN        LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      USART1SLPEN      LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      TIM12SLPEN       LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      TIM15SLPEN       LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      TIM16SLPEN       LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      TIM17SLPEN       LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      SAI1SLPEN        LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      USB1SLPEN        LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SLPENR      I3C2SLPEN        LL_APB2_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2SLPENR, Periphs) == Periphs) ? 1UL : 0UL);
}


/**
  * @brief  Disable APB2 peripheral clocks in Sleep mode
  * @rmtoll APB2SLPENR      TIM1SLPEN        LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      SPI1SLPEN        LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      TIM8SLPEN        LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      USART1SLPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      TIM12SLPEN       LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      TIM15SLPEN       LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      TIM16SLPEN       LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      TIM17SLPEN       LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      SAI1SLPEN        LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      USB1SLPEN        LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SLPENR      I3C2SLPEN        LL_APB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM12 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2SLPENR, Periphs);
}

/**
  * @brief  Enable APB2 peripheral clocks in Stop mode
  * @rmtoll APB2STPENR      SPI1STPEN        LL_APB2_GRP1_EnableClockStop\n
  *         APB2STPENR      USART1STPEN      LL_APB2_GRP1_EnableClockStop\n
  *         APB2STPENR      USB1STPEN        LL_APB2_GRP1_EnableClockStop\n
  *         APB2STPENR      I3C2STPEN        LL_APB2_GRP1_EnableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2STPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2STPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clocks in Stop mode is enabled or not
  * @rmtoll APB2STPENR      SPI1STPEN        LL_APB2_GRP1_IsEnabledClockStop\n
  *         APB2STPENR      USART1STPEN      LL_APB2_GRP1_IsEnabledClockStop\n
  *         APB2STPENR      USB1STPEN        LL_APB2_GRP1_IsEnabledClockStop\n
  *         APB2STPENR      I3C2STPEN        LL_APB2_GRP1_IsEnabledClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClockStop(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2STPENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripheral clocks in Stop mode
  * @rmtoll APB2STPENR      SPI1STPEN        LL_APB2_GRP1_DisableClockStop\n
  *         APB2STPENR      USART1STPEN      LL_APB2_GRP1_DisableClockStop\n
  *         APB2STPENR      USB1STPEN        LL_APB2_GRP1_DisableClockStop\n
  *         APB2STPENR      I3C2STPEN        LL_APB2_GRP1_DisableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB1
  *         @arg @ref LL_APB2_GRP1_PERIPH_I3C2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockStop(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2STPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3 APB3
  * @{
  */

/**
  * @brief  Enable APB3 peripherals clock.
  * @rmtoll APB3ENR      SYSCFGEN      LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPUART1EN     LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      I2C3EN        LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPTIM1EN      LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPTIM3EN      LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPTIM4EN      LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      COMPEN        LL_APB3_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB3ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB3ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 peripheral clock is enabled or not
  * @rmtoll APB3ENR      SYSCFGEN      LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPUART1EN     LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      I2C3EN        LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPTIM1EN      LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPTIM3EN      LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPTIM4EN      LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      COMPEN        LL_APB3_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 peripherals clock.
  * @rmtoll APB3ENR      SYSCFGEN      LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPUART1EN     LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      I2C3EN        LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPTIM1EN      LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPTIM3EN      LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPTIM4EN      LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      COMPEN        LL_APB3_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3ENR, Periphs);
}

/**
  * @brief  Force APB3 peripherals reset.
  * @rmtoll APB3RSTR      SYSCFGRST      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR      LPUART1RST     LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR      I2C3RST        LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR      LPTIM1RST      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR      LPTIM3RST      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR      LPTIM4RST      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR      COMPRST        LL_APB3_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Release APB3 peripherals reset.
  * @rmtoll APB3RSTR      SYSCFGRST      LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR      LPUART1RST     LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR      I2C3RST        LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR      LPTIM1RST      LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR      LPTIM3RST      LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR      LPTIM4RST      LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR      COMPRST        LL_APB3_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Enable APB3 peripheral clocks in Sleep mode
  * @rmtoll APB3SLPENR      SYSCFGSLPEN      LL_APB3_GRP1_EnableClockSleep\n
  *         APB3SLPENR      LPUART1SLPEN     LL_APB3_GRP1_EnableClockSleep\n
  *         APB3SLPENR      I2C3SLPEN        LL_APB3_GRP1_EnableClockSleep\n
  *         APB3SLPENR      LPTIM1SLPEN      LL_APB3_GRP1_EnableClockSleep\n
  *         APB3SLPENR      LPTIM3SLPEN      LL_APB3_GRP1_EnableClockSleep\n
  *         APB3SLPENR      LPTIM4SLPEN      LL_APB3_GRP1_EnableClockSleep\n
  *         APB3SLPENR      COMPSLPEN        LL_APB3_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB3SLPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB3SLPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 peripheral clocks in Sleep mode is enabled or not
  * @rmtoll APB3SLPENR      SYSCFGSLPEN      LL_APB3_GRP1_IsEnabledClockSleep\n
  *         APB3SLPENR      LPUART1SLPEN     LL_APB3_GRP1_IsEnabledClockSleep\n
  *         APB3SLPENR      I2C3SLPEN        LL_APB3_GRP1_IsEnabledClockSleep\n
  *         APB3SLPENR      LPTIM1SLPEN      LL_APB3_GRP1_IsEnabledClockSleep\n
  *         APB3SLPENR      LPTIM3SLPEN      LL_APB3_GRP1_IsEnabledClockSleep\n
  *         APB3SLPENR      LPTIM4SLPEN      LL_APB3_GRP1_IsEnabledClockSleep\n
  *         APB3SLPENR      COMPSLPEN        LL_APB3_GRP1_IsEnabledClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3SLPENR, Periphs) == Periphs) ? 1UL : 0UL);
}


/**
  * @brief  Disable APB3 peripheral clocks in Sleep mode
  * @rmtoll APB3SLPENR      SYSCFGSLPEN      LL_APB3_GRP1_DisableClockSleep\n
  *         APB3SLPENR      LPUART1SLPEN     LL_APB3_GRP1_DisableClockSleep\n
  *         APB3SLPENR      I2C3SLPEN        LL_APB3_GRP1_DisableClockSleep\n
  *         APB3SLPENR      LPTIM1SLPEN      LL_APB3_GRP1_DisableClockSleep\n
  *         APB3SLPENR      LPTIM3SLPEN      LL_APB3_GRP1_DisableClockSleep\n
  *         APB3SLPENR      LPTIM4SLPEN      LL_APB3_GRP1_DisableClockSleep\n
  *         APB3SLPENR      COMPSLPEN        LL_APB3_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3SLPENR, Periphs);
}


/**
  * @brief  Enable APB3 peripheral clocks in Stop mode
  * @rmtoll APB3STPENR      LPUART1STPEN     LL_APB3_GRP1_EnableClockStop\n
  *         APB3STPENR      I2C3STPEN        LL_APB3_GRP1_EnableClockStop\n
  *         APB3STPENR      LPTIM1STPEN      LL_APB3_GRP1_EnableClockStop\n
  *         APB3STPENR      LPTIM3STPEN      LL_APB3_GRP1_EnableClockStop\n
  *         APB3STPENR      LPTIM4STPEN      LL_APB3_GRP1_EnableClockStop\n
  *         APB3STPENR      COMPSTPEN        LL_APB3_GRP1_EnableClockStop\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB3STPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB3STPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 peripheral clocks in Stop mode is enabled or not
  * @rmtoll APB3STPENR      LPUART1STPEN     LL_APB3_GRP1_IsEnabledClockStop\n
  *         APB3STPENR      I2C3STPEN        LL_APB3_GRP1_IsEnabledClockStop\n
  *         APB3STPENR      LPTIM1STPEN      LL_APB3_GRP1_IsEnabledClockStop\n
  *         APB3STPENR      LPTIM3STPEN      LL_APB3_GRP1_IsEnabledClockStop\n
  *         APB3STPENR      LPTIM4STPEN      LL_APB3_GRP1_IsEnabledClockStop\n
  *         APB3STPENR      COMPSTPEN        LL_APB3_GRP1_IsEnabledClockStop\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClockStop(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3STPENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 peripheral clocks in Stop mode
  * @rmtoll APB3STPENR      LPUART1STPEN     LL_APB3_GRP1_DisableClockStop\n
  *         APB3STPENR      I2C3STPEN        LL_APB3_GRP1_DisableClockStop\n
  *         APB3STPENR      LPTIM1STPEN      LL_APB3_GRP1_DisableClockStop\n
  *         APB3STPENR      LPTIM3STPEN      LL_APB3_GRP1_DisableClockStop\n
  *         APB3STPENR      LPTIM4STPEN      LL_APB3_GRP1_DisableClockStop\n
  *         APB3STPENR      COMPSTPEN        LL_APB3_GRP1_DisableClockStop\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClockStop(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3STPENR, Periphs);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U3xx_LL_BUS_H */
