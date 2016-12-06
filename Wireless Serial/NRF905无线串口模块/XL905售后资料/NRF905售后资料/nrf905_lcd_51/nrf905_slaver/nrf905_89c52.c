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

sbit red_led  = P2^0;
sbit gre_led  = P2^1;

sbit key      = P2^4;
sbit key1      = P2^5;
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

void ini_lcd(void);
void lcd_printf_char(U8 disp_char, U8 row_col);
void lcd_printf_string(U8 *disp_str, U8 row_len_col);
void lcd_write_reg(U8 command);
void lcd_write_data(U8 value);
void lcd_wait(void);
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
    SpiWrite(0x03);
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
   unsigned int timeout;

Ini_System();
PWR=0;
//P0=0;
DR=1;
red_led=1;
success_flag=0;
    TRX_CE=0;
    Delay(1000);
    TXEN=0;
    TRX_CE=1;
    PWR=1;
	
	 TxPacket();
				     //Delay(5000);
					 //lcd_printf_string("        ", ROW(0x00)|LEN(0x08)|COL(0x00));
	                 //lcd_printf_string("send... ", ROW(0x01)|LEN(0x08)|COL(0x00));
                    // Delay(5000);
	red_led=1;
				 
	TXEN=0;
    TRX_CE=1;
    PWR=1;
    Delay(1000);		
    
	
	//ini_lcd();
	//delay_2us(50000);

	//lcd_printf_string(" master ", ROW(0x00)|LEN(0x08)|COL(0x00));
	//lcd_printf_string(" nrf905 ", ROW(0x01)|LEN(0x08)|COL(0x00));

//TxPacket();
    while(1)
    {   
        Wait_Rec_Packet();        //等待接收完成 
		
		if(success_flag)
        {
			
			TXEN=0;
            TRX_CE=1;
            PWR=1;
			
			red_led=0;
			Delay(5000);
			Delay(5000);
			success_flag=0;
			red_led=1;
			
			 red_led=0;
		     TxPacket();
				     //Delay(5000);
					 //lcd_printf_string("        ", ROW(0x00)|LEN(0x08)|COL(0x00));
	                 //lcd_printf_string("send... ", ROW(0x01)|LEN(0x08)|COL(0x00));
                    // Delay(5000);
	                 red_led=1;
				 
				     TXEN=0;
                     TRX_CE=1;
                     PWR=1;
                     Delay(1000);		
			
			
			
		}
		
		if(!key)         //senfing  testing
		{
			Delay(30);
			if(!key)
			{    Delay(30);
				 //while(!key);
				 //Delay(100);
				 //while((key)&&(key1))
				 {
					 red_led=0;
				     TxPacket();
				     //Delay(5000);
					 //lcd_printf_string("        ", ROW(0x00)|LEN(0x08)|COL(0x00));
	                 //lcd_printf_string("send... ", ROW(0x01)|LEN(0x08)|COL(0x00));
                    // Delay(5000);
	                 red_led=1;
				 
				     TXEN=0;
                     TRX_CE=1;
                     PWR=1;
                     Delay(1000);					 
				 }
				 				 
			}
				
		}
		
		
   //DR=1;
// for(i=0;i<2;i++)
// Delay(65530);
//TxPacket();
   //Delay(50000);
    //P0=~P0;
    }
}

//----------------- 20091113 START---------------
//----------------- 1602 start ------------------
/***********************************************************
name:		ini_lcd		
input:		none
output:		none
describe:	初始化LCD	
notice:
creat date: 2008-7-25
creator:	dengyihong
************************************************************/
void ini_lcd(void)
{
    lcd_write_reg(0x38);
    lcd_write_reg(0x38);
    lcd_write_reg(0x38);
    lcd_write_reg(0x08);
    lcd_wait();
    lcd_write_reg(0x01);
    lcd_wait();
    delay_2us(50000);
    
    lcd_write_reg(0x14);
    lcd_wait();
    lcd_write_reg(0x06);
    lcd_wait();
    lcd_write_reg(0x80);
    lcd_wait();
    lcd_write_reg(0x0c);
    lcd_wait();	
}


/***********************************************************
name:		lcd_printf_string	
input:		*disp_str  ---  存放显示字符的头指针
			row_len_col  ---  显示坐标参数及显示字符数
			row_len_col:
				bit[7:6]: 显示行坐标
				bit[5:3]: 显示字符长度
				bit[2:0]: 显示字符的起始列坐标
output:		none
describe:	在屏幕上显示多个字符		
notice:
creat date: 2008-7-25
creator:	dengyihong
************************************************************/
void lcd_printf_string(U8 *disp_str, U8 row_len_col)
{
    U8 i = 0;
    U8 len = 0;
    
    len = (row_len_col & LEN_MASK) >> 0x03;
    
    lcd_write_reg(row_len_col & ROW_COL);
    lcd_wait();
    
    for(i=0; i<=len; i++)
    {
        lcd_write_data(*disp_str++);
        lcd_wait();	
    }
}


/***********************************************************
name:		lcd_printf_char		
input:		disp_char  ---  要显示的字符
			row_col    ---  显示坐标
output:		none
describe:	在屏幕上显示一个字符		
notice:
creat date: 2008-7-25
creator:	dengyihong
************************************************************/
/*
void lcd_printf_char(U8 disp_char, U8 row_col)
{
    lcd_write_reg(row_col & ROW_COL);
    lcd_wait();
    lcd_write_data(disp_char);
    lcd_wait();	
}
*/

/***********************************************************
name:		lcd_write_reg		
input:		command  ---  要写入的命令
output:		none
describe:	写控制命令到LCD	
notice:
creat date: 2008-7-25
creator:	dengyihong
************************************************************/
void lcd_write_reg(U8 command)
{
    LCD_DATA = command;		// 写控制命令
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 1;
    delay_2us(100);
    LCD_EN = 0;
}


/***********************************************************
name:		lcd_write_data		
input:		value  ---  要写入的数据
output:		none
describe:	写数据到LCD	
notice:
creat date: 2008-7-25
creator:	dengyihong
************************************************************/
void lcd_write_data(U8 value)
{
   LCD_DATA =  value;		//写数据
   LCD_RS = 1;
   LCD_RW = 0;
   LCD_EN = 1;
   delay_2us(100);
   LCD_EN = 0; 	
}

/***********************************************************
name:		lcd_wait	
input:		none
output:		none
describe:	等待LCD内部操作完成	
notice:
creat date: 2008-7-25
creator:	dengyihong
************************************************************/
void lcd_wait(void)
{
    U8 value = 0;
       
    do
    {
        LCD_RS = 0;
        LCD_RW = 1;
        LCD_EN = 1;
        value = LCD_DATA;	
        LCD_EN = 0;
    }while(value & 0x80);		// 等待内部操作完成	
}

/**********************************************************
name:		delay_2us
input:		delay_cnt
output:		none
describe:	delay x*2us
notice:
creat date:	2008-7-24
creator:	dengyihong
**********************************************************/
void delay_2us(U16 delay_cnt)
{
    while(delay_cnt--);
}


//----------------- 1602 start ------------------

























