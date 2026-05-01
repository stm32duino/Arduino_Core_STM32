/*
  USBAPI.h
  Copyright (c) 2005-2014 Arduino.  All right reserved.
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

#ifndef __USBAPI__
#define __USBAPI__

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#include <inttypes.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#include "Arduino.h"
#include "USB_EP.h"

#define EPX_SIZE USB_EP_SIZE

#include "USBCore.h"

//================================================================================
//================================================================================
//  USB

#define EP_TYPE_CONTROL         (USB_ENDPOINT_TYPE_CONTROL)
#define EP_TYPE_BULK_IN         (USB_ENDPOINT_IN(USB_ENDPOINT_TYPE_BULK))
#define EP_TYPE_BULK_OUT        (USB_ENDPOINT_TYPE_BULK)
#define EP_TYPE_INTERRUPT_IN    (USB_ENDPOINT_IN(USB_ENDPOINT_TYPE_INTERRUPT))
#define EP_TYPE_INTERRUPT_OUT   (USB_ENDPOINT_TYPE_INTERRUPT)
#define EP_TYPE_ISOCHRONOUS_IN  (USB_ENDPOINT_IN(USB_ENDPOINT_TYPE_ISOCHRONOUS))
#define EP_TYPE_ISOCHRONOUS_OUT (USB_ENDPOINT_TYPE_ISOCHRONOUS)

//================================================================================
//================================================================================
//  Low level API

typedef struct {
  uint8_t bmRequestType;
  uint8_t bRequest;
  uint8_t wValueL;
  uint8_t wValueH;
  uint16_t wIndex;
  uint16_t wLength;
} USBSetup;

//================================================================================
//================================================================================

#define TRANSFER_PGM     0x80
#define TRANSFER_RELEASE 0x40
#define TRANSFER_ZERO    0x20

/// @brief Sends a message over the CTRL 0 endpoint
/// @param flags ignored on STM32
/// @param d data buffer
/// @param len length of data
/// @return length of data written, can be smaller than len
int USB_SendControl(uint8_t flags, const void *d, int len);
/// @brief Reads data from the CTRL 0 endpoint
/// @param d data buffer
/// @param len length of data
/// @return length read into buffer, can be smaller than len
int USB_RecvControl(void *d, int len);
/// @brief Gives the available read length on an RX (OUT) endpoint
/// @param ep RX (OUT) endpoint
/// @return length in bytes
uint8_t USB_Available(uint8_t ep);
/// @brief The amount of free space on a TX (IN) ep
/// @param ep TX (IN) endpoint
/// @return free space in bytes
uint8_t USB_SendSpace(uint8_t ep);
/// @brief Sends a zero length packet, blocking for compatibility
/// @param ep TX (IN) endpoint
/// @return 0
int USB_SendZLP(uint8_t ep);
/// @brief Sends data to an endpoint, blocking for compatibility
/// @param ep TX (IN) endpoint
/// @param data data buffer
/// @param len data length
/// @return length written to EP, can be smaller than len
int USB_Send(uint8_t ep, const void *data, int len);
/// @brief Sends data to an endpoint, non blocking
/// unless previous data is still being sent out
/// when not using TX buffers make sure to use a buffer allocated on heap
/// @param ep TX (IN) endpoint
/// @param data data buffer
/// @param len data length
/// @return length written to EP, can be smaller than len
int USB_SendQuick(uint8_t ep, const void *data, int len);
/// @brief Returns if sending is possible on this endpoint
/// @param ep TX (IN) endpoint
/// @return true if sending is possible
bool USB_SendAvailable(uint8_t ep);
/// @brief Receives data on a RX (OUT) endpoint
/// @param ep RX (OUT) endpoint
/// @param data data buffer
/// @param len data length
/// @return length read into buffer
int USB_Recv(uint8_t ep, void *data, int len);
/// @brief Reads a single byte from an endpoint,
/// not very performant, prefer using a buffer instead
/// @param ep RX (OUT) endpoint
/// @return 1 if reading was successful
int USB_Recv(uint8_t ep);
/// @brief Flushes an endpoint
/// @param ep RX or TX endpoint
void USB_Flush(uint8_t ep);
/// @brief Starts the USB and allocates needed resources
/// @return true if successful
bool USB_Begin();
/// @brief Checks if the USB is allocated and ready to connect.
///
/// Sending to buffer is already possible but there might be no host listening yet
/// @return true if ready
bool USB_Running();
/// @brief Checks if the USB has active communication with a host
///
/// This can be used to react to usb connection/disconnection
/// @return true if active
bool USB_Connected();
/// @brief Stops all USB activity and cleans up used resources
void USB_End();

// for pluggableusb support
int PLUG_GetInterface(uint8_t *interfaceCount);
int PLUG_GetDescriptor(USBSetup &setup);
bool PLUG_Setup(USBSetup &setup);
uint8_t PLUG_GetNumEndpoints();
uint8_t PLUG_GetNumInterfaces();
uint8_t PLUG_GetEndpointTypes(uint8_t *types);

#endif

#endif /* if defined(USBCON) */
