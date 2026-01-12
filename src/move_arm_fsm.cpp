#include "main.cpp"
typedef struct {
  int state, new_state;

  // tes - time entering state
  // tis - time in state
  unsigned long tes, tis;
} fsm_t;

// Input variables
uint8_t S1, prevS1;
uint8_t S2, prevS2;

// Output variables
uint8_t LED_1, LED_2;

// Our finite state machines
fsm_t fsm1, fsm2;


// meaningful names for the fsm1 states
enum {
OFF,
move_to_piece,
pick_piece,
remove_from_tower,
move_to_right_tower ,
insert_and_drop,
};

uint32_t interval, last_cycle;
uint32_t loop_micros;
uint32_t blink_period;

// Set new state
void set_state(fsm_t& fsm, int new_state)
{
  if (fsm.state != new_state) {  // if the state chnanged tis is reset
    fsm.state = new_state;
    fsm.tes = millis();
    fsm.tis = 0;
  }
}


void setup() 
{
  pinMode(LED1_pin, OUTPUT);
  pinMode(LED2_pin, OUTPUT);
  pinMode(S1_pin, INPUT_PULLUP);
  pinMode(S2_pin, INPUT_PULLUP);

  // Start the serial port with 115200 baudrate
  Serial.begin(115200);

  blink_period = 1000 * 1.0/0.33; // In ms

  interval = 40;
  set_state(fsm1, 0);
  set_state(fsm2, 0);    
}

void solve_hanoi(){

    for(int i=0; i<16; i++){
        update_hanoi_fsm();
        switch (fsm1.state) {
            case OFF:
                Serial.println("State: OFF");
                break;
            case move_to_piece:
                Serial.println("State: MOVE TO PIECE");
                moverParaCoordenadas(v[0][i],v[1][i],v[2][i]);
                break;
            case pick_piece:
                Serial.println("State: PICK PIECE");
                break;
            case remove_from_tower:
                Serial.println("State: REMOVE FROM TOWER");
                moverParaCoordenadas(w[0][i],w[1][i],w[2][i]);
                break;
            case move_to_right_tower:
                Serial.println("State: MOVE TO RIGHT TOWER");
                moverParaCoordenadas(u[0][i],u[1][i],u[2][i]);
                break;
            case insert_and_drop:
                Serial.println("State: INSERT AND DROP");
                moverParaCoordenadas();
                break;
        }
           
    }


}







void loop()
{
          // Update tis for all state machines
      uint32_t cur_time = millis();   // Just one call to millis()
      fsm1.tis = cur_time - fsm1.tes;
      fsm2.tis = cur_time - fsm2.tes; 

            if (fsm1.state == OFF && S1){
        fsm1.new_state = move_to_piece;

      } else if(fsm1.state == move_to_piece && S1) {
        fsm1.new_state = pick_piece;
      }

      else if(fsm1.state == pick_piece && S1){
        fsm1.new_state = remove_from_tower;

      } else if(fsm1.state == remove_from_tower && S1) {
        fsm1.new_state = move_to_right_tower;
      }

      else if(fsm1.state == move_to_right_tower && S1){
        fsm1.new_state = insert_and_drop;

      } else if(fsm1.state == insert_and_drop && S1) {
        fsm1.new_state = move_to_piece;
      }

        else if(fsm1.state == insert_and_drop && S1) {
        fsm1.new_state = OFF;
      }




      set_state(fsm1, fsm1.new_state);

    return 0;
}