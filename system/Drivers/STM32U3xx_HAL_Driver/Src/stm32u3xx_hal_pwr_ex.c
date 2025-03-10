/**
  ******************************************************************************
  * @file    stm32u3xx_hal_pwr_ex.c
  * @author  GPM Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller extension peripheral :
  *           + Power Supply Control Functions
  *           + Low Power Control Functions
  *           + Voltage Monitoring Functions
  *           + Memories Retention Functions
  *           + I/O Pull-Up Pull-Down Configuration Functions
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
      (++) Voltage scaling can be one of the following values :
             (+++) voltage output scale 1 :
                   => Used when system clock frequency is up to 100 MHz
             (+++) voltage output scale 2 :

   (#) Call HAL_PWREx_EnableFastSoftStart() and HAL_PWREx_DisableFastSoftStart()
       to enable / disable the fast software startup for the current regulator.

   (#) Call HAL_PWREx_EnableBatteryCharging() and
       HAL_PWREx_DisableBatteryCharging() functions to enable and disable the
       battery charging feature with the selected resistor.

   (#) Call HAL_PWREx_EnterSHUTDOWNMode() function to enter the whole system in
       Shutdown mode. Wake-up from Shutdown mode can be following to an external
       reset (NRST pin), a WKUP line event, or an RTC event occurs
       (alarm, periodic wakeup, timestamp), or a tamper detection.

   (#) Call HAL_PWREx_EnableUltraLowPowerMode() and
       HAL_PWREx_DisableUltraLowPowerMode() to enable / disable the BOR ultra
       low power mode.

   (#) Call HAL_PWREx_EnableSRAM1ContentStandbyRetention() and
       HAL_PWREx_DisableSRAM1ContentStandbyRetention() to
       enable / disable the SRAM1 content retention in Standby low
       power mode.

   (#) Call HAL_PWREx_EnableSRAM2ContentStandbyRetention() and
       HAL_PWREx_DisableSRAM2ContentStandbyRetention() to
       enable / disable the SRAM2 pages content retention in Standby mode.

   (#) Call HAL_PWREx_EnableRAMsContentStopRetention() and
       HAL_PWREx_DisableRAMsContentStopRetention() to
       enable / disable the RAMs content retention in Stop mode (Stop 0/1/2/3).
       (++) Retained RAM can be one of the following RAMs :
             (+++) SRAM1
             (+++) SRAM2
             (+++) ICACHE SRAM
             (+++) FDCAN & USB SRAM
             (+++) PKA SRAM

   (#) Call HAL_PWREx_EnableFlashFastWakeUp() and
       HAL_PWREx_DisableFlashFastWakeUp() to enable / disable the flash memory
       fast wakeup from Stop mode (Stop 0/1).

   (#) Call HAL_PWREx_EnableSRAMFastWakeUp() and
       HAL_PWREx_DisableSRAMFastWakeUp() to enable / disable the SRAM memories
       fast wakeup from Stop mode (Stop 0/1).

   (#) Call HAL_PWREx_EnableStandbyIORetention() and HAL_PWREx_DisableStandbyIORetention()
       to enable / disable the IO state retention while in Standby mode.

   (#) Call HAL_PWREx_GetStandbyIORetentionStatus() to retrieve for a given port for which
       IO the state was retained while in Standby mode.

   (#) Call HAL_PWREx_DisableStandbyRetainedIOState() to disable the IO state retained in
       Standby mode.

   (#) Call HAL_PWREx_ConfigSupply() to Configure the system Power Supply.

   (#) Call HAL_PWREx_EnableVddUSB() and HAL_PWREx_DisableVddUSB()
       functions to enable and disable the VDDUSB supply valid.

   (#) Call HAL_PWREx_EnableVddIO2() and HAL_PWREx_DisableVddIO2()
       functions to enable and disable the VDDIO2 supply valid.
       (+) This feature is available only for STM32U375xx, STM32U385xx devices.

   (#) Call HAL_PWREx_EnableVddA() and HAL_PWREx_DisableVddA()
       functions to enable and disable the VDDA supply valid.

   (#) Call HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() to
       apply respectively pull-up and pull-down to selected I/O.
       Call HAL_PWREx_DisableGPIOPullUp() and HAL_PWREx_DisableGPIOPullDown() to
       disable applied respectively pull-up and pull-down to selected I/O.

   (#) Call HAL_PWREx_EnablePullUpPullDownConfig() and
       HAL_PWREx_DisablePullUpPullDownConfig() to I/O enable / disable pull-up
       and pull-down configuration.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief    PWR Extended HAL module driver
  * @{
  */

#if defined (HAL_PWR_MODULE_ENABLED)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */
/*!< Time out value of flags setting */
#define PWR_VOSF_SETTING_DELAY_VALUE   (0x32U)                                 /*!< Time out value for VOSF flag setting */
#define PWR_MODE_CHANGE_DELAY_VALUE    (0x32U)                                 /*!< Time out for step down converter operating mode */
#define BOOSTER_TIMEOUT_VALUE          (1U)                                    /*!< Timeout for booster ready : 1ms */

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
      (+) The STM32U3 series devices embed two regulators : one LDO (linear
          voltage regulator) and one SMPS (step down converter) in parallel to
          provide the VCORE supply for digital peripherals, SRAM1, SRAM2 and
          embedded Flash memory.

      (+) The SMPS allows the power consumption to be reduced but some
          peripherals can be perturbed by the noise generated by the SMPS,
          requiring the application to switch to LDO when running this
          peripheral in order to reach the best performances.

      (+) The LDO and the SMPS regulators have two modes: Main regulator mode
          (used when performance is needed), and Low-power regulator mode. LDO
          or SMPS can be used in all voltage scaling ranges, and in all Stop
          and Standby with retention modes.

      (+) After reset, the regulator is the LDO, in Range 2. Switching to SMPS
          provides lower consumption in particular at high VDD voltage. It is
          possible to switch from LDO to SMPS, or from SMPS to LDO on the fly in
          any range, by configuring the REGSEL bit. It is recommended to switch
          first to SMPS before changing the voltage range.

      (+) When exiting from Stop or Standby retention modes, the regulator is the
          same than when entering these low-power modes.

      (+) When exiting from Standby modes, the LDO regulator is always used. When Standby
          has been entered from the SMPS regulator, after exiting standby with the LDO,
          the regulator is subsequently switched to SMPS regulator.

      (+) When exiting from Stop 0 modes the voltage range is the same as on entering Stop 0
          mode. When exiting from Stop 1, Stop 2, Stop 3 and Standby modes the voltage range 2 is used.

      (+) Both regulators can provide four different voltages (voltage scaling)
          and can operate in Stop modes.
          Voltage scaling ranges can be one of the following values :
             (++) voltage output scale 1 :
                  => Used when system clock frequency is up to 100 MHz
             (++) voltage output scale 2 :
                  => Used when system clock frequency is up to 16 MHz


    *** VBAT charging ***
    =====================
    [..]
      When VDD is present, it is possible to charge the external battery on VBAT
      through an internal resistance.
      The VBAT charging is done either through a 5 kOhm resistor or through a 1.5
      kOhm resistor depending on the VBRS bit value in the PWR_BDCR register.
      The battery charging is enabled by setting VBE bit in the PWR_BDCR
      register. It is automatically disabled in VBAT mode.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the main internal regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  * @param  VoltageScaling : Specifies the regulator output voltage scale.
  *                          This parameter can be one of the following values :
  *                          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 : Regulator voltage output range 1.
  *                                                                   Used when system clock frequency is up to 100 MHz.
  *                          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 : Regulator voltage output range 2.
  *                                                                   Used when system clock frequency is up to 16 MHz.
  * @note   Before moving to voltage scaling 2, it is mandatory to ensure that
  *         the system frequency is equal or below 16 MHz.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t timeout;
  uint32_t vosr;

  /* Check the parameter */
  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

  /* Set voltage scaling level */
  vosr = (PWR->VOSR & ~(PWR_VOSR_R2EN | PWR_VOSR_R1EN));
  vosr |= VoltageScaling;
  PWR->VOSR = vosr;

  /* Wait until VOSRDY is set */
  timeout = ((PWR_VOSF_SETTING_DELAY_VALUE * SystemCoreClock) / 1000000U) + 1U;

  /* store expected ready flag */
  vosr = (VoltageScaling << (PWR_VOSR_R1RDY_Pos - PWR_VOSR_R1EN_Pos));

  while (((PWR->VOSR & vosr) != vosr) && (timeout != 0U))
  {
    timeout--;
  }

  /* Check time out */
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  Return voltage scaling range.
  * @retval Applied voltage scaling value.
  *         This parameter can be one of the following values:
  *         @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 : Regulator voltage output range 1.
  *         @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 : Regulator voltage output range 2.
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return ((PWR->VOSR & (PWR_VOSR_R1RDY | PWR_VOSR_R2RDY)) >> (PWR_VOSR_R1RDY_Pos - PWR_VOSR_R1EN_Pos));
}

/**
  * @brief  Enable VDDUSB supply.
  * @note   Remove VDDUSB electrical and logical isolation, once VDDUSB supply
  *         is present for consumption saving.
  * @retval None.
  */
void HAL_PWREx_EnableVddUSB(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

/**
  * @brief  Disable VDDUSB supply.
  * @retval None.
  */
void HAL_PWREx_DisableVddUSB(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

#if defined(PWR_SVMCR_IO2SV)
/**
  * @brief  Enable VDDIO2 supply valid.
  * @note   Setting this bit is mandatory to use PG[15:2] I/Os.
  * @retval None.
  */
void HAL_PWREx_EnableVddIO2(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}

/**
  * @brief  Disable VDDIO2 supply valid.
  * @retval None.
  */
void HAL_PWREx_DisableVddIO2(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}
#endif /* PWR_SVMCR_IO2SV */

/**
  * @brief  Enable VDDA supply valid.
  * @note   Setting this bit is mandatory to use the analog peripherals.
  * @retval None.
  */
void HAL_PWREx_EnableVddA(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Disable VDDA supply valid.
  * @retval None.
  */
void HAL_PWREx_DisableVddA(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Enable EPOD booster
  * @note   EPOD booster shall be enabled prior to increase system frequency above 24 MHz in all ranges.
  * @note   EPOD Booster clock source and divider shall be configured through RCC before calling this function.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableEpodBooster(void)
{
  uint32_t tickstart;

  /* Set EPOD booster bit */
  PWR->VOSR |= PWR_VOSR_BOOSTEN;

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till boster ready bit is set */
  while (READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY) != PWR_VOSR_BOOSTRDY)
  {
    if ((HAL_GetTick() - tickstart) > BOOSTER_TIMEOUT_VALUE)
    {
      if (READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY) != PWR_VOSR_BOOSTRDY)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Booster is enabled and ready */
  return HAL_OK;
}

/**
  * @brief  Disable EPOD booster
  * @note   EPOD booster shall be disabled when decreasing system frequency below 24 MHz in all ranges to save power
  *         consumption.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableEpodBooster(void)
{
  uint32_t tickstart;

  /* Disable EPOD booster bit */
  PWR->VOSR &= ~PWR_VOSR_BOOSTEN;

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till boster ready bit is reset */
  while (READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > BOOSTER_TIMEOUT_VALUE)
    {
      if (READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY) != 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Booster is disabled */
  return HAL_OK;
}

#if defined(PWR_CR3_REGSEL)
/**
  * @brief  Configure the system Power Supply.
  * @param  SupplySource : Specifies the Power Supply source.
  *                        This parameter can be one of the following values :
  *                        @arg PWR_LDO_SUPPLY  : The LDO regulator supplies the Vcore Power Domains.
  *                        @arg PWR_SMPS_SUPPLY : The SMPS regulator supplies the Vcore Power Domains.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource)
{
  uint32_t timeout;

  /* Check the parameter */
  assert_param(IS_PWR_SUPPLY(SupplySource));

  /* Set maximum time out */
  timeout = ((PWR_MODE_CHANGE_DELAY_VALUE * SystemCoreClock) / 1000000U) + 1U;

  /* Configure the LDO as system regulator supply  */
  if (SupplySource == PWR_LDO_SUPPLY)
  {
    /* Set the power supply configuration */
    CLEAR_BIT(PWR->CR3, PWR_CR3_REGSEL);

    /* Wait until system switch on new regulator */
    while (HAL_IS_BIT_SET(PWR->SVMSR, PWR_SVMSR_REGS) && (timeout != 0U))
    {
      timeout--;
    }
  }
  /* Configure the SMPS as system regulator supply  */
  else
  {
    /* Set the power supply configuration */
    SET_BIT(PWR->CR3, PWR_CR3_REGSEL);

    /* Wait until system switch on new regulator */
    while (HAL_IS_BIT_CLR(PWR->SVMSR, PWR_SVMSR_REGS) && (timeout != 0U))
    {
      timeout--;
    }
  }

  /* Check time out  */
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief  Get the power supply configuration.
  * @retval The supply configured.
  */
uint32_t  HAL_PWREx_GetSupplyConfig(void)
{
  return (PWR->SVMSR & PWR_SVMSR_REGS);
}
#endif /* defined(PWR_CR3_REGSEL) */

/**
  * @brief  Enable fast soft start for the current regulator.
  * @retval None.
  */
void HAL_PWREx_EnableFastSoftStart(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Disable fast soft start for the current regulator.
  * @retval None.
  */
void HAL_PWREx_DisableFastSoftStart(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Enable the Battery charging.
  * @note   When VDD is present, charge the external battery through an internal
  *         resistor.
  * @param  ResistorValue : Specifies the charging resistor.
  *                         This parameter can be one of the following values :
  *                         @arg PWR_BATTERY_CHARGING_RESISTOR_5   : 5 KOhm resistor.
  *                         @arg PWR_BATTERY_CHARGING_RESISTOR_1_5 : 1.5 KOhm resistor.
  * @retval None.
  */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorValue)
{
  /* Check the parameter */
  assert_param(IS_PWR_BATTERY_RESISTOR_SELECT(ResistorValue));

  /* Specify the charging resistor and enable the Battery charging */
  MODIFY_REG(PWR->BDCR, (PWR_BDCR_VBRS | PWR_BDCR_VBE), (ResistorValue | PWR_BDCR_VBE));

}

/**
  * @brief  Disable the Battery charging.
  * @retval None.
  */
void HAL_PWREx_DisableBatteryCharging(void)
{
  /* Disable the Battery charging and restore default charging resistor value */
  CLEAR_BIT(PWR->BDCR, (PWR_BDCR_VBRS | PWR_BDCR_VBE));
}
/**
  * @}
  */


/** @defgroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @brief    Low power control functions
  */

/**
  * @brief  Enter the whole system to Shutdown mode.
  * @note   Shutdown mode allows the lowest power consumption. The internal
  *         regulator is switched off so that the VCORE domain is powered off.
  *         The PLL, the HSI16, the MSI (MSIS and MSIK), the LSI and the HSE
  *         oscillators are also switched off.
  * @note   The SRAMs and register contents are lost except for registers in the
  *         Backup domain. The BOR is not available in Shutdown mode. No power
  *         voltage monitoring is possible in this mode, therefore the switch to
  *         Backup domain is not supported.
  * @retval None.
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{
  /* Set Shutdown mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, (PWR_CR1_LPMS_1 | PWR_CR1_LPMS_2));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief  Enable BOR and PVD ultra-low power mode.
  * @note   BOR and PVD operations can be in discontinuous (ultra-low power) mode in
  *         Standby modes.
  * @note   This bit must be set to reach the lowest power consumption in the low-power modes.
  * @note   This bit shall not be set together with autonomous peripherals using HSI16
  *         as kernel clock.
  * @retval None.
  */
void HAL_PWREx_EnableUltraLowPowerMode(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Disable BOR and PVD ultra-low power mode.
  * @retval None.
  */
void HAL_PWREx_DisableUltraLowPowerMode(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}
/**
  * @}
  */


/** @defgroup PWREx_Exported_Functions_Group3 Memories Retention Functions
  * @brief    Memories retention functions
  *
@verbatim
 ===============================================================================
                     ##### Memories Retention Functions #####
 ===============================================================================
    [..]
      Devices RAMs are configurable to reduce the consumption by powering off the SRAMi.
       (+) SRAM power down are :
             (++) SRAM1
             (++) SRAM2

    [..]
      Devices RAMs are configurable to retain or lose RAMs content
      during Stop mode (Stop 0/1/2/3).
       (+) Retained content RAMs in Stop modes are :
             (++) SRAM1
             (++) SRAM2
             (++) ICACHE
             (++) PKA SRAM
             (++) FDCAN and USB peripherals SRAM

    [..]
      Devices RAMs are configurable to retain or lose RAMs content
      in Standby mode.
       (+) Retained content RAMs in Standby mode are :
             (++) SRAM2

@endverbatim
  * @{
  */

/**
  * @brief  Enable RAMs power down.
  * @note   This bit is used to reduce the consumption by powering off the SRAMi.
  * @param RAMSelection: Specifies RAMs.
  *                      This parameter can be one of the following values :
  *                      @arg PWR_SRAM1_POWERDOWN  : SRAM1 powered off.
  *                      @arg PWR_SRAM2_POWERDOWN  : SRAM2 powered off.
  * @retval None.
  */
void HAL_PWREx_EnableRAMsPowerDown(uint32_t RAMSelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_RAM_POWERDOWN(RAMSelection));

  /* SRAMi powered off */
  SET_BIT(PWR->CR1, RAMSelection);
}

/**
  * @brief  Disable RAMs power down.
  * @note   When this bit is cleared to 0, wait for more than 1.6us before accessing the SRAM.
  * @param RAMSelection: Specifies RAMs .
  *                      This parameter can be one of the following values :
  *                      @arg PWR_SRAM1_POWERDOWN  : SRAM1 powered on.
  *                      @arg PWR_SRAM2_POWERDOWN  : SRAM2 powered on.
  * @retval None.
  */
void HAL_PWREx_DisableRAMsPowerDown(uint32_t RAMSelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_RAM_POWERDOWN(RAMSelection));

  /* SRAMi powered on */
  CLEAR_BIT(PWR->CR1, RAMSelection);
}

/**
  * @brief Enable RAMs content retention in Stop mode (Stop 0, 1, 2, 3).
  * @note  When enabling content retention for a given ram, memory is kept powered
  *        on in Stop mode. (Consumption is not optimized)
  * @param RAMSelection: Specifies RAMs content to be retained in Stop mode.
  *                      This parameter can be one or a combination of the following values :
  *                      @arg PWR_SRAM1_PAGE1_STOP_RETENTION : SRAM1 page 1 retention.
  *                      @arg PWR_SRAM1_PAGE2_STOP_RETENTION : SRAM1 page 2 retention.
  *                      @arg PWR_SRAM1_PAGE3_STOP_RETENTION : SRAM1 page 3 retention.
  *                      @arg PWR_SRAM1_PAGE4_STOP_RETENTION : SRAM1 page 4 retention.
  *                      @arg PWR_SRAM1_PAGE5_STOP_RETENTION : SRAM1 page 5 retention.
#if defined(PWR_CR2_SRAM1PDS6)
  *                      @arg PWR_SRAM1_PAGE6_STOP_RETENTION : SRAM1 page 6 retention.
  *                      @arg PWR_SRAM1_PAGE7_STOP_RETENTION : SRAM1 page 7 retention.
#endif
  *                      @arg PWR_SRAM1_FULL_STOP_RETENTION  : SRAM1 full retention.
  *                      @arg PWR_SRAM2_PAGE1_STOP_RETENTION : SRAM2 page 1 retention.
  *                      @arg PWR_SRAM2_PAGE2_STOP_RETENTION : SRAM2 page 2 retention.
  *                      @arg PWR_SRAM2_PAGE3_STOP_RETENTION : SRAM2 page 3 retention.
  *                      @arg PWR_SRAM2_FULL_STOP_RETENTION  : SRAM2 full retention.
  *                      @arg PWR_ICACHE_STOP_RETENTION      : I-CACHE SRAM retention.
  *                      @arg PWR_FDCAN_USB_STOP_RETENTION   : FDCAN & USB SRAM retention.
  *                      @arg PWR_PKA_STOP_RETENTION         : PKA SRAM retention.
  * @retval None.
  */
void HAL_PWREx_EnableRAMsContentStopRetention(uint32_t RAMSelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_RAM_STOP_RETENTION(RAMSelection));

  /* Enable RAM retention in Stop mode */
  CLEAR_BIT(PWR->CR2, RAMSelection);
}

/**
  * @brief Disable RAMs content retention in Stop mode (Stop 0, 1, 2, 3).
  * @note  When disabling content retention for a given RAM, memory is
  *        powered down in Stop mode. (Consumption is optimized)
  * @param RAMSelection: Specifies RAMs content to be lost in Stop mode.
  *                      This parameter can be one or a combination of the following values :
  *                      @arg PWR_SRAM1_PAGE1_STOP_RETENTION : SRAM1 page 1 retention.
  *                      @arg PWR_SRAM1_PAGE2_STOP_RETENTION : SRAM1 page 2 retention.
  *                      @arg PWR_SRAM1_PAGE3_STOP_RETENTION : SRAM1 page 3 retention.
  *                      @arg PWR_SRAM1_PAGE4_STOP_RETENTION : SRAM1 page 4 retention.
  *                      @arg PWR_SRAM1_PAGE5_STOP_RETENTION : SRAM1 page 5 retention.
#if defined(PWR_CR2_SRAM1PDS6)
  *                      @arg PWR_SRAM1_PAGE6_STOP_RETENTION : SRAM1 page 6 retention.
  *                      @arg PWR_SRAM1_PAGE7_STOP_RETENTION : SRAM1 page 7 retention.
#endif
  *                      @arg PWR_SRAM1_FULL_STOP_RETENTION  : SRAM1 full retention.
  *                      @arg PWR_SRAM2_PAGE1_STOP_RETENTION : SRAM2 page 1 retention.
  *                      @arg PWR_SRAM2_PAGE2_STOP_RETENTION : SRAM2 page 2 retention.
  *                      @arg PWR_SRAM2_PAGE3_STOP_RETENTION : SRAM2 page 3 retention.
  *                      @arg PWR_SRAM2_FULL_STOP_RETENTION  : SRAM2 full retention.
  *                      @arg PWR_ICACHE_STOP_RETENTION      : I-CACHE SRAM retention.
  *                      @arg PWR_FDCAN_USB_STOP_RETENTION   : FDCAN & USB SRAM retention.
  *                      @arg PWR_PKA_STOP_RETENTION         : PKA SRAM retention.
  * @retval None.
  */
void HAL_PWREx_DisableRAMsContentStopRetention(uint32_t RAMSelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_RAM_STOP_RETENTION(RAMSelection));

  /* Disable RAM retention in Stop mode */
  SET_BIT(PWR->CR2, RAMSelection);
}

/**
  * @brief  Enable SRAM2 content retention in Standby mode.
  * @param  SRAM2Pages : Specifies the SRAM2 pages.
  *                      This parameter can be combination of the following values :
  *                      @arg PWR_SRAM2_PAGE1_STANDBY_RETENTION : SRAM2 page 1 retention.
  *                      @arg PWR_SRAM2_PAGE2_STANDBY_RETENTION : SRAM2 page 2 retention.
  *                      @arg PWR_SRAM2_PAGE3_STANDBY_RETENTION : SRAM2 page 3 retention.
  *                      @arg PWR_SRAM2_FULL_STANDBY_RETENTION  : SRAM2 full retention.
  * @retval None.
  */
void HAL_PWREx_EnableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages)
{
  /* Check the parameters */
  assert_param(IS_PWR_SRAM2_STANDBY_RETENTION(SRAM2Pages));

  MODIFY_REG(PWR->CR1, PWR_ALL_RAM_STANDBY_RETENTION_MASK, SRAM2Pages);
}

/**
  * @brief  Disable SRAM2 content retention in Standby mode.
  * @param  SRAM2Pages : Specifies the SRAM2 pages.
  *                      This parameter can be combination of the following values :
  *                      @arg PWR_SRAM2_PAGE1_STANDBY_RETENTION : SRAM2 page 1 retention.
  *                      @arg PWR_SRAM2_PAGE2_STANDBY_RETENTION : SRAM2 page 2 retention.
  *                      @arg PWR_SRAM2_PAGE3_STANDBY_RETENTION : SRAM2 page 3 retention.
  *                      @arg PWR_SRAM2_FULL_STANDBY_RETENTION  : SRAM2 full retention.
  * @retval None.
  */
void HAL_PWREx_DisableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages)
{
  /* Check the parameters */
  assert_param(IS_PWR_SRAM2_STANDBY_RETENTION(SRAM2Pages));

  CLEAR_BIT(PWR->CR1, SRAM2Pages);
}

/**
  * @brief  Enable the flash memory fast wakeup from Stop 0 and Stop 1 modes.
  * @note   This feature is used to obtain the best trade-off between low-power
  *         consumption and wakeup time when exiting the Stop 0 or Stop 1 modes.
  *         When this feature is enabled, the Flash memory remains in normal
  *         mode in Stop 0 and Stop 1 modes, which offers a faster startup time
  *         with higher consumption.
  * @retval None.
  */
void HAL_PWREx_EnableFlashFastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Disable the Flash Power Down in Stop mode.
  * @note   This feature is used to obtain the best trade-off between low-power
  *         consumption and wakeup time when exiting the Stop 0 or Stop 1 modes.
  *         When this feature is disabled, the Flash memory enters low-power
  *         mode in Stop 0 and Stop 1 modes, which causes a slower startup time
  *         with lower consumption.
  * @retval None.
  */
void HAL_PWREx_DisableFlashFastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Enable the SRAM memory fast wakeup from Stop 0 and Stop 1 modes.
  * @note   This bit is used to obtain the best trade-off between low-power consumption
  *         and wakeup time.
  * @retval None.
  */
void HAL_PWREx_EnableSRAMFastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_SRAMFWU);
}

/**
  * @brief  Disable the SRAM memory fast wakeup from Stop 0 and Stop 1 modes.
  * @note   This bit is used to obtain the best trade-off between low-power consumption
  *         and wakeup time.
  * @retval None.
  */
void HAL_PWREx_DisableSRAMFastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_SRAMFWU);
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group4 I/O Pull-Up Pull-Down Configuration Functions
  * @brief    I/O pull-up / pull-down configuration functions
  *
@verbatim
 ===============================================================================
                     ##### IOs configuration functions #####
 ===============================================================================
    [..]
      In Standby and Shutdown mode, pull up and pull down can be configured to
      maintain an I/O in the selected state. If the APC bit in the PWR_APCR
      register is set, the I/Os can be configured either with a pull-up through
      PWR_PUCRx registers (x=A,B,C,D,E,G,H), or with a pull-down through
      PWR_PDCRx registers (x=A,B,C,D,E,G,H), or can be kept in analog state
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
  * @brief  Enable pull-up and pull-down configuration.
  * @note   When APC bit is set, the I/O pull-up and pull-down configurations
  *         defined in PWR_PUCRx and PWR_PDCRx registers are applied in Stop 3,
  *         Standby and Shutdown modes.
  * @note   Pull-up set by PUy bit of PWR_PUCRx register is not activated if the
  *         corresponding PDy bit of PWR_PDCRx register is also set (pull-down
  *         configuration priority is higher). HAL_PWREx_EnableGPIOPullUp() and
  *         HAL_PWREx_EnableGPIOPullDown() API's ensure there is no conflict
  *         when setting PUy or PDy bit.
  * @retval None.
  */
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration.
  * @note   When APC bit is cleared, the I/O pull-up and pull-down configurations
  *         defined in PWR_PUCRx and PWR_PDCRx registers are not applied in Stop 3,
  *         Standby and Shutdown modes.
  * @retval None.
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Enable GPIO pull-up state in Stop 3, Standby and Shutdown modes.
  * @note   Set the relevant PUy bits of PWR_PUCRx register to configure the I/O
  *         in pull-up state in Stop 3, Standby and Shutdown modes.
  * @note   This state is effective in Stop 3, Standby and Shutdown modes only if APC
  *         bit is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is lost when exiting the Shutdown mode due to the
  *         power-on reset, maintained when exiting the Standby mode.
  * @note   To avoid any conflict at Standby and Shutdown modes exits, the
  *         corresponding PDy bit of PWR_PDCRx register is cleared unless it is
  *         reserved.
  * @note   Even if a PUy bit to set is reserved, the other PUy bits entered as
  *         input parameter at the same time are set.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Apply Pull Up to GPIO port A */
      SET_BIT(PWR->PUCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_14))));
      CLEAR_BIT(PWR->PDCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      break;

    case PWR_GPIO_B: /* Apply Pull Up to GPIO port B */
      SET_BIT(PWR->PUCRB, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRB, (GPIO_Pin & (~(PWR_GPIO_BIT_4))));
      break;

    case PWR_GPIO_C: /* Apply Pull Up to GPIO port C */
      SET_BIT(PWR->PUCRC, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Apply Pull Up to GPIO port D */
      SET_BIT(PWR->PUCRD, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Apply Pull Up to GPIO port E */
      SET_BIT(PWR->PUCRE, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRE, GPIO_Pin);
      break;

#if defined(PWR_GPIO_F)
    case PWR_GPIO_F: /* Apply Pull Up to GPIO port F */
      SET_BIT(PWR->PUCRF, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRF, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_F) */

#if defined(PWR_GPIO_G)
    case PWR_GPIO_G: /* Apply Pull Up to GPIO port G */
      SET_BIT(PWR->PUCRG, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRG, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_G) */

    case PWR_GPIO_H: /* Apply Pull Up to GPIO port H */
      SET_BIT(PWR->PUCRH, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRH, GPIO_Pin);
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Disable GPIO pull-up state in Stop 3, Standby mode and Shutdown modes.
  * @note   Reset the relevant PUy bits of PWR_PUCRx register used to configure
  *         the I/O in pull-up state in Stop 3, Standby and Shutdown modes.
  * @note   Even if a PUy bit to reset is reserved, the other PUy bits entered as
  *         input parameter at the same time are reset.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Disable Pull Up for GPIO port A */
      CLEAR_BIT(PWR->PUCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_14))));
      break;

    case PWR_GPIO_B: /* Disable Pull Up for GPIO port B */
      CLEAR_BIT(PWR->PUCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C: /* Disable Pull Up for GPIO port C */
      CLEAR_BIT(PWR->PUCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Disable Pull Up for GPIO port D */
      CLEAR_BIT(PWR->PUCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Disable Pull Up for GPIO port E */
      CLEAR_BIT(PWR->PUCRE, GPIO_Pin);
      break;

#if defined(PWR_GPIO_F)
    case PWR_GPIO_F: /* Disable Pull Up for GPIO port F */
      CLEAR_BIT(PWR->PUCRF, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_F) */

#if defined(PWR_GPIO_G)
    case PWR_GPIO_G: /* Disable Pull Up for GPIO port G */
      CLEAR_BIT(PWR->PUCRG, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_G) */

    case PWR_GPIO_H: /* Disable Pull Up for GPIO port H */
      CLEAR_BIT(PWR->PUCRH, GPIO_Pin);
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Enable GPIO pull-down state in Stop 3, Standby and Shutdown modes.
  * @note   Set the relevant PDy bits of PWR_PDCRx register to configure the I/O
  *         in pull-down state in Stop 3, Standby and Shutdown modes.
  * @note   This state is effective in Standby and Shutdown modes only if APC bit
  *         is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is lost when exiting the Shutdown mode due to the
  *         power-on reset, maintained when exiting the Standby mode.
  * @note   To avoid any conflict at Standby and Shutdown modes exits, the
  *         corresponding PUy bit of PWR_PUCRx register is cleared unless it is
  *         reserved.
  * @note   Even if a PDy bit to set is reserved, the other PDy bits entered as
  *         input parameter at the same time are set.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Apply Pull Down to GPIO port A */
      SET_BIT(PWR->PDCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      CLEAR_BIT(PWR->PUCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_14))));
      break;

    case PWR_GPIO_B: /* Apply Pull Down to GPIO port B */
      SET_BIT(PWR->PDCRB, (GPIO_Pin & (~(PWR_GPIO_BIT_4))));
      CLEAR_BIT(PWR->PUCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C: /* Apply Pull Down to GPIO port C */
      SET_BIT(PWR->PDCRC, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Apply Pull Down to GPIO port D */
      SET_BIT(PWR->PDCRD, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Apply Pull Down to GPIO port E */
      SET_BIT(PWR->PDCRE, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRE, GPIO_Pin);
      break;

#if defined(PWR_GPIO_F)
    case PWR_GPIO_F: /* Apply Pull Down to GPIO port F */
      SET_BIT(PWR->PDCRF, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRF, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_F) */

#if defined(PWR_GPIO_G)
    case PWR_GPIO_G: /* Apply Pull Down to GPIO port G */
      SET_BIT(PWR->PDCRG, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRG, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_G) */

    case PWR_GPIO_H: /* Apply Pull Down to GPIO port H */
      SET_BIT(PWR->PDCRH, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRH, GPIO_Pin);
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Disable GPIO pull-down state in Stop 3, Standby and Shutdown modes.
  * @note   Reset the relevant PDy bits of PWR_PDCRx register used to configure the I/O
  *         in pull-down state in Stop 3, Standby and Shutdown modes.
  * @note   Even if a PDy bit to reset is reserved, the other PDy bits entered as input
  *         parameter at the same time are reset.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Disable Pull Down for GPIO port A */
      CLEAR_BIT(PWR->PDCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      break;

    case PWR_GPIO_B: /* Disable Pull Down for GPIO port B */
      CLEAR_BIT(PWR->PDCRB, (GPIO_Pin & (~(PWR_GPIO_BIT_4))));
      break;

    case PWR_GPIO_C: /* Disable Pull Down for GPIO port C */
      CLEAR_BIT(PWR->PDCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Disable Pull Down for GPIO port D */
      CLEAR_BIT(PWR->PDCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Disable Pull Down for GPIO port E */
      CLEAR_BIT(PWR->PDCRE, GPIO_Pin);
      break;

#if defined(PWR_GPIO_F)
    case PWR_GPIO_F: /* Disable Pull Down for GPIO port F */
      CLEAR_BIT(PWR->PDCRF, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_F) */

#if defined(PWR_GPIO_G)
    case PWR_GPIO_G: /* Disable Pull Down for GPIO port G */
      CLEAR_BIT(PWR->PDCRG, GPIO_Pin);
      break;
#endif /* defined(PWR_GPIO_G) */

    case PWR_GPIO_H: /* Disable Pull Down for GPIO port H */
      CLEAR_BIT(PWR->PDCRH, GPIO_Pin);
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group5 I3C Pull-Up Configuration Functions
  * @brief    I3C pull-up configuration functions
  *
@verbatim
 ===============================================================================
                     ##### I3C Pull-Up Configuration functions #####
 ===============================================================================
    [..]
      In Stop modes(2,3), Standby and Shutdown mode, I3C pull-up can be configured to
      maintain an I/O in the pull-up state. The I/Os can be configured through
      PWR_I3CPUCRx registers (x=1,2), or with a pull-down through
      PWR_PDCRx registers (x=A,B,C,D,E,G,H), or can be kept in analog state.

@endverbatim
  * @{
  */

/**
  * @brief  Enable I3C pull-up state in Stop (2, 3), Standby and Shutdown modes.
  * @note   After exiting Stop mode, the I3C pull-up control bits must be cleared
  *         to let I3C peripheral controls I/O pull-up activation.
  * @note   After exiting Standby mode, and after I3C initialization is done,
  *         the I3C pull-up control bits must be cleared, to let I3C peripheral
  *         controls I/O pull-up activation.
  * @note   After exiting Standby mode, and after I3C initialization is done,
  *         the I3C pull-up control bits must be cleared, to let I3C peripheral
  *         controls I/O pull-up activation.
  * @param  Gpio : Specify the I/O pin.
  *                     This parameter can be a value of
  *                     @ref PWREx_I3C_PULLUP_GPIO.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableI3CPullUp(uint32_t Gpio)
{
  /* Check the parameters */
  assert_param(IS_PWR_I3C_PULLUP_GPIO(Gpio));

  if ((Gpio & 0xFFFFU) != 0U)
  {
    SET_BIT(PWR->I3CPUCR1, (Gpio & 0xFFFFU));
  }

  if (((Gpio >> PWR_I3CUPCR2_OFFSET) & 0xFFFFU) != 0U)
  {
    SET_BIT(PWR->I3CPUCR2, ((Gpio >> PWR_I3CUPCR2_OFFSET) & 0xFFFFU));
  }

  return HAL_OK;
}

/**
  * @brief  Disable I3C pull-up state in Stop (2, 3), Standby and Shutdown modes.
  * @param  Gpio : Specify the I/O pin.
  *                     This parameter can be a value of
  *                     @ref PWREx_I3C_PULLUP_GPIO.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableI3CPullUp(uint32_t Gpio)
{
  /* Check the parameters */
  assert_param(IS_PWR_I3C_PULLUP_GPIO(Gpio));

  if ((Gpio & 0xFFFFU) != 0U)
  {
    CLEAR_BIT(PWR->I3CPUCR1, (Gpio & 0xFFFFU));
  }

  if (((Gpio >> PWR_I3CUPCR2_OFFSET) & 0xFFFFU) != 0U)
  {
    CLEAR_BIT(PWR->I3CPUCR2, ((Gpio >> PWR_I3CUPCR2_OFFSET) & 0xFFFFU));
  }

  return HAL_OK;
}
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

/**
  * @}
  */
