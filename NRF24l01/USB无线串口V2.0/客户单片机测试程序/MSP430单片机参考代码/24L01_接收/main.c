/****************POWSOS__430******************************
�����ܣ�24L01���հ���շ��������
----------------------------------------------------------
����˵�������յ�����,D1~D7��ͬʱ��˸
*********************************************************/

#include  <msp430x14x.h>
#include "24l01.h"
extern unsigned char TestBuf;
/*******************************************
�������ƣ�Init_Clock
��    �ܣ�����ϵͳʱ��ѡ���ⲿ����8M
��    ������
����ֵ  ����
********************************************/
void Init_Clock(void)
{
    unsigned char i;
  /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     //�ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             //����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           //MCLK��SMCLKѡ���Ƶ����
}

int main( void )
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT 
    P2DIR |=0XFF;                   //LED�Ƴ�ʼ��
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

