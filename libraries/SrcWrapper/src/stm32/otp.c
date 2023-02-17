/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include "otp.h"

#ifdef OTP_AREA_BASE

uint8_t *OTP_Read(uint8_t id)
{
  uint8_t *p_id;

  p_id = (uint8_t *)(OTP_AREA_END_ADDR - 7) ;

  while (((*(p_id + 7)) != id) && (p_id != (uint8_t *)OTP_AREA_BASE)) {
    p_id -= 8 ;
  }

  if ((*(p_id + 7)) != id) {
    p_id = 0 ;
  }

  return p_id ;
}

#endif /* OTP_AREA_BASE */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
