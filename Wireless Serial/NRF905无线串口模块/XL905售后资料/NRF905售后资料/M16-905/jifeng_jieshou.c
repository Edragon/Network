//ICC-AVR application builder : 2007-8-11 20:37:32
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
//#define  nrf905_TX_EN	  PB0	   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0)
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0)
//#define  nrf905_TRX_CE  PD4	
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4)  
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4) 
//#define  nrf905_PWR     PB1 	  
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1) 
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1)
//#define  nrf905_MISO	  PB6   	
//#define  nrf905_MOSI    PB5	    
//#define  nrf905_SCK     PB7	  
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7)
//#define  nrf905_CSN     PB4			
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4)  
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4)				
//#define  nrf905_CD      PD3	
#define   Hign_nrf905_CD    PORTD |= (1 << PD3) 
#define   Low_nrf905_CD     PORTD &= ~(1 << PD3) 
#define   Read_nrf905_CD    PINB & (1 << PD3)
//#define  nrf905_AM      PB3	  
#define   Hign_nrf905_AM    PORTB |= (1 << PB3) 
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3)
#define   Read_nrf905_AM    PINB & (1 << PB3)
//#define  nrf905_DR      PB2  		
#define   Hign_nrf905_DR    PORTB |= (1 << PB2)
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2)
#define   Read_nrf905_DR    PINB & (1 << PB2)

#define   Read_KEY_2  	    PINA & (1 << PA5)        

#define   Read_KEY_3    	PINA & (1 << PA6)

#define   Read_KEY_4   	    PINA & (1 << PA7)   
//------------------------------------------------------------------
//#define Display1   PA1  		
#define   Hign_Display1     PORTA |= (1 << PA1);   
#define   Low_Display1    PORTA &= ~(1 << PA1); 
//#define Display2      PA2  		
#define   Hign_Display2     PORTA |= (1 << PA2);   
#define   Low_Display2    PORTA &= ~(1 << PA2); 
//#define Display3     PA3  		
#define   Hign_Display3     PORTA |= (1 << PA3);   
#define   Low_Display3     PORTA &= ~(1 << PA3); 
//#define Display4      PA4 		
#define   Hign_Display4     PORTA |= (1 << PA4);   
#define   Low_Display4     PORTA &= ~(1 << PA4); 
//--------------------------------------------------------------------
#define   Hign_BELL  PORTD |= (1 << PD5);   
#define   Low_BELL     PORTD &= ~(1 << PD5); 
//---------------------------------------------------------------------
#define   Hign_JDQ  PORTD |= (1 << PD7)
#define   Low_JDQ     PORTD &= ~(1 << PD7)
//-------------------------------------------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------------------------------------
uchar TxRxBuf[4];
//---------------------------------------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
uchar tf;
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9¶ÎÂë
//------------------------------------------------------------------------------
//----------------------------------¼Ä´æÆ÷ÅäÖÃ----------------------------------
uchar RFConf[11]=
{
  0x00,                             
  0x5f,                            
  0x0c,                            
  0x44,                             
  0x04,0x04,                        
  0xCC,0xCC,0xCC,0xCC,             		  
  0x58, 
};
//----------------------------------º¯ÊýÉêÃ÷------------------------------------
void Delay(uint x);
void Spi_initial();
uchar SpiReadSpiWrite(uchar DATA);
void system_Init(void);
void Config905(void);
void TxPacket(uchar TxBUF[4]);
void SetTxMode(void);
void TX(void);
void StartUART(void);
void R_S_Byte(uchar R_Byte);
//-----------------------------------------------------------
void Delay(uint x)
{
	uint i;
	while(x--)
	for(i=0;i<30;i++);
}
//-------------------------------------------------------------------
void Spi_initial()
{
	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);   
}
//------------------------------------------------------------------	
uchar SpiReadSpiWrite(unsigned char cData)//r
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF) ))
	{};			
	return SPDR;
}
//----------------------------------------------------------------
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
//--------------------------------NRF905¼Ä´æÆ÷³õÊ¼»¯º¯Êý------------------------
void Config905(void)
{
	uchar i;
	Low_nrf905_CSN;	
	Delay(1);				
	SpiWrite(WC);				
	for (i=0;i<11;i++)			
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//------------------------------------------------------------
void TxPacket(uchar TxBUF[4])
{
	uchar i;
	Low_nrf905_CSN;		   						
	SpiReadSpiWrite(WTP);			
	for (i=0;i<4;i++)
	{
	SpiReadSpiWrite(TxBUF[i]);		
	}						
	Hign_nrf905_CSN;
	Delay(1);							
	Low_nrf905_CSN;							
	SpiReadSpiWrite(WTA);				
	for (i=0;i<4;i++)					
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	Hign_nrf905_CSN;					
	Hign_nrf905_TRX_CE;											
	Low_nrf905_TRX_CE;						
}
//-----------------------------------------------------------------
void SetTxMode(void)
{
	Low_nrf905_TRX_CE;			
	Hign_nrf905_TX_EN;				
	Delay(1); 				
}
//------------------------------------------------------------------------
//-------------------------------------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(100); 				
}
//------------------------------------------------------------------
void RxPacket(void)					
{
	uchar i;
   	Low_nrf905_TRX_CE;
	Low_nrf905_CSN;						
   	Delay(1);
	SpiReadSpiWrite(RRP);				 
	for (i = 0 ;i < 4 ;i++)
	{   
	TxRxBuf[i]=SpiReadSpiWrite(0);	   
	}
	Hign_nrf905_CSN;
    Delay(2);                            //
	Hign_nrf905_TRX_CE;							
}
//------------------------------------------------------------------
void  RX(void)
{
    SetRxMode();			         
	RxPacket();                     
	Delay(10);
	if(TxRxBuf[0]==0x29)
	{
	 PORTC=seg[1];
	 Low_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Hign_Display1;
	}
	if(TxRxBuf[0]==0x30)
	{
	 PORTC=seg[2];
	 Hign_Display4;
	 Low_Display3;
	 Hign_Display2;
	 Hign_Display1;
	}
	if(TxRxBuf[0]==0x31)
	{
	 PORTC=seg[3];
	 Hign_Display4;
	 Hign_Display3;
	 Low_Display2;
	 Hign_Display1;

	}
}
//------------------------------Ö÷º¯Êý------------------------------------------
void main(void)
{  
	uint i,j,temp[32];
	DDRD=0xf2;		
	DDRB=0xB3;		
	DDRA=0x1e;      
	DDRC=0xff; 		
	PORTA=0x00;
	PORTC=0xbf;
	Hign_BELL;
	Hign_JDQ ;
	Spi_initial();
	system_Init();
	Config905();
	while(1)
 {
     RX();
//------------------------------------------------------------------------------
	if((PINA & 0x20) == 0)		 
	{
	while(!(PINA & 0x20));   			
	 TxRxBuf[0]=0x29;
	 tf=1;   
	 PORTC=seg[1];
	 Low_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Hign_Display1;
	 }
//------------------------------------------------------------------------------
	if((PINA & 0x40) == 0)			
	{
	while(!(PINA & 0x40));   		
 	 TxRxBuf[0]=0x30; 
	 tf=1;    
	 PORTC=seg[2];
	 Hign_Display4;
	 Low_Display3;
	 Hign_Display2;
	 Hign_Display1;
	 }
//------------------------------------------------------------------------------
	if((PINA & 0x80) == 0)			
	{
	while(!(PINA & 0x80));   			
 	 TxRxBuf[0]=0x31;
	 tf=3;
	 PORTC=seg[3];
	 Hign_Display4;
	 Hign_Display3;
	 Low_Display2;
	 Hign_Display1;
	}
//------------------------------------------------------------------------------
	if(tf)
	{
	tf=0;
	Low_JDQ ;
	//--------------------------------------------------------
	SetTxMode();				
	TxPacket(TxRxBuf);				
	//-------------------------------------------------
	TxRxBuf[0]=0;
	 }
	 //****************************************************************

	Hign_BELL;
	Hign_JDQ ;															
}
}