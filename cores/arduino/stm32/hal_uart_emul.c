/**
  ******************************************************************************
  * @file    hal_uart_emul.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Adaptation from stm32f4xx_hal_uart_emul.c
  *          UART Emulation HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter (UART Emulation):
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
  @verbatim
   ==============================================================================
                        ##### How to use this driver #####
   ==============================================================================
  [..]
    The UART Emulation HAL driver can be used as follows:

    (#) Declare a UART_Emul_HandleTypeDef handle structure.

    (#) Initialize the UART Emulation low level resources by implementing the HAL_UART_Emul_MspInit() API:
        (##) Enable the UART_EMUL clock
        (##) UART Emulation port declaration
            (+++) UART pins configuration: TxPinNumber and RxPinNumber
            (+++) Enable the clock for the GPIOs

    (#) Program the Baud Rate, Word Length, Stop Bit, Parity,
         and Mode(Receiver/Transmitter) in the huart Emul Init structure.

    (#) Initialize the UART Emulation registers software by calling the HAL_UART_Emul_Init() API.

        -@- The specific UART Emulaion Handle (Transmission complete, Reception complete
            and Transfer Error) will be managed using the macros HAL_UART_Emul_TxCpltCallback(),
						HAL_UART_Emul_RxCpltCallback() and __HAL_UART_Emul_TranferError() inside the transmit
            and receive process.

        -@- These API's(HAL_UART_Emul_Init() configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
     				by calling the customed HAL_UART_Emul_MspInit() API.

    (#) Three modes of operations are available within this driver:

     *** UART Emulation mode IO operation ***
     ===================================
     [..]
       (+) Send an amount of data in non blocking mode (IT) using HAL_UART_Emul_Transmit()
       (+) At transmission end of transfer HAL_UART_Emul_TxCpltCallback is executed and user can
            add his own code by customization of function pointer HAL_UART_Emul_TxCpltCallback
       (+) Receive an amount of data in non blocking mode (IT) using HAL_UART_Emul_Receive()

       (+) At reception end of transfer HAL_UART_Emul_RxCpltCallback is executed and user can
            add his own code by customization of function pointer HAL_UART_Emul_RxCpltCallback
       (+) In case of transfer Error, HAL_UART_ErrorCallback() function is executed and user can
            add his own code by customization of function pointer HAL_UART_Emul_ErrorCallback

     *** UART Emulation HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in UART Emulation HAL driver.

      (+) __HAL_UART_EMUL_GET_FLAG : Checks whether the specified UART Emulation flag is set or not
      (+) __HAL_UART_EMUL_CLEAR_FLAG : Clears the specified UART Emulation pending flag
      (+) __HAL_UART_EMUL_SET_FLAG : Set the specified UART Emulation flag

     [..]
       (@) You can refer to the UART Emulation HAL driver header file for more useful macros

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#if defined(TIM1_BASE) && defined(UART_EMUL_RX) && defined(UART_EMUL_TX)
/* Includes ------------------------------------------------------------------*/
#include "hal_uart_emul.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup UART_EMUL_HAL_Driver
  * @brief HAL UART Emulation module driver
  * @{
 */
//#ifdef HAL_UART_EMUL_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* DMA Handle declaration */
static DMA_HandleTypeDef  hdma_tx;
static DMA_HandleTypeDef  hdma_rx;
/* Timer handler declaration */
static TIM_HandleTypeDef  TimHandle;

/* UART Emulation Handle */
static UART_Emul_HandleTypeDef      *huart_emul;

/* First Buffer for format data in reception mode */
static uint32_t *pFirstBuffer_Rx[RX_BUFFER_SIZE];

/* Second Buffer for format data in reception mode */
static uint32_t *pSecondBuffer_Rx[RX_BUFFER_SIZE];

/* First Buffer for format data in transmission mode */
static uint32_t *pFirstBuffer_Tx[TX_BUFFER_SIZE];

/* Second Buffer for format data in transmission mode */
static uint32_t *pSecondBuffer_Tx[TX_BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void UART_Emul_SetConfig (UART_Emul_HandleTypeDef *huart);
static void UART_Emul_SetConfig_DMATx(void);
static void UART_Emul_SetConfig_DMARx(void);
static void UART_Emul_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void UART_Emul_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void UART_Emul_DMAError(DMA_HandleTypeDef *hdma);
static void UART_Emul_TransmitFrame(UART_Emul_HandleTypeDef *huart);
static void UART_Emul_ReceiveFrame(UART_Emul_HandleTypeDef *huart, uint32_t *pData);
static void UART_Emul_TransmitFormatFrame(UART_Emul_HandleTypeDef *huart , uint8_t pData, uint32_t *pBuffer_Tx);
static uint8_t UART_Emul_ReceiveFormatFrame(UART_Emul_HandleTypeDef *huart, uint32_t *pBuffer, uint8_t pFrame);


/* Private functions ---------------------------------------------------------*/

/** @defgroup UART_Private_Functions
  * @{
  */

/** @defgroup UART_Emulation_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    This subsection provides a set of functions allowing to initialize the UART Emulation
    in asynchronous mode.
      (+) For the asynchronous mode only these parameters can be configured:
        (++) Baud Rate (4800 up 115200)
        (++) Word Length (5 bit up 9 bit)
        (++) Stop Bit (1 or 2 stop bit)
        (++) Parity: If the parity is enabled, then the MSB bit of the data to be transmitted
              				is changed by the parity bit.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the UART Emulation mode according to the specified parameters in
  *         the UART_Emul_InitTypeDef and create the associated handle.
  * @param  huart: UART Emulation handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Emul_Init(UART_Emul_HandleTypeDef *huart)
{
  /* Check the UART handle allocation */
  if (huart == NULL)
  {
    return HAL_ERROR;
  }

  if (huart->State == HAL_UART_EMUL_STATE_RESET)
  {
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_UART_Emul_MspInit(huart);
  }

  /* Get Structure for uart emul Handle */
  huart_emul = huart;

  /* Set the TIM state */
  huart->State = HAL_UART_EMUL_STATE_BUSY;

  /* Set the UART Emulation Communication parameters */
  UART_Emul_SetConfig(huart);

  /* Initialize the UART Emulation state */
  huart->ErrorCode = HAL_UART_EMUL_ERROR_NONE;
  huart->State = HAL_UART_EMUL_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the UART Emulation .
  * @param  huart: UART Emulation handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Emul_DeInit(UART_Emul_HandleTypeDef *huart)
{
  /* Check the UART Emulation handle allocation */
  if (huart == NULL)
  {
    return HAL_ERROR;
  }

  huart->State = HAL_UART_EMUL_STATE_BUSY;

  /* DeInit the low level hardware */
  HAL_UART_Emul_MspDeInit(huart);

  huart->ErrorCode = HAL_UART_EMUL_ERROR_NONE;
  huart->State = HAL_UART_EMUL_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief  Initializes the UART Emulation MSP.
  * @param  huart: UART Emulation Handle
  * @retval None
  */
__weak void HAL_UART_Emul_MspInit(UART_Emul_HandleTypeDef *huart)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_UART_Emul_MspInit could be implemented in the user file
   */
}

/**
 * @brief  UART Emulation MSP DeInit.
 * @param  huart: UART Emulation handle
 * @retval None
 */
__weak void HAL_UART_Emul_MspDeInit(UART_Emul_HandleTypeDef *huart)
{
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_Emul_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup UART_Emulation_Group2 IO operation functions
  *  @brief UART Emulation Transmit and Receive functions
  *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
   This subsection provides a set of functions allowing to manage the UART asynchronous
   and Half duplex data transfers.

    (#) There is one mode of transfer:
       (++) Non-Blocking mode: The communication is performed using DMA,
            this APIs returns the HAL status.
            The end of the data processing will be indicated through the
            DMA IRQ

            The HAL_UART_Emul_TxCpltCallback(), HAL_UART_Emul_RxCpltCallback() user callbacks
            will be executed respectivelly at the end of the transmit or receive process.
            The HAL_UART_Emul_ErrorCallback() user callback will be executed when
            a communication error is detected.

    (#) Non Blocking mode functions with DMA are:
        (++) HAL_UART_Emul_Transmit_DMA()
        (++) HAL_UART_Emul_Receive_DMA()

    (#) A set of Transfer Complete Callbacks are provided in Non Blocking mode:
        (++) HAL_UART_Emul_TxCpltCallback()
        (++) HAL_UART_Emul_RxCpltCallback()
        (++) HAL_UART_Emul_ErrorCallback()

    [..]

@endverbatim
  * @{
  */
/**
 * @brief  Sends an amount of data
 * @param  huart: UART Emulation handle
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval HAL status
*/
HAL_StatusTypeDef HAL_UART_Emul_Transmit_DMA(UART_Emul_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  uint32_t tmp = 0;

  tmp = huart->State;
  if ((tmp == HAL_UART_EMUL_STATE_READY) || (tmp == HAL_UART_EMUL_STATE_BUSY_RX))
  {
    if ((pData == NULL ) || (Size == 0))
    {
      return HAL_ERROR;
    }

    huart->TxXferSize = Size;
    huart->pTxBuffPtr = pData;
    huart->TxXferCount = 1;
    huart->ErrorCode = HAL_UART_EMUL_ERROR_NONE;

    /* Check if a receive process is ongoing or not */
    if (huart->State == HAL_UART_EMUL_STATE_BUSY_RX)
    {
      huart->State = HAL_UART_EMUL_STATE_BUSY_TX_RX;
    }
    else
    {
      huart->State = HAL_UART_EMUL_STATE_BUSY_TX;
    }

    /* Set the UART Emulation DMA transfer complete callback */
    TimHandle.hdma[TIM_DMA_Handle_Tx]->XferCpltCallback = UART_Emul_DMATransmitCplt;

    /* Set the DMA error callback */
    TimHandle.hdma[TIM_DMA_Handle_Tx]->XferErrorCallback = UART_Emul_DMAError;

    /* Format first Frame to be sent */
    if (huart->TxXferCount == FIRST_BYTE)
    {
      /* Format Frame to be sent */
      UART_Emul_TransmitFormatFrame(huart, *(pData), (uint32_t*)pFirstBuffer_Tx);

      /* Enable the Capture compare channel */
      TIM_CCxChannelCmd(UART_EMUL_TX_TIMER_INSTANCE, TIM_Channel_Tx, TIM_CCx_ENABLE);

      /* Send Frames */
      UART_Emul_TransmitFrame(huart);
    }

    if ((huart->TxXferCount == FIRST_BYTE) && (huart->TxXferCount < Size))
    {
      /* Format Second Frame to be sent */
      UART_Emul_TransmitFormatFrame(huart, *(pData + huart->TxXferCount), (uint32_t*)pSecondBuffer_Tx);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
 * @brief  Receives an amount of data in non blocking mode.
 * @param  huart: UART Emulation handle
 * @param  pData: Data to be received
 * @param  Size: Amount of data to be received
 * @retval HAL status
*/
HAL_StatusTypeDef HAL_UART_Emul_Receive_DMA(UART_Emul_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  uint32_t tmp = 0;

  tmp = huart->State;
  if ((tmp == HAL_UART_EMUL_STATE_READY) || (tmp == HAL_UART_EMUL_STATE_BUSY_TX))
  {
    if ((pData == NULL ) || (Size == 0))
    {
      return HAL_ERROR;
    }

    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;
    huart->RxXferCount = 1;

    huart->ErrorCode = HAL_UART_EMUL_ERROR_NONE;

    /* Check if a transmit process is ongoing or not */
    if (huart->State == HAL_UART_EMUL_STATE_BUSY_TX)
    {
      huart->State = HAL_UART_EMUL_STATE_BUSY_TX_RX;
    }
    else
    {
      huart->State = HAL_UART_EMUL_STATE_BUSY_RX;
    }

    /* Set the UART Emulation DMA transfer complete callback */
    TimHandle.hdma[TIM_DMA_Handle_Rx]->XferCpltCallback = UART_Emul_DMAReceiveCplt;

    /* Set the DMA error callback */
    TimHandle.hdma[TIM_DMA_Handle_Rx]->XferErrorCallback = UART_Emul_DMAError;

    /* Enable the Capture compare channel */
    TIM_CCxChannelCmd(UART_EMUL_RX_TIMER_INSTANCE, TIM_Channel_Rx, TIM_CCx_ENABLE);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Initializes the UART Emulation Transfer Complete.
  * @param  huart: UART Emulation Handle
  * @retval None
  */
__weak void HAL_UART_Emul_RxCpltCallback(UART_Emul_HandleTypeDef *huart)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_UART_Emul_TransferComplet could be implemented in the user file
   */
}

/**
  * @}
  */
/*===============================================================================
            #####  Interrupt Handlers used in UART Emulation #####
  ===============================================================================
*/

/**
* @brief  This function handles DMA interrupt request for TC.
* @param  None
* @retval None
*/
void UART_EMUL_RX_DMA_IRQHandler(void)
{
  /* Increment Counter of Frame */
  huart_emul->RxXferCount ++;

  /* Enable External interrupt for next Frame */
  EXTI->IMR |= huart_emul->Init.RxPinNumber;

  if (__HAL_DMA_GET_FLAG(TimHandle.hdma[TIM_DMA_Handle_Rx], __HAL_DMA_GET_TE_FLAG_INDEX(TimHandle.hdma[TIM_DMA_Handle_Rx])) != RESET)
  {
    UART_Emul_DMAError(&hdma_rx);
  }

  /* Clear the transfer complete flag */
  __HAL_DMA_CLEAR_FLAG(TimHandle.hdma[TIM_DMA_Handle_Rx], __HAL_DMA_GET_TC_FLAG_INDEX(TimHandle.hdma[TIM_DMA_Handle_Rx]));

  /* Transfer complete callback */
  TimHandle.hdma[TIM_DMA_Handle_Rx]->XferCpltCallback(TimHandle.hdma[TIM_DMA_Handle_Rx]);
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void UART_EMUL_EXTI_RX(void/*uint16_t GPIO_Pin*/)
{
  uint32_t tmpreceive = 0;
  uint32_t tmpformat = 0;
  uint32_t tmpdata = 0;

  /* Disable EXTI line Rx */
  EXTI->IMR &= ~huart_emul->Init.RxPinNumber;

  if ((huart_emul->RxXferCount % 2) != 0)
  {
    tmpreceive = (uint32_t)pFirstBuffer_Rx;
    tmpformat = (uint32_t)pSecondBuffer_Rx;
  }
  else
  {
    tmpreceive = (uint32_t)pSecondBuffer_Rx;
    tmpformat = (uint32_t)pFirstBuffer_Rx;
  }

  /* Start receiver mode in the reference point*/
  UART_Emul_ReceiveFrame(huart_emul, (uint32_t*)tmpreceive);

  if (huart_emul->RxXferCount > 1)
{
    /* Format frame */
    *(uint8_t*)((huart_emul->pRxBuffPtr) + (huart_emul->RxXferCount - 2)) = UART_Emul_ReceiveFormatFrame(huart_emul, (uint32_t*)tmpformat, (uint8_t)tmpdata);
  }
}

/**
* @brief  This function handles DMA interrupt request for TC.
* @param  None
* @retval None
*/
void UART_EMUL_TX_DMA_IRQHandler(void)
{
  if (__HAL_DMA_GET_FLAG(TimHandle.hdma[TIM_DMA_Handle_Tx], __HAL_DMA_GET_TE_FLAG_INDEX(TimHandle.hdma[TIM_DMA_Handle_Tx])) != RESET)
  {
    UART_Emul_DMAError(&hdma_tx);
  }

  /* Clear the transfer complete flag */
  __HAL_DMA_CLEAR_FLAG(TimHandle.hdma[TIM_DMA_Handle_Tx], __HAL_DMA_GET_TC_FLAG_INDEX(TimHandle.hdma[TIM_DMA_Handle_Tx]));

  /* Transfer complete callback */
  TimHandle.hdma[TIM_DMA_Handle_Tx]->XferCpltCallback(TimHandle.hdma[TIM_DMA_Handle_Tx]);
}

/**
  * @brief  This function handles UART Emulation request.
  * @param  huart: UART Emulation handle
  * @retval None
  */
void HAL_UART_Emul_IRQHandler(UART_Emul_HandleTypeDef *huart)
{
  uint32_t tmp = 0;

  tmp = __HAL_UART_EMUL_GET_FLAG(huart, UART_EMUL_FLAG_PE);
  /* UART Emulation parity error  occurred */
  if (tmp != RESET)
  {
    __HAL_UART_EMUL_CLEAR_FLAG(huart, UART_EMUL_FLAG_PE);

    huart->ErrorCode |= HAL_UART_EMUL_ERROR_PE;
  }

  tmp = __HAL_UART_EMUL_GET_FLAG(huart, UART_EMUL_FLAG_FE);
  /* UART Emulation frame error occurred */
  if (tmp != RESET)
  {
    __HAL_UART_EMUL_CLEAR_FLAG(huart, UART_EMUL_FLAG_FE);

    huart->ErrorCode |= HAL_UART_EMUL_ERROR_FE;
  }

  tmp = __HAL_UART_EMUL_GET_FLAG(huart, UART_EMUL_FLAG_TC);
  /* UART Emulation in mode Transmitter */
  if ((tmp != RESET))
  {
    __HAL_UART_EMUL_CLEAR_FLAG(huart, UART_EMUL_FLAG_TC);
  }

  tmp = __HAL_UART_EMUL_GET_FLAG(huart, UART_EMUL_FLAG_RC);
  /* UART Emulation in mode Receiver */
  if ((tmp != RESET))
  {
    __HAL_UART_EMUL_CLEAR_FLAG(huart, UART_EMUL_FLAG_RC);
  }

  if (huart->ErrorCode != HAL_UART_EMUL_ERROR_NONE)
  {
    /* Set the UART Emulation state ready to be able to start again the process */
    huart->State = HAL_UART_EMUL_STATE_READY;

    HAL_UART_Emul_ErrorCallback(huart);
  }
}

/**
  * @}
  */

/** @defgroup UART_Emulation_Group3 Peripheral State and Errors functions
  *  @brief   UART Emulation State and Errors functions
  *
@verbatim
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================
 [..]
   This subsection provides a set of functions allowing to return the State of
   UART Emulation communication process, return Peripheral Errors occured during communication
   process
   (+) HAL_UART_Emul_GetState() API can be helpful to check in run-time the state of the UART Emulation.
   (+) HAL_UART_Emul_GetError() check in run-time errors that could be occured durung communication.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the UART Emulation state.
  * @param  huart: UART Emulation handle
  * @retval HAL state
  */
HAL_UART_Emul_StateTypeDef HAL_UART_Emul_GetState(UART_Emul_HandleTypeDef *huart)
{
  return huart->State;
}

/**
* @brief  Return the UART Emulation error code
* @param  huart : pointer to UART_Emul_HandleTypeDef structure that contains
  *              the configuration information for the specified UART Emulation.
* @retval UART Emulation Error Code
*/
uint32_t HAL_UART_Emul_GetError(UART_Emul_HandleTypeDef *huart)
{
  return huart->ErrorCode;
}

/**
  * @}
  */
/*===============================================================================
            #####  Private function for UART Emulation #####
  ===============================================================================
*/

/**
  * @brief  This function is executed in case of Receive Complete for last frame.
  * @param  None
  * @retval None
  */
static void UART_Emul_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
  uint32_t tmpformat = 0;
  uint32_t tmpdata = 0;
  if (huart_emul->RxXferCount > huart_emul->RxXferSize)
  {
    /*Enable EXTI line Rx  */
    //EXTI->IMR |= huart_emul->Init.RxPinNumber;

    /* Disable the Peripheral */
    __HAL_DMA_DISABLE(&hdma_rx);

    /* Disable the TIM Update DMA request */
    __HAL_TIM_DISABLE_DMA(&TimHandle, TIM_DMA_source_Rx);

    if ((huart_emul->RxXferCount % 2) == 0)
    {
      tmpformat = (uint32_t)pFirstBuffer_Rx;
    }

    else
    {
      tmpformat = (uint32_t)pSecondBuffer_Rx;
    }

    /* Formatted Last Frame */
    *(uint8_t*)((huart_emul->pRxBuffPtr) + (huart_emul->RxXferCount - 2)) = UART_Emul_ReceiveFormatFrame(huart_emul, (uint32_t*)tmpformat, (uint8_t)tmpdata);

    /* Set RC flag receiver complete */
    __HAL_UART_EMUL_SET_FLAG(huart_emul, UART_EMUL_FLAG_RC);

    /* De_Initialize counter frame for Rx */
    huart_emul->RxXferCount = 0;

    /* Initialize the UART Emulation  state */
    huart_emul->ErrorCode = HAL_UART_EMUL_ERROR_NONE;

    /* Check if a transmit process is ongoing or not */
    if (huart_emul->State == HAL_UART_EMUL_STATE_BUSY_TX_RX)
    {
      huart_emul->State = HAL_UART_EMUL_STATE_BUSY_TX;
    }
    else
    {
      huart_emul->State = HAL_UART_EMUL_STATE_READY;
    }

    /* Handle for UART Emulation Receive Complete */
    HAL_UART_Emul_RxCpltCallback(huart_emul);
  }
}

/**
 * @brief  Receives an amount of Frames.
 * @param  huart: UART Emulation handle
 * @param  pData: Frame to be Received
 * @retval None
*/
static void UART_Emul_ReceiveFrame(UART_Emul_HandleTypeDef *huart, uint32_t *pData)
{
  uint32_t tmp_sr =0;
  uint32_t tmp_ds =0;
  uint32_t tmp_size =0;
  uint32_t tmp_arr =0;

  tmp_arr = UART_EMUL_RX_TIMER_INSTANCE->ARR;
  tmp_ds = (uint32_t)pData;
  tmp_sr = (uint32_t) & (huart->RxPortName->IDR);
  tmp_size =  __HAL_UART_EMUL_FRAME_LENGTH(huart);

  /* Enable the transfer complete interrupt */
  __HAL_DMA_ENABLE_IT(&hdma_rx, DMA_IT_TC);

  /* Enable the transfer Error interrupt */
  __HAL_DMA_ENABLE_IT(&hdma_rx, DMA_IT_TE);

#if defined (STM32F0xx) || defined (STM32F3xx)
  /* Configure DMA Stream data length */
  hdma_rx.Instance->CNDTR = tmp_size;

  /* Configure DMA Stream source address */
  hdma_rx.Instance->CPAR = tmp_sr;

  /* Configure DMA Stream destination address */
  hdma_rx.Instance->CMAR = tmp_ds;
#else
  /* Configure DMA Stream data length */
  hdma_rx.Instance->NDTR = tmp_size;

  /* Configure DMA Stream source address */
  hdma_rx.Instance->PAR = tmp_sr;

  /* Configure DMA Stream destination address */
  hdma_rx.Instance->M0AR = tmp_ds;
#endif
  /* Enable the Peripheral */
  __HAL_DMA_ENABLE(&hdma_rx);

  if ((huart_emul->RxXferCount == 1)||(huart->State != HAL_UART_EMUL_STATE_BUSY_TX_RX))
  {
    UART_EMUL_RX_TIMER_INSTANCE->CCR2 = ((UART_EMUL_RX_TIMER_INSTANCE->CNT + (tmp_arr / 2)) % tmp_arr);
  }

  /* Enable the TIM Update DMA request */
  __HAL_TIM_ENABLE_DMA(&TimHandle, TIM_DMA_source_Rx);

  /* Enable Timer */
  __HAL_TIM_ENABLE(&TimHandle);
}

/**
  * @brief  Configures the UART Emulation peripheral
             + Enable clock for all peripherals Timer, GPIO
             + DMA Configuration channel, Stream, Mode,...
  * @param  huart: UART Emulation handle
  * @retval None
  */
static void UART_Emul_SetConfig (UART_Emul_HandleTypeDef *huart)
{
  uint32_t bit_time = 0;

  /* Check the parameters */
  assert_param(IS_UART_EMUL_BAUDRATE(huart->Init.BaudRate));
  assert_param(IS_UART_EMUL_WORD_LENGTH(huart->Init.WordLength));
  assert_param(IS_UART_EMUL_STOPBITS(huart->Init.StopBits));
  assert_param(IS_UART_EMUL_MODE(huart->Init.Mode));
  assert_param(IS_UART_EMUL_MODE(huart->Init.Parity));

  /* Init Bit Time */
  if((HAL_RCC_GetSysClockFreq()/HAL_RCC_GetPCLK2Freq()== 1) | (HAL_RCC_GetSysClockFreq()/HAL_RCC_GetPCLK2Freq()== 2))
  {
    bit_time = ((uint32_t) ((HAL_RCC_GetSysClockFreq()/huart->Init.BaudRate) - 1));
  }
  else
  {
    bit_time = ((uint32_t) (((HAL_RCC_GetPCLK2Freq()*2)/huart->Init.BaudRate) - 1));
  }

  /*##-1- Configure  the Timer peripheral in Bit Delay ##############*/
  /* Initialize TIM peripheral as follow:
  + Period = TimerPeriod
  + Prescaler = 0
  + ClockDivision = 0
  + Counter direction = Up
  */
  TimHandle.Instance            = UART_EMUL_TX_TIMER_INSTANCE;
  TimHandle.Init.Period         = bit_time;
  TimHandle.Init.Prescaler      = 0;
  TimHandle.Init.ClockDivision  = 0;
  TimHandle.Init.CounterMode    = TIM_COUNTERMODE_UP;
  HAL_TIM_Base_Init(&TimHandle);

  if (huart->Init.Mode == UART_EMUL_MODE_TX)
  {
    /* Configure UART Emulation in Transmission mode */
    UART_Emul_SetConfig_DMATx();
  }
  else if (huart->Init.Mode == UART_EMUL_MODE_RX)
  {
    /* Configure UART Emulation in Reception mode */
    UART_Emul_SetConfig_DMARx();
  }
  else
  {
    /* Configure UART Emulation in full-duplex mode */
    UART_Emul_SetConfig_DMATx();
    UART_Emul_SetConfig_DMARx();
  }
}

/**
  * @brief  Configures the DMA for UART Emulation transmission.
             + DMA Configuration channel, Stream, Mode, ...
  * @param  None
  * @retval None
  */
static void UART_Emul_SetConfig_DMATx(void)
{
  /* Init Idle */
  HAL_GPIO_WritePin((huart_emul->TxPortName), (huart_emul->Init.TxPinNumber), GPIO_PIN_SET);

  /*##-1- Configure  DMA For UART Emulation TX #############################*/
  /* Set the parameters to be configured */
  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;         /* Transfer mode                        */
  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;             /* Peripheral increment mode Disable    */
  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;              /* Memory increment mode Enable         */
  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;         /* Peripheral data alignment : Word     */
  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD ;         /* memory data alignment :  Word        */
  hdma_tx.Init.Mode                = DMA_NORMAL;                   /* Normal DMA mode                      */
  hdma_tx.Init.Priority            = DMA_PRIORITY_HIGH;            /* Priority level : High                */
#ifdef STM32F4xx
  hdma_tx.Init.Channel             = DMA_Channel_Tx;               /* Channel used                         */
  hdma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         /* FIFO mode disable                    */
  hdma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;      /* FIFO threshold level                 */
  hdma_tx.Init.MemBurst            = DMA_MBURST_SINGLE;            /* Memory Burst transfer                */
  hdma_tx.Init.PeriphBurst         = DMA_PBURST_SINGLE;            /* Periph Burst transfer                */
#endif

  /* Set hdma_tim instance */
  hdma_tx.Instance = DMA_Stream_Tx;
  hdma_tx.Parent = TimHandle.hdma[TIM_DMA_Handle_Tx];
  /* Link hdma_tim to hdma[ ] ( channel Tx or Rx) */
  __HAL_LINKDMA(&TimHandle, hdma[TIM_DMA_Handle_Tx] , hdma_tx);

  /* Initialize TIMx DMA handle */
  HAL_DMA_Init(TimHandle.hdma[TIM_DMA_Handle_Tx]);

  /*##-2- NVIC configuration for DMA transfer complete interrupt ###########*/
  HAL_NVIC_SetPriority(UART_EMUL_TX_DMA_IRQn, 3, 3);
  HAL_NVIC_EnableIRQ(UART_EMUL_TX_DMA_IRQn);
}

/**
  * @brief  Configures the DMA for UART Emulation reception.
             + DMA Configuration channel, Stream, Mode, ...
  * @param  None
  * @retval None
  */
static void UART_Emul_SetConfig_DMARx(void)
{
  /*##-1- Configure  DMA For UART Emulation RX #############################*/
  /* Set the parameters to be configured */
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;         /* Transfer mode                        */
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;             /* Peripheral increment mode Disable    */
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;              /* Memory increment mode Enable         */
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;         /* Peripheral data alignment : Word     */
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD ;         /* memory data alignment :  Word        */
  hdma_rx.Init.Mode                = DMA_NORMAL;                   /* Normal DMA mode                      */
  hdma_rx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;            /* Priority level : very High      */
#if defined(STM32F4xx)
  hdma_rx.Init.Channel             = DMA_Channel_Rx;               /* Channel used                         */
  hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         /* FIFO mode disable                    */
  hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;      /* FIFO threshold level                 */
  hdma_rx.Init.MemBurst            = DMA_MBURST_SINGLE;            /* Memory Burst transfer                */
  hdma_rx.Init.PeriphBurst         = DMA_PBURST_SINGLE;            /* Periph Burst transfer                */
#endif
  /* Set hdma_tim instance */
  hdma_rx.Instance = DMA_Stream_Rx;

  /* Link hdma_tim to hdma[ ] ( channel Tx or Rx) */
  __HAL_LINKDMA(&TimHandle, hdma[TIM_DMA_Handle_Rx], hdma_rx);

  /* Initialize TIMx DMA handle */
  HAL_DMA_Init(TimHandle.hdma[TIM_DMA_Handle_Rx]);

  /*##-2- NVIC configuration for DMA transfer complete interrupt ###########*/
  HAL_NVIC_SetPriority(UART_EMUL_RX_DMA_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(UART_EMUL_RX_DMA_IRQn);
}

/**
 * @brief  Format Frame in Receiver mode.
 * @param  huart: UART Emulation handle
 * @param  pBuffer: pointer of receiver Buffer
 * @param  pFrame: pointer of Frame
 * @retval None
*/
static uint8_t UART_Emul_ReceiveFormatFrame(UART_Emul_HandleTypeDef *huart, uint32_t *pBuf, uint8_t Data)
{
  uint32_t counter = 0;
  uint32_t length = 0;
  uint32_t tmp = 0;
  uint32_t cntparity = 0;

  if (huart->Init.Parity != UART_EMUL_PARITY_NONE)
  {
    /* Get Length of frame */
    length = huart->Init.WordLength -1 ;
  }
  else
  {
    /* Get Length of frame */
    length = huart->Init.WordLength;
  }

  if ((pBuf[huart->Init.WordLength+1]&huart->Init.RxPinNumber) != huart->Init.RxPinNumber)
  {
    /* UART Emulation frame error occurred */
    __HAL_UART_EMUL_SET_FLAG(huart_emul, UART_EMUL_FLAG_FE);

    huart->ErrorCode |= HAL_UART_EMUL_ERROR_FE;

    /* Disable External interrupt for next Frame */
    EXTI->IMR &= ~huart_emul->Init.RxPinNumber;

    /* Handle for UART Emulation Error */
    HAL_UART_Emul_ErrorCallback(huart);

    tmp = RESET;
  }
  else
  {
    /* format data */
    for (counter = 0; counter < length; counter++)
    {
      if ((pBuf[counter+1]&(huart->Init.RxPinNumber)) == (huart->Init.RxPinNumber))
      {
        Data = (0x01 << counter) | Data;
        cntparity ++;
      }
    }
    /* Parity Bit */
    if (huart->Init.Parity == UART_EMUL_PARITY_ODD)
    {

      if (((cntparity % 2) != SET) && ((pBuf[length+1]&huart->Init.RxPinNumber) != huart->Init.RxPinNumber))
      {
        /* Set flag PE */
        __HAL_UART_EMUL_SET_FLAG(huart, UART_EMUL_FLAG_PE);

        HAL_UART_Emul_ErrorCallback(huart);
      }
    }
    if (huart->Init.Parity == UART_EMUL_PARITY_EVEN)
    {

      if (((cntparity % 2) != RESET) && ((pBuf[length+1]&huart->Init.RxPinNumber) != huart->Init.RxPinNumber))
      {
        /* UART Emulation parity error occurred */
        __HAL_UART_EMUL_SET_FLAG(huart, UART_EMUL_FLAG_PE);

        huart->ErrorCode |= HAL_UART_EMUL_ERROR_PE;

        HAL_UART_Emul_ErrorCallback(huart);
      }
    }

    /* Reset counter parity */
    cntparity = 0;

    tmp = Data;
  }

  return tmp;
}

/**
  * @brief  This function formats one Frame
  * @param  UART Emulation Handle
  * @param  pdata pinteur in data
  * @retval None
  */
static void UART_Emul_TransmitFormatFrame(UART_Emul_HandleTypeDef *huart , uint8_t Data, uint32_t *pBuffer_Tx)
{
  uint32_t counter = 0;
  uint32_t bitmask = 0;
  uint32_t length = 0;
  uint32_t cntparity = 0;

  length = huart->Init.WordLength;

  /* Get the Pin Number */
  bitmask = (uint32_t)huart->Init.TxPinNumber;

  /* with no parity */
  if(huart->Init.Parity == 0x00)
  {
    for (counter = 0; counter < length; counter++)
    {
      if (((Data >> counter)&BitMask) != 0)
      {
        pBuffer_Tx[counter+1] = bitmask;
      }
      else
      {
        pBuffer_Tx[counter+1] = (bitmask << 16);
      }
    }
  }
  /* with parity */
  else
  {
    for (counter = 0; counter < length-1; counter++)
    {
      if (((Data >> counter)&BitMask) != 0)
      {
        pBuffer_Tx[counter+1] = bitmask;
        cntparity ++;
      }
      else
      {
        pBuffer_Tx[counter+1] = (bitmask << 16);
      }
    }
  }

  switch  (huart->Init.Parity)
  {
    case UART_EMUL_PARITY_ODD:
    {
      /* Initialize Parity Bit */
      if ((cntparity % 2) != SET)
      {
        pBuffer_Tx[length] = bitmask;
      }
      else
      {
        pBuffer_Tx[length] = (bitmask << 16);
      }

    }
    break;
    case UART_EMUL_PARITY_EVEN:
    {
      /* Initialize Parity Bit */
      if ((cntparity % 2) != SET)
      {
        pBuffer_Tx[length] = (bitmask << 16);
      }
      else
      {
        pBuffer_Tx[length] = bitmask;
      }
    }
    break;
    default:
      break;
  }
  /* Initialize Bit Start */
  pBuffer_Tx[0] = (bitmask << 16);

  if (huart->Init.StopBits == UART_EMUL_STOPBITS_1)
  {
    /* Initialize Bit Stop  */
    pBuffer_Tx[length+1] = bitmask;
  }
  else
  {
    /* Initialize Bit Stop  */
    pBuffer_Tx[length+1] = bitmask;
    pBuffer_Tx[length+2] = bitmask;
  }
  /* Reset counter parity */
  cntparity = 0;
}

/**
  * @brief  Sends an amount of Frames
  * @param  huart: UART Emulation handle
  * @param  pData: Frame to be sent
  * @retval None
  */
static void UART_Emul_TransmitFrame(UART_Emul_HandleTypeDef *huart)
{
  uint32_t tmp_sr = 0;
  uint32_t tmp_ds = 0;
  uint32_t tmp_size = 0;


  if ((huart_emul->TxXferCount % 2 ) != 0)
  {
    tmp_sr = (uint32_t)pFirstBuffer_Tx;
  }
  else
  {
    tmp_sr = (uint32_t)pSecondBuffer_Tx;
  }

	tmp_ds = (uint32_t) & ((huart->TxPortName)->BSRR);

  tmp_size = __HAL_UART_EMUL_FRAME_LENGTH(huart);

#if defined (STM32F0xx) || defined (STM32F3xx)
  /* Configure DMA Stream data length */
  hdma_rx.Instance->CNDTR = tmp_size;

  /* Configure DMA Stream source address */
  hdma_rx.Instance->CPAR = tmp_sr;

  /* Configure DMA Stream destination address */
  hdma_rx.Instance->CMAR = tmp_ds;
#else
  /* Configure DMA Stream data length */
  hdma_tx.Instance->NDTR = tmp_size;

  /* Configure DMA Stream destination address */
  hdma_tx.Instance->PAR = tmp_ds;

  /* Configure DMA Stream source address */
  hdma_tx.Instance->M0AR = tmp_sr;
#endif

  /* Enable the transfer complete interrupt */
  __HAL_DMA_ENABLE_IT(&hdma_tx, DMA_IT_TC);

  /* Enable the transfer Error interrupt */
  __HAL_DMA_ENABLE_IT(&hdma_tx, DMA_IT_TE);

  /* Enable the Peripheral */
  __HAL_DMA_ENABLE(&hdma_tx);

  /* Enable the TIM Update DMA request */
  __HAL_TIM_ENABLE_DMA(&TimHandle, TIM_DMA_source_Tx);

  /* Enable the Peripheral */
  __HAL_TIM_ENABLE(&TimHandle);
}

/**
  * @brief  This function is executed in case of Transfer Complete of a Frame.
  * @param  None
  * @retval None
  */
static void UART_Emul_DMATransmitCplt(DMA_HandleTypeDef *hdma)
{
  uint32_t tmpbuffer = 0;

  /* Incremente Counter of frame */
  huart_emul->TxXferCount++;

  if (huart_emul->TxXferCount <= huart_emul->TxXferSize)
  {
    /* Call UART Emulation Transmit frame for next Frame */
    UART_Emul_TransmitFrame(huart_emul);

    if ((huart_emul->TxXferCount % 2 ) != 0)
    {
      tmpbuffer = (uint32_t)pSecondBuffer_Tx;
    }
    else
    {
      tmpbuffer = (uint32_t)pFirstBuffer_Tx;
    }
    /* Format second Data to be sent */
    UART_Emul_TransmitFormatFrame(huart_emul, *(huart_emul->pTxBuffPtr + huart_emul->TxXferCount), (uint32_t*)tmpbuffer);
  }
  else
  {
    /* Disable the transfer complete interrupt */
    __HAL_DMA_DISABLE_IT(TimHandle.hdma[TIM_DMA_Handle_Tx], DMA_IT_TC);

    /* Set TC flag in the status register software */
    __HAL_UART_EMUL_SET_FLAG(huart_emul, UART_EMUL_FLAG_TC);

    /* Disable the Peripheral */
    __HAL_DMA_DISABLE(&hdma_tx);

    /* Disable the TIM Update DMA request */
    __HAL_TIM_DISABLE_DMA(&TimHandle, TIM_DMA_source_Tx);

    /* De_Initialize counter frame for Tx */
    huart_emul->TxXferCount = 0;

    /* Initialize the UART Emulation state */
    huart_emul->ErrorCode = HAL_UART_EMUL_ERROR_NONE;

    /* Check if a receive process is ongoing or not */
    if (huart_emul->State == HAL_UART_EMUL_STATE_BUSY_TX_RX)
    {
      huart_emul->State = HAL_UART_EMUL_STATE_BUSY_RX;
    }
    else
    {
      huart_emul->State = HAL_UART_EMUL_STATE_READY;
    }
    /* Handle for UART Emulation Transfer Complete */
    HAL_UART_Emul_TxCpltCallback(huart_emul);
  }
}

/**
  * @brief  This function is executed in case of error of Transfer occurrence.
  * @param  hdma : DMA Handle
  * @retval None
  */
static void UART_Emul_DMAError(DMA_HandleTypeDef *hdma)
{
  /* UART Emulation frame error occurred */
  __HAL_UART_EMUL_SET_FLAG(huart_emul, UART_EMUL_FLAG_FE);

  huart_emul->ErrorCode |= HAL_UART_EMUL_ERROR_FE;

  HAL_UART_Emul_ErrorCallback(huart_emul);
}

/**
  * @brief  Initializes the UART Emulation Transfer Complete.
  * @param  huart: UART Emulation Handle
  * @retval None
  */
__weak void HAL_UART_Emul_TxCpltCallback(UART_Emul_HandleTypeDef *huart)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_UART_Emul_TransferComplete could be implemented in the user file
   */
}

/**
  * @brief  UART Emulation error callbacks.
  * @param  huart: UART Emulation handle
  * @retval None
  */
__weak void HAL_UART_Emul_ErrorCallback(UART_Emul_HandleTypeDef *huart)
{
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_ErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */

//#endif /* HAL_UART_EMUL_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
#endif //TIM1_BASE && UART_EMUL_RX && UART_EMUL_TX
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
