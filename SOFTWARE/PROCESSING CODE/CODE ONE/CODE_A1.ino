// LETS WRITE THE CODE FOR FIGHTER FLIGHT COMPUTER
// THIS IS A FIRST VERSION OF THIS FLIGHT COMPUTER

// DEFINE THE HEADER FILE /PATH
#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <SimpleKalmanFilter.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <SD.h>

// DEFINE THE MPU6050 OBJECT
MPU6050 mpu6050;

int16_t ax, ay, az; // DEFINE THE ACCELEROMETER RAW DATA [x , y , z ]
int16_t gx, gy, gz; // DEFINE THE GYROSCOPE RAW DATA [x , y , z ]

float AccX, AccY, AccZ;    // DEFINE THE ACCELEROMETER SCALED DATA [x , y , z ]
float GyroX, GyroY, GyroZ; // DEFINE THE GYROSCOPE SCALED DATA [x , y , z ]

// CALCULATE THE ROLL ,PITCH , AND YAW ANGLE
float ROLL, PITCH, YAW;

// Define Kalman filter parameters
// define the kalman filter for roll , pitch and yaw
SimpleKalmanFilter kalmanPitch(2, 2, 0.15); // Q, R, initial estimate
SimpleKalmanFilter kalmanRoll(2, 2, 0.15);  // Q, R, initial estimate
SimpleKalmanFilter kalmanYaw(2, 2, 0.15);   // Q ,R,initial estimate

// define the kalman filter for AccX , AccY , AccZ
SimpleKalmanFilter kalmanAccX(2, 2, 0.15);
SimpleKalmanFilter kalmanAccY(2, 2, 0.15);
SimpleKalmanFilter kalmanAccZ(2, 2, 0.15);

// define the kalman filter for GyroX , GyroY , GyroZ
SimpleKalmanFilter kalmanGyroX(2, 2, 0.15);
SimpleKalmanFilter kalmanGyroY(2, 2, 0.15);
SimpleKalmanFilter kalmanGyroZ(2, 2, 0.15);

// DEFINE THE BMP280 SENSOR OBJECT
Adafruit_BMP280 BMP280;

// DEFINE THE SD CARD OBJECT
File BlackBox;

// DEFINE THE COMPONENTS LED , BUZZER , PUSHBUTTON
#define First_PushButton 2  // set the first pushbutton on d2
#define Second_PushButton 3 // set the second pushbutton on d3
#define Buzzer 4            // set the buzzer on d4
#define First_Led 5         // set the first led on d5
#define Second_Led 6        // set the second led on d6
#define ChipSelect 10       // set chip select pin for Micro sd card

// Define the some Globe variables
int First_PushButtonValue = 0;
int Second_PushButtonValue = 0;
int Mode_Value = 0; // initialize mode to zero

void Startup_Sound()
{
  // DEFINE THE BUZZER FREQUENCY
  const int Delay_200_Millisecond = 200;

  // DEFINE THE FIRST BUZZER TONE FREQUENCY
  int Buzzer_Tone_First_Frequency[] = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000};

  for (int Buzzer_Tone_First = 0; Buzzer_Tone_First < 10; Buzzer_Tone_First++)
  {
    tone(Buzzer, Buzzer_Tone_First_Frequency[Buzzer_Tone_First], Delay_200_Millisecond);
    delay(50); // DELAY FOR 100 MILLISECOND
  }

  // DEFINE THE SECOND BUZZER TONE FREQUENCY
  int Buzzer_Tone_Second_Frequency[] = {300, 600, 900, 1200, 1500, 1800, 2100, 2400, 2700, 3000};

  for (int Buzzer_Tone_Second = 0; Buzzer_Tone_Second < 10; Buzzer_Tone_Second++)
  {
    tone(Buzzer, Buzzer_Tone_Second_Frequency[Buzzer_Tone_Second], Delay_200_Millisecond);
    delay(50); // DELAY FOR 50 MILLISECOND
  }

  // DEFINE THE THIRD BUZZER TONE FREQUENCY
  for (int Buzzer_Tone_Third = 0; Buzzer_Tone_Third <= 3; Buzzer_Tone_Third++)
  {
    // DEFINE THE TONE
    tone(Buzzer, 1000);
    delay(Delay_200_Millisecond); // DELAY FOR 100 MILLISECOND
    noTone(Buzzer);

    tone(Buzzer, 2400);
    delay(Delay_200_Millisecond); // DELAY FOR 100 MILLISECOND
    noTone(Buzzer);

    tone(Buzzer, 1200);
    delay(Delay_200_Millisecond); // DELAY FOR 100 MILLISECOND
    noTone(Buzzer);

    digitalWrite(Buzzer, LOW);
    delay(50); // DELAY FOR 50 MILLISECOND
  }
}

void logo()
{
  Serial.println("WELCOME TO PIE.SPACE");
  // DELAY FOR 3 SECOND
  // the program will we start on 3 second
  delay(3000); // DELAY FOR 3 SECOND
}

void setup()
{
  // LETS DEFINE THE SERIAL MONITOR IN THIS CASE I AM USING 9600 BITS PER SECOND (BPS)
  Serial.begin(9600);
  // define the buzzer startup sound
  logo();
  Startup_Sound();

  pinMode(First_PushButton, INPUT);
  pinMode(Second_PushButton, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(First_Led, OUTPUT);
  pinMode(Second_Led, OUTPUT);
  pinMode(ChipSelect, OUTPUT);
  digitalWrite(First_Led, HIGH);
  digitalWrite(Second_Led, LOW);

  // mpu6050

  Serial.print("Initialization MPU6050 SENSOR..........");
  Wire.begin();
  mpu6050.initialize();
  mpu6050.setFullScaleAccelRange(MPU6050_ACCEL_FS_2); //+-2g
  mpu6050.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
  Serial.println("Initialization done .");

  // BMP280
  // DEFINE THE BMP280 I2C ADDRESS = 0X76
  Serial.print("Initialization BMP280 SENSOR.........");
  if (!BMP280.begin(0x76))
  {
    Serial.println("BMP280 SENSOR NOT CONNECTED PLEASE CHECK THE WIRE ");
    Serial.println("SCL == SCL");
    Serial.println("SDA == SDA ");
    while (true)
      ;
  }
  else
  {
    Serial.println("Initialization done .");
  }

  // // SD CARD
  // Serial.print("Initializing SD Card.....");
  // if (!SD.begin(ChipSelect))
  // {
  //   Serial.println("initialization failed ! ");
  //   while (true)
  //     ;
  // }
  // Serial.println("Initialization done . ");

  // CLEAR THE SD CARD MODULE
  if (SD.exists("file.txt"))
  {
    if (SD.remove("file.txt") == true)
    {
      Serial.println("removed data");
    }
  }

  // define the pushbutton value
  First_PushButtonValue = digitalRead(First_PushButton);   // define the first pushbutton value
  Second_PushButtonValue = digitalRead(Second_PushButton); // define the second pushbutton value
}

void mpu6050_data()
{
  // get the raw data
  mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // convert the raw accelerometer data to g
  AccX = (float)ax / 16384.0;
  AccY = (float)ay / 16384.0;
  AccZ = (float)az / 16384.0;

  // convert the raw gyroscope data to degree/second
  GyroX = (float)gx / 131.0;
  GyroY = (float)gy / 131.0;
  GyroZ = (float)gz / 131.0;

  // calculate the roll and pitch angles
  // convert the radian to degree 180/pi
  ROLL = atan2(AccY, AccZ) * 180 / M_PI;
  PITCH = atan(-AccX / sqrt(AccY * AccY + AccZ * AccZ)) * 180 / M_PI;
  YAW = atan2(-GyroX, sqrt(GyroY * GyroY + GyroZ * GyroZ)) * 180 / M_PI;

  // apply the kalman filter for smooth roll pitch yaw angles
  PITCH = kalmanPitch.updateEstimate(PITCH);
  ROLL = kalmanRoll.updateEstimate(ROLL);
  YAW = kalmanYaw.updateEstimate(YAW);

  // define the accelerometer
  AccX = kalmanAccX.updateEstimate(AccX);
  AccY = kalmanAccY.updateEstimate(AccY);
  AccZ = kalmanAccZ.updateEstimate(AccZ);

  // define the gyroscope
  GyroX = kalmanGyroX.updateEstimate(GyroX);
  GyroY = kalmanGyroY.updateEstimate(GyroY);
  GyroZ = kalmanGyroZ.updateEstimate(GyroZ);

  // measure the altitude
  float Altitude = BMP280.readAltitude(1016);
  float Temperature = BMP280.readTemperature();
  float Pressure = BMP280.readPressure();

  // print on the serial monitor
  // first we will print roll , pitch , yaw

  Serial.print(PITCH);
  Serial.print(" , ");

  Serial.print(ROLL);
  Serial.print(" , ");

  Serial.print(YAW);
  Serial.print(" , ");

  // define the acceleration
  Serial.print(AccX);
  Serial.print(" , ");

  Serial.print(AccY);
  Serial.print(" , ");

  Serial.print(AccZ);
  Serial.print(" , ");

  Serial.print(GyroX);
  Serial.print(" , ");

  Serial.print(GyroY);
  Serial.print(" , ");

  Serial.print(GyroZ);
  Serial.print(" , ");


  
  // define the altitude and temperature and pressure
  Serial.print(Altitude);
  Serial.print(" , ");

  Serial.print(Temperature);
  Serial.print(" , ");

  Serial.println(Pressure);

  delay(10);
}

void loop()
{

  // call the function
  mpu6050_data();
}