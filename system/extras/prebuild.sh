#!/bin/bash

BUILD_PATH="$1"
BUILD_SOURCE_PATH="$2"

# Create sketch dir if not exists
if [ ! -f "$BUILD_PATH/sketch" ]; then
  mkdir -p "$BUILD_PATH/sketch"
fi

# Create empty build.opt if build_opt.h does not exists in the original sketch dir
if [ ! -f "$BUILD_SOURCE_PATH/build_opt.h" ]; then
  touch "$BUILD_PATH/sketch/build.opt"
else
  # Else copy the build_opt.h as build.opt
  # Workaround to the header file preprocessing done by arduino-cli
  # See https://github.com/arduino/arduino-cli/issues/1338
  cp "$BUILD_SOURCE_PATH/build_opt.h" "$BUILD_PATH/sketch/build.opt"
fi

# Force include of SrcWrapper library
echo "#include <SrcWrapper.h>" > "$BUILD_PATH/sketch/SrcWrapper.cpp"
