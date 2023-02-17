/*
 * Copyright (c) 2020 Xilinx, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**************************************************************************
 * FILE NAME
 *
 *       zynqmp_mb_a53_rproc.c
 *
 * DESCRIPTION
 *
 *      OpenAMP remoteproc implementation for Xilinx MicroBlaze design
 *      example. The design instanciates Xilinx MicroBlaze soft proccesor
 *      in ZynqMP's programmable logic and uses processing system (PS)
 *      DDR memory for its text and data. The APU in PS runs Linux with
 *      reserved-memory nodes in its device tree toaccommodat the
 *      MicroBlaze text, data.
 *
 **************************************************************************/

#include <metal/atomic.h>
#include <metal/assert.h>
#include <metal/device.h>
#include <metal/irq.h>
#include <metal/utilities.h>
#include <openamp/rpmsg_virtio.h>
#include "platform_info.h"

static struct remoteproc *
zynqmp_mb_a53_proc_init(struct remoteproc *rproc, struct remoteproc_ops *ops,
			void *arg)
{
	struct remoteproc_priv *prproc = arg;

	if (!rproc || !prproc || !ops)
		return NULL;
	rproc->priv = prproc;
	rproc->ops = ops;
	return rproc;
}

static inline void zynqmp_mb_a53_proc_remove(struct remoteproc *rproc)
{
	(void)rproc;
}

static void *
zynqmp_mb_a53_proc_mmap(struct remoteproc *rproc, metal_phys_addr_t *pa,
			metal_phys_addr_t *da, size_t size,
			unsigned int attribute, struct metal_io_region **io)
{
	struct remoteproc_mem *mem;
	metal_phys_addr_t lpa, lda;
	struct metal_io_region *tmpio;

	lpa = *pa;
	lda = *da;

	if (lpa == METAL_BAD_PHYS && lda == METAL_BAD_PHYS)
		return NULL;
	if (lpa == METAL_BAD_PHYS)
		lpa = lda;
	if (lda == METAL_BAD_PHYS)
		lda = lpa;

	mem = metal_allocate_memory(sizeof(*mem));
	if (!mem)
		return NULL;
	tmpio = metal_allocate_memory(sizeof(*tmpio));
	if (!tmpio) {
		metal_free_memory(mem);
		return NULL;
	}
	remoteproc_init_mem(mem, NULL, lpa, lda, size, tmpio);
	/* va is the same as pa in this platform */
	metal_io_init(tmpio, (void *)lpa, &mem->pa, size,
		      sizeof(metal_phys_addr_t) << 3, attribute, NULL);
	remoteproc_add_mem(rproc, mem);
	*pa = lpa;
	*da = lda;
	if (io) {
		*io = tmpio;
	} else {
		metal_free_memory(tmpio);
		metal_free_memory(mem);
		return NULL;
	}

	return metal_io_phys_to_virt(tmpio, mem->pa);
}

static int zynqmp_mb_a53_proc_notify(struct remoteproc *rproc, uint32_t id)
{
	(void)rproc;
	(void)id;
	if (!rproc)
		return -1;

	char *notify = (char *)POLL_SHM_LOCATION;
	*notify = POLL_STOP;
	return 0;
}

/*
 * processor operations from mb to a53. It defines
 * notification operation and remote processor management operations.
 */
struct remoteproc_ops zynqmp_mb_a53_proc_ops = {
	.init = zynqmp_mb_a53_proc_init,
	.remove = zynqmp_mb_a53_proc_remove,
	.mmap = zynqmp_mb_a53_proc_mmap,
	.notify = zynqmp_mb_a53_proc_notify,
	.start = NULL,
	.stop = NULL,
	.shutdown = NULL,
};
