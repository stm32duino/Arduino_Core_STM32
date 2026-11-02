# IWatchdog

## Introduction

The IWatchdog library provides an interface to the independent watchdog
(IWDG) of the STM32 microcontrollers. The IWDG generates a reset of the CPU
when the software becomes stuck or unresponsive.

The IWDG contains a down-counter. When it reaches zero, the microcontroller is
reset. In normal operation the software reloads the counter periodically to
prevent the reset. If a software error keeps the CPU away from the reload for
too long, the IWDG resets the CPU.

## Usage

The library is delivered with the STM32 core. Include its header in the sketch:

```Arduino
#include <IWatchdog.h>

void setup() {
  // Reset the CPU if the watchdog is not reloaded within 4 seconds.
  IWatchdog.begin(4000000);
}

void loop() {
  // ... code executed in less than 2 seconds to keep 50% headroom ...
  IWatchdog.reload();
}
```

A default instance named `IWatchdog` is available. See the `IWDG_Button`
example of the library.

> [!WARNING]
> Once started, the IWDG cannot be stopped. A debugging session can be reset
> by the watchdog while the CPU is halted. Also consider the watchdog when the
> CPU is put in a low power mode.

## Timeout and window

Timeouts are in **microseconds**. Plan to reload the counter at least twice as
often as the timeout: `reload()` is not expensive. A very large timeout leaves
the system stuck for a long time before the reset.

The valid range depends on the LSI clock. With a 32 kHz LSI it goes from 125 µs
to about 32.8 s, and the precision depends on the value:

| Timeout range       | Precision |
| ------------------- | --------- |
| 125 µs - 512 ms     | 125 µs    |
| 513 ms - 1024 ms    | 250 µs    |
| 1025 ms - 2048 ms   | 500 µs    |
| 2049 ms - 4096 ms   | 1 ms      |
| 4097 ms - 8192 ms   | 2 ms      |
| 8193 ms - 16384 ms  | 4 ms      |
| 16385 ms - 32768 ms | 8 ms      |

The optional window must be less than the timeout. When the window is enabled,
the counter has to be reloaded inside the window, otherwise a reset is
generated.

> [!NOTE]
> The window feature is not available on all STM32 series.

## API

| Method | Description |
| ------ | ----------- |
| `void begin(uint32_t timeout, uint32_t window = IWDG_TIMEOUT_MAX)` | Initializes and starts the IWDG. `timeout` and `window` are in microseconds. Returns without starting the IWDG if `timeout` is out of the valid range. |
| `void reload()` | Reloads the counter. Call it periodically once the IWDG is started. |
| `void set(uint32_t timeout, uint32_t window = IWDG_TIMEOUT_MAX)` | Sets the timeout and window values. Same parameters as `begin()`. |
| `void get(uint32_t *timeout, uint32_t *window = NULL)` | Gets the current timeout and window values, in microseconds. |
| `bool isEnabled()` | Returns `true` if the IWDG has been started. |
| `bool isReset(bool clear = false)` | Returns `true` if the last reset was caused by the IWDG. Clears the IWDG reset flag if `clear` is `true`. |
| `void clearReset()` | Clears the IWDG reset flag. |

| Constant | Description |
| -------- | ----------- |
| `IWDG_TIMEOUT_MIN` | Minimal timeout in microseconds. |
| `IWDG_TIMEOUT_MAX` | Maximal timeout in microseconds. |
