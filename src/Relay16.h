/*************************************************************************
Title:    Iowa Scaled Engineering I2C-RELAY16 Driver Library
Authors:  Nathan D. Holmes <maverick@drgw.net>
File:     $Id: $
License:  GNU General Public License v3

LICENSE:
    Copyright (C) 2014 Nathan D. Holmes & Michael D. Petersen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    For more information about the Iowa Scaled Engineering I2C-RELAY16, see:
    http://www.iascaled.com/store/I2C-RELAY16
    

*************************************************************************/

#ifndef RELAY16_H
#define RELAY16_H

#include "Arduino.h"
#include "Wire.h"

class Relay16
{
	public:
		Relay16();
		boolean begin();
		boolean begin(boolean j5, boolean j6, boolean j7, int8_t dioReset=-1);
		boolean begin(TwoWire& i2cInterface, boolean j5=false, boolean j6=false, boolean j7=false, int8_t dioReset=-1);
		boolean begin(TwoWire& i2cInterface, uint8_t address, int8_t dioReset=-1);

		boolean relayOn(uint8_t relayNum);
		boolean relayOff(uint8_t relayNum);
		boolean digitalWrite(uint8_t relayNum, uint8_t relayState);
		boolean allOff();
		boolean allOn();
		boolean refresh();
		
	private:
		TwoWire* i2cInterface;
		uint16_t relayBits;
		uint8_t addr;
		int8_t dioReset;
};


#endif

