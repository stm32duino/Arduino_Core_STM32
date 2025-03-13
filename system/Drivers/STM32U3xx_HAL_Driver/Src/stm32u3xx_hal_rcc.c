/**
  ******************************************************************************
  * @file    stm32u3xx_hal_rcc.c
  * @author  MCD Application Team
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
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
  @verbatim
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    [..]
      After reset the device is running from Multi-Speed Internal RC oscillator
      at 12 MHz with Flash 1 wait state. Flash prefetch buffer and I-Cache are
      disabled and all peripherals are off except internal SRAMs, Flash and SWD.
      (+) There is no prescaler on High speed (AHBs) and no prescaler Low speed
          (APBs) busses: all peripherals mapped on these busses are running at
          SYSCLK speed.
      (+) The clock for all peripherals is switched off, except SRAMs and FLASH.
      (+) All GPIOs are in analog mode, except the JTAG pins which
          are assigned to be used for debug purpose.

    [..]
      Once the device started, the user application has to:
      (+) Configure the clock source to be used to drive the System clock
          (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency and Flash settings
      (+) Configure the AHB and APB busses prescalers
      (+) Enable the clock for the peripheral(s) to be used
      (+) Configure the kernel clock source(s) for peripherals which clocks are
          not derived from the System clock.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @brief RCC HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */
/* timeout value */
/* LSI maximum timeout is 16 us plus 4 LSI clock cycles when prediv is used */
#define HSE_TIMEOUT_VALUE               HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE               (2U)    /* 2 ms (minimum Tick + 1) */
#define HSI48_TIMEOUT_VALUE             (2U)    /* 2 ms (minimum Tick + 1) */
#define LSI_TIMEOUT_VALUE               ((5u * 128u * 1000u) / LSI_VALUE)
#define MSI_TIMEOUT_VALUE               (2U)    /* 2 ms (minimum Tick + 1) */
#define CLOCKSWITCH_TIMEOUT_VALUE       5000U     /* 5 s    */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define __MCO_CLK_ENABLE()              __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO_GPIO_PORT                   GPIOA
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
  @verbatim
 ===============================================================================
           ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to configure the internal and external oscillators
      (HSE, HSI, LSE, LSI, MSIS and MSIK, CSS and MCO) and the System busses clocks (SYSCLK,
      AHB1, AHB2, APB1, APB2, APB3).

    [..] Internal/external clock configuration

         (+) HSE (high-speed external): 4 to 50 MHz crystal oscillator that can be used directly
             as System clock source. It can be used also optionally as kernel clock source for peripherals,
             especially as RTC clock source.

         (+) LSE (low-speed external): 32.768 KHz oscillator can be used as peripheral kernel clock
             source, especially as RTC clock source.

         (+) HSI (high-speed internal): 16 MHz factory-trimmed RC that can used directly as System
             clock source and as peripheral kernel clock source.

         (+) LSI (low-speed internal): 32 KHz low consumption RC used as peripheral kernel clock source
             including IWDG and RTC.

         (+) MSIS (multi-speed internal system): 3 to 96 MHz factory-trimmed RC that can used directly as System
             clock source.

         (+) MSIK (multi-speed internal kernem): 3 to 96 MHz factory-trimmed RC that can used as
             peripheral kernel clock source.

         (+) CSS (Clock security system): once enabled, if a HSE clock failure occurs
             and HSE is used directly as System clock source, the System clock
             is automatically switched to HSI and an interrupt is generated if enabled.
             The interrupt is linked to the Cortex-M33 NMI (Non-Maskable Interrupt)
             exception vector.

         (+) MCO (microcontroller clock output): used to output LSI, HSI, LSE, HSE, SYSCLK, clocks
            (through a configurable prescaler) on PA8 pin.

    [..] System, AHB and APB busses clocks configuration
         (+) Several clock sources can be used to drive the System clock (SYSCLK): HSE, HSI, MSIS
             The AHB clock (HCLK) is derived from System clock through configurable
             prescaler and used to clock the CPU, memory and peripherals mapped
             on AHB bus (DMA, GPIO...). APB1 (PCLK1), APB2 (PCLK2) clocks are derived
             from AHB clock through configurable prescalers and used to clock
             the peripherals mapped on these busses. You can use
             @ref HAL_RCC_GetSysClockFreq(), HAL_RCC_GetHCLKFreq, HAL_RCC_GetPCLK1Freq, HAL_RCC_GetPCLK2Freq
             HAL_RCC_GetPCLK3Freq functions to retrieve these clock frequencies.

         -@- All the peripheral kernel clocks are derived from the System clock (SYSCLK) but some
             peripheral can select a different source (you have to use HAL_RCCEx_PeriphCLKConfig()
             function to configure it) :
           (+@) U(S)ARTx (x = 1, 3 , 4, 5) :Kernel clock can be PCLKx or HSI.
           (+@) I3Cx (x = 1, 2) : Kernel clock can be PCLKx or MSIK.
           (+@) I2Cx (x = 1, 2, 3) : Kernel clock can be PCLKx or MSIK.
           (+@) SPIx (x = 1, 2, 3) : Kernel clock can be PCLKx or MSIK.
           (+@) LPTIMx (x = 1, 3, 4) : Kernel clock can be MSIK, LSI, HSI or LSE.
           (+@) LPTIM2 : Kernel clock can be PCLK1, LSI, HSI or LSE.
           (+@) SYSTICK : Kernel clock can be HCLK/8, LSI or LSE when external clock is selected in SysTick.
           (+@) FDCAN : Kernel clock can be SYSCLK or MSIK.
           (+@) ICLK : Kernel clock can be HSI48, MSIK, HSE or SYSCLK.
           (+@) USB1 : Kernel clock can be ICLK or ICLK/2.
           (+@) TIMIC : Kernel clock can be HSI/256, MSIS/1024, MSIS/4, MSIK/1024 or MSIK/4.
           (+@) ADF1 : Kernel clock can be HCLK, AUDIOCLK input pin, MSIK or SAI1.
           (+@) SAI1 : Kernel clock can be MSIK, AUDIOCLK input pin or HSE.
           (+@) RNG : Kernel clock can be HSI48 or MSIK.
           (+@) ADC12 / DAC : Kernel clock can be HCLK, HSE or MSIK. Selected clock can be then divided by 2^x
                              (x = 0 to 9).
           (+@) DAC1SH : Kernel clock can be LSE or LSI.
           (+@) OCTOSPI1 : Kernel clock can be SYSCLK or MSIK.
           (+@) LPUART1 : Kernel clock can be PCLK3, HSI, LSE or MSIK.
           (+@) RTC : Kernel clock can be LSI, LSE or HSE clock divided by 32.

         (+) The maximum frequency of SYSCLK / AHB1 / AHB2 / APB1 / APB2 / APB3 is
              (++) 96 MHz at voltage range 1
              (++) 48 MHZ at voltage range 2
             The clock source frequency should be adapted depending on the device voltage range
             as listed in the Reference Manual "Clock source frequency versus voltage scaling" chapter.

  @endverbatim

           Table 1. Flash latency versus HCLK clock frequency and voltage scaling ranges.
                    when flash low power mode is disabled (LPM = 0)
           +-------------------------------------------------------+
           | Latency         |     HCLK clock frequency (MHz)      |
           |                 |-------------------------------------|
           |                 | voltage range 1  | voltage range 2  |
           |                 |      0.9 V       |      0.75 V      |
           |-----------------|------------------|------------------|
           |0WS(1 CPU cycles)|      HCLK <= 32  |      HCLK <= 16  |
           |-----------------|------------------|------------------|
           |1WS(2 CPU cycles)|      HCLK <= 64  |      HCLK <= 32  |
           |-----------------|------------------|------------------|
           |2WS(3 CPU cycles)|      HCLK <= 96  |      HCLK <= 48  |
           +-----------------+------------------+------------------+

           Table 2. EPOD booster mode versus HCLK clock frequency and voltage scaling ranges.
           +-------------------------------------------------------+
           | EPOD booster    |     HCLK clock frequency (MHz)      |
           |                 |-------------------------------------|
           |                 | voltage range 1  | voltage range 2  |
           |                 |      0.9 V       |      0.75 V      |
           |-----------------|------------------|------------------|
           | Disabled        |      HCLK <= 24  |      HCLK <= 24  |
           |-----------------|------------------|------------------|
           | Enabled         |      HCLK <= 96  |      HCLK <= 48  |
           +-----------------+------------------+------------------+
  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - MSIS & MSIK ON and used as system clock source
  *            - HSE OFF
  *            - AHB1, AHB2, APB1, APB2 and APB3 prescaler set to 1.
  *            - CSS, MCO1 and MCO2 OFF
  *            - All interrupts disabled and cleared
  * @note   This function doesn't modify the configuration of the
  *            - Peripheral clocks
  *            - LSI, LSE and RTC clocks
  * @retval None
  */
HAL_StatusTypeDef HAL_RCC_DeInit(void)
{
  uint32_t tickstart;

  /* Get start tick*/
  tickstart = HAL_GetTick();

  /* Set MSISON and MSIKON bit */
  SET_BIT(RCC->CR, (RCC_CR_MSISON | RCC_CR_MSIKON));

  /* Wait till MSIS is ready */
  while (READ_BIT(RCC->CR, RCC_CR_MSISRDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
    {
      if (READ_BIT(RCC->CR, RCC_CR_MSISRDY) == 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Select MSIS and MSIK source and divider */
  MODIFY_REG(RCC->ICSCR1, (RCC_ICSCR1_MSISDIV | RCC_ICSCR1_MSIKDIV),
             (RCC_ICSCR1_MSISDIV_0 | RCC_ICSCR1_MSISSEL | RCC_ICSCR1_MSIKDIV_0 | RCC_ICSCR1_MSIKSEL));

  /* Set MSRCx trimming default value */
  WRITE_REG(RCC->ICSCR2, (RCC_ICSCR2_MSITRIM1_5 | RCC_ICSCR2_MSITRIM0_5));

  /* Set HSITRIM default value */
  WRITE_REG(RCC->ICSCR3, RCC_ICSCR3_HSITRIM_4);

  /* Get start tick*/
  tickstart = HAL_GetTick();

  /* Reset CFGR1 register (MSIS is selected as system clock source) */
  CLEAR_REG(RCC->CFGR1);

  /* Wait till clock switch is ready */
  while (READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > CLOCKSWITCH_TIMEOUT_VALUE)
    {
      if (READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS) != 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Set AHBx and APBx prescaler to their default values */
  CLEAR_REG(RCC->CFGR2);
  CLEAR_REG(RCC->CFGR3);
  CLEAR_REG(RCC->CFGR4);

  /* Clear CR register in 2 steps: first to clear HSEON in case bypass was enabled */
  RCC->CR = (RCC_CR_MSISON | RCC_CR_MSIKON);

  /* Then again to HSEBYP in case bypass was enabled */
  RCC->CR = (RCC_CR_MSISON | RCC_CR_MSIKON);

  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER);

  /* Clear all interrupts flags */
  WRITE_REG(RCC->CICR, 0xFFFFFFFFU);

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = (MSIRC1_VALUE >> 1u);

  /* Adapt Systick interrupt period */
  if (HAL_InitTick(uwTickPrio) != HAL_OK)
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  Initialize the RCC Oscillators according to the specified parameters in the
  *         RCC_OscInitTypeDef.
  * @param  RCC_OscInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function. User should request a transition to HSE Off
  *         first and then to HSE On or HSE Bypass.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *RCC_OscInitStruct)
{
  uint32_t tickstart;
  uint32_t sysclksrc;
  uint32_t tmpreg1;

  /* Check Null pointer */
  if (RCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

  sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();

  /*------------------------------- HSE Configuration ------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) != 0x00u)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

    /* When the HSE is used as system clock source, it is not allowed to be disabled */
    if (sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSE)
    {
      if (RCC_OscInitStruct->HSEState == RCC_HSE_OFF)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Check the HSE State */
      if (RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        /* Set the new HSE configuration ---------------------------------------*/
        __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Set the new HSE configuration ---------------------------------------*/
        __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is disabled */
        while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  /*----------------------------- HSI Configuration --------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) != 0x00u)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_HSI_CALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

    /* Check if HSI is used as system clock */
    if (sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSI)
    {
      /* When HSI is used as system clock it will not be disabled */
      if (RCC_OscInitStruct->HSIState == RCC_HSI_OFF)
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
    }
    else
    {
      /* Check the HSI State */
      if (RCC_OscInitStruct->HSIState != RCC_HSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_ENABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
      else
      {
        /* Disable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_DISABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is disabled */
        while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  /*------------------------------ HSI48 Configuration -----------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI48) != 0x00u)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI48(RCC_OscInitStruct->HSI48State));

    /* Check the HSI48 State */
    if (RCC_OscInitStruct->HSI48State != RCC_HSI48_OFF)
    {
      /* Enable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_ENABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till HSI48 is ready */
      while (READ_BIT(RCC->CR, RCC_CR_HSI48RDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > HSI48_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_DISABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till HSI48 is disabled */
      while (READ_BIT(RCC->CR, RCC_CR_HSI48RDY) != 0U)
      {
        if ((HAL_GetTick() - tickstart) > HSI48_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }


  /*------------------------------ LSE Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) != 0x00u)
  {
    FlagStatus       pwrclkchanged = RESET;

    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

    /* Update LSE configuration in Backup Domain control register    */
    /* Requires to enable write access to Backup Domain of necessary */
    if (__HAL_RCC_PWR_IS_CLK_ENABLED() != 0x01)
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }

    /* Enable write access to Backup domain */
    SET_BIT(PWR->DBPR, PWR_DBPR_DBP);

    /* Set the new LSE configuration -----------------------------------------*/
    /* Check the LSE State */
    if (RCC_OscInitStruct->LSEState != RCC_LSE_OFF)
    {
      /* If LSE is already on or in bypass mode, only LSE system can be modified */
      tmpreg1 = (RCC->BDCR & ~RCC_BDCR_LSESYSEN);
      tmpreg1 |= RCC_OscInitStruct->LSEState;
      RCC->BDCR = tmpreg1;

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is ready */
      while (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      /* Enable LSESYS additionally if requested */
      if ((RCC_OscInitStruct->LSEState & RCC_BDCR_LSESYSEN) != 0U)
      {
        /* Wait till LSESYS is ready */
        while (READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Wait till LSESYSRDY is cleared */
        while (READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    else
    {
      CLEAR_BIT(RCC->BDCR, (RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN));
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is disabled */
      while (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) != 0U)
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

  /*------------------------------ LSI Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) != 0x00u)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

    /* Get CSR register value */
    tmpreg1 = RCC->CSR;

    /* Check the LSI State */
    if (RCC_OscInitStruct->LSIState != RCC_LSI_OFF)
    {
      /* Check LSI division factor */
      assert_param(IS_RCC_LSI_DIV(RCC_OscInitStruct->LSIDiv));

      /* Check is LSIDiv is requested to be changed and LSI is already ON */
      if ((RCC_OscInitStruct->LSIDiv != (tmpreg1 & RCC_CSR_LSIPREDIV)) && ((tmpreg1 & RCC_CSR_LSIRDY) != 0x00u))
      {
        /* Disable LSI (end clear ready bit from tmpreg to avoid its propagation below) */
        tmpreg1 &= ~(RCC_CSR_LSION | RCC_CSR_LSIRDY);
        RCC->CSR = tmpreg1;

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till LSI is disabled */
        while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) != 0x00u)
        {
          if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
          {
            /* LSI may be forced ON by IWDG */
            return HAL_TIMEOUT;
          }
        }
        /* Wait at least a half of LSI clock period before applying the new LSI prediv value */
        HAL_Delay(1);
      }

      /* Set LSI division factor */
      tmpreg1 &= ~RCC_CSR_LSIPREDIV;
      tmpreg1 |= RCC_OscInitStruct->LSIDiv;

      /* Enable  LSI */
      tmpreg1 |= RCC_CSR_LSION;
      RCC->CSR = tmpreg1;

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == 0x00u)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Disable the Internal Low Speed oscillator */
      tmpreg1 &= ~RCC_CSR_LSION;
      RCC->CSR = tmpreg1;

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is disabled */
      while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) != 0x00u)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*------------------------------ MSIS Configuration -----------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_MSIS) != 0x00u)
  {
    /* Check the parameters */
    assert_param(IS_RCC_MSI(RCC_OscInitStruct->MSISState));

    /* Check if MSIS is asked to be turn off */
    if (RCC_OscInitStruct->MSISState == RCC_MSI_OFF)
    {
      /* When MSIS is used as system clock it will not be disabled */
      if (sysclksrc == RCC_SYSCLKSOURCE_STATUS_MSIS)
      {
        return HAL_ERROR;
      }
      else
      {
        /* Disable the MSIS */
        __HAL_RCC_MSIS_DISABLE();

        /* Store ready bit value for timeout */
        tmpreg1 = 0x00u;
      }
    }
    else
    {
      /* Otherwise, turn it ON or if already ON, changing source and range is allowed */
      assert_param(IS_RCC_MSI_SOURCE(RCC_OscInitStruct->MSISSource));
      assert_param(IS_RCC_MSI_DIV(RCC_OscInitStruct->MSISDiv));

      /* Changing source and range is not possible when osnillator is ON but not Ready */
      if ((RCC->CR & (RCC_CR_MSISON | RCC_CR_MSISRDY)) == RCC_CR_MSISON)
      {
        return HAL_ERROR;
      }
      else
      {
        /* Adjusts the MSIS source and divider, and force MSI selection to ICSCR1 */
        tmpreg1 = RCC->ICSCR1 & ~(RCC_ICSCR1_MSISSEL | RCC_ICSCR1_MSISDIV);
        tmpreg1 |= (RCC_ICSCR1_MSIRGSEL | RCC_OscInitStruct->MSISSource | RCC_OscInitStruct->MSISDiv);
        RCC->ICSCR1 = tmpreg1;

        /* If MSIS is already selected as system clock, update Systick */
        if (sysclksrc == RCC_SYSCLKSOURCE_STATUS_MSIS)
        {
          /* Update the SystemCoreClock global variable */
          SystemCoreClock = HAL_RCC_GetSysClockFreq() >> AHBPrescTable[(RCC->CFGR2 & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos];

          /* Configure the source of time base considering new system clocks settings*/
          if (HAL_InitTick(uwTickPrio) != HAL_OK)
          {
            return HAL_ERROR;
          }
        }
        else
        {
          /* Enable the MSIS */
          __HAL_RCC_MSIS_ENABLE();
        }

        /* Store ready bit value for timeout */
        tmpreg1 = RCC_CR_MSISRDY;
      }
    }

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Wait till HSI48 is disabled */
    while (READ_BIT(RCC->CR, RCC_CR_MSISRDY) != tmpreg1)
    {
      if ((HAL_GetTick() - tickstart) > MSI_TIMEOUT_VALUE)
      {
        if (READ_BIT(RCC->CR, RCC_CR_MSISRDY) != tmpreg1)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*------------------------------ MSIK Configuration -----------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_MSIK) != 0x00u)
  {
    /* Check the parameters */
    assert_param(IS_RCC_MSI(RCC_OscInitStruct->MSIKState));

    /* Check if MSIK is asked to be turn off */
    if (RCC_OscInitStruct->MSIKState == RCC_MSI_OFF)
    {
      /* Disable the MSIK */
      __HAL_RCC_MSIK_DISABLE();

      /* Store ready bit value for timeout */
      tmpreg1 = 0x00u;
    }
    else
    {
      /* Otherwise, turn it ON or if already ON, changing source and range is allowed */
      assert_param(IS_RCC_MSI_SOURCE(RCC_OscInitStruct->MSIKSource));
      assert_param(IS_RCC_MSI_DIV(RCC_OscInitStruct->MSIKDiv));

      /* Changing source and range is not possible when osnillator is ON but not Ready */
      if ((RCC->CR & (RCC_CR_MSIKON | RCC_CR_MSIKRDY)) == RCC_CR_MSIKON)
      {
        return HAL_ERROR;
      }
      else
      {
        /* Adjusts the MSIK source and divider, and force MSI selection to ICSCR1 */
        tmpreg1 = RCC->ICSCR1 & ~(RCC_ICSCR1_MSIKSEL | RCC_ICSCR1_MSIKDIV);
        tmpreg1 |= (RCC_ICSCR1_MSIRGSEL | ((RCC_OscInitStruct->MSIKSource | RCC_OscInitStruct->MSIKDiv) >> (RCC_ICSCR1_MSISSEL_Pos - RCC_ICSCR1_MSIKSEL_Pos)));
        RCC->ICSCR1 = tmpreg1;

        /* Enable the MSIK */
        __HAL_RCC_MSIK_ENABLE();

        /* Store ready bit value for timeout */
        tmpreg1 = RCC_CR_MSIKRDY;
      }
    }

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Wait till HSI48 is disabled */
    while (READ_BIT(RCC->CR, RCC_CR_MSIKRDY) != tmpreg1)
    {
      if ((HAL_GetTick() - tickstart) > MSI_TIMEOUT_VALUE)
      {
        if (READ_BIT(RCC->CR, RCC_CR_MSIKRDY) != tmpreg1)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Initialize the CPU, AHB and APB bus clocks according to the specified
  *         parameters in the RCC_ClkInitStruct.
  * @param  RCC_ClkInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency  FLASH Latency
  *         This parameter can be one of the following values:
  *            @arg FLASH_LATENCY_0   FLASH 0 Latency cycle
  *            @arg FLASH_LATENCY_1   FLASH 1 Latency cycle
  *            @arg FLASH_LATENCY_2   FLASH 2 Latency cycles
  *            @arg FLASH_LATENCY_3   FLASH 3 Latency cycles
  *            @arg FLASH_LATENCY_4   FLASH 4 Latency cycles
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency.
  * @note   The MSIS (12 MHz) is used by default as system clock source after
  *         startup from Reset. MSIS frequency when wake-up from STANDBY mode can be
  *         configured using HAL_RCCEx_StandbyWakeupMSISConfig().
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source is ready.
  * @note   You can use HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  * @retval None
  */
HAL_StatusTypeDef  HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency)
{
  uint32_t tmpreg1;
  uint32_t update;
  uint32_t tickstart;

  /* Check Null pointer */
  if (RCC_ClkInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_CLOCKTYPE(RCC_ClkInitStruct->ClockType));
  assert_param(IS_FLASH_LATENCY(FLatency));

  /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
   must be correctly programmed according to the frequency of the CPU clock
  (HCLK) and the supply voltage of the device. */

  /* Increasing the number of wait states because of higher CPU frequency */
  if (FLatency > __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if (__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      return HAL_ERROR;
    }
  }

  /*------------------------- SYSCLK Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
  {
    assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));

    /* Read CR register */
    tmpreg1 = RCC->CR;

    /* HSE is selected as System Clock Source */
    if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
    {
      /* Check the HSE ready flag */
      if ((tmpreg1 & RCC_CR_HSERDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* HSI is selected as System Clock Source */
    else if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSI)
    {
      /* Check the HSI ready flag */
      if ((tmpreg1 & RCC_CR_HSIRDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* MSIS is selected as System Clock Source */
    else
    {
      /* Check the MSIS ready flag */
      if ((tmpreg1 & RCC_CR_MSISRDY) == 0U)
      {
        return HAL_ERROR;
      }
    }

    /* Switch System clock source */
    MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SW, RCC_ClkInitStruct->SYSCLKSource);

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_SYSCLK_SOURCE() != (RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR1_SWS_Pos))
    {
      if ((HAL_GetTick() - tickstart) > CLOCKSWITCH_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Get CFGR2 content value, and reset update variable */
  tmpreg1 = RCC->CFGR2;
  update = 0x00u;

  /*-------------------------- HCLK Configuration --------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
    assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));

    /* update HCLK1 divider and notify register is required */
    tmpreg1 &= ~RCC_CFGR2_HPRE;
    tmpreg1 |= RCC_ClkInitStruct->AHBCLKDivider;
    update = 0x01u;
  }


  /*-------------------------- PCLK1 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
    assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB1CLKDivider));

    /* update PCLK1 divider and notify register is required */
    tmpreg1 &= ~RCC_CFGR2_PPRE1;
    tmpreg1 |= RCC_ClkInitStruct->APB1CLKDivider;
    update = 0x01u;
  }

  /*-------------------------- PCLK2 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
    assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB2CLKDivider));

    /* update PCLK2 divider and notify register is required */
    tmpreg1 &= ~RCC_CFGR2_PPRE2;
    tmpreg1 |= (RCC_ClkInitStruct->APB2CLKDivider << (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));
    update = 0x01u;
  }

  /* update CFGR2 if required */
  if (update != 0x00u)
  {
    RCC->CFGR2 = tmpreg1;
  }

  /*-------------------------- PCLK3 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK3) == RCC_CLOCKTYPE_PCLK3)
  {
    assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB3CLKDivider));
    WRITE_REG(RCC->CFGR3, RCC_ClkInitStruct->APB3CLKDivider);
  }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (FLatency < __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if (__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      return HAL_ERROR;
    }
  }

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HAL_RCC_GetSysClockFreq() >> AHBPrescTable[(RCC->CFGR2 & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos];

  /* Configure the source of time base considering new system clocks settings*/
  return HAL_InitTick(uwTickPrio);
}

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Control functions
  * @brief   RCC clocks control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to:

    (+) Output clock to MCO pin.
    (+) Retrieve current clock frequencies.
    (+) Enable the Clock Security System.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the microcontroller clock output
  * @param  RCC_MCOx  specifies the instance of clock output and its associated pin.
  *            @arg @ref RCC_MCO1_PA8  Clock source to output on MCO1 pin(PA8)
  *            @arg @ref RCC_MCO1_PA9  Clock source to output on MCO1 pin(PA9)
  *            @arg @ref RCC_MCO2_PA8  Clock source to output on MCO2 pin(PA8)
  *            @arg @ref RCC_MCO2_PA10  Clock source to output on MCO2 pin(PA10)
  * @param  RCC_MCOSource  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK   MCO1 output disabled, no clock on MCO1
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK    System  clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_MSIS      MSIS clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_HSI       HSI clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_HSE       HSE clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_LSI       LSI clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_LSE       LSE clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_HSI48     HSI48 clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_MSIK      MSIK clock selected as MCO1 source
  *            @arg @ref RCC_MCO2SOURCE_NOCLOCK   MCO2 output disabled, no clock on MCO2
  *            @arg @ref RCC_MCO2SOURCE_SYSCLK    System  clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_MSIS      MSIS clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_HSI       HSI clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_HSE       HSE clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_LSI       LSI clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_LSE       LSE clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_HSI48     HSI48 clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_MSIK      MSIK clock selected as MCO2 source
  * @param  RCC_MCODiv  specifies the MCO prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1    no division applied to MCO1 clock
  *            @arg @ref RCC_MCODIV_2    division by 2 applied to MCO1 clock
  *            @arg @ref RCC_MCODIV_4    division by 4 applied to MCO1 clock
  *            @arg @ref RCC_MCODIV_8    division by 8 applied to MCO1 clock
  *            @arg @ref RCC_MCODIV_16   division by 16 applied to MCO1 clock
  *            @arg @ref RCC_MCODIV_32   division by 32 applied to MCO1 clock
  *            @arg @ref RCC_MCODIV_64   division by 64 applied to MCO1 clock
  *            @arg @ref RCC_MCODIV_128  division by 128 applied to MCO1 clock
  *            @arg @ref RCC_MCO2DIV_1   no division applied to MCO2 clock
  *            @arg @ref RCC_MCO2DIV_2   division by 2 applied to MCO2 clock
  *            @arg @ref RCC_MCO2DIV_4   division by 4 applied to MCO2 clock
  *            @arg @ref RCC_MCO2DIV_8   division by 8 applied to MCO2 clock
  *            @arg @ref RCC_MCO2DIV_16  division by 16 applied to MCO2 clock
  *            @arg @ref RCC_MCO2DIV_32  division by 32 applied to MCO2 clock
  *            @arg @ref RCC_MCO2DIV_64  division by 64 applied to MCO2 clock
  *            @arg @ref RCC_MCO2DIV_128 division by 128 applied to MCO2 clock
  * @retval None
  */
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  uint32_t clearmask;

  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCOx));

  /* MCO Clock Enable. On U3, MCO1 and MCO2 are always on GPIOA */
  __MCO_CLK_ENABLE();

  /* Configure the MCO1 pin in alternate function mode */
  GPIO_InitStruct.Pin = (RCC_MCOx & RCC_MCO_GPIOPIN_MASK);
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = ((RCC_MCOx & RCC_MCO_GPIOAF_MASK) >> RCC_MCO_GPIOAF_POS);
  HAL_GPIO_Init(MCO_GPIO_PORT, &GPIO_InitStruct);

  if ((RCC_MCOx & RCC_MCO_INDEX_MASK) != 0x00u)
  {
    assert_param(IS_RCC_MCO2DIV(RCC_MCODiv));
    assert_param(IS_RCC_MCO2SOURCE(RCC_MCOSource));
    clearmask = (RCC_CFGR1_MCO2SEL | RCC_CFGR1_MCO2PRE);
  }
  else
  {
    assert_param(IS_RCC_MCODIV(RCC_MCODiv));
    assert_param(IS_RCC_MCO1SOURCE(RCC_MCOSource));
    clearmask = (RCC_CFGR1_MCOSEL | RCC_CFGR1_MCOPRE);
  }

  /* Mask MCOxSEL[] and MCOxPRE[] bits then set MCOx clock source and prescaler */
  MODIFY_REG(RCC->CFGR1, clearmask, (RCC_MCOSource | RCC_MCODiv));
}

/**
  * @brief  Return the SYSCLK frequency.
  * @note   The system frequency computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  *         If SYSCLK source is MSIS, function returns values based on MSIRC0_VALUE(*)
  *         or MSIRC1_VALUE(*)
  *         If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  *         If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  *         (*)  MSIRC0_VALUE and MSIRC1_VALUE are constants defined in stm32u3xx_hal_conf.h
  *              file. Default values are respectively 96 MHz and 48 MHz. Real value may vary
  *              depending on voltage and tempereture variations.
  *         (*)  HSI_VALUE is a constant defined in stm32u3xx_hal_conf.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *         (**) HSE_VALUE is a constant defined in stm32u3xx_hal_conf.h file (default value
  *              32 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  * @note   Internal RC oscillators can be trimmed.
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  uint32_t tmpcfgr;
  uint32_t sysclk;

  /* Get SYSCLK source */
  tmpcfgr = __HAL_RCC_GET_SYSCLK_SOURCE();

  if (tmpcfgr == RCC_SYSCLKSOURCE_STATUS_HSE)
  {
    /* HSE used as system clock source */
    sysclk = HSE_VALUE;
  }
  else if (tmpcfgr == RCC_SYSCLKSOURCE_STATUS_HSI)
  {
    /* HSI used as system clock source */
    sysclk = HSI_VALUE;
  }
  else
  {
    /* MSIS used as system clock source. Read ICSR1 register */
    tmpcfgr = RCC->ICSCR1;

    /* Check which MSIS Range is selected */
    if ((tmpcfgr & RCC_ICSCR1_MSIRGSEL) != 0x00u)
    {
      /* Check which MSIRCx is selected as MSIS source */
      if ((tmpcfgr & RCC_ICSCR1_MSISSEL) != 0x00u)
      {
        /* MSI RC1 is selected */
        sysclk = MSIRC1_VALUE;
      }
      else
      {
        /* MSI RC0 is selected */
        sysclk = MSIRC0_VALUE;
      }

      /* Get MSIS range */
      tmpcfgr = (tmpcfgr & RCC_ICSCR1_MSISDIV) >> RCC_ICSCR1_MSISDIV_Pos;
    }
    else
    {
      /* MSI RC1 is selected */
      sysclk = MSIRC1_VALUE;

      /* Get MSIS range */
      tmpcfgr = (RCC->CSR & (RCC_CSR_MSISDIVS_1 | RCC_CSR_MSISDIVS_0)) >> RCC_CSR_MSISDIVS_Pos;
    }

    /* MSIS frequency in HZ*/
    sysclk >>= tmpcfgr;
  }

  return sysclk;
}

/**
  * @brief  Return the HCLK frequency.
  * @note   Each time HCLK changes, this function must be called to update the
  *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency.
  * @retval HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  SystemCoreClock = HAL_RCC_GetSysClockFreq() >> AHBPrescTable[(RCC->CFGR2 & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos];
  return SystemCoreClock;
}

/**
  * @brief  Return the PCLK1 frequency.
  * @note   Each time PCLK1 changes, this function must be called to update the
  *         right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK1 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR2 & RCC_CFGR2_PPRE1) >> RCC_CFGR2_PPRE1_Pos]);
}

/**
  * @brief  Return the PCLK2 frequency.
  * @note   Each time PCLK2 changes, this function must be called to update the
  *         right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency ---------------------------*/
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR2 & RCC_CFGR2_PPRE2) >> RCC_CFGR2_PPRE2_Pos]);
}

/**
  * @brief  Return the PCLK3 frequency.
  * @note   Each time PCLK3 changes, this function must be called to update the
  *         right PCLK3 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK3 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK3Freq(void)
{
  /* Get HCLK source and Compute PCLK3 frequency ---------------------------*/
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR3 & RCC_CFGR3_PPRE3) >> RCC_CFGR3_PPRE3_Pos]);
}

/**
  * @brief  Return the MSIS frequency.
  * @retval MSIS frequency in Hz
  */
uint32_t HAL_RCC_GetMSISFreq(void)
{
  uint32_t tmp;
  uint32_t msirange;

  /* Compute MSIS frequency ------------------------------------------------*/
  /* Read RCC ICSR1 register */
  tmp = RCC->ICSCR1;

  /* Check which MSIS Range is selected */
  if ((tmp & RCC_ICSCR1_MSIRGSEL) != 0x00u)
  {
    /* Get MSIS range */
    msirange = (tmp & RCC_ICSCR1_MSISDIV) >> RCC_ICSCR1_MSISDIV_Pos;

    /* Check which MSIRCx is selected as MSIS source */
    if ((tmp & RCC_ICSCR1_MSISSEL) != 0x00u)
    {
      /* MSI RC1 is selected */
      tmp = MSIRC1_VALUE;
    }
    else
    {
      /* MSI RC0 is selected */
      tmp = MSIRC0_VALUE;
    }
  }
  else
  {
    /* MSI RC1 is selected */
    tmp = MSIRC1_VALUE;
    /* Get MSIS range */
    msirange = (RCC->CSR & (RCC_CSR_MSISDIVS_1 | RCC_CSR_MSISDIVS_0)) >> RCC_CSR_MSISDIVS_Pos;
  }

  /*MSIS frequency in HZ*/
  tmp >>= msirange;

  return tmp;
}

/**
  * @brief  Return the MSIK frequency.
  * @retval MSIK frequency in Hz
  */
uint32_t HAL_RCC_GetMSIKFreq(void)
{
  uint32_t tmp;
  uint32_t msirange;

  /* Compute MSIK frequency ------------------------------------------------*/
  /* Read RCC ICSR1 register */
  tmp = RCC->ICSCR1;

  /* Check which MSIK Range is selected */
  if ((tmp & RCC_ICSCR1_MSIRGSEL) != 0x00u)
  {
    /* Get MSIK range */
    msirange = (tmp & RCC_ICSCR1_MSIKDIV) >> RCC_ICSCR1_MSIKDIV_Pos;

    /* Check which MSIRCx is selected as MSIK source */
    if ((tmp & RCC_ICSCR1_MSIKSEL) != 0x00u)
    {
      /* MSI RC1 is selected */
      tmp = MSIRC1_VALUE;
    }
    else
    {
      /* MSI RC0 is selected */
      tmp = MSIRC0_VALUE;
    }
  }
  else
  {
    /* MSI RC1 is selected */
    tmp = MSIRC1_VALUE;

    /* Get MSIK range */
    msirange = (RCC->CSR & (RCC_CSR_MSIKDIVS_1 | RCC_CSR_MSIKDIVS_0)) >> RCC_CSR_MSIKDIVS_Pos;
  }

  /*MSIK frequency in HZ*/
  tmp >>= msirange;

  return tmp;
}


/**
  * @brief  Configure the RCC_OscInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_OscInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         will be configured.
  * @retval None
  */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct)
{
  uint32_t regvalue;
  uint32_t mask;

  /* Check the parameters */
  assert_param(RCC_OscInitStruct != (void *)NULL);

  /* Set all possible values for the Oscillator type parameter ---------------*/
  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI   | \
                                      RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_LSI | \
                                      RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSIS  | \
                                      RCC_OSCILLATORTYPE_MSIK;

  /* Get Backup Domain register 1 */
  regvalue = RCC->BDCR;

  /* Get the LSE configuration -----------------------------------------------*/
  mask = (RCC_BDCR_LSEBYP | RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON);
  RCC_OscInitStruct->LSEState = (regvalue & mask);

  /* Get the LSI configuration -----------------------------------------------*/
  regvalue = RCC->CSR;
  RCC_OscInitStruct->LSIState = (regvalue & RCC_CSR_LSION);
  RCC_OscInitStruct->LSIDiv = (regvalue & RCC_CSR_LSIPREDIV);

  /* Get Control register */
  regvalue = RCC->CR;

  /* Get the HSE configuration -----------------------------------------------*/
  mask = (RCC_CR_HSEEXT | RCC_CR_HSEBYP | RCC_CR_HSEON);
  RCC_OscInitStruct->HSEState = (regvalue & mask);

  /* Get the HSI configuration -----------------------------------------------*/
  RCC_OscInitStruct->HSIState = (regvalue & RCC_CR_HSION);
  RCC_OscInitStruct->HSICalibrationValue = ((RCC->ICSCR3 & RCC_ICSCR3_HSITRIM) >> RCC_ICSCR3_HSITRIM_Pos);

  /* Get the HSI48 configuration ---------------------------------------------*/
  RCC_OscInitStruct->HSI48State = (regvalue & RCC_CR_HSI48ON);

  /* Get the MSIS and MSIK configuration -------------------------------------*/
  RCC_OscInitStruct->MSISState = (regvalue & RCC_CR_MSISON);
  RCC_OscInitStruct->MSIKState = ((regvalue & RCC_CR_MSIKON) >> (RCC_CR_MSIKON_Pos - RCC_CR_MSISON_Pos));

  /* Get ICSR1 register */
  regvalue = RCC->ICSCR1;

  /* Check which MSI Range is selected */
  if ((regvalue & RCC_ICSCR1_MSIRGSEL) != 0x00u)
  {
    /* Check which MSIRCx is selected as MSIS source and get prescaler */
    RCC_OscInitStruct->MSISSource = (regvalue & RCC_ICSCR1_MSISSEL);
    RCC_OscInitStruct->MSISDiv = (regvalue & RCC_ICSCR1_MSISDIV);

    /* Check which MSIRCx is selected as MSIK source and get prescaler */
    RCC_OscInitStruct->MSIKSource = ((regvalue & RCC_ICSCR1_MSIKSEL) << (RCC_ICSCR1_MSISSEL_Pos - RCC_ICSCR1_MSIKSEL_Pos));
    RCC_OscInitStruct->MSIKDiv = ((regvalue & RCC_ICSCR1_MSIKDIV) << (RCC_ICSCR1_MSISDIV_Pos - RCC_ICSCR1_MSIKDIV_Pos));
  }
  else
  {
    /* MSI RC1 is forced as MSIx source */
    RCC_OscInitStruct->MSISSource = RCC_MSI_RC1;
    RCC_OscInitStruct->MSIKSource = RCC_MSI_RC1;

    /* Get both MSIS and MSIK divier */
    RCC_OscInitStruct->MSISDiv  = ((RCC->CSR & RCC_CSR_MSISDIVS) << (RCC_ICSCR1_MSISDIV_Pos - RCC_CSR_MSISDIVS_Pos));
    RCC_OscInitStruct->MSIKDiv  = ((RCC->CSR & RCC_CSR_MSIKDIVS) << (RCC_ICSCR1_MSISDIV_Pos - RCC_CSR_MSIKDIVS_Pos));
  }
}

/**
  * @brief  Configure the RCC_ClkInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_ClkInitStruct  pointer to an RCC_ClkInitTypeDef structure that
  *         will be configured.
  * @param  pFLatency  Pointer on the Flash Latency.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency)
{
  uint32_t tmpreg1;

  /* Check the parameters */
  assert_param(RCC_ClkInitStruct != (void *)NULL);
  assert_param(pFLatency != (void *)NULL);

  /* Set all possible values for the Clock type parameter --------------------*/
  RCC_ClkInitStruct->ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3);

  /* Get the SYSCLK configuration --------------------------------------------*/
  RCC_ClkInitStruct->SYSCLKSource = (RCC->CFGR1 & RCC_CFGR1_SW);

  /* Get the HCLK configuration ----------------------------------------------*/
  tmpreg1 = RCC->CFGR2;
  RCC_ClkInitStruct->AHBCLKDivider = (tmpreg1 & RCC_CFGR2_HPRE);

  /* Get the PCLK1 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB1CLKDivider = (tmpreg1 & RCC_CFGR2_PPRE1);

  /* Get the PCLK2 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB2CLKDivider = ((tmpreg1 & RCC_CFGR2_PPRE2) >> (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));

  /* Get the PCLK3 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB3CLKDivider = (RCC->CFGR3 & RCC_CFGR3_PPRE3);

  /* Get the Flash Wait State (Latency) configuration ------------------------*/
  *pFLatency = (FLASH->ACR & FLASH_ACR_LATENCY);
}

/**
  * @brief  Enable the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to
  *         the Cortex-M33 NMI (Non-Maskable Interrupt) exception vector.
  * @note   The Clock Security System can only be cleared by reset.
  * @retval None
  */
void HAL_RCC_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSECSSON);
}

/**
  * @brief Handle the RCC Clock Security System interrupt request.
  * @note This API should be called under the NMI_Handler().
  * @retval None
  */
void HAL_RCC_NMI_IRQHandler(void)
{
  /* Check RCC CSSF interrupt flag  */
  if (__HAL_RCC_GET_IT(RCC_IT_CSS))
  {
    /* Clear RCC CSS pending bit */
    __HAL_RCC_CLEAR_IT(RCC_IT_CSS);

    /* RCC Clock Security System interrupt user callback */
    HAL_RCC_CSSCallback();
  }
}

/**
  * @brief  RCC Clock Security System interrupt callback.
  * @retval none
  */
__weak void HAL_RCC_CSSCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RCC_CSSCallback should be implemented in the user file
   */
}

/**
  * @brief  Get and clear reset flags
  * @note   Once reset flags are retrieved, this API is clearing them in order
  *         to isolate next reset reason.
  * @retval can be a combination of @ref RCC_Reset_Flag
  */
uint32_t HAL_RCC_GetResetSource(void)
{
  uint32_t reset;

  /* Get all reset flags */
  reset = RCC->CSR & RCC_RESET_FLAG_ALL;

  /* Clear Reset flags */
  RCC->CSR |= RCC_CSR_RMVF;

  return reset;
}

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group3 Attributes management functions
  *  @brief Attributes management functions.
  *
@verbatim
 ===============================================================================
                       ##### RCC attributes functions #####
 ===============================================================================
@endverbatim
  * @{
  */
/**
  * @brief  Configure the RCC item attribute(s).
  * @note   Available attributes are to secure items and set RCC as privileged.
  * @note   As the privileged attributes concern either all secure or all non-secure
  *         RCC resources accesses and not each RCC individual items access attribute,
  *         the application must ensure that the privilege access attribute configurations
  *         are coherent amongst the security level set on RCC individual items so not to
  *         overwrite a previous more restricted access rule (consider either all secure
  *         and/or all non-secure RCC resources accesses by privileged-only transactions
  *         or privileged and unprivileged transactions).
  * @param  Item Item(s) to set attributes on.
  *         This parameter can be a one or a combination of @ref RCC_items
  * @param  Attributes specifies the RCC secure/privilege attributes.
  *         This parameter can be a value of @ref RCC_attributes
  * @retval None
  */
void HAL_RCC_ConfigAttributes(uint32_t Item, uint32_t Attributes)
{
  /* Check the parameters */
  assert_param(IS_RCC_ITEM_ATTRIBUTES(Item));
  assert_param(IS_RCC_ATTRIBUTES(Attributes));

#if !defined(CPU_IN_SECURE_STATE)
  /* Prevent unused argument(s) compilation warning */
  UNUSED( Item);
#endif /* CPU_IN_SECURE_STATE */

  switch (Attributes)
  {
#if defined(CPU_IN_SECURE_STATE)
    /* Secure Privilege attribute */
    case RCC_SEC_PRIV:
      SET_BIT(RCC->SECCFGR, Item);
      SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
      break;
    /* Secure Non-Privilege attribute */
    case RCC_SEC_NPRIV:
      SET_BIT(RCC->SECCFGR, Item);
      CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
      break;
    /* Non-secure Privilege attribute */
    case RCC_NSEC_PRIV:
      CLEAR_BIT(RCC->SECCFGR, Item);
      SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
      break;
    /* Non-secure Non-Privilege attribute */
    case RCC_NSEC_NPRIV:
      CLEAR_BIT(RCC->SECCFGR, Item);
      CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
      break;
#else
    /* Non-secure Privilege attribute */
    case RCC_NSEC_PRIV:
      SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
      break;
    /* Non-secure Non-Privilege attribute */
    case RCC_NSEC_NPRIV:
      CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
      break;
#endif /* CPU_IN_SECURE_STATE */
    default:
      /* Nothing to do */
      break;
  }
}
/**
  * @}
  */

/**
  * @brief  Get the attribute of a RCC item.
  * @note   Secure and non-secure attributes are only available from secure state
  *         when the system implements the security (TZEN=1)
  * @param  Item Single item to get secure/non-secure and privilege/non-privilege attribute from.
  *         This parameter can be a one value of @ref RCC_items except RCC_ALL.
  * @param  pAttributes pointer to return the attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_RCC_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes)
{
  uint32_t attributes;

  /* Check null pointer */
  if (pAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_ITEM_ATTRIBUTES(Item));

  /* Check item security */
  if ((RCC->SECCFGR & Item) == Item)
  {
    /* Get Secure privileges attribute */
    attributes = ((RCC->PRIVCFGR & RCC_PRIVCFGR_SPRIV) == 0U) ? RCC_SEC_NPRIV : RCC_SEC_PRIV;
  }
  else
  {
    /* Get Non-Secure privileges attribute */
    attributes = ((RCC->PRIVCFGR & RCC_PRIVCFGR_NSPRIV) == 0U) ? RCC_NSEC_NPRIV : RCC_NSEC_PRIV;
  }

  /* return value */
  *pAttributes = attributes;

  return HAL_OK;
}
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup RCC_Private_Functions
  * @{
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
