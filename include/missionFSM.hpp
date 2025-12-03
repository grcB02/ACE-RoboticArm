#include <iostream>
#include <string>

#include "IOman.hpp"
#include "system_data.hpp"





// Classe FSM para gerir estado  das missões
class FSM_mission {
private:
    mission_type current_mission;
    mission_state current_mission_state;


    void set_state(mission_state new_state);
public:
    // Construtor
    FSM_mission(IOman &io_manager);


    
    void update_fsm();
    mission_state get_current_state() const;
    mission_type  get_current_mission() const;
};

