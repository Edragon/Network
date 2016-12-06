//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
//---------------------------------ģʽ���ƶ���---------------------------------
//#define  nrf905_TX_EN	  PB0	    //���1
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
//#define  nrf905_TRX_CE  PD4	    //���1
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4);   
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4); 
//#define  nrf905_PWR     PB1 	    //���1
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1);   
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1); 
//--------------------------------NRF905-SPI�ڽӿڶ���--------------------------
//#define  nrf905_MISO	  PB6   	//����0
//#define  nrf905_MOSI    PB5	    //���1
//#define  nrf905_SCK     PB7	    //���1
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7); 
//#define  nrf905_CSN     PB4		//���1		
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4);   
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4); 						
//-------------------------------NRF905״̬�����-------------------------------
//#define  nrf905_CD      PD3	    //����0
#define   Hign_nrf905_CD    PORTD |= (1 << PD3);   
#define   Low_nrf905_CD     PORTD &= ~(1 << PD3); 
#define   Read_nrf905_CD    PINB & (1 << PD4);
//#define  nrf905_AM      PB3	    //����0
#define   Hign_nrf905_AM    PORTB |= (1 << PB3);   
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3); 
#define   Read_nrf905_AM    PINB & (1 << PB3);
//#define  nrf905_DR      PB2  		//����0
#define   Hign_nrf905_DR     PORTB |= (1 << PB2);   
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2); 
#define   Read_nrf905_DR    PINB & (1 << PB2);   
//-------------------------------BELL������-------------------------------------
#define   Hign_BELL  PORTD |= (1 << PD5);   
#define   Low_BELL     PORTD &= ~(1 << PD5); 
//-------------------------------JDQ�̵���--------------------------------------
#define   Hign_JDQ  PORTD |= (1 << PD7)
#define   Low_JDQ     PORTD &= ~(1 << PD7)

//----------------------------------NRF905-SPIָ��------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------��������-------------------------------------
uchar TxRxBuffer[4];
//----------------------------------���յ�ַ------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
//------------------------------------------------------------------------------
uchar count1 ,count2;
//----------------------------------�Ĵ�������----------------------------------
uchar RFConf[11]=
{
  0x00,                            //��������//
  0x4c,                           //CH_NO,����Ƶ����430MHZ
  0x0C,                          //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
  0x44,                         //��ַ������ã�Ϊ4�ֽ�
  0x04,0x04,                   //���շ�����Ч���ݳ���Ϊ4�ֽ�
  0xCC,0xCC,0xCC,0xCC,        //���յ�ַ
  0x58,                      //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
};
//----------------------------------NRF905��������------------------------------
void Delay(uint x);						       //��ʱ�ӳ���																							
void Spi_initial();                            //SPI��ʼ��
uchar SpiReadSpiWrite(unsigned char cData);    //SPI��д�ӳ���
void system_Init(void);		   				   //ϵͳ��ʼ��
void Config905(void);						   //NRF905��ʼ���ӳ���
void TxPacket(void);						
void SetTxMode(void);						   //���ݷ���
void SetRxMode(void);						   //
void TX(void);
unsigned char CheckDR(void);
void RxPacket(void);
void  RX(void);
//-------------------------------���ں�������-----------------------------------
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
	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);// ����ģʽ��fck/16, SPI��ʽ0
}
//---------------------------------SPI��д����----------------------------------	
uchar SpiReadSpiWrite(unsigned char cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF) ))  // �ȴ�SPI�������
	{};			
	return SPDR;
}
//--------------------------------ϵͳ״̬��ʼ��--------------------------------
void system_Init(void)			
{

   	Hign_nrf905_CSN;			// SPIʹ��
	Low_nrf905_SCK;				
	Low_nrf905_DR;				// DR=0
	Low_nrf905_AM;				// AM=0
	Low_nrf905_CD;				// CD=0
	Hign_nrf905_PWR;		    // PWR=1
	Low_nrf905_TRX_CE;			// nrf905_TRX_CE=0
	Low_nrf905_TX_EN ;			// nrf905_TX_EN=0
}
//--------------------------------NRF905�Ĵ�����ʼ������------------------------
void Config905(void)
{
	uchar i;
	Low_nrf905_CSN;				//SPIʹ��											
	Delay(1);				   
	for (i=0;i<11;i++)			//�NRF905������
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//--------------------------------NRF905�������ݴ��----------------------------
void TxPacket(void)
{
	uchar i;
	Low_nrf905_CSN;		   				// ʹ��Spi�������nrf905���ж�д����
	Delay(1);
	SpiReadSpiWrite(WTP);				// д����ǰ��дд��������
	for (i=0;i<32;i++)
	{
	SpiReadSpiWrite(TxRxBuffer[i]);		// �����͵�32�ֽ�����
	}						
	Hign_nrf905_CSN;
	Delay(1);							// �ر�Spi���������nrf905���ж�д����
	Low_nrf905_CSN;						// ʹ��Spi
	SpiReadSpiWrite(WTA);				// д��ַǰ������д��ַ����
	for (i=0;i<4;i++)					// д��4 bytes ���յ�ַ
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	Hign_nrf905_CSN;					// �ر�Spi
	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	Delay(1);							// �ȴ�DR���
	Low_nrf905_TRX_CE;					// ����TRX_CE=0
}
//------------------------------���÷���ģʽ------------------------------------
void SetTxMode(void)
{
	Low_nrf905_TRX_CE;				//
	Hign_nrf905_TX_EN;				//����ʹ��
	Delay(2); 				// delay for mode change(>=650us)
}
//------------------------------���ý���ģʽ����--------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(10); 					// delay for mode change(>=650us)
}
//------------------------------��������----------------------------------------
void TX(void)
{
     SetTxMode();	   // Set nRF905 in Tx mode
	 TxPacket();			   // Send data by nRF905
}
//-----------------------------�ж��Ƿ��յ�����---------------------------------
unsigned char CheckDR(void)		//����Ƿ��������ݴ��� 
{
	if (PINB & (1 << PB2))
	{
		return 1; 	 	  		//�յ�����
	}
	else
	{
		return 0;
	}
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
	TxRxBuffer[i]=SpiReadSpiWrite(0);	  // ��ȡ���ݽ��ջ���������       
	}
	Hign_nrf905_CSN;
    Delay(2);                            //
	Hign_nrf905_TRX_CE;							
}
//--------------------------------���ý���ģʽ----------------------------------
void  RX(void)
{
    SetRxMode();			          //����NRF905����ģʽ
    while (CheckDR()==0);	         //�ȴ��������
	RxPacket();                     //��ȡ�������ݻ�����
	Delay(10);
}
//------------------------------������------------------------------------------
void main(void)
{  
	uint i;
	DDRD=0xF2;						  //�˿�D����											  
	DDRB=0xB3;					     //�˿�B����	
	PORTA=0x00;
	PORTC=0xbf;
//------------------------------------------------------------------------------	
	Hign_JDQ;			  //�رռ̵���				
	Hign_BELL;							
//------------------------------------------------------------------------------				  			 				
	Spi_initial();	                //SPI��ʼ��															  
	system_Init();				   //ϵͳ״̬��ʼ��												
	Config905();  				  //NRF905��ʼ��	
	
//------------------------------------------------------------------------------
	while(1)
	{
	RX();  					//��������
	if(TxRxBuffer[0])
	{
	if(TxRxBuffer[0]==0x29)
	{
	Low_JDQ;			   //�򿪼̵���
	}
	if(TxRxBuffer[0]==0x30)
	{
	Low_BELL;			   //�򿪷�����

	}
	}
	Delay(200);
	Hign_JDQ;			  //�رռ̵���				
	Hign_BELL;			  //�رշ�����		
	}
}
