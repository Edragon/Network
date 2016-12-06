#include "def.h"
#include "./SPI/SPI.h"
#include "./nRF905/nRF905.h"

unsigned char TxBuf[28]={0};
unsigned char RxBuf[28]={0};
unsigned char tf=0;


void Delay(unsigned char n)
{
	unsigned char i;
	while(n--)
	for(i=0;i<80;i++);	
}


void main()
{
     unsigned char led1_count=0;
	 unsigned char led2_count=0;
	 //================NRF905初始化
     nRF905Init();

	//================
	Config905();				// Config nRF905 module
	TxBuf[0] = 1;
	TxBuf[1] = 1;
	SetTxMode();		// Set Tx Mode
	TxPacket(TxBuf);				// Transmit Tx buffer data
	LED1 = 0;
	LED2 = 0;

	Delay(500);				// delay for led light	
	LED1 = 1;
	LED2 = 1;
	TxBuf[0] = 0xff;
	TxBuf[1] = 0xff;

					// led close
	SetRxMode();	// Set nRF905 in Rx mode

	while(1)
	{
	
		   if(KEY1 ==0 ) { TxBuf[0] = 1 ;tf = 1 ; led1_count=15; }
		   if(KEY2 ==0 ) { TxBuf[1] = 1 ;tf = 1 ; led2_count=15;}
			
			if (tf==1)
			{	
				SetTxMode();			// Set Tx Mode
				TxPacket(TxBuf);				// Transmit Tx buffer data
				TxBuf[0] = 0xff;
				TxBuf[1] = 0xff;
				SetRxMode();			// Set nRF905 in Rx mode
				tf=0;
			}
            

		if (RxPacket(RxBuf) == 1)	//返回1 表明有数据包接收到
		{
			if (RxBuf[0]==1)
			{
				led1_count=15;
			}
			if (RxBuf[1]==1)
			{
				led2_count=15;
			}
		}

		//LED显示延时
		if (led1_count>0)	
		{
			led1_count--;
			LED1 = 0;
		}
		else LED1 = 1;

		if (led2_count>0)
		{
			led2_count--;
			LED2 = 0;
		}
		else LED2 = 1;
	}

}