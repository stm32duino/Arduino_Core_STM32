/**
  * \file syscalls_stm32.c
  *
  * Implementation of newlib syscall.
  *
  */

#include "stm32_def.h"
#if defined (  __GNUC__  ) /* GCC CS3 */
  #include <sys/stat.h>
#endif
#include <errno.h>
#undef errno
extern int errno;

/**
 * @brief Increase the program data space (heap) used by malloc.
 * @param incr Number of bytes to add to the heap.
 * @return Previous heap end on success, or (caddr_t)-1 with errno set to ENOMEM.
 */
__attribute__((weak))
caddr_t _sbrk(int incr)
{
  extern char _estack; /* Defined in the linker script */
  extern char _Min_Stack_Size; /* Defined in the linker script */
  extern char _end; /* Defined by the linker */
  static char *heap_end = &_end ;
  char *prev_heap_end = heap_end;

  if (heap_end + incr > (char *)__get_MSP()) {
    /* Heap and stack collision */
    errno = ENOMEM;
    return (caddr_t) -1;
  }
  /* Ensure to keep minimum stack size defined in the linker script */
  if (heap_end + incr >= (char *)(&_estack - &_Min_Stack_Size)) {
    errno = ENOMEM;
    return (caddr_t) -1;
  }

  heap_end += incr ;
  return (caddr_t) prev_heap_end ;
}

/**
 * @brief Close a file. Not supported, always fails.
 * @param file File descriptor to close.
 * @return -1.
 */
__attribute__((weak))
int _close(int file)
{
  (void)file;
  return -1;
}

/**
 * @brief Get file status. Reports every file as a character device.
 * @param file File descriptor.
 * @param st Buffer that receives the file status.
 * @return 0.
 */
__attribute__((weak))
int _fstat(int file, struct stat *st)
{
  (void)file;
  st->st_mode = S_IFCHR ;
  return 0;
}

/**
 * @brief Check whether a file descriptor refers to a terminal. Always reports a terminal.
 * @param file File descriptor.
 * @return 1.
 */
__attribute__((weak))
int _isatty(int file)
{
  (void)file;
  return 1;
}

/**
 * @brief Set the file position. Not supported, always returns 0.
 * @param file File descriptor.
 * @param ptr Offset.
 * @param dir Seek direction.
 * @return 0.
 */
__attribute__((weak))
int _lseek(int file, int ptr, int dir)
{
  (void)file;
  (void)ptr;
  (void)dir;
  return 0;
}

/**
 * @brief Read from a file. Not supported, always returns 0 bytes read.
 * @param file File descriptor.
 * @param ptr Buffer to fill.
 * @param len Maximum number of bytes to read.
 * @return 0.
 */
__attribute__((weak))
int _read(int file, char *ptr, int len)
{
  (void)file;
  (void)ptr;
  (void)len;
  return 0;
}

/* Moved to Print.cpp to support Print::printf()
__attribute__((weak))
int _write(int file, char *ptr, int len)
{
  (void)file;
  (void)ptr;
  (void)len;
  return 0;
}
*/

/**
 * @brief Terminate the program. Loops forever.
 * @param status Exit status (ignored).
 */
__attribute__((weak))
void _exit(int status)
{
  (void)status;
  for (; ;) ;
}

/**
 * @brief Send a signal to a process. Not supported, always fails.
 * @param pid Process ID.
 * @param sig Signal number.
 * @return -1 with errno set to EINVAL.
 */
__attribute__((weak))
int _kill(int pid, int sig)
{
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}

/**
 * @brief Get the process ID. Always returns 1.
 * @return 1.
 */
__attribute__((weak))
int _getpid(void)
{
  return 1;
}
