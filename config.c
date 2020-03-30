/*
 * config.c
 *
 *  Created on: 26 mar. 2020
 *      Author: happybug
 */
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
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
