/**
  ******************************************************************************
  * @file    clock.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide clock services for time purpose
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#include "backup.h"
#include "clock.h"
#include "stm32yyxx_ll_cortex.h"

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
  /* Ensure COUNTFLAG is reset by reading SysTick control and status register */
  LL_SYSTICK_IsActiveCounterFlag();
  uint32_t m = HAL_GetTick();
  const uint32_t tms = SysTick->LOAD + 1;
  __IO uint32_t u = tms - SysTick->VAL;
  if (LL_SYSTICK_IsActiveCounterFlag()) {
    m = HAL_GetTick();
    u = tms - SysTick->VAL;
  }
  return (m * 1000 + (u * 1000) / tms);
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
#ifdef STM32WBxx
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
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      Error_Handler();
    }
  }
}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
