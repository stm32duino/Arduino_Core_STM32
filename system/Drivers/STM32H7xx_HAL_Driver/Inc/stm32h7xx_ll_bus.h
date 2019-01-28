/**
  ******************************************************************************
  * @file    stm32h7xx_ll_bus.h
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
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
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_LL_BUS_H
#define STM32H7xx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx.h"

/** @addtogroup STM32H7xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Constants BUS Exported Constants
  * @{
  */

/** @defgroup BUS_LL_EC_AHB3_GRP1_PERIPH  AHB3 GRP1 PERIPH
  * @{
  */
#define LL_AHB3_GRP1_PERIPH_MDMA           RCC_AHB3ENR_MDMAEN
#define LL_AHB3_GRP1_PERIPH_DMA2D          RCC_AHB3ENR_DMA2DEN
#define LL_AHB3_GRP1_PERIPH_JPGDEC         RCC_AHB3ENR_JPGDECEN
#define LL_AHB3_GRP1_PERIPH_FMC            RCC_AHB3ENR_FMCEN
#define LL_AHB3_GRP1_PERIPH_QSPI           RCC_AHB3ENR_QSPIEN
#define LL_AHB3_GRP1_PERIPH_SDMMC1         RCC_AHB3ENR_SDMMC1EN
#define LL_AHB3_GRP1_PERIPH_FLASH          RCC_AHB3LPENR_FLASHLPEN
#define LL_AHB3_GRP1_PERIPH_DTCM1          RCC_AHB3LPENR_DTCM1LPEN
#define LL_AHB3_GRP1_PERIPH_DTCM2          RCC_AHB3LPENR_DTCM2LPEN
#define LL_AHB3_GRP1_PERIPH_ITCM           RCC_AHB3LPENR_ITCMLPEN
#define LL_AHB3_GRP1_PERIPH_AXISRAM        RCC_AHB3LPENR_AXISRAMLPEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_AHB1_GRP1_PERIPH  AHB1 GRP1 PERIPH
  * @{
  */
#define LL_AHB1_GRP1_PERIPH_DMA1           RCC_AHB1ENR_DMA1EN
#define LL_AHB1_GRP1_PERIPH_DMA2           RCC_AHB1ENR_DMA2EN
#define LL_AHB1_GRP1_PERIPH_ADC12          RCC_AHB1ENR_ADC12EN
#define LL_AHB1_GRP1_PERIPH_ETH1MAC        RCC_AHB1ENR_ETH1MACEN
#define LL_AHB1_GRP1_PERIPH_ETH1TX         RCC_AHB1ENR_ETH1TXEN
#define LL_AHB1_GRP1_PERIPH_ETH1RX         RCC_AHB1ENR_ETH1RXEN
#define LL_AHB1_GRP1_PERIPH_USB1OTGHS      RCC_AHB1ENR_USB1OTGHSEN
#define LL_AHB1_GRP1_PERIPH_USB1OTGHSULPI  RCC_AHB1ENR_USB1OTGHSULPIEN
#define LL_AHB1_GRP1_PERIPH_USB2OTGHS      RCC_AHB1ENR_USB2OTGHSEN
#define LL_AHB1_GRP1_PERIPH_USB2OTGHSULPI  RCC_AHB1ENR_USB2OTGHSULPIEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_DCMI           RCC_AHB2ENR_DCMIEN
#if defined(CRYP)
#define LL_AHB2_GRP1_PERIPH_CRYP           RCC_AHB2ENR_CRYPEN
#endif /* CRYP */
#if defined(HASH)
#define LL_AHB2_GRP1_PERIPH_HASH           RCC_AHB2ENR_HASHEN
#endif /* HASH */
#define LL_AHB2_GRP1_PERIPH_RNG            RCC_AHB2ENR_RNGEN
#define LL_AHB2_GRP1_PERIPH_SDMMC2         RCC_AHB2ENR_SDMMC2EN
#define LL_AHB2_GRP1_PERIPH_D2SRAM1        RCC_AHB2ENR_D2SRAM1EN
#define LL_AHB2_GRP1_PERIPH_D2SRAM2        RCC_AHB2ENR_D2SRAM2EN
#define LL_AHB2_GRP1_PERIPH_D2SRAM3        RCC_AHB2ENR_D2SRAM3EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_AHB4_GRP1_PERIPH  AHB4 GRP1 PERIPH
  * @{
  */
#define LL_AHB4_GRP1_PERIPH_GPIOA          RCC_AHB4ENR_GPIOAEN
#define LL_AHB4_GRP1_PERIPH_GPIOB          RCC_AHB4ENR_GPIOBEN
#define LL_AHB4_GRP1_PERIPH_GPIOC          RCC_AHB4ENR_GPIOCEN
#define LL_AHB4_GRP1_PERIPH_GPIOD          RCC_AHB4ENR_GPIODEN
#define LL_AHB4_GRP1_PERIPH_GPIOE          RCC_AHB4ENR_GPIOEEN
#define LL_AHB4_GRP1_PERIPH_GPIOF          RCC_AHB4ENR_GPIOFEN
#define LL_AHB4_GRP1_PERIPH_GPIOG          RCC_AHB4ENR_GPIOGEN
#define LL_AHB4_GRP1_PERIPH_GPIOH          RCC_AHB4ENR_GPIOHEN
#define LL_AHB4_GRP1_PERIPH_GPIOI          RCC_AHB4ENR_GPIOIEN
#define LL_AHB4_GRP1_PERIPH_GPIOJ          RCC_AHB4ENR_GPIOJEN
#define LL_AHB4_GRP1_PERIPH_GPIOK          RCC_AHB4ENR_GPIOKEN
#define LL_AHB4_GRP1_PERIPH_CRC            RCC_AHB4ENR_CRCEN
#define LL_AHB4_GRP1_PERIPH_BDMA           RCC_AHB4ENR_BDMAEN
#define LL_AHB4_GRP1_PERIPH_ADC3           RCC_AHB4ENR_ADC3EN
#if defined(HSEM)
#define LL_AHB4_GRP1_PERIPH_HSEM           RCC_AHB4ENR_HSEMEN
#endif /* HSEM */
#define LL_AHB4_GRP1_PERIPH_BKPRAM         RCC_AHB4ENR_BKPRAMEN
#define LL_AHB4_GRP1_PERIPH_D3SRAM1        RCC_AHB4ENR_D3SRAM1EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB3_GRP1_PERIPH  APB3 GRP1 PERIPH
  * @{
  */
#define LL_APB3_GRP1_PERIPH_LTDC           RCC_APB3ENR_LTDCEN
#define LL_APB3_GRP1_PERIPH_WWDG1          RCC_APB3ENR_WWDG1EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_TIM2           RCC_APB1LENR_TIM2EN
#define LL_APB1_GRP1_PERIPH_TIM3           RCC_APB1LENR_TIM3EN
#define LL_APB1_GRP1_PERIPH_TIM4           RCC_APB1LENR_TIM4EN
#define LL_APB1_GRP1_PERIPH_TIM5           RCC_APB1LENR_TIM5EN
#define LL_APB1_GRP1_PERIPH_TIM6           RCC_APB1LENR_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7           RCC_APB1LENR_TIM7EN
#define LL_APB1_GRP1_PERIPH_TIM12          RCC_APB1LENR_TIM12EN
#define LL_APB1_GRP1_PERIPH_TIM13          RCC_APB1LENR_TIM13EN
#define LL_APB1_GRP1_PERIPH_TIM14          RCC_APB1LENR_TIM14EN
#define LL_APB1_GRP1_PERIPH_LPTIM1         RCC_APB1LENR_LPTIM1EN
#define LL_APB1_GRP1_PERIPH_SPI2           RCC_APB1LENR_SPI2EN
#define LL_APB1_GRP1_PERIPH_SPI3           RCC_APB1LENR_SPI3EN
#define LL_APB1_GRP1_PERIPH_SPDIFRX        RCC_APB1LENR_SPDIFRXEN
#define LL_APB1_GRP1_PERIPH_USART2         RCC_APB1LENR_USART2EN
#define LL_APB1_GRP1_PERIPH_USART3         RCC_APB1LENR_USART3EN
#define LL_APB1_GRP1_PERIPH_UART4          RCC_APB1LENR_UART4EN
#define LL_APB1_GRP1_PERIPH_UART5          RCC_APB1LENR_UART5EN
#define LL_APB1_GRP1_PERIPH_I2C1           RCC_APB1LENR_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2           RCC_APB1LENR_I2C2EN
#define LL_APB1_GRP1_PERIPH_I2C3           RCC_APB1LENR_I2C3EN
#define LL_APB1_GRP1_PERIPH_CEC            RCC_APB1LENR_CECEN
#define LL_APB1_GRP1_PERIPH_DAC12          RCC_APB1LENR_DAC12EN
#define LL_APB1_GRP1_PERIPH_UART7          RCC_APB1LENR_UART7EN
#define LL_APB1_GRP1_PERIPH_UART8          RCC_APB1LENR_UART8EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_CRS            RCC_APB1HENR_CRSEN
#define LL_APB1_GRP2_PERIPH_SWPMI1          RCC_APB1HENR_SWPMIEN
#define LL_APB1_GRP2_PERIPH_OPAMP          RCC_APB1HENR_OPAMPEN
#define LL_APB1_GRP2_PERIPH_MDIOS          RCC_APB1HENR_MDIOSEN
#define LL_APB1_GRP2_PERIPH_FDCAN          RCC_APB1HENR_FDCANEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_TIM1           RCC_APB2ENR_TIM1EN
#define LL_APB2_GRP1_PERIPH_TIM8           RCC_APB2ENR_TIM8EN
#define LL_APB2_GRP1_PERIPH_USART1         RCC_APB2ENR_USART1EN
#define LL_APB2_GRP1_PERIPH_USART6         RCC_APB2ENR_USART6EN
#define LL_APB2_GRP1_PERIPH_SPI1           RCC_APB2ENR_SPI1EN
#define LL_APB2_GRP1_PERIPH_SPI4           RCC_APB2ENR_SPI4EN
#define LL_APB2_GRP1_PERIPH_TIM15          RCC_APB2ENR_TIM15EN
#define LL_APB2_GRP1_PERIPH_TIM16          RCC_APB2ENR_TIM16EN
#define LL_APB2_GRP1_PERIPH_TIM17          RCC_APB2ENR_TIM17EN
#define LL_APB2_GRP1_PERIPH_SPI5           RCC_APB2ENR_SPI5EN
#define LL_APB2_GRP1_PERIPH_SAI1           RCC_APB2ENR_SAI1EN
#define LL_APB2_GRP1_PERIPH_SAI2           RCC_APB2ENR_SAI2EN
#define LL_APB2_GRP1_PERIPH_SAI3           RCC_APB2ENR_SAI3EN
#define LL_APB2_GRP1_PERIPH_DFSDM1         RCC_APB2ENR_DFSDM1EN
#define LL_APB2_GRP1_PERIPH_HRTIM          RCC_APB2ENR_HRTIMEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB4_GRP1_PERIPH  APB4 GRP1 PERIPH
  * @{
  */
#define LL_APB4_GRP1_PERIPH_SYSCFG         RCC_APB4ENR_SYSCFGEN
#define LL_APB4_GRP1_PERIPH_LPUART1        RCC_APB4ENR_LPUART1EN
#define LL_APB4_GRP1_PERIPH_SPI6           RCC_APB4ENR_SPI6EN
#define LL_APB4_GRP1_PERIPH_I2C4           RCC_APB4ENR_I2C4EN
#define LL_APB4_GRP1_PERIPH_LPTIM2         RCC_APB4ENR_LPTIM2EN
#define LL_APB4_GRP1_PERIPH_LPTIM3         RCC_APB4ENR_LPTIM3EN
#define LL_APB4_GRP1_PERIPH_LPTIM4         RCC_APB4ENR_LPTIM4EN
#define LL_APB4_GRP1_PERIPH_LPTIM5         RCC_APB4ENR_LPTIM5EN
#define LL_APB4_GRP1_PERIPH_COMP12         RCC_APB4ENR_COMP12EN
#define LL_APB4_GRP1_PERIPH_VREF           RCC_APB4ENR_VREFEN
#define LL_APB4_GRP1_PERIPH_RTCAPB         RCC_APB4ENR_RTCAPBEN
#define LL_APB4_GRP1_PERIPH_SAI4           RCC_APB4ENR_SAI4EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_CLKAM_PERIPH  CLKAM PERIPH
  * @{
  */
#define LL_CLKAM_PERIPH_BDMA          RCC_D3AMR_BDMAAMEN
#define LL_CLKAM_PERIPH_LPUART1       RCC_D3AMR_LPUART1AMEN
#define LL_CLKAM_PERIPH_SPI6          RCC_D3AMR_SPI6AMEN
#define LL_CLKAM_PERIPH_I2C4          RCC_D3AMR_I2C4AMEN
#define LL_CLKAM_PERIPH_LPTIM2        RCC_D3AMR_LPTIM2AMEN
#define LL_CLKAM_PERIPH_LPTIM3        RCC_D3AMR_LPTIM3AMEN
#define LL_CLKAM_PERIPH_LPTIM4        RCC_D3AMR_LPTIM4AMEN
#define LL_CLKAM_PERIPH_LPTIM5        RCC_D3AMR_LPTIM5AMEN
#define LL_CLKAM_PERIPH_COMP12        RCC_D3AMR_COMP12AMEN
#define LL_CLKAM_PERIPH_VREF          RCC_D3AMR_VREFAMEN
#define LL_CLKAM_PERIPH_RTC           RCC_D3AMR_RTCAMEN
#define LL_CLKAM_PERIPH_CRC           RCC_D3AMR_CRCAMEN
#define LL_CLKAM_PERIPH_SAI4          RCC_D3AMR_SAI4AMEN
#define LL_CLKAM_PERIPH_ADC3          RCC_D3AMR_ADC3AMEN
#define LL_CLKAM_PERIPH_BKPRAM        RCC_D3AMR_BKPRAMAMEN
#define LL_CLKAM_PERIPH_SRAM4         RCC_D3AMR_SRAM4AMEN
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

/** @defgroup BUS_LL_EF_AHB3 AHB3
  * @{
  */

/**
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      MDMAEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      DMA2DEN       LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      JPGDECEN      LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      FMCEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      QSPIEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      SDMMC1EN      LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      DTCM1EN       LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      DTCM2EN       LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      ITCMEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      AXISRAMEN     LL_AHB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_MDMA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB3_GRP1_PERIPH_JPGDEC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM1 (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM2 (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ITCM (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AXISRAM (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB3ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB3 peripheral clock is enabled or not
  * @rmtoll AHB3ENR      MDMAEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      DMA2DEN       LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      JPGDECEN      LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      FMCEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      QSPIEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      SDMMC1EN      LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      DTCM1EN       LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      DTCM2EN       LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      ITCMEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      AXISRAMEN     LL_AHB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_MDMA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB3_GRP1_PERIPH_JPGDEC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM1 (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM2 (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ITCM (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AXISRAM (*)
  *
  *         (*) value not defined in all devices.
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB3ENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      MDMAEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      DMA2DEN       LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      JPGDECEN      LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      FMCEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      QSPIEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      SDMMC1EN      LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      DTCM1EN       LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      DTCM2EN       LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      ITCMEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      AXISRAMEN     LL_AHB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_MDMA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB3_GRP1_PERIPH_JPGDEC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM1 (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM2 (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ITCM (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AXISRAM (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3ENR, Periphs);
}

/**
  * @brief  Force AHB3 peripherals reset.
  * @rmtoll AHB3RSTR     MDMARST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     DMA2DRST      LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     JPGDECRST     LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     FMCRST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     QSPIRST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     SDMMC1RST     LL_AHB3_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_MDMA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB3_GRP1_PERIPH_JPGDEC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SDMMC1
  * @retval None
*/
__STATIC_INLINE void LL_AHB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3RSTR, Periphs);
}

/**
  * @brief  Release AHB3 peripherals reset.
  * @rmtoll AHB3RSTR     MDMARST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     DMA2DRST      LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     JPGDECRST     LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     FMCRST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     QSPIRST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     SDMMC1RST     LL_AHB3_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_MDMA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB3_GRP1_PERIPH_JPGDEC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SDMMC1
  * @retval None
*/
__STATIC_INLINE void LL_AHB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3RSTR, Periphs);
}

/**
  * @brief  Enable AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB3LPENR    MDMALPEN      LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    DMA2DLPEN     LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    JPGDECLPEN    LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    FMCLPEN       LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    QSPILPEN      LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    SDMMC1LPEN    LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    FLASHLPEN     LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    DTCM1LPEN     LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    DTCM2LPEN     LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    ITCMLPEN      LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    AXISRAMLPEN   LL_AHB3_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB3_GRP1_PERIPH_JPGDEC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ITCM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AXISRAM
  * @retval None
*/
__STATIC_INLINE void LL_AHB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB3LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB3LPENR    MDMALPEN      LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    DMA2DLPEN     LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    JPGDECLPEN    LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    FMCLPEN       LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    QSPILPEN      LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    SDMMC1LPEN    LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    FLASHLPEN     LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    DTCM1LPEN     LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    DTCM2LPEN     LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    ITCMLPEN      LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    AXISRAMLPEN   LL_AHB3_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB3_GRP1_PERIPH_JPGDEC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DTCM2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ITCM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AXISRAM
  * @retval None
*/
__STATIC_INLINE void LL_AHB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB1 AHB1
  * @{
  */

/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll AHB1ENR      DMA1EN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      DMA2EN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ADC12EN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ARTEN         LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ETH1MACEN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ETH1TXEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ETH1RXEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      USB1OTGHSEN   LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      USB1OTGHSULPIEN  LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      USB2OTGHSEN   LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      USB2OTGHSULPIEN  LL_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHSULPI
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHSULPI
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
  * @rmtoll AHB1ENR      DMA1EN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      DMA2EN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ADC12EN       LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ARTEN         LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ETH1MACEN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ETH1TXEN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ETH1RXEN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      USB1OTGHSEN   LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      USB1OTGHSULPIEN  LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      USB2OTGHSEN   LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      USB2OTGHSULPIEN  LL_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHSULPI
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHSULPI
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1ENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHB1ENR      DMA1EN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      DMA2EN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ADC12EN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ARTEN         LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ETH1MACEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ETH1TXEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ETH1RXEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      USB1OTGHSEN   LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      USB1OTGHSULPIEN  LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      USB2OTGHSEN   LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      USB2OTGHSULPIEN  LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHSULPI
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHSULPI
  * @retval None
*/
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll AHB1RSTR     DMA1RST       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     DMA2RST       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     ADC12RST      LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     ARTRST        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     ETH1MACRST    LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     USB1OTGHSRST  LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     USB2OTGHSRST  LL_AHB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHS
  * @retval None
*/
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll AHB1RSTR     DMA1RST       LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     DMA2RST       LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     ADC12RST      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     ARTRST        LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     ETH1MACRST    LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     USB1OTGHSRST  LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     USB2OTGHSRST  LL_AHB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHS
  * @retval None
*/
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Enable AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB1LPENR    DMA1LPEN      LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    DMA2LPEN      LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ADC12LPEN     LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ARTLPEN       LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ETH1MACLPEN   LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ETH1TXLPEN    LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ETH1RXLPEN    LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    USB1OTGHSLPEN  LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    USB1OTGHSULPILPEN  LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    USB2OTGHSLPEN  LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    USB2OTGHSULPILPEN  LL_AHB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHSULPI
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHSULPI
  * @retval None
*/
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB1LPENR    DMA1LPEN      LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    DMA2LPEN      LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ADC12LPEN     LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ARTLPEN       LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ETH1MACLPEN   LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ETH1TXLPEN    LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ETH1RXLPEN    LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    USB1OTGHSLPEN  LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    USB1OTGHSULPILPEN  LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    USB2OTGHSLPEN  LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    USB2OTGHSULPILPEN  LL_AHB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB1OTGHSULPI
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USB2OTGHSULPI
  * @retval None
*/
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2 AHB2
  * @{
  */

/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      DCMIEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      CRYPEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      HASHEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      RNGEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      SDMMC2EN      LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      D2SRAM1EN     LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      D2SRAM2EN     LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      D2SRAM3EN     LL_AHB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM3
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
  * @rmtoll AHB2ENR      DCMIEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      CRYPEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      HASHEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      RNGEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      SDMMC2EN      LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      D2SRAM1EN     LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      D2SRAM2EN     LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      D2SRAM3EN     LL_AHB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM3
  *
  *         (*) value not defined in all devices.
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      DCMIEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      CRYPEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      HASHEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      RNGEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      SDMMC2EN      LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      D2SRAM1EN     LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      D2SRAM2EN     LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      D2SRAM3EN     LL_AHB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM3
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
  * @rmtoll AHB2RSTR     DCMIRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     CRYPRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     HASHRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     RNGRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     SDMMC2RST     LL_AHB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
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
  * @rmtoll AHB2RSTR     DCMIRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     CRYPRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     HASHRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     RNGRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     SDMMC2RST     LL_AHB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR, Periphs);
}

/**
  * @brief  Enable AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB2LPENR    DCMILPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    CRYPLPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    HASHLPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    RNGLPEN       LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    SDMMC2LPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    D2SRAM1LPEN   LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    D2SRAM2LPEN   LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    D2SRAM3LPEN   LL_AHB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM3
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB2LPENR    DCMILPEN      LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    CRYPLPEN      LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    HASHLPEN      LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    RNGLPEN       LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    SDMMC2LPEN    LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    D2SRAM1LPEN   LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    D2SRAM2LPEN   LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    D2SRAM3LPEN   LL_AHB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_D2SRAM3
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB4 AHB4
  * @{
  */

/**
  * @brief  Enable AHB4 peripherals clock.
  * @rmtoll AHB4ENR      GPIOAEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOBEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOCEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIODEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOEEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOFEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOGEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOHEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOIEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOJEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOKEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      CRCEN         LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      BDMAEN        LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      ADC3EN        LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      HSEMEN        LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      BKPRAMEN      LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      D3SRAM1EN     LL_AHB4_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOJ
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOK
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BDMA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC3
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HSEM (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_D3SRAM1
  *
  *         (*) value not defined in all devices.
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
  * @rmtoll AHB4ENR      GPIOAEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOBEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOCEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIODEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOEEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOFEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOGEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOHEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOIEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOJEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOKEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      CRCEN         LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      BDMAEN        LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      ADC3EN        LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      HSEMEN        LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      BKPRAMEN      LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      D3SRAM1EN     LL_AHB4_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOJ
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOK
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BDMA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC3
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HSEM (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_D3SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_AHB4_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB4ENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable AHB4 peripherals clock.
  * @rmtoll AHB4ENR      GPIOAEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOBEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOCEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIODEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOEEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOFEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOGEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOHEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOIEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOJEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOKEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      CRCEN         LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      BDMAEN        LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      ADC3EN        LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      HSEMEN        LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      BKPRAMEN      LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      D3SRAM1EN     LL_AHB4_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOJ
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOK
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BDMA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC3
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HSEM (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_D3SRAM1
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB4_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4ENR, Periphs);
}

/**
  * @brief  Force AHB4 peripherals reset.
  * @rmtoll AHB4RSTR     GPIOARST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOBRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOCRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIODRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOERST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOFRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOGRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOHRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOIRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOJRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOKRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     CRCRST        LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     BDMARST       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     ADC3RST       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     HSEMRST       LL_AHB4_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOJ
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOK
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BDMA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC3
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HSEM (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB4_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB4RSTR, Periphs);
}

/**
  * @brief  Release AHB4 peripherals reset.
  * @rmtoll AHB4RSTR     GPIOARST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOBRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOCRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIODRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOERST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOFRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOGRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOHRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOIRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOJRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOKRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     CRCRST        LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     BDMARST       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     ADC3RST       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     HSEMRST       LL_AHB4_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOJ
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOK
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BDMA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC3
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HSEM (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
*/
__STATIC_INLINE void LL_AHB4_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4RSTR, Periphs);
}

/**
  * @brief  Enable AHB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB4LPENR    GPIOALPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOBLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOCLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIODLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOELPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOFLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOGLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOHLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOILPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOJLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOKLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    CRCLPEN       LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    BDMALPEN      LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    ADC3LPEN      LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    BKPRAMLPEN    LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    D3SRAM1LPEN   LL_AHB4_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOJ
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOK
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BDMA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC3
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_D3SRAM1
  * @retval None
*/
__STATIC_INLINE void LL_AHB4_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB4LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB4LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB4LPENR    GPIOALPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOBLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOCLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIODLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOELPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOFLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOGLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOHLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOILPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOJLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOKLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    CRCLPEN       LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    BDMALPEN      LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    ADC3LPEN      LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    BKPRAMLPEN    LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    D3SRAM1LPEN   LL_AHB4_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOJ
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOK
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BDMA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ADC3
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_D3SRAM1
  * @retval None
*/
__STATIC_INLINE void LL_AHB4_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3 APB3
  * @{
  */

/**
  * @brief  Enable APB3 peripherals clock.
  * @rmtoll APB3ENR      LTDCEN        LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      WWDG1EN       LL_APB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LTDC
  *         @arg @ref LL_APB3_GRP1_PERIPH_WWDG1
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
  * @rmtoll APB3ENR      LTDCEN        LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      WWDG1EN       LL_APB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LTDC
  *         @arg @ref LL_APB3_GRP1_PERIPH_WWDG1
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3ENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable APB3 peripherals clock.
  * @rmtoll APB3ENR      LTDCEN        LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      WWDG1EN       LL_APB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LTDC
  *         @arg @ref LL_APB3_GRP1_PERIPH_WWDG1
  * @retval None
*/
__STATIC_INLINE void LL_APB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3ENR, Periphs);
}

/**
  * @brief  Force APB3 peripherals reset.
  * @rmtoll APB3RSTR     LTDCRST       LL_APB3_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LTDC
  * @retval None
*/
__STATIC_INLINE void LL_APB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Release APB3 peripherals reset.
  * @rmtoll APB3RSTR     LTDCRST       LL_APB3_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LTDC
  * @retval None
*/
__STATIC_INLINE void LL_APB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Enable APB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB3LPENR    LTDCLPEN      LL_APB3_GRP1_EnableClockSleep\n
  *         APB3LPENR    WWDG1LPEN     LL_APB3_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LTDC
  *         @arg @ref LL_APB3_GRP1_PERIPH_WWDG1
  * @retval None
*/
__STATIC_INLINE void LL_APB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB3LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB3LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB3LPENR    LTDCLPEN      LL_APB3_GRP1_DisableClockSleep\n
  *         APB3LPENR    WWDG1LPEN     LL_APB3_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LTDC
  *         @arg @ref LL_APB3_GRP1_PERIPH_WWDG1
  * @retval None
*/
__STATIC_INLINE void LL_APB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1LENR     TIM2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM4EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM5EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM6EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM7EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM12EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM13EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     TIM14EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     LPTIM1EN      LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     WWDG2EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     SPI2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     SPI3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     SPDIFRXEN     LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     USART2EN      LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     USART3EN      LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     UART4EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     UART5EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     I2C1EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     I2C2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     I2C3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     CECEN         LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     DAC12EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     UART7EN       LL_APB1_GRP1_EnableClock\n
  *         APB1LENR     UART8EN       LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC12
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1LENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1LENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1LENR     TIM2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM4EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM5EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM6EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM7EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM12EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM13EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     TIM14EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     LPTIM1EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     WWDG2EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     SPI2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     SPI3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     SPDIFRXEN     LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     USART2EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     USART3EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     UART4EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     UART5EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     I2C1EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     I2C2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     I2C3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     CECEN         LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     DAC12EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     UART7EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1LENR     UART8EN       LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC12
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1LENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1LENR     TIM2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM4EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM5EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM6EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM7EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM12EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM13EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     TIM14EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     LPTIM1EN      LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     WWDG2EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     SPI2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     SPI3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     SPDIFRXEN     LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     USART2EN      LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     USART3EN      LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     UART4EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     UART5EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     I2C1EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     I2C2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     I2C3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     CECEN         LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     DAC12EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     UART7EN       LL_APB1_GRP1_DisableClock\n
  *         APB1LENR     UART8EN       LL_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC12
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1LENR, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1LRSTR    TIM2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM4RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM5RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM6RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM7RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM12RST      LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM13RST      LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    TIM14RST      LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    LPTIM1RST     LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    SPI2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    SPI3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    SPDIFRXRST    LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    USART2RST     LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    USART3RST     LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    UART4RST      LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    UART5RST      LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    I2C1RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    I2C2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    I2C3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    CECRST        LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    DAC12RST      LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    UART7RST      LL_APB1_GRP1_ForceReset\n
  *         APB1LRSTR    UART8RST      LL_APB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC12
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1LRSTR, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1LRSTR    TIM2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM4RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM5RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM6RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM7RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM12RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM13RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    TIM14RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    LPTIM1RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    SPI2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    SPI3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    SPDIFRXRST    LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    USART2RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    USART3RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    UART4RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    UART5RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    I2C1RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    I2C2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    I2C3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    CECRST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    DAC12RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    UART7RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1LRSTR    UART8RST      LL_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC12
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1LRSTR, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1LLPENR   TIM2LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM3LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM4LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM5LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM6LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM7LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM12LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM13LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   TIM14LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   LPTIM1LPEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   WWDG2LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   SPI2LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   SPI3LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   SPDIFRXLPEN   LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   USART2LPEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   USART3LPEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   UART4LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   UART5LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   I2C1LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   I2C2LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   I2C3LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   CECLPEN       LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   DAC12LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   UART7LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LLPENR   UART8LPEN     LL_APB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC12
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1LLPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1LLPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1LLPENR   TIM2LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM3LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM4LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM5LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM6LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM7LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM12LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM13LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   TIM14LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   LPTIM1LPEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   WWDG2LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   SPI2LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   SPI3LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   SPDIFRXLPEN   LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   USART2LPEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   USART3LPEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   UART4LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   UART5LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   I2C1LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   I2C2LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   I2C3LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   CECLPEN       LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   DAC12LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   UART7LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LLPENR   UART8LPEN     LL_APB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC12
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1LLPENR, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1HENR     CRSEN         LL_APB1_GRP2_EnableClock\n
  *         APB1HENR     SWPMIEN       LL_APB1_GRP2_EnableClock\n
  *         APB1HENR     OPAMPEN       LL_APB1_GRP2_EnableClock\n
  *         APB1HENR     MDIOSEN       LL_APB1_GRP2_EnableClock\n
  *         APB1HENR     FDCANEN       LL_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_SWPMI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1HENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1HENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1HENR     CRSEN         LL_APB1_GRP2_IsEnabledClock\n
  *         APB1HENR     SWPMIEN       LL_APB1_GRP2_IsEnabledClock\n
  *         APB1HENR     OPAMPEN       LL_APB1_GRP2_IsEnabledClock\n
  *         APB1HENR     MDIOSEN       LL_APB1_GRP2_IsEnabledClock\n
  *         APB1HENR     FDCANEN       LL_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_SWPMI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1HENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1HENR     CRSEN         LL_APB1_GRP2_DisableClock\n
  *         APB1HENR     SWPMIEN       LL_APB1_GRP2_DisableClock\n
  *         APB1HENR     OPAMPEN       LL_APB1_GRP2_DisableClock\n
  *         APB1HENR     MDIOSEN       LL_APB1_GRP2_DisableClock\n
  *         APB1HENR     FDCANEN       LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_SWPMI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1HENR, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1HRSTR    CRSRST        LL_APB1_GRP2_ForceReset\n
  *         APB1HRSTR    SWPMIRST      LL_APB1_GRP2_ForceReset\n
  *         APB1HRSTR    OPAMPRST      LL_APB1_GRP2_ForceReset\n
  *         APB1HRSTR    MDIOSRST      LL_APB1_GRP2_ForceReset\n
  *         APB1HRSTR    FDCANRST      LL_APB1_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_SWPMI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1HRSTR, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1HRSTR    CRSRST        LL_APB1_GRP2_ReleaseReset\n
  *         APB1HRSTR    SWPMIRST      LL_APB1_GRP2_ReleaseReset\n
  *         APB1HRSTR    OPAMPRST      LL_APB1_GRP2_ReleaseReset\n
  *         APB1HRSTR    MDIOSRST      LL_APB1_GRP2_ReleaseReset\n
  *         APB1HRSTR    FDCANRST      LL_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_SWPMI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1HRSTR, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1HLPENR   CRSLPEN       LL_APB1_GRP2_EnableClockSleep\n
  *         APB1HLPENR   SWPMILPEN     LL_APB1_GRP2_EnableClockSleep\n
  *         APB1HLPENR   OPAMPLPEN     LL_APB1_GRP2_EnableClockSleep\n
  *         APB1HLPENR   MDIOSLPEN     LL_APB1_GRP2_EnableClockSleep\n
  *         APB1HLPENR   FDCANLPEN     LL_APB1_GRP2_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_SWPMI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP2_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1HLPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1HLPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1HLPENR   CRSLPEN       LL_APB1_GRP2_DisableClockSleep\n
  *         APB1HLPENR   SWPMILPEN     LL_APB1_GRP2_DisableClockSleep\n
  *         APB1HLPENR   OPAMPLPEN     LL_APB1_GRP2_DisableClockSleep\n
  *         APB1HLPENR   MDIOSLPEN     LL_APB1_GRP2_DisableClockSleep\n
  *         APB1HLPENR   FDCANLPEN     LL_APB1_GRP2_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_SWPMI1
  *         @arg @ref LL_APB1_GRP2_PERIPH_OPAMP
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  * @retval None
*/
__STATIC_INLINE void LL_APB1_GRP2_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1HLPENR, Periphs);
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
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      USART6EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI4EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI5EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI3EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      DFSDM1EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      HRTIMEN       LL_APB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI3
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM
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
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      USART6EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI4EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI5EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI3EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      DFSDM1EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      HRTIMEN       LL_APB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI3
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2ENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      USART6EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI4EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI5EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI3EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      DFSDM1EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      HRTIMEN       LL_APB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI3
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM
  * @retval None
*/
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll APB2RSTR     TIM1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM8RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     USART1RST     LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     USART6RST     LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SPI1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SPI4RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM15RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM16RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM17RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SPI5RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SAI1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SAI2RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SAI3RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     DFSDM1RST     LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     HRTIMRST      LL_APB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI3
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM
  * @retval None
*/
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll APB2RSTR     TIM1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM8RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     USART1RST     LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     USART6RST     LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SPI1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SPI4RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM15RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM16RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM17RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SPI5RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SAI1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SAI2RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SAI3RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     DFSDM1RST     LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     HRTIMRST      LL_APB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI3
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM
  * @retval None
*/
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Enable APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB2LPENR    TIM1LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM8LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    USART1LPEN    LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    USART6LPEN    LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SPI1LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SPI4LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM15LPEN     LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM16LPEN     LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM17LPEN     LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SPI5LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SAI1LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SAI2LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SAI3LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    DFSDM1LPEN    LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    HRTIMLPEN     LL_APB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI3
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM
  * @retval None
*/
__STATIC_INLINE void LL_APB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB2LPENR    TIM1LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM8LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    USART1LPEN    LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    USART6LPEN    LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SPI1LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SPI4LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM15LPEN     LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM16LPEN     LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM17LPEN     LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SPI5LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SAI1LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SAI2LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SAI3LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    DFSDM1LPEN    LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    HRTIMLPEN     LL_APB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI3
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM
  * @retval None
*/
__STATIC_INLINE void LL_APB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB4 APB4
  * @{
  */

/**
  * @brief  Enable APB4 peripherals clock.
  * @rmtoll APB4ENR      SYSCFGEN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPUART1EN     LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      SPI6EN        LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      I2C4EN        LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM2EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM3EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM4EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM5EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      COMP12EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      VREFEN        LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      RTCAPBEN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      SAI4EN        LL_APB4_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_SAI4
  * @retval None
*/
__STATIC_INLINE void LL_APB4_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB4ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB4ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB4 peripheral clock is enabled or not
  * @rmtoll APB4ENR      SYSCFGEN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPUART1EN     LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      SPI6EN        LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      I2C4EN        LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM2EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM3EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM4EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM5EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      COMP12EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      VREFEN        LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      RTCAPBEN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      SAI4EN        LL_APB4_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_SAI4
  * @retval uint32_t
*/
__STATIC_INLINE uint32_t LL_APB4_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB4ENR, Periphs) == Periphs)?1U:0U);
}

/**
  * @brief  Disable APB4 peripherals clock.
  * @rmtoll APB4ENR      SYSCFGEN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPUART1EN     LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      SPI6EN        LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      I2C4EN        LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM2EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM3EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM4EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM5EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      COMP12EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      VREFEN        LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      RTCAPBEN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      SAI4EN        LL_APB4_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_SAI4
  * @retval None
*/
__STATIC_INLINE void LL_APB4_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB4ENR, Periphs);
}

/**
  * @brief  Force APB4 peripherals reset.
  * @rmtoll APB4RSTR     SYSCFGRST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPUART1RST    LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     SPI6RST       LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     I2C4RST       LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM2RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM3RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM4RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM5RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     COMP12RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     VREFRST       LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     SAI4RST       LL_APB4_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_SAI4
  * @retval None
*/
__STATIC_INLINE void LL_APB4_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB4RSTR, Periphs);
}

/**
  * @brief  Release APB4 peripherals reset.
  * @rmtoll APB4RSTR     SYSCFGRST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPUART1RST    LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     SPI6RST       LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     I2C4RST       LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM2RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM3RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM4RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM5RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     COMP12RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     VREFRST       LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     SAI4RST       LL_APB4_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_SAI4
  * @retval None
*/
__STATIC_INLINE void LL_APB4_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB4RSTR, Periphs);
}

/**
  * @brief  Enable APB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB4LPENR    SYSCFGLPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPUART1LPEN   LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    SPI6LPEN      LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    I2C4LPEN      LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM2LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM3LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM4LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM5LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    COMP12LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    VREFLPEN      LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    RTCAPBLPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    SAI4LPEN      LL_APB4_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_SAI4
  * @retval None
*/
__STATIC_INLINE void LL_APB4_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB4LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB4LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB4LPENR    SYSCFGLPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPUART1LPEN   LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    SPI6LPEN      LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    I2C4LPEN      LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM2LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM3LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM4LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM5LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    COMP12LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    VREFLPEN      LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    RTCAPBLPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    SAI4LPEN      LL_APB4_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_SAI4
  * @retval None
*/
__STATIC_INLINE void LL_APB4_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB4LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_CLKAM BUS_LL_EF_CLKAM
  * @{
  */

/**
  * @brief  Enable peripherals clock for CLKAM Mode.
  * @rmtoll D3AMR        BDMA          LL_CLKAM_Enable\n
  *         D3AMR        LPUART1       LL_CLKAM_Enable\n
  *         D3AMR        SPI6          LL_CLKAM_Enable\n
  *         D3AMR        I2C4          LL_CLKAM_Enable\n
  *         D3AMR        LPTIM2        LL_CLKAM_Enable\n
  *         D3AMR        LPTIM3        LL_CLKAM_Enable\n
  *         D3AMR        LPTIM4        LL_CLKAM_Enable\n
  *         D3AMR        LPTIM5        LL_CLKAM_Enable\n
  *         D3AMR        COMP12        LL_CLKAM_Enable\n
  *         D3AMR        VREF          LL_CLKAM_Enable\n
  *         D3AMR        RTC           LL_CLKAM_Enable\n
  *         D3AMR        CRC           LL_CLKAM_Enable\n
  *         D3AMR        SAI4          LL_CLKAM_Enable\n
  *         D3AMR        ADC3          LL_CLKAM_Enable\n
  *         D3AMR        BKPRAM        LL_CLKAM_Enable\n
  *         D3AMR        SRAM4         LL_CLKAM_Enable
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CLKAM_PERIPH_BDMA
  *         @arg @ref LL_CLKAM_PERIPH_LPUART1
  *         @arg @ref LL_CLKAM_PERIPH_SPI6
  *         @arg @ref LL_CLKAM_PERIPH_I2C4
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM2
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM3
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM4
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM5
  *         @arg @ref LL_CLKAM_PERIPH_COMP12
  *         @arg @ref LL_CLKAM_PERIPH_VREF
  *         @arg @ref LL_CLKAM_PERIPH_RTC
  *         @arg @ref LL_CLKAM_PERIPH_CRC
  *         @arg @ref LL_CLKAM_PERIPH_SAI4
  *         @arg @ref LL_CLKAM_PERIPH_ADC3
  *         @arg @ref LL_CLKAM_PERIPH_BKPRAM
  *         @arg @ref LL_CLKAM_PERIPH_SRAM4
  * @retval None
*/
__STATIC_INLINE void LL_CLKAM_Enable(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->D3AMR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->D3AMR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable peripherals clock for CLKAM Mode.
  * @rmtoll D3AMR        BDMA          LL_CLKAM_Disable\n
  *         D3AMR        LPUART1       LL_CLKAM_Disable\n
  *         D3AMR        SPI6          LL_CLKAM_Disable\n
  *         D3AMR        I2C4          LL_CLKAM_Disable\n
  *         D3AMR        LPTIM2        LL_CLKAM_Disable\n
  *         D3AMR        LPTIM3        LL_CLKAM_Disable\n
  *         D3AMR        LPTIM4        LL_CLKAM_Disable\n
  *         D3AMR        LPTIM5        LL_CLKAM_Disable\n
  *         D3AMR        COMP12        LL_CLKAM_Disable\n
  *         D3AMR        VREF          LL_CLKAM_Disable\n
  *         D3AMR        RTC           LL_CLKAM_Disable\n
  *         D3AMR        CRC           LL_CLKAM_Disable\n
  *         D3AMR        SAI4          LL_CLKAM_Disable\n
  *         D3AMR        ADC3          LL_CLKAM_Disable\n
  *         D3AMR        BKPRAM        LL_CLKAM_Disable\n
  *         D3AMR        SRAM4         LL_CLKAM_Disable
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CLKAM_PERIPH_BDMA
  *         @arg @ref LL_CLKAM_PERIPH_LPUART1
  *         @arg @ref LL_CLKAM_PERIPH_SPI6
  *         @arg @ref LL_CLKAM_PERIPH_I2C4
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM2
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM3
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM4
  *         @arg @ref LL_CLKAM_PERIPH_LPTIM5
  *         @arg @ref LL_CLKAM_PERIPH_COMP12
  *         @arg @ref LL_CLKAM_PERIPH_VREF
  *         @arg @ref LL_CLKAM_PERIPH_RTC
  *         @arg @ref LL_CLKAM_PERIPH_CRC
  *         @arg @ref LL_CLKAM_PERIPH_SAI4
  *         @arg @ref LL_CLKAM_PERIPH_ADC3
  *         @arg @ref LL_CLKAM_PERIPH_BKPRAM
  *         @arg @ref LL_CLKAM_PERIPH_SRAM4
  * @retval None
*/
__STATIC_INLINE void LL_CLKAM_Disable(uint32_t Periphs)
{
  CLEAR_BIT(RCC->D3AMR, Periphs);
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

#endif /* STM32H7xx_LL_BUS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
