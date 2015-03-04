int testPin = 52;

void setup(){
  Serial.begin(9600);
  //Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
  pinMode(testPin, OUTPUT);
  digitalWrite(testPin, HIGH);
  delay(20);
}

void loop(){
}
  
