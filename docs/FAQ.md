### When using "Mass Storage" upload method, following error is displayed:
`NODE_xxxxxx not found. Please ensure the device is correctly connected.`

#### ST-LINK firmware does not support Mass Storage

Some ST-LINK firmware types do not expose the Mass Storage interface. In this case, change the ST-LINK firmware type with [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html):

1. Connect the board to the computer and open STM32CubeProgrammer.
2. Open the **Firmware upgrade** tool.
3. Put the ST-LINK in update mode.
4. Enable **Change type** and select the firmware type that includes **Mass Storage**.
5. Click **Upgrade** and wait for the update to complete.

Reconnect or reset the board after the update, then try the Mass Storage upload method again.

If upload always fail then check the following:

- Verify this is the right board selected in Arduino IDE: "**Tools -> Boards Manager**"
- Verify if you board is correctly connected
- Verify if a mount point exists and check the mount point name. It should be the same than the one searched by the upload tool.

If not, then probably you have an older board with a different label used for the mount point.<br>
Update the `board.txt` file to add `<your_node_label>` to the targeted board.<br>
Example:<br>
`Nucleo_64.menu.pnum.NUCLEO_xxxxxx.node=NODE_xxxxxx`<br>
becomes<br>
`Nucleo_64.menu.pnum.NUCLEO_xxxxxx.node="NODE_xxxxxx,<your_node_label>"`

Node names list has to be separated by ',' and double quoted (for Windows).

### How do I know which (stm32duino/libmaple) core am I running on?

try this code
```C++
void setup() {
	Serial.begin();
}

void loop() {
#ifdef ARDUINO_ARCH_STM32
	Serial.println("stm32duino core");
#elif defined(ARDUINO_ARCH_STM32F1)
	Serial.println("libmaple core");
#elif defined(ARDUINO_ARCH_STM32F4)
	Serial.println("libmaple f4 core");
#else
	Serial.println("unknown core");
#endif
	delay(1000);
}
```

## Debug

Debug can not be functional using generic when some features are enabled. Example, with Generic L486 with USB enabled. When USB is initialized, it configures all the pins available in the `PinMap_USB_OTG_FS`:
https://github.com/stm32duino/Arduino_Core_STM32/blob/c6bc5b23761c30ff5ef08baa22af1519b0a76d5a/variants/STM32L4xx/L475V(C-E-G)T_L476V(C-E-G)T_L486VGT/PeripheralPins.c#L403-L411

In this case `PA_13` is `JTMS-SWDIO` preventing debug to be functional.
To avoid this, it is required to redefine the `PinMap_USB_OTG_FS` array to remove useless pins as explained [here](https://stm32duino.github.io/customization/Custom-definitions/#example-for-the-adc-pinmap-of-the-nucleo_f103rb), like this:

```C
const PinMap PinMap_USB_OTG_FS[] = {
  // {PA_8,  USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_SOF
  // {PA_9,  USB_OTG_FS, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, GPIO_AF_NONE)}, // USB_OTG_FS_VBUS
  // {PA_10, USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_ID
  {PA_11, USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_DM
  {PA_12, USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_DP
  // {PA_13, USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_NOE
  // {PC_9,  USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_NOE
  {NC,    NP,         0}
};
```

Discussed in [issue #2047](https://github.com/stm32duino/Arduino_Core_STM32/issues/2047).

## OS specific
### Linux

#### USB serial (CDC) stalls initially and connecting using a serial monitor fails

problem:

after a sketch is compiled and and firmware installed. on resetting the board.
In some Linux distributions. usb serial (cdc) initially stalls could be into the 10s of seconds after a reset. There is no response in the serial monitor (e.g. putty), in fact the serial monitor (e.g. putty) simply won't connect. running _dmesg_ command did show a /dev/ttyACMx device.

discussion and solution:

create a udev rules file e.g.
/etc/udev/rules.d/45-stm32duino.rules
add a line like
```
ATTRS{idProduct}=="5740", ATTRS{idVendor}=="0483", MODE="664", GROUP="plugdev" SYMLINK+="stm32duino" ENV{ID_MM_DEVICE_IGNORE}="1"
```
make sure that the product id and vendor id matches that used in your sketch.

the main thing is that
``
ENV{ID_MM_DEVICE_IGNORE}="1"
``
which tells udev not to treat it as a modem
that issue is explored in this thread
https://www.stm32duino.com/viewtopic.php?f=62&t=1000

### Windows:

#### When using "BMP (Black Magic Probe)" upload method, error occurs it can't connect to the COM port.

Refers to this [warning](Upload-methods.md#bmp-black-magic-probe)

