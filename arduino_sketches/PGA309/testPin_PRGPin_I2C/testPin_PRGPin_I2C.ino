#include <SendOnlySoftwareSerial.h>

int testPin = 52;
int prgPin = 48;

SendOnlySoftwareSerial PGA309UART (prgPin);  

void setup(){
  Serial.begin(9600);
  PGA309UART.begin(9600);
  pinMode(testPin, OUTPUT);
  pinMode(prgPin, OUTPUT);
  //Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
  digitalWrite(testPin, HIGH);
  //The PRG pin should always be high when no communication is in progress
  digitalWrite(prgPin, HIGH);
  delay(50);
  //Setting up the external EEPROM pointer address
  //Sending initialisation byte 0x55  
  PGA309UART.write(0x55);
  PGA309UART.write(0x02);
  PGA309UART.write();
  PGA309UART.write();
}

void loop(){
}
  
