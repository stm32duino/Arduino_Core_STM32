/**
  ******************************************************************************
  * @file    usbd_printer_if_template.c
  * @author  MCD Application Team
  * @brief   Generic media access Layer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_printer_if_template.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_PRNT
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_PRNT_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_PRNT_Private_Defines
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_PRNT_Private_Macros
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_PRNT_Private_FunctionPrototypes
  * @{
  */

static int8_t TEMPLATE_Init(void);
static int8_t TEMPLATE_DeInit(void);
static int8_t TEMPLATE_Control_req(uint8_t req, uint8_t *pbuf, uint16_t *length);
static int8_t TEMPLATE_Receive(uint8_t *pbuf, uint32_t *Len);

/*printer Private function prototypes*/
void TEMPLATE_PRNT_PageEndManager(uint8_t *Buf, uint32_t Len);

USBD_PRNT_ItfTypeDef USBD_PRNT_Template_fops =
{
  TEMPLATE_Init,
  TEMPLATE_DeInit,
  TEMPLATE_Control_req
  TEMPLATE_Receive
};

static uint8_t PRNT_DEVICE_ID[DEVICE_ID_LEN] =
{
  0x00, 0x6D,
  'M', 'A', 'N', 'U', 'F', 'A', 'C', 'T', 'U', 'R', 'E', 'R', ':',
  'S', 'T', 'M', 'i', 'c', 'r', 'o', 'e', 'l', 'e', 'c', 't', 'r', 'o', 'n', 'i', 'c', 's', ';',
  'C', 'O', 'M', 'M', 'A', 'N', 'D', ' ', 'S', 'E', 'T', ':',
  'P', 'D', 'L', ',',  'P', 'C', 'P', ';',
  'M', 'O', 'D', 'E', 'L', ':',
  'U', 'S', 'B', 'P', 'r', 'i', 'n', 't', 'e', 'r', ';',
  'C', 'O', 'M', 'M', 'E', 'N', 'T', ':',
  'G', 'o', 'o', 'd', ' ', '!', ';',
  'A', 'C', 'T', 'I', 'V', 'E', ' ', 'C', 'O', 'M', 'M', 'A', 'N', 'D', ' ', 'S', 'E', 'T', ':',
  'P', 'C', 'P', ';'
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  TEMPLATE_Init
  *         Initializes the PRNT media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t TEMPLATE_Init(void)
{
  /*
     Add your initialization code here
  */
  return (0);
}

/**
  * @brief  TEMPLATE_DeInit
  *         DeInitializes the PRNT media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t TEMPLATE_DeInit(void)
{
  /*
     Add your deinitialization code here
  */
  return (0);
}


/**
  * @brief  TEMPLATE_Receive
  *         Data received over USB OUT endpoint are sent over PRNT interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint untill exiting this function. If you exit this function
  *         before transfer is complete on PRNT interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t TEMPLATE_Receive(uint8_t *Buf, uint32_t *Len)
{
  UNUSED(Buf);
  UNUSED(Len);

  return (0);
}


/**
  * @brief  TEMPLATE_PRNT_Itf_Control_req
  *         Manage the  PRNT class requests
  * @param  req: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t TEMPLATE_PRNT_Itf_Control_req(uint8_t req, uint8_t *pbuf, uint16_t *length)
{
  uint32_t i = 0;

  /* Check on the setup request value */
  switch (req)
  {
    /* Get Printer Device ID request */
    case PRNT_GET_DEVICE_ID:
      /* Not using for loop here due to MISRA-C2012-Rule-16.1 */
      while (i < sizeof(PRNT_DEVICE_ID))
      {
        pbuf[i] = PRNT_DEVICE_ID[i];
        i++;
      }
      *length = i;
      break;

    /* Get Printer current status */
    case PRNT_GET_PORT_STATUS:
      pbuf[0] =  PRNT_STATUS_PAPER_EMPTY |
                 PRNT_STATUS_SELECTED |
                 PRNT_STATUS_NO_ERROR;

      *length = 1U;
      break;

    /* Printer SOFT RESET request: cleanup pending tasks */
    case PRNT_SOFT_RESET:
      (void)f_close(&hSD.MyFile);
      break;

    default:
      /* Unkown commands are not managed */
      break;
}

/**
* @brief TEMPLATE_PRNT_PageEndManager, defined by user
* Call this function frequently to check if data is received.
* @param Buf: Buffer of data to be received
* @param Len: Number of data received (in bytes)
*/
void TEMPLATE_PRNT_PageEndManager(uint8_t *Buf, uint32_t Len)
{
  UNUSED(Buf);
  UNUSED(Len);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

