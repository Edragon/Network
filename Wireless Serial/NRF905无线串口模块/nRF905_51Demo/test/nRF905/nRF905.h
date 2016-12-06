#ifndef NRF905_H
#define NRF905_H

#include "../def.h"
#include "../SPI/SPI.h"

/*
*********************************************************************
�޸�:
		+.ʹ��ѭ C51���̼�����淶-V0.31
		+.������������/�������(for ATmega48)
		+.�޸�unsigned char RxPacket(unsigned char *RxBuf); ���ӷ���ֵ
		+.�������������/�������Ļ���
*********************************************************************
*/



/*
ʹ����������(�����MCU)
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
//<SPI����>
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24
//************************************************************************************8


//--------------------------------------------------------------
//<RF-Configuration-Register ������Ϣ>
#define CH_NO		76//0x01			//freq=422.4+76/10=430MHz
#define HFREQ_PLL	0x0				//433Mhz / 868/915Mhz
#define PA_PWR		0x3				//����������
#define RX_RED_PWR	0x0				//���չ���
#define AUTO_RETRAN	0x0				//�Զ����·���

//<��ַ��������ݿ��>
/*	defined in "def.h"	*/
#define RX_AWF		0x4				//Rx ���ؽ��յ�ַ���
#define TX_AWF		0x4				//Tx ���ط��͵�ַ���
//#define RX_PW		0x8			//Rx ���ؽ�����Ч���ݿ��
//#define TX_PW		0x8			//Tx ���ط�����Ч���ݿ��
#define RX_PW		0x1c			//Rx ���ؽ�����Ч���ݿ��
#define TX_PW		0x1c			//Tx ���ط�����Ч���ݿ��


#define UP_CLK_FREQ	0x0				//���ʱ��Ƶ��
#define UP_CLK_EN	0x0				//���ʱ��ʹ��
#define XOF			0x3		//12MHz	//��������Ƶ��,���������ⲿ����ı��Ƶ������
#define CRC_EN		0x1				//CRCУ������
#define CRC_MODE	0x1				//CRCģʽ   0b0-8λCRCУ��λ;  0b1-16λCRCУ��λ ��Ĭ�ϣ�

//<������ַ>
#define RX_ADDR_Byte3	0xcc		//������ַ ����ֽ�
#define RX_ADDR_Byte2	0xcc
#define RX_ADDR_Byte1	0xcc
#define RX_ADDR_Byte0	0xcc		//������ַ ����ֽ�

#define TX_ADDR_Byte3	0xcc
#define TX_ADDR_Byte2	0xcc
#define TX_ADDR_Byte1	0xcc
#define TX_ADDR_Byte0	0xcc
//-----------------------------------------------------------

//<��������Ϣ��ϳ�ÿ���ֽڵ�������Ϣ�������������޸�>
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
void Config905(void);					// Config nRF905 module����NRF905ģʽ
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
	void SetST_BYmode(void);		//ת��Standbyģʽ
#endif

//#define SETRF_PA_PWR_ENABLE
#ifdef SETRF_PA_PWR_ENABLE
	void SetRF_PA_PWR(unsigned char i);	//���÷��书��
#endif
*/

// Tx address
extern unsigned char TxAddress[4];
extern RFConfig RxTxConf;

#endif 
