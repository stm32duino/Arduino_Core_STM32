/**
  ******************************************************************************
  * @file    usbd_cdc_if.c
  * @author  MCD Application Team
  * @brief   Generic media access Layer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifdef USBCON
#ifdef USBD_USE_CDC

/* Includes ------------------------------------------------------------------*/
#include "usbd_desc.h"
#include "usbd_cdc_if.h"
#include "bootloader.h"

#ifdef USE_USB_HS
  #define CDC_MAX_PACKET_SIZE USB_OTG_HS_MAX_PACKET_SIZE
#elif defined(USB_OTG_FS) || defined(USB_OTG_FS_MAX_PACKET_SIZE)
  #define CDC_MAX_PACKET_SIZE USB_OTG_FS_MAX_PACKET_SIZE
#else /* USB */
  #define CDC_MAX_PACKET_SIZE USB_MAX_EP0_SIZE
#endif

/*
 * The value USB_CDC_TRANSMIT_TIMEOUT is defined in terms of HAL_GetTick() units.
 * Typically it is 1ms value. The timeout determines when we would consider the
 * host "too slow" and threat the USB CDC port as disconnected.
 */
#ifndef USB_CDC_TRANSMIT_TIMEOUT
  #define USB_CDC_TRANSMIT_TIMEOUT 3
#endif

/* USBD_CDC Private Variables */
/* USB Device Core CDC handle declaration */
USBD_HandleTypeDef hUSBD_Device_CDC;

static bool CDC_initialized = false;

/* Received Data over USB are stored in this buffer       */
CDC_TransmitQueue_TypeDef TransmitQueue;
CDC_ReceiveQueue_TypeDef ReceiveQueue;
__IO uint32_t lineState = 0;
__IO bool receivePended = true;
static uint32_t transmitStart = 0;

#ifdef DTR_TOGGLING_SEQ
  /* DTR toggling sequence management */
  extern void dtr_togglingHook(uint8_t *buf, uint32_t *len);
  uint8_t dtr_toggling = 0;
#endif

/** USBD_CDC Private Function Prototypes */

static int8_t USBD_CDC_Init(void);
static int8_t USBD_CDC_DeInit(void);
static int8_t USBD_CDC_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t USBD_CDC_Receive(uint8_t *pbuf, uint32_t *Len);
static int8_t USBD_CDC_Transferred(void);

USBD_CDC_ItfTypeDef USBD_CDC_fops = {
  USBD_CDC_Init,
  USBD_CDC_DeInit,
  USBD_CDC_Control,
  USBD_CDC_Receive,
  USBD_CDC_Transferred
};

USBD_CDC_LineCodingTypeDef linecoding = {
  115200, /* baud rate*/
  0x00,   /* stop bits-1*/
  0x00,   /* parity - none*/
  0x08    /* nb. of bits 8*/
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  USBD_CDC_Init
  *         Initializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t USBD_CDC_Init(void)
{
  /* Set Application Buffers */
  CDC_TransmitQueue_Init(&TransmitQueue);
  CDC_ReceiveQueue_Init(&ReceiveQueue);
  receivePended = true;
  USBD_CDC_SetRxBuffer(&hUSBD_Device_CDC, CDC_ReceiveQueue_ReserveBlock(&ReceiveQueue));

  return (USBD_OK);
}

/**
  * @brief  USBD_CDC_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t USBD_CDC_DeInit(void)
{
  return (USBD_OK);
}


/**
  * @brief  USBD_CDC_Control
  *         Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t USBD_CDC_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
  UNUSED(length);
  switch (cmd) {
    case CDC_SEND_ENCAPSULATED_COMMAND:

      break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

      break;

    case CDC_SET_COMM_FEATURE:

      break;

    case CDC_GET_COMM_FEATURE:

      break;

    case CDC_CLEAR_COMM_FEATURE:

      break;

    /*******************************************************************************/
    /* Line Coding Structure                                                       */
    /*-----------------------------------------------------------------------------*/
    /* Offset | Field       | Size | Value  | Description                          */
    /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
    /* 4      | bCharFormat |   1  | Number | Stop bits                            */
    /*                                        0 - 1 Stop bit                       */
    /*                                        1 - 1.5 Stop bits                    */
    /*                                        2 - 2 Stop bits                      */
    /* 5      | bParityType |  1   | Number | Parity                               */
    /*                                        0 - None                             */
    /*                                        1 - Odd                              */
    /*                                        2 - Even                             */
    /*                                        3 - Mark                             */
    /*                                        4 - Space                            */
    /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
    /*******************************************************************************/
    case CDC_SET_LINE_CODING:
      linecoding.bitrate    = (uint32_t)(pbuf[0] | (pbuf[1] << 8) | \
                                         (pbuf[2] << 16) | (pbuf[3] << 24));
      linecoding.format     = pbuf[4];
      linecoding.paritytype = pbuf[5];
      linecoding.datatype   = pbuf[6];
      break;

    case CDC_GET_LINE_CODING:
      pbuf[0] = (uint8_t)(linecoding.bitrate);
      pbuf[1] = (uint8_t)(linecoding.bitrate >> 8);
      pbuf[2] = (uint8_t)(linecoding.bitrate >> 16);
      pbuf[3] = (uint8_t)(linecoding.bitrate >> 24);
      pbuf[4] = linecoding.format;
      pbuf[5] = linecoding.paritytype;
      pbuf[6] = linecoding.datatype;
      break;

    case CDC_SET_CONTROL_LINE_STATE:
      lineState =
        (((USBD_SetupReqTypedef *)pbuf)->wValue & 0x01) != 0; // Check DTR state
      if (lineState) { // Reset the transmit timeout when the port is connected
        transmitStart = 0;
      }
#ifdef DTR_TOGGLING_SEQ
      dtr_toggling++; /* Count DTR toggling */
#endif
      break;

    case CDC_SEND_BREAK:

      break;

    default:
      break;
  }

  return (USBD_OK);
}

/**
  * @brief  USBD_CDC_Receive
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint untill exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t USBD_CDC_Receive(uint8_t *Buf, uint32_t *Len)
{
#ifdef DTR_TOGGLING_SEQ
  if (dtr_toggling > 3) {
    dtr_togglingHook(Buf, Len);
    dtr_toggling = 0;
  }
#else
  UNUSED(Buf);
#endif
  /* It always contains required amount of free space for writing */
  CDC_ReceiveQueue_CommitBlock(&ReceiveQueue, (uint16_t)(*Len));
  receivePended = false;
  /* If enough space in the queue for a full buffer then continue receive */
  if (!CDC_resume_receive()) {
    USBD_CDC_ClearBuffer(&hUSBD_Device_CDC);
  }
  return USBD_OK;
}


static int8_t USBD_CDC_Transferred(void)
{
  transmitStart = 0;
  CDC_TransmitQueue_CommitRead(&TransmitQueue);
  CDC_continue_transmit();
  return (USBD_OK);
}

void CDC_init(void)
{
  if (!CDC_initialized) {
    /* Init Device Library */
    if (USBD_Init(&hUSBD_Device_CDC, &USBD_Desc, 0) == USBD_OK) {
      /* Add Supported Class */
      if (USBD_RegisterClass(&hUSBD_Device_CDC, USBD_CDC_CLASS) == USBD_OK) {
        /* Add CDC Interface Class */
        if (USBD_CDC_RegisterInterface(&hUSBD_Device_CDC, &USBD_CDC_fops) == USBD_OK) {
          /* Start Device Process */
          USBD_Start(&hUSBD_Device_CDC);
          CDC_initialized = true;
        }
      }
    }
  }
}

void CDC_deInit(void)
{
  if (CDC_initialized) {
    USBD_Stop(&hUSBD_Device_CDC);
    USBD_CDC_DeInit();
    USBD_DeInit(&hUSBD_Device_CDC);
    CDC_initialized = false;
  }
}

bool CDC_connected()
{
  /* Save the transmitStart value in a local variable to avoid twice reading - fix #478 */
  uint32_t transmitTime = transmitStart;
  if (transmitTime) {
    transmitTime = HAL_GetTick() - transmitTime;
  }
  return hUSBD_Device_CDC.dev_state == USBD_STATE_CONFIGURED
         && transmitTime < USB_CDC_TRANSMIT_TIMEOUT
         && lineState;
}

void CDC_continue_transmit(void)
{
  uint16_t size;
  uint8_t *buffer;
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) hUSBD_Device_CDC.pClassData;
  /*
   * TS: This method can be called both in the main thread
   * (via USBSerial::write) and in the IRQ stream (via USBD_CDC_Transferred),
   * BUT the main thread cannot pass this condition while waiting for a IRQ!
   * This is not possible because TxState is not zero while waiting for data
   * transfer ending! The IRQ thread is uninterrupted, since its priority
   * is higher than that of the main thread. So this method is thread safe.
   */
  if (hcdc->TxState == 0U) {
    buffer = CDC_TransmitQueue_ReadBlock(&TransmitQueue, &size);
    if (size > 0) {
      transmitStart = HAL_GetTick();
      USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, buffer, size);
      /*
       * size never exceed PMA buffer and USBD_CDC_TransmitPacket make full
       * copy of block in PMA, so no need to worry about buffer damage
       */
      USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
    }
  }
}

bool CDC_resume_receive(void)
{
  /*
   * TS: main and IRQ threads can't pass it at same time, because
   * IRQ may occur only if receivePended is true. So it is thread-safe!
   */
  if (!receivePended) {
    uint8_t *block = CDC_ReceiveQueue_ReserveBlock(&ReceiveQueue);
    if (block != NULL) {
      receivePended = true;
      /* Set new buffer */
      USBD_CDC_SetRxBuffer(&hUSBD_Device_CDC, block);
      USBD_CDC_ReceivePacket(&hUSBD_Device_CDC);
      return true;
    }
  }
  return false;
}

#endif /* USBD_USE_CDC */
#endif /* USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

