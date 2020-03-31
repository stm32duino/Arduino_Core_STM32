#ifndef __OPENAMP_VIRTIO_CONFIG_H
#define __OPENAMP_VIRTIO_CONFIG_H

#ifndef RPMSG_BUFFER_SIZE
  /**
  * @brief Size of buffer of each vring buffers
  * @note  If the host processor is Linux, RPMSG_BUFFER_SIZE must be aligned
  *        with the kernel definition.
  *        Reference: https://elixir.bootlin.com/linux/v5.5.2/source/drivers/rpmsg/virtio_rpmsg_bus.c#L137
  */
  #define RPMSG_BUFFER_SIZE (512)
#endif

/** Size of header of a vqueue message */
#define RPMSG_VRING_HEADER_SIZE (16)
/** Available size of payload of a vqueue message */
#define RPMSG_VRING_PAYLOAD_SIZE (RPMSG_BUFFER_SIZE - RPMSG_VRING_HEADER_SIZE)

/**
 * number of rpmsg buffer
 * This means that a single call of rproc_virtio_notified(rvdev.vdev, VRING1_ID)
 * will trigger VirtIOSerial::rxCallback() VRING_NUM_BUFFS times at maximum.
 * A buffer handles VirtIOSerial::rxCallback() requires to be
 * (RPMSG_VRING_PAYLOAD_SIZE * VRING_NUM_BUFFS) at minimum to prevent overflow.
 */
#ifndef VRING_NUM_BUFFS
  #define VRING_NUM_BUFFS         (16)
#endif
#define RPMSG_VRING_TOTAL_PAYLOAD_SIZE (RPMSG_VRING_PAYLOAD_SIZE * VRING_NUM_BUFFS)

#if defined (VIRTIO_LOG)
  /**
  * OpenAMP trace (log) buffer configuration.
  * Users are free to redefine the size if needed.
  */
  #ifndef VIRTIO_LOG_BUFFER_SIZE
    #define VIRTIO_LOG_BUFFER_SIZE (2048)
  #endif

#endif

#endif // __OPENAMP_VIRTIO_CONFIG_H
