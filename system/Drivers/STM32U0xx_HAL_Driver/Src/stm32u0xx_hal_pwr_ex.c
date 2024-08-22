/**
  ******************************************************************************
  * @file    stm32u0xx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller extension peripheral :
  *           + Power Supply Control Functions
  *           + Low Power Control Functions
  *           + Voltage Monitoring Functions
  *           + Memories Retention Functions
  *           + I/O Pull-Up Pull-Down Configuration Functions
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
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Call HAL_PWREx_ControlVoltageScaling() and HAL_PWREx_GetVoltageRange() to
       set / get the voltage scaling range.
      (+) Voltage scaling can be one of the following values :
             (++) voltage output scale 1 : 1V2
                  => Used when system clock frequency is up to 160 MHz
             (++) voltage output scale 2 : 1V1
                  => Used when system clock frequency is up to 100 MHz

   (#) Call HAL_PWREx_EnterSTOP1Mode() function to enter the whole system to
       Stop 1 mode. Wake-up from Stop 1 mode could be following to an event or
       an interrupt according to low power mode intrinsic request called
       (__WFI() or __WFE()). (Regulator state on U0 devices is managed
       internally but regulator parameter is kept for product compatibility).

   (#) Call HAL_PWREx_EnterSTOP2Mode() function to enter the whole system to
       Stop 2 mode. Wake-up from Stop 2 mode could be following to an event or
       an interrupt according to low power mode intrinsic request called
       (__WFI() or __WFE()). (Regulator state on U0 devices is managed
       internally but regulator parameter is kept for product compatibility).

   (#) Call HAL_PWREx_EnableBatteryCharging() and
       HAL_PWREx_DisableBatteryCharging() to enable / disable the battery
       charging capability when VDD alimentation is available.

   (#) Call HAL_PWREx_ConfigPVM() after setting parameters to be configured
       (event mode and PVD type) in order to set up the Peripheral Voltage use
       HAL_PWREx_EnablePVM1(),HAL_PWREx_EnablePVM3() and HAL_PWREx_EnablePVM4()
       functions and use HAL_PWREx_DisablePVM1(),HAL_PWREx_EnablePVM3()
       and HAL_PWREx_EnablePVM4() to stop the PVM VDDx monitoring.
       (+) PVM monitored voltages are :
             (++) VDDUSB versus 1V2
             (++) VDDADC versus 1V62
             (++) VDDDAC versus 2V2

   (#) Call HAL_PWREx_PVD_PVM_IRQHandler() function to handle the PWR PVD and
       PVM interrupt request.

   (#) Call HAL_PWREx_EnablePullUpPullDownConfig() and
       HAL_PWREx_DisablePullUpPullDownConfig() to I/O enable / disable pull-up
       and pull-down configuration.

   (#) Call HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() to
       apply respectively pull-up and pull-down to selected I/O.
       Call HAL_PWREx_DisableGPIOPullUp() and HAL_PWREx_DisableGPIOPullDown() to
       disable applied respectively pull-up and pull-down to selected I/O.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal.h"

/** @addtogroup STM32U0xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */
#if defined (GPIOE)
/* PORTE pins mask */
#define PWR_PORTE_AVAILABLE_PINS  0x00000388U   /* PE3, PE7..PE9 */
#endif /* GPIOE */
#if defined (PWR_PDCRD_PD0)
#define PWR_PORTD_AVAILABLE_PINS  0x00003F7FU   /* PD0..PD6, PD8..PD13 */
#else
#define PWR_PORTD_AVAILABLE_PINS  0x00000004U   /* PD2 */
#endif /* PWR_PDCRD_PD0 */
/* PORTF pins mask */
#define PWR_PORTF_AVAILABLE_PINS  0x0000000FU   /* PF0..PF3 */

/** @defgroup PWREx_PVM_Mode_Mask PWR PVM Mode Mask
  * @{
  */
#define PVM_MODE_IT               0x00010000U   /*!< Mask for interruption yielded by PVM threshold crossing */
#define PVM_MODE_EVT              0x00020000U   /*!< Mask for event yielded by PVM threshold crossing        */
#define PVM_RISING_EDGE           0x00000001U   /*!< Mask for rising edge set as PVM trigger                 */
#define PVM_FALLING_EDGE          0x00000002U   /*!< Mask for falling edge set as PVM trigger                */
/**
  * @}
  */

/** @defgroup PWREx_TimeOut_Value PWR Extended Flag Setting Time Out Value
  * @{
  */
#define PWR_FLAG_SETTING_DELAY_US                      50UL   /*!< Time out value for REGLPF and VOSF flags setting */
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

/** @defgroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1 Power Supply Control Functions
  * @brief    Power supply control functions
  *
@verbatim
 ===============================================================================
                  ##### Power supply control functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to control power supply.

    [..]
      (+) When exiting the Stop or Standby modes, the regulator is the same than
          when entering low power modes. The voltage range is the Range 2.

      (+) Both regulators can provide four different voltages (voltage scaling)
          and can operate in Stop modes.
          Voltage scaling ranges can be one of the following values :
             (++) voltage output scale 1 : 1V2
                  => Used when system clock frequency is up to 160 MHz
             (++) voltage output scale 2 : 1V1
                  => Used when system clock frequency is up to 100 MHz

@endverbatim
  * @{
  */

/**
  * @brief Configure the main internal regulator output voltage.
  * @param  VoltageScaling specifies the regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  *          This parameter can be one of the following values:

  * @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 Regulator voltage output range 1 mode,
  *                                        typical output voltage at 1.2 V,
  *                                        system frequency up to 80 MHz.
  * @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 Regulator voltage output range 2 mode,
  *                                        typical output voltage at 1.0 V,
  *                                        system frequency up to 26 MHz.
  * @note  When moving from Range 1 to Range 2, the system frequency must be decreased to
  *        a value below 26 MHz before calling HAL_PWREx_ControlVoltageScaling() API.
  *        When moving from Range 2 to Range 1, the system frequency can be increased to
  *        a value up to 80 MHz after calling HAL_PWREx_ControlVoltageScaling() API. For
  *        some devices, the system frequency can be increased up to 120 MHz.
  * @note  When moving from Range 2 to Range 1, the API waits for VOSF flag to be
  *        cleared before returning the status. If the flag is not cleared within
  *        50 microseconds, HAL_TIMEOUT status is reported.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t wait_loop_index;
  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

  /* If Set Range 1 */
  if (VoltageScaling == PWR_REGULATOR_VOLTAGE_SCALE1)
  {
    if (READ_BIT(PWR->CR1, PWR_CR1_VOS) != PWR_REGULATOR_VOLTAGE_SCALE1)
    {
      /* Set Range 1 */
      MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_REGULATOR_VOLTAGE_SCALE1);
      /* Wait until VOSF is cleared */
      wait_loop_index = ((PWR_FLAG_SETTING_DELAY_US * SystemCoreClock) / 1000000U) + 1U;
      while ((HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_VOSF)) && (wait_loop_index != 0U))
      {
        wait_loop_index--;
      }
      if (HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_VOSF))
      {
        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
    if (READ_BIT(PWR->CR1, PWR_CR1_VOS) != PWR_REGULATOR_VOLTAGE_SCALE2)
    {
      /* Set Range 2 */
      MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_REGULATOR_VOLTAGE_SCALE2);
      /* No need to wait for VOSF to be cleared for this transition */
    }
  }
  return HAL_OK;
}

/**
  * @brief Return Voltage Scaling Range.
  * @retval VOS bit field (PWR_REGULATOR_VOLTAGE_SCALE1 or PWR_REGULATOR_VOLTAGE_SCALE2)
  *
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->CR1 & PWR_CR1_VOS);
}

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @brief    Low power control functions
  *
@verbatim
 ===============================================================================
                     ##### Low power control functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to control low power modes.

    *** Low Power modes configuration ***
    =====================================
    [..]
      This section presents 3 principles low power modes :

      (+) Stop 1 mode   : Cortex-M4 is stopped, clocks are stopped and the
                          regulator is in low power mode. Only autonomous
                          peripherals can operate in this mode.

      (+) Stop 2 mode   : Cortex-M4 is stopped, clocks are stopped and the
                          regulator is in low power mode. No peripheral can
                          operate in this mode. Only RAMs content is preserved.

      (+) Shutdown mode : All PWR domains enter Shutdown mode and the VCORE
                          supply regulator is powered off. The SRAMs and
                          register contents are lost except for registers in the
                          Backup domain.

   *** Stop 1 mode ***
   ===================
    [..]
      The Stop 1 mode is based on the Cortex-M4 Deepsleep mode combined with
      peripheral clock gating. In Stop 1 mode, all clocks in the VCORE domain
      are stopped.
      The PLL, MSIS, MSIK, HSI16 and HSE oscillators are disabled.
      Some peripherals with the LPBAM capability can switch on HSI16 or MSIS or
      MSIK for transferring data. All SRAMs and register contents are preserved,
      but the SRAMs can be totally or partially switched off to further reduce
      consumption.
      The BOR is always available in Stop 1 mode.

      (+) Entry:
          The Stop 1 mode is entered by using the HAL_PWREx_EnterSTOP1Mode()
          function.

          (++) PWR_STOPENTRY_WFI: enter Stop 1 mode with WFI instruction.
          (++) PWR_STOPENTRY_WFE: enter Stop 1 mode with WFE instruction.

      (+) Exit:
          Any EXTI line configured in interrupt mode (the corresponding EXTI
          interrupt vector must be enabled in the NVIC). The interrupt source
          can be external interrupts or peripherals with wakeup capability.
          Any peripheral interrupt occurring when the AHB/APB clocks are present
          due to an autonomous peripheral clock request (the peripheral vector
          must be enabled in the NVIC)
          Any EXTI line configured in event mode.

   *** Stop 2 mode ***
   ===================
    [..]
      The Stop 2 mode is based on the Cortex-M4 Deepsleep mode combined with
      peripheral clock gating. In Stop 2 mode, all clocks in the VCORE domain
      are stopped.
      The PLL, MSIS, MSIK, HSI16 and HSE oscillators are disabled.
      All SRAMs and register contents are preserved, but the SRAMs can be
      totally or partially switched off to further reduce consumption.
      The BOR is always available in Stop 2 mode.

      (+) Entry:
          The Stop 2 mode is entered by using the HAL_PWREx_EnterSTOP2Mode()
          function.

          (++) PWR_STOPENTRY_WFI: enter Stop 2 mode with WFI instruction.
          (++) PWR_STOPENTRY_WFE: enter Stop 23 mode with WFE instruction.

      (+) Exit:
          WKUPx pin edge, RTC or TAMP event, external Reset in NRST pin, IWDG
          Reset, BOR reset.

  *** Shutdown mode ***
   ====================
    [..]
      The lowest power consumption is reached in Shutdown mode. It is based on
      the Deepsleep mode with the voltage regulator disabled. The VCORE domain
      is consequently powered off.
      The PLL, HSI16, MSIS, MSIK and HSE oscillators are also switched off.
      The SRAMs and register contents are lost except for registers in the
      Backup domain.
      The BOR is not available in Shutdown mode.
      No power voltage monitoring is possible in this mode, therefore the switch
      to Backup domain is not supported.

      (+) Entry:
          The Shutdown mode is entered by using the HAL_PWREx_EnterSHUTDOWNMode()
          function.

      (+) Exit:
          WKUPx pin edge, RTC/TAMP event, external Reset in NRST pin.

@endverbatim
  * @{
  */

/**
  * @brief Enter Low-power Run mode
  * @note  In Low-power Run mode, all I/O pins keep the same state as in Run mode.
  * @note  When Regulator is set to PWR_LOWPOWERREGULATOR_ON, the user can optionally configure the
  *        Flash in power-down monde in setting the RUN_PD bit in FLASH_ACR register.
  *        Additionally, the clock frequency must be reduced below 2 MHz.
  *        Setting RUN_PD in FLASH_ACR then appropriately reducing the clock frequency must
  *        be done before calling HAL_PWREx_EnableLowPowerRunMode() API.
  * @retval None
  */
void HAL_PWREx_EnableLowPowerRunMode(void)
{
  /* Set Regulator parameter */
  SET_BIT(PWR->CR1, PWR_CR1_LPR);
}

/**
  * @brief Exit Low-power Run mode.
  * @note  Before HAL_PWREx_DisableLowPowerRunMode() completion, the function checks that
  *        REGLPF has been properly reset (otherwise, HAL_PWREx_DisableLowPowerRunMode
  *        returns HAL_TIMEOUT status). The system clock frequency can then be
  *        increased above 2 MHz.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void)
{
  uint32_t wait_loop_index;

  /* Clear LPR bit */
  CLEAR_BIT(PWR->CR1, PWR_CR1_LPR);

  /* Wait until REGLPF is reset */
  wait_loop_index = ((PWR_FLAG_SETTING_DELAY_US * SystemCoreClock) / 1000000U) + 1U;
  while ((HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_REGLPF)) && (wait_loop_index != 0U))
  {
    wait_loop_index--;
  }
  if (HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_REGLPF))
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief Enter Stop 1 mode.
  * @note  In Stop 1 mode, only low power voltage regulator is ON.
  * @note  In Stop 1 mode, all I/O pins keep the same state as in Run mode.
  * @note  All clocks in the VCORE domain are stopped; the PLL, the MSI,
  *        the HSI and the HSE oscillators are disabled. Some peripherals with the wakeup capability
  *        (I2Cx, USARTx and LPUART) can switch on the HSI to receive a frame, and switch off the HSI
  *        after receiving the frame if it is not a wakeup frame. In this case, the HSI clock is propagated
  *        only to the peripheral requesting it.
  *        SRAM and register contents are preserved.
  *        The BOR is available.
  * @note  When exiting Stop 1 mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock if STOPWUCK bit in RCC_CFGR register
  *         is set; the MSI oscillator is selected if STOPWUCK is cleared.
  * @note  Due to low power mode, an additional startup delay is incurred when waking up from Stop 1 mode.
  * @param STOPEntry  specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_STOPENTRY_WFI  Enter Stop mode with WFI instruction
  *            @arg @ref PWR_STOPENTRY_WFE  Enter Stop mode with WFE instruction
  * @retval None
  */
void HAL_PWREx_EnterSTOP1Mode(uint8_t STOPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Stop 1 mode with Low-Power Regulator */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_0);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry --------------------------------------------------*/
  if (STOPEntry == PWR_STOPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief Enter Stop 2 mode.
  * @note  In Stop 2 mode, only low power voltage regulator is ON.
  * @note  In Stop 2 mode, all I/O pins keep the same state as in Run mode.
  * @note  All clocks in the VCORE domain are stopped, the PLL, the MSI,
  *        the HSI and the HSE oscillators are disabled. Some peripherals with wakeup capability
  *        (LCD, LPTIM1, I2C3 and LPUART) can switch on the HSI to receive a frame, and switch off the HSI after
  *        receiving the frame if it is not a wakeup frame. In this case the HSI clock is propagated only
  *        to the peripheral requesting it.
  *        SRAM and register contents are preserved.
  *        The BOR is available.
  *        The voltage regulator is set in low-power mode but LPR bit must be cleared to enter stop 2 mode.
  *        Otherwise, Stop 1 mode is entered.
  * @note  When exiting Stop 2 mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock if STOPWUCK bit in RCC_CFGR register
  *         is set; the MSI oscillator is selected if STOPWUCK is cleared.
  * @param STOPEntry  specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_STOPENTRY_WFI  Enter Stop mode with WFI instruction
  *            @arg @ref PWR_STOPENTRY_WFE  Enter Stop mode with WFE instruction
  * @retval None
  */
void HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry)
{
  /* Check the parameter */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));
  /* Clear LPR Bit */
  CLEAR_BIT(PWR->CR1, PWR_CR1_LPR);
  /* Set Stop mode 2 */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_1);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry --------------------------------------------------*/
  if (STOPEntry == PWR_STOPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group3 Voltage Monitoring Functions
  * @brief    Voltage monitoring functions
  *
@verbatim
 ===============================================================================
                     ##### Voltage Monitoring Functions #####
 ===============================================================================
    [..]
      This section provides functions allowing voltage monitoring.

    *** PVM configuration ***
    =========================
    [..]
      (+) The supplies (VDDADC, VDDDAC and VDDUSB) can be independent from VDD and
          can be monitored with three peripheral voltage monitoring (PVM).

      (+) Each PVM output is connected to an EXTI line and can generate an
          interrupt if enabled through the EXTI registers. The PVMx output
          interrupt is generated when the independent power supply drops below
          the PVM threshold and/or when it rises above the PVM threshold,
          depending on EXTI line rising/falling edge configuration.

      (+) Each PVM can remain active in Stop 0, Stop 1, Stop 2 modes, and the
          PVM interrupt can wake up from the Stop mode.

    *** VBAT charging ***
    =====================
    [..]
      When VDD is present, it is possible to charge the external battery on VBAT
      through an internal resistance.
      The VBAT charging is done either through a 5 kOhm resistor or through a 1.5
      kOhm resistor depending on the VBRS bit value in the PWR_BDCR2 register.
      The battery charging is enabled by setting VBE bit in the PWR_BDCR2
      register. It is automatically disabled in VBAT mode.

    *** Backup domain monitoring ***
    ================================
    [..]
      When the Backup domain voltage and temperature monitoring is enabled
      (MONEN = 1 in the PWR_BDCR1 register), the Backup domain voltage and the
      temperature are monitored.
      If the Backup domain voltage monitoring internal tamper is enabled in the
      TAMP peripheral (ITAMP1E = 1 in the TAMP_CR1 register), a tamper event is
      generated when the Backup domain voltage is above the functional range.
      In case the Backup domain voltage is below the functional range,
      a Brownout reset is generated, erasing all device including Backup domain.

    *** Backup domain battery ***
    =============================
    [..]
      (+) To retain the content of the backup registers and supply the RTC
          function when VDD is turned off, the VBAT pin can be connected to an
          optional backup voltage supplied by a battery or by another source.
          The VBAT pin powers the RTC unit, the LSE oscillator and the PC13 to
          PC15 I/Os, allowing the RTC to operate even when the main power supply
          is turned off. The backup SRAM is optionally powered by VBAT pin when
          the BREN bit is set in the PWR Backup domain control register 1
          (PWR_BDCR1).
          The switch to the VBAT supply is controlled by the power down reset
          embedded in the Reset block.

@endverbatim
  * @{
  */
#if defined(USB_DRD_FS)
/**
  * @brief Enable the Power Voltage Monitoring 1: VDDUSB versus 1.2V.
  * @retval None
  */
void HAL_PWREx_EnablePVM1(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_1);
}

/**
  * @brief Disable the Power Voltage Monitoring 1: VDDUSB versus 1.2V.
  * @retval None
  */
void HAL_PWREx_DisablePVM1(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_1);
}
#endif /* USB_DRD_FS */
/**
  * @brief Enable the Power Voltage Monitoring 2: VDDA versus 1.62V.
  * @retval None
  */
void HAL_PWREx_EnablePVM3(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_3);
}

/**
  * @brief Disable the Power Voltage Monitoring 2: VDDA versus 1.62V.
  * @retval None
  */
void HAL_PWREx_DisablePVM3(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_3);
}

/**
  * @brief Enable the Power Voltage Monitoring 3:  VDDA versus 2.2V.
  * @retval None
  */
void HAL_PWREx_EnablePVM4(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_4);
}

/**
  * @brief Disable the Power Voltage Monitoring 3:  VDDA versus 2.2V.
  * @retval None
  */
void HAL_PWREx_DisablePVM4(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_4);
}

/**
  * @brief Configure the Peripheral Voltage Monitoring (PVM).
  * @param sConfigPVM: pointer to a PWR_PVMTypeDef structure that contains the
  *        PVM configuration information.
  * @note The API configures a single PVM according to the information contained
  *       in the input structure. To configure several PVMs, the API must be singly
  *       called for each PVM used.
  * @note Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage thresholds corresponding to each
  *         detection level and to each monitored supply.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(const PWR_PVMTypeDef *sConfigPVM)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_PVM_TYPE(sConfigPVM->PVMType));
  assert_param(IS_PWR_PVM_MODE(sConfigPVM->Mode));

  /* Configure EXTI 35 to 38 interrupts if so required:
     scan through PVMType to detect which PVMx is set and
     configure the corresponding EXTI line accordingly. */
  switch (sConfigPVM->PVMType)
  {
#if defined(USB_DRD_FS)
    case PWR_PVM_1:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM1_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM1_EXTI_DISABLE_IT();
      __HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE();
      }
      break;
#endif /* USB_DRD_FS */
    case PWR_PVM_3:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM3_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM3_EXTI_DISABLE_IT();
      __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE();
      }
      break;
    case PWR_PVM_4:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM4_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM4_EXTI_DISABLE_IT();
      __HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

#if defined(USB_DRD_FS)
/**
  * @brief Enable VDDUSB supply.
  * @note  Remove VDDUSB electrical and logical isolation, once VDDUSB supply is present.
  * @retval None
  */
void HAL_PWREx_EnableVddUSB(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_USV);
}

/**
  * @brief Disable VDDUSB supply.
  * @retval None
  */
void HAL_PWREx_DisableVddUSB(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_USV);
}
#endif /* USB_DRD_FS */

/**
  * @brief Enable battery charging.
  *        When VDD is present, charge the external battery on VBAT through an internal resistor.
  * @param  ResistorSelection specifies the resistor impedance.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_BATTERY_CHARGING_RESISTOR_5     5 kOhms resistor
  *            @arg @ref PWR_BATTERY_CHARGING_RESISTOR_1_5 1.5 kOhms resistor
  * @retval None
  */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection)
{
  assert_param(IS_PWR_BATTERY_RESISTOR_SELECT(ResistorSelection));

  /* Specify resistor selection */
  MODIFY_REG(PWR->CR4, PWR_CR4_VBRS, ResistorSelection);

  /* Enable battery charging */
  SET_BIT(PWR->CR4, PWR_CR4_VBE);
}

/**
  * @brief Disable battery charging.
  * @retval None
  */
void HAL_PWREx_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_VBE);
}
/**
  * @brief This function handles the PWR PVD/PVMx interrupt request.
  * @note This API should be called under the PVD_PVM_IRQHandler().
  * @retval None
  */
void HAL_PWREx_PVD_PVM_IRQHandler(void)
{
  /* Check if the Programmable Voltage Detector is enabled (PVD) */
  if (READ_BIT(PWR->CR2, PWR_CR2_PVDE) != 0U)
  {
    /* Check PWR EXTI Rising flag */
    if (__HAL_PWR_PVD_EXTI_GET_RISING_FLAG() != 0U)
    {
      /* PWR PVD interrupt user callback */
      HAL_PWR_PVDCallback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
    }

    /* Check PWR EXTI Falling flag */
    if (__HAL_PWR_PVD_EXTI_GET_FALLING_FLAG() != 0U)
    {
      /* PWR PVD interrupt user callback */
      HAL_PWR_PVDCallback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
    }
  }

  /* Next, successively check PVMx exti flags */
#if defined(USB_DRD_FS)
  if (READ_BIT(PWR->CR2, PWR_PVM_1) != 0U)
  {
    /* Check PWR EXTI Rising flag */
    if (__HAL_PWR_PVM1_EXTI_GET_RISING_FLAG() != 0U)
    {
      /* PWR PVM interrupt user callback */
      HAL_PWREx_PVM1_Callback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVM1_EXTI_CLEAR_FLAG();
    }

    /* Check PWR EXTI Falling flag */
    if (__HAL_PWR_PVM1_EXTI_GET_FALLING_FLAG() != 0U)
    {
      /* PWR PVM USB interrupt user callback */
      HAL_PWREx_PVM1_Callback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVM1_EXTI_CLEAR_FLAG();
    }
  }
#endif /* USB_DRD_FS */
  if (READ_BIT(PWR->CR2, PWR_PVM_3) != 0U)
  {
    /* Check PWR EXTI Rising flag */
    if (__HAL_PWR_PVM3_EXTI_GET_RISING_FLAG() != 0U)
    {
      /* PWR PVM interrupt user callback */
      HAL_PWREx_PVM3_Callback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVM3_EXTI_CLEAR_FLAG();
    }

    /* Check PWR EXTI Falling flag */
    if (__HAL_PWR_PVM3_EXTI_GET_FALLING_FLAG() != 0U)
    {
      /* PWR PVM ADC interrupt user callback */
      HAL_PWREx_PVM3_Callback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVM3_EXTI_CLEAR_FLAG();
    }
  }

  if (READ_BIT(PWR->CR2, PWR_PVM_4) != 0U)
  {
    /* Check PWR EXTI Rising flag */
    if (__HAL_PWR_PVM4_EXTI_GET_RISING_FLAG() != 0U)
    {
      /* PWR PVM interrupt user callback */
      HAL_PWREx_PVM4_Callback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVM4_EXTI_CLEAR_FLAG();
    }

    /* Check PWR EXTI Falling flag */
    if (__HAL_PWR_PVM4_EXTI_GET_FALLING_FLAG() != 0U)
    {
      /* PWR PVM4 for DAC interrupt user callback */
      HAL_PWREx_PVM4_Callback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVM4_EXTI_CLEAR_FLAG();
    }
  }
}

#if defined(USB_DRD_FS)
/**
  * @brief PWR PVM USB interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_PVM1_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_PVM_USBCallback() API can be implemented in the user file
   */
}
#endif /* USB_DRD_FS */

/**
  * @brief PWR PVM ADC interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_PVM3_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_PVM_ADCCallback() API can be implemented in the user file
   */
}

/**
  * @brief PWR PVM DAC interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_PVM4_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_PVM_DACCallback() API can be implemented in the user file
   */
}

/**
  * @brief Enable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_EnableInternalWakeUpLine(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EIWUL);
}

/**
  * @brief Disable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_DisableInternalWakeUpLine(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EIWUL);
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group4 Memories Retention Functions
  * @brief    Memories retention functions
  *
@verbatim
 ===============================================================================
                     ##### Memories Retention Functions #####
 ===============================================================================
    [..]
      Several STM32U0 devices RAM are configurable to keep / lose RAMs content
      during Stop mode (Stop 0/1/2).
       (+) Retained content RAM in Stop modes are :
             (++) SRAM

@endverbatim
  * @{
  */

/**
  * @brief Enable Full SRAM content retention in Standby mode.
  * @retval None
  */
void HAL_PWREx_EnableSRAMContentRetention(void)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_RRS, PWR_FULL_SRAM_RETENTION);
}

/**
  * @brief Disable SRAM content retention in Standby mode.
  * @retval None
  */
void HAL_PWREx_DisableSRAMContentRetention(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_RRS);
}

/**
  * @brief  Enable Flash Power Down.
  * @note   This API allows to enable flash power down capabilities in low power
  *         run, low power sleep and stop modes.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_LPRUN
  *           @arg @ref PWR_FLASHPD_LPSLEEP
  *           @arg @ref PWR_FLASHPD_STOP
  * @retval None
  */
void HAL_PWREx_EnableFlashPowerDown(uint32_t PowerMode)
{
  assert_param(IS_PWR_FLASH_POWERDOWN(PowerMode));

  PWR->CR1 |= PowerMode;
}

/**
  * @brief  Disable Flash Power Down.
  * @note   This API allows to disable flash power down capabilities in low power
  *         run, low power sleep and stop modes.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_LPRUN
  *           @arg @ref PWR_FLASHPD_LPSLEEP
  *           @arg @ref PWR_FLASHPD_STOP
  * @retval None
  */
void HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode)
{
  assert_param(IS_PWR_FLASH_POWERDOWN(PowerMode));

  PWR->CR1 &= ~PowerMode;
}

/**
  * @brief Enable Ultra Low Power BORL, BORH and PVD for STOP2 and Standby modes.
  * @note  All the other modes are not affected by this bit.
  * @retval None
  */
void HAL_PWREx_EnableUltraLowPowerMode(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_ENULP);
}

/**
  * @brief Disable Ultra Low Power BORL, BORH and PVD for STOP2 and Standby modes.
  * @note  All the other modes are not affected by this bit
  * @retval None
  */
void HAL_PWREx_DisableUltraLowPowerMode(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_ENULP);
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group5 I/O Pull-Up Pull-Down Configuration Functions
  * @brief    I/O pull-up / pull-down configuration functions
  *
@verbatim
 ===============================================================================
              ##### Pull-Up Pull-Down Configuration Functions #####
 ===============================================================================
    [..]
      In Standby and Shutdown mode, pull up and pull down can be configured to
      maintain an I/O in the selected state. If the APC bit in the PWR_APCR
      register is set, the I/Os can be configured either with a pull-up through
      PWR_PUCRx registers (x=A,B,C,D,E,F), or with a pull-down through
      PWR_PDCRx registers (x=A,B,C,D,E,F), or can be kept in analog state
      if none of the PWR_PUCRx or PWR_PDCRx register is set.

    [..]
      The pull-down configuration has highest priority over pull-up
      configuration in case both PWR_PUCRx and PWR_PDCRx are set for the same
      I/O.
      This configuration is lost when exiting the Shutdown but not from Standby
      mode.

@endverbatim
  * @{
  */

/**
  * @brief Enable pull-up and pull-down configuration.
  * @note  When APC bit is set, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are applied in Standby and Shutdown modes.
  * @note  Pull-up set by PUy bit of PWR_PUCRx register is not activated if the corresponding
  *        PDy bit of PWR_PDCRx register is also set (pull-down configuration priority is higher).
  *        HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() API's ensure there
  *        is no conflict when setting PUy or PDy bit.
  * @retval None
  */
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_APC);
}

/**
  * @brief Disable pull-up and pull-down configuration.
  * @note  When APC bit is cleared, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are not applied in Standby and Shutdown modes.
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_APC);
}
/**
  * @}
  */

/**
  * @brief Enable GPIO pull-up state in Standby and Shutdown modes.
  * @note  Set the relevant PUy bits of PWR_PUCRx register to configure the I/O in
  *        pull-up state in Standby and Shutdown modes.
  * @note  This state is effective in Standby and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the
  *        power-on reset, maintained when exiting the Standby mode.
  * @note  To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *        PDy bit of PWR_PDCRx register is cleared unless it is reserved.
  * @note  Even if a PUy bit to set is reserved, the other PUy bits entered as input
  *        parameter at the same time are set.
  * @param  GPIO_Port Specify the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_H
  *         (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIO_Pin Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
  *         I/O pins are available) or the logical OR of several of them to set
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_A:
      SET_BIT(PWR->PUCRA, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRA, GPIO_Pin);
      break;

    case PWR_GPIO_B:
      SET_BIT(PWR->PUCRB, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C:
      SET_BIT(PWR->PUCRC, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D:
      SET_BIT(PWR->PUCRD, (GPIO_Pin & PWR_PORTD_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PDCRD, (GPIO_Pin & PWR_PORTD_AVAILABLE_PINS));
      break;

#if defined (GPIOE)
    case PWR_GPIO_E:
      SET_BIT(PWR->PUCRE, (GPIO_Pin & PWR_PORTE_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PDCRE, (GPIO_Pin & PWR_PORTE_AVAILABLE_PINS));
      break;
#endif /* GPIOE */

    case PWR_GPIO_F:
      SET_BIT(PWR->PUCRF, (GPIO_Pin & PWR_PORTF_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PDCRF, (GPIO_Pin & PWR_PORTF_AVAILABLE_PINS));
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Disable GPIO pull-up state in Standby mode and Shutdown modes.
  * @note  Reset the relevant PUy bits of PWR_PUCRx register used to configure the I/O
  *        in pull-up state in Standby and Shutdown modes.
  * @note  Even if a PUy bit to reset is reserved, the other PUy bits entered as input
  *        parameter at the same time are reset.
  * @param  GPIO_Port Specifies the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_H
  *          (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIO_Pin Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
  *         I/O pins are available) or the logical OR of several of them to reset
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_A:
      CLEAR_BIT(PWR->PUCRA, GPIO_Pin);
      break;

    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PUCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PUCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D:
      CLEAR_BIT(PWR->PUCRD, (GPIO_Pin & PWR_PORTD_AVAILABLE_PINS));
      break;

#if defined (GPIOE)
    case PWR_GPIO_E:
      CLEAR_BIT(PWR->PUCRE, (GPIO_Pin & PWR_PORTE_AVAILABLE_PINS));
      break;
#endif /* GPIOE */

    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PUCRF, (GPIO_Pin & PWR_PORTF_AVAILABLE_PINS));
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Enable GPIO pull-down state in Standby and Shutdown modes.
  * @note  Set the relevant PDy bits of PWR_PDCRx register to configure the I/O in
  *        pull-down state in Standby and Shutdown modes.
  * @note  This state is effective in Standby and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the
  *        power-on reset, maintained when exiting the Standby mode.
  * @note  To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *        PUy bit of PWR_PUCRx register is cleared unless it is reserved.
  * @note  Even if a PDy bit to set is reserved, the other PDy bits entered as input
  *        parameter at the same time are set.
  * @param  GPIO_Port Specify the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_H
  *         (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIO_Pin Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
  *         I/O pins are available) or the logical OR of several of them to set
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_A:
      SET_BIT(PWR->PDCRA, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRA, GPIO_Pin);
      break;

    case PWR_GPIO_B:
      SET_BIT(PWR->PDCRB, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C:
      SET_BIT(PWR->PDCRC, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D:
      SET_BIT(PWR->PDCRD, (GPIO_Pin & PWR_PORTD_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PUCRD, (GPIO_Pin & PWR_PORTD_AVAILABLE_PINS));
      break;

#if defined (GPIOE)
    case PWR_GPIO_E:
      SET_BIT(PWR->PDCRE, (GPIO_Pin & PWR_PORTE_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PUCRE, (GPIO_Pin & PWR_PORTE_AVAILABLE_PINS));
      break;
#endif /* GPIOE */

    case PWR_GPIO_F:
      SET_BIT(PWR->PDCRF, (GPIO_Pin & PWR_PORTF_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PUCRF, (GPIO_Pin & PWR_PORTF_AVAILABLE_PINS));
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Disable GPIO pull-down state in Standby and Shutdown modes.
  * @note  Reset the relevant PDy bits of PWR_PDCRx register used to configure the I/O
  *        in pull-down state in Standby and Shutdown modes.
  * @note  Even if a PDy bit to reset is reserved, the other PDy bits entered as input
  *        parameter at the same time are reset.
  * @param  GPIO_Port Specifies the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_H
  *         (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIO_Pin Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
  *         I/O pins are available) or the logical OR of several of them to reset
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_A:
      CLEAR_BIT(PWR->PDCRA, GPIO_Pin);
      break;

    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PDCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PDCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D:
      CLEAR_BIT(PWR->PDCRD, (GPIO_Pin & PWR_PORTD_AVAILABLE_PINS));
      break;

#if defined (GPIOE)
    case PWR_GPIO_E:
      CLEAR_BIT(PWR->PDCRE, (GPIO_Pin & PWR_PORTE_AVAILABLE_PINS));
      break;
#endif /* GPIOE */

    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PDCRF, (GPIO_Pin & PWR_PORTF_AVAILABLE_PINS));
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

#endif /* defined (HAL_PWR_MODULE_ENABLED) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
