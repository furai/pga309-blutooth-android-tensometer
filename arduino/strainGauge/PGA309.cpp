/*
	PGA309.cpp - Library for communicating with PGA309.
	Created by Lucas Grzegorczyk, 05.03.2015
*/

#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include "PGA309.h"


/*	
	Default private constructor. Inaccessible by default.
	Initialises some variables.
*/
PGA309::PGA309(){
	testPinEnabled = false;
	recData[0] = 0;
	recData[1] = 0;	
	reg1 = {0x00, 0x00};
	reg2 = {0x00, 0x00};
	reg3 = {0x00, 0x00};
	reg4 = {0x00, 0x00};
	reg6 = {0x00, 0x00};
}


/*	
	Overloaded constructor. This one should be used.
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
	Function: write
		Writes 2 bytes of data to PGA309 register LSB first.
	Parameters:
		rgstr - register number (int)
		data - data to be written to the register (int)
	Returns:
		Integer - when different than 0 indicates error.
*/
int PGA309::write(int rgstr,  int data) {
	Wire.beginTransmission(_address);
	Wire.write(rgstr);
	Wire.write(data & 0xFF);	//LSB
	Wire.write(data >> 8);		//MSB
	return Wire.endTransmission();   
}

/*	
	Function: read
		Reads 2 bytes of data from PGA309 register and saves it to recData array.
	Parameters:
		rgstr - register number (int)
	Returns:
		Integer - when 0 indicates success, otherwise there was error.
*/
int PGA309::read(int rgstr) {
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
	Function: getAddress
		Get address on which PGA works.
	Returns:
		Integer - address of the PGA309
*/
int PGA309::getAddress(){
	return _address;
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

void PGA309::setRegisters(float zero_dac, float gain_dac, float coarse_offset, float front_pga, float out_pga, float v_ref /*= 4.096*/){
	int _reg1 = 0x0000, _reg2 = 0x0000, _reg3 = 0x0000, _reg4 = 0x0000, reg6 = 0x0000;
	if(zero_dac != 0){
		_reg1 = ceil(zero_dac/(v_ref/65536));
	}
	if(gain_dac != 0){
		
	}
}