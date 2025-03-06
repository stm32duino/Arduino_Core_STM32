/**
  ******************************************************************************
  * @file    stm32u3xx_ll_utils.c
  * @author  MCD Application Team
  * @brief   UTILS LL module driver.
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
#include "stm32u3xx_ll_utils.h"
#include "stm32u3xx_ll_rcc.h"
#include "stm32u3xx_ll_system.h"
#include "stm32u3xx_ll_pwr.h"
#include <math.h>
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32U3xx_LL_Driver
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
#define UTILS_MAX_FREQUENCY_SCALE1  100000000U  /*!< Maximum frequency for system clock at power scale1, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE2   16000000U  /*!< Maximum frequency for system clock at power scale2, in Hz */

/* Defines used for FLASH latency according to HCLK Frequency */
#define UTILS_SCALE1_LATENCY0_FREQ   32000000U  /*!< HCLK frequency to set FLASH latency 0 in power scale 1 */
#define UTILS_SCALE1_LATENCY1_FREQ   64000000U  /*!< HCLK frequency to set FLASH latency 1 in power scale 1 */
#define UTILS_SCALE1_LATENCY2_FREQ   96000000U  /*!< HCLK frequency to set FLASH latency 2 in power scale 1 */
#define UTILS_SCALE1_LATENCY3_FREQ  100000000U  /*!< HCLK frequency to set FLASH latency 3 in power scale 1 */
#define UTILS_SCALE2_LATENCY0_FREQ    8000000U  /*!< HCLK frequency to set FLASH latency 0 in power scale 2 */
#define UTILS_SCALE2_LATENCY1_FREQ   16000000U  /*!< HCLK frequency to set FLASH latency 1 in power scale 2 */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup UTILS_LL_Private_Macros
  * @{
  */



#define IS_LL_UTILS_SYSCLK_DIV(__VALUE__) (((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_1)      \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_16)  \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_64)  \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_128) \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_256) \
                                           || ((__VALUE__) == LL_RCC_HCLK_SYSCLK_DIV_512))

#define IS_LL_UTILS_APB1_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB1_HCLK_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB1_HCLK_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB1_HCLK_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB1_HCLK_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB1_HCLK_DIV_16))

#define IS_LL_UTILS_APB2_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB2_HCLK_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB2_HCLK_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB2_HCLK_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB2_HCLK_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB2_HCLK_DIV_16))

#define IS_LL_UTILS_APB3_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB3_HCLK_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB3_HCLK_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB3_HCLK_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB3_HCLK_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB3_HCLK_DIV_16))


#define IS_LL_UTILS_HSE_FREQUENCY(__FREQUENCY__) ((__FREQUENCY__) == 32000000U)
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/** @defgroup UTILS_LL_Private_Functions UTILS Private functions
  * @{
  */
static ErrorStatus UTILS_SwitchSystem(uint32_t SYSCLK_Frequency,
                                      LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
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
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base with HCLK as SysTick clock source.
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
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base with HCLK/8 as SysTick clock source.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  HCLKFrequency HCLK frequency in Hz
  * @retval None
  */
void LL_Init1msTick_HCLK_Div8(uint32_t HCLKFrequency)
{
  /* Configure the SysTick to have  1ms time base with HCLK/8 as SysTick clock source */
  SysTick->LOAD = (uint32_t)((HCLKFrequency / 8000U) - 1UL);
  SysTick->VAL = 0UL;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base with LSE as SysTick clock source.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @retval None
  */
void LL_Init1msTick_LSE(void)
{
  /* Configure the SysTick to have  1ms time base with LSE as SysTick clock source */
  SysTick->LOAD = (uint32_t)((LSE_VALUE / 1000U) - 1UL);
  SysTick->VAL = 0UL;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base with LSI as SysTick clock source.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @retval None
  */
void LL_Init1msTick_LSI(void)
{
  /* Configure the SysTick to have  1ms time base with LSI as SysTick clock source */
  SysTick->LOAD = (uint32_t)((LSI_VALUE / 1000U) - 1UL);
  SysTick->VAL = 0UL;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  This function provides minimum delay (in milliseconds) based
  *         on SysTick counter flag
  * @note   When a RTOS is used, it is recommended to avoid using blocking delay
  *         and use rather osDelay service.
  * @note   To respect 1ms timebase, user should call @ref LL_Init1msTick function which
  *         will configure Systick to 1ms
  * @param  Delay specifies the minimum delay time length, in milliseconds.
  * @retval None
  */
void LL_mDelay(uint32_t Delay)
{
  __IO uint32_t  tmp = SysTick->CTRL;  /* Clear the COUNTFLAG first */
  uint32_t tmpDelay = Delay;

  /* Add this code to indicate that local variable is not used */
  ((void)tmp);

  /* Add a period to guaranty minimum wait */
  if (tmpDelay < LL_MAX_DELAY)
  {
    tmpDelay++;
  }

  while (tmpDelay != 0U)
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
    {
      tmpDelay--;
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

         (+) The maximum frequency of the SYSCLK, HCLK, PCLK1 and PCLK2, PCLK7 is
             100000000 Hz.
  @endverbatim
  @internal
             Depending on the device voltage range, the maximum frequency should be
             adapted accordingly:

             (++) Table 1. HCLK clock frequency for STM32U3 devices
             (++) +----------------------------------------------------------+
             (++) | Latency           |       HCLK clock frequency (MHz)     |
             (++) |                   |--------------------------------------|
             (++) |                   |  voltage range 1  |  voltage range 2 |
             (++) |                   |       1.2 V       |       1.1 V      |
             (++) |-------------------|-------------------|------------------|
             (++) |0 WS (1 CPU cycles)|   0 < HCLK <= 32  |  0 < HCLK <= 8   |
             (++) |-------------------|-------------------|------------------|
             (++) |1 WS (2 CPU cycles)|  32 < HCLK <= 64  |  25 < HCLK <= 16 |
             (++) |-------------------|-------------------|------------------|
             (++) |2 WS (3 CPU cycles)|  64 < HCLK <= 96  |  50 < HCLK <= 24 |
             (++) |-------------------|-------------------|------------------|
             (++) |3 WS (4 CPU cycles)|  96 < HCLK <= 100 |
             (++) |-------------------|-------------------|


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
  * @brief  This function configures system clock at maximum frequency with HSI as clock source
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  */
ErrorStatus LL_ConfigSystemClock_HSI16(LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;

  /* Enable HSI if not enabled */
  if (LL_RCC_HSI_IsReady() != 1U)
  {
    LL_RCC_HSI_Enable();
    while (LL_RCC_HSI_IsReady() != 1U)
    {
      /* Wait for HSI ready */
    }
  }

  status = UTILS_SwitchSystem(HSI_VALUE,UTILS_ClkInitStruct);

  return status;
}

/**
  * @brief  This function configures system clock with HSE as clock source
  * @param  HSEFrequency Value at 32000000
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  */
ErrorStatus LL_ConfigSystemClock_HSE(uint32_t HSEFrequency, LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_HSE_FREQUENCY(HSEFrequency));

  /* Enable HSE if not enabled */
  if (LL_RCC_HSE_IsReady() != 1U)
  {
    /* Enable HSE */
    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1U)
    {
      /* Wait for HSE ready */
    }
  }

  status = UTILS_SwitchSystem(HSEFrequency,UTILS_ClkInitStruct);

  return status;
}

/**
  * @}
  */

/**
  * @}
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
  ErrorStatus status = SUCCESS;
  uint32_t latency;

  /* Frequency cannot be equal to 0 */
  if (HCLK_Frequency == 0U)
  {
    status = ERROR;
  }
  else
  {
    if (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1)
    {
      if ((HCLK_Frequency > UTILS_SCALE1_LATENCY2_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY3_FREQ))
      {
        /* 96MHz < HCLK <= 100MHz => 3WS (4 CPU cycles) */
        latency = LL_FLASH_LATENCY_3;
      }
      else if ((HCLK_Frequency > UTILS_SCALE1_LATENCY1_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY2_FREQ))
      {
        /* 64MHz < HCLK <= 96MHz => 2WS (3 CPU cycles) */
        latency = LL_FLASH_LATENCY_2;
      }
      else if ((HCLK_Frequency > UTILS_SCALE1_LATENCY0_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY1_FREQ))
      {
        /* 32MHz < HCLK <= 64MHz  => 1WS (2 CPU cycles) */
        latency = LL_FLASH_LATENCY_1;
      }
      else if (HCLK_Frequency <= UTILS_SCALE1_LATENCY0_FREQ)
      {
        /* HCLK <= 32MHz => 0WS (1 CPU cycle) */
        latency = LL_FLASH_LATENCY_0;
      }
      else
      {
        status = ERROR;
      }
    }
    else /* LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE2 */
    {
      if ((HCLK_Frequency > UTILS_SCALE2_LATENCY0_FREQ) && (HCLK_Frequency <= UTILS_SCALE2_LATENCY1_FREQ))
      {
        /* 8MHz < HCLK <= 16MHz => 1WS (2 CPU cycles) */
        latency = LL_FLASH_LATENCY_1;
      }
      else if (HCLK_Frequency <= UTILS_SCALE2_LATENCY0_FREQ)
      {
        /* HCLK <= 8MHz => 0WS (1 CPU cycle) */
        latency = LL_FLASH_LATENCY_0;
      }
      else
      {
        status = ERROR;
      }
    }
  }

  if (status == SUCCESS)
  {
    LL_FLASH_SetLatency(latency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if (LL_FLASH_GetLatency() != latency)
    {
      status = ERROR;
    }
  }

  return status;
}

/** @addtogroup UTILS_LL_Private_Functions
  * @{
  */
/**
  * @brief  Function to enable PLL and switch system clock to PLL
  * @param  SYSCLK_Frequency SYSCLK frequency
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: No problem to switch system to PLL
  *          - ERROR: Problem to switch system to PLL
  */
static ErrorStatus UTILS_SwitchSystem(uint32_t SYSCLK_Frequency,
                                      LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status = SUCCESS;
  uint32_t hclk_frequency;

  assert_param(IS_LL_UTILS_SYSCLK_DIV(UTILS_ClkInitStruct->AHBCLKDivider));
  assert_param(IS_LL_UTILS_APB1_DIV(UTILS_ClkInitStruct->APB1CLKDivider));
  assert_param(IS_LL_UTILS_APB2_DIV(UTILS_ClkInitStruct->APB2CLKDivider));
  assert_param(IS_LL_UTILS_APB3_DIV(UTILS_ClkInitStruct->APB3CLKDivider));

  /* Calculate HCLK frequency */
  hclk_frequency = __LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, UTILS_ClkInitStruct->AHBCLKDivider);

  /* Increasing the number of wait states because of higher CPU frequency */
  if (SystemCoreClock < hclk_frequency)
  {
    /* Set FLASH latency to highest latency */
    status = LL_SetFlashLatency(hclk_frequency);
  }

  /* Update system clock configuration */
  if (status == SUCCESS)
  {
    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->AHBCLKDivider);

    /* Set APB1, APB2 & APB3 prescaler*/
    LL_RCC_SetAPB1Prescaler(UTILS_ClkInitStruct->APB1CLKDivider);
    LL_RCC_SetAPB2Prescaler(UTILS_ClkInitStruct->APB2CLKDivider);
    LL_RCC_SetAPB3Prescaler(UTILS_ClkInitStruct->APB3CLKDivider);
  }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (SystemCoreClock > hclk_frequency)
  {
    /* Set FLASH latency to lowest latency */
    status = LL_SetFlashLatency(hclk_frequency);
  }

  /* Update SystemCoreClock variable */
  if (status == SUCCESS)
  {
    LL_SetSystemCoreClock(hclk_frequency);
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
