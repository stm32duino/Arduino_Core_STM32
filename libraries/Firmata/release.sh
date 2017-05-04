#!/bin/sh

# use this script to package Firmata for distribution

# package for Arduino 1.0.x
mkdir -p temp/Firmata
cp -r examples temp/Firmata
cp -r extras temp/Firmata
cp -r utility temp/Firmata
cp Boards.h temp/Firmata
cp Firmata.cpp temp/Firmata
cp Firmata.h temp/Firmata
cp keywords.txt temp/Firmata
cp readme.md temp/Firmata
cd temp
find . -name "*.DS_Store" -type f -delete
zip -r Firmata.zip ./Firmata/
cd ..
mv ./temp/Firmata.zip Firmata-2.5.2.zip

#package for Arduino 1.6.x
cp library.properties temp/Firmata
cd temp/Firmata
mv readme.md ./extras/
mkdir src
mv Boards.h ./src/
mv Firmata.cpp ./src/
mv Firmata.h ./src/
mv utility ./src/
cd ..
find . -name "*.DS_Store" -type f -delete
zip -r Firmata.zip ./Firmata/
cd ..
mv ./temp/Firmata.zip Arduino-1.6.x-Firmata-2.5.2.zip
rm -r ./temp
