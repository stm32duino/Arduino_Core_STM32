/*
 * USB_EP_conf.cpp
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#if defined(HAL_PCD_MODULE_ENABLED) && defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#include "USB_EP_conf.h"

ep_desc_t ep_def[USB_MAX_EPS_SLOTS];
uint_fast8_t ep_num = 0;

void USB_EP_ClearEndpoints()
{
  ep_desc_t epdef = {0, 0};
  for (uint_fast8_t i = 0; i < USB_MAX_EPS_SLOTS; i++) {
    ep_def[i] = epdef;
  }
  ep_num = 0;
}

int USB_EP_GetEndpointsSize()
{
  return (USB_ABS_EP0_SIZE + USB_ABS_EP0_TX_SIZE + (ep_num * USB_ABS_EP_SIZE));
}

uint8_t USB_EP_AddEndpoint(uint32_t ep_type)
{
  if (ep_num >= USB_MAX_EPS_SLOTS || USB_EP_GetEndpointsSize() + USB_ABS_EP_SIZE > PMA_MAX_SIZE) {
    return 0;
  }
  uint8_t ep = ep_num + 1;
  ep_def[ep_num].ep_num = ep | (ep_type & (uint32_t)USB_ENDPOINT_DIRECTION_MASK);
  ep_def[ep_num].ep_type = (ep_type & (uint32_t)USB_ENDPOINT_TYPE_MASK);
  ep_num++;
  return ep;
}

uint_fast8_t USB_EP_GetNumEndpoints()
{
  return ep_num;
}

const ep_desc_t *USB_EP_GetEndpointsSlots()
{
  return ep_def;
}

#endif
