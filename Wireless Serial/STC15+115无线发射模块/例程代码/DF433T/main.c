/********************************************
�ֶ������£�

�½��أ�1ms�ĸߵ�ƽ�����500us�ĵ͵�ƽ��
��ʼλ��4ms�ĸߵ�ƽ�����4ms�ĵ͵�ƽ��
����1�� 2ms�ĸߵ�ƽ�����500us�ĵ͵�ƽ��
����0�� 1ms�ĸߵ�ƽ�����500us�ĵ͵�ƽ��
����λ��4ms�ĵ͵�ƽ��
**********************************************/
//�������Ѿ�������Ӳ�����Կ���(STC15F104W)����SYN480���ź������Ҫ���źŷŴ��·
//����ģ��c����

#include<reg52.h>  
#define MCU_FREQ            12000000	//���þ���Ƶ��
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
bit dong=0;  //����ʱ��0�ж�
TMOD=0X01; 
P3M0=0x08;
TH0=(65536-100)/256; 
TL0=(65536-100)%256; 
EA=1; 
ET0=1; 
TR0=1; 
TX=0; 
while(1)  { 
if(key0==0)     //����ָ��0
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
while(m<40);  //4ms�͵�ƽ
} 
dong=1; 
} 

if(key1==0)  //����ָ��1 
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

void v0()  // 1MS�ߵ�ƽ500us�͵�ƽ	����0 
{ 
m=0; 
while(m<10) 
TX=1; 
m=0; 
while(m<5) 
TX=0; 
} 

void v1()   // 2MS�ߵ�ƽ500us�͵�ƽ		 ����1
{ 
m=0; 
while(m<20) 
TX=1; 
m=0; 
while(m<5) 
TX=0; 
} 



void v2()  // 4MS�ߵ�ƽ4ms�͵�ƽ	   ��ʼλ
{ 
m=0; 
while(m<40) 
TX=1; 
m=0; 
while(m<40) 
TX=0; 
} 
void v3()  // 1MS�ߵ�ƽ500us�͵�ƽ 	  �½���	 

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