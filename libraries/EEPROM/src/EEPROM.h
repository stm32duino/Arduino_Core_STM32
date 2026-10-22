/*
  EEPROM.h - EEPROM library
  Original Copyright (c) 2006 David A. Mellis.  All right reserved.
  New version by Christopher Andrews 2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef EEPROM_h
#define EEPROM_h

#include "Arduino.h"
extern "C" {
#include "utility/stm32_eeprom.h"
}
#if defined(USE_HALV2_DRIVER)
  #warning "EEPROM library is not yet compatible with HALv2 driver."
#endif
/**
 * @brief EERef class.
 *
 * This object references an EEPROM cell.
 * Its purpose is to mimic a typical byte of RAM, however its storage is the EEPROM.
 * This class has an overhead of two bytes, similar to storing a pointer to an EEPROM cell.
 */
struct EERef {

  /**
   * @brief Construct a reference to an EEPROM cell.
   * @param idx Index of the EEPROM cell.
   */
  EERef(const int idx)
    : index(idx)                 {}

  /**
   * @brief Read the value of the referenced EEPROM cell.
   * @return Value stored in the EEPROM cell.
   */
  uint8_t operator*() const
  {
#if defined(USE_HALV2_DRIVER)
    return 0; //EEPROM library is not yet compatible with HALv2 driver.
#else
    return eeprom_read_byte(/*(uint8_t*)*/ index);
#endif
  }
  /**
   * @brief Implicit conversion to uint8_t, reads the referenced EEPROM cell.
   * @return Value stored in the EEPROM cell.
   */
  operator uint8_t() const
  {
    return **this;
  }

  /**
   * @brief Write the value of another EERef to the referenced EEPROM cell.
   * @param ref Reference whose value is written.
   * @return Reference to this object.
   */
  EERef &operator=(const EERef &ref)
  {
    return *this = *ref;
  }
  /**
   * @brief Write a byte to the referenced EEPROM cell.
   * @param in Value to write.
   * @return Reference to this object.
   */
  EERef &operator=(uint8_t in)
  {
#if defined(USE_HALV2_DRIVER)
    return *this; //EEPROM library is not yet compatible with HALv2 driver.
#else
    return eeprom_write_byte(/*(uint8_t*)*/ index, in), *this;
#endif
  }
  /**
   * @brief Add a value to the stored value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator +=(uint8_t in)
  {
    return *this = **this + in;
  }
  /**
   * @brief Subtract a value from the stored value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator -=(uint8_t in)
  {
    return *this = **this - in;
  }
  /**
   * @brief Multiply the stored value by a value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator *=(uint8_t in)
  {
    return *this = **this * in;
  }
  /**
   * @brief Divide the stored value by a value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator /=(uint8_t in)
  {
    return *this = **this / in;
  }
  /**
   * @brief Bitwise XOR the stored value with a value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator ^=(uint8_t in)
  {
    return *this = **this ^ in;
  }
  /**
   * @brief Modulo the stored value by a value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator %=(uint8_t in)
  {
    return *this = **this % in;
  }
  /**
   * @brief Bitwise AND the stored value with a value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator &=(uint8_t in)
  {
    return *this = **this & in;
  }
  /**
   * @brief Bitwise OR the stored value with a value and write the result back.
   * @param in Operand.
   * @return Reference to this object.
   */
  EERef &operator |=(uint8_t in)
  {
    return *this = **this | in;
  }
  /**
   * @brief Left shift the stored value by a value and write the result back.
   * @param in Number of bits to shift.
   * @return Reference to this object.
   */
  EERef &operator <<=(uint8_t in)
  {
    return *this = **this << in;
  }
  /**
   * @brief Right shift the stored value by a value and write the result back.
   * @param in Number of bits to shift.
   * @return Reference to this object.
   */
  EERef &operator >>=(uint8_t in)
  {
    return *this = **this >> in;
  }

  /**
   * @brief Write a value only if it differs from the stored value, to reduce EEPROM wear.
   * @param in Value to write.
   * @return Reference to this object.
   */
  EERef &update(uint8_t in)
  {
    return  in != *this ? *this = in : *this;
  }

  /**
   * @brief Prefix increment of the stored value.
   * @return Reference to this object.
   */
  EERef &operator++()
  {
    return *this += 1;
  }
  /**
   * @brief Prefix decrement of the stored value.
   * @return Reference to this object.
   */
  EERef &operator--()
  {
    return *this -= 1;
  }

  /**
   * @brief Postfix increment of the stored value.
   * @return Value stored before the increment.
   */
  uint8_t operator++ (int)
  {
    uint8_t ret = **this;
    return ++(*this), ret;
  }

  /**
   * @brief Postfix decrement of the stored value.
   * @return Value stored before the decrement.
   */
  uint8_t operator-- (int)
  {
    uint8_t ret = **this;
    return --(*this), ret;
  }

  int index; //Index of current EEPROM cell.
};

/**
 * @brief EEPtr class.
 *
 * This object is a bidirectional pointer to EEPROM cells represented by EERef objects.
 * Just like a normal pointer type, this can be dereferenced and repositioned using
 * increment/decrement operators.
 */
struct EEPtr {

  /**
   * @brief Construct a pointer to an EEPROM cell.
   * @param idx Index of the EEPROM cell.
   */
  EEPtr(const int idx)
    : index(idx)                {}

  /**
   * @brief Implicit conversion to the index of the pointed EEPROM cell.
   * @return Index of the EEPROM cell.
   */
  operator int() const
  {
    return index;
  }
  /**
   * @brief Set the index of the pointed EEPROM cell.
   * @param in New index.
   * @return Reference to this object.
   */
  EEPtr &operator=(int in)
  {
    return index = in, *this;
  }

  /**
   * @brief Compare the index of this pointer with another pointer.
   * @param ptr Pointer to compare with.
   * @return true if the indices differ, false otherwise.
   */
  bool operator!=(const EEPtr &ptr)
  {
    return index != ptr.index;
  }
  /**
   * @brief Dereference the pointer.
   * @return EERef referencing the pointed EEPROM cell.
   */
  EERef operator*()
  {
    return index;
  }

  /**
   * @brief Prefix increment, move the pointer to the next EEPROM cell.
   * @return Reference to this object.
   */
  EEPtr &operator++()
  {
    return ++index, *this;
  }
  /**
   * @brief Prefix decrement, move the pointer to the previous EEPROM cell.
   * @return Reference to this object.
   */
  EEPtr &operator--()
  {
    return --index, *this;
  }
  /**
   * @brief Postfix increment, move the pointer to the next EEPROM cell.
   * @return Copy of the pointer before the increment.
   */
  EEPtr operator++ (int)
  {
    return index++;
  }
  /**
   * @brief Postfix decrement, move the pointer to the previous EEPROM cell.
   * @return Copy of the pointer before the decrement.
   */
  EEPtr operator-- (int)
  {
    return index--;
  }

  int index; //Index of current EEPROM cell.
};

/**
 * @brief EEPROMClass class.
 *
 * This object represents the entire EEPROM space.
 * It wraps the functionality of EEPtr and EERef into a basic interface.
 * This class is also 100% backwards compatible with earlier Arduino core releases.
 */
struct EEPROMClass {

  /**
   * @brief Access the EEPROM cell at an index.
   * @param idx Index of the EEPROM cell.
   * @return EERef referencing the EEPROM cell.
   */
  EERef operator[](const int idx)
  {
    return idx;
  }
  /**
   * @brief Read a byte from EEPROM.
   * @param idx Index of the EEPROM cell.
   * @return Value stored in the EEPROM cell.
   */
  uint8_t read(int idx)
  {
    return EERef(idx);
  }
  /**
   * @brief Write a byte to EEPROM.
   * @param idx Index of the EEPROM cell.
   * @param val Value to write.
   */
  void write(int idx, uint8_t val)
  {
    (EERef(idx)) = val;
  }
  /**
   * @brief Write a byte to EEPROM only if it differs from the stored value, to reduce EEPROM wear.
   * @param idx Index of the EEPROM cell.
   * @param val Value to write.
   */
  void update(int idx, uint8_t val)
  {
    EERef(idx).update(val);
  }

  /**
   * @brief Get an iterator to the first EEPROM cell (STL and C++11 iteration).
   * @return EEPtr pointing to index 0.
   */
  EEPtr begin()
  {
    return 0x00;
  }
  /**
   * @brief Get an iterator to the item after the last EEPROM cell (STL and C++11 iteration).
   * @return EEPtr pointing past the last valid cell, it must not be dereferenced.
   */
  EEPtr end()
  {
    return length();  //Standards requires this to be the item after the last valid entry. The returned pointer is invalid.
  }
  /**
   * @brief Get the number of EEPROM bytes available.
   * @return Size of the EEPROM in bytes, 0 when USE_HALV2_DRIVER is defined.
   */
  uint16_t length()
  {
#if defined(USE_HALV2_DRIVER)
    return 0;
#else
    return E2END + 1;
#endif
  }

  /**
   * @brief Read an object from EEPROM.
   * @tparam T Type of the object.
   * @param idx Index of the first EEPROM cell to read.
   * @param t Object to fill with the values read from EEPROM.
   * @return Reference to t.
   */
  template< typename T > T &get(int idx, T &t)
  {
    EEPtr e = idx;
    uint8_t *ptr = (uint8_t *) &t;
    for (int count = sizeof(T) ; count ; --count, ++e) {
      *ptr++ = *e;
    }
    return t;
  }

  /**
   * @brief Write an object to EEPROM. Only the bytes that differ from the stored values are written.
   * @tparam T Type of the object.
   * @param idx Index of the first EEPROM cell to write.
   * @param t Object to write.
   * @return Reference to t.
   */
  template< typename T > const T &put(int idx, const T &t)
  {
    EEPtr e = idx;
    const uint8_t *ptr = (const uint8_t *) &t;
    for (int count = sizeof(T) ; count ; --count, ++e) {
      (*e).update(*ptr++);
    }
    return t;
  }
};

static EEPROMClass EEPROM;
#endif
