/**
  ******************************************************************************
  * @file    stm32c0xx_ll_utils.h
  * @author  MCD Application Team
  * @brief   Header file of UTILS LL module.
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
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL UTILS driver contains a set of generic APIs that can be
    used by user:
      (+) Device electronic signature
      (+) Timing functions

  @endverbatim
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32C0xx_LL_UTILS_H
#define STM32C0xx_LL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx.h"

/** @addtogroup STM32C0xx_LL_Driver
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
#define UID_BASE_ADDRESS              UID_BASE

/**
  * @brief Flash size data register base address
  */
#define FLASHSIZE_BASE_ADDRESS        FLASHSIZE_BASE

/**
  * @brief Package data register base address
  */
#define PACKAGE_BASE_ADDRESS          PACKAGE_BASE

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
/* Exported constants --------------------------------------------------------*/
/** @defgroup UTILS_LL_Exported_Constants UTILS Exported Constants
  * @{
  */

/** @defgroup UTILS_EC_PACKAGETYPE PACKAGE TYPE
  * @{
  */
#if defined(STM32C011xx)
#define LL_UTILS_PACKAGETYPE_SO8           0x0001U /*!< SO8 package type      */
#define LL_UTILS_PACKAGETYPE_WLCSP12       0x0002U /*!< WLCSP12 package type  */
#define LL_UTILS_PACKAGETYPE_UFQFPN20      0x0003U /*!< UFQFPN20 package type */
#define LL_UTILS_PACKAGETYPE_TSSOP20       0x0004U /*!< TSSOP20 package type  */
#elif defined(STM32C031xx)
#define LL_UTILS_PACKAGETYPE_TSSOP20        0x0002U /*!< TSSOP20 package type             */
#define LL_UTILS_PACKAGETYPE_UFQFPN28       0x0003U /*!< UFQFPN28 package type            */
#define LL_UTILS_PACKAGETYPE_QFN32          0x0004U /*!< UFQFPN32 / LQFP32  package type  */
#define LL_UTILS_PACKAGETYPE_QFN48          0x0005U /*!< UFQFPN48 / LQFP48  package type  */
#elif defined(STM32C071xx)
#define LL_UTILS_PACKAGETYPE_WLCSP19_GP     0x0001U /*!< WLCSP19 (GP) package type                           */
#define LL_UTILS_PACKAGETYPE_WLCSP19_N      0x0002U /*!< WLCSP19 (N) package type                            */
#define LL_UTILS_PACKAGETYPE_TSSOP20_GP     0x0003U /*!< TSSOP20 (GP) package type                           */
#define LL_UTILS_PACKAGETYPE_TSSOP20_N      0x0004U /*!< TSSOP20 (N) package type                            */
#define LL_UTILS_PACKAGETYPE_UFQFPN28_GP    0x0005U /*!< UFQFPN28 (GP) package type                          */
#define LL_UTILS_PACKAGETYPE_UFQFPN28_N     0x0006U /*!< UFQFPN28 (GP) package type                          */
#define LL_UTILS_PACKAGETYPE_QFN32_GP       0x0007U /*!< UFQFPN32 / LQFP32 general purpose (GP) package type */
#define LL_UTILS_PACKAGETYPE_QFN32_N        0x0008U /*!< UFQFPN32 / LQFP32 general purpose (N) package type  */
#define LL_UTILS_PACKAGETYPE_QFN48_GP       0x0009U /*!< UFQFPN48 / LQFP48 general purpose (GP) package type */
#define LL_UTILS_PACKAGETYPE_QFN48_N        0x000AU /*!< UFQFPN32 / LQFP48 general purpose (N) package type  */
#define LL_UTILS_PACKAGETYPE_LQFP64_GP      0x000BU /*!< UFQFPN64 / LQFP64 general purpose (GP) package type */
#define LL_UTILS_PACKAGETYPE_LQFP64_N       0x0008U /*!< UFQFPN64 / LQFP64 general purpose (N) package type  */
#define LL_UTILS_PACKAGETYPE_UFBGA64_GP     0x000DU /*!< UFBGA64 (GP) package type                           */
#define LL_UTILS_PACKAGETYPE_UFBGA64_N      0x000EU /*!< UFBGA64 (N) package type                            */
#elif defined(STM32C051xx)
#define LL_UTILS_PACKAGETYPE_WLCSP15        0x0001U /*!< WLCSP15 package type           */
#define LL_UTILS_PACKAGETYPE_TSSOP20        0x0002U /*!< TSSOP20 package type           */
#define LL_UTILS_PACKAGETYPE_UFQFPN28       0x0003U /*!< UFQFPN28 package type          */
#define LL_UTILS_PACKAGETYPE_QFN32          0x0004U /*!< UFQFPN32 / LQFP32 package type */
#define LL_UTILS_PACKAGETYPE_QFN48          0x0005U /*!< UFQFPN48 / LQFP48 package type */
#elif defined(STM32C091xx) || defined(STM32C092xx)
#define LL_UTILS_PACKAGETYPE_TSSOP20        0x0001U /*!< TSSOP20 package type           */
#define LL_UTILS_PACKAGETYPE_WLCSP24        0x0002U /*!< WLCSP24 package type           */
#define LL_UTILS_PACKAGETYPE_UFQFPN28       0x0003U /*!< UFQFPN28 package type          */
#define LL_UTILS_PACKAGETYPE_QFN32          0x0004U /*!< UFQFPN32 / LQFP32 package type */
#define LL_UTILS_PACKAGETYPE_QFN48          0x0005U /*!< UFQFPN48 / LQFP48 package type */
#define LL_UTILS_PACKAGETYPE_QFN64          0x0006U /*!< UFQFPN64 / LQFP64 package type */
#endif /* STM32C0xx */
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
  * @brief  Get Word0 of the unique device identifier (UID based on 96 bits)
  * @retval UID[31:0]: X and Y coordinates on the wafer expressed in BCD format
  */
__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)UID_BASE_ADDRESS)));
}

/**
  * @brief  Get Word1 of the unique device identifier (UID based on 96 bits)
  * @retval UID[63:32]: Wafer number (UID[39:32]) & LOT_NUM[23:0] (UID[63:40])
  */
__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 4U))));
}

/**
  * @brief  Get Word2 of the unique device identifier (UID based on 96 bits)
  * @retval UID[95:64]: Lot number (ASCII encoded) - LOT_NUM[55:24]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word2(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 8U))));
}

/**
  * @brief  Get Flash memory size
  * @note   This bitfield indicates the size of the device Flash memory expressed in
  *         Kbytes. As an example, 0x040 corresponds to 64 Kbytes.
  * @retval FLASH_SIZE[15:0]: Flash memory size
  */
__STATIC_INLINE uint32_t LL_GetFlashSize(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)FLASHSIZE_BASE_ADDRESS)) & 0x0000FFFFUL);
}

/**
  * @brief  Get Package type
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_UTILS_PACKAGETYPE_SO8 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_WLCSP12 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN20 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_TSSOP20 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN28 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_QFN32 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_QFN48 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_WLCSP19 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_WLCSP15 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_WLCSP24 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFBGA64 (*)
  *         @arg @ref LL_UTILS_PACKAGETYPE_LQFP64 (*)
  *
  * @note  (*) Availability depends on devices.
  *
  */
__STATIC_INLINE uint32_t LL_GetPackageType(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)PACKAGE_BASE_ADDRESS)) & 0xFU);
}

/**
  * @}
  */

/** @defgroup UTILS_LL_EF_DELAY DELAY
  * @{
  */

/**
  * @brief  This function configures the Cortex-M SysTick source of the time base.
  * @param  HCLKFrequency HCLK frequency in Hz (can be calculated thanks to RCC helper macro)
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
void        LL_SetSystemCoreClock(uint32_t HCLKFrequency);
ErrorStatus LL_SetFlashLatency(uint32_t HCLK_Frequency);
/* alias for backward compatibility */
#define UTILS_SetFlashLatency LL_SetFlashLatency

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

#endif /* STM32C0xx_LL_UTILS_H */
