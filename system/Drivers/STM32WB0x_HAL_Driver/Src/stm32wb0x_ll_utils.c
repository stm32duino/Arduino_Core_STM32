/**
  ******************************************************************************
  * @file    stm32wb0x_ll_utils.c
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
#include "stm32wb0x_ll_utils.h"
#include "stm32wb0x_ll_rcc.h"
#include "stm32wb0x_ll_system.h"
#include "stm32wb0x_ll_pwr.h"
#include "stm32_assert.h"

/** @addtogroup STM32WB0x_LL_Driver
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
/** @defgroup UTILS_LL_Private_Functions UTILS Private functions
  * @{
  */

/**
  * @}
  */

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

/**
  * @brief  This function sets the System Core Clock.
  * @param  HCLKFrequency system clock divided factor from HSI64MPLL
  *         This parameter can be one of the following values:
  *         SYSCLK_64M
  *         SYSCLK_32M
  *         SYSCLK_16M
  *         SYSCLK_8M
  *         SYSCLK_4M
  *         SYSCLK_2M
  *         SYSCLK_1M
  *         SYSCLK_DIRECT_HSE
  *         SYSCLK_DIRECT_HSE_DIV2
  * @retval SUCCESS or error code
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


/**
  * @}
  */



/**
  * @}
  */

/**
  * @}
  */
