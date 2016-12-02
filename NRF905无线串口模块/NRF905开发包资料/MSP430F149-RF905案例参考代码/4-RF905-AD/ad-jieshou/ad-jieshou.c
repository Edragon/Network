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
//===========================NRF905:SPI??=======================================
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//==============================================================================
#define TxRxBuf_Len     4       
unsigned char TxRxBuf[TxRxBuf_Len]={0x01,0x02,0x03,0x04};
char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};   //NRF905接收地址
char DATA_BUF;
char temp[6];
char seg[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
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
      IFG1 &= ~OFIFG;							// 清除振荡器失效标志
  for (iq0 = 0xFF; iq0 > 0; iq0--);	// 延时，等待XT2起振
   }
   while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振		
   BCSCTL2 =SELM1+SELS;                      //MCLK,SMCLK时钟为XT2			
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
//===========================LCD端口初始化=====================================
void LCD_IO_set()
  {
    CtrlDir |= 0x70;                 //控制线端口设为输出状态 
    DataDir  = 0xFF;                 //数据端口设为输出状态
    P4SEL=0x00;                    //设置P4为一般数字IO口   
    P6SEL&=0x8f;                  //设置P6为一般数字IO口  
  }
//======================232串口初始化===========================================
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
//   IE1 |= URXIE0;   //串口0接收中断使能
//   IE1 |= UTXIE0;   //串口0发送中断使能
//===================端口第二功能使能=========================================
    P3SEL |=BIT4;    //设置P3。4为UART0 的TXD
    P3SEL |=BIT5;    //设置P3。5为UART0 的RXD
    P3DIR |=BIT4;    //设置P3。4为输出
//  _EINT();        //打开全局中断控制，若不需要打开，可以屏蔽本句
  }
//======================通过串口将数据R_Byte发送给 PC =========================================
void R_S_Byte(char R_Byte)
{
  while((IFG1&UTXIFG0)==0);	//判断是否发送完毕
  TXBUF0=R_Byte;
}
//==========================延时================================================
void NRF905_Delay(uchar n)
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

//=================================数据接收=====================================
void RxPacket(void)						
{
    char i;
    NRF905_Delay(1);
    NRF905_Delay(100);
    TRX_CE_0;
    CSN_0;		// SPI使能（Spi enable for write a spi command）
    NRF905_Delay(1);
    SpiWrite(RRP);      // 读SPI数据命令（Read payload command）
for (i = 0 ;i < 4 ;i++)
    {  
      TxRxBuf[i]=SpiRead();		// Read data and save to buffer    
    }
    CSN_1;
    NRF905_Delay(10);
    TRX_CE_1;							
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
	NRF905_Delay(1); 		// delay for mode change(>=650us)
}
//==========================NRF905数据接收流程================================
void  RX(void)
{
    SetRxMode();			// Set nRF905 in Rx mode
    while (CheckDR()==0);
    NRF905_Delay(10);
    RxPacket();		// Recive data by nRF905
    NRF905_Delay(10);
}
//========================延时约5ms=============================================
void Delay5ms(void)
{ 
    uint i=40000;
    while (i != 0)
    {
        i--;
    }
}
//========================等待1602液晶完成内部操作==============================
void WaitForEnable(void) 
{
    P4DIR &= 0x00;  //将P4口切换为输入状态
    CLR_RS;
    SET_RW;
    _NOP();
    SET_EN; 
    _NOP();
    _NOP();
    while((P4IN & Busy)!=0);  //检测忙标志
    CLR_EN;
    P4DIR |= 0xFF;  //将P4口切换为输出状态
}	                  
//==========================向液晶模块写入命令==================================
//=================cmd--命令，chk--是否判忙的标志，1：判忙，0：不判=============
void LcdWriteCommand(uchar cmd,uchar chk) 
{

    if (chk) WaitForEnable();   // 检测忙信号?
    
    CLR_RS;	
    CLR_RW; 
    _NOP();

    DataPort = cmd;             //将命令字写入数据端口 
    _NOP();					
    
    SET_EN;                     //产生使能脉冲信号
    _NOP();
    _NOP();
    CLR_EN;			
}
//=====================向液晶显示的当前地址写入显示数据=========================
void LcdWriteData( uchar data ) 
{
    WaitForEnable();        //等待液晶不忙
    SET_RS;
    CLR_RW; 
    _NOP();
    DataPort = data;        //将显示数据写入数据端口
    _NOP();
    SET_EN;                 //产生使能脉冲信号
    _NOP(); 
    _NOP(); 
    CLR_EN;		
}
//==================向液晶输入显示字符位置的坐标信息============================
void LocateXY(uchar x,uchar y) 
{
    uchar temp;
    x&= 0x01;
    temp = y&0x0f;
    if(x)   temp |= 0x40;  //如果在第2行
    temp |= 0x80;
    LcdWriteCommand(temp,0);
}
//==========================在某个位置显示一个字符==============================
//============x--位置的列坐标   y--位置的行坐标data--显示的字符数据=============
void DisoneChar(uchar x,uchar y,uchar data) 
{
    LocateXY( x, y );			
    LcdWriteData( data );		
}
//==============================让液晶从某个位置起连续显示一个字符==============
//==============================y--位置的列坐标  x--位置的行坐标================
void DispStr(uchar x,uchar y,uchar *ptr) 
{
    uchar *temp;
    uchar i,n = 0;
    
    temp = ptr;
    while(*ptr++ != '\0')   n++;    //计算字符串有效字符的个数
    
    for (i=0;i<n;i++)
    {
        DisoneChar(x++,y,temp[i]);
        if (x == 0x0f)
        {
           x  = 0; 
           y ^= 1;
        }
    }
}
//让液晶从某个位置起连续显示N个字符
void DispNChar(uchar x,uchar y, uchar n,uchar *ptr) 
{
    uchar i;
    
    for (i=0;i<n;i++)
    {
        DisoneChar(x++,y,ptr[i]);
        if (x == 0x0f)
        {
           x = 0; 
           y ^= 1;
        }
    }
}
//========================对1602液晶模块进行复位操作============================
void LcdReset(void) 
{
    LcdWriteCommand(0x38, 0);	    //规定的复位操作
    Delay5ms();
    LcdWriteCommand(0x38, 0);		
    Delay5ms();
    LcdWriteCommand(0x38, 0);
    Delay5ms();
    LcdWriteCommand(0x38, 1);		//显示模式设置
    LcdWriteCommand(0x08, 1);		//显示关闭
    LcdWriteCommand(0x01, 1);	        //显示清屏
    LcdWriteCommand(0x06, 1);		//写字符时整体不移动
    LcdWriteCommand(0x0c,1);		//显示开，不开游标，不闪烁
   
}
//==================================NEWMSG-JASK3000=============================
void NewmsgJASK3000()
{
     DisoneChar(0,1,0x4e) ; // now : XX.X 度
     DisoneChar(0,2,0x45) ;
     DisoneChar(0,3,0x57) ;
     DisoneChar(0,4,0x4d) ;
     DisoneChar(0,5,0x53) ;
     DisoneChar(0,6,0x47) ;
     DisoneChar(0,7,0x2d) ;
     DisoneChar(0,8,0x2d) ;
     DisoneChar(0,9,0x4a) ;
     DisoneChar(0,10,0x41) ;
     DisoneChar(0,11,0x53) ;
     DisoneChar(0,12,0x4b) ;
     DisoneChar(0,13,0x33) ;
     DisoneChar(0,14,0x30) ;
     DisoneChar(0,15,0x30) ;
     DisoneChar(0,16,0x30) ;
}
//=================================== AD电压 显示 ================================
void dy_xianshi()
{
     DisoneChar(1,3,0x4e) ; // now : X.XX V
     DisoneChar(1,4,0x4f) ;
     DisoneChar(1,5,0x57) ;
     DisoneChar(1,6,0x20) ;
     DisoneChar(1,7,0x20) ;
     DisoneChar(1,8,seg[TxRxBuf[0]]) ;
     DisoneChar(1,9,0x2e) ;
     DisoneChar(1,10,seg[TxRxBuf[1]]) ;
     DisoneChar(1,11,seg[TxRxBuf[2]]) ;
     DisoneChar(1,12,0x56) ;

}
//=================================主函数======================================
void main(void)
{
   char i;
   WDTCTL = WDTPW + WDTHOLD; //禁止看门狗
   InitSys();         // 时钟初始化
   nRF905_IO_set();   // NRF905端口设置
   LED_IO_set();      //LED端口设置
   LCD_IO_set();      //LCD端口设置
   Config905();       //NRF905寄存器配置
   init_uart0();      //串口0初始化
   LcdReset();        //LCD初始化  
   NewmsgJASK3000();
   LED1_0;LED2_0;
while(1)
   {
       RX();  //接收数据
    if(TxRxBuf[3])              //软件检验一下
      {
        LED1_1;
	for(i=0;i<4;i++)
	{
	R_S_Byte(TxRxBuf[i]);     //串口上传温度
        NRF905_Delay(10);
	}
	}
      LED1_0;
      dy_xianshi();   //LCD电压显示
   }
}