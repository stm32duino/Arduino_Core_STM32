## STORM32_V1_31_RC

Big thanks to Olliw for creating this board.
http://www.olliw.eu/storm32bgc-wiki/STorM32_Boards

There are many versions of this board:
http://www.olliw.eu/storm32bgc-wiki/STorM32_Boards#STorM32-BGC_v1.3

This board is specifically for the more common 'STM32F103*RC*T' flash size (not RB, RE or RG). It is typically used as a 3 axis gimbal controller,
but can be used as a generic ESC if care is taken to limit voltage/current.  
It is probably only suitable for motors with phase resistance > 1ohm

This board has been used successfully with SimpleFOC Arduino library with a variety of magnetic sensors.

The following ports have been tested:
 - Serial3 - for rx/tx print.  You'll need a ftdi usb/serial converter.
 - SerialUSB - for rx/tx print.  This is (possibly) slightly less reliable than Serial3.
 - SWD - for flashing and debugging.  Requires stlink.
 - I2C1 - for magnetic sensor, etc
 - I2C2 - as above

 SPI2 is possible with desoldering/rewiring of LED1 to reclaim SPI2_SCK.
