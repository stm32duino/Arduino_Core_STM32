/**
  ******************************************************************************
  * @file    stm32wl3x_hal_lpawur.c
  * @author  MCD Application Team
  * @brief   This file provides firmware functions to manage the LPAWUR Radio
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
#include <string.h>

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @addtogroup LPAWUR
  * @{
  */

#ifdef HAL_LPAWUR_MODULE_ENABLED

/** @defgroup LPAWUR_Private_Macros LPAWUR Private Macros
  * @{
  */

#define IS_IRQ_ENABLE(IRQ_EN) (((IRQ_EN) == IRQ_BIT_SYNC_DETECTED) || \
					((IRQ_EN) == IRQ_FRAME_SYNC_COMPLETE) || \
					((IRQ_EN) == IRQ_FRAME_COMPLETE) || \
					((IRQ_EN) == IRQ_FRAME_VALID) )

#define IS_ERROR(ERROR) (((ERROR) == ERROR_NO) || \
					((ERROR) == ERROR_SYNC) || \
					((ERROR) == ERROR_FRAMING) || \
					((ERROR) == ERROR_CRC) )

#define IS_TREC_LOOP_ALGO(STATE) (((STATE) == DEFAULT) || ((STATE) == TWO_STEPS))

/**
  * @}
  */

/**
* @brief  Configure the RF IP of LPAWUR.
* @param  pxSLPAWUR_RFConfigStruct SLPAWUR_RFConfig configuration structure.
* @retval None.
*/
void HAL_LPAWUR_RFConfigInit(SLPAWUR_RFConfig* pxSLPAWUR_RFConfigStruct)
{
  assert_param(IS_EDICAL(pxSLPAWUR_RFConfigStruct->EnergyDetectorIcal));
  assert_param(IS_AGC_MODE(pxSLPAWUR_RFConfigStruct->AgcMode));
  assert_param(IS_AGC_HOLD_MODE(pxSLPAWUR_RFConfigStruct->AgcHoldMode));

  HAL_LPAWUR_MspInit();

  /* Set Energy Detector Calibration value */
  LL_LPAWUR_SetEdIcal(pxSLPAWUR_RFConfigStruct->EnergyDetectorIcal);

  /* Configure Clock divider */
  LL_LPAWUR_SetClkDiv(pxSLPAWUR_RFConfigStruct->ClockDivider);

  /* Configure Energy Detector switch */
  LL_LPAWUR_SetEdSwitch(pxSLPAWUR_RFConfigStruct->EnergyDetectorSwitch);

  /* Configure AGC Reset Mode */
  LL_LPAWUR_SetAgcResetMode(pxSLPAWUR_RFConfigStruct->AgcResetMode);

  /* Configure AGC Hold Mode */
  LL_LPAWUR_SetAgcHoldMode(pxSLPAWUR_RFConfigStruct->AgcHoldMode);

  /* Configure Agc Mode */
  LL_LPAWUR_SetAgcMode(pxSLPAWUR_RFConfigStruct->AgcMode);

  /* Configure Agc level High */
  LL_LPAWUR_SetAGCHighLevel(pxSLPAWUR_RFConfigStruct->AgcHiLvl);

  /* Configure DC current subtraction enabling signal */
  LL_LPAWUR_EnableDCControl(pxSLPAWUR_RFConfigStruct->DCCurrentSubtraction);

  /* Configure Agc level Low */
  LL_LPAWUR_SetAGCLowLevel(pxSLPAWUR_RFConfigStruct->AgcLoLvl);

}

/**
* @brief  Get the LPAWUR RF IP configuration.
* @retval SLPAWUR_RFConfig configuration structure.
*/
SLPAWUR_RFConfig HAL_LPAWUR_GetRFConfig(void)
{
  SLPAWUR_RFConfig SLPAWUR_CurrentRFConfig;

  SLPAWUR_CurrentRFConfig.EnergyDetectorIcal = LL_LPAWUR_GetEdIcal();
  SLPAWUR_CurrentRFConfig.ClockDivider = LL_LPAWUR_GetClkDiv();
  SLPAWUR_CurrentRFConfig.EnergyDetectorSwitch = LL_LPAWUR_GetEdSwitch();
  SLPAWUR_CurrentRFConfig.AgcResetMode = LL_LPAWUR_GetAgcResetMode();
  SLPAWUR_CurrentRFConfig.AgcHoldMode = LL_LPAWUR_GetAgcHoldMode();
  SLPAWUR_CurrentRFConfig.AgcMode = LL_LPAWUR_GetAgcMode();

  return SLPAWUR_CurrentRFConfig;
}

/**
* @brief  Configure the frame of LPAWUR RF IP.
* @param  pxSLPAWUR_FrameInitStruct SLPAWUR_FrameInit configuration structure.
* @retval None.
*/
void HAL_LPAWUR_FrameInit(SLPAWUR_FrameInit* pxSLPAWUR_FrameInitStruct)
{
  assert_param(IS_LPAWUR_PAYLOAD_LENGTH(pxSLPAWUR_FrameInitStruct->PayloadLength));

  /* Set the Timing recovery loop algorithm selection */
  LL_LPAWUR_SetTRecAlgorithm(pxSLPAWUR_FrameInitStruct->TRecAlgoSel);

  /* Set the Slow Clock Cycle Per Bit counter */
  LL_LPAWUR_SetSlowClkCyclePerBitCnt(pxSLPAWUR_FrameInitStruct->SlowClkCyclePerBitCnt);

  /* Set the Paylaod Length */
  LL_LPAWUR_SetPayloadLength(pxSLPAWUR_FrameInitStruct->PayloadLength);

  /* Set the SYNC threshold */
  LL_LPAWUR_SetSyncThrCnt(pxSLPAWUR_FrameInitStruct->SyncThr);

  /* Set the SYNC Length */
  LL_LPAWUR_SetSyncLength(pxSLPAWUR_FrameInitStruct->SyncLength);

  /* Set the Preamble threshold counter */
  LL_LPAWUR_SetPreambleThrCnt(pxSLPAWUR_FrameInitStruct->PreambleThrCnt);

  /* Set the Preamble Enable State */
  LL_LPAWUR_SetPreambleEnable(pxSLPAWUR_FrameInitStruct->PreambleEnable);

  /* Set the SYNC counter timeout */
  LL_LPAWUR_SetFrameSyncCntTimeout(pxSLPAWUR_FrameInitStruct->FrameSyncCntTimeout);

  /* Configure the SYNC pattern */
  HAL_LPAWUR_SetSync((uint32_t)(pxSLPAWUR_FrameInitStruct->FrameSyncPattenHigh<<16) +\
                 (uint32_t)(pxSLPAWUR_FrameInitStruct->FrameSyncPatternLow));

  /* Configure the kp gain value for the timing recovery loop */
  LL_LPAWUR_SetKp(pxSLPAWUR_FrameInitStruct->KpGain);

  /* Configure the ki gain value for the timing recovery loop */
  LL_LPAWUR_SetKi(pxSLPAWUR_FrameInitStruct->KiGain);
}

/**
* @brief  Get the frame configuration of LPAWUR RF IP.
* @retval SLPAWUR_FrameInit configuration structure.
*/
SLPAWUR_FrameInit HAL_LPAWUR_GetFrameInfo(void)
{
  SLPAWUR_FrameInit SLPAWUR_CurrentFrameInfo;

  SLPAWUR_CurrentFrameInfo.SlowClkCyclePerBitCnt = LL_LPAWUR_GetSlowClkCyclePerBitCnt();
  SLPAWUR_CurrentFrameInfo.PayloadLength = LL_LPAWUR_GetPayloadLength();
  SLPAWUR_CurrentFrameInfo.SyncThr = LL_LPAWUR_GetSyncThrCnt();
  SLPAWUR_CurrentFrameInfo.SyncLength = LL_LPAWUR_GetSyncLength();
  SLPAWUR_CurrentFrameInfo.PreambleThrCnt = LL_LPAWUR_GetPreambleThrCnt();
  SLPAWUR_CurrentFrameInfo.PreambleEnable = LL_LPAWUR_GetPreambleEnable();
  SLPAWUR_CurrentFrameInfo.FrameSyncCntTimeout = LL_LPAWUR_GetFrameSyncCntTimeout();
  SLPAWUR_CurrentFrameInfo.FrameSyncPattenHigh = LL_LPAWUR_GetSyncPatternHigh();
  SLPAWUR_CurrentFrameInfo.FrameSyncPatternLow = LL_LPAWUR_GetSyncPatternLow();

  return SLPAWUR_CurrentFrameInfo;
}

/**
* @brief  Configure the IRQ of LPAWUR.
* @param  IrqEnable LPAWUR_IrqEnable configuration structure.
* @retval None.
*/
void HAL_LPAWUR_IrqConfig(LPAWUR_IrqEnable IrqEnable)
{
  assert_param(IS_IRQ_ENABLE(IrqEnable));
  if(IrqEnable == IRQ_BIT_SYNC_DETECTED)
  {
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_BIT_SYNC_DETECTED_E,0x01);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_SYNC_COMPLETE_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_COMPLETE_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_VALID_E,0x00);
  }
  else if(IrqEnable == IRQ_FRAME_SYNC_COMPLETE)
  {
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_BIT_SYNC_DETECTED_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_SYNC_COMPLETE_E,0x01);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_COMPLETE_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_VALID_E,0x00);
  }
  else if(IrqEnable == IRQ_FRAME_COMPLETE)
  {
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_BIT_SYNC_DETECTED_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_SYNC_COMPLETE_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_COMPLETE_E,0x01);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_VALID_E,0x00);
  }
  else if(IrqEnable == IRQ_FRAME_VALID)
  {
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_BIT_SYNC_DETECTED_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_SYNC_COMPLETE_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_COMPLETE_E,0x00);
	MODIFY_REG_FIELD(LPAWUR->IRQ_ENABLE,LPAWUR_IRQ_ENABLE_FRAME_VALID_E,0x01);
  }
}

/**
* @brief  Get the RX status of LPAWUR.
* @retval LPAWUR_Status configuration structure.
*/
LPAWUR_Status HAL_LPAWUR_GetStatus(void)
{
  LPAWUR_Status status = NO_STATUS;
  if(READ_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_BIT_SYNC_DETECTED_F))
	status = BIT_SYNC_DETECTED_F;
  if(READ_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_FRAME_SYNC_COMPLETE_F))
	status = FRAME_SYNC_COMPLETE_F;
  if(READ_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_FRAME_COMPLETE_F))
	status = FRAME_COMPLETE_F;
  if(READ_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_FRAME_VALID_F))
	status = FRAME_VALID_F;

  return status;
}

/**
* @brief  Reset the RX status of LPAWUR.
* @retval None.
*/
void HAL_LPAWUR_ClearStatus(void)
{
  MODIFY_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_BIT_SYNC_DETECTED_F,0x01);
  MODIFY_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_FRAME_SYNC_COMPLETE_F,0x01);
  MODIFY_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_FRAME_COMPLETE_F,0x01);
  MODIFY_REG_FIELD(LPAWUR->STATUS,LPAWUR_STATUS_FRAME_VALID_F,0x01);
}

/**
* @brief  Set the LPAWUR Sync word.
* @param  sync 32 bits SYNC word.
* @retval None.
*/
void HAL_LPAWUR_SetSync(uint32_t sync)
{
  uint16_t SyncHigh = (uint16_t)(sync>>16);
  uint16_t SyncLow = (uint16_t)(sync&0x0000FFFF);
  MODIFY_REG_FIELD(LPAWUR->FRAME_SYNC_CONFIG, LPAWUR_FRAME_SYNC_CONFIG_FRAME_SYNC_PATTERN_H, SyncHigh);
  MODIFY_REG_FIELD(LPAWUR->FRAME_SYNC_CONFIG, LPAWUR_FRAME_SYNC_CONFIG_FRAME_SYNC_PATTERN_L, SyncLow);
}

/**
* @brief  Get the LPAWUR SYNC word.
* @retval 32 bits SYNC word (manchester coded).
*/
uint32_t HAL_LPAWUR_GetSync(void)
{
  uint16_t SyncHigh = READ_REG_FIELD(LPAWUR->FRAME_SYNC_CONFIG,LPAWUR_FRAME_SYNC_CONFIG_FRAME_SYNC_PATTERN_H);
  uint16_t SyncLow = READ_REG_FIELD(LPAWUR->FRAME_SYNC_CONFIG,LPAWUR_FRAME_SYNC_CONFIG_FRAME_SYNC_PATTERN_L);

  return (uint32_t)((SyncHigh<<16) + SyncLow);
}

/**
* @brief  Get the payload.
* @param  buff buffer and length.
* @retval None.
*/
void HAL_LPAWUR_GetPayload(uint8_t* buff)
{
  uint32_t payload0 = READ_REG_FIELD(LPAWUR->PAYLOAD_0,LPAWUR_PAYLOAD_0_PAYLOAD_0);
  uint32_t payload1 = READ_REG_FIELD(LPAWUR->PAYLOAD_1,LPAWUR_PAYLOAD_1_PAYLOAD_1);
  uint8_t length = LL_LPAWUR_GetPayloadLength();

  for( uint8_t i=0; i<4 ; i++)
  {
    buff[i] = ((payload0>>(i*8)) & 0xFF);
  }

  if(length > 4)
  {
    for(uint8_t j=0; j<length-4; j++)
    {
	buff[j+4] = ((payload1>>(j*8)) & 0xFF);
    }
  }
}

/**
* @brief  Get the IP version of the LPAWUR block.
* @retval IP version.
*/
SLPAWUR_Version HAL_LPAWUR_GetVersion(void)
{
  SLPAWUR_Version LPAWUR_Version;

  LPAWUR_Version.product = READ_REG_FIELD(LPAWUR->RFIP_VERSION, LPAWUR_RFIP_VERSION_PRODUCT);
  LPAWUR_Version.version = READ_REG_FIELD(LPAWUR->RFIP_VERSION, LPAWUR_RFIP_VERSION_VERSION);
  LPAWUR_Version.revision = READ_REG_FIELD(LPAWUR->RFIP_VERSION, LPAWUR_RFIP_VERSION_REVISION);

  return LPAWUR_Version;
}

/**
  * @brief LPAWUR MSP Init
  * @retval None
  */
__weak void HAL_LPAWUR_MspInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LPAWUR_MspInit could be implemented in the user file
    */
}

/**
  * @brief LPAWUR MSP DeInit
  * @retval None
  */
__weak void HAL_LPAWUR_MspDeInit(void)
{

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LPAWUR_MspDeInit could be implemented in the user file
    */
}

__weak void HAL_LPAWUR_IRQ_Callback(void)
{
}

void HAL_LPAWUR_IRQHandler(void)
{
  HAL_LPAWUR_IRQ_Callback();
}

/**
  * @}
  */

#endif /* HAL_LPAWUR_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
