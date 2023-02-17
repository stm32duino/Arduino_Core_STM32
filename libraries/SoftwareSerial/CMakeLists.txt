# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(SoftwareSerial INTERFACE)
add_library(SoftwareSerial_usage INTERFACE)

target_include_directories(SoftwareSerial_usage INTERFACE
  src
)


target_link_libraries(SoftwareSerial_usage INTERFACE
  base_config
)

target_link_libraries(SoftwareSerial INTERFACE SoftwareSerial_usage)



add_library(SoftwareSerial_bin OBJECT EXCLUDE_FROM_ALL
  src/SoftwareSerial.cpp
)
target_link_libraries(SoftwareSerial_bin PUBLIC SoftwareSerial_usage)

target_link_libraries(SoftwareSerial INTERFACE
  SoftwareSerial_bin
  $<TARGET_OBJECTS:SoftwareSerial_bin>
)

