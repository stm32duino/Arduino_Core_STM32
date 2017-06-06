/**
  ******************************************************************************
  * @file    LwIP.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    23-May-2017
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LWIP_H__
#define __LWIP_H__

/* Includes ------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

//Include LwIP source files

#include "api/err.c"

#include "core/ipv4/autoip.c"
#include "core/ipv4/dhcp.c"
#include "core/ipv4/etharp.c"
#include "core/ipv4/icmp.c"
#include "core/ipv4/igmp.c"
#include "core/ipv4/ip4_addr.c"
#include "core/ipv4/ip4_frag.c"
#include "core/ipv4/ip4.c"

#include "core/def.c"
#include "core/dns.c"
#include "core/inet_chksum.c"
#include "core/init.c"
#include "core/ip.c"
#include "core/mem.c"
#include "core/memp.c"
#include "core/netif.c"
#include "core/pbuf.c"
#include "core/raw.c"
#include "core/stats.c"
#include "core/sys.c"
#include "core/tcp_in.c"
#include "core/tcp_out.c"
#include "core/tcp.c"
#include "core/timeouts.c"
#include "core/udp.c"

#include "netif/ethernet.c"

#ifdef __cplusplus
}
#endif

#endif /* __LWIP_H__ */

/****END OF FILE****/
