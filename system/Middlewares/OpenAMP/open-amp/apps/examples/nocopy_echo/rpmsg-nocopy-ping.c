/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2020, Xiaomi Inc. All rights reserved.
 * Copyright (c) 2020, STMicroelectronics
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openamp/open_amp.h>
#include <metal/alloc.h>
#include "platform_info.h"
#include "rpmsg-echo.h"

#define LPRINTF(format, ...) printf(format, ##__VA_ARGS__)
#define LPERROR(format, ...) LPRINTF("ERROR: " format, ##__VA_ARGS__)

struct _payload {
	unsigned long num;
	unsigned long size;
	unsigned char data[];
};

struct rpmsg_rcv_msg {
	struct _payload *payload;
	size_t len;
	struct rpmsg_endpoint *ept;
};

static int err_cnt;
static struct rpmsg_rcv_msg rcv_msg;

#define PAYLOAD_MIN_SIZE	1

/* Globals */
static struct rpmsg_endpoint lept;
static int rnum;
static int err_cnt;
static int ept_deleted;

static int rpmsg_check_rcv_msg(struct rpmsg_rcv_msg *rcv_msg, uint32_t exp_num)
{
	int i, ret = RPMSG_SUCCESS;
	struct _payload *r_payload = rcv_msg->payload;

	if (r_payload->num != exp_num) {
		LPERROR("Invalid message number received %ld, expected %d\r\n",
			r_payload->num, exp_num);
		ret = RPMSG_ERR_PARAM;
		goto out;
	}

	if (r_payload->size == 0) {
		LPERROR(" Invalid size of package is received.\r\n");
		ret = RPMSG_ERR_PARAM;
		goto out;
	}

	/* Validate data buffer integrity. */
	for (i = 0; i < (int)r_payload->size; i++) {
		if (r_payload->data[i] != 0xA5) {
			LPRINTF("Data corruption at index %d\r\n", i);
			ret = RPMSG_ERR_PARAM;
			goto out;
		}
	}
out:
	rpmsg_release_rx_buffer(rcv_msg->ept, r_payload);

	return ret;
}

static int rpmsg_endpoint_cb(struct rpmsg_endpoint *ept, void *data, size_t len,
			     uint32_t src, void *priv)
{
	(void)src;
	(void)priv;

	rpmsg_hold_rx_buffer(ept, data);
	rcv_msg.ept = ept;
	rcv_msg.payload =  (struct _payload *)data;
	rcv_msg.len = len;

	LPRINTF(" received payload number %lu of size %lu \r\n",
		rcv_msg.payload->num, (unsigned long)len);

	rnum = rcv_msg.payload->num + 1;
	return RPMSG_SUCCESS;
}

static void rpmsg_service_unbind(struct rpmsg_endpoint *ept)
{
	(void)ept;
	rpmsg_destroy_ept(&lept);
	LPRINTF("echo test: service is destroyed\r\n");
	ept_deleted = 1;
}

static void rpmsg_name_service_bind_cb(struct rpmsg_device *rdev,
				       const char *name, uint32_t dest)
{
	LPRINTF("new endpoint notification is received.\r\n");
	if (strcmp(name, RPMSG_SERVICE_NAME))
		LPERROR("Unexpected name service %s.\r\n", name);
	else
		(void)rpmsg_create_ept(&lept, rdev, RPMSG_SERVICE_NAME,
				       RPMSG_ADDR_ANY, dest,
				       rpmsg_endpoint_cb,
				       rpmsg_service_unbind);

}

static int app(struct rpmsg_device *rdev, void *priv)
{
	int ret;
	int i, num_payloads;
	uint32_t size, max_size;
	int expect_rnum = 0;

	LPRINTF(" 1 - Send data to remote core, retrieve the echo");
	LPRINTF(" and validate its integrity ..\r\n");

	max_size = rpmsg_virtio_get_buffer_size(rdev);
	if ((int32_t)max_size < 0) {
		LPERROR("No available buffer size.\r\n");
		return -1;
	}
	max_size -= sizeof(struct _payload);
	num_payloads = max_size - PAYLOAD_MIN_SIZE + 1;

	/* Create RPMsg endpoint */
	ret = rpmsg_create_ept(&lept, rdev, RPMSG_SERVICE_NAME,
			       RPMSG_ADDR_ANY, RPMSG_ADDR_ANY,
			       rpmsg_endpoint_cb, rpmsg_service_unbind);

	if (ret) {
		LPERROR("Failed to create RPMsg endpoint.\r\n");
		return ret;
	}

	while (!is_rpmsg_ept_ready(&lept))
		platform_poll(priv);

	LPRINTF("RPMSG endpoint is binded with remote.\r\n");
	for (i = 0, size = PAYLOAD_MIN_SIZE; i < num_payloads; i++, size++) {
		struct _payload *i_payload;

		i_payload = rpmsg_get_tx_payload_buffer(&lept, &max_size, 1);
		if (!i_payload) {
			LPERROR("Failed to get payload...\r\n");
			break;
		}

		i_payload->num = i;
		i_payload->size = size;

		/* Mark the data buffer. */
		memset(&i_payload->data[0], 0xA5, size);

		LPRINTF("sending payload number %lu of size %lu\r\n",
			i_payload->num,
			(unsigned long)(2 * sizeof(unsigned long)) + size);

		ret = rpmsg_send_nocopy(&lept, i_payload,
					(2 * sizeof(unsigned long)) + size);

		if (ret < 0) {
			LPERROR("Failed to send data...\r\n");
			break;
		}
		LPRINTF("echo test: sent : %lu\r\n",
			(unsigned long)(2 * sizeof(unsigned long)) + size);

		expect_rnum++;
		do {
			platform_poll(priv);
		} while ((rnum < expect_rnum) && !ept_deleted);

		if (ept_deleted)
			break;
		if (rpmsg_check_rcv_msg(&rcv_msg, expect_rnum - 1))
			err_cnt++;
	}

	LPRINTF("**********************************\r\n");
	LPRINTF(" Test Results: Error count = %d \r\n", err_cnt);
	LPRINTF("**********************************\r\n");
	/* Destroy the RPMsg endpoint */
	rpmsg_destroy_ept(&lept);
	LPRINTF("Quitting application .. Echo test end\r\n");

	return 0;
}

int main(int argc, char *argv[])
{
	void *platform;
	struct rpmsg_device *rpdev;
	int ret;

	/* Initialize platform */
	ret = platform_init(argc, argv, &platform);
	if (ret) {
		LPERROR("Failed to initialize platform.\r\n");
		ret = -1;
	} else {
		rpdev = platform_create_rpmsg_vdev(platform, 0,
						   VIRTIO_DEV_MASTER,
						   NULL,
						   rpmsg_name_service_bind_cb);
		if (!rpdev) {
			LPERROR("Failed to create rpmsg virtio device.\r\n");
			ret = -1;
		} else {
			app(rpdev, platform);
			platform_release_rpmsg_vdev(rpdev, platform);
			ret = 0;
		}
	}

	LPRINTF("Stopping application...\r\n");
	platform_cleanup(platform);

	return ret;
}
