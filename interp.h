#ifndef INTERP_H
#define INTERP_H

#include "player.h"

void interp_run (player_t* p);
int interp_addcmd (char* cmd, int (*cmd_func) (char*), char* doc);

#endif
