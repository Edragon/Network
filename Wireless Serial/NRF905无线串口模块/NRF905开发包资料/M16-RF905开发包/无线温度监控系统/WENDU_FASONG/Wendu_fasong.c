//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Triter : chenjia
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
//------------------------------------------------------------------------------
#define uint  unsigned int
#define uchar unsigned char
//----------------------------温度变量------------------------------------------
uchar  temp_data[2]={0x00,0x00};
uchar  dispaly[7];
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9段码
uchar seg1[10]={0x40,0x4F,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; 
//******************************************************************************
//***********************DS18B20--------PD6*************************************
//******************************************************************************
#define   In_DQ      DDRD &= ~(1 << PD6)       
#define   Out_DQ     DDRD |= (1 << PD6) 
//------------------------------------------------------------------------------
#define   Hign_DQ    PORTD |= (1 << PD6)   
#define   Low_DQ     PORTD &= ~(1 << PD6)
//------------------------------------------------------------------------------
#define   Read_DQ    PIND & (1 << PD6)
//******************************************************************************
//***********************NRF905端口设置*****************************************
//******************************************************************************
///////////////////////////模式控制定义/////////////////////////////////
//#define  nrf905_TX_EN	  PB0	    //输出1
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
//#define  nrf905_TRX_CE  PD4 	    //输出1
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4);   
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4); 
//#define  nrf905_PWR     PB1 	    //输出1
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1);   
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1); 
///////////////////////////SPI口定义////////////////////////////////////
//#define  nrf905_MISO	  PB6   	//输入0
//#define  nrf905_MOSI    PB5	    //输出1
//#define  nrf905_SCK     PB7	    //输出1
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7); 
////////////////////////////////////////////////////////////////////////
//#define  nrf905_CSN     PB4		//输出1		
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4);   
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4); 						
///////////////////////////状态输出口///////////////////////////////////
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
//----------------------------------905-SPI指令---------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------发送数据-------------------------------------
uchar TxRxBuf[4] ;
//----------------------------------接收地址------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
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
void delay(uint x);
void Spi_initial();
uchar SpiReadSpiWrite(uchar DATA);
void system_Init(void);
void Config905(void);
void TxPacket(void);
void SetTxMode(void);
void TX(void);
void StartUART(void);
void R_S_Byte(uchar R_Byte);
//------------------------------------------------------------------------------
void Init_DS18B20(void);
uchar ReadOneChar(void);
void WriteOneChar(uchar dat);
void ReadTemperature(void);
void work_temp();
void StartUART(void);
void R_S_Byte(uchar R_Byte);
void DS1820_delay(uint i);
//------------------------------------------------------------------------------
//**********************************NRF905驱动**********************************
//******************************************************************************
//----------------------------------100us延时子程序-----------------------------
void delay(uint x)
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
	delay(1);				// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config command写放配置命令
	for (i=0;i<11;i++)			// Write configration words  写放配置字
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
	delay(1);
	SpiReadSpiWrite(WTP);				// 写数据前先写写数据命令
	for (i=0;i<4;i++)
	{
	SpiReadSpiWrite(  dispaly[i]);		// 待发送的32字节数据
	}						
	Hign_nrf905_CSN;
	delay(1);							// 关闭Spi，不允许对nrf905进行读写操作
	Low_nrf905_CSN;								// 使能Spi
	SpiReadSpiWrite(WTA);				// 写地址前首先先写地址命令
	for (i=0;i<4;i++)					// 写 4 bytes 地址
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	Hign_nrf905_CSN;					// 关闭Spi
	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	delay(1);							// 等待DR变高
	Low_nrf905_TRX_CE;							// 设置TRX_CE=0
}
//-------------------------------发送模式激发-----------------------------------
void SetTxMode(void)
{
	Low_nrf905_TRX_CE;				//
	Hign_nrf905_TX_EN;				//发送使能
	delay(2); 				// delay for mode change(>=650us)根据晶振不同要改变
}
//------------------------------------------------------------------------------
void TX(void)
{
     SetTxMode();	   // Set nRF905 in Tx mode
	 TxPacket();			   // Send data by nRF905
}
//******************************************************************************
//**********************************DS18B20温度采集*****************************
//******************************************************************************

//----------------------------------延时函数------------------------------------
void DS1820_delay(uint i)
{
	while(i--);
}
//---------------------------------DS18B20初始化--------------------------------
void Init_DS18B20(void)
{
    unsigned char x=1;
	
	Out_DQ;                //配置输出
	Hign_DQ;              //置高电平
	Low_DQ;			     //置低电平
	DS1820_delay(3000);	    //400-960us
	Hign_DQ;		   //置高电平
	In_DQ ;
	DS1820_delay(40);		  //15-60us
	while(Read_DQ)	 ; 
	Out_DQ ;
	Hign_DQ;
	DS1820_delay(300);	
}
//---------------------------------DS18B20读函数--------------------------------
uchar ReadOneChar(void)
{
    uchar i;
	uchar dat = 0;
	
	for(i=8;i>0;i--)
	{
	    Out_DQ;    //配置输出
	    Low_DQ;   //置低电平
		dat >>= 1;
		Hign_DQ; //置高电平
		In_DQ;  //设置输入
		if(Read_DQ)//读取电平
        {
		dat |= 0x80;
        }
		Out_DQ;//配置输出
        DS1820_delay(50);
	}
	return(dat);
}
//------------------------------DS18B20写函数-----------------------------------
void WriteOneChar(uchar dat)
{
    uchar i;
	Out_DQ;//配置输出
	for(i=8;i>0;i--)
	{
	    Low_DQ;//置低电平
		if(dat&0x01)//写电平
        {
        Hign_DQ;//置高电平
        }
        else
        {
         Low_DQ;//置低电平
        }
		DS1820_delay(40);
		Hign_DQ;//置高电平
		dat >>= 1;
	}
	DS1820_delay(8);
}
//------------------------------------读取温度------------------------------------
void ReadTemperature(void)
{		
	Init_DS18B20();
	WriteOneChar(0xCC); 			// 跳过读序号列号的操作
	WriteOneChar(0x44); 			// 启动温度转换
	
	
	Init_DS18B20();
	WriteOneChar(0xCC); 			//跳过读序号列号的操作
	WriteOneChar(0xBE); 			//读取温度寄存器等（共可读9个寄存器） 前两个就是温度

	temp_data[0]= ReadOneChar();   		//读取温度值低位LSB
	temp_data[1]= ReadOneChar();   //读取温度值高位MSB
	
}
//-----------------------------------BCD码温度处理------------------------------
//dispaly[0]十位
//dispaly[1]个位
//dispaly[2]小数位
//dispaly[3]临界标志位
//------------------------------------------------------------------------------
void work_temp()
{
	uchar n=0;
	if(temp_data[1]>127)
	{
	temp_data[1]=(256-temp_data[1]);
	temp_data[0]=(256-temp_data[0]);
	n=1;
	}
//------------------------------------------------------------------------------
	dispaly[6]=((temp_data[0]&0xf0)>>4)|((temp_data[1]&0x0f)<<4);
	dispaly[5]=dispaly[6]/100;				//百位
	dispaly[4]=dispaly[6]%100;				//
	dispaly[2]=dispaly[4]/10;               //十位
	dispaly[1]=dispaly[4]%10;			    //个位
	
	switch	(temp_data[0]&0x0f)
	{
	case 0x0f:dispaly[0]=9;break;
	case 0x0e:dispaly[0]=9;break;
	case 0x0d:dispaly[0]=8;break;
	case 0x0c:dispaly[0]=8;break;
	case 0x0b:dispaly[0]=7;break;
	case 0x0a:dispaly[0]=6;break;
	case 0x09:dispaly[0]=6;break;
	case 0x08:dispaly[0]=5;break;
	case 0x07:dispaly[0]=4;break;
	case 0x06:dispaly[0]=4;break;
	case 0x05:dispaly[0]=3;break;
	case 0x04:dispaly[0]=3;break;
	case 0x03:dispaly[0]=2;break;
	case 0x02:dispaly[0]=1;break;
	case 0x01:dispaly[0]=1;break;
	case 0x00:dispaly[0]=0;break;
	default:break;
	}
		if(n)								//温度正负区分
	{
	dispaly[3]=0x11;						//零下
	}
	else
	{
	dispaly[3]=0x22;				  	//零上
	}
}

//------------------------------------------------------------------------------
void dis_zhuye()
{
	 PORTC=seg[dispaly[2]];
	 Hign_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Low_Display1;
	 delay(80);
	 Hign_Display1;
//------------------------------------------------------------------------------
	 PORTC=seg1[dispaly[1]];
	 Low_Display2;
	 delay(80);
	 Hign_Display2;
//------------------------------------------------ ---------------------------
	 PORTC=seg[dispaly[0]];
	 Low_Display3;
	 delay(80);
	 Hign_Display3;
//----------------------------------------------------------------------------- 
	 PORTC=0xc6;
	 Low_Display4;
	 delay(80);
	 Hign_Display4;	 
}
//----------------------------------主函数--------------------------------------
main()
{
//------------------------------------------------------------------------------
	DDRD=0xb2;		  //
	DDRB=0xB3;		  //
	DDRA=0x1e;       //
	DDRC=0xff; 		//LED端口设置
	PORTA = 0xff;
	Hign_BELL;	
	Hign_JDQ ;	
//------------------------------------------------------------------------------
	Spi_initial();
	system_Init();
	Config905();
	Init_DS18B20();
while(1)
	{
	ReadTemperature();		//读取温度
	work_temp();			//温度处理
	dis_zhuye();
 	TX();	
    }
}
