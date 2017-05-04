/*
  Copyright (c) 2011 Arduino.  All right reserved.

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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UARTClass.h"
#include "Arduino.h"

UARTClass::UARTClass(uart_id_e uart_id)
{
  p_uart_id = uart_id;
}
// Public Methods //////////////////////////////////////////////////////////////

void UARTClass::begin(const uint32_t dwBaudRate)
{
  uart_init(p_uart_id, dwBaudRate); 
}

void UARTClass::end( void )
{
  uart_deinit(p_uart_id);
}

int UARTClass::available( void )
{
  //return the amount of data available
  return uart_available(p_uart_id);
}

int UARTClass::peek( void )
{
  //return the last element of the rx buffer without removing it from the buffer
  return uart_peek(p_uart_id);;
}

int UARTClass::read( void )
{
  //return the last element of the rx buffer
  return uart_read(p_uart_id);
}

void UARTClass::flush( void )
{
  uart_flush(p_uart_id);
}

size_t UARTClass::write( const uint8_t uc_data )
{
  uart_write(p_uart_id, uc_data);
  return 1;
}
