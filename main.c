#include "player.h" 

int 
main (void) 
{ 
  fsm_t* p = fsm_new_player(1); 
  while (1) {
    fsm_fire (p);
    
  }
}
