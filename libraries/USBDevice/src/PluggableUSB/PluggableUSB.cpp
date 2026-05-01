/*
  PluggableUSB.cpp
  Copyright (c) 2015 Arduino LLC
    * Modified by Levi Gillis @ 2022-2025
      Changes can be found in the git repo https://github.com/Levi--G/USBLibrarySTM32

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#include "PluggableUSB.h"
#include "USBAPI.h"
#include "USB_EP_conf.h"

int PluggableUSB_::getInterface(uint8_t *interfaceCount)
{
  int sent = 0;
  PluggableUSBModule *node;
  for (node = rootNode; node; node = node->next) {
    int res = node->getInterface(interfaceCount);
    if (res < 0) {
      return -1;
    }
    sent += res;
  }
  return sent;
}

int PluggableUSB_::getDescriptor(USBSetup &setup)
{
  PluggableUSBModule *node;
  for (node = rootNode; node; node = node->next) {
    int ret = node->getDescriptor(setup);
    // ret!=0 -> request has been processed
    if (ret) {
      return ret;
    }
  }
  return 0;
}

uint8_t PluggableUSB_::getShortName(char *iSerialNum)
{
  uint8_t total = 0;
  PluggableUSBModule *node;
  for (node = rootNode; node; node = node->next) {
    total += node->getShortName(iSerialNum + total);
  }
  *iSerialNum = 0;
  return total;
}

bool PluggableUSB_::setup(USBSetup &setup)
{
  PluggableUSBModule *node;
  for (node = rootNode; node; node = node->next) {
    if (node->setup(setup)) {
      return true;
    }
  }
  return false;
}

bool PluggableUSB_::plug(PluggableUSBModule *node)
{
  if (!rootNode) {
    rootNode = node;
  } else {
    PluggableUSBModule *current = rootNode;
    while (current->next) {
      current = current->next;
    }
    current->next = node;
  }

  node->pluggedInterface = lastIf;
  node->pluggedEndpoint = lastEp;
  lastIf += node->getNumInterfaces();
  lastEp += node->getNumEndpoints();
  USB_PlugRoot(this);
  if (USB_Running()) {
    USB_End();
    USB_Begin();
  }
  return true;
}

PluggableUSB_ &PluggableUSB()
{
  static PluggableUSB_ obj;
  return obj;
}

PluggableUSB_::PluggableUSB_() : PluggableUSBModule(0, 0, nullptr),
  lastIf(0),
  lastEp(1),
  rootNode(NULL)
{
  // Empty
}

uint8_t PluggableUSB_::getNumEndpoints()
{
  uint8_t total = 0;
  PluggableUSBModule *node;
  for (node = rootNode; node; node = node->next) {
    total += node->getNumEndpoints();
  }
  return total;
}

uint8_t PluggableUSB_::getNumInterfaces()
{
  uint8_t total = 0;
  PluggableUSBModule *node;
  for (node = rootNode; node; node = node->next) {
    total += node->getNumInterfaces();
  }
  return total;
}

uint8_t PluggableUSB_::getEndpointTypes(uint8_t *types)
{
  uint8_t total = 0;
  PluggableUSBModule *node;
  for (node = rootNode; node; node = node->next) {
    total += node->getEndpointTypes(types + total);
  }
  return total;
}

#endif /* if defined(USBCON) */
