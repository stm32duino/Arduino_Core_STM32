# Discovery kit with STM32MP157x MPU Series

This variant currently supports the following boards:

* [STM32MP157A-DK1]
* [STM32MP157C-DK2]

This port targets the Cortex-M4 coprocessor. __Note that the coprocessor is not a stand-alone microcontroller: the Arduino firmware for the coprocessor must be managed by the host Linux (Cortex-A side).__ In other words, [Cortex-M4 Engineering mode] is not supported and only Production mode is supported.

Because every OS may have different software configurations (especially Device Tree) not all Linux distributions for these boards are supported. The currently supported distributions are the following:

* [STM32MP15 Starter Package]
* [STM32 MPU OpenSTLinux Distribution]
* [Balena OS]

#### Note
 * Other distributions not listed here may run Arduino firmware but they are not tested.
 * __The first two OSes should select `stm32mp157c-dk2-m4-examples-sdcard` boot mode (or device tree configuration) on boot time.__
 * `stm32mp157c-dk2-sdcard` boot mode is also known to work but it is not guaranteed. See [ST Wiki page on boot mode] for more detail. If you are using it for your own OS, see the [Linux Device Tree considerations](#Linux-Device-Tree-considerations) section.

## How to use

After Verify and Upload, you will see a message similar to the following in Arduino IDE:

    <Arduino build output path>/run_arduino_<sketch name>.sh generated successfully.
    This file should be uploaded manually by SCP, SFTP, Kermit, or etc.
    Then run "sh ./run_arduino_<sketch name>.sh start" command in the board's console.
    For detailed instructions, please visit:
        https://github.com/stm32duino/Arduino_Core_STM32/tree/main/variants/STM32MP1xx/MP153AAC_MP153CAC_MP153DAC_MP153FAC_MP157AAC_MP157CAC_MP157DAC_MP157FAC

`<Arduino build output path>/run_arduino_<sketch name>.sh` looks like this for *Blink* example:

* Windows:

  `C:/Users/%USERNAME%/AppData/Local/Temp/arduino_build_668148/run_arduino.Blink.sh`

* Linux/macOS:

  `/tmp/arduino_build_668148/run_arduino_Blink.sh`

In this example, the user **must** upload `<Arduino build output path>/run_arduino_<sketch name>.sh` file manually. Uploading instruction is described later in the [Uploading](#Uploading) section.

After uploading the user can use `sh run_arduino_<sketch name>.sh start` in the console of host Linux via either SSH or Serial Console, to run the Arduino firmware.

#### Note

* `sh run_arduino_<sketch name>.sh start` is a one-shot command, the Arduino firmware only runs for the current boot. If you want to make it run after reboot, you need to use `sh run_arduino_<sketch name>.sh install` command.

`run_arduino_<sketch name>.sh` help page summary:

    Usage: sh run_arduino_<sketch name>.sh [start|stop|restart|generate|install|uninstall]

    run_arduino_<sketch name>.sh is a helper script that helps managing an Arduino binary
    file for the coprocessor using remoteproc framework.

    sh run_arduino_<sketch name>.sh start
        Upload the binary to the coprocessor then start it.
        This command must be executed while the script contains the binary
        after generate command is run.

    sh run_arduino_<sketch name>.sh install
        Run the binary on boot automatically by installing a systemd service.

    sh run_arduino_<sketch name>.sh uninstall
        Uninstall the autostart service.

    sh run_arduino_<sketch name>.sh monitor
        Monitor data received from the coprocessor via the virtual serial.

    sh run_arduino_<sketch name>.sh send-msg <message...>
        Send a message to the coprocessor via the virtual serial.

    sh run_arduino_<sketch name>.sh send-file <filename>
        Send a file content to the coprocessor via the virtual serial.

    sh run_arduino_<sketch name>.sh minicom
        Launch minicom interactive serial communication program.

    sh run_arduino_<sketch name>.sh log
        Print debugging log in OpenAMP trace buffer.

    sh run_arduino_<sketch name>.sh stop
        Stop the coprocessor.

    sh run_arduino_<sketch name>.sh restart
        Restart the coprocessor.

See the source code [run_arduino_gen.sh] for the full help page and the more details about the `run_arduino_<sketch name>.sh` generated.

[run_arduino_gen.sh] is the shell script that produces a copy of the script called `run_arduino_<sketch name>.sh` but with the sketch binary self-contained.

## Virtual Serial

With Virtual Serial, you can easily implement inter-core communication between the Linux host and Arduino coprocessor. Virtual Serial uses OpenAMP rpmsg framework. This is available as `SerialVirtIO` object and you can use it as a standard Arduino Serial object.

Enable `SerialVirtIO` in Arduino IDE->Tools->Virtual serial support. You can optionally alias generic `Serial` object with `SerialVirtIO` as well.

When enabled, `/dev/ttyRPMSG0` is available to the Linux host. You can use it as a normal serial tty. `sh run_arduino_<sketch name>.sh` provides `monitor`, `minicom`, `send-msg`, `send-file` as a convenience. See above command descriptions.

See [OpenAMP] and [Linux RPMsg] to learn more.

### Configuration

To increase the performance of SerialVirtIO you can resize the related buffer configurations. There are three definitions you can use:

* [`VRING_NUM_BUFFS`](/cores/arduino/stm32/OpenAMP/virtio_config.h)
* [`RPMSG_BUFFER_SIZE`](/cores/arduino/stm32/OpenAMP/virtio_config.h)
* [`VIRTIO_BUFFER_SIZE`](/cores/arduino/stm32/OpenAMP/virtio_buffer.h)

The recommended option is to resize `VRING_NUM_BUFFS`. Be very cautious when resizing `RPMSG_BUFFER_SIZE`, which must be matched with the Linux kernel definition. Also `VIRTIO_BUFFER_SIZE` has the minimum required size depending on the other two. See their links above for further descriptions.

#### Note

* Since openSTLinux distribution 4.0 with Linux 5.15, `RPMSG_SERVICE_NAME` has been renamed from `rpmsg-tty-channel` to `rpmsg-tty`, if older distribution is used, it is required to redefine it to  `rpmsg-tty-channel`

To redefine these definitions, see how to create `build_opt.h` described in Debugging section below.

### Virtual Serial Example

Here is a basic echo example:
```cpp
int available;
char buffer[1024];

unsigned long time = 0;

void setup() {
  // You can SerialVirtIO.begin() and use SerialVirtIO later instead.
  Serial.begin(); // You don't need to configure speed, it is ignored.
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

  // Heartbeat. If Arduino stops the LED won't flash anymore.
  if ((millis() - time) > 1000) {
    time = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
```

Note the use of `Serial.availableForWrite()`. SerialVirtIO has [a hard restriction of the write size], so it is important to `Serial.write()` less than the value of `Serial.availableForWrite()`.

After loading Arduino, You can use SerialVirtIO in two ways in this example:

* Run `sh run_arduino_<sketch name>.sh minicom` and type anything in the minicom console. The console will print out what you type immediately.

* Open two Linux consoles (using SSH)
  1. In the first console, run `sh run_arduino_<sketch name>.sh monitor`
  2. In the second console, run `sh run_arduino_<sketch name>.sh send-msg <your message>` or `sh run_arduino_<sketch name>.sh send-file <your file>`, the first console will print the content of the message.

## Debugging

For printf-style debugging, `core_debug()` is highly recommended instead of using Arduino Serial. In STM32MP1, `core_debug()` utilizes OpenAMP trace buffer and it has a minimal real-time impact (other than the overhead of printf) because it is not bound to the speed of a hardware IO peripheral while printing it.

Select `Core logs Enabled` in `Tools->Debug symbols and core logs`.
Additionally you can resize the buffer size of logging by redefining `VIRTIO_LOG_BUFFER_SIZE` (2kb by default).
Create [build_opt.h] in the sketch directory and simply put `-DVIRTIO_LOG_BUFFER_SIZE=xxxx`. As an example you can create a file like the following:

```
build_opt.h (in the same directory of your Sketch)
-----------------------------

-DVIRTIO_LOG_BUFFER_SIZE=4086
```

Don't forget to add `#include "core_debug.h"` in your code in order to use `core_debug()`.

Also, you must enable the Virtual Serial (described in the above section) and include `SerialVirtIO.begin();` in your Arduino sketch, because this logging feature is tightly coupled to OpenAMP virtio.

You can use `sh run_arduino_<sketch name>.sh log` command or `cat /sys/kernel/debug/remoteproc/remoteproc0/trace0` command to print out the debug log in the Linux host.

Note that when overflow occurs the trace buffer is re-written from the beginning, removing existing logs. Consider increasing `VIRTIO_LOG_BUFFER_SIZE` in this case, as mentioned above.

See [virtio_log.h] for more information.

### Debugging Example

Here is a basic blink example with `core_debug()`:
```cpp
#include "core_debug.h"

unsigned long time = 0;
unsigned long count = 1;

void setup() {
  // You must enable SerialVirtIO to use core_debug(), even if you don't use SerialVirtIO.
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

Don't forget to select `Core logs Enabled` in `Tools->Debug symbols and core logs` as described above.

After loading Arduino, you can simply `sh run_arduino_<sketch name>.sh log` to print the current `core_debug()` logs.

## Pin mapping

The boards have two pin headers: Raspberry Pi HAT headers and Arduino shield headers. This project currently supports Arduino Shield headers only, leaving RPi HAT headers for the Linux applications.

Note that PWM N channel (e.g. TIM1_CH3N) outputs negative output to the corresponding channel, meaning it outputs inverted duty cycle.

| Feature   | ST    | Arduino |   | Arduino | ST    | Feature   | PWM       |
|-----------|-------|:-------:|:-:|:-------:|-------|-----------|-----------|
|           |       |         |   |   SCL   | PA_11 | I2C5-SCL  | TIM1_CH4  |
|           |       |         |   |   SDA   | PA_12 | I2C5-SDA  |           |
|           |       |         |   |  Varef  |       |           |           |
|           |       |    NC   |   |    13   | PE_12 | SPI4-SCK  | TIM1_CH3N |
|           |       |    5V   |   |    12   | PE_13 | SPI4-MISO | TIM1_CH3  |
|           |       |   RST   |   |    11   | PE_14 | SPI4-MOSI | TIM1_CH4  |
|           |       |   3.3V  |   |    10   | PE_11 | SPI4-SS   | TIM1_CH2  |
|           |       |    5V   |   |    9    | PH_6  |           | TIM12_CH1 |
|           |       |   GND   |   |    8    | PG_3  |           |           |
|           |       |   GND   |   |         |       |           |           |
|           |       |   Vin   |   |    7    | PD_1  |           |           |
|           |       |         |   |    6    | PE_9  |           | TIM1_CH1  |
| ADC1_IN0  | PF_14 |    A0   |   |    5    | PD_15 |           | TIM4_CH4  |
| ADC1_IN1  | PF_13 |    A1   |   |    4    | PE_10 |           | TIM1_CH2N |
| ADC1_IN6  | ANA_0 |    A2   |   |    3    | PD_14 |           | TIM4_CH3  |
| ADC1_IN2  | ANA_1 |    A3   |   |    2    | PE_1  |           |           |
| ADC1_IN13 | PC_3  |    A4   |   |    1    | PE_8  | UART7-TX  | TIM1_CH1N |
| ADC1_IN14 | PF_12 |    A5   |   |    0    | PE_7  | UART7-RX  |           |

There are additional pins for LEDs and buttons.

| ST    | Arduino                       | Arduino (cont.)      | Comment                                          |
|-------|-------------------------------|----------------------|--------------------------------------------------|
| PA_14 | 16 / LED_GREEN                | USER1_BTN / USER_BTN | Active Low, LED LD5, also connected to B3 button |
| PA_13 | 17 / LED_RED                  | USER2_BTN            | Active Low, LED LD6, also connected to B4 button |
| PH_7  | 18 / LED_ORANGE / LED_BUILTIN |                      | Active High, LED LD7                             |

[`variant_STM32MP157_DK.h` of the board] has the complete information about the pinouts.

## Uploading

As mentioned above `run_arduino_<sketch name>.sh` file have to be uploaded manually from the PC to the board's Linux file system in order to be executed on the board directly through the board's Linux console. There are many ways to upload the file.

### Over Network

* **SCP** and **SFTP** are good options to upload the file, since STM32MP1 board runs SSH server by default. There are a lot of online resources on how to use them on the internet. Here is the default SSH access information:
```
host: (Varies. Search online to learn how to figure it out.)
username: root
password: (none by default)
```

### Over Serial

* **C-Kermit** is a combined network and serial communication software package that allows users to transfer files over serial connection. [The ST Wiki page on C-Kermit] describes how to use it.

## Linux Device Tree considerations

To use the Arduino firmware for a custom OS, the user need to take into account in the Linux Device Tree, since a peripheral cannot be shared between the Linux host and the Arduino firmware, and Arduino must occupy some peripherals.

For example, Arduino uses TIM1 for PWM `analogWrite()` implementation. The Device Tree must disable TIM1 for Linux usage like the following:
```
&timers1 {
	status = "disabled";
};
```

And then the Device Tree should enable TIM1 for the coprocessor, although this doesn't seems to be a strict requirement it is safer to do this:
```
&m4_timers1 {
	pinctrl-names = "rproc_default";
	pinctrl-0 = <&timer1_pins>;
	status = "okay";
};
```

[stm32mp157c-dk2-m4-examples.dts] is a great example to begin with. For the full list of peripherals used by the Arduino firmware, see [PeripheralPins_STM32MP157_DK.c](/variants/STM32MP1xx/MP153AAC_MP153CAC_MP153DAC_MP153FAC_MP157AAC_MP157CAC_MP157DAC_MP157FAC/PeripheralPins_STM32MP157_DK.c) of the board.

## Limitations

* Ethernet and USB are not supported. Use them in the Linux host.
* I2C pins on Raspberry Pi HAT header (GPIO2 and GPIO3) are not available in Linux host. This is because the Discovery board shares I2C pins on Arduino header and those on the HAT header.
* [Early firmware loading from U-Boot stage] is not supported. Only firmware loading on Linux boot stage by systemd (aka. `sh run_arduino_<sketch name>.sh install`) supported. The binary itself may be loaded by U-Boot without any problems, but there is no out-of-box tool to configure U-Boot to load the firmware using Arduino IDE yet.
* EEPROM library: Those devices do not have non-volatile memory. The emulation is done using RETRAM. Therefore data will be preserved *only* when VBAT is supplied (e.g. A coin battery is connected to CN3 on STM32MP157A_DK1) and the coprocessor is waken up from sleep. This implies that cold boot the board may cause data loss, even if VBAT is supplied. See [discussions on RETRAM] for more detail.



[STM32MP157A-DK1]: https://www.st.com/en/evaluation-tools/stm32mp157a-dk1.html
[STM32MP157C-DK2]: https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html

[Cortex-M4 Engineering mode]: https://wiki.st.com/stm32mpu/wiki/STM32CubeMP1_development_guidelines
[STM32MP15 Starter Package]: https://wiki.st.com/stm32mpu/wiki/STM32MP15_Discovery_kits_-_Starter_Package
[STM32 MPU OpenSTLinux Distribution]: https://wiki.st.com/stm32mpu/wiki/STM32MP1_Distribution_Package
[Balena OS]: https://github.com/kbumsik/balena-st-stm32mp
[ST Wiki page on boot mode]: https://wiki.st.com/stm32mpu/wiki/STM32CubeMP1_Package#Getting_started_with_STM32CubeMP1_Package

[run_arduino_gen.sh]: https://github.com/stm32duino/Arduino_Tools/blob/main/run_arduino_gen.sh

[OpenAMP]: https://github.com/OpenAMP/open-amp/wiki/OpenAMP-Overview
[Linux RPMsg]: https://wiki.st.com/stm32mpu/wiki/Linux_RPMsg_framework_overview
[a hard restriction of the write size]: /cores/arduino/VirtIOSerial.cpp#L148

[build_opt.h]: https://github.com/stm32duino/Arduino_Core_STM32/wiki/Customize-build-options-using-build_opt.h
[build_opt.h description in wiki]: https://github.com/stm32duino/Arduino_Core_STM32/wiki/Customize-build-options-using-build_opt.h
[virtio_log.h]: /cores/arduino/stm32/OpenAMP/virtio_log.h

[`variant_STM32MP157_DK.h` of the board]: /variants/STM32MP1xx/MP153AAC_MP153CAC_MP153DAC_MP153FAC_MP157AAC_MP157CAC_MP157DAC_MP157FAC/variant_STM32MP157_DK.h

[The ST Wiki page on C-Kermit]: https://wiki.st.com/stm32mpu/wiki/How_to_transfer_a_file_over_serial_console
[a bug in OpenSTLinux]: https://community.st.com/s/question/0D50X0000B9vHa4/cannot-get-download-a-file-using-kermit

[stm32mp157c-dk2-m4-examples.dts]: https://github.com/STMicroelectronics/meta-st-stm32mp/blob/d8cbac759e1275b1a27d4ba38b64a0d83d0e8c9f/recipes-kernel/linux/linux-stm32mp/4.19/4.19.49/0029-ARM-stm32mp1-r2-DEVICETREE.patch#L4334

[Early firmware loading from U-Boot stage]: https://wiki.st.com/stm32mpu/wiki/How_to_start_the_coprocessor_from_the_bootloader
[discussions on RETRAM]: https://community.st.com/s/question/0D50X0000B44pHUSQY/doesnt-the-mcu-coprocessor-have-nonvolatile-memory
