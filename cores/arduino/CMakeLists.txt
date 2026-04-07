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
  api/CanMsg.cpp
  api/CanMsgRingbuffer.cpp
  api/Common.cpp
  api/IPAddress.cpp
  api/PluggableUSB.cpp
  api/Print.cpp
  api/Stream.cpp
  api/String.cpp
  avr/dtostrf.c
  board.c
  core_debug.c
  HardwareSerial.cpp
  hooks.c
  itoa.c
  main.cpp
  pins_arduino.c
  stm32/startup_stm32yyxx.S
  Tone.cpp
  WInterrupts.cpp
  wiring_analog.c
  wiring_digital.c
  wiring_pulse.cpp
  wiring_shift.c
  wiring_time.c
  WMath.cpp
  WSerial.cpp
)
target_link_libraries(core_bin PUBLIC core_usage)

target_link_libraries(core INTERFACE
  core_bin
)

