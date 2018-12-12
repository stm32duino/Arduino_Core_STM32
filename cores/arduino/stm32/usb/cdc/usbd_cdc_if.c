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
#include "usbd_cdc_if.h"

/* USBD_CDC Private Variables */

/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
extern USBD_HandleTypeDef hUSBD_Device_CDC;
/* Received Data over USB are stored in this buffer       */
__IO uint8_t UserRxBuffer[APP_RX_DATA_SIZE];
__IO uint8_t StackRxBuffer[APP_RX_DATA_SIZE];

/* Send Data over USB CDC are stored in this buffer       */
__IO uint8_t UserTxBuffer[APP_TX_DATA_SIZE];
__IO uint8_t StackTxBuffer[APP_TX_DATA_SIZE];

__IO uint32_t UserTxBufPtrIn = 0; /* Increment this pointer or roll it back to
                               start address when data are received over write call */
__IO uint32_t UserTxBufPtrOut = 0; /* Increment this pointer or roll it back to
                                 start address when data are sent over USB */

__IO uint32_t UserRxBufPtrIn = 0; /* Increment this pointer or roll it back to
                               start address when data are received over USB */
__IO uint32_t UserRxBufPtrOut = 0; /* Increment this pointer or roll it back to
                                 start address when data are sent over read call */

__IO uint32_t SLP;
__IO uint32_t GetRxCount;
__IO uint32_t lineState = 0;
uint8_t cptlineState = 0;
volatile uint32_t USB_received = 0;
uint8_t USBBuffer[USB_MAX_EP0_SIZE];
uint8_t USBPackSize;
bool sendZLP = false;

stimer_t CDC_TimHandle;

/** USBD_CDC Private Function Prototypes */

static int8_t USBD_CDC_Init     (void);
static int8_t USBD_CDC_DeInit   (void);
static int8_t USBD_CDC_Control  (uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t USBD_CDC_Receive  (uint8_t* pbuf, uint32_t *Len);
static void CDC_TIM_Config(void);
void CDC_TIM_PeriodElapsedCallback(stimer_t *htim);

USBD_CDC_ItfTypeDef USBD_CDC_fops =
{
  USBD_CDC_Init,
  USBD_CDC_DeInit,
  USBD_CDC_Control,
  USBD_CDC_Receive
};

USBD_CDC_LineCodingTypeDef linecoding =
  {
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
  /* Configure and start the TIM Base generation */
  CDC_TIM_Config();

  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t *)UserTxBuffer, 1);
  USBD_CDC_SetRxBuffer(&hUSBD_Device_CDC, (uint8_t *)StackRxBuffer);

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
static int8_t USBD_CDC_Control  (uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
  UNUSED(length);
  switch (cmd)
  {
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
    linecoding.bitrate    = (uint32_t)(pbuf[0] | (pbuf[1] << 8) |\
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
    cptlineState++;
    if(cptlineState == 2)
    lineState = 1;
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
static int8_t USBD_CDC_Receive (uint8_t* Buf, uint32_t *Len)
{
  /* Initiate next USB packet transfer once a packet is received */
  USBPackSize = *Len;
  memcpy(USBBuffer, Buf, USBPackSize);

  USB_received = 1;
  return (USBD_OK);
}

void CDC_flush(void)
{
  uint8_t status;

  if(UserTxBufPtrOut != UserTxBufPtrIn)
  {
    if(UserTxBufPtrOut > UserTxBufPtrIn) /* Roll-back */
    {
      memcpy((uint8_t*)&StackTxBuffer[0], (uint8_t*)&UserTxBuffer[UserTxBufPtrOut], (APP_TX_DATA_SIZE - UserTxBufPtrOut));

      memcpy((uint8_t*)&StackTxBuffer[APP_TX_DATA_SIZE - UserTxBufPtrOut], (uint8_t*)&UserTxBuffer[0], UserTxBufPtrIn);

      USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&StackTxBuffer[0], (APP_TX_DATA_SIZE - UserTxBufPtrOut + UserTxBufPtrIn));

      do {
        status = USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
      } while(status == USBD_BUSY);

      if(status == USBD_OK)
      {
        UserTxBufPtrOut = UserTxBufPtrIn;
      }
    }
    else
    {
      USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&UserTxBuffer[UserTxBufPtrOut], (UserTxBufPtrIn - UserTxBufPtrOut));

	  do {
        status = USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
      } while(status == USBD_BUSY);

      if(status == USBD_OK)
      {
        UserTxBufPtrOut = UserTxBufPtrIn;
      }
    }
  }
}

void CDC_disable_TIM_Interrupt(void)
{
  HAL_NVIC_DisableIRQ(CDC_TIM_IRQn);
}

void CDC_enable_TIM_Interrupt(void)
{
  HAL_NVIC_EnableIRQ(CDC_TIM_IRQn);
}

static void CDC_TIM_Config(void)
{
  /* Set TIMx instance */
  CDC_TimHandle.timer = CDC_TIM;
  /* Initialize CDC_TIM peripheral as follow:
       + Period = 10000 - 1
       + Prescaler = ((SystemCoreClock/2)/10000) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
  TimerHandleInit(&CDC_TimHandle, (uint16_t)((CDC_POLLING_INTERVAL*1000) - 1), ((uint32_t)(getTimerClkFreq(CDC_TIM) / (1000000)) - 1));
  HAL_NVIC_SetPriority(CDC_TIM_IRQn, 6, 0);

  attachIntHandle(&CDC_TimHandle, CDC_TIM_PeriodElapsedCallback);
}

void CDC_TIM_PeriodElapsedCallback(stimer_t *htim)
{
  UNUSED(htim);
  uint8_t status;
  uint16_t transferSize;

  if(USB_received) {
    USB_received = 0;

    if((USBPackSize > 0)) {
      if(UserRxBufPtrIn + USBPackSize > APP_RX_DATA_SIZE) {
        memcpy(((uint8_t *)UserRxBuffer+UserRxBufPtrIn), &USBBuffer[0], (APP_RX_DATA_SIZE - UserRxBufPtrIn));
        memcpy((uint8_t *)UserRxBuffer, &USBBuffer[(APP_RX_DATA_SIZE - UserRxBufPtrIn)], (USBPackSize - (APP_RX_DATA_SIZE - UserRxBufPtrIn)));
        UserRxBufPtrIn = ((UserRxBufPtrIn + USBPackSize) % APP_RX_DATA_SIZE);
      } else {
        memcpy(((uint8_t *)UserRxBuffer+UserRxBufPtrIn), USBBuffer, USBPackSize);
        UserRxBufPtrIn = ((UserRxBufPtrIn + USBPackSize) % APP_RX_DATA_SIZE);
      }
    }

    USBD_CDC_ReceivePacket(&hUSBD_Device_CDC);
  }

  if(UserTxBufPtrOut > UserTxBufPtrIn) { /* Roll-back */
    memcpy((uint8_t*)&StackTxBuffer[0], (uint8_t*)&UserTxBuffer[UserTxBufPtrOut], (APP_TX_DATA_SIZE - UserTxBufPtrOut));
    memcpy((uint8_t*)&StackTxBuffer[APP_TX_DATA_SIZE - UserTxBufPtrOut], (uint8_t*)&UserTxBuffer[0], UserTxBufPtrIn);

    transferSize = (APP_TX_DATA_SIZE - UserTxBufPtrOut + UserTxBufPtrIn);

    USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&StackTxBuffer[0], transferSize);
  }
  else if (UserTxBufPtrOut != UserTxBufPtrIn) {
    transferSize = (UserTxBufPtrIn - UserTxBufPtrOut);

    USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&UserTxBuffer[UserTxBufPtrOut], transferSize);
  }
  else if (sendZLP) {
    transferSize = 0;

    USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, NULL, 0);
  } else {
    return;
  }

  do {
      if (lineState == 0) // Device disconnected
        status = USBD_OK;
      else
        status = USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
  } while(status == USBD_BUSY);

  if(status == USBD_OK) {
    UserTxBufPtrOut = UserTxBufPtrIn;

    sendZLP = transferSize%USB_MAX_EP0_SIZE == 0;
  }
}


#endif /* USBD_USE_CDC */
#endif /* USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

