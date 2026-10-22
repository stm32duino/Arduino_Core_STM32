/**
  ******************************************************************************
  * @file    usbd_if.h
  * @author  fpistm
  * @brief   Header file for the usbd_if.c file
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_IF_H
#define __USBD_IF_H

#ifdef USBCON
/* Includes ------------------------------------------------------------------*/
#include "Arduino.h"

/* Re-enumeration handling*/
#ifndef USBD_ENUM_DELAY
  #define USBD_ENUM_DELAY 10
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Force to re-enumerate USB.
 *
 * Intended to be called at startup by core code. It can also be used at
 * runtime, while USB is connected, but that does not work in all cases
 * (when USB is enabled on an F103C8, setting output mode on the DP pin
 * no longer has any effect).
 */
void USBD_reenumerate(void);

#ifdef USBD_USE_CDC
/**
 * @brief Initialize the CDC interface used by the USB serial port.
 */
void USBD_CDC_init(void);
#endif

/**
 * @brief Configure the system clock and system IP clocks after wake-up
 *        from the USB resume callback.
 * @note  Weak function, can be redefined by the user at the sketch level.
 *        By default, calls configIPClock() and SystemClock_Config().
 */
void USBD_SystemClockConfigFromResume(void);

#ifdef __cplusplus
}
#endif
#endif /* USBCON */
#endif /* __USBD_IF_H */
