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
	delay_init();	    	 //��ʱ������ʼ��	 
	beep_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600); 
	key_init();
	TIM3_Int_Init(999,7199);
	GPIO_Configuration();
	LCD1602_Init();
	system_init();
//	LCD1602_ClearScreen();
//	LCD1602_Show_Str(0,0,welcome);
//	LCD1602_Show_Str(0,1,loading);//��ʾ���ӳƳ�ʼ��
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
			case key_d:		//����ȷ�Ϻ������ز���
				sum=system_weight();

				key=key_0;	//����ȷ�Ͻ���Ƽ۲���
				while(key!=key_d)
				{
					key=key_scan();
				}				
				if(sum>5000)	//������5kgʱֱ�ӻص�������
					break;
				system_count(sum);
				key=key_0;
				while(key!=key_d)
				{
					key=key_scan();
				}
			break;
			default:		
				system_start();	//�������ֱ�ӱ��������治��
			break;
		}
		
	}

	return 0;
}

