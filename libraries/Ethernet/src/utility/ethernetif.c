/**
  ******************************************************************************
  * @file    LwIP/LwIP_HTTP_Server_Raw/Src/ethernetif.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    17-February-2017
  * @brief   This file implements Ethernet network interface drivers for lwIP
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "lwip/timeouts.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include <string.h>
#include "PeripheralPins.h"
#include "LwIP.h"
#include "stm32_eth.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Network interface name */
#define IFNAME0 's'
#define IFNAME1 't'

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB] __ALIGN_END;/* Ethernet Rx MA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __ALIGN_END;/* Ethernet Tx DMA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE] __ALIGN_END; /* Ethernet Receive Buffer */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE] __ALIGN_END; /* Ethernet Transmit Buffer */

static ETH_HandleTypeDef EthHandle;

static uint8_t macaddress[6]= { MAC_ADDR0, MAC_ADDR1, MAC_ADDR2, MAC_ADDR3, MAC_ADDR4, MAC_ADDR5 };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
                       Ethernet MSP Routines
*******************************************************************************/
/**
  * @brief  Initializes the ETH MSP.
  * @param  heth: ETH handle
  * @retval None
  */
void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  const PinMap* map = PinMap_Ethernet;
  PinName pin = pin_pinName(map);
  GPIO_TypeDef* port = NULL;

  UNUSED(heth);

/* Ethernet pins configuration ************************************************/

  if(map != NULL) {
    while(pin != NC) {
      /* Set port clock */
      port = set_GPIO_Port_Clock(STM_PORT(pin));

      /* pin configuration */
      GPIO_InitStructure.Pin       = STM_GPIO_PIN(pin);
      GPIO_InitStructure.Mode      = STM_PIN_MODE(pinmap_function(pin, PinMap_Ethernet));
      GPIO_InitStructure.Pull      = STM_PIN_PUPD(pinmap_function(pin, PinMap_Ethernet));
      GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_HIGH;
      GPIO_InitStructure.Alternate = STM_PIN_AFNUM(pinmap_function(pin, PinMap_Ethernet));
      HAL_GPIO_Init(port, &GPIO_InitStructure);

      pin = pin_pinName(++map);
    }
  }

#ifdef ETH_INPUT_USE_IT
  /* Enable the Ethernet global Interrupt */
  HAL_NVIC_SetPriority(ETH_IRQn, 0x7, 0);
  HAL_NVIC_EnableIRQ(ETH_IRQn);
#endif /* ETH_INPUT_USE_IT */

  /* Enable ETHERNET clock  */
  __HAL_RCC_ETH_CLK_ENABLE();
}

/*******************************************************************************
                       LL Driver Interface ( LwIP stack --> ETH)
*******************************************************************************/
/**
  * @brief In this function, the hardware should be initialized.
  * Called from ethernetif_init().
  *
  * @param netif the already initialized lwip network interface structure
  *        for this ethernetif
  */
static void low_level_init(struct netif *netif)
{
  uint32_t regvalue = 0;

  EthHandle.Instance = ETH;
  EthHandle.Init.MACAddr = macaddress;
  EthHandle.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
  EthHandle.Init.Speed = ETH_SPEED_100M;
  EthHandle.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
  EthHandle.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
#ifdef ETH_INPUT_USE_IT
  EthHandle.Init.RxMode = ETH_RXINTERRUPT_MODE;
#else
  EthHandle.Init.RxMode = ETH_RXPOLLING_MODE;
#endif /* ETH_INPUT_USE_IT */
  EthHandle.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
  EthHandle.Init.PhyAddress = LAN8742A_PHY_ADDRESS;

  /* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
  if (HAL_ETH_Init(&EthHandle) == HAL_OK)
  {
    /* Set netif link flag */
    netif->flags |= NETIF_FLAG_LINK_UP;
  }

  /* Initialize Tx Descriptors list: Chain Mode */
  HAL_ETH_DMATxDescListInit(&EthHandle, DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);

  /* Initialize Rx Descriptors list: Chain Mode  */
  HAL_ETH_DMARxDescListInit(&EthHandle, DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

  /* set MAC hardware address length */
  netif->hwaddr_len = ETH_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] =  macaddress[0];
  netif->hwaddr[1] =  macaddress[1];
  netif->hwaddr[2] =  macaddress[2];
  netif->hwaddr[3] =  macaddress[3];
  netif->hwaddr[4] =  macaddress[4];
  netif->hwaddr[5] =  macaddress[5];

  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

  /* Enable MAC and DMA transmission and reception */
  HAL_ETH_Start(&EthHandle);

  /**** Configure PHY to generate an interrupt when Eth Link state changes ****/
  /* Read Register Configuration */
  HAL_ETH_ReadPHYRegister(&EthHandle, PHY_IMR, &regvalue);

  regvalue |= PHY_ISFR_INT4;

  /* Enable Interrupt on change of link status */
  HAL_ETH_WritePHYRegister(&EthHandle, PHY_IMR, regvalue );
}

/**
  * @brief This function should do the actual transmission of the packet. The packet is
  * contained in the pbuf that is passed to the function. This pbuf
  * might be chained.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
  * @return ERR_OK if the packet could be sent
  *         an err_t value if the packet couldn't be sent
  *
  * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
  *       strange results. You might consider waiting for space in the DMA queue
  *       to become availale since the stack doesn't retry to send a packet
  *       dropped because of memory failure (except for the TCP timers).
  */
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
  err_t errval;
  struct pbuf *q;
  uint8_t *buffer = (uint8_t *)(EthHandle.TxDesc->Buffer1Addr);
  __IO ETH_DMADescTypeDef *DmaTxDesc;
  uint32_t framelength = 0;
  uint32_t bufferoffset = 0;
  uint32_t byteslefttocopy = 0;
  uint32_t payloadoffset = 0;

  UNUSED(netif);

  DmaTxDesc = EthHandle.TxDesc;
  bufferoffset = 0;

  /* copy frame from pbufs to driver buffers */
  for(q = p; q != NULL; q = q->next)
  {
    /* Is this buffer available? If not, goto error */
    if((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
    {
      errval = ERR_USE;
      goto error;
    }

    /* Get bytes in current lwIP buffer */
    byteslefttocopy = q->len;
    payloadoffset = 0;

    /* Check if the length of data to copy is bigger than Tx buffer size*/
    while( (byteslefttocopy + bufferoffset) > ETH_TX_BUF_SIZE )
    {
      /* Copy data to Tx buffer*/
      memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), (ETH_TX_BUF_SIZE - bufferoffset) );

      /* Point to next descriptor */
      DmaTxDesc = (ETH_DMADescTypeDef *)(DmaTxDesc->Buffer2NextDescAddr);

      /* Check if the buffer is available */
      if((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
      {
        errval = ERR_USE;
        goto error;
      }

      buffer = (uint8_t *)(DmaTxDesc->Buffer1Addr);

      byteslefttocopy = byteslefttocopy - (ETH_TX_BUF_SIZE - bufferoffset);
      payloadoffset = payloadoffset + (ETH_TX_BUF_SIZE - bufferoffset);
      framelength = framelength + (ETH_TX_BUF_SIZE - bufferoffset);
      bufferoffset = 0;
    }

    /* Copy the remaining bytes */
    memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), byteslefttocopy );
    bufferoffset = bufferoffset + byteslefttocopy;
    framelength = framelength + byteslefttocopy;
  }

  /* Prepare transmit descriptors to give to DMA */
  HAL_ETH_TransmitFrame(&EthHandle, framelength);

  errval = ERR_OK;

error:

  /* When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission */
  if ((EthHandle.Instance->DMASR & ETH_DMASR_TUS) != (uint32_t)RESET)
  {
    /* Clear TUS ETHERNET DMA flag */
    EthHandle.Instance->DMASR = ETH_DMASR_TUS;

    /* Resume DMA transmission*/
    EthHandle.Instance->DMATPDR = 0;
  }
  return errval;
}

/**
  * @brief Should allocate a pbuf and transfer the bytes of the incoming
  * packet from the interface into the pbuf.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return a pbuf filled with the received packet (including MAC header)
  *         NULL on memory error
  */
static struct pbuf * low_level_input(struct netif *netif)
{
  struct pbuf *p = NULL;
  struct pbuf *q;
  uint16_t len;
  uint8_t *buffer;
  __IO ETH_DMADescTypeDef *dmarxdesc;
  uint32_t bufferoffset = 0;
  uint32_t payloadoffset = 0;
  uint32_t byteslefttocopy = 0;
  uint32_t i=0;

  UNUSED(netif);

  if (HAL_ETH_GetReceivedFrame_IT(&EthHandle) != HAL_OK)
    return NULL;

  /* Obtain the size of the packet and put it into the "len" variable. */
  len = EthHandle.RxFrameInfos.length;
  buffer = (uint8_t *)EthHandle.RxFrameInfos.buffer;

  if (len > 0)
  {
    /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
  }

  if (p != NULL)
  {
    dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;
    bufferoffset = 0;

    for(q = p; q != NULL; q = q->next)
    {
      byteslefttocopy = q->len;
      payloadoffset = 0;

      /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size */
      while( (byteslefttocopy + bufferoffset) > ETH_RX_BUF_SIZE )
      {
        /* Copy data to pbuf */
        memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), (ETH_RX_BUF_SIZE - bufferoffset));

        /* Point to next descriptor */
        dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
        buffer = (uint8_t *)(dmarxdesc->Buffer1Addr);

        byteslefttocopy = byteslefttocopy - (ETH_RX_BUF_SIZE - bufferoffset);
        payloadoffset = payloadoffset + (ETH_RX_BUF_SIZE - bufferoffset);
        bufferoffset = 0;
      }

      /* Copy remaining data in pbuf */
      memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), byteslefttocopy);
      bufferoffset = bufferoffset + byteslefttocopy;
    }
  }

  /* Release descriptors to DMA */
  /* Point to first descriptor */
  dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;
  /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
  for (i=0; i< EthHandle.RxFrameInfos.SegCount; i++)
  {
    dmarxdesc->Status |= ETH_DMARXDESC_OWN;
    dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
  }

  /* Clear Segment_Count */
  EthHandle.RxFrameInfos.SegCount =0;

  /* When Rx Buffer unavailable flag is set: clear it and resume reception */
  if ((EthHandle.Instance->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
  {
    /* Clear RBUS ETHERNET DMA flag */
    EthHandle.Instance->DMASR = ETH_DMASR_RBUS;
    /* Resume DMA reception */
    EthHandle.Instance->DMARPDR = 0;
  }
  return p;
}

/**
  * @brief This function should be called when a packet is ready to be read
  * from the interface. It uses the function low_level_input() that
  * should handle the actual reception of bytes from the network
  * interface. Then the type of the received packet is determined and
  * the appropriate input function is called.
  *
  * @param netif the lwip network interface structure for this ethernetif
  */
void ethernetif_input(struct netif *netif)
{
  err_t err;
  struct pbuf *p;

  /* move received packet into a new pbuf */
  p = low_level_input(netif);

  /* no packet could be read, silently ignore this */
  if (p == NULL) return;

  /* entry point to the LwIP stack */
  err = netif->input(p, netif);

  if (err != ERR_OK)
  {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
    pbuf_free(p);
    p = NULL;
  }
}

/**
  * @brief Should be called at the beginning of the program to set up the
  * network interface. It calls the function low_level_init() to do the
  * actual setup of the hardware.
  *
  * This function should be passed as a parameter to netif_add().
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return ERR_OK if the loopif is initialized
  *         ERR_MEM if private data couldn't be allocated
  *         any other err_t on error
  */
err_t ethernetif_init(struct netif *netif)
{
  LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;

  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}

/**
  * @brief  Returns the current time in milliseconds
  *         when LWIP_TIMERS == 1 and NO_SYS == 1
  * @param  None
  * @retval Current Time value
  */
u32_t sys_now(void)
{
  return HAL_GetTick();
}

/**
  * @brief  This function sets the netif link status.
  * @param  netif: the network interface
  * @retval None
  */
void ethernetif_set_link(struct netif *netif)
{
  uint32_t regvalue = 0;

  /* Read PHY_MISR*/
  HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ISFR, &regvalue);

  /* Check whether the link interrupt has occurred or not */
  if((regvalue & PHY_ISFR_INT4) != (uint16_t)RESET)
  {
    netif_set_link_down(netif);
  }

  HAL_ETH_ReadPHYRegister(&EthHandle, PHY_BSR, &regvalue);

  if((regvalue & PHY_LINKED_STATUS) != (uint16_t)RESET) {
    netif_set_link_up(netif);
  }
}

/**
  * @brief  Link callback function, this function is called on change of link status
  *         to update low level driver configuration.
  * @param  netif: The network interface
  * @retval None
  */
void ethernetif_update_config(struct netif *netif)
{
  __IO uint32_t tickstart = 0;
  uint32_t regvalue = 0;

  if(netif_is_link_up(netif))
  {
    /* Restart the auto-negotiation */
    if(EthHandle.Init.AutoNegotiation != ETH_AUTONEGOTIATION_DISABLE)
    {
      /* Enable Auto-Negotiation */
      HAL_ETH_WritePHYRegister(&EthHandle, PHY_BCR, PHY_AUTONEGOTIATION);

      /* Get tick */
      tickstart = HAL_GetTick();

      /* Wait until the auto-negotiation will be completed */
      do
      {
        HAL_ETH_ReadPHYRegister(&EthHandle, PHY_BSR, &regvalue);

        /* Check for the Timeout ( 1s ) */
        if((HAL_GetTick() - tickstart ) > 1000)
        {
          /* In case of timeout */
          goto error;
        }

      } while (((regvalue & PHY_AUTONEGO_COMPLETE) != PHY_AUTONEGO_COMPLETE));

      /* Read the result of the auto-negotiation */
      HAL_ETH_ReadPHYRegister(&EthHandle, PHY_SR, &regvalue);

      /* Configure the MAC with the Duplex Mode fixed by the auto-negotiation process */
      if((regvalue & PHY_DUPLEX_STATUS) != (uint32_t)RESET)
      {
        /* Set Ethernet duplex mode to Full-duplex following the auto-negotiation */
        EthHandle.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
      }
      else
      {
        /* Set Ethernet duplex mode to Half-duplex following the auto-negotiation */
        EthHandle.Init.DuplexMode = ETH_MODE_HALFDUPLEX;
      }
      /* Configure the MAC with the speed fixed by the auto-negotiation process */
      if(regvalue & PHY_SPEED_STATUS)
      {
        /* Set Ethernet speed to 10M following the auto-negotiation */
        EthHandle.Init.Speed = ETH_SPEED_10M;
      }
      else
      {
        /* Set Ethernet speed to 100M following the auto-negotiation */
        EthHandle.Init.Speed = ETH_SPEED_100M;
      }
    }
    else /* AutoNegotiation Disable */
    {
    error :
      /* Check parameters */
      assert_param(IS_ETH_SPEED(EthHandle.Init.Speed));
      assert_param(IS_ETH_DUPLEX_MODE(EthHandle.Init.DuplexMode));

      /* Set MAC Speed and Duplex Mode to PHY */
      HAL_ETH_WritePHYRegister(&EthHandle, PHY_BCR, ((uint16_t)(EthHandle.Init.DuplexMode >> 3) |
                                                     (uint16_t)(EthHandle.Init.Speed >> 1)));
    }

    /* ETHERNET MAC Re-Configuration */
    HAL_ETH_ConfigMAC(&EthHandle, (ETH_MACInitTypeDef *) NULL);

    /* Restart MAC interface */
    HAL_ETH_Start(&EthHandle);
  }
  else
  {
    /* Stop MAC interface */
    HAL_ETH_Stop(&EthHandle);
  }

  ethernetif_notify_conn_changed(netif);
}

/**
  * @brief  This function notify user about link status changement.
  * @param  netif: the network interface
  * @retval None
  */
__weak void ethernetif_notify_conn_changed(struct netif *netif)
{
  /* NOTE : This is function clould be implemented in user file
            when the callback is needed,
  */
  UNUSED(netif);
}

/**
  * @brief  This function set a custom MAC address. This function must be called
  *         before ethernetif_init().
  * @param  mac: mac address
  * @retval None
  */
void ethernetif_set_mac_addr(const uint8_t *mac) {
  if(mac != NULL) {
    memcpy(macaddress,mac,6);
  }
}

#ifdef ETH_INPUT_USE_IT
/**
  * @brief  Ethernet Rx Transfer completed callback
  * @param  heth: ETH handle
  * @retval None
  */
void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
  ethernetif_input(&gnetif);
}

/**
  * @brief  This function handles Ethernet interrupt request.
  * @param  None
  * @retval None
  */
void ETH_IRQHandler(void)
{
  HAL_ETH_IRQHandler(&EthHandle);
}
#endif /* ETH_INPUT_USE_IT */

#ifdef __cplusplus
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
