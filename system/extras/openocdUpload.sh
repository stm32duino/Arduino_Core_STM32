#!/bin/bash
OPENOCD_PATH="$1"
OPENOCD_EXTRA_SCRIPTS="$2"

if [ ! -f "${OPENOCD_EXTRA_SCRIPTS}/openocd.cfg" ]; then
    echo "Could not find ${OPENOCD_EXTRA_SCRIPTS}/openocd.cfg."
    exit 1
fi

# invoke openocd, using the default scripts directory from the openocd path, plus the additional scripts directory given,
# and finally all the other arguments passed to this script.
"${OPENOCD_PATH}/bin/openocd" -s "${OPENOCD_PATH}/openocd/scripts" -s "${OPENOCD_EXTRA_SCRIPTS}" -f openocd.cfg "${@:3}"
