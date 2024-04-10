#include <Adafruit_BMP280.h>
#include <Wire.h>

Adafruit_BMP280 bmp; // I2C

// Kalman filter variables
float Q_angle = 0.001;
float Q_bias = 0.003;
float R_measure = 0.03;
float angle = 0; // Reset the angle
float bias = 0; // Reset bias

float P[2][2] = {{0, 0}, {0, 0}};

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  delay(500);
  Serial.println("BMP280 sensor found!");
}

void loop() {
  float dt = 0.1; // Time step
  float y = bmp.readPressure() / 100.0F; // Read pressure in hPa
  float S = 0;

  // Update the angle estimation using the Kalman filter
  angle += dt * (bias - angle);
  P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt * P[1][1];
  P[1][0] -= dt * P[1][1];
  P[1][1] += Q_bias * dt;

  S = P[0][0] + R_measure;
  float K[2] = {P[0][0] / S, P[1][0] / S};

  float y_hat = angle;
  float y_err = y - y_hat;

  angle += K[0] * y_err;
  bias += K[1] * y_err;
  P[0][0] -= K[0] * P[0][0];
  P[0][1] -= K[0] * P[0][1];
  P[1][0] -= K[1] * P[0][0];
  P[1][1] -= K[1] * P[0][1];

  // print on the serial monitor 

  Serial.print("Pressure: ");
  Serial.print(y);
  Serial.print(" hPa, Filtered Pressure: ");
  Serial.print(angle);
  Serial.print(" hPa, Bias: ");
  Serial.print(bias);
  Serial.println();

  delay(100);
}
