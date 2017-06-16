extern "C" {
  #include "string.h"
}

#include "utility/socket.h"

#include "Arduino.h"

#include "Ethernet.h"
#include "EthernetClient.h"
#include "EthernetServer.h"
#include "Dns.h"

EthernetClient::EthernetClient() {
}

EthernetClient::EthernetClient(uint8_t sock) {
}

int EthernetClient::connect(const char* host, uint16_t port) {
  // Look up the host first
  int ret = 0;
  DNSClient dns;
  IPAddress remote_addr;

  dns.begin(Ethernet.dnsServerIP());
  ret = dns.getHostByName(host, remote_addr);
  if (ret == 1) {
    return connect(remote_addr, port);
  } else {
    return ret;
  }
}

int EthernetClient::connect(IPAddress ip, uint16_t port) {
  if(_tcp_client.pcb != NULL) {
    return 0;
  }

  _tcp_client.pcb = tcp_new();

  if(_tcp_client.pcb == NULL) {
    return 0;
  }

  ip_addr_t ipaddr;
  tcp_arg(_tcp_client.pcb, &_tcp_client);
  _tcp_client.state = TCP_NONE;
  if(ERR_OK != tcp_connect(_tcp_client.pcb, u8_to_ip_addr(rawIPAddress(ip), &ipaddr), port, &tcp_connected_callback)) {
    stop();
    return 0;
  }

  while(_tcp_client.state == TCP_NONE) {
    stm32_eth_scheduler();
    if(_tcp_client.state == TCP_CLOSING) {
      stop();
      return 0;
    }
  }

  return 1;
}

size_t EthernetClient::write(uint8_t b) {
  return write(&b, 1);
}

size_t EthernetClient::write(const uint8_t *buf, size_t size) {
  if( (_tcp_client.pcb == NULL) ||
      (_tcp_client.state != TCP_CONNECTED) ||
      (buf == NULL) || (size == 0)) {
    return 0;
  }

  if(ERR_OK != tcp_write(_tcp_client.pcb, buf, size, TCP_WRITE_FLAG_COPY)) {
    return 0;
  }

  // Force to send data right now!
  if(ERR_OK != tcp_output(_tcp_client.pcb)) {
    return 0;
  }

  while(_tcp_client.state != TCP_SENT) {
    stm32_eth_scheduler();
    if(_tcp_client.state == TCP_CLOSING) {
      stop();
      return 0;
    }
  }

  _tcp_client.state = TCP_CONNECTED;

  return size;
}

int EthernetClient::available() {
  stm32_eth_scheduler();
  if(_tcp_client.p != NULL) {
    return _tcp_client.available;
  }
  return 0;
}

int EthernetClient::read() {
  uint8_t b;
  if(_tcp_client.p != NULL) {
    stm32_get_data(_tcp_client.p, &b, 1, _tcp_client.available);
    _tcp_client.available--;

    if(_tcp_client.available == 0) {
      _tcp_client.p = stm32_free_data(_tcp_client.p);
    }

    return b;
  } else {
    // No data available
    return -1;
  }
}

int EthernetClient::read(uint8_t *buf, size_t size) {
  uint16_t nb;
  if(_tcp_client.p != NULL) {
    nb = stm32_get_data(_tcp_client.p, buf, size, _tcp_client.available);
    _tcp_client.available -= nb;

    if(_tcp_client.available == 0) {
      _tcp_client.p = stm32_free_data(_tcp_client.p);
    }

    return nb;
  }
  return -1;
}

int EthernetClient::peek() {
  uint8_t b;
  // Unlike recv, peek doesn't check to see if there's any data available, so we must
  if (!available())
    return -1;
  stm32_get_data(_tcp_client.p, &b, 1, _tcp_client.available);
  return b;
}

void EthernetClient::flush() {
  tcp_output(_tcp_client.pcb);
  stm32_eth_scheduler();
}

void EthernetClient::stop() {
  // Close tcp connection. If failed, force to close connection.
  if(ERR_OK != tcp_close(_tcp_client.pcb)) {
    tcp_abort(_tcp_client.pcb);
  }

  _tcp_client.pcb = NULL;
  _tcp_client.state = TCP_NONE;
}

uint8_t EthernetClient::connected() {
  uint8_t s = status();
  return ((available() && (s == TCP_CLOSING)) || (s == TCP_CONNECTED));
}

uint8_t EthernetClient::status() {
  return _tcp_client.state;
}

// the next function allows us to use the client returned by
// EthernetServer::available() as the condition in an if-statement.

EthernetClient::operator bool() {
  return _sock != MAX_SOCK_NUM;
}

bool EthernetClient::operator==(const EthernetClient& rhs) {
  return _sock == rhs._sock && _sock != MAX_SOCK_NUM && rhs._sock != MAX_SOCK_NUM;
}

uint8_t EthernetClient::getSocketNumber() {
  return 0;
}
