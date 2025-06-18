/**
  ******************************************************************************
  * @file    stm32wb0x_hal_radio_timer.h
  * @author  GPM WBL Application Team
  * @brief   Radio Timer HAL module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WB0x_HAL_RADIO_TIMER_H
#define STM32WB0x_HAL_RADIO_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "stm32wb0x_hal_def.h"
#include "stm32wb0x_ll_radio_timer.h"
#include "stm32wb0x_hal_pwr.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @addtogroup RADIO_TIMER
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RADIO_TIMER_Exported_Types Radio Timer Exported Types
  * @{
  */

/**
  * @brief RADIO TIMER Init Structure definition
  */
typedef struct
{
  uint16_t XTAL_StartupTime;             /*!< XTAL startup in 2.44 us unit */
  bool enableInitialCalibration;         /*!< Enable initial estimation of the frequency of the
            * Low Speed Oscillator, otherwise it will be assumed
            * fixed at 32.768 kHz.
            * Ignored if periodic calibration is active
            * (PeriodicCalibrationInterval != 0). */
  uint32_t periodicCalibrationInterval;  /*!< Periodic calibration interval in ms, to disable set to 0 */
} RADIO_TIMER_InitTypeDef;

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
  bool active; /*!< Managed internally when the timer is started */
  struct VTIMER_HandleTypeS *next; /*!< Managed internally when the timer is started */
  void *userData; /*!< Pointer to user data */
} VTIMER_HandleType;

/**
  * @brief RADIO TIMER status enumeration definition
  */
typedef enum
{
  RADIO_TIMER_OFF = 0,
  RADIO_TIMER_PENDING = 1,
} RADIO_TIMER_Status;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RADIO_TIMER_Exported_Constants Radio Timer Exported Constants
  * @{
  */

/**
  * @brief RADIO TIMER clearing process return values
  */
#define HAL_RADIO_TIMER_SUCCESS  (0x00U)
#define HAL_RADIO_TIMER_LATE     (0x01U)
#define HAL_RADIO_TIMER_CRITICAL (0x02U)
/**
  * @}
  */

/**
  * @brief RADIO TIMER Status
  */
#define RADIO_TIMER1_BUSY         (0x01U)
#define RADIO_TIMER2_BUSY         (0x02U)
#define WAKEUP_RADIO_TIMER_BUSY   (0x03U)
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RADIO_TIMER_Exported_Functions Radio Timer Exported Functions
  * @{
  */

/** @defgroup RADIO_TIMER_EF_Config Radio Timer Init and Configuration functions
  * @{
  */

/**
  * @brief Initialize the radio timer module. It must be placed in the initialization
  *        section of the application.
  * @param RADIO_TIMER_InitStruct Radio Timer Initialization parameters
  * @retval None
  */
void HAL_RADIO_TIMER_Init(RADIO_TIMER_InitTypeDef *RADIO_TIMER_InitStruct);

/**
  * @brief Timer module state machine. Check and schedule the calibration.
  * Check expired timers and execute user callback.
  * It must be placed inside the infinite loop.
  * @retval None
  */
void HAL_RADIO_TIMER_Tick(void);

/**
  * @brief  Return the status of the radio timer.
  *         The timeout of the last radio timer activity taken into account by the Timer Module
  *         is saved in the variable passed as parameter.
  * @param  time: Pointer of the variable where the time of the last radio activity scheduled is stored
  *               The time is expressed in STU.
  * @retval 0 if no radio timer is pending.
  * @retval 1 if a radio timer is pending.
  */
RADIO_TIMER_Status HAL_RADIO_TIMER_GetRadioTimerStatus(uint64_t *time);

/**
  * @}
  */

/** @defgroup RADIO_TIMER_EF_Management Radio Timer Management functions
  * @{
  */

/**
  * @brief  Schedules a radio activity for the given absolute timeout value expressed in STU.
  *         If the calibration of the low speed oscillator is needed, if it is possible,
  *         the radio timer will be programmed with the latest calibration data.
  * @param  time: Absolute time expressed in STU.
  * @param  event_type: Specify if it is a TX (1) or RX (0) event.
  * @param  cal_req: Specify if PLL calibration is requested (1) or not (0).
  * @retval 0 if radio activity has been scheduled successfully.
  * @retval 1 if radio activity has been rejected (it is too close or in the past).
  */
uint32_t HAL_RADIO_TIMER_SetRadioTimerValue(uint32_t time, uint8_t event_type, uint8_t cal_req);

/**
  * @brief  Clear the last radio activity scheduled disabling the radio timers too.
  *         Furthermore, it returns if the timeout is too close with respect the current time and
  *         the radio activity might not be cleared in time.
  * @retval 0 if the radio activity has been cleared successfully.
  * @retval 1 if it is too late to clear the last radio activity.
  * @retval 2 if it might not be possible to clear the last radio activity.
  */
uint32_t HAL_RADIO_TIMER_ClearRadioTimerValue(void);

/**
  * @brief   Programs Timer1 with a relative timeout - expressed in us - wrt the previous radio event.
  * @param   rel_timeout_us: relative delay, in us, wrt the previous radio event.
  * @param   event_type: 1 Tx event.
                         0 Rx event
  * @param   cal_req: 1 PLL calibartion is requested.
                      0 PLL calibartion is not requested.
  * @warning This function should be called with interrupts disabled
  *           to avoid programming the timer with a value in the past
  * @retval  0 if a correct timeout has been programmed in the timeout register
  * @retval  1 if a correct timeout cannot be programmed
  */
uint32_t HAL_RADIO_TIMER_SetRadioTimerRelativeUsValue(uint32_t rel_timeout_us, bool event_type, bool cal_req);

/**
  * @brief  Return the status of the Radio timers and the last value programmed in the register.
  * @note   When Timer2 is on schedule, the time is expressed in microseconds, otherwise in absolute machine time units.
  * @param  time: pointer to value which is going to have time value.
  * @retval 0 if no timer has been programmed.
  * @retval 1 if Timer1 has been programmed.
  * @retval 2 if Timer2 has been programmed.
  * @retval 3 if Wakeup Timer has been programmed.
  */
uint8_t HAL_RADIO_TIMER_GetRadioTimerValue(uint32_t *time);

/**
  * @brief Program the radio timer (a.k.a Timer1) as close as possible.
  *        The current time is sampled and increased by two.
  *        It means that the timer is going to trigger in a timer interval that goes
  *        from one to two machine time units.
  */
void HAL_RADIO_TIMER_SetRadioCloseTimeout(void);

/**
  * @brief  Radio activity finished.
  * @retval None
  */
void HAL_RADIO_TIMER_RadioTimerIsr(void);

/**
  * @brief  Timer State machine semaphore to signal the radio activity finished.
  * @retval None
  */
void HAL_RADIO_TIMER_EndOfRadioActivityIsr(void);

/**
  * @brief  Get the last anchorPoint in system time unit.
  * @return TimerCapture register in system time unit.
  */
uint64_t HAL_RADIO_TIMER_GetAnchorPoint(uint64_t *current_system_time);

/**
  * @brief  Returns the admitted low power mode according to the next timer activity.
  * @return Low Power mode
  */
PowerSaveLevels HAL_RADIO_TIMER_PowerSaveLevelCheck(void);

/**
  * @}
  */

/** @defgroup RADIO_TIMER_EF_Management_TimeUnit Radio Timer Management Time Unit
  * @{
  */

/**
  * @brief  Translate time in microseconds into sys time units.
  * @param  time: Microseconds to be converted in STU
  * @return STU value
  */
uint32_t HAL_RADIO_TIMER_UsToSystime(uint32_t time);

/**
  * @brief   Return the STU corresponding to the MTU passed as parameter.
  * @param   time: MTU amount to be converted in STU
  * @warning This function is not re-entrant since it updates the context variable
  *          storing the system time. It should be called only in
  *          user context and not in interrupt context.
  * @return  STU value
  */
uint32_t HAL_RADIO_TIMER_MachineTimeToSysTime(uint32_t time);

/**
  * @brief  This function returns the current reference time expressed in system time units.
  *         The returned value can be used as absolute time parameter where needed in the other
  *         HAL_RADIO_TIMER* APIs
  * @return absolute current time expressed in system time units.
  */
uint64_t HAL_RADIO_TIMER_GetCurrentSysTime(void);

/**
  * @brief This function returns the sum of an absolute time and a signed relative time.
  * @param  sysTime: Absolute time expressed in internal time units.
  * @param  msTime: Signed relative time expressed in ms.
  * @return 64bit resulting absolute time expressed in internal time units.
  */
uint64_t HAL_RADIO_TIMER_AddSysTimeMs(uint64_t sysTime, int32_t msTime);

/**
  * @brief  Returns the difference between two absolute times: sysTime1-sysTime2.
  * The resulting value is expressed in ms.
  * @param  sysTime2: Absolute time expressed in internal time units.
  * @param  sysTime1: Absolute time expressed in internal time units.
  * @return resulting signed relative time expressed in ms.
  */
int64_t HAL_RADIO_TIMER_DiffSysTimeMs(uint64_t sysTime1, uint64_t sysTime2);

/**
  * @brief   Returns the 64-bit system time, referred to the 32-bit system time parameter.
  *          The returned system time refers to a time between last calibration and last
  *          calibration + 10485 seconds.
  * @param   sys_time: system time
  * @warning The system time cannot be more then 10485 seconds (174 min) after the last calibration time.
  * @return  STU value
  */
uint64_t HAL_RADIO_TIMER_GetSysTime64(uint32_t sys_time);

/**
  * @brief   Returns the next 64-bit system time in the future, referred to the 32-bit system time parameter.
  *          Compared to HAL_RADIO_TIMER_GetSysTime64() this function makes sure that the returned
  *          time is always in the future, but execution time of the function is longer.
  * @param   sys_time: system time in the future (no more than 10485 s = 174 min in the future)
  * @return  STU value
  */
uint64_t HAL_RADIO_TIMER_GetFutureSysTime64(uint32_t sys_time);

/**
  * @}
  */

/** @defgroup RADIO_TIMER_EF_Virtual_Timer Radio Timer Virtual Timer functions
  * @{
  */

/**
  * @brief Starts a one-shot virtual timer for the given relative timeout value expressed in ms
  * @param timerHandle: The virtual timer
  * @param msRelTimeout: The relative time, from current time, expressed in ms
  * @retval 0 if the timerHandle is valid.
  * @retval 1 if the timerHandle is not valid. It is already started.
  */
uint32_t HAL_RADIO_TIMER_StartVirtualTimer(VTIMER_HandleType *timerHandle, uint32_t msRelTimeout);

/**
  * @brief Starts a one-shot virtual timer for the given absolute timeout value
  *        expressed in internal system time units.
  * @param timerHandle: The virtual timer
  * @param time: Absolute time expressed in STU.
  * @retval 0 if the timerHandle is valid.
  * @retval 1 if the timerHandle is not valid. It is already started.
  */
uint32_t HAL_RADIO_TIMER_StartVirtualTimerSysTime(VTIMER_HandleType *timerHandle, uint64_t time);

/**
  * @brief  Stops the one-shot virtual timer specified if found
  * @param  timerHandle: The virtual timer
  * @retval None
  */
void HAL_RADIO_TIMER_StopVirtualTimer(VTIMER_HandleType *timerHandle);

/**
  * @brief Returns the absolute expiry time of a running virtual timer expressed in internal system time units.
  * @param timerHandle: The virtual timer
  * @retval sysTime: Absolute time expressed in internal system time units.
  */
uint64_t HAL_RADIO_TIMER_ExpiryTime(VTIMER_HandleType *timerHandle);

/**
  * @brief  Virtual timer Timeout Callback. It signals that a host timeout occurred.
  * @retval None
  */
void HAL_RADIO_TIMER_TimeoutCallback(void);

#if defined (STM32WB06) || defined (STM32WB07)
/**
  * @brief   If the wakeup timer triggers for a host wakeup, a pending radio activity is programmed.
  *          If the wakeup timer triggers for a radio activity, a pending virtual timer callback is executed.
  * @retval  None
  */
void HAL_RADIO_TIMER_WakeUpCallback(void);
#endif /* (STM32WB06) || defined (STM32WB07) */

/**
  * @brief  Returns the number of timers in the queue.
  * @return number of timers in the queue.
  */
uint32_t HAL_RADIO_TIMER_GetPendingTimers(void);


void HAL_RADIO_TIMER_CPU_WKUP_IRQHandler(void);
void HAL_RADIO_TIMER_TXRX_WKUP_IRQHandler(void);
void HAL_RADIO_TIMER_ERROR_IRQHandler(void);

void HAL_RADIO_TIMER_CpuWakeUpCallback(void);
void HAL_RADIO_TIMER_TxRxWakeUpCallback(void);

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

#endif /*STM32WB0x_HAL_RADIO_TIMER_H */
