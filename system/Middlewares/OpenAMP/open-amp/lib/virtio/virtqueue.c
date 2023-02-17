/*-
 * Copyright (c) 2011, Bryan Venteicher <bryanv@FreeBSD.org>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>
#include <openamp/virtio.h>
#include <openamp/virtqueue.h>
#include <metal/atomic.h>
#include <metal/log.h>
#include <metal/alloc.h>
#include <metal/cache.h>

/* Prototype for internal functions. */
static void vq_ring_init(struct virtqueue *, void *, int);
static void vq_ring_update_avail(struct virtqueue *, uint16_t);
static uint16_t vq_ring_add_buffer(struct virtqueue *, struct vring_desc *,
				   uint16_t, struct virtqueue_buf *, int, int);
static int vq_ring_enable_interrupt(struct virtqueue *, uint16_t);
static void vq_ring_free_chain(struct virtqueue *, uint16_t);
static int vq_ring_must_notify(struct virtqueue *vq);
static void vq_ring_notify(struct virtqueue *vq);
#ifndef VIRTIO_SLAVE_ONLY
static int virtqueue_nused(struct virtqueue *vq);
#endif
#ifndef VIRTIO_MASTER_ONLY
static int virtqueue_navail(struct virtqueue *vq);
#endif

#ifdef VIRTIO_CACHED_VRINGS
#define VRING_FLUSH(x)		metal_cache_flush(&x, sizeof(x))
#define VRING_INVALIDATE(x)	metal_cache_invalidate(&x, sizeof(x))
#else
#define VRING_FLUSH(x)		do { } while (0)
#define VRING_INVALIDATE(x)	do { } while (0)
#endif /* VIRTIO_CACHED_VRINGS */

/* Default implementation of P2V based on libmetal */
static inline void *virtqueue_phys_to_virt(struct virtqueue *vq,
					   metal_phys_addr_t phys)
{
	struct metal_io_region *io = vq->shm_io;

	return metal_io_phys_to_virt(io, phys);
}

/* Default implementation of V2P based on libmetal */
static inline metal_phys_addr_t virtqueue_virt_to_phys(struct virtqueue *vq,
						       void *buf)
{
	struct metal_io_region *io = vq->shm_io;

	return metal_io_virt_to_phys(io, buf);
}

/**
 * virtqueue_create - Creates new VirtIO queue
 *
 * @param device    - Pointer to VirtIO device
 * @param id        - VirtIO queue ID , must be unique
 * @param name      - Name of VirtIO queue
 * @param ring      - Pointer to vring_alloc_info control block
 * @param callback  - Pointer to callback function, invoked
 *                    when message is available on VirtIO queue
 * @param notify    - Pointer to notify function, used to notify
 *                    other side that there is job available for it
 * @param vq        - Created VirtIO queue.
 *
 * @return          - Function status
 */
int virtqueue_create(struct virtio_device *virt_dev, unsigned short id,
		     const char *name, struct vring_alloc_info *ring,
		     void (*callback)(struct virtqueue *vq),
		     void (*notify)(struct virtqueue *vq),
		     struct virtqueue *vq)
{
	int status = VQUEUE_SUCCESS;

	VQ_PARAM_CHK(ring == NULL, status, ERROR_VQUEUE_INVLD_PARAM);
	VQ_PARAM_CHK(ring->num_descs == 0, status, ERROR_VQUEUE_INVLD_PARAM);
	VQ_PARAM_CHK(ring->num_descs & (ring->num_descs - 1), status,
		     ERROR_VRING_ALIGN);
	VQ_PARAM_CHK(vq == NULL, status, ERROR_NO_MEM);

	if (status == VQUEUE_SUCCESS) {
		vq->vq_dev = virt_dev;
		vq->vq_name = name;
		vq->vq_queue_index = id;
		vq->vq_nentries = ring->num_descs;
		vq->vq_free_cnt = vq->vq_nentries;
		vq->callback = callback;
		vq->notify = notify;

		/* Initialize vring control block in virtqueue. */
		vq_ring_init(vq, ring->vaddr, ring->align);
	}

	/*
	 * CACHE: nothing to be done here. Only desc.next is setup at this
	 * stage but that is only written by master, so no need to flush it.
	 */

	return status;
}

/**
 * virtqueue_add_buffer()   - Enqueues new buffer in vring for consumption
 *                            by other side. Readable buffers are always
 *                            inserted before writable buffers
 *
 * @param vq                - Pointer to VirtIO queue control block.
 * @param buf_list          - Pointer to a list of virtqueue buffers.
 * @param readable          - Number of readable buffers
 * @param writable          - Number of writable buffers
 * @param cookie            - Pointer to hold call back data
 *
 * @return                  - Function status
 */
int virtqueue_add_buffer(struct virtqueue *vq, struct virtqueue_buf *buf_list,
			 int readable, int writable, void *cookie)
{
	struct vq_desc_extra *dxp = NULL;
	int status = VQUEUE_SUCCESS;
	uint16_t head_idx;
	uint16_t idx;
	int needed;

	needed = readable + writable;

	VQ_PARAM_CHK(vq == NULL, status, ERROR_VQUEUE_INVLD_PARAM);
	VQ_PARAM_CHK(needed < 1, status, ERROR_VQUEUE_INVLD_PARAM);
	VQ_PARAM_CHK(vq->vq_free_cnt == 0, status, ERROR_VRING_FULL);

	VQUEUE_BUSY(vq);

	if (status == VQUEUE_SUCCESS) {
		VQASSERT(vq, cookie != NULL, "enqueuing with no cookie");

		head_idx = vq->vq_desc_head_idx;
		VQ_RING_ASSERT_VALID_IDX(vq, head_idx);
		dxp = &vq->vq_descx[head_idx];

		VQASSERT(vq, dxp->cookie == NULL,
			 "cookie already exists for index");

		dxp->cookie = cookie;
		dxp->ndescs = needed;

		/* Enqueue buffer onto the ring. */
		idx = vq_ring_add_buffer(vq, vq->vq_ring.desc, head_idx,
					 buf_list, readable, writable);

		vq->vq_desc_head_idx = idx;
		vq->vq_free_cnt -= needed;

		if (vq->vq_free_cnt == 0) {
			VQ_RING_ASSERT_CHAIN_TERM(vq);
		} else {
			VQ_RING_ASSERT_VALID_IDX(vq, idx);
		}

		/*
		 * Update vring_avail control block fields so that other
		 * side can get buffer using it.
		 */
		vq_ring_update_avail(vq, head_idx);
	}

	VQUEUE_IDLE(vq);

	return status;
}

/**
 * virtqueue_get_buffer - Returns used buffers from VirtIO queue
 *
 * @param vq            - Pointer to VirtIO queue control block
 * @param len           - Length of conumed buffer
 * @param idx           - index of the buffer
 *
 * @return              - Pointer to used buffer
 */
void *virtqueue_get_buffer(struct virtqueue *vq, uint32_t *len, uint16_t *idx)
{
	struct vring_used_elem *uep;
	void *cookie;
	uint16_t used_idx, desc_idx;

	/* Used.idx is updated by slave, so we need to invalidate */
	VRING_INVALIDATE(vq->vq_ring.used->idx);

	if (!vq || vq->vq_used_cons_idx == vq->vq_ring.used->idx)
		return NULL;

	VQUEUE_BUSY(vq);

	used_idx = vq->vq_used_cons_idx++ & (vq->vq_nentries - 1);
	uep = &vq->vq_ring.used->ring[used_idx];

	atomic_thread_fence(memory_order_seq_cst);

	/* Used.ring is written by slave, invalidate it */
	VRING_INVALIDATE(vq->vq_ring.used->ring[used_idx]);

	desc_idx = (uint16_t)uep->id;
	if (len)
		*len = uep->len;

	vq_ring_free_chain(vq, desc_idx);

	cookie = vq->vq_descx[desc_idx].cookie;
	vq->vq_descx[desc_idx].cookie = NULL;

	if (idx)
		*idx = used_idx;
	VQUEUE_IDLE(vq);

	return cookie;
}

uint32_t virtqueue_get_buffer_length(struct virtqueue *vq, uint16_t idx)
{
	VRING_INVALIDATE(vq->vq_ring.desc[idx].len);
	return vq->vq_ring.desc[idx].len;
}

/**
 * virtqueue_free   - Frees VirtIO queue resources
 *
 * @param vq        - Pointer to VirtIO queue control block
 *
 */
void virtqueue_free(struct virtqueue *vq)
{
	if (vq) {
		if (vq->vq_free_cnt != vq->vq_nentries) {
			metal_log(METAL_LOG_WARNING,
				  "%s: freeing non-empty virtqueue\r\n",
				  vq->vq_name);
		}

		metal_free_memory(vq);
	}
}

/**
 * virtqueue_get_available_buffer   - Returns buffer available for use in the
 *                                    VirtIO queue
 *
 * @param vq                        - Pointer to VirtIO queue control block
 * @param avail_idx                 - Pointer to index used in vring desc table
 * @param len                       - Length of buffer
 *
 * @return                          - Pointer to available buffer
 */
void *virtqueue_get_available_buffer(struct virtqueue *vq, uint16_t *avail_idx,
				     uint32_t *len)
{
	uint16_t head_idx = 0;
	void *buffer;

	atomic_thread_fence(memory_order_seq_cst);

	/* Avail.idx is updated by master, invalidate it */
	VRING_INVALIDATE(vq->vq_ring.avail->idx);
	if (vq->vq_available_idx == vq->vq_ring.avail->idx) {
		return NULL;
	}

	VQUEUE_BUSY(vq);

	/* Avail.ring is updated by master, invalidate it */
	VRING_INVALIDATE(vq->vq_ring.avail->ring[head_idx]);

	head_idx = vq->vq_available_idx++ & (vq->vq_nentries - 1);
	*avail_idx = vq->vq_ring.avail->ring[head_idx];

	/* Invalidate the desc entry written by master before accessing it */
	VRING_INVALIDATE(vq->vq_ring.desc[*avail_idx]);
	buffer = virtqueue_phys_to_virt(vq, vq->vq_ring.desc[*avail_idx].addr);
	*len = vq->vq_ring.desc[*avail_idx].len;

	VQUEUE_IDLE(vq);

	return buffer;
}

/**
 * virtqueue_add_consumed_buffer - Returns consumed buffer back to VirtIO queue
 *
 * @param vq                     - Pointer to VirtIO queue control block
 * @param head_idx               - Index of vring desc containing used buffer
 * @param len                    - Length of buffer
 *
 * @return                       - Function status
 */
int virtqueue_add_consumed_buffer(struct virtqueue *vq, uint16_t head_idx,
				  uint32_t len)
{
	struct vring_used_elem *used_desc = NULL;
	uint16_t used_idx;

	if (head_idx > vq->vq_nentries) {
		return ERROR_VRING_NO_BUFF;
	}

	VQUEUE_BUSY(vq);

	/* CACHE: used is never written by master, so it's safe to directly access it */
	used_idx = vq->vq_ring.used->idx & (vq->vq_nentries - 1);
	used_desc = &vq->vq_ring.used->ring[used_idx];
	used_desc->id = head_idx;
	used_desc->len = len;

	/* We still need to flush it because this is read by master */
	VRING_FLUSH(vq->vq_ring.used->ring[used_idx]);

	atomic_thread_fence(memory_order_seq_cst);

	vq->vq_ring.used->idx++;

	/* Used.idx is read by master, so we need to flush it */
	VRING_FLUSH(vq->vq_ring.used->idx);

	/* Keep pending count until virtqueue_notify(). */
	vq->vq_queued_cnt++;

	VQUEUE_IDLE(vq);

	return VQUEUE_SUCCESS;
}

/**
 * virtqueue_enable_cb  - Enables callback generation
 *
 * @param vq            - Pointer to VirtIO queue control block
 *
 * @return              - Function status
 */
int virtqueue_enable_cb(struct virtqueue *vq)
{
	return vq_ring_enable_interrupt(vq, 0);
}

/**
 * virtqueue_disable_cb - Disables callback generation
 *
 * @param vq           - Pointer to VirtIO queue control block
 *
 */
void virtqueue_disable_cb(struct virtqueue *vq)
{
	VQUEUE_BUSY(vq);

	if (vq->vq_dev->features & VIRTIO_RING_F_EVENT_IDX) {
#ifndef VIRTIO_SLAVE_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
			vring_used_event(&vq->vq_ring) =
			    vq->vq_used_cons_idx - vq->vq_nentries - 1;
			VRING_FLUSH(vring_used_event(&vq->vq_ring));
		}
#endif /*VIRTIO_SLAVE_ONLY*/
#ifndef VIRTIO_MASTER_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_SLAVE) {
			vring_avail_event(&vq->vq_ring) =
			    vq->vq_available_idx - vq->vq_nentries - 1;
			VRING_FLUSH(vring_avail_event(&vq->vq_ring));
		}
#endif /*VIRTIO_MASTER_ONLY*/
	} else {
#ifndef VIRTIO_SLAVE_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
			vq->vq_ring.avail->flags |= VRING_AVAIL_F_NO_INTERRUPT;
			VRING_FLUSH(vq->vq_ring.avail->flags);
		}
#endif /*VIRTIO_SLAVE_ONLY*/
#ifndef VIRTIO_MASTER_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_SLAVE) {
			vq->vq_ring.used->flags |= VRING_USED_F_NO_NOTIFY;
			VRING_FLUSH(vq->vq_ring.used->flags);
		}
#endif /*VIRTIO_MASTER_ONLY*/
	}

	VQUEUE_IDLE(vq);
}

/**
 * virtqueue_kick - Notifies other side that there is buffer available for it.
 *
 * @param vq      - Pointer to VirtIO queue control block
 */
void virtqueue_kick(struct virtqueue *vq)
{
	VQUEUE_BUSY(vq);

	/* Ensure updated avail->idx is visible to host. */
	atomic_thread_fence(memory_order_seq_cst);

	if (vq_ring_must_notify(vq))
		vq_ring_notify(vq);

	vq->vq_queued_cnt = 0;

	VQUEUE_IDLE(vq);
}

/**
 * virtqueue_dump Dumps important virtqueue fields , use for debugging purposes
 *
 * @param vq - Pointer to VirtIO queue control block
 */
void virtqueue_dump(struct virtqueue *vq)
{
	if (!vq)
		return;

	VRING_INVALIDATE(vq->vq_ring.avail);
	VRING_INVALIDATE(vq->vq_ring.used);

	metal_log(METAL_LOG_DEBUG,
		  "VQ: %s - size=%d; free=%d; queued=%d; "
		  "desc_head_idx=%d; avail.idx=%d; used_cons_idx=%d; "
		  "used.idx=%d; avail.flags=0x%x; used.flags=0x%x\r\n",
		  vq->vq_name, vq->vq_nentries, vq->vq_free_cnt,
		  vq->vq_queued_cnt, vq->vq_desc_head_idx,
		  vq->vq_ring.avail->idx, vq->vq_used_cons_idx,
		  vq->vq_ring.used->idx, vq->vq_ring.avail->flags,
		  vq->vq_ring.used->flags);
}

/**
 * virtqueue_get_desc_size - Returns vring descriptor size
 *
 * @param vq            - Pointer to VirtIO queue control block
 *
 * @return              - Descriptor length
 */
uint32_t virtqueue_get_desc_size(struct virtqueue *vq)
{
	uint16_t head_idx = 0;
	uint16_t avail_idx = 0;
	uint32_t len = 0;

	/* Avail.idx is updated by master, invalidate it */
	VRING_INVALIDATE(vq->vq_ring.avail->idx);

	if (vq->vq_available_idx == vq->vq_ring.avail->idx) {
		return 0;
	}

	VQUEUE_BUSY(vq);

	/* Avail.ring is updated by master, invalidate it */
	VRING_INVALIDATE(vq->vq_ring.avail->ring[head_idx]);

	head_idx = vq->vq_available_idx & (vq->vq_nentries - 1);
	avail_idx = vq->vq_ring.avail->ring[head_idx];

	/* Invalidate the desc entry written by master before accessing it */
	VRING_INVALIDATE(vq->vq_ring.desc[avail_idx].len);

	len = vq->vq_ring.desc[avail_idx].len;

	VQUEUE_IDLE(vq);

	return len;
}

/**************************************************************************
 *                            Helper Functions                            *
 **************************************************************************/

/**
 *
 * vq_ring_add_buffer
 *
 */
static uint16_t vq_ring_add_buffer(struct virtqueue *vq,
				   struct vring_desc *desc, uint16_t head_idx,
				   struct virtqueue_buf *buf_list, int readable,
				   int writable)
{
	struct vring_desc *dp;
	int i, needed;
	uint16_t idx;

	(void)vq;

	needed = readable + writable;

	for (i = 0, idx = head_idx; i < needed; i++, idx = dp->next) {
		VQASSERT(vq, idx != VQ_RING_DESC_CHAIN_END,
			 "premature end of free desc chain");

		/* CACHE: No need to invalidate desc because it is only written by master */
		dp = &desc[idx];
		dp->addr = virtqueue_virt_to_phys(vq, buf_list[i].buf);
		dp->len = buf_list[i].len;
		dp->flags = 0;

		if (i < needed - 1)
			dp->flags |= VRING_DESC_F_NEXT;

		/*
		 * Readable buffers are inserted  into vring before the
		 * writable buffers.
		 */
		if (i >= readable)
			dp->flags |= VRING_DESC_F_WRITE;

		/*
		 * Instead of flushing the whole desc region, we flush only the
		 * single entry hopefully saving some cycles
		 */
		VRING_FLUSH(desc[idx]);

	}

	return idx;
}

/**
 *
 * vq_ring_free_chain
 *
 */
static void vq_ring_free_chain(struct virtqueue *vq, uint16_t desc_idx)
{
	struct vring_desc *dp;
	struct vq_desc_extra *dxp;

	/* CACHE: desc is never written by slave, no need to invalidate */
	VQ_RING_ASSERT_VALID_IDX(vq, desc_idx);
	dp = &vq->vq_ring.desc[desc_idx];
	dxp = &vq->vq_descx[desc_idx];

	if (vq->vq_free_cnt == 0) {
		VQ_RING_ASSERT_CHAIN_TERM(vq);
	}

	vq->vq_free_cnt += dxp->ndescs;
	dxp->ndescs--;

	if ((dp->flags & VRING_DESC_F_INDIRECT) == 0) {
		while (dp->flags & VRING_DESC_F_NEXT) {
			VQ_RING_ASSERT_VALID_IDX(vq, dp->next);
			dp = &vq->vq_ring.desc[dp->next];
			dxp->ndescs--;
		}
	}

	VQASSERT(vq, dxp->ndescs == 0,
		 "failed to free entire desc chain, remaining");

	/*
	 * We must append the existing free chain, if any, to the end of
	 * newly freed chain. If the virtqueue was completely used, then
	 * head would be VQ_RING_DESC_CHAIN_END (ASSERTed above).
	 *
	 * CACHE: desc.next is never read by slave, no need to flush it.
	 */
	dp->next = vq->vq_desc_head_idx;
	vq->vq_desc_head_idx = desc_idx;
}

/**
 *
 * vq_ring_init
 *
 */
static void vq_ring_init(struct virtqueue *vq, void *ring_mem, int alignment)
{
	struct vring *vr;
	int size;

	size = vq->vq_nentries;
	vr = &vq->vq_ring;

	vring_init(vr, size, ring_mem, alignment);

#ifndef VIRTIO_SLAVE_ONLY
	if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
		int i;

		for (i = 0; i < size - 1; i++)
			vr->desc[i].next = i + 1;
		vr->desc[i].next = VQ_RING_DESC_CHAIN_END;
	}
#endif /*VIRTIO_SLAVE_ONLY*/
}

/**
 *
 * vq_ring_update_avail
 *
 */
static void vq_ring_update_avail(struct virtqueue *vq, uint16_t desc_idx)
{
	uint16_t avail_idx;

	/*
	 * Place the head of the descriptor chain into the next slot and make
	 * it usable to the host. The chain is made available now rather than
	 * deferring to virtqueue_notify() in the hopes that if the host is
	 * currently running on another CPU, we can keep it processing the new
	 * descriptor.
	 *
	 * CACHE: avail is never written by slave, so it is safe to not invalidate here
	 */
	avail_idx = vq->vq_ring.avail->idx & (vq->vq_nentries - 1);
	vq->vq_ring.avail->ring[avail_idx] = desc_idx;

	/* We still need to flush the ring */
	VRING_FLUSH(vq->vq_ring.avail->ring[avail_idx]);

	atomic_thread_fence(memory_order_seq_cst);

	vq->vq_ring.avail->idx++;

	/* And the index */
	VRING_FLUSH(vq->vq_ring.avail->idx);

	/* Keep pending count until virtqueue_notify(). */
	vq->vq_queued_cnt++;
}

/**
 *
 * vq_ring_enable_interrupt
 *
 */
static int vq_ring_enable_interrupt(struct virtqueue *vq, uint16_t ndesc)
{
	/*
	 * Enable interrupts, making sure we get the latest index of
	 * what's already been consumed.
	 */
	if (vq->vq_dev->features & VIRTIO_RING_F_EVENT_IDX) {
#ifndef VIRTIO_SLAVE_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
			vring_used_event(&vq->vq_ring) =
				vq->vq_used_cons_idx + ndesc;
			VRING_FLUSH(vring_used_event(&vq->vq_ring));
		}
#endif /*VIRTIO_SLAVE_ONLY*/
#ifndef VIRTIO_MASTER_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_SLAVE) {
			vring_avail_event(&vq->vq_ring) =
				vq->vq_available_idx + ndesc;
			VRING_FLUSH(vring_avail_event(&vq->vq_ring));
		}
#endif /*VIRTIO_MASTER_ONLY*/
	} else {
#ifndef VIRTIO_SLAVE_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
			vq->vq_ring.avail->flags &= ~VRING_AVAIL_F_NO_INTERRUPT;
			VRING_FLUSH(vq->vq_ring.avail->flags);
		}
#endif /*VIRTIO_SLAVE_ONLY*/
#ifndef VIRTIO_MASTER_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_SLAVE) {
			vq->vq_ring.used->flags &= ~VRING_USED_F_NO_NOTIFY;
			VRING_FLUSH(vq->vq_ring.used->flags);
		}
#endif /*VIRTIO_MASTER_ONLY*/
	}

	atomic_thread_fence(memory_order_seq_cst);

	/*
	 * Enough items may have already been consumed to meet our threshold
	 * since we last checked. Let our caller know so it processes the new
	 * entries.
	 */
#ifndef VIRTIO_SLAVE_ONLY
	if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
		if (virtqueue_nused(vq) > ndesc) {
			return 1;
		}
	}
#endif /*VIRTIO_SLAVE_ONLY*/
#ifndef VIRTIO_MASTER_ONLY
	if (vq->vq_dev->role == VIRTIO_DEV_SLAVE) {
		if (virtqueue_navail(vq) > ndesc) {
			return 1;
		}
	}
#endif /*VIRTIO_MASTER_ONLY*/

	return 0;
}

/**
 *
 * virtqueue_interrupt
 *
 */
void virtqueue_notification(struct virtqueue *vq)
{
	atomic_thread_fence(memory_order_seq_cst);
	if (vq->callback)
		vq->callback(vq);
}

/**
 *
 * vq_ring_must_notify
 *
 */
static int vq_ring_must_notify(struct virtqueue *vq)
{
	uint16_t new_idx, prev_idx, event_idx;

	if (vq->vq_dev->features & VIRTIO_RING_F_EVENT_IDX) {
#ifndef VIRTIO_SLAVE_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
			/* CACHE: no need to invalidate avail */
			new_idx = vq->vq_ring.avail->idx;
			prev_idx = new_idx - vq->vq_queued_cnt;
			VRING_INVALIDATE(vring_avail_event(&vq->vq_ring));
			event_idx = vring_avail_event(&vq->vq_ring);
			return vring_need_event(event_idx, new_idx,
						prev_idx) != 0;
		}
#endif /*VIRTIO_SLAVE_ONLY*/
#ifndef VIRTIO_MASTER_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_SLAVE) {
			/* CACHE: no need to invalidate used */
			new_idx = vq->vq_ring.used->idx;
			prev_idx = new_idx - vq->vq_queued_cnt;
			VRING_INVALIDATE(vring_used_event(&vq->vq_ring));
			event_idx = vring_used_event(&vq->vq_ring);
			return vring_need_event(event_idx, new_idx,
						prev_idx) != 0;
		}
#endif /*VIRTIO_MASTER_ONLY*/
	} else {
#ifndef VIRTIO_SLAVE_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_MASTER) {
			VRING_INVALIDATE(vq->vq_ring.used->flags);
			return (vq->vq_ring.used->flags &
				VRING_USED_F_NO_NOTIFY) == 0;
		}
#endif /*VIRTIO_SLAVE_ONLY*/
#ifndef VIRTIO_MASTER_ONLY
		if (vq->vq_dev->role == VIRTIO_DEV_SLAVE) {
			VRING_INVALIDATE(vq->vq_ring.avail->flags);
			return (vq->vq_ring.avail->flags &
				VRING_AVAIL_F_NO_INTERRUPT) == 0;
		}
#endif /*VIRTIO_MASTER_ONLY*/
	}

	return 0;
}

/**
 *
 * vq_ring_notify
 *
 */
static void vq_ring_notify(struct virtqueue *vq)
{
	if (vq->notify)
		vq->notify(vq);
}

/**
 *
 * virtqueue_nused
 *
 */
#ifndef VIRTIO_SLAVE_ONLY
static int virtqueue_nused(struct virtqueue *vq)
{
	uint16_t used_idx, nused;

	/* Used is written by slave */
	VRING_INVALIDATE(vq->vq_ring.used->idx);
	used_idx = vq->vq_ring.used->idx;

	nused = (uint16_t)(used_idx - vq->vq_used_cons_idx);
	VQASSERT(vq, nused <= vq->vq_nentries, "used more than available");

	return nused;
}
#endif /*VIRTIO_SLAVE_ONLY*/

/**
 *
 * virtqueue_navail
 *
 */
#ifndef VIRTIO_MASTER_ONLY
static int virtqueue_navail(struct virtqueue *vq)
{
	uint16_t avail_idx, navail;

	/* Avail is written by master */
	VRING_INVALIDATE(vq->vq_ring.avail->idx);

	avail_idx = vq->vq_ring.avail->idx;

	navail = (uint16_t)(avail_idx - vq->vq_available_idx);
	VQASSERT(vq, navail <= vq->vq_nentries, "avail more than available");

	return navail;
}
#endif /*VIRTIO_MASTER_ONLY*/
