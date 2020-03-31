#include "fsm.h" 

struct player_t;
typedef struct player_t player_t;

int player_set_up (void *c,player_t* p);
int player_set_down (void *c,player_t* p);
int player_set_left (void *c,player_t* p);
int player_set_right (void *c,player_t* p);

void player_init (player_t* p, int id); 
fsm_t* fsm_new_player (int id);

void player_print (player_t* p,const char* txt);
