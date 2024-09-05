/**
  ******************************************************************************
  * @file    stm32u0xx_hal_rcc_ex.c
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
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal.h"

/** @addtogroup STM32U0xx_HAL_Driver
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
#define __LSCO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO_GPIO_PORT            GPIOA
#define LSCO_PIN                  GPIO_PIN_2

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCCEx_Private_Functions RCCEx Private Functions
  * @{
  */
static HAL_StatusTypeDef RCCEx_PLLSource_Enable(uint32_t PllSource);

/**
  * @}
  */

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
  *            @arg @ref RCC_PERIPHCLK_USART1  USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2  USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART2  LPUART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART3  LPUART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1  I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3  I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1  LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2  LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM3  LPTIM3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIM1  TIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIM15  TIM15 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USB  USB peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC  ADC peripheral clock
  *
  * @note   Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select
  *         the RTC clock source: in this case the access to Backup domain is enabled.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tmpregister;
  uint32_t tickstart;
  HAL_StatusTypeDef ret = HAL_OK;      /* Intermediate status */
  HAL_StatusTypeDef status = HAL_OK;   /* Final status */

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  /*-------------------------- RTC clock source configuration ----------------------*/
  if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
  {
    FlagStatus       pwrclkchanged = RESET;

    /* Check for RTC Parameters used to output RTCCLK */
    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    /* Enable Power Clock */
    if (__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }

    /* Enable write access to Backup domain */
    SET_BIT(PWR->CR1, PWR_CR1_DBP);

    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();

    while (READ_BIT(PWR->CR1, PWR_CR1_DBP) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        ret = HAL_TIMEOUT;
        break;
      }
    }

    if (ret == HAL_OK)
    {
      /* Reset the Backup domain only if the RTC Clock source selection is modified from default */
      tmpregister = READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL);

      if ((tmpregister != RCC_RTCCLKSOURCE_NONE) && (tmpregister != PeriphClkInit->RTCClockSelection))
      {
        /* Store the content of BDCR register before the reset of Backup Domain */
        tmpregister = READ_BIT(RCC->BDCR, ~(RCC_BDCR_RTCSEL));
        /* RTC Clock selection can be changed only if the Backup Domain is reset */
        __HAL_RCC_BACKUPRESET_FORCE();
        __HAL_RCC_BACKUPRESET_RELEASE();
        /* Restore the Content of BDCR register */
        RCC->BDCR = tmpregister;
      }

      /* Wait for LSE reactivation if LSE was enable prior to Backup Domain reset */
      if (HAL_IS_BIT_SET(tmpregister, RCC_BDCR_LSEON))
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till LSE is ready */
        while (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            ret = HAL_TIMEOUT;
            break;
          }
        }
      }

      if (ret == HAL_OK)
      {
        /* Apply new RTC clock source selection */
        __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
      }
      else
      {
        /* set overall return value */
        status = ret;
      }
    }
    else
    {
      /* set overall return value */
      status = ret;
    }

    /* Restore clock configuration if changed */
    if (pwrclkchanged == SET)
    {
      __HAL_RCC_PWR_CLK_DISABLE();
    }
  }

  /*-------------------------- USART1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART1CLKSOURCE(PeriphClkInit->Usart1ClockSelection));

    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(PeriphClkInit->Usart1ClockSelection);
  }

  /*-------------------------- USART2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(PeriphClkInit->Usart2ClockSelection));

    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(PeriphClkInit->Usart2ClockSelection);
  }

  /*-------------------------- LPUART1 clock source configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(PeriphClkInit->Lpuart1ClockSelection));

    /* Configure the LPUART1 clock source */
    __HAL_RCC_LPUART1_CONFIG(PeriphClkInit->Lpuart1ClockSelection);
  }

  /*-------------------------- LPUART2 clock source configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART2) == RCC_PERIPHCLK_LPUART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART2CLKSOURCE(PeriphClkInit->Lpuart2ClockSelection));

    /* Configure the LPUART2 clock source */
    __HAL_RCC_LPUART2_CONFIG(PeriphClkInit->Lpuart2ClockSelection);
  }
#if defined (LPUART3)
  /*-------------------------- LPUART3 clock source configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART3) == RCC_PERIPHCLK_LPUART3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART3CLKSOURCE(PeriphClkInit->Lpuart3ClockSelection));

    /* Configure the LPUART3 clock source */
    __HAL_RCC_LPUART3_CONFIG(PeriphClkInit->Lpuart3ClockSelection);
  }
#endif /* LPUART3 */
  /*-------------------------- I2C1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));

    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }

  /*-------------------------- I2C3 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(PeriphClkInit->I2c3ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(PeriphClkInit->I2c3ClockSelection);
  }

  /*----------------------- LPTIM1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == (RCC_PERIPHCLK_LPTIM1))
  {
    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));
    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }

  /*-------------------------- LPTIM2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM2) == (RCC_PERIPHCLK_LPTIM2))
  {
    assert_param(IS_RCC_LPTIM2CLKSOURCE(PeriphClkInit->Lptim2ClockSelection));
    __HAL_RCC_LPTIM2_CONFIG(PeriphClkInit->Lptim2ClockSelection);
  }
#if defined (LPTIM3)
  /*----------------------- LPTIM3 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM3) == (RCC_PERIPHCLK_LPTIM3))
  {
    assert_param(IS_RCC_LPTIM3CLKSOURCE(PeriphClkInit->Lptim3ClockSelection));
    __HAL_RCC_LPTIM3_CONFIG(PeriphClkInit->Lptim3ClockSelection);
  }
#endif /* LPTIM3 */
  /*-------------------------- ADC clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC) == RCC_PERIPHCLK_ADC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCCLKSOURCE(PeriphClkInit->AdcClockSelection));
    if (PeriphClkInit->AdcClockSelection == RCC_ADCCLKSOURCE_PLLP)
    {
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_DIVP);
    }
    /* Configure the ADC1 clock source */
    __HAL_RCC_ADC_CONFIG(PeriphClkInit->AdcClockSelection);
  }
#if defined (USB_DRD_FS)
  /*-------------------------- USB clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USB) == RCC_PERIPHCLK_USB)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USBCLKSOURCE(PeriphClkInit->UsbClockSelection));
    if (PeriphClkInit->UsbClockSelection == RCC_USBCLKSOURCE_PLLQ)
    {
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_DIVQ);
    }
    /* Configure the USB clock source */
    __HAL_RCC_USB_CONFIG(PeriphClkInit->UsbClockSelection);

  }
#endif /* USB_DRD_FS */
  /*-------------------------- RNG clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RNG) == RCC_PERIPHCLK_RNG)
  {
    /* Check the parameters */
    assert_param(IS_RCC_RNGCLKSOURCE(PeriphClkInit->RngClockSelection));
    if (PeriphClkInit->RngClockSelection == RCC_RNGCLKSOURCE_PLLQ)
    {
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_DIVQ);
    }
    /* Configure the RNG clock source */
    __HAL_RCC_RNG_CONFIG(PeriphClkInit->RngClockSelection);

  }
  /*-------------------------- TIM1 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM1) == RCC_PERIPHCLK_TIM1)
  {

    /* Check the parameters */
    assert_param(IS_RCC_TIM1CLKSOURCE(PeriphClkInit->Tim1ClockSelection));
    if (PeriphClkInit->Tim1ClockSelection == RCC_TIM1CLKSOURCE_PLLQ)
    {
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_DIVQ);
    }
    /* Configure the TIM1 clock source */
    __HAL_RCC_TIM1_CONFIG(PeriphClkInit->Tim1ClockSelection);

  }
  /*-------------------------- TIM15 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM15) == RCC_PERIPHCLK_TIM15)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM15CLKSOURCE(PeriphClkInit->Tim15ClockSelection));
    if (PeriphClkInit->Tim15ClockSelection == RCC_TIM15CLKSOURCE_PLLQ)
    {
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_DIVQ);
    }
    /* Configure the TIM1 clock source */
    __HAL_RCC_TIM15_CONFIG(PeriphClkInit->Tim15ClockSelection);

  }

  return status;
}
/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks(USART1, USART2, LPUART1, LPUART2, LPUART3, I2C1, I2C2, I2C3, I2C4, LPTIM1,
  *         LPTIM2, LPTIM3, USB, TIM1, LCD, SPI1, SPI2, SPI3, RTC, RNG, ADC, DAC, IWDG).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_RTC  | RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | \
                                        RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_LPUART2 | RCC_PERIPHCLK_I2C1 | \
                                        RCC_PERIPHCLK_I2C3 | RCC_PERIPHCLK_LPTIM1 | RCC_PERIPHCLK_LPTIM2 | \
                                        RCC_PERIPHCLK_TIM1 | RCC_PERIPHCLK_TIM15 | RCC_PERIPHCLK_RNG | \
                                        RCC_PERIPHCLK_ADC ;

#if defined(LPUART3)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_LPUART3;
#endif /* LPUART3*/
#if defined(LPTIM3)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_LPTIM3;
#endif /* LPTIM3 */
#if defined(USB_DRD_FS)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_USB;
#endif /* USB_DRD_FS */
  /* Get the RTC clock source ---------------------------------------------*/
  PeriphClkInit->RTCClockSelection   = __HAL_RCC_GET_RTC_SOURCE();

  /* Get the USART1 clock source ---------------------------------------------*/
  PeriphClkInit->Usart1ClockSelection   = __HAL_RCC_GET_USART1_SOURCE();

  /* Get the USART2 clock source ---------------------------------------------*/
  PeriphClkInit->Usart2ClockSelection   = __HAL_RCC_GET_USART2_SOURCE();

  /* Get the LPUART1 clock source --------------------------------------------*/
  PeriphClkInit->Lpuart1ClockSelection  = __HAL_RCC_GET_LPUART1_SOURCE();

  /* Get the LPUART2 clock source --------------------------------------------*/
  PeriphClkInit->Lpuart2ClockSelection  = __HAL_RCC_GET_LPUART2_SOURCE();

#if defined (LPUART3)
  /* Get the LPUART3 clock source --------------------------------------------*/
  PeriphClkInit->Lpuart3ClockSelection  = __HAL_RCC_GET_LPUART3_SOURCE();
#endif /* LPUART3 */

  /* Get the I2C1 clock source -----------------------------------------------*/
  PeriphClkInit->I2c1ClockSelection     = __HAL_RCC_GET_I2C1_SOURCE();

  /* Get the I2C3 clock source -----------------------------------------------*/
  PeriphClkInit->I2c3ClockSelection     = __HAL_RCC_GET_I2C3_SOURCE();

  /* Get the LPTIM1 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim1ClockSelection  = __HAL_RCC_GET_LPTIM1_SOURCE();

  /* Get the LPTIM2 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim2ClockSelection   = __HAL_RCC_GET_LPTIM2_SOURCE();

#if defined (LPTIM3)
  /* Get the LPTIM3 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim3ClockSelection   = __HAL_RCC_GET_LPTIM3_SOURCE();
#endif /* LPTIM3 */

  /* Get the ADC clock source -----------------------------------------------*/
  PeriphClkInit->AdcClockSelection      = __HAL_RCC_GET_ADC_SOURCE();

  /* Get the TIM1 clock source -----------------------------------------------*/
  PeriphClkInit->Tim1ClockSelection     = __HAL_RCC_GET_TIM1_SOURCE();

  /* Get the TIM15 clock source -----------------------------------------------*/
  PeriphClkInit->Tim15ClockSelection     = __HAL_RCC_GET_TIM15_SOURCE();

#if defined (USB_DRD_FS)
  /* Get the USB clock source -------------------------------------------------*/
  PeriphClkInit->UsbClockSelection     = __HAL_RCC_GET_USB_SOURCE();
#endif /* USB_DRD_FS */

  /* Get the RNG clock source -------------------------------------------------*/
  PeriphClkInit->RngClockSelection     = __HAL_RCC_GET_RNG_SOURCE();

}

/**
  * @brief  Return the peripheral clock frequency for peripherals with clock source from PLLSAIs
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_ADC  ADC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1  I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3  I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1  LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2  LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM3  LPTIM3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART2  LPUART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART3  LPUART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART1  USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2  USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART3  USART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART4  USART4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USB  USB peripheral clock (only for devices with USB)
  *            @arg @ref RCC_PERIPHCLK_RNG  RNG peripheral clock (only for devices with RNG)
  *            @arg @ref RCC_PERIPHCLK_TIM1  TIM1 peripheral clock (only for devices with TIM1)
  *            @arg @ref RCC_PERIPHCLK_TIM15  TIM15 peripheral clock (only for devices with TIM15)
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;    /* no init needed */
  PLL_ClocksTypeDef pll_freq;
  uint32_t msirange;
  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

  if (PeriphClk == RCC_PERIPHCLK_RTC)
  {
    /* Get the current RCC_PERIPHCLK_RTC source */
    srcclk = __HAL_RCC_GET_RTC_SOURCE();

    switch (srcclk)
    {
      case RCC_RTCCLKSOURCE_LSE:
        /* Check if LSE is ready */
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
        break;
      case RCC_RTCCLKSOURCE_LSI:
        /* Check if LSI is ready */
        if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
        {
#if defined(RCC_CSR_LSIPREDIV)
          if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
          {
            frequency = LSI_VALUE / 128U;
          }
          else
#endif /* RCC_CSR_LSIPREDIV */
          {
            frequency = LSI_VALUE;
          }
        }
        break;
      case RCC_RTCCLKSOURCE_HSE:
        /* Check if HSE is ready */
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = HSE_VALUE / 32U;
        }
        break;
      default:
        /* No clock source, frequency default init at 0 */
        break;
    }
  }
  else
  {
    /* Other external peripheral clock source than RTC */
    switch (PeriphClk)
    {
      case RCC_PERIPHCLK_USART1:
      {
        /* Get the current USART1 source */
        srcclk = __HAL_RCC_GET_USART1_SOURCE();

        switch (srcclk)
        {
          case RCC_USART1CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_USART1CLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_USART1CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_USART1CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }

        break;
      }

      case RCC_PERIPHCLK_USART2:
      {
        /* Get the current USART2 source */
        srcclk = __HAL_RCC_GET_USART2_SOURCE();

        switch (srcclk)
        {
          case RCC_USART2CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_USART2CLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_USART2CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_USART2CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }

        break;
      }

      /* USART3 and USART4 source */
      case RCC_PERIPHCLK_USART3:
      case RCC_PERIPHCLK_USART4:
      {
        frequency = HAL_RCC_GetPCLK1Freq();
        break;
      }

      case RCC_PERIPHCLK_LPUART1:
      {
        /* Get the current LPUART1 source */
        srcclk = __HAL_RCC_GET_LPUART1_SOURCE();

        switch (srcclk)
        {
          case RCC_LPUART1CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_LPUART1CLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_LPUART1CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_LPUART1CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
      case RCC_PERIPHCLK_LPUART2:
      {
        /* Get the current LPUART2 source */
        srcclk = __HAL_RCC_GET_LPUART2_SOURCE();

        switch (srcclk)
        {
          case RCC_LPUART2CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_LPUART2CLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_LPUART2CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_LPUART2CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
#if defined(LPUART3)
      case RCC_PERIPHCLK_LPUART3:
      {
        /* Get the current LPUART3 source */
        srcclk = __HAL_RCC_GET_LPUART3_SOURCE();

        switch (srcclk)
        {
          case RCC_LPUART3CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_LPUART3CLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_LPUART3CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_LPUART3CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
#endif /* LPUART3 */
      case RCC_PERIPHCLK_ADC:
      {
        srcclk = __HAL_RCC_GET_ADC_SOURCE();

        switch (srcclk)
        {
          case RCC_ADCCLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_ADCCLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;
          case RCC_ADCCLKSOURCE_PLLP:
            HAL_RCCEx_GetPLLClockFreq(&pll_freq);
            frequency = pll_freq.PLL_P_Frequency;
            break;

          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }

      case RCC_PERIPHCLK_I2C1:
      {
        /* Get the current I2C1 source */
        srcclk = __HAL_RCC_GET_I2C1_SOURCE();

        switch (srcclk)
        {
          case RCC_I2C1CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_I2C1CLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_I2C1CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }

        break;
      }

      case RCC_PERIPHCLK_I2C3:
      {
        /* Get the current I2C3 source */
        srcclk = __HAL_RCC_GET_I2C3_SOURCE();

        switch (srcclk)
        {
          case RCC_I2C3CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_I2C3CLKSOURCE_SYSCLK:
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          case RCC_I2C3CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }

        break;
      }

      case RCC_PERIPHCLK_LPTIM1:
      {
        /* Get the current LPTIM1 source */
        srcclk = __HAL_RCC_GET_LPTIM1_SOURCE();

        switch (srcclk)
        {
          case RCC_LPTIM1CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_LPTIM1CLKSOURCE_LSI:
            if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
            {
#if defined(RCC_CSR_LSIPREDIV)
              if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
              {
                frequency = LSI_VALUE / 128U;
              }
              else
#endif /* RCC_CSR_LSIPREDIV */
              {
                frequency = LSI_VALUE;
              }
            }
            break;
          case RCC_LPTIM1CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_LPTIM1CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }

        break;
      }

      case RCC_PERIPHCLK_LPTIM2:
      {
        /* Get the current LPTIM2 source */
        srcclk = __HAL_RCC_GET_LPTIM2_SOURCE();

        switch (srcclk)
        {
          case RCC_LPTIM2CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_LPTIM2CLKSOURCE_LSI:
            if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
            {
#if defined(RCC_CSR_LSIPREDIV)
              if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
              {
                frequency = LSI_VALUE / 128U;
              }
              else
#endif /* RCC_CSR_LSIPREDIV */
              {
                frequency = LSI_VALUE;
              }
            }
            break;
          case RCC_LPTIM2CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_LPTIM2CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
#if defined (LPTIM3)
      case RCC_PERIPHCLK_LPTIM3:
      {
        /* Get the current LPTIM3 source */
        srcclk = __HAL_RCC_GET_LPTIM3_SOURCE();

        switch (srcclk)
        {
          case RCC_LPTIM3CLKSOURCE_PCLK1:
            frequency = HAL_RCC_GetPCLK1Freq();
            break;
          case RCC_LPTIM3CLKSOURCE_LSI:
            if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
            {
#if defined(RCC_CSR_LSIPREDIV)
              if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
              {
                frequency = LSI_VALUE / 128U;
              }
              else
#endif /* RCC_CSR_LSIPREDIV */
              {
                frequency = LSI_VALUE;
              }
            }
            break;
          case RCC_LPTIM3CLKSOURCE_HSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            break;
          case RCC_LPTIM3CLKSOURCE_LSE:
            if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
            {
              frequency = LSE_VALUE;
            }
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }

        break;
      }
#endif /* LPTIM3 */
      case RCC_PERIPHCLK_TIM1:
      {
        /* Get the current TIM1 source */
        srcclk = __HAL_RCC_GET_TIM1_SOURCE();
        switch (srcclk)
        {
          case RCC_TIM1CLKSOURCE_PCLK1:
            if ((READ_BIT(RCC->CFGR, RCC_CFGR_PPRE) == RCC_HCLK_DIV1))
            {
              frequency = HAL_RCC_GetPCLK1Freq();
            }
            else
            {
              frequency = (HAL_RCC_GetPCLK1Freq() * 2U);
            }
            break;
          case RCC_TIM1CLKSOURCE_PLLQ:
            HAL_RCCEx_GetPLLClockFreq(&pll_freq);
            frequency = pll_freq.PLL_Q_Frequency;
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
      case RCC_PERIPHCLK_TIM15:
      {
        /* Get the current TIM15 source */
        srcclk = __HAL_RCC_GET_TIM15_SOURCE();
        switch (srcclk)
        {
          case RCC_TIM15CLKSOURCE_PCLK1:
            if ((READ_BIT(RCC->CFGR, RCC_CFGR_PPRE) == RCC_HCLK_DIV1))
            {
              frequency = HAL_RCC_GetPCLK1Freq();
            }
            else
            {
              frequency = (HAL_RCC_GetPCLK1Freq() * 2U);
            }
            break;
          case RCC_TIM15CLKSOURCE_PLLQ:
            HAL_RCCEx_GetPLLClockFreq(&pll_freq);
            frequency = pll_freq.PLL_Q_Frequency;
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
#if defined (USB_DRD_FS)
      case RCC_PERIPHCLK_USB:
      {
        /* Get the current USB source */
        srcclk = __HAL_RCC_GET_USB_SOURCE();
        switch (srcclk)
        {
          case RCC_USBCLKSOURCE_HSI48:
            frequency = HSI48_VALUE;
            break;
          case RCC_USBCLKSOURCE_MSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_MSIRDY))
            {
              msirange = (__HAL_RCC_GET_MSI_RANGE() >> 4U);
              if (msirange > 11U)
              {
                msirange = 11U;
              }
              frequency = MSIRangeTable[msirange];
            }
            break;
          case RCC_USBCLKSOURCE_PLLQ:
            HAL_RCCEx_GetPLLClockFreq(&pll_freq);
            frequency = pll_freq.PLL_Q_Frequency;
            break;
          /* Clock not enabled for USB */
          case RCC_USBCLKSOURCE_NONE:
            frequency = 0U;
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
#endif /* USB_DRD_FS */
      case RCC_PERIPHCLK_RNG:
      {
        /* Get the current RNG source */
        srcclk = __HAL_RCC_GET_RNG_SOURCE();
        switch (srcclk)
        {
          case RCC_RNGCLKSOURCE_HSI48:
            frequency = HSI48_VALUE;
            break;
          case RCC_RNGCLKSOURCE_MSI:
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_MSIRDY))
            {
              msirange = (__HAL_RCC_GET_MSI_RANGE() >> 4U);
              if (msirange > 11U)
              {
                msirange = 11U;
              }
              frequency = MSIRangeTable[msirange];
            }
            break;
          case RCC_RNGCLKSOURCE_PLLQ:
            HAL_RCCEx_GetPLLClockFreq(&pll_freq);
            frequency = pll_freq.PLL_Q_Frequency;
            break;
          /* Clock not enabled for RNG */
          case RCC_RNGCLKSOURCE_NONE:
            frequency = 0U;
            break;
          default:
            /* No clock source, frequency default init at 0 */
            break;
        }
        break;
      }
      default:
        break;
    }
  }
  return (frequency);
}

/**
  * @brief  Returns the PLL clock frequencies :PLL_P_Frequency,PLL_R_Frequency and PLL_Q_Frequency
  * @note   The PLL clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL factors
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  *
  * @note   Each time PLLCLK changes, this function must be called to update the
  *         right PLLCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @param  PLL_Clocks structure.
  * @retval None
  */

void HAL_RCCEx_GetPLLClockFreq(PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t plln;
  uint32_t pllvco;
  uint32_t msirange;

  plln = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos);
  pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
  pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1U;
  msirange = (__HAL_RCC_GET_MSI_RANGE() >> 4U);
  if (msirange > 11U)
  {
    msirange = 11U;
  }
  switch (pllsource)
  {

    case RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllvco = (HSI_VALUE / pllm) * plln;
      break;

    case RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllvco = ((MSIRangeTable[msirange] / pllm) * plln);
      break;

    case RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
      pllvco = (HSE_VALUE / pllm) * plln;
      break;

    default:
      pllvco = ((MSIRangeTable[msirange] / pllm) * plln);
      break;
  }

  if (__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_DIVP) != 0U)
  {
    PLL_Clocks->PLL_P_Frequency = (uint32_t)(pllvco / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) \
                                                        >> RCC_PLLCFGR_PLLP_Pos) + 1U));
  }
  else
  {
    PLL_Clocks->PLL_P_Frequency = 0;
  }

  if (__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_DIVQ) != 0U)
  {
    PLL_Clocks->PLL_Q_Frequency = (uint32_t)(pllvco / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLQ) \
                                                        >> RCC_PLLCFGR_PLLQ_Pos) + 1U));
  }
  else
  {
    PLL_Clocks->PLL_Q_Frequency = 0;
  }

  if (__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_DIVR) != 0U)
  {
    PLL_Clocks->PLL_R_Frequency = (uint32_t)(pllvco / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) \
                                                        >> RCC_PLLCFGR_PLLR_Pos) + 1U));
  }
  else
  {
    PLL_Clocks->PLL_R_Frequency = 0;
  }
}

/**
  * @brief  Enable PLL.
  * @param  PLLInit  pointer to an RCC_PLLInitTypeDef structure that
  *         contains the configuration information for the PLL
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_EnablePLL(RCC_PLLInitTypeDef  *PLLInit)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  /* check for PLL Parameters used to output PLLCLK */
  assert_param(IS_RCC_PLLSOURCE(PLLInit->PLLSource));
  assert_param(IS_RCC_PLL_DIVM_VALUE(PLLInit->PLLM));
  assert_param(IS_RCC_PLL_MULN_VALUE(PLLInit->PLLN));
  assert_param(IS_RCC_PLL_DIVP_VALUE(PLLInit->PLLP));
  assert_param(IS_RCC_PLL_DIVQ_VALUE(PLLInit->PLLQ));
  assert_param(IS_RCC_PLL_DIVR_VALUE(PLLInit->PLLR));
  assert_param(IS_RCC_PLLCLOCKOUT_VALUE(PLLInit->PLLClockOut));

  /* Disable the PLL */
  __HAL_RCC_PLL_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL is ready to be updated */
  while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > 2U) /* PLL_TIMEOUT_VALUE) */
    {
      status = HAL_TIMEOUT;
      break;
    }
  }

  if (status == HAL_OK)
  {
    /* Make sure PLLSource is ready */
    status = RCCEx_PLLSource_Enable(PLLInit->PLLSource);

    if (status == HAL_OK)
    {
      /* Configure the PLL clock source, multiplication factor N, */
      /* and division factors M, P, Q and R */
      __HAL_RCC_PLL_CONFIG(PLLInit->PLLSource, PLLInit->PLLM, PLLInit->PLLN,
                           PLLInit->PLLP, PLLInit->PLLQ, PLLInit->PLLR);

      /* Configure the PLL Clock output(s) */
      __HAL_RCC_PLLCLKOUT_ENABLE(PLLInit->PLLClockOut);

      /* Enable the PLL again by setting PLLON to 1*/
      __HAL_RCC_PLL_ENABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till PLL is ready */
      while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > 2U) /* PLL_TIMEOUT_VALUE) */
        {
          status = HAL_TIMEOUT;
          break;
        }
      }
    }
  }

  return status;
}

/**
  * @brief  Disable PLL.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_DisablePLL(void)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  /* Disable the PLL */
  __HAL_RCC_PLL_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL is ready */
  while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > 2U) /* PLL_TIMEOUT_VALUE) */
    {
      status = HAL_TIMEOUT;
      break;
    }
  }

  /* To save power disable the PLL Source, FRACN and Clock outputs */
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN | RCC_PLLCFGR_PLLQEN | RCC_PLLCFGR_PLLPEN | RCC_PLLCFGR_PLLSRC);

  return status;
}

/**
  * @brief  Configure the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @param  WakeUpClk  Wakeup clock
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_MSI  MSI oscillator selection
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_HSI  HSI oscillator selection
  * @note   This function shall not be called after the Clock Security System on HSE has been
  *         enabled.
  * @retval None
  */
void HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk)
{
  assert_param(IS_RCC_STOP_WAKEUPCLOCK(WakeUpClk));

  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(WakeUpClk);
}

/**
  * @brief  Configure the MSI range after standby mode.
  * @note   After Standby its frequency can be selected between 3 possible values (1, 3.072 or 4 MHz).
  * @param  MSIRange  MSI range
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_MSIRANGE_4  Range 4 around 4 MHz (reset value)
  *            @arg @ref RCC_MSIRANGE_5  Range 5 around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  Range 6 around 1.5 MHz
  *            @arg @ref RCC_MSIRANGE_7  Range 7 around 1 MHz
  * @retval None
  */
void HAL_RCCEx_StandbyMSIRangeConfig(uint32_t MSIRange)
{
  assert_param(IS_RCC_MSI_STANDBY_CLOCK_RANGE(MSIRange));

  __HAL_RCC_MSI_STANDBY_RANGE_CONFIG(MSIRange);
}

/**
  * @brief  Enable the PLL-mode of the MSI.
  * @note   Prior to enable the PLL-mode of the MSI for automatic hardware
  *         calibration LSE oscillator is to be enabled with HAL_RCC_OscConfig().
  * @retval None
  */
void HAL_RCCEx_EnableMSIPLLMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Disable the PLL-mode of the MSI.
  * @note   PLL-mode of the MSI is automatically reset when LSE oscillator is disabled.
  * @retval None
  */
void HAL_RCCEx_DisableMSIPLLMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Enables the LSE Clock Security System.
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON) ;
}

/**
  * @brief  Disables the LSE Clock Security System.
  * @note   Once enabled this bit cannot be disabled, except after an LSE failure detection
  *         (LSECSSD=1). In that case the software MUST disable the LSECSSON bit.
  *         Reset by power on reset and RTC software reset (RTCRST bit).
  * @retval None
  */
void HAL_RCCEx_DisableLSECSS(void)
{
  /* Disable LSE CSS */
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON) ;
}

/**
  * @brief  Enable the LSE Clock Security System IT & corresponding EXTI line.
  * @note   LSE Clock Security System IT is mapped on RTC EXTI line 27
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS_IT(void)
{
  /* Enable LSE CSS */
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON) ;
  /* Enable LSE CSS IT */
  __HAL_RCC_ENABLE_IT(RCC_IT_LSECSS);
  /* Enable IT on EXTI Line 27 */
  __HAL_RCC_LSECSS_EXTI_ENABLE_IT();
  __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_EDGE();
}

/**
  * @brief Handle the RCC LSE Clock Security System interrupt request.
  * @retval None
  */
void HAL_RCCEx_LSECSS_IRQHandler(void)
{
  /* Check RCC LSE CSSF flag  */
  if (__HAL_RCC_GET_IT(RCC_IT_LSECSS))
  {
    /* RCC LSE Clock Security System interrupt user callback */
    HAL_RCCEx_LSECSS_Callback();

    /* Clear RCC LSE CSS pending bit */
    __HAL_RCC_CLEAR_IT(RCC_IT_LSECSS);
  }
}

/**
  * @brief  RCCEx LSE Clock Security System interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_LSECSS_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_LSECSS_Callback should be implemented in the user file
   */
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
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  FlagStatus       pwrclkchanged = RESET;
  FlagStatus       backupchanged = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* LSCO Pin Clock Enable */
  __LSCO_CLK_ENABLE();
#if defined (LSCO_PIN)
  /* Configure the LSCO pin in analog mode */
  GPIO_InitStruct.Pin = LSCO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LSCO_GPIO_PORT, &GPIO_InitStruct);
#endif /* LSCO_PIN */
  /* Update LSCOSEL clock source in Backup Domain control register */
  if (__HAL_RCC_PWR_IS_CLK_DISABLED())
  {
    __HAL_RCC_PWR_CLK_ENABLE();
    pwrclkchanged = SET;
  }
  if (HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
  {
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL | RCC_BDCR_LSCOEN, LSCOSource | RCC_BDCR_LSCOEN);

  if (backupchanged == SET)
  {
    HAL_PWR_DisableBkUpAccess();
  }
  if (pwrclkchanged == SET)
  {
    __HAL_RCC_PWR_CLK_DISABLE();
  }
}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{
  FlagStatus       pwrclkchanged = RESET;
  FlagStatus       backupchanged = RESET;

  /* Update LSCOEN bit in Backup Domain control register */
  if (__HAL_RCC_PWR_IS_CLK_DISABLED())
  {
    __HAL_RCC_PWR_CLK_ENABLE();
    pwrclkchanged = SET;
  }
  if (HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
  {
    /* Enable access to the backup domain */
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);

  /* Restore previous configuration */
  if (backupchanged == SET)
  {
    /* Disable access to the backup domain */
    HAL_PWR_DisableBkUpAccess();
  }
  if (pwrclkchanged == SET)
  {
    __HAL_RCC_PWR_CLK_DISABLE();
  }
}

/**
  * @}
  */

#if defined(CRS)

/** @defgroup RCCEx_Exported_Functions_Group3 Extended Clock Recovery System Control functions
  * @brief  Extended Clock Recovery System Control functions
  *
@verbatim
 ===============================================================================
                ##### Extended Clock Recovery System Control functions  #####
 ===============================================================================
    [..]
      For devices with Clock Recovery System feature (CRS), RCC Extension HAL driver can be used as follows:

      (#) In System clock config, HSI48 needs to be enabled

      (#) Enable CRS clock in IP MSP init which will use CRS functions

      (#) Call CRS functions as follows:
          (##) Prepare synchronization configuration necessary for HSI48 calibration
              (+++) Default values can be set for frequency Error Measurement (reload and error limit)
                        and also HSI48 oscillator smooth trimming.
              (+++) Macro __HAL_RCC_CRS_RELOADVALUE_CALCULATE can be also used to calculate
                        directly reload value with target and synchronization frequencies values
          (##) Call function HAL_RCCEx_CRSConfig which
              (+++) Resets CRS registers to their default values.
              (+++) Configures CRS registers with synchronization configuration
              (+++) Enables automatic calibration and frequency error counter feature
           Note: When using USB LPM (Link Power Management) and the device is in Sleep mode, the
           periodic USB SOF will not be generated by the host. No SYNC signal will therefore be
           provided to the CRS to calibrate the HSI48 on the run. To guarantee the required clock
           precision after waking up from Sleep mode, the LSE or reference clock on the GPIOs
           should be used as SYNC signal.

          (##) A polling function is provided to wait for complete synchronization
              (+++) Call function HAL_RCCEx_CRSWaitSynchronization()
              (+++) According to CRS status, user can decide to adjust again the calibration or continue
                        application if synchronization is OK

      (#) User can retrieve information related to synchronization in calling function
            HAL_RCCEx_CRSGetSynchronizationInfo()

      (#) Regarding synchronization status and synchronization information, user can try a new calibration
           in changing synchronization configuration and call again HAL_RCCEx_CRSConfig.
           Note: When the SYNC event is detected during the downcounting phase (before reaching the zero value),
           it means that the actual frequency is lower than the target (and so, that the TRIM value should be
           incremented), while when it is detected during the upcounting phase it means that the actual frequency
           is higher (and that the TRIM value should be decremented).

      (#) In interrupt mode, user can resort to the available macros (__HAL_RCC_CRS_XXX_IT). Interrupts will go
          through CRS Handler (CRS_IRQn/CRS_IRQHandler)
              (++) Call function HAL_RCCEx_CRSConfig()
              (++) Enable CRS_IRQn (thanks to NVIC functions)
              (++) Enable CRS interrupt (__HAL_RCC_CRS_ENABLE_IT)
              (++) Implement CRS status management in the following user callbacks called from
                   HAL_RCCEx_CRS_IRQHandler():
                   (+++) HAL_RCCEx_CRS_SyncOkCallback()
                   (+++) HAL_RCCEx_CRS_SyncWarnCallback()
                   (+++) HAL_RCCEx_CRS_ExpectedSyncCallback()
                   (+++) HAL_RCCEx_CRS_ErrorCallback()

      (#) To force a SYNC EVENT, user can use the function HAL_RCCEx_CRSSoftwareSynchronizationGenerate().
          This function can be called before calling HAL_RCCEx_CRSConfig (for instance in Systick handler)

@endverbatim
  * @{
  */

/**
  * @brief  Start automatic synchronization for polling mode
  * @param  pInit Pointer on RCC_CRSInitTypeDef structure
  * @retval None
  */
void HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *const pInit)
{
  uint32_t value;  /* no init needed */

  /* Check the parameters */
  assert_param(IS_RCC_CRS_SYNC_DIV(pInit->Prescaler));
  assert_param(IS_RCC_CRS_SYNC_SOURCE(pInit->Source));
  assert_param(IS_RCC_CRS_SYNC_POLARITY(pInit->Polarity));
  assert_param(IS_RCC_CRS_RELOADVALUE(pInit->ReloadValue));
  assert_param(IS_RCC_CRS_ERRORLIMIT(pInit->ErrorLimitValue));
  assert_param(IS_RCC_CRS_HSI48CALIBRATION(pInit->HSI48CalibrationValue));

  /* CONFIGURATION */

  /* Before configuration, reset CRS registers to their default values*/
  __HAL_RCC_CRS_FORCE_RESET();
  __HAL_RCC_CRS_RELEASE_RESET();

  /* Set the SYNCDIV[2:0] bits according to Prescaler value */
  /* Set the SYNCSRC[1:0] bits according to Source value */
  /* Set the SYNCSPOL bit according to Polarity value */
  value = (pInit->Prescaler | pInit->Source | pInit->Polarity);
  /* Set the RELOAD[15:0] bits according to ReloadValue value */
  value |= pInit->ReloadValue;
  /* Set the FELIM[7:0] bits according to ErrorLimitValue value */
  value |= (pInit->ErrorLimitValue << CRS_CFGR_FELIM_Pos);
  WRITE_REG(CRS->CFGR, value);

  /* Adjust HSI48 oscillator smooth trimming */
  /* Set the TRIM[6:0] bits according to RCC_CRS_HSI48CalibrationValue value */
  MODIFY_REG(CRS->CR, CRS_CR_TRIM, (pInit->HSI48CalibrationValue << CRS_CR_TRIM_Pos));

  /* START AUTOMATIC SYNCHRONIZATION*/

  /* Enable Automatic trimming & Frequency error counter */
  SET_BIT(CRS->CR, CRS_CR_AUTOTRIMEN | CRS_CR_CEN);
}

/**
  * @brief  Generate the software synchronization event
  * @retval None
  */
void HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void)
{
  SET_BIT(CRS->CR, CRS_CR_SWSYNC);
}

/**
  * @brief  Return synchronization info
  * @param  pSynchroInfo Pointer on RCC_CRSSynchroInfoTypeDef structure
  * @retval None
  */
void HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo)
{
  /* Check the parameter */
  assert_param(pSynchroInfo != (void *)NULL);

  /* Get the reload value */
  pSynchroInfo->ReloadValue = (READ_BIT(CRS->CFGR, CRS_CFGR_RELOAD));

  /* Get HSI48 oscillator smooth trimming */
  pSynchroInfo->HSI48CalibrationValue = (READ_BIT(CRS->CR, CRS_CR_TRIM) >> CRS_CR_TRIM_Pos);

  /* Get Frequency error capture */
  pSynchroInfo->FreqErrorCapture = (READ_BIT(CRS->ISR, CRS_ISR_FECAP) >> CRS_ISR_FECAP_Pos);

  /* Get Frequency error direction */
  pSynchroInfo->FreqErrorDirection = (READ_BIT(CRS->ISR, CRS_ISR_FEDIR));
}

/**
  * @brief Wait for CRS Synchronization status.
  * @param Timeout  Duration of the timeout
  * @note  Timeout is based on the maximum time to receive a SYNC event based on synchronization
  *        frequency.
  * @note    If Timeout set to HAL_MAX_DELAY, HAL_TIMEOUT will be never returned.
  * @retval Combination of Synchronization status
  *          This parameter can be a combination of the following values:
  *            @arg @ref RCC_CRS_TIMEOUT
  *            @arg @ref RCC_CRS_SYNCOK
  *            @arg @ref RCC_CRS_SYNCWARN
  *            @arg @ref RCC_CRS_SYNCERR
  *            @arg @ref RCC_CRS_SYNCMISS
  *            @arg @ref RCC_CRS_TRIMOVF
  */
uint32_t HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout)
{
  uint32_t crsstatus = RCC_CRS_NONE;
  uint32_t tickstart;

  /* Get timeout */
  tickstart = HAL_GetTick();

  /* Wait for CRS flag or timeout detection */
  do
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        crsstatus = RCC_CRS_TIMEOUT;
      }
    }
    /* Check CRS SYNCOK flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCOK))
    {
      /* CRS SYNC event OK */
      crsstatus |= RCC_CRS_SYNCOK;

      /* Clear CRS SYNC event OK bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCOK);
    }

    /* Check CRS SYNCWARN flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCWARN))
    {
      /* CRS SYNC warning */
      crsstatus |= RCC_CRS_SYNCWARN;

      /* Clear CRS SYNCWARN bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCWARN);
    }

    /* Check CRS TRIM overflow flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_TRIMOVF))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_TRIMOVF;

      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_TRIMOVF);
    }

    /* Check CRS Error flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCERR))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_SYNCERR;

      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCERR);
    }

    /* Check CRS SYNC Missed flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCMISS))
    {
      /* CRS SYNC Missed */
      crsstatus |= RCC_CRS_SYNCMISS;

      /* Clear CRS SYNC Missed bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCMISS);
    }

    /* Check CRS Expected SYNC flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_ESYNC))
    {
      /* frequency error counter reached a zero value */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_ESYNC);
    }
  } while (RCC_CRS_NONE == crsstatus);

  return crsstatus;
}

/**
  * @brief Handle the Clock Recovery System interrupt request.
  * @retval None
  */
void HAL_RCCEx_CRS_IRQHandler(void)
{
  uint32_t crserror = RCC_CRS_NONE;
  /* Get current IT flags and IT sources values */
  uint32_t itflags = READ_REG(CRS->ISR);
  uint32_t itsources = READ_REG(CRS->CR);

  /* Check CRS SYNCOK flag  */
  if (((itflags & RCC_CRS_FLAG_SYNCOK) != 0U) && ((itsources & RCC_CRS_IT_SYNCOK) != 0U))
  {
    /* Clear CRS SYNC event OK flag */
    WRITE_REG(CRS->ICR, CRS_ICR_SYNCOKC);

    /* user callback */
    HAL_RCCEx_CRS_SyncOkCallback();
  }
  /* Check CRS SYNCWARN flag  */
  else if (((itflags & RCC_CRS_FLAG_SYNCWARN) != 0U) && ((itsources & RCC_CRS_IT_SYNCWARN) != 0U))
  {
    /* Clear CRS SYNCWARN flag */
    WRITE_REG(CRS->ICR, CRS_ICR_SYNCWARNC);

    /* user callback */
    HAL_RCCEx_CRS_SyncWarnCallback();
  }
  /* Check CRS Expected SYNC flag  */
  else if (((itflags & RCC_CRS_FLAG_ESYNC) != 0U) && ((itsources & RCC_CRS_IT_ESYNC) != 0U))
  {
    /* frequency error counter reached a zero value */
    WRITE_REG(CRS->ICR, CRS_ICR_ESYNCC);

    /* user callback */
    HAL_RCCEx_CRS_ExpectedSyncCallback();
  }
  /* Check CRS Error flags  */
  else
  {
    if (((itflags & RCC_CRS_FLAG_ERR) != 0U) && ((itsources & RCC_CRS_IT_ERR) != 0U))
    {
      if ((itflags & RCC_CRS_FLAG_SYNCERR) != 0U)
      {
        crserror |= RCC_CRS_SYNCERR;
      }
      if ((itflags & RCC_CRS_FLAG_SYNCMISS) != 0U)
      {
        crserror |= RCC_CRS_SYNCMISS;
      }
      if ((itflags & RCC_CRS_FLAG_TRIMOVF) != 0U)
      {
        crserror |= RCC_CRS_TRIMOVF;
      }

      /* Clear CRS Error flags */
      WRITE_REG(CRS->ICR, CRS_ICR_ERRC);

      /* user error callback */
      HAL_RCCEx_CRS_ErrorCallback(crserror);
    }
  }
}

/**
  * @brief  RCCEx Clock Recovery System SYNCOK interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_CRS_SyncOkCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_SyncOkCallback should be implemented in the user file
   */
}

/**
  * @brief  RCCEx Clock Recovery System SYNCWARN interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_CRS_SyncWarnCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_SyncWarnCallback should be implemented in the user file
   */
}

/**
  * @brief  RCCEx Clock Recovery System Expected SYNC interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_CRS_ExpectedSyncCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_ExpectedSyncCallback should be implemented in the user file
   */
}

/**
  * @brief  RCCEx Clock Recovery System Error interrupt callback.
  * @param  Error Combination of Error status.
  *         This parameter can be a combination of the following values:
  *           @arg @ref RCC_CRS_SYNCERR
  *           @arg @ref RCC_CRS_SYNCMISS
  *           @arg @ref RCC_CRS_TRIMOVF
  * @retval none
  */
__weak void HAL_RCCEx_CRS_ErrorCallback(uint32_t Error)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Error);

  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_ErrorCallback should be implemented in the user file
   */
}

/**
  * @}
  */

#endif /* CRS */

/** @addtogroup RCCEx_Private_Functions
  * @{
  */

static HAL_StatusTypeDef RCCEx_PLLSource_Enable(uint32_t PllSource)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  switch (PllSource)
  {
    case RCC_PLLSOURCE_MSI:
      /* Check whether MSI in not ready and enable it */
      if (READ_BIT(RCC->CR, RCC_CR_MSIRDY) == 0U)
      {
        /* Enable the Internal Multi Speed oscillator (MSI). */
        __HAL_RCC_MSI_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till MSI is ready */
        while (READ_BIT(RCC->CR, RCC_CR_MSIRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_MSI_TIMEOUT_VALUE)
          {
            status = HAL_TIMEOUT;
            break;
          }
        }
      }
      break;

    case RCC_PLLSOURCE_HSI:
      /* Check whether HSI in not ready and enable it */
      if (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
      {
        /* Enable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till MSI is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_HSI_TIMEOUT_VALUE)
          {
            status = HAL_TIMEOUT;
            break;
          }
        }
      }
      break;

    case RCC_PLLSOURCE_HSE:
      /* Check whether HSE in not ready and enable it */
      if (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0U)
      {
        /* Enable the External High Speed oscillator (HSE). */
        SET_BIT(RCC->CR, RCC_CR_HSEON);

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_HSE_TIMEOUT_VALUE)
          {
            status = HAL_TIMEOUT;
            break;
          }
        }
      }
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
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

#endif /* HAL_RCC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
