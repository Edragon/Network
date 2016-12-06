#include "nRF905.h"


#define uchar unsigned char 
#define uint  unsigned int

unsigned char TxAddress[4]={TX_ADDR_Byte0,TX_ADDR_Byte1,TX_ADDR_Byte2,TX_ADDR_Byte3};

RFConfig RxTxConf =
{
	10,
	RFConfig_Byte0, 	RFConfig_Byte1, 	RFConfig_Byte2, 	RFConfig_Byte3, 	RFConfig_Byte4,
	RFConfig_Byte5, 	RFConfig_Byte6, 	RFConfig_Byte7, 	RFConfig_Byte8, 	RFConfig_Byte9	
};


static void Delay(uchar n)
{
	uint i;
	while(n--)
	for(i=0;i<80;i++);	
}




/*******************************************************************************************/
//function InitIO();		初始化IO
/*******************************************************************************************/
void nRF905Init(void)
{
	/*SPI init*/
	SpiInit();
	//CSN=1;						// Spi 	disable						
	//SCK=0;						// Spi clock line init high
	DR=1;						// Init DR for input
	AM=1;						// Init AM for input
	PWR_UP=1;					// nRF905 power on
	Delay(4);
	TRX_CE=0;					// Set nRF905 in standby mode
	TX_EN=0;					// set radio in Rx mode	

	//====================
	/*
	TX_EN_DDR	= 1;
	TRX_CE_DDR	= 1;
	PWR_UP_DDR	= 1;
	DR_DDR		= 0;
	CD_DDR		= 0;
	*/
	//====================
}


/*******************************************************************************************/
//function WriteTxAddress();	写入目标地址
/*******************************************************************************************/
void WriteTxAddress(void)
{
	unsigned char i;
	unsigned char len= (RxTxConf.buf[2]>>4);
	CSN=0;						// Spi enable for write a spi command	
	SpiWrite(WTA);				// Write address command
	//for (i=0;i<TX_AWF;i++) 
	for (i=0;i<len;i++)
	{
		SpiWrite(TxAddress[i]);
	}	
	CSN=1;						// Spi disable
}


/*******************************************************************************************/
//function Config905();			//配置905寄存器
/*******************************************************************************************/
void Config905(void)
{
	uchar i;					
	CSN=0;						// Spi enable for write a spi command
	SpiWrite(WC);				// Write config command写放配置命令
	for (i=0;i<RxTxConf.n;i++)	// Write configration words  写放配置字
	{
		SpiWrite(RxTxConf.buf[i]);
	}
	CSN=1;						// Disable Spi

	WriteTxAddress();
}




/*******************************************************************************************/
//function SetTxMode();			设置为发送模式
/*******************************************************************************************/
void SetTxMode(void)				
{	
	TRX_CE=0;
	TX_EN=1;
	Delay(1); 					// delay for mode change(>=650us)
}				

/*******************************************************************************************/
//function SetRxMode();			设置为接收模式
/*******************************************************************************************/
void SetRxMode(void)
{
	TX_EN=0;
	TRX_CE=1;
	Delay(1); 					// delay for mode change(>=650us)				
}




//发送数据包
/*******************************************************************************************/
void TxPacket(unsigned char *TxBuf)
{
	uchar i;

	CSN=0;						// Spi enable for write a spi command	
	SpiWrite(WTP);				// Write payload command
	//for (i=0;i<TX_PW;i++)
	for (i=0;i<RxTxConf.buf[4];i++)
	{
		SpiWrite(TxBuf[i]);		// Write 32 bytes Tx data
	}
	CSN=1;						// Spi disable						

	TRX_CE=1;					// Set TRX_CE high,start Tx data transmission
	Delay(1);					// while (DR!=1);
	TRX_CE=0;					// Set TRX_CE low
}

/*
*******************************************************************************************
*	读取数据包
*	返回值:		1-成功接收到数据		0-没有接收到数据
*******************************************************************************************
*/
unsigned char RxPacket(unsigned char *RxBuf)
{
	uchar i;
	if (DR)		//DR 高电平		有接收到数据
	{
		TRX_CE=0;					// Set nRF905 in standby mode	

		CSN=0;						// Spi enable for write a spi command
		SpiWrite(RRP);				// Read payload command	
		//for (i = 0 ;i < RX_PW ;i++)
		for (i = 0 ;i < RxTxConf.buf[3] ;i++)
		{
			RxBuf[i]=SpiRead();		// Read data and save to buffer		
		}
		CSN=1;						// Disable spi
		while(DR);//||AM);	

		TRX_CE=1;

		return 1;
	}
	else
	{
		return 0;
	}
}
/*******************************************************************************************/
/*
#ifdef SET_CHNO_ENABLE
	void SetFrequence(unsigned int fre)
	{
		unsigned char k;

	    CSN=0;					// Spi enable for write a spi command
		SpiWrite(WC);				// Write config command写放配置命令
		k = (fre/2)&0xff;
		SpiWrite(k);				//写入CH_NO高8位
		if ( (fre&0x01)==1)
		{
			k = RFConfig_Byte1 | 0x01;	//最低位置位
		}
		else
		{
			k = RFConfig_Byte1 & 0xfe;	//最低位清零
		}	
		SpiWrite(k);				//写入CH_NO最低位
		CSN=1;					// Disable Spi
	}

#endif
 */


/*******************************************************************************************/
/*
#ifdef SETST_BYMODE_ENABLE
	void SetST_BYmode(void)
	{
		TX_EN=0;
		TRX_CE=0;
		Delay(1); 					// delay for mode change(>=650us)				
	}
#endif
*/
/*******************************************************************************************/
/*
#ifdef SETRF_PA_PWR_ENABLE
	//RF-Configure-Register byte:1
	code unsigned char RF_byte1[4]={0x00,0x04,0x08,0x0c};
	//不同的发射功率
	void SetRF_PA_PWR(unsigned char i)	//SPI->设置发射功率
	{
		SPI_CSN=0;						// Spi enable for write a spi command
		SpiWrite(0x01);				// Write config command写放配置命令 从1号字节开始写
		SpiWrite(RF_byte1[i]);
		SPI_CSN=1;						// Disable Spi
	}
#endif
 */
