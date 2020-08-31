/**
  ******************************************************************************
  * @file    usbd_msc_storage_template.c
  * @author  MCD Application Team
  * @brief   Memory management layer
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

#include "usbd_ep_conf.h"

#ifdef USBCON
#ifdef USBD_USE_MSC_CLASS

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
- "stm32xxxxx_{eval}{discovery}{adafruit}_sd.c"
EndBSPDependencies */

#include "USBMscHandler.h"
#include "usbd_msc_storage_if.h"

uint8_t usbMscMaxLun = 0;
USBMscHandler **ppUsbMscHandlers = nullptr;

int8_t STORAGE_Init(uint8_t lun);

int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num,
                           uint16_t *block_size);

int8_t  STORAGE_IsReady(uint8_t lun);

int8_t  STORAGE_IsWriteProtected(uint8_t lun);

int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
                    uint16_t blk_len);

int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
                     uint16_t blk_len);

int8_t STORAGE_GetMaxLun(void);

/* USB Mass storage Standard Inquiry Data */
uint8_t  STORAGE_Inquirydata[] =  /* 36 */
{
  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0', '1',                     /* Version      : 4 Bytes */
};

USBD_StorageTypeDef USBD_MSC_fops = {
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  STORAGE_Inquirydata,
};

#define HANDLER_LUN_CHECK \
  if (lun > usbMscMaxLun) { \
    return 1; \
  }

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Init(uint8_t lun)
{
  HANDLER_LUN_CHECK

  return !ppUsbMscHandlers[lun]->Init();
}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  HANDLER_LUN_CHECK

  return !ppUsbMscHandlers[lun]->GetCapacity(block_num, block_size);
}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : 0 if device is ready, otherwise not ready
*******************************************************************************/
int8_t  STORAGE_IsReady(uint8_t lun)
{
  HANDLER_LUN_CHECK

  return !ppUsbMscHandlers[lun]->IsReady();
}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsWriteProtected(uint8_t lun)
{
  HANDLER_LUN_CHECK

  return ppUsbMscHandlers[lun]->IsWriteProtected();
}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Read(uint8_t lun, uint8_t *buf,
                    uint32_t blk_addr, uint16_t blk_len)
{
  HANDLER_LUN_CHECK

  return !ppUsbMscHandlers[lun]->Read(buf, blk_addr, blk_len);
}

/*******************************************************************************
* Function Name  : Write_Memory
* Description    : Handle the Write operation to the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Write(uint8_t lun, uint8_t *buf,
                     uint32_t blk_addr, uint16_t blk_len)
{
  HANDLER_LUN_CHECK

  return !ppUsbMscHandlers[lun]->Write(buf, blk_addr, blk_len);
}

/*******************************************************************************
* Function Name  : Write_Memory
* Description    : Handle the Write operation to the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetMaxLun(void)
{
  return usbMscMaxLun;
}

#endif /* USBD_USE_MSC_CLASS */
#endif /* USBCON */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
