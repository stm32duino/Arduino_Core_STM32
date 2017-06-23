// DHCP Library v0.3 - April 25, 2009
// Author: Jordan Terrell - blog.jordanterrell.com

#include <string.h>
#include <stdlib.h>
#include "Dhcp.h"
#include "Arduino.h"
#include "utility/stm32_eth.h"

int DhcpClass::beginWithDHCP(uint8_t *mac, unsigned long timeout, unsigned long responseTimeout)
{
  UNUSED(responseTimeout);
  _timeout = timeout;
  _dhcp_lease_state = DHCP_CHECK_NONE;

  // zero out _dhcpMacAddr
  memset(_dhcpMacAddr, 0, 6);
  reset_DHCP_lease();

  memcpy((void*)_dhcpMacAddr, (void*)mac, 6);
  _dhcp_state = STATE_DHCP_START;
  stm32_set_DHCP_state(_dhcp_state);
  return request_DHCP_lease();
}

void DhcpClass::reset_DHCP_lease(){
  _dhcp_state = STATE_DHCP_RELEASE;
  stm32_set_DHCP_state(_dhcp_state);
  stm32_eth_scheduler();
  _dhcp_state = stm32_get_DHCP_state();
}

//return:0 on error, 1 if request is sent and response is received
int DhcpClass::request_DHCP_lease(){

  int result = 0;
  unsigned long startTime = millis();

  while(_dhcp_state != STATE_DHCP_LEASED)
  {
    stm32_eth_scheduler();
    _dhcp_state = stm32_get_DHCP_state();

    if(result != 1 && ((millis() - startTime) > _timeout)) {
      reset_DHCP_lease();
      break;
    }
  }

  if(_dhcp_state == STATE_DHCP_LEASED) {
    result = 1;
  }

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

    stm32_eth_scheduler();
    rc = stm32_get_DHCP_lease_state();

    if(rc != _dhcp_lease_state)
    {
      switch(_dhcp_lease_state) {
        case DHCP_CHECK_NONE:
          _dhcp_lease_state = rc;
          rc = DHCP_CHECK_NONE;
        break;

        case DHCP_CHECK_RENEW_OK:
          _dhcp_lease_state = rc;
          if(rc == DHCP_CHECK_NONE) {
            rc = DHCP_CHECK_RENEW_OK;
          } else {
            rc = DHCP_CHECK_RENEW_FAIL;
          }
        break;

        case DHCP_CHECK_REBIND_OK:
          _dhcp_lease_state = rc;
          if(rc == DHCP_CHECK_NONE) {
            rc = DHCP_CHECK_REBIND_OK;
          } else {
            rc = DHCP_CHECK_REBIND_FAIL;
          }
        break;

        default:
          _dhcp_lease_state = DHCP_CHECK_NONE;
        break;
      }
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
