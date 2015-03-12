#include <Wire.h>
#include "PGA309.h"
#include "ADS1110.h"

#define PGA309ADDR 0x40
#define ADS1110ADDR 0x49
#define REG3 0x0500
#define REG4 0xE300
#define REG6 0x0600

void WriteToMultiRegisters(PGA309* _pga, int pregData[], int pregToWriteTo[], int size);
void ReadFromMultRegisters(PGA309* _pga, int pregToReadFrom[], int size);
void ReadADSData(ADS1110* _ads, byte data[]);

PGA309 pga(PGA309ADDR);
// ADS1110 ads(ADS1110ADDR);

int regData[] = {REG3, REG4, REG6};
int regToWriteTo[] = {0x03, 0x04, 0x06};
int regToReadFrom[] = {0x03, 0x04, 0x06, 0x08};
byte ADSData[3];

void setup() {
	Serial.begin(9600);
	Wire.begin();
	
	
	//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	pga.enableTestPin();

	WriteToMultiRegisters(&pga, regData, regToWriteTo, (sizeof(regData)/sizeof(int)));
	ReadFromMultRegisters(&pga, regToReadFrom, (sizeof(regToReadFrom)/sizeof(int)));
	delay(1000);
}

void loop() {
	//ReadADSData(&ads, ADSData);
}

//======================================================
// Helper functions
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

void ReadADSData(ADS1110* _ads, byte data[]){
	_ads->read();
	_ads->getRecData(data);
	Serial.println((data[0] * 256) + data[1]);
	delay(200);
}