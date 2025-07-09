
/**
  ******************************************************************************
  * @file    system_stm32wb0x.c
  * @author  GPM WBL Application Team
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File
  *
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
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32wb0x.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the HSI (64 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32wb0x.s" file, to
  *   configure the system clock before to branch to main program.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                     | HSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                              | 16000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                                | 16000000
  *-----------------------------------------------------------------------------
  *=============================================================================
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup STM32WB0x_system
  * @{
  */

/** @addtogroup STM32WB0x_System_Private_Includes
  * @{
  */

#include "stm32wb0x.h"

/**
  * @}
  */

/** @addtogroup STM32WB0x_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WB0x_System_Private_Defines
  * @{
  */

/* Note: Following vector table addresses must be defined in line with linker
         configuration. */

/*!< Uncomment the following line if you need to relocate your vector Table
     in SRAM else user remap will be done in FLASH. */
/* #define VECT_TAB_SRAM */

#if !defined(VECT_TAB_BASE_ADDRESS)
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS   SRAM_BASE       /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x100. */
#else
#define VECT_TAB_BASE_ADDRESS   NVM_BASE        /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x100. */
#endif /* VECT_TAB_SRAM */
#endif /* USER_VECT_TAB_ADDRESS */

#if !defined(VECT_TAB_OFFSET)
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table offset field.
                                                     This value must be a multiple of 0x100. */
#endif /* VECT_TAB_OFFSET */



/******************************************************************************/

/*!< HW TRIMMING Defines */
#define VALIDITY_TAG      0xFCBCECCC  /*!< TAG to validate the content of the
					   trimming area content. */
#define VALIDITY_LOCATION 0x10001EF8  /*!< ROM address of the the validity trimming values content. */

/*!< SMPS Configuration Defines */
#if !defined(CFG_HW_SMPS)
#define CFG_HW_SMPS SMPS_ON
#endif

#if !defined(CFG_HW_SMPS_BOM)
#define CFG_HW_SMPS_BOM SMPS_BOM3 /*!< SMPS Inductor 10uH */
#endif

#if !defined(CFG_HW_SMPS_LOW_POWER)
#define CFG_HW_SMPS_LOW_POWER SMPS_LOW_POWER_OPEN
#endif

/**
  * @}
  */

/** @addtogroup STM32WB0x_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WB0x_System_Private_Variables
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
  uint32_t SystemCoreClock = 16000000U; /* The HSI (64MHz) is used as system clock source after startup from reset, configured at 16 MHz. */

  /* The RAM_VR variable is a mirroring in RAM of some registers information.
     It is a sort of virtual register in RAM.
  */
#if defined ( __ICCARM__ )
  #pragma location=".ram_vr"
  __root __no_init RAM_VR_TypeDef RAM_VR;
#else
#if defined ( __ARMCC_VERSION )
  __attribute__((section(".bss" ".ram_vr")))
#elif defined (  __GNUC__  )
  __attribute__((section(".ram_vr")))
#endif
  RAM_VR_TypeDef RAM_VR __attribute__((used));
#endif
/**
  * @}
  */

/** @addtogroup STM32WB0x_System_Private_FunctionPrototypes
  * @{
  */

void CPUcontextRestore(void);

/**
  * @}
  */

/** @addtogroup STM32WB0x_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
  uint32_t mainRegulator, smpsOutVoltage, hsiCalib;
#if defined(STM32WB06) || defined(STM32WB07)
  uint32_t lsiLpmu;
#else
  uint32_t lsiBw;
#endif
  uint8_t i;

  /* If the reset reason is a wakeup from power save restore the context */
  if ((RCC->CSR == 0) && ((PWR->SR1 != 0)||(PWR->SR3 != 0))) {
    RAM_VR.WakeupFromSleepFlag = 1; /* A wakeup from power save occurred */
    CPUcontextRestore();            /* Restore the context */
    /* if the context restore worked properly, we should never return here */
    while(1) {
      NVIC_SystemReset();
    }
  }

  /* Configure the Vector Table location */
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation */

  /* Store in RAM the AppBase information */
  RAM_VR.AppBase = (uint32_t) SCB->VTOR;

  /* Enable all the RAM banks in retention during power save */
#if defined(PWR_CR2_RAMRET1)
  SET_BIT(PWR->CR2, PWR_CR2_RAMRET1);
#endif /* PWR_CR2_RAMRET1 */

#if defined(PWR_CR2_RAMRET2)
  SET_BIT(PWR->CR2, PWR_CR2_RAMRET2);
#endif /* PWR_CR2_RAMRET2 */

#if defined(PWR_CR2_RAMRET3)
  SET_BIT(PWR->CR2, PWR_CR2_RAMRET3);
#endif /* PWR_CR2_RAMRET3 */

  /* Disable the GPIO retention in power save configuration */
#if defined(PWR_CR2_GPIORET)
  CLEAR_BIT(PWR->CR2, PWR_CR2_GPIORET);
#endif /* PWR_CR2_GPIORET */

  /* SMPS setup */
  if ((CFG_HW_SMPS == SMPS_ON) || (CFG_HW_SMPS == SMPS_BYPAPSS))
  {
    while(READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) != PWR_SR2_SMPSRDY); // Wait until SMPS is ready
    MODIFY_REG(PWR->CR5, PWR_CR5_SMPSBOMSEL, (CFG_HW_SMPS_BOM<<PWR_CR5_SMPSBOMSEL_Pos)); // Configure the SMPS BOM
  }
  if ((CFG_HW_SMPS == SMPS_ON) || (CFG_HW_SMPS == SMPS_OFF))
  {
    MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, (CFG_HW_SMPS<<PWR_CR5_NOSMPS_Pos)); // SMPS ON/OFF Configuration
  }
  else
  {
    MODIFY_REG(PWR->CR5, PWR_CR5_SMPSFBYP, (1<<PWR_CR5_SMPSFBYP_Pos)); // SMPS BYPASS Configuration
  }
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLPOPEN, (CFG_HW_SMPS_LOW_POWER<<PWR_CR5_SMPSLPOPEN_Pos)); // SMPS configuration during power save

  /* If Trimming values from engineering in flash locations are not present load default values */
  if (*(volatile uint32_t*)VALIDITY_LOCATION != VALIDITY_TAG)
  {
#if defined(STM32WB06) || defined(STM32WB07)
    hsiCalib       = 0x1E;
    mainRegulator  = 0x08;
    smpsOutVoltage = 0x03;
    lsiLpmu        = 0x08;

    /* Set Low Speed Internal oscillator LPMU trimming value. */
    MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_LSI_LPMU, ((lsiLpmu << PWR_ENGTRIM_TRIM_LSI_LPMU_Pos) & PWR_ENGTRIM_TRIM_LSI_LPMU));
    SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMLSILPMUEN);
#else
    hsiCalib       = 0x1F;
    lsiBw          = 8;
    mainRegulator  = 0x0A;
    smpsOutVoltage = 0x03;

    /* Low speed internal RC trimming value set by software */
    MODIFY_REG(RCC->CSSWCR, RCC_CSSWCR_LSISWBW, lsiBw << RCC_CSSWCR_LSISWBW_Pos);
    SET_BIT(RCC->CSSWCR, RCC_CSSWCR_LSISWTRIMEN);
#endif

    /* Set HSI Calibration Trimming value */
    MODIFY_REG(RCC->CSSWCR, RCC_CSSWCR_HSITRIMSW, hsiCalib << RCC_CSSWCR_HSITRIMSW_Pos);
    SET_BIT(RCC->CSSWCR, RCC_CSSWCR_HSISWTRIMEN);

    /* Set Main Regulator voltage Trimming value */
    MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_TRIM_MR, ((mainRegulator << PWR_ENGTRIM_TRIM_MR_Pos) & PWR_ENGTRIM_TRIM_MR));
    SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_TRIMMREN);

    /* Set SMPS output voltage Trimming value */
    MODIFY_REG(PWR->ENGTRIM, PWR_ENGTRIM_SMPS_TRIM, ((smpsOutVoltage << PWR_ENGTRIM_SMPS_TRIM_Pos) & PWR_ENGTRIM_SMPS_TRIM));
    SET_BIT(PWR->ENGTRIM, PWR_ENGTRIM_SMPSTRIMEN);
  }

  /* Set all the interrupt with low priprity */
  for (i=0; i<32; i++)
  {
    NVIC_SetPriority((IRQn_Type)i, IRQ_LOW_PRIORITY);
  }

  /* Enable all the irqs */
  __enable_irq();
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
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint8_t directHSE_enabled;
  uint8_t divPrescaler;

  /* Get SYSCLK source HSE or HSI+PLL64MHz */
  directHSE_enabled = (RCC->CFGR & RCC_CFGR_HSESEL) >> RCC_CFGR_HSESEL_Pos;

#if defined(STM32WB06) || defined(STM32WB07)
  /* Get the clock divider */
    divPrescaler = (RCC->CFGR & RCC_CFGR_CLKSYSDIV) >> RCC_CFGR_CLKSYSDIV_Pos;
#else
  /* Get the clock divider */
  divPrescaler = (RCC->CFGR & RCC_CFGR_CLKSYSDIV_STATUS) >> RCC_CFGR_CLKSYSDIV_STATUS_Pos;
#endif

  if (directHSE_enabled)
  {
    SystemCoreClock = HSE_VALUE >> (divPrescaler - 1U);
  }
  else
  {
    SystemCoreClock = HSI_VALUE >> divPrescaler;
  }
}

/**
  * @brief  Restores the saved CPU state before to enter in power save
  *         by popping it from the stack
  * @param  None
  * @retval None
  */
__WEAK void CPUcontextRestore(void)
{
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
