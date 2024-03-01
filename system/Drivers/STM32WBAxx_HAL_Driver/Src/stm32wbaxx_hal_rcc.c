/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_rcc.c
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
  * Copyright (c) 2022 STMicroelectronics.
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
      After reset the device is running from High Speed Internal oscillator
      (from 8 MHz to reach 16MHz) with Flash 0 wait state. Flash prefetch buffer
      is disabled.
      (+) There is no prescaler on High speed (AHBs) except for AHB5 and no
          prescaler Low speed (APBs) busses: all peripherals mapped on these
          busses are running at HSI speed.
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
#include "stm32wbaxx_hal.h"

/** @addtogroup STM32WBAxx_HAL_Driver
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
#define LSI_TIMEOUT_VALUE               ((5u * 128u * 1000u) / LSI_VALUE)
#define PLL_TIMEOUT_VALUE               2U        /* 2 ms (minimum Tick + 1) */
#define PLL_FRAC_WAIT_VALUE             1U        /* PLL Fractional part waiting time before new latch enable : 1 ms */
#define PLL1_NDIV_TIMEOUT_VALUE         10U       /* SYSCLK divider delay when going from divide to not divide. 10 ms when 2-steps */
#define CLOCKSWITCH_TIMEOUT_VALUE       5000U     /* 5 s    */
#define PLL_INPUTRANGE0_FREQMAX         8000000u  /* 8 MHz is maximum frequency for VCO input range 0 */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define __MCO1_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO1_GPIO_PORT        GPIOA
#define MCO1_PIN              GPIO_PIN_8
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static float_t RCC_PLL1_GetVCOOutputFreq(void);
/**
  * @}
  */

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
      (HSE, HSI, LSE, LSI (LSI1 or LSI2), PLL1, CSS and MCO) and the System busses clocks (SYSCLK,
      AHB1, AHB2, AHB4, AHB5, APB1, APB2 and APB7).

    [..] Internal/external clock and PLL1 configuration
         (+) HSI (high-speed internal): 16 MHz factory-trimmed RC used directly or through
             the PLL1 as System clock source.

         (+) LSI (low-speed internal):
           (++) LSI1: 32 kHz low-speed low power internal RC that drives the independent watchdog
                and optionally the RTC used for auto-wakeup from Stop and Standby modes
           (++) LSI2: 32 kHz low-speed low drift internal RC that drives optionally the RTC or
                2.4 GHz RADIO sleep timer used for auto-wakeup from Stop and Standby modes.

         (+) HSE (high-speed external): 32 MHz crystal oscillator used directly or
             through the PLL1 as System clock source. Can be used also optionally as RTC clock source.

         (+) LSE (low-speed external): 32.768 KHz oscillator used optionally as RTC clock source
             and 2.4 GHz RADIO sleep timer.

         (+) PLL1 (clocked by HSI or HSE) providing up to three independent output clocks:
           (++) The P output is used to generate an accurate clock to achieve
                high-quality audio performance on SAI interface and ADC4.
           (++) The Q output is used to generate the clock for the SAI1 and RNG.
           (++) The R output is used to generate the high speed system clock (up to 100MHz).

         (+) CSS (Clock security system): once enabled, if a HSE clock failure occurs
            (HSE used directly or through PLL1 as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled.
             The interrupt is linked to the Cortex-M33 NMI (Non-Maskable Interrupt)
             exception vector.

         (+) MCO (microcontroller clock output): used to output LSI, HSI, LSE, HSE32, SYSCLK, HCLK5 and
             PLL1 R, P, Q clocks (through a configurable prescaler) on PA8 pin.

    [..] System, AHB and APB busses clocks configuration
         (+) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
             HSE and main PLL1.
             The AHB clock (HCLK) is derived from System clock through configurable
             prescaler and used to clock the CPU, memory and peripherals mapped
             on AHB bus (DMA, GPIO...). APB1 (PCLK1), APB2 (PCLK2) and APB7 (PCLK7) clocks are derived
             from AHB clock through configurable prescalers and used to clock
             the peripherals mapped on these busses. You can use
             "HAL_RCC_GetSysClockFreq()" function to retrieve the frequencies of these clocks.

         -@- All the peripheral kernel clocks are derived from the System clock (SYSCLK) but some
             peripheral can select a different source (you have to use HAL_RCCEx_PeriphCLKConfig()
             function to configure it) :
           (+@) U(S)ARTx (x = 1, 2) : Kernel clock can be PCLKx, SYSCLK, HSI or LSE.
           (+@) I2Cx (x = 1, 3) : Kernel clock can be PCLKx, SYSCLK or HSI.
           (+@) LPTIMx (x = 1, 2) : Kernel clock can be PCLKx, LSI, HSI or LSE.
           (+@) SPIx (x = 1, 3) : Kernel clock can be PCLKx, SYSCLK or HSI.
           (+@) SAI1 : Kernel clock can be PLL1P, PLL1Q, SYSCLK, a clock provided on CKIN pin or HSI.
           (+@) RNG : Kernel clock can be LSE, LSI, HSI or PLL1Q.
           (+@) LPUART1 : Kernel clock can be PCLKx, SYSCLK, HSI or LSE.
           (+@) RTC : Kernel clock can be derived either from the LSI, LSE or HSE clock divided by 32.
           (+@) ADC4 : Kernel clock can be HCLK, SYSCLK, PLL1P, HSE or HSI clock.
           (+@) 2.4 GHz RADIO sleep timer : Kernel clock can be LSE, LSI, or HSE divided by 1000 clock.


         (+) The maximum frequency of SYSCLK / AHB1 / AHB2 / AHB4 / APB1 / APB2 / APB7 is
              (++) 100 MHz at voltage range 1
              (++) 16 MHZ at voltage range 2

         (+) The maximum frequency of AHB5 is
              (++) 32 MHz at voltage range 1
              (++) 12 MHZ at voltage range 2

             The clock source frequency should be adapted depending on the device voltage range
             as listed in the Reference Manual "Clock source frequency versus voltage scaling" chapter.

  @endverbatim

     (++)  Table 1. HCLK clock frequency for STM32WBAxx devices
     (++)  +-------------------------------------------------------+
     (++)  | Latency         |     HCLK clock frequency (MHz)      |
     (++)  |                 |-------------------------------------|
     (++)  |                 | voltage scaling  | voltage scaling  |
     (++)  |                 |      range 1     |      range 1     |
     (++)  |-----------------|------------------|------------------|
     (++)  |0WS(1 CPU cycles)|     HCLK <=  32  |     HCLK <=  8   |
     (++)  |-----------------|------------------|------------------|
     (++)  |1WS(2 CPU cycles)|     HCLK <=  64  |     HCLK <= 16   |
     (++)  |-----------------|------------------|------------------|
     (++)  |2WS(3 CPU cycles)|     HCLK <=  96  |        -         |
     (++)  |-----------------|------------------|------------------|
     (++)  |3WS(4 CPU cycles)|     HCLK <= 100  |        -         |
     (++)  +-----------------+------------------+------------------+
  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - HSI ON and used as system clock source
  *            - HSE and PLL1 OFF
  *            - AHB, APB1, APB2 and APB7 prescaler set to 1.
  *            - CSS, MCO1 OFF
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

  /* Set HSION bit */
  SET_BIT(RCC->CR, RCC_CR_HSION);

  /* Wait till HSI is ready */
  while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Set HSITRIM default value */
  MODIFY_REG(RCC->ICSCR3, RCC_ICSCR3_HSITRIM, 0x00100000U);

  /* Get start tick*/
  tickstart = HAL_GetTick();

  /* Reset CFGR1 register (HSI is selected as system clock source) */
  CLEAR_REG(RCC->CFGR1);

  /* Wait till clock switch is ready */
  while (READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > CLOCKSWITCH_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Set AHBx and APBx prescaler to their default values */
  CLEAR_REG(RCC->CFGR2);
  CLEAR_REG(RCC->CFGR3);
  WRITE_REG(RCC->CFGR4, 0x00000010);

  /* Clear CR register in 2 steps: first to clear HSEON in case bypass was enabled */
  RCC->CR = RCC_CR_HSION;

  /* Then again to HSEBYP in case bypass was enabled */
  RCC->CR = RCC_CR_HSION;

  /* Get Start Tick */
  tickstart = HAL_GetTick();

  /* Wait till PLL1 is disabled */
  while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Reset PLL1CFGR register */
  CLEAR_REG(RCC->PLL1CFGR);

  /* Reset PLL1DIVR register */
  WRITE_REG(RCC->PLL1DIVR, 0x01010280U);

  /* Reset PLL1FRACR register */
  CLEAR_REG(RCC->PLL1FRACR);

  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER);

  /* Clear all interrupts flags */
  WRITE_REG(RCC->CICR, 0xFFFFFFFFU);

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HSI_VALUE;

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
  * @note   The PLL1 is not disabled when used as system clock.
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
  uint32_t pllsrc;
  uint32_t tmpreg1;
  uint32_t tmpreg2;
  uint32_t mask;

  /* Check Null pointer */
  if (RCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

  sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();
  pllsrc = __HAL_RCC_GET_PLL1_OSCSOURCE();

  /*------------------------------- HSE Configuration ------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

    /* When the HSE is used as system clock or clock source for PLL1 in these cases it is not allowed to be disabled */
    if ((sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSE) ||
        ((sysclksrc == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (pllsrc == RCC_PLLSOURCE_HSE)))
    {
      if (RCC_OscInitStruct->HSEState == RCC_HSE_OFF)
      {
        return HAL_ERROR;
      }
      else
      {
        /* Otherwise, applying divider is allowed */
        if (sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSE)
        {
          assert_param(IS_RCC_HSEDIV(RCC_OscInitStruct->HSEDiv));

          /* Adjust the HSE division factor */
          __HAL_RCC_HSE_CONFIG(RCC_HSE_ON | RCC_OscInitStruct->HSEDiv);

          /* Update the SystemCoreClock global variable with HSE value */
          SystemCoreClock = (HSE_VALUE / (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSEPRE)) >> RCC_CR_HSEPRE_Pos)));

          /* Adapt Systick interrupt period */
          if (HAL_InitTick(uwTickPrio) != HAL_OK)
          {
            return HAL_ERROR;
          }
        }
      }
    }
    else
    {
      /* Check the HSE State */
      if (RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        assert_param(IS_RCC_HSEDIV(RCC_OscInitStruct->HSEDiv));

        /* Set the new HSE configuration ---------------------------------------*/
        __HAL_RCC_HSE_CONFIG((RCC_OscInitStruct->HSEState | RCC_OscInitStruct->HSEDiv));

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
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_HSI_CALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

    /* Check if HSI is used as system clock or as PLL1 source when PLL1 is selected as system clock */
    if ((sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSI) ||
        ((sysclksrc == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (pllsrc == RCC_PLLSOURCE_HSI)))
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

  /*------------------------------ LSI Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

    FlagStatus  pwrclkchanged = RESET;

    /* Update LSI1 configuration in Backup Domain control register    */
    /* Requires to enable write access to Backup Domain of necessary */
    if (__HAL_RCC_PWR_IS_CLK_ENABLED() != 0x01)
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }

    if (HAL_IS_BIT_CLR(PWR->DBPR, PWR_DBPR_DBP))
    {
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
    }

    /* Get BDCR1 register value */
    tmpreg1 = RCC->BDCR1;

    /* Define mask depending on LSI presence */
    mask = RCC_BDCR1_LSI1ON;
#if defined(RCC_LSI2_SUPPORT)
    mask |= RCC_BDCR1_LSI2ON;
#endif /* RCC_LSI2_SUPPORT */

    /* Check the LSI1 State */
    if (RCC_OscInitStruct->LSIState != RCC_LSI_OFF)
    {
      if ((RCC_OscInitStruct->LSIState & RCC_LSI1_ON) != 0x00u)
      {
        /* Check LSI1 division factor */
        assert_param(IS_RCC_LSIDIV(RCC_OscInitStruct->LSIDiv));

        /* Check is LSIDiv is requested to be changed and LSI is already ON */
        if ((RCC_OscInitStruct->LSIDiv != (tmpreg1 & RCC_BDCR1_LSI1PREDIV)) && ((tmpreg1 & RCC_BDCR1_LSI1RDY) != 0x00u))
        {
          /* Disable LSI1 */
          tmpreg1 &= ~RCC_BDCR1_LSI1ON;
          RCC->BDCR1 = tmpreg1;

          /* Get Start Tick*/
          tickstart = HAL_GetTick();

          /* Wait till LSI1 is disabled */
          while (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSI1RDY) != 0x00u)
          {
            if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
            {
              /* LSI1 may be forced ON by IWDG */
              return HAL_TIMEOUT;
            }
          }
#if defined(STM32WBAXX_SI_CUT1_0)
          /* Wait at least 1 half LSI clock period before apppling new LSI1 prediv value */
          HAL_Delay(1);
#endif
        }

        /* Set LSI1 division factor */
        tmpreg1 &= ~RCC_BDCR1_LSI1PREDIV;
        tmpreg1 |= RCC_OscInitStruct->LSIDiv;
      }

      /* Enable Concerned LSI */
      tmpreg1 |= RCC_OscInitStruct->LSIState;
      RCC->BDCR1 = tmpreg1;

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is ready : LSIRDY bit is position ON shifted by 1 */
      while (READ_BIT(RCC->BDCR1, (RCC_OscInitStruct->LSIState << 1)) == 0x00u)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

#if defined(RCC_LSI2_SUPPORT)
      /* Disable other LSI in case it was ON */
      mask ^= RCC_OscInitStruct->LSIState;
      tmpreg1 &= ~mask;
      RCC->BDCR1 = tmpreg1;

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till other LSI is disabled */
      while (READ_BIT(RCC->BDCR1, (mask << 1)) != 0x00u)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
#endif
    }
    else
    {
      /* Disable the Internal Low Speed oscillator LSI1 and LSI2 is available */
      tmpreg1 &= ~mask;
      RCC->BDCR1 = tmpreg1;

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is disabled : LSIRDY bit position is ON shifted by 1 */
      while (READ_BIT(RCC->BDCR1, (mask << 1)) != 0x00u)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
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

  /*------------------------------ LSE Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
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

    if (HAL_IS_BIT_CLR(PWR->DBPR, PWR_DBPR_DBP))
    {
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
    }

    /* Set the new LSE configuration -----------------------------------------*/
    /* Check the LSE State */
    if (RCC_OscInitStruct->LSEState != RCC_LSE_OFF)
    {
      /* If LSE is already on or in bypass mode, only LSE system can be modified */
      tmpreg1 = (RCC->BDCR1 & ~RCC_BDCR1_LSESYSEN);
      tmpreg1 |= RCC_OscInitStruct->LSEState;
      RCC->BDCR1 = tmpreg1;

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is ready */
      while (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSERDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      /* Enable LSESYS additionally if requested */
      if ((RCC_OscInitStruct->LSEState & RCC_BDCR1_LSESYSEN) != 0U)
      {
        /* Wait till LSESYS is ready */
        while (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSESYSRDY) == 0U)
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
        while (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSESYSRDY) != 0U)
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
      CLEAR_BIT(RCC->BDCR1, (RCC_BDCR1_LSEON | RCC_BDCR1_LSESYSEN));
      CLEAR_BIT(RCC->BDCR1, RCC_BDCR1_LSEBYP);

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is disabled */
      while (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSERDY) != 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      if (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSESYSEN) != 0U)
      {
        /* Wait till LSESYSRDY is cleared */
        while (READ_BIT(RCC->BDCR1, RCC_BDCR1_LSESYSRDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
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

  /*-------------------------------- PLL1 Configuration -----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL1.PLLState));

  if ((RCC_OscInitStruct->PLL1.PLLState) != RCC_PLL_NONE)
  {
    /* Check if the PLL1 is used as system clock or not */
    if (sysclksrc != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
    {
      if ((RCC_OscInitStruct->PLL1.PLLState) == RCC_PLL_ON)
      {
        /* Check the parameters */
        assert_param(IS_RCC_PLLSOURCE(RCC_OscInitStruct->PLL1.PLLSource));
        assert_param(IS_RCC_PLLM_VALUE(RCC_OscInitStruct->PLL1.PLLM));
        assert_param(IS_RCC_PLLN_VALUE(RCC_OscInitStruct->PLL1.PLLN));
        assert_param(IS_RCC_PLLP_VALUE(RCC_OscInitStruct->PLL1.PLLP));
        assert_param(IS_RCC_PLLQ_VALUE(RCC_OscInitStruct->PLL1.PLLQ));
        assert_param(IS_RCC_PLLR_VALUE(RCC_OscInitStruct->PLL1.PLLR));

        /* Disable the main PLL1. */
        tmpreg1 = (RCC->CR & ~RCC_CR_PLL1ON);
        RCC->CR = tmpreg1;

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till PLL1 is disabled */
        do
        {
          tmpreg1 = RCC->CR;
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        } while ((tmpreg1 & RCC_CR_PLL1RDY) != 0U);

        /* Compute VCO input frequency and define range accordingly. First check clock source frequency */
        if (RCC_OscInitStruct->PLL1.PLLSource == RCC_PLLSOURCE_HSE)
        {
          /* Clock source is HSE or HSE/2 */
          pllsrc = HSE_VALUE >> ((tmpreg1 & RCC_CR_HSEPRE) >> RCC_CR_HSEPRE_Pos);
        }
        else
        {
          /* Clock source is HSI */
          pllsrc = HSI_VALUE;
        }

        /* Compute VCO input frequency depending on M divider */
        pllsrc = (pllsrc / RCC_OscInitStruct->PLL1.PLLM);
        assert_param(IS_RCC_PLL_VCOINPUTFREQ(pllsrc));

        if (pllsrc > PLL_INPUTRANGE0_FREQMAX)
        {
          /* Reuse pllsrc local variable to store range */
          pllsrc = RCC_PLL_VCOINPUT_RANGE1;
        }
        else
        {
          /* Reuse pllsrc local variable to store range */
          pllsrc = RCC_PLL_VCOINPUT_RANGE0;
        }

        /* Configure PLL1 source, PLLM divider, VCO input range and enable PLL1R output. Clear also FRACEN*/
        tmpreg2 = RCC->PLL1CFGR;
        tmpreg2 &= ~(RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1RGE | RCC_PLL1CFGR_PLL1FRACEN | RCC_PLL1CFGR_PLL1M);
        tmpreg2 |= (RCC_OscInitStruct->PLL1.PLLSource | pllsrc |
                    ((RCC_OscInitStruct->PLL1.PLLM - 1u) << RCC_PLL1CFGR_PLL1M_Pos) | RCC_PLL1CFGR_PLL1REN);
        RCC->PLL1CFGR = tmpreg2;

        /* Configure PLLN multiplication factor and PLLP, PLLQ, PLLR dividers */
        tmpreg2 = ((RCC_OscInitStruct->PLL1.PLLN - 1u) |
                   ((RCC_OscInitStruct->PLL1.PLLP - 1u) << RCC_PLL1DIVR_PLL1P_Pos) |
                   ((RCC_OscInitStruct->PLL1.PLLQ - 1u) << RCC_PLL1DIVR_PLL1Q_Pos) |
                   ((RCC_OscInitStruct->PLL1.PLLR - 1u) << RCC_PLL1DIVR_PLL1R_Pos));
        RCC->PLL1DIVR = tmpreg2;

        if (RCC_OscInitStruct->PLL1.PLLFractional != 0x00u)
        {
          assert_param(IS_RCC_PLLFRACN_VALUE(RCC_OscInitStruct->PLL1.PLLFractional));

          /* Configure PLL1 PLL1FRACN */
          __HAL_RCC_PLL1_FRACN_CONFIG(RCC_OscInitStruct->PLL1.PLLFractional);

          /* Enable PLL1FRACEN */
          __HAL_RCC_PLL1_FRACN_ENABLE();
        }

        /* Enable the main PLL1. */
        __HAL_RCC_PLL1_ENABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till PLL1 is ready */
        while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the main PLL1. */
        __HAL_RCC_PLL1_DISABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till PLL1 is disabled */
        while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        /* CLear the PLL1 source and disable outputs to save power when PLL1 is off */
        CLEAR_BIT(RCC->PLL1CFGR, (RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1PEN | \
                                  RCC_PLL1CFGR_PLL1QEN | RCC_PLL1CFGR_PLL1REN));
      }
    }
    else
    {
      /* Check if there is a request to disable the PLL1 used as System clock source */
      if ((RCC_OscInitStruct->PLL1.PLLState) == RCC_PLL_OFF)
      {
        return HAL_ERROR;
      }
      else
      {
        /* Do not return HAL_ERROR if request repeats the current configuration */
        tmpreg1 = RCC->PLL1CFGR;
        tmpreg2 = RCC->PLL1DIVR;

        if (((tmpreg1 & RCC_PLL1CFGR_PLL1SRC) != RCC_OscInitStruct->PLL1.PLLSource) ||
            (((tmpreg1 & RCC_PLL1CFGR_PLL1M) >> RCC_PLL1CFGR_PLL1M_Pos) != (RCC_OscInitStruct->PLL1.PLLM - 1u)) ||
            (((tmpreg2 & RCC_PLL1DIVR_PLL1N) >> RCC_PLL1DIVR_PLL1N_Pos) != (RCC_OscInitStruct->PLL1.PLLN - 1u)) ||
            (((tmpreg2 & RCC_PLL1DIVR_PLL1P) >> RCC_PLL1DIVR_PLL1P_Pos) != (RCC_OscInitStruct->PLL1.PLLP - 1u)) ||
            (((tmpreg2 & RCC_PLL1DIVR_PLL1Q) >> RCC_PLL1DIVR_PLL1Q_Pos) != (RCC_OscInitStruct->PLL1.PLLQ - 1u)) ||
            (((tmpreg2 & RCC_PLL1DIVR_PLL1R) >> RCC_PLL1DIVR_PLL1R_Pos) != (RCC_OscInitStruct->PLL1.PLLR - 1u)))
        {
          return HAL_ERROR;
        }
        else
        {
          /* Check if only fractional part needs to be updated  */
          tmpreg1 = ((RCC->PLL1FRACR & RCC_PLL1FRACR_PLL1FRACN) >> RCC_PLL1FRACR_PLL1FRACN_Pos);

          if (RCC_OscInitStruct->PLL1.PLLFractional != tmpreg1)
          {
            assert_param(IS_RCC_PLLFRACN_VALUE(RCC_OscInitStruct->PLL1.PLLFractional));

            /* Disable PLL1FRACEN */
            __HAL_RCC_PLL1_FRACN_DISABLE();

            /* Get Start Tick*/
            tickstart = HAL_GetTick();

            /* Wait at least 2 CK_REF (PLL input source divided by M) period to make sure next latched value will be taken into account. */
            while ((HAL_GetTick() - tickstart) < PLL_FRAC_WAIT_VALUE)
            {
            }

            /* Configure PLL1 PLL1FRACN */
            __HAL_RCC_PLL1_FRACN_CONFIG(RCC_OscInitStruct->PLL1.PLLFractional);

            /* Enable PLL1FRACEN to latch new value. */
            __HAL_RCC_PLL1_FRACN_ENABLE();
          }
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
  *            @arg FLASH_LATENCY_5   FLASH 5 Latency cycles
  *            @arg FLASH_LATENCY_6   FLASH 6 Latency cycles
  *            @arg FLASH_LATENCY_7   FLASH 7 Latency cycles
  *            @arg FLASH_LATENCY_8   FLASH 8 Latency cycles
  *            @arg FLASH_LATENCY_9   FLASH 9 Latency cycles
  *            @arg FLASH_LATENCY_10  FLASH 10 Latency cycles
  *            @arg FLASH_LATENCY_11  FLASH 11 Latency cycles
  *            @arg FLASH_LATENCY_12  FLASH 12 Latency cycles
  *            @arg FLASH_LATENCY_13  FLASH 13 Latency cycles
  *            @arg FLASH_LATENCY_14  FLASH 14 Latency cycles
  *            @arg FLASH_LATENCY_15  FLASH 15 Latency cycles
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency.
  * @note   The HSI (16 MHz) is used by default as system clock source after
  *         startup from Reset, wake-up from STANDBY mode.
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL1 locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source is ready.
  * @note   You can use HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  * @note   The SYSCLK shall only be switched to a higher frequency when incremental
  *         frequency step is 47 MHz. When this is not respected device operation cannot
  *         be guaranteed. For bigger incremental frequency steps the PLL1RCLKPRE division
  *         shall be used.
  * @note   HCLK5 frequency shall not be higher than 32 MHz in range 1, 12 MHz in range 2.
  *         Two different fields allow to configure HCLK5 prescaler: one when System clock
  *         source is to PLL1, other for any other sources.
  *         HCLK5 prescaler is switched automatically by hardware, but configuration shall
  *         always be performed before setting new PLL1 source as Sysclk source.
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

  /*-------------------------- HCLK5 Configuration --------------------------*/
  /* HCLK5 prescaler is switched automatically by hardware, but configuration shall
    always be performed before setting new PLL1 source as Sysclk source. */
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK5) == RCC_CLOCKTYPE_HCLK5)
  {
    assert_param(IS_RCC_HCLK5_HSEHSI(RCC_ClkInitStruct->AHB5_HSEHSI_CLKDivider));
    assert_param(IS_RCC_HCLK5_PLL1(RCC_ClkInitStruct->AHB5_PLL1_CLKDivider));
    MODIFY_REG(RCC->CFGR4, (RCC_CFGR4_HDIV5 | RCC_CFGR4_HPRE5),
               (RCC_ClkInitStruct->AHB5_PLL1_CLKDivider | RCC_ClkInitStruct->AHB5_HSEHSI_CLKDivider));
  }

  /*------------------------- SYSCLK Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
  {
    assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));

    /* Read CR register */
    tmpreg1 = RCC->CR;

    /* PLL1 is selected as System Clock Source */
    if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
    {
      /* Check the PLL1 ready flag */
      if ((tmpreg1 & RCC_CR_PLL1RDY) == 0U)
      {
        return HAL_ERROR;
      }
      else
      {
        if (__HAL_RCC_GET_SYSCLK_SOURCE() != (RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR1_SWS_Pos))
        {
          /* Whatever is PLL frequency, use step prediv to reach maximum frequency. */
          /* Select pll1r to be prediv with 2-step divider when selected as Sysclk source */
          MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRESTEP, RCC_PLL1CFGR_PLL1RCLKPRE);
#if defined(STM32WBAXX_SI_CUT1_0)
          /* add 2 pulse on CLKPRE bit : clear and set it back */
          CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRE);
          SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRE);
          CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRE);
          SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRE);
#endif
        }
      }
    }
    else
    {
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
      else
      {
        /* Check the HSI ready flag */
        if ((tmpreg1 & RCC_CR_HSIRDY) == 0U)
        {
          return HAL_ERROR;
        }
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

    /* If PLL1rCLK is asked to be SYSCLK source, clear prediv. */
    if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
    {
      /* Set PLL1R prediv to not divided */
      CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RCLKPRE);

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait until PLL1 not divided is ready */
      while ((RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1RCLKPRERDY) == 0x00u)
      {
        if ((HAL_GetTick() - tickstart) > PLL1_NDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
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

  /*-------------------------- PCLK7 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK7) == RCC_CLOCKTYPE_PCLK7)
  {
    assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB7CLKDivider));
    WRITE_REG(RCC->CFGR3, RCC_ClkInitStruct->APB7CLKDivider);
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
  * @brief  Select the clock source to output on MCO pin (PA8).
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOx  specifies the output direction for the clock source.
  *         For STM32WBAxx family this parameter can have only one value:
  *            @arg @ref RCC_MCO1  Clock source to output on MCO1 pin(PA8).
  * @param  RCC_MCOSource  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK   MCO output disabled, no clock on MCO
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK    System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI       HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE       HSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLL1RCLK  PLL1R clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI       LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE       LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLL1PCLK  PLL1P clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLL1QCLK  PLL1Q clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HCLK5     HCLK5 clock selected as MCO source
  * @param  RCC_MCODiv  specifies the MCO prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   no division applied to MCO clock
  *            @arg @ref RCC_MCODIV_2   division by 2 applied to MCO clock
  *            @arg @ref RCC_MCODIV_4   division by 4 applied to MCO clock
  *            @arg @ref RCC_MCODIV_8   division by 8 applied to MCO clock
  *            @arg @ref RCC_MCODIV_16  division by 16 applied to MCO clock
  * @retval None
  */
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCOx));
  assert_param(IS_RCC_MCODIV(RCC_MCODiv));
  assert_param(IS_RCC_MCO1SOURCE(RCC_MCOSource));

  /* MCO Clock Enable */
  __MCO1_CLK_ENABLE();

  /* Configure the MCO1 pin in alternate function mode */
  GPIO_InitStruct.Pin = MCO1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(MCO1_GPIO_PORT, &GPIO_InitStruct);

  /* Mask MCOSEL[] and MCOPRE[] bits then set MCO1 clock source and prescaler */
  MODIFY_REG(RCC->CFGR1, (RCC_CFGR1_MCOSEL | RCC_CFGR1_MCOPRE), (RCC_MCOSource | RCC_MCODiv));
}

/**
  * @brief  Return the SYSCLK frequency.
  * @note   The system frequency computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(**)
  * @note   If SYSCLK source is PLL1, function returns values based on HSE_VALUE(**),
  *         HSI_VALUE(*) or MSI Value multiplied/divided by the PLL1 factors.
  * @note   (*)  HSI_VALUE is a constant defined in stm32wbaxx_hal_conf.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (**) HSE_VALUE is a constant defined in stm32wbaxx_hal_conf.h file (default value
  *              32 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @note   Each time SYSCLK changes, this function must be called to update the
  *         right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  uint32_t sysclk;

  /* Get SYSCLK source */
  sysclk = __HAL_RCC_GET_SYSCLK_SOURCE();

  if (sysclk == RCC_SYSCLKSOURCE_STATUS_HSI)
  {
    /* HSI used as system clock source */
    sysclk = HSI_VALUE;
  }
  else if (sysclk == RCC_SYSCLKSOURCE_STATUS_HSE)
  {
    /* HSE used as system clock source. Check if HSE is divided by 2 */
    sysclk = (HSE_VALUE >> ((RCC->CR & RCC_CR_HSEPRE) >> RCC_CR_HSEPRE_Pos));
  }
  else
  {
    /* PLL1 used as system clock source */
    sysclk = HAL_RCC_GetPLL1RFreq();
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
  * @brief  Return the PCLK7 frequency.
  * @note   Each time PCLK7 changes, this function must be called to update the
  *         right PCLK7 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK7 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK7Freq(void)
{
  /* Get HCLK source and Compute PCLK7 frequency ---------------------------*/
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR3 & RCC_CFGR3_PPRE7) >> RCC_CFGR3_PPRE7_Pos]);
}

/**
  * @brief  Return the HCLK5 frequency.
  * @note   Each time HCLK5 changes, this function must be called to update the
  *         right HCLK5 value. Otherwise, any configuration based on this function will be incorrect.
  * @note   HCLK5 frequency depends on System clock source :
            - whenever PLL1 is selected as System clock source, HPRE5 prescaler is internally used to
            divide SYSCLK frequency and feed HCLK5.
            - whenever HSI or HSE are selected as System clock source, HDIV5 prescaler is internally used to
            divide SYSCLK frequency and feed HCLK5.
  *         right HCLK5 value. Otherwise, any configuration based on this function will be incorrect.
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency.
  * @retval HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLK5Freq(void)
{
  uint32_t tmp;
  uint32_t hclk5freq;

  /* Get source of SYSCLK */
  tmp = (RCC->CFGR1 & RCC_CFGR1_SWS);

  /* Depending on SYSCLK source */
  if (tmp != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
  {
    /* HSI or HSE are source of SYSCLK, compute divider */
    tmp = (RCC->CFGR4 & RCC_CFGR4_HDIV5) >> RCC_CFGR4_HDIV5_Pos;
    tmp += 1u;
  }
  else
  {
    /* PLL1 is source of SYSCLK, compute prescaler */
    tmp = AHB5PrescTable[(RCC->CFGR4 & RCC_CFGR4_HPRE5)];
  }

  /* Get SYCLK frequency */
  hclk5freq = (HAL_RCC_GetSysClockFreq() / tmp);

  return hclk5freq;
}

/**
  * @brief  Return the PLL1P frequency.
  * @retval PLL1P frequency in Hz
  */
uint32_t HAL_RCC_GetPLL1PFreq(void)
{
  uint32_t pllp;

  /* PLL1P divider */
  pllp = ((RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1P) >> RCC_PLL1DIVR_PLL1P_Pos) + 1U;

  /* Compute VCO output frequency and return PLL1P one */
  return ((uint32_t)RCC_PLL1_GetVCOOutputFreq() / pllp);
}

/**
  * @brief  Return the PLL1Q frequency.
  * @retval PLL1Q frequency in Hz
  */
uint32_t HAL_RCC_GetPLL1QFreq(void)
{
  uint32_t pllq;

  /* PLL1Q divider */
  pllq = ((RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1Q) >> RCC_PLL1DIVR_PLL1Q_Pos) + 1U;

  /* Compute VCO output frequency and return PLL1Q one */
  return ((uint32_t)RCC_PLL1_GetVCOOutputFreq() / pllq);
}

/**
  * @brief  Return the PLL1R frequency.
  * @retval PLL1R frequency in Hz
  */
uint32_t HAL_RCC_GetPLL1RFreq(void)
{
  uint32_t pllr;

  /* PLL1R divider */
  pllr = ((RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1R) >> RCC_PLL1DIVR_PLL1R_Pos) + 1U;

  /* Compute VCO output frequency and return PLL1R one */
  return ((uint32_t)RCC_PLL1_GetVCOOutputFreq() / pllr);
}

/**
  * @brief  Configure the RCC_OscInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_OscInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         will be configured.
  * @retval None
  */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  uint32_t regvalue;
  uint32_t mask;

  /* Check the parameters */
  assert_param(RCC_OscInitStruct != (void *)NULL);

  /* Set all possible values for the Oscillator type parameter ---------------*/
  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI  | \
                                      RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;

  /* Get Backup Domain register 1 */
  regvalue = RCC->BDCR1;

  /* Get the LSE configuration -----------------------------------------------*/
  mask = (RCC_BDCR1_LSEBYP | RCC_BDCR1_LSESYSEN | RCC_BDCR1_LSEON);
  RCC_OscInitStruct->LSEState = (regvalue & mask);

  /* Get the LSI configuration -----------------------------------------------*/
  mask = RCC_BDCR1_LSI1ON;
#if defined(RCC_LSI2_SUPPORT)
  mask |= RCC_BDCR1_LSI2ON;
#endif
  RCC_OscInitStruct->LSIState = (regvalue & mask);
  RCC_OscInitStruct->LSIDiv = (regvalue & RCC_BDCR1_LSI1PREDIV);

  /* Get Control register */
  regvalue = RCC->CR;

  /* Get the HSE configuration -----------------------------------------------*/
  RCC_OscInitStruct->HSEState = (regvalue & RCC_CR_HSEON);
  RCC_OscInitStruct->HSEDiv = (regvalue & RCC_CR_HSEPRE);

  /* Get the HSI configuration -----------------------------------------------*/
  RCC_OscInitStruct->HSIState = (regvalue & RCC_CR_HSION);
  RCC_OscInitStruct->HSICalibrationValue = ((RCC->ICSCR3 & RCC_ICSCR3_HSITRIM) >> RCC_ICSCR3_HSITRIM_Pos);

  /* Get the PLL1 configuration -----------------------------------------------*/
  if ((regvalue & RCC_CR_PLL1ON) != 0x00u)
  {
    RCC_OscInitStruct->PLL1.PLLState = RCC_PLL_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL1.PLLState = RCC_PLL_OFF;
  }

  /* Get PLL1 configuration register */
  regvalue = RCC->PLL1CFGR;
  RCC_OscInitStruct->PLL1.PLLSource = (regvalue & RCC_PLL1CFGR_PLL1SRC);
  RCC_OscInitStruct->PLL1.PLLM = (((regvalue & RCC_PLL1CFGR_PLL1M) >> RCC_PLL1CFGR_PLL1M_Pos) + 1U);

  /* Check if fractional part is enable */
  if ((regvalue & RCC_PLL1CFGR_PLL1FRACEN) != 0x00u)
  {
    regvalue = (((RCC->PLL1FRACR & RCC_PLL1FRACR_PLL1FRACN) >> RCC_PLL1FRACR_PLL1FRACN_Pos));
  }
  else
  {
    regvalue = 0;
  }
  RCC_OscInitStruct->PLL1.PLLFractional = regvalue;

  /* Get PLL1 dividers register */
  regvalue = RCC->PLL1DIVR;
  RCC_OscInitStruct->PLL1.PLLN = ((regvalue & RCC_PLL1DIVR_PLL1N) + 1U);
  RCC_OscInitStruct->PLL1.PLLQ = (((regvalue & RCC_PLL1DIVR_PLL1Q) >> RCC_PLL1DIVR_PLL1Q_Pos) + 1U);
  RCC_OscInitStruct->PLL1.PLLR = (((regvalue & RCC_PLL1DIVR_PLL1R) >> RCC_PLL1DIVR_PLL1R_Pos) + 1U);
  RCC_OscInitStruct->PLL1.PLLP = (((regvalue & RCC_PLL1DIVR_PLL1P) >> RCC_PLL1DIVR_PLL1P_Pos) + 1U);

}

/**
  * @brief  Configure the RCC_ClkInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_ClkInitStruct  pointer to an RCC_ClkInitTypeDef structure that
  *         will be configured.
  * @param  pFLatency  Pointer on the Flash Latency.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency)
{
  uint32_t tmpreg1;

  /* Check the parameters */
  assert_param(RCC_ClkInitStruct != (void *)NULL);
  assert_param(pFLatency != (void *)NULL);

  /* Set all possible values for the Clock type parameter --------------------*/
  RCC_ClkInitStruct->ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK7 | RCC_CLOCKTYPE_HCLK5);

  /* Get the SYSCLK configuration --------------------------------------------*/
  RCC_ClkInitStruct->SYSCLKSource = (RCC->CFGR1 & RCC_CFGR1_SW);

  /* Get the HCLK configuration ----------------------------------------------*/
  tmpreg1 = RCC->CFGR2;
  RCC_ClkInitStruct->AHBCLKDivider = (tmpreg1 & RCC_CFGR2_HPRE);

  /* Get the PCLK1 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB1CLKDivider = (tmpreg1 & RCC_CFGR2_PPRE1);

  /* Get the PCLK2 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB2CLKDivider = ((tmpreg1 & RCC_CFGR2_PPRE2) >> (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));

  /* Get the PCLK7 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB7CLKDivider = (RCC->CFGR3 & RCC_CFGR3_PPRE7);

  /* Get the PCLK1 configuration ----------------------------------------------*/
  tmpreg1 = RCC->CFGR4;
  RCC_ClkInitStruct->AHB5_PLL1_CLKDivider = (tmpreg1 & RCC_CFGR4_HPRE5);
  RCC_ClkInitStruct->AHB5_HSEHSI_CLKDivider = (tmpreg1 & RCC_CFGR4_HDIV5);

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

#if defined(RCC_PRIVCFGR_NSPRIV)
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

  switch (Attributes)
  {
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
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
#endif /* __ARM_FEATURE_CMSE */
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

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
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
#else
  /* Get Non-Secure privileges attribute */
  attributes = ((RCC->PRIVCFGR & RCC_PRIVCFGR_NSPRIV) == 0U) ? RCC_NSEC_NPRIV : RCC_NSEC_PRIV;
#endif /* __ARM_FEATURE_CMSE */

  /* return value */
  *pAttributes = attributes;

  return HAL_OK;
}
/**
  * @}
  */
#endif

/* Private functions ---------------------------------------------------------*/
/** @addtogroup RCC_Private_Functions
  * @{
  */
/**
  * @brief  Compute PLL1 VCO output frequency
  * @retval Value of PLL1 VCO output frequency
  */
static float_t RCC_PLL1_GetVCOOutputFreq(void)
{
  uint32_t tmpreg1;
  uint32_t tmp;
  float_t pllsrc;
  float_t pllm;
  float_t plln;
  float_t pllfracn;

  /* Get PLL1 DIVR register value */
  tmpreg1 = RCC->PLL1DIVR;

  /* Retrieve PLL1 multiplication factor */
  tmp = (tmpreg1 & RCC_PLL1DIVR_PLL1N) + 1U;
  plln = (float_t) tmp;

  /* Get PLL1 CFGR register value */
  tmpreg1 = RCC->PLL1CFGR;

  /* Retrieve PLL1 divider */
  tmp = ((tmpreg1 & RCC_PLL1CFGR_PLL1M) >> RCC_PLL1CFGR_PLL1M_Pos) + 1U;
  pllm = (float_t) tmp;

  /* Check if fractional part is enable */
  if ((tmpreg1 & RCC_PLL1CFGR_PLL1FRACEN) != 0x00u)
  {
    tmp = ((RCC->PLL1FRACR & RCC_PLL1FRACR_PLL1FRACN) >> RCC_PLL1FRACR_PLL1FRACN_Pos);
  }
  else
  {
    tmp = 0u;
  }
  pllfracn = (float_t)tmp;

  /* determine PLL source */
  switch (tmpreg1 & RCC_PLL1CFGR_PLL1SRC)
  {
    /* HSI used as PLL1 clock source */
    case RCC_PLLSOURCE_HSI:
      pllsrc = (float_t)HSI_VALUE;
      break;

    /* HSE used as PLL1 clock source */
    case RCC_PLLSOURCE_HSE:
      tmp = (HSE_VALUE >> ((RCC->CR & RCC_CR_HSEPRE) >> RCC_CR_HSEPRE_Pos));
      pllsrc = (float_t)tmp;
      break;

    default:
      pllsrc = (float_t)0;
      break;
  }

  /* Compute VCO output frequency */
  return ((pllsrc / pllm) * (plln + (pllfracn / (float_t)0x2000u)));
}


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

/**
  * @}
  */
