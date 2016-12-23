#include"stm8s.h"
#include"main.h"
#include"24L01.h"
#include"uart.h"

uchar USART_RX_STA=0;
uchar USART_RX_BUF[USART_REC_LEN];

void UART1_Configuration(void)//串口初始化配置  
{
	UART1_DeInit();
	UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, 
							UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,	
							UART1_MODE_TXRX_ENABLE);
							
	UART1_Cmd(ENABLE);
	UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
}

void UART1_SendByte(uchar data_8)//发送字节函数
{
	UART1_SendData8(data_8);
	while(UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET);
}

void UART1_SendString(uchar *p)//发送字符串函数
{
	while(*p!=0)
	{
		UART1_SendByte(*p);
		p++;
	}
}

@far @interrupt void UART1_RX_Handler(void)
{
	uchar Res,i;
	if(UART1_GetITStatus(UART1_IT_RXNE)!=RESET)
	{
		Res=UART1_ReceiveData8();
		if((USART_RX_STA&0x80)==0)//接收未完成
		{
			if(USART_RX_STA&0x40)//接收到了0x0d
			{
				if(Res!=0x0a)
				{
					USART_RX_STA=0;//接收错误,重新开始
					for(i=0;i<USART_REC_LEN;i++) USART_RX_BUF[i]=0; //清除串口接收缓冲区
				}
				else USART_RX_STA|=0x80;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)
					USART_RX_STA|=0x40;
				else
				{
					USART_RX_BUF[USART_RX_STA&0x3f]=Res;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))
					{
						USART_RX_STA=0;//接收数据错误,重新开始接收
						for(i=0;i<USART_REC_LEN;i++) USART_RX_BUF[i]=0;//清除串口接收缓冲区
					}
				}		 
			}
		}   		 
	//	UART1_ClearITPendingBit(UART1_IT_RXNE);
	}
}