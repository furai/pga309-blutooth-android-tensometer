#include <Wire.h>
//#include <SendOnlySoftwareSerial.h>

#define PGA_ADDR 0x40
#define EEPROM_ADDR 0x50

int testPin = 52;
int prgPin = 48;

//SendOnlySoftwareSerial PGA309UART (prgPin);  

void setup(){
  Serial.begin(9600);
  Wire.begin();
  //PGA309UART.begin(9600);
  pinMode(testPin, OUTPUT);
  //pinMode(prgPin, OUTPUT);
  //Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
  //digitalWrite(testPin, HIGH);
  //The PRG pin should always be high when no communication is in progress
  //digitalWrite(prgPin, HIGH);
  delay(10);
  //Setting up the external EEPROM pointer address
  //Sending initialisation byte 0x55  
  //PGA309UART.write(0x55);
  //PGA309UART.write(0x02);
  byte rdata = 0xFF;
  byte rdata2 = 0xFF;
  Wire.beginTransmission(PGA_ADDR);
  Wire.write(0x01);
  Wire.write(13);
  Wire.write(15);
  Serial.println(Wire.endTransmission());
  delay(10);
  Wire.beginTransmission(PGA_ADDR);
  Wire.write(0x02);
  Serial.println(Wire.endTransmission());
  Wire.requestFrom(PGA_ADDR, 2);
  if (Wire.available()) rdata = Wire.read(); 
  if (Wire.available()) rdata2 = Wire.read();
  delay(10);
  Serial.println(rdata);
  Serial.println(rdata2);
}

void loop(){
}
  
