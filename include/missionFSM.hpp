#include <iostream>
#include <string>

#include "IOman.hpp"


enum mission_type{
    OFF,
    COLOR_SORTING_KNOWN,
    COLOR_SORTING_UNKNOWN,
    SOLVE_HANOI,
    OPERATION_MODE_SELECTED
};

enum mission_state {
    OFF,
    ready,
    in_progress,
    cpompleted,
    error,
};


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

