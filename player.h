#include "fsm.h" 

struct player_t;
typedef struct player_t player_t;

void player_init (player_t* p, int id); 
fsm_t* fsm_new_player (int id);
