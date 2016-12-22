/*******************************************************/
/* 名   称：NRF24L01+开发板测试程序（DS18B20温度采集实验）*/
/* 功   能：发送接收测试程序                           */
/* 说   明：开发板采集温度通过无线串口发给电脑         */
/* 作者：BQDZ     （论坛：http://bqdz.taobao.com）     */
/* 联系方式： QQ :851968194     旺旺：王亚坤2864       */
/*           手机：15821472722（上海）                 */
/*******************************************************/
#include "DS18B20.h"  	
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

void delay_main(uint t)
{
	uint k;
	while(t--)
	for(k=0;k<200;k++);
}
void main()
{
	uint num;
	uint temp;
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
		delay_main(10);
		num++;
		if(num>=100)
		{
			num=0;
			temp=ReadTemperature();
			rece_buf[1]=0xB5;					//当
			rece_buf[2]=0xB1;					//当
			rece_buf[3]=0xC7;					//前
			rece_buf[4]=0xB0;					//前
			rece_buf[5]=0xCE;					//温
			rece_buf[6]=0xC2;					//温
			rece_buf[7]=0xB6;					//度
			rece_buf[8]=0xC8;					//度
			rece_buf[9]=0xA3;					//：
			rece_buf[10]=0xBA;					//：
			rece_buf[11]=temp/1000+0x30;				
			rece_buf[12]=temp%1000/100+0x30;				
			rece_buf[13]=temp%100/10+0x30;				
			rece_buf[14]='.';					
			rece_buf[15]=temp%10+0x30;	
			rece_buf[16]=0x0D;		 //回车
			rece_buf[17]=0x0A;		 //回车
			rece_buf[0]=17;
			SEND_BUF(rece_buf);			
		}
	}
}



