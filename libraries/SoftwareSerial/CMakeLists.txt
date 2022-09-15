
add_library(SoftwareSerial OBJECT EXCLUDE_FROM_ALL
  src/SoftwareSerial.cpp
)

target_include_directories(SoftwareSerial PUBLIC
  src
)
