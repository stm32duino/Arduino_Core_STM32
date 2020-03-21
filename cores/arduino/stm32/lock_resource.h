/**
  ******************************************************************************
  * @file    lock_resource.h
  * @author  MCD Application Team
  * @brief   Header for lock_resource.c
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
#ifndef _LOCK_RESOURCE_H
#define _LOCK_RESOURCE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum {
  LOCK_RESOURCE_STATUS_OK       = 0x00U,
  LOCK_RESOURCE_STATUS_ERROR    = 0x01U,
  LOCK_RESOURCE_STATUS_TIMEOUT  = 0x02U
} LockResource_Status_t;

/* Exported constants --------------------------------------------------------*/
#define LOCK_RESOURCE_TIMEOUT   100U /* timeout in ms */

/* Exported macro ------------------------------------------------------------*/
#define PERIPH_LOCK(__Periph__)       Periph_Lock(__Periph__, LOCK_RESOURCE_TIMEOUT)
#define PERIPH_UNLOCK(__Periph__)     Periph_Unlock(__Periph__)

/* Exported functions ------------------------------------------------------- */
LockResource_Status_t Periph_Lock(void *Peripheral, uint32_t Timeout);
void Periph_Unlock(void *Peripheral);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _LOCK_RESOURCE_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
