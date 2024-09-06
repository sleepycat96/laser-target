#include "SerialMP3Player.h"
#include "PCF8575.h"

#define TX 5
#define RX 6
#define IRQPIN 2

PCF8575 PCF(0x20);

SerialMP3Player mp3(RX,TX);

uint d = 0;
uint state = 0;

void pcf_irq()
{
  state = PCF.read16();
}

void setup() 
{
  Serial.begin(9600);     // start serial interface
  mp3.begin(9600);        // start mp3-communication
  delay(500);             // wait for init

  mp3.sendCommand(CMD_SEL_DEV, 0, 2);   //select sd-card
  delay(500);             // wait for init

  mp3.setVol(25);
  delay(500);             // wait for init

  Wire.begin();
  PCF.begin();

  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), pcf_irq, FALLING);
}

// the loop function runs over and over again forever
void loop() 
{ 
  if (d == 0);
  else mp3.play(d);     // Play "hello.mp3". You must hear "Hello World"
  delay(500);    // wait 0.5 seconds
}