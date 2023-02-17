/*
 * Copyright (c) 2021, L&T Technology Services Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*This is a sample demonstration application that showcases usage of proxy
 *from the remote core.
 *This application is meant to run on the remote CPU running linux.
 *This application can print to the master console and perform file I/O through
 *rpmsg channels.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <openamp/open_amp.h>
#include <openamp/rpmsg_rpc_client_server.h>
#include "platform_info.h"
#include "linux-rpmsg-rpc-demo.h"

#define REDEF_O_CREAT 100
#define REDEF_O_EXCL 200
#define REDEF_O_RDONLY 0
#define REDEF_O_WRONLY 1
#define REDEF_O_RDWR 2
#define REDEF_O_APPEND 2000
#define REDEF_O_ACCMODE 3

#define raw_printf(format, ...) printf(format, ##__VA_ARGS__)
#define LPRINTF(format, ...) raw_printf("Master> " format, ##__VA_ARGS__)
#define LPERROR(format, ...) LPRINTF("ERROR: " format, ##__VA_ARGS__)

static void *platform;
static struct rpmsg_device *rpdev;
static struct rpmsg_rpc_svr rpcs;
int request_termination;
int ept_deleted;

void rpmsg_service_server_unbind(struct rpmsg_endpoint *ept)
{
	(void)ept;
	rpmsg_destroy_ept(&rpcs.ept);
	LPRINTF("Endpoint is destroyed\r\n");
	ept_deleted = 1;
}

void terminate_rpc_app(void)
{
	LPRINTF("Destroying endpoint.\r\n");
	if (!ept_deleted)
		rpmsg_destroy_ept(&rpcs.ept);
}

void exit_action_handler(int signum)
{
	(void)signum;
	terminate_rpc_app();
}

void kill_action_handler(int signum)
{
	(void)signum;
	LPRINTF("RPC service killed !!\r\n");

	terminate_rpc_app();

	if (rpdev)
		platform_release_rpmsg_vdev(rpdev, platform);
	if (platform)
		platform_cleanup(platform);
}

int rpmsg_handle_open(void *data, struct rpmsg_rpc_svr *rpcs)
{
	void *req_ptr = data + MAX_FUNC_ID_LEN;
	struct rpmsg_rpc_req_open *rpc_open_req = req_ptr;
	char *buf;
	struct rpmsg_rpc_resp_open rpc_open_resp;
	int payload_size = sizeof(rpc_open_resp);
	struct rpmsg_endpoint *ept = &rpcs->ept;
	int fd, ret;

	if (!rpc_open_req || !ept)
		return -EINVAL;
	buf = rpc_open_req->filename;

	/* Open remote fd */
	fd = open(buf, rpc_open_req->flags, rpc_open_req->mode);

	/* Construct rpc response */
	rpc_open_resp.fd = fd;

	/* Transmit rpc response */
	ret = rpmsg_rpc_server_send(rpcs, OPEN_ID, RPMSG_RPC_OK, &rpc_open_resp,
				    payload_size);

	return ret > 0 ?  0 : ret;
}

int rpmsg_handle_close(void *data, struct rpmsg_rpc_svr *rpcs)
{
	void *req_ptr = data + MAX_FUNC_ID_LEN;
	struct rpmsg_rpc_req_close *rpc_close_req = req_ptr;
	struct rpmsg_rpc_resp_close rpc_close_resp;
	struct rpmsg_endpoint *ept = &rpcs->ept;
	int payload_size = sizeof(rpc_close_resp);
	int ret;

	if (!rpc_close_req || !ept)
		return -EINVAL;

	/* Close remote fd */
	ret = close(rpc_close_req->fd);

	/* Construct rpc response */
	rpc_close_resp.close_ret = ret;

	/* Transmit rpc response */
	ret = rpmsg_rpc_server_send(rpcs, CLOSE_ID, RPMSG_RPC_OK,
				    &rpc_close_resp, payload_size);

	return ret > 0 ?  0 : ret;
}

int rpmsg_handle_read(void *data, struct rpmsg_rpc_svr *rpcs)
{
	void *req_ptr = data + MAX_FUNC_ID_LEN;
	struct rpmsg_rpc_req_read *rpc_read_req = req_ptr;
	struct rpmsg_rpc_resp_read rpc_read_resp;
	struct rpmsg_endpoint *ept = &rpcs->ept;
	unsigned long int bytes_read;
	int payload_size = sizeof(rpc_read_resp);
	int ret;

	if (!rpc_read_req || !ept)
		return -EINVAL;

	if (rpc_read_req->fd == 0) {
		bytes_read = MAX_STRING_LEN;
		/* Perform read from fd for large size since this is a
		 * STD/I request
		 */
		bytes_read = read(rpc_read_req->fd, rpc_read_resp.buf,
				  bytes_read);
	} else {
		/* Perform read from fd */
		bytes_read = read(rpc_read_req->fd, rpc_read_resp.buf,
				  rpc_read_req->buflen);
	}

	/* Construct rpc response */
	rpc_read_resp.bytes_read = bytes_read;

	/* Transmit rpc response */
	ret = rpmsg_rpc_server_send(rpcs, READ_ID, RPMSG_RPC_OK, &rpc_read_resp,
				    payload_size);

	return ret > 0 ?  0 : ret;
}

int rpmsg_handle_write(void *data, struct rpmsg_rpc_svr *rpcs)
{
	void *req_ptr = data + MAX_FUNC_ID_LEN;
	struct rpmsg_rpc_req_write *rpc_write_req = req_ptr;
	struct rpmsg_rpc_resp_write rpc_write_resp;
	struct rpmsg_endpoint *ept = &rpcs->ept;
	int payload_size = sizeof(rpc_write_resp);
	int bytes_written;
	int ret;

	if (!rpc_write_req || !ept)
		return -EINVAL;

	/* Write to remote fd */
	bytes_written = write(rpc_write_req->fd, rpc_write_req->ptr,
			      rpc_write_req->len);

	/* Construct rpc response */
	rpc_write_resp.bytes_written = bytes_written;

	/* Transmit rpc response */
	ret = rpmsg_rpc_server_send(rpcs, WRITE_ID, RPMSG_RPC_OK,
				    &rpc_write_resp, payload_size);

	return ret > 0 ?  0 : ret;
}

int rpmsg_handle_input(void *data, struct rpmsg_rpc_svr *rpcs)
{
	void *req_ptr = data + MAX_FUNC_ID_LEN;
	struct rpmsg_rpc_req_input *rpc_input_req = req_ptr;
	struct rpmsg_rpc_resp_input rpc_input_resp;
	struct rpmsg_endpoint *ept = &rpcs->ept;
	int bytes_read;
	int payload_size = sizeof(rpc_input_resp);
	int ret;

	if (!rpc_input_req || !ept)
		return -EINVAL;

	/* Input from remote */
	scanf("%s", rpc_input_resp.buf);
	bytes_read = sizeof(rpc_input_resp.buf);

	/* Construct rpc response */
	rpc_input_resp.bytes_read = bytes_read;

	/* Transmit rpc response */
	ret = rpmsg_rpc_server_send(rpcs, INPUT_ID, RPMSG_RPC_OK,
				    &rpc_input_resp, payload_size);

	return ret > 0 ?  0 : ret;
}

int rpmsg_handle_term(void *data, struct rpmsg_rpc_svr *rpcs)
{
	void *req_ptr = data + MAX_FUNC_ID_LEN;
	struct rpmsg_rpc_req_term *rpc_term_req = req_ptr;
	struct rpmsg_endpoint *ept = &rpcs->ept;

	printf("Received termination request at id %d from endpoint %s\r\n",
	       rpc_term_req->id, ept->name);
	request_termination = 1;

	return 0;
}

/* Service table */
static struct rpmsg_rpc_services rpc_table[] = {
		{OPEN_ID, &rpmsg_handle_open },
		{READ_ID, &rpmsg_handle_read },
		{WRITE_ID, &rpmsg_handle_write },
		{CLOSE_ID, &rpmsg_handle_close },
		{INPUT_ID, &rpmsg_handle_input },
		{TERM_ID, &rpmsg_handle_term }
	};

/* Application entry point */
int app(struct rpmsg_device *rdev, void *priv)
{
	int ret = 0;
	struct sigaction exit_action;
	struct sigaction kill_action;

	/* Initialize signalling infrastructure */
	memset(&exit_action, 0, sizeof(struct sigaction));
	memset(&kill_action, 0, sizeof(struct sigaction));
	exit_action.sa_handler = exit_action_handler;
	kill_action.sa_handler = kill_action_handler;
	sigaction(SIGTERM, &exit_action, NULL);
	sigaction(SIGINT, &exit_action, NULL);
	sigaction(SIGKILL, &kill_action, NULL);
	sigaction(SIGHUP, &kill_action, NULL);

	/* Initialize RPMSG framework */
	LPRINTF("Try to create rpmsg endpoint.\r\n");

	ret = rpmsg_rpc_server_init(&rpcs, rdev, rpc_table,
				    (int)sizeof(rpc_table) / sizeof(
				    struct rpmsg_rpc_services),
				    rpmsg_service_server_unbind);

	if (ret) {
		LPERROR("Failed to create endpoint.\r\n");
		return -EINVAL;
	}

	LPRINTF("Successfully created rpmsg endpoint.\r\n");
	while (1) {
		platform_poll(priv);
		/* we got a shutdown request, exit */
		if (ept_deleted || request_termination) {
			break;
		}
	}
	LPRINTF("\nRPC service exiting !!\r\n");

	terminate_rpc_app();
	return ret;
}

int main(int argc, char *argv[])
{
	int ret;

	LPRINTF("Starting application...\r\n");

	/* Initialize platform */
	ret = platform_init(argc, argv, &platform);
	if (ret) {
		LPERROR("Failed to initialize platform.\r\n");
		ret = -1;
	} else {
		rpdev = platform_create_rpmsg_vdev(platform, 0,
						   VIRTIO_DEV_MASTER,
						   NULL, NULL);
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
