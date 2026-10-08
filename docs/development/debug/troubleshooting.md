# Troubleshooting

## The debug probe is not detected

- Check that the probe is connected to the computer and that its USB status LED is on.
- Check the SWD wiring: `SWDIO`, `SWCLK`, `GND`, and the target voltage reference (`Vref`) must be connected. Connect `NRST` as well when using reset-based connection or recovery.
- Make sure no other application is using the probe. Close STM32CubeProgrammer, OpenOCD, `st-util`, and other debugger sessions before trying again.
- On Linux, check that the required USB permissions or udev rules are installed for the probe.
- If the probe firmware is old, update it with the vendor's ST-LINK tools.

## The target cannot be halted or attached

- Confirm that the selected MCU and debug interface are correct. Use `SWD`, not `JTAG`, unless the board requires it.
- Reduce the SWD clock frequency, especially when using long wires or a custom board.
- Try connecting under reset and hold the board's reset button while starting the debug session. This can recover a target whose firmware disables or reconfigures the debug pins.
- Check that the target is powered and that the probe reports a valid target voltage.
- Disconnect external circuitry from the SWD pins if it may be driving or loading them.

## Breakpoints are not working or symbols are missing

- Compile the sketch with debug information enabled. In Arduino IDE 2, select **Optimize for debugging**.
- Start GDB with the ELF file produced by the same build that was uploaded to the board. A BIN or HEX file does not contain the symbols needed by GDB.
- Verify that the debugger's MCU, SVD file, and ELF path match the board and build being debugged.
- Clean and rebuild the sketch if source files, board settings, or optimization settings changed.
- Avoid high optimization levels when inspecting variables; the compiler may remove or rearrange code.

## The GDB server cannot start

- Check whether another debugger is already listening on the server port. Stop the other session or configure both GDB and the server to use the same available port.
- `st-util` normally listens on `localhost:4242`; OpenOCD commonly uses GDB port `3333`. Use the matching address in the GDB `target remote` command.
- Ensure that the selected GDB server supports the connected probe and target. A server started for ST-LINK cannot be used with an unrelated probe without the appropriate backend.

## The STM32 series is not supported by the OpenOCD version

- OpenOCD target support depends on the installed version and its target configuration scripts. An older package may not recognize a newer STM32 series or may not provide the required device configuration.
- Check the OpenOCD output for messages such as `Error: unknown device` or a missing target configuration file, then install a recent OpenOCD release that lists the required STM32 family as supported.
- If updating OpenOCD is not possible, use another supported GDB server, such as the ST-LINK GDB server included with STM32CubeCLT, or use STM32CubeProgrammer to verify that the probe and target can communicate.

## The board resets or loses the connection during debugging

- Check the USB cable, board power, target voltage, and SWD ground connection.
- Lower the SWD clock frequency and use shorter SWD wires.
- Check whether the sketch resets the MCU, enters low-power mode, or changes the SWD pins during startup.
- Try an attach session or connect-under-reset mode instead of launching and resetting the target automatically.
