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
//==================================BELL========================================
#define  BELL_0     P6OUT &=~BIT3          //���0
#define  BELL_1     P6OUT |= BIT3          //���1
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
	Delay(1); 		// delay for mode change(>=650us)
}
//=================================���ݽ���=====================================
void RxPacket(void)						
{
    char i;
    Delay(1);
    Delay(100);
    TRX_CE_0;
    CSN_0;		// SPIʹ�ܣ�Spi enable for write a spi command��
    Delay(1);
    SpiWrite(RRP);      // ��SPI�������Read payload command��
for (i = 0 ;i <4 ;i++)
    {  
      RxBuf[i]=SpiRead();		// Read data and save to buffer    
    }
    CSN_1;
    Delay(10);
    TRX_CE_1;							
}

//==========================NRF905���ݽ�������================================
void  RX(void)
{
    SetRxMode();			// Set nRF905 in Rx mode
//  while (CheckDR()==0);
    Delay(10);
    RxPacket();		// Recive data by nRF905
    Delay(10);
//=============================================================================
    if(RxBuf[0]==0x29)
    {
     LED1_1;
     BELL_0;
    }
    if(RxBuf[0]==0x30)
    {
     LED1_0;
     BELL_1;
    }
    RxBuf[0]=0x00;
}
//==================================������=====================================
void main(void)
{
   char tf;
   WDTCTL = WDTPW + WDTHOLD; 
   InitSys();
   nRF905_IO_set();
   LED_IO_set();
   BELL_IO_set();
   KEY_IO_set();       //KEY�˿�����
   Config905();
   LED1_1;LED2_1;BELL_1;
while(1)
   {
    RX();//��������
//==================================================
    if((P1IN&0x01))   //��ⰴ��
      {	
        TxBuf[0]=0x29;tf = 1 ; LED2_0;
      }
      if((P1IN&0x02) )		 
      {	
        TxBuf[0]=0x30;tf = 1 ; LED2_1;
      }
     if(tf==1)      //�а�����������
      {
         SetTxMode(); TxPacket(TxBuf);
         tf = 0;	
         TxBuf[0]=0x00;
      }	 
   }
}