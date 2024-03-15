// check the pushbutton 
// first pushbutton connect on d2 
// second pushbutton connect on d3 

#include<Arduino.h>

const int First_Pushbutton = 2;
const int Second_Pushbutton = 3;

// define the global variable 
int First_Pushbutton_Value = 0;
int Second_Pushbutton_Value = 0;


void setup(){
    // define the bud rate in this case i am using 9600 bits per second (bps)

    Serial.begin(9600);

    // define the pinMode
    pinMode(First_Pushbutton , INPUT);
    pinMode(Second_Pushbutton , INPUT);

    Serial.println("check the pushbutton ");
    Serial.println(" press a for check the pushbutton ");
}

void loop(){

    if(Serial.available() > 0 ){
        char command = Serial.read();

        if(command == 'A' || command == 'a'){

            for(int a = 0 ; a<= 1000 ; a++){
                First_Pushbutton_Value = digitalRead(First_Pushbutton);
                Second_Pushbutton_Value = digitalRead(Second_Pushbutton);

                // print on the serial monitor
                Serial.print(" first pushbutton = ");
                Serial.print(First_Pushbutton_Value);
                Serial.print(" , ");

                Serial.print(" second pushbutton = ");
                Serial.println(Second_Pushbutton_Value);

                // define the delay 
                delay(10); //delay for 10 millisecond 

            }
            

            
            
        }
    }



}