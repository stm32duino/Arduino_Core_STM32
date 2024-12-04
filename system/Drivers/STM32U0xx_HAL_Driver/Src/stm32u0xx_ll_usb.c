/**
  ******************************************************************************
  * @file    stm32u0xx_ll_usb.c
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
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32u0xx_hal.h"

/** @addtogroup STM32U0xx_LL_USB_DRIVER
  * @{
  */

#if defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED)
#if defined (USB_DRD_FS)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static HAL_StatusTypeDef USB_CoreReset(USB_DRD_TypeDef *USBx);

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


/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (USB_DRD_FS) */
#endif /* defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED) */

/**
  * @}
  */
