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
  *                      www.st.com/SLA0044
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
/**
 * @brief Resume the USB CDC transmit queue if the IN endpoint is idle.
 * @note Called from USBSerial::write() and from the USB transmit complete callback.
 */
void CDC_continue_transmit(void);

/**
 * @brief Re-arm the USB CDC OUT endpoint with a new receive buffer.
 * @note Does nothing if a receive is already pending or the receive queue has
 *       no room for a full packet.
 * @return true if reception was resumed, false otherwise.
 */
bool CDC_resume_receive(void);

/**
 * @brief Initialize the USB CDC device and start USB enumeration.
 * @note Does nothing if the device is already initialized.
 */
void CDC_init(void);

/**
 * @brief Stop the USB CDC device and release its USB resources.
 * @note Does nothing if the device is not initialized.
 */
void CDC_deInit(void);

/**
 * @brief Check whether a host is connected and ready to receive data.
 * @return true if the device is configured, DTR is asserted and the last
 *         transmission did not time out, false otherwise.
 */
bool CDC_connected(void);

/**
 * @brief Enable or disable the use of the host DTR signal for CDC_connected().
 * @param enable true to take DTR into account, false to ignore it.
 */
void CDC_enableDTR(bool enable);

/* getters for CDC line codings. Do not expose struct directly */

/**
 * @brief Get the baud rate set by the USB host.
 * @return baud rate in bits per second.
 */
uint32_t CDC_getBaudrate(void);

/**
 * @brief Get the stop bits set by the USB host.
 * @return 0 for one stop bit, 1 for 1.5 stop bits, 2 for two stop bits.
 *         Values match USBSerial.h.
 */
uint8_t  CDC_getStopBits(void);

/**
 * @brief Get the parity set by the USB host.
 * @return 0 none, 1 odd, 2 even, 3 mark, 4 space. Values match USBSerial.h.
 */
uint8_t  CDC_getParity(void);

/**
 * @brief Get the number of data bits set by the USB host.
 * @return number of data bits (5, 6, 7, 8 or 16).
 */
uint8_t  CDC_getDataBits(void);

#ifdef __cplusplus
}
#endif
#endif /* USBD_USE_CDC */
#endif /* USBCON */
#endif /* __USBD_CDC_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
