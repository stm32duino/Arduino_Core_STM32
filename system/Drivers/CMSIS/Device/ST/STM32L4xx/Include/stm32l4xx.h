/**
  ******************************************************************************
  * @file    stm32l4xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32L4xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32L4xx device used in the target application
  *              - To use or not the peripheral�s drivers in application code(i.e.
  *                code will be based on direct access to peripheral�s registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l4xx
  * @{
  */

#ifndef __STM32L4xx_H
#define __STM32L4xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32L4)
#define STM32L4
#endif /* STM32L4 */

/* Uncomment the line below according to the target STM32L4 device used in your
   application
  */

#if !defined (STM32L412xx) && !defined (STM32L422xx) && \
    !defined (STM32L431xx) && !defined (STM32L432xx) && !defined (STM32L433xx) && !defined (STM32L442xx) && !defined (STM32L443xx) && \
    !defined (STM32L451xx) && !defined (STM32L452xx) && !defined (STM32L462xx) && \
    !defined (STM32L471xx) && !defined (STM32L475xx) && !defined (STM32L476xx) && !defined (STM32L485xx) && !defined (STM32L486xx) && \
    !defined (STM32L496xx) && !defined (STM32L4A6xx) && \
    !defined (STM32L4R5xx) && !defined (STM32L4R7xx) && !defined (STM32L4R9xx) && !defined (STM32L4S5xx) && !defined (STM32L4S7xx) && !defined (STM32L4S9xx)
  /* #define STM32L412xx */   /*!< STM32L412xx Devices */
  /* #define STM32L422xx */   /*!< STM32L422xx Devices */
  /* #define STM32L431xx */   /*!< STM32L431xx Devices */
  /* #define STM32L432xx */   /*!< STM32L432xx Devices */
  /* #define STM32L433xx */   /*!< STM32L433xx Devices */
  /* #define STM32L442xx */   /*!< STM32L442xx Devices */
  /* #define STM32L443xx */   /*!< STM32L443xx Devices */
  /* #define STM32L451xx */   /*!< STM32L451xx Devices */
  /* #define STM32L452xx */   /*!< STM32L452xx Devices */
  /* #define STM32L462xx */   /*!< STM32L462xx Devices */
  /* #define STM32L471xx */   /*!< STM32L471xx Devices */
  /* #define STM32L475xx */   /*!< STM32L475xx Devices */
  /* #define STM32L476xx */   /*!< STM32L476xx Devices */
  /* #define STM32L485xx */   /*!< STM32L485xx Devices */
  /* #define STM32L486xx */   /*!< STM32L486xx Devices */
  /* #define STM32L496xx */   /*!< STM32L496xx Devices */
  /* #define STM32L4A6xx */   /*!< STM32L4A6xx Devices */
  /* #define STM32L4R5xx */   /*!< STM32L4R5xx Devices */
  /* #define STM32L4R7xx */   /*!< STM32L4R7xx Devices */
  /* #define STM32L4R9xx */   /*!< STM32L4R9xx Devices */
  /* #define STM32L4S5xx */   /*!< STM32L4S5xx Devices */
  /* #define STM32L4S7xx */   /*!< STM32L4S7xx Devices */
  /* #define STM32L4S9xx */   /*!< STM32L4S9xx Devices */
#endif

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
#define __STM32L4_CMSIS_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32L4_CMSIS_VERSION_SUB1   (0x05) /*!< [23:16] sub1 version */
#define __STM32L4_CMSIS_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32L4_CMSIS_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32L4_CMSIS_VERSION        ((__STM32L4_CMSIS_VERSION_MAIN << 24)\
                                       |(__STM32L4_CMSIS_VERSION_SUB1 << 16)\
                                       |(__STM32L4_CMSIS_VERSION_SUB2 << 8 )\
                                       |(__STM32L4_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32L412xx)
  #include "stm32l412xx.h"
#elif defined(STM32L422xx)
  #include "stm32l422xx.h"
#elif defined(STM32L431xx)
  #include "stm32l431xx.h"
#elif defined(STM32L432xx)
  #include "stm32l432xx.h"
#elif defined(STM32L433xx)
  #include "stm32l433xx.h"
#elif defined(STM32L442xx)
  #include "stm32l442xx.h"
#elif defined(STM32L443xx)
  #include "stm32l443xx.h"
#elif defined(STM32L451xx)
  #include "stm32l451xx.h"
#elif defined(STM32L452xx)
  #include "stm32l452xx.h"
#elif defined(STM32L462xx)
  #include "stm32l462xx.h"
#elif defined(STM32L471xx)
  #include "stm32l471xx.h"
#elif defined(STM32L475xx)
  #include "stm32l475xx.h"
#elif defined(STM32L476xx)
  #include "stm32l476xx.h"
#elif defined(STM32L485xx)
  #include "stm32l485xx.h"
#elif defined(STM32L486xx)
  #include "stm32l486xx.h"
#elif defined(STM32L496xx)
  #include "stm32l496xx.h"
#elif defined(STM32L4A6xx)
  #include "stm32l4a6xx.h"
#elif defined(STM32L4R5xx)
  #include "stm32l4r5xx.h"
#elif defined(STM32L4R7xx)
  #include "stm32l4r7xx.h"
#elif defined(STM32L4R9xx)
  #include "stm32l4r9xx.h"
#elif defined(STM32L4S5xx)
  #include "stm32l4s5xx.h"
#elif defined(STM32L4S7xx)
  #include "stm32l4s7xx.h"
#elif defined(STM32L4S9xx)
  #include "stm32l4s9xx.h"
#else
 #error "Please select first the target STM32L4xx device used in your application (in stm32l4xx.h file)"
#endif

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
  ERROR = 0,
  SUCCESS = !ERROR
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))


/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32l4xx_hal.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32L4xx_H */
/**
  * @}
  */

/**
  * @}
  */




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
