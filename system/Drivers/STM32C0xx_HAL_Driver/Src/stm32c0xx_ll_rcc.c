/**
  ******************************************************************************
  * @file    stm32c0xx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif
/** @addtogroup STM32C0xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @addtogroup RCC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_LL_Private_Macros
  * @{
  */

#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  ((__VALUE__) == LL_RCC_USART1_CLKSOURCE)
#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)     ((__VALUE__) == LL_RCC_I2C1_CLKSOURCE)
#define IS_LL_RCC_ADC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_ADC_CLKSOURCE))
#define IS_LL_RCC_I2S_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2S1_CLKSOURCE))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private functions
  * @{
  */
uint32_t RCC_GetSystemClockFreq(void);
uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency);
uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency);
uint32_t RCC_PLL_GetFreqDomain_SYS(void);
uint32_t RCC_PLL_GetFreqDomain_ADC(void);
uint32_t RCC_PLL_GetFreqDomain_I2S1(void);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_LL_Exported_Functions
  * @{
  */

/** @addtogroup RCC_LL_EF_Init
  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - HSI ON and used as system clock source
  *         - HSE OFF
  *         - AHB and APB1 prescaler set to 1.
  *         - CSS, MCO OFF
  *         - All interrupts disabled
  * @note   This function does not modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE and RTC clocks
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RCC_DeInit(void)
{
  /* Set HSION bit and wait for HSI READY bit */
  LL_RCC_HSI_Enable();
  while (LL_RCC_HSI_IsReady() != 1U)
  {}

  /* Set HSITRIM bits to reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x40U);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR, 0x00000000U);

  /* Reset whole CR register but HSI in 2 steps in case HSEBYP is set */
  LL_RCC_WriteReg(CR, RCC_CR_HSION);
  while (LL_RCC_HSE_IsReady() != 0U)
  {}
  LL_RCC_WriteReg(CR, RCC_CR_HSION);

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupts flags */
  LL_RCC_WriteReg(CICR, 0xFFFFFFFFU);

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB and APB1 buses clocks
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE divided by HSI division factor(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   (**) HSI_VALUE is a constant defined in this file (default value
  *              48 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (***) HSE_VALUE is a constant defined in this file (default value
  *               48 MHz), user has to ensure that HSE_VALUE is same as the real
  *               frequency of the crystal used. Otherwise, this function may
  *               have wrong result.
  * @note   The result of this function could be incorrect when using fractional
  *         value for HSE crystal.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @{
  */

/**
  * @brief  Return the frequencies of different on chip clocks;  System, AHB and APB1 buses clocks
  * @note   Each time SYSCLK, HCLK and/or PCLK1 clock changes, this function
  *         must be called to update structure fields. Otherwise, any
  *         configuration based on this function will be incorrect.
  * @param  RCC_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval None
  */
void LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks)
{
  /* Get SYSCLK frequency */
  RCC_Clocks->SYSCLK_Frequency = RCC_GetSystemClockFreq();

  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency   = RCC_GetHCLKClockFreq(RCC_Clocks->SYSCLK_Frequency);

  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency  = RCC_GetPCLK1ClockFreq(RCC_Clocks->HCLK_Frequency);
}

/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  * @retval USART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource)
{
  uint32_t usart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_USART_CLKSOURCE(USARTxSource));

  if (USARTxSource == LL_RCC_USART1_CLKSOURCE)
  {
    /* USART1CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART1_CLKSOURCE_SYSCLK: /* USART1 Clock is System Clock */
        usart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_USART1_CLKSOURCE_HSIKER:    /* USART1 Clock is HSI Kernel */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = (HSI_VALUE / ((LL_RCC_HSIKER_GetDivider() >> RCC_CR_HSIKERDIV_Pos) + 1U));
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_LSE:    /* USART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_PCLK1:  /* USART1 Clock is PCLK1 */
      default:
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  else
  {
  }
  return usart_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that HSI oscillator is not ready
  */
uint32_t LL_RCC_GetI2CClockFreq(uint32_t I2CxSource)
{
  uint32_t i2c_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_I2C_CLKSOURCE(I2CxSource));

  if (I2CxSource == LL_RCC_I2C1_CLKSOURCE)
  {
    /* I2C1 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C1_CLKSOURCE_SYSCLK: /* I2C1 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C1_CLKSOURCE_HSIKER:    /* I2C1 Clock is HSI Kernel */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = (HSI_VALUE / ((LL_RCC_HSIKER_GetDivider() >> RCC_CR_HSIKERDIV_Pos) + 1U));
        }
        break;

      case LL_RCC_I2C1_CLKSOURCE_PCLK1:  /* I2C1 Clock is PCLK1 */
      default:
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  else
  {
  }

  return i2c_frequency;
}

/**
  * @brief  Return I2Sx clock frequency
  * @param  I2SxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2S1_CLKSOURCE
  * @retval I2S clock frequency (in Hz)
  *         @arg @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetI2SClockFreq(uint32_t I2SxSource)
{
  uint32_t i2s_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_I2S_CLKSOURCE(I2SxSource));

  if (I2SxSource == LL_RCC_I2S1_CLKSOURCE)
  {
    /* I2S1 CLK clock frequency */
    switch (LL_RCC_GetI2SClockSource(I2SxSource))
    {
      case LL_RCC_I2S1_CLKSOURCE_HSIKER:    /* I2S1 Clock is HSI Kernel */
        i2s_frequency = (HSI_VALUE / ((LL_RCC_HSIKER_GetDivider() >> RCC_CR_HSIKERDIV_Pos) + 1U));
        break;

      case LL_RCC_I2S1_CLKSOURCE_PIN:          /* I2S1 Clock is External clock */
        i2s_frequency = EXTERNAL_CLOCK_VALUE;
        break;

      case LL_RCC_I2S1_CLKSOURCE_SYSCLK: /* I2S1 Clock is System Clock */
      default:
        i2s_frequency = RCC_GetSystemClockFreq();
        break;
    }
  }

  return i2s_frequency;
}

/**
  * @brief  Return ADCx clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI) is not ready
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NA indicates that no clock source selected
  */
uint32_t LL_RCC_GetADCClockFreq(uint32_t ADCxSource)
{
  uint32_t adc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADC_CLKSOURCE(ADCxSource));

  /* ADCCLK clock frequency */
  switch (LL_RCC_GetADCClockSource(ADCxSource))
  {
    case LL_RCC_ADC_CLKSOURCE_SYSCLK:        /* SYSCLK clock used as ADC clock source */
      adc_frequency = RCC_GetSystemClockFreq();
      break;
    case LL_RCC_ADC_CLKSOURCE_HSIKER  :        /* HSI clock Kernel used as ADC clock source */
      adc_frequency = (HSI_VALUE / ((LL_RCC_HSIKER_GetDivider() >> RCC_CR_HSIKERDIV_Pos) + 1U));
      break;
    default:
      adc_frequency = LL_RCC_PERIPH_FREQUENCY_NA;
      break;
  }

  return adc_frequency;
}

/**
  * @brief  Return RTC clock frequency
  * @retval RTC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillators (LSI, LSE or HSE) are not ready
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NA indicates that no clock source selected
  */
uint32_t LL_RCC_GetRTCClockFreq(void)
{
  uint32_t rtc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* RTCCLK clock frequency */
  switch (LL_RCC_GetRTCClockSource())
  {
    case LL_RCC_RTC_CLKSOURCE_LSE:       /* LSE clock used as RTC clock source */
      if (LL_RCC_LSE_IsReady() == 1U)
      {
        rtc_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_LSI:       /* LSI clock used as RTC clock source */
      if (LL_RCC_LSI_IsReady() == 1U)
      {
        rtc_frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_HSE_DIV32:        /* HSE clock used as ADC clock source */
      rtc_frequency = HSE_VALUE / 32U;
      break;

    case LL_RCC_RTC_CLKSOURCE_NONE:          /* No clock used as RTC clock source */
    default:
      rtc_frequency = LL_RCC_PERIPH_FREQUENCY_NA;
      break;
  }

  return rtc_frequency;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup RCC_LL_Private_Functions
  * @{
  */

/**
  * @brief  Return SYSTEM clock frequency
  * @retval SYSTEM clock frequency (in Hz)
  */
uint32_t RCC_GetSystemClockFreq(void)
{
  uint32_t frequency;
  uint32_t hsidiv;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (LL_RCC_GetSysClkSource())
  {
    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:  /* HSE used as system clock  source */
      frequency = HSE_VALUE;
      break;
    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:  /* HSI used as system clock  source */
    default:
      hsidiv = (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >> RCC_CR_HSIDIV_Pos));
      frequency = (HSI_VALUE / hsidiv);
      break;
  }

  return frequency;
}

/**
  * @brief  Return HCLK clock frequency
  * @param  SYSCLK_Frequency SYSCLK clock frequency
  * @retval HCLK clock frequency (in Hz)
  */
uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency)
{
  /* HCLK clock frequency */
  return __LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, LL_RCC_GetAHBPrescaler());
}

/**
  * @brief  Return PCLK1 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK1 clock frequency (in Hz)
  */
uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK1 clock frequency */
  return __LL_RCC_CALC_PCLK1_FREQ(HCLK_Frequency, LL_RCC_GetAPB1Prescaler());
}

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

#endif /* USE_FULL_LL_DRIVER */
