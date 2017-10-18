#include "stm32f10x.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "hx711.h"
#include "delay.h"
#include "timer.h"
#include "lcd1602.h"
#include "process.h"
#include "beep.h"

int main()
{

	int key=0;
	float sum=0;
	hx711_init();
	delay_init();	    	 //延时函数初始化	 
	beep_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600); 
	key_init();
	TIM3_Int_Init(999,7199);
	GPIO_Configuration();
	LCD1602_Init();
	system_init();
//	LCD1602_ClearScreen();
//	LCD1602_Show_Str(0,0,welcome);
//	LCD1602_Show_Str(0,1,loading);//显示电子称初始化
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(500);
	
	while(1)
	{
		system_start();
		
		key=key_scan();
		while(key!=key_d)
		{
			key=key_scan();
		}
		
		switch(key)
		{
			case key_d:		//按下确认后进入测重操作
				sum=system_weight();

				key=key_0;	//按下确认进入计价操作
				while(key!=key_d)
				{
					key=key_scan();
				}				
				if(sum>5000)	//当超过5kg时直接回到主界面
					break;
				system_count(sum);
				key=key_0;
				while(key!=key_d)
				{
					key=key_scan();
				}
			break;
			default:		
				system_start();	//其它情况直接保持主界面不变
			break;
		}
		
	}

	return 0;
}

