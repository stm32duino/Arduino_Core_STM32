/**
  ******************************************************************************
  * @file    usbh_hid.c
  * @author  MCD Application Team
  * @brief   This file is the HID Layer Handlers for USB Host HID class.
  *
  * @verbatim
  *
  *          ===================================================================
  *                                HID Class  Description
  *          ===================================================================
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse and Keyboard protocols
  *
  *  @endverbatim
  *
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

  /* BSPDependencies
  - "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
  - "stm32xxxxx_{eval}{discovery}_io.c"
  - "stm32xxxxx_{eval}{discovery}{adafruit}_lcd.c"
  - "stm32xxxxx_{eval}{discovery}_sdram.c"
  EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid.h"
#include "usbh_hid_parser.h"


/** @addtogroup USBH_LIB
* @{
*/

/** @addtogroup USBH_CLASS
* @{
*/

/** @addtogroup USBH_HID_CLASS
* @{
*/

/** @defgroup USBH_HID_CORE
* @brief    This file includes HID Layer Handlers for USB Host HID class.
* @{
*/

/** @defgroup USBH_HID_CORE_Private_TypesDefinitions
* @{
*/
/**
* @}
*/


/** @defgroup USBH_HID_CORE_Private_Defines
* @{
*/
/**
* @}
*/


/** @defgroup USBH_HID_CORE_Private_Macros
* @{
*/
/**
* @}
*/


/** @defgroup USBH_HID_CORE_Private_Variables
* @{
*/

/**
* @}
*/


/** @defgroup USBH_HID_CORE_Private_FunctionPrototypes
* @{
*/

static USBH_StatusTypeDef USBH_HID_InterfaceInit  (USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_InterfaceDeInit  (USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_ClassRequest(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_Process(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_SOFProcess(USBH_HandleTypeDef *phost);
static void  USBH_HID_ParseHIDDesc (HID_DescTypeDef *desc, uint8_t *buf);

extern USBH_StatusTypeDef USBH_HID_MouseInit(USBH_HandleTypeDef *phost);
extern USBH_StatusTypeDef USBH_HID_KeybdInit(USBH_HandleTypeDef *phost);

USBH_ClassTypeDef  HID_Class =
{
  "HID",
  USB_HID_CLASS,
  USBH_HID_InterfaceInit,
  USBH_HID_InterfaceDeInit,
  USBH_HID_ClassRequest,
  USBH_HID_Process,
  USBH_HID_SOFProcess,
  NULL,
};
/**
* @}
*/


/** @defgroup USBH_HID_CORE_Private_Functions
* @{
*/


/**
  * @brief  USBH_HID_InterfaceInit
  *         The function init the HID class.
  * @param  phost: Host handle
  * @retval USBH Status
  */
static USBH_StatusTypeDef USBH_HID_InterfaceInit (USBH_HandleTypeDef *phost)
{
  uint8_t max_ep;
  uint8_t num = 0U;
  uint8_t interface;

  USBH_StatusTypeDef status = USBH_FAIL;
  HID_HandleTypeDef *HID_Handle;

  interface = USBH_FindInterface(phost, phost->pActiveClass->ClassCode, HID_BOOT_CODE, 0xFFU);

  if(interface == 0xFFU) /* No Valid Interface */
  {
    status = USBH_FAIL;
    USBH_DbgLog ("Cannot Find the interface for %s class.", phost->pActiveClass->Name);
  }
  else
  {
    USBH_SelectInterface (phost, interface);
    phost->pActiveClass->pData = (HID_HandleTypeDef *)USBH_malloc (sizeof(HID_HandleTypeDef));
    HID_Handle =  (HID_HandleTypeDef *) phost->pActiveClass->pData;
    HID_Handle->state = HID_ERROR;

    /*Decode Bootclass Protocol: Mouse or Keyboard*/
    if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol == HID_KEYBRD_BOOT_CODE)
    {
      USBH_UsrLog ("KeyBoard device found!");
      HID_Handle->Init =  USBH_HID_KeybdInit;
    }
    else if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol  == HID_MOUSE_BOOT_CODE)
    {
      USBH_UsrLog ("Mouse device found!");
      HID_Handle->Init =  USBH_HID_MouseInit;
    }
    else
    {
      USBH_UsrLog ("Protocol not supported.");
      return USBH_FAIL;
    }

    HID_Handle->state     = HID_INIT;
    HID_Handle->ctl_state = HID_REQ_INIT;
    HID_Handle->ep_addr   = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress;
    HID_Handle->length    = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].wMaxPacketSize;
    HID_Handle->poll      = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bInterval ;

    if (HID_Handle->poll  < HID_MIN_POLL)
    {
      HID_Handle->poll = HID_MIN_POLL;
    }

    /* Check fo available number of endpoints */
    /* Find the number of EPs in the Interface Descriptor */
    /* Choose the lower number in order not to overrun the buffer allocated */
    max_ep = ( (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bNumEndpoints <= USBH_MAX_NUM_ENDPOINTS) ?
              phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bNumEndpoints :
                  USBH_MAX_NUM_ENDPOINTS);


    /* Decode endpoint IN and OUT address from interface descriptor */
    for ( ;num < max_ep; num++)
    {
      if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[num].bEndpointAddress & 0x80U)
      {
        HID_Handle->InEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[num].bEndpointAddress);
        HID_Handle->InPipe  =\
          USBH_AllocPipe(phost, HID_Handle->InEp);

        /* Open pipe for IN endpoint */
        USBH_OpenPipe  (phost,
                        HID_Handle->InPipe,
                        HID_Handle->InEp,
                        phost->device.address,
                        phost->device.speed,
                        USB_EP_TYPE_INTR,
                        HID_Handle->length);

        USBH_LL_SetToggle (phost, HID_Handle->InPipe, 0U);

      }
      else
      {
        HID_Handle->OutEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[num].bEndpointAddress);
        HID_Handle->OutPipe  =\
          USBH_AllocPipe(phost, HID_Handle->OutEp);

        /* Open pipe for OUT endpoint */
        USBH_OpenPipe  (phost,
                        HID_Handle->OutPipe,
                        HID_Handle->OutEp,
                        phost->device.address,
                        phost->device.speed,
                        USB_EP_TYPE_INTR,
                        HID_Handle->length);

        USBH_LL_SetToggle (phost, HID_Handle->OutPipe, 0U);
      }

    }
    status = USBH_OK;
  }
  return status;
}

/**
  * @brief  USBH_HID_InterfaceDeInit
  *         The function DeInit the Pipes used for the HID class.
  * @param  phost: Host handle
  * @retval USBH Status
  */
USBH_StatusTypeDef static USBH_HID_InterfaceDeInit (USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle =  (HID_HandleTypeDef *) phost->pActiveClass->pData;

  if(HID_Handle->InPipe != 0x00U)
  {
    USBH_ClosePipe  (phost, HID_Handle->InPipe);
    USBH_FreePipe  (phost, HID_Handle->InPipe);
    HID_Handle->InPipe = 0U;     /* Reset the pipe as Free */
  }

  if(HID_Handle->OutPipe != 0x00U)
  {
    USBH_ClosePipe(phost, HID_Handle->OutPipe);
    USBH_FreePipe  (phost, HID_Handle->OutPipe);
    HID_Handle->OutPipe = 0U;     /* Reset the pipe as Free */
  }

  if(phost->pActiveClass->pData)
  {
    USBH_free (phost->pActiveClass->pData);
  }

  return USBH_OK;
}

/**
  * @brief  USBH_HID_ClassRequest
  *         The function is responsible for handling Standard requests
  *         for HID class.
  * @param  phost: Host handle
  * @retval USBH Status
  */
static USBH_StatusTypeDef USBH_HID_ClassRequest(USBH_HandleTypeDef *phost)
{

  USBH_StatusTypeDef status         = USBH_BUSY;
  USBH_StatusTypeDef classReqStatus = USBH_BUSY;
  HID_HandleTypeDef *HID_Handle =  (HID_HandleTypeDef *) phost->pActiveClass->pData;

  /* Switch HID state machine */
  switch (HID_Handle->ctl_state)
  {
  case HID_REQ_INIT:
  case HID_REQ_GET_HID_DESC:

    /* Get HID Desc */
    if (USBH_HID_GetHIDDescriptor (phost, USB_HID_DESC_SIZE)== USBH_OK)
    {

      USBH_HID_ParseHIDDesc(&HID_Handle->HID_Desc, phost->device.Data);
      HID_Handle->ctl_state = HID_REQ_GET_REPORT_DESC;
    }

    break;
  case HID_REQ_GET_REPORT_DESC:


    /* Get Report Desc */
    if (USBH_HID_GetHIDReportDescriptor(phost, HID_Handle->HID_Desc.wItemLength) == USBH_OK)
    {
      /* The descriptor is available in phost->device.Data */

      HID_Handle->ctl_state = HID_REQ_SET_IDLE;
    }

    break;

  case HID_REQ_SET_IDLE:

    classReqStatus = USBH_HID_SetIdle (phost, 0U, 0U);

    /* set Idle */
    if (classReqStatus == USBH_OK)
    {
      HID_Handle->ctl_state = HID_REQ_SET_PROTOCOL;
    }
    else
    {
      if(classReqStatus == USBH_NOT_SUPPORTED)
      {
        HID_Handle->ctl_state = HID_REQ_SET_PROTOCOL;
      }
    }
    break;

  case HID_REQ_SET_PROTOCOL:
    /* set protocol */
    if (USBH_HID_SetProtocol (phost, 0U) == USBH_OK)
    {
      HID_Handle->ctl_state = HID_REQ_IDLE;

      /* all requests performed*/
      phost->pUser(phost, HOST_USER_CLASS_ACTIVE);
      status = USBH_OK;
    }
    break;

  case HID_REQ_IDLE:
  default:
    break;
  }

  return status;
}

/**
  * @brief  USBH_HID_Process
  *         The function is for managing state machine for HID data transfers
  * @param  phost: Host handle
  * @retval USBH Status
  */
static USBH_StatusTypeDef USBH_HID_Process(USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef status = USBH_OK;
  HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;

  switch (HID_Handle->state)
  {
  case HID_INIT:
    HID_Handle->Init(phost);
    HID_Handle->state = HID_IDLE;

#if (USBH_USE_OS == 1U)
    phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
    (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
    (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
    break;

  case HID_IDLE:
    status = USBH_HID_GetReport (phost, 0x01U, 0U, HID_Handle->pData, (uint8_t)HID_Handle->length);
    if (status == USBH_OK)
    {
      USBH_HID_FifoWrite(&HID_Handle->fifo, HID_Handle->pData, HID_Handle->length);
      HID_Handle->state = HID_SYNC;
    }
    else if (status == USBH_BUSY)
    {
      HID_Handle->state = HID_IDLE;
      status = USBH_OK;
    }
    else if (status == USBH_NOT_SUPPORTED)
    {
      HID_Handle->state = HID_SYNC;
      status = USBH_OK;
    }
    else
    {
      HID_Handle->state = HID_ERROR;
      status = USBH_FAIL;
    }

#if (USBH_USE_OS == 1U)
    phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
    (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
    (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
    break;

  case HID_SYNC:
    /* Sync with start of Even Frame */
    if(phost->Timer & 1U)
    {
      HID_Handle->state = HID_GET_DATA;
    }

#if (USBH_USE_OS == 1U)
    phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
    (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
    (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
    break;

  case HID_GET_DATA:
    USBH_InterruptReceiveData(phost, HID_Handle->pData,
                              (uint8_t)HID_Handle->length,
                              HID_Handle->InPipe);

    HID_Handle->state = HID_POLL;
    HID_Handle->timer = phost->Timer;
    HID_Handle->DataReady = 0U;
    break;

  case HID_POLL:
    if(USBH_LL_GetURBState(phost , HID_Handle->InPipe) == USBH_URB_DONE)
    {
      if(HID_Handle->DataReady == 0U)
      {
        USBH_HID_FifoWrite(&HID_Handle->fifo, HID_Handle->pData, HID_Handle->length);
        HID_Handle->DataReady = 1U;
        USBH_HID_EventCallback(phost);

#if (USBH_USE_OS == 1U)
        phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
        (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
        (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      }
    }
    else
    {
       /* IN Endpoint Stalled */
      if(USBH_LL_GetURBState(phost, HID_Handle->InPipe) == USBH_URB_STALL)
      {
        /* Issue Clear Feature on interrupt IN endpoint */
        if(USBH_ClrFeature(phost, HID_Handle->ep_addr) == USBH_OK)
        {
          /* Change state to issue next IN token */
          HID_Handle->state = HID_GET_DATA;
        }
      }
    }
    break;

  default:
    break;
  }

  return status;
}

/**
  * @brief  USBH_HID_SOFProcess
  *         The function is for managing the SOF Process
  * @param  phost: Host handle
  * @retval USBH Status
  */
static USBH_StatusTypeDef USBH_HID_SOFProcess(USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle =  (HID_HandleTypeDef *) phost->pActiveClass->pData;

  if(HID_Handle->state == HID_POLL)
  {
    if(( phost->Timer - HID_Handle->timer) >= HID_Handle->poll)
    {
      HID_Handle->state = HID_GET_DATA;

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
    }
  }
  return USBH_OK;
}

/**
* @brief  USBH_Get_HID_ReportDescriptor
  *         Issue report Descriptor command to the device. Once the response
  *         received, parse the report descriptor and update the status.
  * @param  phost: Host handle
  * @param  Length : HID Report Descriptor Length
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_HID_GetHIDReportDescriptor (USBH_HandleTypeDef *phost,
                                                    uint16_t length)
{

  USBH_StatusTypeDef status;

  status = USBH_GetDescriptor(phost,
                              USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_STANDARD,
                              USB_DESC_HID_REPORT,
                              phost->device.Data,
                              length);

  /* HID report descriptor is available in phost->device.Data.
  In case of USB Boot Mode devices for In report handling ,
  HID report descriptor parsing is not required.
  In case, for supporting Non-Boot Protocol devices and output reports,
  user may parse the report descriptor*/


  return status;
}

/**
  * @brief  USBH_Get_HID_Descriptor
  *         Issue HID Descriptor command to the device. Once the response
  *         received, parse the report descriptor and update the status.
  * @param  phost: Host handle
  * @param  Length : HID Descriptor Length
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_HID_GetHIDDescriptor (USBH_HandleTypeDef *phost,
                                              uint16_t length)
{
  USBH_StatusTypeDef status;

  status = USBH_GetDescriptor(phost,
                              USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_STANDARD,
                              USB_DESC_HID,
                              phost->device.Data,
                              length);

  return status;
}

/**
  * @brief  USBH_Set_Idle
  *         Set Idle State.
  * @param  phost: Host handle
  * @param  duration: Duration for HID Idle request
  * @param  reportId : Targeted report ID for Set Idle request
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_HID_SetIdle (USBH_HandleTypeDef *phost,
                                     uint8_t duration,
                                     uint8_t reportId)
{

  phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE |\
    USB_REQ_TYPE_CLASS;


  phost->Control.setup.b.bRequest = USB_HID_SET_IDLE;
  phost->Control.setup.b.wValue.w = (uint16_t)(((uint32_t)duration << 8U) | (uint32_t)reportId);

  phost->Control.setup.b.wIndex.w = 0U;
  phost->Control.setup.b.wLength.w = 0U;

  return USBH_CtlReq(phost, 0U, 0U);
}


/**
  * @brief  USBH_HID_Set_Report
  *         Issues Set Report
  * @param  phost: Host handle
  * @param  reportType  : Report type to be sent
  * @param  reportId    : Targeted report ID for Set Report request
  * @param  reportBuff  : Report Buffer
  * @param  reportLen   : Length of data report to be send
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_HID_SetReport (USBH_HandleTypeDef *phost,
                                    uint8_t reportType,
                                    uint8_t reportId,
                                    uint8_t* reportBuff,
                                    uint8_t reportLen)
{

  phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE |\
    USB_REQ_TYPE_CLASS;


  phost->Control.setup.b.bRequest = USB_HID_SET_REPORT;
  phost->Control.setup.b.wValue.w = (uint16_t)(((uint32_t)reportType << 8U) | (uint32_t)reportId);

  phost->Control.setup.b.wIndex.w = 0U;
  phost->Control.setup.b.wLength.w = reportLen;

  return USBH_CtlReq(phost, reportBuff, (uint16_t)reportLen);
}


/**
  * @brief  USBH_HID_GetReport
  *         retreive Set Report
  * @param  phost: Host handle
  * @param  reportType  : Report type to be sent
  * @param  reportId    : Targeted report ID for Set Report request
  * @param  reportBuff  : Report Buffer
  * @param  reportLen   : Length of data report to be send
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_HID_GetReport (USBH_HandleTypeDef *phost,
                                    uint8_t reportType,
                                    uint8_t reportId,
                                    uint8_t* reportBuff,
                                    uint8_t reportLen)
{

  phost->Control.setup.b.bmRequestType = USB_D2H | USB_REQ_RECIPIENT_INTERFACE |\
    USB_REQ_TYPE_CLASS;


  phost->Control.setup.b.bRequest = USB_HID_GET_REPORT;
  phost->Control.setup.b.wValue.w = (uint16_t)(((uint32_t)reportType << 8U) | (uint32_t)reportId);

  phost->Control.setup.b.wIndex.w = 0U;
  phost->Control.setup.b.wLength.w = reportLen;

  return USBH_CtlReq(phost, reportBuff, (uint16_t)reportLen);
}

/**
  * @brief  USBH_Set_Protocol
  *         Set protocol State.
  * @param  phost: Host handle
  * @param  protocol : Set Protocol for HID : boot/report protocol
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_HID_SetProtocol(USBH_HandleTypeDef *phost,
                                        uint8_t protocol)
{
  phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE
                                                 | USB_REQ_TYPE_CLASS;

  phost->Control.setup.b.bRequest = USB_HID_SET_PROTOCOL;
  if(protocol)
  {
    phost->Control.setup.b.wValue.w = 0U;
  }
  else
  {
    phost->Control.setup.b.wValue.w = 1U;
  }

  phost->Control.setup.b.wIndex.w = 0U;
  phost->Control.setup.b.wLength.w = 0U;

  return USBH_CtlReq(phost, 0U, 0U);

}

/**
  * @brief  USBH_ParseHIDDesc
  *         This function Parse the HID descriptor
  * @param  desc: HID Descriptor
  * @param  buf: Buffer where the source descriptor is available
  * @retval None
  */
static void  USBH_HID_ParseHIDDesc (HID_DescTypeDef *desc, uint8_t *buf)
{

  desc->bLength                  = *(uint8_t  *) (buf + 0);
  desc->bDescriptorType          = *(uint8_t  *) (buf + 1);
  desc->bcdHID                   =  LE16  (buf + 2);
  desc->bCountryCode             = *(uint8_t  *) (buf + 4);
  desc->bNumDescriptors          = *(uint8_t  *) (buf + 5);
  desc->bReportDescriptorType    = *(uint8_t  *) (buf + 6);
  desc->wItemLength              =  LE16  (buf + 7);
}

/**
  * @brief  USBH_HID_GetDeviceType
  *         Return Device function.
  * @param  phost: Host handle
  * @retval HID function: HID_MOUSE / HID_KEYBOARD
  */
HID_TypeTypeDef USBH_HID_GetDeviceType(USBH_HandleTypeDef *phost)
{
  HID_TypeTypeDef   type = HID_UNKNOWN;
  uint8_t InterfaceProtocol;

  if(phost->gState == HOST_CLASS)
  {
    InterfaceProtocol = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol;
    if(InterfaceProtocol == HID_KEYBRD_BOOT_CODE)
    {
      type = HID_KEYBOARD;
    }
    else
    {
      if(InterfaceProtocol == HID_MOUSE_BOOT_CODE)
      {
        type = HID_MOUSE;
      }
    }
  }
  return type;
}


/**
  * @brief  USBH_HID_GetPollInterval
  *         Return HID device poll time
  * @param  phost: Host handle
  * @retval poll time (ms)
  */
uint8_t USBH_HID_GetPollInterval(USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle =  (HID_HandleTypeDef *) phost->pActiveClass->pData;

    if((phost->gState == HOST_CLASS_REQUEST) ||
       (phost->gState == HOST_INPUT) ||
         (phost->gState == HOST_SET_CONFIGURATION) ||
           (phost->gState == HOST_CHECK_CLASS) ||
             ((phost->gState == HOST_CLASS)))
  {
    return (uint8_t)(HID_Handle->poll);
  }
  else
  {
    return 0U;
  }
}
/**
  * @brief  USBH_HID_FifoInit
  *         Initialize FIFO.
  * @param  f: Fifo address
  * @param  buf: Fifo buffer
  * @param  size: Fifo Size
  * @retval none
  */
void USBH_HID_FifoInit(FIFO_TypeDef * f, uint8_t * buf, uint16_t size)
{
     f->head = 0U;
     f->tail = 0U;
     f->lock = 0U;
     f->size = size;
     f->buf = buf;
}

/**
  * @brief  USBH_HID_FifoRead
  *         Read from FIFO.
  * @param  f: Fifo address
  * @param  buf: read buffer
  * @param  nbytes: number of item to read
  * @retval number of read items
  */
uint16_t USBH_HID_FifoRead(FIFO_TypeDef *f, void *buf, uint16_t nbytes)
{
  uint16_t i;
  uint8_t * p;
  p = (uint8_t*) buf;

  if(f->lock == 0U)
  {
    f->lock = 1U;
    for(i = 0U; i < nbytes; i++)
    {
      if( f->tail != f->head)
      {
        *p++ = f->buf[f->tail];
        f->tail++;
        if( f->tail == f->size)
        {
          f->tail = 0U;
        }
      } else
      {
        f->lock = 0U;
        return i;
      }
    }
  }
  f->lock = 0U;

  return nbytes;
}

/**
  * @brief  USBH_HID_FifoWrite
  *         Read from FIFO.
  * @param  f: Fifo address
  * @param  buf: read buffer
  * @param  nbytes: number of item to write
  * @retval number of written items
  */
uint16_t USBH_HID_FifoWrite(FIFO_TypeDef *f, void *buf, uint16_t  nbytes)
{
  uint16_t i;
  uint8_t *p;
  p = (uint8_t*) buf;
  if(f->lock == 0U)
  {
    f->lock = 1U;
    for(i = 0U; i < nbytes; i++)
    {
      if( (f->head + 1U == f->tail) ||
         ( (f->head + 1U == f->size) && (f->tail == 0U)))
      {
        f->lock = 0U;
        return i;
      }
      else
      {
        f->buf[f->head] = *p++;
        f->head++;
        if( f->head == f->size)
        {
          f->head = 0U;
        }
      }
    }
  }
  f->lock = 0U;
  return nbytes;
}

/**
* @brief  The function is a callback about HID Data events
*  @param  phost: Selected device
* @retval None
*/
__weak void USBH_HID_EventCallback(USBH_HandleTypeDef *phost)
{

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


/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
