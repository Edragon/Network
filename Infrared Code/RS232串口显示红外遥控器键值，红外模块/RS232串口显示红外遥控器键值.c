
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit IRIN = P3^3;//�������ͷ������
uchar IRCOM[7];	 //�������ݻ�����  
uchar IR_flag;   //�������ݽ��ձ�־
//����:��ʱ1����
//��ڲ���:x
//���ڲ���:��
//˵��:����12M
void Delay_xms(uint x)
{ 
  uint i,j;
  for(i=0;i<x;i++)
    for(j=0;j<112;j++);
}
//0.14ms��ʱ����
void delay(uchar x)    
{
  uchar i;
  while(x--)
  {
   for (i = 0; i<12; i++) 
   {
    _nop_();
   }
  }
}
//���ڳ�ʼ��(ϵͳ����Ϊ12MHz)
void Uart_init(uchar Baud_flag)
{
   TMOD = 0x20;       //T1 2
   PCON = 0x00;       //SMOD = 0
   SCON = 0x50;	      //����1 8
   switch(Baud_flag)
   {   	
    case 0x00:        //2400 11.0592M:0xf4
	  TH1=0xf3;
	  TL1=0xf3;
	break;
	case 0x01:        //4800 11.0592M:0xfa
	  TH1=0xf9;
	  TL1=0xf9;
	break;
    case 0x02:        //9600 11.0592M:0xfd
	  TH1=0xfd;
	  TL1=0xfd;
	break;
    case 0x03:        //19200 11.0592M:0xfe
      TH1=0xfd;
	  TL1=0xfd;
    break;
	default:          //Ĭ��Ϊ2400
	  TH1=0xf3;
	  TL1=0xf3;
	break;
   }   
}
//���ڷ���
void Send_char(uchar ch)
{
 EA=0;
 SBUF=ch; 
 while(!TI);      //�ȴ��������
 TI=0;           //���ж� 
 EA=1;
}
//�������ݽ���
void IR_IN() interrupt 2 using 0 
{
  uchar j,k,N=0;  
  EX1 = 0;   
  delay(15);
  if (IRIN) 
   {
    EX1 =1;
	return;
   }                            //ȷ��IR�źų���   
  while(!IRIN);            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�ź�
  for (j=0;j<4;j++)         //�ռ���������
  { 
   for (k=0;k<8;k++)        //ÿ��������8λ
   {
    while (IRIN);            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�ź�     
    while (!IRIN);          //�� IR ��Ϊ�ߵ�ƽ    
    while (IRIN)           //����IR�ߵ�ƽʱ��
     {
      delay(1);
      N++;           
      if (N>=30)
	   { 
        EX1=1;
	    return;
       }                  //0.14ms���������Զ��뿪��
     }                        //�ߵ�ƽ�������                
     IRCOM[j]=IRCOM[j] >> 1;                  //�������λ��0
     if (N>=8) {IRCOM[j] = IRCOM[j] | 0x80;}  //�������λ��1
     N=0;
  }//end for k
 }//end for j   
   if (IRCOM[2]!=~IRCOM[3])//����У��
   { 
     EX1=1;
     return; 
   }
   EX1 = 1;
   IR_flag=1; //�ý��ձ�־
} 
void main(void)
{
 Delay_xms(50);      //�ȴ�ϵͳ�ȶ�
 EA=0;
 TR1=1;//������ʱ��
 ES=1; //�������ж�
 IT1=1;//�ⲿ�ж�1,�½��ش���
 EX1=1;//ʹ���ⲿ�ж�1 
 EA=1; //�����ж�
 IRIN=1; //��P3^3�ø�
 Uart_init(0);//�����ʳ�ʼ��Ϊ2400
 while(1)
 {
  if(IR_flag)
  {  
   IR_flag=0;    //����ձ�־   
   Send_char(IRCOM[2]);//�����յ�������ͨ�����ڷ���   
  }
 }
}
