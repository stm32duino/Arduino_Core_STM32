/**
  ******************************************************************************
  * @file    rsc_table.c
  * @author  MCD Application Team
  * @brief   Ressource table
  *
  *   This file provides a default resource table requested by remote proc to
  *  load the elf file. It also allows to add debug trace using a shared buffer.
  *
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
#ifdef VIRTIOCON

#include "rsc_table.h"
#include "openamp/open_amp.h"

#define RPMSG_IPU_C0_FEATURES 1
#define VRING_COUNT           2

/* VirtIO rpmsg device id */
#define VIRTIO_ID_RPMSG       7

#if defined (VIRTIO_LOG)
  extern char virtio_log_buffer[];
#endif

const struct shared_resource_table __attribute__((__section__(".resource_table"))) __attribute__((used)) resource_table = {
  .version = 1,
#if defined (VIRTIO_LOG)
  .num = 2,
#else
  .num = 1,
#endif
  .reserved = {0, 0},
  .offset = {
    offsetof(struct shared_resource_table, vdev),
    offsetof(struct shared_resource_table, cm_trace),
  },
  /* Virtio device entry */
  .vdev = {
    .type = RSC_VDEV,
    .id = VIRTIO_ID_RPMSG,
    .notifyid = 0,
    .dfeatures = RPMSG_IPU_C0_FEATURES,
    .gfeatures = 0,
    .config_len = 0,
    .status = 0,
    .num_of_vrings = VRING_COUNT,
    .reserved = {0, 0},
  },
  /* Vring rsc entry - part of vdev rsc entry */
  .vring0 = {
    .da = VRING_TX_ADDRESS,
    .align = VRING_ALIGNMENT,
    .num = VRING_NUM_BUFFS,
    .notifyid = VRING0_ID,
    .reserved = 0
  },
  .vring1 = {
    .da = VRING_RX_ADDRESS,
    .align = VRING_ALIGNMENT,
    .num = VRING_NUM_BUFFS,
    .notifyid = VRING1_ID,
    .reserved = 0
  },
#if defined (VIRTIO_LOG)
  .cm_trace = {
    .type = RSC_TRACE,
    .da = (uint32_t)virtio_log_buffer,
    .len = VIRTIO_LOG_BUFFER_SIZE,
    .reserved = 0,
    .name = "arduino_log",
  },
#endif
} ;

void resource_table_init(int RPMsgRole, void **table_ptr, int *length)
{
  (void)RPMsgRole;
  *length = sizeof(resource_table);
  *table_ptr = (void *)&resource_table;
}

#endif /* VIRTIOCON */
