/**
  ******************************************************************************
  * @file    LwIP.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    24-May-2017
  * @brief   Include LwIP source files
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "stm32_eth.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"
#include "ethernetif.h"
#include "lwip/dhcp.h"
#include "lwip/dns.h"


#ifdef __cplusplus
 extern "C" {
#endif

struct stm32_eth_config {
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;
};

static struct stm32_eth_config gconfig;
struct netif gnetif;

static void Netif_Config(void);

/**
* @brief  Configurates the network interface
* @param  None
* @retval None
*/
static void Netif_Config(void)
{
  /* Add the network interface */
  netif_add(&gnetif, &(gconfig.ipaddr), &(gconfig.netmask), &(gconfig.gw), NULL, &ethernetif_init, &ethernet_input);

  /* Registers the default network interface */
  netif_set_default(&gnetif);

  if (netif_is_link_up(&gnetif))
  {
    /* When the netif is fully configured this function must be called */
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }

  /* Set the link callback function, this function is called on change of link status */
  netif_set_link_callback(&gnetif, ethernetif_update_config);
}


uint32_t message_count = 0;

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{

  /*increment message count */
  message_count++;

  /* Free receive pbuf */
  pbuf_free(p);
}

void stm32_eth_init(uint8_t *mac, uint8_t *ip, uint8_t *gw, uint8_t *netmask)
{
  /* Initialize the LwIP stack */
  lwip_init();

  if(mac != NULL) {
    ethernetif_set_mac_addr(mac);
  } // else default value is used: MAC_ADDR0 ... MAC_ADDR5

  if(ip != NULL) {
    IP_ADDR4(&(gconfig.ipaddr),ip[0],ip[1],ip[2],ip[3]);
  } else {
    #ifdef USE_DHCP
      ip_addr_set_zero_ip4(&(gconfig.ipaddr));
    #else
      IP_ADDR4(&(gconfig.ipaddr),IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
    #endif /* USE_DHCP */
  }

  if(gw != NULL) {
    IP_ADDR4(&(gconfig.gw),gw[0],gw[1],gw[2],gw[3]);
  } else {
    #ifdef USE_DHCP
      ip_addr_set_zero_ip4(&(gconfig.gw));
    #else
      IP_ADDR4(&(gconfig.gw),GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
    #endif /* USE_DHCP */
  }

  if(netmask != NULL) {
    IP_ADDR4(&(gconfig.netmask),netmask[0],netmask[1],netmask[2],netmask[3]);
  } else {
    #ifdef USE_DHCP
      ip_addr_set_zero_ip4(&(gconfig.netmask));
    #else
      IP_ADDR4(&(gconfig.netmask),NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
    #endif /* USE_DHCP */
  }

  /* Configure the Network interface */
  Netif_Config();

//TODO: juste temporaire pour debug
  User_notification(&gnetif);
}

/**
  * @brief  This function must be called in main loop in standalone mode.
  * @param  None
  * @retval None
  */
void stm32_eth_scheduler(void) {
  /* Read a received packet from the Ethernet buffers and send it
  to the lwIP for handling */
  ethernetif_input(&gnetif);

  /* Handle LwIP timeouts */
  sys_check_timeouts();
}


uint8_t stm32_DHCP_process(uint8_t *DHCP_state) {
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;
  struct dhcp *dhcp;

  uint8_t result = 0;

  if(netif_is_link_up(&gnetif)){
    switch (*DHCP_state)
    {
      case DHCP_START:
      {
        ip_addr_set_zero_ip4(&(gnetif.ip_addr));
        ip_addr_set_zero_ip4(&(gnetif.netmask));
        ip_addr_set_zero_ip4(&(gnetif.gw));
        *DHCP_state = DHCP_WAIT_ADDRESS;
        dhcp_start(&gnetif);
      }
      break;

    case DHCP_WAIT_ADDRESS:
      {
        if (dhcp_supplied_address(&gnetif))
        {
          *DHCP_state = DHCP_ADDRESS_ASSIGNED;
          result = 1;
        }
        else
        {
          dhcp = (struct dhcp *)netif_get_client_data(&gnetif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

          /* DHCP timeout */
          if (dhcp->tries > MAX_DHCP_TRIES)
          {
            *DHCP_state = DHCP_TIMEOUT;
          }
        }
      }
      break;
    case DHCP_TIMEOUT:
      {
        /* Stop DHCP */
        dhcp_stop(&gnetif);
        *DHCP_state = DHCP_OFF;
      }
      break;
    case DHCP_LINK_DOWN:
      {
        /* Stop DHCP */
        dhcp_stop(&gnetif);
        *DHCP_state = DHCP_OFF;
      }
      break;
    default: break;
    }
  }

  return result;
}

uint32_t stm32_eth_get_ipaddr(void) {
  return ip4_addr_get_u32(&(gnetif.ip_addr));
}

uint32_t stm32_eth_get_gwaddr(void) {
  return ip4_addr_get_u32(&(gnetif.gw));
}

uint32_t stm32_eth_get_netmaskaddr(void) {
  return ip4_addr_get_u32(&(gnetif.netmask));
}

uint32_t stm32_eth_get_dnsaddr(void) {
  ip_addr_t *tmp = dns_getserver(0);
  return ip4_addr_get_u32(tmp);
}

uint32_t stm32_eth_get_dhcpaddr(void) {
  struct dhcp *dhcp = (struct dhcp *)netif_get_client_data(&gnetif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);
  return ip4_addr_get_u32(&(dhcp->server_ip_addr));
}

/**
  * @brief  This function notify user about link status changement.
  * @param  netif: the network interface
  * @retval None
  */
void ethernetif_notify_conn_changed(struct netif *netif)
{
//   #ifndef USE_DHCP
//   ip_addr_t ipaddr;
//   ip_addr_t netmask;
//   ip_addr_t gw;
// #endif

  if(netif_is_link_up(netif))
  {
    printf("ethernetif_notify_conn_changed: The network cable is now connected \n");

// #ifdef USE_DHCP
//     /* Update DHCP state machine */
//     DHCP_state = DHCP_START;
// #else
//     IP_ADDR4(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
//     IP_ADDR4(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
//     IP_ADDR4(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
//
//     netif_set_addr(netif, &ipaddr , &netmask, &gw);
//
// #ifdef USE_LCD
//     uint8_t iptxt[20];
//     sprintf((char *)iptxt, "%s", ip4addr_ntoa((const ip4_addr_t *)&netif->ip_addr));
//     printf ("Static IP address: %s\n", iptxt);
// #endif
// #endif /* USE_DHCP */

    /* When the netif is fully configured this function must be called.*/
    netif_set_up(netif);
  }
  else
  {
// #ifdef USE_DHCP
//     /* Update DHCP state machine */
//     DHCP_state = DHCP_LINK_DOWN;
// #endif /* USE_DHCP */

    /*  When the netif link is down this function must be called.*/
    netif_set_down(netif);

    printf ("ethernetif_notify_conn_changed: The network cable is not connected \n");
  }
}

/**
  * @brief  Notify the User about the nework interface config status
  * @param  netif: the network interface
  * @retval None
  */
void User_notification(struct netif *netif)
{
  if (netif_is_up(netif))
  {
    printf("User_notification: Waiting for DHCP lease \n");
  }
  else
  {
    printf("User_notification: The network cable is not connected \n");
  }
}

#ifdef __cplusplus
}
#endif
