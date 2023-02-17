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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <openamp/open_amp.h>
#include <openamp/rpmsg_rpc_client_server.h>
#include "rsc_table.h"
#include "platform_info.h"
#include "linux-rpmsg-rpc-demo.h"

#define REDEF_O_CREAT   0000100
#define REDEF_O_EXCL    0000200
#define REDEF_O_RDONLY  0000000
#define REDEF_O_WRONLY  0000001
#define REDEF_O_RDWR    0000002
#define REDEF_O_APPEND  0002000
#define REDEF_O_ACCMODE 0000003

#define LPRINTF(format, ...) printf(format, ##__VA_ARGS__)
#define LPERROR(format, ...) LPRINTF("ERROR: " format, ##__VA_ARGS__)

static struct rpmsg_rpc_clt *rpmsg_default_rpc;
static int fd, bytes_written, bytes_read;
static struct polling poll;
static atomic_int wait_resp;

static void rpmsg_rpc_shutdown(struct rpmsg_rpc_clt *rpc)
{
	(void)rpc;
	LPRINTF("RPMSG RPC is shutting down.\r\n");
}

void linux_rpmsg_set_default_rpc(struct rpmsg_rpc_clt *rpc)
{
	if (!rpc)
		return;
	rpmsg_default_rpc = rpc;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_open_cb
 *
 *   DESCRIPTION
 *
 *       Callback function of rpmsg_open
 *
 *************************************************************************/
void rpmsg_open_cb(struct rpmsg_rpc_clt *rpc, int status, void *data,
		   size_t len)
{
	struct rpmsg_rpc_resp_open *resp =
	(struct rpmsg_rpc_resp_open *)data;
	(void)len;
	(void)rpc;

	/* Assign value from return args */
	if (status)
		fd = 0;
	else
		fd = resp->fd;

	/* to clear the flag set in the caller function */
	atomic_flag_clear(&wait_resp);

}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_open
 *
 *   DESCRIPTION
 *
 *       Open a file.
 *
 *************************************************************************/
int rpmsg_open(const char *filename, int flags, int mode)
{
	struct rpmsg_rpc_clt *rpc = rpmsg_default_rpc;
	struct rpmsg_rpc_req_open rpc_open_req;
	int filename_len = strlen(filename) + 1;
	unsigned int payload_size = sizeof(rpc_open_req);

	if (!filename || payload_size > (int)MAX_BUF_LEN || !rpc) {
		return -EINVAL;
	}

	/* Construct rpc payload */
	rpc_open_req.flags = flags;
	rpc_open_req.mode = mode;
	memcpy(rpc_open_req.filename, filename, filename_len);

	/* flag set to wait for response from endpoint callback */
	(void)atomic_flag_test_and_set(&wait_resp);

	/* Trying to send until the endpoint is ready */
	while (rpmsg_rpc_client_send(rpc, OPEN_ID, &rpc_open_req, payload_size)
	       < 0) {
		if (poll.poll)
			poll.poll(poll.poll_arg);
	}

	/* waiting to get response from endpoint callback */
	while ((atomic_flag_test_and_set(&wait_resp))) {
		if (poll.poll)
			poll.poll(poll.poll_arg);
	}

	return 0;
}

static char *read_req_buffer;

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_read_cb
 *
 *   DESCRIPTION
 *
 *       Callback function of rpmsg_read
 *
 *************************************************************************/
void rpmsg_read_cb(struct rpmsg_rpc_clt *rpc, int status, void *data,
		   size_t len)
{
	struct rpmsg_rpc_resp_read *resp =
	(struct rpmsg_rpc_resp_read *)data;
	(void)len;
	(void)rpc;

	if (status) {
		bytes_read = 0;
		goto out;
	}

	/* Assign value from return args */
	if (resp->bytes_read > 0) {
		memcpy(read_req_buffer, resp->buf, sizeof(resp->buf));
	}
	bytes_read = resp->bytes_read;

out:
	/* to clear the flag set in the caller function */
	atomic_flag_clear(&wait_resp);
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_read
 *
 *   DESCRIPTION
 *
 *       Read data through RPMsg channel
 *
 *	return the number of data read, à in error case
 *************************************************************************/
int rpmsg_read(int fd, char *buffer, int buflen)
{
	struct rpmsg_rpc_clt *rpc = rpmsg_default_rpc;
	struct rpmsg_rpc_req_read rpc_read_req;
	unsigned int payload_size = sizeof(rpc_read_req);
	int ret;

	if (!rpc || !buffer || buflen == 0)
		return -EINVAL;

	/* store buffer address and size  for the callback */
	read_req_buffer = buffer;
	bytes_read = 0;

	/* Construct rpc payload */
	rpc_read_req.fd = fd;
	rpc_read_req.buflen = buflen;

	/* flag set to wait for response from endpoint callback */
	(void)atomic_flag_test_and_set(&wait_resp);

	ret = rpmsg_rpc_client_send(rpc, READ_ID, &rpc_read_req, payload_size);
	if (ret < 0)
		return 0;

	/* waiting to get response from endpoint callback */
	while ((atomic_flag_test_and_set(&wait_resp))) {
		if (poll.poll)
			poll.poll(poll.poll_arg);
	}

	return bytes_read;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_write_cb
 *
 *   DESCRIPTION
 *
 *       Callback function of rpmsg_write
 *
 *************************************************************************/
void rpmsg_write_cb(struct rpmsg_rpc_clt *rpc, int status, void *data,
		    size_t len)
{
	struct rpmsg_rpc_resp_write *resp =
	(struct rpmsg_rpc_resp_write *)data;
	(void)len;
	(void)rpc;

	if (status)
		bytes_written = 0;
	else
		/* Assign value from return args */
		bytes_written = resp->bytes_written;

	/* to clear the flag set in the caller function */
	atomic_flag_clear(&wait_resp);
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_write
 *
 *   DESCRIPTION
 *
 *       Write data through RPMsg channel
 *
 *	 return the number of data written, à in error case
 *************************************************************************/
int rpmsg_write(int fd, char *ptr, int len)
{
	struct rpmsg_rpc_clt *rpc = rpmsg_default_rpc;
	struct rpmsg_rpc_req_write rpc_write_req;
	unsigned int payload_size = sizeof(rpc_write_req);
	int ret;

	if (!rpc)
		return -EINVAL;

	bytes_written = 0;

	/* Construct rpc payload */
	rpc_write_req.fd = fd;
	memcpy(rpc_write_req.ptr, ptr, len + 1);
	rpc_write_req.len = len;

	/* flag set to wait for response from endpoint callback */
	(void)atomic_flag_test_and_set(&wait_resp);

	ret = rpmsg_rpc_client_send(rpc, WRITE_ID, &rpc_write_req,
				    payload_size);
	if (ret < 0)
		return 0;

	/* waiting to get response from endpoint callback */
	while ((atomic_flag_test_and_set(&wait_resp))) {
		if (poll.poll)
			poll.poll(poll.poll_arg);
	}

	return bytes_written;

}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_close_cb
 *
 *   DESCRIPTION
 *
 *       Callback function of rpmsg_close
 *
 *************************************************************************/
void rpmsg_close_cb(struct rpmsg_rpc_clt *rpc, int status, void *data,
		    size_t len)
{
	(void)rpc;
	(void)status;
	(void)data;
	(void)len;

	/* to clear the flag set in the caller function */
	atomic_flag_clear(&wait_resp);
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_close
 *
 *   DESCRIPTION
 *
 *       Close a file.
 *
 *************************************************************************/
int rpmsg_close(int fd)
{
	struct rpmsg_rpc_clt *rpc = rpmsg_default_rpc;
	struct rpmsg_rpc_req_close rpc_close_req;
	unsigned int payload_size = sizeof(rpc_close_req);
	int ret;

	if (!rpc)
		return -EINVAL;

	/* Construct rpc payload */
	rpc_close_req.fd = fd;

	/* flag set to wait for response from endpoint callback */
	(void)atomic_flag_test_and_set(&wait_resp);

	ret = rpmsg_rpc_client_send(rpc, CLOSE_ID, &rpc_close_req,
				    payload_size);

	/* waiting to get response from endpoint callback */
	while ((atomic_flag_test_and_set(&wait_resp))) {
		if (poll.poll)
			poll.poll(poll.poll_arg);
	}

	return ret;
}

static char *input_req_buffer;

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_input_cb
 *
 *   DESCRIPTION
 *
 *       Callback function of rpmsg_input
 *
 *************************************************************************/
void rpmsg_input_cb(struct rpmsg_rpc_clt *rpc, int status, void *data,
		    size_t len)
{
	struct rpmsg_rpc_resp_input *resp =
	(struct rpmsg_rpc_resp_input *)data;
	(void)len;
	(void)rpc;

	if (status) {
		bytes_read = 0;
		goto out;
	}

	/* Assign value from return args */
	if (resp->bytes_read > 0) {
		memcpy(input_req_buffer, resp->buf, sizeof(resp->buf));
	}

	bytes_read = resp->bytes_read;

out:
	/* to clear the flag set in the caller function */
	atomic_flag_clear(&wait_resp);

}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       rpmsg_input
 *
 *   DESCRIPTION
 *
 *       Read input through RPMsg channel
 *
 *	 return the number of byte read, 0 in error case
 *************************************************************************/
int rpmsg_input(char *buffer, int buflen)
{
	struct rpmsg_rpc_clt *rpc = rpmsg_default_rpc;
	struct rpmsg_rpc_req_input rpc_input_req;
	unsigned int payload_size = sizeof(rpc_input_req);
	int ret;

	if (!rpc || !buffer || buflen == 0)
		return -EINVAL;

	/* store buffer address and size  for the callback */
	input_req_buffer = buffer;
	bytes_read = 0;

	/* Construct rpc payload */
	rpc_input_req.buflen = buflen;

	/* flag set to wait for response from endpoint callback */
	(void)atomic_flag_test_and_set(&wait_resp);
	ret = rpmsg_rpc_client_send(rpc, INPUT_ID, &buflen, payload_size);
	if (ret < 0)
		return 0;

	/* waiting to get response from endpoint callback */
	while ((atomic_flag_test_and_set(&wait_resp))) {
		if (poll.poll)
			poll.poll(poll.poll_arg);
	}

	return bytes_read;
}

/* Mapping ID with Callbacks into table */
static const struct rpmsg_rpc_client_services rpc_table[] = {
		{OPEN_ID, &rpmsg_open_cb },
		{READ_ID, &rpmsg_read_cb },
		{WRITE_ID, &rpmsg_write_cb },
		{CLOSE_ID, &rpmsg_close_cb },
		{INPUT_ID, &rpmsg_input_cb }
	};
/*-----------------------------------------------------------------------------
 *
 *  Application specific
 *
 *-----------------------------------------------------------------------------
 */
int app(struct rpmsg_device *rdev, void *priv)
{
	struct rpmsg_rpc_clt rpc;
	struct rpmsg_rpc_req_term rpccall;

	poll.poll = platform_poll;
	poll.poll_arg = priv;
	char *fname = "remote.file";
	char wbuff[50];
	char rbuff[300];
	char ubuff[50];
	char idata[50];
	char fdata[50];
	int table_len;
	int ret;

	/* redirect I/Os */
	LPRINTF("Initializating I/Os redirection...\r\n");
	table_len = (int)sizeof(rpc_table) / sizeof(struct rpmsg_rpc_services);
	atomic_init(&wait_resp, 1);

	ret = rpmsg_rpc_client_init(&rpc, rdev,
				    rpmsg_rpc_shutdown, rpc_table, table_len);
	linux_rpmsg_set_default_rpc(&rpc);

	if (ret) {
		LPRINTF("Failed to initialize rpmsg rpc\r\n");
		return -1;
	}

	printf("\nRemote>Linux Remote Procedure Call (RPC) Demonstration\r\n");
	printf("\nRemote>***************************************************"
	"\r\n");

	printf("\nRemote>Rpmsg based retargetting to proxy initialized..\r\n");

	/* Remote performing file IO on Master */
	printf("\nRemote>FileIO demo ..\r\n");

	printf("\nRemote>Creating a file on master and writing to it..\r\n");
	rpmsg_open(fname, REDEF_O_CREAT | REDEF_O_WRONLY | REDEF_O_APPEND,
		   S_IRUSR | S_IWUSR);
	printf("\nRemote>Opened file '%s' with fd = %d\r\n", fname, fd);
	sprintf(wbuff, "This is a test string being written to file..");
	rpmsg_write(fd, wbuff, strlen(wbuff));
	printf("\nRemote>Wrote to fd = %d, size = %d, content = %s\r\n", fd,
	       bytes_written, wbuff);
	rpmsg_close(fd);
	printf("\nRemote>Closed fd = %d\r\n", fd);

	/* Remote performing file IO on Master */
	printf("\nRemote>Reading a file on master and displaying its "
	"contents..\r\n");
	rpmsg_open(fname, REDEF_O_RDONLY, S_IRUSR | S_IWUSR);
	printf("\nRemote>Opened file '%s' with fd = %d\r\n", fname, fd);
	rpmsg_read(fd, rbuff, sizeof(rbuff));
	*(char *)(&rbuff[0] + bytes_read) = 0;
	printf("\nRemote>Read from fd = %d, size = %d, "
	"printing contents below .. %s\r\n", fd, bytes_read, rbuff);
	rpmsg_close(fd);
	printf("\nRemote>Closed fd = %d\r\n", fd);

	while (1) {
		/* Remote performing STDIO on Master */
		printf("\nRemote>Remote firmware using scanf and printf .."
		"\r\n");
		printf("\nRemote>Scanning user input from master..\r\n");
		printf("\nRemote>Enter name\r\n");
		rpmsg_input(ubuff, sizeof(ubuff));
		ret = bytes_read;
		if (ret) {
			printf("\nRemote>Enter age\r\n");
			rpmsg_input(idata, sizeof(idata));
			ret = bytes_read;
			if (ret) {
				printf("\nRemote>Enter value for pi\r\n");
				rpmsg_input(fdata, sizeof(fdata));
				ret = bytes_read;
				if (ret) {
					printf("\nRemote>User name = '%s'"
					"\r\n", ubuff);
					printf("\nRemote>User age = '%s'\r\n",
					       idata);
					printf("\nRemote>User entered value of "
					"pi = '%s'\r\n", fdata);
				}
			}
		}
		if (!ret) {
			rpmsg_input(ubuff, sizeof(ubuff));
			printf("Remote> Invalid value. Starting again....");
		} else {
			printf("\nRemote>Repeat demo ? (enter yes or no) \r\n");
			scanf("%s", ubuff);
			if ((strcmp(ubuff, "no")) && (strcmp(ubuff, "yes"))) {
				printf("\nRemote>Invalid option. Starting again"
				"....\r\n");
			} else if ((!strcmp(ubuff, "no"))) {
				printf("\nRemote>RPC retargetting quitting ..."
				"\r\n");
				break;
			}
		}
	}

	printf("\nRemote> Firmware's rpmsg-rpc-channel going down! \r\n");
	rpccall.id = TERM_ID;
	(void)rpmsg_rpc_client_send(&rpc, TERM_ID, &rpccall, sizeof(rpccall));

	LPRINTF("Release remoteproc procedure call\r\n");
	rpmsg_rpc_client_release(&rpc);
	return 0;
}

/*-----------------------------------------------------------------------------*
 *  Application entry point
 *-----------------------------------------------------------------------------
 */

int main(int argc, char *argv[])
{
	void *platform;
	struct rpmsg_device *rpdev;
	int ret;

	LPRINTF("Starting application...\r\n");

	/* Initialize platform */
	ret = platform_init(argc, argv, &platform);
	if (ret) {
		LPERROR("Failed to initialize platform.\r\n");
		ret = -1;
	} else {
		rpdev = platform_create_rpmsg_vdev(platform, 0,
						   VIRTIO_DEV_SLAVE,
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
