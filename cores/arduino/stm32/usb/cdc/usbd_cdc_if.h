/**
  ******************************************************************************
  * @file    usbd_cdc_if.h
  * @author  MCD Application Team
  * @brief   Header for usbd_cdc_if.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_IF_H
#define __USBD_CDC_IF_H

#ifdef USBCON
#ifdef USBD_USE_CDC

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc.h"
#include "cdc_queue.h"

/* Periodically, the state of the buffer "UserTxBuffer" is checked.
   The period depends on CDC_POLLING_INTERVAL */
#define CDC_POLLING_INTERVAL             2 /* in ms. The max is 65 and the min is 1 */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

extern USBD_CDC_ItfTypeDef  USBD_CDC_fops;
extern CDC_TransmitQueue_TypeDef TransmitQueue;
extern CDC_ReceiveQueue_TypeDef ReceiveQueue;


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CDC_continue_transmit(void);
bool CDC_resume_receive(void);
void CDC_init(void);
void CDC_deInit(void);
bool CDC_connected(void);

#ifdef __cplusplus
}
#endif
#endif /* USBD_USE_CDC */
#endif /* USBCON */
#endif /* __USBD_CDC_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
