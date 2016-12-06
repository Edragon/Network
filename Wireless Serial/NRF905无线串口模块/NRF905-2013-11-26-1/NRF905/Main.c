/*
 * NRF905ģ��
 * 
 * ��;��NRF905ģ����Գ���
 * 
 * ����					����				��ע
 * Huafeng Lin			2013/11/26			����
 * Huafeng Lin			2013/11/26			�޸�
 * 
 */

#include <reg52.h>
#include <ABSACC.h>
#include <intrins.h>
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------
#define uint unsigned int
#define uchar unsigned char
//----------------------------------------------------------------------------------------------------------------
#define BYTE_BIT0	0x01
#define BYTE_BIT1	0x02
#define BYTE_BIT2	0x04
#define BYTE_BIT3	0x08
#define BYTE_BIT4	0x10
#define BYTE_BIT5	0x20
#define BYTE_BIT6	0x40
#define BYTE_BIT7	0x80
//----------------------------------------------------------------------------------------------------------------
bdata unsigned  char DATA_BUF;
#define DATA7	((DATA_BUF&BYTE_BIT7) != 0)
#define DATA0   ((DATA_BUF&BYTE_BIT0) != 0)
sbit	flag	=DATA_BUF^7;
sbit	flag1	=DATA_BUF^0;
//---------------------------------------------------�������ݻ�����-------------------------------------------------
#define TxRxBuf_Len 4
unsigned char TxRxBuf[TxRxBuf_Len]=
{
0x29,0x30,0x31,0x32,
};
//---------------------------------------------------���ÿڶ���---------------------------------------------------
//���ÿڶ���
sbit	TXEN=P3^7;
sbit	TRX_CE=P1^4;
sbit	PWR=P3^6;
sbit	MISO=P1^0;
sbit	MOSI=P1^3;
sbit	SCK=P1^2;
sbit	CSN=P1^5;

sbit	AM=P1^6;
sbit	DR=P1^1;
sbit	CD=P3^5;
//----------------------------------------------------����--------------------------------------------------

sbit    KEY0    =P3^0;
sbit    KEY1    =P3^1;
//----------------------------------------------------�����λ����-------------------------------------------------------
sbit    led0    =P1^7;
sbit    led1    =P3^4;
//-----------------------------------------------------------------------------------------------------------------
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9����
//-------------------------------------------------------nrf905����ָ��-------------------------------------------
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//------------------------------------------------NRF905�Ĵ�������------------------------------------------------
unsigned char idata RFConf[11]=
{
  0x00,                             	//��������
  0x4c,                             	//CH_NO,����Ƶ����430MHZ
  0x0c,                             	//�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
  0x44,                             	//��ַ������ã�Ϊ4�ֽ�
  0x04,0x04,                        	//���շ�����Ч���ݳ���Ϊ32�ֽ�
  0xCC,0xCC,0xCC,0xCC,              	//���յ�ַ
  0x58,                              	//CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
};
code TxAddress[4]={0xcc,0xcc,0xcc,0xcc};
char tf;
//------------------------------------------------��ʱ------------------------------------------------------------
static void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//---------------------------------------------------SPI������-----------------------------------------------------
unsigned char SpiRead(void)
{
	unsigned char j;
	for (j=0;j<8;j++)
	{
        DATA_BUF=DATA_BUF<<1;
		SCK=1;
		if (MISO)						//��ȡ���λ����������ĩβ��ͨ������λ��������ֽ�
		{
			DATA_BUF|=BYTE_BIT0;
		}
		else
		{
			DATA_BUF&=~BYTE_BIT0;
		}
		SCK=0;
	 }
	 return DATA_BUF;
}
//-------------------------------------------------SPIд����----------------------------------------------------------
void SpiWrite(unsigned char send)
{
	unsigned char i;
	DATA_BUF=send;
	for (i=0;i<8;i++)
	{
		if (DATA7)	//���Ƿ������λ
		{
			MOSI=1;
		}
		else
		{
			MOSI=0;
		}
		SCK=1;
		DATA_BUF=DATA_BUF<<1;
		SCK=0;
	}
}
//------------------------------------------------------��ʼ��nRF905---------------------------------------------
void nRF905Init(void)
{
    CSN=1;						// Spi 	disable
	SCK=0;						// Spi clock line init low
	DR=0;						// Init DR for input
	AM=0;						// Init AM for input
	CD=0;						// Init CD for input
	PWR=1;						// nRF905 power on
	TRX_CE=0;					// Set nRF905 in standby mode
	TXEN=0;						// set radio in Rx mode
}
//-----------------------------------------------------��ʼ���Ĵ���-----------------------------------------------
void Config905(void)
{
	uchar i;
	CSN=0;						// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config commandд����������
	for (i=0;i<11;i++)			// Write configration words  д��������
	{
	   SpiWrite(RFConf[i]);
	}
	CSN=1;						// Disable Spi
}
//-----------------------------------------------------�������ݴ��---------------------------------------------------
void TxPacket(uchar *TxRxBuf)
{
	uchar i;
	//Config905();
	CSN=0;
	SpiWrite(WTP);					// Write payload command
	for (i=0;i<4;i++)
	{
		SpiWrite(TxRxBuf[i]);		// Write 32 bytes Tx data
	}// Spi enable for write a spi command
	CSN=1;
	Delay(1);						// Spi disable
	CSN=0;							// Spi enable for write a spi command
	SpiWrite(WTA);					// Write address command
	for (i=0;i<4;i++)				// Write 4 bytes address
	{
		SpiWrite(TxAddress[i]);
	}
	CSN=1;							// Spi disable
	TRX_CE=1;						// Set TRX_CE high,start Tx data transmission
	Delay(1);						// while (DR!=1);
	TRX_CE=0;						// Set TRX_CE low
}
//----------------------------------------------------------���÷���״̬---------------------------------------------
void SetTxMode(void)
{
	TRX_CE=0;
	TXEN=1;
	Delay(1); 						// delay for mode change(>=650us)
}
//-----------------------------------------------���÷���״̬---------------------------------------------------
void SetRxMode(void)
{
	TXEN=0;
	TRX_CE=1;
	Delay(1); 						// delay for mode change(>=650us)
}
//-------------------------------------------------�ж����ݽ���״̬-----------------------------------------------------
unsigned char CheckDR(void)			//����Ƿ��������ݴ��� Data Ready
{
	if (DR=1&&TRX_CE==1 && TXEN==0)
	{
       // Delay(50)  ;
		return 1;
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------��NRF905��������------------------------------------------------------------
void RxPacket(void)						
{
	uchar i;
    Delay(1);
//	TRX_CE=0;						// Set nRF905 in standby mode
    Delay(100);
    TRX_CE=0;
	CSN=0;							// Spi enable for write a spi command
    Delay(1);
	SpiWrite(RRP);
	for (i = 0 ;i < 4 ;i++)
	{ 
		TxRxBuf[i]=SpiRead();		// Read data and save to buffer       
	}
	CSN=1;
    Delay(10);
	TRX_CE=1;							
}
//--------------------------------------------------------���ݽ���------------------------------------------------
void  RX(void)
{
          SetRxMode();				// Set nRF905 in Rx mode
          while (CheckDR()==0);
		  Delay(10);
	  	  RxPacket();
		  if(TxRxBuf[0]==0x29)
		  {
				led0=0;
				led1=1;
			
		  }
		  if(TxRxBuf[1]==0x29)
		  {
				led0=1;
				led1=0;
			
		  }
}
//-----------------------------------------------------------------------------------------------------------------
void main(void)
{
        nRF905Init();
     	Config905();
		led0=0;
		led1=0;
		
        while(1)
		{
			RX();
		   if(KEY0 ==0 )
			 {	
				tf = 1 ;
				TxRxBuf[0]=0x29;
				TxRxBuf[1]=0x30;

				led0=0;
				led1=1;
			
				 }
		   if(KEY1 ==0 )
			 {	tf = 1 ; 
				TxRxBuf[0]=0x30;
				TxRxBuf[1]=0x29;

				led0=1;
				led1=0;

		 		}
	       if (tf==1)
			{
                SetTxMode();		// Set nRF905 in Tx mode
			    TxPacket(TxRxBuf);	// Send data by nRF905
				tf = 0;	
				Delay(100);
			}
		Delay(100);
		led1=1;
		led0=1;	
		Delay(100);
	}
}