#include <reg52.h>
#include <ABSACC.h>
#include <intrins.h>
#include <stdio.h>
#define uint  unsigned int
#define uchar unsigned char
#define U8     unsigned char
#define U16     unsigned int

#define   ROW(x)       (0x80|(x << 0x06))
#define   COL(x)       (x)
#define   LEN(x)       ((x-0x01) << 0x03)

#define   LEN_MASK     0x38
#define   COL_MASK     0x07
#define   ROW_MASK     0xC0
#define   ROW_COL      (ROW_MASK|COL_MASK)
	
#define   HexDisp(x)   HexDispArray[x]
#define   BYTE_LOW(x)  (x & 0x0F) 
#define   BYTE_HIGH(x) ((x & 0xF0)>>0x04)


//配置口定义//
sbit TXEN    =    P1^6;
sbit TRX_CE =    P1^0;
sbit PWR    =    P1^7;
//SPI口定义//
sbit MISO    =    P1^1;
sbit MOSI    =    P1^4;
sbit SCK    =    P1^2;
sbit CSN    =    P1^3;

// lcd bit define
sbit     LCD_RW = P2^2;
sbit     LCD_RS = P2^1;
sbit     LCD_EN = P2^0;
#define  LCD_DATA P0

sbit red_led  = P2^6;
sbit gre_led  = P2^7;

sbit key       = P2^4;
sbit key1      = P2^5;
sbit key2      = P2^1;
sbit key3      = P2^2;
sbit key4      = P2^3;

//sbit key1      = P2^4;

//状态输出口//
sbit DR        =    P1^5;
sbit LCD    =    P3^2;

/*/RF寄存器配置//
unsigned char idata RFConf[11]=
{
    0x00,        //配置命令//
    0x6C,        //CH_NO,配置频段在433.2MHZ
    0x0C,        //输出功率为10db,不重发，节电为正常模式
    0x44,        //地址宽度设置，为4字节
    0x03,0x03,    //接收发送有效数据长度为3字节
    0xE7,0xE7,0xE7,0xE7,    //接收地址
    0xC0,        //CRC充许，16位CRC校验16M晶振
};*/
   
uchar TxRxBuffer[5];
bit   success_flag=0;

uchar key_value=0;
uchar Rf_Rec_Cnt=0;

void delay_2us(U16 delay_cnt);




///////////延时/////////////////
void Delay(uint x)
{
    uint i;
    for(i=0;i<x;i++){
        _nop_();
    }
}

////////////用SPI口写数据至NRF905内//////////
void SpiWrite(unsigned char b)
{
    unsigned char i=8;
SCK=0;
    while (i--)
    {
        Delay(10);
        MOSI=(bit)(b&0x80);
        b<<=1 ; 
        Delay(10);
        SCK=1; 
        Delay(10);
        SCK=0;
    }
    SCK=0;
}
///////////////from 905 read data////////////////
unsigned char SpiRead(void)
{
    register unsigned char i=8;
    unsigned char ddata=0;
SCK=0;
    while (i--)
    {
        ddata<<=1 ;
       ddata|=MISO;
        SCK=1 ;
        Delay(10);
   SCK=0 ;
   Delay(10);
    }
    SCK=0;
    return ddata;
}
///////////////接收数据包/////////////////
void RxPacket(void)
{
    uchar i;
    i=0;
    //while(DR)
    {
        TxRxBuffer[i] = SpiRead();
		TxRxBuffer[1] = SpiRead();
		TxRxBuffer[2] = SpiRead();
        //i++;
    }
}

/*
;写发射数据命令:20H
;读发射数据命令:21H
;写发射地址命令:22H
;读发射地址命令:23H
;读接收数据命令:24H
*/
void TxPacket(void)
{   PWR=1;
    TXEN=1;
	TRX_CE=0; 
	Delay(2);
    CSN=0;
    SpiWrite(0x22);        //写发送地址,后面跟4字节地址//
    SpiWrite(0xE7);
    SpiWrite(0xE7);
    SpiWrite(0xE7);
    SpiWrite(0xE7);
    CSN=1;
    Delay(2);
    CSN=0;
    SpiWrite(0x20);        //写发送数据命令,后面跟三字节数据//
    SpiWrite(0x01);
    SpiWrite(0x02);		
    //SpiWrite(0x03);
	SpiWrite(key_value);
	
    CSN=1;
    Delay(5);
    TRX_CE=1;                    //使能发射模式//
    Delay(500);                    //等带发送完成//	
    TRX_CE=0;
	while(!DR);
   
    
} 
////////////////等待接收数据包///////////////////
uchar temp;
void Wait_Rec_Packet(void)
{
    //TXEN=0;
    //TRX_CE=1;
    //PWR=1;
    //Delay(1000);
    //while(1)
    {// if (LCD==1)
        if(DR)
        { 
            TRX_CE=0;            //如果数据准备好，则进入待机模式，以便SPI口操作
            CSN=0;
            SpiWrite(0x24);
            RxPacket();
            CSN=1;
			while(DR);
			TRX_CE=1;
			if((TxRxBuffer[0]==0x01)&&(TxRxBuffer[1]==0x02)&&(TxRxBuffer[2]==0x03))
			{
				success_flag=1;
				/*
			    red_led=0;
			    Delay(5000);
			    Delay(5000);
			    success_flag=0;
			    red_led=1;	
                             */
			} 
            
          //break;
        }
    }
}
////////////初始化配置寄存器////////////////
void Ini_System(void)
{
   // uchar i;
    
    CSN=1;
    SCK=0;
    PWR=1;
    TRX_CE=0;
    TXEN=0;
    Delay(2);
    CSN=0;

    SpiWrite( 0x00);        //配置命令//
    SpiWrite( 0x6C);        //CH_NO,配置频段在433.2MHZ
    SpiWrite( 0x0C);        //输出功率为10db,不重发，节电为正常模式
    SpiWrite( 0x44);        //地址宽度设置，为4字节
    SpiWrite( 0x03);SpiWrite( 0x03);    //接收发送有效数据长度为3字节
    SpiWrite( 0xE7);SpiWrite( 0xE7);SpiWrite( 0xE7);SpiWrite( 0xE7);    //接收地址
    SpiWrite( 0xDE); 


    /*for(i=0;i<11;i++){
        SpiWrite(RFConf[i]);
    }*/
    CSN=1;
    PWR=1;
    TRX_CE=1;
    TXEN=0;
    Delay(1000);
}





        
void main(void)
{
   

Ini_System();

DR=1;
red_led=0;
gre_led=0;

success_flag=0;
    TRX_CE=0;
    Delay(1000);
    TXEN=0;
    TRX_CE=1;
    PWR=1;
		
   key_value=0x0;
	
	
	


    while(1)
    {   
        
		
		if(!key)         //senfing  key0
		{
			Delay(5);
			if(!key)
			{    Delay(3);
				 while(!key);				 
				 key_value=0xa0;					 				 
			}
				
		}
		
		else if(!key1)         //senfing  key1
		{
			Delay(5);
			if(!key1)
			{    Delay(3);
				 while(!key1);				 
				 key_value=0xa1;				 				 
			}
				
		}
		
		if(!key2)         //senfing  key2
		{
			Delay(5);
			if(!key2)
			{    Delay(3);
				 while(!key2);				 
				 key_value=0xa2;					
			}
				
		}
		
		if(!key3)         //senfing  key3
		{
			Delay(5);
			if(!key3)
			{    Delay(3);
				 while(!key3);				 
				 key_value=0xa3;					
			}
				
		}
		
		if(!key4)         //senfing  key2
		{
			Delay(5);
			if(!key4)
			{    Delay(3);
				 while(!key4);				 
				 key_value=0xa4;				 				
			}
				
		}
		
		
		
		if(key_value!=0x0)
		{
			 red_led=1;
			 TxPacket();			 
			 key_value=0x0;
			 TXEN=0;
             TRX_CE=1;
             PWR=1;
			 Delay(6000);
			 red_led=0;
		}
		
    }
}

//----------------- 20091113 START---------------


























