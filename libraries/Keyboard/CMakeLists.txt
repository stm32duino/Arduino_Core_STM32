
add_library(Keyboard OBJECT EXCLUDE_FROM_ALL
  src/Keyboard.cpp
)

target_include_directories(Keyboard PUBLIC
  src
)

target_link_libraries(Keyboard PUBLIC
  core_config
)