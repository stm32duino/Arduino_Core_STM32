
add_library(Servo OBJECT EXCLUDE_FROM_ALL
  src/stm32/Servo.cpp
)

target_include_directories(Servo PUBLIC
  src
)
