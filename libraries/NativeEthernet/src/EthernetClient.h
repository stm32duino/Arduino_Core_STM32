#ifndef ethernetclient_h
#define ethernetclient_h
#include "Arduino.h"
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"
#include "utility/stm32_eth.h"

class EthernetClient : public Client {

public:
  EthernetClient();
  EthernetClient(uint8_t sock);
  EthernetClient(struct tcp_struct *tcpClient);

  uint8_t status();
  virtual int connect(IPAddress ip, uint16_t port);
  virtual int connect(const char *host, uint16_t port);
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  virtual int available();
  virtual int read();
  virtual int read(uint8_t *buf, size_t size);
  virtual int peek();
  virtual void flush();
  virtual void stop();
  virtual uint8_t connected();
  virtual operator bool();
  virtual bool operator==(const bool value) { return bool() == value; }
  virtual bool operator!=(const bool value) { return bool() != value; }
  virtual bool operator==(const EthernetClient&);
  virtual bool operator!=(const EthernetClient& rhs) { return !this->operator==(rhs); };
  uint8_t getSocketNumber();

  friend class EthernetServer;

  using Print::write;

private:
  struct tcp_struct *_tcp_client;
};

#endif
