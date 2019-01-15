/**
  ******************************************************************************
  * @file    twi.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide the TWI interface
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f4xx_system
  * @{
  */

/** @addtogroup STM32F4xx_System_Private_Includes
  * @{
  */
#include "core_debug.h"
#include "stm32_def.h"
#include "twi.h"
#include "PinAF_STM32F1.h"

/**
  * @}
  */

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Defines
  * @{
  */

/// @brief I2C timout in tick unit
#define I2C_TIMEOUT_TICK        100

#define SLAVE_MODE_TRANSMIT     0
#define SLAVE_MODE_RECEIVE      1
#define SLAVE_MODE_LISTEN       2


/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Variables
  * @{
  */

/*  Family specific description for I2C */
#if defined(STM32F7xx) || defined(STM32H7xx) || defined(STM32L4xx)
#define I2C_NUM (4)
#elif defined(STM32F2xx) || defined(STM32F3xx) || defined(STM32F4xx) || defined(STM32L0xx)
#define I2C_NUM (3)
#elif defined(STM32F0xx) || defined(STM32F1xx) || defined(STM32L1xx)
#define I2C_NUM (2)
#else
#error "Unknown Family - unknown I2C_NUM"
#endif

static I2C_HandleTypeDef* i2c_handles[I2C_NUM];

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Functions
  * @{
  */


/**
  * @brief  Default init and setup GPIO and I2C peripheral
  * @param  obj : pointer to i2c_t structure
  * @retval none
  */
void i2c_init(i2c_t *obj)
{
  i2c_custom_init(obj, I2C_100KHz, I2C_ADDRESSINGMODE_7BIT, 0x33, 1);
}

/**
  * @brief  Initialize and setup GPIO and I2C peripheral
  * @param  obj : pointer to i2c_t structure
  * @param  timing : one of the i2c_timing_e
  * @param  addressingMode : I2C_ADDRESSINGMODE_7BIT or I2C_ADDRESSINGMODE_10BIT
  * @param  ownAddress : device address
  * @param  master : set to 1 to choose the master mode
  * @retval none
  */
void i2c_custom_init(i2c_t *obj, i2c_timing_e timing, uint32_t addressingMode, uint32_t ownAddress, uint8_t master)
{
  if(obj == NULL)
    return;

  I2C_HandleTypeDef *handle = &(obj->handle);

  // Determine the I2C to use
  I2C_TypeDef *i2c_sda = pinmap_peripheral(obj->sda, PinMap_I2C_SDA);
  I2C_TypeDef *i2c_scl = pinmap_peripheral(obj->scl, PinMap_I2C_SCL);

  //Pins SDA/SCL must not be NP
  if(i2c_sda == NP || i2c_scl == NP) {
    core_debug("ERROR: at least one I2C pin has no peripheral\n");
    return;
  }

  obj->i2c = pinmap_merge_peripheral(i2c_sda, i2c_scl);

  if(obj->i2c == NP) {
    core_debug("ERROR: I2C pins mismatch\n");
    return;
  }

#if defined I2C1_BASE
  // Enable I2C1 clock if not done
  if (obj->i2c == I2C1) {
    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_I2C1_FORCE_RESET();
    __HAL_RCC_I2C1_RELEASE_RESET();

    obj->irq = I2C1_EV_IRQn;
#if !defined(STM32F0xx) && !defined(STM32L0xx)
    obj->irqER = I2C1_ER_IRQn;
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
    i2c_handles[0] = handle;
  }
#endif // I2C1_BASE
#if defined I2C2_BASE
  // Enable I2C2 clock if not done
  if (obj->i2c == I2C2) {
    __HAL_RCC_I2C2_CLK_ENABLE();
    __HAL_RCC_I2C2_FORCE_RESET();
    __HAL_RCC_I2C2_RELEASE_RESET();
    obj->irq = I2C2_EV_IRQn;
#if !defined(STM32F0xx) && !defined(STM32L0xx)
    obj->irqER = I2C2_ER_IRQn;
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
    i2c_handles[1] = handle;
  }
#endif // I2C2_BASE
#if defined I2C3_BASE
  // Enable I2C3 clock if not done
  if (obj->i2c == I2C3) {
    __HAL_RCC_I2C3_CLK_ENABLE();
    __HAL_RCC_I2C3_FORCE_RESET();
    __HAL_RCC_I2C3_RELEASE_RESET();
    obj->irq = I2C3_EV_IRQn;
#if !defined(STM32F0xx) && !defined(STM32L0xx)
    obj->irqER = I2C3_ER_IRQn;
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
    i2c_handles[2] = handle;
  }
#endif // I2C3_BASE
#if defined I2C4_BASE
  // Enable I2C4 clock if not done
  if (obj->i2c == I2C4) {
    __HAL_RCC_I2C4_CLK_ENABLE();
    __HAL_RCC_I2C4_FORCE_RESET();
    __HAL_RCC_I2C4_RELEASE_RESET();
    obj->irq = I2C4_EV_IRQn;
#if !defined(STM32F0xx) && !defined(STM32L0xx)
    obj->irqER = I2C4_ER_IRQn;
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
    i2c_handles[3] = handle;
  }
#endif // I2C4_BASE

  /* Configure I2C GPIO pins */
  pinmap_pinout(obj->scl, PinMap_I2C_SCL);
  pinmap_pinout(obj->sda, PinMap_I2C_SDA);

  handle->Instance             = obj->i2c;
#if defined (STM32F0xx) || defined (STM32F3xx) || defined (STM32F7xx) ||\
    defined (STM32H7xx) || defined (STM32L0xx) || defined (STM32L4xx)
  handle->Init.Timing      = timing;
#else
  handle->Init.ClockSpeed      = timing;
  /* Standard mode (sm) is up to 100kHz, then it's Fast mode (fm)     */
  /* In fast mode duty cyble bit must be set in CCR register          */
  if(timing > 100000)
    handle->Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
  else
    handle->Init.DutyCycle       = I2C_DUTYCYCLE_2;
#endif
  handle->Init.OwnAddress1     = ownAddress;
  handle->Init.OwnAddress2     = 0xFF;
  handle->Init.AddressingMode  = addressingMode;
  handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  handle->Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

  handle->State = HAL_I2C_STATE_RESET;

  HAL_NVIC_SetPriority(obj->irq, 0, 1);
  HAL_NVIC_EnableIRQ(obj->irq);
#if !defined(STM32F0xx) && !defined(STM32L0xx)
  HAL_NVIC_SetPriority(obj->irqER, 0, 1);
  HAL_NVIC_EnableIRQ(obj->irqER);
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)

  // Init the I2C
  HAL_I2C_Init(handle);

  obj->isMaster = master;
  /* Initialize default values */
  obj->slaveRxNbData = 0;
  obj->slaveMode = SLAVE_MODE_LISTEN;
}

/**
  * @brief  Initialize and setup GPIO and I2C peripheral
  * @param  obj : pointer to i2c_t structure
  * @retval none
  */
void i2c_deinit(i2c_t *obj)
{
  HAL_NVIC_DisableIRQ(obj->irq);
#if !defined(STM32F0xx) && !defined(STM32L0xx)
  HAL_NVIC_DisableIRQ(obj->irqER);
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
  HAL_I2C_DeInit(&(obj->handle));
}

/**
  * @brief  Setup transmission speed. I2C must be configured before.
  * @param  obj : pointer to i2c_t structure
  * @param  frequency : i2c transmission speed
  * @retval none
  */
void i2c_setTiming(i2c_t *obj, uint32_t frequency)
{
  uint32_t f = I2C_10KHz;
  __HAL_I2C_DISABLE(&(obj->handle));

  if(frequency <= 10000)
    f = I2C_10KHz;
  else if(frequency <= 50000)
    f = I2C_50KHz;
  else if(frequency <= 100000)
    f = I2C_100KHz;
  else if(frequency <= 200000)
    f = I2C_200KHz;
  else if(frequency <= 400000)
    f = I2C_400KHz;

#if defined (STM32F0xx) || defined (STM32F3xx) || defined (STM32F7xx) ||\
    defined (STM32H7xx) || defined (STM32L0xx) || defined (STM32L4xx)
  obj->handle.Init.Timing = f;
#else
  obj->handle.Init.ClockSpeed = f;
  /* Standard mode (sm) is up to 100kHz, then it's Fast mode (fm)     */
  /* In fast mode duty cyble bit must be set in CCR register          */
  if(frequency > 100000)
    obj->handle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
  else
    obj->handle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
#endif
/*
  else if(frequency <= 600000)
    g_i2c_init_info[i2c_id].i2c_handle.Init.ClockSpeed = I2C_600KHz;
  else if(frequency <= 800000)
    g_i2c_init_info[i2c_id].i2c_handle.Init.ClockSpeed = I2C_800KHz;
  else
    g_i2c_init_info[i2c_id].i2c_handle.Init.ClockSpeed = I2C_1000KHz;
*/
  HAL_I2C_Init(&(obj->handle));
  __HAL_I2C_ENABLE(&(obj->handle));
}

/**
  * @brief  Write bytes at a given address
  * @param  obj : pointer to i2c_t structure
  * @param  dev_address: specifies the address of the device.
  * @param  data: pointer to data to be write
  * @param  size: number of bytes to be write.
  * @retval read status
  */
i2c_status_e i2c_master_write(i2c_t *obj, uint8_t dev_address,
                        uint8_t *data, uint16_t size)

{
  i2c_status_e ret = I2C_ERROR;
  uint32_t tickstart = HAL_GetTick();
  uint32_t delta = 0;

  /* When size is 0, this is usually an I2C scan / ping to check if device is there and ready */
  if (size == 0) {
    return i2c_IsDeviceReady(obj, dev_address, 1);
  }

  do{
    if(HAL_I2C_Master_Transmit_IT(&(obj->handle), dev_address, data, size) == HAL_OK){
      ret = I2C_OK;
      // wait for transfer completion
      while((HAL_I2C_GetState(&(obj->handle)) != HAL_I2C_STATE_READY)
             && (ret == I2C_OK)){
        delta = (HAL_GetTick() - tickstart);
        if(delta > I2C_TIMEOUT_TICK) {
          ret = I2C_TIMEOUT;
        } else if(HAL_I2C_GetError(&(obj->handle)) != HAL_I2C_ERROR_NONE) {
          ret = I2C_ERROR;
        }
      }
    }
    /* When Acknowledge failure occurs (Slave don't acknowledge it's address)
       Master restarts communication */
  }while(HAL_I2C_GetError(&(obj->handle)) == HAL_I2C_ERROR_AF && delta < I2C_TIMEOUT_TICK);

  return ret;
}

/**
  * @brief  Write bytes to master
  * @param  obj : pointer to i2c_t structure
  * @param  data: pointer to data to be write
  * @param  size: number of bytes to be write.
  * @retval status
  */
i2c_status_e i2c_slave_write_IT(i2c_t *obj, uint8_t *data, uint16_t size)
{
  uint8_t i = 0;

  // Protection to not override the TxBuffer
  if(size > I2C_TXRX_BUFFER_SIZE) {
    return I2C_ERROR;
  }

  // Check the communication status
  for(i = 0; i < size; i++) {
    obj->i2cTxRxBuffer[i] = *(data+i);
  }

  obj->i2cTxRxBufferSize = size;

  return I2C_OK;
}

/**
  * @brief  read bytes in master mode at a given address
  * @param  obj : pointer to i2c_t structure
  * @param  dev_address: specifies the address of the device.
  * @param  data: pointer to data to be read
  * @param  size: number of bytes to be read.
  * @retval read status
  */
i2c_status_e i2c_master_read(i2c_t *obj, uint8_t dev_address, uint8_t *data, uint16_t size)
{
  i2c_status_e ret = I2C_ERROR;
  uint32_t tickstart = HAL_GetTick();
  uint32_t delta = 0;

  do{
    if(HAL_I2C_Master_Receive_IT(&(obj->handle), dev_address, data, size) == HAL_OK) {
      ret = I2C_OK;
      // wait for transfer completion
      while((HAL_I2C_GetState(&(obj->handle)) != HAL_I2C_STATE_READY)
             && (ret == I2C_OK)){
        delta = (HAL_GetTick() - tickstart);
        if( delta > I2C_TIMEOUT_TICK) {
          ret = I2C_TIMEOUT;
        } else if(HAL_I2C_GetError(&(obj->handle)) != HAL_I2C_ERROR_NONE) {
          ret = I2C_ERROR;
        }
      }
    }
    /* When Acknowledge failure occurs (Slave don't acknowledge it's address)
       Master restarts communication */
  }while(HAL_I2C_GetError(&(obj->handle)) == HAL_I2C_ERROR_AF && delta < I2C_TIMEOUT_TICK);

  return ret;
}

/**
  * @brief  Checks if target device is ready for communication
  * @param  obj : pointer to i2c_t structure
  * @param  devAddr: specifies the address of the device.
  * @param  trials : Number of trials.
  * @retval status
  */
i2c_status_e i2c_IsDeviceReady(i2c_t *obj, uint8_t devAddr, uint32_t trials)
{
  i2c_status_e ret = HAL_OK;

  switch (HAL_I2C_IsDeviceReady( &(obj->handle), devAddr, trials, I2C_TIMEOUT_TICK)) {
    case HAL_OK:
      ret = HAL_OK;
      break;
    case HAL_TIMEOUT:
      ret = I2C_TIMEOUT;
      break;
    case HAL_BUSY:
      ret = I2C_BUSY;
      break;
    default:
      ret = I2C_TIMEOUT;
      break;
  }

  return ret;
}

/* Aim of the function is to get i2c_s pointer using hi2c pointer */
/* Highly inspired from magical linux kernel's "container_of" */
/* (which was not directly used since not compatible with IAR toolchain) */
i2c_t *get_i2c_obj(I2C_HandleTypeDef *hi2c){
    struct i2c_s *obj_s;
    i2c_t *obj;

    obj_s = (struct i2c_s *)( (char *)hi2c - offsetof(struct i2c_s,handle));
    obj = (i2c_t *)( (char *)obj_s - offsetof(i2c_t,i2c));

    return (obj);
}

/** @brief  sets function called before a slave read operation
  * @param  obj : pointer to i2c_t structure
  * @param  function: callback function to use
  * @retval None
  */
void i2c_attachSlaveRxEvent(i2c_t *obj, void (*function)(uint8_t*, int) )
{
  if((obj == NULL) || (function == NULL))
    return;

  obj->i2c_onSlaveReceive = function;
  HAL_I2C_EnableListen_IT(&(obj->handle));
}

/** @brief  sets function called before a slave write operation
  * @param  obj : pointer to i2c_t structure
  * @param  function: callback function to use
  * @retval None
  */
void i2c_attachSlaveTxEvent(i2c_t *obj, void (*function)(void) )
{
  if((obj == NULL) || (function == NULL))
    return;

  obj->i2c_onSlaveTransmit = function;
  HAL_I2C_EnableListen_IT(&(obj->handle));
}

/**
  * @brief  Slave Address Match callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  TransferDirection: Master request Transfer Direction (Write/Read), value of @ref I2C_XferOptions_definition
  * @param  AddrMatchCode: Address Match Code
  * @retval None
  */
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  i2c_t *obj = get_i2c_obj(hi2c);

  if(AddrMatchCode == hi2c->Init.OwnAddress1) {
    if(TransferDirection == I2C_DIRECTION_RECEIVE) {
      obj->slaveMode = SLAVE_MODE_TRANSMIT;

      if(obj->i2c_onSlaveTransmit != NULL) {
        obj->i2c_onSlaveTransmit();
      }
#if defined(STM32L0xx)
      HAL_I2C_Slave_Seq_Transmit_IT(hi2c, (uint8_t *) obj->i2cTxRxBuffer,
                                           obj->i2cTxRxBufferSize, I2C_LAST_FRAME);
#else
      HAL_I2C_Slave_Sequential_Transmit_IT(hi2c, (uint8_t *) obj->i2cTxRxBuffer,
                                           obj->i2cTxRxBufferSize, I2C_LAST_FRAME);
#endif
    } else {
      obj->slaveRxNbData = 0;
      obj->slaveMode = SLAVE_MODE_RECEIVE;
      /*  We don't know in advance how many bytes will be sent by master so
       *  we'll fetch one by one until master ends the sequence */
#if defined(STM32L0xx)
      HAL_I2C_Slave_Seq_Receive_IT(hi2c, (uint8_t *) &(obj->i2cTxRxBuffer[obj->slaveRxNbData]),
                                          1, I2C_NEXT_FRAME);
#else
      HAL_I2C_Slave_Sequential_Receive_IT(hi2c, (uint8_t *) &(obj->i2cTxRxBuffer[obj->slaveRxNbData]),
                                          1, I2C_NEXT_FRAME);
#endif
    }
  }
}

/**
  * @brief  Listen Complete callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);

  /*  Previous master transaction now ended, so inform upper layer if needed
   *  then prepare for listening to next request */
  if((obj->i2c_onSlaveReceive != NULL) &&
    (obj->slaveMode == SLAVE_MODE_RECEIVE)) {
    if(obj->slaveRxNbData != 0) {
      obj->i2c_onSlaveReceive((uint8_t *) obj->i2cTxRxBuffer, obj->slaveRxNbData);
    }
  }
  obj->slaveMode = SLAVE_MODE_LISTEN;
  obj->slaveRxNbData = 0;
  HAL_I2C_EnableListen_IT(hi2c);
}

/**
  * @brief Slave RX complete callback
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);
  /* One more byte was received, store it then prepare next */
  if(obj->slaveRxNbData < I2C_TXRX_BUFFER_SIZE) {
    obj->slaveRxNbData++;
  } else {
    core_debug("ERROR: I2C Slave RX overflow\n");
  }
  /* Restart interrupt mode for next Byte */
  if(obj->slaveMode == SLAVE_MODE_RECEIVE) {
#if defined(STM32L0xx)
      HAL_I2C_Slave_Seq_Receive_IT(hi2c, (uint8_t *) &(obj->i2cTxRxBuffer[obj->slaveRxNbData]),
                                          1, I2C_NEXT_FRAME);
#else
      HAL_I2C_Slave_Sequential_Receive_IT(hi2c, (uint8_t *) &(obj->i2cTxRxBuffer[obj->slaveRxNbData]),
                                          1, I2C_NEXT_FRAME);
#endif
  }
}

/**
  * @brief Slave TX complete callback
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);
  /* Reset transmit buffer size */
  obj->i2cTxRxBufferSize = 0;
}

/**
  * @brief  I2C error callback.
  * @note   In master mode, the callback is not used because the error is reported
  *         to the Arduino API from i2c_master_write() and i2c_master_read().
  *         In slave mode, there is no mechanism in Arduino API to report an error
  *         so the error callback forces the slave to listen again.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);

  if(obj->isMaster == 0) {
    HAL_I2C_EnableListen_IT(hi2c);
  }
}

#if defined(I2C1_BASE)
/**
* @brief  This function handles I2C1 interrupt.
* @param  None
* @retval None
*/
void I2C1_EV_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[0];
  HAL_I2C_EV_IRQHandler(handle);
#if defined(STM32F0xx) || defined(STM32L0xx)
  HAL_I2C_ER_IRQHandler(handle);
#endif // defined(STM32F0xx) || defined(STM32L0xx)
}

#if !defined(STM32F0xx) && !defined(STM32L0xx)
/**
* @brief  This function handles I2C1 interrupt.
* @param  None
* @retval None
*/
void I2C1_ER_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[0];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
#endif // I2C1_BASE

#if defined(I2C2_BASE)
/**
* @brief  This function handles I2C2 interrupt.
* @param  None
* @retval None
*/
void I2C2_EV_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[1];
  HAL_I2C_EV_IRQHandler(handle);
#if defined(STM32F0xx) || defined(STM32L0xx)
  HAL_I2C_ER_IRQHandler(handle);
#endif // defined(STM32F0xx) || defined(STM32L0xx)
}

#if !defined(STM32F0xx) && !defined(STM32L0xx)
/**
* @brief  This function handles I2C2 interrupt.
* @param  None
* @retval None
*/
void I2C2_ER_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[1];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
#endif // I2C2_BASE

#if defined(I2C3_BASE)
/**
* @brief  This function handles I2C3 interrupt.
* @param  None
* @retval None
*/
void I2C3_EV_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[2];
  HAL_I2C_EV_IRQHandler(handle);
#if defined(STM32F0xx) || defined(STM32L0xx)
  HAL_I2C_ER_IRQHandler(handle);
#endif // defined(STM32F0xx) || defined(STM32L0xx)
}

#if !defined(STM32F0xx) && !defined(STM32L0xx)
/**
* @brief  This function handles I2C3 interrupt.
* @param  None
* @retval None
*/
void I2C3_ER_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[2];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
#endif // I2C3_BASE

#if defined(I2C4_BASE)
/**
* @brief  This function handles I2C4 interrupt.
* @param  None
* @retval None
*/
void I2C4_EV_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[3];
  HAL_I2C_EV_IRQHandler(handle);
#if defined(STM32F0xx) || defined(STM32L0xx)
  HAL_I2C_ER_IRQHandler(handle);
#endif // defined(STM32F0xx) || defined(STM32L0xx)
}

#if !defined(STM32F0xx) && !defined(STM32L0xx)
/**
* @brief  This function handles I2C4 interrupt.
* @param  None
* @retval None
*/
void I2C4_ER_IRQHandler(void)
{
  I2C_HandleTypeDef * handle = i2c_handles[3];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif // !defined(STM32F0xx) && !defined(STM32L0xx)
#endif // I2C4_BASE

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
