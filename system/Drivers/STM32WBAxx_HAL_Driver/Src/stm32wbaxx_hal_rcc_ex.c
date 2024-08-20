/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_rcc_ex.c
  * @author  MCD Application Team
  * @brief   Extended RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities RCC extended peripheral:
  *           + Extended Peripheral Control functions
  *           + Extended Clock management functions
  *           + Extended Clock Recovery System Control functions
  *
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

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @defgroup RCCEx RCCEx
  * @brief RCC Extended HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  *  @brief  Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
                ##### Extended Peripheral Control functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks
    frequencies.
    [..]
    (@) Important note: Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to
        select the RTC clock source; in this case the Backup domain will be reset in
        order to modify the RTC Clock source, as consequence RTC registers (including
        the backup registers) are set to their reset values.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the RCC extended peripherals clocks according to the specified
  *         parameters in the RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1 USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2 USART2 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_I2C1 I2C1 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_LPTIM2 LPTIM2 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_SPI1 SPI1 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_SYSTICK SYSTICK peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIMIC TIMIC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1 SAI1 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_RNG RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_AUDIOSYNC AUDIOSYNC peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_LPUART1 LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3 SPI3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3 I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1 LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC ADC4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RTC RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RADIOST RADIO sleep timer clock (**)
  * @note   (*) Peripherals are not available on all devices
  * @note   (**) This requires the Backup domain access to be enabled
  * @note   Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select
  *         the RTC clock source: in this case the access to Backup domain is enabled.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef *PeriphClkInit)
{
  uint32_t tmpreg1;
  uint32_t tmpreg2;
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  /*-------------------------- USART1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART1CLKSOURCE(PeriphClkInit->Usart1ClockSelection));

    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(PeriphClkInit->Usart1ClockSelection);
  }

#if defined (USART2)
  /*-------------------------- USART2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(PeriphClkInit->Usart2ClockSelection));

    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(PeriphClkInit->Usart2ClockSelection);
  }
#endif


#if defined (I2C1)
  /*-------------------------- I2C1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));

    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }
#endif




#if defined (LPTIM2)
  /*-------------------------- LPTIM2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM2) == (RCC_PERIPHCLK_LPTIM2))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM2CLKSOURCE(PeriphClkInit->Lptim2ClockSelection));

    /* Configure the LPTIM2 clock source */
    __HAL_RCC_LPTIM2_CONFIG(PeriphClkInit->Lptim2ClockSelection);
  }
#endif

#if defined (SPI1)
  /*-------------------------- SPI1 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI1) == RCC_PERIPHCLK_SPI1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI1CLKSOURCE(PeriphClkInit->Spi1ClockSelection));

    /* Configure the SPI1 clock source */
    __HAL_RCC_SPI1_CONFIG(PeriphClkInit->Spi1ClockSelection);
  }
#endif

  /*-------------------------- SYSTICK clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SYSTICK) == RCC_PERIPHCLK_SYSTICK)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SYSTICKCLKSOURCE(PeriphClkInit->SystickClockSelection));

    /* Configure the SYSTICK clock source */
    __HAL_RCC_SYSTICK_CONFIG(PeriphClkInit->SystickClockSelection);
  }

  /*-------------------------- TIMIC clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIMIC) == RCC_PERIPHCLK_TIMIC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIMICCLKSOURCE(PeriphClkInit->TimIcClockSelection));

    /* Configure the TIMIC clock source */
    __HAL_RCC_TIMIC_CONFIG(PeriphClkInit->TimIcClockSelection);
  }

#if defined (SAI1)
  /*-------------------------- SAI1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI1) == RCC_PERIPHCLK_SAI1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SAI1CLKSOURCE(PeriphClkInit->Sai1ClockSelection));

    /* Set the source of SAI1 clock*/
    __HAL_RCC_SAI1_CONFIG(PeriphClkInit->Sai1ClockSelection);

    if (PeriphClkInit->Sai1ClockSelection == RCC_SAI1CLKSOURCE_PLL1P)
    {
      /* Enable PLL1 PCLK output */
      __HAL_RCC_PLL1CLKOUT_ENABLE(RCC_PLL1_PCLK);
    }
    else if (PeriphClkInit->Sai1ClockSelection == RCC_SAI1CLKSOURCE_PLL1Q)
    {
      /* Enable PLL1 QCLK output */
      __HAL_RCC_PLL1CLKOUT_ENABLE(RCC_PLL1_QCLK);
    }
    else
    {
      /* Do nothing ; for misra 15.7 error only */
    }
  }
#endif

  /*------------------------------ RNG Configuration -------------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RNG) == RCC_PERIPHCLK_RNG)
  {
    /* Check the parameters */
    assert_param(IS_RCC_RNGCLKSOURCE(PeriphClkInit->RngClockSelection));

    /* Set the source of RNG clock*/
    __HAL_RCC_RNG_CONFIG(PeriphClkInit->RngClockSelection);

    if (PeriphClkInit->RngClockSelection == RCC_RNGCLKSOURCE_PLL1Q)
    {
      /* Enable PLL1 QCLK output */
      __HAL_RCC_PLL1CLKOUT_ENABLE(RCC_PLL1_QCLK);
    }
  }


#if defined (RCC_CCIPR2_ASSEL)
  /*-------------------------- AS clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_AUDIOSYNC) == RCC_PERIPHCLK_AUDIOSYNC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ASCLKSOURCE(PeriphClkInit->AudioSyncClockSelection));

    /* Configure the AS clock source */
    __HAL_RCC_AUDIOSYNC_CONFIG(PeriphClkInit->AudioSyncClockSelection);

    if (PeriphClkInit->AudioSyncClockSelection == RCC_ASCLKSOURCE_PLL1P)
    {
      /* Enable PLL1 PCLK output */
      __HAL_RCC_PLL1CLKOUT_ENABLE(RCC_PLL1_PCLK);
    }
    else if (PeriphClkInit->AudioSyncClockSelection == RCC_ASCLKSOURCE_PLL1Q)
    {
      __HAL_RCC_PLL1CLKOUT_ENABLE(RCC_PLL1_QCLK);
    }
    else
    {
      /* Do nothing ; for misra 15.7 error only */
    }
  }
#endif

  /*-------------------------- LPUART1 clock source configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(PeriphClkInit->Lpuart1ClockSelection));

    /* Configure the LPUART1 clock source */
    __HAL_RCC_LPUART1_CONFIG(PeriphClkInit->Lpuart1ClockSelection);
  }

  /*-------------------------- SPI3 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI3) == RCC_PERIPHCLK_SPI3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI3CLKSOURCE(PeriphClkInit->Spi3ClockSelection));

    /* Configure the SPI3 clock source */
    __HAL_RCC_SPI3_CONFIG(PeriphClkInit->Spi3ClockSelection);
  }


  /*-------------------------- I2C3 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(PeriphClkInit->I2c3ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(PeriphClkInit->I2c3ClockSelection);
  }

  /*-------------------------- LPTIM1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == (RCC_PERIPHCLK_LPTIM1))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }

  /*-------------------------- ADC clock source configuration ----------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC) == RCC_PERIPHCLK_ADC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCCLKSOURCE(PeriphClkInit->AdcClockSelection));

    /* Configure the ADC4 interface clock source */
    __HAL_RCC_ADC_CONFIG(PeriphClkInit->AdcClockSelection);

    if (PeriphClkInit->AdcClockSelection == RCC_PERIPHCLK_ADC)
    {
      /* Enable PLL1 PCLK output */
      __HAL_RCC_PLL1CLKOUT_ENABLE(RCC_PLL1_PCLK);
    }
  }

  /*-------------------------- RTC clock source configuration ----------------------*/
  if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
  {
    FlagStatus       pwrclkchanged = RESET;

    /* Check for RTC Parameters used to output RTCCLK */
    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    /* Reset the Backup domain only if the RTC Clock source selection is modified from default */
    tmpreg2 = __HAL_RCC_GET_RTC_SOURCE();

    /* Check if RTC clock source needs to be changed */
    if (tmpreg2 != PeriphClkInit->RTCClockSelection)
    {
      /* Enable Power Clock */
      if (__HAL_RCC_PWR_IS_CLK_ENABLED() != 0x01u)
      {
        __HAL_RCC_PWR_CLK_ENABLE();
        pwrclkchanged = SET;
      }

      /* Enable write access to Backup domain */
      SET_BIT(PWR->DBPR, PWR_DBPR_DBP);

      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

      while (HAL_IS_BIT_CLR(PWR->DBPR, PWR_DBPR_DBP))
      {
        if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      /* Save BDCR1 content */
      tmpreg1 = (RCC->BDCR1 & ~RCC_BDCR1_RTCSEL);

      /* Check if a backup domain reset is required */
      if (tmpreg2 != RCC_RTCCLKSOURCE_DISABLE)
      {
#if defined(RCC_LSI2_SUPPORT)
        /* Save BDCR2 content */
        tmpreg2 = RCC->BDCR2;
#endif /* RCC_LSI2_SUPPORT */
        /* RTC Clock selection can be changed only if the Backup Domain is reset */
        __HAL_RCC_BACKUPRESET_FORCE();
        __HAL_RCC_BACKUPRESET_RELEASE();
#if defined(RCC_LSI2_SUPPORT)
        /* Restore previously saved BDCR2 */
        RCC->BDCR2 = tmpreg2;
#endif /* RCC_LSI2_SUPPORT */
      }

      /* Apply new RTC clock source selection */
      RCC->BDCR1 = (tmpreg1 | PeriphClkInit->RTCClockSelection);

      /* mask all ON bits */
      tmpreg2 = (RCC_BDCR1_LSEON | RCC_BDCR1_LSI1ON);
#if defined(RCC_LSI2_SUPPORT)
      tmpreg2 |= RCC_BDCR1_LSI2ON;
#endif

      /* Check which oscillators were enable */
      tmpreg2 &= tmpreg1;

      if (tmpreg2 != 0x00u)
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till all oscillators are enabled : RDY bit position is ON shifted by 1 */
        while (READ_BIT(RCC->BDCR1, (tmpreg2 << 1)) == 0x00u)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      /* Restore clock configuration if changed */
      if (pwrclkchanged == SET)
      {
        __HAL_RCC_PWR_CLK_DISABLE();
      }
    }
  }

  /*-------------------------- RADIO Sleep Timer clock source configuration --*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RADIOST) == RCC_PERIPHCLK_RADIOST)
  {
    /* Check the parameters */
    assert_param(IS_RCC_RADIOSLEEPTIMERSOURCE(PeriphClkInit->RadioSlpTimClockSelection));

    /* Configure the RADIO Sleep Timer clock source */
    __HAL_RCC_RADIOSLPTIM_CONFIG(PeriphClkInit->RadioSlpTimClockSelection);

    /* Check configuration validity as under Backup domain access control */
    if (__HAL_RCC_GET_RADIOSLPTIM_SOURCE() != PeriphClkInit->RadioSlpTimClockSelection)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}


/**
  * @brief  Get the peripheral kernel clock configuration.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for all existing peripheral kernel clocks. (*)
  * @note   (*) Peripherals are not available on all devices
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tmpreg;

  /* Check the parameters */
  assert_param(PeriphClkInit != NULL);

  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLOCK_ALL;

  /* Get CCIPR1 register value */
  tmpreg = RCC->CCIPR1;

  /* Get the USART1 clock source ---------------------------------------------*/
  PeriphClkInit->Usart1ClockSelection = (tmpreg & RCC_CCIPR1_USART1SEL);

#if defined (USART2)
  /* Get the USART2 clock source ---------------------------------------------*/
  PeriphClkInit->Usart2ClockSelection = (tmpreg & RCC_CCIPR1_USART2SEL);
#endif





#if defined (I2C1)
  /* Get the I2C1 clock source -----------------------------------------------*/
  PeriphClkInit->I2c1ClockSelection = (tmpreg & RCC_CCIPR1_I2C1SEL);
#endif

#if defined (LPTIM2)
  /* Get the LPTIM2 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim2ClockSelection = (tmpreg & RCC_CCIPR1_LPTIM2SEL);
#endif

#if defined (SPI1)
  /* Get the SPI1 clock source -----------------------------------------------*/
  PeriphClkInit->Spi1ClockSelection = (tmpreg & RCC_CCIPR1_SPI1SEL);
#endif

  /* Get the SYSTICK clock source --------------------------------------------*/
  PeriphClkInit->SystickClockSelection = (tmpreg & RCC_CCIPR1_SYSTICKSEL);

  /* Get the TIMIC clock source ----------------------------------------------*/
  PeriphClkInit->TimIcClockSelection = (tmpreg & RCC_CCIPR1_TIMICSEL);

  /* Get CCIPR2 register value */
  tmpreg = RCC->CCIPR2;

#if defined (SAI1)
  /* Get the SAI1 clock source -----------------------------------------------*/
  PeriphClkInit->Sai1ClockSelection = (tmpreg & RCC_CCIPR2_SAI1SEL);
#endif

  /* Get the RNG clock source ------------------------------------------------*/
  PeriphClkInit->RngClockSelection = (tmpreg & RCC_CCIPR2_RNGSEL);


#if defined (RCC_CCIPR2_ASSEL)
  /* Get the Audio sync clock source -----------------------------------------*/
  PeriphClkInit->AudioSyncClockSelection = (tmpreg & RCC_CCIPR2_ASSEL);
#endif

  /* Get CCIPR3 register value */
  tmpreg = RCC->CCIPR3;

  /* Get the LPUART1 clock source --------------------------------------------*/
  PeriphClkInit->Lpuart1ClockSelection = (tmpreg & RCC_CCIPR3_LPUART1SEL);

  /* Get the SPI3 clock source -----------------------------------------------*/
  PeriphClkInit->Spi3ClockSelection = (tmpreg & RCC_CCIPR3_SPI3SEL);

  /* Get the I2C3 clock source -----------------------------------------------*/
  PeriphClkInit->I2c3ClockSelection = (tmpreg & RCC_CCIPR3_I2C3SEL);

  /* Get the LPTIM1 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim1ClockSelection = (tmpreg & RCC_CCIPR3_LPTIM1SEL);

  /* Get the ADC clock source ------------------------------------------------*/
  PeriphClkInit->AdcClockSelection = (tmpreg & RCC_CCIPR3_ADCSEL);

  /* Get BDCR1 register value */
  tmpreg = RCC->BDCR1;

  /* Get the RTC clock source ------------------------------------------------*/
  PeriphClkInit->RTCClockSelection = (tmpreg & RCC_BDCR1_RTCSEL);

  /* Get the Radio Sleep Timer clock source ----------------------------------*/
  PeriphClkInit->RadioSlpTimClockSelection = (tmpreg & RCC_BDCR1_RADIOSTSEL);
}


/**
  * @brief  Return the peripheral clock frequency for peripherals
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1 USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2 USART2 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_I2C1 I2C1 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_LPTIM2 LPTIM2 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_SPI1 SPI1 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_SYSTICK SYSTICK peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIMIC TIMIC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1 SAI1 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_RNG RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_AUDIOSYNC AUDIOSYNC peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_LPUART1 LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3 SPI3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3 I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1 LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC ADC4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RTC RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RADIOST RADIO sleep timer clock
  * @note   (*) Peripherals are not available on all devices
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t frequency = 0;
  uint32_t srcclk;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_USART1:
      /* Get the current USART1 source */
      srcclk = __HAL_RCC_GET_USART1_SOURCE();

      if (srcclk == RCC_USART1CLKSOURCE_PCLK2)
      {
        frequency = HAL_RCC_GetPCLK2Freq();
      }
      else if (srcclk == RCC_USART1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_USART1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;

#if defined (USART2)
    case RCC_PERIPHCLK_USART2:
      /* Get the current USART2 source */
      srcclk = __HAL_RCC_GET_USART2_SOURCE();

      if (srcclk == RCC_USART2CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if (srcclk == RCC_USART2CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_USART2CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;
#endif


#if defined(I2C1)
    case RCC_PERIPHCLK_I2C1:
      /* Get the current I2C1 source */
      srcclk = __HAL_RCC_GET_I2C1_SOURCE();

      if (srcclk == RCC_I2C1CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if (srcclk == RCC_I2C1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_I2C1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;
#endif




#if defined(LPTIM2)
    case RCC_PERIPHCLK_LPTIM2:
      /* Get the current LPTIM2 source */
      srcclk = __HAL_RCC_GET_LPTIM2_SOURCE();

      if (srcclk == RCC_LPTIM2CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      /* Check if LSI1 or LIS2 is ready and if LPTIM2 clock selection is LSI */
      else if (srcclk == RCC_LPTIM2CLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1RDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV))
          {
            frequency /= 128U;
          }
        }
#if defined(RCC_LSI2_SUPPORT)
        else if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI2RDY))
        {
          frequency = LSI2_VALUE;
        }
        else
        {
          /* Do nothing ; for misra 15.7 error only */
        }
#endif
      }
      else if (srcclk == RCC_LPTIM2CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;
#endif

#if defined(SPI1)
    case RCC_PERIPHCLK_SPI1:
      /* Get the current SPI1 kernel source */
      srcclk = __HAL_RCC_GET_SPI1_SOURCE();

      if (srcclk == RCC_SPI1CLKSOURCE_PCLK2)
      {
        frequency = HAL_RCC_GetPCLK2Freq();
      }
      else if (srcclk == RCC_SPI1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_SPI1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;
#endif

    case RCC_PERIPHCLK_SYSTICK:
      /* Get the current SYSTICK kernel source */
      srcclk = __HAL_RCC_GET_SYSTICK_SOURCE();

      if (srcclk == RCC_SYSTICKCLKSOURCE_HCLK_DIV8)
      {
        frequency = (HAL_RCC_GetHCLKFreq() / 8U);
      }
      else if (srcclk == RCC_SYSTICKCLKSOURCE_LSE)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      else if (srcclk == RCC_SYSTICKCLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1RDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV))
          {
            frequency /= 128U;
          }
        }
#if defined(RCC_LSI2_SUPPORT)
        else if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI2RDY))
        {
          frequency = LSI2_VALUE;
        }
        else
        {
          /* Do nothing ; for misra 15.7 error only */
        }
#endif
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    case RCC_PERIPHCLK_TIMIC:
      /* Get the current TIMIC source */
      srcclk = __HAL_RCC_GET_TIMIC_SOURCE();

      if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
      {
        frequency = HSI_VALUE;
        if (srcclk == RCC_TIMICCLKSOURCE_HSI_DIV256)
        {
          frequency /= 256U;
        }
      }
      break;

#if defined (SAI1)
    case RCC_PERIPHCLK_SAI1:
      /* Get the current SAI1 source */
      srcclk = __HAL_RCC_GET_SAI1_SOURCE();

      if (srcclk == RCC_SAI1CLKSOURCE_PLL1P)
      {
        frequency = HAL_RCC_GetPLL1PFreq();
      }
      else if (srcclk == RCC_SAI1CLKSOURCE_PLL1Q)
      {
        frequency = HAL_RCC_GetPLL1QFreq();
      }
      else if (srcclk == RCC_SAI1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_SAI1CLKSOURCE_PIN)
      {
        frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      }
      else if (srcclk == RCC_SAI1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;
#endif

    case RCC_PERIPHCLK_RNG:
      /* Get the current RNG source */
      srcclk = __HAL_RCC_GET_RNG_SOURCE();

      if (srcclk == RCC_RNGCLKSOURCE_LSE)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      else if (srcclk == RCC_RNGCLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1RDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV))
          {
            frequency /= 128U;
          }
        }
#if defined(RCC_LSI2_SUPPORT)
        else if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI2RDY))
        {
          frequency = LSI2_VALUE;
        }
        else
        {
          /* Do nothing ; for misra 15.7 error only */
        }
#endif
      }
      else if (srcclk == RCC_RNGCLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        frequency = HAL_RCC_GetPLL1QFreq();
      }
      break;


#if defined (RCC_CCIPR2_ASSEL)
    case RCC_PERIPHCLK_AUDIOSYNC:
      /* Get the current Audio Sync source */
      srcclk = __HAL_RCC_GET_AUDIOSYNC_SOURCE();

      if (srcclk == RCC_ASCLKSOURCE_PLL1P)
      {
        frequency = HAL_RCC_GetPLL1PFreq();
      }
      else
      {
        frequency = HAL_RCC_GetPLL1QFreq();
      }
      break;
#endif

    case RCC_PERIPHCLK_LPUART1:
      /* Get the current LPUART1 source */
      srcclk = __HAL_RCC_GET_LPUART1_SOURCE();

      if (srcclk == RCC_LPUART1CLKSOURCE_PCLK7)
      {
        frequency = HAL_RCC_GetPCLK7Freq();
      }
      else if (srcclk == RCC_LPUART1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_LPUART1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_SPI3:
      /* Get the current SPI3 kernel source */
      srcclk = __HAL_RCC_GET_SPI3_SOURCE();

      if (srcclk == RCC_SPI3CLKSOURCE_PCLK7)
      {
        frequency = HAL_RCC_GetPCLK7Freq();
      }
      else if (srcclk == RCC_SPI3CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_SPI3CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    case RCC_PERIPHCLK_I2C3:
      /* Get the current I2C3 source */
      srcclk = __HAL_RCC_GET_I2C3_SOURCE();

      if (srcclk == RCC_I2C3CLKSOURCE_PCLK7)
      {
        frequency = HAL_RCC_GetPCLK7Freq();
      }
      else if (srcclk == RCC_I2C3CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_I2C3CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    case RCC_PERIPHCLK_LPTIM1:
      /* Get the current LPTIM1 source */
      srcclk = __HAL_RCC_GET_LPTIM1_SOURCE();

      if (srcclk == RCC_LPTIM1CLKSOURCE_PCLK7)
      {
        frequency = HAL_RCC_GetPCLK7Freq();
      }
      else if (srcclk == RCC_LPTIM1CLKSOURCE_LSI)
      {
        /* Check if LSI1 or LIS2 is ready */
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1RDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV))
          {
            frequency /= 128U;
          }
        }
#if defined(RCC_LSI2_SUPPORT)
        else if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI2RDY))
        {
          frequency = LSI2_VALUE;
        }
        else
        {
          /* Do nothing ; for misra 15.7 error only */
        }
#endif
      }
      else if (srcclk == RCC_LPTIM1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_ADC:
      /* Get the current ADC kernel source */
      srcclk = __HAL_RCC_GET_ADC_SOURCE();

      if (srcclk == RCC_ADCCLKSOURCE_HCLK)
      {
        frequency = HAL_RCC_GetHCLKFreq();
      }
      else if (srcclk == RCC_ADCCLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if (srcclk == RCC_ADCCLKSOURCE_PLL1P)
      {
        frequency = HAL_RCC_GetPLL1PFreq();
      }
      else if (srcclk == RCC_ADCCLKSOURCE_HSE)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = HSE_VALUE;
        }
      }
      else if (srcclk == RCC_ADCCLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    case RCC_PERIPHCLK_RTC:
      /* Get the current RTC source */
      srcclk = __HAL_RCC_GET_RTC_SOURCE();

      /* Check if LSE is ready and if RTC clock selection is LSE */
      if (srcclk == RCC_RTCCLKSOURCE_LSE)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      /* Check if LSI1 or LIS2 is ready and if RTC clock selection is LSI */
      else if (srcclk == RCC_RTCCLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1RDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV))
          {
            frequency /= 128U;
          }
        }
#if defined(RCC_LSI2_SUPPORT)
        else if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI2RDY))
        {
          frequency = LSI2_VALUE;
        }
        else
        {
          /* Do nothing ; for misra 15.7 error only */
        }
#endif /* RCC_LSI2_SUPPORT */
      }
      /* Check if HSE is ready  and if RTC clock selection is HSI_DIV32 */
      else
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = (HSE_VALUE / 32U);
        }
      }
      break;

    case RCC_PERIPHCLK_RADIOST:
      /* Get the current RADIOST kernel source */
      srcclk = __HAL_RCC_GET_RADIOSLPTIM_SOURCE();

      if (srcclk == RCC_RADIOSTCLKSOURCE_HSE_DIV1000)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = (HSE_VALUE / 1000U);
        }
      }
      else if (srcclk == RCC_RADIOSTCLKSOURCE_LSE)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      else if (srcclk == RCC_RADIOSTCLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1RDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI1PREDIV))
          {
            frequency /= 128U;
          }
        }
#if defined(RCC_LSI2_SUPPORT)
        else if (HAL_IS_BIT_SET(RCC->BDCR1, RCC_BDCR1_LSI2RDY))
        {
          frequency = LSI2_VALUE;
        }
        else
        {
          /* Do nothing ; for misra 15.7 error only */
        }
#endif
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    default:
      break;
  }

  return (frequency);
}

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  *  @brief  Extended Clock management functions
  *
@verbatim
 ===============================================================================
                ##### Extended clock management functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    activation or deactivation of LSE CSS, Low Speed Clock Output (LSCO), HSE and
    LSE trimming and LSI2 configuration (when applicable).
@endverbatim
  * @{
  */

/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled
  *         with HAL_RCC_OscConfig() and the LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCCEx_PeriphCLKConfig().
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS(void)
{
  SET_BIT(RCC->BDCR1, RCC_BDCR1_LSECSSON);
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  * @retval None
  */
void HAL_RCCEx_DisableLSECSS(void)
{
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSECSSON);
}

/**
  * @brief  Select the Low Speed clock source to output on LSCO pin (PA2).
  * @param  LSCOSource  specifies the Low Speed clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCOSOURCE_LSI  LSI clock selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSE  LSE clock selected as LSCO source
  * @retval None
  */
void HAL_RCCEx_EnableLSCO(uint32_t LSCOSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* Update LSCO selection according to parameter and enable LSCO */
  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSCOSEL, LSCOSource | RCC_BDCR1_LSCOEN);
}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{
  /* Clear LSCOEN in BDCR register */
  CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSCOEN);
}

/**
  * @brief  Set HSE trimming value
  * @param  Trimming  specifies the HSE trimming value.
  *          This parameter should be below 0x3F.
  * @retval None
  */
void HAL_RCCEx_HSESetTrimming(uint32_t Trimming)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSETRIM(Trimming));

  MODIFY_REG(RCC->ECSCR1, RCC_ECSCR1_HSETRIM, Trimming << RCC_ECSCR1_HSETRIM_Pos);
}

/**
  * @brief  Get HSE trimming value
  * @retval The programmed HSE trimming value
  */
uint32_t HAL_RCCEx_HSEGetTrimming(void)
{
  return ((RCC->ECSCR1 & RCC_ECSCR1_HSETRIM) >> RCC_ECSCR1_HSETRIM_Pos);
}

/**
  * @brief  Set LSE trimming value
  * @param  Trimming  specifies the Low Speed clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSETRIMMING_R  current source resistance R
  *            @arg @ref RCC_LSETRIMMING_3_4_R  current source resistance 3/4*R
  *            @arg @ref RCC_LSETRIMMING_2_3_R  current source resistance 2/3*R
  *            @arg @ref RCC_LSETRIMMING_1_2_R  current source resistance 1/2*R
  * @retval None
  */
void HAL_RCCEx_LSESetTrimming(uint32_t Trimming)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSETRIM(Trimming));

  MODIFY_REG(RCC->BDCR1, RCC_BDCR1_LSETRIM, Trimming);
}

/**
  * @brief  Get LSE trimming value
  * @retval The programmed LSE trimming value
  */
uint32_t HAL_RCCEx_LSEGetTrimming(void)
{
  return (RCC->BDCR1 & RCC_BDCR1_LSETRIM);
}

#if defined(RCC_LSI2_SUPPORT)
/**
  * @brief  Set LSI2 Configuration
  * @param  pConfig pointer to an RCC_LSIConfigTypeDef structure that
  *         contains the configuration information for the LSI2 oscillattor
  * @retval None
  */
void HAL_RCCEx_LSI2SetConfig(const RCC_LSIConfigTypeDef *pConfig)
{
  /* Check the parameters */
  assert_param(pConfig != NULL);
  assert_param(IS_RCC_LSI2_FREQTEMPSENS(pConfig->FreqTempSens));
  assert_param(IS_RCC_LSI2_OPERATINGMODE(pConfig->OpMode));

  WRITE_REG(RCC->BDCR2, (pConfig->FreqTempSens | pConfig->OpMode));
}

/**
  * @brief  Set LSI2 Configuration
  * @param  pConfig pointer to an RCC_LSIConfigTypeDef structure that
  *         contains the configuration information for the LSI2 oscillattor
  * @retval None
  */
void HAL_RCCEx_LSI2GetConfig(RCC_LSIConfigTypeDef *pConfig)
{
  uint32_t regbdcr2;

  /* Check the parameters */
  assert_param(pConfig != NULL);

  /* Get register value */
  regbdcr2 = RCC->BDCR2;

  pConfig->FreqTempSens = (regbdcr2 & RCC_BDCR2_LSI2CFG);
  pConfig->OpMode = (regbdcr2 & RCC_BDCR2_LSI2MODE);
}

#endif /* RCC_BDCR1_LSI2ON */

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group3
  *  @brief  Radio clock management functions
  *
@verbatim
 ===============================================================================
                ##### Extended radio clock management functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    radio-related parameters.
@endverbatim
  * @{
  */

/**
  * @brief  Enable the 2.4 GHz RADIO baseband clock
  * @retval None
  */
void HAL_RCCEx_EnableRadioBBClock(void)
{
  SET_BIT(RCC->RADIOENR, RCC_RADIOENR_BBCLKEN);
}

/**
  * @brief  Disable the 2.4 GHz RADIO baseband clock
  * @retval None
  */
void HAL_RCCEx_DisableRadioBBClock(void)
{
  CLEAR_BIT(RCC->RADIOENR, RCC_RADIOENR_BBCLKEN);
}

/**
  * @brief  Enable the 2.4 GHz RADIO bus clock and HSE32 oscillator by 2.4 GHz RADIO sleep timer wakeup event
  * @retval None
  */
void HAL_RCCEx_EnableRequestUponRadioWakeUpEvent(void)
{
  SET_BIT(RCC->RADIOENR, RCC_RADIOENR_STRADIOCLKON);
}

/**
  * @brief  Disable the 2.4 GHz RADIO bus clock and HSE32 oscillator by 2.4 GHz RADIO sleep timer wakeup event
  * @retval None
  */
void HAL_RCCEx_DisableRequestUponRadioWakeUpEvent(void)
{
  CLEAR_BIT(RCC->RADIOENR, RCC_RADIOENR_STRADIOCLKON);
}

/**
  * @brief Get the 2.4 GHz RADIO bus clock readiness.
  * @note  Indicate that the 2.4 GHz RADIO bus clock is ready and the 2.4 GHz RADIO registers can be accessed.
  * @note  The output can be one of the following values :
  *         @arg RCC_RADIO_BUS_CLOCK_NOT_READY  : 2.4 GHz RADIO bus clock not ready.
  *         @arg RCC_RADIO_BUS_CLOCK_READY :  2.4 GHz RADIO bus clock ready.
  * @retval The regulator REG_VDDHPA input supply selection.
  */
uint32_t HAL_RCCEx_GetRadioBusClockReadiness(void)
{
  return READ_BIT(RCC->RADIOENR, RCC_RADIOENR_RADIOCLKRDY);
}
/**
  * @}
  */

#if defined(RCC_CCIPR2_ASSEL)
/** @addtogroup RCCEx_Exported_Functions_Group4
  *  @brief  Radio clock management functions
  *
@verbatim
 ===============================================================================
                ##### Extended radio clock management functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    audio-synchronization-related parameters.
@endverbatim
  * @{
  */

/**
  * @brief  Enable the Audio Synchronization counter and kernel clock
  * @retval None
  */
void HAL_RCCEx_EnableAudioSyncClock(void)
{
  SET_BIT(RCC->ASCR, RCC_ASCR_CEN);
}

/**
  * @brief  Disable the Audio Synchronization counter and kernel clock
  * @retval None
  */
void HAL_RCCEx_DisableAudioSyncClock(void)
{
  CLEAR_BIT(RCC->ASCR, RCC_ASCR_CEN);
}

/**
  * @brief  Set Audio Synchronization Configuration
  * @param  pConf pointer to an RCC_AudioSyncConfigTypeDef structure that
  *         contains the configuration information for the Audio Synchronization
  * @retval None
  */
HAL_StatusTypeDef HAL_RCCEx_SetConfigAudioSync(const RCC_AudioSyncConfigTypeDef *pConf)
{
  /* Check the parameters */
  assert_param(pConf != (void *)NULL);
  assert_param(IS_RCC_AUDIOSYNC_CAPTUREPRESCALER(pConf->CapturePrescaler));
  assert_param(IS_RCC_AUDIOSYNC_CLOCKPRESCALER(pConf->ClockPrescaler));
  assert_param(IS_RCC_AUDIOSYNC_AUTORELOAD(pConf->AutoReloadValue));
  assert_param(IS_RCC_AUDIOSYNC_COMPARE(pConf->CompareValue));

  /* Set ASCR register value */
  RCC->ASCR = (((pConf->CapturePrescaler) << RCC_ASCR_CPS_Pos) & \
               ((pConf->ClockPrescaler) << RCC_ASCR_PSC_Pos));

  /* Set Auto Reload value */
  RCC->ASARR = ((pConf->AutoReloadValue) << RCC_ASARR_AR_Pos);

  /* Set Compare value */
  RCC->ASCOR = ((pConf->CompareValue) << RCC_ASCOR_CO_Pos);

  return HAL_OK;
}

/**
  * @brief  Configure the pConf according to the internal
  *         RCC configuration registers.
  * @param  pConf pointer to an RCC_AudioSyncConfigTypeDef
  *         structure that will be configured.
  * @retval None
  */
void HAL_RCCEx_GetConfigAudioSync(RCC_AudioSyncConfigTypeDef *pConf)
{
  uint32_t regvalue;

  /* Check the parameters */
  assert_param(pConf != (void *)NULL);

  /* Get Audio ASCR register */
  regvalue = RCC->ASCR;

  /* Get Capture prescaler value */
  pConf->CapturePrescaler = ((regvalue & RCC_ASCR_CPS) >> RCC_ASCR_CPS_Pos);

  /* Get Clock prescaler value */
  pConf->ClockPrescaler = ((regvalue & RCC_ASCR_PSC) >> RCC_ASCR_PSC_Pos);

  /* Get Auto Reload value */
  pConf->AutoReloadValue = ((RCC->ASARR & RCC_ASCAR_CA) >> RCC_ASCAR_CA_Pos);

  /* Get Compare value */
  pConf->CompareValue = ((RCC->ASCOR & RCC_ASCOR_CO) >> RCC_ASCOR_CO_Pos);
}

/**
  * @brief  Get AudioSync Counter value
  * @retval The Counter value
  */
uint32_t HAL_RCCEx_GetAudioSyncCounterValue(void)
{
  return ((RCC->ASCNTR & RCC_ASCNTR_CNT) >> RCC_ASCNTR_CNT_Pos);
}

/**
  * @brief  Get AudioSync Capture value
  * @retval The programmed Capture value
  */
uint32_t HAL_RCCEx_GetAudioSyncCaptureValue(void)
{
  return ((RCC->ASCAR & RCC_ASCAR_CA) >> RCC_ASCAR_CA_Pos);
}

/**
  * @}
  */
#endif /* RCC_CCIPR2_ASSEL */

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
