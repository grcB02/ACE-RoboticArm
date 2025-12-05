#pragma once  // <--- 1. Proteção contra inclusão múltipla

#include <iostream>
#include <string>
#include "IOman.hpp"
#include "data.hpp"

enum mission_type {
    NONE_SELECTED,
    COLOR_SORTING_KNOWN,
    COLOR_SORTING_UNKNOWN,
    SOLVE_HANOI,
    OPERATION_MODE_SELECTED
};

enum mission_state {
    OFF,
    READY,          // <--- 4. Consistência (Maiúsculas)
    IN_PROGRESS,    // <--- 4. Consistência
    COMPLETED,      // <--- 2. Correção do typo 'cpompleted'
    ERROR_STATE     // <--- (Evitar usar apenas 'ERROR' pois pode conflituar com macros do sistema)
};

// Classe FSM para gerir estado das missões
class FSM_mission {
private:
    // Referências guardadas para uso interno na FSM
    IOman &io;           // <--- 3. Variável para guardar a referência
    system_data &data;   // <--- 3. Variável para guardar a referência

    mission_type current_mission;
    mission_state current_mission_state;
    mission_state next_state;

public:
    // Construtor
    FSM_mission(IOman &io_manager, system_data &data_ref);

    void set_state(mission_state new_state);
    
    void update_fsm();
    
    mission_state get_current_state() const;
    mission_type get_current_mission() const;
};

