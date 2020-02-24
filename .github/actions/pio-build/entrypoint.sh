#!/bin/bash -x

CMSIS_VERSION=$1
CMSIS_ARCHIVE=CMSIS-${CMSIS_VERSION}.tar.bz2

# Install the development version of ststm32 platform
platformio platform install https://github.com/platformio/platform-ststm32.git

# Prepare framework for CI
python3 -c "import json; import os; fp=open(os.path.expanduser('~/.platformio/platforms/ststm32/platform.json'), 'r+'); data=json.load(fp); data['packages']['framework-arduinoststm32']['version'] = '*'; fp.seek(0); fp.truncate(); json.dump(data, fp); fp.close()"

ln -sf $GITHUB_WORKSPACE $HOME/.platformio/packages/framework-arduinoststm32
# Download and unpack CMSIS package
wget https://github.com/stm32duino/ArduinoModule-CMSIS/releases/download/$CMSIS_VERSION/CMSIS-$CMSIS_VERSION.tar.bz2
tar -xvjf CMSIS-$CMSIS_VERSION.tar.bz2
cd $GITHUB_WORKSPACE/CI/build/
python3 platformio-builder.py --board=blackpill_f103c8 --board=remram_v1

exit $?
