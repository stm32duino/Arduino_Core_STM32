/**
  ******************************************************************************
  * @file    system_stm32u3xx_s.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
  *          to be used in secure application when the system implements
  *          the TrustZone-M security.
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
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32u3xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *      - SECURE_SystemCoreClockUpdate(): Non-secure callable function to update
  *                                        the variable SystemCoreClock and return
  *                                        its value to the non-secure calling
  *                                        application. It must be called whenever
  *                                        the core clock is changed during program
  *                                        execution.
  *
  *   After each device reset the MSI (12 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32u3xx.s" file, to
  *   configure the system clock before to branch to main program.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                     | MSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                              | 12000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                                | 12000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                           | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB3 Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *=============================================================================
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup STM32U3xx_system
  * @{
  */

/** @addtogroup STM32U3xx_System_Private_Includes
  * @{
  */
#include "stm32u3xx.h"
#include "partition_stm32u3xx.h"  /* Trustzone-M core secure attributes */

/**
  * @}
  */

/** @addtogroup STM32U3xx_System_Private_TypesDefinitions
  * @{
  */

#if defined ( __ICCARM__ )
#  define CMSE_NS_ENTRY __cmse_nonsecure_entry
#else
#  define CMSE_NS_ENTRY __attribute((cmse_nonsecure_entry))
#endif
/**
  * @}
  */

/** @addtogroup STM32U3xx_System_Private_Defines
  * @{
  */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE             32000000U /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE             16000000U /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined  (MSIRC0_VALUE)
  #define MSIRC0_VALUE          96000000U /*!< Value of the Internal MSI RC0 oscillator in Hz*/
#endif /* MSI_VALUE */

#if !defined  (MSIRC1_VALUE)
  #define MSIRC1_VALUE          24000000U /*!< Value of the Internal MSI RC1 oscillator in Hz*/
#endif /* MSI_VALUE */

/* Note: Following vector table addresses must be defined in line with linker
         configuration. */
/*!< Uncomment the following line if you need to relocate the vector table
     anywhere in Flash or Sram, else the vector table is kept at the automatic
     remap of boot address selected */
/* #define USER_VECT_TAB_ADDRESS */

#if defined(USER_VECT_TAB_ADDRESS)
/*!< Uncomment the following line if you need to relocate your vector Table
     in Sram else user remap will be done in Flash. */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS   SRAM1_BASE      /*!< Vector Table base address field.
                                   This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
#else
#define VECT_TAB_BASE_ADDRESS   FLASH_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
#endif /* VECT_TAB_SRAM */
#endif /* USER_VECT_TAB_ADDRESS */

/******************************************************************************/

/**
  * @}
  */

/** @addtogroup STM32U3xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32U3xx_System_Private_Variables
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
uint32_t SystemCoreClock = (MSIRC1_VALUE >> 1u);
const uint8_t AHBPrescTable[16] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
const uint8_t APBPrescTable[8] = {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};
/**
  * @}
  */

/** @addtogroup STM32U3xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32U3xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
  /* SAU/IDAU, FPU and Interrupts secure/non-secure allocation settings */
  TZ_SAU_Setup();

  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
#endif

  /* Configure the Vector Table location -------------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation */
#endif /* USER_VECT_TAB_ADDRESS */
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
  *           - If SYSCLK source is MSI, SystemCoreClock will be computed based on
  *             MSIRC0_VALUE(*) or MSIRC1_VALUE(*), depending on MSI source selected.
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(**)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *         (*) MSIRC0_VALUE and MSIRC1_VALUE are constant defined in stm32u3xx_hal_conf.h
  *             file (default values are respectively 96 MHz and 24 MHz)  but the real
  *             value may vary depending on the variations in voltage and temperature.
  *
  *         (**) HSI_VALUE is a constant defined in stm32u3xx_hal.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32u3xx_hal.h file (default value
  *              16 MHz), user has to ensure that HSE_VALUE is same as the real
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
  uint32_t tmp, msirange;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR1 & RCC_CFGR1_SWS)
  {
  case 0x00:  /* MSIS used as system clock source */
    /* Read RCC ICSR1 register */
    tmp = RCC->ICSCR1;
    /* Check which MSIS Range is selected */
    if ((tmp & RCC_ICSCR1_MSIRGSEL) != 0x00u)
  {
      /* Check which MSIRCx is selected as MSIS source */
      if ((tmp & RCC_ICSCR1_MSISSEL) != 0x00u)
      {
        /* MSI RC1 is selected */
        SystemCoreClock = MSIRC1_VALUE;
  }
  else
  {
        /* MSI RC0 is selected */
        SystemCoreClock = MSIRC0_VALUE;
  }

      /* Get MSIS range */
      msirange = (tmp & RCC_ICSCR1_MSISDIV) >> RCC_ICSCR1_MSISDIV_Pos;
    }
    else
    {
      /* MSI RC1 is selected */
      SystemCoreClock = MSIRC1_VALUE;

      /* Get MSIS range */
      msirange = (RCC->CSR & (RCC_CSR_MSISDIVS_1 | RCC_CSR_MSISDIVS_0)) >> RCC_CSR_MSISDIVS_Pos;
    }

    /*MSIS frequency in HZ*/
    SystemCoreClock >>= msirange;
    break;

  case RCC_CFGR1_SWS_0:  /* HSI used as system clock source */
    SystemCoreClock = HSI_VALUE;
    break;

  case RCC_CFGR1_SWS_1:  /* HSE used as system clock source */
    SystemCoreClock = HSE_VALUE;
    break;

  default:
    SystemCoreClock = 0xFFFFFFFFu;
    break;
  }

  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR2 & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}

/**
  * @brief  Secure Non-Secure-Callable function to return the current
  *         SystemCoreClock value after SystemCoreClock update.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  * @retval SystemCoreClock value (HCLK)
  */
CMSE_NS_ENTRY uint32_t SECURE_SystemCoreClockUpdate(void)
{
  SystemCoreClockUpdate();

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
