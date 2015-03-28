/*
	EEPROM24C02.h - Library for communicating with EEPROM24C02.
	Created by Lucas Grzegorczyk, 20.03.2015
*/
#ifndef EEPROM24C02_h
#define EEPROM24C02_h

#define ARRAY_SIZE_EEPROM 2

#include <Arduino.h>

class EEPROM24C02
{
	public:
		EEPROM24C02(int address);
		~EEPROM24C02();
		int read(int addr);
		int read2bytes(int addr);
		int write(int addr, byte data);
		int write2bytes(int addr, int data);
		byte getRecData();
		void getRecData(byte data[]);
		void clear();
	private:
		EEPROM24C02();
		int _address;
		byte recData[ARRAY_SIZE_EEPROM];
};


#endif