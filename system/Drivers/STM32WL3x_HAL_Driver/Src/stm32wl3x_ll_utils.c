/**
  ******************************************************************************
  * @file    stm32wl3x_ll_utils.c
  * @author  MCD Application Team
  * @brief   UTILS LL module driver.
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
/* Includes ------------------------------------------------------------------*/
#include "system_stm32wl3x.h"
#include "stm32wl3x_ll_utils.h"
#include "stm32wl3x_ll_rcc.h"
#include "stm32wl3x_ll_system.h"
#include "stm32wl3x_ll_pwr.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

/** @addtogroup UTILS_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup UTILS_LL_Private_Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup UTILS_LL_Private_Macros
  * @{
  */
#define IS_LL_UTILS_SYSCLK_DIV(__VALUE__) (((__VALUE__) == LL_RCC_RC64MPLL_DIV_1)   \
                                           || ((__VALUE__) == LL_RCC_RC64MPLL_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_RC64MPLL_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_RC64MPLL_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_RC64MPLL_DIV_16)   \
                                           || ((__VALUE__) == LL_RCC_RC64MPLL_DIV_32)   \
                                           || ((__VALUE__) == LL_RCC_RC64MPLL_DIV_64))

#define IS_LL_UTILS_DIRECT_HSE_DIV(__VALUE__) (((__VALUE__) == LL_RCC_DIRECT_HSE_DIV_1)   \
                                           || ((__VALUE__) == LL_RCC_DIRECT_HSE_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_DIRECT_HSE_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_DIRECT_HSE_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_DIRECT_HSE_DIV_16)   \
                                           || ((__VALUE__) == LL_RCC_DIRECT_HSE_DIV_32))


#define IS_LL_UTILS_HSE_BYPASS(__STATE__) (((__STATE__) == LL_UTILS_HSEBYPASS_ON) \
                                           || ((__STATE__) == LL_UTILS_HSEBYPASS_OFF))

#define countof(a)   (sizeof(a) / sizeof(*(a)))
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup UTILS_LL_Exported_Functions
  * @{
  */

/** @addtogroup UTILS_LL_EF_DELAY
  * @{
  */

/**
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  HCLKFrequency SysClk frequency in Hz
  * @retval None
  */

void LL_Init1msTick(uint32_t HCLKFrequency)
{
  /* Use frequency provided in argument */
  LL_InitTick(HCLKFrequency, 1000);
}


/**
  * @brief  This function provides accurate delay (in milliseconds) based
  *         on SysTick counter flag
  * @note   When a RTOS is used, it is recommended to avoid using blocking delay
  *         and use rather osDelay service.
  * @note   To respect 1ms timebase, user should call @ref LL_Init1msTick function which
  *         will configure Systick to 1ms
  * @param  Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void LL_mDelay(uint32_t Delay)
{
  uint32_t mDelay = Delay;
  __IO uint32_t  tmp = SysTick->CTRL;  /* Clear the COUNTFLAG first */
  /* Add this code to indicate that local variable is not used */
  ((void)tmp);

  /* Add a period to guaranty minimum wait */
  if (mDelay < LL_MAX_DELAY)
  {
    mDelay++;
  }

  while (mDelay != 0U)
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
    {
      mDelay--;
    }
  }
}

/**
  * @}
  */

/** @addtogroup UTILS_LL_EF_SYSTEM
  * @{
  */

/**
  * @brief  This function sets directly SystemCoreClock CMSIS variable.
  * @note   Variable can be calculated also through SystemCoreClockUpdate function.
  * @param  HCLKFrequency HCLK frequency in Hz (can be calculated thanks to RCC helper macro)
  * @retval None
  */
void LL_SetSystemCoreClock(uint32_t HCLKFrequency)
{
  /* HCLK clock frequency */
  SystemCoreClock = HCLKFrequency;
}

/**
  * @brief  This function return the System Core Clock expressed in Hz.
  * @retval System Core Clock frequency.
  */
uint32_t LL_GetSystemCoreClock(void)
{
  return SystemCoreClock;
}


#if defined(STM32WL3XX)
/**
  * @brief This function set the HSE XTAL frequency expressed in Hz.
  * @param freq HSE XTAL frequency expressed in Hz.
  */
void LL_SetXTALFreq(uint32_t freq)
{
  HSE_xtalFrequency = freq;

  switch(LL_RCC_GetRC64MPLLPrescaler())
  {
  case LL_RCC_RC64MPLL_DIV_1:
    if (LL_RCC_DIRECT_HSE_IsEnabled())
      SystemCoreClock = HSE_xtalFrequency;
    else
      SystemCoreClock = (HSE_xtalFrequency/3)*4;
    break;
  case LL_RCC_RC64MPLL_DIV_2:
    if (LL_RCC_DIRECT_HSE_IsEnabled())
      SystemCoreClock = HSE_xtalFrequency/2;
    else
      SystemCoreClock = (HSE_xtalFrequency/3)*2;
    break;
  case LL_RCC_RC64MPLL_DIV_4:
    SystemCoreClock = HSE_xtalFrequency/3;
    break;
  case LL_RCC_RC64MPLL_DIV_8:
    SystemCoreClock = HSE_xtalFrequency/6;
    break;
  case LL_RCC_RC64MPLL_DIV_16:
    SystemCoreClock = HSE_xtalFrequency/12;
    break;
  case LL_RCC_RC64MPLL_DIV_32:
    SystemCoreClock = HSE_xtalFrequency/24;
    break;
   case LL_RCC_RC64MPLL_DIV_64:
     SystemCoreClock = HSE_xtalFrequency/48;
     break;
  }
}

/**
  * @brief  This function returns the HSE XTAL frequency expressed in Hz.
  * @retval HSE XTAL frequency frequency.
  */
uint32_t LL_GetXTALFreq(void)
{
  return HSE_xtalFrequency;
}
#endif /* STM32WL3XX */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
