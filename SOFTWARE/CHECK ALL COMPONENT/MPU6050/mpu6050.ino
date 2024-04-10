// this is a simple kalman filter

#include <Wire.h>
#include <MPU6050.h>
#include <SimpleKalmanFilter.h>

MPU6050 mpu;

int16_t ax, ay, az; // Accelerometer raw data
int16_t gx, gy, gz; // Gyroscope raw data

float AccX, AccY, AccZ;    // Accelerometer scaled data
float GyroX, GyroY, GyroZ; // Gyroscope scaled data

float roll, pitch, yaw; // Calculated roll and pitch angles

// Define Kalman filter parameters
SimpleKalmanFilter kalmanPitch(2, 2, 0.15); // Q, R, initial estimate
SimpleKalmanFilter kalmanRoll(2, 2, 0.15);  // Q, R, initial estimate
SimpleKalmanFilter kalmanYaw(2, 2, 0.15);   // Q , R , initial estimate

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    mpu.initialize();
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);  // Set accelerometer range to +/- 2g
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000); // Set gyroscope range to +/- 2000 degrees/sec
}

void loop()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // Get raw sensor data

    // Convert raw accelerometer data to G's
    AccX = (float)ax / 16384.0;
    AccY = (float)ay / 16384.0;
    AccZ = (float)az / 16384.0;

    // Check if AccY and AccZ are both non-zero to avoid division by zero

    // Convert raw gyroscope data to degrees/second
    GyroX = (float)gx / 131.0;
    GyroY = (float)gy / 131.0;
    GyroZ = (float)gz / 131.0;

    // Calculate roll, pitch, and yaw angles
    // convert the radian to degree = 180/pi
    roll = atan2(AccY, AccZ) * 180.0 / M_PI;
    pitch = atan(-AccX / sqrt(AccY * AccY + AccZ * AccZ)) * 180.0 / M_PI;
    yaw = atan2(-GyroX, sqrt(GyroY * GyroY + GyroZ * GyroZ)) * 180.0 / M_PI;

    // Apply Kalman filter to smooth pitch and roll angles
    pitch = kalmanPitch.updateEstimate(pitch);
    roll = kalmanRoll.updateEstimate(roll);
    yaw = kalmanYaw.updateEstimate(yaw);

    // Print
    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(" , ");

    Serial.print(" degrees, Pitch: ");
    Serial.print(pitch);
    Serial.print(" , ");

    Serial.print(" yaw : ");
    Serial.println(yaw);

    // Serial.println(yaw);

    delay(100);
}
