# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(Wire INTERFACE)
add_library(Wire_usage INTERFACE)

target_include_directories(Wire_usage INTERFACE
  src
)


target_link_libraries(Wire_usage INTERFACE
  base_config
)

target_link_libraries(Wire INTERFACE Wire_usage)



add_library(Wire_bin OBJECT EXCLUDE_FROM_ALL
  src/utility/twi.c
  src/Wire.cpp
)
target_link_libraries(Wire_bin PUBLIC Wire_usage)

target_link_libraries(Wire INTERFACE
  Wire_bin
  $<TARGET_OBJECTS:Wire_bin>
)

