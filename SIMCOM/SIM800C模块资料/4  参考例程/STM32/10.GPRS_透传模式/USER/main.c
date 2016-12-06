/**********************************************************************************
 * ������  :GPRS_͸��ģʽ
 * ����    :ͨ��STM32���������ģ�����͸��ģʽ�������Ϸ��������յ������������ݷ��ظ�������
 * ʵ��ƽ̨:STM32F10X
 * ��汾  :


 * Ӳ������˵��
	 ʹ�õ�Ƭ����2��GPRSģ��ͨ��  ע��ʹ�ô���2���Ա������غ�ͨ�Ų����ͻ
	 STM32      GPRSģ��
	 PA3 (RXD2)->RXD
	 PA2 (TXD2)->TXD
	 GND	      ->GND

 * �������˵��
   �����ϵ������ָʾ��RUNING_LED����һ���Ƶ����˸
	 �����Ϸ��������յ������������ݷ��ظ�������
**********************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "Led.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"

#define Buf2_Max 200 					  //����2���泤��
/*************	���س�������	**************/
const char *string = "AT+CIPSTART=\"TCP\",\"14.125.48.205\",9015";//IP��¼������,��Ҫ�����Լ���IP�Ͷ˿����޸�

/*************  ���ر�������	**************/

char Uart2_Buf[Buf2_Max]; //����2���ջ���
char *p1,*p2;             
u8 Times=0,shijian=0;

vu8 Timer0_start;	//��ʱ��0��ʱ����������

/*************	���غ�������	**************/
void System_Initialization(void); //STM32ϵͳ��ʼ��
void Ram_Initialization(void);    //�ڴ������ʼ��
void NVIC_Configuration(void);    //�ж��������ʼ��
void CLR_Buf2(void);              //�崮��2���ջ���
u8 Find(char *a);                 //�����ַ���
void Second_AT_Command(char *b,char *a,u8 wait_time);  //����ATָ��
void Wait_CREG(void);                          //��ѯ�ȴ�ģ��ע��ɹ�
void Set_ATE0(void);                           //ȡ������
void Connect_Server(void);                     //����GPRS���Ӳ�����������͸��ģʽ
void Rec_Server_Data(void);                    //���շ��������ݲ�����


/*************  �ⲿ�����ͱ�������*****************/




/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : ����2������MG323ģ��ͨ�ţ�����1���ڴ��ڵ��ԣ����Ա��������س���ʱ����
					 �����͵�ģ��
*******************************************************************************/
int main(void)
{
	System_Initialization(); //ϵͳ��ʼ��
	Ram_Initialization();    //������ʼ��

	UART1_SendString("GPRSģ��GPRS���Գ���\r\n");
	UART1_SendString("GPRSģ����ע������\r\n");
	Delay_nS(1); 
	UART2_SendString("+++");//�˳�͸��ģʽ������ģ�黹����͸��ģʽ��
  Delay_nS(2);
	Wait_CREG();   //�ȴ�ģ��ע��ɹ�
	UART1_SendString("GPRSģ��ע��ɹ�\r\n");
	UART1_SendString("GPRSģ�鿪ʼ���ӷ�����\r\n");
	Set_ATE0();    //ȡ������
	Connect_Server(); //����GPRS����
	UART1_SendString("���ӳɹ�\r\n");

	while(1)
	{
		Rec_Server_Data();//�������ݲ�ԭ������	
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
	p1=Uart2_Buf;
	p2=p1;
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
      if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
			{
			Res=USART_ReceiveData(USART2);
			*p1 = Res;  	  //�����յ����ַ����浽������
			p1++;                			//����ָ������ƶ�
			if(p1>&Uart2_Buf[Buf2_Max])       		//���������,������ָ��ָ�򻺴���׵�ַ
			{
				p1=Uart2_Buf;
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
  p1=Uart2_Buf;               //�����ַ�������ʼ�洢λ��
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
  while(i == 0)        			
	{
		CLR_Buf2();        
		UART2_SendString("AT+CREG?");   //��ѯ�ȴ�ģ��ע��ɹ�
		UART2_SendLR();
		Delay_nMs(5000);  						
	    for(k=0;k<Buf2_Max;k++)      			
    	{
			if(Uart2_Buf[k] == ':')
			{
				if((Uart2_Buf[k+4] == '1')||(Uart2_Buf[k+4] == '5'))   //˵��ע��ɹ�
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

/*******************************************************************************
* ������ : Set_ATE0
* ����   : ȡ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Set_ATE0(void)
{
	Second_AT_Command("ATE0","OK",3);								//ȡ������		
}
/*******************************************************************************
* ������ : Connect_Server
* ����   : GPRS���ӷ���������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Connect_Server(void)
{
	UART2_SendString("AT+CIPCLOSE=1");	//�ر�����
  Delay_nMs(100);
	Second_AT_Command("AT+CIPSHUT","SHUT OK",2);		//�ر��ƶ�����
	Second_AT_Command("AT+CGCLASS=\"B\"","OK",2);//����GPRS�ƶ�̨���ΪB,֧�ְ����������ݽ��� 
	Second_AT_Command("AT+CGDCONT=1,\"IP\",\"CMNET\"","OK",2);//����PDP������,��������Э��,��������Ϣ
	Second_AT_Command("AT+CGATT=1","OK",2);//����GPRSҵ��
	Second_AT_Command("AT+CIPCSGP=1,\"CMNET\"","OK",2);//����ΪGPRS����ģʽ
  Second_AT_Command("AT+CIPMUX=0","OK",2);//����Ϊ��·����
	Second_AT_Command("AT+CIPHEAD=1","OK",2);//���ý���������ʾIPͷ(�����ж�������Դ,���ڵ�·������Ч)
	Second_AT_Command("AT+CIPMODE=1","OK",2);//��͸������
	Second_AT_Command("AT+CIPCCFG=4,5,200,1","OK",2);//����͸��ģʽ�������ط�����:2,���1S����һ��,ÿ�η���200���ֽ�
  Second_AT_Command((char*)string,"OK",5);//��������
  
  Delay_nMs(100);                                //�ȴ��������ݽ������
  CLR_Buf2();                                    //�崮�ڽ��ջ���Ϊ͸��ģʽ׼��
}
/*******************************************************************************
* ������ : Rec_Server_Data
* ����   : ���շ��������ݺ���,��ԭ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Rec_Server_Data(void)
{
	if(p2!=p1)   		//˵����������δ����
	{	
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
		USART_SendData(USART2,*p2);
		p2++;
    if(p2>&Uart2_Buf[Buf2_Max])
			p2=Uart2_Buf;
	}
}
