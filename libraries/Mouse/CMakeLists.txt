# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(Mouse INTERFACE)
add_library(Mouse_usage INTERFACE)

target_include_directories(Mouse_usage INTERFACE
  src
)


target_link_libraries(Mouse_usage INTERFACE
  base_config
)

target_link_libraries(Mouse INTERFACE Mouse_usage)



add_library(Mouse_bin OBJECT EXCLUDE_FROM_ALL
  src/Mouse.cpp
)
target_link_libraries(Mouse_bin PUBLIC Mouse_usage)

target_link_libraries(Mouse INTERFACE
  Mouse_bin
  $<TARGET_OBJECTS:Mouse_bin>
)

