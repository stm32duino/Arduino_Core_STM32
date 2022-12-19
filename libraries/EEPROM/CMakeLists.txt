

add_library(EEPROM OBJECT EXCLUDE_FROM_ALL
  src/utility/stm32_eeprom.c
)

target_include_directories(EEPROM PUBLIC
  src
)

target_link_libraries(EEPROM PUBLIC
  core_config
)



 