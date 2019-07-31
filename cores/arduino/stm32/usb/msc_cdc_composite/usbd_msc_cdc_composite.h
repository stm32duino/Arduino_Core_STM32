
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_MSC_CDC_COMPOSITE_H
#define __USB_MSC_CDC_COMPOSITE_H



#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "usbd_ioreq.h"
#include "usbd_core.h"
#include "usbd_msc_scsi.h"
#include "usbd_msc_cdc_composite_bot.h"
#include "cdc_queue.h"
#include <stdint.h>

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_MSC_CDC_Exported_Defines
  * @{
  */
#define MSC_INTERFACE_IDX 0x2                             // Index of MSC interface
#define CDC_INTERFACE_IDX 0x0                             // Index of CDC interface

// endpoints numbers
#define MSC_EP_IDX                      0x01  // only EP 0, EP 1 & EP 2 are bidirectional
#define CDC_CMD_EP_IDX                  0x03  // unable to determine why EP 3 will not transmit
#define CDC_EP_IDX                      0x02  // EP 3 can receive data from the host because there
  // is just one receive FIFO and then the packets are
  // distributed by the top layer

#define IN_EP_DIR           0x80 // Adds a direction bit

#define MSC_OUT_EP                      MSC_EP_IDX                  /* EP1 for BULK OUT */
#define MSC_IN_EP                       (MSC_EP_IDX | IN_EP_DIR)    /* EP1 for BULK IN */

#ifdef CDC_CMD_EP
#undef CDC_CMD_EP
#endif
#define CDC_CMD_EP                      (CDC_CMD_EP_IDX| IN_EP_DIR) /* EP2 for CDC commands */

#ifdef CDC_OUT_EP
#undef CDC_OUT_EP
#endif
#define CDC_OUT_EP                      CDC_EP_IDX                  /* EP3 for data OUT */

#ifdef CDC_IN_EP
#undef CDC_IN_EP
#endif
#define CDC_IN_EP                       (CDC_EP_IDX | IN_EP_DIR)    /* EP3 for data IN */

#ifdef USB_MAX_PACKET_SIZE
#undef USB_MAX_PACKET_SIZE
#endif
#define USB_MAX_PACKET_SIZE             USB_MAX_EP0_SIZE

#ifdef CDC_CMD_PACKET_SIZE
#undef CDC_CMD_PACKET_SIZE
#endif
#define CDC_CMD_PACKET_SIZE             8  /* Control Endpoint Packet size */

#ifdef CDC_DATA_PACKET_SIZE
#undef CDC_DATA_PACKET_SIZE
#endif
#define CDC_DATA_PACKET_SIZE            USB_MAX_PACKET_SIZE

#define USB_MSC_PACKET_SIZE             64



/** @addtogroup USBD_MSC_BOT
  * @{
  */

/** @defgroup USBD_MSC
  * @brief This file is the Header file for usbd_msc.c
  * @{
  */


/** @defgroup USBD_BOT_Exported_Defines
  * @{
  */
/* MSC Class Config */
#ifndef MSC_MEDIA_PACKET
#define MSC_MEDIA_PACKET             8192
#endif /* MSC_MEDIA_PACKET */

#define MSC_MAX_FS_PACKET            0x40U
#define MSC_MAX_HS_PACKET            0x200U

#define BOT_GET_MAX_LUN              0xFE
#define BOT_RESET                    0xFF
#define USB_MSC_CONFIG_DESC_SIZ      32


//#define MSC_EPIN_ADDR                0x83U
//#define MSC_EPOUT_ADDR               0x03U

/**
  * @}
  */

/** @defgroup USB_CORE_Exported_Types
  * @{
  */

// forward declarations
//struct _USBD_MSC_BOT_CBWTypeDef;
//struct _USBD_MSC_BOT_CSWTypeDef;
struct _SENSE_ITEM;  // USBD_SCSI_SenseTypeDef

typedef struct _USBD_STORAGE {
  int8_t (* Init)(uint8_t lun);
  int8_t (* GetCapacity)(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
  int8_t (* IsReady)(uint8_t lun);
  int8_t (* IsWriteProtected)(uint8_t lun);
  int8_t (* Read)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* Write)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* GetMaxLun)(void);
  int8_t *pInquiry;

} USBD_StorageTypeDef;


typedef struct _USBD_MSC_BOT_HandleTypeDef {
  uint32_t                 max_lun;
  uint32_t                 interface;
  uint8_t                  bot_state;
  uint8_t                  bot_status;
  uint16_t                 bot_data_length;
  uint8_t                  bot_data[MSC_MEDIA_PACKET];
  USBD_MSC_BOT_CBWTypeDef  cbw;
  USBD_MSC_BOT_CSWTypeDef  csw;

  struct _SENSE_ITEM   scsi_sense [SENSE_LIST_DEEPTH];  //  USBD_SCSI_SenseTypeDef
  uint8_t                  scsi_sense_head;
  uint8_t                  scsi_sense_tail;

  uint16_t                 scsi_blk_size;
  uint32_t                 scsi_blk_nbr;

  uint32_t                 scsi_blk_addr;
  uint32_t                 scsi_blk_len;
} USBD_MSC_BOT_HandleTypeDef;

/* Structure for MSC process */
extern USBD_ClassTypeDef  USBD_MSC;
#define USBD_MSC_CLASS    &USBD_MSC

uint8_t  USBD_MSC_RegisterStorage  (USBD_HandleTypeDef   *pdev,
                                    USBD_StorageTypeDef *fops);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_MSC_CDC_COMPOSITE_H */
/**
  * @}
  */

/**
  * @}
  */
