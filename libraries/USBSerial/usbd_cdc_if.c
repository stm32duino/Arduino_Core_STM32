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
__IO uint8_t StackRxBufferFS[APP_RX_DATA_SIZE];

/* Send Data over USB CDC are stored in this buffer       */
__IO uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];
__IO uint8_t StackTxBufferFS[APP_TX_DATA_SIZE];

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
uint8_t USBBuffer[64];
uint8_t USBPackSize;

/* Default configuration: 115200, 8N1 */
uint8_t lineSetup[] = {0x00, 0xc2, 0x01, 0x00, 0x00, 0x00, 0x08};

#define CDC_POLLING_INTERVAL             2 /* in ms. The max is 65 and the min is 1 */

stimer_t TimHandle;

static void TIM_Config(void);

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

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
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
  /*##-3- Configure and start the TIM Base generation  #################################*/
  TIM_Config();

  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t *)UserTxBufferFS, 1);
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
static int8_t CDC_Control_FS  (uint8_t cmd, uint8_t* pbuf, uint16_t length)
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
    memcpy(lineSetup, pbuf, 7);
    break;

  case CDC_GET_LINE_CODING:
    memcpy(pbuf, lineSetup, 7);
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

static int8_t CDC_Receive_FS (uint8_t* Buf, uint32_t *Len)
{
  /* Initiate next USB packet transfer once a packet is received */
  USBPackSize = *Len;
  memcpy(USBBuffer, Buf, USBPackSize);

  USB_received = 1;
  return (USBD_OK);
}

/**
  * @brief  CDC_Transmit_FS
  *         Data send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be send
  * @param  Len: Number of data to be send (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  UNUSED(Buf);
  uint8_t result = USBD_OK;
  UNUSED(Len);
  USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t *)UserTxBufferFS, 1);
  result = USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
  return result;
}

void CDC_flush(void)
{
  uint8_t status;

  if(UserTxBufPtrOut != UserTxBufPtrIn)
  {
    if(UserTxBufPtrOut > UserTxBufPtrIn) /* Roll-back */
    {
      memcpy((uint8_t*)&StackTxBufferFS[0], (uint8_t*)&UserTxBufferFS[UserTxBufPtrOut], (APP_TX_DATA_SIZE - UserTxBufPtrOut));

      memcpy((uint8_t*)&StackTxBufferFS[APP_TX_DATA_SIZE - UserTxBufPtrOut], (uint8_t*)&UserTxBufferFS[0], UserTxBufPtrIn);

      USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&StackTxBufferFS[0], (APP_TX_DATA_SIZE - UserTxBufPtrOut + UserTxBufPtrIn));

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
      USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&UserTxBufferFS[UserTxBufPtrOut], (UserTxBufPtrIn - UserTxBufPtrOut));

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
  HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
}

void CDC_enable_TIM_Interrupt(void)
{
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

static void TIM_Config(void)
{
  /* Set TIMx instance */
  TimHandle.timer = TIM6;
  /* Initialize TIM6 peripheral as follow:
       + Period = 10000 - 1
       + Prescaler = ((SystemCoreClock/2)/10000) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
  TimerHandleInit(&TimHandle, (uint16_t)((CDC_POLLING_INTERVAL*1000) - 1), ((uint32_t)(getTimerClkFreq(TIM6) / (1000000)) - 1)); //CDC_POLLING_INTERVAL

  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 6, 0);

  timer_attach_interrupt_handle(&TimHandle.handle, TIM6_PeriodElapsedCallback);
}

void TIM6_PeriodElapsedCallback(stimer_t *htim)
{
  UNUSED(htim);
  uint8_t status;

  if(USB_received) {
    USB_received = 0;

    if((USBPackSize > 0)) {
      if(UserRxBufPtrIn + USBPackSize > APP_RX_DATA_SIZE) {
        memcpy(((uint8_t *)UserRxBufferFS+UserRxBufPtrIn), &USBBuffer[0], (APP_RX_DATA_SIZE - UserRxBufPtrIn));
        memcpy((uint8_t *)UserRxBufferFS, &USBBuffer[(APP_RX_DATA_SIZE - UserRxBufPtrIn)], (USBPackSize - (APP_RX_DATA_SIZE - UserRxBufPtrIn)));
        UserRxBufPtrIn = ((UserRxBufPtrIn + USBPackSize) % APP_RX_DATA_SIZE);
      } else {
        memcpy(((uint8_t *)UserRxBufferFS+UserRxBufPtrIn), USBBuffer, USBPackSize);
        UserRxBufPtrIn = ((UserRxBufPtrIn + USBPackSize) % APP_RX_DATA_SIZE);
      }
    }

    USBD_CDC_ReceivePacket(&hUSBD_Device_CDC);
  }

  if(UserTxBufPtrOut != UserTxBufPtrIn) {
    if(UserTxBufPtrOut > UserTxBufPtrIn) { /* Roll-back */
      memcpy((uint8_t*)&StackTxBufferFS[0], (uint8_t*)&UserTxBufferFS[UserTxBufPtrOut], (APP_TX_DATA_SIZE - UserTxBufPtrOut));

      memcpy((uint8_t*)&StackTxBufferFS[APP_TX_DATA_SIZE - UserTxBufPtrOut], (uint8_t*)&UserTxBufferFS[0], UserTxBufPtrIn);

      USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&StackTxBufferFS[0], (APP_TX_DATA_SIZE - UserTxBufPtrOut + UserTxBufPtrIn));

      do {
	    status = USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
      } while(status == USBD_BUSY);

      if(status == USBD_OK) {
        UserTxBufPtrOut = UserTxBufPtrIn;
      }
    }
    else {
      USBD_CDC_SetTxBuffer(&hUSBD_Device_CDC, (uint8_t*)&UserTxBufferFS[UserTxBufPtrOut], (UserTxBufPtrIn - UserTxBufPtrOut));

      do {
        status = USBD_CDC_TransmitPacket(&hUSBD_Device_CDC);
      } while(status == USBD_BUSY);

      if(status == USBD_OK) {
        UserTxBufPtrOut = UserTxBufPtrIn;
      }
    }
  }
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

#endif // USBCON
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
