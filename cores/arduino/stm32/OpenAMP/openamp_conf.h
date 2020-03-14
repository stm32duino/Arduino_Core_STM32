/**
  ******************************************************************************
  * @file    openamp_conf.h
  * @author  MCD Application Team
  * @brief   Configuration file for OpenAMP MW
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OPENAMP_OPENAMP_CONF_H
#define __OPENAMP_OPENAMP_CONF_H

#ifdef VIRTIOCON

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Note: Do not remove this. Removing this might not trigger compile error but
 * the configuration can be significantly different.
 */
#include "virtio_config.h"
#include "virt_uart.h"

/*
 * for GCC add the following content to the .ld file:
 * MEMORY
 * {
 * ...
 * OPEN_AMP_SHMEM (xrw) : ORIGIN = 0x38000400, LENGTH = 63K
 * }
 * __OPENAMP_region_start__  = ORIGIN(OPEN_AMP_SHMEM);
 * __OPENAMP_region_end__ = ORIGIN(OPEN_AMP_SHMEM) + LENGTH(OPEN_AMP_SHMEM);
 *
 * using the LENGTH(OPEN_AMP_SHMEM) to set the SHM_SIZE lead to a crash thus we
 * use the start and end address.
 */
extern int __OPENAMP_region_start__[];  /* defined by linker script */
extern int __OPENAMP_region_end__[];    /* defined by linker script */

#define SHM_START_ADDRESS       ((metal_phys_addr_t)__OPENAMP_region_start__)
#define SHM_SIZE                (size_t)((void *)__OPENAMP_region_end__ - (void *) __OPENAMP_region_start__)

#if defined STM32MP1xx
#define VRING_RX_ADDRESS        -1        /* allocated by Master processor: CA7 */
#define VRING_TX_ADDRESS        -1        /* allocated by Master processor: CA7 */
#define VRING_BUFF_ADDRESS      -1        /* allocated by Master processor: CA7 */
#define VRING_ALIGNMENT         16        /* fixed to match with linux constraint */
#ifndef VRING_NUM_BUFFS
#define VRING_NUM_BUFFS         16        /* number of rpmsg buffer */
#endif
#else
#error "VRING configuration for the device missing"
#endif

/* Fixed parameters */
#define NUM_RESOURCE_ENTRIES    2
#define VRING_COUNT             2

#define VDEV_ID                 0xFF
#define VRING0_ID               0         /* VRING0 ID (master to remote) fixed to 0 for linux compatibility*/
#define VRING1_ID               1         /* VRING1 ID (remote to master) fixed to 1 for linux compatibility  */

#ifdef __cplusplus
}
#endif

#endif /* VIRTIOCON */
#endif /* __OPENAMP_OPENAMP_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
