#!/bin/bash

BUILD_PATH="$1"
BUILD_SOURCE_PATH="$2"
BUILD_PROJECT_NAME="$3"

# Create sketch dir if not exists
if [ ! -f "$BUILD_PATH/sketch" ]; then
  mkdir -p "$BUILD_PATH/sketch"
fi

# Create empty build.opt.h if not exists in the original sketch dir
if [ ! -f "$BUILD_SOURCE_PATH/build_opt.h" ]; then
  touch "$BUILD_PATH/sketch/build_opt.h"
fi

# add build options in source comments
if [ -f "$BUILD_SOURCE_PATH/$BUILD_PROJECT_NAME" ]; then
  grep '\/\/ build-opt' "$BUILD_SOURCE_PATH/$BUILD_PROJECT_NAME" | sed -e 's/\/\/ build-opt//' >> "$BUILD_PATH/sketch/build_opt.h"
fi

# Force include of SrcWrapper library
echo "#include <SrcWrapper.h>" >"$BUILD_PATH/sketch/SrcWrapper.cpp"
