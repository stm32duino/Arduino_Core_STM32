/**
  ******************************************************************************
  * @file    stm32wl3x_hal_mrsubg.h
  * @author  GPM Application Team
  * @brief   Header file of MRSubG HAL module.
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
#ifndef STM32WL3x_HAL_MRSUBG_H
#define STM32WL3x_HAL_MRSUBG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_ll_mrsubg.h"
#include "stm32wl3x_hal_pwr.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @addtogroup MRSUBG
  * @{
  */

/** @defgroup MRSUBG_Private_Constants MRSUBG Private Constants
  * @{
  */
#define GAIN_RX_CHAIN 64

#define CHANNEL_FILTER_THRESHOLD 400000U
#define IF_FREQ_HIGH        600U
#define IF_FREQ_LOW         300U
#define SLOW_CLOCK_FREQ_DEFAULT 32000U

#define WMBUS_PREAMBLE_LEN_S1S2LONGHEADER           (uint16_t)279
#define WMBUS_PREAMBLE_LEN_S1MS2T2OTHERTOMETER      (uint16_t)15
#define WMBUS_PREAMBLE_LEN_T1T2METERTOOTHER         (uint16_t)19
#define WMBUS_PREAMBLE_LEN_R2                       (uint16_t)39
#define WMBUS_PREAMBLE_LEN_N1N2                     (uint16_t)8

#define WMBUS_SYNC_LEN_S1S2LONGHEADER               (uint8_t)17
#define WMBUS_SYNC_LEN_S1MS2T2OTHERTOMETER          (uint8_t)17
#define WMBUS_SYNC_LEN_T1T2METERTOOTHER             (uint8_t)9
#define WMBUS_SYNC_LEN_R2                           (uint8_t)17
#define WMBUS_SYNC_LEN_N1N2                         (uint16_t)15

#define WMBUS_SYNCWORD_S1S2LONGHEADER           (uint32_t)0x1DA58000
#define WMBUS_SYNCWORD_S1MS2T2OTHERTOMETER      (uint32_t)0x1DA58000
#define WMBUS_SYNCWORD_T1T2METERTOOTHER         (uint32_t)0x0F400000
#define WMBUS_SYNCWORD_R2                       (uint32_t)0x1DA58000
#define WMBUS_SYNCWORD_N1N2                     (uint32_t)0xF68D0000

/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/


/** @defgroup MRSUBG_Exported_Macros MRSUBG Exported Macros
  * @{
  */

/**
  * @brief Send a specific command to the STM32WL3x.
  * @param __CMD_NAME__ code of the command to send.
  * @retval None.
  */
#define __HAL_MRSUBG_STROBE_CMD(__CMD_NAME__)           LL_MRSubG_StrobeCommand(__CMD_NAME__)

/**
  * @brief Sets the RX_MODE for the MRSUBG.
  * @param __MODE__ the rx mode
  *        This parameter can be any of the following values:
  *            @arg @ref RX_NORMAL             Only payload is stored into the RAM buffers. CRC and packet length
  *                                           are readable in dedicated status registers
  *            @arg @ref RX_DIRECT_BUFFERS     Full bit stream is stored into the RAM buffers.
  *            @arg @ref RX_DIRECT_GPIO        Full bit stream is provided serially through the RX DATA GPIO.
  *            @arg @ref RX_IQ_SAMPLING        Raw I/Q sampling taken at the output of the Channel filter inside
  *                                           the demodulator are stored in RAM.
  *            @arg @ref RX_FREQDETEC_SAMPLING Raw data taken at the output of the frequency detector inside
  *                                           the demodulator (detection of the instantaneous frequency changes)
  *                                           are stored in RAM.
  *            @arg @ref RX_SOFTBIT_SAMPLING   Raw data taken at the output of the post-filter inside the
  *                                           demodulator (soft bits before the 0/1 detection) are stored in RAM.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_RX_MODE(__MODE__)              LL_MRSubG_SetRXMode(__MODE__)

/**
  * @brief Sets the TX_MODE for the MRSUBG.
  * @param __MODE__ the tx mode
  *        This parameter can be any of the following values:
  *            @arg @ref TX_NORMAL          Only payload is provided through RAM buffers. Rest of the frame
  *                                       built from configuration registers (PREAMBLE, SYNC, CRC...).
  *            @arg @ref TX_DIRECT_BUFFERS  Full bit stream (including PREAMBLE, SYNC, CRC...) to be provided
  *                                       through RAM buffers.
  *            @arg @ref TX_DIRECT_GPIO     Full bit stream (including PREAMBLE, SYNC, CRC...) to be provided
  *                                       serially through the TX DATA GPIO.
  *            @arg @ref TX_PN              Internal PN generator sends a polynomial bit stream on the antenna.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_TX_MODE(__MODE__)              LL_MRSubG_SetTXMode(__MODE__)

/**
  * @brief Set the PCKTLEN field of the PCKTLEN_CONFIG register.
  * @param __P_LEN__ payload length in bytes.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_PKT_LEN(__P_LEN__)             LL_MRSUBG_SetPacketLength(__P_LEN__)

/**
  * @brief Set global configuration table for sequencer hardware.
  * @param __ARG__ Pointer to the global configuration table struct.
  * @retval None.
  */
#define __HAL_MRSUBG_SEQ_SET_GLOBAL_CONFIG(__ARG__)     LL_MRSubG_Sequencer_SetGlobalConfiguration(__ARG__)

/**
  * @brief Trigger sequencer, i.e., launch sequence of actions.
  * @retval None.
  */
#define __HAL_MRSUBG_SEQ_TRIGGER()                      LL_MRSubG_Sequencer_Trigger()

/**
  * @brief Set the size for the data buffer.
  * @param __SIZE__ the size of the data buffer.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_DATABUFFER_SIZE(__SIZE__)      \
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DATABUFFER_SIZE, MR_SUBG_GLOB_STATIC_DATABUFFER_SIZE_DATABUFFER_SIZE, __SIZE__)

/**
  * @brief  Get the size of the data buffer.
  * @retval The size of the data buffer.
  */
#define __HAL_MRSUBG_GET_DATABUFFER_SIZE()              READ_REG(MR_SUBG_GLOB_STATIC->DATABUFFER_SIZE)

/**
  * @brief  Get the number of bytes used in the last used DATA BUFFER.
  * @retval The number of bytes used in the last used DATA BUFFER.
  */
#define __HAL_MRSUBG_GET_DATABUFFER_COUNT()             \
  READ_REG_FIELD(MR_SUBG_GLOB_STATUS->DATABUFFER_INFO, MR_SUBG_GLOB_STATUS_DATABUFFER_INFO_CURRENT_DATABUFFER_COUNT)

/**
  * @brief  Set the pointer for data buffer 0.
  * @param  __ARG__ Pointer to be set for data buffer 0.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_DATABUFFER0_POINTER(__ARG__)   WRITE_REG(MR_SUBG_GLOB_STATIC->DATABUFFER0_PTR, __ARG__)

/**
  * @brief  Set the pointer for data buffer 1.
  * @param  __ARG__ Pointer to be set for data buffer 1.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_DATABUFFER1_POINTER(__ARG__)   WRITE_REG(MR_SUBG_GLOB_STATIC->DATABUFFER1_PTR, __ARG__)

/**
  * @brief  Get the RX indicator status.
  * @retval The RX indicator status.
  */
#define __HAL_MRSUBG_GET_RX_INDICATOR()                 READ_REG(MR_SUBG_GLOB_STATUS->RX_INDICATOR)

/**
  * @brief  Enable RF sequence IRQ with a given flag.
  * @param  __FLAG__ Flag to enable RF sequence IRQ.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_RFSEQ_IRQ_ENABLE(__FLAG__)     WRITE_REG(MR_SUBG_GLOB_DYNAMIC->RFSEQ_IRQ_ENABLE, __FLAG__)

/**
  * @brief  Get the RF sequence IRQ status.
  * @retval The RF sequence IRQ status.
  */
#define __HAL_MRSUBG_GET_RFSEQ_IRQ_STATUS()             READ_REG(MR_SUBG_GLOB_STATUS->RFSEQ_IRQ_STATUS)

/**
  * @brief  Clear the RF sequence IRQ flag with a given flag.
  * @param  __FLAG__ Flag to clear RF sequence IRQ.
  * @retval None.
  */
#define __HAL_MRSUBG_CLEAR_RFSEQ_IRQ_FLAG(__FLAG__)     WRITE_REG(MR_SUBG_GLOB_STATUS->RFSEQ_IRQ_STATUS, __FLAG__)

/**
  * @brief  Get detailed RF sequence status.
  * @retval The detailed RF sequence status.
  */
#define __HAL_MRSUBG_GET_RFSEQ_STATUS_DETAIL()          READ_REG(MR_SUBG_GLOB_STATUS->RFSEQ_STATUS_DETAIL)

/**
  * @brief  Set detailed RF sequence status with a given argument.
  * @param  __ARG__ Argument to set detailed RF sequence status.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_RFSEQ_STATUS_DETAIL(__ARG__)   WRITE_REG(MR_SUBG_GLOB_STATUS->RFSEQ_STATUS_DETAIL, __ARG__)

/**
  * @brief  Set the RX timeout with a given timeout value.
  * @param  __TIMEOUT__ Timeout value to set for RX.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_RX_TIMEOUT(__TIMEOUT__)        \
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_TIMEOUT, __TIMEOUT__)

/**
  * @brief  Set the fast RX timeout with a given timeout value.
  * @param  __TIMEOUT__ Timeout value to set for fast RX.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_FAST_RX_TIMEOUT(__TIMEOUT__)   \
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->FAST_RX_TIMER, MR_SUBG_GLOB_DYNAMIC_FAST_RX_TIMER_FAST_RX_TIMEOUT, __TIMEOUT__)

/**
  * @brief  Set the wakeup offset with a given offset value.
  * @param  __OFFSET__ Offset value to set for wakeup.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_WAKEUP_OFFSET(__OFFSET__)      \
  MODIFY_REG_FIELD(MR_SUBG_GLOB_RETAINED->WAKEUP_CTRL, MR_SUBG_GLOB_RETAINED_WAKEUP_CTRL_SOC_WAKEUP_OFFSET, __OFFSET__)

/**
  * @brief  Enable CS blanking.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_CS_BLANKING()                  \
  SET_BIT(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_AS_CS_BLANKING)

/**
  * @brief  Clear CS blanking.
  * @retval None.
  */
#define __HAL_MRSUBG_CLEAR_CS_BLANKING()                \
  CLEAR_BIT(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_AS_CS_BLANKING)

/**
  * @brief  Set the PQI threshold with a given threshold value.
  * @param  __THRVAL__ The threshold level.
  * @retval None.
  */
#define __HAL_MRSUBG_SET_PQI_THRESHOLD(__THRVAL__)      \
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_PQI_THR, __THRVAL__)

/**
  * @brief  Set the SQI threshold with a given threshold value.
  * @param  __THRVAL__ Threshold value of type @ref SQI_Threshold.
  * @retval None
  */
#define __HAL_MRSUBG_SET_SQI_THRESHOLD(__THRVAL__)  LL_MRSubG_SetSQIThreshold(__THRVAL__)

/**
  * @brief  Get the SQI threshold value.
  * @retval Threshold value of type @ref SQI_Threshold.
  */
#define __HAL_MRSUBG_GET_SQI_THRESHOLD()  LL_MRSubG_GetSQIThreshold()

/**
  * @brief  Enable WMBUS and SQI mask.
  * @retval None.
  */
#define __HAL_MRSUBG_WMBUS_ENABLE_AND_SQI_MASK()        \
  {                                                       \
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_OR_nAND_SELECT); \
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_SQI_TIMEOUT_MASK); \
  }

/**
  * @brief  Get the IF offset digital value.
  * @retval The IF offset digital value.
  */
#define __HAL_MRSUBG_GET_IF_OFFSET_DIG()                \
  READ_REG_FIELD(MR_SUBG_GLOB_STATIC->IF_CTRL, MR_SUBG_GLOB_STATIC_IF_CTRL_IF_OFFSET_DIG)

/**
  * @brief  Get the RSSI level in dBm.
  * @retval The RSSI level to convert.
  */
#define __HAL_MRSUBG_CONVERT_RSSI_TO_DBM(__VALUE__)       (__VALUE__/2)-(96+GAIN_RX_CHAIN)

/**
  * @}
  */


/** @defgroup MRSUBG_Exported_Types MRSUBG Exported Types
  * @{
  */

/**
  * @brief  STM32WL3x Modulation enumeration
  */
typedef enum
{
  MOD_2FSK       = 0x00, /*!< 2-FSK modulation selected */
  MOD_4FSK       = 0x01, /*!< 4-FSK modulation selected */
  MOD_2GFSK05    = 0x12, /*!< 2GFSK modulation selected with BT = 0.5 */
  MOD_2GFSK1     = 0x02, /*!< 2GFSK modulation selected with BT = 1 */
  MOD_4GFSK05    = 0x13, /*!< 4GFSK modulation selected with BT = 0.5 */
  MOD_4GFSK1   = 0x03, /*!< 4GFSK modulation selected with BT = 1 */
  MOD_ASK        = 0x05, /*!< ASK modulation selected. */
  MOD_OOK        = 0x05, /*!< OOK modulation selected. */
  MOD_POLAR      = 0x06, /*!< Polar modulation selected. */
  MOD_CW         = 0x07, /*!< CW modulation selected */
} MRSubGModSelect;

/**
  * @brief  STM32WL3x selection of the PRBS polynomial
  */
typedef enum
{
  PN9   = 0x00, /* x^9 +x^5 + 1 with the initial state equal to 0x1FF. */
  PN15  = 0x01, /* x^15 +x^14 + 1 with the initial state equal to 0x7FFF. */
} MRSubG_PN_SEL;

/**
  * @brief  STM32WL3x Time Capture selection trigger
  */
typedef enum
{
  TC_SEL_DISABLE     = 0x00, /*!< The feature is disabled, no time capture will occur. */
  TC_SEL_END_OF_TX   = 0x01, /*!< The interpolated absolute time is latched on end of transmission information. */
  TC_SEL_END_OF_RX   = 0x02, /*!< The interpolated absolute time is latched on end of reception information
                                  whatever the CRC result (RX OK or CRC error). */
  TC_SEL_SYNC_DETECT = 0x03, /*!< The interpolated absolute time is latched on the SYNC word detection event. */
} MRSubG_TimeCaptureSel;


/**
  * @brief  STM32WL3x AFC reinitialization option to improve the AFC behavior on frames
  *         with PREAMBLE smaller than 64 bits
  */
typedef enum
{
  AFC_REINIT_NONE       = 0x00, /*!< No reinitialization allowed. */
  AFC_REINIT_RSSI       = 0x01, /*!< Reinitialization based on RSSI ramping. */
  AFC_REINIT_FDEV       = 0x02, /*!< Reinitialization based on abnormal Fdev. */
  AFC_REINIT_RSSI_FDEV  = 0x03, /*!< Reinitialization based on both RSSI and abnormal Fdev. <- DEFAULT */
} MRSubG_AFCReinit;


/**
  * @brief  STM32WL3x Basic Packet Init structure definition.
  */
typedef enum
{
  PKT_BASIC   = 0,
  PKT_802_15_4  = 1
} MRSubG_PcktType;

/**
  * @brief  WMbus submode enumeration.
  */
typedef enum
{
  WMBUS_SUBMODE_NOT_CONFIGURED            = 0,   /*!< WMBUS submode S1, S2 (long header) - Header length = WMBUS_prmbl_ctrl + 279 (in "01" bit pairs) , Sync word = 0x7696 (length 18 bits) */
  WMBUS_SUBMODE_S1_S2_LONG_HEADER,               /*!< WMBUS submode S1, S2 (long header) - Header length = WMBUS_prmbl_ctrl + 279 (in "01" bit pairs) , Sync word = 0x7696 (length 18 bits) */
  WMBUS_SUBMODE_S1_M_S2_T2_OTHER_TO_METER,       /*!< WMBUS submode S1-m, S2, T2 (other to meter) - Header length = WMBUS_prmbl_ctrl + 15 (in "01" bit pairs) , Sync word = 0x7696 (length 18 bits)*/
  WMBUS_SUBMODE_T1_T2_METER_TO_OTHER,            /*!< WMBUS submode T1, T2 (meter to other) - Header length = WMBUS_prmbl_ctrl + 19 (in "01" bit pairs) ,  Sync word = 0x3D (length 10 bits)*/
  WMBUS_SUBMODE_R2_SHORT_HEADER,                 /*!< WMBUS submode R2, short header - Header length = WMBUS_prmbl_ctrl + 39 (in "01" bit pairs) , Sync word = 0x7696 (length 18 bits)*/
} WMbusSubmode;

/**
  * @brief  STM32WL3x MRSUBG Radio Config structure definition
  */
typedef struct
{
  uint32_t          lFrequencyBase;     /*!< Specifies the base carrier frequency (in Hz) */
  MRSubGModSelect   xModulationSelect;  /*!< Specifies the modulation @ref MRSubGModSelect */
  uint32_t          lDatarate;          /*!< Specifies the datarate expressed in sps.*/
  uint32_t          lFreqDev;           /*!< Specifies the frequency deviation expressed in Hz. */
  uint32_t          lBandwidth;         /*!< Specifies the channel filter bandwidth expressed in Hz. */
  uint8_t           dsssExp;            /*!< Specifies the DSSS spreading exponent. Use 0 to disable DSSS. */
  int8_t           outputPower;         /*!< PA value to write expressed in dBm. */
  MRSubG_PA_DRVMode PADrvMode;          /*!< PA drive mode. */
} SMRSubGConfig_t;


/**
  * @brief  STM32WL3x MRSUBG RF version structure definition
  */
typedef struct
{
  uint8_t       revision;       /*!< Revision of the RFIP (to be used for metal fixes)*/
  uint8_t       version;        /*!< Version of the RFIP (to be used for cut upgrades)*/
  uint8_t       product;        /*!< Used for major upgrades (new protocols support / new features)*/
} SMRSubGVersion_t;

/**
  * @brief  STM32WL3x Basic Packet Init structure definition.
  */
typedef struct
{
  uint16_t    PreambleLength;         /*!< Set the preamble length of packet in pairs of bits (0 to 2046) */
  uint16_t    PostambleLength;  /*!< Set the postable length of packet. The number of POSTAMBLE pairs of bits can be set from 0 to 63. */
  uint8_t   SyncLength;             /*!< Set the sync word length of packet in bits. From 1 to 64 bits. */
  uint32_t    SyncWord;               /*!< Set the sync words in MSB. */
  MRSubG_LengthMode FixVarLength;           /*!< Enable the variable length mode. */
  MRSubG_PreambleSeq  PreambleSequence; /*!< Select the PREAMBLE pattern to be applied. */
  MRSubG_PostambleSeq PostambleSequence;  /*!< Packet postamble control: postamble bit sequence selection. */
  MRSubG_PcktCrcMode  CrcMode;                /*!< Set the CRC type. @ref MRSubG_PcktCrcMode */
  MRSubG_PcktCoding     Coding;     /*!< Enable the FEC/Viterbi. */
  FunctionalState DataWhitening;          /*!< Enable the data whitening. */
  MRSubG_LenWidthhMode  LengthWidth;    /*!< Set the length width. this bit field is considered/relevant only if FIX_VAR_LEN=1 */
  FunctionalState       SyncPresent;    /*!< ndicate if a SYNC word is present on the frame or not (null length) */
} MRSubG_PcktBasicFields_t;

/**
  * @brief  STM32WL3x WMBUS Packet Init structure definition.
  */
typedef struct
{
  WMbusSubmode  xWMbusSubmode;          /*!< Set the WMBUS submode. @ref WMbusSubmode */
  uint16_t      PreambleLength;         /*!< Set the preamble length of packet. From 1 to 2046 bit. */
  uint16_t      PostambleLength;  /*!< Set the postable length of packet. From 1 to 126 bit. */
} MRSubG_WMBUS_PcktFields_t;

/**
  * @brief  STM32WL3x 802.15.4 FEC encoding types.
  */
typedef enum
{
  FEC_15_4_G_NONE           = 0,
  FEC_15_4_G_NRNSC          = 1,
  FEC_15_4_G_RSC          = 2,
  FEC_15_4_G_RSC_Interleaving   = 3
} MRSubG_FEC15_4gType;

/**
  * @brief  STM32WL3x 802.15.4 Packet Init structure definition.
  */
typedef struct
{
  MRSubGModSelect Modulation;           /*!< Enumerated value as follow:
                                          - 0: MOD_2FSK
                                          - 1: MOD_4FSK */
  uint8_t  PreambleLength;              /*!< number of times the standard preamble sequence shall be repeated.
                                        The standard preamble sequence is "01010101" for 2-FSK
                                        and "0111011101110111" for 4-FSK. From 4 to 64. */
  MRSubG_PcktCrcMode FCSType;           /*!< Enumerated value as follow:
                                          - 0: FCS_32BIT CRC mode5
                                          - 1: FCS_16BIT CRC mode3 */
  FunctionalState       Whitening;      /*!< Enable the data whitening. */
  MRSubG_FEC15_4gType   FecType;  /*!< FEC type for 802.15.4g */
  uint16_t            FrameLength;  /*!< size of payload + FCS, in bytes */
} MRSubG_802_15_4_PcktFields_t;


/**
  * @}
  */

/** @defgroup MRSUBG_Exported_Functions MRSUBG Exported Functions
  * @{
  */
void HAL_MRSubG_MspInit(void);
void HAL_MRSubG_MspDeInit(void);

void HAL_MRSubG_IRQ_Callback(void);
void HAL_MRSubG_BUSY_Callback(void);
void HAL_MRSubG_TX_RX_SEQUENCE_Callback(void);
void HAL_MRSubG_WKUP_Callback(void);
void HAL_MRSubG_IRQHandler(void);
void HAL_MRSubG_BUSY_IRQHandler(void);
void HAL_MRSubG_TX_RX_SEQUENCE_IRQHandler(void);
void HAL_MRSubG_WKUP_IRQHandler(void);

SMRSubGVersion_t HAL_MRSubGGetVersion(void);
uint8_t HAL_MRSubG_Init(SMRSubGConfig_t *pxSRadioInitStruct);
void HAL_MRSubG_GetInfo(SMRSubGConfig_t *pxSRadioInitStruct);
void HAL_MRSubG_SetFrequencyBase(uint32_t lFBase);
uint32_t HAL_MRSubG_GetFrequencyBase(void);
void HAL_MRSubG_SetDatarate(uint32_t lDatarate);
uint32_t HAL_MRSubG_GetDatarate(void);
void HAL_MRSubG_SetFrequencyDev(uint32_t lFDev);
uint32_t HAL_MRSubG_GetFrequencyDev(void);
void HAL_MRSubG_SetChannelBW(uint32_t lBandwidth);
uint32_t HAL_MRSubG_GetChannelBW(void);
void HAL_MRSubG_SetModulation(MRSubGModSelect xModulation, uint8_t dsssExponent);
MRSubGModSelect HAL_MRSubG_GetModulation(void);
int32_t HAL_MRSubG_GetRssidBm(void);
void HAL_MRSubG_SetRSSIThreshold(int16_t rssiTh);
int32_t HAL_MRSubG_GetRSSIThreshold(void);
void HAL_MRSubG_SetPALeveldBm(uint8_t cIndex, int8_t lPowerdBm, MRSubG_PA_DRVMode drvMode);
int8_t HAL_MRSubG_GetPALeveldBm(void);
uint32_t HAL_MRSubG_GetBytesOfTransaction(void);
uint32_t HAL_MRSubG_Sequencer_Microseconds(uint32_t microseconds);
uint32_t HAL_MRSubG_Sequencer_Milliseconds(uint32_t milliseconds);
uint32_t HAL_MRSubG_Sequencer_Seconds(uint32_t seconds);
ErrorStatus HAL_MRSubG_Sequencer_ApplyStaticConfig(MRSubG_Sequencer_GlobalConfiguration_t *cfg);
ErrorStatus HAL_MRSubG_Sequencer_ApplyDynamicConfig(MRSubG_Sequencer_ActionConfiguration_t *cfg, MRSubGCmd cmd);
void HAL_MRSubG_PktBasicSetPayloadLength(uint16_t nPayloadLength);
void HAL_MRSubG_PacketBasicInit(MRSubG_PcktBasicFields_t *pxPktBasicInit);
void HAL_MRSubG_WMBus_PacketInit(MRSubG_WMBUS_PcktFields_t *pxPktWMbusInit);
void HAL_MRSubG_802_15_4_PacketInit(MRSubG_802_15_4_PcktFields_t *px802_15_4PktInit);

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

#endif /* STM32WL3x_HAL_MRSUBG_H */
