/**
  ******************************************************************************
  * @file    stm32f7xx_hal_hcd.c
  * @author  MCD Application Team
  * @brief   HCD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
  [..]
    (#)Declare a HCD_HandleTypeDef handle structure, for example:
       HCD_HandleTypeDef  hhcd;

    (#)Fill parameters of Init structure in HCD handle

    (#)Call HAL_HCD_Init() API to initialize the HCD peripheral (Core, Host core, ...)

    (#)Initialize the HCD low level resources through the HAL_HCD_MspInit() API:
        (##) Enable the HCD/USB Low Level interface clock using the following macros
             (+++) __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
             (+++) __HAL_RCC_USB_OTG_HS_CLK_ENABLE(); (For High Speed Mode)
             (+++) __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE(); (For High Speed Mode)

        (##) Initialize the related GPIO clocks
        (##) Configure HCD pin-out
        (##) Configure HCD NVIC interrupt

    (#)Associate the Upper USB Host stack to the HAL HCD Driver:
        (##) hhcd.pData = phost;

    (#)Enable HCD transmission and reception:
        (##) HAL_HCD_Start();

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

/** @defgroup HCD HCD
  * @brief HCD HAL module driver
  * @{
  */

#ifdef HAL_HCD_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup HCD_Private_Functions HCD Private Functions
  * @{
  */
static void HCD_HC_IN_IRQHandler(HCD_HandleTypeDef *hhcd, uint8_t chnum);
static void HCD_HC_OUT_IRQHandler(HCD_HandleTypeDef *hhcd, uint8_t chnum);
static void HCD_RXQLVL_IRQHandler(HCD_HandleTypeDef *hhcd);
static void HCD_Port_IRQHandler(HCD_HandleTypeDef *hhcd);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HCD_Exported_Functions HCD Exported Functions
  * @{
  */

/** @defgroup HCD_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
          ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_Init(HCD_HandleTypeDef *hhcd)
{
  /* Check the HCD handle allocation */
  if(hhcd == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_HCD_ALL_INSTANCE(hhcd->Instance));

  if(hhcd->State == HAL_HCD_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hhcd->Lock = HAL_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_HCD_MspInit(hhcd);
  }

  hhcd->State = HAL_HCD_STATE_BUSY;

  /* Disable the Interrupts */
  __HAL_HCD_DISABLE(hhcd);

  /* Init the Core (common init.) */
  (void)USB_CoreInit(hhcd->Instance, hhcd->Init);

  /* Force Host Mode*/
  (void)USB_SetCurrentMode(hhcd->Instance, USB_HOST_MODE);

  /* Init Host */
  (void)USB_HostInit(hhcd->Instance, hhcd->Init);

  hhcd->State= HAL_HCD_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Initialize a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  epnum Endpoint number.
  *          This parameter can be a value from 1 to 15
  * @param  dev_address Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed Current device speed.
  *          This parameter can be one of these values:
  *            HCD_SPEED_HIGH: High speed mode,
  *            HCD_SPEED_FULL: Full speed mode,
  *            HCD_SPEED_LOW: Low speed mode
  * @param  ep_type Endpoint Type.
  *          This parameter can be one of these values:
  *            EP_TYPE_CTRL: Control type,
  *            EP_TYPE_ISOC: Isochronous type,
  *            EP_TYPE_BULK: Bulk type,
  *            EP_TYPE_INTR: Interrupt type
  * @param  mps Max Packet Size.
  *          This parameter can be a value from 0 to32K
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_HC_Init(HCD_HandleTypeDef *hhcd,
                                  uint8_t ch_num,
                                  uint8_t epnum,
                                  uint8_t dev_address,
                                  uint8_t speed,
                                  uint8_t ep_type,
                                  uint16_t mps)
{
  HAL_StatusTypeDef status;

  __HAL_LOCK(hhcd);
  hhcd->hc[ch_num].do_ping = 0U;
  hhcd->hc[ch_num].dev_addr = dev_address;
  hhcd->hc[ch_num].max_packet = mps;
  hhcd->hc[ch_num].ch_num = ch_num;
  hhcd->hc[ch_num].ep_type = ep_type;
  hhcd->hc[ch_num].ep_num = epnum & 0x7FU;

  if ((epnum & 0x80U) == 0x80U)
  {
    hhcd->hc[ch_num].ep_is_in = 1U;
  }
  else
  {
    hhcd->hc[ch_num].ep_is_in = 0U;
  }

  hhcd->hc[ch_num].speed = speed;

  status =  USB_HC_Init(hhcd->Instance,
                        ch_num,
                        epnum,
                        dev_address,
                        speed,
                        ep_type,
                        mps);
  __HAL_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  Halt a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_HC_Halt(HCD_HandleTypeDef *hhcd, uint8_t ch_num)
{
  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(hhcd);
  (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
  __HAL_UNLOCK(hhcd);

  return status;
}

/**
  * @brief  DeInitialize the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_DeInit(HCD_HandleTypeDef *hhcd)
{
  /* Check the HCD handle allocation */
  if(hhcd == NULL)
  {
    return HAL_ERROR;
  }

  hhcd->State = HAL_HCD_STATE_BUSY;

  /* DeInit the low level hardware */
  HAL_HCD_MspDeInit(hhcd);

  __HAL_HCD_DISABLE(hhcd);

  hhcd->State = HAL_HCD_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief  Initialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void  HAL_HCD_MspInit(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitialize the HCD MSP.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void  HAL_HCD_MspDeInit(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   HCD IO operation functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..] This subsection provides a set of functions allowing to manage the USB Host Data
    Transfer

@endverbatim
  * @{
  */

/**
  * @brief  Submit a new URB for processing.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  direction Channel number.
  *          This parameter can be one of these values:
  *           0 : Output / 1 : Input
  * @param  ep_type Endpoint Type.
  *          This parameter can be one of these values:
  *            EP_TYPE_CTRL: Control type/
  *            EP_TYPE_ISOC: Isochronous type/
  *            EP_TYPE_BULK: Bulk type/
  *            EP_TYPE_INTR: Interrupt type/
  * @param  token Endpoint Type.
  *          This parameter can be one of these values:
  *            0: HC_PID_SETUP / 1: HC_PID_DATA1
  * @param  pbuff pointer to URB data
  * @param  length Length of URB data
  * @param  do_ping activate do ping protocol (for high speed only).
  *          This parameter can be one of these values:
  *           0 : do ping inactive / 1 : do ping active
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_HC_SubmitRequest(HCD_HandleTypeDef *hhcd,
                                           uint8_t ch_num,
                                           uint8_t direction,
                                           uint8_t ep_type,
                                           uint8_t token,
                                           uint8_t* pbuff,
                                           uint16_t length,
                                           uint8_t do_ping)
{
  UNUSED(do_ping);

  hhcd->hc[ch_num].ep_is_in = direction;
  hhcd->hc[ch_num].ep_type  = ep_type;

  if(token == 0U)
  {
    hhcd->hc[ch_num].data_pid = HC_PID_SETUP;
  }
  else
  {
    hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
  }

  /* Manage Data Toggle */
  switch(ep_type)
  {
  case EP_TYPE_CTRL:
    if((token == 1U) && (direction == 0U)) /*send data */
    {
      if (length == 0U)
      { /* For Status OUT stage, Length==0, Status Out PID = 1 */
        hhcd->hc[ch_num].toggle_out = 1U;
      }

      /* Set the Data Toggle bit as per the Flag */
      if (hhcd->hc[ch_num].toggle_out == 0U)
      { /* Put the PID 0 */
        hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
      }
      else
      { /* Put the PID 1 */
        hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
      }
    }
    break;

  case EP_TYPE_BULK:
    if(direction == 0U)
    {
      /* Set the Data Toggle bit as per the Flag */
      if ( hhcd->hc[ch_num].toggle_out == 0U)
      { /* Put the PID 0 */
        hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
      }
      else
      { /* Put the PID 1 */
        hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
      }
    }
    else
    {
      if( hhcd->hc[ch_num].toggle_in == 0U)
      {
        hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
      }
      else
      {
        hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
      }
    }

    break;
  case EP_TYPE_INTR:
    if(direction == 0U)
    {
      /* Set the Data Toggle bit as per the Flag */
      if ( hhcd->hc[ch_num].toggle_out == 0U)
      { /* Put the PID 0 */
        hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
      }
      else
      { /* Put the PID 1 */
        hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
      }
    }
    else
    {
      if( hhcd->hc[ch_num].toggle_in == 0U)
      {
        hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
      }
      else
      {
        hhcd->hc[ch_num].data_pid = HC_PID_DATA1;
      }
    }
    break;

  case EP_TYPE_ISOC:
    hhcd->hc[ch_num].data_pid = HC_PID_DATA0;
    break;

  default:
    break;
  }

  hhcd->hc[ch_num].xfer_buff = pbuff;
  hhcd->hc[ch_num].xfer_len  = length;
  hhcd->hc[ch_num].urb_state = URB_IDLE;
  hhcd->hc[ch_num].xfer_count = 0U;
  hhcd->hc[ch_num].ch_num = ch_num;
  hhcd->hc[ch_num].state = HC_IDLE;

  return USB_HC_StartXfer(hhcd->Instance, &hhcd->hc[ch_num], (uint8_t)hhcd->Init.dma_enable);
}

/**
  * @brief  Handle HCD interrupt request.
  * @param  hhcd HCD handle
  * @retval None
  */
void HAL_HCD_IRQHandler(HCD_HandleTypeDef *hhcd)
{
  USB_OTG_GlobalTypeDef *USBx = hhcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i, interrupt;

  /* Ensure that we are in device mode */
  if (USB_GetMode(hhcd->Instance) == USB_OTG_MODE_HOST)
  {
    /* Avoid spurious interrupt */
    if(__HAL_HCD_IS_INVALID_INTERRUPT(hhcd))
    {
      return;
    }

    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_PXFR_INCOMPISOOUT))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_OTG_GINTSTS_PXFR_INCOMPISOOUT);
    }

    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_IISOIXFR))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_OTG_GINTSTS_IISOIXFR);
    }

    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_PTXFE))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_OTG_GINTSTS_PTXFE);
    }

    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_MMIS))
    {
      /* Incorrect mode, acknowledge the interrupt */
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_OTG_GINTSTS_MMIS);
    }

    /* Handle Host Disconnect Interrupts */
    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_DISCINT))
    {

      /* Cleanup HPRT */
      USBx_HPRT0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |\
        USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG );

      /* Handle Host Port Interrupts */
      HAL_HCD_Disconnect_Callback(hhcd);
      (void)USB_InitFSLSPClkSel(hhcd->Instance, HCFG_48_MHZ);
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_OTG_GINTSTS_DISCINT);
    }

    /* Handle Host Port Interrupts */
    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_HPRTINT))
    {
      HCD_Port_IRQHandler (hhcd);
    }

    /* Handle Host SOF Interrupts */
    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_SOF))
    {
      HAL_HCD_SOF_Callback(hhcd);
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_OTG_GINTSTS_SOF);
    }

    /* Handle Host channel Interrupts */
    if(__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_HCINT))
    {
      interrupt = USB_HC_ReadInterrupt(hhcd->Instance);
      for (i = 0U; i < hhcd->Init.Host_channels; i++)
      {
        if ((interrupt & (1UL << (i & 0xFU))) != 0U)
        {
          if ((USBx_HC(i)->HCCHAR & USB_OTG_HCCHAR_EPDIR) == USB_OTG_HCCHAR_EPDIR)
          {
            HCD_HC_IN_IRQHandler(hhcd, (uint8_t)i);
          }
          else
          {
            HCD_HC_OUT_IRQHandler (hhcd, (uint8_t)i);
          }
        }
      }
      __HAL_HCD_CLEAR_FLAG(hhcd, USB_OTG_GINTSTS_HCINT);
    }

    /* Handle Rx Queue Level Interrupts */
    if((__HAL_HCD_GET_FLAG(hhcd, USB_OTG_GINTSTS_RXFLVL)) != 0U)
    {
      USB_MASK_INTERRUPT(hhcd->Instance, USB_OTG_GINTSTS_RXFLVL);

      HCD_RXQLVL_IRQHandler (hhcd);

      USB_UNMASK_INTERRUPT(hhcd->Instance, USB_OTG_GINTSTS_RXFLVL);
    }
  }
}

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_SOF_Callback could be implemented in the user file
   */
}

/**
  * @brief Connection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_Connect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_Disconnect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Port Enabled  Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_Disconnect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Port Disabled  Event callback.
  * @param  hhcd HCD handle
  * @retval None
  */
__weak void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_Disconnect_Callback could be implemented in the user file
   */
}

/**
  * @brief  Notify URB state change callback.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  urb_state:
  *          This parameter can be one of these values:
  *            URB_IDLE/
  *            URB_DONE/
  *            URB_NOTREADY/
  *            URB_NYET/
  *            URB_ERROR/
  *            URB_STALL/
  * @retval None
  */
__weak void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum, HCD_URBStateTypeDef urb_state)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhcd);
  UNUSED(chnum);
  UNUSED(urb_state);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HCD_HC_NotifyURBChange_Callback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group3 Peripheral Control functions
 *  @brief   Management functions
 *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the HCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_Start(HCD_HandleTypeDef *hhcd)
{
  __HAL_LOCK(hhcd);
  __HAL_HCD_ENABLE(hhcd);
  (void)USB_DriveVbus(hhcd->Instance, 1U);
  __HAL_UNLOCK(hhcd);
  return HAL_OK;
}

/**
  * @brief  Stop the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_HCD_Stop(HCD_HandleTypeDef *hhcd)
{
  __HAL_LOCK(hhcd);
  (void)USB_StopHost(hhcd->Instance);
  __HAL_UNLOCK(hhcd);
  return HAL_OK;
}

/**
  * @brief  Reset the host port.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HCD_ResetPort(HCD_HandleTypeDef *hhcd)
{
  return (USB_ResetPort(hhcd->Instance));
}

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group4 Peripheral State functions
 *  @brief   Peripheral State functions
 *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the HCD handle state.
  * @param  hhcd HCD handle
  * @retval HAL state
  */
HCD_StateTypeDef HAL_HCD_GetState(HCD_HandleTypeDef *hhcd)
{
  return hhcd->State;
}

/**
  * @brief  Return  URB state for a channel.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval URB state.
  *          This parameter can be one of these values:
  *            URB_IDLE/
  *            URB_DONE/
  *            URB_NOTREADY/
  *            URB_NYET/
  *            URB_ERROR/
  *            URB_STALL
  */
HCD_URBStateTypeDef HAL_HCD_HC_GetURBState(HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  return hhcd->hc[chnum].urb_state;
}


/**
  * @brief  Return the last host transfer size.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval last transfer size in byte
  */
uint32_t HAL_HCD_HC_GetXferCount(HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  return hhcd->hc[chnum].xfer_count;
}

/**
  * @brief  Return the Host Channel state.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval Host channel state
  *          This parameter can be one of these values:
  *            HC_IDLE/
  *            HC_XFRC/
  *            HC_HALTED/
  *            HC_NYET/
  *            HC_NAK/
  *            HC_STALL/
  *            HC_XACTERR/
  *            HC_BBLERR/
  *            HC_DATATGLERR
  */
HCD_HCStateTypeDef  HAL_HCD_HC_GetState(HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  return hhcd->hc[chnum].state;
}

/**
  * @brief  Return the current Host frame number.
  * @param  hhcd HCD handle
  * @retval Current Host frame number
  */
uint32_t HAL_HCD_GetCurrentFrame(HCD_HandleTypeDef *hhcd)
{
  return (USB_GetCurrentFrame(hhcd->Instance));
}

/**
  * @brief  Return the Host enumeration speed.
  * @param  hhcd HCD handle
  * @retval Enumeration speed
  */
uint32_t HAL_HCD_GetCurrentSpeed(HCD_HandleTypeDef *hhcd)
{
  return (USB_GetHostSpeed(hhcd->Instance));
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup HCD_Private_Functions
  * @{
  */
/**
  * @brief  Handle Host Channel IN interrupt requests.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_HC_IN_IRQHandler (HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  USB_OTG_GlobalTypeDef *USBx = hhcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t ch_num = (uint32_t)chnum;

  uint32_t tmpreg;

  if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_AHBERR) == USB_OTG_HCINT_AHBERR)
  {
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_AHBERR);
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_ACK) == USB_OTG_HCINT_ACK)
  {
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_ACK);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_STALL) == USB_OTG_HCINT_STALL)
  {
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    hhcd->hc[ch_num].state = HC_STALL;
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_NAK);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_STALL);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_DTERR) == USB_OTG_HCINT_DTERR)
  {
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_NAK);
    hhcd->hc[ch_num].state = HC_DATATGLERR;
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_DTERR);
  }
  else
  {
    /* ... */
  }

  if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_FRMOR) == USB_OTG_HCINT_FRMOR)
  {
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_FRMOR);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_XFRC) == USB_OTG_HCINT_XFRC)
  {
    if (hhcd->Init.dma_enable != 0U)
    {
      hhcd->hc[ch_num].xfer_count = hhcd->hc[ch_num].xfer_len - \
                               (USBx_HC(ch_num)->HCTSIZ & USB_OTG_HCTSIZ_XFRSIZ);
    }

    hhcd->hc[ch_num].state = HC_XFRC;
    hhcd->hc[ch_num].ErrCnt = 0U;
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_XFRC);

    if ((hhcd->hc[ch_num].ep_type == EP_TYPE_CTRL)||
        (hhcd->hc[ch_num].ep_type == EP_TYPE_BULK))
    {
      __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
      (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
      __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_NAK);
    }
    else if(hhcd->hc[ch_num].ep_type == EP_TYPE_INTR)
    {
      USBx_HC(ch_num)->HCCHAR |= USB_OTG_HCCHAR_ODDFRM;
      hhcd->hc[ch_num].urb_state = URB_DONE;
      HAL_HCD_HC_NotifyURBChange_Callback(hhcd, (uint8_t)ch_num, hhcd->hc[ch_num].urb_state);
    }
    else
    {
      /* ... */
    }
    hhcd->hc[ch_num].toggle_in ^= 1U;

  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_CHH) == USB_OTG_HCINT_CHH)
  {
    __HAL_HCD_MASK_HALT_HC_INT(ch_num);

    if(hhcd->hc[ch_num].state == HC_XFRC)
    {
      hhcd->hc[ch_num].urb_state  = URB_DONE;
    }
    else if (hhcd->hc[ch_num].state == HC_STALL)
    {
      hhcd->hc[ch_num].urb_state  = URB_STALL;
    }
    else if((hhcd->hc[ch_num].state == HC_XACTERR) ||
            (hhcd->hc[ch_num].state == HC_DATATGLERR))
    {
      hhcd->hc[ch_num].ErrCnt++;
      if(hhcd->hc[ch_num].ErrCnt > 3U)
      {
        hhcd->hc[ch_num].ErrCnt = 0U;
        hhcd->hc[ch_num].urb_state = URB_ERROR;
      }
      else
      {
        hhcd->hc[ch_num].urb_state = URB_NOTREADY;
      }

      /* re-activate the channel  */
      tmpreg = USBx_HC(ch_num)->HCCHAR;
      tmpreg &= ~USB_OTG_HCCHAR_CHDIS;
      tmpreg |= USB_OTG_HCCHAR_CHENA;
      USBx_HC(ch_num)->HCCHAR = tmpreg;
    }
    else if (hhcd->hc[ch_num].state == HC_NAK)
    {
      hhcd->hc[ch_num].urb_state  = URB_NOTREADY;
      /* re-activate the channel  */
      tmpreg = USBx_HC(ch_num)->HCCHAR;
      tmpreg &= ~USB_OTG_HCCHAR_CHDIS;
      tmpreg |= USB_OTG_HCCHAR_CHENA;
      USBx_HC(ch_num)->HCCHAR = tmpreg;
    }
    else
    {
      /* ... */
    }
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_CHH);
    HAL_HCD_HC_NotifyURBChange_Callback(hhcd, (uint8_t)ch_num, hhcd->hc[ch_num].urb_state);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_TXERR) == USB_OTG_HCINT_TXERR)
  {
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    hhcd->hc[ch_num].ErrCnt++;
    hhcd->hc[ch_num].state = HC_XACTERR;
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_TXERR);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_NAK) == USB_OTG_HCINT_NAK)
  {
    if(hhcd->hc[ch_num].ep_type == EP_TYPE_INTR)
    {
      hhcd->hc[ch_num].ErrCnt = 0U;
      __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
      (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    }
    else if ((hhcd->hc[ch_num].ep_type == EP_TYPE_CTRL)||
             (hhcd->hc[ch_num].ep_type == EP_TYPE_BULK))
    {
       hhcd->hc[ch_num].ErrCnt = 0U;
       if (hhcd->Init.dma_enable == 0U)
       {
         hhcd->hc[ch_num].state = HC_NAK;
         __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
         (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
       }
    }
    else
    {
      /* ... */
    }
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_NAK);
  }
  else
  {
    /* ... */
  }
}

/**
  * @brief  Handle Host Channel OUT interrupt requests.
  * @param  hhcd HCD handle
  * @param  chnum Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval none
  */
static void HCD_HC_OUT_IRQHandler (HCD_HandleTypeDef *hhcd, uint8_t chnum)
{
  USB_OTG_GlobalTypeDef *USBx = hhcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t ch_num = (uint32_t)chnum;
  uint32_t tmpreg;

  if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_AHBERR) == USB_OTG_HCINT_AHBERR)
  {
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_AHBERR);
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_ACK) == USB_OTG_HCINT_ACK)
  {
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_ACK);

    if( hhcd->hc[ch_num].do_ping == 1U)
    {
      hhcd->hc[ch_num].do_ping = 0U;
      hhcd->hc[ch_num].urb_state  = URB_NOTREADY;
      __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
      (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    }
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_NYET) == USB_OTG_HCINT_NYET)
  {
    hhcd->hc[ch_num].state = HC_NYET;
    hhcd->hc[ch_num].do_ping = 1U;
    hhcd->hc[ch_num].ErrCnt= 0U;
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_NYET);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_FRMOR) == USB_OTG_HCINT_FRMOR)
  {
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_FRMOR);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_XFRC) == USB_OTG_HCINT_XFRC)
  {
    hhcd->hc[ch_num].ErrCnt = 0U;
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_XFRC);
    hhcd->hc[ch_num].state = HC_XFRC;
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_STALL) == USB_OTG_HCINT_STALL)
  {
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_STALL);
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    hhcd->hc[ch_num].state = HC_STALL;
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_NAK) == USB_OTG_HCINT_NAK)
  {
    hhcd->hc[ch_num].ErrCnt = 0U;
    hhcd->hc[ch_num].state = HC_NAK;

    if (hhcd->hc[ch_num].do_ping == 0U)
    {
      if (hhcd->hc[ch_num].speed == HCD_SPEED_HIGH)
      {
        hhcd->hc[ch_num].do_ping = 1U;
      }
    }

    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_NAK);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_TXERR) == USB_OTG_HCINT_TXERR)
  {
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    hhcd->hc[ch_num].state = HC_XACTERR;
     __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_TXERR);
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_DTERR) == USB_OTG_HCINT_DTERR)
  {
    __HAL_HCD_UNMASK_HALT_HC_INT(ch_num);
    (void)USB_HC_Halt(hhcd->Instance, (uint8_t)ch_num);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_NAK);
    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_DTERR);
    hhcd->hc[ch_num].state = HC_DATATGLERR;
  }
  else if ((USBx_HC(ch_num)->HCINT & USB_OTG_HCINT_CHH) == USB_OTG_HCINT_CHH)
  {
    __HAL_HCD_MASK_HALT_HC_INT(ch_num);

    if (hhcd->hc[ch_num].state == HC_XFRC)
    {
      hhcd->hc[ch_num].urb_state  = URB_DONE;
      if (hhcd->hc[ch_num].ep_type == EP_TYPE_BULK)
      {
        hhcd->hc[ch_num].toggle_out ^= 1U;
      }
    }
    else if (hhcd->hc[ch_num].state == HC_NAK)
    {
      hhcd->hc[ch_num].urb_state = URB_NOTREADY;
    }
    else if (hhcd->hc[ch_num].state == HC_NYET)
    {
      hhcd->hc[ch_num].urb_state  = URB_NOTREADY;
    }
    else if (hhcd->hc[ch_num].state == HC_STALL)
    {
      hhcd->hc[ch_num].urb_state  = URB_STALL;
    }
    else if ((hhcd->hc[ch_num].state == HC_XACTERR) ||
            (hhcd->hc[ch_num].state == HC_DATATGLERR))
    {
      hhcd->hc[ch_num].ErrCnt++;
      if (hhcd->hc[ch_num].ErrCnt > 3U)
      {
        hhcd->hc[ch_num].ErrCnt = 0U;
        hhcd->hc[ch_num].urb_state = URB_ERROR;
      }
      else
      {
        hhcd->hc[ch_num].urb_state = URB_NOTREADY;
      }

      /* re-activate the channel  */
      tmpreg = USBx_HC(ch_num)->HCCHAR;
      tmpreg &= ~USB_OTG_HCCHAR_CHDIS;
      tmpreg |= USB_OTG_HCCHAR_CHENA;
      USBx_HC(ch_num)->HCCHAR = tmpreg;
    }
    else
    {
      /* ... */
    }

    __HAL_HCD_CLEAR_HC_INT(ch_num, USB_OTG_HCINT_CHH);
    HAL_HCD_HC_NotifyURBChange_Callback(hhcd, (uint8_t)ch_num, hhcd->hc[ch_num].urb_state);
  }
  else
  {
     /* ... */
  }
}

/**
  * @brief  Handle Rx Queue Level interrupt requests.
  * @param  hhcd HCD handle
  * @retval none
  */
static void HCD_RXQLVL_IRQHandler (HCD_HandleTypeDef *hhcd)
{
  USB_OTG_GlobalTypeDef *USBx = hhcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t pktsts;
  uint32_t pktcnt;
  uint32_t temp;
  uint32_t tmpreg;
  uint32_t ch_num;

  temp = hhcd->Instance->GRXSTSP;
  ch_num = temp & USB_OTG_GRXSTSP_EPNUM;
  pktsts = (temp & USB_OTG_GRXSTSP_PKTSTS) >> 17;
  pktcnt = (temp & USB_OTG_GRXSTSP_BCNT) >> 4;

  switch (pktsts)
  {
  case GRXSTS_PKTSTS_IN:
    /* Read the data into the host buffer. */
    if ((pktcnt > 0U) && (hhcd->hc[ch_num].xfer_buff != (void  *)0))
    {
      (void)USB_ReadPacket(hhcd->Instance, hhcd->hc[ch_num].xfer_buff, (uint16_t)pktcnt);

      /*manage multiple Xfer */
      hhcd->hc[ch_num].xfer_buff += pktcnt;
      hhcd->hc[ch_num].xfer_count  += pktcnt;

      if((USBx_HC(ch_num)->HCTSIZ & USB_OTG_HCTSIZ_PKTCNT) > 0U)
      {
        /* re-activate the channel when more packets are expected */
        tmpreg = USBx_HC(ch_num)->HCCHAR;
        tmpreg &= ~USB_OTG_HCCHAR_CHDIS;
        tmpreg |= USB_OTG_HCCHAR_CHENA;
        USBx_HC(ch_num)->HCCHAR = tmpreg;
        hhcd->hc[ch_num].toggle_in ^= 1U;
      }
    }
    break;

  case GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
    break;

  case GRXSTS_PKTSTS_IN_XFER_COMP:
  case GRXSTS_PKTSTS_CH_HALTED:
  default:
    break;
  }
}

/**
  * @brief  Handle Host Port interrupt requests.
  * @param  hhcd HCD handle
  * @retval None
  */
static void HCD_Port_IRQHandler (HCD_HandleTypeDef *hhcd)
{
  USB_OTG_GlobalTypeDef *USBx = hhcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  __IO uint32_t hprt0, hprt0_dup;

  /* Handle Host Port Interrupts */
  hprt0 = USBx_HPRT0;
  hprt0_dup = USBx_HPRT0;

  hprt0_dup &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |\
                 USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

  /* Check whether Port Connect detected */
  if((hprt0 & USB_OTG_HPRT_PCDET) == USB_OTG_HPRT_PCDET)
  {
    if((hprt0 & USB_OTG_HPRT_PCSTS) == USB_OTG_HPRT_PCSTS)
    {
      USB_MASK_INTERRUPT(hhcd->Instance, USB_OTG_GINTSTS_DISCINT);
      HAL_HCD_Connect_Callback(hhcd);
    }
    hprt0_dup  |= USB_OTG_HPRT_PCDET;
  }

  /* Check whether Port Enable Changed */
  if((hprt0 & USB_OTG_HPRT_PENCHNG) == USB_OTG_HPRT_PENCHNG)
  {
    hprt0_dup |= USB_OTG_HPRT_PENCHNG;

    if((hprt0 & USB_OTG_HPRT_PENA) == USB_OTG_HPRT_PENA)
    {
      if(hhcd->Init.phy_itface  == USB_OTG_EMBEDDED_PHY)
      {
        if ((hprt0 & USB_OTG_HPRT_PSPD) == (HPRT0_PRTSPD_LOW_SPEED << 17))
        {
          (void)USB_InitFSLSPClkSel(hhcd->Instance, HCFG_6_MHZ);
        }
        else
        {
          (void)USB_InitFSLSPClkSel(hhcd->Instance, HCFG_48_MHZ);
        }
      }
      else
      {
        if(hhcd->Init.speed == HCD_SPEED_FULL)
        {
          USBx_HOST->HFIR = 60000U;
        }
      }

      HAL_HCD_PortEnabled_Callback(hhcd);
      HAL_HCD_Connect_Callback(hhcd);
    }
    else
    {
      HAL_HCD_PortDisabled_Callback(hhcd);

      /* Cleanup HPRT */
      USBx_HPRT0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |\
        USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG );

      USB_UNMASK_INTERRUPT(hhcd->Instance, USB_OTG_GINTSTS_DISCINT);
    }
  }

  /* Check for an overcurrent */
  if((hprt0 & USB_OTG_HPRT_POCCHNG) == USB_OTG_HPRT_POCCHNG)
  {
    hprt0_dup |= USB_OTG_HPRT_POCCHNG;
  }

  /* Clear Port Interrupts */
  USBx_HPRT0 = hprt0_dup;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_HCD_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
