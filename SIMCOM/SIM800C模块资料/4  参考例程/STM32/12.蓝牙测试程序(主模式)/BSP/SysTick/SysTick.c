/**********************************************************************************
 * �ļ���  ��SysTick.c
 * ����    ��ͨ��ϵͳ�δ�ʱ��SysTick�ж�ʵ��nMs(n����)��nS(n��)����ʱ        
 * ʵ��ƽ̨��NiRen_TwoHeartϵͳ��
 * Ӳ�����ӣ�������ӵ�·       
 * ��汾  ��ST_v3.5
**********************************************************************************/

#include "SysTick.h"

static u32 SysTickDelayTime;

/*******************************************************************************
* ������  : SysTick_Init_Config
* ����    : ��ʼ��ϵͳ�δ�ʱ��SysTick
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : 1)��SystemFrequency / 1000		1ms�ж�һ��
*			2)��SystemFrequency / 100000	10us�ж�һ��
*			3)��SystemFrequency / 1000000	1us�ж�һ��
*			���㷽��:(SystemFrequency / Value)��ϵͳʱ�ӽ����ж�һ��
*******************************************************************************/
void SysTick_Init_Config(void)
{

	while(SysTick_Config(SystemCoreClock / 1000));	//��ʼ����ʹ��ϵͳ�δ�ʱ��,����1��ʾ��������̫��			 
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;		  //ʧ�ܵδ�ʱ�� 
}

/*******************************************************************************
* ������  : Delay_nMs
* ����    : ��ʱ����(n����)
* ����    : nm����ʱʱ��(n����)
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Delay_nMs(u32 nms)
{ 
	SysTickDelayTime = nms;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	//ʹ�ܵδ�ʱ�� 
	while(SysTickDelayTime != 0);					//�ȴ���ʱʱ�䵽
}

/*******************************************************************************
* ������  : Delay_S
* ����    : ��ʱ����(n��)
* ����    : nS����ʱʱ��(n��)
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Delay_nS(u32 ns)
{ 
	SysTickDelayTime = ns*1000;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	//ʹ�ܵδ�ʱ�� 
	while(SysTickDelayTime != 0);					//�ȴ���ʱʱ�䵽
}


/*******************************************************************************
* ������  : SysTickDelayTime_Counter
* ����    : ��ȡ���ĳ���
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : ��SysTick�жϳ���SysTick_Handler()����(stm32f10x_it.c)
*******************************************************************************/ 
void SysTickDelayTime_Counter(void)
{
	if (SysTickDelayTime > 0)
	{ 
		SysTickDelayTime--;
	}
}

/*******************************************************************************
* ������  : RCC_Configuration
* ����    : ����ϵͳʱ��Ϊ72MHZ(������Ը�����Ҫ��)
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : STM32F107x��STM32F105xϵ��MCU��STM32F103xϵ��MCUʱ������������ͬ
*******************************************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;               //�ⲿ����ʱ��(HSE)�Ĺ���״̬����
  
  RCC_DeInit();                               //��������ʱ����صļĴ�������ΪĬ��ֵ
  RCC_HSEConfig(RCC_HSE_ON);                  //�����ⲿ����ʱ��HSE 
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); //�ȴ��ⲿ����ʱ��(HSE)�ȶ�

  if(SUCCESS == HSEStartUpStatus)             //����ⲿ����ʱ���Ѿ��ȶ�
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //Flash����
    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    
  
    RCC_HCLKConfig(RCC_SYSCLK_Div1); //����AHBʱ�ӵ���ϵͳʱ��(1��Ƶ)/72MHZ
    RCC_PCLK2Config(RCC_HCLK_Div1);  //����APB2ʱ�Ӻ�HCLKʱ�����/72MHz(���Ϊ72MHz)
    RCC_PCLK1Config(RCC_HCLK_Div2);  //����APB1ʱ����HCLKʱ�ӵ�2��Ƶ/36MHz(���Ϊ36MHz)
  
#ifndef STM32F10X_CL                 //���ʹ�õĲ���STM32F107x��STM32F105xϵ��MCU,PLL��������  
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); //PLLCLK = 8MHz * 9 = 72 MHz 
#else                                //���ʹ�õ���STM32F107x��STM32F105xϵ��MCU,PLL��������
    /***** ����PLLx *****/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);

    RCC_PLL2Cmd(ENABLE); //ʹ��PLL2 
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET);//�ȴ�PLL2�ȶ�

    /* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#endif

    RCC_PLLCmd(ENABLE); //ʹ��PLL
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); //�ȴ�PLL�ȶ�

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);          //����ϵͳʱ�ӵ�ʱ��ԴΪPLL

    while(RCC_GetSYSCLKSource() != 0x08);               //���ϵͳ��ʱ��Դ�Ƿ���PLL
    RCC_ClockSecuritySystemCmd(ENABLE);                 //ʹ��ϵͳ��ȫʱ�� 

	/* Enable peripheral clocks --------------------------------------------------*/
  	/* Enable I2C1 and I2C1 clock */
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  	/* Enable GPIOA GPIOB SPI1 and USART1 clocks */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB
					| RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD
					| RCC_APB2Periph_AFIO, ENABLE);    
  }
}
