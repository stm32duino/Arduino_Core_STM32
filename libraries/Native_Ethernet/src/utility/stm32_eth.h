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

#ifndef __STM32_ETH_H__
#define __STM32_ETH_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "lwip/ip_addr.h"
#include "lwip/dhcp.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

/* Exported types ------------------------------------------------------------*/
/* TCP connection state */
typedef enum
{
  TCP_NONE = 0,
  TCP_CONNECTED,
  TCP_RECEIVED,
  TCP_SENT,
  TCP_ACCEPTED,
  TCP_CLOSING,
}tcp_client_states;

/* Struct to store received data */
struct pbuf_data {
  struct pbuf *p;     // the packet buffer that was received
  uint16_t available; // number of data
};

/* UDP structure */
struct udp_struct {
  struct udp_pcb *pcb; /* pointer on the current udp_pcb */
  struct pbuf_data data;
  ip_addr_t ip;       // the remote IP address from which the packet was received
  u16_t port;         // the remote port from which the packet was received
};

/* TCP structure */
struct tcp_struct {
  struct tcp_pcb *pcb;          /* pointer on the current tcp_pcb */
  struct pbuf_data data;
  tcp_client_states state;      /* current connection state */
};

/* Exported constants --------------------------------------------------------*/
/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0   (uint8_t) 192
#define IP_ADDR1   (uint8_t) 168
#define IP_ADDR2   (uint8_t) 0
#define IP_ADDR3   (uint8_t) 10

/*NETMASK*/
#define NETMASK_ADDR0   (uint8_t) 255
#define NETMASK_ADDR1   (uint8_t) 255
#define NETMASK_ADDR2   (uint8_t) 255
#define NETMASK_ADDR3   (uint8_t) 0

/*Gateway Address*/
#define GW_ADDR0   (uint8_t) 192
#define GW_ADDR1   (uint8_t) 168
#define GW_ADDR2   (uint8_t) 0
#define GW_ADDR3   (uint8_t) 1

/* DHCP process states */
#define DHCP_OFF                   (uint8_t) 0
#define DHCP_START                 (uint8_t) 1
#define DHCP_WAIT_ADDRESS          (uint8_t) 2
#define DHCP_ADDRESS_ASSIGNED      (uint8_t) 3
#define DHCP_TIMEOUT               (uint8_t) 4
#define DHCP_LINK_DOWN             (uint8_t) 5
#define DHCP_ASK_RELEASE           (uint8_t) 6

/* Maximum number of client per server */
#define MAX_CLIENT  32

#ifdef ETH_INPUT_USE_IT
extern struct netif gnetif;
#endif


/* Exported functions ------------------------------------------------------- */
void stm32_eth_init(const uint8_t *mac, const uint8_t *ip, const uint8_t *gw, const uint8_t *netmask);
void stm32_eth_scheduler(void);

void User_notification(struct netif *netif);

void stm32_DHCP_Process(struct netif *netif);
void stm32_DHCP_Periodic_Handle(struct netif *netif);
void stm32_DHCP_manual_config(void);
uint8_t stm32_get_DHCP_lease_state(void);
void stm32_set_DHCP_state(uint8_t state);
uint8_t stm32_get_DHCP_state(void);
uint8_t stm32_dhcp_started(void);

void stm32_dns_init(const uint8_t *dnsaddr);
int8_t stm32_dns_gethostbyname(const char *hostname, uint32_t *ipaddr);

void udp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                          const ip_addr_t *addr, u16_t port);

uint32_t stm32_eth_get_ipaddr(void);
uint32_t stm32_eth_get_gwaddr(void);
uint32_t stm32_eth_get_netmaskaddr(void);
uint32_t stm32_eth_get_dnsaddr(void);
uint32_t stm32_eth_get_dhcpaddr(void);

struct pbuf *stm32_new_data(struct pbuf *p, const uint8_t *buffer, size_t size);
struct pbuf *stm32_free_data(struct pbuf *p);
uint16_t stm32_get_data(struct pbuf_data *data, uint8_t *buffer, size_t size);

ip_addr_t *u8_to_ip_addr(uint8_t *ipu8, ip_addr_t *ipaddr);
uint32_t ip_addr_to_u32(ip_addr_t *ipaddr);

err_t tcp_connected_callback(void *arg, struct tcp_pcb *tpcb, err_t err);
err_t tcp_accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err);

#ifdef __cplusplus
}
#endif

#endif /* __STM32_ETH_H__ */
