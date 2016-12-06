/**********************************************************************************
 * ������  :
 * ����    :ͨ���ֻ���������LED
 						ͨ��STC�����崮��2����ģ����������������ӹ��̷��͵�����1�������ֻ�
						��������SPP���Ӻ󣬻ᶨʱ���͹̶����ݸ��ֻ��������ڣ��ֻ��������͵�����
						���Զ�ת��������1��
						���г���ǰ�������ȴ��������׵��ֻ������������֡�
 * ʵ��ƽ̨:STC15XX
 * ��汾  :
**********************************************************************************/

#include "string.h"
#include "delay.h"
#include "uart.h"


#define Buf1_Max 60 					  //����1���泤��
#define Buf2_Max 200 					  //����2���泤��
/*************	���س�������	**************/
sbit RUNING_LED = P2^1;					//����ָʾ��
sbit LED  			= P3^3;					//����ָʾ��

const char *sendtable="Niren-elec Bluetooth LED control\r\n\32";

/*************  ���ر�������	**************/
xdata u8 Uart1_Buf[Buf1_Max];
xdata u8 Uart2_Buf[Buf2_Max];
char *p1,*p2; 

u16 Times=0;
u8 First_Int = 0,shijian=0;
u8 Timer_send;//��ʱ���ͼ�ʱ��
//u8 Time_count=0;
bdata u8 Flag;//��ʱ����־λ
sbit Timer0_start =Flag^0;	//��ʱ��0��ʱ����������
sbit Uart2_Start  =Flag^1;	//����2��ʼ��������
sbit Uart2_End		=Flag^2;	//����2�������ݽ���


/*************	���غ�������	**************/
void GPIO_config(void);
void Timer0Init(void);
void CLR_Buf2(void);
u8 Find(u8 *a);
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time);

/*************  �ⲿ�����ͱ�������*****************/




/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : ����2������GPRSģ��ͨ�ţ�����1���ڴ��ڵ��ԣ����Ա��������س���ʱ����
					 �����͵�ģ��
*******************************************************************************/
void main(void)
{
	GPIO_config();
	Uart1Init();
	Uart2Init();
	Timer0Init();
	EA=1;	//�����ж�

	UART1_SendString("SIM808ģ���������Գ���\r\n");
	UART1_SendString("����ֻ�������������\r\n");
	UART1_SendString("SIM808ģ��������\r\n");
	Second_AT_Command("AT+BTPOWER=1\r\n","AT",2);//��������Դ,������ж�OK����Ϊ��Դԭ�������ٷ��ʹ򿪵Ļ��᷵�ش���
	delay_ms(100); 
	Second_AT_Command("AT+BTUNPAIR=0\r\n","AT",2);//ɾ������Ե���������,���ж�OK����Ϊû������Ե��豸ʱ����ERROR
	UART1_SendString("SIM808ģ�鿪ʼ���������豸,��ȷ���ֻ��������ڿɱ�����\r\n");
  do
	{
		UART1_SendString("�����豸��............\r\n");
		Second_AT_Command("AT+BTSCAN=1,10\r\n","+BTSCAN: 1",11);   //���������������豸������ʱ��10S
	}while(strstr((const char*)Uart2_Buf,"+BTSCAN: 0")==NULL);   //�ȴ��������豸���˳�
	UART1_SendString("���ӵ�һ���豸............\r\n");
	do
	{
		Second_AT_Command("AT+BTPAIR=0,1\r\n","+BTPAIRING:",3);//���ӵ�һ�����������豸 
		delay_ms(200); 
		Second_AT_Command("AT+BTPAIR=1,1\r\n","+BTPAIR:",35);//��Ӧ����,����ֻ����ڲ�ȷ��ƥ�䣬��Ҫ30S��Ż��ϱ����ʧ��
		delay_ms(100);//�ȴ������������
	}while(strstr((const char*)Uart2_Buf,"+BTPAIR: 1")==NULL);//ƥ��ɹ�
	UART1_SendString("SIM808ģ������ƥ��ɹ�\r\n");
	UART1_SendString("����ֻ�������������\r\n");
	Second_AT_Command("AT+BTGETPROF=1\r\n","BTGETPROF: 4",5);//��ȡ���������б�
	Second_AT_Command("AT+BTCONNECT=1,4\r\n","OK",2);//��ȡ���������б�
	UART1_SendString("SIM808ģ����������SPP����ɹ�\r\n");
	CLR_Buf2(); 
	while(1)
	{
		//���յ�����
		if((p1=(char*)strstr((const char*)Uart2_Buf,"DATA:")),(p1!=NULL))//Ѱ�ҿ�ʼ��
		{		
				if((p2=(char*)strstr((const char*)p1,"\x0d\x0a")),(p2!=NULL))//Ѱ�ҽ�����
				{
					char *p3;
					*p2=0;//��ӽ�����
					p3=strstr((const char*)p1,",");//������һ��','
					p1=strstr((const char*)p3+1,",");//�����ڶ���','
					UART1_SendString("���յ�������:");
					UART1_SendString(p1+1);
					UART1_SendLR();
					if(*(p1+4)==(char)0xB1)
					{
						LED=~LED;
					}
					CLR_Buf2(); 
				}
		}else
		if(Timer_send>100)//����ʱ��ʱ��������
		{	
			Second_AT_Command("AT+BTSPPSEND",">",1);
			Second_AT_Command((char *)sendtable,"OK",1);
			Timer_send=0;
		}
	}
}

/*******************************************************************************
* ������ : Uart1 
* ����   : ����1�жϷ�����ں���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Uart1() interrupt 4
{
    if (RI)
    {
        RI = 0;                 //���RIλ
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
    }
}

/*******************************************************************************
* ������ : Uart2
* ����   : ����2�жϷ�����ں���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Uart2() interrupt 8
{
		IE2  &= ~0x01;   //�رմ���2�ж�
    if (S2CON & S2RI)
    {
      S2CON &= ~S2RI;         //���S2RIλ
			Uart2_Buf[First_Int] = S2BUF;  	  //�����յ����ַ����浽������
			First_Int++;                			//����ָ������ƶ�
			if(First_Int > Buf2_Max)       		//���������,������ָ��ָ�򻺴���׵�ַ
			{
				First_Int = 0;
			}
    }
    if (S2CON & S2TI)
    {
      S2CON &= ~S2TI;         //���S2TIλ
    }
		IE2  |= 0x01;   //ʹ�ܴ���2�ж�
}
/*******************************************************************************
* ������ : Timer0_ISR
* ����   : ��ʱ��0�жϷ�����ں���,20ms�ж�һ��
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Timer0_ISR() interrupt 1
{
	static u8 Time_count=0; 
	TR0=0;//�ض�ʱ��
	Time_count++;
	if(Time_count>=50)
	{
		Time_count = 0;
		RUNING_LED =~RUNING_LED;
	}
	if(Timer0_start)
	Times++;
	if(Times > (u16)(50*shijian))
	{
		Timer0_start = 0;
		Times = 0;
	}
	Timer_send++;
	TR0=1;//����ʱ��
}
/*******************************************************************************
* ������ : GPIO_config
* ����   : IO�����ú���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void	GPIO_config(void)
{
		P3M1 &= 0XC3;  //����P32~P35Ϊ�������
		P3M0 |=	~0XC3;
		LED=0;
		RUNING_LED=0;
}
void Timer0Init(void)		//20����@22.1184MHz
{
	AUXR &= 0x7F;	//12Tģʽ
	TMOD &= 0xF0;	//���ö�ʱ��ģʽ 16λ����
	TL0 = 0x00;		//�趨��ʱ����ֵ
	TH0 = 0x70;		//�趨��ʱ����ֵ
	TF0 = 0;			//���TF0��־
	TR0 = 1;			//��ʱ��0��ʼ��ʱ
	ET0 = 1;    	//ʹ�ܶ�ʱ��0�ж�
}
/*******************************************************************************
* ������ : CLR_Buf2
* ����   : �������2��������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void CLR_Buf2(void)
{
	u16 k;
	for(k=0;k<Buf2_Max;k++)      //��������������
	{
		Uart2_Buf[k] = 0x00;
	}
    First_Int = 0;              //�����ַ�������ʼ�洢λ��
}

/*******************************************************************************
* ������ : Find
* ����   : �жϻ������Ƿ���ָ�����ַ���
* ����   : 
* ���   : 
* ����   : unsigned char:1 �ҵ�ָ���ַ���0 δ�ҵ�ָ���ַ� 
* ע��   : 
*******************************************************************************/

u8 Find(u8 *a)
{ 
  if(strstr(Uart2_Buf,a)!=NULL)
	    return 1;
	else
			return 0;
}

/*******************************************************************************
* ������ : Second_AT_Command
* ����   : ����ATָ���
* ����   : �������ݵ�ָ�롢���͵ȴ�ʱ��(��λ��S)
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/

void Second_AT_Command(u8 *b,u8 *a,u8 wait_time)         
{
	u8 i;
	u8 *c;
	c = b;										//�����ַ�����ַ��c
	CLR_Buf2(); 
  i = 0;
	while(i == 0)                    
	{
		if(!Find(a)) 
		{
			if(Timer0_start == 0)
			{
				UART1_SendString(Uart2_Buf);
				b = c;							//���ַ�����ַ��b
				for (b; *b!='\0';b++)
				{
					UART2_SendData(*b);
				}
				UART2_SendLR();	
				Times = 0;
				shijian = wait_time;
				Timer0_start = 1;
		   }
    }
 	  else
		{
			i = 1;
			Timer0_start = 0;
		}
	}
}
