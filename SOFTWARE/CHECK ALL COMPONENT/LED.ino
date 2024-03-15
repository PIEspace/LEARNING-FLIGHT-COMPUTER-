// check the led

// first led connect on d5 
//second led connect on d6 

#include<Arduino.h>

const int First_Led = 5;
const int Second_Led = 6;

void setup(){

// define the pinMode of the led 
pinMode(First_Led , OUTPUT);
pinMode(Second_Led , OUTPUT);

}

void loop(){

    // turn on the led for 1 second and then turn off for 100 millisecond 
    digitalWrite(First_Led , 1);
    delay(1000); //delay for 1000 millisecond 
    digitalWrite(First_Led , 0 );
    delay(100); //delay for 100 millisecond 

    // define the second led 
    digitalWrite(Second_Led , 1 );
    delay(1000); //delay for 1000 millisecond
    digitalWrite(Second_Led , 0 );
    delay(100); //delay for 100 millisecond 
    



}