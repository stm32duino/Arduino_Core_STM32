# arduino-builder.py

This script manages _[arduino-builder](https://github.com/arduino/arduino-builder)_ command line tool for compiling Arduino sketch(es).

## Requirements
- [Arduino IDE](https://www.arduino.cc/en/Main/Software) (_[arduino-builder](https://github.com/arduino/arduino-builder)_ is included) 
- Python version greater than or equal to  3.2 (due to `concurrent.futures` usage)

## Usage

```
usage: arduino-builder.py [-h] [-l [{board,sketch}] | -a] [-b pattern] [-c]
                          [--arch architecture]
                          [--config <core configuration file>] [-v]
                          [--bin | --travis]
                          [-i <shetch filepath> | -f <sketches list filepath> | -s pattern | -e <excluded sketches list filepath>]

Manage arduino-builder command line tool for compiling Arduino sketch(es).

optional arguments:
  -h, --help            show this help message and exit
  -l [{board,sketch}], --list [{board,sketch}]
                        list available board(s) or sketch(es)
  -a, --all             build all sketches found for all available boards
  -b pattern, --board pattern
                        pattern to find one or more board(s) to build
  -c, --clean           clean output directory
                        <user patch config>/arduinoBuilderOutput
  --arch architecture   core architecture to build. Default build architecture
                        is stm32
  --config <core configuration file>
                        JSON file containing the build configuration for one
                        or more maintainer/architecture. Board options for
                        build, applicability of sketches for boards or
                        required options. If sketch is not listed then
                        applicable to all board. Default core configuration is
                        for 'stm32' architecture in: <user patch config>/arduino-
                        builder/conf/cores_config.json
  -v, --verbose         enable arduino-builder verbose mode
  --bin                 save binaries
  --travis              Custom configuration for Travis CI build

Sketch(es) options:
  By default build <user patch config>/arduino/examples/01.Basics/Blink/Blink.ino

  -i <shetch filepath>, --ino <shetch filepath>
                        single ino file to build
  -f <sketches list filepath>, --file <sketches list filepath>
                        file containing list of sketches to build
  -s pattern, --sketches pattern
                        pattern to find one or more sketch to build
  -e <excluded sketches list filepath>, --exclude <excluded sketches list filepath>
                        file containing pattern of sketches to ignore. Default
                        path : <user patch config>/arduino-builder/conf/exclude_list.txt
```

## Cores configuration files

ToDo

## Usage examples

ToDo

