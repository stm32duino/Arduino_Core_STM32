/**
  ******************************************************************************
  * @file    stm32u3xx_hal.c
  * @author  MCD Application Team
  * @brief   HAL module driver.
  *          This is the common part of the HAL initialization
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
    The common HAL driver contains a set of generic and common APIs that can be
    used by the PPP peripheral drivers and the user to start using the HAL.
    [..]
    The HAL contains two APIs' categories:
         (+) Common HAL APIs
         (+) Services HAL APIs

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @defgroup HAL HAL
  * @brief HAL module driver
  * @{
  */

#ifdef HAL_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/** @defgroup HAL_Private_Defines HAL Private Defines
  * @{
  */
#define VREFBUF_TIMEOUT_VALUE           10U   /* 10 ms (to be confirmed) */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/** @defgroup HAL_Exported_Variables HAL Exported Variables
  * @{
  */
__IO uint32_t uwTick;
uint32_t uwTickPrio   = (1UL << __NVIC_PRIO_BITS); /* Invalid PRIO */
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 Initialization and de-initialization Functions
  *  @brief    Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initializes the Flash interface the NVIC allocation and initial clock
          configuration. It initializes the systick also when timeout is needed
          and the backup domain when enabled.
      (+) De-Initializes common part of the HAL.
      (+) Configure The time base source to have 1ms time base with a dedicated
          Tick interrupt priority.
        (++) SysTick timer is used by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
        (++) Time base configuration function (HAL_InitTick ()) is called automatically
             at the beginning of the program after reset by HAL_Init() or at any time
             when clock is configured, by HAL_RCC_ClockConfig().
        (++) Source of time base is configured  to generate interrupts at regular
             time intervals. Care must be taken if HAL_Delay() is called from a
             peripheral ISR process, the Tick interrupt line must have higher priority
            (numerically lower) than the peripheral interrupt. Otherwise the caller
            ISR process will be blocked.
       (++) functions affecting time base configurations are declared as __weak
             to make  override possible  in case of other  implementations in user file.
@endverbatim
  * @{
  */

/**
  * @brief  Configure the Flash prefetch, the time base source, NVIC and any required global low
  *         level hardware by calling the HAL_MspInit() callback function to be optionally defined
  *         in user file stm32u3xx_hal_msp.c.
  *
  * @note   HAL_Init() function is called at the beginning of program after reset and before
  *         the clock configuration.
  *
  * @note   In the default implementation the System Timer (SysTick) is used as source of time base.
  *         The SysTick configuration is based on MSI clock, as MSI is the clock
  *         used after a system Reset and the NVIC configuration is set to Priority group 4.
  *         Once done, time base tick starts incrementing: the tick variable counter is incremented
  *         each 1ms in the SysTick_Handler() interrupt handler.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_Init(void)
{
  /* Configure Flash prefetch */
#if (PREFETCH_ENABLE != 0U)
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif /* PREFETCH_ENABLE */

  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Ensure time base clock coherency */
  SystemCoreClockUpdate();

  /* Select HCLK as SysTick clock source */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* Initialize 1ms tick time base (default SysTick based on MSI clock after Reset) */
  if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Init the low level hardware */
  HAL_MspInit();

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  This function de-Initializes common part of the HAL and stops the systick.
  *         This function is optional.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* Reset of all peripherals */
  __HAL_RCC_AHB1_FORCE_RESET();
  __HAL_RCC_AHB1_RELEASE_RESET();

  __HAL_RCC_AHB2_FORCE_RESET();
  __HAL_RCC_AHB2_RELEASE_RESET();

  __HAL_RCC_APB1_FORCE_RESET();
  __HAL_RCC_APB1_RELEASE_RESET();

  __HAL_RCC_APB2_FORCE_RESET();
  __HAL_RCC_APB2_RELEASE_RESET();

  __HAL_RCC_APB3_FORCE_RESET();
  __HAL_RCC_APB3_RELEASE_RESET();

  /* De-Init the low level hardware */
  HAL_MspDeInit();

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the MSP.
  * @retval None
  */
__weak void HAL_MspInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes the MSP.
  * @retval None
  */
__weak void HAL_MspDeInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MspDeInit could be implemented in the user file
   */
}

/**
  * @brief This function configures the source of the time base.
  *        The time source is configured to have 1ms time base with a dedicated
  *        Tick interrupt priority.
  * @note This function is called  automatically at the beginning of program after
  *       reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig().
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals.
  *       Care must be taken if HAL_Delay() is called from a peripheral ISR process,
  *       The SysTick interrupt must have higher priority (numerically lower)
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __weak  to be overwritten  in case of other
  *       implementation  in user file.
  * @param TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  uint32_t ticknumber = 0U;
  uint32_t systicksel;

  /* Check uwTickFreq for MisraC 2012 (even if uwTickFreq is a enum type that don't take the value zero)*/
  if ((uint32_t)uwTickFreq == 0UL)
  {
    return HAL_ERROR;
  }

  /* Check Clock source to calculate the tickNumber */
  if(READ_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk) == SysTick_CTRL_CLKSOURCE_Msk)
  {
    /* HCLK selected as SysTick clock source */
    ticknumber = SystemCoreClock / (1000UL / (uint32_t)uwTickFreq);
  }
  else
  {
    systicksel = __HAL_RCC_GET_SYSTICK_SOURCE();
    switch (systicksel)
    {
      /* HCLK_DIV8 selected as SysTick clock source */
      case RCC_SYSTICKCLKSOURCE_HCLK_DIV8:
        /* Calculate tick value */
        ticknumber = (SystemCoreClock / (8000UL / (uint32_t)uwTickFreq));
        break;

      /* LSI selected as SysTick clock source */
      case RCC_SYSTICKCLKSOURCE_LSI:
        /* Calculate tick value */
        ticknumber = (LSI_VALUE / (1000UL / (uint32_t)uwTickFreq));
        break;

      /* LSE selected as SysTick clock source */
      case RCC_SYSTICKCLKSOURCE_LSE:
        /* Calculate tick value */
        ticknumber = (LSE_VALUE / (1000UL / (uint32_t)uwTickFreq));
        break;

      default:
        /* Nothing to do */
        break;
    }
  }

  /* Configure the SysTick */
  if (HAL_SYSTICK_Config(ticknumber) > 0U)
  {
    return HAL_ERROR;
  }

  /* Configure the SysTick IRQ priority */
  HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);
  uwTickPrio = TickPriority;

  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HAL_Group2 HAL Control functions
  *  @brief    HAL Control functions
  *
@verbatim
 ===============================================================================
                      ##### HAL Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the HAL API driver version
      (+) Get the device identifier
      (+) Get the device revision identifier
      (+) Enable/Disable Debug module during SLEEP mode
      (+) Enable/Disable Debug module during STOP mode
      (+) Enable/Disable Debug module during STANDBY mode

@endverbatim
  * @{
  */

/**
  * @brief This function is called to increment a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
__weak void HAL_IncTick(void)
{
  uwTick += (uint32_t)uwTickFreq;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function returns a tick priority.
  * @retval tick priority
  */
uint32_t HAL_GetTickPrio(void)
{
  return uwTickPrio;
}

/**
  * @brief Set new tick Freq.
  * @retval Status
  */
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq)
{
  HAL_StatusTypeDef status  = HAL_OK;
  HAL_TickFreqTypeDef prevTickFreq;

  assert_param(IS_TICKFREQ(Freq));

  if (uwTickFreq != Freq)
  {

    /* Back up uwTickFreq frequency */
    prevTickFreq = uwTickFreq;

    /* Update uwTickFreq global variable used by HAL_InitTick() */
    uwTickFreq = Freq;

    /* Apply the new tick Freq  */
    status = HAL_InitTick(uwTickPrio);
    if (status != HAL_OK)
    {
      /* Restore previous tick frequency */
      uwTickFreq = prevTickFreq;
    }
  }

  return status;
}

/**
  * @brief Return tick frequency.
  * @retval Tick frequency.
  *         Value of @ref HAL_TickFreqTypeDef.
  */
HAL_TickFreqTypeDef HAL_GetTickFreq(void)
{
  return uwTickFreq;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay  specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void HAL_SuspendTick(void)
{
  /* Disable SysTick Interrupt */
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void HAL_ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief  Returns the HAL revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t HAL_GetHalVersion(void)
{
  return __STM32U3xx_HAL_VERSION;
}

/**
  * @brief  Returns the device revision identifier.
  * @retval Device revision identifier
  */
uint32_t HAL_GetREVID(void)
{
  return ((DBGMCU->IDCODE & DBGMCU_IDCODE_REV_ID) >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @retval Device identifier
  */
uint32_t HAL_GetDEVID(void)
{
  return (DBGMCU->IDCODE & DBGMCU_IDCODE_DEV_ID);
}

/**
  * @brief  Return the first word of the unique device identifier (UID based on 96 bits)
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw0(void)
{
  return (READ_REG(*((uint32_t *)UID_BASE)));
}

/**
  * @brief  Return the second word of the unique device identifier (UID based on 96 bits)
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw1(void)
{
  return (READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}

/**
  * @brief  Return the third word of the unique device identifier (UID based on 96 bits)
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw2(void)
{
  return (READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}

/**
  * @}
  */


/** @defgroup HAL_Exported_Functions_Group3 HAL Debug functions
  *  @brief    HAL Debug functions
  *
@verbatim
 ===============================================================================
                      ##### HAL Debug functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Enable/Disable Debug module during STOP0/STOP1/STOP2 modes
      (+) Enable/Disable Debug module during STANDBY mode

@endverbatim
  * @{
  */

/**
  * @brief  Enable the Debug Module during STOP0/STOP1/STOP2 modes.
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP0/STOP1/STOP2 modes.
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode.
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode.
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group4 HAL SYSCFG configuration functions
  *  @brief    HAL SYSCFG configuration functions
  *
@verbatim
 ===============================================================================
                      ##### HAL SYSCFG configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the Voltage reference buffer
      (+) Enable/Disable the Voltage reference buffer
      (+) Enable/Disable the I/O analog switch voltage booster
      (+) Configure/Enable/Disable the compensation cell (VDD,VDDIO2)

@endverbatim
  * @{
  */

/**
  * @brief Configure the internal voltage reference buffer voltage scale.
  * @param  VoltageScaling: specifies the output voltage to achieve
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_VREFBUF_VOLTAGE_SCALE0: VREF_OUT1 around 1.5 V.
  *                                                This requires VDDA equal to or higher than 1.8 V.
  *            @arg SYSCFG_VREFBUF_VOLTAGE_SCALE1: VREF_OUT1 around 1.8 V.
  *                                                This requires VDDA equal to or higher than 2.1 V.
  *            @arg SYSCFG_VREFBUF_VOLTAGE_SCALE2: VREF_OUT1 around 2.048 V.
  *                                                This requires VDDA equal to or higher than 2.4 V.
  *            @arg SYSCFG_VREFBUF_VOLTAGE_SCALE3: VREF_OUT1 around 2.5 V.
  *                                                This requires VDDA equal to or higher than 2.8 V.
  * @retval None
  */
void HAL_SYSCFG_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_VREFBUF_VOLTAGE_SCALE(VoltageScaling));

  MODIFY_REG(VREFBUF->CSR, VREFBUF_CSR_VRS, VoltageScaling);
}

/**
  * @brief Configure the internal voltage reference buffer high impedance mode.
  * @param  Mode: specifies the high impedance mode
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE: VREF+ pin is internally connect to VREFINT output.
  *            @arg SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE: VREF+ pin is high impedance.
  * @retval None
  */
void HAL_SYSCFG_VREFBUF_HighImpedanceConfig(uint32_t Mode)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_VREFBUF_HIGH_IMPEDANCE(Mode));

  MODIFY_REG(VREFBUF->CSR, VREFBUF_CSR_HIZ, Mode);
}

/**
  * @brief  Tune the Internal Voltage Reference buffer (VREFBUF).
  * @retval None
  */
void HAL_SYSCFG_VREFBUF_TrimmingConfig(uint32_t TrimmingValue)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_VREFBUF_TRIMMING(TrimmingValue));

  MODIFY_REG(VREFBUF->CCR, VREFBUF_CCR_TRIM, TrimmingValue);
}

/**
  * @brief  Enable the Internal Voltage Reference buffer (VREFBUF).
  * @retval HAL_OK/HAL_TIMEOUT
  */
HAL_StatusTypeDef HAL_SYSCFG_EnableVREFBUF(void)
{
  uint32_t  tickstart;

  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* VRR detection is only available when bit HIZ is cleared */
  if (READ_BIT(VREFBUF->CSR, VREFBUF_CSR_HIZ) == 0UL)
  {
    /* Wait for VRR bit  */
    while (READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRR) == 0UL)
    {
      if ((HAL_GetTick() - tickstart) > VREFBUF_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Disable the Internal Voltage Reference buffer (VREFBUF).
  *
  * @retval None
  */
void HAL_SYSCFG_DisableVREFBUF(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  Enable the I/O analog switch voltage booster
  *
  * @retval None
  */
void HAL_SYSCFG_EnableIOAnalogBooster(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Disable the I/O analog switch voltage booster
  *
  * @retval None
  */
void HAL_SYSCFG_DisableIOAnalogBooster(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Enable the I/O analog switch voltage booster
  *
  * @retval None
  */
void HAL_SYSCFG_EnableIOAnalogSwitchVdd(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ANASWVDD);
}

/**
  * @brief  Disable the I/O analog switch voltage booster
  *
  * @retval None
  */
void HAL_SYSCFG_DisableIOAnalogSwitchVdd(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ANASWVDD);
}

/**
  * @brief  Enable the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can the combination of the following values:
  *            @arg SYSCFG_IO_VDD_CELL Compensation cell for the I/O supplied by vdd
  *            @arg SYSCFG_IO_VDDIO2_CELL Compensation cell for the I/O supplied by vddio2
  * @note   The vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  * @retval None
  */
void HAL_SYSCFG_EnableCompensationCell(uint32_t Selection)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_COMPENSATION_CELL(Selection));

  SET_BIT(SYSCFG->CCCSR, Selection);
}

/**
  * @brief  Disable the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can the combination of the following values:
  *            @arg SYSCFG_IO_VDD_CELL Compensation cell for the I/O supplied by vdd
  *            @arg SYSCFG_IO_VDDIO2_CELL Compensation cell for the I/O supplied by vddio2
  * @note   The vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  * @retval None
  */
void HAL_SYSCFG_DisableCompensationCell(uint32_t Selection)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_COMPENSATION_CELL(Selection));

  CLEAR_BIT(SYSCFG->CCCSR, Selection);
}

/**
  * @brief  Get the compensation cell ready status
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can one of the following values:
  *            @arg SYSCFG_IO_VDD_CELL Compensation cell for the I/O supplied by vdd
  *            @arg SYSCFG_IO_VDDIO2_CELL Compensation cell for the I/O supplied by vddio2
  * @retval Ready status (1 or 0)
  */
uint32_t HAL_SYSCFG_GetCompensationCellReadyStatus(uint32_t Selection)
{
  uint32_t flag;

  /* Check the parameter */
  assert_param(IS_SYSCFG_COMPENSATION_CELL(Selection));

  if (Selection == SYSCFG_IO_VDD_CELL)
  {
    flag = (((SYSCFG->CCCSR & SYSCFG_CCCSR_RDY1) == 0U) ? 0UL : 1UL);
  }
  else /* SYSCFG_IO_VDDIO2_CELL */
  {
    flag = (((SYSCFG->CCCSR & SYSCFG_CCCSR_RDY2) == 0U) ? 0UL : 1UL);
  }

  return flag;
}

/**
  * @brief  Configure the code selection for the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can one of the following values:
  *            @arg SYSCFG_IO_VDD_CELL Compensation cell for the I/O supplied by vdd
  *            @arg SYSCFG_IO_VDDIO2_CELL Compensation cell for the I/O supplied by vddio2
  * @param  Code code selection to be applied for the I/O compensation cell
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_IO_CELL_CODE  Code from the cell (available in the SYSCFG_CCVR)
  *            @arg SYSCFG_IO_REGISTER_CODE Code from the compensation cell code register (SYSCFG_CCCR)
  * @param  NmosValue In case SYSCFG_IO_REGISTER_CODE is selected, it  provides the Nmos value
  *                   to apply in range 0 to 15 else this parameter is not used
  * @param  PmosValue In case SYSCFG_IO_REGISTER_CODE is selected, it  provides the Pmos value
  *                   to apply in range 0 to 15 else this parameter is not used
  * @retval None
  */
void HAL_SYSCFG_ConfigCompensationCell(uint32_t Selection, uint32_t Code, uint32_t NmosValue, uint32_t PmosValue)
{
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_SYSCFG_COMPENSATION_CELL(Selection));
  assert_param(IS_SYSCFG_IO_COMPENSATION_CODE(Code));

  if (Code == SYSCFG_IO_REGISTER_CODE)
  {
    /* Check the parameters */
    assert_param(IS_SYSCFG_IO_COMPENSATION_CELL_NMOS_VALUE(NmosValue));
    assert_param(IS_SYSCFG_IO_COMPENSATION_CELL_PMOS_VALUE(PmosValue));

    offset = ((Selection == SYSCFG_IO_VDD_CELL) ? 0U : 8U);

    MODIFY_REG(SYSCFG->CCCR, (0xFFU << offset), ((NmosValue << offset) | (PmosValue << (offset + 4U))));
  }

  MODIFY_REG(SYSCFG->CCCSR, (Selection << 1U), (Code << (POSITION_VAL(Selection) + 1U)));
}

/**
  * @brief  Get the code selection for the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can one of the following values:
  *            @arg SYSCFG_IO_VDD_CELL Compensation cell for the I/O supplied by vdd
  *            @arg SYSCFG_IO_VDDIO2_CELL Compensation cell for the I/O supplied by vddio2
  * @param  pCode pointer code selection
  * @param  pNmosValue pointer to the Nmos value in range 0 to 15
  * @param  pPmosValue pointer to the Pmos value in range 0 to 15
  * @retval  HAL_OK (all values available) or HAL_ERROR (check parameters)
  */
HAL_StatusTypeDef HAL_SYSCFG_GetCompensationCell(uint32_t Selection, uint32_t *pCode, uint32_t *pNmosValue,
                                                 uint32_t *pPmosValue)
{
  uint32_t reg;
  uint32_t offset;
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Check parameters */
  if ((pCode != NULL) && (pNmosValue != NULL) && (pPmosValue != NULL))
  {
    *pCode = ((SYSCFG->CCCSR & (Selection << 1U)) == 0U) ? SYSCFG_IO_CELL_CODE : SYSCFG_IO_REGISTER_CODE;

    reg = (*pCode == SYSCFG_IO_CELL_CODE) ? (SYSCFG->CCVR) : (SYSCFG->CCCR);
    offset = ((Selection == SYSCFG_IO_VDD_CELL) ? 0U : 8U);

    *pNmosValue = ((reg >> offset) & 0xFU);
    *pPmosValue = ((reg >> (offset + 4U)) & 0xFU);

    status = HAL_OK;
  }
  return status;
}

/**
  * @brief  Configure the infrared (IR) interface
  * @param  Modulation
  *         This parameter can one of the following values:
  *            @arg SYSCFG_IR_MOD_TIM16
  *            @arg SYSCFG_IR_MOD_USART1
  *            @arg SYSCFG_IR_MOD_UART4
  * @param  OutputPol
  *         This parameter can one of the following values:
  *            @arg SYSCFG_IR_OUTPUTPOL_NONINVERTED
  *            @arg SYSCFG_IR_OUTPUTPOL_INVERTED
  * @retval  None
  */
void HAL_SYSCFG_ConfigIR(uint32_t Modulation, uint32_t OutputPol)
{
  assert_param(IS_SYSCFG_IR_MODULATION(Modulation));
  assert_param(IS_SYSCFG_IR_OUTPUTPOL(OutputPol));

  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_IR_MOD | SYSCFG_CFGR1_IR_POL, Modulation | OutputPol);
}

/**
  * @brief  Get the infrared (IR) interface configuration
  * @param  pModulation pointer to Modulation
  * @param  pOutputPol  pointer to Output Polarity
  * @retval  HAL_OK (all values available) or HAL_ERROR (check parameters)
  */
HAL_StatusTypeDef HAL_SYSCFG_GetConfigIR(uint32_t *pModulation, uint32_t *pOutputPol)
{
  uint32_t reg;
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Check parameters */
  if ((pModulation != NULL) && (pOutputPol != NULL))
  {
    reg = SYSCFG->CFGR1;

    *pModulation = (uint32_t)(READ_BIT(reg, SYSCFG_CFGR1_IR_MOD));
    *pOutputPol  = (uint32_t)(READ_BIT(reg, SYSCFG_CFGR1_IR_POL));

    status = HAL_OK;
  }
  return status;
}

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group5 HAL SYSCFG lock management functions
  *  @brief SYSCFG lock management functions.
  *
@verbatim
 ===============================================================================
                       ##### SYSCFG lock functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Lock the SYSCFG item(s).
  * @note   Setting lock(s) depends on privilege mode in secure/non-secure code
  *         Lock(s) cleared only at system reset
  * @param  Item Item(s) to set lock on.
  *         This parameter can be a combination of @ref SYSCFG_Lock_items
  * @retval None
  */
void HAL_SYSCFG_Lock(uint32_t Item)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_LOCK_ITEMS(Item));

  /* Privilege secure/non-secure locks */
  SYSCFG->CNSLCKR = (0xFFFFU & Item);  /* non-secure lock item in 16 lowest bits */

#if defined (CPU_IN_SECURE_STATE)
  /* Privilege secure only locks */
  SYSCFG->CSLCKR = ((0xFFFF0000U & Item) >> 16U);  /* Secure-only lock item in 16 highest bits */
#endif /* CPU_IN_SECURE_STATE */
}

/**
  * @brief  Get the lock state of SYSCFG item.
  * @note   Getting lock(s) depends on privilege mode in secure/non-secure code
  * @param  pItem pointer to return locked items
  *         the return value can be a combination of @ref SYSCFG_Lock_items
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SYSCFG_GetLock(uint32_t *pItem)
{
  uint32_t tmp_lock;

  /* Check null pointer */
  if (pItem == NULL)
  {
    return HAL_ERROR;
  }

  /* Get the non-secure lock state */
  tmp_lock = SYSCFG->CNSLCKR;

  /* Get the secure lock state in secure code */
#if defined (CPU_IN_SECURE_STATE)
  tmp_lock |= (SYSCFG->CSLCKR << 16U);
#endif /* CPU_IN_SECURE_STATE */

  /* Return overall lock status */
  *pItem = tmp_lock;

  return HAL_OK;
}

/**
  * @}
  */


/** @defgroup HAL_Exported_Functions_Group6 HAL SYSCFG attributes management functions
  *  @brief SYSCFG attributes management functions.
  *
@verbatim
 ===============================================================================
                       ##### SYSCFG attributes functions #####
 ===============================================================================

@endverbatim
  * @{
  */

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Configure the SYSCFG item attribute(s).
  * @note   Available attributes are to secure SYSCFG items, so this function is
  *         only available in secure
  * @param  Item Item(s) to set attributes on.
  *         This parameter can be a one or a combination of @ref SYSCFG_Attributes_items
  * @param  Attributes  specifies the secure/non-secure attributes.
  * @retval None
  */
void HAL_SYSCFG_ConfigAttributes(uint32_t Item, uint32_t Attributes)
{
  uint32_t tmp;

  /* Check the parameters */
  assert_param(IS_SYSCFG_ITEMS_ATTRIBUTES(Item));
  assert_param(IS_SYSCFG_ATTRIBUTES(Attributes));

  tmp = SYSCFG_S->SECCFGR;

  /* Set or reset Item */
  if ((Attributes & SYSCFG_SEC) != 0x00U)
  {
    tmp |= Item;
  }
  else
  {
    tmp &= ~Item;
  }

  /* Set secure attributes */
  SYSCFG_S->SECCFGR = tmp;
}

#endif /* CPU_IN_SECURE_STATE */

/**
  * @brief  Get the attribute of a SYSCFG item.
  * @note   Available attributes are to secure SYSCFG items, so this function is
  *         only available in secure
  * @param  Item Single item to get secure/non-secure attribute from.
  * @param  pAttributes pointer to return the attribute.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SYSCFG_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes)
{
  /* Check null pointer */
  if (pAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_SYSCFG_SINGLE_ITEMS_ATTRIBUTES(Item));

  /* Get the secure attribute state */
  if ((SYSCFG->SECCFGR & Item) != 0U)
  {
    *pAttributes = SYSCFG_SEC;
  }
  else
  {
    *pAttributes = SYSCFG_NSEC;
  }

  return HAL_OK;
}

/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
