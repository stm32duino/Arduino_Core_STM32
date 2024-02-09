/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_utils.c
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
#include "stm32wbaxx_ll_utils.h"
#include "stm32wbaxx_ll_rcc.h"
#include "stm32wbaxx_ll_system.h"
#include "stm32wbaxx_ll_pwr.h"
#include <math.h>
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32WBAxx_LL_Driver
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

/* Defines used for PLL range */
#define UTILS_PLLVCO_INPUT_MIN        4000000U  /*!< Frequency min for PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MAX       16000000U  /*!< Frequency max for PLLVCO input, in Hz   */
#define UTILS_PLLVCO_OUTPUT_MIN     128000000U  /*!< Frequency min for PLLVCO output, in Hz  */
#define UTILS_PLLVCO_OUTPUT_MAX     544000000U  /*!< Frequency max for PLLVCO output, in Hz  */

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
#define IS_LL_UTILS_SYSCLK_DIV(__VALUE__) (((__VALUE__) == LL_RCC_SYSCLK_DIV_1)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_16))

#define IS_LL_UTILS_APB1_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB1_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_16))

#define IS_LL_UTILS_APB2_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB2_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_16))

#define IS_LL_UTILS_APB7_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB7_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB7_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB7_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB7_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB7_DIV_16))

#define IS_LL_UTILS_PLLM_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 16U))

#define IS_LL_UTILS_PLLN_VALUE(__VALUE__) ((4U <= (__VALUE__)) && ((__VALUE__) <= 512U))

#define IS_LL_UTILS_PLLR_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 128U))

#define IS_LL_UTILS_PLLVCO_INPUT(__VALUE__)  ((UTILS_PLLVCO_INPUT_MIN <= (__VALUE__))\
                                              && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX))

#define IS_LL_UTILS_PLLVCO_OUTPUT(__VALUE__) ((UTILS_PLLVCO_OUTPUT_MIN <= (__VALUE__))\
                                              && ((__VALUE__) <= UTILS_PLLVCO_OUTPUT_MAX))

#define IS_LL_UTILS_PLL_FREQUENCY(__VALUE__) ((LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1) ? \
                                              ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE1) : \
                                              ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE2))

#define IS_LL_UTILS_HSE_FREQUENCY(__FREQUENCY__) ((__FREQUENCY__) == 32000000U)
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/** @defgroup UTILS_LL_Private_Functions UTILS Private functions
  * @{
  */
static uint32_t    UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency,
                                               const LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct);
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency,
                                                  LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
static ErrorStatus UTILS_PLL_IsBusy(void);
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

             (++) Table 1. HCLK clock frequency for STM32WBA devices
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
  * @brief  This function configures system clock at maximum frequency with HSI as clock source of the PLL
  * @note   The application need to ensure that PLL1, PLL2 and/or PLL3 are disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = (((HSI frequency / PLLM) * PLLN) / PLLR)
  *         - PLL1M: ensure that the VCO input frequency ranges from 4 to 16 MHz (PLL1VCO_input = HSI frequency / PLL1M)
  *         - PLL1N: ensure that the VCO output frequency is between 128 and 544 MHz
             (PLL1VCO_output = PLL1VCO_input * PLL1N)
  *         - PLL1R: ensure that max frequency at 100 MHz is reached (PLL1VCO_output / PLL1R)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  */
ErrorStatus LL_PLL1_ConfigSystemClock_HSI(LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                          LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
  uint32_t pllfreq;

  /* Check if one of the PLL is enabled */
  if (UTILS_PLL_IsBusy() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(HSI_VALUE, UTILS_PLLInitStruct);

    /* Enable HSI if not enabled */
    if (LL_RCC_HSI_IsReady() != 1U)
    {
      LL_RCC_HSI_Enable();
      while (LL_RCC_HSI_IsReady() != 1U)
      {
        /* Wait for HSI ready */
      }
    }

    /* Configure PLL */
    LL_RCC_PLL1_ConfigDomain_SYS(LL_RCC_PLL1SOURCE_HSI, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                 UTILS_PLLInitStruct->PLLR);

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);
  }
  else
  {
    /* Current PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  This function configures system clock with HSE as clock source of the PLL
  * @note   The application need to ensure that PLL, PLLSAI1 and/or PLLSAI2 are disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = (((HSE frequency / PLLM) * PLLN) / PLLR)
  *         - PLL1M: ensure that the VCO input frequency ranges from 4 to 16 MHz (PLL1VCO_input = HSE frequency / PLL1M)
  *         - PLL1N: ensure that the VCO output frequency is between 128 and 544 MHz
             (PLL1VCO_output = PLL1VCO_input * PLL1N)
  *         - PLL1R: ensure that max frequency at 100 MHz is reached (PLL1VCO_output / PLL1R)
  * @param  HSEFrequency Value at 32000000
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  */
ErrorStatus LL_PLL1_ConfigSystemClock_HSE(uint32_t HSEFrequency,
                                          LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                          LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
  uint32_t pllfreq;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_HSE_FREQUENCY(HSEFrequency));

  /* Check if one of the PLL is enabled */
  if (UTILS_PLL_IsBusy() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(HSEFrequency, UTILS_PLLInitStruct);

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

    /* Configure PLL */
    LL_RCC_PLL1_ConfigDomain_SYS(LL_RCC_PLL1SOURCE_HSE, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                 UTILS_PLLInitStruct->PLLR);

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);
  }
  else
  {
    /* Current PLL configuration cannot be modified */
    status = ERROR;
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
  * @brief  Function to check that PLL can be modified
  * @param  PLL_InputFrequency  PLL input frequency (in Hz)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @retval PLL output frequency (in Hz)
  */
static uint32_t UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency, const LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct)
{
  uint32_t pllfreq;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_PLLM_VALUE(UTILS_PLLInitStruct->PLLM));
  assert_param(IS_LL_UTILS_PLLN_VALUE(UTILS_PLLInitStruct->PLLN));
  assert_param(IS_LL_UTILS_PLLR_VALUE(UTILS_PLLInitStruct->PLLR));

  /* Check different PLL parameters according to RM                          */
  /*  - PLLM: ensure that the VCO input frequency ranges from 4 to 16 MHz.   */
  pllfreq = PLL_InputFrequency / (UTILS_PLLInitStruct->PLLM);
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(pllfreq));

  /*  - PLLN: ensure that the VCO output frequency is between 128 and 544 MHz.*/
  pllfreq = pllfreq * (UTILS_PLLInitStruct->PLLN);
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(pllfreq));

  /*  - PLLR: ensure that max frequency at 100 MHz is reached                   */
  pllfreq = pllfreq / (UTILS_PLLInitStruct->PLLR);
  assert_param(IS_LL_UTILS_PLL_FREQUENCY(pllfreq));

  return pllfreq;
}

/**
  * @brief  Function to check that PLL can be modified
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLL modification can be done
  *          - ERROR: PLL is busy
  */
static ErrorStatus UTILS_PLL_IsBusy(void)
{
  ErrorStatus status = SUCCESS;

  /* Check if PLL1 is busy*/
  if (LL_RCC_PLL1_IsReady() != 0U)
  {
    /* PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Function to enable PLL and switch system clock to PLL
  * @param  SYSCLK_Frequency SYSCLK frequency
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: No problem to switch system to PLL
  *          - ERROR: Problem to switch system to PLL
  */
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency,
                                                  LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status = SUCCESS;
  uint32_t hclk_frequency;

  assert_param(IS_LL_UTILS_SYSCLK_DIV(UTILS_ClkInitStruct->AHBCLKDivider));
  assert_param(IS_LL_UTILS_APB1_DIV(UTILS_ClkInitStruct->APB1CLKDivider));
  assert_param(IS_LL_UTILS_APB2_DIV(UTILS_ClkInitStruct->APB2CLKDivider));
  assert_param(IS_LL_UTILS_APB7_DIV(UTILS_ClkInitStruct->APB7CLKDivider));

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
    /* Enable PLL1 */
    LL_RCC_PLL1_Enable();
    LL_RCC_PLL1_EnableDomain_PLL1R();
    while (LL_RCC_PLL1_IsReady() != 1U)
    {
      /* Wait for PLL ready */
    }

    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->AHBCLKDivider);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1R);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1R)
    {
      /* Wait for system clock switch to PLL */
    }

    /* Set APB1, APB2 & APB7 prescaler*/
    LL_RCC_SetAPB1Prescaler(UTILS_ClkInitStruct->APB1CLKDivider);
    LL_RCC_SetAPB2Prescaler(UTILS_ClkInitStruct->APB2CLKDivider);
    LL_RCC_SetAPB7Prescaler(UTILS_ClkInitStruct->APB7CLKDivider);
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
