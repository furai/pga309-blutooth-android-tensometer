#include <Wire.h> 

#define chip 0x50

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write(eeaddress);
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF; 
  Wire.beginTransmission(deviceaddress);
  Wire.write(eeaddress >> 8);  
  Wire.endTransmission();
   Wire.requestFrom(deviceaddress,1); 
  if (Wire.available()) rdata = Wire.read();
   return rdata;
}

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();  
 
  unsigned int address = 1;
 
  writeEEPROM(0x50, address, 13);
  delay(5);
  Serial.print(readEEPROM(chip, address), DEC);
}

void loop(){}
