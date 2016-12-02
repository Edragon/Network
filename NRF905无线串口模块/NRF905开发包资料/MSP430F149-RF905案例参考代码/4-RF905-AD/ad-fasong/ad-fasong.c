/****************************************************************************
 **
 **     NewMsg-RFDevKit5000
 **
 **     File version: $2009.2.1$
 **
 ***************************************************************************/
#include <msp430x14x.h>
#define  uchar   unsigned char
#define  uint    unsigned int
#define  uclong  unsigned long
//===========================DS18B20�˿�========================================
#define  OUT_DS18B20_0     P6OUT &=~BIT7          //���0
#define  OUT_DS18B20_1     P6OUT |= BIT7          //���1
#define  DS18B20_IN        P6DIR &=~BIT7          //��������Ϊ����
#define  DS18B20_OUT       P6DIR |= BIT7          //��������Ϊ���
//==================TXEN��TRX_CE��PWR_0 Ϊ�շ�ģʽ���ƶ˿�======================
#define  TXEN_0     P2OUT &=~BIT0          //���0
#define  TXEN_1     P2OUT |= BIT0          //���1
//==============================================================================
#define  TRX_CE_0   P2OUT &=~BIT1
#define  TRX_CE_1   P2OUT |= BIT1
//==============================================================================
#define  PWR_0      P2OUT &=~BIT2
#define  PWR_1      P2OUT |= BIT2
//===================================����ӳ�===================================
#define  MISO_0     P3OUT &=~BIT2      
#define  MISO_1     P3OUT |= BIT2         
//==================================��������====================================
#define  MOSI_0     P3OUT &=~BIT1         
#define  MOSI_1     P3OUT |= BIT1        
//===================================SPIʱ�Ӷ˿�================================
#define  SCK_0      P3OUT &=~BIT3         
#define  SCK_1      P3OUT |= BIT3         
//===================================SPIʹ�ܶ˿�=================================
#define  CSN_0      P3OUT &=~BIT0
#define  CSN_1      P3OUT |= BIT0
//==================================����Ϊ״̬�˿�==============================
//===========================AM  ��ַƥ��=======================================
#define  AM_0       P2OUT &=~BIT5       
#define  AM_1       P2OUT |= BIT5
//=================================DR ���ݽ���״̬==============================
#define  DR_0       P2OUT &=~BIT6
#define  DR_1       P2OUT |= BIT6
//=====================================CD �ز�����״̬==========================
#define  CD_0       P2OUT &=~BIT4
#define  CD_1       P2OUT |= BIT4
//==============================================================================
#define  LED1_0     P6OUT &=~BIT1          //���0
#define  LED1_1     P6OUT |= BIT1          //���1
#define  LED2_0     P6OUT &=~BIT2          //���0
#define  LED2_1     P6OUT |= BIT2          //���1
//============================DS18B20�Ĵ���ָ��=================================
#define DS18B20_READ_ROM          0x33
#define DS18B20_MATCH_ROM         0X55
#define DS18B20_SKIP_ROM          0XCC
#define DS18B20_SEARCH_ROM        0XF0
#define DS18B20_ALARM_SEARCH_ROM  0XEC
#define DS18B20_WRITE_RAM         0X40
#define DS18B20_READ_RAM          0XBE
#define DS18B20_COPY_RAM          0X48 
#define DS18B20_CONVERT_TEM       0X44
#define DS18B20_EECALL_EEPROM     0XB8
#define DS18B20_READ_POWER_SUPPLY 0XB4
//===========================NRF905:SPIָ��=====================================
#define WC		          0x00
#define RC		          0x10
#define WTP		          0x20
#define RTP		          0x21
#define WTA		          0x22
#define RTA		          0x23
#define RRP		          0x24
//===========================AD��ر���====================================
char UART0_RX_BUF[],nRX0_Len_temp,nRX0_Len;
unsigned int ADC_Buf1[32];
unsigned int ADC_Buf2[32];
unsigned int ADC_BUF_Temp1[32];
unsigned int ADC_BUF_Temp2[32];
unsigned int nADC_Count=0; 
char AD_TxBuf[4]={0x22,0x22,0x22,0x22};
//==========================NRF905��ر���======================================
#define TxRxBuf_Len 4                             
unsigned char TxRxBuf[TxRxBuf_Len]={0x01,0x02,0x03,0x22};
char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};   //NRF905���յ�ַ
char DATA_BUF;
//==========================NRF905:10�ֽڼĴ�����ʼ��===========================
unsigned char  RFConf[11]=
{
  WC,                                //SPIд��������
  0x4c,                             //CH_NO,����Ƶ����430MHZ
  0x0C,                             //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
  0x44,                             //��ַ������ã�Ϊ4�ֽ�
  0x04,0x04,                        //���շ�����Ч���ݳ���Ϊ4�ֽ�
  0xCC,0xCC,0xCC,0xCC,              //���յ�ַ
  0x58,                              //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
}; 
//================================ϵͳʱ�ӵȳ�ʼ��==============================
void InitSys()
{
   unsigned int iq0;
   _DINT();
   BCSCTL1 &=~XT2OFF;
   do
   {
      IFG1 &= ~OFIFG;			// �������ʧЧ��־
  for (iq0 = 0xFF; iq0 > 0; iq0--);	// ��ʱ���ȴ�XT2����
   }
   while ((IFG1 & OFIFG) != 0);		// �ж�XT2�Ƿ�����	
   BCSCTL2 +=SELM0; 
   BCSCTL2 +=SELS;                //MCLK,SMCLKʱ��ΪXT2
       _EINT();        //��ȫ���жϿ��ƣ�������Ҫ�򿪣��������α���
}
//==============================================================================
void ADC_IO_set(void)
{
  P6DIR= P6DIR&0XFE;              //����P6.0-P6.1ΪAD�ɼ�����
  P6SEL= P6SEL|0X01;              //����P6.0-P6.
}
//===========================��ʼ��nRF905=======================================
void nRF905_IO_set(void)
{
        P2DIR |= 0x07; P2DIR &= 0x8F;   P2SEL&=0x84;        
        P3DIR |= 0xC0; P3DIR |= 0xFB;   P3SEL&=0xF0;        
        CSN_1;				            // Spi 	disable
	SCK_0;				          // Spi clock line init low
	PWR_1;					 // nRF905 power on
	TRX_CE_0;				// Set nRF905 in standby mode
	TXEN_0;					// set radio in Rx mode
}
//==============================================================================
void LED_IO_set(void)
{    
        P6DIR |= 0x06;   P6SEL&=0xf9;        
}
//==========================��ʱ================================================
void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);
}
//=============================TIMERA��ʼ��=====================================
void Init_TimerA(void)
{
  TACTL=TASSEL1+TACLR;
  CCTL0=CCIE;
  CCR0=40000;
  TACTL |=MC0;
}
/**********************************************************
�������ƣ�TimerA_ISR
�������ܣ���ʱ��A�жϣ����ڲɼ�AD
��    �룺
��    ����ADC_Buf[]
**********************************************************/
#if __VER__<200
  interrupt [TIMERA0_VECTOR] void TimerA_ISR(void)
#else
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
#endif
{   
    int i;
    ADC12CTL0&=~(ENC);    //������ת��
    ADC_Buf1[nADC_Count]=ADC12MEM0;//����ͨ��0����
    ADC_Buf2[nADC_Count]=ADC12MEM1; //����ͨ��1����   
    nADC_Count+=1;
    if(nADC_Count==32)         //����32��
    {
      nADC_Count=0;
      for(i=0;i<32;i++) 
      {
        ADC_BUF_Temp1[i]=ADC_Buf1[i];
        ADC_BUF_Temp2[i]=ADC_Buf2[i];
      }
    }
    ADC12CTL0 |=ENC+ADC12SC;      //����ADת��������ʼ����
}
/*********************************************************
�������ƣ�Init_ADC(void)
�������ܣ�ad��ʼ��
��    �룺
��    ����
*********************************************************/
void Init_ADC(void)
{
  ADC12CTL0&=~(ENC);    //�ر�AD���Ӷ�����������ADת������ƼĴ�����ADC12�Ĵ���  
                        //����#define ENC (0x002)   /* ADC12 Enable Conversion
  ADC12CTL0 |=REF2_5V+REFON;//�����ڲ��ο���ѹ���ο���ѹ���ڲ�2.5V��
//==============================================================================
  ADC12CTL1 |=CSTARTADD_0;    //ת������ʼ��ַΪ��ADCCME0�������� CSTARTADD_0----->CSTARTADD_15ѡ��
  ADC12MCTL0=INCH_0;        //���òο���ѹ�ֱ�ΪAVSS��AVCC������ͨ��ΪA0
  ADC12MCTL1=INCH_1+SREF_1; //���òο���ѹ�ֱ�ΪAVSS��REFF+������ͨ��ΪA1
  ADC12MCTL2=INCH_2+EOS;   //ת��ͨ���Ӵ�
//==============================================================================
  ADC12CTL0|=ADC12ON;     //��ADC12ģ�飬���Խ���ת��
  ADC12CTL0|=MSC;         //MSC=1ʱ���״�ת����SHI�ź������ش���������ʱ��������Ĳ����͵�һ�������������
//==============================================================================
  ADC12CTL1|=CONSEQ_1;     //ת��ģʽ:����ͨ��������ת��
  ADC12CTL1|=ADC12SSEL_1;  //SMCLK
  ADC12CTL1|=ADC12DIV_0;   //ʱ�ӷ�ƵΪ1 
  ADC12CTL1|=(SHP);        //���������ɶ�ʱ������
    
  ADC12CTL0|=ENC;         //ʹ��ADCת������
  return;
}
/***********************************************************
�������ܣ��Բɼ�����AD�����˲�����
�������ƣ�filter
***********************************************************/
unsigned int filter(void)
{
  unsigned long temp;
  unsigned int result;
  unsigned char n;
  temp=0;
  for(n=0;n<32;n++)   //��ͨ��1���ݽ������ƽ���˲�
  {
    temp += ADC_BUF_Temp1[n];
  }
  temp>>=5;           //����32
  temp*=2500;         //����2500mV
  result=temp>>12;    //1/4096
 
  return result;
}
//--------------------------------//AD���ݲɼ���λ------------------------------
unsigned char GetBaiwei(unsigned char temp)   
{
	temp= temp/100;
        return temp;
}
//-----------------------------//AD���ݲɼ�ʮλ---------------------------------
unsigned char  GetShiwei(unsigned char temp)  
{
	if(temp > 99)
	{
	temp = temp - GetBaiwei(temp)*100;
	}
	temp= temp/10;
        return temp;
}
//---------------------------- //AD���ݲɼ���λ---------------------------------
unsigned char  GetGewei(unsigned char temp)   
{
	temp= temp%10;
        return temp;
}

//=========================NRF905 SPI��������IOģ��SPIʱ��==================
unsigned char SpiRead(void)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		DATA_BUF=DATA_BUF<<1;
		SCK_1;
		if ((P3IN&0x04))	//��ȡ���λ����������ĩβ��ͨ������λ��������ֽ�
		{
			DATA_BUF|=0x01;
		}
		else
		{
			DATA_BUF&=~(0x01);
		}
		SCK_0;
	 }
	 return DATA_BUF;
}
//=========================NRF905 SPI��д������IOģ��SPIʱ��==================
void SpiWrite(unsigned char send)
{
	unsigned char i;
	DATA_BUF=send;
	for (i=0;i<8;i++)
	{
	if (((DATA_BUF&0x80) != 0))	//���Ƿ������λ
        {
	    MOSI_1;
	 }
	else
	 {
	    MOSI_0;
	 }
	SCK_1;
	DATA_BUF=DATA_BUF<<1;
	SCK_0;
	}
}
//==================================��ʼ��NRF905================================
void Config905(void)
{
	uchar i;
	CSN_0;			// Spi enable for write a spi command
	for (i=0;i<11;i++)	// Write configration words  д��������
	{
	   SpiWrite(RFConf[i]);
	}
	CSN_1;					//�ر�SPI
}
//=========================NRF905װ�ص�ַ+���ݴ��+���ݷ���=====================
void TxPacket(void)
{
	uchar i;
	CSN_0;
	SpiWrite(WTP);				// ��������װ������
	for (i=0;i<4;i++)
	{
	  SpiWrite(AD_TxBuf[i]);
	}
	CSN_1;                                  // �ر�SPI
	Delay(1);		
	CSN_0;					// ��SPI
	SpiWrite(WTA);				// д���ַҪ�ͽ��շ���ַһ��
	for (i=0;i<4;i++)			// 4�ֽڵ�ַ
	{
	  SpiWrite(TxAddress[i]);
	}
	CSN_1;					//�ر�SPI
	TRX_CE_1;					// Set TRX_CE high,start Tx data transmission
	Delay(10);					// while (DR!=1);
	TRX_CE_0;					// Set TRX_CE low
}
//==================================����ģʽ��ʼ��-=============================
void SetTxMode(void)
{
	TRX_CE_0;
	TXEN_1;
	Delay(1); 					// Delay for mode change(>=650us)
}
//==================================���ݷ���===================================
void TX(void)
{
        SetTxMode();
	TxPacket();
}
main()
{
    int a;
    WDTCTL=WDTPW + WDTHOLD;   // Stop watchdog 
    InitSys();
    nRF905_IO_set();
    LED_IO_set();
    ADC_IO_set();
    Init_ADC(); 
    Init_TimerA();  //TIMERA��ʼ��
    Config905();
    LED1_0;    LED2_0;
  while(1)
    {
    a=filter();     //AD���ݴ���
    AD_TxBuf[0]=GetBaiwei(a);  
    AD_TxBuf[1]=GetShiwei(a); 
    AD_TxBuf[2]=GetGewei(a);
    LED1_0; 
    TX();         //AD���ݷ���
    Delay(200);
    Delay(200);
    LED1_1;  
    }
}