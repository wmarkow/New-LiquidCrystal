// ---------------------------------------------------------------------------
// Created by Francisco Malpartida on 20/08/11.
// Copyright 2011 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
//
// Thread Safe: No
// Extendable: Yes
//
// @file LiquidCrystal.h
// This file implements a basic liquid crystal library that comes as standard
// in the Arduino SDK.
// 
// @brief 
// This is a basic implementation of the LiquidCrystal library of the
// Arduino SDK. This library is a refactored version of the one supplied
// in the Arduino SDK in such a way that it simplifies its extension
// to support other mechanism to communicate to LCDs such as I2C, Serial.
// The original library has been reworked in such a way that this will be
// the base class implementing all generic methods to command an LCD based
// on the Hitachi HD44780 and compatible chipsets.
//
// This base class is a pure abstract class and needs to be extended. As reference,
// it has been extended to drive 4 and 8 bit mode control, LCDs and I2C extension
// backpacks such as the I2CLCDextraIO using the PCF8574* I2C IO Expander ASIC.
//
//
// This library is only compatible with Arduino's SDK version 1.0
//
// @version API 1.0.0
//
// @author F. Malpartida - fmalpartida@gmail.com
// ---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "Arduino.h"
#include "LiquidCrystal.h"

// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------

// Constructor
LiquidCrystal::LiquidCrystal () 
{

}

// PUBLIC METHODS
// ---------------------------------------------------------------------------

// Common LCD Commands
// ---------------------------------------------------------------------------
void LiquidCrystal::clear()
{
   command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
   delayMicroseconds(2000);    // this command is time consuming
}

void LiquidCrystal::home()
{
   command(LCD_RETURNHOME);  // set cursor position to zero
   delayMicroseconds(2000);  // This command is time consuming
}

void LiquidCrystal::setCursor(uint8_t col, uint8_t row)
{
   int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
   
   if ( row > _numlines ) 
   {
      row = _numlines-1;    // rows start at 0
   }
   
   command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off
void LiquidCrystal::noDisplay() 
{
   _displaycontrol &= ~LCD_DISPLAYON;
   command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal::display() 
{
   _displaycontrol |= LCD_DISPLAYON;
   command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal::noCursor() 
{
   _displaycontrol &= ~LCD_CURSORON;
   command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal::cursor() 
{
   _displaycontrol |= LCD_CURSORON;
   command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns on/off the blinking cursor
void LiquidCrystal::noBlink() 
{
   _displaycontrol &= ~LCD_BLINKON;
   command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal::blink() 
{
   _displaycontrol |= LCD_BLINKON;
   command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal::scrollDisplayLeft(void) 
{
   command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LiquidCrystal::scrollDisplayRight(void) {
   command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal::leftToRight(void) 
{
   _displaymode |= LCD_ENTRYLEFT;
   command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal::rightToLeft(void) 
{
   _displaymode &= ~LCD_ENTRYLEFT;
   command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal::autoscroll(void) 
{
   _displaymode |= LCD_ENTRYSHIFTINCREMENT;
   command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal::noAutoscroll(void) 
{
   _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
   command(LCD_ENTRYMODESET | _displaymode);
}

// Write to CGRAM of new characters
void LiquidCrystal::createChar(uint8_t location, uint8_t charmap[]) 
{
   location &= 0x7;            // we only have 8 locations 0-7

   command(LCD_SETCGRAMADDR | (location << 3));
   for (int i=0; i<8; i++) 
   {
      write(charmap[i]);      // call the virtual write method
   }
}

// General LCD commands - generic methods used by the rest of the commands
// ---------------------------------------------------------------------------
void LiquidCrystal::command(uint8_t value) 
{
   send(value, LOW);
}

size_t LiquidCrystal::write(uint8_t value) 
{
   send(value, HIGH);
   
   return 1;           // assume OK
}