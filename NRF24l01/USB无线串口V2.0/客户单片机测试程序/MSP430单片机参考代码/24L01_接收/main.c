/****************POWSOS__430******************************
程序功能：24L01接收板接收发射板数据
----------------------------------------------------------
测试说明：若收到数据,D1~D7会同时闪烁
*********************************************************/

#include  <msp430x14x.h>
#include "24l01.h"
extern unsigned char TestBuf;
/*******************************************
函数名称：Init_Clock
功    能：设置系统时钟选用外部晶振8M
参    数：无
返回值  ：无
********************************************/
void Init_Clock(void)
{
    unsigned char i;
  /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     //等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             //晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2 + SELS;           //MCLK和SMCLK选择高频晶振
}

int main( void )
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT 
    P2DIR |=0XFF;                   //LED灯初始化
    P2OUT |=0XFF;
    Init_Clock();
    nRF24L01_IO_set();
    NRF_Check();
    nRF24L01_Init(nRF_RX_Mode);
    while(1)
    {
      
      nRF24L01_Revceive();
      

    }
    
}

