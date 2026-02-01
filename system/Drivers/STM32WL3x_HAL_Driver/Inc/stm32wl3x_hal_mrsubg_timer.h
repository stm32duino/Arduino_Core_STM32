/**
  ******************************************************************************
  * @file    stm32wl3x_hal_mrsubg_timer.h
  * @author  GPM WBL Application Team
  * @brief   MRSUBG Timer HAL module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WL3x_HAL_MRSUBG_TIMER_H
#define STM32WL3x_HAL_MRSUBG_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32wl3x_hal_def.h"
#include "stm32wl3x_ll_mrsubg_timer.h"
#include "stm32wl3x_hal_pwr.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @addtogroup MRSUBG_TIMER
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup MRSUBG_TIMER_Exported_Types MRSUBG Timer Exported Types
  * @{
  */

/**
  * @brief MRSUBG TIMER Init Structure definition
  */
typedef struct
{
  uint32_t HSE_XTAL_freq;                /*!< HSE XTAL frequency */
  uint16_t XTAL_StartupTime;             /*!< XTAL startup in us unit */
  BOOL enableInitialCalibration;         /*!< Enable initial estimation of the frequency of the
            * Low Speed Oscillator, otherwise it will be assumed
            * fixed at 32.768 kHz. */
  uint32_t periodicCalibrationInterval;  /*!< Periodic calibration interval in ms, to disable set to 0 */
} MRSUBG_TIMER_InitTypeDef;

/**
  * @brief  VIRTUAL TIMER Callback pointer definition
  */
typedef void (*VTIMER_CallbackType)(void *);

/**
  * @brief VIRTUAL TIMER handle Structure definition
  */
typedef struct VTIMER_HandleTypeS
{
  uint64_t expiryTime; /*!< Managed internally when the timer is started */
  VTIMER_CallbackType callback; /*!< Pointer to the user callback */
  BOOL active; /*!< Managed internally when the timer is started */
  struct VTIMER_HandleTypeS *next; /*!< Managed internally when the timer is started */
  void *userData; /*!< Pointer to user data */
} VTIMER_HandleType_t;

/**
  * @brief MRSUBG TIMER status enumeration definition
  */
typedef enum
{
  MRSUBG_TIMER_OFF = 0,
  MRSUBG_TIMER_PENDING = 1,
} MRSUBG_TIMER_Status;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup MRSUBG_TIMER_Exported_Constants MRSUBG Timer Exported Constants
  * @{
  */


/**
  * @brief MRSUBG TIMER Status
  */
#define WAKEUP_MRSUBG_TIMER_BUSY   (0x01U)

#define TIME_MAX_VALUE 255

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup MRSUBG_Timer_Exported_Functions MRSUBG Timer Exported Functions
  * @{
  */
void HAL_MRSUBG_TIMER_CPU_WKUP_Callback(void);
void HAL_MRSUBG_TIMER_CPU_WKUP_IRQHandler(void);

/** @defgroup MRSUBG_Timer_EF_Config MRSUBG Timer Init and Configuration functions
  * @{
  */

/**
  * @brief Initialize the MRSUBG timer module. It must be placed in the initialization
  *        section of the application.
  * @param MRSUBG_TIMER_InitStruct MRSUBG Timer Initialization parameters
  * @retval None
  */
void HAL_MRSUBG_TIMER_Init(MRSUBG_TIMER_InitTypeDef *MRSUBG_TIMER_InitStruct);

/**
  * @brief Timer module state machine. Check and schedule the calibration.
  * Check expired timers and execute user callback.
  * It must be placed inside the infinite loop.
  * @retval None
  */
void HAL_MRSUBG_TIMER_Tick(void);

/**
  * @}
  */

/** @defgroup MRSUBG_Timer_EF_Management MRSUBG Timer Management functions
  * @{
  */

/**
  * @brief  Return the status of the RFIP Wakeup timer and the last value programmed in the register.
  * @param  time: return the RFIP Wakeup time.
  * @retval 0 if no timer has been programmed.
  * @retval 1 if RFIP Wakeup Timer has been programmed.
  */
uint8_t HAL_MRSUBG_TIMER_GetRadioTimerValue(uint32_t *time);

/**
  * @brief  Returns the admitted low power mode according to the next timer activity.
  * @return Low Power mode
  */
PowerSaveLevels HAL_MRSUBG_TIMER_PowerSaveLevelCheck(void);

/**
  * @}
  */

/** @defgroup MRSUBG_Timer_EF_Management_TimeUnit MRSUBG Timer Management Time Unit
  * @{
  */

/**
  * @brief  Translates time in microseconds into machine time units.
  * @param  time: Microseconds to be converted in MTU
  * @return Machine time value
  */
uint64_t HAL_MRSUBG_TIMER_UsToMachinetime(uint64_t time);

/**
  * @brief  Translates time machine time in microseconds.
  * @param  time: Machine time to be converted in microseconds
  * @return Time value in microseconds
  */
uint64_t HAL_MRSUBG_TIMER_MachinetimeToUs(uint64_t time);

/**
  * @brief  This function returns the current reference time expressed in system time units.
  *         The returned value can be used as absolute time parameter where needed in the other
  *         HAL_MRSUBG_TIMER* APIs
  * @return absolute current time expressed in system time units.
  */
uint64_t HAL_MRSUBG_TIMER_GetCurrentSysTime(void);

/**
  * @}
  */

/** @defgroup MRSUBG_Timer_EF_Virtual_Timer MRSUBG Timer Virtual Timer functions
  * @{
  */

/**
  * @brief Starts a one-shot virtual timer for the given relative timeout value expressed in us
  * @param timerHandle: The virtual timer
  * @param usRelTimeout: The relative time, from current time, expressed in us
  * @retval 0 if the timerHandle is valid.
  * @retval 1 if the timerHandle is not valid. It is already started.
  */
uint32_t HAL_MRSUBG_TIMER_StartVirtualTimer(VTIMER_HandleType_t *timerHandle, uint64_t usRelTimeout);

/**
  * @brief Starts a one-shot virtual timer for the given relative timeout value expressed in ms
  * @param timerHandle: The virtual timer
  * @param msRelTimeout: The relative time, from current time, expressed in ms
  * @retval 0 if the timerHandle is valid.
  * @retval 1 if the timerHandle is not valid. It is already started.
  */
uint32_t HAL_MRSUBG_TIMER_StartVirtualTimerMs(VTIMER_HandleType_t *timerHandle, uint32_t msRelTimeout);

/**
  * @brief  Stops the one-shot virtual timer specified if found
  * @param  timerHandle: The virtual timer
  * @retval None
  */
void HAL_MRSUBG_TIMER_StopVirtualTimer(VTIMER_HandleType_t *timerHandle);

/**
  * @brief Returns the absolute expiry time of a running virtual timer expressed in internal system time units.
  * @param timerHandle: The virtual timer
  * @retval sysTime: Absolute time expressed in internal system time units.
  */
uint64_t HAL_MRSUBG_TIMER_ExpiryTime(VTIMER_HandleType_t *timerHandle);

/**
  * @brief  Virtual timer Timeout Callback. It signals that a host timeout occurred.
  * @retval None
  */
void HAL_MRSUBG_TIMER_TimeoutCallback(void);

/**
  * @brief  Returns the number of timers in the queue.
  * @return number of timers in the queue.
  */
uint32_t HAL_MRSUBG_TIMER_GetPendingTimers(void);

void HAL_MRSUBG_TIMER_MspInit(void);

void HAL_MRSUBG_TIMER_MspDeInit(void);

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

#endif /*STM32WL3x_HAL_MRSUBG_TIMER_H */
