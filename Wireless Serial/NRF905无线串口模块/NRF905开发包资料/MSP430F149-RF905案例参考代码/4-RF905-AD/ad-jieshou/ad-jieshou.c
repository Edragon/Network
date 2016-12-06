#include <msp430x14x.h>
//==============================================================================
#define  uchar   unsigned char
#define  uint    unsigned int
#define  uclong  unsigned long
//==================TXEN��TRX_CE��PWR_0 Ϊ�շ�ģʽ���ƶ˿�======================
#define  TXEN_0     P2OUT &=~BIT0          //���0
#define  TXEN_1     P2OUT |= BIT0          //���1
//==============================================================================
#define  TRX_CE_0   P2OUT &=~BIT1
#define  TRX_CE_1   P2OUT |= BIT1
//==============================================================================
#define  PWR_0      P2OUT &=~BIT2
#define  PWR_1      P2OUT |= BIT2
//===================================����ӳ�===================================
#define  MISO_0     P3OUT &=~BIT2      
#define  MISO_1     P3OUT |= BIT2         
//==================================��������====================================
#define  MOSI_0     P3OUT &=~BIT1         
#define  MOSI_1     P3OUT |= BIT1        
//===================================SPIʱ�Ӷ˿�================================
#define  SCK_0      P3OUT &=~BIT3         
#define  SCK_1      P3OUT |= BIT3         
//===================================SPIʹ�ܶ˿�=================================
#define  CSN_0      P3OUT &=~BIT0
#define  CSN_1      P3OUT |= BIT0
//==================================����Ϊ״̬�˿�==============================
//===========================AM  ��ַƥ��=======================================
#define  AM_0       P2OUT &=~BIT5       
#define  AM_1       P2OUT |= BIT5
//=================================DR ���ݽ���״̬==============================
#define  DR_0       P2OUT &=~BIT6
#define  DR_1       P2OUT |= BIT6
//=====================================CD �ز�����״̬==========================
#define  CD_0       P2OUT &=~BIT4
#define  CD_1       P2OUT |= BIT4
//==============================================================================
#define  LED1_0     P6OUT &=~BIT1          //���0
#define  LED1_1     P6OUT |= BIT1          //���1
#define  LED2_0     P6OUT &=~BIT2          //���0
#define  LED2_1     P6OUT |= BIT2          //���1
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
char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};   //NRF905���յ�ַ
char DATA_BUF;
char temp[6];
char seg[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
//==========================NRF905:10�ֽڼĴ�����ʼ��===========================
unsigned char  RFConf[11]=
{
  WC,                                //SPIд��������
  0x4c,                             //CH_NO,����Ƶ����430MHZ
  0x0C,                             //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
  0x44,                             //��ַ������ã�Ϊ4�ֽ�
  0x04,0x04,                        //���շ�����Ч���ݳ���Ϊ4�ֽ�
  0xCC,0xCC,0xCC,0xCC,              //���յ�ַ
  0x58,                              //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
};
//================================ϵͳʱ�ӵȳ�ʼ��==============================
void InitSys()
{
   unsigned int iq0;
   _DINT();
   BCSCTL1 &=~XT2OFF;
   do
   {
      IFG1 &= ~OFIFG;							// �������ʧЧ��־
  for (iq0 = 0xFF; iq0 > 0; iq0--);	// ��ʱ���ȴ�XT2����
   }
   while ((IFG1 & OFIFG) != 0);		// �ж�XT2�Ƿ�����		
   BCSCTL2 =SELM1+SELS;                      //MCLK,SMCLKʱ��ΪXT2			
}
//===========================��ʼ��nRF905=======================================
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
//===========================LCD�˿ڳ�ʼ��=====================================
void LCD_IO_set()
  {
    CtrlDir |= 0x70;                 //�����߶˿���Ϊ���״̬ 
    DataDir  = 0xFF;                 //���ݶ˿���Ϊ���״̬
    P4SEL=0x00;                    //����P4Ϊһ������IO��   
    P6SEL&=0x8f;                  //����P6Ϊһ������IO��  
  }
//======================232���ڳ�ʼ��===========================================
void init_uart0(void)
  {
//====================���ڹ���ģʽ����========================================
    U0CTL=0x00;      // U0CTL��������0ͨ��Э�顢ͨ��ģʽ��У��λ�����ã�����UART0
    U0CTL +=CHAR;    //(CHAR=0x10)��CHAR=0ʱλ7λ���ݣ��� CHAR=1ʱΪ8λ���� 
                     //����ҪУ�飬����λΪ8λ���޷������첽UARTͨ�ţ�UART������
//====================���ڷ��Ͳ�������========================================
    U0TCTL=0x00;     //U0TCTL��������0���͹��ܲ���
    U0TCTL +=SSEL0;  //�����ʷ�����ѡ��ACLK 
                     //#define SSEL1  (0x20)       #define SSEL0  (0x10)
//====================���ڲ���������9600====================================
//===================�����ʼ��㹫ʽ��������=BRCLK/��UBR+��M7+M6+��������+M0��/8��
    UBR0_0=0x03;     //UBR0_0Ϊ����0�������������ֵ͵�ַ 
    UBR1_0=0x00;     //UBR1_0Ϊ����0�������������ָߵ�ַ 
    UMCTL_0=0x4A;    //UBR1_0Ϊ����0������С�����ָߵ�ַ 
//===================�����շ�ʹ�ܿ���=========================================
    ME1 |= UTXE0;    //����0���͹���ʹ��
    ME1 |= URXE0;    //����0���չ���ʹ��    
//===================�����ж�ʹ�ܿ���=========================================
//   IE1 |= URXIE0;   //����0�����ж�ʹ��
//   IE1 |= UTXIE0;   //����0�����ж�ʹ��
//===================�˿ڵڶ�����ʹ��=========================================
    P3SEL |=BIT4;    //����P3��4ΪUART0 ��TXD
    P3SEL |=BIT5;    //����P3��5ΪUART0 ��RXD
    P3DIR |=BIT4;    //����P3��4Ϊ���
//  _EINT();        //��ȫ���жϿ��ƣ�������Ҫ�򿪣��������α���
  }
//======================ͨ�����ڽ�����R_Byte���͸� PC =========================================
void R_S_Byte(char R_Byte)
{
  while((IFG1&UTXIFG0)==0);	//�ж��Ƿ������
  TXBUF0=R_Byte;
}
//==========================��ʱ================================================
void NRF905_Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//=========================NRF905 SPI��������IOģ��SPIʱ��==================
unsigned char SpiRead(void)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		DATA_BUF=DATA_BUF<<1;
		SCK_1;
		if ((P3IN&0x04))	//��ȡ���λ����������ĩβ��ͨ������λ��������ֽ�
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
//=========================NRF905 SPI��д������IOģ��SPIʱ��==================
void SpiWrite(unsigned char send)
{
	unsigned char i;
	DATA_BUF=send;
	for (i=0;i<8;i++)
	{
	if (((DATA_BUF&0x80) != 0))	//���Ƿ������λ
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
//==================================��ʼ��NRF905================================
void Config905(void)
{
	uchar i;
	CSN_0;						// Spi enable for write a spi command
	for (i=0;i<11;i++)	// Write configration words  д��������
	{
	   SpiWrite(RFConf[i]);
	}
	CSN_1;					//�ر�SPI
}

//=================================���ݽ���=====================================
void RxPacket(void)						
{
    char i;
    NRF905_Delay(1);
    NRF905_Delay(100);
    TRX_CE_0;
    CSN_0;		// SPIʹ�ܣ�Spi enable for write a spi command��
    NRF905_Delay(1);
    SpiWrite(RRP);      // ��SPI�������Read payload command��
for (i = 0 ;i < 4 ;i++)
    {  
      TxRxBuf[i]=SpiRead();		// Read data and save to buffer    
    }
    CSN_1;
    NRF905_Delay(10);
    TRX_CE_1;							
}
//=========DR���,�� �յ����ݺ�DR��1���������ݶ�������DR��0=====================
unsigned char CheckDR(void)		//����Ƿ��������ݴ��� Data Ready
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
//==========================NRF905���ݽ�������================================
void  RX(void)
{
    SetRxMode();			// Set nRF905 in Rx mode
    while (CheckDR()==0);
    NRF905_Delay(10);
    RxPacket();		// Recive data by nRF905
    NRF905_Delay(10);
}
//========================��ʱԼ5ms=============================================
void Delay5ms(void)
{ 
    uint i=40000;
    while (i != 0)
    {
        i--;
    }
}
//========================�ȴ�1602Һ������ڲ�����==============================
void WaitForEnable(void) 
{
    P4DIR &= 0x00;  //��P4���л�Ϊ����״̬
    CLR_RS;
    SET_RW;
    _NOP();
    SET_EN; 
    _NOP();
    _NOP();
    while((P4IN & Busy)!=0);  //���æ��־
    CLR_EN;
    P4DIR |= 0xFF;  //��P4���л�Ϊ���״̬
}	                  
//==========================��Һ��ģ��д������==================================
//=================cmd--���chk--�Ƿ���æ�ı�־��1����æ��0������=============
void LcdWriteCommand(uchar cmd,uchar chk) 
{

    if (chk) WaitForEnable();   // ���æ�ź�?
    
    CLR_RS;	
    CLR_RW; 
    _NOP();

    DataPort = cmd;             //��������д�����ݶ˿� 
    _NOP();					
    
    SET_EN;                     //����ʹ�������ź�
    _NOP();
    _NOP();
    CLR_EN;			
}
//=====================��Һ����ʾ�ĵ�ǰ��ַд����ʾ����=========================
void LcdWriteData( uchar data ) 
{
    WaitForEnable();        //�ȴ�Һ����æ
    SET_RS;
    CLR_RW; 
    _NOP();
    DataPort = data;        //����ʾ����д�����ݶ˿�
    _NOP();
    SET_EN;                 //����ʹ�������ź�
    _NOP(); 
    _NOP(); 
    CLR_EN;		
}
//==================��Һ��������ʾ�ַ�λ�õ�������Ϣ============================
void LocateXY(uchar x,uchar y) 
{
    uchar temp;
    x&= 0x01;
    temp = y&0x0f;
    if(x)   temp |= 0x40;  //����ڵ�2��
    temp |= 0x80;
    LcdWriteCommand(temp,0);
}
//==========================��ĳ��λ����ʾһ���ַ�==============================
//============x--λ�õ�������   y--λ�õ�������data--��ʾ���ַ�����=============
void DisoneChar(uchar x,uchar y,uchar data) 
{
    LocateXY( x, y );			
    LcdWriteData( data );		
}
//==============================��Һ����ĳ��λ����������ʾһ���ַ�==============
//==============================y--λ�õ�������  x--λ�õ�������================
void DispStr(uchar x,uchar y,uchar *ptr) 
{
    uchar *temp;
    uchar i,n = 0;
    
    temp = ptr;
    while(*ptr++ != '\0')   n++;    //�����ַ�����Ч�ַ��ĸ���
    
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
//��Һ����ĳ��λ����������ʾN���ַ�
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
//========================��1602Һ��ģ����и�λ����============================
void LcdReset(void) 
{
    LcdWriteCommand(0x38, 0);	    //�涨�ĸ�λ����
    Delay5ms();
    LcdWriteCommand(0x38, 0);		
    Delay5ms();
    LcdWriteCommand(0x38, 0);
    Delay5ms();
    LcdWriteCommand(0x38, 1);		//��ʾģʽ����
    LcdWriteCommand(0x08, 1);		//��ʾ�ر�
    LcdWriteCommand(0x01, 1);	        //��ʾ����
    LcdWriteCommand(0x06, 1);		//д�ַ�ʱ���岻�ƶ�
    LcdWriteCommand(0x0c,1);		//��ʾ���������α꣬����˸
   
}
//==================================NEWMSG-JASK3000=============================
void NewmsgJASK3000()
{
     DisoneChar(0,1,0x4e) ; // now : XX.X ��
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
//=================================== AD��ѹ ��ʾ ================================
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
//=================================������======================================
void main(void)
{
   char i;
   WDTCTL = WDTPW + WDTHOLD; //��ֹ���Ź�
   InitSys();         // ʱ�ӳ�ʼ��
   nRF905_IO_set();   // NRF905�˿�����
   LED_IO_set();      //LED�˿�����
   LCD_IO_set();      //LCD�˿�����
   Config905();       //NRF905�Ĵ�������
   init_uart0();      //����0��ʼ��
   LcdReset();        //LCD��ʼ��  
   NewmsgJASK3000();
   LED1_0;LED2_0;
while(1)
   {
       RX();  //��������
    if(TxRxBuf[3])              //�������һ��
      {
        LED1_1;
	for(i=0;i<4;i++)
	{
	R_S_Byte(TxRxBuf[i]);     //�����ϴ��¶�
        NRF905_Delay(10);
	}
	}
      LED1_0;
      dy_xianshi();   //LCD��ѹ��ʾ
   }
}