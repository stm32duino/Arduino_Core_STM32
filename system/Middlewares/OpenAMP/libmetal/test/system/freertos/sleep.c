/*
 * Copyright (c) 2016, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <metal/errno.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"

#include "metal-test.h"
#include <metal/time.h>
#include <metal/sleep.h>
#include <metal/log.h>
#include <metal/sys.h>

static int sleep(void)
{
	int rc;
	unsigned int usec = 150000;
	unsigned long long tstart, tend, tdelayed, tolerance;


	tstart = metal_get_timestamp();
	metal_sleep_usec(usec);
	tend = metal_get_timestamp();
	tdelayed = tend - tstart;
	/* allow +/- 1 OS tick */
	tolerance = portTICK_PERIOD_MS * 1000;
	if (tdelayed > (usec + tolerance) || tdelayed < (usec - tolerance))
		rc = -1;
	else
		rc = 0;

	return rc;
}
METAL_ADD_TEST(sleep);
