#include <Wire.h>
#define PGA309Addr 0x40

int testPin = 52;

void writePGA309Register(unsigned int addr, int rgstr,  int data);
int readPGA309Register(unsigned int addr, int rgstr);

void setup(){
  Serial.begin(9600);
  //Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
  pinMode(testPin, OUTPUT);
  digitalWrite(testPin, HIGH);
  delay(20);
}

void loop(){
}
  
void writePGA309Register(unsigned int addr, int rgstr,  int data){
  Wire.beginTransmission(addr);
  Wire.write(rgstr);
}

int readPGA309Register(unsigned int addr, int rgstr){
  int recData
  Wire.beginTransmission(addr);
  Wire.write(rgstr);
  Wire.endTransmission(); 
  Wire.requestFrom(addr,1);
  if (Wire.available()) recData = Wire.receive();
  return recData;
}
