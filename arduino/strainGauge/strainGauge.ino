#include <Wire.h>
#include <Arduino.h>
#include "PGA309.h"
#include "ADS1110.h"
#include "EEPROM24C02.h"
#include "Util.h"

#define PGA309ADDR 0x40
#define ADS1110ADDR 0x49
#define EEPROM24C02ADDR 0x50
#define REG1 0x03C6
#define REG2 0xE77B
#define REG3 0x0500
#define REG4 0xE700
#define REG6 0x1200
#define ADSREG B10001101

PGA309 pga(PGA309ADDR);
ADS1110 ads(ADS1110ADDR);
EEPROM24C02 eeprom(EEPROM24C02ADDR);

// int regData[] = {REG1, REG2, REG3, REG4, REG6};
// int regToWriteTo[] = {0x01, 0x02, 0x03, 0x04, 0x06};
int regToReadFrom[] = {0x01, 0x02, 0x03, 0x04, 0x06, 0x08};
int regData[] = {REG1, REG2};
int regToWriteTo[] = {0x01, 0x02};
// int regToReadFrom[] = {0x01, 0x02};
byte ADSData[3];
int memData[] = {0x5449, 0x0000, 0x0000, REG3, REG4, 0x0000, REG6, (0xFFFF-((0x5449+REG3+REG4+REG6)&0xFFFF)), 0x0280, REG1, REG2, 0x7FFF, 0x0000, (0xFFFF-((0x0280+REG1+REG2+0x7FFF)&0xFFFF))};
int memToWriteToReadFrom[] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A};

void setup(){
	Serial.begin(19200);
	Wire.begin();
	
	
	//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	pga.enableTestPin();
	delay(100);
	// eeprom.clear();
	// util::WriteToMultiEEPROM(&eeprom, memData, memToWriteToReadFrom,  (sizeof(memToWriteToReadFrom)/sizeof(int)));
	// util::ReadFromMultEEPROM(&eeprom, memToWriteToReadFrom, (sizeof(memToWriteToReadFrom)/sizeof(int)));
	// delay(1000);
	


	// util::WriteToMultiRegisters(&pga, regData, regToWriteTo, (sizeof(regData)/sizeof(int)));
	// util::ReadFromMultRegisters(&pga, regToReadFrom, (sizeof(regToReadFrom)/sizeof(int)));
	Serial.print("Status of writing to the ADS internal register:");
	Serial.println(ads.write(ADSREG));
	delay(100);
	pga.disableTestPin();
	delay(100);
}

void loop(){
	// util::printMenu();
	util::ReadADSData(&ads, ADSData);
	// util::ReadErrorREG(&pga);
	// util::ReadFromMultRegisters(&pga, regToReadFrom, (sizeof(regToReadFrom)/sizeof(int)));
}