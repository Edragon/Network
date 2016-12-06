/**********************************************************************************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����         

 * Ӳ�����ӣ�  PB5 -> LED1     
 *             PB6 -> LED2     
 *             PB7 -> LED3    
 *             PB8 -> LED3    
 * ��汾  ��ST_v3.5
**********************************************************************************/

#include "Led.h"
	   
/*******************************************************************************
* ������  : GPIO_Config
* ����    : LED ��PWR_MG323 IO����
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : LED(1~4)��IO�ڷֱ���:PB5,PB6,PB7,PB8  PWR_MG323:PB9
*******************************************************************************/
void GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;				//����һ��GPIO_InitTypeDef���͵�GPIO��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(LED_RCC, ENABLE);			//ʹ��GPIOB������ʱ��	
	
	GPIO_InitStructure.GPIO_Pin = LED_ALL;	//ѡ��Ҫ��ʼ����GPIOB����(PB5,PB6,PB7,PB8,PB9)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������Ź���ģʽΪͨ��������� 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//������������������Ϊ50MHz
	GPIO_Init(LED_PORT, &GPIO_InitStructure);			//���ÿ⺯���е�GPIO��ʼ����������ʼ��GPIOB�е�PB5,PB6,PB7,PB8,PB9����

	LED_ALL_OFF();										//�ر�ALL_LED  					 
}

/*����LED1.PB5*/
void LED1_ON(void) 
{
	GPIO_SetBits(LED_PORT,LED1);
}

/*�ر�LED1.PB5*/
void LED1_OFF(void)
{
	GPIO_ResetBits(LED_PORT,LED1);
}

/*����LED2.PB6*/
void LED2_ON(void)  
{
	GPIO_SetBits(LED_PORT,LED2);
}

/*�ر�LED2.PB6*/
void LED2_OFF(void)
{
	GPIO_ResetBits(LED_PORT,LED2);
}

/*����LED3.PB7*/
void LED3_ON(void)   
{
	GPIO_SetBits(LED_PORT,LED3);
}

/*�ر�LED3.PB7*/
void LED3_OFF(void)  
{
	GPIO_ResetBits(LED_PORT,LED3); 
}

/*����LED4.PB8*/
void LED4_ON(void) 
{
	GPIO_SetBits(LED_PORT,LED4);
}

/*�ر�LED4.PB8*/
void LED4_OFF(void) 
{
	GPIO_ResetBits(LED_PORT,LED4); 
}

/*����ALL_LED*/
void LED_ALL_ON(void)
{
	GPIO_SetBits(LED_PORT,LED_ALL);
}
/*�ر�ALL_LED*/
void LED_ALL_OFF(void)  
{
	GPIO_ResetBits(LED_PORT,LED_ALL); 
}

