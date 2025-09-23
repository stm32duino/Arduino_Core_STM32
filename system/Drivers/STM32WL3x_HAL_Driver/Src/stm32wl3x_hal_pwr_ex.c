/**
  ******************************************************************************
  * @file    stm32wl3x_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Extended Peripheral Control functions
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

/** @addtogroup PWREx
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/**
  * @brief Enable IO pull-up state in DeepStop and Shutdown modes.
  * @param GPIO Specify the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 or the logical OR
  *         of several of them to setseveral bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      SET_BIT(PWR->PUCRA, GPIONumber);
      CLEAR_BIT(PWR->PDCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      SET_BIT(PWR->PUCRB, GPIONumber);
      CLEAR_BIT(PWR->PDCRB, GPIONumber);
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Disable IO pull-up state in DeepStop mode and Shutdown modes.
  * @param GPIO Specifies the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15
  *         or the logical OR of several of them to reset
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      CLEAR_BIT(PWR->PUCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PUCRB, GPIONumber);
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Enable GPIO pull-down state in DeepStop and Shutdown modes.
  * @note  Set the relevant PDy bits of PWR_PDCRx register to configure the I/O in
  *        pull-down state in DeepStop and Shutdown modes.
  * @note  This state is effective in DeepStop and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the
  *        power-on reset, maintained when exiting the DeepStop mode.
  * @note  To avoid any conflict at DeepStop and Shutdown modes exits, the corresponding
  *        PUy bit of PWR_PUCRx register is cleared unless it is reserved.
  * @note  Even if a PDy bit to set is reserved, the other PDy bits entered as input
  *        parameter at the same time are set.
  * @param GPIO Specify the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15
  *         or the logical OR of several of them to set
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      SET_BIT(PWR->PDCRA, GPIONumber);
      CLEAR_BIT(PWR->PUCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      SET_BIT(PWR->PDCRB, GPIONumber);
      CLEAR_BIT(PWR->PUCRB, GPIONumber);
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Disable GPIO pull-down state in DeepStop and Shutdown modes.
  * @note  Reset the relevant PDy bits of PWR_PDCRx register used to configure the I/O
  *        in pull-down state in DeepStop and Shutdown modes.
  * @note  Even if a PDy bit to reset is reserved, the other PDy bits entered as input
  *        parameter at the same time are reset.
  * @param GPIO Specifies the IO port. This parameter can be PWR_GPIO_A, PWR_GPIO_B
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15
  *         or the logical OR of several of them to reset
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      CLEAR_BIT(PWR->PDCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PDCRB, GPIONumber);
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Enable pull-up and pull-down configuration.
  * @note  When APC bit is set, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are applied in DeepStop and Shutdown modes.
  * @note  Pull-up set by PUy bit of PWR_PUCRx register is not activated if the corresponding
  *        PDy bit of PWR_PDCRx register is also set (pull-down configuration priority is higher).
  *        HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() API's ensure there
  *        is no conflict when setting PUy or PDy bit.
  * @retval None
  */
void HAL_PWREx_EnablePullUpPullDownConfig()
{
  SET_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief Disable pull-up and pull-down configuration.
  * @note  When APC bit is cleared, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are not applied in DeepStop and Shutdown modes.
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig()
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief  Enable the wake up line functionality.
  * @note   Wake up lines are used to wake up the system from DEEPSTOP.
  *         The polarity is applied only for the IOs source line and the wakeup
  *         event are only edge detection, not level detection.
  * @param  WakeUpPeripheral : Specifies which wake up peripheral to
  *                            enable. This parameter can be a combination of:
  *                            @arg @ref PWR_WAKEUP_LPAWUR
  *                            @arg @ref PWR_WAKEUP_SUBG
  *                            @arg @ref PWR_WAKEUP_SUBGHOST
  *                            @arg @ref PWR_WAKEUP_LCSC
  *                            @arg @ref PWR_WAKEUP_COMP
  *                            @arg @ref PWR_WAKEUP_LCD
  *                            @arg @ref PWR_WAKEUP_RTC
  *                            @arg @ref PWR_WAKEUP_LPUART
  * @param  WakeUpPolarity   : Specifies the polarity of the wake up peripehral source.
  *                      This parameter is applied only for the IOs source and
  *                      can be a value of @ref PWR_WAKEUP_POLARITY.
  * @retval None.
  */
void HAL_PWREx_EnableInternalWakeUpLine(uint32_t WakeUpPeripheral, uint32_t WakeUpPolarity)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_SOURCE(WakeUpPeripheral));
  assert_param(IS_PWR_WAKEUP_POLARITY(WakeUpPolarity));

  /* Specifies the wake up line polarity for the event detection (rising or falling edge) */
  LL_PWR_SetWakeupInternalPolarity(WakeUpPeripheral, WakeUpPolarity);

  /* Enable wake-up internal peripheral */
  LL_PWR_EnableInternWU(WakeUpPeripheral);
}

/**
  * @brief  Get and Clear Wake-up Peripheral source.
  * @retval WakeUpPin : This parameter can be a combination of
  *                     @ref PWR_WAKEUP_SOURCE define group
  */
uint32_t HAL_PWREx_GetClearInternalWakeUpLine(void)
{
  uint32_t wakeup_sources;

  /* Get all wake-up Peripheral */
  wakeup_sources = LL_PWR_GetInternalWakeupSource();

  /* Clear all the wake-up Peripehral flags */
  LL_PWR_ClearInternalWakeupSource(wakeup_sources);

  return wakeup_sources;
}

/**
  * @brief  Disable the wake up peripheral functionality.
  * @param  WakeUpPeripehral : Specifies the wake up peripehral to disable.
  *                            This parameter can be a combination of
  *                            @arg @ref PWR_WAKEUP_LPAWUR
  *                            @arg @ref PWR_WAKEUP_SUBG
  *                            @arg @ref PWR_WAKEUP_SUBGHOST
  *                            @arg @ref PWR_WAKEUP_LCSC
  *                            @arg @ref PWR_WAKEUP_COMP
  *                            @arg @ref PWR_WAKEUP_LCD
  *                            @arg @ref PWR_WAKEUP_RTC
  *                            @arg @ref PWR_WAKEUP_LPUART
  * @retval None
  */
void HAL_PWREx_DisableInternalWakeUpLine(uint32_t WakeUpPeripehral)
{
  /* Reset the wake up peripehral polarity to the default value */
  LL_PWR_SetWakeupInternalPolarity(WakeUpPeripehral, PWR_WUP_RISIEDG);

  /* Disable wake-up peripehral */
  LL_PWR_DisableInternWU(WakeUpPeripehral);
}

/**
  * @brief  Enter the whole system in SHUTDOWN mode.
  * @note   The SHUTDOWN mode is the least power consuming mode.
  * @note   All the device clock and bus clocks are stopped, the VDD12i and
  *         VDD12o power domains are switched off.
  *         All the RAM banks are NOT retained.
  *         All the register content are lost.
  * @retval None.
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{

  /* Clear all the wake-up pin flags */
  LL_PWR_ClearInternalWakeupSource(LL_PWR_WAKEUP_ALL);
  LL_PWR_ClearWakeupSource(PWR_WAKEUP_PORTA, LL_PWR_WAKEUP_ALL);
  LL_PWR_ClearWakeupSource(PWR_WAKEUP_PORTB, LL_PWR_WAKEUP_ALL);

  /* Enable the device Shutdown configuration */
  LL_PWR_SetPowerMode(LL_PWR_MODE_SHUTDOWN);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Wait for Interrupt Request to enter in SHUTDOWN */
  __WFI();
}

/**
  * @brief  Enable the DEEPSTOP2 feature, debugger feature not lost during DEEPSTOP.
  * @rmtoll DBGR               HAL_PWREx_EnableDEEPSTOP2
  * @retval None
  */
void HAL_PWREx_EnableDEEPSTOP2(void)
{
  SET_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2);
}

/**
  * @brief  Disable the DEEPSTOP2 feature, debugger feature lost during DEEPSTOP.
  * @rmtoll DBGR               HAL_PWREx_DisableDEEPSTOP2
  * @retval None
  */
void HAL_PWREx_DisableDEEPSTOP2(void)
{
  CLEAR_BIT(PWR->DBGR, PWR_DBGR_DEEPSTOP2);
}

/**
  * @brief Configure the SMPS output voltage.
  * @param OutputVoltage SMPS output voltage value.
  *         This parameter can be one of the following values
  *         @ref PWREx_SMPS_OUTPUT_VOLTAGE_LEVEL
  * @param BOM SMPS BOM configuration.
  *         This parameter can be one of the following values
  *         @ref PWREx_SMPS_BOM
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSMPS(uint32_t OutputVoltage, uint32_t BOM)
{
  /* Check the parameter */
  assert_param(IS_PWR_SMPS_OUTPUT_VOLTAGE(OutputVoltage));
  assert_param(IS_PWR_SMPS_BOM(BOM));

  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSLVL, OutputVoltage);
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSBOMSEL, BOM);

  return HAL_OK;
}

/**
  * @brief Set SMPS operating mode.
  * @param  OperatingMode This parameter can be one of the following values:
  *         @arg @ref PWR_SMPS_ON
  *         @arg @ref PWR_SMPS_OFF
  *         @arg @ref PWR_SMPS_PRECHARGE
  *
  * @retval None
  */
void HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode)
{
  /* Check the parameter */
  assert_param(IS_PWR_SMPS_MODE(OperatingMode));

  /* SMPS ON Configuration */
  if (OperatingMode == PWR_SMPS_ON)
  {
    LL_PWR_SetSMPSMode(LL_PWR_SMPS);
    while (!LL_PWR_IsSMPSinRUNMode());
    LL_PWR_SetSMPSPrechargeMode(LL_PWR_NO_SMPS_PRECHARGE);
  }

  /* SMPS Precharge Configuration */
  if (OperatingMode == PWR_SMPS_BYPASS)
  {
    LL_PWR_SetSMPSMode(LL_PWR_SMPS);
    while (!LL_PWR_IsSMPSinRUNMode());
    LL_PWR_SetSMPSPrechargeMode(OperatingMode);
  }

  /* SMPS OFF Configuration */
  if (OperatingMode == PWR_SMPS_OFF)
  {
    LL_PWR_SetSMPSMode(OperatingMode);
    while (LL_PWR_IsSMPSinRUNMode());
    LL_PWR_SetSMPSPrechargeMode(LL_PWR_NO_SMPS_PRECHARGE);
  }
}

/**
  * @brief  Get SMPS operating mode
  * @retval Returned value can be one of the following values:
  *         @arg @ref PWR_SMPS_ON
  *         @arg @ref PWR_SMPS_OFF
  *         @arg @ref PWR_SMPS_PRECHARGE
  */
uint32_t HAL_PWREx_SMPS_GetMode(void)
{
  uint32_t smpsConfiguration;

  if (LL_PWR_IsEnabledSMPSPrechargeMode())
  {
    smpsConfiguration = PWR_SMPS_PRECHARGE;
  }
  else
  {
    smpsConfiguration = LL_PWR_GetSMPSMode();
  }

  return smpsConfiguration;
}

/**
  * @brief Enable RAMs content retention in Deepstop mode.
  * @note  When enabling content retention for a given RAM, memory is kept powered
  *         on in Deepstop mode.
  * @retval None.
  */
void HAL_PWREx_EnableSRAMRetention()
{
  /* Enable RAM BANK1 Retention in DEEPSTOP */
  SET_BIT(PWR->CR2, LL_PWR_RAMRET_1);
}

/**
  * @brief Disable RAMs content retention in Deepstop mode.
  * @note  When disabling content retention for a given RAM, memory content
  *        is lost in Deepstop mode.
  * @retval None.
  */
void HAL_PWREx_DisableSRAMRetention()
{
  /* Disable RAM BANK1 Retention in DEEPSTOP */
  CLEAR_BIT(PWR->CR2, LL_PWR_RAMRET_1);
}

/**
  * @brief  Enable the GPIORET feature, GPIO retain their status during DEEPSTOP
  *         and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      HAL_PWREx_EnableGPIORetention
  * @retval None
  */
void HAL_PWREx_EnableGPIORetention()
{
  SET_BIT(PWR->CR2, PWR_CR2_GPIORET);
}

/**
  * @brief  Disable the GPIORET feature, don't retain their status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      HAL_PWREx_DisableGPIORetention
  * @retval None
  */
void HAL_PWREx_DisableGPIORetention()
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_GPIORET);
}

/**
  * @brief  Enable the DBGRET feature, PA2 and PA3 retain their status during DEEPSTOP
  *         and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      HAL_PWREx_EnableDBGRetention
  * @retval None
  */
void HAL_PWREx_EnableDBGRetention()
{
  SET_BIT(PWR->CR2, PWR_CR2_DBGRET);
}

/**
  * @brief  Disable the DBGRET feature, don't retain their status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      HAL_PWREx_DisableDBGRetention
  * @retval None
  */
void HAL_PWREx_DisableDBGRetention()
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_DBGRET);
}

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
