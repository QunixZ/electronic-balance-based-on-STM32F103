#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x_gpio.h"
#include "delay.h"

#define key_1 1+0x30
#define key_2 2+0x30
#define key_3 3+0x30
#define key_a 0x31+0x30
#define key_4 4+0x30
#define key_5 5+0x30
#define key_6 6+0x30
#define key_b 0x32+0x30
#define key_7 7+0x30
#define key_8 8+0x30
#define key_9 9+0x30
#define key_c 0x33+0x30
#define key_x 0x35+0x30
#define key_0 0+0x30
#define key_s 0x2e
#define key_d 0x34+0x30


void key_init(void);
int key_scan(void);

#endif

