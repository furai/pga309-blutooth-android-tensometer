/*
	PGA309.cpp - Library for communicating with PGA309.
	Created by Lucas Grzegorczyk, 05.03.2015
*/

#include <Arduino.h>
#include <Wire.h>
#include "PGA309.h"

/*	
	Default private constructor. Inaccessible by default.
	Initialises some variables.
*/
PGA309::PGA309(){
	testPinEnabled = false;
	recData[0] = 0;
	recData[1] = 0;	
}


/*	
	Overloaded constructor. This one should be uesd.
*/
PGA309::PGA309(int address):PGA309::PGA309(){
	_addr = address;
}

/*	
	Simple destructor.
*/
PGA309::~PGA309(){
	//nothing to clean up
}

/*	
	Function: enableTestPin
		Enables test pin on PGA309.
*/
void PGA309::enableTestPin(){
	if (!testPinEnabled){
		pinMode(TESTPIN, OUTPUT);
		digitalWrite(TESTPIN, HIGH);
		testPinEnabled = true;
	}
}

void PGA309::disableTestPin(){
	if (testPinEnabled){
		pinMode(TESTPIN, INPUT);
		testPinEnabled = false;
	}
}

/*	
	Function: writePGA309Register
		Writes 2 bytes of data to PGA309 register LSB first.
	Parameters:
		rgstr - register number (int)
		data - data to be written to the register (int)
	Returns:
		Integer - when different than 0 indicates error.
*/
int PGA309::writePGA309Register(int rgstr,  int data) {
	Wire.beginTransmission(_addr);
	Wire.write(rgstr);
	Wire.write(data & 0xFF);	//LSB
	Wire.write(data >> 8);		//MSB
	return Wire.endTransmission();   
}

/*	
	Function: readPGA309Register
		Reads 2 bytes of data from PGA309 register and saves it to recData array.
	Parameters:
		rgstr - register number (int)
	Returns:
		Integer - when 0 indicates success, otherwise there was error.
*/
int PGA309::readPGA309Register(int rgstr) {
	int error;
	Wire.beginTransmission(_addr);
	Wire.write(rgstr);
	if((error = Wire.endTransmission()) != 0)
		return error;
	Wire.requestFrom(_addr, 2);
	int i = 0;
	while (Wire.available()){
		recData[i] = Wire.read();
		i++;
	}
}

/*	
	Function: print_binary
		Prints number in binary format with leading zeros.
	Parameters:
		v - number (int)
		numOfPlaces - number of places to display (int)
*/
String PGA309::binaryFormat(int v, int numOfPlaces){
	int mask=0, n;
	String str = "";

	for (n=1; n<=numOfPlaces; n++){
		mask = (mask << 1) | 0x0001;
	}

	v = v & mask;  

	while(numOfPlaces){
		if (v & (0x0001 << numOfPlaces-1)){
			str += '1';
		} else {
			str += '0';
		}

		--numOfPlaces;
	}
	return str;
}


/*
	Function: getAddress
		Get address on which PGA works.
	Returns:
		Integer - address of the PGA309
*/
int PGA309::getAddress(){
	return _addr;
}


/*
	Function: getRecDeta
		Gets received data from the PGA 309.
	Parameters:
		Array to be modified and filled with data (byte[])
*/
void PGA309::getRecData(byte data[]){
	data[0] = recData[0];
	data[1] = recData[1];
}