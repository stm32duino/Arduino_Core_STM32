/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * All rights reserved.
 * Copyright (c) 2017 Xilinx, Inc.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**************************************************************************
 * FILE NAME
 *
 *       platform_info.c
 *
 * DESCRIPTION
 *
 *       This file define platform specific data and implements APIs to set
 *       platform specific information for OpenAMP.
 *
 **************************************************************************/
#include <metal/alloc.h>
#include <metal/atomic.h>
#include <metal/io.h>
#include <metal/irq.h>
#include <metal/device.h>
#include <metal/utilities.h>
#include <openamp/remoteproc.h>
#include <openamp/rpmsg_virtio.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/un.h>
#include "platform_info.h"

#define RPU_CPU_ID          0 /* RPU remote CPU Index. We only talk to
                               * one CPU in the exmaple. We set the CPU
                               * index to 0. */
#ifdef versal
#define IPI_CHN_BITMASK     0x08 /* IPI channel bit mask for IPI
					* from/to RPU0 */
#define IPI_DEV_NAME        "ff360000.ipi" /* IPI device name */
#else
#define IPI_CHN_BITMASK	    0x00000100
#define IPI_DEV_NAME	    "ff340000.ipi"
#endif /* versal */
#define DEV_BUS_NAME        "platform" /* device bus name. "platform" bus
                                        * is used in Linux kernel for generic
					* devices */
/* libmetal devices names used in the examples.
 * They are platform devices, you find them in Linux sysfs
 * sys/bus/platform/devices */
#define SHM_DEV_NAME        "3ed20000.shm" /* shared device name */

#define RSC_MEM_PA          0x3ED20000UL
#define RSC_MEM_SIZE        0x2000UL
#define VRING_MEM_PA        0x3ED40000UL
#define VRING_MEM_SIZE      0x8000UL
#define SHARED_BUF_PA       0x3ED48000UL
#define SHARED_BUF_SIZE     0x40000UL


struct remoteproc_priv rproc_priv = {
	.shm_name = SHM_DEV_NAME,
	.shm_bus_name = DEV_BUS_NAME,
#ifndef RPMSG_NO_IPI
	.ipi_name = IPI_DEV_NAME,
	.ipi_bus_name = DEV_BUS_NAME,
	.ipi_chn_mask = IPI_CHN_BITMASK,
#endif /* !RPMSG_NO_IPI */
#ifdef RPMSG_NO_IPI
	.shm_poll_name = POLL_DEV_NAME,
	.shm_poll_bus_name = DEV_BUS_NAME,
#endif /* RPMSG_NO_IPI */
};

static struct remoteproc rproc_inst;

/* External functions */
extern int init_system(void);
extern void cleanup_system(void);

#define _rproc_wait() metal_cpu_yield()


/* processor operations from r5 to a53. It defines
 * notification operation and remote processor managementi operations. */
extern struct remoteproc_ops zynqmp_linux_r5_proc_ops;

/* RPMsg virtio shared buffer pool */
static struct rpmsg_virtio_shm_pool shpool;

static struct remoteproc *
platform_create_proc(int proc_index, int rsc_index)
{
	void *rsc_table;
	int rsc_size;
	int ret;
	metal_phys_addr_t pa;

	(void)proc_index;
	(void)rsc_index;
	rsc_size = RSC_MEM_SIZE;

	/* Initialize remoteproc instance */
	if (!remoteproc_init(&rproc_inst, &zynqmp_linux_r5_proc_ops,
			     &rproc_priv))
		return NULL;
	printf("Successfully initialized remoteproc\r\n");

	/* Mmap resource table */
	pa = RSC_MEM_PA;
	printf("Calling mmap resource table.\r\n");
	rsc_table = remoteproc_mmap(&rproc_inst, &pa, NULL, rsc_size,
				    0, NULL);
	if (!rsc_table) {
		fprintf(stderr, "ERROR: Failed to mmap resource table.\r\n");
		return NULL;
	}
	printf("Successfully mmap resource table.\r\n");
	/* parse resource table to remoteproc */
	ret = remoteproc_set_rsc_table(&rproc_inst, rsc_table, rsc_size);
	if (ret) {
		printf("Failed to intialize remoteproc\r\n");
		remoteproc_remove(&rproc_inst);
		return NULL;
	}
	printf("Successfully set resource table to remoteproc.\r\n");

	return &rproc_inst;
}

int platform_init(int argc, char *argv[], void **platform)
{
	unsigned long proc_id = 0;
	unsigned long rsc_id = 0;
	struct remoteproc *rproc;

	if (!platform) {
		fprintf(stderr, "Failed to initialize platform, NULL pointer"
			"to store platform data.\r\n");
		return -EINVAL;
	}
	/* Initialize HW system components */
	init_system();

	if (argc >= 2) {
		proc_id = strtoul(argv[1], NULL, 0);
	}

	if (argc >= 3) {
		rsc_id = strtoul(argv[2], NULL, 0);
	}

	rproc = platform_create_proc(proc_id, rsc_id);
	if (!rproc) {
		fprintf(stderr, "Failed to create remoteproc device.\r\n");
		return -EINVAL;
	}
	*platform = rproc;
	return 0;
}

struct  rpmsg_device *
platform_create_rpmsg_vdev(void *platform, unsigned int vdev_index,
			   unsigned int role,
			   void (*rst_cb)(struct virtio_device *vdev),
			   rpmsg_ns_bind_cb ns_bind_cb)
{
	struct remoteproc *rproc = platform;
	struct rpmsg_virtio_device *rpmsg_vdev;
	struct virtio_device *vdev;
	void *shbuf;
	struct metal_io_region *shbuf_io;
	int ret;

	rpmsg_vdev = metal_allocate_memory(sizeof(*rpmsg_vdev));
	if (!rpmsg_vdev)
		return NULL;
	shbuf_io = remoteproc_get_io_with_pa(rproc, SHARED_BUF_PA);
	if (!shbuf_io)
		goto err1;
	shbuf = metal_io_phys_to_virt(shbuf_io,
				      SHARED_BUF_PA);

	printf("Creating virtio...\r\n");
	/* TODO: can we have a wrapper for the following two functions? */
	vdev = remoteproc_create_virtio(rproc, vdev_index, role, rst_cb);
	if (!vdev) {
		printf("failed remoteproc_create_virtio\r\n");
		goto err1;
	}
	printf("Successfully created virtio device.\r\n");

	/* Only RPMsg virtio master needs to initialize the shared buffers pool */
	rpmsg_virtio_init_shm_pool(&shpool, shbuf, SHARED_BUF_SIZE);

	printf("initializing rpmsg vdev\r\n");
	/* RPMsg virtio slave can set shared buffers pool argument to NULL */
	ret = rpmsg_init_vdev(rpmsg_vdev, vdev, ns_bind_cb,
			      shbuf_io, &shpool);
	if (ret) {
		printf("failed rpmsg_init_vdev\r\n");
		goto err2;
	}
	return rpmsg_virtio_get_rpmsg_device(rpmsg_vdev);
err2:
	remoteproc_remove_virtio(rproc, vdev);
err1:
	metal_free_memory(rpmsg_vdev);
	return NULL;
}

int platform_poll(void *priv)
{
	struct remoteproc *rproc = priv;
	struct remoteproc_priv *prproc;
	unsigned int flags;
	int ret;

	prproc = rproc->priv;
	while(1) {
#ifdef RPMSG_NO_IPI
		(void)flags;
		if (metal_io_read32(prproc->shm_poll_io, 0)) {
			ret = remoteproc_get_notification(rproc,
							  RSC_NOTIFY_ID_ANY);
			if (ret)
				return ret;
			break;
		}
#else
		flags = metal_irq_save_disable();
		if (!(atomic_flag_test_and_set(&prproc->ipi_nokick))) {
			metal_irq_restore_enable(flags);
			ret = remoteproc_get_notification(rproc,
							  RSC_NOTIFY_ID_ANY);
			if (ret)
				return ret;
			break;
		}
		_rproc_wait();
		metal_irq_restore_enable(flags);
#endif /* RPMSG_NO_IPI */
	}
	return 0;
}

void platform_release_rpmsg_vdev(struct rpmsg_device *rpdev, void *platform)
{
	struct rpmsg_virtio_device *rpvdev;
	struct remoteproc *rproc;

	rpvdev = metal_container_of(rpdev, struct rpmsg_virtio_device, rdev);
	rproc = platform;

	rpmsg_deinit_vdev(rpvdev);
	remoteproc_remove_virtio(rproc, rpvdev->vdev);
}

void platform_cleanup(void *platform)
{
	struct remoteproc *rproc = platform;

	if (rproc)
		remoteproc_remove(rproc);
	cleanup_system();
}
