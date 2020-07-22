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

void USBD_reenumerate(void);
#ifdef USBD_USE_CDC
void USBD_CDC_init(void);
#endif
#ifdef __cplusplus
}
#endif
#endif /* USBCON */
#endif /* __USBD_IF_H */
