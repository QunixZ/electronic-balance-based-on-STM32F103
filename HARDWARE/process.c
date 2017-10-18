#include "process.h"
#include "lcd1602.h"
#include "delay.h"
#include "hx711.h"
#include "usart.h"
#include "key.h"
#include "beep.h"

u8 welcome[]="welcome!";
u8 loading[]="system loading...";
u8 start[]="Press'D'to start";
u8 weight[]="weighting...";
u8 error[]="overweight!";
u8 count1[]="input price:";
u8 count2[]="/gram";
u8 total[]="the total price is";
	
	
//��ʼ������
void system_init()
{
	LCD1602_ClearScreen();
	LCD1602_Show_Str(0,0,welcome);
	LCD1602_Show_Str(0,1,loading);//��ʾ���ӳƳ�ʼ��
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(500);
}
//��ʼ����
void system_start()
{
	LCD1602_ClearScreen();
	LCD1602_Show_Str(0,0,start);
}
//���ؽ���
float system_weight()
{
	int i;
	float sum=0;
	TIM_Cmd(TIM3, DISABLE); //�����ȹرռ�ʱ�����������ݳ���
	
	LCD1602_ClearScreen();
	LCD1602_Show_Str(0,0,weight);
	Weight_Shiwu=0;
	for(i=0;i<20;i++)
	{
		get_weight();
		if(Weight_Shiwu<1)	//�ȴ�������Ʒ�ٿ�ʼ����
		{
			Weight_Shiwu=0;
			i--;
		}
		if(i>4)							//��Ʒ�շ���ʱ����ҡ�Ρ��ֵ������Ȼᵼ������������Ӧ����ȥ
		{
		sum+=Weight_Shiwu/15;
		delay_ms(10);
		}
	}
	//printf("%f\r\n",sum);	��ӡ�����ڷ������
	
	//1602��ʾ��ֵ
	TIM_Cmd(TIM3, ENABLE);
	if(sum>5000)					//���г����жϣ����Ʒ�������
	{
		LCD1602_Show_Str(0,0,error);
		BEEP=1;	//������
		delay_ms(1000);
		BEEP=0;
		delay_ms(200);
		BEEP=1;
		delay_ms(500);
		BEEP=0;
		return sum;
	}
	if(sum>1000)					//������С��1000ʱ����ʾǧλ����ͬ
	{
		LCD1602_Write_Cmd(line_2+8);
		LCD1602_Write_Dat(sum/1000+0x30);
		
		LCD1602_Write_Cmd(line_2+9);
		LCD1602_Write_Dat((int)sum%1000/100+0x30);
		
		LCD1602_Write_Cmd(line_2+10);
		LCD1602_Write_Dat((int)sum%100/10+0x30);
	}
	
	else if(sum>100)
	{
		LCD1602_Write_Cmd(line_2+9);
		LCD1602_Write_Dat(sum/100+0x30);
		
		LCD1602_Write_Cmd(line_2+10);
		LCD1602_Write_Dat((int)sum%100/10+0x30);

	}
	
		else if(sum>10)
		{
			LCD1602_Write_Cmd(line_2+10);
			LCD1602_Write_Dat((int)sum%100/10+0x30);
		}
	

	
	LCD1602_Write_Cmd(line_2+11);
	LCD1602_Write_Dat((int)sum%10+0x30);
	
	LCD1602_Write_Cmd(line_2+12);
	LCD1602_Write_Dat('.');
	
	LCD1602_Write_Cmd(line_2+13);
	LCD1602_Write_Dat((int)(sum*10)%10+0x30);
	
	LCD1602_Write_Cmd(line_2+14);
	LCD1602_Write_Dat((int)(sum*100)%10+0x30);
	
	LCD1602_Write_Cmd(line_2+15);
	LCD1602_Write_Dat('g');
	
	return sum;
	//LCD1602_Write_Dat(0x30);
}
//�Ƽ۽���
void system_count(float sum)
{
	int price[6]={0x30,0x30,0x30,0x30,0x30,0x30},bit;
	float true_price;
	int k=0;
	
	LCD1602_ClearScreen();
	LCD1602_Show_Str(0,0,count1);
	LCD1602_Show_Str(11,1,count2);
	
	LCD1602_Set_Cursor(5,1);
	
	while((bit=key_scan())!=key_d)
	{
		if(bit==key_c)
		{
			if(k>0)
			{
				k--;
				LCD1602_Set_Cursor(5+k,1);//���ú���ɾ���������ڰ���Cʱ�����޸�����ļ۸�
				
			}
		}
		else if(bit>-1)
		{
			price[k++]=bit;
			LCD1602_Write_Dat(bit);
		}
		

	}
	true_price=(price[0]-0x30)*100+(price[1]-0x30)*10+price[2]-0x30+(price[4]-0x30)*0.1+(price[5]-0x30)*0.01;
	
	sum=true_price*sum;
	
	LCD1602_ClearScreen();
	LCD1602_Show_Str(0,0,total);

	//1602��ʾ��ֵ
	if(sum>10000)
	{
		LCD1602_Write_Cmd(line_2+7);
		LCD1602_Write_Dat(sum/10000+0x30);
				
		LCD1602_Write_Cmd(line_2+8);
		LCD1602_Write_Dat((int)sum%10000/1000+0x30);
		
		LCD1602_Write_Cmd(line_2+9);
		LCD1602_Write_Dat((int)sum%1000/100+0x30);
		
		LCD1602_Write_Cmd(line_2+10);
		LCD1602_Write_Dat((int)sum%100/10+0x30);
	}
	
	else if(sum>1000)
	{
		LCD1602_Write_Cmd(line_2+8);
		LCD1602_Write_Dat(sum/1000+0x30);
		
		LCD1602_Write_Cmd(line_2+9);
		LCD1602_Write_Dat((int)sum%1000/100+0x30);
		
		LCD1602_Write_Cmd(line_2+10);
		LCD1602_Write_Dat((int)sum%100/10+0x30);
	}
	
	else if(sum>100)
	{
		LCD1602_Write_Cmd(line_2+9);
		LCD1602_Write_Dat(sum/100+0x30);
		
		LCD1602_Write_Cmd(line_2+10);
		LCD1602_Write_Dat((int)sum%100/10+0x30);

	}
	
		else if(sum>10)
		{
			LCD1602_Write_Cmd(line_2+10);
			LCD1602_Write_Dat((int)sum%100/10+0x30);
		}
	

	
	LCD1602_Write_Cmd(line_2+11);
	LCD1602_Write_Dat((int)sum%10+0x30);
	
	LCD1602_Write_Cmd(line_2+12);
	LCD1602_Write_Dat('.');
	
	LCD1602_Write_Cmd(line_2+13);
	LCD1602_Write_Dat((int)(sum*10)%10+0x30);
	
	LCD1602_Write_Cmd(line_2+14);
	LCD1602_Write_Dat((int)(sum*100)%10+0x30);
	
}

