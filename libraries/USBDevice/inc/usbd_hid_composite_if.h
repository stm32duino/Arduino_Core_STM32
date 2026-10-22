/**
  ******************************************************************************
  * @file    usbd_hid_composite_if.h
  * @brief   Header for USB HID composite interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics
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
#ifndef __USBD_HID_COMPOSITE_IF_H
#define __USBD_HID_COMPOSITE_IF_H
#ifdef USBCON
#ifdef USBD_USE_HID_COMPOSITE

/* Includes ------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum {
  HID_KEYBOARD,
  HID_MOUSE
} HID_Interface;

/* Exported macro ------------------------------------------------------------*/
#define IS_HID_INTERFACE(DEVICE)    (((DEVICE) == HID_KEYBOARD) ||\
                                     ((DEVICE) == HID_MOUSE))

/* Exported functions ------------------------------------------------------- */
/**
 * @brief Initialize the USB device stack for a HID composite interface.
 * @param device HID interface to enable: HID_KEYBOARD or HID_MOUSE.
 * @note The USB device is started once, when the first interface is
 *       initialized. Calling it again for the other interface only
 *       marks it as active.
 */
void HID_Composite_Init(HID_Interface device);

/**
 * @brief Release a HID composite interface.
 * @param device HID interface to release: HID_KEYBOARD or HID_MOUSE.
 * @note The USB device is stopped and de-initialized once no interface
 *       is active.
 */
void HID_Composite_DeInit(HID_Interface device);

/**
 * @brief Send a HID mouse report.
 * @param report Pointer to the report data.
 * @param len Length of the report, in bytes.
 */
void HID_Composite_mouse_sendReport(uint8_t *report, uint16_t len);

/**
 * @brief Send a HID keyboard report.
 * @param report Pointer to the report data.
 * @param len Length of the report, in bytes.
 */
void HID_Composite_keyboard_sendReport(uint8_t *report, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif /* USBD_USE_HID_COMPOSITE */
#endif /* USBCON */

#endif /* __USBD_HID_COMPOSITE_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
