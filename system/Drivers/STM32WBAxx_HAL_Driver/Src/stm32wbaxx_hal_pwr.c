/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_pwr.c
  * @author  MCD Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Initialization/De-Initialization Functions.
  *           + Peripheral Control Functions.
  *           + PWR Attributes Functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
      (+) CPU CRun.
      (+) CPU CSleep.
      (+) CPU CStop.
   (#) The Core low power modes are :
      (+) Run.
      (+) Stop 0.
      (+) Stop 1.
      (+) Standby with retention
      (+) Standby.

  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) After startup, power management peripheral is not active by default. Use
       __HAL_RCC_PWR_CLK_ENABLE() macro to enable power interface.

   (#) Call HAL_PWR_EnableBkUpAccess() and HAL_PWR_DisableBkUpAccess() functions
       to enable/disable access to the backup domain (RCC Backup domain control
       register RCC_BDCR, RTC registers, TAMP registers, backup registers and
       backup SRAM).

   (#) Call HAL_PWR_ConfigPVD() after setting parameters to be configured (event
       mode and voltage threshold) in order to set up the Programmed Voltage
       Detector, then use HAL_PWR_EnablePVD() and  HAL_PWR_DisablePVD()
       functions to start and stop the PVD detection.
       (+) PVD level can be one of the following values :
             (++) 2V0
             (++) 2V2
             (++) 2V4
             (++) 2V5
             (++) 2V6
             (++) 2V8
             (++) 2V9
             (++) External input analog voltage PVD_IN (compared internally to
                  VREFINT)

   (#) Call HAL_PWR_EnableWakeUpPin() and HAL_PWR_DisableWakeUpPin() functions
       with the right parameter to configure the wake up pin polarity (Low or
       High), the wake up pin selection and to enable and disable it.

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

   (#) Call HAL_PWR_PVD_IRQHandler() under PVD_IRQHandler() function to
       handle the PWR PVD interrupt request.

   (#) Call HAL_PWR_WAKEUP_PIN_IRQHandler() function to handle all wake-up
       pins interrupts.

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
#include "stm32wbaxx_hal.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

#if defined(HAL_PWR_MODULE_ENABLED)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Private_Defines PWR Private Defines
  * @{
  */

/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */
#define PVD_RISING_EDGE  (0x01U)  /*!< Mask for rising edge set as PVD trigger                 */
#define PVD_FALLING_EDGE (0x02U)  /*!< Mask for falling edge set as PVD trigger                */
#define PVD_MODE_IT      (0x04U)  /*!< Mask for interruption yielded by PVD threshold crossing */
#define PVD_MODE_EVT     (0x08U)  /*!< Mask for event yielded by PVD threshold crossing        */
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
      RCC_BDCR, RTC registers, TAMP registers, backup registers and backup SRAM)
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
  * @brief  Enable access to the backup domain (RCC Backup domain control
  *         register RCC_BDCR, RTC registers, TAMP registers, backup registers
  *         and backup SRAM).
  * @note   After a system reset, the backup domain is protected against
  *         possible unwanted write accesses.
  * @retval None.
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Disable access to the backup domain (RCC Backup domain control
  *         register RCC_BDCR, RTC registers, TAMP registers, backup registers
  *         and backup SRAM).
  * @retval None.
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->DBPR, PWR_DBPR_DBP);
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

      (+) A PVDO flag is available in the PWR supply voltage monitoring control
          register (PWR_SVMCR) to indicate if VDD is higher or lower than the
          PVD threshold. This event is internally connected to the EXTI line 16
          and can generate an interrupt if enabled through the EXTI registers.
          It is configurable through __HAL_PWR_PVD_EXTI_ENABLE_IT() macro.

      (+) The PVD can remain active in Stop 0 and Stop 1 modes. The PVD
          is not functional in Standby mode.

      (+) During Stop 0 and Stop 1 modes, it is possible to set the PVD
          in ultra-low-power mode to further reduce the current consumption by
          setting the ULPMEN bit in PWR_CR1 register.

    *** Wake-up pin configuration ***
    =================================
    [..]
      (+) Wake-up pin is used to wake up the system from Standby mode.
          The pin selection is configurable through the WUCR3 register to map
          internal signal to wake up pin line.
          The pin polarity is configurable through the WUCR2 register to be
          active on rising or falling edges.

      (+) There are up to 19 wake-up signals that can be mapped to up to 8
          wake-up lines in the STM32WBA family.

      (+) When a wakeup pin event is received the HAL_PWR_WAKEUP_PIN_IRQHandler
          is called and the appropriate flag is set in the PWR_WKUPFR register.
          Then in the HAL_PWR_WAKEUP_PIN_IRQHandler function the wakeup pin flag
          will be cleared and the appropriate user callback will be called.
          The user can add his own code by customization of function pointer
          HAL_PWR_WKUPx_Callback.

    *** Low Power modes configuration ***
    =====================================
    [..]
      This section presents 4 principles low-power modes :
      (+) Sleep mode   : Cortex-M33 is stopped and all PWR domains are remaining
                         active (powered and clocked).

      (+) Stop 0 mode  : Cortex-M33 is stopped, clocks are stopped and the
                         main regulator is running.

      (+) Stop 1 mode   : Cortex-M33 is stopped, clocks are stopped and the
                          regulator is in low power mode. Several peripheral can
                          operate in this mode.

      (+) Standby mode : Cortex-M33 is in SleepDeep mode and the voltage
                         supply regulator is powered off.

   *** Sleep mode ***
   ==================
    [..]
      (+) Entry :
          The Sleep mode is entered by using the HAL_PWR_EnterSLEEPMode()
          function.

          (++) PWR_SLEEPENTRY_WFI: enter Sleep mode with WFI instruction.
          (++) PWR_SLEEPENTRY_WFE: enter Sleep mode with WFE instruction.

      -@@- The Regulator parameter is not used for the STM32WBA family and is
           kept as parameter just to maintain compatibility with other families.

      (+) Exit :
          According to Sleep entry, any event when entry is __WFE() intrinsic
          and any interrupt when entry is __WFI() intrinsic can wake up the
          device from Sleep mode.

   *** Stop 0 & Stop 1 modes ***
   ===================
    [..]
      The Stop 0 and Stop 1 mode are based on the Cortex-M33 Deepsleep mode combined with
      the peripheral clock gating.
      In Stop 0 mode, the voltage regulator is configured in main.
      In Stop 1 mode, The voltage regulator is configured in low power mode.
      all clocks in the VCORE domain are stopped.
      In Stop mode 0 the PLL, HSI16 and HSE32 oscillators are disabled.
      Some peripherals with the LPBAM capability can switch on HSI16 or HSE32 for
      transferring data. All SRAMs and register contents are preserved,
      but the SRAMs can totally or not be switched off to further reduce
      consumption.
      The BOR is always available in Stop mode.

      (+) Entry:
          The Stop mode is entered using the HAL_PWR_EnterSTOPMode() function
          with :
         (++) Regulator:
          (+++) PWR_MAINREGULATOR_ON     : Main regulator ON      (Stop 0 mode).
          (+++) PWR_LOWPOWERREGULATOR_ON : Low power regulator ON (Stop 1 mode).

         (++) STOPEntry:
          (+++) PWR_STOPENTRY_WFI: enter Stop mode with WFI instruction.
          (+++) PWR_STOPENTRY_WFE: enter Stop mode with WFE instruction.

      (+) Exit:
          Any EXTI line configured in interrupt mode (the corresponding EXTI
          interrupt vector must be enabled in the NVIC). The interrupt source
          can be external interrupts or peripherals with wakeup capability.
          Any peripheral interrupt occurring when the AHB/APB clocks are present
          due to an autonomous peripheral clock request (the peripheral vector
          must be enabled in the NVIC).
          Any EXTI line configured in event mode.

   *** Standby mode ***
   ====================
    [..]
      The Standby mode is used to achieve the lowest power consumption with BOR.
      The internal regulator is switched off so that the VCORE domain is powered
      off.
      The PLL, the HSI16 RC and the HSE32 crystal oscillators are also switched off.
      The RTC can remain active (Standby mode with RTC, Standby mode without
      RTC).
      The Brownout reset (BOR) always remains active in Standby mode.
      The state of each I/O during Standby mode can be selected by software:
      I/O with internal pull-up, internal pull-down or floating.
      After entering Standby mode, SRAMs and register contents are lost except
      for registers and backup SRAM in the Backup domain and Standby circuitry.
      Optionally, the full SRAM1 and SRAM2 can be retained in Standby mode depending
      on R1RSB1 and R2RSB1 bit configuration in PWR_CR1. In this case, the low-power
      regulator is ON and provides the supply to SRAM1 and or SRAM2. Also the 2.4
      GHz RADIO SRAMs can be retained, and the sleep timer kept operational depending
      on RADIOSB bit configuration in PWR_CR1.
      The BORL (Brownout reset detector low) can be configured in ultra low
      power mode to further reduce power consumption during Standby mode.
      The device exits Standby mode when an external reset (NRST pin), an IWDG
      reset, WKUP pin event (configurable rising or falling edge), an RTC event
      occurs (alarm, periodic wakeup, timestamp), or a tamper detection.
      The system clock after wakeup is HSI16.

      (++) Entry:
           The Standby mode is entered using the HAL_PWR_EnterSTANDBYMode()
           function.

      (++) Exit:
           WKUPx pin edge, RTC event, external Reset in NRST pin, IWDG Reset,
           BOR reset.

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
  * @note   Wake up lines are used to wake up the system from Sleep, Stop 0-1 and
  *         Standby modes.
  * @param  WakeUpPin : Specifies which wake up line to enable. This parameter
  *                     can be one of PWR_WakeUp_Pins_High_Polarity define
  *                     group where every param select the wake up line, the
  *                     wake up source with high polatiry detection and the wake
  *                     up selected I/O or can be one of
  *                     PWR_WakeUp_Pins_Low_Polarity define group where every
  *                     param select the wake up line, the wake up source with
  *                     low polarity and the wake up selected I/O or can be one
  *                     of PWR_WakeUp_Pins define group where every param select
  *                     the wake up line, the wake up source with
  *                     high polarity and the first wake up I/O.
  * @retval None.
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  /* Check the parameter */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPin));

  /* Specifies the wake up line polarity for the event detection (rising or falling edge) */
  MODIFY_REG(PWR->WUCR2, (PWR_EWUP_MASK & WakeUpPin), (WakeUpPin >> PWR_WUP_POLARITY_SHIFT));

  /* Specifies the wake up line I/O selection */
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(PWR_EWUP_MASK & WakeUpPin) * 2U)),
             (WakeUpPin >> PWR_WUP_SELECT_SIGNAL_SHIFT));

  /* Enable wake-up line */
  SET_BIT(PWR->WUCR1, (PWR_EWUP_MASK & WakeUpPin));
}

/**
  * @brief  Disable the wake up line functionality.
  * @param  WakeUpPin : Specifies the wake up line to disable.
  *                     This parameter can be a combination of all the following
  *                     values when available:
  *                     @arg @ref PWR_WAKEUP_PIN1
  *                     @arg @ref PWR_WAKEUP_PIN2
  *                     @arg @ref PWR_WAKEUP_PIN3
  *                     @arg @ref PWR_WAKEUP_PIN4
  *                     @arg @ref PWR_WAKEUP_PIN6
  *                     @arg @ref PWR_WAKEUP_PIN5
  *                     @arg @ref PWR_WAKEUP_PIN7
  *                     @arg @ref PWR_WAKEUP_PIN8
  * @retval None
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPin));

  /* Disable wake-up pin */
  CLEAR_BIT(PWR->WUCR1, (PWR_EWUP_MASK & WakeUpPin));
}

/**
  * @brief  Get and Clear Wake-up source.
  * @retval WakeUpPin : This parameter can be a combination of all the following
  *                     values when available:
  *                     @arg @ref PWR_WAKEUP_PIN1
  *                     @arg @ref PWR_WAKEUP_PIN2
  *                     @arg @ref PWR_WAKEUP_PIN3
  *                     @arg @ref PWR_WAKEUP_PIN4
  *                     @arg @ref PWR_WAKEUP_PIN6
  *                     @arg @ref PWR_WAKEUP_PIN5
  *                     @arg @ref PWR_WAKEUP_PIN7
  *                     @arg @ref PWR_WAKEUP_PIN8
  */
uint32_t HAL_PWR_GetClearWakeupSource(void)
{
  uint32_t wakeuppin;

  /* Get all wake-up pins */
  wakeuppin = PWR->WUSR;

  /* Clear all the wake-up interrupt flags */
  PWR->WUSCR = wakeuppin;

  return wakeuppin;
}

/**
  * @brief  Enter the CPU in Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
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
  * @note   When WFI entry is used, ticks interrupt must be disabled to avoid
  *         unexpected CPU wake up.
  * @retval None.
  */
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry)
{
  UNUSED(Regulator);

  /* Check the parameter */
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Select Sleep mode entry */
  if (SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
  else
  {
    /* Wait For Event Request */
    __SEV();
    __WFE();
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
  * @note   Stop 1 mode, The voltage regulator is configured in low power mode.
  *         Stop 1 achieves the lowest power consumption while retaining
  *         the content of SRAM and registers. All clocks in the VCORE domain
  *         are stopped. The PLL, HSI16 and HSE32 oscillators are disabled.
  *         The LSE or LSI is still running.
  * @note   When exiting Stop mode by issuing an interrupt or a
  *         wakeup event, the HSI16 oscillator is selected as system clock
  *         The MCU is in Run mode same range as before entering Stop mode.
  * @note   On STM32WBAXX_SI_CUT1_0 :
  *         Under a critical timing wakeup condition, CPU is executing code
  *         after WFI while the system is still evolving to manage the enter and
  *         exit from STOP mode. Under this condition it results that STOPF flag
  *         is set and SYSCLK source change during CPU wakeup code execution.
  *         Worst case scenario is when the system is running on PLL, fed by
  *         HSE32, and HSI16 is on. In this case STOPF flag bit is set and
  *         SYSCLK clock source is changed 25 sys clock cycles after WFI.
  *         Undoing any PLL1ON, HSEON, HSION and SYSCLK modification.
  *         Workaround at application level is to call this API under critical
  *         section and add a wait loop of at least 25 system clock cycles,
  *         before reading the STOPF flag and making any modification to PLL1ON,
  *         HSEON, HSION and SYSCLK selection.
  * @param  Regulator : Specifies the regulator state in Stop mode
  *         This parameter can be one of the following values:
  *            @arg @ref PWR_LOWPOWERMODE_STOP0  Stop 0 mode (main regulator ON)
  *            @arg @ref PWR_LOWPOWERMODE_STOP1  Stop 1 mode (low power regulator ON)
  * @param  STOPEntry : Specifies if Stop mode is entered with WFI or WFE
  *                     instruction.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_STOPENTRY_WFI enter Stop mode with Wait
  *                               For Interrupt request.
  *                     @arg @ref PWR_STOPENTRY_WFE enter Stop mode with Wait
  *                               For Event request.
  * @retval None.
  */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry)
{
  /* Check the parameter */
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Select Stop mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, Regulator);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Select Stop mode entry */
  if (STOPEntry == PWR_STOPENTRY_WFI)
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
  else
  {
    /* Wait For Event Request */
    __SEV();
    __WFE();
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * @brief  Enter the whole system to Standby mode.
  * @note   The Standby mode is used to achieve the lowest power consumption
  *         with BOR. The internal regulator is switched off so that the VCORE
  *         domain is powered off. The PLL, the HSI16 and the HSE32 crystal
  *         oscillators are also switched off.
  * @note   After entering Standby mode, SRAMs and register contents are lost
  *         except for registers and backup SRAM in the Backup domain and
  *         Standby circuitry. Optionally, the full SRAM1 or SRAM2 can be
  *         retained in Standby mode, supplied by the low-power regulator.
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
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

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
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None.
  */
void HAL_PWR_PVD_IRQHandler(void)
{
  uint32_t  rising_flag;
  uint32_t  falling_flag;

  rising_flag  = READ_REG(EXTI->RPR1);
  falling_flag = READ_REG(EXTI->FPR1);

  /* Check PWR exti rising flag */
  if ((rising_flag & PWR_EXTI_LINE_PVD) != 0U)
  {
    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVD interrupt rising user callback */
    HAL_PWR_PVD_Rising_Callback();
  }

  /* Check PWR exti fallling flag */
  if ((falling_flag & PWR_EXTI_LINE_PVD) != 0U)
  {
    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVD interrupt falling user callback */
    HAL_PWR_PVD_Falling_Callback();
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
  * @brief  PWR PVD interrupt Falling callback
  * @retval None
  */
__weak void HAL_PWR_PVD_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVD_Falling_Callback can be implemented in the user file
  */
}
/**
  * @}
  */

/**
  * @brief This function handles the PWR WAKEUP interrupt request.
  * @note   This API should be called under the WKUP_IRQHandler().
  * @retval None.
  */
void HAL_PWR_WKUP_IRQHandler(void)
{
  uint32_t wakeuppin;

  wakeuppin = HAL_PWR_GetClearWakeupSource();

  /* Wakeup pin EXTI line interrupt detected */
  if ((wakeuppin & PWR_WUSR_WUF1) != 0U)
  {
    /* PWR WKUP1 interrupt user callback */
    HAL_PWR_WKUP1_Callback();
  }
#if defined(PWR_WUCR1_WUPEN2)
  if ((wakeuppin & PWR_WUSR_WUF2) != 0U)
  {
    /* PWR WKUP2 interrupt user callback */
    HAL_PWR_WKUP2_Callback();
  }
#endif /* defined(PWR_WUCR1_WUPEN2) */
  if ((wakeuppin & PWR_WUSR_WUF3) != 0U)
  {
    /* PWR WKUP3 interrupt user callback */
    HAL_PWR_WKUP3_Callback();
  }

  if ((wakeuppin & PWR_WUSR_WUF4) != 0U)
  {
    /* PWR WKUP4 interrupt user callback */
    HAL_PWR_WKUP4_Callback();
  }
#if defined(PWR_WUCR1_WUPEN5)
  if ((wakeuppin & PWR_WUSR_WUF5) != 0U)
  {
    /* PWR WKUP5 interrupt user callback */
    HAL_PWR_WKUP5_Callback();
  }
#endif /* defined(PWR_WUCR1_WUPEN5) */
  if ((wakeuppin & PWR_WUSR_WUF6) != 0U)
  {
    /* PWR WKUP6 interrupt user callback */
    HAL_PWR_WKUP6_Callback();
  }
  if ((wakeuppin & PWR_WUSR_WUF7) != 0U)
  {
    /* PWR WKUP7 interrupt user callback */
    HAL_PWR_WKUP7_Callback();
  }
  if ((wakeuppin & PWR_WUSR_WUF8) != 0U)
  {
    /* PWR WKUP8 interrupt user callback */
    HAL_PWR_WKUP8_Callback();
  }
}

/**
  * @brief PWR WKUP1 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP1_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP1Callback can be implemented in the user file
  */
}

#if defined(PWR_WUCR1_WUPEN2)
/**
  * @brief PWR WKUP2 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP2_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP2Callback can be implemented in the user file
  */
}
#endif /* defined(PWR_WUCR1_WUPEN2) */

/**
  * @brief PWR WKUP3 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP3_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP3Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP4 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP4_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP4Callback can be implemented in the user file
  */
}

#if defined(PWR_WUCR1_WUPEN5)
/**
  * @brief PWR WKUP5 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP5_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP5Callback can be implemented in the user file
  */
}
#endif /* defined(PWR_WUCR1_WUPEN5) */

/**
  * @brief PWR WKUP6 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP6_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP6Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP7 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP7_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP7Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP8 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_WKUP8_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_WKUP8Callback can be implemented in the user file
  */
}
/**
  * @}
  */

#if defined(PWR_PRIVCFGR_NSPRIV)
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

      (++) Low-power mode.
      (++) Wake-up (WKUP) pins.
      (++) Voltage detection and monitoring.
      (++) VBAT mode.
      (++) I/Os pull-up/pull-down configuration.

      Other PWR configuration bits are secure when :
      (++) The system clock selection is secure in RCC: the voltage scaling
           (VOS) configuration is secure.
      (++) A GPIO is configured as secure: its corresponding bit for pull-up /
           pull-down configuration in Standby mode is secure.

      A non-secure access to a secure-protected register bit is denied :
      (++) The secured bits are not written (WI) with a non-secure write access.
      (++) The secured bits are read as 0 (RAZ) with a non-secure read access.

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
      (++) The PWR secure bits can be written only with privileged access,
      including PWR_SECCFGR.
      (++) The PWR secure bits can be read only with privileged access except
           PWR_SECCFGR and PWR_PRIVCFGR that can be read by privileged or
           unprivileged access.
      (++) An unprivileged access to a privileged PWR bit or register is
           discarded : the bits are read as zero and the write to these bits is
           ignored (RAZ/WI).
      The NSPRIV bit of PWR_PRIVCFGR can be written with privileged access only,
      secure or non-secure. This bit configures the privileged access of all PWR
      securable functions that are configured as non-secure (defined by
      PWR_SECCFGR, GTZC, RCC or GPIO).
      When the NSPRIV bit is set in PWR_PRIVCFGR :
      (++) The PWR securable bits that are configured as non-secure, can be
           written only with privileged access.
      (++) The PWR securable bits that are configured as non-secure, can be read
           only with privileged access except PWR_PRIVCFGR that can be read by
           privileged or unprivileged accesses.
      (++) The VOSRDY bit in PWR_VOSR, PWR_SR, PWR_SVMSR and PWR_WUSR, can be read
           with privileged or unprivileged accesses.
      (++) An unprivileged access to a privileged PWR bit or register is
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

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
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
#endif /* __ARM_FEATURE_CMSE */
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

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
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
#else
  /* Get Non-Secure privileges attribute */
  attributes = ((PWR->PRIVCFGR & PWR_PRIVCFGR_NSPRIV) == 0U) ? PWR_NSEC_NPRIV : PWR_NSEC_PRIV;
#endif /* __ARM_FEATURE_CMSE */

  /* return value */
  *pAttributes = attributes;

  return HAL_OK;
}
/**
  * @}
  */
#endif /* #if defined(PWR_PRIVCFGR_SPRIV) */

/**
  * @}
  */

#endif /* defined(HAL_PWR_MODULE_ENABLED) */
/**
  * @}
  */

/**
  * @}
  */
