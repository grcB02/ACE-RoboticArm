#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

uint32_t interval, last_cycle;
uint32_t loop_micros;
uint32_t cycle_count;

void set_interval(float new_interval)
{
  interval = new_interval * 1000000L;   // In microseconds
}   

Adafruit_PWMServoDriver input_servos = Adafruit_PWMServoDriver();
Servo myservo;

uint8_t servonum = 12;

void setup() 
{
  input_servos.begin();

  Serial.begin(115200);

  // Our cycle time
  set_interval(20e-3); // 20 ms -> 50 Hz
  input_servos.setOscillatorFrequency(27000000);
  input_servos.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  input_servos.setPWM(n, 0, pulse);
}

void loop() 
{
 Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    input_servos.setPWM(servonum, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    input_servos.setPWM(servonum, 0, pulselen);
  }

  delay(500);

  // Drive each servo one at a time using writeMicroseconds(), it's not precise due to calculation rounding!
  // The writeMicroseconds() function is used to mimic the Arduino Servo library writeMicroseconds() behavior. 
  for (uint16_t microsec = USMIN; microsec < USMAX; microsec++) {
    input_servos.writeMicroseconds(servonum, microsec);
  }

  delay(500);
  for (uint16_t microsec = USMAX; microsec > USMIN; microsec--) {
    input_servos.writeMicroseconds(servonum, microsec);
  }

  delay(500);

  servonum++;
  if (servonum > 15) servonum = 12; //testar os 4 servos do braço

}