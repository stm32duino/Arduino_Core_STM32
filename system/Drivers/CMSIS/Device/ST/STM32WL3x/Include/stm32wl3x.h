/**
  ******************************************************************************
  * @file    stm32wl3x.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32WL3x Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32WBxx device used in the target application
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

/** @addtogroup stm32wl3x
  * @{
  */

#ifndef STM32WL3x_H
#define STM32WL3x_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined(STM32WL3)
#define STM32WL3
#endif /* STM32WL3 */

/** Uncomment the line below according to the target STM32WL3 device used in your application.
  * stm32wl3xx.h file contains:
  * - All the peripheral register's definitions, bits definitions and memory mapping for STM32WL3xx devices
  * - IRQ channel definition
  * - Peripheral memory mapping and physical registers address definition
  * - Peripheral pointer declaration and driver header file inclusion
  * - Product miscellaneous configuration: assert macros, …
  * Note: These CMSIS drivers (stm32wl3xx.h) are always supporting features of the sub-family's superset.
  */
#if !defined(STM32WL3XX) && !defined(STM32WL3RX)
  /* #define STM32WL3XX */   /*!< STM32WL30x, STM32WL31x and STM32WL33x Devices */
  /* #define STM32WL3RX */   /*!< STM32WL3RX Devices */
#endif /* STM32WL3XX */

/* Legacy aliases */
#if defined(STM32WL33)
 #define STM32WL3XX
#endif /* STM32WL33 */


/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined(USE_HAL_DRIVER)
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
#define __STM32WL3x_CMSIS_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32WL3x_CMSIS_VERSION_SUB1   (0x03U) /*!< [23:16] sub1 version */
#define __STM32WL3x_CMSIS_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32WL3x_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32WL3x_CMSIS_VERSION       ((__STM32WL3x_CMSIS_VERSION_MAIN << 24U)\
                                       |(__STM32WL3x_CMSIS_VERSION_SUB1 << 16U)\
                                       |(__STM32WL3x_CMSIS_VERSION_SUB2 << 8U )\
                                       |(__STM32WL3x_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32WL3XX)
  #include "stm32wl3xx.h"
#elif defined(STM32WL3R) || defined(STM32WL3RX)
#include "stm32wl3rx.h"
#else
 #error "Please select first the target STM32WL3xx device used in your application (in stm32wl3x.h file)"
#endif /* STM32WL3XX */

/**
  * @}
  */

/** @addtogroup Exported types
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

typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;

typedef uint8_t BOOL;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */

/**@brief Macro that checks if STATE is a FlagStatus / ITStatus */
#define IS_FLAGSTATUS(STATE) (((STATE) == RESET) || ((STATE) == SET))
#define IS_ITSTATUS(STATE)   IS_FLAGSTATUS(STATE)

/** @brief Macro that checks if STATE is a FunctionalState */
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/** @brief Macro that returns a 16-bit value from a buffer where the value is stored in Little Endian Format */
#define LE_TO_HOST_16(ptr)   (uint16_t) ( ((uint16_t)*((uint8_t *)(ptr))) | \
                                          ((uint16_t)*((uint8_t *)(ptr) + 1) << 8) )

/** @brief Macro that returns a 16-bit value from a buffer where the value is stored in Big Endian Format */
#define BE_TO_HOST_16(ptr)  (uint16_t) ( ((uint16_t) *((uint8_t *)ptr)) << 8 | \
                                         ((uint16_t) *((uint8_t *)ptr + 1) ) )

/** @brief Macro that stores a 16-bit value into a buffer in Little Endian Format (2 bytes) */
#define HOST_TO_LE_16(buf, val)    ( ((buf)[0] =  (uint8_t) (val)    ) , \
                                   ((buf)[1] =  (uint8_t) ((val)>>8) ) )

/** @brief Macro that returns a 32-bit value from a buffer where the value is stored in Little Endian Format */
#define LE_TO_HOST_32(ptr)   (uint32_t) ( ((uint32_t)*((uint8_t *)(ptr))) | \
                                           ((uint32_t)*((uint8_t *)(ptr) + 1) << 8)  | \
                                           ((uint32_t)*((uint8_t *)(ptr) + 2) << 16) | \
                                           ((uint32_t)*((uint8_t *)(ptr) + 3) << 24) )

/** @brief Macro that returns a 16-bit value from a buffer where the value is stored in Big Endian Format */
#define BE_TO_HOST_32(ptr)  (uint32_t) ( ((uint32_t) *((uint8_t *)ptr    )) << 24 | \
                                         ((uint32_t) *((uint8_t *)ptr + 1)) << 16 | \
                                         ((uint32_t) *((uint8_t *)ptr + 2)) << 8 | \
                                         ((uint32_t) *((uint8_t *)ptr + 3)) )

/** @brief Macro that stores a 32-bit value into a buffer in Little Endian Format (4 bytes) */
#define HOST_TO_LE_32(buf, val)    ( ((buf)[0] =  (uint8_t) (val)     ) , \
                                   ((buf)[1] =  (uint8_t) ((val)>>8)  ) , \
                                   ((buf)[2] =  (uint8_t) ((val)>>16) ) , \
                                   ((buf)[3] =  (uint8_t) ((val)>>24) ) )

/** @brief Macro that returns a 64-bit value from a buffer where the value is stored in Little Endian Format */
#define LE_TO_HOST_64(ptr)   (uint64_t) ( ((uint64_t)*((uint8_t *)(ptr))) | \
                                          ((uint64_t)*((uint8_t *)(ptr) + 1) << 8)  | \
                                          ((uint64_t)*((uint8_t *)(ptr) + 2) << 16) | \
                                          ((uint64_t)*((uint8_t *)(ptr) + 3) << 24) | \
                                          ((uint64_t)*((uint8_t *)(ptr) + 4) << 32) | \
                                          ((uint64_t)*((uint8_t *)(ptr) + 5) << 40) | \
                                          ((uint64_t)*((uint8_t *)(ptr) + 6) << 48) | \
                                          ((uint64_t)*((uint8_t *)(ptr) + 7) << 56) )

/** @brief Macro that stores a 64-bit value into a buffer in Little Endian Format (8 bytes) */
#define HOST_TO_LE_64(buf, val)    ( ((buf)[0] =  (uint8_t) (val)       ) , \
                                     ((buf)[1] =  (uint8_t) ((val)>>8)  ) , \
                                     ((buf)[2] =  (uint8_t) ((val)>>16) ) , \
                                     ((buf)[3] =  (uint8_t) ((val)>>24) ) , \
                                     ((buf)[4] =  (uint8_t) ((val)>>32) ) , \
                                     ((buf)[5] =  (uint8_t) ((val)>>40) ) , \
                                     ((buf)[6] =  (uint8_t) ((val)>>48) ) , \
                                     ((buf)[7] =  (uint8_t) ((val)>>56) ) )

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         (REG)

#define TOGGLE_BIT(REG, BIT)  ((REG) ^= (BIT))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), ((READ_REG(REG) & (~(CLEARMASK))) | (SETMASK)))

#define MODIFY_REG_FIELD(REG, FIELD_NAME, VAL)  MODIFY_REG(REG, FIELD_NAME##_Msk, ((VAL)<<(FIELD_NAME##_Pos))&(FIELD_NAME##_Msk))

#define READ_REG_FIELD(REG, FIELD)	((REG & FIELD)>>FIELD##_Pos)

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

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

/**@brief TRUE, FALSE definition */
#ifndef TRUE
#define TRUE  ((BOOL)1U)
#endif
#ifndef FALSE
#define FALSE ((BOOL)0U)
#endif

#if defined(USE_HAL_DRIVER)
 #include "stm32wl3x_hal.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32WL3x_H */
/**
  * @}
  */

/**
  * @}
  */
