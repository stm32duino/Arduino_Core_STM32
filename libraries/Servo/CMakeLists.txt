# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(Servo INTERFACE)
add_library(Servo_usage INTERFACE)

target_include_directories(Servo_usage INTERFACE
  src
)


target_link_libraries(Servo_usage INTERFACE
  base_config
)

target_link_libraries(Servo INTERFACE Servo_usage)



add_library(Servo_bin OBJECT EXCLUDE_FROM_ALL
  src/stm32/Servo.cpp
)
target_link_libraries(Servo_bin PUBLIC Servo_usage)

target_link_libraries(Servo INTERFACE
  Servo_bin
  $<TARGET_OBJECTS:Servo_bin>
)

