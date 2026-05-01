/*
 * PacketBuffer.h
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#ifndef PACKET_BUFFER_H_
#define PACKET_BUFFER_H_

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#include "USBOptions.h"
#include <stddef.h>
#include <stdint.h>

#if PACKETBUFFER_COUNT < 2
  #warning "PacketBuffer is likely too small, expect issues"
#endif

class PacketBuffer {
  public:
    virtual uint8_t *PrepareWrite(uint32_t &len) = 0;
    virtual void CommitWrite(uint32_t len) = 0;
    virtual uint8_t *PrepareRead(uint32_t &len) = 0;
    virtual void CommitRead(uint32_t len) = 0;
    virtual uint32_t Read(uint8_t *data, uint32_t len) = 0;
    virtual uint32_t Write(uint8_t *data, uint32_t len) = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void clear() = 0;
    virtual uint32_t available() = 0;
    virtual uint32_t availableToWrite() = 0;
    virtual ~PacketBuffer() = default;
};

template <uint32_t size>
struct USBD_HID_BufferItem {
  uint32_t len = 0;
  uint32_t pos = 0;
  uint8_t buf[size];

  uint32_t Read(uint8_t *data, uint32_t length)
  {
    uint8_t read = min(Remaining(), length);
    if (read) {
      memcpy(data, buf + pos, read);
      pos += read;
    }
    return read;
  }
  uint32_t Write(uint8_t *data, uint32_t length)
  {
    uint8_t write = min(size, length);
    if (write) {
      memcpy(buf, data, write);
      len = write;
      pos = 0;
    }
    return write;
  }
  uint32_t Remaining()
  {
    return len - pos;
  }
  bool Empty()
  {
    return Remaining() <= 0;
  }
  void Clear()
  {
    len = 0;
    pos = 0;
  }
  void WriteLength(uint32_t length)
  {
    len = length;
    pos = 0;
  }
  void ReadLength(uint32_t length)
  {
    pos = min(pos + length, size);
  }
};

template <uint32_t buffersize, uint32_t capacity>
class SplitPacketBuffer : public PacketBuffer {
  public:
    virtual uint8_t *PrepareWrite(uint32_t &len)
    {
      isPrepared = true;
      if (writeHead == readHead) {
        // overwrite last
        writeHead = prevUnsafeHead(writeHead);
      }
      len = min(buffersize, len);
      return buffer[writeHead].buf;
    }
    virtual void CommitWrite(uint32_t len)
    {
      if (isPrepared) {
        buffer[writeHead].WriteLength(len);
        writeHead = newWriteHead();
      }
    }
    virtual uint8_t *PrepareRead(uint32_t &len)
    {
      isPrepared = true;
      if (!buffer[readHead].Remaining()) {
        readHead = newReadHead();
      }
      len = min(len, buffer[readHead].Remaining());
      return buffer[readHead].buf;
    }
    virtual void CommitRead(uint32_t len)
    {
      if (isPrepared) {
        buffer[readHead].ReadLength(len);
        if (buffer[readHead].Empty()) {
          readHead = newReadHead();
        }
      }
    }
    uint32_t Read(uint8_t *data, uint32_t len)
    {
      if (!buffer[readHead].Remaining()) {
        readHead = newReadHead();
      }
      uint32_t read = 0;
      if (buffer[readHead].Remaining()) {
        read = buffer[readHead].Read(data, len);
        if (buffer[readHead].Empty()) {
          readHead = newReadHead();
        }
      }
      return read;
    }
    virtual uint32_t Write(uint8_t *data, uint32_t len)
    {
      uint32_t write = 0;
      if (writeHead == readHead) {
        // overwrite last
        writeHead = prevUnsafeHead(writeHead);
      }
      write = buffer[writeHead].Write(data, len);
      writeHead = newWriteHead();
      return write;
    }
    virtual bool isEmpty()
    {
      return available() == 0;
    }
    virtual bool isFull()
    {
#if PACKETBUFFER_ALLOW_OVERWRITE
      return false;
#else
      return readHead == writeHead;
#endif
    }
    void clear()
    {
      readHead = 0;
      writeHead = 1;
    }
    virtual uint32_t available()
    {
      if (!buffer[readHead].Remaining()) {
        readHead = newReadHead();
      }
      return getAvailable(readHead, writeHead);
    }
    virtual uint32_t availableToWrite()
    {
      return readHead == writeHead ? 0 : capacity;
    }

    uint32_t getAvailable(int head, int otherhead)
    {
#if PACKETBUFFER_USE_FAST_AVAILABLE
      return buffer[head].Remaining();
#else
      uint32_t16_t total = 0;
      auto ptr = head;
      auto endptr = otherhead;
      for (size_t i = 0; i != endptr; i++) {
        total += buffer[i].Remaining();
        i = newUnsafeHead(ptr);
      }
      return total;
#endif
    }

  private:
    USBD_HID_BufferItem<buffersize> buffer[capacity];
    int readHead = 0;
    int writeHead = 1;
    bool isPrepared = false;
    int newReadHead()
    {
      auto result = nextUnsafeHead(readHead);
      if (result == writeHead) {
        return readHead;
      }
      return result;
    }
    int newWriteHead()
    {
      return nextUnsafeHead(writeHead);
    }
    int nextUnsafeHead(int current)
    {
      auto result = current + 1;
      if (result >= capacity) {
        result = 0;
      }
      return result;
    }
    int prevUnsafeHead(int current)
    {
      auto result = current - 1;
      if (result < 0) {
        result = capacity - 1;
      }
      return result;
    }
};

#endif
#endif // PACKET_BUFFER_H_
