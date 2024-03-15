// check the buzzer
// buzzer connect on d4

#include <Arduino.h>

const int Buzzer = 4;

void setup()
{
    // define the bud rate so in this case i am using 9600 bits per second (bps)
    Serial.begin(9600);

    // define the pinMode
    pinMode(Buzzer, OUTPUT);
}

void buzzer_tone(void)
{

    // define the frequency
    const int First_Frequency[] = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000};

    for (int a = 0; a <= 10; a++)
    {
        tone(Buzzer, First_Frequency[a], 100);
        delay(50);
    }
    noTone(Buzzer);
    delay(10);

    const int Second_Frequency [] = {300,600,900,1200,1500,1800,2100,2400,2700,3000};
    for(int b=0 ; b<=10 ;b++){
        tone(Buzzer , Second_Frequency[b] , 100);
        delay(50);
    }
    noTone(Buzzer);
    delay(10);
}
void loop()
{
    //calling the function 
    buzzer_tone();
}