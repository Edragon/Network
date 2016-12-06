#include <msp430x14x.h>
//==============================================================================
#define  uchar   unsigned char
#define  uint    unsigned int
#define  uclong  unsigned long
//==================TXEN，TRX_CE，PWR_0 为收发模式控制端口======================
#define  TXEN_0     P2OUT &=~BIT0          //输出0
#define  TXEN_1     P2OUT |= BIT0          //输出1
//==============================================================================
#define  TRX_CE_0   P2OUT &=~BIT1
#define  TRX_CE_1   P2OUT |= BIT1
//==============================================================================
#define  PWR_0      P2OUT &=~BIT2
#define  PWR_1      P2OUT |= BIT2
//===================================主入从出===================================
#define  MISO_0     P3OUT &=~BIT2      
#define  MISO_1     P3OUT |= BIT2         
//==================================主出从入====================================
#define  MOSI_0     P3OUT &=~BIT1         
#define  MOSI_1     P3OUT |= BIT1        
//===================================SPI时钟端口================================
#define  SCK_0      P3OUT &=~BIT3         
#define  SCK_1      P3OUT |= BIT3         
//===================================SPI使能端口=================================
#define  CSN_0      P3OUT &=~BIT0
#define  CSN_1      P3OUT |= BIT0
//==================================以下为状态端口==============================
//===========================AM  地址匹配=======================================
#define  AM_0       P2OUT &=~BIT5       
#define  AM_1       P2OUT |= BIT5
//=================================DR 数据接收状态==============================
#define  DR_0       P2OUT &=~BIT6
#define  DR_1       P2OUT |= BIT6
//=====================================CD 载波侦听状态==========================
#define  CD_0       P2OUT &=~BIT4
#define  CD_1       P2OUT |= BIT4
//==============================================================================
#define  LED1_0     P6OUT &=~BIT1          //输出0
#define  LED1_1     P6OUT |= BIT1          //输出1
#define  LED2_0     P6OUT &=~BIT2          //输出0
#define  LED2_1     P6OUT |= BIT2          //输出1
//==================================BELL========================================
#define  BELL_0     P6OUT &=~BIT3          //输出0
#define  BELL_1     P6OUT |= BIT3          //输出1
//===========================NRF905:SPI指令=====================================
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//==========================32字节发送数据收发缓冲区============================
#define TxRxBuf_Len 4
char TxBuf[TxRxBuf_Len];
char RxBuf[TxRxBuf_Len];
//==========================NRF905：10寄存器配置================================
unsigned char  RFConf[11]=
{
  0x00,                             
  0x5f,                            
  0x0c,                            
  0x44,                             
  0x04,0x04,                        
  0xCC,0xCC,0xCC,0xCC,             		  
  0x58,        
};
char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};
char DATA_BUF;
/*****************************************************************************
系统初始化
******************************************************************************/
void InitSys()
{
   unsigned int iq0;
   _DINT();
   BCSCTL1 &=~XT2OFF;
   do
   {
      IFG1 &= ~OFIFG;							// 清除振荡器失效标志
   }
  	
   BCSCTL2 =SELM1+SELS;                      //MCLK,SMCLK时钟为XT2
						
}
//==============================================================================
void LED_IO_set(void)
{    
        P6DIR |= 0x06;   P6SEL&=0xf9;        
}
//==============================================================================
void BELL_IO_set(void)
{    
        P6DIR |= 0x08;   P6SEL&=0xF7;        
}
//==============================================================================
void KEY_IO_set(void)
{    
        P1DIR &= 0xfc;   P1SEL&=0xfc;        
}
//=========================================================================
void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//===========================================
unsigned char SpiRead(void)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		DATA_BUF=DATA_BUF<<1;
		SCK_1;
		if ((P3IN&0x04))	
		{
			DATA_BUF|=0x01;
		}
		else
		{
			DATA_BUF&=~(0x01);
		}
		SCK_0;
	 }
	 return DATA_BUF;
}
//===========================================
void SpiWrite(unsigned char send)
{
	unsigned char i;
	DATA_BUF=send;
	for (i=0;i<8;i++)
	{
	if (((DATA_BUF&0x80) != 0))	//总是发送最高位
        {
	    MOSI_1;
	 }
	else
	 {
	    MOSI_0;
	 }
	SCK_1;
	DATA_BUF=DATA_BUF<<1;
	SCK_0;
	}
}

//===========================初始化nRF905=======================================
void nRF905_IO_set(void)
{   
        CSN_1;				            // Spi 	disable
	SCK_0;				          // Spi clock line init low
	PWR_1;					 // nRF905 power on
	TRX_CE_0;				// Set nRF905 in standby mode
	TXEN_0;					// set radio in Rx mode
}
//==================================================================
void Config905(void)
{
	uchar i;
	CSN_0;						// Spi enable for write a spi command
	for (i=0;i<11;i++)	// Write configration words  写放配置字
	{
	   SpiWrite(RFConf[i]);
	}
	CSN_1;					//关闭SPI
}
//==============================================
void TxPacket(char *data_Bufer)
{
	uchar i;
	CSN_0;
	SpiWrite(WTP);				
	for (i=0;i<4;i++)
	{
	  SpiWrite(data_Bufer[i]);
	}
	CSN_1;                                  
	Delay(10);		
	CSN_0;					
	SpiWrite(WTA);				
	for (i=0;i<4;i++)			
	{
	  SpiWrite(TxAddress[i]);
	}
	CSN_1;					
	TRX_CE_1;					
	TRX_CE_0;				
}
//===============================================================
void SetTxMode(void)
{
	TRX_CE_0;
	TXEN_1;
	Delay(100); 					// Delay for mode change(>=650us)
}

//=========DR检测,当 收到数据后DR置1，当把数据读出来后DR清0=====================
unsigned char CheckDR(void)		//检查是否有新数据传入 Data Ready
{
	if ((P2IN&0x40))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//==============================================================================
void SetRxMode(void)
{
	TXEN_0;
	TRX_CE_1;
	Delay(1); 		// delay for mode change(>=650us)
}
//=================================数据接收=====================================
void RxPacket(void)						
{
    char i;
    Delay(1);
    TRX_CE_0;
    CSN_0;		// SPI使能（Spi enable for write a spi command）
    Delay(1);
    SpiWrite(RRP);     
for (i = 0 ;i <4 ;i++)
    {  
      RxBuf[i]=SpiRead();		 
    }
    CSN_1;
    Delay(10);
    TRX_CE_1;							
}

//=========================================================
void  RX(void)
{
    SetRxMode();			// Set nRF905 in Rx mode
    RxPacket();		// Recive data by nRF905
    Delay(10);
//=============================================================================
    if(RxBuf[0]==0x29)
    {
     LED1_1;
     BELL_0;
    }
    if(RxBuf[0]==0x30)
    {
     LED1_0;
     BELL_1;
    }
    RxBuf[0]=0x00;
}
//==================================主函数=====================================
void main(void)
{
   char tf;
   WDTCTL = WDTPW + WDTHOLD; 
   InitSys();
   nRF905_IO_set();
   LED_IO_set();
   BELL_IO_set();
   KEY_IO_set();      
   Config905();
   LED1_1;LED2_1;BELL_1;
while(1)
   {
    RX();//接收数据
//==================================================
    if((P1IN&0x01))   //检测按键
      {	
        TxBuf[0]=0x29;tf = 1 ; LED2_0;
      }
      if((P1IN&0x02) )		 
      {	
        TxBuf[0]=0x30;tf = 1 ; LED2_1;
      }
     if(tf==1)     
      {
         SetTxMode(); TxPacket(TxBuf);
         tf = 0;	
         TxBuf[0]=0x00;
      }	 
   }
}