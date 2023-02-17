# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(EEPROM INTERFACE)
add_library(EEPROM_usage INTERFACE)

target_include_directories(EEPROM_usage INTERFACE
  src
)


target_link_libraries(EEPROM_usage INTERFACE
  base_config
)

target_link_libraries(EEPROM INTERFACE EEPROM_usage)



add_library(EEPROM_bin OBJECT EXCLUDE_FROM_ALL
  src/utility/stm32_eeprom.c
)
target_link_libraries(EEPROM_bin PUBLIC EEPROM_usage)

target_link_libraries(EEPROM INTERFACE
  EEPROM_bin
  $<TARGET_OBJECTS:EEPROM_bin>
)

