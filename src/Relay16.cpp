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

#include <stdlib.h>
#include <string.h>
#include "Arduino.h"
#include "Relay16.h"

Relay16::Relay16()
{
	this->addr = 0;
	this->relayBits = 0; // All relays off
	this->dioReset = -1; // Unknown digital I/O for the reset line
	this->i2cInterface = NULL;
}

boolean Relay16::refresh()
{
	if (NULL == this->i2cInterface || 0 == this->addr)
		return false;
	this->i2cInterface->beginTransmission(this->addr);
	this->i2cInterface->write(~(this->relayBits & 0xFF));
	this->i2cInterface->write(~((this->relayBits >> 8) & 0xFF));
	if(0 != this->i2cInterface->endTransmission(true))
		return false;
	return true;
}


boolean Relay16::allOff()
{
	this->relayBits = 0;
	return refresh();
}

boolean Relay16::allOn()
{
	this->relayBits = 0xFFFF;
	refresh();
}

boolean Relay16::digitalWrite(uint8_t relayNum, uint8_t relayState)
{
	if (relayState)
		return relayOn(relayNum);
	else
		return relayOff(relayNum);
}

boolean Relay16::relayOn(byte relayNum)
{
	if (relayNum < 1 || relayNum > 16)
		return false;
	this->relayBits |= 1<<(relayNum-1);
	refresh();
}

boolean Relay16::relayOff(byte relayNum)
{
	if (relayNum < 1 || relayNum > 16)
		return false;
	this->relayBits &= ~(1<<(relayNum-1));
	return refresh();
}

boolean Relay16::begin()
{
	return this->begin(Wire, false, false, false, -1);
}

boolean Relay16::begin(boolean j5, boolean j6, boolean j7, int8_t dioResetPin)
{
	return this->begin(Wire, j5, j6, j7, dioResetPin);
}

boolean Relay16::begin(TwoWire& i2cInterface, boolean j5, boolean j6, boolean j7, int8_t dioResetPin)
{
	uint8_t addrBitmap = 0x20 | (j5?0x01:0x00) | (j6?0x02:0x00) | (j7?0x04:0x00);
	return this->begin(i2cInterface, addrBitmap, dioResetPin);
}

boolean Relay16::begin(TwoWire& i2cInterface, uint8_t address, int8_t dioResetPin)
{
	this->addr = address;
	this->i2cInterface = &i2cInterface;
	this->dioReset = dioResetPin;
	
	// If there's a DIO pin assigned to reset, use it to do a hardware reset on initialization
	if (-1 != this->dioReset)
	{
		pinMode(this->dioReset, OUTPUT);
		digitalWrite(this->dioReset, LOW);
		delayMicroseconds(100);
		digitalWrite(this->dioReset, HIGH);
	}
	
	return this->allOff();
}
