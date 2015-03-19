/*
	Util.cpp - Library with helper functions.
	Its sole purpose is to remove the functions from the main .ino file.
	Created by Lucas Grzegorczyk, 18.03.2015
*/
#include <Arduino.h>
#include <Wire.h>
#include "PGA309.h"
#include "ADS1110.h"
#include "Util.h"

namespace util{
	void WriteToMultiRegisters(PGA309* _pga, int pregData[], int pregToWriteTo[], int size){
		for (int i = 0; i < size; i++){
			Serial.print("Status of writing to the PGA309 internal register ");
			Serial.print(pregToWriteTo[i]);
			Serial.print(": ");
			Serial.println(_pga->writePGA309Register(pregToWriteTo[i], pregData[i]));
			delay(5);
		}
	}

	void ReadFromMultRegisters(PGA309* _pga, int pregToReadFrom[], int size){
		int testdata;
		byte data[2];
		for (int i = 0; i < size; i++){
			testdata = _pga->readPGA309Register(pregToReadFrom[i]);
			if (testdata != 0){
				Serial.print("There was error while reading data from register ");
				Serial.print(pregToReadFrom[i]);
				Serial.print(": ");
				Serial.println(testdata);
			} else {
				Serial.print("Successfully read data from the register ");
				Serial.print(pregToReadFrom[i]);
				Serial.print(". Data: ");
				_pga->getRecData(data);
				for (int i = 1; i >= 0 ; i--){
					Serial.print(_pga->binaryFormat(data[i],8));
					Serial.print(" ");
				}
				Serial.println();
			}
			delay(5);
		}
	}	

	void ReadErrorREG(PGA309* _pga){
		int testdata;
		byte data[2];

		testdata = _pga->readPGA309Register(0x08);
		if (testdata != 0){
			Serial.print("There was error while reading data from register ");
			Serial.print(0x08);
			Serial.print(": ");
			Serial.println(testdata);
		} else {
			Serial.print("Successfully read data from the register ");
			Serial.print(0x08);
			Serial.print(". Data: ");
			_pga->getRecData(data);
			for (int i = 1; i >= 0 ; i--){
				Serial.print(_pga->binaryFormat(data[i],8));
				Serial.print(" ");
			}
			Serial.println();
		}
		delay(5);
	}

	void ReadADSData(ADS1110* _ads, byte data[]){
		_ads->read();
		_ads->getRecData(data);
		Serial.println((data[0] * 256) + data[1]);
		delay(200);
	}

	void printMenu(){
		Serial.println("What would you like to do?");
		Serial.println("1. Enable/disable test pin.");
		Serial.println("2. Write to PGA309 registers.");
		Serial.println("3. Write to ADS1110 registers.");
		Serial.println("4. Continuous read from PGA309 error register.");
		Serial.println("5. Continuous read from ADS1110.");

	}

}	