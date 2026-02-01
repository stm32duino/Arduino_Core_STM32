/**
  ******************************************************************************
  * @file    system_stm32wl3x.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex Device System Source File for STM32WL3x devices.
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

#ifndef SYSTEM_STM32WL3x_H
#define SYSTEM_STM32WL3x_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32WL3x_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup System Address
  * @{
  */

  /**
   * @brief RAM base address
   */
  #define _MEMORY_RAM_BEGIN_       0x20000000
  #define _MEMORY_RAM_SIZE_        0x8000           /* 32KB  */
  #define _MEMORY_RAM_END_         0x20007FFF

  /**
   * @brief User FLASH base address
   */
  #define _MEMORY_FLASH_BEGIN_     0x10040000
  #define _MEMORY_FLASH_SIZE_      0x40000          /* 256KB */
  #define _MEMORY_FLASH_END_       0x1007FFFF
  #define _MEMORY_BYTES_PER_PAGE_  (2048)

/**
 * @brief ROM base address
 */
#define _MEMORY_ROM_BEGIN_       0x10000000
#define _MEMORY_ROM_SIZE_        0x1800             /* 6KB */
#define _MEMORY_ROM_END_         0x1000017FF

/**
  * @}
  */


/** @addtogroup STM32WL3x_NVIC_IRQ_Priority
  * @{
  */
#define IRQ_CRITICAL_PRIORITY   0
#define IRQ_HIGH_PRIORITY       1
#define IRQ_MED_PRIORITY        2
#define IRQ_LOW_PRIORITY        3

/**
  * @}
  */

/** @addtogroup STM32WL3x_SMPS_CONFIG
  * @{
  */
/* SMPS BOM supported */
#define SMPS_BOM1 0 // SMPS Inductor 1.5uH
#define SMPS_BOM2 1 // SMPS Inductor 2.2uH
#define SMPS_BOM3 2 // SMPS Inductor 10uH

/* SMPS Configuration supported */
#define SMPS_ON          0
#define SMPS_OFF         1
#define SMPS_STATIC_BOF  2
#define SMPS_DYNAMIC_BOF 3

/* SMPS Configuration during power save */
#define SMPS_LOW_POWER_NO_OPEN 0
#define SMPS_LOW_POWER_OPEN    1

/**
  * @}
  */

/** @addtogroup Exported types
  * @{
  */
typedef void( *intfunc )( void );

typedef union { intfunc __fun; void * __ptr; } intvec_elem;

typedef struct RAM_VR_s
{
  uint32_t Reserve1;
  uint32_t SavedMSP;
  uint32_t WakeupFromSleepFlag;
  /**
   * ResetReason is the content of RCC_CSR after a reset.
   * RCC_CSR is automatically reset by internal bootloader.
   * See Reset Flags Defines RCC_LL_EC_GET_FLAG in stm32wl3x_ll_rcc.h
   */
  uint32_t ResetReason;
  uint32_t AppBase;
  uint32_t bootloader_vr;
  uint32_t bootloader_vr1;
  uint32_t Reserved2[4];
}RAM_VR_TypeDef;

/**
  * @}
  */

/** @addtogroup STM32WL3x_System_Exported_Variables
  * @{
  */
  /* The SystemCoreClock variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
   */
extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */

extern uint32_t HSE_xtalFrequency;   /*!< Crystal frequency */

extern RAM_VR_TypeDef RAM_VR;        /*!< Virtual Register map in RAM  */

extern const intvec_elem __vector_table[];

/**
  * @}
  */


/** @addtogroup STM32WL3x_System_Exported_Functions
  * @{
  */

/**
  * @brief Setup the microcontroller system.
  *
  * Initialize the System and update the SystemCoreClock variable.
  */
extern void SystemInit (void);


/**
  * @brief  Update SystemCoreClock variable.
  *
  * Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
  */
extern void SystemCoreClockUpdate (void);

/**
  * @brief CPU Content Restore.
  *
  * Function designed to restore CPU context at wakeup from Power Save.
  */
extern void CPUcontextRestore(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STM32WL3x_H */

/**
  * @}
  */

/**
  * @}
  */
