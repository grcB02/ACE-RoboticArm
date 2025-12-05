#include "missionFSM.hpp"

// 1. Construtor: Inicializar as referências na lista de inicialização
// O nome do parâmetro 'data_ref' evita confusão com o membro 'data'
FSM_mission::FSM_mission(IOman &io_manager, system_data &data_ref) 
    : io(io_manager), data(data_ref) 
{
    // Definir estados iniciais seguros
    current_mission = mission_type::NONE_SELECTED;
    current_mission_state = mission_state::OFF;
    next_state = mission_state::OFF;
}

// 2. Adicionado FSM_mission:: antes do nome da função
void FSM_mission::set_state(mission_state new_state){
    current_mission_state = new_state;
}

// 3. Adicionado 'const' para bater certo com o cabeçalho (se lá tiver const)
// e adicionado o FSM_mission::
mission_state FSM_mission::get_current_state() const { 
    return current_mission_state; 
}

mission_type FSM_mission::get_current_mission() const { 
    return current_mission; 
}

void FSM_mission::update_fsm(){
    // 4. O switch deve ser sobre o ESTADO, não sobre a missão
    switch (current_mission_state)
    {
    case OFF:
        // Exemplo: Se carregou no botão de Start (Sok)
        if(data.Sok){
            next_state = mission_type::COLOR_SORTING_KNOWN; // Usar nomes corrigidos (Maiúsculas)
        } else {
            next_state = mission_type::NONE_SELECTED;
        }
        break;

    case READY:
        // Lógica de preparação...
        next_state = mission_type::COLOR_SORTING_UNKNOWN;
        break;

    case IN_PROGRESS:
        // Lógica principal...
        break;

    case COMPLETED: // Corrigido erro ortográfico 'cpompleted'
        /* code */
        break;

    case ERROR_STATE:
        /* code */
        break;      
    
    default:
        next_state = ERROR_STATE;
        break;
    }

    // Atualizar o estado efetivamente
    set_state(next_state);    
}