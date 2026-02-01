/**
  ******************************************************************************
  * @file    stm32wl3x_ll_mrsubg.h
  * @author  GPM Application Team
  * @brief   Header file of MRSUBG LL module.
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
#ifndef STM32WL3x_LL_MRSUBG_H
#define STM32WL3x_LL_MRSUBG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x.h"
#include "stm32wl3x_ll_utils.h"

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

/** @defgroup MRSUBG_LL MRSUBG
  * @{
  */

/** @defgroup MRSUBG_LL_Private_Constants MRSUBG Private Constants
  * @{
  */

/* Legacy aliases */
#if defined(IS_169MHZ)
#define STM32WL33XA
#endif /* IS_169MHZ */

#if defined(STM32WL33XA)
/* WL33xA */
#define LOW_BAND_FACTOR       20  /*!< Band select factor for middle band. Factor B in the equation of the user manual */
#define HIGH_BAND_FACTOR      8   /*!< Band select factor for high band. Factor B in the equation of the user manual */

#define LOW_BAND_LOWER_LIMIT    159200000   /*!< Lower limit of the low band */
#define LOW_BAND_UPPER_LIMIT    185600000   /*!< Upper limit of the low band */
#define HIGH_BAND_LOWER_LIMIT   398000000   /*!< Lower limit of the high band */
#define HIGH_BAND_UPPER_LIMIT   464000000   /*!< Upper limit of the high band */
#else
#if defined(STM32WL3RX)
/* WL3x including WL3Rx at 315 MHz */
#define LOW_LOW_BAND_FACTOR   12  /*!< Band select factor for middle band. Factor B in the equation of the user manual */
#endif /* STM32WL3RX */

#define LOW_BAND_FACTOR       8   /*!< Band select factor for middle band. Factor B in the equation of the user manual */
#define HIGH_BAND_FACTOR      4   /*!< Band select factor for high band. Factor B in the equation of the user manual */

#if defined(STM32WL3RX)
#define LOW_LOW_BAND_LOWER_LIMIT    275500000   /*!< Lower limit of the low low band */
#define LOW_LOW_BAND_UPPER_LIMIT    318500000   /*!< Upper limit of the low low band */
#endif /* STM32WL3RX */

#define LOW_BAND_LOWER_LIMIT    413000000   /*!< Lower limit of the low band */
#define LOW_BAND_UPPER_LIMIT    479000000   /*!< Upper limit of the low band */
#define HIGH_BAND_LOWER_LIMIT   826000000   /*!< Lower limit of the high band */
#define HIGH_BAND_UPPER_LIMIT   958000000   /*!< Upper limit of the high band */
#endif /* STM32WL33XA */

#define MINIMUM_DATARATE    100 /*!< Minimum datarate supported by STM32WL3x 100 bps */
#define MAXIMUM_DATARATE    300000  /*!< Maximum datarate supported by STM32WL3x 300 ksps (600 kbps) */

/* If we use SEQ_F as the only flag bit to match on, \
then a match can never occur because SEQ_F is only set when the sequencer terminates. */
#define SEQ_MASK_NEVER_MATCH MR_SUBG_GLOB_STATUS_RFSEQ_IRQ_STATUS_SEQ_F

#define SEQ_MASK_ALWAYS_MATCH 0x00000000 /* The Sequencer automatically matches a null mask */

/**
  * @}
  */

/** @defgroup MRSUBG_LL_Exported_Macros MRSUBG Exported Macros
  * @{
  */

#define IS_PREAMBLE_LEN(VAL)          (VAL<=2046)
#define IS_POSTAMBLE_LEN(VAL)         (VAL<=126)
#define IS_SYNC_LEN(VAL)                (VAL<=32)
#define IS_FRAME_LEN(VAL)               (VAL>=2) && (VAL<=2047)
#define IS_PREAMBLE_15_4G_LEN(VAL)      (((VAL)>=4) && ((VAL)<=64))

#define IS_MODULATION_15_4G(MOD) (((MOD) == MOD_2FSK) || ((MOD) == MOD_4FSK))

#define IS_FCS_TYPE(TYPE)        (((TYPE) == FCS_16BIT) || \
                                  ((TYPE) == FCS_32BIT))

#define IS_FEC_TYPE(TYPE)       (((TYPE) == FEC_15_4_G_NONE) || \
                                 ((TYPE) == FEC_15_4_G_NRNSC) || \
                                 ((TYPE) == FEC_15_4_G_RSC) || \
                                 ((TYPE) == FEC_15_4_G_RSC_Interleaving))


#define IS_WMBUS_SUBMODE(MODE)   (((MODE) == WMBUS_SUBMODE_S1_S2_LONG_HEADER) || \
                                  ((MODE) == WMBUS_SUBMODE_NOT_CONFIGURED) || \
                                  ((MODE) == WMBUS_SUBMODE_S1_M_S2_T2_OTHER_TO_METER) || \
                                  ((MODE) == WMBUS_SUBMODE_T1_T2_METER_TO_OTHER) || \
                                  ((MODE) == WMBUS_SUBMODE_R2_SHORT_HEADER))

/** @brief Macro that checks if SELECTION is a MRSubG_WhiteningBeforeFECType */
#define IS_WHITEFEC_SELECTION(SELECTION) (((SELECTION) == FEC_THEN_WHITENING) || ((SELECTION) == WHITENING_THEN_FEC))

#define PREAMBLE_BYTE(v)        (4*v)
#define SYNC_BYTE(v)            ((8*v)-1)
/**
  * @}
  */


/** @defgroup MRSUBG_LL_Exported_Types MRSUBG Exported Types
  * @{
  */
/**
  * @brief  STM32WL3x MRSUBG PA modes
  */
typedef enum
{
  PA_LEGACY     = 0x00, /* legacy mode */
  PA_FIR        = 0x01, /* FIR active (to be used in ASK/OOK modulation only) */
  PA_DIRECT     = 0x02  /* Direct mode */
} MRSubG_PAMode;

/**
  * @brief  STM32WL3x PA drive modes
  */
typedef enum
{
  PA_DRV_TX         = 0x01, /* up to 10dBm */
  PA_DRV_TX_HP      = 0x02, /* up to 14dBm */
  PA_DRV_TX_TX_HP   = 0x03  /* up to 20dBm */
} MRSubG_PA_DRVMode;

/**
  * @enum SQI_Threshold
  * @brief Defines the SQI threshold for SYNC word detection tolerance.
  *
  * This enum represents the allowed number of bit errors tolerated when detecting
  * the SYNC word in the SQI (SYNC Quality Indicator) threshold for SYNC word detection tolerance. The value corresponds
  * to the maximum number of bit mismatches accepted between the detected SYNC word
  * and the expected SYNC word.
  *
  * The SQI_THR field occupies bits 18:16 in the relevant control register.
  *
  * Values:
  *  - SQI_THR_PERFECT_MATCH (0): No bit errors allowed; exact match required.
  *  - SQI_THR_1_BIT_ERROR   (1): Up to 1 bit error tolerated.
  *  - ...
  *  - SQI_THR_7_BIT_ERROR   (7): Up to 7 bit errors tolerated.
  */
typedef enum
{
  SQI_THR_PERFECT_MATCH = 0,  /* 0 bit error accepted */
  SQI_THR_1_BIT_ERROR   = 1,  /* 1 bit error accepted */
  SQI_THR_2_BIT_ERROR   = 2,  /* 2 bits error accepted */
  SQI_THR_3_BIT_ERROR   = 3,  /* 3 bits error accepted */
  SQI_THR_4_BIT_ERROR   = 4,  /* 4 bits error accepted */
  SQI_THR_5_BIT_ERROR   = 5,  /* 5 bits error accepted */
  SQI_THR_6_BIT_ERROR   = 6,  /* 6 bits error accepted */
  SQI_THR_7_BIT_ERROR   = 7   /* 7 bits error accepted */
} SQI_Threshold;

/**
  * @brief  STM32WL3x Commands codes enumeration
  */
typedef enum
{
  CMD_NOP               = ((uint8_t)(0x00)),  /* No action. This 'no' command can be requested at any time, \
                                              whatever the on-going command or in IDLE */
  CMD_TX                = ((uint8_t)(0x01)),  /* Start a TX sequence */
  CMD_RX                = ((uint8_t)(0x02)),  /* Start a RX sequence */
  CMD_LOCKRX            = ((uint8_t)(0x03)),  /* Start a RF sequence up to PLL locked based on RX frequency */
  CMD_LOCKTX            = ((uint8_t)(0x04)),  /* Start a RF sequence up to PLL locked based on TX frequency */
  CMD_SABORT            = ((uint8_t)(0x05)),  /* Stop any on-going RX/TX/LOCKRX/LOCKTX command */
  CMD_CALIB_SAFEASK     = ((uint8_t)(0x0A)),  /* Launch a PA Safe-ASK calibration to get the max safe \
                                              PA code to be used */
  CMD_RELOAD_RX_TIMER   = ((uint8_t)(0x06)),  /* Reload with a new timeout and \
                                              new stop conditions and restart the RX Timer */
  CMD_CALIB_AGC         = ((uint8_t)(0x0B))   /* Start needed HW features to run an AGC_ATTEN trim \
                                              sequence at SW level */
} MRSubGCmd;

/**
  * @brief  STM32WL3x MRSUBG FSM state enumaration
  */
typedef enum
{
  STATE_IDLE = 0x00,
  STATE_ENA_RF_REG = 0x01,
  STATE_WAIT_ACTIVE2 = 0x02,
  STATE_ACTIVE2 = 0x03,
  STATE_ENA_CURR = 0x04,
  STATE_SYNTH_SETUP = 0x05,
  STATE_CALIB_VCO = 0x06,
  STATE_LOCKRXTX = 0x07,
  STATE_LOCKONTX = 0x08,
  STATE_EN_PA = 0x09,
  STATE_TX = 0x0A,
  STATE_PA_DWN_ANA = 0x0B,
  STATE_END_TX = 0x0C,
  STATE_LOCKONRX = 0x0D,
  STATE_EN_RX = 0x0E,
  STATE_EN_LNA = 0x0F,
  STATE_RX = 0x10,
  STATE_END_RX = 0x11,
  STATE_SYNTH_PWDN = 0x12
} MRSubGFSMState;

/**
  * @brief  BT Values for GFSK
  */
typedef enum
{
  BT_1 = 0,
  BT_05 = 1
} MRSubG_BTSelect;

/**
  * @brief  STM32WL3x Transmission modes
  */
typedef enum
{
  ISI_EQ_DISABLED = 0x00,
  ISI_EQ_SP = 0x01,
  ISI_EQ_DP = 0x02
} MRSubG_ISIEQMode;

/**
  * @brief  STM32WL3x Transmission modes
  */
typedef enum
{
  TX_NORMAL             = 0x00, /* Only payload is provided through RAM buffers Rest of the frame built from \
                                configuration registers (PREAMBLE, SYNC, CRC...). */
  TX_DIRECT_BUFFERS     = 0x01, /* Full bit stream (including PREAMBLE, SYNC, CRC...) to be \
                                provided through RAM buffers. */
  TX_DIRECT_GPIO        = 0x02, /* Full bit stream (including PREAMBLE, SYNC, CRC...) to be \
                                provided serially through the TX DATA GPIO. */
  TX_PN                 = 0x03  /* Internal PN generator send a polynomial bit stream on the antenna. */
} MRSubGTXMode;

/**
  * @brief  STM32WL3x Reception modes
  */
typedef enum
{
  RX_NORMAL             = 0x00, /* Only payload is stored into the RAM buffers. \
                                CRC and packet length are readable in dedicated status registers */
  RX_DIRECT_BUFFERS     = 0x01, /* Full bit stream is stored into the RAM buffers. */
  RX_DIRECT_GPIO        = 0x02, /* Full bit stream is provided serially through the RX DATA GPIO */
  RX_IQ_SAMPLING        = 0x03, /* Raw I/Q sampling taken at the output of the Channel filter \
                                inside the demodulator are stored in RAM. */
  RX_FREQDETEC_SAMPLING = 0x04, /* Raw data taken at the output of the frequency detector inside the \
                                demodulator (detection of the instantaneous frequency changes) are stored in RAM. */
  RX_SOFTBIT_SAMPLING   = 0x05  /* Raw data taken at the output of the post-filter inside the \
                                demodulator (soft bits before the 0/1 detection) are stored in RAM. */
} MRSubGRXMode;

/**
  * @brief  STM32WL3x preamble pattern enumeration
  */
typedef enum
{
  PRE_SEQ_0101 = 0x00, /* Suitable for 2-(G)FSK and ASK/OOK */
  PRE_SEQ_1010 = 0x01, /* Suitable for 2-(G)FSK and ASK/OOK */
  PRE_SEQ_0011 = 0x02, /* Suitable for 2-(G)FSK and ASK/OOK \
                        (not recommended - not the most convenient for the receiver) */
  PRE_SEQ_1100 = 0x03, /* Suitable for 2-(G)FSK and ASK/OOK \
                        (not recommended - not the most convenient for the receiver) */
  PRE_SEQ_0111 = 0x00, /* Suitable for 4-(G)FSK */
  PRE_SEQ_0010 = 0x01, /* Suitable for 4-(G)FSK */
  PRE_SEQ_1101 = 0x02, /* Suitable for 4-(G)FSK */
  PRE_SEQ_1000 = 0x03  /* Suitable for 4-(G)FSK */
} MRSubG_PreambleSeq;

/**
  * @brief  STM32WL3x preamble pattern enumeration
  */
typedef enum
{
  POST_SEQ_0101 = 0x00, /* 010101... */
  POST_SEQ_1010 = 0x01, /* 101010... */
  POST_SEQ_OTHER = 0x02  /* depends on last payload/CRC bit. If 0: 101010... - If 1: 010101... */
} MRSubG_PostambleSeq;

/**
  * @brief  STM32WL3x packet coding options
  */
typedef enum
{
  CODING_NONE = 0x00,   /* None */
  CODING_FEC = 0x01,    /* FEC in TX / Viterbi in RX */
  CODING_3o6 = 0x02,    /* 3of6 coding */
  CODING_MANCHESTER = 0x03  /* Manchester coding */
} MRSubG_PcktCoding;

/**
  * @brief  Whitening before FEC feature
  */
typedef enum
{
  FEC_THEN_WHITENING    = 0,
  WHITENING_THEN_FEC    = 1
} MRSubG_WhiteningBeforeFECType;

/**
  * @brief Manchester encoding polarity.
  *  0: "0" is encoded with "01" and "1" is encoded with "10"
  *  1: "0" is encoded with "10" and "1" is encoded with "01"
  */
typedef enum
{
  MANCHESTER_TYPE0 = 0,
  MANCHESTER_TYPE1 = 1
} MRSubG_ManchesterPolarity;

/**
  * @brief  CRC length in bytes enumeration.
  */
typedef enum
{
  PKT_NO_CRC               = 0x00, /*!< No CRC                              */
  PKT_CRC_MODE_8BITS       = 0x01, /*!< CRC length 8 bits  - poly: 0x07     */
  PKT_CRC_MODE_16BITS_1    = 0x02, /*!< CRC length 16 bits - poly: 0x8005   */
  PKT_CRC_MODE_16BITS_2    = 0x03, /*!< CRC length 16 bits - poly: 0x1021   */
  FCS_16BIT              = 0x03, /*!< CRC length 16 bits - poly: 0x1021   */
  PKT_CRC_MODE_24BITS      = 0x04, /*!< CRC length 24 bits - poly: 0x864CFB */
  PKT_CRC_MODE_32BITS      = 0x05, /*!< CRC length 32 bits - poly: 0x04C11DB7 */
  FCS_32BIT              = 0x05, /*!< CRC length 32 bits - poly: 0x04C11DB7 */
} MRSubG_PcktCrcMode;

/**
  * @brief Fixed or Variable length mode.
  * 0: FIXED length mode (no LENGTH field added in the frame in TX and no decode in RX)
  * 1: VARIABLE length mode (LENGTH field put in the frame in TX and decoded in RX)
  */
typedef enum
{
  FIXED   = 0,
  VARIABLE  = !FIXED
} MRSubG_LengthMode;

/**
  * @brief 1 or 2 bytes length width.
  * 0: LENGTH bit field is defined on 1 byte
  * 1: LENGTH bit field is defined on 2 bytes
  */
typedef enum
{
  BYTE_LEN_1  = 0,
  BYTES_LEN_2   = 1
} MRSubG_LenWidthhMode;

/**
  * @brief  STM32WL3x Frequency Band IDs
  */
typedef enum
{
  FQCY_STANDARD   = 0x00, /* Standard band */
  FQCY_169MHZ     = 0x03  /* 169 MHz band */
} MRSubG_Frequency_ID;

/**
  * @brief Sequencer flag bits
  */
typedef enum
{
  /* Indicating if the low power mode was allowed during the wait interval since last SeqAction execution */
  SEQ_FLAG_SLEEPENABLE = 0x01,

  /* Enable/disable a force reload of the Static registers even if no reset occurs since last reload */
  SEQ_FLAG_FORCERELOAD = 0x02,

  /* Clear the internal seq_event_status bus before to start the SeqAction */
  SEQ_FLAG_CLEAREVENTS = 0x04

} MRSubG_Sequencer_Flags;

typedef struct MRSubG_Sequencer_ActionConfiguration_t MRSubG_Sequencer_ActionConfiguration_t;

/**
  * @brief Sequencer ActionConfiguration RAM table structure
  */
struct MRSubG_Sequencer_ActionConfiguration_t
{
  /*
   * NextAction1
   */
  /** Pointer to NextAction1, executed upon NextAction1Mask match. */
  MRSubG_Sequencer_ActionConfiguration_t *NextAction1Ptr;

  /** Time to wait before NextAction1 execution, in interpolated absolute time units. */
  uint32_t NextAction1Interval;

  /** Bitmask for NextAction1 - if SubGHz status register against matches against this mask, \
    * NextAction1 is performed next. */
  uint32_t NextAction1Mask;

  /** Configuration flags (ForceClearEvents, ForceReload and SleepEn) for sequencer hardware, \
    * set if NextAction1 is performed next. */
  uint32_t NextAction1Ctrl;

  /* NextAction2 */
  /** Pointer to NextAction2, executed upon NextAction1Mask match. */
  MRSubG_Sequencer_ActionConfiguration_t *NextAction2Ptr;

  /** Time to wait before NextAction2 execution, in interpolated absolute time units. */
  uint32_t NextAction2Interval;

  /** Bitmask for NextAction2 - if SubGHz status register against matches against this mask, \
    * NextAction2 is performed next. */
  uint32_t NextAction2Mask;

  /** Configuration flags (ForceClearEvents, ForceReload and SleepEn) for sequencer hardware, \
    * set if NextAction2 is performed next. */
  uint32_t NextAction2Ctrl;

  /** Time to wait for either NextAction1Mask or NextAction2Mask match before aborting, \
    * in interpolated absolute time units.
    *  Set to 0 for no timeout. */
  uint32_t ActionTimeout;

  /** Dynamic Register Configuration, applied for the current action. */
  MR_SUBG_GLOB_DYNAMIC_TypeDef DynamicConfigReg;
};

/**
  * @brief Sequencer GlobalConfiguration RAM table structure
  */
typedef struct
{
  /** Pointer to first ActionConfiguration */
  volatile MRSubG_Sequencer_ActionConfiguration_t *ActionConfigPtr;

  /** Configuration flags (ForceClearEvents, ForceReload and SleepEn) for sequencer hardware. */
  volatile uint32_t Flags;

  /** SubGHz static configuration registers. */
  MR_SUBG_GLOB_STATIC_TypeDef StaticConfigReg;
} MRSubG_Sequencer_GlobalConfiguration_t;

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup MRSUBG_LL_Exported_Functions MRSUBG Exported Functions
  * @{
  */

/**
  * @brief  Set the PA Mode.
  * @param  paMode the PA Mode.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetPAMode(MRSubG_PAMode paMode)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_MODE, paMode);
}

/**
  * @brief  Get the PA Mode.
  * @retval The PA Mode.
  */
__STATIC_INLINE MRSubG_PAMode LL_MRSubG_GetPAMode(void)
{
  return (MRSubG_PAMode)READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_MODE);
}

/**
  * @brief  Set the PA Drive Mode.
  * @param  paDrvMode the PA Drive Mode.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetPADriveMode(MRSubG_PA_DRVMode paDrvMode)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_DRV_MODE, paDrvMode);
}

/**
  * @brief  Get the PA Drive Mode.
  * @retval The PA Drive Mode.
  */
__STATIC_INLINE MRSubG_PA_DRVMode LL_MRSubG_GetPADriveMode(void)
{
  return (MRSubG_PA_DRVMode) READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_DRV_MODE);
}

/**
  * @brief  Force the SYNC word to be formatted as 2-(G)FSK bit mapping instead of 4-(G)FSK.
  * @param  forceSync DISABLE: the SYNC word is treated in 4-(G)FSK mapping as the rest of the frame.
  *                   ENABLE: the SYNC word of the frame is mapped as follows
  *                       '1' is mapped to +Fdev; '0' is mapped to -Fdev for constellation mapping = 0 and 1
  *                       '1' is mapped to -Fdev; '0' is mapped to +Fdev for constellation mapping = 2 and 3
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_Force2FSKSync(FunctionalState forceSync)
{
  if (forceSync == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_FORCE_2FSK_SYNC_MODE);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_FORCE_2FSK_SYNC_MODE);
}

/**
  * @brief  Set the CONST_MAP configuration for
  * 2-(G)FSK or 4-(G)FSK
  * @param  nConMap the configuration.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetConstellationMapping(uint8_t nConMap)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_CONST_MAP, nConMap);
}

/**
  * @brief Invert bit to symbol mapping for 4(G)FSK
  * @param  xNewState new state for FOUR_FSK_SYM_SWAP bit
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SwapSymbolMapping(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_FOUR_FSK_SYM_SWAP);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_FOUR_FSK_SYM_SWAP);
}

/**
  * @brief Select BT value for GFSK
  * @param  bSel BT value
  *  This value is type of @ref MRSubG_BTSelect.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetBTSel(MRSubG_BTSelect bSel)
{
  if (bSel == BT_05)
  {
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_BT_SEL);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->MOD0_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD0_CONFIG_BT_SEL);
}

/**
  * @brief Select BT value for GFSK
  * @param  xNewState BT value
  *  This value is type of @ref MRSubG_BTSelect.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetFrequencyInterpolator(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_MOD_INTERP_EN);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_MOD_INTERP_EN);
}

/**
  * @brief Set the ISI cancellation equalizer
  * @param  isiEq the Equalizer value
  *  This value is type of @ref MRSubG_ISIEQMode.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetISIEqualizer(MRSubG_ISIEQMode isiEq)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_AS_EQU_CTRL, isiEq);
}

/**
  * @brief  Send a specific command to the STM32WL3x.
  * @param  xCommandCode code of the command to send.
           This parameter can be any value of @ref MRSubGCmd.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_StrobeCommand(MRSubGCmd xCommandCode)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->COMMAND, MR_SUBG_GLOB_DYNAMIC_COMMAND_COMMAND_ID, xCommandCode);
}

/**
  * @brief  Set the TX_MODE field of the PCKT_CTRL register.
  * @param  txMode The TX Mode.
  *      This parameter can be any value of @ref MRSubGTXMode.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetTXMode(MRSubGTXMode txMode)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_TX_MODE, txMode);
}

/**
  * @brief  Sets the RX_MODE field of PCKT_CTRL register.
  * @param  rxMode the rx mode.
  *      This parameter can be any value of @ref MRSubGRXMode.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetRXMode(MRSubGRXMode rxMode)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_RX_MODE, rxMode);
}

/**
  * @brief  Sets the channel number.
  * @param  cChannel the channel number.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetChannel(uint8_t cChannel)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->ADDITIONAL_CTRL, MR_SUBG_GLOB_DYNAMIC_ADDITIONAL_CTRL_CH_NUM, cChannel);
}

/**
  * @brief  Returns the actual channel number.
  * @retval uint8_t Actual channel number.
  */
__STATIC_INLINE uint8_t LL_MRSubG_GetChannel(void)
{
  return READ_REG(MR_SUBG_GLOB_DYNAMIC->ADDITIONAL_CTRL) & MR_SUBG_GLOB_DYNAMIC_ADDITIONAL_CTRL_CH_NUM;
}

/**
  * @brief  Set the channel spacing factor in channel space register.
  *         The channel spacing is From ~732 Hz to ~187 kHz in 732 Hz steps
  * @param  lChannelSpace the channel spacing expressed in Hz.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetChannelSpace(uint8_t lChannelSpace)
{
  MODIFY_REG_FIELD(
    MR_SUBG_GLOB_DYNAMIC->ADDITIONAL_CTRL,
    MR_SUBG_GLOB_DYNAMIC_ADDITIONAL_CTRL_CH_SPACING,
    lChannelSpace
  );
}

/**
  * @brief  Return the channel space register.
  * @retval uint8_t Channel spacing.
  */
__STATIC_INLINE uint8_t LL_MRSubG_GetChannelSpace(void)
{
  return READ_REG_FIELD(
           MR_SUBG_GLOB_DYNAMIC->ADDITIONAL_CTRL,
           MR_SUBG_GLOB_DYNAMIC_ADDITIONAL_CTRL_CH_SPACING
         );
}

/**
  * @brief  Set the PA_DEGEN_ON bit. This will Enable/Disable a degeneration mode, \
  *         which introduces a pre-distortion to linearize the power control curve.
  * @param  xNewState enable (ENABLE) to enable or disable (DISABLE) the degeneration.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetPADegen(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_RADIO->PA_REG, MR_SUBG_RADIO_PA_REG_PA_DEGEN_ON);
  }
  else
  {
    CLEAR_BIT(MR_SUBG_RADIO->PA_REG, MR_SUBG_RADIO_PA_REG_PA_DEGEN_ON);
  }
}

/**
  * @brief  Returns the actual PA_LEVEL_MAX_INDEX.
  * @retval uint8_t Actual PA_LEVEL_MAX_INDEX. This parameter will be in the range [0:7].
  */
__STATIC_INLINE uint8_t LL_MRSubG_GetPALevelMaxIndex(void)
{
  return READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_LEVEL_MAX_INDEX);
}

/**
  * @brief  Sets a specific PA_LEVEL_MAX_INDEX.
  * @param  cIndex PA_LEVEL_MAX_INDEX to set.
  * @retval None
  */
__STATIC_INLINE void LL_MRSubG_SetPALevelMaxIndex(uint8_t cIndex)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PA_CONFIG, MR_SUBG_GLOB_STATIC_PA_CONFIG_PA_LEVEL_MAX_INDEX, cIndex);
}

/**
  * @brief  Set the Almost Empty threshold for the Databuffer. \
  *         When the number of elements in Databuffer reaches this value an interrupt can can be generated.
  * @param  cThrTx: almost empty threshold.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetAlmostEmptyThresholdTx(uint16_t cThrTx)
{
  /* Writes the Almost Empty threshold for Tx in the corresponding register */
  MODIFY_REG_FIELD(
    MR_SUBG_GLOB_DYNAMIC->DATABUFFER_THR,
    MR_SUBG_GLOB_DYNAMIC_DATABUFFER_THR_TX_ALMOST_EMPTY_THR,
    cThrTx
  );
}

/**
  * @brief  Set the almost full threshold for the Databuffer. \
  *         When the number of elements in Databuffer reaches this value an interrupt can be generated.
  * @param  cThrRx almost full threshold.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetAlmostFullThresholdRx(uint16_t cThrRx)
{
  /* Writes the Almost Full threshold for Tx in the corresponding register */
  MODIFY_REG_FIELD(
    MR_SUBG_GLOB_DYNAMIC->DATABUFFER_THR,
    MR_SUBG_GLOB_DYNAMIC_DATABUFFER_THR_RX_ALMOST_FULL_THR,
    cThrRx
  );
}

/**
  * @brief  Return the RADIO FSM State.
  * @retval Value of RADIO_FSM_STATE register
  */
__STATIC_INLINE MRSubGFSMState LL_MRSubG_GetRadioFSMState(void)
{
  return (MRSubGFSMState)(READ_REG_FIELD(MR_SUBG_GLOB_STATUS->RADIO_FSM_INFO,
                                         MR_SUBG_GLOB_STATUS_RADIO_FSM_INFO_RADIO_FSM_STATE));
}

/**
  * @brief  Set the PREAMBLE field Length.
  * @param  cPreambleLength length of PREAMBLE field in pairs of bits (0 to 2046 bits).
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetPreambleLength(uint16_t cPreambleLength)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_PREAMBLE_LENGTH, cPreambleLength);
}

/**
  * @brief  Return the PREAMBLE field Length.
  * @retval uint16_t Preamble field length in in pairs of bits (0 to 2046 bits).
  */
__STATIC_INLINE uint16_t LL_MRSubG_GetPreambleLength(void)
{
  return READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_PREAMBLE_LENGTH);
}

/**
  * @brief  Set the PREAMBLE pattern to be applied.
  * @param  cPreambleSeq the pattern to apply
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetPreambleSeq(MRSubG_PreambleSeq cPreambleSeq)
{
  MODIFY_REG_FIELD(
    MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
    MR_SUBG_GLOB_STATIC_PCKT_CONFIG_PREAMBLE_SEQ,
    (uint8_t)cPreambleSeq
  );
}

/**
  * @brief  Return the PREAMBLE pattern.
  * @retval MRSubG_PreambleSeq Preamble pattern
  */
__STATIC_INLINE MRSubG_PreambleSeq LL_MRSubG_GetPreambleSeq(void)
{
  return (MRSubG_PreambleSeq)(READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
                                             MR_SUBG_GLOB_STATIC_PCKT_CONFIG_PREAMBLE_SEQ));
}

/**
  * @brief  Set the POSTAMBLE field Length.
  * @param  cPostambleLength length of POSTAMBLE field in pairs of bits (0 to 126 bits).
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetPostambleLength(uint16_t cPostambleLength)
{
  MODIFY_REG_FIELD(
    MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
    MR_SUBG_GLOB_STATIC_PCKT_CONFIG_POSTAMBLE_LENGTH,
    cPostambleLength
  );
}

/**
  * @brief  Return the POSTAMBLE field Length.
  * @retval uint16_t Postamble field length in in pairs of bits (0 to 126 bits).
  */
__STATIC_INLINE uint16_t LL_MRSubG_GetPostambleLength(void)
{
  return READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_POSTAMBLE_LENGTH);
}

/**
  * @brief  Set the POSTAMBLE pattern to be applied.
  * @param  cPostambleSeq the pattern to apply
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetPostamblSeq(MRSubG_PostambleSeq cPostambleSeq)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_POSTAMBLE_SEQ,
                   (uint8_t)cPostambleSeq);
}

/**
  * @brief  Return the POSTAMBLE pattern.
  * @retval MRSubG_PostambleSeq Postamble pattern
  */
__STATIC_INLINE MRSubG_PostambleSeq LL_MRSubG_GetPostambleSeq(void)
{
  return (MRSubG_PostambleSeq)(READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
                                              MR_SUBG_GLOB_STATIC_PCKT_CONFIG_POSTAMBLE_SEQ));
}

/**
  * @brief  Set the SYNC_PRESENT bit.
  * @param  cSyncPresent the enable/disable value for the bit
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetSyncPresent(FunctionalState cSyncPresent)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SYNC_PRESENT, cSyncPresent);
}

/**
  * @brief  Get the SYNC_PRESENT bit.
  * @retval The enable/disable value for the bit.
  */
__STATIC_INLINE FunctionalState LL_MRSubG_GetSyncPresent(void)
{
  return (FunctionalState)(READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
                                          MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SYNC_PRESENT));
}

/**
  * @brief  Set the SECONDARY_SYNC_SEL bit.
       In TX mode: this bit selects which synchro word is sent on the frame between SYNC and SEC_SYNC
         In RX mode: it enables the detection of SEC_SYNC in parallel of SYNC word.
  * @param  cSecondarySync the enable/disable value for the bit
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetSecondarySync(FunctionalState cSecondarySync)
{
  MODIFY_REG_FIELD(
    MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
    MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SECONDARY_SYNC_SEL,
    cSecondarySync
  );
}

/**
  * @brief  Get the SECONDARY_SYNC_SEL bit.
  * @retval The enable/disable value for the bit.
  */
__STATIC_INLINE FunctionalState LL_MRSubG_GetSecondarySync(void)
{
  return (FunctionalState)(READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
                                          MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SECONDARY_SYNC_SEL));
}

/**
  * @brief  Set the SYNC field Length.
  * @param  cSyncLength length of SYNC field in bits.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetSyncLength(uint8_t cSyncLength)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SYNC_LEN, cSyncLength);
}

/**
  * @brief  Return the SYNC field Length.
  * @retval uint8_t Sync field length in bits.
  */
__STATIC_INLINE uint8_t LL_MRSubG_GetSyncLength(void)
{
  return READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_SYNC_LEN);
}

/**
  * @brief  Set the SYNC word.
  * @param  lSyncWord SYNC word given as a 32 bits aligned word.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetSyncWord(uint32_t lSyncWord)
{
  WRITE_REG(MR_SUBG_GLOB_STATIC->SYNC, lSyncWord);
}

/**
  * @brief  Get the SYNC word.
  * @retval The Sync word.
  */
__STATIC_INLINE uint32_t LL_MRSubG_GetSyncWord(void)
{
  return READ_REG(MR_SUBG_GLOB_STATIC->SYNC);
}


/**
  * @brief  Set the SEC_SYNC word.
  * @param  lSecSyncWord SEC_SYNC word given as a 32 bits aligned word.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetSecondarySyncWord(uint32_t lSecSyncWord)
{
  WRITE_REG(MR_SUBG_GLOB_STATIC->SEC_SYNC, lSecSyncWord);
}

/**
  * @brief  Get the SEC_SYNC word.
  * @retval The Secondary Sync word.
  */
__STATIC_INLINE uint32_t LL_MRSubG_GetSecondarySyncWord(void)
{
  return READ_REG(MR_SUBG_GLOB_STATIC->SEC_SYNC);
}

/**
  * @brief  Enable or Disable WHITENING for STM32WL3x packets.
  * @param  xNewState new state for WHITENING mode.
  *         This parameter can be S_ENABLE or S_DISABLE.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_PacketHandlerWhitening(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_WHIT_EN);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_WHIT_EN);
}

/**
  * @brief  Enable or Disable BYTE_SWAP for STM32WL3x packets.
  * @param  xNewState new state for BYTE_SWAP mode.
  *         This parameter can be S_ENABLE or S_DISABLE.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_PacketHandlerByteSwap(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_BYTE_SWAP);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_BYTE_SWAP);
}

/**
  * @brief  Set the Fec and Whitening order
  * @param  xWhitFecOrder new Whitening/FEC order.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_PacketHandlerWhiteningFecOrder(MRSubG_WhiteningBeforeFECType xWhitFecOrder)
{
  if (xWhitFecOrder == WHITENING_THEN_FEC)
  {
    SET_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_WHIT_BF_FEC);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_WHIT_BF_FEC);
}

/**
  * @brief  Set the Whitening initialization value
  * @param  whit_init Whitening initialization value.
  *         In 802.15.4 standard, this initialization seed must be programmed to 0x1FF.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_PacketHandlerSetWhiteningInit(uint16_t whit_init)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_WHIT_INIT, whit_init);
}

/**
  * @brief  Set the type of coding and decoding for the packets.
  * @param  cCoding coding/decoding selection.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_PacketHandlerCoding(MRSubG_PcktCoding cCoding)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_CODING_SEL, cCoding);
}

/**
  * @brief  Set the Manchester type for the packets.
  * @param  manType the Manchester encoding polarity.
  * 0: '0' is encoded with '01' and '1' is encoded with '10'
  * 1: '0' is encoded with '10' and '1' is encoded with '01'
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_PacketHandlerManchesterType(MRSubG_ManchesterPolarity manType)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CTRL, MR_SUBG_GLOB_STATIC_PCKT_CTRL_MANCHESTER_TYPE, manType);
}

/**
  * @brief  Set the CRC mode.
  * @param  xPktCrcMode This parameter can be one among the @ref MRSubG_PcktCrcMode .
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_PacketHandlerSetCrcMode(MRSubG_PcktCrcMode xPktCrcMode)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_CRC_MODE, xPktCrcMode);
}

/**
  * @brief  Get the CRC mode.
  * @retval MRSubG_PcktCrcMode CRC mode in the @ref MRSubG_PcktCrcMode enum.
  */
__STATIC_INLINE MRSubG_PcktCrcMode LL_MRSubG_PacketHandlerGetCrcMode(void)
{
  return (MRSubG_PcktCrcMode)(READ_REG(MR_SUBG_GLOB_STATIC->PCKT_CONFIG) & MR_SUBG_GLOB_STATIC_PCKT_CONFIG_CRC_MODE);
}

/**
  * @brief  Set the PCKTLEN field of the PCKTLEN_CONFIG register.
  * @param  nPacketLen payload length in bytes.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSUBG_SetPacketLength(uint16_t nPacketLen)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->PCKTLEN_CONFIG, MR_SUBG_GLOB_DYNAMIC_PCKTLEN_CONFIG_PCKTLEN, nPacketLen);
}

/**
  * @brief  Get the PCKTLEN field of the PCKTLEN_CONFIG register.
  * @retval Payload length in bytes.
  */
__STATIC_INLINE uint16_t LL_MRSUBG_GetPacketLength(void)
{
  return READ_REG(MR_SUBG_GLOB_DYNAMIC->PCKTLEN_CONFIG) & MR_SUBG_GLOB_DYNAMIC_PCKTLEN_CONFIG_PCKTLEN;
}

/**
  * @brief  Set the FIX_VAR_LEN field of the PCKT_CONFI register.
  * @param  lenType length mode.
  *    0: FIXED length mode (no LENGTH field added in the frame in TX and no decode in RX)
  *    1: VARIABLE length mode (LENGTH field put in the frame in TX and decoded in RX)
  * @retval None.
  */
__STATIC_INLINE void LL_MRSUBG_SetFixedVariableLength(MRSubG_LengthMode lenType)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_FIX_VAR_LEN, lenType);
}

/**
  * @brief  Get the FIX_VAR_LEN field of the PCKT_CONFI register.
  * @retval The Fixed/Variable length mode.
  */
__STATIC_INLINE MRSubG_LengthMode LL_MRSUBG_GetFixedVariableLength(void)
{
  return (MRSubG_LengthMode)(READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
                                            MR_SUBG_GLOB_STATIC_PCKT_CONFIG_FIX_VAR_LEN));
}

/**
  * @brief  Return the payload length for the Basic packet format.
  * @retval Payload length in bytes.
  */
__STATIC_INLINE uint16_t LL_MRSubG_PktBasicGetPayloadLength(void)
{
  return READ_REG(MR_SUBG_GLOB_STATIC->DATABUFFER_SIZE) & MR_SUBG_GLOB_STATIC_DATABUFFER_SIZE_DATABUFFER_SIZE;
}

/**
  * @brief  Indicates if the LENGTH field is defined on 1 byte or 2 bytes.
  * @param  lenWidth the length field to set.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetLenWidth(MRSubG_LenWidthhMode lenWidth)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG, MR_SUBG_GLOB_STATIC_PCKT_CONFIG_LEN_WIDTH, lenWidth);
}

/**
  * @brief  Return the LENGTH field, defined on 1 byte or 2 bytes.
  * @retval The LENGTH field.
  */
__STATIC_INLINE MRSubG_LenWidthhMode LL_MRSubG_GetLenWidth(void)
{
  return (MRSubG_LenWidthhMode)(READ_REG_FIELD(MR_SUBG_GLOB_STATIC->PCKT_CONFIG,
                                               MR_SUBG_GLOB_STATIC_PCKT_CONFIG_LEN_WIDTH));
}

/**
  * @brief  Enable or Disable RX_TIMER_RX_CS_TIMEOUT flag.
  * @param  xNewState new state for RX_TIMER_RX_CS_TIMEOUT flag.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetRxCsTimeout(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_CS_TIMEOUT_MASK);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_CS_TIMEOUT_MASK);
}

/**
  * @brief  Enable or Disable RX_TIMER_RX_PQI_TIMEOUT flag.
  * @param  xNewState new state for RX_TIMER_RX_PQI_TIMEOUT flag.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetRxPqiTimeout(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_PQI_TIMEOUT_MASK);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_PQI_TIMEOUT_MASK);
}

/**
  * @brief  Enable or Disable RX_TIMER_RX_SQI_TIMEOUT flag.
  * @param  xNewState new state for RX_TIMER_RX_SQI_TIMEOUT flag.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetRxSqiTimeout(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_SQI_TIMEOUT_MASK);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_SQI_TIMEOUT_MASK);
}

/**
  * @brief  Set or Reset RX_TIMER_RX_OR_nAND_SELECT.
  * @param  xNewState new state for RX_TIMER_RX_OR_nAND_SELECT bit.
  *         This parameter can be SET or RESET.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_SetRxOrnAndSelect(FlagStatus xNewState)
{
  if (xNewState == SET)
  {
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_OR_nAND_SELECT);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->RX_TIMER, MR_SUBG_GLOB_DYNAMIC_RX_TIMER_RX_OR_nAND_SELECT);
}

/**
  * @brief  Enable or Disable FAST_CS_TERM.
  * @param  xNewState new state for FAST_CS_TERM_EN.
  *         This parameter can be S_ENABLE or S_DISABLE.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_FastCsTermEn(FunctionalState xNewState)
{
  if (xNewState == ENABLE)
  {
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->FAST_RX_TIMER, MR_SUBG_GLOB_DYNAMIC_FAST_RX_TIMER_FAST_CS_TERM_EN);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->FAST_RX_TIMER, MR_SUBG_GLOB_DYNAMIC_FAST_RX_TIMER_FAST_CS_TERM_EN);
}

/**
  * @brief  Set or Reset VCO_CALIB_REQ.
  * @param  xNewState new state for VCO_CALIB_REQ bit.
  *         This parameter can be SET or RESET.
  * @retval None.
  */
__STATIC_INLINE void LL_MRSubG_VCOCalibReq(FlagStatus xNewState)
{
  if (xNewState == SET)
  {
    SET_BIT(MR_SUBG_GLOB_DYNAMIC->VCO_CAL_CONFIG, MR_SUBG_GLOB_DYNAMIC_VCO_CAL_CONFIG_VCO_CALIB_REQ);
  }
  else
    CLEAR_BIT(MR_SUBG_GLOB_DYNAMIC->VCO_CAL_CONFIG, MR_SUBG_GLOB_DYNAMIC_VCO_CAL_CONFIG_VCO_CALIB_REQ);
}

/**
  * @brief  Return the CHFLT_E field.
  * @retval The CHFLT_E field.
  */
__STATIC_INLINE uint8_t LL_MRSubG_GetChFlt_E(void)
{
  return READ_REG_FIELD(MR_SUBG_GLOB_DYNAMIC->MOD1_CONFIG, MR_SUBG_GLOB_DYNAMIC_MOD1_CONFIG_CHFLT_E);
}

/**
  * @brief  Return the RSSI_LEVEL_ON_SYNC register.
  * @retval The RSSI Level On Sync value.
  */
__STATIC_INLINE uint16_t LL_MRSubG_GetRssiLevelOnSync(void)
{
  return READ_REG(MR_SUBG_GLOB_STATUS->RX_INDICATOR) & MR_SUBG_GLOB_STATUS_RX_INDICATOR_RSSI_LEVEL_ON_SYNC;
}

/**
  * @brief  Set the MRSUBG RSSI_FLT register.
  * @retval The value to store for the register.
  */
__STATIC_INLINE void LL_MRSubG_SetRSSIFilter(uint32_t rssiFilter)
{
  WRITE_REG(MR_SUBG_RADIO->RSSI_FLT, rssiFilter);
}

/**
  * @brief  Set the RSSI threshold register.
  * @retval The value to store for the signal detect threshold.
  */
__STATIC_INLINE void LL_MRSubG_SetRssiThresholdRegister(uint16_t rssiValReg)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_RSSI_THR, rssiValReg);
}

/**
  * @brief  Set the MRSUBG Clock Recovery 0 register.
  * @retval The value to store for the register.
  */
__STATIC_INLINE void LL_MRSubG_SetClkRecCtrl0(uint32_t clkRec)
{
  WRITE_REG(MR_SUBG_RADIO->CLKREC_CTRL0, clkRec);
}

/**
  * @brief  Set the MRSUBG Clock Recovery 1 register.
  * @retval The value to store for the register.
  */
__STATIC_INLINE void LL_MRSubG_SetClkRecCtrl1(uint32_t clkRec)
{
  WRITE_REG(MR_SUBG_RADIO->CLKREC_CTRL1, clkRec);
}

/**
  * @brief  Set the MRSUBG AFC0 register.
  * @retval The value to store for the AFC0_CONFIG register.
  */
__STATIC_INLINE void LL_MRSubG_SetAFC0(uint32_t afcCfg)
{
  WRITE_REG(MR_SUBG_RADIO->AFC0_CONFIG, afcCfg);
}

/**
  * @brief  Set the MRSUBG AFC1 register.
  * @retval The value to store for the AFC1_CONFIG register.
  */
__STATIC_INLINE void LL_MRSubG_SetAFC1(uint32_t afcCfg)
{
  WRITE_REG(MR_SUBG_RADIO->AFC1_CONFIG, afcCfg);
}

/**
  * @brief  Set the MRSUBG AFC2 register.
  * @retval The value to store for the AFC2_CONFIG register.
  */
__STATIC_INLINE void LL_MRSubG_SetAFC2(uint32_t afcCfg)
{
  WRITE_REG(MR_SUBG_RADIO->AFC2_CONFIG, afcCfg);
}

/**
  * @brief  Set the MRSUBG AFC3 register.
  * @retval The value to store for the AFC3_CONFIG register.
  */
__STATIC_INLINE void LL_MRSubG_SetAFC3(uint32_t afcCfg)
{
  WRITE_REG(MR_SUBG_RADIO->AFC3_CONFIG, afcCfg);
}

/**
  * @brief  Low Level function to set the SQI threshold field in AS_QI_CTRL register.
  * @param  thr Threshold value of type @ref SQI_Threshold.
  * @retval None
  */
__STATIC_INLINE void LL_MRSubG_SetSQIThreshold(SQI_Threshold thr)
{
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_SQI_THR, thr);
}

/**
  * @brief  Low Level function to get the SQI threshold field from AS_QI_CTRL register.
  * @retval Threshold value of type @ref SQI_Threshold.
  */
__STATIC_INLINE SQI_Threshold LL_MRSubG_GetSQIThreshold(void)
{
  uint8_t thr = READ_REG_FIELD(MR_SUBG_GLOB_STATIC->AS_QI_CTRL, MR_SUBG_GLOB_STATIC_AS_QI_CTRL_SQI_THR);
  return (SQI_Threshold)thr;
}

/**
 @verbatim
  ==============================================================================
                     ##### How to use the MRSUBG Radio Sequencer #####
  ==============================================================================
    [..]
    The LL_SEQUENCER driver contains a set of APIs that can be used to configure
    the STM32WL3x MRSubG sequencer hardware.
    Typically it is used as follows:

  *** Step 1: Set up ActionConfiguration tables ***
  =================================================
    [..]
    In this step, configuration RAM tables are created for all actions in the
    flow graph.

   (+) Allocate a MRSubG_Sequencer_ActionConfiguration_t struct for each action
       that is part of your flow graph. The sequencer hardware accesses this struct in RAM as
       the ActionConfiguration RAM table.
       It must persist in RAM while the Action is being executed.
       Make sure that the RAM table is word-aligned.

   (+) For each ActionConfiguration item:

       (++) Set up the dynamic registers (MR_SUBG_GLOB_DYNAMIC) of the STM32WL3x
            as desired upon execution of the action. This can be performed
            using the standard MRSubG_* and packet APIs.
            Do not issue any command in the meantime (i.e., keep COMMAND_ID in
            the COMMAND to 0) to prevent side effects.
       (++) Copy all dynamic register values to the ActionConfiguration RAM
            table using MRSubG_Sequencer_ApplyDynamicConfig and configure
            which command is issued when the action gets executed.
       (++) Change the appropriate values in the
            MRSubG_Sequencer_ActionConfiguration_t struct to configure under
            which conditions either NextAction1 or NextAction2 are executed,
            to provide a pointer to ActionConfiguration RAM tables for both
            actions and to configure inter-action intervals.
            Use SEQ_MASK_NEVER_MATCH as NextAction1Mask / NextAction2Mask to
            ensure that this particular next action is never executed.
       (++) You may choose to configure an ActionTimeout, i.e. limit the
            maximum time to wait for a mask match for either NextAction1 or
            NextAction2.

  *** Step 2: Set up GlobalConfiguration table ***
  ================================================
    [..]
    In this step, a single configuration RAM table containing the global
    sequencer properties and the contents of the static configuration
    registers is created.

   (+) Allocate a MRSubG_Sequencer_GlobalConfiguration_t struct.
       The sequencer hardware accesses this struct in RAM as the
       GlobalConfiguration RAM table. The sequencer hardware will update
       properties of this RAM table during operation.

   (+) Modify the GlobalConfiguration struct:

       (++) Set up the static registers (MR_SUBG_GLOB_STATIC) of the STM32WL3x
            as desired upon execution of the action. This can be performed
            using the standard MRSubG_* and packet APIs.
       (++) Copy all static register values to the GlobalConfiguration RAM
            table using MRSubG_Sequencer_ApplyStaticConfig.
       (++) Set the current (i.e., first) action to execute by making
            ActionConfigPtr point to the appropriate ActionConfiguration.

   (+) Tell the sequencer hardware where to find the GlobalConfiguration
       by calling LL_MRSubG_Sequencer_SetGlobalConfiguration.

  *** Step 3: Trigger the sequencer ***
  =====================================
    [..]
   (+) When desired, start the sequencer using MRSubG_Sequencer_Trigger.

   (+) You may choose to intervene into the sequencer control flow
       programmatically using, for example, an interrupt.

   (+) If, at any point, you need to restart the sequencer:

       (++) Set the action to execute next by modifying ActionConfigPtr in
            the GlobalConfiguration struct.
       (++) Re-trigger the sequencer using MRSubG_Sequencer_Trigger.
  @endverbatim
  **/

/*
  * @brief  Set global configuration table for sequencer hardware.
  * @param  Pointer to the global configuration table struct.
  * @retval None
  */
__STATIC_INLINE void LL_MRSubG_Sequencer_SetGlobalConfiguration(MRSubG_Sequencer_GlobalConfiguration_t *cfg)
{
  /* GLOBALTABLE_PTR is relative to device SRAM_BASE base address */
  MR_SUBG_GLOB_RETAINED->SEQ_GLOBALTABLE_PTR = ((uint32_t)cfg) - SRAM_BASE;
}

/*
 * @brief  Determine whether sequencer hardware is currently active.
 * @retval 1 in case sequencer is active, otherwise 0
 */
__STATIC_INLINE uint8_t LL_MRSubG_Sequencer_IsActive(void)
{
  return (MR_SUBG_GLOB_MISC->SEQUENCER_CTRL & MR_SUBG_GLOB_MISC_SEQUENCER_CTRL_DISABLE_SEQ) ? 0 : 1;
}

/*
 * @brief  Trigger sequencer, i.e., launch sequence of actions.
 * @retval None
 */
__STATIC_INLINE void LL_MRSubG_Sequencer_Trigger(void)
{
  MR_SUBG_GLOB_MISC->SEQUENCER_CTRL &= ~MR_SUBG_GLOB_MISC_SEQUENCER_CTRL_DISABLE_SEQ;
  MR_SUBG_GLOB_MISC->SEQUENCER_CTRL |= MR_SUBG_GLOB_MISC_SEQUENCER_CTRL_GEN_SEQ_TRIGGER;
}

/*
 * @brief  Disable sequencer hardware.
 * @retval None
 */
__STATIC_INLINE void LL_MRSubG_Sequencer_Disable(void)
{
  MR_SUBG_GLOB_MISC->SEQUENCER_CTRL |=
    MR_SUBG_GLOB_MISC_SEQUENCER_CTRL_DISABLE_SEQ |
    MR_SUBG_GLOB_MISC_SEQUENCER_CTRL_GEN_SEQ_TRIGGER;
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

#endif /*STM32WL3x_LL_MRSUBG_H */
