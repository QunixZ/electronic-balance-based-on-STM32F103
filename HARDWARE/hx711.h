#ifndef _HX711_H_
#define _HX711_H_

#include "stm32f10x_gpio.h"
#include "delay.h"
#include "sys.h"

/***************HX711���Ŷ���*****************/
//ʹ��SPIͨ��
//SDK=PB0
//DOUT=PB1

#define SCK PBout(0)
#define DOUT PBin(1)
#define Gap_Value 399.5//���崫����У׼������ֱ��Ӱ�����׼ȷ��

extern u32 HX711_Buffer;
extern u32 Weight_Maopi;
extern float Weight_Shiwu;
//extern u8 Flag_Error;

void hx711_init(void);
u32 hx711_read(void);
void get_maopi(void);
void get_weight(void);

#endif
