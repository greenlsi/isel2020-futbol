/*
 * time_spect_operations.c
 *
 *  Created on: 26 mar. 2020
 *      Author: happybug
 */



#include "timespect_operations.h"

int timespec_less (const struct timespec* a, const struct timespec* b){
		if (a->tv_sec != b->tv_sec)
			return a->tv_sec < b->tv_sec;
		return a->tv_nsec < b->tv_nsec;
	}

void timespec_add (struct timespec* res, const struct timespec* a, const struct timespec* b){

	res->tv_sec = a->tv_sec + b->tv_sec;
	res->tv_nsec = a->tv_nsec + b->tv_nsec;
	if (res->tv_nsec >= 1000000000) {
		res->tv_sec++;
		res->tv_nsec -= 1000000000;
	}

}
void timespec_sub (struct timespec* res, const struct timespec* a, const struct timespec* b){
	res->tv_sec = a->tv_sec - b->tv_sec;
	res->tv_nsec = a->tv_nsec - b->tv_nsec;
	if (res->tv_nsec < 0) {
		res->tv_sec--;
		res->tv_nsec += 1000000000;
	}
}
