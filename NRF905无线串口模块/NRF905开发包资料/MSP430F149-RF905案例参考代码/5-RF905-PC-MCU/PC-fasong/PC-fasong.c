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
//===================================LED========================================
#define  LED1_0     P6OUT &=~BIT1          //���0
#define  LED1_1     P6OUT |= BIT1          //���1
#define  LED2_0     P6OUT &=~BIT2          //���0
#define  LED2_1     P6OUT |= BIT2          //���1
//==================================BELL========================================
#define  BELL_0     P6OUT &=~BIT3          //���0
#define  BELL_1     P6OUT |= BIT3          //���1
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
//===========================NRF905:SPIָ��=====================================
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//==========================32�ֽڷ��������շ�������============================
#define TxRxBuf_Len 4
char TxBuf[TxRxBuf_Len];
char RxBuf[TxRxBuf_Len];
//==========================NRF905��10�Ĵ�������================================
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
char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};
char DATA_BUF;
char MARK;
/*****************************************************************************
ϵͳ��ʼ��
******************************************************************************/
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
//==========================��ʱ================================================
void Delay(uchar n)
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
//=========================NRF905װ�ص�ַ+���ݴ��+���ݷ���=====================
void TxPacket(char *data_Bufer)
{
	uchar i;
	CSN_0;
	SpiWrite(WTP);				// ��������װ������
	for (i=0;i<4;i++)
	{
	  SpiWrite(data_Bufer[i]);
	}
	CSN_1;                                  // �ر�SPI
	Delay(1);		
	CSN_0;					// ��SPI
	SpiWrite(WTA);				// д���ַҪ�ͽ��շ���ַһ��
	for (i=0;i<4;i++)			// 4�ֽڵ�ַ
	{
	  SpiWrite(TxAddress[i]);
	}
	CSN_1;					//�ر�SPI
	TRX_CE_1;					// Set TRX_CE high,start Tx data transmission
	Delay(10);	// while (DR!=1); ��ʱʱ�䲻��̫��
	TRX_CE_0;					// Set TRX_CE low
}
//==================================����ģʽ��ʼ��-=============================
void SetTxMode(void)
{
	TRX_CE_0;
	TXEN_1;
	Delay(1); 					// Delay for mode change(>=650us)
}

//======================���ڳ�ʼ��==============================================
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
    IE1 |= URXIE0;   //����0�����ж�ʹ��
//   IE1 |= UTXIE0;   //����0�����ж�ʹ��
//===================�˿ڵڶ�����ʹ��=========================================
    P3SEL |=BIT4;    //����P3��4ΪUART0 ��TXD
    P3SEL |=BIT5;    //����P3��5ΪUART0 ��RXD
    P3DIR |=BIT4;    //����P3��4Ϊ���
    _EINT();        //��ȫ���жϿ��ƣ�������Ҫ�򿪣��������α���
  }
//======================���ڽ����жϷ�����====================================
#if __VER__ < 200
  interrupt [UART0RX_VECTOR] void  UART0_RX_ISR(void)
#else
  #pragma vector=UART0RX_VECTOR
  __interrupt void UART0_RX_ISR(void)
#endif
{
  while ((IFG1 & URXIFG0) == 1);//�жϱ�־        
  if((U0RCTL&RXERR)==0)          //û�н��ճ���
  {
  MARK = RXBUF0; // RXBUF0 to TXBUF0
  //delay(500);
  TXBUF0=MARK;
  IFG1=IFG1&0xef;
  }
}
//==================================������=====================================
void main(void)
{
   char tf;
   WDTCTL = WDTPW + WDTHOLD; 
   InitSys();
   nRF905_IO_set();
   LED_IO_set();        //LED�˿�����
   BELL_IO_set();
   KEY_IO_set();       //KEY�˿�����
   Config905();
   init_uart0();
   LED1_1;LED2_1;BELL_1;
while(1)
   {
    if(MARK==48)		//0��0�� ASCII��Ϊ48
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
     if (tf==1)//�����յ�PC��ָ���������
	{
         SetTxMode(); TxPacket(TxBuf);
         tf = 0;  MARK=0;
          TxBuf[0]=0x00;
	}	 
   }
}