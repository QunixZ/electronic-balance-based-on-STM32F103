#include "hx711.h"

u32 HX711_Buffer;
u32 Weight_Maopi;
float Weight_Shiwu;
//u8 Flag_Error;

//��ʼ���������ӿ�
void hx711_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	
	//HX711_DOUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);					//��ʼ������Ϊ0
}


//��ȡ��ʱ�̴���������
u32 hx711_read(void)	//����128
{
	unsigned long count; 
	unsigned char i; 
  DOUT=1; 
	delay_us(1);
  SCK=0; 
  count=0; 
  while(DOUT); 
  for(i=0;i<24;i++)
	{ 
	  SCK=1; 
	  count=count<<1; 
		delay_us(1);
		SCK=0; 
	  if(DOUT)
		count++; 
		delay_us(1);
	} 
 	SCK=1; 
  count=count^0x800000;//��25�������½�����ʱ��ת������
	delay_us(1);
	SCK=0;  
	return(count);
}


//�õ���ʱ�̴������������洢
void get_maopi()
{
	Weight_Maopi = hx711_read();
}

//����ʵ������
void get_weight()
{
		HX711_Buffer = hx711_read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//��ȡʵ���AD������ֵ��
	
		Weight_Shiwu = ((float)Weight_Shiwu/Gap_Value); 	//����ʵ���ʵ������
																		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
																		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
																		//������Գ���������ƫСʱ����С����ֵ��
	}
}


