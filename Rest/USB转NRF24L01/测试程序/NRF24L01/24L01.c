#include"stm8s.h"
#include"stm8s903k.h"
#include"stm8s903k3.h"
#include"main.h"
#include"24L01.h"

const uchar TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const uchar RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址

//初始化SPI
void MY_SPI_Init(void)
{
	SPI_DeInit();
	
	SPI_Init(SPI_FIRSTBIT_MSB, 
					 SPI_BAUDRATEPRESCALER_2,
					 SPI_MODE_MASTER,
					 SPI_CLOCKPOLARITY_LOW, 
					 SPI_CLOCKPHASE_1EDGE, 													
					 SPI_DATADIRECTION_2LINES_FULLDUPLEX,
					 SPI_NSS_SOFT, 
					 0x07);
				 
	SPI_Cmd(ENABLE);//使能SPI
	
	GPIO_Init(IOPORT_SPI_CS,PIN_SPI_CS,GPIO_MODE_OUT_PP_HIGH_FAST);//SPI_CS引脚初始化为推挽输出
	SPI_CS_HIGH;//取消SPI传输
}

//SPI读写函数
//dat:准备发送的值
//返回值：读取到的值
uchar SPI_ReadWriteByte(uchar dat)
{
	while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
	SPI_SendData(dat);
	
	while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
	return SPI_ReceiveData();
}

//NRF24L01初始化
void NRF24L01_Init(void)
{
	GPIO_Init(IOPORT_24L01_CE,PIN_24L01_CE,GPIO_MODE_OUT_PP_HIGH_FAST);//NRF24L01_CE初始化为推挽输出
	GPIO_Init(IOPORT_24L01_IRQ,PIN_24L01_IRQ, GPIO_MODE_IN_PU_NO_IT);//IRQ上拉输入
	
	MY_SPI_Init();
	
	NRF24L01_CE_LOW;//NRF24L01片选使能
	SPI_CS_HIGH;		//SPI片选取消
}

//检测24L01是否存在
//返回值:0，成功;1，失败	
uchar NRF24L01_Check(void)
{
	uchar buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uchar i;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}	 	 

//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值
uchar NRF24L01_Write_Reg(uchar reg,uchar value)
{
	uchar status;	
	
	SPI_CS_LOW;                 //使能SPI传输
	status =SPI_ReadWriteByte(reg);//发送寄存器号 
	SPI_ReadWriteByte(value);      //写入寄存器的值
	SPI_CS_HIGH;                 //禁止SPI传输	
	
	return(status);       			//返回状态值
}

//读取SPI寄存器值
//reg:要读的寄存器
uchar NRF24L01_Read_Reg(uchar reg)
{
	uchar reg_val;	   
	
 	SPI_CS_LOW;          //使能SPI传输		
	SPI_ReadWriteByte(reg);   //发送寄存器号
	reg_val=SPI_ReadWriteByte(0XFF);//读取寄存器内容
	SPI_CS_HIGH;          //禁止SPI传输		
	
	return(reg_val);           //返回状态值
}	

//在指定位置读出指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值 
uchar NRF24L01_Read_Buf(uchar reg,uchar *pBuf,uchar len)
{
	uchar status,u8_ctr;
	
	SPI_CS_LOW;            //使能SPI传输
	status=SPI_ReadWriteByte(reg);//发送寄存器值(位置), 并读取状态值   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI_ReadWriteByte(0XFF);//读出数据
	SPI_CS_HIGH;       //关闭SPI传输
		
	return status;        //返回读到的状态值	   
}
	//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
uchar NRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar len)
{
	uchar status,u8_ctr;
	
 	SPI_CS_LOW;         //使能SPI传输
	status = SPI_ReadWriteByte(reg);//发送寄存器值(位置), 并读取状态值
	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI_ReadWriteByte(*pBuf++); //写入数据	 
	SPI_CS_HIGH;       //关闭SPI传输
	
	return status;          //返回读到的状态值
}	

//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
uchar NRF24L01_TxPacket(uchar *txbuf)
{
	uchar sta;
	
	NRF24L01_CE_LOW;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//
 	NRF24L01_CE_HIGH;//启动发送	   
	while(NRF24L01_IRQ!=0);//等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //
	if(sta&MAX_TX)//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}

//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
uchar NRF24L01_RxPacket(uchar *rxbuf)
{
	uchar sta;		    							   
	
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //
	if(sta&RX_OK)//接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}			

//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE_LOW;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    	//使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);	//使能通道0的接收地址  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	    	//设置RF通信频率		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);		//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	
  NRF24L01_CE_HIGH; //CE为高,进入接收模式 
}			

//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE_LOW;

	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,
	
	NRF24L01_CE_HIGH;
	delay_10us(5);
}