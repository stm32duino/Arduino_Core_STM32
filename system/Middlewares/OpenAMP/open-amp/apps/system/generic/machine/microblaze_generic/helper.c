/*
 * Copyright (c) 2020 Xilinx, Inc. All rights reserved.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "xparameters.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include <metal/sys.h>
#include "platform_info.h"

static void system_metal_logger(enum metal_log_level level,
				const char *format, ...)
{
	(void)level;
	(void)format;
}

/* Main hw machinery initialization entry point, called from main()*/
/* return 0 on success */
int init_system(void)
{
	int ret;
	struct metal_init_params metal_param = {
		.log_handler = system_metal_logger,
		.log_level = METAL_LOG_INFO,
	};

	/* Low level abstraction layer for openamp initialization */
	ret = metal_init(&metal_param);
	return ret;
}

void cleanup_system(void)
{
	metal_finish();
}
