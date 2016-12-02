//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
//---------------------------------模式控制定义---------------------------------
//#define  nrf905_TX_EN	  PB0	    //输出1
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
//#define  nrf905_TRX_CE  PD4	    //输出1
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4);   
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4); 
//#define  nrf905_PWR     PB1 	    //输出1
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1);   
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1); 
//--------------------------------NRF905-SPI口接口定义--------------------------
//#define  nrf905_MISO	  PB6   	//输入0
//#define  nrf905_MOSI    PB5	    //输出1
//#define  nrf905_SCK     PB7	    //输出1
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7); 
//#define  nrf905_CSN     PB4		//输出1		
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4);   
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4); 						
//-------------------------------NRF905状态输出口-------------------------------
//#define  nrf905_CD      PD3	    //输入0
#define   Hign_nrf905_CD    PORTD |= (1 << PD3);   
#define   Low_nrf905_CD     PORTD &= ~(1 << PD3); 
#define   Read_nrf905_CD    PINB & (1 << PD4);
//#define  nrf905_AM      PB3	    //输入0
#define   Hign_nrf905_AM    PORTB |= (1 << PB3);   
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3); 
#define   Read_nrf905_AM    PINB & (1 << PB3);
//#define  nrf905_DR      PB2  		//输入0
#define   Hign_nrf905_DR     PORTB |= (1 << PB2);   
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2); 
#define   Read_nrf905_DR    PINB & (1 << PB2);   
//-------------------------------BELL蜂明器-------------------------------------
#define   Hign_BELL  PORTD |= (1 << PD5);   
#define   Low_BELL     PORTD &= ~(1 << PD5); 
//-------------------------------JDQ继电器--------------------------------------
#define   Hign_JDQ  PORTD |= (1 << PD7)
#define   Low_JDQ     PORTD &= ~(1 << PD7)

//----------------------------------NRF905-SPI指令------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------发送数据-------------------------------------
uchar TxRxBuffer[4];
//----------------------------------接收地址------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
//------------------------------------------------------------------------------
uchar count1 ,count2;
//----------------------------------寄存器配置----------------------------------
uchar RFConf[11]=
{
  0x00,                            //配置命令//
  0x4c,                           //CH_NO,配置频段在430MHZ
  0x0C,                          //输出功率为10db,不重发，节电为正常模式
  0x44,                         //地址宽度设置，为4字节
  0x04,0x04,                   //接收发送有效数据长度为4字节
  0xCC,0xCC,0xCC,0xCC,        //接收地址
  0x58,                      //CRC充许，8位CRC校验，外部时钟信号不使能，16M晶振
};
//----------------------------------NRF905函数申明------------------------------
void Delay(uint x);						       //延时子程序																							
void Spi_initial();                            //SPI初始化
uchar SpiReadSpiWrite(unsigned char cData);    //SPI读写子程序
void system_Init(void);		   				   //系统初始化
void Config905(void);						   //NRF905初始化子程序
void TxPacket(void);						
void SetTxMode(void);						   //数据发送
void SetRxMode(void);						   //
void TX(void);
unsigned char CheckDR(void);
void RxPacket(void);
void  RX(void);
//-------------------------------串口函数申明-----------------------------------
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
	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);// 主机模式，fck/16, SPI方式0
}
//---------------------------------SPI读写程序----------------------------------	
uchar SpiReadSpiWrite(unsigned char cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF) ))  // 等待SPI发送完毕
	{};			
	return SPDR;
}
//--------------------------------系统状态初始化--------------------------------
void system_Init(void)			
{

   	Hign_nrf905_CSN;			// SPI使能
	Low_nrf905_SCK;				
	Low_nrf905_DR;				// DR=0
	Low_nrf905_AM;				// AM=0
	Low_nrf905_CD;				// CD=0
	Hign_nrf905_PWR;		    // PWR=1
	Low_nrf905_TRX_CE;			// nrf905_TRX_CE=0
	Low_nrf905_TX_EN ;			// nrf905_TX_EN=0
}
//--------------------------------NRF905寄存器初始化函数------------------------
void Config905(void)
{
	uchar i;
	Low_nrf905_CSN;				//SPI使能											
	Delay(1);				   
	for (i=0;i<11;i++)			//碞RF905配置字
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//--------------------------------NRF905待发数据打包----------------------------
void TxPacket(void)
{
	uchar i;
	Low_nrf905_CSN;		   				// 使能Spi，允许对nrf905进行读写操作
	Delay(1);
	SpiReadSpiWrite(WTP);				// 写数据前先写写数据命令
	for (i=0;i<32;i++)
	{
	SpiReadSpiWrite(TxRxBuffer[i]);		// 待发送的32字节数据
	}						
	Hign_nrf905_CSN;
	Delay(1);							// 关闭Spi，不允许对nrf905进行读写操作
	Low_nrf905_CSN;						// 使能Spi
	SpiReadSpiWrite(WTA);				// 写地址前首先先写地址命令
	for (i=0;i<4;i++)					// 写入4 bytes 接收地址
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	Hign_nrf905_CSN;					// 关闭Spi
	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	Delay(1);							// 等待DR变高
	Low_nrf905_TRX_CE;					// 设置TRX_CE=0
}
//------------------------------设置发送模式------------------------------------
void SetTxMode(void)
{
	Low_nrf905_TRX_CE;				//
	Hign_nrf905_TX_EN;				//发送使能
	Delay(2); 				// delay for mode change(>=650us)
}
//------------------------------设置接收模式激发--------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(10); 					// delay for mode change(>=650us)
}
//------------------------------发送数据----------------------------------------
void TX(void)
{
     SetTxMode();	   // Set nRF905 in Tx mode
	 TxPacket();			   // Send data by nRF905
}
//-----------------------------判断是否收到数据---------------------------------
unsigned char CheckDR(void)		//检查是否有新数据传入 
{
	if (PINB & (1 << PB2))
	{
		return 1; 	 	  		//收到数据
	}
	else
	{
		return 0;
	}
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
	TxRxBuffer[i]=SpiReadSpiWrite(0);	  // 读取数据接收缓冲区数据       
	}
	Hign_nrf905_CSN;
    Delay(2);                            //
	Hign_nrf905_TRX_CE;							
}
//--------------------------------设置接收模式----------------------------------
void  RX(void)
{
    SetRxMode();			          //设置NRF905接收模式
    while (CheckDR()==0);	         //等待接收完成
	RxPacket();                     //读取接收数据缓冲区
	Delay(10);
}
//------------------------------主函数------------------------------------------
void main(void)
{  
	uint i;
	DDRD=0xF2;						  //端口D设置											  
	DDRB=0xB3;					     //端口B设置	
	PORTA=0x00;
	PORTC=0xbf;
//------------------------------------------------------------------------------	
	Hign_JDQ;			  //关闭继电器				
	Hign_BELL;							
//------------------------------------------------------------------------------				  			 				
	Spi_initial();	                //SPI初始化															  
	system_Init();				   //系统状态初始化												
	Config905();  				  //NRF905初始化	
	
//------------------------------------------------------------------------------
	while(1)
	{
	RX();  					//接收数据
	if(TxRxBuffer[0])
	{
	if(TxRxBuffer[0]==0x29)
	{
	Low_JDQ;			   //打开继电器
	}
	if(TxRxBuffer[0]==0x30)
	{
	Low_BELL;			   //打开蜂明器

	}
	}
	Delay(200);
	Hign_JDQ;			  //关闭继电器				
	Hign_BELL;			  //关闭蜂明器		
	}
}
