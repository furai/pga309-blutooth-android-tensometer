/*
	Util.h - Library with helper functions.
	Its sole purpose is to remove the functions from the main .ino file.
	Created by Lucas Grzegorczyk, 18.03.2015
*/
#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

namespace util{
	void WriteToMultiRegisters(PGA309* _pga, int pregData[], int pregToWriteTo[], int size);
	void ReadFromMultRegisters(PGA309* _pga, int pregToReadFrom[], int size);
	void ReadADSData(ADS1110* _ads, byte data[]);
	void ReadErrorREG(PGA309* _pga);
	void printMenu();
	String binaryFormat(int n, int numOfPlaces);
	void WriteToMultiEEPROM(EEPROM24C02* _eeprom, int pmemData[], int pmemToWriteTo[], int size);
}

#endif