/**
  ******************************************************************************
  * @file    stm32wl3x_ll_lcsc.h
  * @author  MCD Application Team
  * @brief   Header file of LCSC LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WL3x_LL_LCSC_H
#define STM32WL3x_LL_LCSC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x.h"

/** @addtogroup STM32WL3x_LL_Driver
  * @{
 */

#if defined (LCSC)

/** @defgroup LCSC_LL LCSC
  * @{
 */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @defgroup LCSC_LL_Exported_Constants LCSC Exported Constants
  * @{
 */

/** @defgroup LCSC_LL_CLKWISE_STATE LCSC Clockwise state values
  * @{
 */
#define LL_LCSC_SR_CLKWISE_FSM_Q1  (0U)
#define LL_LCSC_SR_CLKWISE_FSM_Q2  (LCSC_SR_CLKWISE_STATE_0)
#define LL_LCSC_SR_CLKWISE_FSM_Q3  (LCSC_SR_CLKWISE_STATE_1)
#define LL_LCSC_SR_CLKWISE_FSM_Q4  (LCSC_SR_CLKWISE_STATE_1 | LCSC_SR_CLKWISE_STATE_0)
/**
  * @}
 */

/** @defgroup LCSC_LL_ACLKWISE_STATE LCSC Anti clockwise state values
  * @{
 */
#define LL_LCSC_SR_ACLKWISE_FSM_Q1  (0U)
#define LL_LCSC_SR_ACLKWISE_FSM_Q2  (LCSC_SR_ACLKWISE_STATE_0)
#define LL_LCSC_SR_ACLKWISE_FSM_Q3  (LCSC_SR_ACLKWISE_STATE_1)
#define LL_LCSC_SR_ACLKWISE_FSM_Q4  (LCSC_SR_ACLKWISE_STATE_1 | LCSC_SR_ACLKWISE_STATE_0)
/**
  * @}
 */

/** @defgroup LCSC_LL_LAST_DIR LCSC Last direction detected values
  * @{
 */
#define LL_LCSC_SR_LAST_DIR_UNKNOWN           (0U)
#define LL_LCSC_SR_LAST_DIR_CLOCKWISE         (LCSC_SR_LAST_DIR_1)
#define LL_LCSC_SR_LAST_DIR_COUNTER_CLOCKWISE (LCSC_SR_LAST_DIR_1 | LCSC_SR_LAST_DIR_0)
/**
  * @}
 */


/**
  * @}
 */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LCSC_LL_Exported_Macros LCSC Exported Macros
  * @{
 */


/** @defgroup LCSC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Set the measurement duration (also called TMeas) is the duration of an LC measurement sequence.
  * @note   This period is given in number of slow clock cycles.
  * @rmtoll CR0          TMEAS       LL_LCSC_SetMeasurementTime
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 16383 (form 0x0 to 0x3fff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetMeasurementTime(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR0, LCSC_CR0_TMEAS, value);
}

/**
  * @brief  Get the measurement duration (also called TMeas) is the duration of an LC measurement sequence
  *         (including LCA, LCB and LCT if necessary, and also the time left before the next power-up of analog blocks
  *         (DAC, COMP, VCMBUFF)).
  * @note   This period is given in number of slow clock cycles.
  * @rmtoll CR0          TMEAS       LL_LCSC_GetMeasurementTime
  * @param  LCSCx LCSC Instance
  * @retval the measurement duration TMeas
  */
__STATIC_INLINE uint32_t LL_LCSC_GetMeasurementTime(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR0, LCSC_CR0_TMEAS));
}

/**
  * @brief  Set the capture duration time.
  * @note   Also called Tcapture, it is the duration of one LC measurement, starting from the excitation pulse
  *         on the LC line and ending once the TCAP number of slow clock cycles has been reached. This duration
  *         is given in number of slow clock cycles.
  * @rmtoll CR0          TCAP       LL_LCSC_SetCaptureTime
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 63 (form 0x0 to 0x3f)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetCaptureTime(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR0, LCSC_CR0_TCAP, value << LCSC_CR0_TCAP_Pos);
}

/**
  * @brief  Get the capture duration (also called Tcapture).
  * @note   It is the duration of one LC measurement, starting from the excitation pulse on the LC line and ending
  *         once the TCAP number of slow clock cycles has been reached.
  *         This duration is given in number of slow clock cycles.
  * @rmtoll CR0          TCAP       LL_LCSC_GetCaptureTime
  * @param  LCSCx LCSC Instance
  * @retval the capture duration Tcapture
  */
__STATIC_INLINE uint32_t LL_LCSC_GetCaptureTime(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR0, LCSC_CR0_TCAP) >> LCSC_CR0_TCAP_Pos);
}

/**
  * @brief  Set the inter-capture duration (also called TinterCapture).
  * @note   It is the duration between the end of a first TCAP and the following TCAP and is equal
  *         to TICAP + 2 slow clock cycles.
  *         This duration is given in number of slow clock cycles.
  * @rmtoll CR0          TICAP       LL_LCSC_SetInterCaptureTime
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 7 (form 0x0 to 0x7)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetInterCaptureTime(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR0, LCSC_CR0_TICAP, value << LCSC_CR0_TICAP_Pos);
}

/**
  * @brief  Get the inter-capture duration (also called TinterCapture).
  * @note   It is the duration between the end of a firstTCAP and the following TCAP
  *         and is equal to TICAP + 2 slow clock cycles. This duration is given in number of slow clock cycles.
  * @rmtoll CR0          TICAP       LL_LCSC_GetInterCaptureTime
  * @param  LCSCx LCSC Instance
  * @retval the inter-capture duration TinterCapture
  */
__STATIC_INLINE uint32_t LL_LCSC_GetInterCaptureTime(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR0, LCSC_CR0_TICAP) >> LCSC_CR0_TICAP_Pos);
}

/**
  * @brief  Set the count threshold used to define if the LCA and LCB is near of not of a metallic surface.
  * @rmtoll CR1          LCAB_DAMP_THRES       LL_LCSC_SetDampingThreshold_LCAB
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetDampingThreshold_LCAB(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR1, LCSC_CR1_LCAB_DAMP_THRES, value << LCSC_CR1_LCAB_DAMP_THRES_Pos);
}

/**
  * @brief  Get the count threshold used to define if the LCA and LCB is near of not of a metallic surface.
  * @rmtoll CR1          LCAB_DAMP_THRES       LL_LCSC_GetDampingThreshold_LCAB
  * @param  LCSCx LCSC Instance
  * @retval the damping threshold for LCA and LCB
  */
__STATIC_INLINE uint32_t LL_LCSC_GetDampingThreshold_LCAB(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR1, LCSC_CR1_LCAB_DAMP_THRES) >> LCSC_CR1_LCAB_DAMP_THRES_Pos);
}

/**
  * @brief  Set the duration of TrecoveryVCM (in number of slow clock cycles)
  *         between the enable of the VCMBUFF and the establishment of the Voltage to the value VDD33/2.
  * @note   This time is to be considered between each sequence of LC measurement, called TSCAN in the registers.
  *         (sequence of LC measurement = LCA, LCB and sometimes LCT). TREC_VCM must not be set to values lower of 0x02
  * @rmtoll CR1          TREC_VCM       LL_LCSC_Set_VCMBuff_RecoveryTime
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 511 (form 0x0 to 0x1ff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_Set_VCMBuff_RecoveryTime(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR1, LCSC_CR1_TREC_VCM, value << LCSC_CR1_TREC_VCM_Pos);
}

/**
  * @brief  Get the duration of TrecoveryVCM (in number of slow clock cycles)
  *         between the enable of the VCMBUFF and the establishment of the Voltage to the value VDD33/2.
  * @note   This time is to be considered between each sequence of LC measurement, called TSCAN in the registers.
  *         (sequence of LC measurement = LCA, LCB and sometimes LCT). TREC_VCM must not be set to values lower of 0x02
  * @rmtoll CR1          TREC_VCM       LL_LCSC_Get_VCMBuff_RecoveryTime
  * @param  LCSCx LCSC Instance
  * @retval the VCMBUFF Recovery Time
  */
__STATIC_INLINE uint32_t LL_LCSC_Get_VCMBuff_RecoveryTime(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR1, LCSC_CR1_TREC_VCM) >> LCSC_CR1_TREC_VCM_Pos);
}

/**
  * @brief  Set the duration of TStartVCM (in number of slow clock cycles)
  *         between the enable of the VCMBUFF and the establishment of the Voltage to the value VDD33/2.
  * @note   This time is only to be considered for the first LC measurement after an enabling of the LCSC feature
  *         thanks to the LCSC_EN bit. TSART_VCM must not be set to values lower of 0x02
  * @rmtoll CR1          TSTART_VCM       LL_LCSC_Set_VCMBuff_StartingTime
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 2047 (form 0x0 to 0x7ff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_Set_VCMBuff_StartingTime(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR1, LCSC_CR1_TSTART_VCM, value << LCSC_CR1_TSTART_VCM_Pos);
}

/**
  * @brief  Get the duration of TStartVCM (in number of slow clock cycles)
  *         between the enable of the VCMBUFF and the establishment of the Voltage to the value VDD33/2.
  * @note   This time is only to be considered for the first LC measurement after an enabling of the LCSC
  *         feature thanks to the LCSC_EN bit. TSART_VCM must not be set to values lower of 0x02
  * @rmtoll CR1          TSTART_VCM       LL_LCSC_Get_VCMBuff_StartingTime
  * @param  LCSCx LCSC Instance
  * @retval the VCMBUFF Starting Time
  */
__STATIC_INLINE uint32_t LL_LCSC_Get_VCMBuff_StartingTime(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR1, LCSC_CR1_TSTART_VCM) >> LCSC_CR1_TSTART_VCM_Pos);
}

/**
  * @brief  Set the tamper detection prescaler comparing to the measurement period
  * @note   0x0: the tamper detection and the LCT measurement are never done
  *         others: the LCT measurement is done once every TAMP_PSC sequences of measurements.
  * @rmtoll CR2          TAMP_PSC       LL_LCSC_SetMeasurementInterval_LCT
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetMeasurementInterval_LCT(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR2, LCSC_CR2_TAMP_PSC, value << LCSC_CR2_TAMP_PSC_Pos);
}

/**
  * @brief  Get the tamper detection prescaler comparing to the measurement period
  * @note   0x00: the tamper detection and the LCT measurement are never done
  *         others: the LCT measurement is done once every TAMP_PSC sequences of measurements.
  * @rmtoll CR2          TAMP_PSC       LL_LCSC_GetMeasurementInterval_LCT
  * @param  LCSCx LCSC Instance
  * @retval the tamper detection prescaler
  */
__STATIC_INLINE uint32_t LL_LCSC_GetMeasurementInterval_LCT(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR2, LCSC_CR2_TAMP_PSC) >> LCSC_CR2_TAMP_PSC_Pos);
}

/**
  * @brief  Set the count threshold used to define if the LCT is near of not of a metallic surface.
  * @rmtoll CR2          LCT_DAMP_THRES       LL_LCSC_SetDampingThreshold_LCT
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetDampingThreshold_LCT(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CR2, LCSC_CR2_LCT_DAMP_THRES, value << LCSC_CR2_LCT_DAMP_THRES_Pos);
}

/**
  * @brief  Get the count threshold used to define if the LCT is near of not of a metallic surface.
  * @rmtoll CR2          LCT_DAMP_THRES       LL_LCSC_GetDampingThreshold_LCT
  * @param  LCSCx LCSC Instance
  * @retval the damping threshold for LCT
  */
__STATIC_INLINE uint32_t LL_LCSC_GetDampingThreshold_LCT(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CR2, LCSC_CR2_LCT_DAMP_THRES) >> LCSC_CR2_LCT_DAMP_THRES_Pos);
}

/**
  * @brief  Set the Pulse width programming for generated pulse.
  * @rmtoll PULSE_CR          LCAB_PULSE_WIDTH       LL_LCSC_SetLowPulseWidth_LCAB
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 15 (form 0x0 to 0xf)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetLowPulseWidth_LCAB(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->PULSE_CR, LCSC_PULSE_CR_LCAB_PULSE_WIDTH, value << LCSC_PULSE_CR_LCAB_PULSE_WIDTH_Pos);
}

/**
  * @brief  Get the Pulse width programming for generated pulse.
  * @rmtoll PULSE_CR          LCAB_PULSE_WIDTH       LL_LCSC_GetLowPulseWidth_LCAB
  * @param  LCSCx LCSC Instance
  * @retval the low pulse width for LCA and LCB
  */
__STATIC_INLINE uint32_t LL_LCSC_GetLowPulseWidth_LCAB(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->PULSE_CR, LCSC_PULSE_CR_LCAB_PULSE_WIDTH) >> LCSC_PULSE_CR_LCAB_PULSE_WIDTH_Pos);
}

/**
  * @brief  Set the Pulse width programming for generated pulse.
  * @rmtoll PULSE_CR          LCT_PULSE_WIDTH       LL_LCSC_SetLowPulseWidth_LCT
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 15 (form 0x0 to 0xf)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetLowPulseWidth_LCT(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->PULSE_CR, LCSC_PULSE_CR_LCT_PULSE_WIDTH, value << LCSC_PULSE_CR_LCT_PULSE_WIDTH_Pos);
}

/**
  * @brief  Get the Pulse width programming for generated pulse.
  * @rmtoll PULSE_CR          LCT_PULSE_WIDTH       LL_LCSC_GetLowPulseWidth_LCT
  * @param  LCSCx LCSC Instance
  * @retval the low pulse width for LCT
  */
__STATIC_INLINE uint32_t LL_LCSC_GetLowPulseWidth_LCT(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->PULSE_CR, LCSC_PULSE_CR_LCT_PULSE_WIDTH) >> LCSC_PULSE_CR_LCT_PULSE_WIDTH_Pos);
}

/**
  * @brief  LCSC Enable the IRQ and Wakeup event generation once the CLKWISE has reached the CLKWISE_THRES value.
  * @rmtoll ENR          CLKWISE_IE            LL_LCSC_EnableClockWiseInterruptAndWakeup
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_EnableIT_ClockWise(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ENR, LCSC_ENR_CLKWISE_IE);
}

/**
  * @brief  LCSC Disable the IRQ and Wakeup event generation once
  *         the CLKWISE has reached the CLKWISE_THRES value.
  * @rmtoll ENR          CLKWISE_IE            LL_LCSC_DisableIT_ClockWise
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_DisableIT_ClockWise(LCSC_TypeDef *LCSCx)
{
  CLEAR_BIT(LCSCx->ENR, LCSC_ENR_CLKWISE_IE);
}

/**
  * @brief  Indicate if the clock wise interrupt (CLKWISE) is enabled.
  *         Enable the IRQ and Wakeup event generation once the CLKWISE has reached the CLKWISE_THRES value.
  * @rmtoll ENR          CLKWISE_IE            LL_LCSC_IsEnabledIT_ClockWise
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsEnabledIT_ClockWise(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ENR, LCSC_ENR_CLKWISE_IE) == (LCSC_ENR_CLKWISE_IE)) ? 1U : 0U);
}

/**
  * @brief  LCSC Enable the IRQ and Wakeup event generation once
  *         the anti clock wise value is equal or greater than the ACLKWISE_THRES bits.
  * @rmtoll ENR          ACLKWISE_IE            LL_LCSC_EnableIT_AntiClockWise
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_EnableIT_AntiClockWise(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ENR, LCSC_ENR_ACLKWISE_IE);
}

/**
  * @brief  LCSC Disable the IRQ and Wakeup event generation once
  *         the anti clock wise value is equal or greater than the ACLKWISE_THRES bits.
  * @rmtoll ENR          ACLKWISE_IE            LL_LCSC_DisableIT_AntiClockWise
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_DisableIT_AntiClockWise(LCSC_TypeDef *LCSCx)
{
  CLEAR_BIT(LCSCx->ENR, LCSC_ENR_ACLKWISE_IE);
}

/**
  * @brief  Indicate if the anti clock wise interrupt (ACLKWISE) is enabled.
  * @rmtoll ENR          ACLKWISE_IE            LL_LCSC_IsEnabledIT_AntiClockWise
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsEnabledIT_AntiClockWise(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ENR, LCSC_ENR_ACLKWISE_IE) == (LCSC_ENR_ACLKWISE_IE)) ? 1U : 0U);
}

/**
  * @brief  LCSC Enable the IRQ and the Wakeup event generation on a tamper detection.
  * @rmtoll ENR          TAMP_IE            LL_LCSC_EnableIT_LCT
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_EnableIT_LCT(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ENR, LCSC_ENR_TAMP_IE);
}

/**
  * @brief  LCSC Disable the IRQ and the Wakeup event generation on a tamper detection.
  * @rmtoll ENR          TAMP_IE            LL_LCSC_DisableIT_LCT
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_DisableIT_LCT(LCSC_TypeDef *LCSCx)
{
  CLEAR_BIT(LCSCx->ENR, LCSC_ENR_TAMP_IE);
}

/**
  * @brief  Indicate if the tamper interrupt (TAMP_IE) is enabled.
  * @rmtoll ENR          TAMP_IE            LL_LCSC_IsEnabledIT_LCT
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsEnabledIT_LCT(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ENR, LCSC_ENR_TAMP_IE) == (LCSC_ENR_TAMP_IE)) ? 1U : 0U);
}

/**
  * @brief  LCSC Enable the IRQ and the Wakeup event generation on a LCAB count out of bounds
  * @rmtoll ENR          CNT_OFB_WKP_IE            LL_LCSC_EnableIT_CounterOutOfBoundWakeup
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_EnableIT_CounterOutOfBoundWakeup(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ENR, LCSC_ENR_CNT_OFB_WKP_IE);
}

/**
  * @brief  LCSC Disable the IRQ and the Wakeup event generation on a LCAB count out of bounds
  * @rmtoll ENR          CNT_OFB_WKP_IE            LL_LCSC_DisableIT_CounterOutOfBoundWakeup
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_DisableIT_CounterOutOfBoundWakeup(LCSC_TypeDef *LCSCx)
{
  CLEAR_BIT(LCSCx->ENR, LCSC_ENR_CNT_OFB_WKP_IE);
}

/**
  * @brief  Indicate if the LCAB count out of bounds interrupt (CNT_OFB_WKP_IE) is enabled.
  * @rmtoll ENR          CNT_OFB_WKP_IE            LL_LCSC_IsEnabledIT_CounterOutOfBoundWakeup
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsEnabledIT_CounterOutOfBoundWakeup(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ENR, LCSC_ENR_CNT_OFB_WKP_IE) == (LCSC_ENR_CNT_OFB_WKP_IE)) ? 1U : 0U);
}

/**
  * @brief  LCSC Enable (start) or Disable (stop) the LCSC Measurement.
  * @rmtoll ENR          LCSC_EN            LL_LCSC_Enable
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_Enable(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ENR, LCSC_ENR_LCSC_EN);
}

/**
  * @brief  LCSC Disable (start) or Disable (stop) the LCSC Measurement.
  * @rmtoll ENR          LCSC_EN            LL_LCSC_Disable
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_Disable(LCSC_TypeDef *LCSCx)
{
  CLEAR_BIT(LCSCx->ENR, LCSC_ENR_LCSC_EN);
}

/**
  * @brief  Indicate if LCSC_EN is enabled. Enable (start) or Disable (stop) the LCSC Measurement.
  * @rmtoll ENR          LCSC_EN            LL_LCSC_IsEnabled
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsEnabled(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ENR, LCSC_ENR_LCSC_EN) == (LCSC_ENR_LCSC_EN)) ? 1U : 0U);
}

/**
  * @brief  Get the Number of Clock Wise revolutions
  * @rmtoll WHEEL_SR          CLKWISE       LL_LCSC_GetClockWise
  * @param  LCSCx LCSC Instance
  * @retval the Number of Clock Wise revolutions
  */
__STATIC_INLINE uint32_t LL_LCSC_GetClockWise(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->WHEEL_SR, LCSC_WHEEL_SR_CLKWISE) >> LCSC_WHEEL_SR_CLKWISE_Pos);
}

/**
  * @brief  Get the Number of Anti Clock Wise revolutions
  * @rmtoll WHEEL_SR          ACLKWISE       LL_LCSC_GetAntiClockWise
  * @param  LCSCx LCSC Instance
  * @retval the Number of Anti Clock Wise revolutions
  */
__STATIC_INLINE uint32_t LL_LCSC_GetAntiClockWise(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->WHEEL_SR, LCSC_WHEEL_SR_ACLKWISE) >> LCSC_WHEEL_SR_ACLKWISE_Pos);
}

/**
  * @brief  Set the Number of Clock Wise revolutions target
  * @rmtoll CONFR          CLKWISE_THRES       LL_LCSC_SetClockWiseTarget
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 65535 (form 0x0 to 0xffff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetClockWiseTarget(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CONFR, LCSC_CONFR_CLKWISE_THRES, value << LCSC_CONFR_CLKWISE_THRES_Pos);
}

/**
  * @brief  Get the Number of Clock Wise revolutions target
  * @rmtoll CONFR          CLKWISE_THRES       LL_LCSC_GetClockWiseTarget
  * @param  LCSCx LCSC Instance
  * @retval the Number of Clock Wise revolutions target
  */
__STATIC_INLINE uint32_t LL_LCSC_GetClockWiseTarget(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CONFR, LCSC_CONFR_CLKWISE_THRES) >> LCSC_CONFR_CLKWISE_THRES_Pos);
}

/**
  * @brief  Set the Number of Anti Clock Wise revolutions target
  * @rmtoll CONFR          ACLKWISE_THRES       LL_LCSC_SetAntiClockWiseTarget
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 65535 (form 0x0 to 0xffff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetAntiClockWiseTarget(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->CONFR, LCSC_CONFR_ACLKWISE_THRES, value << LCSC_CONFR_ACLKWISE_THRES_Pos);
}

/**
  * @brief  Get the Number of Anti Clock Wise revolutions target
  * @rmtoll CONFR          ACLKWISE_THRES       LL_LCSC_GetAntiClockWiseTarget
  * @param  LCSCx LCSC Instance
  * @retval the Number of Anti Clock Wise revolutions target
  */
__STATIC_INLINE uint32_t LL_LCSC_GetAntiClockWiseTarget(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->CONFR, LCSC_CONFR_ACLKWISE_THRES) >> LCSC_CONFR_ACLKWISE_THRES_Pos);
}

/**
  * @brief  Get the LCA Comparator last damping count
  * @rmtoll COMP_CTN          CMP_LCA_CNT       LL_LCSC_GetComparatorLastDampingCount_LCA
  * @param  LCSCx LCSC Instance
  * @retval the LCA Comparator last damping count
  */
__STATIC_INLINE uint32_t LL_LCSC_GetComparatorLastDampingCount_LCA(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->COMP_CTN, LCSC_COMP_CTN_CMP_LCA_CNT) >> LCSC_COMP_CTN_CMP_LCA_CNT_Pos);
}

/**
  * @brief  Get the LCB Comparator last damping count
  * @rmtoll COMP_CTN          CMP_LCB_CNT       LL_LCSC_GetComparatorLastDampingCount_LCB
  * @param  LCSCx LCSC Instance
  * @retval the LCB Comparator last damping count
  */
__STATIC_INLINE uint32_t LL_LCSC_GetComparatorLastDampingCount_LCB(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->COMP_CTN, LCSC_COMP_CTN_CMP_LCB_CNT) >> LCSC_COMP_CTN_CMP_LCB_CNT_Pos);
}

/**
  * @brief  Get the LCT Comparator last damping count
  * @rmtoll COMP_CTN          CMP_LCT_CNT       LL_LCSC_GetComparatorLastDampingCount_LCT
  * @param  LCSCx LCSC Instance
  * @retval the LCT Comparator last damping count
  */
__STATIC_INLINE uint32_t LL_LCSC_GetComparatorLastDampingCount_LCT(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->COMP_CTN, LCSC_COMP_CTN_CMP_LCT_CNT) >> LCSC_COMP_CTN_CMP_LCT_CNT_Pos);
}

/**
  * @brief  Get the current state of the LCSC clockwise FSM
  * @rmtoll SR          CLKWISE_STATE       LL_LCSC_GetClockWise_State
  * @param  LCSCx LCSC Instance
  * @retval can be one of the following values
  * @arg LL_LCSC_SR_CLKWISE_FSM_Q1
  * @arg LL_LCSC_SR_CLKWISE_FSM_Q2
  * @arg LL_LCSC_SR_CLKWISE_FSM_Q3
  * @arg LL_LCSC_SR_CLKWISE_FSM_Q4
  */
__STATIC_INLINE uint32_t LL_LCSC_GetClockWise_State(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->SR, LCSC_SR_CLKWISE_STATE));
}

/**
  * @brief  Get the current state of the LCSC anti clockwise FSM
  * @rmtoll SR          ACLKWISE_STATE       LL_LCSC_GetAntiClockWise_State
  * @param  LCSCx LCSC Instance
  * @retval can be one of the following values
  * @arg LL_LCSC_SR_ACLKWISE_FSM_Q1
  * @arg LL_LCSC_SR_ACLKWISE_FSM_Q2
  * @arg LL_LCSC_SR_ACLKWISE_FSM_Q3
  * @arg LL_LCSC_SR_ACLKWISE_FSM_Q4
  */
__STATIC_INLINE uint32_t LL_LCSC_GetAntiClockWise_State(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->SR, LCSC_SR_ACLKWISE_STATE) >> LCSC_SR_ACLKWISE_STATE_Pos);
}

/**
  * @brief  Get the last direction detected
  * @rmtoll SR          LAST_DIR       LL_LCSC_GetLastDirection
  * @param  LCSCx LCSC Instance
  * @retval can be one of the following values
  * @arg LL_LCSC_SR_LAST_DIR_UNKNOWN
  * @arg LL_LCSC_SR_LAST_DIR_CLOCKWISE
  * @arg LL_LCSC_SR_LAST_DIR_COUNTER_CLOCKWISE
  */
__STATIC_INLINE uint32_t LL_LCSC_GetLastDirection(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->SR, LCSC_SR_LAST_DIR) >> LCSC_SR_LAST_DIR_Pos);
}

/**
  * @brief  Get the Minimum of CMP_LCA_CNT, CMP_LCB_CNT reached during the measurement
  * @rmtoll STAT          MIN_LCAB_CNT       LL_LCSC_GetMin_Counter
  * @param  LCSCx LCSC Instance
  * @retval the Minimum of CMP_LCA_CNT
  */
__STATIC_INLINE uint32_t LL_LCSC_GetMin_Counter(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->STAT, LCSC_STAT_MIN_LCAB_CNT) >> LCSC_STAT_MIN_LCAB_CNT_Pos);
}

/**
  * @brief  Get the Maximum of CMP_LCA_CNT, CMP_LCB_CNT reached during the measurement
  * @rmtoll STAT          MAX_LCAB_CNT       LL_LCSC_GetMax_Counter
  * @param  LCSCx LCSC Instance
  * @retval the Maximum of CMP_LCA_CNT
  */
__STATIC_INLINE uint32_t LL_LCSC_GetMax_Counter(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->STAT, LCSC_STAT_MAX_LCAB_CNT) >> LCSC_STAT_MAX_LCAB_CNT_Pos);
}

/**
  * @brief  Set the Minimum bound of CMP_LCA_COUNT, CMP_LCB_COUNT used when monitoring the MIN_LCAB_CNT
  * @rmtoll STAT          MIN_LCAB_CNT_BOUND       LL_LCSC_SetMin_CounterOutOfBound
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetMin_CounterOutOfBound(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->STAT, LCSC_STAT_MIN_LCAB_CNT_BOUND, value << LCSC_STAT_MIN_LCAB_CNT_BOUND_Pos);
}

/**
  * @brief  Get the Minimum bound of CMP_LCA_COUNT, CMP_LCB_COUNT used when monitoring the MIN_LCAB_CNT
  * @rmtoll STAT          MIN_LCAB_CNT_BOUND       LL_LCSC_GetMin_CounterOutOfBound
  * @param  LCSCx LCSC Instance
  * @retval the Minimum bound of CMP_LCA_COUNT
  */
__STATIC_INLINE uint32_t LL_LCSC_GetMin_CounterOutOfBound(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->STAT, LCSC_STAT_MIN_LCAB_CNT_BOUND) >> LCSC_STAT_MIN_LCAB_CNT_BOUND_Pos);
}

/**
  * @brief  Set the Maximum bound of CMP_LCA_COUNT, CMP_LCB_COUNT used when monitoring the MAX_LCAB_CNT
  * @rmtoll STAT          MAX_LCAB_CNT_BOUND       LL_LCSC_SetMax_CounterOutOfBound
  * @param  LCSCx LCSC Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_SetMax_CounterOutOfBound(LCSC_TypeDef *LCSCx, uint32_t value)
{
  MODIFY_REG(LCSCx->STAT, LCSC_STAT_MAX_LCAB_CNT_BOUND, value << LCSC_STAT_MAX_LCAB_CNT_BOUND_Pos);
}

/**
  * @brief  Get the Maximum bound of CMP_LCA_COUNT, CMP_LCB_COUNT used when monitoring the MAX_LCAB_CNT
  * @rmtoll STAT          MAX_LCAB_CNT_BOUND       LL_LCSC_GetMax_CounterOutOfBound
  * @param  LCSCx LCSC Instance
  * @retval the Maximum bound of CMP_LCA_COUNT
  */
__STATIC_INLINE uint32_t LL_LCSC_GetMax_CounterOutOfBound(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->STAT, LCSC_STAT_MAX_LCAB_CNT_BOUND) >> LCSC_STAT_MAX_LCAB_CNT_BOUND_Pos);
}

/**
  * @brief  Get the Revision of the RFIP
  * @note   to be used for metal fixes
  * @rmtoll VER          REV       LL_LCSC_GetRevision
  * @param  LCSCx LCSC Instance
  * @retval the Revision of the RFIP
  */
__STATIC_INLINE uint32_t LL_LCSC_GetRevision(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->VER, LCSC_VER_REV) >> LCSC_VER_REV_Pos);
}

/**
  * @brief  Get the Version of the RFIP
  * @note   to be used for cut upgrades
  * @rmtoll VER          VER       LL_LCSC_GetVersion
  * @param  LCSCx LCSC Instance
  * @retval the Version of the RFIP
  */
__STATIC_INLINE uint32_t LL_LCSC_GetVersion(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->VER, LCSC_VER_VER) >> LCSC_VER_VER_Pos);
}

/**
  * @brief  Get the Used for major upgrades
  * @rmtoll VER          PROD       LL_LCSC_GetProduct
  * @param  LCSCx LCSC Instance
  * @retval the Used for major upgrades
  */
__STATIC_INLINE uint32_t LL_LCSC_GetProduct(LCSC_TypeDef *LCSCx)
{
  return (uint32_t)(READ_BIT(LCSCx->VER, LCSC_VER_PROD) >> LCSC_VER_PROD_Pos);
}

/**
  * @brief  Indicate if CLKWISE_F is enabled. Clock Wise Flag
  * @note   0: counter CLKWISE has not reached CLKWISE_THRES
  *         1: counter CLKWISE has reached CLKWISE_THRES
  * @rmtoll ISR          CLKWISE_F            LL_LCSC_IsActiveFlag_CLKWISE
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsActiveFlag_CLKWISE(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ISR, LCSC_ISR_CLKWISE_F) == (LCSC_ISR_CLKWISE_F)) ? 1U : 0U);
}

/**
  * @brief  Clear LCSC. Clock Wise Flag
  * @rmtoll ISR          CLKWISE_F            LL_LCSC_ClearFlag_CLKWISE
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_ClearFlag_CLKWISE(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ISR, LCSC_ISR_CLKWISE_F);
}

/**
  * @brief  Indicate if ACLKWISE_F is enabled. Anti Clock Wise Flag
  * @note   0: counter ACLKWISE has not reached ACLKWISE_THRES
  *         1: counter CLKWISE has reached CLKWISE_THRES
  * @rmtoll ISR          ACLKWISE_F            LL_LCSC_IsActiveFlag_ACLKWISE
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsActiveFlag_ACLKWISE(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ISR, LCSC_ISR_ACLKWISE_F) == (LCSC_ISR_ACLKWISE_F)) ? 1U : 0U);
}

/**
  * @brief  Clear LCSC. Anti Clock Wise Flag
  * @rmtoll ISR          ACLKWISE_F            LL_LCSC_ClearFlag_ACLKWISE
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_ClearFlag_ACLKWISE(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ISR, LCSC_ISR_ACLKWISE_F);
}

/**
  * @brief  Indicate if TAMP_F is enabled. Tamper Flag
  * @note   0: tamper not detected
  *         1: tamper detected
  * @rmtoll ISR          TAMP_F            LL_LCSC_IsActiveFlag_TAMP
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsActiveFlag_TAMP(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ISR, LCSC_ISR_TAMP_F) == (LCSC_ISR_TAMP_F)) ? 1U : 0U);
}

/**
  * @brief  Clear LCSC. Tamper Flag
  * @rmtoll ISR          TAMP_F            LL_LCSC_ClearFlag_TAMP
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_ClearFlag_TAMP(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ISR, LCSC_ISR_TAMP_F);
}

/**
  * @brief  Indicate if CNT_OFB_F is enabled. Out of Bound Counter Flag
  * @note   0: Out of Bound not detected
  *         1: Out of Bound detected
  * @rmtoll ISR          CNT_OFB_F            LL_LCSC_IsActiveFlag_CNT_OFB
  * @param  LCSCx LCSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LCSC_IsActiveFlag_CNT_OFB(LCSC_TypeDef *LCSCx)
{
  return ((READ_BIT(LCSCx->ISR, LCSC_ISR_CNT_OFB_F) == (LCSC_ISR_CNT_OFB_F)) ? 1U : 0U);
}

/**
  * @brief  Clear LCSC. Out of Bound Counter Flag
  * @rmtoll ISR          CNT_OFB_F            LL_LCSC_ClearFlag_CNT_OFB
  * @param  LCSCx LCSC Instance
  * @retval None
  */
__STATIC_INLINE void LL_LCSC_ClearFlag_CNT_OFB(LCSC_TypeDef *LCSCx)
{
  SET_BIT(LCSCx->ISR, LCSC_ISR_CNT_OFB_F);
}


/**
  * @}
 */


/* Exported functions --------------------------------------------------------*/

/**
  * @}
 */

/**
  * @}
 */

#endif /* LCSC */

/**
  * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* STM32WL3x_LL_LCSC_H */
