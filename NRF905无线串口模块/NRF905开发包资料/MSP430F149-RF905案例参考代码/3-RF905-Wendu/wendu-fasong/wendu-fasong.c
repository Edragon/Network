/****************************************************************************
 **
 **     NewMsg-RFDevKit5000
 **
 **     File version: $2009.2.1$
 **
 ***************************************************************************/
#include <msp430x14x.h>
#define  uchar   unsigned char
#define  uint    unsigned int
#define  uclong  unsigned long
//===========================DS18B20端口========================================
#define  OUT_DS18B20_0     P6OUT &=~BIT7          //输出0
#define  OUT_DS18B20_1     P6OUT |= BIT7          //输出1
#define  DS18B20_IN        P6DIR &=~BIT7          //方向设置为输入
#define  DS18B20_OUT       P6DIR |= BIT7          //方向设置为输出
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
//============================DS18B20寄存器指令=================================
#define DS18B20_READ_ROM          0x33
#define DS18B20_MATCH_ROM         0X55
#define DS18B20_SKIP_ROM          0XCC
#define DS18B20_SEARCH_ROM        0XF0
#define DS18B20_ALARM_SEARCH_ROM  0XEC
#define DS18B20_WRITE_RAM         0X40
#define DS18B20_READ_RAM          0XBE
#define DS18B20_COPY_RAM          0X48 
#define DS18B20_CONVERT_TEM       0X44
#define DS18B20_EECALL_EEPROM     0XB8
#define DS18B20_READ_POWER_SUPPLY 0XB4
//===========================NRF905:SPI指令=====================================
#define WC		          0x00
#define RC		          0x10
#define WTP		          0x20
#define WTA		          0x22
#define RTA		          0x23
#define RTP		          0x21
#define RRP		          0x24
//===========================DS18B20相关变量====================================
char temp_data[2]={0x00,0x00};
char dispaly[7]={0x11,0x22,0x33,0x44,0x55,0x66,0x77};
//==========================NRF905相关变量======================================
#define TxRxBuf_Len 4                             
unsigned char TxRxBuf[TxRxBuf_Len]={0x01,0x02,0x03,0x04};
char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};   //NRF905接收地址
char DATA_BUF;
//==========================NRF905:10字节寄存器初始化===========================
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
//================================系统时钟等初始化==============================
void InitSys()
{
   unsigned int iq0;
   _DINT();
   BCSCTL1 &=~XT2OFF;
   do
   {
      IFG1 &= ~OFIFG;			// 清除振荡器失效标志
  for (iq0 = 0xFF; iq0 > 0; iq0--);	// 延时，等待XT2起振
   }
   while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振	
   BCSCTL2 +=SELM0; 
   BCSCTL2 +=SELS;               
}
//==============================================================================
void DS18B20_IO_set(void)
{
  P6SEL&=0x7f; 
}
//===========================DS18B20延时========================================  
void DS1820_delay(int i)
{
	while(i--);
}
//==========================延时================================================
void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//==========================DS18B20复位=========================================
void ds18b20_reset(void) 
{ 

  DS18B20_OUT; //
  OUT_DS18B20_1;
  OUT_DS18B20_0;
  DS1820_delay(2500);  //500us
  OUT_DS18B20_1;
  DS18B20_IN;    //设置为输入
  DS1820_delay(10);
  while(P6IN&BIT7);
  DS18B20_OUT;
  OUT_DS18B20_1;
  DS1820_delay(250);
} 
//========================DS18B20读操作函数=====================================
char ds18b20_read(void) 
{ 
  char i;
  char temp=0;
  for(i=0;i<8;i++)
  {
   DS18B20_OUT;
   OUT_DS18B20_0;
   temp>>=1;
   OUT_DS18B20_1;
   DS18B20_IN;
   if(P6IN&BIT7)
   {
     temp|=0x80;
   }
     DS1820_delay(4);
     DS18B20_OUT;
     DS1820_delay(5);
  }
return (temp);
}
//========================DS18B20写操作函数=====================================
void ds18b20_write(char Date) 
{ 
  char i; 
    DS18B20_OUT;
     for(i=0;i<8;i++)
     {
       OUT_DS18B20_0;
      // DS1820_delay(6);
       if(Date & 0x01) 
       {
         OUT_DS18B20_1;
       }
       else
       {
         OUT_DS18B20_0;
       }
       DS1820_delay(4);
       OUT_DS18B20_1;
       Date>>=1;
     }
       DS1820_delay(8);
} 

//======================DS18B20温度转换函数=====================================
void Ds18b20Convert(void) 
{ 
   ds18b20_reset(); 
  ds18b20_write(0xCC); 
  ds18b20_write(0x44);
  
  Delay(200);
    
  ds18b20_reset(); 
  ds18b20_write(0xCC); 
  ds18b20_write(0xBE); 
  
  temp_data[0]=ds18b20_read(); 
  temp_data[1]=ds18b20_read();
}
//=========================温度换算处理=========================================
void work_temp()
{
	char n=0;
if(temp_data[1]>127)
	{
	temp_data[1]=(256-temp_data[1]);			//负值
	temp_data[0]=(256-temp_data[0]);
	n=1;
	}
	dispaly[6]=((temp_data[0]&0xf0)>>4)|((temp_data[1]&0x0f)<<4);
	dispaly[5]=dispaly[6]/100;				//百位
	dispaly[4]=dispaly[6]%100;				//
	dispaly[2]=dispaly[4]/10;				//十位
	dispaly[1]=dispaly[4]%10;				//个位	
	switch	(temp_data[0]&0x0f)				//小数位
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
	case 0x00:dispaly[0]=1;break;
	default:break;
	}
    if(n)		//负值时显示aa,正直显示dd
	{
	dispaly[3]=0x11;						//
	}
    else dispaly[3]=0x22;
}
//=========================NRF905 SPI读函数（IO模拟SPI时序）==================
unsigned char SpiRead(void)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		DATA_BUF=DATA_BUF<<1;
		SCK_1;
		if ((P3IN&0x04))//读取最高位，保存至最末尾，通过左移位完成整个字节
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
//==============================================================================
void LED_IO_set(void)
{    
        P6DIR |= 0x06;   P6SEL&=0xf9;        
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
void TxPacket(void)
{
	uchar i;
	CSN_0;
	SpiWrite(WTP);				// 待发数据装载命令
	for (i=0;i<4;i++)
	{
	  SpiWrite(dispaly[i]);
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
	Delay(10);					// while (DR!=1);
	TRX_CE_0;					// Set TRX_CE low
}
//==================================发送模式初始化-=============================
void SetTxMode(void)
{
	TRX_CE_0;
	TXEN_1;
	Delay(1); 					// Delay for mode change(>=650us)
}
//==================================数据发送===================================
void TX(void)
{
        SetTxMode();
	TxPacket();
}
main()
{
    WDTCTL=WDTPW + WDTHOLD;   // Stop watchdog 
    InitSys();
    nRF905_IO_set();
    LED_IO_set();
    DS18B20_IO_set();
    Config905();
    Ds18b20Convert();
    LED1_0;    LED2_0;
  while(1)
    {
    Ds18b20Convert();
    LED1_1;
    work_temp();	
    TX();
    LED1_0;	
    }
}