/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Target/usbh_conf.h
  * @version        : v1.0_Cube
  * @brief          : Header for usbh_conf.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBH_CONF__H__
#define __USBH_CONF__H__
#ifdef __cplusplus
extern "C" {
#endif

// #define USBHOST

#ifdef USBHOST
/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "main.h"

// #include "stm32f4xx.h"
// #include "stm32f4xx_hal.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_HOST_LIBRARY
  * @{
  */

/** @defgroup USBH_CONF
  * @brief usb host low level driver configuration file
  * @{
  */

/** @defgroup USBH_CONF_Exported_Variables USBH_CONF_Exported_Variables
  * @brief Public variables.
  * @{
  */

/**
  * @}
  */

/** @defgroup USBH_CONF_Exported_Defines USBH_CONF_Exported_Defines
  * @brief Defines for configuration of the Usb host.
  * @{
  */

/*----------   -----------*/
#define USBH_MAX_NUM_ENDPOINTS      2U

/*----------   -----------*/
#define USBH_MAX_NUM_INTERFACES      2U

/*----------   -----------*/
#define USBH_MAX_NUM_CONFIGURATION      2U

/*----------   -----------*/
#define USBH_KEEP_CFG_DESCRIPTOR      2U

/*----------   -----------*/
#define USBH_MAX_NUM_SUPPORTED_CLASS      2U

/*----------   -----------*/
#define USBH_MAX_SIZE_CONFIGURATION      256U

/*----------   -----------*/
#define USBH_MAX_DATA_BUFFER      512U

/*----------   -----------*/
#define USBH_DEBUG_LEVEL      0U

/*----------   -----------*/
#define USBH_USE_OS      0U

/****************************************/
/* #define for FS and HS identification */
#define HOST_HS     0
#define HOST_FS     1

/* Interrupt priority */
#ifndef USBH_IRQ_PRIO
#define USBH_IRQ_PRIO                       0
#endif /* USBH_IRQ_PRIO */
#ifndef USBH_IRQ_SUBPRIO
#define USBH_IRQ_SUBPRIO                    0
#endif /* USBH_IRQ_SUBPRIO */

#if (USBH_USE_OS == 1)
#include "cmsis_os.h"
#define USBH_PROCESS_PRIO          osPriorityNormal
#define USBH_PROCESS_STACK_SIZE    ((uint16_t)0)
#endif /* (USBH_USE_OS == 1) */

/**
  * @}
  */

/** @defgroup USBH_CONF_Exported_Macros USBH_CONF_Exported_Macros
  * @brief Aliases.
  * @{
  */

/* Memory management macros */

/** Alias for memory allocation. */
#define USBH_malloc         malloc

/** Alias for memory release. */
#define USBH_free           free

/** Alias for memory set. */
#define USBH_memset         memset

/** Alias for memory copy. */
#define USBH_memcpy         memcpy

/* DEBUG macros */

#if (USBH_DEBUG_LEVEL > 0U)
#define  USBH_UsrLog(...)   do { \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBH_UsrLog(MSG, ...) do {} while (0)
#endif

#if (USBH_DEBUG_LEVEL > 1U)

#define  USBH_ErrLog(...) do { \
                            printf("ERROR: ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBH_ErrLog(MSG, ...) do {} while (0)
#endif

#if (USBH_DEBUG_LEVEL > 2U)
#define  USBH_DbgLog(...)   do { \
                            printf("DEBUG : ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBH_DbgLog(MSG, ...) do {} while (0)
#endif

/**
  * @}
  */

/** @defgroup USBH_CONF_Exported_Types USBH_CONF_Exported_Types
  * @brief Types.
  * @{
  */

/**
  * @}
  */

/** @defgroup USBH_CONF_Exported_FunctionsPrototype USBH_CONF_Exported_FunctionsPrototype
  * @brief Declaration of public functions for Usb host.
  * @{
  */

/* Exported functions -------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* USBHOST */

#ifdef __cplusplus
}
#endif

#endif /* __USBH_CONF__H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
