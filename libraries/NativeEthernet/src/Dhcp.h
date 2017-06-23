// DHCP Library v0.3 - April 25, 2009
// Author: Jordan Terrell - blog.jordanterrell.com

#ifndef Dhcp_h
#define Dhcp_h

#include "EthernetUdp.h"

/* DHCP state machine. */
#define STATE_DHCP_STOP				DHCP_OFF
#define STATE_DHCP_START 			DHCP_START
#define	STATE_DHCP_DISCOVER		DHCP_WAIT_ADDRESS
#define	STATE_DHCP_REQUEST		0
#define	STATE_DHCP_LEASED			DHCP_ADDRESS_ASSIGNED
#define	STATE_DHCP_REREQUEST	0
#define	STATE_DHCP_RELEASE		DHCP_ASK_RELEASE

#define DHCP_CHECK_NONE         (0)
#define DHCP_CHECK_RENEW_FAIL   (1)
#define DHCP_CHECK_RENEW_OK     (2)
#define DHCP_CHECK_REBIND_FAIL  (3)
#define DHCP_CHECK_REBIND_OK    (4)

class DhcpClass {
private:
  uint8_t  _dhcpMacAddr[6];
  unsigned long _timeout;
	uint8_t _dhcp_lease_state;
  uint8_t _dhcp_state;

  int request_DHCP_lease();
  void reset_DHCP_lease();

public:
  IPAddress getLocalIp();
  IPAddress getSubnetMask();
  IPAddress getGatewayIp();
  IPAddress getDhcpServerIp();
  IPAddress getDnsServerIp();

  int beginWithDHCP(uint8_t *, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);
  int checkLease();
};

#endif
