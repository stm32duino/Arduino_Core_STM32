/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_dma.h
  * @author  MCD Application Team
  * @brief   Header file of DMA LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
 @verbatim
  ==============================================================================
                        ##### LL DMA driver acronyms #####
  ==============================================================================
  [..]  Acronyms table :
                   =========================================
                   || Acronym ||                          ||
                   =========================================
                   || SRC     ||  Source                  ||
                   || DEST    ||  Destination             ||
                   || ADDR    ||  Address                 ||
                   || ADDRS   ||  Addresses               ||
                   || INC     ||  Increment / Incremented ||
                   || DEC     ||  Decrement / Decremented ||
                   || BLK     ||  Block                   ||
                   || RPT     ||  Repeat / Repeated       ||
                   || TRIG    ||  Trigger                 ||
                   =========================================
 @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WBAxx_LL_DMA_H
#define STM32WBAxx_LL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx.h"

/** @addtogroup STM32WBAxx_LL_Driver
  * @{
  */

#if defined (GPDMA1)

/** @defgroup DMA_LL DMA
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup DMA_LL_Private_Variables DMA Private Variables
  * @{
  */
#define DMA_CHANNEL0_OFFSET  (0x00000050UL)
#define DMA_CHANNEL1_OFFSET  (0x000000D0UL)
#define DMA_CHANNEL2_OFFSET  (0x00000150UL)
#define DMA_CHANNEL3_OFFSET  (0x000001D0UL)
#define DMA_CHANNEL4_OFFSET  (0x00000250UL)
#define DMA_CHANNEL5_OFFSET  (0x000002D0UL)
#define DMA_CHANNEL6_OFFSET  (0x00000350UL)
#define DMA_CHANNEL7_OFFSET  (0x000003D0UL)

/* Array used to get the DMA Channel register offset versus Channel index LL_DMA_CHANNEL_x */
static const uint32_t LL_DMA_CH_OFFSET_TAB[] =
{
  DMA_CHANNEL0_OFFSET,  DMA_CHANNEL1_OFFSET,  DMA_CHANNEL2_OFFSET,  DMA_CHANNEL3_OFFSET,
  DMA_CHANNEL4_OFFSET,  DMA_CHANNEL5_OFFSET,  DMA_CHANNEL6_OFFSET,  DMA_CHANNEL7_OFFSET,
};

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

#if defined (USE_FULL_LL_DRIVER)
/** @defgroup DMA_LL_ES_INIT DMA Exported Init structure
  * @{
  */

/**
  * @brief  LL DMA init structure definition.
  */
typedef struct
{
  uint32_t SrcAddress;               /*!< This field specify the data transfer source address.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter must be a value between Min_Data = 0 and Max_Data = 0xFFFFFFFF.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetSrcAddress().                                                */

  uint32_t DestAddress;              /*!< This field specify the data transfer destination address.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter must be a value between Min_Data = 0 and Max_Data = 0xFFFFFFFF.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDestAddress().                                               */

  uint32_t Direction;                /*!< This field specify the data transfer direction.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_TRANSFER_DIRECTION.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDataTransferDirection().                                     */

  uint32_t BlkHWRequest;             /*!< This field specify the hardware request unity.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_BLKHW_REQUEST.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetBlkHWRequest().                                              */

  uint32_t DataAlignment;            /*!< This field specify the transfer data alignment.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_DATA_ALIGNMENT.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDataAlignment().                                             */

  uint32_t SrcBurstLength;           /*!< This field specify the source burst length of transfer in bytes.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter must be a value between Min_Data = 1 and Max_Data = 64.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetSrcBurstLength().                                            */

  uint32_t DestBurstLength;          /*!< This field specify the destination burst length of transfer in bytes.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter must be a value between Min_Data = 1 and Max_Data = 64.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDestBurstLength().                                           */

  uint32_t SrcDataWidth;             /*!< This field specify the source data width.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_SOURCE_DATA_WIDTH.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetSrcDataWidth().                                              */

  uint32_t DestDataWidth;            /*!< This field specify the destination data width.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_DESTINATION_DATA_WIDTH.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDestDataWidth().                                             */

  uint32_t SrcIncMode;               /*!< This field specify the source burst increment mode.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_SOURCE_INCREMENT_MODE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetSrcIncMode().                                                */

  uint32_t DestIncMode;              /*!< This field specify the destination burst increment mode.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_DESTINATION_INCREMENT_MODE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDestIncMode().                                               */

  uint32_t Priority;                 /*!< This field specify the channel priority level.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_PRIORITY_LEVEL.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetChannelPriorityLevel().                                      */

  uint32_t BlkDataLength;            /*!< This field specify the length of a block transfer in bytes.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter must be a value between Min_Data = 0 and Max_Data = 0x0000FFFF.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetBlkDataLength().                                             */

  uint32_t TriggerMode;              /*!< This field specify the trigger mode.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_TRIGGER_MODE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetTriggerMode().                                               */

  uint32_t TriggerPolarity;          /*!< This field specify the trigger event polarity.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_TRIGGER_POLARITY.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetTriggerPolarity().                                           */

  uint32_t TriggerSelection;         /*!< This field specify the trigger event selection.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_TRIGGER_SELECTION.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetHWTrigger().                                                 */

  uint32_t Request;                  /*!< This field specify the peripheral request selection.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_REQUEST_SELECTION.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetPeriphRequest().                                             */

  uint32_t TransferEventMode;        /*!< This field specify the transfer event mode.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_TRANSFER_EVENT_MODE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetTransferEventMode().                                         */

  uint32_t DestHWordExchange;        /*!< This field specify the destination half word exchange.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_DEST_HALFWORD_EXCHANGE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDestHWordExchange().                                         */

  uint32_t DestByteExchange;         /*!< This field specify the destination byte exchange.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_DEST_BYTE_EXCHANGE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDestByteExchange().                                          */

  uint32_t SrcByteExchange;          /*!< This field specify the source byte exchange.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_SRC_BYTE_EXCHANGE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetSrcByteExchange().                                           */

  uint32_t SrcAllocatedPort;         /*!< This field specify the source allocated port.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_SOURCE_ALLOCATED_PORT.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetSrcAllocatedPort().                                          */

  uint32_t DestAllocatedPort;        /*!< This field specify the destination allocated port.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_DESTINATION_ALLOCATED_PORT.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetDestAllocatedPort().                                         */

  uint32_t LinkAllocatedPort;        /*!< This field specify the linked-list allocated port.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_LINKED_LIST_ALLOCATED_PORT.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetLinkAllocatedPort().                                         */

  uint32_t LinkStepMode;             /*!< This field specify the link step mode.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value of @ref DMA_LL_EC_LINK_STEP_MODE.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetLinkStepMode().                                              */

  uint32_t LinkedListBaseAddr;       /*!< This field specify the linked list base address.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value Between 0 to 0xFFFF0000 (where the 4 first
                                          bytes are always forced to 0).
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetLinkedListBaseAddr().                                        */

  uint32_t LinkedListAddrOffset;     /*!< Specifies the linked list address offset.
                                          Programming this field is mandatory for all available DMA channels.
                                          This parameter can be a value Between 0 to 0x0000FFFC.
                                          This feature can be modified afterwards using unitary function
                                          @ref LL_DMA_SetLinkedListAddrOffset().                                      */

} LL_DMA_InitTypeDef;


/**
  * @brief  LL DMA init linked list structure definition.
  */
typedef struct
{
  uint32_t Priority;             /*!< This field specify the channel priority level.
                                      Programming this field is mandatory for all available DMA channels.
                                      This parameter can be a value of @ref DMA_LL_EC_PRIORITY_LEVEL.
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_DMA_SetChannelPriorityLevel().                                          */

  uint32_t LinkStepMode;         /*!< This field specify the link step mode.
                                      Programming this field is mandatory for all available DMA channels.
                                      This parameter can be a value of @ref DMA_LL_EC_LINK_STEP_MODE.
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_DMA_SetLinkStepMode().                                                  */

  uint32_t LinkAllocatedPort;    /*!< This field specify the linked-list allocated port.
                                      Programming this field is mandatory for all available DMA channels.
                                      This parameter can be a value of @ref DMA_LL_EC_LINKED_LIST_ALLOCATED_PORT.
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_DMA_SetLinkAllocatedPort().                                             */

  uint32_t TransferEventMode;    /*!< This field specify the transfer event mode.
                                      Programming this field is mandatory for all available DMA channels.
                                      This parameter can be a value of @ref DMA_LL_EC_TRANSFER_EVENT_MODE.
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_DMA_SetTransferEventMode().                                             */
} LL_DMA_InitLinkedListTypeDef;


/**
  * @brief  LL DMA node init structure definition.
  */
typedef struct
{
  /* CTR1 register fields ******************************************************
     If any CTR1 fields need to be updated comparing to previous node, it is
     mandatory to update the new value in CTR1 register fields and enable update
     CTR1 register in UpdateRegisters fields if it is not enabled in the
     previous node.

  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t DestSecure;           /*!< This field specify the destination secure.
                                      This parameter can be a value of @ref DMA_LL_EC_DESTINATION_SECURITY_ATTRIBUTE. */
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

  uint32_t DestAllocatedPort;    /*!< This field specify the destination allocated port.
                                      This parameter can be a value of @ref DMA_LL_EC_DESTINATION_ALLOCATED_PORT.     */

  uint32_t DestHWordExchange;    /*!< This field specify the destination half word exchange.
                                      This parameter can be a value of @ref DMA_LL_EC_DEST_HALFWORD_EXCHANGE.         */

  uint32_t DestByteExchange;     /*!< This field specify the destination byte exchange.
                                      This parameter can be a value of @ref DMA_LL_EC_DEST_BYTE_EXCHANGE.             */

  uint32_t DestBurstLength;      /*!< This field specify the destination burst length of transfer in bytes.
                                      This parameter must be a value between Min_Data = 1 and Max_Data = 64.          */

  uint32_t DestIncMode;          /*!< This field specify the destination increment mode.
                                      This parameter can be a value of @ref DMA_LL_EC_DESTINATION_INCREMENT_MODE.     */

  uint32_t DestDataWidth;        /*!< This field specify the destination data width.
                                      This parameter can be a value of @ref DMA_LL_EC_DESTINATION_DATA_WIDTH.         */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t SrcSecure;            /*!< This field specify the source secure.
                                      This parameter can be a value of @ref DMA_LL_EC_SOURCE_SECURITY_ATTRIBUTE.      */
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

  uint32_t SrcAllocatedPort;     /*!< This field specify the source allocated port.
                                      This parameter can be a value of @ref DMA_LL_EC_SOURCE_ALLOCATED_PORT.          */

  uint32_t SrcByteExchange;      /*!< This field specify the source byte exchange.
                                      This parameter can be a value of @ref DMA_LL_EC_SRC_BYTE_EXCHANGE.              */

  uint32_t DataAlignment;        /*!< This field specify the transfer data alignment.
                                      This parameter can be a value of @ref DMA_LL_EC_DATA_ALIGNMENT.                 */

  uint32_t SrcBurstLength;       /*!< This field specify the source burst length of transfer in bytes.
                                      This parameter must be a value between Min_Data = 1 and Max_Data = 64.          */

  uint32_t SrcIncMode;           /*!< This field specify the source increment mode.
                                      This parameter can be a value of @ref DMA_LL_EC_SOURCE_INCREMENT_MODE.          */

  uint32_t SrcDataWidth;         /*!< This field specify the source data width.
                                      This parameter can be a value of @ref DMA_LL_EC_SOURCE_DATA_WIDTH.              */


  /* CTR2 register fields ******************************************************
     If any CTR2 fields need to be updated comparing to previous node, it is
     mandatory to update the new value in CTR2 register fields and enable update
     CTR2 register in UpdateRegisters fields if it is not enabled in the
     previous node.

     For all node created, filling all fields is mandatory.
  */
  uint32_t TransferEventMode;    /*!< This field specify the transfer event mode.
                                      This parameter can be a value of @ref DMA_LL_EC_TRANSFER_EVENT_MODE.            */

  uint32_t TriggerPolarity;      /*!< This field specify the trigger event polarity.
                                      This parameter can be a value of @ref DMA_LL_EC_TRIGGER_POLARITY.               */

  uint32_t TriggerSelection;     /*!< This field specify the trigger event selection.
                                      This parameter can be a value of @ref DMA_LL_EC_TRIGGER_SELECTION.              */

  uint32_t TriggerMode;          /*!< This field specify the trigger mode.
                                      This parameter can be a value of @ref DMA_LL_EC_TRIGGER_MODE.                   */

  uint32_t BlkHWRequest;         /*!< This field specify the hardware request unity.
                                      This parameter can be a value of @ref DMA_LL_EC_BLKHW_REQUEST.                  */

  uint32_t Direction;            /*!< This field specify the transfer direction.
                                      This parameter can be a value of @ref DMA_LL_EC_TRANSFER_DIRECTION.             */

  uint32_t Request;              /*!< This field specify the peripheral request selection.
                                      This parameter can be a value of @ref DMA_LL_EC_REQUEST_SELECTION.              */


  /* CBR1 register fields ******************************************************
     If any CBR1 fields need to be updated comparing to previous node, it is
     mandatory to update the new value in CBR1 register fields and enable update
     CBR1 register in UpdateRegisters fields if it is not enabled in the
     previous node.
  */

  uint32_t BlkDataLength;            /*!< This field specify the length of a block transfer in bytes.
                                          This parameter must be a value between Min_Data = 0
                                          and Max_Data = 0x0000FFFF.                                                  */

  /* CSAR register fields ******************************************************
     If any CSAR fields need to be updated comparing to previous node, it is
     mandatory to update the new value in CSAR register fields and enable update
     CSAR register in UpdateRegisters fields if it is not enabled in the
     previous node.

     For all node created, filling all fields is mandatory.
  */
  uint32_t SrcAddress;              /*!< This field specify the transfer source address.
                                         This parameter must be a value between Min_Data = 0
                                         and Max_Data = 0xFFFFFFFF.                                                   */


  /* CDAR register fields ******************************************************
     If any CDAR fields need to be updated comparing to previous node, it is
     mandatory to update the new value in CDAR register fields and enable update
     CDAR register in UpdateRegisters fields if it is not enabled in the
     previous node.

     For all node created, filling all fields is mandatory.
  */
  uint32_t DestAddress;             /*!< This field specify the transfer destination address.
                                         This parameter must be a value between Min_Data = 0
                                         and Max_Data = 0xFFFFFFFF.                                                   */

  /* CLLR register fields ******************************************************
     If any CLLR fields need to be updated comparing to previous node, it is
     mandatory to update the new value in CLLR register fields and enable update
     CLLR register in UpdateRegisters fields if it is not enabled in the
     previous node.
  */
  uint32_t UpdateRegisters;      /*!< Specifies the linked list register update.
                                      This parameter can be a value of @ref DMA_LL_EC_LINKEDLIST_REGISTER_UPDATE.     */

  /* DMA Node type field *******************************************************
     This parameter defines node types as node size and node content varies
     between channels.
     Thanks to this fields, linked list queue could be created independently
     from channel selection. So, one queue could be executed by all DMA channels.
  */
  uint32_t NodeType;             /*!< Specifies the node type to be created.
                                      This parameter can be a value of @ref DMA_LL_EC_LINKEDLIST_NODE_TYPE.           */
} LL_DMA_InitNodeTypeDef;

/**
  * @brief  LL DMA linked list node structure definition.
  * @note   For GPDMA linear addressing channels, the maximum node size is :
  *         (4 Bytes * 6 registers = 24 Bytes).
  */
typedef struct
{
  __IO uint32_t LinkRegisters[6U];

} LL_DMA_LinkNodeTypeDef;
/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_LL_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_LL_EC_CHANNEL Channel
  * @{
  */
#define LL_DMA_CHANNEL_0   (0x00U)
#define LL_DMA_CHANNEL_1   (0x01U)
#define LL_DMA_CHANNEL_2   (0x02U)
#define LL_DMA_CHANNEL_3   (0x03U)
#define LL_DMA_CHANNEL_4   (0x04U)
#define LL_DMA_CHANNEL_5   (0x05U)
#define LL_DMA_CHANNEL_6   (0x06U)
#define LL_DMA_CHANNEL_7   (0x07U)
#define LL_DMA_CHANNEL_8   (0x08U)
#define LL_DMA_CHANNEL_9   (0x09U)
#define LL_DMA_CHANNEL_10  (0x0AU)
#define LL_DMA_CHANNEL_11  (0x0BU)
#define LL_DMA_CHANNEL_12  (0x0CU)
#define LL_DMA_CHANNEL_13  (0x0DU)
#define LL_DMA_CHANNEL_14  (0x0EU)
#define LL_DMA_CHANNEL_15  (0x0FU)
#if defined (USE_FULL_LL_DRIVER)
#define LL_DMA_CHANNEL_ALL (0x10U)
#endif /* USE_FULL_LL_DRIVER */
/**
  * @}
  */

#if defined (USE_FULL_LL_DRIVER)
/** @defgroup DMA_LL_EC_CLLR_OFFSET CLLR offset
  * @{
  */
#define LL_DMA_CLLR_OFFSET0 (0x00U)
#define LL_DMA_CLLR_OFFSET1 (0x01U)
#define LL_DMA_CLLR_OFFSET2 (0x02U)
#define LL_DMA_CLLR_OFFSET3 (0x03U)
#define LL_DMA_CLLR_OFFSET4 (0x04U)
#define LL_DMA_CLLR_OFFSET5 (0x05U)
#define LL_DMA_CLLR_OFFSET6 (0x06U)
#define LL_DMA_CLLR_OFFSET7 (0x07U)
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup DMA_LL_EC_PRIORITY_LEVEL Priority Level
  * @{
  */
#define LL_DMA_LOW_PRIORITY_LOW_WEIGHT  0x00000000U    /*!< Priority level : Low Priority, Low Weight  */
#define LL_DMA_LOW_PRIORITY_MID_WEIGHT  DMA_CCR_PRIO_0 /*!< Priority level : Low Priority, Mid Weight  */
#define LL_DMA_LOW_PRIORITY_HIGH_WEIGHT DMA_CCR_PRIO_1 /*!< Priority level : Low Priority, High Weight */
#define LL_DMA_HIGH_PRIORITY            DMA_CCR_PRIO   /*!< Priority level : High Priority             */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_LINKED_LIST_ALLOCATED_PORT Linked List Allocated Port
  * @{
  */
#define LL_DMA_LINK_ALLOCATED_PORT0 0x00000000U /*!< Linked List Allocated Port 0 */
#define LL_DMA_LINK_ALLOCATED_PORT1 DMA_CCR_LAP /*!< Linked List Allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_LINK_STEP_MODE Link Step Mode
  * @{
  */
#define LL_DMA_LSM_FULL_EXECUTION  0x00000000U /*!< Channel execute the full linked list        */
#define LL_DMA_LSM_1LINK_EXECUTION DMA_CCR_LSM /*!< Channel execute one node of the linked list */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DEST_HALFWORD_EXCHANGE Destination Half-Word Exchange
  * @{
  */
#define LL_DMA_DEST_HALFWORD_PRESERVE 0x00000000U  /*!< No destination Half-Word exchange when destination data width
                                                        is word                                                       */
#define LL_DMA_DEST_HALFWORD_EXCHANGE DMA_CTR1_DHX /*!< Destination Half-Word exchange when destination data width
                                                        is word                                                       */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DEST_BYTE_EXCHANGE Destination Byte Exchange
  * @{
  */
#define LL_DMA_DEST_BYTE_PRESERVE 0x00000000U  /*!< No destination Byte exchange when destination data width > Byte */
#define LL_DMA_DEST_BYTE_EXCHANGE DMA_CTR1_DBX /*!< Destination Byte exchange when destination data width > Byte    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SRC_BYTE_EXCHANGE Source Byte Exchange
  * @{
  */
#define LL_DMA_SRC_BYTE_PRESERVE 0x00000000U  /*!< No source Byte exchange when source data width is word */
#define LL_DMA_SRC_BYTE_EXCHANGE DMA_CTR1_SBX /*!< Source Byte exchange when source data width is word    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_ALLOCATED_PORT Source Allocated Port
  * @{
  */
#define LL_DMA_SRC_ALLOCATED_PORT0 0x00000000U  /*!< Source Allocated Port 0 */
#define LL_DMA_SRC_ALLOCATED_PORT1 DMA_CTR1_SAP /*!< Source Allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_ALLOCATED_PORT Destination Allocated Port
  * @{
  */
#define LL_DMA_DEST_ALLOCATED_PORT0 0x00000000U  /*!< Destination Allocated Port 0 */
#define LL_DMA_DEST_ALLOCATED_PORT1 DMA_CTR1_DAP /*!< Destination Allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_INCREMENT_MODE Destination Increment Mode
  * @{
  */
#define LL_DMA_DEST_FIXED       0x00000000U   /*!< Destination fixed single/burst       */
#define LL_DMA_DEST_INCREMENT   DMA_CTR1_DINC /*!< Destination incremented single/burst */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_DATA_WIDTH Destination Data Width
  * @{
  */
#define LL_DMA_DEST_DATAWIDTH_BYTE       0x00000000U         /*!< Destination Data Width : Byte       */
#define LL_DMA_DEST_DATAWIDTH_HALFWORD   DMA_CTR1_DDW_LOG2_0 /*!< Destination Data Width : HalfWord   */
#define LL_DMA_DEST_DATAWIDTH_WORD       DMA_CTR1_DDW_LOG2_1 /*!< Destination Data Width : Word       */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DATA_ALIGNMENT Data Alignment
  * @{
  */
#define LL_DMA_DATA_ALIGN_ZEROPADD    0x00000000U    /*!< If src data width < dest data width :
                                                          => Right Aligned padded with 0 up to destination
                                                             data width.
                                                          If src data width > dest data width :
                                                          => Right Aligned Left Truncated down to destination
                                                             data width.                                              */
#define LL_DMA_DATA_ALIGN_SIGNEXTPADD DMA_CTR1_PAM_0 /*!< If src data width < dest data width :
                                                          => Right Aligned padded with sign extended up to destination
                                                             data width.
                                                          If src data width > dest data width :
                                                          => Left Aligned Right Truncated down to the destination
                                                             data width                                               */
#define LL_DMA_DATA_PACK_UNPACK       DMA_CTR1_PAM_1 /*!< If src data width < dest data width :
                                                          => Packed at the destination data width
                                                          If src data width > dest data width :
                                                          => Unpacked at the destination data width                   */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_INCREMENT_MODE Source Increment Mode
  * @{
  */
#define LL_DMA_SRC_FIXED     0x00000000U   /*!< Source fixed single/burst */
#define LL_DMA_SRC_INCREMENT DMA_CTR1_SINC /*!< Source incremented single/burst    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_DATA_WIDTH Source Data Width
  * @{
  */
#define LL_DMA_SRC_DATAWIDTH_BYTE        0x00000000U         /*!< Source Data Width : Byte       */
#define LL_DMA_SRC_DATAWIDTH_HALFWORD    DMA_CTR1_SDW_LOG2_0 /*!< Source Data Width : HalfWord   */
#define LL_DMA_SRC_DATAWIDTH_WORD        DMA_CTR1_SDW_LOG2_1 /*!< Source Data Width : Word       */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_BLKHW_REQUEST Block Hardware Request
  * @{
  */
#define LL_DMA_HWREQUEST_SINGLEBURST 0x00000000U   /*!< Hardware request is driven by a peripheral with a hardware
                                                        request/acknowledge protocol at a burst level                 */
#define LL_DMA_HWREQUEST_BLK         DMA_CTR2_BREQ /*!< Hardware request is driven by a peripheral with a hardware
                                                        request/acknowledge protocol at a block level                 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRANSFER_EVENT_MODE Transfer Event Mode
  * @{
  */
#define LL_DMA_TCEM_BLK_TRANSFER         0x00000000U       /*!< The TC (and the HT) event is generated at the
                                                                (respectively half) end of each block                 */
#define LL_DMA_TCEM_RPT_BLK_TRANSFER     DMA_CTR2_TCEM_0   /*!< The TC (and the HT) event is generated at the
                                                                (respectively half) end of the repeated block         */
#define LL_DMA_TCEM_EACH_LLITEM_TRANSFER DMA_CTR2_TCEM_1   /*!< The TC (and the HT) event is generated at the
                                                                (respectively half) end of each linked-list item      */
#define LL_DMA_TCEM_LAST_LLITEM_TRANSFER DMA_CTR2_TCEM     /*!< The TC (and the HT) event is generated at the
                                                                (respectively half) end of the last linked-list item  */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRIGGER_POLARITY Trigger Polarity
  * @{
  */
#define LL_DMA_TRIG_POLARITY_MASKED    0x00000000U         /*!< No trigger of the selected DMA request.
                                                                Masked trigger event                                  */
#define LL_DMA_TRIG_POLARITY_RISING    DMA_CTR2_TRIGPOL_0  /*!< Trigger of the selected DMA request on the rising
                                                                edge of the selected trigger event input              */
#define LL_DMA_TRIG_POLARITY_FALLING   DMA_CTR2_TRIGPOL_1  /*!< Trigger of the selected DMA request on the falling
                                                                edge of the selected trigger event input              */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRIGGER_MODE Transfer Trigger Mode
  * @{
  */
#define LL_DMA_TRIGM_BLK_TRANSFER        0x00000000U      /*!< A block transfer is conditioned by (at least)
                                                               one hit trigger                                        */
#define LL_DMA_TRIGM_RPT_BLK_TRANSFER    DMA_CTR2_TRIGM_0 /*!< A repeated block transfer is conditioned by (at least)
                                                               one hit trigger                                        */
#define LL_DMA_TRIGM_LLI_LINK_TRANSFER   DMA_CTR2_TRIGM_1 /*!< A LLI link transfer is conditioned by (at least)
                                                               one hit trigger                                        */
#define LL_DMA_TRIGM_SINGLBURST_TRANSFER DMA_CTR2_TRIGM   /*!< A Single/Burst transfer is conditioned by (at least)
                                                               one hit trigger                                        */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRANSFER_DIRECTION Transfer Direction
  * @{
  */
#define LL_DMA_DIRECTION_MEMORY_TO_MEMORY DMA_CTR2_SWREQ /*!< Memory to memory direction     */
#define LL_DMA_DIRECTION_PERIPH_TO_MEMORY 0x00000000U    /*!< Peripheral to memory direction */
#define LL_DMA_DIRECTION_MEMORY_TO_PERIPH DMA_CTR2_DREQ  /*!< Memory to peripheral direction */
/**
  * @}
  */


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup DMA_LL_EC_SOURCE_SECURITY_ATTRIBUTE Source Security Attribute
  * @{
  */
#define LL_DMA_CHANNEL_NSEC 0x00000000U /*!< NSecure channel */
#define LL_DMA_CHANNEL_SEC  0x00000001U /*!< Secure channel  */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_SECURITY_ATTRIBUTE Source Security Attribute
  * @{
  */
#define LL_DMA_CHANNEL_SRC_NSEC 0x00000000U   /*!< NSecure transfer from the source */
#define LL_DMA_CHANNEL_SRC_SEC  DMA_CTR1_SSEC /*!< Secure transfer from the source  */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_SECURITY_ATTRIBUTE Destination Security Attribute
  * @{
  */
#define LL_DMA_CHANNEL_DEST_NSEC 0x00000000U   /*!< NSecure transfer from the destination */
#define LL_DMA_CHANNEL_DEST_SEC  DMA_CTR1_DSEC /*!< Secure transfer from the destination  */
/**
  * @}
  */
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/** @defgroup DMA_LL_EC_LINKEDLIST_NODE_TYPE Linked list node type
  * @{
  */
#define LL_DMA_GPDMA_LINEAR_NODE 0x01U /*!< GPDMA node : linear addressing node      */

/**
  * @}
  */

/** @defgroup DMA_LL_EC_LINKEDLIST_REGISTER_UPDATE Linked list register update
  * @{
  */
#define LL_DMA_UPDATE_CTR1 DMA_CLLR_UT1 /*!< Update CTR1 register from memory :
                                             available for all DMA channels                */
#define LL_DMA_UPDATE_CTR2 DMA_CLLR_UT2 /*!< Update CTR2 register from memory :
                                             available for all DMA channels                */
#define LL_DMA_UPDATE_CBR1 DMA_CLLR_UB1 /*!< Update CBR1 register from memory :
                                             available for all DMA channels                */
#define LL_DMA_UPDATE_CSAR DMA_CLLR_USA /*!< Update CSAR register from memory :
                                             available for all DMA channels                */
#define LL_DMA_UPDATE_CDAR DMA_CLLR_UDA /*!< Update CDAR register from memory :
                                             available for all DMA channels                */
#define LL_DMA_UPDATE_CLLR DMA_CLLR_ULL /*!< Update CLLR register from memory :
                                             available for all DMA channels                */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_REQUEST_SELECTION Request Selection
  * @{
  */
/* GPDMA1 Hardware Requests */
#define LL_GPDMA1_REQUEST_ADC4            0U     /*!< GPDMA1 HW request is ADC4          */
#if defined (SPI1)
#define LL_GPDMA1_REQUEST_SPI1_RX         1U     /*!< GPDMA1 HW request is SPI1_RX       */
#define LL_GPDMA1_REQUEST_SPI1_TX         2U     /*!< GPDMA1 HW request is SPI1_TX       */
#endif /* SPI1 */
#define LL_GPDMA1_REQUEST_SPI3_RX         3U     /*!< GPDMA1 HW request is SPI3_RX       */
#define LL_GPDMA1_REQUEST_SPI3_TX         4U     /*!< GPDMA1 HW request is SPI3_TX       */
#if defined (I2C1)
#define LL_GPDMA1_REQUEST_I2C1_RX         5U     /*!< GPDMA1 HW request is I2C1_RX       */
#define LL_GPDMA1_REQUEST_I2C1_TX         6U     /*!< GPDMA1 HW request is I2C1_TX       */
#define LL_GPDMA1_REQUEST_I2C1_EVC        7U     /*!< GPDMA1 HW request is I2C1_EVC      */
#endif /* I2C1 */
#define LL_GPDMA1_REQUEST_I2C3_RX         8U     /*!< GPDMA1 HW request is I2C3_RX       */
#define LL_GPDMA1_REQUEST_I2C3_TX         9U     /*!< GPDMA1 HW request is I2C3_TX       */
#define LL_GPDMA1_REQUEST_I2C3_EVC       10U     /*!< GPDMA1 HW request is I2C3_EVC      */
#define LL_GPDMA1_REQUEST_USART1_RX      11U     /*!< GPDMA1 HW request is USART1_RX     */
#define LL_GPDMA1_REQUEST_USART1_TX      12U     /*!< GPDMA1 HW request is USART1_TX     */
#if defined (USART2)
#define LL_GPDMA1_REQUEST_USART2_RX      13U     /*!< GPDMA1 HW request is USART2_RX     */
#define LL_GPDMA1_REQUEST_USART2_TX      14U     /*!< GPDMA1 HW request is USART2_TX     */
#endif /* USART2 */
#define LL_GPDMA1_REQUEST_LPUART1_RX     15U     /*!< GPDMA1 HW request is LPUART1_RX    */
#define LL_GPDMA1_REQUEST_LPUART1_TX     16U     /*!< GPDMA1 HW request is LPUART1_TX    */
#if defined (SAI1)
#define LL_GPDMA1_REQUEST_SAI1_A         17U     /*!< GPDMA1 HW request is SAI1_A        */
#define LL_GPDMA1_REQUEST_SAI1_B         18U     /*!< GPDMA1 HW request is SAI1_B        */
#endif /* SAI1 */
#define LL_GPDMA1_REQUEST_TIM1_CH1       19U     /*!< GPDMA1 HW request is TIM1_CH1      */
#define LL_GPDMA1_REQUEST_TIM1_CH2       20U     /*!< GPDMA1 HW request is TIM1_CH2      */
#define LL_GPDMA1_REQUEST_TIM1_CH3       21U     /*!< GPDMA1 HW request is TIM1_CH3      */
#define LL_GPDMA1_REQUEST_TIM1_CH4       22U     /*!< GPDMA1 HW request is TIM1_CH4      */
#define LL_GPDMA1_REQUEST_TIM1_UP        23U     /*!< GPDMA1 HW request is TIM1_UP       */
#define LL_GPDMA1_REQUEST_TIM1_TRIG      24U     /*!< GPDMA1 HW request is TIM1_TRIG     */
#define LL_GPDMA1_REQUEST_TIM1_COM       25U     /*!< GPDMA1 HW request is TIM1_COM      */
#define LL_GPDMA1_REQUEST_TIM2_CH1       26U     /*!< GPDMA1 HW request is TIM2_CH1      */
#define LL_GPDMA1_REQUEST_TIM2_CH2       27U     /*!< GPDMA1 HW request is TIM2_CH2      */
#define LL_GPDMA1_REQUEST_TIM2_CH3       28U     /*!< GPDMA1 HW request is TIM2_CH3      */
#define LL_GPDMA1_REQUEST_TIM2_CH4       29U     /*!< GPDMA1 HW request is TIM2_CH4      */
#define LL_GPDMA1_REQUEST_TIM2_UP        30U     /*!< GPDMA1 HW request is TIM2_UP       */
#if defined (TIM3)
#define LL_GPDMA1_REQUEST_TIM3_CH1       31U     /*!< GPDMA1 HW request is TIM3_CH1      */
#define LL_GPDMA1_REQUEST_TIM3_CH2       32U     /*!< GPDMA1 HW request is TIM3_CH2      */
#define LL_GPDMA1_REQUEST_TIM3_CH3       33U     /*!< GPDMA1 HW request is TIM3_CH3      */
#define LL_GPDMA1_REQUEST_TIM3_CH4       34U     /*!< GPDMA1 HW request is TIM3_CH4      */
#define LL_GPDMA1_REQUEST_TIM3_UP        35U     /*!< GPDMA1 HW request is TIM3_UP       */
#define LL_GPDMA1_REQUEST_TIM3_TRIG      36U     /*!< GPDMA1 HW request is TIM3_TRIG     */
#endif /* TIM3 */
#define LL_GPDMA1_REQUEST_TIM16_CH1      37U     /*!< GPDMA1 HW request is TIM16_CH1     */
#define LL_GPDMA1_REQUEST_TIM16_UP       38U     /*!< GPDMA1 HW request is TIM16_UP      */
#if defined (TIM17)
#define LL_GPDMA1_REQUEST_TIM17_CH1      39U     /*!< GPDMA1 HW request is TIM17_CH1     */
#define LL_GPDMA1_REQUEST_TIM17_UP       40U     /*!< GPDMA1 HW request is TIM17_UP      */
#endif /* TIM17 */
#if defined (AES)
#define LL_GPDMA1_REQUEST_AES_IN         41U     /*!< GPDMA1 HW request is AES_IN        */
#define LL_GPDMA1_REQUEST_AES_OUT        42U     /*!< GPDMA1 HW request is AES_OUT       */
#endif /* AES */
#define LL_GPDMA1_REQUEST_HASH_IN        43U     /*!< GPDMA1 HW request is HASH_IN       */
#if defined (SAES)
#define LL_GPDMA1_REQUEST_SAES_IN        44U     /*!< GPDMA1 HW request is SAES_IN       */
#define LL_GPDMA1_REQUEST_SAES_OUT       45U     /*!< GPDMA1 HW request is SAES_OUT      */
#endif /* SAES */
#define LL_GPDMA1_REQUEST_LPTIM1_IC1     46U     /*!< GPDMA1 HW request is LPTIM1_IC1    */
#define LL_GPDMA1_REQUEST_LPTIM1_IC2     47U     /*!< GPDMA1 HW request is LPTIM1_IC2    */
#define LL_GPDMA1_REQUEST_LPTIM1_UE      48U     /*!< GPDMA1 HW request is LPTIM1_UE     */
#if defined (LPTIM2)
#define LL_GPDMA1_REQUEST_LPTIM2_IC1     49U     /*!< GPDMA1 HW request is LPTIM2_IC1    */
#define LL_GPDMA1_REQUEST_LPTIM2_IC2     50U     /*!< GPDMA1 HW request is LPTIM2_IC2    */
#define LL_GPDMA1_REQUEST_LPTIM2_UE      51U     /*!< GPDMA1 HW request is LPTIM2_UE     */
#endif /* LPTIM2 */

/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRIGGER_SELECTION Trigger Selection
  * @{
  */
/* GPDMA1 Hardware Triggers */
#define LL_GPDMA1_TRIGGER_EXTI_LINE0        0U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE0      */
#define LL_GPDMA1_TRIGGER_EXTI_LINE1        1U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE1      */
#define LL_GPDMA1_TRIGGER_EXTI_LINE2        2U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE2      */
#define LL_GPDMA1_TRIGGER_EXTI_LINE3        3U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE3      */
#define LL_GPDMA1_TRIGGER_EXTI_LINE4        4U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE4      */
#define LL_GPDMA1_TRIGGER_EXTI_LINE5        5U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE5      */
#define LL_GPDMA1_TRIGGER_EXTI_LINE6        6U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE6      */
#define LL_GPDMA1_TRIGGER_EXTI_LINE7        7U       /*!< GPDMA1 HW Trigger signal is EXTI_LINE7      */
#define LL_GPDMA1_TRIGGER_TAMP_TRG1         8U       /*!< GPDMA1 HW Trigger signal is TAMP_TRG1       */
#define LL_GPDMA1_TRIGGER_TAMP_TRG2         9U       /*!< GPDMA1 HW Trigger signal is TAMP_TRG2       */
#define LL_GPDMA1_TRIGGER_TAMP_TRG3         10U      /*!< GPDMA1 HW Trigger signal is TAMP_TRG3       */
#define LL_GPDMA1_TRIGGER_LPTIM1_CH1        11U      /*!< GPDMA1 HW Trigger signal is LPTIM1_CH1      */
#define LL_GPDMA1_TRIGGER_LPTIM1_CH2        12U      /*!< GPDMA1 HW Trigger signal is LPTIM1_CH2      */
#if defined (LPTIM2)
#define LL_GPDMA1_TRIGGER_LPTIM2_CH1        13U      /*!< GPDMA1 HW Trigger signal is LPTIM2_CH1      */
#define LL_GPDMA1_TRIGGER_LPTIM2_CH2        14U      /*!< GPDMA1 HW Trigger signal is LPTIM2_CH2      */
#endif /* LPTIM2 */
#if defined (COMP1)
#define LL_GPDMA1_TRIGGER_COMP1_OUT         15U      /*!< GPDMA1 HW Trigger signal is COMP1_OUT       */
#endif /* COMP1 */
#if defined (COMP2)
#define LL_GPDMA1_TRIGGER_COMP2_OUT         16U      /*!< GPDMA1 HW Trigger signal is COMP2_OUT       */
#endif /* COMP2 */
#define LL_GPDMA1_TRIGGER_RTC_ALRA_TRG      17U      /*!< GPDMA1 HW Trigger signal is RTC_ALRA_TRG    */
#define LL_GPDMA1_TRIGGER_RTC_ALRB_TRG      18U      /*!< GPDMA1 HW Trigger signal is RTC_ALRB_TRG    */
#define LL_GPDMA1_TRIGGER_RTC_WUT_TRG       19U      /*!< GPDMA1 HW Trigger signal is RTC_WUT_TRG     */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH0_TCF    20U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH0_TCF  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH1_TCF    21U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH1_TCF  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH2_TCF    22U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH2_TCF  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH3_TCF    23U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH3_TCF  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH4_TCF    24U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH4_TCF  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH5_TCF    25U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH5_TCF  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH6_TCF    26U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH6_TCF  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH7_TCF    27U      /*!< GPDMA1 HW Trigger signal is GPDMA1_CH7_TCF  */
#define LL_GPDMA1_TRIGGER_TIM2_TRGO         28U      /*!< GPDMA1 HW Trigger signal is TIM2_TRGO       */
#define LL_GPDMA1_TRIGGER_ADC4_AWD1         29U      /*!< GPDMA1 HW Trigger signal is ADC4_ADW1       */
#if defined (TIM3)
#define LL_GPDMA1_TRIGGER_TIM3_TRGO         30U      /*!< GPDMA1 HW Trigger signal is TIM3_TRGO       */
#endif /* TIM3 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup DMA_LL_Exported_Macros DMA Exported Macros
  * @{
  */

/** @defgroup DMA_LL_EM_COMMON_WRITE_READ_REGISTERS Common Write and Read Registers macros
  * @{
  */
/**
  * @brief  Write a value in DMA register.
  * @param  __INSTANCE__ DMA Instance.
  * @param  __REG__      Register to be written.
  * @param  __VALUE__    Value to be written in the register.
  * @retval None.
  */
#define LL_DMA_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DMA register.
  * @param  __INSTANCE__ DMA Instance.
  * @param  __REG__      Register to be read.
  * @retval Register value.
  */
#define LL_DMA_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/** @defgroup DMA_LL_EM_CONVERT_DMAxCHANNELy Convert DMAxChannely
  * @{
  */
/**
  * @brief  Convert DMAx_Channely into DMAx.
  * @param  __CHANNEL_INSTANCE__ DMAx_Channely.
  * @retval DMAx.
  */
#define LL_DMA_GET_INSTANCE(__CHANNEL_INSTANCE__) \
  (GPDMA1)

/**
  * @brief  Convert DMAx_Channely into LL_DMA_CHANNEL_y.
  * @param  __CHANNEL_INSTANCE__ DMAx_Channely.
  * @retval LL_DMA_CHANNEL_y.
  */
#define LL_DMA_GET_CHANNEL(__CHANNEL_INSTANCE__) \
  (((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)GPDMA1_Channel0))  ? LL_DMA_CHANNEL_0  : \
   ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)GPDMA1_Channel1))  ? LL_DMA_CHANNEL_1  : \
   ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)GPDMA1_Channel2))  ? LL_DMA_CHANNEL_2  : \
   ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)GPDMA1_Channel3))  ? LL_DMA_CHANNEL_3  : \
   ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)GPDMA1_Channel4))  ? LL_DMA_CHANNEL_4  : \
   ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)GPDMA1_Channel5))  ? LL_DMA_CHANNEL_5  : \
   ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)GPDMA1_Channel6))  ? LL_DMA_CHANNEL_6  : \
   LL_DMA_CHANNEL_7)

/**
  * @brief  Convert DMA Instance DMAx and LL_DMA_CHANNEL_y into DMAx_Channely.
  * @param  __DMA_INSTANCE__ DMAx.
  * @param  __CHANNEL__      LL_DMA_CHANNEL_y.
  * @retval DMAx_Channely.
  */
#define LL_DMA_GET_CHANNEL_INSTANCE(__DMA_INSTANCE__, __CHANNEL__) \
  ((((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)GPDMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_0))) \
   ? GPDMA1_Channel0  :                                                                                                \
   (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)GPDMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_1))) \
   ? GPDMA1_Channel1  :                                                                                                \
   (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)GPDMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_2))) \
   ? GPDMA1_Channel2  :                                                                                                \
   (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)GPDMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_3))) \
   ? GPDMA1_Channel3  :                                                                                                \
   (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)GPDMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_4))) \
   ? GPDMA1_Channel4  :                                                                                                \
   (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)GPDMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_5))) \
   ? GPDMA1_Channel5  :                                                                                                \
   (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)GPDMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)LL_DMA_CHANNEL_6))) \
   ? GPDMA1_Channel6 :  GPDMA1_Channel7)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup DMA_LL_Exported_Functions DMA Exported Functions
  * @{
  */

/** @defgroup DMA_LL_EF_Configuration Configuration
  * @{
  */
/**
  * @brief Enable channel.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          EN            LL_DMA_EnableChannel
  * @param  DMAx DMAx Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_EN);
}

/**
  * @brief Disable channel.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          EN            LL_DMA_DisableChannel
  * @param  DMAx DMAx Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR,
          (DMA_CCR_SUSP | DMA_CCR_RESET));
}

/**
  * @brief Check if channel is enabled or disabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          EN            LL_DMA_IsEnabledChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_EN)
           == (DMA_CCR_EN)) ? 1UL : 0UL);
}

/**
  * @brief Reset channel.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          RESET            LL_DMA_ResetChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ResetChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_RESET);
}

/**
  * @brief Suspend channel.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          SUSP            LL_DMA_SuspendChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SuspendChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_SUSP);
}

/**
  * @brief Resume channel.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          SUSP            LL_DMA_ResumeChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ResumeChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_SUSP);
}

/**
  * @brief Check if channel is suspended.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          SUSP            LL_DMA_IsSuspendedChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsSuspendedChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_SUSP)
           == (DMA_CCR_SUSP)) ? 1UL : 0UL);
}

/**
  * @brief Set linked-list base address.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLBAR          LBA           LL_DMA_SetLinkedListBaseAddr
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  LinkedListBaseAddr Between 0 to 0xFFFF0000 (where the 4 LSB bytes
  *         are always 0)
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetLinkedListBaseAddr(const DMA_TypeDef *DMAx, uint32_t Channel,
                                                  uint32_t LinkedListBaseAddr)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLBAR, DMA_CLBAR_LBA,
             (LinkedListBaseAddr & DMA_CLBAR_LBA));
}

/**
  * @brief Get linked-list base address.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLBAR          LBA           LL_DMA_GetLinkedListBaseAddr
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Value between 0 to 0xFFFF0000 (where the 4 LSB bytes are always 0)
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkedListBaseAddr(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLBAR, DMA_CLBAR_LBA));
}

/**
  * @brief Configure all parameters linked to channel control.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR         PRIO           LL_DMA_ConfigControl\n
  *         CCR         LAP            LL_DMA_ConfigControl\n
  *         CCR         LSM            LL_DMA_ConfigControl
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_LOW_PRIORITY_LOW_WEIGHT  or @ref LL_DMA_LOW_PRIORITY_MID_WEIGHT or
  *              @ref LL_DMA_LOW_PRIORITY_HIGH_WEIGHT or @ref LL_DMA_HIGH_PRIORITY
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT0     or @ref LL_DMA_LINK_ALLOCATED_PORT1
  *         @arg @ref LL_DMA_LSM_FULL_EXECUTION       or @ref LL_DMA_LSM_1LINK_EXECUTION
  *@retval None.
  */
__STATIC_INLINE void LL_DMA_ConfigControl(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Configuration)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR,
             (DMA_CCR_PRIO | DMA_CCR_LAP | DMA_CCR_LSM), Configuration);
}

/**
  * @brief Set priority level.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          PRIO           LL_DMA_SetChannelPriorityLevel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Priority This parameter can be one of the following values:
  *         @arg @ref LL_DMA_LOW_PRIORITY_LOW_WEIGHT
  *         @arg @ref LL_DMA_LOW_PRIORITY_MID_WEIGHT
  *         @arg @ref LL_DMA_LOW_PRIORITY_HIGH_WEIGHT
  *         @arg @ref LL_DMA_HIGH_PRIORITY
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetChannelPriorityLevel(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t  Priority)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_PRIO, Priority);
}

/**
  * @brief Get Channel priority level.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          PRIO           LL_DMA_GetChannelPriorityLevel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_LOW_PRIORITY_LOW_WEIGHT
  *         @arg @ref LL_DMA_LOW_PRIORITY_MID_WEIGHT
  *         @arg @ref LL_DMA_LOW_PRIORITY_HIGH_WEIGHT
  *         @arg @ref LL_DMA_HIGH_PRIORITY
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelPriorityLevel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_PRIO));
}

/**
  * @brief Set linked-list allocated port.
  * @rmtoll CCR          LAP           LL_DMA_SetLinkAllocatedPort
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  LinkAllocatedPort This parameter can be one of the following values:
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT1
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetLinkAllocatedPort(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t  LinkAllocatedPort)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR,
             DMA_CCR_LAP, LinkAllocatedPort);
}

/**
  * @brief Get linked-list allocated port.
  * @rmtoll CCR          LAP           LL_DMA_GetLinkAllocatedPort
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT1
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkAllocatedPort(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_LAP));
}

/**
  * @brief Set link step mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          LSM           LL_DMA_SetLinkStepMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
    *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  LinkStepMode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_LSM_FULL_EXECUTION
  *         @arg @ref LL_DMA_LSM_1LINK_EXECUTION
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetLinkStepMode(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t LinkStepMode)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_LSM, LinkStepMode);
}

/**
  * @brief Get Link step mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR          LSM           LL_DMA_GetLinkStepMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_LSM_FULL_EXECUTION
  *         @arg @ref LL_DMA_LSM_1LINK_EXECUTION
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkStepMode(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_LSM));
}

/**
  * @brief Configure data transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          DAP           LL_DMA_ConfigTransfer\n
  *         CTR1          DHX           LL_DMA_ConfigTransfer\n
  *         CTR1          DBX           LL_DMA_ConfigTransfer\n
  *         CTR1          DINC          LL_DMA_ConfigTransfer\n
  *         CTR1          SAP           LL_DMA_ConfigTransfer\n
  *         CTR1          SBX           LL_DMA_ConfigTransfer\n
  *         CTR1          PAM           LL_DMA_ConfigTransfer\n
  *         CTR1          SINC          LL_DMA_ConfigTransfer
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT0     or @ref LL_DMA_DEST_ALLOCATED_PORT1
  *         @arg @ref LL_DMA_DEST_HALFWORD_PRESERVE   or @ref LL_DMA_DEST_HALFWORD_EXCHANGE
  *         @arg @ref LL_DMA_DEST_BYTE_PRESERVE       or @ref LL_DMA_DEST_BYTE_EXCHANGE
  *         @arg @ref LL_DMA_SRC_BYTE_PRESERVE        or @ref LL_DMA_SRC_BYTE_EXCHANGE
  *         @arg @ref LL_DMA_DEST_FIXED               or @ref LL_DMA_DEST_INCREMENT
  *         @arg @ref LL_DMA_DEST_DATAWIDTH_BYTE      or @ref LL_DMA_DEST_DATAWIDTH_HALFWORD or
  *              @ref LL_DMA_DEST_DATAWIDTH_WORD
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT0      or @ref LL_DMA_SRC_ALLOCATED_PORT1
  *         @arg @ref LL_DMA_DATA_ALIGN_ZEROPADD      or @ref LL_DMA_DATA_ALIGN_SIGNEXTPADD  or
  *              @ref LL_DMA_DATA_PACK_UNPACK
  *         @arg @ref LL_DMA_SRC_FIXED                or @ref LL_DMA_SRC_INCREMENT
  *         @arg @ref LL_DMA_SRC_DATAWIDTH_BYTE       or @ref LL_DMA_SRC_DATAWIDTH_HALFWORD  or
  *              @ref LL_DMA_SRC_DATAWIDTH_WORD
  *@retval None.
  */
__STATIC_INLINE void LL_DMA_ConfigTransfer(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Configuration)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1,
             DMA_CTR1_DAP | DMA_CTR1_DHX | DMA_CTR1_DBX | DMA_CTR1_SBX | DMA_CTR1_DINC | DMA_CTR1_SINC | \
             DMA_CTR1_SAP | DMA_CTR1_PAM | DMA_CTR1_DDW_LOG2 | DMA_CTR1_SDW_LOG2, Configuration);
}

/**
  * @brief Configure source and destination burst length.
  * @rmtoll CTR1          DBL_1           LL_DMA_SetDestBurstLength\n
  * @rmtoll CTR1          SBL_1           LL_DMA_SetDestBurstLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcBurstLength Between 1 to 64
  * @param  DestBurstLength Between 1 to 64
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ConfigBurstLength(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcBurstLength,
                                              uint32_t DestBurstLength)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1,
             (DMA_CTR1_SBL_1 | DMA_CTR1_DBL_1), (((SrcBurstLength - 1U) << DMA_CTR1_SBL_1_Pos) & DMA_CTR1_SBL_1) | \
             (((DestBurstLength - 1U) << DMA_CTR1_DBL_1_Pos) & DMA_CTR1_DBL_1));
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief Configure all secure parameters linked to DMA channel.
  * @note  This API is used for all available DMA channels.
  * @rmtoll SECCFGR       SEC            LL_DMA_ConfigChannelSecure\n
  * @rmtoll CTR1          SSEC           LL_DMA_ConfigChannelSecure\n
  * @rmtoll CTR1          DSEC           LL_DMA_ConfigChannelSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_CHANNEL_NSEC      or @ref LL_DMA_CHANNEL_SEC
  *         @arg @ref LL_DMA_CHANNEL_SRC_NSEC  or @ref LL_DMA_CHANNEL_SRC_SEC
  *         @arg @ref LL_DMA_CHANNEL_DEST_NSEC or @ref LL_DMA_CHANNEL_DEST_SEC
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ConfigChannelSecure(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Configuration)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(DMAx->SECCFGR, (DMA_SECCFGR_SEC0 << Channel), ((Configuration & LL_DMA_CHANNEL_SEC) << Channel));
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1,
             (DMA_CTR1_SSEC | DMA_CTR1_DSEC), (Configuration & (~LL_DMA_CHANNEL_SEC)));
}

/**
  * @brief Enable security attribute of the DMA transfer to the destination.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          DSEC           LL_DMA_EnableChannelDestSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableChannelDestSecure(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DSEC);
}

/**
  * @brief Disable security attribute of the DMA transfer to the destination.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          DSEC           LL_DMA_DisableChannelDestSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableChannelDestSecure(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DSEC);
}
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

#if defined (DMA_SECCFGR_SEC0)
/**
  * @brief Check security attribute of the DMA transfer to the destination.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          DSEC           LL_DMA_IsEnabledChannelDestSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannelDestSecure(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DSEC)
           == (DMA_CTR1_DSEC)) ? 1UL : 0UL);
}
#endif /* DMA_SECCFGR_SEC0 */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief Enable security attribute of the DMA transfer from the source.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          SSEC           LL_DMA_EnableChannelSrcSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableChannelSrcSecure(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SSEC);
}

/**
  * @brief Disable security attribute of the DMA transfer from the source.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          SSEC           LL_DMA_DisableChannelSrcSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableChannelSrcSecure(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SSEC);
}
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

#if defined (DMA_SECCFGR_SEC0)
/**
  * @brief Check security attribute of the DMA transfer from the source.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          SSEC           LL_DMA_IsEnabledChannelSrcSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannelSrcSecure(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SSEC)
           == (DMA_CTR1_SSEC)) ? 1UL : 0UL);
}
#endif /* DMA_SECCFGR_SEC0 */

/**
  * @brief Set destination allocated port.
  * @rmtoll CTR1          DAP           LL_DMA_SetDestAllocatedPort
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DestAllocatedPort This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT1
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDestAllocatedPort(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t DestAllocatedPort)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DAP,
             DestAllocatedPort);
}

/**
  * @brief Get destination allocated port.
  * @rmtoll CTR1          DAP           LL_DMA_GetDestAllocatedPort
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT1
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestAllocatedPort(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DAP));
}

/**
  * @brief Set destination half-word exchange.
  * @rmtoll CTR1          DHX            LL_DMA_SetDestHWordExchange
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DestHWordExchange This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_HALFWORD_PRESERVE
  *         @arg @ref LL_DMA_DEST_HALFWORD_EXCHANGE
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDestHWordExchange(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t DestHWordExchange)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DHX,
             DestHWordExchange);
}

/**
  * @brief Get destination half-word exchange.
  * @rmtoll CTR1          DHX            LL_DMA_GetDestHWordExchange
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_HALFWORD_PRESERVE
  *         @arg @ref LL_DMA_DEST_HALFWORD_EXCHANGE
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestHWordExchange(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DHX));
}

/**
  * @brief Set destination byte exchange.
  * @rmtoll CTR1          DBX            LL_DMA_SetDestByteExchange
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DestByteExchange This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_BYTE_PRESERVE
  *         @arg @ref LL_DMA_DEST_BYTE_EXCHANGE
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDestByteExchange(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t DestByteExchange)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DBX,
             DestByteExchange);
}

/**
  * @brief Get destination byte exchange.
  * @rmtoll CTR1          DBX            LL_DMA_GetDestByteExchange
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_BYTE_PRESERVE
  *         @arg @ref LL_DMA_DEST_BYTE_EXCHANGE
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestByteExchange(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DBX));
}

/**
  * @brief Set source byte exchange.
  * @rmtoll CTR1          SBX            LL_DMA_SetSrcByteExchange
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcByteExchange This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_BYTE_PRESERVE
  *         @arg @ref LL_DMA_SRC_BYTE_EXCHANGE
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetSrcByteExchange(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcByteExchange)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SBX,
             SrcByteExchange);
}

/**
  * @brief Get source byte exchange.
  * @rmtoll CTR1          SBX            LL_DMA_GetSrcByteExchange
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_BYTE_PRESERVE
  *         @arg @ref LL_DMA_SRC_BYTE_EXCHANGE
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcByteExchange(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SBX));
}

/**
  * @brief Set destination burst length.
  * @rmtoll CTR1          DBL_1           LL_DMA_SetDestBurstLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DestBurstLength Between 1 to 64
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDestBurstLength(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t DestBurstLength)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DBL_1,
             ((DestBurstLength - 1U) << DMA_CTR1_DBL_1_Pos) & DMA_CTR1_DBL_1);
}

/**
  * @brief Get destination burst length.
  * @rmtoll CTR1          DBL_1           LL_DMA_GetDestBurstLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Between 1 to 64.
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestBurstLength(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1,
                    DMA_CTR1_DBL_1) >> DMA_CTR1_DBL_1_Pos) + 1U);
}

/**
  * @brief Set destination increment mode.
  * @rmtoll CTR1          DINC           LL_DMA_SetDestIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DestInc This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_FIXED
  *         @arg @ref LL_DMA_DEST_INCREMENT
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDestIncMode(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t DestInc)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DINC, DestInc);
}

/**
  * @brief Get destination increment mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          DINC           LL_DMA_GetDestIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_FIXED
  *         @arg @ref LL_DMA_DEST_INCREMENT
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestIncMode(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DINC));
}

/**
  * @brief Set destination data width.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          DDW_LOG2           LL_DMA_SetDestDataWidth
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DestDataWidth This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATAWIDTH_BYTE
  *         @arg @ref LL_DMA_DEST_DATAWIDTH_HALFWORD
  *         @arg @ref LL_DMA_DEST_DATAWIDTH_WORD
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDestDataWidth(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t  DestDataWidth)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DDW_LOG2,
             DestDataWidth);
}

/**
  * @brief Get destination data width.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          DDW_LOG2           LL_DMA_GetDestDataWidth
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATAWIDTH_BYTE
  *         @arg @ref LL_DMA_DEST_DATAWIDTH_HALFWORD
  *         @arg @ref LL_DMA_DEST_DATAWIDTH_WORD
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestDataWidth(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_DDW_LOG2));
}

/**
  * @brief Set source allocated port.
  * @rmtoll CTR1          SAP           LL_DMA_SetSrcAllocatedPort
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcAllocatedPort This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT1
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetSrcAllocatedPort(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcAllocatedPort)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SAP,
             SrcAllocatedPort);
}

/**
  * @brief Get source allocated port.
  * @rmtoll CTR1          SAP           LL_DMA_GetSrcAllocatedPort
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT1
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcAllocatedPort(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SAP));
}

/**
  * @brief Set data alignment mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          PAM           LL_DMA_SetDataAlignment
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DataAlignment This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DATA_ALIGN_ZEROPADD
  *         @arg @ref LL_DMA_DATA_ALIGN_SIGNEXTPADD
  *         @arg @ref LL_DMA_DATA_PACK_UNPACK
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDataAlignment(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t DataAlignment)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_PAM,
             DataAlignment);
}

/**
  * @brief Get data alignment mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          PAM           LL_DMA_GetDataAlignment
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DATA_ALIGN_ZEROPADD
  *         @arg @ref LL_DMA_DATA_ALIGN_SIGNEXTPADD
  *         @arg @ref LL_DMA_DATA_PACK_UNPACK
  */
__STATIC_INLINE uint32_t LL_DMA_GetDataAlignment(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_PAM));
}

/**
  * @brief Set source burst length.
  * @rmtoll CTR1          SBL_1           LL_DMA_SetSrcBurstLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcBurstLength Between 1 to 64
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetSrcBurstLength(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcBurstLength)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SBL_1,
             ((SrcBurstLength - 1U) << DMA_CTR1_SBL_1_Pos) & DMA_CTR1_SBL_1);
}

/**
  * @brief Get source burst length.
  * @rmtoll CTR1          SBL_1           LL_DMA_GetSrcBurstLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Between 1 to 64
  * @retval None.
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcBurstLength(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1,
                    DMA_CTR1_SBL_1) >> DMA_CTR1_SBL_1_Pos) + 1U);
}

/**
  * @brief Set source increment mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          SINC           LL_DMA_SetSrcIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcInc This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_FIXED
  *         @arg @ref LL_DMA_SRC_INCREMENT
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetSrcIncMode(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcInc)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SINC, SrcInc);
}

/**
  * @brief Get source increment mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          SINC           LL_DMA_GetSrcIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_FIXED
  *         @arg @ref LL_DMA_SRC_INCREMENT
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcIncMode(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SINC));
}

/**
  * @brief Set source data width.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          SDW_LOG2           LL_DMA_SetSrcDataWidth
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcDataWidth This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_DATAWIDTH_BYTE
  *         @arg @ref LL_DMA_SRC_DATAWIDTH_HALFWORD
  *         @arg @ref LL_DMA_SRC_DATAWIDTH_WORD
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetSrcDataWidth(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t  SrcDataWidth)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SDW_LOG2,
             SrcDataWidth);
}

/**
  * @brief Get Source Data width.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR1          SDW_LOG2           LL_DMA_GetSrcDataWidth
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_DATAWIDTH_BYTE
  *         @arg @ref LL_DMA_SRC_DATAWIDTH_HALFWORD
  *         @arg @ref LL_DMA_SRC_DATAWIDTH_WORD
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcDataWidth(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR1, DMA_CTR1_SDW_LOG2));
}

/**
  * @brief Configure channel transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2        TCEM               LL_DMA_ConfigChannelTransfer\n
  *         CTR2        TRIGPOL            LL_DMA_ConfigChannelTransfer\n
  *         CTR2        TRIGM              LL_DMA_ConfigChannelTransfer\n
  *         CTR2        BREQ               LL_DMA_ConfigChannelTransfer\n
  *         CTR2        DREQ               LL_DMA_ConfigChannelTransfer\n
  *         CTR2        SWREQ              LL_DMA_ConfigChannelTransfer
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_TCEM_BLK_TRANSFER          or @ref LL_DMA_TCEM_RPT_BLK_TRANSFER      or
  *              @ref LL_DMA_TCEM_EACH_LLITEM_TRANSFER  or @ref LL_DMA_TCEM_LAST_LLITEM_TRANSFER
  *         @arg @ref LL_DMA_HWREQUEST_SINGLEBURST      or @ref LL_DMA_HWREQUEST_BLK
  *         @arg @ref LL_DMA_TRIG_POLARITY_MASKED       or @ref LL_DMA_TRIG_POLARITY_RISING       or
  *              @ref LL_DMA_TRIG_POLARITY_FALLING
  *         @arg @ref LL_DMA_TRIGM_BLK_TRANSFER         or @ref LL_DMA_TRIGM_RPT_BLK_TRANSFER     or
  *              @ref LL_DMA_TRIGM_LLI_LINK_TRANSFER    or @ref LL_DMA_TRIGM_SINGLBURST_TRANSFER
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY or @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH or
  *              @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  *@retval None.
  */
__STATIC_INLINE void LL_DMA_ConfigChannelTransfer(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Configuration)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2,
             (DMA_CTR2_TCEM | DMA_CTR2_TRIGPOL | DMA_CTR2_TRIGM | DMA_CTR2_DREQ | DMA_CTR2_SWREQ | DMA_CTR2_BREQ),
             Configuration);
}

/**
  * @brief Set transfer event mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          TCEM           LL_DMA_SetTransferEventMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  TransferEventMode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_TCEM_BLK_TRANSFER
  *         @arg @ref LL_DMA_TCEM_RPT_BLK_TRANSFER
  *         @arg @ref LL_DMA_TCEM_EACH_LLITEM_TRANSFER
  *         @arg @ref LL_DMA_TCEM_LAST_LLITEM_TRANSFER
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetTransferEventMode(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t  TransferEventMode)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_TCEM,
             TransferEventMode);
}

/**
  * @brief Get transfer event mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          TCEM           LL_DMA_GetTransferEventMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_TCEM_BLK_TRANSFER
  *         @arg @ref LL_DMA_TCEM_RPT_BLK_TRANSFER
  *         @arg @ref LL_DMA_TCEM_EACH_LLITEM_TRANSFER
  *         @arg @ref LL_DMA_TCEM_LAST_LLITEM_TRANSFER
  */
__STATIC_INLINE uint32_t LL_DMA_GetTransferEventMode(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_TCEM));
}

/**
  * @brief Set trigger polarity.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          TRIGPOL            LL_DMA_SetTriggerPolarity
    * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  TriggerPolarity This parameter can be one of the following values:
  *         @arg @ref LL_DMA_TRIG_POLARITY_MASKED
  *         @arg @ref LL_DMA_TRIG_POLARITY_RISING
  *         @arg @ref LL_DMA_TRIG_POLARITY_FALLING
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetTriggerPolarity(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t TriggerPolarity)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_TRIGPOL,
             TriggerPolarity);
}

/**
  * @brief Get trigger polarity.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          TRIGPOL            LL_DMA_GetTriggerPolarity
    * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_TRIG_POLARITY_MASKED
  *         @arg @ref LL_DMA_TRIG_POLARITY_RISING
  *         @arg @ref LL_DMA_TRIG_POLARITY_FALLING
  */
__STATIC_INLINE uint32_t LL_DMA_GetTriggerPolarity(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_TRIGPOL));
}

/**
  * @brief Set trigger Mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          TRIGM            LL_DMA_SetTriggerMode
    * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  TriggerMode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_TRIGM_BLK_TRANSFER
  *         @arg @ref LL_DMA_TRIGM_LLI_LINK_TRANSFER
  *         @arg @ref LL_DMA_TRIGM_SINGLBURST_TRANSFER
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetTriggerMode(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t TriggerMode)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_TRIGM,
             TriggerMode);
}

/**
  * @brief Get trigger Mode.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          TRIGM            LL_DMA_GetTriggerMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_TRIGM_BLK_TRANSFER
  *         @arg @ref LL_DMA_TRIGM_LLI_LINK_TRANSFER
  *         @arg @ref LL_DMA_TRIGM_SINGLBURST_TRANSFER
  */
__STATIC_INLINE uint32_t LL_DMA_GetTriggerMode(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_TRIGM));
}

/**
  * @brief Set destination hardware and software transfer request.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          DREQ           LL_DMA_SetDataTransferDirection\n
  * @rmtoll CTR2          SWREQ          LL_DMA_SetDataTransferDirection
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Direction This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDataTransferDirection(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Direction)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2,
             DMA_CTR2_DREQ | DMA_CTR2_SWREQ, Direction);
}

/**
  * @brief Get destination hardware and software transfer request.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          DREQ           LL_DMA_GetDataTransferDirection\n
  * @rmtoll CTR2          SWREQ          LL_DMA_GetDataTransferDirection
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  */
__STATIC_INLINE uint32_t LL_DMA_GetDataTransferDirection(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2,
                   DMA_CTR2_DREQ | DMA_CTR2_SWREQ));
}

/**
  * @brief Set block hardware request.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          BREQ           LL_DMA_SetBlkHWRequest\n
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  BlkHWRequest This parameter can be one of the following values:
  *         @arg @ref LL_DMA_HWREQUEST_SINGLEBURST
  *         @arg @ref LL_DMA_HWREQUEST_BLK
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetBlkHWRequest(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t BlkHWRequest)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_BREQ,
             BlkHWRequest);
}

/**
  * @brief Get block hardware request.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2          BREQ           LL_DMA_GetBlkHWRequest\n
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_HWREQUEST_SINGLEBURST
  *         @arg @ref LL_DMA_HWREQUEST_BLK
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkHWRequest(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_BREQ));
}

/**
  * @brief Set hardware request.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2         REQSEL     LL_DMA_SetPeriphRequest
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Request This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_REQUEST_ADC4
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_EVC (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_A (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_B (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_UP
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_TRIG
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_UP
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH2 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH3 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH4 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_UP (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_TRIG (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_UP
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_CH1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_UP (*)
  *         @arg @ref LL_GPDMA1_REQUEST_AES_IN (*)
  *         @arg @ref LL_GPDMA1_REQUEST_AES_OUT (*)
  *         @arg @ref LL_GPDMA1_REQUEST_HASH_IN
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_IN (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_OUT (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_UE
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC2 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_UE (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_EVC (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_EVC (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH2 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH3 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH4 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_UP (*)
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_TX (*)
  * @note   (*) Availability depends on devices.
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetPeriphRequest(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Request)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_REQSEL, Request);
}

/**
  * @brief  Get hardware request.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2         REQSEL     LL_DMA_GetPeriphRequest
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPDMA1_REQUEST_ADC4
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_EVC (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_A (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_B (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CH4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_UP
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_TRIG
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CH4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_UP
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH2 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH3 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CH4 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_UP (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_TRIG (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_UP
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_CH1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_UP (*)
  *         @arg @ref LL_GPDMA1_REQUEST_AES_IN (*)
  *         @arg @ref LL_GPDMA1_REQUEST_AES_OUT (*)
  *         @arg @ref LL_GPDMA1_REQUEST_HASH_IN
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_IN (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_OUT (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_UE
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC2 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_UE (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_EVC (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_TX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_EVC (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH1 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH2 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH3 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CH4 (*)
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_UP (*)
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_RX (*)
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_TX (*)
  * @note   (*) Availability depends on devices.
  */
__STATIC_INLINE  uint32_t LL_DMA_GetPeriphRequest(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_REQSEL));
}

/**
  * @brief Set hardware trigger.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2         TRIGSEL     LL_DMA_SetHWTrigger
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  Trigger This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE4
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE5
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE6
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE7
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH1 (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH2 (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP1_OUT (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP2_OUT (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC4_AWD1
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM3_TRGO (*)
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetHWTrigger(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Trigger)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2, DMA_CTR2_TRIGSEL,
             (Trigger << DMA_CTR2_TRIGSEL_Pos) & DMA_CTR2_TRIGSEL);
}

/**
  * @brief Get hardware triggers.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CTR2         TRIGSEL     LL_DMA_GetHWTrigger
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE4
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE5
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE6
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE7
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH1 (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH2 (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP1_OUT (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP2_OUT (*)
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC4_AWD1
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM3_TRGO (*)
  */
__STATIC_INLINE  uint32_t LL_DMA_GetHWTrigger(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CTR2,
                   DMA_CTR2_TRIGSEL) >> DMA_CTR2_TRIGSEL_Pos);
}

/**
  * @brief  Set block data length in bytes to transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CBR1        BNDT         LL_DMA_SetBlkDataLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  BlkDataLength Between 0 to 0x0000FFFF
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetBlkDataLength(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t BlkDataLength)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CBR1, DMA_CBR1_BNDT,
             BlkDataLength);
}

/**
  * @brief  Get block data length in bytes to transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CBR1        BNDT         LL_DMA_GetBlkDataLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Between 0 to 0x0000FFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkDataLength(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CBR1, DMA_CBR1_BNDT));
}

/**
  * @brief Configure the source and destination addresses.
  * @note  This API is used for all available DMA channels.
  * @note   This API must not be called when the DMA Channel is enabled.
  * @rmtoll CSAR        SA          LL_DMA_ConfigAddresses\n
  *         CDAR        DA          LL_DMA_ConfigAddresses
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcAddress Between 0 to 0xFFFFFFFF
  * @param  DestAddress Between 0 to 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ConfigAddresses(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcAddress, uint32_t
                                            DestAddress)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSAR, SrcAddress);
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CDAR, DestAddress);
}

/**
  * @brief Set source address.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSAR        SA         LL_DMA_SetSrcAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  SrcAddress Between 0 to 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetSrcAddress(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcAddress)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSAR, SrcAddress);
}

/**
  * @brief  Get source address.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSAR        SA         LL_DMA_GetSrcAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Between 0 to 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcAddress(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSAR));
}

/**
  * @brief  Set destination address.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CDAR        DA         LL_DMA_SetDestAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  DestAddress Between 0 to 0xFFFFFFFF
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetDestAddress(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t DestAddress)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CDAR, DestAddress);
}

/**
  * @brief  Get destination address.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CDAR        DA         LL_DMA_GetDestAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Between 0 to 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestAddress(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CDAR));
}


/**
  * @brief Configure registers update and node address offset during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UT1            LL_DMA_ConfigLinkUpdate\n
  * @rmtoll CLLR          UT2            LL_DMA_ConfigLinkUpdate\n
  * @rmtoll CLLR          UB1            LL_DMA_ConfigLinkUpdate\n
  * @rmtoll CLLR          USA            LL_DMA_ConfigLinkUpdate\n
  * @rmtoll CLLR          UDA            LL_DMA_ConfigLinkUpdate\n
  * @rmtoll CLLR          ULL            LL_DMA_ConfigLinkUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  RegistersUpdate This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_UPDATE_CTR1
  *         @arg @ref LL_DMA_UPDATE_CTR2
  *         @arg @ref LL_DMA_UPDATE_CBR1
  *         @arg @ref LL_DMA_UPDATE_CSAR
  *         @arg @ref LL_DMA_UPDATE_CDAR
  *         @arg @ref LL_DMA_UPDATE_CLLR
  * @param  LinkedListAddrOffset Between 0 to 0x0000FFFC by increment of 4 Bytes.
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ConfigLinkUpdate(const DMA_TypeDef *DMAx, uint32_t Channel, uint32_t RegistersUpdate,
                                             uint32_t LinkedListAddrOffset)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR,
             (DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA  | \
              DMA_CLLR_ULL | DMA_CLLR_LA), (RegistersUpdate | (LinkedListAddrOffset & DMA_CLLR_LA)));
}

/**
  * @brief Enable CTR1 update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UT1            LL_DMA_EnableCTR1Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableCTR1Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UT1);
}

/**
  * @brief Disable CTR1 update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UT1            LL_DMA_DisableCTR1Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableCTR1Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UT1);
}

/**
  * @brief Check if CTR1 update during the link transfer is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UT1            LL_DMA_IsEnabledCTR1Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCTR1Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UT1)
           == (DMA_CLLR_UT1)) ? 1UL : 0UL);
}

/**
  * @brief Enable CTR2 update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UT2            LL_DMA_EnableCTR2Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableCTR2Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UT2);
}

/**
  * @brief Disable CTR2 update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UT2            LL_DMA_DisableCTR2Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableCTR2Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UT2);
}

/**
  * @brief Check if CTR2 update during the link transfer is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UT2            LL_DMA_IsEnabledCTR2Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCTR2Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UT2)
           == (DMA_CLLR_UT2)) ? 1UL : 0UL);
}

/**
  * @brief Enable CBR1 update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UB1            LL_DMA_EnableCBR1Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableCBR1Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UB1);
}

/**
  * @brief Disable CBR1 update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UB1            LL_DMA_DisableCBR1Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableCBR1Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UB1);
}

/**
  * @brief Check if CBR1 update during the link transfer is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UB1            LL_DMA_IsEnabledCBR1Update
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCBR1Update(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UB1)
           == (DMA_CLLR_UB1)) ? 1UL : 0UL);
}

/**
  * @brief Enable CSAR update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          USA            LL_DMA_EnableCSARUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableCSARUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_USA);
}

/**
  * @brief Disable CSAR update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          USA            LL_DMA_DisableCSARUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableCSARUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_USA);
}

/**
  * @brief Check if CSAR update during the link transfer is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          USA            LL_DMA_IsEnabledCSARUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCSARUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_USA)
           == (DMA_CLLR_USA)) ? 1UL : 0UL);
}

/**
  * @brief Enable CDAR update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UDA            LL_DMA_EnableCDARUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableCDARUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UDA);
}

/**
  * @brief Disable CDAR update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UDA            LL_DMA_DisableCDARUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableCDARUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UDA);
}

/**
  * @brief Check if CDAR update during the link transfer is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          UDA            LL_DMA_IsEnabledCDARUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCDARUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_UDA)
           == (DMA_CLLR_UDA)) ? 1UL : 0UL);
}


/**
  * @brief Enable CLLR update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          ULL            LL_DMA_EnableCLLRUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableCLLRUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_ULL);
}

/**
  * @brief Disable CLLR update during the link transfer.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          ULL            LL_DMA_DisableCLLRUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableCLLRUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_ULL);
}

/**
  * @brief Check if CLLR update during the link transfer is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          ULL            LL_DMA_IsEnabledCLLRUpdate
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCLLRUpdate(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_ULL)
           == (DMA_CLLR_ULL)) ? 1UL : 0UL);
}

/**
  * @brief Set linked list address offset.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          LA           LL_DMA_SetLinkedListAddrOffset
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @param  LinkedListAddrOffset Between 0 to 0x0000FFFC by increment of 4 Bytes.
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_SetLinkedListAddrOffset(const DMA_TypeDef *DMAx, uint32_t Channel,
                                                    uint32_t  LinkedListAddrOffset)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  MODIFY_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR, DMA_CLLR_LA,
             (LinkedListAddrOffset & DMA_CLLR_LA));
}

/**
  * @brief Get linked list address offset.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CLLR          LA           LL_DMA_GetLinkedListAddrOffset
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Between 0 to 0x0000FFFC.
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkedListAddrOffset(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CLLR,
                   DMA_CLLR_LA) >> DMA_CLLR_LA_Pos);
}

/**
  * @brief Get FIFO level.
  * @rmtoll CSR          FIFOL           LL_DMA_GetFIFOLevel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval Between 0 to 0x000000FF.
  */
__STATIC_INLINE uint32_t LL_DMA_GetFIFOLevel(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return (READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR,
                   DMA_CSR_FIFOL) >> DMA_CSR_FIFOL_Pos);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief Enable the DMA channel secure attribute.
  * @note  This API is used for all available DMA channels.
  * @rmtoll SECCFGR  SECx    LL_DMA_EnableChannelSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableChannelSecure(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(DMAx->SECCFGR, (DMA_SECCFGR_SEC0 << (Channel & 0x0000000FU)));
}

/**
  * @brief Disable the DMA channel secure attribute.
  * @note  This API is used for all available DMA channels.
  * @rmtoll SECCFGR  SECx    LL_DMA_DisableChannelSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableChannelSecure(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(DMAx->SECCFGR, (DMA_SECCFGR_SEC0 << (Channel & 0x0000000FU)));
}
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

#if defined (DMA_SECCFGR_SEC0)
/**
  * @brief Check if DMA channel secure is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll SECCFGR             SECx          LL_DMA_IsEnabledChannelSecure
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannelSecure(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  return ((READ_BIT(DMAx->SECCFGR, (DMA_SECCFGR_SEC0 << (Channel & 0x0000000FU)))
           == (DMA_SECCFGR_SEC0 << (Channel & 0x0000000FU))) ? 1UL : 0UL);
}
#endif /* DMA_SECCFGR_SEC0 */
#if defined (DMA_PRIVCFGR_PRIV0)
/**
  * @brief Enable the DMA channel privilege attribute.
  * @note  This API is used for all available DMA channels.
  * @rmtoll PRIVCFGR          PRIVx      LL_DMA_EnableChannelPrivilege
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableChannelPrivilege(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(DMAx->PRIVCFGR, (DMA_PRIVCFGR_PRIV0 << (Channel & 0x0000000FU)));
}

/**
  * @brief Disable the DMA channel privilege attribute.
  * @note  This API is used for all available DMA channels.
  * @rmtoll PRIVCFGR          PRIVx      LL_DMA_DisableChannelPrivilege
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableChannelPrivilege(DMA_TypeDef *DMAx, uint32_t Channel)
{
  CLEAR_BIT(DMAx->PRIVCFGR, (DMA_PRIVCFGR_PRIV0 << (Channel & 0x0000000FU)));
}

/**
  * @brief Check if DMA Channel privilege is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll PRIVCFGR          PRIVx      LL_DMA_IsEnabledChannelPrivilege
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannelPrivilege(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  return ((READ_BIT(DMAx->PRIVCFGR, (DMA_PRIVCFGR_PRIV0 << (Channel & 0x0000000FU)))
           == (DMA_PRIVCFGR_PRIV0 << (Channel & 0x0000000FU))) ? 1UL : 0UL);
}
#endif /* DMA_PRIVCFGR_PRIV0 */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief Enable the DMA channel lock attributes.
  * @note  This API is used for all available DMA channels.
  * @rmtoll RCFGLOCKR           LOCKx         LL_DMA_EnableChannelLockAttribute
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableChannelLockAttribute(DMA_TypeDef *DMAx, uint32_t Channel)
{
  SET_BIT(DMAx->RCFGLOCKR, (DMA_RCFGLOCKR_LOCK0 << (Channel & 0x0000000FU)));
}
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#if defined (DMA_RCFGLOCKR_LOCK0)
/**
  * @brief Check if DMA channel attributes are locked.
  * @note  This API is used for all available DMA channels.
  * @rmtoll SECCFGR            LOCKx       LL_DMA_IsEnabledChannelLockAttribute
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannelLockAttribute(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  return ((READ_BIT(DMAx->RCFGLOCKR, (DMA_RCFGLOCKR_LOCK0 << (Channel & 0x0000000FU)))
           == (DMA_RCFGLOCKR_LOCK0 << (Channel & 0x0000000FU))) ? 1UL : 0UL);
}

#endif /* DMA_RCFGLOCKR_LOCK0 */
/**
  * @}
  */

/** @defgroup DMA_LL_EF_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief Clear trigger overrun flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CFCR          TOF        LL_DMA_ClearFlag_TO
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TO(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CFCR, DMA_CFCR_TOF);
}

/**
  * @brief Clear suspension flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CFCR          SUSPF        LL_DMA_ClearFlag_SUSP
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ClearFlag_SUSP(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CFCR, DMA_CFCR_SUSPF);
}

/**
  * @brief Clear user setting error flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CFCR          USEF         LL_DMA_ClearFlag_USE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ClearFlag_USE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CFCR, DMA_CFCR_USEF);
}

/**
  * @brief Clear link transfer error flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CFCR          ULEF         LL_DMA_ClearFlag_ULE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ClearFlag_ULE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CFCR, DMA_CFCR_ULEF);
}

/**
  * @brief Clear data transfer error flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CFCR          DTEF         LL_DMA_ClearFlag_DTE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ClearFlag_DTE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CFCR, DMA_CFCR_DTEF);
}

/**
  * @brief Clear half transfer flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CFCR          HTF          LL_DMA_ClearFlag_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ClearFlag_HT(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CFCR, DMA_CFCR_HTF);
}

/**
  * @brief Clear transfer complete flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CFCR          TCF          LL_DMA_ClearFlag_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TC(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  WRITE_REG(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CFCR, DMA_CFCR_TCF);
}

/**
  * @brief Get trigger overrun flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           TOF        LL_DMA_IsActiveFlag_TO
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TO(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_TOF)
           == (DMA_CSR_TOF)) ? 1UL : 0UL);
}

/**
  * @brief Get suspension flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           SUSPF        LL_DMA_IsActiveFlag_SUSP
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_SUSP(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_SUSPF)
           == (DMA_CSR_SUSPF)) ? 1UL : 0UL);
}

/**
  * @brief Get user setting error flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           USEF         LL_DMA_IsActiveFlag_USE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_USE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_USEF)
           == (DMA_CSR_USEF)) ? 1UL : 0UL);
}

/**
  * @brief Get user setting error flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           ULEF         LL_DMA_IsActiveFlag_ULE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_ULE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_ULEF)
           == (DMA_CSR_ULEF)) ? 1UL : 0UL);
}

/**
  * @brief Get data transfer error flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           DTEF         LL_DMA_IsActiveFlag_DTE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DTE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_DTEF)
           == (DMA_CSR_DTEF)) ? 1UL : 0UL);
}

/**
  * @brief Get half transfer flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           HTF          LL_DMA_IsActiveFlag_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_HTF)
           == (DMA_CSR_HTF)) ? 1UL : 0UL);
}

/**
  * @brief Get transfer complete flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           TCF          LL_DMA_IsActiveFlag_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_TCF)
           == (DMA_CSR_TCF)) ? 1UL : 0UL);
}

/**
  * @brief Get idle flag.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CSR           IDLEF        LL_DMA_IsActiveFlag_IDLE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_IDLE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CSR, DMA_CSR_IDLEF)
           == (DMA_CSR_IDLEF)) ? 1UL : 0UL);
}

/**
  * @brief Check if nsecure masked interrupt is active.
  * @note  This API is used for all available DMA channels.
  * @rmtoll MISR  MISx    LL_DMA_IsActiveFlag_MIS
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_MIS(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  return ((READ_BIT(DMAx->MISR, (DMA_MISR_MIS0 << (Channel & 0x0FU)))
           == (DMA_MISR_MIS0 << (Channel & 0x0FU))) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief Check if secure masked interrupt is active.
  * @note  This API is used for all available DMA channels.
  * @rmtoll SMISR  MISx    LL_DMA_IsActiveFlag_SMIS
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_SMIS(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  return ((READ_BIT(DMAx->SMISR, (DMA_SMISR_MIS0 << (Channel & 0x0000000FU)))
           == (DMA_SMISR_MIS0 << (Channel & 0x0000000FU))) ? 1UL : 0UL);
}
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */

/** @defgroup DMA_LL_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief Enable trigger overrun interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           TOIE       LL_DMA_EnableIT_TO
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableIT_TO(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_TOIE);
}

/**
  * @brief Enable suspension interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           SUSPIE       LL_DMA_EnableIT_SUSP
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableIT_SUSP(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_SUSPIE);
}

/**
  * @brief Enable user setting error interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           USEIE        LL_DMA_EnableIT_USE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableIT_USE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_USEIE);
}

/**
  * @brief Enable update link transfer error interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           ULEIE        LL_DMA_EnableIT_ULE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableIT_ULE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_ULEIE);
}

/**
  * @brief Enable data transfer error interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           DTEIE        LL_DMA_EnableIT_DTE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableIT_DTE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_DTEIE);
}

/**
  * @brief Enable half transfer complete interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           HTIE         LL_DMA_EnableIT_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableIT_HT(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_HTIE);
}

/**
  * @brief Enable transfer complete interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           TCIE         LL_DMA_EnableIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_EnableIT_TC(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  SET_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_TCIE);
}

/**
  * @brief Disable trigger overrun interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           TOIE       LL_DMA_DisableIT_TO
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableIT_TO(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_TOIE);
}

/**
  * @brief Disable suspension interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           SUSPIE       LL_DMA_DisableIT_SUSP
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableIT_SUSP(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_SUSPIE);
}

/**
  * @brief Disable user setting error interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           USEIE        LL_DMA_DisableIT_USE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableIT_USE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_USEIE);
}

/**
  * @brief Disable update link transfer error interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           ULEIE        LL_DMA_DisableIT_ULE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableIT_ULE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_ULEIE);
}

/**
  * @brief Disable data transfer error interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           DTEIE        LL_DMA_DisableIT_DTE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableIT_DTE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_DTEIE);
}

/**
  * @brief Disable half transfer complete interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           HTIE         LL_DMA_DisableIT_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableIT_HT(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_HTIE);
}

/**
  * @brief Disable transfer complete interrupt.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           TCIE         LL_DMA_DisableIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval None.
  */
__STATIC_INLINE void LL_DMA_DisableIT_TC(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  CLEAR_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_TCIE);
}

/**
  * @brief Check if trigger overrun interrupt is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           TOIE       LL_DMA_IsEnabledIT_TO
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TO(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_TOIE)
           == DMA_CCR_TOIE) ? 1UL : 0UL);
}

/**
  * @brief Check if suspension interrupt is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           SUSPIE       LL_DMA_IsEnabledIT_SUSP
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_SUSP(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_SUSPIE)
           == DMA_CCR_SUSPIE) ? 1UL : 0UL);
}

/**
  * @brief Check if user setting error interrupt is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR           USEIE        LL_DMA_IsEnabledIT_USE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_USE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_USEIE)
           == DMA_CCR_USEIE) ? 1UL : 0UL);
}

/**
  * @brief Check if update link transfer error interrupt is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR        ULEIE         LL_DMA_IsEnabledIT_ULE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_ULE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_ULEIE)
           == DMA_CCR_ULEIE) ? 1UL : 0UL);
}

/**
  * @brief Check if data transfer error interrupt is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR        DTEIE         LL_DMA_IsEnabledIT_DTE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_DTE(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_DTEIE)
           == DMA_CCR_DTEIE) ? 1UL : 0UL);
}

/**
  * @brief Check if half transfer complete interrupt is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR        HTIE         LL_DMA_IsEnabledIT_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_HT(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_HTIE)
           == DMA_CCR_HTIE) ? 1UL : 0UL);
}

/**
  * @brief Check if transfer complete interrupt is enabled.
  * @note  This API is used for all available DMA channels.
  * @rmtoll CCR        TCIE         LL_DMA_IsEnabledIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TC(const DMA_TypeDef *DMAx, uint32_t Channel)
{
  uint32_t dma_base_addr = (uint32_t)DMAx;
  return ((READ_BIT(((DMA_Channel_TypeDef *)(dma_base_addr + LL_DMA_CH_OFFSET_TAB[Channel]))->CCR, DMA_CCR_TCIE)
           == DMA_CCR_TCIE) ? 1UL : 0UL);
}
/**
  * @}
  */

#if defined (USE_FULL_LL_DRIVER)
/** @defgroup DMA_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
uint32_t LL_DMA_Init(DMA_TypeDef *DMAx, uint32_t Channel, LL_DMA_InitTypeDef *DMA_InitStruct);
uint32_t LL_DMA_DeInit(DMA_TypeDef *DMAx, uint32_t Channel);

void     LL_DMA_StructInit(LL_DMA_InitTypeDef *DMA_InitStruct);
void     LL_DMA_ListStructInit(LL_DMA_InitLinkedListTypeDef *DMA_InitLinkedListStruct);
void     LL_DMA_NodeStructInit(LL_DMA_InitNodeTypeDef *DMA_InitNodeStruct);

uint32_t LL_DMA_List_Init(DMA_TypeDef *DMAx, uint32_t Channel,
                          LL_DMA_InitLinkedListTypeDef *DMA_InitLinkedListStruct);
uint32_t LL_DMA_List_DeInit(DMA_TypeDef *DMAx, uint32_t Channel);

uint32_t LL_DMA_CreateLinkNode(LL_DMA_InitNodeTypeDef *DMA_InitNodeStruct, LL_DMA_LinkNodeTypeDef *pNode);
void     LL_DMA_ConnectLinkNode(LL_DMA_LinkNodeTypeDef *pPrevLinkNode, uint32_t PrevNodeCLLRIdx,
                                LL_DMA_LinkNodeTypeDef *pNewLinkNode, uint32_t NewNodeCLLRIdx);
void     LL_DMA_DisconnectNextLinkNode(LL_DMA_LinkNodeTypeDef *pLinkNode, uint32_t LinkNodeCLLRIdx);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* GPDMA1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32WBAxx_LL_DMA_H */
