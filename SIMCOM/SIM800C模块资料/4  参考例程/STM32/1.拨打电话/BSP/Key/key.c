/**********************************************************************************
 * �ļ���  ��key.c
 * ����    ������ɨ��(ϵͳ�δ�ʱ��SysTickʵ��ɨ����ʱ)
 * ʵ��ƽ̨��NiRen_TwoHeartϵͳ��
 * Ӳ�����ӣ�  PC10 -> KEY1     
 *             PC11 -> KEY2       
 * ��汾  ��ST_v3.5
**********************************************************************************/

#include "key.h" 
#include "SysTick.h"

/*******************************************************************************
* ������  : Key_GPIO_Config
* ����    : KEY IO����
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : KEY(1~2)��IO�ڷֱ���:PC10,PC11
*******************************************************************************/
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;				//����һ��GPIO_InitTypeDef���͵�GPIO��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);			//ʹ��GPIOA������ʱ��	
	
	GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2;			//ѡ��Ҫ��ʼ����GPIOA����(PA15,PA14)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//�������Ź���ģʽΪ�������� 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//������������������Ϊ50MHz
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);			//���ÿ⺯���е�GPIO��ʼ����������ʼ��GPIOA�е�PA15,PA14����
}

/*******************************************************************************
* ������  : Key_Detection
* ����    : �������¼��
* ����    : GPIOx��������Ӧ��GPIO��GPIO_Pin����Ӧ�����˿�
* ���    : ��
* ����    : KEY_DOWN(0):��Ӧ�������£�KEY_UP(1):��Ӧ����û����
* ˵��    : KEY(1~2)��IO�ڷֱ���:PC10,PC11
*******************************************************************************/
u8 Key_Down_Detection(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{			
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_DOWN)	//����Ƿ��а������� 
	{	   
		Delay_nMs(10);	//��ʱ����		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_DOWN)	//����Ƿ��а�������   
		{	 
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_DOWN);	//�ȴ������ͷ�  
			return KEY_DOWN;	 
		}
		else
		{
			return KEY_UP;
		}
	}
	else
	{
		return KEY_UP;
	}
}

/*******************************************************************************
* ������  : Key_Down_Scan
* ����    : ��������ɨ��
* ����    : ��
* ���    : 0��û�а������£�1����������
* ����    : �� 
* ˵��    : KEY(1~2)��IO�ڷֱ���:PC10,PC11
*******************************************************************************/
u8 Key_Down_Scan(void)
{
	u16 downflag=0;
	u8 value=0;

  	downflag=GPIO_ReadInputData(KEY_PORT);
	if((downflag & 0x0c00) != 0x0c00)	//����Ƿ��а������� 
	{	   
		Delay_nMs(10);	//��ʱ����	
		downflag = GPIO_ReadInputData(KEY_PORT) & 0x0c00;	
		if(downflag != 0x0c00 )	//����Ƿ��а�������   
		{	 
			if((downflag & 0x0400) == 0) value |= 0x01;
			if((downflag & 0x0800) == 0) value |= 0x02; 	 
		}		
	}	

	return value;
}
