/**
  ******************************************************************************
  * @file    stm32wb0x.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32WB0x Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32WB0x device used in the target application
  *              - To use or not the peripheral's drivers in application code(i.e.
  *                code will be based on direct access to peripheral's registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
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
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32wb0x
  * @{
  */

#ifndef __STM32WB0x_H
#define __STM32WB0x_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32WB0)
#define STM32WB0
#endif /* STM32WB0 */

/* Uncomment the line below according to the target STM32WB0 device used in your
   application
  */

#if !defined(STM32WB05) && !defined(STM32WB06) && !defined(STM32WB07) && !defined(STM32WB09)
  /* #define STM32WB05 */   /*!< STM32WB05 Devices */
  /* #define STM32WB06 */   /*!< STM32WB06 Devices */
  /* #define STM32WB07 */   /*!< STM32WB07 Devices */
  /* #define STM32WB09 */   /*!< STM32WB09 Devices */
#endif /* !STM32WB05 && !STM32WB06 && !STM32WB07 && !STM32WB09  */

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
  * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
/*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number
  */
#define __STM32WB0x_CMSIS_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32WB0x_CMSIS_VERSION_SUB1   (0x03U) /*!< [23:16] sub1 version */
#define __STM32WB0x_CMSIS_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32WB0x_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32WB0x_CMSIS_DEVICE_VERSION        ((__STM32WB0x_CMSIS_VERSION_MAIN << 24)\
                                                 |(__STM32WB0x_CMSIS_VERSION_SUB1 << 16)\
                                                 |(__STM32WB0x_CMSIS_VERSION_SUB2 << 8 )\
                                                 |(__STM32WB0x_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined( STM32WB05) || defined( STM32WB05x)

#include "stm32wb05.h" /* Header file supporting STM32WB05 */

#elif defined( STM32WB06) || defined( STM32WB06x)

#include "stm32wb06.h" /* Header file supporting STM32WB06 */

#elif defined( STM32WB07) || defined( STM32WB07x)

#include "stm32wb07.h" /* Header file supporting STM32WB07 */

#elif defined( STM32WB09) || defined( STM32WB09x)

#include "stm32wb09.h" /* Header file supporting STM32WB09 */

#else

#error "Please select first the target STM32WB0x device used in your application, for instance xx (in stm32wb0x.h file)"

#endif
#include "system_stm32wb0x.h"

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;

/** @brief Booelan definition */
typedef uint8_t BOOL;

#define TRUE  ((BOOL)1U)
#define FALSE ((BOOL)0U)

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define TOGGLE_BIT(REG, BIT)  ((REG) ^= (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define MODIFY_REG_FIELD(REG, FIELD_NAME, VAL)  MODIFY_REG(REG, FIELD_NAME##_Msk, ((VAL)<<(FIELD_NAME##_Pos))&\
                                                           (FIELD_NAME##_Msk))

/* Use of interrupt control for register exclusive access (privileged mode only) */
/* Atomic 32-bit register access macro to set one or several bits */
#define ATOMIC_SET_BIT(REG, BIT) \
  do {                           \
    uint32_t primask;            \
    primask = __get_PRIMASK();   \
    __set_PRIMASK(1);            \
    SET_BIT((REG), (BIT));       \
    __set_PRIMASK(primask);      \
  } while(0)

/* Atomic 32-bit register access macro to clear one or several bits */
#define ATOMIC_CLEAR_BIT(REG, BIT) \
  do {                             \
    uint32_t primask;              \
    primask = __get_PRIMASK();     \
    __set_PRIMASK(1);              \
    CLEAR_BIT((REG), (BIT));       \
    __set_PRIMASK(primask);        \
  } while(0)

/* Atomic 32-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK) \
  do {                                            \
    uint32_t primask;                             \
    primask = __get_PRIMASK();                    \
    __set_PRIMASK(1);                             \
    MODIFY_REG((REG), (CLEARMSK), (SETMASK));     \
    __set_PRIMASK(primask);                       \
  } while(0)

/* Atomic 16-bit register access macro to set one or several bits */
#define ATOMIC_SETH_BIT(REG, BIT)   ATOMIC_SET_BIT(REG, BIT)

/* Atomic 16-bit register access macro to clear one or several bits */
#define ATOMIC_CLEARH_BIT(REG, BIT) ATOMIC_CLEAR_BIT(REG, BIT)

/* Atomic 16-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFYH_REG(REG, CLEARMSK, SETMASK) ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK)

/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
#include "stm32wb0x_hal.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32WB0x_H */
/**
  * @}
  */

/**
  * @}
  */
