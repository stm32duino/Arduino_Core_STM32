/**
  ******************************************************************************
  * @file    stm32u3xx_hal_rcc_ex.c
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
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @defgroup RCCEx RCCEx
  * @brief RCC Extended HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define MSI_PLL_TIMEOUT_VALUE           2U    /* 2 ms (minimum Tick + 1) */

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
  *            @arg @ref RCC_PERIPHCLK_USART1   USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART3   USART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART4    UART4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART5    UART5 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I3C1     I3C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1     I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2     I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I3C2     I3C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI2     SPI2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2   LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI1     SPI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SYSTICK  SYSTICK peripheral clock
  *            @arg @ref RCC_PERIPHCLK_FDCAN    FDCAN peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ICLK     ICLK peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USB1     USB1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIMIC    TIMIC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADF1     ADF1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3     SPI3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1     SAI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RNG      RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADCDAC   ADCDAC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_DAC1SH   DAC1SH peripheral clock
  *            @arg @ref RCC_PERIPHCLK_OCTOSPI1 OCTOSPI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3     I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM34  LPTIM34 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1   LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2   USART2 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_I2C4     I2C4 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_SPI4     SPI4 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_RTC      RTC peripheral clock
  *
  *            (*) value not defined in all devices.
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

  /*-------------------------- USART3 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART3) == RCC_PERIPHCLK_USART3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART3CLKSOURCE(PeriphClkInit->Usart3ClockSelection));

    /* Configure the USART3 clock source */
    __HAL_RCC_USART3_CONFIG(PeriphClkInit->Usart3ClockSelection);
  }

  /*-------------------------- UART4 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART4) == RCC_PERIPHCLK_UART4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART4CLKSOURCE(PeriphClkInit->Uart4ClockSelection));

    /* Configure the UART4 clock source */
    __HAL_RCC_UART4_CONFIG(PeriphClkInit->Uart4ClockSelection);
  }

  /*-------------------------- UART5 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART5) == RCC_PERIPHCLK_UART5)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART5CLKSOURCE(PeriphClkInit->Uart5ClockSelection));

    /* Configure the UART5 clock source */
    __HAL_RCC_UART5_CONFIG(PeriphClkInit->Uart5ClockSelection);
  }

  /*-------------------------- I3C1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I3C1) == RCC_PERIPHCLK_I3C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I3C1CLKSOURCE(PeriphClkInit->I3c1ClockSelection));

    /* Configure the I3C1 clock source */
    __HAL_RCC_I3C1_CONFIG(PeriphClkInit->I3c1ClockSelection);
  }

  /*-------------------------- I2C1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));

    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }

  /*-------------------------- I2C2 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C2) == RCC_PERIPHCLK_I2C2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C2CLKSOURCE(PeriphClkInit->I2c2ClockSelection));

    /* Configure the I2C2 clock source */
    __HAL_RCC_I2C2_CONFIG(PeriphClkInit->I2c2ClockSelection);
  }

  /*-------------------------- I3C2 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I3C2) == RCC_PERIPHCLK_I3C2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I3C2CLKSOURCE(PeriphClkInit->I3c2ClockSelection));

    /* Configure the I3C2 clock source */
    __HAL_RCC_I3C2_CONFIG(PeriphClkInit->I3c2ClockSelection);
  }

  /*-------------------------- SPI2 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI2) == RCC_PERIPHCLK_SPI2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI2CLKSOURCE(PeriphClkInit->Spi2ClockSelection));

    /* Configure the SPI2 clock source */
    __HAL_RCC_SPI2_CONFIG(PeriphClkInit->Spi2ClockSelection);
  }

  /*-------------------------- LPTIM2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM2) == (RCC_PERIPHCLK_LPTIM2))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM2CLKSOURCE(PeriphClkInit->Lptim2ClockSelection));

    /* Configure the LPTIM2 clock source */
    __HAL_RCC_LPTIM2_CONFIG(PeriphClkInit->Lptim2ClockSelection);
  }

  /*-------------------------- SPI1 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI1) == RCC_PERIPHCLK_SPI1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI1CLKSOURCE(PeriphClkInit->Spi1ClockSelection));

    /* Configure the SPI1 clock source */
    __HAL_RCC_SPI1_CONFIG(PeriphClkInit->Spi1ClockSelection);
  }

  /*-------------------------- SYSTICK clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SYSTICK) == RCC_PERIPHCLK_SYSTICK)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SYSTICKCLKSOURCE(PeriphClkInit->SystickClockSelection));

    /* Configure the SYSTICK clock source */
    __HAL_RCC_SYSTICK_CONFIG(PeriphClkInit->SystickClockSelection);
  }

  /*-------------------------- FDCAN clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_FDCAN) == RCC_PERIPHCLK_FDCAN)
  {
    /* Check the parameters */
    assert_param(IS_RCC_FDCANCLKSOURCE(PeriphClkInit->FdcanClockSelection));

    /* Configure the FDCAN1 clock source */
    __HAL_RCC_FDCAN_CONFIG(PeriphClkInit->FdcanClockSelection);
  }

  /*-------------------------- ICLK clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ICLK) == RCC_PERIPHCLK_ICLK)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ICLKCLKSOURCE(PeriphClkInit->IclkClockSelection));

    /* Set the source of ICLK clock*/
    __HAL_RCC_ICLK_CONFIG(PeriphClkInit->IclkClockSelection);
  }

  /*-------------------------- USB1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USB1) == RCC_PERIPHCLK_USB1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USB1CLKSOURCE(PeriphClkInit->Usb1ClockSelection));

    /* Set the source of USB1 clock*/
    __HAL_RCC_USB1_CONFIG(PeriphClkInit->Usb1ClockSelection);
  }

  /*-------------------------- TIMIC clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIMIC) == RCC_PERIPHCLK_TIMIC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIMICCLKSOURCE(PeriphClkInit->TimIcClockSelection));

    /* Configure the TIMIC clock source */
    __HAL_RCC_TIMIC_CONFIG(PeriphClkInit->TimIcClockSelection);
  }

  /*-------------------------- ADF1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADF1) == RCC_PERIPHCLK_ADF1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADF1CLKSOURCE(PeriphClkInit->Adf1ClockSelection));

    /* Set the source of ADF1 clock*/
    __HAL_RCC_ADF1_CONFIG(PeriphClkInit->Adf1ClockSelection);
  }

  /*-------------------------- SPI3 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI3) == RCC_PERIPHCLK_SPI3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI3CLKSOURCE(PeriphClkInit->Spi3ClockSelection));

    /* Configure the SPI3 clock source */
    __HAL_RCC_SPI3_CONFIG(PeriphClkInit->Spi3ClockSelection);
  }

  /*-------------------------- SAI1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI1) == RCC_PERIPHCLK_SAI1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SAI1CLKSOURCE(PeriphClkInit->Sai1ClockSelection));

    /* Set the source of SAI1 clock*/
    __HAL_RCC_SAI1_CONFIG(PeriphClkInit->Sai1ClockSelection);
  }

  /*-------------------------- RNG clock source configuration -------------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RNG) == RCC_PERIPHCLK_RNG)
  {
    /* Check the parameters */
    assert_param(IS_RCC_RNGCLKSOURCE(PeriphClkInit->RngClockSelection));

    /* Set the source of RNG clock*/
    __HAL_RCC_RNG_CONFIG(PeriphClkInit->RngClockSelection);
  }

  /*-------------------------- ADCDAC clock source configuration ----------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADCDAC) == RCC_PERIPHCLK_ADCDAC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCDACCLKSOURCE(PeriphClkInit->AdcDacClockSelection));
    assert_param(IS_RCC_ADCDAC_DIV(PeriphClkInit->AdcDacClockDivider));

    /* Configure the ADC12 and DAC1 interface clock source */
    __HAL_RCC_ADCDAC_CONFIG(PeriphClkInit->AdcDacClockSelection);

    /* Configure the ADC12 and DAC1 interface clock divider */
    __HAL_RCC_ADCDAC_DIV_CONFIG(PeriphClkInit->AdcDacClockDivider);
  }

  /*-------------------------- DAC1SH clock source configuration ----------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_DAC1SH) == RCC_PERIPHCLK_DAC1SH)
  {
    /* Check the parameters */
    assert_param(IS_RCC_DAC1SHCLKSOURCE(PeriphClkInit->Dac1SampleHoldClockSelection));

    /* Configure the DAC1 sample and hold interface clock source */
    __HAL_RCC_DAC1SH_CONFIG(PeriphClkInit->Dac1SampleHoldClockSelection);
  }

  /*-------------------------- OCTOSPI1 clock source configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_OCTOSPI1) == RCC_PERIPHCLK_OCTOSPI1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_OCTOSPICLKSOURCE(PeriphClkInit->Octospi1ClockSelection));

    /* Configure the OCTOSPI1 clock source */
    __HAL_RCC_OCTOSPI_CONFIG(PeriphClkInit->Octospi1ClockSelection);
  }

  /*-------------------------- LPUART1 clock source configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(PeriphClkInit->Lpuart1ClockSelection));

    /* Configure the LPUART1 clock source */
    __HAL_RCC_LPUART1_CONFIG(PeriphClkInit->Lpuart1ClockSelection);
  }

  /*-------------------------- I2C3 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(PeriphClkInit->I2c3ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(PeriphClkInit->I2c3ClockSelection);
  }

  /*-------------------------- LPTIM34 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM34) == (RCC_PERIPHCLK_LPTIM34))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM34CLKSOURCE(PeriphClkInit->Lptim34ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_LPTIM34_CONFIG(PeriphClkInit->Lptim34ClockSelection);
  }

  /*-------------------------- LPTIM1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == (RCC_PERIPHCLK_LPTIM1))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));

    /* Configure the LPTIM1 clock source */
    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }

#if defined(USART2)
  /*-------------------------- USART2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(PeriphClkInit->Usart2ClockSelection));

    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(PeriphClkInit->Usart2ClockSelection);
  }
#endif /* USART2 */

#if defined(I2C4)
  /*-------------------------- I2C4 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C4) == RCC_PERIPHCLK_I2C4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C4CLKSOURCE(PeriphClkInit->I2c4ClockSelection));

    /* Configure the I3C1 clock source */
    __HAL_RCC_I2C4_CONFIG(PeriphClkInit->I2c4ClockSelection);
  }
#endif /* I2C4 */

#if defined(SPI4)
  /*-------------------------- SPI4 clock source configuration ----------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI4) == RCC_PERIPHCLK_SPI4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI4CLKSOURCE(PeriphClkInit->Spi4ClockSelection));

    /* Configure the SPI4 clock source */
    __HAL_RCC_SPI4_CONFIG(PeriphClkInit->Spi4ClockSelection);
  }
#endif /* SPI4 */

  /*-------------------------- RTC clock source configuration ----------------------*/
  if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
  {
    /* Check for RTC Parameters used to output RTCCLK */
    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    /* Reset the Backup domain only if the RTC Clock source selection is different then axisting one */
    tmpreg1 = RCC->BDCR;
    tmpreg2 = (RCC->BDCR & RCC_BDCR_RTCSEL);

    /* Check if RTC clock source needs to be changed */
    if (tmpreg2 != PeriphClkInit->RTCClockSelection)
    {
      FlagStatus       pwrclkchanged = RESET;

      /* Enable Power Clock */
      if (__HAL_RCC_PWR_IS_CLK_ENABLED() != 0x01u)
      {
        __HAL_RCC_PWR_CLK_ENABLE();
        pwrclkchanged = SET;
      }

      /* Enable write access to Backup domain */
      SET_BIT(PWR->DBPR, PWR_DBPR_DBP);

      /* Check if a backup domain reset is required */
      if (tmpreg2 != RCC_RTCCLKSOURCE_DISABLE)
      {
        /* RTC Clock selection can be changed only if the Backup Domain is reset */
        __HAL_RCC_BACKUPRESET_FORCE();
        __HAL_RCC_BACKUPRESET_RELEASE();
      }

      /* Apply new RTC clock source selection */
      tmpreg1 &= ~(RCC_BDCR_RTCSEL | RCC_BDCR_RTCEN);

      /* Check is RTC disable is asked */
      if (PeriphClkInit->RTCClockSelection != RCC_RTCCLKSOURCE_DISABLE)
      {
        tmpreg1 |= (RCC_BDCR_RTCEN | PeriphClkInit->RTCClockSelection);
      }
      RCC->BDCR = tmpreg1;

      /* Check if an oscillator was enable */
      if ((tmpreg1 & RCC_BDCR_LSEON) != 0x00u)
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till LSE is ready */
        while (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0x00u)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            if (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0x00u)
            {
              return HAL_TIMEOUT;
            }
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

  return HAL_OK;
}


/**
  * @brief  Get the peripheral kernel clock configuration.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for all existing peripheral kernel clocks. (*)
  * @note   (*) Peripherals are not available on all devices
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef *PeriphClkInit)
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

  /* Get the USART3 clock source ---------------------------------------------*/
  PeriphClkInit->Usart3ClockSelection = (tmpreg & RCC_CCIPR1_USART3SEL);

  /* Get the UART4 clock source ----------------------------------------------*/
  PeriphClkInit->Uart4ClockSelection = (tmpreg & RCC_CCIPR1_UART4SEL);

  /* Get the UART5 clock source ----------------------------------------------*/
  PeriphClkInit->Uart5ClockSelection = (tmpreg & RCC_CCIPR1_UART5SEL);

  /* Get the I3C1 clock source -----------------------------------------------*/
  PeriphClkInit->I3c1ClockSelection = (tmpreg & RCC_CCIPR1_I3C1SEL);

  /* Get the I2C1 clock source -----------------------------------------------*/
  PeriphClkInit->I2c1ClockSelection = (tmpreg & RCC_CCIPR1_I2C1SEL);

  /* Get the I2C2 clock source -----------------------------------------------*/
  PeriphClkInit->I2c2ClockSelection = (tmpreg & RCC_CCIPR1_I2C2SEL);

  /* Get the I3C2 clock source -----------------------------------------------*/
  PeriphClkInit->I3c2ClockSelection = (tmpreg & RCC_CCIPR1_I3C2SEL);

  /* Get the SPI2 clock source -----------------------------------------------*/
  PeriphClkInit->Spi2ClockSelection = (tmpreg & RCC_CCIPR1_SPI2SEL);

  /* Get the LPTIM2 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim2ClockSelection = (tmpreg & RCC_CCIPR1_LPTIM2SEL);

  /* Get the SPI1 clock source -----------------------------------------------*/
  PeriphClkInit->Spi1ClockSelection = (tmpreg & RCC_CCIPR1_SPI1SEL);

  /* Get the SYSTICK clock source --------------------------------------------*/
  PeriphClkInit->SystickClockSelection = (tmpreg & RCC_CCIPR1_SYSTICKSEL);

  /* Get the FDCAN clock source ---------------------------------------------*/
  PeriphClkInit->FdcanClockSelection = (tmpreg & RCC_CCIPR1_FDCANSEL);

  /* Get the ICLK clock source -----------------------------------------------*/
  PeriphClkInit->IclkClockSelection = (tmpreg & RCC_CCIPR1_ICLKSEL);

  /* Get the USB1 clock source -----------------------------------------------*/
  PeriphClkInit->Usb1ClockSelection = (tmpreg & RCC_CCIPR1_USB1SEL);

  /* Get the TIMIC clock source ----------------------------------------------*/
  PeriphClkInit->TimIcClockSelection = (tmpreg & RCC_CCIPR1_TIMICSEL);

  /* Get CCIPR2 register value */
  tmpreg = RCC->CCIPR2;

  /* Get the ADF1 clock source -----------------------------------------------*/
  PeriphClkInit->Adf1ClockSelection = (tmpreg & RCC_CCIPR2_ADF1SEL);

  /* Get the SPI3 clock source -----------------------------------------------*/
  PeriphClkInit->Spi3ClockSelection = (tmpreg & RCC_CCIPR2_SPI3SEL);

  /* Get the SAI1 clock source -----------------------------------------------*/
  PeriphClkInit->Sai1ClockSelection = (tmpreg & RCC_CCIPR2_SAI1SEL);

  /* Get the RNG clock source ------------------------------------------------*/
  PeriphClkInit->RngClockSelection = (tmpreg & RCC_CCIPR2_RNGSEL);

  /* Get the ADC DAC clock divider -------------------------------------------*/
  PeriphClkInit->AdcDacClockDivider = (tmpreg & RCC_CCIPR2_ADCDACPRE);

  /* Get the ADC DAC clock source --------------------------------------------*/
  PeriphClkInit->AdcDacClockSelection = (tmpreg & RCC_CCIPR2_ADCDACSEL);

  /* Get the DAC Sample and hold clock source --------------------------------*/
  PeriphClkInit->Dac1SampleHoldClockSelection = (tmpreg & RCC_CCIPR2_DAC1SHSEL);

  /* Get the OCTOSPI1 clock source --------------------------------------------*/
  PeriphClkInit->Octospi1ClockSelection = (tmpreg & RCC_CCIPR2_OCTOSPISEL);

  /* Get CCIPR3 register value */
  tmpreg = RCC->CCIPR3;

  /* Get the LPUART1 clock source --------------------------------------------*/
  PeriphClkInit->Lpuart1ClockSelection = (tmpreg & RCC_CCIPR3_LPUART1SEL);

  /* Get the I2C3 clock source -----------------------------------------------*/
  PeriphClkInit->I2c3ClockSelection = (tmpreg & RCC_CCIPR3_I2C3SEL);

  /* Get the LPTIM34 clock source --------------------------------------------*/
  PeriphClkInit->Lptim34ClockSelection = (tmpreg & RCC_CCIPR3_LPTIM34SEL);

  /* Get the LPTIM1 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim1ClockSelection = (tmpreg & RCC_CCIPR3_LPTIM1SEL);

#if defined(USART2)
  /* Get the USART2 clock source ---------------------------------------------*/
  PeriphClkInit->Usart2ClockSelection = (tmpreg & RCC_CCIPR2_USART2SEL);
#endif /* USART2 */

#if defined(I2C4)
  /* Get the I2C4 clock source ---------------------------------------------*/
  PeriphClkInit->I2c4ClockSelection = (tmpreg & RCC_CCIPR2_I2C4SEL);
#endif /* I2C4 */

#if defined(SPI4)
  /* Get the SPI4 clock source ---------------------------------------------*/
  PeriphClkInit->Spi4ClockSelection = (tmpreg & RCC_CCIPR2_SPI4SEL);
#endif /* SPI4 */

  /* Get BDCR register value */
  tmpreg = RCC->BDCR;

  /* Get the RTC clock source ------------------------------------------------*/
  PeriphClkInit->RTCClockSelection = (tmpreg & RCC_BDCR_RTCSEL);
}


/**
  * @brief  Return the peripheral clock frequency for peripherals
  * @note   Return 0 if peripheral clock identifier not managed by this API or
  *         if clock source is turned off.
  * @note   MISRAC2012-Rule-17.2_a waiver has been granted as function is
  *         intentionally calls itself when a peripheral kernel clock frequency
  *         depends on other peripheral kernel clock. Recursion is limited to
  *         only one call.
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1   USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART3   USART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART4    UART4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART5    UART5 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I3C1     I3C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1     I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2     I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I3C2     I3C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI2     SPI2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2   LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI1     SPI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SYSTICK  SYSTICK peripheral clock
  *            @arg @ref RCC_PERIPHCLK_FDCAN    FDCAN peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ICLK     ICLK peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USB1     USB1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_TIMIC    TIMIC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADF1     ADF1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3     SPI3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1     SAI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RNG      RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADCDAC   ADCDAC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_DAC1SH   DAC1SH peripheral clock
  *            @arg @ref RCC_PERIPHCLK_OCTOSPI1 OCTOSPI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3     I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM34  LPTIM34 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1   LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2   USART2 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_I2C4     I2C4 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_SPI4     SPI4 peripheral clock (*)
  *            @arg @ref RCC_PERIPHCLK_RTC      RTC peripheral clock
  *
  *            (*) value not defined in all devices.
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
      else /* srcclk == RCC_USART1CLKSOURCE_HSI */
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_USART3:
      /* Get the current USART3 source */
      srcclk = __HAL_RCC_GET_USART3_SOURCE();

      if (srcclk == RCC_USART3CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else  /* srcclk == RCC_USART3CLKSOURCE_HSI */
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_UART4:
      /* Get the current UART4 source */
      srcclk = __HAL_RCC_GET_UART4_SOURCE();

      if (srcclk == RCC_UART4CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_UART4CLKSOURCE_HSI */
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_UART5:
      /* Get the current UART5 source */
      srcclk = __HAL_RCC_GET_UART5_SOURCE();

      if (srcclk == RCC_UART5CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_UART5CLKSOURCE_HSI */
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_I3C1:
      /* Get the current I3C1 source */
      srcclk = __HAL_RCC_GET_I3C1_SOURCE();

      if (srcclk == RCC_I3C1CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_I3C1CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_I2C1:
      /* Get the current I2C1 source */
      srcclk = __HAL_RCC_GET_I2C1_SOURCE();

      if (srcclk == RCC_I2C1CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_I2C1CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_I2C2:
      /* Get the current I2C2 source */
      srcclk = __HAL_RCC_GET_I2C2_SOURCE();

      if (srcclk == RCC_I2C2CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_I2C2CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_I3C2:
      /* Get the current I3C2 source */
      srcclk = __HAL_RCC_GET_I3C2_SOURCE();

      if (srcclk == RCC_I3C2CLKSOURCE_PCLK2)
      {
        frequency = HAL_RCC_GetPCLK2Freq();
      }
      else /* srcclk == RCC_I3C2CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_SPI2:
      /* Get the current SPI2 kernel source */
      srcclk = __HAL_RCC_GET_SPI2_SOURCE();

      if (srcclk == RCC_SPI2CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_SPI2CLKSOURCE_MSIK */
      {
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

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
        if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
          {
            frequency /= 128U;
          }
        }
      }
      else if (srcclk == RCC_LPTIM2CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else /* srcclk == RCC_LPTIM2CLKSOURCE_LSE */
      {
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_SPI1:
      /* Get the current SPI1 kernel source */
      srcclk = __HAL_RCC_GET_SPI1_SOURCE();

      if (srcclk == RCC_SPI1CLKSOURCE_PCLK2)
      {
        frequency = HAL_RCC_GetPCLK2Freq();
      }
      else /* srcclk == RCC_SPI1CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_SYSTICK:
      /* Get the current SYSTICK kernel source */
      srcclk = __HAL_RCC_GET_SYSTICK_SOURCE();

      if (srcclk == RCC_SYSTICKCLKSOURCE_HCLK_DIV8)
      {
        frequency = (HAL_RCC_GetHCLKFreq() / 8u);
      }
      else if (srcclk == RCC_SYSTICKCLKSOURCE_LSE)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      else if (srcclk == RCC_SYSTICKCLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
          {
            frequency /= 128u;
          }
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    case RCC_PERIPHCLK_FDCAN:
      /* Get the current FDCAN source */
      srcclk = __HAL_RCC_GET_FDCAN_SOURCE();

      if (srcclk == RCC_FDCANCLKSOURCE_MSIK)
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      else /* srcclk == RCC_FDCANCLKSOURCE_SYSCLK */
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      break;

    case RCC_PERIPHCLK_ICLK:
      /* Get the current ICLK source */
      srcclk = __HAL_RCC_GET_ICLK_SOURCE();

      if (srcclk == RCC_ICLKCLKSOURCE_HSI48)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSI48RDY))
        {
          frequency = HSI48_VALUE;
        }
      }
      else if (srcclk == RCC_ICLKCLKSOURCE_MSIK)
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      else if (srcclk == RCC_ICLKCLKSOURCE_HSE)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = HSE_VALUE;
        }
      }
      else /* srcclk == RCC_ICLKCLKSOURCE_SYSCLK */
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      break;

    case RCC_PERIPHCLK_USB1:
      /* Compute Intermediate clock frequency */
      frequency = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_ICLK);

      /* Get the current USB1 source */
      srcclk = __HAL_RCC_GET_USB1_SOURCE();

      if (srcclk == RCC_USB1CLKSOURCE_ICLK_DIV2)
      {
        frequency = (frequency >> 1u);
      }
      break;

    case RCC_PERIPHCLK_ADF1:
      /* Get the current ADF1 source */
      srcclk = __HAL_RCC_GET_ADF1_SOURCE();

      if (srcclk == RCC_ADF1CLKSOURCE_HCLK)
      {
        frequency = HAL_RCC_GetHCLKFreq();
      }
      else if (srcclk == RCC_ADF1CLKSOURCE_PIN)
      {
        frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      }
      else if (srcclk == RCC_ADF1CLKSOURCE_MSIK)
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      else /* srcclk == RCC_ADF1CLKSOURCE_SAI1K */
      {
        /* Compute SAI1 frequency */
        frequency = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SAI1);
      }
      break;

    case RCC_PERIPHCLK_SPI3:
      /* Get the current SPI3 kernel source */
      srcclk = __HAL_RCC_GET_SPI3_SOURCE();

      if (srcclk == RCC_SPI3CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_SPI3CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_SAI1:
      /* Get the current SAI1 source */
      srcclk = __HAL_RCC_GET_SAI1_SOURCE();

      if (srcclk == RCC_SAI1CLKSOURCE_MSIK)
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      else if (srcclk == RCC_SAI1CLKSOURCE_PIN)
      {
        frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      }
      else if (srcclk == RCC_SAI1CLKSOURCE_HSE)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = HSE_VALUE;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    case RCC_PERIPHCLK_RNG:
      /* Get the current RNG source */
      srcclk = __HAL_RCC_GET_RNG_SOURCE();

      if (srcclk == RCC_RNGCLKSOURCE_HSI48)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSI48RDY))
        {
          frequency = HSI48_VALUE;
        }
      }
      else /* srcclk == RCC_RNGCLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_ADCDAC:
      /* Get the current ADC DAC kernel source */
      srcclk = __HAL_RCC_GET_ADCDAC_SOURCE();

      if (srcclk == RCC_ADCDACCLKSOURCE_HCLK)
      {
        frequency = HAL_RCC_GetHCLKFreq();
      }
      else if (srcclk == RCC_ADCDACCLKSOURCE_HSE)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = HSE_VALUE;
        }
      }
      else if (srcclk == RCC_ADCDACCLKSOURCE_MSIK)
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }

      /* Get the current ADC DAC clock divider source */
      srcclk = __HAL_RCC_GET_ADCDAC_DIV();

      if (srcclk == RCC_ADCDACCLK_DIV1)
      {
        /* No divider selected */
        srcclk = 0u;
      }
      else if (srcclk < RCC_CCIPR2_ADCDACPRE_3)
      {
        /* divider is 2 */
        srcclk = 1u;
      }
      else
      {
        /* compute divider */
        srcclk = ((srcclk & ~RCC_CCIPR2_ADCDACPRE_3) >> RCC_CCIPR2_ADCDACPRE_Pos) + 2u;
      }

      /* Compute frequency */
      frequency = (frequency >> srcclk);
      break;

    case RCC_PERIPHCLK_DAC1SH:
      /* Get the current ADC kernel source */
      srcclk = __HAL_RCC_GET_DAC1SH_SOURCE();

      if (srcclk == RCC_DAC1SHCLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
          {
            frequency /= 128u;
          }
        }
      }
      else /* srcclk == RCC_DAC1SHCLKSOURCE_LSE */
      {
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_OCTOSPI1:
      /* Get the current OCTOSPI1 source */
      srcclk = __HAL_RCC_GET_OCTOSPI_SOURCE();

      if (srcclk == RCC_OCTOSPICLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else /* srcclk == RCC_OCTOSPICLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_LPUART1:
      /* Get the current LPUART1 source */
      srcclk = __HAL_RCC_GET_LPUART1_SOURCE();

      if (srcclk == RCC_LPUART1CLKSOURCE_PCLK3)
      {
        frequency = HAL_RCC_GetPCLK3Freq();
      }
      else if (srcclk == RCC_LPUART1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else if (srcclk == RCC_LPUART1CLKSOURCE_LSE)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      else /* srcclk == RCC_LPUART1CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_I2C3:
      /* Get the current I2C3 source */
      srcclk = __HAL_RCC_GET_I2C3_SOURCE();

      if (srcclk == RCC_I2C3CLKSOURCE_PCLK3)
      {
        frequency = HAL_RCC_GetPCLK3Freq();
      }
      else /* srcclk == RCC_I2C3CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;

    case RCC_PERIPHCLK_LPTIM34:
      /* Get the current LPTIM34 source */
      srcclk = __HAL_RCC_GET_LPTIM34_SOURCE();

      if (srcclk == RCC_LPTIM34CLKSOURCE_MSIK)
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      else if (srcclk == RCC_LPTIM34CLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
          {
            frequency /= 128u;
          }
        }
      }
      else if (srcclk == RCC_LPTIM34CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else /* srcclk == RCC_LPTIM34CLKSOURCE_LSE */
      {
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;

    case RCC_PERIPHCLK_LPTIM1:
      /* Get the current LPTIM1 source */
      srcclk = __HAL_RCC_GET_LPTIM1_SOURCE();

      if (srcclk == RCC_LPTIM1CLKSOURCE_MSIK)
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      else if (srcclk == RCC_LPTIM1CLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
          {
            frequency /= 128u;
          }
        }
      }
      else if (srcclk == RCC_LPTIM1CLKSOURCE_HSI)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      else /* srcclk == RCC_LPTIM1CLKSOURCE_LSE */
      {
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      break;

#if defined(USART2)
    case RCC_PERIPHCLK_USART2:
      /* Get the current USART2 source */
      srcclk = __HAL_RCC_GET_USART2_SOURCE();

      if (srcclk == RCC_USART2CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else  /* srcclk == RCC_USART2CLKSOURCE_HSI */
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
        {
          frequency = HSI_VALUE;
        }
      }
      break;
#endif /* USART2 */

#if defined(I2C4)
    case RCC_PERIPHCLK_I2C4:
      /* Get the current I2C4 source */
      srcclk = __HAL_RCC_GET_I2C4_SOURCE();

      if (srcclk == RCC_I2C4CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_I2C4CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;
#endif /* I2C4 */

#if defined(SPI4)
    case RCC_PERIPHCLK_SPI4:
      /* Get the current SPI4 kernel source */
      srcclk = __HAL_RCC_GET_SPI4_SOURCE();

      if (srcclk == RCC_SPI4CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else /* srcclk == RCC_SPI3CLKSOURCE_MSIK */
      {
        /* Do not check RDY flag as done in get frequency API */
        frequency = HAL_RCC_GetMSIKFreq();
      }
      break;
#endif /* SPI4 */

    case RCC_PERIPHCLK_RTC:
      /* Get the current RTC source */
      srcclk = __HAL_RCC_GET_RTC_SOURCE();

      /* Check if LSE is ready and if RTC clock selection is LSE */
      if (srcclk == RCC_RTCCLKSOURCE_LSE)
      {
        if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))
        {
          frequency = LSE_VALUE;
        }
      }
      /* Check if LSI1 or LIS2 is ready and if RTC clock selection is LSI */
      else if (srcclk == RCC_RTCCLKSOURCE_LSI)
      {
        if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY))
        {
          /* LSI Frequency */
          frequency = LSI_VALUE;

          /* Check is LSI1 is divided */
          if (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIPREDIV))
          {
            frequency /= 128u;
          }
        }
      }
      /* Check if HSE is ready and if RTC clock selection is HSE_DIV32*/
      else if (srcclk == RCC_RTCCLKSOURCE_HSE_DIV32)
      {
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
        {
          frequency = HSE_VALUE / 32u;
        }
      }
      else
      {
        /* Do nothing ; for misra 15.7 error only */
      }
      break;

    /* Do nothing for Timer input capture as clock source is selected in timer block */
    case RCC_PERIPHCLK_TIMIC:
    default:
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
    [..] This subsection provides a set of functions allowing to control:

         (+) EPOD Booster clock configuration.
         (+) MSI RC PLL mode.
         (+) SYSCLK source on wakeup from STOP.
         (+) Automatic kernel clock startup on wakeup from STOP.
         (+) Capability to keep kernel clock on in stop.
         (+) MSIS and MSIK clock frequency at standby exit.
         (+) Activation or deactivation of LSE CSS.
         (+) Activation or deactivation of Low Speed Clock Output (LSCO).
@endverbatim
  * @{
  */

/**
  * @brief  Configure EPOD Booster clock.
  * @param  Source    The EPOD booster clock source.
                      This parameter can be a value of @ref RCC_EPOD_Booster_Source
  * @param  Divider   The division factor of EPOD booster clock.
                      This parameter can be a value of @ref RCC_EPOD_Booster_Div
  * @note   Clock source and divider shall be selected to reach an input Booster Clock between 3 and 16 MHz.
  * @note   If MSI is selected as EPOD source, divider is automatically chosen by hardware. Thus Divider parameter
  *         will be ignored
  * @note   When booster is not user, clock source shall be set to RCC_EPODBOOSTER_SOURCE_NONE to save power.
  * @retval None
  */
HAL_StatusTypeDef HAL_RCCEx_EpodBoosterClkConfig(uint32_t Source, uint32_t Divider)
{
  uint32_t tmpreg1;
  HAL_StatusTypeDef status;

  assert_param(IS_RCC_EPODBOOSTER_SOURCE(Source));
  assert_param(IS_RCC_EPODBOOSTER_DIV(Divider));

  /* check if any source is selected and ready */
  tmpreg1 = RCC->CR;

  /* MSIS is selected as EPOD Booster clock source, check if MSIS is ready */
  if ((Source == RCC_EPODBOOSTER_SOURCE_MSIS) && ((tmpreg1 & RCC_CR_MSISRDY) == 0U))
  {
    status = HAL_ERROR;
  }
  /* HSI is selected as EPOD Booster clock source, check if HSI is ready */
  else if ((Source == RCC_EPODBOOSTER_SOURCE_HSI) && ((tmpreg1 & RCC_CR_HSIRDY) == 0U))
  {
    status = HAL_ERROR;
  }
  /* HSE is selected as EPOD Booster clock source, check if HSE is ready */
  else if ((Source == RCC_EPODBOOSTER_SOURCE_HSE) && ((tmpreg1 & RCC_CR_HSERDY) == 0U))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Apply configuration */
    tmpreg1 = (RCC->CFGR4 & ~(RCC_CFGR4_BOOSTDIV | RCC_CFGR4_BOOSTSEL));
    tmpreg1 |= (Divider | Source);
    RCC->CFGR4 = tmpreg1;

    /* update status is ok */
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Get EPOD clock configuration.
  * @param  Source    Pointer to EPOD booster clock source value.
  * @param  Divider   Pointer to EPOD booster clock divider value.
  * @retval None
  */
void HAL_RCCEx_GetEpodBoosterClkConfig(uint32_t *Source, uint32_t *Divider)
{
  uint32_t tmpreg1;

  /* Get booster clock configuration */
  tmpreg1 = RCC->CFGR4;

  /* Retrieve source and divider */
  *Source = (tmpreg1 & RCC_CFGR4_BOOSTSEL);
  *Divider = (tmpreg1 & RCC_CFGR4_BOOSTDIV);
}

/**
  * @brief  Configure MSIRCx PLL mode.
  * @param  MSISrce   MSIRC source to configure in PLL mode.
  *         This parameter can be a value of @ref RCC_MSI_Source
  * @param  RCxPLLMode  pointer to an RCC_MSIRCxPLLTypeDef structure that
  *         contains the configuration information for MSIRCx PLL mode.
  * @note   If HSE is selected as PLL input source for both MSIRCx, it shall be kept with same divider (1 or 2).
  * @note   For MSI RC1, PLL multiplication factor N shall be set wisely. Else, this field can be left empty.
  * @retval None
  */
HAL_StatusTypeDef HAL_RCCEx_MSIRCxPLLModeConfig(uint32_t MSISrce, const RCC_MSIRCxPLLTypeDef *RCxPLLMode)
{
  uint32_t tmpcr;
  uint32_t tmpicscr1;
  uint32_t offset;
  uint32_t mask;

  /* Check Null pointer */
  if (RCxPLLMode == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_MSI_SOURCE(MSISrce));
  assert_param(IS_RCC_MSI_PLL(RCxPLLMode->State));

  if (MSISrce != RCC_MSI_RC0)
  {
    offset = 0x00u;
  }
  else
  {
    offset = 0x01u;
  }

  /* Read configuration register */
  tmpcr = RCC->CR;

  /* Compute activation mask */
  mask = (1uL << (RCC_CR_MSIPLL1EN_Pos + offset));

  /* check if PLL mode is asked to be enabled or disabled */
  if (RCxPLLMode->State != RCC_MSIRCx_PLL_OFF)
  {
    assert_param(IS_RCC_MSI_PLL_INPUT(RCxPLLMode->InputSrce));
    assert_param(IS_RCC_MSI_PLL_FASTMODE(RCxPLLMode->FastMode));

    /* Configure PLL input source */
    tmpicscr1 = RCC->ICSCR1;

    /* Set PLL input source */
    tmpicscr1 &= ~(RCC_ICSCR1_MSIPLL1SEL << offset);
    tmpicscr1 |= ((RCxPLLMode->InputSrce & RCC_ICSCR1_MSIPLL1SEL) << offset);

    /* Check if PLL source is HSE */
    if ((RCxPLLMode->InputSrce & RCC_ICSCR1_MSIPLL1SEL) != 0x00u)
    {
      assert_param(IS_RCC_MSI_PLL_INPUT_HSE_FREQ(HSE_VALUE));

      /* Clear or set HSE source divider */
      if (HSE_VALUE != RCC_MSIRCx_PLL_INPUT_HSE32)
      {
        tmpicscr1 &= ~RCC_ICSCR1_MSIHSINDIV;
      }
      else
      {
        tmpicscr1 |= RCC_ICSCR1_MSIHSINDIV;
      }
    }

    /* Check if RC1 is being configured */
    if (MSISrce != RCC_MSI_RC0)
    {
      assert_param(IS_RCC_MSI_PLL_NVALUE(RCxPLLMode->MSIRC1PLLN));

      /* Adjust PLL N multiplication factor */
      tmpicscr1 &= ~RCC_ICSCR1_MSIPLL1N;
      tmpicscr1 |= RCxPLLMode->MSIRC1PLLN;
    }

    /* Write configuration */
    RCC->ICSCR1 = tmpicscr1;

    /* Configure PLL fast mode */
    tmpcr &= ~(1uL << (RCC_CR_MSIPLL1FAST_Pos + offset));
    tmpcr |= (RCxPLLMode->FastMode << offset);

    /* Enable PLL mode for selected RC */
    tmpcr |= mask;
  }
  else
  {
    /* Disable PLL mode for selected RC */
    tmpcr &= ~mask;
  }

  /* Write configuration register */
  RCC->CR = tmpcr;

  /* Compute ready flag data */
  mask <<= (RCC_CR_MSIPLL1RDY_Pos - RCC_CR_MSIPLL1EN_Pos);
  tmpicscr1 = ((RCxPLLMode->State << (RCC_CR_MSIPLL1RDY_Pos - RCC_CR_MSIPLL1EN_Pos)) << offset);

  /* Get Start Tick*/
  tmpcr = HAL_GetTick();

  /* Wait until ready flag status */
  while (READ_BIT(RCC->CR, mask) != tmpicscr1)
  {
    if ((HAL_GetTick() - tmpcr) > MSI_PLL_TIMEOUT_VALUE)
    {
      if (READ_BIT(RCC->CR, mask) != tmpicscr1)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get MSIRCx PLL mode.
  * @param  MSISrce   MSIRC source to get PLL configuration.
  *         This parameter can be a value of @ref RCC_MSI_Source
  * @param  RCxPLLMode  pointer to an RCC_MSIRCxPLLTypeDef structure that
  *         will return the configuration information for MSIRCx PLL mode.
  * @retval None
  */
void HAL_RCCEx_GetMSIRCxPLLModeConfig(uint32_t MSISrce, RCC_MSIRCxPLLTypeDef *RCxPLLMode)
{
  uint32_t tmpcr;
  uint32_t offset;

  /* Check the parameters */
  assert_param(RCxPLLMode != (void *)NULL);
  assert_param(IS_RCC_MSI_SOURCE(MSISrce));

  if (MSISrce != RCC_MSI_RC0)
  {
    offset = 0x00u;
  }
  else
  {
    offset = 0x01u;
  }

  /* Read configuration register */
  tmpcr = RCC->CR;
  RCxPLLMode->State = ((tmpcr & (1uL << (RCC_CR_MSIPLL1EN_Pos + offset))) >> offset);
  RCxPLLMode->FastMode = ((tmpcr & (1uL << (RCC_CR_MSIPLL1FAST_Pos + offset))) >> offset);

  /* Read ICSCR1 register */
  tmpcr = RCC->ICSCR1;
  RCxPLLMode->InputSrce = ((tmpcr & (1uL << (RCC_ICSCR1_MSIPLL1SEL_Pos + offset))) >> offset);

  /* Check if source is HSE */
  if ((RCxPLLMode->InputSrce & RCC_ICSCR1_MSIPLL1SEL) != 0x00u)
  {
    /* Get HSE divider */
    RCxPLLMode->InputSrce |= (tmpcr & RCC_ICSCR1_MSIHSINDIV);
  }
  else
  {
    /* If MSI source is MSIRC1 */
    if (MSISrce != RCC_MSI_RC0)
    {
      /* Get PLLN multiplication factor */
      RCxPLLMode->MSIRC1PLLN = (tmpcr & RCC_ICSCR1_MSIPLL1N);
    }
  }
}

/**
  * @brief  Configure the system clock source for wakeup from Stop and to be used as emergency clock for the Clock
  *         security system on HSE.
  * @param  WakeupClk  Wakeup clock
  *         This parameter can be one of the following values:
  *            @arg RCC_STOP_WKUP_SYSCLK_MSIS: MSIS oscillator selection
  *            @arg RCC_STOP_WKUP_SYSCLK_HSI:  HSI oscillator selection
  * @note   This function shall not be called after the Clock Security System on HSE has been
  *         enabled.
  * @retval None
  */
void HAL_RCCEx_StopWakeupSysclkConfig(uint32_t WakeupClk)
{
  assert_param(IS_RCC_STOP_WKUP_SYSCLK(WakeupClk));

  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_STOPWUCK, WakeupClk);
}

/**
  * @brief  Configure the Kernel clock source to be automatically enabled when wakeup from Stop.
  * @param  WakeupClk: Kernel Wakeup clock
  *         This parameter can be one of the following values:
  *            @arg RCC_KERNELCLK_MSIK: MSIK oscillator selection
  *            @arg RCC_KERNELCLK_HSI:  HSI oscillator selection
  * @retval None
  */
void HAL_RCCEx_StopWakeupKernelClkConfig(uint32_t WakeupClk)
{
  uint32_t cfgr1;

  assert_param(IS_RCC_KERNEL_CLK(WakeupClk));

  /* Read cfgr1 */
  cfgr1 = RCC->CFGR1;

  /* If selected source is HSI */
  if (WakeupClk == RCC_KERNELCLK_HSI)
  {
    cfgr1 |= RCC_CFGR1_STOPKERWUCK;
  }
  else
  {
    cfgr1 &= ~RCC_CFGR1_STOPKERWUCK;
  }

  /* write cfgr1 */
  RCC->CFGR1 = cfgr1;
}

/**
  * @brief  Enable a kernel clock to be forced ON when entering in STOP.
  *         Keeping a Oscillator on in stop mode allows to speed up communication by removing oscillator startup time.
  * @param  KernelClk  Wakeup clock
  *         This parameter can be a combination of following values:
  *            @arg RCC_KERNELCLK_MSIK: MSIK oscillator selection
  *            @arg RCC_KERNELCLK_HSI:  HSI oscillator selection
  * @note   HSI and MSIK kernel clocks shall be disabled when entering in STOP 3
  *         enabled.
  * @retval None
  */
void HAL_RCCEx_EnableKernelClkInStop(uint32_t KernelClk)
{
  assert_param(IS_RCC_MULTI_KERNEL_CLK(KernelClk));

  RCC->CR |= KernelClk;
}

/**
  * @brief  Disable a kernel clock to be forced ON when entering in STOP.
  * @param  KernelClk  Wakeup clock
  *         This parameter can be a combination of following values:
  *            @arg RCC_KERNELCLK_MSIK: MSIK oscillator selection
  *            @arg RCC_KERNELCLK_HSI:  HSI oscillator selection
  * @note   HSI and MSIK kernel clocks shall be disabled when entering in STOP 3
  *         enabled.
  * @retval None
  */
void HAL_RCCEx_DisableKernelClkInStop(uint32_t KernelClk)
{
  assert_param(IS_RCC_MULTI_KERNEL_CLK(KernelClk));

  RCC->CR &= ~KernelClk;
}


/**
  * @brief  Configure MSIS division at Standby mode exit.
  * @note   After a system reset, a power-on reset or when exiting Shutdown mode, range 5 (MSIRC1, DIV2, 12MHz)
  *         is always selected.
  * @note   API is forcing MSI range selection it, so out the function MSIS frequency will be driven by ICSCR1.
  * @param  MSISDiv  MSIS divider
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_MSI_DIV2  MSIS frequency is around 12 MHz (range 5, reset value)
  *            @arg @ref RCC_MSI_DIV4  MSIS frequency is around 6 MHz (range 6)
  *            @arg @ref RCC_MSI_DIV8  MSIS frequency is around 3 MHz (range 7)
  * @retval None
  */
void HAL_RCCEx_StandbyWakeupMSISConfig(uint32_t MSISDiv)
{
  uint32_t csr;

  assert_param(IS_RCC_MSI_STANDBY_DIV(MSISDiv));

  /* Allow write access to MSIS standby mode */
  RCC->ICSCR1 |= RCC_ICSCR1_MSIRGSEL;

  /* Modify exit from standby MSIS divider selection */
  csr = (RCC->CSR & ~RCC_CSR_MSISDIVS);
  csr |= (MSISDiv >> (RCC_ICSCR1_MSISDIV_Pos - RCC_CSR_MSISDIVS_Pos));
  RCC->CSR = csr;
}

/**
  * @brief  Configure MSIK division at Standby mode exit.
  * @note   After a system reset, a power-on reset or when exiting Shutdown mode, range 5 (MSIRC1, DIV2, 12MHz)
  *         is always selected.
  * @note   API is forcing MSI range selection it, so out the function MSIK frequency will be driven by ICSCR1.
  * @param  MSIKDiv  MSIK divider
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_MSI_DIV2  MSIK frequency is around 12 MHz (range 5, reset value)
  *            @arg @ref RCC_MSI_DIV4  MSIK frequency is around 6 MHz (range 6)
  *            @arg @ref RCC_MSI_DIV8  MSIK frequency is around 3 MHz (range 7)
  * @retval None
  */

void HAL_RCCEx_StandbyWakeupMSIKConfig(uint32_t MSIKDiv)
{
  uint32_t csr;

  assert_param(IS_RCC_MSI_STANDBY_DIV(MSIKDiv));

  /* Allow write access to MSIS standby mode */
  RCC->ICSCR1 |= RCC_ICSCR1_MSIRGSEL;

  /* Modify exit from standby MSIK divider selection */
  csr = (RCC->CSR & ~RCC_CSR_MSIKDIVS);
  csr |= (MSIKDiv >> (RCC_ICSCR1_MSISDIV_Pos - RCC_CSR_MSIKDIVS_Pos));
  RCC->CSR = csr;
}


/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled
  *         with HAL_RCC_OscConfig() and the LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCCEx_PeriphCLKConfig().
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  * @retval None
  */
void HAL_RCCEx_DisableLSECSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
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
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL, LSCOSource | RCC_BDCR_LSCOEN);
}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{
  /* Clear LSCOEN in BDCR register */
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @}
  */


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
           precision after waking up from Sleep mode, reference clock on the GPIOs
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
void HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *pInit)
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
