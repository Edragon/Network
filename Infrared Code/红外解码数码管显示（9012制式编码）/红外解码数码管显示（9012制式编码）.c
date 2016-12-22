/*copyright 2009,Shen zhen  JinChuang Electronic Technology co.,Ltd
 *
 *This sample is used for Timer1 16bit timer mode.
 *
 *write by Shifang 2009-4-23
 *
 *V1.1
 */
 //使用12M晶振 适用于TC9012芯片，其他芯片请自行更改解码时序
#include<reg52.h>
#include<stdio.h>
#include<intrins.h>

////////////////////////////////////////////////
#define TURE 1
#define FALSE 0

////////////////////////////////////////////////

sbit IR=P3^2;//红外接口标志


////////////////////////////////////////////

unsigned char  irtime;//红外用全局变量

bit irpro_ok,irok;
unsigned char IRcord[4];
unsigned char   irdata[33];

//////////////////////////////////////////////

void Delay(unsigned char mS);
void Ir_work(void);
void Ircordpro(void);

//////////////////////////////////////////////////////////////////  

void tim0_isr (void) interrupt 1 using 1//定时器0中断服务函数
{
  irtime++;
}

///////////////////////////////////////////////////////////////////////
void ex0_isr (void) interrupt 0 using 0//外部中断0服务函数
{
  static unsigned char  i;
  static bit startflag;

 if(startflag)
 {
   
    if(irtime<55&&irtime>40)//引导码 TC9012的头码
            i=0;
     
    		irdata[i]=irtime;//一次存储32位电平宽度
    		irtime=0;
    		i++;
   			 if(i==33)
      			{
	  			 irok=1;
				 i=0;
	  			}
          }
	 
  	 else
		{irtime=0;startflag=1;}

}

////////////////////////////////////////////////////////////////////
void TIM0init(void)//定时器0初始化
{

  TMOD=0x02;//定时器0工作方式2，TH0是重装值，TL0是初值
  TH0=0x00;//reload value
  TL0=0x00;//initial value
  ET0=1;//开中断
  TR0=1;
}
///////////////////////////////////////////////////////////////////
void EX0init(void)
{
 IT0 = 1;   // Configure interrupt 0 for falling edge on /INT0 (P3.2)
 EX0 = 1;   // Enable EX0 Interrupt
 EA = 1;  
}
/****************************************************************/

/******************************************************************/

  void Ir_work(void)//红外键值散转程序
  {
       switch(IRcord[2])//判断第三个数码值
	         {
			 case 1:P0=0xf9;break;//1 显示相应的按键值
			 case 2:P0=0xa4;break;//2
			 case 3:P0=0xb0;break;//3
			 case 4:P0=0x99;break;//4
			 case 5:P0=0x92;break;//5
			 case 6:P0=0x82;break;//6
			 case 7:P0=0xf8;break;//7
			 case 8:P0=0x80;break;//8
			 case 9:P0=0x90;break;//9
		    case 0:P0=0xc0;break;//0

			 }

   

		  irpro_ok=0;//处理完成标志

  }

/*****************************************************************/
void Ircordpro(void)//红外码值处理函数
{ 
  unsigned char i, j, k;
  unsigned char cord,value;

  k=1;
  for(i=0;i<4;i++)//处理4个字节
     {
      for(j=1;j<=8;j++) //处理1个字节8位
         {
          cord=irdata[k];
          if(cord>7)//大于某值为1
		    {
             value=value|0x80;
			}
          else 
		    {
             value=value;
			}
          if(j<8)
		    {
			 value=value>>1;
			}
           k++;
         }
     IRcord[i]=value;
     value=0;     
     } irpro_ok=1;//处理完毕标志位置1
    
}




/////////////////////////////////////////////////////////////////

void main(void)
{
 EX0init(); // Enable Global Interrupt Flag
 TIM0init();//初始化定时器0

 P2=0x00;//8位数码管全部显示

 while(1)//主循环
   {
    if(irok)
	  {   
	   Ircordpro();//码值处理
 	   irok=0;
	  }

    if(irpro_ok)//step press key
	  {
	   Ir_work();//码值识别散转
  	  }
   }
}
  