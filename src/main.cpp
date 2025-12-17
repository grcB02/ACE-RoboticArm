#include <Wire.h>
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
