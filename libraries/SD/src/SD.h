/*

 SD - a slightly more friendly wrapper for sdfatlib

 This library aims to expose a subset of SD card functionality
 in the form of a higher level "wrapper" object.

 License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

 (C) Copyright 2010 SparkFun Electronics

 */

#ifndef __SD_H__
#define __SD_H__

#include <Arduino.h>

#include "Sd2Card.h"
#include "SdFatFs.h"

// flags for ls()
/** ls() flag to print modify date */
uint8_t const LS_DATE = 1;
/** ls() flag to print file size */
uint8_t const LS_SIZE = 2;
/** ls() flag for recursive list of subdirectories */
uint8_t const LS_R = 4;

class File {
public:
  File(void);
  File(const char* name);
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  virtual size_t write(const char *buf, size_t size);

  virtual int read();
  virtual int peek();
  virtual int available();
  virtual void flush();
  int read(void* buf, size_t len);
  uint8_t seek(uint32_t pos);
  uint32_t position();
  uint32_t size();
  void close();
  operator bool();

  char* name(void);
  char* fullname(void) {return _name;};
  uint8_t isDirectory();
  File openNextFile(uint8_t mode = FILE_READ);
  void rewindDirectory(void);

  virtual size_t print(const char* data);
  virtual size_t println();
  virtual size_t println(const char* data);
  virtual size_t println(String& data);

  // Print to Serial line
  void ls(uint8_t flags, uint8_t indent = 0);
  static void printFatDate(uint16_t fatDate);
  static void printFatTime(uint16_t fatTime);
  static void printTwoDigits(uint8_t v);


  char *_name = NULL; //file or dir name
  FIL _fil = {}; // init all fields to 0
  DIR _dir = {}; // init all fields to 0

};

class SDClass {

public:

  /* Initialize the SD peripheral */
  uint8_t begin();
  uint8_t begin(uint8_t cspin);
  static File open(const char *filepath, uint8_t mode);
  static File open(const char *filepath);
  static uint8_t exists(const char *filepath);
  static uint8_t mkdir(const char *filepath);
  static uint8_t remove(const char *filepath);
  static uint8_t rmdir(const char *filepath);

  File openRoot(void);

  friend class File;

private:
  Sd2Card _card;
  SdFatFs _fatFs;

};

extern SDClass SD;

#endif
