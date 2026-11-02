# SoftwareSerial

## Introduction

The SoftwareSerial library emulates a UART on any pair of GPIO pins. Its API
follows the official Arduino
[SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial/)
library and it derives from `Stream`, so `print()`, `println()`, `read()` and
`available()` are available.

## Usage

```Arduino
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
```

See the `SoftwareSerialExample` and `TwoPortReceive` examples of the library.

## Implementation

A **hardware timer** generates an interrupt at
`frequency = baudrate * OVERSAMPLE` (by default `3 * baudrate`) to handle the
reception and the transmission. This increases the CPU load, especially at a
high baud rate.

* Several instances can be created, but only one can receive at a time.
  Use `listen()` to select the receiving instance.
* The receive buffer holds `_SS_MAX_RX_BUFF` (64) bytes. `overflow()` reports
  that bytes were dropped.
* If the RX and TX pins are the same, the instance works in half-duplex mode.

## API

| Method | Description |
| ------ | ----------- |
| `SoftwareSerial(pin_size_t receivePin, pin_size_t transmitPin, bool inverse_logic = false)` | Creates an instance. Use the same pin for RX and TX for half-duplex. `inverse_logic` inverts the data level. |
| `void begin(long speed)` | Sets the baud rate and initializes the pins. Starts listening unless the instance is half-duplex. |
| `void end()` | Stops the instance and disables the timer interrupt. |
| `bool listen()` | Makes this instance the listening one. Returns `true` if it replaced another one or was not listening, `false` if it was already listening. |
| `bool isListening()` | Returns `true` if this instance is listening. |
| `bool stopListening()` | Stops listening. Waits for the pending output. |
| `bool overflow()` | Returns `true` if the receive buffer overflowed since the last call, then clears the flag. |
| `int available()` | Number of bytes in the receive buffer. |
| `int read()` | Reads a byte, `-1` if the buffer is empty. |
| `int peek()` | Returns the next byte without removing it, `-1` if the buffer is empty. |
| `size_t write(uint8_t byte)` | Sends a byte, waiting for any previous transmission. |
| `void flush()` | Clears the receive buffer and waits for the pending transmission. |
| `static void setInterruptPriority(uint32_t preemptPriority, uint32_t subPriority)` | Sets the priority of the timer interrupt shared by all instances. |

> [!NOTE]
> Define `FORCE_BAUD_RATE` to override the speed passed to `begin()`.
