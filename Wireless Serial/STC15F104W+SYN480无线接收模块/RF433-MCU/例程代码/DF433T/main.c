/********************************************
现定义如下：

下降沿：1ms的高电平，随后500us的低电平。
起始位：4ms的高电平，随后4ms的低电平。
数据1： 2ms的高电平，随后500us的低电平。
数据0： 1ms的高电平，随后500us的低电平。
结束位：4ms的低电平。
**********************************************/
//本程序已经过调试硬件测试可用(STC15F104W)，在SYN480的信号输出脚要接信号放大电路
//发射模块c程序

#include<reg52.h>  
#define MCU_FREQ            12000000	//设置晶振频率
#define uchar unsigned char 
sfr P3M0=0xb2;

sbit key0=P3^0; 

sbit key1=P3^1; 


sbit TX=P3^2; 

uchar m; 

void v0(); 

void v1(); 

void v2(); 

void v3();  

void delay_315(); 
void main() 

{ 
uchar i; 
bit dong=0;  //开定时器0中断
TMOD=0X01; 
P3M0=0x08;
TH0=(65536-100)/256; 
TL0=(65536-100)%256; 
EA=1; 
ET0=1; 
TR0=1; 
TX=0; 
while(1)  { 
if(key0==0)     //发送指令0
{ 
delay_315(); 
while(key0==0)
{
v3();
v2();
v0();
v0();
v0();
m=0;
while(m<40);  //4ms低电平
} 
dong=1; 
} 

if(key1==0)  //发送指令1 
{ 
delay_315(); 
while(key1==0)
{
v3();
v2();
v0();
v0();
v1();
m=0;
while(m<40);
} 
dong=1; 
} 
/*
if(key2==0) 
{ 
delay_315(); 
while(key2==0){v3();v2();v0();v1();v0();m=0;while(m<40);} 
dong=1; 
} 

if(key3==0) 
{ 
delay_315(); 
while(key3==0){v3();v2();v0();v1();v1();m=0;while(m<40);} 
dong=1; 
} 


if(dong==1) 
{ 
dong=0; 
for(i=0;i<5;i++){v3();v2();v1();v0();v0();m=0;while(m<40);} 
}
*/ 
} 
}

void timer0() interrupt 1 

{ 
TH0=(65536-100)/256;
TL0=(65536-100)%256; 
m++; 
TF0=0; 
} 

void v0()  // 1MS高电平500us低电平	数据0 
{ 
m=0; 
while(m<10) 
TX=1; 
m=0; 
while(m<5) 
TX=0; 
} 

void v1()   // 2MS高电平500us低电平		 数据1
{ 
m=0; 
while(m<20) 
TX=1; 
m=0; 
while(m<5) 
TX=0; 
} 



void v2()  // 4MS高电平4ms低电平	   起始位
{ 
m=0; 
while(m<40) 
TX=1; 
m=0; 
while(m<40) 
TX=0; 
} 
void v3()  // 1MS高电平500us低电平 	  下降沿	 

{ 
m=0; 
while(m<10) 
TX=1; 
m=0; 
while(m<5) 
TX=0; 
} 

void delay_315() 
{ 
uchar i,j; 
for(i=0;i<10;i++) 
for(j=0;j<110;j++); 
} 