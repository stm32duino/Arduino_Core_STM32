/*
 * Copyright (c) 2021, L&T Technology Services Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <openamp/rpmsg_rpc_client_server.h>

#define LPERROR(format, ...) metal_log(METAL_LOG_ERROR, format, ##__VA_ARGS__)

static int rpmsg_endpoint_server_cb(struct rpmsg_endpoint *, void *,
				    size_t, uint32_t, void *);

int rpmsg_rpc_server_init(struct rpmsg_rpc_svr *rpcs, struct rpmsg_device *rdev,
			  const struct rpmsg_rpc_services *services, int len,
			  rpmsg_ns_unbind_cb rpmsg_service_server_unbind)
{
	int ret;

	rpcs->services = services;
	rpcs->n_services = len;

	ret = rpmsg_create_ept(&rpcs->ept, rdev, RPMSG_RPC_SERVICE_NAME,
			       RPMSG_ADDR_ANY, RPMSG_ADDR_ANY,
			       rpmsg_endpoint_server_cb,
			       rpmsg_service_server_unbind);
	if (ret)
		return ret;

	return ret;
}

static const struct rpmsg_rpc_services *find_service(struct rpmsg_rpc_svr *rpcs,
						     unsigned int id)
{
	const struct rpmsg_rpc_services *service;

	for (unsigned int i = 0; i < rpcs->n_services; i++) {
		service = &rpcs->services[i];

		if (service->id == id) {
			return service;
		}
	}
	return NULL;
}

static int rpmsg_endpoint_server_cb(struct rpmsg_endpoint *ept, void *data,
				    size_t len,
				    uint32_t src, void *priv)
{
	unsigned char buf[MAX_BUF_LEN];
	unsigned int id;
	const struct rpmsg_rpc_services *service;
	struct rpmsg_rpc_svr *rpcs;
	(void)priv;
	(void)src;

	if (len > MAX_BUF_LEN)
		return -EINVAL;

	rpcs = metal_container_of(ept, struct rpmsg_rpc_svr, ept);

	memcpy(buf, data, len);
	id = *buf;
	service = find_service(rpcs, id);

	if (service) {
		if (service->cb_function(buf, rpcs)) {
			LPERROR("Service failed at rpc id: %ld\r\n", id);
		}
	} else {
		LPERROR("Handling remote procedure call errors: rpc id %ld\r\n",
			id);
		rpmsg_rpc_server_send(rpcs, id, RPMSG_RPC_INVALID_ID, NULL, 0);
	}
	return RPMSG_SUCCESS;
}

int rpmsg_rpc_server_send(struct rpmsg_rpc_svr *rpcs, uint32_t rpc_id,
			  int status, void *request_param, size_t param_size)
{
	struct rpmsg_endpoint *ept = &rpcs->ept;
	struct rpmsg_rpc_answer msg;

	if (!ept)
		return -EINVAL;
	if (param_size > (MAX_BUF_LEN - sizeof(msg.status)))
		return -EINVAL;

	msg.id = rpc_id;
	msg.status = status;
	memcpy(msg.params, request_param, param_size);

	return rpmsg_send(ept, &msg, MAX_FUNC_ID_LEN + param_size);
}
