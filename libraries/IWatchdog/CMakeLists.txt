
add_library(IWatchdog OBJECT EXCLUDE_FROM_ALL
  src/IWatchdog.cpp
)

target_include_directories(IWatchdog PUBLIC
  src
)
