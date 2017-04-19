/**
  ******************************************************************************
  * @file    uart_emul.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    11-July-2016
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

#ifdef STM32F0xx
/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "uart_emul.h"
#include "interrupt.h"
#include "uart.h"

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

/* UART Emulation Handle */
static UART_Emul_HandleTypeDef      *huart_emul;

/* First Buffer for format data in transmission mode */
static uint32_t *pFirstBuffer_Tx[TX_BUFFER_SIZE];

/* Second Buffer for format data in transmission mode */
static uint32_t *pSecondBuffer_Tx[TX_BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void UART_Emul_SetConfig (UART_Emul_HandleTypeDef *huart);
static void UART_Emul_TransmitCplt(void);
static void UART_Emul_ReceiveCplt(void);
static void UART_Emul_TransmitFrame(UART_Emul_HandleTypeDef *huart);
static void UART_Emul_TransmitFormatFrame(UART_Emul_HandleTypeDef *huart , uint8_t pData, uint32_t *pBuffer_Tx);
static uint8_t UART_Emul_ReceiveFormatFrame(UART_Emul_HandleTypeDef *huart, uint16_t pFrame);
static void UART_EMUL_TIM_TX_IT(void);
static void UART_EMUL_TIM_RX_IT(void);

void TIM_TX_CALLBACK(timer_id_e timer_id) {UART_EMUL_TIM_TX_IT();}
void TIM_RX_CALLBACK(timer_id_e timer_id) {UART_EMUL_TIM_RX_IT();}

static volatile uint8_t g_txCplt = 0;

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
       (++) Non-Blocking mode: The communication is performed using IT,
            this APIs returns the HAL status.
            The end of the data processing will be indicated through the
            IT IRQ

            The HAL_UART_Emul_TxCpltCallback(), HAL_UART_Emul_RxCpltCallback() user callbacks
            will be executed respectivelly at the end of the transmit or receive process.
            The HAL_UART_Emul_ErrorCallback() user callback will be executed when
            a communication error is detected.

    (#) Non Blocking mode functions with IT are:
        (++) HAL_UART_Emul_Transmit()
        (++) HAL_UART_Emul_Receive()

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
HAL_StatusTypeDef HAL_UART_Emul_Transmit(UART_Emul_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
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

    /* Format first Frame to be sent */
    if (huart->TxXferCount == FIRST_BYTE)
    {
      /* Format Frame to be sent */
      UART_Emul_TransmitFormatFrame(huart, *(pData), (uint32_t*)pFirstBuffer_Tx);

      /* Send Frames */
      UART_Emul_TransmitFrame(huart);
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
HAL_StatusTypeDef HAL_UART_Emul_Receive(UART_Emul_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
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
* @brief  This function handles IT interrupt request for TC.
* @param  None
* @retval None
*/
void UART_EMUL_RX_IRQHandler(void)
{
  /* Disable timer */
  TimerHandleDeinit(__UART_EMUL_RX_TIMER);

  /* Increment Counter of Frame */
  huart_emul->RxXferCount ++;

  /* Transfer complete callback */
  UART_Emul_ReceiveCplt();
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void UART_EMUL_EXTI_RX(void)
{
  uint32_t bit_time = 0;

  /* Disable EXTI line Rx */
  EXTI->IMR &= ~huart_emul->Init.RxPinNumber;

  /* Init Bit Time */
  if((HAL_RCC_GetSysClockFreq()/HAL_RCC_GetPCLK1Freq()== 1) | (HAL_RCC_GetSysClockFreq()/HAL_RCC_GetPCLK1Freq()== 2))
  {
    bit_time = ((uint32_t) ((HAL_RCC_GetSysClockFreq()/huart_emul->Init.BaudRate) - 1));
  }
  else
  {
    bit_time = ((uint32_t) (((HAL_RCC_GetPCLK1Freq()*2)/huart_emul->Init.BaudRate) - 1));
  }

  /* Enable timer */
  TimerHandleInit(__UART_EMUL_RX_TIMER, bit_time, 0);
  setTimerCounter(__UART_EMUL_RX_TIMER, 0);

  huart_emul->RxXferByte = 0;
  huart_emul->RxBitCount = 0;
}

/**
* @brief  This function handles Timer interrupt request for TC.
* @param  none
* @retval None
*/
void UART_EMUL_TIM_RX_IT(void)
{
  if(huart_emul->RxBitCount < huart_emul->RxBitSize)
  {
    huart_emul->RxXferByte |= HAL_GPIO_ReadPin(huart_emul->RxPortName,
                                               huart_emul->Init.RxPinNumber) << huart_emul->RxBitCount;
    huart_emul->RxBitCount++;

    if(huart_emul->RxBitCount == huart_emul->RxBitSize) {
      UART_EMUL_RX_IRQHandler();
    }
  }
}

/**
* @brief  This function handles Timer interrupt request for TC.
* @param  none
* @retval None
*/
void UART_EMUL_TIM_TX_IT(void)
{
  if(huart_emul->TxBitCount < huart_emul->TxBitSize)
  {
    HAL_GPIO_WritePin(huart_emul->TxPortName, huart_emul->Init.TxPinNumber, SET & (huart_emul->TxXferByte >> huart_emul->TxBitCount));
    huart_emul->TxBitCount++;

    if(huart_emul->TxBitCount == huart_emul->TxBitSize) {
      /* Put Tx output in standby state */
      HAL_GPIO_WritePin(huart_emul->TxPortName, huart_emul->Init.TxPinNumber, SET);
      g_txCplt = 1;
    }
  } else if(g_txCplt == 1) {
    UART_Emul_TransmitCplt();
    g_txCplt = 0;
  }
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
static void UART_Emul_ReceiveCplt(void)
{
  if (huart_emul->RxXferCount > huart_emul->RxXferSize)
  {
    /*Enable EXTI line Rx  */
    EXTI->IMR |= huart_emul->Init.RxPinNumber;

    /* Formatted Last Frame */
    *(uint8_t*)((huart_emul->pRxBuffPtr) + (huart_emul->RxXferCount - 2)) = UART_Emul_ReceiveFormatFrame(huart_emul, huart_emul->RxXferByte);

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
  * @brief  Configures the UART Emulation peripheral
             + Enable clock for all peripherals Timer, GPIO
  * @param  huart: UART Emulation handle
  * @retval None
  */
static void UART_Emul_SetConfig (UART_Emul_HandleTypeDef *huart)
{
  /* Check the parameters */
  assert_param(IS_UART_EMUL_BAUDRATE(huart->Init.BaudRate));
  assert_param(IS_UART_EMUL_WORD_LENGTH(huart->Init.WordLength));
  assert_param(IS_UART_EMUL_STOPBITS(huart->Init.StopBits));
  assert_param(IS_UART_EMUL_MODE(huart->Init.Mode));
  assert_param(IS_UART_EMUL_MODE(huart->Init.Parity));

  /* Configure  the Timer peripheral (TIM17) in Bit Delay */
  attachIntHandle(__UART_EMUL_TX_TIMER, TIM_TX_CALLBACK);
  attachIntHandle(__UART_EMUL_RX_TIMER, TIM_RX_CALLBACK);

  /* Put Tx output in standby state */
  HAL_GPIO_WritePin(huart_emul->TxPortName, huart_emul->Init.TxPinNumber, SET);

  /* Enable Rx EXTI interrupt */
  stm32_interrupt_enable(huart->RxPortName, huart->Init.RxPinNumber, UART_EMUL_EXTI_RX, GPIO_MODE_IT_FALLING);

  /* Configure the number of bit in a frame */
  huart->RxBitSize = __HAL_UART_EMUL_FRAME_LENGTH(huart);
}

/**
 * @brief  Format Frame in Receiver mode.
 * @param  huart: UART Emulation handle
 * @param  pBuffer: pointer of receiver Buffer
 * @param  pFrame: pointer of Frame
 * @retval None
*/
static uint8_t UART_Emul_ReceiveFormatFrame(UART_Emul_HandleTypeDef *huart, uint16_t Data)
{
  uint16_t counter = 0;
  uint8_t length = 0;
  uint8_t tmp = 0;
  uint8_t cntparity = 0;

  /* Get Length of frame */
  length = huart->Init.WordLength;

  /* Remove stop bit(s) */
  Data &= MASK_STOP_BIT(huart);

  /* Remove start bit */
  Data >>= BitMask;

  /* Check parity */
  if (huart->Init.Parity == UART_EMUL_PARITY_NONE)
  {
    tmp = Data;
  }
  else
  {
    /* format data */
    for (counter = 0; counter < length; counter++)
    {
      if(((Data >> counter) & 0x01) == 0x01)
      {
        cntparity ++;
      }
    }

    /* Remove parity bit */
    tmp = (uint8_t)(Data & ~(0x0001 << (length - 1)));

    /* Parity Bit */
    if (huart->Init.Parity == UART_EMUL_PARITY_ODD)
    {
      if ((cntparity % 2) != SET)
      {
        /* Set flag PE */
        __HAL_UART_EMUL_SET_FLAG(huart, UART_EMUL_FLAG_PE);

        HAL_UART_Emul_ErrorCallback(huart);

        tmp = RESET;
      }
    }
    else if (huart->Init.Parity == UART_EMUL_PARITY_EVEN)
    {
      if ((cntparity % 2) != RESET)
      {
        /* UART Emulation parity error occurred */
        __HAL_UART_EMUL_SET_FLAG(huart, UART_EMUL_FLAG_PE);

        huart->ErrorCode |= HAL_UART_EMUL_ERROR_PE;

        HAL_UART_Emul_ErrorCallback(huart);

        tmp = RESET;
      }
    }

    /* Reset counter parity */
    cntparity = 0;
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
  uint32_t bit_time = 0;

  /* Disable EXTI line Rx */
  //EXTI->IMR &= ~huart->Init.RxPinNumber;

  /* Init Bit Time */
  if((HAL_RCC_GetSysClockFreq()/HAL_RCC_GetPCLK1Freq()== 1) | (HAL_RCC_GetSysClockFreq()/HAL_RCC_GetPCLK1Freq()== 2))
  {
    bit_time = ((uint32_t) ((HAL_RCC_GetSysClockFreq()/huart->Init.BaudRate) - 1));
  }
  else
  {
    bit_time = ((uint32_t) (((HAL_RCC_GetPCLK1Freq()*2)/huart->Init.BaudRate) - 1));
  }

  huart->TxBitSize = __HAL_UART_EMUL_FRAME_LENGTH(huart);
  huart->TxBitCount = 0;

  /* Add start and stop bits */
  huart->TxXferByte = huart->pTxBuffPtr[huart->TxXferCount-1] << 1;
  huart->TxXferByte |= (uint16_t)(0x0001 << (huart->TxBitSize - huart->Init.StopBits));
  if(huart->Init.StopBits == UART_EMUL_STOPBITS_2)
  {
    huart->TxXferByte |= (uint16_t)(0x0001 << (huart->TxBitSize - huart->Init.StopBits + 1));
  }

  /* Enable timer */
  TimerHandleInit(__UART_EMUL_TX_TIMER, bit_time, 0);
  setTimerCounter(__UART_EMUL_TX_TIMER, 0);
}

/**
  * @brief  This function is executed in case of Transfer Complete of a Frame.
  * @param  None
  * @retval None
  */
static void UART_Emul_TransmitCplt(void)
{
  uint32_t tmpbuffer = 0;

  /* Incremente Counter of frame */
  huart_emul->TxXferCount++;

  /* Disable timer */
  TimerHandleDeinit(__UART_EMUL_TX_TIMER);

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

    /* Enable EXTI line Rx */
    //EXTI->IMR |= huart_emul->Init.RxPinNumber;

    /* Handle for UART Emulation Transfer Complete */
    HAL_UART_Emul_TxCpltCallback(huart_emul);
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
#endif
