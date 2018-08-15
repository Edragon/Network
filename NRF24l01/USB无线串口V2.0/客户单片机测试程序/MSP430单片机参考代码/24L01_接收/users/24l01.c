#include  <msp430x14x.h>
#include "24l01.h"

unsigned char TestBuf=0;


uchar  const TX_ADDRESS[TX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; // Define a static TX address
uchar rx_buf[RX_PLOAD_WIDTH];        
uchar tx_buf[]={0x0c,0xc9,0xcf,0xba,0xa3,0xb1,0xa6,0xc7,0xb6,0xb5,0xe7,0xd7,0xd3};//�Ϻ���Ƕ����
uchar flag,q;

//******************************************************************************************
//��ʱ����
//******************************************************************************************

void delay_50us(unsigned int i)
{
	//for(unsigned char i=0; i<77; i++);
	unsigned long j;
	for(;i>0;i--)
	{
		for(j=0;j<33;j++);//50.4us
	}
}

void delay_100ms(unsigned int i)
{
	unsigned long j;
	for(;i>0;i--)
	{
		for(j=0;j<144200;j++);
	}
}

void msDelay(unsigned int ms)
{
    unsigned int i,j;
	
    for(i=0;i<ms;i++)
    {
       j=1329;;
       while(j--);
    }
}
void delay_1ms(unsigned int i)
{
	unsigned long j;
	for(;i>0;i--)
	{
		//for(j=0;j<640;j++);//8M--->880us
		for(j=0;j<730;j++);//8M--->1ms
		//for(j=0;j<80;j++);//1M
		//for(j=0;j<200;j++);//1M 1ms��ʱ�ǶԵģ���345������12ms��׼������ˣ���Ӱ��������
	}
}
void inerDelay_us(int n)
{
	for(;n>0;n--);
}

//***********************************************************************************
void CE_Pin(BYTE state)
{
    if(state)
    nRF24L01_CE_1;
  else
    nRF24L01_CE_0;
}

//***********************************************************************************
//***********************************************************************************
void CSN_Pin(BYTE state)                                // Set/reset CSN pin
{
    if(state)
    nRF24L01_CSN_1;
  else
    nRF24L01_CSN_0;
}
//***********************************************************************************
//***********************************************************************************
void SCK_Pin(BYTE state)                                // Set/reset SCK pin
{
  if(state)
    nRF24L01_SCK_1;
  else
    nRF24L01_SCK_0;
}
//***********************************************************************************
//***********************************************************************************
void MOSI_Pin(BYTE state)                               // Set/reset MOSI pin
{
  if(state)
    nRF24L01_MOSI_1;
  else
    nRF24L01_MOSI_0;
}
//***********************************************************************************
//***********************************************************************************

BYTE MISO_Pin(void)                                     // Read MISO pin
{
  return nRF24L01_MISO_IN;
}
//**************************************************
//Function: SPI_RW();

//escription:
 // Writes one byte to nRF24L01, and return the byte read
 // from nRF24L01 during write, according to SPI protocol
//**************************************************/
uchar SPI_RW(uchar byte)
{
	uchar bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++)   // output 8-bit
   	{
   		MOSI_Pin(byte&0x80);         // output 'byte', MSB to MOSI
   		byte = (byte << 1);           // shift next bit into MSB..
   		SCK_Pin(1);// Set SCK high..
   		byte|=MISO_Pin();       		  // capture current MISO bit
   		SCK_Pin(0);            		  // ..then set SCK low again
   	}
    return(byte);           		  // return read byte
}
/**************************************************/

//**************************************************
//Function: SPI_RW_Reg();

//Description:
 // Writes value 'value' to register 'reg'
//**************************************************/
uchar SPI_RW_Reg(BYTE reg, BYTE value)
{
        uchar status;
  	CSN_Pin(0);                   // CSN low, init SPI transaction
  	status = SPI_RW(reg);      // select register
  	SPI_RW(value);             // ..and write value to it..
  	CSN_Pin(1);                   // CSN high again

  	return(status);            // return nRF24L01 status byte
        
}
/**************************************************/

/**************************************************
Function: SPI_Read();

Description:
  Read one byte from nRF24L01 register, 'reg'
**************************************************/
BYTE SPI_Read(BYTE reg)
{
	BYTE reg_val;

  	CSN_Pin(0);                // CSN low, initialize SPI communication...
  	SPI_RW(reg);            // Select register to read from..
  	reg_val = SPI_RW(0);    // ..then read registervalue
  	CSN_Pin(1);                // CSN high, terminate SPI communication

  	return(reg_val);        // return register value
}
/**************************************************/

/**************************************************
Function: SPI_Read_Buf();

Description:
  Reads 'bytes' #of bytes from register 'reg'
  Typically used to read RX payload, Rx/Tx address
**************************************************/
uchar SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes)
{
	uchar status,byte_ctr;

  	CSN_Pin(0);                    		// Set CSN low, init SPI tranaction
  	status = SPI_RW(reg);       		// Select register to write to and read status byte

  	for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
    	pBuf[byte_ctr] = SPI_RW(0);    // Perform SPI_RW to read byte from nRF24L01

  	CSN_Pin(1);                           // Set CSN high again

  	return(status);                    // return nRF24L01 status byte
}
/**************************************************/

/**************************************************
Function: SPI_Write_Buf();

Description:
  Writes contents of buffer '*pBuf' to nRF24L01
  Typically used to write TX payload, Rx/Tx address
**************************************************/
uchar SPI_Write_Buf(BYTE reg, BYTE const *pBuf, BYTE bytes)
{
	uchar status,byte_ctr;

  	CSN_Pin(0);                  // Set CSN low, init SPI tranaction
  	status = SPI_RW(reg);    // Select register to write to and read status byte
  	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) // then write all byte in buffer(*pBuf)
    	SPI_RW(*pBuf++);
  	CSN_Pin(1);                 // Set CSN high again
  	return(status);          // return nRF24L01 status byte
}
/**************************************************/

//***********************************************************************************
/**************************************************
Function: RX_Mode();

Description:
  This function initializes one nRF24L01 device to
  RX Mode, set RX address, writes RX payload width,
  select RF channel, datarate & LNA HCURR.
  After init, CE is toggled high, which means that
  this device is now ready to receive a datapacket.
**************************************************/
void RX_Mode(void)
{
        CE_Pin(0);
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, RX_ADR_WIDTH); 
	SPI_RW_Reg(WRITE_REG + EN_AA, ENAA_P0); 
	SPI_RW_Reg(WRITE_REG + SETUP_RETR,0x1a);
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //ʹ��ͨ��0�Ľ��յ�ַ 
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //����RFͨ��Ϊ2.400GHz  Ƶ��=2.4+0GHz
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); 
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x0F);   //����TX�������,0db����,2Mbps,���������濪��
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   
        CE_Pin(1);
}
/**************************************************/

/**************************************************
Function: TX_Mode();

Description:
  This function initializes one nRF24L01 device to
  TX mode, set TX address, set RX address for auto.ack,
  fill TX payload, select RF channel, datarate & TX pwr.
  PWR_UP is set, CRC(2 bytes) is enabled, & PRIM:TX.

  ToDo: One high pulse(>10us) on CE will now send this
  packet and expext an acknowledgment from the RX device.
**************************************************/
void TX_Mode(void)
{
	CE_Pin(0);
	
  	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, RX_ADR_WIDTH); 
	SPI_RW_Reg(WRITE_REG + EN_AA, ENAA_P0);  
	SPI_RW_Reg(WRITE_REG + SETUP_RETR,0x1a);
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); 
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x0F);   //����TX�������,0db����,2Mbps,���������濪�� 
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   
	CE_Pin(1);

}


/**************************************************/

void nRF24L01_Init(unsigned char Mode)
{
	TestBuf = SPI_Read(RX_ADDR_P4);//return is 0xC5,if connection is ok

	if(Mode == nRF_TX_Mode)
		TX_Mode();
	else RX_Mode();
	delay_1ms(2);//24L01 ����ģʽ������ģʽ��Ҫ1.5ms
}


void nRF24L01_Send(void)
{
		SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); // Writes data to TX payload
}

void nRF24L01_Revceive(void)
{
               TestBuf = SPI_Read(STATUS); 
		SPI_RW_Reg(WRITE_REG+STATUS,TestBuf);
		if(TestBuf&RX_OK)
		{		
			SPI_Read_Buf(RD_RX_PLOAD, rx_buf, RX_PLOAD_WIDTH);
			SPI_RW_Reg(FLUSH_RX, 0xff);
                        if(rx_buf[1]=='1')P2OUT ^=0xFF;
		}
		
}
/*
 * ��������NRF_Check
 * ����  ����Ҫ����NRF��MCU�Ƿ���������
 * ����  ����	
 * ���  ��SUCCESS/ERROR ��������/����ʧ��
 * ����  ���ⲿ����
 */
uchar NRF_Check(void)
{
	uchar buf[5]={0xC2,0xC2,0xC2,0xC2,0xC2};
	uchar buf1[5];
	uchar i; 
	 
	/*д��5���ֽڵĵ�ַ.  */  
	SPI_Write_Buf(WRITE_REG+TX_ADDR,buf,5);

	/*����д��ĵ�ַ */
	SPI_Read_Buf(TX_ADDR,buf1,5); 
	 
	/*�Ƚ�*/               
	for(i=0;i<5;i++)
	{       
		if(buf1[i]!=0xC2)
		break;            
	} 
	       
	if(i==5)
		return 1 ;        //MCU��NRF�ɹ����� 
	else
		return 0 ;        //MCU��NRF����������
              
}

void nRF24L01_IO_set(void)
{
      P4DIR |= BIT4;         //ce
      //P4OUT = BIT4;         //ce
      P4DIR |= BIT5;         //csn
      P5DIR |= BIT3;         //sck
      P5DIR |= BIT2;         //mosi out
      P5DIR &=~BIT1;         //MISO IN 
      P1DIR &=~BIT4;         //IRQ
      
      SCK_Pin(0);
      CE_Pin(1);
}

