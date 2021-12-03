/*
 * ZynqMP RPU life cycle management remoteproc example implementation
 *
 * Copyright(c) 2019 Xilinx Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <common.h>

static struct remoteproc *rpu_rproc_init(struct remoteproc *rproc,
				 struct remoteproc_ops *ops, void *arg)
{
	struct rproc_priv *priv;
	unsigned int cpu_id = *((unsigned int *)arg);

	if (cpu_id < NODE_RPU_0 || cpu_id > NODE_RPU_1) {
		LPERROR("%s: invalid node id: %d\n\r", __func__, cpu_id);
		return NULL;
	}

	LPRINTF("%s: node id: %d\n\r", __func__, cpu_id);
	priv = metal_allocate_memory(sizeof(*priv));
	if (!priv)
		return NULL;
	memset(priv, 0, sizeof(*priv));
	priv->rproc = rproc;
	priv->cpu_id = cpu_id;
	priv->rproc->ops = ops;
	metal_list_init(&priv->rproc->mems);
	priv->rproc->priv = priv;
	rproc->state = RPROC_READY;
	return priv->rproc;
}

static void rpu_rproc_remove(struct remoteproc *rproc)
{
	struct rproc_priv *priv;

	priv = (struct rproc_priv *)rproc->priv;
	metal_free_memory(priv);
}

static void *rpu_rproc_mmap(struct remoteproc *rproc,
		    metal_phys_addr_t *pa, metal_phys_addr_t *da,
		    size_t size, unsigned int attribute,
		    struct metal_io_region **io)
{
	struct remoteproc_mem *mem;
	struct rproc_priv *priv;
	metal_phys_addr_t lpa, lda, lda_end;

	priv = rproc->priv;

	if ((!da || !pa) || (*da == METAL_BAD_PHYS && *pa == METAL_BAD_PHYS))
		return NULL;
	LPRINTF("%s: pa=0x%x, da=0x%x, size=0x%x, atrribute=0x%x\n\r",
		__func__, *pa, *da, size, attribute);
	lda = *da;
	lpa = *pa;
	if (!attribute)
		attribute = NORM_SHARED_NCACHE | PRIV_RW_USER_RW;

	lda_end = lda + size;
	/* call xilpm request node for relevant memory */
	if (lda <= 0x40000) {
		if (priv->cpu_id == NODE_RPU_0 || priv->cpu_id == NODE_RPU) {
			lpa = 0xFFE00000 + lda;
			if (lda < 0x10000)
				XPm_RequestNode(NODE_TCM_0_A,PM_CAP_ACCESS,
					XPM_MIN_QOS,REQUEST_ACK_NO);
			if (lda <= 0x20000 && lda_end >= 0x10000)
				XPm_RequestNode(NODE_TCM_1_A,PM_CAP_ACCESS,
					XPM_MIN_QOS,REQUEST_ACK_NO);
			if (lda <= 0x30000 && lda_end >= 0x20000)
				XPm_RequestNode(NODE_TCM_0_B,PM_CAP_ACCESS,
					XPM_MIN_QOS,REQUEST_ACK_NO);
			if (lda <= 0x40000 && lda_end >= 0x30000)
				XPm_RequestNode(NODE_TCM_1_B,PM_CAP_ACCESS,
					XPM_MIN_QOS,REQUEST_ACK_NO);
		} else if (priv->cpu_id == NODE_RPU_1) {
			lpa = 0xFFE90000 + lda;
			if (lda < 0x10000)
				XPm_RequestNode(NODE_TCM_1_A,PM_CAP_ACCESS,
					XPM_MIN_QOS,REQUEST_ACK_NO);
			if (lda <= 0x30000 && lda_end >= 0x20000)
				XPm_RequestNode(NODE_TCM_1_B,PM_CAP_ACCESS,
					XPM_MIN_QOS,REQUEST_ACK_NO);
		} else {
			LPERROR("mmap failed: invalid cpu node: %d\r\n", priv->cpu_id);
			return NULL;
		}
	}

	mem = metal_allocate_memory(sizeof(*mem));
	if (!mem)
		return NULL;
	mem->pa = lpa;
	mem->da = lda;

	*io = metal_allocate_memory(sizeof(struct metal_io_region));
	if (!*io) {
		metal_free_memory(mem);
		return NULL;
	}

        /* This code only runs on the R5, which has a flat memory
         * space. Therefore, we use the same value for the physical
         * and virtual addresses we pass in to metal_io_init().
         */
	metal_io_init(*io, (void *)mem->pa, &mem->pa, size,
		      sizeof(metal_phys_addr_t)<<3, attribute, NULL);
	mem->io = *io;
	metal_list_add_tail(&rproc->mems, &mem->node);
	*pa = lpa;
	*da = lda;
	mem->size = size;
	return metal_io_phys_to_virt(*io, mem->pa);
}

static int rpu_rproc_start(struct remoteproc *rproc)
{
	struct rproc_priv *priv;
	int ret;

	priv = rproc->priv;
	ret = XPm_RequestWakeUp(priv->cpu_id, true, rproc->bootaddr,
			REQUEST_ACK_NO);
	if (ret != XST_SUCCESS) {
		LPRINTF("%s: Failed to start RPU 0x%x, ret=0x%x\n\r",
			__func__, priv->cpu_id, ret);
		return -1;
	}
	return 0;
}

static int rpu_rproc_stop(struct remoteproc *rproc)
{
	/* It is lacking a stop operation in the libPM */
	(void)rproc;
	return 0;
}

static int rpu_rproc_shutdown(struct remoteproc *rproc)
{
	struct rproc_priv *priv;
	int ret;
	struct remoteproc_mem *mem;
	struct metal_list *node;

	priv = rproc->priv;
	/* Delete all the registered remoteproc memories */
	metal_list_for_each(&rproc->mems, node) {
		struct metal_list *tmpnode;
		metal_phys_addr_t pa, pa_end;

		mem = metal_container_of(node, struct remoteproc_mem, node);
		tmpnode = node;
		/* Release TCM resource */
		pa = mem->pa;
		pa_end = metal_io_phys(mem->io, metal_io_region_size(mem->io));
		node = tmpnode->prev;
		metal_list_del(tmpnode);
		metal_free_memory(mem->io);
		metal_free_memory(mem);
		/* call xilpm release node for relevant memory */
		if (pa <= 0x40000) {
			if (priv->cpu_id == NODE_RPU_0 || priv->cpu_id == NODE_RPU) {
				if (pa < 0x10000)
					XPm_ReleaseNode(NODE_TCM_0_A);
				if (pa <= 0x20000 && pa_end >= 0x10000)
					XPm_ReleaseNode(NODE_TCM_1_A);
				if (pa <= 0x30000 && pa_end >= 0x20000)
					XPm_ReleaseNode(NODE_TCM_0_B);
				if (pa <= 0x40000 && pa_end >= 0x30000)
					XPm_ReleaseNode(NODE_TCM_1_B);
			} else if (priv->cpu_id == NODE_RPU_1) {
				if (pa < 0x10000)
					XPm_ReleaseNode(NODE_TCM_1_A);
				if (pa <= 0x30000 && pa_end >= 0x20000)
					XPm_ReleaseNode(NODE_TCM_1_B);
			} else {
				LPERROR("unmap failed: invalid cpu node: %d\r\n", priv->cpu_id);
				return NULL;
			}
		}

	}

	ret = XPm_ForcePowerDown(priv->cpu_id, REQUEST_ACK_NO);
	if (ret != XST_SUCCESS)
		return -1;
	return 0;
}

struct remoteproc_ops zynqmp_rpu_rproc_ops = {
    .init = rpu_rproc_init,
    .remove = rpu_rproc_remove,
    .start = rpu_rproc_start,
    .stop = rpu_rproc_stop,
    .shutdown = rpu_rproc_shutdown,
    .mmap = rpu_rproc_mmap,
};
