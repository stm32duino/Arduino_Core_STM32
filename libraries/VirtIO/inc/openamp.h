/**
  ******************************************************************************
  * @file   openamp.h
  * @brief  Header for openamp applications
  * @author  MCD Application Team
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OPENAMP_OPENAMP_H
#define __OPENAMP_OPENAMP_H

#ifdef VIRTIOCON

#include <openamp/rpmsg.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "openamp_conf.h"

/** @brief Send a message through an rpmsg endpoint. Alias of rpmsg_send(). */
#define OPENAMP_send  rpmsg_send
/** @brief Destroy an rpmsg endpoint. Alias of rpmsg_destroy_ept(). */
#define OPENAMP_destroy_ept rpmsg_destroy_ept

/**
 * @brief Initialize the OpenAMP framework.
 * @return 0 on success, a negative or error value otherwise.
 */
int OPENAMP_Init(void);

/**
 * @brief Deinitialize the OpenAMP framework.
 */
void OPENAMP_DeInit(void);

/**
 * @brief Create and register a name service endpoint.
 * @param ept Virtio rpmsg endpoint to initialize.
 * @param name Virtio rpmsg name service name.
 * @param dest Message destination address. Set RPMSG_ADDR_ANY if the host
 *             processor decides it.
 * @param cb Virtio rpmsg endpoint callback (receive).
 * @param unbind_cb Virtio rpmsg endpoint destroy callback.
 * @return 0 on success, a negative or error value otherwise.
 */
int OPENAMP_create_endpoint(struct rpmsg_endpoint *ept, const char *name,
                            uint32_t dest, rpmsg_ept_cb cb,
                            rpmsg_ns_unbind_cb unbind_cb);

/**
 * @brief Check and process any received messages from the tx channel.
 * @note  Do not call this from an ISR.
 */
void OPENAMP_check_for_tx_message(void);

/**
 * @brief Check and process any received messages from the rx channel.
 * @note  Do not call this from an ISR.
 */
void OPENAMP_check_for_rx_message(void);

/**
 * @brief Wait until an rpmsg endpoint (VirtIOSerial) is ready to send.
 *        Readiness is reached when the destination address is known.
 * @note  Blocks until the first message arrives from the Linux host.
 *        Sending an rpmsg message before that fails.
 * @note  Do not call this from an ISR.
 * @see   VirtIOSerial::rxCallback
 * @param rp_ept Virtio rpmsg endpoint to wait for.
 */
void OPENAMP_Wait_EndPointready(struct rpmsg_endpoint *rp_ept);

#ifdef __cplusplus
}
#endif
#endif /* VIRTIOCON */
#endif /*__OPENAMP_OPENAMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
