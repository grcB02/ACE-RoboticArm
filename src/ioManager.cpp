#include <Arduino.h>
#include <VectorXf.h>
#include "MPU6500_Raw.h"
MPU6500 mpu;

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address

typedef struct{
  float angle_x, angle_y, angle_z;
}datas;

typedef struct {
  Vec3f w;
  Vec3f a;
  uint32_t cycle_time, last_cycle_time; // IMU cycle tracking
} imu_values_t;

imu_values_t imu;
datas data_imu;

float angle_update(imu_values_t imu){


   if (mpu.update()) {
      imu.last_cycle_time = imu.cycle_time;
      imu.cycle_time = micros();

      imu.w.x = mpu.getGyroX();
      imu.w.y = mpu.getGyroY();
      imu.w.z = mpu.getGyroZ();

      imu.a.x = mpu.getAccX();
      imu.a.y = mpu.getAccY();
      imu.a.z = mpu.getAccZ();
    }
    else{
        //printf("mpu has not updated yet");
        return 0;
    }
}