/**
  ******************************************************************************
  * @file    system_stm32wl3x.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex Device Peripheral Access Layer System Source File
  *
  ******************************************************************************
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32wl3x.s" file.
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
  *   Then SystemInit() function is called, in "startup_stm32wl3x.s" file, to
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup STM32WL3x_system
  * @{
  */

/** @addtogroup STM32WL3x_System_Private_Includes
  * @{
  */

#include "stm32wl3x.h"

/**
  * @}
  */

/** @addtogroup STM32WL3x_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WL3x_System_Private_Defines
  * @{
  */

/* Note: Following vector table addresses must be defined in line with linker
         configuration. */
/*!< Uncomment the following line and change the address
     if you need to relocate your vector Table at a custom base address (+ VECT_TAB_OFFSET) */
/* #define VECT_TAB_BASE_ADDRESS 0x08000000 */

#if !defined(VECT_TAB_OFFSET)
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x100. */
#endif  /* VECT_TAB_OFFSET */
#if !defined(VECT_TAB_BASE_ADDRESS)
/*!< Uncomment the following line if you need to relocate your vector Table
     in SRAM else user remap will be done in FLASH. */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS   SRAM_BASE       /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x100. */
#else
#define VECT_TAB_BASE_ADDRESS   FLASH_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x100. */
#endif /* VECT_TAB_SRAM */
#endif /* VECT_TAB_BASE_ADDRESS */
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

/** @addtogroup STM32WL3x_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WL3x_System_Private_Variables
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

  /* Crystal frequency */
  uint32_t HSE_xtalFrequency = HSE_VALUE;

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

/** @addtogroup STM32WL3x_System_Private_FunctionPrototypes
  * @{
  */

void CPUcontextRestore(void);

/**
  * @}
  */

/** @addtogroup STM32WL3x_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
  uint32_t mainRegulator, smpsOutVoltage, lsiBw, hsiCalib;
  uint8_t i;

  /* If the reset reason is a wakeup from power save restore the context */
  if ((RCC->CSR == 0) && ((PWR->IWUF != 0) || (PWR->WUFA != 0) || (PWR->WUFB != 0)))
  {
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
  SET_BIT(PWR->CR2, PWR_CR2_RAMRET1);

  /* Disable the GPIO retention in power save configuration */
  CLEAR_BIT(PWR->CR2, PWR_CR2_GPIORET);

  /* SMPS setup */
  if ((CFG_HW_SMPS == SMPS_ON) || (CFG_HW_SMPS == SMPS_STATIC_BOF) || (CFG_HW_SMPS == SMPS_DYNAMIC_BOF))
  {
    while(READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) != PWR_SR2_SMPSRDY); // Wait until SMPS is ready
    MODIFY_REG(PWR->CR5, PWR_CR5_SMPSBOMSEL, (CFG_HW_SMPS_BOM<<PWR_CR5_SMPSBOMSEL_Pos)); // Configure the SMPS BOM
  }
  if ((CFG_HW_SMPS == SMPS_ON) || (CFG_HW_SMPS == SMPS_OFF))
  {
    MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, (CFG_HW_SMPS<<PWR_CR5_NOSMPS_Pos)); // SMPS ON/OFF Configuration
  }
  if (CFG_HW_SMPS == SMPS_STATIC_BOF)
  {
    SET_BIT(PWR->CR5, PWR_CR5_NOSMPS_BOF);
    CLEAR_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_DYN);
    SET_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_STATIC);
  }
  if (CFG_HW_SMPS == SMPS_DYNAMIC_BOF)
  {
    /* The SMPS output voltage level and SMPS BOF tuning are set to 1.4V by default */
    SET_BIT(PWR->CR5, PWR_CR5_NOSMPS_BOF);
    CLEAR_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_STATIC);
    SET_BIT(PWR->CR5, PWR_CR5_SMPS_BOF_DYN);
  }
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLPOPEN, (CFG_HW_SMPS_LOW_POWER<<PWR_CR5_SMPSLPOPEN_Pos)); // SMPS configuration during power save

  /* If Trimming values from engineering in flash locations are not present load default values */
  if (*(volatile uint32_t*)VALIDITY_LOCATION != VALIDITY_TAG)
  {
    hsiCalib       = 0x21;
    lsiBw          = 8;
    mainRegulator  = 0x03;
    smpsOutVoltage = 0x03;

    /* Set HSI Calibration Trimming value */
    MODIFY_REG(RCC->CSSWCR, RCC_CSSWCR_HSITRIMSW, hsiCalib << RCC_CSSWCR_HSITRIMSW_Pos);
    SET_BIT(RCC->CSSWCR, RCC_CSSWCR_HSISWTRIMEN);

    /* Low speed internal RC trimming value set by software */
    MODIFY_REG(RCC->CSSWCR, RCC_CSSWCR_LSISWBW, lsiBw << RCC_CSSWCR_LSISWBW_Pos);
    SET_BIT(RCC->CSSWCR, RCC_CSSWCR_LSISWTRIMEN);

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

  /* Get the clock divider */
  divPrescaler = (RCC->CFGR & RCC_CFGR_CLKSYSDIV_STATUS) >> RCC_CFGR_CLKSYSDIV_STATUS_Pos;

  if (directHSE_enabled)
  {
    switch(divPrescaler)
    {
    case 0:
      SystemCoreClock = HSE_VALUE;
      break;
    case 1:
      SystemCoreClock = HSE_VALUE/2;
      break;
    default:
      SystemCoreClock = HSE_VALUE/(3*(1<<(divPrescaler-2)));
      break;
    }
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
