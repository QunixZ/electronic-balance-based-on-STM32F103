#ifndef _HX711_H_
#define _HX711_H_

#include "stm32f10x_gpio.h"
#include "delay.h"
#include "sys.h"

/***************HX711引脚定义*****************/
//使用SPI通信
//SDK=PB0
//DOUT=PB1

#define SCK PBout(0)
#define DOUT PBin(1)
#define Gap_Value 399.5//定义传感器校准参数，直接影响测量准确性

extern u32 HX711_Buffer;
extern u32 Weight_Maopi;
extern float Weight_Shiwu;
//extern u8 Flag_Error;

void hx711_init(void);
u32 hx711_read(void);
void get_maopi(void);
void get_weight(void);

#endif
