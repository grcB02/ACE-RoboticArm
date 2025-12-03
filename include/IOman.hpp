#include "data.hpp"
#include "MotorController.hpp"

class IOman {
private:
    void read_sensors();
    void calculate_flanks();
    void debounce_buttons();
    

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
    void update_data();
    void setup();
    void update_outputs();
    system_data sys_data;
};