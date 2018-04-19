/**
  ******************************************************************************
  * @file    LowPower.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    17 - November -2017
  * @brief   Provides a Low Power interface
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

#include "Arduino.h"
#include "LowPower.h"

#ifdef HAL_PWR_MODULE_ENABLED

#ifdef __cplusplus
 extern "C" {
#endif

// NOTE: is these pins are common to a MCU family?
/* Wakeup pins list. Allow to know which pins can be used as wake up pin in
standby or shutdown mode */
#if defined(STM32L053xx)
const PinMap PinMap_WKUP[] = {
    {PA_0,  NP,  1},  //WKUP1
    {PC_13, NP,  2},  //WKUP2
    {NC,    NP,  0}
};
#elif defined(STM32L476xx)
const PinMap PinMap_WKUP[] = {
    {PA_0,  NP,  1},  //WKUP1
    {PC_13, NP,  2},  //WKUP2
    {PE_6,  NP,  3},  //WKUP3
    {PA_2,  NP,  4},  //WKUP4
    {PC_5,  NP,  5},  //WKUP5
    {NC,    NP,  0}
};
#endif

// Save UART handler for callback
static UART_HandleTypeDef* WakeUpUart = NULL;
// Save callback pointer
static void (*WakeUpUartCb)( void ) = NULL;

/**
  * @brief  Initialize low power mode
  * @param  None
  * @retval None
  */
void LowPower_init(){
  /* Enable Power Clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* Ensure that HSI is wake-up system clock */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);

  /* Check if the system was resumed from StandBy mode */
  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
  {
    /* Clear Standby flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
  }

  /* Clear all related wakeup flags */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
}

/**
  * @brief  Configure a pin as wakeup source if compatible.
  * @param  pin: pin to configure
  * @param  mode: pin mode (edge or state). The configuration have to be compatible.
  * @retval None
  */
void LowPower_EnableWakeUpPin(uint32_t pin, uint32_t mode) {
#ifndef STM32L4xx
  UNUSED(mode);
#endif
  PinName p = digitalPinToPinName(pin);
  uint32_t wupPin = pinmap_find_function(p, PinMap_WKUP);
  switch (wupPin) {
#ifdef PWR_WAKEUP_PIN1
    case 1 :
    #ifdef STM32L4xx
      if (mode == RISING) {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1_HIGH);
      }
      else {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1_LOW);
      }
    #else
      HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
    #endif
      break;
#endif //PWR_WAKEUP_PIN1
#ifdef PWR_WAKEUP_PIN2
    case 2 :
    #ifdef STM32L4xx
      if (mode == RISING) {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2_HIGH);
      }
      else {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2_LOW);
      }
    #else
      HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2);
    #endif
      break;
#endif //PWR_WAKEUP_PIN2
#ifdef PWR_WAKEUP_PIN3
    case 3 :
    #ifdef STM32L4xx
      if (mode == RISING) {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN3_HIGH);
      }
      else {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN3_LOW);
      }
    #else
      HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN3);
    #endif
      break;
#endif //PWR_WAKEUP_PIN3
#ifdef PWR_WAKEUP_PIN4
    case 4 :
    #ifdef STM32L4xx
      if (mode == RISING) {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4_HIGH);
      }
      else {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4_LOW);
      }
    #else
      HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4);
    #endif
      break;
#endif //PWR_WAKEUP_PIN4
#ifdef PWR_WAKEUP_PIN5
    case 5 :
    #ifdef STM32L4xx
      if (mode == RISING) {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN5_HIGH);
      }
      else {
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN5_LOW);
      }
    #else
      HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN5);
    #endif
      break;
#endif //PWR_WAKEUP_PIN5
    default :
      break;
  }
}

/**
  * @brief  Enable the sleep mode.
  * @param  None
  * @retval None
  */
void LowPower_sleep(uint32_t regulator){
  __disable_irq();
  /*Suspend Tick increment to prevent wakeup by Systick interrupt.
    Otherwise the Systick interrupt will wake up the device within 1ms (HAL time base)*/
  HAL_SuspendTick();

  /* Enter Sleep Mode , wake up is done once User push-button is pressed */
  HAL_PWR_EnterSLEEPMode(regulator, PWR_SLEEPENTRY_WFI);

  /* Resume Tick interrupt if disabled prior to SLEEP mode entry */
  HAL_ResumeTick();
  __enable_irq();

  if (WakeUpUartCb != NULL) {
    WakeUpUartCb();
  }
}

/**
  * @brief  Enable the stop mode.
  * @param  None
  * @retval None
  */
void LowPower_stop(){
  __disable_irq();

#if STM32L4xx
  if (WakeUpUart != NULL) {
    HAL_UARTEx_EnableStopMode(WakeUpUart);
  }
#endif

#ifdef STM32L0xx
  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();

  /* Enable the fast wake up from Ultra low power mode */
  HAL_PWREx_EnableFastWakeUp();

  /* Select HSI as system clock source after Wake Up from Stop mode */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
#endif

  // Enter Stop mode
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

  // Exit Stop mode reset clocks
  SystemClock_Config();
  __enable_irq();

#if STM32L4xx
  if (WakeUpUart != NULL) {
    HAL_UARTEx_DisableStopMode(WakeUpUart);

    if (WakeUpUartCb != NULL) {
      WakeUpUartCb();
    }
  }
#endif
}

/**
  * @brief  Enable the standby mode. The board reset when leaves this mode.
  * @param  None
  * @retval None
  */
void LowPower_standby(){
  __disable_irq();

#ifdef STM32L0xx
  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();

  /* Enable the fast wake up from Ultra low power mode */
  HAL_PWREx_EnableFastWakeUp();
#endif

  HAL_PWR_EnterSTANDBYMode();
}

/**
  * @brief  Enable the shutdown mode.The board reset when leaves this mode.
  *         If shutdown mode not available, use standby mode instead.
  * @param  None
  * @retval None
  */
void LowPower_shutdown(){
  __disable_irq();
#ifdef STM32L4xx
  // LSE must be on to use shutdown mode
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == SET) {
    HAL_PWREx_EnterSHUTDOWNMode();
  } else {
    LowPower_standby();
  }
#else
  LowPower_standby();
#endif
}

/**
  * @brief  Configure the UART as a wakeup source. A callback can be called when
  *         the chip leaves the low power mode. See board datasheet to check
  *         with which low power mode the UART is compatible.
  * @param  serial: pointer to serial
  * @param  FuncPtr: pointer to callback
  * @retval None
  */
void LowPower_EnableWakeUpUart(serial_t* serial, void (*FuncPtr)( void ) ) {
  UART_WakeUpTypeDef WakeUpSelection;

  // Save Uart handler
  WakeUpUart = &(serial->handle);

  // Save callback
  WakeUpUartCb = FuncPtr;

  /* make sure that no UART transfer is on-going */
  while(__HAL_UART_GET_FLAG(WakeUpUart, USART_ISR_BUSY) == SET);
  /* make sure that UART is ready to receive
   * (test carried out again later in HAL_UARTEx_StopModeWakeUpSourceConfig) */
  while(__HAL_UART_GET_FLAG(WakeUpUart, USART_ISR_REACK) == RESET);

  /* set the wake-up event:
   * specify wake-up on RXNE flag */
  WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_READDATA_NONEMPTY;
  HAL_UARTEx_StopModeWakeUpSourceConfig(WakeUpUart, WakeUpSelection);

  /* Enable the UART Wake UP from STOP1 mode Interrupt */
  __HAL_UART_ENABLE_IT(WakeUpUart, UART_IT_WUF);
}

#ifdef __cplusplus
}
#endif

#endif // HAL_PWR_MODULE_ENABLED

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
