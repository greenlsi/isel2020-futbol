#include "fsm.h" 

struct player_t;
typedef struct player_t player_t;

void player_set_up (player_t* p);
void player_set_down (player_t* p);
void player_set_left (player_t* p);
void player_set_right (player_t* p);

void player_init (player_t* p, int id); 
fsm_t* fsm_new_player (int id);

void player_print (player_t* p);
