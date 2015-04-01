/*
	PGA309.h - Library for communicating with PGA309.
	Created by Lucas Grzegorczyk, 05.03.2015
*/

#ifndef PGA309_h
#define PGA309_h

#define TESTPIN 0x34
#define ARRAY_SIZE_PGA 2
#define NUMBER_OF_REGISTERS 6

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
		int writeRegisters();
		void setRegisters(	float zero_dac, float gain_dac, float coarse_offset, float front_pga, float out_pga,
							float v_ref = 4.096, bool continConvMode = false, bool intTempMode = true,
							bool VexcEnable = true, bool intVrefSelect = false, bool intVrefEnable = true);
	private:
		int _registers[NUMBER_OF_REGISTERS];
		PGA309();
		int _address;
		bool testPinEnabled;
		byte recData[ARRAY_SIZE_PGA];
		int calcRegCoarseOffset(float coarse_offset, float v_ref);
		int calcRegFrontPGA(float front_pga);
		int calcRegOutPGA(float out_pga);
};

#endif