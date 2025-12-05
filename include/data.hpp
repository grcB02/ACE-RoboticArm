
//dados atualizados, debounced, flancos e assim ,basicamente dados para usarmos
struct system_data {
    bool Sok=0;


};

//dados brutos, valores lidos dos sensores
struct raw_data{
    
};

//dados que mudam rapidamente, tipo o accelerometro 
struct volatile_data
{
    
};

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
