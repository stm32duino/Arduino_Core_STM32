# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(core INTERFACE)
add_library(core_usage INTERFACE)

target_include_directories(core_usage INTERFACE
  .
)


target_link_libraries(core_usage INTERFACE
  base_config
)

target_link_libraries(core INTERFACE core_usage)



add_library(core_bin STATIC EXCLUDE_FROM_ALL
  abi.cpp
  avr/dtostrf.c
  board.c
  core_debug.c
  HardwareSerial.cpp
  hooks.c
  IPAddress.cpp
  itoa.c
  main.cpp
  pins_arduino.c
  Print.cpp
  RingBuffer.cpp
  stm32/startup_stm32yyxx.S
  stm32/usb/cdc/cdc_queue.c
  stm32/usb/cdc/usbd_cdc.c
  stm32/usb/cdc/usbd_cdc_if.c
  stm32/usb/hid/usbd_hid_composite.c
  stm32/usb/hid/usbd_hid_composite_if.c
  stm32/usb/usb_device_core.c
  stm32/usb/usb_device_ctlreq.c
  stm32/usb/usb_device_ioreq.c
  stm32/usb/usbd_conf.c
  stm32/usb/usbd_desc.c
  stm32/usb/usbd_ep_conf.c
  stm32/usb/usbd_if.c
  Stream.cpp
  Tone.cpp
  USBSerial.cpp
  WInterrupts.cpp
  wiring_analog.c
  wiring_digital.c
  wiring_pulse.cpp
  wiring_shift.c
  wiring_time.c
  WMath.cpp
  WSerial.cpp
  WString.cpp
)
target_link_libraries(core_bin PUBLIC core_usage)

target_link_libraries(core INTERFACE
  core_bin
)

