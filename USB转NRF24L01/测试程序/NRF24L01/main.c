#include"stm8s.h"
#include"stm8s903k.h"
#include"stm8s903k3.h"
#include"main.h"
#include"24L01.h"
#include"uart.h"

uchar Mode_Status;

uchar NRF24L01_RX_BUF[RX_PLOAD_WIDTH+1]={0};

main()
{
	uchar i,data_len;
	
	SysClkInit();//��ʼ����ʱ�ӣ�
	NRF24L01_Init();//��ʼ��NRF24L01
	UART1_Configuration();//��ʼ������
	enableInterrupts();//�����ж�
	GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);//ģʽ����λ������������
						//����������Ҫ���ģ���Ķ�����������һ����mian.h��
	while(NRF24L01_Check())//���NRF24L01�Ƿ����
	{
		UART1_SendString("����NRF24L01\r\n");
		delay_ms(500);
	}
	UART1_SendString("\r\n���NRF24L01�ɹ�\r\n"); //��⵽NRF24L01
	
	NRF24L01_Status_TX();//����Ĭ�Ϸ���ģʽ
	
	while(1)
	{
		Mode_Config(PinLevel_Check());//���ݿ������ŵ�ƽ����ģʽ
		
		if((USART_RX_STA&0x80)!=0)//�������ݽ������
		{
			if(Mode_Status==MODE_TX)//24L01����ģʽ
			{
				UART1_SendString("\r\n�㷢�͵���ϢΪ��");
				data_len=USART_RX_STA&0x3f;//�õ����յ������ݳ���
				USART_RX_STA=0;
				for(i=0;i<data_len;i++) UART1_SendByte(USART_RX_BUF[i]);//�����ڷ��͵����ݷ���
			//	UART1_SendString("\r\n");// ����
				if(NRF24L01_TxPacket(USART_RX_BUF)==TX_OK) UART1_SendString("\r\nNRF24L01���ͳɹ�\r\n");
				else 	UART1_SendString("\r\nNRF24L01����ʧ��\r\n");
			}
			else if(Mode_Status==MODE_RX) 
			{
				USART_RX_STA=0;
				UART1_SendString("\r\nNRF24L01����ģʽ���޷�����\r\n");
			}
			for(i=0;i<data_len;i++) USART_RX_BUF[i]=0;//ÿ�δ��ڽ�����ɺ���Ҫ����������ջ���
		}

		if(Mode_Status==MODE_RX)//����ģʽ
		{
			if(NRF24L01_RxPacket(NRF24L01_RX_BUF)==0)//�������
			{
				UART1_SendString("\r\n����յ���ϢΪ��");
				NRF24L01_RX_BUF[RX_PLOAD_WIDTH]=0;//���Ҫ��0����� ���Ǳ���ģ���Ϊ�Ѿ���ʼ��Ϊ0
				UART1_SendString(NRF24L01_RX_BUF); //��24L01���յ���Ϣ���͸�����
			}
		}
	}
}

void SysClkInit(void)//�����ⲿ������Ϊ��ʱ��
{
//	CLK_SWR=0xb4; //HSEΪ��ʱ��Դ
//	while(!(CLK_SWCR&0x08));
//	CLK_CKDIVR=0x00;//CPUʱ��0��Ƶ��ϵͳʱ��0��Ƶ
//	CLK_CSSR=0x01;//ʱ�Ӱ�ȫ���ʹ��
//	CLK_SWCR=0x02;//ʹ���Զ�ʱ���л�
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);   //1��Ƶ 16MHZ
}

void delay_ms(uint z)//ms��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=1330;y>0;y--);
}

void delay_10us(uint z)//10us��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=15;y>0;y--);
}

uchar PinLevel_Check(void)//���ģʽ�������ŵĵ�ƽ
{
	static uchar up_falg=1;//��֧�������ķ�ʽ
	if(up_falg&&MODE_CTRL_PIN==0)
	{
		delay_ms(10);
		if(MODE_CTRL_PIN==0) 
		{
			up_falg=0;
			return 0;
		}
	}
	if(MODE_CTRL_PIN!=0) up_falg=1;
	return 1;
}

void Mode_Config(uchar sta)//����NRF24L01���շ�ģʽ
{
	static uchar ModeConfig_flag=0;
	if(sta==0)
	{
		ModeConfig_flag=!ModeConfig_flag;
		if(ModeConfig_flag==0)
		{
			NRF24L01_Status_TX();
		}
		else 
		{
			NRF24L01_Status_RX();
		}
	}
}

void NRF24L01_Status_RX(void)
{
	NRF24L01_RX_Mode();//NRF24L01���óɽ���ģʽ
	Mode_Status=MODE_RX;
	UART1_SendString("\r\nNRF24L01����ģʽ\r\n");
}

void NRF24L01_Status_TX(void)
{
	NRF24L01_TX_Mode();//NRF24L01���óɷ���ģʽ
	Mode_Status=MODE_TX;
	UART1_SendString("\r\nNRF24L01����ģʽ\r\n");
}
