#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <sys/select.h>

static struct termios orig_termios;

void disable_raw_mode() 
{
  if (tcsetattr(0, TCSAFLUSH, &orig_termios) == -1)
    perror ("tcsetattr");
}

void enable_raw_mode() 
{
  if (tcgetattr(0, &orig_termios) == -1) perror("tcgetattr");
  atexit(disable_raw_mode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(0, TCSAFLUSH, &raw) == -1) perror("tcsetattr");
}

int timespec_less (const struct timespec* a, const struct timespec* b);
void timespec_add (struct timespec* res, const struct timespec* a, const struct timespec* b);
void timespec_sub (struct timespec* res, const struct timespec* a, const struct timespec* b);

static fsm_t* p = NULL;

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

void
delay_until (struct timespec* next)
{
  struct timespec now, t;

  clock_gettime (CLOCK_REALTIME, &now);
  /* t = next - now */
  timespec_sub (&t, next, &now);
  nanosleep (&t, NULL);
}

int
main (void)
{
  struct timespec next;
  struct timespec period = { 1, 0 };

  enable_raw_mode();

  p = fsm_new_player(1); 
  clock_gettime(CLOCK_REALTIME, &next);
  while (1) {

    if (key_pressed())
      key_process(getchar());

    fsm_fire (p);
    player_print ((player_t*) p);
    
    timespec_add (&next, &next, &period);
    delay_until (&next);
  }
}
