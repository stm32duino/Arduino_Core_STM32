/*
 * Copyright(c) 2019 Xilinx Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <metal/alloc.h>
#include <metal/io.h>
#include <metal/sys.h>
#include <metal/utilities.h>
#include <openamp/remoteproc.h>
#include <openamp/remoteproc_loader.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
/* Xilinx headers */
#include <pm_api_sys.h>
#include <xil_mpu.h>
#include <xil_printf.h>
#include <xreg_cortexr5.h>

#ifdef versal
#include <xpm_nodeid.h>
#include <xpm_defs.h>

#ifndef NODE_APU_0
#define NODE_APU_0			PM_DEV_ACPU_0
#endif
#ifndef NODE_APU_1
#define NODE_APU_1			PM_DEV_ACPU_1
#endif
#ifndef NODE_RPU_0
#define NODE_RPU_0			PM_DEV_RPU0_0
#endif
#ifndef NODE_RPU
#define NODE_RPU			PM_DEV_RPU0_0
#endif

#ifndef NODE_RPU_1
#define NODE_RPU_1			PM_DEV_RPU0_1
#endif

#ifndef NODE_TCM_0_A
#define NODE_TCM_0_A PM_DEV_TCM_0_A
#endif
#ifndef NODE_TCM_0_B
#define NODE_TCM_0_B PM_DEV_TCM_0_B
#endif
#ifndef NODE_TCM_1_A
#define NODE_TCM_1_A PM_DEV_TCM_1_A
#endif
#ifndef NODE_TCM_1_B
#define NODE_TCM_1_B PM_DEV_TCM_1_B
#endif

#ifndef NODE_DDR
#define NODE_DDR			PM_DEV_DDR_0
#endif

#ifndef NODE_OCM_BANK_0
#define NODE_OCM_BANK_0			PM_DEV_OCM_0
#endif
#ifndef NODE_OCM_BANK_1
#define NODE_OCM_BANK_1			PM_DEV_OCM_1
#endif
#ifndef NODE_OCM_BANK_2
#define NODE_OCM_BANK_2			PM_DEV_OCM_2
#endif
#ifndef NODE_OCM_BANK_3
#define NODE_OCM_BANK_3			PM_DEV_OCM_3
#endif

/* Requirement limits */
#define XPM_MAX_CAPABILITY (PM_CAP_ACCESS | PM_CAP_CONTEXT | PM_CAP_WAKEUP)
#define XPM_MAX_LATENCY        (0xFFFFU)
#define XPM_MAX_QOS            (100)
#define XPM_MIN_CAPABILITY (0)
#define XPM_MIN_LATENCY        (0)
#define XPM_MIN_QOS            (0)
#define XPM_DEF_CAPABILITY XPM_MAX_CAPABILITY
#define XPM_DEF_LATENCY        XPM_MAX_LATENCY
#define XPM_DEF_QOS            XPM_MAX_QOS

enum XPmRequestAck {
    REQUEST_ACK_NO = 1,
    REQUEST_ACK_BLOCKING,
    REQUEST_ACK_NON_BLOCKING,
    REQUEST_ACK_CB_CERROR,
};

#else /* zynqmp */
#include <pm_defs.h>
#define XPM_MAX_QOS            MAX_QOS
#define XPM_MIN_QOS            (0)
#endif /* versal */

#define LPRINTF(format, ...) xil_printf(format, ##__VA_ARGS__)
//#define LPRINTF(format, ...)
#define LPERROR(format, ...) LPRINTF("ERROR: " format, ##__VA_ARGS__)

struct rproc_priv {
    struct remoteproc *rproc;
    int cpu_id;
};

#endif /* COMMON_H_ */
