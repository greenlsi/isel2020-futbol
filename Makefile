CC= gcc
CFLAGS= -Wall -Werror -ansi -g -O

main: main.o player.o fsm.o timespec_utils.o
