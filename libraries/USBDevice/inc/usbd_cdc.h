/**
  ******************************************************************************
  * @file    usbd_cdc.h
  * @author  MCD Application Team
  * @brief   header file for the usbd_cdc.c file.
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
#ifndef __USB_CDC_H
#define __USB_CDC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_ioreq.h"
#include "usbd_ep_conf.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */

/** @defgroup usbd_cdc USBD CDC Class
  * @brief This file is the Header file for usbd_cdc.c
  * @{
  */


/** @defgroup usbd_cdc_Exported_Defines USBD CDC Exported Defines
  * @brief CDC endpoint parameters, class request codes and control line state bits.
  * @{
  */
#ifndef CDC_HS_BINTERVAL
/**
 * @brief Polling interval of the CDC command endpoint at high speed.
 *        Can be overridden.
 */
#define CDC_HS_BINTERVAL                            0x10U
#endif /* CDC_HS_BINTERVAL */

#ifndef CDC_FS_BINTERVAL
/**
 * @brief Polling interval of the CDC command endpoint at full speed.
 *        Can be overridden.
 */
#define CDC_FS_BINTERVAL                            0x10U
#endif /* CDC_FS_BINTERVAL */

/* CDC Endpoints parameters */

/** @brief Size, in bytes, of the CDC configuration descriptor. */
#define USB_CDC_CONFIG_DESC_SIZ                     67U
#define CDC_DATA_HS_IN_PACKET_SIZE                  CDC_DATA_HS_MAX_PACKET_SIZE
#define CDC_DATA_HS_OUT_PACKET_SIZE                 CDC_DATA_HS_MAX_PACKET_SIZE

#define CDC_DATA_FS_IN_PACKET_SIZE                  CDC_DATA_FS_MAX_PACKET_SIZE
#define CDC_DATA_FS_OUT_PACKET_SIZE                 CDC_DATA_FS_MAX_PACKET_SIZE

/** @brief Maximum size, in bytes, of a CDC class request data stage. */
#define CDC_REQ_MAX_DATA_SIZE                       0x7U
/*---------------------------------------------------------------------*/
/*  CDC definitions                                                    */
/*---------------------------------------------------------------------*/
#define CDC_SEND_ENCAPSULATED_COMMAND               0x00U
#define CDC_GET_ENCAPSULATED_RESPONSE               0x01U
#define CDC_SET_COMM_FEATURE                        0x02U
#define CDC_GET_COMM_FEATURE                        0x03U
#define CDC_CLEAR_COMM_FEATURE                      0x04U
#define CDC_SET_LINE_CODING                         0x20U
#define CDC_GET_LINE_CODING                         0x21U
#define CDC_SET_CONTROL_LINE_STATE                  0x22U
#define CDC_SEND_BREAK                              0x23U

// Control Line State bits
/** @brief DTR bit (Data Terminal Ready) in SET_CONTROL_LINE_STATE wValue. */
#define CLS_DTR   (1 << 0)
/** @brief RTS bit (Request To Send) in SET_CONTROL_LINE_STATE wValue. */
#define CLS_RTS   (1 << 1)

/**
  * @}
  */


/** @defgroup usbd_cdc_Exported_Types USBD CDC Exported Types
  * @brief Types used by the USB CDC class.
  * @{
  */

typedef struct {
  uint32_t bitrate;   /**< Data terminal rate, in bits per second. */
  uint8_t  format;    /**< Stop bits: 0 = 1, 1 = 1.5, 2 = 2 stop bits. */
  uint8_t  paritytype; /**< Parity: 0 none, 1 odd, 2 even, 3 mark, 4 space. */
  uint8_t  datatype;  /**< Data bits: 5, 6, 7, 8 or 16. */
} USBD_CDC_LineCodingTypeDef;

/** @brief Application callbacks of the CDC class. */
typedef struct _USBD_CDC_Itf {
  /** Called when the CDC class is initialized. */
  int8_t (* Init)(void);
  /** Called when the CDC class is de-initialized. */
  int8_t (* DeInit)(void);
  /** Handle a CDC class request. */
  int8_t (* Control)(uint8_t cmd, uint8_t *pbuf, uint16_t length);
  /** Called when data is received on the OUT endpoint. */
  int8_t (* Receive)(uint8_t *Buf, uint32_t *Len);
  /** Called when a transfer on the IN endpoint is complete. */
  int8_t (* TransmitCplt)(uint8_t *Buf, uint32_t *Len, uint8_t epnum);
} USBD_CDC_ItfTypeDef;

/** @brief CDC class instance data. */
typedef struct {
  uint32_t data[CDC_DATA_HS_MAX_PACKET_SIZE / 4U];      /* Force 32-bit alignment */
  uint8_t  CmdOpCode;   /**< Pending class request code. */
  uint8_t  CmdLength;   /**< Length of the pending class request data. */
  uint8_t  *RxBuffer;   /**< Buffer receiving the OUT endpoint data. */
  uint8_t  *TxBuffer;   /**< Buffer sent on the IN endpoint. */
  uint32_t RxLength;    /**< Length of the data received. */
  uint32_t TxLength;    /**< Length of the data to send. */

  /** 0 when the IN endpoint is idle, 1 when a transfer is in progress. */
  __IO uint32_t TxState;
  __IO uint32_t RxState; /**< Reception state. */
} USBD_CDC_HandleTypeDef;
/**
  * @}
  */

/** @defgroup usbd_cdc_Exported_Variables USBD CDC Exported Variables
  * @brief Class driver exported by the USB CDC class.
  * @{
  */

/** @brief CDC class driver. */
extern USBD_ClassTypeDef USBD_CDC;
/**
 * @brief Pointer to the CDC class driver, as expected by USBD_RegisterClass().
 */
#define USBD_CDC_CLASS &USBD_CDC
/**
  * @}
  */

/** @defgroup usbd_cdc_Exported_Functions USBD CDC Exported Functions
  * @brief Functions used by the application to drive the USB CDC class.
  * @{
  */
/**
 * @brief Register the application callbacks for the CDC class.
 * @param pdev device instance.
 * @param fops pointer to the CDC interface callbacks.
 * @return USBD_OK on success, USBD_FAIL if fops is NULL.
 */
uint8_t USBD_CDC_RegisterInterface(USBD_HandleTypeDef *pdev,
                                   USBD_CDC_ItfTypeDef *fops);

/**
 * @brief Set the buffer and length of the next data to send on the CDC IN endpoint.
 * @note Does not start the transfer, call USBD_CDC_TransmitPacket() for that.
 * @param pdev device instance.
 * @param pbuff pointer to the Tx buffer.
 * @param length length of the data to send, in bytes.
 * @param ClassId class ID, used only when USE_USBD_COMPOSITE is defined.
 * @return USBD_OK on success, USBD_FAIL if the class instance is not allocated.
 */
#ifdef USE_USBD_COMPOSITE
uint8_t USBD_CDC_SetTxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff,
                             uint32_t length, uint8_t ClassId);
#else
uint8_t USBD_CDC_SetTxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff,
                             uint32_t length);
#endif /* USE_USBD_COMPOSITE */

/**
 * @brief Set the Rx buffer used for the next packet received on the CDC OUT endpoint.
 * @param pdev device instance.
 * @param pbuff pointer to the Rx buffer.
 * @return USBD_OK on success, USBD_FAIL if the class instance is not allocated.
 */
uint8_t USBD_CDC_SetRxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff);

/**
 * @brief Transmit the buffer set by USBD_CDC_SetTxBuffer() on the CDC IN endpoint.
 * @note Does nothing if a transfer is already in progress.
 * @param pdev device instance.
 * @param ClassId class ID, used only when USE_USBD_COMPOSITE is defined.
 * @return USBD_OK if the transfer was started, USBD_BUSY if a transfer is in
 *         progress, USBD_FAIL if the class instance is not allocated.
 */
#ifdef USE_USBD_COMPOSITE
uint8_t USBD_CDC_TransmitPacket(USBD_HandleTypeDef *pdev, uint8_t ClassId);
#else
uint8_t USBD_CDC_TransmitPacket(USBD_HandleTypeDef *pdev);
#endif /* USE_USBD_COMPOSITE */

/**
 * @brief Prepare the CDC OUT endpoint to receive the next packet into the Rx buffer.
 * @param pdev device instance.
 * @return USBD_OK on success, USBD_FAIL if the class instance is not allocated.
 */
uint8_t USBD_CDC_ReceivePacket(USBD_HandleTypeDef *pdev);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_CDC_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
