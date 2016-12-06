//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
//---------------------------------NRF905Ä£Ê½¿ØÖÆ¶¨Òå---------------------------------
//#define  nrf905_TX_EN	  PB0	    //Êä³ö1
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
//#define  nrf905_TRX_CE  PD4 	    //Êä³ö1
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4);   
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4); 
//#define  nrf905_PWR     PB1 	    //Êä³ö1
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1);   
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1); 
//--------------------------------NRF905-SPI¿Ú½Ó¿Ú¶¨Òå--------------------------
//#define  nrf905_MISO	  PB6   	//ÊäÈë0
//#define  nrf905_MOSI    PB5	    //Êä³ö1
//#define  nrf905_SCK     PB7	    //Êä³ö1
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7); 
//#define  nrf905_CSN     PB4		//Êä³ö1		
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4);   
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4); 						
//-------------------------------NRF905×´Ì¬Êä³ö¿Ú-------------------------------
//#define  nrf905_CD      PD3	    //ÊäÈë0
#define   Hign_nrf905_CD    PORTD |= (1 << PD3);   
#define   Low_nrf905_CD     PORTD &= ~(1 << PD3); 
#define   Read_nrf905_CD    PINB & (1 << PD3);
//#define  nrf905_AM      PB3	    //ÊäÈë0
#define   Hign_nrf905_AM    PORTB |= (1 << PB3);   
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3); 
#define   Read_nrf905_AM    PINB & (1 << PB3);
//#define  nrf905_DR      PB2  		//ÊäÈë0
#define   Hign_nrf905_DR     PORTB |= (1 << PB2);   
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2); 
#define   Read_nrf905_DR    PINB & (1 << PB2);   
//------------------------------ÊıÂë¹ÜÎ»Ñ¡--------------------------------------
//#define Display1   PA1  		    //Êä³ö1
#define   Hign_Display1     PORTA |= (1 << PA1);   
#define   Low_Display1    PORTA &= ~(1 << PA1); 
//#define Display2      PA2  		//Êä³ö1
#define   Hign_Display2     PORTA |= (1 << PA2);   
#define   Low_Display2    PORTA &= ~(1 << PA2); 
//#define Display3     PA3  		//Êä³ö1
#define   Hign_Display3     PORTA |= (1 << PA3);   
#define   Low_Display3     PORTA &= ~(1 << PA3); 
//#define Display4      PA4 		//Êä³ö1
#define   Hign_Display4     PORTA |= (1 << PA4);   
#define   Low_Display4     PORTA &= ~(1 << PA4);   
//-------------------------------BELL·äÃ÷Æ÷-------------------------------------
#define   Hign_BELL  PORTD |= (1 << PD5);   
#define   Low_BELL     PORTD &= ~(1 << PD5); 
//-------------------------------JDQ¼ÌµçÆ÷--------------------------------------
#define   Hign_JDQ  PORTD |= (1 << PD7)
#define   Low_JDQ     PORTD &= ~(1 << PD7) 

//----------------------------------NRF905-SPIÖ¸Áî------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------·¢ËÍÊı¾İ-------------------------------------
uchar TxRxBuffer[4];
//----------------------------------½ÓÊÕµØÖ·------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
uint temp[6];
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9¶ÎÂë
uchar seg1[10]={0x40,0x4F,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; 
//----------------------------------¼Ä´æÆ÷ÅäÖÃ----------------------------------
uchar RFConf[11]=
{
  0x00,                            //ÅäÖÃÃüÁî//
  0x4c,                           //CH_NO,ÅäÖÃÆµ¶ÎÔÚ430MHZ
  0x0C,                          //Êä³ö¹¦ÂÊÎª10db,²»ÖØ·¢£¬½ÚµçÎªÕı³£Ä£Ê½
  0x44,                         //µØÖ·¿í¶ÈÉèÖÃ£¬Îª4×Ö½Ú
  0x04,0x04,                   //½ÓÊÕ·¢ËÍÓĞĞ§Êı¾İ³¤¶ÈÎª4×Ö½Ú
  0xCC,0xCC,0xCC,0xCC,        //½ÓÊÕµØÖ·
  0x58,                      //CRC³äĞí£¬8Î»CRCĞ£Ñé£¬Íâ²¿Ê±ÖÓĞÅºÅ²»Ê¹ÄÜ£¬16M¾§Õñ
};
//----------------------------------NRF905º¯ÊıÉêÃ÷------------------------------
void Delay(uint x);						       //ÑÓÊ±×Ó³ÌĞò																							
void Spi_initial();                            //SPI³õÊ¼»¯
uchar SpiReadSpiWrite(unsigned char cData);    //SPI¶ÁĞ´×Ó³ÌĞò
void system_Init(void);		   				   //ÏµÍ³³õÊ¼»¯
void Config905(void);						   //NRF905³õÊ¼»¯×Ó³ÌĞò
void SetRxMode(void);						   //
unsigned char CheckDR(void);
void RxPacket(void);
void  RX(void);
//-------------------------------´®¿Úº¯ÊıÉêÃ÷-----------------------------------
void StartUART(void);
void R_S_Byte(uchar R_Byte);
//----------------------------------100usÑÓÊ±×Ó³ÌĞò-----------------------------
void Delay(uint x)
{
	uint i;
	while(x--)
	for(i=0;i<80;i++);
}
//----------------------------------SPI³õÊ¼»¯-----------------------------------
void Spi_initial()
{
	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);// Ö÷»úÄ£Ê½£¬fck/16, SPI·½Ê½0
}
//---------------------------------SPI¶ÁĞ´³ÌĞò----------------------------------	
uchar SpiReadSpiWrite(unsigned char cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF) ))  // µÈ´ıSPI·¢ËÍÍê±Ï
	{};			
	return SPDR;
}
//--------------------------------ÏµÍ³×´Ì¬³õÊ¼»¯--------------------------------
void system_Init(void)			
{

   	Hign_nrf905_CSN;			// SPIÊ¹ÄÜ
	Low_nrf905_SCK;				
	Low_nrf905_DR;				// DR=0
	Low_nrf905_AM;				// AM=0
	Low_nrf905_CD;				// CD=0
	Hign_nrf905_PWR;		    // PWR=1
	Low_nrf905_TRX_CE;			// nrf905_TRX_CE=0
	Low_nrf905_TX_EN ;			// nrf905_TX_EN=0
}
//--------------------------------NRF905¼Ä´æÆ÷³õÊ¼»¯º¯Êı------------------------
void Config905(void)
{
	uchar i;
	Low_nrf905_CSN;				//SPIÊ¹ÄÜ											
	Delay(1);				   
	for (i=0;i<11;i++)			//Ğ´RF905ÅäÖÃ×Ö
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//------------------------------ÉèÖÃ½ÓÊÕÄ£Ê½¼¤·¢--------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(10); 					// delay for mode change(>=650us)
}
//-----------------------------ÅĞ¶ÏÊÇ·ñÊÕµ½Êı¾İ---------------------------------
unsigned char CheckDR(void)		//¼ì²éÊÇ·ñÓĞĞÂÊı¾İ´«Èë 
{
	if (PINB & (1 << PB2))
	{
		return 1; 	 	  		//ÊÕµ½Êı¾İ
	}
	else
	{
		return 0;
	}
}
//-----------------------------------¶Á½ÓÊÕÊı¾İ°ü-------------------------------
void RxPacket(void)							//¶ÁÊı¾İ
{
	uchar i;
    Low_nrf905_TRX_CE;
	Low_nrf905_CSN;						    // Ê¹ÄÜSPI
    Delay(1);
	SpiReadSpiWrite(RRP);				   // Ğ´ÈëÊı¾İ½ÓÊÕ»º³åÇøÊı¾İÃüÁî
	for (i = 0 ;i < 4 ;i++)
	{   
	TxRxBuffer[i]=SpiReadSpiWrite(0);	  // ¶ÁÈ¡Êı¾İ½ÓÊÕ»º³åÇøÊı¾İ       
	}
	Hign_nrf905_CSN;
    Delay(2);                            //
	Hign_nrf905_TRX_CE;							
}
//--------------------------------ÉèÖÃ½ÓÊÕÄ£Ê½----------------------------------
void  RX(void)
{
    SetRxMode();			          //ÉèÖÃNRF905½ÓÊÕÄ£Ê½
    while (CheckDR()==0);	         //µÈ´ı½ÓÊÕÍê³É
	RxPacket();                     //¶ÁÈ¡½ÓÊÕÊı¾İ»º³åÇø
	Delay(10);
}

//----------------------------ÎÂ¶ÈLEDÔÊ¾½çÃæ-----------------------------------
void  dis_zhuye()
{
	 PORTC=seg[TxRxBuffer[2]];
	 Hign_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Low_Display1;
	 Delay(80);
	 Hign_Display1;
//------------------------------------------------------------------------------
	 PORTC=seg1[TxRxBuffer[1]];
	 Low_Display2;
	 Delay(80);
	 Hign_Display2;
//------------------------------------------------ ---------------------------
	 PORTC=seg[TxRxBuffer[0]];
	 Low_Display3;
	 Delay(80);
	 Hign_Display3;
//----------------------------------------------------------------------------- 
	 PORTC=0xc6;
	 Low_Display4;
	 Delay(80);
	 Hign_Display4;	 
//------------------------------------------------------------------------------ 	
}
//-------------------------------´®¿Ú³õÊ¼»¯-------------------------------------
void StartUART(void)
{
 	 UCSRA=0x00;	
	 UCSRB=0x18;	
	 UCSRC=0x06;	
	 UBRRL=0x67;
	 UBRRH=0x00;
	 UCSRA=UCSRA|0x08;	
}
//------------------------------´®¿Ú·¢ËÍ----------------------------------------
void R_S_Byte(uchar R_Byte)
{	
     UDR= R_Byte;  
}
//------------------------------Ö÷º¯Êı------------------------------------------
void main(void)
{  
	uchar i;
	DDRD=0xb2;		  //
	DDRB=0xB3;		  //
	DDRA=0x1e;       //
	DDRC=0xff; 		//LED¶Ë¿ÚÉèÖÃ
	PORTA = 0xff;
	Hign_BELL;	
	Hign_JDQ ;			
//------------------------------------------------------------------------------				  			 				
	Spi_initial();	                //SPI³õÊ¼»¯															  
	system_Init();				   //ÏµÍ³×´Ì¬³õÊ¼»¯												
	Config905();  				  //NRF905³õÊ¼»¯	
//------------------------------------------------------------------------------							  
//------------------------------------------------------------------------------
	StartUART();				//´®¿Ú³õÊ¼»¯9600²¨ÌØÂÊ
	Delay(500);
//------------------------------------------------------------------------------
	while(1)
	{
	RX();  					//½ÓÊÕÊı¾İ
	if(TxRxBuffer[0])
		{
		temp[2]=((TxRxBuffer[2]<<4)|TxRxBuffer[1]);		//ÕûÊıÎ»
		temp[1]=TxRxBuffer[0];							//Ğ¡ÊıÎ»
		temp[0]=TxRxBuffer[3];     					    //·ûºÅÎ»
		//temp[4]=TxRxBuffer[2];						//Ê®Î»
		//temp[5]=TxRxBuffer[1];						//¸öÎ»
	for(i=0;i<3;i++)
		{
		R_S_Byte(temp[2-i]);      //´®¿ÚÏÔÊ¾ÎÂ¶È
		Delay(20);
		}
		
	}
	if((temp[2]>=53)||(temp[2]<=32))//´óÓÚ35¶ÈÊ±±¨¾¯£¬0x35×ª»»³É10½øÖÆÎª53
									//µÍÓÚ20¶ÈÊ±Ò²±¨¾¯,0x20,×ª»»³É10½øÖÆÎª	32						  									  																
	{
		Low_BELL;  //´ò¿ª·äÃ÷Æ÷±¨¾¯
		Low_JDQ;   //´ò¿ª¼ÌµçÆ÷¡£¿ÉÒÔ½øĞĞÏà¹ØµçÆ÷¿ª¹Ø²Ù×÷
	}
	else
	{
	 	Hign_BELL ;//¹Ø±Õ·äÃ÷Æ÷±¨¾¯
		Hign_JDQ;  //¹Ø±Õ¼ÌµçÆ÷
	}
	dis_zhuye();
	}
}
