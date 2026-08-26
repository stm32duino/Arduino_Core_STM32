/**
  ******************************************************************************
  * @file    usbd_msc_scsi.c
  * @author  MCD Application Team
  * @brief   This file provides all the USBD SCSI layer functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
- "stm32xxxxx_{eval}{discovery}{adafruit}_sd.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc_bot.h"
#include "usbd_msc_scsi.h"
#include "usbd_msc.h"
#include "usbd_msc_data.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup MSC_SCSI
  * @brief Mass storage SCSI layer module
  * @{
  */

/** @defgroup MSC_SCSI_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup MSC_SCSI_Private_Defines
  * @{
  */

/**
  * @}
  */


/** @defgroup MSC_SCSI_Private_Macros
  * @{
  */
/**
  * @}
  */


/** @defgroup MSC_SCSI_Private_Variables
  * @{
  */
extern uint8_t MSCInEpAdd;
extern uint8_t MSCOutEpAdd;
/**
  * @}
  */


/** @defgroup MSC_SCSI_Private_FunctionPrototypes
  * @{
  */
static int8_t SCSI_TestUnitReady(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_Inquiry(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ReadFormatCapacity(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ReadCapacity10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ReadCapacity16(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_RequestSense(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_StartStopUnit(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_AllowPreventRemovable(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ProcessModeSelect(USBD_HandleTypeDef *pdev, uint8_t lun,
                                     uint32_t param_list_length);
static int8_t SCSI_ModeSelect6(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ModeSelect10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ModeSense6(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ModeSense10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_Write10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_Write12(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_Read10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_Read12(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_Verify10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ReportLuns(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_ReceiveDiagnosticResults(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params);
static int8_t SCSI_CheckAddressRange(USBD_HandleTypeDef *pdev, uint8_t lun,
                                     uint32_t blk_offset, uint32_t blk_nbr);

static int8_t SCSI_ProcessRead(USBD_HandleTypeDef *pdev, uint8_t lun);
static int8_t SCSI_ProcessWrite(USBD_HandleTypeDef *pdev, uint8_t lun);

static int8_t SCSI_UpdateBotData(USBD_MSC_BOT_HandleTypeDef *hmsc,
                                 uint8_t *pBuff, uint16_t length);
/**
  * @}
  */


/** @defgroup MSC_SCSI_Private_Functions
  * @{
  */


/**
  * @brief  SCSI_ProcessCmd
  *         Process SCSI commands
  * @param  pdev: device instance
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
int8_t SCSI_ProcessCmd(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *cmd)
{
  int8_t ret;
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  switch (cmd[0])
  {
    case SCSI_TEST_UNIT_READY:
      ret = SCSI_TestUnitReady(pdev, lun, cmd);
      break;

    case SCSI_REQUEST_SENSE:
      ret = SCSI_RequestSense(pdev, lun, cmd);
      break;

    case SCSI_INQUIRY:
      ret = SCSI_Inquiry(pdev, lun, cmd);
      break;

    case SCSI_START_STOP_UNIT:
      ret = SCSI_StartStopUnit(pdev, lun, cmd);
      break;

    case SCSI_ALLOW_MEDIUM_REMOVAL:
      ret = SCSI_AllowPreventRemovable(pdev, lun, cmd);
      break;

    case SCSI_MODE_SELECT6:
      ret = SCSI_ModeSelect6(pdev, lun, cmd);
      break;

    case SCSI_MODE_SELECT10:
      ret = SCSI_ModeSelect10(pdev, lun, cmd);
      break;

    case SCSI_MODE_SENSE6:
      ret = SCSI_ModeSense6(pdev, lun, cmd);
      break;

    case SCSI_MODE_SENSE10:
      ret = SCSI_ModeSense10(pdev, lun, cmd);
      break;

    case SCSI_READ_FORMAT_CAPACITIES:
      ret = SCSI_ReadFormatCapacity(pdev, lun, cmd);
      break;

    case SCSI_READ_CAPACITY10:
      ret = SCSI_ReadCapacity10(pdev, lun, cmd);
      break;

    case SCSI_READ_CAPACITY16:
      ret = SCSI_ReadCapacity16(pdev, lun, cmd);
      break;

    case SCSI_READ10:
      ret = SCSI_Read10(pdev, lun, cmd);
      break;

    case SCSI_READ12:
      ret = SCSI_Read12(pdev, lun, cmd);
      break;

    case SCSI_WRITE10:
      ret = SCSI_Write10(pdev, lun, cmd);
      break;

    case SCSI_WRITE12:
      ret = SCSI_Write12(pdev, lun, cmd);
      break;

    case SCSI_VERIFY10:
      ret = SCSI_Verify10(pdev, lun, cmd);
      break;

    case SCSI_REPORT_LUNS:
      ret = SCSI_ReportLuns(pdev, lun, cmd);
      break;

    case SCSI_RECEIVE_DIAGNOSTIC_RESULTS:
      ret = SCSI_ReceiveDiagnosticResults(pdev, lun, cmd);
      break;

    default:
      SCSI_SenseCode(pdev, lun, ILLEGAL_REQUEST, INVALID_CDB);
      hmsc->bot_state = USBD_BOT_NO_DATA;
      ret = -1;
      break;
  }

  return ret;
}


/**
  * @brief  SCSI_TestUnitReady
  *         Process SCSI Test Unit Ready Command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_TestUnitReady(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  UNUSED(params);
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  /* case 9 : Hi > D0 */
  if (hmsc->cbw.dDataLength != 0U)
  {
    SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);

    return -1;
  }

  if (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED)
  {
    SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
    hmsc->bot_state = USBD_BOT_NO_DATA;
    return -1;
  }

  if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsReady(lun) != 0)
  {
    SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
    hmsc->bot_state = USBD_BOT_NO_DATA;

    return -1;
  }
  hmsc->bot_data_length = 0U;

  return 0;
}


/**
  * @brief  SCSI_Inquiry
  *         Process Inquiry command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_Inquiry(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  uint8_t *pPage;
  uint16_t len;
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  if (hmsc->cbw.dDataLength == 0U)
  {
    SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
    return -1;
  }

  if ((params[1] & 0x01U) != 0U) /* Evpd is set */
  {
    if (params[2] == 0U) /* Request for Supported Vital Product Data Pages*/
    {
      (void)SCSI_UpdateBotData(hmsc, MSC_Page00_Inquiry_Data, LENGTH_INQUIRY_PAGE00);
    }
    else if (params[2] == 0x80U) /* Request for VPD page 0x80 Unit Serial Number */
    {
      (void)SCSI_UpdateBotData(hmsc, MSC_Page80_Inquiry_Data, LENGTH_INQUIRY_PAGE80);
    }
    else /* Request Not supported */
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST,
                     INVALID_FIELD_IN_COMMAND);

      return -1;
    }
  }
  else
  {

    pPage = (uint8_t *) & ((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId]) \
            ->pInquiry[lun * STANDARD_INQUIRY_DATA_LEN];
    len = (uint16_t)pPage[4] + 5U;

    if (params[4] <= len)
    {
      len = params[4];
    }

    (void)SCSI_UpdateBotData(hmsc, pPage, len);
  }

  return 0;
}


/**
  * @brief  SCSI_ReadCapacity10
  *         Process Read Capacity 10 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ReadCapacity10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  UNUSED(params);
  int8_t ret;
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

  ret = ((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->GetCapacity(lun, &p_scsi_blk->nbr,
                                                                             &p_scsi_blk->size);

  if ((ret != 0) || (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED))
  {
    SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
    return -1;
  }

  hmsc->bot_data[0] = (uint8_t)((p_scsi_blk->nbr - 1U) >> 24);
  hmsc->bot_data[1] = (uint8_t)((p_scsi_blk->nbr - 1U) >> 16);
  hmsc->bot_data[2] = (uint8_t)((p_scsi_blk->nbr - 1U) >>  8);
  hmsc->bot_data[3] = (uint8_t)(p_scsi_blk->nbr - 1U);

  hmsc->bot_data[4] = (uint8_t)(p_scsi_blk->size >> 24);
  hmsc->bot_data[5] = (uint8_t)(p_scsi_blk->size >> 16);
  hmsc->bot_data[6] = (uint8_t)(p_scsi_blk->size >> 8);
  hmsc->bot_data[7] = (uint8_t)(p_scsi_blk->size);

  hmsc->bot_data_length = 8U;

  return 0;
}


/**
  * @brief  SCSI_ReadCapacity16
  *         Process Read Capacity 16 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ReadCapacity16(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  uint32_t idx;
  uint32_t alloc_len;
  int8_t ret;
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

  ret = ((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->GetCapacity(lun, &p_scsi_blk->nbr,
                                                                             &p_scsi_blk->size);

  if ((ret != 0) || (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED))
  {
    SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
    return -1;
  }

  /* READ CAPACITY(16) response is 32 bytes per SBC-3 */
  for (idx = 0U; idx < 32U; idx++)
  {
    hmsc->bot_data[idx] = 0U;
  }

  hmsc->bot_data[4] = (uint8_t)((p_scsi_blk->nbr - 1U) >> 24);
  hmsc->bot_data[5] = (uint8_t)((p_scsi_blk->nbr - 1U) >> 16);
  hmsc->bot_data[6] = (uint8_t)((p_scsi_blk->nbr - 1U) >>  8);
  hmsc->bot_data[7] = (uint8_t)(p_scsi_blk->nbr - 1U);

  hmsc->bot_data[8] = (uint8_t)(p_scsi_blk->size >>  24);
  hmsc->bot_data[9] = (uint8_t)(p_scsi_blk->size >>  16);
  hmsc->bot_data[10] = (uint8_t)(p_scsi_blk->size >>  8);
  hmsc->bot_data[11] = (uint8_t)(p_scsi_blk->size);

  /* Clamp transfer length to actual response size (32 bytes) */
  alloc_len = ((uint32_t)params[10] << 24) |
              ((uint32_t)params[11] << 16) |
              ((uint32_t)params[12] <<  8) |
              (uint32_t)params[13];

  hmsc->bot_data_length = MIN(alloc_len, 32U);

  return 0;
}


/**
  * @brief  SCSI_ReadFormatCapacity
  *         Process Read Format Capacity command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ReadFormatCapacity(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  uint16_t blk_size;
  uint16_t alloc_len;
  uint32_t blk_nbr;
  uint16_t i;
  int8_t ret;
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  ret = ((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->GetCapacity(lun, &blk_nbr, &blk_size);

  if ((ret != 0) || (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED))
  {
    SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
    return -1;
  }

  for (i = 0U; i < 12U ; i++)
  {
    hmsc->bot_data[i] = 0U;
  }

  hmsc->bot_data[3] = 0x08U;
  hmsc->bot_data[4] = (uint8_t)((blk_nbr - 1U) >> 24);
  hmsc->bot_data[5] = (uint8_t)((blk_nbr - 1U) >> 16);
  hmsc->bot_data[6] = (uint8_t)((blk_nbr - 1U) >>  8);
  hmsc->bot_data[7] = (uint8_t)(blk_nbr - 1U);

  hmsc->bot_data[8] = 0x02U;
  hmsc->bot_data[9] = (uint8_t)(blk_size >>  16);
  hmsc->bot_data[10] = (uint8_t)(blk_size >>  8);
  hmsc->bot_data[11] = (uint8_t)(blk_size);

  alloc_len = ((uint16_t)params[7] << 8) | (uint16_t)params[8];
  hmsc->bot_data_length = MIN(alloc_len, READ_FORMAT_CAPACITY_DATA_LEN);

  return 0;
}


/**
  * @brief  SCSI_ProcessModeSelect
  *         Drain MODE SELECT parameter data without applying mode pages
  * @param  lun: Logical unit number
  * @param  param_list_length: Mode parameter list length from the CDB
  * @retval status
  */
static int8_t SCSI_ProcessModeSelect(USBD_HandleTypeDef *pdev, uint8_t lun,
                                     uint32_t param_list_length)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;
  uint32_t packet_length;
  uint32_t rx_length;

  UNUSED(param_list_length);

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

#ifdef USE_USBD_COMPOSITE
  /* Get the Endpoints addresses allocated for this class instance */
  MSCOutEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_OUT, USBD_EP_TYPE_BULK, (uint8_t)pdev->classId);
#endif /* USE_USBD_COMPOSITE */

  if (hmsc->bot_state == USBD_BOT_IDLE)
  {
    if ((hmsc->cbw.bmFlags & 0x80U) == 0x80U)
    {
      hmsc->bot_state = USBD_BOT_NO_DATA;
      hmsc->bot_data_length = 0U;
      return 0;
    }

    if (hmsc->cbw.dDataLength == 0U)
    {
      hmsc->bot_data_length = 0U;
      return 0;
    }

    p_scsi_blk->len = hmsc->cbw.dDataLength;
    hmsc->bot_state = USBD_BOT_DATA_OUT;

    packet_length = MIN(p_scsi_blk->len, MSC_MEDIA_PACKET);
    (void)USBD_LL_PrepareReceive(pdev, MSCOutEpAdd, hmsc->bot_data, packet_length);

    return 0;
  }

  rx_length = USBD_LL_GetRxDataSize(pdev, MSCOutEpAdd);

  if (rx_length >= p_scsi_blk->len)
  {
    hmsc->csw.dDataResidue -= p_scsi_blk->len;
    p_scsi_blk->len = 0U;
    MSC_BOT_SendCSW(pdev, USBD_CSW_CMD_PASSED);
  }
  else
  {
    p_scsi_blk->len -= rx_length;
    hmsc->csw.dDataResidue -= rx_length;
    packet_length = MIN(p_scsi_blk->len, MSC_MEDIA_PACKET);
    (void)USBD_LL_PrepareReceive(pdev, MSCOutEpAdd, hmsc->bot_data, packet_length);
  }

  return 0;
}


/**
  * @brief  SCSI_ModeSelect6
  *         Process Mode Select6 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ModeSelect6(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  return SCSI_ProcessModeSelect(pdev, lun, params[4]);
}


/**
  * @brief  SCSI_ModeSelect10
  *         Process Mode Select10 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ModeSelect10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  uint32_t param_list_length;

  param_list_length = ((uint32_t)params[7] << 8) | (uint32_t)params[8];

  return SCSI_ProcessModeSelect(pdev, lun, param_list_length);
}


/**
  * @brief  SCSI_ModeSense6
  *         Process Mode Sense6 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ModeSense6(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  uint16_t len = MODE_SENSE6_LEN;

  if (hmsc == NULL)
  {
    return -1;
  }

  /* Check If media is write-protected */
  if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsWriteProtected(lun) != 0)
  {
    MSC_Mode_Sense6_data[2] |= (0x1U << 7); /* Set the WP (write protection) bit */
  }
  else
  {
    MSC_Mode_Sense6_data[2] &= ~(0x1U << 7); /* Clear the WP (write protection) bit */
  }

  if (params[4] <= len)
  {
    len = params[4];
  }

  (void)SCSI_UpdateBotData(hmsc, MSC_Mode_Sense6_data, len);

  return 0;
}


/**
  * @brief  SCSI_ModeSense10
  *         Process Mode Sense10 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ModeSense10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  uint16_t len = MODE_SENSE10_LEN;
  uint16_t alloc_len;

  if (hmsc == NULL)
  {
    return -1;
  }

  /* Check If media is write-protected */
  if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsWriteProtected(lun) != 0)
  {
    MSC_Mode_Sense10_data[3] |= (0x1U << 7); /* Set the WP (write protection) bit */
  }
  else
  {
    MSC_Mode_Sense10_data[3] &= ~(0x1U << 7); /* Clear the WP (write protection) bit */
  }

  /* Allocation length is a 16-bit field: CDB bytes 7-8 */
  alloc_len = ((uint16_t)params[7] << 8) | (uint16_t)params[8];

  if (alloc_len < len)
  {
    len = alloc_len;
  }

  (void)SCSI_UpdateBotData(hmsc, MSC_Mode_Sense10_data, len);

  return 0;
}


/**
  * @brief  SCSI_RequestSense
  *         Process Request Sense command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_RequestSense(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  UNUSED(lun);
  uint8_t i;
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  if (hmsc->cbw.dDataLength == 0U)
  {
    SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
    return -1;
  }

  for (i = 0U; i < REQUEST_SENSE_DATA_LEN; i++)
  {
    hmsc->bot_data[i] = 0U;
  }

  hmsc->bot_data[0] = 0x70U;
  hmsc->bot_data[7] = REQUEST_SENSE_DATA_LEN - 6U;

  if ((hmsc->scsi_sense_head != hmsc->scsi_sense_tail))
  {
    hmsc->bot_data[2] = (uint8_t)hmsc->scsi_sense[hmsc->scsi_sense_head].Skey;
    hmsc->bot_data[12] = (uint8_t)hmsc->scsi_sense[hmsc->scsi_sense_head].w.b.ASC;
    hmsc->bot_data[13] = (uint8_t)hmsc->scsi_sense[hmsc->scsi_sense_head].w.b.ASCQ;
    hmsc->scsi_sense_head++;

    if (hmsc->scsi_sense_head == SENSE_LIST_DEEPTH)
    {
      hmsc->scsi_sense_head = 0U;
    }
  }

  hmsc->bot_data_length = REQUEST_SENSE_DATA_LEN;

  if (params[4] <= REQUEST_SENSE_DATA_LEN)
  {
    hmsc->bot_data_length = params[4];
  }

  return 0;
}


/**
  * @brief  SCSI_SenseCode
  *         Load the last error code in the error list
  * @param  lun: Logical unit number
  * @param  sKey: Sense Key
  * @param  ASC: Additional Sense Code
  * @retval none

  */
void SCSI_SenseCode(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t sKey, uint8_t ASC)
{
  UNUSED(lun);
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return;
  }

  hmsc->scsi_sense[hmsc->scsi_sense_tail].Skey = sKey;
  hmsc->scsi_sense[hmsc->scsi_sense_tail].w.b.ASC = ASC;
  hmsc->scsi_sense[hmsc->scsi_sense_tail].w.b.ASCQ = 0U;
  hmsc->scsi_sense_tail++;

  if (hmsc->scsi_sense_tail == SENSE_LIST_DEEPTH)
  {
    hmsc->scsi_sense_tail = 0U;
  }

  if (hmsc->scsi_sense_tail == hmsc->scsi_sense_head)
  {
    hmsc->scsi_sense_head++;

    if (hmsc->scsi_sense_head == SENSE_LIST_DEEPTH)
    {
      hmsc->scsi_sense_head = 0U;
    }
  }
}


/**
  * @brief  SCSI_StartStopUnit
  *         Process Start Stop Unit command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_StartStopUnit(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  UNUSED(lun);
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  if ((hmsc->scsi_medium_state == SCSI_MEDIUM_LOCKED) && ((params[4] & 0x3U) == 2U))
  {
    SCSI_SenseCode(pdev, lun, ILLEGAL_REQUEST, INVALID_FIELD_IN_COMMAND);

    return -1;
  }

  if ((params[4] & 0x3U) == 0x1U) /* START=1 */
  {
    hmsc->scsi_medium_state = SCSI_MEDIUM_UNLOCKED;
  }
  else if ((params[4] & 0x3U) == 0x2U) /* START=0 and LOEJ Load Eject=1 */
  {
    hmsc->scsi_medium_state = SCSI_MEDIUM_EJECTED;
  }
  else if ((params[4] & 0x3U) == 0x3U) /* START=1 and LOEJ Load Eject=1 */
  {
    hmsc->scsi_medium_state = SCSI_MEDIUM_UNLOCKED;
  }
  else
  {
    /* .. */
  }
  hmsc->bot_data_length = 0U;

  return 0;
}


/**
  * @brief  SCSI_AllowPreventRemovable
  *         Process Allow Prevent Removable medium command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_AllowPreventRemovable(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  UNUSED(lun);
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  if (params[4] == 0U)
  {
    hmsc->scsi_medium_state = SCSI_MEDIUM_UNLOCKED;
  }
  else
  {
    hmsc->scsi_medium_state = SCSI_MEDIUM_LOCKED;
  }

  hmsc->bot_data_length = 0U;

  return 0;
}


/**
  * @brief  SCSI_Read10
  *         Process Read10 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_Read10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

  if (hmsc->bot_state == USBD_BOT_IDLE) /* Idle */
  {
    /* case 10 : Ho <> Di */
    if ((hmsc->cbw.bmFlags & 0x80U) != 0x80U)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    if (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);

      return -1;
    }

    if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsReady(lun) != 0)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
      return -1;
    }

    p_scsi_blk->addr = ((uint32_t)params[2] << 24) |
                       ((uint32_t)params[3] << 16) |
                       ((uint32_t)params[4] <<  8) |
                       (uint32_t)params[5];

    p_scsi_blk->len = ((uint32_t)params[7] <<  8) | (uint32_t)params[8];

    if (SCSI_CheckAddressRange(pdev, lun, p_scsi_blk->addr, p_scsi_blk->len) < 0)
    {
      return -1; /* error */
    }

    /* cases 4,5 : Hi <> Dn */
    if (hmsc->cbw.dDataLength != (p_scsi_blk->len * p_scsi_blk->size))
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    hmsc->bot_state = USBD_BOT_DATA_IN;
  }
  hmsc->bot_data_length = MSC_MEDIA_PACKET;

  return SCSI_ProcessRead(pdev, lun);
}


/**
  * @brief  SCSI_Read12
  *         Process Read12 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_Read12(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

  if (hmsc->bot_state == USBD_BOT_IDLE) /* Idle */
  {
    /* case 10 : Ho <> Di */
    if ((hmsc->cbw.bmFlags & 0x80U) != 0x80U)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    if (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
      return -1;
    }

    if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsReady(lun) != 0)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
      return -1;
    }

    p_scsi_blk->addr = ((uint32_t)params[2] << 24) |
                       ((uint32_t)params[3] << 16) |
                       ((uint32_t)params[4] <<  8) |
                       (uint32_t)params[5];

    p_scsi_blk->len = ((uint32_t)params[6] << 24) |
                      ((uint32_t)params[7] << 16) |
                      ((uint32_t)params[8] << 8) |
                      (uint32_t)params[9];

    if (SCSI_CheckAddressRange(pdev, lun, p_scsi_blk->addr, p_scsi_blk->len) < 0)
    {
      return -1; /* error */
    }

    /* cases 4,5 : Hi <> Dn */
    if (hmsc->cbw.dDataLength != (p_scsi_blk->len * p_scsi_blk->size))
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    hmsc->bot_state = USBD_BOT_DATA_IN;
  }
  hmsc->bot_data_length = MSC_MEDIA_PACKET;

  return SCSI_ProcessRead(pdev, lun);
}


/**
  * @brief  SCSI_Write10
  *         Process Write10 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_Write10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;
  uint32_t len;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

#ifdef USE_USBD_COMPOSITE
  /* Get the Endpoints addresses allocated for this class instance */
  MSCOutEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_OUT, USBD_EP_TYPE_BULK, (uint8_t)pdev->classId);
#endif /* USE_USBD_COMPOSITE */

  if (hmsc->bot_state == USBD_BOT_IDLE) /* Idle */
  {
    if (hmsc->cbw.dDataLength == 0U)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    /* case 8 : Hi <> Do */
    if ((hmsc->cbw.bmFlags & 0x80U) == 0x80U)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    if (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
      hmsc->bot_state = USBD_BOT_NO_DATA;
      return -1;
    }

    /* Check whether Media is ready */
    if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsReady(lun) != 0)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
      hmsc->bot_state = USBD_BOT_NO_DATA;
      return -1;
    }

    /* Check If media is write-protected */
    if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsWriteProtected(lun) != 0)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, WRITE_PROTECTED);
      hmsc->bot_state = USBD_BOT_NO_DATA;
      return -1;
    }

    p_scsi_blk->addr = ((uint32_t)params[2] << 24) |
                       ((uint32_t)params[3] << 16) |
                       ((uint32_t)params[4] << 8) |
                       (uint32_t)params[5];

    p_scsi_blk->len = ((uint32_t)params[7] << 8) |
                      (uint32_t)params[8];

    /* check if LBA address is in the right range */
    if (SCSI_CheckAddressRange(pdev, lun, p_scsi_blk->addr, p_scsi_blk->len) < 0)
    {
      return -1; /* error */
    }

    len = p_scsi_blk->len * p_scsi_blk->size;

    /* cases 3,11,13 : Hn,Ho <> D0 */
    if (hmsc->cbw.dDataLength != len)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    len = MIN(len, MSC_MEDIA_PACKET);

    /* Prepare EP to receive first data packet */
    hmsc->bot_state = USBD_BOT_DATA_OUT;
    (void)USBD_LL_PrepareReceive(pdev, MSCOutEpAdd, hmsc->bot_data, len);
  }
  else /* Write Process ongoing */
  {
    return SCSI_ProcessWrite(pdev, lun);
  }

  return 0;
}


/**
  * @brief  SCSI_Write12
  *         Process Write12 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_Write12(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;
  uint32_t len;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

#ifdef USE_USBD_COMPOSITE
  /* Get the Endpoints addresses allocated for this class instance */
  MSCOutEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_OUT, USBD_EP_TYPE_BULK, (uint8_t)pdev->classId);
#endif /* USE_USBD_COMPOSITE */

  if (hmsc->bot_state == USBD_BOT_IDLE) /* Idle */
  {
    if (hmsc->cbw.dDataLength == 0U)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    /* case 8 : Hi <> Do */
    if ((hmsc->cbw.bmFlags & 0x80U) == 0x80U)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    if (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
      hmsc->bot_state = USBD_BOT_NO_DATA;
      return -1;
    }

    /* Check whether Media is ready */
    if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsReady(lun) != 0)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
      hmsc->bot_state = USBD_BOT_NO_DATA;
      return -1;
    }

    /* Check If media is write-protected */
    if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsWriteProtected(lun) != 0)
    {
      SCSI_SenseCode(pdev, lun, NOT_READY, WRITE_PROTECTED);
      hmsc->bot_state = USBD_BOT_NO_DATA;
      return -1;
    }

    p_scsi_blk->addr = ((uint32_t)params[2] << 24) |
                       ((uint32_t)params[3] << 16) |
                       ((uint32_t)params[4] << 8) |
                       (uint32_t)params[5];

    p_scsi_blk->len = ((uint32_t)params[6] << 24) |
                      ((uint32_t)params[7] << 16) |
                      ((uint32_t)params[8] << 8) |
                      (uint32_t)params[9];

    /* check if LBA address is in the right range */
    if (SCSI_CheckAddressRange(pdev, lun, p_scsi_blk->addr, p_scsi_blk->len) < 0)
    {
      return -1; /* error */
    }

    len = p_scsi_blk->len * p_scsi_blk->size;

    /* cases 3,11,13 : Hn,Ho <> D0 */
    if (hmsc->cbw.dDataLength != len)
    {
      SCSI_SenseCode(pdev, hmsc->cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
      return -1;
    }

    len = MIN(len, MSC_MEDIA_PACKET);

    /* Prepare EP to receive first data packet */
    hmsc->bot_state = USBD_BOT_DATA_OUT;
    (void)USBD_LL_PrepareReceive(pdev, MSCOutEpAdd, hmsc->bot_data, len);
  }
  else /* Write Process ongoing */
  {
    return SCSI_ProcessWrite(pdev, lun);
  }

  return 0;
}


/**
  * @brief  SCSI_Verify10
  *         Process Verify10 command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_Verify10(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  uint32_t blk_offset;
  uint32_t blk_nbr;

  if (hmsc == NULL)
  {
    return -1;
  }

  if (hmsc->cbw.dDataLength != 0U)
  {
    SCSI_SenseCode(pdev, lun, ILLEGAL_REQUEST, INVALID_CDB);
    hmsc->bot_state = USBD_BOT_NO_DATA;
    return -1;
  }

  if (hmsc->scsi_medium_state == SCSI_MEDIUM_EJECTED)
  {
    SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
    hmsc->bot_state = USBD_BOT_NO_DATA;
    return -1;
  }

  if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->IsReady(lun) != 0)
  {
    SCSI_SenseCode(pdev, lun, NOT_READY, MEDIUM_NOT_PRESENT);
    hmsc->bot_state = USBD_BOT_NO_DATA;
    return -1;
  }

  if ((params[1] & 0x02U) == 0x02U)
  {
    SCSI_SenseCode(pdev, lun, ILLEGAL_REQUEST, INVALID_FIELD_IN_COMMAND);
    hmsc->bot_state = USBD_BOT_NO_DATA;
    return -1; /* Error, Verify Mode Not supported*/
  }

  /* Decode LBA and verification length from current CDB */
  blk_offset = ((uint32_t)params[2] << 24) |
               ((uint32_t)params[3] << 16) |
               ((uint32_t)params[4] <<  8) |
               (uint32_t)params[5];

  blk_nbr = ((uint32_t)params[7] <<  8) | (uint32_t)params[8];

  if (SCSI_CheckAddressRange(pdev, lun, blk_offset, blk_nbr) < 0)
  {
    return -1; /* error */
  }

  hmsc->bot_data_length = 0U;

  return 0;
}

/**
  * @brief  SCSI_ReportLuns12
  *         Process ReportLuns command
  * @retval status
  */
static int8_t SCSI_ReportLuns(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc;
  uint32_t report_idx;
  uint32_t lun_list_length;
  uint32_t total_length;
  uint32_t alloc_len;
  uint8_t lun_idx;

  UNUSED(lun);

  /* Define the report LUNs buffer: 8-byte header + 8 bytes per LUN entry */
  static uint8_t lun_report[8U + (8U * (MSC_BOT_MAX_LUN + 1U))];

  hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hmsc == NULL)
  {
    return -1;
  }

  /* Initialize the report LUNs buffer */
  for (report_idx = 0U; report_idx < sizeof(lun_report); report_idx++)
  {
    lun_report[report_idx] = 0U;
  }

  /* Set the LUN list length in the first 4 bytes */
  lun_list_length = 8U * (hmsc->max_lun + 1U);
  lun_report[0] = (uint8_t)(lun_list_length >> 24);
  lun_report[1] = (uint8_t)(lun_list_length >> 16);
  lun_report[2] = (uint8_t)(lun_list_length >> 8);
  lun_report[3] = (uint8_t)(lun_list_length & 0xFFU);

  /* Update the LUN list */
  for (lun_idx = 0U; lun_idx <= hmsc->max_lun; lun_idx++)
  {
    /* LUN identifier is placed at the second byte of each 8-byte entry */
    lun_report[(8U * (lun_idx + 1U)) + 1U] = lun_idx;
  }

  /* Calculate the total length of the report LUNs buffer */
  total_length = lun_list_length + 8U;

  /* Clamp to allocation length from CDB bytes 6-9 */
  alloc_len = ((uint32_t)params[6] << 24) |
              ((uint32_t)params[7] << 16) |
              ((uint32_t)params[8] <<  8) |
              (uint32_t)params[9];

  if (alloc_len < total_length)
  {
    total_length = alloc_len;
  }

  /* Update the BOT data with the report LUNs buffer */
  (void)SCSI_UpdateBotData(hmsc, lun_report, (uint16_t)total_length);

  return 0;
}

/**
  * @brief  SCSI_ReceiveDiagnosticResults
  *         Process SCSI_Receive Diagnostic Results command
  * @param  lun: Logical unit number
  * @param  params: Command parameters
  * @retval status
  */
static int8_t SCSI_ReceiveDiagnosticResults(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *params)
{
  UNUSED(lun);
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  uint16_t allocation_length;

  if (hmsc == NULL)
  {
    return -1;
  }

  /* Extract the allocation length from the CDB */
  allocation_length = (((uint16_t)params[3] << 8) | (uint16_t)params[4]);

  if (allocation_length == 0U)
  {
    hmsc->bot_data_length = 0U;
    return 0;
  }

  /* Ensure the allocation length does not exceed the diagnostic data length */
  if (allocation_length > DIAGNOSTIC_DATA_LEN)
  {
    allocation_length = DIAGNOSTIC_DATA_LEN;
  }

  /* Send the diagnostic data to the host */
  (void)SCSI_UpdateBotData(hmsc, MSC_Diagnostic_Data, allocation_length);

  return 0;
}

/**
  * @brief  SCSI_CheckAddressRange
  *         Check address range
  * @param  lun: Logical unit number
  * @param  blk_offset: first block address
  * @param  blk_nbr: number of block to be processed
  * @retval status
  */
static int8_t SCSI_CheckAddressRange(USBD_HandleTypeDef *pdev, uint8_t lun,
                                     uint32_t blk_offset, uint32_t blk_nbr)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

  /* Refresh cached capacity for this LUN so multi-LUN configs
     with different sizes use the correct block count. */
  (void)((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->GetCapacity(lun, &p_scsi_blk->nbr,
                                                                             &p_scsi_blk->size);

  if ((blk_nbr > p_scsi_blk->nbr) || (blk_offset > (p_scsi_blk->nbr - blk_nbr)))
  {
    SCSI_SenseCode(pdev, lun, ILLEGAL_REQUEST, ADDRESS_OUT_OF_RANGE);
    return -1;
  }

  return 0;
}

/**
  * @brief  SCSI_ProcessRead
  *         Handle Read Process
  * @param  lun: Logical unit number
  * @retval status
  */
static int8_t SCSI_ProcessRead(USBD_HandleTypeDef *pdev, uint8_t lun)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;
  uint32_t len;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

  len = p_scsi_blk->len * p_scsi_blk->size;

#ifdef USE_USBD_COMPOSITE
  /* Get the Endpoints addresses allocated for this class instance */
  MSCInEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_IN, USBD_EP_TYPE_BULK, (uint8_t)pdev->classId);
#endif /* USE_USBD_COMPOSITE */

  len = MIN(len, MSC_MEDIA_PACKET);

  if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->Read(lun, hmsc->bot_data,
                                                                    p_scsi_blk->addr,
                                                                    (len / p_scsi_blk->size)) < 0)
  {
    SCSI_SenseCode(pdev, lun, HARDWARE_ERROR, UNRECOVERED_READ_ERROR);
    return -1;
  }

  (void)USBD_LL_Transmit(pdev, MSCInEpAdd, hmsc->bot_data, len);

  p_scsi_blk->addr += (len / p_scsi_blk->size);
  p_scsi_blk->len -= (len / p_scsi_blk->size);

  /* case 6 : Hi = Di */
  hmsc->csw.dDataResidue -= len;

  if (p_scsi_blk->len == 0U)
  {
    hmsc->bot_state = USBD_BOT_LAST_DATA_IN;
  }

  return 0;
}

/**
  * @brief  SCSI_ProcessWrite
  *         Handle Write Process
  * @param  lun: Logical unit number
  * @retval status
  */
static int8_t SCSI_ProcessWrite(USBD_HandleTypeDef *pdev, uint8_t lun)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = (USBD_MSC_BOT_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  USBD_MSC_BOT_LUN_TypeDef *p_scsi_blk;
  uint32_t len;

  if (hmsc == NULL)
  {
    return -1;
  }

  p_scsi_blk = &hmsc->scsi_blk[lun];

  len = p_scsi_blk->len * p_scsi_blk->size;

#ifdef USE_USBD_COMPOSITE
  /* Get the Endpoints addresses allocated for this class instance */
  MSCOutEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_OUT, USBD_EP_TYPE_BULK, (uint8_t)pdev->classId);
#endif /* USE_USBD_COMPOSITE */

  len = MIN(len, MSC_MEDIA_PACKET);

  if (((USBD_StorageTypeDef *)pdev->pUserData[pdev->classId])->Write(lun, hmsc->bot_data, p_scsi_blk->addr,
                                                                     (len / p_scsi_blk->size)) < 0)
  {
    SCSI_SenseCode(pdev, lun, HARDWARE_ERROR, WRITE_FAULT);
    return -1;
  }

  p_scsi_blk->addr += (len / p_scsi_blk->size);
  p_scsi_blk->len -= (len / p_scsi_blk->size);

  /* case 12 : Ho = Do */
  hmsc->csw.dDataResidue -= len;

  if (p_scsi_blk->len == 0U)
  {
    MSC_BOT_SendCSW(pdev, USBD_CSW_CMD_PASSED);
  }
  else
  {
    len = MIN((p_scsi_blk->len * p_scsi_blk->size), MSC_MEDIA_PACKET);

    /* Prepare EP to Receive next packet */
    (void)USBD_LL_PrepareReceive(pdev, MSCOutEpAdd, hmsc->bot_data, len);
  }

  return 0;
}


/**
  * @brief  SCSI_UpdateBotData
  *         fill the requested Data to transmit buffer
  * @param  hmsc handler
  * @param  pBuff: Data buffer
  * @param  length: Data length
  * @retval status
  */
static int8_t SCSI_UpdateBotData(USBD_MSC_BOT_HandleTypeDef *hmsc,
                                 uint8_t *pBuff, uint16_t length)
{
  uint16_t len = length;

  if (hmsc == NULL)
  {
    return -1;
  }

  hmsc->bot_data_length = len;

  while (len != 0U)
  {
    len--;
    hmsc->bot_data[len] = pBuff[len];
  }

  return 0;
}
/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

