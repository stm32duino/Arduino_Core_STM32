/*
 * Copyright (c) 2021, L&T Technology Services Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <openamp/rpmsg_rpc_client_server.h>

static int rpmsg_endpoint_client_cb(struct rpmsg_endpoint *, void *, size_t,
				    uint32_t, void *);

static void rpmsg_service_client_unbind(struct rpmsg_endpoint *ept)
{
	struct rpmsg_rpc_clt *rpc;
	(void)ept;

	rpc = metal_container_of(ept, struct rpmsg_rpc_clt, ept);
	rpmsg_destroy_ept(&rpc->ept);
	if (rpc->shutdown_cb)
		rpc->shutdown_cb(rpc);
}

int rpmsg_rpc_client_init(struct rpmsg_rpc_clt *rpc,
			  struct rpmsg_device *rdev,
			  rpmsg_rpc_shutdown_cb shutdown_cb,
			  const struct rpmsg_rpc_client_services *services,
			  int len)
{
	int ret;

	if (!rpc || !rdev)
		return -EINVAL;

	rpc->services = services;
	rpc->n_services = len;

	rpc->shutdown_cb = shutdown_cb;

	ret = rpmsg_create_ept(&rpc->ept, rdev,
			       RPMSG_RPC_SERVICE_NAME, RPMSG_ADDR_ANY,
			       RPMSG_ADDR_ANY,
			       rpmsg_endpoint_client_cb,
			       rpmsg_service_client_unbind);

	return ret;
}

int rpmsg_rpc_client_send(struct rpmsg_rpc_clt *rpc,
			  unsigned int rpc_id, void *request_param,
			  size_t req_param_size)
{
	unsigned char tmpbuf[MAX_BUF_LEN];

	if (!rpc)
		return -EINVAL;

	/* to optimize with the zero copy API */
	memcpy(tmpbuf, &rpc_id, MAX_FUNC_ID_LEN);
	memcpy(&tmpbuf[MAX_FUNC_ID_LEN], request_param, req_param_size);
	return rpmsg_send(&rpc->ept, tmpbuf, MAX_FUNC_ID_LEN + req_param_size);
}

static const struct rpmsg_rpc_client_services *find_service(struct
							    rpmsg_rpc_clt * rpc,
							    uint32_t id)
{
	const struct rpmsg_rpc_client_services *service;

	for (unsigned int i = 0; i < rpc->n_services; i++) {
		service = &rpc->services[i];

		if (service->id == id) {
			return service;
		}
	}
	return NULL;
}

void rpmsg_rpc_client_release(struct rpmsg_rpc_clt *rpc)
{
	if (!rpc)
		return;
	if (&rpc->ept)
		rpmsg_destroy_ept(&rpc->ept);

}

static int rpmsg_endpoint_client_cb(struct rpmsg_endpoint *ept,
				    void *data, size_t len,
				    uint32_t src, void *priv)
{
	struct rpmsg_rpc_clt *rpc;
	const struct rpmsg_rpc_client_services *service;
	struct rpmsg_rpc_answer *msg;
	(void)priv;
	(void)src;

	if (!data || !ept)
		return -EINVAL;

	msg = (struct rpmsg_rpc_answer *)data;

	rpc = metal_container_of(ept,
				 struct rpmsg_rpc_clt,
				 ept);
	service = find_service(rpc, msg->id);
	if (!service)
		return -EINVAL;

	/* Invoke the callback function of the rpc */
	service->cb(rpc, msg->status, msg->params, len);

	return RPMSG_SUCCESS;
}
