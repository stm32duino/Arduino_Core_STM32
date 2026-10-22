/**
  ******************************************************************************
 * @file    usbd_confv2.c
 * @brief   HAL v2 USB device low-level adapter.
  ******************************************************************************
  */

#if defined(USBCON) && defined(USE_HALV2_DRIVER)

#include "usbd_core.h"
#include "usbd_if.h"
#include "usbd_ep_conf.h"

#ifndef USE_HAL_PCD_MODULE
  #error "USE_HAL_PCD_MODULE is required"
#endif

static hal_pcd_handle_t g_hpcd;
static USBD_HandleTypeDef *g_pdev;
static uint8_t g_stalled_in;
static uint8_t g_stalled_out;

/**
 * @brief Configure the USB clock, interrupt priority, and NVIC interrupt for
 *        the HAL v2 USB device.
 */
static void USBD_V2_ConfigPinsAndIrq(void)
{
  /* The HAL v2 USB DRD FS PCD owns PA11/PA12 and configures these fixed USB
   * pins during peripheral initialization. */

  HAL_RCC_USB_EnableClock();
  HAL_CORTEX_NVIC_SetPriority(USB_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);
  HAL_CORTEX_NVIC_EnableIRQ(USB_IRQn);
}

#if !defined(USBD_REENUM_DISABLED)
/* HAL v2 adapters own USB pull-up control.  Keep the common re-enumeration
 * entry point, but implement it through the PCD API rather than the legacy
 * USB_DevConnect/USB_DevDisconnect helpers. */
void USBD_reenumerate(void)
{
  if ((g_hpcd.global_state == HAL_PCD_STATE_IDLE) ||
      (g_hpcd.global_state == HAL_PCD_STATE_ACTIVE)) {
    const uint32_t was_active = (g_hpcd.global_state == HAL_PCD_STATE_ACTIVE);

    (void)HAL_PCD_DeviceDisconnect(&g_hpcd);
    HAL_Delay(USBD_ENUM_DELAY);

    /* HAL_PCD_Start() connects the device when startup is still in the IDLE
     * state.  Only reconnect here when the device was already running. */
    if (was_active != 0U) {
      (void)HAL_PCD_DeviceConnect(&g_hpcd);
    }
  }
}
#endif

/**
 * @brief HAL PCD callback for a SETUP stage packet. Forwards it to the USB
 *        device core.
 * @param hpcd PCD handle that raised the callback.
 */
void HAL_PCD_SetupStageCallback(hal_pcd_handle_t *hpcd)
{
  USBD_LL_SetupStage(g_pdev, (uint8_t *)hpcd->setup);
}

/**
 * @brief HAL PCD callback for the end of an OUT data stage. Forwards it to
 *        the USB device core.
 * @param hpcd PCD handle that raised the callback.
 * @param epnum Endpoint number.
 */
void HAL_PCD_DataOutStageCallback(hal_pcd_handle_t *hpcd, uint8_t epnum)
{
  USBD_LL_DataOutStage(g_pdev, epnum, hpcd->out_ep[epnum].p_xfer_buffer);
}

/**
 * @brief HAL PCD callback for the end of an IN data stage. Forwards it to
 *        the USB device core.
 * @param hpcd PCD handle that raised the callback.
 * @param epnum Endpoint number.
 */
void HAL_PCD_DataInStageCallback(hal_pcd_handle_t *hpcd, uint8_t epnum)
{
  USBD_LL_DataInStage(g_pdev, epnum, hpcd->in_ep[epnum].p_xfer_buffer);
}

/**
 * @brief HAL PCD callback for a start-of-frame event. Forwards it to the USB
 *        device core.
 * @param hpcd PCD handle that raised the callback.
 */
void HAL_PCD_SofCallback(hal_pcd_handle_t *hpcd)
{
  (void)hpcd;
  USBD_LL_SOF(g_pdev);
}

/**
 * @brief HAL PCD callback for a bus reset. Resets the USB device core and
 *        sets the speed to full speed.
 * @param hpcd PCD handle that raised the callback.
 */
void HAL_PCD_ResetCallback(hal_pcd_handle_t *hpcd)
{
  (void)hpcd;
  USBD_LL_Reset(g_pdev);
  USBD_LL_SetSpeed(g_pdev, USBD_SPEED_FULL);
}

/**
 * @brief HAL PCD callback for a suspend event. Forwards it to the USB device
 *        core.
 * @param hpcd PCD handle that raised the callback.
 */
void HAL_PCD_SuspendCallback(hal_pcd_handle_t *hpcd)
{
  (void)hpcd;
  USBD_LL_Suspend(g_pdev);
}

/**
 * @brief HAL PCD callback for a resume event. Forwards it to the USB device
 *        core.
 * @param hpcd PCD handle that raised the callback.
 */
void HAL_PCD_ResumeCallback(hal_pcd_handle_t *hpcd)
{
  (void)hpcd;
  USBD_LL_Resume(g_pdev);
}

/**
 * @brief HAL PCD callback for an incomplete isochronous OUT transfer.
 * @param hpcd PCD handle that raised the callback.
 * @param epnum Endpoint number.
 */
void HAL_PCD_ISOOUTIncompleteCallback(hal_pcd_handle_t *hpcd, uint8_t epnum)
{
  (void)hpcd;
  USBD_LL_IsoOUTIncomplete(g_pdev, epnum);
}

/**
 * @brief HAL PCD callback for an incomplete isochronous IN transfer.
 * @param hpcd PCD handle that raised the callback.
 * @param epnum Endpoint number.
 */
void HAL_PCD_ISOINIncompleteCallback(hal_pcd_handle_t *hpcd, uint8_t epnum)
{
  (void)hpcd;
  USBD_LL_IsoINIncomplete(g_pdev, epnum);
}

/**
 * @brief HAL PCD callback for the device connect event. Forwards it to the
 *        USB device core.
 * @param hpcd PCD handle that raised the callback.
 */
void HAL_PCD_ConnectCallback(hal_pcd_handle_t *hpcd)
{
  (void)hpcd;
  USBD_LL_DevConnected(g_pdev);
}

/**
 * @brief HAL PCD callback for the device disconnect event. Forwards it to the
 *        USB device core.
 * @param hpcd PCD handle that raised the callback.
 */
void HAL_PCD_DisconnectCallback(hal_pcd_handle_t *hpcd)
{
  (void)hpcd;
  USBD_LL_DevDisconnected(g_pdev);
}

/**
 * @brief USB interrupt service routine. Passes the interrupt to the HAL PCD
 *        driver.
 */
void USB_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&g_hpcd);
}

/**
 * @brief Initialize the low-level USB driver: configure the PCD and endpoint
 *        PMA, then toggle the USB pull-up through USBD_reenumerate().
 * @note  Calls Error_Handler() if the HAL PCD setup fails.
 * @param pdev USB device handle.
 * @return USBD_OK.
 */
USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev)
{
  hal_pcd_config_t config = {
    .dma_enable = HAL_PCD_DMA_DISABLED,
    .pcd_speed = HAL_PCD_SPEED_FS,
    .phy_interface = HAL_PCD_PHY_EMBEDDED_FS,
    .sof_enable = HAL_PCD_SOF_DISABLED,
    .lpm_enable = HAL_PCD_LPM_DISABLED,
    .battery_charging_enable = HAL_PCD_BCD_DISABLED,
    .vbus_sensing_enable = HAL_PCD_VBUS_SENSE_DISABLED,
    .bulk_doublebuffer_enable = HAL_PCD_BULK_DB_DISABLED,
  };

  USBD_V2_ConfigPinsAndIrq();

  g_pdev = pdev;
  g_stalled_in = 0U;
  g_stalled_out = 0U;
  pdev->pData = &g_hpcd;

  if (HAL_PCD_Init(&g_hpcd, HAL_PCD_DRD_FS) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_PCD_SetConfig(&g_hpcd, &config) != HAL_OK) {
    Error_Handler();
  }

  for (uint32_t i = 0U; i < (DEV_NUM_EP + 1U); i++) {
    if (HAL_PCD_PMAConfig(&g_hpcd, ep_def[i].ep_adress, ep_def[i].ep_kind,
                          ep_def[i].ep_size) != HAL_OK) {
      Error_Handler();
    }
  }

  /* HAL v2 exposes the USB pull-up through the PCD device-connect API. */
  USBD_reenumerate();

  return USBD_OK;
}

/**
 * @brief De-initialize the low-level USB driver and disable its clock and
 *        interrupt.
 * @param pdev USB device handle.
 * @return USBD_OK.
 */
USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev)
{
  (void)pdev;
  HAL_CORTEX_NVIC_DisableIRQ(USB_IRQn);
  HAL_PCD_DeInit(&g_hpcd);
  HAL_RCC_USB_DisableClock();
  g_pdev = NULL;
  return USBD_OK;
}

/**
 * @brief Start the USB device.
 * @param pdev USB device handle.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev)
{
  (void)pdev;
  return (HAL_PCD_Start(&g_hpcd) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Stop the USB device.
 * @param pdev USB device handle.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev)
{
  (void)pdev;
  return (HAL_PCD_Stop(&g_hpcd) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Open an endpoint.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @param ep_type Endpoint type, as a hal_pcd_ep_type_t value.
 * @param ep_mps Maximum packet size, in bytes.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr,
                                  uint8_t ep_type, uint16_t ep_mps)
{
  (void)pdev;
  return (HAL_PCD_OpenEndpoint(&g_hpcd, ep_addr, ep_mps,
                               (hal_pcd_ep_type_t)ep_type) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Close an endpoint.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  (void)pdev;
  return (HAL_PCD_CloseEndpoint(&g_hpcd, ep_addr) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Flush the buffers of an endpoint.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  (void)pdev;
  return (HAL_PCD_FlushEndpoint(&g_hpcd, ep_addr) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Stall an endpoint. The stall state is also recorded in this module.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  uint8_t mask = (uint8_t)(1U << (ep_addr & 0x0FU));
  (void)pdev;
  if ((ep_addr & 0x80U) != 0U) {
    g_stalled_in |= mask;
  } else {
    g_stalled_out |= mask;
  }
  return (HAL_PCD_SetEndpointStall(&g_hpcd, ep_addr) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Clear the stall of an endpoint. The stall state is also cleared in
 *        this module.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  uint8_t mask = (uint8_t)(1U << (ep_addr & 0x0FU));
  (void)pdev;
  if ((ep_addr & 0x80U) != 0U) {
    g_stalled_in &= (uint8_t)~mask;
  } else {
    g_stalled_out &= (uint8_t)~mask;
  }
  return (HAL_PCD_ClearEndpointStall(&g_hpcd, ep_addr) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Check whether an endpoint is stalled.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @return Non-zero if the endpoint is stalled, 0 otherwise.
 */
uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  uint8_t mask = (uint8_t)(1U << (ep_addr & 0x0FU));
  (void)pdev;
  return ((ep_addr & 0x80U) != 0U) ? ((g_stalled_in & mask) != 0U) :
         ((g_stalled_out & mask) != 0U);
}

/**
 * @brief Set the USB device address.
 * @param pdev USB device handle.
 * @param dev_addr New device address.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr)
{
  (void)pdev;
  return (HAL_PCD_SetDeviceAddress(&g_hpcd, dev_addr) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Send data on an IN endpoint.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @param pbuf Data to send.
 * @param size Number of bytes to send.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev, uint8_t ep_addr,
                                    uint8_t *pbuf, uint32_t size)
{
  (void)pdev;
  return (HAL_PCD_SetEndpointTransmit(&g_hpcd, ep_addr, pbuf, size) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Prepare an OUT endpoint to receive data.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @param pbuf Buffer that receives the data.
 * @param size Maximum number of bytes to receive.
 * @return USBD_OK on success, USBD_FAIL otherwise.
 */
USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev, uint8_t ep_addr,
                                          uint8_t *pbuf, uint32_t size)
{
  (void)pdev;
  return (HAL_PCD_SetEndpointReceive(&g_hpcd, ep_addr, pbuf, size) == HAL_OK) ? USBD_OK : USBD_FAIL;
}

/**
 * @brief Get the number of bytes received on an endpoint.
 * @param pdev USB device handle.
 * @param ep_addr Endpoint address, including the direction bit.
 * @return Number of received bytes.
 */
uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  (void)pdev;
  return HAL_PCD_EP_GetRxCount(&g_hpcd, ep_addr);
}

/**
 * @brief Delay for the USB stack.
 * @param delay Delay, in milliseconds.
 */
void USBD_LL_Delay(uint32_t delay)
{
  HAL_Delay(delay);
}

#endif /* USBCON && USE_HALV2_DRIVER */
