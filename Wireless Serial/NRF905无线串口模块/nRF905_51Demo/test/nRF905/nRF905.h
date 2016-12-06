#ifndef NRF905_H
#define NRF905_H

#include "../def.h"
#include "../SPI/SPI.h"

/*
*********************************************************************
修改:
		+.使遵循 C51工程及代码规范-V0.31
		+.增加引脚输入/输出配置(for ATmega48)
		+.修改unsigned char RxPacket(unsigned char *RxBuf); 增加返回值
		+.针对有引脚输入/输出方向的机型
*********************************************************************
*/



/*
使用如下引脚(相对于MCU)
TX_EN	[O] 
TRX_CE	[O]
PWR_UP	[O]
AM		[I]
DR		[I]
CD		[I]
////////////////////////////
#define TX_EN
#define TRX_CE
#define PWR_UP
#define AM
#define DR
#define CD
//--------------
#define TX_EN_DDR
#define TRX_CE_DDR
#define PWR_UP_DDR
#define AM_DDR
#define DR_DDR
#define CD_DDR
//--------------------------
sbit	TX_EN	=P^;
sbit	TRX_CE	=P^;
sbit	PWR_UP	=P^;
sbit	AM		=P^;
sbit	DR		=P^;
sbit	CD		=P^;
*/

//**************************
//<SPI命令>
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//************************************************************************************8


//--------------------------------------------------------------
//<RF-Configuration-Register 配置信息>
#define CH_NO		76//0x01			//freq=422.4+76/10=430MHz
#define HFREQ_PLL	0x0				//433Mhz / 868/915Mhz
#define PA_PWR		0x3				//最大输出功率
#define RX_RED_PWR	0x0				//接收功率
#define AUTO_RETRAN	0x0				//自动重新发送

//<地址宽度与数据宽度>
/*	defined in "def.h"	*/
#define RX_AWF		0x4				//Rx 本地接收地址宽度
#define TX_AWF		0x4				//Tx 本地发送地址宽度
//#define RX_PW		0x8			//Rx 本地接收有效数据宽度
//#define TX_PW		0x8			//Tx 本地发送有效数据宽度
#define RX_PW		0x1c			//Rx 本地接收有效数据宽度
#define TX_PW		0x1c			//Tx 本地发送有效数据宽度


#define UP_CLK_FREQ	0x0				//输出时钟频率
#define UP_CLK_EN	0x0				//输出时钟使能
#define XOF			0x3		//12MHz	//晶体振荡器频率,必须依据外部晶体的标称频率设置
#define CRC_EN		0x1				//CRC校验允许
#define CRC_MODE	0x1				//CRC模式   0b0-8位CRC校验位;  0b1-16位CRC校验位 （默认）

//<本机地址>
#define RX_ADDR_Byte3	0xcc		//本机地址 最高字节
#define RX_ADDR_Byte2	0xcc
#define RX_ADDR_Byte1	0xcc
#define RX_ADDR_Byte0	0xcc		//本机地址 最低字节

#define TX_ADDR_Byte3	0xcc
#define TX_ADDR_Byte2	0xcc
#define TX_ADDR_Byte1	0xcc
#define TX_ADDR_Byte0	0xcc
//-----------------------------------------------------------

//<将设置信息组合成每个字节的数据信息，此区域无需修改>
#define RFConfig_Byte0	(CH_NO & 0xff)
#define RFConfig_Byte1	(AUTO_RETRAN<<5 | RX_RED_PWR<<4 | PA_PWR<<2 | HFREQ_PLL<<1 | CH_NO>>8)
#define RFConfig_Byte2	(TX_AWF<<4 | RX_AWF)
#define RFConfig_Byte3	RX_PW
#define RFConfig_Byte4	TX_PW
#define RFConfig_Byte5	RX_ADDR_Byte0
#define RFConfig_Byte6	RX_ADDR_Byte1
#define RFConfig_Byte7	RX_ADDR_Byte2
#define RFConfig_Byte8	RX_ADDR_Byte3
#define RFConfig_Byte9	(CRC_MODE<<7 | CRC_EN<<6 | XOF<<3 | UP_CLK_EN<<2 | UP_CLK_FREQ)
//------------------------------------------------------------

typedef struct RFConfig
{
	unsigned char n;
	unsigned char buf[10];
} RFConfig;


//************************************************************************************8


void nRF905Init(void);					// Initialize IO port
void Config905(void);					// Config nRF905 module配置NRF905模式
void SetTxMode(void);					// Set nRF905 in Tx mode
void SetRxMode(void);					// Set nRF905 in Rx mode
void TxPacket(unsigned char *TxBuf);	// Send data by nRF905
unsigned char RxPacket(unsigned char *RxBuf);	// Recive data by nRF905

/*
#define SET_CHNO_ENABLE
#ifdef SET_CHNO_ENABLE
	void SetFrequence(unsigned int fre);
#endif

//#define SETST_BYMODE_ENABLE
#ifdef SETST_BYMODE_ENABLE
	void SetST_BYmode(void);		//转至Standby模式
#endif

//#define SETRF_PA_PWR_ENABLE
#ifdef SETRF_PA_PWR_ENABLE
	void SetRF_PA_PWR(unsigned char i);	//设置发射功率
#endif
*/

// Tx address
extern unsigned char TxAddress[4];
extern RFConfig RxTxConf;

#endif 
