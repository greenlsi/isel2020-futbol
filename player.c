#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#define MIN_Y  0
#define MAX_Y  24
#define MIN_X  0
#define MAX_X  79

struct player_t {
  fsm_t fsm;
  int id;
  int pos_x;
  int pos_y;
  /* flags */
  int up;
  int down;
  int left;
  int right;
};

static int key_up_not_top (fsm_t* this) {
  player_t* p = (player_t*) this;
  return (p->pos_y > MIN_Y) && p->up;
}

static int key_down_not_bottom (fsm_t* this) {
  player_t* p = (player_t*) this;
  return (p->pos_y < MAX_Y) && p->down;
}

static int key_left_not_left (fsm_t* this) {
  player_t* p = (player_t*) this;
  return (p->pos_x > MIN_X) && p->left;
}

static int key_right_not_right (fsm_t* this) {
  player_t* p = (player_t*) this;
  return (p->pos_x < MAX_X) && p->right;
}

static void move_up (fsm_t* this) {
  player_t* p = (player_t*) this;
  p->pos_y --; p->up = 0;
}

static void move_down (fsm_t* this) {
  player_t* p = (player_t*) this;
  p->pos_y ++; p->down = 0;
} 

static void move_left (fsm_t* this) {
  player_t* p = (player_t*) this;
  p->pos_x --; p->left = 0;
} 

static void move_right (fsm_t* this) {
  player_t* p = (player_t*) this;
  p->pos_x ++; p->right = 0;
} 

void player_init (player_t* this, int id) {
  static fsm_trans_t tt[] = {
    { 0, key_up_not_top, 0, move_up },
    { 0, key_down_not_bottom, 0, move_down },
    { 0, key_left_not_left, 0, move_left },
    { 0, key_right_not_right, 0, move_right },
    { -1, NULL, -1, NULL }
  };
 
  fsm_init ((fsm_t*) this, tt);
  this->id = id;
  this->pos_x = this->pos_y = 0; 
  this->up = this->down = this->left = this->right = 0;
}

fsm_t* fsm_new_player (int id) {
  player_t* this = (player_t*) malloc (sizeof (player_t));
  player_init (this, id);
  return (fsm_t*) this;
}
/*
 * Estas condiciones las he puesto aquí ya que las variables del tamaño del tablero están aquí
 * Si estas coondiciones no aparecen. otras soluciones son:
 * 		1.- cuando se active un flag bajar el resto de flags (puede que de otros errores)
 * 		2.- hacer globales los limites del tablero y poner estas condiciones en la funcion key_process (puede que de otros errores)
 */

int player_set_up (void *c,player_t* p)    { if(p->pos_y>MIN_Y)p->up = 1; return 0;}
int player_set_down (void *c,player_t* p)  { if(p->pos_y<MAX_Y)p->down = 1;return 0; }
int player_set_left (void *c,player_t* p)  { if(p->pos_x>MIN_X)p->left = 1; return 0;}
int player_set_right (void *c,player_t* p) { if(p->pos_x<MAX_X)p->right = 1; return 0;}

void
player_print (player_t* p,const char* txt)
{
 screen_printxy (p->pos_x, p->pos_y,txt);
}

