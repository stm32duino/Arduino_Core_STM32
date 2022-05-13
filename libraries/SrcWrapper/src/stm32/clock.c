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
#include "backup.h"
#include "clock.h"
#include "lock_resource.h"
#include "otp.h"
#include "stm32yyxx_ll_cortex.h"
#include "stm32yyxx_ll_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  Function called to read the current micro second
  * @param  None
  * @retval None
  */
uint32_t getCurrentMicros(void)
{
  uint32_t m0 = HAL_GetTick();
  __IO uint32_t u0 = SysTick->VAL;
  uint32_t m1 = HAL_GetTick();
  __IO uint32_t u1 = SysTick->VAL;
  const uint32_t tms = SysTick->LOAD + 1;

  if (m1 != m0) {
    return (m1 * 1000 + ((tms - u1) * 1000) / tms);
  } else {
    return (m0 * 1000 + ((tms - u0) * 1000) / tms);
  }
}

/**
  * @brief  Function called wto read the current millisecond
  * @param  None
  * @retval None
  */
uint32_t getCurrentMillis(void)
{
  return HAL_GetTick();
}

void noOsSystickHandler()
{

}

void osSystickHandler() __attribute__((weak, alias("noOsSystickHandler")));
/**
  * @brief  Function called when the tick interruption falls
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  osSystickHandler();
}

/**
  * @brief  Enable the specified clock if not already set
  * @param  source: clock source: LSE_CLOCK, LSI_CLOCK, HSI_CLOCK or HSE_CLOCK
  * @retval None
  */
void enableClock(sourceClock_t source)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

#if defined(STM32MP1xx)
  /** Clock source selection is done by First Stage Boot Loader on Cortex A
   *  See variant.cpp for corresponding boards.
   */
  if (!IS_ENGINEERING_BOOT_MODE()) {
    return;
  }
#endif /* STM32MP1xx */

  enableBackupDomain();

  switch (source) {
    case LSI_CLOCK:
#ifdef RCC_FLAG_LSI1RDY
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_LSI1RDY) == RESET) {
        RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI1;
#else
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET) {
        RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI;
#endif
        RCC_OscInitStruct.LSIState = RCC_LSI_ON;
      }
      break;
    case HSI_CLOCK:
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET) {
        RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
#if defined(STM32MP1xx)
        RCC_OscInitStruct.HSICalibrationValue = 0x00;
#else
        RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
#endif
      }
      break;
    case LSE_CLOCK:
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET) {
#ifdef __HAL_RCC_LSEDRIVE_CONFIG
        __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
#endif
        RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSE;
        RCC_OscInitStruct.LSEState = RCC_LSE_ON;
      }
      break;
    case HSE_CLOCK:
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET) {
        RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
      }
      break;
    default:
      /* No valid clock to enable */
      break;
  }
  if (RCC_OscInitStruct.OscillatorType != RCC_OSCILLATORTYPE_NONE) {
    hsem_lock(CFG_HW_RCC_SEMID, HSEM_LOCK_DEFAULT_RETRY);
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      Error_Handler();
    }
    hsem_unlock(CFG_HW_RCC_SEMID);
  }
}

void configHSECapacitorTuning(void)
{
#if defined(OTP_AREA_BASE) && defined(STM32WBxx)
  OTP_BT_t *p_otp;
  /* Read HSE_Tuning from OTP with index 0 */
  p_otp = (OTP_BT_t *) OTP_Read(0);
  if ((p_otp) && (!LL_RCC_HSE_IsReady())) {
    LL_RCC_HSE_SetCapacitorTuning(p_otp->hse_tuning);
  }
#endif
}

/**
  * @brief  This function enables clocks for some system IP
  * @param  None
  * @retval None
  */
void configIPClock(void)
{
#ifdef HSEM_BASE
  __HAL_RCC_HSEM_CLK_ENABLE();
#endif

#if defined(__HAL_RCC_PWR_CLK_ENABLE)
  /* Enable PWR clock, needed for example: voltage scaling, low power ... */
  __HAL_RCC_PWR_CLK_ENABLE();
#endif

#if defined(__HAL_RCC_SYSCFG_CLK_ENABLE)
  /* Enable SYSCFG clock, needed for example: Pin remap or Analog switch ... */
  __HAL_RCC_SYSCFG_CLK_ENABLE();
#endif

#if defined(HAL_CRC_MODULE_ENABLED)
  /* Enable CRC clock, needed for example: MotionFX Library ... */
#if defined(__HAL_RCC_CRC2_CLK_ENABLE)
  __HAL_RCC_CRC2_CLK_ENABLE();
#elif defined(__HAL_RCC_CRC_CLK_ENABLE)
  __HAL_RCC_CRC_CLK_ENABLE();
#endif
#endif
}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
