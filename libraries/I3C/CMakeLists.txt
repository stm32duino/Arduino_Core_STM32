# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(I3C INTERFACE)
add_library(I3C_usage INTERFACE)

target_include_directories(I3C_usage INTERFACE
  src
)


target_link_libraries(I3C_usage INTERFACE
  base_config
)

target_link_libraries(I3C INTERFACE I3C_usage)



add_library(I3C_bin OBJECT EXCLUDE_FROM_ALL
  src/I3C.cpp
  src/I3C_I2C.cpp
)
target_link_libraries(I3C_bin PUBLIC I3C_usage)

target_link_libraries(I3C INTERFACE
  I3C_bin
  $<TARGET_OBJECTS:I3C_bin>
)
