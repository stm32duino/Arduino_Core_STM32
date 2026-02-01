/**
  ******************************************************************************
  * @file    stm32u3xx_hal_pwr.c
  * @author  GPM Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Initialization/De-Initialization Functions.
  *           + Peripheral Control Functions.
  *           + PWR Attributes Functions.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                        ##### PWR peripheral overview #####
  ==============================================================================
  [..]
   (#) The Power control (PWR) provides an overview of the supply architecture
       for the different power domains and of the supply configuration
       controller.

   (#) Every entity has low power mode as described below :
   (#) The CPU low power modes are :
      (++) CPU CRun.
      (++) CPU CSleep.
      (++) CPU CStop.
   (#) The Core low power modes are :
      (++) Run.
      (++) Stop 0.
      (++) Stop 1.
      (++) Stop 2.
      (++) Stop 3.
      (++) Standby.
      (++) Shutdown.

  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) After startup, power management peripheral is not active by default. Use
       __HAL_RCC_PWR_CLK_ENABLE() macro to enable power interface.

   (#) Call HAL_PWR_EnableBkUpAccess() and HAL_PWR_DisableBkUpAccess() functions
       to enable/disable access to the backup domain (RCC Backup domain control
       register RCC_BDCR, RTC registers, TAMP registers, backup registers).

   (#) Call HAL_PWR_ConfigPVD() after setting parameters to be configured (event
       mode and voltage threshold) in order to set up the Programmed Voltage
       Detector, then use HAL_PWR_EnablePVD() and  HAL_PWR_DisablePVD()
       functions to start and stop the PVD detection.
       (++) PVD level can be one of the following values :
             (+++) 2V0
             (+++) 2V2
             (+++) 2V4
             (+++) 2V5
             (+++) 2V6
             (+++) 2V8
             (+++) 2V9
             (+++) External input analog voltage PVD_IN (compared internally to
                  VREFINT)

   (#) Call HAL_PWR_EnableWakeUpLine() and HAL_PWR_DisableWakeUpLine() functions
       with the right parameter to configure the wake up line polarity (Low or
       High), the wake up line selection and to enable and disable it.

   (#) Call HAL_PWR_EnterSLEEPMode() function to enter the CPU in Sleep mode.
       Wake-up from Sleep mode could be following to an event or an
       interrupt according to low power mode intrinsic request called (__WFI()
       or __WFE()).

   (#) Call HAL_PWR_EnterSTOPMode() function to enter the whole system to Stop
       mode. Wake-up from Stop mode could be following to an event or an
       interrupt according to low power mode intrinsic request called (__WFI()
       or __WFE()).

   (#) Call HAL_PWR_EnterSTANDBYMode() function to enter the whole system in
       Standby mode. Wake-up from Standby mode can be following only by an
       interrupt.

   (#) Call HAL_PWR_EnableSleepOnExit() and HAL_PWR_DisableSleepOnExit() APIs to
       enable and disable the Cortex-M33 re-entry in Sleep mode after an
       interruption handling is over.

   (#) Call HAL_PWR_EnableSEVOnPend() and HAL_PWR_DisableSEVOnPend() functions
       to configure the Cortex-M33 to wake-up after any pending event / interrupt
       even if it's disabled or has insufficient priority to cause exception
       entry.

   (#) Call HAL_PWR_ConfigPVM() after setting parameters to be configured
       (event mode and PVD type) in order to set up the Peripheral Voltage
       Monitor, then use HAL_PWR_EnableVddUSBVoltageMonitor(), HAL_PWR_EnableVddIO2VoltageMonitor(),
       HAL_PWR_EnableVddA1VoltageMonitor() and HAL_PWR_EnableVddA2VoltageMonitor()
       functions to start the PVM VDDx monitoring.
       Use HAL_PWR_DisableVddUSBVoltageMonitor(), HAL_PWR_DisableVddIO2VoltageMonitor(),
       HAL_PWR_DisableVddA1VoltageMonitor() and HAL_PWR_DisableVddA2VoltageMonitor()
       to stop the PVM VDDx monitoring.
       (++) PVM monitored voltages are :
             (+++) VDDUSB
             (+++) VDDIO2 (This feature is available only for STM32U375xx, STM32U385xx devices.)
             (+++) VDDA

   (#) Call HAL_PWR_PVD_IRQHandler() under PVD_PVM_IRQHandler() function to
       handle the PWR PVD & PVM interrupt request.

   (#) Call HAL_PWR_WAKEUP_LINE_IRQHandler() function to handle all wake-up
       lines interrupts.

   (#) Call HAL_PWR_ConfigAttributes() function to configure PWR item secure and
       privilege attributes and call HAL_PWR_GetConfigAttributes() function to
       get the attribute configuration for the selected item.

     *** PWR HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in PWR HAL driver.

      (+) __HAL_PWR_GET_FLAG()   : Get the PWR pending flags.
      (+) __HAL_PWR_CLEAR_FLAG() : Clear the PWR pending flags.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

#if defined (HAL_PWR_MODULE_ENABLED)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Private_Defines PWR Private Defines
  * @{
  */

/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */
#define PVD_RISING_EDGE                (1U)                                    /*!< Mask for rising edge set as PVD trigger                 */
#define PVD_FALLING_EDGE               (2U)                                    /*!< Mask for falling edge set as PVD trigger                */
#define PVD_MODE_IT                    (4U)                                    /*!< Mask for interruption yielded by PVD threshold crossing */
#define PVD_MODE_EVT                   (8U)                                    /*!< Mask for event yielded by PVD threshold crossing        */
/**
  * @}
  */

/** @defgroup PWR_PVM_Mode_Mask PWR PVM Mode Mask
  * @{
  */
#define PVM_RISING_EDGE                (1U)                                    /*!< Mask for rising edge set as PVM trigger                 */
#define PVM_FALLING_EDGE               (2U)                                    /*!< Mask for falling edge set as PVM trigger                */
#define PVM_MODE_IT                    (4U)                                    /*!< Mask for interruption yielded by PVM threshold crossing */
#define PVM_MODE_EVT                   (8U)                                    /*!< Mask for event yielded by PVM threshold crossing        */
/**
  * @}
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Initialization and De-Initialization Functions
  *  @brief   Initialization and de-Initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and De-Initialization Functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to deinitialize power peripheral.

    [..]
      After system reset, the backup domain (RCC Backup domain control register
      RCC_BDCR, RTC registers, TAMP registers, backup registers)
      is protected against possible unwanted write accesses.
      The HAL_PWR_EnableBkUpAccess() function enables the access to the backup
      domain.
      The HAL_PWR_DisableBkUpAccess() function disables the access to the backup
      domain.

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
  * @brief  Enable write access to the backup domain (RCC Backup domain control
  *         register RCC_BDCR, RTC registers, TAMP registers, backup registers).
  * @note   After a system reset, the backup domain is protected against
  *         possible unwanted write accesses.
  * @retval None.
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  WRITE_REG(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Disable write access to the backup domain (RCC Backup domain control
  *         register RCC_BDCR, RTC registers, TAMP registers, backup registers).
  * @retval None.
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  CLEAR_REG(PWR->DBPR);
}
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2 Peripheral Control Functions
  *  @brief   Low power modes configuration functions
  *
@verbatim
 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to control power peripheral.

    *** PVD configuration ***
    =========================
    [..]
      (+) The PVD can be used to monitor the VDD power supply by comparing it
          to a threshold selected by the PVDLS[2:0] bits in the PWR supply
          voltage monitoring control register (PWR_SVMCR) and can be enabled by
          setting the PVDE bit.

      (+) A PVDO flag is available in the PWR supply voltage monitoring status
          register (PWR_SVMSR) to indicate if VDD is higher or lower than the
          PVD threshold. This event is internally connected to the EXTI line 16
          and can generate an interrupt if enabled through the EXTI registers.
          It is configurable through __HAL_PWR_PVD_EXTI_ENABLE_IT() macro.

      (+) The PVD can remain active in Stop 0, Stop 1, Stop 2 modes. The PVD
          is not functional in Stop 3, Standby and Shutdown mode.

      (+) During Stop 0, Stop 1 and Stop 2 modes, it is possible to set the PVD
          in ultra-low-power mode to further reduce the current consumption by
          setting the ULPMEN bit in PWR_CR1 register.

    *** Wake-up line configuration ***
    =================================
    [..]
      (+) Each of ten wakeup events WKUPx, (x = 1 to 10), can be generated from pins or internal events,
          selected by WUSELx[1:0] in the PWR_WUCR3 register.

          The pin polarity is configurable through the WUCR2 register to be
          active on rising or falling edges.

      (+) When a wakeup event is received the HAL_PWR_WKUP_IRQHandler
          is called and the appropriate flag is set in the PWR_WUSR register.
          Then in the HAL_PWR_WKUP_IRQHandler function the wakeup pin flag
          will be cleared and the appropriate user callback will be called.
          The user can add his own code by customization of function pointer
          HAL_PWR_WKUPx_Callback.

    *** Low Power modes configuration ***
    =====================================
    [..]
      This section presents 7 principles low-power modes :
      (+) Sleep mode   : Cortex-M33 is stopped and all PWR domains are remaining
                         active (powered and clocked).

      (+) Stop 0 mode  : Cortex-M33 is stopped, clocks are stopped and the
                         main regulator is running.

      (+) Stop 1 mode  : Cortex-M33 is stopped, clocks are stopped and the
                         regulator is in low power mode. Several peripheral can
                         operate in this mode.

      (+) Stop 2 mode  : Cortex-M33 is stopped, clocks are stopped and the
                         regulator is in low power mode. Only autonomous
                         peripherals can operate in this mode.

      (+) Stop 3 mode  : Cortex-M33 is stopped, clocks are stopped and the
                         regulator is in low power mode. No peripheral can
                         operate in this mode. Only RAMs content is preserved.

      (+) Standby mode : Cortex-M33 is in SleepDeep mode and the voltage
                         supply regulator is powered off.

      (+) Shutdown mode: All PWR domains enter Shutdown mode and the VCORE
                         supply regulator is powered off. The SRAMs and
                         register contents are lost except for registers in the
                         Backup domain.
@endverbatim
  * @{
  */

/**
  * @brief  Configure the voltage threshold detected by the Programmed Voltage
  *         Detector (PVD).
  * @param  sConfigPVD : Pointer to a PWR_PVDTypeDef structure that contains the
  *                      PVD configuration information (PVDLevel and EventMode).
  * @retval None.
  */
HAL_StatusTypeDef HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PLS[2:0] bits according to PVDLevel value */
  MODIFY_REG(PWR->SVMCR, PWR_SVMCR_PVDLS, sConfigPVD->PVDLevel);

  /* Disable PVD Event/Interrupt */
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();
  __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();

  /* Configure the PVD in interrupt mode */
  if ((sConfigPVD->Mode & PVD_MODE_IT) == PVD_MODE_IT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }

  /* Configure the PVD in event mode */
  if ((sConfigPVD->Mode & PVD_MODE_EVT) == PVD_MODE_EVT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_EVENT();
  }

  /* Configure the PVD in rising edge */
  if ((sConfigPVD->Mode & PVD_RISING_EDGE) == PVD_RISING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }

  /* Configure the PVD in falling edge */
  if ((sConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
  }

  return HAL_OK;
}

/**
  * @brief  Enable the programmable voltage detector (PVD).
  * @retval None.
  */
void HAL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Disable the programmable voltage detector (PVD).
  * @retval None.
  */
void HAL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Enable the wake up line functionality.
  * @note   Wake up lines are used to wake up the system from Stop 0-1-2-3, Standby and
  *         Shutdown modes.
  * @param  WakeUpLine : Specifies which wake up line to enable.
  *                     This parameter can be one of the following:
  *                     @arg @ref PWR_WAKEUP_LINE1
  *                     @arg @ref PWR_WAKEUP_LINE2
  *                     @arg @ref PWR_WAKEUP_LINE3
  *                     @arg @ref PWR_WAKEUP_LINE4
  *                     @arg @ref PWR_WAKEUP_LINE5
  *                     @arg @ref PWR_WAKEUP_LINE6
  *                     @arg @ref PWR_WAKEUP_LINE7
  *                     @arg @ref PWR_WAKEUP_LINE8
  *                     @arg @ref PWR_WAKEUP_LINE9
  *                     @arg @ref PWR_WAKEUP_LINE10
  * @param  Selection  : Specifies the source of the line to enable.
  *                     This parameter can be one of the following values when available:
  *                     @arg @ref PWR_WAKEUP_SELECT_0
  *                     @arg @ref PWR_WAKEUP_SELECT_1
  *                     @arg @ref PWR_WAKEUP_SELECT_2
  *                     @arg @ref PWR_WAKEUP_SELECT_3
  * @param  Polarity   : Specifies the polarity of the pin in case of the line selected is a pin.
  *                     This parameter can be one of the following values when available:
  *                     @arg @ref PWR_WAKEUP_POLARITY_HIGH
  *                     @arg @ref PWR_WAKEUP_POLARITY_LOW
  * @retval None.
  */
void HAL_PWR_EnableWakeUpLine(uint32_t WakeUpLine, uint32_t Selection, uint32_t Polarity)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_LINE(WakeUpLine));
  assert_param(IS_PWR_WAKEUP_SELECTION(Selection));
  assert_param(IS_PWR_WAKEUP_POLARITY(Polarity));

  /* Specifies the wake up line I/O selection */
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpLine) * 2U)), Selection << (POSITION_VAL(WakeUpLine) * 2U));

  /* Specifies the wake up line polarity */
  MODIFY_REG(PWR->WUCR2, (1UL << (POSITION_VAL(WakeUpLine))), Polarity << (POSITION_VAL(WakeUpLine)));

  /* Enable wake-up line */
  SET_BIT(PWR->WUCR1, WakeUpLine);
}

/**
  * @brief  Disable the wake up line functionality.
  * @param  WakeUpLine : Specifies the wake up line to disable.
  *                     This parameter can be a combination of all the following
  *                     values when available:
  *                     @arg @ref PWR_WAKEUP_LINE1
  *                     @arg @ref PWR_WAKEUP_LINE2
  *                     @arg @ref PWR_WAKEUP_LINE3
  *                     @arg @ref PWR_WAKEUP_LINE4
  *                     @arg @ref PWR_WAKEUP_LINE5
  *                     @arg @ref PWR_WAKEUP_LINE6
  *                     @arg @ref PWR_WAKEUP_LINE7
  *                     @arg @ref PWR_WAKEUP_LINE8
  *                     @arg @ref PWR_WAKEUP_LINE9
  *                     @arg @ref PWR_WAKEUP_LINE10
  * @retval None
  */
void HAL_PWR_DisableWakeUpLine(uint32_t WakeUpLine)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_LINE(WakeUpLine));

  /* Disable wake-up line */
  CLEAR_BIT(PWR->WUCR1, WakeUpLine);
}

/**
  * @brief  Get and Clear Wake-up source.
  * @retval WakeUpLine : This parameter can be a combination of all the following
  *                     values when available:
  *                     @arg @ref PWR_WAKEUP_LINE1
  *                     @arg @ref PWR_WAKEUP_LINE2
  *                     @arg @ref PWR_WAKEUP_LINE3
  *                     @arg @ref PWR_WAKEUP_LINE4
  *                     @arg @ref PWR_WAKEUP_LINE5
  *                     @arg @ref PWR_WAKEUP_LINE6
  *                     @arg @ref PWR_WAKEUP_LINE7
  *                     @arg @ref PWR_WAKEUP_LINE8
  *                     @arg @ref PWR_WAKEUP_LINE9
  *                     @arg @ref PWR_WAKEUP_LINE10
  */
uint32_t HAL_PWR_GetClearWakeupSource(void)
{
  uint32_t wakeupline;

  /* Get all wake-up lines */
  wakeupline = READ_REG(PWR->WUSR);

  /* Clear all the wake-up interrupt flags */
  WRITE_REG(PWR->WUSCR, wakeupline);

  return wakeupline;
}

/**
  * @brief  Enter the CPU in Sleep mode.
  * @note   In Sleep mode, all I/O lines keep the same state as in Run mode.
  * @note   CPU clock is off and all peripherals including Cortex-M33 core such
  *         as NVIC and SysTick can run and wake up the CPU when an interrupt
  *         or an event occurs.
  * @param  Regulator : Specifies the regulator state in Sleep mode.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_MAINREGULATOR_ON
  *                     @arg @ref PWR_LOWPOWERREGULATOR_ON
  * @note   This parameter is not available in this product.
  *         The parameter is kept just to maintain compatibility with other
  *         products.
  * @param  SLEEPEntry : Specifies if Sleep mode is entered with WFI or WFE
  *                      instruction.
  *                      This parameter can be one of the following values :
  *                      @arg @ref PWR_SLEEPENTRY_WFI enter Sleep mode with Wait
  *                                For Interrupt request.
  *                      @arg @ref PWR_SLEEPENTRY_WFE enter Sleep mode with Wait
  *                                For Event request.
  *                      @arg @ref PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR enter Sleep mode with Wait
  *                                For Event request and no clear of pending event before.
  * @retval None.
  */
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Regulator);

  /* Check the parameter */
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Sleep mode entry */
  if (SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
  else
  {
    if (SLEEPEntry != PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR)
    {
      /* Clear all pending event */
      __SEV();
      __WFE();
    }

    /* Request Wait For Event */
    __WFE();
  }
}

/**
  * @brief  Enter the whole system to Stop mode.
  * @note   In Stop 0 mode, the regulator remains in main regulator mode,
  *         allowing a very fast wakeup time but with much higher consumption
  *         comparing to other Stop modes.
  * @note   Stop 0 offers the largest number of active peripherals and wakeup
  *         sources, a smaller wakeup time but a higher consumption.
  *         All clocks OFF except LSI and LSE.
  *         MSIK, MSIS or HSI16 can be enabled temporarily when requested by
            an autonomous peripheral, or forced to be kept enabled.
  * @note   The Stop 1 mode is the same as Stop 0 mode except that the regulator is
  *         in low-power mode.
  * @note   The Stop 2 mode is similar to Stop 1 except that most of the core domain
            is put in a lower leakage mode.
  * @note   The Stop 3 mode is based on the Cortex-M33 Deepsleep mode combined
  *         with peripheral clock gating.
  *         All clocks in the VCORE domain are stopped.
  *         The LSE or LSI is still running.
  * @note   When exiting Stop mode by issuing an interrupt or a wakeup event,
  *         if STOPWUCK=1 in RCC_CFGR1 the HSI16 oscillator is selected as system clock.
  *         if STOPWUCK=0 in RCC_CFGR1 the MSIS with frequency before entering the Stop
  *         mode, limited to 48 MHz.
  *         When exiting the Stop or Standby mode, the regulator is the same than when
  *         entering lowpower modes. The voltage range is the range 2.
  * @param  StopMode : Specifies the Stop mode
  *         This parameter can be one of the following values:
  *            @arg @ref PWR_LOWPOWERMODE_STOP0
  *            @arg @ref PWR_LOWPOWERMODE_STOP1
  *            @arg @ref PWR_LOWPOWERMODE_STOP2
  *            @arg @ref PWR_LOWPOWERMODE_STOP3
  * @param  STOPEntry : Specifies if Stop mode is entered with WFI or WFE
  *                     instruction.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_STOPENTRY_WFI enter Stop mode with Wait
  *                               For Interrupt request.
  *                     @arg @ref PWR_STOPENTRY_WFE enter Stop mode with Wait
  *                               For Event request.
  *                     @arg @ref PWR_STOPENTRY_WFE_NO_EVT_CLEAR enter Stop mode with Wait
  *                               For Event request and no clear of pending event before.
  * @retval None.
  */
void HAL_PWR_EnterSTOPMode(uint32_t StopMode, uint8_t STOPEntry)
{
  /* Check the parameter */
  assert_param(IS_PWR_STOPMODE(StopMode));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Configure Stop mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, StopMode);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry */
  if (STOPEntry == PWR_STOPENTRY_WFI)
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
  else
  {
    if (STOPEntry != PWR_STOPENTRY_WFE_NO_EVT_CLEAR)
    {
      /* Clear all pending event */
      __SEV();
      __WFE();
    }

    /* Request Wait For Event */
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Enter the whole system to Standby mode.
  * @note   The Standby mode is used to achieve the lowest power consumption
  *         with BOR. The internal regulator is switched off so that the VCORE
  *         domain is powered off. The MSI (MSIS and MSIK) RC, the HSI16 RC and
  *         the HSE crystal oscillators are also switched off.
  * @note   After entering Standby mode, SRAMs and register contents are lost
  *         except for registers in the Backup domain and Standby circuitry.
  *         Optionally, 8 Kbytes, 24 Kbytes, 32 Kbytes or full SRAM2 content
  *         can be retained in Standby mode, supplied by the low-power regulator.
  * @note   The state of each I/O during Standby mode can be selected by
  *         software : Enable GPIO state retention in Standby mode through
  *         HAL_PWREx_EnableStandbyIORetention() and disable through
  *         HAL_PWREx_DisableStandbyIORetention().
  * @retval None.
  */
void HAL_PWR_EnterSTANDBYMode(void)
{
  /* Select Standby mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_2);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Wait For Interrupt Request */
  __WFI();
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
  /* Set SLEEPONEXIT bit of Cortex-M33 System Control Register */
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
  /* Clear SLEEPONEXIT bit of Cortex-M33 System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Enable CORTEX SEV-ON-PEND feature.
  * @note   Sets SEVONPEND bit of SCR register. When this bit is set, any
  *         pending event / interrupt even if it's disabled or has insufficient
  *         priority to cause exception entry wakes up the Cortex-M33.
  * @retval None.
  */
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex-M33 System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Disable CORTEX SEVONPEND feature.
  * @note   Resets SEVONPEND bit of SCR register. When this bit is reset, only
  *         enabled pending causes exception entry wakes up the Cortex-M33.
  * @retval None.
  */
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex-M33 System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Enable the VDDUSB independent USB voltage monitor.
  * @retval None.
  */
void HAL_PWR_EnableVddUSBVoltageMonitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

/**
  * @brief  Disable the VDDUSB independent USB voltage monitor.
  * @retval None.
  */
void HAL_PWR_DisableVddUSBVoltageMonitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

#if defined(PWR_SVMCR_IO2SV)
/**
  * @brief  Enable the VDDIO2 independent voltage monitor.
  * @retval None.
  */
void HAL_PWR_EnableVddIO2VoltageMonitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}

/**
  * @brief  Disable the VDDIO2 independent voltage monitor.
  * @retval None.
  */
void HAL_PWR_DisableVddIO2VoltageMonitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}
#endif /* PWR_SVMCR_IO2SV */

/**
  * @brief  Enable the VDDA independent analog supply voltage monitor 1.
  * @note   1.8V threshold
  * @retval None.
  */
void HAL_PWR_EnableVddA1VoltageMonitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Disable the VDDA independent analog supply voltage monitor 1.
  * @retval None.
  */
void HAL_PWR_DisableVddA1VoltageMonitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Enable the VDDA independent analog supply voltage monitor 2.
  * @note   1.8V threshold
  * @retval None.
  */
void HAL_PWR_EnableVddA2VoltageMonitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Disable the VDDA independent analog supply voltage monitor 2.
  * @retval None.
  */
void HAL_PWR_DisableVddA2VoltageMonitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Configure the voltage monitor threshold detected by the Peripheral
  *         voltage monitoring (PVM).
  * @param  pConfigPVM : Pointer to a PWR_PVMTypeDef structure that contains the
  *                      PVM configuration information (PVMType and EventMode).
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWR_ConfigPVM(const PWR_PVMTypeDef *pConfigPVM)
{

  /* Check the parameters */
  assert_param(IS_PWR_PVM_TYPE(pConfigPVM->PVMType));
  assert_param(IS_PWR_PVM_MODE(pConfigPVM->Mode));

  /* Check the peripheral voltage monitor type */
  switch (pConfigPVM->PVMType)
  {
    case PWR_VDDUSB_VM: /* Independent USB voltage monitor */

      /* Disable EXTI USBVM event and interrupt */
      __HAL_PWR_USBVM_EXTI_DISABLE_EVENT();
      __HAL_PWR_USBVM_EXTI_DISABLE_IT();
      __HAL_PWR_USBVM_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_USBVM_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the USBVM in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_USBVM_EXTI_ENABLE_IT();
      }

      /* Configure the USBVM in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_USBVM_EXTI_ENABLE_EVENT();
      }

      /* Configure the USBVM in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_USBVM_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the USBVM in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_USBVM_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

#if defined(PWR_SVMCR_IO2SV)
    case PWR_VDDIO2_VM: /* Independent I/Os voltage monitor */

      /* Disable EXTI IO2VM event and interrupt */
      __HAL_PWR_IO2VM_EXTI_DISABLE_EVENT();
      __HAL_PWR_IO2VM_EXTI_DISABLE_IT();
      __HAL_PWR_IO2VM_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_IO2VM_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the IO2VM in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_IT();
      }

      /* Configure the IO2VM in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_EVENT();
      }

      /* Configure the IO2VM in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the IO2VM in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_FALLING_EDGE();
      }
      break;
#endif /* PWR_SVMCR_IO2SV */

    case PWR_VDDA_VM1: /* Independent ADC voltage monitor 1 */

      /* Disable EXTI ADCVM1 event and interrupt */
      __HAL_PWR_ADCVM1_EXTI_DISABLE_EVENT();
      __HAL_PWR_ADCVM1_EXTI_DISABLE_IT();
      __HAL_PWR_ADCVM1_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_ADCVM1_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the ADCVM1 in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_ADCVM1_EXTI_ENABLE_IT();
      }

      /* Configure the ADCVM1 in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_ADCVM1_EXTI_ENABLE_EVENT();
      }

      /* Configure the ADCVM1 in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_ADCVM1_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the ADCVM1 in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_ADCVM1_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    case PWR_VDDA_VM2: /* Independent ADC voltage monitor 2 */

      /* Disable EXTI ADCVM2 event and interrupt */
      __HAL_PWR_ADCVM2_EXTI_DISABLE_EVENT();
      __HAL_PWR_ADCVM2_EXTI_DISABLE_IT();
      __HAL_PWR_ADCVM2_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_ADCVM2_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the ADCVM2 in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_ADCVM2_EXTI_ENABLE_IT();
      }

      /* Configure the ADCVM2 in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_ADCVM2_EXTI_ENABLE_EVENT();
      }

      /* Configure the ADCVM2 in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_ADCVM2_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the ADCVM2 in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_ADCVM2_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    default: /* No valid voltage monitor selected */
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}


/**
  * @brief  This function handles the PWR PVD/PVM interrupt request.
  * @note   This API should be called under the PVD_PVM_IRQHandler().
  * @retval None.
  */
void HAL_PWR_PVD_PVM_IRQHandler(void)
{
  uint32_t  rising_flag;
  uint32_t  falling_flag;

  rising_flag  = READ_REG(EXTI->RPR1);
  falling_flag = READ_REG(EXTI->FPR1);

  /* Check PWR EXTI rising flag */
  if ((rising_flag & PWR_EXTI_LINE_PVD) != 0U)
  {
    /* Clear PVD EXTI pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVD interrupt rising user callback */
    HAL_PWR_PVD_Rising_Callback();
  }

  /* Check PWR EXTI falling flag */
  if ((falling_flag & PWR_EXTI_LINE_PVD) != 0U)
  {
    /* Clear PVD EXTI pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVD interrupt falling user callback */
    HAL_PWR_PVD_Falling_Callback();
  }

  /* Check PWR PVM USB EXTI rising flag */
  if ((rising_flag & PWR_EXTI_LINE_PVM_VDDUSB) != 0U)
  {
    /* Clear PVM USB EXTI pending bit */
    __HAL_PWR_USBVM_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVM USB interrupt rising user callback */
    HAL_PWR_USBVM_Rising_Callback();
  }

  /* Check PWR PVM USB EXTI falling flag */
  if ((falling_flag & PWR_EXTI_LINE_PVM_VDDUSB) != 0U)
  {
    /* Clear PVM USB EXTI pending bit */
    __HAL_PWR_USBVM_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVM USB interrupt falling user callback */
    HAL_PWR_USBVM_Falling_Callback();
  }

#if defined(PWR_SVMCR_IO2SV)
  /* Check PWR PVM IO2 EXTI rising flag */
  if ((rising_flag & PWR_EXTI_LINE_PVM_VDDIO2) != 0U)
  {
    /* Clear PVM IO2 EXTI pending bit */
    __HAL_PWR_IO2VM_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVM IO2 interrupt rising user callback */
    HAL_PWR_IO2VM_Rising_Callback();
  }

  /* Check PWR PVM IO2 EXTI falling flag */
  if ((falling_flag & PWR_EXTI_LINE_PVM_VDDIO2) != 0U)
  {
    /* Clear PVM IO2 EXTI pending bit */
    __HAL_PWR_IO2VM_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVM IO2 interrupt falling user callback */
    HAL_PWR_IO2VM_Falling_Callback();
  }
#endif /* PWR_SVMCR_IO2SV */

  /* Check PWR PVM ADC VM EXTI rising flag */
  if ((rising_flag & PWR_EXTI_LINE_PVM_VDDA1) != 0U)
  {
    /* Clear PVM ADC VM1 EXTI pending bit */
    __HAL_PWR_ADCVM1_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVM ADC VM1 interrupt rising user callback */
    HAL_PWR_ADCVM1_Rising_Callback();
  }

  /* Check PWR PVM ADC VM1 EXTI fallling flag */
  if ((falling_flag & PWR_EXTI_LINE_PVM_VDDA1) != 0U)
  {
    /* Clear PVM ADC VM1 EXTI pending bit */
    __HAL_PWR_ADCVM1_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVM ADC VM1 interrupt falling user callback */
    HAL_PWR_ADCVM1_Falling_Callback();
  }

  /* Check PWR PVM ADC VM2 EXTI rising flag */
  if ((rising_flag & PWR_EXTI_LINE_PVM_VDDA2) != 0U)
  {
    /* Clear PVM ADC VM2 EXTI pending bit */
    __HAL_PWR_ADCVM2_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVM ADC VM2 interrupt rising user callback */
    HAL_PWR_ADCVM2_Rising_Callback();
  }

  /* Check PWR PVM ADC VM2 EXTI falling flag */
  if ((falling_flag & PWR_EXTI_LINE_PVM_VDDA2) != 0U)
  {
    /* Clear PVM ADC VM2 EXTI pending bit */
    __HAL_PWR_ADCVM2_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVM ADC VM2 interrupt falling user callback */
    HAL_PWR_ADCVM2_Falling_Callback();
  }
}

/**
  * @brief  PWR PVD interrupt rising callback
  * @retval None
  */
__weak void HAL_PWR_PVD_Rising_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVD_Rising_Callback can be implemented in the user file
  */
}

/**
  * @brief  PWR PVD interrupt falling callback
  * @retval None
  */
__weak void HAL_PWR_PVD_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVD_Falling_Callback can be implemented in the user file
  */
}

/**
  * @brief  PWR USBVM interrupt Rising callback.
  * @retval None.
  */
__weak void HAL_PWR_USBVM_Rising_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_USBVM_Rising_Callback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR USBVM interrupt Falling callback.
  * @retval None.
  */
__weak void HAL_PWR_USBVM_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_USBVM_Falling_Callback() API can be implemented in the user file
   */
}

#if defined(PWR_SVMCR_IO2SV)
/**
  * @brief  PWR IO2VM interrupt Rising callback.
  * @retval None.
  */
__weak void HAL_PWR_IO2VM_Rising_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_IO2VM_Rising_Callback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR IO2VM interrupt Falling callback.
  * @retval None.
  */
__weak void HAL_PWR_IO2VM_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_IO2VM_Falling_Callback() API can be implemented in the user file
   */
}
#endif /* PWR_SVMCR_IO2SV */

/**
  * @brief  PWR ADCVM1 interrupt Rising callback.
  * @retval None.
  */
__weak void HAL_PWR_ADCVM1_Rising_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_ADCVM1_Rising_Callback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR ADCVM1 interrupt Falling callback.
  * @retval None.
  */
__weak void HAL_PWR_ADCVM1_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_ADCVM1_Falling_Callback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR ADCVM2 interrupt Rising callback.
  * @retval None.
  */
__weak void HAL_PWR_ADCVM2_Rising_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_ADCVM2_Rising_Callback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR ADCVM2 interrupt Falling callback.
  * @retval None.
  */
__weak void HAL_PWR_ADCVM2_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWR_ADCVM2_Falling_Callback() API can be implemented in the user file
   */
}

/**
  * @brief This function handles the PWR WAKEUP interrupt request.
  * @note   This API should be called under the WKUP_IRQHandler().
  * @retval None.
  */
void HAL_PWR_WKUP_IRQHandler(void)
{
  uint32_t wakeupline;

  wakeupline = HAL_PWR_GetClearWakeupSource();

  /* Wakeup line interrupt detected */
  if ((wakeupline & PWR_WUSR_WUF1) != 0U)
  {
    /* PWR WKUP1 interrupt user callback */
    HAL_PWR_WKUP1_Callback();
  }

  if ((wakeupline & PWR_WUSR_WUF2) != 0U)
  {
    /* PWR WKUP2 interrupt user callback */
    HAL_PWR_WKUP2_Callback();
  }

  if ((wakeupline & PWR_WUSR_WUF3) != 0U)
  {
    /* PWR WKUP3 interrupt user callback */
    HAL_PWR_WKUP3_Callback();
  }

  if ((wakeupline & PWR_WUSR_WUF4) != 0U)
  {
    /* PWR WKUP4 interrupt user callback */
    HAL_PWR_WKUP4_Callback();
  }

  if ((wakeupline & PWR_WUSR_WUF5) != 0U)
  {
    /* PWR WKUP5 interrupt user callback */
    HAL_PWR_WKUP5_Callback();
  }

  if ((wakeupline & PWR_WUSR_WUF6) != 0U)
  {
    /* PWR WKUP6 interrupt user callback */
    HAL_PWR_WKUP6_Callback();
  }
  if ((wakeupline & PWR_WUSR_WUF7) != 0U)
  {
    /* PWR WKUP7 interrupt user callback */
    HAL_PWR_WKUP7_Callback();
  }
  if ((wakeupline & PWR_WUSR_WUF8) != 0U)
  {
    /* PWR WKUP8 interrupt user callback */
    HAL_PWR_WKUP8_Callback();
  }
  if ((wakeupline & PWR_WUSR_WUF9) != 0U)
  {
    /* PWR WKUP9 interrupt user callback */
    HAL_PWR_WKUP9_Callback();
  }
  if ((wakeupline & PWR_WUSR_WUF10) != 0U)
  {
    /* PWR WKUP10 interrupt user callback */
    HAL_PWR_WKUP10_Callback();
  }
}

/**
  * @brief PWR WKUP1 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP1_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP1_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP2 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP2_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP2_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP3 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP3_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP3_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP4 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP4_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP4_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP5 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP5_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP5_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP6 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP6_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP6_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP7 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP7_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP7_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP8 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP8_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP8_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP9 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP9_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP9_Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP10 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP10_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP10_Callback can be implemented in the user file
  */
}
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group3 Attributes Management Functions
  *  @brief    Attributes management functions
  *
@verbatim
 ===============================================================================
                       ##### PWR Attributes Functions #####
 ===============================================================================
    [..]
      When the TrustZone security is activated by the TZEN option bit in the
      FLASH_OPTR register, some PWR register fields can be secured against
      non-secure access.
      The PWR TrustZone security allows the following features to be secured
      through the PWR_SECCFGR register :

      (+) Low-power mode.
      (+) Wake-up (WKUP) lines.
      (+) Voltage detection and monitoring.
      (+) VBAT mode.
      (+) I/Os pull-up/pull-down configuration.

      Other PWR configuration bits are secure when :
      (++ The system clock selection is secure in RCC: the voltage scaling
           (VOS) configuration is secure.
      (+) A GPIO is configured as secure: its corresponding bit for pull-up /
           pull-down configuration in Standby mode is secure.

      A non-secure access to a secure-protected register bit is denied :
      (+) The secured bits are not written (WI) with a non-secure write access.
      (+) The secured bits are read as 0 (RAZ) with a non-secure read access.

    [..]
      When the TrustZone security is disabled (TZEN = 0), PWR_SECCFGR is RAZ/WI
      and all other registers are non-secure.

    [..]
      By default, after a reset, all PWR registers can be read or written with
      both privileged and unprivileged accesses, except PWR_PRIVCFGR that can be
      written with privileged access only. PWR_PRIVCFGR can be read by secure
      and non secure, privileged and unprivileged accesses.
      The SPRIV bit in PWR_PRIVCFGR can be written with secure privileged access
      only. This bit configures the privileged access of all PWR secure
      functions (defined by PWR_SECCFGR, GTZC, RCC or GPIO).
      When the SPRIV bit is set in PWR_PRIVCFGR:
      (+) The PWR secure bits can be written only with privileged access,
      including PWR_SECCFGR.
      (+) The PWR secure bits can be read only with privileged access except
           PWR_SECCFGR and PWR_PRIVCFGR that can be read by privileged or
           unprivileged access.
      (+) An unprivileged access to a privileged PWR bit or register is
           discarded : the bits are read as zero and the write to these bits is
           ignored (RAZ/WI).
      The NSPRIV bit of PWR_PRIVCFGR can be written with privileged access only,
      secure or non-secure. This bit configures the privileged access of all PWR
      securable functions that are configured as non-secure (defined by
      PWR_SECCFGR, GTZC, RCC or GPIO).
      When the NSPRIV bit is set in PWR_PRIVCFGR :
      (+) The PWR securable bits that are configured as non-secure, can be
           written only with privileged access.
      (+) The PWR securable bits that are configured as non-secure, can be read
           only with privileged access except PWR_PRIVCFGR that can be read by
           privileged or unprivileged accesses.
      (+) The VOSRDY bit in PWR_VOSR, PWR_SR, PWR_SVMSR and PWR_WUSR, can be read
           with privileged or unprivileged accesses.
      (+) An unprivileged access to a privileged PWR bit or register is
           discarded : the bits are read as zero and the write to these bits is
           ignored (RAZ/WI).

@endverbatim
  * @{
  */

/**
  * @brief  Configure the PWR item attributes.
  * @note   Available attributes are security and privilege protection.
  * @note   Security attribute can only be set only by secure access.
  * @note   Privilege attribute for secure items can be managed only by a secure
  *         privileged access.
  * @note   Privilege attribute for nsecure items can be managed  by a secure
  *         privileged access or by a nsecure privileged access.
  * @note   As the privileged attributes concern either all secure or all non-secure PWR
  *         resources accesses and not each PWR individual items access attribute, the application
  *         must ensure that the privilege access attribute configurations are coherent amongst the
  *         security level set on PWR individual items so not to overwrite a previous more restricted
  *         access rule (consider either all secure and/or all non-secure PWR resources accesses by
  *         privileged-only transactions or privileged and unprivileged transactions).
  * @param  Item       : Specifies the item(s) to set attributes on.
  *                      This parameter can be a combination of PWR_ITEMS.
  * @param  Attributes : Specifies the available attribute(s).
  *                      This parameter can be one of PWR_ATTRIBUTES.
  * @retval None.
  */
void HAL_PWR_ConfigAttributes(uint32_t Item, uint32_t Attributes)
{
  /* Check the parameters */
  assert_param(IS_PWR_ITEMS_ATTRIBUTES(Item));
  assert_param(IS_PWR_ATTRIBUTES(Attributes));

  /* Prevent unused argument(s) compilation warning */
  UNUSED(Item);

#if defined (CPU_IN_SECURE_STATE)
  /* Secure item management (TZEN = 1) */
  if ((Attributes & PWR_ITEM_ATTR_SEC_PRIV_MASK) == PWR_ITEM_ATTR_SEC_PRIV_MASK)
  {
    /* Privilege item management */
    if ((Attributes & PWR_SEC_PRIV) == PWR_SEC_PRIV)
    {
      SET_BIT(PWR_S->SECCFGR, Item);
      SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
    }
    else
    {
      SET_BIT(PWR_S->SECCFGR, Item);
      CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
    }
  }
  /* NSecure item management */
  else
  {
    /* Privilege item management */
    if ((Attributes & PWR_NSEC_PRIV) == PWR_NSEC_PRIV)
    {
      CLEAR_BIT(PWR_S->SECCFGR, Item);
      SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
    else
    {
      CLEAR_BIT(PWR_S->SECCFGR, Item);
      CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
  }
#else
  /* NSecure item management (TZEN = 0) */
  if ((Attributes & PWR_ITEM_ATTR_NSEC_PRIV_MASK) == PWR_ITEM_ATTR_NSEC_PRIV_MASK)
  {
    /* Privilege item management */
    if ((Attributes & PWR_NSEC_PRIV) == PWR_NSEC_PRIV)
    {
      SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
    else
    {
      CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
  }
#endif /* defined (CPU_IN_SECURE_STATE) */
}


/**
  * @brief  Get attribute(s) of a PWR item.
  * @param  Item        : Specifies the item(s) to set attributes on.
  *                       This parameter can be one of PWR_ITEMS.
  * @param  pAttributes : Pointer to return attribute(s).
  *                       Returned value could be on of PWR_ATTRIBUTES.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWR_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes)
{
  uint32_t attributes;

  /* Check attribute pointer */
  if (pAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameter */
  assert_param(IS_PWR_ITEMS_ATTRIBUTES(Item));

  /* Check item security */
  if ((PWR->SECCFGR & Item) == Item)
  {
    /* Get Secure privileges attribute */
    attributes = ((PWR->PRIVCFGR & PWR_PRIVCFGR_SPRIV) == 0U) ? PWR_SEC_NPRIV : PWR_SEC_PRIV;
  }
  else
  {
    /* Get Non-Secure privileges attribute */
    attributes = ((PWR->PRIVCFGR & PWR_PRIVCFGR_NSPRIV) == 0U) ? PWR_NSEC_NPRIV : PWR_NSEC_PRIV;
  }

  /* return value */
  *pAttributes = attributes;

  return HAL_OK;
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (HAL_PWR_MODULE_ENABLED) */
/**
  * @}
  */

/**
  * @}
  */
