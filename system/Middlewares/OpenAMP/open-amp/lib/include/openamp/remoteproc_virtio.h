/*
 * Remoteproc Virtio Framework
 *
 * Copyright(c) 2018 Xilinx Ltd.
 * Copyright(c) 2011 Texas Instruments, Inc.
 * Copyright(c) 2011 Google, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REMOTEPROC_VIRTIO_H
#define REMOTEPROC_VIRTIO_H

#include <metal/io.h>
#include <metal/list.h>
#include <openamp/virtio.h>

#if defined __cplusplus
extern "C" {
#endif

/* define vdev notification funciton user should implement */
typedef int (*rpvdev_notify_func)(void *priv, uint32_t id);

/**
 * struct remoteproc_virtio
 * @priv pointer to private data
 * @vdev_rsc address of vdev resource
 * @vdev_rsc_io metal I/O region of vdev_info, can be NULL
 * @notify notification function
 * @vdev virtio device
 * @node list node
 */
struct remoteproc_virtio {
	void *priv;
	void *vdev_rsc;
	struct metal_io_region *vdev_rsc_io;
	rpvdev_notify_func notify;
	struct virtio_device vdev;
	struct metal_list node;
};

/**
 * rproc_virtio_create_vdev
 *
 * Create rproc virtio vdev
 *
 * @role: 0 - virtio master, 1 - virtio slave
 * @notifyid: virtio device notification id
 * @rsc: pointer to the virtio device resource
 * @rsc_io: pointer to the virtio device resource I/O region
 * @priv: pointer to the private data
 * @notify: vdev and virtqueue notification function
 * @rst_cb: reset virtio device callback
 *
 * return pointer to the created virtio device for success,
 * NULL for failure.
 */
struct virtio_device *
rproc_virtio_create_vdev(unsigned int role, unsigned int notifyid,
			 void *rsc, struct metal_io_region *rsc_io,
			 void *priv,
			 rpvdev_notify_func notify,
			 virtio_dev_reset_cb rst_cb);

/**
 * rproc_virtio_remove_vdev
 *
 * Remove rproc virtio vdev
 *
 * @vdev - pointer to the virtio device
 */
void rproc_virtio_remove_vdev(struct virtio_device *vdev);

/**
 * rproc_virtio_init_vring
 *
 * Initialize rproc virtio vring
 *
 * @vdev: pointer to the virtio device
 * @index: vring index in the virtio device
 * @notifyid: remoteproc vring notification id
 * @va: vring virtual address
 * @io: pointer to vring I/O region
 * @num_desc: number of descriptors
 * @align: vring alignment
 *
 * return 0 for success, negative value for failure.
 */
int rproc_virtio_init_vring(struct virtio_device *vdev, unsigned int index,
			    unsigned int notifyid, void *va,
			    struct metal_io_region *io,
			    unsigned int num_descs, unsigned int align);

/**
 * rproc_virtio_notified
 *
 * remoteproc virtio is got notified
 *
 * @vdev - pointer to the virtio device
 * @notifyid - notify id
 *
 * return 0 for successful, negative value for failure
 */
int rproc_virtio_notified(struct virtio_device *vdev, uint32_t notifyid);

/**
 * rproc_virtio_wait_remote_ready
 *
 * Blocking function, waiting for the remote core is ready to start
 * communications.
 *
 * @vdev - pointer to the virtio device
 *
 * return true when remote processor is ready.
 */
void rproc_virtio_wait_remote_ready(struct virtio_device *vdev);

#if defined __cplusplus
}
#endif

#endif /* REMOTEPROC_VIRTIO_H */
