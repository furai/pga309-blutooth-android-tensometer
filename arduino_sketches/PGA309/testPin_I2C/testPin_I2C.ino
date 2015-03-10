#include <Wire.h>
#include "PGA309.h"

#define PGA309ADDR 0x40

PGA309 pga(PGA309ADDR);

void setup() {
	Serial.begin(9600);
	Wire.begin();
	Serial.println(pga.getAddress());
	byte* data;
	data = pga.getRecData();
	for (int i = 0; i < 2; i++){
		Serial.print(pga.binaryFormat(data[i],8));
		Serial.print(" ");
	}
//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	// pinMode(testPin, OUTPUT);
	// digitalWrite(testPin, HIGH);
	// Serial.print("Status of writing to the PGA309 internal register: ");
	// Serial.println(writePGA309Register(0x02, 0x1248));
	// int testdata;
	// testdata = readPGA309Register(0x02, recData);
	// if (testdata < 0){
	// 	Serial.print("There was error while reading: ");
	// 	Serial.println(-testdata);
	// } else {
	// 	Serial.print("Successfully read data from the register. Data: ");
	// 	for (int i = 0; i < 2; i++){
	// 		print_binary(recData[i],8);
	// 		Serial.print(" ");
	// 	}
	// }
}

void loop() {
}
