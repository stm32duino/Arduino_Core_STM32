/**
  ******************************************************************************
  * @file    stm32wb0x_ll_radio_timer.h
  * @author  GPM WBL Application Team
  * @brief   Radio Timer LL module
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
#ifndef STM32WB0x_LL_RADIO_TIMER_H
#define STM32WB0x_LL_RADIO_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

/** @addtogroup RADIO_TIMER_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup RADIO_TIMER_LL_TIMERS Radio & Wakeup Timer definitions
  * @{
  */
#define LL_RADIO_BLE_WAKEUP_TIMER    0x00000000U
#define LL_RADIO_CPU_WAKEUP_TIMER    0x00000001U
#define LL_RADIO_TIMER_1             0x00000002U
#define LL_RADIO_TIMER_2             0x00000003U
/**
  * @}
  */

/** @defgroup RADIO_TIMER_LL_TIMERS_FLAG Flag Defines
  * @{
  */
#define LL_RADIO_TIMECAPTURETRIGF BLUE_STATUSREG_TIMECAPTURETRIG
/**
  * @}
  */

/** @defgroup RADIO_TIMER_LL_TIMERS_INT Interrupt Defines
  * @{
  */
#define LL_RADIO_BLE_WAKEUP_IT WAKEUP_WAKEUP_BLE_IRQ_ENABLE_WAKEUP_IT
#define LL_RADIO_CPU_WAKEUP_IT WAKEUP_WAKEUP_CM0_IRQ_ENABLE_WAKEUP_IT
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup RADIO_TIMER_LL_Exported_Functions Radio Timer Exported Functions
  * @{
  */

/** @defgroup RADIO_TIMER_LL_EF_Radio_Timer_Configuration Radio Timer configuration
  * @{
  */

/**
  * @brief  Enable Radio Timer1.
  * @rmtoll TIMEOUTDESTREG    DESTINATION   LL_RADIO_TIMER_EnableTimer1
  * @param  BLUEx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableTimer1(BLUE_TypeDef *BLUEx)
{
  MODIFY_REG_FIELD(BLUEx->TIMEOUTDESTREG, BLUE_TIMEOUTDESTREG_DESTINATION, LL_RADIO_TIMER_1);
}

/**
  * @brief  Disable Radio Timer1.
  * @rmtoll TIMEOUTDESTREG   DESTINATION   LL_RADIO_TIMER_DisableTimer1
  * @param  BLUEx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableTimer1(BLUE_TypeDef *BLUEx)
{
  MODIFY_REG_FIELD(BLUEx->TIMEOUTDESTREG, BLUE_TIMEOUTDESTREG_DESTINATION, 0);
}

/**
  * @brief  Indicates if Radio Timer1 is enabled.
  * @rmtoll TIMEOUTDESTREG   DESTINATION   LL_RADIO_TIMER_IsEnabledTimer1
  * @param  BLUEx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledTimer1(BLUE_TypeDef *BLUEx)
{
  return ((READ_BIT(BLUEx->TIMEOUTDESTREG, BLUE_TIMEOUTDESTREG_DESTINATION) == (LL_RADIO_TIMER_1)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Radio Timer2.
  * @rmtoll TIMEOUTDESTREG    DESTINATION   LL_RADIO_TIMER_EnableTimer2
  * @param  BLUEx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableTimer2(BLUE_TypeDef *BLUEx)
{
  MODIFY_REG_FIELD(BLUEx->TIMEOUTDESTREG, BLUE_TIMEOUTDESTREG_DESTINATION, LL_RADIO_TIMER_2);
}

/**
  * @brief  Disable Radio Timer2.
  * @rmtoll TIMEOUTDESTREG   DESTINATION   LL_RADIO_TIMER_DisableTimer2
  * @param  BLUEx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableTimer2(BLUE_TypeDef *BLUEx)
{
  MODIFY_REG_FIELD(BLUEx->TIMEOUTDESTREG, BLUE_TIMEOUTDESTREG_DESTINATION, 0);
}

/**
  * @brief  Indicates if Radio Timer2 is enabled.
  * @rmtoll TIMEOUTDESTREG   DESTINATION   LL_RADIO_TIMER_IsEnabledTimer2
  * @param  BLUEx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledTimer2(BLUE_TypeDef *BLUEx)
{
  return ((READ_BIT(BLUEx->TIMEOUTDESTREG, BLUE_TIMEOUTDESTREG_DESTINATION) == (LL_RADIO_TIMER_2)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Radio Timer Timeout. Time units in microseconds for Timer2
  *         or in periods of 512 kHz clock for Timer1 (Interpolated Time).
  * @param  BLUEx Radio Timer instance
  * @param  timeout
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_SetTimeout(BLUE_TypeDef *BLUEx, uint32_t timeout)
{
  WRITE_REG(BLUEx->TIMEOUTREG, timeout);
}

/**
  * @brief  Get the Radio Timer Timeout. Time units in microseconds for Timer2
  *         or in periods of 512 kHz clock for Timer1 (Interpolated Time).
  * @param  BLUEx Radio Timer instance
  * @retval Timeout configured
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetTimeout(BLUE_TypeDef *BLUEx)
{
  return (uint32_t)(READ_REG(BLUEx->TIMEOUTREG));
}

/**
  * @brief  Get the Radio Timer value from the beginning of a new Bluetooth LE sequence.
  *         The granularity is the interpolated absolute time.
  * @param  BLUEx Radio Timer instance
  * @retval Time from the beginning of a new BLE sequence
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetTimerCapture(BLUE_TypeDef *BLUEx)
{
  return (uint32_t)(READ_REG(BLUEx->TIMERCAPTUREREG));
}

/**
  * @}
  */

/** @defgroup RADIO_TIMER_LL_EF_Wakeup_Timer_Configuration Radio Wakeup Timer configuration
  * @{
  */

/**
  * @brief  Enable Radio BLE Wakeup Timer.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    BLE_WAKEUP_EN   LL_RADIO_TIMER_EnableBLEWakeupTimer
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableBLEWakeupTimer(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_BLE_WAKEUP_EN);
}

/**
  * @brief  Disable Radio BLE Wakeup Timer.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    BLE_WAKEUP_EN   LL_RADIO_TIMER_DisableBLEWakeupTimer
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableBLEWakeupTimer(WAKEUP_TypeDef *WAKEUPx)
{
  CLEAR_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_BLE_WAKEUP_EN);
}

/**
  * @brief  Indicates if BLE Wakeup Timer is enabled.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    BLE_WAKEUP_EN   LL_RADIO_TIMER_IsEnabledBLEWakeupTimer
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledBLEWakeupTimer(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_BLE_WAKEUP_EN) == (WAKEUP_BLUE_SLEEP_REQUEST_MODE_BLE_WAKEUP_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Radio CPU Wakeup Timer.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    CPU_WAKEUP_EN   LL_RADIO_TIMER_EnableCPUWakeupTimer
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableCPUWakeupTimer(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN);
}

/**
  * @brief  Disable Radio CPU Wakeup Timer.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    CPU_WAKEUP_EN   LL_RADIO_TIMER_DisableCPUWakeupTimer
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableCPUWakeupTimer(WAKEUP_TypeDef *WAKEUPx)
{
  CLEAR_BIT(WAKEUPx->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN);
}

/**
  * @brief  Indicates if CPU Wakeup Timer is enabled.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    CPU_WAKEUP_EN   LL_RADIO_TIMER_IsEnabledCPUWakeupTimer
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledCPUWakeupTimer(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN) == (WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wakeup Offset to let time to power and clocks to settle (Granularity slow clock period).
  * @param  WAKEUPx Radio Timer instance
  * @param  Time Time in slow clock period
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_SetWakeupOffset(WAKEUP_TypeDef *WAKEUPx, uint8_t Time)
{
  WRITE_REG(WAKEUPx->WAKEUP_OFFSET[0], (Time & 0xFF));
}

/**
  * @brief  Get the Wakeup Offset (Granularity slow clock period).
  * @param  WAKEUPx Radio Timer instance
  * @retval Wakeup Time Offset (Granulary slow clock period, size 8 bit)
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetWakeupOffset(WAKEUP_TypeDef *WAKEUPx)
{
  return (uint32_t)(READ_REG(WAKEUPx->WAKEUP_OFFSET[0] & 0xFF));
}

/**
  * @brief  Set the BLE Wakeup Time (Granularity unit is in 16 x slow clock period).
  * @param  WAKEUPx Radio Timer instance
  * @param  Time in 16 x slow clock period
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_SetBLEWakeupTime(WAKEUP_TypeDef *WAKEUPx, uint32_t Time)
{
  WRITE_REG(WAKEUPx->BLUE_WAKEUP_TIME, Time);
}

/**
  * @brief  Get the BLE Wakeup Time (Granularity unit is 16 x slow clock period).
  * @param  WAKEUPx Radio Timer instance
  * @retval BLE Wakeup Time
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetBLEWakeupTime(WAKEUP_TypeDef *WAKEUPx)
{
  return (uint32_t)(READ_REG(WAKEUPx->BLUE_WAKEUP_TIME));
}

/**
  * @brief  Set the CPU Wakeup Time (Granularity unit is slow clock period).
  *         Only the first 28 MSB bit are considered.
  * @param  WAKEUPx Radio Timer instance
  * @param  Time in slow clock period
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_SetCPUWakeupTime(WAKEUP_TypeDef *WAKEUPx, uint32_t Time)
{
  WRITE_REG(WAKEUPx->CM0_WAKEUP_TIME, Time);
}

/**
  * @brief  Get the CPU Wakeup Time (Granularity unit is slow clock period).
  * @param  WAKEUPx Radio Timer instance
  * @retval CPU Wakeup Time
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetCPUWakeupTime(WAKEUP_TypeDef *WAKEUPx)
{
  return (uint32_t)(READ_REG(WAKEUPx->CM0_WAKEUP_TIME));
}

/**
  * @brief  Get the Absolute Time of the wakeup timer (Granularity unit is 16 x slow clock period).
  * @param  WAKEUPx Radio Timer instance
  * @retval Absolute Time of Wakeup Timer
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetAbsoluteTime(WAKEUP_TypeDef *WAKEUPx)
{
  return (uint32_t)(READ_REG(WAKEUPx->ABSOLUTE_TIME));
}

/**
  * @}
  */


/** @defgroup RADIO_TIMER_LL_EF_Low_Power_Timer_Configuration Radio Timer Low Power configuration
  * @{
  */

/**
  * @brief  Enable the Low Power Mode for the Wakeup Radio Timers.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    SLEEP_EN   LL_RADIO_TIMER_EnableWakeupTimerLowPowerMode
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableWakeupTimerLowPowerMode(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN);
}

/**
  * @brief  Disable the Low Power Mode for the Wakeup Radio Timers.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    SLEEP_EN   LL_RADIO_TIMER_DisableWakeupTimerLowPowerMode
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableWakeupTimerLowPowerMode(WAKEUP_TypeDef *WAKEUPx)
{
  CLEAR_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN);
}

/**
  * @brief  Indicates if Wakeup Radio Timer Low Power Mode is enabled.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    SLEEP_EN   LL_RADIO_TIMER_IsEnabledWakeupTimerLowPowerMode
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledWakeupTimerLowPowerMode(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN) == (WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the SoC to go in low power mode always whatever is the radio status.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    FORCE_SLEEPING   LL_RADIO_TIMER_EnableBLEWakeupTimerForceSleeping
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableBLEWakeupTimerForceSleeping(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_FORCE_SLEEPING);
}

/**
  * @brief  Disable the SoC to go in low power mode always.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    FORCE_SLEEPING   LL_RADIO_TIMER_DisableBLEWakeupTimerForceSleeping
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableBLEWakeupTimerForceSleeping(WAKEUP_TypeDef *WAKEUPx)
{
  CLEAR_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_FORCE_SLEEPING);
}

/**
  * @brief  Indicates if BLUE Wakeup Radio Timer Force Sleeping Mode is enabled.
  * @rmtoll BLUE_SLEEP_REQUEST_MODE    FORCE_SLEEPING   LL_RADIO_TIMER_IsEnabledBLEWakeupTimerForceSleeping
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledBLEWakeupTimerForceSleeping(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_FORCE_SLEEPING) == (WAKEUP_BLUE_SLEEP_REQUEST_MODE_FORCE_SLEEPING)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the CPU to be considered always as sleeping by the wakeup block.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    FORCE_SLEEPING   LL_RADIO_TIMER_EnableCPUWakeupTimerForceSleeping
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableCPUWakeupTimerForceSleeping(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_FORCE_SLEEPING);
}

/**
  * @brief  Disable the CPU to be considered always as sleeping by the wakeup block.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    FORCE_SLEEPING   LL_RADIO_TIMER_DisableCPUWakeupTimerForceSleeping
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableCPUWakeupTimerForceSleeping(WAKEUP_TypeDef *WAKEUPx)
{
  CLEAR_BIT(WAKEUPx->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_FORCE_SLEEPING);
}

/**
  * @brief  Indicates if CPU Wakeup Radio Timer Force Sleeping Mode is enabled.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    FORCE_SLEEPING   LL_RADIO_TIMER_IsEnabledCPUWakeupTimerForceSleeping
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledCPUWakeupTimerForceSleeping(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_FORCE_SLEEPING) == (WAKEUP_CM0_SLEEP_REQUEST_MODE_FORCE_SLEEPING)) ? 1UL : 0UL);
}

/**
  * @brief  Set the sleep request mode.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    SLEEP_REQ_MODE   LL_RADIO_TIMER_SetSleepRequestMode
  * @param  WAKEUPx Radio Timer instance
  * @param  mode Sleep mode value in range 0-7
  * @retval None.
  */
__STATIC_INLINE void LL_RADIO_TIMER_SetSleepRequestMode(WAKEUP_TypeDef *WAKEUPx, uint8_t mode)
{
#if defined(STM32WB09)
  return;
#else
  MODIFY_REG_FIELD(WAKEUP->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_REQ_MODE, (mode & 0x7));
#endif
}

/**
  * @brief  Get the sleep request mode.
  * @rmtoll CM0_SLEEP_REQUEST_MODE    SLEEP_REQ_MODE   LL_RADIO_TIMER_GetSleepRequestMode
  * @param  WAKEUPx Radio Timer instance
  * @retval Sleep mode value in range 0-7
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetSleepRequestMode(WAKEUP_TypeDef *WAKEUPx)
{
#if defined(STM32WB09)
  return 0;
#else
  return (uint32_t)(READ_REG(WAKEUP->BLUE_SLEEP_REQUEST_MODE) & WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_REQ_MODE);
#endif
}

/**
  * @}
  */

/** @defgroup RADIO_TIMER_LL_EF_IT_Management IT-Management
  * @{
  */

/**
  * @brief  Enable the BLE wakeup interrupt towards the CPU.
  * @rmtoll WAKEUP_BLE_IRQ_ENABLE    WAKEUP_IT   LL_RADIO_TIMER_EnableBLEWakeupIT
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableBLEWakeupIT(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->WAKEUP_BLE_IRQ_ENABLE, WAKEUP_WAKEUP_BLE_IRQ_ENABLE_WAKEUP_IT);
}

/**
  * @brief  Disable the BLE wakeup interrupt towards the CPU.
  * @rmtoll WAKEUP_BLE_IRQ_ENABLE    WAKEUP_IT   LL_RADIO_TIMER_DisableBLEWakeupIT
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableBLEWakeupIT(WAKEUP_TypeDef *WAKEUPx)
{
  CLEAR_BIT(WAKEUPx->WAKEUP_BLE_IRQ_ENABLE, WAKEUP_WAKEUP_BLE_IRQ_ENABLE_WAKEUP_IT);
}

/**
  * @brief  Indicates if BLE wakeup interrupt towards the CPU is enabled.
  * @rmtoll WAKEUP_BLE_IRQ_ENABLE    WAKEUP_IT   LL_RADIO_TIMER_IsEnabledBLEWakeupIT
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledBLEWakeupIT(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->WAKEUP_BLE_IRQ_ENABLE, WAKEUP_WAKEUP_BLE_IRQ_ENABLE_WAKEUP_IT) == (WAKEUP_WAKEUP_BLE_IRQ_ENABLE_WAKEUP_IT)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the CPU wakeup interrupt towards the CPU.
  * @rmtoll WAKEUP_CM0_IRQ_ENABLE    WAKEUP_IT   LL_RADIO_TIMER_EnableCPUWakeupIT
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableCPUWakeupIT(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->WAKEUP_CM0_IRQ_ENABLE, WAKEUP_WAKEUP_CM0_IRQ_ENABLE_WAKEUP_IT);
}

/**
  * @brief  Disable the CPU wakeup interrupt towards the CPU.
  * @rmtoll WAKEUP_CM0_IRQ_ENABLE    WAKEUP_IT   LL_RADIO_TIMER_DisableCPUWakeupIT
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableCPUWakeupIT(WAKEUP_TypeDef *WAKEUPx)
{
  CLEAR_BIT(WAKEUPx->WAKEUP_CM0_IRQ_ENABLE, WAKEUP_WAKEUP_CM0_IRQ_ENABLE_WAKEUP_IT);
}

/**
  * @brief  Indicates if CPU wakeup interrupt towards the CPU is enabled.
  * @rmtoll WAKEUP_CPU_IRQ_ENABLE    WAKEUP_IT   LL_RADIO_TIMER_IsEnabledCPUWakeupIT
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledCPUWakeupIT(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->WAKEUP_CM0_IRQ_ENABLE, WAKEUP_WAKEUP_CM0_IRQ_ENABLE_WAKEUP_IT) == (WAKEUP_WAKEUP_CM0_IRQ_ENABLE_WAKEUP_IT)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RADIO_TIMER_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check if the Radio Timer Time Capture Triggert Flag is set or not
  * @rmtoll STATUSREG    TIMECAPTURETRIG    LL_RADIO_TIMER_IsActiveFlag_TIMECAPTURETRIG
  * @param  BLEx BLE Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsActiveFlag_TIMECAPTURETRIG(BLUE_TypeDef *BLEx)
{
  return ((READ_BIT(BLEx->STATUSREG, BLUE_STATUSREG_TIMECAPTURETRIG) == (BLUE_STATUSREG_TIMECAPTURETRIG)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the BLE Wakeup interrupt flag.
  * @rmtoll WAKEUP_BLE_IRQ_STATUS   WAKEUP_IT   LL_RADIO_TIMER_ClearFlag_BLEWakeup
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_ClearFlag_BLEWakeup(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->WAKEUP_BLE_IRQ_STATUS, WAKEUP_WAKEUP_BLE_IRQ_STATUS_WAKEUP_IT);
}

/**
  * @brief  Indicate whether the BLE Wakeup interrupt flag is set
  * @rmtoll WAKEUP_BLE_IRQ_STATUS   WAKEUP_IT   LL_RADIO_TIMER_IsActiveFlag_BLEWakeup
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsActiveFlag_BLEWakeup(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->WAKEUP_BLE_IRQ_STATUS, WAKEUP_WAKEUP_BLE_IRQ_STATUS_WAKEUP_IT) == (WAKEUP_WAKEUP_BLE_IRQ_STATUS_WAKEUP_IT)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CPU Wakeup interrupt flag.
  * @rmtoll WAKEUP_CM0_IRQ_STATUS   WAKEUP_IT   LL_RADIO_TIMER_ClearFlag_CPUWakeup
  * @param  WAKEUPx Radio Timer instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_ClearFlag_CPUWakeup(WAKEUP_TypeDef *WAKEUPx)
{
  SET_BIT(WAKEUPx->WAKEUP_CM0_IRQ_STATUS, WAKEUP_WAKEUP_CM0_IRQ_STATUS_WAKEUP_IT);
}

/**
  * @brief  Indicate whether the CPU Wakeup interrupt flag is set
  * @rmtoll WAKEUP_CM0_IRQ_STATUS   WAKEUP_IT   LL_RADIO_TIMER_IsActiveFlag_CPUWakeup
  * @param  WAKEUPx Radio Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsActiveFlag_CPUWakeup(WAKEUP_TypeDef *WAKEUPx)
{
  return ((READ_BIT(WAKEUPx->WAKEUP_CM0_IRQ_STATUS, WAKEUP_WAKEUP_CM0_IRQ_STATUS_WAKEUP_IT) == (WAKEUP_WAKEUP_CM0_IRQ_STATUS_WAKEUP_IT)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RADIO_TIMER_LL_EF_LSI_CALIBRATION Radio Timer LSI calibration APIs
  * @{
  */

/**
  * @brief  Set the window length (in slow clock period) for slow clock measurement.
  * @param RADIO_CTRLx: Radio Control instance
  * @param  Count Slow clock is measured in a window of SLOW_COUNT+1 slow clock cycles
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_SetLSIWindowCalibrationLength(RADIO_CTRL_TypeDef *RADIO_CTRLx, uint32_t Count)
{
  WRITE_REG(RADIO_CTRLx->CLK32COUNT_REG, Count);
}

/**
  * @brief  Get the window length (in slow clock period) for slow clock measurement.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval The LSI Window Length used for the LSI calibration procedure
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetLSIWindowCalibrationLength(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  return (uint32_t)(READ_REG(RADIO_CTRLx->CLK32COUNT_REG));
}

/**
  * @brief  Start the LSI calibration procedure.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_StartLSICalibration(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  WRITE_REG(RADIO_CTRLx->CLK32PERIOD_REG, 0);
}

/**
  * @brief  Get the LSI clock Period calibrated.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval The LSI clock period calibrated
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetLSIPeriod(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  return (uint32_t)(READ_REG(RADIO_CTRLx->CLK32PERIOD_REG));
}

/**
  * @brief  Get the LSI clock Frequency calibrated.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval The LSI clock frequency calibrated
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_GetLSIFrequency(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  return (uint32_t)(READ_REG(RADIO_CTRLx->CLK32FREQUENCY_REG));
}

/**
  * @brief  Enable the LSI calibration ended interrupt.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_EnableLSICalibrationIT(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  SET_BIT(RADIO_CTRLx->RADIO_CONTROL_IRQ_ENABLE, RADIO_CTRL_RADIO_CONTROL_IRQ_ENABLE_SLOW_CLK_IRQ_MASK);
}

/**
  * @brief  Disable the LSI calibration ended interrupt.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_DisableLSICalibrationEndedIT(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  CLEAR_BIT(RADIO_CTRLx->RADIO_CONTROL_IRQ_ENABLE, RADIO_CTRL_RADIO_CONTROL_IRQ_ENABLE_SLOW_CLK_IRQ_MASK);
}

/**
  * @brief  Indicates if the LSI calibration ended interrupt is enabled.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsEnabledLSICalibrationEndedIT(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  return ((READ_BIT(RADIO_CTRLx->RADIO_CONTROL_IRQ_ENABLE, RADIO_CTRL_RADIO_CONTROL_IRQ_ENABLE_SLOW_CLK_IRQ_MASK) == (RADIO_CTRL_RADIO_CONTROL_IRQ_ENABLE_SLOW_CLK_IRQ_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the LSI calibration ended flag.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TIMER_ClearFlag_LSICalibrationEnded(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  SET_BIT(RADIO_CTRLx->RADIO_CONTROL_IRQ_STATUS, RADIO_CTRL_RADIO_CONTROL_IRQ_STATUS_SLOW_CLK_IRQ);
}

/**
  * @brief  Check if the LSI calibration ended flag is set or not.
  * @param RADIO_CTRLx: Radio Control instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TIMER_IsActiveFlag_LSICalibrationEnded(RADIO_CTRL_TypeDef *RADIO_CTRLx)
{
  return ((READ_BIT(RADIO_CTRLx->RADIO_CONTROL_IRQ_STATUS, RADIO_CTRL_RADIO_CONTROL_IRQ_STATUS_SLOW_CLK_IRQ) == (RADIO_CTRL_RADIO_CONTROL_IRQ_STATUS_SLOW_CLK_IRQ)) ? 1UL : 0UL);
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WB0x_LL_RADIO_TIMER_H */
