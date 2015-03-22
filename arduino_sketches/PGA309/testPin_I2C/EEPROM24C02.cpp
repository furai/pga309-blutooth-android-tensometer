/*
	EEPROM24C02.cpp - Library for communicating with EEPROM24C02.
	Created by Lucas Grzegorczyk, 20.03.2015
*/
#include <Arduino.h>
#include <Wire.h>
#include "EEPROM24C02.h"

/*
	Default private constructor.
*/
EEPROM24C02::EEPROM24C02(){
	recData = 0;
}

/*
	Overloaded constructor.
*/
EEPROM24C02::EEPROM24C02(int address):EEPROM24C02::EEPROM24C02(){
	_address = address;
}

/*
	Default destructor.
*/
EEPROM24C02::~EEPROM24C02(){
	//Nothing to destruct.
}

/*
	Function: read
		Reads from EEPROM24C02 memory address.
	Parameters:
		data - data written to memory (byte)
	Returns:
		Integer - 0 successful write, anything else error.
*/
int EEPROM24C02::read(int addr){
	int error;
	Wire.beginTransmission(_address);
	Wire.write(addr);
	if((error = Wire.endTransmission()) != 0)
		return error;
	Wire.requestFrom(_address, 1);
	while (Wire.available()){
		recData = Wire.read();
	}
}

/*
	Function: write
		Writes to EEPROM24C02 memory address.
	Parameters:
		data - data written to the memory address (byte)
	Returns:
		Integer - 0 successful write, anything else error.
*/
int EEPROM24C02::write(int addr, byte data){
	Wire.beginTransmission(_address);
	Wire.write(addr);
	Wire.write(data);
	return Wire.endTransmission(); 
}

/*
	Function: write
		Writes to EEPROM24C02 memory address.
	Parameters:
		data - data written to the memory address (byte)
	Returns:
		Integer - 0 successful write, anything else error.
*/
int EEPROM24C02::write2bytes(int addr, int data){
	Wire.beginTransmission(_address);
	Wire.write(addr);
	Wire.write(data & 0xFF);	//LSB
	Wire.write(data >> 8);		//MSB
	return Wire.endTransmission(); 
}


/*
	Function: getRecDeta
		Gets received data from the EEPROM24C02.
	Parameters:
		Array to be modified and filled with data (byte[])
*/
byte EEPROM24C02::getRecData(){
	return recData;
}