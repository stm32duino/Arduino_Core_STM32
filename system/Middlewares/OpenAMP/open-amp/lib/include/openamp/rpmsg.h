/*
 * Remote processor messaging
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 * All rights reserved.
 * Copyright (c) 2016 Freescale Semiconductor, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RPMSG_H_
#define _RPMSG_H_

#include <metal/compiler.h>
#include <metal/mutex.h>
#include <metal/list.h>
#include <metal/utilities.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#if defined __cplusplus
extern "C" {
#endif

/* Configurable parameters */
#define RPMSG_NAME_SIZE			(32)
#define RPMSG_ADDR_BMP_SIZE		(128)

#define RPMSG_NS_EPT_ADDR		(0x35)
#define RPMSG_RESERVED_ADDRESSES	(1024)
#define RPMSG_ADDR_ANY			0xFFFFFFFF

/* Error macros. */
#define RPMSG_SUCCESS			0
#define RPMSG_ERROR_BASE		-2000
#define RPMSG_ERR_NO_MEM		(RPMSG_ERROR_BASE - 1)
#define RPMSG_ERR_NO_BUFF		(RPMSG_ERROR_BASE - 2)
#define RPMSG_ERR_PARAM			(RPMSG_ERROR_BASE - 3)
#define RPMSG_ERR_DEV_STATE		(RPMSG_ERROR_BASE - 4)
#define RPMSG_ERR_BUFF_SIZE		(RPMSG_ERROR_BASE - 5)
#define RPMSG_ERR_INIT			(RPMSG_ERROR_BASE - 6)
#define RPMSG_ERR_ADDR			(RPMSG_ERROR_BASE - 7)

struct rpmsg_endpoint;
struct rpmsg_device;

/* Returns positive value on success or negative error value on failure */
typedef int (*rpmsg_ept_cb)(struct rpmsg_endpoint *ept, void *data,
			    size_t len, uint32_t src, void *priv);
typedef void (*rpmsg_ns_unbind_cb)(struct rpmsg_endpoint *ept);
typedef void (*rpmsg_ns_bind_cb)(struct rpmsg_device *rdev,
				 const char *name, uint32_t dest);

/**
 * struct rpmsg_endpoint - binds a local rpmsg address to its user
 * @name: name of the service supported
 * @rdev: pointer to the rpmsg device
 * @addr: local address of the endpoint
 * @dest_addr: address of the default remote endpoint binded.
 * @cb: user rx callback, return value of this callback is reserved
 *      for future use, for now, only allow RPMSG_SUCCESS as return value.
 * @ns_unbind_cb: end point service unbind callback, called when remote
 *                ept is destroyed.
 * @node: end point node.
 * @priv: private data for the driver's use
 *
 * In essence, an rpmsg endpoint represents a listener on the rpmsg bus, as
 * it binds an rpmsg address with an rx callback handler.
 */
struct rpmsg_endpoint {
	char name[RPMSG_NAME_SIZE];
	struct rpmsg_device *rdev;
	uint32_t addr;
	uint32_t dest_addr;
	rpmsg_ept_cb cb;
	rpmsg_ns_unbind_cb ns_unbind_cb;
	struct metal_list node;
	void *priv;
};

/**
 * struct rpmsg_device_ops - RPMsg device operations
 * @send_offchannel_raw: send RPMsg data
 * @hold_rx_buffer: hold RPMsg RX buffer
 * @release_rx_buffer: release RPMsg RX buffer
 * @get_tx_payload_buffer: get RPMsg TX buffer
 * @send_offchannel_nocopy: send RPMsg data without copy
 */
struct rpmsg_device_ops {
	int (*send_offchannel_raw)(struct rpmsg_device *rdev,
				   uint32_t src, uint32_t dst,
				   const void *data, int len, int wait);
	void (*hold_rx_buffer)(struct rpmsg_device *rdev, void *rxbuf);
	void (*release_rx_buffer)(struct rpmsg_device *rdev, void *rxbuf);
	void *(*get_tx_payload_buffer)(struct rpmsg_device *rdev,
				       uint32_t *len, int wait);
	int (*send_offchannel_nocopy)(struct rpmsg_device *rdev,
				      uint32_t src, uint32_t dst,
				       const void *data, int len);
};

/**
 * struct rpmsg_device - representation of a RPMsg device
 * @endpoints: list of endpoints
 * @ns_ept: name service endpoint
 * @bitmap: table endpoint address allocation.
 * @lock: mutex lock for rpmsg management
 * @ns_bind_cb: callback handler for name service announcement without local
 *              endpoints waiting to bind.
 * @ops: RPMsg device operations
 * @support_ns: create/destroy namespace message
 */
struct rpmsg_device {
	struct metal_list endpoints;
	struct rpmsg_endpoint ns_ept;
	unsigned long bitmap[metal_bitmap_longs(RPMSG_ADDR_BMP_SIZE)];
	metal_mutex_t lock;
	rpmsg_ns_bind_cb ns_bind_cb;
	struct rpmsg_device_ops ops;
	bool support_ns;
};

/**
 * rpmsg_send_offchannel_raw() - send a message across to the remote processor,
 * specifying source and destination address.
 * @ept: the rpmsg endpoint
 * @data: payload of the message
 * @len: length of the payload
 *
 * This function sends @data of length @len to the remote @dst address from
 * the source @src address.
 * The message will be sent to the remote processor which the channel belongs
 * to.
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
int rpmsg_send_offchannel_raw(struct rpmsg_endpoint *ept, uint32_t src,
			      uint32_t dst, const void *data, int len,
			      int wait);

/**
 * rpmsg_send() - send a message across to the remote processor
 * @ept: the rpmsg endpoint
 * @data: payload of the message
 * @len: length of the payload
 *
 * This function sends @data of length @len based on the @ept.
 * The message will be sent to the remote processor which the channel belongs
 * to, using @ept's source and destination addresses.
 * In case there are no TX buffers available, the function will block until
 * one becomes available, or a timeout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is returned.
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
static inline int rpmsg_send(struct rpmsg_endpoint *ept, const void *data,
			     int len)
{
	return rpmsg_send_offchannel_raw(ept, ept->addr, ept->dest_addr, data,
					 len, true);
}

/**
 * rpmsg_sendto() - send a message across to the remote processor, specify dst
 * @ept: the rpmsg endpoint
 * @data: payload of message
 * @len: length of payload
 * @dst: destination address
 *
 * This function sends @data of length @len to the remote @dst address.
 * The message will be sent to the remote processor which the @ept
 * channel belongs to, using @ept's source address.
 * In case there are no TX buffers available, the function will block until
 * one becomes available, or a timeout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is returned.
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
static inline int rpmsg_sendto(struct rpmsg_endpoint *ept, const void *data,
			       int len, uint32_t dst)
{
	return rpmsg_send_offchannel_raw(ept, ept->addr, dst, data, len, true);
}

/**
 * rpmsg_send_offchannel() - send a message using explicit src/dst addresses
 * @ept: the rpmsg endpoint
 * @src: source address
 * @dst: destination address
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len to the remote @dst address,
 * and uses @src as the source address.
 * The message will be sent to the remote processor which the @ept
 * channel belongs to.
 * In case there are no TX buffers available, the function will block until
 * one becomes available, or a timeout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is returned.
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
static inline int rpmsg_send_offchannel(struct rpmsg_endpoint *ept,
					uint32_t src, uint32_t dst,
					const void *data, int len)
{
	return rpmsg_send_offchannel_raw(ept, src, dst, data, len, true);
}

/**
 * rpmsg_trysend() - send a message across to the remote processor
 * @ept: the rpmsg endpoint
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len on the @ept channel.
 * The message will be sent to the remote processor which the @ept
 * channel belongs to, using @ept's source and destination addresses.
 * In case there are no TX buffers available, the function will immediately
 * return -ENOMEM without waiting until one becomes available.
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
static inline int rpmsg_trysend(struct rpmsg_endpoint *ept, const void *data,
				int len)
{
	return rpmsg_send_offchannel_raw(ept, ept->addr, ept->dest_addr, data,
					 len, false);
}

/**
 * rpmsg_trysendto() - send a message across to the remote processor,
 * specify dst
 * @ept: the rpmsg endpoint
 * @data: payload of message
 * @len: length of payload
 * @dst: destination address
 *
 * This function sends @data of length @len to the remote @dst address.
 * The message will be sent to the remote processor which the @ept
 * channel belongs to, using @ept's source address.
 * In case there are no TX buffers available, the function will immediately
 * return -ENOMEM without waiting until one becomes available.
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
static inline int rpmsg_trysendto(struct rpmsg_endpoint *ept, const void *data,
				  int len, uint32_t dst)
{
	return rpmsg_send_offchannel_raw(ept, ept->addr, dst, data, len, false);
}

/**
 * rpmsg_trysend_offchannel() - send a message using explicit src/dst addresses
 * @ept: the rpmsg endpoint
 * @src: source address
 * @dst: destination address
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len to the remote @dst address,
 * and uses @src as the source address.
 * The message will be sent to the remote processor which the @ept
 * channel belongs to.
 * In case there are no TX buffers available, the function will immediately
 * return -ENOMEM without waiting until one becomes available.
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
static inline int rpmsg_trysend_offchannel(struct rpmsg_endpoint *ept,
					   uint32_t src, uint32_t dst,
					   const void *data, int len)
{
	return rpmsg_send_offchannel_raw(ept, src, dst, data, len, false);
}

/**
 * @brief Holds the rx buffer for usage outside the receive callback.
 *
 * Calling this function prevents the RPMsg receive buffer from being released
 * back to the pool of shmem buffers. This API can only be called at rx
 * callback context (rpmsg_rx_cb_t). With this API, the application doesn't
 * need to copy the message in rx callback. Instead, the rx buffer base address
 * is saved in application context and further processed in application
 * process. After the message is processed, the application can release the rx
 * buffer for future reuse in vring by calling the rpmsg_release_rx_buffer()
 * function.
 *
 * @param: ept The rpmsg endpoint
 * @param: rxbuf RX buffer with message payload
 *
 * @see rpmsg_release_rx_buffer
 */
void rpmsg_hold_rx_buffer(struct rpmsg_endpoint *ept, void *rxbuf);

/**
 * @brief Releases the rx buffer for future reuse in vring.
 *
 * This API can be called at process context when the message in rx buffer is
 * processed.
 *
 * @ept: the rpmsg endpoint
 * @rxbuf: rx buffer with message payload
 *
 * @see rpmsg_hold_rx_buffer
 */
void rpmsg_release_rx_buffer(struct rpmsg_endpoint *ept, void *rxbuf);

/**
 * @brief Gets the tx buffer for message payload.
 *
 * This API can only be called at process context to get the tx buffer in vring.
 * By this way, the application can directly put its message into the vring tx
 * buffer without copy from an application buffer.
 * It is the application responsibility to correctly fill the allocated tx
 * buffer by data and passing correct parameters to the rpmsg_send_nocopy() or
 * rpmsg_sendto_nocopy() function to perform data no-copy-send mechanism.
 *
 * @ept:  Pointer to rpmsg endpoint
 * @len:  Pointer to store tx buffer size
 * @wait: Boolean, wait or not for buffer to become available
 *
 * @return The tx buffer address on success and NULL on failure
 *
 * @see rpmsg_send_offchannel_nocopy
 * @see rpmsg_sendto_nocopy
 * @see rpmsg_send_nocopy
 */
void *rpmsg_get_tx_payload_buffer(struct rpmsg_endpoint *ept,
				  uint32_t *len, int wait);

/**
 * rpmsg_send_offchannel_nocopy() - send a message in tx buffer reserved by
 * rpmsg_get_tx_payload_buffer() across to the remote processor.
 *
 * This function sends buf of length len to the remote dst address,
 * and uses src as the source address.
 * The message will be sent to the remote processor which the ept
 * endpoint belongs to.
 * The application has to take the responsibility for:
 *  1. tx buffer reserved (rpmsg_get_tx_payload_buffer() )
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the rpmsg_send_offchannel_nocopy() function is issued the tx buffer is
 * no more owned by the sending task and must not be touched anymore unless the
 * rpmsg_send_offchannel_nocopy() function fails and returns an error. In that
 * case application should try to re-issue the rpmsg_send_offchannel_nocopy()
 * again.
 *
 * @ept:  The rpmsg endpoint
 * @src:  The rpmsg endpoint local address
 * @dst:  The rpmsg endpoint remote address
 * @data: TX buffer with message filled
 * @len:  Length of payload
 *
 * @return number of bytes it has sent or negative error value on failure.
 *
 * @see rpmsg_get_tx_payload_buffer
 * @see rpmsg_sendto_nocopy
 * @see rpmsg_send_nocopy
 */
int rpmsg_send_offchannel_nocopy(struct rpmsg_endpoint *ept, uint32_t src,
				 uint32_t dst, const void *data, int len);

/**
 * @brief rpmsg_sendto_nocopy() - sends a message in tx buffer allocated by
 * rpmsg_get_tx_payload_buffer() across to the remote processor, specify dst.
 *
 * This function sends buf of length len to the remote dst address.
 * The message will be sent to the remote processor which the ept
 * endpoint belongs to, using ept's source address.
 * The application has to take the responsibility for:
 *  1. tx buffer allocation (rpmsg_get_tx_payload_buffer() )
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the rpmsg_sendto_nocopy() function is issued the tx buffer is no more
 * owned by the sending task and must not be touched anymore unless the
 * rpmsg_sendto_nocopy() function fails and returns an error. In that case the
 * application should try to re-issue the rpmsg_sendto_nocopy() again.
 *
 * @ept:  The rpmsg endpoint
 * @data: TX buffer with message filled
 * @len:  Length of payload
 * @dst:  Destination address
 *
 * @return number of bytes it has sent or negative error value on failure.
 *
 * @see rpmsg_get_tx_payload_buffer
 * @see rpmsg_send_offchannel_nocopy
 * @see rpmsg_send_nocopy
 */
static inline int rpmsg_sendto_nocopy(struct rpmsg_endpoint *ept,
				      const void *data, int len, uint32_t dst)
{
	return rpmsg_send_offchannel_nocopy(ept, ept->addr, dst, data, len);
}

/**
 * rpmsg_send_nocopy() - send a message in tx buffer reserved by
 * rpmsg_get_tx_payload_buffer() across to the remote processor.
 *
 * This function sends buf of length len on the ept endpoint.
 * The message will be sent to the remote processor which the ept
 * endpoint belongs to, using ept's source and destination addresses.
 * The application has to take the responsibility for:
 *  1. tx buffer reserved (rpmsg_get_tx_payload_buffer() )
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the rpmsg_send_nocopy() function is issued the tx buffer is no more
 * owned by the sending task and must not be touched anymore unless the
 * rpmsg_send_nocopy() function fails and returns an error. In that case the
 * application should try to re-issue the rpmsg_send_nocopy() again.
 *
 * @ept:  The rpmsg endpoint
 * @data: TX buffer with message filled
 * @len:  Length of payload
 *
 * @return number of bytes it has sent or negative error value on failure.
 *
 * @see rpmsg_get_tx_payload_buffer
 * @see rpmsg_send_offchannel_nocopy
 * @see rpmsg_sendto_nocopy
 */
static inline int rpmsg_send_nocopy(struct rpmsg_endpoint *ept,
				    const void *data, int len)
{
	return rpmsg_send_offchannel_nocopy(ept, ept->addr,
					    ept->dest_addr, data, len);
}

/**
 * rpmsg_init_ept - initialize rpmsg endpoint
 *
 * Initialize an RPMsg endpoint with a name, source address,
 * remoteproc address, endpoint callback, and destroy endpoint callback.
 *
 * API deprecated since release v2020.10
 *
 * @ept: pointer to rpmsg endpoint
 * @name: service name associated to the endpoint
 * @src: local address of the endpoint
 * @dest: target address of the endpoint
 * @cb: endpoint callback
 * @ns_unbind_cb: end point service unbind callback, called when remote ept is
 *                destroyed.
 */
__deprecated static inline void rpmsg_init_ept(struct rpmsg_endpoint *ept,
					       const char *name,
					       uint32_t src, uint32_t dest,
					       rpmsg_ept_cb cb,
					       rpmsg_ns_unbind_cb ns_unbind_cb)
{
	strncpy(ept->name, name ? name : "", sizeof(ept->name));
	ept->addr = src;
	ept->dest_addr = dest;
	ept->cb = cb;
	ept->ns_unbind_cb = ns_unbind_cb;
}

/**
 * rpmsg_create_ept - create rpmsg endpoint and register it to rpmsg device
 *
 * Create a RPMsg endpoint, initialize it with a name, source address,
 * remoteproc address, endpoint callback, and destroy endpoint callback,
 * and register it to the RPMsg device.
 *
 * @ept: pointer to rpmsg endpoint
 * @name: service name associated to the endpoint
 * @src: local address of the endpoint
 * @dest: target address of the endpoint
 * @cb: endpoint callback
 * @ns_unbind_cb: end point service unbind callback, called when remote ept is
 *                destroyed.
 *
 * In essence, an rpmsg endpoint represents a listener on the rpmsg bus, as
 * it binds an rpmsg address with an rx callback handler.
 *
 * Rpmsg client should create an endpoint to discuss with remote. rpmsg client
 * provide at least a channel name, a callback for message notification and by
 * default endpoint source address should be set to RPMSG_ADDR_ANY.
 *
 * As an option Some rpmsg clients can specify an endpoint with a specific
 * source address.
 */

int rpmsg_create_ept(struct rpmsg_endpoint *ept, struct rpmsg_device *rdev,
		     const char *name, uint32_t src, uint32_t dest,
		     rpmsg_ept_cb cb, rpmsg_ns_unbind_cb ns_unbind_cb);

/**
 * rpmsg_destroy_ept - destroy rpmsg endpoint and unregister it from rpmsg
 *                     device
 *
 * @ept: pointer to the rpmsg endpoint
 *
 * It unregisters the rpmsg endpoint from the rpmsg device and calls the
 * destroy endpoint callback if it is provided.
 */
void rpmsg_destroy_ept(struct rpmsg_endpoint *ept);

/**
 * is_rpmsg_ept_ready - check if the rpmsg endpoint ready to send
 *
 * @ept: pointer to rpmsg endpoint
 *
 * Returns 1 if the rpmsg endpoint has both local addr and destination
 * addr set, 0 otherwise
 */
static inline unsigned int is_rpmsg_ept_ready(struct rpmsg_endpoint *ept)
{
	return ept && ept->rdev && ept->dest_addr != RPMSG_ADDR_ANY;
}

#if defined __cplusplus
}
#endif

#endif				/* _RPMSG_H_ */
