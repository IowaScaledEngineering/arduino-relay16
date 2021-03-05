# Relay16 Arduino Library for the Iowa Scaled Engineering I2C-RELAY16 and I2C-RELAY16-QWIIC

## Summary

The [Iowa Scaled Engineering I2C-RELAY16](https://www.iascaled.com/store/I2C-RELAY16) is an I2C-compatible driver board for
commonly available Chinese-made 16-relay boards that have 16 SPDT relays and a 20-pin header for control.

The I2C-RELAY16 comes in two varieties:
* [I2C-RELAY16](https://www.iascaled.com/store/I2C-RELAY16) - A 5V version with 6p6c connectors at each end
* [I2C-RELAY16-QWIIC](https://www.iascaled.com/store/I2C-RELAY16-QWIIC) - A 3.3V version that is compatible with the [Qwiic I2C standard](https://www.sparkfun.com/qwiic).

Both are identical from a software standpoint, and the Relay16 library will work with both.

The Relay16 library is built to make controlling these boards simple and straightforward from the Arduino environment.

## Hardware

[Schematic for I2C-RELAY16 v3.0](https://github.com/IowaScaledEngineering/i2c-relay16/raw/master/pg/i2c-relay16-v3.0-3cc69a9/i2c-relay16.pdf)

[ISE I2C 6p6c Connector Standard](https://www.iascaled.com/store/6P6C-I2C)

[Schematic for I2C-RELAY16-QWIIC v3.0](https://github.com/IowaScaledEngineering/i2c-relay16/raw/master/pg/i2c-relay16-qwiic-v3.0-38b1970/i2c-relay16-qwiic.pdf)

### Solder Jumpers

The v3.0 PCBs include three solder jumpers that can be closed using a soldering iron and little bit of solder to bridge the gap.   These three
jumpers set the board address, allowing up to 8 I2C-RELAY16 boards on an individual I2C bus.

* J5 - Pull Address line A0 high.  If open, A0 is low (default).
* J6 - Pull Address line A1 high.  If open, A1 is low (default).
* J7 - Pull Address line A2 high.  If open, A2 is low (default).

| J5    | J6    | J7    | 7-bit I2C Address |
|-------|-------|-------|-------------------|
| Open  | Open  | Open  | 0x20              |
| Short | Open  | Open  | 0x21              |
| Open  | Short | Open  | 0x22              |
| Short | Short | Open  | 0x23              |
| Open  | Open  | Short | 0x24              |
| Short | Open  | Short | 0x25              |
| Open  | Short | Short | 0x26              |
| Short | Short | Short | 0x27              |

-----

## Software - The Arduino-Compatible Relay16 Library

### Arduino Library Installation

The easiest way is to search for "Relay16" in the Arduino Library manager.

Alternately, you can manually download and install it from [our Github repository](https://github.com/IowaScaledEngineering/arduino-relay16).

-----

### Relay16 Library Functions and Class Methods

The board is represented by a Relay16 object with the following methods available:

#### void begin();
#### void begin(boolean j5, boolean j6, boolean j7, int8_t dioReset=-1);
#### void begin(TwoWire& i2cInterface, boolean j5=false, boolean j6=false, boolean j7=false, int8_t dioReset=-1);
#### void begin(TwoWire& i2cInterface, uint8_t address, int8_t dioReset=-1);

Before using the Relay16 object, begin() must be called once. This initializes the object and stores the address of the I2C-RELAY16 that the object will control,
as well as some optional other parameters

If called with no parameters, it defaults to all solder address jumpers open (address 0x20) and on the default Wire interface.

__Arguments:__
* i2cInterface (optional) - If the I2C interface is not the default "Wire" interface, you can specify another one during initialization.
* j5 / j6 / j7 (optional) - The state of the address solder jumpers.  "false" indicates the jumper is NOT soldered closed, "true" indicates that the jumper is soldered / shorted.
* address (optional) - The explicit 7-bit I2C address, if you are controlling the relay16 through an address changer
* dioReset (optional) - The Arduino digital I/O connected to the reset line, if used (only available on the I2C-RELAY16, not available on Qwiic).  Set to -1 if not used.

__Return values:__
* true - initialization was successful
* false - initialization failed

-----

#### boolean relayOn(uint8_t relayNum);

Turns on a relay on the Relay16.

__Arguments:__
* relayNum - Integer 1 through 16.

__Return values:__
* true - command was successful
* false - command failed

-----

#### boolean relayOff(uint8_t relayNum);

Turns off a relay on the Relay16.

__Arguments:__
* relayNum - Integer 1 through 16.

__Return values:__
* true - command was successful
* false - command failed

-----

#### boolean digitalWrite(uint8_t relayNum, uint8_t relayState)

Works just like the built-in digitalWrite function works on a pin, except this one sets a relay to HIGH (on) or LOW (off).

__Arguments:__
* relayNum - Integer 1 through 16.
* relayState - LOW / zero = off, HIGH / non-zero = on

__Return values:__
* true - command was successful
* false - command failed

-----

#### boolean allOn()

Turns on all relays on this Relay16

__Return values:__
* true - command was successful
* false - command failed

-----

#### boolean allOff()

Turns off all relays on this Relay16

__Return values:__
* true - command was successful
* false - command failed

-----

#### boolean refresh()

Sends the current state of all relays back to the Relay16 board.  Normally this is done every time you call a function to change
the state of a relay, but sometimes it's handy to refresh the whole board in case something glitches.

__Return values:__
* true - command was successful
* false - command failed

-----

## License

Like all public Iowa Scaled Engineering designs, the I2C-RELAY16 and Relay16 library are open hardware and open source software.  Please refer to the hardware and software license files in the respective repositories for details.
