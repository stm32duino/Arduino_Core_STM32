/**
  ******************************************************************************
  * @file    stm32wl3x_hal_pwr.c
  * @author  MCD Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Power Voltage Detector functions
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

/** @addtogroup PWR
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup PWR_Private_Defines
  * @{
  */

/**
  * @}
 */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions  PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group  Peripheral Control functions
  *  @brief Low Power modes configuration functions
  *
@verbatim

 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================

  ==============================================================================
                        ##### PWR peripheral overview #####
  ==============================================================================
  [..]
   (#) The Power control (PWR) provides an overview of the supply architecture
       for the different power domains and of the supply configuration
       controller.

   (#) Every entity has low power mode as described below :
   (#) The CPU low power modes are :
      (+) CPU CRun.
      (+) CPU Sleep WFI.
      (+) CPU DeepSleep.
   (#) The Core low power modes are :
      (+) Run.
      (+) Sleep.
      (+) DEEPSTOP with with retention and low speed clock enabled.
      (+) DEEPSTOP with with retention and low speed clock disabled.
      (+) Shutdown.

    [..]
     *** PVD configuration ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PVDLS[2:0] bits in PWR_CR2 register).
      (+) PVDO flag is available to indicate when VDD is lower
          than the PVD threshold. This event can generate an interrupt if enabled.
          This is done through  __HAL_PVD_ENABLE_IT() macro.
      (+) The PVD is stopped in Shutdown mode.

    *** Wake-up pin configuration ***
    =================================
    [..]
      (+) Wake-up pin is used to wake up the system from DEEPSTOP mode.
          The pin selection is configurable through the IEWU, EWUA and EWB
          registers to map signal to wake up pin line.
          The pin polarity is configurable through the IWUP, WUPA and WUPB
          registers to be active on rising or falling edges.

      (+) Refer the user manual to know which wake-up lines are present in the
          device family.

      (+) When a wakeup pin event is received the appropriate flag is set in
          the IWUF, WUFA and WUFB registers.
          Then the wakeup pin flag will be cleared and the IOs user
          callback will be called.
          The user can add his own code by customization of this function
          HAL_PWR_WKUPx_Callback.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector (PVD).
  * @param  sConfigPVD pointer to a PWR_PVDTypeDef structure that contains the PVD
  *         configuration information.
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage thresholds corresponding to each
  *         detection level.
  * @retval None
  */
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PVDLS bits according to PVDLevel value */
  LL_PWR_SetPVDLevel(sConfigPVD->PVDLevel);

  /* Clear any previous config. Keep it clear if IT mode is selected */
  __HAL_PWR_PVD_DISABLE_IT();

  /* Configure interrupt mode */
  if ((sConfigPVD->Mode & PWR_PVD_MODE_IT) == PWR_PVD_MODE_IT)
  {
    __HAL_PWR_PVD_ENABLE_IT();
  }

  return HAL_OK;
}

/**
  * @brief Enables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_EnablePVD(void)
{
  /* Enable the power voltage detector */
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief Disables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_DisablePVD(void)
{
  /* Disable the power voltage detector */
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  PWR PVD interrupt callback
  * @retval None
  */
__weak void HAL_PWR_PVDCallback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVDCallback can be implemented in the user file
  */
}

/**
  * @brief  Enable the wake up line functionality.
  * @note   Wake up lines are used to wake up the system from DEEPSTOP.
  *         The polarity is applied only for the IOs source line and the wakeup
  *         event are only edge detection, not level detection.
  * @param  WakeUpPort : Specifies which wake up IO port configure. This parameter
  *                      can be one value of @ref PWR_WAKEUP_SOURCE_PORT.
  * @param  WakeUpPin  : Specifies which wake up line to enable. This parameter
  *                      can be a combination of @ref PWR_WAKEUP_SOURCE define
  *                      group where every param select the wake up line
  * @param  WakeUpPolarity  : Specifies the polarity of the wake up pin source.
  *                      This parameter is applied only for the IOs source and
  *                      can be a value of @ref PWR_WAKEUP_POLARITY.
  * @retval None.
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPort, uint32_t WakeUpPin, uint32_t WakeUpPolarity)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_SOURCE(WakeUpPin));
  assert_param(IS_PWR_WAKEUP_POLARITY(WakeUpPolarity));

  /* Specifies the wake up line polarity for the event detection (rising or falling edge) */
  if (WakeUpPolarity == PWR_WUP_FALLEDG)
  {
    LL_PWR_SetWakeUpPinPolarityLow(WakeUpPort, WakeUpPin);
  }
  else
  {
    LL_PWR_SetWakeUpPinPolarityHigh(WakeUpPort, WakeUpPin);
  }
  /* Enable wake-up line */
  LL_PWR_EnableWakeUpPin(WakeUpPort, WakeUpPin);
}

/**
  * @brief  Disable the wake up line functionality.
  * @param  WakeUpPort : IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *                     @arg @ref  PWR_WAKEUP_PORTA
  *                     @arg @ref  PWR_WAKEUP_PORTB
  * @param  WakeUpPin : Specifies the wake up line to disable.
  *                     This parameter can be a combination of @ref PWR_WAKEUP_SOURCE define group
  * @retval None
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPort, uint32_t WakeUpPin)
{
  /* Reset the wake up line polarity to the default value */
  LL_PWR_SetWakeUpPinPolarityHigh(WakeUpPort, WakeUpPin);

  /* Disable wake-up line */
  LL_PWR_DisableWakeUpPin(WakeUpPort, WakeUpPin);
}

/**
  * @brief  Get and Clear Wake-up source.
  * @param  WakeUpPort : IO port to get out of DEEPSTOP mode. This parameter can be one of the following values:
  *                     @arg @ref  PWR_WAKEUP_PORTA
  *                     @arg @ref  PWR_WAKEUP_PORTB
  * @retval WakeUpPin : This parameter can be a combination of
  *                     @ref PWR_WAKEUP_SOURCE define group
  */
uint32_t HAL_PWR_GetClearWakeupSource(uint32_t WakeUpPort)
{
  uint32_t wakeuppin;

  /* Get all wake-up pins */
  wakeuppin = LL_PWR_GetWakeupSource(WakeUpPort);

  /* Clear all the wake-up pin flags */
  LL_PWR_ClearWakeupSource(WakeUpPort, wakeuppin);

  return wakeuppin;
}

/**
  * @brief  Enter the CPU in Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @note   CPU clock is off and all peripherals including Cortex-M0+ core such
  *         as NVIC and SysTick can run and wake up the CPU when an interrupt
  *         or an event occurs.
  * @retval None.
  */
void HAL_PWR_EnterSLEEPMode(void)
{
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Wait For Interrupt Request */
  __WFI();

}

/**
  * @brief  Configures the system to allow the DEEPSTOP mode.
  * @param  sConfigDEEPSTOP : Pointer to a @ref PWR_DEEPSTOPTypeDef structure that
  *                           contains the DEEPSTOP configuration information.
  * @retval None.
  */
HAL_StatusTypeDef HAL_PWR_ConfigDEEPSTOP(PWR_DEEPSTOPTypeDef *sConfigDEEPSTOP)
{
  /* Disable the low speed clock if requested */
  if (sConfigDEEPSTOP->deepStopMode == PWR_DEEPSTOP_WITH_SLOW_CLOCK_OFF)
  {
    LL_RCC_LSE_Disable();
    LL_RCC_LSI_Disable();
  }

  /* Enable the GPIO retention in DEEPSTOP configuration */
  LL_PWR_EnableGPIORET();

  /* Disable DIRECT HSE configuration to allow DEEPSTOP request */
  if (LL_RCC_DIRECT_HSE_IsEnabled())
  {
    LL_RCC_DIRECT_HSE_Disable();
  }

  /* Wait until  the low speed clock if OFF */
  if (sConfigDEEPSTOP->deepStopMode == PWR_DEEPSTOP_WITH_SLOW_CLOCK_OFF)
  {
    while (LL_RCC_LSE_IsReady() || LL_RCC_LSI_IsReady()) {}
  }

  return HAL_OK;
}

/**
  * @brief  Enter the whole system in DEEPSTOP mode.
  * @note   The DEEPSTOP is the only low power mode of the device allowing to
  *         restart from a saved context environment and go on running
  *         the application at wakeup.
  * @note   CPU clock and bus clocks are stopped, the VDD12i power domain is
  *         switched off, the VDD12o power domain is ON and supplied at 1.0V.
  *         All the RAM banks are retained (by configuration in SystemInit()).
  *         The slow clock can be running or stopped, depending on the software
  *         configuration.
  *         All the register content is lost. Only few peripheral can save
  *         the setting if configured like wake up source.
  * @retval None.
  */
void HAL_PWR_EnterDEEPSTOPMode(void)
{
  /* Clear all the wake-up pin flags */
  LL_PWR_ClearInternalWakeupSource(LL_PWR_WAKEUP_ALL);
  LL_PWR_ClearWakeupSource(PWR_WAKEUP_PORTA, LL_PWR_WAKEUP_ALL);
  LL_PWR_ClearWakeupSource(PWR_WAKEUP_PORTB, LL_PWR_WAKEUP_ALL);

  /* Enable the device DEEPSTOP configuration */
  MODIFY_REG_FIELD(PWR->CR1, PWR_CR1_LPMS, PWR_MODE_DEEPSTOP);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Wait for Interrupt Request to enter in DEEPSTOP */
  __WFI();
}

/**
  * @brief  Configures the system to allow the SHUTDOWN mode.
  * @param  sConfigSHUTDOWN : Pointer to a @ref PWR_SHUTDOWNTypeDef structure that
  *                           contains the SHUTDOWN configuration information.
  * @retval None.
  */
HAL_StatusTypeDef HAL_PWR_ConfigSHUTDOWN(PWR_SHUTDOWNTypeDef *sConfigSHUTDOWN)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_POLARITY(sConfigSHUTDOWN->WakeUpPol));

  /* BOR configuration during Shutdown mode */
  if (sConfigSHUTDOWN->BORStatus == ENABLE)
  {
    LL_PWR_EnableBORinSDN();
  }
  else
  {
    LL_PWR_DisableBORinSDN();
  }

  if (sConfigSHUTDOWN->WakeUpPinStatus == ENABLE)
  {
    LL_PWR_IOWakeupPolaritySDN(sConfigSHUTDOWN->WakeUpPol);
    LL_PWR_EnableIOWakeupSDN();
  }
  else
  {
    LL_PWR_DisableIOWakeupSDN();
  }

#if defined(PWR_CR2_GPIORET)
  /* Enable the GPIO retention in shutdown configuration */
  LL_PWR_EnableGPIORET();
#endif /* PWR_CR2_GPIORET */

  /* Disable DIRECT HSE configuration to allow shutdown request */
  if (LL_RCC_DIRECT_HSE_IsEnabled())
  {
    LL_RCC_DIRECT_HSE_Disable();
  }

  return HAL_OK;
}

/**
  * @brief  Indicate SLEEP-ON-EXIT feature when returning from handler mode to
  *         thread mode.
  * @note   Set SLEEPONEXIT bit of SCR register. When this bit is set, the
  *         processor re-enters Sleep mode when an interruption handling is over.
  *         Setting this bit is useful when the processor is expected to run
  *         only on interruptions handling.
  * @retval None.
  */
void HAL_PWR_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex-M0+ System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Disable SLEEP-ON-EXIT feature when returning from handler mode to
  *         thread mode.
  * @note   Clears SLEEPONEXIT bit of SCR register. When this bit is set, the
  *         processor re-enters Sleep mode when an interruption handling is over.
  * @retval None.
  */
void HAL_PWR_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex-M0+ System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Enable CORTEX SEV-ON-PEND feature.
  * @note   Sets SEVONPEND bit of SCR register. When this bit is set, any
  *         pending event / interrupt even if it's disabled or has insufficient
  *         priority to cause exception entry wakes up the Cortex-M0+.
  * @retval None.
  */
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex-M0+ System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Disable CORTEX SEVONPEND feature.
  * @note   Resets SEVONPEND bit of SCR register. When this bit is reset, only
  *         enabled pending causes exception entry wakes up the Cortex-M0+.
  * @retval None.
  */
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex-M0+ System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None.
  */
void HAL_PWR_PVD_IRQHandler(void)
{
  /* Check PWR flag */
  if (__HAL_PWR_PVD_GET_FLAG() != 0U)
  {
    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();

    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_CLEAR_FLAG();
  }
}

/**
  * @brief This function handles the PWR WAKEUP interrupt request.
  * @retval None.
  */
void HAL_PWR_WKUP_IRQHandler(void)
{
  uint32_t wakeuppin;

  /* IO Wakeup Source PortA */
  wakeuppin = LL_PWR_GetWakeupSource(LL_PWR_WAKEUP_PORTA);

  /* Wakeup pin line interrupt detected */
  if (wakeuppin != 0)
  {
    HAL_PWR_WKUPx_Callback(PWR_WAKEUP_PORTA, wakeuppin);
  }

  /* IO Wakeup Source PortB */
  wakeuppin = LL_PWR_GetWakeupSource(LL_PWR_WAKEUP_PORTB);

  /* Wakeup pin line interrupt detected */
  if (wakeuppin != 0)
  {
    HAL_PWR_WKUPx_Callback(PWR_WAKEUP_PORTB, wakeuppin);
  }

}

/**
  * @brief PWR WKUPx interrupt callback.
  * @param wakeupPort wakeup PORT
  * @param wakeupIOs IO wakeup line
  * @retval None.
  */
__weak void HAL_PWR_WKUPx_Callback(uint32_t wakeupPort, uint32_t wakeupIOs)

{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUPxCallback can be implemented in the user file
  */
}


/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_PWR_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
