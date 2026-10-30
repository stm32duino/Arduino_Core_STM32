/*
 *******************************************************************************
 * Copyright (c) 2016-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CLOCK_H
#define __CLOCK_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Clock source selection */
/**
 * @brief Clock source selection
 */
typedef enum {
  LSI_CLOCK,
  HSI_CLOCK,
  LSE_CLOCK,
  HSE_CLOCK
} sourceClock_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
 * @brief Returns the time elapsed since startup, in milliseconds.
 * @return Milliseconds since startup, from the HAL tick. Wraps after about
 *         49.7 days.
 */
uint32_t getCurrentMillis(void);

/**
 * @brief Returns the time elapsed since startup, in microseconds.
 * @return Microseconds since startup, refined with the SysTick counter.
 *         Wraps after about 71.6 minutes.
 */
uint32_t getCurrentMicros(void);

/**
 * @brief Enables the clocks of the system IPs (HSEM, PWR, SYSCFG, CRC) used
 *        by the core.
 */
void configIPClock(void);

/**
 * @brief Enables the specified clock source if it is not already ready.
 * @param source Clock source to enable: LSE_CLOCK, LSI_CLOCK, HSI_CLOCK or HSE_CLOCK.
 * @note The backup domain is enabled first. Error_Handler() is called on
 *       failure.
 *       On STM32MP1xx the clock is only configured in engineering boot mode.
 */
void enableClock(sourceClock_t source);

/**
 * @brief Applies the HSE capacitor tuning value stored in OTP.
 * @note Only effective on STM32WB series when HSE is not already ready.
 */
void configHSECapacitorTuning(void);

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
