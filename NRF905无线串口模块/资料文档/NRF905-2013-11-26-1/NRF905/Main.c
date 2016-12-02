/*
 * NRF905模块
 * 
 * 用途：NRF905模块测试程序
 * 
 * 作者					日期				备注
 * Huafeng Lin			2013/11/26			新增
 * Huafeng Lin			2013/11/26			修改
 * 
 */

#include <reg52.h>
#include <ABSACC.h>
#include <intrins.h>
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------
#define uint unsigned int
#define uchar unsigned char
//----------------------------------------------------------------------------------------------------------------
#define BYTE_BIT0	0x01
#define BYTE_BIT1	0x02
#define BYTE_BIT2	0x04
#define BYTE_BIT3	0x08
#define BYTE_BIT4	0x10
#define BYTE_BIT5	0x20
#define BYTE_BIT6	0x40
#define BYTE_BIT7	0x80
//----------------------------------------------------------------------------------------------------------------
bdata unsigned  char DATA_BUF;
#define DATA7	((DATA_BUF&BYTE_BIT7) != 0)
#define DATA0   ((DATA_BUF&BYTE_BIT0) != 0)
sbit	flag	=DATA_BUF^7;
sbit	flag1	=DATA_BUF^0;
//---------------------------------------------------发送数据缓冲区-------------------------------------------------
#define TxRxBuf_Len 4
unsigned char TxRxBuf[TxRxBuf_Len]=
{
0x29,0x30,0x31,0x32,
};
//---------------------------------------------------配置口定义---------------------------------------------------
//配置口定义
sbit	TXEN=P3^7;
sbit	TRX_CE=P1^4;
sbit	PWR=P3^6;
sbit	MISO=P1^0;
sbit	MOSI=P1^3;
sbit	SCK=P1^2;
sbit	CSN=P1^5;

sbit	AM=P1^6;
sbit	DR=P1^1;
sbit	CD=P3^5;
//----------------------------------------------------按键--------------------------------------------------

sbit    KEY0    =P3^0;
sbit    KEY1    =P3^1;
//----------------------------------------------------数码管位控制-------------------------------------------------------
sbit    led0    =P1^7;
sbit    led1    =P3^4;
//-----------------------------------------------------------------------------------------------------------------
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9段码
//-------------------------------------------------------nrf905控制指令-------------------------------------------
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//------------------------------------------------NRF905寄存器配置------------------------------------------------
unsigned char idata RFConf[11]=
{
  0x00,                             	//配置命令
  0x4c,                             	//CH_NO,配置频段在430MHZ
  0x0c,                             	//输出功率为10db,不重发，节电为正常模式
  0x44,                             	//地址宽度设置，为4字节
  0x04,0x04,                        	//接收发送有效数据长度为32字节
  0xCC,0xCC,0xCC,0xCC,              	//接收地址
  0x58,                              	//CRC充许，8位CRC校验，外部时钟信号不使能，16M晶振
};
code TxAddress[4]={0xcc,0xcc,0xcc,0xcc};
char tf;
//------------------------------------------------延时------------------------------------------------------------
static void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//---------------------------------------------------SPI读函数-----------------------------------------------------
unsigned char SpiRead(void)
{
	unsigned char j;
	for (j=0;j<8;j++)
	{
        DATA_BUF=DATA_BUF<<1;
		SCK=1;
		if (MISO)						//读取最高位，保存至最末尾，通过左移位完成整个字节
		{
			DATA_BUF|=BYTE_BIT0;
		}
		else
		{
			DATA_BUF&=~BYTE_BIT0;
		}
		SCK=0;
	 }
	 return DATA_BUF;
}
//-------------------------------------------------SPI写函数----------------------------------------------------------
void SpiWrite(unsigned char send)
{
	unsigned char i;
	DATA_BUF=send;
	for (i=0;i<8;i++)
	{
		if (DATA7)	//总是发送最高位
		{
			MOSI=1;
		}
		else
		{
			MOSI=0;
		}
		SCK=1;
		DATA_BUF=DATA_BUF<<1;
		SCK=0;
	}
}
//------------------------------------------------------初始化nRF905---------------------------------------------
void nRF905Init(void)
{
    CSN=1;						// Spi 	disable
	SCK=0;						// Spi clock line init low
	DR=0;						// Init DR for input
	AM=0;						// Init AM for input
	CD=0;						// Init CD for input
	PWR=1;						// nRF905 power on
	TRX_CE=0;					// Set nRF905 in standby mode
	TXEN=0;						// set radio in Rx mode
}
//-----------------------------------------------------初始化寄存器-----------------------------------------------
void Config905(void)
{
	uchar i;
	CSN=0;						// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config command写放配置命令
	for (i=0;i<11;i++)			// Write configration words  写放配置字
	{
	   SpiWrite(RFConf[i]);
	}
	CSN=1;						// Disable Spi
}
//-----------------------------------------------------发送数据打包---------------------------------------------------
void TxPacket(uchar *TxRxBuf)
{
	uchar i;
	//Config905();
	CSN=0;
	SpiWrite(WTP);					// Write payload command
	for (i=0;i<4;i++)
	{
		SpiWrite(TxRxBuf[i]);		// Write 32 bytes Tx data
	}// Spi enable for write a spi command
	CSN=1;
	Delay(1);						// Spi disable
	CSN=0;							// Spi enable for write a spi command
	SpiWrite(WTA);					// Write address command
	for (i=0;i<4;i++)				// Write 4 bytes address
	{
		SpiWrite(TxAddress[i]);
	}
	CSN=1;							// Spi disable
	TRX_CE=1;						// Set TRX_CE high,start Tx data transmission
	Delay(1);						// while (DR!=1);
	TRX_CE=0;						// Set TRX_CE low
}
//----------------------------------------------------------设置发送状态---------------------------------------------
void SetTxMode(void)
{
	TRX_CE=0;
	TXEN=1;
	Delay(1); 						// delay for mode change(>=650us)
}
//-----------------------------------------------设置发送状态---------------------------------------------------
void SetRxMode(void)
{
	TXEN=0;
	TRX_CE=1;
	Delay(1); 						// delay for mode change(>=650us)
}
//-------------------------------------------------判断数据接收状态-----------------------------------------------------
unsigned char CheckDR(void)			//检查是否有新数据传入 Data Ready
{
	if (DR=1&&TRX_CE==1 && TXEN==0)
	{
       // Delay(50)  ;
		return 1;
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------读NRF905接收数据------------------------------------------------------------
void RxPacket(void)						
{
	uchar i;
    Delay(1);
//	TRX_CE=0;						// Set nRF905 in standby mode
    Delay(100);
    TRX_CE=0;
	CSN=0;							// Spi enable for write a spi command
    Delay(1);
	SpiWrite(RRP);
	for (i = 0 ;i < 4 ;i++)
	{ 
		TxRxBuf[i]=SpiRead();		// Read data and save to buffer       
	}
	CSN=1;
    Delay(10);
	TRX_CE=1;							
}
//--------------------------------------------------------数据接收------------------------------------------------
void  RX(void)
{
          SetRxMode();				// Set nRF905 in Rx mode
          while (CheckDR()==0);
		  Delay(10);
	  	  RxPacket();
		  if(TxRxBuf[0]==0x29)
		  {
				led0=0;
				led1=1;
			
		  }
		  if(TxRxBuf[1]==0x29)
		  {
				led0=1;
				led1=0;
			
		  }
}
//-----------------------------------------------------------------------------------------------------------------
void main(void)
{
        nRF905Init();
     	Config905();
		led0=0;
		led1=0;
		
        while(1)
		{
			RX();
		   if(KEY0 ==0 )
			 {	
				tf = 1 ;
				TxRxBuf[0]=0x29;
				TxRxBuf[1]=0x30;

				led0=0;
				led1=1;
			
				 }
		   if(KEY1 ==0 )
			 {	tf = 1 ; 
				TxRxBuf[0]=0x30;
				TxRxBuf[1]=0x29;

				led0=1;
				led1=0;

		 		}
	       if (tf==1)
			{
                SetTxMode();		// Set nRF905 in Tx mode
			    TxPacket(TxRxBuf);	// Send data by nRF905
				tf = 0;	
				Delay(100);
			}
		Delay(100);
		led1=1;
		led0=1;	
		Delay(100);
	}
}