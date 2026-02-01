/**
  ******************************************************************************
  * @file    stm32wl3x_ll_mrsubg_timer.h
  * @author  GPM WBL Application Team
  * @brief   MRSUBG Timer LL module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MRSUBG_TIMER_H
#define MRSUBG_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

/** @addtogroup MRSUBG_TIMER_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup MRSUBG_TIMER_LL_Exported_Functions MRSUBG Timer Exported Functions
  * @{
  */

/** @defgroup MRSUBG_TIMER_LL_EF_Wakeup_Timer_Configuration MRSUBG Wakeup Timer configuration
  * @{
  */

/**
  * @brief  Enable MRSUBG CPU Wakeup Timer.
  * @rmtoll WAKEUP_CTRL    CPU_WAKEUP_EN   LL_MRSUBG_TIMER_EnableCPUWakeupTimer
  * @param  GLOB_RETAINEDx Global Retained instance
  * @retval None
  */
__STATIC_INLINE void LL_MRSUBG_TIMER_EnableCPUWakeupTimer(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx)
{
  SET_BIT(GLOB_RETAINEDx->WAKEUP_CTRL, MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_CPU_WAKEUP_EN);
}

/**
  * @brief  Disable Radio CPU Wakeup Timer.
  * @rmtoll WAKEUP_CTRL    CPU_WAKEUP_EN   LL_MRSUBG_TIMER_DisableCPUWakeupTimer
  * @param  GLOB_RETAINEDx Global Retained instance
  * @retval None
  */
__STATIC_INLINE void LL_MRSUBG_TIMER_DisableCPUWakeupTimer(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx)
{
  CLEAR_BIT(GLOB_RETAINEDx->WAKEUP_CTRL, MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_CPU_WAKEUP_EN);
}

/**
  * @brief  Indicates if CPU Wakeup Timer is enabled.
  * @rmtoll WAKEUP_CTRL    CPU_WAKEUP_EN   LL_MRSUBG_TIMER_IsEnabledCPUWakeupTimer
  * @param  GLOB_RETAINEDx Global Retained instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_IsEnabledCPUWakeupTimer(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx)
{
  return ((READ_BIT(GLOB_RETAINEDx->WAKEUP_CTRL, MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_CPU_WAKEUP_EN) \
           == (MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_CPU_WAKEUP_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates if RFIP Wakeup Timer is enabled.
  * @rmtoll WAKEUP_CTRL    RFIP_WAKEUP_EN   LL_MRSUBG_TIMER_IsEnabledRFIPWakeupTimer
  * @param  GLOB_RETAINEDx Global Retained instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_IsEnabledRFIPWakeupTimer(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx)
{
  return ((READ_BIT(GLOB_RETAINEDx->WAKEUP_CTRL, MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_RFIP_WAKEUP_EN)  \
           == (MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_RFIP_WAKEUP_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wakeup Offset to let time to power and clocks to settle (Granularity slow clock period).
  * @param  GLOB_RETAINEDx Global Retained instance
  * @param  Time Time in slow clock period
  * @retval None
  */
__STATIC_INLINE void LL_MRSUBG_TIMER_SetWakeupOffset(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx, uint8_t Time)
{
  MODIFY_REG_FIELD(GLOB_RETAINEDx->WAKEUP_CTRL, MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_SOC_WAKEUP_OFFSET, (Time & 0xFF));
}

/**
  * @brief  Get the Wakeup Offset (Granularity slow clock period).
  * @param  GLOB_RETAINEDx Global Retained instance
  * @retval Wakeup Time Offset (Granulary slow clock period, size 8 bit)
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_GetWakeupOffset(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx)
{
  return (uint32_t)(READ_REG(GLOB_RETAINEDx->WAKEUP_CTRL) & 0xFF);
}

/**
  * @brief  Set the CPU Wakeup Time.
  *         The value to program is in interpolated absolute time granularity.
  * @param  GLOB_RETAINEDx Global Retained instance
  * @param  Time in slow clock period
  * @retval None
  */
__STATIC_INLINE void LL_MRSUBG_TIMER_SetCPUWakeupTime(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx, uint32_t Time)
{
  WRITE_REG(GLOB_RETAINEDx->CPU_WAKEUPTIME, Time);
}

/**
  * @brief  Get the CPU Wakeup Time.
  * @param  GLOB_RETAINEDx Global Retained instance
  * @retval CPU Wakeup Time in interpolated absolute time granularity.
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_GetCPUWakeupTime(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx)
{
  return (uint32_t)(READ_REG(GLOB_RETAINEDx->CPU_WAKEUPTIME));
}

/**
  * @brief  Get the RFIP Wakeup Time.
  * @param  GLOB_RETAINEDx Global Retained instance
  * @retval RFIP Wakeup Time in interpolated absolute time granularity.
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_GetRFIPWakeupTime(MR_SUBG_GLOB_RETAINED_TypeDef *GLOB_RETAINEDx)
{
  return (uint32_t)(READ_REG(GLOB_RETAINEDx->RFIP_WAKEUPTIME));
}

/**
  * @brief  Get the Absolute Time of the wakeup timer (Granularity unit is 16 x slow clock period).
  * @param  GLOB_MISCx Global Misc instance
  * @retval Absolute Time of Wakeup Timer
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_GetAbsoluteTime(MR_SUBG_GLOB_MISC_TypeDef *GLOB_MISCx)
{
  return (uint32_t)(READ_REG(GLOB_MISCx->ABSOLUTE_TIME));
}

/**
  * @}
  */

/** @defgroup MRSUBG_TIMER_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear the RFIP Wakeup interrupt flag.
  * @rmtoll WAKEUP_IRQ_STATUS   RFIP_WAKEUP_F   LL_MRSUBG_TIMER_ClearFlag_RFIPWakeup
  * @param  GLOB_MISCx Global Misc instance
  * @retval None
  */
__STATIC_INLINE void LL_MRSUBG_TIMER_ClearFlag_RFIPWakeup(MR_SUBG_GLOB_MISC_TypeDef *GLOB_MISCx)
{
  SET_BIT(GLOB_MISCx->WAKEUP_IRQ_STATUS, MR_SUBG_GLOB_MISC_WAKEUP_IRQ_STATUS_RFIP_WAKEUP_F);
}

/**
  * @brief  Indicate whether the RFIP Wakeup interrupt flag is set
  * @rmtoll WAKEUP_IRQ_STATUS   RFIP_WAKEUP_F   LL_MRSUBG_TIMER_IsActiveFlag_RFIPWakeup
  * @param  GLOB_MISCx Global Misc instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_IsActiveFlag_RFIPWakeup(MR_SUBG_GLOB_MISC_TypeDef *GLOB_MISCx)
{
  return ((READ_BIT(GLOB_MISCx->WAKEUP_IRQ_STATUS, MR_SUBG_GLOB_MISC_WAKEUP_IRQ_STATUS_RFIP_WAKEUP_F) == \
           (MR_SUBG_GLOB_MISC_WAKEUP_IRQ_STATUS_RFIP_WAKEUP_F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the CPU Wakeup interrupt flag.
  * @rmtoll WAKEUP_IRQ_STATUS   CPU_WAKEUP_F   LL_MRSUBG_TIMER_ClearFlag_CPUWakeup
  * @param  GLOB_MISCx GLobal Misc instance
  * @retval None
  */
__STATIC_INLINE void LL_MRSUBG_TIMER_ClearFlag_CPUWakeup(MR_SUBG_GLOB_MISC_TypeDef *GLOB_MISCx)
{
  SET_BIT(GLOB_MISCx->WAKEUP_IRQ_STATUS, MR_SUBG_GLOB_MISC_WAKEUP_IRQ_STATUS_CPU_WAKEUP_F);
}

/**
  * @brief  Indicate whether the CPU Wakeup interrupt flag is set
  * @rmtoll WAKEUP_IRQ_STATUS   CPU_WAKEUP_F   LL_MRSUBG_TIMER_IsActiveFlag_CPUWakeup
  * @param  GLOB_MISCx Global Misc instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_IsActiveFlag_CPUWakeup(MR_SUBG_GLOB_MISC_TypeDef *GLOB_MISCx)
{
  return ((READ_BIT(GLOB_MISCx->WAKEUP_IRQ_STATUS, MR_SUBG_GLOB_MISC_WAKEUP_IRQ_STATUS_CPU_WAKEUP_F) == \
           (MR_SUBG_GLOB_MISC_WAKEUP_IRQ_STATUS_CPU_WAKEUP_F)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup MRSUBG_TIMER_LL_EF_LSI_CALIBRATION Radio Timer LSI calibration APIs
  * @{
  */

/**
  * @brief  Get the SCM (slow clock measurements).
  * @param  GLOB_MISCx Global Misc instance
  * @retval SCM value
  */
__STATIC_INLINE uint32_t LL_MRSUBG_TIMER_GetSCM(MR_SUBG_GLOB_MISC_TypeDef *GLOB_MISCx)
{
  return (uint32_t)(READ_REG(GLOB_MISCx->SCM_COUNTER_VAL)& MR_SUBG_GLOB_MISC_SCM_COUNTER_VAL_SCM_COUNTER_CURRVAL);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* MRSUBG_TIMER_H */
