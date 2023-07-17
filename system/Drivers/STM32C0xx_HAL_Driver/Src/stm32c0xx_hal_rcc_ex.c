/**
  ******************************************************************************
  * @file    stm32c0xx_hal_rcc_ex.c
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
#include "stm32c0xx_hal.h"

/** @addtogroup STM32C0xx_HAL_Driver
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
#define LSCO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO_GPIO_PORT        GPIOA
#define LSCO_PIN              GPIO_PIN_2
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
    [..]
    (@) Important note: Care must be taken when @ref HAL_RCCEx_PeriphCLKConfig() is used to
        select the RTC clock source; as consequence RTC registers and RCC_CSR1 register are
        set to their reset values.

@endverbatim
  * @{
  */
/**
  * @brief  Initialize the RCC extended peripherals clocks according to the specified
  *         parameters in the @ref RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit  pointer to a @ref RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *            @arg @ref RCC_PERIPHCLK_RTC  RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC    ADC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1   I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2S1   I2S1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART1 USART1 peripheral clock
  * @note   Care must be taken when @ref HAL_RCCEx_PeriphCLKConfig() is used to select
  *         the RTC clock source: in this case the access to RTC domain is enabled.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tmpregister;
  uint32_t tickstart;
  HAL_StatusTypeDef ret    = HAL_OK;   /* Intermediate status */
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


    /* Reset the RTC domain only if the RTC Clock source selection is modified from default */
    tmpregister = READ_BIT(RCC->CSR1, RCC_CSR1_RTCSEL);

    /* Reset the RTC domain only if the RTC Clock source selection is modified */
    if ((tmpregister != RCC_RTCCLKSOURCE_NONE) && (tmpregister != PeriphClkInit->RTCClockSelection))
    {
      /* Store the content of CSR1 register before the reset of RTC Domain */
      tmpregister = READ_BIT(RCC->CSR1, ~(RCC_CSR1_RTCSEL));
      /* RTC Clock selection can be changed only if the RTC Domain is reset */
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();
      /* Restore the Content of CSR1 register */
      RCC->CSR1 = tmpregister;
    }

    /* Wait for LSE reactivation if LSE was enable prior to RTC Domain reset */
    if (HAL_IS_BIT_SET(tmpregister, RCC_CSR1_LSEON))
    {
      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is ready */
      while (READ_BIT(RCC->CSR1, RCC_CSR1_LSERDY) == 0U)
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

  /*-------------------------- I2C1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));

    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }

  /*-------------------------- ADC clock source configuration ----------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC) == RCC_PERIPHCLK_ADC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCCLKSOURCE(PeriphClkInit->AdcClockSelection));

    /* Configure the ADC interface clock source */
    __HAL_RCC_ADC_CONFIG(PeriphClkInit->AdcClockSelection);

  }

  /*-------------------------- I2S1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S1) == RCC_PERIPHCLK_I2S1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2S1CLKSOURCE(PeriphClkInit->I2s1ClockSelection));

    /* Configure the I2S1 clock source */
    __HAL_RCC_I2S1_CONFIG(PeriphClkInit->I2s1ClockSelection);
  }
  /*------------------------------------ HSI Kernel clock source configuration --------------------------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_HSIKER) == RCC_PERIPHCLK_HSIKER)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSIKERDIV(PeriphClkInit->HSIKerClockDivider));

    /* Configure the HSI Kernel clock source Divider */
    __HAL_RCC_HSIKER_CONFIG(PeriphClkInit->HSIKerClockDivider);
  }
  return status;
}

/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks: I2C1, I2S1, USART1, RTC, ADC,
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2S1 | \
                                        RCC_PERIPHCLK_ADC    | RCC_PERIPHCLK_RTC  | RCC_PERIPHCLK_HSIKER ;


  /* Get the USART1 clock source ---------------------------------------------*/
  PeriphClkInit->Usart1ClockSelection  = __HAL_RCC_GET_USART1_SOURCE();

  /* Get the I2C1 clock source -----------------------------------------------*/
  PeriphClkInit->I2c1ClockSelection    = __HAL_RCC_GET_I2C1_SOURCE();

  /* Get the RTC clock source ------------------------------------------------*/
  PeriphClkInit->RTCClockSelection     = __HAL_RCC_GET_RTC_SOURCE();

  /* Get the ADC clock source -----------------------------------------------*/
  PeriphClkInit->AdcClockSelection     = __HAL_RCC_GET_ADC_SOURCE();

  /* Get the I2S1 clock source -----------------------------------------------*/
  PeriphClkInit->I2s1ClockSelection    = __HAL_RCC_GET_I2S1_SOURCE();

  /* Get the HSI Kernel clock divider -----------------------------------------------*/
  PeriphClkInit->HSIKerClockDivider    = __HAL_RCC_GET_HSIKER_DIVIDER();
}

/**
  * @brief  Return the peripheral clock frequency for peripherals
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_RTC     RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC     ADC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1    I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2S1    I2S1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART1  USART1 peripheral clock
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

  if (PeriphClk == RCC_PERIPHCLK_RTC)
  {
    /* Get the current RTC source */
    srcclk = __HAL_RCC_GET_RTC_SOURCE();

    /* Check if LSE is ready and if RTC clock selection is LSE */
    if ((HAL_IS_BIT_SET(RCC->CSR1, RCC_CSR1_LSERDY)) && (srcclk == RCC_RTCCLKSOURCE_LSE))
    {
      frequency = LSE_VALUE;
    }
    /* Check if LSI is ready and if RTC clock selection is LSI */
    else if ((HAL_IS_BIT_SET(RCC->CSR2, RCC_CSR2_LSIRDY)) && (srcclk == RCC_RTCCLKSOURCE_LSI))
    {
      frequency = LSI_VALUE;
    }
    /* Check if HSE is ready  and if RTC clock selection is HSI_DIV32*/
    else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) && (srcclk == RCC_RTCCLKSOURCE_HSE_DIV32))
    {
      frequency = HSE_VALUE / 32U;
    }
    /* Clock not enabled for RTC*/
    else
    {
      /* Nothing to do as frequency already initialized to 0U */
    }
  }
  else
  {
    /* Other external peripheral clock source than RTC */

    switch (PeriphClk)
    {

      case RCC_PERIPHCLK_USART1:
        /* Get the current USART1 source */
        srcclk = __HAL_RCC_GET_USART1_SOURCE();

        if (srcclk == RCC_USART1CLKSOURCE_PCLK1)            /* PCLK1 */
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_USART1CLKSOURCE_SYSCLK)     /* SYSCLK  */
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_USART1CLKSOURCE_HSIKER))
        {
          frequency = (HSI_VALUE / ((__HAL_RCC_GET_HSIKER_DIVIDER() >> RCC_CR_HSIKERDIV_Pos) + 1U));
        }
        else if ((HAL_IS_BIT_SET(RCC->CSR1, RCC_CSR1_LSERDY)) && (srcclk == RCC_USART1CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for USART1 */
        else
        {
          /* Nothing to do as frequency already initialized to 0U */
        }
        break;

      case RCC_PERIPHCLK_ADC:

        srcclk = __HAL_RCC_GET_ADC_SOURCE();

        if (srcclk == RCC_ADCCLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_ADCCLKSOURCE_HSIKER))
        {
          frequency = (HSI_VALUE / ((__HAL_RCC_GET_HSIKER_DIVIDER() >> RCC_CR_HSIKERDIV_Pos) + 1U));
        }
        /* Clock not enabled for ADC */
        else
        {
          /* Nothing to do as frequency already initialized to 0U */
        }
        break;

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
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C1CLKSOURCE_HSIKER))
        {
          frequency = (HSI_VALUE / ((__HAL_RCC_GET_HSIKER_DIVIDER() >> RCC_CR_HSIKERDIV_Pos) + 1U));
        }
        /* Clock not enabled for I2C1 */
        else
        {
          /* Nothing to do as frequency already initialized to 0U */
        }
        break;

      case RCC_PERIPHCLK_I2S1:
        /* Get the current I2S1 source */
        srcclk = __HAL_RCC_GET_I2S1_SOURCE();

        if (srcclk == RCC_I2S1CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2S1CLKSOURCE_HSIKER))
        {
          frequency = (HSI_VALUE / ((__HAL_RCC_GET_HSIKER_DIVIDER() >> RCC_CR_HSIKERDIV_Pos) + 1U));
        }
        else if (srcclk == RCC_I2S1CLKSOURCE_EXT)
        {
          /* External clock used.*/
          frequency = EXTERNAL_I2S1_CLOCK_VALUE;
        }
        /* Clock not enabled for I2S1 */
        else
        {
          /* Nothing to do as frequency already initialized to 0U */
        }
        break;

      default:
        break;
    }
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
    activation or deactivation of LSE CSS, Low speed clock output and
    clock after wake-up from STOP mode.
@endverbatim
  * @{
  */

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
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* LSCO Pin Clock Enable */
  LSCO_CLK_ENABLE();

  /* configure the LSCO pin in analog mode */
  GPIO_InitStruct.Pin = LSCO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LSCO_GPIO_PORT, &GPIO_InitStruct);

  MODIFY_REG(RCC->CSR1, RCC_CSR1_LSCOSEL | RCC_CSR1_LSCOEN, LSCOSource | RCC_CSR1_LSCOEN);

}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{

  CLEAR_BIT(RCC->CSR1, RCC_CSR1_LSCOEN);

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
