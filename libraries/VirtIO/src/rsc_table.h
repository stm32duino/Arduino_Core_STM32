/*
 * Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                       opensource.org/licenses/BSD-3-Clause
 *
 */

/**
 * @file    rsc_table.h
 * @brief   Resource table for the BM remote, populated for use by the Linux Master.
 */

#ifndef __OPENAMP_RSC_TABLE_H
#define __OPENAMP_RSC_TABLE_H

#ifdef VIRTIOCON

#include "virtio_config.h"
#include "openamp/open_amp.h"
#include "openamp_conf.h"

/**
 * @brief Resource table for the given remote: rpmsg vdev entry with its two
 *        vrings, and the trace (log) entry.
 */
struct shared_resource_table {
  unsigned int version;
  unsigned int num;
  unsigned int reserved[2];
  unsigned int offset[NUM_RESOURCE_ENTRIES];
  /* text carveout entry */

  /* rpmsg vdev entry */
  struct fw_rsc_vdev vdev;
  struct fw_rsc_vdev_vring vring0;
  struct fw_rsc_vdev_vring vring1;
  struct fw_rsc_trace cm_trace;
};

/**
 * @brief Initialize the resource table used by the remote processor.
 * @param RPMsgRole Role of the processor. Not used.
 * @param table_ptr Output: pointer to the resource table.
 * @param length Output: size of the resource table, in bytes.
 */
void resource_table_init(int RPMsgRole, void **table_ptr, int *length);

#endif /* VIRTIOCON */
#endif /* __OPENAMP_RSC_TABLE_H */
