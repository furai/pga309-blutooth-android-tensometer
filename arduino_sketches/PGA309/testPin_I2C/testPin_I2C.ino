#include <Wire.h>
#include <PGA309.h>
#define PGA309Addr 0x40

int testPin = 52;
byte recData[2];

int writePGA309Register(int rgstr,  int data);
int readPGA309Register(int rgstr, byte precData[]);
void print_binary(int v, int num_places);

void setup() {
	Serial.begin(9600);
	Wire.begin();
//Setting the test pin high enables direct writing of internal registers and stops transactions with External EEPROM
	pinMode(testPin, OUTPUT);
	digitalWrite(testPin, HIGH);
	Serial.print("Status of writing to the PGA309 internal register: ");
	Serial.println(writePGA309Register(0x02, 0x1248));
	int testdata;
	testdata = readPGA309Register(0x02, recData);
	if (testdata < 0){
		Serial.print("There was error while reading: ");
		Serial.println(-testdata);
	} else {
		Serial.print("Successfully read data from the register. Data: ");
		for (int i = 0; i < 2; i++){
			print_binary(recData[i],8);
			Serial.print(" ");
		}
	}
}

void loop() {
}

/*Function: writePGA309Register
Writes 2 bytes of data to PGA309 register.
Parameters:
rgstr - register number (int)
data - data to be written to the register (int)
Returns:
Integer - when different than 0 indicates error.
*/
int writePGA309Register(int rgstr,  int data) {
	Wire.beginTransmission(PGA309Addr);
	Wire.write(rgstr);
	Wire.write(data >> 8);
	Wire.write(data & 0xFF);
	return Wire.endTransmission();   
}

/*Function: readPGA309Register
Reads 2 bytes of data from PGA309 register.
Parameters:
rgstr - register number (int)
precData - pointer for the array of bytes
Returns:
Integer - when positive indicates success, when negative - means that there was error.
Modified arrray.
*/
int readPGA309Register(int rgstr, byte precData[]) {
	int error;
	Wire.beginTransmission(PGA309Addr);
	Wire.write(rgstr);
	if((error = Wire.endTransmission()) != 0)
		return -error;
	Wire.requestFrom(PGA309Addr, 2);
	int i = 0;

	while (Wire.available()){
		precData[i] = Wire.read();
		i++;
	}
}

void print_binary(int v, int num_places){
	int mask=0, n;

	for (n=1; n<=num_places; n++){
		mask = (mask << 1) | 0x0001;
	}

	v = v & mask;  // truncate v to specified number of places

	while(num_places){
		if (v & (0x0001 << num_places-1)){
			Serial.print("1");
		} else {
			Serial.print("0");
		}

		--num_places;

		// if(((num_places%4) == 0) && (num_places != 0))
		// {
		// 	Serial.print("_");
		// }
	}
}
