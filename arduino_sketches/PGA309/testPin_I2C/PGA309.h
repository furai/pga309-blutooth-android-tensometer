/*
	PGA309.h - Library for communicating with PGA309.
	Created by Lucas Grzegorczyk, 05.03.2015
*/

#ifndef PGA309_h
#define PGA309_h

#define TESTPIN 0x34
#define ARRAY_SIZE_PGA 2

#include <Arduino.h>

class PGA309
{
	public:
		PGA309(int address);
		~PGA309();
		void enableTestPin();
		void disableTestPin();
		int write(int rgstr,  int data);
		int read(int rgstr);
		int getAddress();
		void getRecData(byte data[]);
		byte readTempADC();
	private:
		PGA309();
		int _address;
		bool testPinEnabled;
		byte recData[ARRAY_SIZE_PGA];
};

#endif