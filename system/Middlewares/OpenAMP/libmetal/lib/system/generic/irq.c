/*
 * Copyright (c) 2016 - 2017, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	generic/irq.c
 * @brief	generic libmetal irq definitions.
 */

#include <metal/errno.h>
#include <metal/irq.h>
#include <metal/sys.h>
#include <metal/log.h>
#include <metal/mutex.h>
#include <metal/list.h>
#include <metal/utilities.h>
#include <metal/alloc.h>

unsigned int metal_irq_save_disable(void)
{
	return sys_irq_save_disable();
}

void metal_irq_restore_enable(unsigned int flags)
{
	sys_irq_restore_enable(flags);
}

