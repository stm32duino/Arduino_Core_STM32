/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DFU_RUNTIME_H
#define __USB_DFU_RUNTIME_H

#include <bootloader.h>

/**************************************************/
/* DFU Requests  DFU states                       */
/**************************************************/
#define APP_STATE_IDLE                 0U
#define APP_STATE_DETACH               1U
#define DFU_STATE_IDLE                 2U
#define DFU_STATE_DNLOAD_SYNC          3U
#define DFU_STATE_DNLOAD_BUSY          4U
#define DFU_STATE_DNLOAD_IDLE          5U
#define DFU_STATE_MANIFEST_SYNC        6U
#define DFU_STATE_MANIFEST             7U
#define DFU_STATE_MANIFEST_WAIT_RESET  8U
#define DFU_STATE_UPLOAD_IDLE          9U
#define DFU_STATE_ERROR                10U

/**************************************************/
/* DFU errors                                     */
/**************************************************/
#define DFU_ERROR_NONE                 0x00U
#define DFU_ERROR_TARGET               0x01U
#define DFU_ERROR_FILE                 0x02U
#define DFU_ERROR_WRITE                0x03U
#define DFU_ERROR_ERASE                0x04U
#define DFU_ERROR_CHECK_ERASED         0x05U
#define DFU_ERROR_PROG                 0x06U
#define DFU_ERROR_VERIFY               0x07U
#define DFU_ERROR_ADDRESS              0x08U
#define DFU_ERROR_NOTDONE              0x09U
#define DFU_ERROR_FIRMWARE             0x0AU
#define DFU_ERROR_VENDOR               0x0BU
#define DFU_ERROR_USB                  0x0CU
#define DFU_ERROR_POR                  0x0DU
#define DFU_ERROR_UNKNOWN              0x0EU
#define DFU_ERROR_STALLEDPKT           0x0FU

typedef enum {
  DFU_DETACH = 0U,
  DFU_DNLOAD,
  DFU_UPLOAD,
  DFU_GETSTATUS,
  DFU_CLRSTATUS,
  DFU_GETSTATE,
  DFU_ABORT
} DFU_RequestTypeDef;

#define DFU_DESCRIPTOR_TYPE            0x21U

// Device will detach by itself (alternative is that the host sends a
// USB reset within DETACH_TIMEOUT).
#define DFU_RT_ATTR_WILL_DETACH 0x08U
// Device is still accessible on USB after flashing (manifestation).
// Probably not so relevant in runtime mode
#define DFU_RT_ATTR_MANIFESTATION_TOLERANT 0x04U
#define DFU_RT_ATTR_CAN_UPLOAD 0x02U
#define DFU_RT_ATTR_CAN_DNLOAD 0x01U

// Of these, only WILL_DETACH is relevant at runtime, but specify
// CAN_UPLOAD and CAN_DNLOAD too, just in case there is a tool that
// somehow checks these before resetting.
#define DFU_RT_ATTRS DFU_RT_ATTR_WILL_DETACH \
        | DFU_RT_ATTR_CAN_UPLOAD | DFU_RT_ATTR_CAN_DNLOAD

// Detach timeout is only relevant when ATTR_WILL_DETACH is unset
#define DFU_RT_DETACH_TIMEOUT 0
// This should be only relevant for actual firmware uploads (the actual
// value is read from the bootloader after reset), but specify a
// conservative value here in case any tool fails to reread the value
// after reset.
// The max packet size for EP0 control transfers is specified in the
// device descriptor.
#define DFU_RT_TRANSFER_SIZE 64
#define DFU_RT_DFU_VERSION 0x0101 // DFU 1.1

#define DFU_RT_IFACE_NUM 2 // XXX: Hardcoded

#define DFU_RT_IFACE_DESC_SIZE 18U
#define DFU_RT_IFACE_DESC \
  /*DFU Runtime interface descriptor*/ \
  0x09,                                 /* bLength: Endpoint Descriptor size */                        \
  USB_DESC_TYPE_INTERFACE,              /* bDescriptorType: */                                         \
  DFU_RT_IFACE_NUM,                     /* bInterfaceNumber: Number of Interface */ \
  0x00,                                 /* bAlternateSetting: Alternate setting */                     \
  0x00,                                 /* bNumEndpoints: no endpoints used (only control endpoint) */ \
  0xFE,                                 /* bInterfaceClass: Application Specific */                    \
  0x01,                                 /* bInterfaceSubClass: Device Firmware Upgrade Code*/          \
  0x01,                                 /* bInterfaceProtocol: Runtime Protocol*/                      \
  /* TODO: Put a meaningful string here, which shows up in the Windows * */ \
  /* device manager when no driver is installed yet. */ \
  0x00,                                 /* iInterface: */                                              \
  \
  /*DFU Runtime Functional Descriptor*/ \
  0x09,                                 /* bFunctionLength */                                          \
  DFU_DESCRIPTOR_TYPE,                  /* bDescriptorType: DFU Functional */                          \
  DFU_RT_ATTRS,                         /* bmAttributes: DFU Attributes */                             \
  LOBYTE(DFU_RT_DETACH_TIMEOUT),        /* wDetachTimeout */                                           \
  HIBYTE(DFU_RT_DETACH_TIMEOUT),        \
  LOBYTE(DFU_RT_TRANSFER_SIZE),         /* wTransferSize */                                            \
  HIBYTE(DFU_RT_TRANSFER_SIZE),         \
  LOBYTE(DFU_RT_DFU_VERSION),           /* bcdDFUVersion */                                            \
  HIBYTE(DFU_RT_DFU_VERSION)

/**
  * @brief  USBD_DFU_Runtime_Control
  *         Manage the DFU interface control requests
  * @param  bRequest: Command code from request
  * @param  wValue: Value from request
  * @param  data: Buffer for result
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t USBD_DFU_Runtime_Control(uint8_t bRequest, uint16_t wValue, uint8_t *data, uint16_t len)
{
  UNUSED(wValue);
  switch (bRequest) {
    case DFU_GETSTATUS:
      if (len != 6) {
        return (USBD_FAIL);
      }

      data[0] = DFU_ERROR_NONE;
      // Minimum delay until next GET_STATUS
      data[1] = data[2] = data[3] = 0;
      data[4] = APP_STATE_IDLE;
      // State string descriptor
      data[5] = 0;

      return (USBD_OK);

    case DFU_DETACH:
      scheduleBootloaderReset();
      return (USBD_OK);

    case DFU_GETSTATE:
      if (len != 1) {
        return (USBD_FAIL);
      }
      data[0] = APP_STATE_IDLE;
      return (USBD_OK);

    default:
      return (USBD_FAIL);
  }
}

#endif // __USB_DFU_RUNTIME_H
