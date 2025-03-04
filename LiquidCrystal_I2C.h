// ---------------------------------------------------------------------------
// Created by Francisco Malpartida on 20/08/11.
// Copyright (C) - 2018
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License v3.0
//    along with this program.
//    If not, see <https://www.gnu.org/licenses/gpl-3.0.en.html>.
// 
// ---------------------------------------------------------------------------
//
// Thread Safe: No
// Extendable: Yes
//
// @file LiquidCrystal_I2C.h
// This file implements a basic liquid crystal library that comes as standard
// in the Arduino SDK but using an I2C IO extension board.
//
// @brief
// This is a basic implementation of the LiquidCrystal library of the
// Arduino SDK. The original library has been reworked in such a way that
// this class implements the all methods to command an LCD based
// on the Hitachi HD44780 and compatible chipsets using I2C extension
// backpacks such as the I2CLCDextraIO with the PCF8574* I2C IO Expander ASIC.
//
// The functionality provided by this class and its base class is identical
// to the original functionality of the Arduino LiquidCrystal library.
//
//
// @author F. Malpartida - fmalpartida@gmail.com
// ---------------------------------------------------------------------------
#ifndef LiquidCrystal_I2C_h
#define LiquidCrystal_I2C_h
#include <inttypes.h>
#include <Print.h>

#include "I2CIO.h"
#include "LCD.h"


class LiquidCrystal_I2C : public LCD
{
public:

   /*!
    @method
    @abstract   Class constructor.
    @discussion Initializes class variables and defines the I2C address of the
    LCD. The constructor does not initialize the LCD.

    @param      lcd_Addr[in] I2C address of the IO expansion module. For I2CLCDextraIO,
    the address can be configured using the on board jumpers.
    */
   LiquidCrystal_I2C (uint8_t lcd_Addr);
   // Constructor with backlight control
   LiquidCrystal_I2C (uint8_t lcd_Addr, uint8_t backlighPin, t_backlightPol pol);

   /*!
    @method
    @abstract   Class constructor.
    @discussion Initializes class variables and defines the I2C address of the
    LCD. The constructor does not initialize the LCD.

    @param      lcd_Addr[in] I2C address of the IO expansion module. For I2CLCDextraIO,
    the address can be configured using the on board jumpers.
    @param      En[in] LCD En (Enable) pin connected to the IO extender module
    @param      Rw[in] LCD Rw (Read/write) pin connected to the IO extender module
    @param      Rs[in] LCD Rs (Reset) pin connected to the IO extender module
    */
   LiquidCrystal_I2C( uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs);
   // Constructor with backlight control
   LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
                     uint8_t backlighPin, t_backlightPol pol);

   /*!
    @method
    @abstract   Class constructor.
    @discussion Initializes class variables and defines the I2C address of the
    LCD. The constructor does not initialize the LCD.

    @param      lcd_Addr[in] I2C address of the IO expansion module. For I2CLCDextraIO,
    the address can be configured using the on board jumpers.
    @param      En[in] LCD En (Enable) pin connected to the IO extender module
    @param      Rw[in] LCD Rw (Read/write) pin connected to the IO extender module
    @param      Rs[in] LCD Rs (Reset) pin connected to the IO extender module
    @param      d4[in] LCD data 0 pin map on IO extender module
    @param      d5[in] LCD data 1 pin map on IO extender module
    @param      d6[in] LCD data 2 pin map on IO extender module
    @param      d7[in] LCD data 3 pin map on IO extender module
    */
   LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
                     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 );
   // Constructor with backlight control
   LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
                     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                     uint8_t backlighPin, t_backlightPol pol);
   /*!
    @function
    @abstract   LCD initialization and associated HW.
    @discussion Initializes the LCD to a given size (col, row). This methods
    initializes the LCD, therefore, it MUST be called prior to using any other
    method from this class or parent class.

    The begin method can be overloaded if necessary to initialize any HW that
    is implemented by a library and can't be done during construction, here
    we use the Wire class.

    @param      cols[in] the number of columns that the display has
    @param      rows[in] the number of rows that the display has
    @param      charsize[in] size of the characters of the LCD: LCD_5x8DOTS or
    LCD_5x10DOTS.
    */
   virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

   /*!
    @function
    @abstract   Send a particular value to the LCD.
    @discussion Sends a particular value to the LCD for writing to the LCD or
    as an LCD command.

    Users should never call this method.

    @param      value[in] Value to send to the LCD.
    @param      mode[in] DATA - write to the LCD CGRAM, COMMAND - write a
    command to the LCD.
    */
   virtual void send(uint8_t value, uint8_t mode);

   /*!
    @function
    @abstract   Sets the pin to control the backlight.
    @discussion Sets the pin in the device to control the backlight. This device
    doesn't support dimming backlight capability.

    @param      0: backlight off, 1..255: backlight on.
    */
   void setBacklightPin ( uint8_t value, t_backlightPol pol );

   /*!
    @function
    @abstract   Switch-on/off the LCD backlight.
    @discussion Switch-on/off the LCD backlight.
    The setBacklightPin has to be called before setting the backlight for
    this method to work. @see setBacklightPin.

    @param      value: backlight mode (HIGH|LOW)
    */
   void setBacklight ( uint8_t value );

  /*!
   @function
    @abstract   Gets the character at specific LCD position.
    @discussion Gets the character at specific LCD position.
    It will call setCursor to set a correct DDRAM address in order to read
    a character from it. It will not restore the previous cursor position.
    @see setCursor

    @param      col[in] LCD column
    @param      row[in] LCD row - line.
    @result     Character at the specific LCD position
    */
   char getCharAt(uint8_t col, uint8_t row);

private:

   /*!
    @function
   @abstract   Initialises class private variables
   @discussion This is the class single point for initialising private variables.
   Making config public would enable to inherit and overload the methdo by a custom one.

   @param      lcd_Addr[in] I2C address of the IO expansion module. For I2CLCDextraIO,
   the address can be configured using the on board jumpers.
   @param      En[in] LCD En (Enable) pin connected to the IO extender module
   @param      Rw[in] LCD Rw (Read/write) pin connected to the IO extender module
   @param      Rs[in] LCD Rs (Reset) pin connected to the IO extender module
   @param      d4[in] LCD data 0 pin map on IO extender module
   @param      d5[in] LCD data 1 pin map on IO extender module
   @param      d6[in] LCD data 2 pin map on IO extender module
   @param      d7[in] LCD data 3 pin map on IO extender module
   */
  void config (uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
               uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 );

private:

   /*!
    @method
    @abstract   Initializes the LCD class
    @discussion Initializes the LCD class and IO expansion module.
    */
   int  init();

   /*!
    @method
    @abstract   Writes an 4 bit value to the LCD.
    @discussion Writes 4 bits (the least significant) to the LCD control data lines.
    @param      value[in] Value to write to the LCD
    @param      more[in]  Value to distinguish between command and data.
    COMMAND == command, DATA == data.
    */
   void write4bits(uint8_t value, uint8_t mode);

   /*!
    @method
    @abstract   Reads 4 bit value from the LCD.
    @discussion Reads 4 bits from the LCD data lines.
    @result     4 data bits read from LCD. They are stored in the low nibble of returned value.
    */
   uint8_t read4bits();

   /*!
    @method
    @abstract   Pulse the LCD enable line (En).
    @discussion Sends a pulse of 1 uS to the Enable pin to execute an command
    or write operation.
    */
   void pulseEnable(uint8_t);


   uint8_t _Addr;             // I2C Address of the IO expander
   uint8_t _backlightPinMask; // Backlight IO pin mask
   uint8_t _backlightStsMask; // Backlight status mask
   I2CIO   _i2cio;            // I2CIO PCF8574* expansion module driver I2CLCDextraIO
   uint8_t _En;               // LCD expander word for enable pin
   uint8_t _Rw;               // LCD expander word for R/W pin
   uint8_t _Rs;               // LCD expander word for Register Select pin
   uint8_t _data_pins[4];     // LCD data lines

};

#endif
