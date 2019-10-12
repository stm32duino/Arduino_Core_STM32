/**
  ******************************************************************************
  * File Name          : mbox_hsem.c
  * Description        : This file provides code for the configuration
  *                      of the mailbox based on hardware semaphore.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "openamp/open_amp.h"
#include "stm32h7xx_hal.h"
#include "openamp_conf.h"
#include "mbox_hsem.h"
//#include "metal/atomic.h"
//#include "metal/device.h"

/* Within 'USER CODE' section, code will be kept by default at each generation */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* Private define ------------------------------------------------------------*/
#define RX_NO_MSG           0
#define RX_NEW_MSG          1

/* Private variables ---------------------------------------------------------*/
static uint32_t msg_received = RX_NO_MSG;

/* Private functions ---------------------------------------------------------*/
void HAL_HSEM_FreeCallback(uint32_t SemMask)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(SemMask);
  msg_received = RX_NEW_MSG;

#ifdef CORE_CM7
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));   
#endif
#ifdef CORE_CM4
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));   
#endif  
}

/**
  * @brief  Initialize MAILBOX with IPCC peripheral
  * @param  None
  * @retval : Operation result
  */
int MAILBOX_Init(void)
{
  __HAL_RCC_HSEM_CLK_ENABLE();

#ifdef CORE_CM7
  /* Enable CM7 receive irq */
  HAL_NVIC_SetPriority(HSEM1_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(HSEM1_IRQn);
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));    
#endif        
#ifdef CORE_CM4 
  /* Enable CM4 receive irq */
  HAL_NVIC_SetPriority(HSEM2_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(HSEM2_IRQn);
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));    
#endif

  return 0;
}

/**
  * @brief  Initialize MAILBOX with IPCC peripheral
  * @param  virtio device
  * @retval : Operation result
  */
int MAILBOX_Poll(struct virtio_device *vdev)
{
  /* If we got an interrupt, ask for the corresponding virtqueue processing */

  if (msg_received == RX_NEW_MSG)
  {
#ifdef CORE_CM7   
    rproc_virtio_notified(vdev, VRING0_ID);
#endif                
#ifdef CORE_CM4   
    rproc_virtio_notified(vdev, VRING1_ID);
#endif                
    msg_received = RX_NO_MSG;
    return 0;
  }

  return -EAGAIN;
}

/**
  * @brief  Callback function called by OpenAMP MW to notify message processing
  * @param  VRING id
  * @retval Operation result
  */
int MAILBOX_Notify(void *priv, uint32_t id)
{
   (void)priv;
   (void)id;

#ifdef CORE_CM7 
  HAL_HSEM_FastTake(HSEM_ID_0); 
  HAL_HSEM_Release(HSEM_ID_0,0);
#endif                
#ifdef CORE_CM4   
  HAL_HSEM_FastTake(HSEM_ID_1); 
  HAL_HSEM_Release(HSEM_ID_1,0);
#endif  

  return 0;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
