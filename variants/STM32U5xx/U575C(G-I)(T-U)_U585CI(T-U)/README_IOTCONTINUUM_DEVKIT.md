## Pinout


### Outer PINs

| I/O Pins | Arduino | STM32U585 |
| --- | --- | --- |
| 13 | IO13 | GPIO6 Expander |
| 12 | D12 | PB13 |
| 11 | D11 | PA11 |
| 10 | D10 | PA8 |
| 9 | D9 | PB15 |
| 6 | D6 | PB14 |
| 5 | D5 | PB10 |
| 4 | IO4 | GPIO1 Expander |
| SCL | D17 | PB6 |
| SDA | D18 | PB7 |
| RX/D1 | D1 | PA3 |
| TX/D0 | D0 | PA2 |
| A0 | A0/D2 | PA0 |
| A1 | A1/D3 | PA1 |
| A2 | A2/D4 | PA6 |
| A3 | A3/D7 | PB0 |
| A4 | A4/D8 | PB1 |
| A5 | A5/D13 | PB2 |
| SCK | D14 | PB3 |
| MISO | D15 | PB4 |
| MOSI | D16 | PB5 |

### Inner PINs

| I/O Pins | Arduino | STM32U585 | Comment |
| --- | --- | --- | --- |
| BAT_LEVEL | BAT_LEVEL | PA4 | Battery level |
| USB_UART_RX | PIN_SERIAL_RX | PA5 | RX to USB |
| USB_UART_TX | PIN_SERIAL_TX | PA7 | TX to USB |
| MODULE_TX | PIN_SERIAL3_TX | PA9 | TX to HL7812 |
| MODULE_RX | PIN_SERIAL3_RX | PA10 | RX to HL7812 |
| BUTTON | USER_BTN | PA12 | Push button status |
| SWDIO | NC | PA13 | J-TAG Programming |
| SWCLK | NC | PA14 | J-TAG Programming |
| WAKE_UP | WAKE_UP_HL7812 | PA15 | Module wake up on sleep |
| VGPIO | VGPIO | PC13 | Module state (active/on sleep) |
| SEL_MODE_UART | SWITCH_TO_HL7812 | PB8 | UART mode activation (STM32 or HL7812) |
| RESET MODULE | RESET_HL7812 | PB12 | Module Reset |
| INT2_ACCEL | INT_ACCEL | PB9 | LSM6DSOX interrupt state |
| LED RGB | RED_LED, GREEN_LED, BLUE_LED | NC | Led R=GPIO3, G=GPIO4, B=GPIO5 Expander |
