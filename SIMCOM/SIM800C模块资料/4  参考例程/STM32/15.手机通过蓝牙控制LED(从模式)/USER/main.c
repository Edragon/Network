/**********************************************************************************
 * ������  :�������ܲ��Գ���
 * ����    :ͨ��STM32�����崮��2����ģ����������������ӹ��̷��͵�����1�������ֻ�
						��������SPP���Ӻ󣬻ᶨʱ���͹̶����ݸ��ֻ��������ڣ��ֻ��������͵�����
						���Զ�ת��������1��
						���г���ǰ�������ȴ��������׵��ֻ������������֡�
 * ʵ��ƽ̨:STM32F10X
 * ��汾  :


 * Ӳ������˵��
	 ʹ�õ�Ƭ����2��GPRSģ��ͨ��  ע��ʹ�ô���2���Ա������غ�ͨ�Ų����ͻ
	 STM32      GPRSģ��
	 PA3 (RXD2)->RXD
	 PA2 (TXD2)->TXD
	 GND	      ->GND

 * �������˵��
   ���������׵��ֻ�APP���л�ģʽ�����վģʽ��ͨ��������1���͡�����2���Ϳ��Կ���LED������
**********************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "Led.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"

#define Buf2_Max 200 					  //����2���泤��
/*************	���س�������	**************/
const char *sendtable="Niren-elec Bluetooth test\r\n\32";
/*************  ���ر�������	**************/

char Uart2_Buf[Buf2_Max]; //����2���ջ���

char *p1,*p2; 

vu8 Times=0,First_Int = 0,shijian=0;

vu8 Timer0_start;	//��ʱ��0��ʱ����������

vu8 Timer_send;//��ʱ���ͼ�ʱ��


/*************	���غ�������	**************/
void System_Initialization(void); //STM32ϵͳ��ʼ��
void Ram_Initialization(void);    //�ڴ������ʼ��
void NVIC_Configuration(void);    //�ж��������ʼ��
void CLR_Buf2(void);              //�崮��2���ջ���
u8 Find(char *a);                 //�����ַ���
void Second_AT_Command(char *b,char *a,u8 wait_time);  //����ATָ��



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
int main(void)
{
	System_Initialization(); //ϵͳ��ʼ��
	Ram_Initialization();    //������ʼ��
    LED4_OFF();
    
	UART1_SendString("SIM800ģ���������Գ���\r\n");
	UART1_SendString("����ֻ�������������\r\n");
	UART1_SendString("SIM800ģ�����������\r\n");
    Second_AT_Command("ATE1\r\n","AT",2);//�򿪻���
	Second_AT_Command("AT+BTPOWER=1\r\n","AT",2);//��������Դ,������ж�OK����Ϊ��Դԭ�������ٷ��ʹ򿪵Ļ��᷵�ش���
	Delay_nMs(100); 
	UART1_SendString("�ȴ��ֻ�APP����ģ��\r\n");
    while(1)
    {
        if(strstr((const char*)Uart2_Buf,"BTPAIRING")!=NULL)//�������
        {
            CLR_Buf2();
            Second_AT_Command("AT+BTPAIR=1,1\r\n","OK",3);//�����ֻ����
            while(strstr((const char*)Uart2_Buf,"BTCONNECTING")==NULL);   //�ȴ����ģ��  
            break;
        }else
        if(strstr((const char*)Uart2_Buf,"BTCONNECTING")!=NULL)//��������
        {
            break;
        }
    }    
	Second_AT_Command("AT+BTACPT=1\r\n","OK",3);//��Ӧ����
	UART1_SendString("SIM800ģ����������SPP����ɹ�\r\n");
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
                    if(*(p1+4)==(char)0xB1)//�ֻ�APP ������1
					{
						LED4_ON();
					}
					if(*(p1+4)==(char)0xB2)//������2
					{
						LED4_OFF();
					}
					CLR_Buf2(); 
				}
		}else
		if(Timer_send>5)//����ʱ��ʱ��������
		{	
			Second_AT_Command("AT+BTSPPSEND",">",1);
			Second_AT_Command((char *)sendtable,"OK",1);
			Timer_send=0;
		}
		
	}
	
	
}

/*******************************************************************************
* ������  : System_Initialization
* ����    : STM32ϵͳ��ʼ������(��ʼ��STM32ʱ�Ӽ�����)
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void System_Initialization(void)
{
	RCC_Configuration();		//����ϵͳʱ��Ϊ72MHZ(������Ը�����Ҫ��)
  SysTick_Init_Config();  //��ʼ��ϵͳ�δ�ʱ��SysTick
  NVIC_Configuration();		//STM32�ж�������������
	Timer2_Init_Config();		//��ʱ��2��ʼ������
	USART1_Init_Config(115200);	//����1��ʼ������
	USART2_Init_Config(115200);	//����2��ʼ������	
	GPIO_Config();          //��ʼ��GPIO
}
/*******************************************************************************
* ������  : Ram_Initialization
* ����    : ������ʼ������
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Ram_Initialization(void)
{
	Times=0;
	shijian=0;
	Timer0_start=0;
	Timer_send=0;
}

/*******************************************************************************
* ������  : NVIC_Configuration
* ����    : STM32�ж�������������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ����KEY1(PC11)���ж�������
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;						//����NVIC��ʼ���ṹ��

  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				    //�����ж����ȼ���Ϊ2����ռ���ȼ��ʹ����ȼ�����λ(����0��3)
	
	/*��ʱ��2�ж���������*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				    //�����ж�������
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//�����������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			  //������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				    //ʹ��NVIC
	NVIC_Init(&NVIC_InitStructure);
	/*����1�ж���������*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;				  //�����ж�������
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//�����������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			  //������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				    //ʹ��NVIC
	NVIC_Init(&NVIC_InitStructure);
  /*����2�ж���������*/
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;				  //�����ж�������
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//�����������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			  //������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				    //ʹ��NVIC
	NVIC_Init(&NVIC_InitStructure);
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
		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�����ж�
		{
			Res =USART_ReceiveData(USART2);
			Uart2_Buf[First_Int] = Res;  	  //�����յ����ַ����浽������
			First_Int++;                			//����ָ������ƶ�
			if(First_Int > Buf2_Max)       		//���������,������ָ��ָ�򻺴���׵�ַ
			{
				First_Int = 0;
			} 
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
void TIM2_IRQHandler(void)   //TIM2�ж�
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
			//LED4_ON(); 
			flag=0;
		}
		else
		{
			//LED4_OFF(); 
			flag=1;
		}
		Timer_send++;
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
	First_Int=0;
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

void Second_AT_Command(char *b,char *a,u8 wait_time)         
{
	u8 i;
	char *c;
	c = b;										//�����ַ�����ַ��c
	CLR_Buf2(); 
  i = 0;
	while(i == 0)                    
	{
		if(!Find(a)) 
		{
			if(Timer0_start == 0)
			{
				CLR_Buf2(); 
				//UART1_SendString(b);
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
	//UART1_SendString(Uart2_Buf); 
}

