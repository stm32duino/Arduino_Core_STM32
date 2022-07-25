# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(Keyboard INTERFACE)
add_library(Keyboard_usage INTERFACE)

target_include_directories(Keyboard_usage INTERFACE
  src
)


target_link_libraries(Keyboard_usage INTERFACE
  base_config
)

target_link_libraries(Keyboard INTERFACE Keyboard_usage)



add_library(Keyboard_bin OBJECT EXCLUDE_FROM_ALL
  src/Keyboard.cpp
)
target_link_libraries(Keyboard_bin PUBLIC Keyboard_usage)

target_link_libraries(Keyboard INTERFACE
  Keyboard_bin
  $<TARGET_OBJECTS:Keyboard_bin>
)

