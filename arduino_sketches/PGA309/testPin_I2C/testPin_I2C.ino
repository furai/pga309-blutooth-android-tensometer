#include <Wire.h>
#include "PGA309.h"
#include "ADS1110.h"

#define PGA309ADDR 0x40
#define ADS1110ADDR 0x49
#define REG3 0x0500
#define REG4 0xE300
#define REG6 0x0600

void WriteToMultiRegisters(int pregData[], int pregToWriteTo[], int size);
void ReadFromMultRegisters(int pregToReadFrom[], int size);

PGA309 pga(PGA309ADDR);

int regData[] = {REG3, REG4, REG6};
int regToWriteTo[] = {0x03, 0x04, 0x06};
int regToReadFrom[] = {0x03, 0x04, 0x06, 0x08};

void setup() {
	Serial.begin(9600);
	Wire.begin();
	
	
	//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	pga.enableTestPin();

	WriteToMultiRegisters(regData, regToWriteTo, (sizeof(regData)/sizeof(int)));
	ReadFromMultRegisters(regToReadFrom, (sizeof(regToReadFrom)/sizeof(int)));
}

void loop() {
}

//======================================================
// Helper functions
void WriteToMultiRegisters(int pregData[], int pregToWriteTo[], int size){
	for (int i = 0; i < size; i++){
		Serial.print("Status of writing to the PGA309 internal register ");
		Serial.print(pregToWriteTo[i]);
		Serial.print(": ");
		Serial.println(pga.writePGA309Register(pregToWriteTo[i], pregData[i]));
		delay(5);
	}
}

void ReadFromMultRegisters(int pregToReadFrom[], int size){
	int testdata;
	byte data[2];
	for (int i = 0; i < size; i++){
	testdata = pga.readPGA309Register(pregToReadFrom[i]);
	if (testdata != 0){
		Serial.print("There was error while reading data from register ");
		Serial.print(pregToReadFrom[i]);
		Serial.print(": ");
		Serial.println(testdata);
	} else {
		Serial.print("Successfully read data from the register ");
		Serial.print(pregToReadFrom[i]);
		Serial.print(". Data: ");
		pga.getRecData(data);
		for (int i = 1; i >= 0 ; i--){
			Serial.print(pga.binaryFormat(data[i],8));
			Serial.print(" ");
		}
		Serial.println();
	}
		delay(5);
	}
}