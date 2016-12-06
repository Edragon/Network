#include "pic.h"

#define uchar unsigned char
#define uint unsigned int
//****************************************************************
#define TX_EN	RC1 				
#define TRX_CE  RC2					
#define PWR     RB1					
//*****************************************************************
#define  MISO	RC4   					
#define  MOSI   RC5						
#define  SCK    RC3						
#define  CSN    RC0						
//****************************************************************
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
//****************************************************************
void Delay(uchar x);
void Spi_initial();
uchar SpiReadSpiWrite(uchar DATA);
void system_Init(void);
void Config905(void);
void TxPacket(void);
void SetTxMode(void);
unsigned char CheckCD(void);
void TX(void);
void StartUART(void);
void R_S_Byte(uchar R_Byte);
//****************************************************
uchar TxRxBuf[32]=			  
{
0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,
0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,
0x25,0x26,0x27,0x28,0x29,0x30,0x31,0x32,
};
//***************************************************************
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };   
//***************************************************************
uchar RFConf[11]=
{
  0x00,                             
  0x5F,                             
  0x2C,                            
  0x44,                            
  0x20,0x20,                        
  0xCC,0xCC,0xCC,0xCC,             
  0x58,                             
};
//********************************—” ±**************************************
void Delay(uchar x)               
{
	uchar i;
	while(x--)
	for(i=0;i<30;i++);
}
//****************************************************************
void Spi_initial()
{ 
	INTCON=0x00;		
	PIR1=0x00;		
	SSPCON=0x20;		
	SSPSTAT=0xc0;		
	SSPIF=0;		 
}
//*********************************************************************	
uchar SpiReadSpiWrite(uchar DATA)//r
{
	uchar b;
	Spi_initial();
	SSPBUF=DATA;	 	
	do
	{
	;
	}
	while(SSPIF==0);
	SSPIF=0;	
	b=SSPBUF;	
	return b;
	}
//*********************************************************************
void system_Init(void)			//r
{
	TRISA=0x00;
	TRISB=0x0D;
	TRISC=0x90;
	TRISD=0x00;
	TRISE=0x00;	
	ADCON1=0x07;		//
   	CSN=1;				// Spi 	disable
	SCK=0;				// Spi clock line init low
	DR=0;				// Init DR for input
	AM=0;				// Init AM for input
	CD=0;				// Init CD for input
	PWR=1;				// nRF905 power on
	TRX_CE=0;			// Set nRF905 in standby mode
	TX_EN=0;			// set radio in Rx mode
}
//********************************≥ı ºªØºƒ¥Ê∆˜********************************
void Config905(void)
{
	uchar i;
	CSN=0;	
	Delay(1);				
	//SpiWrite(WC);				
	for (i=0;i<11;i++)			
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	CSN=1;					// Disable Spi
}
//****************************************************************
void TxPacket(void)
{
	uchar i;
	CSN=0;
	Delay(1);
	SpiReadSpiWrite(WTP);			   
	for (i=0;i<32;i++)
	{
	SpiReadSpiWrite(TxRxBuf[i]);		
	}							
	CSN=1;								// Spi disable
	Delay(1);					
	CSN=0;						    	// Spi enable for write a spi command
	SpiReadSpiWrite(WTA);				
	for (i=0;i<4;i++)		         	
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	CSN=1;						      
	TRX_CE=1;					
	Delay(1);			           
	TRX_CE=0;				       
}
//*******************************************************************************
void SetTxMode(void)				
{
	TRX_CE=0;			    	//
	TX_EN=1;			    
	Delay(1); 				  
}
//********************************************************************************
void TX(void)
{
    SetTxMode();			
	TxPacket();		    	
}
//*************************************************************
void StartUART(void)
{
	TXSTA=0x04;				
	PIE1=0; 			
	RCSTA=0x80; 		
	TRISC=TRISC|0X80;  	
	TRISC=TRISC&0XBF;  	
	TXEN=1;			
}
//**************************************************************
void R_S_Byte(uchar R_Byte)
{	
     	TXREG= R_Byte;  
}
//*********************************************************************
main()
{

	PORTE=0xff;			
	PORTD=0xbf;          
	StartUART();			
	system_Init();			
	Config905();			
	W1=0;	W2=0;	W3=0; W4=0;
	while(1)
	{
	TX();					

	}	
}
