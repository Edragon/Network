#include "pic.h"
//****************************************************************************
#define uchar unsigned char
#define uint unsigned int
//***************************************************************
#define TX_EN	RC1 				
#define TRX_CE  RC2					
#define PWR     RB1					
//*****************************************************************
#define  MISO	RC4   				
#define  MOSI   RC5					
#define  SCK    RC3						
#define  CSN    RC0						
//*****************************************************************
#define  CD     RB2						
#define  AM     RB3						
#define  DR     RB0						
//****************************************************************
#define  W1     RB7						
#define  W2		RB6						
#define  W3		RB5						
#define  W4		RB4					
//**************************************************************
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//********************************************************************
void Delay(uchar n);
void Spi_initial();
uchar SpiReadSpiWrite(uchar DATA);
void nRF905Init(void);
void Config905(void);
void SetRxMode(void);
uchar CheckDR(void);
void RxPacket(void);
void RX(void);
void StartUART( void );
void R_S_Byte(uchar R_Byte);
//********************************************************************
uchar RFConf[11]=
{
  0x00,                           	
  0x5F,								
  0x2c,								 
  0x44,				               
  0x20,0x20,						
  0xcc,0xcc,0xcc,0xcc,				
  0x58,                            	
};
//**********************************************************8*********
uchar TxRxBuffer[32];
//***********************************************************************
void Delay(uchar n)
{
	uchar k;
	while(n--)
	for(k=0;k<80;k++);
}
//*********************************************************************
void Spi_initial()
{
	TRISC=TRISC&0xDF;		
	TRISC=TRISC&0xF7;		
	TRISC=TRISC|0x10;		  
	INTCON=0x00;			
	PIR1=0x00;			
	SSPCON=0x20;			
	SSPSTAT=0xc0;			
	SSPIF=0;			
}
//*********************************SPI读写*************************************	
uchar SpiReadSpiWrite(uchar DATA)	//r
{
	uchar b;
	Spi_initial();
	SSPBUF=DATA;	 		//写入要发送数据发送的同时也得到数据
	
	while(SSPIF==0);
	SSPIF=0;	
	b=SSPBUF;		
	return b;
	}
//*********************************************************
void system_Init(void)			//r
{
  	TRISA=0x00;
	TRISB=0x0D;
	TRISC=0x90;
	TRISD=0x00;
	TRISE=0x00;	
   	CSN=1;				// Spi 	disable
	SCK=0;				// Spi clock line init low
	DR=0;				// Init DR for input
	AM=0;				// Init AM for input
	CD=0;				// Init CD for input
	PWR=1;				// nRF905 power on
	TRX_CE=0;			// Set nRF905 in standby mode
	TX_EN=0;			// set radio in Rx mode
}
//*********************************************************
void Config905(void)
{
	uchar i;
	CSN=0;				// Spi enable for write a spi command
	for (i=0;i<11;i++)
	{
	   SpiReadSpiWrite(RFConf[i]);
	}
	CSN=1;				// Disable Spi
}
//**************************************************************************
void SetRxMode(void)
{
	TX_EN=0;
	Delay(1); 
	TRX_CE=1;
	Delay(1); 			// delay for mode change(>=650us)
}
//**************************************************************************
void RxPacket(void)						
{
	uchar i;
   	Delay(1);
   	TRX_CE=0;
	CSN=0;					// Spi enable for write a spi command
   	Delay(1);
	SpiReadSpiWrite(RRP);
	for (i = 0 ;i < 32 ;i++)
	{
	TxRxBuffer[i]=SpiReadSpiWrite(0);	// Read data and save to buffer
   	}
	CSN=1 ;
    while (AM||DR);				
	TRX_CE=1;							
}
//*****************************************************************************
void  RX(void)
{
    SetRxMode();		
    while(DR==0);		
    Delay(1);			
	RxPacket();			
	Delay(1);
}
//*********************************************************************
void StartUART(void)
{  	
	TXSTA=0x04;		 	
	SPBRG=103; 			
	PIE1=0; 			
	RCSTA=0x80; 		
	TRISC=TRISC|0X80;  	
	TRISC=TRISC&0XBF;  	
	TXEN=1;				
}
//************************************************************************
void R_S_Byte(uchar R_Byte)
{	
     	TXREG= R_Byte;  
}
//*********************************************************************************
void main(void)
{
   	char i,count;
	PORTE=0xff;             
	PORTD=0xff;				

    StartUART();			
	system_Init();			
	Delay(10);
	Config905();			
	W1=0;W2=0;W3=0;W4=0;
	while(1)
	{
		RX();				
		if(TxRxBuffer[0])
		{
		for(i=0;i<32;i++)	
		{
		R_S_Byte(TxRxBuffer[i]);
		Delay(20);
		}
		}
		count++;
		if(count==4)
		{
		count=0;	
		}
		switch(count)
		{
		case 	0x01:	
		PORTD=	0xbf;
		break;	
		case 	0x02:	 
 	   
		PORTD=	0xf7;
		break;	
		case 	0x03:
		PORTD=	0xfe;
	  	break;	
		default:  break;
		}
	}
}


