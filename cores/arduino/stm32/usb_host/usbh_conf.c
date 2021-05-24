/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Target/usbh_conf.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the board support package for the USB host library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#ifdef USBHOST
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "Arduino.h"

#ifndef HAL_HCD_MODULE_ENABLED
  #error "HAL_HCD_MODULE_ENABLED is required"
#endif

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

HCD_HandleTypeDef g_hhcd;

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
USBH_StatusTypeDef USBH_Get_USB_Status(HAL_StatusTypeDef hal_status);

/* USER CODE END PFP */

/* Private functions ---------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/*******************************************************************************
                       LL Driver Callbacks (HCD -> USB Host Library)
*******************************************************************************/
/* MSP Init */

void HAL_HCD_MspInit(HCD_HandleTypeDef *hhcd)
{
  const PinMap *map = NULL;
#if defined (USB_OTG_FS)
  if (hhcd->Instance == USB_OTG_FS) {
    /* Configure USB FS GPIOs */
    map = PinMap_USB_OTG_FS;
    while (map->pin != NC) {
      pin_function(map->pin, map->function);
      map++;
    }

    /* Peripheral clock enable */
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    /* Set USB FS Interrupt priority */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, USBH_IRQ_PRIO, USBH_IRQ_SUBPRIO);

    /* Enable USB FS Interrupt */
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);

    if (hhcd->Init.low_power_enable == 1) {
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
      HAL_NVIC_SetPriority(OTG_FS_WKUP_IRQn, USBH_IRQ_PRIO, USBH_IRQ_SUBPRIO);

      /* Enable EXTI Interrupt */
      HAL_NVIC_EnableIRQ(OTG_FS_WKUP_IRQn);
#endif
    }
  }
#endif
#if defined(USB_OTG_HS)
  if (hhcd->Instance == USB_OTG_HS) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    map = PinMap_USB_OTG_HS;
    while (map->pin != NC) {
      pin_function(map->pin, map->function);
      map++;
    }

    /* Peripheral clock enable */
    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();

    /* Set USB HS Interrupt priority */
    HAL_NVIC_SetPriority(OTG_HS_IRQn, USBH_IRQ_PRIO, USBH_IRQ_SUBPRIO);

    /* Enable USB HS Interrupt */
    HAL_NVIC_EnableIRQ(OTG_HS_IRQn);

    if (hhcd->Init.low_power_enable == 1) {
      /* Enable EXTI Line 18 for USB wakeup */
#ifdef __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG
      __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG();
#endif
#ifdef __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_EDGE
      __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_EDGE();
#endif
      __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_IT();
#if !defined(STM32L4xx)
      /* Set EXTI Wakeup Interrupt priority */
      HAL_NVIC_SetPriority(OTG_HS_WKUP_IRQn, USBH_IRQ_PRIO, USBH_IRQ_SUBPRIO);

      /* Enable EXTI Interrupt */
      HAL_NVIC_EnableIRQ(OTG_HS_WKUP_IRQn);
#endif
    }
  }
#endif
}

void HAL_HCD_MspDeInit(HCD_HandleTypeDef *hhcd)
{
#if defined (USB_OTG_FS)
  if (hhcd->Instance == USB_OTG_FS) {
    /* Disable USB FS Clock */
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();
    HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
  }
#endif
#if defined (USB_OTG_HS)
  if (hhcd->Instance == USB_OTG_HS) {
    /* Disable USB HS Clocks */
    __HAL_RCC_USB_OTG_HS_CLK_DISABLE();
    HAL_NVIC_DisableIRQ(OTG_HS_IRQn);
  }
#endif /* USB_OTG_HS */
}

/**
  * @brief  SOF callback.
  * @param  hhcd: HCD handle
  * @retval None
  */
void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_IncTimer(hhcd->pData);
}

/**
  * @brief  SOF callback.
  * @param  hhcd: HCD handle
  * @retval None
  */
void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_Connect(hhcd->pData);
}

/**
  * @brief  SOF callback.
  * @param  hhcd: HCD handle
  * @retval None
  */
void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_Disconnect(hhcd->pData);
}

/**
  * @brief  Notify URB state change callback.
  * @param  hhcd: HCD handle
  * @param  chnum: channel number
  * @param  urb_state: state
  * @retval None
  */
void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum, HCD_URBStateTypeDef urb_state)
{
  /* To be used with OS to sync URB state with the global state machine */
#if (USBH_USE_OS == 1)
  USBH_LL_NotifyURBChange(hhcd->pData);
#endif
}
/**
* @brief  Port Port Enabled callback.
  * @param  hhcd: HCD handle
  * @retval None
  */
void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_PortEnabled(hhcd->pData);
}

/**
  * @brief  Port Port Disabled callback.
  * @param  hhcd: HCD handle
  * @retval None
  */
void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_PortDisabled(hhcd->pData);
}

/*******************************************************************************
                       LL Driver Interface (USB Host Library --> HCD)
*******************************************************************************/

/**
  * @brief  Initialize the low level portion of the host driver.
  * @param  phost: Host handle
  * @retval USBH status
  */
USBH_StatusTypeDef USBH_LL_Init(USBH_HandleTypeDef *phost)
{
  /* Init USB_IP */
  if (phost->id == HOST_FS) {
    /* Link the driver to the stack. */
    g_hhcd.pData = phost;
    phost->pData = &g_hhcd;

    g_hhcd.Instance = USB_OTG_FS;
    g_hhcd.Init.Host_channels = 8;
    g_hhcd.Init.speed = HCD_SPEED_FULL;
    g_hhcd.Init.dma_enable = DISABLE;
    g_hhcd.Init.phy_itface = HCD_PHY_EMBEDDED;
    g_hhcd.Init.Sof_enable = DISABLE;
    if (HAL_HCD_Init(&g_hhcd) != HAL_OK) {
      // Error_Handler( );
      return USBH_FAIL;
    }

    USBH_LL_SetTimer(phost, HAL_HCD_GetCurrentFrame(&g_hhcd));
  } else if (phost->id == HOST_HS) {
    /* Link the driver to the stack. */
    g_hhcd.pData = phost;
    phost->pData = &g_hhcd;

    g_hhcd.Instance = USB_OTG_HS;
    g_hhcd.Init.Host_channels = 12;
    g_hhcd.Init.speed = HCD_SPEED_FULL;
    g_hhcd.Init.dma_enable = DISABLE;
#ifdef USE_USB_HS_IN_FS
    g_hhcd.Init.phy_itface = USB_OTG_EMBEDDED_PHY;
#else
    g_hhcd.Init.phy_itface = USB_OTG_ULPI_PHY;
#endif
    g_hhcd.Init.Sof_enable = DISABLE;
    g_hhcd.Init.low_power_enable = DISABLE;
    g_hhcd.Init.vbus_sensing_enable = DISABLE;
    g_hhcd.Init.use_external_vbus = DISABLE;

    if (HAL_HCD_Init(&g_hhcd) != HAL_OK) {
      Error_Handler();
    }

    USBH_LL_SetTimer(phost, HAL_HCD_GetCurrentFrame(&g_hhcd));
  }
  return USBH_OK;
}

/**
  * @brief  De-Initialize the low level portion of the host driver.
  * @param  phost: Host handle
  * @retval USBH status
  */
USBH_StatusTypeDef USBH_LL_DeInit(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;
  hal_status = HAL_HCD_DeInit(phost->pData);
  usb_status = USBH_Get_USB_Status(hal_status);
  return usb_status;
}

/**
  * @brief  Start the low level portion of the host driver.
  * @param  phost: Host handle
  * @retval USBH status
  */
USBH_StatusTypeDef USBH_LL_Start(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;
  hal_status = HAL_HCD_Start(phost->pData);
  usb_status = USBH_Get_USB_Status(hal_status);
  return usb_status;
}

/**
  * @brief  Stop the low level portion of the host driver.
  * @param  phost: Host handle
  * @retval USBH status
  */
USBH_StatusTypeDef USBH_LL_Stop(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;
  hal_status = HAL_HCD_Stop(phost->pData);
  usb_status = USBH_Get_USB_Status(hal_status);
  return usb_status;
}

/**
  * @brief  Return the USB host speed from the low level driver.
  * @param  phost: Host handle
  * @retval USBH speeds
  */
USBH_SpeedTypeDef USBH_LL_GetSpeed(USBH_HandleTypeDef *phost)
{
  USBH_SpeedTypeDef speed = USBH_SPEED_FULL;

  switch (HAL_HCD_GetCurrentSpeed(phost->pData)) {
    case 0 :
      speed = USBH_SPEED_HIGH;
      break;

    case 1 :
      speed = USBH_SPEED_FULL;
      break;

    case 2 :
      speed = USBH_SPEED_LOW;
      break;

    default:
      speed = USBH_SPEED_FULL;
      break;
  }
  return  speed;
}

/**
  * @brief  Reset the Host port of the low level driver.
  * @param  phost: Host handle
  * @retval USBH status
  */
USBH_StatusTypeDef USBH_LL_ResetPort(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;
  hal_status = HAL_HCD_ResetPort(phost->pData);
  usb_status = USBH_Get_USB_Status(hal_status);
  return usb_status;
}

/**
  * @brief  Return the last transfered packet size.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  * @retval Packet size
  */
uint32_t USBH_LL_GetLastXferSize(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  return HAL_HCD_HC_GetXferCount(phost->pData, pipe);
}

/**
  * @brief  Open a pipe of the low level driver.
  * @param  phost: Host handle
  * @param  pipe_num: Pipe index
  * @param  epnum: Endpoint number
  * @param  dev_address: Device USB address
  * @param  speed: Device Speed
  * @param  ep_type: Endpoint type
  * @param  mps: Endpoint max packet size
  * @retval USBH status
  */
USBH_StatusTypeDef USBH_LL_OpenPipe(USBH_HandleTypeDef *phost, uint8_t pipe_num, uint8_t epnum,
                                    uint8_t dev_address, uint8_t speed, uint8_t ep_type, uint16_t mps)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;

  hal_status = HAL_HCD_HC_Init(phost->pData, pipe_num, epnum,
                               dev_address, speed, ep_type, mps);

  usb_status = USBH_Get_USB_Status(hal_status);

  return usb_status;
}

/**
  * @brief  Close a pipe of the low level driver.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  * @retval USBH status
  */
USBH_StatusTypeDef USBH_LL_ClosePipe(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;

  hal_status = HAL_HCD_HC_Halt(phost->pData, pipe);

  usb_status = USBH_Get_USB_Status(hal_status);

  return usb_status;
}

/**
  * @brief  Submit a new URB to the low level driver.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  *         This parameter can be a value from 1 to 15
  * @param  direction : Channel number
  *          This parameter can be one of the these values:
  *           0 : Output
  *           1 : Input
  * @param  ep_type : Endpoint Type
  *          This parameter can be one of the these values:
  *            @arg EP_TYPE_CTRL: Control type
  *            @arg EP_TYPE_ISOC: Isochrounous type
  *            @arg EP_TYPE_BULK: Bulk type
  *            @arg EP_TYPE_INTR: Interrupt type
  * @param  token : Endpoint Type
  *          This parameter can be one of the these values:
  *            @arg 0: PID_SETUP
  *            @arg 1: PID_DATA
  * @param  pbuff : pointer to URB data
  * @param  length : Length of URB data
  * @param  do_ping : activate do ping protocol (for high speed only)
  *          This parameter can be one of the these values:
  *           0 : do ping inactive
  *           1 : do ping active
  * @retval Status
  */
USBH_StatusTypeDef USBH_LL_SubmitURB(USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t direction,
                                     uint8_t ep_type, uint8_t token, uint8_t *pbuff, uint16_t length,
                                     uint8_t do_ping)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;

  hal_status = HAL_HCD_HC_SubmitRequest(phost->pData, pipe, direction,
                                        ep_type, token, pbuff, length,
                                        do_ping);
  usb_status =  USBH_Get_USB_Status(hal_status);

  return usb_status;
}

/**
  * @brief  Get a URB state from the low level driver.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  *         This parameter can be a value from 1 to 15
  * @retval URB state
  *          This parameter can be one of the these values:
  *            @arg URB_IDLE
  *            @arg URB_DONE
  *            @arg URB_NOTREADY
  *            @arg URB_NYET
  *            @arg URB_ERROR
  *            @arg URB_STALL
  */
USBH_URBStateTypeDef USBH_LL_GetURBState(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  return (USBH_URBStateTypeDef)HAL_HCD_HC_GetURBState(phost->pData, pipe);
}

/**
  * @brief  Drive VBUS.
  * @param  phost: Host handle
  * @param  state : VBUS state
  *          This parameter can be one of the these values:
  *           0 : VBUS Inactive
  *           1 : VBUS Active
  * @retval Status
  */
USBH_StatusTypeDef USBH_LL_DriverVBUS(USBH_HandleTypeDef *phost, uint8_t state)
{

  /* USER CODE BEGIN 0 */

  /* USER CODE END 0*/

  if (phost->id == HOST_FS) {
    if (state == 0) {
      /* Drive high Charge pump */
      /* ToDo: Add IOE driver control */
      /* USER CODE BEGIN DRIVE_HIGH_CHARGE_FOR_FS */

      /* USER CODE END DRIVE_HIGH_CHARGE_FOR_FS */
    } else {
      /* Drive low Charge pump */
      /* ToDo: Add IOE driver control */
      /* USER CODE BEGIN DRIVE_LOW_CHARGE_FOR_FS */

      /* USER CODE END DRIVE_LOW_CHARGE_FOR_FS */
    }
  }
  HAL_Delay(200);
  return USBH_OK;
}

/**
  * @brief  Set toggle for a pipe.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  * @param  toggle: toggle (0/1)
  * @retval Status
  */
USBH_StatusTypeDef USBH_LL_SetToggle(USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t toggle)
{
  HCD_HandleTypeDef *pHandle;
  pHandle = phost->pData;

  if (pHandle->hc[pipe].ep_is_in) {
    pHandle->hc[pipe].toggle_in = toggle;
  } else {
    pHandle->hc[pipe].toggle_out = toggle;
  }

  return USBH_OK;
}

/**
  * @brief  Return the current toggle of a pipe.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  * @retval toggle (0/1)
  */
uint8_t USBH_LL_GetToggle(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  uint8_t toggle = 0;
  HCD_HandleTypeDef *pHandle;
  pHandle = phost->pData;

  if (pHandle->hc[pipe].ep_is_in) {
    toggle = pHandle->hc[pipe].toggle_in;
  } else {
    toggle = pHandle->hc[pipe].toggle_out;
  }
  return toggle;
}

/**
  * @brief  Delay routine for the USB Host Library
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBH_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
  * @brief  Retuns the USB status depending on the HAL status:
  * @param  hal_status: HAL status
  * @retval USB status
  */
USBH_StatusTypeDef USBH_Get_USB_Status(HAL_StatusTypeDef hal_status)
{
  USBH_StatusTypeDef usb_status = USBH_OK;

  switch (hal_status) {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


/**
  * @brief  This function handles USB-On-The-Go FS/HS global interrupt request.
  * @param  None
  * @retval None
  */
#ifdef USE_USBHOST_HS
  void OTG_HS_IRQHandler(void)
#elif defined(USB_OTG_FS)
  void OTG_FS_IRQHandler(void)
#else /* USB */
  void USB_IRQHandler(void)
#endif
{
  HAL_HCD_IRQHandler(&g_hhcd);
}

/**
  * @brief  This function handles USB OTG HCD Wakeup IRQ Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USBHOST_HS
  void OTG_HS_WKUP_IRQHandler(void)
#elif defined(USB_OTG_FS)
  void OTG_FS_WKUP_IRQHandler(void)
#else
  void USBWakeUp_IRQHandler(void)
#endif
{
  if ((&g_hhcd)->Init.low_power_enable) {
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));

    /* Configures system clock after wake-up from STOP: enable HSE, PLL and select
    PLL as system clock source (HSE and PLL are disabled in STOP mode) */
    SystemClock_Config();
  }
#if defined(USE_USBHOST_HS) && defined(__HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG)
  /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG();
#elif defined(USB_OTG_FS) && defined(__HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG)
  /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG();
#elif defined(__HAL_USB_WAKEUP_EXTI_CLEAR_FLAG)
  __HAL_USB_WAKEUP_EXTI_CLEAR_FLAG();
#endif
}

#endif /* USBHOST */
