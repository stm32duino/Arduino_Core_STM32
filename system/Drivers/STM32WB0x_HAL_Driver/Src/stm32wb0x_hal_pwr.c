/**
  ******************************************************************************
  * @file    stm32wb0x_hal_pwr.c
  * @author  MCD Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions
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

/** @addtogroup PWR
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions  PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Initialization and De-Initialization Functions
  * @brief    Initialization and De-Initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and De-Initialization Functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to deinitialize power peripheral.

@endverbatim
  * @{
  */
/**
  * @brief  Deinitialize the HAL PWR peripheral registers to their default reset
  *         values.
  * @note   This functionality is not available in this product.
  *         The prototype is kept just to maintain compatibility with other
  *         products.
  * @retval None.
  */
void HAL_PWR_DeInit(void)
{
}

/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2  Peripheral Control functions
  *  @brief Power Control functions
  *
@verbatim

 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================
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
      (+) PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event can generate an interrupt if enabled.
          This is done through  __HAL_PVD_ENABLE_IT() macro.
      (+) The PVD is stopped in Shutdown mode.

    *** WakeUp pin configuration ***
    ================================
    [..]
      (+) Wake-up pin is used to wake up the system from DEEPSTOP mode.
          The pin selection is configurable through the CR3 and CR6 registers to map
          signal to wake up pin line.
          The pin polarity is configurable through the CR4 and CR7 registers to be
          active on rising or falling edges.

      (+) When a wakeup pin event is received the appropriate flag is set in
          the SR1 and SR3 registers.
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
HAL_StatusTypeDef HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PVDLS bits according to PVDLevel value */
  MODIFY_REG(PWR->CR2, PWR_CR2_PVDLS, sConfigPVD->PVDLevel);

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
  * @brief Enable the WakeUp PINx functionality.
  * @param WakeUpPin Specifies which Wake-Up pin to enable.
  *        This parameter can be one of the following:
  *        @arg @ref PWR_WAKEUP_PA0
  *        @arg @ref PWR_WAKEUP_PA1
  *        @arg @ref PWR_WAKEUP_PA2
  *        @arg @ref PWR_WAKEUP_PA3
  *        @arg @ref PWR_WAKEUP_PA4 (*)
  *        @arg @ref PWR_WAKEUP_PA5 (*)
  *        @arg @ref PWR_WAKEUP_PA6 (*)
  *        @arg @ref PWR_WAKEUP_PA7 (*)
  *        @arg @ref PWR_WAKEUP_PA8
  *        @arg @ref PWR_WAKEUP_PA9
  *        @arg @ref PWR_WAKEUP_PA10
  *        @arg @ref PWR_WAKEUP_PA11
  *        @arg @ref PWR_WAKEUP_PA12 (*)
  *        @arg @ref PWR_WAKEUP_PA13 (*)
  *        @arg @ref PWR_WAKEUP_PA14 (*)
  *        @arg @ref PWR_WAKEUP_PA15 (*)
  *        @arg @ref PWR_WAKEUP_PB0
  *        @arg @ref PWR_WAKEUP_PB1
  *        @arg @ref PWR_WAKEUP_PB2
  *        @arg @ref PWR_WAKEUP_PB3
  *        @arg @ref PWR_WAKEUP_PB4
  *        @arg @ref PWR_WAKEUP_PB5
  *        @arg @ref PWR_WAKEUP_PB6
  *        @arg @ref PWR_WAKEUP_PB7
  *        @arg @ref PWR_WAKEUP_PB8 (*)
  *        @arg @ref PWR_WAKEUP_PB9 (*)
  *        @arg @ref PWR_WAKEUP_PB10 (*)
  *        @arg @ref PWR_WAKEUP_PB11 (*)
  *        @arg @ref PWR_WAKEUP_PB12 (**)
  *        @arg @ref PWR_WAKEUP_PB13 (**)
  *        @arg @ref PWR_WAKEUP_PB14 (**)
  *        @arg @ref PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  * @param WakeUpPolarity Specifies the polarity of the wake up pin source.
  *        This parameter can be one of the following:
  *        @arg @ref PWR_WUP_RISIEDG
  *        @arg @ref PWR_WUP_FALLEDG
  *
  * @retval None
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPin, uint32_t WakeUpPolarity)
{
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPin));
  assert_param(IS_PWR_WAKEUP_PIN_POLARITY(WakeUpPolarity));

  /* Specifies the wake up line polarity for the event detection (rising or falling edge) */
  if (WakeUpPolarity == PWR_WUP_FALLEDG)
  {
    SET_BIT(PWR->CR4, (WakeUpPin & 0x0000FFFF));
    SET_BIT(PWR->CR7, (WakeUpPin >> 16));
  }
  else
  {
    CLEAR_BIT(PWR->CR4, (WakeUpPin & 0x0000FFFF));
    CLEAR_BIT(PWR->CR7, (WakeUpPin >> 16));
  }
  /* Enable wake-up line */
  SET_BIT(PWR->CR3, (WakeUpPin & 0x0000FFFF));
  SET_BIT(PWR->CR6, (WakeUpPin >> 16));

}

/**
  * @brief Disable the WakeUp PINx functionality.
  * @param WakeUpPinx Specifies the Power Wake-Up pin to disable.
  *        This parameter can be one of the following:
  *        @arg @ref PWR_WAKEUP_PA0
  *        @arg @ref PWR_WAKEUP_PA1
  *        @arg @ref PWR_WAKEUP_PA2
  *        @arg @ref PWR_WAKEUP_PA3
  *        @arg @ref PWR_WAKEUP_PA4 (*)
  *        @arg @ref PWR_WAKEUP_PA5 (*)
  *        @arg @ref PWR_WAKEUP_PA6 (*)
  *        @arg @ref PWR_WAKEUP_PA7 (*)
  *        @arg @ref PWR_WAKEUP_PA8
  *        @arg @ref PWR_WAKEUP_PA9
  *        @arg @ref PWR_WAKEUP_PA10
  *        @arg @ref PWR_WAKEUP_PA11
  *        @arg @ref PWR_WAKEUP_PA12 (*)
  *        @arg @ref PWR_WAKEUP_PA13 (*)
  *        @arg @ref PWR_WAKEUP_PA14 (*)
  *        @arg @ref PWR_WAKEUP_PA15 (*)
  *        @arg @ref PWR_WAKEUP_PB0
  *        @arg @ref PWR_WAKEUP_PB1
  *        @arg @ref PWR_WAKEUP_PB2
  *        @arg @ref PWR_WAKEUP_PB3
  *        @arg @ref PWR_WAKEUP_PB4
  *        @arg @ref PWR_WAKEUP_PB5
  *        @arg @ref PWR_WAKEUP_PB6
  *        @arg @ref PWR_WAKEUP_PB7
  *        @arg @ref PWR_WAKEUP_PB8 (*)
  *        @arg @ref PWR_WAKEUP_PB9 (*)
  *        @arg @ref PWR_WAKEUP_PB10 (*)
  *        @arg @ref PWR_WAKEUP_PB11 (*)
  *        @arg @ref PWR_WAKEUP_PB12 (**)
  *        @arg @ref PWR_WAKEUP_PB13 (**)
  *        @arg @ref PWR_WAKEUP_PB14 (**)
  *        @arg @ref PWR_WAKEUP_PB15 (**)
  *        (*) available only on STM32WB06 and STM32WB07 devices
  *        (**) available only on STM32WB05 and STM32WB09 devices
  *
  * @retval None
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx)
{
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));
  CLEAR_BIT(PWR->CR3, (WakeUpPinx & 0x0000FFFF));
  CLEAR_BIT(PWR->CR6, (WakeUpPinx >> 16));

}

/**
  * @brief  Get and Clear Wake-up source.
  * @retval WakeUpPin : This parameter can be a combination of
  *                     @ref PWREx_WakeUp_Pins define group
  */
uint32_t HAL_PWR_GetClearWakeupSource(void)
{
  uint32_t wakeuppin;

  /* Get all wake-up pins */
  wakeuppin = LL_PWR_GetWakeupSource();

  /* Clear all the wake-up pin flags */
  LL_PWR_ClearWakeupSource(wakeuppin);

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
  uint8_t radio_disabled = FALSE;

  /* Disable the low speed clock if requested */
  if (sConfigDEEPSTOP->deepStopMode == PWR_DEEPSTOP_WITH_SLOW_CLOCK_OFF)
  {
    LL_RCC_LSE_Disable();
    LL_RCC_LSI_Disable();
  }

  /* If the radio IP is not used at all by the SoC (or not yet started), the
    following steps need to be done after any reset to allow DEEPSTOP mode */
  if (!LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_MRBLE))
  {
    radio_disabled = TRUE;
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_MRBLE);
  }
  if ((READ_BIT(WAKEUP->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN) == 0) &&
      (READ_BIT(WAKEUP->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN) == 0))
  {
    SET_BIT(WAKEUP->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_FORCE_SLEEPING);
  }
  if (radio_disabled)
  {
    LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_MRBLE);
  }

#if defined(PWR_CR2_GPIORET)
  /* Enable the GPIO retention in DEEPSTOP configuration */
  LL_PWR_EnableGPIORET();
#endif /* PWR_CR2_GPIORET */

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
  * @brief  Enter DEEPSTOP mode
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
  * @retval None
  */
void HAL_PWR_EnterDEEPSTOPMode(void)
{
  /* Clear all the wake-up pin flags */
  LL_PWR_ClearWakeupSource(LL_PWR_WAKEUP_ALL);
  /* Enable the device DEEPSTOP configuration */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_LOWPOWERMODE_STOP);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Request Wait For Interrupt */
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
  assert_param(IS_PWR_WAKEUP_PIN_POLARITY(sConfigSHUTDOWN->WakeUpPol));

  /* If the radio IP is not used at all by the SoC (or not yet started), the
    following steps need to be done after any reset to allow Shutdown mode */
  if (!LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_MRBLE))
  {
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_MRBLE);
  }
  if ((SET_BIT(WAKEUP->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_SLEEP_EN) == 0)  &&
      (READ_BIT(WAKEUP->CM0_SLEEP_REQUEST_MODE, WAKEUP_CM0_SLEEP_REQUEST_MODE_CPU_WAKEUP_EN) == 0))
  {
    SET_BIT(WAKEUP->BLUE_SLEEP_REQUEST_MODE, WAKEUP_BLUE_SLEEP_REQUEST_MODE_FORCE_SLEEPING);
  }

  /* BOR configuration during Shutdown mode */
  if (sConfigSHUTDOWN->BORStatus == ENABLE)
  {
    LL_PWR_EnableBORinSDN();
  }
  else
  {
    LL_PWR_DisableBORinSDN();
  }

#if defined(STM32WB09)
  if (sConfigSHUTDOWN->WakeUpPinStatus == ENABLE)
  {
    LL_PWR_IOWakeupPolaritySDN(sConfigSHUTDOWN->WakeUpPol);
    LL_PWR_EnableIOWakeupSDN();
  }
  else
  {
    LL_PWR_DisableIOWakeupSDN();
  }
#endif /* STM32WB09 */

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
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
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
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Enable Cortex Sev On Pending feature.
  * @note   Set SEVONPEND bit of SCR register. When this bit is set, enabled
  *         events and all interrupts, including disabled ones can wakeup
  *         processor from WFE.
  * @retval None
  */
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}


/**
  * @brief  Disable Cortex Sev On Pending feature.
  * @note   Clear SEVONPEND bit of SCR register. When this bit is clear, only
  *         enable interrupts or events can wakeup processor from WFE
  * @retval None
  */
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
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
  * @brief This function handles the PWR WAKEUP interrupt request.
  * @note   This API should be called under the WKUP_IRQHandler().
  * @retval None.
  */
void HAL_PWR_WKUP_IRQHandler(void)
{
  uint32_t wakeuppin;

  wakeuppin = HAL_PWR_GetClearWakeupSource();

  /* Wakeup pin line interrupt detected */
  if (wakeuppin != 0U)
  {
    HAL_PWR_WKUPx_Callback(wakeuppin);
  }
}

/**
  * @brief PWR WKUPx interrupt callback.
  * @param WakeupIOs IO wakeup line
  * @retval None.
  */
__weak void HAL_PWR_WKUPx_Callback(uint32_t WakeupIOs)
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
