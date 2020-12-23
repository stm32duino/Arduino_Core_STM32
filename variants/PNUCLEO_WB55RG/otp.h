/**
  ******************************************************************************
  * @file    otp.h
  * @author  MCD Application Team
  * @brief   OTP manager  interface
  ******************************************************************************
   * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OTP_H
#define __OTP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __packed {
  uint8_t   bd_address[6];
  uint8_t   hse_tuning;
  uint8_t   id;
} OTP_ID0_t;

/* Exported constants --------------------------------------------------------*/
#define CFG_OTP_BASE_ADDRESS  OTP_AREA_BASE

#define CFG_OTP_END_ADDRESS OTP_AREA_END_ADDR

#ifdef __cplusplus
}
#endif

#endif /*__OTP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
