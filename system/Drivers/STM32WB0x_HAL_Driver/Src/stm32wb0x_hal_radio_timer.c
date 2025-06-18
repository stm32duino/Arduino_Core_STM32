/**
  ******************************************************************************
  * @file    stm32wb0x_hal_radio_timer.c
  * @author  GPM WBL Application Team
  * @brief   Virtual timer and Radio timer high level APIs
  * @details This file implements the software layer that provides the virtualization of the
  * resources of a single hardware timer in order to allocate many user virtual timers.
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
  * The time base unit is a STU that is the unit exposed to the user and it is equal to 625/256 us.
  * The calibration/anti-wrapping mechanism is not managed by the user.
  *
  * This software layer also exposes the possibility to program a radio timer.
  * A radio timer allows the user to trigger an already configured radio transaction.
  * The duties of this library does not include the configuration of a radio transaction.
  * This layer tries to exploit the last calibration values to program the radio activity
  * in order to improve the accuracy. In this case, the radio event is not immediately programmed
  * when it is requested, but only when the next calibration values are available.
  * Since the calibration values are available inside the timer tick when the calibration is over,
  * the application must ensure that the timer tick is called after the calibration timer
  * expiration within a certain margin in order to avoid that the radio event is shifted in the
  * past and cannot be anymore programmed.
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
#include "stm32wb0x_hal.h"
/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @addtogroup RADIO_TIMER
  * @brief HAL RADIO TIMER  module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup RADIO_TIMER_Private_Types RADIO TIMER Private Types
  * @{
  */
typedef struct
{
  uint8_t periodicCalibration; /*!< Periodic calibration enable status */
  uint32_t periodicCalibrationInterval;  /*!< Periodic calibration interval in ms, to disable set to 0 */
  uint32_t periodicCalibrationCheckDuration;  /*!< Interval between calibration start and timeout interrupt to check if calibration is completed */
  bool calibration_in_progress;  /*!< Flag to indicate that a periodic calibration has been started */
} CalibrationSettingsTypeDef;

typedef struct
{
  uint32_t period;        /** Number of 16 MHz clock cycles in (2*(SLOW_COUNT+1)) low speed oscillator periods */
  uint32_t freq;          /** 2^39/period */
  int32_t freq1;          /** Round(((freq/64)*0x753)/256) */
  int32_t period1;        /** Round (( ((period /256) * 0x8BCF6) + (((period % 256)* 0x8BCF6)/256)) / 32) */
  int32_t last_period1;   /** Period global in last calibration */
  uint64_t last_calibration_time; /** Absolute system time when last calibration was performed */
  uint32_t calibration_machine_interval; /** Calibration Interval MTU */
  uint8_t calibration_data_available; /** Flag to signal if a new calibration data is available or not */
} CalibrationDataTypeDef;

typedef struct
{
  uint8_t tx_cal_delay; /**time in MTU to be compensated if transmission and pll calibration are requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t tx_no_cal_delay; /**time in MTU to be compensated if transmission is requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t rx_cal_delay; /**time in MTU to be compensated if reception and pll calibration are requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t rx_no_cal_delay; /**time in MTU to be compensated if reception is requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t tx_cal_delay_st; /**time in STU to be compensated if transmission and pll calibration are requested. The value in RAM must be initialized before the TIMER is initialized*/
  uint8_t tim12_delay_mt;
} TxRxDelayTypeDef;

typedef struct
{
  uint64_t expiryTime;
  bool cal_req;
  bool active;
  bool pending;
  bool intTxRx_to_be_served;
  bool event_type;
} RADIO_TIMER_RadioHandleTypeDef;

typedef struct
{
  CalibrationSettingsTypeDef calibrationSettings;
  CalibrationDataTypeDef calibrationData;
  TxRxDelayTypeDef TxRxDelay;
  VTIMER_HandleType calibrationTimer;
  RADIO_TIMER_RadioHandleTypeDef radioTimer;
  uint32_t hs_startup_time; /*!< HS startup time */
  uint64_t cumulative_time; /** Absolute system time since power up */
  uint64_t last_system_time; /** Last System Time */
  uint32_t last_machine_time; /** Last machine time used to update cumulative time */
  uint8_t last_setup_time; /**setup time of last timer programmed*/
  uint32_t last_anchor_mt;
  VTIMER_HandleType *rootNode; /*!< First timer of the host timer queue */
  bool enableTimeBase;      /*!< Internal flag. User can ignore it*/
  uint8_t expired_count; /*!< Progressive number to indicate expired timers */
  uint8_t served_count; /*!< Progressive number to indicate served expired timers */
  uint8_t stop_notimer_action; /*!< Flag to indicate DEEPSTOP no timer action */
  uint8_t wakeup_calibration; /*!< Flag to indicate if start a calibration after  wakeup */
#if defined (STM32WB06) || defined (STM32WB07)
  uint8_t hostIsRadioPending; /*!< If hostIsRadioPending is true, the virtual timer callback will be triggered when the wakeup timer triggers */
  uint32_t hostMargin; /*!< It depends on the hs startup time. See HOST_MARGIN */
  uint8_t waitCal; /*!< Wait the next calibration to get the latest values */
#endif
} RADIO_TIMER_ContextTypeDef;

/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/** @defgroup RADIO_TIMER_Private_Defines RADIO TIMER Private Defines
  * @{
  */
#define MULT64_THR_FREQ (806)
#define MULT64_THR_PERIOD (1589)

/* Margin to add to the calibration interval in order to guarantee
 * enough time to program the radio timer after the calibration.
 * It is expressed in STU. */
#define RADIO_ACTIVITY_MARGIN (204800)

/* Time after that calibration should be completed
 * It is expressed in STU.*/

#define CALIBRATION_CHECK_DURATION (100)

/* Threshold to take into account the calibration duration. */

#define CALIB_SAFE_THR (370)

/* Minimum threshold to safely program the radio timer (expressed in STU) */
#define TIMER1_MARGIN (10)

/*  Delay to program a radio timer in the worst case (in STU).
   This is the sum of: 1st init dalay, 2 init delay and tx delay (118 + 65 + 2)  */
#define TIMER1_INIT_DELAY (76)

/* Radio event types */
#define RX (0)
#define TX (1)

#define MARGIN_EXT (200)

/* Minimum threshold in STU to safely clear radio timers.
The wakeup timer in the worst case triggers about 30us in advance.
This must be considered when the radio timer is cleared.
Then a window of about 30 us is considered as critical, that is
it is not sure the timer can be cleared properly */
#define CLEAR_MIN_THR (15)

/* Extra margin to consider before going in low power mode.
   This is the time (STU) needed for the system to go to sleep from the time the
   HAL_RADIO_TIMER_PowerSaveLevelCheck() is called. */
#define LOW_POWER_THR (82)  // Around 200 us.

#if defined (STM32WB06) || defined (STM32WB07)
/* HOST_MARGIN is the margin in STU needed to program a pending radio operation after the host timer is triggered */
#define HOST_MARGIN (200)

#define RADIO_TX_RX_EXCEPTION_NUMBER 18
#endif

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup RADIO_TIMER_Private_Macros RADIO TIMER Private Macros
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
#define INCREMENT_EXPIRE_COUNT_ISR (RADIO_TIMER_Context.expired_count\
                                    = ((RADIO_TIMER_Context.expired_count + 1) == RADIO_TIMER_Context.served_count) ? RADIO_TIMER_Context.expired_count : (RADIO_TIMER_Context.expired_count + 1))
#define INCREMENT_EXPIRE_COUNT ATOMIC_SECTION_BEGIN(); INCREMENT_EXPIRE_COUNT_ISR ; ATOMIC_SECTION_END();

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup RADIO_TIMER_Private_Variables RADIO TIMER Private Variables
  * @{
  */
static RADIO_TIMER_ContextTypeDef RADIO_TIMER_Context;
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup RADIO_TIMER_Private_Constants  RADIO TIMER Private Constants
  * @{
  */
#define TIMER_SYSTICK_PER_FIVE_SECONDS (2048000)
#define TIMER_SYSTICK_PER_SECOND       (409600)
#define TIMER_SYSTICK_PER_10MS         (4096)

/** Margin arging to take for long sleep to allow the
  * system to avoid to have the counter wrapping. It is expressed in machine
  * time, so it is variable when using internal RO
  */
#define TIMER_WRAPPING_MARGIN (4096)
/** Number of significant bits in the radio timer */
#define TIMER_BITS (32)
#define TIMER_MAX_VALUE (0xFFFFFFFFU >> (32-TIMER_BITS))

#define WAKEUP_INIT_DELAY (27) /* about 65us in STU */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @addtogroup RADIO_TIMER_Private_Functions
  * @{
  */
/* Privati Calibration APIs */
static void _calibrationProcedure(void);
static void _timer_start_calibration(void);
static void _timer_calibrate(CalibrationDataTypeDef *calibrationData);
static void _get_calibration_data(CalibrationDataTypeDef *calibrationData);
static void _calibration_callback(void *handle);
static void _updateCalibrationData(void);

static uint32_t _us_to_systime(uint32_t time);
static uint32_t _us_to_machinetime(uint32_t time);
static void _configureTxRxDelay(RADIO_TIMER_ContextTypeDef *context, uint8_t calculate_st);
static void _update_xtal_startup_time(uint16_t hs_startup_time, int32_t freq1);
uint32_t blue_unit_conversion(uint32_t time, uint32_t period_freq,
                              uint32_t thr); /* Translate MTU to STU and vice-versa. It is implemented using integer operation. */
static uint64_t _get_system_time_and_machine(RADIO_TIMER_ContextTypeDef *context, uint32_t *current_machine_time);
static int32_t _start_timer(VTIMER_HandleType *timerHandle, uint64_t time);
static VTIMER_HandleType *_update_user_timeout(VTIMER_HandleType *rootNode, uint8_t *expired);
static VTIMER_HandleType *_insert_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle);
static void _virtualTimeBaseEnable(FunctionalState state);
static VTIMER_HandleType *_remove_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle);
static VTIMER_HandleType *_check_callbacks(VTIMER_HandleType *rootNode, VTIMER_HandleType **expiredList);
static void _update_system_time(RADIO_TIMER_ContextTypeDef *context);
static void _check_radio_activity(RADIO_TIMER_RadioHandleTypeDef *timerHandle, uint8_t *expired);
#if defined (STM32WB06) || defined (STM32WB07)
static uint32_t TIMER_SetRadioHostWakeupTime(uint32_t delay, bool *share);
static void _set_controller_as_host(void);
static void _check_host_activity(void);
#else
static uint32_t VTIMER_SetWakeupTime(uint32_t delay, bool allow_sleep);
#endif
static uint8_t TIMER_SetRadioTimerValue(uint32_t timeout, bool event_type, bool cal_req);
static uint64_t TIMER_GetPastSysTime(uint32_t time, uint64_t *current_system_time);
static bool TIMER_SleepCheck(void);
static uint8_t TIMER_GetRadioTimerValue(uint32_t *time);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RADIO_TIMER_Exported_Functions Radio Timer Exported Functions
  * @{
  */

/* ------------------------ RADIO Init APIs ----------------------------------*/
/**
  * @brief  Initialize the radio timer module. It must be placed in the initialization
  *         section of the application.
  * @param RADIO_TIMER_InitStruct Radio Timer Initialization parameters
  * @retval None
  */
void HAL_RADIO_TIMER_Init(RADIO_TIMER_InitTypeDef *RADIO_TIMER_InitStruct)
{
  /* Interrupt Configuration */
  LL_RADIO_TIMER_ClearFlag_CPUWakeup(WAKEUP);
  LL_RADIO_TIMER_EnableCPUWakeupIT(WAKEUP);
  NVIC_EnableIRQ(RADIO_TIMER_CPU_WKUP_IRQn);
  NVIC_EnableIRQ(RADIO_TIMER_ERROR_IRQn);

#if defined (STM32WB06) || defined (STM32WB07)
  LL_RADIO_TIMER_ClearFlag_BLEWakeup(WAKEUP);
  LL_RADIO_TIMER_EnableBLEWakeupIT(WAKEUP);
  NVIC_EnableIRQ(RADIO_TIMER_TXRX_WKUP_IRQn);
  RADIO_TIMER_Context.hostMargin = MAX(HOST_MARGIN, RADIO_TIMER_InitStruct->XTAL_StartupTime);
#endif

  /* Calibration Setting */
  RADIO_TIMER_Context.calibrationSettings.periodicCalibration = (RADIO_TIMER_InitStruct->periodicCalibrationInterval != 0);
  if (RADIO_TIMER_Context.calibrationSettings.periodicCalibration || RADIO_TIMER_InitStruct->enableInitialCalibration)
  {
    _calibrationProcedure();
  }
  else
  {
    /* Assume fix frequency at 32.768 kHz */
    RADIO_TIMER_Context.calibrationData.last_period1 = 0x00190000;
    RADIO_TIMER_Context.calibrationData.period1 = 0x00190000 ;
    RADIO_TIMER_Context.calibrationData.freq1 = 0x0028F5C2 ;
    RADIO_TIMER_Context.calibrationData.period = 23437;
    RADIO_TIMER_Context.calibrationData.freq = 23456748;
  }
  if (RADIO_TIMER_InitStruct->periodicCalibrationInterval == 0)
  {
    RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval = HAL_RADIO_TIMER_MachineTimeToSysTime(0x50000000);


  }
  else
  {
    RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval = (TIMER_SYSTICK_PER_10MS * RADIO_TIMER_InitStruct->periodicCalibrationInterval) / 10;
    RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval = MIN(RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval,
                                                                              HAL_RADIO_TIMER_MachineTimeToSysTime(TIMER_MAX_VALUE - TIMER_WRAPPING_MARGIN));
  }
  RADIO_TIMER_Context.calibrationSettings.periodicCalibrationCheckDuration = CALIBRATION_CHECK_DURATION;
  RADIO_TIMER_Context.calibrationSettings.calibration_in_progress = FALSE;

  /* XTAL startup time configuration */
  RADIO_TIMER_Context.hs_startup_time = RADIO_TIMER_InitStruct->XTAL_StartupTime;
  _update_xtal_startup_time(RADIO_TIMER_Context.hs_startup_time, RADIO_TIMER_Context.calibrationData.freq1);

  /* Init Radio Timer Context */
  RADIO_TIMER_Context.last_setup_time = 0;
  RADIO_TIMER_Context.cumulative_time = 0;
  RADIO_TIMER_Context.last_machine_time = LL_RADIO_TIMER_GetAbsoluteTime(WAKEUP);
  RADIO_TIMER_Context.last_system_time = 0;
  RADIO_TIMER_Context.calibrationData.last_calibration_time = 0;
  RADIO_TIMER_Context.calibrationData.calibration_data_available = 0;
  RADIO_TIMER_Context.calibrationData.calibration_machine_interval = blue_unit_conversion(RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval,
                                                                     RADIO_TIMER_Context.calibrationData.freq1, MULT64_THR_FREQ);
  RADIO_TIMER_Context.wakeup_calibration = RADIO_TIMER_Context.calibrationSettings.periodicCalibration;

  /* Init the Virtual Timer queue */
  RADIO_TIMER_Context.rootNode = NULL;
  RADIO_TIMER_Context.enableTimeBase = TRUE;
  RADIO_TIMER_Context.stop_notimer_action = FALSE;
  RADIO_TIMER_Context.expired_count = 0;
  RADIO_TIMER_Context.served_count = 0;

  /* Init Radio Timer queue */
  RADIO_TIMER_Context.radioTimer.active = FALSE;
  RADIO_TIMER_Context.radioTimer.pending = FALSE;
  RADIO_TIMER_Context.radioTimer.intTxRx_to_be_served = FALSE;
  RADIO_TIMER_Context.radioTimer.expiryTime = 0;

  /* Configure the Calibration callback and schedule the next calibration */
  RADIO_TIMER_Context.calibrationTimer.callback = _calibration_callback;
  RADIO_TIMER_Context.calibrationTimer.userData = NULL;
  _start_timer(&RADIO_TIMER_Context.calibrationTimer,
               HAL_RADIO_TIMER_GetCurrentSysTime() + RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval);

  /* Tx & Rx delay configuration */
  _configureTxRxDelay(&RADIO_TIMER_Context, TRUE);
}

/**
  * @brief Timer module state machine. Check and schedule the calibration.
  * Check expired timers and execute user callback.
  * It must be placed inside the infinite loop.
  * @retval None
  */
void HAL_RADIO_TIMER_Tick(void)
{
  uint8_t expired = 0;

  ATOMIC_SECTION_BEGIN();
  if (RADIO_TIMER_Context.radioTimer.active)
  {
    if (RADIO_TIMER_Context.radioTimer.expiryTime < HAL_RADIO_TIMER_GetCurrentSysTime())
    {
      RADIO_TIMER_Context.radioTimer.active = FALSE;
    }
  }
  ATOMIC_SECTION_END();

  /* Check for expired timers */
  while (DIFF8(RADIO_TIMER_Context.expired_count, RADIO_TIMER_Context.served_count))
  {
    VTIMER_HandleType *expiredList, *curr;
    uint8_t to_be_served = DIFF8(RADIO_TIMER_Context.expired_count, RADIO_TIMER_Context.served_count);

    RADIO_TIMER_Context.rootNode = _check_callbacks(RADIO_TIMER_Context.rootNode, &expiredList);

    /* Call all the user callbacks */
    curr = expiredList;
    while (curr != NULL)
    {
      /* Save next pointer, in case callback start the timer again */
      VTIMER_HandleType *next = curr->next;
      curr->active = FALSE;
      if (curr->callback)
      {
        curr->callback(curr); /* we are sure a callback is set?*/
      }
      curr = next;
    }

    RADIO_TIMER_Context.rootNode = _update_user_timeout(RADIO_TIMER_Context.rootNode, &expired);
    if (expired == 1)
    {
      /* A new root timer is already expired, mimic timer expire */
      INCREMENT_EXPIRE_COUNT;
    }
    RADIO_TIMER_Context.served_count += to_be_served;
  }

  /* Check for periodic calibration */
  if (RADIO_TIMER_Context.calibrationSettings.calibration_in_progress)
  {
    if (LL_RADIO_TIMER_IsActiveFlag_LSICalibrationEnded(RADIO_CTRL))
    {
      /* Calibration is completed */
      RADIO_TIMER_Context.calibrationSettings.calibration_in_progress = FALSE;
      if ((RADIO_TIMER_Context.wakeup_calibration == FALSE) && RADIO_TIMER_Context.stop_notimer_action)
      {
        RADIO_TIMER_Context.stop_notimer_action = FALSE;
      }
      else
      {
        /* Collect calibration data */
        _updateCalibrationData();
        RADIO_TIMER_Context.rootNode = _update_user_timeout(RADIO_TIMER_Context.rootNode, &expired);
        if (expired == 1)
        {
          /* A new root timer is already expired, mimic timer expire */
          INCREMENT_EXPIRE_COUNT;
        }
      }

#if defined (STM32WB06) || defined (STM32WB07)
      if (RADIO_TIMER_Context.waitCal)
      {
        RADIO_TIMER_Context.waitCal = 0;
        RADIO_TIMER_Context.radioTimer.pending = TRUE;
        _check_radio_activity(&RADIO_TIMER_Context.radioTimer, &expired);
        RADIO_TIMER_Context.rootNode = _update_user_timeout(RADIO_TIMER_Context.rootNode, &expired);
        if (expired == 1)
        {
          /* A new root timer is already expired, mimic timer expire */
          INCREMENT_EXPIRE_COUNT;
        }
      }
#else
      _check_radio_activity(&RADIO_TIMER_Context.radioTimer, &expired); //Start Radio Timer after calibration
#endif

      /* Schedule next calibration event */
      HAL_RADIO_TIMER_StopVirtualTimer(&RADIO_TIMER_Context.calibrationTimer);
      _start_timer(&RADIO_TIMER_Context.calibrationTimer,
                   HAL_RADIO_TIMER_GetCurrentSysTime() + RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval);
    }
  }
  /* if there is a periodic calibration, start it in advance during the active phase */
  else
  {
    if (RADIO_TIMER_Context.calibrationSettings.periodicCalibration)
    {
      if (HAL_RADIO_TIMER_GetCurrentSysTime() > (RADIO_TIMER_Context.calibrationData.last_calibration_time +
                                                 TIMER_SYSTICK_PER_FIVE_SECONDS))
      {
        HAL_RADIO_TIMER_StopVirtualTimer(&RADIO_TIMER_Context.calibrationTimer);
        _calibration_callback(&RADIO_TIMER_Context.calibrationTimer);
      }
    }
  }
}

/**
  * @brief  Return the status of the radio timer.
  *         The timeout of the last radio timer activity taken into account by the Timer Module
  *         is saved in the variable passed as parameter.
  * @param  time: Pointer of the variable where the time of the last radio activity scheduled is stored
  *               The time is expressed in STU.
  * @retval 0 if no radio timer is pending.
  * @retval 1 if a radio timer is pending.
  */
RADIO_TIMER_Status HAL_RADIO_TIMER_GetRadioTimerStatus(uint64_t *time)
{
  RADIO_TIMER_Status status;

  *time = RADIO_TIMER_Context.radioTimer.expiryTime;
  if ((RADIO_TIMER_Context.radioTimer.pending) || (LL_RADIO_TIMER_IsEnabledBLEWakeupTimer(WAKEUP))
      || (LL_RADIO_TIMER_IsEnabledTimer1(BLUE)))
  {
    status =  RADIO_TIMER_PENDING;
  }
  else
  {
    status = RADIO_TIMER_OFF;
  }
  return status;
}

/**
  * @brief Get the last anchorPoint in system time unit.
  * @param current_system_time: Current System Time
  * @return TimerCapture register in system time unit.
  */
uint64_t HAL_RADIO_TIMER_GetAnchorPoint(uint64_t *current_system_time)
{
  return TIMER_GetPastSysTime(BLUE->TIMERCAPTUREREG, current_system_time);
}

/**
  * @brief  Returns the admitted low power mode according to the next timer activity.
  * @return Low Power mode
  */
PowerSaveLevels HAL_RADIO_TIMER_PowerSaveLevelCheck(void)
{
  uint32_t nextRadioActivity;
  uint8_t timerState;
  uint64_t current_time;
  PowerSaveLevels level;

  if (TIMER_SleepCheck() == FALSE)
  {
    return POWER_SAVE_LEVEL_RUNNING;
  }

  level = POWER_SAVE_LEVEL_STOP;

  current_time = HAL_RADIO_TIMER_GetCurrentSysTime();
  timerState = TIMER_GetRadioTimerValue(&nextRadioActivity);

  /*Timer1 and wakeup timer are programmed only through the timer module*/
  if (((RADIO_TIMER_Context.radioTimer.active || RADIO_TIMER_Context.radioTimer.pending)
       && !(timerState == RADIO_TIMER1_BUSY)) || RADIO_TIMER_Context.radioTimer.intTxRx_to_be_served)
  {
    if (RADIO_TIMER_Context.radioTimer.expiryTime < (current_time + \
                                                     RADIO_TIMER_Context.last_setup_time + \
                                                     RADIO_TIMER_Context.hs_startup_time + \
                                                     LOW_POWER_THR))
    {
      return POWER_SAVE_LEVEL_CPU_HALT;
    }

    level = POWER_SAVE_LEVEL_STOP_LS_CLOCK_ON;
  }
  else
  {
    if ((timerState == RADIO_TIMER2_BUSY) || (timerState == RADIO_TIMER1_BUSY))
    {
      return POWER_SAVE_LEVEL_CPU_HALT;
    }
  }

  if (RADIO_TIMER_Context.rootNode != NULL && RADIO_TIMER_Context.rootNode->active)
  {
    if (RADIO_TIMER_Context.rootNode->expiryTime < (current_time + LOW_POWER_THR + RADIO_TIMER_Context.hs_startup_time))
    {
      return POWER_SAVE_LEVEL_CPU_HALT;
    }

    if (level == POWER_SAVE_LEVEL_STOP)
    {
      if ((RADIO_TIMER_Context.rootNode->next == NULL)
          && (RADIO_TIMER_Context.rootNode == &RADIO_TIMER_Context.calibrationTimer))
      {
        RADIO_TIMER_Context.stop_notimer_action = TRUE;
        _virtualTimeBaseEnable(DISABLE);
        LL_RADIO_TIMER_DisableCPUWakeupTimer(WAKEUP);
        return POWER_SAVE_LEVEL_STOP;
      }
    }
    level = POWER_SAVE_LEVEL_STOP_LS_CLOCK_ON;
  }

  return level;
}

/* ---------------------- RADIO Activity APIs --------------------------------*/
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
uint32_t HAL_RADIO_TIMER_SetRadioTimerValue(uint32_t time, uint8_t event_type, uint8_t cal_req)
{
  uint8_t retVal = 0;
#if defined (STM32WB06) || defined (STM32WB07)
  uint64_t current_time;
#endif

  RADIO_TIMER_Context.radioTimer.event_type = event_type;
  RADIO_TIMER_Context.radioTimer.cal_req = cal_req;
  RADIO_TIMER_Context.radioTimer.expiryTime = RADIO_TIMER_Context.calibrationData.last_calibration_time + (uint32_t)(time - (uint32_t)RADIO_TIMER_Context.calibrationData.last_calibration_time);
  RADIO_TIMER_Context.radioTimer.active = FALSE;
  RADIO_TIMER_Context.radioTimer.intTxRx_to_be_served = FALSE;
  RADIO_TIMER_Context.radioTimer.pending = TRUE;

#if defined (STM32WB06) || defined (STM32WB07)
  current_time = HAL_RADIO_TIMER_GetCurrentSysTime();

  if (RADIO_TIMER_Context.rootNode == NULL)
  {
    _check_radio_activity(&RADIO_TIMER_Context.radioTimer, &retVal);
  }
  else
  {
    if (RADIO_TIMER_Context.rootNode->expiryTime < current_time ||
        ((RADIO_TIMER_Context.radioTimer.expiryTime < (RADIO_TIMER_Context.rootNode->expiryTime +
                                                       RADIO_TIMER_Context.hostMargin)) && RADIO_TIMER_Context.rootNode->active) || !RADIO_TIMER_Context.rootNode->active)
    {
      /* Program the radio timer */
      _check_radio_activity(&RADIO_TIMER_Context.radioTimer, &retVal);
      if ((RADIO_TIMER_Context.radioTimer.expiryTime >= RADIO_TIMER_Context.rootNode->expiryTime)
          && RADIO_TIMER_Context.rootNode->active)
      {
        /*The radio operation is before or too close the host timeout*/
        RADIO_TIMER_Context.hostIsRadioPending = 1;
      }
    }
    else
    {
      /* If radio timer is not programmed, an emulated host timer is already programmed.
      Make sure radio errors are disabled.
      This call is not needed if radio errors are not enabled by the BLE stack. */
      _set_controller_as_host();
      _check_host_activity();
    }
  }
#else
  _check_radio_activity(&RADIO_TIMER_Context.radioTimer, &retVal);
#endif

  _virtualTimeBaseEnable(ENABLE);

  return retVal;
}

/**
  * @brief   Programs Timer1 with a relative timeout - expressed in us - wrt the previous radio event.
  * @param   rel_timeout_us: relative delay, in us, wrt the previous radio event.
  * @param   event_type: 1 Tx event.
                         0 Rx event
  * @param   cal_req: 1 PLL calibartion is requested.
                      0 PLL calibartion is not requested.
  * @warning The API must be called with interrupts disabled to avoid programming the timer with a value in the past
  * @retval  0 if a correct timeout has been programmed in the timeout register
  * @retval  1 if a correct timeout cannot be programmed
  */
uint32_t HAL_RADIO_TIMER_SetRadioTimerRelativeUsValue(uint32_t rel_timeout_us, bool event_type, bool cal_req)
{
  uint32_t event_time;
  uint32_t radio_init_delay;
  uint32_t abs_timeout_mt;
  uint32_t current_machine_time;

  /*choose the 2nd init duration. Check the event_type and cal. request*/
  if (event_type == TX)
  {
    if (cal_req)
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.tx_cal_delay;
    }
    else
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.tx_no_cal_delay;
    }
  }
  else
  {
    if (cal_req)
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.rx_cal_delay;
    }
    else
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.rx_no_cal_delay;
    }
  }

  abs_timeout_mt =  RADIO_TIMER_Context.last_anchor_mt + _us_to_machinetime(rel_timeout_us);

  event_time = (abs_timeout_mt - RADIO_TIMER_Context.TxRxDelay.tim12_delay_mt - radio_init_delay) & TIMER_MAX_VALUE;

  current_machine_time = WAKEUP->ABSOLUTE_TIME;

  if ((event_time - current_machine_time) > 0x80000000)
  {
    /* Requested time is in the past, return error */
    return 1;
  }

  LL_RADIO_TIMER_SetTimeout(BLUE, event_time);
  LL_RADIO_TIMER_EnableTimer1(BLUE);
  LL_RADIO_TIMER_DisableBLEWakeupTimer(WAKEUP);

#if defined (STM32WB06) || defined (STM32WB07)
  BLUEGLOB->BYTE4 |= 1 << 7;
  BLUEGLOB->BYTE22 = 0xF0;
  BLUEGLOB->BYTE23 = 0xFF;
#endif

  RADIO_TIMER_Context.last_anchor_mt = abs_timeout_mt & TIMER_MAX_VALUE;

  radio_init_delay += RADIO_TIMER_Context.TxRxDelay.tim12_delay_mt;
  RADIO_TIMER_Context.last_setup_time = blue_unit_conversion(radio_init_delay, RADIO_TIMER_Context.calibrationData.period1, MULT64_THR_PERIOD);

  return 0;
}

/**
  * @brief  Return the status of the Radio timers and the last value programmed in the register.
  * @note   When Timer2 is on schedule, the time is expressed in microseconds, otherwise in absolute machine time units.
  * @param  time: pointer to value which is going to have time value.
  * @retval 0 if no timer has been programmed.
  * @retval 1 if Timer1 has been programmed.
  * @retval 2 if Timer2 has been programmed.
  * @retval 3 if Wakeup Timer has been programmed.
  */
uint8_t HAL_RADIO_TIMER_GetRadioTimerValue(uint32_t *time)
{
  return TIMER_GetRadioTimerValue(time);
}

/**
  * @brief  Clear the last radio activity scheduled disabling the radio timers too.
  *         Furthermore, it returns if the timeout is too close with respect the current time and
  *         the radio activity might not be cleared in time.
  * @retval 0 if the radio activity has been cleared successfully.
  * @retval 1 if it is too late to clear the last radio activity.
  * @retval 2 if it might not be possible to clear the last radio activity.
  */
uint32_t HAL_RADIO_TIMER_ClearRadioTimerValue(void)
{
  int64_t time_diff;
  uint8_t retVal;

  /* Disable Radio Timer1/2 and BLE Wakeup Timer */
  LL_RADIO_TIMER_DisableTimer1(BLUE);
  LL_RADIO_TIMER_DisableTimer2(BLUE);
  LL_RADIO_TIMER_DisableBLEWakeupTimer(WAKEUP);
  RADIO_TIMER_Context.radioTimer.active = FALSE;
  RADIO_TIMER_Context.radioTimer.pending = FALSE;
  RADIO_TIMER_Context.radioTimer.intTxRx_to_be_served = FALSE;

  /*The rfSetup is different if Timer1 or Wakeup timer is programmed*/
  ATOMIC_SECTION_BEGIN();
  time_diff = RADIO_TIMER_Context.radioTimer.expiryTime \
              - HAL_RADIO_TIMER_GetCurrentSysTime() \
              - RADIO_TIMER_Context.last_setup_time;
  ATOMIC_SECTION_END();

#if defined (STM32WB06) || defined (STM32WB07)
  /* Check if the routine is executed in the Tx/Rx interrupt handler or not */
  if (((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) - 16) != RADIO_TX_RX_EXCEPTION_NUMBER)
  {
    _check_host_activity();
  }
#endif

  if (time_diff <= 0)
  {
    retVal = HAL_RADIO_TIMER_LATE;
  }
  else if (time_diff < CLEAR_MIN_THR)
  {
    retVal = HAL_RADIO_TIMER_CRITICAL;
  }
  else
  {
    retVal = HAL_RADIO_TIMER_SUCCESS;
  }

  return retVal;
}

/**
  * @brief Program the radio timer (a.k.a Timer1) as close as possible.
  *        The current time is sampled and increased by two.
  *        It means that the timer is going to trigger in a timer interval that goes
  *        from one to two machine time units.
  */
void HAL_RADIO_TIMER_SetRadioCloseTimeout(void)
{
  uint32_t current_time;

  ATOMIC_SECTION_BEGIN();
  current_time = LL_RADIO_TIMER_GetAbsoluteTime(WAKEUP);
  LL_RADIO_TIMER_SetTimeout(BLUE, ((current_time + 2) & TIMER_MAX_VALUE));
  LL_RADIO_TIMER_EnableTimer1(BLUE);
  ATOMIC_SECTION_END();
}

/**
  * @brief  Radio activity finished.
  * @retval None
  */
void HAL_RADIO_TIMER_RadioTimerIsr(void)
{
#if defined (STM32WB06) || defined (STM32WB07)
  if (!(LL_RADIO_TIMER_IsEnabledTimer1(BLUE) || LL_RADIO_TIMER_IsEnabledTimer2(BLUE)))
  {
    _check_host_activity();
  }
#endif
}

/**
  * @brief  Timer State machine semaphore to signal the radio activity finished.
  * @retval None
  */
void HAL_RADIO_TIMER_EndOfRadioActivityIsr(void)
{
  RADIO_TIMER_Context.radioTimer.intTxRx_to_be_served = FALSE;
}

/* ----------------------- Radio Timer time unit APIs ------------------------*/

/**
  * @brief  Translate time in microseconds into sys time units.
  * @param  time: Microseconds to be converted in STU
  * @return STU value
  */
uint32_t HAL_RADIO_TIMER_UsToSystime(uint32_t time)
{
  return _us_to_systime(time);
}

/**
  * @brief   Returns the STU corresponding to the MTU passed as parameter.
  * @param   time: MTU amount to be converted in STU
  * @warning This function is not re-entrant since it updates the context variable
  *          storing the system time. It should be called only in
  *          user context and not in interrupt context.
  * @return  STU value
  */
uint32_t HAL_RADIO_TIMER_MachineTimeToSysTime(uint32_t time)
{
  return blue_unit_conversion(time, RADIO_TIMER_Context.calibrationData.period1, MULT64_THR_PERIOD);
}

/**
  * @brief  This function returns the current reference time expressed in system time units.
  *         The returned value can be used as absolute time parameter where needed in the other
  *         HAL_RADIO_TIMER* APIs
  * @return absolute current time expressed in system time units.
  */
uint64_t HAL_RADIO_TIMER_GetCurrentSysTime(void)
{
  uint32_t current_machine_time;
  return _get_system_time_and_machine(&RADIO_TIMER_Context, &current_machine_time);
}

/**
  * @brief  This function returns the sum of an absolute time and a signed relative time.
  * @param  sysTime: Absolute time expressed in internal time units.
  * @param  msTime: Signed relative time expressed in ms.
  * @return 64bit resulting absolute time expressed in internal time units.
  */
uint64_t HAL_RADIO_TIMER_AddSysTimeMs(uint64_t sysTime, int32_t msTime)
{
  int32_t sysTick = (msTime * TIMER_SYSTICK_PER_10MS) / 10;
  return (sysTime + sysTick);
}

/**
  * @brief  Returns the difference between two absolute times: sysTime1-sysTime2.
  *         The resulting value is expressed in ms.
  * @param  sysTime2: Absolute time expressed in internal time units.
  * @param  sysTime1: Absolute time expressed in internal time units.
  * @return resulting signed relative time expressed in ms.
  */
int64_t HAL_RADIO_TIMER_DiffSysTimeMs(uint64_t sysTime1, uint64_t sysTime2)
{
  return ((sysTime1 - sysTime2) * 10) >> 12;
}

/* -------------------------- Virtual timer APIs ---------------------------- */

/**
  * @brief  Starts a one-shot virtual timer for the given relative timeout value expressed in ms
  * @param  timerHandle: The virtual timer
  * @param  msRelTimeout: The relative time, from current time, expressed in ms
  * @retval 0 if the timerHandle is valid.
  * @retval 1 if the timerHandle is not valid. It is already started.
  */
uint32_t HAL_RADIO_TIMER_StartVirtualTimer(VTIMER_HandleType *timerHandle, uint32_t msRelTimeout)
{
  uint64_t temp = msRelTimeout;
  uint8_t retVal;
  retVal = _start_timer(timerHandle, HAL_RADIO_TIMER_GetCurrentSysTime() + (temp * TIMER_SYSTICK_PER_10MS) / 10);
  _virtualTimeBaseEnable(ENABLE);

  return retVal;
}

/**
  * @brief Starts a one-shot virtual timer for the given absolute timeout value
  *        expressed in internal system time units.
  * @param timerHandle: The virtual timer
  * @param time: Absolute time expressed in STU.
  * @retval 0 if the timerHandle is valid.
  * @retval 1 if the timerHandle is not valid. It is already started.
  */
uint32_t HAL_RADIO_TIMER_StartVirtualTimerSysTime(VTIMER_HandleType *timerHandle, uint64_t time)
{
  uint8_t retVal;
  retVal = _start_timer(timerHandle, time);
  _virtualTimeBaseEnable(ENABLE);

  return retVal;
}

/**
  * @brief  Stops the one-shot virtual timer specified if found
  * @param  timerHandle: The virtual timer
  * @retval None
  */
void HAL_RADIO_TIMER_StopVirtualTimer(VTIMER_HandleType *timerHandle)
{
  VTIMER_HandleType *rootNode = _remove_timer_in_queue(RADIO_TIMER_Context.rootNode, timerHandle);
  uint8_t expired = 0;
  timerHandle->active = FALSE;
  if (RADIO_TIMER_Context.rootNode != rootNode)
  {
    RADIO_TIMER_Context.rootNode = _update_user_timeout(rootNode, &expired);
    if (expired)
    {
      /* A new root timer is already expired, mimic timer expire */
      INCREMENT_EXPIRE_COUNT;
    }
  }
  else
  {
    RADIO_TIMER_Context.rootNode = rootNode;
  }
}

/**
  * @brief Returns the absolute expiry time of a running virtual timer expressed in internal system time units.
  * @param timerHandle: The virtual timer
  * @retval sysTime: Absolute time expressed in internal system time units.
  */
uint64_t HAL_RADIO_TIMER_ExpiryTime(VTIMER_HandleType *timerHandle)
{
  return timerHandle->expiryTime;
}

#if defined (STM32WB06) || defined (STM32WB07)
/**
  * @brief   If the wakeup timer triggers for a host wakeup, a pending radio activity is programmed.
  *          If the wakeup timer triggers for a radio activity, a pending virtual timer callback is executed.
  * @retval  None
  */
void HAL_RADIO_TIMER_WakeUpCallback(void)
{
  volatile uint32_t status = 0;
  uint8_t expired;
  UNUSED(status);
  _check_radio_activity(&RADIO_TIMER_Context.radioTimer, &expired);
  if (RADIO_TIMER_Context.hostIsRadioPending)
  {
    RADIO_TIMER_Context.hostIsRadioPending = 0;
    HAL_RADIO_TIMER_TimeoutCallback();
  }

  LL_RADIO_TIMER_ClearFlag_BLEWakeup(WAKEUP);
  status = LL_RADIO_TIMER_IsActiveFlag_BLEWakeup(WAKEUP);
}
#endif

/**
  * @brief  Virtual timer Timeout Callback. It signals that a host timeout occurred.
  * @retval None
  */
void HAL_RADIO_TIMER_TimeoutCallback(void)
{
  volatile uint32_t status = 0;
  UNUSED(status);
#if defined (STM32WB06) || defined (STM32WB07)
  RADIO_TIMER_Context.hostIsRadioPending = 0;
#endif

  /* Disable host timer */
  LL_RADIO_TIMER_DisableCPUWakeupTimer(WAKEUP);
  INCREMENT_EXPIRE_COUNT_ISR;
  /* Clear the interrupt */
  LL_RADIO_TIMER_ClearFlag_CPUWakeup(WAKEUP);
  status = LL_RADIO_TIMER_IsActiveFlag_CPUWakeup(WAKEUP);
}

/**
  * @brief  Returns the number of timers in the queue.
  * @return number of timers in the queue.
  */
uint32_t HAL_RADIO_TIMER_GetPendingTimers(void)
{
  VTIMER_HandleType *curr = RADIO_TIMER_Context.rootNode;
  uint32_t counter = 0;
  while (curr != NULL)
  {
    counter++;
    curr = curr->next;
  }
  return counter;
}

/**
  * @brief   Returns the 64-bit system time, referred to the 32-bit system time parameter.
  *          The returned system time refers to a time between last calibration and last
  *          calibration + 10485 seconds.
  * @param   sys_time: system time
  * @warning The system time cannot be more then 10485 seconds (174 min) after the last calibration time.
  * @return  STU value
  */
uint64_t HAL_RADIO_TIMER_GetSysTime64(uint32_t sys_time)
{
  uint64_t time;

  time = RADIO_TIMER_Context.calibrationData.last_calibration_time + (uint32_t)(sys_time - (uint32_t)RADIO_TIMER_Context.calibrationData.last_calibration_time);

  return time;
}

/**
  * @brief   Returns the next 64-bit system time in the future, referred to the 32-bit system time parameter.
  *          Compared to HAL_RADIO_TIMER_GetSysTime64() this function makes sure that the returned
  *          time is always in the future, but execution time of the function is longer.
  * @param   sys_time: system time in the future (no more than 10485 s = 174 min in the future)
  * @return  STU value
  */
uint64_t HAL_RADIO_TIMER_GetFutureSysTime64(uint32_t sys_time)
{
  uint64_t current_time;
  uint32_t sysTime_ms32b;

  current_time = HAL_RADIO_TIMER_GetCurrentSysTime();
  sysTime_ms32b = current_time >> 32; /* Most significant 32 bits of sysTime64 */

  if (sys_time < (uint32_t)current_time)
  {
    /* Need to get most signicant 32 bits of current time increased by one */
    sysTime_ms32b++;
  }

  return sys_time | (((uint64_t)sysTime_ms32b) << 32);
}

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup RADIO_TIMER_Private_Functions  RADIO TIMER Private Functions
  * @{
  */

static void _calibrationProcedure(void)
{
  /* Make sure any pending calibration is over */
  while (LL_RADIO_TIMER_IsActiveFlag_LSICalibrationEnded(RADIO_CTRL) == 0);

  /* Set SLOW_COUNT to 23, that is calibrate over 24 clock periods, this number
  cannot be changed without changing all the integer maths function in the
  file  */
  LL_RADIO_TIMER_SetLSIWindowCalibrationLength(RADIO_CTRL, 23);

  /* Start a calibration and take the correct freq */
  _timer_calibrate(&RADIO_TIMER_Context.calibrationData);
  /* For first time set last to current */
  RADIO_TIMER_Context.calibrationData.last_period1 = RADIO_TIMER_Context.calibrationData.period1;

}

static void _timer_start_calibration(void)
{
  /* Clear any pending interrupt */
  LL_RADIO_TIMER_ClearFlag_LSICalibrationEnded(RADIO_CTRL);
  /* Start calibration */
  LL_RADIO_TIMER_StartLSICalibration(RADIO_CTRL);
}

static void _timer_calibrate(CalibrationDataTypeDef *calibrationData)
{
  _timer_start_calibration();
  while (LL_RADIO_TIMER_IsActiveFlag_LSICalibrationEnded(RADIO_CTRL) == 0);
  _get_calibration_data(calibrationData);
}

static void _get_calibration_data(CalibrationDataTypeDef *calibrationData)
{
  int32_t period;
  int32_t freq;
  int32_t mul1;
  int32_t b1;
  int32_t b2;
  int32_t mult;
  int32_t a1;
  int32_t a2;

  period =  LL_RADIO_TIMER_GetLSIPeriod(RADIO_CTRL);
  while (period != LL_RADIO_TIMER_GetLSIPeriod(RADIO_CTRL) || period == 0)
  {
    period = LL_RADIO_TIMER_GetLSIPeriod(RADIO_CTRL);
  }

  mul1 = 0x8BCF6 ;
  b1 = period >> 8 ;
  b2 = period & 0xff ;
  calibrationData->period1 = ((mul1 * b1) + ((b2 * mul1) >> 8) + 16) >> 5;
  calibrationData->period = period;

  mult = 0x753 ;
  freq = LL_RADIO_TIMER_GetLSIFrequency(RADIO_CTRL);

  while (freq != LL_RADIO_TIMER_GetLSIFrequency(RADIO_CTRL) || freq == 0)
  {
    freq = LL_RADIO_TIMER_GetLSIFrequency(RADIO_CTRL);
  }
  a1 = freq >> 6 ;
  a2 = a1 * mult ;
  calibrationData->freq1 = (a2 + 128) >> 8 ;
  calibrationData->freq = freq;
}

static void _configureTxRxDelay(RADIO_TIMER_ContextTypeDef *context, uint8_t calculate_st)
{
  uint8_t tx_delay_start;

  tx_delay_start = (BLUEGLOB->TXDELAYSTART * 125 / 1000) + 1;

  BLUEGLOB->WAKEUPINITDELAY =  blue_unit_conversion(WAKEUP_INIT_DELAY, context->calibrationData.freq1, MULT64_THR_FREQ);
  context->TxRxDelay.tim12_delay_mt = _us_to_machinetime(BLUEGLOB->TIMER12INITDELAYCAL);
  context->TxRxDelay.tx_cal_delay = _us_to_machinetime(BLUEGLOB->TRANSMITCALDELAYCHK + tx_delay_start);
  context->TxRxDelay.tx_no_cal_delay = _us_to_machinetime(BLUEGLOB->TRANSMITNOCALDELAYCHK + tx_delay_start);
  context->TxRxDelay.rx_cal_delay = _us_to_machinetime(BLUEGLOB->RECEIVECALDELAYCHK);
  context->TxRxDelay.rx_no_cal_delay = _us_to_machinetime(BLUEGLOB->RECEIVENOCALDELAYCHK);

  if (calculate_st)
  {
    context->TxRxDelay.tx_cal_delay_st    = _us_to_systime(BLUEGLOB->TRANSMITCALDELAYCHK + tx_delay_start) + WAKEUP_INIT_DELAY;
  }

}

static uint32_t _us_to_systime(uint32_t time)
{
  uint32_t t1, t2;
  t1 = time * 0x68;
  t2 = time * 0xDB;
  return (t1 >> 8) + (t2 >> 16);
}

static uint32_t _us_to_machinetime(uint32_t time)
{
  uint64_t tmp = (uint64_t)RADIO_TIMER_Context.calibrationData.freq * (uint64_t)time * (uint64_t)3U;
  uint32_t time_mt = ((tmp + (1 << 26)) >> 27) & TIMER_MAX_VALUE;

  return time_mt;
}

static void _update_xtal_startup_time(uint16_t hs_startup_time, int32_t freq1)
{
  int32_t time1;

  time1 = blue_unit_conversion(hs_startup_time, freq1, MULT64_THR_FREQ);
  if (time1 >= 4096)
  {
    time1 = 4095;
  }
  if (time1 < 16)
  {
    time1 = 16;
  }
  LL_RADIO_TIMER_SetWakeupOffset(WAKEUP, (time1 >> 4));
}

static void _calibration_callback(void *handle)
{
  if(RADIO_TIMER_Context.calibrationSettings.calibration_in_progress == FALSE)
  {
    if (RADIO_TIMER_Context.calibrationSettings.periodicCalibration)
    {
      _timer_start_calibration();
    }
    RADIO_TIMER_Context.calibrationSettings.calibration_in_progress = TRUE;
  }
  _start_timer(&RADIO_TIMER_Context.calibrationTimer, HAL_RADIO_TIMER_GetCurrentSysTime() + RADIO_TIMER_Context.calibrationSettings.periodicCalibrationCheckDuration);
}

static int32_t _start_timer(VTIMER_HandleType *timerHandle, uint64_t time)
{
  uint8_t expired = 0;

  /* The timer is already started*/
  if (timerHandle->active)
  {
    return 1;
  }
  timerHandle->expiryTime = time;
  timerHandle->active = TRUE;
  if (_insert_timer_in_queue(RADIO_TIMER_Context.rootNode, timerHandle) == timerHandle)
  {
    RADIO_TIMER_Context.rootNode = _update_user_timeout(timerHandle, &expired);
    if (expired)
    {
      /* A new root timer is already expired, mimic timer expire that is normally signaled
       through the interrupt handler that increase the number of expired timers*/
      INCREMENT_EXPIRE_COUNT;
    }
  }
  #if defined (STM32WB06) || defined (STM32WB07)
  else
  {
    _check_host_activity();
  }
  #endif

  return expired;
}

static uint64_t _get_system_time_and_machine(RADIO_TIMER_ContextTypeDef *context, uint32_t *current_machine_time)
{
  uint32_t difftime;
  uint64_t new_time;

  ATOMIC_SECTION_BEGIN();
  new_time = context->cumulative_time;
  *current_machine_time =  LL_RADIO_TIMER_GetAbsoluteTime(WAKEUP);
  difftime = TIME_ABSDIFF(*current_machine_time, context->last_machine_time);
  new_time += blue_unit_conversion(difftime, context->calibrationData.period1, MULT64_THR_PERIOD);
  if (new_time < context->last_system_time)
  {
    new_time += blue_unit_conversion(TIMER_MAX_VALUE, context->calibrationData.period1, MULT64_THR_PERIOD);
  }
  context->last_system_time = new_time;
  ATOMIC_SECTION_END();

  return new_time;
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
    if (curr->active)
    {
      ATOMIC_SECTION_BEGIN();
#if defined (STM32WB06) || defined (STM32WB07)
      uint8_t dummy;
      bool share = FALSE;
      _check_radio_activity(&RADIO_TIMER_Context.radioTimer, &dummy);
#endif
      delay = curr->expiryTime - HAL_RADIO_TIMER_GetCurrentSysTime();
      if (delay > 0)
      {
         /* Protection against interrupt must be used to avoid that the called function will be interrupted
          and so the timer programming will happen after the target time is already passed
          leading to a timer expiring after timer wraps, instead of the expected delay */
#if defined (STM32WB06) || defined (STM32WB07)
        /* Is the active radio operation before or too close the host timeout? */
        if (((RADIO_TIMER_Context.radioTimer.expiryTime) < (curr->expiryTime + RADIO_TIMER_Context.hostMargin))
            && RADIO_TIMER_Context.radioTimer.active)
        {
          if ((RADIO_TIMER_Context.radioTimer.expiryTime >= curr->expiryTime) && RADIO_TIMER_Context.radioTimer.active)
          {
            RADIO_TIMER_Context.hostIsRadioPending = 1;
          }
        }
        else
        {
          /* It's fine to program the wakeup timer for an host wakeup */
          share = TRUE;
        }
        TIMER_SetRadioHostWakeupTime(delay, &share);
        if (share == TRUE)
        {
          RADIO_TIMER_Context.radioTimer.pending |= RADIO_TIMER_Context.radioTimer.active;
          RADIO_TIMER_Context.radioTimer.active = FALSE;
        }
#else
        VTIMER_SetWakeupTime(delay, TRUE);
#endif
      }
      else
      {
        *expired = 1;
      }
      ATOMIC_SECTION_END();
      break;
    }
    curr = curr->next;
  }
  if (*expired)
  {
    return rootOrig;
  }

  return curr;
}

#if defined (STM32WB05) || defined (STM32WB09)
static uint32_t VTIMER_SetWakeupTime(uint32_t delay, bool allow_sleep)
{
  uint32_t current_time;
  delay = blue_unit_conversion(delay, RADIO_TIMER_Context.calibrationData.freq1, MULT64_THR_FREQ) ;
  /* If the delay is too small round to minimum 2 tick */
  delay = MAX(32, delay);
  current_time = LL_RADIO_TIMER_GetAbsoluteTime(WAKEUP);
  /* 4 least significant bits are not taken into account. Then let's round the value */
  LL_RADIO_TIMER_SetCPUWakeupTime(WAKEUP, ((current_time + (delay + 8)) & TIMER_MAX_VALUE));
  LL_RADIO_TIMER_EnableWakeupTimerLowPowerMode(WAKEUP);
  LL_RADIO_TIMER_EnableCPUWakeupTimer(WAKEUP);

  return current_time;
}
#endif

static VTIMER_HandleType *_insert_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle)
{
  VTIMER_HandleType *current = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;

  while ((current != NULL) && (current->expiryTime < handle->expiryTime))
  {
    prev = current;
    current = current->next;
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
  if (state != DISABLE)
  {
    if (RADIO_TIMER_Context.enableTimeBase == FALSE)
    {
      _calibration_callback(&RADIO_TIMER_Context.calibrationTimer);
      RADIO_TIMER_Context.enableTimeBase = TRUE;
    }
  }
  else
  {
    HAL_RADIO_TIMER_StopVirtualTimer(&RADIO_TIMER_Context.calibrationTimer);
    RADIO_TIMER_Context.enableTimeBase = FALSE;
  }
}

static VTIMER_HandleType *_remove_timer_in_queue(VTIMER_HandleType *rootNode, VTIMER_HandleType *handle)
{
  VTIMER_HandleType *current = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;

  while ((current != NULL) && (current != handle))
  {
    prev = current;
    current = current->next;
  }

  if (current == NULL)
  {
    /* Not found */
  }
  else if (current == rootNode)
  {
    /* New root node */
    returnValue = current->next;
  }
  else
  {
    prev->next = current->next;
  }

  return returnValue;
}

/* Check the number of expired timer from rootNode (ordered list of timers) and return the list of expired timers */
static VTIMER_HandleType *_check_callbacks(VTIMER_HandleType *rootNode, VTIMER_HandleType **expiredList)
{

  VTIMER_HandleType *curr = rootNode;
  VTIMER_HandleType *prev = NULL;
  VTIMER_HandleType *returnValue = rootNode;
  *expiredList = rootNode;

  int64_t delay;
  uint32_t expiredCount = 0;

  while (curr != NULL)
  {

    if (curr->active)
    {
      delay = curr->expiryTime - HAL_RADIO_TIMER_GetCurrentSysTime();

      if (delay > 5)   /*TBR*/
      {
        /* End of expired timers list*/
        break;
      }
    }

    prev = curr;
    curr = curr->next;
    expiredCount++;
  }

  if (expiredCount)
  {
    /* Some timers expired */
    prev->next = NULL;
    returnValue = curr;
  }
  else
  {
    /* No timer expired */
    *expiredList = NULL;
  }

  return returnValue;
}

static void _updateCalibrationData(void)
{
  if (RADIO_TIMER_Context.calibrationSettings.periodicCalibration)
  {

    CalibrationDataTypeDef updatedCalibrationData;
    _get_calibration_data(&updatedCalibrationData);
    _update_xtal_startup_time(RADIO_TIMER_Context.hs_startup_time, updatedCalibrationData.freq1);

    ATOMIC_SECTION_BEGIN();
    RADIO_TIMER_Context.calibrationData.calibration_data_available = 1;
    RADIO_TIMER_Context.calibrationData.freq = updatedCalibrationData.freq;
    RADIO_TIMER_Context.calibrationData.freq1 = updatedCalibrationData.freq1;
    RADIO_TIMER_Context.calibrationData.period = updatedCalibrationData.period;
    RADIO_TIMER_Context.calibrationData.period1 = updatedCalibrationData.period1;
    _update_system_time(&RADIO_TIMER_Context);
    ATOMIC_SECTION_END();

    _configureTxRxDelay(&RADIO_TIMER_Context, FALSE);
  }
  else
  {
  ATOMIC_SECTION_BEGIN();
  _update_system_time(&RADIO_TIMER_Context);
  ATOMIC_SECTION_END();
  }
}

/* This function update the system time after a calibration.
 * If the user calls too often this function, you could have rounding issues in the integer maths.
 */
static void _update_system_time(RADIO_TIMER_ContextTypeDef *context)
{
  uint32_t current_machine_time;
  uint32_t period;

  current_machine_time = LL_RADIO_TIMER_GetAbsoluteTime(WAKEUP);
  period = context->calibrationData.last_period1;
  context->cumulative_time = context->calibrationData.last_calibration_time + \
                             blue_unit_conversion(TIME_ABSDIFF(current_machine_time,
                                                               context->last_machine_time),
                                                  period, MULT64_THR_PERIOD);

  if ((context->calibrationSettings.periodicCalibration == 0)
      && (TIME_ABSDIFF(current_machine_time,
                       context->last_machine_time) < context->calibrationData.calibration_machine_interval))
  {
    context->cumulative_time += blue_unit_conversion(TIMER_MAX_VALUE, period, MULT64_THR_PERIOD);
  }
  context->last_machine_time = current_machine_time;
  context->calibrationData.last_calibration_time = context->cumulative_time;
  context->calibrationData.last_period1 = context->calibrationData.period1;
}

/* Check if it is time to program the pending radio timer (large timeouts).
   1) The radio event is before the next calibration event. Then the timer must be programmed.
   2) The calibration timer expired but the calibration didn't start and the values not updated as expected.
      Then the next calibration event is misleading. The radio timer must be programmed.
   3) The radio event is after the next calibration event. Then the timer will be programmed with the latest values.
   The check on the next calibration event is made even though the calibration is disabled (max cal. interval)
   in order to avoid counter wrapping with timeouts far in the future.
*/
static void _check_radio_activity(RADIO_TIMER_RadioHandleTypeDef *timerHandle, uint8_t *expired)
{
  uint64_t nextCalibrationEvent, currentTime;
  *expired = 0;
  if (timerHandle->pending)
  {

    nextCalibrationEvent = RADIO_TIMER_Context.calibrationData.last_calibration_time + \
                           RADIO_TIMER_Context.calibrationSettings.periodicCalibrationInterval;

    ATOMIC_SECTION_BEGIN();
    currentTime = HAL_RADIO_TIMER_GetCurrentSysTime();
    if ((timerHandle->expiryTime < (nextCalibrationEvent + RADIO_ACTIVITY_MARGIN)) || \
        (currentTime > (nextCalibrationEvent + CALIB_SAFE_THR)))
    {
      if (timerHandle->expiryTime - TIMER1_INIT_DELAY > (currentTime + TIMER1_MARGIN))
      {
        *expired = TIMER_SetRadioTimerValue(timerHandle->expiryTime, timerHandle->event_type, timerHandle->cal_req);
        timerHandle->pending = FALSE; /* timer has been served. No more pending */
        timerHandle->active = TRUE; /* timer has been programmed and it becomes ACTIVE */
        timerHandle->intTxRx_to_be_served = TRUE;
      }
      else
      {

        RADIO_TIMER_Context.radioTimer.pending = FALSE;
        *expired = 1;

      }
    }
    else
    {

#if defined (STM32WB06) || defined (STM32WB07)
      RADIO_TIMER_Context.waitCal = 1;
#endif

    }
    ATOMIC_SECTION_END();

  }
}

#if defined (STM32WB06) || defined (STM32WB07)
/**
  * @brief   Set the wakeup time to the specified delay. The delay is converted in machine time and only 28 most significant bits
  *          are taken into account. The XTAL startup time is not taken into account for the wakeup, i.e. the system does not wait for
  *          the XTAL startup time parameter to trigger the interrupt. If is it possible the wakeup timer is programmed too.
  *          The delay is translated into machine time unit (MTU) and it is assigned to the wakeup register.
  * @param   delay: Delay from the current time expressed in system time unit (STU). Range is 0 to maximum value of STU.
  *          The maximum value STU is dependent on the speed of the low speed oscillator.
  *          A value too small will force the timer to wrap, so it is recommended to use at least 5-10 STU.
  * @param   share: flag that indicates if the wakeup timer has to be programmed too.
  *          if other code commands the system to go to deep sleep.
  * @warning The API must be called with interrupts disabled to avoid programming the timer with a value in the past.
  * @return  Current time in MTU.
  */
static uint32_t TIMER_SetRadioHostWakeupTime(uint32_t delay, bool *share)
{
  uint32_t current_time;

  delay = blue_unit_conversion(delay, RADIO_TIMER_Context.calibrationData.freq1, MULT64_THR_FREQ) ;
  /* If the delay is too small round to minimum 2 tick */
  delay = MAX(32, delay);
  current_time = LL_RADIO_TIMER_GetAbsoluteTime(WAKEUP);
  /* 4 least significant bits are not taken into account. Then let's round the value */
  LL_RADIO_TIMER_SetCPUWakeupTime(WAKEUP, ((current_time + (delay + 8)) & TIMER_MAX_VALUE));
  LL_RADIO_TIMER_EnableWakeupTimerLowPowerMode(WAKEUP);
  LL_RADIO_TIMER_EnableCPUWakeupTimer(WAKEUP);
  if ((LL_RADIO_TIMER_IsEnabledTimer1(BLUE) || LL_RADIO_TIMER_IsEnabledTimer2(BLUE) || (*share != TRUE)))
  {
    *share = FALSE;
    return current_time;
  }
  _set_controller_as_host();
  /* 4 least significant bits are not taken into account. Then let's round the value */
  LL_RADIO_TIMER_SetBLEWakeupTime(WAKEUP, ((current_time + delay + 8) & 0xFFFFFFF0));
  LL_RADIO_TIMER_SetSleepRequestMode(WAKEUP, 0);
  LL_RADIO_TIMER_EnableBLEWakeupTimer(WAKEUP);
  LL_RADIO_TIMER_EnableWakeupTimerLowPowerMode(WAKEUP);
  return current_time;
}

static void _set_controller_as_host(void)
{
  BLUEGLOB->BYTE4 &= ~(1 << 7);
  BLUEGLOB->BYTE22 = 0x0;
  BLUEGLOB->BYTE23 = 0x0;
}

static void _check_host_activity(void)
{
  uint8_t expired;
  RADIO_TIMER_Context.rootNode = _update_user_timeout(RADIO_TIMER_Context.rootNode, &expired);
  if (expired == 1)
  {
    /* A new root timer is already expired, mimic timer expire */
    INCREMENT_EXPIRE_COUNT_ISR;
  }
}
#endif

/**
  * @brief   Programs either the Wakeup timer or Timer1. Both timers are able to trigger the radio sequencer.
  *          Then, they are able to start a transmission or a reception according to the configured radio ram tables.
  *          Only the wakeup timer is able to let the device out from sleep.
  *          The wakeup timer is programmed if the anolag part has enough time to settle after the wakeup or not.
  *          The timeout passed as parameter represents the moment where the first bit must be transmitted or the
  *          receive window must be opened.
  *          Since the radio needs some time to setup, the final timeout programmed is compensated by certain
  *          time intervals according to the kind of operation (Tx or Rx), calibration request and programmed timer.
  *          The wakeup offset is compensated automatically by the hardware.
  *          The CPU wakes up at timeout minus wakeup_offset. if the wakeup timer is programmed, the BLE event triggers
  *          when the absolute time mathches the 28 MSB of the timeout. Otherwise the trigger event occurs considering all 32 bits.
  * @param   timeout: absolute starting time of the desired operation expressed in STU.
  *                   If this absolute time is less then the current time, the timer will wrap.
  *                   The maximum value STU is dependent on the speed of the low speed oscillator.
  * @param   event_type: 1 Tx event.
                         0 Rx event
  * @param   cal_req: 1 pll calibration is requested.
                     0 pll calibration is not requested.
  * @warning The API must be called with interrupts disabled to avoid programming the timer with a value in the past
  * @retval  0 if a correct timeout has been programmed in the timeout register
  * @retval  1 if a correct timeout cannot be programmed
  */
static uint8_t TIMER_SetRadioTimerValue(uint32_t timeout, bool event_type, bool cal_req)
{
  uint32_t current_time, delay, radio_init_delay, device_delay, rel_timeout, rel_timeout_mt;
  uint8_t ret_val;

  /*choose the 2nd init duration. Check the event_type and cal. request*/
  if (event_type == TX)
  {
    if (cal_req)
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.tx_cal_delay;
      device_delay = RADIO_TIMER_Context.TxRxDelay.tx_cal_delay_st;
    }
    else
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.tx_no_cal_delay;
      device_delay = RADIO_TIMER_Context.TxRxDelay.tx_cal_delay_st;
    }
  }
  else
  {
    if (cal_req)
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.rx_cal_delay;
      device_delay = RADIO_TIMER_Context.TxRxDelay.tx_cal_delay_st;
    }
    else
    {
      radio_init_delay = RADIO_TIMER_Context.TxRxDelay.rx_no_cal_delay;
      device_delay = RADIO_TIMER_Context.TxRxDelay.tx_cal_delay_st;
    }
  }

  /* At this point, it is care of the upper layers to guarantee that the timeout represents an absolute time in the future */
  rel_timeout = timeout - (uint32_t)_get_system_time_and_machine(&RADIO_TIMER_Context, &current_time);

  rel_timeout_mt =  blue_unit_conversion(rel_timeout, RADIO_TIMER_Context.calibrationData.freq1, MULT64_THR_FREQ);

  /*Check if the timeout is beyond the wakeup time offset. Then program either the WakeUp timer or the Timer1*/
  if (rel_timeout > (device_delay + RADIO_TIMER_Context.hs_startup_time + MARGIN_EXT))
  {
    /*The timeout is after the wakeup_time_offset, So it is ok to program the wakeup timer*/
    delay = rel_timeout_mt - BLUEGLOB->WAKEUPINITDELAY - radio_init_delay;
    LL_RADIO_TIMER_SetBLEWakeupTime(WAKEUP, ((current_time + delay) & TIMER_MAX_VALUE));
    LL_RADIO_TIMER_SetSleepRequestMode(WAKEUP, 0);
    LL_RADIO_TIMER_DisableTimer1(BLUE);
    LL_RADIO_TIMER_DisableTimer2(BLUE);
    LL_RADIO_TIMER_EnableBLEWakeupTimer(WAKEUP);
    LL_RADIO_TIMER_EnableWakeupTimerLowPowerMode(WAKEUP);
    radio_init_delay += BLUEGLOB->WAKEUPINITDELAY;
  }
  else
  {
    delay = rel_timeout_mt - RADIO_TIMER_Context.TxRxDelay.tim12_delay_mt - radio_init_delay;
    LL_RADIO_TIMER_SetTimeout(BLUE, ((current_time + delay) & TIMER_MAX_VALUE));
    LL_RADIO_TIMER_DisableBLEWakeupTimer(WAKEUP);
    LL_RADIO_TIMER_EnableTimer1(BLUE);
    radio_init_delay += RADIO_TIMER_Context.TxRxDelay.tim12_delay_mt;
  }

  RADIO_TIMER_Context.last_anchor_mt = (current_time + rel_timeout_mt) & TIMER_MAX_VALUE;

#if defined (STM32WB06) || defined (STM32WB07)
  BLUEGLOB->BYTE4 |= 1 << 7;
  BLUEGLOB->BYTE22 = 0xF0;
  BLUEGLOB->BYTE23 = 0xFF;
#endif

  /* Basic low level check with an extra margin of machine units */
  if ((delay + radio_init_delay) < (radio_init_delay + 5))
  {
    LL_RADIO_TIMER_DisableTimer1(BLUE);
    LL_RADIO_TIMER_DisableTimer2(BLUE);
    LL_RADIO_TIMER_DisableBLEWakeupTimer(WAKEUP);
    ret_val =  1;
  }
  else
  {
    RADIO_TIMER_Context.last_setup_time = blue_unit_conversion(radio_init_delay, RADIO_TIMER_Context.calibrationData.period1, MULT64_THR_PERIOD);
    ret_val = 0;
  }

  return ret_val;
}

/**
  * @brief   Return the system time referred to the absolute machine time passed as parameter and the current system time.
  * @param   time: Absolute machine time in the past
  * @param   current_system_time: Current System time
  * @warning User should guarantee that call to this function are performed in a non-interruptible context.
  * @return  STU value
  */
static uint64_t TIMER_GetPastSysTime(uint32_t time, uint64_t *current_system_time)
{
  uint32_t delta_systime, current_machine_time;

  *current_system_time = _get_system_time_and_machine(&RADIO_TIMER_Context, &current_machine_time);
  delta_systime = blue_unit_conversion(TIME_DIFF(current_machine_time, time), RADIO_TIMER_Context.calibrationData.period1, MULT64_THR_PERIOD);

  return (*current_system_time - delta_systime);
}

/**
  * @brief  Return the consensus of the Virtual timer management to go in sleep.
  * @retval TRUE if all vtimers have been served and the calibration procedure has already finished.
  * @retval FALSE if the vtimer Tick is still busy.
  */
static bool TIMER_SleepCheck(void)
{
  return ((RADIO_TIMER_Context.expired_count == RADIO_TIMER_Context.served_count) && (RADIO_TIMER_Context.calibrationSettings.calibration_in_progress == FALSE));
}

/**
  * @brief  Return the status of the Radio timers and the last value programmed in the register.
  * @note   When Timer2 is on schedule, the time is expressed in microseconds, otherwise in absolute machine time units.
  * @param  time: pointer to value which is going to have time value.
  * @retval 0 if no timer has been programmed.
  * @retval 1 if Timer1 has been programmed.
  * @retval 2 if Timer2 has been programmed.
  * @retval 3 if Wakeup Timer has been programmed.
  */
static uint8_t TIMER_GetRadioTimerValue(uint32_t *time)
{
  if (LL_RADIO_TIMER_IsEnabledBLEWakeupTimer(WAKEUP))
  {
    *time = LL_RADIO_TIMER_GetBLEWakeupTime(WAKEUP);
    return WAKEUP_RADIO_TIMER_BUSY;
  }
  else if (LL_RADIO_TIMER_IsEnabledTimer1(BLUE))
  {
    *time = LL_RADIO_TIMER_GetTimeout(BLUE);
    return RADIO_TIMER1_BUSY;
  }
  else if (LL_RADIO_TIMER_IsEnabledTimer2(BLUE))
  {
    *time = LL_RADIO_TIMER_GetTimeout(BLUE);
    return RADIO_TIMER2_BUSY;
  }
  else
  {
    return 0;
  }
}

__weak void HAL_RADIO_TIMER_CpuWakeUpCallback(void)
{
}


__weak void HAL_RADIO_TIMER_TxRxWakeUpCallback(void)
{
}

void HAL_RADIO_TIMER_CPU_WKUP_IRQHandler(void)
{
  HAL_RADIO_TIMER_TimeoutCallback();

  HAL_RADIO_TIMER_CpuWakeUpCallback();
}

void HAL_RADIO_TIMER_TXRX_WKUP_IRQHandler(void)
{
  HAL_RADIO_TIMER_TxRxWakeUpCallback();
#if defined (STM32WB06) || defined (STM32WB07)
  HAL_RADIO_TIMER_WakeUpCallback();
#endif
}

void HAL_RADIO_TIMER_ERROR_IRQHandler(void)
{
  volatile uint32_t debug_cmd = 0;
  UNUSED(debug_cmd);
  BLUE->DEBUGCMDREG |= 1;

  /* If the device is configured with
     System clock = 64 MHz and BLE clock = 16 MHz
     a register read is necessary to end fine
     the clear interrupt register operation,
     due the AHB down converter latency */
  debug_cmd = BLUE->DEBUGCMDREG;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
