//ICC-AVR application builder : 2007-8-11 20:37:32
// Target : M16
// Triter : chenjia
// Crystal: 8.0000Mhz
#include <iom16v.h>
#include <macros.h>
//------------------------------------------------------------------------------
#define uint  unsigned int
#define uchar unsigned char
//----------------------------�¶ȱ���------------------------------------------
uchar  temp_data[2]={0x00,0x00};
uchar  dispaly[7];
uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9����
uchar seg1[10]={0x40,0x4F,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; 
//******************************************************************************
//***********************DS18B20--------PD6*************************************
//******************************************************************************
#define   In_DQ      DDRD &= ~(1 << PD6)       
#define   Out_DQ     DDRD |= (1 << PD6) 
//------------------------------------------------------------------------------
#define   Hign_DQ    PORTD |= (1 << PD6)   
#define   Low_DQ     PORTD &= ~(1 << PD6)
//------------------------------------------------------------------------------
#define   Read_DQ    PIND & (1 << PD6)
//******************************************************************************
//***********************NRF905�˿�����*****************************************
//******************************************************************************
///////////////////////////ģʽ���ƶ���/////////////////////////////////
//#define  nrf905_TX_EN	  PB0	    //���1
#define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
#define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
//#define  nrf905_TRX_CE  PD4 	    //���1
#define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4);   
#define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4); 
//#define  nrf905_PWR     PB1 	    //���1
#define   Hign_nrf905_PWR    PORTB |= (1 << PB1);   
#define   Low_nrf905_PWR     PORTB &= ~(1 << PB1); 
///////////////////////////SPI�ڶ���////////////////////////////////////
//#define  nrf905_MISO	  PB6   	//����0
//#define  nrf905_MOSI    PB5	    //���1
//#define  nrf905_SCK     PB7	    //���1
#define   Low_nrf905_SCK     PORTB &= ~(1 << PB7); 
////////////////////////////////////////////////////////////////////////
//#define  nrf905_CSN     PB4		//���1		
#define   Hign_nrf905_CSN    PORTB |= (1 << PB4);   
#define   Low_nrf905_CSN     PORTB &= ~(1 << PB4); 						
///////////////////////////״̬�����///////////////////////////////////
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
//----------------------------------905-SPIָ��---------------------------------
#define WC	0x00
#define RRC	0x10
#define WTP	0x20
#define RTP	0x21
#define WTA	0x22
#define RTA	0x23
#define RRP	0x24
//---------------------------------��������-------------------------------------
uchar TxRxBuf[4] ;
//----------------------------------���յ�ַ------------------------------------
uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
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
void delay(uint x);
void Spi_initial();
uchar SpiReadSpiWrite(uchar DATA);
void system_Init(void);
void Config905(void);
void TxPacket(void);
void SetTxMode(void);
void TX(void);
void StartUART(void);
void R_S_Byte(uchar R_Byte);
//------------------------------------------------------------------------------
void Init_DS18B20(void);
uchar ReadOneChar(void);
void WriteOneChar(uchar dat);
void ReadTemperature(void);
void work_temp();
void StartUART(void);
void R_S_Byte(uchar R_Byte);
void DS1820_delay(uint i);
//------------------------------------------------------------------------------
//**********************************NRF905����**********************************
//******************************************************************************
//----------------------------------100us��ʱ�ӳ���-----------------------------
void delay(uint x)
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
	delay(1);				// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config commandд����������
	for (i=0;i<11;i++)			// Write configration words  д��������
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
	delay(1);
	SpiReadSpiWrite(WTP);				// д����ǰ��дд��������
	for (i=0;i<4;i++)
	{
	SpiReadSpiWrite(  dispaly[i]);		// �����͵�32�ֽ�����
	}						
	Hign_nrf905_CSN;
	delay(1);							// �ر�Spi���������nrf905���ж�д����
	Low_nrf905_CSN;								// ʹ��Spi
	SpiReadSpiWrite(WTA);				// д��ַǰ������д��ַ����
	for (i=0;i<4;i++)					// д 4 bytes ��ַ
	{
	SpiReadSpiWrite(TxAddress[i]);
	}
	Hign_nrf905_CSN;					// �ر�Spi
	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	delay(1);							// �ȴ�DR���
	Low_nrf905_TRX_CE;							// ����TRX_CE=0
}
//-------------------------------����ģʽ����-----------------------------------
void SetTxMode(void)
{
	Low_nrf905_TRX_CE;				//
	Hign_nrf905_TX_EN;				//����ʹ��
	delay(2); 				// delay for mode change(>=650us)���ݾ���ͬҪ�ı�
}
//------------------------------------------------------------------------------
void TX(void)
{
     SetTxMode();	   // Set nRF905 in Tx mode
	 TxPacket();			   // Send data by nRF905
}
//******************************************************************************
//**********************************DS18B20�¶Ȳɼ�*****************************
//******************************************************************************

//----------------------------------��ʱ����------------------------------------
void DS1820_delay(uint i)
{
	while(i--);
}
//---------------------------------DS18B20��ʼ��--------------------------------
void Init_DS18B20(void)
{
    unsigned char x=1;
	
	Out_DQ;                //�������
	Hign_DQ;              //�øߵ�ƽ
	Low_DQ;			     //�õ͵�ƽ
	DS1820_delay(3000);	    //400-960us
	Hign_DQ;		   //�øߵ�ƽ
	In_DQ ;
	DS1820_delay(40);		  //15-60us
	while(Read_DQ)	 ; 
	Out_DQ ;
	Hign_DQ;
	DS1820_delay(300);	
}
//---------------------------------DS18B20������--------------------------------
uchar ReadOneChar(void)
{
    uchar i;
	uchar dat = 0;
	
	for(i=8;i>0;i--)
	{
	    Out_DQ;    //�������
	    Low_DQ;   //�õ͵�ƽ
		dat >>= 1;
		Hign_DQ; //�øߵ�ƽ
		In_DQ;  //��������
		if(Read_DQ)//��ȡ��ƽ
        {
		dat |= 0x80;
        }
		Out_DQ;//�������
        DS1820_delay(50);
	}
	return(dat);
}
//------------------------------DS18B20д����-----------------------------------
void WriteOneChar(uchar dat)
{
    uchar i;
	Out_DQ;//�������
	for(i=8;i>0;i--)
	{
	    Low_DQ;//�õ͵�ƽ
		if(dat&0x01)//д��ƽ
        {
        Hign_DQ;//�øߵ�ƽ
        }
        else
        {
         Low_DQ;//�õ͵�ƽ
        }
		DS1820_delay(40);
		Hign_DQ;//�øߵ�ƽ
		dat >>= 1;
	}
	DS1820_delay(8);
}
//------------------------------------��ȡ�¶�------------------------------------
void ReadTemperature(void)
{		
	Init_DS18B20();
	WriteOneChar(0xCC); 			// ����������кŵĲ���
	WriteOneChar(0x44); 			// �����¶�ת��
	
	
	Init_DS18B20();
	WriteOneChar(0xCC); 			//����������кŵĲ���
	WriteOneChar(0xBE); 			//��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�

	temp_data[0]= ReadOneChar();   		//��ȡ�¶�ֵ��λLSB
	temp_data[1]= ReadOneChar();   //��ȡ�¶�ֵ��λMSB
	
}
//-----------------------------------BCD���¶ȴ���------------------------------
//dispaly[0]ʮλ
//dispaly[1]��λ
//dispaly[2]С��λ
//dispaly[3]�ٽ��־λ
//------------------------------------------------------------------------------
void work_temp()
{
	uchar n=0;
	if(temp_data[1]>127)
	{
	temp_data[1]=(256-temp_data[1]);
	temp_data[0]=(256-temp_data[0]);
	n=1;
	}
//------------------------------------------------------------------------------
	dispaly[6]=((temp_data[0]&0xf0)>>4)|((temp_data[1]&0x0f)<<4);
	dispaly[5]=dispaly[6]/100;				//��λ
	dispaly[4]=dispaly[6]%100;				//
	dispaly[2]=dispaly[4]/10;               //ʮλ
	dispaly[1]=dispaly[4]%10;			    //��λ
	
	switch	(temp_data[0]&0x0f)
	{
	case 0x0f:dispaly[0]=9;break;
	case 0x0e:dispaly[0]=9;break;
	case 0x0d:dispaly[0]=8;break;
	case 0x0c:dispaly[0]=8;break;
	case 0x0b:dispaly[0]=7;break;
	case 0x0a:dispaly[0]=6;break;
	case 0x09:dispaly[0]=6;break;
	case 0x08:dispaly[0]=5;break;
	case 0x07:dispaly[0]=4;break;
	case 0x06:dispaly[0]=4;break;
	case 0x05:dispaly[0]=3;break;
	case 0x04:dispaly[0]=3;break;
	case 0x03:dispaly[0]=2;break;
	case 0x02:dispaly[0]=1;break;
	case 0x01:dispaly[0]=1;break;
	case 0x00:dispaly[0]=0;break;
	default:break;
	}
		if(n)								//�¶���������
	{
	dispaly[3]=0x11;						//����
	}
	else
	{
	dispaly[3]=0x22;				  	//����
	}
}

//------------------------------------------------------------------------------
void dis_zhuye()
{
	 PORTC=seg[dispaly[2]];
	 Hign_Display4;
	 Hign_Display3;
	 Hign_Display2;
	 Low_Display1;
	 delay(80);
	 Hign_Display1;
//------------------------------------------------------------------------------
	 PORTC=seg1[dispaly[1]];
	 Low_Display2;
	 delay(80);
	 Hign_Display2;
//------------------------------------------------ ---------------------------
	 PORTC=seg[dispaly[0]];
	 Low_Display3;
	 delay(80);
	 Hign_Display3;
//----------------------------------------------------------------------------- 
	 PORTC=0xc6;
	 Low_Display4;
	 delay(80);
	 Hign_Display4;	 
}
//----------------------------------������--------------------------------------
main()
{
//------------------------------------------------------------------------------
	DDRD=0xb2;		  //
	DDRB=0xB3;		  //
	DDRA=0x1e;       //
	DDRC=0xff; 		//LED�˿�����
	PORTA = 0xff;
	Hign_BELL;	
	Hign_JDQ ;	
//------------------------------------------------------------------------------
	Spi_initial();
	system_Init();
	Config905();
	Init_DS18B20();
while(1)
	{
	ReadTemperature();		//��ȡ�¶�
	work_temp();			//�¶ȴ���
	dis_zhuye();
 	TX();	
    }
}
