/**
  ******************************************************************************
  * @file    stm32wb0x_hal_radio.c
  * @author  GPM WBL Application Team
  * @brief   This file provides all the Radio Driver APIs.
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
#include "stm32wb0x_hal.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */
#ifdef HAL_RADIO_MODULE_ENABLED

/** @addtogroup RADIO
  * @{
  */

/** @defgroup RADIO_Private_Constants RADIO Private Constants
  * @{
  */

#define RSSI_OFFSET 119

/* Access address used only to sense medium with HAL_RADIO_CarrierSense() */
#define FAKE_NETWORK_ID 0xAAAAAAAA

#define VALIDITY_TAG 0xFCBCECCC
#define VALIDITY_LOCATION    0x10001EF8
#define MR_TRIMMING_LOCATION 0x10001EE8

#define MR_BLE_IBIAS_TRIM_Pos         (8)
#define MR_BLE_IBIAS_TRIM_Msk         (0x0F << MR_BLE_IBIAS_TRIM_Pos)
#define MR_BLE_IPTAT_TRIM_Pos         (12)
#define MR_BLE_IPTAT_TRIM_Msk         (0x0F << MR_BLE_IPTAT_TRIM_Pos)
#define MR_BLE_VBG_TRIM_Pos           (16)
#define MR_BLE_VBG_TRIM_Msk           (0x0F << MR_BLE_VBG_TRIM_Pos)
#define MR_BLE_RXADC_DELAY_I_TRIM_Pos (20)
#define MR_BLE_RXADC_DELAY_I_TRIM_Msk (0x07 << MR_BLE_RXADC_DELAY_I_TRIM_Pos)
#define MR_BLE_RXADC_DELAY_Q_TRIM_Pos (24)
#define MR_BLE_RXADC_DELAY_Q_TRIM_Msk (0x07 << MR_BLE_RXADC_DELAY_Q_TRIM_Pos)

/* AFC Configuration */
#define AFC_DELAY_BEFORE    (0x05)
#define AFC_DELAY_AFTER     (0x05)
#define CR_GAIN_BEFORE      (0x06)
#define CR_GAIN_AFTER       (0x06)
#define CR_LR_GAIN_BEFORE   (0x05)
#define CR_LR_GAIN_AFTER    (0x05)
#define LR_RSSI_THR         (0x1D)
#define LR_PD_THR           (0x59)
#define LR_AAC_THR          (0x32)

/* Fine tuning values for antenna switching and IQ samplig */
#define RX_TIME_TO_SAMPLE   (0x1F)
#define RX_TIME_TO_SWITCH   (0x09)

/** @defgroup Sequencer_timeouts Sequencer Timeouts
  * @{
  */

/* initDelay */
#define INITDELAY_WAKEUP          (0x40U)
#define INITDELAY_TIMER12_CAL     (0x3FU)
#define INITDELAY_TIMER2_NOCAL    (0x9U)

/* Init_radio_delay */
#if defined (STM32WB05) || defined(STM32WB09 )
#define DELAYCHK_TRANSMIT_CAL     (0x5AU)
#define DELAYCHK_TRANSMIT_NOCAL   (0x32U)
#define DELAYCHK_RECEIVE_CAL      (0x5AU)
#define DELAYCHK_RECEIVE_NOCAL    (0x32U)
#endif
#if defined (STM32WB06) || defined (STM32WB07)
#define DELAYCHK_TRANSMIT_CAL     (0x76U)
#define DELAYCHK_TRANSMIT_NOCAL   (0x3AU)
#define DELAYCHK_RECEIVE_CAL      (0x74U)
#define DELAYCHK_RECEIVE_NOCAL    (0x38U)
#endif

/* ConfigEndDuration */
#define CONFIG_END_DURATION       (0x14U)

/* DataInit phase start */
#define CHECK_TXDATAREADY         (0x5U)

/* TX parameters init */
#if defined (STM32WB05) || defined(STM32WB09 )
#define TXREADY_TIMEOUT          (0x4U)
#endif
#if defined (STM32WB06) || defined(STM32WB07)
#define TXREADY_TIMEOUT          (0x5U)
#endif
#define TXDELAY_START            (0x10U)
#define TXDELAY_END              (0x10U)

/* RX parameter init */
#define RCV_TIMEOUT              (0x100)

/* Number of state machine used */
#define STATEMACHINE_COUNT   (CFG_NUM_RADIO_TASKS)
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup RADIO_Private_Macros RADIO Private Macros
  * @{
  */
#define IS_STATE_VALID(STATEMACHINE_NO) (STATEMACHINE_NO < STATEMACHINE_COUNT)
#define IS_POWERLEVEL_VALID(POWER) (POWER < 0x20)
#define IS_RFCHANNEL_VALID(RF_CHANNEL) (RF_CHANNEL <40)
#define IS_FREQOFFSET_VALID(FREQ_OFFSET) (FREQ_OFFSET >2)
#define IS_PHY_VALID(PHY) (PHY==PHY_1M || PHY==PHY_2M || PHY==PHY_CODED_S_2 || PHY==PHY_CODED_S_8)
#define IS_PREALEN_VALID(PREA) (PREA < 16)


#define MASK_INTERRUPTS() __disable_irq();
#define UNMASK_INTERRUPTS() __enable_irq();


#define TIME_DIFF(a, b)       ((int32_t)(a - b))
/**
  * @}
  */

/** @defgroup RADIO_Private_Variables RADIO Private Variables
  * @{
  */

#if USE_RADIO_PROPRIETARY_DRIVER

RadioGlobalParameters_t globalParameters;

static ActionPacket aPacket[2];
static uint32_t networkID = 0x88DF88DF;

#endif /* USE_RADIO_PROPRIETARY_DRIVER */

/**
  * @}
  */

/** @defgroup RADIO_Private_Functions RADIO Private Functions
  * @{
  */

#if USE_RADIO_PROPRIETARY_DRIVER

static uint8_t CondRoutineTrue(ActionPacket *p)
{
  return TRUE;
}

static uint8_t DataRoutineNull(ActionPacket *current_action_packet, ActionPacket *next)
{
  return TRUE;
}

static uint8_t CondRoutineRxTrue(ActionPacket *p)
{
  /* received a packet */
  if ((p->status & BLUE_INTERRUPT1REG_RCVOK) != 0)
  {
    /* packet received without CRC error */
    return TRUE;
  }
  return FALSE;
}

#endif /* USE_RADIO_PROPRIETARY_DRIVER */


/**
  * @}
  */

/** @defgroup RADIO_Global_Variables RADIO Global Variables
  * @{
  */

/* ------------------------------------------------------------------------------
*  volatile uint32_t hot_table_radio_config_u32[]
*
*  Hot table radio configuration storage.
*  This variable is only used during the smart power management
*  procedure
*  ------------------------------------------------------------------------------ */
/* Round up HOT_TABLE_SIZE to an integer number of words then add 4 words for table management pointers */
volatile uint32_t hot_table_radio_config_u32[((HOT_TABLE_SIZE + 3) >> 2) + 4] = {0x00};

/* BLUE RAM, reserved for radio communication. Not usable from the application */
__SECTION(".bss.__blue_RAM")
__REQUIRED(uint8_t __blue_RAM[CFG_NUM_RADIO_TASKS * sizeof(STATMACH_TypeDef) + sizeof(GLOBALSTATMACH_TypeDef)]) = {0,};

/**
  * @}
  */

/** @defgroup RADIO_Exported_Functions RADIO Exported Functions
  * @{
  */

/**
  * @brief  Initializes the radio.
  * @retval None
  */
void HAL_RADIO_Init(RADIO_HandleTypeDef *hradio)
{
  uint32_t mr_ble_ibias;
  uint32_t mr_ble_iptat;
  uint32_t mr_ble_vbg;
  uint32_t mr_ble_rxadc_delay_i;
  uint32_t mr_ble_rxadc_delay_q;
  uint8_t mr_ble_rxadc_delay_flag;
  uint8_t *hot_table_radio_config = (uint8_t *)&hot_table_radio_config_u32[4];
  uint8_t index;

  /* Retrieve Trimming values from engineering flash locations */
  if (*(volatile uint32_t *)VALIDITY_LOCATION == VALIDITY_TAG)
  {
    mr_ble_ibias            = ((*(volatile uint32_t *)MR_TRIMMING_LOCATION) & MR_BLE_IBIAS_TRIM_Msk) >> MR_BLE_IBIAS_TRIM_Pos;
    mr_ble_iptat            = ((*(volatile uint32_t *)MR_TRIMMING_LOCATION) & MR_BLE_IPTAT_TRIM_Msk) >> MR_BLE_IPTAT_TRIM_Pos;
    mr_ble_vbg              = ((*(volatile uint32_t *)MR_TRIMMING_LOCATION) & MR_BLE_VBG_TRIM_Msk) >> MR_BLE_VBG_TRIM_Pos;
    mr_ble_rxadc_delay_i    = ((*(volatile uint32_t *)MR_TRIMMING_LOCATION) & MR_BLE_RXADC_DELAY_I_TRIM_Msk) >> MR_BLE_RXADC_DELAY_I_TRIM_Pos;
    mr_ble_rxadc_delay_q    = ((*(volatile uint32_t *)MR_TRIMMING_LOCATION) & MR_BLE_RXADC_DELAY_Q_TRIM_Msk) >> MR_BLE_RXADC_DELAY_Q_TRIM_Pos;
    mr_ble_rxadc_delay_flag = TRUE;
  }
  else
  {
    mr_ble_ibias = 0x08;
    mr_ble_iptat = 0x07;
    mr_ble_vbg   = 0x08;
    mr_ble_rxadc_delay_flag = FALSE;
#if defined(STM32WB05) || defined(STM32WB09)
    mr_ble_rxadc_delay_i    = 3;
    mr_ble_rxadc_delay_q    = 3;
    mr_ble_rxadc_delay_flag = TRUE;
#endif /* STM32WB05 or STM32WB09 */
  }

  BLUEGLOB->BYTE4 = BLUE_IDLE_0;
  if (hradio != NULL)
  {
    HAL_RADIO_MspInit(hradio);
  }
  LL_RADIO_TIMER_DisableTimer1(BLUE);
  LL_RADIO_TIMER_DisableTimer2(BLUE);
  LL_RADIO_TIMER_DisableBLEWakeupTimer(WAKEUP);

  /* Write Radio Trimming values in the registers: Cbias' VBG, Cbias' IPTAT, Cbias' IBIAS, RxAnaUsr Delay Trim I & Q */
  MODIFY_REG_FIELD(RRM->CBIAS1_ANA_ENG, RRM_CBIAS1_ANA_ENG_RFD_CBIAS_VBG_TRIM, mr_ble_vbg);
  MODIFY_REG_FIELD(RRM->CBIAS0_ANA_ENG, RRM_CBIAS0_ANA_ENG_RFD_CBIAS_IPTAT_TRIM, mr_ble_iptat);
  MODIFY_REG_FIELD(RRM->CBIAS0_ANA_ENG, RRM_CBIAS0_ANA_ENG_RFD_CBIAS_IBIAS_TRIM, mr_ble_ibias);
  if (mr_ble_rxadc_delay_flag)
  {
    MODIFY_REG_FIELD(RRM->RXADC_ANA_USR, RRM_RXADC_ANA_USR_RFD_RXADC_DELAYTRIM_I, mr_ble_rxadc_delay_i);
    MODIFY_REG_FIELD(RRM->RXADC_ANA_USR, RRM_RXADC_ANA_USR_RFD_RXADC_DELAYTRIM_Q, mr_ble_rxadc_delay_q);
  }

  /* Radio AFC configuration */
  MODIFY_REG(RRM->AFC1_DIG_ENG, RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER | RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE,
             ((AFC_DELAY_BEFORE << RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE_Pos) & RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE_Msk) |
             ((AFC_DELAY_AFTER << RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER_Pos) & RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER_Msk));
  MODIFY_REG(RRM->CR0_DIG_ENG, RRM_CR0_DIG_ENG_CR_GAIN_BEFORE | RRM_CR0_DIG_ENG_CR_GAIN_AFTER,
             ((CR_GAIN_BEFORE << RRM_CR0_DIG_ENG_CR_GAIN_BEFORE_Pos) & RRM_CR0_DIG_ENG_CR_GAIN_BEFORE_Msk) |
             ((CR_GAIN_AFTER << RRM_CR0_DIG_ENG_CR_GAIN_AFTER_Pos) & RRM_CR0_DIG_ENG_CR_GAIN_AFTER_Msk));
  MODIFY_REG(RRM->CR0_LR, RRM_CR0_LR_CR_LR_GAIN_BEFORE | RRM_CR0_LR_CR_LR_GAIN_AFTER,
             ((CR_LR_GAIN_BEFORE << RRM_CR0_LR_CR_LR_GAIN_BEFORE_Pos) & RRM_CR0_LR_CR_LR_GAIN_BEFORE_Msk) |
             ((CR_LR_GAIN_AFTER << RRM_CR0_LR_CR_LR_GAIN_AFTER_Pos) & RRM_CR0_LR_CR_LR_GAIN_AFTER_Msk));

  /* Radio RSSI Threshold configuration */
  MODIFY_REG_FIELD(RRM->LR_RSSI_THR_DIG_ENG, RRM_LR_RSSI_THR_DIG_ENG_LR_RSSI_THR, LR_RSSI_THR);
  MODIFY_REG_FIELD(RRM->LR_PD_THR_DIG_ENG, RRM_LR_PD_THR_DIG_ENG_LR_PD_THR, LR_PD_THR);
  MODIFY_REG_FIELD(RRM->LR_AAC_THR_DIG_ENG, RRM_LR_AAC_THR_DIG_ENG_LR_AAC_THR, LR_AAC_THR);

  /* Enable Viterbi */
  SET_BIT(RRM->VIT_CONF_DIG_ENG, RRM_VIT_CONF_DIG_ENG_VIT_CONF_0);

#if defined(STM32WB05) || defined(STM32WB09)
  MODIFY_REG_FIELD(RRM->ANTSW_DIG0_USR, RRM_ANTSW0_DIG_USR_RX_TIME_TO_SAMPLE, RX_TIME_TO_SAMPLE);
  MODIFY_REG_FIELD(RRM->ANTSW_DIG1_USR, RRM_ANTSW1_DIG_USR_RX_TIME_TO_SWITCH, RX_TIME_TO_SWITCH);
#endif /* STM32WB05 or STM32WB09 */

  /*Set InitDelay*/
  LL_RADIO_SetWakeupInitDelay(INITDELAY_WAKEUP);
  LL_RADIO_SetTimer12InitDelayCal(INITDELAY_TIMER12_CAL);
  LL_RADIO_SetTimer12InitDelayNoCal(INITDELAY_TIMER2_NOCAL);

  /*Set Init_radio_delay*/
  LL_RADIO_SetReceivedCalDelayChk(DELAYCHK_RECEIVE_CAL);
  LL_RADIO_SetReceivedNoCalDelayChk(DELAYCHK_RECEIVE_NOCAL);
  LL_RADIO_SetTransmitCalDelayChk(DELAYCHK_TRANSMIT_CAL);
  LL_RADIO_SetTransmitNoCalDelayChk(DELAYCHK_TRANSMIT_NOCAL);

  /* Initial and final TX delays: control the on-air start time of the TX packet
  *  and the length of the packet "tail" after last bit is transmitted
  */
  LL_RADIO_SetTxDelayStart(TXDELAY_START);
  LL_RADIO_SetTxDelayEnd(TXDELAY_END);

  /* Timeout for TX ready signal from the radio FSM after the 2nd init phase
  *  has expired
  */
  LL_RADIO_SetTransmissionReadyTimeout(TXREADY_TIMEOUT);

  /* Timing for the various programming phases of the radio, modem and memory
  *  pointers.
  */
  LL_RADIO_SetConfigurationEndDuration(CONFIG_END_DURATION);
  LL_RADIO_SetTxDataReadyCheck(CHECK_TXDATAREADY);

  LL_RADIO_ChkFlagAutoclearEnable_Enable();
  LL_RADIO_NoActiveLErrorInterrupt_Enable();
  LL_RADIO_TxRxSkipInterrupt_Enable();

#if defined(GLOBAL_WORD6_DEFAULTANTENNAID_Msk)
  LL_RADIO_SetDefaultAntennaID(0);
#else
  /* nothing to do */
#endif

  /* The commands in the hot table start at word 4
  * The words 0 to 2 are used to point to the command list
  * for the various trigger events, word 3 is a null command
  * (see function BLEPLAT_CNTR_SetRadioConfigData)
  */
  index = 0;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_CBIAS1_ANA_ENG;
  hot_table_radio_config[index++] = RRM->CBIAS1_ANA_ENG;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_CBIAS0_ANA_ENG;
  hot_table_radio_config[index++] = RRM->CBIAS0_ANA_ENG;

  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_RXADC_ANA_USR;
  hot_table_radio_config[index++] = RRM->RXADC_ANA_USR;

  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_AFC1_DIG_ENG;
  hot_table_radio_config[index++] = RRM->AFC1_DIG_ENG;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_CR0_DIG_ENG;
  hot_table_radio_config[index++] = RRM->CR0_DIG_ENG;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_CR0_LR;
  hot_table_radio_config[index++] = RRM->CR0_LR;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_LR_RSSI_THR_DIG_ENG;
  hot_table_radio_config[index++] = RRM->LR_RSSI_THR_DIG_ENG;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_LR_PD_THR_DIG_ENG;
  hot_table_radio_config[index++] = RRM->LR_PD_THR_DIG_ENG;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_LR_AAC_THR_DIG_ENG;
  hot_table_radio_config[index++] = RRM->LR_AAC_THR_DIG_ENG;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_VIT_CONF_DIG_ENG;
  hot_table_radio_config[index++] = RRM->VIT_CONF_DIG_ENG;
#if defined(STM32WB05) || defined(STM32WB09)
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_ANTSW_DIG0_USR;
  hot_table_radio_config[index++] = RRM->ANTSW_DIG0_USR;
  hot_table_radio_config[index++] = 0x01;
  hot_table_radio_config[index++] = RRM_ANTSW_DIG1_USR;
  hot_table_radio_config[index++] = RRM->ANTSW_DIG1_USR;
#endif
  hot_table_radio_config[index++] = 0x00;

  hot_table_radio_config_u32[0] = (uint32_t)(&hot_table_radio_config_u32[4]); /* Point to Port 0 command list 1 executed when Wakeup timer triggers */
  hot_table_radio_config_u32[1] = (uint32_t)(&hot_table_radio_config_u32[4]); /* Point to Port 0 command list 2 executed when Timer1 triggers       */
  hot_table_radio_config_u32[2] = (uint32_t)(&hot_table_radio_config_u32[3]); /* Point to Port 0 command list 3 executed when Timer2 triggers       */
  hot_table_radio_config_u32[3] = 0x00000000;                /* Null command */

  LL_RADIO_SetRadioConfigurationAddressPointer(hot_table_radio_config_u32[0]);
  /* Reload radio config pointer */
  RRM->UDRA_CTRL0 = RRM_UDRA_CTRL0_RELOAD_RDCFGPTR;
  LL_RADIO_Active2ErrorInterrupt_Enable();

#if USE_RADIO_PROPRIETARY_DRIVER
  globalParameters.back2backTime = BACK_TO_BACK_TIME;
  globalParameters.tone_start_stop_flag = 0;
#endif

  /*Clear all interrupts of the BLUE Controller*/
  uint32_t int_val_tmp = BLUE->INTERRUPT1REG;
  BLUE->INTERRUPT1REG = int_val_tmp;

  /*BLE wake up IRQ Status clearing and enable*/
  WAKEUP->WAKEUP_BLE_IRQ_STATUS |= 1;
  WAKEUP->WAKEUP_BLE_IRQ_ENABLE |= 1;

  /* If the device is configured with
     System clock = 64 MHz and BLE clock = 16 MHz
     a register read is necessary to end fine
     the clear interrupt register operation,
     due the AHB down converter latency */
  int_val_tmp = BLUE->INTERRUPT1REG;

  return;
}

/**
  * @brief  Read RSSI
  * @retval int8_t: RSSI in dBm
  */
int8_t HAL_RADIO_ReadRSSI(void)
{
  int32_t rssi_dbm;
  uint32_t rssi0 = RRM->RSSI0_DIG_OUT;
  uint32_t rssi1 = RRM->RSSI1_DIG_OUT;

  uint32_t rssi_int16 = ((rssi1 & 0xFF) << 8) | (rssi0 & 0xFF);
  uint32_t reg_agc = RRM->AGC_DIG_OUT;

  if ((rssi_int16 == 0U) || (reg_agc > 0xbU))
  {
    rssi_dbm = 127 ;
  }
  else
  {
    rssi_dbm = (int32_t)reg_agc * 6 - RSSI_OFFSET;//127 ;
    while (rssi_int16 > 30U)
    {
      rssi_dbm = rssi_dbm + 6 ;
      rssi_int16 = (rssi_int16 >> 1) ;
    }
    rssi_dbm = rssi_dbm + (int32_t)(uint32_t)((417U * rssi_int16 + 18080U) >> 10);
  }
  return (int8_t)rssi_dbm;
}

#if USE_RADIO_PROPRIETARY_DRIVER

/**
  * @brief  This routine is called when a RADIO event is complete.
  * @param  p: Current action packet which its transaction has been completed.
  * @param  next: Next action packet which is going to be scheduled.
  * @retval return value: TRUE
  */
uint8_t HAL_RADIO_Callback(ActionPacket *p, ActionPacket *next)
{
  /* Event is a reception */
  if ((p->status & BLUE_STATUSREG_PREVTRANSMIT) == 0)
  {
    RxStats_t receivedStats = {0};
    /* Reception ends with no errors */
    if ((p->status & BLUE_INTERRUPT1REG_RCVOK) != 0)
    {
      if ((p->status & BLUE_INTERRUPT1REG_ENCERROR) != 0)
      {
        receivedStats.rssi = p->rssi;
        receivedStats.timestamp_receive = p->timestamp_receive;
        HAL_RADIO_CallbackRcvEncryptErr(&receivedStats);
      }
      else
      {
        receivedStats.rssi = p->rssi;
        receivedStats.timestamp_receive = p->timestamp_receive;
        HAL_RADIO_CallbackRcvOk(&receivedStats);
      }
    }
    /* Reception ends with timeout */
    else if ((p->status & BLUE_INTERRUPT1REG_RCVTIMEOUT) != 0)
    {
      receivedStats.rssi = p->rssi;
      receivedStats.timestamp_receive = 0;
      HAL_RADIO_CallbackRcvTimeout(&receivedStats);
    }
    /* Reception ends with errors */
    else if ((p->status & BLUE_INTERRUPT1REG_RCVCRCERR) != 0)
    {
      receivedStats.rssi = p->rssi;
      receivedStats.timestamp_receive = p->timestamp_receive;
      HAL_RADIO_CallbackRcvError(&receivedStats);
    }
  }
  /* Event is a transmission */
  else if ((p->status & BLUE_INTERRUPT1REG_DONE) != 0)
  {
    /* RADIO TX operation done */
    HAL_RADIO_CallbackTxDone();
  }
  return TRUE;
}

__weak void HAL_RADIO_CallbackRcvError(RxStats_t *rxPacketStats) {}
__weak void HAL_RADIO_CallbackRcvTimeout(RxStats_t *rxPacketStats) {}
__weak void HAL_RADIO_CallbackRcvEncryptErr(RxStats_t *rxPacketStats) {}
__weak void HAL_RADIO_CallbackRcvOk(RxStats_t *rxPacketStats) {}
__weak void HAL_RADIO_CallbackTxDone(void) {}

/**
  * @brief  Radio ISR.
  *         Besides, next packet is scheduled here.
  * @retval None
  */
static void HAL_RADIO_ActionPacketIsr(uint32_t int_flags)
{
  if ((int_flags & BLUE_INTERRUPT1REG_DONE) != 0)
  {

    ActionPacket *next, *actionPacketBackup;
    BlueTransStruct *p;
    uint32_t time;

    /* Copy status in order for callback to access it. */
    globalParameters.current_action_packet->status = int_flags | \
                                                     (BLUE->STATUSREG & BLUE_STATUSREG_PREVTRANSMIT_Msk);

    if ((globalParameters.current_action_packet->condRoutine(globalParameters.current_action_packet)) == TRUE)
    {
      next = globalParameters.current_action_packet->next_true;
    }
    else
    {
      next = globalParameters.current_action_packet->next_false;
    }
    /*The radio event is started. So here a check on the next packet of the event is made*/
    if (next == NULL_0)
    {
      /* timer2 off */
      LL_RADIO_TIMER_DisableTimer1(BLUE);
      LL_RADIO_TIMER_DisableTimer2(BLUE);
      LL_RADIO_TIMER_DisableBLEWakeupTimer(WAKEUP);
      MODIFY_REG(BLUEGLOB->BYTE4, GLOBAL_BYTE4_ACTIVE_Msk, BLUE_IDLE_0);
      HAL_RADIO_TIMER_ClearRadioTimerValue();
    }
    else
    {
      BLUEGLOB->BYTE4 = (next->StateMachineNo | GLOBAL_BYTE4_ACTIVE_Msk);
      p = &next->trans_packet;
      MODIFY_REG((bluedata + next->StateMachineNo)->BYTE0, STATEMACH_BYTE0_TXMODE_Msk,
                 next->trans_config);/* Transmission or reception*/
      (bluedata + next->StateMachineNo)->TXPOINT = BLUE_STRUCT_PTR_CAST(p);
      (bluedata + next->StateMachineNo)->RCVPOINT = BLUE_STRUCT_PTR_CAST(p);
      (bluedata + next->StateMachineNo)->MAXRECEIVEDLENGTH = next->MaxReceiveLength;

      /* Packet will execute on time specified by WakeupTime */
      if ((next->ActionTag & TIMER_WAKEUP) != 0)
      {
        /* timer1/2 off */
        LL_RADIO_TIMER_DisableTimer1(BLUE);
        LL_RADIO_TIMER_DisableTimer2(BLUE);

        /* program timer at next->wakeuptime */
        if ((next->ActionTag & RELATIVE) != 0)
        {
          time = HAL_RADIO_TIMER_GetCurrentSysTime() + HAL_RADIO_TIMER_UsToSystime(next->WakeupTime);
          HAL_RADIO_TIMER_SetRadioTimerValue(time, (next->trans_config == STATEMACH_BYTE0_TXMODE_Msk), (next->ActionTag & PLL_TRIG));
        }
        else
        {
          HAL_RADIO_TIMER_SetRadioTimerValue(next->WakeupTime, (next->trans_config == STATEMACH_BYTE0_TXMODE_Msk), (next->ActionTag & PLL_TRIG));
        }
      }
      else
      {
        /* back to back */
      }
    }

    /* Accept the packet even with CRC Error */
    if (((int_flags & BLUE_INTERRUPT1REG_RCVOK) != 0) || ((int_flags & BLUE_INTERRUPT1REG_RCVCRCERR) != 0))
    {

      uint64_t current_system_time;
      /* read RSSI */
      globalParameters.current_action_packet->rssi =  HAL_RADIO_ReadRSSI();

      /* bluedata->config = bluedata->config ^ 0x80 ;  toggle NESN bit
      bluedata->config = bluedata->config & 0x7F ;  //reset NESN bit */

      /* read time stamp */
      globalParameters.current_action_packet->timestamp_receive = HAL_RADIO_TIMER_GetAnchorPoint(&current_system_time);
    }
    else if ((int_flags & BLUE_INTERRUPT1REG_RCVTIMEOUT) != 0)
    {
      /* read RSSI even if a timeout happens */
      globalParameters.current_action_packet->rssi =  HAL_RADIO_ReadRSSI();
    }

    actionPacketBackup = globalParameters.current_action_packet;
    globalParameters.current_action_packet = next;
    actionPacketBackup->dataRoutine(actionPacketBackup, next);
  }

  return ;
}

/**
  * @brief  This routine force the radio to be stopped. After calling this function,
  *         the ISR is not triggered unless, "MakeActionPacketPending" API called again.
  * @retval 0 if the radio activity has been cleared successfully.
  * @retval 1 if it is too late to clear the last radio activity.
  * @retval 2 if it might not be possible to clear the last radio activity.
  */
uint8_t HAL_RADIO_StopActivity(void)
{
  uint8_t retval;
  MASK_INTERRUPTS();
  MODIFY_REG(BLUEGLOB->BYTE4, GLOBAL_BYTE4_ACTIVE_Msk, BLUE_IDLE_0);
  retval = HAL_RADIO_TIMER_ClearRadioTimerValue();
  globalParameters.current_action_packet = 0;
  UNMASK_INTERRUPTS();
  return retval;
}

/**
  * @brief  This routine sets the channel map. If channel map is not in use, do not use it. The
  *         chan_remap constant is a 37-bit vector, one bit per channel from 0 to 36, with the
  *         LSB corresponding to the channel 0. If the corresponding bit is set, the channel is in use; if it is cleared,
  *         there is an automatic remap to another channel, as defined in the Bluetooth Low
  *         Energy specification.
  *         Setting all bits of the array to one, disables the channel remapping, and this is the mode
  *         that should be used if the Bluetooth channel remap is not in use.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  chan_remap: a 37-bit vector, one bit per channel from 0 to 36, with the LSB corresponding to the channel 0
  * @retval None
  */
void HAL_RADIO_SetChannelMap(uint8_t StateMachineNo, uint8_t *chan_remap)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));

  for (uint8_t i = 0; i < 5; i++)
  {
    (bluedata + StateMachineNo)->USEDCHANNELFLAGS[i] = chan_remap[i];
  }
  (bluedata + StateMachineNo)->USEDCHANNELFLAGS[4] &= 0x1F;
  return;
}

/**
  * @brief  This routine sets the channel and the channel increment. Channel and channel
  *         increment follows channel mapping corresponding to Bluetooth specification.
  *         RF channel 0:  2402 MHz -> ble channel index 37
  *         RF channel 1:  2404 MHz -> ble channel index 0
  *         RF channel 2:  2406 MHz -> ble channel index 1
  *         ...
  *         RF channel 11: 2424 MHz -> ble channel index 10
  *         RF channel 12: 2426 MHz -> ble channel index 38
  *         RF channel 13: 2428 MHz -> ble channel index 11
  *         RF channel 14: 2430 MHz -> ble channel index 12
  *         ...
  *         RF channel 38: 2478 MHz -> ble channel index 36
  *         RF channel 39: 2480 MHz -> ble channel index 39
  *
  *         For the ble channel index 37, 38 and 39 (RF channel 0, 12, 39):
  *          - The crc_init value should always be 0x555555.
  *          - There is no encryption.
  *          - The channel increment is dedicated, the channel sequence is:
  *            37 -> 38 -> 39 -> 37 -> ... while for the other channels is:
  *            0 -> 1 -> ... -> 36 -> 0 -> ...
  *            There is no channel map for these three channels.
  *            Valid values for packet length for these channels are from 6 to 37.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  channel: ble channel index. From 0 to 39.
  * @param  channel_increment: determines the hoping value.
  * @retval None
  */
void HAL_RADIO_SetChannel(uint8_t StateMachineNo, uint8_t channel, uint8_t channel_increment)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));
  assert_param(IS_RFCHANNEL_VALID(channel));

  MODIFY_REG((bluedata + StateMachineNo)->BYTE0, STATEMACH_BYTE0_UCHAN_Msk, channel);
  /*if TxRxPack.incchan = 0, then remap_chan is used as physical channel*/
  MODIFY_REG((bluedata + StateMachineNo)->BYTE1, STATEMACH_BYTE1_REMAP_CHAN_Msk, channel);
  (bluedata + StateMachineNo)->HOPINCR = channel_increment;
  return;
}

/**
  * @brief  This routine sets the NetworkID and the CRC init.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  NetworkID: The NetworkID is the ID of the device.
  *         The user shall ensure that the NetworkID meets the following requirements:
  *           - It shall have no more than six consecutive zeros or ones.
  *           - It shall not have all four octets equal.
  *           - It shall have no more than 24 transitions.
  *           - It shall have a minimum of two transitions in the most significant six bits.
  * @param  crc_init: CRC initialization value.
  *         This value must be 0x555555 when channel frequency is one of these values: 37, 38, 39.
  * @retval None
  */
void HAL_RADIO_SetTxAttributes(uint8_t StateMachineNo, uint32_t NetworkID, uint32_t crc_init)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));

  (bluedata + StateMachineNo)->ACCADDR = NetworkID;
  (bluedata + StateMachineNo)->CRCINIT[0] = crc_init;
  (bluedata + StateMachineNo)->CRCINIT[1] = crc_init >> 8;
  (bluedata + StateMachineNo)->CRCINIT[2] = crc_init >> 16;
  return;
}

/**
  * @brief  This routine sets the 40-bit receive and transmit packet count, to be used in
  *         encryption calculation.
  *         Both are pointers to char, and set the 39-bit counter + 1-bit MSB as defined in the
  *         Bluetooth Low Energy spec. One is for transmit packets, the other is for receive packets.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  count_tx: 40-bit transmit packet count, to be used in encryption nounce calculation.
  * @param  count_rcv: 40-bit receive packet count, to be used in encryption nounce calculation.
  * @retval None
  */
void HAL_RADIO_SetEncryptionCount(uint8_t StateMachineNo, uint8_t *count_tx, uint8_t *count_rcv)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));

  for (uint8_t i = 0; i < 5; i++)
  {
    (bluedata + StateMachineNo)->PCNTRCV[i] = count_rcv[i];
    (bluedata + StateMachineNo)->PCNTTX[i] = count_tx[i];
  }
  return;
}

/**
  * @brief  This routines sets the 8-byte encryption initial vector, and the 16-byte encryption key.
  *         The definition of the encryption key and its initial value is according the Bluetooth Low Energy spec.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  enc_iv: 8-byte encryption initial vector.
  * @param  enc_key: 16-byte encryption key.
  * @retval None
  */
void HAL_RADIO_SetEncryptionAttributes(uint8_t StateMachineNo, uint8_t *enc_iv, uint8_t *enc_key)
{
  uint8_t i = 0;
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));

  for (i = 0; i < 8; i++)
  {
    (bluedata + StateMachineNo)->ENCRYPTIV[i] = enc_iv[i];
    (bluedata + StateMachineNo)->ENCRYPTK[i] = enc_key[i];
  }
  for (i = 8; i < 16; i++)
  {
    (bluedata + StateMachineNo)->ENCRYPTK[i] = enc_key[i];
  }

  return;
}

/**
  * @brief  Set the maximum length of a received packet.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  MaxReceivedLength: Upper limit for the length of a received packet.
  *                            From 0 to 255 bytes.
  * @retval None
  */
void HAL_RADIO_SetMaxReceivedLength(uint8_t StateMachineNo, uint8_t MaxReceivedLength)
{
  (bluedata + StateMachineNo)->MAXRECEIVEDLENGTH = MaxReceivedLength;
  return;
}

/**
  * @brief  Initializes the time between back-to-back radio transmissions.
  * @param  back_to_back_time: time between two packets if wakeupTimer is not used. Resolution is 1 us.
  * @retval None
  */
void HAL_RADIO_SetBackToBackTime(uint32_t back_to_back_time)
{
  globalParameters.back2backTime = back_to_back_time;
  return;
}


/**
  * @brief Phy selection
  * @param  StateMachineNo: state machine number in multi state.
  * @param  phy:
  *         0x0  PHY is not coded 1Mbps
  *         0x1  PHY is not coded 2Mbps
  *         0x4  PHY is coded 1Mbps with S=8
  *         0x6  PHY is coded 1Mbps with S=2
  * @retval None
  */
void HAL_RADIO_SetPhy(uint8_t StateMachineNo, uint8_t phy)
{
  assert_param(IS_PHY_VALID(phy));

  MODIFY_REG((bluedata + StateMachineNo)->BYTE3, STATEMACH_BYTE3_TXPHY_Msk, phy);
  MODIFY_REG((bluedata + StateMachineNo)->BYTE3, STATEMACH_BYTE3_RXPHY_Msk, phy << 4);

  return;
}

/**
  * @brief  This routine turns encrypt ON and OFF. When the encryption is enabled, the hardware will add 4 bytes
  *         at the end of the packet as MIC (Message Authentication Code). So the user need to add 4 byte to the
  *         length of the packet. The parameters enable the encryption for both. There are two separated parameters
  *         for this function just compliance with previous version of the driver.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  EncryptFlagTx: DISABLE: encryption is turned OFF for both TX and RX operations.
  *              ENABLE: encryption is turned OFF for both TX and RX operations.
  *         This parameter can be: ENABLE or DISABLE.
  * @param  EncryptFlagRcv: encryption is turned OFF for both TX and RX operations.
  *              ENABLE: encryption is turned OFF for both TX and RX operations.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void HAL_RADIO_SetEncryptFlags(uint8_t StateMachineNo, FunctionalState EncryptFlagTx, FunctionalState EncryptFlagRcv)
{
  /* Check the parameters */
  assert_param(IS_STATE_VALID(StateMachineNo));
  assert_param(IS_FUNCTIONAL_STATE(EncryptFlagTx));
  assert_param(IS_FUNCTIONAL_STATE(EncryptFlagRcv));

  if (EncryptFlagTx == ENABLE || EncryptFlagRcv == ENABLE)
  {
    (bluedata + StateMachineNo)->BYTE2 |= STATEMACH_BYTE2_ENCRYPTON_Msk;
    (bluedata + StateMachineNo)->BYTE35 |= STATEMACH_BYTE35_INTENCERROR_Msk;
  }
  else
  {
    (bluedata + StateMachineNo)->BYTE2 &= (~STATEMACH_BYTE2_ENCRYPTON_Msk);
  }
  (bluedata + StateMachineNo)->BYTE35 |= STATEMACH_BYTE35_INTRXOVERFLOWERROR_Msk;
  return;
}

/**
  * @brief  Set the receive window length.
  *         Define the maximum duration to stay in reception without any preamble
  *         and access address detection.
  * @param  ReceiveTimeout: receive window length in microseconds.
  * @retval None
  */
void HAL_RADIO_SetGlobalReceiveTimeout(uint32_t ReceiveTimeout)
{
  /* Set the Rx window Timeout expressed as: 4^(RCVTIMEOUT_19_18)*RCVTIMEOUT_17_0 */
  if (ReceiveTimeout < 0x40000)
  {
    BLUEGLOB->RCVTIMEOUT[0] = (ReceiveTimeout)       & 0x000000FF;
    BLUEGLOB->RCVTIMEOUT[1] = (ReceiveTimeout >> 8)  & 0x000000FF;
    BLUEGLOB->RCVTIMEOUT[2] = (ReceiveTimeout >> 16) & 0x00000003;
  }
  else if (ReceiveTimeout < 0x100000)
  {
    BLUEGLOB->RCVTIMEOUT[0] = (ReceiveTimeout >> 2)  & 0x000000FF;
    BLUEGLOB->RCVTIMEOUT[1] = (ReceiveTimeout >> 10) & 0x000000FF;
    BLUEGLOB->RCVTIMEOUT[2] = (ReceiveTimeout >> 18) & 0x00000003;

    BLUEGLOB->RCVTIMEOUT[2] |= 0x04;
  }
  else if (ReceiveTimeout < 0x400000)
  {
    BLUEGLOB->RCVTIMEOUT[0] = (ReceiveTimeout >> 4)  & 0x000000FF;
    BLUEGLOB->RCVTIMEOUT[1] = (ReceiveTimeout >> 12) & 0x000000FF;
    BLUEGLOB->RCVTIMEOUT[2] = (ReceiveTimeout >> 20) & 0x00000003;

    BLUEGLOB->RCVTIMEOUT[2] |= 0x08;
  }
  else if (ReceiveTimeout < 0x1000000)
  {
    BLUEGLOB->RCVTIMEOUT[0] = (ReceiveTimeout >> 6)  & 0x000000FF ;
    BLUEGLOB->RCVTIMEOUT[1] = (ReceiveTimeout >> 14) & 0x000000FF ;
    BLUEGLOB->RCVTIMEOUT[2] = (ReceiveTimeout >> 22) & 0x00000003 ;

    BLUEGLOB->RCVTIMEOUT[2] |= 0x0C;
  }
  else
  {
    /* error */
  }
}

/**
  * @brief  This routine should be called after writing/modifying an action packet, and before it
  *         is executed via either the API mechanism, or the next mechanism.
  * @param  p: pointer to action packet.
  * @retval None
  */
void HAL_RADIO_SetReservedArea(ActionPacket *p)
{
  uint32_t relTimeout;
  uint32_t cnt;

  /*Init to 0 the TxRxPack*/
  for (cnt = 0; cnt < sizeof(p->trans_packet); cnt++)
  {
    ((uint8_t *)(&(p->trans_packet)))[cnt] = 0;
  }

  /*Set the TxRxPack for the next transaction. The list cannot be empty.
  At least,it can be composed by one only packet that points to itself*/
  p->trans_packet.NEXTPTR = BLUE_STRUCT_PTR_CAST(&(p->trans_packet));

  /* Set the buffer that contains the values to send or that stores
  the data received */
  p->trans_packet.DATAPTR = BLUE_DATA_PTR_CAST(p->data);

  /* Compensate the radio setup time from the back2back time */
  relTimeout = globalParameters.back2backTime - 70;

  /*Check if there is some action to perform next*/
//  if (p->next_false || p->next_true){ /* Host timer workaround */
  /* Set the Timeout for the Timer2 */
  p->trans_packet.TIMER2[0] = relTimeout & 0xFF;
  p->trans_packet.TIMER2[1] = (relTimeout >> 8) & 0xFF;
  p->trans_packet.BYTE14 = (relTimeout >> 16) & TXRXPACK_BYTE14_TIMER2_19_16_Msk;
  /*Enable relative timer*/
  p->trans_packet.BYTE14 |= TXRXPACK_BYTE14_TIMER2EN_Msk;
//  }

  /* TrigDone or TrigReceive */
  if ((p->ActionTag & TIMESTAMP_POSITION) == 0)
  {
    p->trans_packet.BYTE14 |= TIMESTAMP_POSITION_LASTBIT;
  }
  else
  {
    p->trans_packet.BYTE14 |= TIMESTAMP_POSITION_ACCESSADDRESS;
  }

  p->trans_packet.BYTE4 |= TXRXPACK_BYTE4_KEEPSEMAREQ_Msk | \
                           (p->ActionTag & INC_CHAN) | \
                           (p->ActionTag & PLL_TRIG);

  p->trans_packet.BYTE5 |= (p->ActionTag & WHITENING_DISABLE) | \
                           TXRXPACK_BYTE5_TXDATAREADY_Msk | \
                           TXRXPACK_BYTE5_ALLTABLEREADY_Msk;

  /* Enable all interrupts */
  p->trans_packet.BYTE15 = TXRXPACK_BYTE15_INT_EN_Msk;

  /* By Default the next action is considered as next_true */
  if ((p->next_true->ActionTag & TXRX) != 0)
  {
    /* Set the type of the next activity */
    p->trans_packet.BYTE5 |= TXRXPACK_BYTE5_NEXTTXMODE_Msk;
  }

  p->trans_config = 0; // Rx
  if ((p->ActionTag & TXRX) != 0)
  {
    p->trans_config = STATEMACH_BYTE0_TXMODE_Msk; // Tx
  }
  return ;
}


/**
  * @brief  This routine should be called for the first actionPacket that needs to be scheduled
  *         on the radio. For it to work OK, the WakeupTime should be valid.
  *         Subsequent packets can be dispatched using the same process, or by providing non-NULL pointers
  *         to the next_true and next_false pointers of the ActionPacket.
  * @param  p: pointer to action packet.
  * @retval uint8_t with following values:
  *          - 0x00 : Success.
  *          - 0xC4 : Radio is busy, action packet has not been executed.
  */
uint8_t HAL_RADIO_MakeActionPacketPending(ActionPacket *p)
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t time;
  uint32_t dummyTime;
  if (HAL_RADIO_GetStatus(&dummyTime) == BLUE_IDLE_0)
  {
    uint8_t  statemachineNo;
    BlueTransStruct *p1 ;

    /* timer1/2 off */
    LL_RADIO_TIMER_DisableTimer1(BLUE);
    LL_RADIO_TIMER_DisableTimer2(BLUE);

    statemachineNo = 0x7F & p->StateMachineNo;

    BLUEGLOB->BYTE4 = (p->StateMachineNo | GLOBAL_BYTE4_ACTIVE_Msk);

    p1 = &p->trans_packet;
    (bluedata + statemachineNo)->RCVPOINT = BLUE_STRUCT_PTR_CAST(p1);
    (bluedata + statemachineNo)->TXPOINT = BLUE_STRUCT_PTR_CAST(p1);
    (bluedata + statemachineNo)->MAXRECEIVEDLENGTH = p->MaxReceiveLength;

#if defined (STM32WB05) || defined(STM32WB09 )
    (bluedata + statemachineNo)->BYTE3 |= 1 << 3;
#endif

    globalParameters.current_action_packet = p;

    MODIFY_REG((bluedata + statemachineNo)->BYTE0, STATEMACH_BYTE0_TXMODE_Msk,
               p->trans_config); /* Transmission or reception */

    /* program timer at next->wakeuptime */
    MASK_INTERRUPTS();
    if ((p->ActionTag & RELATIVE) != 0)
    {
      time = HAL_RADIO_TIMER_GetCurrentSysTime() + HAL_RADIO_TIMER_UsToSystime(p->WakeupTime);
      returnValue = HAL_RADIO_TIMER_SetRadioTimerValue(time, (p->trans_config == STATEMACH_BYTE0_TXMODE_Msk), (p->ActionTag & PLL_TRIG));
    }
    else /*absolute time*/
    {
      returnValue = HAL_RADIO_TIMER_SetRadioTimerValue(p->WakeupTime, (p->trans_config == STATEMACH_BYTE0_TXMODE_Msk), (p->ActionTag & PLL_TRIG));
    }

    UNMASK_INTERRUPTS();
  }
  else
  {
    returnValue = RADIO_BUSY_C4;
  }
  return returnValue;
}

/**
  * @brief  Get the status of the radio and if it is active
  *         the last programmed value in MTU.
  * @param  time: where to store the last value programmed.
  * @retval 0 if the radio controller is IDLE or no timer has been programmed
  * @retval 1 if the radio is ACTIVE and a radio timer has been programmed
  */
uint8_t HAL_RADIO_GetStatus(uint32_t *time)
{
  uint8_t retValue = BLUE_IDLE_0;
  if ((BLUEGLOB->BYTE4 & GLOBAL_BYTE4_ACTIVE_Msk) != 0)
  {
    retValue = HAL_RADIO_TIMER_GetRadioTimerValue(time);
  }
  return retValue;
}

/**
  * @brief  Configures the transmit power level.
  * @param  PowerLevel: power level which should set to this value.
  *         See the documentation inside the datasheet.
  * @retval None
  */
void HAL_RADIO_SetTxPower(uint8_t PowerLevel)
{
  /* Check the parameters */
  assert_param(IS_POWERLEVEL_VALID(PowerLevel));

  for (uint8_t n = 0; n < STATEMACHINE_COUNT ; n++)
  {
    (bluedata + n)->PAPOWER = PowerLevel;
  }
  return;
}


/**
  * @brief  Restore default preamble length to one byte.
  * @param  StateMachineNo: state machine number in multi state.
  * @retval None
  */
void HAL_RADIO_SetDefaultPreambleLen(uint8_t StateMachineNo)
{
  (bluedata + StateMachineNo)->BYTE34 &= ~(STATEMACH_BYTE34_ENAPREAMBLEREP_Msk);
  return;
}

/**
  * @brief  Set how many times repeat the preamble.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  PreaLen: preamble length in byte for coded or uncoded phy.
  * @retval None
  */
void HAL_RADIO_SetPreambleRep(uint8_t StateMachineNo, uint8_t PreaLen)
{
  /* Check the parameters */
  assert_param(IS_PREALEN_VALID(PreaLen));

  (bluedata + StateMachineNo)->BYTE34 |= STATEMACH_BYTE34_ENAPREAMBLEREP_Msk;
  (bluedata + StateMachineNo)->BYTE34 |= (PreaLen & STATEMACH_BYTE34_PREAMBLEREP_Msk);
  return;
}

/**
  * @brief  Enable or disable the CRC hardware functionality.
  * By default the CRC hardware feature is enabled. So, it can be enabled again
  * if it has been disabled.
  * If disabled, the CRC will be neither checked in reception nor appended in transmission.
  * @warning ALPHA version. In reception just ignore the CRC error and don't use this feature.
  * @param  StateMachineNo: state machine number in multi state.
  * @param  hwCRC:
  *         - ENABLE: enable the CRC hardware feature.
  *         - DISABLE: disable the CRC hardware feature.
  * @retval None
  */
void HAL_RADIO_DisableCRC(uint8_t StateMachineNo, FunctionalState hwCRC)
{
  if (hwCRC != DISABLE)
  {
    (bluedata + StateMachineNo)->BYTE34 &= ~STATEMACH_BYTE34_DISABLECRC_Msk;
  }
  else
  {
    (bluedata + StateMachineNo)->BYTE34 |= STATEMACH_BYTE34_DISABLECRC_Msk;
  }
  return;
}

/**
  * @brief  Starts tone transmission on selected channel.
  *         This API is dedicated for test and destroys context and multistate.
  *         So, after calling this function the radio should be re-initialized.
  * @param  RF_Channel: radio frequency channel number from 0 to 39.
  *         Note that RF channel index is different from ble channel index due to advertising channels,
  *         Please refer following table:
  *         RF channel 0:  2402 MHz -> ble channel index 37
  *         RF channel 1:  2404 MHz -> ble channel index 0
  *         RF channel 2:  2406 MHz -> ble channel index 1
  *         ...
  *         RF channel 11: 2424 MHz -> ble channel index 10
  *         RF channel 12: 2426 MHz -> ble channel index 38
  *         RF channel 13: 2428 MHz -> ble channel index 11
  *         RF channel 14: 2430 MHz -> ble channel index 12
  *         ...
  *         RF channel 38: 2478 MHz -> ble channel index 36
  *         RF channel 39: 2480 MHz -> ble channel index 39
  * @param  powerLevel: power level which should set.
  * @param  freq_offset: Specify if the tone must be emitted with an offset from the channel center frequency.
  *         If 0, the tone is emitted at the channel center frequency.
  *         If 1 or 2, the device will continuously emit the tone at the center
  *         frequency plus or minus 250 kHz respectively..
  * @retval None
  */
uint8_t HAL_RADIO_StartTone(uint8_t RF_Channel, uint8_t powerLevel, uint8_t freq_offset)
{
  /* Check the parameters */
  assert_param(IS_RFCHANNEL_VALID(RF_Channel));
  assert_param(IS_POWERLEVEL_VALID(powerLevel));
  assert_param(IS_FREQOFFSET_VALID(freq_offset)); /*TBR*/

  uint8_t retVal;
  uint32_t dummyTime;

  if (globalParameters.tone_start_stop_flag != 0U)
  {
    retVal = 1;
  }
  else
  {
    if ((RF_Channel >= 40U) || (freq_offset > 2U)) /*TBR*/
    {
      retVal = 1;
    }
    else
    {
      if (HAL_RADIO_GetStatus(&dummyTime) == BLUE_IDLE_0)
      {
        globalParameters.tone_start_stop_flag = 1;
        /* [EM:] Calculate the synt divide factor for 16 MHz quarts and +250 kHz offset wrt the channel center frequency
        *  Algorithmically MAK = F_rf*(2^20)/32 = F_rf*(2^15)
        *  With F_rf = (2402+2*RF_Channel)+0.25 MHz
        *  K corresponds to b19-b0  of MAK
        *  A corresponds to b22-b20 of MAK
        *  M corresponds to b27-b23 of MAK
        */
        uint32_t kHz_250_scaled = 8192; // = 0.250*2^20/32
        uint32_t MAK = ((2402UL + 2UL * RF_Channel) << 15);

        if (freq_offset == 1U)
        {
          MAK += kHz_250_scaled;
        }
        else if (freq_offset == 2U)
        {
          MAK -= kHz_250_scaled;
        }
        else
        {
        }

        uint8_t  M  = ((uint8_t)(MAK >> 23) & 0x1FU);
        uint8_t  A  = ((uint8_t)(MAK >> 20) & 0x07U);
        uint32_t K = (MAK & 0x000FFFFFUL) + 1UL;

        uint32_t MOD3_DIG_TEST = (M << 3) | (A & 0x7U);
        uint32_t MOD2_DIG_TEST = (K >> 12) & 0xFFU;
        uint32_t MOD1_DIG_TEST = (K >> 4) & 0xFFU;
        uint32_t MOD0_DIG_TEST = ((K & 0x0FU) << 4) | 0x09U;
        uint32_t RADIO_FSM_USR = ((powerLevel) << 3) | 0x06;

        RRM->RADIO_FSM_USR = RADIO_FSM_USR;
        RRM->MOD3_DIG_TST = MOD3_DIG_TEST;
        RRM->MOD2_DIG_TST = MOD2_DIG_TEST;
        RRM->MOD1_DIG_TST = MOD1_DIG_TEST;
        RRM->MOD0_DIG_TST = MOD0_DIG_TEST;

        /* Take control of the radio FSM through the test bus */
        RRM->DTB5_DIG_ENG = 0x09;
        uint32_t *rrm_udra_test = ((uint32_t *)&RRM->RRM_CTRL) + 0x01;
        *rrm_udra_test = 0x03;
        RRM->DTB5_DIG_ENG = 0x39;
        while (RRM->FSM_STATUS_DIG_OUT != 0x04);
        RRM->DTB5_DIG_ENG = 0x3B;
        retVal = 0;
      }
      else
      {
        retVal = 1;
      }
    }
  }
  return retVal;
}

/**
  * @brief  This routine stop tone transmission.
  *         This API is dedicated for test and destroys context and multistate.
  *         So, after calling this function the radio should be re-initialized.
  * @retval None
  */
uint8_t HAL_RADIO_StopTone(void)
{
  uint8_t retVal;

  if (globalParameters.tone_start_stop_flag != 0U)
  {
    globalParameters.tone_start_stop_flag = 0;
    /* Release control of the radio FSM through the test bus */
    RRM->DTB5_DIG_ENG = 0x00;
    uint32_t *rrm_udra_test = ((uint32_t *)&RRM->RRM_CTRL) + 0x01;
    *rrm_udra_test = 0x00;
    retVal = 0;
  }
  else
  {
    retVal = 1;
  }
  return retVal;
}


/**
  * @brief  Encrypts plain text data using AES encryption with given input key and
  *         128 bit block size
  * @param  Key: encryption key to be used.
  * @param  plainData: text data to be encrypted.
  * @param  cypherData: contains the encrypted data.
  * @retval None
  */
void HAL_RADIO_EncryptPlainData(uint8_t *Key, uint8_t *plainData, uint8_t *cypherData)
{
  uint32_t key[4] ;
  uint32_t cleartext[4] ;
  uint32_t ciphertext[4] ;
  volatile uint32_t ii ;

  for (uint8_t i = 0; i < 4; i++)
  {
    key[i] = ((uint32_t)Key[i * 4]) | ((uint32_t)Key[i * 4 + 1]) << 8 | ((uint32_t)Key[i * 4 + 2]) << 16 | ((uint32_t)Key[ i * 4 + 3]) << 24;
    cleartext[i] = ((uint32_t)plainData[i * 4]) | ((uint32_t)plainData[i * 4 + 1]) << 8 | ((uint32_t)plainData[i * 4 + 2]) << 16 | ((uint32_t)plainData[i * 4 + 3]) << 24;
  }

  BLUE->MANAESKEY0REG = key[3];
  BLUE->MANAESKEY1REG = key[2];
  BLUE->MANAESKEY2REG = key[1];
  BLUE->MANAESKEY3REG = key[0];

  BLUE->MANAESCLEARTEXT0REG = cleartext[3];
  BLUE->MANAESCLEARTEXT1REG = cleartext[2];
  BLUE->MANAESCLEARTEXT2REG = cleartext[1];
  BLUE->MANAESCLEARTEXT3REG = cleartext[0];

  BLUE->MANAESCMDREG = 1;

  ii = 0 ;
  while ((BLUE->MANAESSTATREG == 0) && ii < 100)
  {
    ii++;
  }

  ciphertext[0] = BLUE->MANAESCIPHERTEXT3REG;
  ciphertext[1] = BLUE->MANAESCIPHERTEXT2REG;
  ciphertext[2] = BLUE->MANAESCIPHERTEXT1REG;
  ciphertext[3] = BLUE->MANAESCIPHERTEXT0REG;

  for (uint8_t i = 0; i < 4; i++)
  {
    cypherData[i * 4] = ((uint8_t)ciphertext[i]);
    cypherData[i * 4 + 1] = (uint8_t)(ciphertext[i] >> 8);
    cypherData[i * 4 + 2] = (uint8_t)(ciphertext[i] >> 16);
    cypherData[i * 4 + 3] = (uint8_t)(ciphertext[i] >> 24);
  }

  return ;
}


/**
  * @brief  This routine sets the network ID field for packet transmission and filtering for the receiving.
  *         Only two devices with same networkID can communicate with each other.
  * @param  ID: network ID based on bluetooth specification:
  *           1. It shall have no more than six consecutive zeros or ones.
  *           2. It shall not have all four octets equal.
  *           3. It shall have no more than 24 transitions.
  *           4. It shall have a minimum of two transitions in the most significant six bits.
  *
  * @retval uint8_t: return value
  *           - 0x00 : Success.
  *           - 0xC0 : Invalid parameter.
  */
uint8_t HAL_RADIO_SetNetworkID(uint32_t ID)
{
  networkID = ID;
  return 0;
}


/**
  * @brief  This routine sends a packet on a specific channel and at a specific time.
  * @param  channel: BLE channel index between 0 to 39.
  * @param  wakeup_time: Time of transmission in us. This is relative time regarding now.
  *         Minimum wakeup_time of 230 us. TBR
  * @param  txBuffer: Pointer to TX data buffer. Second byte of this buffer must be the length of the data.
  * @param  Callback: This function is being called as data routine.
  *         First ActionPacket is current action packet and the second one is next action packet.
  * @retval uint8_t return value
  *           - 0x00 : Success.
  *           - 0xC0 : Invalid parameter.
  *           - 0xC4 : Radio is busy, receiving has not been triggered.
  */
uint8_t HAL_RADIO_SendPacket(uint8_t channel, uint32_t wakeup_time, uint8_t *txBuffer,
                             uint8_t (*Callback)(ActionPacket *, ActionPacket *))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy;
  uint32_t time;

  time = (uint32_t)HAL_RADIO_TIMER_GetCurrentSysTime() + HAL_RADIO_TIMER_UsToSystime(wakeup_time);

  if (channel > 39)
  {
    returnValue = INVALID_PARAMETER_C0;
  }

  if (HAL_RADIO_GetStatus(&dummy) != BLUE_IDLE_0)
  {
    returnValue = RADIO_BUSY_C4;
  }

  if (returnValue == SUCCESS_0)
  {
    uint8_t map[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    HAL_RADIO_SetChannelMap(0, &map[0]);
    HAL_RADIO_SetChannel(0, channel, 0);
    HAL_RADIO_SetTxAttributes(0, networkID, 0x555555);

    aPacket[0].StateMachineNo = 0;
    aPacket[0].ActionTag =  TXRX | PLL_TRIG;
    aPacket[0].WakeupTime = time;
    aPacket[0].MaxReceiveLength = 0; /* does not affect for Tx */
    aPacket[0].data = txBuffer;
    aPacket[0].next_true = NULL_0;
    aPacket[0].next_false = NULL_0;
    aPacket[0].condRoutine = CondRoutineTrue;
    aPacket[0].dataRoutine = Callback;

    HAL_RADIO_SetReservedArea(&aPacket[0]);
    returnValue = HAL_RADIO_MakeActionPacketPending(&aPacket[0]);
  }

  return returnValue;
}


/**
  * @brief  This routine sends a packet on a specific channel and at a certain time then wait for receiving acknowledge.
  * @param  channel: BLE channel index between 0 to 39.
  * @param  wakeup_time: Time of transmission based on us. This is relative time regarding now.
  *         Minimum wakeup_time of 250 us. TBR
  * @param  txBuffer: Pointer to TX data buffer. Second byte of this buffer must be the length of the data.
  * @param  rxBuffer: Pointer to RX data buffer. Second byte of this buffer must be the length of the data.
  * @param  receive_timeout: Time of RX window used to wait for the packet on us.
  * @param  receive_length: number of bytes that the link layer accepts in reception.
  * @param  Callback: This function is being called as data routine.
  *         First ActionPacket is current action packet and the second one is next action packet.
  * @retval uint8_t return value
  *           - 0x00 : Success.
  *           - 0xC0 : Invalid parameter.
  *           - 0xC4 : Radio is busy, receiving has not been triggered.
  */
uint8_t HAL_RADIO_SendPacketWithAck(uint8_t channel, uint32_t wakeup_time, uint8_t *txBuffer, uint8_t *rxBuffer,
                                    uint32_t receive_timeout,
                                    uint8_t receive_length,
                                    uint8_t (*Callback)(ActionPacket *, ActionPacket *))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy;
  uint32_t time;

  time = (uint32_t)HAL_RADIO_TIMER_GetCurrentSysTime() + HAL_RADIO_TIMER_UsToSystime(wakeup_time);

  if (channel > 39)
  {
    returnValue = INVALID_PARAMETER_C0;
  }

  if (HAL_RADIO_GetStatus(&dummy) != BLUE_IDLE_0)
  {
    returnValue = RADIO_BUSY_C4;
  }

  uint8_t map[5] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
  HAL_RADIO_SetChannelMap(0, &map[0]);
  HAL_RADIO_SetChannel(0, channel, 0);
  HAL_RADIO_SetTxAttributes(0, networkID, 0x555555);
  HAL_RADIO_SetGlobalReceiveTimeout(receive_timeout);

  aPacket[0].StateMachineNo = 0;
  aPacket[0].ActionTag = TXRX | PLL_TRIG;
  aPacket[0].WakeupTime = time;
  aPacket[0].MaxReceiveLength = 0; /* does not affect for Tx */
  aPacket[0].data = txBuffer;
  aPacket[0].next_true = &aPacket[1];
  aPacket[0].next_false = &aPacket[1];
  aPacket[0].condRoutine = CondRoutineTrue;
  aPacket[0].dataRoutine = DataRoutineNull;

  aPacket[1].StateMachineNo = 0;
  aPacket[1].ActionTag = 0;
  aPacket[1].WakeupTime = time;
  aPacket[1].MaxReceiveLength = receive_length;
  aPacket[1].data = rxBuffer;
  aPacket[1].next_true = NULL_0;
  aPacket[1].next_false = NULL_0;
  aPacket[1].condRoutine = CondRoutineTrue;
  aPacket[1].dataRoutine = Callback;

  HAL_RADIO_SetReservedArea(&aPacket[0]);
  HAL_RADIO_SetReservedArea(&aPacket[1]);
  returnValue = HAL_RADIO_MakeActionPacketPending(&aPacket[0]);

  return returnValue;
}

#if defined (STM32WB06) || defined (STM32WB07)

static uint8_t CarrierSenseCallback(ActionPacket *p, ActionPacket *next)
{
  return TRUE;
}

/**
  * @brief  This function puts the radio in RX state to read the RSSI.
  * @note   The function uses a busy loop to wait for the RSSI value and then exits
  *         from RX state.
  * @param      channel: BLE channel index between 0 to 39.
  * @param[out] rssi: the measured RSSI value on the channel
  * @retval uint8_t return value
  *           - 0x00 : Success.
  *           - 0xC0 : Invalid parameter.
  *           - 0xC4 : Radio is busy, receiving has not been triggered.
  */
uint8_t HAL_RADIO_CarrierSense(uint8_t channel, int8_t *rssi)
{
  uint8_t ret;
  uint16_t loop = 0;
  uint32_t *DEMOD_DIG_TST_p = (uint32_t *)0x60001564;
  uint32_t end_time;
  static uint8_t buffer[1];

  *rssi = 127;

  uint32_t networkID_tmp = networkID;

  networkID = FAKE_NETWORK_ID;

  ret = HAL_RADIO_ReceivePacket(channel, 300, buffer, 1000, sizeof(buffer), CarrierSenseCallback);

  networkID = networkID_tmp;

  if (ret)
  {
    return ret;
  }

  /* loop variable just to protect from infinite loop */
  while ((RRM->FSM_STATUS_DIG_OUT & RRM_FSM_STATUS_DIG_OUT_STATUS) != 0x1A && loop++ < 60000);
  end_time = WAKEUP->ABSOLUTE_TIME + 20;
  while (TIME_DIFF(end_time, WAKEUP->ABSOLUTE_TIME) > 0);
  *DEMOD_DIG_TST_p = 0x02;
  /* Need to wait at least 3 BLE clocks. In worst case (sysclock = 64 MHz and blesysclk = 16 MHz)
     this means 12 cpu cycles. Some cycles are already used by the call to HAL_RADIO_ReadRSSI()
     and at the beginning of the function. */
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  *rssi = HAL_RADIO_ReadRSSI();
  *DEMOD_DIG_TST_p = 0x00;
  BLUE->CMDREG = BLUE_CMDREG_TXRXSKIP;

  return 0;
}

#elif defined(STM32WB05) || defined(STM32WB09 )

static volatile int8_t _rssi;
static volatile uint8_t _timeout;

static uint8_t CarrierSenseCallback(ActionPacket *p, ActionPacket *next)
{
  _rssi = 127;

  if ((p->status & BLUE_INTERRUPT1REG_DONE) && (p->status & BLUE_STATUSREG_PREVTRANSMIT) == 0 &&
      ((p->status & BLUE_INTERRUPT1REG_RCVOK) || (p->status & BLUE_INTERRUPT1REG_RCVTIMEOUT)
       || (p->status & BLUE_INTERRUPT1REG_RCVCRCERR)))
  {
    _rssi = p->rssi;
  }
  _timeout = TRUE;

  return TRUE;
}

/**
  * @brief  This function puts the radio in RX state to read the RSSI.
  * @note   The function uses a busy loop to wait for the RSSI value and then exits
  *         from RX state.
  * @param      channel: BLE channel index between 0 to 39.
  * @param[out] rssi: the measured RSSI value on the channel
  * @retval uint8_t return value
  *           - 0x00 : Success.
  *           - 0xC0 : Invalid parameter.
  *           - 0xC4 : Radio is busy, receiving has not been triggered.
  */
uint8_t HAL_RADIO_CarrierSense(uint8_t channel, int8_t *rssi)
{
  uint8_t ret;
  uint16_t loop = 0;
  static uint8_t buffer[1];

  *rssi = 127;

  uint32_t networkID_tmp = networkID;

  networkID = FAKE_NETWORK_ID;

  _timeout = FALSE;

  ret = HAL_RADIO_ReceivePacket(channel, 300, buffer, 5, sizeof(buffer), CarrierSenseCallback);

  networkID = networkID_tmp;

  if (ret)
  {
    return ret;
  }

  /* loop variable just to protect from infinite loop */
  while (_timeout == FALSE && loop++ < 60000);
  *rssi = _rssi;

  return 0;
}

#endif

/**
  * @brief  This routine receives a packet on a specific channel and at a certain time.
  * @param  channel: BLE channel index between 0 to 39.
  * @param  wakeup_time: Time of transmission based on us. This is relative time regarding now.
  *         Minimum wakeup_time of 230 us. TBR
  * @param  rxBuffer: Pointer to RX data buffer. Second byte of this buffer must be the length of the data.
  * @param  receive_timeout: Time of RX window used to wait for the packet on us.
  * @param  receive_length: number of bytes that the link layer accepts in reception.
  * @param  Callback: This function is being called as data routine.
  *         First ActionPacket is current action packet and the second one is next action packet.
  * @retval uint8_t return value
  *           - 0x00 : Success.
  *           - 0xC0 : Invalid parameter.
  *           - 0xC4 : Radio is busy, receiving has not been triggered.
  */
uint8_t HAL_RADIO_ReceivePacket(uint8_t channel, uint32_t wakeup_time, uint8_t *rxBuffer, uint32_t receive_timeout,
                                uint8_t receive_length,
                                uint8_t (*Callback)(ActionPacket *, ActionPacket *))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy;
  uint32_t time;
  time = (uint32_t)HAL_RADIO_TIMER_GetCurrentSysTime() + HAL_RADIO_TIMER_UsToSystime(wakeup_time);

  if (channel > 39)
  {
    returnValue = INVALID_PARAMETER_C0;
  }

  if (HAL_RADIO_GetStatus(&dummy) != BLUE_IDLE_0)
  {
    returnValue = RADIO_BUSY_C4;
  }

  if (returnValue == SUCCESS_0)
  {
    uint8_t map[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    HAL_RADIO_SetChannelMap(0, &map[0]);
    HAL_RADIO_SetChannel(0, channel, 0);
    HAL_RADIO_SetTxAttributes(0, networkID, 0x555555);
    HAL_RADIO_SetGlobalReceiveTimeout(receive_timeout);


    aPacket[0].StateMachineNo = 0;
    aPacket[0].ActionTag =  PLL_TRIG;
    aPacket[0].WakeupTime = time;
    aPacket[0].MaxReceiveLength = receive_length;
    aPacket[0].data = rxBuffer;
    aPacket[0].next_true = NULL_0;
    aPacket[0].next_false = NULL_0;
    aPacket[0].condRoutine = CondRoutineTrue;
    aPacket[0].dataRoutine = Callback;

    HAL_RADIO_SetReservedArea(&aPacket[0]);
    returnValue = HAL_RADIO_MakeActionPacketPending(&aPacket[0]);
  }

  return returnValue;
}

/**
  * @brief  This routine receives a packet on a specific channel and at a certain time.
  *         Then sends a packet as an acknowledgment.
  * @param  channel: BLE channel index between 0 to 39.
  * @param  wakeup_time: time of transmission based on us. This is relative time regarding now.
  *         Minimum wakeup_time of 250 us. TBR
  * @param  rxBuffer: points to received data buffer. second byte of this buffer determines the length of the data.
  * @param  txBuffer: points to data buffer to send. second byte of this buffer must be the length of the buffer.
  * @param  receive_timeout: Time of RX window used to wait for the packet on us.
  * @param  receive_length: number of bytes that the link layer accepts in reception.
  * @param  Callback: This function is being called as data routine.
  *         First ActionPacket is current action packet and the second one is next action packet.
  * @retval uint8_t return value
  *           - 0x00 : Success.
  *           - 0xC0 : Invalid parameter.
  *           - 0xC4 : Radio is busy, receiving has not been triggered.
  */
uint8_t HAL_RADIO_ReceivePacketWithAck(uint8_t channel, uint32_t wakeup_time, uint8_t *rxBuffer, uint8_t *txBuffer,
                                       uint32_t receive_timeout,
                                       uint8_t receive_length,
                                       uint8_t (*Callback)(ActionPacket *, ActionPacket *))
{
  uint8_t returnValue = SUCCESS_0;
  uint32_t dummy;
  uint32_t time;

  time = (uint32_t)HAL_RADIO_TIMER_GetCurrentSysTime() + HAL_RADIO_TIMER_UsToSystime(wakeup_time);

  if (channel > 39)
  {
    returnValue = INVALID_PARAMETER_C0;
  }

  if (HAL_RADIO_GetStatus(&dummy) != BLUE_IDLE_0)
  {
    returnValue = RADIO_BUSY_C4;
  }

  if (returnValue == SUCCESS_0)
  {
    uint8_t map[5] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

    HAL_RADIO_SetChannelMap(0, &map[0]);
    HAL_RADIO_SetChannel(0, channel, 0);
    HAL_RADIO_SetTxAttributes(0, networkID, 0x555555);
    HAL_RADIO_SetGlobalReceiveTimeout(receive_timeout);

    aPacket[0].StateMachineNo = 0;
    aPacket[0].ActionTag =  PLL_TRIG;
    aPacket[0].WakeupTime = time;
    aPacket[0].MaxReceiveLength = receive_length;
    aPacket[0].data = rxBuffer;
    aPacket[0].next_true = &aPacket[1];
    aPacket[0].next_false = NULL_0;
    aPacket[0].condRoutine = CondRoutineRxTrue;
    aPacket[0].dataRoutine = Callback;

    aPacket[1].StateMachineNo = 0;
    aPacket[1].ActionTag =  TXRX;
    aPacket[1].WakeupTime = time;
    aPacket[1].MaxReceiveLength = 0; /* does not affect for Tx */
    aPacket[1].data = txBuffer;
    aPacket[1].next_true = NULL_0;
    aPacket[1].next_false = NULL_0;
    aPacket[1].condRoutine = CondRoutineTrue;
    aPacket[1].dataRoutine = Callback;

    HAL_RADIO_SetReservedArea(&aPacket[0]);
    HAL_RADIO_SetReservedArea(&aPacket[1]);
    returnValue = HAL_RADIO_MakeActionPacketPending(&aPacket[0]);
  }

  return returnValue;
}

#endif /* USE_RADIO_PROPRIETARY_DRIVER */

/**
  * @brief RADIO MSP Init
  * @param  hradio pointer to a RADIO_HandleTypeDef structure that contains
  *         the configuration information for RADIO module
  * @retval None
  */
__weak void HAL_RADIO_MspInit(RADIO_HandleTypeDef *hradio)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hradio);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RADIO_MspInit could be implemented in the user file
   */
}

/**
  * @brief RADIO MSP DeInit
  * @param  hradio pointer to a RADIO_HandleTypeDef structure that contains
  *         the configuration information for RADIO module
  * @retval None
  */
__weak void HAL_RADIO_MspDeInit(RADIO_HandleTypeDef *hradio)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hradio);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RADIO_MspDeInit could be implemented in the user file
   */
}

__weak void HAL_RADIO_TxRxCallback(uint32_t flags)
{
}


__weak void HAL_RADIO_TxRxSeqCallback(void)
{
}

void HAL_RADIO_TXRX_IRQHandler(void)
{
  uint32_t blue_status = BLUE->STATUSREG;
  uint32_t blue_interrupt = BLUE->INTERRUPT1REG;

  /** clear all pending interrupts */
  BLUE->INTERRUPT1REG = blue_interrupt;

  HAL_RADIO_TIMER_EndOfRadioActivityIsr();

#if (USE_RADIO_PROPRIETARY_DRIVER == 1)
  HAL_RADIO_ActionPacketIsr(blue_status | blue_interrupt);
#endif

  HAL_RADIO_TxRxCallback(blue_status | blue_interrupt);

  HAL_RADIO_TIMER_RadioTimerIsr();

  /* If the device is configured with
     System clock = 64 MHz and BLE clock = 16 MHz
     a register read is necessary to end fine
     the clear interrupt register operation,
     due the AHB down converter latency */
  blue_interrupt = BLUE->INTERRUPT1REG;
}


void HAL_RADIO_TXRX_SEQ_IRQHandler(void)
{
  HAL_RADIO_TxRxSeqCallback();
}

/**
  * @}
  */
#endif /* HAL_RADIO_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
