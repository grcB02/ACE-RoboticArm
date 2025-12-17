#include <Wire.h>
<<<<<<< HEAD
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  110 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 
#define USMAX  2400 
#define SERVO_FREQ 60 //frequencia do servo

#define SERVO1 0
#define SERVO2 9
#define SERVO3 8
#define SERVO4 10

const double L1 = 1; 
const double L2 = 1;

uint8_t servonum = SERVO1;


void moverParaCoordenadas(double x, double y, double z) {
  // --- MOTOR 1: Rotação da Base ---
  // Calcula o ângulo no plano horizontal
  double angulo1 = atan2(y, x) * 180.0 / M_PI;

  // --- CÁLCULOS PARA O PLANO VERTICAL ---
  // r é a distância horizontal total do centro até o ponto (x,y)
  double r = sqrt(x * x + y * y);
  
  // s é a distância direta da origem do motor 2 até o ponto de destino (x,y,z)
  double s = sqrt(r * r + z * z);

=======
<<<<<<< HEAD
#include <Adafruit_PWMServoDriver.h>
=======
#include <cmath> // Include cmath for fabsf, sqrtf, and M_PI

#include <VectorXf.h>

#include "MPU6500_Raw.h"
MPU6500 mpu;

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET      -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET, 3400000, 400000);
>>>>>>> 75126fe722904d22539b15ab2ae884c297790988


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  110 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 
#define USMAX  2400 
#define SERVO_FREQ 60 //frequencia do servo

<<<<<<< HEAD
#define SERVO1 0
#define SERVO2 9
#define SERVO3 8
#define SERVO4 10
=======
Adafruit_PWMServoDriver ServoDriver = Adafruit_PWMServoDriver();


void setup_servos(Adafruit_PWMServoDriver &driver) {

    driver.begin();
  driver.setOscillatorFrequency(28000000);
  driver.setPWMFreq(50);  // Analog servos run at ~50 Hz updates (20 ms period)
  delay(10);

}

void setup_I2C_PCA9685(Adafruit_PWMServoDriver &driver)
{
    // Definir pinos usados para I2C (RP2040 / Arduino compatível)
    Wire.setSDA(SDA_PIN);
    Wire.setSCL(SCL_PIN);

    Wire.begin();

    // Tentar encontrar o PCA9685
    while (!driver.begin()) {
        Serial.println("Erro: PCA9685 não encontrado! Verifica as ligações.");
        delay(200);
    }

    Serial.println("PCA9685 encontrado.");

    /*
    // Ajustar a frequência interna
    driver.setOscillatorFrequency(28000000);

    // Frequência típica dos servos (20 ms → ~50 Hz)
    driver.setPWMFreq(50);

    //isto está repetido na função setup_servos, depois ver como é melhor organizar

    */

    delay(10);
}


int angle_to_pulse(int angle)
{
    // Limitar ângulo entre 0 e 180
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    // --- Ajusta aqui conforme o teu servo ---
    float pulse_min_ms = 1.0;   // Pulso mínimo (ms) → posição 0°
    float pulse_max_ms = 2.0;   // Pulso máximo (ms) → posição 180°
    // ----------------------------------------

    float period_ms = 20.0;     // 50Hz → 20 ms por ciclo

    // Converter ângulo 0–180 para pulso em ms
    float pulse_ms = pulse_min_ms + (angle / 180.0) * (pulse_max_ms - pulse_min_ms);

    // Converter ms para valor 0–4095
    int pulse_value = (pulse_ms / period_ms) * 4096;

    return pulse_value;
}

void set_interval(float new_interval)
{
  interval = new_interval * 1000000L;   // In microseconds
}   
>>>>>>> 75126fe722904d22539b15ab2ae884c297790988

const double L1 = 1; 
const double L2 = 1;

uint8_t servonum = SERVO1;


void moverParaCoordenadas(double x, double y, double z) {
  // --- MOTOR 1: Rotação da Base ---
  // Calcula o ângulo no plano horizontal
  double angulo1 = atan2(y, x) * 180.0 / M_PI;

  // --- CÁLCULOS PARA O PLANO VERTICAL ---
  // r é a distância horizontal total do centro até o ponto (x,y)
  double r = sqrt(x * x + y * y);
  
  // s é a distância direta da origem do motor 2 até o ponto de destino (x,y,z)
  double s = sqrt(r * r + z * z);

>>>>>>> bfa0bb5ffe4fe05d365b631434dacbbe70be524b
  // Verificação de segurança: o ponto está ao alcance?
  if (s > (L1 + L2)) {
    Serial.println("Erro: Ponto fora de alcance!");
    return;
  }

  // --- MOTOR 2: Elevação principal ---
  double a1 = atan2(z, r);
  double a2 = acos((L1 * L1 + s * s - L2 * L2) / (2 * L1 * s));
  double angulo2 = (a1 + a2) * 180.0 / M_PI;

  // --- MOTOR 3: Ajuste da "Garra/Forklift" ---
  // Para braços tipo o do vídeo, o ângulo do motor 3 costuma ser 
  // calculado para compensar o ângulo do motor 2 e manter o plano.
  double cosAngulo3 = (L1 * L1 + L2 * L2 - s * s) / (2 * L1 * L2);
  double angulo3 = acos(cosAngulo3) * 180.0 / M_PI;

  // --- ENVIO PARA OS MOTORES ---
  // Nota: dependendo da montagem, podes precisar de somar 90 ou subtrair o valor de 180
  motorSetAngle(SERVO1, (int)angulo1);
  motorSetAngle(SERVO2, (int)angulo2);
  motorSetAngle(SERVO3, (int)angulo3);

  Serial.print("X:"); Serial.print(x); 
  Serial.print(" Y:"); Serial.print(y); 
  Serial.print(" Z:"); Serial.println(z);
}


void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  Wire.setSDA(20);
  Wire.setSCL(21);

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);//nao sei o que faz, algo a ver com o core do microcontrolador
  pwm.setPWMFreq(SERVO_FREQ);  //frequencia do servo 60Hz
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
  pwm.setPWM(n, 0, pulse);
}

void motorSetAngle(uint8_t n, int angle){
  int angle_PWM = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  Serial.print("Motor|Angulo : Motor-->");
  Serial.print(n);
  Serial.print("|");
  Serial.print(angle);
  Serial.print("--->");
  Serial.println(angle_PWM);

  pwm.setPWM(n, 0, angle_PWM);
}

void loop() {
  // Drive each servo one at a time using setPWM()
  Serial.println(servonum);

  motorSetAngle(servonum, 180);

  delay(1000);

  motorSetAngle(servonum, 0);
  
  delay(1000);

  if(servonum == SERVO1){
    servonum = SERVO2;
  }else if(servonum == SERVO2){
    servonum = SERVO4;
  }else if(servonum == SERVO3){
    servonum = SERVO4;
  }else if(servonum == SERVO4){
    servonum = 0;
  }

}
