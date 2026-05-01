/*
 * USBCore.c
 * Template generated with Stm32CubeMX "usbd_customhid.c":
 * Copyright (c) 2015 STMicroelectronics.
 * All rights reserved.
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 * Implementation/modification:
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

/* Includes ------------------------------------------------------------------*/
#include "Arduino.h"
#include "PacketBuffer.h"
#include "PluggableUSB.h"
#include "USBAPI.h"
#include "USBCore_stm32.h"
#include "USB_EP_conf.h"
#include "usbd_desc.h"

static uint8_t USBD_HID_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_HID_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_HID_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);
static bool Init_Endpoints();

static uint8_t *USBD_HID_GetFSCfgDesc(uint16_t *length);
static uint8_t *USBD_HID_GetHSCfgDesc(uint16_t *length);
static uint8_t *USBD_HID_GetOtherSpeedCfgDesc(uint16_t *length);
static uint8_t *USBD_HID_GetDeviceQualifierDesc(uint16_t *length);
static uint8_t USBD_HID_EP0_RxReady(USBD_HandleTypeDef *pdev);
static uint8_t USBD_HID_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t USBD_HID_DataOut(USBD_HandleTypeDef *pdev, uint8_t endp);

static bool PrepareReceive(USBD_HandleTypeDef *pdev, USBD_HID_HandleTypeDef *hhid, uint8_t ep);

USBD_ClassTypeDef USBD_HID_CLASS = {
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL,                 /* EP0_TxSent */
  USBD_HID_EP0_RxReady, /* EP0_RxReady */
  USBD_HID_DataIn,      /* DataIn */
  USBD_HID_DataOut,     /* DataOut */
  NULL,                 /* SOF */
  NULL,
  NULL,
  USBD_HID_GetHSCfgDesc,
  USBD_HID_GetFSCfgDesc,
  USBD_HID_GetOtherSpeedCfgDesc,
  USBD_HID_GetDeviceQualifierDesc,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END = {
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

/* Buffers for properly handling interface and report descriptors */
#ifndef USB_CFGBUFFER_LEN
  #define USB_CFGBUFFER_LEN 128
#endif
__ALIGN_BEGIN uint8_t tempcfgBuffer[USB_CFGBUFFER_LEN] __ALIGN_END;
uint8_t tempcfgbufferpos = 0;
bool cfgBufferMode = false;
__ALIGN_BEGIN uint8_t tempdescBuffer[USB_CFGBUFFER_LEN] __ALIGN_END;
uint8_t tempdescbufferpos = 0;
bool descBufferMode = false;

/* RX buffers */
PacketBuffer *EP_Buffers[USB_MAX_EPS];
uint16_t Recv_EP0 = false;
USBD_SetupReqTypedef EP0Setup;

/* USB Device Core HID composite handle declaration */
USBD_HandleTypeDef hUSBD_Device_HID_Handle;

bool HID_initialized = false;
PluggableUSBModule *rootModule;

bool USB_Begin()
{
  if (HID_initialized || rootModule == NULL) {
    return false;
  }

  if (!Init_Endpoints()) {
    return false;
  }

  /* Init Device Library */
  if (USBD_Init(&hUSBD_Device_HID_Handle, &USBD_Desc, 0) != USBD_OK) {
    return false;
  }
  /* Add Supported Class */
  if (USBD_RegisterClass(&hUSBD_Device_HID_Handle, &USBD_HID_CLASS) != USBD_OK) {
    return false;
  }
  /* Start Device Process */
  if (USBD_Start(&hUSBD_Device_HID_Handle) != USBD_OK) {
    return false;
  }
  HID_initialized = true;
  return true;
}

bool GetHHID(USBD_HID_HandleTypeDef *&hhid)
{
  hhid = (USBD_HID_HandleTypeDef *)hUSBD_Device_HID_Handle.pClassData;
  return hhid != NULL;
}

bool USB_Running()
{
  USBD_HID_HandleTypeDef *hhid;
  return GetHHID(hhid);
}

bool USB_Connected()
{
  return hUSBD_Device_HID_Handle.dev_state == USBD_STATE_CONFIGURED;
}

void USB_End()
{
  if (HID_initialized) {
    /* Stop Device Process */
    USBD_Stop(&hUSBD_Device_HID_Handle);
    /* DeInit Device Library */
    USBD_DeInit(&hUSBD_Device_HID_Handle);
    HID_initialized = false;
  }
}

void USB_PlugRoot(PluggableUSBModule *root)
{
  bool wasinit = HID_initialized;
  if (wasinit) {
    USB_End();
  }
  rootModule = root;
  if (wasinit) {
    USB_Begin();
  }
}
int PLUG_GetInterface(uint8_t *interfaceCount)
{
  return rootModule->getInterface(interfaceCount);
}
int PLUG_GetDescriptor(USBSetup &setup)
{
  return rootModule->getDescriptor(setup);
}
bool PLUG_Setup(USBSetup &setup)
{
  return rootModule->setup(setup);
}
uint8_t PLUG_GetNumEndpoints()
{
  return rootModule->getNumEndpoints();
}
uint8_t PLUG_GetNumInterfaces()
{
  return rootModule->getNumInterfaces();
}
uint8_t PLUG_GetEndpointTypes(uint8_t *types)
{
  return rootModule->getEndpointTypes(types);
}

static bool Init_Endpoints()
{
  USB_EP_ClearEndpoints();
  uint8_t eps = PLUG_GetNumEndpoints();
  if (eps > USB_MAX_EPS) {
    return false;
  }
  uint8_t epstypes[eps];
  if (eps != PLUG_GetEndpointTypes(epstypes)) {
    return false;
  }
  for (uint_fast8_t i = 0; i < eps; i++) {
    if (!USB_EP_AddEndpoint(epstypes[i])) {
      return false;
    }
  }
  return true;
}

USBD_EndpointTypeDef *GetEPTypeDef(uint8_t ep, bool in)
{
  if (in) {
    return &hUSBD_Device_HID_Handle.ep_in[SMALL_EP(ep)];
  }
  return &hUSBD_Device_HID_Handle.ep_out[SMALL_EP(ep)];
}

static bool USB_SendAvailable_Internal(USBD_HID_HandleTypeDef *&hhid, uint8_t endp)
{
  uint8_t ep = SMALL_EP(endp);
#if PACKETBUFFER_USE_TX_BUFFERS
  if (EP_Buffers[ep] != NULL && (!EP_Buffers[ep]->isFull() || PACKETBUFFER_ALLOW_OVERWRITE)) {
    return true;
  }
#endif
  return hUSBD_Device_HID_Handle.dev_state == USBD_STATE_CONFIGURED && hhid->EPstate[ep] != HID_BUSY;
}

static bool USB_Flush_Internal(USBD_HID_HandleTypeDef *&hhid, uint8_t endp)
{
  if (USB_SendAvailable_Internal(hhid, endp)) {
    return true;
  }
  uint8_t ep = SMALL_EP(endp);
  uint8_t EP = IN_EP(endp);
#if USB_WRITE_TIMEOUT
  uint32_t start = millis();
  while (hhid->EPstate[ep] == HID_BUSY && millis() - start < USB_WRITE_TIMEOUT) {
    delay(1);
  }
#else
  while (hhid->EPstate[ep] == HID_BUSY) {
    delay(1);
  }
#endif
  USBD_LL_FlushEP(&hUSBD_Device_HID_Handle, EP);
  return USB_SendAvailable_Internal(hhid, endp);
}

bool USB_SendAvailable(uint8_t endp)
{
  USBD_HID_HandleTypeDef *hhid;
  if (!GetHHID(hhid)) {
    return false;
  }
  return USB_SendAvailable_Internal(hhid, endp);
}

#if PACKETBUFFER_USE_TX_BUFFERS
static bool USB_SendTXBufferUnsafe(USBD_HandleTypeDef *pdev, USBD_HID_HandleTypeDef *hhid, uint8_t ep)
{
  if (EP_Buffers[ep] && !EP_Buffers[ep]->isEmpty()) {
    hhid->EPstate[ep] = HID_BUSY;
    uint32_t len = USB_EP_SIZE;
    auto buf = EP_Buffers[ep]->PrepareRead(len);
    pdev->ep_in[ep].total_length = len;
    (void)USBD_LL_Transmit(pdev, ep, buf, len);
    return true;
  }
  return false;
}
#endif

int USB_SendQuick(uint8_t endp, const void *data, int len)
{
  USBD_HID_HandleTypeDef *hhid;
  if (!GetHHID(hhid)) {
    return 0;
  }
  if (!USB_SendAvailable_Internal(hhid, endp) && !USB_Flush_Internal(hhid, endp)) {
    return 0;
  }
  uint8_t ep = SMALL_EP(endp);
  uint8_t EP = IN_EP(endp);
#if PACKETBUFFER_USE_TX_BUFFERS
  auto buffer = EP_Buffers[ep];
  if (buffer == NULL) {
    return 0;
  }
  auto write = buffer->Write((uint8_t *)data, len);
  if (hhid->EPstate[ep] == HID_IDLE) {
    USB_SendTXBufferUnsafe(&hUSBD_Device_HID_Handle, hhid, ep);
  }
  return write;
#else
  if (hhid->EPstate[ep] == HID_IDLE) {
    hhid->EPstate[ep] = HID_BUSY;
    hUSBD_Device_HID_Handle.ep_in[ep].total_length = len;
    (void)USBD_LL_Transmit(&hUSBD_Device_HID_Handle, EP, (uint8_t *)data, len);
    return len;
  }
  return 0;
#endif
}

int USB_Send(uint8_t endp, const void *data, int len)
{
  USBD_HID_HandleTypeDef *hhid;
  if (GetHHID(hhid)) {
    int ret = USB_SendQuick(endp, data, len);
    // USB_Send is blocking in the original avr implementation
    USB_Flush_Internal(hhid, endp);
    return ret;
  }
  return 0;
}

int USB_SendControl(uint8_t flags, const void *d, int len)
{
  if (cfgBufferMode) {
    if (tempcfgbufferpos + len < USB_CFGBUFFER_LEN) {
      uint8_t cpy = 0;
      uint8_t *ptr = (uint8_t *)d;
      for (uint8_t i = 0; i < len;) {
        if (ptr[i] == 0) {
          i++;
        } else if (ptr[i] + i <= len) {
          memcpy(tempcfgBuffer + tempcfgbufferpos, ptr + i, ptr[i]);
          tempcfgbufferpos += ptr[i];
          cpy += ptr[i];
          i += ptr[i];
        }
      }
      return cpy;
    }
    return 0;
  }
  if (descBufferMode) {
    if (tempdescbufferpos + len < USB_CFGBUFFER_LEN) {
      memcpy(tempdescBuffer + tempdescbufferpos, d, len);
      tempdescbufferpos += len;
      return len;
    }
    return 0;
  }
  if (!USB_Running()) {
    return 0;
  }
  return (USBD_CtlSendData(&hUSBD_Device_HID_Handle, (uint8_t *)d, len) == USBD_OK) ? len : 0;
}

uint8_t USB_SendSpace(uint8_t endp)
{
  return USB_SendAvailable(endp) ? (endp == 0 ? USB_EP0_SIZE : USB_EP_SIZE) : 0;
}

int USB_SendZLP(uint8_t endp)
{
  return USB_Send(endp, NULL, 0);
}

void USB_Flush(uint8_t endp)
{
  USBD_HID_HandleTypeDef *hhid;
  if (GetHHID(hhid)) {
    USB_Flush_Internal(hhid, endp);
  }
}

uint8_t USB_Available(uint8_t endp)
{
  auto buffer = EP_Buffers[SMALL_EP(endp)];
  if (!buffer) {
    return 0;
  }
  return buffer->available();
}

int USB_Recv(uint8_t endp, void *data, int len)
{
  if (len <= 0) {
    return 0;
  }
  uint8_t ep = SMALL_EP(endp);
  if (ep == 0) {
    return USB_RecvControl(data, len);
  }
  USBD_HID_HandleTypeDef *hhid;
  if (!GetHHID(hhid)) {
    return 0;
  }
  auto buffer = EP_Buffers[ep];
  if (buffer == NULL) {
    return 0;
  }
  uint8_t read = buffer->Read((uint8_t *)data, len);
  PrepareReceive(&hUSBD_Device_HID_Handle, hhid, ep);
  return read;
}

int USB_Recv(uint8_t endp)
{
  uint8_t c;
  if (USB_Recv(endp, &c, 1) != 1) {
    return -1;
  }
  return c;
}

int USB_RecvControl(void *data, int len)
{
  if (len <= 0) {
    return 0;
  }
  auto buffer = EP_Buffers[0];
  if (buffer == NULL) {
    return 0;
  }
  return buffer->Read((uint8_t *)data, len);
}

/**
 * @brief  USBD_HID_Init
 *         Initialize the HID interface
 * @param  pdev: device instance
 * @param  cfgidx: Configuration index
 * @retval status
 */
static uint8_t USBD_HID_Init(USBD_HandleTypeDef *pdev,
                             uint8_t cfgidx)
{
  UNUSED(cfgidx);

  USBD_HID_HandleTypeDef *hhid;

  hhid = (USBD_HID_HandleTypeDef *)USBD_malloc(sizeof(USBD_HID_HandleTypeDef));

  if (hhid == NULL) {
    pdev->pClassData = NULL;
    return (uint8_t)USBD_EMEM;
  }

  (void)USBD_memset(hhid, 0, sizeof(USBD_HID_HandleTypeDef));

  pdev->pClassData = (void *)hhid;

  EP_Buffers[0] = new SplitPacketBuffer<USB_EP0_SIZE, EP0_PACKETBUFFER_COUNT>();

  uint_fast8_t eps = USB_EP_GetNumEndpoints();
  const ep_desc_t *epdefs = USB_EP_GetEndpointsSlots();

  for (uint_fast8_t i = 0; i < eps; i++) {
    uint8_t EP = epdefs[i].ep_num;
    uint8_t ep = SMALL_EP(EP);
    USBD_EndpointTypeDef *eptdef = GetEPTypeDef(EP, IS_IN_EP(EP));
    eptdef->bInterval = ((pdev->dev_speed == USBD_SPEED_HIGH) ? HID_HS_BINTERVAL : HID_FS_BINTERVAL);
    USBD_LL_OpenEP(pdev, EP, epdefs[i].ep_type, USB_EP_SIZE);
    eptdef->is_used = 1U;
    hhid->EPstate[ep] = HID_IDLE;
    if (IS_IN_EP(EP)) {
#if PACKETBUFFER_USE_TX_BUFFERS
      EP_Buffers[ep] = new SplitPacketBuffer<USB_EP_SIZE, PACKETBUFFER_COUNT>();
#endif
    } else {
      EP_Buffers[ep] = new SplitPacketBuffer<USB_EP_SIZE, PACKETBUFFER_COUNT>();
      if (!PrepareReceive(pdev, hhid, ep)) {
        return (uint8_t)USBD_EMEM;
      }
    }
  }
  return (uint8_t)USBD_OK;
}

/**
 * @brief  USBD_HID_DeInit
 *         DeInitialize the HID layer
 * @param  pdev: device instance
 * @param  cfgidx: Configuration index
 * @retval status
 */
static uint8_t USBD_HID_DeInit(USBD_HandleTypeDef *pdev,
                               uint8_t cfgidx)
{
  UNUSED(cfgidx);

  if (EP_Buffers[0]) {
    delete EP_Buffers[0];
    EP_Buffers[0] = NULL;
  }

  uint_fast8_t eps = USB_EP_GetNumEndpoints();
  const ep_desc_t *epdefs = USB_EP_GetEndpointsSlots();

  for (uint_fast8_t i = 0; i < eps; i++) {
    uint8_t EP = epdefs[i].ep_num;
    uint8_t ep = SMALL_EP(EP);
    USBD_EndpointTypeDef *epdef = GetEPTypeDef(ep, IS_IN_EP(EP));
    USBD_LL_CloseEP(pdev, EP);
    epdef->is_used = 0U;
    epdef->bInterval = 0U;
    if (EP_Buffers[ep]) {
      delete EP_Buffers[ep];
      EP_Buffers[ep] = NULL;
    }
  }

  /* Free allocated memory */
  if (pdev->pClassData != NULL) {
    (void)USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  }

  return (uint8_t)USBD_OK;
}

USBD_StatusTypeDef USBD_HID_GetDescriptor(USBD_HandleTypeDef *pdev,
                                          USBD_SetupReqTypedef *req)
{
  USBSetup setup = {req->bmRequest, req->bRequest, lowByte(req->wValue), highByte(req->wValue), req->wIndex, req->wLength};
  tempdescbufferpos = 0;
  descBufferMode = true;
  auto result = PLUG_GetDescriptor(setup);
  descBufferMode = false;

  if (result && tempdescbufferpos > 0) {
    USB_SendControl(0, tempdescBuffer, min((uint16_t)tempdescbufferpos, req->wLength));
  }
  return USBD_OK;
}

uint8_t HandleSetup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  USBD_HID_HandleTypeDef *hhid = (USBD_HID_HandleTypeDef *)pdev->pClassData;
  USBD_StatusTypeDef ret = USBD_OK;
  uint16_t len = 0U;
  uint8_t *pbuf = NULL;
  uint16_t status_info = 0U;

  switch (req->bmRequest & USB_REQ_TYPE_MASK) {
    case USB_REQ_TYPE_CLASS: {
        USBSetup setup = {req->bmRequest, req->bRequest, lowByte(req->wValue), highByte(req->wValue), req->wIndex, req->wLength};
        bool result = PLUG_Setup(setup);
        if (result) {
          ret = USBD_OK;
        } else {
          switch (req->bRequest) {
            case HID_REQ_SET_PROTOCOL:
              hhid->Protocol = (uint8_t)(req->wValue);
              break;

            case HID_REQ_GET_PROTOCOL:
              (void)USBD_CtlSendData(pdev, (uint8_t *)&hhid->Protocol, 1U);
              break;

            case HID_REQ_SET_IDLE:
              hhid->IdleState = (uint8_t)(req->wValue >> 8);
              break;

            case HID_REQ_GET_IDLE:
              (void)USBD_CtlSendData(pdev, (uint8_t *)&hhid->IdleState, 1U);
              break;

            default:
              USBD_CtlError(pdev, req);
              ret = USBD_FAIL;
              break;
          }
        }
        break;
      }
    case USB_REQ_TYPE_STANDARD:
      switch (req->bRequest) {
        case USB_REQ_GET_STATUS:
          if (pdev->dev_state == USBD_STATE_CONFIGURED) {
            (void)USBD_CtlSendData(pdev, (uint8_t *)&status_info, 2U);
          } else {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;
        case USB_REQ_GET_DESCRIPTOR:
          ret = USBD_HID_GetDescriptor(pdev, req);
          break;

        case USB_REQ_GET_INTERFACE:
          if (pdev->dev_state == USBD_STATE_CONFIGURED) {
            (void)USBD_CtlSendData(pdev, (uint8_t *)&hhid->AltSetting, 1U);
          } else {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_SET_INTERFACE:
          if (pdev->dev_state == USBD_STATE_CONFIGURED) {
            hhid->AltSetting = (uint8_t)(req->wValue);
          } else {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_CLEAR_FEATURE:
          break;

        default:
          USBD_CtlError(pdev, req);
          ret = USBD_FAIL;
          break;
      }
      break;

    default:
      USBD_CtlError(pdev, req);
      ret = USBD_FAIL;
      break;
  }

  return (uint8_t)ret;
}

/**
 * @brief  USBD_HID_Setup
 *         Handle the HID specific requests
 * @param  pdev: instance
 * @param  req: usb requests
 * @retval status
 */
static uint8_t USBD_HID_Setup(USBD_HandleTypeDef *pdev,
                              USBD_SetupReqTypedef *req)
{
  USBD_HID_HandleTypeDef *hhid = (USBD_HID_HandleTypeDef *)pdev->pClassData;
  if (hhid == NULL) {
    return (uint8_t)USBD_FAIL;
  }
  if (req->wLength && ((req->bmRequest & 0x80) == 0)) {
    if (Recv_EP0) {
      // transfer still in progress
      return (uint8_t)USBD_FAIL;
    }
    EP0Setup = *req;
    EP_Buffers[0]->clear();
    Recv_EP0 = min(req->wLength, (uint16_t)(PACKETBUFFER_COUNT * USB_EP0_SIZE));
    uint32_t len = Recv_EP0;
    auto buf = EP_Buffers[0]->PrepareWrite(len);
    USBD_CtlPrepareRx(&hUSBD_Device_HID_Handle, buf, len);
    return (uint8_t)USBD_OK;
  }
  return HandleSetup(pdev, req);
}

/**
 * @brief  USBD_HID_GetCfgFSDesc
 *         return FS configuration descriptor
 * @param  speed : current device speed
 * @param  length : pointer data length
 * @retval pointer to descriptor buffer
 */
static uint8_t *USBD_HID_GetFSCfgDesc(uint16_t *length)
{
  /* Since this needs to be returned as pointer to an aligned array
  we will store the "sent" configuration and send the filled buffer instead */
  auto confsize = USB_CONFIGUARTION_DESC_SIZE;
  tempcfgbufferpos = confsize;
  cfgBufferMode = true;
  u8 interfaces = 0;
  *length = PLUG_GetInterface(&interfaces);
  *length += confsize;
  cfgBufferMode = false;
  ConfigDescriptor config = D_CONFIG(*length, interfaces);
  memcpy(tempcfgBuffer, &config, confsize);
  return tempcfgBuffer;
}

/**
 * @brief  USBD_HID_GetCfgHSDesc
 *         return HS configuration descriptor
 * @param  speed : current device speed
 * @param  length : pointer data length
 * @retval pointer to descriptor buffer
 */
static uint8_t *USBD_HID_GetHSCfgDesc(uint16_t *length)
{
  // should not happen/matter => return FS
  return USBD_HID_GetFSCfgDesc(length);
}

/**
 * @brief  USBD_HID_GetOtherSpeedCfgDesc
 *         return other speed configuration descriptor
 * @param  speed : current device speed
 * @param  length : pointer data length
 * @retval pointer to descriptor buffer
 */
static uint8_t *USBD_HID_GetOtherSpeedCfgDesc(uint16_t *length)
{
  // should not happen/matter => return FS
  return USBD_HID_GetFSCfgDesc(length);
}

static uint8_t USBD_HID_HandleDataOut(USBD_HandleTypeDef *pdev, uint8_t endp)
{
  USBD_HID_HandleTypeDef *hhid;
  if (!GetHHID(hhid)) {
    return USBD_FAIL;
  }
  uint8_t ep = SMALL_EP(endp);
  auto buffer = EP_Buffers[ep];
  if (buffer == NULL) {
    // this should never happen;
    return (uint8_t)USBD_FAIL;
  }
  buffer->CommitWrite(USBD_LL_GetRxDataSize(pdev, endp));
  hhid->EPstate[ep] = HID_IDLE;
  if (ep != 0) {
    PrepareReceive(pdev, hhid, ep);
  }
  return (uint8_t)USBD_OK;
}

static uint8_t USBD_HID_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
  if (Recv_EP0) {
    if (USBD_HID_HandleDataOut(pdev, 0) != USBD_OK) {
      return (uint8_t)USBD_FAIL;
    }
    auto read = EP_Buffers[0]->available();
    if (Recv_EP0 > read) {
      uint32_t len = Recv_EP0 - read;
      auto buf = EP_Buffers[0]->PrepareWrite(len);
      USBD_CtlPrepareRx(pdev, buf, len);
      return (uint8_t)USBD_OK;
    }
    Recv_EP0 = 0;
    return (uint8_t)HandleSetup(pdev, &EP0Setup);
  }
  // this should not happen?
  return (uint8_t)USBD_FAIL;
}

/**
 * @brief  USBD_HID_DataIn
 *         handle data IN Stage
 * @param  pdev: device instance
 * @param  epnum: endpoint index
 * @retval status
 */
static uint8_t USBD_HID_DataIn(USBD_HandleTypeDef *pdev,
                               uint8_t endp)
{
  /* Ensure that the FIFO is empty before a new transfer, this condition could
  be caused by  a new transfer before the end of the previous transfer */

  uint8_t ep = SMALL_EP(endp);

  USBD_HID_HandleTypeDef *hhid;
  if (!GetHHID(hhid)) {
    return (uint8_t)USBD_FAIL;
  }

#if PACKETBUFFER_USE_TX_BUFFERS
  EP_Buffers[ep]->CommitRead(pdev->ep_in[ep].total_length);
#endif

  if (pdev->ep_in[ep].total_length > 0U && (pdev->ep_in[ep].total_length % pdev->ep_in[ep].maxpacket) == 0U) {
    /* Update the packet total length */
    pdev->ep_in[ep].total_length = 0U;

    /* Send ZLP */
    (void)USBD_LL_Transmit(pdev, endp, NULL, 0U);
    return (uint8_t)USBD_OK;
  }
#if PACKETBUFFER_USE_TX_BUFFERS
  if (!USB_SendTXBufferUnsafe(pdev, hhid, ep)) {
    hhid->EPstate[ep] = HID_IDLE;
  }
  return (uint8_t)USBD_OK;
#else
  hhid->EPstate[ep] = HID_IDLE;
  return (uint8_t)USBD_OK;
#endif
}

/**
 * @brief  USBD_CDC_DataOut
 *         Data received on non-control Out endpoint
 * @param  pdev: device instance
 * @param  epnum: endpoint number
 * @retval status
 */
static uint8_t USBD_HID_DataOut(USBD_HandleTypeDef *pdev, uint8_t endp)
{
  return USBD_HID_HandleDataOut(pdev, endp);
}

/// @param ep SMALL_EP(endp)
static bool PrepareReceive(USBD_HandleTypeDef *pdev, USBD_HID_HandleTypeDef *hhid, uint8_t ep)
{
  if (ep == 0) {
    // this should never happen
    return false;
  }
  if (hhid->EPstate[ep] == HID_BUSY) {
    return true;
  }
  if (EP_Buffers[ep]->isFull() && !PACKETBUFFER_ALLOW_OVERWRITE) {
    return false;
  }
  hhid->EPstate[ep] = HID_BUSY;
  uint32_t len = USB_EP_SIZE;
  auto buf = EP_Buffers[ep]->PrepareWrite(len);
  USBD_LL_PrepareReceive(pdev, ep, buf, len);
  return true;
}

/**
 * @brief  DeviceQualifierDescriptor
 *         return Device Qualifier descriptor
 * @param  length : pointer data length
 * @retval pointer to descriptor buffer
 */
static uint8_t *USBD_HID_GetDeviceQualifierDesc(uint16_t *length)
{
  // Serial1.println("DeviceQ");
  *length = (uint16_t)sizeof(USBD_HID_DeviceQualifierDesc);
  return USBD_HID_DeviceQualifierDesc;
}
#endif /* USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
