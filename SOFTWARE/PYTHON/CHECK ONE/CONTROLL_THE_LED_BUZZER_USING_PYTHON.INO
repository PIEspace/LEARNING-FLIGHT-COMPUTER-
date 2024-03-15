// control the led , buzzer using python (gui application )

#include<Arduino.h>

// define the led and buzzer 
const int FIRST_LED = 5 ;
const int SECOND_LED = 6;
const int BUZZER = 4 ;

void setup(){
    // define the bud rate so in this case i am using 9600 bits per second 
    Serial.begin(9600);

    // define the pinMode
    pinMode(FIRST_LED , OUTPUT);
    pinMode(SECOND_LED , OUTPUT);
    pinMode(BUZZER , OUTPUT);

    Serial.println(" FIRST LED TURN ON PRESS   = A ");
    Serial.println(" FIRST LED TURN OFF PRESS  = B ");
    Serial.println(" SECOND LED TURN ON PRESS  = C ");
    Serial.println(" SECOND LED TURN OFF PRESS = D ");
    Serial.println(" BUZZER  TURN ON PRESS  = E  ");
    Serial.println(" BUZZER  TURN OFF PRESS = F  ");
    
}

void loop(){

    

    if(Serial.available() > 0 ){
        char command = Serial.read();

        if(command == 'A' || command == 'a'){
            Serial.println(" TURN ON THE FIRST LED ");
            digitalWrite(FIRST_LED , 1);
        }

        else if (command == 'B' || command == 'b'){
            Serial.println(" TURN OFF THE FIRST LED ");
            digitalWrite(FIRST_LED , 0 );

        }

        else if (command == 'C' || command == 'c'){
            Serial.println(" TURN ON THE SECOND LED ");
            digitalWrite(SECOND_LED , 1);
        }

        else if (command == 'D' || command == 'd'){
            Serial.println(" TURN OFF THE SECOND LED ");
            digitalWrite(SECOND_LED  , 0 );
        }

        else if (command == 'E' || command == 'e'){
            Serial.println(" TURN ON THE BUZZER ");
            digitalWrite(BUZZER , 1);
        }

        else if (command == 'F' || command == 'f'){
            Serial.println(" TURN OFF THE BUZZER ");
            digitalWrite(BUZZER , 0 );
        }
    }


}