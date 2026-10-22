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

  /* Interrupt priority */
  #ifndef IPCC_IRQ_PRIO
    #define IPCC_IRQ_PRIO       1
  #endif
  #ifndef IPCC_IRQ_SUBPRIO
    #define IPCC_IRQ_SUBPRIO    0
  #endif

  /**
   * @brief Initialize the mailbox with the IPCC peripheral.
   * @return 0 on success, -1 on failure.
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
   * @note  Called by OpenAMP from virtqueue_kick() during tx only, never rx.
   * @param priv Private data passed by OpenAMP. Unused.
   * @param vring_id Vring ID.
   * @return 0 on success, -1 otherwise.
   */
  int MAILBOX_Notify(void *priv, uint32_t vring_id);

#endif /* VIRTIOCON */
#endif /* __OPENAMP_MBOX_IPCC_H */
