/**
  ******************************************************************************
  * @file    system_stm32u0xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File
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
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32u0xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the MSI (4 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32u0xx.s" file, to
  *   configure the system clock before to branch to main program.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                    | MSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 4000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 4000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        HSI Division factor                    | 1
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 1
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 8
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 7
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_R                                  | 2
  *-----------------------------------------------------------------------------
  *        Require 48MHz for RNG                  | Disabled
  *-----------------------------------------------------------------------------
  *=============================================================================
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32u0xx_system
  * @{
  */

/** @addtogroup STM32U0xx_System_Private_Includes
  * @{
  */

#include "stm32u0xx.h"

#if !defined  (HSE_VALUE)
#define HSE_VALUE    (32000000U)     /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    (16000000UL)    /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined  (MSI_VALUE)
#define MSI_VALUE    (4000000UL)     /*!< Value of the Internal oscillator in Hz*/
#endif /* MSI_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    (32000UL)       /*!< Value of the Internal oscillator in Hz */
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    (32768UL)       /*!< Value of the External oscillator in Hz */
#endif /* LSE_VALUE */

/**
  * @}
  */

/** @addtogroup STM32U0xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32U0xx_System_Private_Defines
  * @{
  */

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
//#define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0U /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */

/*!< Comment the following line if you would like to disable the software
     workaround related to debug access in case RDP=1 and Boot_Lock=1      */
#define ENABLE_DBG_SWEN /*!< Enable the debugger read access. */
/******************************************************************************/
/**
  * @}
  */

/** @addtogroup STM32U0xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32U0xx_System_Private_Variables
  * @{
  */
/* The SystemCoreClock variable is updated in three ways:
    1) by calling CMSIS function SystemCoreClockUpdate()
    2) by calling HAL API function HAL_RCC_GetHCLKFreq()
    3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
       Note: If you use this function to configure the system clock; then there
             is no need to call the 2 first functions listed above, since SystemCoreClock
             variable is updated automatically.
*/
uint32_t SystemCoreClock = 4000000U;

const uint8_t  AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t  APBPrescTable[8] =  {0, 0, 0, 0, 1, 2, 3, 4};
const uint32_t MSIRangeTable[12] = {100000U,   200000U,   400000U,   800000U,  1000000U,  2000000U, \
                                    4000000U, 8000000U, 16000000U, 24000000U, 32000000U, 48000000U
                                   };

/**
  * @}
  */

/** @addtogroup STM32U0xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32U0xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
#ifdef ENABLE_DBG_SWEN
uint32_t tmp_seccr;
uint32_t tmp_optr;
#endif /* ENABLE_DBG_SWEN */
  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM1_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif /* VECT_TAB_SRAM */

/* Software workaround added to keep Debug enabled after Boot_Lock activation and RDP=1  */
#ifdef ENABLE_DBG_SWEN
  tmp_seccr = FLASH->SECR;
  tmp_optr = FLASH->OPTR;
  if (((tmp_seccr & FLASH_SECR_BOOT_LOCK) == FLASH_SECR_BOOT_LOCK)         \
      && (((tmp_optr & FLASH_OPTR_RDP) != 0xCCU)                           \
      && ((tmp_optr & FLASH_OPTR_RDP) != 0xAAU)))
  {
    FLASH->ACR |= FLASH_ACR_DBG_SWEN;  /* Debug access software enabled to avoid the chip
                                          to be locked when RDP=1 and Boot_Lock=1        */
  }
#endif /* ENABLE_DBG_SWEN */
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is MSI, SystemCoreClock will contain the MSI_VALUE(*)
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(**)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(***)
  *             or HSI_VALUE(*) or MSI_VALUE(*) multiplied/divided by the PLL factors.
  *
  *         (*) MSI_VALUE is a constant defined in stm32u0xx_hal.h file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSI_VALUE is a constant defined in stm32u0xx_hal.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32u0xx_hal.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t tmp, msirange, pllvco, pllsource, pllm, pllr;

  /* Get MSI Range frequency--------------------------------------------------*/
  if ((RCC->CR & RCC_CR_MSIRGSEL) == 0U)
  {
    /* MSISRANGE from RCC_CSR applies */
    msirange = (RCC->CSR & RCC_CSR_MSISTBYRG) >> 8U;
  }
  else
  {
    /* MSIRANGE from RCC_CR applies */
    msirange = (RCC->CR & RCC_CR_MSIRANGE) >> 4U;
  }
  /* MSI frequency range in HZ*/
  if (msirange > 11U)
  {
    msirange = 0U;
  }
  msirange = MSIRangeTable[msirange];

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case 0x00:  /* MSI used as system clock source */
      SystemCoreClock = msirange;
      break;

    case RCC_CFGR_SWS_0:  /* HSI used as system clock source */
      SystemCoreClock = HSI_VALUE;
      break;

    case RCC_CFGR_SWS_1:  /* HSE used as system clock source */
      SystemCoreClock = HSE_VALUE;
      break;

    case RCC_CFGR_SWS_2:  /* LSI used as system clock */
      SystemCoreClock = LSI_VALUE;
      break;

    case (RCC_CFGR_SWS_2 | RCC_CFGR_SWS_0):  /* LSE used as system clock */
      SystemCoreClock = LSE_VALUE;
      break;

    case (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0):  /* PLL used as system clock  source */
      /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
         SYSCLK = PLL_VCO / PLLR
         */
      pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
      pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1U ;

      switch (pllsource)
      {
        case RCC_PLLCFGR_PLLSRC_0:  /* MSI used as PLL clock source */
          pllvco = (msirange / pllm);
          break;

        case RCC_PLLCFGR_PLLSRC_1:  /* HSI used as PLL clock source */
          pllvco = (HSI_VALUE / pllm);
          break;

        case (RCC_PLLCFGR_PLLSRC_1 | RCC_PLLCFGR_PLLSRC_0):  /* HSE used as PLL clock source */
          pllvco = (HSE_VALUE / pllm);
          break;

        default:  /* no clock used as PLL clock source */
          pllvco = 0x0U;
          break;
      }
      pllvco = pllvco * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos);
      pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos) + 1UL);
      SystemCoreClock = pllvco / pllr;
      break;

    default:
      SystemCoreClock = msirange;
      break;
  }
  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos) & 0xFU];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
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
