#PGA309 - Funduino Mega 2560 R3 + Communication over bluetooth with Android device.
###Short description
The purpose of this project is to measure tensions with use of tensometers (strain gauge) and pga309 in the sensor bridge configuration. Data will be sent to the android phone (which will plot it) over Bluetooth. All of the components will be connected to the Funduino Mega 2560 R3 for the ease of development.
The whole project is WIP.
###Current status and TODO
1. **PGA309**
	- [x] Basic communication
		- [x] Writing to internal registers
		- [x] Reading from internal registers
		- [x] Turning on/off test pin
	- [ ] More advanced functions
		- [ ] Creating register data knowing the correct calibration settings
		- [ ] Calculating internal nodes violations 
2. **ADS1110**
	- [ ] Basic communication
		- [x] Writing to internal register
		- [x] Reading from internal register
		- [x] Reading and displaying data
		- [ ] Sending data over BlueTooth
	- [ ] More advanced functions
		- [ ] Function allowing to set up desired gain without going over/under scale
3. **EEPROM24C02**
	- [x] Basic communication
		- [x] Writing to any memory location
		- [x] Reading from any memory location
		- [x] Clearing whole memory
	- [ ] More advanced functions
		- [ ] Basing on configuration settings calculate correct values that need to be written to EEPROM
		- [ ] Calculate checksums
		- [ ] Write those settings into EEPROM
4. **Android**
	- [ ] Basic BlueTooth communication
		- [x] Connecting to Funduino
		- [ ] Receiving/collecting data
	- [ ] Presentation of data
		- [ ] Plotting it
		- [ ] History
	- [ ] Calibration
		- [ ] Accepting basic input and calculating settings basic on it
		- [ ] Sending calibration data to PGA309
- [ ] Finish this list