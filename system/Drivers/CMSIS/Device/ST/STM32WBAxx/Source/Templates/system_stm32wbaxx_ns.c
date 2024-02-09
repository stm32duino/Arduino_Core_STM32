/**
  ******************************************************************************
  * @file    system_stm32wbaxx_ns.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
  *          to be used in non-secure application when the system implements
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
  *      - SystemInit(): This function is called at non-secure startup before
  *                      branch to non-secure main program.
  *                      This call is made inside the "startup_stm32wbaxx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the HSI (16 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32wbaxx.s" file, to
  *   configure the system clock before to branch to main secure program.
  *   Later, when non-secure SystemInit() function is called, in "startup_stm32wbaxx.s"
  *   file, the system clock may have been updated from reset value by the main
  *   secure program.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup STM32WBAxx_system
  * @{
  */

/** @addtogroup STM32WBAxx_System_Private_Includes
  * @{
  */

#include "stm32wbaxx.h"

/**
  * @}
  */

/** @addtogroup STM32WBAxx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WBAxx_System_Private_Defines
  * @{
  */
#if !defined (HSE_VALUE)
#define HSE_VALUE     (32000000U) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined (HSI_VALUE)
#define HSI_VALUE     (16000000U) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

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
#define VECT_TAB_BASE_ADDRESS   SRAM2_BASE                 /*!< Vector Table base address field.
                                                                This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U                /*!< Vector Table base offset field.
                                                                This value must be a multiple of 0x200. */
#else
#define VECT_TAB_BASE_ADDRESS   (FLASH_BASE + 0x00080000U) /*!< Vector Table base address field.
                                                                This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U                /*!< Vector Table base offset field.
                                                                This value must be a multiple of 0x200. */
#endif /* VECT_TAB_SRAM */
#endif /* USER_VECT_TAB_ADDRESS */

/******************************************************************************/

/**
  * @}
  */

/** @addtogroup STM32WBAxx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WBAxx_System_Private_Variables
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
  uint32_t SystemCoreClock = 16000000U; /* The HSI16 is used as system clock source after startup from reset, configured at 16 MHz. */

  const uint8_t AHBPrescTable[8] = {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};
  const uint8_t APBPrescTable[8] = {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};
  const uint8_t AHB5PrescTable[8] = {1U, 1U, 1U, 1U, 2U, 3U, 4U, 6U};
/**
  * @}
  */

/** @addtogroup STM32WBAxx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WBAxx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
#endif

  /* Configure the Vector Table location -------------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation */
#endif /* USER_VECT_TAB_ADDRESS */

  /* Non-secure main application shall call SystemCoreClockUpdate() to update */
  /* the SystemCoreClock variable to insure non-secure application relies on  */
  /* the initial clock reference set by secure application.                   */
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   From the non-secure application, the SystemCoreClock value is
  *         retrieved from the secure domain via a Non-Secure Callable function
  *         since the RCC peripheral may be protected with security attributes
  *         that prevent to compute the SystemCoreClock variable from the RCC
  *         peripheral registers.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(**)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *           - If SYSCLK source is PLL1, SystemCoreClock will contain the HSE_VALUE(***)
  *             or HSI_VALUE(*)  multiplied/divided by the PLL1 factors.
  *
  *         (**) HSI_VALUE is a constant defined in STM32WBAxx_hal.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in STM32WBAxx_hal.h file (default value
  *              32 MHz), user has to ensure that HSE_VALUE is same as the real
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
  /* Get the SystemCoreClock value from the secure domain */
  SystemCoreClock = SECURE_SystemCoreClockUpdate();
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
