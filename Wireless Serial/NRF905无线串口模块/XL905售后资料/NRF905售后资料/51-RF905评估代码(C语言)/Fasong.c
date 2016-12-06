#include <reg52.h>
#include <ABSACC.h>
#include <intrins.h>
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------
#define uint unsigned int
#define uchar unsigned char
//----------------------------------------------------------------------------------------------------------------
#define BYTE_BIT0	0x01
#define BYTE_BIT7	0x80
//----------------------------------------------------------------------------------------------------------------
bdata unsigned  char DATA_BUF;
#define DATA7	((DATA_BUF&BYTE_BIT7) != 0)
#define DATA0   ((DATA_BUF&BYTE_BIT0) != 0)
sbit	flag	=DATA_BUF^7;
sbit	flag1	=DATA_BUF^0;
//-----------------------------------------------------------------------------------------------
#define TxRxBuf_Len 4
unsigned char TxRxBuf[TxRxBuf_Len]={0x29,0x30,0x31,0x32,};
code TxAddress[4]={0xcc,0xcc,0xcc,0xcc};
char tf;
//-------------------------------------------------------------------------------------------
sbit	TXEN=P1^4;
sbit	TRX_CE=P3^2;
sbit	PWR=P1^3;
//-----------------------------------------------------------------------------------------
sbit    LED=P3^5;
//-------------------------------------------------------------------------------------------
sbit	MISO=P1^6;
sbit	MOSI=P1^1;
sbit	SCK=P1^5;
sbit	CSN=P1^0;
//------------------------------------------------------------------------------------------------
sbit	AM=P1^7;
sbit	DR=P3^3;
sbit	CD=P1^2;
//---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
sbit	KEY=P3^4;
//----------------------------------------------------------------------------------
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//------------------------------------------Ã------------------------------------------------
unsigned char idata RFConf[11]=
{
  0x00,                             
  0x5f,                            
  0x0c,                            
  0x44,                             
  0x04,0x04,                        
  0xCC,0xCC,0xCC,0xCC,             		  
  0x58,                              
};
//==========================================================================================================
void nrf905_Delay(int n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//========================================================================================================
unsigned char SpiRead(void)
{
	unsigned char j;
	for (j=0;j<8;j++)
	{
        DATA_BUF=DATA_BUF<<1;
		SCK=1;
		if (MISO)	
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
//==========================================================================================================
void SpiWrite(unsigned char send)
{
	unsigned char i;
	DATA_BUF=send;
	for (i=0;i<8;i++)
	{
		if (DATA7)
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
//---------------------------------------------
void nRF905Init(void)
{
    CSN=1;						// Spi 	disable
	SCK=0;						// Spi clock line init low
	DR=1;						// Init DR for input
	AM=1;						// Init AM for input
	CD=1;						// Init CD for input
	PWR=1;					// nRF905 power on
	TRX_CE=0;					// Set nRF905 in standby mode
	TXEN=0;					// set radio in Rx mode
}
//-----------------------------------------------------³õÊ¼»¯¼Ä´æÆ÷-----------------------------------------------
void Config905(void)
{
	uchar i;
	CSN=0;						// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config commandÐ´·ÅÅäÖÃÃüÁî
	for (i=0;i<11;i++)	// Write configration words  Ð´·ÅÅäÖÃ×Ö
	{
	   SpiWrite(RFConf[i]);
	}
	CSN=1;					// Disable Spi
}
//-----------------------------------------------------·¢ËÍÊý¾Ý´ò°ü---------------------------------------------------
void TxPacket(uchar *TxRxBuf)
{
	uchar i;
	Config905();
	CSN=0;
	SpiWrite(WTP);				// Write payload command
	for (i=0;i<4;i++)
	{
		SpiWrite(TxRxBuf[i]);		// Write 32 bytes Tx data
	}
	CSN=1;
	nrf905_Delay(1);						// Spi disable
	CSN=0;						// Spi enable for write a spi command
	SpiWrite(WTA);				// Write address command
	for (i=0;i<4;i++)			// Ð´ÈëÓë¶Ô·½µØÖ·Ò»ÑùµÄµØÖ·
	{
		SpiWrite(TxAddress[i]);
	}
	CSN=1;						// Spi disable
	TRX_CE=1;					// Set TRX_CE high,start Tx data transmission
	nrf905_Delay(1);					// while (DR!=1);
	TRX_CE=0;					// Set TRX_CE low
}
//----------------------------------------------ÉèÖÃ·¢ËÍ³õÊ¼×´Ì¬---------------------------------------------
void SetTxMode(void)
{
	TRX_CE=0;
	TXEN=1;
	nrf905_Delay(1); 					// nrf905_Delay for mode change(>=650us)
}
//-----------------------------------------------ÉèÖÃ½ÓÊÕ³õÊ¼»¯---------------------------------------------------
void SetRxMode(void)
{
	TXEN=0;
	TRX_CE=1;
	nrf905_Delay(1); 					// nrf905_Delay for mode change(>=650us)
}
//-------------------------------------------------ÅÐ¶ÏÊý¾Ý½ÓÊÕ×´Ì¬-----------------------------------------------------
unsigned char CheckDR(void)		//¼ì²éÊÇ·ñÓÐÐÂÊý¾Ý´«Èë Data Ready
{
	if (DR==1)
	{
		DR=0;
		return 1;
	}
	else
	{
		return 0;
	}

}
//----------------------------------------------------¶ÁNRF905½ÓÊÕÊý¾Ý------------------------------------------------------------
void RxPacket(void)						
{
	uchar i;
    nrf905_Delay(1);
	TRX_CE=0;					// Set nRF905 in standby mode
    nrf905_Delay(100);
    TRX_CE=0;
	CSN=0;						// Spi enable for write a spi command
    nrf905_Delay(1);
	SpiWrite(RRP);
	for (i = 0 ;i < 4 ;i++)
	{ 
		TxRxBuf[i]=SpiRead();		// Read data and save to buffer       
	}
	CSN=1;
    nrf905_Delay(10);
	TRX_CE=1;							
}
//-------------------------------------------------------------------------------------------------------
void  RX(void)
{
          SetRxMode();	
		  nrf905_Delay(10);
	  	  RxPacket();
		  if(TxRxBuf[0]==0x29)
		  {
		  		LED=0;
			    nrf905_Delay(300);
				LED=1;
			    nrf905_Delay(300);
		  }

}
//-----------------------------------------------------------------------------------------------------------------
void main(void)
{
        nRF905Init();
     	Config905();
		LED=1;
        while(1)
		{
			RX();
		   if(KEY ==0 )
			 {	
			 	while(KEY==0);
				tf = 1 ;
				TxRxBuf[0]=0x29;
				 }
		  
	       if (tf==1)
			{
                SetTxMode();
			    TxPacket(TxRxBuf);
  				LED=0;
			    nrf905_Delay(300);
				LED=1;
			    nrf905_Delay(300);		
				tf = 0;	
			}	
}
}
