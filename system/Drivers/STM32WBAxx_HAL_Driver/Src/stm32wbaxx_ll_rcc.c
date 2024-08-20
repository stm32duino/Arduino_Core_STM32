/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 20223 STMicroelectronics.
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
#include "stm32wbaxx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif
/** @addtogroup STM32WBAxx_LL_Driver
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
#if defined(USART2)
#define IS_LL_RCC_USART2_CLKSOURCE(__VALUE__) ((__VALUE__) == LL_RCC_USART2_CLKSOURCE)
#else
#define IS_LL_RCC_USART2_CLKSOURCE(__VALUE__) (0)
#endif

#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) \
                                               || IS_LL_RCC_USART2_CLKSOURCE(__VALUE__))

#if defined(I2C1)
#define IS_LL_RCC_I2C1_CLKSOURCE(__VALUE__) ((__VALUE__) == LL_RCC_I2C1_CLKSOURCE)
#else
#define IS_LL_RCC_I2C1_CLKSOURCE(__VALUE__) (0)
#endif

#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_I2C3_CLKSOURCE) \
                                             || IS_LL_RCC_I2C1_CLKSOURCE(__VALUE__))

#if defined(SPI1)
#define IS_LL_RCC_SPI1_CLKSOURCE(__VALUE__) ((__VALUE__) == LL_RCC_SPI1_CLKSOURCE)
#else
#define IS_LL_RCC_SPI1_CLKSOURCE(__VALUE__) (0)
#endif

#define IS_LL_RCC_SPI_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_SPI3_CLKSOURCE) \
                                             || IS_LL_RCC_SPI1_CLKSOURCE(__VALUE__))

#if defined(LPTIM2)
#define IS_LL_RCC_LPTIM2_CLKSOURCE(__VALUE__) ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE)
#else
#define IS_LL_RCC_LPTIM2_CLKSOURCE(__VALUE__) (0)
#endif

#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) \
                                               || IS_LL_RCC_LPTIM2_CLKSOURCE(__VALUE__))

#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__) ((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE)

#if defined(SAI1)
#define IS_LL_RCC_SAI_CLKSOURCE(__VALUE__)    ((__VALUE__) == LL_RCC_SAI1_CLKSOURCE)
#endif /* SAI1 */

#define IS_LL_RCC_RNG_CLKSOURCE(__VALUE__)    ((__VALUE__) == LL_RCC_RNG_CLKSOURCE)

#define IS_LL_RCC_ADC_CLKSOURCE(__VALUE__)    ((__VALUE__) == LL_RCC_ADC_CLKSOURCE)

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
uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency);
uint32_t RCC_GetPCLK7ClockFreq(uint32_t HCLK_Frequency);
uint32_t RCC_PLL1R_GetFreqDomain(void);
uint32_t RCC_PLL1P_GetFreqDomain(void);
uint32_t RCC_PLL1Q_GetFreqDomain(void);
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
  *         - HSE, HSI, PLL1, PLL2 and PLL3 OFF
  *         - AHB, APB1, APB2 and APB3 prescaler set to 1.
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
  uint32_t vl_mask;

  /* Set HSION bit */
  LL_RCC_HSI_Enable();

  /* Insure HSIRDY bit is set */
  while (LL_RCC_HSI_IsReady() == 0U)
  {
  }

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x20U);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR1, 0x00000000U);
  LL_RCC_WriteReg(CFGR2, 0x00000000U);

  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Read CR register */
  vl_mask = LL_RCC_ReadReg(CR);

  /* Reset HSION, HSIKERON, HSEON and PLL1ON bits */
  CLEAR_BIT(vl_mask, (RCC_CR_HSION | RCC_CR_HSIKERON  | RCC_CR_HSEON | RCC_CR_PLL1ON));

  /* Write new mask in CR register */
  LL_RCC_WriteReg(CR, vl_mask);

  /* Wait for PLL1RDY, PLL2RDY and PLL3RDY bits to be reset */
  while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY) != 0U)
  {
  }

  /* Reset PLL1CFGR register */
  LL_RCC_WriteReg(PLL1CFGR, 0x0U);

  /* Reset PLL1DIVR register */
  LL_RCC_WriteReg(PLL1DIVR, 0x01010280U);

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupt flags */
#if defined(RCC_LSI2_SUPPORT)
  vl_mask = RCC_CICR_LSI1RDYC | RCC_CICR_LSI2RDYC | RCC_CICR_LSERDYC  | RCC_CICR_HSIRDYC | \
            RCC_CICR_HSERDYC  | RCC_CICR_PLL1RDYC | RCC_CICR_HSECSSC;
#else
  vl_mask = RCC_CICR_LSI1RDYC |                     RCC_CICR_LSERDYC  | RCC_CICR_HSIRDYC | \
            RCC_CICR_HSERDYC  | RCC_CICR_PLL1RDYC | RCC_CICR_HSECSSC;
#endif
  LL_RCC_WriteReg(CICR, vl_mask);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Reset secure configuration */
  LL_RCC_ConfigSecure(LL_RCC_ALL_NSEC);
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3U) */

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1 and APB2 buses clocks
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   If SYSCLK source is PLL1, function returns values based on HSE_VALUE(***)
  *         or HSI_VALUE(**) multiplied/divided by the PLL1 factors.
  * @note   (**) HSI_VALUE is a constant defined in this file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (***) HSE_VALUE is a constant defined in this file (default value
  *               32 MHz), user has to ensure that HSE_VALUE is same as the real
  *               frequency of the crystal used. Otherwise, this function may
  *               have wrong result.
  * @note   The result of this function could be incorrect when using fractional
  *         value for HSE crystal.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @{
  */

/**
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1 and APB2 buses clocks
  * @note   Each time SYSCLK, HCLK and/or PCLK1, PCLK2 and/or PCLK7 clock changes, this function
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

  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency  = RCC_GetPCLK2ClockFreq(RCC_Clocks->HCLK_Frequency);

  /* PCLK7 clock frequency */
  RCC_Clocks->PCLK7_Frequency  = RCC_GetPCLK7ClockFreq(RCC_Clocks->HCLK_Frequency);
}

/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
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
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_LSE:    /* USART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() != 0U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_PCLK2:  /* USART1 Clock is PCLK2 */
        usart_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(USART2)
  else if (USARTxSource == LL_RCC_USART2_CLKSOURCE)
  {
    /* USART2CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART2_CLKSOURCE_SYSCLK: /* USART2 Clock is System Clock */
        usart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_USART2_CLKSOURCE_HSI:    /* USART2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_LSE:    /* USART2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() != 0U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_PCLK1:  /* USART2 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* USART2 */
  else
  {
    /* nothing to do */
  }

  return usart_frequency;
}

/**
  * @brief  Return SPIx clock frequency
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  * @retval SPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI) is not ready
  */
uint32_t LL_RCC_GetSPIClockFreq(uint32_t SPIxSource)
{
  uint32_t SPI_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SPI_CLKSOURCE(SPIxSource));

  if (SPIxSource == LL_RCC_SPI3_CLKSOURCE)
  {
    /* SPI3 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI3_CLKSOURCE_SYSCLK: /* SPI3 Clock is System Clock */
        SPI_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_SPI3_CLKSOURCE_HSI:    /* SPI3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          SPI_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI3_CLKSOURCE_PCLK7:   /* SPI3 Clock is PCLK7 */
        SPI_frequency = RCC_GetPCLK7ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(SPI1)
  else if (SPIxSource == LL_RCC_SPI1_CLKSOURCE)
  {
    /* SPI1 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI1_CLKSOURCE_SYSCLK: /* SPI1 Clock is System Clock */
        SPI_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_SPI1_CLKSOURCE_HSI:    /* SPI1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          SPI_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI1_CLKSOURCE_PCLK2:  /* SPI1 Clock is PCLK2 */
        SPI_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* SPI1 */
  else
  {
    /* nothing to do */
  }

  return SPI_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI) is not ready
  */
uint32_t LL_RCC_GetI2CClockFreq(uint32_t I2CxSource)
{
  uint32_t i2c_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_I2C_CLKSOURCE(I2CxSource));

  if (I2CxSource == LL_RCC_I2C3_CLKSOURCE)
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C3_CLKSOURCE_SYSCLK: /* I2C3 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C3_CLKSOURCE_HSI:    /* I2C3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C3_CLKSOURCE_PCLK7:  /* I2C3 Clock is PCLK7 */
        i2c_frequency = RCC_GetPCLK7ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(I2C1)
  else if (I2CxSource == LL_RCC_I2C1_CLKSOURCE)
  {
    /* I2C1 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C1_CLKSOURCE_SYSCLK: /* I2C1 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C1_CLKSOURCE_HSI:    /* I2C1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C1_CLKSOURCE_PCLK1:  /* I2C1 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* I2C1 */
  else
  {
    /* nothing to do */
  }

  return i2c_frequency;
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

  /* LPUART1CLK clock frequency */
  switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
  {
    case LL_RCC_LPUART1_CLKSOURCE_SYSCLK: /* LPUART1 Clock is System Clock */
      lpuart_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_LPUART1_CLKSOURCE_HSI:    /* LPUART1 Clock is HSI Osc. */
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        lpuart_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_LSE:    /* LPUART1 Clock is LSE Osc. */
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        lpuart_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PCLK7:  /* LPUART1 Clock is PCLK7 */
      lpuart_frequency = RCC_GetPCLK7ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
      break;

    default:
      /* unreachable code */
      break;
  }

  return lpuart_frequency;
}

/**
  * @brief  Return LPTIMx clock frequency
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
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
#if defined(RCC_LSI2_SUPPORT)
        if ((RCC->BDCR1& (RCC_BDCR1_LSI1ON | RCC_BDCR1_LSI2ON)) != 0U)
#else
        if (LL_RCC_LSI1_IsReady() != 0U)
#endif
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_HSI:    /* LPTIM1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_LSE:    /* LPTIM1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() != 0U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_PCLK7:  /* LPTIM1 Clock is PCLK7 */
        lptim_frequency = RCC_GetPCLK7ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(LPTIM2)
  else if (LPTIMxSource == LL_RCC_LPTIM2_CLKSOURCE)
  {
    /* LPTIM2CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM2_CLKSOURCE_LSI:    /* LPTIM2 Clock is LSI Osc. */
#if defined(RCC_LSI2_SUPPORT)
        if ((RCC->BDCR1& (RCC_BDCR1_LSI1ON | RCC_BDCR1_LSI2ON)) != 0U)
#else
        if (LL_RCC_LSI1_IsReady() != 0U)
#endif
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_HSI:    /* LPTIM2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_LSE:    /* LPTIM2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() != 0U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_PCLK1:  /* LPTIM2 Clock is PCLK1 */
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* LPTIM2 */
  else
  {
    /* nothing to do */
  }

  return lptim_frequency;
}

#if defined(SAI1)
/**
  * @brief  Return SAIx clock frequency
  * @param  SAIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  * @retval SAI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that PLL1 is not ready
  */
uint32_t LL_RCC_GetSAIClockFreq(uint32_t SAIxSource)
{
  uint32_t sai_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SAI_CLKSOURCE(SAIxSource));

  if (SAIxSource == LL_RCC_SAI1_CLKSOURCE)
  {
    /* SAI1CLK clock frequency */
    switch (LL_RCC_GetSAIClockSource(SAIxSource))
    {
      case LL_RCC_SAI1_CLKSOURCE_PLL1P:        /* PLL1P clock used as SAI1 clock source */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1_IsEnabledDomain_PLL1P() != 0U)
          {
            sai_frequency = RCC_PLL1P_GetFreqDomain();
          }
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PLL1Q:        /* PLL1Q clock used as SAI1 clock source */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1_IsEnabledDomain_PLL1Q() != 0U)
          {
            sai_frequency = RCC_PLL1Q_GetFreqDomain();
          }
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_SYSCLK:        /* System clock used as SAI1 clock source */
        sai_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_SAI1_CLKSOURCE_PIN:         /* External input clock used as SAI1 clock source */
        sai_frequency = EXTERNAL_SAI1_CLOCK_VALUE;
        break;

      case LL_RCC_SAI1_CLKSOURCE_HSI:        /* SAI Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          sai_frequency = HSI_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else
  {
    /* nothing to do */
  }

  return sai_frequency;
}
#endif /* SAI1 */

/**
  * @brief  Return RNGx clock frequency
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval RNG clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI or HSI48) or PLL1 is not ready
  */
uint32_t LL_RCC_GetRNGClockFreq(uint32_t RNGxSource)
{
  uint32_t rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_RNG_CLKSOURCE(RNGxSource));

  /* RNGCLK clock frequency */
  switch (LL_RCC_GetRNGClockSource(RNGxSource))
  {
    case LL_RCC_RNG_CLKSOURCE_HSI:            /* HSI clock used as RNG clock source */
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        rng_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_LSI:            /* LSI clock used as RNG clock source */
#if defined(RCC_LSI2_SUPPORT)
      if ((RCC->BDCR1& (RCC_BDCR1_LSI1ON | RCC_BDCR1_LSI2ON)) != 0U)
#else
      if (LL_RCC_LSI1_IsReady() != 0U)
#endif
      {
        rng_frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_LSE:            /* LSE clock used as RNG clock source */
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        rng_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_PLL1Q_DIV2:     /* PLL1Q/2 clock used as RNG clock source */
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        if (LL_RCC_PLL1_IsEnabledDomain_PLL1Q() != 0U)
        {
          rng_frequency = RCC_PLL1Q_GetFreqDomain()/2U;
        }
      }
      break;
    default:
      /* unreachable code */
      break;

  }

  return rng_frequency;
}

/**
  * @brief  Return ADCx clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSE / HSI) or PLL1 is not ready
  */
uint32_t LL_RCC_GetADCClockFreq(uint32_t ADCxSource)
{
  uint32_t adc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADC_CLKSOURCE(ADCxSource));

  /* ADCCLK clock frequency */
  switch (LL_RCC_GetADCClockSource(ADCxSource))
  {
    case LL_RCC_ADC_CLKSOURCE_HCLK:         /* ADC Clock is SYSCLK */
      adc_frequency = RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq());
      break;

    case LL_RCC_ADC_CLKSOURCE_SYSCLK:       /* SYSCLK clock used as ADC clock source */
      adc_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ADC_CLKSOURCE_PLL1P:        /* PLL1P clock used as ADC clock source */
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        if (LL_RCC_PLL1_IsEnabledDomain_PLL1P() != 0U)
        {
          adc_frequency = RCC_PLL1P_GetFreqDomain();
        }
      }
      break;

    case LL_RCC_ADC_CLKSOURCE_HSI:          /*HSI clock used as ADC clock source */
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        adc_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_ADC_CLKSOURCE_HSE:           /*HSE clock used as ADC clock source */
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        adc_frequency = HSE_VALUE;
      }
      break;

    default:
      /* unreachable code */
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
  uint32_t frequency;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (LL_RCC_GetSysClkSource())
  {
    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:   /* HSI used as system clock  source */
      frequency = HSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:   /* HSE used as system clock  source */
      frequency = HSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_PLL1R:  /* PLL1 used as system clock  source */
      frequency = RCC_PLL1R_GetFreqDomain();
      break;

    default:
      frequency = HSI_VALUE;
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
  * @brief  Return PCLK2 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK2 clock frequency (in Hz)
  */
uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK2 clock frequency */
  return __LL_RCC_CALC_PCLK2_FREQ(HCLK_Frequency, LL_RCC_GetAPB2Prescaler());
}


/**
  * @brief  Return PCLK7 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK7 clock frequency (in Hz)
  */
uint32_t RCC_GetPCLK7ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK7 clock frequency */
  return __LL_RCC_CALC_PCLK7_FREQ(HCLK_Frequency, LL_RCC_GetAPB7Prescaler());
}

/**
  * @brief  Return PLL1R clock frequency used for system domain
  * @retval PLL1R clock frequency (in Hz)
  */
uint32_t RCC_PLL1R_GetFreqDomain(void)
{
  uint32_t pllinputfreq, pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE/ PLLM) * PLLN
     SYSCLK = PLL_VCO / PLLR
    */
  pllsource = LL_RCC_PLL1_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL1 clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL1 clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = HSI_VALUE;
      break;
  }
  return __LL_RCC_CALC_PLL1RCLK_FREQ(pllinputfreq, LL_RCC_PLL1_GetDivider(),
                                     LL_RCC_PLL1_GetN(), LL_RCC_PLL1_GetR());
}
/**
  * @brief  Return PLL1P clock frequency used for ADC and SAI domains
  * @retval PLL1P clock frequency (in Hz)
  */
uint32_t RCC_PLL1P_GetFreqDomain(void)
{
  uint32_t pll1inputfreq, pll1outputfreq, pll1source;
  uint32_t pll1n, pll1pdiv;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
     Domain clock = PLL_VCO / PLL1P
    */
  pll1source = LL_RCC_PLL1_GetMainSource();

  switch (pll1source)
  {
    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL1 clock source */
      pll1inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL1 clock source */
      pll1inputfreq = HSE_VALUE;
      break;

    default:
      pll1inputfreq = HSI_VALUE;
      break;
  }

  pll1n = LL_RCC_PLL1_GetN();
  pll1pdiv = LL_RCC_PLL1_GetP();
  if ((pll1n >= 8U) && (pll1pdiv >= 2U))
  {
    pll1outputfreq = __LL_RCC_CALC_PLL1PCLK_FREQ(pll1inputfreq, LL_RCC_PLL1_GetDivider(),
                                                 pll1n, pll1pdiv);
  }
  else
  {
    pll1outputfreq = 0;  /* Invalid PLL1N or PLL1PDIV value */
  }
  return pll1outputfreq;
}

/**
  * @brief  Return PLL1Q clock frequency used for RNG and SAI domains
  * @retval PLL1Q clock frequency (in Hz)
  */
uint32_t RCC_PLL1Q_GetFreqDomain(void)
{
  uint32_t pll1inputfreq, pll1source;

  /* PLL1_VCO = (HSE_VALUE or HSI_VALUE / PLL1M) * PLL1N
     Domain clock = PLL1_VCO / PLL1Q
    */
  pll1source = LL_RCC_PLL1_GetMainSource();

  switch (pll1source)
  {
    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL1 clock source */
      pll1inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL1 clock source */
      pll1inputfreq = HSE_VALUE;
      break;

    default:
      pll1inputfreq = HSI_VALUE;
      break;
  }
  return __LL_RCC_CALC_PLL1QCLK_FREQ(pll1inputfreq, LL_RCC_PLL1_GetDivider(),
                                     LL_RCC_PLL1_GetN(), LL_RCC_PLL1_GetQ());
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
