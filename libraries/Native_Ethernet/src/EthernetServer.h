#ifndef ethernetserver_h
#define ethernetserver_h

#include "Server.h"

class EthernetClient;

class EthernetServer :
public Server {
private:
  uint16_t _port;
  struct tcp_struct _tcp_server;
  struct tcp_struct *_tcp_client[MAX_CLIENT];
  
  void accept(void);
public:
  EthernetServer(uint16_t);
  EthernetClient available();
  virtual void begin();
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  using Print::write;
};

#endif
