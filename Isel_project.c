
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/select.h>
#include "timespect_operations.h"
#include "player.h"
#include "config.h"
#include "task.h"
#include "interp.h"
#include "window.h"
#include "screen.h"

static pthread_t game = NULL;
static fsm_t* p = NULL;
/*
int
key_pressed (void)
{
  struct timeval timeout = { 0, 0 };
  fd_set rd_fdset;
  FD_ZERO(&rd_fdset);
  FD_SET(0, &rd_fdset);
  return select(1, &rd_fdset, NULL, NULL, &timeout) > 0;
}

void
key_process (int ch)
{
  switch (ch) {
  case 'w': player_set_up ((player_t*) p); break;
  case 's': player_set_down ((player_t*) p); break;
  case 'a': player_set_left ((player_t*) p); break;
  case 'd': player_set_right ((player_t*) p); break;

  case 'q': exit(0); break;
  }
}
*/
void
delay_until (struct timespec* next)
{
  struct timespec now, t;

  clock_gettime (CLOCK_REALTIME, &now);
  /* t = next - now */
  timespec_sub (&t, next, &now);
  nanosleep (&t, NULL);
}
static
void* play(){
	 struct timeval next_activation;
	 struct timeval now, timeout, rtime;
	 gettimeofday (&next_activation, NULL);
	   while (1) {
	     struct timeval *period = task_get_period (pthread_self());
	     timeval_add (&next_activation, &next_activation, period);
	     gettimeofday (&now, NULL);
	     timeval_sub (&timeout, &next_activation, &now);
	     timeval_sub (&rtime, period, &timeout);
	     task_register_time (pthread_self(), &rtime);
	     select (0, NULL, NULL, NULL, &timeout) ;

	     fsm_fire(p);
	     player_print((player_t*)p,"*");

	 }
	   return NULL;
}

int
main (void)
{
  task_setup();
  enable_raw_mode();
  screen_setup (2);
  window_setup ();

  p = fsm_new_player(1);

  game = task_new ("screen", play, 25, 25, 2, 1024);

  interp_run((player_t*)p);

}
