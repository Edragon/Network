							#include"reg52.h"

#define uint unsigned int
#define uchar unsigned char

void main(void)
{
	EX1=1;
	EA=1;
	while(1);
}

void interrupt1()interrupt 2
{
	uchar i=0,j=0,k=0,us=0;
	uchar addr[4]={0};
	EX1=0;

	for(i=0;i<255;i++)  //9ms内有高电平认为是干扰
	{
		if(P3&0x08)	    //255的值实际时间为800us
		{
			EX1=1;
			return;
		}
	}
	while(!(P3&0x08));	//等待9ms低电平过去
   	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			while(P3&0x08);	//等待4.5ms高电平过去	
			while(!(P3&0x08));	//等待0.56ms低电平后面的高电平
			while(P3&0x08)		//计算这个高电平的时间
			{
				for(us=0;us<=32;us++);	//100us的延时语句
				if((k++)>=30)		//高电平时间过长退出程序
				{
					EX1=1;
					return;
				}
			}
			addr[i]=addr[i]>>1;	//接收一位数据
			if(k>=8)
				addr[i]=addr[i]|0x80;	//高电平大于0.56ms，则为1
			k=0;
		}
	}	

	P0=~(addr[2]);	 //P2的LED显示二进制键值

	EX1=1;	  
}	   