/*******************************************************/
/* 名   称：NRF24L01+开发板测试程序（LED实验）         */
/* 功   能：发送接收测试程序                           */
/* 说   明：按下开发板1的按键“KEY1”       		   */ 
/*          点亮开发板2的LED1、LED3    				   */
/*          按下开发板1的按键“KEY2”          		   */
/*          点亮开发板2的LED2、LED4    			       */     
/* 作者：BQDZ     （论坛：http://bqdz.taobao.com）     */
/* 联系方式： QQ :851968194     旺旺：王亚坤2864       */
/*           手机：15821472722（上海）                 */
/*******************************************************/
#include "API.h"  	
uchar TX_ADDRESS[TX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //发送地址
uchar RX_ADDRESS[RX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //接收地址
uchar   rate = 0x0F;    				    //2Mbs, 0dB  低噪声增益开启
sbit 	S1   = P3^2;						//按键“KEY1”
sbit 	S2	 = P3^3;						//按键“KEY2”
sbit 	LED1 = P0^3;						//LED1
sbit 	LED2 = P0^2;						//LED2
sbit 	LED3 = P0^1;						//LED3
sbit 	LED4 = P0^0;						//LED4
uchar rece_buf[32];							//接收寄存器

void delay()
{
	uchar i,j;
	for(i=0;i<50;i++)
		for(j=0;j<200;j++);
}
void main()
{
	while(NRF24L01_Check()); // 等待检测到NRF24L01，程序才会向下执行
	NRF24L01_RT_Init(TX_PLOAD_WIDTH,TX_ADDRESS,TX_ADR_WIDTH,RX_ADDRESS,RX_ADR_WIDTH,rate);			
	while(1)
	{
		if(NRF_IRQ==0)	 	// 如果无线模块接收到数据
		{		
			if(NRF24L01_RxPacket(rece_buf)==0)
			{			   
				if(	rece_buf[1]=='1')		   	//第1位以后是收到的命令数据，rece_buf[0]是数据位数长度
					LED1=LED3=~LED1;
				if(	rece_buf[1]=='2')	 		//第1位以后是收到的命令数据，rece_buf[0]是数据位数长度
					LED2=LED4=~LED2;		
			}
		}
		if(S1==0)								//按下S1发送ASCII码 “1”
		{
			rece_buf[1]='1';
			rece_buf[0]=1;	   					//一共要发送1个字节，rece_buf[0]=1
			SEND_BUF(rece_buf);			
			while(!S1);	
			delay();
		}
		if(S2==0)			  					//按下S2发送 ASCII码“2”
		{
			rece_buf[1]='2';
			rece_buf[0]=1;	   					//一共要发送1个字节，rece_buf[0]=1
			SEND_BUF(rece_buf);			
			while(!S2);	
			delay();	
		}
	}
}



