/*
 * Copyright (c) 2015, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	generic/mutex.h
 * @brief	Generic mutex primitives for libmetal.
 */

#ifndef __METAL_MUTEX__H__
#error "Include metal/mutex.h instead of metal/generic/mutex.h"
#endif

#ifndef __METAL_GENERIC_MUTEX__H__
#define __METAL_GENERIC_MUTEX__H__

#include <metal/atomic.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	atomic_int v;
} metal_mutex_t;

#define METAL_MUTEX_UNLOCKED 0
#define METAL_MUTEX_LOCKED   1

/*
 * METAL_MUTEX_INIT - used for initializing an mutex element in a static struct
 * or global
 */
#define METAL_MUTEX_INIT(m) { ATOMIC_VAR_INIT(METAL_MUTEX_UNLOCKED) }
/*
 * METAL_MUTEX_DEFINE - used for defining and initializing a global or
 * static singleton mutex
 */
#define METAL_MUTEX_DEFINE(m) metal_mutex_t m = METAL_MUTEX_INIT(m)

static inline void __metal_mutex_init(metal_mutex_t *mutex)
{
	atomic_store(&mutex->v, METAL_MUTEX_UNLOCKED);
}

static inline void __metal_mutex_deinit(metal_mutex_t *mutex)
{
	(void)mutex;
}

static inline int __metal_mutex_try_acquire(metal_mutex_t *mutex)
{
	int unlocked = METAL_MUTEX_UNLOCKED;

	if (atomic_compare_exchange_strong(&mutex->v, &unlocked,
					   METAL_MUTEX_LOCKED)) {
		return 1; /* acquired */
	} else {
		return 0; /* not acquired */
	}
}

static inline void __metal_mutex_acquire(metal_mutex_t *mutex)
{
	int unlocked = METAL_MUTEX_UNLOCKED;

	while (!atomic_compare_exchange_weak(&mutex->v, &unlocked,
					     METAL_MUTEX_LOCKED)) {
		;
	}
}

static inline void __metal_mutex_release(metal_mutex_t *mutex)
{
	atomic_store(&mutex->v, METAL_MUTEX_UNLOCKED);
}

static inline int __metal_mutex_is_acquired(metal_mutex_t *mutex)
{
	return atomic_load(&mutex->v);
}

#ifdef __cplusplus
}
#endif

#endif /* __METAL_GENERIC_MUTEX__H__ */
