
/*****************************************
本程序适用于STC15F/L104W
****************************************/

/*******************************************
现定义如下：

下降沿：1ms的高电平，随后500us的低电平。
起始位：4ms的高电平，随后4ms的低电平。
数据1：2ms的高电平，随后500us的低电平。
数据0：1ms的高电平，随后500us的低电平。
结束位：4ms的低电平。
******************************************/


//接收程序

#include"reg52.h"  
#define MCU_FREQ                          12000000	//设置晶振频率
#define uchar unsigned char 
sfr P3M0=0xb2;
sfr P3M1=0xb1;
sbit RX=P3^2; 

sbit red0=P3^0; 

sbit red1=P3^1; 

uchar m; 
bit n;  
void main() 
{ 
uchar a,b,c,p,x,y;    //定义存取的数据
TMOD=0X01; 
P3M1=0x04;
TH0=(65536-100)/256; //开定时器0 
TL0=(65536-100)%256; 
EA=1; 
ET0=1; 
TR0=1; 
EX0=1; 
IT0=1; 
//P0=0Xff; 
//P1=0x00;
red0=1;
red1=1;
p=5; 
x=0;  
while(1) 
{ 
if(n==1) 
{ 
while(RX==0); //读取协议下降沿
m=0; 
EX0=0; 
while(RX==1); 
if(m>35&&m<45) //读取协议起始位高电平
{
m=0; 
while(RX==0); 
if(m>35&&m<45)  //读取协议起始位低电平
{
m=0;

while(RX==1);   //读取数据1 
if(m>5&&m<15) a=0; 
if(m>15&&m<25)a=4; 
while(RX==0); 
m=0; 

while(RX==1);   //读取数据2  
if(m>5&&m<15) b=0; 
if(m>15&&m<25)b=2; 
while(RX==0); 
m=0;  

while(RX==1); //读取数据3  
if(m>5&&m<15) c=0; 
if(m>15&&m<25)c=1; 
while(RX==0); 
m=0;  
p=a+b+c;  
x++;  
if(x==1) y=p; 
if(x==2) //连续收到两次数据才进入匹配
{ 
x=0; 
if(y==p) 
{ 
switch(p) 

{  
case 0:red0=0;red1=1;
       break;
case 1:red0=1;red1=0;
       break;
case 2:red0=1;red1=1; 
       break;
case 3:red0=1;red1=1;  
       break;
case 4:red0=1;red1=1;
       break;
       }
      }
     }
    }
   }
EX0=1;  }
  
 }
}

void INT_0() interrupt 0

{                     
  n=1; 
} 
void timer0() interrupt 1 
{ 
TH0=(65536-100)/256; 
TL0=(65536-100)%256; 
m++; 
TF0=0; 
} 
