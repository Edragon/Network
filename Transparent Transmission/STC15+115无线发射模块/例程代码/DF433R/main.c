
/*****************************************
������������STC15F/L104W
****************************************/

/*******************************************
�ֶ������£�

�½��أ�1ms�ĸߵ�ƽ�����500us�ĵ͵�ƽ��
��ʼλ��4ms�ĸߵ�ƽ�����4ms�ĵ͵�ƽ��
����1��2ms�ĸߵ�ƽ�����500us�ĵ͵�ƽ��
����0��1ms�ĸߵ�ƽ�����500us�ĵ͵�ƽ��
����λ��4ms�ĵ͵�ƽ��
******************************************/


//���ճ���

#include"reg52.h"  
#define MCU_FREQ                          12000000	//���þ���Ƶ��
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
uchar a,b,c,p,x,y;    //�����ȡ������
TMOD=0X01; 
P3M1=0x04;
TH0=(65536-100)/256; //����ʱ��0 
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
while(RX==0); //��ȡЭ���½���
m=0; 
EX0=0; 
while(RX==1); 
if(m>35&&m<45) //��ȡЭ����ʼλ�ߵ�ƽ
{
m=0; 
while(RX==0); 
if(m>35&&m<45)  //��ȡЭ����ʼλ�͵�ƽ
{
m=0;

while(RX==1);   //��ȡ����1 
if(m>5&&m<15) a=0; 
if(m>15&&m<25)a=4; 
while(RX==0); 
m=0; 

while(RX==1);   //��ȡ����2  
if(m>5&&m<15) b=0; 
if(m>15&&m<25)b=2; 
while(RX==0); 
m=0;  

while(RX==1); //��ȡ����3  
if(m>5&&m<15) c=0; 
if(m>15&&m<25)c=1; 
while(RX==0); 
m=0;  
p=a+b+c;  
x++;  
if(x==1) y=p; 
if(x==2) //�����յ��������ݲŽ���ƥ��
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
