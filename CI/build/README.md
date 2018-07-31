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

Script is able to uses a JSON configuration file containing the build configuration for one or more maintainer/architecture. 
A default configuration file is provided: [cores_config.json](conf/cores_config.json)


#### Template
```json
{
  "cores": [
    {
      "maintainer": "maintainer/vendor name",
      "architecture": "architecture name",
      "boards": [
        {
          "name": "board1",
          "options": "specific options for board1 to concatenate with the fqbn"
        },
        {
          "name": "board2",
          "fqbn": "Fully Qualified Board Name and options, used instead of generated one"
        }
      ],
      "sketches": [
        {
          "pattern": "sketche(s) pattern",
          "applicable": true,
          "boards": [ "List of boards (comma separated) which can be built for the sketche(s) pattern. Only those listed board will be built." ],
          "options": "specific options to build the matched sketch pattern to concatenate with the fqbn (optional)"
        },
        {
          "pattern": "sketche(s) pattern",
          "applicable": false,
          "boards": [ "List of boards (comma separated) which cannot be built for the sketche(s) pattern. All others available boards will be built." ]
        }
      ]
    },
    {
      "maintainer": "Other maintainer/vendor name",
      "architecture": "Other architecture name",
      "boards": [
        {
          "name": "boardx",
          "options": "specific options for board1 to concatenate with the fqbn"
        }
      ],
      "sketches": [
        {
          "pattern": "sketchbook",
          "applicable": true,
          "boards": [ "" ]
        }
      ]
    }
  ]
}
```

#### Template

Will add `flash=C8` option to the fqbn of the BLUEPILL_F103C8 board
```json
  {
    "name": "BLUEPILL_F103C8",
    "options": "flash=C8"
  }
```

Will ignore `04.Communication/MultiSerial.ino` and `04.Communication/SerialPassthrough.ino`
```json
  {
    "pattern": "04.Communication/(Multi)?Serial(Passthrough)?",
    "applicable": true,
    "boards": [ "" ]
  }
```

Will build all sketch available in  `09.USB/*` for the listed boards and add `usb=HID` option to the fqbn
```json
  {
    "pattern": "09.USB",
    "applicable": true,
    "boards": [ "NUCLEO_F429ZI", "DISCO_L475VG_IOT", "DISCO_F407VG" ],
    "options": "usb=HID"
  }
```

## Usage examples

ToDo

