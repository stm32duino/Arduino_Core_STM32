/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller extension peripheral :
  *           + Power Supply Control Functions
  *           + Low Power Control Functions
  *           + Voltage Monitoring Functions
  *           + Memories Retention Functions
  *           + I/O Retention Functions
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
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Call HAL_PWREx_ControlVoltageScaling() and HAL_PWREx_GetVoltageRange() to
       set / get the voltage scaling range.
      (+) Voltage scaling can be one of the following values :
             (++) voltage output scale 1 :
                  => Used when system clock frequency is up to 100 MHz
             (++) voltage output scale 2 :
                  => Used when system clock frequency is up to 16 MHz

   (#) Call HAL_PWREx_EnableUltraLowPowerMode() and
       HAL_PWREx_DisableUltraLowPowerMode() to enable / disable the BOR ultra
       low power mode.

   (#) Call HAL_PWREx_EnableSRAM1ContentStandbyRetention() and
       HAL_PWREx_DisableSRAM1ContentStandbyRetention() to
       enable / disable the SRAM1 content retention in Standby low
       power mode.

   (#) Call HAL_PWREx_EnableSRAM2ContentStandbyRetention() and
       HAL_PWREx_DisableSRAM2ContentStandbyRetention() to
       enable / disable the SRAM2 content retention in Standby low
       power mode.

   (#) Call HAL_PWREx_EnableRAMsContentStopRetention() and
       HAL_PWREx_DisableRAMsContentStopRetention() to
       enable / disable the RAMs content retention in Stop mode (Stop 0/1).
       (+) Retained RAM can be one of the following RAMs :
             (++) SRAM1
             (++) SRAM2
             (++) ICACHE

   (#) Call HAL_PWREx_EnableFlashFastWakeUp() and
       HAL_PWREx_DisableFlashFastWakeUp() to enable / disable the flash memory
       fast wakeup from Stop mode (Stop 0/1).

   (#) Call HAL_PWREx_EnableStandbyIORetention() and HAL_PWREx_DisableStandbyIORetention()
       to enable / disable the IO state retention while in Standby mode.

   (#) Call HAL_PWREx_GetStandbyIORetentionStatus() to retrieve for a given port for which
       IO the state was retained while in Standby mode.

   (#) Call HAL_PWREx_DisableStandbyRetainedIOState() to disable the IO state retained in
       Standby mode.

   (#) Call HAL_PWREx_ConfigSupply to Configure the system Power Supply.

   (#) Call HAL_PWREx_GetRADIOOperatingMode to get the 2.4 GHz RADIO operating mode.

   (#) Call HAL_PWREx_GetRADIOPHYOperatingModeto get the 2.4 GHz RADIO PHY operating mode.

   (#) Call HAL_PWREx_GetRADIOEncryptionOperatingMode to get the radio encryption mode.

   (#) Call HAL_PWREx_GetRFVDDHPA to get the 2.4 GHz RADIO control.

   (#) Call HAL_PWREx_SetREGVDDHPAInputSupply and HAL_PWREx_GetREGVDDHPAInputSupply
       set / get the regulator VDDHPA input supply selection.

   (#) Call HAL_PWREx_EnableREGVDDHPABypass and HAL_PWREx_DisableREGVDDHPABypass
       to enable / disable regulator REG_VDDHPA bypass

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief    PWR Extended HAL module driver
  * @{
  */

#if defined(HAL_PWR_MODULE_ENABLED)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx)
#define PWR_PORTA_AVAILABLE_PINS  (0x0FFFFU)
#define PWR_PORTB_AVAILABLE_PINS  (0x0FFFFU)
#define PWR_PORTC_AVAILABLE_PINS  (0x0E000U)
#define PWR_PORTH_AVAILABLE_PINS  (0x00008U)
#elif defined(STM32WBA50xx)
#define PWR_PORTA_AVAILABLE_PINS  (0x0F1E3U)
#define PWR_PORTB_AVAILABLE_PINS  (0x09318U)
#define PWR_PORTC_AVAILABLE_PINS  (0x0C000U)
#define PWR_PORTH_AVAILABLE_PINS  (0x00008U)
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) */
/*!< Time out value of flags setting */
#define PWR_VOSF_SETTING_DELAY_VALUE (0x32U) /*!< Time out value for VOSF flag setting */
#define PWR_MODE_CHANGE_DELAY_VALUE  (0x32U) /*!< Time out for step down converter operating mode */
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
      (+) The STM32WBA series devices embed two regulators : one LDO (linear
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
          mode. When exiting from Stop 1 and Standby modes the voltage range 2 is used.

      (+) When the 2.4 GHz RADIO is active the regulator and range can not be changed. Any
          requested regulator or range change while the 2.4 GHz RADIO is active is suspended
          and will only take effect after the 2.4 GHz RADIO has entered Sleep or Deepsleep mode.

      (+) Both regulators can provide four different voltages (voltage scaling)
          and can operate in Stop modes.
          Voltage scaling ranges can be one of the following values :
             (++) voltage output scale 1 :
                  => Used when system clock frequency is up to 100 MHz
             (++) voltage output scale 2 :
                  => Used when system clock frequency is up to 16 MHz

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
  * @note  Before moving to voltage scaling 2, it is mandatory to ensure that
  *        the system frequency is equal or below 16 MHz.
  * @note  When the 2.4 GHz RADIO is active, the range cannot be changed.
  *        Any requested range change while the 2.4 GHz RADIO is active is suspended and will
  *        only take effect after the 2.4 GHz RADIO has entered Sleep or Deepsleep mode.
  * @note  In range 2, the 2.4 GHz RADIO shall not transmit nor receive.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t timeout;

  /* Check the parameter */
  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

  /* Get the current voltage scale applied */
  uint32_t vos_old = READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOS);

  /* No change, nothing to do */
  if (vos_old == VoltageScaling)
  {
    return HAL_OK;
  }

  /* Set voltage scaling level */
  MODIFY_REG(PWR->VOSR, PWR_VOSR_VOS, VoltageScaling);


  /* Wait until VOSRDY is set */
  timeout = ((PWR_VOSF_SETTING_DELAY_VALUE * SystemCoreClock) / 1000000U) + 1U;
  while (HAL_IS_BIT_CLR(PWR->VOSR, PWR_VOSR_VOSRDY) && (timeout != 0U))
  {
    timeout--;
  }

  /* Check time out  */
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }

  /* Wait until ACTVOSRDY is set */
  timeout = ((PWR_VOSF_SETTING_DELAY_VALUE * SystemCoreClock) / 1000000U) + 1U;
  while ((HAL_IS_BIT_CLR(PWR->SVMSR, PWR_SVMSR_ACTVOSRDY)) && (timeout != 0U))
  {
    timeout--;
  }

  /* Check time out  */
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief  Return voltage scaling range.
  * @retval Applied voltage scaling value.
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->SVMSR & PWR_SVMSR_ACTVOS);
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

#if defined(PWR_CR2_FPWM)
/**
  * @brief  Enable SMPS PWM mode
  * @note   FPWM bit is used to reduce the SMPS switching harmonics in range 1.
  * @note   Setting FPWM bit has no effect in range 2
  * @retval None.
  */
void HAL_PWREx_EnableSMPSPWM(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FPWM);
}

/**
  * @brief  Disable SMPS PWM mode
  * @retval None.
  */
void HAL_PWREx_DisableSMPSPWM(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FPWM);
}
#endif /* defined(PWR_CR2_FPWM) */
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
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @brief    Low power control functions
  */

/**
  * @brief  Enable BOR and PVD ultra-low power mode.
  * @note   BOR and PVD operations can be in discontinuous (ultra-low power) mode in
  *         Stop 1 and Standby modes.
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



/** @defgroup PWREx_Exported_Functions_Group4 Memories Retention Functions
  * @brief    Memories retention functions
  *
@verbatim
 ===============================================================================
                     ##### Memories Retention Functions #####
 ===============================================================================
    [..]
      Several STM32WBA devices RAMs are configurable to retain or lose RAMs content
      during Stop mode.
       (+) Retained content RAMs in Stop modes are :
             (++) SRAM1
             (++) SRAM2
             (++) ICACHE

    [..]
      Several STM32WBA devices RAMs are configurable to retain or lose RAMs content
      in Standby mode.
       (+) Retained content RAMs in Standby mode are :
             (++) SRAM1
             (++) SRAM2

@endverbatim
  * @{
  */

/**
  * @brief  Enable SRAM1 content retention in Standby mode.
  * @note   When R1RSB1 bit is set, SRAM1 is powered by the low-power regulator in
  *         Standby mode and its content is kept.
  * @param  SRAM1Pages : Specifies the SRAM1 area
  *                      This parameter can be combination of the following values :
  *                      @arg PWR_SRAM1_FULL_STANDBY_RETENTION  : full SRAM1 retention.
  * @retval None.
  */
void HAL_PWREx_EnableSRAM1ContentStandbyRetention(uint32_t SRAM1Pages)
{
  /* Check the parameters */
  assert_param(IS_PWR_SRAM1_STANDBY_RETENTION(SRAM1Pages));

  /* Set RRSx bit(s) */
  MODIFY_REG(PWR->CR1, PWR_SRAM1_FULL_STANDBY_RETENTION, SRAM1Pages);
}

/**
  * @brief  Disable SRAM1 content retention in Standby mode.
  * @note   When R1RSB1 bit is reset, SRAM1 is powered off in Standby
  *         mode and its content is lost.
  * @retval None.
  */
void HAL_PWREx_DisableSRAM1ContentStandbyRetention(void)
{
  /* Clear R1RSB1 bit */
  CLEAR_BIT(PWR->CR1, PWR_SRAM1_FULL_STANDBY_RETENTION);
}

/**
  * @brief  Enable SRAM2 content retention in Standby mode.
  * @note   When R2RSB1 bit is set, SRAM2 is powered by the low-power regulator in
  *         Standby mode and its content is kept.
  * @param  SRAM2Pages : Specifies the SRAM2 area
  *                      This parameter can be one of the following values :
  *                      @arg PWR_SRAM2_FULL_STANDBY_RETENTION  : full SRAM2 retention.
  * @retval None.
  */
void HAL_PWREx_EnableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages)
{
  /* Check the parameters */
  assert_param(IS_PWR_SRAM2_STANDBY_RETENTION(SRAM2Pages));

  /* Set RRSx bit(s) */
  MODIFY_REG(PWR->CR1, PWR_SRAM2_FULL_STANDBY_RETENTION, SRAM2Pages);
}

/**
  * @brief  Disable SRAM2 content retention in Standby mode.
  * @note   When R2RSB1 bit is reset, SRAM2 is powered off in Standby
  *         mode and its content is lost.
  * @retval None.
  */
void HAL_PWREx_DisableSRAM2ContentStandbyRetention(void)
{
  /* Clear R2RSB1 bit */
  CLEAR_BIT(PWR->CR1, PWR_SRAM2_FULL_STANDBY_RETENTION);
}

/**
  * @brief  Enable 2.4GHz RADIO SRAMs and Sleep clock retention in Standby mode.
  * @note   When RADIORSB bit is set, the 2.4 GHz RADIO SRAMs (TXRX and Sequence) content
  *         is retained in Standby mode and the 2.4 GHz RADIO sleep timer counter remains
  *         operational.
  * @param  RadioSRAM : Specifies the Radio SRAM area
  *                      This parameter can be one of the following values :
  *                      @arg PWR_RADIOSRAM_FULL_STANDBY_RETENTION: full Radio SRAM and sleep counter retention.
  * @retval None.
  */
void HAL_PWREx_EnableRadioSRAMClockStandbyRetention(uint32_t RadioSRAM)
{
  /* Check the parameters */
  assert_param(IS_PWR_RADIOSRAM_STANDBY_RETENTION(RadioSRAM));

  /* Set Radio RAM retention bit(s) */
  MODIFY_REG(PWR->CR1, PWR_RADIOSRAM_FULL_STANDBY_RETENTION, RadioSRAM);
}

/**
  * @brief  Disable 2.4GHz RADIO SRAMs and Sleep clock retention in Standby mode.
  * @note   When RADIORSB bit is reset, the 2.4 GHz RADIO SRAMs and the sleep timer counter
  *         are not retained in Standby mode.
  * @retval None.
  */
void HAL_PWREx_DisableRadioSRAMClockStandbyRetention(void)
{
  /* Clear RADIORSB bit */
  CLEAR_BIT(PWR->CR1, PWR_RADIOSRAM_FULL_STANDBY_RETENTION);
}

/**
  * @brief  Enable RAMs content retention in Stop modes.
  * @note   When enabling content retention for a given ram, memory is kept powered
  *         on in Stop mode. (Consumption is not optimized)
  * @note   On Silicon Cut 1.0, it is mandatory to disable the ICACHE before going into
  *         stop modes otherwise an hard fault may occur when waking up from stop modes.
  * @param RAMSelection: Specifies RAMs content to be retained in Stop mode.
  *                      This parameter can be one or a combination of the values:
  *                      @arg PWR_SRAM1_FULL_STOP_RETENTION  : full SRAM1 retention .
  *                      @arg PWR_SRAM2_FULL_STOP_RETENTION  : full SRAM2 retention.
  *                      @arg PWR_ICACHE_FULL_STOP_RETENTION : I-CACHE SRAM retention.
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
  * @brief Disable RAMs content retention in Stop modes.
  * @note  When disabling content retention for a given RAM, memory is
  *        powered down in Stop mode. (Consumption is optimized)
  * @param RAMSelection: Specifies RAMs content to be lost in Stop mode.
  *                      This parameter can be one or a combination of the values:
  *                      @arg PWR_SRAM1_FULL_STOP_RETENTION  : full SRAM1 retention .
  *                      @arg PWR_SRAM2_FULL_STOP_RETENTION  : full SRAM2 retention.
  *                      @arg PWR_ICACHE_FULL_STOP_RETENTION : I-CACHE SRAM retention.
  * @retval None.
  */
void HAL_PWREx_DisableRAMsContentStopRetention(uint32_t RAMSelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_RAM_STOP_RETENTION(RAMSelection));

  /* Disable RAM retention in Stop mode */
  MODIFY_REG(PWR->CR2, PWR_ALL_RAM_STOP_RETENTION_MASK, RAMSelection);
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
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group5 I/O Retention Functions
  * @brief    I/O retention functions
  *
@verbatim
 ===============================================================================
                     ##### IOs retention functions #####
 ===============================================================================
    [..]
      In Standby mode, the GPIOs are by default in floating state. If Standby GPIO
      retention is enabled in the PWR_IORETENRx register, the GPIO will retain the pull
      or output level. When entering Standby mode, GPIOs that are enabled for Standby mode
      retention keep their pull or level during and after exiting from Standby mode until
      the PWR_IORETRx bit is cleared by software.

    [..]
      When entering Standby mode the PWR_IORETRx bit will be set by hardware for the GPIOs with
      Standby retention enabled in. Once PWR_IORETRx is cleared by software, the GPIO configuration
      will switch to the one defined as below:
      (+) when GPIO is not selecting an alternate function, GPIO configuration is applied,
      (+) when GPIO is selecting an alternate function, the selected peripheral alternate function
          control will be applied.
      The GPIO Standby retention enable information in PWR_IORETENRx is lost and has to be reconfigured
      for sub-sequent entering into Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief  Enable GPIO state retention in Standby mode.
  * @note   Set the relevant Pxy bits of PWR_IORETENRx register to configure the I/O
  *         state retention in Standby mode.
  * @note   The configuration is kept when exiting the Standby mode.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableStandbyIORetention(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef ret = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /*  Enables the Standby GPIO retention feature for PAy  */
      if (((GPIO_Pin & PWR_PORTA_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTA_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        SET_BIT(PWR->IORETENRA, GPIO_Pin);
      }
      break;

    case PWR_GPIO_B: /* Enables the Standby GPIO retention feature for PBy */
      if (((GPIO_Pin & PWR_PORTB_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTB_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        SET_BIT(PWR->IORETENRB, GPIO_Pin);
      }
      break;

    case PWR_GPIO_C: /* Enables the Standby GPIO retention feature for PCy */
      if (((GPIO_Pin & PWR_PORTC_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTC_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        SET_BIT(PWR->IORETENRC, GPIO_Pin);
      }
      break;

    case PWR_GPIO_H: /* Enables the Standby GPIO retention feature for PHy */
      if (((GPIO_Pin & PWR_PORTH_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTH_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        SET_BIT(PWR->IORETENRH, GPIO_Pin);
      }
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Disable GPIO state retention in Standby mode.
  * @note   Clear the relevant Pxy bits of PWR_IORETENRx register to disable
  *         the I/O state retention in Standby mode.
  * @note   The configuration is kept when exiting the Standby mode.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableStandbyIORetention(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef ret = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /*  Disables the Standby GPIO retention feature for PAy  */
      if (((GPIO_Pin & PWR_PORTA_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTA_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETENRA, GPIO_Pin);
      }
      break;

    case PWR_GPIO_B: /* Disables the Standby GPIO retention feature for PBy */
      if (((GPIO_Pin & PWR_PORTB_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTB_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETENRB, GPIO_Pin);
      }
      break;

    case PWR_GPIO_C: /* Disables the Standby GPIO retention feature for PCy */
      if (((GPIO_Pin & PWR_PORTC_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTC_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETENRC, GPIO_Pin);
      }
      break;

    case PWR_GPIO_H: /* Disables the Standby GPIO retention feature for PHy */
      if (((GPIO_Pin & PWR_PORTH_AVAILABLE_PINS) == 0U) || \
           ((GPIO_Pin & (~PWR_PORTH_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETENRH, GPIO_Pin);
      }
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Return for a given port for which IO the state was retained in Standby mode.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @note  The API returns the whole set of IOs for a given GPIO. A '1' at GPIO_Pin
  *        position indicates that this IO state (pull or level) was retained when
  *        the device entered Standby mode.
  * @retval HAL Status.
  */
uint32_t HAL_PWREx_GetStandbyIORetentionStatus(uint32_t GPIO_Port)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));

  /* Check GPIO port Standby IO retention status */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Get port A standby GPIO retention status */
      return READ_REG(PWR->IORETRA);
      break;

    case PWR_GPIO_B: /* Get port B standby GPIO retention status */
      return READ_REG(PWR->IORETRB);
      break;

    case PWR_GPIO_C: /* Get port C standby GPIO retention status */
      return READ_REG(PWR->IORETRC);
      break;

    case PWR_GPIO_H: /* Get port H standby GPIO retention status */
      return READ_REG(PWR->IORETRH);
      break;

    default:
      return 0U;
      break;
  }
}

/**
  * @brief  Disable the GPIO state retained in Standby mode
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @note   This API can be used to disable after Standby mode the IO state that
  *         was configured to be retained by HAL_PWREx_EnableStandbyIORetention().
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableStandbyRetainedIOState(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef ret = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Disable the IO state (pull or level) retained for PAy in Standby mode */
      if (((GPIO_Pin & PWR_PORTA_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTA_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETRA, GPIO_Pin);
      }
      break;

    case PWR_GPIO_B: /* Disable the IO state (pull or level) retained for PBy in Standby mode */
      if (((GPIO_Pin & PWR_PORTB_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTB_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETRB, GPIO_Pin);
      }
      break;

    case PWR_GPIO_C: /* Disable the IO state (pull or level) retained for PCy in Standby mode */
      if (((GPIO_Pin & PWR_PORTC_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTC_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETRC, GPIO_Pin);
      }
      break;

    case PWR_GPIO_H: /* Disable the IO state (pull or level) retained for PHy in Standby mode */
      if (((GPIO_Pin & PWR_PORTH_AVAILABLE_PINS) == 0U) || \
          ((GPIO_Pin & (~PWR_PORTH_AVAILABLE_PINS)) != 0U))
      {
        ret = HAL_ERROR;
      }
      else
      {
        CLEAR_BIT(PWR->IORETRH, GPIO_Pin);
      }
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  return ret;
}

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group6 I/O RADIO Configuration and Status Reading Functions
  * @brief    RADIO power amplifier setting and RADIO status reading functions
  *
@verbatim
 ===============================================================================
                ##### RADIO configuration and status reading functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief Get the 2.4 GHz RADIO operating mode.
  * @note The output can be any value from
  *                      @ref PWREx_RADIO_Mode.
  *                      @arg PWR_RADIO_DEEPSLEEP_MODE : 2.4 GHz RADIO deep sleep mode.
  *                      @arg PWR_RADIO_SLEEP_MODE  : 2.4 GHz RADIO sleep mode.
  *                      @arg PWR_RADIO_ACTIVE_MODE :  2.4 GHz RADIO active mode.
  * @retval The operating mode
  */
uint32_t  HAL_PWREx_GetRADIOOperatingMode(void)
{
  uint32_t temp = READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_MODE);

  if ((temp & PWR_RADIOSCR_MODE_1) == PWR_RADIOSCR_MODE_1)
  {
    temp = PWR_RADIO_ACTIVE_MODE;

  }
  return temp;
}

/**
  * @brief Get the 2.4 GHz RADIO PHY operating mode.
  * @note The output can be any value from
  *                      @ref PWREx_RADIO_PHY_Mode.
  *                      @arg PWR_RADIO_PHY_SLEEP_MODE : 2.4 GHz RADIO PHY sleep mode.
  *                      @arg PWR_RADIO_PHY_STANDBY_MODE  : 2.4 GHz RADIO PHY standby mode.
  * @retval The PHY operating mode
  */
uint32_t  HAL_PWREx_GetRADIOPHYOperatingMode(void)
{
  return READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_PHYMODE);
}

/**
  * @brief Get the 2.4 GHz RADIO encryption operating mode.
  * @note The output can be any value from
  *                      @arg PWR_RADIO_ENCMODE_ENABLED  : 2.4 GHz RADIO encryption function enabled.
  *                      @arg PWR_RADIO_ENCMODE_DISABLED : 2.4 GHz RADIO encryption function disabled.
  * @retval The Radio encryption operating mode
  */
uint32_t  HAL_PWREx_GetRADIOEncryptionOperatingMode(void)
{
  return READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_ENCMODE);
}

/**
  * @brief Get the 2.4 GHz RADIO control.
  * @note The output can be any value from
  *       Bits [3:0]  output power table format
  *       Bit  [4]    rf_event.
  * @retval The PHY operating mode
  */
uint32_t  HAL_PWREx_GetRFVDDHPA(void)
{
  return READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_RFVDDHPA);
}

#if defined(PWR_RADIOSCR_REGPASEL)
/**
  * @brief Set the regulator REG_VDDHPA input supply selection.
  * @param  SupplySelection : Specifies the regulator REG_VDDHPA input supply.
  *          This parameter can be one of the following values :
  *         @arg PWR_RADIO_REG_VDDRFPA  : VDDRFPA pin selected as regulator REG_VDDHPA input supply.
  *         @arg PWR_RADIO_REG_VDDHPA_VD11 :  Regulator REG_VDDHPA input supply selection between VDDRFPA
  *                                           and VDD11 dependent on requested regulated output voltage.
  * @retval HAL Status.
  */
HAL_StatusTypeDef  HAL_PWREx_SetREGVDDHPAInputSupply(uint32_t SupplySelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_REGPASEL_SUPPLYSELECTION(SupplySelection));

  MODIFY_REG(PWR->RADIOSCR, PWR_RADIOSCR_REGPASEL, SupplySelection);

  return HAL_OK;
}

/**
  * @brief Get the regulator REG_VDDHPA input supply selection.
  * @note  The output can be one of the following values :
  *         @arg PWR_RADIO_REG_VDDRFPA  : VDDRFPA pin selected as regulator REG_VDDHPA input supply.
  *         @arg PWR_RADIO_REG_VDDHPA_VD11 :  Regulator REG_VDDHPA input supply selection between VDDRFPA
  *                                           and VDD11 dependent on requested regulated output voltage.
  * @retval The regulator REG_VDDHPA input supply selection.
  */
uint32_t HAL_PWREx_GetREGVDDHPAInputSupply(void)
{
  return READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPASEL);
}
#endif /* defined(PWR_RADIOSCR_REGPASEL) */

#if defined(PWR_RADIOSCR_REGPABYPEN)
/**
  * @brief  Enable regulator REG_VDDHPA bypass
  * @note   Make 2.4 GHz RADIO PA 1.2 V supplied directly from internal VDD11. (only available when
  *         REGPASEL = 0)
  * @note   This API shall only be called when the VDDHPA regulator is not used
  * @retval None.
  */
void HAL_PWREx_EnableREGVDDHPABypass(void)
{
  SET_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPABYPEN);
}

/**
  * @brief  Disable regulator REG_VDDHPA bypass
  * @retval None.
  */
void HAL_PWREx_DisableREGVDDHPABypass(void)
{
  CLEAR_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPABYPEN);
}
#endif /* defined(PWR_RADIOSCR_REGPABYPEN) */

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

/**
  * @}
  */
