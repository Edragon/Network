
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit IRIN = P3^3;//红外接收头数据线
uchar IRCOM[7];	 //红外数据缓冲区  
uchar IR_flag;   //红外数据接收标志
//功能:延时1毫秒
//入口参数:x
//出口参数:无
//说明:晶振12M
void Delay_xms(uint x)
{ 
  uint i,j;
  for(i=0;i<x;i++)
    for(j=0;j<112;j++);
}
//0.14ms延时函数
void delay(uchar x)    
{
  uchar i;
  while(x--)
  {
   for (i = 0; i<12; i++) 
   {
    _nop_();
   }
  }
}
//串口初始化(系统晶振为12MHz)
void Uart_init(uchar Baud_flag)
{
   TMOD = 0x20;       //T1 2
   PCON = 0x00;       //SMOD = 0
   SCON = 0x50;	      //串口1 8
   switch(Baud_flag)
   {   	
    case 0x00:        //2400 11.0592M:0xf4
	  TH1=0xf3;
	  TL1=0xf3;
	break;
	case 0x01:        //4800 11.0592M:0xfa
	  TH1=0xf9;
	  TL1=0xf9;
	break;
    case 0x02:        //9600 11.0592M:0xfd
	  TH1=0xfd;
	  TL1=0xfd;
	break;
    case 0x03:        //19200 11.0592M:0xfe
      TH1=0xfd;
	  TL1=0xfd;
    break;
	default:          //默认为2400
	  TH1=0xf3;
	  TL1=0xf3;
	break;
   }   
}
//串口发送
void Send_char(uchar ch)
{
 EA=0;
 SBUF=ch; 
 while(!TI);      //等待发送完毕
 TI=0;           //清中断 
 EA=1;
}
//红外数据接收
void IR_IN() interrupt 2 using 0 
{
  uchar j,k,N=0;  
  EX1 = 0;   
  delay(15);
  if (IRIN) 
   {
    EX1 =1;
	return;
   }                            //确认IR信号出现   
  while(!IRIN);            //等IR变为高电平，跳过9ms的前导低电平信号
  for (j=0;j<4;j++)         //收集四组数据
  { 
   for (k=0;k<8;k++)        //每组数据有8位
   {
    while (IRIN);            //等 IR 变为低电平，跳过4.5ms的前导高电平信号     
    while (!IRIN);          //等 IR 变为高电平    
    while (IRIN)           //计算IR高电平时长
     {
      delay(1);
      N++;           
      if (N>=30)
	   { 
        EX1=1;
	    return;
       }                  //0.14ms计数过长自动离开。
     }                        //高电平计数完毕                
     IRCOM[j]=IRCOM[j] >> 1;                  //数据最高位补0
     if (N>=8) {IRCOM[j] = IRCOM[j] | 0x80;}  //数据最高位补1
     N=0;
  }//end for k
 }//end for j   
   if (IRCOM[2]!=~IRCOM[3])//数据校验
   { 
     EX1=1;
     return; 
   }
   EX1 = 1;
   IR_flag=1; //置接收标志
} 
void main(void)
{
 Delay_xms(50);      //等待系统稳定
 EA=0;
 TR1=1;//启动定时器
 ES=1; //开串口中断
 IT1=1;//外部中断1,下降沿触发
 EX1=1;//使能外部中断1 
 EA=1; //开总中断
 IRIN=1; //将P3^3置高
 Uart_init(0);//波特率初始化为2400
 while(1)
 {
  if(IR_flag)
  {  
   IR_flag=0;    //清接收标志   
   Send_char(IRCOM[2]);//将接收到的数据通过串口发送   
  }
 }
}
