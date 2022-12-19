

add_library(Servo OBJECT EXCLUDE_FROM_ALL
  src/stm32/Servo.cpp
)

target_include_directories(Servo PUBLIC
  src
)

target_link_libraries(Servo PUBLIC
  core_config
)



 