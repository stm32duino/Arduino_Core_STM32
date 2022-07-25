# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(RGB_LED_TLC59731 INTERFACE)
add_library(RGB_LED_TLC59731_usage INTERFACE)

target_include_directories(RGB_LED_TLC59731_usage INTERFACE
  src
)


target_link_libraries(RGB_LED_TLC59731_usage INTERFACE
  base_config
)

target_link_libraries(RGB_LED_TLC59731 INTERFACE RGB_LED_TLC59731_usage)



add_library(RGB_LED_TLC59731_bin OBJECT EXCLUDE_FROM_ALL
  src/RGB_LED_TLC59731.cpp
)
target_link_libraries(RGB_LED_TLC59731_bin PUBLIC RGB_LED_TLC59731_usage)

target_link_libraries(RGB_LED_TLC59731 INTERFACE
  RGB_LED_TLC59731_bin
  $<TARGET_OBJECTS:RGB_LED_TLC59731_bin>
)

