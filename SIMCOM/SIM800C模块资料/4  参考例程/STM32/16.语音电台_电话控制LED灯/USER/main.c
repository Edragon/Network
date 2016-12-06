/**********************************************************************************
 * ������  :
 * ����    :ͨ���ֻ�ͨ������LED
 * ʵ��ƽ̨:STM32F10X
 * ��汾  :

**********************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "Led.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"

#define Automatic_Startup 1     //���������� V1.2�汾��������������

//#define Buf1_Max 60 					  //����1���泤��
#define Buf2_Max 200 					  //����2���泤��
/*************	���س�������	**************/


/*************  ���ر�������	**************/
//char Uart1_Buf[Buf1_Max];
char Uart2_Buf[Buf2_Max];

u8 Times=0,First_Int = 0,shijian=0;

vu8 Timer0_start;	//��ʱ��0��ʱ����������
vu8 Uart2_Start;	//����2��ʼ��������
vu8 Uart2_End;	  //����2�������ݽ���


/*************	���غ�������	**************/
void CLR_Buf2(void);
u8 Find(char *a);
void Second_AT_Command(char *b,u8 wait_time);
void Set_TTS_Mode(void);
void Check_New_Message(void);
void Wait_CREG(void);

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
int main(void)
{
	SysTick_Init_Config();
	GPIO_Config();
	
	USART1_Init_Config(115200);
	USART2_Init_Config(115200);
	Timer2_Init_Config();
	UART1_SendString("GPRSģ������̨����\r\n");
	UART1_SendString("GPRSģ����ע������\r\n");
	Wait_CREG();
	UART1_SendString("GPRSģ��ע��ɹ�\r\n");
	UART1_SendString("GPRSģ��TTS��DTMF����\r\n");
	Set_TTS_Mode();
	UART1_SendString("���óɹ�\r\n");
	//Second_AT_Command("AT+CMGD=1,4",3);//ɾ���������ж���
	
	UART1_SendString("��ʼ�����\r\n");
	while(1)
	{
		Check_New_Message();
	}
}

/*******************************************************************************
* ������  : USART2_IRQHandler
* ����    : ����1�жϷ������
* ����    : ��
* ����    : �� 
* ˵��    : 
*******************************************************************************/
void USART2_IRQHandler(void)                	
{
			u8 Res=0;
			Res =USART_ReceiveData(USART2);
			Uart2_Buf[First_Int] = Res;  	  //�����յ����ַ����浽������
			First_Int++;                			//����ָ������ƶ�
			if(First_Int > Buf2_Max)       		//���������,������ָ��ָ�򻺴���׵�ַ
			{
				First_Int = 0;
			}    
} 	

/*******************************************************************************
* ������  : TIM2_IRQHandler
* ����    : ��ʱ��2�ж϶Ϸ�����
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void TIM2_IRQHandler(void)   //TIM3�ж�
{
	static u8 flag =1;

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		
		if(Timer0_start)
		Times++;
		if(Times > shijian)
		{
			Timer0_start = 0;
			Times = 0;
		}
	
		if(flag)
		{
			LED4_ON(); 
			flag=0;
		}
		else
		{
			LED4_OFF(); 
			flag=1;
		}
	}	
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

u8 Find(char *a)
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

void Second_AT_Command(char *b,u8 wait_time)         
{
	u8 i;
	char *c;
	c = b;										//�����ַ�����ַ��c
	CLR_Buf2(); 
  i = 0;
	while(i == 0)                    
	{
		if(!Find("OK")) 
		{
			if(Timer0_start == 0)
			{
				b = c;							//���ַ�����ַ��b
				for (; *b!='\0';b++)
				{
					while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
					USART_SendData(USART2,*b);//UART2_SendData(*b);
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
	CLR_Buf2(); 
}

/*******************************************************************************
* ������ : Set_TTS_Mode
* ����   : ����TTS��DTMFģʽ
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Set_TTS_Mode(void)
{
	Second_AT_Command("ATE0",3);										//ȡ������	
	Second_AT_Command("AT+CTTSPARAM=100,0,50,50,1",3);				    //����TTS����
	Second_AT_Command("AT+DDET=1",3);								    //��DTMF����
    //Second_AT_Command("ATS0=1",3);                                      //�����Զ�����
}

/*******************************************************************************
* ������ : Check_Message_rec
* ����   : ����Ƿ�������Ϣ����ִ����Ϣ����ָ��
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/

void Check_New_Message(void)
{
    static u8 Ring_flag=0;//�����־
    
    if(Ring_flag==0)
    {
        if(strstr(Uart2_Buf,"RING")!=NULL)   		//�������ַ����к���"+CMT"�ͱ�ʾ���µĶ���
        {
            Second_AT_Command("ATA",3);             //�����绰
            UART1_SendString("������\r\n");
            Ring_flag=1;
            Second_AT_Command("AT+CTTS=2,\"��ӭʹ�����˵����������Գ���\"",3); //������������
            CLR_Buf2();
        }
    }else
    {
        if(strstr(Uart2_Buf,"+DTMF:")!=NULL)   		//�а�������
        {
            UART1_SendString("�а�������\r\n");
            if(strstr(Uart2_Buf,"1")!=NULL)//�򿪵�һ·
            {
                LED1_ON();
                Second_AT_Command("AT+CTTS=2,\"�򿪵�һ·\"",3); //������������
                UART1_SendString("�򿪵�һ·\r\n");
            }else
            if(strstr(Uart2_Buf,"2")!=NULL)//�رյ�һ·
            {
                LED1_OFF();
                Second_AT_Command("AT+CTTS=2,\"�رյ�һ·\"",3); //������������
                UART1_SendString("�رյ�һ·\r\n");
            }else
            if(strstr(Uart2_Buf,"3")!=NULL)//�򿪵ڶ�·
            {
                LED2_ON();
                Second_AT_Command("AT+CTTS=2,\"�򿪵ڶ�·\"",3); //������������
                UART1_SendString("�򿪵ڶ�·\r\n");
            }else
            if(strstr(Uart2_Buf,"4")!=NULL)//�رյڶ�·
            {
                LED2_OFF();
                Second_AT_Command("AT+CTTS=2,\"�رյڶ�·\"",3); //������������
                UART1_SendString("�رյڶ�·\r\n");
            }
            CLR_Buf2();
        }else
        if(strstr(Uart2_Buf,"NO CARRIER")!=NULL)
        {
            UART1_SendString("�Ҷ�\r\n");
            Ring_flag=0;
            CLR_Buf2();
        }
    }
        

    
}

/*******************************************************************************
* ������ : Wait_CREG
* ����   : �ȴ�ģ��ע��ɹ�
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Wait_CREG(void)
{
	u8 i;
	u8 k;
	i = 0;
	CLR_Buf2();
  while(i == 0)        			
	{
		CLR_Buf2();        
		UART2_SendString("AT+CREG?");
		UART2_SendLR();
		Delay_nMs(5000);  						
	    for(k=0;k<Buf2_Max;k++)      			
    	{
			if(Uart2_Buf[k] == ':')
			{
				if((Uart2_Buf[k+4] == '1')||(Uart2_Buf[k+4] == '5'))
				{
					i = 1;
					UART1_SendLR();
				  break;
				}
			}
		}
		UART1_SendString("ע����.....");
	}
}
