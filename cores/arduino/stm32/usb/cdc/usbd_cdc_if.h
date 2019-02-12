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
#include "timer.h"

#ifndef APP_RX_DATA_SIZE
#define APP_RX_DATA_SIZE  2048
#endif
#ifndef APP_TX_DATA_SIZE
#define APP_TX_DATA_SIZE  2048
#endif

#ifndef CDC_TIM
#ifdef TIM6
#define CDC_TIM TIM6
#else
#define CDC_TIM TIM4
#endif
#endif
#ifndef CDC_TIM_IRQn
#ifdef TIM6
#define CDC_TIM_IRQn TIM6_IRQn
#else
#define CDC_TIM_IRQn TIM4_IRQn
#endif
#endif

/* Periodically, the state of the buffer "UserTxBuffer" is checked.
   The period depends on CDC_POLLING_INTERVAL */
#define CDC_POLLING_INTERVAL             2 /* in ms. The max is 65 and the min is 1 */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

extern USBD_CDC_ItfTypeDef  USBD_CDC_fops;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CDC_disable_TIM_Interrupt(void);
void CDC_enable_TIM_Interrupt(void);
void CDC_flush(void);
void CDC_resume_receive(void);

#ifdef __cplusplus
}
#endif
#endif /* USBD_USE_CDC */
#endif /* USBCON */
#endif /* __USBD_CDC_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
