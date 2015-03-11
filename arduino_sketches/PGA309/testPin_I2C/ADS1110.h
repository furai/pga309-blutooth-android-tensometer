/*
	ADS1110.h - Library for communicating with ADS1110.
	Created by Lucas Grzegorczyk, 05.03.2015
*/

#ifndef ADS1110_h
#define ADS1110_h
	
#include <Arduino.h>

class ADS1110
{
	public:
		ADS1110(int address);
		~ADS1110();
	private:
		ADS1110();
		int _address;
};

#endif