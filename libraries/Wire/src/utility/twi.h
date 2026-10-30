/**
  ******************************************************************************
  * @file    twi.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Header for twi module
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TWI_H__
#define __TWI_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "PeripheralPins.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/**
 * @brief Manual implementation of offsetof (a gcc built-in function).
 * @param type Structure type.
 * @param member Member of the structure.
 */
#define OFFSETOF(type, member) ((uint32_t) (&(((type *)(0))->member)))

/**
 * @def I2C_IRQ_PRIO
 * @brief I2C interrupt preemption priority.
 *        Can be overridden before including this file.
 */
#ifndef I2C_IRQ_PRIO
#define I2C_IRQ_PRIO       2
#endif
/**
 * @def I2C_IRQ_SUBPRIO
 * @brief I2C interrupt sub-priority.
 *        Can be overridden before including this file.
 */
#ifndef I2C_IRQ_SUBPRIO
#define I2C_IRQ_SUBPRIO    0
#endif

/**
 * @def I2C_TXRX_BUFFER_SIZE
 * @brief Size in bytes of the slave Tx/Rx buffer of an i2c_t object.
 *        Can be overridden before including this file.
 * @note The size cannot exceed 255.
 */
#if !defined(I2C_TXRX_BUFFER_SIZE)
#define I2C_TXRX_BUFFER_SIZE    32
#elif (I2C_TXRX_BUFFER_SIZE >= 256)
#error I2C buffer size cannot exceed 255
#endif

/* Redefinition of IRQ for C0/F0/G0/L0/U0 families */
#if defined(STM32C0xx) || defined(STM32F0xx) || defined(STM32G0xx) ||\
    defined(STM32L0xx) || defined(STM32U0xx) || defined(STM32WB0x) || \
    defined(STM32WL3x)
#if defined(I2C1_BASE)
#define I2C1_EV_IRQn        I2C1_IRQn
#define I2C1_EV_IRQHandler  I2C1_IRQHandler
#endif // defined(I2C1_BASE)
#if defined(I2C2_BASE)
#if (defined(STM32G0xx) || defined(STM32U0xx)) && defined(I2C3_BASE)
#if defined(I2C4_BASE)
#define I2C2_EV_IRQn        I2C2_3_4_IRQn
#define I2C2_EV_IRQHandler  I2C2_3_4_IRQHandler
#else
#define I2C2_EV_IRQn        I2C2_3_IRQn
#define I2C2_EV_IRQHandler  I2C2_3_IRQHandler
#endif // defined(I2C4_BASE)
#else
#define I2C2_EV_IRQn        I2C2_IRQn
#define I2C2_EV_IRQHandler  I2C2_IRQHandler
#endif
#endif // defined(I2C2_BASE)
#if defined(I2C3_BASE)
#if defined(STM32G0xx) || defined(STM32U0xx)
#if defined(I2C4_BASE)
#define I2C3_EV_IRQn        I2C2_3_4_IRQn
#else
#define I2C3_EV_IRQn        I2C2_3_IRQn
#endif
#else
#define I2C3_EV_IRQn        I2C3_IRQn
#define I2C3_EV_IRQHandler  I2C3_IRQHandler
#endif
#endif // defined(I2C3_BASE)
/* Defined but no one has it */
#if defined(I2C4_BASE)
#if defined(STM32U0xx)
#define I2C4_EV_IRQn        I2C2_3_4_IRQn
#else
#define I2C4_EV_IRQn        I2C4_IRQn
#define I2C4_EV_IRQHandler  I2C4_IRQHandler
#endif
#endif // defined(I2C4_BASE)
#endif /* STM32C0xx || STM32F0xx || STM32G0xx || STM32L0xx || STM32U0xx */

/**
 * @brief I2C object type, see i2c_s.
 */
typedef struct i2c_s i2c_t;

/**
 * @brief I2C peripheral context: instance, HAL handle, pins, interrupts and slave buffers.
 * @note The first two members (i2c and handle) must be kept first
 * for the get_i2c_obj() function to work as expected.
 */
struct i2c_s {
  /*  The 1st 2 members I2CName i2c
     *  and I2C_HandleTypeDef handle should
     *  be kept as the first members of this struct
     *  to have get_i2c_obj() function work as expected
     */
  /** I2C peripheral instance. */
  I2C_TypeDef  *i2c;
  /** HAL handle of the I2C peripheral. */
#if defined(USE_HALV2_DRIVER)
  hal_i2c_handle_t handle;
#else
  I2C_HandleTypeDef handle;
#endif /* USE_HALV2_DRIVER */
  /** Pointer to the owning TwoWire instance, used by the slave callbacks. */
  void *__this;
  /** SDA pin. */
  PinName sda;
  /** SCL pin. */
  PinName scl;
  /** Event interrupt number. */
  IRQn_Type irq;
#if !defined(STM32C0xx) && !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
  /** Error interrupt number. */
  IRQn_Type irqER;
#endif /* !STM32C0xx && !STM32F0xx && !STM32G0xx && !STM32L0xx */
  /** Number of accumulated bytes received in slave mode. */
  volatile int slaveRxNbData;
  /** Callback called when the slave has received data from the master. */
  void (*i2c_onSlaveReceive)(i2c_t *);
  /** Callback called when the master requests data from the slave. */
  void (*i2c_onSlaveTransmit)(i2c_t *);
  /** Slave Tx/Rx buffer, I2C_TXRX_BUFFER_SIZE bytes. */
  volatile uint8_t i2cTxRxBuffer[I2C_TXRX_BUFFER_SIZE];
  /** Number of bytes currently stored in i2cTxRxBuffer for transmission. */
  volatile uint8_t i2cTxRxBufferSize;
  /**
   * Current slave mode: SLAVE_MODE_TRANSMIT, SLAVE_MODE_RECEIVE or SLAVE_MODE_LISTEN.
   */
  volatile uint8_t slaveMode;
  /** true when the peripheral is configured as master, false as slave. */
  bool isMaster;
  /** true to enable the general call address (slave mode). */
  bool generalCall;
  /** true to disable clock stretching (slave mode). */
  bool NoStretchMode;
};

/**
 * @brief I2C status returned by the i2c_* functions.
 */
typedef enum {
  /** Operation completed successfully. */
  I2C_OK = 0,
  /** Data does not fit in the buffer. */
  I2C_DATA_TOO_LONG = 1,
  /** Address was not acknowledged (NACK). */
  I2C_NACK_ADDR = 2,
  /** Data was not acknowledged (NACK). */
  I2C_NACK_DATA = 3,
  /** Other error. */
  I2C_ERROR = 4,
  /** Operation timed out. */
  I2C_TIMEOUT = 5,
  /** Bus or peripheral is busy. */
  I2C_BUSY = 6
} i2c_status_e;

/* Exported functions ------------------------------------------------------- */
/**
 * @brief Initialize and set up the GPIO pins and the I2C peripheral.
 * @param obj Pointer to the i2c_t structure.
 * @param timing I2C clock frequency in Hz.
 * @param ownAddress Own address already shifted left by 1 (7-bit address << 1).
 */
void i2c_init(i2c_t *obj, uint32_t timing, uint32_t ownAddress);
/**
 * @brief Deinitialize the GPIO pins and the I2C peripheral.
 * @param obj Pointer to the i2c_t structure.
 */
void i2c_deinit(i2c_t *obj);
/**
 * @brief Set the transmission speed.
 *        The I2C peripheral must be initialized before.
 * @param obj Pointer to the i2c_t structure.
 * @param frequency I2C transmission speed in Hz.
 */
void i2c_setTiming(i2c_t *obj, uint32_t frequency);
/**
 * @brief Write bytes to a device at a given address.
 *
 * A size of 0 checks whether the device is ready (scan / ping) instead of writing.
 * @param obj Pointer to the i2c_t structure.
 * @param dev_address 7-bit address of the device.
 * @param data Pointer to the data to write.
 * @param size Number of bytes to write.
 * @return I2C_OK on success, otherwise the i2c_status_e error code.
 */
i2c_status_e i2c_master_write(i2c_t *obj, uint8_t dev_address, uint8_t *data, uint16_t size);
/**
 * @brief Buffer bytes to send to the master in slave transmit mode.
 * @param obj Pointer to the i2c_t structure.
 * @param data Pointer to the data to buffer.
 * @param size Number of bytes to buffer, at most I2C_TXRX_BUFFER_SIZE.
 * @return I2C_OK on success, I2C_DATA_TOO_LONG if size exceeds I2C_TXRX_BUFFER_SIZE.
 */
i2c_status_e i2c_slave_write_IT(i2c_t *obj, uint8_t *data, uint16_t size);
/**
 * @brief Read bytes from a device at a given address in master mode.
 * @param obj Pointer to the i2c_t structure.
 * @param dev_address 7-bit address of the device.
 * @param data Pointer to the buffer receiving the data.
 * @param size Number of bytes to read.
 * @return I2C_OK on success, otherwise the i2c_status_e error code.
 */
i2c_status_e i2c_master_read(i2c_t *obj, uint8_t dev_address, uint8_t *data, uint16_t size);

/**
 * @brief Check whether the target device is ready for communication.
 * @param obj Pointer to the i2c_t structure.
 * @param devAddr 7-bit address of the device.
 * @param trials Number of trials.
 * @return I2C_OK if the device is ready, I2C_NACK_ADDR if it does not answer,
 *         otherwise the i2c_status_e error code.
 */
i2c_status_e i2c_IsDeviceReady(i2c_t *obj, uint8_t devAddr, uint32_t trials);

/**
 * @brief Set the function called when the slave receives data from a master.
 * @param obj Pointer to the i2c_t structure.
 * @param function Callback function to use, called with the i2c_t structure.
 */
void i2c_attachSlaveRxEvent(i2c_t *obj, void (*function)(i2c_t *));
/**
 * @brief Set the function called when a master requests data from the slave.
 * @param obj Pointer to the i2c_t structure.
 * @param function Callback function to use, called with the i2c_t structure.
 */
void i2c_attachSlaveTxEvent(i2c_t *obj, void (*function)(i2c_t *));

#ifdef __cplusplus
}
#endif

#endif /* __TWI_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
