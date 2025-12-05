#include "IOman.hpp"

class IOman {
private:
    void IOman::read_sensors(){
        // Implementação da leitura dos sensores
    };
    void IOman::calculate_flanks(){
        // Implementação do cálculo de flancos
    };
    void IOman::debounce_buttons(){

    };

    /*
    //debounce dos botoes
    debounce_sok()
    debounce_snext()

    //update dos outputs
    update_motor1()
    update_motor2()
    update_motor3() 
    */
    
public:
    IOman(system_data data, volatile_data v_data, MotorController &motor_controller);
    void IOman::update_data(){
        read_sensors();
        calculate_flanks();
        debounce_buttons();
        update_outputs();
    };

    
    void IOman::setup(){

    };



    void IOman::update_outputs(){

    };

    
};