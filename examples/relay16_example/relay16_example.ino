/*************************************************************************
Title:    Iowa Scaled Engineering I2C-RELAY16 Driver Library Example Sketch
Authors:  Nathan D. Holmes <maverick@drgw.net>
File:     $Id: $
License:  GNU General Public License v3

LICENSE:
    Copyright (C) 2014 Nathan D. Holmes & Michael D. Petersen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    For more information about the Iowa Scaled Engineering I2C-RELAY16, see:
    http://www.iascaled.com/store/I2C-RELAY16

*************************************************************************/

#include <Wire.h>
#include <Relay16.h>

Relay16 relayBoard;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Wire.begin();

// Both of the following initialization examples assume that address jumpers J5, J6, and J7
// on the I2C-RELAY16 are set to low (not solder jumpered).  If some of
// them are solder-shorted, you'll need to adjust those to HIGH below.

  relayBoard.begin(LOW, LOW, LOW);

// If the /IORST line on the I2C cable is tied to a pin, you can initialize
// it with that pin number.
//
// relayBoard.begin(LOW, LOW, LOW, 4);

}

void loop() {
  // print the results to the serial monitor:

  byte relayNum;

  for (relayNum = 1; relayNum <= 16; relayNum++)
  {
    relayBoard.relayOn(relayNum);
    delay(250);
    relayBoard.relayOff(relayNum);  
    
  }

  relayBoard.allOn();
  delay(250);
  relayBoard.allOff();
  delay(250);   

}
