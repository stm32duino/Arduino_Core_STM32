// DHCP Library v0.3 - April 25, 2009
// Author: Jordan Terrell - blog.jordanterrell.com

#include <string.h>
#include <stdlib.h>
#include "Dhcp.h"
#include "Arduino.h"
#include "utility/util.h"
#include "lwip/dhcp.h"

int DhcpClass::beginWithDHCP(uint8_t *mac, unsigned long timeout, unsigned long responseTimeout)
{
  _dhcpLeaseTime=0;
  _dhcpT1=0;
  _dhcpT2=0;
  _timeout = timeout;
  _responseTimeout = responseTimeout;

  // zero out _dhcpMacAddr
  memset(_dhcpMacAddr, 0, 6);
  reset_DHCP_lease();

  memcpy((void*)_dhcpMacAddr, (void*)mac, 6);
  _dhcp_state = STATE_DHCP_START;
  return request_DHCP_lease();
}

void DhcpClass::reset_DHCP_lease(){
  dhcp_release(&gnetif);
  dhcp_stop(&gnetif);
}

//return:0 on error, 1 if request is sent and response is received
int DhcpClass::request_DHCP_lease(){

  int result = 0;

  unsigned long startTime = millis();
  unsigned long nextTime = startTime;

  if (!netif_is_link_up(&gnetif)) {
    return result;
  }

  while(_dhcp_state != STATE_DHCP_LEASED)
  {
    stm32_eth_scheduler();

    if((millis() - nextTime) >= 500) {
      result = stm32_DHCP_process(&_dhcp_state);
      nextTime = millis();
    }

    if(result != 1 && ((millis() - startTime) > _timeout)) {
      reset_DHCP_lease();
      break;
    }
  }

  _lastCheckLeaseMillis = millis();

  return result;
}

/*
    returns:
    0/DHCP_CHECK_NONE: nothing happened
    1/DHCP_CHECK_RENEW_FAIL: renew failed
    2/DHCP_CHECK_RENEW_OK: renew success
    3/DHCP_CHECK_REBIND_FAIL: rebind fail
    4/DHCP_CHECK_REBIND_OK: rebind success
*/
int DhcpClass::checkLease(){
    int rc = DHCP_CHECK_NONE;

    unsigned long now = millis();
    unsigned long elapsed = now - _lastCheckLeaseMillis;

    // if more then one sec passed, reduce the counters accordingly
    if (elapsed >= 1000) {
        // set the new timestamps
        _lastCheckLeaseMillis = now - (elapsed % 1000);
        elapsed = elapsed / 1000;

        // decrease the counters by elapsed seconds
        // we assume that the cycle time (elapsed) is fairly constant
        // if the remainder is less than cycle time * 2
        // do it early instead of late
        if (_renewInSec < elapsed * 2)
            _renewInSec = 0;
        else
            _renewInSec -= elapsed;

        if (_rebindInSec < elapsed * 2)
            _rebindInSec = 0;
        else
            _rebindInSec -= elapsed;
    }

    // if we have a lease but should renew, do it
    if (_renewInSec == 0 &&_dhcp_state == STATE_DHCP_LEASED) {
        _dhcp_state = STATE_DHCP_REREQUEST;
        rc = 1 + request_DHCP_lease();
    }

    // if we have a lease or is renewing but should bind, do it
    if (_rebindInSec == 0 && (_dhcp_state == STATE_DHCP_LEASED || _dhcp_state == STATE_DHCP_START)) {
        // this should basically restart completely
        _dhcp_state = STATE_DHCP_START;
        reset_DHCP_lease();
        rc = 3 + request_DHCP_lease();
    }
    return rc;
}

IPAddress DhcpClass::getLocalIp()
{
  return IPAddress(stm32_eth_get_ipaddr());
}

IPAddress DhcpClass::getSubnetMask()
{
  return IPAddress(stm32_eth_get_netmaskaddr());
}

IPAddress DhcpClass::getGatewayIp()
{
  return IPAddress(stm32_eth_get_gwaddr());
}

IPAddress DhcpClass::getDhcpServerIp()
{
  return IPAddress(stm32_eth_get_dhcpaddr());
}

IPAddress DhcpClass::getDnsServerIp()
{
  return IPAddress(stm32_eth_get_dnsaddr());
}

void DhcpClass::printByte(char * buf, uint8_t n ) {
  char *str = &buf[1];
  buf[0]='0';
  do {
    unsigned long m = n;
    n /= 16;
    char c = m - 16 * n;
    *str-- = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);
}
