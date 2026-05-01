# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(Mouse_STM32 INTERFACE)
add_library(Mouse_STM32_usage INTERFACE)

target_include_directories(Mouse_STM32_usage INTERFACE
  src
)


target_link_libraries(Mouse_STM32_usage INTERFACE
  base_config
)

target_link_libraries(Mouse_STM32 INTERFACE Mouse_STM32_usage)



add_library(Mouse_STM32_bin OBJECT EXCLUDE_FROM_ALL
  src/Mouse_STM32.cpp
)
target_link_libraries(Mouse_STM32_bin PUBLIC Mouse_STM32_usage)

target_link_libraries(Mouse_STM32 INTERFACE
  Mouse_STM32_bin
  $<TARGET_OBJECTS:Mouse_STM32_bin>
)

