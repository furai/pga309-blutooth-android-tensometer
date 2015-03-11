/*
	PGA309.h - Library for communicating with PGA309.
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
	_address = address;
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
	Wire.beginTransmission(_address);
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
		precData - pointer for the array of bytes
	Returns:
		Integer - when 0 indicates success, otherwise there was error.
*/
int PGA309::readPGA309Register(int rgstr) {
	int error;
	Wire.beginTransmission(_address);
	Wire.write(rgstr);
	if((error = Wire.endTransmission()) != 0)
		return error;
	Wire.requestFrom(_address, 2);
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

int PGA309::getAddress(){
	return _address;
}

byte* PGA309::getRecData(){
	return recData;
}