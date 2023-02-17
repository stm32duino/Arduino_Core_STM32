#!/bin/bash

BUILD_PATH="$1"
BUILD_SOURCE_PATH="$2"
BOARD_PLATFORM_PATH="$3"

# Create sketch dir if not exists
if [ ! -f "$BUILD_PATH/sketch" ]; then
  mkdir -p "$BUILD_PATH/sketch"
fi

# Create empty build.opt if build_opt.h does not exists in the original sketch dir
# Then add or append -fmacro-prefix-map option to change __FILE__ absolute path of
# the board platform folder to a relative path by using '.'.
# (i.e. the folder containing boards.txt)
if [ ! -f "$BUILD_SOURCE_PATH/build_opt.h" ]; then
  printf '\n-fmacro-prefix-map="%s"=.' "${BOARD_PLATFORM_PATH//\\/\\\\}" > "$BUILD_PATH/sketch/build.opt"
else
  # Else copy the build_opt.h as build.opt
  # Workaround to the header file preprocessing done by arduino-cli
  # See https://github.com/arduino/arduino-cli/issues/1338
  cp "$BUILD_SOURCE_PATH/build_opt.h" "$BUILD_PATH/sketch/build.opt"
  printf '\n-fmacro-prefix-map="%s"=.' "${BOARD_PLATFORM_PATH//\\/\\\\}" >> "$BUILD_PATH/sketch/build.opt"
fi


# Force include of SrcWrapper library
echo "#include <SrcWrapper.h>" > "$BUILD_PATH/sketch/SrcWrapper.cpp"
