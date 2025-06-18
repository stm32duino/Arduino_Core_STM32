/**
  ******************************************************************************
  * @file    stm32wb0x_ll_utils.h
  * @author  MCD Application Team
  * @brief   Header file of UTILS LL module.
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
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL UTILS driver contains a set of generic APIs that can be
    used by user:
      (+) Device electronic signature
      (+) Timing functions
      (+) PLL configuration functions

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WB0x_LL_UTILS_H
#define STM32WB0x_LL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

/** @defgroup UTILS_LL UTILS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup UTILS_LL_Private_Constants UTILS Private Constants
  * @{
  */

/* Max delay can be used in LL_mDelay */
#define LL_MAX_DELAY                  0xFFFFFFFFU

/**
  * @brief Unique device ID register base address
  */
#define UID_BASE_ADDRESS              UID64_BASE

/**
  * @brief Flash size data register base address
  */
#define FLASHSIZE_BASE_ADDRESS        FLASHSIZE_BASE

/**
 * @brief RAM size data register base address
 */
#define RAMSIZE_BASE_ADDRESS        RAMSIZE_BASE

/**
  * @brief Package data register base address
  */
#define PACKAGE_BASE_ADDRESS          PACKAGE_BASE

/**
 * @brief Device ID data register base address
 */
#define DEV_ID_BASE_ADDRESS           DEV_ID_BASE

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup UTILS_LL_Private_Macros UTILS Private Macros
  * @{
  */
/**
  * @}
  */
/* Exported types ------------------------------------------------------------*/
/** @defgroup UTILS_LL_ES_INIT UTILS Exported structures
  * @{
  */

/**
  * @brief  UTILS System, AHB and APB buses clock configuration structure definition
  */
typedef struct
{/*Sys clock  divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_SYSCLK_DIV. */
  uint32_t dummy;
} LL_UTILS_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UTILS_LL_Exported_Constants UTILS Exported Constants
  * @{
  */

/** @defgroup UTILS_EC_HSE_BYPASS HSE Bypass activation
  * @{
  */
#define LL_UTILS_HSEBYPASS_OFF        0x00000000U       /*!< HSE Bypass is not enabled                */
#define LL_UTILS_HSEBYPASS_ON         0x00000001U       /*!< HSE Bypass is enabled                    */
/**
  * @}
  */

/** @defgroup UTILS_EC_PACKAGETYPE PACKAGE TYPE
  * @{
  */
#define LL_UTILS_PACKAGETYPE_QFN48          0x5F485F48U /*!< QFN48 package type                       */
#define LL_UTILS_PACKAGETYPE_QFN32          0x5F325F32U /*!< QFN32 package type                       */
#define LL_UTILS_PACKAGETYPE_CSP49          0xAC49AC49U /*!< CSP49 package type                       */

/**
  * @}
  */
/** @defgroup UTILS_EC_RAMSIZE RAM SIZE
  * @{
  */
#define LL_UTILS_RAMSIZE_24K          0x00000000U /*!< 24 kB of RAM available */
#define LL_UTILS_RAMSIZE_32K          0x00000001U /*!< 32 kB of RAM available */
#define LL_UTILS_RAMSIZE_48K          0x00000002U /*!< 48 kB of RAM available */
#define LL_UTILS_RAMSIZE_64K          0x00000003U /*!< 64 kB of RAM available */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup UTILS_LL_Exported_Functions UTILS Exported Functions
  * @{
  */

/** @defgroup UTILS_EF_DEVICE_ELECTRONIC_SIGNATURE DEVICE ELECTRONIC SIGNATURE
  * @{
  */
  /**
    * @brief  Get Word0 of the unique device identifier (UID based on 64 bits)
    * @retval Word0 of UID64
    */
__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)UID_BASE_ADDRESS)));
}

  /**
    * @brief  Get Word1 of the unique device identifier (UID based on 64 bits)
    * @retval Word1 of UID64
    */
__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 4U))));
}


  /**
    * @brief  Get Flash memory size
    * @note   This bitfield indicates the words number of the device Flash memory expressed.
    *         As an example, 0x7FFF corresponds to 128 Kbytes.
    * @retval FLASH_SIZE[15:0]: Flash memory size
    */
__STATIC_INLINE uint32_t LL_GetFlashSize(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)FLASHSIZE_BASE_ADDRESS)) & 0x0000FFFFUL);
}

  /**
    * @brief  Get RAM memory size
    * @retval Returned value can be one of the following values:
    * @arg LL_UTILS_RAMSIZE_24K
    * @arg LL_UTILS_RAMSIZE_32K
    * @arg LL_UTILS_RAMSIZE_48K
    * @arg LL_UTILS_RAMSIZE_64K
    */
  __STATIC_INLINE uint32_t LL_GetRAMSize(void)
  {
    __IOM uint32_t tmpreg;
#if defined(FLASH_FLASH_SIZE_RAM_SIZE)
    tmpreg = (READ_REG(*((uint32_t *)RAMSIZE_BASE_ADDRESS)) & FLASH_FLASH_SIZE_RAM_SIZE) >> FLASH_FLASH_SIZE_RAM_SIZE_Pos;

    if (tmpreg == 0) {
      tmpreg = LL_UTILS_RAMSIZE_32K;
    }
#else
    tmpreg = LL_UTILS_RAMSIZE_24K;
#endif

    return tmpreg;
  }


/**
    * @brief  Get Package type
    * @retval Returned value can be one of the following values:
    * @arg LL_UTILS_PACKAGETYPE_QFN48
    * @arg LL_UTILS_PACKAGETYPE_QFN32
    * @arg LL_UTILS_PACKAGETYPE_CSP49
  *
  */
__STATIC_INLINE uint32_t LL_GetPackageType(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)PACKAGE_BASE_ADDRESS)));
}

  /**
    * @brief  Get Device version and cut information
    * @retval DIE_ID register information
    */
  __STATIC_INLINE uint32_t LL_GetDIE_ID(void)
  {
    return (uint32_t)(READ_REG(*((uint32_t *)DEV_ID_BASE_ADDRESS)));
  }

/**
  * @}
  */

/** @defgroup UTILS_LL_EF_DELAY DELAY
  * @{
  */
/**
  * @brief  This function configures the Cortex-M SysTick source of the time base.
  * @param  HCLKFrequency SysClk frequency in Hz
  * @note   When a RTOS is used, it is recommended to avoid changing the SysTick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  Ticks Number of ticks
  * @retval None
  */

__STATIC_INLINE void LL_InitTick(uint32_t HCLKFrequency, uint32_t Ticks)
{
  /* Configure the SysTick to have interrupt in 1ms time base */
  SysTick->LOAD  = (uint32_t)((HCLKFrequency / Ticks) - 1UL);  /* set reload register */
  SysTick->VAL   = 0UL;                                       /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                   /* Enable the Systick Timer */
}

void        LL_Init1msTick(uint32_t HCLKFrequency);

void        LL_mDelay(uint32_t Delay);

/**
  * @}
  */

/** @defgroup UTILS_EF_SYSTEM SYSTEM
  * @{
  */

void LL_SetSystemCoreClock(uint32_t HCLKFrequency);
uint32_t LL_GetSystemCoreClock(void);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WB0x_LL_UTILS_H */
