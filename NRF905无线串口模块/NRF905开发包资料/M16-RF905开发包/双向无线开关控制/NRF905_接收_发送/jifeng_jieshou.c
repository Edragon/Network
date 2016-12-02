//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
///////////////////////////ģʽ���ƶ���/////////////////////////////////
//#define  nrf905_TX_EN	  PB0	    //���1   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0)
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0)
//#define  nrf905_TRX_CE  PD4	    //���1
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4)  
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4) 
//#define  nrf905_PWR     PB1 	    //���1
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1) 
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1)
//--------------------------------SPI�ڶ���-------------------------------------
//#define  nrf905_MISO	  PB6   	//����0
//#define  nrf905_MOSI    PB5	    //���1
//#define  nrf905_SCK     PB7	    //���1
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7)
//------------------------------------------------------------------------------
//#define  nrf905_CSN     PB4		//���1		
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4)  
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4)				
//-------------------------------״̬�����-------------------------------------
//#define  nrf905_CD      PD3	    //����0
#define   Hign_nrf905_CD    PORTD |= (1 << PD3) 
#define   Low_nrf905_CD     PORTD &= ~(1 << PD3) 
#define   Read_nrf905_CD    PINB & (1 << PD3)
//#define  nrf905_AM      PB3	    //����0
#define   Hign_nrf905_AM    PORTB |= (1 << PB3) 
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3)
#define   Read_nrf905_AM    PINB & (1 << PB3)
//#define  nrf905_DR      PB2  		//����0
#define   Hign_nrf905_DR    PORTB |= (1 << PB2)
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2)
#define   Read_nrf905_DR    PINB & (1 << PB2)
//��ȡ��ֵKEY2-KEY3-KEY4  
#define   Read_KEY_2  	    PINA & (1 << PA5)        
//�׶Ӽ�3��
#define   Read_KEY_3    	PINA & (1 << PA6)
//�ҶӼ�2��
#define   Read_KEY_4   	    PINA & (1 << PA7)   
//�ҶӼ�3��
//------------------------------�����λѡ--------------------------------------
//#define Display1   PA1  		    //���1
#define   Hign_Display1     PORTA |= (1 << PA1);   
#define   Low_Display1    PORTA &= ~(1 << PA1); 
//#define Display2      PA2  		//���1
#define   Hign_Display2     PORTA |= (1 << PA2);   
#define   Low_Display2    PORTA &= ~(1 << PA2); 
//#define Display3     PA3  		//���1
#define   Hign_Display3     PORTA |= (1 << PA3);   
#define   Low_Display3     PORTA &= ~(1 << PA3); 
//#define Display4      PA4 		//���1
#define   Hign_Display4     PORTA |= (1 << PA4);   
#define   Low_Display4     PORTA &= ~(1 << PA4); 
//-------------------------------BELL������-------------------------------------
#define   Hign_BELL  PORTD |= (1 << PD5);   
#define   Low_BELL     PORTD &= ~(1 << PD5); 
//-------------------------------JDQ�̵���--------------------------------------
#define   Hign_JDQ  PORTD |= (1 << PD7)
#define   Low_JDQ     PORTD &= ~(1 << PD7)
//----------------------------------905-SPIָ��---------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------�������ݻ�����-------------------------------
uchar TxRxBuf[4];
//----------------------------------���յ�ַ------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
uchar tf;
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9����
//------------------------------------------------------------------------------
//----------------------------------�Ĵ�������----------------------------------
uchar RFConf[11]=
{
  0x00,                             //��������//
  0x4c,                             //CH_NO,����Ƶ����430MHZ
  0x0C,                             //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
  0x44,                             //��ַ������ã�Ϊ4�ֽ�
  0x04,0x04,                        //���շ�����Ч���ݳ���Ϊ4�ֽ�
  0xCC,0xCC,0xCC,0xCC,              //���յ�ַ
  0x58,                              //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
};
//----------------------------------��������------------------------------------
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
//----------------------------------100us��ʱ�ӳ���-----------------------------
void Delay(uint x)
{
	uint i;
	while(x--)
	for(i=0;i<80;i++);
}
//----------------------------------SPI��ʼ��-----------------------------------
void Spi_initial()
{
	//SPCR=0x50;
	//SPSR=0x00;	
	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);   // ����ģʽ��fck/16, SPI��ʽ0
}
//---------------------------------SPI��д����----------------------------------	
uchar SpiReadSpiWrite(unsigned char cData)//r
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF) ))
	{};			// �ȴ�SPI�������
	return SPDR;
}
//---------------------------------ϵͳ״̬��ʼ��-------------------------------
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
//--------------------------------NRF905�Ĵ�����ʼ������------------------------
void Config905(void)
{
	uchar i;
	Low_nrf905_CSN;	
	Delay(1);				// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config commandд����������
	for (i=0;i<11;i++)			// Write configration words  д��������
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//--------------------------------NRF905�������ݴ��----------------------------
void TxPacket(uchar TxBUF[4])
{
	uchar i;
	Low_nrf905_CSN;		   						// ʹ��Spi�������nrf905���ж�д����
	Delay(1);
	SpiReadSpiWrite(WTP);				// д����ǰ��дд��������
	for (i=0;i<4;i++)
	{
	SpiReadSpiWrite(TxBUF[i]);		// �����͵�32�ֽ�����
	}						
	Hign_nrf905_CSN;
	Delay(1);							// �ر�Spi���������nrf905���ж�д����
	Low_nrf905_CSN;								// ʹ��Spi
	SpiReadSpiWrite(WTA);				// д��ַǰ������д��ַ����
	for (i=0;i<4;i++)					// д 4 bytes ��ַ
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	Hign_nrf905_CSN;					// �ر�Spi
	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	Delay(1);							// �ȴ�DR���
	Low_nrf905_TRX_CE;							// ����TRX_CE=0
}
//-------------------------------����ģʽ����-----------------------------------
void SetTxMode(void)
{
	Low_nrf905_TRX_CE;				//
	Hign_nrf905_TX_EN;				//����ʹ��
	Delay(2); 				// delay for mode change(>=650us)���ݾ���ͬҪ�ı�
}
//------------------------------------------------------------------------
//------------------------------���ý���ģʽ����--------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(1000); 					// delay for mode change(>=650us)
}
//-----------------------------------���������ݰ�-------------------------------
void RxPacket(void)							//������
{
	uchar i;
    Low_nrf905_TRX_CE;
	Low_nrf905_CSN;						    // ʹ��SPI
    Delay(1);
	SpiReadSpiWrite(RRP);				   // д�����ݽ��ջ�������������
	for (i = 0 ;i < 4 ;i++)
	{   
	TxRxBuf[i]=SpiReadSpiWrite(0);	  // ��ȡ���ݽ��ջ���������       
	}
	Hign_nrf905_CSN;
    Delay(2);                            //
	Hign_nrf905_TRX_CE;							
}
//--------------------------------���ý���ģʽ----------------------------------
void  RX(void)
{
    SetRxMode();			          //����NRF905����ģʽ
	RxPacket();                     //��ȡ�������ݻ�����
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
//------------------------------������------------------------------------------
void main(void)
{  
	uint i,j,temp[32];
	DDRD=0xf2;		  //
	DDRB=0xB3;		  //
	DDRA=0x1e;       //
	DDRC=0xff; 		//LED�˿�����
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
	if((PINA & 0x20) == 0)		  //�м�����KEY1
	{
	while(!(PINA & 0x20));   			//�ȴ������ɿ�GREEN
	 TxRxBuf[0]=0x29;
	 tf=1;   
	 PORTC=seg[1];
	 Low_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Hign_Display1;
	 }
//------------------------------------------------------------------------------
	if((PINA & 0x40) == 0)			//�м�����KEY2
	{
	while(!(PINA & 0x40));   			//�ȴ������ɿ�GREEN
 	 TxRxBuf[0]=0x30; 
	 tf=1;    
	 PORTC=seg[2];
	 Hign_Display4;
	 Low_Display3;
	 Hign_Display2;
	 Hign_Display1;
	 }
//------------------------------------------------------------------------------
	if((PINA & 0x80) == 0)			//�м�����KEY3
	{
	while(!(PINA & 0x80));   			//�ȴ������ɿ�GREEN
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
	SetTxMode();				// �������ݷ�s��
	TxPacket(TxRxBuf);			// װ�ش���������	
	Delay(200); 	
	//-------------------------------------------------
	TxRxBuf[0]=0;
	 }
	 //****************************************************************

	Hign_BELL;
	Hign_JDQ ;															
}
}