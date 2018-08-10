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
                        <user path config>/arduinoBuilderOutput
  --arch architecture   core architecture to build. Default build architecture
                        is stm32
  --config <core configuration file>
                        JSON file containing the build configuration for one
                        or more maintainer/architecture. Board options for
                        build, applicability of sketches for boards or
                        required options. If sketch is not listed then
                        applicable to all board. Default core configuration is
                        for 'stm32' architecture in: conf/cores_config.json
  -v, --verbose         enable arduino-builder verbose mode
  --bin                 save binaries
  --travis              Custom configuration for Travis CI build

Sketch(es) options:
  By default build <arduino path>/examples/01.Basics/BareMinimum/BareMinimum.ino

  -i <shetch filepath>, --ino <shetch filepath>
                        single ino file to build
  -f <sketches list filepath>, --file <sketches list filepath>
                        file containing list of sketches to build
  -s pattern, --sketches pattern
                        pattern to find one or more sketch to build
  -e <excluded sketches list filepath>, --exclude <excluded sketches list filepath>
                        file containing pattern of sketches to ignore. Default
                        path : conf/exclude_list.txt
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

#### Examples

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

Will build all sketches available in  `09.USB/*` for the listed boards and add `usb=HID` option to the fqbn
```json
  {
    "pattern": "09.USB",
    "applicable": true,
    "boards": [ "NUCLEO_F429ZI", "DISCO_L475VG_IOT", "DISCO_F407VG" ],
    "options": "usb=HID"
  }
```

## Usage examples

* List all boards containing `F1` or `L4` (not case sensitive):

`python3 arduino-builder.py -l -b "F1|l4"`

Will produce on the [stm32](https://github.com/stm32duino/Arduino_Core_STM32) core:
```
Cores configuration JSON file that will be used: conf/cores_config.json
Build configuration for 'STM32' maintainer and 'stm32' architecture
9 board(s) available
BLUEPILL_F103C8
DISCO_F100RB
DISCO_L475VG_IOT
MAPLEMINI_F103CB
NUCLEO_F103RB
NUCLEO_L432KC
NUCLEO_L476RG
NUCLEO_L496ZG
NUCLEO_L496ZG-P
```

* List all sketch containing `digital` or `analog` (not case sensitive):

`python3 arduino-builder.py -l sketch -s "Digital|analog"`

Will produce on the [stm32](https://github.com/stm32duino/Arduino_Core_STM32) core:
```
Cores configuration JSON file that will be used: conf/cores_config.json
Build configuration for 'STM32' maintainer and 'stm32' architecture
<Arduino path>/examples/01.Basics/AnalogReadSerial/AnalogReadSerial.ino
<Arduino path>/examples/01.Basics/DigitalReadSerial/DigitalReadSerial.ino
<Arduino path>/examples/01.Basics/ReadAnalogVoltage/ReadAnalogVoltage.ino
<Arduino path>/examples/02.Digital/BlinkWithoutDelay/BlinkWithoutDelay.ino
<Arduino path>/examples/02.Digital/Button/Button.ino
<Arduino path>/examples/02.Digital/Debounce/Debounce.ino
<Arduino path>/examples/02.Digital/DigitalInputPullup/DigitalInputPullup.ino
<Arduino path>/examples/02.Digital/StateChangeDetection/StateChangeDetection.ino
<Arduino path>/examples/02.Digital/toneKeyboard/toneKeyboard.ino
<Arduino path>/examples/02.Digital/toneMelody/toneMelody.ino
<Arduino path>/examples/02.Digital/toneMultiple/toneMultiple.ino
<Arduino path>/examples/02.Digital/tonePitchFollower/tonePitchFollower.ino
<Arduino path>/examples/03.Analog/AnalogInOutSerial/AnalogInOutSerial.ino
<Arduino path>/examples/03.Analog/AnalogInput/AnalogInput.ino
<Arduino path>/examples/03.Analog/AnalogWriteMega/AnalogWriteMega.ino
<Arduino path>/examples/03.Analog/Calibration/Calibration.ino
<Arduino path>/examples/03.Analog/Fading/Fading.ino
<Arduino path>/examples/03.Analog/Smoothing/Smoothing.ino
<Arduino path>/examples/10.StarterKit_BasicKit/p08_DigitalHourglass/p08_DigitalHourglass.ino
19 sketches found
```

* Build all sketches containing `digital` or `analog` for all boards containing `F1` or `L4` (not case sensitive):

`python3 arduino-builder.py -s "Digital|analog" -b "F1|l4"` 

* List all boards for STM32F1 core:

`python3 arduino-builder.py -l --arch STM32F1`

Will list:
```
Cores configuration JSON file that will be used: conf/cores_config.json
Build configuration for 'Arduino_STM32' maintainer and 'STM32F1' architecture
23 board(s) available
NucleoF103_HSE
NucleoF103_HSI
STM32F103C8
STM32F103CB
STM32F103R8
STM32F103RB
STM32F103RC
STM32F103RE
STM32F103T8
STM32F103TB
STM32F103VB
STM32F103VC
STM32F103VD
STM32F103VE
STM32F103ZC
STM32F103ZD
STM32F103ZE
STM32VLD
hytiny-stm32f103t
maple
mapleMini
mapleRET6
microduino32_flash
```
