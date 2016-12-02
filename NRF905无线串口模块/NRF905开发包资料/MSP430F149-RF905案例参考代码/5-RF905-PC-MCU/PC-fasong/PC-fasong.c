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
//===================================LED========================================
#define  LED1_0     P6OUT &=~BIT1          //输出0
#define  LED1_1     P6OUT |= BIT1          //输出1
#define  LED2_0     P6OUT &=~BIT2          //输出0
#define  LED2_1     P6OUT |= BIT2          //输出1
//==================================BELL========================================
#define  BELL_0     P6OUT &=~BIT3          //输出0
#define  BELL_1     P6OUT |= BIT3          //输出1
//===================================LCD========================================
#define DataDir     P4DIR              
#define DataPort    P4OUT	
//==============================================================================
#define Busy	    0x80
//==============================================================================
#define CtrlDir     P6DIR
#define CLR_RS P6OUT&=~BIT6;    //RS = P6.6	
#define SET_RS P6OUT|=BIT6;	
//==============================================================================
#define CLR_RW P6OUT&=~BIT5;	//RW = P6.5
#define SET_RW P6OUT|=BIT5;	
//==============================================================================
#define CLR_EN P6OUT&=~BIT4;	//EN = P6.4
#define SET_EN P6OUT|=BIT4;	
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
  WC,                                //SPI写操作命令
  0x4c,                             //CH_NO,配置频段在430MHZ
  0x0C,                             //输出功率为10db,不重发，节电为正常模式
  0x44,                             //地址宽度设置，为4字节
  0x04,0x04,                        //接收发送有效数据长度为4字节
  0xCC,0xCC,0xCC,0xCC,              //接收地址
  0x58,                              //CRC充许，8位CRC校验，外部时钟信号不使能，16M晶振
};
char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};
char DATA_BUF;
char MARK;
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
  for (iq0 = 0xFF; iq0 > 0; iq0--);	// 延时，等待XT2起振
   }
   while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振		
   BCSCTL2 =SELM1+SELS;                      //MCLK,SMCLK时钟为XT2
							//???USART0
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
//===========================初始化nRF905=======================================
void nRF905_IO_set(void)
{
        P2DIR |= 0x07; P2DIR &= 0x8F;   P2SEL&=0x84;        
        P3DIR |= 0xC0; P3DIR |= 0xFB;   P3SEL&=0xF0;        
        CSN_1;				            // Spi 	disable
	SCK_0;				          // Spi clock line init low
	PWR_1;					 // nRF905 power on
	TRX_CE_0;				// Set nRF905 in standby mode
	TXEN_0;					// set radio in Rx mode
}
//==========================延时================================================
void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//=========================NRF905 SPI读函数（IO模拟SPI时序）==================
unsigned char SpiRead(void)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		DATA_BUF=DATA_BUF<<1;
		SCK_1;
		if ((P3IN&0x04))	//读取最高位，保存至最末尾，通过左移位完成整个字节
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
//=========================NRF905 SPI读写函数（IO模拟SPI时序）==================
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
//==================================初始化NRF905================================
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
//=========================NRF905装载地址+数据打包+数据发送=====================
void TxPacket(char *data_Bufer)
{
	uchar i;
	CSN_0;
	SpiWrite(WTP);				// 待发数据装载命令
	for (i=0;i<4;i++)
	{
	  SpiWrite(data_Bufer[i]);
	}
	CSN_1;                                  // 关闭SPI
	Delay(1);		
	CSN_0;					// 打开SPI
	SpiWrite(WTA);				// 写入地址要和接收方地址一样
	for (i=0;i<4;i++)			// 4字节地址
	{
	  SpiWrite(TxAddress[i]);
	}
	CSN_1;					//关闭SPI
	TRX_CE_1;					// Set TRX_CE high,start Tx data transmission
	Delay(10);	// while (DR!=1); 延时时间不能太短
	TRX_CE_0;					// Set TRX_CE low
}
//==================================发送模式初始化-=============================
void SetTxMode(void)
{
	TRX_CE_0;
	TXEN_1;
	Delay(1); 					// Delay for mode change(>=650us)
}

//======================串口初始化==============================================
void init_uart0(void)
  {
//====================串口工作模式设置========================================
    U0CTL=0x00;      // U0CTL包含串口0通信协议、通信模式、校验位等设置，允许UART0
    U0CTL +=CHAR;    //(CHAR=0x10)当CHAR=0时位7位数据，当 CHAR=1时为8位数据 
                     //不需要校验，数据位为8位，无反馈，异步UART通信，UART被允许
//====================串口发送操作设置========================================
    U0TCTL=0x00;     //U0TCTL包含串口0发送功能操作
    U0TCTL +=SSEL0;  //波特率发生器选择ACLK 
                     //#define SSEL1  (0x20)       #define SSEL0  (0x10)
//====================串口拨特率设置9600====================================
//===================拨特率计算公式：拨特率=BRCLK/（UBR+（M7+M6+。。。。+M0）/8）
    UBR0_0=0x03;     //UBR0_0为串口0波特率整数部分低地址 
    UBR1_0=0x00;     //UBR1_0为串口0波特率整数部分高地址 
    UMCTL_0=0x4A;    //UBR1_0为串口0波特率小数部分高地址 
//===================串口收发使能控制=========================================
    ME1 |= UTXE0;    //串口0发送功能使能
    ME1 |= URXE0;    //串口0接收功能使能    
//===================串口中断使能控制=========================================
    IE1 |= URXIE0;   //串口0接收中断使能
//   IE1 |= UTXIE0;   //串口0发送中断使能
//===================端口第二功能使能=========================================
    P3SEL |=BIT4;    //设置P3。4为UART0 的TXD
    P3SEL |=BIT5;    //设置P3。5为UART0 的RXD
    P3DIR |=BIT4;    //设置P3。4为输出
    _EINT();        //打开全局中断控制，若不需要打开，可以屏蔽本句
  }
//======================串口接收中断服务函数====================================
#if __VER__ < 200
  interrupt [UART0RX_VECTOR] void  UART0_RX_ISR(void)
#else
  #pragma vector=UART0RX_VECTOR
  __interrupt void UART0_RX_ISR(void)
#endif
{
  while ((IFG1 & URXIFG0) == 1);//中断标志        
  if((U0RCTL&RXERR)==0)          //没有接收出错
  {
  MARK = RXBUF0; // RXBUF0 to TXBUF0
  //delay(500);
  TXBUF0=MARK;
  IFG1=IFG1&0xef;
  }
}
//==================================主函数=====================================
void main(void)
{
   char tf;
   WDTCTL = WDTPW + WDTHOLD; 
   InitSys();
   nRF905_IO_set();
   LED_IO_set();        //LED端口设置
   BELL_IO_set();
   KEY_IO_set();       //KEY端口设置
   Config905();
   init_uart0();
   LED1_1;LED2_1;BELL_1;
while(1)
   {
    if(MARK==48)		//0，0的 ASCII码为48
	{
	TxBuf[0]=0x01;tf=1;LED1_1;BELL_0; 
	}
    if(MARK==49)		//1
	{
	TxBuf[0]=0x11;tf=1;LED1_0; BELL_1; 
        }
    if(MARK==50)		//2
	{
	TxBuf[0]=0x21;tf=1;LED1_1;BELL_0;
        }	
    if(MARK==51)		//3
	{
	TxBuf[0]=0x31;tf=1;LED1_0; BELL_1;
	}
    if(MARK==52)		//4
	{
	TxBuf[0]=0x41;tf=1;LED2_0; BELL_0; 
	}
    if(MARK==53)	        //5
	{
	TxBuf[0]=0x51;tf=1;LED2_1; BELL_1;
	}
    if(MARK==54)		//6
	{
	TxBuf[0]=0x61;tf=1;LED2_0; BELL_0; 
	}
    if(MARK==55)		//7
	{
	TxBuf[0]=0x71;tf=1;LED1_1; BELL_1; 
        }
    if(MARK==56)		//8
	{
	TxBuf[0]=0x81;tf=1;LED1_0;BELL_0; 
	}
   if(MARK==57)			//9
	{
	TxBuf[0]=0x91;tf=1;LED1_1; BELL_0; 
        }
//-----------------------------------------------------------------------------
     if (tf==1)//当有收到PC端指令后发送数据
	{
         SetTxMode(); TxPacket(TxBuf);
         tf = 0;  MARK=0;
          TxBuf[0]=0x00;
	}	 
   }
}