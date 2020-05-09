/**
  ******************************************************************************
  * @file    usbd_conf.c
  * @author  MCD Application Team
  * @brief   USB Device configuration and interface file
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
#ifdef USBCON
/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"
#include "usbd_if.h"
#include "usbd_ep_conf.h"
#include "stm32yyxx_ll_pwr.h"

#ifndef HAL_PCD_MODULE_ENABLED
#error "HAL_PCD_MODULE_ENABLED is required"
#else
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if !defined(USBD_VBUS_DETECTION_ENABLE)
  #define VBUS_SENSING DISABLE
#else
  #define VBUS_SENSING ENABLE
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PCD_HandleTypeDef g_hpcd;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
                       PCD BSP Routines
*******************************************************************************/

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd)
{
  const PinMap *map = NULL;
#if defined(PWR_CR2_USV)
  /* Enable VDDUSB on Pwrctrl CR2 register*/
#if !defined(STM32WBxx)
  if (__HAL_RCC_PWR_IS_CLK_DISABLED()) {
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWREx_EnableVddUSB();
    __HAL_RCC_PWR_CLK_DISABLE();
  } else
#endif
  {
    HAL_PWREx_EnableVddUSB();
  }
#endif
#ifdef STM32H7xx
  if (!LL_PWR_IsActiveFlag_USB()) {
    HAL_PWREx_EnableUSBVoltageDetector();
  }
#endif
#if defined (USB)
  if (hpcd->Instance == USB) {

    /* Configure USB FS GPIOs */
    map = PinMap_USB;
    while (map->pin != NC) {
      pin_function(map->pin, map->function);
      map++;
    }

    /* Enable USB FS Clock */
    __HAL_RCC_USB_CLK_ENABLE();

#if defined (USE_USB_INTERRUPT_REMAPPED)
    /*USB interrupt remapping enable */
    __HAL_REMAPINTERRUPT_USB_ENABLE();
#endif

#if defined(STM32G4xx) || defined(STM32WBxx)
    HAL_NVIC_SetPriority(USB_HP_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);
    HAL_NVIC_EnableIRQ(USB_HP_IRQn);
    HAL_NVIC_SetPriority(USB_LP_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);
    HAL_NVIC_EnableIRQ(USB_LP_IRQn);
#else
    /* Set USB FS Interrupt priority */
    HAL_NVIC_SetPriority(USB_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);

    /* Enable USB FS Interrupt */
    HAL_NVIC_EnableIRQ(USB_IRQn);
#endif /* STM32WBxx */

    if (hpcd->Init.low_power_enable == 1) {
      /* Enable EXTI for USB wakeup */
#ifdef __HAL_USB_WAKEUP_EXTI_CLEAR_FLAG
      __HAL_USB_WAKEUP_EXTI_CLEAR_FLAG();
#endif
#ifdef __HAL_USB_WAKEUP_EXTI_ENABLE_RISING_EDGE
      __HAL_USB_WAKEUP_EXTI_ENABLE_RISING_EDGE();
#endif
      __HAL_USB_WAKEUP_EXTI_ENABLE_IT();
#if defined(STM32F1xx) || defined(STM32F3xx)
      /* USB Wakeup Interrupt */
      HAL_NVIC_EnableIRQ(USBWakeUp_IRQn);

      /* Enable USB Wake-up interrupt */
      HAL_NVIC_SetPriority(USBWakeUp_IRQn, 0, 0);
#endif
    }
  }
#endif /* USB */
#if defined (USB_OTG_FS)
  if (hpcd->Instance == USB_OTG_FS) {

    /* Configure USB FS GPIOs */
    map = PinMap_USB_OTG_FS;
    while (map->pin != NC) {
      pin_function(map->pin, map->function);
      map++;
    }

    /* Enable USB FS Clock */
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    /* Set USB FS Interrupt priority */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);

    /* Enable USB FS Interrupt */
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);

    if (hpcd->Init.low_power_enable == 1) {
      /* Enable EXTI Line 18 for USB wakeup */
#ifdef __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG
      __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG();
#endif
#ifdef __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_RISING_EDGE
      __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_RISING_EDGE();
#endif
      __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_IT();
#if !defined(STM32L4xx)
      /* Set EXTI Wakeup Interrupt priority */
      HAL_NVIC_SetPriority(OTG_FS_WKUP_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);

      /* Enable EXTI Interrupt */
      HAL_NVIC_EnableIRQ(OTG_FS_WKUP_IRQn);
#endif
    }
  }
#endif /* USB_OTG_FS */
#if defined (USB_OTG_HS)
  if (hpcd->Instance == USB_OTG_HS)  {
    /* Configure USB HS GPIOs */
    map = PinMap_USB_OTG_HS;
    while (map->pin != NC) {
      pin_function(map->pin, map->function);
      map++;
    }
#ifndef USE_USB_HS_IN_FS
    __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE();
#endif /* USE_USB_HS_IN_FS */

    /* Enable USB HS Clocks */
    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();

    /* Set USBHS Interrupt priority */
    HAL_NVIC_SetPriority(OTG_HS_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);

    /* Enable USB HS Interrupt */
    HAL_NVIC_EnableIRQ(OTG_HS_IRQn);

    if (hpcd->Init.low_power_enable == 1) {
      /* Enable EXTI Line 20 for USB wakeup */
#ifdef __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG
      __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG();
#endif
#ifdef __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_EDGE
      __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_EDGE();
#endif
      __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_IT();

      /* Set EXTI Wakeup Interrupt priority */
      HAL_NVIC_SetPriority(OTG_HS_WKUP_IRQn, USBD_IRQ_PRIO, USBD_IRQ_SUBPRIO);

      /* Enable EXTI Interrupt */
      HAL_NVIC_EnableIRQ(OTG_HS_WKUP_IRQn);
    }
  }
#endif /* USB_OTG_HS */
}

/**
  * @brief  De-Initializes the PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd)
{
  /* Disable USB FS Clock */
#if defined (USB)
  if (hpcd->Instance == USB) {
    __HAL_RCC_USB_CLK_DISABLE();
  }
#endif
#if defined (USB_OTG_FS)
  if (hpcd->Instance == USB_OTG_FS) {
    /* Disable USB FS Clock */
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();
  }
#endif
#if defined (USB_OTG_HS)
  if (hpcd->Instance == USB_OTG_HS) {
    /* Disable USB HS Clocks */
    __HAL_RCC_USB_OTG_HS_CLK_DISABLE();
  }
#endif /* USB_OTG_HS */
}

/*******************************************************************************
                       LL Driver Callbacks (PCD -> USB Device Library)
*******************************************************************************/

/**
  * @brief  SetupStage callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_SetupStage(hpcd->pData, (uint8_t *)hpcd->Setup);
}

/**
  * @brief  DataOut Stage callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_DataOutStage(hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

/**
  * @brief  DataIn Stage callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_DataInStage(hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

/**
  * @brief  SOF callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_SOF(hpcd->pData);
}

/**
  * @brief  Reset callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_SpeedTypeDef speed = USBD_SPEED_FULL;

#if defined (USB_OTG_HS)
  /* Set USB Current Speed */
  switch (hpcd->Init.speed) {
    case PCD_SPEED_HIGH:
      speed = USBD_SPEED_HIGH;
      break;

    case PCD_SPEED_FULL:
      speed = USBD_SPEED_FULL;
      break;

    default:
      speed = USBD_SPEED_FULL;
      break;
  }
#endif
  /* Reset Device */
  USBD_LL_Reset(hpcd->pData);

  USBD_LL_SetSpeed(hpcd->pData, speed);
}

/**
  * @brief  Suspend callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_Suspend(hpcd->pData);
  __HAL_PCD_GATE_PHYCLOCK(hpcd);

  /*Enter in STOP mode */
  if (hpcd->Init.low_power_enable) {
    /* Set SLEEPDEEP bit and SleepOnExit of Cortex System Control Register */
    SCB->SCR |= (uint32_t)((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
  }
}

/**
  * @brief  Resume callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
  if (hpcd->Init.low_power_enable) {
    SystemClock_Config();

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
  }
  __HAL_PCD_UNGATE_PHYCLOCK(hpcd);
  USBD_LL_Resume(hpcd->pData);
}

/**
  * @brief  ISOOUTIncomplete callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_IsoOUTIncomplete(hpcd->pData, epnum);
}

/**
  * @brief  ISOINIncomplete callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_IsoINIncomplete(hpcd->pData, epnum);
}

/**
  * @brief  ConnectCallback callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_DevConnected(hpcd->pData);
}

/**
  * @brief  Disconnect callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_DevDisconnected(hpcd->pData);
}



/**
  * @brief  This function handles USB-On-The-Go FS/HS global interrupt request.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_HS
  void OTG_HS_IRQHandler(void)
#elif defined(USB_OTG_FS)
  void OTG_FS_IRQHandler(void)
#else /* USB */
  void USB_IRQHandler(void)
#endif
{
  HAL_PCD_IRQHandler(&g_hpcd);
}

#if defined(STM32WBxx)
/**
  * @brief This function handles USB high priority interrupt.
  * @param  None
  * @retval None
  */
void USB_HP_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&g_hpcd);
}

/**
  * @brief This function handles USB low priority interrupt, USB wake-up interrupt through EXTI line 28.
  * @param  None
  * @retval None
  */
void USB_LP_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&g_hpcd);
}
#else
/**
  * @brief  This function handles USB OTG FS Wakeup IRQ Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_HS
  void OTG_HS_WKUP_IRQHandler(void)
#elif defined(USB_OTG_FS)
  void OTG_FS_WKUP_IRQHandler(void)
#else
  void USBWakeUp_IRQHandler(void)
#endif
{
  if ((&g_hpcd)->Init.low_power_enable) {
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));

    /* Configures system clock after wake-up from STOP: enable HSE, PLL and select
    PLL as system clock source (HSE and PLL are disabled in STOP mode) */
    SystemClock_Config();

    /* ungate PHY clock */
    __HAL_PCD_UNGATE_PHYCLOCK((&g_hpcd));
  }
#if defined(USE_USB_HS) && defined(__HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG)
  /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG();
#elif defined(USB_OTG_FS) && defined(__HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG)
  /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG();
#elif defined(__HAL_USB_WAKEUP_EXTI_CLEAR_FLAG)
  __HAL_USB_WAKEUP_EXTI_CLEAR_FLAG();
#endif
}
#endif
/*******************************************************************************
                       LL Driver Interface (USB Device Library --> PCD)
*******************************************************************************/
/**
  * @brief  Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev)
{
  USBD_reenumerate();
  /* Set common LL Driver parameters */
  g_hpcd.Init.dev_endpoints = DEV_NUM_EP;
  g_hpcd.Init.ep0_mps = DEP0CTL_MPS_64;
#if !defined(STM32F1xx) && !defined(STM32F2xx) || defined(USB)
  g_hpcd.Init.lpm_enable = DISABLE;
  g_hpcd.Init.battery_charging_enable = DISABLE;
#endif
  g_hpcd.Init.low_power_enable = DISABLE;
  g_hpcd.Init.Sof_enable = DISABLE;

  /* Set specific LL Driver parameters */
#ifdef USE_USB_HS
  g_hpcd.Instance = USB_OTG_HS;
  g_hpcd.Init.use_dedicated_ep1 = DISABLE;
  g_hpcd.Init.dma_enable = DISABLE;
#ifdef USE_USB_HS_IN_FS
  g_hpcd.Init.phy_itface = PCD_PHY_EMBEDDED;
#else
  g_hpcd.Init.phy_itface = PCD_PHY_ULPI;
#endif
  g_hpcd.Init.speed = PCD_SPEED_HIGH;
  g_hpcd.Init.vbus_sensing_enable = VBUS_SENSING;
  g_hpcd.Init.use_external_vbus = DISABLE;
#else /* USE_USB_FS */
#ifdef USB_OTG_FS
  g_hpcd.Instance = USB_OTG_FS;
  g_hpcd.Init.use_dedicated_ep1 = DISABLE;
  g_hpcd.Init.dma_enable = DISABLE;
  g_hpcd.Init.vbus_sensing_enable = VBUS_SENSING;
  g_hpcd.Init.use_external_vbus = DISABLE;
#else
  g_hpcd.Instance = USB;
#endif
  g_hpcd.Init.phy_itface = PCD_PHY_EMBEDDED;
  g_hpcd.Init.speed = PCD_SPEED_FULL;
#endif /* USE_USB_HS */

  /* Link The driver to the stack */
  g_hpcd.pData = pdev;
  pdev->pData = &g_hpcd;

  /* Initialize LL Driver */
  if (HAL_PCD_Init(&g_hpcd) != HAL_OK) {
    Error_Handler();
  }


#if !defined (USB)
  /* configure EPs FIFOs */
  HAL_PCDEx_SetRxFiFo(&g_hpcd, ep_def[0].ep_size);
  for (uint32_t i = 1; i < (DEV_NUM_EP + 1); i++) {
    HAL_PCDEx_SetTxFiFo(&g_hpcd, ep_def[i].ep_adress & 0xF, ep_def[i].ep_size);
  }
#else
  for (uint32_t i = 0; i < (DEV_NUM_EP + 1); i++) {
    HAL_PCDEx_PMAConfig(&g_hpcd, ep_def[i].ep_adress, ep_def[i].ep_kind, ep_def[i].ep_size);
  }
#endif /* USE_USB_HS */
  return USBD_OK;
}

/**
  * @brief  De-Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev)
{
  HAL_PCD_DeInit(pdev->pData);
  return USBD_OK;
}

/**
  * @brief  Starts the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev)
{
  HAL_PCD_Start(pdev->pData);
  return USBD_OK;
}

/**
  * @brief  Stops the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev)
{
  HAL_PCD_Stop(pdev->pData);
  return USBD_OK;
}

/**
  * @brief  Opens an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  ep_type: Endpoint Type
  * @param  ep_mps: Endpoint Max Packet Size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev,
                                  uint8_t ep_addr,
                                  uint8_t ep_type,
                                  uint16_t ep_mps)
{
  HAL_PCD_EP_Open(pdev->pData,
                  ep_addr,
                  ep_mps,
                  ep_type);
  return USBD_OK;
}

/**
  * @brief  Closes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_Close(pdev->pData, ep_addr);
  return USBD_OK;
}

/**
  * @brief  Flushes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_Flush(pdev->pData, ep_addr);
  return USBD_OK;
}

/**
  * @brief  Sets a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_SetStall(pdev->pData, ep_addr);
  return USBD_OK;
}

/**
  * @brief  Clears a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_ClrStall(pdev->pData, ep_addr);
  return USBD_OK;
}

/**
  * @brief  Returns Stall condition.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Stall (1: Yes, 0: No)
  */
uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  PCD_HandleTypeDef *hpcd = pdev->pData;

  if ((ep_addr & 0x80) == 0x80) {
    return hpcd->IN_ep[ep_addr & 0x7F].is_stall;
  } else {
    return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
  }
}

/**
  * @brief  Assigns a USB address to the device.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr)
{
  HAL_PCD_SetAddress(pdev->pData, dev_addr);
  return USBD_OK;
}

/**
  * @brief  Transmits data over an endpoint.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be sent
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev,
                                    uint8_t ep_addr,
                                    uint8_t *pbuf,
                                    uint16_t size)
{
  HAL_PCD_EP_Transmit(pdev->pData, ep_addr, pbuf, size);
  return USBD_OK;
}

/**
  * @brief  Prepares an endpoint for reception.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be received
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev,
                                          uint8_t ep_addr,
                                          uint8_t *pbuf,
                                          uint16_t size)
{
  HAL_PCD_EP_Receive(pdev->pData, ep_addr, pbuf, size);
  return USBD_OK;
}

/**
  * @brief  Returns the last transferred packet size.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Received Data Size
  */
uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  return HAL_PCD_EP_GetRxCount(pdev->pData, ep_addr);
}

/**
  * @brief  Delays routine for the USB Device Library.
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBD_LL_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}
#endif /* HAL_PCD_MODULE_ENABLED */
#endif /* USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

