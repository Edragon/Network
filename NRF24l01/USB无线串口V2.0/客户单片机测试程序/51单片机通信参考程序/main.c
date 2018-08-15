/**********************************************************/
/* 名   称：NRF24L01+无线USB通信模块程序                  */
/* 功   能：发送接收测试程序                              */
/*          格式：首位是个数，后面跟要发送的数据          */ 
/*                例如：发送5个字节 11 22 33 44 55(16进制)*/
/*                电脑串口发送：1122334455                */
/*                模块实际发送：051122334455              */     
/* 作者：BQDZ     （论坛：http://bqdz.taobao.com）        */
/* 联系方式： QQ :851968194     旺旺：王亚坤2864          */
/*           手机：15821472722（上海）                    */
/**********************************************************/
#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int

/**********  NRF24L01寄存器操作命令  ***********/
#define READ_REG        0x00  //读配置寄存器,低5位为寄存器地址
#define WRITE_REG       0x20  //写配置寄存器,低5位为寄存器地址
#define RD_RX_PLOAD     0x61  //读RX有效数据,1~32字节
#define WR_TX_PLOAD     0xA0  //写TX有效数据,1~32字节
#define FLUSH_TX        0xE1  //清除TX FIFO寄存器.发射模式下用
#define FLUSH_RX        0xE2  //清除RX FIFO寄存器.接收模式下用
#define REUSE_TX_PL     0xE3  //重新使用上一包数据,CE为高,数据包被不断发送.
#define NOP             0xFF  //空操作,可以用来读状态寄存器	 
/**********  NRF24L01寄存器地址   *************/
#define CONFIG          0x00  //配置寄存器地址                             
#define EN_AA           0x01  //使能自动应答功能 
#define EN_RXADDR       0x02  //接收地址允许
#define SETUP_AW        0x03  //设置地址宽度(所有数据通道)
#define SETUP_RETR      0x04  //建立自动重发
#define RF_CH           0x05  //RF通道
#define RF_SETUP        0x06  //RF寄存器
#define STATUS          0x07  //状态寄存器
#define OBSERVE_TX      0x08  // 发送检测寄存器
#define CD              0x09  // 载波检测寄存器
#define RX_ADDR_P0      0x0A  // 数据通道0接收地址
#define RX_ADDR_P1      0x0B  // 数据通道1接收地址
#define RX_ADDR_P2      0x0C  // 数据通道2接收地址
#define RX_ADDR_P3      0x0D  // 数据通道3接收地址
#define RX_ADDR_P4      0x0E  // 数据通道4接收地址
#define RX_ADDR_P5      0x0F  // 数据通道5接收地址
#define TX_ADDR         0x10  // 发送地址寄存器
#define RX_PW_P0        0x11  // 接收数据通道0有效数据宽度(1~32字节) 
#define RX_PW_P1        0x12  // 接收数据通道1有效数据宽度(1~32字节) 
#define RX_PW_P2        0x13  // 接收数据通道2有效数据宽度(1~32字节) 
#define RX_PW_P3        0x14  // 接收数据通道3有效数据宽度(1~32字节) 
#define RX_PW_P4        0x15  // 接收数据通道4有效数据宽度(1~32字节)
#define RX_PW_P5        0x16  // 接收数据通道5有效数据宽度(1~32字节)
#define FIFO_STATUS     0x17  // FIFO状态寄存器
/*————————————————————————————————————————————————————————————————————*/

/******   STATUS寄存器bit位定义      *******/
#define MAX_TX  	0x10  	  //达到最大发送次数中断
#define TX_OK   	0x20  	  //TX发送完成中断
#define RX_OK   	0x40  	  //接收到数据中断
/*——————————————————————————————————————————————————*/

/*********     24L01发送接收数据宽度定义	  ***********/
#define TX_ADR_WIDTH    5     //5字节地址宽度
#define RX_ADR_WIDTH    5     //5字节地址宽度
#define TX_PLOAD_WIDTH  32    //32字节有效数据宽度
#define RX_PLOAD_WIDTH  32    //32字节有效数据宽度

const uchar TX_ADDRESS[TX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //发送地址
const uchar RX_ADDRESS[RX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //发送地址

sbit NRF_CE   = P2^7;
sbit NRF_CSN  = P2^6;
sbit NRF_MISO = P2^3;
sbit NRF_MOSI = P2^4;
sbit NRF_SCK  = P2^5;
sbit NRF_IRQ  = P2^2;
sbit LED=P1^0;

sbit S1=P3^2;
sbit S2=P3^4;
uchar rece_buf[32];

void delay_us(uchar num)
{
	uchar i; 
	for(i=0;i>num;i++)
 	_nop_();
}
void delay_150us()
{
	uint i;

	for(i=0;i>150;i++);
}
void delay(uint t)
{
	uchar k;
	while(t--)
	for(k=0;k<200;k++);
}
/***************************************************************/

/*******************************************************************/
uchar SPI_RW(uchar byte)
{
	uchar bit_ctr;
	for(bit_ctr=0;bit_ctr<8;bit_ctr++)  // 输出8位
	{
		NRF_MOSI=(byte&0x80); 			// MSB TO MOSI
		byte=(byte<<1);					// shift next bit to MSB
		NRF_SCK=1;
		byte|=NRF_MISO;	        		// capture current MISO bit
		NRF_SCK=0;
	}
	return byte;
}

/*********************************************/
/* 函数功能：给24L01的寄存器写值（一个字节） */
/* 入口参数：reg   要写的寄存器地址          */
/*           value 给寄存器写的值            */
/* 出口参数：status 状态值                   */
/*********************************************/
uchar NRF24L01_Write_Reg(uchar reg,uchar value)
{
	uchar status;

	NRF_CSN=0;                  //CSN=0;   
  	status = SPI_RW(reg);		//发送寄存器地址,并读取状态值
	SPI_RW(value);
	NRF_CSN=1;                  //CSN=1;

	return status;
}
/*************************************************/
/* 函数功能：读24L01的寄存器值 （一个字节）      */
/* 入口参数：reg  要读的寄存器地址               */
/* 出口参数：value 读出寄存器的值                */
/*************************************************/
uchar NRF24L01_Read_Reg(uchar reg)
{
 	uchar value;

	NRF_CSN=0;              //CSN=0;   
  	SPI_RW(reg);			//发送寄存器值(位置),并读取状态值
	value = SPI_RW(NOP);
	NRF_CSN=1;             	//CSN=1;

	return value;
}
/*********************************************/
/* 函数功能：读24L01的寄存器值（多个字节）   */
/* 入口参数：reg   寄存器地址                */
/*           *pBuf 读出寄存器值的存放数组    */
/*           len   数组字节长度              */
/* 出口参数：status 状态值                   */
/*********************************************/
uchar NRF24L01_Read_Buf(uchar reg,uchar *pBuf,uchar len)
{
	uchar status,u8_ctr;
	NRF_CSN=0;                   	//CSN=0       
  	status=SPI_RW(reg);				//发送寄存器地址,并读取状态值   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)
	pBuf[u8_ctr]=SPI_RW(0XFF);		//读出数据
	NRF_CSN=1;                 		//CSN=1
  	return status;        			//返回读到的状态值
}
/**********************************************/
/* 函数功能：给24L01的寄存器写值（多个字节）  */
/* 入口参数：reg  要写的寄存器地址            */
/*           *pBuf 值的存放数组               */
/*           len   数组字节长度               */
/**********************************************/
uchar NRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar len)
{
	uchar status,u8_ctr;
	NRF_CSN=0;
  	status = SPI_RW(reg);			//发送寄存器值(位置),并读取状态值
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)
	SPI_RW(*pBuf++); 				//写入数据
	NRF_CSN=1;
  	return status;          		//返回读到的状态值
}							  					   

/*********************************************/
/* 函数功能：24L01接收数据                   */
/* 入口参数：rxbuf 接收数据数组              */
/* 返回值： 0   成功收到数据                 */
/*          1   没有收到数据                 */
/*********************************************/
uchar NRF24L01_RxPacket(uchar *rxbuf)
{
	uchar state;
	 
	state=NRF24L01_Read_Reg(STATUS);  			//读取状态寄存器的值    	 
	NRF24L01_Write_Reg(WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
	if(state&RX_OK)								//接收到数据
	{
		NRF_CE = 0;
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);					//清除RX FIFO寄存器
		NRF_CE = 1;
		delay_150us(); 
		return 0; 
	}	   
	return 1;//没收到任何数据
}
/**********************************************/
/* 函数功能：设置24L01为发送模式              */
/* 入口参数：txbuf  发送数据数组              */
/* 返回值； 0x10    达到最大重发次数，发送失败*/
/*          0x20    成功发送完成              */
/*          0xff    发送失败                  */
/**********************************************/
uchar NRF24L01_TxPacket(uchar *txbuf)
{
	uchar state;
   
	NRF_CE=0;												//CE拉低，使能24L01配置
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);	//写数据到TX BUF  32个字节
 	NRF_CE=1;												//CE置高，使能发送	   
	while(NRF_IRQ==1);										//等待发送完成
	state=NRF24L01_Read_Reg(STATUS);  						//读取状态寄存器的值	   
	NRF24L01_Write_Reg(WRITE_REG+STATUS,state); 			//清除TX_DS或MAX_RT中断标志
	if(state&MAX_TX)										//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);					//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(state&TX_OK)											//发送完成
	{
		return TX_OK;
	}
	return 0xff;											//发送失败
}

/********************************************/
/* 函数功能：检测24L01是否存在              */
/* 返回值；  0  存在                        */
/*           1  不存在                      */
/********************************************/ 	  
uchar NRF24L01_Check(void)
{
	uchar check_in_buf[5]={0x11,0x22,0x33,0x44,0x55};
	uchar check_out_buf[5]={0x00};

	NRF_SCK=0;
	NRF_CSN=1;    
	NRF_CE=0;

	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR, check_in_buf, 5);

	NRF24L01_Read_Buf(READ_REG+TX_ADDR, check_out_buf, 5);

	if((check_out_buf[0] == 0x11)&&\
	   (check_out_buf[1] == 0x22)&&\
	   (check_out_buf[2] == 0x33)&&\
	   (check_out_buf[3] == 0x44)&&\
	   (check_out_buf[4] == 0x55))return 0;
	else return 1;
}			


void NRF24L01_RT_Init(void)
{	
	NRF_CE=0;		  
  	NRF24L01_Write_Reg(WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度
	NRF24L01_Write_Reg(FLUSH_RX,0xff);									//清除RX FIFO寄存器    
  	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,(uchar*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
  	NRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0,(uchar*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  
  	NRF24L01_Write_Reg(WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
  	NRF24L01_Write_Reg(WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
  	NRF24L01_Write_Reg(WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
  	NRF24L01_Write_Reg(WRITE_REG+RF_CH,0);        //设置RF通道为2.400GHz  频率=2.4+0GHz
  	NRF24L01_Write_Reg(WRITE_REG+RF_SETUP,0x0F);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0f);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF_CE=1;									  //CE置高，使能发送
}

void SEND_BUF(uchar *buf)
{
	NRF_CE=0;
	NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0e);
	NRF_CE=1;
	delay_us(15);
	NRF24L01_TxPacket(buf);
	NRF_CE=0;
	NRF24L01_Write_Reg(WRITE_REG+CONFIG, 0x0f);
	NRF_CE=1;	
}
void main()
{
	while(NRF24L01_Check()); // 等待检测到NRF24L01，程序才会向下执行
	NRF24L01_RT_Init();			
	while(1)
	{
		if(NRF_IRQ==0)	 	// 如果无线模块接收到数据
		{		
			if(NRF24L01_RxPacket(rece_buf)==0)
			{			   
				if(	rece_buf[1]=='1')		   	//第1位以后是收到的命令数据，rece_buf[0]是数据位数长度
					LED=0;
				if(	rece_buf[1]=='2')	 		//第1位以后是收到的命令数据，rece_buf[0]是数据位数长度
					LED=1;		
			}
		}
		if(S1==0)								//按下S1发送ASCII码 “123”
		{
			rece_buf[1]='1';
			rece_buf[2]='2';
			rece_buf[3]='3';
			rece_buf[0]=3;	  					//一共要发送3个字节，rece_buf[0]必须是3！！！！！！
			SEND_BUF(rece_buf);
			while(!S1);	
		}
		if(S2==0)								//按下S1发送ASCII码 “ABCD”
		{
			rece_buf[1]='A';
			rece_buf[2]='B';
			rece_buf[3]='C';
			rece_buf[4]='D';
			rece_buf[0]=4;	   					//一共要发送4个字节，rece_buf[0]必须是4！！！！！！
			SEND_BUF(rece_buf);
			while(!S2);	
		}
		if(1)			  					//发送 “上海宝嵌电子”
		{
			rece_buf[1]=0xc9;					//上
			rece_buf[2]=0xcf;					//上
			rece_buf[3]=0xba;					//海
			rece_buf[4]=0xa3;					//海
			rece_buf[5]=0xb1;					//宝
			rece_buf[6]=0xa6;					//宝
			rece_buf[7]=0xc7;					//嵌
			rece_buf[8]=0xb6;					//嵌
			rece_buf[9]=0xb5;					//电
			rece_buf[10]=0xe7;					//电
			rece_buf[11]=0xd7;					//子
			rece_buf[12]=0xd3;					//子
			rece_buf[0]=12;						//一共要发送12个字节，rece_buf[0]必须是12！！！！！！
			SEND_BUF(rece_buf);
		}
		delay(100);
	}
}



