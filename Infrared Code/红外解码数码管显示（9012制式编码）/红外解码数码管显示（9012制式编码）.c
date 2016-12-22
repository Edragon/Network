/*copyright 2009,Shen zhen  JinChuang Electronic Technology co.,Ltd
 *
 *This sample is used for Timer1 16bit timer mode.
 *
 *write by Shifang 2009-4-23
 *
 *V1.1
 */
 //ʹ��12M���� ������TC9012оƬ������оƬ�����и��Ľ���ʱ��
#include<reg52.h>
#include<stdio.h>
#include<intrins.h>

////////////////////////////////////////////////
#define TURE 1
#define FALSE 0

////////////////////////////////////////////////

sbit IR=P3^2;//����ӿڱ�־


////////////////////////////////////////////

unsigned char  irtime;//������ȫ�ֱ���

bit irpro_ok,irok;
unsigned char IRcord[4];
unsigned char   irdata[33];

//////////////////////////////////////////////

void Delay(unsigned char mS);
void Ir_work(void);
void Ircordpro(void);

//////////////////////////////////////////////////////////////////  

void tim0_isr (void) interrupt 1 using 1//��ʱ��0�жϷ�����
{
  irtime++;
}

///////////////////////////////////////////////////////////////////////
void ex0_isr (void) interrupt 0 using 0//�ⲿ�ж�0������
{
  static unsigned char  i;
  static bit startflag;

 if(startflag)
 {
   
    if(irtime<55&&irtime>40)//������ TC9012��ͷ��
            i=0;
     
    		irdata[i]=irtime;//һ�δ洢32λ��ƽ���
    		irtime=0;
    		i++;
   			 if(i==33)
      			{
	  			 irok=1;
				 i=0;
	  			}
          }
	 
  	 else
		{irtime=0;startflag=1;}

}

////////////////////////////////////////////////////////////////////
void TIM0init(void)//��ʱ��0��ʼ��
{

  TMOD=0x02;//��ʱ��0������ʽ2��TH0����װֵ��TL0�ǳ�ֵ
  TH0=0x00;//reload value
  TL0=0x00;//initial value
  ET0=1;//���ж�
  TR0=1;
}
///////////////////////////////////////////////////////////////////
void EX0init(void)
{
 IT0 = 1;   // Configure interrupt 0 for falling edge on /INT0 (P3.2)
 EX0 = 1;   // Enable EX0 Interrupt
 EA = 1;  
}
/****************************************************************/

/******************************************************************/

  void Ir_work(void)//�����ֵɢת����
  {
       switch(IRcord[2])//�жϵ���������ֵ
	         {
			 case 1:P0=0xf9;break;//1 ��ʾ��Ӧ�İ���ֵ
			 case 2:P0=0xa4;break;//2
			 case 3:P0=0xb0;break;//3
			 case 4:P0=0x99;break;//4
			 case 5:P0=0x92;break;//5
			 case 6:P0=0x82;break;//6
			 case 7:P0=0xf8;break;//7
			 case 8:P0=0x80;break;//8
			 case 9:P0=0x90;break;//9
		    case 0:P0=0xc0;break;//0

			 }

   

		  irpro_ok=0;//������ɱ�־

  }

/*****************************************************************/
void Ircordpro(void)//������ֵ������
{ 
  unsigned char i, j, k;
  unsigned char cord,value;

  k=1;
  for(i=0;i<4;i++)//����4���ֽ�
     {
      for(j=1;j<=8;j++) //����1���ֽ�8λ
         {
          cord=irdata[k];
          if(cord>7)//����ĳֵΪ1
		    {
             value=value|0x80;
			}
          else 
		    {
             value=value;
			}
          if(j<8)
		    {
			 value=value>>1;
			}
           k++;
         }
     IRcord[i]=value;
     value=0;     
     } irpro_ok=1;//������ϱ�־λ��1
    
}




/////////////////////////////////////////////////////////////////

void main(void)
{
 EX0init(); // Enable Global Interrupt Flag
 TIM0init();//��ʼ����ʱ��0

 P2=0x00;//8λ�����ȫ����ʾ

 while(1)//��ѭ��
   {
    if(irok)
	  {   
	   Ircordpro();//��ֵ����
 	   irok=0;
	  }

    if(irpro_ok)//step press key
	  {
	   Ir_work();//��ֵʶ��ɢת
  	  }
   }
}
  