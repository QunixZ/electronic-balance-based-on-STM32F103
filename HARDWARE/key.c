#include "key.h"

void key_init()
{
	GPIO_InitTypeDef GPIO_StructInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//时钟使能
	
	GPIO_StructInit.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//将PA0到PA3配置为推挽输出
	GPIO_StructInit.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_StructInit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_StructInit);
	
	GPIO_StructInit.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//将PA4到PA7配置为下拉输入
	GPIO_StructInit.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_StructInit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_StructInit);	
			
}

//键盘扫描函数，返回被按下的键值
int key_scan(void)
{
	int Key_Value= -1;
//	u16 Write_Value=0x00;
	
	GPIO_Write(GPIOA,(GPIOA->ODR&0xfff0|0xf));
	
	if((GPIOA->IDR&0x00f0)==0x0000)
		return -1;
	else
	{
		delay_ms(10);
	}
	
	if((GPIOA->IDR&0x00f0)==0x0000)
		return -1;
	else
	{
		GPIO_Write(GPIOA,(GPIOA->ODR&0xfff0|0x1));
		switch((GPIOA->IDR&0x00f0))
		{
			case 0x0010:
				Key_Value=key_d;
			break;
			case 0x0020:
				Key_Value=key_c;
			break;
			case 0x0040:
				Key_Value=key_b;
			break;
			case 0x0080:
				Key_Value=key_a;
			default:
				break;
		}
		
		GPIO_Write(GPIOA,(GPIOA->ODR&0xfff0|0x2));
		switch((GPIOA->IDR&0x00f0))
		{
			case 0x0010:
				Key_Value=key_s;
			break;
			case 0x0020:
				Key_Value=key_9;
			break;
			case 0x0040:
				Key_Value=key_6;
			break;
			case 0x0080:
				Key_Value=key_3;
			default:
				break;
		}
		
		GPIO_Write(GPIOA,(GPIOA->ODR&0xfff0|0x4));
		switch((GPIOA->IDR&0x00f0))
		{
			case 0x0010:
				Key_Value=key_0;
			break;
			case 0x0020:
				Key_Value=key_8;
			break;
			case 0x0040:
				Key_Value=key_5;
			break;
			case 0x0080:
				Key_Value=key_2;
			default:
				break;
		}
		
		GPIO_Write(GPIOA,(GPIOA->ODR&0xfff0|0x8));
		switch((GPIOA->IDR&0x00f0))
		{
			case 0x0010:
				Key_Value=key_x;
			break;
			case 0x0020:
				Key_Value=key_7;
			break;
			case 0x0040:
				Key_Value=key_4;
			break;
			case 0x0080:
				Key_Value=key_1;
			default:
				break;
		}
	}
	
	return Key_Value;
}

