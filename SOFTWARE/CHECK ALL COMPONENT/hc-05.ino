// turn on and turn off led using bluetooth 

#include<Arduino.h>


#define FIRST_LED 5 
#define SECOND_LED 6 


void setup(){
    // define the bud rate so in this case i am using 9600 bits per second 
    Serial.begin(9600);

    //define the pinMode
    pinMode(FIRST_LED , OUTPUT);
    pinMode(SECOND_LED , OUTPUT);

    

}

void loop(){

    Serial.println(" turn on the first led = A ");
    Serial.println(" turn off the first led = B");
    Serial.println(" turn on the second led = C ");
    Serial.println(" turn off the second led = D");

    if(Serial.available() >0 ){
        char command = Serial.read();

        if(command == 'A' || command == 'a'){
            Serial.println("turn on the first led ");
            digitalWrite(FIRST_LED , 1);
        }

        else if(command == 'B' || command == 'b'){
            Serial.println("turn off the first led ");
            digitalWrite(FIRST_LED , 0 );
        }

        // define the second led 
        else if (command == 'C' || command == 'c'){
            Serial.println("turn on the second led ");
            digitalWrite(SECOND_LED , 1 );
        }

        else if ( command == 'D' || command == 'd'){
            Serial.println("turn off the second led ");
            digitalWrite(SECOND_LED , 0 );
        }
    }

}