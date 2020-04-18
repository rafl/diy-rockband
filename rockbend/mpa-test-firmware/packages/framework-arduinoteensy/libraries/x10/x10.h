/*
 	x10.h - - X10 transmission library for Arduino - Version 0.4
  
  Original library		(0.1) by Tom Igoe.
  Timing bug fixes		(0.2) "   "   "

	Sends X10 commands.

*/

// ensure this library description is only included once
#ifndef x10_h
#define x10_h

// include types & constants of Wiring core API
#include "Arduino.h"

#define BIT_DELAY 1778    	// 1778 us between bit repeats in a half-cycle
#define BIT_LENGTH 800		// each bit is slightly less than 1ms long

#define	HOUSE_A	B0110
#define	HOUSE_B	B1110	
#define	HOUSE_C	B0010
#define	HOUSE_D	B1010
#define	HOUSE_E	B0001
#define	HOUSE_F	B1001
#define	HOUSE_G	B0101
#define	HOUSE_H	B1101
#define	HOUSE_I	B0111
#define	HOUSE_J	B1111
#define	HOUSE_K	B0011
#define	HOUSE_L	B1011
#define	HOUSE_M	B0000
#define	HOUSE_N	B1000
#define HOUSE_O	B0100
#define HOUSE_P	B1100

#define UNIT_1	B01100
#define UNIT_2	B11100
#define UNIT_3	B00100
#define UNIT_4	B10100
#define UNIT_5	B00010
#define UNIT_6	B10010
#define UNIT_7	B01010
#define UNIT_8	B11010
#define UNIT_9	B01110
#define UNIT_10	B11110
#define UNIT_11	B00110
#define UNIT_12	B10110
#define UNIT_13	B00000
#define UNIT_14	B10000
#define UNIT_15	B01000
#define UNIT_16	B11000

#define ALL_UNITS_OFF	B00001
#define ALL_LIGHTS_ON	B00011
#define ON				B00101
#define OFF				B00111
#define DIM				B01001
#define BRIGHT			B01011
#define ALL_LIGHTS_OFF	B01101
#define EXTENDED_CODE	B01111
#define HAIL_REQUEST	B10001
#define HAIL_ACKNOWLEDGE	B10011
#define PRE_SET_DIM			B10101
#define EXTENDED_DATA		B11001
#define STATUS_ON			B11011
#define STATUS_OFF			B11101
#define STATUS_REQUEST		B11111

// library interface description
class x10 {
  public:
	// constructors:
	x10(uint8_t zeroCrossingPin, uint8_t dataPin);
	// write command method:
	void write(byte houseCode, byte numberCode, byte numRepeats);
	// returns the version number:
	int version(void);

  private:
	volatile uint8_t *zeroCrossingReg;	// AC zero crossing pin
	uint8_t zeroCrossingBit;
  	uint8_t dataPin;			// data out pin
  	// sends the individual bits of the commands:
	void sendBits(byte cmd, byte numBits, byte isStartCode);
	// checks for AC zero crossing
	void waitForZeroCross(void);
};

#endif

