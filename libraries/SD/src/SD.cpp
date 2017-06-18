/*

 SD - a slightly more friendly wrapper for sdfatlib

 This library aims to expose a subset of SD card functionality
 in the form of a higher level "wrapper" object.

 License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

 (C) Copyright 2010 SparkFun Electronics


 This library provides four key benefits:

   * Including `SDStm.h` automatically creates a global
     `SD` object which can be interacted with in a similar
     manner to other standard global objects like `Serial` and `Ethernet`.

   * Boilerplate initialisation code is contained in one method named
     `begin` and no further objects need to be created in order to access
     the SD card.

   * Calls to `open` can supply a full path name including parent
     directories which simplifies interacting with files in subdirectories.

   * Utility methods are provided to determine whether a file exists
     and to create a directory heirarchy.


  Note however that not all functionality provided by the underlying
  sdfatlib library is exposed.

 */

/*

  Implementation Notes

  In order to handle multi-directory path traversal, functionality that
  requires this ability is implemented as callback functions.

  Individual methods call the `walkPath` function which performs the actual
  directory traversal (swapping between two different directory/file handles
  along the way) and at each level calls the supplied callback function.

  Some types of functionality will take an action at each level (e.g. exists
  or make directory) which others will only take an action at the bottom
  level (e.g. open).

 */

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "stm32_def.h"
}
#include "assert.h"
#include "SDStm.h"
SDClass SD;

/**
  * @brief  Link SD, register the file system object to the FatFs mode and configure
  *         relatives SD IOs except SD Detect Pin
  * @param  None
  * @retval TRUE or FALSE
  */
uint8_t SDClass::begin()
{
	/*##-1- Initializes SD IOs #############################################*/
	if (_card.init()) {
		return _fatFs.init();
    }
    else
    {
	  return FALSE;
    }
}

/**
  * @brief  Link SD, register the file system object to the FatFs mode and configure
  *         relatives SD IOs including SD Detect Pin
  * @param  None
  * @retval TRUE or FALSE
  */
uint8_t SDClass::begin(uint8_t cspin)
{
	/*##-1- Initializes SD IOs #############################################*/
	if (_card.init(cspin)) {
		return _fatFs.init();
    }
    else
    {
	  return FALSE;
    }
}

/**
  * @brief  Check if a file or folder exist on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::exists(const char *filepath)
{
    FILINFO fno;

    if(f_stat(filepath, &fno) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
  * @brief  Create directory on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::mkdir(const char *filepath)
{
   if(f_mkdir(filepath) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
  * @brief  Remove directory on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::rmdir(const char *filepath)
{
    if(f_unlink(filepath) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
  * @brief  Open a file on the SD disk, if not existing it's created
  * @param  filename: File name
  * @retval File object referring to the opened file
  */
File SDClass::open(const char *filepath)
{
    File file = File(filepath);

    if(f_open(&file._fil, filepath, FA_READ) != FR_OK)
    {
		f_opendir(&file._dir, filepath);
	}
	return file;
}

/**
  * @brief  Open a file on the SD disk, if not existing it's created
  * @param  filename: File name
  * @param  mode: the mode in which to open the file
  * @retval File object referring to the opened file
  */
File SDClass::open(const char *filepath, uint8_t mode)
{
	File file = File(filepath);

	if((mode == FILE_WRITE) && (SD.exists(filepath) != TRUE))
    {
        mode = mode | FA_CREATE_ALWAYS;
    }

    if(f_open(&file._fil, filepath, mode) != FR_OK)
    {
		f_opendir(&file._dir, filepath);
	}
    return file;
}

/**
  * @brief  Remove a file on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::remove(const char *filepath)
{
   if(f_unlink(filepath) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

File SDClass::openRoot(void)
{
    File file = File(_fatFs.getRoot());

	if(f_opendir(&file._dir, _fatFs.getRoot()) != FR_OK)
	{
		file._dir.fs = 0;
	}
    return file;
}

File::File()
{
	_name = NULL;
	 _fil.fs = 0;
	 _dir.fs = 0;
}

File::File(const char* name)
{
	_name = (char*)malloc(strlen(name) +1);
	assert(_name  != NULL );
	sprintf(_name, "%s", name);
	_fil.fs = 0;
	_dir.fs = 0;
}

/** List directory contents to Serial.
 *
 * \param[in] flags The inclusive OR of
 *
 * LS_DATE - %Print file modification date
 *
 * LS_SIZE - %Print file size.
 *
 * LS_R - Recursive list of subdirectories.
 *
 * \param[in] indent Amount of space before file name. Used for recursive
 * list to indicate subdirectory level.
 */
void File::ls(uint8_t flags, uint8_t indent) {
  FRESULT res = FR_OK;
  FILINFO fno;
  char *fn;

#if _USE_LFN
  static char lfn[_MAX_LFN];
  fno.lfname = lfn;
  fno.lfsize = sizeof(lfn);
#endif

  while(1)
  {
    res = f_readdir(&_dir, &fno);
    if(res != FR_OK || fno.fname[0] == 0)
    {
      break;
    }
    if(fno.fname[0] == '.')
    {
      continue;
    }
#if _USE_LFN
    fn = *fno.lfname ? fno.lfname : fno.fname;
#else
    fn = fno.fname;
#endif
	//print any indent spaces
	for (int8_t i = 0; i < indent; i++) Serial.print(' ');
    Serial.print(fn);

    if((fno.fattrib & AM_DIR) == 0)
    {
	  // print modify date/time if requested
	  if (flags & LS_DATE) {
		Serial.print(' ');
		printFatDate(fno.fdate);
		Serial.print(' ');
		printFatTime(fno.ftime);
	  }
	  // print size if requested
	  if (flags & LS_SIZE) {
	    Serial.print(' ');
	    Serial.print(fno.fsize);
	  }
	  Serial.println();
    }
	else
	{
	  // list subdirectory content if requested
	  if (flags & LS_R)
	  {
		char *fullPath;
		fullPath = (char*)malloc(strlen(_name) + 1 + strlen(fn) +1);
		if (fullPath != NULL) {
		  sprintf(fullPath, "%s/%s", _name, fn);
		  File filtmp = SD.open(fullPath);

		  if (filtmp._name != NULL) {
			Serial.println();
			filtmp.ls(flags, indent+2);
			filtmp.close();
		  } else {
			Serial.println(fn);
			Serial.print("Error to open dir: ");
			Serial.println(fn);
		  }
		  free(fullPath);
		} else {
		  Serial.println();
		  Serial.print("Error to allocate memory!");
		}
	  }
	}
  }
}
//------------------------------------------------------------------------------
/** %Print a directory date field to Serial.
 *
 *  Format is yyyy-mm-dd.
 *
 * \param[in] fatDate The date field from a directory entry.
 */
void File::printFatDate(uint16_t fatDate) {
  Serial.print(FAT_YEAR(fatDate));
  Serial.print('-');
  printTwoDigits(FAT_MONTH(fatDate));
  Serial.print('-');
  printTwoDigits(FAT_DAY(fatDate));
}
//------------------------------------------------------------------------------
/** %Print a directory time field to Serial.
 *
 * Format is hh:mm:ss.
 *
 * \param[in] fatTime The time field from a directory entry.
 */
void File::printFatTime(uint16_t fatTime) {
  printTwoDigits(FAT_HOUR(fatTime));
  Serial.print(':');
  printTwoDigits(FAT_MINUTE(fatTime));
  Serial.print(':');
  printTwoDigits(FAT_SECOND(fatTime));
}
//------------------------------------------------------------------------------
/** %Print a value as two digits to Serial.
 *
 * \param[in] v Value to be printed, 0 <= \a v <= 99
 */
void File::printTwoDigits(uint8_t v) {
  char str[3];
  str[0] = '0' + v/10;
  str[1] = '0' + v % 10;
  str[2] = 0;
  Serial.print(str);
}

/**
  * @brief  Read byte from the file
  * @retval Byte read
  */
int File::read()
{
    uint8_t byteread;
    int8_t data;
    f_read(&_fil, (void *)&data, 1, (UINT *)&byteread);
    return data;
}

/**
  * @brief  Read an amount of data from the file
  * @param  buf: an array to store the read data from the file
  * @param  len: the number of elements to read
  * @retval Number of bytes read
  */
int File::read(void* buf, size_t len)
{
    uint8_t bytesread;

    f_read(&_fil, buf, len, (UINT *)&bytesread);
    return bytesread;

}

/**
  * @brief  Close a file on the SD disk
  * @param  None
  * @retval None
  */
void File::close()
{
	if(_name)
	{
		if(_fil.fs != 0) {
			/* Flush the file before close */
			f_sync(&_fil);

			/* Close the file */
			f_close(&_fil);
		}

		if(_dir.fs != 0) {
			f_closedir(&_dir);
		}

		free(_name);
	}
}


/**
  * @brief  Ensures that any bytes written to the file are physically saved to the SD card
  * @param  None
  * @retval None
  */
void File::flush()
{
    f_sync(&_fil);
}

/**
  * @brief  Read a byte from the file without advancing to the next one
  * @param  None
  * @retval read byte
  */
int File::peek()
{
    int data;
    data = read();
    seek(position() -1);
    return data;
}

/**
  * @brief  Get the current position within the file
  * @param  None
  * @retval position within file
  */
uint32_t File::position()
{
    uint32_t filepos = 0;
    filepos = f_tell(&_fil);
    return filepos;
}

/**
  * @brief  Seek to a new position in the file
  * @param  pos: The position to which to seek
  * @retval TRUE or FALSE
  */
uint8_t File::seek(uint32_t pos)
{
  if(pos > size())
  {
    return FALSE;
  }
  else
  {
    if(f_lseek(&_fil, pos) != FR_OK)
    {
      return FALSE;
    }
    else
    {
      return TRUE;
    }
  }
}

/**
  * @brief  Get the size of the file
  * @param  None
  * @retval file's size
  */
uint32_t File::size()
{
    uint32_t file_size = 0;

    file_size = f_size(&_fil);
    return(file_size);
}

File::operator bool() {
  return  ((_name == NULL) || ((_fil.fs == 0) && (_dir.fs == 0))) ? FALSE : TRUE;
}
/**
  * @brief  Write data to the file
  * @param  data: Data to write to the file
  * @retval Number of data written (1)
  */
size_t File::write(uint8_t data)
{
  return write(&data, 1);
}

/**
  * @brief  Write an array of data to the file
  * @param  buf: an array of characters or bytes to write to the file
  * @param  len: the number of elements in buf
  * @retval Number of data written
  */
size_t File::write(const char *buf, size_t size)
{
    size_t byteswritten;
    f_write(&_fil, (const void *)buf, size, (UINT *)&byteswritten);
    return byteswritten;
}

size_t File::write(const uint8_t *buf, size_t size)
{
    return write((const char *)buf, size);
}

/**
  * @brief  Print data to the file
  * @param  data: Data to write to the file
  * @retval Number of data written (1)
  */
size_t File::print(const char* data)
{
	return write(data, strlen(data));
}

/**
  * @brief  Print data to the file
  * @retval Number of data written (1)
  */
size_t File::println()
{
    return write("\r\n", 2);
}

/**
  * @brief  Print data to the file
  * @param  data: Data to write to the file
  * @retval Number of data written (1)
  */
size_t File::println(const char* data)
{
	size_t bytewritten = write(data, strlen(data));
	bytewritten += println();
	return bytewritten;
}

/**
  * @brief  Print data to the file
  * @param  data: Data of type String to write to the file
  * @retval Number of data written (1)
  */
size_t File::println(String& data)
{
   return println(data.c_str());
}

/**
  * @brief  Check if there are any bytes available for reading from the file
  * @retval Number of bytes available
  */
int File::available()
{
    uint32_t n = size() - position();
    return n > 0x7FFF ? 0x7FFF : n;
}


char* File::name()
{
	char *name = strrchr(_name, '/');
	if (name && name[0] == '/')
		name++;
	return name;
}

/**
  * @brief  Check if the file is directory or normal file
  * @retval TRUE if directory else FALSE
  */
uint8_t File::isDirectory()
{
    FILINFO fno;
	assert(_name  != NULL );
	if (_dir.fs != 0)
		return TRUE;
	else if (_fil.fs != 0)
		return FALSE;
	// if not init get info
	if (f_stat(_name, &fno) == FR_OK)
	{
		if(fno.fattrib & AM_DIR)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

File File::openNextFile(uint8_t mode)
{
  FRESULT res = FR_OK;
  FILINFO fno;
  char *fn;
  char *fullPath = NULL;
  size_t name_len= strlen(_name);
  size_t len = name_len;
#if _USE_LFN
  static char lfn[_MAX_LFN];
  fno.lfname = lfn;
  fno.lfsize = sizeof(lfn);
#endif
  while(1)
  {
    res = f_readdir(&_dir, &fno);
    if(res != FR_OK || fno.fname[0] == 0)
    {
      return File();
    }
    if(fno.fname[0] == '.')
    {
      continue;
    }
#if _USE_LFN
    fn = *fno.lfname ? fno.lfname : fno.fname;
#else
    fn = fno.fname;
#endif
	len += strlen(fn) +2;
	fullPath = (char*)malloc(len);
	if (fullPath != NULL) {
	  // Avoid twice '/'
	  if ((name_len > 0)  && (_name[name_len-1] == '/'))
	  {
		sprintf(fullPath, "%s%s", _name, fn);
	  } else {
	    sprintf(fullPath, "%s/%s", _name, fn);
	  }
	  File filtmp = SD.open(fullPath, mode);
	  free(fullPath);
	  return filtmp;
	} else {
		return File();
	}
  }
}

void File::rewindDirectory(void)
{
	if(isDirectory())
	{
		if(_dir.fs != 0) {
			f_closedir(&_dir);
		}
		f_opendir(&_dir, _name);
	}
}

