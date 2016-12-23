#include "API.h"
sbit DQ=P3^7;          //定义DS18B20总线I/O
uchar T_flag;
/*****延时子程序*****/
void Delay_DS18B20(int num)
{
   uchar i;	   
   while(num--)
   for(i=0;i<12;i++);
} 
/*****初始化DS18B20*****/
void Init_DS18B20(void)
{
   uchar x=0;
   DQ = 1;          //DQ复位
   Delay_DS18B20(2);   //稍做延时  
   DQ = 0;          //单片机将DQ拉低
   Delay_DS18B20(80); //精确延时，大于480us
   DQ = 1;          //拉高总线
   Delay_DS18B20(14);
   x = DQ;            //稍做延时后，如果x=0则初始化成功，x=1则初始化失败
   Delay_DS18B20(20);
}

/*****读一个字节*****/
uchar ReadOneChar(void)
{
   uchar i=0;
   uchar dat = 0;
   for(i=8;i>0;i--)
   {
	   DQ = 0;     // 给脉冲信号
	   dat>>=1;
	   DQ = 1;     // 给脉冲信号
	   if(DQ)
	   dat|=0x80;
	   Delay_DS18B20(8);
   }
   return(dat);
}

/*****写一个字节*****/
void WriteOneChar(uchar dat)
{
	uchar i=0;
	for (i=8; i>0; i--)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_DS18B20(10);
		DQ = 1;
		dat>>=1;
    }
}

/*****读取温度*****/
uint ReadTemperature(void)
{
   uchar Temp_Low=0;
   uchar Temp_High=0;
   uint Temperature=0;
   float Temp=0; 
   Init_DS18B20();
   WriteOneChar(0xCC); //跳过读序号列号的操作
   WriteOneChar(0x44); //启动温度转换
   Delay_DS18B20(120);
   Init_DS18B20();
   WriteOneChar(0xCC); //跳过读序号列号的操作
   WriteOneChar(0xBE); //读取温度寄存器
   Temp_Low=ReadOneChar();      //读低8位
   Temp_High=ReadOneChar();    //读高8位
   if(Temp_High>7)			   //负温度
   {
   		Temp_Low=256-Temp_Low;
		Temp_High=256-Temp_High;
		T_flag=1;//温度标志位，负温度
   }
   else
   T_flag=0;//正温度标志
   Temperature=Temp_High;
   Temperature<<=8;
   Temperature=Temperature|Temp_Low;
   Temp=Temperature*0.0625;
   Temperature= Temp*10+0.5;      //放大10倍输出并四舍五入
   return(Temperature);
}