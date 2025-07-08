/**
  ******************************************************************************
  * @file    stm32wb0x_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32wb0x_ll_rcc.h"
#ifdef USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32WB0x_LL_Driver
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

#if defined(RCC_CFGR_LPUCLKSEL)
#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__) ((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE)
#endif /* RCC_CFGR_LPUCLKSEL */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private functions
  * @{
  */
static uint32_t RCC_GetSystemClockFreq(void);

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
  * @brief  Reset the RCC clock  to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - HSI ON and used as system clock source
  *         - HSE and PLL Source OFF
  *         - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RCC_DeInit(void)
{
  uint32_t vl_mask;

  /* Disable all the HS clock source */
  LL_RCC_HSE_Disable();
  LL_RCC_RC64MPLL_Disable();

  /* Set the System Clock prescaler to reset state */
  LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_4);

  /* Wait for PLL READY bit to be reset */
  while (LL_RCC_RC64MPLL_IsReady() != 0U)
  {}

  /* Insure HSIRDY bit is set */
  while (LL_RCC_HSI_IsReady() == 0U)
  {}

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupt flags */
  vl_mask = RCC_CIFR_LSIRDYF | RCC_CIFR_LSERDYF | RCC_CIFR_HSIRDYF | RCC_CIFR_HSERDYF | RCC_CIFR_HSIPLLRDYF;
  LL_RCC_WriteReg(CIFR, vl_mask);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequency of the system clock device.
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   (**) HSI_VALUE is a constant defined in this file (default value
  *              64 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (***) HSE_VALUE is a constant defined in this file (default value
  *               32 MHz). The HSE_VALUE value is divided from a 64 MHz PLL to return
  *               frequency of the crystal used.
  * @{
  */

/**
  * @brief  Return the frequency of the system clock.
  * @param  RCC_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval None
  */
void LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks)
{
  /* Get SYSCLK frequency */
  RCC_Clocks->SYSCLK_Frequency = RCC_GetSystemClockFreq();
}

/**
  * @brief  Return SMPS clock frequency
  * @note   This function is only applicable when CPU runs.
  * @retval SMPS clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that the peripheral has a wrong ANADIV prescaler setup
  */
uint32_t LL_RCC_GetSMPSClockFreq(void)
{
  uint32_t smps_frequency;
  uint32_t smps_prescaler;

  smps_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  smps_prescaler = LL_RCC_GetSMPSPrescaler();
  if (smps_prescaler == LL_RCC_SMPS_DIV_2)
  {
    smps_frequency = 32000000 / 4;
  }
  else
  {
    smps_frequency = 32000000 / 8;
  }

  return smps_frequency;
}

#if defined(RCC_CFGR_LPUCLKSEL)
/**
  * @brief  Return LPUARTx clock frequency
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval LPUART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (CLK_16M or LSE) is not ready
  */
uint32_t LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource)
{
  uint32_t lpuart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPUART_CLKSOURCE(LPUARTxSource));

  /* LPUART1CLK clock frequency */
  if (LPUARTxSource == LL_RCC_LPUART1_CLKSOURCE)
  {
    switch (LL_RCC_GetLPUARTClockSource())
    {
      case LL_RCC_LPUCLKSEL_CLKLSE: /* LPUART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lpuart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPUCLKSEL_CLK16M: /* LPUART1 Clock is CLK_16M */
        lpuart_frequency = 16000000U;
        break;

      default:
        break;
    }
  }

  return lpuart_frequency;
}
#endif /* RCC_CFGR_LPUCLKSEL */

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
  * @brief  Return SYSTEM clock (SYSCLK) frequency
  * @retval SYSTEM clock frequency (in Hz)
  */
static uint32_t RCC_GetSystemClockFreq(void)
{
  uint32_t frequency;
  uint32_t smps_prescaler=0;

  frequency = RC64MPLL_VALUE;

  if (LL_RCC_DIRECT_HSE_IsEnabled())
  {
    frequency = HSE_VALUE;

#if defined(RCC_CFGR_CLKSYSDIV_STATUS)
    switch (LL_RCC_GetCLKSYSPrescalerStatus())
#else
    switch (LL_RCC_GetRC64MPLLPrescaler())
#endif
    {
      case LL_RCC_DIRECT_HSE_DIV_1:
        smps_prescaler = 1;
        break;
      case LL_RCC_DIRECT_HSE_DIV_2:
        smps_prescaler = 2;
        break;
      case LL_RCC_DIRECT_HSE_DIV_4:
        smps_prescaler = 4;
        break;
      case LL_RCC_DIRECT_HSE_DIV_8:
        smps_prescaler = 8;
        break;
      case LL_RCC_DIRECT_HSE_DIV_16:
        smps_prescaler = 16;
        break;
      case LL_RCC_DIRECT_HSE_DIV_32:
        smps_prescaler = 32;
        break;
    }
  }
  else
  {
    frequency = RC64MPLL_VALUE;

#if defined(RCC_CFGR_CLKSYSDIV_STATUS)
    switch (LL_RCC_GetCLKSYSPrescalerStatus())
#else
    switch (LL_RCC_GetRC64MPLLPrescaler())
#endif
    {
      case LL_RCC_RC64MPLL_DIV_1:
        smps_prescaler = 1;
        break;
      case LL_RCC_RC64MPLL_DIV_2:
        smps_prescaler = 2;
        break;
      case LL_RCC_RC64MPLL_DIV_4:
        smps_prescaler = 4;
        break;
      case LL_RCC_RC64MPLL_DIV_8:
        smps_prescaler = 8;
        break;
      case LL_RCC_RC64MPLL_DIV_16:
        smps_prescaler = 16;
        break;
      case LL_RCC_RC64MPLL_DIV_32:
        smps_prescaler = 32;
        break;
      case LL_RCC_RC64MPLL_DIV_64:
        smps_prescaler = 64;
        break;
    }
  }

  return (uint32_t)(frequency / smps_prescaler);
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
