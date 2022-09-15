
add_library(Mouse OBJECT EXCLUDE_FROM_ALL
  src/Mouse.cpp
)

target_include_directories(Mouse PUBLIC
  src
)
