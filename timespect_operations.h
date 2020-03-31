/*
 * time_spect_operations.h
 *
 *  Created on: 26 mar. 2020
 *      Author: happybug
 */

#ifndef TIMESPECT_OPERATIONS_H_
#define TIMESPECT_OPERATIONS_H_

#include <sys/time.h>
int timespec_less (const struct timespec* a, const struct timespec* b);
void timespec_add (struct timespec* res, const struct timespec* a, const struct timespec* b);
void timespec_sub (struct timespec* res, const struct timespec* a, const struct timespec* b);



#endif /* TIMESPECT_OPERATIONS_H_ */
