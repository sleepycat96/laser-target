#include "Arduino.h"
#include "PCF8575.h"
#include " SerialMP3Player.h"

#define TX 11
#define RX 10
#define SHOTSOUND 11

SerialMP3Player mp3(RX,TX);

// Instantiate Wire for generic use at 400kHz
TwoWire I2Cone = TwoWire(0);

// For arduino uno only pin 1 and 2 are interrupted
#define ESP_INTERRUPTED_PIN 2

// Function interrupt
void keyChangedOnPCF8575();

// Set i2c address
PCF8575 pcf8575(&I2Cone,0x20, 21, 22, ESP_INTERRUPTED_PIN, keyChangedOnPCF8575);
unsigned long timeElapsed;

int diem = 0;
void setup()
{
	Serial.begin(115200);

	pcf8575.pinMode(P0, INPUT);
	pcf8575.pinMode(P1, INPUT);
	pcf8575.pinMode(P2, INPUT);
	pcf8575.pinMode(P3, INPUT);
 	pcf8575.pinMode(P4, INPUT);
 	pcf8575.pinMode(P5, INPUT);
	pcf8575.pinMode(P6, INPUT);
	pcf8575.pinMode(P7, INPUT);
	pcf8575.pinMode(P8, INPUT);
 	pcf8575.pinMode(P9, INPUT);

	pcf8575.begin();

	Serial.println("START");

	timeElapsed = millis();
}

bool keyChanged = false;
void loop()
{
	if (keyChanged){
		PCF8575::DigitalInput di = pcf8575.digitalReadAll();
    	if (di.p0 == 1) diem = 1;
    	if (di.p1 == 1) diem = 2;
   		if (di.p2 == 1) diem = 3;
    	if (di.p3 == 1) diem = 4;
    	if (di.p4 == 1) diem = 5;
    	if (di.p5 == 1) diem = 6;
    	if (di.p6 == 1) diem = 7;
    	if (di.p7 == 1) diem = 8;
    	if (di.p8 == 1) diem = 9;
    	if (di.p9 == 1) diem = 10;
		keyChanged= false;
	}
	if (diem != 0) baodiem(diem);
	
}

void baodiem(int d)
{
	mp3.play(SHOTSOUND);
	mp3.play(d);
}
void keyChangedOnPCF8575(){
	// Interrupt called (No Serial no read no wire in this function, and DEBUG disabled on PCF library)
	 keyChanged = true;
}