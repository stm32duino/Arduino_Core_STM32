/**
  ******************************************************************************
  * @file    stm32wl3x_hal_rcc_ex.c
  * @author  MCD Application Team
  * @brief   Extended RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities RCC extended peripheral:
  *           + Extended Peripheral Control functions
  *           + Extended Clock management functions
  *
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

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @defgroup RCCEx RCCEx
  * @brief RCC Extended HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup RCCEx_Private_Constants RCCEx Private Constants
  * @{
  */

#if defined(STM32WL3XX)
#define __LSCO1_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO1_GPIO_PORT        GPIOA
#define LSCO1_PIN              GPIO_PIN_4
#define LSCO1_GPIO_AF          GPIO_AF0_LCO
#endif

#define __LSCO2_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO2_GPIO_PORT        GPIOA
#define LSCO2_PIN              GPIO_PIN_10
#define LSCO2_GPIO_AF          GPIO_AF0_LCO


#if defined(STM32WL3XX)
#define __LSCO3_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define LSCO3_GPIO_PORT        GPIOB
#define LSCO3_PIN              GPIO_PIN_12
#define LSCO3_GPIO_AF          GPIO_AF2_LCO
#endif

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @defgroup RCCEx_Exported_Functions_Group1 Extended Peripheral Control functions
  *  @brief  Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
                ##### Extended Peripheral Control functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks
    frequencies.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the RCC extended peripherals clocks according to the specified
  *         parameters in the @ref RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit  pointer to a @ref RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *
  *            @arg @ref RCC_PERIPHCLK_RF        RF peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SMPS      SMPS peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3_I2S          SPI3 I2S peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1           LPUART1 peripheral clock
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));


  /*-------------------------- SMPS clock configuration -------------------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SMPS) == RCC_PERIPHCLK_SMPS))
  {
    assert_param(IS_RCC_SMPS_CLOCK_PRESC(PeriphClkInit->SmpsDivSelection));
    __HAL_RCC_SMPS_DIV_CONFIG(PeriphClkInit->SmpsDivSelection);
    __HAL_RCC_KRM_RATE_MULTIPLIER_CONFIG(PeriphClkInit->KRMRateMultiplier);
  }

  /*-------------------------- SPI3_I2S clock source configuration ---------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI3_I2S) == RCC_PERIPHCLK_SPI3_I2S))
  {
    assert_param(IS_RCC_SPI3I2S_CLOCK_SOURCE(PeriphClkInit->SPI3I2SClockSelection));
    __HAL_RCC_SPI3I2S_CLK_CONFIG(PeriphClkInit->SPI3I2SClockSelection);
  }
#if defined(RCC_CFGR_LPUCLKSEL)
  /*-------------------------- LPUART1 clock source configuration ---------------------*/
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1))
  {
    assert_param(IS_RCC_LPUART1_CLOCK_SOURCE(PeriphClkInit->LPUART1ClockSelection));
    __HAL_RCC_LPUART1_CLK_CONFIG(PeriphClkInit->LPUART1ClockSelection);
  }
#endif /* RCC_CFGR_LPUCLKSEL */

  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC_WDG_SUBG_LPAWUR_LCD_LCSC) ==
       RCC_PERIPHCLK_RTC_WDG_SUBG_LPAWUR_LCD_LCSC))
  {
    assert_param(IS_RCC_RTC_WDG_SUBG_PAWUR_LCD_LCSC_CLOCK_SOURCE(PeriphClkInit->RTCWDGSUBGLPAWURLCDLCSCClockSelection));
    __HAL_RCC_RTC_SUBG_LPAWUR_LCD_LCSC_CLK_CONFIG(PeriphClkInit->RTCWDGSUBGLPAWURLCDLCSCClockSelection);
  }

  return HAL_OK;
}


/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks(RF, SMPS, SPI3I2S).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLOCK_ALL;

  /* Get the SPI clock config --------------------------------------------------*/

  /* Get the SPI3 I2S clock source -------------------------------------------*/
  PeriphClkInit->SPI3I2SClockSelection = __HAL_RCC_GET_SPI3I2S_CLK_CONFIG();

  /* Get the RF clock config -------------------------------------------------*/
#if defined(RCC_CFGR_LPUCLKSEL)
  PeriphClkInit->LPUART1ClockSelection = __HAL_RCC_GET_LPUART1_CLK_CONFIG();
#endif /* RCC_CFGR_LPUCLKSEL */

  /* Get the SMPS clock divider ------------------------------------------------*/
  PeriphClkInit->SmpsDivSelection = __HAL_RCC_GET_SMPS_DIV();

  /* Get the KRM rate multiplier -----------------------------------------------*/
  PeriphClkInit->KRMRateMultiplier = __HAL_RCC_GET_KRM_RATE_MULTIPLIER();

  /* Get RTC, WDG and SUBG LPAWUR LCD LCSC clock */
  PeriphClkInit->RTCWDGSUBGLPAWURLCDLCSCClockSelection = __HAL_RCC_GET_RTC_SUBG_LPAWUR_LCD_LCSC_CLK_CONFIG();
}

/**
  * @brief  Return the peripheral clock frequency for peripherals with clock source
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_RF        RF   peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SMPS      SMPS peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3_I2S          SPI3 I2S peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1           LPUART1 peripheral clock
  * @retval Frequency in Hz
  * @note   (*) Peripherals are not available on all devices
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t frequency, spiFreqValue, krmValue;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

  /* No if clausule is covered */
  frequency = 0;

  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_RF :
      frequency = HSE_VALUE / 3;
      break;

    case RCC_PERIPHCLK_SMPS :
      if (__HAL_RCC_IS_KRM_ENABLED())
      {
        if (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_DIRECT_HSE)
        {
          frequency = HSE_VALUE;
        }
        else
        {
          frequency = RC64MPLL_VALUE;
        }
        krmValue = __HAL_RCC_GET_KRM_RATE_MULTIPLIER();
        if (krmValue < 8)
        {
          krmValue = 8;
        }
        frequency = frequency / krmValue;
      }
      else
      {
        switch (__HAL_RCC_GET_SMPS_DIV())
        {
          case RCC_SMPSCLK_DIV2:
            frequency = RC64MPLL_VALUE / 8;
            break;
          case RCC_SMPSCLK_DIV4:
            frequency = RC64MPLL_VALUE / 16;
            break;
        }
      }
      break;

    case RCC_PERIPHCLK_SPI3_I2S :
      spiFreqValue = __HAL_RCC_GET_SPI3I2S_CLK_CONFIG();
      switch (spiFreqValue)
      {
        case RCC_SPI3I2S_CLKSOURCE_CLK_ROOT_DIV :
          frequency = RC64MPLL_VALUE / 4;
          break;

        case RCC_SPI3I2S_CLKSOURCE_CLK_ROOT :
          if (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_DIRECT_HSE)
          {
            frequency = HSE_VALUE / 2;
          }
          else
          {
            frequency = RC64MPLL_VALUE / 2;
          }
          break;
        case RCC_SPI3I2S_CLKSOURCE_CLK_RC64MPLL :
          frequency = HAL_RCC_GetSysClockFreq() ;
          break;
      }
      break;
#if defined(RCC_CFGR_LPUCLKSEL)
    case RCC_PERIPHCLK_LPUART1 :
      switch (__HAL_RCC_GET_LPUART1_CLK_CONFIG())
      {
        case RCC_LPUART1_CLKSOURCE_LSE:
          frequency = LSE_VALUE;
          break;
        case RCC_LPUART1_CLKSOURCE_16M:
          frequency = 16000000U;
          break;
        default:
          frequency = HSE_VALUE / 2;
          break;
      }
      break;
#endif /* RCC_CFGR_LPUCLKSEL */
    default :
      break;
  }
  return (frequency);
}

/**
  * @}
  */

/** @defgroup RCCEx_Exported_Functions_Group2 Extended Clock management functions
  *  @brief  Extended Clock management functions
  *
@verbatim
 ===============================================================================
                ##### Extended clock management functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    activation or deactivation Low speed clock output.
@endverbatim
  * @{
  */

/**
  * @brief  Select the clock source to output on LSCO1 pin(PA4) or LSC02 pin (PA10) or LSCO3 pin (PB12).
  * @note   PA4, PA10 or PB12 should be configured in alternate function mode.
  * @param  RCC_LSCOx  specifies the output direction for the clock source.
  *            @arg @ref RCC_LSCO1  Clock source to output on LSCO1 pin(PA4)
  *            @arg @ref RCC_LSCO2  Clock source to output on LSCO2 pin(PA10)
  *            @arg @ref RCC_LSCO3  Clock source to output on LSCO3 pin(PB12)
  * @param  RCC_LSCOSource  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCOSOURCE_LSI       LSI clock selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSE       LSE clock selected as LSCO source
  * @retval None
  * @note   LSCO should be disable with @ref HAL_RCCEx_DisableLSCO
  */
void HAL_RCCEx_LSCOConfig(uint32_t RCC_LSCOx, uint32_t RCC_LSCOSource)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_LSCO(RCC_LSCOx));
  assert_param(IS_RCC_LSCOSOURCE(RCC_LSCOSource));

  /* Common GPIO init parameters */
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;

#if defined(LSCO1_PIN)
  if (RCC_LSCOx == RCC_LSCO1)
  {
    /* LSCO1 Clock Enable */
    __LSCO1_CLK_ENABLE();
    /* Configure the LSCO1 pin in alternate function mode */
    GPIO_InitStruct.Pin       = LSCO1_PIN;
    GPIO_InitStruct.Alternate = LSCO1_GPIO_AF;
    HAL_GPIO_Init(LSCO1_GPIO_PORT, &GPIO_InitStruct);
  }
#endif

  if (RCC_LSCOx == RCC_LSCO2)
  {
    /* LSCO2 Clock Enable */
    __LSCO2_CLK_ENABLE();
    /* Configure the LSCO2 pin in alternate function mode */
    GPIO_InitStruct.Pin       = LSCO2_PIN;
    GPIO_InitStruct.Alternate = LSCO2_GPIO_AF;
    HAL_GPIO_Init(LSCO2_GPIO_PORT, &GPIO_InitStruct);
  }

  if (RCC_LSCOx == RCC_LSCO3)
  {
    /* LSCO3 Clock Enable */
    __LSCO3_CLK_ENABLE();
    /* Configure the LSCO3 pin in alternate function mode */
    GPIO_InitStruct.Pin       = LSCO3_PIN;
    GPIO_InitStruct.Alternate = LSCO3_GPIO_AF;
    HAL_GPIO_Init(LSCO3_GPIO_PORT, &GPIO_InitStruct);
  }

  /* Configure the clock source to output */
  LL_RCC_ConfigLSCO(RCC_LSCOSource);
}


/**
  * @brief  Enable the Low Speed clock source to output on LSCO pin during STANDBY with retention.
  *         It is applicable only for LSCO2
  * @param  LSCOSource  specifies the Low Speed clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCOSOURCE_LSI_LPMU  Internal LPMU slow clock source selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSI       LSI clock selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSE       LSE clock selected as LSCO source
  * @retval None
  */
void HAL_RCCEx_EnableLSCOinDEEPSTOP(uint32_t LSCOSource)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* LSCO Pin Clock Enable */
  __LSCO2_CLK_ENABLE();

  /* Configure the LSCO pin in alternate function mode */
  GPIO_InitStruct.Pin   = LSCO2_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = LSCO2_GPIO_AF;
  HAL_GPIO_Init(LSCO2_GPIO_PORT, &GPIO_InitStruct);

  /* Enable the LSCO2 pin during STANDBY with retention */
#if defined(RCC_CFGR_LCOEN)
  LL_RCC_LSCOinDeepStop_Enable();
#endif
  /* Configure the clock source to output */
  LL_RCC_ConfigLSCO(LSCOSource);
}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{
#if defined(RCC_CFGR_LCOEN)
  LL_RCC_LSCOinDeepStop_Disable();
#endif
  LL_RCC_ConfigLSCO(LL_RCC_LSCOSOURCE_NOCLOCK);

}


/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_RCC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
