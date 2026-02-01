/**
  ******************************************************************************
  * @file    stm32wl3x_hal_lpawur.h
  * @author  MCD Application Team
  * @brief   Header file of LPAWUR HAL module.
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
#ifndef STM32WL3x_HAL_LPAWUR_H
#define STM32WL3x_HAL_LPAWUR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_ll_lpawur.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */
#if defined (LPAWUR)
/** @addtogroup LPAWUR
  * @{
  */

/** @defgroup LPAWUR_Exported_Macros LPAWUR Exported Macros
  * @{
  */

/**
 * @brief  Set the frame sync configuration for LPAWUR.
 * @param  __VAL__ Value to be set for the frame sync configuration.
 */
#define __HAL_LPAWUR_SET_FRAME_SYNC_CONFIG(__VAL__)           WRITE_REG(LPAWUR->FRAME_SYNC_CONFIG, __VAL__);

  /**
  * @}
  */


/** @defgroup LPAWUR_Exported_Types LPAWUR Exported Types
  * @{
  */

/**
 * @brief  STM32WL3 LPAWUR IRQ enumeration
 */
typedef enum {
  IRQ_BIT_SYNC_DETECTED   = 0x00, /*!< Enables interrupt on BIT_SYNC_DETECTED_F flag */
  IRQ_FRAME_SYNC_COMPLETE = 0x01, /*!< Enables interrupt on FRAME_SYNC_COMPLETE_F flag */
  IRQ_FRAME_COMPLETE      = 0x02, /*!< Enables interrupt on FRAME_COMPLETE_F flag */
  IRQ_FRAME_VALID         = 0x03  /*!< Enables interrupt on FRAME_VALID_F flag */
} LPAWUR_IrqEnable;

/**
 * @brief  STM32WL3 LPAWUR STATUS enumeration
 */
typedef enum {
  BIT_SYNC_DETECTED_F   = 0x00, /*!< Preamble (= bit sync) has been detected, the content of the PAYLOAD_X registers is not yet	valid */
  FRAME_SYNC_COMPLETE_F = 0x01, /*!< Frame Sync has been detected, the content of the PAYLOAD_X registers is not yet valid */
  FRAME_COMPLETE_F      = 0x02, /*!< Frame (payload + CRC) received, the content of the PAYLOAD_X registers is valid */
  FRAME_VALID_F         = 0x03, /*!< Frame (payload + CRC) received without error (the CRC has been checked and is matching with the received CRC) */
  NO_STATUS             = 0x04  /*!< Frame (payload + CRC) received without error (the CRC has been checked and is matching with the received CRC) */
} LPAWUR_Status;

/**
 * @brief  STM32WL3 LPAWUR Frame Init structure definition
 */
typedef struct {
  TrecLoopAlgo TRecAlgoSel;         /*!< Timing recovery loop algorithm selection */
  uint8_t SlowClkCyclePerBitCnt;    /*!< The number of expected slow clock cycle per each manchester coded bit (default 16) */
  uint8_t PayloadLength;            /*!<  The number of data Bytes in the payload (decoded).
						      Only the values 1 (8bits) to 8 (64bits) included are supported, other values are not supported
						      and shall not be used.
						      Default value is 7 bytes / 56 bits */
  uint8_t SyncThr;                  /*!< Detection threshold when receiving the Frame sync (Manchester encoded). The frame sync
						      detection uses a correlator to detect the address.
						      - If FRAME_CONFIG0.SYNC_LENGTH=0, recommended threshold is 16 (0x10)
						      - If FRAME_CONFIG0.SYNC_LENGTH=1, recommended threshold is 32 (0x20)
						      Default value is 16 (0x10) */
  uint8_t SyncLength;             /*!< Frame sync pattern length:
						      - If the input signal sync_len=0 (default), a 8-bits frame sync is used, the Low word
						      (FRAME_CONFIG1.FRAME_SYNC_PATTERN_L) is describing the frame sync pattern
						      value (16 bits after encoding)
						      - If the input signal sync_len=1, a 16-bits frame sync is used, both Low
						      (FRAME_SYNC_CONFIG.FRAME_SYNC_PATTERN_L) and High
						      (FRAME_SYNC_CONFIG.FRAME_SYNC_PATTERN_H) words are storing the pattern
						      value (32 bits after encoding) */
  uint8_t PreambleThrCnt;         /*!< The number of transitions for preamble detection when receiving the Manchester encoded
                  preamble. Default value is 18 (0x12)*/
  FunctionalState PreambleEnable;   /*!< Preamble detection enable.
                  - If PREAMBLE_ENABLE = 1 (default value) the sync detection starts after the preamble found,
                  - If PREAMBLE_ENABLE = 0, the sync detection starts when the LPAWUR_rx is enabled*/
  uint8_t FrameSyncCntTimeout;    /*!< The timeout in Manchester encoded bits for the Frame Sync.
                  It represents the number of samples after which a sync_error is raised if the frame sync is not detected.
						      The default value is 70 (0x46)*/
  uint16_t FrameSyncPattenHigh;  /*!<  The value of the frame sync pattern, High word, Manchester encoded, used only when the
                  frame sync length is 32 bits (default 0x0000)*/
  uint16_t FrameSyncPatternLow;  /*!< The value of the frame sync pattern, Low word, Manchester encoded, used both when the
                  frame sync length is 16 bits and 32 bits (default 0x9696 which represent a frame sync value of 0x99)*/
  uint8_t KpGain;  /*!< kp gain value for the timing recovery loop */
  uint8_t KiGain;  /*!< ki gain value for the timing recovery loop. */

}SLPAWUR_FrameInit;

/**
 * @brief  STM32WL3 LPAWUR RF Config structure definition
 */
typedef struct {
  EdIcal            EnergyDetectorIcal;   /*!< Current versus VBAT calibration for ED*/
  uint8_t           ClockDivider;         /*!< Calibrate the 4kHz clock (programmable divider)*/
  FunctionalState   EnergyDetectorSwitch; /*!< Energy Detector as input switch (test mode) deactivated by default*/
  AgcResetMode      AgcResetMode;         /*!< The AGC reset behavior when the AGC is working in ON or HOLD mode
                          0x0: reset the AGC after the complete frame detection (default)
                          0x1: the AGC is never reset */
  AgcHoldType       AgcHoldMode;          /*!< The behavior when the AGC is ON and is working in HOLD mode
                          0x0: hold after the preamble detection (default)
                          0x1: hold after the sync detection */
  AgcMode           AgcMode;              /*!< Define the working mode of the AGC:
                          0x0: AGC MAX (default value) : the AGC is ON and is always operating at maximum value
                          0x1: AGC OFF: the AGC is OFF
                          0x2: AGC ON : the AGC is ON
                          0x3: AGC HOLD: the AGC is ON and its value is frozen during the LPAWUR frame detection,
                          depending of the AGC_HOLD_MODE configuration after a preamble or after the frame sync. */
  AgcHighLevel     AgcHiLvl;              /*!< Define the AGC level (High) */
  FunctionalState  DCCurrentSubtraction;  /*!< DC current subtraction enabling signal */
  AgcLowLevel      AgcLoLvl;              /*!< Define the AGC level (Low) */
}SLPAWUR_RFConfig;

/**
 * @brief  STM32WL3 LPAWUR RF version structure definition
 */
typedef struct {
  uint8_t   revision; /*!< Revision of the RFIP (to be used for metal fixes)*/
  uint8_t   version;  /*!< Version of the RFIP (to be used for cut upgrades)*/
  uint8_t   product;  /*!< Used for major upgrades (new protocols support / new features)*/
} SLPAWUR_Version;

/**
  * @}
  */

/** @defgroup LPAWUR_Exported_Functions LPAWUR Exported Functions
  * @{
  */
void HAL_LPAWUR_IRQ_Callback(void);
void HAL_LPAWUR_IRQHandler(void);

void HAL_LPAWUR_RFConfigInit(SLPAWUR_RFConfig* pxSLPAWUR_RFConfigStruct);
SLPAWUR_RFConfig HAL_LPAWUR_GetRFConfig(void);
void HAL_LPAWUR_FrameInit(SLPAWUR_FrameInit* pxSLPAWUR_FrameInitStruct);
SLPAWUR_FrameInit HAL_LPAWUR_GetFrameInfo(void);
void HAL_LPAWUR_IrqConfig(LPAWUR_IrqEnable IrqEnable);
LPAWUR_Status HAL_LPAWUR_GetStatus(void);
void HAL_LPAWUR_ClearStatus(void);
void HAL_LPAWUR_SetSync(uint32_t sync);
uint32_t HAL_LPAWUR_GetSync(void);
void HAL_LPAWUR_GetPayload(uint8_t* buff);
SLPAWUR_Version HAL_LPAWUR_GetVersion(void);
void HAL_LPAWUR_MspInit(void);
void HAL_LPAWUR_MspDeInit(void);

/**
  * @}
  */

/**
  * @}
  */
#endif /* LPAWUR */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WL3x_HAL_LPAWUR_H */
