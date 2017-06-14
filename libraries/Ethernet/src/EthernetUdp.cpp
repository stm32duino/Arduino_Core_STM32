/*
 *  Udp.cpp: Library to send/receive UDP packets with the Arduino ethernet shield.
 *  This version only offers minimal wrapping of socket.c/socket.h
 *  Drop Udp.h/.cpp into the Ethernet library directory at hardware/libraries/Ethernet/
 *
 * MIT License:
 * Copyright (c) 2008 Bjoern Hartmann
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * bjoern@cs.stanford.edu 12/30/2008
 */

#include "utility/socket.h"
#include "Ethernet.h"
#include "Udp.h"
#include "Dns.h"

/* Constructor */
EthernetUDP::EthernetUDP() : _sock(MAX_SOCK_NUM) {}

/* Start EthernetUDP socket, listening at local port PORT */
uint8_t EthernetUDP::begin(uint16_t port) {
  // Can create a single udp connection per socket
  if(_udp_pcb != NULL) {
    return 0;
  }

  _udp_pcb = udp_new();

  if(_udp_pcb == NULL) {
    return 0;
  }

  IPAddress ip = Ethernet.localIP();
  ip_addr_t ipaddr;

  if(ERR_OK != udp_bind(_udp_pcb, u8_to_ip_addr(rawIPAddress(ip), &ipaddr), port)) {
    // udp_recv(_udp_pcb, udp_receive_callback, &_arg);
    return 0;
  }

  _port = port;
  _remaining = 0;

  stm32_eth_scheduler();

  return 1;
}

/* return number of bytes available in the current packet,
   will return zero if parsePacket hasn't been called yet */
int EthernetUDP::available() {
  return _remaining;
}

/* Release any resources being used by this EthernetUDP instance */
void EthernetUDP::stop()
{
  if(_udp_pcb != NULL) {
    udp_disconnect(_udp_pcb);
    udp_remove(_udp_pcb);
    _udp_pcb = NULL;
  }

  stm32_eth_scheduler();
}

int EthernetUDP::beginPacket(const char *host, uint16_t port)
{
  // Look up the host first
  int ret = 0;
  DNSClient dns;
  IPAddress remote_addr;

  dns.begin(Ethernet.dnsServerIP());
  ret = dns.getHostByName(host, remote_addr);
  if (ret == 1) {
    return beginPacket(remote_addr, port);
  } else {
    return ret;
  }
}

int EthernetUDP::beginPacket(IPAddress ip, uint16_t port)
{
  if(_udp_pcb == NULL) {
    return 0;
  }

  ip_addr_t ipaddr;

  if(ERR_OK != udp_connect( _udp_pcb, u8_to_ip_addr(rawIPAddress(ip), &ipaddr), port)) {
    return 0;
  }

  udp_recv(_udp_pcb, &udp_receive_callback, &_arg);
  stm32_eth_scheduler();

  return 1;
}

int EthernetUDP::endPacket()
{
  if((_udp_pcb == NULL) || (_data == NULL)) {
    return 0;
  }

  // A remote IP & port must be connected to udp pcb. Call ::beginPacket before.
  if((udp_flags(_udp_pcb) & UDP_FLAGS_CONNECTED) != UDP_FLAGS_CONNECTED) {
    return 0;
  }

  if(ERR_OK != udp_send(_udp_pcb, _data)) {
    _data = stm32_free_data(_data);
    return 0;
  }

  _data = stm32_free_data(_data);
  stm32_eth_scheduler();

  return 1;
}

size_t EthernetUDP::write(uint8_t byte)
{
  return write(&byte, 1);
}

size_t EthernetUDP::write(const uint8_t *buffer, size_t size)
{
  _data = stm32_new_data(_data, buffer, size);
  if(_data == NULL) {
    return 0;
  }

  return size;
}

int EthernetUDP::parsePacket()
{
  // discard any remaining bytes in the last packet
  // while (_remaining) {
  //   // could this fail (loop endlessly) if _remaining > 0 and recv in read fails?
  //   // should only occur if recv fails after telling us the data is there, lets
  //   // hope the w5100 always behaves :)
  //   read();
  // }

  stm32_eth_scheduler();

  if (_arg.available > 0)
  {
    _remoteIP = IPAddress(ip_addr_to_u32(_arg.ip));
    _remotePort = _arg.port;
    _remaining = _arg.available;

    return _remaining;
  }
  // There aren't any packets available
  return 0;
}

int EthernetUDP::read()
{
  uint8_t byte;

  if(_arg.p == NULL) {
    return -1;
  }

  if (_remaining > 0)
  {
    // We read things without any problems
    _remaining--;

    if(_remaining == 0) {
      _arg.available = 0;
      _arg.p = stm32_free_data(_arg.p);
    }

    return byte;
  }

  // If we get here, there's no data available
  return -1;
}

int EthernetUDP::read(unsigned char* buffer, size_t len)
{
  if(_arg.p == NULL) {
    return -1;
  }

  if (_remaining > 0)
  {
    int got;

    if (_remaining <= len)
    {
      // data should fit in the buffer
      got = (int)stm32_get_data(_arg.p, (uint8_t *)buffer, _remaining, _remaining);
    }
    else
    {
      // too much data for the buffer,
      // grab as much as will fit
      got = (int)stm32_get_data(_arg.p, (uint8_t *)buffer, len, _remaining);
    }

    if (got > 0)
    {
      _remaining -= got;

      if(_remaining == 0) {
        _arg.available = 0;
        _arg.p = stm32_free_data(_arg.p);
      }

      return got;
    }

  }

  // If we get here, there's no data available or recv failed
  return -1;

}

int EthernetUDP::peek()
{
  uint8_t b;
  // Unlike recv, peek doesn't check to see if there's any data available, so we must.
  // If the user hasn't called parsePacket yet then return nothing otherwise they
  // may get the UDP header
  if (!_remaining)
    return -1;
  // ::peek(_sock, &b);
  stm32_get_data(_arg.p, &b, 1, _remaining);
  return b;
}

void EthernetUDP::flush()
{
  // TODO: we should wait for TX buffer to be emptied
}

/* Start EthernetUDP socket, listening at local port PORT */
uint8_t EthernetUDP::beginMulticast(IPAddress ip, uint16_t port)
{
  // Can create a single udp connection per socket
  if(_udp_pcb != NULL) {
    return 0;
  }

  _udp_pcb = udp_new();

  if(_udp_pcb == NULL) {
    return 0;
  }

  ip_addr_t ipaddr;

  if(ERR_OK != udp_bind(_udp_pcb, u8_to_ip_addr(rawIPAddress(ip), &ipaddr), port)) {
    // udp_recv(_udp_pcb, udp_receive_callback, &_arg);
    return 0;
  }

  _port = port;
  _remaining = 0;

  stm32_eth_scheduler();

  return 1;
}
