//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
#define uint  unsigned int
#define uchar unsigned char
//---------------------------------NRF905ģʽ���ƶ���---------------------------------
//#define  nrf905_TX_EN	  PB0	    //���1
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
//#define  nrf905_TRX_CE  PD4 	    //���1
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
#define   Read_nrf905_CD    PINB & (1 << PD3);
//#define  nrf905_AM      PB3	    //����0
#define   Hign_nrf905_AM    PORTB |= (1 << PB3);   
#define   Low_nrf905_AM     PORTB &= ~(1 << PB3); 
#define   Read_nrf905_AM    PINB & (1 << PB3);
//#define  nrf905_DR      PB2  		//����0
#define   Hign_nrf905_DR     PORTB |= (1 << PB2);   
#define   Low_nrf905_DR     PORTB &= ~(1 << PB2); 
#define   Read_nrf905_DR    PINB & (1 << PB2);   
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
uint temp[6];
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9����
uchar seg1[10]={0x40,0x4F,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; 
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
void SetRxMode(void);						   //
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
	for (i=0;i<11;i++)			//дRF905������
	{
	 SpiReadSpiWrite(RFConf[i]);
	}
	Hign_nrf905_CSN;					// Disable Spi
}
//------------------------------���ý���ģʽ����--------------------------------
void SetRxMode(void)
{
	Low_nrf905_TX_EN;
	Hign_nrf905_TRX_CE;
	Delay(10); 					// delay for mode change(>=650us)
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

//----------------------------�¶�LED�ʾ����-----------------------------------
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
//-------------------------------���ڳ�ʼ��-------------------------------------
void StartUART(void)
{
 	 UCSRA=0x00;	
	 UCSRB=0x18;	
	 UCSRC=0x06;	
	 UBRRL=0x67;
	 UBRRH=0x00;
	 UCSRA=UCSRA|0x08;	
}
//------------------------------���ڷ���----------------------------------------
void R_S_Byte(uchar R_Byte)
{	
     UDR= R_Byte;  
}
//------------------------------������------------------------------------------
void main(void)
{  
	uchar i;
	DDRD=0xb2;		  //
	DDRB=0xB3;		  //
	DDRA=0x1e;       //
	DDRC=0xff; 		//LED�˿�����
	PORTA = 0xff;
	Hign_BELL;	
	Hign_JDQ ;			
//------------------------------------------------------------------------------				  			 				
	Spi_initial();	                //SPI��ʼ��															  
	system_Init();				   //ϵͳ״̬��ʼ��												
	Config905();  				  //NRF905��ʼ��	
//------------------------------------------------------------------------------							  
//------------------------------------------------------------------------------
	StartUART();				//���ڳ�ʼ��9600������
	Delay(500);
//------------------------------------------------------------------------------
	while(1)
	{
	RX();  					//��������
	if(TxRxBuffer[0])
		{
		temp[2]=((TxRxBuffer[2]<<4)|TxRxBuffer[1]);		//����λ
		temp[1]=TxRxBuffer[0];							//С��λ
		temp[0]=TxRxBuffer[3];     					    //����λ
		//temp[4]=TxRxBuffer[2];						//ʮλ
		//temp[5]=TxRxBuffer[1];						//��λ
	for(i=0;i<3;i++)
		{
		R_S_Byte(temp[2-i]);      //������ʾ�¶�
		Delay(20);
		}
		
	}
	if((temp[2]>=53)||(temp[2]<=32))//����35��ʱ������0x35ת����10����Ϊ53
									//����20��ʱҲ����,0x20,ת����10����Ϊ	32						  									  																
	{
		Low_BELL;  //�򿪷���������
		Low_JDQ;   //�򿪼̵��������Խ�����ص������ز���
	}
	else
	{
	 	Hign_BELL ;//�رշ���������
		Hign_JDQ;  //�رռ̵���
	}
	dis_zhuye();
	}
}
