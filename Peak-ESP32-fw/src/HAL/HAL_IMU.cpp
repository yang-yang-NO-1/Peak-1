#include "HAL/HAL.h"
#include "Adafruit_MPU6050.h"
#include "App/Accounts/Account_Master.h"

Adafruit_MPU6050 mpu;

void HAL::IMU_Init()
{
    Wire.setPins(32,33);
    if (!mpu.begin())
    {
        Serial.println("MPU connection failed.");
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void HAL::IMU_Update()
{
    IMU_Info_t imuInfo;
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    imuInfo.ax = a.acceleration.x;
    imuInfo.ay = a.acceleration.y;
    imuInfo.az = a.acceleration.z;
    imuInfo.gx = g.gyro.x;
    imuInfo.gy = g.gyro.y;
    imuInfo.gz = g.gyro.z;
    imuInfo.mx = temp.temperature;
    // imuInfo.my = mpu.getMagY();
    // imuInfo.mz = mpu.getMagZ();
    // imuInfo.roll = mpu.getRoll();
    // imuInfo.yaw = mpu.getYaw();
    // imuInfo.pitch = mpu.getPitch();

    AccountSystem::IMU_Commit(&imuInfo);
}
