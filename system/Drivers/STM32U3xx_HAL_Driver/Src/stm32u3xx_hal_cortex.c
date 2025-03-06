/**
  ******************************************************************************
  * @file    stm32u3xx_hal_cortex.c
  * @author  MCD Application Team
  * @brief   CORTEX HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORTEX:
  *           + Initialization and Configuration functions
  *           + Peripheral Control functions
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
    *** How to configure Interrupts using CORTEX HAL driver ***
    ===========================================================
    [..]
    This section provides functions allowing to configure the NVIC interrupts (IRQ).
    The Cortex-M33 exceptions are managed by CMSIS functions.

    (#) Configure the NVIC Priority Grouping using HAL_NVIC_SetPriorityGrouping() function.
    (#) Configure the priority of the selected IRQ Channels using HAL_NVIC_SetPriority().
    (#) Enable the selected IRQ Channels using HAL_NVIC_EnableIRQ().

     -@- When the NVIC_PRIORITYGROUP_0 is selected, IRQ pre-emption is no more possible.
         The pending IRQ priority will be managed only by the sub priority.

     -@- IRQ priority order (sorted by highest to lowest priority):
        (+@) Lowest pre-emption priority
        (+@) Lowest sub priority
        (+@) Lowest hardware priority (IRQ number)

    [..]
    *** How to configure SysTick using CORTEX HAL driver ***
    ========================================================
    [..]
    Setup SysTick Timer for time base.

   (+) The HAL_SYSTICK_Config() function calls the SysTick_Config() function which
       is a CMSIS function that:
        (++) Configures the SysTick Reload register with value passed as function parameter.
        (++) Configures the SysTick IRQ priority to the lowest value (0x0F).
        (++) Resets the SysTick Counter register.
        (++) Configures the SysTick Counter clock source to be Core Clock Source (HCLK).
        (++) Enables the SysTick Interrupt.
        (++) Starts the SysTick Counter.

   (+) You can change the SysTick Clock source to be HCLK_Div8 by calling the macro
       __HAL_CORTEX_SYSTICKCLK_CONFIG(SYSTICK_CLKSOURCE_HCLK_DIV8) just after the
       HAL_SYSTICK_Config() function call. The __HAL_CORTEX_SYSTICKCLK_CONFIG() macro is defined
       inside the stm32u3xx_hal_cortex.h file.

   (+) You can change the SysTick IRQ priority by calling the
       HAL_NVIC_SetPriority(SysTick_IRQn,...) function just after the HAL_SYSTICK_Config() function
       call. The HAL_NVIC_SetPriority() call the NVIC_SetPriority() function which is a CMSIS function.

   (+) To adjust the SysTick time base, use the following formula:

       Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
       (++) Reload Value is the parameter to be passed for HAL_SYSTICK_Config() function
       (++) Reload Value should not exceed 0xFFFFFF

    [..]
    *** How to configure MPU using CORTEX HAL driver ***
    ========================================================
    [..]
    This section provides functions allowing to configure the MPU.
    The Cortex-M33 includes a memory protection unit (MPU) that can restrict the read and write accesses to
    memory regions (including regions mapped to peripherals).
    In Armv8-M architecture, memory types are divided into:
      (#) normal memory
      (#) device memory

    A normal memory has the following attributes:
    (#) cacheability: memories cacheable or non-cacheable
    (#) shareability: normal memory shareable or non-shareable
    (#) execute never: memories marked as executable or execute never (XN)

    A device memory has the following attributes:
    (#) G or nG: gathering or non-gathering. (multiple accesses to a device can be merged into a single
    transaction except for operations with memory ordering semantics, for example, memory barrier
    instructions, load acquire/store release).
    (#) R or nR: reordering
    (#) E or nE: early write acknowledge (similar to bufferable)

    Only four combinations of these attributes are valid:
    (#) device-nGnRnE: equivalent to Armv7-M strongly ordered memory type
    (#) device-nGnRE: equivalent to Armv7-M device memory
    (#) device-nGRE: new to Armv8-M
    (#) device-GRE: new to Armv8-M

    A normal memory has the following attributes:
    (#) Cache Allocation attribute : set when a cache line is allocated (no allocation, read/write/read-write allocation)
    (#) Cache write policy : write through (write to cache AND memory), write back (memory is written when the cache line is evicted)
    (#) Transient : indicates that the region will be used for a short period of time
    For normal memory, attributes can be set for inner and outer caches separately.
    Note that outer attributes set to 0 change the memory to device mode. Both inner and outer attributes should be set for normal memory.

    Sample configurations
    (#) Inner-outer cacheable, write back, read-write allocate INNER_OUTER(MPU_RW_ALLOCATE | MPU_WRITE_BACK)
    (#) Inner write back, read allocation, outer non-cacheable (MPU_R_ALLOCATE | MPU_WRITE_BACK) | OUTER(MPU_NOT_CACHEABLE)
    For detail on memory attributes, refer to the ARMv8-m MPU documentation.

    On STM32U3xx, the MPUs are split memory into regions (up to eight for the non-secure MPU,
    and up to twelve for the secure MPU).
    The secure MPU is only available when TrustZone is activated.

    (#) Enable the MPU using HAL_MPU_Enable() function or HAL_MPU_Enable_NS function for non-secure MPU.
    (#) Disable the MPU using HAL_MPU_Disable() function or HAL_MPU_Disable_NS function for non-secure MPU.
    (#) Enable the MPU region using HAL_MPU_EnableRegion() function or HAL_MPU_EnableRegion_NS function for non-secure MPU region.
    (#) Disable the MPU region using HAL_MPU_DisableRegion() function or HAL_MPU_DisableRegion_NS function for non-secure MPU region.
    (#) Configure the MPU region using HAL_MPU_ConfigRegion() function or HAL_MPU_ConfigRegion_NS function
        for non-secure MPU.
    (#) Configure the MPU memory attributes using HAL_MPU_ConfigMemoryAttributes() function or
        HAL_MPU_ConfigMemoryAttributes_NS function for non-secure MPU.

    (#) The HAL_MPU_XXX_NS functions are only available when TrustZone is activated and CPU in secure state.
        _NS functions are targeting non secure MPU, in any other cases APIs without NS shall be used.

  @endverbatim
  ******************************************************************************

  The table below gives the allowed values of the pre-emption priority and subpriority according
  to the Priority Grouping configuration performed by HAL_NVIC_SetPriorityGrouping() function.

    =================================================================================================================
      NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPrio | NVIC_IRQChannelSubPrio |       Description
    =================================================================================================================
     NVIC_PRIORITYGROUP_0  |                0              |            0-15        | 0 bit for pre-emption priority
                           |                               |                        | 4 bits for subpriority
    -----------------------------------------------------------------------------------------------------------------
     NVIC_PRIORITYGROUP_1  |                0-1            |            0-7         | 1 bit for pre-emption priority
                           |                               |                        | 3 bits for subpriority
    -----------------------------------------------------------------------------------------------------------------
     NVIC_PRIORITYGROUP_2  |                0-3            |            0-3         | 2 bits for pre-emption priority
                           |                               |                        | 2 bits for subpriority
    -----------------------------------------------------------------------------------------------------------------
     NVIC_PRIORITYGROUP_3  |                0-7            |            0-1         | 3 bits for pre-emption priority
                           |                               |                        | 1 bit for subpriority
    -----------------------------------------------------------------------------------------------------------------
     NVIC_PRIORITYGROUP_4  |                0-15           |            0           | 4 bits for pre-emption priority
                           |                               |                        | 0 bit for subpriority
    =================================================================================================================

  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX
  * @brief CORTEX HAL module driver
  * @{
  */

#ifdef HAL_CORTEX_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup CORTEX_Private_Functions CORTEX Private Functions
  * @{
  */
static void MPU_ConfigRegion(MPU_Type *MPUx, const MPU_Region_InitTypeDef *pMPU_RegionInit);
static void MPU_ConfigMemoryAttributes(MPU_Type *MPUx, const MPU_Attributes_InitTypeDef *pMPU_AttributesInit);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup CORTEX_Exported_Functions
  * @{
  */


/** @addtogroup CORTEX_Exported_Functions_Group1
  *  @brief    Initialization and Configuration functions
  *
@verbatim
  ==============================================================================
              ##### Initialization and Configuration functions #####
  ==============================================================================
    [..]
      This section provides the CORTEX HAL driver functions allowing to configure Interrupts
      SysTick functionalities

@endverbatim
  * @{
  */


/**
  * @brief  Set the priority grouping field (pre-emption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0  0 bit  for pre-emption priority,
  *                                    4 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1  1 bit  for pre-emption priority,
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2  2 bits for pre-emption priority,
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3  3 bits for pre-emption priority,
  *                                    1 bit  for subpriority
  *         @arg NVIC_PRIORITYGROUP_4  4 bits for pre-emption priority,
  *                                    0 bit  for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ pre-emption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @retval None
  */
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));

  /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
  NVIC_SetPriorityGrouping(PriorityGroup);
}

/**
  * @brief  Set the priority of an interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @param  PreemptPriority The pre-emption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority
  * @param  SubPriority the subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority.
  * @retval None
  */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t prioritygroup;

  /* Check the parameters */
  assert_param(IS_NVIC_PRIO_INTERRUPT(IRQn));
  prioritygroup = NVIC_GetPriorityGrouping();
  assert_param(IS_NVIC_SUB_PRIORITY(SubPriority, prioritygroup));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority, prioritygroup));

  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

/**
  * @brief  Enable a device specific interrupt in the NVIC interrupt controller.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @retval None
  */
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Enable interrupt */
  NVIC_EnableIRQ(IRQn);
}

/**
  * @brief  Disable a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @retval None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Disable interrupt */
  NVIC_DisableIRQ(IRQn);
}

/**
  * @brief  Initiate a system reset request to reset the MCU.
  * @retval None
  */
void HAL_NVIC_SystemReset(void)
{
  /* System Reset */
  NVIC_SystemReset();
}

/**
  * @brief  Initialize the System Timer with interrupt enabled and start the System Tick Timer (SysTick):
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  TicksNumb Specifies the ticks Number of ticks between two interrupts.
  * @retval status:  - 0  Function succeeded.
  *                  - 1  Function failed.
  */
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb)
{
  if ((TicksNumb - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    /* Reload value impossible */
    return (1UL);
  }

  /* Set reload register */
  WRITE_REG(SysTick->LOAD, (uint32_t)(TicksNumb - 1UL));

  /* Load the SysTick Counter Value */
  WRITE_REG(SysTick->VAL, 0UL);

  /* Enable SysTick IRQ and SysTick Timer */
  SET_BIT(SysTick->CTRL, (SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk));

  /* Function successful */
  return (0UL);
}
/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group2
  *  @brief   Cortex control functions
  *
@verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
    [..]
      This subsection provides a set of functions allowing to control the CORTEX
      (NVIC, SYSTICK, MPU) functionalities.


@endverbatim
  * @{
  */

/**
  * @brief  Get the priority grouping field from the NVIC Interrupt Controller.
  * @retval Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
  */
uint32_t HAL_NVIC_GetPriorityGrouping(void)
{
  /* Get the PRIGROUP[10:8] field value */
  return NVIC_GetPriorityGrouping();
}

/**
  * @brief  Get the priority of an interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @param  PriorityGroup the priority grouping bits length.
  *         This parameter can be one of the following values:
  *           @arg NVIC_PRIORITYGROUP_0  0 bit for pre-emption priority,
  *                                      4 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_1  1 bit for pre-emption priority,
  *                                      3 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_2  2 bits for pre-emption priority,
  *                                      2 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_3  3 bits for pre-emption priority,
  *                                      1 bit for subpriority
  *           @arg NVIC_PRIORITYGROUP_4  4 bits for pre-emption priority,
  *                                      0 bit for subpriority
  * @param  pPreemptPriority Pointer on the Preemptive priority value (starting from 0).
  * @param  pSubPriority Pointer on the Subpriority value (starting from 0).
  * @retval None
  */
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIO_INTERRUPT(IRQn));
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));

  /* Get priority for Cortex-M system or device specific interrupts */
  NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, pPreemptPriority, pSubPriority);
}

/**
  * @brief  Set Pending bit of an external interrupt.
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @retval None
  */
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Set interrupt pending */
  NVIC_SetPendingIRQ(IRQn);
}

/**
  * @brief  Get Pending Interrupt (read the pending register in the NVIC
  *         and return the pending bit for the specified interrupt).
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @retval status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Return 1 if pending else 0 */
  return NVIC_GetPendingIRQ(IRQn);
}

/**
  * @brief  Clear the pending bit of an external interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @retval None
  */
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Clear pending interrupt */
  NVIC_ClearPendingIRQ(IRQn);
}

/**
  * @brief  Get active interrupt (read the active register in NVIC and return the active bit).
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer
  *         to the appropriate CMSIS device file (stm32u3xxxx.h))
  * @retval status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn)
{
  /* Return 1 if active else 0 */
  return NVIC_GetActive(IRQn);
}

/**
  * @brief  Configure the SysTick clock source.
  * @param  CLKSource specifies the SysTick clock source.
  *         This parameter can be one of the following values:
  *             @arg SYSTICK_CLKSOURCE_LSI  LSI clock selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_LSE  LSE clock selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK AHB clock selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK_DIV8 AHB clock divided by 8 selected as SysTick clock source.
  * @retval None
  */
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE(CLKSource));
  switch (CLKSource)
  {
    /* Select HCLK as Systick clock source */
    case SYSTICK_CLKSOURCE_HCLK:
      SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
      break;
    /* Select HCLK_DIV8 as Systick clock source */
    case SYSTICK_CLKSOURCE_HCLK_DIV8:
      CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
      MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL, (0x00000000U));
      break;
    /* Select LSI as Systick clock source */
    case SYSTICK_CLKSOURCE_LSI:
      CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
      MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL, RCC_CCIPR1_SYSTICKSEL_0);
      break;
    /* Select LSE as Systick clock source */
    case SYSTICK_CLKSOURCE_LSE:
      CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
      MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL, RCC_CCIPR1_SYSTICKSEL_1);
      break;
    default:
      /* Nothing to do */
      break;
  }
}

/**
  * @brief  Get the SysTick clock source configuration.
  * @retval  SysTick clock source that can be one of the following values:
  *             @arg SYSTICK_CLKSOURCE_LSI: LSI clock selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_LSE: LSE clock selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
  */
uint32_t HAL_SYSTICK_GetCLKSourceConfig(void)
{
  uint32_t systick_source;

  /* Read SysTick->CTRL register for internal or external clock source */
  if (READ_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk) != 0U)
  {
    /* Internal clock source */
    systick_source = SYSTICK_CLKSOURCE_HCLK;
  }
  else
  {
    /* External clock source, check the selected one in RCC */
    switch (__HAL_RCC_GET_SYSTICK_SOURCE())
    {
      case RCC_SYSTICKCLKSOURCE_LSI:
        systick_source = SYSTICK_CLKSOURCE_LSI;
        break;

      case RCC_SYSTICKCLKSOURCE_LSE:
        systick_source = SYSTICK_CLKSOURCE_LSE;
        break;

      default: /* RCC_SYSTICKCLKSOURCE_HCLK_DIV8 */
        systick_source = SYSTICK_CLKSOURCE_HCLK_DIV8;
        break;
    }
  }
  return systick_source;
}

/**
  * @brief  Handle SYSTICK interrupt request.
  * @retval None
  */
void HAL_SYSTICK_IRQHandler(void)
{
  HAL_SYSTICK_Callback();
}

/**
  * @brief  SYSTICK callback.
  * @retval None
  */
__weak void HAL_SYSTICK_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */
}

/**
  * @brief  Clear pending event(s).
  * @retval None
  */
void HAL_CORTEX_ClearEvent(void)
{
  __SEV();
  __WFE();
}

/**
  * @brief  Enable the MPU.
  * @param  MPU_Control Specifies the control mode of the MPU during hard fault,
  *                     NMI, FAULTMASK and privileged access to the default memory
  *         This parameter can be one of the following values:
  *            @arg MPU_HFNMI_PRIVDEF_NONE
  *            @arg MPU_HARDFAULT_NMI
  *            @arg MPU_PRIVILEGED_DEFAULT
  *            @arg MPU_HFNMI_PRIVDEF
  * @retval None
  */
void HAL_MPU_Enable(uint32_t MPU_Control)
{
  /* Force any outstanding transfers to complete before enabling MPU */
  __DMB();

  /* Enable the MPU */
  MPU->CTRL = (MPU_Control | MPU_CTRL_ENABLE_Msk);

  /* Enable fault exceptions */
  SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

  /* Ensure MPU setting take effects */
  __DSB();
  __ISB();
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Enable the non-secure MPU.
  * @param  MPU_Control: Specifies the control mode of the MPU during hard fault,
  *                      NMI, FAULTMASK and privileged access to the default memory
  *          This parameter can be one of the following values:
  *            @arg MPU_HFNMI_PRIVDEF_NONE
  *            @arg MPU_HARDFAULT_NMI
  *            @arg MPU_PRIVILEGED_DEFAULT
  *            @arg MPU_HFNMI_PRIVDEF
  * @retval None
  */
void HAL_MPU_Enable_NS(uint32_t MPU_Control)
{
  __DMB(); /* Data Memory Barrier operation to force any outstanding writes to memory before enabling the MPU */

  /* Enable the MPU */
  MPU_NS->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;

  /* Enable fault exceptions */
  SCB_NS->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

  /* Follow ARM recommendation with */
  /* Data Synchronization and Instruction Synchronization Barriers to ensure MPU configuration */
  __DSB(); /* Ensure that the subsequent instruction is executed only after the write to memory */
  __ISB(); /* Flush and refill pipeline with updated MPU configuration settings */
}
#endif /* defined (CPU_IN_SECURE_STATE) */

/**
  * @brief  Disable the MPU.
  * @retval None
  */
void HAL_MPU_Disable(void)
{
  /* Force any outstanding transfers to complete before disabling MPU */
  __DMB();

  /* Disable fault exceptions */
  SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;

  /* Disable the MPU */
  MPU->CTRL &= ~MPU_CTRL_ENABLE_Msk;

  /* Ensure MPU setting take effects */
  __DSB();
  __ISB();
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Disable the non-secure MPU.
  * @retval None
  */
void HAL_MPU_Disable_NS(void)
{
  /* Force any outstanding transfers to complete before disabling MPU */
  __DMB();

  /* Disable fault exceptions */
  SCB_NS->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;

  /* Disable the MPU */
  MPU_NS->CTRL &= ~MPU_CTRL_ENABLE_Msk;

  /* Ensure MPU setting take effects */
  __DSB();
  __ISB();
}
#endif /* defined (CPU_IN_SECURE_STATE) */

/**
  * @brief  Enable the MPU Region.
  * @retval None
  */
void HAL_MPU_EnableRegion(uint32_t RegionNumber)
{
  /* Check the parameters */
  assert_param(IS_MPU_REGION_NUMBER(RegionNumber));

  /* Set the Region number */
  MPU->RNR = RegionNumber;

  /* Enable the Region */
  SET_BIT(MPU->RLAR, MPU_RLAR_EN_Msk);
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Enable the non-secure MPU Region.
  * @retval None
  */
void HAL_MPU_EnableRegion_NS(uint32_t RegionNumber)
{
  assert_param(IS_MPU_REGION_NUMBER(RegionNumber));

  /* Set the Region number */
  MPU_NS->RNR = RegionNumber;

  /* Enable the Region */
  SET_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk);
}
#endif /* defined (CPU_IN_SECURE_STATE) */

/**
  * @brief  Disable the MPU Region.
  * @retval None
  */
void HAL_MPU_DisableRegion(uint32_t RegionNumber)
{
  /* Check the parameters */
  assert_param(IS_MPU_REGION_NUMBER(RegionNumber));

  /* Set the Region number */
  MPU->RNR = RegionNumber;

  /* Disable the Region */
  CLEAR_BIT(MPU->RLAR, MPU_RLAR_EN_Msk);
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Disable the non-secure MPU Region.
  * @retval None
  */
void HAL_MPU_DisableRegion_NS(uint32_t RegionNumber)
{
  /* Check the parameters */
  assert_param(IS_MPU_REGION_NUMBER(RegionNumber));

  /* Set the Region number */
  MPU_NS->RNR = RegionNumber;

  /* Disable the Region */
  CLEAR_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk);
}
#endif /* defined (CPU_IN_SECURE_STATE) */


/**
  * @brief  Initialize and configure the Region and the memory to be protected.
  * @param  pMPU_RegionInit Pointer to a MPU_Region_InitTypeDef structure that contains
  *                         the initialization and configuration information.
  * @retval None
  * @note   STM32U3xx supports 12 secure and 8 non secure MPU regions.
  */
void HAL_MPU_ConfigRegion(const MPU_Region_InitTypeDef *pMPU_RegionInit)
{
  MPU_ConfigRegion(MPU, pMPU_RegionInit);
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Initialize and configure the Region and the memory to be protected for non-secure MPU.
  * @param  pMPU_RegionInit Pointer to a MPU_Region_InitTypeDef structure that contains
  *                         the initialization and configuration information.
  * @note   STM32U3xx supports 8 non secure MPU regions.
  * @retval None
  */
void HAL_MPU_ConfigRegion_NS(const MPU_Region_InitTypeDef *pMPU_RegionInit)
{
  MPU_ConfigRegion(MPU_NS, pMPU_RegionInit);
}
#endif /* defined (CPU_IN_SECURE_STATE) */

/**
  * @brief  Initialize and configure the memory attributes.
  * @param  pMPU_AttributesInit Pointer to a MPU_Attributes_InitTypeDef structure that contains
  *                             the initialization and configuration information.
  * @retval None
  */
void HAL_MPU_ConfigMemoryAttributes(const MPU_Attributes_InitTypeDef *pMPU_AttributesInit)
{
  MPU_ConfigMemoryAttributes(MPU, pMPU_AttributesInit);
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Initialize and configure the memory attributes for non-secure MPU.
  * @param  pMPU_AttributesInit Pointer to a MPU_Attributes_InitTypeDef structure that contains
  *                             the initialization and configuration information.
  * @retval None
  */
void HAL_MPU_ConfigMemoryAttributes_NS(const MPU_Attributes_InitTypeDef *pMPU_AttributesInit)
{
  MPU_ConfigMemoryAttributes(MPU_NS, pMPU_AttributesInit);
}
#endif /* defined (CPU_IN_SECURE_STATE) */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup CORTEX_Private_Functions
  * @{
  */
static void MPU_ConfigRegion(MPU_Type *MPUx, const MPU_Region_InitTypeDef *pMPU_RegionInit)
{
  /* Check the parameters */
  assert_param(IS_MPU_REGION_NUMBER(pMPU_RegionInit->Number));
  assert_param(IS_MPU_REGION_ENABLE(pMPU_RegionInit->Enable));

  /* Set the Region number */
  MPUx->RNR = pMPU_RegionInit->Number;

  /* Disable the Region */
  CLEAR_BIT(MPUx->RLAR, MPU_RLAR_EN_Msk);

  /* Check the parameters */
  assert_param(IS_MPU_INSTRUCTION_ACCESS(pMPU_RegionInit->DisableExec));
  assert_param(IS_MPU_REGION_PERMISSION_ATTRIBUTE(pMPU_RegionInit->AccessPermission));
  assert_param(IS_MPU_ACCESS_SHAREABLE(pMPU_RegionInit->IsShareable));
  assert_param(IS_MPU_ATTRIBUTES_NUMBER(pMPU_RegionInit->AttributesIndex));

  MPUx->RBAR = (((uint32_t)pMPU_RegionInit->BaseAddress & 0xFFFFFFE0UL)  |
                ((uint32_t)pMPU_RegionInit->IsShareable      << MPU_RBAR_SH_Pos)  |
                ((uint32_t)pMPU_RegionInit->AccessPermission << MPU_RBAR_AP_Pos)  |
                ((uint32_t)pMPU_RegionInit->DisableExec      << MPU_RBAR_XN_Pos));

  MPUx->RLAR = (((uint32_t)pMPU_RegionInit->LimitAddress & 0xFFFFFFE0UL) |
                ((uint32_t)pMPU_RegionInit->AttributesIndex  << MPU_RLAR_AttrIndx_Pos) |
                ((uint32_t)pMPU_RegionInit->Enable           << MPU_RLAR_EN_Pos));
}

static void MPU_ConfigMemoryAttributes(MPU_Type *MPUx, const MPU_Attributes_InitTypeDef *pMPU_AttributesInit)
{
  __IO uint32_t *p_mair;
  uint32_t      attr_values;
  uint32_t      attr_number;

  /* Check the parameters */
  assert_param(IS_MPU_ATTRIBUTES_NUMBER(pMPU_AttributesInit->Number));
  /* No need to check Attributes value as all 0x0..0xFF possible */

  if (pMPU_AttributesInit->Number < MPU_ATTRIBUTES_NUMBER4)
  {
    /* Program MPU_MAIR0 */
    p_mair = &(MPUx->MAIR0);
    attr_number = pMPU_AttributesInit->Number;
  }
  else
  {
    /* Program MPU_MAIR1 */
    p_mair = &(MPUx->MAIR1);
    attr_number = (uint32_t)pMPU_AttributesInit->Number - 4U;
  }

  attr_values = *(p_mair);
  attr_values &=  ~(0xFFU << (attr_number * 8U));
  *(p_mair) = attr_values | ((uint32_t)pMPU_AttributesInit->Attributes << (attr_number * 8U));
}

/**
  * @}
  */

#endif /* HAL_CORTEX_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
