#include "API.h"
sbit DQ=P3^7;          //����DS18B20����I/O
uchar T_flag;
/*****��ʱ�ӳ���*****/
void Delay_DS18B20(int num)
{
   uchar i;	   
   while(num--)
   for(i=0;i<12;i++);
} 
/*****��ʼ��DS18B20*****/
void Init_DS18B20(void)
{
   uchar x=0;
   DQ = 1;          //DQ��λ
   Delay_DS18B20(2);   //������ʱ  
   DQ = 0;          //��Ƭ����DQ����
   Delay_DS18B20(80); //��ȷ��ʱ������480us
   DQ = 1;          //��������
   Delay_DS18B20(14);
   x = DQ;            //������ʱ�����x=0���ʼ���ɹ���x=1���ʼ��ʧ��
   Delay_DS18B20(20);
}

/*****��һ���ֽ�*****/
uchar ReadOneChar(void)
{
   uchar i=0;
   uchar dat = 0;
   for(i=8;i>0;i--)
   {
	   DQ = 0;     // �������ź�
	   dat>>=1;
	   DQ = 1;     // �������ź�
	   if(DQ)
	   dat|=0x80;
	   Delay_DS18B20(8);
   }
   return(dat);
}

/*****дһ���ֽ�*****/
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

/*****��ȡ�¶�*****/
uint ReadTemperature(void)
{
   uchar Temp_Low=0;
   uchar Temp_High=0;
   uint Temperature=0;
   float Temp=0; 
   Init_DS18B20();
   WriteOneChar(0xCC); //����������кŵĲ���
   WriteOneChar(0x44); //�����¶�ת��
   Delay_DS18B20(120);
   Init_DS18B20();
   WriteOneChar(0xCC); //����������кŵĲ���
   WriteOneChar(0xBE); //��ȡ�¶ȼĴ���
   Temp_Low=ReadOneChar();      //����8λ
   Temp_High=ReadOneChar();    //����8λ
   if(Temp_High>7)			   //���¶�
   {
   		Temp_Low=256-Temp_Low;
		Temp_High=256-Temp_High;
		T_flag=1;//�¶ȱ�־λ�����¶�
   }
   else
   T_flag=0;//���¶ȱ�־
   Temperature=Temp_High;
   Temperature<<=8;
   Temperature=Temperature|Temp_Low;
   Temp=Temperature*0.0625;
   Temperature= Temp*10+0.5;      //�Ŵ�10���������������
   return(Temperature);
}