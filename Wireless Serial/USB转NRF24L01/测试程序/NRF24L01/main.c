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
	
	SysClkInit();//初始化主时钟，
	NRF24L01_Init();//初始化NRF24L01
	UART1_Configuration();//初始化串口
	enableInterrupts();//开总中断
	GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);//模式控制位，，上拉输入
						//这个引脚如果要更改，需改动两处，还有一处在mian.h中
	while(NRF24L01_Check())//检测NRF24L01是否存在
	{
		UART1_SendString("请检查NRF24L01\r\n");
		delay_ms(500);
	}
	UART1_SendString("\r\n检测NRF24L01成功\r\n"); //检测到NRF24L01
	
	NRF24L01_Status_TX();//开机默认发送模式
	
	while(1)
	{
		Mode_Config(PinLevel_Check());//根据控制引脚电平配置模式
		
		if((USART_RX_STA&0x80)!=0)//串口数据接收完成
		{
			if(Mode_Status==MODE_TX)//24L01发送模式
			{
				UART1_SendString("\r\n你发送的信息为：");
				data_len=USART_RX_STA&0x3f;//得到接收到的数据长度
				USART_RX_STA=0;
				for(i=0;i<data_len;i++) UART1_SendByte(USART_RX_BUF[i]);//将串口发送的数据返回
			//	UART1_SendString("\r\n");// 换行
				if(NRF24L01_TxPacket(USART_RX_BUF)==TX_OK) UART1_SendString("\r\nNRF24L01发送成功\r\n");
				else 	UART1_SendString("\r\nNRF24L01发送失败\r\n");
			}
			else if(Mode_Status==MODE_RX) 
			{
				USART_RX_STA=0;
				UART1_SendString("\r\nNRF24L01接收模式，无法发送\r\n");
			}
			for(i=0;i<data_len;i++) USART_RX_BUF[i]=0;//每次串口接收完成后，需要重新清除接收缓存
		}

		if(Mode_Status==MODE_RX)//接收模式
		{
			if(NRF24L01_RxPacket(NRF24L01_RX_BUF)==0)//接收完成
			{
				UART1_SendString("\r\n你接收的信息为：");
				NRF24L01_RX_BUF[RX_PLOAD_WIDTH]=0;//最后要补0，这句 不是必须的，因为已经初始化为0
				UART1_SendString(NRF24L01_RX_BUF); //将24L01接收的信息发送给串口
			}
		}
	}
}

void SysClkInit(void)//启用外部晶振作为主时钟
{
//	CLK_SWR=0xb4; //HSE为主时钟源
//	while(!(CLK_SWCR&0x08));
//	CLK_CKDIVR=0x00;//CPU时钟0分频，系统时钟0分频
//	CLK_CSSR=0x01;//时钟安全监测使能
//	CLK_SWCR=0x02;//使能自动时钟切换
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);   //1分频 16MHZ
}

void delay_ms(uint z)//ms延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=1330;y>0;y--);
}

void delay_10us(uint z)//10us延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=15;y>0;y--);
}

uchar PinLevel_Check(void)//检测模式配置引脚的电平
{
	static uchar up_falg=1;//不支持连按的方式
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

void Mode_Config(uchar sta)//配置NRF24L01的收发模式
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
	NRF24L01_RX_Mode();//NRF24L01配置成接收模式
	Mode_Status=MODE_RX;
	UART1_SendString("\r\nNRF24L01接收模式\r\n");
}

void NRF24L01_Status_TX(void)
{
	NRF24L01_TX_Mode();//NRF24L01配置成发射模式
	Mode_Status=MODE_TX;
	UART1_SendString("\r\nNRF24L01发送模式\r\n");
}
