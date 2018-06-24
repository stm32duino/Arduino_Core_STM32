# Adding MCCI Boards

The following template should be used as a starting point for adding a board in this STM32 BSP.

- `{{board}}` is conventionally `mcci_catena_{{modelnumber}}`.
- `{{modelnumber}}` is assigned by marketing; it's typically a number but might have a regional suffix. Characters should be chosen from C++ indentifier characters (`[a-zA-Z0-9_]`).
- `{{pid}}` is the USB product ID -- a 4-digit hex number.

```ini
#
# Configuration information for MCCI Catena {{modelnumber}} boards
# See template in https://github.com/mcci-catena/ArduinoCore-samd/MCCI-ADDING-BOARDS.md
#
{{board}}.name=MCCI Catena {{modelnumber}}
{{board}}.build.vid=0x040E
{{board}}.build.pid={{pid}}
{{board}}.vid.0=0x040E
{{board}}.pid.0={{pid}}

{{board}}.build.core=arduino
{{board}}.build.board=Catena
{{board}}.build.extra_flags=-D{build.product_line} {build.enable_usb} {build.xSerial}

{{board}}.node=NODE_CATENA_{{modelnumber}}
{{board}}.upload.maximum_size=196608
{{board}}.upload.maximum_data_size=20480
{{board}}.build.mcu=cortex-m0
{{board}}.build.board=MCCI_CATENA_{{modelnumber}}
{{board}}.build.series=STM32L0xx
{{board}}.build.product_line=STM32L082xx
{{board}}.build.variant=CATENA_{{modelnumber}}
{{board}}.build.cmsis_lib_gcc=arm_cortexM0l_math
{{board}}.build.extra_flags=-DARDUINO_STM32 -DARDUINO_{build.series} -DARDUINO_{build.product_line} -D{build.product_line} {build.enable_usb} {build.xSerial} -D__CORTEX_SC=0 -D{build.board} {build.lorawan_flags}

#
# menu.upload_method
#{{board}}.menu.upload_method.MassStorage=Mass Storage
#{{board}}.menu.upload_method.MassStorage.upload.protocol=
#{{board}}.menu.upload_method.MassStorage.upload.tool=massStorageCopy

{{board}}.menu.upload_method.DFU=DFU
{{board}}.menu.upload_method.DFU.upload.tool=stm32l0_dfu
{{board}}.menu.upload_method.DFU.upload.protocol=dfu
{{board}}.menu.upload_method.DFU.upload.maximum_size=196608
{{board}}.menu.upload_method.DFU.upload.maximum_data_size=20480
{{board}}.menu.upload_method.DFU.upload.use_1200bps_touch=true
{{board}}.menu.upload_method.DFU.upload.wait_for_upload_port=false
{{board}}.menu.upload_method.DFU.upload.native_usb=false

{{board}}.menu.upload_method.STLink=STLink
{{board}}.menu.upload_method.STLink.upload.protocol=STLink
{{board}}.menu.upload_method.STLink.upload.tool=stlink_upload

#{{board}}.menu.upload_method.Serial=Serial
#{{board}}.menu.upload_method.Serial.upload.protocol=Serial
#{{board}}.menu.upload_method.Serial.upload.tool=serial_upload

#
# menu.xserial
{{board}}.menu.xserial.none=No Serial
{{board}}.menu.xserial.generic=Generic Serial
{{board}}.menu.xserial.none.build.xSerial=-DNO_HWSERIAL
#{{board}}.menu.xserial.all=All (up to 10)
#{{board}}.menu.xserial.all.build.xSerial=-DALL_HWSERIAL
#{{board}}.menu.xserial.third=Enable first third (USART1 to 3 if available)
#{{board}}.menu.xserial.third.build.xSerial=-DFIRST_THIRD_HWSERIAL

#
# menu.usb
{{board}}.menu.usb.usb_device=USB Serial
{{board}}.menu.usb.usb_device.build.enable_usb={build.usb_flags}
{{board}}.menu.usb.none=No USB

#
# menu.opt
{{board}}.menu.opt.osstd=Smallest (-Os default)
{{board}}.menu.opt.osstd.build.flags.optimize=-Os
{{board}}.menu.opt.osstd.build.flags.ldspecs=
# {{board}}.menu.opt.oslto=Smallest (-Os) with LTO
# {{board}}.menu.opt.oslto.build.flags.optimize=-Os -flto
# {{board}}.menu.opt.oslto.build.flags.ldspecs=-flto
{{board}}.menu.opt.o1std=Fast (-O1)
{{board}}.menu.opt.o1std.build.flags.optimize=-O1
{{board}}.menu.opt.o1std.build.flags.ldspecs=
# {{board}}.menu.opt.o1lto=Fast (-O1) with LTO
# {{board}}.menu.opt.o1lto.build.flags.optimize=-O1 -flto
# {{board}}.menu.opt.o1lto.build.flags.ldspecs=-flto
{{board}}.menu.opt.o2std=Faster (-O2)
{{board}}.menu.opt.o2std.build.flags.optimize=-O2
{{board}}.menu.opt.o2std.build.flags.ldspecs=
# {{board}}.menu.opt.o2lto=Faster (-O2) with LTO
# {{board}}.menu.opt.o2lto.build.flags.optimize=-O2 -flto
# {{board}}.menu.opt.o2lto.build.flags.ldspecs=-flto
{{board}}.menu.opt.o3std=Fastest (-O3)
{{board}}.menu.opt.o3std.build.flags.optimize=-O3
{{board}}.menu.opt.o3std.build.flags.ldspecs=
# {{board}}.menu.opt.o3lto=Fastest (-O3) with LTO
# {{board}}.menu.opt.o3lto.build.flags.optimize=-O3 -flto
# {{board}}.menu.opt.o3lto.build.flags.ldspecs=-flto
{{board}}.menu.opt.ogstd=Debug (-g)
{{board}}.menu.opt.ogstd.build.flags.optimize=-Og -gdwarf-2
{{board}}.menu.opt.ogstd.build.flags.ldspecs=

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