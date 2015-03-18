#include <Wire.h>
#include "PGA309.h"
#include "ADS1110.h"

#define PGA309ADDR 0x40
#define ADS1110ADDR 0x49
#define REG1 0x0326
#define REG2 0xE77B
#define REG3 0x0500
#define REG4 0xE700
#define REG6 0x0600
#define ADSREG B10001101

void WriteToMultiRegisters(PGA309* _pga, int pregData[], int pregToWriteTo[], int size);
void ReadFromMultRegisters(PGA309* _pga, int pregToReadFrom[], int size);
void ReadADSData(ADS1110* _ads, byte data[]);
void ReadErrorREG(PGA309* _pga);

PGA309 pga(PGA309ADDR);
ADS1110 ads(ADS1110ADDR);

int regData[] = {REG1, REG2, REG3, REG4, REG6};
int regToWriteTo[] = {0x01, 0x02, 0x03, 0x04, 0x06};
int regToReadFrom[] = {0x01, 0x02, 0x03, 0x04, 0x06, 0x08};
byte ADSData[3];

void setup() {
	Serial.begin(9600);
	Wire.begin();
	
	
	//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	pga.enableTestPin();

	WriteToMultiRegisters(&pga, regData, regToWriteTo, (sizeof(regData)/sizeof(int)));
	ReadFromMultRegisters(&pga, regToReadFrom, (sizeof(regToReadFrom)/sizeof(int)));
	Serial.print("Status of writing to the ADS internal register:");
	Serial.println(ads.write(ADSREG));
	delay(1000);

}

void loop() {
	ReadADSData(&ads, ADSData);
	ReadErrorREG(&pga);
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