/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef _USB_MSC_HANDLER_H_
#define _USB_MSC_HANDLER_H_

#if defined(USBCON) && defined(USBD_USE_MSC_CLASS)

#include "usbd_core.h"
#include "usbd_msc.h"

/* Handler for mass storage devices */
class USBMscHandler {
  public:
    // Example: A 128 MB SD card has 245760 blocks, at a block size of 512 bytes
    // Returns true if successful, otherwise false.
    virtual bool GetCapacity(uint32_t *pBlockNum, uint16_t *pBlockSize) = 0;

    // Read [blk_len] blocks, starting at [blk_addr] into [buf].
    // Returns true if successful, otherwise false.
    virtual bool Read(uint8_t *pBuf, uint32_t blkAddr, uint16_t blkLen) = 0;

    // Write [blk_len] blocks, starting at [blk_addr] into [buf].
    // Returns true if successful, otherwise false.
    virtual bool Write(uint8_t *pBuf, uint32_t blkAddr, uint16_t blkLen) = 0;

    /** Optional functions **/

    virtual bool Init()
    {
      return true;
    }

    // Return false if the mass storage device has not been connected or initialized yet.
    virtual bool IsReady()
    {
      return true;
    }

    // If the device should be read-only then this function should return true.
    virtual bool IsWriteProtected()
    {
      return false;
    }
};

class DummyUSBMscHandler : public USBMscHandler {
  public:
    // Any call to one of these functions always fails.
    bool GetCapacity(uint32_t *pBlockNum, uint16_t *pBlockSize)
    {
      return false;
    }

    bool Read(uint8_t *pBuf, uint32_t blockAddr, uint16_t blkLen)
    {
      return false;
    }

    bool Write(uint8_t *pBuf, uint32_t blockAddr, uint16_t blkLen)
    {
      return false;
    }

    // The dummy handler is never ready.
    bool IsReady()
    {
      return false;
    }
};

#endif
#endif