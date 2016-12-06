#ifndef _DEF_H_
#define _DEF_H_

#include <at89x52.h>
#include <intrins.h>



#define BYTE_BIT0	0x01
#define BYTE_BIT1	0x02
#define BYTE_BIT2	0x04
#define BYTE_BIT3	0x08
#define BYTE_BIT4	0x10
#define BYTE_BIT5	0x20
#define BYTE_BIT6	0x40
#define BYTE_BIT7	0x80


/*******************************************************************************************/
sbit	TX_EN	=P1^7;
sbit	TRX_CE	=P1^6;
sbit	PWR_UP	=P1^5;
sbit	MISO	=P1^1;
sbit	MOSI	=P1^0;
sbit	SCK		=P3^7;
sbit	CSN		=P3^3;

sbit	AM		=P1^3;
sbit	DR		=P3^2;
sbit	CD		=P1^4;

sbit    LED1    =P3^4;
sbit    LED2    =P3^5;
sbit    KEY1    =P3^0;
sbit    KEY2    =P3^1;

#endif //_DEF_H_
