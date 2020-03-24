CC= gcc
CFLAGS= -Wall -Werror -g -O -ansi
LDFLAGS=
LDLIBS=

main: main.o fsm.o player.o timespec_utils.o

clean:
	rm -f main *.o
