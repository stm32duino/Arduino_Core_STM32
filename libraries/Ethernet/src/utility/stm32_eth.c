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
#include "lwip/prot/dhcp.h"
#include "lwip/dns.h"


#ifdef __cplusplus
 extern "C" {
#endif

#define TIME_CHECK_ETH_LINK_STATE 500U  //Check ethernet link status every seconds

#define TIMEOUT_DNS_REQUEST 10000U

#define MAX_DHCP_TRIES  4
uint32_t DHCPfineTimer = 0;
__IO uint8_t DHCP_state = DHCP_OFF;
static uint8_t DHCP_Started_by_user = 0;

struct stm32_eth_config {
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;
};

static struct stm32_eth_config gconfig;
struct netif gnetif;

static uint32_t gEhtLinkTickStart = 0;

/*************************** Function prototype *******************************/
static void Netif_Config(void);
static void tcp_connection_close(struct tcp_pcb *tpcb, struct tcp_struct *tcp);
static err_t tcp_recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static err_t tcp_sent_callback(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void tcp_err_callback(void *arg, err_t err);


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

void stm32_eth_init(const uint8_t *mac, const uint8_t *ip, const uint8_t *gw, const uint8_t *netmask)
{
  /* Initialize the LwIP stack */
  lwip_init();

  if(mac != NULL) {
    ethernetif_set_mac_addr(mac);
  } // else default value is used: MAC_ADDR0 ... MAC_ADDR5

  if(ip != NULL) {
    IP_ADDR4(&(gconfig.ipaddr),ip[0],ip[1],ip[2],ip[3]);
  } else {
    #ifdef LWIP_DHCP
      ip_addr_set_zero_ip4(&(gconfig.ipaddr));
    #else
      IP_ADDR4(&(gconfig.ipaddr),IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
    #endif /* LWIP_DHCP */
  }

  if(gw != NULL) {
    IP_ADDR4(&(gconfig.gw),gw[0],gw[1],gw[2],gw[3]);
  } else {
    #ifdef LWIP_DHCP
      ip_addr_set_zero_ip4(&(gconfig.gw));
    #else
      IP_ADDR4(&(gconfig.gw),GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
    #endif /* LWIP_DHCP */
  }

  if(netmask != NULL) {
    IP_ADDR4(&(gconfig.netmask),netmask[0],netmask[1],netmask[2],netmask[3]);
  } else {
    #ifdef LWIP_DHCP
      ip_addr_set_zero_ip4(&(gconfig.netmask));
    #else
      IP_ADDR4(&(gconfig.netmask),NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
    #endif /* LWIP_DHCP */
  }

  /* Configure the Network interface */
  Netif_Config();

//TODO: juste temporaire pour debug: laisser à l'utilisateur la possibilité de l'utiliser
  User_notification(&gnetif);

  stm32_eth_scheduler();
}

/**
  * @brief  This function must be called in main loop in standalone mode.
  * @param  None
  * @retval None
  */
void stm32_eth_scheduler(void) {
  /* Read a received packet from the Ethernet buffers and send it
  to the lwIP for handling */
#ifndef ETH_INPUT_USE_IT
  ethernetif_input(&gnetif);
#endif /* ETH_INPUT_USE_IT */

  /* Check ethernet link status */
  if((HAL_GetTick() - gEhtLinkTickStart) >= TIME_CHECK_ETH_LINK_STATE) {
    ethernetif_set_link(&gnetif);
    gEhtLinkTickStart = HAL_GetTick();
  }

  /* Handle LwIP timeouts */
  sys_check_timeouts();

  stm32_DHCP_Periodic_Handle(&gnetif);
}


uint8_t stm32_dhcp_started(void) {
  return DHCP_Started_by_user;
}

/**
  * @brief  DHCP_Process_Handle
  * @param  None
  * @retval None
  */
void stm32_DHCP_process(struct netif *netif) {
  struct dhcp *dhcp;

  if(netif_is_link_up(netif)){
    switch (DHCP_state)
    {
    case DHCP_START:
      {
        ip_addr_set_zero_ip4(&netif->ip_addr);
        ip_addr_set_zero_ip4(&netif->netmask);
        ip_addr_set_zero_ip4(&netif->gw);
        DHCP_state = DHCP_WAIT_ADDRESS;
        dhcp_start(netif);
        DHCP_Started_by_user = 1;
      }
      break;

    case DHCP_WAIT_ADDRESS:
      {
        if (dhcp_supplied_address(netif))
        {
          DHCP_state = DHCP_ADDRESS_ASSIGNED;
        }
        else
        {
          dhcp = (struct dhcp *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

          /* DHCP timeout */
          if (dhcp->tries > MAX_DHCP_TRIES)
          {
            DHCP_state = DHCP_TIMEOUT;

            // If DHCP address not bind, keep DHCP stopped
            DHCP_Started_by_user = 0;

            /* Stop DHCP */
            dhcp_stop(netif);
          }
        }
      }
      break;
    case DHCP_ASK_RELEASE:
      {
        /* Force release */
        dhcp_release(netif);
        dhcp_stop(netif);
        DHCP_state = DHCP_OFF;
      }
      break;
    case DHCP_LINK_DOWN:
      {
        /* Stop DHCP */
        dhcp_stop(netif);
        DHCP_state = DHCP_OFF;
      }
      break;
    default: break;
    }
  } else {
    DHCP_state = DHCP_OFF;
  }
}

/**
  * @brief  DHCP periodic check
  * @param  localtime the current LocalTime value
  * @retval None
  */
void stm32_DHCP_Periodic_Handle(struct netif *netif)
{
  /* Fine DHCP periodic process every 500ms */
  if (HAL_GetTick() - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
  {
    DHCPfineTimer =  HAL_GetTick();
    /* process DHCP state machine */
    stm32_DHCP_process(netif);
  }
}

void stm32_DHCP_manual_config(void) {
  dhcp_inform(&gnetif);
}

uint8_t stm32_get_DHCP_lease_state(void) {
  uint8_t res = 0;
  struct dhcp* dhcp = (struct dhcp *)netif_get_client_data(&gnetif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

  if(dhcp->state == DHCP_STATE_RENEWING) {
    res = 2;
  } else if(dhcp->state == DHCP_STATE_REBINDING) {
    res = 4;
  }

  return res;
}

void stm32_set_DHCP_state(uint8_t state) {
  DHCP_state = state;
}

uint8_t stm32_get_DHCP_state(void) {
  return DHCP_state;
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
  const ip_addr_t *tmp = dns_getserver(0);
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

    if(DHCP_Started_by_user == 1) {
      DHCP_state = DHCP_START;
    }

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
    if(DHCP_Started_by_user == 1) {
      /* Update DHCP state machine */
      DHCP_state = DHCP_LINK_DOWN;
    }

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
    if(DHCP_Started_by_user == 1) {
      /* Update DHCP state machine */
      DHCP_state = DHCP_LINK_DOWN;
    }
  }
}

void stm32_dns_init(const uint8_t *dnsaddr)
{
  ip_addr_t ip;

  /* DNS initialized by DHCP when call dhcp_start() */
  if(!stm32_dhcp_started()) {
    dns_init();
    IP_ADDR4(&ip,dnsaddr[0],dnsaddr[1],dnsaddr[2],dnsaddr[3]);
    dns_setserver(0, &ip);
  }
}

void dns_callback(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
  UNUSED(name);

  if(ipaddr != NULL) {
    *((uint32_t *)callback_arg) = ip4_addr_get_u32(ipaddr);
  } else {
    *((uint32_t *)callback_arg) = 0;
  }
}

int8_t stm32_dns_gethostbyname(const char *hostname, uint32_t *ipaddr)
{
  ip_addr_t iphost;
  err_t err;
  uint32_t tickstart = 0;
  int8_t ret = 0;

  *ipaddr = 0;
  err = dns_gethostbyname(hostname, &iphost, &dns_callback, ipaddr);

  switch(err) {
    case ERR_OK:
      *ipaddr = ip4_addr_get_u32(&iphost);
      ret = 1;
    break;

    case ERR_INPROGRESS:
      tickstart = HAL_GetTick();
      while(*ipaddr == 0) {
        stm32_eth_scheduler();
        if((HAL_GetTick() - tickstart) >= TIMEOUT_DNS_REQUEST) {
          ret = -1;
          break;
        }
      }

      if(ret == 0) {
        if(*ipaddr == 0) {
          ret = -2;
        } else {
          ret = 1;
        }
      }
    break;

    case ERR_ARG:
      ret = -4;
    break;

    default:
      ret = -4;
    break;
  }

  return ret;
}

ip_addr_t *u8_to_ip_addr(uint8_t *ipu8, ip_addr_t *ipaddr)
{
  IP_ADDR4(ipaddr,ipu8[0],ipu8[1],ipu8[2],ipu8[3]);
  return ipaddr;
}

uint32_t ip_addr_to_u32(ip_addr_t *ipaddr)
{
  return ip4_addr_get_u32(ipaddr);
}

struct pbuf *stm32_new_data(struct pbuf *p, const uint8_t *buffer, size_t size)
{
  // Allocate memory if pbuf doesn't exit yet.
  if(p == NULL) {
    p = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);

    if(p != NULL) {
      // Copy data inside pbuf
      if(ERR_OK == pbuf_take(p, (uint8_t *)buffer, size)) {
        return p;
      } else {
        pbuf_free(p);
      }
    }
  }
  // If pbuf allocated, grow the size of pbuf and add new data
  // NOTE: pbuf_realloc can't be used to grow the size of pbuf
  else {
    struct pbuf *q = pbuf_alloc(PBUF_TRANSPORT, size + p->tot_len, PBUF_RAM);

    if(q != NULL) {
      if(ERR_OK == pbuf_copy(q, p)) {
        err_t err = pbuf_take_at(q, (uint8_t *)buffer, size, p->tot_len);
        if(ERR_OK == /*pbuf_take_at(q, (uint8_t *)buffer, size, p->tot_len)*/err) {
          pbuf_free(p);
          p = q;
          return p;
        } else {
        }
      }

      pbuf_free(q);
    }
  }

  return 0;
}

struct pbuf *stm32_free_data(struct pbuf *p)
{
  uint16_t n = pbuf_free(p);

  if(n != 0) {
    p = NULL;
  }

  return p;
}

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param p the udp_pcb which received data
  * @param data the buffer where write the data read
  * @param size the number of data to read
  * @param available the number of data not read
  * @retval number of data read
  */
uint16_t stm32_get_data(struct pbuf *p, uint8_t *data, size_t size, uint16_t available)
{
  uint16_t i;
  uint16_t offset;
  uint16_t nb;

  if((p == NULL) || (data == NULL) || (size == 0) || (available == 0) || (available > p->tot_len)) {
    return 0;
  }

  offset = p->tot_len - available;
  nb = 0;

  for(i = 0; (i < size) && ((offset + i) < p->tot_len); i++) {
    data[i] = pbuf_get_at(p, offset + i);
    nb++;
  }

  return nb;
}

uint16_t stm32_data_available(struct pbuf *p)
{
  if(p == NULL) {
    return 0;
  }

  return p->tot_len;
}

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void udp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                          const ip_addr_t *addr, u16_t port)
{
  struct udp_struct *udp_arg = (struct udp_struct *)arg;

  /* Send data to the application layer */
  if((udp_arg != NULL) && (udp_arg->pcb == pcb)) {
    // Free the old p buffer

    //TODO: chain new data to the oldest?
    if(udp_arg->p != NULL) {
      pbuf_free(udp_arg->p);
    }
    udp_arg->p = p;
    udp_arg->available = p->tot_len;
    ip_addr_copy(udp_arg->ip, *addr);
    udp_arg->port = port;
  } else {
    pbuf_free(p);
  }
}

/**
  * @brief Function called when TCP connection established
  * @param tpcb: pointer on the connection contol block
  * @param err: when connection correctly established err should be ERR_OK
  * @retval err_t: returned error
  */
err_t tcp_connected_callback(void *arg, struct tcp_pcb *tpcb, err_t err)
{
  struct tcp_struct *tcp_arg = (struct tcp_struct *)arg;

  if (err == ERR_OK)
  {
    if ((tcp_arg != NULL) && (tcp_arg->pcb == tpcb))
    {
      tcp_arg->state = TCP_CONNECTED;

      /* initialize LwIP tcp_recv callback function */
      tcp_recv(tpcb, tcp_recv_callback);

      /* initialize LwIP tcp_sent callback function */
      tcp_sent(tpcb, tcp_sent_callback);

      /* initialize LwIP tcp_poll callback function */
      // tcp_poll(tpcb, tcp_poll_callback, 1);

      /* initialize LwIP tcp_err callback function */
      tcp_err(tpcb, tcp_err_callback);

      return ERR_OK;
    }
    else
    {
      /* close connection */
      tcp_connection_close(tpcb, tcp_arg);

      return ERR_ARG;
    }
  }
  else
  {
    /* close connection */
    tcp_connection_close(tpcb, tcp_arg);
  }
  return err;
}

/**
  * @brief  This function is the implementation of tcp_accept LwIP callback
  * @param  arg: not used
  * @param  newpcb: pointer on tcp_pcb struct for the newly created tcp connection
  * @param  err: not used
  * @retval err_t: error status
  */
err_t tcp_accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;
  struct tcp_struct *tcp_arg = (struct tcp_struct *)arg;

  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);

  /* set priority for the newly accepted tcp connection newpcb */
  tcp_setprio(newpcb, TCP_PRIO_MIN);

  if (es != NULL)
  {
    es->state = ES_ACCEPTED;
    es->pcb = newpcb;
    es->retries = 0;
    es->p = NULL;

    /* pass newly allocated es structure as argument to newpcb */
    tcp_arg(newpcb, es);

    /* initialize lwip tcp_recv callback function for newpcb  */
    tcp_recv(newpcb, tcp_echoserver_recv);

    /* initialize lwip tcp_err callback function for newpcb  */
    tcp_err(newpcb, tcp_echoserver_error);

    /* initialize lwip tcp_poll callback function for newpcb */
    tcp_poll(newpcb, tcp_echoserver_poll, 0);

    ret_err = ERR_OK;
  }
  else
  {
    /*  close tcp connection */
    tcp_echoserver_connection_close(newpcb, es);
    /* return memory error */
    ret_err = ERR_MEM;
  }
  return ret_err;
}

/**
  * @brief tcp_receiv callback
  * @param arg: argument to be passed to receive callback
  * @param tpcb: tcp connection control block
  * @param err: receive error code
  * @retval err_t: retuned error
  */
static err_t tcp_recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  struct tcp_struct *tcp_arg = (struct tcp_struct *)arg;
  err_t ret_err;

  /* if we receive an empty tcp frame from server => close connection */
  if (p == NULL)
  {
    /* we're done sending, close connection */
    tcp_connection_close(tpcb, tcp_arg);
    ret_err = ERR_OK;
  }
  /* else : a non empty frame was received from echo server but for some reason err != ERR_OK */
  else if(err != ERR_OK)
  {
    /* free received pbuf*/
    if (p != NULL)
    {
      pbuf_free(p);
    }
    ret_err = err;
  }
  else if(tcp_arg->state == TCP_CONNECTED)
  {
    /* Acknowledge data reception */
    tcp_recved(tpcb, p->tot_len);

    if(tcp_arg->p == NULL) {
      tcp_arg->p = p;
    } else {
      pbuf_chain(tcp_arg->p, p); //TODO: not validated!!!!!
    }

    tcp_arg->available += p->len;
    ret_err = ERR_OK;
  }
  /* data received when connection already closed */
  else
  {
    /* Acknowledge data reception */
    tcp_recved(tpcb, p->tot_len);

    /* free pbuf and do nothing */
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
}

/**
  * @brief  This function implements the tcp_poll callback function
  * @param  arg: pointer on argument passed to callback
  * @param  tpcb: tcp connection control block
  * @retval err_t: error code
  */
// static err_t tcp_poll_callback(void *arg, struct tcp_pcb *tpcb)
// {
//   err_t ret_err;
//   struct echoclient *es;
//
//   es = (struct echoclient*)arg;
//   if (es != NULL)
//   {
//     if (es->p_tx != NULL)
//     {
//       /* there is a remaining pbuf (chain) , try to send data */
//       tcp_echoclient_send(tpcb, es);
//     }
//     else
//     {
//       /* no remaining pbuf (chain)  */
//       if(es->state == ES_CLOSING)
//       {
//         /* close tcp connection */
//         tcp_connection_close(tpcb, es);
//       }
//     }
//     ret_err = ERR_OK;
//   }
//   else
//   {
//     /* nothing to be done */
//     tcp_abort(tpcb);
//     ret_err = ERR_ABRT;
//   }
//   return ret_err;
// }

/**
  * @brief  This function implements the tcp_sent LwIP callback (called when ACK
  *         is received from remote host for sent data)
  * @param  arg: pointer on argument passed to callback
  * @param  tcp_pcb: tcp connection control block
  * @param  len: length of data sent
  * @retval err_t: returned error code
  */
static err_t tcp_sent_callback(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  struct tcp_struct *tcp_arg = (struct tcp_struct *)arg;

  LWIP_UNUSED_ARG(len);

  if((tcp_arg != NULL) && (tcp_arg->pcb == tpcb))
  {
    /* still got pbufs to send */
    tcp_arg->state = TCP_SENT;
    return ERR_OK;
  }

  return ERR_ARG;
}

/** Function prototype for tcp error callback functions. Called when the pcb
 * receives a RST or is unexpectedly closed for any other reason.
 *
 * @note The corresponding pcb is already freed when this callback is called!
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param err Error code to indicate why the pcb has been closed
 *            ERR_ABRT: aborted through tcp_abort or by a TCP timer
 *            ERR_RST: the connection was reset by the remote host
 */
static void tcp_err_callback(void *arg, err_t err)
{
  struct tcp_struct *tcp_arg = (struct tcp_struct *)arg;

  if(tcp_arg != NULL) {
    if(ERR_OK != err) {
      tcp_arg->pcb = NULL;
      tcp_arg->state = TCP_CLOSING;
    }
  }
}

/**
  * @brief This function is used to close the tcp connection with server
  * @param tpcb: tcp connection control block
  * @param es: pointer on echoclient structure
  * @retval None
  */
static void tcp_connection_close(struct tcp_pcb *tpcb, struct tcp_struct *tcp)
{
  /* remove callbacks */
  tcp_recv(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_poll(tpcb, NULL,0);
  tcp_err(tpcb, NULL);
  tcp_accept(tpcb, NULL);

  /* close tcp connection */
  tcp_close(tpcb);

  tcp->pcb = NULL;
  tcp->state = TCP_CLOSING;
}

#ifdef __cplusplus
}
#endif
