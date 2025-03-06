/**
  ******************************************************************************
  * @file    stm32u3xx_ll_rcc.c
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
#include "stm32u3xx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32U3xx_LL_Driver
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
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private functions
  * @{
  */
static uint32_t RCC_GetSystemClockFreq(void);
static uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency);
static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetPCLK3ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetMSISClockFreq(void);
static uint32_t RCC_GetMSIKClockFreq(void);
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
  *         - MSIS ON (RC1, 12MHz) and used as system clock source
  *         - other clocks OFF
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

  /* Set MSISON and MSIKON bit */
  SET_BIT(RCC->CR, (RCC_CR_MSISON | RCC_CR_MSIKON));

  /* Wait until MSI is ready */
  while (LL_RCC_MSIS_IsReady() == 0U)
  {
  }

  /* Select MSIS source and divider */
  LL_RCC_MSIS_SetClockSource(LL_RCC_MSIS_CLOCK_SOURCE_RC1);
  LL_RCC_MSIS_SetClockDivision(LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_2);

  /* Set MSRCx trimming default value */
  LL_RCC_MSI_RC0_SetTrimming(0x20);
  LL_RCC_MSI_RC1_SetTrimming(0x20);

  /* Set HSITRIM default value */
  LL_RCC_HSI_SetCalibTrimming(0x10);

  /* Reset CFGR1 register (MSIS is selected as system clock source) */
  CLEAR_REG(RCC->CFGR1);

  /* Wait until clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_MSIS)
  {
  }

  /* Set AHBx and APBx prescaler to their default values */
  CLEAR_REG(RCC->CFGR2);
  CLEAR_REG(RCC->CFGR3);
  CLEAR_REG(RCC->CFGR4);

  /* Clear CR register in 2 steps: first to clear HSEON in case bypass was enabled */
  RCC->CR = (RCC_CR_MSISON | RCC_CR_MSIKON);

  /* Then again to HSEBYP in case bypass was enabled */
  /* The HSEBYP bit can be written only if the HSE oscillator is disabled (HSEON = 0 and HSERDY = 0) */
  RCC->CR = (RCC_CR_MSISON | RCC_CR_MSIKON);

  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER);

  /* Clear all interrupts flags */
  WRITE_REG(RCC->CICR, 0xFFFFFFFFU);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB1, AHB2, APB1, APB2 and APB3 buses clocks
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is HSI16, function returns values based on HSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   If SYSCLK source is MSIS, function returns values based on MSIS value
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
  * @note   Each time SYSCLK, HCLK and/or PCLK1, PCLK2 and/or PCLK3 clock changes, this function
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
  RCC_Clocks->PCLK3_Frequency  = RCC_GetPCLK3ClockFreq(RCC_Clocks->HCLK_Frequency);
}


/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE
  * @retval USART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI) is not ready
  */
uint32_t LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource)
{
  uint32_t usart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_USART_CLKSOURCE(USARTxSource));

  if (USARTxSource == LL_RCC_USART1_CLKSOURCE)
  {
    /* USART1CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART1_CLKSOURCE_HSI16:    /* USART1 Clock is HSI16 Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          usart_frequency = HSI_VALUE;
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
      case LL_RCC_USART2_CLKSOURCE_HSI16:    /* USART2 Clock is HSI16 Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          usart_frequency = HSI_VALUE;
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
  else /* i.e. USARTxSource == LL_RCC_USART3_CLKSOURCE */
  {
    /* USART3CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART3_CLKSOURCE_HSI16:    /* USART3 Clock is HSI16 Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART3_CLKSOURCE_PCLK1:  /* USART3 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }

  return usart_frequency;
}


/**
  * @brief  Return UARTx clock frequency
  * @param  UARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  * @retval UART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t LL_RCC_GetUARTClockFreq(uint32_t UARTxSource)
{
  uint32_t UART_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_UART_CLKSOURCE(UARTxSource));

  /* UART1CLK clock frequency */
  switch (LL_RCC_GetUARTClockSource(UARTxSource))
  {
    case LL_RCC_UART4_CLKSOURCE_HSI16:    /* UART4 Clock is HSI16 Osc. */
    case LL_RCC_UART5_CLKSOURCE_HSI16:    /* UART5 Clock is HSI16 Osc. */
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        UART_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_UART4_CLKSOURCE_PCLK1:  /* UART4 Clock is PCLK1 */
    case LL_RCC_UART5_CLKSOURCE_PCLK1:  /* UART5 Clock is PCLK1 */
      UART_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
      break;

    default:
      /* unreachable code */
      break;
  }

  return UART_frequency;
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

  assert_param(IS_LL_RCC_LPUART_CLKSOURCE(LPUARTxSource));

  /* LPUART1CLK clock frequency */
  switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
  {
    case LL_RCC_LPUART1_CLKSOURCE_MSIK: /* LPUART1 Clock is MSIK */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        lpuart_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_HSI16:    /* LPUART1 Clock is HSI16 Osc. */
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

    case LL_RCC_LPUART1_CLKSOURCE_PCLK3:  /* LPUART1 Clock is PCLK3 */
      lpuart_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
      break;

    default:
      /* unreachable code */
      break;
  }

  return lpuart_frequency;
}


/**
  * @brief  Return SPIx clock frequency
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  *         @arg @ref LL_RCC_SPI4_CLKSOURCE
  * @retval SPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates error
  */
uint32_t LL_RCC_GetSPIClockFreq(uint32_t SPIxSource)
{
  uint32_t SPI_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_SPI_CLKSOURCE(SPIxSource));

  if (SPIxSource == LL_RCC_SPI1_CLKSOURCE)
  {
    /* SPI1 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI1_CLKSOURCE_MSIK: /* SPI1 Clock is MSIK */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          SPI_frequency = RCC_GetMSIKClockFreq();
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
  else if (SPIxSource == LL_RCC_SPI2_CLKSOURCE)
  {
    /* SPI1 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI2_CLKSOURCE_MSIK: /* SPI2 Clock is MSIK */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          SPI_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_SPI2_CLKSOURCE_PCLK1:  /* SPI2 Clock is PCLK1 */
        SPI_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined (SPI4)
  else if (SPIxSource == LL_RCC_SPI4_CLKSOURCE)
  {
    /* SPI4 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI4_CLKSOURCE_MSIK: /* SPI3 Clock is MSIK */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          SPI_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_SPI4_CLKSOURCE_PCLK1:  /* SPI3 Clock is PCLK1 */
        SPI_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* SPI4 */
  else /*if (SPIxSource == LL_RCC_SPI3_CLKSOURCE)*/
  {
    /* SPI3 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI3_CLKSOURCE_MSIK: /* SPI3 Clock is MSIK */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          SPI_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_SPI3_CLKSOURCE_PCLK1:  /* SPI3 Clock is PCLK1 */
        SPI_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }

  return SPI_frequency;
}

/**
  * @brief  Return OCTOSPIx clock frequency
  * @param  OCTOSPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE
  * @retval OCTOSPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates error
  */
uint32_t LL_RCC_GetOCTOSPIClockFreq(uint32_t OCTOSPIxSource)
{
  uint32_t OCTOSPI_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_OCTOSPI_CLKSOURCE(OCTOSPIxSource));

  /* OCTOSPI CLK clock frequency */
  switch (LL_RCC_GetOCTOSPIClockSource(OCTOSPIxSource))
  {
    case LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK: /* OCTOSPI Clock is SYSCLK */
      OCTOSPI_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_OCTOSPI_CLKSOURCE_MSIK:  /* OCTOSPI Clock is MSIK */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        OCTOSPI_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    default:
      /* unreachable code */
      break;
  }
  return OCTOSPI_frequency;
}

/**
  * @brief  Return FDCANx clock frequency
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval FDCAN clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates error
  */
uint32_t LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource)
{
  uint32_t FDCAN_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_FDCAN_CLKSOURCE(FDCANxSource));

  /* FDCAN CLK clock frequency */
  switch (LL_RCC_GetFDCANClockSource(FDCANxSource))
  {
    case LL_RCC_FDCAN_CLKSOURCE_SYSCLK: /* FDCAN Clock is SYSCLK */
      FDCAN_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_FDCAN_CLKSOURCE_MSIK:  /* FDCAN Clock is MSIK */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        FDCAN_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    default:
      /* unreachable code */
      break;
  }
  return FDCAN_frequency;
}

/**
  * @brief  Return USBx clock frequency
  * @param  USBxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB1_CLKSOURCE
  * @retval USB clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates error
  */
uint32_t LL_RCC_GetUSBClockFreq(uint32_t USBxSource)
{
  uint32_t usb_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_USB_CLKSOURCE(USBxSource));

  /* USB CLK clock frequency */
  switch (LL_RCC_GetICLKClockSource(LL_RCC_ICLK_CLKSOURCE))
  {
    case LL_RCC_ICLK_CLKSOURCE_SYSCLK: /* USB Clock is SYSCLK */
      usb_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ICLK_CLKSOURCE_MSIK:  /* USB Clock is MSIK */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        usb_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    case LL_RCC_ICLK_CLKSOURCE_HSI48:  /* USB Clock is HSI48 */
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        usb_frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_ICLK_CLKSOURCE_HSE:  /* USB Clock is HSE */
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        usb_frequency = HSE_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }
  if (LL_RCC_GetUSBClockSource(USBxSource) == LL_RCC_USB1_CLKSOURCE_ICLKDIV2)
  {
    usb_frequency /= 2U;
  }

  return (usb_frequency);
}

/**
  * @brief  Return SDMMCx clock frequency
  * @param  SDMMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates error
  */
uint32_t LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource)
{
  uint32_t SDMMC_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_SDMMC_CLKSOURCE(SDMMCxSource));

  /* SDMMC CLK clock frequency */
  switch (LL_RCC_GetICLKClockSource(LL_RCC_ICLK_CLKSOURCE))
  {
    case LL_RCC_ICLK_CLKSOURCE_SYSCLK: /* SDMMC Clock is SYSCLK */
      SDMMC_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ICLK_CLKSOURCE_MSIK:  /* SDMMC Clock is MSIK */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        SDMMC_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    case LL_RCC_ICLK_CLKSOURCE_HSI48:  /* SDMMC Clock is HSI48 */
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        SDMMC_frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_ICLK_CLKSOURCE_HSE:  /* SDMMC Clock is HSE */
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        SDMMC_frequency = HSE_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return (SDMMC_frequency);
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates error
  */
uint32_t LL_RCC_GetI2CClockFreq(uint32_t I2CxSource)
{
  uint32_t i2c_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_I2C_CLKSOURCE(I2CxSource));

  if (I2CxSource == LL_RCC_I2C1_CLKSOURCE)
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C1_CLKSOURCE_MSIK: /* I2C3 Clock is MSIK Clock */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          i2c_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_I2C1_CLKSOURCE_PCLK1:  /* I2C3 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (I2CxSource == LL_RCC_I2C2_CLKSOURCE)
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C2_CLKSOURCE_MSIK: /* I2C3 Clock is MSIK Clock */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          i2c_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_I2C2_CLKSOURCE_PCLK1:  /* I2C3 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(I2C4)
  else if (I2CxSource == LL_RCC_I2C4_CLKSOURCE)
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C4_CLKSOURCE_MSIK: /* I2C4 Clock is MSIK Clock */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          i2c_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_I2C4_CLKSOURCE_PCLK1:  /* I2C4 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* I2C4 */
  else /*if (I2CxSource == LL_RCC_I2C3_CLKSOURCE)*/
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C3_CLKSOURCE_MSIK: /* I2C3 Clock is MSIK Clock */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          i2c_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_I2C3_CLKSOURCE_PCLK3:  /* I2C3 Clock is PCLK3 */
        i2c_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  return i2c_frequency;
}

/**
  * @brief  Return I3Cx clock frequency
  * @param  I3CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  *         @arg @ref LL_RCC_I3C2_CLKSOURCE
  * @retval I3C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates error
  */
uint32_t LL_RCC_GetI3CClockFreq(uint32_t I3CxSource)
{
  uint32_t I3C_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_I3C_CLKSOURCE(I3CxSource));

  if (I3CxSource == LL_RCC_I3C1_CLKSOURCE)
  {
    /* I3C3 CLK clock frequency */
    switch (LL_RCC_GetI3CClockSource(I3CxSource))
    {
      case LL_RCC_I3C1_CLKSOURCE_MSIK: /* I3C3 Clock is MSIK Clock */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          I3C_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_I3C1_CLKSOURCE_PCLK1:  /* I3C3 Clock is PCLK1 */
        I3C_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else /* I3CxSource = LL_RCC_I3C2_CLKSOURCE */
  {
    /* I3C3 CLK clock frequency */
    switch (LL_RCC_GetI3CClockSource(I3CxSource))
    {
      case LL_RCC_I3C2_CLKSOURCE_MSIK: /* I3C2 Clock is MSIK Clock */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          I3C_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      case LL_RCC_I3C2_CLKSOURCE_PCLK2:  /* I3C2 Clock is PCLK2 */
        I3C_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  return I3C_frequency;
}

/**
  * @brief  Return LPTIMx clock frequency
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE
  * @retval LPTIM clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI16, LSI or LSE) is not ready
  */
uint32_t LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource)
{
  uint32_t lptim_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_LPTIM_CLKSOURCE(LPTIMxSource));

  if (LPTIMxSource == LL_RCC_LPTIM1_CLKSOURCE)
  {
    /* LPTIM1CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM1_CLKSOURCE_LSI:    /* LPTIM1 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() != 0U)
        {
          lptim_frequency = LSI_VALUE;
          if (LL_RCC_LSI_GetClockPrediv() == LL_RCC_LSI_PREDIV_128)
          {
            lptim_frequency /= 128U;
          }
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_HSI16:    /* LPTIM1 Clock is HSI16 Osc. */
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

      case LL_RCC_LPTIM1_CLKSOURCE_MSIK:  /* LPTIM1 Clock is MSIK */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          lptim_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (LPTIMxSource == LL_RCC_LPTIM2_CLKSOURCE)
  {
    /* LPTIM2CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM2_CLKSOURCE_LSI:    /* LPTIM2 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() != 0U)
        {
          lptim_frequency = LSI_VALUE;
          if (LL_RCC_LSI_GetClockPrediv() == LL_RCC_LSI_PREDIV_128)
          {
            lptim_frequency /= 128U;
          }
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_HSI16:    /* LPTIM2 Clock is HSI16 Osc. */
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
  else /* LPTIMxSource = LL_RCC_LPTIM34_CLKSOURCE */
  {
    /* LPTIM34CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM34_CLKSOURCE_LSI:    /* LPTIM34 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() != 0U)
        {
          lptim_frequency = LSI_VALUE;
          if (LL_RCC_LSI_GetClockPrediv() == LL_RCC_LSI_PREDIV_128)
          {
            lptim_frequency /= 128U;
          }
        }
        break;

      case LL_RCC_LPTIM34_CLKSOURCE_HSI16:    /* LPTIM34 Clock is HSI16 Osc. */
        if (LL_RCC_HSI_IsReady() != 0U)
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM34_CLKSOURCE_LSE:    /* LPTIM34 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() != 0U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM34_CLKSOURCE_MSIK:  /* LPTIM34 Clock is PCLK1 */
        if (LL_RCC_MSIK_IsReady() != 0U)
        {
          lptim_frequency = RCC_GetMSIKClockFreq();
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  return lptim_frequency;
}

/**
  * @brief  Return RTCx clock frequency
  * @param  RTCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE
  * @retval RTC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSE, LSI or LSE) is not ready
  */
uint32_t LL_RCC_GetRTCClockFreq(uint32_t RTCxSource)
{
  uint32_t rtc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_RTC_CLKSOURCE(RTCxSource));

  /* RTC CLK clock frequency */
  switch (LL_RCC_GetRTCClockSource(RTCxSource))
  {
    case LL_RCC_RTC_CLKSOURCE_LSE:        /* LSE clock used as RTC clock source */
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        rtc_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_LSI:        /* LSI clock used as RTC clock source */
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        rtc_frequency = LSI_VALUE;
        if (LL_RCC_LSI_GetClockPrediv() == LL_RCC_LSI_PREDIV_128)
        {
          rtc_frequency /= 128U;
        }
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_HSE_DIV32:        /* HSE/32 clock used as RTC clock source */
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        rtc_frequency = HSE_VALUE / 32U;
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_NONE:
    default:
      /* unreachable code */
      break;
  }
  return rtc_frequency;
}

/**
  * @brief  Return SAIx clock frequency
  * @param  SAIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  * @retval SAI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that MSIK or HSE is not ready
  */
uint32_t LL_RCC_GetSAIClockFreq(uint32_t SAIxSource)
{
  uint32_t sai_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_SAI_CLKSOURCE(SAIxSource));

  /* SAI1CLK clock frequency */
  switch (LL_RCC_GetSAIClockSource(SAIxSource))
  {
    case LL_RCC_SAI1_CLKSOURCE_MSIK:        /* MSIK clock used as SAI1 clock source */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        sai_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    case LL_RCC_SAI1_CLKSOURCE_AUDCLKIN:         /* External input clock used as SAI1 clock source */
      sai_frequency = EXTERNAL_AUDIO_CLOCK_VALUE;
      break;

    case LL_RCC_SAI1_CLKSOURCE_HSE:        /* SAI Clock is HSE Osc. */
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        sai_frequency = HSE_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return sai_frequency;
}

/**
  * @brief  Return ADFx clock frequency
  * @param  ADFxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE
  * @retval ADF clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that MSIK or HSE is not ready
  */
uint32_t LL_RCC_GetADFClockFreq(uint32_t ADFxSource)
{
  uint32_t adf_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_ADF_CLKSOURCE(ADFxSource));

  /* ADF1CLK clock frequency */
  switch (LL_RCC_GetADFClockSource(ADFxSource))
  {
    case LL_RCC_ADF1_CLKSOURCE_MSIK:        /* MSIK clock used as ADF1 clock source */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        adf_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    case LL_RCC_ADF1_CLKSOURCE_AUDCLKIN:         /* External input clock used as ADF1 clock source */
      adf_frequency = EXTERNAL_AUDIO_CLOCK_VALUE;
      break;

    case LL_RCC_ADF1_CLKSOURCE_SAI1:        /* ADF Clock is SAI1 clock */
      adf_frequency = LL_RCC_GetSAIClockFreq(LL_RCC_SAI1_CLKSOURCE);
      break;

    default:
      /* unreachable code */
      break;
  }

  return adf_frequency;
}

/**
  * @brief  Return RNGx clock frequency
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval RNG clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI48) or MSIK is not ready
  */
uint32_t LL_RCC_GetRNGClockFreq(uint32_t RNGxSource)
{
  uint32_t rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_RNG_CLKSOURCE(RNGxSource));

  /* RNGCLK clock frequency */
  switch (LL_RCC_GetRNGClockSource(RNGxSource))
  {
    case LL_RCC_RNG_CLKSOURCE_HSI48:            /* HSI48 clock used as RNG clock source */
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        rng_frequency = HSI48_VALUE;
      }
      break;
    case LL_RCC_RNG_CLKSOURCE_MSIK:            /* MSIK clock used as RNG clock source */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        rng_frequency = RCC_GetMSIKClockFreq();
      }
      break;

    default:
      /* unreachable code */
      break;
  }
  return rng_frequency;
}

/**
  * @brief  Return ADCDACx clock frequency
  * @param  ADCDACxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSE) or MSIK is not ready
  */
uint32_t LL_RCC_GetADCDACClockFreq(uint32_t ADCDACxSource)
{
  uint32_t adcdac_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_ADCDAC_CLKSOURCE(ADCDACxSource));

  /* ADCDACCLK clock frequency */
  switch (LL_RCC_GetADCDACClockSource(ADCDACxSource))
  {
    case LL_RCC_ADCDAC_CLKSOURCE_HCLK:         /* ADCDAC Clock is SYSCLK */
      adcdac_frequency = RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq());
      break;
    case LL_RCC_ADCDAC_CLKSOURCE_HSE:           /* HSE clock used as ADC clock source */
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        adcdac_frequency = HSE_VALUE;
      }
      break;
    case LL_RCC_ADCDAC_CLKSOURCE_MSIK:           /* MSIK clock used as ADC clock source */
      if (LL_RCC_MSIK_IsReady() != 0U)
      {
        adcdac_frequency = RCC_GetMSIKClockFreq();
      }
      break;
    default:
      /* unreachable code */
      break;
  }

  if (adcdac_frequency != LL_RCC_PERIPH_FREQUENCY_NO)
  {
    switch (LL_RCC_GetADCDACClockPrescaler(LL_RCC_ADCDAC_CLKPRESCALER))
    {
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_2:
        adcdac_frequency /= 2U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_4:
        adcdac_frequency /= 4U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_8:
        adcdac_frequency /= 8U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_16:
        adcdac_frequency /= 16U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_32:
        adcdac_frequency /= 32U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_64:
        adcdac_frequency /= 64U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_128:
        adcdac_frequency /= 128U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_256:
        adcdac_frequency /= 256U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK_DIV_512:
        adcdac_frequency /= 512U;
        break;
      case LL_RCC_ADCDAC_CLKPRESCALER_ICLK:
      default:
        /* No division */
        break;
    }
  }
  return adcdac_frequency;
}

/**
  * @brief  Return DACSHx clock frequency
  * @param  DACSHxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE
  * @retval DACSH clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that error occurred
  */
uint32_t LL_RCC_GetDACSHClockFreq(uint32_t DACSHxSource)
{
  uint32_t dacsh_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  assert_param(IS_LL_RCC_DAC1SH_CLKSOURCE(DACSHxSource));

  /* DACSHCLK clock frequency */
  switch (LL_RCC_GetDACSHClockSource(DACSHxSource))
  {
    case LL_RCC_DAC1SH_CLKSOURCE_LSE:        /* LSE clock used as DAC1SH clock source */
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        dacsh_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_DAC1SH_CLKSOURCE_LSI:        /* LSI clock used as DAC1SH clock source */
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        dacsh_frequency = LSI_VALUE;
        if (LL_RCC_LSI_GetClockPrediv() == LL_RCC_LSI_PREDIV_128)
        {
          dacsh_frequency /= 128U;
        }
      }
      break;

    default:
      /* unreachable code */
      break;
  }
  return dacsh_frequency;
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
static uint32_t RCC_GetSystemClockFreq(void)
{
  uint32_t frequency;

  switch (LL_RCC_GetSysClkSource())
  {
    case LL_RCC_SYS_CLKSOURCE_HSE:   /* HSE used as system clock  source */
      frequency = HSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_MSIS:  /* MSIS used as system clock  source */
      frequency = RCC_GetMSISClockFreq();
      break;

    case LL_RCC_SYS_CLKSOURCE_HSI16:   /* HSI used as system clock  source */
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
static uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency)
{
  /* HCLK clock frequency */
  return __LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, LL_RCC_GetAHBPrescaler());
}

/**
  * @brief  Return PCLK1 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK1 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK1 clock frequency */
  return __LL_RCC_CALC_PCLK1_FREQ(HCLK_Frequency, LL_RCC_GetAPB1Prescaler());
}

/**
  * @brief  Return PCLK2 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK2 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK2 clock frequency */
  return __LL_RCC_CALC_PCLK2_FREQ(HCLK_Frequency, LL_RCC_GetAPB2Prescaler());
}


/**
  * @brief  Return PCLK3 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK3 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK3ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK3 clock frequency */
  return __LL_RCC_CALC_PCLK3_FREQ(HCLK_Frequency, LL_RCC_GetAPB3Prescaler());
}

/**
  * @brief  Return MSIS clock frequency
  * @retval MSIS clock frequency (in Hz)
  */
static uint32_t RCC_GetMSISClockFreq(void)
{
  uint32_t frequency = MSIRC1_VALUE;

  if (LL_RCC_MSIS_GetClockSource() == LL_RCC_MSIS_CLOCK_SOURCE_RC0)
  {
    frequency = MSIRC0_VALUE;
  }
  switch (LL_RCC_MSIS_GetClockDivision())
  {
    case LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_2:
      frequency /= 2U;
      break;
    case LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_4:
      frequency /= 4U;
      break;
    case LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_8:
      frequency /= 8U;
      break;
    case LL_RCC_MSIS_CLOCK_SOURCE_RC_DIV_1:
    default:
      /* no division */
      break;
  }

  return frequency;
}

/**
  * @brief  Return MSIK clock frequency
  * @retval MSIK clock frequency (in Hz)
  */
static uint32_t RCC_GetMSIKClockFreq(void)
{
  uint32_t frequency = MSIRC1_VALUE;

  if (LL_RCC_MSIK_GetClockSource() == LL_RCC_MSIK_CLOCK_SOURCE_RC0)
  {
    frequency = MSIRC0_VALUE;
  }
  switch (LL_RCC_MSIK_GetClockDivision())
  {
    case LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_2:
      frequency /= 2U;
      break;
    case LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_4:
      frequency /= 4U;
      break;
    case LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_8:
      frequency /= 8U;
      break;
    case LL_RCC_MSIK_CLOCK_SOURCE_RC_DIV_1:
    default:
      /* no division */
      break;
  }

  return frequency;
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
