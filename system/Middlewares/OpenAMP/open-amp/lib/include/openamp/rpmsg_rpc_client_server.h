/*
 * Copyright (c) 2021, L&T Technology Services Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RPMSG_RPC_CLIENT_SERVER_H
#define RPMSG_RPC_CLIENT_SERVER_H

#include <openamp/open_amp.h>
#include <metal/compiler.h>

#if defined __cplusplus
extern "C" {
#endif

#define RPMSG_RPC_OK		0
#define RPMSG_RPC_INVALID_ID	(-1L)
#define RPMSG_RPC_SERVICE_NAME "rpmsg-rpc"

/* RPMSG_BUFFER_SIZE = 512
 * sizeof(struct rpmsg_hdr) = 16
 * RPMSG_BUFFER_SIZE - sizeof(struct rpmsg_hdr) - 1 = 495
 * Aligning to 64 bits -> 488UL
 */
#define MAX_BUF_LEN	488UL
#define MAX_FUNC_ID_LEN sizeof(unsigned long int)

struct rpmsg_rpc_clt;
struct rpmsg_rpc_svr;

typedef void (*rpmsg_rpc_shutdown_cb)(struct rpmsg_rpc_clt *rpc);
typedef void (*app_cb)(struct rpmsg_rpc_clt *rpc, int statust, void *data,
		       size_t len);
typedef int (*rpmsg_rpc_syscall_cb)(void *data, struct rpmsg_rpc_svr *rpcs);

/**
 * struct rpmsg_rpc_request - rpc request message
 *
 * @id: service id
 * @params: request params
 *
 */
struct rpmsg_rpc_request {
	uint32_t id;
	unsigned char params[MAX_BUF_LEN];
};

/**
 * struct rpmsg_rpc_answer - rpc request message
 *
 * @id: service id
 * @status: status of rpc
 * @params: answer params
 *
 */
METAL_PACKED_BEGIN
struct rpmsg_rpc_answer {
	uint32_t id;
	int32_t status;
	unsigned char params[MAX_BUF_LEN];
} METAL_PACKED_END;

/**
 * struct rpmsg_rpc_services - table for services
 *
 * @id: service id
 * @cb_function: id callback
 *
 */
struct rpmsg_rpc_services {
	uint32_t id;
	rpmsg_rpc_syscall_cb cb_function;
};

/**
 * struct rpmsg_rpc_client_services - table for client services
 *
 * @id: service id
 * @app_cb: id callback
 *
 */
struct rpmsg_rpc_client_services {
	uint32_t id;
	app_cb cb;
};

/**
 * struct rpmsg_rpc_svr - server remote procedure call data
 *
 * RPMsg RPC will send request to endpoint
 *
 * @ept: rpmsg_endpoint structure
 * @services: service table
 * @n_services: number of services
 *
 */
struct rpmsg_rpc_svr {
	struct rpmsg_endpoint ept;
	const struct rpmsg_rpc_services *services;
	unsigned int n_services;
};

/**
 * struct rpmsg_rpc_clt - client remote procedure call data
 *
 * RPMsg RPC will send request to remote and
 * wait for callback.
 *
 * @ept: rpmsg_endpoint structure
 * @shutdown_cb: shutdown callback function
 * @services: service table
 * @n_services: number of services
 *
 */
struct rpmsg_rpc_clt {
	struct rpmsg_endpoint ept;
	rpmsg_rpc_shutdown_cb shutdown_cb;
	const struct rpmsg_rpc_client_services *services;
	unsigned int n_services;
};

/**
 * rpmsg_rpc_client_release - release RPMsg remote procedure call
 *
 * This function is to release remoteproc procedure call service
 *
 * @rpc: pointer to the client remote procedure call data
 *
 */
void rpmsg_rpc_client_release(struct rpmsg_rpc_clt *rpc);

/**
 * rpmsg_rpc_client_init - initialize RPMsg remote procedure call
 *
 * This function is to initialize the remote procedure call
 * client data. RPMsg RPC will send request to remote and
 * wait for callback and load services to table
 *
 * @rpc: pointer to the client remote procedure call data
 * @rdev: pointer to the rpmsg device
 * @shutdown_cb: shutdown callback function
 * @services: pointer to service table
 * @len: length of table
 *
 * return 0 for success, and negative value for failure
 */
int rpmsg_rpc_client_init(struct rpmsg_rpc_clt *rpc,
			  struct rpmsg_device *rdev,
			  rpmsg_rpc_shutdown_cb shutdown_cb,
			  const struct rpmsg_rpc_client_services *services,
			  int len);

/**
 * rpmsg_rpc_server_init - initialize RPMsg rpc for server
 *
 * This function create endpoint and loads services into table
 *
 * @rpcs: pointer to the server rpc
 * @rdev: pointer to the rpmsg device
 * @services: pointer to service table
 * @len: length of table
 * @rpmsg_service_server_unbind: unbind function callback
 *
 * return 0 for success, and negative value for failure
 */
int rpmsg_rpc_server_init(struct rpmsg_rpc_svr *rpcs, struct rpmsg_device *rdev,
			  const struct rpmsg_rpc_services *services, int len,
			  rpmsg_ns_unbind_cb rpmsg_service_server_unbind);

/**
 * rpmsg_rpc_client_send - Request RPMsg RPC call
 *
 * @rpc: pointer to client remoteproc procedure call data
 * @rpc_id:  function id
 * @request_param: pointer to request buffer
 * @req_param_size: length of the request data
 *
 * return length of the received response, negative value for failure.
 */
int rpmsg_rpc_client_send(struct rpmsg_rpc_clt *rpc,
			  unsigned int rpc_id, void *request_param,
			  size_t req_param_size);

/**
 * rpmsg_rpc_server_send - Request RPMsg RPC call
 *
 * This function sends RPC request
 *
 * @rpcs: pointer to server rpc data
 * @rpc_id:  function id
 * @status: status of rpc
 * @request_param: pointer to request buffer
 * @param_size: length of the request data
 *
 * return length of the received response, negative value for failure.
 */
int rpmsg_rpc_server_send(struct rpmsg_rpc_svr *rpcs, uint32_t rpc_id,
			  int status, void *request_param,
			  size_t param_size);

#if defined __cplusplus
}
#endif

#endif /* RPMSG_RPC_CLIENT_SERVER_H */
