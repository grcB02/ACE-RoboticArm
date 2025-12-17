#pragma once
#include "data.hpp"
#include "MotorController.hpp"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

class IOman {
private:
    void read_sensors();
    void calculate_flanks();
    void debounce_buttons();

    volatile_data v_data;
    MotorController &motor_controller;

public:
    IOman(system_data data, volatile_data v_data, MotorController &motor_controller);

    void update_data();
    void setup();
    void update_outputs();
    void set_motor_angle(int motor_id, float angle);
    void setup_I2C_PCA9685(Adafruit_PWMServoDriver &driver);

    void setup_servos(Adafruit_PWMServoDriver &driver);
    void setup_I2C_PCA9685(Adafruit_PWMServoDriver &driver);



    system_data sys_data;
};
