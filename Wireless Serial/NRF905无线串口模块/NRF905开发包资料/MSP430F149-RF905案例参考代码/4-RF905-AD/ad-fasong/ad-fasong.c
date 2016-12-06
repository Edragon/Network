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
#define RTP		          0x21
#define WTA		          0x22
#define RTA		          0x23
#define RRP		          0x24
//===========================AD相关变量====================================
char UART0_RX_BUF[],nRX0_Len_temp,nRX0_Len;
unsigned int ADC_Buf1[32];
unsigned int ADC_Buf2[32];
unsigned int ADC_BUF_Temp1[32];
unsigned int ADC_BUF_Temp2[32];
unsigned int nADC_Count=0; 
char AD_TxBuf[4]={0x22,0x22,0x22,0x22};
//==========================NRF905相关变量======================================
#define TxRxBuf_Len 4                             
unsigned char TxRxBuf[TxRxBuf_Len]={0x01,0x02,0x03,0x22};
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
   BCSCTL2 +=SELS;                //MCLK,SMCLK时钟为XT2
       _EINT();        //打开全局中断控制，若不需要打开，可以屏蔽本句
}
//==============================================================================
void ADC_IO_set(void)
{
  P6DIR= P6DIR&0XFE;              //设置P6.0-P6.1为AD采集功能
  P6SEL= P6SEL|0X01;              //设置P6.0-P6.
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
//==========================延时================================================
void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//=============================TIMERA初始化=====================================
void Init_TimerA(void)
{
  TACTL=TASSEL1+TACLR;
  CCTL0=CCIE;
  CCR0=40000;
  TACTL |=MC0;
}
/**********************************************************
函数名称：TimerA_ISR
函数功能：定时器A中断，用于采集AD
输    入：
输    出：ADC_Buf[]
**********************************************************/
#if __VER__<200
  interrupt [TIMERA0_VECTOR] void TimerA_ISR(void)
#else
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
#endif
{   
    int i;
    ADC12CTL0&=~(ENC);    //不允许转换
    ADC_Buf1[nADC_Count]=ADC12MEM0;//读出通道0数据
    ADC_Buf2[nADC_Count]=ADC12MEM1; //读出通道1数据   
    nADC_Count+=1;
    if(nADC_Count==32)         //采样32次
    {
      nADC_Count=0;
      for(i=0;i<32;i++) 
      {
        ADC_BUF_Temp1[i]=ADC_Buf1[i];
        ADC_BUF_Temp2[i]=ADC_Buf2[i];
      }
    }
    ADC12CTL0 |=ENC+ADC12SC;      //允许AD转换，并开始采样
}
/*********************************************************
函数名称：Init_ADC(void)
函数功能：ad初始化
输    入：
输    出：
*********************************************************/
void Init_ADC(void)
{
  ADC12CTL0&=~(ENC);    //关闭AD，从而可以来设置AD转换类控制寄存器：ADC12寄存器  
                        //其中#define ENC (0x002)   /* ADC12 Enable Conversion
  ADC12CTL0 |=REF2_5V+REFON;//开启内部参考电压，参考电压：内部2.5V，
//==============================================================================
  ADC12CTL1 |=CSTARTADD_0;    //转换的起始地址为：ADCCME0，（可以 CSTARTADD_0----->CSTARTADD_15选择）
  ADC12MCTL0=INCH_0;        //设置参考电压分别为AVSS和AVCC，输入通道为A0
  ADC12MCTL1=INCH_1+SREF_1; //设置参考电压分别为AVSS和REFF+，输入通道为A1
  ADC12MCTL2=INCH_2+EOS;   //转换通道接触
//==============================================================================
  ADC12CTL0|=ADC12ON;     //打开ADC12模块，可以进行转换
  ADC12CTL0|=MSC;         //MSC=1时，首次转换由SHI信号上升沿触发采样定时器，后面的采样和第一次完成立即进行
//==============================================================================
  ADC12CTL1|=CONSEQ_1;     //转换模式:序列通道，单次转换
  ADC12CTL1|=ADC12SSEL_1;  //SMCLK
  ADC12CTL1|=ADC12DIV_0;   //时钟分频为1 
  ADC12CTL1|=(SHP);        //采样脉冲由定时器产生
    
  ADC12CTL0|=ENC;         //使能ADC转换功能
  return;
}
/***********************************************************
函数功能：对采集到得AD进行滤波处理
函数名称：filter
***********************************************************/
unsigned int filter(void)
{
  unsigned long temp;
  unsigned int result;
  unsigned char n;
  temp=0;
  for(n=0;n<32;n++)   //对通道1数据进行求和平均滤波
  {
    temp += ADC_BUF_Temp1[n];
  }
  temp>>=5;           //处于32
  temp*=2500;         //乘上2500mV
  result=temp>>12;    //1/4096
 
  return result;
}
//--------------------------------//AD数据采集百位------------------------------
unsigned char GetBaiwei(unsigned char temp)   
{
	temp= temp/100;
        return temp;
}
//-----------------------------//AD数据采集十位---------------------------------
unsigned char  GetShiwei(unsigned char temp)  
{
	if(temp > 99)
	{
	temp = temp - GetBaiwei(temp)*100;
	}
	temp= temp/10;
        return temp;
}
//---------------------------- //AD数据采集个位---------------------------------
unsigned char  GetGewei(unsigned char temp)   
{
	temp= temp%10;
        return temp;
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
	CSN_0;			// Spi enable for write a spi command
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
	  SpiWrite(AD_TxBuf[i]);
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
    int a;
    WDTCTL=WDTPW + WDTHOLD;   // Stop watchdog 
    InitSys();
    nRF905_IO_set();
    LED_IO_set();
    ADC_IO_set();
    Init_ADC(); 
    Init_TimerA();  //TIMERA初始化
    Config905();
    LED1_0;    LED2_0;
  while(1)
    {
    a=filter();     //AD数据处理
    AD_TxBuf[0]=GetBaiwei(a);  
    AD_TxBuf[1]=GetShiwei(a); 
    AD_TxBuf[2]=GetGewei(a);
    LED1_0; 
    TX();         //AD数据发送
    Delay(200);
    Delay(200);
    LED1_1;  
    }
}