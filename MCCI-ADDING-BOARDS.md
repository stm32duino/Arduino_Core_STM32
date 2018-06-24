# Adding MCCI Boards

The following template should be used as a starting point for adding a board.

- `{{board}}` is conventionally `mcci_catena_{{modelnumber}}`.
- `{{modelnumber}}` is assigned by marketing; it's to be hoped that it will be a number only!
- `{{pid}}` is the USB product ID -- a 4-digit hex number.

```ini
#
# Configuration information for MCCI Catena {{modelnumber}} boards
# See template in https://github.com/mcci-catena/ArduinoCore-samd/MCCI-ADDING-BOARDS.md
#
{{board}}.name=Catena {{modelnumber}}
{{board}}.upload.tool=bossac
{{board}}.upload.protocol=sam-ba
{{board}}.upload.maximum_size=262144
{{board}}.upload.use_1200bps_touch=true
{{board}}.upload.wait_for_upload_port=true
{{board}}.upload.native_usb=true
{{board}}.build.mcu=cortex-m0plus
{{board}}.build.f_cpu=48000000L
{{board}}.build.usb_product="MCCI Catena {{modelnumber}}"
{{board}}.build.usb_manufacturer="MCCI Corporation"
{{board}}.build.board=MCCI_CATENA_{{modelnumber}}
{{board}}.build.core=arduino
{{board}}.build.extra_flags=-DARDUINO_SAMD_ZERO -DARDUINO_SAMD_FEATHER_M0 -DMCCI_CATENA_{{modelnumber}} -D__SAMD21G18A__ {build.usb_flags} {build.lorawan_flags}
{{board}}.build.ldscript=linker_scripts/gcc/flash_with_bootloader.ld
{{board}}.build.openocdscript=openocd_scripts/arduino_zero.cfg
{{board}}.build.variant=arduino_zero
{{board}}.build.variant_system_lib=
{{board}}.build.vid=0x040E
{{board}}.build.pid=0x{{pid}}
{{board}}.bootloader.tool=openocd
{{board}}.bootloader.file=feather/samd21_sam_ba.bin
#
# menu.lorawan_region
{{board}}.menu.lorawan_region.us915=North America 915 MHz
{{board}}.menu.lorawan_region.eu868=Europe 868 MHz
{{board}}.menu.lorawan_region.au921=Australia 921 MHz
{{board}}.menu.lorawan_region.as923=Asia 923 MHz
{{board}}.menu.lorawan_region.as923jp=Japan 923 MHz
{{board}}.menu.lorawan_region.in866=India 866 MHz
{{board}}.menu.lorawan_region.projcfg=Use arduino-lmic/project_confic/lmic_project_lmic_config_preconditions.h
{{board}}.menu.lorawan_region.us915.build.lorawan_flags=-DCFG_us915=1 -DCFG_sx1276_radio=1 -DARDUINO_LMIC_PROJECT_CONFIG_H=lmic_config_preconditions.h
{{board}}.menu.lorawan_region.eu868.build.lorawan_flags=-DCFG_eu868=1 -DCFG_sx1276_radio=1 -DARDUINO_LMIC_PROJECT_CONFIG_H=lmic_config_preconditions.h
{{board}}.menu.lorawan_region.au921.build.lorawan_flags=-DCFG_au921=1 -DCFG_sx1276_radio=1 -DARDUINO_LMIC_PROJECT_CONFIG_H=lmic_config_preconditions.h
{{board}}.menu.lorawan_region.as923.build.lorawan_flags=-DCFG_as923=1 -DCFG_sx1276_radio=1 -DARDUINO_LMIC_PROJECT_CONFIG_H=lmic_config_preconditions.h
{{board}}.menu.lorawan_region.as923jp.build.lorawan_flags=-DCFG_as923=1 -DLMIC_COUNTRY_CODE=LMIC_COUNTRY_CODE_JP -DCFG_sx1276_radio=1 -DARDUINO_LMIC_PROJECT_CONFIG_H=lmic_config_preconditions.h
{{board}}.menu.lorawan_region.in866.build.lorawan_flags=-DCFG_in866=1 -DCFG_sx1276_radio=1 -DARDUINO_LMIC_PROJECT_CONFIG_H=lmic_config_preconditions.h
{{board}}.menu.lorawan_region.projcfg.build.lorawan_flags=

#### end of MCCI Catena {{modelnumber}}
```