#include "IOman.hpp"

void IOman::read_sensors() {
    // Implementação da leitura dos sensores
}

void IOman::calculate_flanks() {
    // Implementação do cálculo de flancos
}

void IOman::debounce_buttons() {
    // Implementação do debounce dos botões
}

IOman::IOman(system_data data, volatile_data v_data, MotorController &motor_controller)
    : sys_data(data),
      v_data(v_data),
      motor_controller(motor_controller)
{
}

void IOman::update_data() {
    read_sensors();
    calculate_flanks();
    debounce_buttons();
    update_outputs();
}

void IOman::setup() {
    // Setup inicial de IOman
}

void IOman::update_outputs() {
    // Implementação da atualização das saídas
}

void IOman::set_motor_angle(int motor_id, float angle) {
    ServoDriver.setPWM(motor_id, 0, angle);
}

void setup_I2C_PCA9685(Adafruit_PWMServoDriver &driver)
{
    // Definir pinos usados para I2C (RP2040 / Arduino compatível)
    Wire.setSDA(8);
    Wire.setSCL(9);

    Wire.begin();

    // Tentar encontrar o PCA9685
    while (!driver.begin()) {
        Serial.println("Erro: PCA9685 não encontrado! Verifica as ligações.");
        delay(200);
    }

    Serial.println("PCA9685 encontrado.");

    // Ajustar a frequência interna
    driver.setOscillatorFrequency(28000000);

    // Frequência típica dos servos (20 ms → ~50 Hz)
    driver.setPWMFreq(50);

    delay(10);
}