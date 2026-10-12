# Discovery kit with STM32MP157x MPU Series

## Supported boards

Since core version **1.8.0**, the following boards are supported:

- [STM32MP157A-DK1](https://www.st.com/en/evaluation-tools/stm32mp157a-dk1.html)
- [STM32MP157C-DK2](https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html)

This port targets the Cortex-M4 coprocessor. The coprocessor is not a stand-alone microcontroller: the Arduino firmware for it must be managed by the host Linux system on the Cortex-A side. [Cortex-M4 Engineering mode] is not supported; only Production mode is supported.

Because operating systems may have different software configurations, especially Device Tree settings, not all Linux distributions are supported. The currently supported distributions are:

- [STM32MP15 Starter Package](https://wiki.st.com/stm32mpu/wiki/STM32MP15_Discovery_kits_-_Starter_Package)
- [STM32 MPU OpenSTLinux Distribution](https://wiki.st.com/stm32mpu/wiki/STM32MP1_Distribution_Package)
- [Balena OS](https://github.com/kbumsik/balena-st-stm32mp)

Other distributions may run Arduino firmware but are not tested. The STM32MP15 Starter Package and OpenSTLinux should select the `stm32mp157c-dk2-m4-examples-sdcard` boot mode, or equivalent Device Tree configuration, at boot. The `stm32mp157c-dk2-sdcard` boot mode is also known to work but is not guaranteed. See the [ST Wiki boot-mode documentation](https://wiki.st.com/stm32mpu/wiki/STM32CubeMP1_Package#Getting_started_with_STM32CubeMP1_Package) for details.

## How to use

After Verify and Upload, Arduino IDE generates a script similar to:

```text
<Arduino build output path>/run_arduino_<sketch name>.sh
```

And displays a message similar to:

```text
    <Arduino build output path>/run_arduino_<sketch name>.sh generated successfully.
    This file should be uploaded manually by SCP, SFTP, Kermit, or etc.
    Then run "sh ./run_arduino_<sketch name>.sh start" command in the board's console.
    For detailed instructions, please visit:
        https://stm32duino.github.io/STM32MP1/
```

Upload the generated script manually to the board's Linux file system. Uploading instruction is described later in the [Uploading](#uploading) section. Then run this command from the host Linux console, using SSH or a serial console:

```sh
sh run_arduino_<sketch name>.sh start
```

For example, the generated file is located under the Arduino build path, such as `/tmp/arduino_build_668148/run_arduino_Blink.sh` on Linux/macOS or `C:/Users/%USERNAME%/AppData/Local/Temp/arduino_build_668148/run_arduino_Blink.sh` on Windows.

The `start` command runs the Arduino firmware for the current boot only. To run it automatically after reboot, install the generated service:

```sh
sh run_arduino_<sketch name>.sh install
```

The generated script also supports `stop`, `restart`, `uninstall`, `monitor`, `send-msg`, `send-file`, `minicom`, and `log`. See [`run_arduino_gen.sh`](https://github.com/stm32duino/Arduino_Tools/blob/main/run_arduino_gen.sh) for the complete help text and script implementation.

## Virtual Serial

Virtual Serial uses the OpenAMP RPMsg framework for communication between the Linux host and the Arduino coprocessor. It is available through the `SerialVirtIO` object and can be used like a standard Arduino `Serial` object.

Enable **Virtual serial support** in **Arduino IDE > Tools**. You can optionally alias the generic `Serial` object to `SerialVirtIO`. When enabled, `/dev/ttyRPMSG0` is available on the Linux host.

The generated script provides `monitor`, `minicom`, `send-msg`, and `send-file` convenience commands. See the [OpenAMP overview](https://github.com/OpenAMP/open-amp/wiki/OpenAMP-Overview) and [Linux RPMsg documentation](https://wiki.st.com/stm32mpu/wiki/Linux_RPMsg_framework_overview) for background.

### Configuration

The following definitions control the related buffers:

- [`VRING_NUM_BUFFS`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/libraries/VirtIO/inc/virtio_config.h)
- [`RPMSG_BUFFER_SIZE`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/libraries/VirtIO/inc/virtio_config.h)
- [`VIRTIO_BUFFER_SIZE`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/libraries/VirtIO/inc/virtio_buffer.h)

The recommended option is to resize `VRING_NUM_BUFFS`. Be cautious when resizing `RPMSG_BUFFER_SIZE`, which must match the Linux kernel definition. `VIRTIO_BUFFER_SIZE` has a minimum required size derived from the other two settings.

Since OpenSTLinux 4.0 with Linux 5.15, `RPMSG_SERVICE_NAME` has been renamed from `rpmsg-tty-channel` to `rpmsg-tty`. For older distributions, redefine it to `rpmsg-tty-channel`.

To redefine these settings, use a `build_opt.h` file as described in [Customize build options](customization/Customize-build-options-using-build_opt.h.md).

### Virtual Serial example

```cpp
int available;
char buffer[1024];
unsigned long start_time = 0;

void setup() {
  Serial.begin(); // The baud rate is ignored.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  available = Serial.available();
  while (available > 0) {
    int size = min(available, Serial.availableForWrite());
    Serial.readBytes(buffer, size);
    Serial.write(buffer, size);
    available -= size;
  }

  if ((millis() - start_time) > 1000) {
    start_time = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
```

`SerialVirtIO` has a hard write-size limit, so write no more than `Serial.availableForWrite()` bytes at a time. See the [implementation limit](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/libraries/VirtIO/src/VirtIOSerial.cpp#L148).

After loading Arduino, You can use SerialVirtIO in two ways in this example:

1- Run `sh run_arduino_<sketch name>.sh minicom` and type anything in the minicom console. The console will print out what you type immediately.

2- Open two Linux consoles (using SSH)

  * In the first console, run `sh run_arduino_<sketch name>.sh monitor`
  * In the second console, run `sh run_arduino_<sketch name>.sh send-msg <your message>` or `sh run_arduino_<sketch name>.sh send-file <your file>`, the first console will print the content of the message.


## Debugging

For printf-style debugging, `core_debug()` is recommended instead of Arduino Serial. On STM32MP1, it uses the OpenAMP trace buffer and is not bound to the speed of a hardware I/O peripheral.

Enable **Core logs Enabled** in **Tools > Debug symbols and core logs**. You can resize the log buffer by creating `build_opt.h` in the sketch directory:

```c
-DVIRTIO_LOG_BUFFER_SIZE=4086
```

Include `core_debug.h` and enable `SerialVirtIO.begin()` because the logging feature uses OpenAMP virtio. Print logs with:

```sh
sh run_arduino_<sketch name>.sh log
```

Alternatively, read the Linux trace buffer directly with `cat /sys/kernel/debug/remoteproc/remoteproc0/trace0`. When the trace buffer overflows, old logs are overwritten. See [`virtio_log.h`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/libraries/VirtIO/inc/virtio_log.h) for more information.

### Debugging example

```cpp
#include "core_debug.h"

unsigned long time = 0;
unsigned long count = 1;

void setup() {
  SerialVirtIO.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if ((millis() - time) > 1000) {
    time = millis();
    core_debug("%u seconds\n", count++);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
```

## Pin mapping

The boards have Raspberry Pi HAT headers and Arduino shield headers. This port currently supports the Arduino shield headers; the HAT headers remain available to Linux applications. PWM N channels, such as `TIM1_CH3N`, produce an inverted duty cycle on the corresponding output.

| Feature | ST | Arduino | | Arduino | ST | Feature | PWM |
| --- | --- | :---: | :-: | :---: | --- | --- | --- |
| | | | | SCL | PA_11 | I2C5-SCL | TIM1_CH4 |
| | | | | SDA | PA_12 | I2C5-SDA | |
| | | Varef | | | | | |
| | | NC | | 13 | PE_12 | SPI4-SCK | TIM1_CH3N |
| | | 5V | | 12 | PE_13 | SPI4-MISO | TIM1_CH3 |
| | | RST | | 11 | PE_14 | SPI4-MOSI | TIM1_CH4 |
| | | 3.3V | | 10 | PE_11 | SPI4-SS | TIM1_CH2 |
| | | 5V | | 9 | PH_6 | | TIM12_CH1 |
| | | GND | | 8 | PG_3 | | |
| | | GND | | | | | |
| | | Vin | | 7 | PD_1 | | |
| ADC1_IN0 | PF_14 | A0 | | 6 | PE_9 | | TIM1_CH1 |
| ADC1_IN1 | PF_13 | A1 | | 5 | PD_15 | | TIM4_CH4 |
| ADC1_IN6 | ANA_0 | A2 | | 4 | PE_10 | | TIM1_CH2N |
| ADC1_IN2 | ANA_1 | A3 | | 3 | PD_14 | | TIM4_CH3 |
| ADC1_IN13 | PC_3 | A4 | | 2 | PE_1 | | |
| ADC1_IN14 | PF_12 | A5 | | 1 | PE_8 | UART7-TX | TIM1_CH1N |
| | | | | 0 | PE_7 | UART7-RX | |

Additional pins are available for LEDs and buttons:

| ST | Arduino | Arduino (continued) | Comment |
| --- | --- | --- | --- |
| PA_14 | 16 / LED_GREEN | USER1_BTN / USER_BTN | Active low, LED LD5, also connected to B3 button |
| PA_13 | 17 / LED_RED | USER2_BTN | Active low, LED LD6, also connected to B4 button |
| PH_7 | 18 / LED_ORANGE / LED_BUILTIN | | Active high, LED LD7 |

See the [complete board variant pin definitions](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/variants/STM32MP1xx/MP153AAC_MP153CAC_MP153DAC_MP153FAC_MP157AAC_MP157CAC_MP157DAC_MP157FAC/variant_STM32MP157_DK.h) for the full mapping.

## Uploading

The generated `run_arduino_<sketch name>.sh` file must be uploaded manually from the PC to the board's Linux file system before it can be executed by the board console. SCP and SFTP are convenient because the board normally runs an SSH server. C-Kermit can transfer the generated script over a serial connection; see the [ST Wiki C-Kermit guide](https://wiki.st.com/stm32mpu/wiki/How_to_transfer_a_file_over_serial_console).

## Linux Device Tree considerations

The Linux host and Arduino firmware cannot share a peripheral. A custom OS Device Tree must reserve the peripherals used by the Arduino firmware.

For example, Arduino uses `TIM1` for the `analogWrite()` PWM implementation. Disable `TIM1` for Linux:

```dts
&timers1 {
    status = "disabled";
};
```

Then enable `TIM1` for the coprocessor:

```dts
&m4_timers1 {
    pinctrl-names = "rproc_default";
    pinctrl-0 = <&timer1_pins>;
    status = "okay";
};
```

The [`stm32mp157c-dk2-m4-examples.dts` example](https://github.com/STMicroelectronics/meta-st-stm32mp/blob/d8cbac759e1275b1a27d4ba38b64a0d83d0e8c9f/recipes-kernel/linux/linux-stm32mp/4.19/4.19.49/0029-ARM-stm32mp1-r2-DEVICETREE.patch#L4334) is a useful starting point. See the [complete peripheral pin map](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/variants/STM32MP1xx/MP153AAC_MP153CAC_MP153DAC_MP153FAC_MP157AAC_MP157CAC_MP157FAC/PeripheralPins_STM32MP157_DK.c) for the peripherals used by the Arduino firmware.

## Limitations

- Ethernet and USB are not supported by the Arduino coprocessor port; use them from the Linux host.
- I2C pins on the Raspberry Pi HAT header, GPIO2 and GPIO3, are not available to the Linux host because the Discovery board shares them with the Arduino header.
- Early firmware loading from the U-Boot stage is not supported. Firmware loading is supported during the Linux boot stage through systemd, using `sh run_arduino_<sketch name>.sh install`.
- The EEPROM library uses RETRAM because these devices do not have non-volatile memory. Data is preserved only when VBAT is supplied and the coprocessor is woken from sleep. A cold boot can still cause data loss. See the [ST Community RETRAM discussion](https://community.st.com/s/question/0D50X0000B44pHUSQY/doesnt-the-mcu-coprocessor-have-nonvolatile-memory) for details.


[Cortex-M4 Engineering mode]: https://wiki.st.com/stm32mpu/wiki/How_to_use_engineering_and_production_modes
