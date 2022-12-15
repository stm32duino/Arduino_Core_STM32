/*
 * Copyright (c) 2021, L&T Technology Services Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RPMSG_RPC_DEMO_H
#define RPMSG_RPC_DEMO_H

#define OPEN_ID           0x1UL
#define CLOSE_ID          0x2UL
#define WRITE_ID          0x3UL
#define READ_ID           0x4UL
#define ACK_STATUS_ID     0x5UL
#define TERM_ID			  0x6UL
#define INPUT_ID          0x7UL
#define MAX_STRING_LEN    300
#define MAX_FILE_NAME_LEN 10

typedef int (*rpmsg_rpc_poll)(void *arg);

struct polling {
	rpmsg_rpc_poll poll;
	void *poll_arg;
};

struct rpmsg_rpc_req_open {
	char filename[MAX_FILE_NAME_LEN];
	int flags;
	int mode;
};

struct rpmsg_rpc_req_read {
	int fd;
	uint32_t buflen;
};

struct rpmsg_rpc_req_input {
	uint32_t buflen;
};

struct rpmsg_rpc_req_write {
	int fd;
	uint32_t len;
	char ptr[MAX_STRING_LEN];
};

struct rpmsg_rpc_req_close {
	int fd;
};

struct rpmsg_rpc_req_term {
	int id;
};

struct rpmsg_rpc_resp_open {
	int fd;
};

struct rpmsg_rpc_resp_read {
	int bytes_read;
	char buf[MAX_STRING_LEN];
};

struct rpmsg_rpc_resp_input {
	int bytes_read;
	char buf[MAX_STRING_LEN];
};

struct rpmsg_rpc_resp_write {
	int bytes_written;
};

struct rpmsg_rpc_resp_close {
	int close_ret;
};

#endif /* RPMSG_RPC_DEMO_H */
