#include <Arduino.h>

//#include "SerialMP3Player.h"
#include "PCF8575.h"
#include <PxMatrix.h> // For P10 LED matrix
#include <Wire.h>

#define TX 5
#define RX 6
// Define PCF8575 I2C address
//#define PCF8575_ADDRESS 0x20

#define IRQPIN 2
// Define pins for P10 LED matrix display
#define P_LAT 8
#define P_A 9
#define P_B 10
#define P_C 11
#define P_D 12
#define P_OE 13

// Create instances for PCF8575 and LED matrix display
PCF8575 PCF(0x20);
PxMATRIX display(32, 16, P_LAT, P_OE, P_A, P_B, P_C, P_D);
//SerialMP3Player mp3(RX,TX);

bool keyChanged = false;
uint16_t points = 0;

void pcf_irq()
{
  keyChanged = true;
}

void setup() {
  // Start Serial for debugging
  Serial.begin(9600);

  // Initialize PCF8575
  Wire.begin();
  // Set PCF8575 pins as input with pull-up resistors
  PCF.begin();
  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), pcf_irq, FALLING);

  // Initialize LED matrix display
  display.begin(8);           // Lower refresh rate for Arduino Uno
  display.setFastUpdate(true); // Faster refresh
  display.clearDisplay();
}

void loop()
{
  // Reset total points
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(0);
  // Read inputs and calculate the score
  if (keyChanged)
  {
    switch (PCF.read16())
    {
      case 0:
        points = 0;
        break;
      case 1:
        points = 1;
        break;
      case 2:
        points = 2;
        break;
      case 4:
        points = 3;
        break;
      case 8:
        points = 4;
        break;
      case 16:
        points = 5;
        break;
      case 32:
        points = 6;
        break;
      case 64:
        points = 7;
        break;
      case 128:
        points = 8;
        break;
      case 256:
        points = 9;
      case 512:
        points = 10;
        break;
    }
     
  // Clear display and show the score
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(points);

    // Debugging: Output the score to Serial
    Serial.print("Total Points: ");
    Serial.println(points);

    delay(2000); 
    keyChanged = false;
  }
}