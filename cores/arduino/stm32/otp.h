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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OTP_H
#define __OTP_H

#include "stm32_def.h"

#ifdef OTP_AREA_BASE
#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32WBxx
/*
 * See AN5042: Precise HSE frequency and startup time tuning
 * for STM32 wireless MCUs. Each OTP structure type is indicated
 * by its index (one byte).The index used for the BT structure is 0.
 */
typedef struct __packed {
  uint8_t   bd_address[6];
  uint8_t   hse_tuning;
  uint8_t   id;
} OTP_BT_t;
#endif /* STM32WBxx */

/* Exported functions --------------------------------------------------------*/

/**
 * @brief This API return the address (64 bits aligned) of the ID parameter in the OTP
 *        It returns the first ID declaration found from the higher address down to the base address
 *        The user shall fill the OTP from the base address to the top of the OTP so that the more recent
 *        declaration is returned by the API
 *        The OTP manager handles only 64 bits parameter
 *        | Id    | Parameter |
 *        | 8bits | 58bits    |
 *        | MSB   |  LSB      |
 *
 * @param  id: ID of the parameter to read from OTP
 * @retval Address of the ID in the OTP - returns 0 when no ID found
 */
uint8_t *OTP_Read(uint8_t id);

#ifdef __cplusplus
}
#endif
#endif /* OTP_AREA_BASE */
#endif /*__OTP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
