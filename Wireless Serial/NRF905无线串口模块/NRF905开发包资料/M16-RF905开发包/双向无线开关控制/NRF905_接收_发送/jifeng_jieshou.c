//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
///////////////////////////模式控制定义/////////////////////////////////
//#define  nrf905_TX_EN	  PB0	    //输出1   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0)
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0)
//#define  nrf905_TRX_CE  PD4	    //输出1
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4)  
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4) 
//#define  nrf905_PWR     PB1 	    //输出1
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1) 
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1)
//--------------------------------SPI口定义-------------------------------------
//#define  nrf905_MISO	  PB6   	//输入0
//#define  nrf905_MOSI    PB5	    //输出1
//#define  nrf905_SCK     PB7	    //输出1
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7)
//------------------------------------------------------------------------------
//#define  nrf905_CSN     PB4		//输出1		
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4)  
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4)				
//-------------------------------状态输出口-------------------------------------
//#define  nrf905_CD      PD3	    //输入0
#define   Hign_nrf905_CD    PORTD |= (1 << PD3) 
#define   Low_nrf905_CD     PORTD &= ~(1 << PD3) 
#define   Read_nrf905_CD    PINB & (1 << PD3)
//#define  nrf905_AM      PB3	    //输入0
#define   Hign_nrf905_AM    PORTB |= (1 << PB3) 
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3)
#define   Read_nrf905_AM    PINB & (1 << PB3)
//#define  nrf905_DR      PB2  		//输入0
#define   Hign_nrf905_DR    PORTB |= (1 << PB2)
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2)
#define   Read_nrf905_DR    PINB & (1 << PB2)
//读取键值KEY2-KEY3-KEY4  
#define   Read_KEY_2  	    PINA & (1 << PA5)        
//甲队加3分
#define   Read_KEY_3    	PINA & (1 << PA6)
//乙队加2分
#define   Read_KEY_4   	    PINA & (1 << PA7)   
//乙队加3分
//------------------------------数码管位选--------------------------------------
//#define Display1   PA1  		    //输出1
#define   Hign_Display1     PORTA |= (1 << PA1);   
#define   Low_Display1    PORTA &= ~(1 << PA1); 
//#define Display2      PA2  		//输出1
#define   Hign_Display2     PORTA |= (1 << PA2);   
#define   Low_Display2    PORTA &= ~(1 << PA2); 
//#define Display3     PA3  		//输出1
#define   Hign_Display3     PORTA |= (1 << PA3);   
#define   Low_Display3     PORTA &= ~(1 << PA3); 
//#define Display4      PA4 		//输出1
#define   Hign_Display4     PORTA |= (1 << PA4);   
#define   Low_Display4     PORTA &= ~(1 << PA4); 
//-------------------------------BELL蜂明器-------------------------------------
#define   Hign_BELL  PORTD |= (1 << PD5);   
#define   Low_BELL     PORTD &= ~(1 << PD5); 
//-------------------------------JDQ继电器--------------------------------------
#define   Hign_JDQ  PORTD |= (1 << PD7)
#define   Low_JDQ     PORTD &= ~(1 << PD7)
//----------------------------------905-SPI指令---------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------发送数据缓冲区-------------------------------
uchar TxRxBuf[4];
//----------------------------------接收地址------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
uchar tf;
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9段码
//------------------------------------------------------------------------------
//----------------------------------寄存器配置----------------------------------
uchar RFConf[11]=
{
  0x00,                             //配置命令//
  0x4c,                             //CH_NO,配置频段在430MHZ
  0x0C,                             //输出功率为10db,不重发，节电为正常模式
  0x44,                             //地址宽度设置，为4字节
  0x04,0x04,                        //接收发送有效数据长度为4字节
  0xCC,0xCC,0xCC,0xCC,              //接收地址
  0x58,                              //CRC充许，8位CRC校验，外部时钟信号不使能，16M晶振
};
//----------------------------------函数申明------------------------------------
void Delay(uint x);
void Spi_initial();
uchar SpiReadSpiWrite(uchar DATA);
void system_Init(void);
void Config905(void);
void TxPacket(uchar TxBUF[4]);
void SetTxMode(void);
void TX(void);
void StartUART(void);
void R_S_Byte(uchar R_Byte);
//----------------------------------100us延时子程序-----------------------------
void Delay(uint x)
{
	uint i;
	while(x--)
	for(i=0;i<80;i++);
}
//----------------------------------SPI初始化-----------------------------------
void Spi_initial()
{
	//SPCR=0x50;
	//SPSR=0x00;	
	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);   // 主机模式，fck/16, SPI方式0
}
//---------------------------------SPI读写程序----------------------------------	
uchar SpiReadSpiWrite(unsigned char cData)//r
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF) ))
	{};			// 等待SPI发送完毕
	return SPDR;
}
//---------------------------------系统状态初始化-------------------------------
void system_Init(void)			//r
{

   	Hign_nrf905_CSN;				// Spi 	disable
	Low_nrf905_SCK;				// Spi clock line init low
	Low_nrf905_DR;				// Init DR for input
	Low_nrf905_AM;				// Init AM for input
	Low_nrf905_CD;				// Init nrf905_CDfor input
	Hign_nrf905_PWR;				// nRF905 power on
	Low_nrf905_TRX_CE;			// Set nRF905 in standby mode
	Low_nrf905_TX_EN ;			// set radio in Rx mode
}
//--------------------------------NRF905寄存器初始化函数------------------------
void Config905(void)
{
	uchar i;
	Low_nrf905_CSN;	
	Delay(1);				// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config command写放配置命令
	for (i=0;i<11;i++)			// Write configration words  写放配置字
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//--------------------------------NRF905待发数据打包----------------------------
void TxPacket(uchar TxBUF[4])
{
	uchar i;
	Low_nrf905_CSN;		   						// 使能Spi，允许对nrf905进行读写操作
	Delay(1);
	SpiReadSpiWrite(WTP);				// 写数据前先写写数据命令
	for (i=0;i<4;i++)
	{
	SpiReadSpiWrite(TxBUF[i]);		// 待发送的32字节数据
	}						
	Hign_nrf905_CSN;
	Delay(1);							// 关闭Spi，不允许对nrf905进行读写操作
	Low_nrf905_CSN;								// 使能Spi
	SpiReadSpiWrite(WTA);				// 写地址前首先先写地址命令
	for (i=0;i<4;i++)					// 写 4 bytes 地址
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	Hign_nrf905_CSN;					// 关闭Spi
	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	Delay(1);							// 等待DR变高
	Low_nrf905_TRX_CE;							// 设置TRX_CE=0
}
//-------------------------------发送模式激发-----------------------------------
void SetTxMode(void)
{
	Low_nrf905_TRX_CE;				//
	Hign_nrf905_TX_EN;				//发送使能
	Delay(2); 				// delay for mode change(>=650us)根据晶振不同要改变
}
//------------------------------------------------------------------------
//------------------------------设置接收模式激发--------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(1000); 					// delay for mode change(>=650us)
}
//-----------------------------------读接收数据包-------------------------------
void RxPacket(void)							//读数据
{
	uchar i;
    Low_nrf905_TRX_CE;
	Low_nrf905_CSN;						    // 使能SPI
    Delay(1);
	SpiReadSpiWrite(RRP);				   // 写入数据接收缓冲区数据命令
	for (i = 0 ;i < 4 ;i++)
	{   
	TxRxBuf[i]=SpiReadSpiWrite(0);	  // 读取数据接收缓冲区数据       
	}
	Hign_nrf905_CSN;
    Delay(2);                            //
	Hign_nrf905_TRX_CE;							
}
//--------------------------------设置接收模式----------------------------------
void  RX(void)
{
    SetRxMode();			          //设置NRF905接收模式
	RxPacket();                     //读取接收数据缓冲区
	Delay(10);
	if(TxRxBuf[0]==0x29)
	{
	 PORTC=seg[1];
	 Low_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Hign_Display1;
	}
	if(TxRxBuf[0]==0x30)
	{
	 PORTC=seg[2];
	 Hign_Display4;
	 Low_Display3;
	 Hign_Display2;
	 Hign_Display1;
	}
	if(TxRxBuf[0]==0x31)
	{
	 PORTC=seg[3];
	 Hign_Display4;
	 Hign_Display3;
	 Low_Display2;
	 Hign_Display1;

	}
}
//------------------------------主函数------------------------------------------
void main(void)
{  
	uint i,j,temp[32];
	DDRD=0xf2;		  //
	DDRB=0xB3;		  //
	DDRA=0x1e;       //
	DDRC=0xff; 		//LED端口设置
	PORTA=0x00;
	PORTC=0xbf;
	Hign_BELL;
	Hign_JDQ ;
	Spi_initial();
	system_Init();
	Config905();
	while(1)
 {
     RX();
//------------------------------------------------------------------------------
	if((PINA & 0x20) == 0)		  //有键按下KEY1
	{
	while(!(PINA & 0x20));   			//等待按键松开GREEN
	 TxRxBuf[0]=0x29;
	 tf=1;   
	 PORTC=seg[1];
	 Low_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Hign_Display1;
	 }
//------------------------------------------------------------------------------
	if((PINA & 0x40) == 0)			//有键按下KEY2
	{
	while(!(PINA & 0x40));   			//等待按键松开GREEN
 	 TxRxBuf[0]=0x30; 
	 tf=1;    
	 PORTC=seg[2];
	 Hign_Display4;
	 Low_Display3;
	 Hign_Display2;
	 Hign_Display1;
	 }
//------------------------------------------------------------------------------
	if((PINA & 0x80) == 0)			//有键按下KEY3
	{
	while(!(PINA & 0x80));   			//等待按键松开GREEN
 	 TxRxBuf[0]=0x31;
	 tf=3;
	 PORTC=seg[3];
	 Hign_Display4;
	 Hign_Display3;
	 Low_Display2;
	 Hign_Display1;
	}
//------------------------------------------------------------------------------
	if(tf)
	{
	tf=0;
	Low_JDQ ;
	//--------------------------------------------------------
	SetTxMode();				// 激发数据发s送
	TxPacket(TxRxBuf);			// 装载待发送数据	
	Delay(200); 	
	//-------------------------------------------------
	TxRxBuf[0]=0;
	 }
	 //****************************************************************

	Hign_BELL;
	Hign_JDQ ;															
}
}