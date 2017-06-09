/**
  ******************************************************************************
  * @file    spi_com.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Header for spi module
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
#ifndef __SPI_COM_H
#define __SPI_COM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "PeripheralPins.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

struct spi_s {
    SPI_HandleTypeDef handle;
    SPI_TypeDef *spi;
    PinName pin_miso;
    PinName pin_mosi;
    PinName pin_sclk;
    PinName pin_ssel;
};

typedef struct spi_s spi_t;


///@brief specifies the SPI speed bus in HZ.
#define SPI_SPEED_CLOCK_DEFAULT     4000000

#define SPI_SPEED_CLOCK_DIV2_MHZ    ((uint32_t)2)
#define SPI_SPEED_CLOCK_DIV4_MHZ    ((uint32_t)4)
#define SPI_SPEED_CLOCK_DIV8_MHZ    ((uint32_t)8)
#define SPI_SPEED_CLOCK_DIV16_MHZ   ((uint32_t)16)
#define SPI_SPEED_CLOCK_DIV32_MHZ   ((uint32_t)32)
#define SPI_SPEED_CLOCK_DIV64_MHZ   ((uint32_t)64)
#define SPI_SPEED_CLOCK_DIV128_MHZ  ((uint32_t)128)
#define SPI_SPEED_CLOCK_DIV256_MHZ  ((uint32_t)256)

///@brief speficies the SPI mode to use
//Mode          Clock Polarity (CPOL)       Clock Phase (CPHA)
//SPI_MODE0             0                         0
//SPI_MODE1             0                         1
//SPI_MODE2             1                         0
//SPI_MODE3             1                         1
//enum definitions coming from SPI.h of SAM
typedef enum {
  SPI_MODE_0 = 0x00,
  SPI_MODE_1 = 0x01,
  SPI_MODE_2 = 0x02,
  SPI_MODE_3 = 0x03
}spi_mode_e;

///@brief SPI errors
typedef enum {
  SPI_OK = 0,
  SPI_TIMEOUT = 1,
  SPI_ERROR = 2
}spi_status_e;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void spi_init(spi_t *obj, uint32_t speed, spi_mode_e mode, uint8_t msb);
void spi_deinit(spi_t *obj);
spi_status_e spi_send(spi_t *obj, uint8_t *Data, uint16_t len, uint32_t Timeout);
spi_status_e spi_transfer(spi_t *obj, uint8_t * tx_buffer,
                      uint8_t * rx_buffer, uint16_t len, uint32_t Timeout);
uint32_t spi_getClkFreq(spi_t *obj);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_COM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
