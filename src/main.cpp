#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial DataSerial(1);

/*
 * Forbind ESP1 (den du skal debugge) pin 16,
 * til RX på ESP2 (den der skal sende data), og
 * pin 17 på ESP1 til TX på ESP2.
 * Åben MATLAB og vælg ESP2.
 * Åben Serial Monitor for ESP1.
 * Kør MATLAB script!
*/

uint8_t s1RXpin = 17;
uint8_t s1TXpin = 16;

int16_t serialValue = 0;

void readTwoBytes(int16_t *val) {
	if (DataSerial.available() > 1) {
		byte lowbyte = DataSerial.read();
		*val = DataSerial.read();
		*val = ((*val)<<8) + lowbyte;
	}
}

void setup() {
	Serial.begin(115200);
	DataSerial.begin(115200, SERIAL_8N1, s1RXpin, s1TXpin);
}

void loop() {
	if (DataSerial.available() > 0) {
		readTwoBytes(&serialValue);
		//Serial.print("New value: ");
		Serial.println(serialValue);
	}
}