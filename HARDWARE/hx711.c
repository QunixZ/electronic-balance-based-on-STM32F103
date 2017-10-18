#include "hx711.h"

u32 HX711_Buffer;
u32 Weight_Maopi;
float Weight_Shiwu;
//u8 Flag_Error;

//初始化传感器接口
void hx711_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	
	//HX711_DOUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);					//初始化设置为0
}


//读取该时刻传感器读数
u32 hx711_read(void)	//增益128
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
  count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	delay_us(1);
	SCK=0;  
	return(count);
}


//得到该时刻传感器读数并存储
void get_maopi()
{
	Weight_Maopi = hx711_read();
}

//计算实际重量
void get_weight()
{
		HX711_Buffer = hx711_read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。
	
		Weight_Shiwu = ((float)Weight_Shiwu/Gap_Value); 	//计算实物的实际重量
																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
																		//当发现测试出来的重量偏大时，增加该数值。
																		//如果测试出来的重量偏小时，减小改数值。
	}
}


