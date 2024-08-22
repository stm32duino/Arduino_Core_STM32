/**
  ******************************************************************************
  * @file    stm32u0xx_ll_bus.h
  * @author  MCD Application Team
  * @brief   Header file of BUS LL module.

  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB & APB peripherals, 1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

  @endverbatim
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
#ifndef __STM32U0xx_LL_BUS_H
#define __STM32U0xx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx.h"

/** @addtogroup STM32U0xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Peripheral_Memory_Mapping Peripheral Memory Mapping
  * @{
  */
#define RCC_MAP         RCC        /* Alias Legacy/Non-Secure periphal memory access */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Constants BUS Exported Constants
  * @{
  */

/** @defgroup BUS_LL_EC_AHB1_GRP1_PERIPH  AHB GRP1 PERIPH
  * @{
  */
#define LL_AHB1_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_AHB1_GRP1_PERIPH_DMA1           RCC_AHBENR_DMA1EN
#if defined (DMA2)
#define LL_AHB1_GRP1_PERIPH_DMA2           RCC_AHBENR_DMA2EN
#endif /* DMA2 */
#define LL_AHB1_GRP1_PERIPH_FLASH          RCC_AHBENR_FLASHEN
#define LL_AHB1_GRP1_PERIPH_CRC            RCC_AHBENR_CRCEN
#define LL_AHB1_GRP1_PERIPH_TSC            RCC_AHBENR_TSCEN
#if defined (AES)
#define LL_AHB1_GRP1_PERIPH_AES            RCC_AHBENR_AESEN
#endif /* AES */
#define LL_AHB1_GRP1_PERIPH_RNG            RCC_AHBENR_RNGEN
#define LL_AHB1_GRP1_PERIPH_SRAM1          RCC_AHBSMENR_SRAM1SMEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_APB1_GRP1_PERIPH_TIM2           RCC_APBENR1_TIM2EN
#define LL_APB1_GRP1_PERIPH_TIM3           RCC_APBENR1_TIM3EN
#define LL_APB1_GRP1_PERIPH_TIM6           RCC_APBENR1_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7           RCC_APBENR1_TIM7EN
#define LL_APB1_GRP1_PERIPH_LPUART2        RCC_APBENR1_LPUART2EN
#if defined (LCD)
#define LL_APB1_GRP1_PERIPH_LCD            RCC_APBENR1_LCDEN
#endif /* LCD */
#define LL_APB1_GRP1_PERIPH_RTCAPB         RCC_APBENR1_RTCAPBEN
#define LL_APB1_GRP1_PERIPH_WWDG           RCC_APBENR1_WWDGEN
#if defined (LPUART3)
#define LL_APB1_GRP1_PERIPH_LPUART3        RCC_APBENR1_LPUART3EN
#endif /* LPUART3 */
#if defined (USB_DRD_FS)
#define LL_APB1_GRP1_PERIPH_USB            RCC_APBENR1_USBEN
#endif /* USB_DRD_FS */
#define LL_APB1_GRP1_PERIPH_SPI2           RCC_APBENR1_SPI2EN
#define LL_APB1_GRP1_PERIPH_SPI3           RCC_APBENR1_SPI3EN
#define LL_APB1_GRP1_PERIPH_CRS            RCC_APBENR1_CRSEN
#define LL_APB1_GRP1_PERIPH_USART2         RCC_APBENR1_USART2EN
#define LL_APB1_GRP1_PERIPH_USART3         RCC_APBENR1_USART3EN
#define LL_APB1_GRP1_PERIPH_USART4         RCC_APBENR1_USART4EN
#define LL_APB1_GRP1_PERIPH_LPUART1        RCC_APBENR1_LPUART1EN
#define LL_APB1_GRP1_PERIPH_I2C1           RCC_APBENR1_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2           RCC_APBENR1_I2C2EN
#define LL_APB1_GRP1_PERIPH_I2C3           RCC_APBENR1_I2C3EN
#define LL_APB1_GRP1_PERIPH_OPAMP          RCC_APBENR1_OPAMPEN
#define LL_APB1_GRP1_PERIPH_I2C4           RCC_APBENR1_I2C4EN
#if defined (LPTIM3)
#define LL_APB1_GRP1_PERIPH_LPTIM3         RCC_APBENR1_LPTIM3EN
#endif /* LPTIM3 */
#define LL_APB1_GRP1_PERIPH_PWR            RCC_APBENR1_PWREN
#define LL_APB1_GRP1_PERIPH_DAC1           RCC_APBENR1_DAC1EN
#define LL_APB1_GRP1_PERIPH_LPTIM2         RCC_APBENR1_LPTIM2EN
#define LL_APB1_GRP1_PERIPH_LPTIM1         RCC_APBENR1_LPTIM1EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_ALL           0xFFFFFFFFU
#define LL_APB1_GRP2_PERIPH_SYSCFG        RCC_APBENR2_SYSCFGEN
#define LL_APB1_GRP2_PERIPH_COMP          RCC_APBENR2_SYSCFGEN
#define LL_APB1_GRP2_PERIPH_VREFBUF       RCC_APBENR2_SYSCFGEN
#define LL_APB1_GRP2_PERIPH_TIM1          RCC_APBENR2_TIM1EN
#define LL_APB1_GRP2_PERIPH_SPI1          RCC_APBENR2_SPI1EN
#define LL_APB1_GRP2_PERIPH_USART1        RCC_APBENR2_USART1EN
#define LL_APB1_GRP2_PERIPH_TIM15         RCC_APBENR2_TIM15EN
#define LL_APB1_GRP2_PERIPH_TIM16         RCC_APBENR2_TIM16EN
#define LL_APB1_GRP2_PERIPH_ADC           RCC_APBENR2_ADCEN

/**
  * @}
  */

/** @defgroup BUS_LL_EC_IOP_GRP1_PERIPH  IOP GRP1 PERIPH
  * @{
  */
#define LL_IOP_GRP1_PERIPH_ALL             0xFFFFFFFFU
#define LL_IOP_GRP1_PERIPH_GPIOA           RCC_IOPENR_GPIOAEN
#define LL_IOP_GRP1_PERIPH_GPIOB           RCC_IOPENR_GPIOBEN
#define LL_IOP_GRP1_PERIPH_GPIOC           RCC_IOPENR_GPIOCEN
#define LL_IOP_GRP1_PERIPH_GPIOD           RCC_IOPENR_GPIODEN
#if defined (GPIOE)
#define LL_IOP_GRP1_PERIPH_GPIOE           RCC_IOPENR_GPIOEEN
#endif /* GPIOE */
#define LL_IOP_GRP1_PERIPH_GPIOF           RCC_IOPENR_GPIOFEN

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Functions BUS Exported Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB AHB
  * @{
  */

/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll AHBENR      DMA1EN        LL_AHB1_GRP1_EnableClock\n
  *         AHBENR      DMA2EN        LL_AHB1_GRP1_EnableClock\n
  *         AHBENR      FLASHEN       LL_AHB1_GRP1_EnableClock\n
  *         AHBENR      CRCEN         LL_AHB1_GRP1_EnableClock\n
  *         AHBENR      TSCEN         LL_AHB1_GRP1_EnableClock\n
  *         AHBENR      AESEN         LL_AHB1_GRP1_EnableClock\n
  *         AHBENR      RNGEN         LL_AHB1_GRP1_EnableClock\n
  *         AHBENR      SRAM1EN       LL_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHBENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHBENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled or not
  * @rmtoll AHBENR      DMA1EN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR      DMA2EN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR      FLASHEN       LL_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR      CRCEN         LL_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR      TSCEN         LL_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR      AESEN         LL_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR      RNGEN         LL_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR      SRAM1EN       LL_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->AHBENR, Periphs) == Periphs);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHBENR      DMA1EN        LL_AHB1_GRP1_DisableClock\n
  *         AHBENR      DMA2EN        LL_AHB1_GRP1_DisableClock\n
  *         AHBENR      FLASHEN       LL_AHB1_GRP1_DisableClock\n
  *         AHBENR      CRCEN         LL_AHB1_GRP1_DisableClock\n
  *         AHBENR      TSCEN         LL_AHB1_GRP1_DisableClock\n
  *         AHBENR      AESEN         LL_AHB1_GRP1_DisableClock\n
  *         AHBENR      RNGEN         LL_AHB1_GRP1_DisableClock\n
  *         AHBENR      SRAM1EN       LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBENR, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll AHBRSTR     DMA1RST       LL_AHB1_GRP1_ForceReset\n
  *         AHBRSTR     DMA2RST       LL_AHB1_GRP1_ForceReset\n
  *         AHBRSTR     FLASHRST      LL_AHB1_GRP1_ForceReset\n
  *         AHBRSTR     CRCRST        LL_AHB1_GRP1_ForceReset\n
  *         AHBRSTR     TSCRST        LL_AHB1_GRP1_ForceReset\n
  *         AHBRSTR     AESRST        LL_AHB1_GRP1_ForceReset\n
  *         AHBRSTR     RNGRST        LL_AHB1_GRP1_ForceReset\n
  *         AHBRSTR     SRAM1RST      LL_AHB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHBRSTR, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll AHBRSTR     DMA1RST       LL_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR     DMA2RST       LL_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR     FLASHRST      LL_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR     CRCRST        LL_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR     TSCRST        LL_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR     AESRST        LL_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR     RNGRST        LL_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR     SRAM1RST      LL_AHB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBRSTR, Periphs);
}

/**
  * @brief  Enable AHB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHBSMENR    DMA1SMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    DMA2SMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    FLASHSMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    SRAM1SMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    CRCSMEN       LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    TSCSMEN       LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    AESSMEN       LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    RNGSMEN       LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHBSMENR    SRAM1SMEN     LL_AHB1_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHBSMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHBSMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHBSMENR    DMA1SMEN      LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    DMA2SMEN      LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    FLASHSMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    SRAM1SMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    CRCSMEN       LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    TSCSMEN       LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    AESSMEN       LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    RNGSMEN       LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHBSMENR    SRAM1SMEN     LL_AHB1_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBSMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1_GRP1 GRP1
  * @{
  */

/**
  * @brief  Enable APB1 GRP1 peripherals clock.
  * @rmtoll APBENR1     TIM2EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     TIM3EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     TIM6EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     TIM7EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     LPUART2EN     LL_APB1_GRP1_EnableClock\n
  *         APBENR1     LCDEN         LL_APB1_GRP1_EnableClock\n
  *         APBENR1     RTCAPBEN      LL_APB1_GRP1_EnableClock\n
  *         APBENR1     WWDGEN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     LPUART3EN     LL_APB1_GRP1_EnableClock\n
  *         APBENR1     USBFSEN       LL_APB1_GRP1_EnableClock\n
  *         APBENR1     SPI2EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     SPI3EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     CRSEN         LL_APB1_GRP1_EnableClock\n
  *         APBENR1     USART2EN      LL_APB1_GRP1_EnableClock\n
  *         APBENR1     USART3EN      LL_APB1_GRP1_EnableClock\n
  *         APBENR1     USART4EN      LL_APB1_GRP1_EnableClock\n
  *         APBENR1     LPUART1EN     LL_APB1_GRP1_EnableClock\n
  *         APBENR1     I2C1EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     I2C2EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     I2C3EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     OPAMPEN       LL_APB1_GRP1_EnableClock\n
  *         APBENR1     I2C4EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     LPTIM3EN      LL_APB1_GRP1_EnableClock\n
  *         APBENR1     PWREN         LL_APB1_GRP1_EnableClock\n
  *         APBENR1     DAC1EN        LL_APB1_GRP1_EnableClock\n
  *         APBENR1     LPTIM2EN      LL_APB1_GRP1_EnableClock
  *         APBENR1     LPTIM1EN      LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LCD
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USB
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_PWR
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC1
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APBENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APBENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 GRP1 peripheral clock is enabled or not
  * @rmtoll APBENR1     TIM2EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     TIM3EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     TIM6EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     TIM7EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     LPUART2EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     LCDEN          LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     RTCAPBEN       LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     WWDGEN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     LPUART3EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     USBFSEN        LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     SPI2EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     SPI3EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     CRSEN          LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     USART2EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     USART3EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     USART4EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     USART4EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     LPUART1EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     I2C1EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     I2C2EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     I2C3EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     OPAMPEN        LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     I2C4EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     LPTIM3EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     PWREN          LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     DAC1EN         LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     LPTIM2EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APBENR1     LPTIM1EN       LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LCD
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USB
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_PWR
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC1
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->APBENR1, Periphs) == Periphs);
}

/**
  * @brief  Disable APB1 GRP1 peripherals clock.
  * @rmtoll APBENR1     TIM2EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     TIM3EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     TIM6EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     TIM7EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     LPUART2EN      LL_APB1_GRP1_DisableClock\n
  *         APBENR1     LCDEN          LL_APB1_GRP1_DisableClock\n
  *         APBENR1     RTCAPBEN       LL_APB1_GRP1_DisableClock\n
  *         APBENR1     WWDGEN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     LPUART3EN      LL_APB1_GRP1_DisableClock\n
  *         APBENR1     USBFSEN        LL_APB1_GRP1_DisableClock\n
  *         APBENR1     SPI2EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     SPI3EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     CRSEN          LL_APB1_GRP1_DisableClock\n
  *         APBENR1     USART2EN       LL_APB1_GRP1_DisableClock\n
  *         APBENR1     USART3EN       LL_APB1_GRP1_DisableClock\n
  *         APBENR1     USART4EN       LL_APB1_GRP1_DisableClock\n
  *         APBENR1     LPUART1EN      LL_APB1_GRP1_DisableClock\n
  *         APBENR1     I2C1EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     I2C2EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     I2C3EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     OPAMPEN        LL_APB1_GRP1_DisableClock\n
  *         APBENR1     I2C4EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     LPTIM3EN       LL_APB1_GRP1_DisableClock\n
  *         APBENR1     PWREN          LL_APB1_GRP1_DisableClock\n
  *         APBENR1     DAC1EN         LL_APB1_GRP1_DisableClock\n
  *         APBENR1     LPTIM2EN       LL_APB1_GRP1_DisableClock\n
  *         APBENR1     LPTIM1EN       LL_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LCD
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USB
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_PWR
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC1
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APBENR1, Periphs);
}

/**
  * @brief  Force APB1 GRP1 peripherals reset.
  * @rmtoll APBRSTR1    TIM2RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    TIM3RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    TIM6RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    TIM7RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    LPUART2RST     LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    LCDRST         LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    RTCAPBRST      LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    WWDGRST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    LPUART3RST     LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    USBFSRST       LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    SPI2RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    SPI3RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    CRSRST         LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    USART2RST      LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    USART3RST      LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    USART4RST      LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    LPUART1RST     LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    I2C1RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    I2C2RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    I2C3RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    OPAMPRST       LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    I2C4RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    LPTIM3RST      LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    PWRRST         LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    DAC1RST        LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    LPTIM2RST      LL_APB1_GRP1_ForceReset\n
  *         APBRSTR1    LPTIM1RST      LL_APB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LCD
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USB
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_PWR
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC1
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APBRSTR1, Periphs);
}

/**
  * @brief  Release APB1 GRP1 peripherals reset.
  * @rmtoll APBRSTR1    TIM2RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    TIM3RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    TIM6RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    TIM7RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    LPUART2RST     LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    LCDRST         LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    RTCAPBRST      LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    WWDGRST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    LPUART3RST     LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    USBFSRST       LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    SPI2RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    SPI3RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    CRSRST         LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    USART2RST      LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    USART3RST      LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    USART4RST      LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    LPUART1RST     LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    I2C1RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    I2C2RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    I2C3RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    OPAMPRST       LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    I2C4RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    LPTIM3RST      LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    PWRRST         LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    DAC1RST        LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    LPTIM2RST      LL_APB1_GRP1_ReleaseReset\n
  *         APBRSTR1    LPTIM1RST      LL_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LCD
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USB
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_PWR
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC1
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APBRSTR1, Periphs);
}

/**
  * @brief  Enable APB1 GRP1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APBSMENR1   TIM2SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   TIM3SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   TIM6SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   TIM7SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   LPUART2SMEN    LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   LCDSMEN        LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   RTCAPBSMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   WWDGSMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   LPUART3SMEN    LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   USBFSSMEN      LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   SPI2SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   SPI3SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   CRSSMEN        LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   USART2SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   USART3SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   USART4SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   LPUART1SMEN    LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   I2C1SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   I2C2SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   I2C3SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   OPAMPSMEN      LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   I2C4SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   LPTIM3SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   PWRSMEN        LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   DAC1SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   LPTIM2SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APBSMENR1   LPTIM1SMEN     LL_APB1_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LCD
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USB
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_PWR
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC1
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APBSMENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APBSMENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB_1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APBSMENR1   TIM2SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   TIM3SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   TIM6SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   TIM7SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   LPUART2SMEN   LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   LCDSMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   RTCAPBSMEN    LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   WWDGSMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   LPUART3SMEN   LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   USBFSSMEN     LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   SPI2SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   SPI3SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   CRSSMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   USART2SMEN    LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   USART3SMEN    LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   USART4SMEN    LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   LPUART1SMEN   LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   I2C1SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   I2C2SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   I2C3SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   OPAMPSMEN     LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   I2C4SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   LPTIM3SMEN    LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   PWRSMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   DAC1SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   LPTIM2SMEN    LL_APB1_GRP1_DisableClockStopSleep\n
  *         APBSMENR1   LPTIM1SMEN    LL_APB1_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LCD
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USB
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_PWR
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC1
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APBSMENR1, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1_GRP2 GRP2
  * @{
  */

/**
  * @brief  Enable APB1 GRP2 peripherals clock.
  * @rmtoll APBENR2      SYSCFGEN      LL_APB1_GRP2_EnableClock\n
  *         APBENR2      TIM1EN        LL_APB1_GRP2_EnableClock\n
  *         APBENR2      SPI1EN        LL_APB1_GRP2_EnableClock\n
  *         APBENR2      USART1EN      LL_APB1_GRP2_EnableClock\n
  *         APBENR2      TIM15EN       LL_APB1_GRP2_EnableClock\n
  *         APBENR2      TIM16EN       LL_APB1_GRP2_EnableClock\n
  *         APBENR2      ADCEN         LL_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref LL_APB1_GRP2_PERIPH_COMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_VREFBUF
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref LL_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_USART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM15
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref LL_APB1_GRP2_PERIPH_ADC
  *
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APBENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APBENR2, Periphs);
  (void)tmpreg;
}
/**
  * @brief  Check if APB1 GRP2 peripheral clock is enabled or not
  * @rmtoll APBENR2      SYSCFGEN      LL_APB1_GRP2_IsEnabledClock\n
  *         APBENR2      TIM1EN        LL_APB1_GRP2_IsEnabledClock\n
  *         APBENR2      SPI1EN        LL_APB1_GRP2_IsEnabledClock\n
  *         APBENR2      USART1EN      LL_APB1_GRP2_IsEnabledClock\n
  *         APBENR2      TIM15EN       LL_APB1_GRP2_IsEnabledClock\n
  *         APBENR2      TIM16EN       LL_APB1_GRP2_IsEnabledClock\n
  *         APBENR2      ADCEN         LL_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref LL_APB1_GRP2_PERIPH_COMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_VREFBUF
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref LL_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_USART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM15
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref LL_APB1_GRP2_PERIPH_ADC
  * @note (*) peripheral not available on all devices
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APBENR2, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 GRP2 peripherals clock.
  * @rmtoll APBENR2      SYSCFGEN      LL_APB1_GRP2_DisableClock\n
  *         APBENR2      TIM1EN        LL_APB1_GRP2_DisableClock\n
  *         APBENR2      SPI1EN        LL_APB1_GRP2_DisableClock\n
  *         APBENR2      USART1EN      LL_APB1_GRP2_DisableClock\n
  *         APBENR2      TIM15EN       LL_APB1_GRP2_DisableClock\n
  *         APBENR2      TIM16EN       LL_APB1_GRP2_DisableClock\n
  *         APBENR2      ADCEN         LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref LL_APB1_GRP2_PERIPH_VREFBUF
  *         @arg @ref LL_APB1_GRP2_PERIPH_COMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref LL_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_USART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM15
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref LL_APB1_GRP2_PERIPH_ADC
  * @note (*) peripheral not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APBENR2, Periphs);
}

/**
  * @brief  Force APB1_GRP2 peripherals reset.
  * @rmtoll APBRSTR2     SYSCFGRST     LL_APB1_GRP2_ForceReset\n
  *         APBRSTR2     TIM1RST       LL_APB1_GRP2_ForceReset\n
  *         APBRSTR2     SPI1RST       LL_APB1_GRP2_ForceReset\n
  *         APBRSTR2     USART1RST     LL_APB1_GRP2_ForceReset\n
  *         APBRSTR2     TIM15RST      LL_APB1_GRP2_ForceReset\n
  *         APBRSTR2     TIM16RST      LL_APB1_GRP2_ForceReset\n
  *         APBRSTR2     ADCRST        LL_APB1_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref LL_APB1_GRP2_PERIPH_VREFBUF
  *         @arg @ref LL_APB1_GRP2_PERIPH_COMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref LL_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_USART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM15
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref LL_APB1_GRP2_PERIPH_ADC
  * @note (*) peripheral not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APBRSTR2, Periphs);
}

/**
  * @brief  Release APB1_GRP2 peripherals reset.
  * @rmtoll APBRSTR2     SYSCFGRST     LL_APB1_GRP2_ReleaseReset\n
  *         APBRSTR2     TIM1RST       LL_APB1_GRP2_ReleaseReset\n
  *         APBRSTR2     SPI1RST       LL_APB1_GRP2_ReleaseReset\n
  *         APBRSTR2     USART1RST     LL_APB1_GRP2_ReleaseReset\n
  *         APBRSTR2     TIM15RST      LL_APB1_GRP2_ReleaseReset\n
  *         APBRSTR2     TIM16RST      LL_APB1_GRP2_ReleaseReset\n
  *         APBRSTR2     ADCRST        LL_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref LL_APB1_GRP2_PERIPH_VREFBUF
  *         @arg @ref LL_APB1_GRP2_PERIPH_COMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref LL_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_USART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM15
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref LL_APB1_GRP2_PERIPH_ADC
  * @note (*) peripheral not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APBRSTR2, Periphs);
}

/**
  * @brief  Enable APB1_GRP2 peripheral clocks in Sleep and Stop modes
  * @rmtoll APBSMENR2    SYSCFGSMEN    LL_APB1_GRP2_EnableClockStopSleep\n
  *         APBSMENR2    TIM1SMEN      LL_APB1_GRP2_EnableClockStopSleep\n
  *         APBSMENR2    SPI1SMEN      LL_APB1_GRP2_EnableClockStopSleep\n
  *         APBSMENR2    USART1SMEN    LL_APB1_GRP2_EnableClockStopSleep\n
  *         APBSMENR2    TIM15SMEN     LL_APB1_GRP2_EnableClockStopSleep\n
  *         APBSMENR2    TIM16SMEN     LL_APB1_GRP2_EnableClockStopSleep\n
  *         APBSMENR2    ADCSMEN       LL_APB1_GRP2_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref LL_APB1_GRP2_PERIPH_VREFBUF
  *         @arg @ref LL_APB1_GRP2_PERIPH_COMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref LL_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_USART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM15
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref LL_APB1_GRP2_PERIPH_ADC
  * @note (*) peripheral not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APBSMENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APBSMENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB1_GRP2 peripheral clocks in Sleep and Stop modes
  * @rmtoll APBSMENR2    SYSCFGSMEN    LL_APB1_GRP2_DisableClockStopSleep\n
  *         APBSMENR2    TIM1SMEN      LL_APB1_GRP2_DisableClockStopSleep\n
  *         APBSMENR2    SPI1SMEN      LL_APB1_GRP2_DisableClockStopSleep\n
  *         APBSMENR2    USART1SMEN    LL_APB1_GRP2_DisableClockStopSleep\n
  *         APBSMENR2    TIM15SMEN     LL_APB1_GRP2_DisableClockStopSleep\n
  *         APBSMENR2    TIM16SMEN     LL_APB1_GRP2_DisableClockStopSleep\n
  *         APBSMENR2    ADCSMEN       LL_APB1_GRP2_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref LL_APB1_GRP2_PERIPH_VREFBUF
  *         @arg @ref LL_APB1_GRP2_PERIPH_COMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref LL_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_USART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM15
  *         @arg @ref LL_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref LL_APB1_GRP2_PERIPH_ADC
  * @note (*) peripheral not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APBSMENR2, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1_DBG DBG
  * @{
  */

/**
  * @brief  Enable APB1 DBG clock.
  * @rmtoll DBGCFGR      DBGEN      LL_APB1_DBG_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_APB1_DBG_EnableClock(void)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN);
  (void)tmpreg;
}
/**
  * @brief  Check if APB1 DBG clock is enabled or not
  * @rmtoll DBGCFGR      DBGEN      LL_APB1_DBG_IsEnabledClock
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_DBG_IsEnabledClock(void)
{
  return ((READ_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN) == (RCC_DBGCFGR_DBGEN)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 DBG peripherals clock.
  * @rmtoll DBGCFGR      DBGEN      LL_APB1_DBG_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_APB1_DBG_DisableClock(void)
{
  CLEAR_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGEN);
}

/**
  * @brief  Force APB1_DBG peripherals reset.
  * @rmtoll DBGCFGR     DBGRST     LL_APB1_DBG_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_APB1_DBG_ForceReset(void)
{
  SET_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGRST);
}

/**
  * @brief  Release APB1_DBG peripherals reset.
  * @rmtoll DBGCFGR     DBGRST     LL_APB1_DBG_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_APB1_DBG_ReleaseReset(void)
{
  CLEAR_BIT(RCC->DBGCFGR, RCC_DBGCFGR_DBGRST);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_IOP IOP
  * @{
  */

/**
  * @brief  Enable IOP peripherals clock.
  * @rmtoll IOPENR       GPIOAEN       LL_IOP_GRP1_EnableClock\n
  *         IOPENR       GPIOBEN       LL_IOP_GRP1_EnableClock\n
  *         IOPENR       GPIOCEN       LL_IOP_GRP1_EnableClock\n
  *         IOPENR       GPIODEN       LL_IOP_GRP1_EnableClock\n
  *         IOPENR       GPIOFEN       LL_IOP_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOF
  * @retval None
  */
__STATIC_INLINE void LL_IOP_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->IOPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->IOPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if IOP peripheral clock is enabled or not
  * @rmtoll IOPENR       GPIOAEN       LL_IOP_GRP1_IsEnabledClock\n
  *         IOPENR       GPIOBEN       LL_IOP_GRP1_IsEnabledClock\n
  *         IOPENR       GPIOCEN       LL_IOP_GRP1_IsEnabledClock\n
  *         IOPENR       GPIODEN       LL_IOP_GRP1_IsEnabledClock\n
  *         IOPENR       GPIOFEN       LL_IOP_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOF
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_IOP_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->IOPENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable IOP peripherals clock.
  * @rmtoll IOPENR       GPIOAEN       LL_IOP_GRP1_DisableClock\n
  *         IOPENR       GPIOBEN       LL_IOP_GRP1_DisableClock\n
  *         IOPENR       GPIOCEN       LL_IOP_GRP1_DisableClock\n
  *         IOPENR       GPIODEN       LL_IOP_GRP1_DisableClock\n
  *         IOPENR       GPIOFEN       LL_IOP_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOF
  * @retval None
  */
__STATIC_INLINE void LL_IOP_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->IOPENR, Periphs);
}

/**
  * @brief  Disable IOP peripherals clock.
  * @rmtoll IOPRSTR      GPIOARST      LL_IOP_GRP1_ForceReset\n
  *         IOPRSTR      GPIOBRST      LL_IOP_GRP1_ForceReset\n
  *         IOPRSTR      GPIOCRST      LL_IOP_GRP1_ForceReset\n
  *         IOPRSTR      GPIODRST      LL_IOP_GRP1_ForceReset\n
  *         IOPRSTR      GPIOFRST      LL_IOP_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_IOP_GRP1_PERIPH_ALL
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOF
  * @retval None
  */
__STATIC_INLINE void LL_IOP_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->IOPRSTR, Periphs);
}

/**
  * @brief  Release IOP peripherals reset.
  * @rmtoll IOPRSTR      GPIOARST      LL_IOP_GRP1_ReleaseReset\n
  *         IOPRSTR      GPIOBRST      LL_IOP_GRP1_ReleaseReset\n
  *         IOPRSTR      GPIOCRST      LL_IOP_GRP1_ReleaseReset\n
  *         IOPRSTR      GPIODRST      LL_IOP_GRP1_ReleaseReset\n
  *         IOPRSTR      GPIOFRST      LL_IOP_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_IOP_GRP1_PERIPH_ALL
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOF
  * @retval None
  */
__STATIC_INLINE void LL_IOP_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->IOPRSTR, Periphs);
}

/**
  * @brief  Enable IOP peripheral clocks in Sleep and Stop modes
  * @rmtoll IOPSMENR     GPIOASMEN     LL_IOP_GRP1_EnableClockStopSleep\n
  *         IOPSMENR     GPIOBSMEN     LL_IOP_GRP1_EnableClockStopSleep\n
  *         IOPSMENR     GPIOCSMEN     LL_IOP_GRP1_EnableClockStopSleep\n
  *         IOPSMENR     GPIODSMEN     LL_IOP_GRP1_EnableClockStopSleep\n
  *         IOPSMENR     GPIOFSMEN     LL_IOP_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOF
  * @retval None
  */
__STATIC_INLINE void LL_IOP_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->IOPSMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->IOPSMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable IOP peripheral clocks in Sleep and Stop modes
  * @rmtoll IOPSMENR     GPIOASMEN     LL_IOP_GRP1_DisableClockStopSleep\n
  *         IOPSMENR     GPIOBSMEN     LL_IOP_GRP1_DisableClockStopSleep\n
  *         IOPSMENR     GPIOCSMEN     LL_IOP_GRP1_DisableClockStopSleep\n
  *         IOPSMENR     GPIODSMEN     LL_IOP_GRP1_DisableClockStopSleep\n
  *         IOPSMENR     GPIOFSMEN     LL_IOP_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_IOP_GRP1_PERIPH_GPIOF
  * @retval None
  */
__STATIC_INLINE void LL_IOP_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->IOPSMENR, Periphs);
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

#endif /* __STM32U0xx_LL_BUS_H */
