#!/bin/sh

# Use python venv
python3 -m venv "$HOME/venv"
# shellcheck disable=SC1091
. "$HOME/venv/bin/activate"
# Install PlatformIO
python3 -m pip install --quiet --upgrade platformio

# Install the development version of ststm32 platform
pio pkg install --platform "https://github.com/platformio/platform-ststm32.git" --force --global || {
  exit 1
}
# Prepare framework for CI
# Modify platform.json to use local framework-arduinoststm32 package
python3 -c "import json; import os; fp=open(os.path.expanduser('~/.platformio/platforms/ststm32/platform.json'), 'r+'); data=json.load(fp); data['packages']['framework-arduinoststm32']['version'] = '*'; del data['packages']['framework-arduinoststm32']['owner']; fp.seek(0); fp.truncate(); json.dump(data, fp); fp.close()" || {
  exit 1
}
# Create symbolic link to the framework-arduinoststm32 package pointing to the repository workspace
ln --symbolic "$GITHUB_WORKSPACE" "$HOME/.platformio/packages/framework-arduinoststm32" || {
  exit 1
}
cd "$GITHUB_WORKSPACE/CI/build/" || {
  exit 1
}
python3 platformio-builder.py --board=malyanm300_f070cb --board=nucleo_l152re

exit $?
