// receive the hello world from the transmitter side
// in the receiver side i am using teensy 3.2 
#include<Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial XBee(0, 1); // RX, TX pins

void setup() {
  Serial.begin(9600);
  XBee.begin(9600);
}

void loop() {
  if (XBee.available()) {
    char receivedChar = XBee.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
  }
}
