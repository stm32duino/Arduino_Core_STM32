/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @brief          :
  ******************************************************************************
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  * 1. Redistributions of source code must retain the above copyright notice,
  * this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of its contributors
  * may be used to endorse or promote products derived from this software
  * without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/

#ifdef USBCON

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"
#include "stm32_def.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_CDC
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_CDC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup USBD_CDC_Private_Defines
  * @{
  */
/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */
/**
  * @}
  */

/** @defgroup USBD_CDC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CDC_Private_Variables
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
extern USBD_HandleTypeDef hUSBD_Device_CDC;

/* Received Data over USB are stored in this buffer       */
__IO uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
__IO uint16_t StackRxBufferFS[(APP_RX_DATA_SIZE + 1) / 2];

/* Send Data over USB CDC are stored in this buffer       */
__IO uint16_t UserTxBufferFS[(APP_TX_DATA_SIZE + 1) / 2];
__IO uint16_t StackTxBufferFS[(APP_TX_DATA_SIZE + 1) / 2];

__IO uint8_t *gCDC_pTxBufferFS;
__IO uint32_t UserTxBufPtrIn = 0; /* Increment this pointer or roll it back to
                               start address when data are received over write call */

__IO uint32_t UserRxBufPtrIn = 0; /* Increment this pointer or roll it back to
                               start address when data are received over USB */
__IO uint32_t UserRxBufPtrOut = 0; /* Increment this pointer or roll it back to
                                 start address when data are sent over read call */

__IO uint32_t gCDC_LineState = 0;

/* Default configuration: 115200, 8N1 */
USBD_CDC_LineCodingTypeDef gCDC_LineSetup = { 115200, 0x00, 0x00, 0x08 };

/* USB handler declaration */
/* Handle for USB Full Speed IP */
//  USBD_HandleTypeDef  *hUsbDevice_0;

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CDC_Private_FunctionPrototypes
  * @{
  */
static int8_t CDC_Init_FS     (void);
static int8_t CDC_DeInit_FS   (void);
static int8_t CDC_Control_FS  (uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS  (uint8_t* pbuf, uint32_t *Len);
static int8_t CDC_TransmitDone(void);

static void CDC_StartReceive(void);

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS,
  CDC_TransmitDone
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  CDC_Init_FS
  *         Initializes the CDC media low layer over the FS USB IP
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t *)StackTxBufferFS, 1);
  USBD_CDC_SetRxBuffer(&hUSBD_Device_CDC, (uint8_t *)StackRxBufferFS);

  return (USBD_OK);
}

/**
  * @brief  CDC_DeInit_FS
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  UserTxBufPtrIn = 0;
  UserRxBufPtrIn = 0;
  UserRxBufPtrOut = 0;
  gCDC_LineState = 0;
  return (USBD_OK);
}

/**
  * @brief  CDC_Control_FS
  *         Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
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
    memcpy(&gCDC_LineSetup, pbuf, 7);
    USBD_UsrLog("BaudRate=%u", gCDC_LineSetup.bitrate);
    break;

  case CDC_GET_LINE_CODING:
    memcpy(pbuf, &gCDC_LineSetup, 7);
    break;

  case CDC_SET_CONTROL_LINE_STATE:
    {
    USBD_SetupReqTypedef *req = (void *) pbuf;
    gCDC_LineState = req->wValue;
    USBD_UsrLog("LINE_STATE=%x", gCDC_LineState);
    }
    break;

  case CDC_SEND_BREAK:

    break;

  default:
    break;
  }

  return (USBD_OK);
}

/**
  * @brief  CDC_Receive_FS
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will block any OUT packet reception on USB endpoint
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result
  *         in receiving more data while previous ones are still not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */

static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  uint32_t Size = *Len;

  if (Size > 0)
  {
    if ((UserRxBufPtrIn + Size) > APP_RX_DATA_SIZE)
    {
      uint32_t n = APP_RX_DATA_SIZE - UserRxBufPtrIn;
      memcpy(&UserRxBufferFS[UserRxBufPtrIn], Buf, n);
      if ((Size -= n) != 0)
        memcpy(UserRxBufferFS, &Buf[n], Size);
      UserRxBufPtrIn = Size;
    }
    else
    {
      memcpy(&UserRxBufferFS[UserRxBufPtrIn], Buf, Size);
      UserRxBufPtrIn += Size;
    }
  }

  CDC_StartReceive();

  return (USBD_OK);
}

/**
  * @brief  CDC_TransmitDone
  *         Transmit done callback
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_TransmitDone(void)
{
  if (UserTxBufPtrIn)
  {
    USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, gCDC_pTxBufferFS, UserTxBufPtrIn);

    if (gCDC_pTxBufferFS == (uint8_t *)UserTxBufferFS)
      gCDC_pTxBufferFS = (uint8_t *)StackTxBufferFS;
    else
      gCDC_pTxBufferFS = (uint8_t *)UserTxBufferFS;
    UserTxBufPtrIn = 0;

    USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
  }

  return (USBD_OK);
}

/* Public functions ---------------------------------------------------------*/
int CDC_AvailableForRead(void)
{
  int Bytes;

  if (UserRxBufPtrIn < UserRxBufPtrOut)
  {
    Bytes = (int)(APP_RX_DATA_SIZE - UserRxBufPtrOut + UserRxBufPtrIn);
  }
  else
  {
    Bytes = (int)(UserRxBufPtrIn - UserRxBufPtrOut);
  }
  return Bytes;
}

int CDC_AvailableForWrite(void)
{
  return APP_TX_DATA_SIZE - UserTxBufPtrIn;
}

void CDC_Flush(void)
{
  uint32_t ConnectionState;

  while ((ConnectionState = USBD_LL_ConnectionState()) != 0)
  {
    if (UserTxBufPtrIn == 0)
    {
      USBD_UsrLog("-Flush");
      return;
    }
    USBD_LL_Delay(5);
  }

  USBD_UsrLog("?Flush");
  UserTxBufPtrIn = 0;
}

int CDC_Peek(void)
{
  int c;

  USBD_LL_DisableIRQ();

  if (UserRxBufPtrOut == UserRxBufPtrIn)
  {
    c = -1;
  }
  else
  {
    c = UserRxBufferFS[UserRxBufPtrOut];
  }

  USBD_LL_EnableIRQ();
  return c;
}

int CDC_Read(void)
{
  USBD_CDC_HandleTypeDef *hcdc = hUSBD_Device_CDC.pClassData;
  int c;

  USBD_LL_DisableIRQ();

  if (UserRxBufPtrOut == UserRxBufPtrIn)
  {
    c = -1;
  }
  else
  {
    c = UserRxBufferFS[UserRxBufPtrOut];
    if (++UserRxBufPtrOut == APP_RX_DATA_SIZE)
      UserRxBufPtrOut = 0;
  }

  if (hcdc->RxState == 0)
    CDC_StartReceive();

  USBD_LL_EnableIRQ();
  return c;
}

static void CDC_StartReceive(void)
{
  uint32_t Size;

  // Get available size for read
  if (UserRxBufPtrIn >= UserRxBufPtrOut)
  {
    Size = (APP_RX_DATA_SIZE - 1 - UserRxBufPtrIn + UserRxBufPtrOut);
  } else
  {
    Size = (UserRxBufPtrOut - UserRxBufPtrIn - 1);
  }

  if (hUSBD_Device_CDC.dev_speed == USBD_SPEED_HIGH)
  {
    if (Size >= CDC_DATA_HS_OUT_PACKET_SIZE)
      USBD_CDC_ReceivePacket(&hUSBD_Device_CDC);
  }
  else
  {
    if (Size >= CDC_DATA_FS_OUT_PACKET_SIZE)
      USBD_CDC_ReceivePacket(&hUSBD_Device_CDC);
  }
}

size_t CDC_Write(const uint8_t *pBuffer, size_t nBuffer)
{
  USBD_CDC_HandleTypeDef   *hcdc = hUSBD_Device_CDC.pClassData;
  size_t nBytes;

  USBD_LL_DisableIRQ();

  if (hcdc->TxState == 0)
  {
    if (nBuffer > APP_TX_DATA_SIZE)
      nBytes = APP_TX_DATA_SIZE;
    else
      nBytes = nBuffer;

    memcpy(StackTxBufferFS, pBuffer, nBytes);
    gCDC_pTxBufferFS = (uint8_t *)UserTxBufferFS;
    UserTxBufPtrIn = 0;

    USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t *)StackTxBufferFS, nBytes);

    USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
  }
  else
  {
    nBytes = APP_TX_DATA_SIZE - UserTxBufPtrIn;
    if (nBytes > nBuffer)
      nBytes = nBuffer;

    memcpy(gCDC_pTxBufferFS + UserTxBufPtrIn, pBuffer, nBytes);
    UserTxBufPtrIn += nBytes;
  }

  USBD_LL_EnableIRQ();
  return nBytes;
}

uint16_t CDC_LineState(void)
{
  return gCDC_LineState;
}

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* USBCON */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
