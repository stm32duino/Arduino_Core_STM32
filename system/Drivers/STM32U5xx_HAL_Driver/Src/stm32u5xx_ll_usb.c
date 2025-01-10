/**
  ******************************************************************************
  * @file    stm32u5xx_ll_usb.c
  * @author  MCD Application Team
  * @brief   USB Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Fill parameters of Init structure in USB_CfgTypeDef structure.

      (#) Call USB_CoreInit() API to initialize the USB Core peripheral.

      (#) The upper HAL HCD/PCD driver will call the right routines for its internal processes.

  @endverbatim

  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_LL_USB_DRIVER
  * @{
  */

#if defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED)
#if defined (USB_OTG_FS) || defined (USB_OTG_HS) || defined (USB_DRD_FS)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
static HAL_StatusTypeDef USB_CoreReset(USB_OTG_GlobalTypeDef *USBx);

/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Functions USB Low Layer Exported Functions
  * @{
  */

/** @defgroup USB_LL_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
                      ##### Initialization/de-initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the USB Core
  * @param  USBx USB Instance
  * @param  cfg pointer to a USB_OTG_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_CoreInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret;
#if defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) \
 || defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx)
  if (cfg.phy_itface == USB_OTG_HS_EMBEDDED_PHY)
  {
    /* Init The UTMI Interface */
    USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_TSDPS);
  }

  /* Reset after a PHY select */
  ret = USB_CoreReset(USBx);

  if (cfg.dma_enable == 1U)
  {
    USBx->GAHBCFG |= USB_OTG_GAHBCFG_HBSTLEN_2;
    USBx->GAHBCFG |= USB_OTG_GAHBCFG_DMAEN;
  }

#else

  /* Select FS Embedded PHY */
  USBx->GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;

  /* Reset after a PHY select */
  ret = USB_CoreReset(USBx);

  if (cfg.battery_charging_enable == 0U)
  {
    /* Activate the USB Transceiver */
    USBx->GCCFG |= USB_OTG_GCCFG_PWRDWN;
  }
  else
  {
    /* Deactivate the USB Transceiver */
    USBx->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);
  }
#endif /* defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) ||
          defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx) */

  return ret;
}


/**
  * @brief  Set the USB turnaround time
  * @param  USBx USB Instance
  * @param  hclk: AHB clock frequency
  * @retval USB turnaround time In PHY Clocks number
  */
HAL_StatusTypeDef USB_SetTurnaroundTime(USB_OTG_GlobalTypeDef *USBx,
                                        uint32_t hclk, uint8_t speed)
{
  uint32_t UsbTrd;

  /* The USBTRD is configured according to the tables below, depending on AHB frequency
  used by application. In the low AHB frequency range it is used to stretch enough the USB response
  time to IN tokens, the USB turnaround time, so to compensate for the longer AHB read access
  latency to the Data FIFO */
  if (speed == USBD_FS_SPEED)
  {
    if ((hclk >= 14200000U) && (hclk < 15000000U))
    {
      /* hclk Clock Range between 14.2-15 MHz */
      UsbTrd = 0xFU;
    }
    else if ((hclk >= 15000000U) && (hclk < 16000000U))
    {
      /* hclk Clock Range between 15-16 MHz */
      UsbTrd = 0xEU;
    }
    else if ((hclk >= 16000000U) && (hclk < 17200000U))
    {
      /* hclk Clock Range between 16-17.2 MHz */
      UsbTrd = 0xDU;
    }
    else if ((hclk >= 17200000U) && (hclk < 18500000U))
    {
      /* hclk Clock Range between 17.2-18.5 MHz */
      UsbTrd = 0xCU;
    }
    else if ((hclk >= 18500000U) && (hclk < 20000000U))
    {
      /* hclk Clock Range between 18.5-20 MHz */
      UsbTrd = 0xBU;
    }
    else if ((hclk >= 20000000U) && (hclk < 21800000U))
    {
      /* hclk Clock Range between 20-21.8 MHz */
      UsbTrd = 0xAU;
    }
    else if ((hclk >= 21800000U) && (hclk < 24000000U))
    {
      /* hclk Clock Range between 21.8-24 MHz */
      UsbTrd = 0x9U;
    }
    else if ((hclk >= 24000000U) && (hclk < 27700000U))
    {
      /* hclk Clock Range between 24-27.7 MHz */
      UsbTrd = 0x8U;
    }
    else if ((hclk >= 27700000U) && (hclk < 32000000U))
    {
      /* hclk Clock Range between 27.7-32 MHz */
      UsbTrd = 0x7U;
    }
    else /* if(hclk >= 32000000) */
    {
      /* hclk Clock Range between 32-200 MHz */
      UsbTrd = 0x6U;
    }
  }
  else if (speed == USBD_HS_SPEED)
  {
    UsbTrd = USBD_HS_TRDT_VALUE;
  }
  else
  {
    UsbTrd = USBD_DEFAULT_TRDT_VALUE;
  }

  USBx->GUSBCFG &= ~USB_OTG_GUSBCFG_TRDT;
  USBx->GUSBCFG |= (uint32_t)((UsbTrd << 10) & USB_OTG_GUSBCFG_TRDT);

  return HAL_OK;
}

/**
  * @brief  USB_EnableGlobalInt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EnableGlobalInt(USB_OTG_GlobalTypeDef *USBx)
{
  USBx->GAHBCFG |= USB_OTG_GAHBCFG_GINT;
  return HAL_OK;
}

/**
  * @brief  USB_DisableGlobalInt
  *         Disable the controller's Global Int in the AHB Config reg
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DisableGlobalInt(USB_OTG_GlobalTypeDef *USBx)
{
  USBx->GAHBCFG &= ~USB_OTG_GAHBCFG_GINT;
  return HAL_OK;
}

/**
  * @brief  USB_SetCurrentMode Set functional mode
  * @param  USBx  Selected device
  * @param  mode  current core mode
  *          This parameter can be one of these values:
  *            @arg USB_DEVICE_MODE Peripheral mode
  *            @arg USB_HOST_MODE Host mode
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetCurrentMode(USB_OTG_GlobalTypeDef *USBx, USB_OTG_ModeTypeDef mode)
{
  uint32_t ms = 0U;

  USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_FHMOD | USB_OTG_GUSBCFG_FDMOD);

  if (mode == USB_HOST_MODE)
  {
    USBx->GUSBCFG |= USB_OTG_GUSBCFG_FHMOD;

    do
    {
      HAL_Delay(10U);
      ms += 10U;
    } while ((USB_GetMode(USBx) != (uint32_t)USB_HOST_MODE) && (ms < HAL_USB_CURRENT_MODE_MAX_DELAY_MS));
  }
  else if (mode == USB_DEVICE_MODE)
  {
    USBx->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD;

    do
    {
      HAL_Delay(10U);
      ms += 10U;
    } while ((USB_GetMode(USBx) != (uint32_t)USB_DEVICE_MODE) && (ms < HAL_USB_CURRENT_MODE_MAX_DELAY_MS));
  }
  else
  {
    return HAL_ERROR;
  }

  if (ms == HAL_USB_CURRENT_MODE_MAX_DELAY_MS)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  USB_DevInit Initializes the USB_OTG controller registers
  *         for device mode
  * @param  USBx  Selected device
  * @param  cfg   pointer to a USB_OTG_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i;

  for (i = 0U; i < 15U; i++)
  {
    USBx->DIEPTXF[i] = 0U;
  }

#if defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) \
 || defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx)
  /* Disable USB PHY pulldown resistors */
  USBx->GCCFG &= ~USB_OTG_GCCFG_PULLDOWNEN;
#endif /* defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) ||
          defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx) */

  /* VBUS Sensing setup */
  if (cfg.vbus_sensing_enable == 0U)
  {
    USBx_DEVICE->DCTL |= USB_OTG_DCTL_SDIS;

    /* Deactivate VBUS Sensing B */
    USBx->GCCFG &= ~USB_OTG_GCCFG_VBDEN;

    /* B-peripheral session valid override enable */
#if defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) \
 || defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx)
    USBx->GCCFG |= USB_OTG_GCCFG_VBVALEXTOEN;
    USBx->GCCFG |= USB_OTG_GCCFG_VBVALOVAL;
#else
    USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
    USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
#endif /* defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) ||
          defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx) */
  }
  else
  {
#if defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) \
 || defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx)
    /* B-peripheral session valid override disable */
    USBx->GCCFG &= ~USB_OTG_GCCFG_VBVALEXTOEN;
    USBx->GCCFG &= ~USB_OTG_GCCFG_VBVALOVAL;
#endif /* defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) ||
          defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx) */

    /* Enable HW VBUS sensing */
    USBx->GCCFG |= USB_OTG_GCCFG_VBDEN;
  }

  /* Restart the Phy Clock */
  USBx_PCGCCTL = 0U;

#if defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) \
 || defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx)
  if (cfg.phy_itface == USB_OTG_HS_EMBEDDED_PHY)
  {
    if (cfg.speed == USBD_HS_SPEED)
    {
      /* Set Core speed to High speed mode */
      (void)USB_SetDevSpeed(USBx, USB_OTG_SPEED_HIGH);
    }
    else
    {
      /* Set Core speed to Full speed mode */
      (void)USB_SetDevSpeed(USBx, USB_OTG_SPEED_HIGH_IN_FULL);
    }
  }
  else
#endif /* defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) ||
          defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx) */
  {
    /* Set Core speed to Full speed mode */
    (void)USB_SetDevSpeed(USBx, USB_OTG_SPEED_FULL);
  }

  /* Flush the FIFOs */
  if (USB_FlushTxFifo(USBx, 0x10U) != HAL_OK) /* all Tx FIFOs */
  {
    ret = HAL_ERROR;
  }

  if (USB_FlushRxFifo(USBx) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  /* Clear all pending Device Interrupts */
  USBx_DEVICE->DIEPMSK = 0U;
  USBx_DEVICE->DOEPMSK = 0U;
  USBx_DEVICE->DAINTMSK = 0U;

  for (i = 0U; i < cfg.dev_endpoints; i++)
  {
    if ((USBx_INEP(i)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      if (i == 0U)
      {
        USBx_INEP(i)->DIEPCTL = USB_OTG_DIEPCTL_SNAK;
      }
      else
      {
        USBx_INEP(i)->DIEPCTL = USB_OTG_DIEPCTL_EPDIS | USB_OTG_DIEPCTL_SNAK;
      }
    }
    else
    {
      USBx_INEP(i)->DIEPCTL = 0U;
    }

    USBx_INEP(i)->DIEPTSIZ = 0U;
    USBx_INEP(i)->DIEPINT  = 0xFB7FU;
  }

  for (i = 0U; i < cfg.dev_endpoints; i++)
  {
    if ((USBx_OUTEP(i)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      if (i == 0U)
      {
        USBx_OUTEP(i)->DOEPCTL = USB_OTG_DOEPCTL_SNAK;
      }
      else
      {
        USBx_OUTEP(i)->DOEPCTL = USB_OTG_DOEPCTL_EPDIS | USB_OTG_DOEPCTL_SNAK;
      }
    }
    else
    {
      USBx_OUTEP(i)->DOEPCTL = 0U;
    }

    USBx_OUTEP(i)->DOEPTSIZ = 0U;
    USBx_OUTEP(i)->DOEPINT  = 0xFB7FU;
  }

  USBx_DEVICE->DIEPMSK &= ~(USB_OTG_DIEPMSK_TXFURM);

  /* Disable all interrupts. */
  USBx->GINTMSK = 0U;

  /* Clear any pending interrupts */
  USBx->GINTSTS = 0xBFFFFFFFU;

  /* Enable the common interrupts */
  if (cfg.dma_enable == 0U)
  {
    USBx->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;
  }

  /* Enable interrupts matching to the Device mode ONLY */
  USBx->GINTMSK |= USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_USBRST |
                   USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_IEPINT |
                   USB_OTG_GINTMSK_OEPINT   | USB_OTG_GINTMSK_IISOIXFRM |
                   USB_OTG_GINTMSK_PXFRM_IISOOXFRM | USB_OTG_GINTMSK_WUIM;

  if (cfg.Sof_enable != 0U)
  {
    USBx->GINTMSK |= USB_OTG_GINTMSK_SOFM;
  }

  if (cfg.vbus_sensing_enable == 1U)
  {
    USBx->GINTMSK |= (USB_OTG_GINTMSK_SRQIM | USB_OTG_GINTMSK_OTGINT);
  }

  return ret;
}

/**
  * @brief  USB_FlushTxFifo Flush a Tx FIFO
  * @param  USBx  Selected device
  * @param  num  FIFO number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval HAL status
  */
HAL_StatusTypeDef USB_FlushTxFifo(USB_OTG_GlobalTypeDef *USBx, uint32_t num)
{
  __IO uint32_t count = 0U;

  /* Wait for AHB master IDLE state. */
  do
  {
    count++;

    if (count > HAL_USB_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

  /* Flush TX Fifo */
  count = 0U;
  USBx->GRSTCTL = (USB_OTG_GRSTCTL_TXFFLSH | (num << 6));

  do
  {
    count++;

    if (count > HAL_USB_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);

  return HAL_OK;
}

/**
  * @brief  USB_FlushRxFifo  Flush Rx FIFO
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_FlushRxFifo(USB_OTG_GlobalTypeDef *USBx)
{
  __IO uint32_t count = 0U;

  /* Wait for AHB master IDLE state. */
  do
  {
    count++;

    if (count > HAL_USB_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

  /* Flush RX Fifo */
  count = 0U;
  USBx->GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;

  do
  {
    count++;

    if (count > HAL_USB_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);

  return HAL_OK;
}

/**
  * @brief  USB_SetDevSpeed  Initializes the DevSpd field of DCFG register
  *         depending the PHY type and the enumeration speed of the device.
  * @param  USBx  Selected device
  * @param  speed  device speed
  *          This parameter can be one of these values:
  *            @arg USB_OTG_SPEED_HIGH: High speed mode
  *            @arg USB_OTG_SPEED_HIGH_IN_FULL: High speed core in Full Speed mode
  *            @arg USB_OTG_SPEED_FULL: Full speed mode
  * @retval  Hal status
  */
HAL_StatusTypeDef USB_SetDevSpeed(const USB_OTG_GlobalTypeDef *USBx, uint8_t speed)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  USBx_DEVICE->DCFG |= speed;
  return HAL_OK;
}

/**
  * @brief  USB_GetDevSpeed  Return the Dev Speed
  * @param  USBx  Selected device
  * @retval speed  device speed
  *          This parameter can be one of these values:
  *            @arg USBD_HS_SPEED: High speed mode
  *            @arg USBD_FS_SPEED: Full speed mode
  */
uint8_t USB_GetDevSpeed(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint8_t speed;
  uint32_t DevEnumSpeed = USBx_DEVICE->DSTS & USB_OTG_DSTS_ENUMSPD;

  if (DevEnumSpeed == DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ)
  {
    speed = USBD_HS_SPEED;
  }
  else if ((DevEnumSpeed == DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ) ||
           (DevEnumSpeed == DSTS_ENUMSPD_FS_PHY_48MHZ))
  {
    speed = USBD_FS_SPEED;
  }
  else
  {
    speed = 0xFU;
  }

  return speed;
}

/**
  * @brief  Activate and configure an endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    USBx_DEVICE->DAINTMSK |= USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK));

    if ((USBx_INEP(epnum)->DIEPCTL & USB_OTG_DIEPCTL_USBAEP) == 0U)
    {
      USBx_INEP(epnum)->DIEPCTL |= (ep->maxpacket & USB_OTG_DIEPCTL_MPSIZ) |
                                   ((uint32_t)ep->type << 18) | (epnum << 22) |
                                   USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                   USB_OTG_DIEPCTL_USBAEP;
    }
  }
  else
  {
    USBx_DEVICE->DAINTMSK |= USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16);

    if (((USBx_OUTEP(epnum)->DOEPCTL) & USB_OTG_DOEPCTL_USBAEP) == 0U)
    {
      USBx_OUTEP(epnum)->DOEPCTL |= (ep->maxpacket & USB_OTG_DOEPCTL_MPSIZ) |
                                    ((uint32_t)ep->type << 18) |
                                    USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                    USB_OTG_DOEPCTL_USBAEP;
    }
  }
  return HAL_OK;
}

/**
  * @brief  Activate and configure a dedicated endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  /* Read DEPCTLn register */
  if (ep->is_in == 1U)
  {
    if (((USBx_INEP(epnum)->DIEPCTL) & USB_OTG_DIEPCTL_USBAEP) == 0U)
    {
      USBx_INEP(epnum)->DIEPCTL |= (ep->maxpacket & USB_OTG_DIEPCTL_MPSIZ) |
                                   ((uint32_t)ep->type << 18) | (epnum << 22) |
                                   USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                   USB_OTG_DIEPCTL_USBAEP;
    }

    USBx_DEVICE->DEACHMSK |= USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK));
  }
  else
  {
    if (((USBx_OUTEP(epnum)->DOEPCTL) & USB_OTG_DOEPCTL_USBAEP) == 0U)
    {
      USBx_OUTEP(epnum)->DOEPCTL |= (ep->maxpacket & USB_OTG_DOEPCTL_MPSIZ) |
                                    ((uint32_t)ep->type << 18) | (epnum << 22) |
                                    USB_OTG_DOEPCTL_USBAEP;
    }

    USBx_DEVICE->DEACHMSK |= USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16);
  }

  return HAL_OK;
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeactivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  /* Read DEPCTLn register */
  if (ep->is_in == 1U)
  {
    if ((USBx_INEP(epnum)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SNAK;
      USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
    }

    USBx_DEVICE->DEACHMSK &= ~(USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
    USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
    USBx_INEP(epnum)->DIEPCTL &= ~(USB_OTG_DIEPCTL_USBAEP |
                                   USB_OTG_DIEPCTL_MPSIZ |
                                   USB_OTG_DIEPCTL_TXFNUM |
                                   USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                   USB_OTG_DIEPCTL_EPTYP);
  }
  else
  {
    if ((USBx_OUTEP(epnum)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_SNAK;
      USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_EPDIS;
    }

    USBx_DEVICE->DEACHMSK &= ~(USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
    USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
    USBx_OUTEP(epnum)->DOEPCTL &= ~(USB_OTG_DOEPCTL_USBAEP |
                                    USB_OTG_DOEPCTL_MPSIZ |
                                    USB_OTG_DOEPCTL_SD0PID_SEVNFRM |
                                    USB_OTG_DOEPCTL_EPTYP);
  }

  return HAL_OK;
}

/**
  * @brief  De-activate and de-initialize a dedicated endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeactivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  /* Read DEPCTLn register */
  if (ep->is_in == 1U)
  {
    if ((USBx_INEP(epnum)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      USBx_INEP(epnum)->DIEPCTL  |= USB_OTG_DIEPCTL_SNAK;
      USBx_INEP(epnum)->DIEPCTL  |= USB_OTG_DIEPCTL_EPDIS;
    }

    USBx_INEP(epnum)->DIEPCTL &= ~ USB_OTG_DIEPCTL_USBAEP;
    USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
  }
  else
  {
    if ((USBx_OUTEP(epnum)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      USBx_OUTEP(epnum)->DOEPCTL  |= USB_OTG_DOEPCTL_SNAK;
      USBx_OUTEP(epnum)->DOEPCTL  |= USB_OTG_DOEPCTL_EPDIS;
    }

    USBx_OUTEP(epnum)->DOEPCTL &= ~USB_OTG_DOEPCTL_USBAEP;
    USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
  }

  return HAL_OK;
}

/**
  * @brief  USB_EPStartXfer : setup and starts a transfer over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPStartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep, uint8_t dma)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;
  uint16_t pktcnt;

  /* IN endpoint */
  if (ep->is_in == 1U)
  {
    /* Zero Length Packet? */
    if (ep->xfer_len == 0U)
    {
      USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);
      USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (1U << 19));
      USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
    }
    else
    {
      /* Program the transfer size and packet count
      * as follows: xfersize = N * maxpacket +
      * short_packet pktcnt = N + (short_packet
      * exist ? 1 : 0)
      */
      USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
      USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);

      if (epnum == 0U)
      {
        if (ep->xfer_len > ep->maxpacket)
        {
          ep->xfer_len = ep->maxpacket;
        }

        USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (1U << 19));
      }
      else
      {
        pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
        USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & ((uint32_t)pktcnt << 19));

        if (ep->type == EP_TYPE_ISOC)
        {
          USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_MULCNT);
          USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_MULCNT & ((uint32_t)pktcnt << 29));
        }
      }

      USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_XFRSIZ & ep->xfer_len);
    }

    if (dma == 1U)
    {
      if ((uint32_t)ep->dma_addr != 0U)
      {
        USBx_INEP(epnum)->DIEPDMA = (uint32_t)(ep->dma_addr);
      }

      if (ep->type == EP_TYPE_ISOC)
      {
        if ((USBx_DEVICE->DSTS & (1U << 8)) == 0U)
        {
          USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
        }
        else
        {
          USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
        }
      }

      /* EP enable, IN data in FIFO */
      USBx_INEP(epnum)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);
    }
    else
    {
      /* EP enable, IN data in FIFO */
      USBx_INEP(epnum)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);

      if (ep->type != EP_TYPE_ISOC)
      {
        /* Enable the Tx FIFO Empty Interrupt for this EP */
        if (ep->xfer_len > 0U)
        {
          USBx_DEVICE->DIEPEMPMSK |= 1UL << (ep->num & EP_ADDR_MSK);
        }
      }
      else
      {
        if ((USBx_DEVICE->DSTS & (1U << 8)) == 0U)
        {
          USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
        }
        else
        {
          USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
        }

        (void)USB_WritePacket(USBx, ep->xfer_buff, ep->num, (uint16_t)ep->xfer_len, dma);
      }
    }
  }
  else /* OUT endpoint */
  {
    /* Program the transfer size and packet count as follows:
    * pktcnt = N
    * xfersize = N * maxpacket
    */
    USBx_OUTEP(epnum)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_XFRSIZ);
    USBx_OUTEP(epnum)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_PKTCNT);

    if (epnum == 0U)
    {
      if (ep->xfer_len > 0U)
      {
        ep->xfer_len = ep->maxpacket;
      }

      /* Store transfer size, for EP0 this is equal to endpoint max packet size */
      ep->xfer_size = ep->maxpacket;

      USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_XFRSIZ & ep->xfer_size);
      USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
    }
    else
    {
      if (ep->xfer_len == 0U)
      {
        USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_XFRSIZ & ep->maxpacket);
        USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
      }
      else
      {
        pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
        ep->xfer_size = ep->maxpacket * pktcnt;

        USBx_OUTEP(epnum)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_PKTCNT & ((uint32_t)pktcnt << 19);
        USBx_OUTEP(epnum)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_XFRSIZ & ep->xfer_size;
      }
    }

    if (dma == 1U)
    {
      if ((uint32_t)ep->xfer_buff != 0U)
      {
        USBx_OUTEP(epnum)->DOEPDMA = (uint32_t)(ep->xfer_buff);
      }
    }

    if (ep->type == EP_TYPE_ISOC)
    {
      if ((USBx_DEVICE->DSTS & (1U << 8)) == 0U)
      {
        USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_SODDFRM;
      }
      else
      {
        USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM;
      }
    }
    /* EP enable */
    USBx_OUTEP(epnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
  }

  return HAL_OK;
}


/**
   * @brief  USB_EPStoptXfer  Stop transfer on an EP
   * @param  USBx  usb device instance
   * @param  ep pointer to endpoint structure
   * @retval HAL status
   */
HAL_StatusTypeDef USB_EPStopXfer(const USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
  __IO uint32_t count = 0U;
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;

  /* IN endpoint */
  if (ep->is_in == 1U)
  {
    /* EP enable, IN data in FIFO */
    if (((USBx_INEP(ep->num)->DIEPCTL) & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
    {
      USBx_INEP(ep->num)->DIEPCTL |= (USB_OTG_DIEPCTL_SNAK);
      USBx_INEP(ep->num)->DIEPCTL |= (USB_OTG_DIEPCTL_EPDIS);

      do
      {
        count++;

        if (count > 10000U)
        {
          ret = HAL_ERROR;
          break;
        }
      } while (((USBx_INEP(ep->num)->DIEPCTL) & USB_OTG_DIEPCTL_EPENA) ==  USB_OTG_DIEPCTL_EPENA);
    }
  }
  else /* OUT endpoint */
  {
    if (((USBx_OUTEP(ep->num)->DOEPCTL) & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      USBx_OUTEP(ep->num)->DOEPCTL |= (USB_OTG_DOEPCTL_SNAK);
      USBx_OUTEP(ep->num)->DOEPCTL |= (USB_OTG_DOEPCTL_EPDIS);

      do
      {
        count++;

        if (count > 10000U)
        {
          ret = HAL_ERROR;
          break;
        }
      } while (((USBx_OUTEP(ep->num)->DOEPCTL) & USB_OTG_DOEPCTL_EPENA) ==  USB_OTG_DOEPCTL_EPENA);
    }
  }

  return ret;
}


/**
  * @brief  USB_WritePacket : Writes a packet into the Tx FIFO associated
  *         with the EP/channel
  * @param  USBx  Selected device
  * @param  src   pointer to source buffer
  * @param  ch_ep_num  endpoint or host channel number
  * @param  len  Number of bytes to write
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL status
  */
HAL_StatusTypeDef USB_WritePacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *src,
                                  uint8_t ch_ep_num, uint16_t len, uint8_t dma)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint8_t *pSrc = src;
  uint32_t count32b;
  uint32_t i;

  if (dma == 0U)
  {
    count32b = ((uint32_t)len + 3U) / 4U;
    for (i = 0U; i < count32b; i++)
    {
      USBx_DFIFO((uint32_t)ch_ep_num) = __UNALIGNED_UINT32_READ(pSrc);
      pSrc++;
      pSrc++;
      pSrc++;
      pSrc++;
    }
  }

  return HAL_OK;
}

/**
  * @brief  USB_ReadPacket : read a packet from the RX FIFO
  * @param  USBx  Selected device
  * @param  dest  source pointer
  * @param  len  Number of bytes to read
  * @retval pointer to destination buffer
  */
void *USB_ReadPacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *dest, uint16_t len)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint8_t *pDest = dest;
  uint32_t pData;
  uint32_t i;
  uint32_t count32b = (uint32_t)len >> 2U;
  uint16_t remaining_bytes = len % 4U;

  for (i = 0U; i < count32b; i++)
  {
    __UNALIGNED_UINT32_WRITE(pDest, USBx_DFIFO(0U));
    pDest++;
    pDest++;
    pDest++;
    pDest++;
  }

  /* When Number of data is not word aligned, read the remaining byte */
  if (remaining_bytes != 0U)
  {
    i = 0U;
    __UNALIGNED_UINT32_WRITE(&pData, USBx_DFIFO(0U));

    do
    {
      *(uint8_t *)pDest = (uint8_t)(pData >> (8U * (uint8_t)(i)));
      i++;
      pDest++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);
  }

  return ((void *)pDest);
}

/**
  * @brief  USB_EPSetStall : set a stall condition over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPSetStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    if (((USBx_INEP(epnum)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == 0U) && (epnum != 0U))
    {
      USBx_INEP(epnum)->DIEPCTL &= ~(USB_OTG_DIEPCTL_EPDIS);
    }
    USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_STALL;
  }
  else
  {
    if (((USBx_OUTEP(epnum)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == 0U) && (epnum != 0U))
    {
      USBx_OUTEP(epnum)->DOEPCTL &= ~(USB_OTG_DOEPCTL_EPDIS);
    }
    USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_STALL;
  }

  return HAL_OK;
}

/**
  * @brief  USB_EPClearStall : Clear a stall condition over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPClearStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t epnum = (uint32_t)ep->num;

  if (ep->is_in == 1U)
  {
    USBx_INEP(epnum)->DIEPCTL &= ~USB_OTG_DIEPCTL_STALL;
    if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
    {
      USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM; /* DATA0 */
    }
  }
  else
  {
    USBx_OUTEP(epnum)->DOEPCTL &= ~USB_OTG_DOEPCTL_STALL;
    if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
    {
      USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM; /* DATA0 */
    }
  }
  return HAL_OK;
}

/**
  * @brief  USB_StopDevice : Stop the usb device mode
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_StopDevice(USB_OTG_GlobalTypeDef *USBx)
{
  HAL_StatusTypeDef ret;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i;

  /* Clear Pending interrupt */
  for (i = 0U; i < 15U; i++)
  {
    USBx_INEP(i)->DIEPINT = 0xFB7FU;
    USBx_OUTEP(i)->DOEPINT = 0xFB7FU;
  }

  /* Clear interrupt masks */
  USBx_DEVICE->DIEPMSK  = 0U;
  USBx_DEVICE->DOEPMSK  = 0U;
  USBx_DEVICE->DAINTMSK = 0U;

  /* Flush the FIFO */
  ret = USB_FlushRxFifo(USBx);
  if (ret != HAL_OK)
  {
    return ret;
  }

  ret = USB_FlushTxFifo(USBx,  0x10U);
  if (ret != HAL_OK)
  {
    return ret;
  }

  return ret;
}

/**
  * @brief  USB_SetDevAddress : Stop the usb device mode
  * @param  USBx  Selected device
  * @param  address  new device address to be assigned
  *          This parameter can be a value from 0 to 255
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetDevAddress(const USB_OTG_GlobalTypeDef *USBx, uint8_t address)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  USBx_DEVICE->DCFG &= ~(USB_OTG_DCFG_DAD);
  USBx_DEVICE->DCFG |= ((uint32_t)address << 4) & USB_OTG_DCFG_DAD;

  return HAL_OK;
}

/**
  * @brief  USB_DevConnect : Connect the USB device by enabling Rpu
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevConnect(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  /* In case phy is stopped, ensure to ungate and restore the phy CLK */
  USBx_PCGCCTL &= ~(USB_OTG_PCGCCTL_STOPCLK | USB_OTG_PCGCCTL_GATECLK);

  USBx_DEVICE->DCTL &= ~USB_OTG_DCTL_SDIS;

  return HAL_OK;
}

/**
  * @brief  USB_DevDisconnect : Disconnect the USB device by disabling Rpu
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevDisconnect(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  /* In case phy is stopped, ensure to ungate and restore the phy CLK */
  USBx_PCGCCTL &= ~(USB_OTG_PCGCCTL_STOPCLK | USB_OTG_PCGCCTL_GATECLK);

  USBx_DEVICE->DCTL |= USB_OTG_DCTL_SDIS;

  return HAL_OK;
}

/**
  * @brief  USB_ReadInterrupts: return the global USB interrupt status
  * @param  USBx  Selected device
  * @retval USB Global Interrupt status
  */
uint32_t USB_ReadInterrupts(USB_OTG_GlobalTypeDef const *USBx)
{
  uint32_t tmpreg;

  tmpreg = USBx->GINTSTS;
  tmpreg &= USBx->GINTMSK;

  return tmpreg;
}

/**
  * @brief  USB_ReadChInterrupts: return USB channel interrupt status
  * @param  USBx  Selected device
  * @param  chnum Channel number
  * @retval USB Channel Interrupt status
  */
uint32_t USB_ReadChInterrupts(const USB_OTG_GlobalTypeDef *USBx, uint8_t chnum)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg = USBx_HC(chnum)->HCINT;
  tmpreg &= USBx_HC(chnum)->HCINTMSK;

  return tmpreg;
}

/**
  * @brief  USB_ReadDevAllOutEpInterrupt: return the USB device OUT endpoints interrupt status
  * @param  USBx  Selected device
  * @retval USB Device OUT EP interrupt status
  */
uint32_t USB_ReadDevAllOutEpInterrupt(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg  = USBx_DEVICE->DAINT;
  tmpreg &= USBx_DEVICE->DAINTMSK;

  return ((tmpreg & 0xffff0000U) >> 16);
}

/**
  * @brief  USB_ReadDevAllInEpInterrupt: return the USB device IN endpoints interrupt status
  * @param  USBx  Selected device
  * @retval USB Device IN EP interrupt status
  */
uint32_t USB_ReadDevAllInEpInterrupt(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg  = USBx_DEVICE->DAINT;
  tmpreg &= USBx_DEVICE->DAINTMSK;

  return ((tmpreg & 0xFFFFU));
}

/**
  * @brief  Returns Device OUT EP Interrupt register
  * @param  USBx  Selected device
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device OUT EP Interrupt register
  */
uint32_t USB_ReadDevOutEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;

  tmpreg  = USBx_OUTEP((uint32_t)epnum)->DOEPINT;
  tmpreg &= USBx_DEVICE->DOEPMSK;

  return tmpreg;
}

/**
  * @brief  Returns Device IN EP Interrupt register
  * @param  USBx  Selected device
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device IN EP Interrupt register
  */
uint32_t USB_ReadDevInEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t tmpreg;
  uint32_t msk;
  uint32_t emp;

  msk = USBx_DEVICE->DIEPMSK;
  emp = USBx_DEVICE->DIEPEMPMSK;
  msk |= ((emp >> (epnum & EP_ADDR_MSK)) & 0x1U) << 7;
  tmpreg = USBx_INEP((uint32_t)epnum)->DIEPINT & msk;

  return tmpreg;
}

/**
  * @brief  USB_ClearInterrupts: clear a USB interrupt
  * @param  USBx  Selected device
  * @param  interrupt  flag
  * @retval None
  */
void  USB_ClearInterrupts(USB_OTG_GlobalTypeDef *USBx, uint32_t interrupt)
{
  USBx->GINTSTS &= interrupt;
}

/**
  * @brief  Returns USB core mode
  * @param  USBx  Selected device
  * @retval return core mode : Host or Device
  *          This parameter can be one of these values:
  *           0 : Host
  *           1 : Device
  */
uint32_t USB_GetMode(const USB_OTG_GlobalTypeDef *USBx)
{
  return ((USBx->GINTSTS) & 0x1U);
}

/**
  * @brief  Activate EP0 for Setup transactions
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateSetup(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  /* Set the MPS of the IN EP0 to 64 bytes */
  USBx_INEP(0U)->DIEPCTL &= ~USB_OTG_DIEPCTL_MPSIZ;

  USBx_DEVICE->DCTL |= USB_OTG_DCTL_CGINAK;

  return HAL_OK;
}

/**
  * @brief  Prepare the EP0 to start the first control setup
  * @param  USBx  Selected device
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @param  psetup  pointer to setup packet
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EP0_OutStart(const USB_OTG_GlobalTypeDef *USBx, uint8_t dma, const uint8_t *psetup)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t gSNPSiD = *(__IO const uint32_t *)(&USBx->CID + 0x1U);

  if (gSNPSiD > USB_OTG_CORE_ID_300A)
  {
    if ((USBx_OUTEP(0U)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
    {
      return HAL_OK;
    }
  }

  USBx_OUTEP(0U)->DOEPTSIZ = 0U;
  USBx_OUTEP(0U)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
  USBx_OUTEP(0U)->DOEPTSIZ |= (3U * 8U);
  USBx_OUTEP(0U)->DOEPTSIZ |=  USB_OTG_DOEPTSIZ_STUPCNT;

  if (dma == 1U)
  {
    USBx_OUTEP(0U)->DOEPDMA = (uint32_t)psetup;
    /* EP enable */
    USBx_OUTEP(0U)->DOEPCTL |= USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_USBAEP;
  }

  return HAL_OK;
}

/**
  * @brief  Reset the USB Core (needed after USB clock settings change)
  * @param  USBx  Selected device
  * @retval HAL status
  */
static HAL_StatusTypeDef USB_CoreReset(USB_OTG_GlobalTypeDef *USBx)
{
  __IO uint32_t count = 0U;

  /* Wait for AHB master IDLE state. */
  do
  {
    count++;

    if (count > HAL_USB_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

  /* Core Soft Reset */
  count = 0U;
  USBx->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;

  do
  {
    count++;

    if (count > HAL_USB_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_CSRST) == USB_OTG_GRSTCTL_CSRST);

  return HAL_OK;
}

/**
  * @brief  USB_HostInit : Initializes the USB OTG controller registers
  *         for Host mode
  * @param  USBx  Selected device
  * @param  cfg   pointer to a USB_OTG_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_HostInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i;

#if defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) \
 || defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx)
  /* Enable USB PHY pulldown resistors */
  USBx->GCCFG |= USB_OTG_GCCFG_PULLDOWNEN;
#endif /* defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) ||
          defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx) */

  /* Restart the Phy Clock */
  USBx_PCGCCTL = 0U;

#if defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) \
 || defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx)
  /* Disable VBUS override */
  USBx->GCCFG &= ~(USB_OTG_GCCFG_VBVALOVAL | USB_OTG_GCCFG_VBVALEXTOEN);
#endif /* defined (STM32U595xx) || defined (STM32U5A5xx) || defined (STM32U599xx) || defined (STM32U5A9xx) ||
          defined (STM32U5F7xx) || defined (STM32U5G7xx) || defined (STM32U5F9xx) || defined (STM32U5G9xx) */

  /* Disable VBUS sensing */
  USBx->GCCFG &= ~(USB_OTG_GCCFG_VBDEN);
#if defined (STM32U575xx) || defined (STM32U585xx)
  /* Disable Battery chargin detector */
  USBx->GCCFG &= ~(USB_OTG_GCCFG_BCDEN);
#else
  /* Disable Battery chargin detector */
  USBx->GCCFG &= ~(USB_OTG_GCCFG_PDEN);
  USBx->GCCFG &= ~(USB_OTG_GCCFG_SDEN);
#endif /* defined (STM32U575xx) || defined (STM32U585xx) */

  if ((USBx->GUSBCFG & USB_OTG_GUSBCFG_PHYSEL) == 0U)
  {
    if (cfg.speed == USBH_FSLS_SPEED)
    {
      /* Force Device Enumeration to FS/LS mode only */
      USBx_HOST->HCFG |= USB_OTG_HCFG_FSLSS;
    }
    else
    {
      /* Set default Max speed support */
      USBx_HOST->HCFG &= ~(USB_OTG_HCFG_FSLSS);
    }
  }
  else
  {
    /* Set default Max speed support */
    USBx_HOST->HCFG &= ~(USB_OTG_HCFG_FSLSS);
  }

  /* Make sure the FIFOs are flushed. */
  if (USB_FlushTxFifo(USBx, 0x10U) != HAL_OK) /* all Tx FIFOs */
  {
    ret = HAL_ERROR;
  }

  if (USB_FlushRxFifo(USBx) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  /* Clear all pending HC Interrupts */
  for (i = 0U; i < cfg.Host_channels; i++)
  {
    USBx_HC(i)->HCINT = CLEAR_INTERRUPT_MASK;
    USBx_HC(i)->HCINTMSK = 0U;
  }

  /* Disable all interrupts. */
  USBx->GINTMSK = 0U;

  /* Clear any pending interrupts */
  USBx->GINTSTS = CLEAR_INTERRUPT_MASK;
#if defined (USB_OTG_HS)
  if (USBx == USB_OTG_HS)
  {
    /* set Rx FIFO size */
    USBx->GRXFSIZ  = 0x200U;
    USBx->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x100U << 16) & USB_OTG_NPTXFD) | 0x200U);
    USBx->HPTXFSIZ = (uint32_t)(((0xE0U << 16) & USB_OTG_HPTXFSIZ_PTXFD) | 0x300U);
  }
  else
#endif /* defined (USB_OTG_HS) */
  {
    /* set Rx FIFO size */
    USBx->GRXFSIZ  = 0x80U;
    USBx->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x60U << 16) & USB_OTG_NPTXFD) | 0x80U);
    USBx->HPTXFSIZ = (uint32_t)(((0x40U << 16)& USB_OTG_HPTXFSIZ_PTXFD) | 0xE0U);
  }

  /* Enable the common interrupts */
  if (cfg.dma_enable == 0U)
  {
    USBx->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;
  }

  /* Enable interrupts matching to the Host mode ONLY */
  USBx->GINTMSK |= (USB_OTG_GINTMSK_PRTIM            | USB_OTG_GINTMSK_HCIM | \
                    USB_OTG_GINTMSK_SOFM             | USB_OTG_GINTSTS_DISCINT | \
                    USB_OTG_GINTMSK_PXFRM_IISOOXFRM  | USB_OTG_GINTMSK_WUIM);

  return ret;
}

/**
  * @brief  USB_InitFSLSPClkSel : Initializes the FSLSPClkSel field of the
  *         HCFG register on the PHY type and set the right frame interval
  * @param  USBx  Selected device
  * @param  freq  clock frequency
  *          This parameter can be one of these values:
  *           HCFG_48_MHZ : Full Speed 48 MHz Clock
  *           HCFG_6_MHZ : Low Speed 6 MHz Clock
  * @retval HAL status
  */
HAL_StatusTypeDef USB_InitFSLSPClkSel(const USB_OTG_GlobalTypeDef *USBx, uint8_t freq)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  USBx_HOST->HCFG &= ~(USB_OTG_HCFG_FSLSPCS);
  USBx_HOST->HCFG |= (uint32_t)freq & USB_OTG_HCFG_FSLSPCS;

  if (freq == HCFG_48_MHZ)
  {
    USBx_HOST->HFIR = HFIR_48_MHZ;
  }
  else if (freq == HCFG_6_MHZ)
  {
    USBx_HOST->HFIR = HFIR_6_MHZ;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  USB_OTG_ResetPort : Reset Host Port
  * @param  USBx  Selected device
  * @retval HAL status
  * @note (1)The application must wait at least 10 ms
  *   before clearing the reset bit.
  */
HAL_StatusTypeDef USB_ResetPort(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  __IO uint32_t hprt0 = 0U;

  hprt0 = USBx_HPRT0;

  hprt0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |
             USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

  USBx_HPRT0 = (USB_OTG_HPRT_PRST | hprt0);
  HAL_Delay(100U);                                 /* See Note #1 */
  USBx_HPRT0 = ((~USB_OTG_HPRT_PRST) & hprt0);
  HAL_Delay(10U);

  return HAL_OK;
}

/**
  * @brief  USB_DriveVbus : activate or de-activate vbus
  * @param  state  VBUS state
  *          This parameter can be one of these values:
  *           0 : Deactivate VBUS
  *           1 : Activate VBUS
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DriveVbus(const USB_OTG_GlobalTypeDef *USBx, uint8_t state)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  __IO uint32_t hprt0 = 0U;

  hprt0 = USBx_HPRT0;

  hprt0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |
             USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

  if (((hprt0 & USB_OTG_HPRT_PPWR) == 0U) && (state == 1U))
  {
    USBx_HPRT0 = (USB_OTG_HPRT_PPWR | hprt0);
  }
  if (((hprt0 & USB_OTG_HPRT_PPWR) == USB_OTG_HPRT_PPWR) && (state == 0U))
  {
    USBx_HPRT0 = ((~USB_OTG_HPRT_PPWR) & hprt0);
  }
  return HAL_OK;
}

/**
  * @brief  Return Host Core speed
  * @param  USBx  Selected device
  * @retval speed : Host speed
  *          This parameter can be one of these values:
  *            @arg HCD_SPEED_HIGH: High speed mode
  *            @arg HCD_SPEED_FULL: Full speed mode
  *            @arg HCD_SPEED_LOW: Low speed mode
  */
uint32_t USB_GetHostSpeed(USB_OTG_GlobalTypeDef const *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  __IO uint32_t hprt0 = 0U;

  hprt0 = USBx_HPRT0;
  return ((hprt0 & USB_OTG_HPRT_PSPD) >> 17);
}

/**
  * @brief  Return Host Current Frame number
  * @param  USBx  Selected device
  * @retval current frame number
  */
uint32_t USB_GetCurrentFrame(USB_OTG_GlobalTypeDef const *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  return (USBx_HOST->HFNUM & USB_OTG_HFNUM_FRNUM);
}

/**
  * @brief  Initialize a host channel
  * @param  USBx  Selected device
  * @param  ch_num  Channel number
  *         This parameter can be a value from 1 to 15
  * @param  epnum  Endpoint number
  *          This parameter can be a value from 1 to 15
  * @param  dev_address  Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed  Current device speed
  *          This parameter can be one of these values:
  *            @arg USB_OTG_SPEED_HIGH: High speed mode
  *            @arg USB_OTG_SPEED_FULL: Full speed mode
  *            @arg USB_OTG_SPEED_LOW: Low speed mode
  * @param  ep_type  Endpoint Type
  *          This parameter can be one of these values:
  *            @arg EP_TYPE_CTRL: Control type
  *            @arg EP_TYPE_ISOC: Isochronous type
  *            @arg EP_TYPE_BULK: Bulk type
  *            @arg EP_TYPE_INTR: Interrupt type
  * @param  mps  Max Packet Size
  *          This parameter can be a value from 0 to 32K
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_Init(USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num,
                              uint8_t epnum, uint8_t dev_address, uint8_t speed,
                              uint8_t ep_type, uint16_t mps)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t HCcharEpDir;
  uint32_t HCcharLowSpeed;
  uint32_t HostCoreSpeed;

  /* Clear old interrupt conditions for this host channel. */
  USBx_HC((uint32_t)ch_num)->HCINT = CLEAR_INTERRUPT_MASK;

  /* Enable channel interrupts required for this transfer. */
  switch (ep_type)
  {
    case EP_TYPE_CTRL:
    case EP_TYPE_BULK:
      USBx_HC((uint32_t)ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM  |
                                            USB_OTG_HCINTMSK_STALLM |
                                            USB_OTG_HCINTMSK_TXERRM |
                                            USB_OTG_HCINTMSK_DTERRM |
                                            USB_OTG_HCINTMSK_AHBERR |
                                            USB_OTG_HCINTMSK_NAKM;

      if ((epnum & 0x80U) == 0x80U)
      {
        USBx_HC((uint32_t)ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_BBERRM;
      }
      else
      {
#if defined (USB_OTG_HS)
        if (USBx == USB_OTG_HS)
        {
          USBx_HC((uint32_t)ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_NYET |
                                                 USB_OTG_HCINTMSK_ACKM;
        }
#endif /* defined (USB_OTG_HS) */
      }
      break;

    case EP_TYPE_INTR:
      USBx_HC((uint32_t)ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM  |
                                            USB_OTG_HCINTMSK_STALLM |
                                            USB_OTG_HCINTMSK_TXERRM |
                                            USB_OTG_HCINTMSK_DTERRM |
                                            USB_OTG_HCINTMSK_NAKM   |
                                            USB_OTG_HCINTMSK_AHBERR |
                                            USB_OTG_HCINTMSK_FRMORM;

      if ((epnum & 0x80U) == 0x80U)
      {
        USBx_HC((uint32_t)ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_BBERRM;
      }

      break;

    case EP_TYPE_ISOC:
      USBx_HC((uint32_t)ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM  |
                                            USB_OTG_HCINTMSK_ACKM   |
                                            USB_OTG_HCINTMSK_AHBERR |
                                            USB_OTG_HCINTMSK_FRMORM;

      if ((epnum & 0x80U) == 0x80U)
      {
        USBx_HC((uint32_t)ch_num)->HCINTMSK |= (USB_OTG_HCINTMSK_TXERRM | USB_OTG_HCINTMSK_BBERRM);
      }
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  /* Clear Hub Start Split transaction */
  USBx_HC((uint32_t)ch_num)->HCSPLT = 0U;

  /* Enable host channel Halt interrupt */
  USBx_HC((uint32_t)ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_CHHM;

  /* Enable the top level host channel interrupt. */
  USBx_HOST->HAINTMSK |= 1UL << (ch_num & 0xFU);

  /* Make sure host channel interrupts are enabled. */
  USBx->GINTMSK |= USB_OTG_GINTMSK_HCIM;

  /* Program the HCCHAR register */
  if ((epnum & 0x80U) == 0x80U)
  {
    HCcharEpDir = (0x1U << 15) & USB_OTG_HCCHAR_EPDIR;
  }
  else
  {
    HCcharEpDir = 0U;
  }

  HostCoreSpeed = USB_GetHostSpeed(USBx);

  /* LS device plugged to HUB */
  if ((speed == HPRT0_PRTSPD_LOW_SPEED) && (HostCoreSpeed != HPRT0_PRTSPD_LOW_SPEED))
  {
    HCcharLowSpeed = (0x1U << 17) & USB_OTG_HCCHAR_LSDEV;
  }
  else
  {
    HCcharLowSpeed = 0U;
  }

  USBx_HC((uint32_t)ch_num)->HCCHAR = (((uint32_t)dev_address << 22) & USB_OTG_HCCHAR_DAD) |
                                      ((((uint32_t)epnum & 0x7FU) << 11) & USB_OTG_HCCHAR_EPNUM) |
                                      (((uint32_t)ep_type << 18) & USB_OTG_HCCHAR_EPTYP) |
                                      ((uint32_t)mps & USB_OTG_HCCHAR_MPSIZ) |
                                      USB_OTG_HCCHAR_MC_0 | HCcharEpDir | HCcharLowSpeed;

  if ((ep_type == EP_TYPE_INTR) || (ep_type == EP_TYPE_ISOC))
  {
    USBx_HC((uint32_t)ch_num)->HCCHAR |= USB_OTG_HCCHAR_ODDFRM;
  }

  return ret;
}

/**
  * @brief  Start a transfer over a host channel
  * @param  USBx  Selected device
  * @param  hc  pointer to host channel structure
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_StartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_HCTypeDef *hc, uint8_t dma)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t ch_num = (uint32_t)hc->ch_num;
  __IO uint32_t tmpreg;
  uint8_t  is_oddframe;
  uint16_t len_words;
  uint16_t num_packets;
  uint16_t max_hc_pkt_count = HC_MAX_PKT_CNT;

#if defined (USB_OTG_HS)
  if (USBx == USB_OTG_HS)
  {
    /* in DMA mode host Core automatically issues ping in case of NYET/NAK */
    if (dma == 1U)
    {
      if (((hc->ep_type == EP_TYPE_CTRL) || (hc->ep_type == EP_TYPE_BULK)) && (hc->do_ssplit == 0U))
      {

        USBx_HC((uint32_t)ch_num)->HCINTMSK &= ~(USB_OTG_HCINTMSK_NYET |
                                                 USB_OTG_HCINTMSK_ACKM |
                                                 USB_OTG_HCINTMSK_NAKM);
      }
    }
    else
    {
      if ((hc->speed == USBH_HS_SPEED) && (hc->do_ping == 1U))
      {
        (void)USB_DoPing(USBx, hc->ch_num);
        return HAL_OK;
      }
    }
  }
#endif /* defined (USB_OTG_HS) */

  if (hc->do_ssplit == 1U)
  {
    /* Set number of packet to 1 for Split transaction */
    num_packets = 1U;

    if (hc->ep_is_in != 0U)
    {
      hc->XferSize = (uint32_t)num_packets * hc->max_packet;
    }
    else
    {
      if (hc->ep_type == EP_TYPE_ISOC)
      {
        if (hc->xfer_len > ISO_SPLT_MPS)
        {
          /* Isochrone Max Packet Size for Split mode */
          hc->XferSize = hc->max_packet;
          hc->xfer_len = hc->XferSize;

          if ((hc->iso_splt_xactPos == HCSPLT_BEGIN) || (hc->iso_splt_xactPos == HCSPLT_MIDDLE))
          {
            hc->iso_splt_xactPos = HCSPLT_MIDDLE;
          }
          else
          {
            hc->iso_splt_xactPos = HCSPLT_BEGIN;
          }
        }
        else
        {
          hc->XferSize = hc->xfer_len;

          if ((hc->iso_splt_xactPos != HCSPLT_BEGIN) && (hc->iso_splt_xactPos != HCSPLT_MIDDLE))
          {
            hc->iso_splt_xactPos = HCSPLT_FULL;
          }
          else
          {
            hc->iso_splt_xactPos = HCSPLT_END;
          }
        }
      }
      else
      {
        if ((dma == 1U) && (hc->xfer_len > hc->max_packet))
        {
          hc->XferSize = (uint32_t)num_packets * hc->max_packet;
        }
        else
        {
          hc->XferSize = hc->xfer_len;
        }
      }
    }
  }
  else
  {
    /* Compute the expected number of packets associated to the transfer */
    if (hc->xfer_len > 0U)
    {
      num_packets = (uint16_t)((hc->xfer_len + hc->max_packet - 1U) / hc->max_packet);

      if (num_packets > max_hc_pkt_count)
      {
        num_packets = max_hc_pkt_count;
        hc->XferSize = (uint32_t)num_packets * hc->max_packet;
      }
    }
    else
    {
      num_packets = 1U;
    }

    /*
    * For IN channel HCTSIZ.XferSize is expected to be an integer multiple of
    * max_packet size.
    */
    if (hc->ep_is_in != 0U)
    {
      hc->XferSize = (uint32_t)num_packets * hc->max_packet;
    }
    else
    {
      hc->XferSize = hc->xfer_len;
    }
  }

  /* Initialize the HCTSIZn register */
  USBx_HC(ch_num)->HCTSIZ = (hc->XferSize & USB_OTG_HCTSIZ_XFRSIZ) |
                            (((uint32_t)num_packets << 19) & USB_OTG_HCTSIZ_PKTCNT) |
                            (((uint32_t)hc->data_pid << 29) & USB_OTG_HCTSIZ_DPID);

  if (dma != 0U)
  {
    /* xfer_buff MUST be 32-bits aligned */
    USBx_HC(ch_num)->HCDMA = (uint32_t)hc->xfer_buff;
  }

  is_oddframe = (((uint32_t)USBx_HOST->HFNUM & 0x01U) != 0U) ? 0U : 1U;
  USBx_HC(ch_num)->HCCHAR &= ~USB_OTG_HCCHAR_ODDFRM;
  USBx_HC(ch_num)->HCCHAR |= (uint32_t)is_oddframe << 29;

  if (hc->do_ssplit == 1U)
  {
    /* Set Hub start Split transaction */
    USBx_HC((uint32_t)ch_num)->HCSPLT = ((uint32_t)hc->hub_addr << USB_OTG_HCSPLT_HUBADDR_Pos) |
                                        (uint32_t)hc->hub_port_nbr | USB_OTG_HCSPLT_SPLITEN;

    /* unmask ack & nyet for IN/OUT transactions */
    USBx_HC((uint32_t)ch_num)->HCINTMSK |= (USB_OTG_HCINTMSK_ACKM |
                                            USB_OTG_HCINTMSK_NYET);

    if ((hc->do_csplit == 1U) && (hc->ep_is_in == 0U))
    {
      USBx_HC((uint32_t)ch_num)->HCSPLT |= USB_OTG_HCSPLT_COMPLSPLT;
      USBx_HC((uint32_t)ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_NYET;
    }

    if (((hc->ep_type == EP_TYPE_ISOC) || (hc->ep_type == EP_TYPE_INTR)) &&
        (hc->do_csplit == 1U) && (hc->ep_is_in == 1U))
    {
      USBx_HC((uint32_t)ch_num)->HCSPLT |= USB_OTG_HCSPLT_COMPLSPLT;
    }

    /* Position management for iso out transaction on split mode */
    if ((hc->ep_type == EP_TYPE_ISOC) && (hc->ep_is_in == 0U))
    {
      /* Set data payload position */
      switch (hc->iso_splt_xactPos)
      {
        case HCSPLT_BEGIN:
          /* First data payload for OUT Transaction */
          USBx_HC((uint32_t)ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS_1;
          break;

        case HCSPLT_MIDDLE:
          /* Middle data payload for OUT Transaction */
          USBx_HC((uint32_t)ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS_Pos;
          break;

        case HCSPLT_END:
          /* End data payload for OUT Transaction */
          USBx_HC((uint32_t)ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS_0;
          break;

        case HCSPLT_FULL:
          /* Entire data payload for OUT Transaction */
          USBx_HC((uint32_t)ch_num)->HCSPLT |= USB_OTG_HCSPLT_XACTPOS;
          break;

        default:
          break;
      }
    }
  }
  else
  {
    /* Clear Hub Start Split transaction */
    USBx_HC((uint32_t)ch_num)->HCSPLT = 0U;
  }

  /* Set host channel enable */
  tmpreg = USBx_HC(ch_num)->HCCHAR;
  tmpreg &= ~USB_OTG_HCCHAR_CHDIS;

  /* make sure to set the correct ep direction */
  if (hc->ep_is_in != 0U)
  {
    tmpreg |= USB_OTG_HCCHAR_EPDIR;
  }
  else
  {
    tmpreg &= ~USB_OTG_HCCHAR_EPDIR;
  }
  tmpreg |= USB_OTG_HCCHAR_CHENA;
  USBx_HC(ch_num)->HCCHAR = tmpreg;

  if (dma != 0U) /* dma mode */
  {
    return HAL_OK;
  }

  if ((hc->ep_is_in == 0U) && (hc->xfer_len > 0U) && (hc->do_csplit == 0U))
  {
    switch (hc->ep_type)
    {
      /* Non periodic transfer */
      case EP_TYPE_CTRL:
      case EP_TYPE_BULK:

        len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);

        /* check if there is enough space in FIFO space */
        if (len_words > (USBx->HNPTXSTS & 0xFFFFU))
        {
          /* need to process data in nptxfempty interrupt */
          USBx->GINTMSK |= USB_OTG_GINTMSK_NPTXFEM;
        }
        break;

      /* Periodic transfer */
      case EP_TYPE_INTR:
      case EP_TYPE_ISOC:
        len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);
        /* check if there is enough space in FIFO space */
        if (len_words > (USBx_HOST->HPTXSTS & 0xFFFFU)) /* split the transfer */
        {
          /* need to process data in ptxfempty interrupt */
          USBx->GINTMSK |= USB_OTG_GINTMSK_PTXFEM;
        }
        break;

      default:
        break;
    }

    /* Write packet into the Tx FIFO. */
    (void)USB_WritePacket(USBx, hc->xfer_buff, hc->ch_num, (uint16_t)hc->xfer_len, 0);
  }

  return HAL_OK;
}

/**
  * @brief Read all host channel interrupts status
  * @param  USBx  Selected device
  * @retval HAL state
  */
uint32_t USB_HC_ReadInterrupt(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  return ((USBx_HOST->HAINT) & 0xFFFFU);
}

/**
  * @brief  Halt a host channel
  * @param  USBx  Selected device
  * @param  hc_num  Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_Halt(const USB_OTG_GlobalTypeDef *USBx, uint8_t hc_num)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t hcnum = (uint32_t)hc_num;
  __IO uint32_t count = 0U;
  uint32_t HcEpType = (USBx_HC(hcnum)->HCCHAR & USB_OTG_HCCHAR_EPTYP) >> 18;
  uint32_t ChannelEna = (USBx_HC(hcnum)->HCCHAR & USB_OTG_HCCHAR_CHENA) >> 31;
  uint32_t SplitEna = (USBx_HC(hcnum)->HCSPLT & USB_OTG_HCSPLT_SPLITEN) >> 31;

  /* In buffer DMA, Channel disable must not be programmed for non-split periodic channels.
     At the end of the next uframe/frame (in the worst case), the core generates a channel halted
     and disables the channel automatically. */

  if ((((USBx->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == USB_OTG_GAHBCFG_DMAEN) && (SplitEna == 0U)) &&
      ((ChannelEna == 0U) || (((HcEpType == HCCHAR_ISOC) || (HcEpType == HCCHAR_INTR)))))
  {
    return HAL_OK;
  }

  /* Check for space in the request queue to issue the halt. */
  if ((HcEpType == HCCHAR_CTRL) || (HcEpType == HCCHAR_BULK))
  {
    USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHDIS;

    if ((USBx->GAHBCFG & USB_OTG_GAHBCFG_DMAEN) == 0U)
    {
      if ((USBx->HNPTXSTS & (0xFFU << 16)) == 0U)
      {
        USBx_HC(hcnum)->HCCHAR &= ~USB_OTG_HCCHAR_CHENA;
        USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
        do
        {
          count++;

          if (count > 1000U)
          {
            break;
          }
        } while ((USBx_HC(hcnum)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
      }
      else
      {
        USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
      }
    }
    else
    {
      USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
    }
  }
  else
  {
    USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHDIS;

    if ((USBx_HOST->HPTXSTS & (0xFFU << 16)) == 0U)
    {
      USBx_HC(hcnum)->HCCHAR &= ~USB_OTG_HCCHAR_CHENA;
      USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
      do
      {
        count++;

        if (count > 1000U)
        {
          break;
        }
      } while ((USBx_HC(hcnum)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
    }
    else
    {
      USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Initiate Do Ping protocol
  * @param  USBx  Selected device
  * @param  hc_num  Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_DoPing(const USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num)
{
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t chnum = (uint32_t)ch_num;
  uint32_t num_packets = 1U;
  uint32_t tmpreg;

  USBx_HC(chnum)->HCTSIZ = ((num_packets << 19) & USB_OTG_HCTSIZ_PKTCNT) |
                           USB_OTG_HCTSIZ_DOPING;

  /* Set host channel enable */
  tmpreg = USBx_HC(chnum)->HCCHAR;
  tmpreg &= ~USB_OTG_HCCHAR_CHDIS;
  tmpreg |= USB_OTG_HCCHAR_CHENA;
  USBx_HC(chnum)->HCCHAR = tmpreg;

  return HAL_OK;
}

/**
  * @brief  Stop Host Core
  * @param  USBx  Selected device
  * @retval HAL state
  */
HAL_StatusTypeDef USB_StopHost(USB_OTG_GlobalTypeDef *USBx)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t USBx_BASE = (uint32_t)USBx;
  __IO uint32_t count = 0U;
  uint32_t value;
  uint32_t i;

  (void)USB_DisableGlobalInt(USBx);

  /* Flush USB FIFO */
  if (USB_FlushTxFifo(USBx, 0x10U) != HAL_OK) /* all Tx FIFOs */
  {
    ret = HAL_ERROR;
  }

  if (USB_FlushRxFifo(USBx) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  /* Flush out any leftover queued requests. */
  for (i = 0U; i <= 15U; i++)
  {
    value = USBx_HC(i)->HCCHAR;
    value |=  USB_OTG_HCCHAR_CHDIS;
    value &= ~USB_OTG_HCCHAR_CHENA;
    value &= ~USB_OTG_HCCHAR_EPDIR;
    USBx_HC(i)->HCCHAR = value;
  }

  /* Halt all channels to put them into a known state. */
  for (i = 0U; i <= 15U; i++)
  {
    value = USBx_HC(i)->HCCHAR;
    value |= USB_OTG_HCCHAR_CHDIS;
    value |= USB_OTG_HCCHAR_CHENA;
    value &= ~USB_OTG_HCCHAR_EPDIR;
    USBx_HC(i)->HCCHAR = value;

    do
    {
      count++;

      if (count > 1000U)
      {
        break;
      }
    } while ((USBx_HC(i)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
  }

  /* Clear any pending Host interrupts */
  USBx_HOST->HAINT = CLEAR_INTERRUPT_MASK;
  USBx->GINTSTS = CLEAR_INTERRUPT_MASK;

  (void)USB_EnableGlobalInt(USBx);

  return ret;
}

/**
  * @brief  USB_ActivateRemoteWakeup active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  if ((USBx_DEVICE->DSTS & USB_OTG_DSTS_SUSPSTS) == USB_OTG_DSTS_SUSPSTS)
  {
    /* active Remote wakeup signalling */
    USBx_DEVICE->DCTL |= USB_OTG_DCTL_RWUSIG;
  }

  return HAL_OK;
}

/**
  * @brief  USB_DeActivateRemoteWakeup de-active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t USBx_BASE = (uint32_t)USBx;

  /* active Remote wakeup signalling */
  USBx_DEVICE->DCTL &= ~(USB_OTG_DCTL_RWUSIG);

  return HAL_OK;
}
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

#if defined (USB_DRD_FS)
static HAL_StatusTypeDef USB_CoreReset(USB_DRD_TypeDef *USBx);
#if (USE_USB_DOUBLE_BUFFER == 1U)
static HAL_StatusTypeDef USB_HC_BULK_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                  USB_DRD_HCTypeDef *hc,
                                                  uint32_t ch_reg,
                                                  uint32_t *len);

static HAL_StatusTypeDef USB_HC_ISO_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                 USB_DRD_HCTypeDef *hc,
                                                 uint32_t len);
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */

/**
  * @brief  Reset the USB Core (needed after USB clock settings change)
  * @param  USBx Selected device
  * @retval HAL status
  */
static HAL_StatusTypeDef USB_CoreReset(USB_DRD_TypeDef *USBx)
{
  /* Disable Host Mode */
  USBx->CNTR &= ~USB_CNTR_HOST;

  /* Force Reset IP */
  USBx->CNTR |= USB_CNTR_USBRST;

  return HAL_OK;
}

/**
  * @brief  Initializes the USB Core
  * @param  USBx USB Instance
  * @param  cfg pointer to a USB_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_CoreInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret;
  UNUSED(cfg);

  if (USBx == NULL)
  {
    return HAL_ERROR;
  }

  /* Reset after a PHY select */
  ret = USB_CoreReset(USBx);

  /* Clear pending interrupts */
  USBx->ISTR = 0U;

  return ret;
}

/**
  * @brief  USB_EnableGlobalInt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EnableGlobalInt(USB_DRD_TypeDef *USBx)
{
  uint32_t winterruptmask;

  /* Clear pending interrupts */
  USBx->ISTR = 0U;

  /* Set winterruptmask variable */
  winterruptmask = USB_CNTR_CTRM  | USB_CNTR_WKUPM |
                   USB_CNTR_SUSPM | USB_CNTR_ERRM |
                   USB_CNTR_SOFM | USB_CNTR_ESOFM |
                   USB_CNTR_RESETM | USB_CNTR_L1REQM;

  /* Set interrupt mask */
  USBx->CNTR = winterruptmask;

  return HAL_OK;
}

/**
  * @brief  USB_DisableGlobalInt
  *         Disable the controller's Global Int in the AHB Config reg
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DisableGlobalInt(USB_DRD_TypeDef *USBx)
{
  uint32_t winterruptmask;

  /* Set winterruptmask variable */
  winterruptmask = USB_CNTR_CTRM  | USB_CNTR_WKUPM |
                   USB_CNTR_SUSPM | USB_CNTR_ERRM |
                   USB_CNTR_SOFM | USB_CNTR_ESOFM |
                   USB_CNTR_RESETM | USB_CNTR_L1REQM;

  /* Clear interrupt mask */
  USBx->CNTR &= ~winterruptmask;

  return HAL_OK;
}

/**
  * @brief  USB_SetCurrentMode Set functional mode
  * @param  USBx Selected device
  * @param  mode current core mode
  *          This parameter can be one of the these values:
  *            @arg USB_DEVICE_MODE Peripheral mode
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetCurrentMode(USB_DRD_TypeDef *USBx, USB_DRD_ModeTypeDef mode)
{
  if (mode == USB_DEVICE_MODE)
  {
    USBx->CNTR &= ~USB_CNTR_HOST;
  }
  else if (mode == USB_HOST_MODE)
  {
    USBx->CNTR |= USB_CNTR_HOST;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  USB_DevInit Initializes the USB controller registers
  *         for device mode
  * @param  USBx Selected device
  * @param  cfg  pointer to a USB_DRD_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret;

  /* Prevent unused argument(s) compilation warning */
  UNUSED(cfg);

  /* Force Reset */
  USBx->CNTR = USB_CNTR_USBRST;

  /* Release Reset */
  USBx->CNTR &= ~USB_CNTR_USBRST;

  /* Set the Device Mode */
  ret = USB_SetCurrentMode(USBx, USB_DEVICE_MODE);

  /* Clear pending interrupts */
  USBx->ISTR = 0U;

  return ret;
}

/**
  * @brief  USB_FlushTxFifo : Flush a Tx FIFO
  * @param  USBx : Selected device
  * @param  num : FIFO number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval HAL status
  */
HAL_StatusTypeDef USB_FlushTxFifo(USB_DRD_TypeDef const *USBx, uint32_t num)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(USBx);
  UNUSED(num);

  /* NOTE : - This function is not required by USB Device FS peripheral, it is used
              only by USB OTG FS peripheral.
            - This function is added to ensure compatibility across platforms.
   */

  return HAL_OK;
}

/**
  * @brief  USB_FlushRxFifo : Flush Rx FIFO
  * @param  USBx : Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_FlushRxFifo(USB_DRD_TypeDef const *USBx)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(USBx);

  /* NOTE : - This function is not required by USB Device FS peripheral, it is used
              only by USB OTG FS peripheral.
            - This function is added to ensure compatibility across platforms.
   */

  return HAL_OK;
}


#if defined (HAL_PCD_MODULE_ENABLED)
/**
  * @brief  Activate and configure an endpoint
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateEndpoint(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t wEpRegVal;

  wEpRegVal = PCD_GET_ENDPOINT(USBx, ep->num) & USB_EP_T_MASK;

  /* initialize Endpoint */
  switch (ep->type)
  {
    case EP_TYPE_CTRL:
      wEpRegVal |= USB_EP_CONTROL;
      break;

    case EP_TYPE_BULK:
      wEpRegVal |= USB_EP_BULK;
      break;

    case EP_TYPE_INTR:
      wEpRegVal |= USB_EP_INTERRUPT;
      break;

    case EP_TYPE_ISOC:
      wEpRegVal |= USB_EP_ISOCHRONOUS;
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  PCD_SET_ENDPOINT(USBx, ep->num, (wEpRegVal | USB_EP_VTRX | USB_EP_VTTX));

  PCD_SET_EP_ADDRESS(USBx, ep->num, ep->num);

  if (ep->doublebuffer == 0U)
  {
    if (ep->is_in != 0U)
    {
      /*Set the endpoint Transmit buffer address */
      PCD_SET_EP_TX_ADDRESS(USBx, ep->num, ep->pmaadress);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      if (ep->type != EP_TYPE_ISOC)
      {
        /* Configure NAK status for the Endpoint */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
      }
    }
    else
    {
      /* Set the endpoint Receive buffer address */
      PCD_SET_EP_RX_ADDRESS(USBx, ep->num, ep->pmaadress);

      /* Set the endpoint Receive buffer counter */
      PCD_SET_EP_RX_CNT(USBx, ep->num, ep->maxpacket);
      PCD_CLEAR_RX_DTOG(USBx, ep->num);

      if (ep->num == 0U)
      {
        /* Configure VALID status for EP0 */
        PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
      }
      else
      {
        /* Configure NAK status for OUT Endpoint */
        PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_NAK);
      }
    }
  }
#if (USE_USB_DOUBLE_BUFFER == 1U)
  /* Double Buffer */
  else
  {
    if (ep->type == EP_TYPE_BULK)
    {
      /* Set bulk endpoint as double buffered */
      PCD_SET_BULK_EP_DBUF(USBx, ep->num);
    }
    else
    {
      /* Set the ISOC endpoint in double buffer mode */
      PCD_CLEAR_EP_KIND(USBx, ep->num);
    }

    /* Set buffer address for double buffered mode */
    PCD_SET_EP_DBUF_ADDR(USBx, ep->num, ep->pmaaddr0, ep->pmaaddr1);

    if (ep->is_in == 0U)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      /* Set endpoint RX count */
      PCD_SET_EP_DBUF_CNT(USBx, ep->num, ep->is_in, ep->maxpacket);

      /* Set endpoint RX to valid state */
      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT */
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      if (ep->type != EP_TYPE_ISOC)
      {
        /* Configure NAK status for the Endpoint */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
      }

      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
    }
  }
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */

  return ret;
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeactivateEndpoint(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  if (ep->doublebuffer == 0U)
  {
    if (ep->is_in != 0U)
    {
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      /* Configure DISABLE status for the Endpoint */
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
    }

    else
    {
      PCD_CLEAR_RX_DTOG(USBx, ep->num);

      /* Configure DISABLE status for the Endpoint */
      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
    }
  }
#if (USE_USB_DOUBLE_BUFFER == 1U)
  /* Double Buffer */
  else
  {
    if (ep->is_in == 0U)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);

      /* Reset value of the data toggle bits for the endpoint out*/
      PCD_TX_DTOG(USBx, ep->num);

      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(USBx, ep->num);
      PCD_CLEAR_TX_DTOG(USBx, ep->num);
      PCD_RX_DTOG(USBx, ep->num);

      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
      PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
    }
  }
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */

  return HAL_OK;
}

/**
  * @brief  USB_EPStartXfer setup and starts a transfer over an EP
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPStartXfer(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  uint32_t len;
#if (USE_USB_DOUBLE_BUFFER == 1U)
  uint16_t pmabuffer;
  uint16_t wEPVal;
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */

  /* IN endpoint */
  if (ep->is_in == 1U)
  {
    /* Multi packet transfer */
    if (ep->xfer_len > ep->maxpacket)
    {
      len = ep->maxpacket;
    }
    else
    {
      len = ep->xfer_len;
    }

    /* configure and validate Tx endpoint */
    if (ep->doublebuffer == 0U)
    {
      USB_WritePMA(USBx, ep->xfer_buff, ep->pmaadress, (uint16_t)len);
      PCD_SET_EP_TX_CNT(USBx, ep->num, len);
    }
#if (USE_USB_DOUBLE_BUFFER == 1U)
    else
    {
      /* double buffer bulk management */
      if (ep->type == EP_TYPE_BULK)
      {
        if (ep->xfer_len_db > ep->maxpacket)
        {
          /* enable double buffer */
          PCD_SET_BULK_EP_DBUF(USBx, ep->num);

          /* each Time to write in PMA xfer_len_db will */
          ep->xfer_len_db -= len;

          /* Fill the two first buffer in the Buffer0 & Buffer1 */
          if ((PCD_GET_ENDPOINT(USBx, ep->num) & USB_EP_DTOG_TX) != 0U)
          {
            /* Set the Double buffer counter for pmabuffer1 */
            PCD_SET_EP_DBUF1_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr1;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
            ep->xfer_buff += len;

            if (ep->xfer_len_db > ep->maxpacket)
            {
              ep->xfer_len_db -= len;
            }
            else
            {
              len = ep->xfer_len_db;
              ep->xfer_len_db = 0U;
            }

            /* Set the Double buffer counter for pmabuffer0 */
            PCD_SET_EP_DBUF0_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr0;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          }
          else
          {
            /* Set the Double buffer counter for pmabuffer0 */
            PCD_SET_EP_DBUF0_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr0;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
            ep->xfer_buff += len;

            if (ep->xfer_len_db > ep->maxpacket)
            {
              ep->xfer_len_db -= len;
            }
            else
            {
              len = ep->xfer_len_db;
              ep->xfer_len_db = 0U;
            }

            /* Set the Double buffer counter for pmabuffer1 */
            PCD_SET_EP_DBUF1_CNT(USBx, ep->num, ep->is_in, len);
            pmabuffer = ep->pmaaddr1;

            /* Write the user buffer to USB PMA */
            USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
          }
        }
        /* auto Switch to single buffer mode when transfer <Mps no need to manage in double buffer */
        else
        {
          len = ep->xfer_len_db;

          /* disable double buffer mode for Bulk endpoint */
          PCD_CLEAR_BULK_EP_DBUF(USBx, ep->num);

          /* Set Tx count with nbre of byte to be transmitted */
          PCD_SET_EP_TX_CNT(USBx, ep->num, len);
          pmabuffer = ep->pmaaddr0;

          /* Write the user buffer to USB PMA */
          USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
        }
      }
      else /* Manage isochronous double buffer IN mode */
      {
        /* Each Time to write in PMA xfer_len_db will */
        ep->xfer_len_db -= len;

        /* Fill the data buffer */
        if ((PCD_GET_ENDPOINT(USBx, ep->num) & USB_EP_DTOG_TX) != 0U)
        {
          /* Set the Double buffer counter for pmabuffer1 */
          PCD_SET_EP_DBUF1_CNT(USBx, ep->num, ep->is_in, len);
          pmabuffer = ep->pmaaddr1;

          /* Write the user buffer to USB PMA */
          USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
        }
        else
        {
          /* Set the Double buffer counter for pmabuffer0 */
          PCD_SET_EP_DBUF0_CNT(USBx, ep->num, ep->is_in, len);
          pmabuffer = ep->pmaaddr0;

          /* Write the user buffer to USB PMA */
          USB_WritePMA(USBx, ep->xfer_buff, pmabuffer, (uint16_t)len);
        }
      }
    }
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */

    PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_VALID);
  }
  else /* OUT endpoint */
  {
    if (ep->doublebuffer == 0U)
    {
      if ((ep->xfer_len == 0U) && (ep->type == EP_TYPE_CTRL))
      {
        /* This is a status out stage set the OUT_STATUS */
        PCD_SET_OUT_STATUS(USBx, ep->num);
      }
      else
      {
        PCD_CLEAR_OUT_STATUS(USBx, ep->num);
      }

      /* Multi packet transfer */
      if (ep->xfer_len > ep->maxpacket)
      {
        ep->xfer_len -= ep->maxpacket;
      }
      else
      {
        ep->xfer_len = 0U;
      }
    }
#if (USE_USB_DOUBLE_BUFFER == 1U)
    else
    {
      /* First Transfer Coming From HAL_PCD_EP_Receive & From ISR */
      /* Set the Double buffer counter */
      if (ep->type == EP_TYPE_BULK)
      {
        /* Coming from ISR */
        if (ep->xfer_count != 0U)
        {
          /* Update last value to check if there is blocking state */
          wEPVal = (uint16_t)PCD_GET_ENDPOINT(USBx, ep->num);

          /* Blocking State */
          if ((((wEPVal & USB_EP_DTOG_RX) != 0U) && ((wEPVal & USB_EP_DTOG_TX) != 0U)) ||
              (((wEPVal & USB_EP_DTOG_RX) == 0U) && ((wEPVal & USB_EP_DTOG_TX) == 0U)))
          {
            PCD_FREE_USER_BUFFER(USBx, ep->num, 0U);
          }
        }
      }
      /* iso out double */
      else if (ep->type == EP_TYPE_ISOC)
      {
        /* Only single packet transfer supported in FS */
        ep->xfer_len = 0U;
      }
      else
      {
        return HAL_ERROR;
      }
    }
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */

    PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
  }

  return HAL_OK;
}


/**
  * @brief  USB_EPSetStall set a stall condition over an EP
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPSetStall(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  if (ep->is_in != 0U)
  {
    PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_STALL);
  }
  else
  {
    PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_STALL);
  }

  return HAL_OK;
}

/**
  * @brief  USB_EPClearStall Clear a stall condition over an EP
  * @param  USBx Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPClearStall(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  if (ep->is_in != 0U)
  {
    PCD_CLEAR_TX_DTOG(USBx, ep->num);

    if (ep->type != EP_TYPE_ISOC)
    {
      /* Configure NAK status for the Endpoint */
      PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_NAK);
    }
  }
  else
  {
    PCD_CLEAR_RX_DTOG(USBx, ep->num);

    /* Configure VALID status for the Endpoint */
    PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_VALID);
  }

  return HAL_OK;
}

/**
   * @brief  USB_EPStoptXfer  Stop transfer on an EP
   * @param  USBx  usb device instance
   * @param  ep pointer to endpoint structure
   * @retval HAL status
   */
HAL_StatusTypeDef USB_EPStopXfer(USB_DRD_TypeDef *USBx, USB_DRD_EPTypeDef *ep)
{
  /* IN endpoint */
  if (ep->is_in == 1U)
  {
    if (ep->doublebuffer == 0U)
    {
      if (ep->type != EP_TYPE_ISOC)
      {
        /* Configure NAK status for the Endpoint */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_NAK);
      }
      else
      {
        /* Configure TX Endpoint to disabled state */
        PCD_SET_EP_TX_STATUS(USBx, ep->num, USB_EP_TX_DIS);
      }
    }
  }
  else /* OUT endpoint */
  {
    if (ep->doublebuffer == 0U)
    {
      if (ep->type != EP_TYPE_ISOC)
      {
        /* Configure NAK status for the Endpoint */
        PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_NAK);
      }
      else
      {
        /* Configure RX Endpoint to disabled state */
        PCD_SET_EP_RX_STATUS(USBx, ep->num, USB_EP_RX_DIS);
      }
    }
  }

  return HAL_OK;
}
#endif /* defined (HAL_PCD_MODULE_ENABLED) */

/**
  * @brief  USB_StopDevice Stop the usb device mode
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_StopDevice(USB_DRD_TypeDef *USBx)
{
  /* disable all interrupts and force USB reset */
  USBx->CNTR = USB_CNTR_USBRST;

  /* clear interrupt status register */
  USBx->ISTR = 0U;

  /* switch-off device */
  USBx->CNTR = (USB_CNTR_USBRST | USB_CNTR_PDWN);

  return HAL_OK;
}

/**
  * @brief  USB_SetDevAddress Stop the usb device mode
  * @param  USBx Selected device
  * @param  address new device address to be assigned
  *          This parameter can be a value from 0 to 255
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_SetDevAddress(USB_DRD_TypeDef *USBx, uint8_t address)
{
  if (address == 0U)
  {
    /* set device address and enable function */
    USBx->DADDR = USB_DADDR_EF;
  }

  return HAL_OK;
}

/**
  * @brief  USB_DevConnect Connect the USB device by enabling the pull-up/pull-down
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_DevConnect(USB_DRD_TypeDef *USBx)
{
  /* Enabling DP Pull-UP bit to Connect internal PU resistor on USB DP line */
  USBx->BCDR |= USB_BCDR_DPPU;

  return HAL_OK;
}

/**
  * @brief  USB_DevDisconnect Disconnect the USB device by disabling the pull-up/pull-down
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_DevDisconnect(USB_DRD_TypeDef *USBx)
{
  /* Disable DP Pull-Up bit to disconnect the Internal PU resistor on USB DP line */
  USBx->BCDR &= ~(USB_BCDR_DPPU);

  return HAL_OK;
}

/**
  * @brief  USB_ReadInterrupts return the global USB interrupt status
  * @param  USBx Selected device
  * @retval USB Global Interrupt status
  */
uint32_t USB_ReadInterrupts(USB_DRD_TypeDef const *USBx)
{
  uint32_t tmpreg;

  tmpreg = USBx->ISTR;
  return tmpreg;
}

/**
  * @brief  USB_ActivateRemoteWakeup : active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateRemoteWakeup(USB_DRD_TypeDef *USBx)
{
  USBx->CNTR |= USB_CNTR_L2RES;

  return HAL_OK;
}

/**
  * @brief  USB_DeActivateRemoteWakeup de-active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(USB_DRD_TypeDef *USBx)
{
  USBx->CNTR &= ~USB_CNTR_L2RES;

  return HAL_OK;
}

/**
  * @brief Copy a buffer from user memory area to packet memory area (PMA)
  * @param   USBx USB peripheral instance register address.
  * @param   pbUsrBuf pointer to user memory area.
  * @param   wPMABufAddr address into PMA.
  * @param   wNBytes no. of bytes to be copied.
  * @retval None
  */
void USB_WritePMA(USB_DRD_TypeDef const *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  UNUSED(USBx);
  uint32_t WrVal;
  uint32_t count;
  __IO uint32_t *pdwVal;
  uint32_t NbWords = ((uint32_t)wNBytes + 3U) >> 2U;
  /* Due to the PMA access 32bit only so the last non word data should be processed alone */
  uint16_t remaining_bytes = wNBytes % 4U;
  uint8_t *pBuf = pbUsrBuf;

  /* Check if there is a remaining byte */
  if (remaining_bytes != 0U)
  {
    NbWords--;
  }

  /* Get the PMA Buffer pointer */
  pdwVal = (__IO uint32_t *)(USB_DRD_PMAADDR + (uint32_t)wPMABufAddr);

  /* Write the Calculated Word into the PMA related Buffer */
  for (count = NbWords; count != 0U; count--)
  {
    *pdwVal = __UNALIGNED_UINT32_READ(pBuf);
    pdwVal++;
    /* Increment pBuf 4 Time as Word Increment */
    pBuf++;
    pBuf++;
    pBuf++;
    pBuf++;
  }

  /* When Number of data is not word aligned, write the remaining Byte */
  if (remaining_bytes != 0U)
  {
    WrVal = 0U;

    do
    {
      WrVal |= (uint32_t)(*(uint8_t *)pBuf) << (8U * count);
      count++;
      pBuf++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);

    *pdwVal = WrVal;
  }
}

/**
  * @brief Copy data from packet memory area (PMA) to user memory buffer
  * @param   USBx USB peripheral instance register address.
  * @param   pbUsrBuf pointer to user memory area.
  * @param   wPMABufAddr address into PMA.
  * @param   wNBytes no. of bytes to be copied.
  * @retval None
  */
void USB_ReadPMA(USB_DRD_TypeDef const *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  UNUSED(USBx);
  uint32_t count;
  uint32_t RdVal;
  __IO uint32_t *pdwVal;
  uint32_t NbWords = ((uint32_t)wNBytes + 3U) >> 2U;
  /*Due to the PMA access 32bit only so the last non word data should be processed alone */
  uint16_t remaining_bytes = wNBytes % 4U;
  uint8_t *pBuf = pbUsrBuf;

  /* Get the PMA Buffer pointer */
  pdwVal = (__IO uint32_t *)(USB_DRD_PMAADDR + (uint32_t)wPMABufAddr);

  /* if nbre of byte is not word aligned decrement the nbre of word*/
  if (remaining_bytes != 0U)
  {
    NbWords--;
  }

  /*Read the Calculated Word From the PMA related Buffer*/
  for (count = NbWords; count != 0U; count--)
  {
    __UNALIGNED_UINT32_WRITE(pBuf, *pdwVal);

    pdwVal++;
    pBuf++;
    pBuf++;
    pBuf++;
    pBuf++;
  }

  /*When Number of data is not word aligned, read the remaining byte*/
  if (remaining_bytes != 0U)
  {
    RdVal = *(__IO uint32_t *)pdwVal;

    do
    {
      *(uint8_t *)pBuf = (uint8_t)(RdVal >> (8U * (uint8_t)(count)));
      count++;
      pBuf++;
      remaining_bytes--;
    } while (remaining_bytes != 0U);
  }
}


/*------------------------------------------------------------------------*/
/*                                HOST API                                */
/*------------------------------------------------------------------------*/

/**
  * @brief  USB_HostInit Initializes the USB DRD controller registers
  *         for Host mode
  * @param  USBx Selected device
  * @param  cfg  pointer to a USB_DRD_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_HostInit(USB_DRD_TypeDef *USBx, USB_DRD_CfgTypeDef cfg)
{
  UNUSED(cfg);

  /* Clear All Pending Interrupt */
  USBx->ISTR = 0U;

  /* Disable all interrupts */
  USBx->CNTR &= ~(USB_CNTR_CTRM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM |
                  USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_DCON |
                  USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_L1REQM);

  /* Clear All Pending Interrupt */
  USBx->ISTR = 0U;

  /* Set the PullDown on the PHY */
  USBx->BCDR |= USB_BCDR_DPPD;

  /* Enable Global interrupt */
  USBx->CNTR |= (USB_CNTR_CTRM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM |
                 USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_DCON |
                 USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_L1REQM);

  return HAL_OK;
}


/**
  * @brief  USB_DRD_ResetPort : Reset Host Port
  * @param  USBx Selected device
  * @retval HAL status
  * @note (1)The application must wait at least 10 ms
  *   before clearing the reset bit.
  */
HAL_StatusTypeDef USB_ResetPort(USB_DRD_TypeDef *USBx)
{
  /* Force USB Reset */
  USBx->CNTR |= USB_CNTR_USBRST;
  HAL_Delay(100);
  /* Release USB Reset */
  USBx->CNTR &= ~USB_CNTR_USBRST;
  HAL_Delay(30);

  return HAL_OK;
}

/**
  * @brief  Return Host Core speed
  * @param  USBx Selected device
  * @retval speed Host speed
  *          This parameter can be one of these values
  *            @arg USB_DRD_SPEED_FS Full speed mode
  *            @arg USB_DRD_SPEED_LS Low speed mode
  */
uint32_t USB_GetHostSpeed(USB_DRD_TypeDef const *USBx)
{
  if ((USBx->ISTR & USB_ISTR_LS_DCONN) != 0U)
  {
    return USB_DRD_SPEED_LS;
  }
  else
  {
    return USB_DRD_SPEED_FS;
  }
}

/**
  * @brief  Return Host Current Frame number
  * @param  USBx Selected device
  * @retval current frame number
  */
uint32_t USB_GetCurrentFrame(USB_DRD_TypeDef const *USBx)
{
  return USBx->FNR & 0x7FFU;
}

/**
  * @brief  Set the channel Kind (Single/double buffer mode)
  * @param  USBx Selected device
  * @param  phy_ch_num Selected device
  * @param  db_state double state can be USB_DRD_XXX_DBUFF_ENBALE/USB_DRD_XXX_DBUFF_DISABLE
  * @retval HAL status
  */
HAL_StatusTypeDef USB_HC_DoubleBuffer(USB_DRD_TypeDef *USBx,
                                      uint8_t phy_ch_num, uint8_t db_state)
{
  uint32_t tmp;

  if ((db_state == USB_DRD_BULK_DBUFF_ENBALE) || (db_state == USB_DRD_ISOC_DBUFF_DISABLE))
  {
    tmp = (USB_DRD_GET_CHEP(USBx, phy_ch_num) | USB_CH_KIND) & USB_CHEP_DB_MSK;
  }
  else
  {
    tmp = USB_DRD_GET_CHEP(USBx, phy_ch_num) & (~USB_CH_KIND) & USB_CHEP_DB_MSK;
  }

  /* Set the device speed in case using HUB FS with device LS */
  USB_DRD_SET_CHEP(USBx, phy_ch_num, tmp);

  return HAL_OK;
}

/**
  * @brief  Initialize a host channel
  * @param  USBx Selected device
  * @param  phy_ch_num Channel number
  *         This parameter can be a value from 1 to 15
  * @param  epnum Endpoint number
  *          This parameter can be a value from 1 to 15
  * @param  dev_address Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed Current device speed
  *          This parameter can be one of these values:
  *          @arg USB_DRD_SPEED_FULL Full speed mode
  *          @arg USB_DRD_SPEED_LOW  Low speed mode
  * @param  ep_type Endpoint Type
  *          This parameter can be one of these values:
  *            @arg EP_TYPE_CTRL Control type
  *            @arg EP_TYPE_ISOC Isochronous type
  *            @arg EP_TYPE_BULK Bulk type
  *            @arg EP_TYPE_INTR Interrupt type
  * @param  mps Max Packet Size
  *          This parameter can be a value from 0 to 32K
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_Init(USB_DRD_TypeDef *USBx, uint8_t phy_ch_num,
                              uint8_t epnum, uint8_t dev_address, uint8_t speed,
                              uint8_t ep_type, uint16_t mps)
{
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t wChRegVal;
  uint32_t HostCoreSpeed;

  UNUSED(mps);

  wChRegVal = USB_DRD_GET_CHEP(USBx, phy_ch_num) & USB_CH_T_MASK;

  /* Initialize host Channel */
  switch (ep_type)
  {
    case EP_TYPE_CTRL:
      wChRegVal |= USB_EP_CONTROL;
      break;

    case EP_TYPE_BULK:
      wChRegVal |= USB_EP_BULK;
      break;

    case EP_TYPE_INTR:
      wChRegVal |= USB_EP_INTERRUPT;
      break;

    case EP_TYPE_ISOC:
      wChRegVal |= USB_EP_ISOCHRONOUS;
      break;

    default:
      ret = HAL_ERROR;
      break;
  }

  /* Clear device address, Endpoint number and Low Speed Endpoint fields */
  wChRegVal &= ~(USB_CHEP_DEVADDR |
                 USB_CHEP_ADDR |
                 USB_CHEP_LSEP |
                 USB_CHEP_NAK |
                 USB_CHEP_KIND |
                 USB_CHEP_ERRTX |
                 USB_CHEP_ERRRX |
                 (0xFU << 27));

  /* Set device address and Endpoint number associated to the channel */
  wChRegVal |= (((uint32_t)dev_address << USB_CHEP_DEVADDR_Pos) |
                ((uint32_t)epnum & 0x0FU));

  /* Get Host core Speed */
  HostCoreSpeed = USB_GetHostSpeed(USBx);

  /* Set the device speed in case using HUB FS with device LS */
  if ((speed == USB_DRD_SPEED_LS) && (HostCoreSpeed == USB_DRD_SPEED_FS))
  {
    wChRegVal |= USB_CHEP_LSEP;
  }

  /* Update the channel register value */
  USB_DRD_SET_CHEP(USBx, phy_ch_num, (wChRegVal | USB_CH_VTRX | USB_CH_VTTX));

  return ret;
}

/**
  * @brief  Start a transfer over a host channel
  * @param  USBx Selected device
  * @param  hc pointer to host channel structure
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_StartXfer(USB_DRD_TypeDef *USBx, USB_DRD_HCTypeDef *hc)
{
  uint32_t len;
  uint32_t phy_ch_num = (uint32_t)hc->phy_ch_num;
#if (USE_USB_DOUBLE_BUFFER == 1U)
  uint32_t ch_reg = USB_DRD_GET_CHEP(USBx, phy_ch_num);
#endif /* USE_USB_DOUBLE_BUFFER */

  if (hc->ch_dir == CH_IN_DIR)  /* In Channel */
  {
    /* Multi packet transfer */
    if (hc->xfer_len > hc->max_packet)
    {
      len = hc->max_packet;
    }
    else
    {
      len = hc->xfer_len;
    }

    if (hc->doublebuffer == 0U)
    {
      if ((hc->ep_type == EP_TYPE_BULK) ||
          (hc->ep_type == EP_TYPE_INTR))
      {
        USB_DRD_CLEAR_RX_DTOG(USBx, phy_ch_num);

        /* Set Data PID */
        if (hc->data_pid == HC_PID_DATA1)
        {
          USB_DRD_RX_DTOG(USBx, phy_ch_num);
        }
      }

      /* Set RX buffer count */
      USB_DRD_SET_CHEP_RX_CNT(USBx, phy_ch_num, len);
    }
#if (USE_USB_DOUBLE_BUFFER == 1U)
    else if (hc->ep_type == EP_TYPE_BULK)
    {
      /* Double buffer activated */
      if ((hc->xfer_len > hc->max_packet))
      {
        (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_BULK_DBUFF_ENBALE);

        /* Set the Double buffer counter */
        USB_DRD_SET_CHEP_DBUF0_CNT(USBx, phy_ch_num, 0U, len);
        USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, 0U, len);
      }
      else  /* Switch to single buffer mode */
      {
        (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_BULK_DBUFF_DISABLE);

        /* Set RX buffer count */
        USB_DRD_SET_CHEP_RX_CNT(USBx, phy_ch_num, len);
      }
    }
    else  /* Isochronous */
    {
      /* Set the Double buffer counter */
      USB_DRD_SET_CHEP_DBUF0_CNT(USBx, phy_ch_num, 0U, len);
      USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, 0U, len);
    }
#endif /* USE_USB_DOUBLE_BUFFER */

    /* Enable host channel */
    USB_DRD_SET_CHEP_RX_STATUS(USBx, phy_ch_num, USB_CH_RX_VALID);
  }
  else   /* Out Channel */
  {
    /* Multi packet transfer */
    if (hc->xfer_len > hc->max_packet)
    {
      len = hc->max_packet;
    }
    else
    {
      len = hc->xfer_len;
    }

    /* Configure and validate Tx endpoint */
    if (hc->doublebuffer == 0U)
    {
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaadress, (uint16_t)len);
      USB_DRD_SET_CHEP_TX_CNT(USBx, phy_ch_num, (uint16_t)len);

      /* SET PID SETUP  */
      if ((hc->data_pid) == HC_PID_SETUP)
      {
        USB_DRD_CHEP_TX_SETUP(USBx,  phy_ch_num);
      }

      if ((hc->ep_type == EP_TYPE_BULK) ||
          (hc->ep_type == EP_TYPE_INTR))
      {
        USB_DRD_CLEAR_TX_DTOG(USBx, phy_ch_num);

        /* Set Data PID */
        if (hc->data_pid == HC_PID_DATA1)
        {
          USB_DRD_TX_DTOG(USBx, phy_ch_num);
        }
      }
    }
#if (USE_USB_DOUBLE_BUFFER == 1U)
    else if (hc->ep_type == EP_TYPE_BULK)
    {
      (void)USB_HC_BULK_DB_StartXfer(USBx, hc, ch_reg, &len);
    }
    else
    {
      (void)USB_HC_ISO_DB_StartXfer(USBx, hc, len);
    }
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */

    /* Enable host channel */
    USB_DRD_SET_CHEP_TX_STATUS(USBx, hc->phy_ch_num, USB_CH_TX_VALID);
  }

  return HAL_OK;
}

#if (USE_USB_DOUBLE_BUFFER == 1U)
/**
  * @brief  Start Transfer of Channel isochronous out double buffer
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @param  len Transfer Length
  * @retval HAL state
  */
static HAL_StatusTypeDef USB_HC_ISO_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                 USB_DRD_HCTypeDef *hc,
                                                 uint32_t len)
{
  uint32_t phy_ch_num = (uint32_t)hc->phy_ch_num;

  /* check the DTOG_TX to determine in which buffer we should write */
  if ((USB_DRD_GET_CHEP(USBx, phy_ch_num) & USB_CH_DTOG_TX) != 0U)
  {
    USB_DRD_SET_CHEP_DBUF0_CNT(USBx, phy_ch_num, 1U, len);
    USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)len);
  }
  else
  {
    /* DTOGTX=0 */
    /* Set the Double buffer counter for pmabuffer0 */
    USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, 1U, len);
    USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr1, (uint16_t)len);
  }

  return HAL_OK;
}

/**
  * @brief  Start Transfer of Channel bulk out double buffer
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @param  ch_reg snapshot of the CHEPR register
  * @param  len Transfer Length
  * @retval HAL state
  */
static HAL_StatusTypeDef USB_HC_BULK_DB_StartXfer(USB_DRD_TypeDef *USBx,
                                                  USB_DRD_HCTypeDef *hc,
                                                  uint32_t ch_reg,
                                                  uint32_t *len)
{
  uint32_t phy_ch_num = (uint32_t)hc->phy_ch_num;

  /* -Double Buffer Mangement- */
  if (hc->xfer_len_db > hc->max_packet)
  {
    /* enable double buffer mode */
    (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_BULK_DBUFF_ENBALE);
    *len = hc->max_packet;
    hc->xfer_len_db -= *len;

    /* Prepare two buffer before enabling host */
    if ((ch_reg & USB_CH_DTOG_TX) == 0U)
    {
      /* Write Buffer0 */
      USB_DRD_SET_CHEP_DBUF0_CNT(USBx, phy_ch_num, 1U, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)*len);
    }
    else
    {
      /* Write Buffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, 1U, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr1, (uint16_t)*len);
    }

    hc->xfer_buff += *len;

    /* Multi packet transfer */
    if (hc->xfer_len_db > hc->max_packet)
    {
      hc->xfer_len_db -= *len;
    }
    else
    {
      *len = hc->xfer_len_db;
      hc->xfer_len_db = 0U;
    }

    if ((ch_reg & USB_CH_DTOG_TX) == 0U)
    {
      /* Write Buffer1 */
      USB_DRD_SET_CHEP_DBUF1_CNT(USBx, phy_ch_num, 1U, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr1, (uint16_t)*len);
    }
    else
    {
      /* Write Buffer0 */
      USB_DRD_SET_CHEP_DBUF0_CNT(USBx, phy_ch_num, 1U, (uint16_t)*len);
      USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)*len);
    }
  }
  else
  {
    /* Disable bulk double buffer mode */
    (void)USB_HC_DoubleBuffer(USBx, (uint8_t)phy_ch_num, USB_DRD_BULK_DBUFF_DISABLE);
    USB_WritePMA(USBx, hc->xfer_buff, hc->pmaaddr0, (uint16_t)*len);
    USB_DRD_SET_CHEP_TX_CNT(USBx, phy_ch_num, (uint16_t)*len);
  }

  return HAL_OK;
}
#endif /* (USE_USB_DOUBLE_BUFFER == 1U) */


/**
  * @brief  Halt a host channel in
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_IN_Halt(USB_DRD_TypeDef *USBx, uint8_t phy_ch)
{
  /* Set disable to Channel */
  USB_DRD_SET_CHEP_RX_STATUS(USBx, phy_ch, USB_CH_RX_DIS);

  return HAL_OK;
}


/**
  * @brief  Halt a host channel out
  * @param  USBx Selected device
  * @param  hc_num Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_OUT_Halt(USB_DRD_TypeDef *USBx, uint8_t phy_ch)
{
  /* Set disable to Channel */
  USB_DRD_SET_CHEP_TX_STATUS(USBx, phy_ch, USB_CH_TX_DIS);

  return HAL_OK;
}

/**
  * @brief  Stop Host Core
  * @param  USBx Selected device
  * @retval HAL state
  */
HAL_StatusTypeDef USB_StopHost(USB_DRD_TypeDef *USBx)
{
  USBx->ISTR &= ~(USB_ISTR_DIR | USB_ISTR_L1REQ |
                  USB_ISTR_ESOF | USB_ISTR_SOF |
                  USB_ISTR_RESET | USB_ISTR_DCON |
                  USB_ISTR_SUSP | USB_ISTR_WKUP |
                  USB_ISTR_ERR | USB_ISTR_PMAOVR |
                  USB_ISTR_CTR);

  /* Set PowerDown */
  USBx->CNTR |= USB_CNTR_PDWN;

  /* Force a Reset */
  USBx->CNTR |= USB_CNTR_USBRST;

  return HAL_OK;
}
#endif /* defined (USB_DRD_FS) */
/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) || defined (USB_DRD_FS) */
#endif /* defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED) */

/**
  * @}
  */
