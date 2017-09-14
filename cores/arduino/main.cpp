/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"


// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need HAL may fail.
 __attribute__(( constructor (101))) void premain() {
    init();
}

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
	initVariant();

#if defined(USBCON)
	usbd_interface_init();
#endif

	setup();

	for (;;)
	{
		CoreCallback();
		loop();
		if (serialEventRun) serialEventRun();
	}

	return 0;
}
