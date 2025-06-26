/**
  ******************************************************************************
  * @file    stm32wb0x_hal_radio.h
  * @author  GPM WBL Application Team
  * @brief   Header file of RADIO module.
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
#ifndef STM32WB0x_HAL_RADIO_H
#define STM32WB0x_HAL_RADIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal_def.h"
#include "stm32wb0x_ll_radio.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @addtogroup RADIO
  * @{
  */

/** @defgroup RADIO_Exported_Types RADIO Exported Types
  * @{
  */

/**
  * @brief  RADIO Handle Structure definition
  */
typedef struct
{
  BLUE_TypeDef                 *Instance;  /*!< Register base address    */
} RADIO_HandleTypeDef;


#if USE_RADIO_PROPRIETARY_DRIVER

typedef struct ActionPacket ActionPacket;

struct ActionPacket
{
  uint8_t StateMachineNo;       /* This parameter indicates the state machine number for this action. From 0 to 7. */
  uint8_t ActionTag;            /* The action tags are: PLL_TRIG TXRX TIMER_WAKEUP
                                    WHITENING_DISABLE INC_CHAN TIMESTAMP_POSITION RELATIVE */
  uint8_t MaxReceiveLength;     /* Maximum size of received payload. Applicable only for RX actions. */
  uint32_t WakeupTime;          /* Contains the wakeup time in microsecond if it is relative.
                                 * If it is absolute it must be expressed in System Time (STU). */
  uint8_t *data;                /* Pointer to the array with the data to send (header, length and data field), for TX.
                                 * Pointer to the array where the data received are copied, for RX.
                                 * In case of RX, the array must have the max size MAX_PACKET_LENGTH. */
  uint32_t status;              /* The Status Register with the information on the action. */
  uint32_t timestamp_receive;   /* This field contains the timestamp when a packet is received.
                                 * Intended to be used in the dataRoutine() callback routine. RX only. */
  int32_t rssi;                 /* The rssi of the packet was received with. RX only. */
  BlueTransStruct trans_packet; /* This is a linked list, which is going to be used by Hardware.
                                  * User does not need to do anything. */
  ActionPacket *next_true;      /* Pointer to next ActionPacket if condRoutine() returns TRUE */
  ActionPacket *next_false;     /* Pointer to next ActionPacket if condRoutine() returns FALSE */
  uint8_t (*condRoutine)(ActionPacket *);        /* User callback that decide the next ActionPacket to use.
                                                 * It is time critical. Routine must end within 45 us. */
  uint8_t (*dataRoutine)(ActionPacket *, ActionPacket *); /* User callback for managing data. */
  uint8_t trans_config;         /* To configure the device for TX or RX. User does not need to do anything. */
};


typedef struct
{
  uint32_t back2backTime;
  uint8_t tone_start_stop_flag;
  ActionPacket *current_action_packet;
} RadioGlobalParameters_t;


typedef struct
{
  int32_t rssi;
  uint32_t timestamp_receive;
} RxStats_t;

#endif /* USE_RADIO_PROPRIETARY_DRIVER */


/**
  * @}
  */


/** @defgroup RADIO_Exported_Functions RADIO Exported Functions
  * @{
  */

void HAL_RADIO_Init(RADIO_HandleTypeDef *hradio);

void HAL_RADIO_TXRX_IRQHandler(void);

void HAL_RADIO_TXRX_SEQ_IRQHandler(void);

void HAL_RADIO_TxRxCallback(uint32_t flags);

void HAL_RADIO_TxRxSeqCallback(void);

int8_t HAL_RADIO_ReadRSSI(void);

void HAL_RADIO_MspInit(RADIO_HandleTypeDef *hradio);
void HAL_RADIO_MspDeInit(RADIO_HandleTypeDef *hradio);

#if USE_RADIO_PROPRIETARY_DRIVER

uint8_t HAL_RADIO_GetStatus(uint32_t *time);
void HAL_RADIO_SetChannelMap(uint8_t StateMachineNo, uint8_t *chan_remap);
void HAL_RADIO_SetChannel(uint8_t StateMachineNo, uint8_t channel, uint8_t channel_increment);
void HAL_RADIO_SetTxAttributes(uint8_t StateMachineNo, uint32_t NetworkID, uint32_t crc_init);
void HAL_RADIO_SetMaxReceivedLength(uint8_t StateMachineNo, uint8_t MaxReceivedLength);
void HAL_RADIO_SetBackToBackTime(uint32_t back_to_back_time);
void HAL_RADIO_SetPhy(uint8_t StateMachineNo, uint8_t phy);
void HAL_RADIO_SetTxPower(uint8_t PowerLevel);
uint8_t HAL_RADIO_StopActivity(void);
void HAL_RADIO_SetGlobalReceiveTimeout(uint32_t ReceiveTimeout);
void HAL_RADIO_SetReservedArea(ActionPacket *p);
uint8_t HAL_RADIO_MakeActionPacketPending(ActionPacket *p);
uint8_t HAL_RADIO_StartTone(uint8_t RF_channel, uint8_t powerLevel, uint8_t freq_offset);
uint8_t HAL_RADIO_StopTone(void);
void HAL_RADIO_SetEncryptionCount(uint8_t StateMachineNo, uint8_t *count_tx, uint8_t *count_rcv);
void HAL_RADIO_SetEncryptionAttributes(uint8_t StateMachineNo, uint8_t *enc_iv, uint8_t *enc_key);
void HAL_RADIO_SetEncryptFlags(uint8_t StateMachineNo, FunctionalState EncryptFlagTx, FunctionalState EncryptFlagRcv);
void HAL_RADIO_EncryptPlainData(uint8_t *Key, uint8_t *plainData, uint8_t *cypherData);
void HAL_RADIO_SetDefaultPreambleLen(uint8_t StateMachineNo);
void HAL_RADIO_SetPreambleRep(uint8_t StateMachineNo, uint8_t PreaLen);
void HAL_RADIO_DisableCRC(uint8_t StateMachineNo, FunctionalState hwCRC);
uint8_t HAL_RADIO_SetNetworkID(uint32_t ID);
uint8_t HAL_RADIO_CarrierSense(uint8_t channel, int8_t *rssi);
uint8_t HAL_RADIO_Callback(ActionPacket *p, ActionPacket *next);

void HAL_RADIO_CallbackRcvError(RxStats_t *rxPacketStats);
void HAL_RADIO_CallbackRcvTimeout(RxStats_t *rxPacketStats);
void HAL_RADIO_CallbackRcvEncryptErr(RxStats_t *rxPacketStats);
void HAL_RADIO_CallbackRcvOk(RxStats_t *rxPacketStats);
void HAL_RADIO_CallbackTxDone(void);

uint8_t HAL_RADIO_SendPacket(uint8_t channel, uint32_t wakeup_time, uint8_t *txBuffer,
                             uint8_t (*Callback)(ActionPacket *, ActionPacket *));

uint8_t HAL_RADIO_SendPacketWithAck(uint8_t channel, uint32_t wakeup_time, uint8_t *txBuffer, uint8_t *rxBuffer,
                                    uint32_t receive_timeout, uint8_t receive_length,
                                    uint8_t (*Callback)(ActionPacket *, ActionPacket *));

uint8_t HAL_RADIO_ReceivePacket(uint8_t channel, uint32_t wakeup_time, uint8_t *rxBuffer, uint32_t receive_timeout,
                                uint8_t receive_length,
                                uint8_t (*Callback)(ActionPacket *, ActionPacket *));

uint8_t HAL_RADIO_ReceivePacketWithAck(uint8_t channel, uint32_t wakeup_time, uint8_t *rxBuffer, uint8_t *txBuffer,
                                       uint32_t receive_timeout, uint8_t receive_length,
                                       uint8_t (*Callback)(ActionPacket *, ActionPacket *));

#endif /* USE_RADIO_PROPRIETARY_DRIVER */

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

#endif /* STM32WB0x_HAL_RADIO_H */
