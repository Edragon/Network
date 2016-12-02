#ifndef SPI_H
#define SPI_H

/*
*********************************************************************
修改:
		使遵循 C51工程及代码规范-V0.31
		增加引脚输入/输出配置 SpiInit (for ATmega48)
		使能DDR功能,默认 1:输出 0:输入
		+.修改为mc9s12dg128_SPI模块代码
*********************************************************************
*/

#include "..\def.h"
/*
使用如下引脚(相对于MCU)
SPI_MOSI	[O]	主机输出(写操作)	SCK上升沿 主机向从机写入数据
SPI_MISO	[I]	主机出入(读操作)	SCK下降沿 从机更新输出的数据(CSN下降沿更新第一个位_MSB)
SPI_SCK		[O]	串行时钟信号
SPI_CSN		[O]	片选(低电平有效)
////////////////////////////
#define SPI_MOSI
#define SPI_MISO
#define SPI_SCK
#define SPI_CSN
//---------------
#define SPI_MOSI_DDR
#define SPI_MISO_DDR
#define SPI_SCK_DDR
#define SPI_CSN_DDR
//--------------------------
sbit	SPI_MOSI	= P^;
sbit	SPI_MISO	= P^;
sbit	SPI_SCK		= P^;
sbit	SPI_CSN		= P^;
*/


//void SpiCmdWrite(unsigned char command,unsigned char WriteBuf[],unsigned char len);
//void SpiCmdRead(unsigned char command,unsigned char ReadBuf[],unsigned char len);


void SpiInit(void);
unsigned char SpiRead(void);
void SpiWrite(unsigned char send);






#endif


