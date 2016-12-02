//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
//---------------------------------NRF905模式控制定义---------------------------------
//#define  nrf905_TX_EN	  PB0	    //输出1
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
//#define  nrf905_TRX_CE  PD4 	    //输出1
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
#define   Read_nrf905_CD    PINB & (1 << PD3);
//#define  nrf905_AM      PB3	    //输入0
#define   Hign_nrf905_AM    PORTB |= (1 << PB3);   
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3); 
#define   Read_nrf905_AM    PINB & (1 << PB3);
//#define  nrf905_DR      PB2  		//输入0
#define   Hign_nrf905_DR     PORTB |= (1 << PB2);   
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2); 
#define   Read_nrf905_DR    PINB & (1 << PB2);   
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
uint temp[6];
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9段码
uchar seg1[10]={0x40,0x4F,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; 
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
void SetRxMode(void);						   //
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
	for (i=0;i<11;i++)			//写RF905配置字
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//------------------------------设置接收模式激发--------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(10); 					// delay for mode change(>=650us)
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

//----------------------------温度LED允窘缑�-----------------------------------
void  dis_zhuye()
{
	 PORTC=seg[TxRxBuffer[2]];
	 Hign_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Low_Display1;
	 Delay(80);
	 Hign_Display1;
//------------------------------------------------------------------------------
	 PORTC=seg1[TxRxBuffer[1]];
	 Low_Display2;
	 Delay(80);
	 Hign_Display2;
//------------------------------------------------ ---------------------------
	 PORTC=seg[TxRxBuffer[0]];
	 Low_Display3;
	 Delay(80);
	 Hign_Display3;
//----------------------------------------------------------------------------- 
	 PORTC=0xc6;
	 Low_Display4;
	 Delay(80);
	 Hign_Display4;	 
//------------------------------------------------------------------------------ 	
}
//-------------------------------串口初始化-------------------------------------
void StartUART(void)
{
 	 UCSRA=0x00;	
	 UCSRB=0x18;	
	 UCSRC=0x06;	
	 UBRRL=0x67;
	 UBRRH=0x00;
	 UCSRA=UCSRA|0x08;	
}
//------------------------------串口发送----------------------------------------
void R_S_Byte(uchar R_Byte)
{	
     UDR= R_Byte;  
}
//------------------------------主函数------------------------------------------
void main(void)
{  
	uchar i;
	DDRD=0xb2;		  //
	DDRB=0xB3;		  //
	DDRA=0x1e;       //
	DDRC=0xff; 		//LED端口设置
	PORTA = 0xff;
	Hign_BELL;	
	Hign_JDQ ;			
//------------------------------------------------------------------------------				  			 				
	Spi_initial();	                //SPI初始化															  
	system_Init();				   //系统状态初始化												
	Config905();  				  //NRF905初始化	
//------------------------------------------------------------------------------							  
//------------------------------------------------------------------------------
	StartUART();				//串口初始化9600波特率
	Delay(500);
//------------------------------------------------------------------------------
	while(1)
	{
	RX();  					//接收数据
	if(TxRxBuffer[0])
		{
		temp[2]=((TxRxBuffer[2]<<4)|TxRxBuffer[1]);		//整数位
		temp[1]=TxRxBuffer[0];							//小数位
		temp[0]=TxRxBuffer[3];     					    //符号位
		//temp[4]=TxRxBuffer[2];						//十位
		//temp[5]=TxRxBuffer[1];						//个位
	for(i=0;i<3;i++)
		{
		R_S_Byte(temp[2-i]);      //串口显示温度
		Delay(20);
		}
		
	}
	if((temp[2]>=53)||(temp[2]<=32))//大于35度时报警，0x35转换成10进制为53
									//低于20度时也报警,0x20,转换成10进制为	32						  									  																
	{
		Low_BELL;  //打开蜂明器报警
		Low_JDQ;   //打开继电器。可以进行相关电器开关操作
	}
	else
	{
	 	Hign_BELL ;//关闭蜂明器报警
		Hign_JDQ;  //关闭继电器
	}
	dis_zhuye();
	}
}
