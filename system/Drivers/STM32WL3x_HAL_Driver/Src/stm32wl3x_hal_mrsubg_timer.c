/**
******************************************************************************
* @file    stm32wl3x_hal_mrsubg_timer.c
* @author  GPM WBL Application Team
* @brief   Virtual timer and MRSUBG timer high level APIs
* @details This file implements the software layer that provides the virtualization of the
* resources of a single hardware radio timer in order to allocate many user virtual timers.
* The only constraint to the number of virtual timers is the memory.
* Each instance of a virtual timer is placed in an queue ordered by the expiration time
* and it can be linked to a callback.
* The timer tick is in charge to execute the callback linked to each virtual timer
* and to update the hardware timeout to guarantee the expiration of the next virtual
* timer in the queue.
* A special virtual timer called calibration/anti-wrapping timer is automatically armed
* by the software. This timer can address two tasks:
* - it is in charge to maintain the never wrapping virtual time base.
* - if the slow clock calibration is enabled, it starts the calibration procedure at each
* calibration interval specified during the initialization.
*
* A timer is intended as an event programmed in the future at a certain absolute expiration time
* on a time base. In this implementation the time base grows on 64 bits. Then, it never wraps.
* However, due to hardware timer finite length and in order to maintain the timing coherency, the time base
* must be maintained at least one time before the hardware timer wraps.
* Then even if the slow clock calibration is disabled, the calibration/anti-wrapping timer
* is always active with the only role to maintain the time base and it will expire
* at a rate that depends on the hardware timer capability.
* The time base unit is a STU that is the unit exposed to the user and it is equal to 1 us.
* The calibration/anti-wrapping mechanism is not managed by the user.
*
* This software layer also exposes the possibility to read if a radio timer is programmed.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @defgroup MRSUBG_TIMER MRSUBG TIMER
  * @{
  */

#ifdef HAL_MRSUBG_TIMER_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/

/** @defgroup MRSUBG_TIMER_Private_Types MRSUBG TIMER Private Types
  * @{
  */

typedef struct {
  VTIMER_HandleType calibrationTimer;
  VTIMER_HandleType *rootNode; /*!< First timer of the host timer queue */
  uint8_t enableTimeBase;      /*!< Internal flag. User can ignore it*/
  uint8_t expired_count; /*!< Progressive number to indicate expired timers */
  uint8_t served_count; /*!< Progressive number to indicate served expired timers */
  uint8_t stop_notimer_action; /*!< Flag to indicate DEEPSTOP no timer action */
  uint64_t cumulative_time; /** Absolute system time since power up */
  uint32_t hs_startup_time; /** HS startup time in us */
  uint32_t last_scm_counter; /** Number of 16Mhz fast clock cycles seen in a 32 slow clock period window read in the last calibration*/
  uint32_t fast_clock_freq; /** The fast clock frequency is XO frequency / 3 so typically 16MHz. But it can also be 15.666MHz with a XO at 47MHz or 16.666MHz with a XO at 50MHz. */
  uint32_t slow_clock_freq; /** Slow clock freq */
  uint32_t interpolated_freq; /** Interpolated frequency */
  uint32_t last_interpolated_freq; /** Last interpolated frequency */
  uint64_t timer_max_value; /** TIMER_MAX_VALUE in System Time Unit (1us) */
  uint32_t last_calibration_machine_time; /** Last machine time when calibration was performed */
  uint32_t calibration_machine_interval; /** Calibration Interval MTU */
  uint64_t last_system_time; /** Last System Time */
  uint64_t last_calibration_time; /** Absolute system time when last calibration was performed */
  uint8_t  calibration_in_progress;  /*!< Flag to indicate that a periodic calibration has been started */
  uint8_t  close_expiration;  /*!< Flag to indicate that a timer is about to expire */
  uint64_t periodicCalibrationInterval; /** Calibration Interval in system time unit (us) */
  uint8_t  periodic_calibration; /** Tells whether periodic hardware calibration is needed or not, i.e. LSO speed varies with temperature, etc. */
} MRSUBG_TIMER_ContextTypeDef;

/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/** @defgroup MRSUBG_Timer_Private_Defines MRSUBG TIMER Private Defines
  * @{
  */

/* Extra margin to consider before going in low power mode */
#define LOW_POWER_THR_STU (60)
#define LOW_POWER_THR_MTU (30)

/* Automatic Calibration interval 5 sec */
#define FIVE_SECONDS 5000000
/* Assumed slow clock working frequency to be at 32.768 kHz */
#define SLOW_CLOCK_WORKING_FREQ 32768
/* Max attempt number for SCM to exit transitory phase and reach working frequency */
#define MAX_SCM_DELAY_COUNT 10
/* ms to wait between SCM reads during transitory phase */
#define SCM_DELAY_MS 5

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup MRSUBG_Timer_Private_Macros MRSUBG TIMER Private Macros
  * @{
  */

#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
                                __disable_irq(); \
/* Must be called in the same scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

#define MAX(a,b) ((a) < (b) )? (b) : (a)
#define MIN(a,b) ((a) < (b) )? (a) : (b)
#define DIFF8(a,b) ((a)>=(b) ? ((a)-(b)) : (256+((a)-(b))))
#define TIME_DIFF(a, b)       (((int32_t)((a - b) << (32-TIMER_BITS))) >> (32-TIMER_BITS))
/* This define assumes that a is always greater than b */
#define TIME_ABSDIFF(a, b)       ((a - b) & TIMER_MAX_VALUE)
#define INCREMENT_EXPIRE_COUNT_ISR (MRSUBG_TIMER_Context.expired_count = ((MRSUBG_TIMER_Context.expired_count + 1) == MRSUBG_TIMER_Context.served_count) ? MRSUBG_TIMER_Context.expired_count : (MRSUBG_TIMER_Context.expired_count + 1))
#define INCREMENT_EXPIRE_COUNT ATOMIC_SECTION_BEGIN(); INCREMENT_EXPIRE_COUNT_ISR ; ATOMIC_SECTION_END();

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup MRSUBG_Timer_Private_Variables MRSUBG TIMER Private Variables
  * @{
  */
static MRSUBG_TIMER_ContextTypeDef MRSUBG_TIMER_Context;
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup MRSUBG_Timer_Private_Constants MRSUBG TIMER Private Constants
  * @{
  */

/** Margin arging to take for long sleep to allow the
  * system to avoid to have the counter wrapping. It is expressed in machine
  * time, so it is variable when using internal RO
  */
#define TIMER_WRAPPING_MARGIN (4096)
/** Number of significant bits in the radio timer */
#define TIMER_BITS (32)
#define TIMER_MAX_VALUE (0xFFFFFFFFU >> (32-TIMER_BITS))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @addtogroup MRSUBG_Timer_Private_Functions
  * @{
  */
/* Privati Calibration APIs */
static void _get_calibration_data(void);
static void _timer_calibrate(void);
static void _updateCalibrationData(void);
static void _calibration_callback (void *handle);
static void _update_xtal_startup_time(void);
static void _update_system_time(void);
static uint64_t _us_to_machinetime(uint64_t time);
static uint64_t _machinetime_to_us(uint64_t time);
static uint64_t _get_system_time_and_machine(uint32_t *current_machine_time);
static int32_t _start_timer(VTIMER_HandleType *timerHandle, uint64_t time);
static VTIMER_HandleType *_update_user_timeout(VTIMER_HandleType *rootNode, uint8_t *expired);
static uint32_t VTIMER_SetWakeupTime(uint64_t delay, BOOL allow_sleep);
static VTIMER_HandleType * _insert_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle);
static void _virtualTimeBaseEnable(FunctionalState state);
static VTIMER_HandleType * _remove_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle);
static VTIMER_HandleType *_check_callbacks(VTIMER_HandleType *rootNode,VTIMER_HandleType **expiredList);

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup MRSUBG_Timer_Exported_Functions MRSUBG Timer Exported Functions
  * @{
  */

/* ------------------------ RADIO Init APIs ----------------------------------*/
/**
 * @brief  Initialize the radio timer module. It must be placed in the initialization
 *         section of the application.
 * @param MRSUBG_TIMER_InitStruct Radio Timer Initialization parameters
 * @retval None
 */
void HAL_MRSUBG_TIMER_Init(MRSUBG_TIMER_InitTypeDef *MRSUBG_TIMER_InitStruct)
{
  /* Wait to be sure that the Radio Timer is active */
  while(LL_MRSUBG_TIMER_GetAbsoluteTime(MR_SUBG_GLOB_MISC) < 0x10);

  /* Interrupt Configuration */
  LL_MRSUBG_TIMER_ClearFlag_CPUWakeup(MR_SUBG_GLOB_MISC);
  HAL_MRSUBG_TIMER_MspInit();

  /* HSE XTAL clock frequency */
  MRSUBG_TIMER_Context.fast_clock_freq = MRSUBG_TIMER_InitStruct->HSE_XTAL_freq/3;

  /* Calibration Setting */
  MRSUBG_TIMER_Context.periodic_calibration = (MRSUBG_TIMER_InitStruct->periodicCalibrationInterval!=0);
  if (MRSUBG_TIMER_Context.periodic_calibration || MRSUBG_TIMER_InitStruct->enableInitialCalibration)
  {
    _timer_calibrate();
  }
  else
  {
    /* Assume fix frequency at 32.768 kHz */
    MRSUBG_TIMER_Context.slow_clock_freq = SLOW_CLOCK_WORKING_FREQ;
    MRSUBG_TIMER_Context.interpolated_freq = 16u * MRSUBG_TIMER_Context.slow_clock_freq;
    MRSUBG_TIMER_Context.last_interpolated_freq = MRSUBG_TIMER_Context.interpolated_freq;
    MRSUBG_TIMER_Context.timer_max_value = (((uint64_t)TIMER_MAX_VALUE*1000000ull)/MRSUBG_TIMER_Context.interpolated_freq);
  }
  if (MRSUBG_TIMER_InitStruct->periodicCalibrationInterval == 0)
  {
    MRSUBG_TIMER_Context.calibration_machine_interval = TIMER_MAX_VALUE - TIMER_WRAPPING_MARGIN;
  }
  else
  {
    MRSUBG_TIMER_Context.calibration_machine_interval =  MIN(_us_to_machinetime(MRSUBG_TIMER_InitStruct->periodicCalibrationInterval*1000ull),
                                                            (TIMER_MAX_VALUE-TIMER_WRAPPING_MARGIN));
  }
  MRSUBG_TIMER_Context.periodicCalibrationInterval = _machinetime_to_us(MRSUBG_TIMER_Context.calibration_machine_interval);
  MRSUBG_TIMER_Context.calibration_in_progress = FALSE;

  /* XTAL startup time configuration */
  MRSUBG_TIMER_Context.hs_startup_time = MRSUBG_TIMER_InitStruct->XTAL_StartupTime;
  _update_xtal_startup_time();

  /* Init Radio Timer Context */
  MRSUBG_TIMER_Context.last_calibration_machine_time = LL_MRSUBG_TIMER_GetAbsoluteTime(MR_SUBG_GLOB_MISC);
  MRSUBG_TIMER_Context.last_system_time = 0;
  MRSUBG_TIMER_Context.last_calibration_time = _machinetime_to_us(MRSUBG_TIMER_Context.last_calibration_machine_time);
  MRSUBG_TIMER_Context.cumulative_time = MRSUBG_TIMER_Context.last_calibration_time;

  /* Init the Virtual Timer queue */
  MRSUBG_TIMER_Context.rootNode = NULL;
  MRSUBG_TIMER_Context.enableTimeBase = TRUE;
  MRSUBG_TIMER_Context.stop_notimer_action = FALSE;
  MRSUBG_TIMER_Context.expired_count=0;
  MRSUBG_TIMER_Context.served_count=0;

  /* Configure the Calibration callback and schedule the next calibration */
  MRSUBG_TIMER_Context.calibrationTimer.callback = _calibration_callback;
  MRSUBG_TIMER_Context.calibrationTimer.userData = NULL;
  _start_timer(&MRSUBG_TIMER_Context.calibrationTimer, HAL_MRSUBG_TIMER_GetCurrentSysTime() + MRSUBG_TIMER_Context.periodicCalibrationInterval);
}

/**
 * @brief Timer module state machine. Check and schedule the calibration.
 * Check expired timers and execute user callback.
 * It must be placed inside the infinite loop.
 * @retval None
 */
void HAL_MRSUBG_TIMER_Tick(void)
{
  uint8_t expired = 0;

  /* Check for expired timers */
  while (DIFF8(MRSUBG_TIMER_Context.expired_count, MRSUBG_TIMER_Context.served_count))
  {
    VTIMER_HandleType *expiredList, *curr;
    uint8_t to_be_served = DIFF8(MRSUBG_TIMER_Context.expired_count, MRSUBG_TIMER_Context.served_count);

    MRSUBG_TIMER_Context.rootNode = _check_callbacks(MRSUBG_TIMER_Context.rootNode, &expiredList);

    /* Call all the user callbacks */
    curr=expiredList;
    while (curr != NULL)
    {
      /* Save next pointer, in case callback start the timer again */
      VTIMER_HandleType *next = curr->next;
      curr->active = FALSE;
      if (curr->callback)
        curr->callback(curr); /* we are sure a callback is set?*/
      curr = next;
    }

    MRSUBG_TIMER_Context.rootNode = _update_user_timeout(MRSUBG_TIMER_Context.rootNode, &expired);
    if (expired == 1)
    {
      /* A new root timer is already expired, mimic timer expire */
      INCREMENT_EXPIRE_COUNT;
    }

    if (expiredList == NULL)
    {
      /* Set the close_expiration flag to handle an expired timer later, since its not yet percived as expired by software checks */
      MRSUBG_TIMER_Context.close_expiration = 1;
    }
    else
    {
      MRSUBG_TIMER_Context.close_expiration = 0;
    }
    MRSUBG_TIMER_Context.served_count += to_be_served;
  }

  /* Check for periodic calibration */
  if (MRSUBG_TIMER_Context.calibration_in_progress)
  {
    if(LL_MRSUBG_TIMER_GetSCM(MR_SUBG_GLOB_MISC) != 0)
    {
      /* Calibration is completed */
      MRSUBG_TIMER_Context.calibration_in_progress = FALSE;
      /* Collect calibration data */
      _updateCalibrationData();
      HAL_MRSUBG_TIMER_StopVirtualTimer(&MRSUBG_TIMER_Context.calibrationTimer);
      /* Schedule next calibration event */
      _start_timer(&MRSUBG_TIMER_Context.calibrationTimer, HAL_MRSUBG_TIMER_GetCurrentSysTime() + MRSUBG_TIMER_Context.periodicCalibrationInterval);
    }
  }
  /* Make sure no expired timer was left unarmed due to time missalignment */
  if (MRSUBG_TIMER_Context.close_expiration)
  {
    if((MRSUBG_TIMER_Context.calibrationTimer.expiryTime) < HAL_MRSUBG_TIMER_GetCurrentSysTime())
    {
      INCREMENT_EXPIRE_COUNT;
    }
    else if ((MRSUBG_TIMER_Context.rootNode->expiryTime) < HAL_MRSUBG_TIMER_GetCurrentSysTime())
    {
      INCREMENT_EXPIRE_COUNT;
    }
  }
}

/**
 * @brief  Returns the admitted low power mode according to the next timer activity.
 * @return Low Power mode
 */
PowerSaveLevels HAL_MRSUBG_TIMER_PowerSaveLevelCheck(void)
{
  uint32_t nextRadioActivity;
  uint8_t timerState;
  uint32_t hs_startup_machine_time;
  PowerSaveLevels level;

  if (((MRSUBG_TIMER_Context.expired_count == MRSUBG_TIMER_Context.served_count) && !MRSUBG_TIMER_Context.calibration_in_progress) == FALSE)
  {
    return POWER_SAVE_LEVEL_DISABLED;
  }

  level = POWER_SAVE_LEVEL_DEEPSTOP_NOTIMER;

  timerState = HAL_MRSUBG_TIMER_GetRadioTimerValue(&nextRadioActivity);

  /*Wakeup timer are programmed only through the timer module*/
  if (timerState == WAKEUP_MRSUBG_TIMER_BUSY)
  {
    hs_startup_machine_time = _us_to_machinetime(MRSUBG_TIMER_Context.hs_startup_time);
    if(TIME_ABSDIFF(nextRadioActivity, LL_MRSUBG_TIMER_GetAbsoluteTime(MR_SUBG_GLOB_MISC)) < (hs_startup_machine_time+LOW_POWER_THR_MTU))
    {
      return POWER_SAVE_LEVEL_SLEEP;
    }

    level = POWER_SAVE_LEVEL_DEEPSTOP_TIMER;
  }

  if(MRSUBG_TIMER_Context.rootNode != NULL && MRSUBG_TIMER_Context.rootNode->active)
  {
    /* Disable power save if a timer is about to expire */
    if(((MRSUBG_TIMER_Context.rootNode->expiryTime - HAL_MRSUBG_TIMER_GetCurrentSysTime()) < (LOW_POWER_THR_STU + MRSUBG_TIMER_Context.hs_startup_time)*3)|| (MRSUBG_TIMER_Context.close_expiration !=0))
    {
      MRSUBG_TIMER_Context.close_expiration = 1;
      return POWER_SAVE_LEVEL_DISABLED;
    }

    if(level == POWER_SAVE_LEVEL_DEEPSTOP_NOTIMER)
    {
      if((MRSUBG_TIMER_Context.rootNode->next == NULL) && (MRSUBG_TIMER_Context.rootNode == &MRSUBG_TIMER_Context.calibrationTimer))
      {
        MRSUBG_TIMER_Context.stop_notimer_action = TRUE;
        _virtualTimeBaseEnable(DISABLE);
        LL_MRSUBG_TIMER_DisableCPUWakeupTimer(MR_SUBG_GLOB_RETAINED);
        return POWER_SAVE_LEVEL_DEEPSTOP_NOTIMER;
      }
    }
    level = POWER_SAVE_LEVEL_DEEPSTOP_TIMER;
  }

  return level;
}

/* ---------------------- RADIO Activity APIs --------------------------------*/

/**
 * @brief  Return the status of the RFIP Wakeup timer and the last value programmed in the register.
 * @param  time: return the RFIP Wakeup time.
 * @retval 0 if no timer has been programmed.
 * @retval 1 if RFIP Wakeup Timer has been programmed.
 */
uint8_t HAL_MRSUBG_TIMER_GetRadioTimerValue(uint32_t *time)
{
  uint8_t status = 0;

  *time = 0;
  if(LL_MRSUBG_TIMER_IsEnabledRFIPWakeupTimer(MR_SUBG_GLOB_RETAINED))
  {
    *time = LL_MRSUBG_TIMER_GetRFIPWakeupTime(MR_SUBG_GLOB_RETAINED);
    status = WAKEUP_MRSUBG_TIMER_BUSY;
  }

  return status;
}

/* ----------------------- Radio Timer time unit APIs ------------------------*/

/**
 * @brief  Translates time in microseconds into machine time units.
 * @param  time: Microseconds to be converted in MTU
 * @return Machine time value
 */
uint64_t HAL_MRSUBG_TIMER_UsToMachinetime(uint64_t time)
{
  return _us_to_machinetime(time);
}

/**
 * @brief  Translates time machine time in microseconds.
 * @param  time: Machine time to be converted in microseconds
 * @return Time value in microseconds
 */
uint64_t HAL_MRSUBG_TIMER_MachinetimeToUs(uint64_t time)
{
  return _machinetime_to_us(time);
}

/**
 * @brief  This function returns the current reference time expressed in system time units (1us).
 *         The returned value can be used as absolute time parameter where needed in the other
 *         HAL_MRSUBG_TIMER* APIs
 * @return absolute current time expressed in system time units (1 us).
 */
uint64_t HAL_MRSUBG_TIMER_GetCurrentSysTime(void)
{
  uint32_t current_machine_time;
  return _get_system_time_and_machine(&current_machine_time);
}

/* -------------------------- Virtual timer APIs ---------------------------- */

/**
 * @brief Starts a one-shot virtual timer for the given relative timeout value expressed in us
 * @param timerHandle: The virtual timer
 * @param usRelTimeout: The relative time, from current time, expressed in us
 * @retval 0 if the timerHandle is valid.
 * @retval 1 if the timerHandle is not valid. It is already started.
 */
uint32_t HAL_MRSUBG_TIMER_StartVirtualTimer(VTIMER_HandleType *timerHandle, uint64_t usRelTimeout)
{
  uint8_t retVal;
  retVal = _start_timer(timerHandle, (HAL_MRSUBG_TIMER_GetCurrentSysTime()+usRelTimeout));
  _virtualTimeBaseEnable(ENABLE);

  return retVal;
}

/**
 * @brief Starts a one-shot virtual timer for the given relative timeout value expressed in ms
 * @param timerHandle: The virtual timer
 * @param msRelTimeout: The relative time, from current time, expressed in ms
 * @retval 0 if the timerHandle is valid.
 * @retval 1 if the timerHandle is not valid. It is already started.
 */
uint32_t HAL_MRSUBG_TIMER_StartVirtualTimerMs(VTIMER_HandleType *timerHandle, uint32_t msRelTimeout)
{
  uint64_t time = msRelTimeout*1000;
  uint8_t retVal;
  retVal = _start_timer(timerHandle, (HAL_MRSUBG_TIMER_GetCurrentSysTime()+time));
  _virtualTimeBaseEnable(ENABLE);

  return retVal;
}

/**
 * @brief  Stops the one-shot virtual timer specified if found
 * @param  timerHandle: The virtual timer
 * @retval None
 */
void HAL_MRSUBG_TIMER_StopVirtualTimer(VTIMER_HandleType *timerHandle)
{
  VTIMER_HandleType *rootNode = _remove_timer_in_queue(MRSUBG_TIMER_Context.rootNode, timerHandle);
  uint8_t expired = 0;
  timerHandle->active=FALSE;
  if (MRSUBG_TIMER_Context.rootNode != rootNode)
  {
    MRSUBG_TIMER_Context.rootNode = _update_user_timeout(rootNode, &expired);
    if (expired)
    {
      /* A new root timer is already expired, mimic timer expire */
      INCREMENT_EXPIRE_COUNT;
    }
  }
  else
  {
     MRSUBG_TIMER_Context.rootNode = rootNode;
  }
}

/**
 * @brief Returns the absolute expiry time of a running virtual timer expressed in internal system time units (us).
 * @param timerHandle: The virtual timer
 * @retval sysTime: Absolute time expressed in internal system time units (us).
 */
uint64_t HAL_MRSUBG_TIMER_ExpiryTime(VTIMER_HandleType *timerHandle)
{
  return timerHandle->expiryTime;
}

/**
 * @brief  Virtual timer Timeout Callback. It signals that a host timeout occurred.
 * @retval None
 */
void HAL_MRSUBG_TIMER_TimeoutCallback(void)
{
  /* Disable host timer */
  LL_MRSUBG_TIMER_DisableCPUWakeupTimer(MR_SUBG_GLOB_RETAINED);
  INCREMENT_EXPIRE_COUNT_ISR;
  /* Clear the interrupt */
  LL_MRSUBG_TIMER_ClearFlag_CPUWakeup(MR_SUBG_GLOB_MISC);
  LL_MRSUBG_TIMER_IsActiveFlag_CPUWakeup(MR_SUBG_GLOB_MISC);
}

/**
 * @brief  Returns the number of timers in the queue.
 * @return number of timers in the queue.
 */
uint32_t HAL_MRSUBG_TIMER_GetPendingTimers(void)
{
  VTIMER_HandleType *curr = MRSUBG_TIMER_Context.rootNode;
  uint32_t counter = 0;
  while (curr != NULL)
  {
    counter++;
    curr = curr->next;
  }
  return counter;
}

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup MRSUBG_Timer_Private_Functions MRSUBG TIMER Private Functions
  * @{
  */

static void _get_calibration_data(void)
{
  uint16_t scm_counter_currval;
  uint32_t last_interpolated_freq;

  scm_counter_currval = LL_MRSUBG_TIMER_GetSCM(MR_SUBG_GLOB_MISC);
  if ((scm_counter_currval != 0) && (scm_counter_currval != MRSUBG_TIMER_Context.last_scm_counter))
  {
    MRSUBG_TIMER_Context.slow_clock_freq = ((32ull * (uint64_t)MRSUBG_TIMER_Context.fast_clock_freq * 1000)/scm_counter_currval);
    MRSUBG_TIMER_Context.last_scm_counter = scm_counter_currval;
    last_interpolated_freq = MRSUBG_TIMER_Context.interpolated_freq;
    MRSUBG_TIMER_Context.interpolated_freq = (16u * MRSUBG_TIMER_Context.slow_clock_freq)/1000;
    if (last_interpolated_freq == 0)
    {
      MRSUBG_TIMER_Context.last_interpolated_freq = MRSUBG_TIMER_Context.interpolated_freq;
    }
    else
    {
      MRSUBG_TIMER_Context.last_interpolated_freq = last_interpolated_freq;
    }
    MRSUBG_TIMER_Context.slow_clock_freq /= 1000;
    MRSUBG_TIMER_Context.timer_max_value = (((uint64_t)TIMER_MAX_VALUE*1000000ull)/MRSUBG_TIMER_Context.interpolated_freq);
  }
}

static void _timer_calibrate(void)
{
  uint8_t scm_transitory = 0;
  /* wait for SCM to leave reset state value */
  while(LL_MRSUBG_TIMER_GetSCM(MR_SUBG_GLOB_MISC) == 0);
  /* wait for SCM to reach a stable slow clock value after a transitory startup period */
  while((LL_MRSUBG_TIMER_GetSCM(MR_SUBG_GLOB_MISC) != ((32ull * (uint64_t)MRSUBG_TIMER_Context.fast_clock_freq)/SLOW_CLOCK_WORKING_FREQ)) && (scm_transitory++ < MAX_SCM_DELAY_COUNT))
  {
    HAL_Delay(SCM_DELAY_MS);
  }
  _get_calibration_data();
}

static void _update_xtal_startup_time(void)
{
  uint16_t time;

  time= ((MRSUBG_TIMER_Context.hs_startup_time*MRSUBG_TIMER_Context.slow_clock_freq)/1000000ull);
  if(time >= 255)
    time = 255;
  if(time < 16)
    time = 20;

  LL_MRSUBG_TIMER_SetWakeupOffset(MR_SUBG_GLOB_RETAINED, (uint8_t)time);
}

static void _updateCalibrationData(void)
{
    _get_calibration_data();
    _update_xtal_startup_time();
    ATOMIC_SECTION_BEGIN();
    _update_system_time();
    ATOMIC_SECTION_END();
}

static void _calibration_callback (void *handle)
{
  MRSUBG_TIMER_Context.calibration_in_progress = TRUE;
}

static void _update_system_time(void)
{
  uint32_t current_machine_time;
  uint64_t new_time;

  current_machine_time = LL_MRSUBG_TIMER_GetAbsoluteTime(MR_SUBG_GLOB_MISC) & TIMER_MAX_VALUE;
  new_time = ((uint64_t)TIME_ABSDIFF(current_machine_time, MRSUBG_TIMER_Context.last_calibration_machine_time)*1000000ull)/MRSUBG_TIMER_Context.last_interpolated_freq;
  MRSUBG_TIMER_Context.cumulative_time = MRSUBG_TIMER_Context.last_calibration_time + new_time;

  if (TIME_ABSDIFF(current_machine_time, MRSUBG_TIMER_Context.last_calibration_machine_time) < MRSUBG_TIMER_Context.calibration_machine_interval)
  {
     if (MRSUBG_TIMER_Context.periodic_calibration == 0)
     {
        /* When accounting for slow clock frequency oscillations over time:
         * In wrap around conditions of the HW timer, timer_max_value
         * added to the cumulative time needs to be calculated using
         * last_interpolated_freq, used until this calibration cycle.
         */
        MRSUBG_TIMER_Context.cumulative_time += (((uint64_t)TIMER_MAX_VALUE*1000000ull)/MRSUBG_TIMER_Context.last_interpolated_freq);
     }
     else
     {
        /* Account for elapsed time when periodic_calibrations are set & a wraparound of the register occurs */
        MRSUBG_TIMER_Context.cumulative_time += MRSUBG_TIMER_Context.periodicCalibrationInterval;
     }
  }
  MRSUBG_TIMER_Context.last_calibration_machine_time = current_machine_time;
  MRSUBG_TIMER_Context.last_calibration_time = MRSUBG_TIMER_Context.cumulative_time;
  MRSUBG_TIMER_Context.last_interpolated_freq = MRSUBG_TIMER_Context.interpolated_freq;
  /* When accounting for slow clock frequency oscillations over time:
   * periodicCalibrationInterval (used as timeout for the next calibration cycle)
   * has to be calculated dynamically using the current frequency value.
   */
  MRSUBG_TIMER_Context.periodicCalibrationInterval = _machinetime_to_us(MRSUBG_TIMER_Context.calibration_machine_interval);
}

static uint64_t _us_to_machinetime(uint64_t time)
{
  return ((uint64_t)(time * MRSUBG_TIMER_Context.interpolated_freq) / 1000000ull);
}

static uint64_t _machinetime_to_us(uint64_t time)
{
  return ((time*1000000ull)/MRSUBG_TIMER_Context.interpolated_freq);
}

static uint64_t _get_system_time_and_machine(uint32_t *current_machine_time)
{
  uint64_t new_time;

  ATOMIC_SECTION_BEGIN();
  *current_machine_time =  LL_MRSUBG_TIMER_GetAbsoluteTime(MR_SUBG_GLOB_MISC);
  new_time = ((uint64_t)TIME_ABSDIFF(*current_machine_time, MRSUBG_TIMER_Context.last_calibration_machine_time)*1000000ull) / MRSUBG_TIMER_Context.interpolated_freq;
  new_time += MRSUBG_TIMER_Context.cumulative_time;
  if (new_time < MRSUBG_TIMER_Context.last_system_time) {
    new_time += MRSUBG_TIMER_Context.timer_max_value;
  }
  MRSUBG_TIMER_Context.last_system_time = new_time;

  ATOMIC_SECTION_END();

  return new_time;
}

static int32_t _start_timer(VTIMER_HandleType *timerHandle, uint64_t time)
{
  uint8_t expired = 0;

  /* The timer is already started*/
  if(timerHandle->active)
  {
    return 1;
  }
  timerHandle->expiryTime = time;
  timerHandle->active = TRUE;
  if (_insert_timer_in_queue(MRSUBG_TIMER_Context.rootNode, timerHandle) == timerHandle)
  {
    MRSUBG_TIMER_Context.rootNode = _update_user_timeout(timerHandle, &expired);
    if (expired)
    {
      /* A new root timer is already expired, mimic timer expire that is normally signaled
       through the interrupt handler that increase the number of expired timers*/
      INCREMENT_EXPIRE_COUNT;
    }
  }
  return expired;
}

/* Set timeout and skip non active timers */
static VTIMER_HandleType *_update_user_timeout(VTIMER_HandleType *rootNode, uint8_t *expired)
{
  VTIMER_HandleType *curr = rootNode;
  VTIMER_HandleType *rootOrig = rootNode;
  int64_t delay;
  *expired = 0;
  while (curr != NULL)
  {
    if (curr->active) {
      ATOMIC_SECTION_BEGIN();
      delay = curr->expiryTime-HAL_MRSUBG_TIMER_GetCurrentSysTime();
      if (delay > 0)
      {
        /* Protection against interrupt must be used to avoid that the called function will be interrupted
          and so the timer programming will happen after the target time is already passed
          leading to a timer expiring after timer wraps, instead of the expected delay */
        VTIMER_SetWakeupTime(delay, TRUE);
      }
      else
      {
        *expired = 1;
      }
      ATOMIC_SECTION_END();
      break;
    }
    curr=curr->next;
  }
  if (*expired)
    return rootOrig;

  return curr;
}

static uint32_t VTIMER_SetWakeupTime(uint64_t delay, BOOL allow_sleep)
{
  uint32_t current_time;
  uint32_t delay_mtu;

  delay_mtu = _us_to_machinetime(delay);
  /* If the delay is too small round to minimum 2 tick */
  delay_mtu = MAX(32,delay_mtu);
  current_time = LL_MRSUBG_TIMER_GetAbsoluteTime(MR_SUBG_GLOB_MISC);
  /* 4 least significant bits are not taken into account. Then let's round the value */
  LL_MRSUBG_TIMER_SetCPUWakeupTime(MR_SUBG_GLOB_RETAINED, ((current_time + (delay_mtu + 8)) & TIMER_MAX_VALUE));
  LL_MRSUBG_TIMER_EnableCPUWakeupTimer(MR_SUBG_GLOB_RETAINED);

  return current_time;
}

static VTIMER_HandleType * _insert_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle)
{
  VTIMER_HandleType *current = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;

  while ((current!=NULL) && (current->expiryTime < handle->expiryTime))
  {
    prev = current;
    current=current->next;
  }

  handle->next = current;

  if (prev == NULL)
  {
    /* We are the new root */
    returnValue = handle;
  }
  else
  {
    prev->next = handle;
  }

  return returnValue;
}

static void _virtualTimeBaseEnable(FunctionalState state)
{
  if(state != DISABLE)
  {
    if (MRSUBG_TIMER_Context.enableTimeBase == FALSE)
    {
      _calibration_callback(&MRSUBG_TIMER_Context.calibrationTimer);
      MRSUBG_TIMER_Context.enableTimeBase = TRUE;
    }
  }
  else
  {
    HAL_MRSUBG_TIMER_StopVirtualTimer(&MRSUBG_TIMER_Context.calibrationTimer);
    MRSUBG_TIMER_Context.enableTimeBase = FALSE;
  }
}

static VTIMER_HandleType * _remove_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle)
{
  VTIMER_HandleType *current = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;

  while ((current!=NULL) && (current != handle)) {
    prev = current;
    current=current->next;
  }

  if (current == NULL) {
    /* Not found */
  }
  else if (current == rootNode) {
    /* New root node */
    returnValue = current->next;
  }
  else {
    prev->next = current->next;
  }

  return returnValue;
}

/* Check the number of expired timer from rootNode (ordered list of timers) and return the list of expired timers */
static VTIMER_HandleType *_check_callbacks(VTIMER_HandleType *rootNode,VTIMER_HandleType **expiredList)
{

  VTIMER_HandleType *curr = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;
  *expiredList = rootNode;

  int64_t delay;
  uint32_t expiredCount = 0;

  while (curr != NULL) {

    if (curr->active) {
      delay = curr->expiryTime - HAL_MRSUBG_TIMER_GetCurrentSysTime();

      if (delay > 5) {
        /* End of expired timers list */
        break;
      }
    }

    prev = curr;
    curr=curr->next;
    expiredCount++;
  }

  if (expiredCount) {
    /* Some timers expired */
    prev->next=NULL;
    returnValue = curr;
  }
  else {
    /* No timer expired */
    *expiredList = NULL;
  }

  return returnValue;
}

/**
  * @brief MRSUBG TIMER MSP Init
  * @retval None
  */
__weak void HAL_MRSUBG_TIMER_MspInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MRSUBG_TIMER_MspInit could be implemented in the user file
    */
}

/**
  * @brief MRSUBG TIMER MSP DeInit
  * @retval None
  */
__weak void HAL_MRSUBG_TIMER_MspDeInit(void)
{

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MRSubG_MspDeInit could be implemented in the user file
    */
}

__weak void HAL_MRSUBG_TIMER_CPU_WKUP_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_MRSUBG_TIMER_CPU_WKUP_Callback() can be implemented in the user file
    */
}

void HAL_MRSUBG_TIMER_CPU_WKUP_IRQHandler(void)
{
  HAL_MRSUBG_TIMER_CPU_WKUP_Callback();
}

/**
  * @}
  */

#endif /* HAL_MRSUBG_TIMER_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
