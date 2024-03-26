#!/bin/sh -

BUILD_PATH="$1"
BUILD_SOURCE_PATH="$2"
BOARD_PLATFORM_PATH="$3"

# Create sketch dir if not exists
if [ ! -f "$BUILD_PATH/sketch" ]; then
  mkdir -p "$BUILD_PATH/sketch"
fi

# Create empty build.opt or clear it if build_opt.h does not exists in the original sketch dir
if [ ! -f "$BUILD_SOURCE_PATH/build_opt.h" ]; then
  true >"$BUILD_PATH/sketch/build.opt"
else
  # Else copy the build_opt.h as build.opt
  # Workaround to the header file preprocessing done by arduino-cli
  # See https://github.com/arduino/arduino-cli/issues/1338
  cp -f "$BUILD_SOURCE_PATH/build_opt.h" "$BUILD_PATH/sketch/build.opt"
fi
# On Windows, need to protect '\' in path
UNAME_OS="$(uname -s)"
case "${UNAME_OS}" in
  Windows*)
    i=1
    prefix=""
    while [ "$i" -le "${#BOARD_PLATFORM_PATH}" ]; do
      c=$(printf '%s' "$BOARD_PLATFORM_PATH" | cut -c $i)
      prefix=${prefix}${c}
      if [ "${c}" = "\\" ]; then
        prefix=${prefix}"\\"
      fi
      i="$((i + 1))"
    done
    ;;
  *)
    prefix=${BOARD_PLATFORM_PATH}
    ;;
esac
# Then append -fmacro-prefix-map option to change __FILE__ absolute path of
# the board platform folder to a relative path by using '.'.
# (i.e. the folder containing boards.txt)
printf '\n-fmacro-prefix-map="%s"=.' "${prefix}" >>"$BUILD_PATH/sketch/build.opt"

# Force include of SrcWrapper library
echo "#include <SrcWrapper.h>" >"$BUILD_PATH/sketch/SrcWrapper.cpp"
