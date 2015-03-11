#include <Wire.h>
#include "PGA309.h"

#define PGA309ADDR 0x40
#define REG3 0x0500
#define REG4 0x8000
#define REG6 0x0600

PGA309 pga(PGA309ADDR);

void setup() {
	Serial.begin(9600);
	Wire.begin();
	byte* data;
	
	//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	pga.enableTestPin();
	Serial.print("Status of writing to the PGA309 internal register 3: ");
	Serial.println(pga.writePGA309Register(0x03, REG3));
	delay(10);
	Serial.print("Status of writing to the PGA309 internal register 4: ");
	Serial.println(pga.writePGA309Register(0x04, REG4));
	delay(10);
	Serial.print("Status of writing to the PGA309 internal register 6: ");
	Serial.println(pga.writePGA309Register(0x06, REG6));
	delay(10);
	int testdata;
	testdata = pga.readPGA309Register(0x03);
	if (testdata != 0){
		Serial.print("There was error while reading: ");
		Serial.println(testdata);
	} else {
		Serial.print("Successfully read data from the register. Data: ");
		data = pga.getRecData();
		for (int i = 1; i >= 0 ; i--){
			Serial.print(pga.binaryFormat(data[i],8));
			Serial.print(" ");
		}
		Serial.println();
	}
	testdata = pga.readPGA309Register(0x04);
	if (testdata != 0){
		Serial.print("There was error while reading: ");
		Serial.println(testdata);
	} else {
		Serial.print("Successfully read data from the register. Data: ");
		data = pga.getRecData();
		for (int i = 1; i >= 0 ; i--){
			Serial.print(pga.binaryFormat(data[i],8));
			Serial.print(" ");
		}
		Serial.println();
	}
	testdata = pga.readPGA309Register(0x06);
	if (testdata != 0){
		Serial.print("There was error while reading: ");
		Serial.println(testdata);
	} else {
		Serial.print("Successfully read data from the register. Data: ");
		data = pga.getRecData();
		for (int i = 1; i >= 0 ; i--){
			Serial.print(pga.binaryFormat(data[i],8));
			Serial.print(" ");
		}
		Serial.println();
	}
	testdata = pga.readPGA309Register(0x08);
	if (testdata != 0){
		Serial.print("There was error while reading: ");
		Serial.println(testdata);
	} else {
		Serial.print("Successfully read data from the register. Data: ");
		data = pga.getRecData();
		for (int i = 1; i >= 0 ; i--){
			Serial.print(pga.binaryFormat(data[i],8));
			Serial.print(" ");
		}
		Serial.println();
	}

}

void loop() {
}
