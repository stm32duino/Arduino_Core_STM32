#ifndef ethernet_h
#define ethernet_h

#include <inttypes.h>
#include "IPAddress.h"
#include <LwIP.h>
#include "EthernetClient.h"
#include "EthernetServer.h"
#include "Dhcp.h"

class EthernetClass {
private:
  IPAddress _dnsServerAddress;
  DhcpClass* _dhcp;
public:
  // Initialise the Ethernet shield to use the provided MAC address and gain the rest of the
  // configuration through DHCP.
  // Returns 0 if the DHCP configuration failed, and 1 if it succeeded
  int begin(uint8_t *mac_address, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);
  void begin(uint8_t *mac_address, IPAddress local_ip);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);
  int maintain();

  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  IPAddress dnsServerIP();

  friend class EthernetClient;
  friend class EthernetServer;
};

extern EthernetClass Ethernet;

#endif
