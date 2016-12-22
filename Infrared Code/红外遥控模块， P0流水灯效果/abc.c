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

	for(i=0;i<255;i++)  //9ms���иߵ�ƽ��Ϊ�Ǹ���
	{
		if(P3&0x08)	    //255��ֵʵ��ʱ��Ϊ800us
		{
			EX1=1;
			return;
		}
	}
	while(!(P3&0x08));	//�ȴ�9ms�͵�ƽ��ȥ
   	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			while(P3&0x08);	//�ȴ�4.5ms�ߵ�ƽ��ȥ	
			while(!(P3&0x08));	//�ȴ�0.56ms�͵�ƽ����ĸߵ�ƽ
			while(P3&0x08)		//��������ߵ�ƽ��ʱ��
			{
				for(us=0;us<=32;us++);	//100us����ʱ���
				if((k++)>=30)		//�ߵ�ƽʱ������˳�����
				{
					EX1=1;
					return;
				}
			}
			addr[i]=addr[i]>>1;	//����һλ����
			if(k>=8)
				addr[i]=addr[i]|0x80;	//�ߵ�ƽ����0.56ms����Ϊ1
			k=0;
		}
	}	

	P0=~(addr[2]);	 //P2��LED��ʾ�����Ƽ�ֵ

	EX1=1;	  
}	   