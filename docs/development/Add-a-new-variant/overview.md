# Add a new variant (board)

## What is a variant?

It is described by Arduino [here](https://arduino.github.io/arduino-cli/latest/platform-specification/#core-variants)

> A core variant folder is an additional folder that is compiled together with the core and allows platform developers to easily add specific configurations.
>
> Variants must be placed inside the variants folder in the current architecture.

> [!NOTE]
> Since STM32 core release 2.0.0 the [variants folder] contains one folder for each STM32 MCU family.

> [!TIP]
> The example of all the steps below is available in [PR #1398](https://github.com/stm32duino/Arduino_Core_STM32/pull/1398).

??? example "Variants folders"

    ```text
    variants/
    |-- STM32C0xx/
    |-- STM32C5xx/
    |-- STM32F0xx/
    |-- STM32F1xx/
    |-- STM32F2xx/
    |-- STM32F3xx/
    |-- STM32F4xx/
    |-- STM32F7xx/
    |-- STM32G0xx/
    |-- STM32G4xx/
    |-- STM32H5xx/
    |-- STM32H7xx/
    |-- STM32L0xx/
    |-- STM32L1xx/
    |-- STM32L4xx/
    |-- STM32L5xx/
    |-- STM32MP1xx/
    |-- STM32U0xx/
    |-- STM32U3xx/
    |-- STM32U5xx/
    |-- STM32WB0x/
    |-- STM32WBAxx/
    |-- STM32WBxx/
    |-- STM32WL3x/
    `-- STM32WLxx/
    ```

Each MCU family has several MCU references. Each subfolder name can contain one or more mcu reference(s).

??? example "STM32G0xx family example"

    ```text
    STM32G0xx/
    |-- G030C(6-8)T/
    |-- G030F6P/
    |-- G030J6M/
    |-- G030K(6-8)T/
    |-- G031C(4-6-8)(T-U)_G041C(6-8)(T-U)/
    |-- G031F(4-6-8)P_G031Y8Y_G041F(6-8)P_G041Y8Y/
    |-- G031G(4-6-8)U_G041G(6-8)U/
    |-- G031J(4-6)M_G041J6M/
    |-- G031K(4-6-8)(T-U)_G041K(6-8)(T-U)/
    |-- G050C(6-8)T/
    |-- G050F6P/
    |-- G050K(6-8)T/
    |-- G051C(6-8)(T-U)_G061C(6-8)(T-U)/
    |-- G051F6P_G051F8(P-Y)_G061F6P_G061F8(P-Y)/
    |-- G051G(6-8)U_G061G(6-8)U/
    |-- G051K(6-8)(T-U)_G061K(6-8)(T-U)/
    |-- G070CBT/
    |-- G070KBT/
    |-- G070RBT/
    |-- G071C(6-8-B)(T-U)_G081CB(T-U)/
    |-- G071EBY_G081EBY/
    |-- G071G(6-8-B)U_G081GBU/
    |-- G071G(8-B)UxN_G081GBUxN/
    |-- G071K(6-8-B)(T-U)_G081KB(T-U)/
    |-- G071K(8-B)(T-U)xN_G081KB(T-U)xN/
    |-- G071R(6-8)T_G071RB(I-T)_G081RB(I-T)/
    |-- G0B0CET/
    |-- G0B0KET/
    |-- G0B0RET/
    |-- G0B0VET/
    |-- G0B1C(B-C-E)(T-U)_G0C1C(C-E)(T-U)/
    |-- G0B1C(B-C-E)(T-U)xN_G0C1C(C-E)(T-U)xN/
    |-- G0B1K(B-C-E)(T-U)_G0C1K(C-E)(T-U)/
    |-- G0B1K(B-C-E)(T-U)xN_G0C1K(C-E)(T-U)xN/
    |-- G0B1M(B-C-E)T_G0C1M(C-E)T/
    |-- G0B1NEY_G0C1NEY/
    |-- G0B1R(B-C-E)(I-T)xN_G0C1R(C-E)(I-T)xN/
    |-- G0B1R(B-C-E)T_G0C1R(C-E)T/
    `-- G0B1V(B-C-E)(I-T)_G0C1V(C-E)(I-T)/
    ```

MCU name are factorized to avoid long path names, for example:

[`G0B1R(B-C-E)T_G0C1R(C-E)T`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/variants/STM32G0xx/G0B1R(B-C-E)T_G0C1R(C-E)T) is for `G0B1RBT`, `G0B1RCT`, `G0B1RET`, `G0C1RCT` and `G0C1RET`.

All generic variants are now automatically generated in the variant folder thanks the [STM32_open_pin_data] repository which provides all the information required for the pin configuration of products based on STM32 MCU.

This means that the generic STM32 MCU files required for a variant are generated inside each MCU folder. Only the linker script is not automatically generated. Note that the default system clock configuration is empty by default. So the default clock at reset will be used.

### Generated variant files

> [!WARNING]
> Below files are automatically generated so do not modify them. Only the `generic_clock.c` can be modified to add default system clock configuration and so will not be overwritten.

 * `board_entry.txt`: contains generic variant declaration to ease board addition in the [`boards.txt`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/boards.txt) file. See [Arduino boards.txt specification].
 * `generic_clock.c`: contains the default system clock configuration: `WEAK void SystemClock_Config(void)`
 * `PinNamesVar.h`: contains specific [`PinName`](../../Pin-naming.md#pinname-constants) definitions of the MCU
 * `PeripheralPins.c`: contains list of available [`PinName`](../../Pin-naming.md#pinname-constants) per peripheral.
 * `variant_generic.cpp`: contains Digital PinName array and Analog (`Ax`) [pin number] array
 * `variant_generic.h`: contains all definition required by the variant: STM32 [pin number] definitions, peripheral pins for default instances: Serial, I2C, SPI, Tone, Servo, ...

Use the dedicated workflows from the submenu:

- [Define a new generic variant](generic-variant.md)
- [Define a dedicated board](dedicated-board.md)

---

> [!TIP]
> If you have any issue with the following guide. Do not hesitate to ask question on the [stm32duino Github discussions](https://github.com/orgs/stm32duino/discussions) or the [stm32duino forum](http://stm32duino.com).

[pin number]: ../../Pin-naming.md#arduino-pin-numbers-and-variant-aliases
[variants folder]: https://github.com/stm32duino/Arduino_Core_STM32/tree/main/variants
[Arduino boards.txt specification]: https://arduino.github.io/arduino-cli/latest/platform-specification/#boardstxt
[CheckVariant example]: https://github.com/stm32duino/STM32Examples/tree/main/examples/NonReg/CheckVariant
[Nucleo-G0B1RE]: https://www.st.com/en/evaluation-tools/nucleo-g0b1re.html
[STM32_open_pin_data]: https://github.com/STMicroelectronics/STM32_open_pin_data
[STM32CubeMX]: http://www.st.com/en/development-tools/stm32cubemx.html
[Arduino_Core_STM32]: https://github.com/stm32duino/Arduino_Core_STM32
