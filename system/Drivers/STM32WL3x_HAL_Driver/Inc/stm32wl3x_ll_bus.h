/**
  ******************************************************************************
  * @file    stm32wl3x_ll_bus.h
  * @author  MCD Application Team
  * @brief   Header file of BUS LL module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WL3x_LL_BUS_H
#define STM32WL3x_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x.h"

/** @addtogroup STM32WL3x_LL_Driver
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

/** @defgroup BUS_LL_AHB1_GRP1_PERIPH  AHB PERIPH
  * @{
  */
#define LL_AHB1_GRP1_PERIPH_ALL            (RCC_AHBENR_DMAEN|\
                                            RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN|RCC_AHBENR_CRCEN|RCC_AHBENR_RNGEN|RCC_AHBENR_AESEN)
#define LL_AHB1_GRP1_PERIPH_DMA            RCC_AHBENR_DMAEN
#define LL_AHB1_GRP1_PERIPH_GPIOA          RCC_AHBENR_GPIOAEN
#define LL_AHB1_GRP1_PERIPH_GPIOB          RCC_AHBENR_GPIOBEN
#define LL_AHB1_GRP1_PERIPH_CRC            RCC_AHBENR_CRCEN
#define LL_AHB1_GRP1_PERIPH_RNG            RCC_AHBENR_RNGEN
#if defined(AES)
#define LL_AHB1_GRP1_PERIPH_AES           RCC_AHBENR_AESEN
#endif

#define LL_AHB1_GRP1_PERIPH_FLASH           RCC_AHBSMENR_FLASHSMEN
#define LL_AHB1_GRP1_PERIPH_SRAM0           RCC_AHBSMENR_SRAM0SMEN
#define LL_AHB1_GRP1_PERIPH_SRAM1           RCC_AHBSMENR_SRAM1SMEN

/**
  * @}
  */

/** @defgroup BUS_LL_APB0_GRP1_PERIPH  APB0 PERIPH
  * @{
  */
#define LL_APB0_GRP1_PERIPH_ALL            (RCC_APB0ENR_TIM2EN|\
                                            RCC_APB0ENR_TIM16EN|\
                                            RCC_APB0ENR_SYSCFGEN|\
                                            RCC_APB0ENR_LCDEN|\
                                            RCC_APB0ENR_COMPEN|RCC_APB0ENR_DACEN|RCC_APB0ENR_RTCEN|RCC_APB0ENR_LCSCEN|RCC_APB0ENR_WDGEN|RCC_APB0ENR_DBGMCUEN)
#if defined(TIM1)
#define LL_APB0_GRP1_PERIPH_TIM1           RCC_APB0ENR_TIM1EN
#endif
#if defined(TIM2)
#define LL_APB0_GRP1_PERIPH_TIM2           RCC_APB0ENR_TIM2EN
#endif
#if defined(TIM16)
#define LL_APB0_GRP1_PERIPH_TIM16          RCC_APB0ENR_TIM16EN
#endif
#if defined(TIM17)
#define LL_APB0_GRP1_PERIPH_TIM17          RCC_APB0ENR_TIM17EN
#endif
#define LL_APB0_GRP1_PERIPH_SYSCFG         RCC_APB0ENR_SYSCFGEN
#if defined(LCD)
#define LL_APB0_GRP1_PERIPH_LCDC           RCC_APB0ENR_LCDEN
#endif
#if defined(COMP1)
#define LL_APB0_GRP1_PERIPH_COMP           RCC_APB0ENR_COMPEN
#endif
#if defined(DAC1)
#define LL_APB0_GRP1_PERIPH_DAC            RCC_APB0ENR_DACEN
#endif
#define LL_APB0_GRP1_PERIPH_RTC            RCC_APB0ENR_RTCEN
#if defined(LCSC)
#define LL_APB0_GRP1_PERIPH_LCSC           RCC_APB0ENR_LCSCEN
#endif
#define LL_APB0_GRP1_PERIPH_WDG            RCC_APB0ENR_WDGEN
#if defined(DBGMCU)
#define LL_APB0_GRP1_PERIPH_DBGMCU         RCC_APB0ENR_DBGMCUEN
#endif
/**
  * @}
  */


/** @defgroup BUS_LL_APB1_GRP1_PERIPH  APB1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL            (RCC_APB1ENR_SPI1EN|\
                                            RCC_APB1ENR_ADCDIGEN|\
                                            RCC_APB1ENR_ADCANAEN|RCC_APB1ENR_LPUARTEN|RCC_APB1ENR_USARTEN|RCC_APB1ENR_SPI3EN|RCC_APB1ENR_I2C1EN|RCC_APB1ENR_I2C2EN)
#if defined(SPI1)
#define LL_APB1_GRP1_PERIPH_SPI1           RCC_APB1ENR_SPI1EN
#endif
#define LL_APB1_GRP1_PERIPH_ADCDIG         RCC_APB1ENR_ADCDIGEN
#define LL_APB1_GRP1_PERIPH_ADCANA         RCC_APB1ENR_ADCANAEN
#define LL_APB1_GRP1_PERIPH_LPUART1         RCC_APB1ENR_LPUARTEN
#define LL_APB1_GRP1_PERIPH_USART1          RCC_APB1ENR_USARTEN
#define LL_APB1_GRP1_PERIPH_SPI3           RCC_APB1ENR_SPI3EN
#define LL_APB1_GRP1_PERIPH_I2C1           RCC_APB1ENR_I2C1EN
#if defined(I2C2)
#define LL_APB1_GRP1_PERIPH_I2C2           RCC_APB1ENR_I2C2EN
#endif
/**
  * @}
  */

/** @defgroup BUS_LL_APB2_GRP1_PERIPH  APB2 PERIPH
  * @{
  */
#if defined(MR_SUBG_RADIO)
#define LL_APB2_GRP1_PERIPH_ALL      (RCC_APB2ENR_MRSUBGEN|RCC_APB2ENR_LPAWUREN)
#define LL_APB2_GRP1_PERIPH_MRSUBG   RCC_APB2ENR_MRSUBGEN
#define LL_APB2_GRP1_PERIPH_LPAWUR   RCC_APB2ENR_LPAWUREN
#endif
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
  * @brief  Enable AHB peripherals clock.
  * @rmtoll AHBENR      DMAEN        LL_AHB1_GRP1_EnableClock
  *         AHBENR      GPIOAEN      LL_AHB1_GRP1_EnableClock
  *         AHBENR      GPIOBEN      LL_AHB1_GRP1_EnableClock
  *         AHBENR      CRCEN        LL_AHB1_GRP1_EnableClock
  *         AHBENR      RNGEN        LL_AHB1_GRP1_EnableClock
  *         AHBENR      AESEN        LL_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
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
  * @brief  Check if AHB peripheral clock is enabled or not
  * @rmtoll AHBENR      DMAEN          LL_AHB1_GRP1_IsEnabledClock
  *         AHBENR      GPIOAEN        LL_AHB1_GRP1_IsEnabledClock
  *         AHBENR      GPIOBEN        LL_AHB1_GRP1_IsEnabledClock
  *         AHBENR      CRCEN          LL_AHB1_GRP1_IsEnabledClock
  *         AHBENR      RNGEN          LL_AHB1_GRP1_IsEnabledClock
  *         AHBENR      AESEN          LL_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHBENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB peripherals clock.
  * @rmtoll AHBENR      DMAENN        LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOAEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOBEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      CRCEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      RNGEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      AESEN         LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBENR, Periphs);
}

/**
  * @brief  Enable AHB peripherals clock in Sleep Mode
  * @rmtoll AHBENR      DMAENN        LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOAEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOBEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      SRAM0EN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      SRMA1EN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      CRCEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      RNGEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      AESEN         LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_FLASH
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_SRAM0
  * @arg LL_AHB1_GRP1_PERIPH_SRAM1
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockSleepMode(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHBSMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHBSMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB peripheral clock is enabled or not in Sleep Mode
  * @rmtoll AHBENR      DMAENN        LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOAEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOBEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      SRAM0EN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      SRMA1EN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      CRCEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      RNGEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      AESEN         LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_FLASH
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_SRAM0
  * @arg LL_AHB1_GRP1_PERIPH_SRAM1
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockSleepMode(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHBSMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB peripherals clock in Sleep Mode
  * @rmtoll AHBENR      DMAENN        LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOAEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      GPIOBEN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      SRAM0EN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      SRMA1EN       LL_AHB1_GRP1_DisableClock
  *         AHBENR      CRCEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      RNGEN         LL_AHB1_GRP1_DisableClock
  *         AHBENR      AESEN         LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_FLASH
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_SRAM0
  * @arg LL_AHB1_GRP1_PERIPH_SRAM1
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockSleepMode(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBSMENR, Periphs);
}

/**
  * @brief  Force AHB peripherals reset.
  * @rmtoll AHBRSTR     DMARST        LL_AHB1_GRP1_ForceReset
  *         AHBRSTR     GPIOARST      LL_AHB1_GRP1_ForceReset
  *         AHBRSTR     GPIOBRST      LL_AHB1_GRP1_ForceReset
  *         AHBRSTR     CRCRST        LL_AHB1_GRP1_ForceReset
  *         AHBRSTR     RNGRST        LL_AHB1_GRP1_ForceReset
  *         AHBRSTR     AESRST        LL_AHB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHBRSTR, Periphs);
}

/**
  * @brief  Release AHB peripherals reset.
  * @rmtoll AHBRSTR     DMARST       LL_AHB1_GRP1_ReleaseReset
  *         AHBRSTR     GPIOARST     LL_AHB1_GRP1_ReleaseReset
  *         AHBRSTR     GPIOBRST     LL_AHB1_GRP1_ReleaseReset
  *         AHBRSTR     CRCRST       LL_AHB1_GRP1_ReleaseReset
  *         AHBRSTR     RNGRST       LL_AHB1_GRP1_ReleaseReset
  *         AHBRSTR     AESRST       LL_AHB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_AHB1_GRP1_PERIPH_DMA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOA
  * @arg LL_AHB1_GRP1_PERIPH_GPIOB
  * @arg LL_AHB1_GRP1_PERIPH_CRC
  * @arg LL_AHB1_GRP1_PERIPH_RNG
  * @arg LL_AHB1_GRP1_PERIPH_AES
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHBRSTR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB0 APB0
  * @{
  */

/**
  * @brief  Enable APB0 peripherals clock.
  * @rmtoll APB0ENR     TIM2EN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     TIM16EN    LL_APB0_GRP1_EnableClock
  *         APB0ENR     SYSCFGEN   LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCDEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     COMPEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     DACEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     RTCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCSCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     WDGEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     DBGMCUEN   LL_APB0_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  * @retval None
  */
__STATIC_INLINE void LL_APB0_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB0ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB0ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB0 peripheral clock is enabled or not
  * @rmtoll APB0ENR     TIM2EN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     TIM16EN    LL_APB0_GRP1_EnableClock
  *         APB0ENR     SYSCFGEN   LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCDEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     COMPEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     DACEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     RTCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCSCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     WDGEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     DBGMCUEN   LL_APB0_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  * @retval None
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB0_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB0ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB0 peripherals clock.
  * @rmtoll APB0ENR     TIM2EN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     TIM16EN    LL_APB0_GRP1_EnableClock
  *         APB0ENR     SYSCFGEN   LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCDEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     COMPEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     DACEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     RTCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCSCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     WDGEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     DBGMCUEN   LL_APB0_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  * @retval None
  * @retval None
  */
__STATIC_INLINE void LL_APB0_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB0ENR, Periphs);
}

/**
  * @brief  Enable APB0 peripherals clock in sleep mode.
  * @rmtoll APB0ENR     TIM2EN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     TIM16EN    LL_APB0_GRP1_EnableClock
  *         APB0ENR     SYSCFGEN   LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCDEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     COMPEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     DACEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     RTCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCSCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     WDGEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     DBGMCUEN   LL_APB0_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  * @retval None
  */
__STATIC_INLINE void LL_APB0_GRP1_EnableClockSleepMode(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB0SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB0SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB0 peripheral clock is enabled in sleep mode or not
  * @rmtoll APB0ENR     TIM2EN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     TIM16EN    LL_APB0_GRP1_EnableClock
  *         APB0ENR     SYSCFGEN   LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCDEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     COMPEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     DACEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     RTCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCSCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     WDGEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     DBGMCUEN   LL_APB0_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  *
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB0_GRP1_IsEnabledClockSleepMode(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB0SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB0 peripherals clock in sleep mode.
  * @rmtoll APB0ENR     TIM2EN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     TIM16EN    LL_APB0_GRP1_EnableClock
  *         APB0ENR     SYSCFGEN   LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCDEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     COMPEN     LL_APB0_GRP1_EnableClock
  *         APB0ENR     DACEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     RTCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     LCSCEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     WDGEN      LL_APB0_GRP1_EnableClock
  *         APB0ENR     DBGMCUEN   LL_APB0_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  * @retval None
  */
__STATIC_INLINE void LL_APB0_GRP1_DisableClockSleepMode(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB0SMENR, Periphs);
}

/**
  * @brief  Force APB0 peripherals reset.
  * @rmtoll APB0RSTR    TIM2RST      LL_APB0_GRP1_ForceReset
  *         APB0RSTR    TIM16RST     LL_APB0_GRP1_ForceReset
  *         APB0RSTR    SYSCFGRST    LL_APB0_GRP1_ForceReset
  *         APB0RSTR    LCDRST      LL_APB0_GRP1_ForceReset
  *         APB0RSTR    COMPRST      LL_APB0_GRP1_ForceReset
  *         APB0RSTR    DACRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    RTCRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    LCSCRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    WDGRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    DBGMCURST    LL_APB0_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  * @retval None
  */
__STATIC_INLINE void LL_APB0_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB0RSTR, Periphs);
}

/**
  * @brief  Release APB0 peripherals reset.
  * @rmtoll APB0RSTR    TIM2RST      LL_APB0_GRP1_ForceReset
  *         APB0RSTR    TIM16RST     LL_APB0_GRP1_ForceReset
  *         APB0RSTR    SYSCFGRST    LL_APB0_GRP1_ForceReset
  *         APB0RSTR    LCDRST      LL_APB0_GRP1_ForceReset
  *         APB0RSTR    COMPRST      LL_APB0_GRP1_ForceReset
  *         APB0RSTR    DACRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    RTCRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    LCSCRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    WDGRST       LL_APB0_GRP1_ForceReset
  *         APB0RSTR    DBGMCURST    LL_APB0_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB0_GRP1_PERIPH_TIM2
  * @arg LL_APB0_GRP1_PERIPH_TIM16
  * @arg LL_APB0_GRP1_PERIPH_SYSCFG
  * @arg LL_APB0_GRP1_PERIPH_LCDC
  * @arg LL_APB0_GRP1_PERIPH_COMP
  * @arg LL_APB0_GRP1_PERIPH_DAC
  * @arg LL_APB0_GRP1_PERIPH_RTC
  * @arg LL_APB0_GRP1_PERIPH_LCSC
  * @arg LL_APB0_GRP1_PERIPH_WDG
  * @arg LL_APB0_GRP1_PERIPH_DBGMCU
  * @retval None
  */
__STATIC_INLINE void LL_APB0_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB0RSTR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_GRP1_EnableClock
  *         APB1ENR      ADCDIGEN      LL_APB1_GRP1_EnableClock
  *         APB1ENR      ADCANAEN      LL_APB1_GRP1_EnableClock
  *         APB1ENR      LPUARTEN      LL_APB1_GRP1_EnableClock
  *         APB1ENR      USARTEN       LL_APB1_GRP1_EnableClock
  *         APB1ENR      SPI3EN        LL_APB1_GRP1_EnableClock
  *         APB1ENR      I2C1EN        LL_APB1_GRP1_EnableClock
  *         APB1ENR      I2C2EN        LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_ADCANA
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      ADCDIGEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      ADCANAEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      LPUARTEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      USARTEN       LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      SPI3EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C2EN        LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_ADCANA
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      ADCDIGEN      LL_APB1_GRP1_DisableClock
  *         APB1ENR      ADCANAEN      LL_APB1_GRP1_DisableClock
  *         APB1ENR      LPUARTEN      LL_APB1_GRP1_DisableClock
  *         APB1ENR      USARTEN       LL_APB1_GRP1_DisableClock
  *         APB1ENR      SPI3EN        LL_APB1_GRP1_DisableClock
  *         APB1ENR      I2C1EN        LL_APB1_GRP1_DisableClock
  *         APB1ENR      I2C2EN        LL_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_ADCANA
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock in sleep mode.
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      ADCDIGEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      LPUARTEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      USARTEN       LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      SPI3EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C2EN        LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockSleepMode(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not in sleep mode.
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      ADCDIGEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      LPUARTEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      USARTEN       LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      SPI3EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C2EN        LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockSleepMode(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock in sleep mode.
  * @rmtoll APB1ENR      SPI1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      ADCDIGEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      LPUARTEN      LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      USARTEN       LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      SPI3EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C1EN        LL_APB1_GRP1_IsEnabledClock
  *         APB1ENR      I2C2EN        LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockSleepMode(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SMENR, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR     SPI1RST       LL_APB1_GRP1_ForceReset
  *         APB1RSTR     ADCRST        LL_APB1_GRP1_ForceReset
  *         APB1RSTR     LPUARTRST     LL_APB1_GRP1_ForceReset
  *         APB1RSTR     USARTRST      LL_APB1_GRP1_ForceReset
  *         APB1RSTR     SPI3RST       LL_APB1_GRP1_ForceReset
  *         APB1RSTR     I2C1RST       LL_APB1_GRP1_ForceReset
  *         APB1RSTR     I2C2RST       LL_APB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_ALL
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR     SPI1RST       LL_APB1_GRP1_ReleaseReset
  *         APB1RSTR     ADCRST        LL_APB1_GRP1_ReleaseReset
  *         APB1RSTR     LPUARTRST     LL_APB1_GRP1_ReleaseReset
  *         APB1RSTR     USARTRST      LL_APB1_GRP1_ReleaseReset
  *         APB1RSTR     SPI3RST       LL_APB1_GRP1_ReleaseReset
  *         APB1RSTR     I2C1RST       LL_APB1_GRP1_ReleaseReset
  *         APB1RSTR     I2C2RST       LL_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB1_GRP1_PERIPH_ALL
  * @arg LL_APB1_GRP1_PERIPH_SPI1
  * @arg LL_APB1_GRP1_PERIPH_ADCDIG
  * @arg LL_APB1_GRP1_PERIPH_LPUART1
  * @arg LL_APB1_GRP1_PERIPH_USART1
  * @arg LL_APB1_GRP1_PERIPH_SPI3
  * @arg LL_APB1_GRP1_PERIPH_I2C1
  * @arg LL_APB1_GRP1_PERIPH_I2C2
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */
/**
  * @brief  Enable APB2 peripherals clock.
  * @rmtoll APB2ENR      MRSUBGEN       LL_APB2_GRP1_EnableClock
  * @rmtoll APB2ENR      LPAWUREN       LL_APB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB2_GRP1_PERIPH_MRSUBG
  * @arg LL_APB2_GRP1_PERIPH_LPAWUR
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
  * @rmtoll APB2ENR      MRSUBGEN       LL_APB2_GRP1_IsEnabledClock
  * @rmtoll APB2ENR      LPAWUREN       LL_APB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB2_GRP1_PERIPH_MRSUBG
  * @arg LL_APB2_GRP1_PERIPH_LPAWUR
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB2ENR      MRSUBGEN       LL_APB2_GRP1_DisableClock
  * @rmtoll APB2ENR      LPAWUREN        LL_APB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB2_GRP1_PERIPH_MRSUBG
  * @arg LL_APB2_GRP1_PERIPH_LPAWUR
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll APB2RSTR     MRSUBGRST       LL_APB2_GRP1_ForceReset
  * @rmtoll APB2RSTR     LPAWURRST        LL_APB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB2_GRP1_PERIPH_MRSUBG
  * @arg LL_APB2_GRP1_PERIPH_LPAWUR
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll APB2RSTR     MRSUBGRST       LL_APB2_GRP1_ReleaseReset
  * @rmtoll APB2RSTR     LPAWURRST        LL_APB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  * @arg LL_APB2_GRP1_PERIPH_MRSUBG
  * @arg LL_APB2_GRP1_PERIPH_LPAWUR
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
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

#endif /* STM32WL3x_LL_BUS_H */
