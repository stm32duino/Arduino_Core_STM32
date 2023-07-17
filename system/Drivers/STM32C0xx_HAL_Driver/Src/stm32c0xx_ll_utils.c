/**
  ******************************************************************************
  * @file    stm32c0xx_ll_utils.c
  * @author  MCD Application Team
  * @brief   UTILS LL module driver.
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
/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_ll_utils.h"
#include "stm32c0xx_ll_rcc.h"
#include "stm32c0xx_ll_system.h"
#include "stm32c0xx_ll_pwr.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32C0xx_LL_Driver
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
#define UTILS_MAX_FREQUENCY          48000000U     /*!< Maximum frequency for system clock, in Hz */

/* Defines used for HSE range */
#define UTILS_HSE_FREQUENCY_MIN      4000000U      /*!< Frequency min for HSE frequency, in Hz   */
#define UTILS_HSE_FREQUENCY_MAX      48000000U     /*!< Frequency max for HSE frequency, in Hz   */

/* Defines used for FLASH latency according to HCLK Frequency */
#define UTILS_SCALE1_LATENCY1_FREQ  24000000U       /*!< HCLK frequency to set FLASH latency 1 in power scale 1  */
#define UTILS_SCALE1_LATENCY2_FREQ  48000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 1  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup UTILS_LL_Private_Macros
  * @{
  */
#define IS_LL_UTILS_SYSCLK_DIV(__VALUE__) (((__VALUE__) == LL_RCC_HCLK_DIV_1)    \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_16)  \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_64)  \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_128) \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_256) \
                                           || ((__VALUE__) == LL_RCC_HCLK_DIV_512))

#define IS_LL_UTILS_APB1_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB1_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_16))

#define IS_LL_UTILS_HSI_DIV(__VALUE__)  (((__VALUE__) == LL_RCC_HSI_DIV_1)  \
                                         || ((__VALUE__) == LL_RCC_HSI_DIV_2)  \
                                         || ((__VALUE__) == LL_RCC_HSI_DIV_4)  \
                                         || ((__VALUE__) == LL_RCC_HSI_DIV_8)  \
                                         || ((__VALUE__) == LL_RCC_HSI_DIV_16) \
                                         || ((__VALUE__) == LL_RCC_HSI_DIV_32) \
                                         || ((__VALUE__) == LL_RCC_HSI_DIV_64) \
                                         || ((__VALUE__) == LL_RCC_HSI_DIV_128))

#define IS_LL_UTILS_HSIKER_DIV(__VALUE__)  (((__VALUE__) == LL_RCC_HSIKER_DIV_1)  \
                                            || ((__VALUE__) == LL_RCC_HSIKER_DIV_2)  \
                                            || ((__VALUE__) == LL_RCC_HSIKER_DIV_3)  \
                                            || ((__VALUE__) == LL_RCC_HSIKER_DIV_4)  \
                                            || ((__VALUE__) == LL_RCC_HSIKER_DIV_5) \
                                            || ((__VALUE__) == LL_RCC_HSIKER_DIV_6) \
                                            || ((__VALUE__) == LL_RCC_HSIKER_DIV_7) \
                                            || ((__VALUE__) == LL_RCC_HSIKER_DIV_8))

#define IS_LL_UTILS_HSE_BYPASS(__STATE__) (((__STATE__) == LL_UTILS_HSEBYPASS_ON) \
                                           || ((__STATE__) == LL_UTILS_HSEBYPASS_OFF))

#define IS_LL_UTILS_HSE_FREQUENCY(__FREQUENCY__) (((__FREQUENCY__) >= UTILS_HSE_FREQUENCY_MIN)\
                                                  && ((__FREQUENCY__) <= UTILS_HSE_FREQUENCY_MAX))
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
  * @param  HCLKFrequency HCLK frequency in Hz
  * @note   HCLK frequency can be calculated thanks to RCC helper macro or function @ref LL_RCC_GetSystemClocksFreq
  * @retval None
  */
void LL_Init1msTick(uint32_t HCLKFrequency)
{
  /* Use frequency provided in argument */
  LL_InitTick(HCLKFrequency, 1000U);
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
  __IO uint32_t  tmp = SysTick->CTRL;  /* Clear the COUNTFLAG first */
  uint32_t tmpDelay; /* MISRAC2012-Rule-17.8 */
  /* Add this code to indicate that local variable is not used */
  ((void)tmp);
  tmpDelay  = Delay;
  /* Add a period to guaranty minimum wait */
  if (tmpDelay  < LL_MAX_DELAY)
  {
    tmpDelay ++;
  }

  while (tmpDelay  != 0U)
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
    {
      tmpDelay --;
    }
  }
}

/**
  * @}
  */

/** @addtogroup UTILS_EF_SYSTEM
  *  @brief    System Configuration functions
  *
  @verbatim
 ===============================================================================
           ##### System Configuration functions #####
 ===============================================================================
    [..]
         System, AHB and APB buses clocks configuration

         (+) The maximum frequency of the SYSCLK, HCLK, PCLK1 is 48000000 Hz.
  @endverbatim
  @internal
             Depending on the device voltage range, the maximum frequency should be
             adapted accordingly:

             (++)  Table 1. HCLK clock frequency.
             (++)  +------------------------------------+
             (++)  | Latency         |  HCLK clock      |
             (++)  |                 |  frequency (MHz) |
             (++)  |                 |                  |
             (++)  |                 |-------------------
             (++)  |                 | voltage range 1  |
             (++)  |                 |   1.08V - 1.32V  |
             (++)  |-----------------|------------------|
             (++)  |0WS(1 CPU cycles)|      HCLK <= 24  |
             (++)  |-----------------|------------------|
             (++)  |1WS(2 CPU cycles)|      HCLK <= 48  |
             (++)  +------------------------------------+

  @endinternal
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
  * @}
  */

/**
  * @}
  */

/** @addtogroup UTILS_LL_Private_Functions
  * @{
  */
/**
  * @brief  Update number of Flash wait states in line with new frequency and current
            voltage range.
  * @param  HCLK_Frequency  HCLK frequency
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Latency has been modified
  *          - ERROR: Latency cannot be modified
  */
ErrorStatus LL_SetFlashLatency(uint32_t HCLK_Frequency)
{
  uint32_t timeout;
  uint32_t getlatency;
  uint32_t latency;
  ErrorStatus status;

  /* Frequency cannot be equal to 0 */
  if ((HCLK_Frequency == 0U) || (HCLK_Frequency > UTILS_SCALE1_LATENCY2_FREQ))
  {
    status = ERROR;
  }
  else
  {
    if (HCLK_Frequency > UTILS_SCALE1_LATENCY1_FREQ)
    {
      /* 24 < HCLK <= 48 => 1WS (2 CPU cycles) */
      latency = LL_FLASH_LATENCY_1;
    }
    else
    {
      /* else HCLK_Frequency < 24MHz default LL_FLASH_LATENCY_0 0WS */
      latency = LL_FLASH_LATENCY_0;
    }

    LL_FLASH_SetLatency(latency);

    /* Check that the new number of wait states is taken into account to access the Flash
       memory by reading the FLASH_ACR register */
    timeout = 2;
    do
    {
      /* Wait for Flash latency to be updated */
      getlatency = LL_FLASH_GetLatency();
      timeout--;
    } while ((getlatency != latency) && (timeout > 0U));

    if(getlatency != latency)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
  return status;
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
