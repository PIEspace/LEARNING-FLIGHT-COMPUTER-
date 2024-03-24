// transmit  the hello world from the receiver  side
// in the transmitter  side i am using arduino nano 
#include <SoftwareSerial.h>
#include<Arduino.h>

SoftwareSerial XBee(0, 1); // RX, TX pins

void setup() {
  Serial.begin(9600);
  XBee.begin(9600);
}

void loop() {
  XBee.println("Hello, World!");
  delay(10);
}
