/*
 * Copyright (c) 2016, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <metal/errno.h>

/* We need to find the internal MAX_IRQS limit */
/* Could be retrieved from platform specific files in the future */
#define METAL_INTERNAL

#include "metal-test.h"
#include <metal/irq.h>
#include <metal/log.h>
#include <metal/sys.h>
#include <metal/list.h>
#include <metal/utilities.h>

static int irq_handler(int irq, void *priv)
{
	(void)irq;
	(void)priv;

	return 0;
}

static int irq(void)
{
	int rc = 0;
	char *err_msg="";
	enum metal_log_level mll= metal_get_log_level();

	/* Do not show LOG_ERROR or LOG_DEBUG for expected fail case */
	metal_set_log_level(METAL_LOG_CRITICAL);

	rc = metal_irq_register(1, irq_handler, (void *)1);
	if (rc) {
		err_msg = "register irq 0 fail drv_id 1\n";
		goto out;
	}
	rc = metal_irq_register(2, irq_handler, (void *)1);
	if (rc) {
		err_msg = "register irq 1 fail drv_id 1\n";
		goto out;
	}

	metal_irq_unregister(1);
	rc = metal_irq_register(1, irq_handler, (void *)1);
	if (rc) {
		err_msg = "register irq 0 after unregistering failed\n";
		goto out;
	}
	metal_irq_unregister(1);
	metal_irq_unregister(2);

	return 0;
out:
	metal_set_log_level(mll);
	if ((err_msg[0] != '\0') && (!rc))
		rc = -EINVAL;
	if (rc) metal_log(METAL_LOG_ERROR, "%s", err_msg);
	return rc;
}

METAL_ADD_TEST(irq);
