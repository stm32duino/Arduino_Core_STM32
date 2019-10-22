/*
  Copyright (c) 2011 Arduino.  All right reserved.
  Copyright (c) 2018 MCCI Corporation.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "variant.h"
#include "stm32l0xx_ll_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
// This array allows to map Arduino pin number(Dx or x)
// to STM32 PinName (PX_n) -- don't forget to also change variant.h
const PinName digitalPin[] = {
//PX_n,  //Dx
  PA_10, //D0      D0_UART_RX		JP4-2
  PA_9,  //D1      D1_UART_TX		JP4-3
  PA_7,  //D2      RADIO_MOSI
  PA_6,  //D3      RADIO_MISO
  PB_3,  //D4      RADIO_SCK
  PB_6,  //D5      EN
  PA_13, //D6      D6_SWDIO		JP1-4
  PA_15, //D7      RADIO_NSS
  PC_0,  //D8      RADIO_RESET
  PA_14, //D9      D9_SWCLK		JP1-3
  PH_1,  //D10     D10
  PB_5,  //D11     D11
  PB_7,  //D12     D12
  PB_2,  //D13     D13
  PA_0,  //D14/A0  A0_VBAT_DET
  PA_5,  //D15/A1  A1
  PA_4,  //D16/A2  A2
  PA_3,  //D17/A3  A3_RS485_RX
  PA_2,  //D18/A4  A4_RS485_TX
  PB_12, //D19/A5  NSS
  PB_9,  //D20/A6  SDA
  PB_8,  //D21/A7  SCL
  PB_14, //D22/A8  MISO
  PB_15, //D23/A9  MOSI
  PB_13, //D24/A10 SCK
  PB_4,  //D25/A11 RADIO_DIO_0
  PB_1,  //D26/A12 RADIO_DIO_1
  PB_0,  //D27/A13 RADIO_DIO_2
  PC_13, //D28/A14 RADIO_DIO_3
  PA_1,  //D29/A15 RADIO_ANT_SWITCH_RX       CRF1
  PC_1,  //D30/A16 RADIO_ANT_SWITCH_TX_BOOST CRF3
  PC_2,  //D31/A17 RADIO_ANT_SWITCH_TX_RFO   CRF2
  NC,    //D32     Flash Write-Protect (not supported these platforms)
  PA_8,  //D33     RADIO_TCXO      TCXO VDD, possibly VDD boost enable.
};

#ifdef __cplusplus
}
#endif
