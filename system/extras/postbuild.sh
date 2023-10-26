#!/bin/bash

BUILD_PATH="$1"
BUILD_SERIE="$2"
BOARD_PLATFORM_PATH="$3"

[[ -n "$4" ]] && cfg="-$4" || cfg=""

OPENOCD_CONFIG="$BOARD_PLATFORM_PATH/variants/$BUILD_SERIE/openocd$cfg.cfg"

# Copy the correct openocd.cfg if exists
if [ ! -f "$OPENOCD_CONFIG" ]; then
  printf 'No %s available. Debug is not supported.' "$OPENOCD_CONFIG"
else
  # Always name the file 'openocd.cfg' even if the source name is different, since the name
  # is static in the debug.* configuration
  cp -f "$OPENOCD_CONFIG" "$BUILD_PATH/openocd.cfg"
fi
