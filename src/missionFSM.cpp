#include "missionFSM.hpp"

// 1. Construtor: Inicializar as referências na lista de inicialização
// O nome do parâmetro 'data_ref' evita confusão com o membro 'data'
FSM_mission::FSM_mission(IOman &io_manager, system_data &data_ref) 
    : io(io_manager), data(data_ref) 
{
    // Definir estados iniciais seguros
    current_mission = FSMMission_type::NONE_SELECTED;
    current_mission_state = FSMMission_state::OFF;
    next_state = FSMMission_state::OFF;
}

// 2. Adicionado FSM_mission:: antes do nome da função
void FSM_mission::set_state(FSMMission_state new_state){
    current_mission_state = new_state;
}

// 3. Adicionado 'const' para bater certo com o cabeçalho (se lá tiver const)
// e adicionado o FSM_mission::
FSMMission_state FSM_mission::get_current_state() { 
    return current_mission_state; 
}

FSMMission_type FSM_mission::get_current_mission() { 
    return current_mission; 
}

//UPDATE MISSION
void FSM_mission::update_mission(){
    
    switch (current_mission)
    {
    case FSMMission_type::NONE_SELECTED:
        // Exemplo: Se carregou no botão de Start (Sok)
        if(data.Sok){
            new_mission = FSMMission_type::COLOR_SORTING_KNOWN; // Usar nomes corrigidos (Maiúsculas)
        } 
        break;

    case FSMMission_type::COLOR_SORTING_KNOWN:
        break;

    case FSMMission_type::COLOR_SORTING_UNKNOWN:

        break;

    case FSMMission_type::SOLVE_HANOI: // Corrigido erro ortográfico 'cpompleted'
        
        break;

    case FSMMission_type::OPERATION_MODE_SELECTED:
        /* code */
        break;      

    // Atualizar o estado efetivamente
    set_mission(new_mission);
    }    
}