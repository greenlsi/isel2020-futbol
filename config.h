/*
 * config.h
 *
 *  Created on: 26 mar. 2020
 *      Author: happybug
 */

#ifndef CONFIG_H_
#define CONFIG_H_

extern  struct termios orig_termios;
void disable_raw_mode();
void enable_raw_mode();

#endif /* CONFIG_H_ */
