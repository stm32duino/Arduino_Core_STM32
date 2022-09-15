
add_library(RGB_LED_TLC59731 OBJECT EXCLUDE_FROM_ALL
  src/RGB_LED_TLC59731.cpp
)

target_include_directories(RGB_LED_TLC59731 PUBLIC
  src
)
