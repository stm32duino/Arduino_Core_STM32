/*
  PluggableUSB.h
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

#ifndef PUSB_STM32_h
#define PUSB_STM32_h

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#include "USBAPI.h"
#include <stdint.h>

class PluggableUSBModule {
  public:
    PluggableUSBModule(uint8_t numEps, uint8_t numIfs, uint8_t *epType) : numEndpoints(numEps), numInterfaces(numIfs), endpointType(epType), pluggedEndpoint(1)
    {
    }

  protected:
    virtual bool setup(USBSetup &setup) = 0;
    virtual int getInterface(uint8_t *interfaceCount) = 0;
    virtual int getDescriptor(USBSetup &setup) = 0;
    virtual uint8_t getShortName(char *name)
    {
      name[0] = 'A' + pluggedInterface;
      return 1;
    }

    uint8_t pluggedInterface;
    uint8_t pluggedEndpoint;

    const uint8_t numEndpoints;
    const uint8_t numInterfaces;
    const uint8_t *endpointType;

    virtual uint8_t getNumEndpoints()
    {
      return numEndpoints;
    }

    virtual uint8_t getNumInterfaces()
    {
      return numInterfaces;
    }

    virtual uint8_t getEndpointTypes(uint8_t *types)
    {
      for (size_t i = 0; i < numEndpoints; i++) {
        types[i] = endpointType[i];
      }
      return numEndpoints;
    }

    PluggableUSBModule *next = NULL;

    friend class PluggableUSB_;
    friend int PLUG_GetInterface(uint8_t *interfaceCount);
    friend int PLUG_GetDescriptor(USBSetup &setup);
    friend bool PLUG_Setup(USBSetup &setup);
    friend uint8_t PLUG_GetNumEndpoints();
    friend uint8_t PLUG_GetNumInterfaces();
    friend uint8_t PLUG_GetEndpointTypes(uint8_t *types);
};

class PluggableUSB_ : PluggableUSBModule {
  public:
    PluggableUSB_();
    bool plug(PluggableUSBModule *node);
    int getInterface(uint8_t *interfaceCount);
    int getDescriptor(USBSetup &setup);
    bool setup(USBSetup &setup);
    uint8_t getShortName(char *name);

  protected:
    virtual uint8_t getNumEndpoints();
    virtual uint8_t getNumInterfaces();
    virtual uint8_t getEndpointTypes(uint8_t *types);

  private:
    uint8_t lastIf;
    uint8_t lastEp;
    PluggableUSBModule *rootNode;
};

// Replacement for global singleton.
// This function prevents static-initialization-order-fiasco
// https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
PluggableUSB_ &PluggableUSB();

/// @brief Allows installing a single pluggable module without the overhead of multiple module support
/// @param root The module to install, will replace any already present
void USB_PlugRoot(PluggableUSBModule *root);

#endif

#endif /*PUSB_STM32_h*/
