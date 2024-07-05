/**
  ******************************************************************************
  * @file    stm32c0xx_hal_pwr_ex.c
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
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"

/** @addtogroup STM32C0xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */

/** @defgroup PWREx_Gpio_Pin_Number  PWREx Gpio Pin Number
  * @{
  */
#define PWR_GPIO_PIN_NB                     16u  /*!< Number of gpio pin in bank */
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
/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1 Extended Peripheral Control functions
  *  @brief   Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
  ##### Extended Peripheral Initialization and de-initialization functions #####
 ===============================================================================
    [..]

@endverbatim
  * @{
  */

#if defined (PWR_PVM_SUPPORT)
/**
  * @brief Enable the Power Voltage Monitoring for USB peripheral (power domain Vddio2)
  * @retval None
  */
void HAL_PWREx_EnablePVMUSB(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVM_VDDIO2_0);
}

/**
  * @brief Disable the Power Voltage Monitoring for USB peripheral (power domain Vddio2)
  * @retval None
  */
void HAL_PWREx_DisablePVMUSB(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVM_VDDIO2_0);
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
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_PVM_TYPE(sConfigPVM->PVMType));
  assert_param(IS_PWR_PVM_MODE(sConfigPVM->Mode));

  /* Configure EXTI 34 interrupts if so required:
     scan through PVMType to detect which PVMx is set and
     configure the corresponding EXTI line accordingly. */
  switch (sConfigPVM->PVMType)
  {
    case PWR_PVM_USB:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM_EXTI_DISABLE_IT();
      __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}
#endif /* PWR_PVM_SUPPORT */
/**
  * @brief  Enable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_EnableInternalWakeUpLine(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EIWUL);
}


/**
  * @brief  Disable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_DisableInternalWakeUpLine(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EIWUL);
}


/**
  * @brief  Enable GPIO pull-up state in Standby and Shutdown modes.
  * @note   Set the relevant PUy bit of PWR_PUCRx register to configure the I/O in
  *         pull-up state in Standby and Shutdown modes.
  * @note   This state is effective in Standby and Shutdown modes only if APC bit
  *         is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is lost when exiting the Shutdown mode due to the
  *         power-on reset, maintained when exiting the Standby mode.
  * @note   To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *         PDy bit of PWR_PDCRx register is cleared unless it is reserved.
  * @param  GPIO Specify the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
  *         I/O pins are available) or the logical OR of several of them to set
  *         several bits for a given port in a single API call.
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

    case PWR_GPIO_C:
      SET_BIT(PWR->PUCRC, GPIONumber);
      CLEAR_BIT(PWR->PDCRC, GPIONumber);
      break;
#if defined (GPIOD)
    case PWR_GPIO_D:
      SET_BIT(PWR->PUCRD, GPIONumber);
      CLEAR_BIT(PWR->PDCRD, GPIONumber);
      break;
#endif /* GPIOD */
    case PWR_GPIO_F:
      SET_BIT(PWR->PUCRF, GPIONumber);
      CLEAR_BIT(PWR->PDCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Disable GPIO pull-up state in Standby mode and Shutdown modes.
  * @note   Reset the relevant PUy bit of PWR_PUCRx register used to configure the I/O
  *         in pull-up state in Standby and Shutdown modes.
  * @param  GPIO Specifies the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
  *         I/O pins are available) or the logical OR of several of them to reset
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

    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PUCRC, GPIONumber);
      break;
#if defined (GPIOD)
    case PWR_GPIO_D:
      CLEAR_BIT(PWR->PUCRD, GPIONumber);
      break;
#endif /* GPIOD */
    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PUCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Enable GPIO pull-down state in Standby and Shutdown modes.
  * @note   Set the relevant PDy bit of PWR_PDCRx register to configure the I/O in
  *         pull-down state in Standby and Shutdown modes.
  * @note   This state is effective in Standby and Shutdown modes only if APC bit
  *         is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is lost when exiting the Shutdown mode due to the
  *         power-on reset, maintained when exiting the Standby mode.
  * @note   To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *         PUy bit of PWR_PUCRx register is cleared unless it is reserved.
  * @param  GPIO Specify the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
  *         I/O pins are available) or the logical OR of several of them to set
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

    case PWR_GPIO_C:
      SET_BIT(PWR->PDCRC, GPIONumber);
      CLEAR_BIT(PWR->PUCRC, GPIONumber);
      break;
#if defined (GPIOD)
    case PWR_GPIO_D:
      SET_BIT(PWR->PDCRD, GPIONumber);
      CLEAR_BIT(PWR->PUCRD, GPIONumber);
      break;
#endif /* GPIOD */
    case PWR_GPIO_F:
      SET_BIT(PWR->PDCRF, GPIONumber);
      CLEAR_BIT(PWR->PUCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Disable GPIO pull-down state in Standby and Shutdown modes.
  * @note   Reset the relevant PDy bit of PWR_PDCRx register used to configure the I/O
  *         in pull-down state in Standby and Shutdown modes.
  * @param  GPIO Specifies the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
  *         I/O pins are available) or the logical OR of several of them to reset
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

    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PDCRC, GPIONumber);
      break;
#if defined (GPIOD)
    case PWR_GPIO_D:
      CLEAR_BIT(PWR->PDCRD, GPIONumber);
      break;
#endif /* GPIOD */
    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PDCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Enable pull-up and pull-down configuration.
  * @note   When APC bit is set, the I/O pull-up and pull-down configurations defined in
  *         PWR_PUCRx and PWR_PDCRx registers are applied in Standby and Shutdown modes.
  * @note   Pull-up set by PUy bit of PWR_PUCRx register is not activated if the corresponding
  *         PDy bit of PWR_PDCRx register is also set (pull-down configuration priority is higher).
  *         HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() APIs ensure there
  *         is no conflict when setting PUy or PDy bit.
  * @retval None
  */
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration.
  * @note   When APC bit is cleared, the I/O pull-up and pull-down configurations defined in
  *         PWR_PUCRx and PWR_PDCRx registers are not applied in Standby and Shutdown modes.
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_APC);
}


/**
  * @brief  Enable Flash Power Down.
  * @note   This API allows to enable flash power down capabilities in sleep and stop modes.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_SLEEP
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
  * @note   This API allows to disable flash power down capabilities in sleep and stop modes.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_SLEEP
  *           @arg @ref PWR_FLASHPD_STOP
  * @retval None
  */
void HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode)
{
  assert_param(IS_PWR_FLASH_POWERDOWN(PowerMode));

  PWR->CR1 &= ~PowerMode;
}


/**
  * @brief  Enter Shutdown mode.
  * @note   In Shutdown mode, the PLL, the HSI, the LSI and the HSE oscillators are switched
  *         off. The voltage regulator is disabled and Vcore domain is powered off.
  *         SRAM and registers contents are lost except for registers in the Backup domain.
  *         The BOR is not available.
  * @note   The I/Os can be configured either with a pull-up or pull-down or can
  *         be kept in analog state.
  *         HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown()
  *         respectively enable Pull Up and PullDown state.
  *         HAL_PWREx_DisableGPIOPullUp() & HAL_PWREx_DisableGPIOPullDown()
  *         disable the same. These states are effective in Standby mode only if
  *         APC bit is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @retval None

  * @retval None
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{
  /* Set Shutdown mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_LOWPOWERMODE_SHUTDOWN);

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

/** @addtogroup PWREx_Exported_Functions_Group2 Extended PWR Backup register functions
  * @brief      Extended PWR Backup register functions
  *
@verbatim
  ===============================================================================
             ##### Extended PWR Backup register functions #####
  ===============================================================================
  [..]
   This subsection provides functions allowing to
   (+) Write a data in a specified PWR Backup data register
   (+) Read a data in a specified PWR Backup data register
@endverbatim
  * @{
  */


/**
  * @brief  Write a data in a specified PWR Backup data register.
  * @param  BackupRegister PWR Backup data Register number.
  *          This parameter can be PWR_BKP_DRx where x can be from 0 to PWR_BACKUP_NB
  * @param  Data Data to be written in the specified Backup data register.
  * @retval None
  */
void HAL_PWREx_BKUPWrite(uint32_t BackupRegister, uint16_t Data)
{
  uint32_t tmp;

  /* Check the parameters */
  assert_param(IS_PWR_BKP(BackupRegister));

  tmp = (uint32_t) &(PWR->BKP0R);
  tmp += (BackupRegister * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint16_t)Data;
}


/**
  * @brief  Reads data from the specified PWR Backup data Register.
  * @param  BackupRegister PWR Backup data Register number.
  *          This parameter can be PWR_BKP_DRx where x can be from 0 to PWR_BACKUP_NB
  * @retval Read value
  */
uint32_t HAL_PWREx_BKUPRead(uint32_t BackupRegister)
{
  uint32_t tmp;

  /* Check the parameters */
  assert_param(IS_PWR_BKP(BackupRegister));

  tmp = (uint32_t) &(PWR->BKP0R);
  tmp += (BackupRegister * 4U);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
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
