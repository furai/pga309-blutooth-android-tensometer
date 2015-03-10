#include <Wire.h>
#include "PGA309.h"

#define PGA309ADDR 0x40

PGA309 pga(PGA309ADDR);

void setup() {
	Serial.begin(9600);
	Wire.begin();
	Serial.println(pga.getAddress());
	byte* data;
	
	//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	pga.enableTestPin();
	Serial.print("Status of writing to the PGA309 internal register: ");
	Serial.println(pga.writePGA309Register(0x03, 0x1248));
	int testdata;
	testdata = pga.readPGA309Register(0x03);
	if (testdata != 0){
		Serial.print("There was error while reading: ");
		Serial.println(testdata);
	} else {
		Serial.print("Successfully read data from the register. Data: ");
		data = pga.getRecData();
		for (int i = 0; i < 2; i++){
			Serial.print(pga.binaryFormat(data[i],8));
			Serial.print(" ");
		}
	}
}

void loop() {
}
