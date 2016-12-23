/*******************************************************/
/* 名   称：NRF24L01+开发板测试程序（上位机通讯矩阵键盘）*/
/* 功   能：开发板发送电脑接收，电脑发送开发板接收     */
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
sbit     P14 = P1^4;    
sbit     P15 = P1^5;    
sbit     P16 = P1^6;    
sbit     P17 = P1^7;    
uchar GetKeyChar()
{
	
	P1=0xfe;
	if(!P14){return '1';}  
	if(!P15){return '2';}   
	if(!P16){return '3';}  
	if(!P17){return 'A';} 

	P1=0xfd;
	if(!P14){return '4';}    
	if(!P15){return '5';}   
	if(!P16){return '6';}   
	if(!P17){return 'B';} 


	P1=0xfb;
	if(!P14){return '7';}   
	if(!P15){return '8';}    
	if(!P16){return '9';}    
	if(!P17){return 'C';} 

	P1=0xf7;
	if(!P14){return '*';}   
	if(!P15){return '0';}   
	if(!P16){return '#';}    
	if(!P17){return 'D';}   
	
	return 99;          //没有按键被按下
}
void main()
{
	uchar strKeyCode;
	while(NRF24L01_Check()); // 等待检测到NRF24L01，程序才会向下执行
	NRF24L01_RT_Init(TX_PLOAD_WIDTH,TX_ADDRESS,TX_ADR_WIDTH,RX_ADDRESS,RX_ADR_WIDTH,rate);			
	while(1)
	{
		strKeyCode=GetKeyChar();
		if(strKeyCode!=99)
		{
			rece_buf[1]=0xC4;					//您
			rece_buf[2]=0xFA;					//您
			rece_buf[3]=0xB0;					//按
			rece_buf[4]=0xB4;					//按
			rece_buf[5]=0xCF;					//下
			rece_buf[6]=0xC2;					//下
			rece_buf[7]=0xB5;					//的
			rece_buf[8]=0xC4;					//的
			rece_buf[9]=0xCA;					//是
			rece_buf[10]=0xC7;					//是
			rece_buf[11]=0xA3;					//：
			rece_buf[12]=0xBA;					//：
			
			rece_buf[13]=strKeyCode;

			rece_buf[14]=0x0D;					//回
			rece_buf[15]=0x0A;					//车

			rece_buf[0]=15;	   					//一共要发送15个字节，rece_buf[0]=15   这是和本店USB转nRF24L01模块通信协议
			SEND_BUF(rece_buf);
			delay_us(20000); 		
		}
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
			rece_buf[0]=1;	   					//一共要发送1个字节，rece_buf[0]=1	 这是和本店USB转nRF24L01模块通信协议
			SEND_BUF(rece_buf);
			delay_us(10000);
			while(!S1);	
		}
		if(S2==0)			  					//按下S2发送 “上海宝嵌电子”
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
			rece_buf[0]=12;						//一共要发送12个字节，rece_buf[0]必须是12 这是和本店USB转nRF24L01模块通信协议
			SEND_BUF(rece_buf);
			delay_us(20000);
			while(!S2);	
		}
	}
}



