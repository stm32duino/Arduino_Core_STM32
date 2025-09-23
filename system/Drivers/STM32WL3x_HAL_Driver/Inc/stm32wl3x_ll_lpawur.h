/**
  ******************************************************************************
  * @file    stm32wl3x_ll_lpawur.h
  * @author  MCD Application Team
  * @brief   Header file of LPAWUR LL module.
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
#ifndef STM32WL3x_LL_LPAWUR_H
#define STM32WL3x_LL_LPAWUR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32wl3x_ll_utils.h"
#include "stm32wl3x.h"

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

/** @addtogroup LPAWUR
  * @{
  */

/** @defgroup LPAWUR_Private_Constants LPAWUR Private Constants
  * @{
  */

#define MINIMUM_LPAWUR_PAYLOAD_LEN		0x1
#define MAXIMUM_LPAWUR_PAYLOAD_LEN		0x8

/**
  * @}
  */

/** @defgroup LPAWUR_Exported_Macros LPAWUR Exported Macros
* @{
  */

/**
 * @brief  Check if the payload length is within the valid range for LPAWUR.
 * @param  PAYLOAD_LEN Payload length to be checked.
 * @retval True if the payload length is within the valid range, false otherwise.
 */
#define IS_LPAWUR_PAYLOAD_LENGTH(PAYLOAD_LEN) ((PAYLOAD_LEN)>=MINIMUM_LPAWUR_PAYLOAD_LEN && \
                                             (PAYLOAD_LEN)<=MAXIMUM_LPAWUR_PAYLOAD_LEN)

/**
 * @brief  Check if the wakeup value is valid.
 * @param  WAKEUP Wakeup value to be checked.
 * @retval True if the wakeup value is valid, false otherwise.
 */
#define IS_WAKEUP(WAKEUP) (((WAKEUP) == WAKEUP_BIT_SYNC) || \
					((WAKEUP) == WAKEUP_FRAME_SYNC) || \
					((WAKEUP) == WAKEUP_FRAME_COMPLETE) || \
					((WAKEUP) == WAKEUP_FRAME_VALID) )

/**
 * @brief  Check if the EDICAL value is valid.
 * @param  EDICAL EDICAL value to be checked.
 * @retval True if the EDICAL value is valid, false otherwise.
 */
#define IS_EDICAL(EDICAL) (((EDICAL) == ED_ICAL_VBAT_1_70_TO_2_00) || \
					((EDICAL) == ED_ICAL_VBAT_2_00_TO_2_25) || \
					((EDICAL) == ED_ICAL_VBAT_2_25_TO_2_50) || \
					((EDICAL) == ED_ICAL_VBAT_2_50_TO_2_75) || \
					((EDICAL) == ED_ICAL_VBAT_2_75_TO_3_00) || \
					((EDICAL) == ED_ICAL_VBAT_3_00_TO_3_25) || \
					((EDICAL) == ED_ICAL_VBAT_3_25_TO_3_50) || \
					((EDICAL) == ED_ICAL_VBAT_3_50_TO_3_75) )

/**
 * @brief  Check if the AGC high level value is valid.
 * @param  AGC_LEVEL AGC high level value to be checked.
 * @retval True if the AGC high level value is valid, false otherwise.
 */
#define IS_AGC_HIGH_LEVEL(AGC_LEVEL) (((AGC_LEVEL) == AGC_VBAT_0500) || \
					((AGC_LEVEL) == AGC_VBAT_0575) || \
                                        ((AGC_LEVEL) == AGC_VBAT_0650) || \
                                        ((AGC_LEVEL) == AGC_VBAT_0725) || \
                                        ((AGC_LEVEL) == AGC_VBAT_0800) || \
                                        ((AGC_LEVEL) == AGC_VBAT_0875) || \
                                        ((AGC_LEVEL) == AGC_VBAT_0950) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1025) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1100) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1175) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1250) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1325) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1400) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1475) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1550) || \
                                        ((AGC_LEVEL) == AGC_VBAT_1625) )

/**
 * @brief  Check if the AGC low level value is valid.
 * @param  AGC_LEVEL AGC low level value to be checked.
 * @retval True if the AGC low level value is valid, false otherwise.
 */
#define IS_AGC_LOW_LEVEL(AGC_LEVEL) (((AGC_LEVEL) == AGC_LOW_0) || \
                                      ((AGC_LEVEL) == AGC_LOW_1) || \
                                      ((AGC_LEVEL) == AGC_LOW_2) || \
                                      ((AGC_LEVEL) == AGC_LOW_3) )

/**
 * @brief  Check if the AGC hold mode value is valid.
 * @param  HOLD_MODE AGC hold mode value to be checked.
 * @retval True if the AGC hold mode value is valid, false otherwise.
 */
#define IS_AGC_HOLD_MODE(HOLD_MODE) (((HOLD_MODE) == AGC_HOLD_AFTER_PREAMBLE) || \
					((HOLD_MODE) == AGC_HOLD_AFTER_SYNC) )

/**
 * @brief  Check if the AGC mode value is valid.
 * @param  AGC_MODE AGC mode value to be checked.
 * @retval True if the AGC mode value is valid, false otherwise.
 */
#define IS_AGC_MODE(AGC_MODE) (((AGC_MODE) == AGC_MODE_MAX) || \
					((AGC_MODE) == AGC_MODE_OFF) || \
					((AGC_MODE) == AGC_MODE_ON) || \
					((AGC_MODE) == AGC_MODE_HOLD) )

/**
  * @}
  */

/** @defgroup LPAWUR_Exported_Types LPAWUR Exported Types
  * @{
  */
/**
 * @brief  STM32WL3 LPAWUR Wakeup enumeration
 */
typedef enum {
  WAKEUP_BIT_SYNC       = 0x00, /*!< the bit Sync has been detected */
  WAKEUP_FRAME_SYNC     = 0x01, /*!< Frame sync detected */
  WAKEUP_FRAME_COMPLETE = 0x02, /*!< Frame_complete detected */
  WAKEUP_FRAME_VALID    = 0x03  /*!< Frame_Valid detected (default value) */
} WakeUpLevel;

/**
 * @brief  STM32WL3 LPAWUR ERROR enumeration
 */
typedef enum {
  ERROR_NO      = 0x00, /*!< NO ERROR */
  ERROR_SYNC    = 0x01, /*!< error in SYNC word */
  ERROR_FRAMING = 0x02, /*!< FRAMING error */
  ERROR_CRC     = 0x03  /*!< CRC error */
} LPAWUR_Error;

/**
 * @brief  STM32WL3 LPAWUR ED_ICAL enumeration
 */
typedef enum {
  ED_ICAL_VBAT_1_70_TO_2_00	= 0x00, /*!< VBAT=1.7 to 2.0V (default value) */
  ED_ICAL_VBAT_2_00_TO_2_25	= 0x01, /*!< VBAT=2.0 to 2.25V */
  ED_ICAL_VBAT_2_25_TO_2_50	= 0x02, /*!< VBAT=2.25 to 2.5V */
  ED_ICAL_VBAT_2_50_TO_2_75	= 0x03, /*!< VBAT=2.5 to 2.75V */
  ED_ICAL_VBAT_2_75_TO_3_00	= 0x04, /*!< VBAT=2.75 to 3.0V */
  ED_ICAL_VBAT_3_00_TO_3_25	= 0x05, /*!< VBAT=3.0 to 3.25V */
  ED_ICAL_VBAT_3_25_TO_3_50	= 0x06, /*!< VBAT=3.25 to 3.5V */
  ED_ICAL_VBAT_3_50_TO_3_75	= 0x07  /*!< VBAT=3.5 to 3.75V */
} EdIcal;

/**
 * @brief  STM32WL3 LPAWUR AGC_HIGH_LEVEL enumeration
 */
typedef enum {
  AGC_VBAT_0500	= 0x00, /*!< AGC VBAT=0.5V */
  AGC_VBAT_0575	= 0x01, /*!< AGC VBAT=0.575V */
  AGC_VBAT_0650	= 0x02, /*!< AGC VBAT=0.650V */
  AGC_VBAT_0725	= 0x03, /*!< AGC VBAT=0.725V */
  AGC_VBAT_0800	= 0x04, /*!< AGC VBAT=0.8V (default value) */
  AGC_VBAT_0875	= 0x05, /*!< AGC VBAT=0.875V */
  AGC_VBAT_0950	= 0x06, /*!< AGC VBAT=0.950V */
  AGC_VBAT_1025	= 0x07, /*!< AGC VBAT=1.025V */
  AGC_VBAT_1100	= 0x08, /*!< AGC VBAT=1.1V */
  AGC_VBAT_1175	= 0x09, /*!< AGC VBAT=1.175V */
  AGC_VBAT_1250	= 0x0A, /*!< AGC VBAT=1.25V */
  AGC_VBAT_1325	= 0x0B, /*!< AGC VBAT=1.325V */
  AGC_VBAT_1400	= 0x0C, /*!< AGC VBAT=1.4V */
  AGC_VBAT_1475	= 0x0D, /*!< AGC VBAT=1.475V */
  AGC_VBAT_1550	= 0x0E, /*!< AGC VBAT=1.55V */
  AGC_VBAT_1625	= 0x0F, /*!< AGC VBAT=1.625V */
} AgcHighLevel;

/**
 * @brief  STM32WL3 LPAWUR AGC_LOW_LEVEL enumeration
 */
typedef enum {
  AGC_LOW_0	= 0x00, /*!< AGC reference level = 0 V */
  AGC_LOW_1	= 0x01, /*!< AGC reference level = 100 mV */
  AGC_LOW_2	= 0x02, /*!< AGC reference level = 200 mV (default value) */
  AGC_LOW_3	= 0x03, /*!< AGC reference level = 300 mV */
} AgcLowLevel;

/**
 * @brief  STM32WL3 LPAWUR AGC Hold Mode enumeration
 */
typedef enum {
  AGC_HOLD_AFTER_PREAMBLE = 0x00, /*!< AGC Hold after preamble detection (default) */
  AGC_HOLD_AFTER_SYNC     = 0x01  /*!< AGC Hold after Sync detection */
} AgcHoldType;

/**
 * @brief  STM32WL3 LPAWUR AGC Hold Mode enumeration
 */
typedef enum {
  AGC_MODE_MAX 			  = 0x00, /*!< AGC Mode MAX (default) */
  AGC_MODE_OFF    		= 0x01, /*!< AGC Mode OFF */
  AGC_MODE_ON     		= 0x02, /*!< AGC Mode ON */
  AGC_MODE_HOLD    		= 0x03  /*!< AGC HOLD: the AGC is ON and its value is frozen during the LPAWUR frame detection */
} AgcMode;

typedef enum {
  AGC_RESET_MODE_AFTER_FRAME  = 0x00, /*!< reset the AGC after the complete frame detection */
  AGC_RESET_MODE_NEVER        = 0x01  /*!< the AGC is never reset */
} AgcResetMode;

/**
 * @brief  STM32WL3 LPAWUR TREC LOOP Algorithm
 */
typedef enum
{
  DEFAULT = 0,          /*!< The timing recovery loop algorithm is a second order loop with a defined leakage (0.98) */
  TWO_STEPS = !DEFAULT  /*!< The timing recovery loop algorithm is with two steps. First order loop until preamble detected and second order loop after */
} TrecLoopAlgo;

/** @defgroup LPAWUR_Exported_Functions LPAWUR Exported Functions
  * @{
  */
/**
* @brief  Read the error status of LPAWUR.
* @retval LPAWUR_Error value.
*/
__STATIC_INLINE LPAWUR_Error LL_LPAWUR_ReadError(void)
{
  return (LPAWUR_Error)(READ_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_ERROR_F));
}

/**
* @brief  Clear the error status of LPAWUR.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_ClearErrorStatus(void)
{
  MODIFY_REG_FIELD(LPAWUR->STATUS, LPAWUR_STATUS_ERROR_F, 0x01);
}


/**
* @brief  Set the Slow Clock Cycle Bit Counter.
* @param  ClkCyclePerBit The Slow Clock Cycle Bit Counter.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetSlowClkCyclePerBitCnt(uint8_t ClkCyclePerBit)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG0, LPAWUR_FRAME_CONFIG0_SLOW_CLK_CYCLE_PER_BIT_CNT, ClkCyclePerBit);
}


/**
* @brief  Get the Slow Clock Cycle Bit Counter.
* @retval ClkCyclePerBit.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetSlowClkCyclePerBitCnt(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG0,LPAWUR_FRAME_CONFIG0_SLOW_CLK_CYCLE_PER_BIT_CNT));
}

/**
* @brief  Set the Payload Length.
* @param  length The Payload Length.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetPayloadLength(uint8_t length)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG0, LPAWUR_FRAME_CONFIG0_PAYLOAD_LENGTH,length);
}

/**
* @brief  Get the payload length.
* @retval Length.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetPayloadLength(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG0, LPAWUR_FRAME_CONFIG0_PAYLOAD_LENGTH));
}

/**
* @brief  Set SYNC threshold counter.
* @param  SyncThrCnt The SYNC threshold counter.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetSyncThrCnt(uint8_t SyncThrCnt)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG0,LPAWUR_FRAME_CONFIG0_SYNC_THRESHOLD_COUNT,SyncThrCnt);
}

/**
* @brief  Get the SYNC threshold counter.
* @retval Sync threshold counter.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetSyncThrCnt(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG0, LPAWUR_FRAME_CONFIG0_SYNC_THRESHOLD_COUNT));
}

/**
* @brief  Set the LPAWUR SYNC length.
* @param  SyncLen The LPAWUR SYNC length.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetSyncLength(uint8_t SyncLen)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG0, LPAWUR_FRAME_CONFIG0_SYNC_LENGTH, SyncLen);
}

/**
* @brief  Get the LPAWUR SYNC length.
* @retval SyncLen.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetSyncLength(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG0,LPAWUR_FRAME_CONFIG0_SYNC_LENGTH));
}

/**
* @brief  Set the Preamble threshold counter.
* @param  cnt counter value.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetPreambleThrCnt(uint8_t cnt)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG0,LPAWUR_FRAME_CONFIG0_PREAMBLE_THRESHOLD_COUNT,cnt);
}

/**
* @brief  Get the Preamble threshold counter.
* @retval Counter value.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetPreambleThrCnt(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG0,LPAWUR_FRAME_CONFIG0_PREAMBLE_THRESHOLD_COUNT));
}

/**
* @brief  Set the Timing recovery loop algorithm selection.
* @param  algoSel the algorithm selection.
* 	This value is type of @ref TrecLoopAlgo.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetTRecAlgorithm(TrecLoopAlgo algoSel)
{
  if(algoSel == DEFAULT)
  {
    MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_TREC_LOOP_ALGO_SEL, 0x0);
  }
  else
  {
    MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_TREC_LOOP_ALGO_SEL, 0x1);
  }
}

/**
* @brief  Get the Timing recovery loop algorithm selection.
* @retval algorithm selection.
* 	This value is type of @ref TrecLoopAlgo.
*/
__STATIC_INLINE TrecLoopAlgo LL_LPAWUR_GetTRecAlgorithm(void)
{
  if(READ_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_TREC_LOOP_ALGO_SEL))
    return TWO_STEPS;
  else
    return DEFAULT;
}

/**
* @brief  Set the preamble enable.
* @param  state enable or disable the preamble.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetPreambleEnable(FunctionalState state)
{
  if(state == ENABLE)
  {
    MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_PREAMBLE_ENABLE,0x1);
  }
  else
  {
    MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_PREAMBLE_ENABLE,0x0);
  }
}

/**
* @brief  Get the preamble enable state.
* @retval Preamble enable state.
*/
__STATIC_INLINE FunctionalState LL_LPAWUR_GetPreambleEnable(void)
{
  if(READ_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_PREAMBLE_ENABLE))
    return ENABLE;
  else
    return DISABLE;
}

/**
* @brief  Set Frame Sync counter timeout.
* @param  timeout the Frame Sync counter timeout.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetFrameSyncCntTimeout(uint8_t timeout)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_FRAME_SYNC_COUNTER_TIMEOUT,timeout);
}

/**
* @brief  Get the Frame Sync counter timeout value.
* @retval Counter timeout.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetFrameSyncCntTimeout(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_FRAME_SYNC_COUNTER_TIMEOUT));
}

/**
* @brief  Set the Kp parameter for clock recovery.
* @param  v_kp The Kp parameter for clock recovery.
* @retval None
*/
__STATIC_INLINE void LL_LPAWUR_SetKp(uint8_t v_kp)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_KP,v_kp);
}

/**
* @brief  Get the Kp parameter.
* @retval Kp.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetKp(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_KP));
}

/**
* @brief  Set the Ki parameter for clock recovery.
* @param  v_ki The Ki parameter for clock recovery.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetKi(uint8_t v_ki)
{
  MODIFY_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_KI,v_ki);
}

/**
* @brief  Get the Ki parameter.
* @retval Ki.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetKi(void)
{
  return (uint8_t)(READ_REG_FIELD(LPAWUR->FRAME_CONFIG1,LPAWUR_FRAME_CONFIG1_KI));
}

/**
* @brief  Get the High SYNC pattern.
* @retval 16bits HIGH SYNC pattern (manchester encoded).
*/
__STATIC_INLINE uint16_t LL_LPAWUR_GetSyncPatternHigh(void)
{
  uint16_t SyncHigh = READ_REG_FIELD(LPAWUR->FRAME_SYNC_CONFIG,LPAWUR_FRAME_SYNC_CONFIG_FRAME_SYNC_PATTERN_H);
  return SyncHigh;
}

/**
* @brief  Get the Low SYNC pattern.
* @retval 16bits LOW SYNC pattern (manchester encoded).
*/
__STATIC_INLINE uint16_t LL_LPAWUR_GetSyncPatternLow(void)
{
  uint16_t SyncLow = READ_REG_FIELD(LPAWUR->FRAME_SYNC_CONFIG,LPAWUR_FRAME_SYNC_CONFIG_FRAME_SYNC_PATTERN_L);
  return SyncLow;
}

/**
* @brief  Set the LPAWUR Wake Up level.
* @param  xWakeUpLvl The LPAWUR Wake Up level.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetWakeUpLevel(WakeUpLevel xWakeUpLvl)
{
  MODIFY_REG_FIELD(LPAWUR->RFIP_CONFIG,LPAWUR_RFIP_CONFIG_WAKEUP_LEVEL,xWakeUpLvl);
}

/**
* @brief  Get the LPAWUR Wake Up level.
* @retval WakeUpLevel.
*/
__STATIC_INLINE WakeUpLevel LL_LPAWUR_GetWakeUpLevel(void)
{
  return (WakeUpLevel)READ_REG_FIELD(LPAWUR->RFIP_CONFIG,LPAWUR_RFIP_CONFIG_WAKEUP_LEVEL);
}

/**
* @brief  Enable or Disable the LPAWUR feature.
* @param  state Enable or Disable the LPAWUR.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetState(FunctionalState state)
{
  if(state == ENABLE)
  {
    SET_BIT(LPAWUR->RFIP_CONFIG,LPAWUR_RFIP_CONFIG_LPAWUR_ENABLE);
  }
  else
  {
    CLEAR_BIT(LPAWUR->RFIP_CONFIG,LPAWUR_RFIP_CONFIG_LPAWUR_ENABLE);
  }
}

/**
* @brief  Get the LPAWUR feature state.
* @retval state.
*/
__STATIC_INLINE FunctionalState LL_LPAWUR_GetState(void)
{
  if(READ_REG_FIELD(LPAWUR->RFIP_CONFIG,LPAWUR_RFIP_CONFIG_LPAWUR_ENABLE))
    return ENABLE;
  else
    return DISABLE;
}

/**
* @brief  Set the Energy Detector calibration value.
* @param  value calibration value.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetEdIcal(EdIcal value)
{
  MODIFY_REG_FIELD(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_ED_ICAL,value);
}

/**
* @brief  Get the ED calibration value.
* @retval calibration value.
*/
__STATIC_INLINE EdIcal LL_LPAWUR_GetEdIcal(void)
{
  return (EdIcal)READ_REG_FIELD(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_ED_ICAL);
}

/**
* @brief  Set the AGC High Level value.
* @param  value AGC High Level value.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetAGCHighLevel(AgcHighLevel value)
{
  MODIFY_REG_FIELD(LPAWUR->RF_CONFIG, LPAWUR_RF_CONFIG_AGC_HIGH_LVL, value);
}

/**
* @brief  Get the AGC High Level value.
* @retval AGC High Level value.
*/
__STATIC_INLINE AgcHighLevel LL_LPAWUR_GetAGCHighLevel(void)
{
  return (AgcHighLevel)READ_REG_FIELD(LPAWUR->RF_CONFIG, LPAWUR_RF_CONFIG_AGC_HIGH_LVL);
}

/**
* @brief  Set the DC level shift enable.
* @param  state enable state.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_EnableDCControl(FunctionalState state)
{
  if(state == ENABLE)
  {
    SET_BIT(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_ED_DC_CTRL); /* DC level shift (default value) */
  }
  else
  {
    CLEAR_BIT(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_ED_DC_CTRL);  /* No DC level shift */
  }
}

/**
* @brief  Set the AGC Low Level value.
* @param  value AGC Low Level value.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetAGCLowLevel(AgcLowLevel value)
{
  MODIFY_REG_FIELD(LPAWUR->RF_CONFIG, LPAWUR_RF_CONFIG_AGC_LOW_LVL, value);
}

/**
* @brief  Get the AGC Low Level value.
* @retval AGC Low Level value.
*/
__STATIC_INLINE AgcLowLevel LL_LPAWUR_GetAGCLowLevel(void)
{
  return (AgcLowLevel)READ_REG_FIELD(LPAWUR->RF_CONFIG, LPAWUR_RF_CONFIG_AGC_LOW_LVL);
}

/**
* @brief  Set the Clock divider
* @param  div The Clock divider.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetClkDiv(uint8_t div)
{
  MODIFY_REG_FIELD(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_CLKDIV,div);
}

/**
* @brief  Get the clock divider value.
* @retval div.
*/
__STATIC_INLINE uint8_t LL_LPAWUR_GetClkDiv(void)
{
  return (uint8_t)READ_REG_FIELD(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_CLKDIV);
}

/**
* @brief  Set the ED switch.
* @param  state The ED switch state.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetEdSwitch(FunctionalState state)
{
  if(state == ENABLE)
  {
    SET_BIT(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_ED_SWITCH);
  }
  else
  {
    CLEAR_BIT(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_ED_SWITCH);
  }
}

/**
* @brief  Get the ED switch feature state.
* @retval state.
*/
__STATIC_INLINE FunctionalState LL_LPAWUR_GetEdSwitch(void)
{
  if(READ_REG_FIELD(LPAWUR->RF_CONFIG,LPAWUR_RF_CONFIG_ED_SWITCH))
    return ENABLE;
  else
    return DISABLE;
}

/**
* @brief  Set the AGC reset Mode.
* @param  mode The AGC reset Mode.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetAgcResetMode(AgcResetMode mode)
{
  if(mode == AGC_RESET_MODE_NEVER)
  {
    SET_BIT(LPAWUR->AGC_CONFIG,LPAWUR_AGC_CONFIG_AGC_RESET_MODE);
  }
  else
  {
    CLEAR_BIT(LPAWUR->AGC_CONFIG,LPAWUR_AGC_CONFIG_AGC_RESET_MODE);
  }
}

/**
* @brief  Get the AGC reset mode.
* @retval state.
*/
__STATIC_INLINE AgcResetMode LL_LPAWUR_GetAgcResetMode(void)
{
  if(READ_REG_FIELD(LPAWUR->AGC_CONFIG,LPAWUR_AGC_CONFIG_AGC_RESET_MODE))
    return AGC_RESET_MODE_NEVER;
  else
    return AGC_RESET_MODE_AFTER_FRAME;
}

/**
* @brief  Set the AGC Hold mode.
* @param  mode The AGC Hold mode.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetAgcHoldMode(AgcHoldType mode)
{
  MODIFY_REG_FIELD(LPAWUR->AGC_CONFIG,LPAWUR_AGC_CONFIG_AGC_HOLD_MODE,mode);
}

/**
* @brief  Get the AGC Hold mode.
* @retval hold mode.
*/
__STATIC_INLINE AgcHoldType LL_LPAWUR_GetAgcHoldMode(void)
{
  return (AgcHoldType)READ_REG_FIELD(LPAWUR->AGC_CONFIG,LPAWUR_AGC_CONFIG_AGC_HOLD_MODE);
}

/**
* @brief  Set the AGC mode.
* @param  mode The AGC mode.
* @retval None.
*/
__STATIC_INLINE void LL_LPAWUR_SetAgcMode(AgcMode mode)
{
  MODIFY_REG_FIELD(LPAWUR->AGC_CONFIG,LPAWUR_AGC_CONFIG_AGC_MODE,mode);
}

/**
* @brief  Get the AGC mode.
* @retval mode.
*/
__STATIC_INLINE AgcMode LL_LPAWUR_GetAgcMode(void)
{
  return (AgcMode)READ_REG_FIELD(LPAWUR->AGC_CONFIG,LPAWUR_AGC_CONFIG_AGC_MODE);
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

#endif /*STM32WL3x_LL_LPAWUR_H */
