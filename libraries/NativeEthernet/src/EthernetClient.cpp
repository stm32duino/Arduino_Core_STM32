extern "C" {
  #include "string.h"
}

#include "Arduino.h"

#include "NativeEthernet.h"
#include "EthernetClient.h"
#include "EthernetServer.h"
#include "Dns.h"

EthernetClient::EthernetClient() {
}

EthernetClient::EthernetClient(uint8_t sock) {
  UNUSED(sock);
}

EthernetClient::EthernetClient(struct tcp_struct *tcpClient) {
  _tcp_client = tcpClient;
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
  /* Can't create twice the same client */
  if(_tcp_client != NULL) {
    return 0;
  }

  /* Allocates memory for client */
  _tcp_client = (struct tcp_struct *)mem_malloc(sizeof(struct tcp_struct));

  if(_tcp_client == NULL) {
    return 0;
  }

  /* Creates a new TCP protocol control block */
  _tcp_client->pcb = tcp_new();

  if(_tcp_client->pcb == NULL) {
    return 0;
  }

  _tcp_client->data.p = NULL;
  _tcp_client->data.available = 0;
  _tcp_client->state = TCP_NONE;

  ip_addr_t ipaddr;
  tcp_arg(_tcp_client->pcb, _tcp_client);
  if(ERR_OK != tcp_connect(_tcp_client->pcb, u8_to_ip_addr(rawIPAddress(ip), &ipaddr), port, &tcp_connected_callback)) {
    stop();
    return 0;
  }

  uint32_t startTime = millis();
  while(_tcp_client->state == TCP_NONE) {
    stm32_eth_scheduler();
    if((_tcp_client->state == TCP_CLOSING) || ((millis() - startTime) >= 10000)) {
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
  if( (_tcp_client == NULL) || (_tcp_client->pcb == NULL) ||
      (buf == NULL) || (size == 0)) {
    return 0;
  }

  if(ERR_OK != tcp_write(_tcp_client->pcb, buf, size, TCP_WRITE_FLAG_COPY)) {
    return 0;
  }

  //Force to send data right now!
  if(ERR_OK != tcp_output(_tcp_client->pcb)) {
    return 0;
  }

  tcp_client_states tmp = _tcp_client->state;
  while(_tcp_client->state != TCP_SENT) {
    stm32_eth_scheduler();
    if(_tcp_client->state == TCP_CLOSING) {
      stop();
      return 0;
    }
  }

  _tcp_client->state = tmp;

  return size;
}

int EthernetClient::available() {
  stm32_eth_scheduler();
  if(_tcp_client != NULL) {
    return _tcp_client->data.available;
  }
  return 0;
}

int EthernetClient::read() {
  uint8_t b;
  if((_tcp_client != NULL) && (_tcp_client->data.p != NULL)) {
    stm32_get_data(&(_tcp_client->data), &b, 1);
    return b;
  }
  // No data available
  return -1;
}

int EthernetClient::read(uint8_t *buf, size_t size) {
  if((_tcp_client != NULL) && (_tcp_client->data.p != NULL)) {
    return stm32_get_data(&(_tcp_client->data), buf, size);
  }
  return -1;
}

int EthernetClient::peek() {
  uint8_t b;
  // Unlike recv, peek doesn't check to see if there's any data available, so we must
  if (!available())
    return -1;
  b = pbuf_get_at(_tcp_client->data.p, 0);
  return b;
}

void EthernetClient::flush() {
  if((_tcp_client == NULL) || (_tcp_client->pcb == NULL)) {
    return;
  }
  tcp_output(_tcp_client->pcb);
  stm32_eth_scheduler();
}

void EthernetClient::stop() {
  if(_tcp_client == NULL) {
    return;
  }

  // Close tcp connection. If failed, force to close connection.
  if(ERR_OK != tcp_close(_tcp_client->pcb)) {
    tcp_abort(_tcp_client->pcb);
  }

  _tcp_client->pcb = NULL;
  // _tcp_client->state = TCP_NONE;

   mem_free(_tcp_client);
  _tcp_client = NULL;
}

uint8_t EthernetClient::connected() {
  uint8_t s = status();
  return ((available() && (s == TCP_CLOSING)) ||
          (s == TCP_CONNECTED) || (s == TCP_ACCEPTED));
}

uint8_t EthernetClient::status() {
  if(_tcp_client == NULL) {
    return TCP_NONE;
  }
  return _tcp_client->state;
}

// the next function allows us to use the client returned by
// EthernetServer::available() as the condition in an if-statement.

EthernetClient::operator bool() {
  return _tcp_client != NULL;
}

bool EthernetClient::operator==(const EthernetClient& rhs) {
  return _tcp_client == rhs._tcp_client && _tcp_client->pcb == rhs._tcp_client->pcb;
}

uint8_t EthernetClient::getSocketNumber() {
  return 0;
}
