/**
  ******************************************************************************
  * @file    mbox_ipcc.h
  * @author  MCD Application Team
  * @brief   Header for mbox_ipcc.c module
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

#ifndef __OPENAMP_MBOX_IPCC_H
#define __OPENAMP_MBOX_IPCC_H

#ifdef VIRTIOCON

  /**
  * @def IPCC_IRQ_PRIO
  * @brief IPCC interrupt preemption priority.
  *        Can be overridden before including this file.
  */
  #ifndef IPCC_IRQ_PRIO
    #define IPCC_IRQ_PRIO       1
  #endif
  /**
  * @def IPCC_IRQ_SUBPRIO
  * @brief IPCC interrupt sub-priority.
  *        Can be overridden before including this file.
  */
  #ifndef IPCC_IRQ_SUBPRIO
    #define IPCC_IRQ_SUBPRIO    0
  #endif

  /**
  * @brief Initialize the mailbox with the IPCC peripheral.
  * @return 0 on success, -1 if an IPCC channel notification cannot be activated.
  * @note  On failure Error_Handler() is called first, which is unlikely to return.
  */
  int MAILBOX_Init(void);

  /**
  * @brief Process vring messages received from the IPCC ISR.
  * @param vdev Virtio device.
  * @param vring_id Vring ID.
  * @return 0 if a message was processed, -1 otherwise.
  */
  int MAILBOX_Poll(struct virtio_device *vdev, uint32_t vring_id);

  /**
  * @brief Notify the remote processor (kick) that a message is ready.
  * @note  Called by OpenAMP from virtqueue_kick() in
  *        rpmsg_virtio_send_offchannel_raw(), therefore only while tx, but not rx.
  * @note  Blocks until the IPCC channel is free.
  * @param priv Private data passed by OpenAMP. Unused.
  * @param vring_id Vring ID.
  * @return 0 on success, -1 otherwise.
  */
  int MAILBOX_Notify(void *priv, uint32_t vring_id);

#endif /* VIRTIOCON */
#endif /* __OPENAMP_MBOX_IPCC_H */
