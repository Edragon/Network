									   #include <reg51.h>
#include <intrins.h>

void IR_SHOW();
void delay(unsigned char x);//x*0.14MS
void delay1(unsigned char ms);
void beep();

sbit IRIN = P3^2;
sbit BEEP = P3^7;
sbit RELAY= P1^3;
sbit GEWEI= P2^7;
sbit SHIWEI= P2^6;

unsigned char IRCOM[8];
unsigned char code table[16] = 
                    {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
main()
{
 IE = 0x81;    //允许总中断中断,使能 INT0 外部中断
 TCON = 0x1;   //触发方式为脉冲负边沿触发
 delay(1);

         IRIN=1;
      BEEP=1;
   RELAY=1;
   for(;;)
   {
    IR_SHOW();
   }

} //end main

void IR_IN() interrupt 0 using 0
{
 unsigned char i,j,k,N=0;
  EA = 0;
I1:
  for (i=0;i<4;i++)
   {
    if (IRIN==0) break;
 if (i==3) {EA =1;return;}
   }
  delay(20);
    if (IRIN==1) goto I1;  //确认IR信号出现
  while (!IRIN)            //等 IR 变为高电平
    {delay(1);}

 for (j=0;j<4;j++)
 { 
  for (k=0;k<8;k++)
  {
   while (IRIN)            //等 IR 变为低电平
     {delay(1);}
    while (!IRIN)          //等 IR 变为高电平
     {delay(1);}
     while (IRIN)           //计算IR高电平时长
      {
    delay(1);
    N++;           
    if (N>=30) {EA=1;return;}
   }
     IRCOM[j]=IRCOM[j] >> 1;
     if (N>=8) {IRCOM[j] = IRCOM[j] | 0x80;}
     N=0;
  }//end for k
 }//end for j
   
   if (IRCOM[2]!=~IRCOM[3]) {EA=1;return;}
   IRCOM[5]=IRCOM[2] & 0x0F;
   IRCOM[6]=IRCOM[2] & 0xF0;
   IRCOM[6]=IRCOM[6] >> 4;
   beep();
   EA = 1;
  
}

void IR_SHOW()
 {
  P0 = table[IRCOM[5]];      
  GEWEI = 0;
  SHIWEI = 1;
  delay1(4);
  P0 = table[IRCOM[6]];      
  SHIWEI = 0;
  GEWEI = 1;
  delay1(4);
 }

void beep()
{
  unsigned char i;
  for (i=0;i<100;i++)
   {
   delay(5);
   BEEP=!BEEP;
   } 
  BEEP=1;
}

void delay(unsigned char x)//x*0.14MS
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++) {}
 }
}


void delay1(unsigned char ms)
{
 unsigned char i;
  while(ms--)
 {
  for(i = 0; i<120; i++)
  {
   _nop_();
   _nop_();
   _nop_();
   _nop_();
  }
 }
}