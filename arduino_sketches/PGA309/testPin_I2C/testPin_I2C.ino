#include <Wire.h>
#include <Arduino.h>
#include "PGA309.h"
#include "ADS1110.h"
#include "Util.h"

#define PGA309ADDR 0x40
#define ADS1110ADDR 0x49
#define REG1 0x03C6
#define REG2 0xE77B
#define REG3 0x0500
#define REG4 0xE700
#define REG6 0x0600
#define ADSREG B10001101

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

	// util::WriteToMultiRegisters(&pga, regData, regToWriteTo, (sizeof(regData)/sizeof(int)));
	// util::ReadFromMultRegisters(&pga, regToReadFrom, (sizeof(regToReadFrom)/sizeof(int)));
	// Serial.print("Status of writing to the ADS internal register:");
	// Serial.println(ads.write(ADSREG));
	// delay(1000);

}

void loop() {
	// util::ReadADSData(&ads, ADSData);
	// util::ReadErrorREG(&pga);
}

