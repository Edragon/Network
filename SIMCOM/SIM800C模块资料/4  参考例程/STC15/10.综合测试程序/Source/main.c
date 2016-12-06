/**********************************************************************************
 * ������  :sim900a
 * ����    :ͨ�����ڲ���ģ��Ĺ���
 * ʵ��ƽ̨:STC15XX

**********************************************************************************/

#include "string.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

#define Buf1_Max 200 					  //����1���泤��
#define Buf2_Max 200 					  //����2���泤��
/*************	���س�������	**************/
sbit RUNING_LED = P2^1;					//����ָʾ��
sbit LED  			= P3^3;					//����ָʾ��


/*************  ���ر�������	**************/
xdata u16 USART_RX_STA;
xdata u8 Uart1_Buf[Buf1_Max];//����1���ݻ�����
xdata u8 Uart2_Buf[Buf2_Max];//����2���ݻ�����
u8 First_Int = 0,shijian=0;
u16 Times=0;      //��ʱ����
u8 Time_UART1=0;  //����1��ʱ��
u8 Time_UART2=0;  //����2��ʱ��
u8 Time_miao=0;
bdata u8 Flag;//��ʱ����־λ
sbit Timer0_start =Flag^0;	//��ʱ��0��ʱ����������
sbit Uart2_Start  =Flag^1;	//����2��ʼ��������
sbit Uart2_End		=Flag^2;	//����2�������ݽ���

/*************	���غ�������	**************/
void GPIO_config(void);//GPIO�˿�����
void Timer0Init(void);//��ʱ��0��ʼ��
void CLR_Buf2(void);//�������2���ջ���
u8 sim900a_send_cmd(u8 *cmd,u8 *ack,u8 wait_time);//ģ��ָ��ͺ���
void sim900a_test(void);//ģ�����������
void sim900a_mtest();//ģ����Ϣ���
u8 sim900a_gsminfo();//GSM��Ϣ��ʾ(�ź�����,��ص���,����ʱ��)
u8 sim900a_call_test();//���Ų��Գ���
u8 sim900a_sms_test();//���Ų��Գ���
u8 sim900a_gprs_test();//GPRS���ݴ�����Գ���
u8 change_str_hex(u8 *p,u8 len);//�ַ�ת��
u8 sim900a_jz_test();//��վ��λ���Գ���
u8 sim900a_tts_test();//TTS�ı��������Գ���
/*************  �ⲿ�����ͱ�������*****************/




/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : ����2������ģ��ͨ�ţ�����1���ڴ��ڵ��ԣ����Ա��������س���ʱ����
					 �����͵�ģ��
*******************************************************************************/
void main(void)
{
	GPIO_config();//IO����
	Uart1Init();//����1��ʼ��
	Uart2Init();//����2��ʼ��
	Timer0Init();//��ʱ��0��ʼ��
	EA=1;	//�����ж�
	UART1_SendString("GPRSģ����Ų��Գ���\r\n");//��ӡ��Ϣ
	UART1_SendString("GPRSģ����ע������\r\n");
	sim900a_test(); //sim900a���Գ���
	while(1)
	{
	
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
		u8 res;
		ES=0;
    if (RI)
    {
        RI = 0;                 //���RIλ
				res=SBUF;
				Time_UART1=0;
				if((USART_RX_STA&0x8000)==0)//����δ���
				{
					if(USART_RX_STA&0x4000)//���յ���0x0d
					{
						if(res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
						else USART_RX_STA|=0x8000;	//��������� 
					}else //��û�յ�0X0D
					{	
						if(res==0x0d)USART_RX_STA|=0x4000;
						else
						{
							Uart1_Buf[USART_RX_STA&0X3FFF]=res;
							USART_RX_STA++;
							if(USART_RX_STA>(Buf1_Max-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
						}		 
					}
				}  
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
    }
		ES=1;
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
      Time_UART2=0;
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
		if(Time_miao>=1)Time_miao++;//Time_miao==1ʱ��������������Զ�ֹͣ
	}
	if(Timer0_start)
	Times++;
	if(Times > (50*shijian))
	{
		Timer0_start = 0;
		Times = 0;
	}
	Time_UART2++;
	if(USART_RX_STA&(~0x8000))//���ڽ���״̬��
	{
		Time_UART1++;
		if(Time_UART1>=200)USART_RX_STA=0;//���ճ�ʱ����λ����
	}
	
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
/*******************************************************************************
* ������ : Timer0Init
* ����   : ��ʱ��0��ʼ��
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
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
	if(First_Int==0)First_Int=Buf2_Max;
	for(k=0;k<First_Int;k++)      //��������������
	{
		Uart2_Buf[k] = 0x00;
	}
    First_Int = 0;              //�����ַ�������ʼ�洢λ��
}

/*******************************************************************************
* ������ : sim900a_send_cmd
* ����   : ����ATָ���
* ����   : �������ݵ�ָ�롢���͵ȴ�ʱ��(��λ��S)
* ���   : 
* ����   : 0:����  1:����
* ע��   : 
*******************************************************************************/

u8 sim900a_send_cmd(u8 *cmd,u8 *ack,u8 wait_time)         
{
	u8 i,res=1;
	u8 *c;
	c = cmd;										//�����ַ�����ַ��c
	CLR_Buf2(); 
  i = 2;
	
	for (cmd; *cmd!='\0';cmd++)
	{
		UART2_SendData(*cmd);
	}
	UART2_SendLR();	
	Times = 0;
	shijian = wait_time;
	Timer0_start = 1;
	while(Timer0_start&res)                    
	{
		if(strstr(Uart2_Buf,ack)==NULL)
			 res=1;
		else
		{
			 res=0;
		}

	}
	return res;
}

//sim900a�����Գ���

/*******************************************************************************
* ������ : sim900a_test
* ����   : sim900a�����Գ���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void sim900a_test(void)
{
	u8 key=0; 
	u8 timex=0;
	u8 sim_ready=0;
	while(sim900a_send_cmd("AT","OK",5))//��ѯ�Ƿ�Ӧ��ATָ��
	{
		UART1_SendString("δ��⵽ģ��\r\n");
		delay_ms(800);
		UART1_SendString("���ڳ�������\r\n");
		delay_ms(400);  
	} 	 
	sim900a_send_cmd("ATE0","OK",200);//������
	sim900a_mtest();
	if(sim900a_gsminfo()==0)
	{
		sim_ready=1;
		UART1_SendString("��ѡ��:ѡ����Ӧ������+�س����ٷ���\r\n"); 				    	 
		UART1_SendString("����\t"); 				    	 
		UART1_SendString("����\t");				    	 
		UART1_SendString("GPRS\t");
		UART1_SendString("��λ\t");
		UART1_SendString("����\r\n");
	}
	while(1)
	{
		if(sim_ready)
		{
			if(USART_RX_STA&0x8000)
			{
				USART_RX_STA=0;
				if(strstr(Uart1_Buf,"����"))
					sim900a_call_test();	//�绰����
				else
				if(strstr(Uart1_Buf,"����"))
					sim900a_sms_test();		//���Ų���
				else
				if(strstr(Uart1_Buf,"GPRS"))
					sim900a_gprs_test();	//GPRS����
				else
				if(strstr(Uart1_Buf,"��λ"))
				  sim900a_jz_test();		//��վ����
				else
				if(strstr(Uart1_Buf,"����"))
					sim900a_tts_test();		//��������
				
				UART1_SendString("��ѡ��:ѡ����Ӧ������+�س����ٷ���\r\n"); 				    	 
				UART1_SendString("����\t"); 				    	 
				UART1_SendString("����\t");				    	 
				UART1_SendString("GPRS\t");
				UART1_SendString("��λ\t");
				UART1_SendString("����\r\n");
			}
			
		}			
	} 	
}
/*******************************************************************************
* ������ : sim900a_mtest
* ����   : SIM900A GSM/GPRS�����Կ��Ʋ���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void sim900a_mtest()
{
	u8 *p1; 
	UART1_SendString("\r\nNiRen-Elec SIM900A ���Գ���\r\n");  
	CLR_Buf2(); 
	if(sim900a_send_cmd("AT+CGMI","OK",5)==0)//��ѯ����������
	{ 
		UART1_SendString("������:");
		p1=(u8*)strstr((const char*)(Uart2_Buf+2),"\r\n");
		UART1_Send_Len(Uart2_Buf+2,p1-Uart2_Buf);
		CLR_Buf2(); 		
	} 
	if(sim900a_send_cmd("AT+CGMM","OK",5)==0)//��ѯģ������
	{ 
		UART1_SendString("ģ���ͺ�:");
		p1=(u8*)strstr((const char*)(Uart2_Buf+2),"\r\n"); 
		UART1_Send_Len(Uart2_Buf+2,p1-Uart2_Buf);
		CLR_Buf2();
	} 
	if(sim900a_send_cmd("AT+CGSN","OK",5)==0)//��ѯ��Ʒ���к�
	{ 
		UART1_SendString("��Ʒ���к�:");
		p1=(u8*)strstr((const char*)(Uart2_Buf+2),"\r\n"); 
		UART1_Send_Len(Uart2_Buf+2,p1-Uart2_Buf);
		CLR_Buf2();		
	}
	if(sim900a_send_cmd("AT+CNUM","+CNUM",5)==0)//��ѯ��������
	{ 
		UART1_SendString("��������:");
		p1=(u8*)strstr((const char*)(Uart2_Buf+2),"\r\n"); 
		UART1_Send_Len(Uart2_Buf+2,p1-Uart2_Buf);
		CLR_Buf2();		
	}
	UART1_SendLR();
}

/*******************************************************************************
* ������ : sim900a_gsminfo
* ����   : SIM900A GSM/GPRS״̬��Ϣ���(�ź�����,��ص���,����ʱ��)
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
u8 sim900a_gsminfo()
{
	u8 *p1;
	u8 *p2;
	u8 res=0;
	CLR_Buf2();
	if(sim900a_send_cmd("AT+CPIN?","OK",3))
	{
    UART1_SendString("�����ֻ����Ƿ��в���\r\n");
		res|=1<<0;	//��ѯSIM���Ƿ���λ 
	}
	CLR_Buf2(); 
	
	if(sim900a_send_cmd("AT+COPS?","OK",3)==0)		//��ѯ��Ӫ������
	{ 
		p1=(u8*)strstr((const char*)(Uart2_Buf),"\""); 
		if(p1)//����Ч����
		{
			p2=(u8*)strstr((const char*)(p1+1),"\"");				
			UART1_SendString("��Ӫ��:");
			UART1_Send_Len(p1+1,p2-p1-1);
			UART1_SendLR();
		}
	}else res|=1<<1;
	CLR_Buf2();
 
	if(sim900a_send_cmd("AT+CSQ","OK",3)==0)		//��ѯ�ź�����
	{ 
		p1=(u8*)strstr((const char*)(Uart2_Buf),":");
		if(p1)
		{
			p2=(u8*)strstr((const char*)(p1+1),",");
			UART1_SendString("�ź�����:");
			UART1_Send_Len(p1+2,p2-p1-2);
			UART1_SendLR();
		}		
	}else res|=1<<2;
	CLR_Buf2();
	
	if(sim900a_send_cmd("AT+CBC","OK",3)==0)		//��ѯ��ص���
	{ 
		p1=(u8*)strstr((const char*)(Uart2_Buf),",");
		p2=(u8*)strstr((const char*)(p1+1),",");
		UART1_SendString("��ص���:");	
		UART1_Send_Len(p1+1,2);UART1_SendString("%");
		UART1_SendString("\t");
		UART1_Send_Len(p2+1,4);UART1_SendString("mv");
		UART1_SendLR();	
	}else res|=1<<3; 
	CLR_Buf2();
	
	if(sim900a_send_cmd("AT+CCLK?","OK",3)==0)		//��ѯ��ص���
	{ 
		p1=(u8*)strstr((const char*)(Uart2_Buf),"\"");
		UART1_SendString("ʱ������:");
		UART1_Send_Len(p1+1,17);
	  UART1_SendLR();	
	}else res|=1<<4; 
	CLR_Buf2();
  if(sim900a_send_cmd("AT+DDET=1","OK",3)==0)
	{
		UART1_SendString("ģ��֧��DTMF��Ƶ���룬����ֱ��ʶ��Է�ͨ�������а��µİ���");
    UART1_SendLR();	
	}else
	{
    UART1_SendString("ģ�鲻֧��DTMF��Ƶ���룬������ʶ��Է�ͨ�������а��µİ���");
    UART1_SendLR();	
	}
	if(sim900a_send_cmd("AT+CTTS=?","OK",3)==0)
	{
		UART1_SendString("ģ��֧��TTS��������������ֱ�ӽ��ı����ų�����");
    UART1_SendLR();	
	}
	else
	{
		UART1_SendString("ģ�鲻֧��TTS��������");
    UART1_SendLR();			
	}
	if(sim900a_send_cmd("AT+CIPGSMLOC=?","OK",3)==0)
	{
		UART1_SendString("ģ��֧�ֻ�վ��λ������ֱ�ӻ�ȡ��λ��Ϣ");
    UART1_SendLR();	
	}
	else
	{
		UART1_SendString("ģ�鲻֧�ֻ�վ��λ");
    UART1_SendLR();			
	}
	return res;
}

/*******************************************************************************
* ������ : sim900a_call_test
* ����   : ���Ų��Դ���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
u8 sim900a_call_test()
{	
	u8 temp[50];
	u16 len=0;
	u16 i=0;
	u8 mode=0;
	u8 flag=0;
	u8 *p1;
	UART1_SendString("@@@@@@@@@@@���Ų���@@@@@@@@@@@\r\n");
	UART1_SendString("����绰�����롰�µ�xxxx+�س���\r\n");
	UART1_SendString("�����绰�����롰����+�س���\r\n");
  UART1_SendString("�Ҷϵ绰�����롰�Ҷ�+�س���\r\n");
	UART1_SendString("DTMF���������롰�����ַ�+�س���\r\n");
	UART1_SendString("�˳����ԣ����롰�˳�+�س���\r\n");
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0X3FFF;
			USART_RX_STA=0;
			if(strstr(Uart1_Buf,"�˳�"))return 0;
			if(strstr(Uart1_Buf,"����"))mode=1;
			else
			if(strstr(Uart1_Buf,"�Ҷ�"))mode=2;
			else
			if(strstr(Uart1_Buf,"�µ�"))mode=3;
			else
			if(mode==0)mode=0;//��Ч
			else 
			{
				mode=4;
				flag=1;
			}
		}
		switch(mode)
		{
			case 0://������
				if(strstr(Uart2_Buf,"RING"))
				{
					CLR_Buf2();
					UART1_SendString("������\r\n");
				}
				break;
			case 1:
						 if(sim900a_send_cmd("ATA","OK",2)==0)//����
						 {
							UART1_SendString("�����ɹ�\r\n");
						  mode=4; 
						 }
				break;
			case 2:if(sim900a_send_cmd("ATH","OK",2)==0)//�Ҷ�
							UART1_SendString("�Ҷϳɹ�\r\n");		
						 mode=0;
				break;
			case 3://����
						UART1_SendString("�µ�:");
						UART1_Send_Len(Uart1_Buf+4,len-4);
						strcpy(temp,"ATD");
						for(i=3;i<(len-4+3);i++)
						temp[i]=Uart1_Buf[i+1];
						temp[i++]=';';
						temp[i++]='\0';
						if(sim900a_send_cmd(temp,"OK",8)==0)
						{
							UART1_SendString("���гɹ�\r\n");
							mode=4;
						}
						else
						{
							UART1_SendString("�����º���\r\n");
						  mode=0;
						}
			  break;
			case 4://����DTMF
				if(flag)
				{
				flag=0;
				strcpy(temp,"AT+VTS=");
				temp[7]=Uart1_Buf[0];
				temp[8]='\0';
				sim900a_send_cmd(temp,"OK",3);
				}
				if(strstr(Uart2_Buf,"DTMF:"))
				{
          delay_ms(10);
					p1=(u8*)strstr((const char*)(Uart2_Buf),":");
					UART1_SendString("�Է����°�����");
					UART1_SendData(*(p1+2));
					UART1_SendLR();	
					CLR_Buf2();
				}
				break;
		}
		
	}
}

/*******************************************************************************
* ������ : sim900a_sms_test
* ����   : ���Ų��Դ���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
u8 sim900a_sms_test()
{
	u16 len=0;
	u8 mode=0;
	u8 temp[50];
	u8 *p,*p1;
	u8 loc=0;
  sim900a_send_cmd("AT+CNMI=3,1,0,0,0","OK",3);		//�����¶���ֻ�ϱ�λ��
	sim900a_send_cmd("AT+CMGF=1","OK",3);								//TEXT	
	sim900a_send_cmd("AT+CPMS=\"SM\",\"SM\",\"SM\"","OK",3);		//���в�����SIM���н���
	UART1_SendString("@@@@@@@@@@@@@@@@@@@@@@@@@���Ų���@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\r\n");
	UART1_SendString("���Ͷ��ţ��밴Ҫ������绰+����(������)���Իس�����:��137xxxx+niren-electron\r\n");
  UART1_SendString("�鿴���ţ��鿴��xx��xx������ŵĴ洢λ��\r\n");
	UART1_SendString("�˳����ԣ����롰�˳�+�س���\r\n");
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0X3FFF;
			if(len>Buf2_Max-2)len=Buf2_Max-2;
			USART_RX_STA=0;
			if(strstr(Uart1_Buf,"�˳�"))return 0;
			if(strstr(Uart1_Buf,"+"))mode=1;//���Ͷ���
			else
			if(strstr(Uart1_Buf,"�鿴"))mode=2;
			else 
			{
				mode=0;
			}
		}
		switch(mode)
		{
			case 0:
        if(strstr(Uart2_Buf,"+CMTI:"))
				{
          UART1_SendString("���¶���\r\n");
					UART1_SendString("����λ��: ");
					p=strstr(Uart2_Buf,",");
					UART1_SendString(p+1);
					CLR_Buf2();
				}
				break;
			case 1:
				Uart1_Buf[len]='\0';//��ӽ�����;
				strcpy((char*)temp,(const char *)"AT+CMGS=\"+86");
				loc=sizeof("AT+CMGS=\"+86");
				p=(char*)strstr((char*)Uart1_Buf,(char*)"+");
				Uart1_Buf[(p-Uart1_Buf)]='\0';
				strcpy((char*)(&temp[loc-1]),(const char*)Uart1_Buf);
				loc=strlen(temp);
				temp[loc]='\"';
				temp[loc+1]='\0';
				//printf("%s\n",temp);
				//printf("%s%c\n",temp,0x1a);
				sim900a_send_cmd("AT+CMGF=1","OK",2);
				sim900a_send_cmd("AT+CSCS=\"GSM\"","OK",2);
				sim900a_send_cmd(temp,">",2);
        strcpy((char*)&temp,(const char*)(p+1));
			  loc=strlen(temp);
				temp[loc]='\32';
				temp[loc+1]='\0';
			  sim900a_send_cmd(temp,"OK",10);
			  UART1_SendString("���Ͷ��ųɹ�\r\n");
        mode=0;
			break;
			case 2:
        Uart1_Buf[len]='\0';//��ӽ�����;
				p=strstr(Uart1_Buf,"��");
				strcpy((char*)temp,(const char*)"AT+CMGR=");
			  loc=strlen(temp);
				strcpy((char*)(&temp[loc]),(const char*)(p+2));
				loc=strlen(temp);
			  if(sim900a_send_cmd(temp,"OK",5)==0)
				{
					p=strstr(Uart2_Buf+2,"\r\n");
					p1=strstr(p+2,"\r\n");
					loc=p1-p;
					UART1_SendString("�������ݣ�");
					UART1_Send_Len(p+2,loc);
				}
				mode=0;
				break;
			case 3:
				break;
		}
	}
}

/*******************************************************************************
* ������ : sim900a_gprs_test
* ����   : GPRS���Դ���
* ����   : 
* ���   : 
* ����   : 
* ע��   :  Ϊ�˱������ӣ�ÿ���и�10�뷢��һ������
*******************************************************************************/
u8 sim900a_gprs_test()
{	
  u16 len=0;
	u8 mode=0;
	u8 temp[50];
	u8 flag=0;
	u8 *p1,*p2;
	UART1_SendString("@@@@@@@@@@@@@@GPRS����@@@@@@@@@@@@@@@@@@@@@\r\n");
	UART1_SendString("���ò���������\"ģʽ\",\"IP\",�˿�+�س�\r\n�磺����\"TCP\",\"125.89.18.79\",12345\r\n");
	UART1_SendString("�������ݣ�����+����+�س�\r\n�磺�������˵���\r\n");
	UART1_SendString("�˳����ԣ��˳�+�س�\r\n");
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0X3FFF;
			if(len>Buf2_Max-2)len=Buf2_Max-2;
			USART_RX_STA=0;
			if(strstr(Uart1_Buf,"�˳�"))mode=4;//�˳�
			else
			if(strstr(Uart1_Buf,"����"))mode=1;//��������
			else
			if(strstr(Uart1_Buf,"����"))mode=2;//��������
			else 												mode=0;			
		}
		else
		{
			if(strstr(Uart2_Buf,"CONNECT OK")&&(flag==1))//���ӳɹ�
			{
					UART1_SendString("���ӳɹ�\r\n");
					Time_miao=1;
					flag=2;
					mode=3;
					CLR_Buf2();
			}else
			if((flag==1)&&((strstr(Uart2_Buf,"CLOSED"))||(Time_miao>10)))//����ʧ�ܻ�ʱ
			{
					UART1_SendString("����ʧ��\r\n");
					Time_miao=0;
					flag=0;
					mode=1; //��������
					CLR_Buf2();
			}	
			if((flag==2)&&(Time_miao>10))//ÿ10��һ��������
			{
				Time_miao=1;
				mode=3;
			}
	  }
    switch(mode)
		{
			case 0:        
						if(strstr(Uart2_Buf,"+IPD")&&(Time_UART2>1))
						{
							UART1_SendString("��������\r\n");
							p1=strstr(Uart2_Buf,",");
							p2=strstr(Uart2_Buf,":");
							UART1_Send_Len(p2+1,change_str_hex((p1+1),(p2-p1-1)));
							UART1_SendLR();
							CLR_Buf2();
						}
			break;
			case 1: 
				     if(strstr(Uart1_Buf,"TCP")||strstr(Uart1_Buf,"UDP"))
						 {
                strcpy((char*)&temp,(const char*)"AT+CIPSTART=");
							  memcpy((char*)&temp[12],(const char*)(&Uart1_Buf[4]),len-4);
							  sim900a_send_cmd("AT+CIPCLOSE=1","CLOSE OK",2);	//�ر�����
								sim900a_send_cmd("AT+CIPSHUT","SHUT OK",2);		//�ر��ƶ�����
 							  sim900a_send_cmd("AT+CGCLASS=\"B\"","OK",2);//����GPRS�ƶ�̨���ΪB,֧�ְ����������ݽ��� 
								sim900a_send_cmd("AT+CGDCONT=1,\"IP\",\"CMNET\"","OK",2);//����PDP������,��������Э��,��������Ϣ
								sim900a_send_cmd("AT+CGATT=1","OK",2);//����GPRSҵ��
								sim900a_send_cmd("AT+CIPCSGP=1,\"CMNET\"","OK",2);//����ΪGPRS����ģʽ
								sim900a_send_cmd("AT+CIPHEAD=1","OK",2);//���ý���������ʾIPͷ(�����ж�������Դ,���ڵ�·������Ч)
                if(sim900a_send_cmd(temp,"OK",2 )==0)//��������
								{
                  UART1_SendString("���ڷ�������\r\n");
									Time_miao=1;
									flag=1;
								}
								else
								{
									UART1_SendString("�������������\r\n");
									Time_miao=0;
									flag=0;
								}
						 }
						 else
						 {
							  UART1_SendString("�������������\r\n");
						 }
             mode=0;
			break;
			case 2:
              if(flag==2)
							{
                UART1_SendString("��ʼ����...........\r\n");
								if(sim900a_send_cmd("AT+CIPSEND",">",2)==0)
								{
										 Uart1_Buf[len]='\32';
										 Uart1_Buf[len+1]='\0';
										 if(sim900a_send_cmd(&Uart1_Buf[4],"SEND OK",8)==0)
										 { 								
													UART1_SendString("���ͳɹ�\r\n");
													Time_miao=1;
										 }
										 else
											 UART1_SendString("����ʧ��\r\n");
										 
								}else
								{
										 UART2_SendData(0X1B);//ESC,ȡ������
                     UART1_SendString("����ʧ��\r\n");
								}
						  }else UART1_SendString("��û����\r\n");
							mode=0;
			break;
			case 3:
						if(sim900a_send_cmd("AT+CIPSEND",">",2)==0)
						{
							UART2_SendData(0x00);
							UART2_SendData(0X1A);//CTRL+Z,�������ݷ���,����һ�δ���								
							UART1_SendString("�����ɹ�\r\n");

								 
						}else
						{
								 UART2_SendData(0X1B);//ESC,ȡ������
				         UART1_SendString("����ʧ��\r\n");
						}
				mode=0;
			break;
			case 4:
						sim900a_send_cmd("AT+CIPCLOSE=1","CLOSE OK",5);	//�ر�����
						sim900a_send_cmd("AT+CIPSHUT","SHUT OK",5);		//�ر��ƶ�����
						return 1;
			break;
		}      
	}
}
u8 change_str_hex(u8 *p,u8 len)
{
  u8 i=0;
	u8 value=0;
	for(i=0;i<len;i++)
	{
    value=value*10;
		value+=(*(p++)-'0');
	}
	return value;
}

/*******************************************************************************
* ������ : sim900a_JZ_test
* ����   : ��վ��λ���Դ���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
u8 sim900a_jz_test()
{
  u8 *p1,*p2,*p3;
	UART1_SendString("@@@@@@@@@@@@@@@@@@@@@��վ��λ����@@@@@@@@@@@@@@@@@@@@@@@@@\r\n");
	UART1_SendString("�˳����ԣ��˳�+�س�\r\n");
	sim900a_send_cmd("AT+SAPBR=3,1,\"Contype\",\"GPRS\"","OK",2);
	sim900a_send_cmd("AT+SAPBR=3,1,\"APN\",\"CMNET\"","OK",2);
  if(sim900a_send_cmd("AT+SAPBR=1,1","OK",5))//����
	{
	
		UART1_SendString("��ʧ�ܣ���ȷ��ģ���Ƿ��иù���\r\n");
		return 1;		
	}
	if(sim900a_send_cmd("AT+SAPBR=2,1","OK",5))
	{
    UART1_SendString("��ȡ����IP����\r\n");
		return 2;
	}
  Time_miao=1;
	while(1)
	{
    if(USART_RX_STA&0x8000)
		{
			USART_RX_STA=0;
			if(strstr(Uart1_Buf,"�˳�"))//�˳�
			{
				 sim900a_send_cmd("AT+SAPBR=0,1","OK",2);//�ر�
				 return 0;
			}
			else
			UART1_SendString("�������\r\n");
		}
    if(sim900a_send_cmd("AT+CIPGSMLOC=1,1","OK",10)==0)//��ȡ��γ�Ⱥ�ʱ��
		{
        Time_miao=1;
 			  p1=(u8*)strstr((const char*)(Uart2_Buf),",");
				p3=(u8*)strstr(p1,"\r\n");
				if(p1)//��Ч����
				{	
					p2=(u8*)strtok((char*)(p1),",");
          UART1_SendString("����:");UART1_SendString(p2);UART1_SendData('\t');
					
					p2=(u8*)strtok(NULL,",");
          UART1_SendString("γ��:");UART1_SendString(p2);UART1_SendData('\t');
					
					p2=(u8*)strtok(NULL,",");
          UART1_SendString("����:");UART1_SendString(p2);UART1_SendData('\t');
					
					p2=(u8*)strtok(NULL,",");
					*p3='\0';//���������
          UART1_SendString("ʱ��:");UART1_SendString(p2);UART1_SendLR();
				}
		}
		if(Time_miao>11)
		{
      Time_miao=0;
			//sim900a_send_cmd("AT+SAPBR=0,1","OK",2);//�ر�
			UART1_SendString("��ʧ�ܣ���ȷ��ģ���Ƿ��иù���\r\n");
			return 1;
		}
	}
}
/*******************************************************************************
* ������ : sim900a_tts_test
* ����   : TTS�ı��������Դ���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
u8 sim900a_tts_test()
{
  u16 len=0;
	UART1_SendString("@@@@@@@@@@@@@@@@@@@@@TTS�ı���������@@@@@@@@@@@@@@@@@@@@@@@\r\n");
	UART1_SendString("�˳����ԣ��˳�+�س�\r\n");
	UART1_SendString("ֱ����������+�س��������Խ�����ͨ���������ų���\r\n");
  UART1_SendString("ע�⣺���֧��190���ֽ�\r\n");
	if(sim900a_send_cmd("AT+CTTS=?","OK",2))
	{
		 UART1_SendString("�������ѯģ���Ƿ�߱��ù���\r\n");
		 return 1;
	}
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
      len=USART_RX_STA&0X3FFF;
			if(len>(Buf2_Max-2))len=(Buf2_Max-2);
      USART_RX_STA=0;
			if((len==4)&&(strstr(Uart1_Buf,"�˳�")))//�˳�	
			return 0;
			UART2_SendData('A');
			UART2_SendData('T');
			UART2_SendData('+');
			UART2_SendData('C');
			UART2_SendData('T');
			UART2_SendData('T');
			UART2_SendData('S');
			UART2_SendData('=');
			UART2_SendData('2');
			UART2_SendData(',');
			UART2_SendData('\"');
			Uart1_Buf[len]='\"';
			Uart1_Buf[len+1]='\0';
			if(sim900a_send_cmd(Uart1_Buf,"OK",2))
				UART1_SendString("�ȴ���һ֡���ݲ������\r\n");
		}
	}
}

