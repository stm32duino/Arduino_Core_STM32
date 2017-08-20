/*
 * This file could be generated thanks a python script: genpinmap_arduino.py
 *
 * This script allows to generate the pins mapping of a STM32 MCU.
 *
 * It is included with the STM32Tools package install with this core.
 * Go to:
 * <local Arduino directory>\packages\STM32\tools\STM32Tools\<version>\tools\src\genpinmap\
 * Tips: <local Arduino directory> is displayed in the "Preferences" dialog of the Arduino IDE. 
 *
 * This script is able to generate the PeripheralPins.c using STM32
 * xml file description in Cube MX.
 * After file generation, review it carefully.
 * Comment a line if the pin is generated several times for the same IP
 * or if the pin should not be used
 * (overlaid with some HW on the board, for instance)
 *
 * USAGE: genpinmap_arduino.py <BOARD_NAME> <product xml file name>
 *
 *     <BOARD_NAME> is the name of the board as it will be named in variant folder
 *     <product xml file name> is the STM32 file description in Cube MX
 *
 * !!This xml file contains non alpha characters in its name, you should call it with quotes
 *
 */