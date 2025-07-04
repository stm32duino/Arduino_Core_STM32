/**
  ******************************************************************************
  * @file    stm32wb0x_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Extended Initialization and de-initialization functions
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
#include "stm32wb0x_hal.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */
/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Functions PWREx Extended Exported Functions
  * @{
  */

/**
  * @brief Enable Internal Wake-up Line (RTC).
  * @retval None
  */
void HAL_PWREx_EnableInternalWakeUpLine(void)
{
  SET_BIT(PWR->CR3, PWR_WAKEUP_PIN_RTC);
}

/**
  * @brief Disable Internal Wake-up Line (RTC).
  * @retval None
  */
void HAL_PWREx_DisableInternalWakeUpLine(void)
{
  CLEAR_BIT(PWR->CR3, PWR_WAKEUP_PIN_RTC);
}

#if defined (PWR_CR3_EIWL2)
/**
  * @brief Enable Internal Wake-up Line2 (LPUART).
  * @retval None
  */
void HAL_PWREx_EnableInternalWakeUpLineLpuart(void)
{
  SET_BIT(PWR->CR3, PWR_WAKEUP_PIN_LPUART);
}

/**
  * @brief Disable Internal Wake-up Line2 (LPUART).
  * @retval None
  */
void HAL_PWREx_DisableInternalWakeUpLineLpuart(void)
{
  CLEAR_BIT(PWR->CR3, PWR_WAKEUP_PIN_LPUART);
}
#endif /* PWR_CR3_EIWL2 */

/**
  * @brief Enable wakeup on Bluetooth LE Host CPU.
  * @retval None
  */
void HAL_PWREx_EnableBleHostCpuWakeUp(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EWBLEHCPU);
}

/**
  * @brief Disable wakeup on Bluetooth LE Host CPU.
  * @retval None
  */
void HAL_PWREx_DisableBleHostCpuWakeUp(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EWBLEHCPU);
}

/**
  * @brief Enable wakeup on Bluetooth LE.
  * @retval None
  */
void HAL_PWREx_EnableBleWakeUp(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EWBLE);
}

/**
  * @brief Disable wakeup on Bluetooth LE.
  * @retval None
  */
void HAL_PWREx_DisableBleWakeUp(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EWBLE);
}

/**
  * @brief Enable GPIO pull-up state in DeepStop and Shutdown modes.
  * @note  Set the relevant PUy bits of PWR_PUCRx register to configure the I/O in
  *        pull-up state in DeepStop and Shutdown modes.
  * @note  This state is effective in DeepStop and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the
  *        power-on reset, maintained when exiting the  mode.
  * @note  To avoid any conflict at DeepStop and Shutdown modes exits, the corresponding
  *        PDy bit of PWR_PDCRx register is cleared unless it is reserved.
  * @note  Even if a PUy bit to set is reserved, the other PUy bits entered as input
  *        parameter at the same time are set.
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
  * @brief Disable GPIO pull-up state in DeepStop mode and Shutdown modes.
  * @note  Reset the relevant PUy bits of PWR_PUCRx register used to configure the I/O
  *        in pull-up state in DeepStop and Shutdown modes.
  * @note  Even if a PUy bit to reset is reserved, the other PUy bits entered as input
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
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief Disable pull-up and pull-down configuration.
  * @note  When APC bit is cleared, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are not applied in DeepStop and Shutdown modes.
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_APC);
}

/**
  * @brief Enable RAMx content retention in DEEPSTOP mode.
  * @rmtoll CR2         RAMRET1    HAL_PWREx_EnableSRAMRetention
  *         CR2         RAMRET2    HAL_PWREx_EnableSRAMRetention
  *         CR2         RAMRET3    HAL_PWREx_EnableSRAMRetention
  * @param  banks RAM bank selection. This parameter can be a combination of the following values:
  *         @arg @ref PWR_RAMRET_1
  *         @arg @ref PWR_RAMRET_2 (*)
  *         @arg @ref PWR_RAMRET_3 (*)
  *         (*) Not available on devices STM32WB05
  * @retval None
  */
void HAL_PWREx_EnableSRAMRetention(uint32_t banks)
{
  LL_PWR_EnableRAMBankRet(banks);
}

/**
  * @brief Disable RAMx content retention in DEEPSTOP mode.
  * @rmtoll CR2         RAMRET1    HAL_PWREx_DisableSRAMRetention
  *         CR2         RAMRET2    HAL_PWREx_DisableSRAMRetention
  *         CR2         RAMRET3    HAL_PWREx_DisableSRAMRetention
  * @param  banks RAM bank selection. This parameter can be a combination of the following values:
  *         @arg @ref PWR_RAMRET_1
  *         @arg @ref PWR_RAMRET_2 (*)
  *         @arg @ref PWR_RAMRET_3 (*)
  *         (*) Not available on devices STM32WB05
  * @retval None
  */
void HAL_PWREx_DisableSRAMRetention(uint32_t banks)
{
  LL_PWR_DisableRAMBankRet(banks);
}

#if defined (PWR_CR2_GPIORET)
/**
  * @brief  Enable the GPIORET feature, GPIO retain their status during DEEPSTOP
  *         and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      HAL_PWREx_EnableGPIORetention
  * @retval None
  */
void HAL_PWREx_EnableGPIORetention(void)
{
  LL_PWR_EnableGPIORET();
}

/**
  * @brief  Disable the GPIORET feature, don't retain their status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         GPIORET      HAL_PWREx_DisableGPIORetention
  * @retval None
  */
void HAL_PWREx_DisableGPIORetention(void)
{
  LL_PWR_DisableGPIORET();
}
#endif /* PWR_CR2_GPIORET */

#if defined (PWR_CR2_DBGRET)
/**
  * @brief  Enable the DBGRET feature, PA2 and PA3 retain their status during DEEPSTOP
  *         and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      HAL_PWREx_EnableDBGRetention
  * @retval None
  */
void HAL_PWREx_EnableDBGRetention(void)
{
  LL_PWR_EnableDBGRET();
}

/**
  * @brief  Disable the DBGRET feature, don't retain their status during DEEPSTOP and exiting from DEEPSTOP.
  * @rmtoll CR2         DBGRET      HAL_PWREx_DisableDBGRetention
  * @retval None
  */
void HAL_PWREx_DisableDBGRetention(void)
{
  LL_PWR_DisableDBGRET();
}
#endif /* PWR_CR2_DBGRET */

/**
  * @brief Configure the SMPS step down converter.
  * @param OutputVoltage SMPS output voltage configuration.
  *        This parameter can be one of the following values:
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V20
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V25
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V30
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V35
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V40
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V45
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V50
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V55
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V60
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V65
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V70
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V75
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V80
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V85
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V90
  *         @arg @ref PWR_SMPS_OUTPUT_VOLTAGE_1V95
  * @param BOM SMPS BOM configuration.
  * @note  To set and enable SMPS operating mode, refer to function
  *        "HAL_PWREx_SMPS_SetMode()".
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
  *         @arg @ref PWR_SMPS_BYPASS
  *
  * @retval None
  */
void HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode)
{
  /* Check the parameter */
  assert_param(IS_PWR_SMPS_MODE(OperatingMode));

  if (OperatingMode == PWR_SMPS_ON)
  {
    MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, PWR_SMPS_ON);
    while (!LL_PWR_IsSMPSinRUNMode());
    MODIFY_REG(PWR->CR5, PWR_CR5_SMPSFBYP, PWR_NO_SMPS_PRECHARGE);
  }

  /* SMPS Precharge Configuration */
  if (OperatingMode == PWR_SMPS_BYPASS)
  {
    MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, PWR_SMPS_ON);
    while (!LL_PWR_IsSMPSinRUNMode());
    MODIFY_REG(PWR->CR5, PWR_CR5_SMPSFBYP, PWR_SMPS_PRECHARGE);
  }

  /* SMPS OFF Configuration */
  if (OperatingMode == PWR_SMPS_OFF)
  {
    MODIFY_REG(PWR->CR5, PWR_CR5_NOSMPS, PWR_SMPS_OFF);
    while (LL_PWR_IsSMPSinRUNMode());
    MODIFY_REG(PWR->CR5, PWR_CR5_SMPSFBYP, PWR_NO_SMPS_PRECHARGE);
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
  return (uint32_t)(READ_BIT(PWR->SR2, (PWR_SR2_SMPSENR | PWR_SR2_SMPSBYPR)));
}

/**
  * @brief  Enter Shutdown mode.
  * @note   In Shutdown mode, all clocks are off as RC64MPLL, LSI and LSE are switched
  *         off. The system is powered down as both regulators are OFF is powered off.
  * @note   The I/Os can be configured either with a pull-up or pull-down or can
  *         be kept in analog state.
  *         HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown()
  *         respectively enable Pull Up and Pull Down state.
  *         HAL_PWREx_DisableGPIOPullUp() & HAL_PWREx_DisableGPIOPullDown()
  *         disable the same. These states are effective in Standby mode only if
  *         APC bit is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @retval None
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{
  /* Clear all the wake-up pin flags */
  LL_PWR_ClearWakeupSource(LL_PWR_WAKEUP_ALL);

  /* Set Shutdown mode */
  SET_BIT(PWR->CR1, PWR_LOWPOWERMODE_SHUTDOWN);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif /* __CC_ARM */

  /* Request Wait For Interrupt */
  __WFI();
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
