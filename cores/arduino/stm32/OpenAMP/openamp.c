/**
  ******************************************************************************
  * @file   openamp.c
  * @author  MCD Application Team
  * @brief  Code for openamp applications
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
#ifdef VIRTIOCON

#include "virtio_config.h"
#include "openamp/open_amp.h"
#include "openamp.h"
#include "rsc_table.h"
#include "metal/sys.h"
#include "metal/device.h"
#include "mbox_ipcc.h"
/* Private define ------------------------------------------------------------*/

#define SHM_DEVICE_NAME         "STM32_SHM"

/* Globals */

static struct metal_io_region *shm_io;
static struct metal_io_region *rsc_io;
static struct shared_resource_table *rsc_table;
static struct rpmsg_virtio_shm_pool shpool;
static struct rpmsg_virtio_device rvdev;
static metal_phys_addr_t shm_physmap;

/**
 * @brief OpenAMP libmetal device structure
 */
struct metal_device shm_device = {
  .name = SHM_DEVICE_NAME,
  .num_regions = 2,
  .regions = {
    {.virt = NULL}, /* shared memory */
    {.virt = NULL}, /* rsc_table memory */
  },
  .node = { NULL },
  .irq_num = 0,
  .irq_info = NULL
};

/**
 * @brief Initialize OpenAMP shared memory (libmetal and resource table)
 *
 * @param RPMsgRole: RPMSG_REMOTE - Device is remote (slave)
 * @retval 0 on success
 */
static int OPENAMP_shmem_init(int RPMsgRole)
{
  int status = 0;
  struct metal_device *device;
  struct metal_init_params metal_params = METAL_INIT_DEFAULTS;
  void *rsc_tab_addr;
  int rsc_size;

  metal_init(&metal_params);

  status = metal_register_generic_device(&shm_device);
  if (status != 0) {
    return status;
  }

  status = metal_device_open("generic", SHM_DEVICE_NAME, &device);
  if (status != 0) {
    return status;
  }

  shm_physmap = SHM_START_ADDRESS;
  metal_io_init(&device->regions[0], (void *)SHM_START_ADDRESS, &shm_physmap,
                SHM_SIZE, -1, 0, NULL);

  shm_io = metal_device_io_region(device, 0);
  if (shm_io == NULL) {
    return -1;
  }

  /* Initialize resources table variables */
  resource_table_init(RPMsgRole, &rsc_tab_addr, &rsc_size);
  rsc_table = (struct shared_resource_table *)rsc_tab_addr;
  if (!rsc_table) {
    return -1;
  }

  metal_io_init(&device->regions[1], rsc_table,
                (metal_phys_addr_t *)rsc_table, rsc_size, -1U, 0, NULL);

  rsc_io = metal_device_io_region(device, 1);
  if (rsc_io == NULL) {
    return -1;
  }

  return 0;
}

/**
 * @brief Initialize the openamp framework
 *
 * @retval 0 when success
 */
int OPENAMP_Init()
{
  struct fw_rsc_vdev_vring *vring_rsc;
  struct virtio_device *vdev;
  int status = 0;

  MAILBOX_Init();

  /* Libmetal Initilalization */
  status = OPENAMP_shmem_init(RPMSG_REMOTE);
  if (status) {
    return status;
  }

  vdev = rproc_virtio_create_vdev(RPMSG_REMOTE, VDEV_ID, &rsc_table->vdev,
                                  rsc_io, NULL, MAILBOX_Notify, NULL);
  if (vdev == NULL) {
    return -1;
  }

  rproc_virtio_wait_remote_ready(vdev);
  vring_rsc = &rsc_table->vring0;
  status = rproc_virtio_init_vring(vdev, 0, vring_rsc->notifyid,
                                   (void *)vring_rsc->da, shm_io,
                                   vring_rsc->num, vring_rsc->align);
  if (status != 0) {
    return status;
  }
  vring_rsc = &rsc_table->vring1;
  status = rproc_virtio_init_vring(vdev, 1, vring_rsc->notifyid,
                                   (void *)vring_rsc->da, shm_io,
                                   vring_rsc->num, vring_rsc->align);
  if (status != 0) {
    return status;
  }

  rpmsg_virtio_init_shm_pool(&shpool, (void *)VRING_BUFF_ADDRESS,
                             (size_t)SHM_SIZE);
  rpmsg_init_vdev(&rvdev, vdev, NULL, shm_io, &shpool);

  return 0;
}

/**
 * @brief Deinitialize the openamp framework
 */
void OPENAMP_DeInit()
{
  rpmsg_deinit_vdev(&rvdev);

  metal_finish();
}

/**
 * @brief Initialize the endpoint struct
 *
 * @param ept: virtio rpmsg endpoint
 */
void OPENAMP_init_ept(struct rpmsg_endpoint *ept)
{
  rpmsg_init_ept(ept, "", RPMSG_ADDR_ANY, RPMSG_ADDR_ANY, NULL, NULL);
}

/**
 * @brief Create and register the name service endpoint
 *
 * @param ept: virtio rpmsg endpoint
 * @param name: virtio rpmsg name service name
 * @param dest: message destination address. Set RPMSG_ADDR_ANY if
 *              the host processor will decide this
 * @param cb: virtio rpmsg endpoint callback (receive)
 * @param unbind_cb: virtio rpmsg endpoint destroy callback
 * @retval 0 when success
 */
int OPENAMP_create_endpoint(struct rpmsg_endpoint *ept, const char *name,
                            uint32_t dest, rpmsg_ept_cb cb,
                            rpmsg_ns_unbind_cb unbind_cb)
{
  return rpmsg_create_ept(ept, &rvdev.rdev, name, RPMSG_ADDR_ANY, dest, cb,
                          unbind_cb);
}

/**
 * @brief Check and process any received messages from tx channel
 * @note  Don't call this in an ISR.
 */
void OPENAMP_check_for_tx_message(void)
{
  MAILBOX_Poll(rvdev.vdev, VRING0_ID);
}

/**
 * @brief Check and process any received messages from rx channel
 * @note  Don't call this in an ISR.
 */
void OPENAMP_check_for_rx_message(void)
{
  MAILBOX_Poll(rvdev.vdev, VRING1_ID);
}

/**
 * @brief Wait loop on rpmsg endpoint (VirtIOSerial) ready to send a message.
 *        (until message dest address is known)
 * @note  This will wait until the first message arrives from the Linux host.
 *        If we send a rpmsg message before this it will fail.
 * @note  Don't call this in an ISR.
 * @see   VirtIOSerial::rxCallback
 * @param rp_ept: virtio rpmsg endpoint
 */
void OPENAMP_Wait_EndPointready(struct rpmsg_endpoint *rp_ept)
{
  while (!is_rpmsg_ept_ready(rp_ept)) {
    MAILBOX_Poll(rvdev.vdev, VRING0_ID);
    MAILBOX_Poll(rvdev.vdev, VRING1_ID);
  }
}

#endif /* VIRTIOCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
