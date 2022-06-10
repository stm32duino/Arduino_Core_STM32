
add_library(Mouse OBJECT EXCLUDE_FROM_ALL
  src/Mouse.cpp
)

target_include_directories(Mouse PUBLIC
  src
)

target_link_libraries(Mouse PUBLIC
  core_config
)