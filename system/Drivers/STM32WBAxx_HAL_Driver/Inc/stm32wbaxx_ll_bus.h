/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_bus.h
  * @author  MCD Application Team
  * @brief   Header file of BUS LL module.
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
#ifndef STM32WBAxx_LL_BUS_H
#define STM32WBAxx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx.h"

/** @addtogroup STM32WBAxx_LL_Driver
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
#define LL_AHB1_GRP1_PERIPH_ALL           0xFFFFFFFFU
#if defined(GPDMA1)
#define LL_AHB1_GRP1_PERIPH_GPDMA1        RCC_AHB1ENR_GPDMA1EN
#endif
#define LL_AHB1_GRP1_PERIPH_FLASH         RCC_AHB1ENR_FLASHEN
#define LL_AHB1_GRP1_PERIPH_CRC           RCC_AHB1ENR_CRCEN
#define LL_AHB1_GRP1_PERIPH_TSC           RCC_AHB1ENR_TSCEN
#define LL_AHB1_GRP1_PERIPH_RAMCFG        RCC_AHB1ENR_RAMCFGEN
#if defined(GTZC_TZSC)
#define LL_AHB1_GRP1_PERIPH_GTZC1         RCC_AHB1ENR_GTZC1EN
#endif /* GTZC_TZSC */
#define LL_AHB1_GRP1_PERIPH_SRAM1         RCC_AHB1ENR_SRAM1EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_AHB2_GRP1_PERIPH_GPIOA          RCC_AHB2ENR_GPIOAEN
#define LL_AHB2_GRP1_PERIPH_GPIOB          RCC_AHB2ENR_GPIOBEN
#define LL_AHB2_GRP1_PERIPH_GPIOC          RCC_AHB2ENR_GPIOCEN
#define LL_AHB2_GRP1_PERIPH_GPIOH          RCC_AHB2ENR_GPIOHEN
#define LL_AHB2_GRP1_PERIPH_AES            RCC_AHB2ENR_AESEN
#define LL_AHB2_GRP1_PERIPH_HASH           RCC_AHB2ENR_HASHEN
#define LL_AHB2_GRP1_PERIPH_RNG            RCC_AHB2ENR_RNGEN
#if defined(SAES)
#define LL_AHB2_GRP1_PERIPH_SAES           RCC_AHB2ENR_SAESEN
#endif /* SAES */
#define LL_AHB2_GRP1_PERIPH_HSEM           RCC_AHB2ENR_HSEMEN
#define LL_AHB2_GRP1_PERIPH_PKA            RCC_AHB2ENR_PKAEN
#define LL_AHB2_GRP1_PERIPH_SRAM2          RCC_AHB2ENR_SRAM2EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB4_GRP1_PERIPH  AHB4 GRP1 PERIPH
  * @{
  */
#define LL_AHB4_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_AHB4_GRP1_PERIPH_PWR            RCC_AHB4ENR_PWREN
#define LL_AHB4_GRP1_PERIPH_ADC4           RCC_AHB4ENR_ADC4EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB5_GRP1_PERIPH  AHB5 GRP1 PERIPH
  * @{
  */
#define LL_AHB5_GRP1_PERIPH_ALL            0xFFFFFFFFU
#if defined(PTACONV)
#define LL_AHB5_GRP1_PERIPH_PTACONV        RCC_AHB5ENR_PTACONVEN
#endif /* PTACONV */
#define LL_AHB5_GRP1_PERIPH_RADIO          RCC_AHB5ENR_RADIOEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL           0xFFFFFFFFU
#define LL_APB1_GRP1_PERIPH_TIM2          RCC_APB1ENR1_TIM2EN
#if defined(TIM3)
#define LL_APB1_GRP1_PERIPH_TIM3          RCC_APB1ENR1_TIM3EN
#endif /* TIM3 */
#if defined(WWDG)
#define LL_APB1_GRP1_PERIPH_WWDG          RCC_APB1ENR1_WWDGEN
#endif /* WWDG */
#define LL_APB1_GRP1_PERIPH_USART2        RCC_APB1ENR1_USART2EN
#if defined(I2C1)
#define LL_APB1_GRP1_PERIPH_I2C1          RCC_APB1ENR1_I2C1EN
#endif /* I2C1 */
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_ALL            0xFFFFFFFFU
#if defined(LPTIM2)
#define LL_APB1_GRP2_PERIPH_LPTIM2         RCC_APB1ENR2_LPTIM2EN
#endif /* LPTIM2 */
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_ALL            0xFFFFFFFFU
#if defined(TIM1)
#define LL_APB2_GRP1_PERIPH_TIM1           RCC_APB2ENR_TIM1EN
#endif /* TIM1 */
#if defined(SPI1)
#define LL_APB2_GRP1_PERIPH_SPI1           RCC_APB2ENR_SPI1EN
#endif /* SPI1 */
#define LL_APB2_GRP1_PERIPH_USART1         RCC_APB2ENR_USART1EN
#define LL_APB2_GRP1_PERIPH_TIM16          RCC_APB2ENR_TIM16EN
#if defined(TIM17)
#define LL_APB2_GRP1_PERIPH_TIM17          RCC_APB2ENR_TIM17EN
#endif /* TIM17 */
#if defined(SAI1)
#define LL_APB2_GRP1_PERIPH_SAI1           RCC_APB2ENR_SAI1EN
#endif /* SAI1 */
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB7_GRP1_PERIPH  APB7 GRP1 PERIPH
  * @{
  */
#define LL_APB7_GRP1_PERIPH_ALL           0xFFFFFFFFU
#define LL_APB7_GRP1_PERIPH_SYSCFG        RCC_APB7ENR_SYSCFGEN
#define LL_APB7_GRP1_PERIPH_SPI3          RCC_APB7ENR_SPI3EN
#define LL_APB7_GRP1_PERIPH_LPUART1       RCC_APB7ENR_LPUART1EN
#define LL_APB7_GRP1_PERIPH_I2C3          RCC_APB7ENR_I2C3EN
#define LL_APB7_GRP1_PERIPH_LPTIM1        RCC_APB7ENR_LPTIM1EN
#if defined(COMP1)
#define LL_APB7_GRP1_PERIPH_COMP          RCC_APB7ENR_COMPEN
#endif /* COMP1 */
#define LL_APB7_GRP1_PERIPH_RTCAPB        RCC_APB7ENR_RTCAPBEN
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
#if defined(GPDMA1)
  * @rmtoll AHB1ENR    GPDMA1EN     LL_AHB1_GRP1_EnableClock\n
#endif
  *         AHB1ENR    FLASHEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    CRCEN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    TSCEN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    RAMCFGEN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    GTZC1EN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    SRAM1EN      LL_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled or not
#if defined(GPDMA1)
  * @rmtoll        AHB1ENR    GPDMA1EN     LL_AHB1_GRP1_IsEnabledClock
#endif
  *         AHB1ENR    FLASHEN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    CRCEN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    TSCEN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    RAMCFGEN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    GTZC1EN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    SRAM1EN      LL_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
   *        @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripherals clock.
#if defined(GPDMA1)
  * @rmtoll AHB1ENR    GPDMA1EN     LL_AHB1_GRP1_DisableClock
#endif
  *         AHB1ENR    FLASHEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    CRCEN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    TSCEN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    RAMCFGEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    GTZC1EN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    SRAM1EN      LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
   *        @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
#if defined(GPDMA1)
  * @rmtoll AHB1RSTR    GPDMA1RSTR     LL_AHB1_GRP1_ForceReset\n
#endif
  *         AHB1RSTR    CRCRSTR        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    TSCRSTR        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    RAMCFGRSTR     LL_AHB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
#if defined(GPDMA1)
  * @rmtoll AHB1RSTR    GPDMA1RSTR      LL_AHB1_GRP1_ReleaseReset\n
#endif
  *         AHB1RSTR    CRCRSTR         LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    TSCRSTR         LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    RAMCFGRSTR      LL_AHB1_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Enable AHB1 peripheral clocks in Sleep and Stop modes
#if defined(GPDMA1)
  * @rmtoll AHB1SMENR   GPDMA1SMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
#endif
  *         AHB1SMENR   FLASHSMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   CRCSMEN        LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   TSCSMEN        LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   RAMCFGSMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   GTZC1SMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   SRAM1SMEN      LL_AHB1_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clocks in Sleep and Stop modes is enabled or not
#if defined(GPDMA1)
  * @rmtoll AHB1SMENR   GPDMA1SMEN     LL_AHB1_GRP1_IsEnabledClockStopSleep\n
#endif
  *         AHB1SMENR   FLASHSMEN      LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   CRCSMEN        LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   TSCSMEN        LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   RAMCFGSMEN     LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   GTZC1SMEN      LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   SRAM1SMEN      LL_AHB1_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripheral clocks in Sleep and Stop modes
#if defined(GPDMA1)
  * @rmtoll AHB1SMENR   GPDMA1SMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
#endif
  *         AHB1SMENR   FLASHSMEN      LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   CRCSMEN        LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   TSCSMEN        LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   RAMCFGSMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   GTZC1SMEN      LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   SRAM1SMEN      LL_AHB1_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
#if defined(GPDMA1)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1 (*)
#endif
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2_GRP1_PERIPH AHB2 GRP1 PERIPH
  * @{
  */
/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      GPIOAEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      GPIOBEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      GPIOCEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      GPIOHEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      AESEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      HASHEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      RNGEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      SAESEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      HSEMEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      PKAEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      SRAM2EN       LL_AHB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled or not
  * @rmtoll AHB2ENR      GPIOAEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      GPIOBEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      GPIOCEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      GPIOHEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      AESEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      HASHEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      RNGEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      SAESEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      HSEMEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      PKAEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      SRAM2EN       LL_AHB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      GPIOAEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      GPIOBEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      GPIOCEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      GPIOHEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      AESEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      HASHEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      RNGEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      SAESEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      HSEMEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      PKAEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      SRAM2EN       LL_AHB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR, Periphs);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll AHB2RSTR     GPIOARST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     GPIOBRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     GPIOCRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     GPIOHRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     AESRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     HASHRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     RNGRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     SAESRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     HSEMRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     PKARST        LL_AHB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR, Periphs);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll AHB2RSTR     GPIOARST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     GPIOBRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     GPIOCRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     GPIOHRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     AESRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     HASHRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     RNGRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     SAESRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     HSEMRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     PKARST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     SRAM1RST      LL_AHB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR, Periphs);
}

/**
  * @brief  Enable AHB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB2SMENR    GPIOASMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    GPIOBSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    GPIOCSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    GPIOHSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    AESSMEN        LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    HASHSMEN       LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    RNGSMEN        LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    SAESSMEN       LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    PKASMEN        LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR    SRAM2SMEN      LL_AHB2_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll AHB2SMENR    GPIOASMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    GPIOBSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    GPIOCSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    GPIOHSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    AESSMEN        LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    HASHSMEN       LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    RNGSMEN        LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    SAESSMEN       LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    PKASMEN        LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR    SRAM2SMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB2SMENR    GPIOASMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    GPIOBSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    GPIOCSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    GPIOHSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    AESSMEN        LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    HASHSMEN       LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    RNGSMEN        LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    SAESSMEN       LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    PKASMEN        LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR    SRAM2SMEN      LL_AHB2_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB4 AHB4
  * @{
  */
/**
  * @brief  Enable AHB4 peripherals clock.
  * @rmtoll AHB4ENR  PWREN         LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR  ADC4EN        LL_AHB4_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB4ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB4ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB4 peripheral clock is enabled or not
  * @rmtoll AHB4ENR  PWREN         LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR  ADC4EN        LL_AHB4_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB4ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 peripherals clock.
  * @rmtoll AHB4ENR  PWREN         LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR  ADC4EN        LL_AHB4_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4ENR, Periphs);
}

/**
  * @brief  Force AHB4 peripherals reset.
  * @rmtoll AHB4RSTR  ADC4RST        LL_AHB4_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB4RSTR, Periphs);
}

/**
  * @brief  Release AHB4 peripherals reset.
  * @rmtoll AHB4RSTR  ADC4RST        LL_AHB4_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4RSTR, Periphs);
}

/**
  * @brief  Enable AHB4 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB4SMENR  PWRSMEN        LL_AHB4_GRP1_EnableClockStopSleep\n
  *         AHB4SMENR  ADC4SMEN       LL_AHB4_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB4SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB4SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB4 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll AHB4SMENR  PWRSMEN        LL_AHB4_GRP1_IsEnabledClockStopSleep\n
  *         AHB4SMENR  ADC4SMEN       LL_AHB4_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB4SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB4SMENR  PWRSMEN        LL_AHB4_GRP1_DisableClockStopSleep\n
  *         AHB4SMENR  ADC4SMEN       LL_AHB4_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC4
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB5 AHB5
  * @{
  */
/**
  * @brief  Enable AHB5 peripherals clock.
  * @rmtoll AHB5ENR  RADIOEN        LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR  PTACONVEN      LL_AHB5_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB5ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB5ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB5 peripheral clock is enabled or not
  * @rmtoll AHB5ENR  RADIOEN        LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR  PTACONVEN      LL_AHB5_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB5_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB5ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB5 peripherals clock.
  * @rmtoll AHB5ENR  RADIOEN        LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR  PTACONVEN      LL_AHB5_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB5ENR, Periphs);
}

/**
  * @brief  Force AHB5 peripherals reset.
  * @rmtoll AHB5RSTR  RADIORST        LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR  PTACONVRST      LL_AHB5_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB5RSTR, Periphs);
}

/**
  * @brief  Release AHB5 peripherals reset.
  * @rmtoll AHB5RSTR  RADIORST        LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR  PTACONVRST      LL_AHB5_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB5RSTR, Periphs);
}

/**
  * @brief  Enable AHB5 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB5SMENR  RADIOSMEN       LL_AHB5_GRP1_EnableClockStopSleep\n
  *         AHB5SMENR  PTACONVSMEN     LL_AHB5_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB5SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB5SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB5 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll AHB5SMENR  RADIOSMEN       LL_AHB5_GRP1_IsEnabledClockStopSleep\n
  *         AHB5SMENR  PTACONVSMEN     LL_AHB5_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB5_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB5SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB5 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB5SMENR  RADIOSMEN       LL_AHB5_GRP1_DisableClockStopSleep\n
  *         AHB5SMENR  PTACONVSMEN     LL_AHB5_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RADIO
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PTACONV (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB5SMENR, Periphs);
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
#if defined(WWDG)
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_EnableClock\n
#endif
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
#if defined(WWDG)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG (*)
#endif
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
  *
  *         (*) value not defined in all devices.
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
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
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
#if defined(WWDG)
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_IsEnabledClock\n
#endif
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
#if defined(WWDG)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG (*)
#endif
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
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
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
#if defined(WWDG)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG (*)
#endif
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR1, Periphs);
}

/**
  * @brief  Disable APB1 peripherals clock.
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR2, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR1     TIM2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     USART2RST     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     I2C1RST       LL_APB1_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  *         APB1RSTR2     LPTIM2RST     LL_APB1_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR1     TIM2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     USART2RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     I2C1RST       LL_APB1_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  *         APB1RSTR2     LPTIM2RST     LL_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Enable APB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB1SMENR1     TIM2SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     TIM3SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
#if defined(WWDG)
  *         APB1SMENR1     WWDGSMEN       LL_APB1_GRP1_EnableClockStopSleep\n
#endif
  *         APB1SMENR1     USART2SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     I2C1SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
#if defined(WWDG)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG (*)
#endif
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SMENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SMENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll APB1SMENR1     TIM2SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     TIM3SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
#if defined(WWDG)
  *         APB1SMENR1     WWDGSMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
#endif
  *         APB1SMENR1     USART2SMEN     LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     I2C1SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
#if defined(WWDG)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG (*)
#endif
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SMENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB1SMENR1     TIM2SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     TIM3SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
#if defined(WWDG)
  *         APB1SMENR1     WWDGSMEN       LL_APB1_GRP1_DisableClockStopSleep\n
#endif
  *         APB1SMENR1     USART2SMEN     LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     I2C1SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
#if defined(WWDG)
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG (*)
#endif
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SMENR1, Periphs);
}

/**
  * @brief  Enable APB1 peripheral clocks in Sleep and Stop modes
  *         APB1SMENR2     LPTIM2SMEN     LL_APB1_GRP2_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SMENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SMENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clocks in Sleep and Stop modes is enabled or not
  *         APB1SMENR2     LPTIM2SMEN     LL_APB1_GRP2_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SMENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripheral clocks in Sleep and Stop modes
  *         APB1SMENR2     LPTIM2SMEN     LL_APB1_GRP2_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SMENR2, Periphs);
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
  *         APB2ENR      USART1EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
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
  *         APB2ENR      USART1EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
  *
  *         (*) value not defined in all devices.
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
  *         APB2ENR      USART1EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
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
  *         APB2RSTR      USART1RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM16RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM17RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      SAI1RST        LL_APB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
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
  *         APB2RSTR      USART1RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM16RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM17RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      SAI1RST        LL_APB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Enable APB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB2SMENR     TIM1SMEN       LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     SPI1SMEN       LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     USART1SMEN     LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     TIM16SMEN      LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     TIM17SMEN      LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     SAI1SMEN       LL_APB2_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2SMENR, Periphs);
  (void)tmpreg;
}


/**
  * @brief  Check if APB2 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll APB2SMENR     TIM1SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     SPI1SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     USART1SMEN     LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     TIM16SMEN      LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     TIM17SMEN      LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     SAI1SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB2SMENR     TIM1SMEN        LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     SPI1SMEN        LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     USART1SMEN      LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     TIM16SMEN       LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     TIM17SMEN       LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     SAI1SMEN        LL_APB2_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2SMENR, Periphs);
}

/**
  * @}
  */


/** @defgroup BUS_LL_EF_APB7 APB7
  * @{
  */

/**
  * @brief  Enable APB7 peripherals clock.
  * @rmtoll APB7ENR      SYSCFGEN       LL_APB7_GRP1_EnableClock\n
  *         APB7ENR      SPI3EN         LL_APB7_GRP1_EnableClock\n
  *         APB7ENR      LPUART1EN      LL_APB7_GRP1_EnableClock\n
  *         APB7ENR      I2C3EN         LL_APB7_GRP1_EnableClock\n
  *         APB7ENR      LPTIM1EN       LL_APB7_GRP1_EnableClock\n
  *         APB7ENR      COMPEN         LL_APB7_GRP1_EnableClock\n
  *         APB7ENR      RTCAPBEN       LL_APB7_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *         @arg @ref LL_APB7_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB7_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB7ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB7ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB7 peripheral clock is enabled or not
  * @rmtoll APB7ENR      SYSCFGEN       LL_APB7_GRP1_IsEnabledClock\n
  *         APB7ENR      SPI3EN         LL_APB7_GRP1_IsEnabledClock\n
  *         APB7ENR      LPUART1EN      LL_APB7_GRP1_IsEnabledClock\n
  *         APB7ENR      I2C3EN         LL_APB7_GRP1_IsEnabledClock\n
  *         APB7ENR      LPTIM1EN       LL_APB7_GRP1_IsEnabledClock\n
  *         APB7ENR      COMPEN         LL_APB7_GRP1_IsEnabledClock\n
  *         APB7ENR      RTCAPBEN       LL_APB7_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *         @arg @ref LL_APB7_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB7_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB7ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB7ENR      SYSCFGEN       LL_APB7_GRP1_DisableClock\n
  *         APB7ENR      SPI3EN         LL_APB7_GRP1_DisableClock\n
  *         APB7ENR      LPUART1EN      LL_APB7_GRP1_DisableClock\n
  *         APB7ENR      I2C3EN         LL_APB7_GRP1_DisableClock\n
  *         APB7ENR      LPTIM1EN       LL_APB7_GRP1_DisableClock\n
  *         APB7ENR      COMPEN         LL_APB7_GRP1_DisableClock\n
  *         APB7ENR      RTCAPBEN       LL_APB7_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *         @arg @ref LL_APB7_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB7_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB7ENR, Periphs);
}

/**
  * @brief  Force APB7 peripherals reset.
  * @rmtoll APB7RSTR     SYSCFGRST     LL_APB7_GRP1_ForceReset\n
  *         APB7RSTR     SPI3RST       LL_APB7_GRP1_ForceReset\n
  *         APB7RSTR     LPUART1RST    LL_APB7_GRP1_ForceReset\n
  *         APB7RSTR     I2C3RST       LL_APB7_GRP1_ForceReset\n
  *         APB7RSTR     LPTIM1RST     LL_APB7_GRP1_ForceReset\n
  *         APB7RSTR     COMPRST       LL_APB7_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB7_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB7RSTR, Periphs);
}

/**
  * @brief  Release APB7 peripherals reset.
  * @rmtoll APB7RSTR     SYSCFGRST     LL_APB7_GRP1_ReleaseReset\n
  *         APB7RSTR     SPI3RST       LL_APB7_GRP1_ReleaseReset\n
  *         APB7RSTR     LPUART1RST    LL_APB7_GRP1_ReleaseReset\n
  *         APB7RSTR     I2C3RST       LL_APB7_GRP1_ReleaseReset\n
  *         APB7RSTR     LPTIM1RST     LL_APB7_GRP1_ReleaseReset\n
  *         APB7RSTR     COMPRST       LL_APB7_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB7_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB7RSTR, Periphs);
}

/**
  * @brief  Enable APB7 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB7SMENR    SYSCFGSMEN    LL_APB7_GRP1_EnableClockStopSleep\n
  *         APB7SMENR    SPI3SMEN      LL_APB7_GRP1_EnableClockStopSleep\n
  *         APB7SMENR    LPUART1SMEN   LL_APB7_GRP1_EnableClockStopSleep\n
  *         APB7SMENR    I2C3SMEN      LL_APB7_GRP1_EnableClockStopSleep\n
  *         APB7SMENR    LPTIM1SMEN    LL_APB7_GRP1_EnableClockStopSleep\n
  *         APB7SMENR    COMPSMEN      LL_APB7_GRP1_EnableClockStopSleep\n
  *         APB7SMENR    RTCAPBSMEN    LL_APB7_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *         @arg @ref LL_APB7_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB7_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB7SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB7SMENR, Periphs);
  (void)tmpreg;
}


/**
  * @brief  Check if APB7 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll APB7SMENR    SYSCFGSMEN    LL_APB7_GRP1_IsEnabledClockStopSleep\n
  *         APB7SMENR    SPI3SMEN      LL_APB7_GRP1_IsEnabledClockStopSleep\n
  *         APB7SMENR    LPUART1SMEN   LL_APB7_GRP1_IsEnabledClockStopSleep\n
  *         APB7SMENR    I2C3SMEN      LL_APB7_GRP1_IsEnabledClockStopSleep\n
  *         APB7SMENR    LPTIM1SMEN    LL_APB7_GRP1_IsEnabledClockStopSleep\n
  *         APB7SMENR    COMPSMEN      LL_APB7_GRP1_IsEnabledClockStopSleep\n
  *         APB7SMENR    RTCAPBSMEN    LL_APB7_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *         @arg @ref LL_APB7_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB7_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB7SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB7 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB7SMENR    SYSCFGSMEN     LL_APB7_GRP1_DisableClockStopSleep\n
  *         APB7SMENR    SPI3SMEN       LL_APB7_GRP1_DisableClockStopSleep\n
  *         APB7SMENR    LPUART1SMEN    LL_APB7_GRP1_DisableClockStopSleep\n
  *         APB7SMENR    I2C3SMEN       LL_APB7_GRP1_DisableClockStopSleep\n
  *         APB7SMENR    LPTIM1SMEN     LL_APB7_GRP1_DisableClockStopSleep\n
  *         APB7SMENR    COMPSMEN       LL_APB7_GRP1_DisableClockStopSleep\n
  *         APB7SMENR    RTCAPBSMEN     LL_APB7_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB7_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB7_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB7_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB7_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB7_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB7_GRP1_PERIPH_COMP (*)
  *         @arg @ref LL_APB7_GRP1_PERIPH_RTCAPB
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB7_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB7SMENR, Periphs);
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

#endif /* STM32WBAxx_LL_BUS_H */
