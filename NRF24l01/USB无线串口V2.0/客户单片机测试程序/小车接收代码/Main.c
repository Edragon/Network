#include "STC15W1K16PWM.h"
#include "API.h"
#define uchar unsigned char
#define uint unsigned int
uchar TX_ADDRESS[TX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���͵�ַ
uchar RX_ADDRESS[RX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���յ�ַ
uchar   rate = 0x0F;    				    //2Mbs, 0dB  ���������濪��
uchar rece_buf[32];	
#define weigou WDT_CONTR=0x35;
sbit PWM=P2^6;
uint num;
uint Pus,Input;
uchar speed;
sbit LED1=P0^0;
sbit LED2=P0^1;
sbit LED3=P0^2;
sbit LED4=P0^3;

sbit M1=P2^0;
sbit M2=P2^1;


void Timer0Init(void)		//10΢��@30.000MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xD4;		//���ö�ʱ��ֵ
	TH0 = 0xFE;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	EA=1;
	ET0=1;
	P2M0=0;
	P2M1=0;
}

void delay(uint t)
{
	uchar i;
	while(t--)
	for(i=0;i<100;i++);
}
void  Forward()
{
	M1=0;
	M2=1;
}

void  Back()
{
	M1=1;
	M2=0;
}
void Stop()
{
	M1=M2=0;
}


void main()
{
	uchar count;
	uint tt;
	Input=speed=120;
	while(NRF24L01_Check()); // �ȴ���⵽NRF24L01������Ż�����ִ��
	NRF24L01_RT_Init(TX_PLOAD_WIDTH,TX_ADDRESS,TX_ADR_WIDTH,RX_ADDRESS,RX_ADR_WIDTH,rate);
	Timer0Init(); 
	LED1=0;
	while(1)
	{
		weigou;
		if(NRF_IRQ==0)	 	// �������ģ����յ�����
		{		
			if(NRF24L01_RxPacket(rece_buf)==0)
			if((rece_buf[1]>=0)&&(rece_buf[1]<=240)) 
			{
				Input=rece_buf[1]+60;	
			} 
			speed=rece_buf[2]; 
			count=120;
			
		}
		if(speed>120) 	 	//ǰ��
		{
			count++;
			if(count>240)count=119;
			if(speed>count)Forward();
			if(speed<count)Stop();
			
		}
		if(speed<120) 		  //����
		{
			count--;
			if(count==0)count=121;
			if(speed<count)Back();
			if(speed>count)Stop();
			
		}
		if(speed==120)Stop();
		tt++;
		if(tt>50000)
		{
			LED1=!LED1;
			tt=0;
		}
	}

}

void timer0() interrupt 1
{
	num++;	  //10us	   =100��1ms
	Pus++;
	if(num==2000)	 //20ms
	{
		PWM=1;
		num=0;
		Pus=0;
	}
	if(Pus==Input)
	{
		PWM=0;
		Pus=0;
	}
}