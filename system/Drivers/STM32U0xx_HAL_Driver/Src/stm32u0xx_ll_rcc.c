/**
  ******************************************************************************
  * @file    stm32u0xx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_LL_DRIVER */
/** @addtogroup STM32U0xx_LL_Driver
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
#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART3_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART4_CLKSOURCE))
#if defined (LPUART3)
#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPUART2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPUART3_CLKSOURCE))
#else
#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPUART2_CLKSOURCE))
#endif /* LPUART3 */
#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C3_CLKSOURCE))
#if defined (LPTIM3)
#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM3_CLKSOURCE))
#else
#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE))
#endif /* LPTIM3 */
#define IS_LL_RCC_TIM_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_TIM1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_TIM15_CLKSOURCE))

#define IS_LL_RCC_RNG_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_RNG_CLKSOURCE))
#if defined (USB)
#define IS_LL_RCC_USB_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_USB_CLKSOURCE))
#endif /* USB */
#define IS_LL_RCC_ADC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_ADC_CLKSOURCE))


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
uint32_t RCC_PLL_GetFreqDomain_PLLP(void);
uint32_t RCC_PLL_GetFreqDomain_PLLQ(void);
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
  *         - MSI  ON and used as system clock source
  *         - HSE, HSI, PLL and PLLSAIxSource OFF
  *         - AHB, APB prescaler set to 1.
  *         - CSS, MCO OFF
  *         - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE and RTC clocks
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RCC_DeInit(void)
{
  uint32_t vl_mask = 0U;

  /* Set MSION bit */
  LL_RCC_MSI_Enable();

  /* Insure MSIRDY bit is set before writing default MSIRANGE value */
  while (LL_RCC_MSI_IsReady() == 0U)
  {
    __NOP();
  }

  /* Set MSIRANGE default value */
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
  /* Set MSITRIM bits to the reset value*/
  LL_RCC_MSI_SetCalibTrimming(0);

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x10U);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR, 0x00000000U);

  vl_mask = 0xFFFFFFFFU;
#if defined(RCC_CRRCR_HSI48ON)
  /* Reset HSION, HSIKERON, HSIASFS, HSEON, PLLSYSON bits */
  CLEAR_BIT(vl_mask, (RCC_CR_HSION | RCC_CR_HSIKERON  | RCC_CR_HSEON | RCC_CRRCR_HSI48ON |
                      RCC_CR_PLLON));
#else
  CLEAR_BIT(vl_mask, (RCC_CR_HSION | RCC_CR_HSIKERON  | RCC_CR_HSEON | RCC_CR_PLLON));
#endif /* RCC_CRRCR_HSI48ON */
  /* Write new mask in CR register */
  LL_RCC_WriteReg(CR, vl_mask);

  /* Reset PLLCFGR register */
  LL_RCC_WriteReg(PLLCFGR, 16U << RCC_PLLCFGR_PLLN_Pos);

  /* Reset HSEBYP bit */
  LL_RCC_HSE_DisableBypass();

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB buses clocks
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is MSI, function returns values based on MSI_VALUE(*)
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   If SYSCLK source is PLL, function returns values based on HSE_VALUE(***)
  *         or HSI_VALUE(**) or MSI_VALUE(*) multiplied/divided by the PLL factors.
  * @note   (*) MSI_VALUE is a constant defined in this file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  * @note   (**) HSI_VALUE is a constant defined in this file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (***) HSE_VALUE is a constant defined in this file (default value
  *               8 MHz), user has to ensure that HSE_VALUE is same as the real
  *               frequency of the crystal used. Otherwise, this function may
  *               have wrong result.
  * @note   The result of this function could be incorrect when using fractional
  *         value for HSE crystal.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @{
  */

/**
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB buses clocks
  * @note   Each time SYSCLK, HCLK, PCLK1 and/or PCLK2 clock changes, this function
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
  RCC_Clocks->HCLK_Frequency = RCC_GetHCLKClockFreq(RCC_Clocks->SYSCLK_Frequency);

  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_GetPCLK1ClockFreq(RCC_Clocks->HCLK_Frequency);

}

/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE
  *         @arg @ref LL_RCC_USART4_CLKSOURCE
  *
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

      case LL_RCC_USART1_CLKSOURCE_HSI:    /* USART1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_LSE:    /* USART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady())
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_PCLK1:  /* USART1 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }
  else if (USARTxSource == LL_RCC_USART2_CLKSOURCE)
  {
    /* USART2CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART2_CLKSOURCE_SYSCLK: /* USART2 Clock is System Clock */
        usart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_USART2_CLKSOURCE_HSI:    /* USART2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_LSE:    /* USART2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady())
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_PCLK1:  /* USART2 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }
  else if ((USARTxSource == LL_RCC_USART3_CLKSOURCE) || (USARTxSource == LL_RCC_USART4_CLKSOURCE))
  {
    /* USART3 or USART4 clock frequency : PCLK */
    usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
  }
  return usart_frequency;
}

/**
  * @brief  Return TIMx clock frequency
  * @param  TIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_TIM1_CLKSOURCE
  *         @arg @ref LL_RCC_TIM15_CLKSOURCE
  *
  *         (*) value not defined in all devices.
  * @retval USART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t LL_RCC_GetTIMClockFreq(uint32_t TIMxSource)
{
  uint32_t tim_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_TIM_CLKSOURCE(TIMxSource));

  if (TIMxSource == LL_RCC_TIM1_CLKSOURCE)
  {
    /* TIM1CLK clock frequency */
    switch (LL_RCC_GetTIMClockSource(TIMxSource))
    {
      case LL_RCC_TIM1_CLKSOURCE_PCLK1: /* TIM1 Clock is System Clock */
        if (LL_RCC_GetAPB1Prescaler() == LL_RCC_APB1_DIV_1)
        {
          tim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        }
        else
        {
          tim_frequency = 2 * (RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq())));
        }
        break;

      case LL_RCC_TIM1_CLKSOURCE_PLLQ: /* TIM1 Clock is PLLQ Osc. */
        if (LL_RCC_PLL_IsReady())
        {
          tim_frequency = RCC_PLL_GetFreqDomain_PLLQ();
        }
        break;

      default:
        break;
    }
  }
  else if (TIMxSource == LL_RCC_TIM15_CLKSOURCE)
  {
    switch (LL_RCC_GetTIMClockSource(TIMxSource))
    {
      case LL_RCC_TIM15_CLKSOURCE_PCLK1: /* TIM15 Clock is System Clock */
        if (LL_RCC_GetAPB1Prescaler() == LL_RCC_APB1_DIV_1)
        {
          tim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        }
        else
        {
          tim_frequency = 2 * (RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq())));
        }
        break;

      case LL_RCC_TIM15_CLKSOURCE_PLLQ: /* TIM15 Clock is PLLQ Osc. */
        if (LL_RCC_PLL_IsReady())
        {
          tim_frequency = RCC_PLL_GetFreqDomain_PLLQ();
        }
        break;

      default:
        break;
    }
  }
  return tim_frequency;
}

/**
  * @brief  Return LPUARTx clock frequency
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval LPUART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource)
{
  uint32_t lpuart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPUART_CLKSOURCE(LPUARTxSource));

  if (LPUARTxSource == LL_RCC_LPUART1_CLKSOURCE)
  {
    /* LPUART1CLK clock frequency */
    switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
    {
      case LL_RCC_LPUART1_CLKSOURCE_SYSCLK: /* LPUART1 Clock is System Clock */
        lpuart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_LPUART1_CLKSOURCE_PCLK1:  /* LPUART1 Clock is PCLK1 */
        lpuart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_LPUART1_CLKSOURCE_HSI:    /* LPUART1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          lpuart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPUART1_CLKSOURCE_LSE:    /* LPUART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1)
        {
          lpuart_frequency = LSE_VALUE;
        }
        break;

      default:
        break;
    }
  }
  else if (LPUARTxSource == LL_RCC_LPUART2_CLKSOURCE)
  {
    /* LPUART1CLK clock frequency */
    switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
    {
      case LL_RCC_LPUART2_CLKSOURCE_SYSCLK: /* LPUART1 Clock is System Clock */
        lpuart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_LPUART2_CLKSOURCE_HSI:    /* LPUART1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          lpuart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPUART2_CLKSOURCE_LSE:    /* LPUART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady())
        {
          lpuart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPUART2_CLKSOURCE_PCLK1:  /* LPUART1 Clock is PCLK1 */
        lpuart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }
#if defined (LPUART3)
  else if (LPUARTxSource == LL_RCC_LPUART3_CLKSOURCE)
  {
    /* LPUART1CLK clock frequency */
    switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
    {
      case LL_RCC_LPUART3_CLKSOURCE_SYSCLK: /* LPUART1 Clock is System Clock */
        lpuart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_LPUART3_CLKSOURCE_HSI:    /* LPUART1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          lpuart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPUART3_CLKSOURCE_LSE:    /* LPUART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady())
        {
          lpuart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPUART3_CLKSOURCE_PCLK1:  /* LPUART1 Clock is PCLK1 */
        lpuart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }
#endif /* LPUART3 */
  return lpuart_frequency;
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
        if (READ_BIT(RCC->CSR, RCC_CSR_LSIPREDIV) == RCC_CSR_LSIPREDIV)
        {
          rtc_frequency = LSI_VALUE / 128U;
        }
        else
        {
          rtc_frequency = LSI_VALUE;
        }
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_HSE_DIV32:        /* HSE clock used as ADC clock source */
      rtc_frequency = HSE_VALUE / 32U;
      break;

    case LL_RCC_RTC_CLKSOURCE_NONE:          /* No clock used as RTC clock source */
      rtc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
      break;

    default:
      break;
  }

  return rtc_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  *
  *         (*) value not defined in all devices.
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

      case LL_RCC_I2C1_CLKSOURCE_HSI:    /* I2C1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C1_CLKSOURCE_PCLK1:  /* I2C1 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }
  else if (I2CxSource == LL_RCC_I2C3_CLKSOURCE)
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C3_CLKSOURCE_SYSCLK: /* I2C3 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C3_CLKSOURCE_HSI:    /* I2C3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C3_CLKSOURCE_PCLK1:  /* I2C3 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }

  return i2c_frequency;
}

/**
  * @brief  Return LPTIMx clock frequency
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE (*)
  *
  *         (*) value not defined in all devices.
  * @retval LPTIM clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI, LSI or LSE) is not ready
  */
uint32_t LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource)
{
  uint32_t lptim_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPTIM_CLKSOURCE(LPTIMxSource));

  if (LPTIMxSource == LL_RCC_LPTIM1_CLKSOURCE)
  {
    /* LPTIM1CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM1_CLKSOURCE_LSI:    /* LPTIM1 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          if (READ_BIT(RCC->CSR, RCC_CSR_LSIPREDIV) == RCC_CSR_LSIPREDIV)
          {
            lptim_frequency = LSI_VALUE / 128U;
          }
          else
          {
            lptim_frequency = LSI_VALUE;
          }
        }
        break;
      case LL_RCC_LPTIM1_CLKSOURCE_HSI:    /* LPTIM1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_LSE:    /* LPTIM1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady())
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_PCLK1:  /* LPTIM1 Clock is PCLK1 */
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }
  else if (LPTIMxSource == LL_RCC_LPTIM2_CLKSOURCE)
  {
    /* LPTIM2CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM2_CLKSOURCE_LSI:    /* LPTIM2 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          if (READ_BIT(RCC->CSR, RCC_CSR_LSIPREDIV) == RCC_CSR_LSIPREDIV)
          {
            lptim_frequency = LSI_VALUE / 128U;
          }
          else
          {
            lptim_frequency = LSI_VALUE;
          }
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_HSI:    /* LPTIM2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady())
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_LSE:    /* LPTIM2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady())
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_PCLK1:  /* LPTIM2 Clock is PCLK1 */
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        break;
    }
  }
#if defined (LPTIM3)
  else
  {
    if (LPTIMxSource == LL_RCC_LPTIM3_CLKSOURCE)
    {
      /* LPTIM2CLK clock frequency */
      switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
      {
        case LL_RCC_LPTIM3_CLKSOURCE_LSI:    /* LPTIM3 Clock is LSI Osc. */
          if (LL_RCC_LSI_IsReady() == 1U)
          {
            if (READ_BIT(RCC->CSR, RCC_CSR_LSIPREDIV) == RCC_CSR_LSIPREDIV)
            {
              lptim_frequency = LSI_VALUE / 128U;
            }
            else
            {
              lptim_frequency = LSI_VALUE;
            }
          }
          break;

        case LL_RCC_LPTIM3_CLKSOURCE_HSI:    /* LPTIM3 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady())
          {
            lptim_frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_LPTIM3_CLKSOURCE_LSE:    /* LPTIM3 Clock is LSE Osc. */
          if (LL_RCC_LSE_IsReady())
          {
            lptim_frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_LPTIM3_CLKSOURCE_PCLK1:  /* LPTIM3 Clock is PCLK1 */
          lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
          break;

        default:
          break;
      }
    }
  }
#endif /* LPTIM3 */
  return lptim_frequency;
}

/**
  * @brief  Return RNGx clock frequency
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval RNG clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI) or PLL is not ready
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NA indicates that no clock source selected
  */
uint32_t LL_RCC_GetRNGClockFreq(uint32_t RNGxSource)
{
  uint32_t rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_RNG_CLKSOURCE(RNGxSource));

  /* RNGCLK clock frequency */
  switch (LL_RCC_GetRNGClockSource(RNGxSource))
  {
    case LL_RCC_RNG_CLKSOURCE_PLLQ:           /* PLL clock used as RNG clock source */
      if (LL_RCC_PLL_IsReady())
      {
        rng_frequency = RCC_PLL_GetFreqDomain_PLLQ();
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_MSI:           /* MSI clock used as RNG clock source */
      if (LL_RCC_MSI_IsReady())
      {
        rng_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               (LL_RCC_MSI_IsEnabledRangeSelect() ?
                                                LL_RCC_MSI_GetRange() :
                                                LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_NONE:          /* No clock used as RNG clock source */
      rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
      break;

    default:
      break;

  }

  return rng_frequency;
}

#if defined (USB)
/**
  * @brief  Return USBx clock frequency
  * @param  USBxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE
  * @retval USB clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI) or PLL is not ready
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NA indicates that no clock source selected
  */
uint32_t LL_RCC_GetUSBClockFreq(uint32_t USBxSource)
{
  uint32_t usb_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_USB_CLKSOURCE(USBxSource));

  /* USBCLK clock frequency */
  switch (LL_RCC_GetUSBClockSource(USBxSource))
  {
    case LL_RCC_USB_CLKSOURCE_PLLQ:           /* PLL clock used as USB clock source */
      if (LL_RCC_PLL_IsReady())
      {
        usb_frequency = RCC_PLL_GetFreqDomain_PLLQ();
      }
      break;

    case LL_RCC_USB_CLKSOURCE_MSI:           /* MSI clock used as USB clock source */
      if (LL_RCC_MSI_IsReady())
      {
        usb_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               (LL_RCC_MSI_IsEnabledRangeSelect() ?
                                                LL_RCC_MSI_GetRange() :
                                                LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_USB_CLKSOURCE_NONE:          /* No clock used as USB clock source */
      usb_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
      break;

    default:
      break;
  }

  return usb_frequency;
}
#endif /* USB */
/**
  * @brief  Return ADCx clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI) or PLL is not ready
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
    case LL_RCC_ADC_CLKSOURCE_HSI:    /* ADC Clock is HSI Osc. */
      if (LL_RCC_HSI_IsReady())
      {
        adc_frequency = HSI_VALUE;
      }
      break;
    case LL_RCC_ADC_CLKSOURCE_PLLP:    /* ADC Clock is HSI Osc. */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        if (LL_RCC_PLL_IsEnabledDomain_PLLP() == 1U)
        {
          adc_frequency = RCC_PLL_GetFreqDomain_PLLP();
        }
      }
      break;
    case LL_RCC_ADC_CLKSOURCE_NONE:          /* No clock used as ADC clock source */
      adc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
      break;

    default:
      break;
  }

  return adc_frequency;
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
  uint32_t frequency = 0U;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (LL_RCC_GetSysClkSource())
  {
    case LL_RCC_SYS_CLKSOURCE_STATUS_MSI:  /* MSI used as system clock source */
      frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                         (LL_RCC_MSI_IsEnabledRangeSelect() ?
                                          LL_RCC_MSI_GetRange() :
                                          LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:  /* HSI used as system clock  source */
      frequency = HSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:  /* HSE used as system clock  source */
      frequency = HSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_LSI:  /* LSI used as system clock  source */
      if (READ_BIT(RCC->CSR, RCC_CSR_LSIPREDIV) == RCC_CSR_LSIPREDIV)
      {
        frequency = LSI_VALUE / 128U;
      }
      else
      {
        frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_LSE:  /* LSE used as system clock  source */
      frequency = LSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_PLL:  /* PLL used as system clock  source */
      frequency = RCC_PLL_GetFreqDomain_SYS();
      break;

    default:
      frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                         (LL_RCC_MSI_IsEnabledRangeSelect() ?
                                          LL_RCC_MSI_GetRange() :
                                          LL_RCC_MSI_GetRangeAfterStandby()));
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
  * @brief  Return PLLR clock frequency used for system domain
  * @retval PLL clock frequency (in Hz)
  */
uint32_t RCC_PLL_GetFreqDomain_SYS(void)
{
  uint32_t pllinputfreq = 0U;
  uint32_t pllsource = 0U;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
     SYSCLK = PLL_VCO / PLLR
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            (LL_RCC_MSI_IsEnabledRangeSelect() ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = 0U;
      break;
  }
  return __LL_RCC_CALC_PLLCLK_R_FREQ(pllinputfreq, LL_RCC_PLL_GetM(),
                                     LL_RCC_PLL_GetN(), LL_RCC_PLL_GetR());
}

/**
  * @brief  Return PLLP clock frequency used for ADC domain
  * @retval PLL clock frequency (in Hz)
  */
uint32_t RCC_PLL_GetFreqDomain_PLLP(void)
{
  uint32_t pllinputfreq = 0U;
  uint32_t pllsource = 0U;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
     PLLP clock = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            (LL_RCC_MSI_IsEnabledRangeSelect() ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    default:
      pllinputfreq = 0U;
      break;
  }
  return __LL_RCC_CALC_PLLCLK_P_FREQ(pllinputfreq, LL_RCC_PLL_GetM(),
                                     LL_RCC_PLL_GetN(), LL_RCC_PLL_GetP());
}

/**
  * @brief  Return PLLQ clock frequency used for 48 MHz domain
  * @retval PLL clock frequency (in Hz)
  */
uint32_t RCC_PLL_GetFreqDomain_PLLQ(void)
{
  uint32_t pllinputfreq = 0U;
  uint32_t pllsource = 0U;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
     PLLQ clock = PLL_VCO / PLLQ
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            (LL_RCC_MSI_IsEnabledRangeSelect() ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = 0U;
      break;
  }
  return __LL_RCC_CALC_PLLCLK_Q_FREQ(pllinputfreq, LL_RCC_PLL_GetM(),
                                     LL_RCC_PLL_GetN(), LL_RCC_PLL_GetQ());
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
