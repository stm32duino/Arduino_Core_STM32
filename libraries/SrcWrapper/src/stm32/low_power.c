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
#include "low_power.h"

#if defined(HAL_PWR_MODULE_ENABLED) && !defined(HAL_PWR_MODULE_ONLY)

#ifdef __cplusplus
extern "C" {
#endif

#if defined(UART_IT_WUF) && defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
/* Save UART handler for callback */
static UART_HandleTypeDef *WakeUpUart = NULL;
#endif
/* Save callback pointer */
static void (*WakeUpUartCb)(void) = NULL;

#ifdef STM32G0xx
#define PWR_FLAG_WU PWR_FLAG_WUF
#endif

/**
  * @brief  Initialize low power mode
  * @param  None
  * @retval None
  */
void LowPower_init()
{
#if !defined(STM32H7xx) && !defined(STM32MP1xx) && !defined(STM32WBxx)
  /* Enable Power Clock */
  __HAL_RCC_PWR_CLK_ENABLE();
#endif
  /* Allow access to Backup domain */
  HAL_PWR_EnableBkUpAccess();

#ifdef __HAL_RCC_WAKEUPSTOP_CLK_CONFIG
  /* Ensure that HSI is wake-up system clock */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
#endif
  /* Check if the system was resumed from StandBy mode */
  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET) {
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
void LowPower_EnableWakeUpPin(uint32_t pin, uint32_t mode)
{
#if !defined(PWR_WAKEUP_PIN1_HIGH)
  UNUSED(mode);
#endif
  uint32_t wkup_pin;
  PinName p = digitalPinToPinName(pin);
  if (p != NC) {
    switch (p) {
      default :
#ifdef PWR_WAKEUP_PIN1
      case SYS_WKUP1 :
        wkup_pin = PWR_WAKEUP_PIN1;
#ifdef PWR_WAKEUP_PIN1_HIGH
        if (mode != RISING) {
          wkup_pin = PWR_WAKEUP_PIN1_LOW;
        }
#endif
        break;
#endif /* PWR_WAKEUP_PIN1 */
#ifdef PWR_WAKEUP_PIN2
      case SYS_WKUP2 :
        wkup_pin = PWR_WAKEUP_PIN2;
#ifdef PWR_WAKEUP_PIN2_HIGH
        if (mode != RISING) {
          wkup_pin = PWR_WAKEUP_PIN2_LOW;
        }
#endif
        break;
#endif /* PWR_WAKEUP_PIN2 */
#ifdef PWR_WAKEUP_PIN3
      case SYS_WKUP3 :
        wkup_pin = PWR_WAKEUP_PIN3;
#ifdef PWR_WAKEUP_PIN3_HIGH
        if (mode != RISING) {
          wkup_pin = PWR_WAKEUP_PIN3_LOW;
        }
#endif
        break;
#endif /* PWR_WAKEUP_PIN3 */
#ifdef PWR_WAKEUP_PIN4
      case SYS_WKUP4 :
        wkup_pin = PWR_WAKEUP_PIN4;
#ifdef PWR_WAKEUP_PIN4_HIGH
        if (mode != RISING) {
          wkup_pin = PWR_WAKEUP_PIN4_LOW;
        }
#endif
        break;
#endif /* PWR_WAKEUP_PIN4 */
#ifdef PWR_WAKEUP_PIN5
      case SYS_WKUP5 :
        wkup_pin = PWR_WAKEUP_PIN5;
#ifdef PWR_WAKEUP_PIN5_HIGH
        if (mode != RISING) {
          wkup_pin = PWR_WAKEUP_PIN5_LOW;
        }
#endif
        break;
#endif /* PWR_WAKEUP_PIN5 */
#ifdef PWR_WAKEUP_PIN6
      case SYS_WKUP6 :
        wkup_pin = PWR_WAKEUP_PIN6;
#ifdef PWR_WAKEUP_PIN6_HIGH
        if (mode != RISING) {
          wkup_pin = PWR_WAKEUP_PIN6_LOW;
        }
#endif
        break;
#endif /* PWR_WAKEUP_PIN6 */
#ifdef PWR_WAKEUP_PIN7
      case SYS_WKUP7 :
        wkup_pin = PWR_WAKEUP_PIN7;
        break;
#endif /* PWR_WAKEUP_PIN7 */
#ifdef PWR_WAKEUP_PIN8
      case SYS_WKUP8 :
        wkup_pin = PWR_WAKEUP_PIN8;
        break;
#endif /* PWR_WAKEUP_PIN8 */
    }
    HAL_PWR_EnableWakeUpPin(wkup_pin);
  }
}

/**
  * @brief  Enable the sleep mode.
  * @param  None
  * @retval None
  */
void LowPower_sleep(uint32_t regulator)
{
  /*
   * Suspend Tick increment to prevent wakeup by Systick interrupt.
   * Otherwise the Systick interrupt will wake up the device within
   * 1ms (HAL time base)
   */
  HAL_SuspendTick();

  /* Enter Sleep Mode , wake up is done once User push-button is pressed */
  HAL_PWR_EnterSLEEPMode(regulator, PWR_SLEEPENTRY_WFI);

  /* Resume Tick interrupt if disabled prior to SLEEP mode entry */
  HAL_ResumeTick();

  if (WakeUpUartCb != NULL) {
    WakeUpUartCb();
  }
}

/**
  * @brief  Enable the stop mode.
  * @param  obj : pointer to serial_t structure
  * @retval None
  */
void LowPower_stop(serial_t *obj)
{
  __disable_irq();

#if defined(UART_IT_WUF) && defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
  if (WakeUpUart != NULL) {
    HAL_UARTEx_EnableStopMode(WakeUpUart);
  }
#endif

#if defined(STM32L0xx) || defined(STM32L1xx)
  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();

  /* Enable the fast wake up from Ultra low power mode */
  HAL_PWREx_EnableFastWakeUp();
#endif
#ifdef __HAL_RCC_WAKEUPSTOP_CLK_CONFIG
  /* Select HSI as system clock source after Wake Up from Stop mode */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
#endif

  /* Enter Stop mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* Exit Stop mode reset clocks */
  SystemClock_ConfigFromStop();
#if defined(UART_IT_WUF) && defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
  if (WakeUpUart != NULL) {
    /* In case of WakeUp from UART, reset its clock source to HSI */
    uart_config_lowpower(obj);
    HAL_UARTEx_DisableStopMode(WakeUpUart);
  }
#else
  UNUSED(obj);
#endif
  __enable_irq();

  HAL_Delay(10);

  if (WakeUpUartCb != NULL) {
    WakeUpUartCb();
  }
}

/**
  * @brief  Enable the standby mode. The board reset when leaves this mode.
  * @param  None
  * @retval None
  */
void LowPower_standby()
{
  __disable_irq();

#if defined(STM32L0xx) || defined(STM32L1xx)
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
void LowPower_shutdown()
{
  __disable_irq();
#ifdef STM32L4xx
  /* LSE must be on to use shutdown mode */
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == SET) {
    HAL_PWREx_EnterSHUTDOWNMode();
  } else
#endif
  {
    LowPower_standby();
  }
}

/**
  * @brief  Configure the UART as a wakeup source. A callback can be called when
  *         the chip leaves the low power mode. See board datasheet to check
  *         with which low power mode the UART is compatible.
  * Warning This function will change UART clock source to HSI
  * @param  serial: pointer to serial
  * @param  FuncPtr: pointer to callback
  * @retval None
  */
void LowPower_EnableWakeUpUart(serial_t *serial, void (*FuncPtr)(void))
{
#if defined(UART_IT_WUF) && defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
  UART_WakeUpTypeDef WakeUpSelection;
  if (serial == NULL) {
    return;
  }
  /* Save Uart handler and Serial object */
  WakeUpUart = &(serial->handle);

  /* make sure that no UART transfer is on-going */
  while (__HAL_UART_GET_FLAG(WakeUpUart, USART_ISR_BUSY) == SET);
  /* make sure that UART is ready to receive
   * (test carried out again later in HAL_UARTEx_StopModeWakeUpSourceConfig) */
  while (__HAL_UART_GET_FLAG(WakeUpUart, USART_ISR_REACK) == RESET);

  /* set the wake-up event:
   * specify wake-up on RXNE flag
   */
  WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_READDATA_NONEMPTY;
  HAL_UARTEx_StopModeWakeUpSourceConfig(WakeUpUart, WakeUpSelection);

  /* Enable the UART Wake UP from STOP1 mode Interrupt */
  __HAL_UART_ENABLE_IT(WakeUpUart, UART_IT_WUF);
#else
  UNUSED(serial);
#endif
  /* Save callback */
  WakeUpUartCb = FuncPtr;
}

/**
  * @brief  Configures system clock after wake-up from STOP
  * @note   Weaked function which can be redefined by user at the sketch level.
  *         By default, call 'SystemClock_Config()'.
  * @param  None
  * @retval None
  */
WEAK void SystemClock_ConfigFromStop(void)
{
  SystemClock_Config();
}

#ifdef __cplusplus
}
#endif

#endif /* HAL_PWR_MODULE_ENABLED  && !HAL_PWR_MODULE_ONLY */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
