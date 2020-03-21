/**
  ******************************************************************************
  * @file   openamp.h
  * @brief  Header for openamp applications
  * @author  MCD Application Team
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
#ifndef __OPENAMP_OPENAMP_H
#define __OPENAMP_OPENAMP_H

#ifdef VIRTIOCON

#ifdef __cplusplus
extern "C" {
#endif

#include <openamp/rpmsg.h>
#include "openamp_conf.h"

#define OPENAMP_send  rpmsg_send
#define OPENAMP_destroy_ept rpmsg_destroy_ept

int OPENAMP_Init(void);
void OPENAMP_DeInit(void);
void OPENAMP_init_ept(struct rpmsg_endpoint *ept);

int OPENAMP_create_endpoint(struct rpmsg_endpoint *ept, const char *name,
                            uint32_t dest, rpmsg_ept_cb cb,
                            rpmsg_ns_unbind_cb unbind_cb);
void OPENAMP_check_for_tx_message(void);
void OPENAMP_check_for_rx_message(void);
void OPENAMP_Wait_EndPointready(struct rpmsg_endpoint *rp_ept);

#ifdef __cplusplus
}
#endif
#endif /* VIRTIOCON */
#endif /*__OPENAMP_OPENAMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
