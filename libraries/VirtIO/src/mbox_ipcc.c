/**
  ******************************************************************************
  * @file    mbox_ipcc.c
  * @author  MCD Application Team
  * @brief   This file provides code for the configuration
  *                      of the mailbox_ipcc_if.c MiddleWare.
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

/*
 * Channel direction and usage:
virtio_rpmsg_bus.c                           virtqueue      vring   rpmsg_virtio.c
 ========   <-- new msg ---=============--------<------             ==========
||      || rvq (rx)    || IPCC CHANNEL 1 ||  svq (tx_vq) -> vring0 ||        ||
||  A7  ||  ------->-------=============--- buf free-->            ||   M4   ||
||      ||                                                         ||        ||
||master||  <-- buf free---=============--------<------            || slave  ||
||      || svq (tx)    || IPCC CHANNEL 2 ||  rvq (rx_vq) -> vring1 ||(remote)||
 ========   ------->-------=============----new msg -->             ==========
 */

/* Includes ------------------------------------------------------------------*/
#include "virtio_config.h"
#include <openamp/open_amp.h>
#include "stm32_def.h"
#include "openamp_conf.h"
#include "mbox_ipcc.h"

/* Private define ------------------------------------------------------------*/
#define MASTER_CPU_ID       0
#define REMOTE_CPU_ID       1
#define IPCC_CPU_A7         MASTER_CPU_ID
#define IPCC_CPU_M4         REMOTE_CPU_ID

typedef enum {
  MBOX_NO_MSG = 0,
  MBOX_NEW_MSG = 1,
  MBOX_BUF_FREE = 2
} mbox_status_t;

/* Private variables ---------------------------------------------------------*/
IPCC_HandleTypeDef hipcc;
mbox_status_t msg_received_ch1 = MBOX_NO_MSG;
mbox_status_t msg_received_ch2 = MBOX_NO_MSG;

/* Private function prototypes -----------------------------------------------*/
void IPCC_channel1_callback(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);
void IPCC_channel2_callback(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);

/**
  * @brief  Initialize MAILBOX with IPCC peripheral
  * @param  None
  * @retval : Operation result
  */
int MAILBOX_Init(void)
{
  __HAL_RCC_IPCC_CLK_ENABLE();
  HAL_NVIC_SetPriority(IPCC_RX1_IRQn, IPCC_IRQ_PRIO, IPCC_IRQ_SUBPRIO);
  HAL_NVIC_EnableIRQ(IPCC_RX1_IRQn);

  hipcc.Instance = IPCC;
  if (HAL_IPCC_Init(&hipcc) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_IPCC_ActivateNotification(&hipcc, IPCC_CHANNEL_1, IPCC_CHANNEL_DIR_RX,
                                    IPCC_channel1_callback) != HAL_OK) {
    Error_Handler();
    return -1;
  }

  if (HAL_IPCC_ActivateNotification(&hipcc, IPCC_CHANNEL_2, IPCC_CHANNEL_DIR_RX,
                                    IPCC_channel2_callback) != HAL_OK) {
    Error_Handler();
    return -1;
  }

  return 0;
}

/**
 * @brief  Process vring messages received from IPCC ISR
 * @param vdev: virtio device
 * @param vring_id: Vring ID
 * @retval : Operation result
 */
int MAILBOX_Poll(struct virtio_device *vdev, uint32_t vring_id)
{
  int ret = -1;

  switch (vring_id) {
    case VRING0_ID:
      if (msg_received_ch1 == MBOX_BUF_FREE) {
        /* This calls rpmsg_virtio_tx_callback(), which actually does nothing. */
        rproc_virtio_notified(vdev, VRING0_ID);
        msg_received_ch1 = MBOX_NO_MSG;
        ret = 0;
      }
      break;
    case VRING1_ID:
      if (msg_received_ch2 == MBOX_NEW_MSG) {
        /**
         * This calls rpmsg_virtio_rx_callback(), which calls virt_uart rx callback
         * RING_NUM_BUFFS times at maximum.
         */
        rproc_virtio_notified(vdev, VRING1_ID);
        msg_received_ch2 = MBOX_NO_MSG;
        ret = 0;
      }
      break;
    default:
      break;
  }

  return ret;
}

/**
  * @brief  Callback function called by OpenAMP MW to notify message processing (aka. kick)
  * @note   This callback is called by virtqueue_kick() in rpmsg_virtio_send_offchannel_raw().
  *         Therefore, it is only called while tx, but not rx.
  * @param  Vring id
  * @retval Operation result
  */
int MAILBOX_Notify(void *priv, uint32_t vring_id)
{
  (void)priv;
  uint32_t channel;

  /* Called after virtqueue processing: time to inform the remote */
  if (vring_id == VRING0_ID) {
    channel = IPCC_CHANNEL_1;
  } else if (vring_id == VRING1_ID) {
    /* Note: the OpenAMP framework never notifies this */
    channel = IPCC_CHANNEL_2;
    return -1;
  } else {
    return -1;
  }

  /* Check that the channel is free (otherwise wait until it is) */
  if (HAL_IPCC_GetChannelStatus(&hipcc, channel, IPCC_CHANNEL_DIR_TX) == IPCC_CHANNEL_STATUS_OCCUPIED) {
    /* Wait for channel to be freed */
    while (HAL_IPCC_GetChannelStatus(&hipcc, channel, IPCC_CHANNEL_DIR_TX) == IPCC_CHANNEL_STATUS_OCCUPIED)
      ;
  }

  /* Inform the host processor (either new message, or buf free) */
  HAL_IPCC_NotifyCPU(&hipcc, channel, IPCC_CHANNEL_DIR_TX);
  return 0;
}

/* Private function  ---------------------------------------------------------*/
/* Callback from IPCC Interrupt Handler: Master Processor informs that there are some free buffers */
void IPCC_channel1_callback(IPCC_HandleTypeDef *hipcc,
                            uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir)
{
  (void) ChannelDir;
  msg_received_ch1 = MBOX_BUF_FREE;

  /* Inform the host processor that we have received the 'buff free' msg */
  HAL_IPCC_NotifyCPU(hipcc, ChannelIndex, IPCC_CHANNEL_DIR_RX);
}

/* Callback from IPCC Interrupt Handler: new message received from Master Processor */
void IPCC_channel2_callback(IPCC_HandleTypeDef *hipcc,
                            uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir)
{
  (void) ChannelDir;
  msg_received_ch2 = MBOX_NEW_MSG;

  /* Inform the host processor that we have received the msg */
  HAL_IPCC_NotifyCPU(hipcc, ChannelIndex, IPCC_CHANNEL_DIR_RX);
}

/**
  * @brief This function handles IPCC RX1 occupied interrupt.
  */
void IPCC_RX1_IRQHandler(void)
{
  HAL_IPCC_RX_IRQHandler(&hipcc);
}

#endif /* VIRTIOCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
