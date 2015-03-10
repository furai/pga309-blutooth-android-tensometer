/*
	PGA309.h - Library for communicating with PGA309.
	Created by Lucas Grzegorczyk, 05.03.2015
*/

#include <Arduino.h>
#include "PGA309.h"

PGA309::PGA309(int address){
	_address = address;
	testPinEnabled = false;
	recData[0] = 0;
	recData[1] = 0;
}

void PGA309::enableTestPin(){
	if (!testPinEnabled){
		pinMode(testPin, OUTPUT);
	}
}

void PGA309::disableTestPin(){

}

/*	Function: writePGA309Register
		Writes 2 bytes of data to PGA309 register.
	Parameters:
		rgstr - register number (int)
		data - data to be written to the register (int)
	Returns:
		Integer - when different than 0 indicates error.
*/
int PGA309::writePGA309Register(int rgstr,  int data) {
	Wire.beginTransmission(PGA309Addr);
	Wire.write(rgstr);
	Wire.write(data >> 8);
	Wire.write(data & 0xFF);
	return Wire.endTransmission();   
}

/*	Function: readPGA309Register
		Reads 2 bytes of data from PGA309 register.
	Parameters:
		rgstr - register number (int)
		precData - pointer for the array of bytes
	Returns:
		Integer - when positive indicates success, when negative - means that there was error.
		Modified arrray.
*/
int PGA309::readPGA309Register(int rgstr, byte precData[]) {
	int error;
	Wire.beginTransmission(PGA309Addr);
	Wire.write(rgstr);
	if((error = Wire.endTransmission()) != 0)
		return -error;
	Wire.requestFrom(PGA309Addr, 2);
	int i = 0;

	while (Wire.available()){
		precData[i] = Wire.read();
		i++;
	}
}

/*	Function: print_binary
		Prints number in binary format with leading zeros.
	Parameters:
		v - number (int)
		num_places - number of places to display (int)
*/
String PGA309::binaryFormat(int v, int numOfPlaces){
	int mask=0, n;
	String str = "";

	for (n=1; n<=num_places; n++){
		mask = (mask << 1) | 0x0001;
	}

	v = v & mask;  

	while(num_places){
		if (v & (0x0001 << num_places-1)){
			str += '1';
		} else {
			str += '0';
		}

		--num_places;
	}
	return str;
}
